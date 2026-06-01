/**
 * @file module_driver_ism.c
 * @author Flagchip
 * @brief ISM driver source code
 * @version 2.0.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    QXW0076   N/A          First version
*********************************************************************************/

#include <module_driver_ism.h>

#if ISM_INSTANCE_COUNT > 0U

#ifndef ISM_DEV_ERROR_REPORT
#define ISM_DEV_ERROR_REPORT	STD_OFF
#endif

#if ISM_DEV_ERROR_REPORT == STD_ON
#define ISM_ReportDevError(func, error) ReportDevError(ISM_MODULE_ID, func, error)
#endif

/* ################################################################################## */
/* ####################################### Macro #################################### */

/* ################################################################################## */
/* ################################### Type define ################################## */

/* ################################################################################## */
/* ################################ Local Variables ################################# */
static ISM_Type *const s_apIsmBase[ISM_INSTANCE_COUNT] = ISM_BASE_PTRS;

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */
/* ################################################################################## */
/* ################################ Local Functions  ################################ */

/* ################################################################################## */
/* ################################ Global Functions ################################ */

/**
 * @brief Init the ISM.
 *
 * @param pIsmHandle Ism processing handle.
 * @param pInitConfig ISMInstance initial configuration.
 */
void ISM_CommonInit(ISM_HandleType *pIsmHandle,const ISM_InitCfgType *pInitConfig)
{
	ISM_Type *pIsm = ISM;
#if ISM_DEV_ERROR_REPORT == STD_ON

	if ((ISM_HWA_PARAM_ECMC(pIsm) != ECM_INSTANCE_COUNT)||(ISM_HWA_PARAM_FPC(pIsm) != FPC_INSTANCE_COUNT)||(ISM_HWA_PARAM_LAM(pIsm) != LAM_INSTANCE_COUNT))
	{
		ISM_ReportDevError(ISM_COMMON_INIT_ID, ISM_E_PARAM_INVALID);
	}
	else if (NULL == pInitConfig)
	{
		ISM_ReportDevError(ISM_COMMON_INIT_ID, ISM_E_PARAM_POINTER);
	}
	else
	{
#endif
		ISM_HWA_Enable(pIsm, pInitConfig->bIsmEnable);
		ISM_HWA_InterruptEnable(pIsm, pInitConfig->bIntEnable);


		/*Send info to global handler*/
		pIsmHandle->bEnable = pInitConfig->bIntEnable;
		pIsmHandle->bIntEnable = pInitConfig->bIntEnable;
		pIsmHandle->pEventIsrCalllback = pInitConfig->pEventIsrCalllback;
		pIsmHandle->pEcmEventIsrCalllback = pInitConfig->pEcmEventIsrCalllback;

#if ISM_DEV_ERROR_REPORT == STD_ON
	}
#endif
}


/**
 * @brief Config the FPC channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8FpcIndex FPC index.
 * @param pConfig FPC configuration.
 */
