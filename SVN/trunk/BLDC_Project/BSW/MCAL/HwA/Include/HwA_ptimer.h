/**
 * @file HwA_ptimer.h
 * @author Flagchip030
 * @brief PTIMER hardware access layer
 * @version 2.0.0
 * @date 2024-04-20
 * 
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 * 
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip030   N/A          First version
*********************************************************************************/

#ifndef _HWA_PTIMER_H_
#define _HWA_PTIMER_H_

#include "device_header.h"

#if PTIMER_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_ptimer HwA_ptimer
 * @ingroup module_driver_ptimer
 * @{
 */

/**
 * @brief Ptimer value load mode
 *
 * Some Ptimer registers are buffered and will only take effect after called
 * PTIMER_LoadValue() function, and this option selects when the buffered configurations
 * will tack effect after PTIMER_LoadValue() is called.
 *
 */
typedef enum
{
    PTIMER_LOAD_VAL_IMMEDIATELY                       = 0U,
    /**<  Loaded immediately after load operation. */
    PTIMER_LOAD_VAL_AT_MODULO_COUNTER                 = 1U,
    /**< Loaded when counter hits the max count after load operation. */
    PTIMER_LOAD_VAL_AT_NEXT_TRIGGER                   = 2U,
    /**< Loaded when detecting an input trigger after load operation. */
    PTIMER_LOAD_VAL_AT_MODULO_COUNTER_OR_NEXT_TRIGGER = 3U
    /**< Loaded when counter hits the max count or detecting an input trigger after load operation. */
} PTIMER_LoadValueModeType;

/**
 * @brief Ptimer clock pre-divider factor
 *
 * The Ptimer clock source is from core clock and the divider is a multiplication of
 * PTIMER_ClockPreDividerType and PTIMER_ClockPreDivMultiplyFactorType, and thus:
 * Freq = Core_Freq / (PTIMER_ClockPreDividerType * PTIMER_ClockPreDivMultiplyFactorType)
 *
 */
typedef enum
{
    PTIMER_PRE_DIVIDE_BY_1   = 0U,
    PTIMER_PRE_DIVIDE_BY_2   = 1U,
    PTIMER_PRE_DIVIDE_BY_4   = 2U,
    PTIMER_PRE_DIVIDE_BY_8   = 3U,
    PTIMER_PRE_DIVIDE_BY_16  = 4U,
    PTIMER_PRE_DIVIDE_BY_32  = 5U,
    PTIMER_PRE_DIVIDE_BY_64  = 6U,
    PTIMER_PRE_DIVIDE_BY_128 = 7U
} PTIMER_ClockPreDividerType;

/**
 * @brief Ptimer clock divider multiplication factor
 *
 * The Ptimer clock source is from core clock and the divider is a multiplication of
 * PTIMER_ClockPreDividerType and PTIMER_ClockPreDivMultiplyFactorType, and thus:
 * Freq = Core_Freq / (PTIMER_ClockPreDividerType * PTIMER_ClockPreDivMultiplyFactorType)
 *
 */
typedef enum
{
    PTIMER_PRE_DIVIDER_MULTIPLY_BY_1  = 0U,
    PTIMER_PRE_DIVIDER_MULTIPLY_BY_10 = 1U,
    PTIMER_PRE_DIVIDER_MULTIPLY_BY_20 = 2U,
    PTIMER_PRE_DIVIDER_MULTIPLY_BY_40 = 3U
} PTIMER_ClockPreDivMultiplyFactorType;

/**
 * @brief Ptimer trigger source
 *
 */
typedef enum
{
    PTIMER_TRGSRC_TRGSEL = 0x00U, /**< Ptimer trigger source from TrgSel */
    PTIMER_TRGSRC_SW     = 0x0FU  /**< Ptimer trigger source from software trigger*/
} PTIMER_TrgSrcType;

/**
 * @brief Get the STATUS_CTRL register value
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE uint32_t PTIMER_HWA_GetStatusCtrl(const PTIMER_Type *const pPtimer)
{
    return pPtimer->STATUS_CTRL;
}

/**
 * @brief Set the STATUS_CTRL register value
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u32CfgValue the register value to set
 */
LOCAL_INLINE void PTIMER_HWA_SetStatusCtrl(PTIMER_Type *const pPtimer, uint32_t u32CfgValue)
{
    pPtimer->STATUS_CTRL = u32CfgValue;
}

/**
 * @brief Get the load mode of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return PTIMER_LoadValueModeType the load mode of the Ptimer instance
 */
LOCAL_INLINE PTIMER_LoadValueModeType PTIMER_HWA_GetLoadMode(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_LDMODE_MASK) >> PTIMER_STATUS_CTRL_LDMODE_SHIFT;
    return (PTIMER_LoadValueModeType)u32TmpVal;
}

