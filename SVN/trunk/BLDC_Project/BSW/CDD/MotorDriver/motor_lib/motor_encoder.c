#include "motor_encoder.h"
#include "typedef.h"
#include "device_header.h"
#include "motor_config.h"
#include "motor_foc.h"
#include "motor_config.h"
#include "motor_foc.h"
#include "math.h"
#include <string.h>
#include "IoHwAb_Counter.h"
#include "NvM.h"

volatile MOTOR_SENSOR_ENCODER motor_sensor_encoder_state;

/* 运行时编码器电角度偏置（rad）：
 * - 初始化为配置宏 ENCODER_ELEC_ANGLE_OFFSET；
 * - 可在开环阶段通过校准逻辑重新赋值；
 * - 供电角外推时使用，替代原有宏常量。 */
float g_encoder_elec_angle_offset_cal = (float)ENCODER_ELEC_ANGLE_OFFSET;

/* 以 π 为单位的偏置系数：g_encoder_elec_angle_offset_cal = g_encoder_elec_angle_offset_pi * π。
 * 便于在调试器中直接看到 “N·π” 的 N。 */
float g_encoder_elec_angle_offset_pi = (float)ENCODER_ELEC_ANGLE_OFFSET / (float)M_PI;

/* 使用 EncoderStrokeId Block 存储 Encoder 行程位置 */
extern sint32 NvMEncoderStroke[2];



// CAN中断接收编码器信号,
typedef struct
{
    int16_t angle;      // 16bit 有符号计数，单位：LSB（-32768..32767 对应 -180..+180deg）
    uint32_t timestamp; // 与 FTU 计数相关的 tick 差
} MotorEncoderData;

// 运行节奏（根据你的实际系统：FOC 20kHz=50us，编码器 CAN 200us/帧）
#define EST_LOOP_PERIOD_SEC (0.00005f) // 50us 主循环
#define ENC_CAN_PERIOD_SEC (0.00020f)  // 200us 编码器帧周期

/* 50us 对应的 FTU tick 数：用于在非 CAN 到来周期内用固定步长推进 curtimestamp。 */
#define ENC_FOC_PERIOD_TICKS ((uint32_t)((EST_LOOP_PERIOD_SEC / FTU_SECONDS_PER_TICK) + 0.5f))

// 通讯预估为150us
#define TRANSMISSION_DELAY (0.00015f / FTU_SECONDS_PER_TICK)
// 注：当前工程 FTU1 tick=1/8MHz=1.25e-7s（见 FTU_SE)ONDS_PER_TICK）
#define ENCODER_FULL_SCALE 65536u
#define ENCODER_SECTORS 3u // 一圈机械角包含的电角周期数，通常等于 NUM_POLE_PAIRS
#define ENCODER_SECTOR_SIZE (ENCODER_FULL_SCALE / ENCODER_SECTORS)
#define MOTOR_DIRECTION_FORWARD 1
#define MOTOR_DIRECTION_REVERSE -1

// 角度与滤波工具
#ifndef TWO_PI
#define TWO_PI (2.0f * (float)M_PI)
#endif
#define ENC_LSB_TO_RAD (TWO_PI / 65536.0f) // 机械角每 LSB 的弧度

static inline float wrap_0_2pi(float a)
{
    while (a >= TWO_PI)
        a -= TWO_PI;
    while (a < 0.0f)
        a += TWO_PI;
    return a;
}

typedef struct
{
    float theta_min_elec_rad;    // 电角阈值，小于此认为噪声
    uint32_t dt_min_ticks;       // 最小有效时间间隔（tick）
    uint8_t k_confirm;           // 方向切换确认次数
    float alpha_speed;           // 速度低通系数（0..1）
    float rpm_stop_thresh;       // 判停阈值 rpm
    float rpm_dir_bypass_thresh; // 方向确认快速通道阈值（rpm），超过即一次通过
} EncoderFilterCfg;

typedef struct
{
    int8_t direction;        // -1/0/1
    uint8_t dir_conf_cnt;    // 确认计数
    float rpm;               // 低通后的 rpm
    float elec_inc_per_tick; // rad / tick（滤波后/确认后）
} EncoderFilterState;