void ISM_FpcConfig(ISM_HandleType *pIsmHandle,uint8_t u8FpcIndex, const ISM_FpcCfgType *pConfig)
{
#if ISM_DEV_ERROR_REPORT == STD_ON
	if(u8FpcIndex > FPC_INSTANCE_COUNT)
	{
		ISM_ReportDevError(ISM_FPC_CONFIG_ID, ISM_E_PARAM_CHANNEL);
	}
	else if (NULL == pConfig)
	{
		ISM_ReportDevError(ISM_FPC_CONFIG_ID, ISM_E_PARAM_POINTER);
	}
	else
	{
#endif
		uint32_t u32TempValue = 0;
		FPC_Type *pFpc;
		pFpc = ISM_HWA_GetFpc(ISM, u8FpcIndex);
		ISM_HWA_SetFpcCtrlIen(pFpc, pConfig->bGlitchIntEnable);
		u32TempValue |= ISM_FPC_CONFIG_FED(pConfig->eFallingDelayNode);
		u32TempValue |= ISM_FPC_CONFIG_FEG(pConfig->eFallingDetectMode);
		u32TempValue |= ISM_FPC_CONFIG_RED(pConfig->eRisingDelayNode);
		u32TempValue |= ISM_FPC_CONFIG_REG(pConfig->eRisingDetectMode);
		u32TempValue |= ISM_FPC_CONFIG_CMP(pConfig->u32ThresholdValue);
		ISM_HWA_SetFpcConfig(pFpc, u32TempValue);
		/*Send info to global handler*/
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].bGlitchIntEnable = pConfig->bGlitchIntEnable;
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].eFallingDelayNode = pConfig->eFallingDelayNode;
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].eFallingDetectMode = pConfig->eFallingDetectMode;
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].eRisingDelayNode = pConfig->eRisingDelayNode;
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].eRisingDetectMode = pConfig->eRisingDetectMode;
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].u32ThresholdValue = pConfig->u32ThresholdValue;
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].pFpcChannelCalllback = pConfig->pFpcChannelCalllback;

#if ISM_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Enable FPC channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8FpcIndex FPC index.
 * @param bEnable Enable value.
 */
void ISM_FpcEnable(ISM_HandleType *pIsmHandle,uint8_t u8FpcIndex, bool bEnable)
{
#if ISM_DEV_ERROR_REPORT == STD_ON
	if(u8FpcIndex > FPC_INSTANCE_COUNT)
	{
		ISM_ReportDevError(ISM_FPC_ENABLE_ID, ISM_E_PARAM_CHANNEL);
	}
	else if (NULL == pIsmHandle)
	{
		ISM_ReportDevError(ISM_FPC_ENABLE_ID, ISM_E_PARAM_POINTER);
	}
	else
	{
#endif
		FPC_Type *pFpc;
		pFpc = ISM_HWA_GetFpc(ISM, u8FpcIndex);
		ISM_HWA_SetFpcCtrlEn(pFpc, bEnable);
		/*Send info to global handler*/
		pIsmHandle->tIsmFpcChannelStatus[u8FpcIndex].bFpcChannelEn = bEnable;
#if ISM_DEV_ERROR_REPORT == STD_ON
	}
#endif
}


/**
 * @brief Config the LAM channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8LamIndex LAM index.
 * @param pConfig LAM configuration.
 */
void ISM_LamConfig(ISM_HandleType *pIsmHandle,uint8_t u8LamIndex, const ISM_LamCfgType *pConfig)
{

#if ISM_DEV_ERROR_REPORT == STD_ON
	if(u8LamIndex > LAM_INSTANCE_COUNT)
	{
		ISM_ReportDevError(ISM_LAM_CONFIG_ID, ISM_E_PARAM_CHANNEL);
	}
	else if (NULL == pConfig)
	{
		ISM_ReportDevError(ISM_LAM_CONFIG_ID, ISM_E_PARAM_POINTER);
	}
	else
	{
#endif
		uint32_t u32TempValue = 0;
		LAM_Type *pLam;
		pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

		ISM_HWA_SetLamCtrIen(pLam, pConfig->bOvflIntEnable);
		ISM_HWA_SetLamCounter(pLam, pConfig->u32EvtCntThreshold);
		u32TempValue |= ISM_LAM_CONFIG_RCS(pConfig->u8RcsSel);
		u32TempValue |= ISM_LAM_CONFIG_MCS(pConfig->u8MonSel);
		u32TempValue |= ISM_LAM_CONFIG_IVW(pConfig->eInvWin);
		u32TempValue |= ISM_LAM_CONFIG_EDS(pConfig->eWinEdgSel);
		u32TempValue |= ISM_LAM_CONFIG_EWS(pConfig->eEvtWinSel);
		u32TempValue |= ISM_LAM_CONFIG_RMS(pConfig->eRunMode);
		u32TempValue |= ISM_LAM_CONFIG_MOS(pConfig->eMonSrcSel);
		u32TempValue |= ISM_LAM_CONFIG_IVM(pConfig->eInvMon);
		u32TempValue |= ISM_LAM_CONFIG_IVR(pConfig->eInvRef);
		ISM_HWA_SetLamConfig(pLam, u32TempValue);
		/*Send info to global handler*/
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].bOvflIntEnable = pConfig->bOvflIntEnable;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].eEvtWinSel = pConfig->eEvtWinSel;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].eInvMon = pConfig->eInvMon;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].eInvRef =pConfig->eInvRef;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].eInvWin =pConfig->eInvWin;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].eMonSrcSel =pConfig->eMonSrcSel;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].eRunMode =pConfig->eRunMode ;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].eWinEdgSel =pConfig->eWinEdgSel;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].u32EvtCntThreshold =pConfig->u32EvtCntThreshold;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].u8MonSel =pConfig->u8MonSel;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].u8RcsSel =pConfig->u8RcsSel;
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].pLamChannelOverCalllback = pConfig->pLamChannelOverCalllback;
#if ISM_DEV_ERROR_REPORT == STD_ON
	}
