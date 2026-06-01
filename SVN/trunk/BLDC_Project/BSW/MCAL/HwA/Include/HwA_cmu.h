/**
 * @file HwA_cmu.h
 * @author Flagchip100
 * @brief CMU hardware access layer
 * @version 2.0.0
 * @date 2024-08-15
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#ifndef _HWA_CMU_H_
#define _HWA_CMU_H_

#include "device_header.h"

#if CMU_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_cmu HwA_cmu
 * @ingroup module_driver_cmu
 * @{
 */

/**
 * @brief Set Reference Window value
 *
 * @param pCmu CMU Instance
 * @param u32Temp Ref Window value
 */
LOCAL_INLINE void CMU_HWA_SetRefWindow(CMU_Type *const pCmu, uint32_t u32Temp)
{
    pCmu->REF_WINDOW = u32Temp;
}

/**
 * @brief Set Minimun Counter value
 *
 * @param pCmu CMU Instance
 * @param u32Temp Min Count value
 */
LOCAL_INLINE void CMU_HWA_SetMinCnts(CMU_Type *const pCmu, uint32_t u32Temp)
{
    pCmu->MIN = u32Temp;
}

/**
 * @brief Get Minimun Counter value
 *
 * @param pCmu CMU Instance
 * @return Min count value
 */
LOCAL_INLINE uint32_t CMU_HWA_GetMinCnts(CMU_Type *const pCmu)
{
    return (pCmu->MIN & CMU_MIN_MIN_MASK) >> CMU_MIN_MIN_SHIFT;
}

/**
 * @brief Set Maximun Counter value
 *
 * @param pCmu CMU Instance
 * @param u32Temp Max count value
 */
LOCAL_INLINE void CMU_HWA_SetMaxCnts(CMU_Type *const pCmu, uint32_t u32Temp)
{
    pCmu->MAX = u32Temp;
}

/**
 * @brief Get Maximun Counter value
 *
 * @param pCmu CMU Instance
 * @return Max count value
 */
LOCAL_INLINE uint32_t CMU_HWA_GetMaxCnts(CMU_Type *const pCmu)
{
    return (pCmu->MAX & CMU_MAX_MAX_MASK) >> CMU_MAX_MAX_SHIFT;
}

/**
 * @brief Get Counter value
 *
 * @param pCmu CMU Instance
 * @return Counter value
 */
LOCAL_INLINE uint32_t CMU_HWA_GetCount(CMU_Type *const pCmu)
{
    return (pCmu->MON_CNT & CMU_MON_CNT_MON_CNT_MASK) >> CMU_MON_CNT_MON_CNT_SHIFT;
}

/**
 * @brief Set period window Counter
 *
 * @param pCmu CMU Instance
 * @param u32Temp Period value
 */
LOCAL_INLINE void CMU_HWA_SetPeriodWindow(CMU_Type *const pCmu, uint32_t u32Temp)
{
    pCmu->PERIOD = (pCmu->PERIOD & ~CMU_PERIOD_WINDOW_MASK) | CMU_PERIOD_WINDOW(u32Temp);
}

/**
 * @brief Set period enble bit
 *
 * @param pCmu CMU Instance
 * @param bEnable Set enable bit
 */
LOCAL_INLINE void CMU_HWA_SetPeriodEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->PERIOD = (pCmu->PERIOD & ~CMU_PERIOD_EN_MASK) | CMU_PERIOD_EN(bEnable);
}

/**
 * @brief Get period enble bit
 *
 * @param pCmu CMU Instance
 * @return Period mode enable bit
 */
LOCAL_INLINE bool CMU_HWA_GetPeriodEnable(CMU_Type *const pCmu)
{
    return (pCmu->PERIOD & CMU_PERIOD_EN_MASK) == CMU_PERIOD_EN_MASK ? true : false;
}

/**
 * @brief Set control register value
 *
 * @param pCmu CMU Instance
 * @param u32Temp Control value
 */
LOCAL_INLINE void CMU_HWA_SETCTRL(CMU_Type *const pCmu, uint32_t u32Temp)
{
    pCmu->CTRL = u32Temp;
}

/**
 * @brief return control register value
 *
 * @param pCmu CMU Instance
 * @return CTRL value
 */
LOCAL_INLINE uint32_t CMU_HWA_GetCTRL(CMU_Type *const pCmu)
{
    uint32_t u32Temp = pCmu->CTRL;
    return u32Temp;
}

/**
 * @brief return status register value
 *
 * @param pCmu CMU Instance
 * @return Status value
 */
LOCAL_INLINE uint32_t CMU_HWA_GetST(CMU_Type *const pCmu)
{
    uint32_t u32Temp = pCmu->ST;
    return u32Temp;
}

/**
 * @brief Clear clock monitor status
 *
 * @param pCmu CMU Instance
 */
LOCAL_INLINE void CMU_HWA_ClsST(CMU_Type *const pCmu)
{
    pCmu->ST = (uint32_t)(CMU_ST_MIS_MASK | CMU_ST_LOC_MASK);
}

/**
 * @brief Enabel Standby mode
 *
 * @param pCmu CMU Instance
 * @param bEnable Enable mode
 */
LOCAL_INLINE void CMU_HWA_StanbyModeEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->CTRL = (pCmu->CTRL & ~((uint32_t)CMU_CTRL_LP_EN_MASK)) | CMU_CTRL_LP_EN(bEnable);
}

/**
 * @brief Enabel Stop mode
 *
 * @param pCmu CMU Instance
 * @param bEnable Enable mode
 */
LOCAL_INLINE void CMU_HWA_StopModeEnable(CMU_Type *const pCmu, bool bEnable)
{
    pCmu->CTRL = (pCmu->CTRL & ~((uint32_t)CMU_CTRL_STOP_EN_MASK)) | CMU_CTRL_STOP_EN(bEnable);
}

/**
 * @brief Enable Softeare Reset
 *
 * @param pCmu CMU Instance
 */
LOCAL_INLINE void CMU_HWA_SoftwareRST(CMU_Type *const pCmu)
{
    pCmu->CTRL |= CMU_CTRL_SW_RST_MASK;
}

/**
 * @brief Enable Software Reset
 *
 * @param pCmu CMU Instance
 * @return Software reset is done
 */
LOCAL_INLINE bool CMU_HWA_GetSoftwareRST(CMU_Type *const pCmu)
{
    return (pCmu->CTRL & CMU_CTRL_SW_RST_MASK) == CMU_CTRL_SW_RST_MASK ? true : false;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_CMU_H_ */
