/**
 * @file module_driver_fcpit.h
 * @author Flagchip032
 * @brief FCPIT driver source code
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
*   2.0.0       2024-04-20    QXW0076   N/A          First version
*********************************************************************************/

#include "module_driver_fcpit.h"

#if FCPIT_INSTANCE_COUNT > 0U

#ifndef FCPIT_DEV_ERROR_REPORT
#define FCPIT_DEV_ERROR_REPORT	STD_OFF
#endif

#if FCPIT_DEV_ERROR_REPORT == STD_ON
#define FCPIT_ReportDevError(func, error) ReportDevError(FCPIT_MODULE_ID, func, error)
#endif

/* global functions */
/**
 * @brief Initialize Fcpit instance common feature.
 * @param pFcpitHandle Fcpit processing handle
 * @param pInitStruct Fcpit initialization structure
 */
void FCPIT_CommonInit(FCPIT_HandleType *pFcpitHandle,const FCPIT_CommonInitType * pInitStruct)
{
	/*Enable module clock*/
	FCPIT_HWA_EnableModule();
	if (pInitStruct->bDebugEn)
	{
		FCPIT_HWA_SetChannelRunOnDebug();
	}
	else
	{
		FCPIT_HWA_SetChannelStopOnDebug();
	}

	if (pInitStruct->bLowPowerModeEn)
	{
		FCPIT_HWA_SetChannelRunOnLpm();
	}
	else
	{
		FCPIT_HWA_SetChannelStopOnLpm();
	}
	/*Send info to global handler*/
	pFcpitHandle->bDebugEn = pInitStruct->bDebugEn;
	pFcpitHandle->bLowPowerModeEn = pInitStruct->bLowPowerModeEn;
}


/* global functions */
/**
 * @brief Initialize Fcpit instance.
 * @param pFcpitHandle Fcpit processing handle
 * @param pInitStruct Fcpit initialization structure
 */
void FCPIT_ChannelInit(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelInitType * pInitStruct)
{
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pInitStruct->eFcpitChannel >= FCPIT_CHANNEL_MAX)
	{
		FCPIT_ReportDevError(FCPIT_CHANNEL_INIT_ID, FCPIT_E_PARAM_CHANNEL);
	}
	else
	{
#endif
    	/*Enable module clock*/
		FCPIT_HWA_EnableModule();
        /* w1c , clear channel interrupt flag*/
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)1U << (uint32_t)pInitStruct->eFcpitChannel);

        FCPIT_HWA_ConfigChannel(pInitStruct->eFcpitChannel, (uint32_t)0U);

        /*config mode*/
        FCPIT_HWA_ConfigChannelMode(pInitStruct->eFcpitChannel, pInitStruct->eMode);

        if ((pInitStruct->eFcpitChannel > FCPIT_CHANNEL_0) && (pInitStruct->bChainModeEn))
        {
            FCPIT_HWA_EnableChannelChainMode(pInitStruct->eFcpitChannel);
        }
        /*config value*/
        FCPIT_HWA_SetChannelValue(pInitStruct->eFcpitChannel, pInitStruct->u32TimerValue);

        /*Send info to global handler*/
        pFcpitHandle->tChannelStatus[(uint8_t)pInitStruct->eFcpitChannel].bChainModeEn = pInitStruct->bChainModeEn;
        pFcpitHandle->tChannelStatus[(uint8_t)pInitStruct->eFcpitChannel].eMode = pInitStruct->eMode;
        pFcpitHandle->tChannelStatus[(uint8_t)pInitStruct->eFcpitChannel].u32TimerValue = pInitStruct->u32TimerValue;

#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Initialize Fcpit trigger configuration
 * @param pFcpitHandle Fcpit processing handle
 * @param pTrgStruct Fcpit trigger structure
 */
