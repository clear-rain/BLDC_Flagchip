#ifndef _DEVICE_FEATURES_FC4150F512__TRGSEL_COMMON_H_
#define _DEVICE_FEATURES_FC4150F512__TRGSEL_COMMON_H_
/*********************** Trgsel Features ****************************/
#define TRGSEL_INSTANCE_COUNT                                  (4u)
/** Peripheral TRGSEL3 base address */
#define TRGSEL3_BASE                             (0x40072000u)
/** Peripheral TRGSEL3 base pointer */
#define TRGSEL3                                  ((TRGSEL_Type *)TRGSEL3_BASE)
/** Array initializer of TRGSEL peripheral base addresses */
#define TRGSEL_BASE_ADDRS                        {TRGSEL0_BASE, TRGSEL1_BASE, TRGSEL2_BASE, TRGSEL3_BASE}
/** Array initializer of TRGSEL peripheral base pointers */
#define TRGSEL_BASE_PTRS                         {TRGSEL0, TRGSEL1, TRGSEL2, TRGSEL3}

/**
 * @brief TrgSel instance 0 trigger targets
 *
 */
typedef enum
{
    TRGSEL0_TARGET_FTU0_TRG0               = 0U, /* Target trigger is FTU0_TRG0 */
    TRGSEL0_TARGET_FTU1_TRG0               = 1U, /* Target trigger is FTU1_TRG0 */
    TRGSEL0_TARGET_FTU2_TRG0               = 2U, /* Target trigger is FTU2_TRG0 */
    TRGSEL0_TARGET_FTU3_TRG0               = 3U, /* Target trigger is FTU3_TRG0 */
    TRGSEL0_TARGET_FTU4_TRG0               = 4U, /* Target trigger is FTU4_TRG0 */
    TRGSEL0_TARGET_FTU5_TRG0               = 5U, /* Target trigger is FTU5_TRG0 */
    TRGSEL0_TARGET_PTIMER0_TRG0            = 6U, /* Target trigger is PTIMER0_TRG0 */
    TRGSEL0_TARGET_PTIMER1_TRG0            = 7U, /* Target trigger is PTIMER1_TRG0 */
    TRGSEL0_TARGET_FCPIT_TRG_CH0           = 12U, /* Target trigger is FCPIT_TRG_CH0 */
    TRGSEL0_TARGET_FCPIT_TRG_CH1           = 13U, /* Target trigger is FCPIT_TRG_CH1 */
    TRGSEL0_TARGET_FCPIT_TRG_CH2           = 14U, /* Target trigger is FCPIT_TRG_CH2 */
    TRGSEL0_TARGET_FCPIT_TRG_CH3           = 15U, /* Target trigger is FCPIT_TRG_CH3 */
    TRGSEL0_TARGET_AOTMR0_ALT0             = 16U, /* Target trigger is AOTMR0_ALT0 */
    TRGSEL0_TARGET_LU0_INPUT0A             = 17U, /* Target trigger is LU0_INPUT0A */
    TRGSEL0_TARGET_LU0_INPUT0B             = 18U, /* Target trigger is LU0_INPUT0B */
    TRGSEL0_TARGET_LU0_INPUT0C             = 19U, /* Target trigger is LU0_INPUT0C */
    TRGSEL0_TARGET_LU0_INPUT0D             = 20U, /* Target trigger is LU0_INPUT0D */
    TRGSEL0_TARGET_LU0_INPUT1A             = 21U, /* Target trigger is LU0_INPUT1A */
    TRGSEL0_TARGET_LU0_INPUT1B             = 22U, /* Target trigger is LU0_INPUT1B */
    TRGSEL0_TARGET_LU0_INPUT1C             = 23U, /* Target trigger is LU0_INPUT1C */
    TRGSEL0_TARGET_LU0_INPUT1D             = 24U, /* Target trigger is LU0_INPUT1D */
    TRGSEL0_TARGET_LU0_INPUT2A             = 25U, /* Target trigger is LU0_INPUT2A */
    TRGSEL0_TARGET_LU0_INPUT2B             = 26U, /* Target trigger is LU0_INPUT2B */
    TRGSEL0_TARGET_LU0_INPUT2C             = 27U, /* Target trigger is LU0_INPUT2C */
    TRGSEL0_TARGET_LU0_INPUT2D             = 28U, /* Target trigger is LU0_INPUT2D */
    TRGSEL0_TARGET_LU0_INPUT3A             = 29U, /* Target trigger is LU0_INPUT3A */
    TRGSEL0_TARGET_LU0_INPUT3B             = 30U, /* Target trigger is LU0_INPUT3B */
    TRGSEL0_TARGET_LU0_INPUT3C             = 31U, /* Target trigger is LU0_INPUT3C */
    TRGSEL0_TARGET_LU0_INPUT3D             = 32U, /* Target trigger is LU0_INPUT3D */
    TRGSEL0_TARGET_ADC0_TRG0               = 33U, /* Target trigger is ADC0_TRG0 */
    TRGSEL0_TARGET_ADC0_TRG1               = 34U, /* Target trigger is ADC0_TRG1 */
    TRGSEL0_TARGET_ADC0_TRG2               = 35U, /* Target trigger is ADC0_TRG2 */
    TRGSEL0_TARGET_ADC0_TRG3               = 36U, /* Target trigger is ADC0_TRG3 */
    TRGSEL0_TARGET_ADC1_TRG0               = 37U, /* Target trigger is ADC1_TRG0 */
    TRGSEL0_TARGET_ADC1_TRG1               = 38U, /* Target trigger is ADC1_TRG1 */
    TRGSEL0_TARGET_ADC1_TRG2               = 39U, /* Target trigger is ADC1_TRG2 */
    TRGSEL0_TARGET_ADC1_TRG3               = 40U, /* Target trigger is ADC1_TRG3 */
    TRGSEL0_TARGET_CMP0_SAMPLE_EN          = 41U, /* Target trigger is CMP0_SAMPLE_EN*/
    TRGSEL0_TARGET_CMP1_SAMPLE_EN          = 42U, /* Target trigger is CMP1_SAMPLE_EN*/
    TRGSEL0_TARGET_CMP2_SAMPLE_EN          = 43U, /* Target trigger is CMP2_SAMPLE_EN*/
    TRGSEL0_TARGET_TRGSEL1_INPUT0          = 44U, /* Target trigger is TRGSEL1_INPUT0 */
    TRGSEL0_TARGET_TRGSEL1_INPUT1          = 45U, /* Target trigger is TRGSEL1_INPUT1 */
    TRGSEL0_TARGET_TRGSEL1_INPUT2          = 46U, /* Target trigger is TRGSEL1_INPUT2 */
    TRGSEL0_TARGET_TRGSEL1_INPUT3          = 47U, /* Target trigger is TRGSEL1_INPUT3 */
    TRGSEL0_TARGET_FTU6_TRG0               = 52U, /* Target trigger is FTU6_TRG0 */
    TRGSEL0_TARGET_FTU7_TRG0               = 53U  /* Target trigger is FTU7_TRG0 */
} TrgSel0_TargetType;

