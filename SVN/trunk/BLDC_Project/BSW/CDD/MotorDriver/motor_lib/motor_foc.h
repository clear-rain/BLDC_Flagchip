/**
 * @file motor_foc.h
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

#ifndef _MOTOR_LIB_MOTOR_FOC_H_
#define _MOTOR_LIB_MOTOR_FOC_H_

#include "motor_config.h"

#include "motor_estimator.h"
#include "motor_misc.h"
#include "motor_pid.h"
#include "motor_svpwm.h"

// 内部开环/闭环状态
typedef enum
{
    MOTOR_FOC_LOOP_OPEN = 0,
    MOTOR_FOC_LOOP_CLOSED = 1,
} MotorFocLoopState;

// 速度模式下的启动方式配置：开环起步 或 直接闭环启动
typedef enum
{
    MOTOR_FOC_START_OPENLOOP = 0,
    MOTOR_FOC_START_CLOSEDLOOP = 1,
} MotorFocStartupMode;

typedef struct
{
    MotorParam motor_param;
    MotorAlphabetaCurrent motor_alpha_beta_current;
    MotorAlphabetaVoltage motor_alpha_beta_voltage;
    MotorDqCurrent motor_d_q_current_ramped;
    MotorDqCurrent motor_d_q_current_mea;
    MotorDqCurrent motor_d_q_current_filt;
    MotorDqCurrent motor_d_q_voltage_ramped;
    MotorDqCurrent motor_d_q_voltage_out;
    MotorPosition motor_position;
	MotorOpenloop motor_openloop;
    MotorDqCurrent motor_openloopcurrent;
    MotorRotor motor_rotor;
    MotorEstimator motor_estimator;
    MotorEstimatorParam motor_estimator_param;
    MotorPid motor_pid_speed;
    MotorPid motor_pid_id;
    MotorPid motor_pid_iq;
    MotorSvpwm motor_svpwm;
    MotorCtrlParam motor_ctrl_param;
    // 内部：记录当前处于开环还是闭环
    MotorFocLoopState loop_state;
    // 配置：速度模式下的启动方式（默认开环起步）
    MotorFocStartupMode speed_startup_mode;
} MotorFocStruct;

void Motor_FocInit(MotorFocStruct *foc_str, const MotorEstimatorParam *estimator_param);
void Motor_FocPidInit(MotorFocStruct *foc_str, MotorPid pid_speed, MotorPid pid_id, MotorPid pid_iq);
// 新原型：对称传参，mode 指定控制模式；
// - 速度模式：使用 target_speed_rpm
// - 电流模式：使用 id_ref/iq_ref
// - 电压模式：使用 vd_ref/vq_ref
void Motor_FocStart(MotorFocStruct *foc_str,
                    MotorCtrlMode mode,
                    float target_speed_rpm,
                    float id_ref,
                    float iq_ref,
                    float vd_ref,
                    float vq_ref);
// 便捷封装：保持调用简洁
static inline void Motor_FocStartSpeed(MotorFocStruct *foc_str, float target_speed_rpm)
{
    Motor_FocStart(foc_str, MOTOR_CTRL_MODE_SPEED, target_speed_rpm, 0.0f, 0.0f, 0.0f, 0.0f);
}
static inline void Motor_FocStartCurrent(MotorFocStruct *foc_str, float id_ref, float iq_ref)
{
    Motor_FocStart(foc_str, MOTOR_CTRL_MODE_CURRENT, 0.0f, id_ref, iq_ref, 0.0f, 0.0f);
}
static inline void Motor_FocStartVoltage(MotorFocStruct *foc_str, float vd_ref, float vq_ref)
{
    Motor_FocStart(foc_str, MOTOR_CTRL_MODE_VOLTAGE, 0.0f, 0.0f, 0.0f, vd_ref, vq_ref);
}
void Motor_FocStop(MotorFocStruct *foc_str);
void Motor_FocRunning(MotorCurrent *current_mea, MotorFocStruct *foc_str);
// 无参版本：内部获取全局的 current 与 foc 结构
void Motor_FocCtrl(void);

#endif /* _MOTOR_LIB_MOTOR_FOC_H_ */
