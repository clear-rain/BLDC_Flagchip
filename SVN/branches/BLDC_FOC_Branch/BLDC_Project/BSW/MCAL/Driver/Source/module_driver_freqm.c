/**
 * @file        module_driver_freqm.c
 * @author Flagchip100
 * @brief FREQM driver source code
 * @version     2.0.0
 * @date        2024-08-01
 *
 * @copyright   Copyright 2020-2024 Flagchip Semiconductors Co., Ltd.
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#include "module_driver_freqm.h"

#if (FREQM_INSTANCE_COUNT > 0u)

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef FREQM_DEV_ERROR_REPORT
#define FREQM_DEV_ERROR_REPORT    STD_OFF
#endif

#if FREQM_DEV_ERROR_REPORT == STD_ON
#define FREQM_ReportDevError(func, error)     ReportDevError(FREQM_MODULE_ID, func, error)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static FREQM_Type *const s_apFreqmBase[FREQM_INSTANCE_COUNT] = FREQM_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Initializes the FREQM module with the specified configuration.
 *
 * This function initializes the FREQM module with the given configuration settings, including the clock divider value,
 * the clock source to be measured, the measurement length, and the reference timeout.
 *
 * @param pHandle Pointer to the FREQM handle structure.
 * @param pInitStruct Pointer to the initialization structure containing the configuration settings.
 *
 * @return FREQM_StatusType Indicates the status of the initialization process (FREQM_STATUS_SUCCESS or FREQM_STATUS_FAIL).
 *
 * @note If any of the required pointers are NULL or the instance index is out of range, a device error will be reported,
 * and the function returns FREQM_STATUS_FAIL.
 */
FREQM_StatusType FREQM_Init(FREQM_HandleType *const pHandle, const FREQM_CfgType *const pInitStruct)
{
    FREQM_StatusType eStatus = FREQM_STATUS_SUCCESS;

#if FREQM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        FREQM_ReportDevError(FREQM_INIT_ID, FREQM_E_PARAM_NULLPTR);
        eStatus = FREQM_STATUS_FAIL;
    }
    else if (pInitStruct == NULL)
    {
        FREQM_ReportDevError(FREQM_INIT_ID, FREQM_E_PARAM_NULLPTR);
        eStatus = FREQM_STATUS_FAIL;
    }
    else if (pHandle->eInstance >= FREQM_INSTANCE_COUNT)
    {
        FREQM_ReportDevError(FREQM_INIT_ID, FREQM_E_PARAM_INSTANCE);
        eStatus = FREQM_STATUS_FAIL;
    }
    else
#endif
    {
        FREQM_Type *const pFreqm = s_apFreqmBase[pHandle->eInstance];
        uint32_t u32TimeOutVal = 0xffff;
        uint32_t u32CntStatus;

        FREQM_HWA_DisableCntEventInterrupt(pFreqm);

        /* Configure the clock divider value */
        FREQM_HWA_MesClk_PreDiv(pFreqm, pInitStruct->u8PredivVal);
        /* Select the clock source to be measured */
        FREQM_HWA_MesClkSel(pFreqm, pInitStruct->u8ClkSel);

        FREQM_HWA_EnableCntEventInterrupt(pFreqm);

        /* Configure the measure counter targer value */
        FREQM_HWA_SetMesLength(pFreqm, pInitStruct->u32MesLen);
        /* Configure the reference counter target value */
        FREQM_HWA_SetRefTimeout(pFreqm, pInitStruct->u32RefTo);


        FREQM_HWA_SetRefCnt(pFreqm, 0u);
        do
        {
            u32CntStatus = FREQM_HWA_GetCntStatus(pFreqm);
            u32TimeOutVal--;
            if (u32TimeOutVal == 0u)
            {
                FREQM_HWA_DisableCntEventInterrupt(pFreqm);
                eStatus = FREQM_STATUS_TIMEOUT;
                break;
            }
        } while(u32CntStatus != 0u);
    }

    return eStatus;
}

