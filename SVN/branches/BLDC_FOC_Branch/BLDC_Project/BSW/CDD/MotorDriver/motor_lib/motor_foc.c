/**()
 * @file motor"foc.c
 * @author Flagchip127
 * @brief FC4xxx motor_foc
 * @version 1.0.0
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   1.0.0       2024-05-20    Flagchip127   N/A          First version for FC4150
 ******************************************************************************** */

#include "motor_foc.h"
#include "IoHwAb_Counter.h"
#if ENABLE_RTT
#include "SEGGER_RTT.h"

typedef struct
{
    float vF32_1;
    float vF32_2;
} __attribute__((packed)) acValBuffer_t;

acValBuffer_t acValBuffer;

volatile MOTOR_SENSOR_HALL motor_sensor_hall_state;
extern MotorFocStruct motor_foc_struct;
extern MotorCurrent motor_current_0;

void UploadParameter(void)
{
    //	acValBuffer.vF32_1 = motor_foc_struct.motor_estimator.angle;
    acValBuffer.vF32_1 = motor_foc_struct.motor_ctrl_param.target_speed;
    acValBuffer.vF32_2 = motor_foc_struct.motor_estimator.speed;
    //	acValBuffer.vF32_1= motor_current_0.ib*10;
    //	acValBuffer.vF32_2= motor_current_0.ic*10;

    // acValBuffer.vF32_3 = motor_runing_output.angle * 100;
    SEGGER_RTT_Write(1, &acValBuffer, sizeof(acValBuffer));
    SEGGER_RTT_Write(1, &acValBuffer, sizeof(acValBuffer));
}
#endif

LOCAL_INLINE
void Motor_Pid_Speed(float ref_speed, float mea_speed, MotorPid *speed_pid)
{
#if ENABLE_ID_LIMIT_SPEED_PID_OUTPUT
    if (id_pid->in_ref < MAX_MOTOR_CURRENT)
    {
        speed_pid->out_max = sqrtf(
            (float)((float)(MAX_MOTOR_CURRENT * MAX_MOTOR_CURRENT) - (float)(speed_pid->in_ref * speed_pid->in_ref)));
        speed_pid->out_min = -speed_pid->out_max;
    }
    else
    {
        speed_pid->out_max = 0.0f;
        speed_pid->out_min = 0.0f;
    }
#endif
    speed_pid->in_ref = ref_speed;
    speed_pid->in_mea = mea_speed;

    Motor_Pid(speed_pid);
}

LOCAL_INLINE
void Motor_Pid_Current(float ref_current, float mea_current, MotorPid *current_pid)
{
    /* 误差死区：小于一定电流就视为 0，防止追噪声 */
    const float I_ERR_DEADBAND = 0.1f; /* 100mA，根据你的电流标定调整 */

    float err = ref_current - mea_current;
    if (err > -I_ERR_DEADBAND && err < I_ERR_DEADBAND)
    {
        /* 这里选择把误差钳为 0，保持输出平稳 */
        mea_current = ref_current;  /* 等价于 err = 0 */
    }
    current_pid->in_ref = ref_current;
    current_pid->in_mea = mea_current;

    Motor_Pid(current_pid);
}
LOCAL_INLINE
void Motor_dqVoltage_Ramp(MotorFocStruct *foc_str)
{
    const float ramp_step = 0.001f;

    RampValue(foc_str->motor_pid_id.out,
              &foc_str->motor_d_q_voltage_ramped.daxis,
              ramp_step,
              ramp_step,
              0.0f,
              0.0f);

    RampValue(foc_str->motor_pid_iq.out,
              &foc_str->motor_d_q_voltage_ramped.qaxis,
              ramp_step,
              ramp_step,
              0.0f,
              0.0f);

    foc_str->motor_d_q_voltage_out.daxis = foc_str->motor_d_q_voltage_ramped.daxis;
    foc_str->motor_d_q_voltage_out.qaxis = foc_str->motor_d_q_voltage_ramped.qaxis;
}

