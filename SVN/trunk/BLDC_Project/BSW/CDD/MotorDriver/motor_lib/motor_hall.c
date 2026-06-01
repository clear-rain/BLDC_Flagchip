/*
 * Hall 位置估算。
 *
 * 文件内按职责划分为五部分：
 * 1. 拓扑表：定义有效 Hall 顺序、扇区中心角和边界。
 * 2. 采样层：读取 U/V/W 三路 GPIO，组合为 Hall 状态。
 * 3. 计时层：访问 Hall 专用计数器 FTU2。
 * 4. 边沿状态机：在中断中处理跳变、更新方向和速度参考。
 * 5. 周期估算：在 FOC 周期内输出连续角度和速度。
 */

#include "motor_hall.h"
#include "motor_config.h"
#include "motor_math.h"
#include "motor_foc.h"
#include "IoHwAb_Dio.h"
#include "IoHwAb_HallCounter.h"
#include <errno.h>
#include <math.h>

/* 模块状态 */

volatile MOTOR_SENSOR_HALL motor_sensor_hall_state;

#if HALL_FEATURE_DEBUG_OBSERVE
volatile uint8_t  motor_hall_overflow_count_dbg;
volatile int8_t   motor_hall_step_delta_dbg;
volatile uint32_t motor_hall_diff_cnt_dbg;
volatile uint8_t  motor_hall_reset_reason_dbg;
#endif

extern MotorFocStruct motor_foc_struct;

/* 首次有效边沿只建立时间参考，不立即输出速度。 */
static uint8_t s_first_edge = 1U;
static uint8_t s_oscillation_cycle_count = 0U;

typedef struct
{
    uint32_t tick_history[HALL_SPEED_WINDOW_SECTORS];
    int8_t step_history[HALL_SPEED_WINDOW_SECTORS];
    uint8_t count;
    uint8_t next_index;
    int8_t last_dir;
    uint16_t consecutive_dir_steps;
} HallSpeedWindowState;

static HallSpeedWindowState s_speed_window;

/* ===== 1. 拓扑表与角度定义 ===== */

#define HALL_NUM_STATES  6U
#define HALL_TWO_PI      (2.0f * (float)M_PI)
#define HALL_SECTOR_SPAN ((float)(M_PI / 3.0))   /* 60 deg per sector */

/*
 * 扇区角配置：
 * - HALL_SECTOR_GLOBAL_OFFSET 用于整圈平移。
 * - HALL_SECTOR_TRIM_x 用于各扇区独立微调。
 * 原始角允许超出 [0, 2pi)，后续会统一归一化并展开成单调序列。
 */
#ifndef HALL_SECTOR_GLOBAL_OFFSET
#define HALL_SECTOR_GLOBAL_OFFSET (0.0f)
#define HALL_SECTOR_TRIM_0 (2.680f)
#define HALL_SECTOR_TRIM_1 (2.629f)
#define HALL_SECTOR_TRIM_2 (2.624f)
#define HALL_SECTOR_TRIM_3 (2.631f)
#define HALL_SECTOR_TRIM_4 (2.621f)
#define HALL_SECTOR_TRIM_5 (2.604f)
#endif

/* 6 个有效 Hall 状态按正向电角度顺序排列。 */
static const uint16_t s_hall_seq[HALL_NUM_STATES] = {
    0x01U, 0x05U,0x04U, 0x06U,0x02U, 0x03U,  
};

/* 原始起始角：允许超出 [0, 2pi)。 */
static const float s_sector_start_raw[HALL_NUM_STATES] = {
    0.0f                      + HALL_SECTOR_TRIM_0 + HALL_SECTOR_GLOBAL_OFFSET,
    (float)(M_PI / 3.0)       + HALL_SECTOR_TRIM_1 + HALL_SECTOR_GLOBAL_OFFSET,
    (float)(2.0 * M_PI / 3.0) + HALL_SECTOR_TRIM_2 + HALL_SECTOR_GLOBAL_OFFSET,
    (float)(M_PI)             + HALL_SECTOR_TRIM_3 + HALL_SECTOR_GLOBAL_OFFSET,
    (float)(4.0 * M_PI / 3.0) + HALL_SECTOR_TRIM_4 + HALL_SECTOR_GLOBAL_OFFSET,
    (float)(5.0 * M_PI / 3.0) + HALL_SECTOR_TRIM_5 + HALL_SECTOR_GLOBAL_OFFSET,
};

