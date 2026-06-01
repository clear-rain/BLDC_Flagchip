/**
 * @file module_driver_ftu.c
 * @author Flagchip032
 * @brief FTU driver source code
 * @version 2.0.0
 * @date 2024-11-10
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip032   N/A          First version
*********************************************************************************/

#include "module_driver_ftu.h"

#if FTU_INSTANCE_COUNT > 0U

#include "module_driver_pcc.h"
#include "module_driver_smisc.h"


#ifndef FTU_DEV_ERROR_REPORT
#define FTU_DEV_ERROR_REPORT	STD_OFF
#endif

#if FTU_DEV_ERROR_REPORT == STD_ON
#define FTU_ReportDevError(func, error) ReportDevError(FTU_MODULE_ID, func, error)
#endif

/********* Local variable ************/
static FTU_Type * const s_pFtuBasePtrs[FTU_INSTANCE_COUNT] = FTU_BASE_PTRS;

/********* Local Functions ************/

/********* Global Functions ************/
/**
 * @brief Initialize FTU basic configuration
 *
 * @param pFtuHandle FTU processing handle
 * @param pCommonStruct the basic configurations of the FTU instance
 */
void FTU_CommonInit(FTU_HandleType *pFtuHandle, const FTU_CommonType *const pCommonStruct)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_COMMON_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pCommonStruct->u32OverflowValue > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_COMMON_INIT_ID, FTU_E_PARAM_COUNT);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		uint32_t u32Loop;
		if (true == pCommonStruct->bGtbEnable)
		{
			FTU_HWA_EnableGlobalTimeBase(pFtu);
		}
		else
		{
			FTU_HWA_DisableGlobalTimeBase(pFtu);
		}
		FTU_HWA_DisableModuleCpwmMode(pFtu);
		/* set FTU prescale */
		FTU_HWA_SetModulePrescale(pFtu, pCommonStruct->ePrescaler);
		/* configure fault filter prescaler */
		FTU_HWA_ConfigModuleFilterPrescale(pFtu, pCommonStruct->eFliterPrescaler);
		/*set the compare register as max value*/
		FTU_HWA_SetModuleCompareValue(pFtu, (uint32_t)pCommonStruct->u32OverflowValue);
		/*set initial value as 0*/
		FTU_HWA_SetCounterInitialValue(pFtu, 0u);
		/*set any value to clear the current counter register to initial value*/
		FTU_HWA_ClearModuleCounter(pFtu, (uint32_t)0x1U);
		/* set ftu OUTMASK sync mode, set bit SYNCHOM and OUTMASK register will update when then sync event happened */
		FTU_HWA_EnableOutputMaskBySync(pFtu);
		/* set ftu debug mode */
		FTU_HWA_ConfigDebugMode(pFtu, (uint32_t)pCommonStruct->eDbgMode);
#ifdef FTU_UPDOWN_DIS_FEATURE
		/* Disable channel match trigger/interrupt when count-up/down in CPWM/QUAD mode */
		FTU_HWA_ConfigUpDownDisable(s_pFtuBasePtrs[eInstance], pCommonStruct->eUpDownDisable);
#endif
		/* configure hardware trigger mode */
		FTU_HWA_ConfigTrigMode(pFtu, pCommonStruct->eHwTrigMode);
		/* configure the frequency of the reload opportunities*/
		FTU_HWA_ConfigFreqOfReloadOp(pFtu, pCommonStruct->u8ReloadFreq);


		pFtuHandle->tStatus.pChannelCallback = NULL;
		pFtuHandle->tStatus.pFaultCallback = NULL;
		pFtuHandle->tStatus.pOverflowCallback = NULL;
		pFtuHandle->tStatus.pReloadPointCallback = NULL;

		/* select clock source */
		if (FTU_INTERNAL_CLK == pCommonStruct->eClkSrc)
		{
			pFtuHandle->tStatus.eFtuClkSrc = FTU_INTERNAL_CLK;
		}
		else if (FTU_EXTERNAL_CLK0 == pCommonStruct->eClkSrc)
		{
			pFtuHandle->tStatus.eFtuClkSrc = FTU_EXTERNAL_CLK0;
#ifdef FTU_TCKSEL_EXIST
			FTU_HWA_ConfigExternalClkSrc(pFtu, FTU_TCLK0_USED);
#else
			SMISC_HWA_SetFtuExternalClkSrc(pFtuHandle->eInstance, FTU_TCLK0_USED);
#endif
		}
		else if (FTU_EXTERNAL_CLK1 == pCommonStruct->eClkSrc)
		{
			pFtuHandle->tStatus.eFtuClkSrc = FTU_EXTERNAL_CLK1;
#ifdef FTU_TCKSEL_EXIST
			FTU_HWA_ConfigExternalClkSrc(pFtu, FTU_TCLK1_USED);
#else
			SMISC_HWA_SetFtuExternalClkSrc(pFtuHandle->eInstance, FTU_TCLK1_USED);
#endif
		}
		else if (FTU_EXTERNAL_CLK2 == pCommonStruct->eClkSrc)
		{
			pFtuHandle->tStatus.eFtuClkSrc = FTU_EXTERNAL_CLK2;
#ifdef FTU_TCKSEL_EXIST
			FTU_HWA_ConfigExternalClkSrc(pFtu, FTU_TCLK2_USED);
#else
			SMISC_HWA_SetFtuExternalClkSrc(pFtuHandle->eInstance, FTU_TCLK2_USED);
#endif
		}
		else
		{
			pFtuHandle->tStatus.eFtuClkSrc = pCommonStruct->eClkSrc;
		}

		for(u32Loop = 0u; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (pCommonStruct->u32InterruptMask & ((uint32_t)FTU_INTR_MASK_CHANNEL_0 << u32Loop)))
			{
				/* Enable Channel Interrupt */
				FTU_HWA_EnableChannelInterrupt(pFtu, (uint8_t)u32Loop);
			}
			else
			{
				/* Disable Channel Interrupt */
				FTU_HWA_DisableChannelInterrupt(pFtu, (uint8_t)u32Loop);
			}
		}

		if (0u != (pCommonStruct->u32InterruptMask & (uint32_t)FTU_INTR_MASK_OVERFLOW))
		{
			/* Enable Overflow Interrupt */
			FTU_HWA_EnableOverflowInterrupt(pFtu);
		}
		else
		{
			/* Disable Overflow Interrupt */
			FTU_HWA_DisableOverflowInterrupt(pFtu);
		}

		if (0u != (pCommonStruct->u32InterruptMask & (uint32_t)FTU_INTR_MASK_FAULT))
		{
			/* Enable Fault Interrupt */
			FTU_HWA_EnableModuleFaultInterrupt(pFtu);
		}
		else
		{
			/* Disable Fault Interrupt */
			FTU_HWA_DisableModuleFaultInterrupt(pFtu);
		}

		if (0u != (pCommonStruct->u32InterruptMask & (uint32_t)FTU_INTR_MASK_RELOAD_POINT))
		{
			/* Enable Reload Point Interrupt */
			FTU_HWA_EnableReloadPointInterrupt(pFtu);
		}
		else
		{
			/* Disable Reload Point Interrupt */
			FTU_HWA_DisableReloadPointInterrupt(pFtu);
		}
		/*register callback functions*/
		pFtuHandle->tStatus.pChannelCallback = pCommonStruct->pChannelCallback;
		pFtuHandle->tStatus.pFaultCallback = pCommonStruct->pFaultCallback;
		pFtuHandle->tStatus.pOverflowCallback = pCommonStruct->pOverflowCallback;
		pFtuHandle->tStatus.pReloadPointCallback = pCommonStruct->pReloadPointCallback;
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief De-initialize the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 */
void FTU_DeInit(FTU_HandleType *pFtuHandle)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_DEINIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		pFtuHandle->tStatus.eFtuClkSrc = FTU_NO_CLK;
		pFtuHandle->tStatus.pChannelCallback = NULL;
		pFtuHandle->tStatus.pFaultCallback = NULL;
		pFtuHandle->tStatus.pOverflowCallback = NULL;
		pFtuHandle->tStatus.pReloadPointCallback = NULL;

		FTU_HWA_ClearModuleRegister(s_pFtuBasePtrs[pFtuHandle->eInstance]);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Fills in the FTU configuration structure with the default settings.
 *
 * @param pCommonStruct Pointer to the user configuration structure
 */
