/*
 * motor_hall.h
 * Hall 位置估算模块 — 公共头文件
 *
 * 按 hall_rewrite_spec.md 规格重写。
 * 非基础性功能通过 HALL_FEATURE_xxx 宏控制，编译时可用
 * -DHALL_FEATURE_xxx=0 关闭对应功能。
 */

#ifndef MOTOR_HALL_H_
#define MOTOR_HALL_H_

#include "motor_estimator.h"

/* ============================================================
 *  Feature Macros — 非基础性功能开关
 * ============================================================ */

/* 低速回退：低于阈值时退回扇区中心角，避免低速抖动 */
#ifndef HALL_FEATURE_LOW_SPEED_FALLBACK
#define HALL_FEATURE_LOW_SPEED_FALLBACK      0
#endif

/* 非法 Hall 状态保护：非法状态丢弃，保持上一次有效状态 */
#ifndef HALL_FEATURE_ILLEGAL_STATE_GUARD
#define HALL_FEATURE_ILLEGAL_STATE_GUARD     0
#endif

/* 丢边容错：允许跨多个扇区计算速度 */
#ifndef HALL_FEATURE_MISSED_EDGE_TOLERANCE
#define HALL_FEATURE_MISSED_EDGE_TOLERANCE   0
#endif

/* 速度 IIR 滤波（边沿侧） */
#ifndef HALL_FEATURE_SPEED_FILTER
#define HALL_FEATURE_SPEED_FILTER            1
#endif

/* 使用多扇区滑动窗口作为主速度估算 */
#ifndef HALL_FEATURE_WINDOW_SPEED
#define HALL_FEATURE_WINDOW_SPEED            1
#endif

/* 检测窗口内来回抖动 */
#ifndef HALL_FEATURE_OSCILLATION_DETECT
#define HALL_FEATURE_OSCILLATION_DETECT      1
#endif

/* 超时检测：Hall 边沿超时后清零速度、退回中心角 */
#ifndef HALL_FEATURE_TIMEOUT_DETECTION
#define HALL_FEATURE_TIMEOUT_DETECTION       1
#endif

/* 调试可观测变量 */
#ifndef HALL_FEATURE_DEBUG_OBSERVE
#define HALL_FEATURE_DEBUG_OBSERVE           0
#endif

/* ============================================================
 *  Configuration Constants
 * ============================================================ */

#ifndef HALL_MAX_RPM_VALID
#define HALL_MAX_RPM_VALID      6000.0f
#endif

#ifndef HALL_MIN_RPM_VALID
#define HALL_MIN_RPM_VALID      5.0f
#endif

/* 速度窗口覆盖的扇区数；6 表示 1 个电角周期。 */
#ifndef HALL_SPEED_WINDOW_SECTORS
#define HALL_SPEED_WINDOW_SECTORS 6U
#endif

#if HALL_FEATURE_LOW_SPEED_FALLBACK
#ifndef HALL_INTERP_MIN_RPM
#define HALL_INTERP_MIN_RPM     20.0f
#endif
#endif

#if HALL_FEATURE_TIMEOUT_DETECTION
#ifndef HALL_STOP_TIMEOUT_SEC
#define HALL_STOP_TIMEOUT_SEC   0.2f
#endif
/* 溢出计数阈值：达到该值即判定为边沿超时 */
#ifndef HALL_OVERFLOW_THRESHOLD
#define HALL_OVERFLOW_THRESHOLD  1U
#endif
#endif

#if HALL_FEATURE_SPEED_FILTER
#ifndef HALL_SPEED_FILTER_ALPHA
#define HALL_SPEED_FILTER_ALPHA 0.8f
#endif
#endif

#if HALL_FEATURE_OSCILLATION_DETECT
#ifndef HALL_OSCILLATION_MIN_SAMPLES
#define HALL_OSCILLATION_MIN_SAMPLES 4U
#endif

#ifndef HALL_OSCILLATION_MAX_NET_STEPS
#define HALL_OSCILLATION_MAX_NET_STEPS 2U
#endif

#ifndef HALL_OSCILLATION_MIN_DIR_FLIPS
#define HALL_OSCILLATION_MIN_DIR_FLIPS 2U
#endif

#ifndef HALL_OSCILLATION_ZERO_RPM
#define HALL_OSCILLATION_ZERO_RPM 30.0f
#endif

#ifndef HALL_OSCILLATION_CONFIRM_CYCLES
#define HALL_OSCILLATION_CONFIRM_CYCLES 10U
#endif
#endif

/* 周期侧输出速度平滑滤波权重 */
#ifndef HALL_OUTPUT_FILTER_ALPHA
#define HALL_OUTPUT_FILTER_ALPHA 0.9f
#endif

/* ============================================================
 *  Reset/Failure Reason Enumeration
 * ============================================================ */

typedef enum {
    HALL_RESET_NONE             = 0U,
    HALL_RESET_OVERFLOW         = 1U,   /* FTU 溢出超时 */
    HALL_RESET_LOW_SPEED        = 2U,   /* dt 过大，低于最低 RPM */
    HALL_RESET_INVALID_DT       = 3U,   /* dt<=0 或 travel_angle 无效 */
    HALL_RESET_FIRST_SYNC       = 4U,   /* 首次同步，不出速度 */
    HALL_RESET_PERIODIC_TIMEOUT = 5U,   /* 周期侧检测到超时 */
    HALL_RESET_ILLEGAL_STATE    = 6U,   /* 非法 Hall 状态 */
    HALL_RESET_OSCILLATION      = 7U    /* 窗口内检测到来回抖动 */
} HallResetReason;

/* ============================================================
 *  Debug Observability
 * ============================================================ */

#if HALL_FEATURE_DEBUG_OBSERVE
extern volatile uint8_t  motor_hall_overflow_count_dbg;
extern volatile int8_t   motor_hall_step_delta_dbg;
extern volatile uint32_t motor_hall_diff_cnt_dbg;
extern volatile uint8_t  motor_hall_reset_reason_dbg;
#endif

/* ============================================================
 *  Public API
 * ============================================================ */

/* GPIO 中断回调入口 — 由 BspGpio Hall 中断回调调用 */
extern void hall_estimator_irq(void);

/* FOC 周期调用入口 — 由 Motor_Estimator() 调用 */
extern void Motor_Hall_Transducer(MotorEstimator *estimator);

#endif /* MOTOR_HALL_H_ */