/* 归一化后扇区起始角：按 Hall 顺序单调递增（允许 >2pi）。 */
static float s_sector_start[HALL_NUM_STATES];
static uint8_t s_sector_start_ready = 0U;

static void Hall_UpdateSectorStarts(void)
{
    uint8_t idx;
    float prev;

    prev = s_sector_start_raw[0U];
    Mat_AngleWraps(&prev);
    s_sector_start[0U] = prev;

    for (idx = 1U; idx < HALL_NUM_STATES; idx++)
    {
        float curr = s_sector_start_raw[idx];
        Mat_AngleWraps(&curr);

        while (curr <= prev)
        {
            curr += HALL_TWO_PI;
        }

        s_sector_start[idx] = curr;
        prev = curr;
    }

    s_sector_start_ready = 1U;
}

static void Hall_EnsureSectorStartsReady(void)
{
    if (s_sector_start_ready == 0U)
    {
        Hall_UpdateSectorStarts();
    }
}

/* 由扇区边界推导得到的中心角缓存；边界不变时只需计算一次。 */
static float s_center_angle[HALL_NUM_STATES];
static uint8_t s_center_angle_ready = 0U;

static void Hall_UpdateCenterAngles(void)
{
    uint8_t idx;

    Hall_EnsureSectorStartsReady();

    for (idx = 0U; idx < HALL_NUM_STATES; idx++)
    {
        uint8_t next = (uint8_t)(idx + 1U);
        float start = s_sector_start[idx];
        float end;
        float center;

        if (next >= HALL_NUM_STATES)
        {
            next = 0U;
        }

        end = s_sector_start[next];
        if (end <= start)
        {
            end += HALL_TWO_PI;
        }

        center = 0.5f * (start + end);
        Mat_AngleWraps(&center);
        s_center_angle[idx] = center;
    }

    s_center_angle_ready = 1U;
}

/* 前向声明：供扇区限幅函数在定义前调用。 */
static float Hall_AlignAngleToRef(float sample, float reference);

/* 状态转扇区索引；非法状态返回 -1。 */
static int8_t Hall_GetIndex(uint16_t state)
{
    uint8_t i;
    for (i = 0U; i < HALL_NUM_STATES; i++)
    {
        if (s_hall_seq[i] == state)
        {
            return (int8_t)i;
        }
    }
    return -1;
}

/* 查询当前状态对应的扇区中心角。 */
static float Hall_CenterAngle(uint16_t state)
{
    int8_t idx = Hall_GetIndex(state);

    if (idx < 0) { return 0.0f; }
    if (s_center_angle_ready == 0U)
    {
        Hall_UpdateCenterAngles();
    }

    return s_center_angle[(uint8_t)idx];
}

/* 查询扇区终点；统一使用“下一个扇区起点”，必要时加 2pi 保持连续。 */
static float Hall_SectorEnd(uint8_t idx)
{
    uint8_t next = (uint8_t)(idx + 1U);
    float start;
    float end;

    Hall_EnsureSectorStartsReady();

    if (next >= HALL_NUM_STATES)
    {
        next = 0U;
    }

    start = s_sector_start[idx];
    end = s_sector_start[next];
    if (end <= start)
    {
        end += HALL_TWO_PI;
    }

    return end;
}

/*
 * 计算从前一状态到当前状态的跨步数。
 * 正值表示正向，负值表示反向。
 * 若正反两个方向跨步相同，则用上一次方向消歧。
 */
static int8_t Hall_StepDelta(uint16_t prev_state, uint16_t curr_state,
                             float old_dir)
{
    int8_t ip = Hall_GetIndex(prev_state);
    int8_t ic = Hall_GetIndex(curr_state);
    uint8_t fwd, bwd;

    if ((ip < 0) || (ic < 0) || (ip == ic))
    {
        return 0;
    }

    fwd = (uint8_t)((ic - ip + (int8_t)HALL_NUM_STATES) % (int8_t)HALL_NUM_STATES);
    bwd = (uint8_t)((ip - ic + (int8_t)HALL_NUM_STATES) % (int8_t)HALL_NUM_STATES);

    if (fwd < bwd) { return (int8_t)fwd; }
    if (bwd < fwd) { return (int8_t)(-(int8_t)bwd); }
    /* 3 步对 3 步时沿用上一次方向。 */
    return (old_dir < 0.0f) ? (int8_t)(-(int8_t)bwd) : (int8_t)fwd;
}

