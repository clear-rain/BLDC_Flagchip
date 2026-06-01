/**
 * @file HwA_adc.h
 * @author Flagchip030
 * @brief ADC hardware access layer
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

#ifndef _HWA_ADC_H_
#define _HWA_ADC_H_

#include "device_header.h"

#if ADC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_adc HwA_adc
 * @ingroup module_driver_adc
 * @{
 */

/**
 * @brief One ADC instance has 4 sample time options
 * 
 */
#define ADC_SAMPLE_TIME_OPTION_CNT 4U

/**
 * @brief Select the ADC Resolution
 *
 */
typedef enum
{
    ADC_RESOLUTION_12_BIT = 0U,  /**< 12 bit resolution */
    ADC_RESOLUTION_10_BIT = 1U,  /**< 10 bit resolution */
    ADC_RESOLUTION_8_BIT  = 2U,   /**< 8 bit resolution */
} ADC_ResolutionType;

/**
 * @brief Select the ADC result alignment
 *
 */
typedef enum
{
    ADC_ALIGN_RIGHT = 0U,   /**< ADC result is aligned in right */
    ADC_ALIGN_LEFT  = 1U    /**< ADC result is aligned in left */
} ADC_AlignType;

/**
 * @brief Select the ADC trigger mode
 *
 * @note This option is only valid in ADC single sequence mode and ADC continuous mode.
 * In ADC discontinuous mode, the ADC trigger mode is fixed as ADC_TRIGMODE_RISING_EDGE
 *
 */
typedef enum
{
    ADC_TRIGMODE_SW           = 0U,  /**< ADC is triggered by software */
    ADC_TRIGMODE_RISING_EDGE  = 1U,  /**< ADC is triggered by hardware trigger on rising edge */
    ADC_TRIGMODE_FALLING_EDGE = 2U,  /**< ADC is triggered by hardware trigger on falling edge */
    ADC_TRIGMODE_BOTH_EDGE    = 3U,  /**< ADC is triggered by hardware trigger on both edges */
    ADC_TRIGMODE_HIGH_VOLTAGE = 4U,  /**< ADC is triggered when hardware trigger is high voltage */
    ADC_TRIGMODE_LOW_VOLTAGE  = 5U   /**< ADC is triggered when hardware trigger is low voltage */
} ADC_TrigModeType;

/**
 * @brief Select the ADC sequence mode
 *
 */
typedef enum
{
    ADC_SEQMODE_SINGLE          = 0U,   /**< ADC single sequence mode */
    ADC_SEQMODE_CONTINUOUS      = 1U,   /**< ADC continuous mode */
    ADC_SEQMODE_DISCONTINUOUS_0 = 2U,   /**< ADC discontinuous 0 mode */
    ADC_SEQMODE_DISCONTINUOUS_1 = 3U    /**< ADC discontinuous 1 mode */
} ADC_SeqModeType;

/**
 * @brief Select the ADC overrun management mode
 *
 * To select whether the old data are preserved or overwritten by the new data when ADC
 * is overrun (The FIFO is full when new convertion result comes)
 *
 */
typedef enum
{
    ADC_OVERRUN_MODE_PRESERVE  = 0U, /**< old data are preserved when ADC is overrun */
    ADC_OVERRUN_MODE_OVERWRITE = 1U  /**< old data are overwritten when ADC is overrun */
} ADC_OvrModeType;

/**
 * @brief Select the ADC voltage reference source
 *
 */
typedef enum
{
    ADC_REF_INTERNAL = 0U,   /**< select the internal voltage reference */
    ADC_REF_EXTERNAL = 1U    /**< select the external voltage reference */
} ADC_RefType;

/**
 * @brief Select the ADC hardware average samples
 *
 */
typedef enum
{
    ADC_AVERAGE_4  = 0U,  /**< result average by 4 samples */
    ADC_AVERAGE_8  = 1U,  /**< result average by 8 samples */
    ADC_AVERAGE_16 = 2U,  /**< result average by 16 samples */
    ADC_AVERAGE_32 = 3U   /**< result average by 32 samples */
} ADC_AverageType;

/**
 * @brief Set the ADC clock divider
 * 
 * @note ADC clock divider is not available in FC4150F512K
 * 
 */
typedef enum
{
    ADC_CLOCK_DIV_1 = 0U,
    ADC_CLOCK_DIV_2 = 1U,
    ADC_CLOCK_DIV_4 = 2U,
    ADC_CLOCK_DIV_8 = 3U
} ADC_ClockDivideType;

/**
 * @brief The trigger source of the ADC instance
 *
 * @note In ADC discontinuous 1 mode, the trigger source is from SMISC
 * In ADC single and continuous mode, if hardware trigger is enabled, the trigger
 * source is from TRGSEL
 *
 */
typedef enum
{
    ADC_TRIGSRC_SMISC  = 0U,       /* Trigger source from PTIMER/TRGSEL with SMISC */
    ADC_TRIGSRC_TRGSEL = 2U        /* Trigger source from TRGSEL */
} ADC_TrigSrcType;

/**
 * @brief Select the ADC pretrigger source for discontinuous mode
 *
 * @note This option is only valid when ADC sequence mode is discontinuous. In ADC single
 * and continuous modes, the pretrigger is not needed
 *
 */
typedef enum
{
    ADC_PRETRIGGER_SEL_PTIMER     = 0x00U,   /**< PTIMER pretrigger selected. */
    ADC_PRETRIGGER_SEL_TRGSEL     = 0x01U,   /**< TRGSEL pretrigger selected. */
    ADC_PRETRIGGER_SEL_SW         = 0x02U    /**< Software pretrigger selected. */
} ADC_PreTriggerSelType;

/**
 * @brief Select the ADC trigger source for discontinuous mode
 *
 * @note This option is only valid when ADC sequence mode is discontinuous. In ADC single
 * and continuous modes, if the trigger mode is not software, then the hardware trigger
 * source is always from TRGSEL
 *
 */
typedef enum
{
    ADC_TRIGGER_SEL_PTIMER        = 0x00U,   /**< PTIMER trigger selected. */
    ADC_TRIGGER_SEL_TRGSEL        = 0x01U    /**< TRGSEL trigger selected. */
} ADC_TriggerSelType;

/**
 * @brief Select the software pretrigger source
 *
 * @note This option is only valid when software pretrigger is selected in ADC
 * discontinuous mode. Otherwise, this option is invalid and should not be configured
 *
 */
typedef enum
{
    ADC_SW_PRETRIGGER_DISABLED = 0x00U,   /**< SW pretrigger disabled. */
    ADC_SW_PRETRIGGER_0        = 0x04U,   /**< SW pretrigger 0. */
    ADC_SW_PRETRIGGER_1        = 0x05U,   /**< SW pretrigger 1. */
    ADC_SW_PRETRIGGER_2        = 0x06U,   /**< SW pretrigger 2. */
    ADC_SW_PRETRIGGER_3        = 0x07U    /**< SW pretrigger 3. */
} ADC_SwPreTriggerType;

