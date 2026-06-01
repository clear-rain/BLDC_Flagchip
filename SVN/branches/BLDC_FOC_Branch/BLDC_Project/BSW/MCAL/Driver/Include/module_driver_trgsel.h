/**
 * @file module_driver_trgsel.h
 * @author Flagchip103
 * @brief TRGSEL driver type definition and API
 * @version 2.0.0
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 * 
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip103   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_TRGSEL_H_
#define _DRIVER_MODULE_DRIVER_TRGSEL_H_

#include "device_header.h"

#if TRGSEL_INSTANCE_COUNT > 0U
/**
 *
 * @addtogroup module_driver_trgsel
 * @{
 */
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  TRGSEL API Service IDs
 * @brief Service for det error report
 * @{
 */
#define TRGSEL_GET_TARGET_TRIGGER_SOURCE_ID 	   0U
#define TRGSEL_SET_TARGET_TRIGGER_SOURCE_ID        1U
#define TRGSEL_GET_TARGET_LOCK_STATUS_ID           2U
#define TRGSEL_LOCK_TARGET_TRIGGER_SOURCE_ID       3U
#define TRGSEL_GENERATE_SW_TRIGGER_ID              4U

/** @}*/

/**
 * @name  TRGSEL Dev Error Code
 * @brief Error Code of calling TRGSEL apis
 *
 * @{
 */
#define TRGSEL_E_PARAM_INSTANCE_NUMBER  		    0x01U
#define TRGSEL_E_INVALID_TARGET  		            0x02U
#define TRGSEL_E_INVALID_SOURCE  		            0x03U
#define TRGSEL_E_TARGET_LOCKED  		            0x04U
#define TRGSEL_E_INVALID_SW_TRIGGIER                0x05U
/** @}*/

/**
 * @name TrgSel typedefs
 * @brief TrgSel trigger targets
 * @{
 */
typedef uint32_t TRGSEL_TargetType;

/**
 * @brief TrgSel trigger sources
 * 
 */
typedef uint32_t TRGSEL_SourceType;
/** @}*/



/**
 * @name  TRGSEL_InstanceType
 * @brief The TrgSel eInstance to select
 * @{
 */
typedef enum{
    TRGSEL_INSTANCE_0 = 0U,
    TRGSEL_INSTANCE_1 = 1U,
    TRGSEL_INSTANCE_2 = 2U,
    TRGSEL_INSTANCE_3 = 3U
} TRGSEL_InstanceType;
/** @}*/

/**
 * @name TRGSEL_SwTriggerChannelType
 * @brief Software trigger channels for SMISC software trigger channel 0~7
 * @{
 */
typedef enum
{
    TRGSEL_SW_TRIGGER_CHANNEL_0  = 0U,
    TRGSEL_SW_TRIGGER_CHANNEL_1  = 1U,
    TRGSEL_SW_TRIGGER_CHANNEL_2  = 2U,
    TRGSEL_SW_TRIGGER_CHANNEL_3  = 3U,
    TRGSEL_SW_TRIGGER_CHANNEL_4  = 4U,
    TRGSEL_SW_TRIGGER_CHANNEL_5  = 5U,
    TRGSEL_SW_TRIGGER_CHANNEL_6  = 6U,
    TRGSEL_SW_TRIGGER_CHANNEL_7  = 7U
} TRGSEL_SwTriggerChannelType;
/** @}*/

/**
 * @name TRGSEL APIs
 * @brief Get the trigger source of the selected trigger eTarget
 *
 * @param eInstance the TrgSel instance to which the trigger target belongs
 * @param eTarget the trigger target to get the trigger source
 * @return TRGSEL_SourceType the trigger source of the selected trigger target
 * @{
 */
TRGSEL_SourceType TRGSEL_GetTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget);

/**
 * @brief Set the trigger source of the selected trigger target
 *
 * @param eInstance the TrgSel instance to which the trigger target belongs
 * @param eTarget the trigger target to set the trigger source
 * @param eSource the selected trigger source to trig the target
 */
void TRGSEL_SetTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget,
                                   const TRGSEL_SourceType eSource);

/**
 * @brief Get wether the trigger source of the selected target is locked
 *
 * @param eInstance the TrgSel instance to which the trigger target belongs
 * @param eTarget the trigger target to get the lock status
 * @return true the trigger source of the selected target cannot be modified
 * @return false the trigger source of the selected target can be modified
 */
bool TRGSEL_GetTargetLockStatus(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget);

/**
 * @brief Lock the trigger source of the selected target
 *
 * @note The trigger target is grouped by four, so if you lock the trigger source of one target, the
 * adjacent three trigger targets in the same register group are also be locked. So please ensure the
 * trigger sources are not to be modified before lock the trigger target.
 *
 * @param eInstance the TrgSel instance to which the trigger target belongs
 * @param eTarget the trigger target to lock the trigger source
 */
void TRGSEL_LockTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget);

/**
 * @brief Generate trigger signal for the selected software trigger source channel
 * 
 * @param eChannel the selected software trigger source channel
 */
void TRGSEL_GenerateSwTrigger(const TRGSEL_SwTriggerChannelType eChannel);
/** @}*/

#if defined(__cplusplus)
}
#endif
/** @}*/
#endif

#endif