// NUM_POLE_PAIRS=3、rpm_min=40、dt=200us，可得 theta_min≈0.002513rad
#define ENC_RPM_MIN_MECH (40.0f) // 期望最低可识别机械转速（rpm）
#define ENC_THETA_MIN_ELEC_RAD (TWO_PI * (float)NUM_POLE_PAIRS * (ENC_RPM_MIN_MECH / 60.0f) * ENC_CAN_PERIOD_SEC)

#define ENC_DT_MIN_FRACTION_OF_CAN (0.2f)
#define ENC_DT_MIN_TICKS ((uint32_t)((ENC_CAN_PERIOD_SEC * ENC_DT_MIN_FRACTION_OF_CAN) / FTU_SECONDS_PER_TICK))

// 速度一阶低通（alpha=exp(-dt/τ)），dt≈ENC_CAN_PERIOD_SEC
// 若 τ=10ms、dt=200us，则 alpha≈exp(-0.0002/0.01)≈0.9802。此处直接填入近似值，保留公式注释。
#define ENC_SPEED_LPF_TAU_SEC (0.010f)
// alpha ≈ exp(-ENC_CAN_PERIOD_SEC/ENC_SPEED_LPF_TAU_SEC) 在 dt=200us、τ=10ms 下约为 0.9802
#define ENC_ALPHA_SPEED (0.985f)

// 4) 判停阈值（rpm）：通常取“期望最小识别转速”的一半形成迟滞
#define ENC_RPM_STOP_THRESH (0.5f * ENC_RPM_MIN_MECH) // 20rpm 迟滞

// 5) 方向确认快速通道：当速度较大时（例如为 rpm_min 的 3 倍），一次通过方向确认
#define ENC_RPM_DIR_BYPASS_MULT (3.0f)
#define ENC_RPM_DIR_BYPASS_THRESH (ENC_RPM_DIR_BYPASS_MULT * ENC_RPM_MIN_MECH)

static const EncoderFilterCfg kEncCfg = {
    .theta_min_elec_rad = ENC_THETA_MIN_ELEC_RAD,
    .dt_min_ticks = ENC_DT_MIN_TICKS,
    .k_confirm = 3,
    .alpha_speed = ENC_ALPHA_SPEED,
    .rpm_stop_thresh = ENC_RPM_STOP_THRESH,
    .rpm_dir_bypass_thresh = ENC_RPM_DIR_BYPASS_THRESH,
};
static EncoderFilterState gEncState = {0};
static int16_t s_last_raw_cnt = 0;

static inline void
Encoder_FilterUpdateFromDelta(float dtheta_elec, uint32_t dt_ticks, const EncoderFilterCfg *cfg, EncoderFilterState *st)
{
    if (dt_ticks < cfg->dt_min_ticks)
        return; // 过密采样，忽略

    // if (fabsf(dtheta_elec) < cfg->theta_min_elec_rad)
    // {
    //     // 角度太小，视为噪声：对速度与角增量做指数衰减，逐步趋近 0
    //     st->rpm *= cfg->alpha_speed;
    //     st->elec_inc_per_tick *= cfg->alpha_speed;
    //     if (fabsf(st->rpm) < cfg->rpm_stop_thresh)
    //     {
    //         st->rpm = 0.0f;
    //         st->elec_inc_per_tick = 0.0f;
    //         st->direction = 0;
    //     }
    //     return;p
    // }

    // 先计算瞬时速度，用于“高速一次通过”策略
    float elec_inc_per_tick = dtheta_elec / (float)dt_ticks;         // rad/tick
    float elec_rad_per_s = elec_inc_per_tick / FTU_SECONDS_PER_TICK; // rad/s
    float mech_rps = elec_rad_per_s / TWO_PI / (float)NUM_POLE_PAIRS;
    float rpm_inst = mech_rps * 60.0f;

    // int8_t observed_dir = (dtheta_elec > 0.0f) ? 1 : -1;
    // if (fabsf(rpm_inst) >= cfg->rpm_dir_bypass_thresh)
    // {
    //     // 高速：方向切换一次确认
    //     st->direction = observed_dir;
    //     st->dir_conf_cnt = cfg->k_confirm;
    // }
    // else
    // {
    //     // 低速：按 K 次确认抑制抖动
    //     if (observed_dir == st->direction)
    //     {
    //         if (st->dir_conf_cnt < cfg->k_confirm)
    //             st->dir_conf_cnt++;
    //     }
    //     else
    //     {
    //         if (st->dir_conf_cnt > 0)
    //         {
    //             st->dir_conf_cnt--; // 抵消一次
    //         }
    //         else
    //         {
    //             st->direction = observed_dir; // 真正切换
    //             st->dir_conf_cnt = 1;
    //         }
    //     }
    // }

    st->rpm = cfg->alpha_speed * st->rpm + (1.0f - cfg->alpha_speed) * rpm_inst;
    if (fabsf(st->rpm) < cfg->rpm_stop_thresh)
        st->direction = 0;

    st->elec_inc_per_tick = elec_inc_per_tick;
}

