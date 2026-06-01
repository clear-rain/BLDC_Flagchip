/**
 * @file module_driver_cmu.c
 * @author Flagchip032
 * @brief SMC driver source code
 * @version 2.0.0
 * @date 2024-08-11
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip031   N/A          First version
*********************************************************************************/

#include "module_driver_cmu.h"

#if CMU_INSTANCE_COUNT > 0U

#include "module_driver_scg.h"
#include "module_driver_smisc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef CMU_DEV_ERROR_REPORT
#define CMU_DEV_ERROR_REPORT    STD_OFF
#endif

#if CMU_DEV_ERROR_REPORT == STD_ON
#define CMU_ReportDevError(func, error)     ReportDevError(CMU_MODULE_ID, func, error)
#endif

#define CMU_MULTIPLY_FACTOR     100U
#define CMU_PERCENT_FACTOR      100U
#define CMU_DIVID_FACTOR_1K     1000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static CMU_InterruptType CMU_GetInterruptType(CMU_HandleType *const pHandle);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static CMU_Type *const s_apCmuBase[CMU_INSTANCE_COUNT] = CMU_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Initializes a CMU configuration structure with default values
 *
 * This function configures the provided CMU configuration structure with a set of default settings,
 * including interrupt enable, low-power mode, clock divider, and more. If the passed configuration
 * structure pointer is NULL and error reporting is enabled, an error will be reported.
 *
 * @param pInitCfg Pointer to a CMU_CfgType structure that will be initialized with default configuration values
 *
 * @note The function checks for NULL pointer only if error reporting (`CMU_DEV_ERROR_REPORT`) is turned on.
 *       By default, it sets the structure fields to:
 *       - Interrupt Enable: true
 *       - Low Power Enable: false
 *       - Clock Monitor Enable: false
 *       - Module Enable: true
 *       - Peripheral Monitor Enable: false
 *       - Clock Divider: CMU_REFCLK_NODIV
 *       - Error Callback: NULL
 */
void CMU_GetDefaultConfig(CMU_CfgType *const pInitCfg)
{
#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        CMU_ReportDevError(CMU_GET_DEFAULT_CONFIG_ID, CMU_E_PARAM_NULLPTR);
    }
    else
#endif
    {
        pInitCfg->bIntEnable          = true;
        pInitCfg->bLpen               = false;
        pInitCfg->bSten               = false;
        pInitCfg->bEnable             = true;
        pInitCfg->bPerMonitorEnable   = false;
        pInitCfg->eDiv                = CMU_REFCLK_NODIV;
    }
}

/**
 * @brief Calculates monitor window values for the CMU based on the given configuration
 *
 * This function calculates the reference and monitor clock window values for the specified CMU instance.
 * It verifies input parameters, checks the clock status, and performs necessary calculations.
 * If any input is invalid or an error occurs, appropriate error reporting may be triggered.
 *
 * @param pInitCfg Pointer to a CMU configuration structure with user-defined settings
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void CMU_CaculateMonitorWindowsValue(CMU_CfgType *const pInitCfg)
{
#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        CMU_ReportDevError(CMU_CAL_MONITOR_WINDOW_ID, CMU_E_PARAM_NULLPTR);
    }
    else
#endif
    {
        uint32_t u32RefWindow, u32MaxRefWindow, u32MinRefWindow;
        uint32_t u32MonitorCnts, u32MinMonitorCnts, u32MaxMonitorCnts;
        uint32_t u32RefClk, u32MonitorClk;
        uint32_t u32MaxPeriod;

        /* divide the clock value by 1K_factor */
        u32RefClk = (pInitCfg->u32RefClk >> pInitCfg->eDiv) / CMU_DIVID_FACTOR_1K;
        u32MonitorClk = pInitCfg->u32MonitorClk / CMU_DIVID_FACTOR_1K;

        if ((u32RefClk != 0U) && (u32MonitorClk != 0U))
        {
            if (u32RefClk / u32MonitorClk <= 0x100U)
            {
                u32MaxRefWindow = (0xffffffU - 3U) / u32MonitorClk * u32RefClk / 105U * CMU_PERCENT_FACTOR - 2U;

                if (u32MaxRefWindow > 0xffffffU)
                {
                    u32MaxRefWindow = 0xffffffU;
                }
            }
            else
            {
                u32MaxRefWindow = 0xffffffU;
            }

            u32MinRefWindow = 6U + 5U * u32RefClk / u32MonitorClk;
            u32RefWindow = 100U * u32MinRefWindow;

            if (u32RefWindow > u32MaxRefWindow)
            {
                u32RefWindow = u32MaxRefWindow;
            }

            u32MonitorCnts = u32MonitorClk * (u32RefWindow + 2U) / u32RefClk;
            u32MinMonitorCnts = u32MonitorCnts * 95U / CMU_PERCENT_FACTOR - 3U;
            u32MaxMonitorCnts = u32MonitorCnts * 105U / CMU_PERCENT_FACTOR + 3U;

            /* Program program PERIOD[EN] and PERIOD[WINDOW]. */
            u32MaxPeriod = u32RefClk / u32RefWindow;

            if (u32MaxPeriod >> CMU_PERIOD_WINDOW_WIDTH)
            {
                u32MaxPeriod = (1U << CMU_PERIOD_WINDOW_WIDTH) - 1U;
            }

            pInitCfg->u32RefWindow        = u32RefWindow;
            pInitCfg->u32PerMonitorWindow = u32MaxPeriod;
            pInitCfg->u32MinMonitorCnts   = u32MinMonitorCnts;
            pInitCfg->u32MaxMonitorCnts   = u32MaxMonitorCnts;
        }
        else
        {
            pInitCfg->bIntEnable          = false;
            pInitCfg->bLpen               = false;
            pInitCfg->bSten               = false;
            pInitCfg->bEnable             = false;
            pInitCfg->bPerMonitorEnable   = false;
            pInitCfg->u32RefWindow        = 0;
            pInitCfg->u32PerMonitorWindow = 0;
            pInitCfg->u32MinMonitorCnts   = 0;
            pInitCfg->u32MaxMonitorCnts   = 0;
        }
    }
}

