/**
 * @file motor_math.h
 * @author Flagchip127
 * @brief FC4xxx motor_math
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

#ifndef _MOTOR_LIB_MOTOR_MATH_H_
#define _MOTOR_LIB_MOTOR_MATH_H_

#include "compiler.h"
#include "stdint.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#endif
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880
#define M_SQRT1_2 0.70710678118654752440
#endif
#ifndef M_SQRT3
#define M_SQRT3 1.73205080756887719000
#define M_SQRT3_2 0.86602540378443859500
#endif

typedef struct
{
    float ia;
    float ib;
    float ic;
} MotorCurrent;

typedef struct
{
    float alpha;
    float beta;
} MotorAlphabetaCurrent, MotorAlphabetaVoltage;

typedef struct
{
    float angle;
    float sin;
    float cos;
} MotorPosition;

typedef struct
{
    float daxis;
    float qaxis;
} MotorDqCurrent, MotorDqVoltage;

LOCAL_INLINE
void Mat_Clark(MotorCurrent *motor_current, MotorAlphabetaCurrent *motor_alpha_beta_current)
{
    /********************************************
     *       |        1,      -1/2,       -1/2| *
     * 2/3 * |        0, sqrt(3)/2, -sqrt(3)/2| *
     *       |sqrt(2)/2, sqrt(2)/2,  sqrt(2)/2| *
     *******************************************/
    /********************************************
     * ia = -ib - ic
     *******************************************/

    // motor_alpha_beta_current->alpha = (motor_current->ia - (motor_current->ib + motor_current->ic)* 0.5f)* 2.0f/ 3.0f;
    motor_alpha_beta_current->alpha = motor_current->ia;
    motor_alpha_beta_current->beta =
        (motor_current->ib * 2 + motor_current->ia) * 0.866025404f * 2.0f / 3.0f;
}

LOCAL_INLINE
void Mat_Park(MotorAlphabetaCurrent *motor_alpha_beta_current,
              MotorPosition *motor_pos,
              MotorDqCurrent *motor_d_q_current)
{
    /********************************************
     *       |  cos,          sin|              *
     *       | -sin,          cos|              *
     *******************************************/

    motor_d_q_current->daxis =
        motor_alpha_beta_current->alpha * motor_pos->cos + motor_alpha_beta_current->beta * motor_pos->sin;
    motor_d_q_current->qaxis =
        -motor_alpha_beta_current->alpha * motor_pos->sin + motor_alpha_beta_current->beta * motor_pos->cos;
}

LOCAL_INLINE
void Mat_Antipark(MotorDqVoltage *motor_d_q_voltage,
                  MotorPosition *motor_pos,
                  MotorAlphabetaVoltage *motor_alpha_beta_voltage)
{
    /********************************************
     *       |  cos,         -sin|              *
     *       |  sin,          cos|              *
     *******************************************/

    motor_alpha_beta_voltage->alpha =
        motor_d_q_voltage->daxis * motor_pos->cos - motor_d_q_voltage->qaxis * motor_pos->sin;
    motor_alpha_beta_voltage->beta =
        motor_d_q_voltage->daxis * motor_pos->sin + motor_d_q_voltage->qaxis * motor_pos->cos;
}

LOCAL_INLINE
void Mat_AngleWraps(float *angle)
{
    const float two_pi = 2.0f * (float)M_PI;

    while (*angle >= two_pi)
    {
        *angle -= two_pi;
    }
    while (*angle < 0.0f)
    {
        *angle += two_pi;
    }
}

LOCAL_INLINE
void Lib_Ramp(float Input, float *Output, float UpStep, float DownStep)
{
    if (*Output > Input + DownStep)
    {
        *Output = *Output - DownStep;
    }
    else if (*Output < Input - UpStep)
    {
        *Output = *Output + UpStep;
    }
    else
    {
    }
}

#endif /* _MOTOR_LIB_MOTOR_MATH_H_ */