/**
 * @brief Set the load mode of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param eLoadMode the load mode of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_SetLoadMode(PTIMER_Type *const pPtimer, PTIMER_LoadValueModeType eLoadMode)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_LDMODE_MASK) | PTIMER_STATUS_CTRL_LDMODE(eLoadMode);
}

/**
 * @brief Get whether sequence error interrupt is enabled
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return true  sequence error interrupt is enabled
 * @return false sequence error interrupt is disabled
 */
LOCAL_INLINE bool PTIMER_HWA_GetSeqErrIntEnableFlag(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_SERR_INTEN_MASK) >> PTIMER_STATUS_CTRL_SERR_INTEN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable sequence error interrupt
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param bEnable whether to enable sequence error interrupt
 */
LOCAL_INLINE void PTIMER_HWA_SetSeqErrIntEnableFlag(PTIMER_Type *const pPtimer, bool bEnable)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_SERR_INTEN_MASK) | PTIMER_STATUS_CTRL_SERR_INTEN(
                               bEnable);
}

/**
 * @brief Generate software trigger signal for Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_GenerateSwTrigger(PTIMER_Type *const pPtimer)
{
    pPtimer->STATUS_CTRL |= PTIMER_STATUS_CTRL_SWTRG_MASK;
}

/**
 * @brief Get whether DMA is enabled for the Ptimer insstance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return true DMA is enabled
 * @return false DMA is disabled
 */
LOCAL_INLINE bool PTIMER_HWA_GetDMAEnableFlag(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_DMAEN_MASK) >> PTIMER_STATUS_CTRL_DMAEN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable Ptimer DMA
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param bEnable whether to enable DMA for the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_SetDMAEnableFlag(PTIMER_Type *const pPtimer, bool bEnable)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_DMAEN_MASK) | PTIMER_STATUS_CTRL_DMAEN(bEnable);
}

/**
 * @brief Get the predivider value of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return PTIMER_ClockPreDividerType the predivider of the Ptimer instance
 */
LOCAL_INLINE PTIMER_ClockPreDividerType PTIMER_HWA_GetDivPrescaler(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_PRESCALER_MASK) >> PTIMER_STATUS_CTRL_PRESCALER_SHIFT;
    return (PTIMER_ClockPreDividerType)u32TmpVal;
}

/**
 * @brief Set the predivider value of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param eDivPrescaler the predivider of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_SetDivPrescaler(PTIMER_Type *const pPtimer, PTIMER_ClockPreDividerType eDivPrescaler)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_PRESCALER_MASK) | PTIMER_STATUS_CTRL_PRESCALER(
                               eDivPrescaler);
}

/**
 * @brief Get the trigger source of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return PTIMER_TRGSRC_TRGSEL the trigger source is from TrgSel
 * @return PTIMER_TRGSRC_SW the trigger source is from software
 */
LOCAL_INLINE PTIMER_TrgSrcType PTIMER_HWA_GetTriggerSource(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_TRGSEL_MASK) >> PTIMER_STATUS_CTRL_TRGSEL_SHIFT;
    return (PTIMER_TrgSrcType)u32TmpVal;
}

