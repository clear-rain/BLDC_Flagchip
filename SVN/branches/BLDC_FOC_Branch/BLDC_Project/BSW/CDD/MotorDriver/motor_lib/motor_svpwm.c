/**
 * @file motor_svpwm.c
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
 *   1.0.0       2024-05-20    Flagchip127   n/A          First version for FC4150
 *****************,************************************************************** */

#include "motor_svpwm.h"
#include "IoHwAb_Pwm.h"
#include "motor_config.h"
#include "IoHwAb_Dio.h"
#include "motor_foc.h"

// PWM 占空比调试缓冲，模仿电流采样缓冲
#if MOTOR_DEBUG_CAPTURE
/* 复用电流采样的生产者计数器，保证同一索引下的电流与 PWM 对应同一控制周期 */
extern volatile uint16_t testIProducerCnt;
volatile float testArrayPwmA[MOTOR_DEBUG_CAPTURE_LEN];
volatile float testArrayPwmB[MOTOR_DEBUG_CAPTURE_LEN];
volatile float testArrayPwmC[MOTOR_DEBUG_CAPTURE_LEN];
volatile float testArrayAngle[MOTOR_DEBUG_CAPTURE_LEN];
#endif

static const float kSqrt3 = (float)M_SQRT3;
static const float kSqrt3_2 = 0.5f * (float)M_SQRT3;

#ifndef MOTOR_SVPWM_ZERO7_RATIO
#define MOTOR_SVPWM_ZERO7_RATIO (0.5f)
#endif

static inline float Motor_SelectXYZ(int8_t sel, float x, float y, float z)
{
    switch (sel)
    {
        case 1:
            return x;
        case -1:
            return -x;
        case 2:
            return y;
        case -2:
            return -y;
        case 3:
            return z;
        case -3:
            return -z;
        default:
            return 0.0f;
    }
}

static inline float Motor_SelectT(uint8_t sel, float ta, float tb, float tc)
{
    switch (sel)
    {
        case 0U:
            return ta;
        case 1U:
            return tb;
        case 2U:
            return tc;
        default:
            return tb;
    }
}

static inline uint32_t Motor_ClampCastPwmCount(float t, uint32_t period)
{
    /* Treat NaN as 0, clamp to [0, period], then round-to-nearest */
    if (!(t > 0.0f))
        return 0U;
    /* Round-to-nearest with saturation */
    if (t >= ((float)period - 0.5f))
        return period;
    return (uint32_t)(t + 0.5f);
}

void Motor_SvpwmInit(MotorSvpwm *svpwm, uint32_t period)
{
    svpwm->period = period;
    svpwm->pwm_a = 0U;
    svpwm->pwm_b = 0U;
    svpwm->pwm_c = 0U;
}
void Motor_Svpwm(MotorAlphabetaVoltage *alpha_beta_voltage, MotorSvpwm *svpwm)
{
    float x, y, z, ta, tb, tc;
    float tx = 0, ty = 0;
    uint32_t n = 0;

    const float period = (float)svpwm->period;
    const float alpha = alpha_beta_voltage->alpha;
    const float beta = alpha_beta_voltage->beta;

    /* Sector bits: sign tests only; positive scaling (e.g., *0.5f) does not change sign */
    n = ((beta >= 0.0f) ? 1U : 0U) |
        (((kSqrt3 * alpha - beta) >= 0.0f) ? 2U : 0U) |
        (((-kSqrt3 * alpha - beta) >= 0.0f) ? 4U : 0U);

    x = period * beta;
    y = period * (kSqrt3_2 * alpha + 0.5f * beta);
    z = period * (-kSqrt3_2 * alpha + 0.5f * beta);

    {
        /* 0:0, 1:+z, 2:+y, 3:-z, 4:-x, 5:+x, 6:-y, 7:0 */
        static const int8_t kTxSel[8] = {0, 3, 2, -3, -1, 1, -2, 0};
        /* 0:0, 1:+y, 2:-x, 3:+x, 4:+z, 5:-y, 6:-z, 7:0 */
        static const int8_t kTySel[8] = {0, 2, -1, 1, 3, -2, -3, 0};
        const uint8_t sector = (uint8_t)(n & 0x7U);
        tx = Motor_SelectXYZ(kTxSel[sector], x, y, z);
        ty = Motor_SelectXYZ(kTySel[sector], x, y, z);
    }

    {
        const float sum = tx + ty;
        if ((sum > period) && (sum > 0.0f))
        {
            const float scale = period / sum;
            tx *= scale;
            ty *= scale;
        }
        else if (sum <= 0.0f)
        {
            /* Prevent division-by-zero / negative sum due to numerical corner cases */
            tx = 0.0f;
            ty = 0.0f;
        }
    }
    {
        const float t0 = period - tx - ty;
        float t0b = t0 * MOTOR_SVPWM_ZERO7_RATIO;

        if (t0b < 0.0f)
        {
            t0b = 0.0f;
        }
        else if (t0b > t0)
        {
            t0b = t0;
        }

        tc = t0b;
        tb = t0b + ty;
        ta = tb + tx;
    }

    const uint32_t period_u32 = svpwm->period;

    {
        /* 0/7 don't matter because ta==tb==tc when tx=ty=0; pick any mapping */
        static const uint8_t kMapA[8] = {1U, 1U, 0U, 0U, 2U, 2U, 1U, 1U};
        static const uint8_t kMapB[8] = {1U, 0U, 2U, 1U, 1U, 0U, 2U, 1U};
        static const uint8_t kMapC[8] = {1U, 2U, 1U, 2U, 0U, 1U, 0U, 1U};
        const uint8_t sector = (uint8_t)(n & 0x7U);

        const float out_a = Motor_SelectT(kMapA[sector], ta, tb, tc);
        const float out_b = Motor_SelectT(kMapB[sector], ta, tb, tc);
        const float out_c = Motor_SelectT(kMapC[sector], ta, tb, tc);

        svpwm->pwm_a = Motor_ClampCastPwmCount(out_a, period_u32);
        svpwm->pwm_b = Motor_ClampCastPwmCount(out_b, period_u32);
        svpwm->pwm_c = Motor_ClampCastPwmCount(out_c, period_u32);
    }
}