/**
 * @brief TrgSel instance 1 trigger targets
 *
 */
typedef enum
{
    TRGSEL1_TARGET_DMA_CH0                 = 0U, /* Target trigger is DMA_CH0 */
    TRGSEL1_TARGET_DMA_CH1                 = 1U, /* Target trigger is DMA_CH1 */
    TRGSEL1_TARGET_DMA_CH2                 = 2U, /* Target trigger is DMA_CH2 */
    TRGSEL1_TARGET_DMA_CH3                 = 3U, /* Target trigger is DMA_CH3 */
    TRGSEL1_TARGET_TRGSEL_OUT0             = 4U, /* Target trigger is TRGSEL_OUT0 */
    TRGSEL1_TARGET_TRGSEL_OUT1             = 5U, /* Target trigger is TRGSEL_OUT1 */
    TRGSEL1_TARGET_TRGSEL_OUT2             = 6U, /* Target trigger is TRGSEL_OUT2 */
    TRGSEL1_TARGET_TRGSEL_OUT3             = 7U, /* Target trigger is TRGSEL_OUT3 */
    TRGSEL1_TARGET_TRGSEL_OUT4             = 8U, /* Target trigger is TRGSEL_OUT4 */
    TRGSEL1_TARGET_TRGSEL_OUT5             = 9U, /* Target trigger is TRGSEL_OUT5 */
    TRGSEL1_TARGET_TRGSEL_OUT6             = 10U, /* Target trigger is TRGSEL_OUT6 */
    TRGSEL1_TARGET_TRGSEL_OUT7             = 11U, /* Target trigger is TRGSEL_OUT7 */
    TRGSEL1_TARGET_FCUART0_TRG             = 12U, /* Target trigger is FCUART0_TRG */
    TRGSEL1_TARGET_FCUART1_TRG             = 13U, /* Target trigger is FCUART1_TRG */
    TRGSEL1_TARGET_FCUART2_TRG             = 14U, /* Target trigger is FCUART2_TRG */
    TRGSEL1_TARGET_FCSPI0_TRG              = 15U, /* Target trigger is FCSPI0_TRG */
    TRGSEL1_TARGET_FCSPI1_TRG              = 16U, /* Target trigger is FCSPI1_TRG */
    TRGSEL1_TARGET_FCSPI2_TRG              = 17U, /* Target trigger is FCSPI2_TRG */
    TRGSEL1_TARGET_FCIIC0_TRG              = 18U, /* Target trigger is FCIIC0_TRG */
    TRGSEL1_TARGET_FCIIC1_TRG              = 19U, /* Target trigger is FCIIC1_TRG */
    TRGSEL1_TARGET_HSM_TRG                 = 20U, /* Target trigger is HSM_TRG */
    TRGSEL1_TARGET_FCUART3_TRG             = 21U, /* Target trigger is FCUART3_TRG */
    TRGSEL1_TARGET_FCUART4_TRG             = 22U, /* Target trigger is FCUART4_TRG */
    TRGSEL1_TARGET_FCUART5_TRG             = 23U, /* Target trigger is FCUART5_TRG */
    TRGSEL1_TARGET_FCSPI3_TRG              = 24U  /* Target trigger is FCSPI3_TRG */
} TrgSel1_TargetType;

/**
 * @brief TrgSel instance 2 trigger targets
 *
 */
typedef enum
{
    TRGSEL2_TARGET_FTU0_FLT0               = 0U, /* Target trigger is FTU0 FLT0 */
    TRGSEL2_TARGET_FTU0_FLT1               = 1U, /* Target trigger is FTU0 FLT1 */
    TRGSEL2_TARGET_FTU0_FLT2               = 2U, /* Target trigger is FTU0 FLT2 */
    TRGSEL2_TARGET_FTU0_FLT3               = 3U, /* Target trigger is FTU0 FLT3 */
    TRGSEL2_TARGET_FTU1_FLT0               = 4U, /* Target trigger is FTU1 FLT0 */
    TRGSEL2_TARGET_FTU1_FLT1               = 5U, /* Target trigger is FTU1 FLT1 */
    TRGSEL2_TARGET_FTU1_FLT2               = 6U, /* Target trigger is FTU1 FLT2 */
    TRGSEL2_TARGET_FTU1_FLT3               = 7U, /* Target trigger is FTU1 FLT3 */
    TRGSEL2_TARGET_FTU2_FLT0               = 8U, /* Target trigger is FTU2 FLT0 */
    TRGSEL2_TARGET_FTU2_FLT1               = 9U, /* Target trigger is FTU2 FLT1 */
    TRGSEL2_TARGET_FTU2_FLT2               = 10U, /* Target trigger is FTU2 FLT2 */
    TRGSEL2_TARGET_FTU2_FLT3               = 11U, /* Target trigger is FTU2 FLT3 */
    TRGSEL2_TARGET_FTU3_FLT0               = 12U, /* Target trigger is FTU3 FLT0 */
    TRGSEL2_TARGET_FTU3_FLT1               = 13U, /* Target trigger is FTU3 FLT1 */
    TRGSEL2_TARGET_FTU3_FLT2               = 14U, /* Target trigger is FTU3 FLT2 */
    TRGSEL2_TARGET_FTU3_FLT3               = 15U, /* Target trigger is FTU3 FLT3 */
    TRGSEL2_TARGET_FTU4_FLT0               = 16U, /* Target trigger is FTU4 FLT0 */
    TRGSEL2_TARGET_FTU4_FLT1               = 17U, /* Target trigger is FTU4 FLT1 */
    TRGSEL2_TARGET_FTU5_FLT0               = 20U, /* Target trigger is FTU5 FLT0 */
    TRGSEL2_TARGET_FTU5_FLT1               = 21U, /* Target trigger is FTU5 FLT1 */
    TRGSEL2_TARGET_FTU0_TRG2               = 24U, /* Target trigger is FTU0 TRG2 */
    TRGSEL2_TARGET_FTU1_TRG2               = 25U, /* Target trigger is FTU1 TRG2 */
    TRGSEL2_TARGET_FTU2_TRG2               = 26U, /* Target trigger is FTU2 TRG2 */
    TRGSEL2_TARGET_FTU3_TRG2               = 27U, /* Target trigger is FTU3 TRG2 */
    TRGSEL2_TARGET_FTU4_TRG2               = 28U, /* Target trigger is FTU4 TRG2 */
    TRGSEL2_TARGET_FTU5_TRG2               = 29U, /* Target trigger is FTU5 TRG2 */

    TRGSEL2_TARGET_FTU6_FLT0               = 30U, /* Target trigger is FTU6 FLT0 */
    TRGSEL2_TARGET_FTU6_FLT1               = 31U, /* Target trigger is FTU6 FLT1 */
    TRGSEL2_TARGET_FTU6_FLT2               = 32U, /* Target trigger is FTU6 FLT2 */
    TRGSEL2_TARGET_FTU6_FLT3               = 33U, /* Target trigger is FTU6 FLT3 */
    TRGSEL2_TARGET_FTU7_FLT0               = 34U, /* Target trigger is FTU7 FLT0 */
    TRGSEL2_TARGET_FTU7_FLT1               = 35U, /* Target trigger is FTU7 FLT1 */
    TRGSEL2_TARGET_FTU7_FLT2               = 36U, /* Target trigger is FTU7 FLT2 */
    TRGSEL2_TARGET_FTU7_FLT3               = 37U, /* Target trigger is FTU7 FLT3 */
    TRGSEL2_TARGET_FTU6_TRG2               = 38U, /* Target trigger is FTU6 TRG2 */
    TRGSEL2_TARGET_FTU7_TRG2               = 39U, /* Target trigger is FTU7 TRG2 */
//  TRGSEL2_TARGET_CAN_RX                  = 40U, /* Target trigger is CAN RX */
} TrgSel2_TargetType;

