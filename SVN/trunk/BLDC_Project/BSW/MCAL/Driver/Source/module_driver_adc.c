/**
 * @file module_driver_adc.c
 * @author Flagchip030
 * @brief ADC driver source code
 * @version 2.0.0
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip095   N/A          First version
*********************************************************************************/

#include "module_driver_adc.h"

#if ADC_INSTANCE_COUNT > 0U

#include "module_driver_dma.h"
#include "module_driver_trgsel.h"
#include "module_driver_scg.h"
#include "module_driver_pcc.h"

#if ADC_DEV_ERROR_REPORT == STD_ON
    #define ADC_ReportDevError(func, error) ReportDevError(ADC_MODULE_ID, func, error)
#endif
/**
 * @name  ADC default values
 * @brief ADC default configuration parameters
 *
 * @{
 */
#define ADC_DEFAULT_SAMPLE_TIME_OPTION_0                  (0x04U)
#define ADC_DEFAULT_SAMPLE_TIME_OPTION_1                  (0x0AU)
#define ADC_DEFAULT_SAMPLE_TIME_OPTION_2                  (0x22U)
#define ADC_DEFAULT_SAMPLE_TIME_OPTION_3                  (0x82U)
#define ADC_DEFAULT_STARTUP_COUNTER                       (0xC0U)
#define ADC_DEFAULT_WATER_MARK                            (0x10U)
#define ADC_DEFAULT_COMPARE_HIGH_THRESHOLD                (0x000U)
#define ADC_DEFAULT_COMPARE_LOW_THRESHOLD                 (0x200U)
#define ADC_DEFAULT_SC_CHANNEL                            (0x3FU)

#ifdef ADC_ERR_001_WORKAROUND
    #define ADC_DISCONTINUOUS_1_SC_START_INDEX 4U
#else
    #define ADC_DISCONTINUOUS_1_SC_START_INDEX 0U
#endif

/** @}*/

/********* Local Variables ************/
static ADC_Type *const s_apAdcBase[ADC_INSTANCE_COUNT] = ADC_BASE_PTRS;

/******* Local Function Prototype *********/
#ifdef ADC_DISABLE_NEED_ADDITIONAL_ADC_CLK
    /**
    * @brief Wait 3 ADC clocks for the selected ADC instance
    *
    * @param eInstance the ADC instance selected
    */
    static inline void ADC_WaitClk(uint32_t u32SysFreq, uint32_t u32AdcFreq);
#endif

/**
 * @brief The internal DMA handler function for ADC instances
 *
 * @param eInstance the ADC instance selected
 */
static void ADCn_DMAHandler(void *pAdcHandler);

/**
 * @brief The internal config ADC interrupt function
 *
 * @param pAdcHandle the ADC handler
 */
static void ADC_InitInterrupt(ADC_HandleType *pAdcHandle);

/********* Local Functions ************/
#ifdef ADC_DISABLE_NEED_ADDITIONAL_ADC_CLK
static inline void ADC_WaitClk(uint32_t u32SysFreq, uint32_t u32AdcFreq)
{
    uint32_t u32ClkCnt;
    u32ClkCnt = 4U;
    u32ClkCnt = (u32SysFreq % u32AdcFreq == 0U) ? (u32SysFreq / u32AdcFreq) : (u32SysFreq / u32AdcFreq + 1U);
    /* Run this counter down to zero */
    while (u32ClkCnt != 0U)
    {
        /* Since we need a three cycle delay, we assume the decrement is one cycle
            and insert two NOP instructions. The actual delay will be larger because
            of the loop overhead and the compiler optimization.
        */
        u32ClkCnt--;
        NOP();
        NOP();
    }
}
#endif

