/**
 * @file module_driver_tstmp.c
 * @author Flagchip074
 * @brief TSTMP driver source code
 * @version 2.0.0
 * @date 2024-11-08
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
#include "module_driver_tstmp.h"

#if TSTMP_INSTANCE_COUNT > 0U

#ifndef TSTMP_DEV_ERROR_REPORT
#define TSTMP_DEV_ERROR_REPORT	STD_OFF
#endif

#if TSTMP_DEV_ERROR_REPORT == STD_ON
#define TSTMP_ReportDevError(func, error) ReportDevError(TSTMP_MODULE_ID, func, error)
#endif

/** @brief TSTMP modulate interrupt enable shift macro */
#define TSTMP_MOD_INTEN_MODn_INTEN_SHIFT(n)     (1U * (uint32_t)(n))
/** @brief TSTMP modulate interrupt enable mask macro */
#define TSTMP_MOD_INTEN_MODn_INTEN_MASK(n)      ((uint32_t)((uint32_t)0x1U << TSTMP_MOD_INTEN_MODn_INTEN_SHIFT(n)))
/** @brief TSTMP modulate interrupt enable macro */
#define TSTMP_MOD_INTEN_MODn_INTEN(n, x)        (((uint32_t)(x) << TSTMP_MOD_INTEN_MODn_INTEN_SHIFT(n)) & TSTMP_MOD_INTEN_MODn_INTEN_MASK(n))


/** @brief Tstmp instance list */
static TSTMP_Type *s_pTstmpPtrs[TSTMP_INSTANCE_COUNT] = TSTMP_BASE_PTRS;



/**
 * @brief Initialize TSTMP instance
 *
  * @param pTstmpHandle TSTMP processing handle
 * @param pInitStruct TSTMP initialization structure
 * @note TSTMP will auto start the modulate when write MODn_SETVAL register
 *       TSTMP1 clock source is core clock
 */
void TSTMP_Init(TSTMP_HandleType *pTstmpHandle,const TSTMP_InitType *const pInitStruct)
{

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_INIT_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
		/*Send info to global handler*/

		pTstmpHandle->tStatus.u32ModulateValue[0] = pInitStruct->u32Modulate0Value;
		pTstmpHandle->tStatus.u32ModulateValue[1] = pInitStruct->u32Modulate1Value;
		pTstmpHandle->tStatus.u32ModulateValue[2] = pInitStruct->u32Modulate2Value;
		pTstmpHandle->tStatus.u32ModulateValue[3] = pInitStruct->u32Modulate3Value;

		/* clear MOD match flag */
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn0);
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn1);
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn2);
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn3);

		/* set MOD0 match value */
		TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MODChn0, pInitStruct->u32Modulate0Value);
		/* set MOD1 match value */
		TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MODChn1, pInitStruct->u32Modulate1Value);
		/* set MOD2 match value */
		TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MODChn2, pInitStruct->u32Modulate2Value);
		/* set MOD3 match value */
		TSTMP_HWA_SetModMatchValue(pTstmp, TSTMP_MODChn3, pInitStruct->u32Modulate3Value);
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief De-initialize TSTMP instance
 * @param pTstmpHandle TSTMP processing handle
 */
