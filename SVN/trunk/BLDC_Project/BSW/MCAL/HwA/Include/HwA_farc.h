/**
 * @file HwA_farc.h
 * @author Flagchip054
 * @brief FARC hardware access layer
 * @version 2.0.0
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 * 
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/

#ifndef _HWA_FARC_H_
#define _HWA_FARC_H_

#include "device_header.h"

#if FARC_INSTANCE_COUNT > 0u

/**
 * @defgroup HwA_farc HwA_farc
 * @ingroup module_driver_farc
 * @{
 */

/**
 * @brief Get FARC module LRBA register
 *
 * @return LRBA register value
 */
LOCAL_INLINE uint32_t FARC_HWA_GetLRBA(void)
{
    return FARC->LRBAR;
}

/**
 * @brief Set FARC module LRS register
 *
 * @param Size LRS register value
 */
LOCAL_INLINE void FARC_HWA_SetLRS(uint32_t Size)
{
    FARC->LRSR = Size;
}

/**
 * @brief Set FARC module PRBA register
 *
 * @param BaseAddr PRBA register value
 */
LOCAL_INLINE void FARC_HWA_SetPRBA(uint32_t BaseAddr)
{
    FARC->PRBAR = BaseAddr;
}

/**
 * @brief Get FARC module LRS register
 *
 * @return LRS register value
 */
LOCAL_INLINE uint32_t FARC_HWA_GetLRS(void)
{
    return FARC->LRSR;
}

/**
 * @brief Get FARC module PRBA register
 *
 * @return PRBA register value
 */
LOCAL_INLINE uint32_t FARC_HWA_GetPRBA(void)
{
    return FARC->PRBAR;
}

/** @}*/
#endif

#endif /* _HWA_FARC_H_ */