/**
 * @brief Deinitializes the FREQM module.
 *
 * This function deinitializes the specified FREQM module instance by resetting its configuration settings to default
 * values and disabling the counter event interrupt.
 *
 * @param pHandle Pointer to the FREQM handle structure.
 *
 * @return FREQM_StatusType Indicates the status of the deinitialization process (FREQM_STATUS_SUCCESS or FREQM_STATUS_FAIL).
 *
 * @note If the handle pointer is NULL or the instance index is out of range, a device error will be reported, and the
 * function returns FREQM_STATUS_FAIL.
 */
FREQM_StatusType FREQM_DeInit(FREQM_HandleType *const pHandle)
{
    FREQM_StatusType eStatus = FREQM_STATUS_SUCCESS;

#if FREQM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        FREQM_ReportDevError(FREQM_DEINIT_ID, FREQM_E_PARAM_NULLPTR);
        eStatus = FREQM_STATUS_FAIL;
    }
    else if (pHandle->eInstance >= FREQM_INSTANCE_COUNT)
    {
        FREQM_ReportDevError(FREQM_DEINIT_ID, FREQM_E_PARAM_INSTANCE);
        eStatus = FREQM_STATUS_FAIL;
    }
    else
#endif
    {
        FREQM_Type *const pFreqm = s_apFreqmBase[pHandle->eInstance];

        /* Set register to reset value */    
        FREQM_HWA_MesClk_PreDiv(pFreqm, 0u);
        FREQM_HWA_MesClkSel(pFreqm, 0u);
        FREQM_HWA_SetMesLength(pFreqm, 0xFFFFFFFFu);
        FREQM_HWA_SetRefTimeout(pFreqm, 0xFFFFFFFFu);
        
        FREQM_HWA_DisableCntEventInterrupt(pFreqm);
    }

    return eStatus;
}

/**
 * @brief Starts the frequency measurement process in the FREQM module.
 *
 * This function starts the frequency measurement process by resetting the measurement counter to zero.
 *
 * @param pHandle Pointer to the FREQM handle structure.
 *
 * @return FREQM_StatusType Indicates the status of the start measurement process (FREQM_STATUS_SUCCESS or FREQM_STATUS_FAIL).
 *
 * @note If the handle pointer is NULL or the instance index is out of range, a device error will be reported, and the
 * function returns FREQM_STATUS_FAIL.
 */
FREQM_StatusType FREQM_StartMeasure(FREQM_HandleType *pHandle)
{
    FREQM_StatusType eStatus = FREQM_STATUS_SUCCESS;

#if FREQM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        FREQM_ReportDevError(FREQM_STARTMEASURE_ID, FREQM_E_PARAM_NULLPTR);
        eStatus = FREQM_STATUS_FAIL;
    }
    else if (pHandle->eInstance >= FREQM_INSTANCE_COUNT)
    {
        FREQM_ReportDevError(FREQM_STARTMEASURE_ID, FREQM_E_PARAM_INSTANCE);
        eStatus = FREQM_STATUS_FAIL;
    }
    else
#endif
    {
        FREQM_Type *const pFreqm = s_apFreqmBase[pHandle->eInstance];

        FREQM_HWA_SetMesCnt(pFreqm, 0u);
    }

    return eStatus;
}

/**
 * @brief Clears the status of the FREQM module.
 *
 * This function clears the status of the specified FREQM module instance by resetting the reference counter and waiting
 * for the counters to stop.
 *
 * @param pHandle Pointer to the FREQM handle structure.
 *
 * @return FREQM_StatusType Indicates the status of the clear status operation (FREQM_STATUS_SUCCESS or FREQM_STATUS_FAIL).
 *
 * @note If the handle pointer is NULL or the instance index is out of range, a device error will be reported, and the
 * function returns FREQM_STATUS_FAIL.
 */
