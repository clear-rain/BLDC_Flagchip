#include "Spindle_Control.h"

#include <stdbool.h>
#include <stdint.h>
#include "motor_api.h"
#include "motor_encoder.h"

extern int32_t Lib_Linear_6P_Interpo(int32_t Input, int32_t x1, int32_t x2, int32_t x3, int32_t x4,  int32_t x5, int32_t x6, int32_t y1, int32_t y2,  int32_t y3,  int32_t y4,  int32_t y5,  int32_t y6);

#ifndef SPINDLE_CTRL_USE_VOLTAGE
#define SPINDLE_CTRL_USE_VOLTAGE (1)
#endif

#define ABS(x) ((x) >= 0 ? (x) : -(x))

#ifndef MAX_OPEN_SPEED
#define MAX_OPEN_SPEED (2500)
#endif

#ifndef MAX_CLOSE_SPEED
#define MAX_CLOSE_SPEED (2500)
#endif

#ifndef MAX_HALL_CNT
/* 行程格号上限 */
#define MAX_HALL_CNT (15000)
#endif

/* 编码器每圈对应的格数，用于位置->转速换算 */
#ifndef ENCODER_SECTORS_PER_REV
#define ENCODER_SECTORS_PER_REV (18)
#endif

/* 5ms 任务周期（秒），用于位置->转速换算 */
#define SPINDLE_TASK_PERIOD_SEC (0.005f)

/* 计算速度时使用的位置窗口长度（样本数） */
#define SPINDLE_SPEED_WINDOW_SIZE (20U)

static int16_t encoder_position = 0;
static int16_t MotorSpeedRf = 0;
static int16_t RampedMotorSpeedRf = 0;

/* 由编码器位置计算得到的物理转速（单位：rpm，方向同编码器计数方向） */
static float s_encoder_speed_rpm = 0.0f;
static int16_t s_encoder_pos_hist[SPINDLE_SPEED_WINDOW_SIZE];
static uint8_t s_encoder_pos_index = 0U;

typedef struct
{
    float kp;
    float ki;
    float integral;
    float out_min;
    float out_max;
} SpindleSpeedPI_t;

#if SPINDLE_CTRL_USE_VOLTAGE
/* 速度 PI：输出为 vq_ref（单位与 FOC 内部 dq 电压一致，幅值 0~0.95 左右） */
#ifndef SPINDLE_PI_KP
#define SPINDLE_PI_KP (0.0005f)
#endif

#ifndef SPINDLE_PI_KI
#define SPINDLE_PI_KI (0.0003f)
#endif

#ifndef SPINDLE_PI_OUT_MAX
#define SPINDLE_PI_OUT_MAX PI_Q_CURRENT_MAX
#endif

static SpindleSpeedPI_t s_spindle_pi =
{
    SPINDLE_PI_KP,
    SPINDLE_PI_KI,
    0.0f,
    -(SPINDLE_PI_OUT_MAX),
    (SPINDLE_PI_OUT_MAX)
};

static float APPVoltageOffset = 0.0f;
#else
/* 速度 PI：输出为 iq_ref（单位与电机库一致，通常为 A） */
#ifndef SPINDLE_PI_KP
#define SPINDLE_PI_KP (0.002f)   /* 初步建议：P 稍大一些，改善跟随 */
#endif

#ifndef SPINDLE_PI_KI
#define SPINDLE_PI_KI (0.0006f)   /* 初步建议：I 较小，慢慢消除静差 */
#endif

/* PI 输出限幅：与电机库的 MAX_MOTOR_CURRENT 对齐 */
#ifndef SPINDLE_PI_OUT_MAX
#define SPINDLE_PI_OUT_MAX (MAX_MOTOR_CURRENT)
#endif

static SpindleSpeedPI_t s_spindle_pi =
{
    SPINDLE_PI_KP,
    SPINDLE_PI_KI,
    0.0f,
    -(SPINDLE_PI_OUT_MAX),
    (SPINDLE_PI_OUT_MAX)
};

float APPCurrentOffset = 0.0f;
#endif

extern PLG_Action_t PLG_Action_Command;

static void Spindle_ResetSpeedEstimator(int16_t cur_pos);