LOCAL_INLINE
void Motor_VoltageRef_Ramp(MotorFocStruct *foc_str)
{
    const float ramp_step = 0.001f;

    RampValue(foc_str->motor_ctrl_param.vd_ref,
              &foc_str->motor_d_q_voltage_ramped.daxis,
              ramp_step,
              ramp_step,
              0.0f,
              0.0f);

    RampValue(foc_str->motor_ctrl_param.vq_ref,
              &foc_str->motor_d_q_voltage_ramped.qaxis,
              ramp_step,
              ramp_step,
              0.0f,
              0.0f);

    foc_str->motor_d_q_voltage_out.daxis = foc_str->motor_d_q_voltage_ramped.daxis;
    foc_str->motor_d_q_voltage_out.qaxis = foc_str->motor_d_q_voltage_ramped.qaxis;
}

// uint8_t use_Realy = 0;
float speed_ramp;

#if MOTOR_DEBUG_CAPTURE
uint16_t testIConsumerCnt;
float testViewIa;
float testViewIb;
float testViewPwmA;
float testViewPwmB;
float testViewPwmC;
float testViewAngle;
#endif
void Motor_FocCtrl(void)
{
#if MOTOR_DEBUG_CAPTURE
    extern volatile uint16_t testIProducerCnt;
    extern volatile float testArrayIa[MOTOR_DEBUG_CAPTURE_LEN];
    extern volatile float testArrayIb[MOTOR_DEBUG_CAPTURE_LEN];
    extern volatile float testArrayPwmA[MOTOR_DEBUG_CAPTURE_LEN];
    extern volatile float testArrayPwmB[MOTOR_DEBUG_CAPTURE_LEN];
    extern volatile float testArrayPwmC[MOTOR_DEBUG_CAPTURE_LEN];
    extern volatile float testArrayAngle[MOTOR_DEBUG_CAPTURE_LEN];

    testViewIa = testArrayIa[testIConsumerCnt];
    testViewIb = testArrayIb[testIConsumerCnt];
    testViewPwmA = testArrayPwmA[testIConsumerCnt];
    testViewPwmB = testArrayPwmB[testIConsumerCnt];
    testViewPwmC = testArrayPwmC[testIConsumerCnt];
    testViewAngle = testArrayAngle[testIConsumerCnt];
    testIConsumerCnt++;
    if (testIConsumerCnt >= MOTOR_DEBUG_CAPTURE_LEN)
    {
        testIProducerCnt = 0;
        testIConsumerCnt = 0;
    }
#endif
    // 参考 Motor_FocRunning 的传入参数：从全局获取当前电流与FOC结构体
    extern MotorCurrent motor_current_0;
    extern MotorFocStruct motor_foc_struct;
    MotorCurrent *current_mea = &motor_current_0;
    MotorFocStruct *foc_str = &motor_foc_struct;
    (void)current_mea; // 当前函数未直接使用电流指针，避免未使用告警
    if (Motor_GetStatus() == MOTOR_STATUS_ON)
    {
        // 模式选择：0 - 电流模式；1 - 速度模式
        uint8_t mode = Motor_GetCtrlMode();
        switch (mode)
        {
            case MOTOR_CTRL_MODE_CURRENT:
                // 电流控制
                RampValue(foc_str->motor_ctrl_param.iq_ref,
                          &foc_str->motor_d_q_current_ramped.qaxis,
                          0.1f,
                          0.1f,
                          0.0f,
                          0.0f);
                RampValue(foc_str->motor_ctrl_param.id_ref,
                          &foc_str->motor_d_q_current_ramped.daxis,
                          0.1f,
                          0.1f,
                          0.0f,
                          0.0f);

                Motor_Pid_Current(foc_str->motor_d_q_current_ramped.daxis,
                                  foc_str->motor_d_q_current_filt.daxis,
                                  &foc_str->motor_pid_id);
                Motor_Pid_Current(foc_str->motor_d_q_current_ramped.qaxis,
                                  foc_str->motor_d_q_current_filt.qaxis,
                                  &foc_str->motor_pid_iq);

                // // For Test
                // foc_str->motor_pid_id.out = 0.0f;
                // foc_str->motor_pid_iq.out = 0.2f;

                break;
            case MOTOR_CTRL_MODE_SPEED:
                // 速度控制
                if (foc_str->loop_state == MOTOR_FOC_LOOP_CLOSED)
                {
                    // 闭环：用速度环输出设定 iq 参考，id=0
                    RampValue(foc_str->motor_ctrl_param.target_speed, &speed_ramp, 0.05f * 40, 0.05f * 40, 300.0f, 300.0f);
                    Motor_Pid_Speed(speed_ramp, foc_str->motor_estimator.speed, &foc_str->motor_pid_speed);

                    RampValue(0, &foc_str->motor_d_q_current_ramped.daxis, 0.01f, 0.01f, 0.0f, 0.0f);
                    RampValue(foc_str->motor_pid_speed.out,
                              &foc_str->motor_d_q_current_ramped.qaxis,
                              0.01f,
                              0.01f,
                              0.0f,
                              0.0f);
                    Motor_Pid_Current(foc_str->motor_d_q_current_ramped.daxis,
                                      foc_str->motor_d_q_current_filt.daxis,
                                      &foc_str->motor_pid_id);
                    Motor_Pid_Current(foc_str->motor_d_q_current_ramped.qaxis,
                                      foc_str->motor_d_q_current_filt.qaxis,
                                      &foc_str->motor_pid_iq);
                }
                break;
            case MOTOR_CTRL_MODE_VOLTAGE:
                /* 直接电压(d/q)控制：跳过电流 PID，直接使用参考电压（归一化幅值） */
                Motor_VoltageRef_Ramp(foc_str);
                /* 兼容：让 pid out 也跟随（便于观察/调试） */
                foc_str->motor_pid_id.out = foc_str->motor_d_q_voltage_out.daxis;
                foc_str->motor_pid_iq.out = foc_str->motor_d_q_voltage_out.qaxis;
                break;
        }

        // foc_str->motor_d_q_voltage_out.daxis =
        //     foc_str->motor_pid_id.out
        //     - foc_str->motor_estimator.speed * 0.10472f * 0.00074f * foc_str->motor_d_q_current_mea.qaxis;
        // foc_str->motor_d_q_voltage_out.qaxis =
        //     foc_str->motor_pid_iq.out + foc_str->motor_estimator.speed * 0.10472f * 0.00045f;
    }
}
volatile uint32_t testCnt;
volatile float testQout = 0.1f;
volatile float testDout = 0.0f;
void Motor_FocRunning(MotorCurrent *current_mea, MotorFocStruct *foc_str)
{
    IoHwAb_Counter_Clear();
    Mat_Clark(current_mea, &foc_str->motor_alpha_beta_current);
    Mat_Park(&foc_str->motor_alpha_beta_current, &foc_str->motor_position, &foc_str->motor_d_q_current_mea);
    // extern uint16_t Com_GetMTEncoderAngleData(void);
    // foc_str->motor_estimator.angle = Com_GetMTEncoderAngleData()/ 0xffff * 2.0 * M_PI  / 3;
    
    Motor_Estimator(&foc_str->motor_alpha_beta_current,
                    &foc_str->motor_alpha_beta_voltage,
                    &foc_str->motor_param,
                    &foc_str->motor_rotor,
                    &foc_str->motor_estimator);

    // 对外仅有 ON/OFF：当为 ON 时，可能处于开环或闭环阶段
    if (Motor_GetStatus() == MOTOR_STATUS_ON)
    {
        uint8_t mode = Motor_GetCtrlMode();

        if (mode == MOTOR_CTRL_MODE_SPEED)
        {
            if (foc_str->loop_state == MOTOR_FOC_LOOP_OPEN)
            {
                float direction = (foc_str->motor_ctrl_param.target_speed >= 0.0f) ? 1.0f : -1.0f;

                if (Motor_Openloop(&foc_str->motor_openloop,
                                   direction,
                                   &foc_str->motor_openloopcurrent,
                                   &foc_str->motor_position)
                    == kMotorFoc_CloseLoop)
                {
                    // 开环结束，切到闭环：对齐 Tmotor 行为
                    foc_str->motor_openloop.openloop_time = 0.0f;
                    foc_str->motor_openloop.openloop_angle_speed_up = 0.0f;
                    speed_ramp = foc_str->motor_estimator.speed;
                    foc_str->motor_position.angle = foc_str->motor_estimator.angle;
                    foc_str->loop_state = MOTOR_FOC_LOOP_CLOSED;
                }

                // 开环阶段：以开环给定电流为参考做电流环
                Motor_Pid_Current(foc_str->motor_openloopcurrent.daxis,
                                  foc_str->motor_d_q_current_mea.daxis,
                                  &foc_str->motor_pid_id);
                Motor_Pid_Current(foc_str->motor_openloopcurrent.qaxis,
                                  foc_str->motor_d_q_current_mea.qaxis,
                                  &foc_str->motor_pid_iq);
            }
            else
            {
                // 速度闭环阶段：位置由估算器决定
                foc_str->motor_position.angle = foc_str->motor_estimator.angle;
            }
        }
        else
        {
            // 电流/电压模式：统一使用估算器角度
            foc_str->motor_position.angle = foc_str->motor_estimator.angle;
        }

        /* d/q 电流一阶低通滤波，降低噪声与抖动（用于闭环电流/速度 PID） */
        {
            const float i_filter_alpha = 0.01f; /* 0~1，越小越平滑 */

            foc_str->motor_d_q_current_filt.daxis +=
                i_filter_alpha * (foc_str->motor_d_q_current_mea.daxis - foc_str->motor_d_q_current_filt.daxis);
            foc_str->motor_d_q_current_filt.qaxis +=
                i_filter_alpha * (foc_str->motor_d_q_current_mea.qaxis - foc_str->motor_d_q_current_filt.qaxis);
        }

        // PID 输出后做电压爬坡，减小阶跃（电流模式下爬坡更快）
        if (foc_str->motor_ctrl_param.ctrl_mode != MOTOR_CTRL_MODE_VOLTAGE)
        {
            Motor_dqVoltage_Ramp(foc_str);
        }

        /*
         * 电压死区会引入强非线性，容易在低电压/低速维持阶段形成极限环（锯齿）。
         * 电流模式下关闭死区；速度模式下保留较小死区用于抑噪。
         */
        if (foc_str->motor_ctrl_param.ctrl_mode != MOTOR_CTRL_MODE_CURRENT)
        {
            const float v_deadband = 0.01f;
            if (foc_str->motor_d_q_voltage_out.daxis < v_deadband && foc_str->motor_d_q_voltage_out.daxis > -v_deadband)
            {
                foc_str->motor_d_q_voltage_out.daxis = 0.0f;
            }
            if (foc_str->motor_d_q_voltage_out.qaxis < v_deadband && foc_str->motor_d_q_voltage_out.qaxis > -v_deadband)
            {
                foc_str->motor_d_q_voltage_out.qaxis = 0.0f;
            }
        }
        // static uint16_t testCntInner = 0;
        // foc_str->motor_d_q_voltage_out.daxis =testDout;
        // foc_str->motor_d_q_voltage_out.qaxis =
        // 0.5f * testQout * arm_sin_f32(testCntInner * 2.0f * (float)M_PI / 10000.0f) + testQout * 1.5f;
        // if(testCntInner++ >= 10000)
        // {
        //     testCntInner = 0;
        // }
        // foc_str->motor_d_q_voltage_out.daxis =testDout;
        // foc_str->motor_d_q_voltage_out.qaxis = testQout;
        Mat_SinCosLookup(foc_str->motor_position.angle, &foc_str->motor_position.sin, &foc_str->motor_position.cos);
        Mat_Antipark(&foc_str->motor_d_q_voltage_out, &foc_str->motor_position, &foc_str->motor_alpha_beta_voltage);

        Motor_Svpwm(&foc_str->motor_alpha_beta_voltage, &foc_str->motor_svpwm);
        Motor_TcUpdate(&foc_str->motor_svpwm, (void *)foc_str);
    }

    testCnt = IoHwAb_Counter_GetCnt() *125;
    // testCnt = IoHwAb_Counter_GetCnt() *125;
#if ENABLE_RTT
    UploadParameter();
#endif
}