/**
 * @brief Select the channel compare mode
 *
 * Select whether the channel compare is enabled on all channels or on the single
 * selected channel
 *
 */
typedef enum
{
    ADC_CMP_CHANNEL_ALL    = 0U,  /**< Compare enabled in all channels */
    ADC_CMP_CHANNEL_SINGLE = 1U   /**< Compare enabled in the specified channel */
} ADC_CmpChannelType;

/**
 * @brief Check whether the conversion result is in the comparing range
 *
 * @param pAdc the base address of the ADC instance
 * @return true the conversion result is in the comparing range
 * @return false the conversion result is not in the comparing range
 */
LOCAL_INLINE bool ADC_HWA_GetCompareFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_ACMP_MASK) >> ADC_INT_STATUS_ACMP_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the compare flag
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearCompareFlag(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_ACMP(1U);
}

/**
 * @brief Get the overrrun status of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return true the ADC is in overrun status
 * @return false the ADC is not overrun
 */
LOCAL_INLINE bool ADC_HWA_GetOverRun(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_OVR_MASK) >> ADC_INT_STATUS_OVR_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the overrun flag of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearOverRun(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_OVR(1U);
}

/**
 * @brief Check whether the ADC conversion sequence is finished
 *
 * @param pAdc the base address of the ADC instance
 * @return true the ADC conversion sequence is finished
 * @return false the ADC conversion sequence is unfinished
 */
LOCAL_INLINE bool ADC_HWA_GetEndOfSequence(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_EOSEQ_MASK) >> ADC_INT_STATUS_EOSEQ_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the ADC conversion sequence complete flag
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearEndOfSequence(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_EOSEQ(1U);
}

/**
 * @brief Check whether the current ADC conversion is finished
 *
 * @param pAdc the base address of the ADC instance
 * @return true the current ADC conversion is finished
 * @return false the current ADC conversion is unfinished
 */
LOCAL_INLINE bool ADC_HWA_GetEndOfConversion(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_EOC_MASK) >> ADC_INT_STATUS_EOC_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the ADC single conversion complete flag
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearEndOfConversion(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_EOC(1U);
}

/**
 * @brief Check whether the sampling phase of the current ADC conversion is finished
 *
 * @param pAdc the base address of the ADC instance
 * @return true the sampling phase of the ADC conversion is finished
 * @return false the sampling phase of the ADC conversion is unfinished
 */
LOCAL_INLINE bool ADC_HWA_GetEndOfSample(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_EOSMP_MASK) >> ADC_INT_STATUS_EOSMP_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the ADC sampling complete flag
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearEndOfSample(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_EOSMP(1U);
}

/**
 * @brief Check whether the data quantity in the FIFO is greater than watermark
 *
 * @param pAdc the base address of the ADC instance
 * @return true the ADC FIFO is ready
 * @return false the ADC FIFO is unready
 */
LOCAL_INLINE bool ADC_HWA_GetFIFOReady(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_FIFO_RDY_MASK) >> ADC_INT_STATUS_FIFO_RDY_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the FIFO ready flag
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearFIFOReady(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_FIFO_RDY(1U);
}

/**
 * @brief Check whether the ADC FIFO is full
 *
 * @param pAdc the base address of the ADC instance
 * @return true the ADC FIFO is full
 * @return false the ADC FIFO is not full
 */
LOCAL_INLINE bool ADC_HWA_GetFull(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_FULL_MASK) >> ADC_INT_STATUS_FULL_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Check whether the ADC FIFO is empty
 *
 * @param pAdc the base address of the ADC instance
 * @return true the ADC FIFO is empty
 * @return false the ADC FIFO is not empty
 */
LOCAL_INLINE bool ADC_HWA_GetEmpty(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_EMPTY_MASK) >> ADC_INT_STATUS_EMPTY_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Check whether the ADC instance is ready to operate
 *
 * @param pAdc the base address of the ADC instance
 * @return true the ADC instance is ready for a new conversion
 * @return false the ADC instance is unready
 */
LOCAL_INLINE bool ADC_HWA_GetReady(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_ADRDY_MASK) >> ADC_INT_STATUS_ADRDY_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Clear the ready flag of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearReady(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_ADRDY(1U);
}

/**
 * @brief Get the trigger error status of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return uint32_t The result has four bits, and each bit indicates that Trigger Latch Unit new
 * trigger request has been missed, because old request has already been latched or is being serviced.
 */
LOCAL_INLINE uint32_t ADC_HWA_GetTriggerErrorStatus(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_TRGERR_MASK) >> ADC_INT_STATUS_TRGERR_SHIFT;

    return (uint32_t)u32TmpVal;
}

/**
 * @brief Clear the trigger error of the specified trigger request
 *
 * @param pAdc the base address of the ADC instance
 * @param u32Request the trigger request to clear
 */
LOCAL_INLINE void ADC_HWA_ClearTriggerError(ADC_Type *const pAdc, uint32_t u32Request)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_TRGERR(1UL << u32Request);
}

/**
 * @brief Clear all of the trigger errors
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearTriggerErrors(ADC_Type *const pAdc)
{
    pAdc->INT_STATUS = ADC_INT_STATUS_TRGERR_MASK;
}

/**
 * @brief Get the trigger latch status of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return uint32_t The result has four bits, and each bit indicate that a Trigger Latch Unit
 * trigger request has been latched.
 */
LOCAL_INLINE uint32_t ADC_HWA_GetTriggerLatchStatus(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_TRG_STATUS_MASK) >> ADC_INT_STATUS_TRG_STATUS_SHIFT;
    return (uint32_t)u32TmpVal;
}

/**
 * @brief Clear the trigger latch status
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_ClearLatchedTriggers(ADC_Type *const pAdc)
{
#ifdef ADC_CLEAR_LATCH_TRIGGER_TOGGLE
    pAdc->CFG2 ^= ADC_CFG2_TRG_CLR_MASK;
#else
    pAdc->CFG2 |= ADC_CFG2_TRG_CLR_MASK;
#endif
}

/**
 * @brief Get the trigger process number
 * the trigger process number indicates the trigger number in Trigger Latch Unit that is being serviced
 *
 * @param pAdc the base address of the ADC instance
 * @return uint32_t the trigger process number
 */
LOCAL_INLINE uint32_t ADC_HWA_GetTriggerProcessNumber(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->INT_STATUS;
    u32TmpVal = (u32TmpVal & ADC_INT_STATUS_TRG_PRO_NUM_MASK) >> ADC_INT_STATUS_TRG_PRO_NUM_SHIFT;
    return (uint32_t)u32TmpVal;
}