static void RampSpeed(int16_t SpeedSet, int16_t *SpeedRef, int16_t ACCStep, int16_t DECStep)
{
    if (*SpeedRef == SpeedSet)
    {
        return;
    }

    if (!(*SpeedRef))
    {
        *SpeedRef = (SpeedSet > 0) ? ACCStep : (int16_t)(-ACCStep);
        return;
    }

    int16_t Step;

    if ((*SpeedRef > 0 && SpeedSet < 0) || (*SpeedRef < 0 && SpeedSet > 0))
    {
        Step = (*SpeedRef > 0) ? (int16_t)(-DECStep) : DECStep;
    }
    else if (*SpeedRef == 0)
    {
        Step = (SpeedSet > 0) ? ACCStep : (int16_t)(-ACCStep);
    }
    else
    {
        if (ABS(*SpeedRef) < ABS(SpeedSet))
        {
            Step = (*SpeedRef > 0) ? ACCStep : (int16_t)(-ACCStep);
        }
        else
        {
            Step = (*SpeedRef > 0) ? (int16_t)(-DECStep) : DECStep;
        }
    }

    if (ABS(*SpeedRef) < 800)
    {
        Step = (int16_t)(Step * 10);
    }

    *SpeedRef = (int16_t)(*SpeedRef + Step);

    if ((*SpeedRef > SpeedSet && Step > 0) || (*SpeedRef < SpeedSet && Step < 0))
    {
        *SpeedRef = SpeedSet;
    }
}

static void GetMotorSpeedRf(void)
{

    if (PLG_CMD_OPEN == PLG_Action_Command)
    {
#if MAX_HALL_CNT >1500
        MotorSpeedRf = (int16_t)Lib_Linear_4P_Interpo(encoder_position,
                                                       0,
                                                       50,
                                                       MAX_HALL_CNT-50,
                                                       MAX_HALL_CNT,
                                                       (int32_t)(0.7f * MAX_OPEN_SPEED),
                                                       (int32_t)(1.0f * MAX_OPEN_SPEED),
                                                       (int32_t)(1.0f * MAX_OPEN_SPEED),
                                                       (int32_t)(0.3f * MAX_OPEN_SPEED));
#else
        MotorSpeedRf = (int16_t)Lib_Linear_6P_Interpo(encoder_position,
                                                       0,
                                                       MAX_HALL_CNT / 20,
                                                       (MAX_HALL_CNT << 1) / 5,
                                                       (MAX_HALL_CNT << 2) / 5 - 1,
                                                       (MAX_HALL_CNT << 2) / 5,
                                                       MAX_HALL_CNT,
                                                       (int32_t)(0.7f * MAX_OPEN_SPEED),
                                                       (int32_t)(1.0f * MAX_OPEN_SPEED),
                                                       (int32_t)(1.0f * MAX_OPEN_SPEED),
                                                       (int32_t)(0.7f * MAX_OPEN_SPEED),
                                                       (int32_t)(0.7f * MAX_OPEN_SPEED),
                                                       (int32_t)(0.3f * MAX_OPEN_SPEED));
#endif

        if (encoder_position > MAX_HALL_CNT - 20)
        {
            MotorSpeedRf = 0;
        }
    }
    else if (PLG_CMD_CLOSE == PLG_Action_Command)
    {
#if MAX_HALL_CNT >1500
        MotorSpeedRf = (int16_t)Lib_Linear_4P_Interpo(encoder_position,
                                                       0,
                                                       50,
                                                       MAX_HALL_CNT-50,
                                                       MAX_HALL_CNT,
                                                       (int32_t)(0.3f * MAX_OPEN_SPEED),
                                                       (int32_t)(1.0f * MAX_OPEN_SPEED),
                                                       (int32_t)(1.0f * MAX_OPEN_SPEED),
                                                       (int32_t)(0.7f * MAX_OPEN_SPEED));
#else
        MotorSpeedRf = (int16_t)Lib_Linear_6P_Interpo(encoder_position,
                                                       0,
                                                       MAX_HALL_CNT / 20,
                                                       (MAX_HALL_CNT << 1) / 5,
                                                       (MAX_HALL_CNT << 2) / 5 - 1,
                                                       (MAX_HALL_CNT << 2) / 5,
                                                       MAX_HALL_CNT,
                                                       (int32_t)(0.4f * MAX_CLOSE_SPEED),
                                                       (int32_t)(0.5f * MAX_CLOSE_SPEED),
                                                       (int32_t)(1.0f * MAX_CLOSE_SPEED),
                                                       (int32_t)(1.0f * MAX_CLOSE_SPEED),
                                                       (int32_t)(1.0f * MAX_CLOSE_SPEED),
                                                       (int32_t)(0.7f * MAX_CLOSE_SPEED));

#endif
        if (encoder_position < 20)
        {
            MotorSpeedRf = 0;
        }
        MotorSpeedRf = (int16_t)(-MotorSpeedRf);
    }
    else
    {
        MotorSpeedRf = 0;
    }

    RampSpeed(MotorSpeedRf, &RampedMotorSpeedRf, 20, 50);
}