#define ENCODER_DATA_BUF_SIZE 16 // 必须使用2的幂
#define ENCODER_DATA_BUF_P0S_MASK (ENCODER_DATA_BUF_SIZE - 1)
MotorEncoderData encoder_data_buf[ENCODER_DATA_BUF_SIZE];
volatile uint8_t encoder_data_pos = 0;
volatile _Bool encoder_data_ready = 0;

#if (MOTOR_ENCODER_SPEED_USE_BUFFER_WINDOW)
static inline uint8_t Encoder_ComputeDeltaFromBuffer(float *dtheta_elec_out, uint32_t *dt_ticks_out)
{
    /*
     * 使用环形缓冲最近一整段数据（最多 ENCODER_DATA_BUF_SIZE 帧）计算平均速度：
     * - dt 使用“当前帧携带的 timestamp（与上一帧的间隔）”累加；
     * - dcnt 使用 int16 差分（天然跨界鲁棒）逐段累加；
     * - 返回有效 pair 数（至少 1 才能形成速度）。
     */
    uint8_t latest = (uint8_t)((encoder_data_pos - 1u) & ENCODER_DATA_BUF_P0S_MASK);

    int32_t total_dcnt = 0;
    uint32_t total_dt = 0u;
    uint8_t pairs = 0u;

    uint8_t idx_cur = latest;
    int16_t raw_cur = encoder_data_buf[idx_cur].angle;

    /* 最多累加 ENCODER_DATA_BUF_SIZE-1 个间隔 */
    for (uint8_t i = 0u; i < (ENCODER_DATA_BUF_SIZE - 1u); i++)
    {
        uint32_t dt = encoder_data_buf[idx_cur].timestamp;
        if (dt == 0u)
        {
            break; /* 当前槽位未初始化或无效 */
        }

        uint8_t idx_prev = (uint8_t)((idx_cur - 1u) & ENCODER_DATA_BUF_P0S_MASK);
        if (encoder_data_buf[idx_prev].timestamp == 0u)
        {
            break; /* 上一帧槽位未初始化，无法再往前扩展窗口 */
        }

        int16_t raw_prev = encoder_data_buf[idx_prev].angle;

        /* 该 dt 对应 (idx_prev -> idx_cur) 这一段 */
        int16_t dcnt = (int16_t)(raw_cur - raw_prev);
        total_dcnt += (int32_t)dcnt;
        total_dt += dt;
        pairs++;

        idx_cur = idx_prev;
        raw_cur = raw_prev;
    }

    if (pairs == 0u)
    {
        *dtheta_elec_out = 0.0f;
        *dt_ticks_out = 0u;
        return 0u;
    }

    float dtheta_mech = (float)total_dcnt * ENC_LSB_TO_RAD;
    *dtheta_elec_out = dtheta_mech * (float)NUM_POLE_PAIRS;
    *dt_ticks_out = total_dt;
    return pairs;
}
#endif

// TODO
extern uint16_t Com_GetMTEncoderAngleData(void);
// int16_t encoderCanAngle;
// uint32_t encoderCanTimestamp;

/* Debug / timing state */
int16_t encoderDCnt =0;
// uint32_t curtimestampView =0;
// uint8_t curtimestampViewCnt =0;

/* 以固定 50us 步长推进的“软件 curtimestamp”（单位：tick，等价于 IoHwAb_Counter_GetCnt()）。
 * 每次 CAN 到来仅对齐一次基准；其余 FOC 周期固定 +50us tick 推进。 */
