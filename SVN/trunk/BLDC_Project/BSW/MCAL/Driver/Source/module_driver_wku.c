/**
 * @file module_driver_wku.c
 * @author Flagchip032
 * @brief WKU driver source code
 * @version 2.0.0
 * @date 2024-05-15
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
#include "module_driver_wku.h"

#if WKU_INSTANCE_COUNT > 0U

/**
 * @brief WKU Enable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_EnableWakeupSource(const uint32_t u32Input)
{
    uint32_t u32TempValue = 0U;
    uint8_t u8Index = 0U;
    WKU_StatusType eRet = WKU_STATUS_SUCCESS;
    if (u32Input > (uint32_t)WKU_INPUT_MAX)
    {
        eRet = WKU_STATUS_PARAM_INVALID;
    }

    if (WKU_STATUS_SUCCESS == eRet)
    {
        u32TempValue = u32Input;
        while (u32TempValue)
        {
            if (u32TempValue & ((uint32_t)1 << u8Index))
            {
                WKU_HWA_EnableWakeupSource((WKU_WakeupInputType)((uint32_t)1 << u8Index));
            }
            u32TempValue &= (uint32_t)~((uint32_t)1 << u8Index);
            u8Index++;
        }
    }
    return eRet;
}

/**
 * @brief WKU Disable wakeup source for single input
 *
 * @param u32Input Number of input, WKU_WakeupInputType type is wakeup source definition
 * @return WKU return type
 */
WKU_StatusType WKU_DisableWakeupSource(const uint32_t u32Input)
{
    uint32_t u32TempValue = 0U;
    uint8_t u8Index = 0U;
    WKU_StatusType eRet = WKU_STATUS_SUCCESS;
    if (u32Input > (uint32_t)WKU_INPUT_MAX)
    {
        eRet = WKU_STATUS_PARAM_INVALID;
    }

    if (WKU_STATUS_SUCCESS == eRet)
    {
    	u32TempValue = u32Input;
        while (u32TempValue)
        {
            if (u32TempValue & ((uint32_t)1 << u8Index))
            {
                WKU_HWA_DisableWakeupSource((WKU_WakeupInputType)((uint32_t)1 << u8Index));
            }
            u32TempValue &= (uint32_t)~((uint32_t)1 << u8Index);
            u8Index++;
        }
    }
    return eRet;
}

/**
 * @brief WKU get wakeup source
 *
 * @return output wakeup source
 */
uint32_t WKU_GetWakeupSources(void)
{
    return WKU_HWA_ReadWakeupSource();
}

#endif
