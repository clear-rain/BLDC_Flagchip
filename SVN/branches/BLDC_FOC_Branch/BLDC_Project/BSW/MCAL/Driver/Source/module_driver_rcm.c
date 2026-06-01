/**
 * @file module_driver_rcm.c
 * @author Flagchip
 * @brief RCM driver source code
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/
#include "module_driver_rcm.h"

#if RCM_INSTANCE_COUNT > 0U

#include "module_driver_smisc.h"

#ifndef RCM_DEV_ERROR_REPORT
#define RCM_DEV_ERROR_REPORT	STD_OFF
#endif

#if RCM_DEV_ERROR_REPORT == STD_ON
#define RCM_ReportDevError(func, error) ReportDevError(RCM_MODULE_ID, func, error)
#endif

/**
 * @brief This local function can disable interrupt before an reset appear.
 */
static RCM_StatusType RCM_DisableInt(uint16_t u16Reset, bool bClearDelay);

/**
 * @brief This api can get RCM register that indicate the source of the most recent reset.
 *
 * @return RCM->SRS register, bit 0-13 corresponding to RCM_ResetEventType 0-13, refer to reference manual for details.
 * @note Multiple flags can be set if multiple reset events occur at the same time
 */
uint32_t RCM_GetLastResetFLag(void)
{
    return RCM_HWA_ReadLastResetFlag();
}

/**
 * @brief This api can get RCM register that indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @returnRCM->SSRS register, bit 0-13 corresponding to RCM_ResetEventType 0-13, refer to reference manual for details.
 */
uint32_t RCM_GetAllResetFlag(void)
{
    return RCM_HWA_ReadAllResetFlagBeforePOR();
}

/**
 * @brief This api can clear reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Enumeration of reset event flag
 */
void RCM_ClearResetFlagAfterPOR(const RCM_ResetEventType eReset)
{
    RCM_HWA_ClearResetFlagAfterPOR(eReset);
}

/**
 * @brief This api can clear all reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
void RCM_ClearAllResetFlagAfterPOR(void)
{
    RCM_HWA_ClearAllResetFlagAfterPOR();
}

/**
 * @brief Enable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param u8BusClockFilterWidth Bus clock filter width
 * @param bLpClkEn select AON clock at low power mode
 * @return RCM return type
 * @note If use AON32K clock, the filter width less than 3 AON32K clock.
 */
RCM_StatusType RCM_EnableResetFilter(RCM_FilterClkSrc eClk, uint8_t u8BusClockFilterWidth, bool bLpClkEn)
{
#if	RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K
    uint32_t u32Aon32kFreq = 0U;
#endif
    RCM_StatusType eRet = RCM_STATUS_SUCCESS;
    uint32_t u32Temp = 0U;
#if (RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K != 1u)
    (void)bLpClkEn;
    if (eClk > RCM_RESET_FILTER_BUS_CLOCK)
    {
        eRet = RCM_STATUS_PARAM_INVALID;
    }
#endif
#if	RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K
    if (eClk > RCM_RESET_FILTER_AON32K_CLOCK)
    {
        eRet = RCM_STATUS_PARAM_INVALID;
    }
    if ((RCM_STATUS_SUCCESS == eRet) && ((eClk > RCM_RESET_FILTER_BUS_CLOCK) || (bLpClkEn)))
    {
        if (SMISC_GetSMISCClockFreq(SMISC_AON32K_CLK, &u32Aon32kFreq))
        {
            if (0U == u32Aon32kFreq)
            {
                eRet = RCM_STATUS_CLOCK_INVALID;
            }
        }
        else
        {
            eRet = RCM_STATUS_CLOCK_INVALID;
        }
    }
#endif

    if (RCM_STATUS_SUCCESS == eRet)
    {
        /* Add robustness item */
    	RCM_HWA_SetRstfltReg(0U);

#if RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K
        if (RCM_RESET_FILTER_AON32K_CLOCK == eClk)
        {
        	u32Temp = (uint32_t)RCM_RSTFLT_RSTFLT_AON_MASK;
        }

        if (bLpClkEn)
        {
        	u32Temp |= (uint32)RCM_RSTFLT_RSTFLT_AON_LP_MASK;
        }
#endif

        if (RCM_RESET_FILTER_BUS_CLOCK == eClk)
        {
            u32Temp = RCM_RSTFLT_RSTFLT_BUSW(u8BusClockFilterWidth);
            u32Temp|= RCM_RSTFLT_RSTFLT_BUS_MASK;
        }

        RCM_HWA_SetRstfltReg(u32Temp);
    }
    return eRet;
}


/**
 * @brief Disable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param bLpClkEn select AON clock at low power mode
 * @return RCM return type
 */
