/**
 * @file motor_pid.c
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

#include "motor_pid.h"

void Motor_PidInit(MotorPid *pid)
{
    pid->kp = 0;
    pid->ki = 0;
    pid->kd = 0;
    pid->out_max = 0;
    pid->out_min = 0;
    pid->sum = 0;
    pid->out = 0;
    pid->in_mea = 0;
    pid->in_ref = 0;

    /* 自适应默认关闭，参数给出保守初值 */
    pid->use_adaptive = 0;
    /* 让自适应基线默认跟随用户配置的 pid->ki（在运行时首次启用时采样） */
    pid->ki_base = 0.0f;        /* 0 表示尚未绑定到用户 Ki */
    pid->ki_min = 0.0f;         /* 0 表示尚未设置，将在绑定后按比例给出 */
    pid->ki_max = 0.0f;         /* 0 表示尚未设置，将在绑定后按比例给出 */
    pid->ki_scale_slow = 0.2f;  /* 正常加速时抑制积分：20% */
    pid->ki_scale_boost = 3.0f; /* 堵转时增强积分：3x */
    /* 速度环（rpm），Ts=50us：
         progress_dmea_th ~ 0.2 rpm/周期 (≈4000 rpm/s)
         stall_dmea_th    ~ 0.01 rpm/周期 (≈200 rpm/s)
         可按实际加速度/噪声微调 */
    pid->progress_dmea_th = 0.2f;
    pid->stall_dmea_th = 0.01f;
    pid->stall_err_frac = 0.2f;
    /* 堵转确认时长：~5ms @20kHz -> 100 次 */
    pid->stall_count_th = 100;
    /* Ki 平滑时间常数 ~5ms -> alpha≈Ts/tau≈0.01 */
    pid->adapt_alpha = 0.01f;
    /* d(mea) 滤波更保守，降噪 */
    pid->dmea_alpha = 0.1f;
    pid->ki_dyn = pid->ki_base;
    pid->mea_prev = 0.0f;
    pid->dmea_filt = 0.0f;
    pid->stall_count = 0;
}

void Motor_Pid(MotorPid *pid)
{
    float err, out, sat_err;

    err = pid->in_ref - pid->in_mea;

    /* 自适应 Ki：根据“进展/堵转”状态动态调整积分增益 */
    if (pid->use_adaptive)
    {
        float ki_adaptive;
        float dmea_raw, ref_abs, ref_norm, ki_tgt;
        int is_progress, stall_cond, is_stall;

        /* 若未显式配置 ki_base，则沿用当前 ki 作为自适应的基线 */
        if ((pid->ki_base == 0.0f) && (pid->ki != 0.0f))
        {
            pid->ki_base = pid->ki;
            if (pid->ki_dyn == 0.0f)
            {
                pid->ki_dyn = pid->ki;
            }
            /* 若未设置上下限，则给相对范围（10% ~ 10x） */
            if (pid->ki_min == 0.0f && pid->ki_base > 0.0f)
            {
                pid->ki_min = 0.1f * pid->ki_base;
            }
            if (pid->ki_max == 0.0f && pid->ki_base > 0.0f)
            {
                pid->ki_max = 10.0f * pid->ki_base;
            }
        }

        dmea_raw = pid->in_mea - pid->mea_prev;
        pid->mea_prev = pid->in_mea;

        /* 一阶滤波 d(mea) */
        pid->dmea_filt = pid->dmea_alpha * dmea_raw + (1.0f - pid->dmea_alpha) * pid->dmea_filt;

        /* 进展：err 与 dmea 同号且幅值超过阈值 */
        is_progress = ((err * pid->dmea_filt) > 0.0f)
                      && ((pid->dmea_filt >= pid->progress_dmea_th) || (-pid->dmea_filt >= pid->progress_dmea_th));

        /* 堵转：速度增量很小 + 偏差较大，需连续计数 */
        ref_abs = (pid->in_ref >= 0.0f) ? pid->in_ref : -pid->in_ref;
        ref_norm = (ref_abs > 1.0f) ? ref_abs : 1.0f;
        stall_cond = err >= 0.0f ? (pid->dmea_filt <= pid->stall_dmea_th && err > pid->stall_err_frac * ref_norm)
                                 : (-pid->dmea_filt <= pid->stall_dmea_th && -err > pid->stall_err_frac * ref_norm);
        if (stall_cond)
        {
            if (pid->stall_count < 32767)
            {
                pid->stall_count++;
            }
        }
        else
        {
            pid->stall_count = 0;
        }
        is_stall = (pid->stall_count >= pid->stall_count_th);

        /* 目标 Ki 与平滑 */
        if (is_stall)
        {
            ki_tgt = pid->ki_base * pid->ki_scale_boost;
        }
        else if (is_progress)
        {
            ki_tgt = pid->ki_base * pid->ki_scale_slow;
        }
        else
        {
            ki_tgt = pid->ki_base;
        }

        /* clamp */
        if (ki_tgt < pid->ki_min)
            ki_tgt = pid->ki_min;
        if (ki_tgt > pid->ki_max)
            ki_tgt = pid->ki_max;

        /* 平滑过渡 */
        pid->ki_dyn += pid->adapt_alpha * (ki_tgt - pid->ki_dyn);
        ki_adaptive = pid->ki_dyn;

        out = pid->sum + pid->kp * err;

        if (out > pid->out_max)
        {
            pid->out = pid->out_max;
        }
        else if (out < pid->out_min)
        {
            pid->out = pid->out_min;
        }
        else
        {
            pid->out = out;
        }

        sat_err = out - pid->out;
        pid->sum = pid->sum + ki_adaptive * err - pid->kd * sat_err;
    }
    else
    {
        out = pid->sum + pid->kp * err;

        if (out > pid->out_max)
        {
            pid->out = pid->out_max;
        }
        else if (out < pid->out_min)
        {
            pid->out = pid->out_min;
        }
        else
        {
            pid->out = out;
        }

        sat_err = out - pid->out;
        pid->sum = pid->sum + pid->ki * err - pid->kd * sat_err;
        if(pid->sum>pid->out_max)
        {
            pid->sum = pid->out_max;
        }
        else if(pid->sum < pid->out_min)
        {
            pid->sum = pid->out_min;
        }
    }
}