/**
 * @brief Get the FIFO Ready interrupt flag
 * If enabled, ADC interrupt is generated when the FIFO water mark is greater than FWMARK
 * @param pAdc the base address of the ADC instance
 * @return true ADC FIFO Ready interrupt is enabled
 * @return false ADC FIFO Ready interrupt is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetFIFOReadyInterruptFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->INT_ENABLE & ADC_INT_ENABLE_FIFO_RDY_IE_MASK) >> ADC_INT_ENABLE_FIFO_RDY_IE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the FIFO Ready interrupt flag
 * If enabled, ADC interrupt is generated when the FIFO water mark is greater than FWMARK
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the ADC FIFO Ready interrupt
 */
LOCAL_INLINE void ADC_HWA_SetFIFOReadyInterruptFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->INT_ENABLE = (pAdc->INT_ENABLE & ~ADC_INT_ENABLE_FIFO_RDY_IE_MASK) | ADC_INT_ENABLE_FIFO_RDY_IE(bEnable);
}

/**
 * @brief Get the Compare interrupt flag
 * If enabled, ADC interrupt is generated when the ADC conversion result is not within the compare threshold
 * @param pAdc the base address of the ADC instance
 * @return true ADC Compare interrupt is enabled
 * @return false ADC Compare interrupt is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetCompareInterruptFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->INT_ENABLE & ADC_INT_ENABLE_ACMP_IE_MASK) >> ADC_INT_ENABLE_ACMP_IE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the Compare interrupt flag
 * If enabled, ADC interrupt is generated when the ADC conversion result is not within the compare threshold
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the ADC Compare interrupt
 */
LOCAL_INLINE void ADC_HWA_SetCompareInterruptFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->INT_ENABLE = (pAdc->INT_ENABLE & ~ADC_INT_ENABLE_ACMP_IE_MASK) | ADC_INT_ENABLE_ACMP_IE(bEnable);
}

/**
 * @brief Get the Overrun interrupt flag
 * If enabled, ADC interrupt is generated when the ADC instance is overrun
 * @param pAdc the base address of the ADC instance
 * @return true ADC Overrun interrupt is enabled
 * @return false ADC Overrun interrupt is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetOverrunInterruptFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->INT_ENABLE & ADC_INT_ENABLE_OVRIE_MASK) >> ADC_INT_ENABLE_OVRIE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the Overrun interrupt flag
 * If enabled, ADC interrupt is generated when the ADC instance is overrun
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the ADC Overrun interrupt
 */
LOCAL_INLINE void ADC_HWA_SetOverrunInterruptFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->INT_ENABLE = (pAdc->INT_ENABLE & ~ADC_INT_ENABLE_OVRIE_MASK) | ADC_INT_ENABLE_OVRIE(bEnable);
}

/**
 * @brief Get the End of Sequence interrupt enable flag
 * If enabled, ADC interrupt is generated when the ADC sequence conversion is completed
 * @param pAdc the base address of the ADC instance
 * @return true ADC End of Sequence interrupt is enabled
 * @return false ADC End of Sequence interrupt is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetEndOfSequenceInterruptFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->INT_ENABLE & ADC_INT_ENABLE_EOSEQIE_MASK) >> ADC_INT_ENABLE_EOSEQIE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the End of Sequence interrupt enable flag
 * If enabled, ADC interrupt is generated when the ADC sequence conversion is completed
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the ADC End of Sequence interrupt
 */
LOCAL_INLINE void ADC_HWA_SetEndOfSequenceInterruptFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->INT_ENABLE = (pAdc->INT_ENABLE & ~ADC_INT_ENABLE_EOSEQIE_MASK) | ADC_INT_ENABLE_EOSEQIE(bEnable);
}

/**
 * @brief Get the conversion complete interrupt enable flag
 * If enabled, ADC interrupt is generated when each ADC conversion is completed
 * @param pAdc the base address of the ADC instance
 * @return true the ADC End of Conversion interrupt is enabled
 * @return false the ADC End of Conversion interrupt is disabled
 */
LOCAL_INLINE bool ADC_HWAGetEndOfConversionInterruptFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->INT_ENABLE & ADC_INT_ENABLE_EOCIE_MASK) >> ADC_INT_ENABLE_EOCIE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the conversion complete interrupt enable flag
 * If enabled, ADC interrupt is generated when each ADC conversion is completed
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the conversion complete interrupt
 */
LOCAL_INLINE void ADC_HWA_SetEndOfConversionInterruptFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->INT_ENABLE = (pAdc->INT_ENABLE & ~ADC_INT_ENABLE_EOCIE_MASK) | ADC_INT_ENABLE_EOCIE(bEnable);
}

/**
 * @brief Get the sample complete interrupt enable flag
 * If enabled, ADC interrupt is generated when each ADC conversion finished the sampling phase
 * @param pAdc the base address of the ADC instance
 * @return true the sample complete interrupt is enabled
 * @return false the sample complete interrupt is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetEndOfSampleInterruptFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->INT_ENABLE & ADC_INT_ENABLE_EOSMPIE_MASK) >> ADC_INT_ENABLE_EOSMPIE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the sample complete interrupt enable flag
 * If enabled, ADC interrupt is generated when each ADC conversion finished the sampling phase
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the sample complete interrupt
 */
LOCAL_INLINE void ADC_HWA_SetEndOfSampleInterruptFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->INT_ENABLE = (pAdc->INT_ENABLE & ~ADC_INT_ENABLE_EOSMPIE_MASK) | ADC_INT_ENABLE_EOSMPIE(bEnable);
}

/**
 * @brief Get the ADC ready interrupt enable flag
 * If enabled, ADC interrupt is generated when the ADC module is ready for conversion
 * @param pAdc the base address of the ADC instance
 * @return true the ADC ready interrupt is enabled
 * @return false the ADC ready interrupt is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetADCReadyInterruptFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->INT_ENABLE & ADC_INT_ENABLE_ADRDYIE_MASK) >> ADC_INT_ENABLE_ADRDYIE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the ADC ready interrupt enable flag
 * If enabled, ADC interrupt is generated when the ADC module is ready for conversion
 * @param pAdc the base address of the ADC instance
 * @param bEnable Whether to enable the ADC ready interrupt
 */
LOCAL_INLINE void ADC_HWA_SetADCReadyInterruptFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->INT_ENABLE = (pAdc->INT_ENABLE & ~ADC_INT_ENABLE_ADRDYIE_MASK) | ADC_INT_ENABLE_ADRDYIE(bEnable);
}

/**
 * @brief Get the interrupt enable config
 *
 * @param pAdc the base address of the ADC instance
 * @return uint32_t the interrupt enable config
 */
