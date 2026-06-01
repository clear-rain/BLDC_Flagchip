/**
 * @file module_driver_fwm.h
 * @author Flagchip031
 * @brief FWM driver type definition and API
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
*   2.0.0       2024-04-20    Flagchip032   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_FWM_H_
#define _DRIVER_MODULE_DRIVER_FWM_H_

#include "HwA_fwm.h"

#if FWM_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_fwm
 * @{
 */

/**
 * @name  FWM API Service IDs
 *
 * @{
 */
#define FWM_INIT_ID 0U
/** @}*/

/**
 * @name  FWM Dev Error Code
 * @brief Error Code of calling FWM apis
 *
 * @{
 */
#define FWM_E_ENABLE_ERROR           0x01U
#define FWM_E_PARAM_INVALID          0x02U
/** @}*/

/**
 * @brief FWM error status code
 *
 */
typedef enum
{
    FWM_STATUS_SUCCESS = 0U,            /**< FWM status success */
    FWM_STATUS_PARAM_INVALID = 1U,      /**< FWM status parameter invalid */
    FWM_STATUS_FUNCTION_ERROR = 2U,     /**< FWM status function error */
    FWM_STATUS_ENABLED_ERROR = 3U       /**< FWM status enabled error */
} FWM_StatusType;

/**
 * @brief The structure of the FWM processing handle
 *
 */
typedef struct _FWM_HandleType
{
    struct
    {
        void (*pResetSignalCallback)(struct _FWM_HandleType *pHandle);     /**<  The FWM ISR callback function. */
    } tSettings;
} FWM_HandleType;

/** @brief FWM init module type, include register setting
 *         for FWM_CTRL/FWM_CMPL/FWM_CMPH/FWM_CLKPRESCALER. */
typedef struct
{
    bool       bIntEn;        /**< FWM_CTRL[INTEN], Interrupt Enable        */
    bool       bInputEn;      /**< FWM_CTRL[INEN],  Input Enable            */
    bool       bInAstSel;     /**< FWM_CTRL[INASTSEL],
                                Setting the ASSIN bit inverts the assert
                                state of input signal to a logic one       */
    bool       bFwmEn;        /**< FWM_CTRL[FWMEN], Interrupt Enable, W1C   */
    uint8_t    u8CompareL;     /**< FWM_CMPL[COMPARE],  Compare low value             */
    uint8_t    u8CompareH;     /**< FWM_CMPH[COMPAREH]   Compare high value            */
    uint8_t    u8ClkDiv;       /**< FWM_CLKPRESCALER[CLK_DIV],FWM clock = SIRC frequency / ( 1 + CLK_DIV ) */
    uint8_t    reserve;
    void (*pResetSignalCallback)(FWM_HandleType *pHandle);       /**<  The FWM ISR callback function. */
} FWM_CfgType;

/**
 * @brief Refresh the watch dog by writing typical CMD1 and CM2 to Service register.
 */
void FWM_Refresh(void);

/**
 * @brief Initialize the FWM configuration setting.
 * @param pFwmHandle: FWM processing handle
 * @param pFwmCfg: point to FWM initial module type.
 * @return FWM_StatusType. Success, Parameter invalid, function error or others.
 */
FWM_StatusType FWM_Init(FWM_HandleType* pFwmHandle, const FWM_CfgType *const pFwmCfg);

/**
 * @brief Fwm interrupt process
 *
 * @param pFwmHandle: FWM processing handle
 */
void FWM_InterruptHandler(FWM_HandleType* pFwmHandle);
/** @}*/ /* module_driver_fwm */

#endif

#endif


