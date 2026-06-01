/**
 * @file module_driver_wku.h
 * @author Flagchip032
 * @brief WKU driver type definition and API
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
#ifndef _DRIVER_MODULE_DRIVER_WKU_H_
#define _DRIVER_MODULE_DRIVER_WKU_H_

#include "HwA_wku.h"

#if WKU_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_wku
 * @{
 */

/** @brief WKU return type. */
typedef enum
{
    WKU_STATUS_SUCCESS = 0U,
    WKU_STATUS_PARAM_INVALID = 1U
} WKU_StatusType;

/**
 * @brief WKU Enable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_EnableWakeupSource(const uint32_t u32Input);

/**
 * @brief WKU Disable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_DisableWakeupSource(const uint32_t u32Input);

/**
 * @brief WKU get wakeup source
 *
 * @return output wakeup source
 */
uint32_t WKU_GetWakeupSources(void);

/** @}*/ /* module_driver_wku */

#endif

#endif
