#include "motor_api.h"
#include "motor_app.h"
#include "motor_foc.h"
#include "motor_misc.h"

extern MotorFocStruct motor_foc_struct;

// 内部状态：控制模式与参考值
static MotorCtrlMode s_mode = MOTOR_CTRL_MODE_SPEED;
static float s_ref_rpm = 0.0f;
static float s_ref_id = 0.0f;
static float s_ref_iq = 0.0f;
static float s_ref_vd = 0.0f;
static float s_ref_vq = 0.0f;

// 直接对外暴露 MotorPid：设置时整体拷贝，但保留若干运行态复位策略，避免瞬态毛刺
static void apply_pid_overwrite(MotorPid *dst, const MotorPid *src)
{
    if (!dst || !src)
        return;
    *dst = *src;

    // 清理旧值
    dst->sum = 0.0f;
    dst->out = 0.0f;
    dst->mea_prev = 0.0f;
    dst->dmea_filt = 0.0f;
    dst->stall_count = 0;
}

void MotorAPI_Init(void)
{
    // 仅确保底层初始化被调用一次
    Motor_Init();
}

static void Reset_Motor_State(void)
{
    MotorPid pid;

    /* 1) 先按当前参数重置 PID 运行态，避免积分/微分历史带入 */
    pid = motor_foc_struct.motor_pid_speed;
    apply_pid_overwrite(&motor_foc_struct.motor_pid_speed, &pid);

    pid = motor_foc_struct.motor_pid_id;
    apply_pid_overwrite(&motor_foc_struct.motor_pid_id, &pid);

    pid = motor_foc_struct.motor_pid_iq;
    apply_pid_overwrite(&motor_foc_struct.motor_pid_iq, &pid);

    /* 2) 再清零 FOC 相关的运行数据，尽量避免上一次运行遗留状态 */

    /* 电流/电压在 αβ、dq 坐标系下的缓存及滤波值 */
    motor_foc_struct.motor_alpha_beta_current.alpha = 0.0f;
    motor_foc_struct.motor_alpha_beta_current.beta = 0.0f;

    motor_foc_struct.motor_alpha_beta_voltage.alpha = 0.0f;
    motor_foc_struct.motor_alpha_beta_voltage.beta = 0.0f;

    motor_foc_struct.motor_d_q_current_ramped.daxis = 0.0f;
    motor_foc_struct.motor_d_q_current_ramped.qaxis = 0.0f;

    motor_foc_struct.motor_d_q_current_mea.daxis = 0.0f;
    motor_foc_struct.motor_d_q_current_mea.qaxis = 0.0f;

    motor_foc_struct.motor_d_q_current_filt.daxis = 0.0f;
    motor_foc_struct.motor_d_q_current_filt.qaxis = 0.0f;

    motor_foc_struct.motor_d_q_voltage_ramped.daxis = 0.0f;
    motor_foc_struct.motor_d_q_voltage_ramped.qaxis = 0.0f;

    motor_foc_struct.motor_d_q_voltage_out.daxis = 0.0f;
    motor_foc_struct.motor_d_q_voltage_out.qaxis = 0.0f;

    /* 位置与正余弦缓存，重置为 0 角度 */
    motor_foc_struct.motor_position.angle = 0.0f;
    motor_foc_struct.motor_position.sin = 0.0f;
    motor_foc_struct.motor_position.cos = 1.0f;

    /* 开环启动相关的内部计数与电流参考 */
    motor_foc_struct.motor_openloop.openloop_time = 0.0f;
    motor_foc_struct.motor_openloop.pre_pos_time = 0.0f;
    motor_foc_struct.motor_openloop.openloop_angle_speed_up = 0.0f;

    motor_foc_struct.motor_openloopcurrent.daxis = 0.0f;
    motor_foc_struct.motor_openloopcurrent.qaxis = 0.0f;

    /* 速度斜坡内部状态（在 motor_foc.c 中定义为全局变量） */
    extern float speed_ramp;
    speed_ramp = 0.0f;

    /* SVPWM 输出缓存占空比，周期保持不变 */
    motor_foc_struct.motor_svpwm.pwm_a = 0u;
    motor_foc_struct.motor_svpwm.pwm_b = 0u;
    motor_foc_struct.motor_svpwm.pwm_c = 0u;

    /* 估算器与循环状态：与 Motor_FocInit / Motor_FocStart 行为保持一致 */
    Motor_EstimatorInit(&motor_foc_struct.motor_rotor,
                        &motor_foc_struct.motor_estimator,
                        &motor_foc_struct.motor_estimator_param);
    motor_foc_struct.loop_state = MOTOR_FOC_LOOP_OPEN;
}