/***************ADC IRQ Functions*****************/
void ADCn_IRQHandler(ADC_HandleType *pAdcHandle)
{
    ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];
    if (ADC_HWA_GetSequenceMode(pAdc) == ADC_SEQMODE_DISCONTINUOUS_1)
    {
        bool bConvCompleted = false;
        uint8_t u8Idx = 0U;
        for (u8Idx = 0U; u8Idx < (pAdcHandle->tSettings).u8ChnCnt; u8Idx++)
        {
            if (ADC_HWA_GetChannelConvertComplete(pAdc, (uint8_t)(u8Idx + ADC_DISCONTINUOUS_1_SC_START_INDEX)) == false)
            {
                break;
            }
            else if (ADC_HWA_GetChannelInterruptEnable(pAdc, (uint8_t)(u8Idx + ADC_DISCONTINUOUS_1_SC_START_INDEX)) == true)
            {
                bConvCompleted = true;
            }
            else
            {}
        }
        if (bConvCompleted)
        {
            #if ADC_DEV_ERROR_REPORT == STD_ON
            if ((pAdcHandle->tSettings).pAdcResultBuffer == NULL)
            {
                ADC_ReportDevError(ADC_INIT_STRUCTURE_ID, ADC_E_PARAM_POINTER);
            }
            else
            {
            #endif
                for (u8Idx = 0U; u8Idx < (pAdcHandle->tSettings).u8ChnCnt; u8Idx++)
                {
                    ((pAdcHandle->tSettings).pAdcResultBuffer)[u8Idx] = ADC_HWA_GetChannelData(pAdc, (uint8_t)(u8Idx + ADC_DISCONTINUOUS_1_SC_START_INDEX));
                }
                if ((pAdcHandle->tSettings).pConvCompleteCallback != NULL)
                {
                    (pAdcHandle->tSettings).pConvCompleteCallback(pAdcHandle, (pAdcHandle->tSettings).pAdcResultBuffer);
                }
                #if ADC_DEV_ERROR_REPORT == STD_ON
            }
                #endif
        }
    }
    else
    {
        bool bAdcSequenceComplete = ADC_HWA_GetEndOfSequence(pAdc);
        bool bAdcFifoFull = ADC_HWA_GetFull(pAdc);
        if ((bAdcSequenceComplete == true) ||
            (bAdcFifoFull == true))
        {
            #if ADC_DEV_ERROR_REPORT == STD_ON
            if ((pAdcHandle->tSettings).pAdcResultBuffer == NULL)
            {
                ADC_ReportDevError(ADC_INIT_STRUCTURE_ID, ADC_E_PARAM_POINTER);
            }
            else
            {
            #endif
                uint32_t u8Idx = 0U;
                while ((ADC_HWA_GetEmpty(pAdc) == false) && (u8Idx != (pAdcHandle->tSettings).u8ChnCnt))
                {
                    ((pAdcHandle->tSettings).pAdcResultBuffer)[u8Idx] = ADC_HWA_GetFIFOData(pAdc);
                    u8Idx++;
                }
                if (ADC_HWA_GetEndOfSequence(pAdc))
                {
                    ADC_HWA_ClearEndOfSequence(pAdc);
                }
                if (ADC_HWA_GetEndOfConversion(pAdc))
                {
                    ADC_HWA_ClearEndOfConversion(pAdc);
                }
                if (ADC_HWA_GetEndOfSample(pAdc))
                {
                    ADC_HWA_ClearEndOfSample(pAdc);
                }
                if (ADC_HWA_GetReady(pAdc))
                {
                    ADC_HWA_ClearReady(pAdc);
                }
                if ((pAdcHandle->tSettings).pConvCompleteCallback != NULL)
                {
                    (pAdcHandle->tSettings).pConvCompleteCallback(pAdcHandle, (pAdcHandle->tSettings).pAdcResultBuffer);
                }
                #if ADC_DEV_ERROR_REPORT == STD_ON
            }
                #endif
        }
    }

    if (ADC_HWA_GetOverRun(pAdc))
    {
        ADC_HWA_ClearOverRun(pAdc);
        if ((pAdcHandle->tSettings).pOverRunCallback != NULL)
        {
            (pAdcHandle->tSettings).pOverRunCallback(pAdcHandle);
        }
    }
    if (ADC_HWA_GetCompareFlag(pAdc))
    {
        ADC_HWA_ClearCompareFlag(pAdc);
        if ((pAdcHandle->tSettings).pCompareCallback != NULL)
        {
            (pAdcHandle->tSettings).pCompareCallback(pAdcHandle);
        }
    }
}

static void ADCn_DMAHandler(void *pAdcHandler)
{
    ADC_HandleType *pAdcHandle = (ADC_HandleType *)pAdcHandler;
    ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];
    if (ADC_HWA_GetEndOfSequence(pAdc))
    {
        ADC_HWA_ClearEndOfSequence(pAdc);
    }
    if (ADC_HWA_GetEndOfConversion(pAdc))
    {
        ADC_HWA_ClearEndOfConversion(pAdc);
    }
    if (ADC_HWA_GetEndOfSample(pAdc))
    {
        ADC_HWA_ClearEndOfSample(pAdc);
    }
    if (ADC_HWA_GetFIFOReady(pAdc))
    {
        ADC_HWA_ClearFIFOReady(pAdc);
    }
    if ((pAdcHandle->tSettings).pConvCompleteCallback != NULL)
    {
        (pAdcHandle->tSettings).pConvCompleteCallback(pAdcHandle, (pAdcHandle->tSettings).pAdcResultBuffer);
    }
}