void TSTMP_Deinit(TSTMP_HandleType *pTstmpHandle)
{
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_DEINIT_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
		uint8_t u8Index;
		for (u8Index = 0U; u8Index < MAX_MOD_NUMBER; u8Index++)
		{

			/* Disable TSTMP MOD(n) match interrupt */
			TSTMP_HWA_DisableModMatchInterrupt(pTstmp, (TSTMP_ModChannelType)u8Index);
			/* Clear TSTMP MOD(n) match value */
			TSTMP_HWA_SetModMatchValue(pTstmp, (TSTMP_ModChannelType)u8Index, (uint32_t)0U);
			/* clear MOD(n) match flag */
			TSTMP_HWA_ClearModMatchFlag(pTstmp,(TSTMP_ModChannelType)u8Index);
#if (TSTMP_SUPPORT_MODULATE_SUPPOT == STD_ON)
			TSTMP_HWA_SetModCounterMode(pTstmp,(TSTMP_ModChannelType)u8Index,TSTMP_MODE_ALWAYS_RUNNING);
			TSTMP_HWA_DisableModCounter(pTstmp,(TSTMP_ModChannelType)u8Index);
#endif
		}

		/*Clear Global configuration*/
		pTstmpHandle->eInstance = (TSTMP_InstanceType)0U;

		pTstmpHandle->tStatus.u32ModulateValue[0] = 0u;
		pTstmpHandle->tStatus.u32ModulateValue[1] = 0u;
		pTstmpHandle->tStatus.u32ModulateValue[2] = 0u;
		pTstmpHandle->tStatus.u32ModulateValue[3] = 0u;

#if (TSTMP_SUPPORT_MODULATE_SUPPOT == STD_ON)
		pTstmpHandle->tStatus.gModRunningMode[0] = TSTMP_MODE_ALWAYS_RUNNING;
		pTstmpHandle->tStatus.gModRunningMode[1] = TSTMP_MODE_ALWAYS_RUNNING;
		pTstmpHandle->tStatus.gModRunningMode[2] = TSTMP_MODE_ALWAYS_RUNNING;
		pTstmpHandle->tStatus.gModRunningMode[3] = TSTMP_MODE_ALWAYS_RUNNING;
#endif

		pTstmpHandle->tStatus.bModulateIntEn[0] = false;
		pTstmpHandle->tStatus.bModulateIntEn[1] = false;
		pTstmpHandle->tStatus.bModulateIntEn[2] = false;
		pTstmpHandle->tStatus.bModulateIntEn[3] = false;

		pTstmpHandle->tStatus.pChannelCallback[0] = NULL;
		pTstmpHandle->tStatus.pChannelCallback[1] = NULL;
		pTstmpHandle->tStatus.pChannelCallback[2] = NULL;
		pTstmpHandle->tStatus.pChannelCallback[3] = NULL;


#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif

}

#if (TSTMP_SUPPORT_MODULATE_SUPPOT == STD_ON)
/**
 * @brief Set the Counting mode of modulate timer counter0,1,2,3
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 * @param eCounterMode Counting mode of counter0

 */
