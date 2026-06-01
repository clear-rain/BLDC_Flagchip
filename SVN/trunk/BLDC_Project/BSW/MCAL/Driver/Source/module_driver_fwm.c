/**
 * @file module_driver_fwm.c
 * @author Flagchip031
 * @brief FWM driver source code
 * @version 2.0.0
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip032   N/A          First version
*********************************************************************************/

#include "module_driver_fwm.h"

#if FWM_INSTANCE_COUNT > 0U

#ifndef FWM_DEV_ERROR_REPORT
#define FWM_DEV_ERROR_REPORT    STD_OFF
#endif

#if FWM_DEV_ERROR_REPORT == STD_ON
#define FWM_ReportDevError(func, error) ReportDevError(FWM_MODULE_ID, func, error)
#endif

/**
 * @brief REFRESH CMD For FC4150.
 */
#define FWM_REFRESH_CMD1                (uint32_t)(0xFC20U)
#define FWM_REFRESH_CMD2                (uint32_t)(0x20CFU)

/**
 * @brief Refresh the watch dog by writing typical CMD1 and CM2 to Service register.
 */
void FWM_Refresh(void)
{
    FWM_HWA_SetService(FWM_REFRESH_CMD1);
    FWM_HWA_SetService(FWM_REFRESH_CMD2);
}

/**
 * @brief Initialize the FWM configuration setting.
 * @param pFwmHandle: FWM processing handle
 * @param pFwmCfg: point to FWM initial module type.
 * @return FWM_StatusType. Success, Parameter invalid, function error or others.
 */
FWM_StatusType FWM_Init(FWM_HandleType* pFwmHandle, const FWM_CfgType *const pFwmCfg)
{
    FWM_StatusType eStatus = FWM_STATUS_ENABLED_ERROR;
    uint32_t u32Temp = 0U;
#if FWM_DEV_ERROR_REPORT == STD_ON
    if (GetFwmEnableStatus() == true)
    {
        eStatus = FWM_STATUS_ENABLED_ERROR;
        FWM_ReportDevError(FWM_INIT_ID, FWM_E_ENABLE_ERROR);
    }
    else if ((pFwmCfg->u8CompareL > pFwmCfg->u8CompareH) || ((pFwmCfg->bInputEn == false) && (pFwmCfg->bInAstSel == true)))
    {
        eStatus = FWM_STATUS_PARAM_INVALID;
        FWM_ReportDevError(FWM_INIT_ID, FWM_E_PARAM_INVALID);
    }
    else
    {
#endif
        /*     Set clock divider    */
        FWM_HWA_SetClkPrescaler(FWM_CLKPRESCALER_CLK_DIV(pFwmCfg->u8ClkDiv));

        /*     Set FWM compare H and L value   */
        FWM_HWA_SetCmpL(FWM_CMPL_COMPAREL(pFwmCfg->u8CompareL));
        FWM_HWA_SetCmpH(FWM_CMPH_COMPAREH(pFwmCfg->u8CompareH));

        /*     Set FWM control value   */
        u32Temp = FWM_HWA_GetCtrl();
        u32Temp &= ~(uint32_t)FWM_CTRL_MASK;

        u32Temp = (uint32_t)(FWM_CTRL_INTEN(pFwmCfg->bIntEn) | FWM_CTRL_INEN(pFwmCfg->bInputEn) |
                             FWM_CTRL_INASTSEL(pFwmCfg->bInAstSel) | FWM_CTRL_FWMEN(pFwmCfg->bFwmEn));
        FWM_HWA_SetCtrl(u32Temp);

        pFwmHandle->tSettings.pResetSignalCallback = pFwmCfg->pResetSignalCallback;

        eStatus = FWM_STATUS_SUCCESS;
#if FWM_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eStatus;
}

/**
 * @brief Fwm interrupt process
 *
 * @param pFwmHandle: FWM processing handle
 */
void FWM_InterruptHandler(FWM_HandleType* pFwmHandle)
{
    if(NULL != pFwmHandle->tSettings.pResetSignalCallback)
    {
        pFwmHandle->tSettings.pResetSignalCallback(pFwmHandle);
    }
}

#endif