void FTU_GetDefaultInitCfg(FTU_CommonType *pCommonStruct)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if(NULL_PTR == pCommonStruct)
	{
		FTU_ReportDevError(FTU_GET_DEFAULT_INIT_CFG_ID, FTU_E_PARAM_POINTER);
	}
	else
	{
#endif
		pCommonStruct->ePrescaler 			= FTU_DIV_1;
		pCommonStruct->eFliterPrescaler		= FTU_FLT_DIV_1;
		pCommonStruct->u32OverflowValue		= 0xFFFF;
		pCommonStruct->eClkSrc				= FTU_INTERNAL_CLK;
		pCommonStruct->u8ReloadFreq			= 0;
		pCommonStruct->eHwTrigMode			= FTU_CLEARS_TRIG_WHEN_DETECTED;
		pCommonStruct->eDbgMode				= FTU_DBG_COUNTER_STOP_CHN_WORKS;
#ifdef FTU_UPDOWN_DIS_FEATURE
		pCommonStruct->eUpDownDisable		= FTU_DISABLE_TRIG_INTR_NONE;
#endif
		pCommonStruct->bGtbEnable			= false;
		pCommonStruct->u32InterruptMask		= 0u;
		pCommonStruct->pChannelCallback		= NULL;
		pCommonStruct->pFaultCallback		= NULL;
		pCommonStruct->pOverflowCallback	= NULL;
		pCommonStruct->pReloadPointCallback	= NULL;
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Configure FTU to counter mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pCounterStruct the configurations of the counter mode
 * @note This function will stop timer
 */
void FTU_CounterModeInit(FTU_HandleType *pFtuHandle, const FTU_CounterModeType *const pCounterStruct)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if (((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT))
	{
		FTU_ReportDevError(FTU_COUNTER_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (	(pCounterStruct->u32CounterValue > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
			||	(pCounterStruct->u32InitialValue > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
			)
	{
		FTU_ReportDevError(FTU_COUNTER_INIT_ID, FTU_E_PARAM_COUNT);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		/* disable ftu timer */
		FTU_HWA_ConfigModuleClkSrc(pFtu, FTU_MODULE_NO_CLK);
		/* set FTU MOD register value */
		FTU_HWA_SetModuleCompareValue(pFtu, (uint32_t)pCounterStruct->u32CounterValue);
		/*set initial value */
		FTU_HWA_SetCounterInitialValue(pFtu, (uint32_t)pCounterStruct->u32InitialValue);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Update the duty cycle of the FTU Channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pConfig The configuration option for update PWM Duty
 */
void FTU_PwmUpdateDuty(FTU_HandleType *pFtuHandle, FTU_PwmDutyUpdateType *pConfig)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_PWM_UPDATE_DUTY_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pConfig->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_PWM_UPDATE_DUTY_ID, FTU_E_PARAM_CHANNEL);
	}
	else if (pConfig->u32Duty > pFtuHandle->tStatus.u32PwmPeriod)
	{
		FTU_ReportDevError(FTU_PWM_UPDATE_DUTY_ID, FTU_E_PARAM_INVALID);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		/* get the cpwm flag*/
		if(pFtuHandle->tStatus.aPwmAlignedMode == FTU_CENTER_ALIGNED_PWM)
		{
			/* Duty value div 2 if cpwm mode*/
			FTU_HWA_SetChannelValue(pFtu, pConfig->u8Channel, (uint32_t)pConfig->u32Duty >> 1u);
		}
		else
		{
			if (pFtuHandle->tStatus.u8PhaseShiftEnable & (1u << pConfig->u8Channel))
			{
#if FTU_DEV_ERROR_REPORT == STD_ON
				if (pConfig->u32PhaseShift > pFtuHandle->tStatus.u32PwmPeriod)
				{
					FTU_ReportDevError(FTU_PWM_UPDATE_DUTY_ID, FTU_E_PARAM_PHASE_SHIFT);
				}
				else
				{
#endif
					FTU_HWA_SetChannelValue(pFtu, pConfig->u8Channel, pConfig->u32PhaseShift);
					if ((pConfig->u32PhaseShift + pConfig->u32Duty) > pFtuHandle->tStatus.u32PwmPeriod)
					{
						FTU_HWA_SetChannelValue(pFtu, (uint8_t)(pConfig->u8Channel + 1u),
								pConfig->u32PhaseShift + pConfig->u32Duty - pFtuHandle->tStatus.u32PwmPeriod - 1);
					}
					else
					{
						FTU_HWA_SetChannelValue(pFtu, (uint8_t)(pConfig->u8Channel + 1),
								pConfig->u32PhaseShift + pConfig->u32Duty);
					}
#if FTU_DEV_ERROR_REPORT == STD_ON
				}
#endif
			}
			else
			{
				FTU_HWA_SetChannelValue(pFtu, pConfig->u8Channel, pConfig->u32Duty);
			}
		}

		if (pFtuHandle->tStatus.aPwmUpdateMode != FTU_PWM_UPDATE_IMMEDIATELY)
		{
			if (true == pConfig->bUpdate)
			{
				FTU_HWA_GenerateSwSync(pFtu);
			}
		}
		else
		{
			FTU_HWA_GenerateSwSync(pFtu);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Update the duty cycle of the FTU Channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pConfig The configuration option for update PWM Duty
 */
void FTU_PwmUpdateDuty_modify(FTU_HandleType *pFtuHandle, FTU_PwmDutyUpdateType *pConfig)
{

		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		/* get the cpwm flag*/
			/* Duty value div 2 if cpwm mode*/
		pFtu->CONTROLS[pConfig->u8Channel].CVn = ((uint32_t)pConfig->u32Duty >> 1u);

		pFtu->SYNC |= (uint32_t)FTU_SYNC_SWSYNC_MASK;
}

/**
 * @brief Update the Period cycle of the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Period period of the PWM mode
 * @param bUpdate Update/Disupdate pwm
 */
void FTU_PwmUpdatePeriod(FTU_HandleType *pFtuHandle, uint32_t u32Period, bool bUpdate)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_PWM_UPDATE_PERIOD_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (u32Period > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_PWM_UPDATE_PERIOD_ID, FTU_E_PARAM_COUNT);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		/* get the cpwm flag*/
		if(pFtuHandle->tStatus.aPwmAlignedMode == FTU_CENTER_ALIGNED_PWM)
		{
			/* Period value div 2 if cpwm mode*/
			FTU_HWA_SetModuleCompareValue(pFtu, u32Period >> 1);
		}
		else
		{
			FTU_HWA_SetModuleCompareValue(pFtu, u32Period);
		}
		if (pFtuHandle->tStatus.aPwmUpdateMode != FTU_PWM_UPDATE_IMMEDIATELY)
		{
			if (true == bUpdate)
			{
				FTU_HWA_GenerateSwSync(pFtu);
			}
		}
		else
		{
			FTU_HWA_GenerateSwSync(pFtu);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Synchronous update cycle and period of the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 */
void FTU_PwmSyncUpdate(FTU_HandleType *pFtuHandle)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_PWM_SYNC_UPDATE_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_HWA_GenerateSwSync(s_pFtuBasePtrs[pFtuHandle->eInstance]);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

static void set_deadtime(FTU_Type *pFtu, uint8_t u8Channel, uint32_t u32Deadtime)
{
	if(u32Deadtime < 1024u)
	{
		FTU_HWA_ConfigPairDeadtimePrescaler(pFtu, u8Channel, FTU_DEADTIME_PRESCALER_DIV_1);
		FTU_HWA_ConfigPairDeadtimeValue(pFtu, u8Channel, u32Deadtime);
	}
	else if(u32Deadtime < 4096u)
	{
		/*deadtime should multiply 2*/
		FTU_HWA_ConfigPairDeadtimePrescaler(pFtu, u8Channel,
											FTU_DEADTIME_PRESCALER_DIV_4);
		FTU_HWA_ConfigPairDeadtimeValue(pFtu, (uint32_t)u8Channel, u32Deadtime >> 2u);
	}
	else
	{
		/*deadtime should multiply 4*/
		FTU_HWA_ConfigPairDeadtimePrescaler(pFtu, u8Channel, FTU_DEADTIME_PRESCALER_DIV_16);
		FTU_HWA_ConfigPairDeadtimeValue(pFtu, u8Channel, u32Deadtime >> 4u);

	}
}

/**
 * @brief Configure FTU to PWM mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pPwmModeStruct the configurations of the PWM mode
 * @note This function will stop timer
 */
void FTU_PwmModeInit(FTU_HandleType *pFtuHandle, const FTU_PwmModeType *const pPwmModeStruct)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pPwmModeStruct->u32PwmPeriod > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_COUNT);
	}
	else
	{
#endif
		uint8_t u8Channel;
		uint32_t u32Loop;
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		pFtuHandle->tStatus.u32PwmPeriod = pPwmModeStruct->u32PwmPeriod;
		pFtuHandle->tStatus.u8PhaseShiftEnable = 0u;
		pFtuHandle->tStatus.aPwmAlignedMode = pPwmModeStruct->eAlignedMode;
		pFtuHandle->tStatus.aPwmUpdateMode = pPwmModeStruct->eUpdateMode;
		FTU_HWA_SetModuleUpdateRegBySync(pFtu);
		if (pPwmModeStruct->eUpdateMode == FTU_PWM_UPDATE_HALF_PERIOD)
		{
			FTU_HWA_EnableMaxLoadPoint(pFtu);
		}
		else if (pPwmModeStruct->eUpdateMode == FTU_PWM_UPDATE_END_PERIOD)
		{
			FTU_HWA_EnableMinLoadPoint(pFtu);
		}
		else if (pPwmModeStruct->eUpdateMode == FTU_PWM_UPDATE_BOTH_HALF_AND_END_PERIOD)
		{
			FTU_HWA_EnableMaxLoadPoint(pFtu);
			FTU_HWA_EnableMinLoadPoint(pFtu);
		}
		else
		{
			FTU_HWA_ClearPwmSyncMode(pFtu);
			FTU_HWA_SetReinitBySync(pFtu);
		}

		/* disable ftu timer */
		FTU_HWA_ConfigModuleClkSrc(pFtu, FTU_MODULE_NO_CLK);
		if (FTU_EDGE_ALIGNED_PWM == pPwmModeStruct->eAlignedMode)
		{
			FTU_HWA_DisableModuleCpwmMode(pFtu);
			FTU_HWA_SetModuleCompareValue(pFtu, pPwmModeStruct->u32PwmPeriod);
		}
		else
		{
			FTU_HWA_EnableModuleCpwmMode(pFtu);
			FTU_HWA_SetModuleCompareValue(pFtu, pPwmModeStruct->u32PwmPeriod >> 1u);
		}

		for (u32Loop = 0u; u32Loop < pPwmModeStruct->u32ChannelCount; u32Loop++)
		{
#if FTU_DEV_ERROR_REPORT == STD_ON
			if (pPwmModeStruct->pPwmChannels[u32Loop].u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
			{
				FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_CHANNEL);
			}
			else if (pPwmModeStruct->pPwmChannels[u32Loop].u32PwmDuty > pFtuHandle->tStatus.u32PwmPeriod)
			{
				FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_INVALID);
			}
			else
			{
#endif
				FTU_PwmChannelType *pChannelCfg = &pPwmModeStruct->pPwmChannels[u32Loop];
				u8Channel = pChannelCfg->u8Channel;
				if(pChannelCfg->bLinkMode)
				{
#if FTU_DEV_ERROR_REPORT == STD_ON
					if ((pPwmModeStruct->pPwmChannels[u32Loop].u8Channel & 1u) != 0u)
					{
						FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_INVALID_CHANNEL);
					}
					else
					{
#endif
						/* set channel(n+1) complement of channel(n) output */
						FTU_HWA_EnableChannelComplement(pFtu, u8Channel);
						if (!pChannelCfg->bLinkChannelComplement)
						{
							FTU_HWA_ClearChannelPolarity(pFtu, (uint8_t)(1U << u8Channel));
							FTU_HWA_SetChannelPolarity(pFtu, (uint8_t)(1U << (u8Channel + (uint8_t)1U)));
						}
						else
						{
							FTU_HWA_ClearChannelPolarity(pFtu,
														(uint8_t)(1U << u8Channel) | (uint8_t)(1U << (u8Channel  + 1u)));
						}
						/*link mode, the u8Channel+1->csc.ELSB bit must be set*/
						FTU_HWA_ConfigChannelPwmLinkMode(pFtu, (uint8_t)(u8Channel + (uint8_t)1U));
						/* enable u8Channel sync function of the ftu*/
						FTU_HWA_EnableChannelSync(pFtu, u8Channel);
						/* configure pin output as channel mode*/
						FTU_HWA_ConfigTrigOutputMode(pFtu, u8Channel, FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);
						FTU_HWA_ConfigTrigOutputMode(pFtu, (uint8_t)(u8Channel + 1u), FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);
						/* enable FTU output */
						FTU_HWA_EnableChannelsOutput(pFtu, (uint8_t)(3U << u8Channel));
#if FTU_DEV_ERROR_REPORT == STD_ON
					}
#endif
				}
				else
				{
#if FTU_DEV_ERROR_REPORT == STD_ON
					if (pPwmModeStruct->pPwmChannels[u32Loop].u32PhaseShift >= FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
					{
						FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_PHASE_SHIFT);
					}
					else
					{
#endif
						if (pChannelCfg->u32PhaseShift)
						{
#if FTU_DEV_ERROR_REPORT == STD_ON
							if((pPwmModeStruct->pPwmChannels[u32Loop].u8Channel & 1u) != 0u)
							{
								FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_INVALID_CHANNEL);
							}
							else
							{
#endif
								FTU_HWA_ClearChannelPolarity(pFtu, (uint8_t)(1U << (u8Channel + 1)));
								/* enable u8Channel sync function of the ftu*/
								FTU_HWA_EnableChannelSync(pFtu, u8Channel);

								/*Enable enhanced phase shift mode*/
								FTU_HWA_EnableChannelPhase(pFtu, u8Channel);
								FTU_HWA_EnableChannelEnhancedPhase(pFtu, u8Channel);
#if FTU_DEV_ERROR_REPORT == STD_ON
							}
#endif
						}
						else
						{
							/* enable u8Channel sync function of the ftu*/
							FTU_HWA_DisableChannelSync(pFtu, u8Channel);

							/*Enable enhanced phase shift mode*/
							FTU_HWA_DisableChannelPhase(pFtu, u8Channel);
							FTU_HWA_DisableChannelPhase(pFtu, u8Channel);
						}

						/* disable channel(n+1) complement of channel(n) output */
						FTU_HWA_DisableChannelComplement(pFtu, u8Channel);
						FTU_HWA_ClearChannelPolarity(pFtu, (uint8_t)(1U << u8Channel));
						/* enable FTU output */
						FTU_HWA_EnableChannelsOutput(pFtu, (uint8_t)(1U << u8Channel));
						/* configure pin output as channel mode*/
						FTU_HWA_ConfigTrigOutputMode(pFtu, u8Channel, FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);
#if FTU_DEV_ERROR_REPORT == STD_ON
					}
#endif
				}
				FTU_HWA_EnableChannelSync(pFtu, u8Channel);
				/* set FTU pwm mode */
				if (FTU_EDGE_ALIGNED_PWM == pPwmModeStruct->eAlignedMode)
				{
					FTU_HWA_ConfigChannelMode(pFtu, u8Channel, FTU_CHANNEL_MODE_EDGE_ALIGN_PWM);
				}
				FTU_HWA_ConfigChannelEdgeLevel(pFtu, u8Channel, (FTU_ChannelEdgeLevelType)pChannelCfg->ePinMode);

				if (pChannelCfg->bDeadtimeEnable)
				{
					FTU_HWA_EnableChannelDeadtime(pFtu, u8Channel);
				}
				else
				{
					FTU_HWA_DisableChannelDeadtime(pFtu, u8Channel);
				}

				/* set the period time and duty time */
				if(FTU_CENTER_ALIGNED_PWM == pPwmModeStruct->eAlignedMode)
				{
#if FTU_DEV_ERROR_REPORT == STD_ON
					if (0u != pPwmModeStruct->pPwmChannels[u32Loop].u32PhaseShift)
					{
						FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_PHASE_SHIFT);
					}
					else
					{
#endif
						FTU_HWA_SetChannelValue(pFtu, u8Channel, pChannelCfg->u32PwmDuty >> 1u);
#if FTU_DEV_ERROR_REPORT == STD_ON
					}
#endif
				}
				else
				{
#if FTU_DEV_ERROR_REPORT == STD_ON
					if (pPwmModeStruct->pPwmChannels[u32Loop].u32PhaseShift > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
					{
						FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_PHASE_SHIFT);
					}
					else
					{
#endif
						if (pChannelCfg->u32PhaseShift)
						{
#if FTU_DEV_ERROR_REPORT == STD_ON
							if ((pPwmModeStruct->pPwmChannels[u32Loop].u8Channel & 1u) != 0u)
							{
								FTU_ReportDevError(FTU_PWM_MODE_INIT_ID, FTU_E_PARAM_PHASE_SHIFT);
							}
							else
							{
#endif
								pFtuHandle->tStatus.u8PhaseShiftEnable |= (uint8_t)(1u << u8Channel);
								FTU_HWA_SetChannelValue(pFtu, u8Channel, pChannelCfg->u32PhaseShift);
								if ((pChannelCfg->u32PhaseShift + pChannelCfg->u32PwmDuty) > pPwmModeStruct->u32PwmPeriod)
								{
									FTU_HWA_SetChannelValue(pFtu, (uint8_t)(u8Channel + 1),
															pChannelCfg->u32PhaseShift + pChannelCfg->u32PwmDuty - pPwmModeStruct->u32PwmPeriod - 1);
								}
								else
								{
									FTU_HWA_SetChannelValue(pFtu, (uint8_t)(u8Channel + 1),
											pChannelCfg->u32PhaseShift + pChannelCfg->u32PwmDuty);
								}
#if FTU_DEV_ERROR_REPORT == STD_ON
							}
#endif
						}
						else
						{
							FTU_HWA_SetChannelValue(pFtu, u8Channel, pChannelCfg->u32PwmDuty);
						}
#if FTU_DEV_ERROR_REPORT == STD_ON
					}
#endif
				}
				set_deadtime(pFtu, u8Channel, pChannelCfg->u32ChannelDeadtime);
#if FTU_DEV_ERROR_REPORT == STD_ON
			}
#endif
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Update the behavior of Output compare channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pOCConfig the configurations of the output compare mode
 */
void FTU_OutputCompareUpdate(FTU_HandleType *pFtuHandle,
                             const FTU_OutputCompareModeType *const pOCConfig)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_OC_MODE_UPDATE_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pOCConfig->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_OC_MODE_UPDATE_ID, FTU_E_PARAM_CHANNEL);
	}
	else if (pOCConfig->u32CompareValue > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_OC_MODE_UPDATE_ID, FTU_E_PARAM_INVALID);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, pOCConfig->u8Channel, (FTU_ChannelEdgeLevelType)pOCConfig->eOutputMode);
		/* set FTU CV register value*/
		FTU_HWA_SetChannelValue(pFtu, pOCConfig->u8Channel, (uint32_t)pOCConfig->u32CompareValue);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Configure FTU to output compare mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pOCConfig the configurations of the output compare mode
 * @note This function will stop timer
 */
void FTU_OutputCompareModeInit(FTU_HandleType *pFtuHandle,
                               const FTU_OutputCompareModeType *const pOCConfig)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_OC_MODE_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pOCConfig->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_OC_MODE_INIT_ID, FTU_E_PARAM_CHANNEL);
	}
	else if (pOCConfig->u32CompareValue > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_OC_MODE_INIT_ID, FTU_E_PARAM_INVALID);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		/* disable ftu timer */
		FTU_HWA_ConfigModuleClkSrc(pFtu, FTU_MODULE_NO_CLK);
		FTU_HWA_DisableChannelEnhancedPhase(pFtu, pOCConfig->u8Channel);
		FTU_HWA_DisableChannelPhase(pFtu, pOCConfig->u8Channel);