static uint32_t s_curtimestamp_ticks_x1000 = 0u;
void Motor_Encoder_CAN_IRQ(void)
{
    uint16_t Motor_0_Encoder = Com_GetMTEncoderAngleData(); // 此处读取到了CAN信号
    uint32_t timestamp = IoHwAb_Counter_GetCnt();
    IoHwAb_Counter_Clear();

    encoder_data_buf[encoder_data_pos].angle = (int16_t)Motor_0_Encoder;
    encoder_data_buf[encoder_data_pos].timestamp = timestamp;
    encoder_data_pos = (encoder_data_pos + 1) & (ENCODER_DATA_BUF_SIZE - 1);

    encoder_data_ready = 1;

    // // For debug
    // encoderCanAngle = (int16_t)Motor_0_Encoder;
    // encoderCanTimestamp = timestamp;
}

// TODO:
// 初始化：在驱动 init 或首次收到有效帧前调用
void Motor_Encoder_Init(void)
{
    encoder_data_pos = 0;
    encoder_data_ready = 0;
    s_last_raw_cnt = 0;
    memset(&gEncState, 0, sizeof(gEncState));

    // curtimestampView = 0u;
    // curtimestampViewCnt = 0u;
    s_curtimestamp_ticks_x1000 = 0u;

    motor_sensor_encoder_state.mechanical_angle = 0;
    motor_sensor_encoder_state.mechanical_angle_transformed = 0.0f;
    motor_sensor_encoder_state.electrical_angle = 0.0f;
    motor_sensor_encoder_state.electrical_angle_estimated = 0.0f;
    motor_sensor_encoder_state.last_electrical_angle = 0.0f;
    motor_sensor_encoder_state.electrical_area = 0;
    motor_sensor_encoder_state.last_electrical_area = 0;
    motor_sensor_encoder_state.electrical_angle_inc_per_tick = 0.0f;
    motor_sensor_encoder_state.speed = 0.0f;
    motor_sensor_encoder_state.direction = 0;
}

/* 在 NVM 初始化完成后调用，
 * 从 NvMEncoderOffset[0] 读取“弧度”偏置值，
 * 并同步计算对应的 π 系数。 */
void Motor_Encoder_LoadOffsetFromNvM(void)
{
    if (NVM_IDLE == NVM_GetStatus())
    {
        if (NVM_OK == NVM_ReadBlockData(EncoderOffsetId))
        {
            float offset_rad = NvMEncoderOffset[0];

            /* 简单范围限制，避免异常值覆盖（例如未初始化为 0xFF 时的巨大数） */
            if ((offset_rad > -10.0f * (float)M_PI) && (offset_rad < 10.0f * (float)M_PI))
            {
                g_encoder_elec_angle_offset_cal = offset_rad;
                g_encoder_elec_angle_offset_pi  = offset_rad / (float)M_PI;
            }
        }
    }
}

/* 从 NVM 读取 Encoder 行程位置（使用 EncoderStrokeId Block）：
 * - NvMEncoderStroke[0] 保存行程格号（每圈18格）；
 * - 若读到的值在合理范围内，则用作当前行程位置。 */
void Motor_Encoder_LoadStrokeFromNvM(void)
{
    if (NVM_IDLE == NVM_GetStatus())
    {
        if (NVM_OK == NVM_ReadBlockData(EncoderStrokeId))
        {
            sint32 pos = NvMEncoderStroke[0];

            /* 合理范围：行程格号约在 -2000..2000 之间，超出视为无效 */
            if ((pos > -2000) && (pos < 2000))
            {
                Motor_Encoder_SetStrokeSector((int16_t)pos);
            }
        }
    }
}

/* 将当前 Encoder 行程位置保存到 NVM：
 * - 使用 EncoderStrokeId Block；
 * - NvMEncoderStroke[0] 为当前行程格号，NvMEncoderStroke[1] 预留。 */