LOCAL_INLINE uint32_t ADC_HWA_GetInterruptEnable(const ADC_Type *const pAdc)
{
    return pAdc->INT_ENABLE;
}

/**
 * @brief Set the interrupt enable
 *
 * @param pAdc ADC type point
 * @param u32InterruptCfg the interrupt enable config
 */
LOCAL_INLINE void ADC_HWA_SetInterruptEnable(ADC_Type *const pAdc, uint32_t u32InterruptCfg)
{
    pAdc->INT_ENABLE = u32InterruptCfg;
}

/**
 * @brief Reset the ADC hardware
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_Reset(ADC_Type *const pAdc)
{
    pAdc->CONTROL = ADC_CONTROL_ADRST(1U);
    pAdc->CONTROL = 0U;
}

/**
 * @brief Get the enable status of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return true the ADC instance is enabled
 * @return false the ADC instance has not been enabled
 */
LOCAL_INLINE bool ADC_HWA_GetEnable(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CONTROL;
    u32TmpVal = (u32TmpVal & ADC_CONTROL_ADEN_MASK) >> ADC_CONTROL_ADEN_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_Enable(ADC_Type *const pAdc)
{
    pAdc->CONTROL = ADC_CONTROL_ADEN(1U);
}

/**
 * @brief Get whether the ADC instance is in disable status
 * 
 * @param pAdc the base address of the ADC instance
 * @return true the ADC instance is in disable status
 * @return false the ADC instance is not in disable status
 */
LOCAL_INLINE bool ADC_HWA_GetDisable(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CONTROL;
    u32TmpVal = (u32TmpVal & ADC_CONTROL_ADDIS_MASK) >> ADC_CONTROL_ADDIS_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Disable the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_Disable(ADC_Type *const pAdc)
{
    pAdc->CONTROL = ADC_CONTROL_ADDIS(1U);
}

/**
 * @brief Get the conversion start status of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return true the conversion of the ADC instance is started
 * @return false the conversion of the ADC instance has not been started
 */
LOCAL_INLINE bool ADC_HWA_GetStart(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CONTROL;
    u32TmpVal = (u32TmpVal & ADC_CONTROL_ADSTART_MASK) >> ADC_CONTROL_ADSTART_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Start the ADC conversion
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_Start(ADC_Type *const pAdc)
{
    pAdc->CONTROL = ADC_CONTROL_ADSTART(1U);
}

/**
 * @brief Get whether ADC is in stopping status
 * 
 * @param pAdc the base address of the ADC instance
 * @return true the ADC instance is stopping
 * @return false the ADC instance is not in stopping status
 */
LOCAL_INLINE bool ADC_HWA_GetStop(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CONTROL;
    u32TmpVal = (u32TmpVal & ADC_CONTROL_ADSTP_MASK) >> ADC_CONTROL_ADSTP_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Stop the ADC conversion
 *
 * @param pAdc the base address of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_Stop(ADC_Type *const pAdc)
{
    pAdc->CONTROL = ADC_CONTROL_ADSTP(1U);
}

/**
 * @brief Get whether the ADC is in differential mode
 * 
 * @note Differential mode is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @return true the ADC is in differential mode
 * @return false the ADC is not in differential mode 
 */
LOCAL_INLINE bool ADC_HWA_GetDifferentialModeEnableFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CFG1;
    u32TmpVal = (u32TmpVal & ADC_CFG1_DIFF_MASK) >> ADC_CFG1_DIFF_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable the ADC differential mode
 * 
 * @note Differential mode is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the ADC differential mode
 */
LOCAL_INLINE void ADC_HWA_SetDifferentialModeEnableFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_DIFF_MASK) | ADC_CFG1_DIFF(bEnable);
}

/**
 * @brief Get the overrun management mode
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_OVERRUN_MODE_PRESERVE the conversion data is preserved when ADC is overrun
 * @return ADC_OVERRUN_MODE_OVERWRITE the conversion data is overwritten when ADC is overrun
 */
LOCAL_INLINE ADC_OvrModeType ADC_HWA_GetOverrunManagementMode(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG1 & ADC_CFG1_OVRMOD_MASK) >> ADC_CFG1_OVRMOD_SHIFT;
    return (ADC_OvrModeType)u32TmpVal;
}

/**
 * @brief Set the overrun management mode
 *
 * @param pAdc the base address of the ADC instance
 * @param eOvrMode the overrun management for the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetOverrunManagementMode(ADC_Type *const pAdc, ADC_OvrModeType eOvrMode)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_OVRMOD_MASK) | ADC_CFG1_OVRMOD(eOvrMode);
}

/**
 * @brief Get the sequence length of the ADC conversion sequence
 *
 * @param pAdc the base address of the ADC instance
 * @return uint8_t the sequence length of the ADC conversion sequence
 */
LOCAL_INLINE uint8_t ADC_HWA_GetSequenceLength(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CFG1;
    u32TmpVal = (u32TmpVal & ADC_CFG1_SEQ_LEN_MASK) >> ADC_CFG1_SEQ_LEN_SHIFT;

    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set the sequence length of the ADC conversion sequence
 *
 * @param pAdc the base address of the ADC instance
 * @param u8SequenceLength the sequence length of the ADC conversion sequence
 */
LOCAL_INLINE void ADC_HWA_SetSequenceLength(ADC_Type *const pAdc, uint8_t u8SequenceLength)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_SEQ_LEN_MASK) | ADC_CFG1_SEQ_LEN(u8SequenceLength);
}

/**
 * @brief Get the ADC sequence mode
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_SeqModeType the sequence mode the the ADC instance
 */
LOCAL_INLINE ADC_SeqModeType ADC_HWA_GetSequenceMode(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CFG1;
    u32TmpVal = (u32TmpVal & ADC_CFG1_SEQ_MOD_MASK) >> ADC_CFG1_SEQ_MOD_SHIFT;

    return (ADC_SeqModeType)u32TmpVal;
}

/**
 * @brief Set the ADC sequence mode
 *
 * @param pAdc the base address of the ADC instance
 * @param eSequenceMode the sequence mode the the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetSequenceMode(ADC_Type *const pAdc, ADC_SeqModeType eSequenceMode)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_SEQ_MOD_MASK) | ADC_CFG1_SEQ_MOD(eSequenceMode);
}

/**
 * @brief Get whether auto disable is enabled
 * 
 * @note Auto disable mode is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @return true  auto disable mode is enabled
 * @return false auto disable mode is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetAutoDisableModeEnableFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CFG1;
    u32TmpVal = (u32TmpVal & ADC_CFG1_AUTO_DIS_MASK) >> ADC_CFG1_AUTO_DIS_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable auto disable mode
 * 
 * @note Auto disable mode is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable auto disable mode
 */