void FCPIT_InitTrigger(FCPIT_HandleType *pFcpitHandle,const FCPIT_TriggerType * pTrgStruct)
{
#if FCPIT_DEV_ERROR_REPORT == STD_ON

	if (NULL == pTrgStruct)
	{
		FCPIT_ReportDevError(FCPIT_INIT_TRIGGER_ID, FCPIT_E_PARAM_POINTER);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_INIT_TRIGGER_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif

        if (pTrgStruct->bStartOnTrigger)
        {
            FCPIT_HWA_SetChannelStartOnTrig(pTrgStruct->eFcpitChannel);
        }
        else
        {
            FCPIT_HWA_ClearChannelStartOnTrig(pTrgStruct->eFcpitChannel);
        }

        if (pTrgStruct->bStopOnInterrupt)
        {
            FCPIT_HWA_SetChannelStopOnInterrupt(pTrgStruct->eFcpitChannel);
        }
        else
        {
            FCPIT_HWA_ClearChannelStopOnInterrupt(pTrgStruct->eFcpitChannel);
        }

        if (pTrgStruct->bReloadOnTrigger)
        {
            FCPIT_HWA_SetChannelReloadOnTrig(pTrgStruct->eFcpitChannel);
        }
        else
        {
            FCPIT_HWA_ClearChannelReloadOnTrig(pTrgStruct->eFcpitChannel);
        }

        if (FCPIT_TRIGGER_EXTERNAL != pTrgStruct->eTriggerSel)
        {
            FCPIT_HWA_SetChannelTriggerSrc(pTrgStruct->eFcpitChannel);
            FCPIT_HWA_SelectChannelTrigger(pTrgStruct->eFcpitChannel, pTrgStruct->eTriggerSel);
        }
        else
        {
            FCPIT_HWA_ClearChannelTriggerSrc(pTrgStruct->eFcpitChannel);
            FCPIT_HWA_SelectChannelTrigger(pTrgStruct->eFcpitChannel, pTrgStruct->eFcpitChannel);
        }
        /*Send info to global handler*/
        pFcpitHandle->tChannelStatus[(uint8_t)pTrgStruct->eFcpitChannel].bStartOnTrigger = pTrgStruct->bStartOnTrigger;
        pFcpitHandle->tChannelStatus[(uint8_t)pTrgStruct->eFcpitChannel].bStopOnInterrupt = pTrgStruct->bStopOnInterrupt;
        pFcpitHandle->tChannelStatus[(uint8_t)pTrgStruct->eFcpitChannel].bReloadOnTrigger = pTrgStruct->bReloadOnTrigger;
        pFcpitHandle->tChannelStatus[(uint8_t)pTrgStruct->eFcpitChannel].eTriggerSel = pTrgStruct->eTriggerSel;


#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief De-initialize Fcpit instance.
 * @param pFcpitHandle Fcpit processing handle
 */
void FCPIT_Deinit(FCPIT_HandleType *pFcpitHandle)
{

    uint8_t u8Index;
    FCPIT_HWA_ConfigModule((uint32_t)FCPIT_MCR_M_CEN_MASK);
    /*clear flag*/
    FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)(FCPIT_MSR_TIF3_MASK | FCPIT_MSR_TIF2_MASK | FCPIT_MSR_TIF1_MASK |
                                                    FCPIT_MSR_TIF0_MASK));
    /*clear enable bit*/
    FCPIT_HWA_DisableChannelsInterrupt((uint32_t)0xFU);

    /*clear channel bit*/
    for (u8Index = 0U; u8Index < MAX_FCPIT_CHANNEL_NUM; u8Index++)
    {
        FCPIT_HWA_ConfigChannel((FCPIT_ChannelType)u8Index, (uint32_t)0U);
        FCPIT_HWA_SetChannelValue((FCPIT_ChannelType)u8Index, (uint32_t)0U);
        /*clear info to global handler*/
        pFcpitHandle->tChannelStatus[u8Index].eMode = FCPIT_CHANNEL_NOMODE;
		pFcpitHandle->tChannelStatus[u8Index].bChainModeEn= false;
		pFcpitHandle->tChannelStatus[u8Index].u32TimerValue = 0u;
		pFcpitHandle->tChannelStatus[u8Index].bStartOnTrigger = false;
		pFcpitHandle->tChannelStatus[u8Index].bStopOnInterrupt = false;
		pFcpitHandle->tChannelStatus[u8Index].bReloadOnTrigger = false;
		pFcpitHandle->tChannelStatus[u8Index].eTriggerSel = FCPIT_NO_TRIGGER;
		pFcpitHandle->tChannelStatus[u8Index].bChannelIsrEn = false;
		pFcpitHandle->tChannelStatus[u8Index].pChannelCallback = NULL;
		pFcpitHandle->tChannelStatus[u8Index].bChannelStarted = false;
    }
    FCPIT_HWA_ConfigModule((uint32_t)0U);
    pFcpitHandle->bDebugEn = false;
    pFcpitHandle->bLowPowerModeEn = false;

}

