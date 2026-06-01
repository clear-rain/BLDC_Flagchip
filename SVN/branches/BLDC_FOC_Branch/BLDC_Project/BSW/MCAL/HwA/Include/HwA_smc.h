/**
 * @file HwA_smc.h
 * @author Flagchip032
 * @brief SMC hardware access layer
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
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/

#ifndef _HWA_SMC_H_
#define _HWA_SMC_H_

#include "device_header.h"

#if SMC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_smc HwA_smc
 * @ingroup module_driver_smc
 * @{
 */

/********* Local typedef ************/
/** @brief SMC stop mode control */
typedef enum
{
    SMC_STOP_MODE = 0U,   /**< Stop mode */
    SMC_STANDBY_MODE = 4U /**< Standby mode */
} SMC_StopModeCtrlType;

/** @brief SMC standby mode */
typedef enum
{
    SMC_CFG_STANDBY_0 = 0U,  /**< Standby mode 0 */
    SMC_CFG_STANDBY_1 = 1U,  /**< Standby mode 1 */
    SMC_CFG_STANDBY_2 = 2U,  /**< Standby mode 2 */
    SMC_CFG_STANDBY_3 = 3U   /**< Standby mode 3 */
} SMC_StandbyModeType;

/********* Local inline function ************/
/**
 * @brief Clear stop mode control value
 *
 */
LOCAL_INLINE void SMC_HWA_ClearStopModeCtrl(void)
{
    SMC->PMCTRL &= ~(uint32_t)SMC_PMCTRL_STOP_MODE_MASK;
}

/**
 * @brief Set stop mode control
 *
 * @param eMode Stop mode control type
 */
LOCAL_INLINE void SMC_HWA_SetStopModeCtrl(SMC_StopModeCtrlType eMode)
{
    SMC->PMCTRL = (uint32_t)eMode;
}

/**
 * @brief Clear standby mode
 *
 */
LOCAL_INLINE void SMC_HWA_ClearStandbyMode(void)
{
    SMC->STANDBY_CFG &= ~(uint32_t)SMC_STANDBY_CFG_OPTION_MASK;
}

/**
 * @brief Set standby mode
 *
 * @param eMode Standby mode type
 */
LOCAL_INLINE void SMC_HWA_SetStandbyMode(SMC_StandbyModeType eMode)
{
    SMC->STANDBY_CFG = (uint32_t)eMode;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_SMC_H_ */