void MotorAPI_StatusSet(bool on)
{
    if (on)
    {
        // 依据当前模式选择启动目标（对称传参）
        if (s_mode == MOTOR_CTRL_MODE_SPEED)
        {
            // Motor_FocStart(&motor_foc_struct, MOTOR_CTRL_MODE_SPEED, s_ref_rpm, 0.0f, 0.0f);
            Motor_FocStartSpeed(&motor_foc_struct, s_ref_rpm);
        }
        else if (s_mode == MOTOR_CTRL_MODE_CURRENT)
        {
            // Motor_FocStart(&motor_foc_struct, MOTOR_CTRL_MODE_CURRENT, 0.0f, s_ref_id, s_ref_iq);
            Motor_FocStartCurrent(&motor_foc_struct, s_ref_id, s_ref_iq);
        }
        else
        {
            Motor_FocStartVoltage(&motor_foc_struct, s_ref_vd, s_ref_vq);
        }
    }
    else
    {
        Reset_Motor_State();   // 每次关闭前复位 PID 运行状态
        Motor_FocStop(&motor_foc_struct);
    }
}

bool MotorAPI_StatusGet(void) { return Motor_GetStatus() == MOTOR_STATUS_ON; }

void MotorAPI_ModeSet(MotorCtrlMode mode)
{
    s_mode = mode;
    Motor_SetCtrlMode((uint8_t)mode);
}

MotorCtrlMode MotorAPI_ModeGet(void) { return s_mode; }

void MotorAPI_SpeedSetRPM(float rpm)
{
    s_ref_rpm = rpm;
    Motor_SetSpeed(rpm);
    motor_foc_struct.motor_ctrl_param.target_speed = rpm;
}

float MotorAPI_SpeedGetRPM(void)
{
    return motor_foc_struct.motor_estimator.speed; // 反馈实际速度
}

void MotorAPI_CurrentSetDQ(float id_ref, float iq_ref)
{
    s_ref_id = id_ref;
    s_ref_iq = iq_ref;
    Motor_SetCurrentRef(id_ref, iq_ref);
}

void MotorAPI_CurrentGetDQRef(float *id_ref, float *iq_ref)
{
    if (id_ref)
        *id_ref = s_ref_id;
    if (iq_ref)
        *iq_ref = s_ref_iq;
}

void MotorAPI_CurrentGetDQMea(float *id_mea, float *iq_mea)
{
    if (id_mea)
        *id_mea = motor_foc_struct.motor_d_q_current_mea.daxis;
    if (iq_mea)
        *iq_mea = motor_foc_struct.motor_d_q_current_mea.qaxis;
}

void MotorAPI_VoltageSetDQ(float vd_ref, float vq_ref)
{
    s_ref_vd = vd_ref;
    s_ref_vq = vq_ref;
    Motor_SetVoltageRef(vd_ref, vq_ref);
}

void MotorAPI_VoltageGetDQRef(float *vd_ref, float *vq_ref)
{
    if (vd_ref)
        *vd_ref = s_ref_vd;
    if (vq_ref)
        *vq_ref = s_ref_vq;
}

void MotorAPI_VoltageGetDQOut(float *vd_out, float *vq_out)
{
    if (vd_out)
        *vd_out = motor_foc_struct.motor_d_q_voltage_out.daxis;
    if (vq_out)
        *vq_out = motor_foc_struct.motor_d_q_voltage_out.qaxis;
}

void MotorAPI_CurrentPidRuntimeSetSum(float id_sum, float iq_sum)
{
    motor_foc_struct.motor_pid_id.sum = id_sum;
    motor_foc_struct.motor_pid_iq.sum = iq_sum;

    /* 兼容：让 out 同步一下，便于观察；下一次 Motor_Pid 会重新计算 out */
    motor_foc_struct.motor_pid_id.out = id_sum;
    motor_foc_struct.motor_pid_iq.out = iq_sum;
}

void MotorAPI_SpeedPidRuntimeSetSum(float speed_sum)
{
    motor_foc_struct.motor_pid_speed.sum = speed_sum;

    /* 兼容：让 out 同步一下，便于观察；下一次 Motor_Pid 会重新计算 out */
    motor_foc_struct.motor_pid_speed.out = speed_sum;
}

void MotorAPI_PidSetSpeed(const MotorPid *pid)
{
    if (!pid)
        return;
    apply_pid_overwrite(&motor_foc_struct.motor_pid_speed, pid);
}

void MotorAPI_PidSetId(const MotorPid *pid)
{
    if (!pid)
        return;
    apply_pid_overwrite(&motor_foc_struct.motor_pid_id, pid);
}

void MotorAPI_PidSetIq(const MotorPid *pid)
{
    if (!pid)
        return;
    apply_pid_overwrite(&motor_foc_struct.motor_pid_iq, pid);
}

void MotorAPI_PidGetSpeed(MotorPid *pid)
{
    if (!pid)
        return;
    *pid = motor_foc_struct.motor_pid_speed;
}

void MotorAPI_PidGetId(MotorPid *pid)
{
    if (!pid)
        return;
    *pid = motor_foc_struct.motor_pid_id;
}

void MotorAPI_PidGetIq(MotorPid *pid)
{
    if (!pid)
        return;
    *pid = motor_foc_struct.motor_pid_iq;
}

void MotorAPI_ErrorClear(void)
{
    // 暂不实现
}

void MotorAPI_ErrorGet(uint32_t *p) { (void)p; }