void Motor_Encoder_SaveStrokeToNvM(void)
{
    if ((NVM_IDLE == NVM_GetStatus()) && (FALSE == NVM_GetIsReachAge()))
    {
        int16_t sector = Motor_Encoder_GetStrokeSector();
        NvMEncoderStroke[0] = (sint32)sector;
        NvMEncoderStroke[1] = 0;

        (void)NVM_WriteBlockData(EncoderStrokeId);
    }
}
void Motor_Encoder_Transducer(MotorEstimator *estimator)
{
    uint8_t encoder_data_pos_tmp =0;
    // FOR CURRENT BUG TEMP FIX
    uint32_t curtimestamp =0;
    {
        // if (encoder_data_buf[encoder_data_pos_tmp].timestamp > (200 + 10)* 8
        //     || encoder_data_buf[encoder_data_pos_tmp].timestamp < (200 - 10)* 8)
        // {
        //     curtimestamp = IoHwAb_Counter_GetCnt() + (uint16_t)encoder_data_buf[encoder_data_pos_tmp].timestamp - 200;
        // }
        // else
        // {
        // }
        /* 4:1（FOC 50us / CAN 200us）：
     * - 仅在 CAN 中断后的首次（encoder_data_ready==1）读取计数器并对齐基准；
     * - 其余周期用固定 +50us tick 推进。 */
        // if (encoder_data_ready)
        // {
        //     curtimestampViewCnt = 0u;

        //     /* 若 CAN 帧间隔 dt 异常，则不使用本次计数器读数对齐基准，沿用上一次的 s_curtimestamp_ticks。 */
        //     if (encoder_data_buf[encoder_data_pos_tmp].timestamp <= (200u + 5u) * 8u &&
        //         encoder_data_buf[encoder_data_pos_tmp].timestamp >= (200u - 5u) * 8u)
        //     {
        //         const uint32_t curtimestamp_raw = IoHwAb_Counter_GetCnt();
        //         const uint32_t curtimestamp_raw_x1000 = curtimestamp_raw * 1000u;

        //         static volatile uint32_t curtimestamp_raw_array[1000];
        //         static uint16_t curtimestamp_raw_index =0;
        //         curtimestamp_raw_array[curtimestamp_raw_index++] = curtimestamp_raw;
        //         curtimestamp_raw_index %=1000;
        //         volatile uint8_t i =0;
        //         if(curtimestamp_raw < 150 && s_curtimestamp_ticks_x1000 > (250 * 1000u))
        //         {
        //             i =0;
        //             do
        //             {
        //                 i++;
        //             }
        //             while(!i);
        //         }
        //         else
        //         {
        //             if(i == 1)
        //             {
        //                 i =0;
        //             }
        //         }
        //         /* 仅在 CAN 到来后的首次做一次滤波（IIR）：
        //          * y(k) = 0.999*y(k-1) + 0.001*x(k)
        //          * 为保留细节，y/x 使用 tick*1000 的定点数。
        //          * 首次（y=0）直接用 raw 初始化，避免冷启动被拉低。 */
        //         if (s_curtimestamp_ticks_x1000 == 0u)
        //         {
        //             s_curtimestamp_ticks_x1000 = curtimestamp_raw_x1000;
        //         }
        //         else
        //         {
        //             s_curtimestamp_ticks_x1000 =
        //                 (s_curtimestamp_ticks_x1000 * 999u + curtimestamp_raw_x1000 + 500u) / 1000u;
        //         }
        //     }
        // }
        // else
        // {
        //     // /* 非 CAN 到来周期：固定步长推进（50us）。 */
        //     // s_curtimestamp_ticks += ENC_FOC_PERIOD_TICKS;
        //     curtimestampViewCnt++;
        // }

        // {
        //     /* 单纯放大：用 x1000 做滤波，使用时再缩回 tick。 */
        //     const uint32_t base_ticks = (s_curtimestamp_ticks_x1000 + 500u) / 1000u;
        //     curtimestamp = base_ticks + (uint32_t)curtimestampViewCnt * (uint32_t)ENC_FOC_PERIOD_TICKS;
        //     curtimestampView = base_ticks;
        // }
    }

    curtimestamp = IoHwAb_Counter_GetCnt();
    if (encoder_data_ready)
    {
        encoder_data_pos_tmp = (encoder_data_pos - 1) & ENCODER_DATA_BUF_P0S_MASK;
        if(encoder_data_buf[encoder_data_pos_tmp].timestamp > (200 + 5)* 8
            || encoder_data_buf[encoder_data_pos_tmp].timestamp < (200 - 5)* 8)
        {
            encoder_data_buf[encoder_data_pos_tmp].timestamp = 200 * 8;
        }
        encoder_data_ready = 0;
        if (encoder_data_buf[encoder_data_pos_tmp].timestamp == 0)
        {
            return;
        }

        // 1) 读取原始计数（int16_t），并保存到对外状态
        int16_t raw_cnt = (int16_t)encoder_data_buf[encoder_data_pos_tmp].angle; // [-32768,32767]
        motor_sensor_encoder_state.mechanical_angle = raw_cnt;

        // 2) 机械角（弧度）：提供 0..2π 显示用
        float mech_rad_signed = (float)raw_cnt * ENC_LSB_TO_RAD; // [-π, π)
        float mech_rad_0_2pi = wrap_0_2pi(mech_rad_signed);
        motor_sensor_encoder_state.mechanical_angle_transformed = mech_rad_0_2pi;

        // 3) 电角（0..2π）
        motor_sensor_encoder_state.last_electrical_angle = motor_sensor_encoder_state.electrical_angle;
        float elec_rad = mech_rad_signed * (float)NUM_POLE_PAIRS;
        elec_rad = fmodf(elec_rad, TWO_PI);
        if (elec_rad < 0.0f)
            elec_rad += TWO_PI;
        motor_sensor_encoder_state.electrical_angle = elec_rad;

        // 4) 计算电角增量/时间间隔：支持宏切换（用于对比）
        int16_t dcnt_latest = (int16_t)(raw_cnt - s_last_raw_cnt);
        encoderDCnt = dcnt_latest; /* 保留调试：最新两帧差分 */
        s_last_raw_cnt = raw_cnt;

        float dtheta_elec_input = 0.0f;
        uint32_t dt_ticks_input = 0u;

    #if (MOTOR_ENCODER_SPEED_USE_BUFFER_WINDOW)
        (void)Encoder_ComputeDeltaFromBuffer(&dtheta_elec_input, &dt_ticks_input);
    #else
        {
            float dtheta_mech = (float)dcnt_latest * ENC_LSB_TO_RAD;
            dtheta_elec_input = dtheta_mech * (float)NUM_POLE_PAIRS;
            dt_ticks_input = encoder_data_buf[encoder_data_pos_tmp].timestamp;
        }
    #endif

        // 5) 过滤/确认/速度计算
        Encoder_FilterUpdateFromDelta(dtheta_elec_input,
                          dt_ticks_input,
                          &kEncCfg,
                          &gEncState);

        motor_sensor_encoder_state.direction = gEncState.direction;
        motor_sensor_encoder_state.electrical_angle_inc_per_tick = gEncState.elec_inc_per_tick;
        motor_sensor_encoder_state.speed = gEncState.rpm;
    }

    // 外推估计（保持原公式，仅依赖 curtimestamp 的获取方式变化）
    motor_sensor_encoder_state.electrical_angle_estimated =
        wrap_0_2pi(motor_sensor_encoder_state.electrical_angle
                 + ((float)(curtimestamp + (uint32_t)TRANSMISSION_DELAY)) *
                     motor_sensor_encoder_state.electrical_angle_inc_per_tick +
                   g_encoder_elec_angle_offset_cal);

    estimator->angle = motor_sensor_encoder_state.electrical_angle_estimated;
    estimator->speed = motor_sensor_encoder_state.speed;
}

