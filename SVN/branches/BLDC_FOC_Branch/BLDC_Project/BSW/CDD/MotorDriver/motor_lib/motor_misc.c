/**(
 * @file motor_misc.h
 * @author Flagchip127
 * @brief FC4xxx motor_misc
 * @version 1.0.0
 * @date 2024-05-20
 *
 * @cop(right Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********,***********************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   1.0.0       2024-05-20    Flagchip127   N/A          First version for FC4150
 ******************************************************************************** */

#include "motor_misc.h"

// Single-motor: keep a single control parameter pointer
static MotorCtrlParam *gMotorCtrlParam = 0;

void Motor_OpenloopInit(MotorOpenloop *openloop,
                        MotorDqCurrent *openloop_current,
                        MotorOpenloopParam openloop_param)
{
    openloop->openloop_time = 0;
    openloop->openloop_time_max = openloop_param.openloop_time_max * openloop_param.openloop_pwm_freq;
    openloop->openloop_angle_speed_up = 0;
    openloop->openloop_angle_speed_max = openloop_param.openloop_angle_speed_max / openloop_param.openloop_pwm_freq;
    openloop->openloop_qaxis_max = openloop_param.openloop_qaxis_max;

    openloop->pre_pos_en = openloop_param.pre_pos_en;
    openloop->pre_pos_time = 0;
    openloop->pre_pos[0] = openloop_param.pre_pos[0];
    openloop->pre_pos[1] = openloop_param.pre_pos[1];

    openloop_current->qaxis = 0;
    openloop_current->daxis = 0;
}

uint8_t Motor_Openloop(MotorOpenloop *openloop, float direction, MotorDqCurrent *d_q_current, MotorPosition *pos)
{
    uint8_t openloop_status = kMotorFoc_OpenLoop;

    //-------------pre-positioning---------------
    if (openloop->pre_pos_time < openloop->pre_pos[0].time_max)
    {
        openloop->pre_pos_time += 1;
        pos->angle = openloop->pre_pos[0].angle;
        d_q_current->daxis = openloop->pre_pos[0].daxis;
        d_q_current->qaxis = openloop->pre_pos[0].qaxis;
    }
    else if (openloop->pre_pos_time < openloop->pre_pos[1].time_max)
    {
        openloop->pre_pos_time += 1;
        pos->angle = openloop->pre_pos[1].angle;
        d_q_current->daxis = openloop->pre_pos[1].daxis;
        d_q_current->qaxis = openloop->pre_pos[1].qaxis;
    }
    else
    {
        /* open loop from: 0 -> (openloop_time_max / 2) */
        if (openloop->openloop_time < (openloop->openloop_time_max / 2))
        {
            openloop->openloop_time += 1;
            openloop->openloop_angle_speed_up +=
                (openloop->openloop_angle_speed_max / openloop->openloop_time_max / 2);
            d_q_current->qaxis +=
                (openloop->openloop_qaxis_max / (openloop->openloop_time_max / 2)) * direction;
        }
        /* open loop from: (openloop_time_max / 2) -> openloop_time_max */
        else if (openloop->openloop_time < openloop->openloop_time_max)
        {
            openloop->openloop_time += 1;
            openloop->openloop_angle_speed_up +=
                openloop->openloop_angle_speed_max / openloop->openloop_time_max;
        }
        else
        {
            /* open loop time end, need limit q current to (openloop_qaxis / 2) */
            if ((d_q_current->qaxis * direction) > (openloop->openloop_qaxis_max / 2))
            {
                d_q_current->qaxis -=
                    (openloop->openloop_qaxis_max / (openloop->openloop_time_max / 2)) * direction;
            }
            /* finish open loop, q current is in range of requirment */
            else
            {
                openloop_status = kMotorFoc_CloseLoop;
            }
        }

        d_q_current->daxis = 0.0f;

        pos->angle += direction * openloop->openloop_angle_speed_up;
    }

    Mat_AngleWraps(&pos->angle);

    return openloop_status;
}

