/**
 * @file HwA_WDOG.h
 * @author Flagchip031
 * @brief Wdog hardware access layer
 * @version 2.0.0
 * @date 2024-04-16
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip031   N/A          First version
*********************************************************************************/

#ifndef _HWA_WDOG_H_
#define _HWA_WDOG_H_

#include "device_header.h"

#if WDOG_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_wdog HwA_wdog
 * @ingroup module_driver_wdog
 * @{
 */

/********* Local typedef ************/

/*********   Local inline function   ************/

/********* Wdog Register interface ************/
/**
 * @brief Set CS register value, for Wdog working mode configuration.
 *
 * @param pWdog: point to wdog instance base register address.
 * 
 * @param u32Cs: configured register value
 */
LOCAL_INLINE void WDOG_HWA_SetCs(WDOG_Type *pWdog, uint32_t u32Cs)
{
    pWdog->CS = u32Cs;
}

/**
 * @brief Get CS register value, for WDOG working mode configuration.
 *
 * @param *pWdog: point to wdog instance base register address.
 *
 * @return uint32_t CS register value.
 */
LOCAL_INLINE uint32_t WDOG_HWA_GetCs(WDOG_Type *pWdog)
{
    uint32_t u32Temp = 0U;
    u32Temp = pWdog->CS;
    return u32Temp;
}

/**
 * @brief Clear Wdog interrupt flag.
 *
 * @param *pWdog: point to wdog instance base register address.
 */
LOCAL_INLINE void WDOG_HWA_ClearInterruptFlag(WDOG_Type *pWdog)
{
    pWdog->CS |= WDOG_CS_FLAG_MASK;
}

/**
 * @brief Get WDOG unlock status, if locked, register can't be written.
 *
 * @param *pWdog: point to wdog instance base register address.
 *
 * @return bool. true as unlocked. false as locked.
 */
LOCAL_INLINE bool WDOG_HWA_GetUnlockStatus(WDOG_Type *pWdog)
{
    return (bool)((((uint32_t)pWdog->CS & (uint32_t)WDOG_CS_ULK_STAT_MASK) != 0U) ? true : false);
}

/**
 * @brief Set COUNTER register value. for Wdog unlock and refresh usage.
 *
 * @param *pWdog: point to wdog instance base register address.
 * 
 * @param u32Counter configured register value
 */
LOCAL_INLINE void WDOG_HWA_SetCounter(WDOG_Type *pWdog, uint32_t u32Counter)
{
    pWdog->COUNTER = u32Counter;
}

/**
 * @brief Set TIMEOUT register value. for WDOG timeout value
 *
 * @param *pWdog: point to wdog instance base register address.
 * 
 * @param u16Timeout configured register value
 */
LOCAL_INLINE void WDOG_HWA_SetTimeout(WDOG_Type *pWdog, uint16_t u16Timeout)
{
    pWdog->TIMEOUT = u16Timeout;
}

/**
 * @brief Set WINDOW register value. for windowed WDOG low threshold value.
 *
 * @param *pWdog: point to wdog instance base register address.
 * 
 * @param u16Window configured register value
 */
LOCAL_INLINE void WDOG_HWA_SetWindow(WDOG_Type *pWdog, uint16_t u16Window)
{
    pWdog->WINDOW = u16Window;
}

/** @}*/ /* HwA_WODG */

#endif

#endif /* #ifndef _HWA_WDOG_H_ */
