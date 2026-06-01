/**
 * @file module_driver_intm.c
 * @author Flagchip100
 * @brief INTM driver source code
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
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#include <module_driver_intm.h>

#if INTM_INSTANCE_COUNT > 0U


#ifndef INTM_DEV_ERROR_REPORT
    #define INTM_DEV_ERROR_REPORT   STD_OFF
#endif

#if INTM_DEV_ERROR_REPORT == STD_ON
    #define INTM_ReportDevError(func, error) ReportDevError(INTM_MODULE_ID, func, error)
#endif

/* ################################################################################## */
/* ##################################### Macros ##################################### */


/* ################################################################################## */
/* ################################# Local Variables ################################ */

static INTM_Type *const s_aIntm_Base[INTM_INSTANCE_MAX] = INTM_BASE_PTRS;


/* ################################################################################## */
/* ################################# Global Functions ############################### */

/**
 * @brief Init the INTM.
 * 
 * @param pIntmHandle INTM instance.
 * @param pInitCfg Init Configuration.
 */
void INTM_Init(INTM_HandleType *pIntmHandle, const INTM_InitType *const pInitCfg)
{
    INTM_MonitorType *pMonitor;
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_INIT_ID, INTM_E_PARAM_INSTANCE);
    }
    else if ((NULL == pInitCfg) || (pInitCfg->eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX))
    {
        INTM_ReportDevError(INTM_INIT_ID, INTM_E_PARAM_POINTER);
    }
    else if ((pInitCfg->u32SrcDelayCnt >= 0xFFFFFFU) || pInitCfg->u16IrqNumber >= IRQn_MAX)
    {
        INTM_ReportDevError(INTM_INIT_ID, INTM_E_PARAM_POINTER);
    }
    else
    {
    #endif

        pMonitor = INTM_HWA_GetIrqMonitor(pIntm, (uint8_t)pInitCfg->eIrqMonitorIndex);
        INTM_HWA_SetIRQReqNum(pMonitor, pInitCfg->u16IrqNumber);
        INTM_HWA_EnableReset(pMonitor, pInitCfg->bEnReset);
        INTM_HWA_EnableInterrupt(pMonitor, pInitCfg->bEnInterrupt);
        INTM_HWA_SetLatency(pMonitor, pInitCfg->u32SrcDelayCnt);

        #if INTERRUPT_INACTIVE_MODE_SUPPORT
        if (pInitCfg->eMode == INTM_INTERRUPT_MODE_INACTIVE)
        {
            INTM_HWA_EnableInactiveMode(pMonitor, true);
        }
        else
        {
            INTM_HWA_EnableInactiveMode(pMonitor, false);
        }
        #endif

        INTM_enable(pIntmHandle, true);
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Enable INTM.
 *
 * @param pIntmHandle INTM instance.
 * @param bEnable Enable INTM.
 */
void INTM_enable(INTM_HandleType *pIntmHandle, const bool bEnable)
{
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_ENABLE_ID, INTM_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        INTM_HWA_Enable(pIntm, bEnable);
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


#if INTERRUPT_INACTIVE_MODE_SUPPORT

/**
 * @brief Start INTM inactive mode.
 * 
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 */
void INTM_StartInactiveMode(INTM_HandleType *pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex)
{

    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    INTM_MonitorType *pMonitor;


    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_START_INACTIVE_ID, INTM_E_PARAM_INSTANCE);
    }
    else if (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX)
    {
        INTM_ReportDevError(INTM_START_INACTIVE_ID, INTM_E_PARAM_PARAM);
    }
    else
    {
    #endif

        pMonitor = INTM_HWA_GetIrqMonitor(pIntm, (uint8_t)eIrqMonitorIndex);
        INTM_HWA_StartInactiveMode(pMonitor);

        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief
 * 
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 */
void INTM_StopInactiveMode(INTM_HandleType *pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    INTM_MonitorType *pMonitor;
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_STOP_INACTIVE_ID, INTM_E_PARAM_INSTANCE);
    }
    else if (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX)
    {
        INTM_ReportDevError(INTM_STOP_INACTIVE_ID, INTM_E_PARAM_PARAM);
    }
    else
    {
    #endif

        pMonitor = INTM_HWA_GetIrqMonitor(pIntm, (uint8_t)eIrqMonitorIndex);
        INTM_HWA_StopInactiveMode(pMonitor);
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}
#endif

/**
 * @brief Write the interrupt acknowledge.
 *
 * @param pIntmHandle INTM instance.
 * @param u16IrqNumber Interrupt nunmber.
 */
void INTM_SetAcknowledge(INTM_HandleType *pIntmHandle, const uint16_t u16IrqNumber)
{
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_SET_ACKNOWLEDGE_ID, INTM_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        INTM_HWA_SetIACKR(pIntm, u16IrqNumber);
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Return counter value.
 *
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return Counter value.
 */
uint32_t INTM_GetCounterValue(INTM_HandleType *pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    INTM_MonitorType *pMonitor;
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_GET_COUNTER_ID, INTM_E_PARAM_INSTANCE);
    }
    else if (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX)
    {
        INTM_ReportDevError(INTM_GET_COUNTER_ID, INTM_E_PARAM_PARAM);
    }
    else
    {
    #endif
        pMonitor = INTM_HWA_GetIrqMonitor(pIntm, (uint8_t)eIrqMonitorIndex);
        return INTM_HWA_GetTimerCounter(pMonitor);
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Clear the interrupt flag.
 *
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 */
void INTM_ClearIntFlag(INTM_HandleType *pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    INTM_MonitorType *pMonitor;
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_CLEAR_INT_FLAG_ID, INTM_E_PARAM_INSTANCE);
    }
    else if (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX)
    {
        INTM_ReportDevError(INTM_CLEAR_INT_FLAG_ID, INTM_E_PARAM_POINTER);
    }
    else
    {
    #endif
        pMonitor = INTM_HWA_GetIrqMonitor(pIntm, (uint8_t)eIrqMonitorIndex);
        INTM_HWA_SetTimerCounter(pMonitor, 0U);
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Get the timeout flag. Return true if INTM_TMR value has exceeded the INTM_LATR value.
 *
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return Timeout flag.
 */
bool INTM_GetTimeoutStatus(INTM_HandleType *pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex)
{
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    INTM_MonitorType *pMonitor;
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_GET_TIMEOUT_STAT_ID, INTM_E_PARAM_INSTANCE);
    }
    else if (eIrqMonitorIndex >= INTM_IRQ_MONITOR_MAX)
    {
        INTM_ReportDevError(INTM_GET_TIMEOUT_STAT_ID, INTM_E_PARAM_PARAM);
    }
    else
    {
    #endif
        pMonitor = INTM_HWA_GetIrqMonitor(pIntm, (uint8_t)eIrqMonitorIndex);
        return INTM_HWA_ReadStatus(pMonitor);
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief intm process interrupt function
 * 
 * @param pIntmHandle INTM instance.
 */
void INTM_IRQProcess(INTM_HandleType *pIntmHandle)
{
    uint8_t u8i;
    INTM_MonitorType *pMonitor;
    INTM_Type *const pIntm = s_aIntm_Base[pIntmHandle->eInstance];
    #if INTM_DEV_ERROR_REPORT == STD_ON
    if ((pIntmHandle->eInstance) >= INTM_INSTANCE_MAX)
    {
        INTM_ReportDevError(INTM_IRQ_PRCE_ID, INTM_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        for (u8i = 0; u8i < (uint8_t)INTM_IRQ_MONITOR_MAX; u8i++)
        {
            pMonitor = INTM_HWA_GetIrqMonitor(pIntm, u8i);
            if (INTM_HWA_ReadStatus(pMonitor))
            {
                if (pIntmHandle->tSettings.pIntmIsrCallback[u8i] != NULL)
                {
                    pIntmHandle->tSettings.pIntmIsrCallback[u8i](pIntmHandle);
                }
            }
        }
        #if INTM_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

#endif
