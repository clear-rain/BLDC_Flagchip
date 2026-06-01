/**
 * @file module_driver_adc.h
 * @author Flagchip030
 * @brief ADC driver type definition and API
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
*   2.0.0       2024-04-20    Flagchip095   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_ADC_H_
#define _DRIVER_MODULE_DRIVER_ADC_H_

#include "HwA_adc.h"

#if ADC_INSTANCE_COUNT > 0U


/**
 * @addtogroup module_driver_adc
 * @{
 */

#include "module_driver_dma.h"
#include "module_driver_pcc.h"
#if defined(__cplusplus)
extern "C" {
#endif


/**
 * @name  ADC API Service IDs
 *
 * @{
 */
#define ADC_INIT_STRUCTURE_ID           0U
#define ADC_INIT_ID                     1U
#define ADC_DEINIT_ID                   2U
#define ADC_INIT_CHANNEL_ID             3U
#define ADC_INIT_COMPARE_ID             4U
#define ADC_INIT_INTERRUPT_ID           5U
#define ADC_INIT_DMA_CHANNEL_ID         6U
#define ADC_SET_SW_PRETRIGGER_ID        7U
#define ADC_ENABLE_ID                   8U
#define ADC_DISABLE_ID                  9U
#define ADC_START_ID                    10U
#define ADC_STOP_ID                     11U
#define ADC_RESET_ID                    12U
#define ADC_GET_TRIG_ERR_STATUS_ID      13U
#define ADC_CLEAR_TRIG_ERR_ID           14U
#define ADC_CLEAR_TRIG_ERRS_ID          15U
#define ADC_GET_TRIG_LATCH_STATUS_ID    16U
#define ADC_CLEAR_LATCH_TRIGGER_ID      17U

/** @}*/

/**
 * @name  PTIMER Dev Error Code
 * @brief Error Code of calling PTIMER apis
 *
 * @{
 */
#define ADC_E_PARAM_INSTANCE            0x01U
#define ADC_E_PARAM_CHANNEL             0x02U
#define ADC_E_PARAM_POINTER             0x03U
#define ADC_E_PARAM_COUNT               0x04U
#define ADC_E_PARAM_INVALID             0x05U
#define ADC_E_PARAM_PHASE_SHIFT         0x06U
/** @}*/

/**
 * @name  ADC0 Internal Channels
 * @brief Available internal ADC channels for ADC Instance 0
 *
 * @{
 */
#define ADC0_CHANNEL_VBG_BUFFER                ADC_CHANNEL_INTERNAL_0
#ifdef ADC_V25_OSC_SUPPORT
#define ADC0_CHANNEL_V25_OSC                   ADC_CHANNEL_INTERNAL_1
#endif
#define ADC0_CHANNEL_V11_PLL                   ADC_CHANNEL_INTERNAL_2
#define ADC0_CHANNEL_TEST_BUS0                 ADC_CHANNEL_INTERNAL_3
#define ADC0_CHANNEL_CMP_DAC0                  ADC_CHANNEL_INTERNAL_4
#define ADC0_CHANNEL_TEMPSENSOR_TS_OUT         ADC_CHANNEL_INTERNAL_5
/** @}*/

/**
 * @name  ADC1 Internal channels
 * @brief Available internal ADC channels for ADC Instance 1
 *
 * @{
 */
#define ADC1_CHANNEL_V11_PD0                   ADC_CHANNEL_INTERNAL_0
#define ADC1_CHANNEL_VREFH                     ADC_CHANNEL_INTERNAL_1
#define ADC1_CHANNEL_VDDA                      ADC_CHANNEL_INTERNAL_2
#define ADC1_CHANNEL_TEST_BUS0                 ADC_CHANNEL_INTERNAL_3
#define ADC1_CHANNEL_CMP_DAC0                  ADC_CHANNEL_INTERNAL_4
/** @}*/

/**
 * @brief The instance index of the ADC peripheral
 *
 */
typedef enum
{
    ADC_INSTANCE_0 = 0U,  /**< ADC instance 0 is selected */
    ADC_INSTANCE_1 = 1U   /**< ADC instance 1 is selected */
} ADC_InstanceType;

/**
 * @brief The channel selected for ADC conversion
 *
 */
typedef enum
{
    ADC_CHANNEL_0          = 0U,
    ADC_CHANNEL_1          = 1U,
    ADC_CHANNEL_2          = 2U,
    ADC_CHANNEL_3          = 3U,
    ADC_CHANNEL_4          = 4U,
    ADC_CHANNEL_5          = 5U,
    ADC_CHANNEL_6          = 6U,
    ADC_CHANNEL_7          = 7U,
    ADC_CHANNEL_8          = 8U,
    ADC_CHANNEL_9          = 9U,
    ADC_CHANNEL_10         = 10U,
    ADC_CHANNEL_11         = 11U,
    ADC_CHANNEL_12         = 12U,
    ADC_CHANNEL_13         = 13U,
    ADC_CHANNEL_14         = 14U,
    ADC_CHANNEL_15         = 15U,
    ADC_CHANNEL_16         = 16U,
    ADC_CHANNEL_17         = 17U,
    ADC_CHANNEL_18         = 18U,
    ADC_CHANNEL_19         = 19U,
    ADC_CHANNEL_20         = 20U,
    ADC_CHANNEL_21         = 21U,
    ADC_CHANNEL_22         = 22U,
    ADC_CHANNEL_23         = 23U,
    ADC_CHANNEL_24         = 24U,
    ADC_CHANNEL_25         = 25U,
    ADC_CHANNEL_26         = 26U,
    ADC_CHANNEL_27         = 27U,
    ADC_CHANNEL_28         = 28U,
    ADC_CHANNEL_29         = 29U,
    ADC_CHANNEL_30         = 30U,
    ADC_CHANNEL_31         = 31U,
    ADC_CHANNEL_INTERNAL_0 = 32U,
    ADC_CHANNEL_INTERNAL_1 = 33U,
    ADC_CHANNEL_INTERNAL_2 = 34U,
    ADC_CHANNEL_INTERNAL_3 = 35U,
    ADC_CHANNEL_INTERNAL_4 = 36U
} ADC_ChannelType;

/**
 * @brief The channel selected for ADC conversion in differential mode
 *
 */
typedef enum
{
    ADC_CHANNEL_0_4        = 0U,
    ADC_CHANNEL_1_5        = 1U,
    ADC_CHANNEL_2_6        = 2U,
    ADC_CHANNEL_3_7        = 3U,
    ADC_CHANNEL_INTERNAL_5 = 37U
} ADC_DifferentialChannelType;

/**
 * @brief The ADC sample time option for selection
 *
 */
typedef enum
{
    ADC_SAMPLE_TIME_OPTION_0 = 0U,
    ADC_SAMPLE_TIME_OPTION_1 = 1U,
    ADC_SAMPLE_TIME_OPTION_2 = 2U,
    ADC_SAMPLE_TIME_OPTION_3 = 3U
} ADC_SampleTimeOptionType;

/**
 * @brief ADC operation return values
 *
 */
typedef enum
{
    ADC_STATUS_SUCCESS = 0x0U,  /**< The ADC operation is succeed */
    ADC_STATUS_ERROR   = 0x1U,  /**< The ADC operation is failed */
    ADC_STATUS_TIMEOUT = 0x2U   /**< The ADC operation is failed because of time out */
} ADC_StatusType;

/**
 * @brief The configuration option for the ADC channel
 *
 */
typedef struct
{
    ADC_ChannelType          eChannel;          /**< Selected ADC channel */
    ADC_SampleTimeOptionType eSampleTimeOption; /**< The sample time selection for the channel */
} ADC_ChannelCfgType;


/**
 * @brief Defines the hardware compare configuration
 *
 * This structure is used to configure the hardware compare feature for the ADC
 *
 * Implements : ADC_CompareType
 */
typedef struct
{
    /* ADC_CMP_CTRL */
    bool bCmpEnable;                     /**< Enable hardware compare */
    uint8_t u8CmpChnSel;                 /**< Compare channel selection */
    /* ADC_CMP_TR */
    uint16_t u16HighThres;               /**< Compare high threshold */
    ADC_CmpChannelType eCmpSingleChn;    /**< 0: ADC compare on all channels;
                                              1: ADC compare on the selected channel */
    uint8_t reserved[1];
    uint16_t u16LowThres;                /**< Compare low threshold */
} ADC_CompareType;

/**
 * @brief The structure of the CMU processing handle
 * Implements : _ADC_HandleType
 **/
typedef struct _ADC_HandleType
{
    ADC_InstanceType eInstance;          /**< ADC instance */

    uint8_t reserve0[3];

    struct
    {
        uint8_t u8ChnCnt;                     /**< number of channels */

        /* ADC_INT_ENABLE */
        bool bConversionCompleteIntEn;    /**< Enable interrupt when conversion completed */
        bool bOverRunIntEn;               /**< Enable interrupt when overrun occured */
        bool bAnalogCmpIntEn;             /**< Enable interrupt when conversion result lays in the compare threshold */

        void (*pConvCompleteCallback)(struct _ADC_HandleType *pHandle, const uint32_t *const pBuff); /**< Conversion complete interrupt callback */

        void (*pOverRunCallback)(struct _ADC_HandleType *pHandle);  /**< Overrun interrupt callback */

        void (*pCompareCallback)(struct _ADC_HandleType *pHandle);  /**< Compare interrupt callback */

        uint32_t *pAdcResultBuffer;
    } tSettings;

} ADC_HandleType;

/**
 * @brief Defines the converter configuration
 *
 * This structure is used to configure the ADC converter
 *
 * Implements : ADC_InitType
 */
typedef struct
{
    uint32_t u3AdcFuncClk;               /**<ADC CLK>  */
    ADC_ResolutionType eResolution;      /**< ADC eResolution (8,10,12 bit) */
    ADC_AlignType eAlign;                /**< ADC alignment (left, right) */
    ADC_TrigModeType eTriggerMode;       /**< ADC trigger type (software, hardware)
                                             - affects only the first control channel */
    bool bWaitEnable;                    /**< Whether to enable ADC wait conversion mode */
    #ifdef ADC_DIFF_INPUT_SUPPORT
    bool bDifferentialModeEnable;        /**< Whether to enable ADC differential mode */
    #endif
    #ifdef ADC_FUNCLK_INTERNAL_DIVIDER_SUPPORT
    ADC_ClockDivideType eClockDivider;   /**< ADC clock divider */
    #endif
    ADC_SeqModeType eSequenceMode;       /**< ADC sequence mode (single, continuous, discontinuous) */
    ADC_OvrModeType eOverrunMode;        /**< Whether to preserve data when ADC overruns */

    ADC_RefType eVoltageRef;             /**< Voltage reference used (external, internal) */
    bool bHwAvgEnable;                   /**< Enable averaging functionality */
    ADC_AverageType eHwAverage;          /**< Selection for number of samples used for averaging */
    uint8_t aSampleTimes[ADC_SAMPLE_TIME_OPTION_CNT];  /**< ADC sample time options, range: 4 ~ 257 */

    ADC_PreTriggerSelType ePreTriggerSel; /**< Pretrigger source selected from Trigger Latching and Arbitration Unit
                                               - affects only the first 4 control channels in discontinuous mode */
    ADC_TriggerSelType eTriggerSel;       /**< Trigger source selected from Trigger Latching and Arbitration Unit
                                               - effects only in discontinuous mode */
    #ifndef ADC_DIFF_INPUT_SUPPORT
    uint8_t reserved0[1];
    #endif
    #ifndef ADC_FUNCLK_INTERNAL_DIVIDER_SUPPORT
    uint8_t reserved1[1];
    #endif
    /* ADC_INT_ENABLE */
    bool bConversionCompleteIntEn;    /**< Enable interrupt when conversion completed */
    bool bOverRunIntEn;               /**< Enable interrupt when overrun occured */
    bool bAnalogCmpIntEn;             /**< Enable interrupt when conversion result lays in the compare threshold */
    void (*pConvCompleteCallback)(struct _ADC_HandleType *pHandle, const uint32_t *const pBuff); /**< Conversion complete interrupt callback */
    void (*pOverRunCallback)(struct _ADC_HandleType *pHandle);  /**< Overrun interrupt callback */
    void (*pCompareCallback)(struct _ADC_HandleType *pHandle);  /**< Compare interrupt callback */
    uint32_t *pAdcResultBuffer;
} ADC_InitType;

/**
 * @brief Defines the DMA configuretion
 *
 * This structure is used to configure the DMA result transfer feature for ADC
 *
 */
typedef struct
{
    bool bDmaEnable;                     /**< Enable DMA for the ADC */
    uint8_t u8DmaChannel;                /**< The DMA channel used to transfer the ADC conversion results */
    uint8_t u8ChannelPriority;           /**< The DMA channel priority, higher value means higher priority.
                                              The priority for different channels must be unique. Default priority
                                              value is same the channel number */
    bool bDmaIntEnable;                  /**< DMA interrupt enable */
    uint32_t *pResultBuffer;             /**< Buffer to store the ADC conversion results */
    void (*pConvCompleteCallback)(struct _ADC_HandleType *pHandle, const uint32_t *const pBuff); /**< Conversion complete interrupt callback */
} ADC_DmaType;


/**
 * @brief Provide the default values of ADC_InitType
 *
 * @param pInitCfg the structure to initialize
 */
void ADC_InitStructure(ADC_InitType *const pInitCfg);

/**
 * @brief Initialize the ADC instance
 *
 * @param pAdcHandle the ADC process handler
 * @param pInitCfg the configurations of the ADC instance
 */
void ADC_Init(ADC_HandleType *pAdcHandle, const ADC_InitType *const pInitCfg);

/**
 * @brief De-initialize the ADC instance
 *
 * Restore the ADC instance to its reset state
 *
 * @param pAdcHandle the ADC process handler
 */
void ADC_DeInit(ADC_HandleType *pAdcHandle);

/**
 * @brief Configure the ADC sample channels
 *
 * @param pAdcHandle the ADC process handler
 * @param aChannels the channels to use
 * @param u8ChnCnt the quantity of channels
 */
void ADC_InitChannel(ADC_HandleType *pAdcHandle, const ADC_ChannelCfgType aChannels[],
                     const uint8_t u8ChnCnt);

/**
 * @brief Configure the hardware compare feature of ADC
 *
 * @param pAdcHandle the ADC process handler
 * @param pCmpCfg the compare paremeters
 */
void ADC_InitCompare(const ADC_HandleType *pAdcHandle, const ADC_CompareType *const pCmpCfg);

/**
 * @brief Configure the DMA feature of ADC
 *
 * @param pDmaHandle the DMA process handler
 * @param pAdcHandle the ADC process handler
 * @param pAdcDmaCfg the DMA paremeters for the ADC instance
 */
void ADC_InitDmaChannel(DMA_HandleType *pDmaHandle, ADC_HandleType *pAdcHandle, const ADC_DmaType *const pAdcDmaCfg);

/**
 * @brief Configure the software pretrigger source for ADC
 *
 * @param pAdcHandle the ADC process handler
 * @param eSwPretrigger the software pretrigger source to use
 * @note The software pretrigger should only be seleted when the ADC discontinuous mode is used
 * and the pretrigger source is selected as ADC_PRETRIGGER_SEL_SW
 */
void ADC_SetSwPretrigger(const ADC_HandleType *pAdcHandle, const ADC_SwPreTriggerType eSwPretrigger);


/**
 * @brief Enable the ADC instance
 *
 * @param pAdcHandle the ADC process handler
 * @return ADC_StatusType whether ADC is enabled successfully
 */
ADC_StatusType ADC_Enable(const ADC_HandleType *pAdcHandle);

/**
 * @brief Disable the ADC instance
 *
 * @param pAdcHandle the ADC process handler
 * @param u32SysFreq the frequency of sysclk
 * @param u32AdcFreq the frequency of adc clk
 * @return ADC_StatusType whether ADC is disabled successfully
 */
ADC_StatusType ADC_Disable(ADC_HandleType *pAdcHandle, uint32_t u32SysFreq, uint32_t u32AdcFreq);

/**
 * @brief Start the ADC conversion
 *
 * If the ADC sequence mode is single or continuous, and the trigger mode is ADC_TRIGMODE_SW,
 * the adc conversion will start immediately. Otherwise, the ADC will wait for the trigger
 * signal to start the conversion
 *
 * @param pAdcHandle the ADC process handler
 */
void ADC_Start(const ADC_HandleType *pAdcHandle);

/**
 * @brief Stop the ADC conversion
 *
 * If the ADC sequence mode is single, it will stop the ongoing conversion. If no ongoing
 * conversion, it will have no effect. If the ADC sequence mode is continuous or discontinuous,
 * it will stop the ongoing conversion and meanwhile the further conversions.
 *
 * @param pAdcHandle the ADC process handler
 * @param u32SysFreq the frequency of sysclk
 * @param u32AdcFreq the frequency of adc clk
 * @return ADC_StatusType whether ADC is stopped successfully
 */
ADC_StatusType ADC_Stop(const ADC_HandleType *pAdcHandle, uint32_t u32SysFreq, uint32_t u32AdcFreq);

/**
 * @brief Reset the ADC hardware
 *
 * @param pAdcHandle the ADC process handler
 */
void ADC_Reset(const ADC_HandleType *pAdcHandle);


/**
 * @brief Get the trigger error status of the ADC instance
 *
 * @param pAdcHandle the ADC process handler
 * @return uint32_t The result has four bits, and each bit indicates that Trigger Latch Unit new
 * trigger request has been missed, because old request has already been latched or is being serviced.
 */
uint32_t ADC_GetTriggerErrorStatus(const ADC_HandleType *pAdcHandle);

/**
 * @brief Clear the trigger error of the specified trigger request
 *
 * @param pAdcHandle the ADC process handler
 * @param u32Request the trigger request to clear
 * @return ADC_StatusType whether the ADC error is cleared successfully
 */
ADC_StatusType ADC_ClearTriggerError(const ADC_HandleType *pAdcHandle, uint32_t u32Request);

/**
 * @brief Clear all of the trigger errors
 *
 * @param pAdcHandle the ADC process handler
 * @return ADC_StatusType whether the ADC errors are cleared successfully
 */
ADC_StatusType ADC_ClearTriggerErrors(const ADC_HandleType *pAdcHandle);

/**
 * @brief Get the trigger latch status of the ADC instance
 *
 * @param pAdcHandle the ADC process handler
 * @return uint32_t The result has four bits, and each bit indicate that a Trigger Latch Unit
 * trigger request has been latched.
 */
uint32_t ADC_GetTriggerLatchStatus(const ADC_HandleType *pAdcHandle);

/**
 * @brief Clear the trigger latch status
 *
 * @param pAdcHandle the ADC process handler
 */
void ADC_ClearLatchedTriggers(const ADC_HandleType *pAdcHandle);

/**
 * @brief ADC IRQ Functions
 *
 * @param pAdcHandle the ADC process handler
 */
void ADCn_IRQHandler(ADC_HandleType *pAdcHandle);

#if defined(__cplusplus)
}

#endif

/** @}*/ /* module_driver_adc */

#endif

#endif
