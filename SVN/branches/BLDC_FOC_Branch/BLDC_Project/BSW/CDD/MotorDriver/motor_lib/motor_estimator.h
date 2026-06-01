/**
 * @file motor_estimator.h
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
#ifndef _MOTOR_LIB_MOTOR_ESTIMATOR_H_
#define _MOTOR_LIB_MOTOR_ESTIMATOR_H_

#include "motor_misc.h"

/* 估算器类型：默认保留编码器直读，新增非线性磁通 + PLL 分支 */
typedef enum
{
    kMotorEstimator_ENCODER = 0,
    kMotorEstimator_NONLINEFLUX_PLL,
    kMotorEstimator_HALL,
    kMotorEstimator_SMO_PLL,
    kMotorEstimator_SMO_ESO_PLL,
    kMotorEstimator_MAX_NUM,
} MotorEstimatorType;


typedef struct
{
    float esa;
    float esb;
    float we;
    float velocity;
    float angle;
    float ialpha_es;
    float esa_unfiltered;
    float ibeta_es;
    float esb_unfiltered;
    float rho;
    float ui;
} MotorRotorSmoPll;

typedef struct
{
    float esa;
    float esb;
    float we;
    float velocity;
    float angle;
    float ialpha_es;
    float esa_unfiltered;
    float ibeta_es;
    float esb_unfiltered;
    float rho;
    float pll_k;
} MotorRotorSmoEsoPll;

typedef struct
{
    float theta;
    float rho;
    float ui;
    float velocity;
    float we;
    float x1_es;
    float x2_es;
} MotorRotorNonlineFluxPll;

typedef struct
{
    float rho;
    float we;
} MotorRotorHall;

typedef struct
{
    float k_pll;
    float pll_pi_p;
    float pll_pi_i;
} MotorSmoPllParam;

typedef struct
{
    float k_smo;
    float k_pll;
} MotorSmoEsoPllParam;

typedef struct
{
    float gama;
    float k_pll;
    float pll_pi_p;
    float pll_pi_i;
} MotorNolineFluxPllParam;


typedef struct
{
    union
    {
        MotorRotorSmoPll smo_pll;
        MotorRotorSmoEsoPll smo_eso_pll;
        MotorRotorNonlineFluxPll nonlineflux_pll;
        MotorRotorHall hall;
        float rotor[32];
    };
} MotorRotor;


typedef struct
{
    MotorEstimatorType type;
    float angle;
    float speed;
    union
    {

        MotorSmoPllParam smo_pll_param;
        MotorSmoEsoPllParam smo_eso_pll_param;
        MotorNolineFluxPllParam nonlineflux_pll_param;
        float param[16];
    };
} MotorEstimator;

typedef struct
{
    MotorEstimatorType type;

    MotorSmoPllParam *smo_pll_param;
    MotorSmoEsoPllParam *smo_eso_pll_param;
    MotorNolineFluxPllParam *nonlineflux_pll_param;
} MotorEstimatorParam;

typedef struct
{
    float angle;
    float estimated_angle;
    float period;
    float angle_speed_inc;
    float sample_period;
    float speed;
    uint32_t sample_count;
    float direction;
    uint16_t last_hall_state;
} MOTOR_SENSOR_HALL;
extern volatile MOTOR_SENSOR_HALL motor_sensor_hall_state;

/* IoHwAb_Counter 使用 FTU1：PCC 选择 FOSCDIVH（BspClock.c 配置为 16MHz，DIVH=1），
 * BspFtuCounter.c 中 prescaler=FTU_DIV_2，因此计数 tick 频率为 16MHz/2 = 8MHz。 */
#define FTU_SECONDS_PER_TICK (float)(1.0f / 8000000.0f)

void Motor_EstimatorInit(MotorRotor *rotor, MotorEstimator *estimator, const MotorEstimatorParam *estimator_param);
void Motor_Estimator(MotorAlphabetaCurrent *alpha_beta_current,
                     MotorAlphabetaVoltage *alpha_beta_voltage,
                     MotorParam *motor_param,
                     MotorRotor *rotor,
                     MotorEstimator *estimator);

#endif /* _MOTOR_LIB_MOTOR_ESTIMATOR_H_ */
