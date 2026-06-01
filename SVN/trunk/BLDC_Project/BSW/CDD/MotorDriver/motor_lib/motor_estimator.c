/**
 * @file motor_estimator.c
 * @author Flagchip127
 * @brief FC4xxx motor_estimator
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
#include "motor_estimator.h"
#include "motor_encoder.h"
#include "motor_hall.h"
#include <math.h>

/* 默认参数：当未提供外部配置时使用 */
static const MotorNolineFluxPllParam s_default_flux_param = {
    .gama = GAMMA,
    .k_pll = KFILTER_VELESTIM,
    .pll_pi_p = PI_NONLINEAR_P,
    .pll_pi_i = PI_NONLINEAR_I,
};

void Motor_EstimatorInit(MotorRotor *rotor, MotorEstimator *estimator, const MotorEstimatorParam *estimator_param)
{
    const MotorEstimatorType type = estimator_param ? estimator_param->type : estimator->type;
    estimator->type = type;
    estimator->angle = 0.0f;
    estimator->speed = 0.0f;

    /* 参数拷贝：按当前估算器类型拷贝对应参数，缺省使用默认值 */
    if (estimator_param)
    {
        switch (type)
        {
            case kMotorEstimator_SMO_PLL:
                if (estimator_param->smo_pll_param)
                {
                    estimator->smo_pll_param = *(estimator_param->smo_pll_param);
                }
                else
                {
                    estimator->smo_pll_param.k_pll = 0.0f;
                    estimator->smo_pll_param.pll_pi_p = 0.0f;
                    estimator->smo_pll_param.pll_pi_i = 0.0f;
                }
                break;

            case kMotorEstimator_SMO_ESO_PLL:
                if (estimator_param->smo_eso_pll_param)
                {
                    estimator->smo_eso_pll_param = *(estimator_param->smo_eso_pll_param);
                }
                else
                {
                    estimator->smo_eso_pll_param.k_smo = 0.0f;
                    estimator->smo_eso_pll_param.k_pll = 0.0f;
                }
                break;

            case kMotorEstimator_NONLINEFLUX_PLL:
                if (estimator_param->nonlineflux_pll_param)
                {
                    estimator->nonlineflux_pll_param = *(estimator_param->nonlineflux_pll_param);
                }
                else
                {
                    estimator->nonlineflux_pll_param = s_default_flux_param;
                }
                break;

            default:
                break;
        }
    }
    else
    {
        /* 没有显式参数时，给各分支填入安全缺省值 */
        estimator->smo_pll_param.k_pll = 0.0f;
        estimator->smo_pll_param.pll_pi_p = 0.0f;
        estimator->smo_pll_param.pll_pi_i = 0.0f;
        estimator->smo_eso_pll_param.k_smo = 0.0f;
        estimator->smo_eso_pll_param.k_pll = 0.0f;
        estimator->nonlineflux_pll_param = s_default_flux_param;
    }

    switch (type)
    {
        case kMotorEstimator_SMO_PLL:
            {
                rotor->smo_pll.esa = 0;
                rotor->smo_pll.esb = 0;
                rotor->smo_pll.we = 0;
                rotor->smo_pll.velocity = 0;
                rotor->smo_pll.angle = 0;
                rotor->smo_pll.ialpha_es = 0;
                rotor->smo_pll.esa_unfiltered = 0;
                rotor->smo_pll.ibeta_es = 0;
                rotor->smo_pll.esb_unfiltered = 0;
                rotor->smo_pll.rho = 0;
                rotor->smo_pll.ui = 0;
            }
            break;

        case kMotorEstimator_SMO_ESO_PLL:
            {
                rotor->smo_eso_pll.esa = 0;
                rotor->smo_eso_pll.esb = 0;
                rotor->smo_eso_pll.we = 0;
                rotor->smo_eso_pll.velocity = 0;
                rotor->smo_eso_pll.angle = 0;
                rotor->smo_eso_pll.ialpha_es = 0;
                rotor->smo_eso_pll.esa_unfiltered = 0;
                rotor->smo_eso_pll.ibeta_es = 0;
                rotor->smo_eso_pll.esb_unfiltered = 0;
                rotor->smo_eso_pll.rho = 0;
                rotor->smo_eso_pll.pll_k = 0;
            }
            break;
        case kMotorEstimator_NONLINEFLUX_PLL:
            rotor->nonlineflux_pll.rho = 0.0f;
            rotor->nonlineflux_pll.ui = 0.0f;
            rotor->nonlineflux_pll.theta = 0.0f;
            rotor->nonlineflux_pll.velocity = 0.0f;
            rotor->nonlineflux_pll.we = 0.0f;
            rotor->nonlineflux_pll.x1_es = 0.0f;
            rotor->nonlineflux_pll.x2_es = 0.0f;
            break;

        case kMotorEstimator_HALL:
            rotor->hall.rho = 0.0f;
            rotor->hall.we = 0.0f;
            break;

        case kMotorEstimator_ENCODER:
        default:
            /* 编码器直读无需内部状态 */
            break;
    }
}
volatile float view_delta_e;
volatile float view_delta_e_filter;
extern volatile uint32_t testCnt;
extern void IoHwAb_Counter_Clear(void);
//#include "C:\Work\FC_IDE\JAC_Project\BSW\ECAL\IoHwAb\Inc\IoHwAb_Dio.h"
static void Motor_Estimator_Smo_Pll(MotorAlphabetaCurrent *alpha_beta_current,
                                    MotorAlphabetaVoltage *alpha_beta_voltage,
                                    MotorParam *motor_param,
                                    MotorRotor *rotor,
                                    MotorEstimator *estimator)
{
    float ialpha_error, ibeta_error, ialpha, ibeta, ualpha, ubeta, filter;
    MotorPosition temp_rotor_position_smo_pll;

    /* 尽量减少除法与函数调用次数，减轻每次估算开销 */
    const float inv_pwm_freq = 1.0f / motor_param->pwm_freq;
    const float inv_L = 1.0f / motor_param->induc;
    const float R_over_L = motor_param->resis * inv_L;
    const float max_val = motor_param->max;
    const float two_pi_over_60 = 2.0f * (float)M_PI / 60.0f;

    ialpha = alpha_beta_current->alpha;
    ibeta = alpha_beta_current->beta;
    ualpha = alpha_beta_voltage->alpha * max_val;
    ubeta = alpha_beta_voltage->beta * max_val;


    if (estimator->speed > 400)
    {
        filter = (float)(estimator->speed * motor_param->pole_pairs * two_pi_over_60 * 3.0f / 20000.0f);
    }
    else
    {
        filter = (float)(400.0f * motor_param->pole_pairs * two_pi_over_60 * 3.0f / 20000.0f);
    }

    rotor->smo_pll.ialpha_es =
        rotor->smo_pll.ialpha_es
        + inv_pwm_freq
              * ((ualpha * inv_L) - (rotor->smo_pll.ialpha_es * R_over_L)
                 - (rotor->smo_pll.esa_unfiltered * inv_L));
    ialpha_error = rotor->smo_pll.ialpha_es - ialpha;

    if (ialpha_error > 0)
    {
        if (ialpha_error > 0.1)
        {
            rotor->smo_pll.esa_unfiltered = max_val;
        }
        else
        {
            rotor->smo_pll.esa_unfiltered = ialpha_error * 10.0f * max_val;
        }
    }
    else if (ialpha_error < 0)
    {
        if (ialpha_error < -0.1)
        {
            rotor->smo_pll.esa_unfiltered = -max_val;
        }
        else
        {
            rotor->smo_pll.esa_unfiltered = ialpha_error * 10.0f * max_val;
        }
    }
    else
    {
        rotor->smo_pll.esa_unfiltered = 0;
    }
    

    
    // IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 0);

    
    rotor->smo_pll.esa = rotor->smo_pll.esa + (rotor->smo_pll.esa_unfiltered - rotor->smo_pll.esa) * filter;

    rotor->smo_pll.ibeta_es =
        rotor->smo_pll.ibeta_es
        + inv_pwm_freq
              * ((ubeta * inv_L) - (rotor->smo_pll.ibeta_es * R_over_L)
                 - (rotor->smo_pll.esb_unfiltered * inv_L));
    ibeta_error = rotor->smo_pll.ibeta_es - ibeta;

    if (ibeta_error > 0)
    {
        if (ibeta_error > 0.1)
        {
            rotor->smo_pll.esb_unfiltered = max_val;
        }
        else
        {
            rotor->smo_pll.esb_unfiltered = ibeta_error * 10.0f * max_val;
        }
    }
    else if (ibeta_error < 0)
    {
        if (ibeta_error < -0.1)
        {
            rotor->smo_pll.esb_unfiltered = -max_val;
        }
        else
        {
            rotor->smo_pll.esb_unfiltered = ibeta_error * 10.0f * max_val;
        }
    }
    else
    {
        rotor->smo_pll.esb_unfiltered = 0;
    }

    rotor->smo_pll.esb = rotor->smo_pll.esb + (rotor->smo_pll.esb_unfiltered - rotor->smo_pll.esb) * filter;

    // PLL
    float delta_e, up, out_pre, out, error;
    temp_rotor_position_smo_pll.angle = rotor->smo_pll.rho;
    Mat_AngleWraps(&temp_rotor_position_smo_pll.angle);
    Mat_SinCosLookup(
        temp_rotor_position_smo_pll.angle, &temp_rotor_position_smo_pll.sin, &temp_rotor_position_smo_pll.cos);
    delta_e = -(rotor->smo_pll.esa * temp_rotor_position_smo_pll.cos)
              - (rotor->smo_pll.esb * temp_rotor_position_smo_pll.sin);

    view_delta_e = delta_e;
    // view_delta_e_filter = view_delta_e_filter + 0.01f * (view_delta_e - view_delta_e_filter);
    // 浮点view_delta_e 转定点  乘以1000转为整数处理   然后使用滑动窗口滤波  
    static uint16_t filter_index = 0;
    #define FILTER_LEN 100
    static float filter_buffer[FILTER_LEN] = {0};
    filter_buffer[filter_index++] = view_delta_e * 1000.0f;
    if (filter_index >= FILTER_LEN)
        filter_index = 0;
    float filter_sum = 0.0f;
    for (uint16_t i = 0; i < FILTER_LEN; i++)
    {
        filter_sum += filter_buffer[i];
    }
    view_delta_e_filter =  view_delta_e_filter + 0.01f * (filter_sum / FILTER_LEN / 1000.0f  - view_delta_e_filter);


    up = estimator->smo_pll_param.pll_pi_p * delta_e;
    out_pre = rotor->smo_pll.ui + up;

    /* 避免多次调用 Motor_GetSpeed 和重复常数运算 */
    const float speed_ref = Motor_GetSpeed();
    const float pll_speed_limit = PLL_PI_LIMIT_K * speed_ref * motor_param->pole_pairs * two_pi_over_60;

    if (out_pre > pll_speed_limit)
    {
        out = pll_speed_limit;
    }
    else if (out_pre < 0)
    {
        out = 0;
    }
    else
    {
        out = out_pre;
    }
    error = out - out_pre;
    rotor->smo_pll.ui = rotor->smo_pll.ui + up * estimator->smo_pll_param.pll_pi_i + 0.2 * error;
    rotor->smo_pll.velocity = out;

    rotor->smo_pll.we =
        rotor->smo_pll.we + (rotor->smo_pll.velocity - rotor->smo_pll.we) * estimator->smo_pll_param.k_pll;

    rotor->smo_pll.rho = rotor->smo_pll.rho + ((rotor->smo_pll.velocity) * (1.0f / motor_param->pwm_freq));
    Mat_AngleWraps(&rotor->smo_pll.rho);

    estimator->angle = rotor->smo_pll.rho;
    estimator->speed = rotor->smo_pll.we * 30 / M_PI / motor_param->pole_pairs;
    
    // IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 1);
}

