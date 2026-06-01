/**
 * @file HwA_rtc.h
 * @author Flagchip032
 * @brief RTC hardware access layer
 * @version 2.0.0
 * @date 2024-03-22
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/
#ifndef _HWA_RTC_H_
#define _HWA_RTC_H_

#include "device_header.h"

#if RTC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_rtc HwA_rtc
 * @ingroup module_driver_rtc
 * @{
 */

/********* Local typedef ************/
/** @brief in the second interrupt mode, this type indicates the interrupt frequency.
 * in the clkout mode , this type indicates the clkout frequency . */
typedef enum
{
    RTC_FREQ_1HZ = 0,
    RTC_FREQ_2HZ,
    RTC_FREQ_4HZ,
    RTC_FREQ_8HZ,
    RTC_FREQ_16HZ,
    RTC_FREQ_32hZ,
    RTC_FREQ_64HZ,
    RTC_FREQ_128HZ
} RTC_ClkoutSecIntFreqType;
/********* Local inline function ************/

/**
 * @brief Read second value
 *
 * @param pRtc the base address of the pRtc instance.
 * @return Second value
 */
LOCAL_INLINE uint32_t RTC_HWA_ReadSecondValue(RTC_Type *const pRtc)
{
    return (uint32_t)pRtc->SR;
}

/**
 * @brief Read RTC SR overflow flag
 *
 * @param pRtc the base address of the pRtc instance.
 * @return Overflow flag
 */
LOCAL_INLINE uint32_t RTC_HWA_ReadOverflowFlag(RTC_Type *const pRtc)
{
    return ((uint32_t)pRtc->STR & (uint32_t)RTC_STR_TOF_MASK);
}

/**
 * @brief Read RTC IER overflow enable bit
 *
 * @param pRtc the base address of the pRtc instance.
 * @return Overflow Enable
 */
LOCAL_INLINE uint32_t RTC_HWA_ReadOverflowEnable(RTC_Type *const pRtc)
{
    return ((uint32_t)pRtc->IER & (uint32_t)RTC_IER_TOIE_MASK);
}

/**
 * @brief Read RTC alarm flag
 *
 * @param pRtc the base address of the pRtc instance.
 * @return Alarm flag
 */
LOCAL_INLINE uint32_t RTC_HWA_ReadAlarmFlag(RTC_Type *const pRtc)
{
    return ((uint32_t)pRtc->STR & (uint32_t)RTC_STR_TAF_MASK);
}

/**
 * @brief Read RTC alarm Enable
 *
 * @param pRtc the base address of the pRtc instance.
 * @return Alarm Enable
 */
LOCAL_INLINE uint32_t RTC_HWA_ReadAlarmEnable(RTC_Type *const pRtc)
{
    return ((uint32_t)pRtc->IER & (uint32_t)RTC_IER_TAIE_MASK);
}

/**
 * @brief Read RTC Compensation Interbal
 *
 * @param pRtc the base address of the pRtc instance.
 * @return Compensation Interbal
 */
LOCAL_INLINE uint8_t RTC_HWA_ReadCompInterval(RTC_Type *const pRtc)
{
    return (uint8_t)((pRtc->COMPR & (uint32_t)RTC_COMPR_CIC_MASK) >> RTC_COMPR_CIC_SHIFT);
}

/**
 * @brief Read RTC Compensation Value
 *
 * @param pRtc the base address of the pRtc instance.
 * @return Compensation Value
 */
LOCAL_INLINE uint8_t RTC_HWA_ReadCompValue(RTC_Type *const pRtc)
{
    return (uint8_t)((pRtc->COMPR & (uint32_t)RTC_COMPR_TCV_MASK) >> RTC_COMPR_TCV_SHIFT);
}

/**
 * @brief Sets the RTC compare interval.
 *
 * This function configures the Compare Interval Reload value (CIR) in the RTC's COMPR register,
 * enabling a timer interrupt at the specified interval. By setting the interval, an interrupt
 * can be generated at the end of each interval, which is useful for timing tasks or applications.
 *
 * @param pRtc Pointer to the RTC module, used to access specific RTC register.
 * @param u8Interval The compare interval reload value, in seconds. This is the time interval
 *                   at which an interrupt is generated when the RTC count reaches this interval.
 */
