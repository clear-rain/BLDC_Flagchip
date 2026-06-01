#ifndef _DEVICE_FEATURES_FC4150F1M__B_FREQM_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_FREQM_COMMON_H_

/************ FREQM Features **************/
/** Number of instances of the FREQM module. */
#define FREQM_INSTANCE_COUNT                    (1u)

/* FREQM - Peripheral instance base addresses */
/** Peripheral FREQM base address */
#define FREQM_BASE                              (0x40046000u)
/** Peripheral FREQM base pointer */
#define FREQM                                   ((FREQM_Type *)FREQM_BASE)
/** Array initializer of FREQM peripheral base addresses */
#define FREQM_BASE_ADDRS                        {FREQM_BASE}
/** Array initializer of FREQM peripheral base pointers */
#define FREQM_BASE_PTRS                         {FREQM}

/**
 * @brief freqm measured clock define
 *
 * @{
 */
#define FREQM_MES_FOSC_CLK              5U
#define FREQM_MES_PLL0_FB_CLK           6U
#define FREQM_MES_SCG_OUT_CLK           7U
#define FREQM_MES_SIRC_128K_CLK         11U
#define FREQM_MES_FIRC_DIVH_CLK         12U
#define FREQM_MES_SIRC_DIVH_CLK         13U
#define FREQM_MES_FOSC_DIVH_CLK         14U
#define FREQM_MES_PLL0_DIVH_CLK         15U
#define FREQM_MES_PLL0_DIVM_CLK         16U
#define FREQM_MES_FOSC_DIVM_CLK         17U
#define FREQM_MES_SIRC_DIVM_CLK         18U
#define FREQM_MES_FIRC_DIVM_CLK         19U
#define FREQM_MES_RTC_CLK               20U
#define FREQM_MES_AON_CLK               21U
#define FREQM_MES_PCC_ADC0              24U
#define FREQM_MES_PCC_ADC1              25U
#define FREQM_MES_PCC_FTU0              28U
#define FREQM_MES_PCC_FTU1              29U
#define FREQM_MES_PCC_FTU2              30U
#define FREQM_MES_PCC_FTU3              31U
#define FREQM_MES_PCC_FTU4              32U
#define FREQM_MES_PCC_FTU5              33U
#define FREQM_MES_PCC_FCPIT             35U
#define FREQM_MES_PCC_FLEXCAN0          36U
#define FREQM_MES_PCC_FCSPI0            37U
#define FREQM_MES_PCC_FCUART0           38U
#define FREQM_MES_TSTMP0                39U

/** @}*/

#endif