#ifdef FTU_ICM_FEATURE
		FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pOCConfig->u8Channel,
											  FTU_MEASURE_MODE_OFF);
#endif
		FTU_HWA_ConfigChannelMode(pFtu, pOCConfig->u8Channel, FTU_CHANNEL_MODE_OUTPUT_COMPARE);
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, pOCConfig->u8Channel, (FTU_ChannelEdgeLevelType)pOCConfig->eOutputMode);

		/* Disable Up-Down Mode*/
		FTU_HWA_DisableModuleCpwmMode(pFtu);
		/* enable FTU output */
		FTU_HWA_EnableChannelsOutput(pFtu, (uint8_t)(1U << pOCConfig->u8Channel));
		/* configure pin output as channel mode*/
		FTU_HWA_ConfigTrigOutputMode(pFtu, pOCConfig->u8Channel, FTU_TRIG_OUTPUT_AS_CHANNEL_MODE);
		/* set FTU CV register value*/
		FTU_HWA_SetChannelValue(pFtu, pOCConfig->u8Channel, (uint32_t)pOCConfig->u32CompareValue);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Set the value of the FTU Channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Channel FTU Channel
 *
 * @return the value of the FTU Channel
 */
uint32_t FTU_GetChannelValue(FTU_HandleType *pFtuHandle, uint32_t u32Channel)
{
	uint32_t u32ChannelValue;
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		u32ChannelValue = 0;
		FTU_ReportDevError(FTU_GET_CHANNEL_VALUE_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (u32Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		u32ChannelValue = 0;
		FTU_ReportDevError(FTU_GET_CHANNEL_VALUE_ID, FTU_E_PARAM_CHANNEL);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		u32ChannelValue = FTU_HWA_GetChannelValue(pFtu, (uint8_t)u32Channel);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
	return u32ChannelValue;
}

/**
 * @brief Get the value of the FTU counter
 *
 * @param pFtuHandle FTU processing handle
 * @return the counter of the FTU
 */
uint32_t FTU_GetCounter(FTU_HandleType *pFtuHandle)
{
	uint32_t u32Counter;
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		u32Counter = 0;
		FTU_ReportDevError(FTU_GET_COUNTER_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		u32Counter = FTU_HWA_GetCounterValue(pFtu);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
	return u32Counter;
}

/**
 * @brief Set the value of the FTU Channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Channel FTU Channel
 * @param u32Value the value to set
 */
void FTU_SetChannelValue(FTU_HandleType *pFtuHandle, uint32_t u32Channel, uint32_t u32Value)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_SET_CHANNEL_VALUE_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (u32Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_SET_CHANNEL_VALUE_ID, FTU_E_PARAM_CHANNEL);
	}
	else if (u32Value > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_SET_CHANNEL_VALUE_ID, FTU_E_PARAM_COUNT);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		FTU_HWA_SetChannelValue(pFtu, (uint8_t)u32Channel, u32Value);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Enable the output trigger of the selected FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32TriggerOutputMask the output trigger mask
 */
void FTU_EnableTriggerOutput(FTU_HandleType *pFtuHandle, uint32_t u32TriggerOutputMask)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_ENABLE_TRIG_OUT_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		/* enable the channel match trigger */
		FTU_HWA_EnableChannelTriggerOut(pFtu, (uint8_t)(u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_ALL_CHANNEL_MATCH));
		if (0u != (u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_RELOAD))
		{
			/* enable reload trigger */
			FTU_HWA_EnableReloadTrigger(pFtu);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Disable the output trigger of the selected FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32TriggerOutputMask the output trigger mask
 */
void FTU_DisableTriggerOutput(FTU_HandleType *pFtuHandle, uint32_t u32TriggerOutputMask)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_DISABLE_TRIG_OUT_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		/* disable the channel match trigger */
		FTU_HWA_DisableChannelTriggerOut(pFtu, (uint8_t)(u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_ALL_CHANNEL_MATCH));
		if (0u != (u32TriggerOutputMask & (uint32_t)FTU_TRIG_OUTPUT_MASK_RELOAD))
		{
			/* disable reload trigger */
			FTU_HWA_DisableReloadTrigger(pFtu);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Start the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 */
void FTU_StartTimer(FTU_HandleType *pFtuHandle)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_START_TIMER_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pFtuHandle->tStatus.eFtuClkSrc == FTU_NO_CLK)
	{
		FTU_ReportDevError(FTU_START_TIMER_ID, FTU_E_PARAM_INVALID);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		/* set FTU module clock source */
		if(pFtuHandle->tStatus.eFtuClkSrc == FTU_INTERNAL_CLK)
		{
			FTU_HWA_ConfigModuleClkSrc(pFtu, FTU_MODULE_INTERNAL_CLK);
		}
		else
		{
			FTU_HWA_ConfigModuleClkSrc(pFtu, FTU_MODULE_EXTERNAL_CLK);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}
#ifdef FTU_GTB_ADVANCED_CTRL
/**
 * @brief Stop the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 */
void FTU_StopGlobalTimeBase(uint32_t u32InstanceMask)
{
	uint32_t u32GTB = 0u, u32Loop0;
	for (u32Loop0 = 0u; u32Loop0 < FTU_INSTANCE_COUNT; u32Loop0++)
	{
		uint32_t u32InstanceFlag = 1u << u32Loop0;
		if (0u != (u32InstanceMask & u32InstanceFlag))
		{
			u32GTB |= u32InstanceFlag;
			SCM_HWA_ClearFtuGTBMask((uint8_t)u32Loop0);
		}
	}
	SCM_HWA_ClearFtuGTBSelect(u32GTB);
}

/**
 * @brief Start the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 * @param u32StartMask Start time, refer to FTU_GlobalTimeBaseStartType
 */
void FTU_StartGlobalTimeBase(uint32_t u32InstanceMask, uint32_t u32StartMask)
{
	uint32_t u32GTB = 0u, u32Loop0, u32Loop1;
	for (u32Loop0 = 0u; u32Loop0 < FTU_INSTANCE_COUNT; u32Loop0++)
	{
		uint32_t u32InstanceFlag = 1u << u32Loop0;
		if (0u != (u32InstanceMask & u32InstanceFlag))
		{
			if (u32StartMask & FTU_GTB_START_AT_ONCE)
			{
				u32GTB |= u32InstanceFlag;
			}
			for (u32Loop1 = 0u; u32Loop1 < TSTMP_MODULATE_COUNT; u32Loop1++)
			{
				if (u32StartMask & (FTU_GTB_START_AT_TSTMP1_MOD0 << u32Loop1))
				{
					SCM_HWA_ConfigFtuGTBMask((uint8_t)u32Loop0, (1u << u32Loop1));
				}
			}
		}
	}
	SCM_HWA_SetFtuGTBSelect(u32GTB);
}
#endif

/**
 * @brief Stop the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 *
 */
void FTU_StopTimer(FTU_HandleType *pFtuHandle)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_STOP_TIMER_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		/* clear FTU module clock source */
		FTU_HWA_ConfigModuleClkSrc(s_pFtuBasePtrs[pFtuHandle->eInstance], FTU_MODULE_NO_CLK);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief initialize fault input of the selected Ftu instance
 *
 * @param pFtuHandle FTU processing handle
 * @param pFaultInit the fault configurations of the FTU instance
 */
void FTU_FaultInit(FTU_HandleType *pFtuHandle, const FTU_FaultInitType *const pFaultInit)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_FAULT_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		uint32_t u32Loop, u32Temp;
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		/* configure fault mode */
		FTU_HWA_ConfigModuleFaultMode(pFtu, pFaultInit->eFaultMode);
		/* Disable all fault inputs*/
		u32Temp = FTU_HWA_GetFaultEnable(pFtu);
		FTU_HWA_DisableModuleFault(pFtu, 0xFu);
		/* configure fault filter value */
		FTU_HWA_SetModuleFaultFilterValue(pFtu, pFaultInit->u8FilterValue);
		/* recover fault inputs*/
		FTU_HWA_EnableModuleFault(pFtu, (uint8_t)u32Temp);
		/* enables the fault control in channels */
		for(u32Loop = 0u; u32Loop < FTU_FAULT_CHANNEL_COUNT; u32Loop++)
		{
			if (0u != (pFaultInit->u8FaultChannelEnable & ((uint8_t)FTU_FAULT_FOR_CHANNEL01 << u32Loop)))
			{
				FTU_HWA_EnableChannelFault(pFtu, (uint8_t)(u32Loop << 1u));
			}
			else
			{
				FTU_HWA_DisableChannelFault(pFtu, (uint8_t)(u32Loop << 1u));
			}
		}
#ifdef FTU_FAULT_DIS_DELAY_FEATURE
		/* set fault disable channel output delay value */
		FTU_HWA_SetFaultDelay0(pFtu, pFaultInit->u8FaultDisableDelay0);
		FTU_HWA_SetFaultDelay1(pFtu, pFaultInit->u8FaultDisableDelay1);
#endif
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}
#ifdef FTU_FAULT_DIS_DELAY_FEATURE
/**
 * @brief Select fault disable channel output delay value
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 * @param eSelection Fault disable channel output delay value selection.
 */
void FTU_FaultSelectDelayValue(FTU_HandleType *pFtuHandle, uint8_t u8Channel, FTU_FaultDisableDelayType eDelaySelection)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_FAULT_SEL_DELAY_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_FAULT_SEL_DELAY_ID, FTU_E_PARAM_CHANNEL);
	}
	else
	{
#endif
		FTU_HWA_SelectFaultDelay(s_pFtuBasePtrs[pFtuHandle->eInstance], u8Channel, eDelaySelection);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}
#endif
/**
 * @brief Enable a fault input
 *
 * @param pFtuHandle FTU processing handle
 * @param pFaultCtrl configurations of the fault input
 */
void FTU_FaultEnable(FTU_HandleType *pFtuHandle, const FTU_FaultControlType *const pFaultCtrl)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_FAULT_ENABLE_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pFaultCtrl->u8FaultIndex >= FTU_FAULT_INPUT_COUNT(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_FAULT_ENABLE_ID, FTU_E_PARAM_INVALID);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		/* configure fault input polarity */
		FTU_HWA_ConfigFaultPolarity(pFtu, pFaultCtrl->u8FaultIndex, (uint8_t)pFaultCtrl->eFaultPol);
		if(true == pFaultCtrl->bFaultFilterEnable)
		{
			FTU_HWA_EnableModuleFaultGlitchFilter(pFtu, (uint8_t)(1u << pFaultCtrl->u8FaultIndex));
		}
		else
		{
			FTU_HWA_DisableModuleFaultGlitchFilter(pFtu, (uint8_t)(1u << pFaultCtrl->u8FaultIndex));
		}
		/* enable fault input */
		FTU_HWA_EnableModuleFault(pFtu, (uint8_t)(1u << pFaultCtrl->u8FaultIndex));
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Disable a fault input
 *
 * @param pFtuHandle FTU processing handle
 * @param u32FaultIndex index of the fault input
 */
void FTU_FaultDisable(FTU_HandleType *pFtuHandle, uint32_t u32FaultIndex)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_FAULT_DISABLE_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (u32FaultIndex >= FTU_FAULT_INPUT_COUNT(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_FAULT_DISABLE_ID, FTU_E_PARAM_INVALID);
	}
	else
	{
#endif
		FTU_HWA_DisableModuleFault(s_pFtuBasePtrs[pFtuHandle->eInstance], (uint8_t)(0x1u << u32FaultIndex));
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief initialize a input capture channel of the selected Ftu instance
 *
 * @param pFtuHandle FTU processing handle
 * @param pInputChannel configurations of the input capture channel
 */
void FTU_InputCaptureChannelInit(FTU_HandleType *pFtuHandle,
                                 const FTU_InputChannelType *const pInputChannel)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_CHANNEL_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pInputChannel->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_CHANNEL_INIT_ID, FTU_E_PARAM_CHANNEL);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		FTU_HWA_DisableQuadratureMode(pFtu);
		FTU_HWA_DisableChannelEnhancedPhase(pFtu, pInputChannel->u8Channel);
		FTU_HWA_DisableChannelPhase(pFtu, pInputChannel->u8Channel);
#ifdef FTU_ICM_FEATURE
		FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pInputChannel->u8Channel,
											  FTU_MEASURE_MODE_OFF);
