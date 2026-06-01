/**
 * @file        HwA_freqm.h
 * @author      Flagchip100
 * @brief       FREQM hardware access layer
 * @version     2.0.0
 * @date        2024-08-01
 *
 * @copyright   Copyright 2020-2024 Flagchip Semiconductors Co., Ltd.
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#ifndef _HWA_FREQM_H_
#define _HWA_FREQM_H_

#include "device_header.h"

#if FREQM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_freqm HwA_freqm
 * @ingroup module_driver_freqm
 * @{
 */

/**
 * @brief Set the measured clock selection.
 *
 * @param pFreqm the base address of the FREQM.
 * @param u8ClkSel the clock selection index.
 */
LOCAL_INLINE void FREQM_HWA_MesClkSel(FREQM_Type *const pFreqm, uint8_t u8ClkSel)
{
    pFreqm->CTRL = (pFreqm->CTRL & ~((uint32_t)FREQM_CTRL_MES_CLK_SEL_MASK)) | FREQM_CTRL_MES_CLK_SEL(u8ClkSel);
}

/**
 * @brief Set the clock selection.
 *
 * @param pFreqm the base address of the FREQM.
 * @param u8PredivVal the measure clock prediv value.
 */
LOCAL_INLINE void FREQM_HWA_MesClk_PreDiv(FREQM_Type *const pFreqm, uint8_t u8PredivVal)
{
    pFreqm->CTRL = (pFreqm->CTRL & ~((uint32_t)FREQM_CTRL_MES_CLK_PREDIV_MASK)) | FREQM_CTRL_MES_CLK_PREDIV(u8PredivVal);
}

/**
 * @brief Enable count event interrupt.
 *
 * @param pFreqm the base address of the FREQM.
 */
LOCAL_INLINE void FREQM_HWA_EnableCntEventInterrupt(FREQM_Type *const pFreqm)
{
    pFreqm->CTRL |= FREQM_CTRL_CNT_EVENT_IE_MASK;
}

/**
 * @brief Disable count event interrupt.
 *
 * @param pFreqm the base address of the FREQM.
 */
LOCAL_INLINE void FREQM_HWA_DisableCntEventInterrupt(FREQM_Type *const pFreqm)
{
    pFreqm->CTRL &= ~((uint32_t)FREQM_CTRL_CNT_EVENT_IE_MASK);
}

/**
 * @brief Set counting length of measure counter.
 *
 * @param pFreqm the base address of the FREQM.
 * @param u32MesLen counting length of measure counter.
 */
LOCAL_INLINE void FREQM_HWA_SetMesLength(FREQM_Type *const pFreqm, uint32_t u32MesLen)
{
    pFreqm->MES_LENGTH = u32MesLen;
}

/**
 * @brief Set timeout value of reference counter.
 *
 * @param pFreqm the base address of the FREQM.
 * @param u32RefTo timeout value of reference counter.
 */
LOCAL_INLINE void FREQM_HWA_SetRefTimeout(FREQM_Type *const pFreqm, uint32_t u32RefTo)
{
    pFreqm->REF_TIMEOUT = u32RefTo;
}

/**
 * @brief Set value of reference counter.
 *
 * @param pFreqm the base address of the FREQM.
 * @param u32RefCnt value of reference counter.
 */
LOCAL_INLINE void FREQM_HWA_SetRefCnt(FREQM_Type *const pFreqm, uint32_t u32RefCnt)
{
    pFreqm->REF_CNT = u32RefCnt;
}

/**
 * @brief Clear counter event interrupt flag.
 *
 * @param pFreqm the base address of the FREQM.
 */
LOCAL_INLINE void FREQM_HWA_ClearInterruptFlag(FREQM_Type *const pFreqm)
{
    pFreqm->CNT_STATUS = FREQM_CNT_STATUS_CNT_EVENT_MASK;
}

/**
 * @brief  Get counter event interrupt flag
 *
 * @param pFreqm the base address of the FREQM
 * @return false for disable, true for enable.
 */
LOCAL_INLINE bool FREQM_HWA_GetInterruptFlag(const FREQM_Type *const pFreqm)
{
   return ((pFreqm->CNT_STATUS & FREQM_CNT_STATUS_CNT_EVENT_MASK) == FREQM_CNT_STATUS_CNT_EVENT_MASK) ? true : false;
}

/**
 * @brief  Get counter status
 *
 * @param pFreqm the base address of the FREQM
 * @return Counter status.
 */
LOCAL_INLINE uint32_t FREQM_HWA_GetCntStatus(const FREQM_Type *const pFreqm)
{
    return (pFreqm->CNT_STATUS & (FREQM_CNT_STATUS_MES_CNT_START_MASK | FREQM_CNT_STATUS_MES_CNT_STOP_MASK | FREQM_CNT_STATUS_REF_CNT_STOP_MASK));
}

/**
 * @brief Set value of measure counter.
 *
 * @param pFreqm the base address of the FREQM.
 * @param u32MesCnt value of measure counter.
 */
LOCAL_INLINE void FREQM_HWA_SetMesCnt(FREQM_Type *const pFreqm, uint32_t u32MesCnt)
{
    pFreqm->MES_CNT = u32MesCnt;
}

/**
 * @brief  Get saved reference counter value.
 *
 * @param pFreqm the base address of the FREQM.
 * @return saved reference counter value.
 */
LOCAL_INLINE uint32_t FREQM_HWA_GetRefCntSave(const FREQM_Type *const pFreqm)
{
    return pFreqm->REF_CNT_SAVE;
}

/** @}*/ /* HwA_freqm */

#endif /* FREQM_INSTANCE_COUNT > 0U */

#endif /* _HWA_FREQM_H_ */
