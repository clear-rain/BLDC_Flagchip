/**
 * @file module_driver_wdog.c
 * @author Flagchip031
 * @brief WDOG driver source code
 * @version 2.0.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip074   N/A          First version
*********************************************************************************/

#include "module_driver_wdog.h"

#if WDOG_INSTANCE_COUNT > 0U

#ifndef WDOG_DEV_ERROR_REPORT
#define WDOG_DEV_ERROR_REPORT    STD_OFF
#endif

#if WDOG_DEV_ERROR_REPORT == STD_ON
#define WDOG_ReportDevError(func, error) ReportDevError(WDOG_MODULE_ID, func, error)
#endif

/********* Local Variables ************/
static WDOG_Type *const s_apWdogBase[WDOG_INSTANCE_COUNT] = WDOG_BASE_PTRS;

/**
 * @brief UNLOCK and REFRESH CMD For MPW FC4150. this may not match with FC4150 user manual
 */
#define WDOG_UNLOCK_CMD                 (uint32_t)(0x08181982U)
#define WDOG_REFRESH_CMD                (uint32_t)(0x20CFFC20U)
#define WDOG_FLAG_TIMEOUT_CMD           (uint32_t)(0x00FFFFFFU)

/**
 * @brief unlock the wdog before Watch dog reconfigure set.
 * @param pWdogHandle: WDOG processing handle
 */
void WDOG_Unlock(WDOG_HandleType* pWdogHandle)
{
    WDOG_Type *pWdog = s_apWdogBase[pWdogHandle->eIntance];
    WDOG_HWA_SetCounter(pWdog,WDOG_UNLOCK_CMD);
}

/**
 * @brief feed the watch dog by writing typical cmd to counter.
 * @param pWdogHandle: WDOG processing handle
 */
void WDOG_Refresh(WDOG_HandleType* pWdogHandle)
{
    WDOG_Type *pWdog = s_apWdogBase[pWdogHandle->eIntance];
    WDOG_HWA_SetCounter(pWdog,WDOG_REFRESH_CMD);
}

/**
 * @brief Initialize the WDOG configuration setting.
 * @param pWdogHandle: WDOG processing handle
 * @param pWdogCfg: the configurations of the WDOG module
 * @return WDOG_StatusType initialization status
 */