#endif
		FTU_HWA_ConfigChannelMode(pFtu, pInputChannel->u8Channel, FTU_CHANNEL_MODE_INPUT);
		if(pInputChannel->u8Channel < FTU_INPUT_FILTER_COUNT)
		{
			/* set FTU input capture filter value */
			FTU_HWA_ConfigInputCaptureFilter(
					pFtu, pInputChannel->u8Channel,
					pInputChannel->u8FilterValue);

		}

		FTU_HWA_ConfigChannelEdgeLevel(pFtu, pInputChannel->u8Channel, (FTU_ChannelEdgeLevelType)pInputChannel->eInputMode);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief initialize the quadrature decoder mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pQuadInit configurations of the quadrature decoder
 */
void FTU_QuadratureModeInit(FTU_HandleType *pFtuHandle,
                            const FTU_QuadratureInitType *const pQuadInit)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_QD_MODE_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (0U == FTU_INSTANCE_QD_SUPPORT(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_QD_MODE_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		/* set quadrature mode */
		FTU_HWA_ConfigQuadratureMode(pFtu, pQuadInit->eQuadMode);
		/* set PHA polarity*/
		if(pQuadInit->bPhaInverted)
		{
			FTU_HWA_EnablePhaInv(pFtu);
		}
		else
		{
			FTU_HWA_DisablePhaInv(pFtu);
		}
		/* set PHB polarity*/
		if(pQuadInit->bPhbInverted)
		{
			FTU_HWA_EnablePhbInv(pFtu);
		}
		else
		{
			FTU_HWA_DisablePhbInv(pFtu);
		}
		/* prescale should not be set in QD mode */
		FTU_HWA_SetModulePrescale(pFtu, FTU_DIV_1);
		/* set top value */
		FTU_HWA_SetModuleCompareValue(pFtu, pQuadInit->u16TopValue);
		/* set bottom value */
		FTU_HWA_SetCounterInitialValue(pFtu, pQuadInit->u16BottomValue);

		/* Set phase A glitch filter value */
		if (0U != pQuadInit->u8PhaFilterVal)
		{
			FTU_HWA_ConfigChannelFilterValue(pFtu, 0, pQuadInit->u8PhaFilterVal);
			FTU_HWA_EnablePhaGlitchFilter(pFtu);
		}
		else
		{
			FTU_HWA_DisablePhaGlitchFilter(pFtu);
		}
		/* Set phase B glitch filter value */
		if (0U != pQuadInit->u8PhbFilterVal)
		{
			FTU_HWA_ConfigChannelFilterValue(pFtu, 1, pQuadInit->u8PhbFilterVal);
			FTU_HWA_EnablePhbGlitchFilter(pFtu);
		}
		else
		{
			FTU_HWA_DisablePhbGlitchFilter(pFtu);
		}
		/* enable the quadrature*/
		FTU_HWA_EnableQuadratureMode(pFtu);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}
/**
 * @brief Enable FTU interrupt
 *
 * @param pFtuHandle FTU processing handle
 * @param u32InterruptMask interrupt enable mask
 */
void FTU_EnableInterrupt(FTU_HandleType *pFtuHandle, uint32_t u32InterruptMask)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_ENABLE_INTR_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		uint32_t u32Loop;

		for(u32Loop = 0u; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (u32InterruptMask & ((uint32_t)FTU_INTR_MASK_CHANNEL_0 << u32Loop)))
			{
				/* Enable Channel Interrupt */
				FTU_HWA_EnableChannelInterrupt(pFtu, (uint8_t)u32Loop);
			}
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_OVERFLOW))
		{
			/* Enable Overflow Interrupt */
			FTU_HWA_EnableOverflowInterrupt(pFtu);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_FAULT))
		{
			/* Enable Fault Interrupt */
			FTU_HWA_EnableModuleFaultInterrupt(pFtu);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_RELOAD_POINT))
		{
			/* Enable Reload Point Interrupt */
			FTU_HWA_EnableReloadPointInterrupt(pFtu);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Disable FTU interrupt
 *
 * @param pFtuHandle FTU processing handle
 * @param u32InterruptMask interrupt disable mask
 */
void FTU_DisableInterrupt(FTU_HandleType *pFtuHandle, uint32_t u32InterruptMask)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_DISABLE_INTR_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
		uint32_t u32Loop;

		for(u32Loop = 0; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (u32InterruptMask & ((uint32_t)FTU_INTR_MASK_CHANNEL_0 << u32Loop)))
			{
				/* Disable Channel Interrupt */
				FTU_HWA_DisableChannelInterrupt(pFtu, (uint8_t)u32Loop);
			}
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_OVERFLOW))
		{
			/* Disable Overflow Interrupt */
			FTU_HWA_DisableOverflowInterrupt(pFtu);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_FAULT))
		{
			/* Disable Fault Interrupt */
			FTU_HWA_DisableModuleFaultInterrupt(pFtu);
		}

		if (0u != (u32InterruptMask & (uint32_t)FTU_INTR_MASK_RELOAD_POINT))
		{
			/* Disable Reload Point Interrupt */
			FTU_HWA_DisableReloadPointInterrupt(pFtu);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Clear the fault flag of the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32FaultFlag flag to clear
 */
void FTU_ClearFault(FTU_HandleType *pFtuHandle, uint32_t u32FaultFlag)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_CLEAR_FAULT_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_HWA_ClearModuleFaultFlag(s_pFtuBasePtrs[pFtuHandle->eInstance], (uint8_t)u32FaultFlag);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Get the fault flag of the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @return uint32_t the fault flag of the selected Ftu instance
 */
uint32_t FTU_GetFaultFlag(FTU_HandleType *pFtuHandle)
{
	uint32_t u32FaultFlag = 0;
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_GET_FAULT_FLAG_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		u32FaultFlag = FTU_HWA_ReadModuleFaultFlag(s_pFtuBasePtrs[pFtuHandle->eInstance]);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
	return u32FaultFlag;
}


/**
 * @brief Enable ftu channel DMA
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Channel The FTU channel .
 */
void FTU_EnableChannelDma(FTU_HandleType *pFtuHandle, uint32_t u32Channel)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_ENABLE_CHANNEL_DMA_ID, FTU_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		FTU_HWA_EnableChannelDma(s_pFtuBasePtrs[pFtuHandle->eInstance], (uint8_t)u32Channel);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

#ifdef FTU_ICM_FEATURE
/**
 * @brief Initialize a Expect Edge Number Measurement channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pExpectEdumMeasure measurement configuration.
 */
void FTU_ExpectEdgeNumberMeasureChannelInit(FTU_HandleType *pFtuHandle, FTU_ExpectEdgeNumberMeasureType *pExpectEdgeNumMeasure)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_EXPENM_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pExpectEdgeNumMeasure->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_EXPENM_INIT_ID, FTU_E_PARAM_CHANNEL);
	}
	else if ((pExpectEdgeNumMeasure->u8Channel & 1u) != 0u)
	{
		FTU_ReportDevError(FTU_IC_EXPENM_INIT_ID, FTU_E_PARAM_CHANNEL);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		FTU_HWA_ConfigChannelMode(pFtu, pExpectEdgeNumMeasure->u8Channel,
								  FTU_CHANNEL_MODE_INPUT);
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, pExpectEdgeNumMeasure->u8Channel,
						   pExpectEdgeNumMeasure->eEdgeMode);
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, pExpectEdgeNumMeasure->u8Channel + 1u,
									   FTU_CHANNEL_EDGE_NOT_USED);
		FTU_HWA_ConfigEdgeNumber(pFtu, pExpectEdgeNumMeasure->u8Channel + 1,
								 pExpectEdgeNumMeasure->u8ExpectEdgeNumber);
		if (FTU_MEASURE_CONTINUOUS_MODE == pExpectEdgeNumMeasure->eContinuouslyMode)
		{
			FTU_HWA_EnableMeasureContinous(pFtu, pExpectEdgeNumMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureContinous(pFtu, pExpectEdgeNumMeasure->u8Channel);
		}
		/* Must put the ICM_MODE setting at the end, otherwise it will not be configured correctly. */
		FTU_HWA_ConfigInputCaptureMeasureMode(	pFtu, pExpectEdgeNumMeasure->u8Channel,
												FTU_MEASURE_EXPECT_EDGE_NUMBER);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Initialize a Edge Number Measurement channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pEdgeNumMeasure measurement configuration.
 */
void FTU_EdgeNumberMeasureChannelInit(FTU_HandleType *pFtuHandle, FTU_EdgeNumberMeasureType *pEdgeNumMeasure)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_ENM_INIT_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (pEdgeNumMeasure->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_ENM_INIT_ID, FTU_E_PARAM_CHANNEL);
	}
	else if ((pEdgeNumMeasure->u8Channel & 1u) != 0u)
	{
		FTU_ReportDevError(FTU_IC_ENM_INIT_ID, FTU_E_PARAM_CHANNEL);
	}
	else if (pEdgeNumMeasure->u32StartWindow >= pEdgeNumMeasure->u32EndWindow)
	{
		FTU_ReportDevError(FTU_IC_ENM_INIT_ID, FTU_E_PARAM_INVALID);
	}
	else if (pEdgeNumMeasure->u32EndWindow > FTU_GET_MAX_COUNTER(s_pFtuBasePtrs[pFtuHandle->eInstance]))
	{
		FTU_ReportDevError(FTU_IC_ENM_INIT_ID, FTU_E_PARAM_COUNT);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		FTU_HWA_ConfigChannelMode(pFtu, pEdgeNumMeasure->u8Channel,
								  FTU_CHANNEL_MODE_INPUT);
		FTU_HWA_ConfigChannelEdgeLevel(pFtu, pEdgeNumMeasure->u8Channel, pEdgeNumMeasure->eEdgeMode);

		FTU_HWA_ConfigChannelEdgeLevel(pFtu, pEdgeNumMeasure->u8Channel + 1u,
									   FTU_CHANNEL_EDGE_NOT_USED);
		FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pEdgeNumMeasure->u8Channel,
											  FTU_MEASURE_ICENM_WIND_WRITE);
		FTU_HWA_SetChannelValue(pFtu, pEdgeNumMeasure->u8Channel,
								pEdgeNumMeasure->u32StartWindow);
		FTU_HWA_SetChannelValue(pFtu, pEdgeNumMeasure->u8Channel + 1u,
								pEdgeNumMeasure->u32EndWindow);
		FTU_HWA_ConfigInputCaptureMeasureMode(  pFtu, pEdgeNumMeasure->u8Channel,
												FTU_MEASURE_EDGE_NUMBER);
		if (FTU_MEASURE_CONTINUOUS_MODE == pEdgeNumMeasure->eContinuouslyMode)
		{
			FTU_HWA_EnableMeasureContinous(pFtu, pEdgeNumMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureContinous(pFtu, pEdgeNumMeasure->u8Channel);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Get the expect edge number result of the channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 */
void FTU_GetExpectEdgeNumberResult(FTU_HandleType *pFtuHandle, uint8_t u8Channel, FTU_ExpectEdgeNumberResultType *pResult)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_EXPENM_GET_ID, FTU_E_PARAM_INSTANCE);
	}
	else if (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_EXPENM_GET_ID, FTU_E_PARAM_CHANNEL);
	}
	else if ((u8Channel & 1u) != 0u)
	{
		FTU_ReportDevError(FTU_IC_EXPENM_GET_ID, FTU_E_PARAM_CHANNEL);
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		pResult->u32FirstEdgeTime = FTU_HWA_GetChannelValue(pFtu, u8Channel);
		pResult->u32LastEdgeTime = FTU_HWA_GetChannelValue(pFtu, u8Channel + 1);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Get Edge number counter
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number.
 * @return uint8_t Edge number counter
 */
uint8_t FTU_GetEdgeNumberCount(FTU_HandleType *pFtuHandle, uint8_t u8Channel)
{
	uint8_t u8Count;
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_ENM_GET_ID, FTU_E_PARAM_INSTANCE);
		u8Count = 0;
	}
	else if (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_ENM_GET_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else if ((u8Channel & 1u) != 0u)
	{
		FTU_ReportDevError(FTU_IC_ENM_GET_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else
	{
#endif
		u8Count = FTU_HWA_GetEdgeNumberCount(s_pFtuBasePtrs[pFtuHandle->eInstance], u8Channel);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
	return u8Count;
}
/**
 * @brief Initialize a signal measure channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pMeasure measurement configuration.
 */
void FTU_SignalMeasureChannelInit(FTU_HandleType *pFtuHandle, FTU_SignalMeasureType *pMeasure)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_INIT_ID, FTU_E_PARAM_INSTANCE);
		u8Count = 0;
	}
	else if (pMeasure->u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_INIT_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else if ((pMeasure->u8Channel & 1u) != 0u)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_INIT_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel, FTU_MEASURE_MODE_OFF);
		FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_OFF);
		FTU_HWA_DisableChannelEnhancedPhase(pFtu, pMeasure->u8Channel);
		FTU_HWA_DisableChannelPhase(pFtu, pMeasure->u8Channel);
		FTU_HWA_DisableChannelEnhancedPhase(pFtu, pMeasure->u8Channel + 1u);
		FTU_HWA_DisableChannelPhase(pFtu, pMeasure->u8Channel + 1u);
		FTU_HWA_DisableModuleCpwmMode(pFtu);

		FTU_HWA_ConfigChannelMode(pFtu, pMeasure->u8Channel, FTU_CHANNEL_MODE_INPUT);
		FTU_HWA_ConfigChannelMode(pFtu, pMeasure->u8Channel + 1u, FTU_CHANNEL_MODE_INPUT);
		if (FTU_SIGNAL_MEASURE_HIGH_TIME == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel, FTU_CHANNEL_EDGE_RISING);
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_FALLING);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel + 1, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_SetChannelPolarity(pFtu, 1u << pMeasure->u8Channel);
		}
		else if (FTU_SIGNAL_MEASURE_LOW_TIME == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel, FTU_CHANNEL_EDGE_RISING);
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_FALLING);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_DUTY_CYCLE);
			FTU_HWA_ClearChannelPolarity(pFtu, 1u << pMeasure->u8Channel);
		}
		else if (FTU_SIGNAL_MEASURE_PERIOD_RISING_EDGE == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel, FTU_CHANNEL_EDGE_RISING);
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_NOT_USED);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel, FTU_MEASURE_MODE_PERIOD);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_PERIOD);
		}
		else if (FTU_SIGNAL_MEASURE_PERIOD_FALLING_EDGE == pMeasure->eMeasureMode)
		{
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel, FTU_CHANNEL_EDGE_FALLING);
			FTU_HWA_ConfigChannelEdgeLevel(pFtu, pMeasure->u8Channel + 1u, FTU_CHANNEL_EDGE_NOT_USED);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel, FTU_MEASURE_MODE_PERIOD);
			FTU_HWA_ConfigInputCaptureMeasureMode(pFtu, pMeasure->u8Channel + 1u, FTU_MEASURE_MODE_PERIOD);
		}

		if (FTU_MEASURE_CONTINUOUS_MODE == pMeasure->eContinuouslyMode)
		{
			FTU_HWA_EnableMeasureContinous(pFtu, pMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureContinous(pFtu, pMeasure->u8Channel);
		}

		if (FTU_MEASURE_START_IMMEDIATELY == pMeasure->eStartMode)
		{
			FTU_HWA_EnableMeasureStartImmd(pFtu, pMeasure->u8Channel);
		}
		else
		{
			FTU_HWA_DisableMeasureStartImmd(pFtu, pMeasure->u8Channel);
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}
/**
 * @brief Re-start measurement when in single mode
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 */
void FTU_SignalMeasureChannelSingle(FTU_HandleType *pFtuHandle, uint8_t u8Channel)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_SINGLE_ID, FTU_E_PARAM_INSTANCE);
		u8Count = 0;
	}
	else if (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_SINGLE_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else if ((u8Channel & 1u) != 0u)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_SINGLE_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else
	{
#endif
		FTU_HWA_SingleMeasurement(s_pFtuBasePtrs[pFtuHandle->eInstance], u8Channel);
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Get the measurement result of the channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 */
void FTU_GetSignalMeasureResult(FTU_HandleType *pFtuHandle, uint8_t u8Channel, FTU_SignalMeasureValueType *pResult)
{
#if FTU_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pFtuHandle->eInstance >= FTU_INSTANCE_COUNT)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_GET_ID, FTU_E_PARAM_INSTANCE);
		u8Count = 0;
	}
	else if (u8Channel >= FTU_CHANNEL_CONTROLS_COUNT)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_GET_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else if ((u8Channel & 1u) != 0u)
	{
		FTU_ReportDevError(FTU_IC_SIG_MEAS_GET_ID, FTU_E_PARAM_CHANNEL);
		u8Count = 0;
	}
	else
	{
#endif
		FTU_Type * const pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];

		FTU_MeasurementModeType eMeasureMode = FTU_HWA_GetMeasureMode(pFtu, u8Channel);
		if (FTU_MEASURE_MODE_DUTY_CYCLE == eMeasureMode)
		{
			if (FTU_HWA_GetChannelPolarity(pFtu, 1u << u8Channel))
			{
				pResult->u32StartTime = FTU_HWA_GetChannelValue(pFtu, u8Channel);
				pResult->u32EndTime = FTU_HWA_GetChannelValue(pFtu, u8Channel + 1);
			}
			else
			{
				pResult->u32StartTime = FTU_HWA_GetChannelValue(pFtu, u8Channel + 1);
				pResult->u32EndTime = FTU_HWA_GetChannelValue(pFtu, u8Channel);
			}
		}
		else if(FTU_MEASURE_MODE_PERIOD == eMeasureMode)
		{
			pResult->u32StartTime = FTU_HWA_GetChannelValue(pFtu, u8Channel + 1);
			pResult->u32EndTime = FTU_HWA_GetChannelValue(pFtu, u8Channel);
		}
		else
		{
			pResult->u32StartTime = 0u;
			pResult->u32EndTime = 0u;
		}
#if FTU_DEV_ERROR_REPORT == STD_ON
	}
#endif
}
#endif