FREQM_StatusType FREQM_ClearStatus(FREQM_HandleType *pHandle)
{
    FREQM_StatusType eStatus = FREQM_STATUS_SUCCESS;

#if FREQM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        FREQM_ReportDevError(FREQM_CLEARSTATUS_ID, FREQM_E_PARAM_NULLPTR);
        eStatus = FREQM_STATUS_FAIL;
    }
    else if (pHandle->eInstance >= FREQM_INSTANCE_COUNT)
    {
        FREQM_ReportDevError(FREQM_CLEARSTATUS_ID, FREQM_E_PARAM_INSTANCE);
        eStatus = FREQM_STATUS_FAIL;
    }
    else
#endif
    {
        FREQM_Type *const pFreqm = s_apFreqmBase[pHandle->eInstance];
        uint32_t u32TimeOutVal = 0xffff;
        uint32_t u32CntStatus;

        FREQM_HWA_SetRefCnt(pFreqm, 0u);
        do
        {
            u32CntStatus = FREQM_HWA_GetCntStatus(pFreqm);
            u32TimeOutVal--;
            if (u32TimeOutVal == 0u)
            {
                eStatus = FREQM_STATUS_TIMEOUT;
                break;
            }
        } while(u32CntStatus != 0u);
    }

    return eStatus;
}

/**
 * @brief Handles common interrupts for the FREQM module.
 *
 * This function processes the common interrupts for the specified FREQM module instance. It checks the interrupt flags and
 * calls the appropriate callback functions based on the interrupt status.
 *
 * @param pHandle Pointer to the FREQM handle structure.
 *
 * @note If the handle pointer is NULL or the instance index is out of range, a device error will be reported.
 */
void FREQM_CommonIRQHandler(FREQM_HandleType *const pHandle)
{
#if FREQM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        FREQM_ReportDevError(FREQM_COMMONIRQHANDLER_ID, FREQM_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= FREQM_INSTANCE_COUNT)
    {
        FREQM_ReportDevError(FREQM_COMMONIRQHANDLER_ID, FREQM_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        FREQM_Type *const pFreqm = s_apFreqmBase[pHandle->eInstance];
        uint32_t u32CntStatus;

        if (FREQM_HWA_GetInterruptFlag(pFreqm) == true)
        {
            FREQM_HWA_ClearInterruptFlag(pFreqm);
        }

        u32CntStatus = FREQM_HWA_GetCntStatus(pFreqm);
        if(u32CntStatus == FREQM_CNT_STATUS_MES_CNT_START_MASK)//0x4
        {
            if (pHandle->tSettings.pMesCntStartCallback != NULL)
            {
                pHandle->tSettings.pMesCntStartCallback(pHandle, FREQM_HWA_GetRefCntSave(pFreqm));
            }
        }
        else if(u32CntStatus == (FREQM_CNT_STATUS_MES_CNT_START_MASK|FREQM_CNT_STATUS_MES_CNT_STOP_MASK) )//0x6
        {
            if (pHandle->tSettings.pMesCntStopCallback != NULL)
            {
                pHandle->tSettings.pMesCntStopCallback(pHandle, FREQM_HWA_GetRefCntSave(pFreqm));
            }
        }
        else if(u32CntStatus == (FREQM_CNT_STATUS_MES_CNT_START_MASK|FREQM_CNT_STATUS_MES_CNT_STOP_MASK|FREQM_CNT_STATUS_REF_CNT_STOP_MASK) )//0x7
        {
            if (pHandle->tSettings.pRefCntStopCallback != NULL)
            {
                pHandle->tSettings.pRefCntStopCallback(pHandle);
            }
        }
        else
        {
            if (pHandle->tSettings.pErrorCallback != NULL)
            {
                pHandle->tSettings.pErrorCallback(pHandle);
            }
        }
    }
}

#endif /* (FREQM_INSTANCE_COUNT > 0u) */
