/**
 * @file module_driver_smc.h
 * @author Flagchip032
 * @brief SMC driver type definition and API
 * @version 2.0.0
 * @date 2024-11-10
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip032   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_SMC_H_
#define _DRIVER_MODULE_DRIVER_SMC_H_

#include "HwA_smc.h"

#if SMC_INSTANCE_COUNT > 0U

#include "HwA_pmc.h"
#include "HwA_cm4.h"
/**
 * @addtogroup module_driver_smc
 * @{
 */

/**
 * @name  PMC mode max ID
 *
 * @{
 */
#define SMC_MODE_MAX_ID         6U
/** @}*/

/** @brief Smc return type. */
typedef enum
{
    SMC_STATUS_SUCCESS = 0U,        /**< Status Success */
    SMC_STATUS_PARAM_INVALID = 1U   /**< Status Parameter invalid */
} SMC_StatusType;

/** @brief Smc mode */
typedef enum
{
    SMC_MODE_RUN = 0U,         /**< The MCU can run at full speed and the internal supply is fully regulated, that is, in run regulation */
    SMC_MODE_STOP,             /**< Core enters sleep mode and no other clock is gated. Only the core clock is gated. */
    SMC_MODE_WAIT,             /**< Both core and bus clocks are gated off. */
    SMC_MODE_STANBY_0,         /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 0. */
    SMC_MODE_STANBY_1,         /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 1. */
    SMC_MODE_STANBY_2,         /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 2. */
    SMC_MODE_STANBY_3          /**< All clocks except some low-power clocks can keep on are gated off and the PD1 domain is powered off. please refer to reference manual for detail about standby mode 3. */
} SMC_ModeType;

/* global functions */
/**
 * @brief Set system mode
 *
 * @param eMode Smc configuration structure
 * @return Smc return type
 */
SMC_StatusType SMC_SetSystemMode(SMC_ModeType eMode);


/** @}*/ /* module_driver_smc */

#endif

#endif