LOCAL_INLINE void ADC_HWA_SetAutoDisableModeEnableFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_AUTO_DIS_MASK) | ADC_CFG1_AUTO_DIS(bEnable);
}

/**
 * @brief Get whether the wait conversion mode is enabled
 *
 * @param pAdc the base address of the ADC instance
 * @return true the wait conversion mode is enabled
 * @return false the wait conversion mode is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetWaitConversionModeFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG1 & ADC_CFG1_WAIT_MASK) >> ADC_CFG1_WAIT_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set the wait conversion mode
 *
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the wait conversion mode
 */
LOCAL_INLINE void ADC_HWA_SetWaitConversionModeFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_WAIT_MASK) | ADC_CFG1_WAIT(bEnable);
}

/**
 * @brief Get the trigger source the the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_TrigSrcType the trigger source of the ADC instance
 */
LOCAL_INLINE ADC_TrigSrcType ADC_HWA_GetTriggerSource(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CFG1;
    u32TmpVal = (u32TmpVal & ADC_CFG1_TRIGSRC_MASK) >> ADC_CFG1_TRIGSRC_SHIFT;

    return (ADC_TrigSrcType)u32TmpVal;
}

/**
 * @brief Set the trigger source the the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param eTriggerSource the trigger source of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetTriggerSource(ADC_Type *const pAdc, ADC_TrigSrcType eTriggerSource)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_TRIGSRC_MASK) | ADC_CFG1_TRIGSRC(eTriggerSource);
}

/**
 * @brief Get the trigger mode of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_TrigModeType the trigger mode if the ADC instance
 */
LOCAL_INLINE ADC_TrigModeType ADC_HWA_GetTriggerMode(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->CFG1;
    u32TmpVal = (u32TmpVal & ADC_CFG1_TRIGMODE_MASK) >> ADC_CFG1_TRIGMODE_SHIFT;

    return (ADC_TrigModeType)u32TmpVal;
}

/**
 * @brief Set the trigger mode of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param eTriggerMode the trigger mode if the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetTriggerMode(ADC_Type *const pAdc, ADC_TrigModeType eTriggerMode)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_TRIGMODE_MASK) | ADC_CFG1_TRIGMODE(eTriggerMode);
}

/**
 * @brief Get the data align mode
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_ALIGN_RIGHT the conversion data is aligned right
 * @return ADC_ALIGN_LEFT the conversion is aligned left
 */
LOCAL_INLINE ADC_AlignType ADC_HWA_GetDataAlignment(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG1 & ADC_CFG1_ALIGN_MASK) >> ADC_CFG1_ALIGN_SHIFT;
    return (ADC_AlignType)u32TmpVal;
}

/**
 * @brief Set the data align mode
 *
 * @param pAdc the base address of the ADC instance
 * @param eAlign the data align mode
 */
LOCAL_INLINE void ADC_HWA_SetDataAlignment(ADC_Type *const pAdc, ADC_AlignType eAlign)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_ALIGN_MASK) | ADC_CFG1_ALIGN(eAlign);
}

/**
 * @brief Get the ADC resolution of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_ResolutionType the resolution of the ADC instance
 */
LOCAL_INLINE ADC_ResolutionType ADC_HWA_GetDataResolution(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG1 & ADC_CFG1_RES_MASK) >> ADC_CFG1_RES_SHIFT;
    return (ADC_ResolutionType)u32TmpVal;
}

/**
 * @brief Set the resolution of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param eResolution the resolution of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetDataResolution(ADC_Type *const pAdc, ADC_ResolutionType eResolution)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_RES_MASK) | ADC_CFG1_RES(eResolution);
}

/**
 * @brief Get whether DMA for the ADC instance is enabled
 *
 * @param pAdc the base address of the ADC instance
 * @return true DMA is enabled for the ADC instance
 * @return false DMA is disabled for the ADC instance
 */
LOCAL_INLINE bool ADC_HWA_GetDMAEnableFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG1 & ADC_CFG1_DMAEN_MASK) >> ADC_CFG1_DMAEN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable or disable the DMA for the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the DMA for the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetDMAEnableFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->CFG1 = (pAdc->CFG1 & ~ADC_CFG1_DMAEN_MASK) | ADC_CFG1_DMAEN(bEnable);
}

/**
 * @brief Get the ADC_CFG1 config
 *
 * @param pAdc the base address of the ADC instance
 * @return uint32_t the ADC_CFG1 config
 */
LOCAL_INLINE uint32_t ADC_HWA_GetConfig1(const ADC_Type *const pAdc)
{
    return pAdc->CFG1;
}

/**
 * @brief Set the ADC_CFG1 config
 *
 * @param pAdc the base address of the ADC instance
 * @param u32Config the ADC_CFG1 config
 */
LOCAL_INLINE void ADC_HWA_SetConfig1(ADC_Type *const pAdc, uint32_t u32Config)
{
    pAdc->CFG1 = u32Config;
}

/**
 * @brief Get the FIFO water mark settings for the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return uint8_t the ADC FIFO water mark setting
 */
LOCAL_INLINE uint8_t ADC_HWA_GetFIFOWaterMark(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_FWMARK_MASK) >> ADC_CFG2_FWMARK_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set the FIFO water mark for the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param u8WaterMark the ADC FIFO water mark setting
 */
LOCAL_INLINE void ADC_HWA_SetFIFOWaterMark(ADC_Type *const pAdc, uint8_t u8WaterMark)
{
    pAdc->CFG2 = (pAdc->CFG2 & ~ADC_CFG2_FWMARK_MASK) | ADC_CFG2_FWMARK(u8WaterMark);
}

/**
 * @brief Get whether hardware average is enabled
 *
 * @param pAdc the base address of the ADC instance
 * @return true hardware average is enabled
 * @return false hardware average is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetAverageEnableFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_AVG_EN_MASK) >> ADC_CFG2_AVG_EN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable or disable hardware average for the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable the ADC hardware average
 */
LOCAL_INLINE void ADC_HWA_SetAverageEnableFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->CFG2 = (pAdc->CFG2 & ~ADC_CFG2_AVG_EN_MASK) | ADC_CFG2_AVG_EN(bEnable);
}

/**
 * @brief Get the hardware average number
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_AverageType the hardware average number
 */
LOCAL_INLINE ADC_AverageType ADC_HWA_GetAverageNumber(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_AVG_LEN_MASK) >> ADC_CFG2_AVG_LEN_SHIFT;
    return (ADC_AverageType)u32TmpVal;
}

/**
 * @brief Set the hardware average number
 *
 * @param pAdc the base address of the ADC instance
 * @param eAverageNumber the hardware average number to set
 */