/* 根据跨步数计算跨越的电角度。 */
static float Hall_TravelAngle(int8_t step_delta)
{
    uint8_t abs_steps = (step_delta >= 0) ? (uint8_t)step_delta
                                          : (uint8_t)(-step_delta);
    return (float)abs_steps * HALL_SECTOR_SPAN;
}

/*
 * 相邻跳变的边沿参考角。
 * 正向进入扇区时取起始边界，反向进入扇区时取结束边界。
 */
static float Hall_EdgeBoundary(uint16_t to_state, int8_t step_delta)
{
    int8_t idx = Hall_GetIndex(to_state);
    if (idx < 0) { return 0.0f; }

    Hall_EnsureSectorStartsReady();

    if (step_delta > 0)
    {
        return s_sector_start[(uint8_t)idx];
    }
    else
    {
        return Hall_SectorEnd((uint8_t)idx);
    }
}

/* 查询当前状态所属扇区的边界。 */
static uint8_t Hall_GetSectorBounds(uint16_t state, float *start, float *end)
{
    int8_t idx = Hall_GetIndex(state);
    if (idx < 0) { return 0U; }

    Hall_EnsureSectorStartsReady();

    *start = s_sector_start[(uint8_t)idx];
    *end   = Hall_SectorEnd((uint8_t)idx);
    return 1U;
}

/* 角度归一化到 [0, 2pi)。 */
static float Hall_Wrap2Pi(float angle)
{
    Mat_AngleWraps(&angle);
    return angle;
}

/* 将角度限制在当前扇区范围内。 */
static float Hall_ClampToSector(float angle, float start, float end)
{
    float midpoint;
    float aligned;

    /* start/end 可能跨越 2pi，先把采样值平移到当前扇区同一圈再限幅。 */
    midpoint = 0.5f * (start + end);
    aligned = Hall_AlignAngleToRef(angle, midpoint);

    if (aligned < start - 0.2f) { aligned = start - 0.2f; }
    if (aligned > end + 0.2f)   { aligned = end + 0.2f; }

    return Hall_Wrap2Pi(aligned);
}

/* 角度归一化到 (-pi, pi]。 */
static float Hall_WrapPi(float angle)
{
    while (angle > (float)M_PI)
    {
        angle -= HALL_TWO_PI;
    }
    while (angle <= (float)-M_PI)
    {
        angle += HALL_TWO_PI;
    }
    return angle;
}

/* 计算有符号最小角差。 */
static float Hall_SignedAngleDiff(float lhs, float rhs)
{
    return Hall_WrapPi(lhs - rhs);
}

/* 将采样值平移到参考值附近，避免跨 2pi 导致滤波跳变。 */
static float Hall_AlignAngleToRef(float sample, float reference)
{
    while ((sample - reference) > (float)M_PI)
    {
        sample -= HALL_TWO_PI;
    }
    while ((sample - reference) <= (float)-M_PI)
    {
        sample += HALL_TWO_PI;
    }
    return sample;
}

/* ===== 2. Hall 采样 ===== */

static uint16_t Hall_ReadRawState(void)
{
    uint16_t u = (IoHwAb_Dio_ReadChannel(IO_HALL_U_IDX) != DIO_STD_LOW) ? 1U : 0U;
    uint16_t v = (IoHwAb_Dio_ReadChannel(IO_HALL_V_IDX) != DIO_STD_LOW) ? 1U : 0U;
    uint16_t w = (IoHwAb_Dio_ReadChannel(IO_HALL_W_IDX) != DIO_STD_LOW) ? 1U : 0U;
    return (uint16_t)((u << 2) | (v << 1) | w);
}

/* ===== 3. Hall 计时器访问 ===== */

static uint32_t Hall_CounterGet(void)
{
    return IoHwAb_HallCounter_GetCnt();
}

static void Hall_CounterClear(void)
{
    IoHwAb_HallCounter_Clear();
}

static uint8_t Hall_CounterOverflowCount(void)
{
    return IoHwAb_HallCounter_GetOverflowCount();
}

static float Hall_TicksToSeconds(uint32_t ticks)
{
    return (float)ticks * HALL_COUNTER_SECONDS_PER_TICK;
}