static void ADC_InitInterrupt(ADC_HandleType *pAdcHandle)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_INIT_INTERRUPT_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->tSettings.bConversionCompleteIntEn) && (pAdcHandle->tSettings.pAdcResultBuffer == NULL))
    {
        ADC_ReportDevError(ADC_INIT_INTERRUPT_ID, ADC_E_PARAM_INVALID);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_INIT_INTERRUPT_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];
        uint32_t u32InterruptCfg;
        if (ADC_HWA_GetSequenceMode(pAdc) == ADC_SEQMODE_DISCONTINUOUS_1)
        {
            u32InterruptCfg = ADC_INT_ENABLE_FIFO_RDY_IE(false) |
                              ADC_INT_ENABLE_ACMP_IE((pAdcHandle->tSettings).bAnalogCmpIntEn) |
                              ADC_INT_ENABLE_OVRIE((pAdcHandle->tSettings).bOverRunIntEn) |
                              ADC_INT_ENABLE_EOSEQIE(false) |
                              ADC_INT_ENABLE_EOCIE(false) |
                              ADC_INT_ENABLE_EOSMPIE(false) |
                              ADC_INT_ENABLE_ADRDYIE(false);
            ADC_HWA_SetInterruptEnable(pAdc, u32InterruptCfg);
        }
        else
        {
            u32InterruptCfg = ADC_INT_ENABLE_FIFO_RDY_IE(false) |
                              ADC_INT_ENABLE_ACMP_IE((pAdcHandle->tSettings).bAnalogCmpIntEn) |
                              ADC_INT_ENABLE_OVRIE((pAdcHandle->tSettings).bOverRunIntEn) |
                              ADC_INT_ENABLE_EOSEQIE((pAdcHandle->tSettings).bConversionCompleteIntEn) |
                              ADC_INT_ENABLE_EOCIE(false) |
                              ADC_INT_ENABLE_EOSMPIE(false) |
                              ADC_INT_ENABLE_ADRDYIE(false);
            ADC_HWA_SetInterruptEnable(pAdc, u32InterruptCfg);
        }
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/***************** Global Functions *********************/
void ADC_InitStructure(ADC_InitType *const pInitCfg)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        ADC_ReportDevError(ADC_INIT_STRUCTURE_ID, ADC_E_PARAM_POINTER);
    }
    else
    {
    #endif
        pInitCfg->eResolution     = ADC_RESOLUTION_12_BIT;      /* 12 bit Resolution */
        pInitCfg->eAlign          = ADC_ALIGN_RIGHT;            /* Align right */
        pInitCfg->eTriggerMode    = ADC_TRIGMODE_SW;            /* Software trigger */
        pInitCfg->bWaitEnable     = false;                      /* Enable wait conversion mode */
        #ifdef ADC_DIFF_INPUT_SUPPORT
        pInitCfg->bDifferentialModeEnable = false;
        #endif
        #ifdef ADC_FUNCLK_INTERNAL_DIVIDER_SUPPORT
        pInitCfg->eClockDivider   = ADC_CLOCK_DIV_1;
        #endif
        pInitCfg->eSequenceMode   = ADC_SEQMODE_SINGLE;         /* Single sequence mode */
        pInitCfg->eOverrunMode    = ADC_OVERRUN_MODE_PRESERVE;  /* Old conversion data preserved when overrun occured */
        pInitCfg->eVoltageRef     = ADC_REF_INTERNAL;                  /* Use internal reference */
        pInitCfg->bHwAvgEnable    = false;                             /* Disable averaging functionality */
        pInitCfg->eHwAverage      = ADC_AVERAGE_4;                     /* Average by 4 samples if average is enabled */
        pInitCfg->aSampleTimes[0] = ADC_DEFAULT_SAMPLE_TIME_OPTION_0;  /* Sample time option 0 is 4 */
        pInitCfg->aSampleTimes[1] = ADC_DEFAULT_SAMPLE_TIME_OPTION_1;  /* Sample time option 1 is 10  */
        pInitCfg->aSampleTimes[2] = ADC_DEFAULT_SAMPLE_TIME_OPTION_2;  /* Sample time option 2 is 34  */
        pInitCfg->aSampleTimes[3] = ADC_DEFAULT_SAMPLE_TIME_OPTION_3;  /* Sample time option 3 is 130 */

        pInitCfg->ePreTriggerSel  = ADC_PRETRIGGER_SEL_PTIMER;  /* PTIMER pretrigger selected */
        pInitCfg->eTriggerSel     = ADC_TRIGGER_SEL_PTIMER;     /* PTIMER trigger selected */
        pInitCfg->u3AdcFuncClk    = 0u;
        pInitCfg->bAnalogCmpIntEn = false;
        pInitCfg->bConversionCompleteIntEn = false;
        pInitCfg->bOverRunIntEn   = false;
        pInitCfg->pCompareCallback = NULL;
        pInitCfg->pConvCompleteCallback = NULL;
        pInitCfg->pOverRunCallback = NULL;
        pInitCfg->pAdcResultBuffer = NULL;
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void ADC_Init(ADC_HandleType *pAdcHandle, const ADC_InitType *const pInitCfg)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if ((pAdcHandle == NULL) || (pInitCfg == NULL))
    {
        ADC_ReportDevError(ADC_INIT_ID, ADC_E_PARAM_POINTER);
    }
    else if (pAdcHandle->eInstance >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_INIT_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];
        #ifdef ADC_FUNCLK_INTERNAL_DIVIDER_SUPPORT
        uint32_t u32TimeOut = 15000000U;
        #endif
        uint32_t u32Cfg1;
        uint32_t u32Cfg2;
        ADC_TrigSrcType eTriggerSrc;
        ADC_TrigModeType eTriggerMode;
        uint32_t u32ClockDiv;
        uint32_t u32StartupCnt;

        if (pInitCfg->eSequenceMode == ADC_SEQMODE_DISCONTINUOUS_1)
        {
            eTriggerSrc = ADC_TRIGSRC_SMISC;
            eTriggerMode = ADC_TRIGMODE_RISING_EDGE;
        }
        else
        {
            eTriggerSrc = ADC_TRIGSRC_TRGSEL;
            eTriggerMode = pInitCfg->eTriggerMode;
        }

        #ifdef ADC_FUNCLK_INTERNAL_DIVIDER_SUPPORT
        u32ClockDiv = 1U << (pInitCfg->eClockDivider);
        #else
        u32ClockDiv = 1U;
        #endif

        if (pInitCfg->u3AdcFuncClk != 0U)
        {
            /* The start up count shall be around 5us */
            u32StartupCnt = (pInitCfg->u3AdcFuncClk) / u32ClockDiv / 1000000U * 5U + 1U;
            if (u32StartupCnt < 2U)
            {
                u32StartupCnt = 2U;
            }
            else if (u32StartupCnt > 255U)
            {
                u32StartupCnt = 255U;
            }
            else
            {}
        }
        else
        {
            u32StartupCnt = ADC_DEFAULT_STARTUP_COUNTER;
        }

        ADC_HWA_Reset(pAdc);

        u32Cfg1 = ADC_CFG1_OVRMOD(pInitCfg->eOverrunMode) |
                  ADC_CFG1_SEQ_LEN(0) |
                  ADC_CFG1_SEQ_MOD(pInitCfg->eSequenceMode) |
                  ADC_CFG1_WAIT(pInitCfg->bWaitEnable) |
                  #ifdef ADC_DIFF_INPUT_SUPPORT
                  ADC_CFG1_DIFF(pInitCfg->bDifferentialModeEnable) |
                  #endif
                  ADC_CFG1_TRIGSRC(eTriggerSrc) |
                  ADC_CFG1_TRIGMODE(eTriggerMode) |
                  ADC_CFG1_ALIGN(pInitCfg->eAlign) |
                  ADC_CFG1_RES(pInitCfg->eResolution) |
                  ADC_CFG1_DMAEN(false);
        ADC_HWA_SetConfig1(pAdc, u32Cfg1);

        u32Cfg2 = ADC_CFG2_FWMARK(ADC_DEFAULT_WATER_MARK) |
                  ADC_CFG2_AVG_EN(pInitCfg->bHwAvgEnable) |
                  ADC_CFG2_AVG_LEN(pInitCfg->eHwAverage) |
                  ADC_CFG2_REF_EXT(pInitCfg->eVoltageRef) |
                  ADC_CFG2_STCNT(u32StartupCnt);
        ADC_HWA_SetConfig2(pAdc, u32Cfg2);

        #ifdef ADC_FUNCLK_INTERNAL_DIVIDER_SUPPORT
        ADC_HWA_SetClockGatingEnableFlag(pAdc, true);
        while ((ADC_HWA_GetClockGatingAck(pAdc) != true) && (u32TimeOut != 0))
        {
            u32TimeOut--;
        }
        if (ADC_HWA_GetClockGatingAck(pAdc) == true)
        {
            ADC_HWA_SetClockDivider(pAdc, pInitCfg->eClockDivider);
        }
        u32TimeOut = 15000000U;
        ADC_HWA_SetClockGatingEnableFlag(pAdc, false);
        while ((ADC_HWA_GetClockGatingAck(pAdc) != false) && (u32TimeOut != 0))
        {
            u32TimeOut--;
        }
        #endif

        uint8_t u8SmprIndex;
        for (u8SmprIndex = 0U; u8SmprIndex < ADC_SAMPLE_TIME_OPTION_CNT; u8SmprIndex++)
        {
            ADC_HWA_SetSampleTime(pAdc, u8SmprIndex, (uint8_t)(pInitCfg->aSampleTimes[u8SmprIndex] - 2U));
        }

        ADC_HWA_SetPretriggerSelect(pAdc, pInitCfg->ePreTriggerSel);
        ADC_HWA_SetTriggerSelect(pAdc, pInitCfg->eTriggerSel);
        (pAdcHandle->tSettings).bAnalogCmpIntEn = pInitCfg->bAnalogCmpIntEn;
        (pAdcHandle->tSettings).bConversionCompleteIntEn = pInitCfg->bConversionCompleteIntEn;
        (pAdcHandle->tSettings).bOverRunIntEn = pInitCfg->bOverRunIntEn;
        (pAdcHandle->tSettings).pCompareCallback = pInitCfg->pCompareCallback;
        (pAdcHandle->tSettings).pConvCompleteCallback = pInitCfg->pConvCompleteCallback;
        (pAdcHandle->tSettings).pOverRunCallback = pInitCfg->pOverRunCallback;
        (pAdcHandle->tSettings).pAdcResultBuffer = pInitCfg->pAdcResultBuffer;
        ADC_InitInterrupt(pAdcHandle);
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void ADC_DeInit(ADC_HandleType *pAdcHandle)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_INIT_CHANNEL_ID, ADC_E_PARAM_POINTER);
    }
    else if (pAdcHandle->eInstance >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_DEINIT_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];
        uint32_t u32TimeOut = 15000000U;
        uint32_t u32Cfg1;
        uint32_t u32Cfg2;

        if (ADC_HWA_GetStart(pAdc) == true)
        {
            ADC_HWA_Stop(pAdc);

            while ((ADC_HWA_GetStop(pAdc) == true) && (u32TimeOut != 0U))
            {
                u32TimeOut--;
            }
        }

        u32TimeOut = 15000000U;

        if (ADC_HWA_GetEnable(pAdc) == true)
        {
            ADC_HWA_Disable(pAdc);

            while ((ADC_HWA_GetEnable(pAdc) == true) && (u32TimeOut != 0U))
            {
                u32TimeOut--;
            }
        }

        ADC_HWA_Reset(pAdc);

        ADC_HWA_SetInterruptEnable(pAdc, 0U);

        u32Cfg1 = ADC_CFG1_OVRMOD(ADC_OVERRUN_MODE_PRESERVE) |
                  ADC_CFG1_SEQ_LEN(0U) |
                  ADC_CFG1_SEQ_MOD(ADC_SEQMODE_SINGLE) |
                  ADC_CFG1_WAIT(false) |
                  ADC_CFG1_TRIGSRC(ADC_TRIGSRC_SMISC) |
                  ADC_CFG1_TRIGMODE(ADC_TRIGMODE_SW) |
                  ADC_CFG1_ALIGN(ADC_ALIGN_RIGHT) |
                  ADC_CFG1_RES(ADC_RESOLUTION_12_BIT) |
                  ADC_CFG1_DMAEN(false);
        ADC_HWA_SetConfig1(pAdc, u32Cfg1);

        u32Cfg2 = ADC_CFG2_FWMARK(ADC_DEFAULT_WATER_MARK) |
                  ADC_CFG2_AVG_EN(false) |
                  ADC_CFG2_AVG_LEN(ADC_AVERAGE_4) |
                  ADC_CFG2_REF_EXT(ADC_REF_INTERNAL) |
                  ADC_CFG2_STCNT(ADC_DEFAULT_STARTUP_COUNTER);
        ADC_HWA_SetConfig2(pAdc, u32Cfg2);

        ADC_HWA_SetSampleTime(pAdc, 0U, ADC_DEFAULT_SAMPLE_TIME_OPTION_0 - 2U);
        ADC_HWA_SetSampleTime(pAdc, 1U, ADC_DEFAULT_SAMPLE_TIME_OPTION_1 - 2U);
        ADC_HWA_SetSampleTime(pAdc, 2U, ADC_DEFAULT_SAMPLE_TIME_OPTION_2 - 2U);
        ADC_HWA_SetSampleTime(pAdc, 3U, ADC_DEFAULT_SAMPLE_TIME_OPTION_3 - 2U);

        ADC_HWA_SetHwCompareEnableFlag(pAdc, false);
        ADC_HWA_SetHwCompareChannel(pAdc, ADC_CMP_CHANNEL_ALL, 0U);

        ADC_HWA_SetHwCompareThreshold(pAdc, ADC_DEFAULT_COMPARE_LOW_THRESHOLD, ADC_DEFAULT_COMPARE_HIGH_THRESHOLD);

        uint8_t u8ChnIndex;
        for (u8ChnIndex = 0U; u8ChnIndex < ADC_SC_COUNT; u8ChnIndex++)
        {
            ADC_HWA_SetChannelSampleTimeIndex(pAdc, u8ChnIndex, 0U);
            ADC_HWA_SetChannelInterruptEnable(pAdc, u8ChnIndex, false);
            ADC_HWA_SetChannelInput(pAdc, u8ChnIndex, ADC_DEFAULT_SC_CHANNEL);
        }
        ADC_HWA_SetPretriggerSelect(pAdc, ADC_PRETRIGGER_SEL_PTIMER);
        ADC_HWA_SetSwPretriggerSelect(pAdc, ADC_SW_PRETRIGGER_DISABLED);
        ADC_HWA_SetTriggerSelect(pAdc, ADC_TRIGGER_SEL_PTIMER);
        (pAdcHandle->tSettings).pOverRunCallback      = NULL;
        (pAdcHandle->tSettings).pConvCompleteCallback = NULL;
        (pAdcHandle->tSettings).pCompareCallback      = NULL;
        (pAdcHandle->tSettings).pAdcResultBuffer      = NULL;
        pAdcHandle->tSettings.u8ChnCnt                = 0;
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void ADC_InitChannel(ADC_HandleType *pAdcHandle, const ADC_ChannelCfgType aChannels[],
                     const uint8_t u8ChnCnt)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL || aChannels == NULL)
    {
        ADC_ReportDevError(ADC_INIT_CHANNEL_ID, ADC_E_PARAM_POINTER);
    }
    else if (pAdcHandle->eInstance >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_INIT_CHANNEL_ID, ADC_E_PARAM_INSTANCE);
    }
    else if (u8ChnCnt > ADC_SC_COUNT)
    {
        ADC_ReportDevError(ADC_INIT_CHANNEL_ID, ADC_E_PARAM_CHANNEL);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];
        ADC_SeqModeType eSeqMode = ADC_HWA_GetSequenceMode(pAdc);

        #if ((ADC_DEV_ERROR_REPORT == STD_ON) && defined(ADC_ERR_001_WORKAROUND))
        if ((eSeqMode == ADC_SEQMODE_DISCONTINUOUS_1) && (u8ChnCnt > ADC_SC_COUNT - ADC_DISCONTINUOUS_1_SC_START_INDEX))
        {
            ADC_ReportDevError(ADC_INIT_CHANNEL_ID, ADC_E_PARAM_CHANNEL);
        }
        else
        {
        #endif
            pAdcHandle->tSettings.u8ChnCnt = u8ChnCnt;
            uint8_t u8ChnIndex;
            if (eSeqMode == ADC_SEQMODE_DISCONTINUOUS_1)
            {
                for (u8ChnIndex = 0U; u8ChnIndex < u8ChnCnt; u8ChnIndex++)
                {
                    ADC_HWA_SetChannelSampleTimeIndex(pAdc, (uint8_t)(u8ChnIndex + ADC_DISCONTINUOUS_1_SC_START_INDEX), aChannels[u8ChnIndex].eSampleTimeOption);
                    ADC_HWA_SetChannelInterruptEnable(pAdc, (uint8_t)(u8ChnIndex + ADC_DISCONTINUOUS_1_SC_START_INDEX), false);
                    ADC_HWA_SetChannelInput(pAdc, (uint8_t)(u8ChnIndex + ADC_DISCONTINUOUS_1_SC_START_INDEX), aChannels[u8ChnIndex].eChannel);
                }
                ADC_HWA_SetChannelInterruptEnable(pAdc, (uint8_t)((pAdcHandle->tSettings).u8ChnCnt + ADC_DISCONTINUOUS_1_SC_START_INDEX - 1U), (pAdcHandle->tSettings).bConversionCompleteIntEn);
            }
            else
            {
                for (u8ChnIndex = 0U; u8ChnIndex < u8ChnCnt; u8ChnIndex++)
                {
                    ADC_HWA_SetChannelSampleTimeIndex(pAdc, u8ChnIndex, aChannels[u8ChnIndex].eSampleTimeOption);
                    ADC_HWA_SetChannelInterruptEnable(pAdc, u8ChnIndex, false);
                    ADC_HWA_SetChannelInput(pAdc, u8ChnIndex, aChannels[u8ChnIndex].eChannel);
                }
                ADC_HWA_SetSequenceLength(pAdc, (uint8_t)(u8ChnCnt - 1U));
                ADC_HWA_SetFIFOWaterMark(pAdc, (uint8_t)(u8ChnCnt - 1U));
            }
            #if ((ADC_DEV_ERROR_REPORT == STD_ON) && defined(ADC_ERR_001_WORKAROUND))
        }
            #endif