LOCAL_INLINE void ADC_HWA_SetAverageNumber(ADC_Type *const pAdc, ADC_AverageType eAverageNumber)
{
    pAdc->CFG2 = (pAdc->CFG2 & ~ADC_CFG2_AVG_LEN_MASK) | ADC_CFG2_AVG_LEN(eAverageNumber);
}
/**
 * @brief Whether clock gating is acknowledged
 * 
 * @note This feature is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @return true ADC clock source is off after setting Clock Gating Enable Flag
 * @return false ADC clock source is on after clearing Clock Gating Enable Flag
 */
LOCAL_INLINE bool ADC_HWA_GetClockGatingAck(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_CG_ACK_MASK) >> ADC_CFG2_CG_ACK_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get whether clock gating is enabled
 * 
 * @note This feature is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @return true Clock gating is enabled, ADC clock is off
 * @return false Clock gating is disabled, ADC clock is on 
 */
LOCAL_INLINE bool ADC_HWA_GetClockGatingEnableFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_CG_MASK) >> ADC_CFG2_CG_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable ADC clock gating
 * 
 * @note This feature is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether to enable ADC clock gating
 */
LOCAL_INLINE void ADC_HWA_SetClockGatingEnableFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->CFG2 = (pAdc->CFG2 & ~ADC_CFG2_CG_MASK) | ADC_CFG2_CG(bEnable);
}

/**
 * @brief Get the voltage reference of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_REF_INTERNAL the ADC instance uses internal voltage reference
 * @return ADC_REF_EXTERNAL the ADC instance uses external voltage reference
 */
LOCAL_INLINE ADC_RefType ADC_HWA_GetVoltageReference(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_REF_EXT_MASK) >> ADC_CFG2_REF_EXT_SHIFT;
    return (ADC_RefType)u32TmpVal;
}

/**
 * @brief Set the voltage reference of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param eRefSel the voltage reference of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetVoltageReference(ADC_Type *const pAdc, ADC_RefType eRefSel)
{
    pAdc->CFG2 = (pAdc->CFG2 & ~ADC_CFG2_REF_EXT_MASK) | ADC_CFG2_REF_EXT(eRefSel);
}

/**
 * @brief Get the ADC clock divider
 * 
 * @note This feature is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @return ADC_ClockDivideType the ADC clock divider
 */
LOCAL_INLINE ADC_ClockDivideType ADC_HWA_GetClockDivider(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_DIV_MASK) >> ADC_CFG2_DIV_SHIFT;
    return (ADC_ClockDivideType)u32TmpVal;
}

/**
 * @brief Set the ADC clock divider
 * 
 * @note Before configuring DIV, must set CG and wait for CG_ACK=1.
 *       After configuring DIV, must clear CG and wait for CG_ACK=0.
 * @note This feature is only available in FC4150F2M
 * 
 * @param pAdc the base address of the ADC instance
 * @param eDivider the ADC clock divider to set
 */
LOCAL_INLINE void ADC_HWA_SetClockDivider(ADC_Type *const pAdc, ADC_ClockDivideType eDivider)
{
    pAdc->CFG2 = (pAdc->CFG2 & ~ADC_CFG2_DIV_MASK) | ADC_CFG2_DIV(eDivider);
}

/**
 * @brief Get the ADC start up count
 *
 * @param pAdc the base address of the ADC instance
 * @return uint8_t the start count of the ADC instance
 */
LOCAL_INLINE uint8_t ADC_HWA_GetStartupCnt(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CFG2 & ADC_CFG2_STCNT_MASK) >> ADC_CFG2_STCNT_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set the ADC start up count
 *
 * @param pAdc the base address of the ADC instance
 * @param u8StartupCnt the start count of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetStartupCnt(ADC_Type *const pAdc, uint8_t u8StartupCnt)
{
    pAdc->CFG2 = (pAdc->CFG2 & ~ADC_CFG2_STCNT_MASK) | ADC_CFG2_STCNT(u8StartupCnt);
}

/**
 * @brief Get the ADC_CFG2 config
 *
 * @param pAdc the base address of the ADC instance
 * @return uint32_t the ADC_CFG2 config
 */
LOCAL_INLINE uint32_t ADC_HWA_GetConfig2(const ADC_Type *const pAdc)
{
    return pAdc->CFG2;
}

/**
 * @brief Set the ADC_CFG2 config
 *
 * @param pAdc the base address of the ADC instance
 * @param u32Config the ADC_CFG2 config
 */
LOCAL_INLINE void ADC_HWA_SetConfig2(ADC_Type *const pAdc, uint32_t u32Config)
{
    pAdc->CFG2 = u32Config;
}

/**
 * @brief Get the sample time of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param u8Selection the sample time index, range 0~3
 * @return uint8_t the sample time of the selected index
 */
LOCAL_INLINE uint8_t ADC_HWA_GetSampleTime(ADC_Type *const pAdc, uint8_t u8Selection)
{
    uint32_t ret;
    ret = (pAdc->SMPR & (ADC_SMPR_SMP_OPT0_MASK << (8U * u8Selection))) >> (8U * u8Selection);
    return (uint8_t)ret;
}

/**
 * @brief Set the sample time of the ADC instance
 *
 * @param pAdc the base address of the ADC instance
 * @param u8Selection the sample time index, range 0~3
 * @param u8SampleTime the sample time of the selected index
 */
LOCAL_INLINE void ADC_HWA_SetSampleTime(ADC_Type *const pAdc, uint8_t u8Selection, uint8_t u8SampleTime)
{
    DEV_ASSERT(u8Selection < ADC_SAMPLE_TIME_OPTION_CNT);
    pAdc->SMPR = (pAdc->SMPR & ~(ADC_SMPR_SMP_OPT0_MASK << (8U * u8Selection))) |
                 (ADC_SMPR_SMP_OPT0(u8SampleTime) << (8U * u8Selection));
}

/**
 * @brief Set the ADC hardware compare channel
 *
 * @param pAdc the base address of the ADC instance
 * @param eChannelType whether the hardware compare enabled on single channel or all channels
 * @param u8ChannalNum if hardware compare is enabled on single channel, this specifies the channel number
 */
LOCAL_INLINE void ADC_HWA_SetHwCompareChannel(ADC_Type *const pAdc, ADC_CmpChannelType eChannelType,
                                              uint8_t u8ChannalNum)
{
    pAdc->CMP_CTRL = (pAdc->CMP_CTRL & (~ADC_CMP_CTRL_ACMPSGL_MASK) & (~ADC_CMP_CTRL_ACMPCH_MASK)) |
                     ADC_CMP_CTRL_ACMPSGL(eChannelType) | ADC_CMP_CTRL_ACMPCH(u8ChannalNum);
}

/**
 * @brief Get whether hardware compare is enabled
 *
 * @param pAdc the base address of the ADC instance
 * @return true hardware compare is enabled
 * @return false hardware compare is disabled
 */