static uint16_t Hall_MechanicalTurnSteps(void)
{
    uint16_t pole_pairs = (uint16_t)(NUM_POLE_PAIRS + 0.5f);
    return (uint16_t)(HALL_NUM_STATES * pole_pairs);
}

static void Hall_SpeedWindowReset(void)
{
    uint8_t i;

    for (i = 0U; i < HALL_SPEED_WINDOW_SECTORS; i++)
    {
        s_speed_window.tick_history[i] = 0U;
        s_speed_window.step_history[i] = 0;
    }

    s_speed_window.count = 0U;
    s_speed_window.next_index = 0U;
    s_speed_window.last_dir = 0;
    s_speed_window.consecutive_dir_steps = 0U;
    s_oscillation_cycle_count = 0U;

    motor_sensor_hall_state.window_speed = 0.0f;
    motor_sensor_hall_state.window_speed_valid = 0U;
    motor_sensor_hall_state.oscillation_flag = 0U;
    motor_sensor_hall_state.electrical_cycle_complete = 0U;
    motor_sensor_hall_state.mechanical_turn_complete = 0U;
}

static void Hall_SpeedWindowPush(uint32_t dt_ticks, int8_t step_delta)
{
    int8_t dir = (step_delta > 0) ? 1 : -1;

    s_speed_window.tick_history[s_speed_window.next_index] = dt_ticks;
    s_speed_window.step_history[s_speed_window.next_index] = step_delta;

    if (s_speed_window.count < HALL_SPEED_WINDOW_SECTORS)
    {
        s_speed_window.count++;
    }

    s_speed_window.next_index++;
    if (s_speed_window.next_index >= HALL_SPEED_WINDOW_SECTORS)
    {
        s_speed_window.next_index = 0U;
    }

    if (s_speed_window.last_dir == dir)
    {
        s_speed_window.consecutive_dir_steps++;
    }
    else
    {
        s_speed_window.last_dir = dir;
        s_speed_window.consecutive_dir_steps = 1U;
    }
}

static void Hall_SpeedWindowEvaluate(void)
{
    uint8_t i;
    uint8_t start;
    uint8_t idx;
    int16_t net_steps = 0;
    uint16_t abs_steps = 0U;
    uint32_t tick_sum = 0U;
    uint8_t dir_flips = 0U;
    int8_t prev_dir = 0;

    motor_sensor_hall_state.window_speed = 0.0f;
    motor_sensor_hall_state.window_speed_valid = 0U;
    motor_sensor_hall_state.oscillation_flag = 0U;
    motor_sensor_hall_state.electrical_cycle_complete =
        (uint8_t)(s_speed_window.consecutive_dir_steps >= HALL_NUM_STATES);
    motor_sensor_hall_state.mechanical_turn_complete =
        (uint8_t)(s_speed_window.consecutive_dir_steps >= Hall_MechanicalTurnSteps());

    if (s_speed_window.count == 0U)
    {
        return;
    }

    start = (s_speed_window.count < HALL_SPEED_WINDOW_SECTORS)
        ? 0U : s_speed_window.next_index;

    for (i = 0U; i < s_speed_window.count; i++)
    {
        int16_t step_value;
        int8_t curr_dir;

        idx = (uint8_t)(start + i);
        if (idx >= HALL_SPEED_WINDOW_SECTORS)
        {
            idx = (uint8_t)(idx - HALL_SPEED_WINDOW_SECTORS);
        }

        step_value = (int16_t)s_speed_window.step_history[idx];
        tick_sum += s_speed_window.tick_history[idx];
        net_steps = (int16_t)(net_steps + step_value);
        abs_steps = (uint16_t)(abs_steps + (uint16_t)((step_value >= 0)
            ? step_value : -step_value));

        curr_dir = (step_value > 0) ? 1 : -1;
        if ((prev_dir != 0) && (curr_dir != prev_dir))
        {
            dir_flips++;
        }
        prev_dir = curr_dir;
    }

#if HALL_FEATURE_OSCILLATION_DETECT
    if ((s_speed_window.count >= HALL_OSCILLATION_MIN_SAMPLES)
        && (abs_steps >= HALL_OSCILLATION_MIN_SAMPLES)
        && (dir_flips >= HALL_OSCILLATION_MIN_DIR_FLIPS)
        && ((uint16_t)((net_steps >= 0) ? net_steps : -net_steps)
            <= HALL_OSCILLATION_MAX_NET_STEPS))
    {
        motor_sensor_hall_state.oscillation_flag = 1U;
    }
#endif

#if HALL_FEATURE_WINDOW_SPEED
    if ((s_speed_window.count >= HALL_SPEED_WINDOW_SECTORS)
        && (tick_sum > 0U) && (net_steps != 0))
    {
        float dt = Hall_TicksToSeconds(tick_sum);
        float travel_angle = Hall_TravelAngle((int8_t)net_steps);

        if ((dt > 0.0f) && (travel_angle > 0.0f))
        {
            float dir_sign = (net_steps >= 0) ? 1.0f : -1.0f;
            float we_rad_s = dir_sign * (travel_angle / dt);

            motor_sensor_hall_state.window_speed =
                we_rad_s * (60.0f / (HALL_TWO_PI * NUM_POLE_PAIRS));
            motor_sensor_hall_state.window_speed_valid = 1U;
        }
    }
#endif
}