LOCAL_INLINE void RTC_HWA_SetCompInterval(RTC_Type *const pRtc, uint8_t u8Interval)
{
    pRtc->COMPR = ((pRtc->COMPR & ~RTC_COMPR_CIR_MASK) | (uint32_t)(u8Interval << RTC_COMPR_CIR_SHIFT));
}

/**
 * @brief Sets the RTC compare value.
 *
 * This function updates the Compare Value (TCR) in the RTC's COMPR register.
 * The TCR determines the point at which a compare interrupt will occur.
 *
 * @param pRtc Pointer to the RTC module, used to access specific RTC register.
 * @param u8Value The compare value, in ticks. This is the value at which an interrupt
 *                is generated when the RTC count matches this value.
 */
LOCAL_INLINE void RTC_HWA_SetCompValue(RTC_Type *const pRtc, uint8_t u8Value)
{
    pRtc->COMPR = ((pRtc->COMPR & ~RTC_COMPR_TCR_MASK) | (uint32_t)(u8Value << RTC_COMPR_TCR_SHIFT));
}

/**
 * @brief Set RTC prescaler register
 *
 * @param pRtc the base address of the pRtc instance.
 * @param u16Value PR register value
 */
LOCAL_INLINE void RTC_HWA_SetPrescalerCounterValue(RTC_Type *const pRtc, uint16_t u16Value)
{
	pRtc->PR = (uint32_t)u16Value;
}

/**
 * @brief Set RTC seconds register
 *
 * @param pRtc the base address of the pRtc instance.
 * @param u32Value SR register value
 */
LOCAL_INLINE void RTC_HWA_SetSecondCounterValue(RTC_Type *const pRtc, uint32_t u32Value)
{
	pRtc->SR = u32Value;
}

/**
 * @brief Set RTC alarm value
 *
 * @param pRtc the base address of the pRtc instance.
 * @param u32Value TAR register value
 */
LOCAL_INLINE void RTC_HWA_SetAlarmCounterValue(RTC_Type *const pRtc, uint32_t u32Value)
{
	pRtc->TAR = u32Value;
}

/**
 * @brief Set RTC interrupt value
 *
 * @param pRtc the base address of the pRtc instance.
 * @param u32Value IER register value
 */
LOCAL_INLINE void RTC_HWA_SetInterruptValue(RTC_Type *const pRtc, uint32_t u32Value)
{
	pRtc->IER = u32Value;
}

/**
 * @brief Configure control register
 *
 * @param pRtc the base address of the pRtc instance.
 * @param u32Value Control value
 */
LOCAL_INLINE void RTC_HWA_ConfigControl(RTC_Type *const pRtc, uint32_t u32Value)
{
	pRtc->CR = u32Value;
}

/**
 * @brief Enable RTC time counter
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_EnableRtcCounter(RTC_Type *const pRtc)
{
	pRtc->STR |= (uint32_t)RTC_STR_TCE_MASK;
}

/**
 * @brief Set RTC_CLKOUT is from the 32.768 khz clock
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_SetClkoutFreqStable(RTC_Type *const pRtc)
{
	pRtc->CR |= (uint32_t)RTC_CR_CKPS_MASK;
}

/**
 * @brief Enables or disables the RTC alarm interrupt.
 *
 * This function sets or clears the TAIE bit in the RTC IER register to enable or disable the alarm interrupt.
 * When the alarm interrupt is enabled, the RTC generates an interrupt request when the clock reaches the preset alarm time.
 *
 * @param pRtc Pointer to the RTC controller.
 * @param bEnable Indicates whether to enable the interrupt. true: Enable interrupt, false: Disable interrupt.
 */
LOCAL_INLINE void RTC_HWA_EnableAlarmInterrupt(RTC_Type *const pRtc, bool bEnable)
{
	pRtc->IER = (pRtc->IER & ~(uint32_t)RTC_IER_TAIE_MASK) | RTC_IER_TAIE(bEnable);
}

