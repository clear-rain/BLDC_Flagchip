/**
 * @file motor_misc.h
 * @author Flagchip127
 * @brief FC4xxx motor_misc
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

#ifndef _MOTOR_LIB_MOTOR_MISC_H_
#define _MOTOR_LIB_MOTOR_MISC_H_

#include "motor_config.h"

#include "motor_arm_math.h"
#include "motor_math.h"

typedef struct
{
    float vdc;
    float max;
    float resis;
    float induc;
    float bemf;
    float bemf_phase_rad;
    float pole_pairs;
    float pwm_freq;
} MotorParam;

typedef struct
{
    float time_max;
    float angle;
    float daxis;
    float qaxis;
} MotorOpenloopPrePos;

typedef struct
{
    uint8_t pre_pos_en;
    MotorOpenloopPrePos pre_pos[2];

    float openloop_time_max;
    float openloop_qaxis_max;
    float openloop_angle_speed_max;
    float openloop_pwm_freq;
    uint16_t task_freq;
} MotorOpenloopParam;

typedef struct
{
    uint8_t pre_pos_en;
    float pre_pos_time;
    MotorOpenloopPrePos pre_pos[2];

    float openloop_time;
    float openloop_time_max;
    float openloop_qaxis_max;
    float openloop_angle_speed_up;
    float openloop_angle_speed_max;
} MotorOpenloop;

typedef struct
{
    uint8_t foc_status;
    float target_speed;
    // 新增：模式与参考电流
    uint8_t ctrl_mode; // 0: current, 1: speed, 2: voltage
    float id_ref;
    float iq_ref;

    /* 电压模式下的 d/q 参考（单位与 motor_d_q_voltage_out 一致，通常为归一化幅值） */
    float vd_ref;
    float vq_ref;
} MotorCtrlParam;

// 对外仅保留开/关两态
#define MOTOR_STATUS_OFF 0u
#define MOTOR_STATUS_ON 1u

// 开环函数返回值语义，与 Tmotor 一致
#define kMotorFoc_OpenLoop 0u
#define kMotorFoc_CloseLoop 1u

// 控制模式：电流/速度（统一给库内外使用）
typedef enum
{
    MOTOR_CTRL_MODE_CURRENT = 0,
    MOTOR_CTRL_MODE_SPEED = 1,
    MOTOR_CTRL_MODE_VOLTAGE = 2,
} MotorCtrlMode;

void Motor_OpenloopInit(MotorOpenloop *openloop,
                        MotorDqCurrent *openloop_current,
                        MotorOpenloopParam openloop_param);
void Motor_ParamInit(MotorParam *motor_param);
void Motor_CtrlInit(MotorCtrlParam *ctrl);

void Motor_SetCtrlStatus(uint8_t status);
void Motor_SetSpeed(float speed);
void Motor_SetCtrlMode(uint8_t mode);
void Motor_SetCurrentRef(float id_ref, float iq_ref);
void Motor_SetVoltageRef(float vd_ref, float vq_ref);

uint8_t Motor_GetStatus(void);
float Motor_GetSpeed(void);
uint8_t Motor_GetCtrlMode(void);
void Motor_GetCurrentRef(float *id_ref, float *iq_ref);
void Motor_GetVoltageRef(float *vd_ref, float *vq_ref);

// 返回值：0 表示仍在开环阶段；1 表示达到闭环条件（内部使用）
uint8_t Motor_Openloop(MotorOpenloop *openloop, float direction, MotorDqCurrent *d_q_cuurent, MotorPosition *pos);

// 通用斜坡：全部参数为 float；当 jet_start==0 或 fast_threshold==0 时对应特性不启用
void RampValue(float target, float *ramp, float ACCStep, float DECStep, float jet_start, float fast_threshold);

#endif /* _MOTOR_LIB_MOTOR_MISC_H_ */