/**
 * @brief TrgSel instance 3 trigger targets
 *
 */
typedef enum
{
    TRGSEL3_TARGET_ISM0_MON0               = 0U, /* Target trigger is ISM0 MON0 */
    TRGSEL3_TARGET_ISM0_MON1               = 1U, /* Target trigger is ISM0 MON1 */
    TRGSEL3_TARGET_ISM0_MON2               = 2U, /* Target trigger is ISM0 MON2 */
    TRGSEL3_TARGET_ISM0_MON3               = 3U, /* Target trigger is ISM0 MON3 */
    TRGSEL3_TARGET_ISM0_MON4               = 4U, /* Target trigger is ISM0 MON4 */
    TRGSEL3_TARGET_ISM0_MON5               = 5U, /* Target trigger is ISM0 MON5 */
    TRGSEL3_TARGET_ISM0_MON6               = 6U, /* Target trigger is ISM0 MON6 */
    TRGSEL3_TARGET_ISM0_MON7               = 7U, /* Target trigger is ISM0 MON7 */
    TRGSEL3_TARGET_ISM0_REF0               = 8U, /* Target trigger is ISM0 REF0 */
    TRGSEL3_TARGET_ISM0_REF1               = 9U, /* Target trigger is ISM0 REF1 */
    TRGSEL3_TARGET_ISM0_REF2               = 10U, /* Target trigger is ISM0 REF2 */
    TRGSEL3_TARGET_ISM0_REF3               = 11U, /* Target trigger is ISM0 REF3 */
    TRGSEL3_TARGET_ISM0_REF4               = 12U, /* Target trigger is ISM0 REF4 */
    TRGSEL3_TARGET_ISM0_REF5               = 13U, /* Target trigger is ISM0 REF5 */
    TRGSEL3_TARGET_ISM0_REF6               = 14U, /* Target trigger is ISM0 REF6 */
    TRGSEL3_TARGET_ISM0_REF7               = 15U  /* Target trigger is ISM0 REF7 */
} TrgSel3_TargetType;

/**
 * @brief TrgSel instance 0 trigger sources
 *
 */
