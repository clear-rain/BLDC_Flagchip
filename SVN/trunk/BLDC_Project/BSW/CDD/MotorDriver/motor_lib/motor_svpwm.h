/**
 * @file motor_svpwm.h
 * @author Flagchip127
 * @brief FC4xxx motor_svpwm
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

#ifndef _MOTOR_MOTOR_LIB_MOTOR_SVPWM_H_
#define _MOTOR_MOTOR_LIB_MOTOR_SVPWM_H_

#include "motor_math.h"

typedef struct
{
    uint32_t period;
    uint32_t pwm_a;
    uint32_t pwm_b;
    uint32_t pwm_c;
} MotorSvpwm;

void Motor_SvpwmInit(MotorSvpwm *svpwm, uint32_t period);
void Motor_Svpwm(MotorAlphabetaVoltage *alpha_beta_voltage, MotorSvpwm *svpwm);
void Motor_TcUpdate(MotorSvpwm *svm, void *foc_str);

#endif /* _MOTOR_MOTOR_LIB_MOTOR_SVPWM_H_ */
