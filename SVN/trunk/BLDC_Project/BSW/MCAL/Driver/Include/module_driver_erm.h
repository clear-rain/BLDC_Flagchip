/**
 * @file module_driver_erm.h
 * @author Flagchip100
 * @brief ERM driver type definition and API
 * @version 2.0.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_ERM_H_
#define _DRIVER_MODULE_DRIVER_ERM_H_

#include "HwA_erm.h"

#if ERM_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_erm
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  ERM API Service IDs
 *
 * @{
 */
#define ERM_INIT_ID                 0x00U
#define ERM_GET_DEFAULT_CONFIG_ID   0x01U
#define ERM_CLEAR_STATUS_ID         0x02U
#define ERM_READ_ADDRESS_ID         0x03U

/** @}*/

/**
 * @name  ERM Dev Error Code
 * @brief Error Code of calling ERM apis
 *
 * @{
 */
#define ERM_E_PARAM_NULLPTR         0x01U
#define ERM_E_PARAM_INSTANCE        0x02U

/** @}*/

/**
 * @brief ERM error interrupt define.
 *
 * @{
 */
#define ERM_NON_CORRECTABLE_IRQ     1U      /**< select Non-correctable interrupt report */
#define ERM_SINGLE_CORRECTION_IRQ   2U      /**< select single correction interrupt report */

/** @}*/

/**
 * @brief The instance index of the ERM peripheral
 *
 */
typedef enum
{
    ERM_INSTANCE_0   = 0U           /**< ERM instance 0 is selected */
} ERM_InstanceType;

/**
 * @brief ERM operation return values
 *
 */
typedef enum
{
    ERM_STATUS_SUCCESS = 0U,        /**< The ERM status success */
    ERM_STATUS_FAIL    = 1U         /**< The ERM status fail */
} ERM_StatusType;

/**
 * @brief Define a structure for configuring ERM channels.
 * 
 */
typedef struct
{
    bool bEnable;                   /**< Indicates whether the channel is enabled or not */
    uint8_t u8IntType;              /**< Specifies the interrupt type for the channel */
    uint8_t _aligned[2U];
} ERM_ChannelCfg;

/**
 * @brief The structure of the ERM processing handle
 *
 */
typedef struct _ERM_HandleType
{
    ERM_InstanceType eInstance;     /**< CMU instance*/
    uint8_t _aligned[3];

    struct
    {
        void (*pErrorCallback)(struct _ERM_HandleType *pHandle, ERM_channelType eChannel, uint8_t u8ErrorType, uint32_t u32Addr);   /**< Error interrupt callback */
    } tSettings;
} ERM_HandleType;

typedef struct
{
    ERM_ChannelCfg tCTCMCfg;            /**< select channel CTCM  */
    ERM_ChannelCfg tDTCMCfg;            /**< select channel DTCM  */
    ERM_ChannelCfg tPFLASHfg;           /**< select channel PFLASH  */
    ERM_ChannelCfg tDMACfg;             /**< select channel DMA  */
#if (ERM_DFLASH_SUPPORT == STD_ON)
    ERM_ChannelCfg tDFLASHCfg;          /**< select channel DFLASH  */
#endif /* end for ERM_DFLASH_SUPPORT == STD_ON */
} ERM_CfgType;

/**
 * @brief Populates the ERM configuration structure with default values
 *
 * This function initializes a given ERM configuration structure with default settings for
 * various error detection and correction configurations. If the provided pointer is `NULL`,
 * an error report will be generated when error reporting is enabled.
 *
 * @param pInitCfg Pointer to an ERM configuration structure to be populated with default values
 *
 * @note Error reporting is enabled when `ERM_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void ERM_GetDefaultConfig(ERM_CfgType *const pInitCfg);

/**
 * @brief Initializes the Error Reporting Module (ERM) for the specified instance
 *
 * This function initializes the ERM module with the provided configuration structure.
 * It performs parameter validation, sets up the control register based on the configuration,
 * and clears the status. If an error occurs or the handle is invalid, an error report will
 * be generated, and the function will return a failure status.
 *
 * @param pHandle Pointer to an ERM handle structure containing the instance information
 * @param pInitCfg Pointer to an ERM configuration structure with desired settings
 *
 * @return Status of the initialization operation
 *         - ERM_STATUS_SUCCESS: Initialization successful
 *         - ERM_STATUS_FAIL: Initialization failed due to an error
 *
 * @note Error reporting is enabled when `ERM_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
ERM_StatusType ERM_Init(ERM_HandleType *const pHandle, const ERM_CfgType *const pInitCfg);

/**
 * @brief Clears the Error Reporting Module (ERM) status flags
 *
 * This function clears all status flags in the ERM module associated with the given handle's
 * instance. If an error occurs or the handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to an ERM handle structure containing the instance information
 *
 * @note Error reporting is enabled when `ERM_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void ERM_ClearStatus(ERM_HandleType *const pHandle);

/**
 * @brief Handles common Error Reporting Module (ERM) interrupts and invokes error callbacks
 *
 * This function serves as the common interrupt handler for the ERM, checking for errors in various channels
 * (CTCM, DTCM, PFLASH, optionally DFLASH, and DMA) and invoking the error callback function when an error
 * is detected. It also clears the status flags after processing the interrupts.
 *
 * @param pHandle Pointer to an ERM handle structure containing the instance information and error callback
 *
 * @note This function is designed to be used within an interrupt context.
 * @note Support for DFLASH depends on the compile-time configuration `ERM_DFLASH_SUPPORT`.
 */
void ERM_CommonIRQHandler(ERM_HandleType *const pHandle);

#if defined(__cplusplus)
}
#endif

/** @}*/ /* module_driver_erm */

#endif

#endif /* _DRIVER_MODULE_DRIVER_ERM_H_ */