/**
 * @brief Initialize Fcpit interrupt functionality
 * @param pFcpitHandle Fcpit processing handle
 * @param pIntStruct Fcpit interrupt structure
 * @note this function will stop timer
 */
void FCPIT_InitInterrupt(FCPIT_HandleType *pFcpitHandle,const FCPIT_IntType * pIntStruct)
{
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if (NULL == pIntStruct)
	{
		FCPIT_ReportDevError(FCPIT_INIT_INTERRUPT_ID, FCPIT_E_PARAM_POINTER);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_INIT_INTERRUPT_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif

        FCPIT_HWA_DisableChannel(pIntStruct->eFcpitChannel);
        /* w1c , clear channel interrupt flag*/
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)1U << (uint32_t)pIntStruct->eFcpitChannel);
        if (pIntStruct->bChannelIsrEn)
        {
            FCPIT_HWA_EnableChannelsInterrupt((uint32_t)1U << (uint32_t)pIntStruct->eFcpitChannel);
            pFcpitHandle->tChannelStatus[pIntStruct->eFcpitChannel].pChannelCallback = pIntStruct->pChannelCallback;
        }
        else
        {
            FCPIT_HWA_DisableChannelsInterrupt((uint32_t)1U << (uint32_t)pIntStruct->eFcpitChannel);
            pFcpitHandle->tChannelStatus[pIntStruct->eFcpitChannel].pChannelCallback = NULL;
        }
        pFcpitHandle->tChannelStatus[pIntStruct->eFcpitChannel].bChannelIsrEn = pIntStruct->bChannelIsrEn;

#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Enable Fcpit interrupt
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_EnableInterrupt(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel)

{
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if (FCPIT_CHANNEL_MAX <= eChannel)
	{
		FCPIT_ReportDevError(FCPIT_ENABLE_INTERRUPT_ID, FCPIT_E_PARAM_CHANNEL);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_ENABLE_INTERRUPT_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif

        FCPIT_HWA_DisableChannel(eChannel);
        /* w1c , clear channel interrupt flag*/
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)1U << (uint32_t)eChannel);
        FCPIT_HWA_EnableChannelsInterrupt((uint32_t)1U << (uint32_t)eChannel);
        FCPIT_HWA_EnableChannel(eChannel);
        pFcpitHandle->tChannelStatus[(uint8_t)eChannel].bChannelIsrEn = true;