RCM_StatusType RCM_DisableResetFilter(RCM_FilterClkSrc eClk, bool bLpClkEn)
{
    RCM_StatusType eRet = RCM_STATUS_SUCCESS;
#if (RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K != 1u)
    (void)bLpClkEn;
    if (eClk > RCM_RESET_FILTER_BUS_CLOCK)
    {
        eRet = RCM_STATUS_PARAM_INVALID;
    }
#endif
#if RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K
    if (eClk > RCM_RESET_FILTER_AON32K_CLOCK)
    {
        eRet = RCM_STATUS_PARAM_INVALID;
    }
#endif

    if (RCM_STATUS_SUCCESS == eRet)
    {
#if RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K
        if (RCM_RESET_FILTER_AON32K_CLOCK == eClk)
        {
            RCM_HWA_DisableAon32kClockFilter();
        }

        if (bLpClkEn)
        {
            RCM_HWA_DisableAon32kLPClockFilter();
        }
#endif
        if (RCM_RESET_FILTER_BUS_CLOCK == eClk)
        {
            RCM_HWA_ClearBusClockFilterWidth();
            RCM_HWA_DisableBusClockFilter();
        }
    }
    return eRet;
}

/**
 * @brief This api can disable interrupt before an reset appear.
 *
 * @param u16Reset Reset event flag, like: RCM_INT_CLKERR1 | RCM_INT_CLKERR0
 * @param bClearDelay Whether to clear delay configuration
 * @return RCM return type
 */
static RCM_StatusType RCM_DisableInt(uint16_t u16Reset, bool bClearDelay)
{
    RCM_StatusType eRet = RCM_STATUS_SUCCESS;
    if (RCM_STATUS_SUCCESS == eRet)
    {
        if (bClearDelay)
        {
            RCM_HWA_ClearResetDelay();
        }
        RCM_HWA_DisableResetInterrupt(u16Reset);
    }
    return eRet;
}

/**
 * @brief Generate software reset through cotex-m register
 *
 */
void RCM_GenerateSwReset(void)
{
    CM4_HWA_SystemReset();
}

/**
 * @brief RCM initialize function
 *
 * @param pRcmHandle Rcm handle
 * @param pInitCfg   Init pointer
 *
 */
void RCM_Init(RCM_HandleType* pRcmHandle, RCM_ConfigType *pInitCfg)
{
    RCM_StatusType eRet = RCM_STATUS_SUCCESS;
#if RCM_RESET_DELAY_CLOCK_AON32K
    uint32_t u32Aon32kFreq = 0U;
#endif

#if RCM_DEV_ERROR_REPORT == STD_ON
    if ( NULL == pInitCfg )
    {
        RCM_ReportDevError(RCM_INIT_ID, RCM_E_PARAM_POINTER);
    }
    else
    {
#endif

        eRet = RCM_EnableResetFilter(pInitCfg->eFliterClkSrc, pInitCfg->u8BusClockFilterWidth, pInitCfg->bResetfiltAonLp);

        if (RCM_STATUS_SUCCESS == eRet)
        {
            if(0U != pInitCfg->u32InterruptMask)
            {
                /* Interrupt configuration */
#if RCM_RESET_DELAY_CLOCK_AON32K
                if (SMISC_GetSMISCClockFreq(SMISC_AON32K_CLK, &u32Aon32kFreq))
                {
                    if (0U == u32Aon32kFreq)
                    {
                        eRet = RCM_STATUS_CLOCK_INVALID;
                    }
                }
                else
                {
                    eRet = RCM_STATUS_CLOCK_INVALID;
                }
#endif
                if (RCM_STATUS_SUCCESS == eRet)
                {   
                    RCM_HWA_EnableGlobalResetInterrupt();
                    RCM_HWA_SetResetDelay(pInitCfg->eDelay);
                    RCM_HWA_EnableResetInterrupt((uint16_t)(pInitCfg->u32InterruptMask));
                    pRcmHandle->pRcmResetInterruptNotify = pInitCfg->pRcmResetInterruptNotify;
                }
                else
                {
                    (void)RCM_DisableInt(0U, true);
                }
            }
            else
            {
                (void)RCM_DisableInt(0U, true);
            }
        }

#if RCM_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief RCM Deinitialize function
 *
 * @param pRcmHandle Rcm handle
 *
 */
void RCM_DeInit(RCM_HandleType* pRcmHandle)
{
    RCM_HWA_SetRstfltReg(0U);
    RCM_HWA_SetSrieReg(0U);
    pRcmHandle->pRcmResetInterruptNotify = NULL;
}

/**
 * @brief RCM interrupt process function
 *
 */
void RCM_UserIRQHandler(RCM_HandleType* pRcmHandle)
{
    if (NULL != pRcmHandle->pRcmResetInterruptNotify)
    {
        pRcmHandle->pRcmResetInterruptNotify(pRcmHandle, RCM_GetAllResetFlag());
    }
}


#endif