typedef enum
{
    TRGSEL0_SRC_VSS                        = 0U, /* Source trigger is VSS */
    TRGSEL0_SRC_VDD                        = 1U, /* Source trigger is VDD */
    TRGSEL0_SRC_SMISC_SW_TRG0              = 2U, /* Source trigger is SMISC_SW_TRG0 */
    TRGSEL0_SRC_SMISC_SW_TRG1              = 3U, /* Source trigger is SMISC_SW_TRG1 */
    TRGSEL0_SRC_SMISC_SW_TRG2              = 4U, /* Source trigger is SMISC_SW_TRG2 */
    TRGSEL0_SRC_SMISC_SW_TRG3              = 5U, /* Source trigger is SMISC_SW_TRG3 */
    TRGSEL0_SRC_TRGSEL_IN0                 = 6U, /* Source trigger is TRGSEL_IN0 */
    TRGSEL0_SRC_TRGSEL_IN1                 = 7U, /* Source trigger is TRGSEL_IN1 */
    TRGSEL0_SRC_TRGSEL_IN2                 = 8U, /* Source trigger is TRGSEL_IN2 */
    TRGSEL0_SRC_TRGSEL_IN3                 = 9U, /* Source trigger is TRGSEL_IN3 */
    TRGSEL0_SRC_TRGSEL_IN4                 = 10U,/* Source trigger is TRGSEL_IN4 */
    TRGSEL0_SRC_TRGSEL_IN5                 = 11U,/* Source trigger is TRGSEL_IN5 */
    TRGSEL0_SRC_TRGSEL_IN6                 = 12U,/* Source trigger is TRGSEL_IN6 */
    TRGSEL0_SRC_TRGSEL_IN7                 = 13U,/* Source trigger is TRGSEL_IN7 */
    TRGSEL0_SRC_TRGSEL_IN8                 = 14U,/* Source trigger is TRGSEL_IN8 */
    TRGSEL0_SRC_TRGSEL_IN9                 = 15U,/* Source trigger is TRGSEL_IN9 */
    TRGSEL0_SRC_TRGSEL_IN10                = 16U,/* Source trigger is TRGSEL_IN10 */
    TRGSEL0_SRC_TRGSEL_IN11                = 17U,/* Source trigger is TRGSEL_IN11 */
    TRGSEL0_SRC_TRGSEL_IN12                = 18U,/* Source trigger is TRGSEL_IN12 */
    TRGSEL0_SRC_TRGSEL_IN13                = 19U,/* Source trigger is TRGSEL_IN13 */
    TRGSEL0_SRC_TRGSEL_IN14                = 20U,/* Source trigger is TRGSEL_IN14 */
    TRGSEL0_SRC_CMP0_OUT                   = 22U,/* Source trigger is CMP0_OUT */
    TRGSEL0_SRC_CMP1_OUT                   = 23U,/* Source trigger is CMP1_OUT */
    TRGSEL0_SRC_CMP2_OUT                   = 24U,/* Source trigger is CMP2_OUT */
    TRGSEL0_SRC_FCPIT_CH0                  = 25U,/* Source trigger is FCPIT_CH0 */
    TRGSEL0_SRC_FCPIT_CH1                  = 26U,/* Source trigger is FCPIT_CH1 */
    TRGSEL0_SRC_FCPIT_CH2                  = 27U,/* Source trigger is FCPIT_CH2 */
    TRGSEL0_SRC_FCPIT_CH3                  = 28U,/* Source trigger is FCPIT_CH3 */
    TRGSEL0_SRC_AONTIMER0                  = 29U,/* Source trigger is AONTIMER0 */
    TRGSEL0_SRC_FTU0_RELOAD_TRG            = 30U,/* Source trigger is FTU0_RELOAD_TRG */
    TRGSEL0_SRC_FTU0_MATCH_TRG             = 31U,/* Source trigger is FTU0_MATCH_TRG */
    TRGSEL0_SRC_FTU1_RELOAD_TRG            = 32U,/* Source trigger is FTU1_RELOAD_TRG */
    TRGSEL0_SRC_FTU1_MATCH_TRG             = 33U,/* Source trigger is FTU1_MATCH_TRG */
    TRGSEL0_SRC_FTU2_RELOAD_TRG            = 34U,/* Source trigger is FTU2_RELOAD_TRG */
    TRGSEL0_SRC_FTU2_MATCH_TRG             = 35U,/* Source trigger is FTU2_MATCH_TRG */
    TRGSEL0_SRC_FTU3_RELOAD_TRG            = 36U,/* Source trigger is FTU3_RELOAD_TRG */
    TRGSEL0_SRC_FTU3_MATCH_TRG             = 37U,/* Source trigger is FTU3_MATCH_TRG */
    TRGSEL0_SRC_FTU4_RELOAD_TRG            = 38U,/* Source trigger is FTU4_RELOAD_TRG */
    TRGSEL0_SRC_FTU4_MATCH_TRG             = 39U,/* Source trigger is FTU4_MATCH_TRG */
    TRGSEL0_SRC_FTU5_RELOAD_TRG            = 40U,/* Source trigger is FTU5_RELOAD_TRG */
    TRGSEL0_SRC_FTU5_MATCH_TRG             = 41U,/* Source trigger is FTU5_MATCH_TRG */
    TRGSEL0_SRC_LU0_OUT0A                  = 42U,/* Source trigger is LU0_OUT0A */
    TRGSEL0_SRC_LU0_OUT1A                  = 43U,/* Source trigger is LU0_OUT1A */
    TRGSEL0_SRC_LU0_OUT2A                  = 44U,/* Source trigger is LU0_OUT2A */
    TRGSEL0_SRC_LU0_OUT3A                  = 45U,/* Source trigger is LU0_OUT3A */
    TRGSEL0_SRC_LU0_OUT0B                  = 46U,/* Source trigger is LU0_OUT0B */
    TRGSEL0_SRC_LU0_OUT1B                  = 47U,/* Source trigger is LU0_OUT1B */
    TRGSEL0_SRC_LU0_OUT2B                  = 48U,/* Source trigger is LU0_OUT2B */
    TRGSEL0_SRC_LU0_OUT3B                  = 49U,/* Source trigger is LU0_OUT3B */
    TRGSEL0_SRC_PTIMER0_ADCCH0_TRG         = 50U,/* Source trigger is PTIMER0_ADCCH0_TRG */
    TRGSEL0_SRC_PTIMER0_PULSE_OUT          = 51U,/* Source trigger is PTIMER0_PULSE_OUT */
    TRGSEL0_SRC_PTIMER1_ADCCH0_TRG         = 52U,/* Source trigger is PTIMER1_ADCCH0_TRG */
    TRGSEL0_SRC_PTIMER1_PULSE_OUT          = 53U,/* Source trigger is PTIMER1_PULSE_OUT */
    TRGSEL0_SRC_RTC_ALARM                  = 54U,/* Source trigger is RTC_ALARM */
    TRGSEL0_SRC_RTC_SECOND                 = 55U,/* Source trigger is RTC_SECOND */
    TRGSEL0_SRC_ADC0_COCO0                 = 60U,/* Source trigger is ADC0_COCO0 */
    TRGSEL0_SRC_ADC0_COCO1                 = 61U,/* Source trigger is ADC0_COCO1 */
    TRGSEL0_SRC_ADC1_COCO0                 = 62U,/* Source trigger is ADC1_COCO0 */
    TRGSEL0_SRC_ADC1_COCO1                 = 63U,/* Source trigger is ADC1_COCO1 */
    TRGSEL0_SRC_GPIOA_TRG                  = 64U,/* Source trigger is GPIOA_TRG */
    TRGSEL0_SRC_GPIOB_TRG                  = 65U,/* Source trigger is GPIOB_TRG */
    TRGSEL0_SRC_GPIOC_TRG                  = 66U,/* Source trigger is GPIOC_TRG */
    TRGSEL0_SRC_GPIOD_TRG                  = 67U,/* Source trigger is GPIOD_TRG */
    TRGSEL0_SRC_GPIOE_TRG                  = 68U,/* Source trigger is GPIOE_TRG */
    TRGSEL0_SRC_FTU0_CH0_OUT               = 69U,/* Source trigger is FTU0_CH0_OUT */
    TRGSEL0_SRC_FTU0_CH1_OUT               = 70U,/* Source trigger is FTU0_CH1_OUT */
    TRGSEL0_SRC_FTU0_CH2_OUT               = 71U,/* Source trigger is FTU0_CH2_OUT */
    TRGSEL0_SRC_FTU0_CH3_OUT               = 72U,/* Source trigger is FTU0_CH3_OUT */
    TRGSEL0_SRC_FTU0_CH4_OUT               = 73U,/* Source trigger is FTU0_CH4_OUT */
    TRGSEL0_SRC_FTU0_CH5_OUT               = 74U,/* Source trigger is FTU0_CH5_OUT */
    TRGSEL0_SRC_FTU0_CH6_OUT               = 75U,/* Source trigger is FTU0_CH6_OUT */
    TRGSEL0_SRC_FTU0_CH7_OUT               = 76U,/* Source trigger is FTU0_CH7_OUT */
    TRGSEL0_SRC_FTU1_CH0_OUT               = 77U,/* Source trigger is FTU1_CH0_OUT */
    TRGSEL0_SRC_FTU1_CH1_OUT               = 78U,/* Source trigger is FTU1_CH1_OUT */
    TRGSEL0_SRC_FTU1_CH2_OUT               = 79U,/* Source trigger is FTU1_CH2_OUT */
    TRGSEL0_SRC_FTU1_CH3_OUT               = 80U,/* Source trigger is FTU1_CH3_OUT */
    TRGSEL0_SRC_FTU1_CH4_OUT               = 81U,/* Source trigger is FTU1_CH4_OUT */
    TRGSEL0_SRC_FTU1_CH5_OUT               = 82U,/* Source trigger is FTU1_CH5_OUT */
    TRGSEL0_SRC_FTU1_CH6_OUT               = 83U,/* Source trigger is FTU1_CH6_OUT */
    TRGSEL0_SRC_FTU1_CH7_OUT               = 84U,/* Source trigger is FTU1_CH7_OUT */
    TRGSEL0_SRC_FTU2_CH0_OUT               = 85U,/* Source trigger is FTU2_CH0_OUT */
    TRGSEL0_SRC_FTU2_CH1_OUT               = 86U,/* Source trigger is FTU2_CH1_OUT */
    TRGSEL0_SRC_FTU2_CH2_OUT               = 87U,/* Source trigger is FTU2_CH2_OUT */
    TRGSEL0_SRC_FTU2_CH3_OUT               = 88U,/* Source trigger is FTU2_CH3_OUT */
    TRGSEL0_SRC_FTU2_CH4_OUT               = 89U,/* Source trigger is FTU2_CH4_OUT */
    TRGSEL0_SRC_FTU2_CH5_OUT               = 90U,/* Source trigger is FTU2_CH5_OUT */
    TRGSEL0_SRC_FTU2_CH6_OUT               = 91U,/* Source trigger is FTU2_CH6_OUT */
    TRGSEL0_SRC_FTU2_CH7_OUT               = 92U,/* Source trigger is FTU2_CH7_OUT */
//    TRGSEL0_SRC_ENET_PPS0                  = 93U,/* Source trigger is ENET_PPS0 */
//    TRGSEL0_SRC_ENET_PPS1                  = 94U,/* Source trigger is ENET_PPS1 */
//    TRGSEL0_SRC_ENET_PPS2                  = 95U,/* Source trigger is ENET_PPS2 */
//    TRGSEL0_SRC_ENET_PPS3                  = 96U,/* Source trigger is ENET_PPS3 */
//    TRGSEL0_SRC_FTU6_RELOAD_TRG            = 101U,/* Source trigger is FTU6_RELOAD_TRG */
//    TRGSEL0_SRC_FTU6_MATCH_TRG             = 102U,/* Source trigger is FTU6_MATCH_TRG */
//    TRGSEL0_SRC_FTU7_RELOAD_TRG            = 103U,/* Source trigger is FTU7_RELOAD_TRG */
//    TRGSEL0_SRC_FTU7_MATCH_TRG             = 104U/* Source trigger is FTU7_MATCH_TRG */
} TrgSel0_SourceType;