/**
 * @brief Interrupt IRQ handle of FTU instance
 *
  * @param pFtuHandle FTU processing handle
 */
void FTUn_IRQHandler(FTU_HandleType *pFtuHandle)
{
	FTU_Type *pFtu = s_pFtuBasePtrs[pFtuHandle->eInstance];
	uint32_t u32FaultFlag = 0u;
	uint8_t u8FaultEnable = FTU_HWA_ReadFaultIntrEnable(pFtu);
	uint8_t u8OverflowFlag = FTU_HWA_ReadModuleOverflowFlag(pFtu);
	uint8_t u8ReloadFlag = FTU_HWA_ReadReloadIntrEnable(pFtu);
	uint32_t u32Loop, u32ChannelIntrFlag = 0, u32TimeStamp;
    
	u8OverflowFlag = FTU_HWA_ReadModuleOverflowIntrEnable(pFtu) & u8OverflowFlag;
	u8ReloadFlag = FTU_HWA_ReadModuleReloadFlag(pFtu) & u8ReloadFlag;
	if(0u != u8FaultEnable)
	{
		u32FaultFlag = FTU_HWA_ReadModuleFaultFlag(pFtu);
	}

	/* Clear interrupt flag*/
	if (0u != u8OverflowFlag)
	{
		FTU_HWA_ClearOverflowFlag(pFtu);
	}
	if (0u != u8ReloadFlag)
	{
		FTU_HWA_ClearReloadFlag(pFtu);
	}

	for (u32Loop = 0U; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
	{
		if ((0u != FTU_HWA_ReadChannelInterruptFlag(pFtu, (uint8_t)u32Loop)) &&
			(0u != FTU_HWA_ReadChannelInterruptEnableFlag(pFtu, (uint8_t)u32Loop)))
		{
			FTU_HWA_ClearChannelInterruptFlag(pFtu, (uint8_t)u32Loop);
			u32ChannelIntrFlag |= (uint8_t)(1u << u32Loop);
		}
	}

	/* call callback functions*/
	if ((0u != u8OverflowFlag) && (NULL != pFtuHandle->tStatus.pOverflowCallback))
	{
		pFtuHandle->tStatus.pOverflowCallback(pFtuHandle);
	}

	if ((0u != u8ReloadFlag) && (NULL != pFtuHandle->tStatus.pReloadPointCallback))
	{
		pFtuHandle->tStatus.pReloadPointCallback(pFtuHandle);
	}

	if ((0u != u32FaultFlag) && (NULL != pFtuHandle->tStatus.pFaultCallback))
	{
		uint32_t u32FaultInputCount = FTU_FAULT_INPUT_COUNT(s_pFtuBasePtrs[pFtuHandle->eInstance]);
		for (u32Loop = 0U; u32Loop < u32FaultInputCount; u32Loop++)
		{
			if (0u != (u32FaultFlag & ((uint32_t)1u << u32Loop)))
			{
				pFtuHandle->tStatus.pFaultCallback(pFtuHandle, u32Loop);
			}
		}
	}

	if ((0u != u32ChannelIntrFlag) && (NULL != pFtuHandle->tStatus.pChannelCallback))
	{
		for (u32Loop = 0U; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
		{
			if (0u != (u32ChannelIntrFlag & ((uint32_t)1u << u32Loop)))
			{
				u32TimeStamp = FTU_HWA_GetChannelValue(pFtu, (uint8_t)u32Loop);
				pFtuHandle->tStatus.pChannelCallback(pFtuHandle, u32Loop, u32TimeStamp);
			}
		}
	}
}

#endif
