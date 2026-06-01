/**
 * @file module_driver_ptimer.c
 * @author Flagchip030
 * @brief PTIMER driver source code
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

#include "module_driver_ptimer.h"

#if PTIMER_INSTANCE_COUNT > 0U

#include "module_driver_scg.h"
#include "HwA_smisc.h"

#if PTIMER_DEV_ERROR_REPORT == STD_ON
    #define PTIMER_ReportDevError(func, error) ReportDevError(PTIMER_MODULE_ID, func, error)
#endif

#ifdef PTIMER_ADC_ERR_001_WORKAROUND
    #define PTIMER_DELAY_START_INDEX 4U
#else
    #define PTIMER_DELAY_START_INDEX 0U
#endif

static PTIMER_Type *const s_apPtimerBase[PTIMER_INSTANCE_COUNT] = PTIMER_BASE_PTRS;

/**
 * @brief Calculate the delay value base on the delay micro seconds
 *
 * @param eInstance the Ptimer instance to use
 * @param u32DelayUs the delay time in micro seconds
 * @return uint16_t the delay time in ptimer clock count
 */
static uint16_t PTIMER_CalcDelayValue(uint32 u32SysFreq, const PTIMER_InstanceType eInstance, const uint32_t u32DelayUs);

/**
 * @brief Initialize the Ptimer interrupt
 *
 * @note the interrupt delay value is buffered and will take effect only after called PTIMER_LoadValue()
 * function.
 *
 * @param PTIMER_HandleType the Ptimer handler pointer
 */
static void PTIMER_InitInterrupt(PTIMER_HandleType *PtimerHandle);

static uint16_t PTIMER_CalcDelayValue(uint32 u32SysFreq, const PTIMER_InstanceType eInstance, const uint32_t u32DelayUs)
{
    uint32_t u32DelayVal;
    const PTIMER_Type *const pPtimer = s_apPtimerBase[eInstance];
    uint32_t u32PdbFreqUs = 0U;
    PTIMER_ClockPreDividerType ePreDivider = PTIMER_HWA_GetDivPrescaler(pPtimer);
    PTIMER_ClockPreDivMultiplyFactorType ePreDivMultFactor = PTIMER_HWA_GetDivMultiply(pPtimer);
    uint8_t u8Prescaler = (uint8_t)(1U << ePreDivider);
    uint8_t u8PrescalerMult = 1U;
    switch (ePreDivMultFactor)
    {
        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_1:
            u8PrescalerMult = 1U;
            break;

        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_10:
            u8PrescalerMult = 10U;
            break;

        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_20:
            u8PrescalerMult = 20U;
            break;

        case PTIMER_PRE_DIVIDER_MULTIPLY_BY_40:
            u8PrescalerMult = 40U;
            break;

        default:
            u8PrescalerMult = 1U;
            break;
    }
    u32PdbFreqUs = u32SysFreq / 1000000U;
    u32DelayVal = (u32DelayUs * u32PdbFreqUs) / ((uint32_t)u8Prescaler * u8PrescalerMult);
    if (u32DelayVal >= (1U << 16U))
    {
        u32DelayVal = 0U;
    }
    return (uint16_t)u32DelayVal;
}

static void PTIMER_InitInterrupt(PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_INIT_INTERRUPT_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_INIT_INTERRUPT_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];

        PTIMER_HWA_SetSeqErrIntEnableFlag(pPtimer, PtimerHandle->tSettings.bSeqErrIntEnable);
        PTIMER_HWA_SetInterruptDelay(pPtimer, PtimerHandle->tSettings.u16IntDelayPeriod);
        PTIMER_HWA_SetInterruptEnableFlag(pPtimer, PtimerHandle->tSettings.bDelayIntEnable);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMERn_IRQHandler(PTIMER_HandleType *PtimerHandle)
{
    PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
    uint8_t u8Channel;
    if (PTIMER_HWA_GetInterruptFlag(pPtimer) == true)
    {
        PTIMER_HWA_ClearInterruptFlag(pPtimer);
        if ((PtimerHandle->tSettings).pIntNotify != NULL)
        {
            (PtimerHandle->tSettings).pIntNotify(PtimerHandle);
        }
    }

    for (u8Channel = 0U; u8Channel < (PtimerHandle->tSettings).u8ChnNum; u8Channel++)
    {
        if (PTIMER_HWA_GetChannelSequenceErrorFlag(pPtimer, u8Channel) == true)
        {
            PTIMER_HWA_ClearChannelSequenceErrorFlag(pPtimer, u8Channel);
            if ((PtimerHandle->tSettings).pSeqErrorNotify != NULL)
            {
                (PtimerHandle->tSettings).pSeqErrorNotify(PtimerHandle, u8Channel);
            }
        }
    }
}