/* ===== 4. 边沿状态机（中断侧） ===== */
#define HALL_EDGE_ERROR_FILTER_ALPHA (0.85f)

/* 按 6 个 Hall 扇区分别记录：原始误差、滤波误差和更新次数。 */
volatile float errorAngleHallAndElectrical[HALL_NUM_STATES] = {0.0f};
volatile float errorAngleHallAndElectricalFiltered[HALL_NUM_STATES] = {0.0f};
volatile uint32_t errorAngleHallAndElectricalUpdateCount[HALL_NUM_STATES] = {0U};
volatile uint8_t errorAngleHallAndElectricalValid[HALL_NUM_STATES] = {0U};

void hall_estimator_irq(void)
{
    uint16_t curr_state;
    uint16_t prev_state;
    int8_t   step_delta;
    float    dir_sign;

    /* 读取当前 Hall 状态。 */
    curr_state = Hall_ReadRawState();
    prev_state = motor_sensor_hall_state.last_hall_state;

    /* 非法状态直接丢弃，不破坏上一笔有效参考。 */
#if HALL_FEATURE_ILLEGAL_STATE_GUARD
    if (Hall_GetIndex(curr_state) < 0)
    {
#if HALL_FEATURE_DEBUG_OBSERVE
        motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_ILLEGAL_STATE;
#endif
        return;
    }
#endif

    /* 状态没变，认为是重复中断或抖动。 */
    if (curr_state == prev_state)
    {
        return;
    }

    /* 根据状态顺序更新方向。 */
    step_delta = Hall_StepDelta(prev_state, curr_state,
                                motor_sensor_hall_state.direction);
    dir_sign = (step_delta >= 0) ? 1.0f : -1.0f;

    if (step_delta > 0)
    {
        motor_sensor_hall_state.direction = 1.0f;
    }
    else if (step_delta < 0)
    {
        motor_sensor_hall_state.direction = -1.0f;
    }
    /* step_delta == 0 时保持原方向。 */

    /* 更新当前 Hall 状态。 */
    motor_sensor_hall_state.last_hall_state = curr_state;

    /* 记录当前扇区中心角，低速或异常时用于回退。 */
    motor_sensor_hall_state.angle = Hall_CenterAngle(curr_state);

#if HALL_FEATURE_DEBUG_OBSERVE
    motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_NONE;
#endif

    /* 首次同步时只建立角度和时间参考，不输出速度。 */
    if ((prev_state == 0U) || (step_delta == 0))
    {
        motor_sensor_hall_state.edge_angle     = motor_sensor_hall_state.angle;
        motor_sensor_hall_state.estimated_angle = motor_sensor_hall_state.angle;
        motor_sensor_hall_state.edge_valid      = 0U;
        motor_sensor_hall_state.speed_valid     = 0U;
        motor_sensor_hall_state.speed           = 0.0f;
        motor_sensor_hall_state.edge_speed      = 0.0f;
        Hall_SpeedWindowReset();
        s_first_edge = 1U;
        Hall_CounterClear();
#if HALL_FEATURE_DEBUG_OBSERVE
        motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_FIRST_SYNC;
#endif
        return;
    }

    /* 处理一次有效跳变。 */
    {
        uint8_t  is_adjacent = (uint8_t)((step_delta == 1) || (step_delta == -1));
        uint32_t now_cnt     = Hall_CounterGet();
        uint8_t  ovf_count   = Hall_CounterOverflowCount();

    #if !HALL_FEATURE_TIMEOUT_DETECTION
        (void)ovf_count;
    #endif

#if HALL_FEATURE_DEBUG_OBSERVE
        motor_hall_overflow_count_dbg = ovf_count;
        motor_hall_step_delta_dbg     = step_delta;
#endif

        /* 相邻跳变时用公共边界角作为插值起点。 */
        if (is_adjacent != 0U)
        {
            motor_sensor_hall_state.edge_angle =
                Hall_Wrap2Pi(Hall_EdgeBoundary(curr_state, step_delta));
            motor_sensor_hall_state.estimated_angle =
                motor_sensor_hall_state.edge_angle;
            motor_sensor_hall_state.edge_valid = 1U;
        }
#if HALL_FEATURE_MISSED_EDGE_TOLERANCE
        else
        {
            /* 丢边时保留速度估算，但角度回退到扇区中心。 */
            motor_sensor_hall_state.edge_angle     = motor_sensor_hall_state.angle;
            motor_sensor_hall_state.estimated_angle = motor_sensor_hall_state.angle;
            motor_sensor_hall_state.edge_valid      = 0U;
            Hall_SpeedWindowReset();
        }
#else
        else
        {
            motor_sensor_hall_state.edge_angle     = motor_sensor_hall_state.angle;
            motor_sensor_hall_state.estimated_angle = motor_sensor_hall_state.angle;
            motor_sensor_hall_state.edge_valid      = 0U;
            Hall_SpeedWindowReset();
            Hall_CounterClear();
            s_first_edge = 1U;
            return;
        }
#endif

        /* 第一笔有效边沿仅用于建立 dt 基准。 */
        if (s_first_edge != 0U)
        {
            s_first_edge = 0U;
            motor_sensor_hall_state.last_edge_cnt = now_cnt;
            Hall_CounterClear();
            return;
        }

#if HALL_FEATURE_TIMEOUT_DETECTION
        if (ovf_count >= HALL_OVERFLOW_THRESHOLD)
        {
            motor_sensor_hall_state.speed       = 0.0f;
            motor_sensor_hall_state.edge_speed  = 0.0f;
            motor_sensor_hall_state.speed_valid  = 0U;
            motor_sensor_hall_state.edge_valid   = 0U;
            Hall_SpeedWindowReset();
            s_first_edge = 1U;
            Hall_CounterClear();
#if HALL_FEATURE_DEBUG_OBSERVE
            motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_OVERFLOW;
#endif
            return;
        }
#endif /* HALL_FEATURE_TIMEOUT_DETECTION */

        /* 用边沿间隔和跨越角度计算转速。 */
        {
            float dt           = Hall_TicksToSeconds(now_cnt);
            float travel_angle = Hall_TravelAngle(step_delta);

#if HALL_FEATURE_DEBUG_OBSERVE
            motor_hall_diff_cnt_dbg = now_cnt;
#endif

            if ((dt > 0.0f) && (travel_angle > 0.0f))
            {
                const float two_pi = HALL_TWO_PI;
                float dt_min = travel_angle * 60.0f
                               / (two_pi * HALL_MAX_RPM_VALID * NUM_POLE_PAIRS);
                float dt_max = travel_angle * 60.0f
                               / (two_pi * HALL_MIN_RPM_VALID * NUM_POLE_PAIRS);

                if ((dt >= dt_min) && (dt <= dt_max))
                {
                    float selected_speed;
                    uint8_t selected_valid;
                    float we_rad_s = dir_sign * (travel_angle / dt);
                    float rpm_meas = we_rad_s
                                     * (60.0f / (two_pi * NUM_POLE_PAIRS));

#if HALL_FEATURE_SPEED_FILTER
                    motor_sensor_hall_state.edge_speed =
                        HALL_SPEED_FILTER_ALPHA * motor_sensor_hall_state.edge_speed
                        + (1.0f - HALL_SPEED_FILTER_ALPHA) * rpm_meas;
#else
                    motor_sensor_hall_state.edge_speed = rpm_meas;
#endif

                    motor_sensor_hall_state.last_edge_cnt = now_cnt;

                    if (is_adjacent != 0U)
                    {
                        Hall_SpeedWindowPush(now_cnt, step_delta);
                        Hall_SpeedWindowEvaluate();
                    }

                    if (motor_sensor_hall_state.window_speed_valid != 0U)
                    {
                        selected_speed = motor_sensor_hall_state.window_speed;
                        selected_valid = 1U;
                    }
                    else
                    {
                        selected_speed = motor_sensor_hall_state.edge_speed;
                        selected_valid = 1U;
                    }

#if HALL_FEATURE_OSCILLATION_DETECT
                    if ((motor_sensor_hall_state.oscillation_flag != 0U)
                        // && (fabsf(motor_sensor_hall_state.window_speed)
                        //     <= HALL_OSCILLATION_ZERO_RPM)
                        )
                    {
                        selected_speed = 0.0f;
                        selected_valid = 0U;
#if HALL_FEATURE_DEBUG_OBSERVE
                        motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_OSCILLATION;
#endif
                    }
#endif

                    motor_sensor_hall_state.speed = selected_speed;
                    motor_sensor_hall_state.speed_valid = selected_valid;
                }
                else if (dt > dt_max)
                {
                    motor_sensor_hall_state.speed       = 0.0f;
                    motor_sensor_hall_state.edge_speed  = 0.0f;
                    motor_sensor_hall_state.speed_valid  = 0U;
                    motor_sensor_hall_state.edge_valid   = 0U;
                    Hall_SpeedWindowReset();
#if HALL_FEATURE_DEBUG_OBSERVE
                    motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_LOW_SPEED;
#endif
                }
                else
                {
                    /* 速度过高时丢弃本次样本，保留上一笔有效速度。 */
                }
            }
            else
            {
                motor_sensor_hall_state.speed       = 0.0f;
                motor_sensor_hall_state.edge_speed  = 0.0f;
                motor_sensor_hall_state.speed_valid  = 0U;
                motor_sensor_hall_state.edge_valid   = 0U;
                Hall_SpeedWindowReset();
#if HALL_FEATURE_DEBUG_OBSERVE
                motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_INVALID_DT;
#endif
            }
        }

        /* 边沿处理完成后清零计数器，重新开始计时。 */
        Hall_CounterClear();

        if (motor_sensor_hall_state.edge_valid != 0U)
        {
            int8_t edge_idx = Hall_GetIndex(curr_state);
            if (edge_idx >= 0)
            {
                uint8_t idx = (uint8_t)edge_idx;
                float raw_error = Hall_SignedAngleDiff(motor_sensor_hall_state.edge_angle,
                                                       motor_foc_struct.motor_position.angle);
                float filtered_error = raw_error;

                if (errorAngleHallAndElectricalValid[idx] != 0U)
                {
                    float aligned_error = Hall_AlignAngleToRef(raw_error,
                                                               errorAngleHallAndElectricalFiltered[idx]);
                    filtered_error = HALL_EDGE_ERROR_FILTER_ALPHA
                                   * errorAngleHallAndElectricalFiltered[idx]
                                   + (1.0f - HALL_EDGE_ERROR_FILTER_ALPHA) * aligned_error;
                    filtered_error = Hall_WrapPi(filtered_error);
                }
                else
                {
                    errorAngleHallAndElectricalValid[idx] = 1U;
                }

                errorAngleHallAndElectrical[idx] = raw_error;
                errorAngleHallAndElectricalFiltered[idx] = filtered_error;
                errorAngleHallAndElectricalUpdateCount[idx]++;
            }
        }
    }
}

    /* ===== 5. 周期估算（FOC 周期侧） ===== */