/**
 * @brief Set the trigger source of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param eTriggerSource the trigger source of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_SetTriggerSource(PTIMER_Type *const pPtimer, PTIMER_TrgSrcType eTriggerSource)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_TRGSEL_MASK) | PTIMER_STATUS_CTRL_TRGSEL(
                               eTriggerSource);
}

/**
 * @brief Get whether the Ptimer instance is enabled
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return true the Ptimer instance is enabled
 * @return false the Ptimer instance is disabled
 */
LOCAL_INLINE bool PTIMER_HWA_GetEnableFlag(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_ENABLE_MASK) >> PTIMER_STATUS_CTRL_ENABLE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_Enable(PTIMER_Type *const pPtimer)
{
    pPtimer->STATUS_CTRL |= PTIMER_STATUS_CTRL_ENABLE_MASK;
}

/**
 * @brief Disable the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_Disable(PTIMER_Type *const pPtimer)
{
    pPtimer->STATUS_CTRL &= ~PTIMER_STATUS_CTRL_ENABLE_MASK;
}

/**
 * @brief Get the delay interrupt flag of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return true the delay interrupt flag of the Ptimer instance is generated
 * @return false the delay interrupt flag of the Ptimer instance is not generated
 */
LOCAL_INLINE bool PTIMER_HWA_GetInterruptFlag(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_INTFLAG_MASK) >> PTIMER_STATUS_CTRL_INTFLAG_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the delay interrupt flag of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_ClearInterruptFlag(PTIMER_Type *const pPtimer)
{
    pPtimer->STATUS_CTRL &= ~PTIMER_STATUS_CTRL_INTFLAG_MASK;
}

/**
 * @brief Get whether delay interrupt is enabled for the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE bool PTIMER_HWA_GetInterruptEnableFlag(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_INTEN_MASK) >> PTIMER_STATUS_CTRL_INTEN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable delay interrupt for the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param bEnable whether to enable delay interrupt for the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_SetInterruptEnableFlag(PTIMER_Type *const pPtimer, bool bEnable)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_INTEN_MASK) | PTIMER_STATUS_CTRL_INTEN(bEnable);
}

/**
 * @brief Get the multiply factor of the predivider of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return PTIMER_ClockPreDivMultiplyFactorType the multiply factor of the Ptimer instance
 */
LOCAL_INLINE PTIMER_ClockPreDivMultiplyFactorType PTIMER_HWA_GetDivMultiply(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_MULT_MASK) >> PTIMER_STATUS_CTRL_MULT_SHIFT;
    return (PTIMER_ClockPreDivMultiplyFactorType)u32TmpVal;
}

/**
 * @brief Set the multiply factor of the predivider of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param eMultFactor the multiply factor of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_SetDivMultiply(PTIMER_Type *const pPtimer,
                                            PTIMER_ClockPreDivMultiplyFactorType eMultFactor)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_MULT_MASK) | PTIMER_STATUS_CTRL_MULT(eMultFactor);
}

/**
 * @brief Get whether continuous mode is enabled for the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return true continuous mode is enabled for the Ptimer instance
 * @return false continuous mode is disabled for the Ptimer instance
 */
LOCAL_INLINE bool PTIMER_HWA_GetContinuoiusModeFlag(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_CONT_MASK) >> PTIMER_STATUS_CTRL_CONT_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable continuous mode for the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param bEnable whether to enable continuous mode for the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_SetContinuoiusModeFlag(PTIMER_Type *const pPtimer, bool bEnable)
{
    pPtimer->STATUS_CTRL = (pPtimer->STATUS_CTRL & ~PTIMER_STATUS_CTRL_CONT_MASK) | PTIMER_STATUS_CTRL_CONT(bEnable);
}

/**
 * @brief Get the config value loading status
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return true the config values are in loading status
 * @return false the config values are loaded
 */