#endif
}


/**
 * @brief Enable LAM Channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8LamIndex LAM index.
 * @param bEnable Enable value.
 */
void ISM_LamEnable(ISM_HandleType *pIsmHandle,uint8_t u8LamIndex, bool bEnable)
{

#if ISM_DEV_ERROR_REPORT == STD_ON
	if(u8LamIndex > LAM_INSTANCE_COUNT)
	{
		ISM_ReportDevError(ISM_LAM_ENABLE_ID, ISM_E_PARAM_CHANNEL);
	}
	else if (NULL == pIsmHandle)
	{
		ISM_ReportDevError(ISM_LAM_ENABLE_ID, ISM_E_PARAM_POINTER);
	}
	else
	{
#endif
		LAM_Type *pLam;


		pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

		ISM_HWA_SetLamCtrEn(pLam, bEnable);
		/*Send info to global handler*/
		pIsmHandle->tIsmLamChannelStatus[u8LamIndex].bLamChannelEn = bEnable;
#if ISM_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Enable LAM system event
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8LamIndex Lam channel index.
 * @param u8EcmIndex Ecm channel index.
 * @param u8EventCount Threshold of the ECM channel counter value.
 */
void ISM_EcmEventConfig(ISM_HandleType *pIsmHandle,uint8_t u8LamIndex, uint8_t u8EcmIndex, uint8_t u8EventCount)
{

#if ISM_DEV_ERROR_REPORT == STD_ON
	if(u8LamIndex > LAM_INSTANCE_COUNT)
	{
		ISM_ReportDevError(ISM_ECM_CONFIG_ID, ISM_E_PARAM_CHANNEL);
	}

	else if (u8EcmIndex == ECM_INSTANCE_COUNT)
	{
		ISM_ReportDevError(ISM_ECM_CONFIG_ID, ISM_E_PARAM_COUNT);
	}
	else
	{
#endif
		ISM_Type *pIsm = ISM;
		if (u8EcmIndex == 0U)
		{
			ISM_HWA_SetEcm0EcCtrl(pIsm, u8EventCount, u8LamIndex);
		}
		else if (u8EcmIndex == 1U)
		{
			ISM_HWA_SetEcm1EcCtrl(pIsm, u8EventCount, u8LamIndex);
		}
		else if (u8EcmIndex == 2U)
		{
			ISM_HWA_SetEcm2EcCtrl(pIsm, u8EventCount, u8LamIndex);
		}
		else if (u8EcmIndex == 3U)
		{
			ISM_HWA_SetEcm3EcCtrl(pIsm, u8EventCount, u8LamIndex);
		}
		else
		{

		}
		/*Send info to global handler*/
		pIsmHandle->tEcmEventStatus[u8EcmIndex].u32Value = u8EventCount;
		pIsmHandle->tEcmEventStatus[u8EcmIndex].u32LamChannelRouter = u8LamIndex;

#if ISM_DEV_ERROR_REPORT == STD_ON
	}
#endif
}


/**
 * @brief Gets the channels where ECM events happened.
 * 
 * @return uint8_t A bitmap indicating the channels where ECM events occurred.
 */
uint8_t ISM_GetEcmEventHappenedChannels(void)
{
    ISM_Type *pIsm = ISM; 
    return (uint8_t)ISM_HWA_GetEcs(pIsm); 
}


/**
 * @brief Gets the channels where LAM events have occurred.
 * 
 * 
 * @return uint16_t A bit field where each bit represents a channel, set if an event has occurred on that channel.
 */
uint16_t ISM_GetLamEventHappenedChannels(void)
{
    ISM_Type *pIsm = ISM;

    return ISM_HWA_GetEs(pIsm);
}

/**
 * @brief Clears the bits for ECM event channels.
 * 
 * @param u8Channels The bit field representing the channels to clear, with each bit corresponding to a channel.
 */
void ISM_ClearEcmEventHappenedChannels(uint8_t u8Channels)
{
    ISM_Type *pIsm = ISM;
    ISM_HWA_ClearEcs(pIsm, (uint32_t)u8Channels);
}

/**
 * @brief Clears the bits for LAM event channels.
 * 
 * @param u16Channels The bit field representing the channels to clear, with each bit corresponding to a channel.
 */
void ISM_ClearLamEventHappenedChannels(uint16_t u16Channels)
{
    ISM_Type *pIsm = ISM;
    ISM_HWA_ClearEs(pIsm, (uint32_t)u16Channels);
}

/**
 * @brief Enables or disables the generation of ECM system events.
 * 
 * @param u32Channels The bit field representing the channels to operate on, with each bit corresponding to a channel.
 * @param bEnable Indicates whether to enable (true) or disable (false) event generation.
 */
void ISM_EnableEcmSystemEvent(uint32_t u32Channels, bool bEnable)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_EnableEcmSystemEvent(pIsm, u32Channels, bEnable);
}

/**
 * @brief Enables or disables the generation of LAM system events.
 *  
 * @param u32Channels The bit field representing the channels to operate on, with each bit corresponding to a channel.
 * @param bEnable Indicates whether to enable (true) or disable (false) event generation.
 */
void ISM_EnableLamSystemEvent(uint32_t u32Channels, bool bEnable)
{
    ISM_Type *pIsm = ISM;

    ISM_HWA_EnableLamSystemEvent(pIsm, u32Channels, bEnable);
}

/**
 * @brief Clears the LAM status counter.
 * 
 * @param u8LamIndex The index of the LAM module to be operated on.
 */
void ISM_ClearLamStatusCounter(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    ISM_HWA_ClearLamStatusCounter(pLam);
}

/**
 * @brief Gets the value of the LAM status counter.
 * 
 * @param u8LamIndex The index of the LAM module to read.
 * @return uint32_t The current value of the LAM status counter.
 */
uint32_t  ISM_GetLamStatusCounter(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    return ISM_HWA_GetLamStatusCounter(pLam);
}

/**
 * @brief Clears the LAM status counter overflow flag.
 * 
 * @param u8LamIndex The index of the LAM module to be operated on.
 */
void ISM_ClearLamStatusOvfl(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    ISM_HWA_ClearLamStatusOvfl(pLam);
}

/**
 * @brief Checks if the LAM status counter has overflowed.
 * 
 * @param u8LamIndex The index of the LAM module to check.
 * @return bool True if the status counter has overflowed, false otherwise.
 */
bool ISM_GetLamStatusOvfl(uint8_t u8LamIndex)
{
    LAM_Type *pLam;

    pLam = ISM_HWA_GetLam(ISM, u8LamIndex);

    return ISM_HWA_GetLamStatusOvfl(pLam);
}

/**
 * @param pIsmHandle Ism processing handle.
 * @brief ISM Interrupt Process Function.
 */
void ISMn_IRQHandler(ISM_HandleType *pIsmHandle)
{
    uint8_t u8i =0;
    FPC_Type *pFpc;
    LAM_Type *pLam;
    uint8_t u8EcmFlags;
    uint16_t u16LamFlags;
    ISM_Type *pIsm = s_apIsmBase[ISM_INSTANCE_0];

    u8EcmFlags = ISM_HWA_GetEcs(pIsm)&ISM_HWA_GetEnabledEcmSystemEvent(pIsm);
    u16LamFlags = ISM_HWA_GetEs(pIsm)&ISM_HWA_GetEnabledLamSystemEvent(pIsm);



    /*ECM event callback*/
    for (u8i = 0; u8i < ECM_INSTANCE_COUNT; u8i++)
	{
		if(((0x1<<u8i)&u8EcmFlags)!=0U)
		{
			if( pIsmHandle->pEcmEventIsrCalllback != NULL)
			{
				pIsmHandle->pEcmEventIsrCalllback(pIsmHandle,u8EcmFlags);
			}
		}
	}

    /*Event callback*/
    for (u8i = 0; u8i < LAM_INSTANCE_COUNT; u8i++)
    {
    	if(((0x1<<u8i)&u16LamFlags)!=0U)
    		{
    			if (pIsmHandle->pEventIsrCalllback !=NULL)
    			{
    				pIsmHandle->pEventIsrCalllback(pIsmHandle,u16LamFlags);
    			}
    		}

    }

    /*FPC callback*/
    for (u8i = 0; u8i < FPC_INSTANCE_COUNT; u8i++)
    {
        pFpc = ISM_HWA_GetFpc(pIsm, u8i);
        if (ISM_HWA_GetFpcCtrlIen(pFpc))
        {
            uint32_t u32Status = 0U;
            if (ISM_HWA_GetFpcRgd(pFpc))
            {
                u32Status |= (uint32_t)FPC_RISING_GLITCH_DETECTED;
            }
            if (ISM_HWA_GetFpcFgd(pFpc))
            {
                u32Status |= (uint32_t)FPC_FALLING_GLITCH_DETECTED;
            }
            if( pIsmHandle->tIsmFpcChannelStatus[u8i].pFpcChannelCalllback != NULL)
            {
            	pIsmHandle->tIsmFpcChannelStatus[u8i].pFpcChannelCalllback(pIsmHandle,u8i);
            }
            if ((u32Status & (uint32_t)FPC_RISING_GLITCH_DETECTED) == (uint32_t)FPC_RISING_GLITCH_DETECTED)
            {
                ISM_HWA_ClearFpcRgd(pFpc);
            }
            if ((u32Status & (uint32_t)FPC_FALLING_GLITCH_DETECTED) == (uint32_t)FPC_FALLING_GLITCH_DETECTED)
            {
                ISM_HWA_ClearFpcFgd(pFpc);
            }
        }
    }

    /*LAM overflow callback*/
    for (u8i = 0; u8i < LAM_INSTANCE_COUNT; u8i++)
    {
        pLam = ISM_HWA_GetLam(pIsm, u8i);
        if (ISM_HWA_GetLamCtrIen(pLam))
        {
            if (ISM_HWA_GetLamStatusOvfl(pLam))
            {
            	if( pIsmHandle->tIsmLamChannelStatus[u8i].pLamChannelOverCalllback != NULL)
                {
            		pIsmHandle->tIsmLamChannelStatus[u8i].pLamChannelOverCalllback(pIsmHandle,u8i);
                }
                ISM_HWA_ClearLamStatusOvfl(pLam);
            }
        }
    }

    ISM_HWA_ClearEcs(pIsm, u8EcmFlags);
    ISM_HWA_ClearEs(pIsm, u16LamFlags);

}

#endif