/**
 * @brief Initializes the CMU module with the provided configuration
 *
 * This function initializes the Clock Monitor Unit (CMU) according to the specified configuration.
 * It performs parameter validation, initializes hardware registers, and sets up callback functions.
 * If any input is invalid, an error will be reported and the function will return `CMU_STATUS_FAIL`.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 * @param pInitCfg Pointer to a constant CMU configuration structure with initialization settings
 *
 * @return Status of the initialization process
 *         - CMU_STATUS_SUCCESS: Initialization successful
 *         - CMU_STATUS_FAIL: Initialization failed due to an error or invalid parameter
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
CMU_StatusType CMU_Init(CMU_HandleType *const pHandle, const CMU_CfgType *const pInitCfg)
{
    CMU_StatusType eStatus = CMU_STATUS_SUCCESS;

#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        CMU_ReportDevError(CMU_INIT_ID, CMU_E_PARAM_NULLPTR);
        eStatus = CMU_STATUS_FAIL;
    }
    else if (pInitCfg == NULL)
    {
        CMU_ReportDevError(CMU_INIT_ID, CMU_E_PARAM_NULLPTR);
        eStatus = CMU_STATUS_FAIL;
    }
    else if (pHandle->eInstance >= CMU_INSTANCE_COUNT)
    {
        CMU_ReportDevError(CMU_INIT_ID, CMU_E_PARAM_INSTANCE);
        eStatus = CMU_STATUS_FAIL;
    }
    else
#endif
    {
        CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];
        uint32_t u32Temp = 0x1FF;

        CMU_HWA_SETCTRL(pCmu, 0);
        CMU_HWA_SoftwareRST(pCmu);
        /* wait for rst complete */
        while (CMU_HWA_GetSoftwareRST(pCmu))
        {
            u32Temp--;
            if (u32Temp == 0)
            {
                eStatus = CMU_STATUS_FAIL;
                break;
            }
        }

        if (u32Temp != 0)
        {
            CMU_HWA_SetRefWindow(pCmu, pInitCfg->u32RefWindow);
            CMU_HWA_SetMinCnts(pCmu, pInitCfg->u32MinMonitorCnts);
            CMU_HWA_SetMaxCnts(pCmu, pInitCfg->u32MaxMonitorCnts);
            CMU_HWA_SetPeriodWindow(pCmu, pInitCfg->u32PerMonitorWindow);
            CMU_HWA_SetPeriodEnable(pCmu, pInitCfg->bPerMonitorEnable);

            /* Program DIV,IRQ_EN,LP_EN,STOP_EN,ENABLE */
            u32Temp = CMU_CTRL_REF_DIV(pInitCfg->eDiv) | \
                      CMU_CTRL_IRQ_EN(pInitCfg->bIntEnable) | \
                      CMU_CTRL_LP_EN(pInitCfg->bLpen) | \
                      CMU_CTRL_STOP_EN(pInitCfg->bSten) | \
                      CMU_CTRL_ENABLE(pInitCfg->bEnable);
            CMU_HWA_SETCTRL(pCmu, u32Temp);
            CMU_HWA_ClsST(pCmu);
        }
    }

    return eStatus;
}