LOCAL_INLINE bool PTIMER_HWA_GetValueLoadStatus(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->STATUS_CTRL & PTIMER_STATUS_CTRL_LDOK_MASK) >> PTIMER_STATUS_CTRL_LDOK_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Load the buffered values into register
 *
 * @note Some Ptimer registers are buffered and will only take effect after called
 * this function
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_LoadValue(PTIMER_Type *const pPtimer)
{
    pPtimer->STATUS_CTRL |= PTIMER_STATUS_CTRL_LDOK_MASK;
}

/**
 * @brief Get the Ptimer max counter period
 * When the Ptimer counter reaches the period, it will return to zero
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return uint16_t the Ptimer max count
 */
LOCAL_INLINE uint16_t PTIMER_HWA_GetMaxCount(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->MAX_CNT & PTIMER_MAX_CNT_MAX_CNT_MASK) >> PTIMER_MAX_CNT_MAX_CNT_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set the Ptimer max counter period
 * When the Ptimer counter reaches the period, it will return to zero
 *
 * @note the period parameter is buffered and will take effect only after called PTIMER_LoadValue()
 * function.
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u16MaxCnt the Ptimer max count
 */
LOCAL_INLINE void PTIMER_HWA_SetMaxCount(PTIMER_Type *const pPtimer, uint16_t u16MaxCnt)
{
    pPtimer->MAX_CNT = PTIMER_MAX_CNT_MAX_CNT(u16MaxCnt);
}

/**
 * @brief Get the Ptimer current count value
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return uint16_t the Ptimer current count value
 */
LOCAL_INLINE uint16_t PTIMER_HWA_GetCounterValue(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->CNT & PTIMER_CNT_CNT_MASK) >> PTIMER_CNT_CNT_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Get the ptimer interrupt period
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return uint16_t the Ptimer interrupt period
 */
LOCAL_INLINE uint16_t PTIMER_HWA_GetInterruptDelay(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->INT_DLY & PTIMER_INT_DLY_INT_DLY_MASK) >> PTIMER_INT_DLY_INT_DLY_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set the ptimer interrupt period
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u16InterruptDelay the Ptimer interrupt period
 */
LOCAL_INLINE void PTIMER_HWA_SetInterruptDelay(PTIMER_Type *const pPtimer, uint16_t u16InterruptDelay)
{
    pPtimer->INT_DLY = PTIMER_INT_DLY_INT_DLY(u16InterruptDelay);
}

/**
 * @brief Get whether back to back trigger is enbaled for the Ptimer channel
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 * @return true back to back trigger is enbaled for the Ptimer channel
 * @return false back to back trigger is disabled for the Ptimer channel
 */