void PTIMER_DeInit(PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_CALC_DELAY_VALUE_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_CALC_DELAY_VALUE_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
        uint8_t u8Chn;

        /* Reset PTIMER Status Ctrl Register */
        PTIMER_HWA_SetStatusCtrl(pPtimer, 0U);
        /* Enable PTIMER */
        PTIMER_HWA_Enable(pPtimer);
        /* Reset PTIMER Max Cnt Register */
        PTIMER_HWA_SetMaxCount(pPtimer, 0xFFFFU);
        /* Reset PTIMER Int Dly Register */
        PTIMER_HWA_SetInterruptDelay(pPtimer, 0xFFFFU);

        for (u8Chn = 0U; u8Chn < PTIMER_DLY_CNT; u8Chn++)
        {
            PTIMER_HWA_SetChannelControl(pPtimer, u8Chn, false, false, false);
            PTIMER_HWA_ClearChannelCounterFlag(pPtimer, u8Chn);
            PTIMER_HWA_ClearChannelSequenceErrorFlag(pPtimer, u8Chn);
            PTIMER_HWA_SetChannelDelay(pPtimer, u8Chn, 0U);
        }

        /* For Pulse out trigger. */
        PTIMER_HWA_DisablePulseOut(pPtimer);
        PTIMER_HWA_SetPulseOutDelay(pPtimer, 0U, 0U);

        PTIMER_HWA_LoadValue(pPtimer);
        PTIMER_HWA_Disable(pPtimer);
        (PtimerHandle->tSettings).pSeqErrorNotify = NULL;
        (PtimerHandle->tSettings).pIntNotify      = NULL;
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/***************** Global Functions *********************/
void PTIMER_InitStructure(PTIMER_InitType *const pInitCfg)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        PTIMER_ReportDevError(PTIMER_INIT_STRUCTURE_ID, PTIMER_E_PARAM_POINTER);
    }
    else
    {
    #endif
        pInitCfg->bContinuousModeEnable     = true;
        pInitCfg->bDmaEnable                = false;
        pInitCfg->bInstanceBackToBackEnable = false;
        pInitCfg->eClkPreDiv                = PTIMER_PRE_DIVIDE_BY_1;
        pInitCfg->eClkPreMultFactor         = PTIMER_PRE_DIVIDER_MULTIPLY_BY_1;
        pInitCfg->eLoadValueMode            = PTIMER_LOAD_VAL_IMMEDIATELY;
        pInitCfg->eTriggerInput             = PTIMER_TRGSRC_SW;
        pInitCfg->bDelayIntEnable           = false;
        pInitCfg->bSeqErrIntEnable          = false;
        pInitCfg->u16IntDelayPeriod         = 58593U;
        pInitCfg->pSeqErrorNotify           = NULL;
        pInitCfg->pIntNotify                = NULL;
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


void PTIMER_Init(PTIMER_HandleType *PtimerHandle, const PTIMER_InitType *const pInitCfg)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL || pInitCfg == NULL)
    {
        PTIMER_ReportDevError(PTIMER_INIT_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_INIT_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];

        PTIMER_DeInit(PtimerHandle);

        PTIMER_HWA_SetLoadMode(pPtimer, pInitCfg->eLoadValueMode);
        PTIMER_HWA_SetDivPrescaler(pPtimer, pInitCfg->eClkPreDiv);
        PTIMER_HWA_SetTriggerSource(pPtimer, pInitCfg->eTriggerInput);
        PTIMER_HWA_SetDivMultiply(pPtimer, pInitCfg->eClkPreMultFactor);
        PTIMER_HWA_SetContinuoiusModeFlag(pPtimer, pInitCfg->bContinuousModeEnable);
        PTIMER_HWA_SetDMAEnableFlag(pPtimer, pInitCfg->bDmaEnable);

        SMISC_HWA_SetPtimerInstanceBackToBackEnableFlag(pInitCfg->bInstanceBackToBackEnable);
        (PtimerHandle->tSettings).pIntNotify = pInitCfg->pIntNotify;
        (PtimerHandle->tSettings).pSeqErrorNotify = pInitCfg->pSeqErrorNotify;
        (PtimerHandle->tSettings).bDelayIntEnable = pInitCfg->bDelayIntEnable;
        (PtimerHandle->tSettings).bSeqErrIntEnable = pInitCfg->bSeqErrIntEnable;
        (PtimerHandle->tSettings).u16IntDelayPeriod = pInitCfg->u16IntDelayPeriod;
        (PtimerHandle->tSettings).u8ChnNum = 0U;
        PTIMER_InitInterrupt(PtimerHandle);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_InitChannel(PTIMER_HandleType *PtimerHandle,
                        const PTIMER_ChannelCfgType aChannelCfg[], const uint8_t u8ChnNum)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if ((aChannelCfg == NULL) || (PtimerHandle == NULL))
    {
        PTIMER_ReportDevError(PTIMER_INIT_CHANNEL_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_INIT_CHANNEL_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else if (u8ChnNum > PTIMER_DLY_CNT - PTIMER_DELAY_START_INDEX)
    {
        PTIMER_ReportDevError(PTIMER_INIT_CHANNEL_ID, PTIMER_E_PARAM_CHANNEL);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];

        uint8_t u8ChnIdx;

        for (u8ChnIdx = 0U; u8ChnIdx < u8ChnNum; u8ChnIdx++)
        {
            PTIMER_HWA_SetChannelControl(pPtimer, (uint8_t)(u8ChnIdx + PTIMER_DELAY_START_INDEX), aChannelCfg[u8ChnIdx].bPreTriggerEnable,
                                         aChannelCfg[u8ChnIdx].bPreTriggerOutputEnable, aChannelCfg[u8ChnIdx].bPreTriggerBackToBackEnable);
            PTIMER_HWA_SetChannelDelay(pPtimer, (uint8_t)(u8ChnIdx + PTIMER_DELAY_START_INDEX), aChannelCfg[u8ChnIdx].u16DelayCnt);
        }
        (PtimerHandle->tSettings).u8ChnNum = u8ChnNum;
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


//ADD
void PTIMER_SetDelayForChannel0(PTIMER_HandleType *PtimerHandle, uint16 DelayCnt, uint16 DelayCnt2, uint16 DelayCnt3, uint16 DelayCnt4)
{
	PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
	PTIMER_HWA_SetChannelDelay(pPtimer, (uint8_t)(4U), DelayCnt);
	PTIMER_HWA_SetChannelDelay(pPtimer, (uint8_t)(5U), DelayCnt2);
	PTIMER_HWA_SetChannelDelay(pPtimer, (uint8_t)(6U), DelayCnt3);
	PTIMER_HWA_SetChannelDelay(pPtimer, (uint8_t)(7U), DelayCnt4);
	PTIMER_HWA_LoadValue(pPtimer);
}

void PTIMER_SetPeriod(const PTIMER_HandleType *PtimerHandle, uint16 u16PtimerPeriod)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_SET_PERIOD_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_SET_PERIOD_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];

        PTIMER_HWA_SetMaxCount(pPtimer, u16PtimerPeriod);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_SetPulseOut(uint32 u32SysFreq, const PTIMER_HandleType *PtimerHandle, const PTIMER_PulseOutType *pPulseOutCfg)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if ((pPulseOutCfg == NULL) || (PtimerHandle == NULL))
    {
        PTIMER_ReportDevError(PTIMER_SET_PULSE_OUT_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_SET_PULSE_OUT_ID, PTIMER_E_PARAM_POINTER);
    }
    else if (u32SysFreq == 0U)
    {
        PTIMER_ReportDevError(PTIMER_SET_PULSE_OUT_ID, PTIMER_E_PARAM_VALUE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];

        uint16_t u16PulseOutCfgDlyHigh = PTIMER_CalcDelayValue(u32SysFreq, PtimerHandle->eInstance, pPulseOutCfg->u32PulseOutDlyHighUs);
        uint16_t u16PulseOutCfgDlyLow = PTIMER_CalcDelayValue(u32SysFreq, PtimerHandle->eInstance, pPulseOutCfg->u32PulseOutDlyLowUs);

        PTIMER_HWA_SetPulseOutDelay(pPtimer, u16PulseOutCfgDlyHigh, u16PulseOutCfgDlyLow);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_LoadValue(const PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_LOAD_VALUE_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_LOAD_VALUE_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
        PTIMER_HWA_LoadValue(pPtimer);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_Enable(const PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_ENABLE_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_ENABLE_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
        PTIMER_HWA_Enable(pPtimer);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_Disable(const PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_DISABLE_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_DISABLE_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
        PTIMER_HWA_Disable(pPtimer);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_EnablePulseOut(const PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_PULSE_OUT_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_PULSE_OUT_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
        PTIMER_HWA_EnablePulseOut(pPtimer);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_DisablePulseOut(const PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_DISABLE_PULSE_OUT_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_DISABLE_PULSE_OUT_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
        PTIMER_HWA_DisablePulseOut(pPtimer);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

void PTIMER_GenerateSWTrigger(const PTIMER_HandleType *PtimerHandle)
{
    #if PTIMER_DEV_ERROR_REPORT == STD_ON
    if (PtimerHandle == NULL)
    {
        PTIMER_ReportDevError(PTIMER_GENERATE_SW_TRIGGER_ID, PTIMER_E_PARAM_POINTER);
    }
    else if ((PtimerHandle->eInstance) >= PTIMER_INSTANCE_COUNT)
    {
        PTIMER_ReportDevError(PTIMER_GENERATE_SW_TRIGGER_ID, PTIMER_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PTIMER_Type *const pPtimer = s_apPtimerBase[PtimerHandle->eInstance];
        PTIMER_HWA_GenerateSwTrigger(pPtimer);
        #if PTIMER_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

#endif

