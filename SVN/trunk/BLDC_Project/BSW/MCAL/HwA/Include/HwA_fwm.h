/**
 * @file HwA_fwm.h
 * @author Flagchip031
 * @brief FWM hardware access layer
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

#ifndef _HWA_FWM_H_
#define _HWA_FWM_H_

#include "device_header.h"

#if FWM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_fwm HwA_fwm
 * @ingroup module_driver_fwm
 * @{
 */

/********* FWM Register interface ************/
/**
 * @brief Set CTRL register value, for FWM working mode configuration.
 *
 * @param u32Ctrl configured register value
 */
LOCAL_INLINE void FWM_HWA_SetCtrl(uint32_t u32Ctrl)
{
    FWM->CTRL = u32Ctrl;
}

/**
 * @brief Get FWM enabled status, Due to the write-once feature
 *        of this bit, it cannot be re-enabled until the next reset.
 */
LOCAL_INLINE bool GetFwmEnableStatus(void)
{
    return (bool)((((uint32_t)FWM->CTRL & (uint32_t)FWM_CTRL_FWMEN_MASK) != 0U) ? true : false);
}

/**
 * @brief Get CTRL register value, for FWM working mode configuration.
 * @return uint32_t CTRL register value.
 */
LOCAL_INLINE uint32_t FWM_HWA_GetCtrl(void)
{
    uint32_t u32Temp = 0U;
    u32Temp = FWM->CTRL;
    return u32Temp;
}

/**
 * @brief Set SERV register value, used for FWM refresh
 *
 * @param u32Service configured register value
 */
LOCAL_INLINE void FWM_HWA_SetService(uint32_t u32Service)
{
    FWM->SERV = u32Service;
}

/**
 * @brief Set CMPL register value, used for Windowed FWM counter low threshold setting.
 *
 * @param u32CmpL configured register value
 */
LOCAL_INLINE void FWM_HWA_SetCmpL(uint32_t u32CmpL)
{
    FWM->CMPL = u32CmpL;
}

/**
 * @brief Set CMPL register value, used for Windowed FWM counter high threshold setting.
 *
 * @param u32CmpH configured register value
 */
LOCAL_INLINE void FWM_HWA_SetCmpH(uint32_t u32CmpH)
{
    FWM->CMPH = u32CmpH;
}

/**
 * @brief Set CLKPRESCALER register value, for input clock divide.
 *
 * @param u32ClkPrescaler configured register value
 */
LOCAL_INLINE void FWM_HWA_SetClkPrescaler(uint32_t u32ClkPrescaler)
{
    FWM->CLKPRESCALER = u32ClkPrescaler;
}

/** @}*/ /* HwA_FWM */

#endif

#endif /* #ifndef _HWA_FWM_H_ */
