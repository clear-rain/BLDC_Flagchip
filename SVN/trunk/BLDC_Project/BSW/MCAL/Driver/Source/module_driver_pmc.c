/* @file module_driver_pmc.c
* @author Flagchip
* @brief PMC driver type definition and API
* @version 2.0.0
* @date 2024-05-15
*
* @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
*
*/
/*********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials          Descriptions
  *   ---------   ----------    ------------     ---------------
  *   2.0.0       2024-05-15    Flagchip055      Update file structures
  *********************************************************************************/

#include "module_driver_pmc.h"

#if PMC_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

#ifndef PMC_DEV_ERROR_REPORT
#define PMC_DEV_ERROR_REPORT	STD_OFF
#endif

#if PMC_DEV_ERROR_REPORT == STD_ON
#define PMC_ReportDevError(func, error) ReportDevError(PMC_MODULE_ID, func, error)
#endif
/**
 * @brief PMC get status flag
 *
 * This function returns the state of a status flag.
 *
 * @param eFlag PMC flag type
 * @return true the flag bit is 1,false the flag bit is 0
 */
bool PMC_GetFlag(PMC_FlagType eFlag)
{
    bool bRetVal = false;
    switch (eFlag)
    {
        case PMC_POR_FLAG:
            bRetVal = PMC_HWA_PorFlag(PMC);
            break;
        case PMC_LVR1P1V_RPM_FLAG:
            bRetVal = PMC_HWA_Lvr1p1vRpmFlag(PMC);
            break;
        case PMC_LVR1P1V_FPM_FLAG:
            bRetVal = PMC_HWA_Lvr1p1vFpmFlag(PMC);
            break;
        case PMC_HVD1P1V_FLAG:
            bRetVal = PMC_HWA_Hvd1p1vFlag(PMC);
            break;
#if PMC_V25_SUPPORT
        case PMC_LVR2P5V_RPM_FLAG:
            bRetVal = PMC_HWA_Lvr2p5vRpmFlag(PMC);
            break;
        case PMC_LVR2P5V_FPM_FLAG:
            bRetVal = PMC_HWA_Lvr2p5vFpmFlag(PMC);
            break;
        case PMC_HVD2P5V_FLAG:
            bRetVal = PMC_HWA_Hvd2p5vFlag(PMC);
            break;
#endif
#if PMC_V3_SUPPORT
        case PMC_LVR3V_RPM_FLAG:
            bRetVal = PMC_HWA_Lvr3vRpmFlag(PMC);
            break;
        case PMC_LVR3V_FPM_FLAG:
            bRetVal = PMC_HWA_Lvr3vFpmFlag(PMC);
            break;
        case PMC_HVD3V_FLAG:
            bRetVal = PMC_HWA_Hvd3vFlag(PMC);
            break;
#endif
#if PMC_V5_SUPPORT
        case PMC_LVR5V_RPM_FLAG:
            bRetVal = PMC_HWA_Lvr5vRpmFlag(PMC);
            break;
        case PMC_LVR5V_FPM_FLAG:
            bRetVal = PMC_HWA_Lvr5vFpmFlag(PMC);
            break;
        case PMC_HVD5V_FLAG:
            bRetVal = PMC_HWA_Hvd5vFlag(PMC);
            break;
#endif
#if PMC_LVD_SUPPORT
        case PMC_LVD5V_FLAG:
            bRetVal = PMC_HWA_Lvd5vFlag(PMC);
            break;
#endif
        default:
            /* Invalid parameter: return */
            break;
    }
    return bRetVal;
}

/**
 * @brief PMC clears an individual status flag.
 *
 * This function clears an individual status flag (see pmc_status_flag_t for list of status bits).
 *
 * @param eFlag PMC flag type
 * @return 0 valid parameter, 1 invalid parameter
 */