/**
 * @brief Enables the Clock Monitor Unit (CMU) for the specified instance
 *
 * This function enables the CMU module for the given handle's instance. It performs parameter
 * validation and updates the control register to activate the CMU. If an error occurs or the
 * handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void CMU_Enable(CMU_HandleType *const pHandle)
{
#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        CMU_ReportDevError(CMU_ENABLE_ID, CMU_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= CMU_INSTANCE_COUNT)
    {
        CMU_ReportDevError(CMU_ENABLE_ID, CMU_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        uint32_t u32Temp;
        CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];

        u32Temp = CMU_HWA_GetCTRL(pCmu);
        u32Temp |= CMU_CTRL_ENABLE_MASK;
        CMU_HWA_SETCTRL(pCmu, u32Temp);
    }
}

/**
 * @brief Disables the Clock Monitor Unit (CMU) for the specified instance
 *
 * This function disables the CMU module for the given handle's instance. It performs parameter
 * validation, clears the control register flags for enabling and interrupts, and resets the
 * status. If an error occurs or the handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void CMU_Disable(CMU_HandleType *const pHandle)
{
#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        CMU_ReportDevError(CMU_DISABLE_ID, CMU_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= CMU_INSTANCE_COUNT)
    {
        CMU_ReportDevError(CMU_DISABLE_ID, CMU_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        uint32_t u32Temp;
        CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];

        u32Temp = CMU_HWA_GetCTRL(pCmu);
        u32Temp &= ~(CMU_CTRL_ENABLE_MASK | CMU_CTRL_IRQ_EN_MASK);
        CMU_HWA_SETCTRL(pCmu, u32Temp);
        CMU_HWA_ClsST(pCmu);
    }
}

/**
 * @brief Enables the Clock Monitor Unit (CMU) interrupt for the specified instance
 *
 * This function enables the interrupt for the CMU module associated with the given handle's instance.
 * It performs parameter validation and updates the control register to enable the interrupt.
 * If an error occurs or the handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void CMU_EnableInterrupt(CMU_HandleType *const pHandle)
{
#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        CMU_ReportDevError(CMU_ENABLE_IRQ_ID, CMU_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= CMU_INSTANCE_COUNT)
    {
        CMU_ReportDevError(CMU_ENABLE_IRQ_ID, CMU_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        uint32_t u32Temp;
        CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];

        u32Temp = CMU_HWA_GetCTRL(pCmu);
        u32Temp |= CMU_CTRL_IRQ_EN_MASK;
        CMU_HWA_SETCTRL(pCmu, u32Temp);
    }
}

/**
 * @brief Disables the Clock Monitor Unit (CMU) interrupt for the specified instance
 *
 * This function disables the interrupt for the CMU module associated with the given handle's instance.
 * It performs parameter validation and updates the control register to disable the interrupt.
 * If an error occurs or the handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void CMU_DisableInterrupt(CMU_HandleType *const pHandle)
{
#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        CMU_ReportDevError(CMU_DISABLE_IRQ_ID, CMU_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= CMU_INSTANCE_COUNT)
    {
        CMU_ReportDevError(CMU_DISABLE_IRQ_ID, CMU_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        uint32_t u32Temp;
        CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];

        u32Temp = CMU_HWA_GetCTRL(pCmu);
        u32Temp &= ~CMU_CTRL_IRQ_EN_MASK;
        CMU_HWA_SETCTRL(pCmu, u32Temp);
    }
}

/**
 * @brief Enables or disables the specified low-power mode for the Clock Monitor Unit (CMU)
 *
 * This function allows enabling or disabling either the standby or stop mode for the CMU instance
 * associated with the given handle. It performs parameter validation and configures the CMU hardware
 * accordingly. If an error occurs or the handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 * @param eMode Enumerated type specifying the low-power mode to be controlled
 * @param bModeEnable Boolean indicating whether to enable (true) or disable (false) the mode
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void CMU_LowPowerModeEnable(CMU_HandleType *const pHandle, CMU_LowpowerModeType eMode, bool bModeEnable)
{
#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        CMU_ReportDevError(CMU_ENABLE_LOWPOWER_MODE_ID, CMU_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= CMU_INSTANCE_COUNT)
    {
        CMU_ReportDevError(CMU_ENABLE_LOWPOWER_MODE_ID, CMU_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];

        if (eMode == CMU_STANDBY_MODE)
        {
            CMU_HWA_StopModeEnable(pCmu, bModeEnable);
            CMU_HWA_StanbyModeEnable(pCmu, bModeEnable);
        }
        else if (eMode == CMU_STOP_MODE)
        {
            CMU_HWA_StopModeEnable(pCmu, bModeEnable);
        }
        else
        {

        }
    }
}

/**
 * @brief Retrieves the current Clock Monitor Unit (CMU) interrupt type for the specified instance
 *
 * This function reads the status register of the CMU module associated with the given handle's instance
 * and returns the active interrupt type. If an error occurs or the handle is invalid, an error
 * report will be generated, and `CMU_INTERRUPT_NONE` will be returned.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 *
 * @return Interrupt type of the CMU
 *         - CMU_INTERRUPT_NONE: No interrupt is active
 *         - CMU_INTERRUPT_LOC: Location interrupt is active
 *         - CMU_INTERRUPT_MIS: Missed interrupt is active
 *
 * @note Error reporting is enabled when `CMU_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
static CMU_InterruptType CMU_GetInterruptType(CMU_HandleType *const pHandle)
{
    CMU_InterruptType eStatus = CMU_INTERRUPT_NONE;

#if CMU_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        CMU_ReportDevError(CMU_GET_IRQ_TYPE_ID, CMU_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= CMU_INSTANCE_COUNT)
    {
        CMU_ReportDevError(CMU_GET_IRQ_TYPE_ID, CMU_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        uint32_t u32Temp;
        CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];

        u32Temp = CMU_HWA_GetST(pCmu);
        if ((u32Temp & CMU_ST_LOC_MASK) != 0U)
        {
            eStatus = CMU_INTERRUPT_LOC;
        }
        else if ((u32Temp & CMU_ST_MIS_MASK) != 0U)
        {
            eStatus = CMU_INTERRUPT_MIS;
        }
        else
        {

        }
    }

    return eStatus;
}

/**
 * @brief Common Clock Monitor Unit (CMU) Interrupt Service Routine (ISR)
 *
 * This ISR handles common interrupt scenarios for the CMU module associated with the given handle.
 * It retrieves the current interrupt status, performs error handling as needed, and calls
 * the registered error callback function if present. Additionally, it addresses a specific
 * hardware erratum (ERR_CMU_001). After processing, the ISR clears the status flags.
 *
 * @param pHandle Pointer to a CMU handle structure containing the instance information
 *
 * @note This function assumes that the CMU interrupt has already occurred and is being serviced.
 * @note Error reporting and handling are performed based on the interrupt status.
 */
void CMU_CommonIRQHandler(CMU_HandleType *const pHandle)
{
    CMU_InterruptType eStatus;
    CMU_Type *const pCmu = s_apCmuBase[pHandle->eInstance];
    uint32_t u32Count;

    eStatus = CMU_GetInterruptType(pHandle);

    /*Errata: ERR_CMU_001*/
    if (eStatus == CMU_INTERRUPT_NONE && CMU_HWA_GetPeriodEnable(pCmu))
    {
        if (CMU_INSTANCE_0 == pHandle->eInstance)
        {
            u32Count = 0x1FFU;
        }
        else
        {
            u32Count = 0x1FU;
        }
        CMU_HWA_SoftwareRST(pCmu);
        while (CMU_HWA_GetSoftwareRST(pCmu))
        {
            u32Count--;
            if (u32Count == 0)
            {
                break;
            }
        }

        if (u32Count == 0)
        {
            eStatus = CMU_INTERRUPT_LOC;
        }
        else
        {
            eStatus = CMU_INTERRUPT_MIS;
        }
    }

    if (pHandle->tSettings.pErrorCallback != NULL)
    {
        pHandle->tSettings.pErrorCallback(pHandle, eStatus);
    }

    CMU_HWA_ClsST(pCmu);
}

#endif