/**
 * @brief TrgSel instance 1 trigger sources
 *
 */
typedef enum
{
    TRGSEL1_SRC_VSS                        = 0U, /* Source trigger is VSS */
    TRGSEL1_SRC_VDD                        = 1U, /* Source trigger is VDD */
    TRGSEL1_SRC_SMISC_SW_TRG4              = 2U, /* Source trigger is SMISC_SW_TRG4 */
    TRGSEL1_SRC_SMISC_SW_TRG5              = 3U, /* Source trigger is SMISC_SW_TRG5 */
    TRGSEL1_SRC_SMISC_SW_TRG6              = 4U, /* Source trigger is SMISC_SW_TRG6 */
    TRGSEL1_SRC_SMISC_SW_TRG7              = 5U, /* Source trigger is SMISC_SW_TRG7 */
    TRGSEL1_SRC_TRGSEL_IN0                 = 6U, /* Source trigger is TRGSEL_IN0 */
    TRGSEL1_SRC_TRGSEL_IN1                 = 7U, /* Source trigger is TRGSEL_IN1 */
    TRGSEL1_SRC_TRGSEL_IN2                 = 8U, /* Source trigger is TRGSEL_IN2 */
    TRGSEL1_SRC_TRGSEL_IN3                 = 9U, /* Source trigger is TRGSEL_IN3 */
    TRGSEL1_SRC_TRGSEL_IN4                 = 10U, /* Source trigger is TRGSEL_IN4 */
    TRGSEL1_SRC_TRGSEL_IN5                 = 11U, /* Source trigger is TRGSEL_IN5 */
    TRGSEL1_SRC_TRGSEL_IN6                 = 12U, /* Source trigger is TRGSEL_IN6 */
    TRGSEL1_SRC_TRGSEL_IN7                 = 13U, /* Source trigger is TRGSEL_IN7 */
    TRGSEL1_SRC_TRGSEL_IN8                 = 14U, /* Source trigger is TRGSEL_IN8 */
    TRGSEL1_SRC_TRGSEL_IN9                 = 15U, /* Source trigger is TRGSEL_IN9 */
    TRGSEL1_SRC_TRGSEL_IN10                = 16U, /* Source trigger is TRGSEL_IN10 */
    TRGSEL1_SRC_TRGSEL_IN11                = 17U, /* Source trigger is TRGSEL_IN11 */
    TRGSEL1_SRC_TRGSEL_IN12                = 18U, /* Source trigger is TRGSEL_IN12 */
    TRGSEL1_SRC_TRGSEL_IN13                = 19U, /* Source trigger is TRGSEL_IN13 */
    TRGSEL1_SRC_TRGSEL_IN14                = 20U, /* Source trigger is TRGSEL_IN14 */
    TRGSEL1_SRC_CMP0_OUT                   = 22U, /* Source trigger is CMP0_OUT */
    TRGSEL1_SRC_CMP1_OUT                   = 23U, /* Source trigger is CMP1_OUT */
    TRGSEL1_SRC_CMP2_OUT                   = 24U, /* Source trigger is CMP2_OUT */
    TRGSEL1_SRC_FCPIT_CH0                  = 25U, /* Source trigger is FCPIT_CH0 */
    TRGSEL1_SRC_FCPIT_CH1                  = 26U, /* Source trigger is FCPIT_CH1 */
    TRGSEL1_SRC_FCPIT_CH2                  = 27U, /* Source trigger is FCPIT_CH2 */
    TRGSEL1_SRC_FCPIT_CH3                  = 28U, /* Source trigger is FCPIT_CH3 */
    TRGSEL1_SRC_AONTIMER0                  = 29U, /* Source trigger is AONTIMER0 */
    TRGSEL1_SRC_FTU0_RELOAD_TRG            = 30U, /* Source trigger is FTU0_RELOAD_TRG */
    TRGSEL1_SRC_FTU0_MATCH_TRG             = 31U, /* Source trigger is FTU0_MATCH_TRG */
    TRGSEL1_SRC_FTU1_RELOAD_TRG            = 32U, /* Source trigger is FTU1_RELOAD_TRG */
    TRGSEL1_SRC_FTU1_MATCH_TRG             = 33U, /* Source trigger is FTU1_MATCH_TRG */
    TRGSEL1_SRC_FTU2_RELOAD_TRG            = 34U, /* Source trigger is FTU2_RELOAD_TRG */
    TRGSEL1_SRC_FTU2_MATCH_TRG             = 35U, /* Source trigger is FTU2_MATCH_TRG */
    TRGSEL1_SRC_FTU3_RELOAD_TRG            = 36U, /* Source trigger is FTU3_RELOAD_TRG */
    TRGSEL1_SRC_FTU3_MATCH_TRG             = 37U, /* Source trigger is FTU3_MATCH_TRG */
    TRGSEL1_SRC_FTU4_RELOAD_TRG            = 38U, /* Source trigger is FTU4_RELOAD_TRG */
    TRGSEL1_SRC_FTU4_MATCH_TRG             = 39U, /* Source trigger is FTU4_MATCH_TRG */
    TRGSEL1_SRC_FTU5_RELOAD_TRG            = 40U, /* Source trigger is FTU5_RELOAD_TRG */
    TRGSEL1_SRC_FTU5_MATCH_TRG             = 41U, /* Source trigger is FTU5_MATCH_TRG */
    TRGSEL1_SRC_LU_OUT0A                   = 42U, /* Source trigger is LU_OUT0A */
    TRGSEL1_SRC_LU_OUT1A                   = 43U, /* Source trigger is LU_OUT1A */
    TRGSEL1_SRC_LU_OUT2A                   = 44U, /* Source trigger is LU_OUT2A */
    TRGSEL1_SRC_LU_OUT3A                   = 45U, /* Source trigger is LU_OUT3A */
    TRGSEL1_SRC_LU_OUT0B                   = 46U, /* Source trigger is LU_OUT0B */
    TRGSEL1_SRC_LU_OUT1B                   = 47U, /* Source trigger is LU_OUT1B */
    TRGSEL1_SRC_LU_OUT2B                   = 48U, /* Source trigger is LU_OUT2B */
    TRGSEL1_SRC_LU_OUT3B                   = 49U, /* Source trigger is LU_OUT3B */
    TRGSEL1_SRC_PTIMER0_ADCCH0_TRIG        = 50U, /* Source trigger is PTIMER0_ADCCH0_TRIG */
    TRGSEL1_SRC_PTIMER0_PULSE_OUT          = 51U, /* Source trigger is PTIMER0_PULSE_OUT */
    TRGSEL1_SRC_PTIMER1_ADCCH0_TRIG        = 52U, /* Source trigger is PTIMER1_ADCCH0_TRIG */
    TRGSEL1_SRC_PTIMER1_PULSE_OUT          = 53U, /* Source trigger is PTIMER1_PULSE_OUT */
    TRGSEL1_SRC_RTC_ALARM                  = 54U, /* Source trigger is RTC_ALARM */
    TRGSEL1_SRC_RTC_SECOND                 = 55U, /* Source trigger is RTC_SECOND */
    TRGSEL1_SRC_ADC0_COCO0                 = 60U, /* Source trigger is ADC0_COCO0 */
    TRGSEL1_SRC_ADC0_COCO1                 = 61U, /* Source trigger is ADC0_COCO1 */
    TRGSEL1_SRC_ADC1_COCO0                 = 62U, /* Source trigger is ADC1_COCO0 */
    TRGSEL1_SRC_ADC1_COCO1                 = 63U, /* Source trigger is ADC1_COCO1 */
    TRGSEL1_SRC_GPIOA_TRG                  = 64U, /* Source trigger is GPIOA_TRG */
    TRGSEL1_SRC_GPIOB_TRG                  = 65U, /* Source trigger is GPIOB_TRG */
    TRGSEL1_SRC_GPIOC_TRG                  = 66U, /* Source trigger is GPIOC_TRG */
    TRGSEL1_SRC_GPIOD_TRG                  = 67U, /* Source trigger is GPIOD_TRG */
    TRGSEL1_SRC_GPIOE_TRG                  = 68U, /* Source trigger is GPIOE_TRG */
    TRGSEL1_SRC_FCUART0_RX_DONE            = 69U, /* Source trigger is FCUART0_RX_DONE */
    TRGSEL1_SRC_FCUART0_TX_DONE            = 70U, /* Source trigger is FCUART0_TX_DONE */
    TRGSEL1_SRC_FCUART0_RX_IDLE            = 71U, /* Source trigger is FCUART0_RX_IDLE */
    TRGSEL1_SRC_FCUART1_RX_DONE            = 72U, /* Source trigger is FCUART1_RX_DONE */
    TRGSEL1_SRC_FCUART1_TX_DONE            = 73U, /* Source trigger is FCUART1_TX_DONE */
    TRGSEL1_SRC_FCUART1_RX_IDLE            = 74U, /* Source trigger is FCUART1_RX_IDLE */
    TRGSEL1_SRC_FCUART2_RX_DONE            = 75U, /* Source trigger is FCUART2_RX_DONE */
    TRGSEL1_SRC_FCUART2_TX_DONE            = 76U, /* Source trigger is FCUART2_TX_DONE */
    TRGSEL1_SRC_FCUART2_RX_IDLE            = 77U, /* Source trigger is FCUART2_RX_IDLE */
    TRGSEL1_SRC_FCIIC0_MASTER_TRG          = 78U, /* Source trigger is FCIIC0_MASTER_TRG */
    TRGSEL1_SRC_FCIIC0_SLAVE_TRG           = 79U, /* Source trigger is FCIIC0_SLAVE_TRG */
    TRGSEL1_SRC_FCIIC1_MASTER_TRG          = 80U, /* Source trigger is FCIIC1_MASTER_TRG */
    TRGSEL1_SRC_FCIIC1_SLAVE_TRG           = 81U, /* Source trigger is FCIIC1_SLAVE_TRG */
    TRGSEL1_SRC_FCSPI0_FRAME               = 82U, /* Source trigger is FCSPI0_FRAME */
    TRGSEL1_SRC_FCSPI0_RX_DONE             = 83U, /* Source trigger is FCSPI0_RX_DONE */
    TRGSEL1_SRC_FCSPI1_FRAME               = 84U, /* Source trigger is FCSPI1_FRAME */
    TRGSEL1_SRC_FCSPI1_RX_DONE             = 85U, /* Source trigger is FCSPI1_RX_DONE */
    TRGSEL1_SRC_FCSPI2_FRAME               = 86U, /* Source trigger is FCSPI2_FRAME */
    TRGSEL1_SRC_FCSPI2_RX_DONE             = 87U, /* Source trigger is FCSPI2_RX_DONE */
    TRGSEL1_SRC_TRGSEL1_INPUT0             = 88U, /* Source trigger is TRGSEL1_INPUT0 */
    TRGSEL1_SRC_TRGSEL1_INPUT1             = 89U, /* Source trigger is TRGSEL1_INPUT1 */
    TRGSEL1_SRC_TRGSEL1_INPUT2             = 90U, /* Source trigger is TRGSEL1_INPUT2 */
    TRGSEL1_SRC_TRGSEL1_INPUT3             = 91U, /* Source trigger is TRGSEL1_INPUT3 */
//    TRGSEL1_SRC_ENET_PPS0                  = 92U, /* Source trigger is ENET_PPS0 */
//    TRGSEL1_SRC_ENET_PPS1                  = 93U, /* Source trigger is ENET_PPS1 */
//    TRGSEL1_SRC_ENET_PPS2                  = 94U, /* Source trigger is ENET_PPS2 */
//    TRGSEL1_SRC_ENET_PPS3                  = 95U, /* Source trigger is ENET_PPS3 */
    TRGSEL1_SRC_FCUART3_RX_DONE            = 100U, /* Source trigger is FCUART3_RX_DONE */
    TRGSEL1_SRC_FCUART3_TX_DONE            = 101U, /* Source trigger is FCUART3_TX_DONE */
    TRGSEL1_SRC_FCUART3_RX_IDLE            = 102U, /* Source trigger is FCUART3_RX_IDLE */
    TRGSEL1_SRC_FCUART4_RX_DONE            = 103U, /* Source trigger is FCUART4_RX_DONE */
    TRGSEL1_SRC_FCUART4_TX_DONE            = 104U, /* Source trigger is FCUART4_TX_DONE */
    TRGSEL1_SRC_FCUART4_RX_IDLE            = 105U, /* Source trigger is FCUART4_RX_IDLE */
    TRGSEL1_SRC_FCUART5_RX_DONE            = 106U, /* Source trigger is FCUART5_RX_DONE */
    TRGSEL1_SRC_FCUART5_TX_DONE            = 107U, /* Source trigger is FCUART5_TX_DONE */
    TRGSEL1_SRC_FCUART5_RX_IDLE            = 108U, /* Source trigger is FCUART5_RX_IDLE */
    TRGSEL1_SRC_FCSPI3_FRAME               = 109U, /* Source trigger is FCSPI3_FRAME */
    TRGSEL1_SRC_FCSPI3_RX_DONE             = 110U, /* Source trigger is FCSPI3_RX_DONE */
//    TRGSEL1_SRC_FTU6_RELOAD_TRG            = 111U, /* Source trigger is FTU6_RELOAD_TRG */
//    TRGSEL1_SRC_FTU6_MATCH_TRG             = 112U, /* Source trigger is FTU6_MATCH_TRG */
//    TRGSEL1_SRC_FTU7_RELOAD_TRG            = 113U, /* Source trigger is FTU7_RELOAD_TRG */
//    TRGSEL1_SRC_FTU7_MATCH_TRG             = 114U /* Source trigger is FTU7_MATCH_TRG */
} TrgSel1_SourceType;