void Motor_FocPidInit(MotorFocStruct *foc_str, MotorPid pid_speed, MotorPid pid_id, MotorPid pid_iq)
{
    Motor_PidInit(&foc_str->motor_pid_speed);
    Motor_PidInit(&foc_str->motor_pid_iq);
    Motor_PidInit(&foc_str->motor_pid_id);

    foc_str->motor_pid_speed.kp = pid_speed.kp;
    foc_str->motor_pid_speed.ki = pid_speed.ki;
    foc_str->motor_pid_speed.kd = pid_speed.kd;
    foc_str->motor_pid_speed.out_max = pid_speed.out_max;
    foc_str->motor_pid_speed.out_min = pid_speed.out_min;

    foc_str->motor_pid_id.kp = pid_id.kp;
    foc_str->motor_pid_id.ki = pid_id.ki;
    foc_str->motor_pid_id.kd = pid_id.kd;
    foc_str->motor_pid_id.out_max = pid_id.out_max;
    foc_str->motor_pid_id.out_min = pid_id.out_min;

    foc_str->motor_pid_iq.kp = pid_iq.kp;
    foc_str->motor_pid_iq.ki = pid_iq.ki;
    foc_str->motor_pid_iq.kd = pid_iq.kd;
    foc_str->motor_pid_iq.out_max = pid_iq.out_max;
    foc_str->motor_pid_iq.out_min = pid_iq.out_min;
}