WDOG_StatusType WDOG_Init(WDOG_HandleType* pWdogHandle, const WDOG_CfgType *const pWdogCfg)
{
    WDOG_StatusType eRet = WDOG_STATUS_SUCCESS;
#if WDOG_DEV_ERROR_REPORT == STD_ON
    if(pWdogHandle->eIntance >= WDOG_INSTANCE_MAX)
    {
        eRet = WDOG_STATUS_ERROR;
        WDOG_ReportDevError(WDOG_INIT_ID, WDOG_E_PARAM_INSTANCE);
    }
    else if((pWdogCfg->bWinEnable == true) && (pWdogCfg->u16WindowValue > pWdogCfg->u16TimeoutValue))
    {
        eRet = WDOG_STATUS_ERROR;
        WDOG_ReportDevError(WDOG_INIT_ID, WDOG_E_PARAM_TIMEOUT);
    }
    else
    {
#endif
        WDOG_Type *pWdog = s_apWdogBase[pWdogHandle->eIntance];
        uint8_t  u8Times = 128U;
        uint32_t u32First = 1U;
        uint32_t u32Temp = 0U;
        uint16_t u16Timeout = 0U;
        uint16_t u16WindowTime = 0U;
        uint32_t u32FlagTimeout = WDOG_FLAG_TIMEOUT_CMD;

        u16Timeout = pWdogCfg->u16TimeoutValue;
        u16WindowTime = pWdogCfg->u16WindowValue;
        u32Temp = WDOG_HWA_GetCs(pWdog);
        u32Temp &= ~(WDOG_CS_CLK_SEL_MASK | WDOG_CS_TST_MASK | WDOG_CS_FLAG_MASK) ;
        u32Temp |= WDOG_CS_WIN(pWdogCfg->bWinEnable)  | WDOG_CS_PRESCALER(pWdogCfg->bPrescalerEnable) |
                   WDOG_CS_CLK_SEL(pWdogCfg->eClkSource) | WDOG_CS_TST(pWdogCfg->eTesttype) | WDOG_CS_INT(pWdogCfg->bInterruptEnable) |
                   WDOG_CS_DBG(pWdogCfg->bEnableInDebug)  | WDOG_CS_UPDATE_MASK | WDOG_CS_ENABLE(pWdogCfg->bEnable) |
                   WDOG_CS_WAIT(pWdogCfg->bEnableInWait)  | WDOG_CS_STOP(pWdogCfg->bEnableInStop);

#if WDOG_RESET_DELAY_SUPPORT
        if(WDOG_REACTION_NO_INT != pWdogCfg->eTimeoutReaction)
        {
            u32Temp |= WDOG_CS_DLY_CNT_MSB(pWdogCfg->eTimeoutReaction);
        }
        else
        {
            //Do nothing. Keep disabling the wdog interrupt and no reset dealy.
        }
#endif
        DISABLE_INTERRUPTS();
        while(u8Times--)
        {
            if(WDOG_HWA_GetUnlockStatus(pWdog) == false)
            {
                /* As long as there is 0 once, it means wdog is not the first time configuration */
                u32First = 0U;
                break;
            }
        }

        if(u32First == 0U)
        {
            while (((WDOG_HWA_GetCs(pWdog) & WDOG_CS_RECFG_STAT_MASK) != WDOG_CS_RECFG_STAT_MASK) && (u32FlagTimeout > 0U))
            {
                u32FlagTimeout = u32FlagTimeout - 1U;
                /* Wait until RECFG_STAT set */
            }
            if(u32FlagTimeout == 0U)
            {
                eRet = WDOG_STATUS_ERROR_RECFG;
            }
            else
            {
                u32FlagTimeout = WDOG_FLAG_TIMEOUT_CMD;
                WDOG_Unlock(pWdogHandle);
                /* After completing the unlock sequence, the reconfiguration must be taken within 128 bus clocks;
                 * otherwise, the watchdog closes the unlock window. */

                while ((WDOG_HWA_GetUnlockStatus(pWdog) == false) && (u32FlagTimeout > 0U))
                {
                    /* 0 indicate WDOG locked. Wait until registers are unlocked */
                    u32FlagTimeout = u32FlagTimeout - 1U;
                }
                if(u32FlagTimeout == 0U)
                {
                    eRet = WDOG_STATUS_ERROR_UNLOCK;
                }
            }
        }

        if(eRet == WDOG_STATUS_SUCCESS)
        {
            /* Set Timer-out register */
            WDOG_HWA_SetTimeout(pWdog,u16Timeout);

            /* Set Window register */
            WDOG_HWA_SetWindow(pWdog,u16WindowTime);

            /* Set CS register */
            WDOG_HWA_SetCs(pWdog,u32Temp);

            u32FlagTimeout = WDOG_FLAG_TIMEOUT_CMD;
            while (((WDOG_HWA_GetCs(pWdog) & WDOG_CS_RECFG_STAT_MASK) != WDOG_CS_RECFG_STAT_MASK) && (u32FlagTimeout > 0U))
            {
                u32FlagTimeout = u32FlagTimeout - 1U;
                /* RECFG_STAT is set when WDOG is successfully reconfigured. Wait until registers reconfiguration successful */
            }
            if(u32FlagTimeout == 0U)
            {
                eRet = WDOG_STATUS_ERROR_RECFG;
            }
        }

        ENABLE_INTERRUPTS();
#if WDOG_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

/**
 * @brief De-initialize the WDOG instance
 * @param pWdogHandle: WDOG processing handle
 */
void WDOG_DeInit(WDOG_HandleType* pWdogHandle)
{
    WDOG_Type *pWdog = s_apWdogBase[pWdogHandle->eIntance];
    uint32_t u32Temp = 0U;

    u32Temp |= WDOG_CS_WIN(0u)  | WDOG_CS_PRESCALER(0u) |
               WDOG_CS_CLK_SEL(WDOG_AON_CLK) | WDOG_CS_TST(WDOG_TST_DISABLED) | WDOG_CS_INT(0u) |
               WDOG_CS_DBG(0u)  | WDOG_CS_UPDATE_MASK | WDOG_CS_ENABLE(0u) |
               WDOG_CS_WAIT(0u)  | WDOG_CS_STOP(0u);

#if WDOG_RESET_DELAY_SUPPORT
    u32Temp |= WDOG_CS_DLY_CNT_MSB(WDOG_REACTION_INT_512_CYCLE);
#endif
    DISABLE_INTERRUPTS();

    WDOG_Unlock(pWdogHandle);
    /* After completing the unlock sequence, the reconfiguration must be taken within 128 bus clocks;
     * otherwise, the watchdog closes the unlock window. */

    while (WDOG_HWA_GetUnlockStatus(pWdog) == false)
    {
        /* 0 indicate WDOG locked. Wait until registers are unlocked */
    }

    /* Set Timer-out register */
    WDOG_HWA_SetTimeout(pWdog, (uint16_t)0x400U);

    /* Set Window register */
    WDOG_HWA_SetWindow(pWdog, (uint16_t)0x0U);

    /* Set CS register */
    WDOG_HWA_SetCs(pWdog, u32Temp);

    ENABLE_INTERRUPTS();
}
/**
 * @brief Wdg n interrupt process
 *
 * @param pWdogHandle: WDOG processing handle
 */
void WDOG_IRQHandler(WDOG_HandleType* pWdogHandle)
{
    WDOG_HWA_ClearInterruptFlag(s_apWdogBase[pWdogHandle->eIntance]);
    if(NULL != pWdogHandle->tSettings.pISRCallback)
    {
        pWdogHandle->tSettings.pISRCallback(pWdogHandle);
    }
}

#endif