static void Motor_Estimator_Smo_Eso_Pll(MotorAlphabetaCurrent *alpha_beta_current,
                                        MotorAlphabetaVoltage *alpha_beta_voltage,
                                        MotorParam *motor_param,
                                        MotorRotor *rotor,
                                        MotorEstimator *estimator)
{
    float ialpha_error, ibeta_error, ialpha, ibeta, ualpha, ubeta, filter;
    MotorPosition temp_rotor_position_smo_pll;

    ialpha = alpha_beta_current->alpha;
    ibeta = alpha_beta_current->beta;
    ualpha = alpha_beta_voltage->alpha * motor_param->max;
    ubeta = alpha_beta_voltage->beta * motor_param->max;

    if (estimator->speed > 400)
    {
        filter = (float)(estimator->speed * motor_param->pole_pairs / 60 * 2 * M_PI * 3 / 20000);
        ;
    }
    else
    {
        filter = (float)(400 * motor_param->pole_pairs / 60 * 2 * M_PI * 3 / 20000);
        ;
    }

    rotor->smo_eso_pll.ialpha_es = rotor->smo_eso_pll.ialpha_es
                                   + 1.0f / motor_param->pwm_freq
                                         * ((ualpha / motor_param->induc)
                                            - (rotor->smo_eso_pll.ialpha_es * motor_param->resis / motor_param->induc)
                                            - (rotor->smo_eso_pll.esa_unfiltered / motor_param->induc));
    ialpha_error = rotor->smo_eso_pll.ialpha_es - ialpha;

    if (ialpha_error > 0)
    {
        if (ialpha_error > 0.1)
        {
            rotor->smo_eso_pll.esa_unfiltered = motor_param->max;
        }
        else
        {
            rotor->smo_eso_pll.esa_unfiltered = ialpha_error * 10 * motor_param->max;
        }
    }
    else if (ialpha_error < 0)
    {
        if (ialpha_error < -0.1)
        {
            rotor->smo_eso_pll.esa_unfiltered = -motor_param->max;
        }
        else
        {
            rotor->smo_eso_pll.esa_unfiltered = ialpha_error * 10 * motor_param->max;
        }
    }
    else
    {
        rotor->smo_eso_pll.esa_unfiltered = 0;
    }

    rotor->smo_eso_pll.esa =
        rotor->smo_eso_pll.esa + (rotor->smo_eso_pll.esa_unfiltered - rotor->smo_eso_pll.esa) * filter;

    rotor->smo_eso_pll.ibeta_es =
        rotor->smo_eso_pll.ibeta_es
        + 1.0f / motor_param->pwm_freq
              * ((ubeta / motor_param->induc) - (rotor->smo_eso_pll.ibeta_es * motor_param->resis / motor_param->induc)
                 - (rotor->smo_eso_pll.esb_unfiltered / motor_param->induc));
    ibeta_error = rotor->smo_eso_pll.ibeta_es - ibeta;

    if (ibeta_error > 0)
    {
        if (ibeta_error > 0.1)
        {
            rotor->smo_eso_pll.esb_unfiltered = motor_param->max;
        }
        else
        {
            rotor->smo_eso_pll.esb_unfiltered = ibeta_error * 10 * motor_param->max;
        }
    }
    else if (ibeta_error < 0)
    {
        if (ibeta_error < -0.1)
        {
            rotor->smo_eso_pll.esb_unfiltered = -motor_param->max;
        }
        else
        {
            rotor->smo_eso_pll.esb_unfiltered = ibeta_error * 10 * motor_param->max;
        }
    }
    else
    {
        rotor->smo_eso_pll.esb_unfiltered = 0;
    }

    rotor->smo_eso_pll.esb =
        rotor->smo_eso_pll.esb + (rotor->smo_eso_pll.esb_unfiltered - rotor->smo_eso_pll.esb) * filter;

    // ESO_PLL
    float beta1, beta2, beta3, delta_e;

    temp_rotor_position_smo_pll.angle = rotor->smo_eso_pll.rho;
    Mat_AngleWraps(&temp_rotor_position_smo_pll.angle);
    Mat_SinCosLookup(
        temp_rotor_position_smo_pll.angle, &temp_rotor_position_smo_pll.sin, &temp_rotor_position_smo_pll.cos);

    delta_e = -(rotor->smo_eso_pll.esa * temp_rotor_position_smo_pll.cos)
              - (rotor->smo_eso_pll.esb * temp_rotor_position_smo_pll.sin);

    beta1 = 3 * estimator->smo_eso_pll_param.k_smo;
    beta2 = 3 * estimator->smo_eso_pll_param.k_smo * estimator->smo_eso_pll_param.k_smo;
    beta3 =
        -estimator->smo_eso_pll_param.k_smo * estimator->smo_eso_pll_param.k_smo * estimator->smo_eso_pll_param.k_smo;

    rotor->smo_eso_pll.pll_k += delta_e * beta3 * 1.0f / motor_param->pwm_freq;
    rotor->smo_eso_pll.velocity += (rotor->smo_eso_pll.pll_k - (delta_e * beta2)) * 1.0f / motor_param->pwm_freq;
    rotor->smo_eso_pll.rho += (rotor->smo_eso_pll.velocity - (delta_e * beta1)) * 1.0f / motor_param->pwm_freq;
    Mat_AngleWraps(&rotor->smo_eso_pll.rho);
    if (rotor->smo_eso_pll.velocity
        > (PLL_PI_LIMIT_K * Motor_GetSpeed() * motor_param->pole_pairs * 2 * M_PI / 60))
    {
        rotor->smo_eso_pll.velocity =
            (PLL_PI_LIMIT_K * Motor_GetSpeed() * motor_param->pole_pairs * 2 * M_PI / 60);
    }
    else if (rotor->smo_eso_pll.velocity < (0))
    {
        rotor->smo_eso_pll.velocity = 0;
    }
    else
    {
        ;
    }
    rotor->smo_eso_pll.we =
        rotor->smo_eso_pll.we
        + (rotor->smo_eso_pll.velocity - rotor->smo_eso_pll.we) * estimator->smo_eso_pll_param.k_pll;
    rotor->smo_eso_pll.angle = rotor->smo_eso_pll.rho + M_PI;
    Mat_AngleWraps(&rotor->smo_eso_pll.angle);

    estimator->angle = rotor->smo_eso_pll.angle;
    estimator->speed = rotor->smo_eso_pll.we * 30 / M_PI / motor_param->pole_pairs;
}