PMC_RetType PMC_ClearFlag(PMC_FlagType eFlag)
{
    PMC_RetType eRet = PMC_STATUS_SUCCESS;
    switch (eFlag)
    {
        case PMC_POR_FLAG:
            PMC_HWA_ClearPorFlag(PMC);
            break;
        case PMC_LVR1P1V_RPM_FLAG:
            PMC_HWA_ClearLvr1p1vRpmFlag(PMC);
            break;
        case PMC_LVR1P1V_FPM_FLAG:
            PMC_HWA_ClearLvr1p1vFpmFlag(PMC);
            break;
        case PMC_HVD1P1V_FLAG:
            PMC_HWA_ClearHvd1p1vFlag(PMC);
            break;
#if PMC_V25_SUPPORT
        case PMC_HVD2P5V_FLAG:
            PMC_HWA_ClearHvd2p5vFlag(PMC);
            break;
        case PMC_LVR2P5V_RPM_FLAG:
            PMC_HWA_ClearLvr2p5vRpmFlag(PMC);
            break;
        case PMC_LVR2P5V_FPM_FLAG:
            PMC_HWA_ClearLvr2p5vFpmFlag(PMC);
            break;
#endif
#if PMC_V3_SUPPORT
        case PMC_LVR3V_RPM_FLAG:
            PMC_HWA_ClearLvr3vRpmFlag(PMC);
            break;
        case PMC_LVR3V_FPM_FLAG:
            PMC_HWA_ClearLvr3vFpmFlag(PMC);
            break;
        case PMC_HVD3V_FLAG:
            PMC_HWA_ClearHvd3vFlag(PMC);
            break;
#endif
#if PMC_V5_SUPPORT
        case PMC_LVR5V_RPM_FLAG:
            PMC_HWA_ClearLvr5vRpmFlag(PMC);
            break;
        case PMC_LVR5V_FPM_FLAG:
            PMC_HWA_ClearLvr5vFpmFlag(PMC);
            break;
        case PMC_HVD5V_FLAG:
            PMC_HWA_ClearHvd5vFlag(PMC);
            break;
#endif
#if PMC_LVD_SUPPORT
        case PMC_LVD5V_FLAG:
            PMC_HWA_ClearLvd5vFlag(PMC);
            break;
#endif
        default:
            eRet = PMC_STATUS_PARAM_INVALID;
            /* Invalid parameter: return */
            break;
    }
    return (eRet);
}

/**
 * @brief PMC get status
 *
 * @param eStatus the status type
 * @return true the status bit return 1
 * @return false the status bit return 0
 */
bool PMC_GetStatus(PMC_StatusType eStatus)
{
    bool bRetVal = false;
    switch (eStatus)
    {
        case PMC_HVD1P1V_STATUS:
            bRetVal = PMC_HWA_Hvd1p1vStatus(PMC);
            break;
#if PMC_V25_SUPPORT
        case PMC_HVD2P5V_STATUS:
            bRetVal = PMC_HWA_Hvd2p5vStatus(PMC);
            break;
#endif
#if PMC_V3_SUPPORT
        case PMC_HVD3V_STATUS:
            bRetVal = PMC_HWA_Hvd3vStatus(PMC);
            break;
#endif
#if PMC_V5_SUPPORT
        case PMC_HVD5V_STATUS:
            bRetVal = PMC_HWA_Hvd5vStatus(PMC);
            break;
#endif
#if PMC_LVD_SUPPORT
        case PMC_LVD5V_STATUS:
            bRetVal = PMC_HWA_Lvd5vStatus(PMC);
            break;
#endif
        default:
            /* Invalid parameter: return */
            break;
    }
    return bRetVal;
}

/**
 * @brief Enable PMC interrupt
 * @param the parameter of interrupt flag
 */
void Pmc_EnableInterrupt(uint32 u32Val)
{
    Pmc_HWA_EnableInterrupt(PMC,u32Val);
}

/**
 * @brief Disable PMC interrupt
 * @param the parameter of interrupt flag
 */
void Pmc_DisableInterrupt(uint32 u32Val)
{
    PMC_HWA_DisableInterrupt(PMC, u32Val);
}

/**
 * @brief PMC Init
 *
 * @param pPmcHandle Pmc handle
 * @param pIntCfg    Pmc initialize configuration
 */