/**
 * @brief TrgSel instance 2 trigger sources
 *
 */
typedef enum
{
    TRGSEL2_SRC_VSS                        = 0U, /*Source trigger is VSS*/
    TRGSEL2_SRC_VDD                        = 1U, /*Source trigger is VDD*/
    TRGSEL2_SRC_TRGSEL_OUT0                = 2U, /*Source trigger is TRGSEL_OUT0*/
    TRGSEL2_SRC_TRGSEL_OUT1                = 3U, /*Source trigger is TRGSEL_OUT1*/
    TRGSEL2_SRC_TRGSEL_OUT2                = 4U, /*Source trigger is TRGSEL_OUT2*/
    TRGSEL2_SRC_TRGSEL_OUT3                = 5U, /*Source trigger is TRGSEL_OUT3*/
    TRGSEL2_SRC_TRGSEL_OUT4                = 6U, /*Source trigger is TRGSEL_OUT4*/
    TRGSEL2_SRC_TRGSEL_OUT5                = 7U, /*Source trigger is TRGSEL_OUT5*/
    TRGSEL2_SRC_TRGSEL_OUT6                = 8U, /*Source trigger is TRGSEL_OUT6*/
    TRGSEL2_SRC_TRGSEL_OUT7                = 9U, /*Source trigger is TRGSEL_OUT7*/
    TRGSEL2_SRC_FTU_FLT0                   = 10U, /*Source trigger is FTU_FLT0*/
    TRGSEL2_SRC_FTU_FLT1                   = 11U, /*Source trigger is FTU_FLT1*/
    TRGSEL2_SRC_FTU_FLT2                   = 12U, /*Source trigger is FTU_FLT2*/
    TRGSEL2_SRC_FTU_FLT3                   = 13U, /*Source trigger is FTU_FLT3*/
    TRGSEL2_SRC_FTU_FLT4                   = 14U, /*Source trigger is FTU_FLT4*/
    TRGSEL2_SRC_FTU_FLT5                   = 15U, /*Source trigger is FTU_FLT5*/
    TRGSEL2_SRC_FTU_FLT6                   = 16U, /*Source trigger is FTU_FLT6*/
    TRGSEL2_SRC_FTU_FLT7                   = 17U, /*Source trigger is FTU_FLT7*/
    TRGSEL2_SRC_FTU_FLT8                   = 18U, /*Source trigger is FTU_FLT8*/
    TRGSEL2_SRC_FTU_FLT9                   = 19U, /*Source trigger is FTU_FLT9*/
    TRGSEL2_SRC_FTU_FLT10                  = 20U, /*Source trigger is FTU_FLT10*/
    TRGSEL2_SRC_FTU_FLT11                  = 21U, /*Source trigger is FTU_FLT11*/
    TRGSEL2_SRC_FTU_FLT12                  = 22U, /*Source trigger is FTU_FLT12*/
    TRGSEL2_SRC_FTU_FLT13                  = 23U, /*Source trigger is FTU_FLT13*/
    TRGSEL2_SRC_FTU_FLT14                  = 24U, /*Source trigger is FTU_FLT14*/
    TRGSEL2_SRC_FTU_FLT15                  = 25U, /*Source trigger is FTU_FLT15*/
    TRGSEL2_SRC_FTU_FLT16                  = 26U, /*Source trigger is FTU_FLT16*/
    TRGSEL2_SRC_FTU_FLT17                  = 27U, /*Source trigger is FTU_FLT17*/
    TRGSEL2_SRC_FTU_FLT18                  = 28U, /*Source trigger is FTU_FLT18*/
    TRGSEL2_SRC_FTU_FLT19                  = 29U, /*Source trigger is FTU_FLT19*/
    TRGSEL2_SRC_FTU_FLT20                  = 30U, /*Source trigger is FTU_FLT20*/
    TRGSEL2_SRC_FTU_FLT21                  = 31U /*Source trigger is FTU_FLT21*/
} TrgSel2_SourceType;