static void Motor_Estimator_Nonlineflux_Pll(MotorAlphabetaCurrent *alpha_beta_current,
                                            MotorAlphabetaVoltage *alpha_beta_voltage,
                                            MotorParam *motor_param,
                                            MotorRotor *rotor,
                                            MotorEstimator *estimator)
{
    float y1, y2, n1, n2, x1_es, x2_es, err, sin_x, cos_x;
    float ialpha, ibeta, ualpha, ubeta;

    ialpha = alpha_beta_current->alpha;
    ibeta = alpha_beta_current->beta;
    ualpha = alpha_beta_voltage->alpha * motor_param->max;
    ubeta = alpha_beta_voltage->beta * motor_param->max;

    y1 = ualpha - motor_param->resis * ialpha;
    y2 = ubeta - motor_param->resis * ibeta;

    n1 = rotor->nonlineflux_pll.x1_es - motor_param->induc * ialpha;
    n2 = rotor->nonlineflux_pll.x2_es - motor_param->induc * ibeta;

    err = (motor_param->bemf_phase_rad * motor_param->bemf_phase_rad) - ((n1 * n1) + (n2 * n2));

    x1_es = rotor->nonlineflux_pll.x1_es
            + (1.0f / motor_param->pwm_freq) * (y1 + 0.5f * estimator->nonlineflux_pll_param.gama * n1 * err);
    x2_es = rotor->nonlineflux_pll.x2_es
            + (1.0f / motor_param->pwm_freq) * (y2 + 0.5f * estimator->nonlineflux_pll_param.gama * n2 * err);

    rotor->nonlineflux_pll.x1_es = x1_es;
    rotor->nonlineflux_pll.x2_es = x2_es;

    cos_x = n1 / motor_param->bemf_phase_rad;
    sin_x = n2 / motor_param->bemf_phase_rad;

    Mat_FastArctan(sin_x, cos_x, &rotor->nonlineflux_pll.theta);
    Mat_AngleWraps(&rotor->nonlineflux_pll.theta);

    // PLL
    float delta_n, delta_theta, up, out_pre, out, error;

    delta_n = rotor->nonlineflux_pll.theta - rotor->nonlineflux_pll.rho;

    if (delta_n > 0.2f)
    {
        delta_theta = 0.2f;
    }
    else if (delta_n < -0.2f)
    {
        delta_theta = -0.2f;
    }
    else
    {
        delta_theta = delta_n;
    }

    up = estimator->nonlineflux_pll_param.pll_pi_p * delta_theta;
    out_pre = rotor->nonlineflux_pll.ui + up;

    const float pll_limit = PLL_PI_LIMIT_K * Motor_GetSpeed() * motor_param->pole_pairs * 2.0f * (float)M_PI / 60.0f;
    if (out_pre > pll_limit)
    {
        out = pll_limit;
    }
    else if (out_pre < -pll_limit)
    {
        out = -pll_limit;
    }
    else
    {
        out = out_pre;
    }

    error = out - out_pre;
    rotor->nonlineflux_pll.ui = rotor->nonlineflux_pll.ui
                                + delta_theta * estimator->nonlineflux_pll_param.pll_pi_i * 1.0f / motor_param->pwm_freq
                                + 0.2f * error;
    rotor->nonlineflux_pll.velocity = out;

    rotor->nonlineflux_pll.we =
        rotor->nonlineflux_pll.we
        + (rotor->nonlineflux_pll.velocity - rotor->nonlineflux_pll.we) * estimator->nonlineflux_pll_param.k_pll;

    rotor->nonlineflux_pll.rho =
        rotor->nonlineflux_pll.rho + ((rotor->nonlineflux_pll.velocity) * (1.0f / motor_param->pwm_freq));
    Mat_AngleWraps(&rotor->nonlineflux_pll.rho);

    estimator->angle = rotor->nonlineflux_pll.rho;
    estimator->speed = rotor->nonlineflux_pll.we * 30.0f / (float)M_PI / motor_param->pole_pairs;
}

void Motor_Estimator(MotorAlphabetaCurrent *alpha_beta_current,
                     MotorAlphabetaVoltage *alpha_beta_voltage,
                     MotorParam *motor_param,
                     MotorRotor *rotor,
                     MotorEstimator *estimator)
{
    switch (estimator->type)
    {
        case kMotorEstimator_SMO_PLL:
            {
                Motor_Estimator_Smo_Pll(alpha_beta_current, alpha_beta_voltage, motor_param, rotor, estimator);
            }
            break;

        case kMotorEstimator_SMO_ESO_PLL:
            {
                Motor_Estimator_Smo_Eso_Pll(alpha_beta_current, alpha_beta_voltage, motor_param, rotor, estimator);
            }
            break;
        case kMotorEstimator_NONLINEFLUX_PLL:
            {
                Motor_Estimator_Nonlineflux_Pll(alpha_beta_current, alpha_beta_voltage, motor_param, rotor, estimator);
            }
            break;

        case kMotorEstimator_HALL:
            Motor_Hall_Transducer(estimator);
            break;

        case kMotorEstimator_ENCODER:
        default:
            Motor_Encoder_Transducer(estimator);
            break;
    }
}