void Spindle_Control_Init(void)
{
    MotorAPI_Init();
    MotorAPI_StatusSet(false);
#if SPINDLE_CTRL_USE_VOLTAGE
    MotorAPI_ModeSet(MOTOR_CTRL_MODE_VOLTAGE);
    MotorAPI_VoltageSetDQ(0.0f, 0.0f);
#else
    MotorAPI_ModeSet(MOTOR_CTRL_MODE_SPEED);
    MotorAPI_SpeedSetRPM(0.0f);
#endif

    /* 上电优先从 NVM 恢复 Encoder 行程位置；若无有效值则默认 0 */
    Motor_Encoder_LoadStrokeFromNvM();
    encoder_position = 0;
    MotorSpeedRf = 0;
    RampedMotorSpeedRf = 0;
    Spindle_ResetSpeedEstimator(0);

    s_spindle_pi.integral = 0.0f;
}

static float Spindle_SpeedPI_Step(float speed_ref_rpm, float speed_mea_rpm)
{
    float error = speed_ref_rpm - speed_mea_rpm;
    float p_term = s_spindle_pi.kp * error;

    /* 先计算积分候选值（带限幅），再做抗积分饱和处理 */
    {
        float integral_new = s_spindle_pi.integral + s_spindle_pi.ki * error * SPINDLE_TASK_PERIOD_SEC;
        if (integral_new > s_spindle_pi.out_max)
        {
            integral_new = s_spindle_pi.out_max;
        }
        else if (integral_new < s_spindle_pi.out_min)
        {
            integral_new = s_spindle_pi.out_min;
        }

        {
            float out_pre = p_term + integral_new;
            float out = out_pre;

            if (out > s_spindle_pi.out_max)
            {
                out = s_spindle_pi.out_max;
            }
            else if (out < s_spindle_pi.out_min)
            {
                out = s_spindle_pi.out_min;
            }

            /*
             * Anti-windup（条件积分）：
             * 当输出已饱和且误差还在“推着更饱和”时，不更新积分。
             */
            if (!((out_pre > s_spindle_pi.out_max && error > 0.0f) ||
                  (out_pre < s_spindle_pi.out_min && error < 0.0f)))
            {
                s_spindle_pi.integral = integral_new;
            }

            return out;
        }
    }
}

static void Spindle_UpdatePhysicalSpeedFromEncoder(void)
{
    /* 使用循环数组做差，基于一段时间的位置变化计算平均转速 */
    int16_t old_pos = s_encoder_pos_hist[s_encoder_pos_index];
    s_encoder_pos_hist[s_encoder_pos_index] = encoder_position;

    s_encoder_pos_index++;
    if (s_encoder_pos_index >= SPINDLE_SPEED_WINDOW_SIZE)
    {
        s_encoder_pos_index = 0U;
    }

    /* 位置增量 -> 转速，方向由编码器计数方向决定 */
    {
        int32_t delta_pos = (int32_t)encoder_position - (int32_t)old_pos;
        float rev = (float)delta_pos / (float)ENCODER_SECTORS_PER_REV;
        float time_sec = (float)SPINDLE_SPEED_WINDOW_SIZE * SPINDLE_TASK_PERIOD_SEC;
        float rev_per_sec = rev / time_sec;
        s_encoder_speed_rpm = rev_per_sec * 60.0f;
    }
}


static void Spindle_ResetSpeedEstimator(int16_t cur_pos)
{
    uint8_t i;
    for (i = 0U; i < SPINDLE_SPEED_WINDOW_SIZE; i++)
    {
        s_encoder_pos_hist[i] = cur_pos;
    }
    s_encoder_pos_index = 0U;
    s_encoder_speed_rpm = 0.0f;
}