void Pmc_Init(PMC_HandleType* pPmcHandle, PMC_ConfigType *pIntCfg)
{
#if PMC_DEV_ERROR_REPORT == STD_ON
	if (NULL == pIntCfg)
	{
		PMC_ReportDevError(PMC_INIT_ID, PMC_E_PARAM_POINTER);
	}
	else
	{
#endif

	bool bIntrEn = false;

#if PMC_BUFVREF10_SUPPORT
	if(true == pIntCfg->bBufVref10En)
	{
		Pmc_HWA_EnableBufVref10Fpm(PMC);
	}
	else
	{
		Pmc_HWA_DisableBufVref10Fpm(PMC);
	}
#else
    if(true == pIntCfg->bV25RpmEn)
    {
    	Pmc_HWA_EnableV25Rpm(PMC);;
    }
    else
    {
    	Pmc_HWA_DisableV25Rpm(PMC);
    }
#endif

    /* Interrupt configuration */
	if ((uint32_t)PMC_INTR_MASK_HVD == ((uint32_t)PMC_INTR_MASK_HVD & (pIntCfg->u32InterruptMask)))
    {
        Pmc_EnableInterrupt(HVD_INTERRUPT);
        bIntrEn = true;
    }
#if PMC_LVD_SUPPORT
    if ((uint32_t)PMC_INTR_MASK_LVD == ((uint32_t)PMC_INTR_MASK_LVD & (pIntCfg->u32InterruptMask)))
    {
        Pmc_EnableInterrupt(LVD_INTERRUPT);
        bIntrEn = true;
    }
#endif
    if ( true == bIntrEn)
    {
    	pPmcHandle->pPmcFaultNotify = pIntCfg->pPmcFaultNotify;
    }

#if PMC_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief PMC DeInit
 *
 * @param pPmcHandle Pmc handle
 */
void Pmc_DeInit(PMC_HandleType* pPmcHandle)
{
    PMC_HWA_SetLVSCRRegister(PMC, LVSCR_DEFAULT_VAL);
    PMC_HWA_SetCONFIGRegister(PMC, CONFIG_DEFAULT_VAL);
    pPmcHandle->pPmcFaultNotify = NULL;
}


/**
 * @brief PMC clears all exist flag bit.
 *
 * This function clears all exist flag bit (see PMC_FlagType for list of flag bits).
 */
void Pmc_ClearAllFlag(void)
{
    PMC_HWA_SetLVSCRRegister(PMC, PMC_LVSCR_MASK);
}

/**
 * @brief PMC_UserIRQHandler function
 * Customer needs to write this function according by customer's requirement. This function is only resolve compile conflict
 *
 * @param pPmcHandle Pmc handle
 *
 */
void PMC_UserIRQHandler(PMC_HandleType* pPmcHandle)
{
    /* high voltage detection of 1.1V interrupt, keep CPU running in this loop until HVD fault disappear */
    if (PMC_GetFlag(PMC_HVD1P1V_FLAG) && PMC_ReadHVDInterruptFlag(PMC))
    {
    	PMC_ClearFlag(PMC_HVD1P1V_FLAG);

    	if (TRUE == (PMC_GetStatus(PMC_HVD1P1V_STATUS)))
        {
            if (NULL != pPmcHandle->pPmcFaultNotify)
            {
            	pPmcHandle->pPmcFaultNotify(pPmcHandle, PMC_HVD1P1V);
            }
        }
        else
        {
            /*The V11 has resumed from High Power*/
        }
    }
#if PMC_V25_SUPPORT
    /* high voltage detection of 2.5V interrupt, keep CPU running in this loop until HVD fault disappear */
    else if (PMC_GetFlag(PMC_HVD2P5V_FLAG) && PMC_ReadHVDInterruptFlag(PMC))
    {
    	PMC_ClearFlag(PMC_HVD2P5V_FLAG);
    	if (TRUE == (PMC_GetStatus(PMC_HVD2P5V_STATUS)))
        {
            if (NULL != pPmcHandle->pPmcFaultNotify)
            {
            	pPmcHandle->pPmcFaultNotify(pPmcHandle, PMC_HVD2P5V);
            }
        }
        else
        {
            /*The V25 has resumed from High Power!*/
        }
    }
#endif
#if PMC_V3_SUPPORT
    /* high voltage detection of 3V interrupt, keep CPU running in this loop until HVD fault disappear */
    else if (PMC_GetFlag(PMC_HVD3V_FLAG) && PMC_ReadHVDInterruptFlag(PMC))
    {
        PMC_ClearFlag(PMC_HVD3V_FLAG);
    	if (TRUE == (PMC_GetStatus(PMC_HVD3V_STATUS)))
        {
            if (NULL != pPmcHandle->pPmcFaultNotify)
            {
            	pPmcHandle->pPmcFaultNotify(pPmcHandle, PMC_HVD3V);
            }
        }
        else
        {
            /*The V3 has resumed from High Power!*/
        }
    }
#endif
#if PMC_V5_SUPPORT
    /* high voltage detection of 5V interrupt, keep CPU running in this loop until HVD fault disappear */
    else if (PMC_GetFlag(PMC_HVD5V_FLAG) && PMC_ReadHVDInterruptFlag(PMC))
    {
        PMC_ClearFlag(PMC_HVD5V_FLAG);
    	if (TRUE == (PMC_GetStatus(PMC_HVD5V_STATUS)))
        {
            if (NULL != pPmcHandle->pPmcFaultNotify)
            {
            	pPmcHandle->pPmcFaultNotify(pPmcHandle, PMC_HVD5V);
            }
        }
        else
        {
            /*The V5 has resumed from High Power!*/
        }
    }
#endif
#if PMC_LVD_SUPPORT
    /* low voltage detection of 5V interrupt, keep CPU running in this loop until LVD fault disappear */
    else if (PMC_GetFlag(PMC_LVD5V_FLAG) && PMC_ReadLVDInterruptFlag(PMC))
    {
    	PMC_ClearFlag(PMC_LVD5V_FLAG);

    	if (TRUE == (PMC_GetStatus(PMC_LVD5V_STATUS)))
        {
            if (NULL != pPmcHandle->pPmcFaultNotify)
            {
            	pPmcHandle->pPmcFaultNotify(pPmcHandle, PMC_LVD5V);
            }
        }
        else
        {
            /*The V5 has resumed from Low Power!*/
        }
    }
#endif
    else
    {
    	/* some error */
    }
}

#endif

