/**
 * @file module_driver_eim.h
 * @author Flagchip100
 * @brief EIM driver type definition and API
 * @version 2.0.0
 * @date 2024-10-24
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

#ifndef _DRIVER_MODULE_DRIVER_EIM_H_
#define _DRIVER_MODULE_DRIVER_EIM_H_

#include "HwA_eim.h"

#if EIM_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_eim
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  EIM API Service IDs
 * @brief EIM API Service IDs
 *
 * @{
 */
#define EIM_INIT_ID                 0x00U
#define EIM_DEINIT_ID               0x01U
/** @}*/

/**
 * @name  EIM Dev Error Code
 * @brief Error Code of calling EIM apis
 *
 * @{
 */
#define EIM_E_PARAM_NULLPTR         0x01U
#define EIM_E_PARAM_INSTANCE        0x02U
/** @}*/

/**
 * @brief The instance index of the EIM peripheral
 *
 */
typedef enum
{
    EIM_INSTANCE_0   = 0U       /**< EIM instance 0 is selected */
} EIM_InstanceType;

/**
 * @brief EIM operation return values
 *
 */
typedef enum
{
    EIM_STATUS_SUCCESS = 0U,     /**< The EIM status success */
    EIM_STATUS_FAIL    = 1U      /**< The EIM status fail */
} EIM_StatusType;

/**
 * @brief The structure of the EIM processing handle
 *
 */
typedef struct _EIM_HandleType
{
    EIM_InstanceType eInstance; /**< EIM instance */
    uint8_t _aligned[3U];
} EIM_HandleType;

/**
 * @brief Define the max EIM channels
 *
 */
typedef struct
{
    uint32_t u32_Word0ChkVal;       /**< Data value for the first word (32-bit) */
    uint32_t u32_Word1DataVal;      /**< Data value for the second word (32-bit) */

	EIM_CHRnType eEimChannel;       /**< Type of EIM channel */
    EIM_WORD0CHRnType eWord0Ch;     /**< Configuration type for the first word in the channel */
    EIM_WORD1CHRnType eWord1Ch;     /**< Configuration type for the second word in the channel */

    uint8_t _aligned;
} EIM_ChCfgType;

/**
 * @brief Initializes the Error Injection Module(EIM) with provided configuration settings.
 *
 * This function sets up the EIM module according to the configuration specified in `pInitCfg`.
 * It configures the word channels (WORD0 and WORD1), enables the selected EIM channel, and activates
 * global error injection if supported. Error checking is performed to ensure valid pointers and EIM instance.
 *
 * @param pHandle A pointer to the EIM handle structure which identifies the EIM instance to initialize.
 * @param pInitCfg A pointer to the initialization configuration structure (`EIM_ChCfgType`) defining setup parameters for the EIM module.
 *
 * @return `EIM_STATUS_SUCCESS` if the initialization was successful, otherwise `EIM_STATUS_FAIL`.
 *
 * @note The error reporting macros are conditionally compiled based on `EIM_DEV_ERROR_REPORT` definition.
 */
EIM_StatusType EIM_Init(EIM_HandleType *const pHandle, const EIM_ChCfgType *const pInitCfg);

/**
 * @brief Deinitializes the Error Injection Module(EIM).
 *
 * This function disables the EIM module by clearing all channel configurations, disabling global error injection,
 * and resetting the word channel registers to their default state. Error checking is performed to ensure a valid EIM instance.
 *
 * @param pHandle A pointer to the EIM handle structure identifying the EIM instance to deinitialize.
 *
 * @note The error reporting macros are conditionally compiled based on `EIM_DEV_ERROR_REPORT` definition.
 */
void EIM_Deinit(EIM_HandleType *const pHandle);

#if defined(__cplusplus)
}
#endif

/** @}*/ /* module_driver_eim */

#endif

#endif