// TODO
void Motor_Encoder_FTU_TOF_IRQ(void)
{
    motor_sensor_encoder_state.electrical_angle_inc_per_tick = 0.0f; // 重置角速度增量
    motor_sensor_encoder_state.speed = 0.0f;
    motor_sensor_encoder_state.electrical_angle_estimated = motor_sensor_encoder_state.electrical_angle;
}

int16_t Motor_Encoder_GetLatestRawCnt(void)
{
    uint8_t pos = (encoder_data_pos - 1u) & (ENCODER_DATA_BUF_P0S_MASK);
    return encoder_data_buf[pos].angle; /* 原始 int16 计数 */
}


/* 多圈行程计数：将编码器原始计数展开为连续多圈 LSB，并量化为“每圈18份”的粗行程格号。 */

static int16_t s_stroke_last_raw = 0;   /* 上一次原始计数，用于行程展开 */
static int32_t s_stroke_ext_lsb  = 0;   /* 展开后的多圈 LSB 计数 */
static int16_t s_stroke_sector   = 0;   /* 对外暴露的行程格号（每圈18份） */

#define STROKE_SECTOR_PER_REV   18
#define STROKE_LSB_PER_SECTOR   (ENCODER_FULL_SCALE / STROKE_SECTOR_PER_REV) /* 每20°对应的LSB数 */