LOCAL_INLINE bool PTIMER_HWA_GetChannelBackToBackFlag(const PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerCtrlIdx = u8Channel % 8U;
    uint32_t u32TmpVal = (pPtimer->CH[u8PtimerChannelIdx].CTRL & PTIMER_CTRL_CH_BTB(1UL << u8PtimerCtrlIdx)) >>
                         (PTIMER_CTRL_CH_BTB_SHIFT + u8PtimerCtrlIdx);
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get whether pre-trigger output is enbaled for the Ptimer channel
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 * @return true pre-trigger output is enbaled for the Ptimer channel
 * @return false pre-trigger output is disabled for the Ptimer channel
 */
LOCAL_INLINE bool PTIMER_HWA_GetChannelPretriggerOutputFlag(const PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerCtrlIdx = u8Channel % 8U;
    uint32_t u32TmpVal = (pPtimer->CH[u8PtimerChannelIdx].CTRL & PTIMER_CTRL_CH_PTOS(1UL << u8PtimerCtrlIdx)) >>
                         (PTIMER_CTRL_CH_PTOS_SHIFT + u8PtimerCtrlIdx);
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief  Get whether pre-trigger is enbaled for the Ptimer channel
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 * @return true pre-trigger is enbaled for the Ptimer channel
 * @return false pre-trigger is disabled for the Ptimer channel
 */
LOCAL_INLINE bool PTIMER_HWA_GetChannelPretriggerEnableFlag(const PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerCtrlIdx = u8Channel % 8U;
    uint32_t u32TmpVal = (pPtimer->CH[u8PtimerChannelIdx].CTRL & PTIMER_CTRL_CH_PTEN(1UL << u8PtimerCtrlIdx)) >>
                         (PTIMER_CTRL_CH_PTEN_SHIFT + u8PtimerCtrlIdx);
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the Ptimer channel control flags
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 * @param bEnablePretrigger whether to enable pre-trigger
 * @param bEnablePretriggerOutput whether to enable pre-trigger output
 * @param bEnableBackToBack whether to enable back to back trigger
 */
LOCAL_INLINE void PTIMER_HWA_SetChannelControl(PTIMER_Type *const pPtimer, uint8_t u8Channel, bool bEnablePretrigger,
                                               bool bEnablePretriggerOutput, bool bEnableBackToBack)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerCtrlIdx = u8Channel % 8U;
    uint32_t u32CtrlMask = PTIMER_CTRL_CH_PTEN(1UL << u8PtimerCtrlIdx) |
                           PTIMER_CTRL_CH_PTOS(1UL << u8PtimerCtrlIdx) |
                           PTIMER_CTRL_CH_BTB(1UL << u8PtimerCtrlIdx);
    pPtimer->CH[u8PtimerChannelIdx].CTRL = (pPtimer->CH[u8PtimerChannelIdx].CTRL & ~u32CtrlMask) |
                                           PTIMER_CTRL_CH_PTEN((uint32_t)bEnablePretrigger << u8PtimerCtrlIdx) |
                                           PTIMER_CTRL_CH_PTOS((uint32_t)bEnablePretriggerOutput << u8PtimerCtrlIdx) |
                                           PTIMER_CTRL_CH_BTB((uint32_t)bEnableBackToBack << u8PtimerCtrlIdx);
}

/**
 * @brief Get whether the Ptimer counter matches the channel counter
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 * @return true the Ptimer counter matches the channel counter
 * @return false the Ptimer counter has not reached the channel counter
 */
LOCAL_INLINE bool PTIMER_HWA_GetChannelCounterFlag(const PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerStatusIdx = u8Channel % 8U;
    uint32_t u32TmpVal = (pPtimer->CH[u8PtimerChannelIdx].STATUS & PTIMER_STATUS_CH_CHN_FLAG(1UL << u8PtimerStatusIdx)) >>
                         (PTIMER_STATUS_CH_CHN_FLAG_SHIFT + u8PtimerStatusIdx);
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the Ptimer channel counter match flag
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 */
LOCAL_INLINE void PTIMER_HWA_ClearChannelCounterFlag(PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerStatusIdx = u8Channel % 8U;
    pPtimer->CH[u8PtimerChannelIdx].STATUS &= ~PTIMER_STATUS_CH_CHN_FLAG(1UL << u8PtimerStatusIdx);
}

/**
 * @brief Get the sequence error status of the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the channel related to the sequence error
 * @return true the selected channel has sequence error
 * @return false the selected channel does not have sequence error
 */
LOCAL_INLINE bool PTIMER_HWA_GetChannelSequenceErrorFlag(const PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerStatusIdx = u8Channel % 8U;
    uint32_t u32TmpVal = (pPtimer->CH[u8PtimerChannelIdx].STATUS & PTIMER_STATUS_CH_SERR_FLAG(1UL << u8PtimerStatusIdx)) >>
                         (PTIMER_STATUS_CH_SERR_FLAG_SHIFT + u8PtimerStatusIdx);
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the sequence error flag of the selected Ptimer channel
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel to clear the sequence error flag
 */
LOCAL_INLINE void PTIMER_HWA_ClearChannelSequenceErrorFlag(PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / 8U;
    uint8_t u8PtimerStatusIdx = u8Channel % 8U;
    pPtimer->CH[u8PtimerChannelIdx].STATUS &= ~PTIMER_STATUS_CH_SERR_FLAG(1UL << u8PtimerStatusIdx);
}

/**
 * @brief Get the channel delay value
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 * @return uint16_t the channel delay value
 */
LOCAL_INLINE uint16_t PTIMER_HWA_GetChannelDelay(const PTIMER_Type *const pPtimer, uint8_t u8Channel)
{
    uint8_t u8PtimerChannelIdx = u8Channel / PTIMER_CH_DLY_CNT;
    uint8_t u8PtimerDelayIdx = u8Channel % PTIMER_CH_DLY_CNT;
    uint32_t u32TmpVal = (pPtimer->CH[u8PtimerChannelIdx].DLY[u8PtimerDelayIdx] & PTIMER_DLY0_CH_CHNDLY_MASK) >>
                         PTIMER_DLY0_CH_CHNDLY_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set the channel delay value
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u8Channel the Ptimer channel
 * @param u16Delay the channel delay value
 */
LOCAL_INLINE void PTIMER_HWA_SetChannelDelay(PTIMER_Type *const pPtimer, uint8_t u8Channel, uint16_t u16Delay)
{
    uint8_t u8PtimerChannelIdx = u8Channel / PTIMER_CH_DLY_CNT;
    uint8_t u8PtimerDelayIdx = u8Channel % PTIMER_CH_DLY_CNT;
    pPtimer->CH[u8PtimerChannelIdx].DLY[u8PtimerDelayIdx] = PTIMER_DLY0_CH_CHNDLY(u16Delay);
}

/**
 * @brief Get whether pulse-out is enabled
 *
 * @param pPtimer the base address of the Ptimer instance
 * @return true pulse-out is enabled
 * @return false pulse-out is disabled
 */
LOCAL_INLINE bool PTIMER_HWA_GetPulseOutEnableFlag(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->POEN & PTIMER_POEN_POEN_MASK) >> PTIMER_POEN_POEN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable pulse-out for the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_EnablePulseOut(PTIMER_Type *const pPtimer)
{
    pPtimer->POEN |= PTIMER_POEN_POEN_MASK;
}

/**
 * @brief Disable pulse-out for the Ptimer instance
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE void PTIMER_HWA_DisablePulseOut(PTIMER_Type *const pPtimer)
{
    pPtimer->POEN &= ~PTIMER_POEN_POEN_MASK;
}

/**
 * @brief Get the delay high value for the pulse-out function
 * When the Ptimer counter reach the delay high value, the pulse output goes high
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE uint16_t PTIMER_HWA_GetPulseOutDelayHigh(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->PODLY & PTIMER_PODLY_DLY1_MASK) >> PTIMER_PODLY_DLY1_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Get the delay low value for the pulse-out function
 * When the Ptimer counter reach the delay low value, the pulse output goes low
 *
 * @param pPtimer the base address of the Ptimer instance
 */
LOCAL_INLINE uint16_t PTIMER_HWA_GetPulseOutDelayLow(const PTIMER_Type *const pPtimer)
{
    uint32_t u32TmpVal = (pPtimer->PODLY & PTIMER_PODLY_DLY2_MASK) >> PTIMER_PODLY_DLY2_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set the pulse out delay value
 * When the Ptimer counter reach the delay high value, the pulse output goes high
 * When the Ptimer counter reach the delay low value, the pulse output goes low
 * The delay high value can be either greater or less than the delay low value
 *
 * @param pPtimer the base address of the Ptimer instance
 * @param u16DelayHigh the delay high value
 * @param u16DelayLow the delay low value
 */
LOCAL_INLINE void PTIMER_HWA_SetPulseOutDelay(PTIMER_Type *const pPtimer, uint16_t u16DelayHigh, uint16_t u16DelayLow)
{
    pPtimer->PODLY = PTIMER_PODLY_DLY1(u16DelayHigh) | PTIMER_PODLY_DLY2(u16DelayLow);
}

/** @}*/

#endif

#endif /* _HWA_PTIMER_H_ */