void Motor_FocStart(MotorFocStruct *foc_str,
                    MotorCtrlMode mode,
                    float target_speed_rpm,
                    float id_ref,
                    float iq_ref,
                    float vd_ref,
                    float vq_ref)
{
    foc_str->motor_ctrl_param.foc_status = MOTOR_STATUS_ON;
    foc_str->motor_ctrl_param.ctrl_mode = (uint8_t)mode;
    foc_str->motor_ctrl_param.target_speed = target_speed_rpm;
    foc_str->motor_ctrl_param.id_ref = id_ref;
    foc_str->motor_ctrl_param.iq_ref = iq_ref;
    foc_str->motor_ctrl_param.vd_ref = vd_ref;
    foc_str->motor_ctrl_param.vq_ref = vq_ref;

    foc_str->motor_openloop.openloop_time = 0;
    foc_str->motor_openloop.openloop_angle_speed_up = 0;
    foc_str->motor_openloop.pre_pos_time = 0;

    foc_str->motor_openloopcurrent.qaxis = 0;
    foc_str->motor_openloopcurrent.daxis = 0;

    foc_str->motor_pid_speed.sum = 0;
    foc_str->motor_pid_id.sum = 0;
    foc_str->motor_pid_iq.sum = 0;

    Motor_EstimatorInit(&foc_str->motor_rotor, &foc_str->motor_estimator, &foc_str->motor_estimator_param);

    // 速度模式：根据配置选择开环或直接闭环；电流/电压模式：直接闭环
    if (mode == MOTOR_CTRL_MODE_SPEED)
    {
        foc_str->loop_state = (foc_str->speed_startup_mode == MOTOR_FOC_START_CLOSEDLOOP)
                                   ? MOTOR_FOC_LOOP_CLOSED
                                   : MOTOR_FOC_LOOP_OPEN;
    }
    else
    {
        foc_str->loop_state = MOTOR_FOC_LOOP_CLOSED;
    }

    // TODO: 开驱动芯片
}