static void Motor_PWM_Set_Duty(uint16_t CH_A, uint16_t CH_B, uint16_t CH_C)
{
//    Bsp_PWM_DutySet(e_PWM_INA_IDX, CH_A);
//    Bsp_PWM_DutySet(e_PWM_INB_IDX, CH_B);
//    Bsp_PWM_DutySet(e_PWM_INC_IDX, CH_C);


//    IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 0);
	FTU_HWA_SetChannelValue(FTU0, 2, CH_A/2);
	FTU_HWA_SetChannelValue(FTU0, 4, CH_B/2);
	FTU_HWA_SetChannelValue(FTU0, 6, CH_C/2);
    FTU_HWA_GenerateSwSync(FTU0);

//    IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 1);
}

// 采用整数计算：min_cap = MAX_PERIOD * 2% = MAX_PERIOD / 50；max_cap = MAX_PERIOD - min_cap
const uint16_t min_cap = (uint16_t)((uint32_t)MAX_PERIOD / (uint32_t)20U);
const uint16_t max_cap = (uint16_t)((uint32_t)MAX_PERIOD - (uint32_t)min_cap);

void Motor_TcUpdate(MotorSvpwm *svm, void *foc_str)
{
    volatile uint16_t pwm_a, pwm_b, pwm_c;
    const uint32_t    period = svm->period;
    // 使用整型周期进行计算，避免浮点->整数的隐式转换
    pwm_a = (uint16_t)(period - svm->pwm_a);
    pwm_b = (uint16_t)(period - svm->pwm_b);
    pwm_c = (uint16_t)(period - svm->pwm_c);

    if (pwm_a >= max_cap)
        pwm_a = max_cap;
    if (pwm_b >= max_cap)
        pwm_b = max_cap;
    if (pwm_c >= max_cap)
        pwm_c = max_cap;

    if (pwm_a <= min_cap)
        pwm_a = min_cap;
    if (pwm_b <= min_cap)
        pwm_b = min_cap;
    if (pwm_c <= min_cap)
        pwm_c = min_cap;

    // 缓存最终占空比（归一化到 0~1 便于观察）
#if MOTOR_DEBUG_CAPTURE
    if (testIProducerCnt < MOTOR_DEBUG_CAPTURE_LEN)
    {
        const float inv_period = 1.0f / (float)period;
        testArrayPwmA[testIProducerCnt] = (float)pwm_a * inv_period;
        testArrayPwmB[testIProducerCnt] = (float)pwm_b * inv_period;
        testArrayPwmC[testIProducerCnt] = (float)pwm_c * inv_period;
        testArrayAngle[testIProducerCnt] = ((MotorFocStruct *)foc_str)->motor_position.angle;
        /* 生产者计数器在 ADC 中断中统一自增，保证同一索引的一组数据完整 */
    }
#endif

    (void)foc_str;

//    static uint8_t flag =0;
//    flag++;
//    if(flag == 0){
    	Motor_PWM_Set_Duty(pwm_a, pwm_b, pwm_c);
//    }
//    Bsp_PWM_DutySet(e_PWM_INA_IDX, 750);
//    Bsp_PWM_DutySet(e_PWM_INB_IDX, 1500);
//    Bsp_PWM_DutySet(e_PWM_INC_IDX, 2250);
}
