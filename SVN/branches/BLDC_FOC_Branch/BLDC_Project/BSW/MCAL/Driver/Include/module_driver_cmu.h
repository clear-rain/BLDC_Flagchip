/**
 * @file module_driver_cmu.h
 * @author Flagchip100
 * @brief CMU driver type definition and API
 * @version 2.0.0
 * @date 2024-04-19
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_CMU_H_
#define _DRIVER_MODULE_DRIVER_CMU_H_

#include "HwA_cmu.h"

#if CMU_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_cmu
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  CMU API Service IDs
 *
 * @{
 */
#define CMU_INIT_ID                 0x00U
#define CMU_GET_DEFAULT_CONFIG_ID   0x01U
#define CMU_ENABLE_ID               0x02U
#define CMU_DISABLE_ID              0x03U
#define CMU_ENABLE_IRQ_ID           0x04U
#define CMU_DISABLE_IRQ_ID          0x05U
#define CMU_GET_IRQ_TYPE_ID         0x06U
#define CMU_ENABLE_LOWPOWER_MODE_ID 0x07U
#define CMU_CAL_MONITOR_WINDOW_ID   0x08U

/** @}*/

/**
 * @name  CMU Dev Error Code
 * @brief Error Code of calling CMU apis
 *
 * @{
 */
#define CMU_E_PARAM_NULLPTR         0x01U
#define CMU_E_PARAM_INSTANCE        0x02U

/** @}*/

/** 
 * @brief The instance index of the CMU peripheral
 * 
 */
typedef enum
{
    CMU_INSTANCE_0   = 0U,  /**< CMU instance 0 is selected */
    CMU_INSTANCE_1   = 1U,  /**< CMU instance 1 is selected */
    CMU_INSTANCE_2   = 2U,  /**< CMU instance 2 is selected */
    CMU_INSTANCE_3   = 3U   /**< CMU instance 3 is selected */
} CMU_InstanceType;

/**
 * @brief CMU operation return values
 *
 */
typedef enum
{
    CMU_STATUS_SUCCESS  = 0x0U,         /**< The CMU status success */
    CMU_STATUS_FAIL     = 0x1U          /**< The CMU status fail */
} CMU_StatusType;

/**
 * @brief CMU Lowpower Mode type
 *
 */
typedef enum
{
    CMU_STOP_MODE       = 0U,           /**< CMU enable in Stop Mode */
    CMU_STANDBY_MODE    = 1U            /**< CMU enable in Standby Mode */
} CMU_LowpowerModeType;

/**
 * @brief CMU interrupt mode type
 *
 */
typedef enum
{
    CMU_INTERRUPT_NONE  = 0U,           /**< No CMU interrupt */
    CMU_INTERRUPT_LOC   = 1U,           /**< CMU_ST[LOC] bit, Monitor clock is loss */
    CMU_INTERRUPT_MIS   = 2U            /**< CMU_ST[MIS] bit, Monitor clock is mismatched */
} CMU_InterruptType;

/**
 * @brief CMU Reference clock div type
 * 
 */
typedef enum
{
    CMU_REFCLK_NODIV      = 0U,         /**< Clock output is disabled */
    CMU_REFCLK_DIV_BY2    = 1U,         /**< Divided by 2 */
    CMU_REFCLK_DIV_BY4    = 2U,         /**< Divided by 4 */
    CMU_REFCLK_DIV_BY8    = 3U,         /**< Divided by 8 */
    CMU_REFCLK_DIV_BY16   = 4U,         /**< Divided by 16 */
    CMU_REFCLK_DIV_BY32   = 5U,         /**< Divided by 32 */
    CMU_REFCLK_DIV_BY64   = 6U,         /**< Divided by 64 */
    CMU_REFCLK_DIV_BY128  = 7U          /**< Divided by 128 */
} CMU_RefClockDivType;

/**
 * @brief The structure of the CMU processing handle
 *
 * Implements : _CMU_HandleType
 */
typedef struct _CMU_HandleType
{
    CMU_InstanceType eInstance;         /**< CMU instance */
    uint8_t _aligned[3U];

    struct
    {
        void (*pErrorCallback)(struct _CMU_HandleType *pHandle, const CMU_InterruptType eStatus);   /**< Error interrupt callback */
    } tSettings;
} CMU_HandleType;

/**
 * @brief CMU configure structure
 *
 * Implements : CMU_CfgType
 */
typedef struct
{
    uint32_t u32RefClk;                 /**< The reference clock frequency */
    uint32_t u32MonitorClk;             /**< The monitor clock frequency */
    uint32_t u32RefWindow;              /**< CMU_REF_WINDOW[REF_WINDOW] bits, The sample window for the reference clock */
    uint32_t u32MinMonitorCnts;         /**< CMU_MIN[MIN] bits, The minimum threshold for the monitor counter */
    uint32_t u32MaxMonitorCnts;         /**< CMU_MAX[MAX] bits, The maximum threshold for the monitor counter */
    uint32_t u32PerMonitorWindow;       /**< CMU_PERIOD[WINDOW] bits, Period Monitor mode WIDOW */
    bool bIntEnable;                    /**< CMU_CTRL[IRQ_EN] bit, interrupt enable, if this bit asserted, either LOC or MIS asserted can lead the interrupt */
    bool bLpen;                         /**< CMU_CTRL[LP_EN] bit, standby mode enable, need STOP_EN asserted */
    bool bSten;                         /**< CMU_CTRL[STOP_EN] bit, stop mode enable */
    bool bEnable;                       /**< CMU_CTRL[EN] bit, cmu enable */
    bool bPerMonitorEnable;             /**< CMU_PERIOD[EN] bit, Period Monitor mode ENABLE */
    CMU_RefClockDivType eDiv;           /**< Divider of reference clock */
    uint8_t _aligned[2];
} CMU_CfgType;

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
void CMU_GetDefaultConfig(CMU_CfgType *const pInitCfg);

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
void CMU_CaculateMonitorWindowsValue(CMU_CfgType *const pInitCfg);

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
CMU_StatusType CMU_Init(CMU_HandleType *const pHandle, const CMU_CfgType *const pInitCfg);

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
void CMU_Enable(CMU_HandleType *const pHandle);

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
void CMU_Disable(CMU_HandleType *const pHandle);

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
void CMU_EnableInterrupt(CMU_HandleType *const pHandle);

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
void CMU_DisableInterrupt(CMU_HandleType *const pHandle);

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
void CMU_LowPowerModeEnable(CMU_HandleType *const pHandle, CMU_LowpowerModeType eMode, bool bModeEnable);

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
void CMU_CommonIRQHandler(CMU_HandleType *const pHandle);

#if defined(__cplusplus)
}
#endif

/** @}*/ /* module_driver_cmu */

#endif

#endif