void TSTMP_SetCounterMode(TSTMP_HandleType *pTstmpHandle, const TSTMP_ModChannelType eMod,const TSTMP_ModeCounterRunningMode eCounterMode)
{
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_SET_COUNTER_MODE_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else if(eCounterMode >TSTMP_MODE_PERIOD_RUNNING )
	{
		TSTMP_ReportDevError(TSTMP_SET_COUNTER_MODE_ID, TSTMP_E_PARAM_INVALID);
	}
	else
	{
#endif
    	TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
        TSTMP_HWA_SetModCounterMode(pTstmp,eMod,eCounterMode);
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif

}

/**
 * @brief Start counter MOD(n) counting
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration

 */
void TSTMP_StartCounter(TSTMP_HandleType *pTstmpHandle,const TSTMP_ModChannelType eMod)
{

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_START_COUNTER_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
		TSTMP_HWA_EnableModCounter(pTstmp,eMod);
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Stop counter MOD(n) counting
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 *
 */
void TSTMP_StopCounter(TSTMP_HandleType *pTstmpHandle,const TSTMP_ModChannelType eMod)
{

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_STOP_COUNTER_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
		TSTMP_HWA_DisableModCounter(pTstmp,eMod);
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif
}
#endif


/**
 * @brief Initialize TSTMP interrupt functionality
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param pIntStruct TSTMP interrupt structure
 */
void TSTMP_InitInterrupt(TSTMP_HandleType *pTstmpHandle, const TSTMP_IntType *const pIntStruct)
{
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_INIT_INTERRUPT_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		uint8_t u8Index;
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];

		for (u8Index = 0U; u8Index < MAX_MOD_NUMBER; u8Index++)
		{
			if (true == pIntStruct->bModulateIntEn[u8Index])
			{
				/* Enable TSTMP MOD(n) match interrupt */
				TSTMP_HWA_EnableModMatchInterrupt(pTstmp, (TSTMP_ModChannelType)u8Index);
				pTstmpHandle->tStatus.bModulateIntEn[u8Index]	=	pIntStruct->bModulateIntEn[u8Index];
				pTstmpHandle->tStatus.pChannelCallback[u8Index] = pIntStruct->pChannelCallback[u8Index];
			}
			else
			{
				/* Disable TSTMP MOD(n) match interrupt */
				TSTMP_HWA_DisableModMatchInterrupt(pTstmp, (TSTMP_ModChannelType)u8Index);
			}
		}


#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Enable TSTMP interrupt function
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 */
void TSTMP_EnableInterrupt(TSTMP_HandleType *pTstmpHandle, const TSTMP_ModChannelType eMod)
{
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_EN_INTERRUPT_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
        /* Enable TSTMP MOD(n) match interrupt */
        TSTMP_HWA_EnableModMatchInterrupt(pTstmp, eMod);
        pTstmpHandle->tStatus.bModulateIntEn[(uint8_t)eMod]	= true;

#if TSTMP_DEV_ERROR_REPORT == STD_ON

	}
#endif
}

/**
 * @brief Disable TSTMP interrupt function
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 */
void TSTMP_DisableInterrupt(TSTMP_HandleType *pTstmpHandle, const TSTMP_ModChannelType eMod)
{
#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_DIS_INTERRUPT_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else
	{
#endif
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
        /* Disable TSTMP MOD(n) match interrupt */
        TSTMP_HWA_DisableModMatchInterrupt(pTstmp, eMod);
        pTstmpHandle->tStatus.bModulateIntEn[(uint8_t)eMod]	= false;

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Get TSTMP count value
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param u64TstmpValue the timestamp value
 */
void TSTMP_GetTstmpValue(TSTMP_HandleType *pTstmpHandle, uint64_t *const u64TstmpValue)
{

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_GET_TSTMP_VALUE_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else if(NULL == u64TstmpValue)
	{
		TSTMP_ReportDevError(TSTMP_GET_TSTMP_VALUE_ID, TSTMP_E_PARAM_INVALID);
	}
	else
	{
#endif

		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
        *u64TstmpValue = TSTMP_HWA_ReadTstmpValue(pTstmp);

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Update Modulate configuration
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param pUpdateStruct TSTMP update structure pointer
 */
void TSTMP_UpdateMod(TSTMP_HandleType *pTstmpHandle,const TSTMP_UpdateType *const pUpdateStruct)
{

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	if ((uint32_t)pTstmpHandle->eInstance >= TSTMP_INSTANCE_MAX)
	{
		TSTMP_ReportDevError(TSTMP_UPDATE_MOD_ID, TSTMP_E_PARAM_INSTANCE);
	}
	else if(NULL == pUpdateStruct)
	{
		TSTMP_ReportDevError(TSTMP_UPDATE_MOD_ID, TSTMP_E_PARAM_INVALID);
	}
	else
	{
#endif
		TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
        /* Clear MOD(n) interrupt flag */

		TSTMP_HWA_ClearModMatchFlag(pTstmp,pUpdateStruct->eMod);

        if ((pUpdateStruct->bIntEn) == true)
        {
        	 /* Enable TSTMP MOD(n) match interrupt */
			TSTMP_HWA_EnableModMatchInterrupt(pTstmp, pUpdateStruct->eMod);
			pTstmpHandle->tStatus.bModulateIntEn[(uint8_t)pUpdateStruct->eMod]	= true;

        }else
        {
			/* Disable TSTMP MOD(n) match interrupt */
			TSTMP_HWA_DisableModMatchInterrupt(pTstmp, pUpdateStruct->eMod);
			pTstmpHandle->tStatus.bModulateIntEn[(uint8_t)pUpdateStruct->eMod]	= false;
        }

        /* set MOD(n) match value */
        TSTMP_HWA_SetModMatchValue(pTstmp, pUpdateStruct->eMod, pUpdateStruct->u32ModValue);
        pTstmpHandle->tStatus.u32ModulateValue[(uint8_t)pUpdateStruct->eMod] = pUpdateStruct->u32ModValue;

        if(pUpdateStruct->pChannelCallback != NULL)
        {
        	pTstmpHandle->tStatus.pChannelCallback[(uint8_t)pUpdateStruct->eMod] = pUpdateStruct->pChannelCallback;
        }

#if TSTMP_DEV_ERROR_REPORT == STD_ON
	}
#endif
}


#if (TSTMP_INSTANCE_COUNT == 1u || TSTMP_INSTANCE_COUNT == 2u)

/**
 * @brief TSTMP interrupt process function
 *
 * @param pTstmpHandle TSTMP processing handle
 */
void TSTMPn_IRQHandler(TSTMP_HandleType *pTstmpHandle)
{
	TSTMP_Type *pTstmp = s_pTstmpPtrs[pTstmpHandle->eInstance];
	uint32_t u32TstmpStatus = TSTMP_HWA_ReadModMatchFlag(pTstmp);
	if (u32TstmpStatus & TSTMP_MOD_STATUS_MOD0_MATCH_MASK)
	{

		pTstmpHandle->tStatus.pChannelCallback[0](pTstmpHandle,(uint32_t)TSTMP_MODChn0);

		/* Clear MOD0 interrupt flag */
		TSTMP_HWA_DisableModMatchInterrupt(pTstmp,TSTMP_MODChn0);
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn0);
		TSTMP_HWA_EnableModMatchInterrupt(pTstmp,TSTMP_MODChn0);
	}
	if (u32TstmpStatus & TSTMP_MOD_STATUS_MOD1_MATCH_MASK)
	{
		pTstmpHandle->tStatus.pChannelCallback[1](pTstmpHandle,(uint32_t)TSTMP_MODChn1);
		/* Clear MOD1 interrupt flag */
		TSTMP_HWA_DisableModMatchInterrupt(pTstmp,TSTMP_MODChn1);
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn1);
		TSTMP_HWA_EnableModMatchInterrupt(pTstmp,TSTMP_MODChn1);
	}
	if (u32TstmpStatus & TSTMP_MOD_STATUS_MOD2_MATCH_MASK)
	{
		pTstmpHandle->tStatus.pChannelCallback[2](pTstmpHandle,(uint32_t)TSTMP_MODChn2);
		/* Clear MOD2 interrupt flag */
		TSTMP_HWA_DisableModMatchInterrupt(pTstmp,TSTMP_MODChn2);
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn2);
		TSTMP_HWA_EnableModMatchInterrupt(pTstmp,TSTMP_MODChn2);
	}
	if (u32TstmpStatus & TSTMP_MOD_STATUS_MOD3_MATCH_MASK)
	{
		pTstmpHandle->tStatus.pChannelCallback[3](pTstmpHandle,(uint32_t)TSTMP_MODChn3);
		/* Clear MOD3 interrupt flag */
		TSTMP_HWA_DisableModMatchInterrupt(pTstmp,TSTMP_MODChn3);
		TSTMP_HWA_ClearModMatchFlag(pTstmp,TSTMP_MODChn3);
		TSTMP_HWA_EnableModMatchInterrupt(pTstmp,TSTMP_MODChn3);
	}
}



#endif /* #if (TSTMP_INSTANCE_COUNT == 1u || TSTMP_INSTANCE_COUNT == 2u) */

#endif /* #if TSTMP_INSTANCE_COUNT > 0U */