float Spindle_GetPhysicalSpeedRPM(void)
{
    return s_encoder_speed_rpm;
}
void Spindle_Control_Task_5ms(void)
{
    /* 读取编码器行程格号 */
    encoder_position = Motor_Encoder_GetStrokeSector();

    Spindle_UpdatePhysicalSpeedFromEncoder();
    GetMotorSpeedRf();
    // switch (PLG_Action_Command)
    // {
    //     case PLG_CMD_OPEN:
    //         RampedMotorSpeedRf = 1000;
    //         break;
    //     case PLG_CMD_CLOSE:
    //         RampedMotorSpeedRf = -1000;
    //         break;
    //     case PLG_CMD_STOP:
    //     default:
    //         RampedMotorSpeedRf = 0;
    //         break;
    // }

    // 使用编码器反馈 + PI 实现速度闭环，驱动下游 FOC
    static int16_t s_last_ramped_speed = 0;

    /* 启动/换向处理：清积分 + 重置速度估算，避免历史拖尾导致振荡 */
    {
        static int8_t s_last_dir = 0; /* -1/0/1 */
        int8_t cur_dir = (RampedMotorSpeedRf > 0) ? 1 : ((RampedMotorSpeedRf < 0) ? -1 : 0);

        if (cur_dir != s_last_dir)
        {
            if (cur_dir != 0)
            {
                Spindle_ResetSpeedEstimator(encoder_position);
            }
#if SPINDLE_CTRL_USE_VOLTAGE
            s_spindle_pi.integral = cur_dir * (SPINDLE_PI_OUT_MAX * 0.1f);
#else
            s_spindle_pi.integral = cur_dir * 8.0f;
#endif
        }
        s_last_dir = cur_dir;
    }

    if (RampedMotorSpeedRf != 0)
    {
        float speed_ref = (float)RampedMotorSpeedRf;
        float speed_mea = Spindle_GetPhysicalSpeedRPM();
        float pi_out = Spindle_SpeedPI_Step(speed_ref, speed_mea);
#if SPINDLE_CTRL_USE_VOLTAGE
        float ff = (speed_ref > 0.0f) ? APPVoltageOffset : -APPVoltageOffset;
        float vq_ref = pi_out + ff;

        if (vq_ref > s_spindle_pi.out_max)
        {
            vq_ref = s_spindle_pi.out_max;
        }
        else if (vq_ref < s_spindle_pi.out_min)
        {
            vq_ref = s_spindle_pi.out_min;
        }

        /* 电机方向与丝杆方向相反，电压 q 轴取反；d 轴维持 0 */
        MotorAPI_ModeSet(MOTOR_CTRL_MODE_VOLTAGE);
        MotorAPI_VoltageSetDQ(-ABS(vq_ref) / 5.0f, -vq_ref);
        // MotorAPI_VoltageSetDQ(0.0f, -vq_ref);
#else
        float ff = (speed_ref > 0.0f) ? APPCurrentOffset : -APPCurrentOffset;
        float iq_ref = pi_out + ff;

        if (iq_ref > s_spindle_pi.out_max)
        {
            iq_ref = s_spindle_pi.out_max;
        }
        else if (iq_ref < s_spindle_pi.out_min)
        {
            iq_ref = s_spindle_pi.out_min;
        }

        /* 电机方向与丝杆方向相反，电流取反 */
        MotorAPI_ModeSet(MOTOR_CTRL_MODE_CURRENT);
        MotorAPI_CurrentSetDQ(-ABS(speed_mea)/1200, -iq_ref);
#endif

        if (!MotorAPI_StatusGet())
        {
            (void)MotorAPI_StatusSet(true);
        }
    }
    else
    {
        /* 简陋的NVM存储:速度由非零变为零时，认为动作结束，将当前位置写入 NVM */
        if (s_last_ramped_speed != 0)
        {
            Motor_Encoder_SaveStrokeToNvM();
        }

        s_spindle_pi.integral = 0.0f;
#if SPINDLE_CTRL_USE_VOLTAGE
    MotorAPI_VoltageSetDQ(0.0f, 0.0f);
#else
    MotorAPI_CurrentSetDQ(0.0f, 0.0f);
#endif
        if (MotorAPI_StatusGet())
        {
            (void)MotorAPI_StatusSet(false);
        }
    }

    s_last_ramped_speed = RampedMotorSpeedRf;

    // MotorAPI_StatusSet(RampedMotorSpeedRf != 0);
    // MotorAPI_ModeSet(MOTOR_CTRL_MODE_SPEED);

    // // Readme: 由于电机方向与丝杆方向相反，速度取反
    // MotorAPI_SpeedSetRPM((float)(-RampedMotorSpeedRf));
}
