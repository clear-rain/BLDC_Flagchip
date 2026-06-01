/**
 * @file HwA_wku.h
 * @author Flagchip032
 * @brief WKU hardware access layer
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

#ifndef _HWA_WKU_H_
#define _HWA_WKU_H_

#include "device_header.h"

#if WKU_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_wku HwA_wku
 * @ingroup module_driver_wku
 * @{
 */

/********* Local typedef ************/
/** @brief Wku input */
typedef enum
{
    WKU_INPUT_WDOG0 = 0x000002U,
    WKU_INPUT_WDOG1 = 0x000004U,
    WKU_INPUT_FCSPI0 = 0x000040U,
    WKU_INPUT_FCUART0 = 0x000080U,
    WKU_INPUT_CMP0 = 0x000400U,
    WKU_INPUT_CMP1 = 0x000800U,
    WKU_INPUT_CMP2 = 0x001000U,
    WKU_INPUT_RTC_ALARM = 0x004000U,
    WKU_INPUT_RTC_SECONDS = 0x008000U,
    WKU_INPUT_FCPIT = 0x010000U,
    WKU_INPUT_CMU0 = 0x020000U,
    WKU_INPUT_AONTIMER = 0x040000U,
    WKU_INPUT_GPIOA = 0x080000U,
    WKU_INPUT_GPIOC = 0x200000U,
    WKU_INPUT_GPIOE = 0x800000U,
    WKU_INPUT_MAX = 0xFFFFFFU
} WKU_WakeupInputType;
/********* Local inline function ************/

/**
 * @brief Enable wakeup source
 *
 * @param eWakeup Wakeup source type
 */
LOCAL_INLINE void WKU_HWA_EnableWakeupSource(const WKU_WakeupInputType eWakeup)
{
    if (eWakeup < WKU_INPUT_CMP0)
    {
        WKU->MWER0 |= (uint32_t)eWakeup;
    }
    else if ((eWakeup < WKU_INPUT_FCPIT) && (eWakeup > WKU_INPUT_FCUART0))
    {
        WKU->MWER1 |= ((uint32_t)eWakeup >> 8U);
    }
    else
    {
        WKU->MWER2 |= ((uint32_t)eWakeup >> 16U);
    }
}

/**
 * @brief Disable wakeup source
 *
 * @param eWakeup Wakeup source type
 */
LOCAL_INLINE void WKU_HWA_DisableWakeupSource(const WKU_WakeupInputType eWakeup)
{
    if (eWakeup < WKU_INPUT_CMP0)
    {
        WKU->MWER0 &= ((~((uint32_t)eWakeup)) & (uint32_t)0xFF);
    }
    else if ((eWakeup < WKU_INPUT_FCPIT) && (eWakeup > WKU_INPUT_FCUART0))
    {
        WKU->MWER1 &= ((~(uint32_t)((uint32_t)eWakeup >> 8U)) & (uint32_t)0xFF);
    }
    else
    {
        WKU->MWER2 &= ((~(uint32_t)((uint32_t)eWakeup >> 16U)) & (uint32_t)0xFF);
    }
}

/**
 * @brief Read WKU wakeup source
 *
 * @return WKU wakeup source value
 */
LOCAL_INLINE uint32_t WKU_HWA_ReadWakeupSource(void)
{
    uint32_t u32WakeupSource = 0U;

    u32WakeupSource = (uint32_t)(WKU->MWER0);
    u32WakeupSource |= (uint32_t)((uint32_t)(WKU->MWER1) << 8U);
    u32WakeupSource |= (uint32_t)((uint32_t)(WKU->MWER2) << 16U);

    return u32WakeupSource;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_WKU_H_ */