void Motor_Hall_Transducer(MotorEstimator *estimator)
{
    uint16_t hall_state  = motor_sensor_hall_state.last_hall_state;
    float    speed_rpm   = motor_sensor_hall_state.speed;
    uint8_t  edge_valid  = motor_sensor_hall_state.edge_valid;
    float    edge_angle  = motor_sensor_hall_state.edge_angle;
    float    center      = motor_sensor_hall_state.angle;
    uint8_t  oscillation_confirmed = 0U;

    float    estimated;
    float    sector_start;
    float    sector_end;

#if HALL_FEATURE_TIMEOUT_DETECTION
    uint8_t  ovf_count     = Hall_CounterOverflowCount();
    uint32_t now_cnt       = Hall_CounterGet();
    float    dt_since_edge = Hall_TicksToSeconds(now_cnt);
#endif

#if HALL_FEATURE_OSCILLATION_DETECT
    if (motor_sensor_hall_state.oscillation_flag != 0U)
    {
        if (s_oscillation_cycle_count < 0xFFU)
        {
            s_oscillation_cycle_count++;
        }
    }
    else
    {
        s_oscillation_cycle_count = 0U;
    }

    if (s_oscillation_cycle_count >= HALL_OSCILLATION_CONFIRM_CYCLES)
    {
        oscillation_confirmed = 1U;
        motor_sensor_hall_state.speed = 0.0f;
        motor_sensor_hall_state.speed_valid = 0U;
#if HALL_FEATURE_DEBUG_OBSERVE
        motor_hall_reset_reason_dbg = (uint8_t)HALL_RESET_OSCILLATION;
#endif
    }
#endif

    /* 先确定当前扇区边界。 */
    if (Hall_GetSectorBounds(hall_state, &sector_start, &sector_end) == 0U)
    {
        /* 当前状态无效时退回中心角。 */
        estimated = Hall_Wrap2Pi(center);
    }
#if HALL_FEATURE_TIMEOUT_DETECTION
    else if ((ovf_count >= HALL_OVERFLOW_THRESHOLD)
             || (dt_since_edge > HALL_STOP_TIMEOUT_SEC))
    {
        /* 超时后清零速度，并回退到当前扇区中心角。 */
        motor_sensor_hall_state.speed       = 0.0f;
        motor_sensor_hall_state.speed_valid  = 0U;
        estimated = center;

#if HALL_FEATURE_DEBUG_OBSERVE
        motor_hall_reset_reason_dbg  = (uint8_t)HALL_RESET_PERIODIC_TIMEOUT;
        motor_hall_overflow_count_dbg = ovf_count;
#endif
    }
#endif /* HALL_FEATURE_TIMEOUT_DETECTION */
    else if (oscillation_confirmed != 0U)
    {
        /* 连续多个周期都表现为抖动时，认为当前无有效转动。 */
        estimated = center;
        speed_rpm = 0.0f;
    }
    else if ((edge_valid != 0U)
             && (motor_sensor_hall_state.speed_valid != 0U)
#if HALL_FEATURE_LOW_SPEED_FALLBACK
             && (fabsf(speed_rpm) >= HALL_INTERP_MIN_RPM)
#endif
            )
    {
            /* 有效速度和边界角存在时，在扇区内推进连续角度。 */
#if HALL_FEATURE_TIMEOUT_DETECTION
        float we = speed_rpm * (HALL_TWO_PI / 60.0f) * NUM_POLE_PAIRS;
        estimated = edge_angle + we * dt_since_edge;
#else
        {
            uint32_t cnt = Hall_CounterGet();
            float dt = Hall_TicksToSeconds(cnt);
            float we = speed_rpm * (HALL_TWO_PI / 60.0f) * NUM_POLE_PAIRS;
            estimated = edge_angle + we * dt;
        }
#endif
        estimated = Hall_Wrap2Pi(estimated);
        estimated = Hall_ClampToSector(estimated, sector_start, sector_end);
    }
    else
    {
        /* 低速或参考无效时使用扇区中心角。 */
        estimated = center;
    }

    motor_sensor_hall_state.estimated_angle = estimated;

    /* 输出电角度。 */
    estimator->angle = motor_sensor_hall_state.estimated_angle;
    Mat_AngleWraps(&estimator->angle);

    /* 输出速度，并做简单平滑。 */
    {
        float filtered_speed = estimator->speed;

#if HALL_FEATURE_TIMEOUT_DETECTION
        if ((ovf_count >= HALL_OVERFLOW_THRESHOLD)
            || (dt_since_edge > HALL_STOP_TIMEOUT_SEC))
        {
            filtered_speed = 0.0f;
        }
        else
#endif
        if (oscillation_confirmed != 0U)
        {
            filtered_speed = 0.0f;
        }
        else
        if (motor_sensor_hall_state.speed_valid != 0U)
        {
            filtered_speed = HALL_OUTPUT_FILTER_ALPHA * estimator->speed
                             + (1.0f - HALL_OUTPUT_FILTER_ALPHA) * speed_rpm;
        }

        estimator->speed = filtered_speed;
    }
}