void Motor_FocStop(MotorFocStruct *foc_str)
{
    foc_str->motor_ctrl_param.foc_status = MOTOR_STATUS_OFF;
    foc_str->motor_ctrl_param.target_speed = 0;

    // 复位内部状态
    foc_str->loop_state = MOTOR_FOC_LOOP_OPEN;

    // TODO: 关驱动芯片

    // 暂时通过调整占空比实现
    FTU_HWA_SetChannelValue(FTU0, 2, 0);
	FTU_HWA_SetChannelValue(FTU0, 4, 0);
	FTU_HWA_SetChannelValue(FTU0, 6, 0);
    FTU_HWA_GenerateSwSync(FTU0);
}

void Motor_FocInit(MotorFocStruct *foc_str, const MotorEstimatorParam *estimator_param)
{
    if (estimator_param)
    {
        foc_str->motor_estimator_param = *estimator_param;
    }
    else
    {
        /* 默认使用编码器直读，保持旧行为 */
        foc_str->motor_estimator_param.type = kMotorEstimator_ENCODER;
        foc_str->motor_estimator_param.nonlineflux_pll_param = 0;
    }

    Motor_EstimatorInit(&foc_str->motor_rotor, &foc_str->motor_estimator, &foc_str->motor_estimator_param);
    foc_str->loop_state = MOTOR_FOC_LOOP_OPEN;
    foc_str->speed_startup_mode = MOTOR_FOC_START_OPENLOOP;
    foc_str->motor_d_q_current_filt.daxis = 0.0f;
    foc_str->motor_d_q_current_filt.qaxis = 0.0f;
}