void RampValue(float target, float *ramp, float ACCStep, float DECStep, float jet_start, float fast_threshold)
{
    const float EPS = 1e-6f;

    if (fabsf(*ramp - target) <= EPS)
    {
        return;
    }

    // Jet start only when ramp is (near) zero and jet_start is (near) non-zero and target is (near) non-zero
    if ((fabsf(*ramp) <= EPS) && (fabsf(jet_start) > EPS) && (fabsf(target) > EPS))
    {
        *ramp = (target > 0.0f) ? jet_start : -jet_start;
        return;
    }
    float Step;

    // If we are changing direction
    if ((*ramp > 0.0f && target < 0.0f) || (*ramp < 0.0f && target > 0.0f))
    {
        // First, decelerate quickly
        Step = (*ramp > 0.0f) ? -DECStep : DECStep;
    }
    else if (fabsf(*ramp) <= EPS)
    {
        // If ramp is zero, determine the direction of acceleration based on target
        Step = (target > 0.0f) ? ACCStep : -ACCStep;
    }
    else
    {
        // Then, accelerate or decelerate slowly according to the target speed
        if (fabsf(*ramp) < fabsf(target))
        {
            // If accelerating
            Step = (*ramp > 0.0f) ? ACCStep : -ACCStep;
        }
        else
        {
            // If decelerating
            Step = (*ramp > 0.0f) ? -DECStep : DECStep;
        }
    }

    // Speed up when magnitude is below threshold (threshold robust to sign)
    if ((fast_threshold > EPS) && (fabsf(*ramp) < fast_threshold))
    {
        Step *= 10.0f;
    }
    // Apply step with robust crossing/overshoot detection
    {
        float old = *ramp;
        float newv = old + Step;
        // If old and new are on different sides of target (or one equals), clamp to target
        if ((newv - target) * (old - target) <= 0.0f)
        {
            *ramp = target;
        }
        else
        {
            *ramp = newv;
        }
    }
}

void Motor_ParamInit(MotorParam *motor_param) { motor_param->max = motor_param->vdc / (float)M_SQRT3; }

void Motor_CtrlInit(MotorCtrlParam *ctrl)
{
    ctrl->foc_status = MOTOR_STATUS_OFF;
    ctrl->target_speed = 0;
    ctrl->ctrl_mode = 1; // 默认速度模式
    ctrl->id_ref = 0.0f;
    ctrl->iq_ref = 0.0f;
    ctrl->vd_ref = 0.0f;
    ctrl->vq_ref = 0.0f;

    gMotorCtrlParam = ctrl;
}

void Motor_SetCtrlStatus(uint8_t status)
{
    if (gMotorCtrlParam)
        gMotorCtrlParam->foc_status = status;
}

void Motor_SetSpeed(float speed)
{
    if (gMotorCtrlParam)
        gMotorCtrlParam->target_speed = speed;
}

void Motor_SetCtrlMode(uint8_t mode)
{
    if (gMotorCtrlParam)
        gMotorCtrlParam->ctrl_mode = mode;
}

void Motor_SetCurrentRef(float id_ref, float iq_ref)
{
    if (gMotorCtrlParam)
    {
        gMotorCtrlParam->id_ref = id_ref;
        gMotorCtrlParam->iq_ref = iq_ref;
    }
}

void Motor_SetVoltageRef(float vd_ref, float vq_ref)
{
    if (gMotorCtrlParam)
    {
        gMotorCtrlParam->vd_ref = vd_ref;
        gMotorCtrlParam->vq_ref = vq_ref;
    }
}

uint8_t Motor_GetStatus(void) { return gMotorCtrlParam ? gMotorCtrlParam->foc_status : 0; }

float Motor_GetSpeed(void) { return gMotorCtrlParam ? gMotorCtrlParam->target_speed : 0.0f; }

uint8_t Motor_GetCtrlMode(void) { return gMotorCtrlParam ? gMotorCtrlParam->ctrl_mode : 1; }

void Motor_GetCurrentRef(float *id_ref, float *iq_ref)
{
    if (id_ref)
        *id_ref = gMotorCtrlParam ? gMotorCtrlParam->id_ref : 0.0f;
    if (iq_ref)
        *iq_ref = gMotorCtrlParam ? gMotorCtrlParam->iq_ref : 0.0f;
}

void Motor_GetVoltageRef(float *vd_ref, float *vq_ref)
{
    if (vd_ref)
        *vd_ref = gMotorCtrlParam ? gMotorCtrlParam->vd_ref : 0.0f;
    if (vq_ref)
        *vq_ref = gMotorCtrlParam ? gMotorCtrlParam->vq_ref : 0.0f;
}