#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Disable Fcpit interrupt
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_DisableInterrupt(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel)
{

#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if (FCPIT_CHANNEL_MAX <= eChannel)
	{
		FCPIT_ReportDevError(FCPIT_DISABLE_INTERRUPT_ID, FCPIT_E_PARAM_CHANNEL);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_DISABLE_INTERRUPT_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif
        FCPIT_HWA_DisableChannel(eChannel);
        /* w1c , clear channel interrupt flag*/
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)1U << (uint32_t)eChannel);
        FCPIT_HWA_DisableChannelsInterrupt((uint32_t)1U << (uint32_t)eChannel);
        FCPIT_HWA_EnableChannel(eChannel);

        pFcpitHandle->tChannelStatus[(uint8_t)eChannel].bChannelIsrEn = false;
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Fcpit start timer
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_Start(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel)
{

#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if (FCPIT_CHANNEL_MAX <= eChannel)
	{
		FCPIT_ReportDevError(FCPIT_START_ID, FCPIT_E_PARAM_CHANNEL);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_START_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif
         FCPIT_HWA_EnableChannel(eChannel);
         pFcpitHandle->tChannelStatus[(uint8_t)eChannel].bChannelStarted = true;
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Fcpit stop
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_Stop(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel)
{
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if (FCPIT_CHANNEL_MAX <= eChannel)
	{
		FCPIT_ReportDevError(FCPIT_STOP_ID, FCPIT_E_PARAM_CHANNEL);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_STOP_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif
		FCPIT_HWA_DisableChannel(eChannel);
		pFcpitHandle->tChannelStatus[(uint8_t)eChannel].bChannelStarted = false;
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Immediately update Fcpit channel value
* @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 */
void FCPIT_ImmediateUpdateChannelValue(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue)
{
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if (FCPIT_CHANNEL_MAX <= eChannel)
	{
		FCPIT_ReportDevError(FCPIT_STOP_ID, FCPIT_E_PARAM_CHANNEL);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_STOP_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif
		FCPIT_HWA_DisableChannel(eChannel);
        FCPIT_HWA_SetChannelValue(eChannel, u32ChannelValue);
        FCPIT_HWA_EnableChannel(eChannel);
    	pFcpitHandle->tChannelStatus[(uint8_t)eChannel].u32TimerValue = u32ChannelValue;
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Update Fcpit channel value
* @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 */
void FCPIT_UpdateChannelValue(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue)
{
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	if (FCPIT_CHANNEL_MAX <= eChannel)
	{
		FCPIT_ReportDevError(FCPIT_STOP_ID, FCPIT_E_PARAM_CHANNEL);
	}
	else if((uint32_t)0U == FCPIT_HWA_ReadModuleEnable())
	{
		FCPIT_ReportDevError(FCPIT_STOP_ID, FCPIT_STATUS_FUNCTION_ERROR);
	}
	else
	{
#endif
        FCPIT_HWA_SetChannelValue(eChannel, u32ChannelValue);
        pFcpitHandle->tChannelStatus[(uint8_t)eChannel].u32TimerValue = u32ChannelValue;
#if FCPIT_DEV_ERROR_REPORT == STD_ON
	}
#endif
}



/**
 * @brief fcpit interrupt function.
* @param pFcpitHandle Fcpit processing handle
 */
void FCPITn_IRQHandler(FCPIT_HandleType *pFcpitHandle)
{
    uint32_t u32TifValue = FCPIT_HWA_ReadEnableInterruptFlag() & FCPIT_HWA_ReadInterruptFlag();

    if (u32TifValue & FCPIT_MSR_TIF0_MASK)
    {
    	if(pFcpitHandle->tChannelStatus[0].pChannelCallback != NULL)
    	{
    		pFcpitHandle->tChannelStatus[0].pChannelCallback(pFcpitHandle,0U);
    	}
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)FCPIT_MSR_TIF0_MASK);
    }
    if (u32TifValue & FCPIT_MSR_TIF1_MASK)
    {
    	if(pFcpitHandle->tChannelStatus[1].pChannelCallback != NULL)
		{
			pFcpitHandle->tChannelStatus[1].pChannelCallback(pFcpitHandle,1U);
		}
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)FCPIT_MSR_TIF1_MASK);
    }
    if (u32TifValue & FCPIT_MSR_TIF2_MASK)
    {
    	if(pFcpitHandle->tChannelStatus[2].pChannelCallback != NULL)
		{
			pFcpitHandle->tChannelStatus[2].pChannelCallback(pFcpitHandle,2U);
		}
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)FCPIT_MSR_TIF2_MASK);
    }
    if (u32TifValue & FCPIT_MSR_TIF3_MASK)
    {
    	if(pFcpitHandle->tChannelStatus[3].pChannelCallback != NULL)
		{
			pFcpitHandle->tChannelStatus[3].pChannelCallback(pFcpitHandle,3U);
		}
        FCPIT_HWA_ClearChannelsInterruptFlag((uint32_t)FCPIT_MSR_TIF3_MASK);
    }

}

#endif


