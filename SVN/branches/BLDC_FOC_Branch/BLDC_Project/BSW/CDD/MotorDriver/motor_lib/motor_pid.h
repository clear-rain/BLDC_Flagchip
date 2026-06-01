/**
 * @file motor_pid.h
 * @author Flagchip127
 * @brief FC4xxx motor_pid
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

#ifndef _MOTOR_MOTOR_LIB_MOTOR_PID_H_
#define _MOTOR_MOTOR_LIB_MOTOR_PID_H_

typedef struct
{
    float kp;
    float ki;
    float kd;
    float out_max;
    float out_min;
    float in_ref;
    float in_mea;
    float sum;
    float out;

    /* 自适应 PID 开关与参数（可选，用于在 Motor_Pid 内启用动态 Ki） */
    int use_adaptive; /* 0: 关闭（默认原行为）；非0：启用自适应 Ki */

    /* 配置参数 */
    float ki_base;          /* 基础 Ki（自适应以此为基） */
    float ki_min;           /* Ki 下限 */
    float ki_max;           /* Ki 上限 */
    float ki_scale_slow;    /* 有进展时的 Ki 缩放（抑制积分） */
    float ki_scale_boost;   /* 堵转时的 Ki 放大（增强积分） */
    float progress_dmea_th; /* 进展判据阈值：|d(mea)| >= 此值 */
    float stall_dmea_th;    /* 堵转判据阈值：|d(mea)| <= 此值 */
    float stall_err_frac;   /* 堵转判据阈值：|err| > frac * max(|ref|,1) */
    int stall_count_th;     /* 堵转需连续满足的次数 */
    float adapt_alpha;      /* Ki 平滑系数 [0,1] */
    float dmea_alpha;       /* d(mea) 滤波系数 [0,1] */

    /* 运行态变量 */
    float ki_dyn;    /* 动态 Ki */
    float mea_prev;  /* 上次测量 */
    float dmea_filt; /* d(mea) 滤波 */
    int stall_count; /* 堵转计数 */
} MotorPid;

void Motor_PidInit(MotorPid *pid);
void Motor_Pid(MotorPid *pid);

#endif /* _MOTOR_MOTOR_LIB_MOTOR_PID_H_ */