#if ADC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

void ADC_InitCompare(const ADC_HandleType *pAdcHandle, const ADC_CompareType *const pCmpCfg)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if ((pCmpCfg == NULL) || (pAdcHandle == NULL))
    {
        ADC_ReportDevError(ADC_INIT_COMPARE_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_INIT_COMPARE_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];

        ADC_HWA_SetHwCompareChannel(pAdc, pCmpCfg->eCmpSingleChn, pCmpCfg->u8CmpChnSel);
        ADC_HWA_SetHwCompareThreshold(pAdc, pCmpCfg->u16LowThres, pCmpCfg->u16HighThres);
        ADC_HWA_SetHwCompareEnableFlag(pAdc, pCmpCfg->bCmpEnable);
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void ADC_InitDmaChannel(DMA_HandleType *pDmaHandle, ADC_HandleType *pAdcHandle, const ADC_DmaType *const pAdcDmaCfg)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if ((pDmaHandle == NULL) || (pAdcHandle == NULL) || (pAdcDmaCfg == NULL))
    {
        ADC_ReportDevError(ADC_INIT_DMA_CHANNEL_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_INIT_DMA_CHANNEL_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];

        if (pAdcDmaCfg->bDmaEnable == true)
        {
            (pAdcHandle->tSettings).pAdcResultBuffer = pAdcDmaCfg->pResultBuffer;
            (pAdcHandle->tSettings).pConvCompleteCallback = pAdcDmaCfg->pConvCompleteCallback;

            DMA_ChannelCfgType tDmaCfg;
            pDmaHandle->tSettings.u8Channel = pAdcDmaCfg->u8DmaChannel;
            if (ADC_HWA_GetSequenceMode(pAdc) == ADC_SEQMODE_DISCONTINUOUS_1)
            {
                tDmaCfg.pSrcBuffer = &pAdc->RESULT[ADC_DISCONTINUOUS_1_SC_START_INDEX];
                tDmaCfg.pDestBuffer = pAdcDmaCfg->pResultBuffer;
                tDmaCfg.u32BlockSize = 4U;
                tDmaCfg.u16BlockCount = (pAdcHandle->tSettings).u8ChnCnt;
                tDmaCfg.eSrcIncMode = DMA_INCREMENT_DATA_SIZE;
            }
            else
            {
                tDmaCfg.pSrcBuffer = &pAdc->FIFO_DATA;
                tDmaCfg.pDestBuffer = pAdcDmaCfg->pResultBuffer;
                tDmaCfg.u32BlockSize = 4U * (pAdcHandle->tSettings).u8ChnCnt;
                tDmaCfg.u16BlockCount = 1U;
                tDmaCfg.eSrcIncMode = DMA_INCREMENT_DISABLE;
            }
            tDmaCfg.eDestIncMode = DMA_INCREMENT_DATA_SIZE;
            tDmaCfg.eSrcDataSize = DMA_TRANSFER_SIZE_4B;
            tDmaCfg.eDestDataSize = DMA_TRANSFER_SIZE_4B;
            tDmaCfg.u8ChannelPriority = pAdcDmaCfg->u8ChannelPriority;
            tDmaCfg.bSrcBlockOffsetEn = false;
            tDmaCfg.bDestBlockOffsetEn = false;
            tDmaCfg.s32BlockOffset = 0;
            tDmaCfg.bSrcAddrLoopbackEn = true;
            tDmaCfg.bDestAddrLoopbackEn = true;
            tDmaCfg.bAutoStop = false;
            tDmaCfg.bSrcCircularBufferEn = false;
            tDmaCfg.u32SrcCircBufferSize = DMA_CIRCULAR_BUFFER_SIZE_1B;
            tDmaCfg.bDestCircularBufferEn = false;
            tDmaCfg.u32DestCircBufferSize = DMA_CIRCULAR_BUFFER_SIZE_1B;
            if (pAdcHandle->eInstance == ADC_INSTANCE_0)
            {
                tDmaCfg.eTriggerSrc = DMA_REQ_ADC0;
            }
            else if (pAdcHandle->eInstance == ADC_INSTANCE_1)
            {
                tDmaCfg.eTriggerSrc = DMA_REQ_ADC1;
            }
            else
            {}

            tDmaCfg.bTransferCompleteIntEn = pAdcDmaCfg->bDmaIntEnable;
            tDmaCfg.bTransferErrorIntEn = false;
            tDmaCfg.pTransferCompleteNotify = ADCn_DMAHandler;
            tDmaCfg.pTransferErrorNotify = NULL;
            tDmaCfg.completedata       = pAdcHandle;

            ADC_HWA_SetDMAEnableFlag(pAdc, true);

            DMA_DeinitChannel(pDmaHandle);
            DMA_InitChannel(pDmaHandle, &tDmaCfg);
        }
        else
        {
            ADC_HWA_SetDMAEnableFlag(pAdc, false);
        }
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void ADC_SetSwPretrigger(const ADC_HandleType *pAdcHandle,
                         const ADC_SwPreTriggerType eSwPretrigger)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_SET_SW_PRETRIGGER_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_SET_SW_PRETRIGGER_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];

        /* If SW Pretrigger Select is not enabled, the SW pretriggers will be ignored by ADC. */
        DEV_ASSERT((ADC_HWA_GetPreTriggerSelect(pAdc) == ADC_PRETRIGGER_SEL_SW) ||
                   (eSwPretrigger == ADC_SW_PRETRIGGER_DISABLED));

        ADC_HWA_SetSwPretriggerSelect(pAdc, eSwPretrigger);
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

ADC_StatusType ADC_Enable(const ADC_HandleType *pAdcHandle)
{
    ADC_StatusType eRet = ADC_STATUS_SUCCESS;
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        eRet = ADC_STATUS_ERROR;
        ADC_ReportDevError(ADC_ENABLE_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        eRet = ADC_STATUS_ERROR;
        ADC_ReportDevError(ADC_ENABLE_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        uint32_t u32TimeOut = 15000000U;
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];

        ADC_HWA_Enable(pAdc);
        while ((ADC_HWA_GetReady(pAdc) != true) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
        if (u32TimeOut != 0U)
        {
            ADC_HWA_ClearReady(pAdc);
            eRet = ADC_STATUS_SUCCESS;
        }
        else
        {
            eRet = ADC_STATUS_TIMEOUT;
        }
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return eRet;
}

ADC_StatusType ADC_Disable(ADC_HandleType *pAdcHandle, uint32_t u32SysFreq, uint32_t u32AdcFreq)
{
    ADC_StatusType eRet = ADC_STATUS_SUCCESS;
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_DISABLE_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_DISABLE_ID, ADC_E_PARAM_INSTANCE);
    }
    #ifdef ADC_DISABLE_NEED_ADDITIONAL_ADC_CLK
    else if ((u32SysFreq == 0u) || (u32AdcFreq == 0u))
    {
        ADC_ReportDevError(ADC_DISABLE_ID, ADC_E_PARAM_INVALID);
    }
    #endif
    else
    {
    #endif
        uint32_t u32TimeOut = 15000000U;
        ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];

        if (ADC_HWA_GetStart(pAdc) == true)
        {
            eRet = ADC_Stop(pAdcHandle, u32SysFreq, u32AdcFreq);
        }

        if (eRet == ADC_STATUS_SUCCESS)
        {
            ADC_HWA_Disable(pAdc);
            while ((ADC_HWA_GetEnable(pAdc) == true) && (u32TimeOut != 0U))
            {
                u32TimeOut--;
            }
            if (u32TimeOut != 0U)
            {
                eRet = ADC_STATUS_SUCCESS;
            }
            else
            {
                eRet = ADC_STATUS_TIMEOUT;
            }
        }
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return eRet;
}

void ADC_Start(const ADC_HandleType *pAdcHandle)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_START_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_START_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[pAdcHandle->eInstance];
        ADC_HWA_Start(pAdc);
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

ADC_StatusType ADC_Stop(const ADC_HandleType *pAdcHandle, uint32_t u32SysFreq, uint32_t u32AdcFreq)
{
    ADC_StatusType eRet = ADC_STATUS_ERROR;
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_STOP_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_STOP_ID, ADC_E_PARAM_INSTANCE);
    }
    #ifdef ADC_DISABLE_NEED_ADDITIONAL_ADC_CLK
    else if ((u32SysFreq == 0u) || (u32AdcFreq == 0u))
    {
        ADC_ReportDevError(ADC_STOP_ID, ADC_E_PARAM_INVALID);
    }
    #endif
    else
    {
    #endif
        uint32_t u32TimeOut = 15000000U;
        ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];

        ADC_HWA_Stop(pAdc);

        while ((ADC_HWA_GetStop(pAdc) == true) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
        if (u32TimeOut != 0U)
        {
            #ifdef ADC_DISABLE_NEED_ADDITIONAL_ADC_CLK
            ADC_WaitClk(u32SysFreq, u32AdcFreq);
            #else
            PROCESS_UNUSED_VAR(u32SysFreq);
            PROCESS_UNUSED_VAR(u32AdcFreq);
            #endif
            eRet = ADC_STATUS_SUCCESS;
        }
        else
        {
            eRet = ADC_STATUS_TIMEOUT;
        }
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return eRet;
}