LOCAL_INLINE bool ADC_HWA_GetHwCompareEnableFlag(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = (pAdc->CMP_CTRL & ADC_CMP_CTRL_ACMPEN_MASK) >> ADC_CMP_CTRL_ACMPEN_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set to enable or disable the hardware compare
 *
 * @param pAdc the base address of the ADC instance
 * @param bEnable whether the ADC hardware compare is enabled
 */
LOCAL_INLINE void ADC_HWA_SetHwCompareEnableFlag(ADC_Type *const pAdc, bool bEnable)
{
    pAdc->CMP_CTRL = (pAdc->CMP_CTRL & ~ADC_CMP_CTRL_ACMPEN_MASK) | ADC_CMP_CTRL_ACMPEN(bEnable);
}

/**
 * @brief Set the ADC hardware compare threshold
 *
 * @param pAdc the base address of the ADC instance
 * @param u16LowThres the lower threshold
 * @param u16HighThres the higher threshold
 */
LOCAL_INLINE void ADC_HWA_SetHwCompareThreshold(ADC_Type *const pAdc, uint16_t u16LowThres, uint16_t u16HighThres)
{
    pAdc->CMP_TR = ADC_CMP_TR_LT(u16LowThres) | ADC_CMP_TR_HT(u16HighThres);
}

/**
 * @brief Get the conversion result FIFO data of the ADC instance
 *
 * @note only reslut data of ADC single mode and continuous mode will be stored
 * in FIFO register.
 *
 * @param pAdc the base address of the ADC instance
 * @return uint32_t the ADC conversion result
 */
LOCAL_INLINE uint32_t ADC_HWA_GetFIFOData(const ADC_Type *const pAdc)
{
    uint32_t u32TmpVal = pAdc->FIFO_DATA;
    u32TmpVal = (u32TmpVal & ADC_FIFO_DATA_FIFO_DATA_MASK) >> ADC_FIFO_DATA_FIFO_DATA_SHIFT;
    return (uint32_t)u32TmpVal;
}

/**
 * @brief Get the sample time index of the ADC channel
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the channel
 * @return uint8_t the sample time index of the ADC channel
 */
LOCAL_INLINE uint8_t ADC_HWA_GetChannelSampleTimeIndex(const ADC_Type *const pAdc, const uint8_t u8ChnIdx)
{
    uint32_t u32TmpVal = (pAdc->SC[u8ChnIdx] & ADC_SC_SMPSEL_MASK) >> ADC_SC_SMPSEL_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set the sample time index of the ADC channel
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the channel
 * @param u8SmpSel the sample time index of the ADC channel
 */
LOCAL_INLINE void ADC_HWA_SetChannelSampleTimeIndex(ADC_Type *const pAdc, const uint8_t u8ChnIdx, uint8_t u8SmpSel)
{
    pAdc->SC[u8ChnIdx] = (pAdc->SC[u8ChnIdx] & ~ADC_SC_SMPSEL_MASK) | ADC_SC_SMPSEL(u8SmpSel);
}

/**
 * @brief Get the channel conversion complete status of the ADC instance
 *
 * @note this function is used only in ADC discontinuous mode to get the channel complete
 * status
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the channel
 * @return true the ADC conversion on the selected channel is completed
 * @return false the ADC conversion on the selected channel is not completed
 */
LOCAL_INLINE bool ADC_HWA_GetChannelConvertComplete(const ADC_Type *const pAdc, const uint8_t u8ChnIdx)
{
    uint32_t u32TmpVal = pAdc->SC[u8ChnIdx];
    u32TmpVal = (u32TmpVal & ADC_SC_COCO_MASK) >> ADC_SC_COCO_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Check whether interrupt is enabled on the selected ADC channel
 *
 * @note this function is used only in ADC discontinuous mode to get the channel interrupt
 * settings
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the channel
 * @return true interrupt is enabled on the selected channel
 * @return false interrupt is disabled on the selected channel
 */
LOCAL_INLINE bool ADC_HWA_GetChannelInterruptEnable(const ADC_Type *const pAdc, const uint8_t u8ChnIdx)
{
    uint32_t u32TmpVal = pAdc->SC[u8ChnIdx];
    u32TmpVal = (u32TmpVal & ADC_SC_AIEN_MASK) >> ADC_SC_AIEN_SHIFT;

    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set to enable or disable interrupt on the selected ADC channel
 *
 * @note this function is used only in ADC discontinuous mode to get the channel interrupt
 * settings
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the channel
 * @param bEnable whether to enable interrupt on the selected ADC channel
 */
LOCAL_INLINE void ADC_HWA_SetChannelInterruptEnable(ADC_Type *const pAdc, const uint8_t u8ChnIdx, bool bEnable)
{
    pAdc->SC[u8ChnIdx] = (pAdc->SC[u8ChnIdx] & ~ADC_SC_AIEN_MASK) | ADC_SC_AIEN(bEnable);
}

/**
 * @brief Get the input channel of the selected ADC channel
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the channel
 * @return uint8_t the hardware input channel
 */
LOCAL_INLINE uint8_t ADC_HWA_GetChannelInput(const ADC_Type *const pAdc, const uint8_t u8ChnIdx)
{
    uint32_t u32TmpVal = (pAdc->SC[u8ChnIdx] & ADC_SC_CHS_MASK) >> ADC_SC_CHS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set the input channel to the selected ADC channel
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the channel
 * @param u8InputChann the hardware input channel
 */
LOCAL_INLINE void ADC_HWA_SetChannelInput(ADC_Type *const pAdc, const uint8_t u8ChnIdx, uint8_t u8InputChann)
{
    pAdc->SC[u8ChnIdx] = (pAdc->SC[u8ChnIdx] & ~ADC_SC_CHS_MASK) | ADC_SC_CHS(u8InputChann);
}

/**
 * @brief Get the conversion result data of the ADC instance
 *
 * @note only result data of ADC discontinuous mode will be stored in RESULTn register.
 *
 * @param pAdc the base address of the ADC instance
 * @param u8ChnIdx the index of the ADC channel
 * @return uint32_t the ADC conversion result
 */
LOCAL_INLINE uint32_t ADC_HWA_GetChannelData(const ADC_Type *const pAdc, const uint8_t u8ChnIdx)
{
    uint32_t u32TmpVal = pAdc->RESULT[u8ChnIdx];
    u32TmpVal = (u32TmpVal & ADC_RESULT_RESULT_MASK) >> ADC_RESULT_RESULT_SHIFT;

    return (uint32_t)u32TmpVal;
}

/**
 * @brief Get the pretrigger source of the ADC instance
 *
 * @note The pretrigger is used only in ADC discontinuous 1 mode
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_PreTriggerSelType the pretrigger source of the ADC instance
 */
LOCAL_INLINE ADC_PreTriggerSelType ADC_HWA_GetPreTriggerSelect(const ADC_Type *const pAdc)
{
    const SMISC_Type *const pSmisc = SMISC;
    uint32_t u32TmpVal = pSmisc->ADCOPTR;
    if (pAdc == ADC0)
    {
        u32TmpVal = (u32TmpVal & SMISC_ADCOPTR_ADC0PRETRGSEL_MASK) >> SMISC_ADCOPTR_ADC0PRETRGSEL_SHIFT;
    }
    else if (pAdc == ADC1)
    {
        u32TmpVal = (u32TmpVal & SMISC_ADCOPTR_ADC1PRETRGSEL_MASK) >> SMISC_ADCOPTR_ADC1PRETRGSEL_SHIFT;
    }
    else
    {
        /* This should never be reached */
        u32TmpVal = ADC_PRETRIGGER_SEL_PTIMER;
    }

    return (ADC_PreTriggerSelType)u32TmpVal;
}

/**
 * @brief Configure the software pretrigger source for ADC
 *
 * @note The pretrigger is used only in ADC discontinuous 1 mode
 *
 * @param pAdc the base address of the ADC instance
 * @param eSwPretrigger the software pretrigger source to use
 */
LOCAL_INLINE void ADC_HWA_SetSwPretriggerSelect(ADC_Type *const pAdc, const ADC_SwPreTriggerType eSwPretrigger)
{
    SMISC_Type *const pSmisc = SMISC;

    if (pAdc == ADC0)
    {
        pSmisc->ADCOPTR = (pSmisc->ADCOPTR & (~SMISC_ADCOPTR_ADC0SWPRETRG_MASK)) | SMISC_ADCOPTR_ADC0SWPRETRG(eSwPretrigger);
    }
    else if (pAdc == ADC1)
    {
        pSmisc->ADCOPTR = (pSmisc->ADCOPTR & (~SMISC_ADCOPTR_ADC1SWPRETRG_MASK)) | SMISC_ADCOPTR_ADC1SWPRETRG(eSwPretrigger);
    }
    else
    {
        /* This should never be reached */
    }
}

/**
 * @brief Get the pretrigger source of the ADC instance
 *
 * @note The pretrigger is used only in ADC discontinuous 1 mode
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_PreTriggerSelType the pretrigger source of the ADC instance
 */
LOCAL_INLINE ADC_PreTriggerSelType ADC_HWA_GetPretriggerSelect(const ADC_Type *const pAdc)
{
    const SMISC_Type *const pSmisc = SMISC;
    uint32_t u32TmpVal = pSmisc->ADCOPTR;
    if (pAdc == ADC0)
    {
        u32TmpVal = (u32TmpVal & SMISC_ADCOPTR_ADC0PRETRGSEL_MASK) >> SMISC_ADCOPTR_ADC0PRETRGSEL_SHIFT;
    }
    else if (pAdc == ADC1)
    {
        u32TmpVal = (u32TmpVal & SMISC_ADCOPTR_ADC1PRETRGSEL_MASK) >> SMISC_ADCOPTR_ADC1PRETRGSEL_SHIFT;
    }
    else
    {
        /* This should never be reached */
    }
    return (ADC_PreTriggerSelType)u32TmpVal;
}

/**
 * @brief Set the pretrigger source of the ADC instance
 *
 * @note The pretrigger is used only in ADC discontinuous 1 mode
 *
 * @param pAdc the base address of the ADC instance
 * @param ePretriggerSel the pretrigger source of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetPretriggerSelect(ADC_Type *const pAdc, ADC_PreTriggerSelType ePretriggerSel)
{
    SMISC_Type *const pSmisc = SMISC;

    if (pAdc == ADC0)
    {
        pSmisc->ADCOPTR = (pSmisc->ADCOPTR & ~SMISC_ADCOPTR_ADC0PRETRGSEL_MASK) | SMISC_ADCOPTR_ADC0PRETRGSEL(ePretriggerSel);
    }
    else if (pAdc == ADC1)
    {
        pSmisc->ADCOPTR = (pSmisc->ADCOPTR & ~SMISC_ADCOPTR_ADC1PRETRGSEL_MASK) | SMISC_ADCOPTR_ADC1PRETRGSEL(ePretriggerSel);
    }
    else
    {
        /* This should never be reached */
    }
}

/**
 * @brief Get the trigger source of the ADC instance
 *
 * @note this trigger source setting is only used in ADC discontinuous 1 mode
 *
 * @param pAdc the base address of the ADC instance
 * @return ADC_TriggerSelType the trigger source of the ADC instance
 */
LOCAL_INLINE ADC_TriggerSelType ADC_HWA_GetTriggerSelect(const ADC_Type *const pAdc)
{
    const SMISC_Type *const pSmisc = SMISC;
    uint32_t u32TmpVal = pSmisc->ADCOPTR;
    if (pAdc == ADC0)
    {
        u32TmpVal = (u32TmpVal & SMISC_ADCOPTR_ADC0TRGSEL_MASK) >> SMISC_ADCOPTR_ADC0TRGSEL_SHIFT;
    }
    else if (pAdc == ADC1)
    {
        u32TmpVal = (u32TmpVal & SMISC_ADCOPTR_ADC1TRGSEL_MASK) >> SMISC_ADCOPTR_ADC1TRGSEL_SHIFT;
    }
    else
    {
        /* This should never be reached */
    }
    return (ADC_TriggerSelType)u32TmpVal;
}

/**
 * @brief Set the trigger source of the ADC instance
 *
 * @note this trigger source setting is only used in ADC discontinuous 1 mode
 *
 * @param pAdc the base address of the ADC instance
 * @param eTriggerSel the trigger source of the ADC instance
 */
LOCAL_INLINE void ADC_HWA_SetTriggerSelect(ADC_Type *const pAdc, ADC_TriggerSelType eTriggerSel)
{
    SMISC_Type *const pSmisc = SMISC;

    if (pAdc == ADC0)
    {
        pSmisc->ADCOPTR = (pSmisc->ADCOPTR & ~SMISC_ADCOPTR_ADC0TRGSEL_MASK) | SMISC_ADCOPTR_ADC0TRGSEL(eTriggerSel);
    }
    else if (pAdc == ADC1)
    {
        pSmisc->ADCOPTR = (pSmisc->ADCOPTR & ~SMISC_ADCOPTR_ADC1TRGSEL_MASK) | SMISC_ADCOPTR_ADC1TRGSEL(eTriggerSel);
    }
    else
    {
        /* This should never be reached */
    }
}

/** @}*/

#endif

#endif /* _HWA_ADC_H_ */