void Motor_Encoder_StrokeUpdate_1msTask(void)
{
    /* 1) 拿最新原始编码器值（此处约定为 -32768..32767，对应 -180..+180deg） */
    int16_t raw = Motor_Encoder_GetLatestRawCnt();

    /* 2) 直接做差分并无脑累加，利用 int16_t 差分天然跨 0deg 鲁棒 */
    int16_t d = (int16_t)(raw - s_stroke_last_raw);
    s_stroke_ext_lsb += (int32_t)(-d); // Readme: 注意由于与APP层方向相反,此处取反
    s_stroke_last_raw = raw;

    /* 3) 将连续 LSB 计数量化为“每圈18份”的格号。这里不做钳位，由上层决定是否限制行程到56圈。 */
    if (STROKE_LSB_PER_SECTOR > 0)
    {
        int32_t sector = s_stroke_ext_lsb / (int32_t)STROKE_LSB_PER_SECTOR;
        s_stroke_sector = (int16_t)sector;
    }
}

int16_t Motor_Encoder_GetStrokeSector(void)
{
    /* 行程格号：每圈18格，上层可认为一圈=18，56圈=56*18=1008 */
    return s_stroke_sector;
}

void Motor_Encoder_SetStrokeSector(int16_t sector)
{
    /*
     * 行程格号设定：需要同步内部多圈计数状态，
     * 否则 1ms 任务下一次积分会把手动设定的值覆盖掉。
     *
     * 做法：
     *  - 以当前最新原始计数作为新的基准（s_stroke_last_raw）；
     *  - 根据期望行程格号反推多圈 LSB 计数：sector * STROKE_LSB_PER_SECTOR；
     *  - s_stroke_sector 直接等于期望值，保证对外一致。
     */
    int16_t raw = Motor_Encoder_GetLatestRawCnt();
    s_stroke_last_raw = raw;
    s_stroke_ext_lsb  = (int32_t)sector * (int32_t)STROKE_LSB_PER_SECTOR;
}

// /* 位置计数内部状态：基于机械角穿越 0 点计圈（纯整数实现） */
// static int16_t s_mech_turn_count = 0;   /* 圈数计数 */
// static int8_t s_last_zone = 0;          /* -1/0/1，见下方说明 */
// static int16_t s_last_raw_cnt_pc = 0; /* 上次原始计数，用于位置计数 */

// #define POSCOUNTER_HYST_LSB ((int16_t)100)
// #define ENC_HALF_RANGE ((int16_t)16384)
// void PosCounter_1msTask(void)
// {
//     /* 1) 直接从缓冲中拿最新原始计数（-32768..32767） */
//     int16_t raw_cnt = Motor_Encoder_GetLatestRawCnt();

//     /* 2) 三态滞环：
//      *   - 若当前计数 < -POSCOUNTER_HYST_LSB，则 zone 记为 -1；
//      *   - 若当前计数 > +POSCOUNTER_HYST_LSB，则 zone 记为  1；
//      *   - 若在 [-POSCOUNTER_HYST_LSB,+POSCOUNTER_HYST_LSB] 内，则保持上一次的 zone 不变；
//      */
//     int8_t zone = s_last_zone;
//     if (raw_cnt < -POSCOUNTER_HYST_LSB)
//     {
//         zone = -1;
//     }
//     else if (raw_cnt > POSCOUNTER_HYST_LSB)
//     {
//         zone = 1;
//     }
//     /* 否则在滞环区间内，zone 保持不变 */
//     // 如果发生了
//     if (raw_cnt - s_last_raw_cnt_pc > ENC_HALF_RANGE || raw_cnt - s_last_raw_cnt_pc < -ENC_HALF_RANGE)
//     {
//         // 跳过当前
//     }
//     else
//     {
//         /* 3) 检测 -1 -> 1 或 1 -> -1 的跨越 */
//         if ((s_last_zone == -1) && (zone == 1))
//         {
//             s_mech_turn_count++; /* 认为经过 0 点正向一圈 */
//         }
//         else if ((s_last_zone == 1) && (zone == -1))
//         {
//             s_mech_turn_count--; /* 认为经过 0 点反向一圈 */
//         }
//     }

//     s_last_zone       = zone;
//     s_last_raw_cnt_pc = raw_cnt;
// }

// int16_t Motor_Encoder_GetMechTurnCount(void)
// {
//     return s_mech_turn_count;
// }

// void Motor_Encoder_SetMechTurnCount(int16_t turns)
// {
//     s_mech_turn_count = turns;
// }