void ADC_Reset(const ADC_HandleType *pAdcHandle)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_RESET_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_RESET_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];
        ADC_HWA_Reset(pAdc);
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

uint32_t ADC_GetTriggerErrorStatus(const ADC_HandleType *pAdcHandle)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_GET_TRIG_ERR_STATUS_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_GET_TRIG_ERR_STATUS_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        const ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];

        return ADC_HWA_GetTriggerErrorStatus(pAdc);
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

ADC_StatusType ADC_ClearTriggerError(const ADC_HandleType *pAdcHandle, uint32_t u32Request)
{
    ADC_StatusType eRet = ADC_STATUS_ERROR;
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_CLEAR_TRIG_ERR_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_CLEAR_TRIG_ERR_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        uint32_t u32TimeOut = 15000000U;

        ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];
        ADC_HWA_ClearTriggerError(pAdc, u32Request);
        while (((ADC_HWA_GetTriggerErrorStatus(pAdc) & (1UL << u32Request)) != 0U) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
        if (u32TimeOut != 0U)
        {
            eRet = ADC_STATUS_SUCCESS;
        }
        else
        {
            eRet = ADC_STATUS_TIMEOUT;
        }
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return eRet;
}

ADC_StatusType ADC_ClearTriggerErrors(const ADC_HandleType *pAdcHandle)
{
    ADC_StatusType eRet = ADC_STATUS_ERROR;
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_CLEAR_TRIG_ERR_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_CLEAR_TRIG_ERRS_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        uint32_t u32TimeOut = 15000000U;

        ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];
        ADC_HWA_ClearTriggerErrors(pAdc);
        while ((ADC_HWA_GetTriggerErrorStatus(pAdc) != 0U) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
        if (u32TimeOut != 0U)
        {
            eRet = ADC_STATUS_SUCCESS;
        }
        else
        {
            eRet = ADC_STATUS_TIMEOUT;
        }
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return eRet;
}

uint32_t ADC_GetTriggerLatchStatus(const ADC_HandleType *pAdcHandle)
{
    uint32_t ret;
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ret = 0U;
        ADC_ReportDevError(ADC_CLEAR_TRIG_ERR_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ret = 0U;
        ADC_ReportDevError(ADC_GET_TRIG_LATCH_STATUS_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];
        ret = ADC_HWA_GetTriggerLatchStatus(pAdc);
        return ret;
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void ADC_ClearLatchedTriggers(const ADC_HandleType *pAdcHandle)
{
    #if ADC_DEV_ERROR_REPORT == STD_ON
    if (pAdcHandle == NULL)
    {
        ADC_ReportDevError(ADC_CLEAR_TRIG_ERR_ID, ADC_E_PARAM_POINTER);
    }
    else if ((pAdcHandle->eInstance) >= ADC_INSTANCE_COUNT)
    {
        ADC_ReportDevError(ADC_CLEAR_LATCH_TRIGGER_ID, ADC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        ADC_Type *const pAdc = s_apAdcBase[(pAdcHandle->eInstance)];
        ADC_HWA_ClearLatchedTriggers(pAdc);
        #if ADC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

#endif