/**
 * @brief TrgSel instance 3 trigger sources
 *
 */
typedef enum
{
    TRGSEL3_SRC_VSS                        = 0U, /*Source trigger is VSS*/
    TRGSEL3_SRC_VDD                        = 1U, /*Source trigger is VDD*/
    TRGSEL3_SRC_TRGSEL_OUT0                = 2U, /*Source trigger is TRGSEL_OUT0*/
    TRGSEL3_SRC_TRGSEL_OUT1                = 3U, /*Source trigger is TRGSEL_OUT1*/
    TRGSEL3_SRC_TRGSEL_OUT2                = 4U, /*Source trigger is TRGSEL_OUT2*/
    TRGSEL3_SRC_TRGSEL_OUT3                = 5U, /*Source trigger is TRGSEL_OUT3*/
    TRGSEL3_SRC_TRGSEL_OUT4                = 6U, /*Source trigger is TRGSEL_OUT4*/
    TRGSEL3_SRC_TRGSEL_OUT5                = 7U, /*Source trigger is TRGSEL_OUT5*/
    TRGSEL3_SRC_TRGSEL_OUT6                = 8U, /*Source trigger is TRGSEL_OUT6*/
    TRGSEL3_SRC_TRGSEL_OUT7                = 9U, /*Source trigger is TRGSEL_OUT7*/
    TRGSEL3_SRC_PTA2_IN                    = 10U, /*Source trigger is PTA2_IN*/
    TRGSEL3_SRC_PTA3_IN                    = 11U, /*Source trigger is PTA3_IN*/
    TRGSEL3_SRC_PTA9_IN                    = 12U, /*Source trigger is PTA9_IN*/
    TRGSEL3_SRC_PTA10_IN                   = 13U, /*Source trigger is PTA10_IN*/
    TRGSEL3_SRC_PTA11_IN                   = 14U, /*Source trigger is PTA11_IN*/
    TRGSEL3_SRC_PTA12_IN                   = 15U, /*Source trigger is PTA12_IN*/
    TRGSEL3_SRC_PTA14_IN                   = 16U, /*Source trigger is PTA14_IN*/
    TRGSEL3_SRC_PTA30_IN                   = 17U, /*Source trigger is PTA30_IN*/
    TRGSEL3_SRC_PTB4_IN                    = 18U, /*Source trigger is PTB4_IN*/
    TRGSEL3_SRC_PTB5_IN                    = 19U, /*Source trigger is PTB5_IN*/
    TRGSEL3_SRC_PTB12_IN                   = 20U, /*Source trigger is PTB12_IN*/
    TRGSEL3_SRC_PTB13_IN                   = 21U, /*Source trigger is PTB13_IN*/
    TRGSEL3_SRC_PTB14_IN                   = 22U, /*Source trigger is PTB14_IN*/
    TRGSEL3_SRC_PTB15_IN                   = 23U, /*Source trigger is PTB15_IN*/
    TRGSEL3_SRC_PTB16_IN                   = 24U, /*Source trigger is PTB16_IN*/
    TRGSEL3_SRC_PTB17_IN                   = 25U, /*Source trigger is PTB17_IN*/
    TRGSEL3_SRC_PTC0_IN                    = 26U, /*Source trigger is PTC0_IN*/
    TRGSEL3_SRC_PTC1_IN                    = 27U, /*Source trigger is PTC1_IN*/
    TRGSEL3_SRC_PTC2_IN                    = 28U, /*Source trigger is PTC2_IN*/
    TRGSEL3_SRC_PTC3_IN                    = 29U, /*Source trigger is PTC3_IN*/
    TRGSEL3_SRC_PTC6_IN                    = 30U, /*Source trigger is PTC6_IN*/
    TRGSEL3_SRC_PTC7_IN                    = 31U, /*Source trigger is PTC7_IN*/
    TRGSEL3_SRC_PTD15_IN                   = 32U, /*Source trigger is PTD15_IN*/
    TRGSEL3_SRC_PTD16_IN                   = 33U, /*Source trigger is PTD16_IN*/
    TRGSEL3_SRC_PTE4_IN                    = 34U, /*Source trigger is PTE4_IN*/
    TRGSEL3_SRC_PTE5_IN                    = 35U, /*Source trigger is PTE5_IN*/
    TRGSEL3_SRC_PTE19_IN                   = 36U, /*Source trigger is PTE19_IN*/
    TRGSEL3_SRC_PTA2_OUT                   = 37U, /*Source trigger is PTA2_OUT*/
    TRGSEL3_SRC_PTA3_OUT                   = 38U, /*Source trigger is PTA3_OUT*/
    TRGSEL3_SRC_PTA9_OUT                   = 39U, /*Source trigger is PTA9_OUT*/
    TRGSEL3_SRC_PTA10_OUT                  = 40U, /*Source trigger is PTA10_OUT*/
    TRGSEL3_SRC_PTA11_OUT                  = 41U, /*Source trigger is PTA11_OUT*/
    TRGSEL3_SRC_PTA12_OUT                  = 42U, /*Source trigger is PTA12_OUT*/
    TRGSEL3_SRC_PTA14_OUT                  = 43U, /*Source trigger is PTA14_OUT*/
    TRGSEL3_SRC_PTA30_OUT                  = 44U, /*Source trigger is PTA30_OUT*/
    TRGSEL3_SRC_PTB4_OUT                   = 45U, /*Source trigger is PTB4_OUT*/
    TRGSEL3_SRC_PTB5_OUT                   = 46U, /*Source trigger is PTB5_OUT*/
    TRGSEL3_SRC_PTB12_OUT                  = 47U, /*Source trigger is PTB12_OUT*/
    TRGSEL3_SRC_PTB13_OUT                  = 48U, /*Source trigger is PTB13_OUT*/
    TRGSEL3_SRC_PTB14_OUT                  = 49U, /*Source trigger is PTB14_OUT*/
    TRGSEL3_SRC_PTB15_OUT                  = 50U, /*Source trigger is PTB15_OUT*/
    TRGSEL3_SRC_PTB16_OUT                  = 51U, /*Source trigger is PTB16_OUT*/
    TRGSEL3_SRC_PTB17_OUT                  = 52U, /*Source trigger is PTB17_OUT*/
    TRGSEL3_SRC_PTC0_OUT                   = 53U, /*Source trigger is PTC0_OUT*/
    TRGSEL3_SRC_PTC1_OUT                   = 54U, /*Source trigger is PTC1_OUT*/
    TRGSEL3_SRC_PTC2_OUT                   = 55U, /*Source trigger is PTC2_OUT*/
    TRGSEL3_SRC_PTC3_OUT                   = 56U, /*Source trigger is PTC3_OUT*/
    TRGSEL3_SRC_PTC6_OUT                   = 57U, /*Source trigger is PTC6_OUT*/
    TRGSEL3_SRC_PTC7_OUT                   = 58U, /*Source trigger is PTC7_OUT*/
    TRGSEL3_SRC_PTD15_OUT                  = 59U, /*Source trigger is PTD15_OUT*/
    TRGSEL3_SRC_PTD16_OUT                  = 60U, /*Source trigger is PTD16_OUT*/
    TRGSEL3_SRC_PTE4_OUT                   = 61U, /*Source trigger is PTE4_OUT*/
    TRGSEL3_SRC_PTE5_OUT                   = 62U, /*Source trigger is PTE5_OUT*/
    TRGSEL3_SRC_PTE19_OUT                  = 63U /*Source trigger is PTE19_OUT*/
} TrgSel3_SourceType;

#endif