/**
 * @brief Enables or disables the RTC second interrupt.
 *
 * This function modifies the RTC Interrupt Enable Register (IER) to enable or disable the RTC second interrupt.
 * Bit operations are used to ensure that other interrupt settings remain unchanged.
 *
 * @param pRtc A pointer to the RTC peripheral registers.
 * @param bEnable A boolean indicating whether to enable (true) or disable (false) the interrupt.
 */
LOCAL_INLINE void RTC_HWA_EnableSecondInterrupt(RTC_Type *const pRtc, bool bEnable)
{
	pRtc->IER = (pRtc->IER & ~(uint32_t)RTC_IER_TSIE_MASK) | RTC_IER_TSIE(bEnable);
}

/**
 * @brief Enables or disables the RTC overflow interrupt.
 *
 * This function sets or clears the TOIE bit in the RTC IER register to enable or disable the overflow interrupt.
 * When the TOIE bit is set, an interrupt request is generated by the RTC on counter overflow.
 *
 * @param pRtc Pointer to the RTC controller.
 * @param bEnable Boolean value indicating whether to enable (true) or disable (false) the interrupt.
 */
LOCAL_INLINE void RTC_HWA_EnableOverflowInterrupt(RTC_Type *const pRtc, bool bEnable)
{
	pRtc->IER = (pRtc->IER & ~(uint32_t)RTC_IER_TOIE_MASK) | RTC_IER_TOIE(bEnable);
}


/**
 * @brief Unlock lock/status/control/compensation register
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_UnlockStatusControlCompensationReg(RTC_Type *const pRtc)
{
	pRtc->LR |= (uint32_t)(RTC_LR_LRL_MASK | RTC_LR_STRL_MASK | RTC_LR_CRL_MASK | RTC_LR_CPL_MASK);
}

/**
 * @brief Set second interrupt and RTC_CLKOUT frequency
 *
 * @param pRtc the base address of the pRtc instance.
 * @param eFreq Frequency value
 */
LOCAL_INLINE void RTC_HWA_SetSecondAndClkoutFreq(RTC_Type *const pRtc, RTC_ClkoutSecIntFreqType eFreq)
{
    uint32_t u32RegValue = pRtc->IER;
    if (u32RegValue & RTC_IER_TSIE_MASK)
    {
    	pRtc->IER &= ~(uint32_t)RTC_IER_TSIE_MASK;
        pRtc->IER = (u32RegValue & ~(uint32_t)RTC_IER_TSIC_MASK) | RTC_IER_TSIC(eFreq);
    }
    else
    {
    	pRtc->IER = (u32RegValue & ~(uint32_t)RTC_IER_TSIC_MASK) | RTC_IER_TSIC(eFreq);
    }
}

/**
 * @brief Disable RTC time counter
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_DisableRtcCounter(RTC_Type *const pRtc)
{
	pRtc->STR &= ~(uint32_t)RTC_STR_TCE_MASK;
}

/**
 * @brief Set RTC_CLKOUT is from the prescaler output clock selected by IER[TSIC]
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_SetClkoutFromSelectFreq(RTC_Type *const pRtc)
{
	pRtc->CR &= ~(uint32_t)RTC_CR_CKPS_MASK;
}


/**
 * @brief Disable alarm interrupt
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_DisableAlarmInterrupt(RTC_Type *const pRtc)
{
	pRtc->IER &= ~(uint32_t)RTC_IER_TAIE_MASK;
}

/**
 * @brief Disable second interrupt
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_DisableSecondInterrupt(RTC_Type *const pRtc)
{
	pRtc->IER &= ~(uint32_t)RTC_IER_TSIE_MASK;
}


/**
 * @brief Disable overflow interrupt
 *
 * @param pRtc the base address of the pRtc instance.
 */
LOCAL_INLINE void RTC_HWA_DisableOverflowInterrupt(RTC_Type *const pRtc)
{
	pRtc->IER &= ~(uint32_t)RTC_IER_TOIE_MASK;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_RTC_H_ */
