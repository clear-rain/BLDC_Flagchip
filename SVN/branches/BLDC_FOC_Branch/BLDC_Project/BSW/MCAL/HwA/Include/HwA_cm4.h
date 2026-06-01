/**
 * @file HwA_cm4.h
 * @author Flagchip
 * @brief CORTEX-M4 hardware access layer
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/

#ifndef _HWA_CM4_H_
#define _HWA_CM4_H_

#include "device_header.h"

/**
 * @defgroup HwA_cm4 HwA_cm4
 * @ingroup module_driver_wku
 * @{
 */

/**
 * @brief Enable deepsleep mode
 *
 */
LOCAL_INLINE void CM4_HWA_EnableDeepSleep(void)
{
    SCB->SCR |= (uint32_t)SCB_SCR_SLEEPDEEP_Msk;
}

/**
 * @brief Disable deepsleep mode
 *
 */
LOCAL_INLINE void CM4_HWA_DisableDeepSleep(void)
{
    SCB->SCR &= ~(uint32_t)SCB_SCR_SLEEPDEEP_Msk;
}

/** @}*/


#endif /* #ifndef _HWA_CM4_H_ */
