/**
 * @file HwA_ftu.h
 * @author Flagchip032
 * @brief FTU hardware access layer
 * @version 2.0.0
 * @date 2024-05-16
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip070   N/A          First version
*********************************************************************************/

#ifndef _HWA_FTU_H_
#define _HWA_FTU_H_

#include "device_header.h"

#if FTU_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_ftu HwA_ftu
 * @ingroup module_driver_ftu
 * @{
 */

/********* Local typedef ************/
/**
 * @brief The definition of enable the deadtime of channel and channel+1
 *
 */
#define FTU_CHCTRL_DEADTIME_CHANNEL(channel) (uint32_t)((uint32_t)1U << ((((uint32_t)(channel) >> 1U) << 3U) + 4U))
/**
 * @brief The definition of enable the complement of channel
 *
 */
#define FTU_CHCTRL_COMPLEMENT_CHANNEL(channel) (uint32_t)((uint32_t)1U << ((((uint32_t)(channel) >> 1U) << 3U) + 1U))
/**
 * @brief The definition of enable the synchronization for channel and channel+1
 *
 */
#define FTU_CHCTRL_SYNCEN_CHANNEL(channel) (uint32_t)((uint32_t)1U << ((((uint32_t)(channel) >> 1U) << 3U) + 5U))
/**
 * @brief The definition of enable the Phase shift mode for channel and channel+1
 *
 */
#define FTU_CHCTRL_PHASE_CHANNEL(channel)	(uint32_t)((uint32_t)1U << (((uint32_t)(channel) >> 1U) << 3U))
/**
 * @brief The definition of enable the Enhanced Phase shift mode for channel and channel+1
 *
 */
#define FTU_CHCTRL_EPHASE_CHANNEL(channel) 	(uint32_t)((uint32_t)1U << ((((uint32_t)(channel) >> 1U) << 3U) + 7U))
/**
 * @brief The definition of enable the fault control in channel and channel+1
 *
 */
#define FTU_CHCTRL_FAULT_CHANNEL(channel) (uint32_t)((uint32_t)1U << ((((uint32_t)(channel) >> 1U) << 3U) + 6U))

/********* Local typedef ************/
/**
 * @brief Select the FTU Debug Mode
 *
 */
typedef enum
{
    FTU_DBG_COUNTER_STOP_CHN_WORKS = 0U,            /**< FTU counter stopped, channel works as function mode. */
    FTU_DBG_COUNTER_STOP_CHN_FORCE_SAFE = 1U,       /**< FTU counter stopped, channel output force to safe state. */
    FTU_DBG_COUNTER_STOP_CHN_FROZEN = 2U,           /**< FTU counter stopped, channel output is frozen. */
    FTU_DBG_COUNTER_WORKS_CHN_WORKS = 3U            /**< FTU counter works as function mode, channel works as function mode. */
} FTU_DebugModeType;

typedef enum
{
	FTU_CHANNEL_MODE_INPUT			= 0u,
	FTU_CHANNEL_MODE_OUTPUT_COMPARE = 1u,
	FTU_CHANNEL_MODE_EDGE_ALIGN_PWM = 2u,
	FTU_CHANNEL_MODE_DO_NOT_CARE	= 3u,
} FTU_ChannelModeType;

typedef enum
{
	FTU_CHANNEL_EDGE_NOT_USED	= 0u,
	FTU_CHANNEL_EDGE_RISING		= 1u,
	FTU_CHANNEL_EDGE_FALLING	= 2u,
	FTU_CHANNEL_EDGE_BOTH		= 3u,
	FTU_CHANNEL_OC_TOGGLE		= 1u,
	FTU_CHANNEL_OC_CLEAR		= 2u,
	FTU_CHANNEL_OC_SET			= 3u,
	FTU_CHANNEL_PWM_HIGH_TRUE	= 2u,
	FTU_CHANNEL_PWM_LOW_TRUE	= 3u,
} FTU_ChannelEdgeLevelType;
/**
 * @brief Select the prescaler of the FTU
 *
 */
typedef enum
{
    FTU_DIV_1 = 0U,
    FTU_DIV_2,
    FTU_DIV_4,
    FTU_DIV_8,
    FTU_DIV_16,
    FTU_DIV_32,
    FTU_DIV_64,
    FTU_DIV_128
} FTU_PrescalerType;

/**
 * @brief Select the prescaler of the FTU filter
 *
 */
typedef enum
{
    FTU_FLT_DIV_1 = 0U,
    FTU_FLT_DIV_2,
    FTU_FLT_DIV_3,
    FTU_FLT_DIV_4,
    FTU_FLT_DIV_5,
    FTU_FLT_DIV_6,
    FTU_FLT_DIV_7,
    FTU_FLT_DIV_8,
    FTU_FLT_DIV_9,
    FTU_FLT_DIV_10,
    FTU_FLT_DIV_11,
    FTU_FLT_DIV_12,
    FTU_FLT_DIV_13,
    FTU_FLT_DIV_14,
    FTU_FLT_DIV_15,
    FTU_FLT_DIV_16
} FTU_FilterPrescalerType;

/**
 * @brief selects the encoding mode used in the Quadrature Decoder mode
 *
 */
typedef enum
{
    FTU_QUADMODE_PHA_PHB_ENCODING_MODE 		= 0U,	/**< Phase A and phase B encoding mode */
    FTU_QUADMODE_COUNT_DIR_ENCODING_MODE,			/**< Count and direction encoding mode */
} FTU_QuadratureModeType;

/**
 * @brief FTU Counter Direction In Quadrature Decoder Mode
 *
 */
typedef enum
{
	FTU_QUADIR_DECREMENT = 0U,						/**< FTU counter decrement */
	FTU_QUADIR_INCREMENT,							/**< FTU counter increment */
} FTU_QuadratureDirectionType;

/**
 * @brief register bit status
 *
 */
typedef enum
{
    FTU_BIT_LOW = 0U,
    FTU_BIT_HIGH
} FTU_BitStatusType;

/**
 * @brief Ftu module clock source
 *
 */
typedef enum
{
    FTU_MODULE_NO_CLK = 0U,						/**< No clock selected */
    FTU_MODULE_INTERNAL_CLK = 1U,				/**< FTU input clock */
    FTU_MODULE_EXTERNAL_CLK = 3U,				/**< External pin input clock */
} FTU_ModuleClkSrcType;
#ifdef FTU_UPDOWN_DIS_FEATURE
/**
 * @brief Disable channel match trigger/interrupt when count-up/down in CPWM/QUAD mode
 *
 */
typedef enum
{
	FTU_DISABLE_TRIG_INTR_NONE	   		= 0U,	/**< No effect */
	FTU_DISABLE_TRIG_INTR_CNT_DOWN 		= 1U,	/**< Disable trigger/interrupt when count-down */
	FTU_DISABLE_TRIG_INTR_CNT_UP   		= 2U,	/**< Disable trigger/interrupt when count-up */
	FTU_DISABLE_TRIG_INTR_CNT_UP_DOWN 	= 3U,	/**< Disable trigger/interrupt when count-up/down */
}FTU_UpDownDisableType;
#endif
/**
 * @brief hardware trig(n) mode
 *
 */
typedef enum
{
    FTU_CLEARS_TRIG_WHEN_DETECTED 		= 0x0U,     /**< FTU clears the TRIG(n) bit when the hardware trigger j is detected, where n = 0, 1,2. */
    FTU_NOT_CLEARS_TRIG_WHEN_DETECTED 	= 0x01U   	/**< FTU does not clear the TRIG(n) bit when the hardware trigger j is detected, where n = 0, 1,2. */
} FTU_TrigModeType;

/**
 * @brief fault mode enumeration
 *
 */
typedef enum
{
    FTU_FAULT_MODE_DISABLED  		= 0x00U,        /**< Fault control is disabled for all channels */
    FTU_FAULT_MODE_EVEN_CHANNEL  	= 0x01U,    	/**< Fault control is enabled for even channels only (channels 0, 2, 4, and 6), and the selected mode is the manual fault clearing */
    FTU_FAULT_MODE_CHANNEL_ALL   	= 0x02U,    	/**< Fault control is enabled for all channels, and the selected mode is the manual fault clearing */
    FTU_FAULT_MODE_AUTO  			= 0x03U         /**< Fault control is enabled for all channels, and the selected mode is the automatic fault clearing */
} FTU_FaultModeType;

#ifdef FTU_TCKSEL_EXIST
/**
 * @brief external clock enumeration
 *
 */
typedef enum
{
    FTU_TCLK0_USED 	= 0U,		/**< FTU_TCLK0 pin as FTU external clock */
    FTU_TCLK1_USED 	= 1U,		/**< FTU_TCLK1 pin as FTU external clock */
    FTU_TCLK2_USED 	= 2U,		/**< FTU_TCLK2 pin as FTU external clock */
    FTU_NO_CLK_USED = 3U,		/**< No clock input */
} FTU_TclkSelType;
#endif
/**
 * @brief Deadtime Prescaler Value
 *
 */
typedef enum
{
	FTU_DEADTIME_PRESCALER_DIV_1 	= 0U,	/**< Divide the FTU input clock by 1 */
	FTU_DEADTIME_PRESCALER_DIV_4 	= 2U,	/**< Divide the FTU input clock by 4 */
	FTU_DEADTIME_PRESCALER_DIV_16 	= 3U,	/**< Divide the FTU input clock by 16 */
} FTU_DeadTimePrescalerType;

/**
 * @brief Trigger output control
 *
 */
typedef enum
{
	FTU_TRIG_OUTPUT_AS_CHANNEL_MODE		= 0U,	/**< channel outputs will be controlled by channel mode */
	FTU_TRIG_OUTPUT_AS_TRIGGER			= 1U,	/**< If a match in the channel occurs, channel output will be a trigger */
}FTU_TrigOutputModeType;
#ifdef FTU_FAULT_DIS_DELAY_FEATURE
/**
 * @brief Fault disable channel output delay value selection
 *
 */
typedef enum
{
	FTU_FAULT_DISABLE_DELAY_NO_DELAY 	= 0u,	/**< Select no delay */
	FTU_FAULT_DISABLE_DELAY_VALUE_0	 	= 1u,	/**< Select delay value 0 */
	FTU_FAULT_DISABLE_DELAY_VALUE_1		= 2u	/**< Select delay value 1 */
}FTU_FaultDisableDelayType;
#endif
#ifdef FTU_ICM_FEATURE
/**
 * @brief Input Capture Measurement Mode
 *
 */
typedef enum
{
	FTU_MEASURE_MODE_OFF			= 0u,	/**< Do not use measurement mode */
	FTU_MEASURE_MODE_DUTY_CYCLE		= 1u,	/**< Duty-cycle Measure */
	FTU_MEASURE_MODE_PERIOD			= 2u,	/**< Period Measure */
	FTU_MEASURE_EDGE_NUMBER			= 3u,	/**< Edge Number Measure */
	FTU_MEASURE_EXPECT_EDGE_NUMBER	= 4u,	/**< Expect Edge Number Measure */
	FTU_MEASURE_ICENM_WIND_WRITE	= 7u,	/**< Configure ICENM Window */
}FTU_MeasurementModeType;
#endif

/********* Local inline function ************/

/**
 * @brief Clear FTU module registers
 *
 * @param pFtu FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearModuleRegister(FTU_Type *pFtu)
{
	uint32_t u32Loop;
    pFtu->SC &= 0U;
    pFtu->CNT = 0U;
    pFtu->MOD = 0U;
    for(u32Loop = 0u; u32Loop < FTU_CHANNEL_CONTROLS_COUNT; u32Loop++)
    {
    	pFtu->CONTROLS[u32Loop].CSCn = (uint32_t)0u;
    	pFtu->CONTROLS[u32Loop].CVn = (uint32_t)0u;
    }
    pFtu->CNTIN = 0U;
    pFtu->STATUS |= FTU_STATUS_CHNF_MASK;
    pFtu->MODE = 0x00000004U;
    pFtu->SYNC = 0U;
    pFtu->OUTINIT = 0U;
    pFtu->OUTMASK = 0U;
    pFtu->CHCTRL = 0U;
    pFtu->DEADTIME = 0U;
    pFtu->TRIGCONF = 0U;
    pFtu->POL = 0U;
    pFtu->FMS &= 0U;
    pFtu->FILTER = 0U;
    pFtu->FLTCTRL = 0U;
    pFtu->QDCTRL = 0U;
    pFtu->CONF = FTU_CONF_DBG(3u);
    pFtu->FLTPOL = 0U;
    pFtu->SYNCONF = 0U;
    pFtu->INVCTRL = 0U;
    pFtu->SWOCTRL = 0U;
    pFtu->PWMLOAD = 0U;
    pFtu->PAIRDEADTIME0 = 0U;
    pFtu->PAIRDEADTIME1 = 0U;
    pFtu->PAIRDEADTIME2 = 0U;
    pFtu->PAIRDEADTIME3 = 0U;
}

/**
 * @brief Disable Global Time Base Enable
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableGlobalTimeBase(FTU_Type *pFtu)
{
	pFtu->CONF &= ~FTU_CONF_GTBEEN_MASK;
}

/**
 * @brief Enable Global Time Base Enable
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableGlobalTimeBase(FTU_Type *pFtu)
{
	pFtu->CONF |= FTU_CONF_GTBEEN_MASK;
}

/**
 * @brief Set the LDOK flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_SetPwmLoadEnable(FTU_Type *pFtu)
{
	pFtu->PWMLOAD |= FTU_PWMLOAD_LDOK_MASK;
}

/**
 * @brief Clear the LDOK flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearPwmLoadEnable(FTU_Type *pFtu)
{
	pFtu->PWMLOAD &= ~FTU_PWMLOAD_LDOK_MASK;
}

/**
 * @brief Set the CNTINC flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_SetCntinSync(FTU_Type *pFtu)
{
	pFtu->SYNCONF |= FTU_SYNCONF_CNTINC_MASK;
}

/**
 * @brief Clear the CNTINC flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearCntinSync(FTU_Type *pFtu)
{
	pFtu->SYNCONF &= ~FTU_SYNCONF_CNTINC_MASK;
}

/**
 * @brief Set the SYNCEN flag
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Index the index of SYNCEN
 */
LOCAL_INLINE void FTU_HWA_SetChannelSyncEnable(FTU_Type *pFtu, uint32_t u32Index)
{
	pFtu->CHCTRL |= (FTU_CHCTRL_SYNCEN0_MASK << (u32Index * 8));
}

/**
 * @brief Clear the SYNCEN flag
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Index the index of SYNCEN
 */
LOCAL_INLINE void FTU_HWA_ClearChannelSyncEnable(FTU_Type *pFtu, uint32_t u32Index)
{
	pFtu->CHCTRL &= (~(FTU_CHCTRL_SYNCEN0_MASK << (u32Index * 8)));
}

/**
 * @brief Set the PWMSYNC flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_SetPwmSyncMode(FTU_Type *pFtu)
{
	pFtu->MODE |= FTU_MODE_PWMSYNC_MASK;
}

/**
 * @brief Clear the PWMSYNC flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearPwmSyncMode(FTU_Type *pFtu)
{
	pFtu->MODE &= ~FTU_MODE_PWMSYNC_MASK;
}

/**
 * @brief Set the REINIT flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_SetReinitBySync(FTU_Type *pFtu)
{
	pFtu->SYNC |= FTU_SYNC_REINIT_MASK;
}

/**
 * @brief Clear the REINIT flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearReinitBySync(FTU_Type *pFtu)
{
	pFtu->SYNC &= ~FTU_SYNC_REINIT_MASK;
}

/**
 * @brief Set the CNTMAX flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableMaxLoadPoint(FTU_Type *pFtu)
{
	pFtu->SYNC |= FTU_SYNC_CNTMAX_MASK;
}

/**
 * @brief Clear the CNTMAX flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableMaxLoadPoint(FTU_Type *pFtu)
{
	pFtu->SYNC &= ~FTU_SYNC_CNTMAX_MASK;
}

/**
 * @brief Set the CNTMIN flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableMinLoadPoint(FTU_Type *pFtu)
{
	pFtu->SYNC |= FTU_SYNC_CNTMIN_MASK;
}

/**
 * @brief Clear the CNTMIN flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableMinLoadPoint(FTU_Type *pFtu)
{
	pFtu->SYNC &= ~FTU_SYNC_CNTMIN_MASK;
}

/**
 * @brief Set the CHNSEL flag of a channel
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Channel channel index
 */
LOCAL_INLINE void FTU_HWA_EnableChannelMatchReload(FTU_Type *pFtu, uint32_t u32Channel)
{
	pFtu->PWMLOAD |= FTU_PWMLOAD_CHNSEL((uint32_t)1u << u32Channel);
}

/**
 * @brief Clear the CHNSEL flag of a channel
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Channel channel index
 */
LOCAL_INLINE void FTU_HWA_DisableChannelMatchReload(FTU_Type *pFtu, uint32_t u32Channel)
{
	pFtu->PWMLOAD &= ~FTU_PWMLOAD_CHNSEL((uint32_t)1u << u32Channel);
}

/**
 * @brief configure the frequency of the reload opportunities
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Freq the number of enabled reload opportunities that should happen until an
 *				 enabled reload opportunity becomes a reload point
 */
LOCAL_INLINE void FTU_HWA_ConfigFreqOfReloadOp(FTU_Type *pFtu, uint8_t u8Freq)
{
	pFtu->CONF = (pFtu->CONF & (~FTU_CONF_LDFQ_MASK)) | FTU_CONF_LDFQ(u8Freq);
}

/**
 * @brief Selects the FTU behavior in Debug mode
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Mode debug mode
 */
LOCAL_INLINE void FTU_HWA_ConfigDebugMode(FTU_Type *pFtu, uint32_t u32Mode)
{
	pFtu->CONF = (pFtu->CONF & (~FTU_CONF_DBG_MASK)) | FTU_CONF_DBG(u32Mode);
}
#ifdef FTU_UPDOWN_DIS_FEATURE
/**
 * @brief Disable channel match trigger/interrupt when count-up/down in CPWM/QUAD mode
 *
 * @param pFtu the base address of the FTU instance
 * @param eUpdownDisable up-down disable mode
 */
LOCAL_INLINE void FTU_HWA_ConfigUpDownDisable(FTU_Type *pFtu, FTU_UpDownDisableType eUpdownDisable)
{
	pFtu->SC = (pFtu->SC & (~FTU_SC_UPDOWN_DIS_MASK)) | FTU_SC_UPDOWN_DIS((uint32_t)eUpdownDisable);
}
#endif

/**
 * @brief Enable reload point interrupt
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableReloadPointInterrupt(FTU_Type *pFtu)
{
	pFtu->SC |= FTU_SC_RIE_MASK;
}

/**
 * @brief Disable reload point interrupt
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableReloadPointInterrupt(FTU_Type *pFtu)
{
	pFtu->SC &= ~((uint32_t)FTU_SC_RIE_MASK);
}

/**
 * @brief Enable software output control of channels
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Mask channel mask
 */
LOCAL_INLINE void FTU_HWA_EnalbeSWOControl(FTU_Type *pFtu, uint32_t u32Mask)
{
	pFtu->SWOCTRL |= FTU_SWOCTRL_CHNOC(u32Mask);
}

/**
 * @brief Disable software output control of channels
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Mask channel mask
 */
LOCAL_INLINE void FTU_HWA_DisalbeSWOControl(FTU_Type *pFtu, uint32_t u32Mask)
{
	pFtu->SWOCTRL &= ~FTU_SWOCTRL_CHNOC(u32Mask);
}

/**
 * @brief Set the software output control value
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Mask channel mask
 */
LOCAL_INLINE void FTU_HWA_SetSWOValue(FTU_Type *pFtu, uint32_t u32Mask)
{
	pFtu->SWOCTRL |= FTU_SWOCTRL_CHNOCV(u32Mask);
}

/**
 * @brief Clear the software output control value
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Mask channel mask
 */
LOCAL_INLINE void FTU_HWA_ClearSWOValue(FTU_Type *pFtu, uint32_t u32Mask)
{
	pFtu->SWOCTRL &= ~FTU_SWOCTRL_CHNOCV(u32Mask);
}

/**
 * @brief Configure the pair deadtime prescaler value
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Channel channel index
 * @param ePrescaler prescaler value
 */
LOCAL_INLINE void FTU_HWA_ConfigPairDeadtimePrescaler(FTU_Type *pFtu, uint32_t u32Channel, FTU_DeadTimePrescalerType ePrescaler)
{
	u32Channel &= (~1u);
    ((volatile uint32_t *)(&pFtu->PAIRDEADTIME0))[u32Channel] =
    			((((volatile uint32_t *)(&pFtu->PAIRDEADTIME0))[u32Channel]) & (~(uint32_t)FTU_DEADTIME_DTPS_MASK))
			| FTU_DEADTIME_DTPS(ePrescaler);
}

/**
 * @brief Configure the deadtime value
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Channel channel index
 * @param u32Value deadtime value
 */
LOCAL_INLINE void FTU_HWA_ConfigPairDeadtimeValue(FTU_Type *pFtu, uint32_t u32Channel, uint32_t u32Value)
{
	u32Channel &= (~1u);
	((volatile uint32_t *)(&pFtu->PAIRDEADTIME0))[u32Channel] =
			((((volatile uint32_t *)(&pFtu->PAIRDEADTIME0))[u32Channel]) & (~(uint32_t)(FTU_DEADTIME_DTVAL_MASK | FTU_DEADTIME_DTVALEX_MASK)))
			| FTU_DEADTIME_DTVAL(u32Value & 0x3Fu) | FTU_DEADTIME_DTVALEX(u32Value >> 6);
}

/**
 * @brief Configure the deadtime prescaler value
 *
 * @param pFtu the base address of the FTU instance
 * @param ePrescaler prescaler value
 */
LOCAL_INLINE void FTU_HWA_ConfigDeadtimePrescaler(FTU_Type *pFtu, FTU_DeadTimePrescalerType ePrescaler)
{
    pFtu->DEADTIME = (pFtu->DEADTIME & (~(uint32_t)FTU_DEADTIME_DTPS_MASK)) | FTU_DEADTIME_DTPS(ePrescaler);
}

/**
 * @brief Configure the deadtime value
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Value deadtime value
 */
LOCAL_INLINE void FTU_HWA_ConfigDeadtimeValue(FTU_Type *pFtu, uint32_t u32Value)
{
	pFtu->DEADTIME = (pFtu->DEADTIME & ((uint32_t)(FTU_DEADTIME_DTVAL_MASK | FTU_DEADTIME_DTVALEX_MASK)))
					| FTU_DEADTIME_DTVAL(u32Value & 0x3Fu) | FTU_DEADTIME_DTVALEX(u32Value >> 6);
}

/**
 * @brief Get the counter value of the selected FTU module
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE uint32_t FTU_HWA_GetCounterValue(FTU_Type *pFtu)
{
	return (uint32_t)pFtu->CNT;
}

/**
 * @brief Clear FTU counter
 *
 * @param pFtu the base address of the FTU instance
 * @param u32RegValue CNT register value
 */
LOCAL_INLINE void FTU_HWA_ClearModuleCounter(FTU_Type *pFtu, uint32_t u32RegValue)
{
    pFtu->CNT = u32RegValue;
}

/**
 * @brief Configure FTU channel
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 * @param u32RegValue the value to write to CSC register
 */
LOCAL_INLINE void FTU_HWA_ConfigChannel(FTU_Type *pFtu, uint8_t u8Channel, uint32_t u32RegValue)
{
    pFtu->CONTROLS[u8Channel].CSCn = u32RegValue;
}

/**
 * @brief Get FTU channel value
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 * @return CVn register value
 */
LOCAL_INLINE uint32_t FTU_HWA_GetChannelValue(FTU_Type *pFtu, uint8_t u8Channel)
{
    return (pFtu->CONTROLS[u8Channel].CVn);
}

/**
 * @brief Set FTU channel value
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 * @param u32RegValue CVn register value
 */
LOCAL_INLINE void FTU_HWA_SetChannelValue(FTU_Type *pFtu, uint8_t u8Channel, uint32_t u32RegValue)
{
    pFtu->CONTROLS[u8Channel].CVn = u32RegValue;
}

/**
 * @brief Set FTU counter compare val
 *
 * @param pFtu the base address of the FTU instance
 * @param u32RegValue MOD register value
 */
LOCAL_INLINE void FTU_HWA_SetModuleCompareValue(FTU_Type *pFtu, uint32_t u32RegValue)
{
    pFtu->MOD = u32RegValue & FTU_MOD_MASK;
}

/**
 * @brief Set FTU counter initial value
 *
 * @param pFtu the base address of the FTU instance
 * @param u32RegValue CNTIN register value
 */
LOCAL_INLINE void FTU_HWA_SetCounterInitialValue(FTU_Type *pFtu, uint32_t u32RegValue)
{
    pFtu->CNTIN = u32RegValue & FTU_CNTIN_INIT_MASK;
}

/**
 * @brief Configure FTU mode
 *
 * @param pFtu the base address of the FTU instance
 * @param u32RegValue MODE register value
 */
LOCAL_INLINE void FTU_HWA_ConfigModuleMode(FTU_Type *pFtu, uint32_t u32RegValue)
{
    pFtu->MODE = u32RegValue;
}

/**
 * @brief Configure FTU deadtime
 *
 * @param pFtu the base address of the FTU instance
 * @param u32RegValue DEADTIME register value
 */
LOCAL_INLINE void FTU_HWA_ConfigDeadtime(FTU_Type *pFtu, uint32_t u32RegValue)
{
    pFtu->DEADTIME = u32RegValue;
}

/**
 * @brief Configure input capture filter
 *
 * @param pFtu the base address of the FTU instance
 * @param u32Channel Channel of FTU instance
 * @param u32FilterValue Filter value
 */
LOCAL_INLINE void FTU_HWA_ConfigInputCaptureFilter(FTU_Type *pFtu, uint32_t u32Channel, uint32_t u32FilterValue)
{
	u32Channel = u32Channel << 2;
	pFtu->FILTER = 	(pFtu->FILTER & (~((uint32_t)0xFu << u32Channel)))
				| 	(u32FilterValue << u32Channel);
}

/**
 * @brief Enable FTU module fault
 *
 * @param pFtu the base address of the FTU instance
 * @param u8InputMask Fault input mask, 0-3 bit indicate fault 0-3
 */
LOCAL_INLINE void FTU_HWA_EnableModuleFault(FTU_Type *pFtu, uint8_t u8InputMask)
{
    pFtu->FLTCTRL |= ((uint32_t)u8InputMask & (uint32_t)0xFU);
}

/**
 * @brief get the fault input enable status
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE uint32_t FTU_HWA_GetFaultEnable(FTU_Type *pFtu)
{
	return (pFtu->FLTCTRL & (uint32_t)0xFU);
}

/**
 * @brief Disable FTU module fault
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Input Fault input number, 0-3 bit indicate fault 0-3
 */
LOCAL_INLINE void FTU_HWA_DisableModuleFault(FTU_Type *pFtu, uint8_t u8Input)
{
    pFtu->FLTCTRL &= ~((uint32_t)u8Input & (uint32_t)0xFU);
}

/**
 * @brief Enable FTU module fault glitch filter
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Input Fault input number, 0-3 bit indicate fault 0-3
 */
LOCAL_INLINE void FTU_HWA_EnableModuleFaultGlitchFilter(FTU_Type *pFtu, uint8_t u8Input)
{
    pFtu->FLTCTRL |= (((uint32_t)u8Input & (uint32_t)0xFU) << 4U);
}

/**
 * @brief Disable FTU module fault glitch filter
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Input Fault input number, 0-3 bit indicate fault 0-3
 */
LOCAL_INLINE void FTU_HWA_DisableModuleFaultGlitchFilter(FTU_Type *pFtu, uint8_t u8Input)
{
    pFtu->FLTCTRL &= ~(((uint32_t)u8Input & (uint32_t)0xFU) << FTU_FLTCTRL_FLT0GFEN_SHIFT);
}

/**
 * @brief Set FTU module fault filter value
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Value FTU fault filter value
 */
LOCAL_INLINE void FTU_HWA_SetModuleFaultFilterValue(FTU_Type *pFtu, uint8_t u8Value)
{
    pFtu->FLTCTRL = (pFtu->FLTCTRL & ~(uint32_t)FTU_FLTCTRL_FFVAL_MASK) | FTU_FLTCTRL_FFVAL(u8Value);
}

#ifdef FTU_FAULT_DIS_DELAY_FEATURE
/**
 * @brief Set FTU module fault disable channel output delay value0
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Value FTU fault delay value0
 */
LOCAL_INLINE void FTU_HWA_SetFaultDelay0(FTU_Type *pFtu, uint8_t u8Value)
{
    pFtu->FLTCTRL = 	(pFtu->FLTCTRL & (~(uint32_t)FTU_FLTCTRL_FDLYV0_MASK))
    				 | 	FTU_FLTCTRL_FDLYV0(u8Value);
}

/**
 * @brief Set FTU module fault disable channel output delay value
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Value FTU fault delay value1
 */
LOCAL_INLINE void FTU_HWA_SetFaultDelay1(FTU_Type *pFtu, uint8_t u8Value)
{
	pFtu->FLTPOL = 	(pFtu->FLTPOL & (~(uint32_t)FTU_FLTPOL_FDLYV1_MASK))
				| 	FTU_FLTPOL_FDLYV1(u8Value);
}
#endif
/**
 * @brief Configure FTU module fault polarity
 *
 * @param pFtu the base address of the FTU instance
 * @param u32FaultIndex index of the fault
 * @param u8InputPol the polarity of the fault input
 */
LOCAL_INLINE void FTU_HWA_ConfigFaultPolarity(FTU_Type *pFtu, uint32_t u32FaultIndex, uint8_t u8InputPol)
{
    pFtu->FLTPOL = 	(pFtu->FLTPOL & (~(uint32_t)(FTU_FLTPOL_FLT0POL_MASK << u32FaultIndex)))
    			| 	(FTU_FLTPOL_FLT0POL(u8InputPol) << u32FaultIndex);
}

/**
 * @brief Set FTU module prescale
 *
 * @param pFtu the base address of the FTU instance
 * @param ePs FTU clock prescaler enumeration
 */
LOCAL_INLINE void FTU_HWA_SetModulePrescale(FTU_Type *pFtu, FTU_PrescalerType ePs)
{
    pFtu->SC = (pFtu->SC & ~(uint32_t)FTU_SC_PS_MASK) | FTU_SC_PS(ePs);
}

/**
 * @brief Read FTU module overflow flag
 *
 * @param pFtu the base address of the FTU instance
 * @return FTU overflow flag
 */
LOCAL_INLINE uint8_t FTU_HWA_ReadModuleOverflowFlag(FTU_Type *pFtu)
{
    return (uint8_t)((pFtu->SC & (uint32_t)FTU_SC_TOF_MASK) >> FTU_SC_TOF_SHIFT);
}

/**
 * @brief Read FTU module overflow interrupt enable
 *
 * @param pFtu the base address of the FTU instance
 * @return FTU overflow interrupt enable
 */
LOCAL_INLINE uint8_t FTU_HWA_ReadModuleOverflowIntrEnable(FTU_Type *pFtu)
{
    return (uint8_t)((pFtu->SC & (uint32_t)FTU_SC_TOIE_MASK) >> FTU_SC_TOIE_SHIFT);
}

/**
 * @brief Read FTU module reload flag
 *
 * @param pFtu the base address of the FTU instance
 * @return FTU reload flag
 */
LOCAL_INLINE uint8_t FTU_HWA_ReadModuleReloadFlag(FTU_Type *pFtu)
{
    return (uint8_t)((pFtu->SC & (uint32_t)FTU_SC_RF_MASK) >> FTU_SC_RF_SHIFT);
}

/**
 * @brief Read FTU module reload interrupt enable
 *
 * @param pFtu the base address of the FTU instance
 * @return reload interrupt enable
 */
LOCAL_INLINE uint8_t FTU_HWA_ReadReloadIntrEnable(FTU_Type *pFtu)
{
	return (uint8_t)((pFtu->SC & (uint32_t)FTU_SC_RIE_MASK) >> FTU_SC_RIE_SHIFT);
}

/**
 * @brief Read FTU channel interrupt flag
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @return FTU channel interrupt flag
 */
LOCAL_INLINE bool FTU_HWA_ReadChannelInterruptFlag(FTU_Type *pFtu, uint8_t u8Channel)
{
    return (0u != (pFtu->CONTROLS[u8Channel].CSCn & (uint32_t)FTU_CSC_CHF_MASK));
}

/**
 * @brief Configure the channel output mode
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param eMode output mode of the selected channel.
 */
LOCAL_INLINE void FTU_HWA_ConfigTrigOutputMode(FTU_Type *pFtu, uint8_t u8Channel, FTU_TrigOutputModeType eMode)
{
	pFtu->CONTROLS[u8Channel].CSCn = 	(pFtu->CONTROLS[u8Channel].CSCn & (~(uint32_t)FTU_CSC_TRIGMODE_MASK))
									 | 	(uint32_t)FTU_CSC_TRIGMODE(eMode);
}
#ifdef FTU_FAULT_DIS_DELAY_FEATURE
/**
 * @brief Select fault disable channel output delay value
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param eSelection Fault disable channel output delay value selection.
 */
LOCAL_INLINE void FTU_HWA_SelectFaultDelay(FTU_Type *pFtu, uint8_t u8Channel, FTU_FaultDisableDelayType eSelection)
{
	pFtu->CONTROLS[u8Channel].CSCn = 	(pFtu->CONTROLS[u8Channel].CSCn & (~(uint32_t)FTU_CSC_FDLYSEL_MASK))
									 | 	(uint32_t)FTU_CSC_FDLYSEL(eSelection);
}
#endif
/**
 * @brief Read FTU channel interrupt enable flag
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @return FTU channel interrupt flag
 */
LOCAL_INLINE uint8_t FTU_HWA_ReadChannelInterruptEnableFlag(FTU_Type *pFtu, uint8_t u8Channel)
{
	return (uint8_t)((pFtu->CONTROLS[u8Channel].CSCn & (uint32_t)FTU_CSC_CHIE_MASK) >> FTU_CSC_CHIE_SHIFT);
}

/**
 * @brief Read FTU module fault(n) flag
 *
 * @param pFtu the base address of the FTU instance
 * @return FTU fault flag
 */
LOCAL_INLINE uint32_t FTU_HWA_ReadModuleFaultFlag(FTU_Type *pFtu)
{
    return (uint32_t)(pFtu->FMS & (uint32_t)0xFU);
}

/**
 * @brief Read FTU module fault interrupt enable
 *
 * @param pFtu the base address of the FTU instance
 * @return FTU fault interrupt enable
 */
LOCAL_INLINE uint8_t FTU_HWA_ReadFaultIntrEnable(FTU_Type *pFtu)
{
	return (uint8_t)((pFtu->MODE & (uint32_t)FTU_MODE_FAULTIE_MASK) >> FTU_MODE_FAULTIE_SHIFT);
}

/**
 * @brief Read FTU module fault detection flag
 *
 * @param pFtu the base address of the FTU instance
 * @return FTU fault detection flag
 */
LOCAL_INLINE uint8_t FTU_HWA_ReadModuleFaultDetectionFlag(FTU_Type *pFtu)
{
	return (uint8_t)((pFtu->FMS & (uint32_t)FTU_FMS_FAULTF_MASK) >> FTU_FMS_FAULTF_SHIFT);
}

/**
 * @brief Enable FTU module channel(n) output
 *
 * @param pFtu the base address of the FTU instance
 * @param u8ChannelMask 0-7 bit indicate 0-7 channel
 */
LOCAL_INLINE void FTU_HWA_EnableChannelsOutput(FTU_Type *pFtu, uint8_t u8ChannelMask)
{
    pFtu->SC |= (uint32_t)FTU_SC_CHNOUTEN(u8ChannelMask);
}

/**
 * @brief Get cpwm mode of the FTU module
 *
 * @param pFtu the base address of the FTU instance
 * @return cpwm mode bit value of the FTU module
 */
LOCAL_INLINE uint8_t FTU_HWA_GetModuleCpwmMode(FTU_Type *pFtu)
{
	return (uint8_t)((pFtu->SC & (uint32_t)FTU_SC_CPWMS_MASK) >> FTU_SC_CPWMS_SHIFT);
}

/**
 * @brief Enable FTU module cpwm mode
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableModuleCpwmMode(FTU_Type *pFtu)
{
    pFtu->SC |= (uint32_t)FTU_SC_CPWMS_MASK;
}

/**
 * @brief Disable FTU module cpwm mode
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableModuleCpwmMode(FTU_Type *pFtu)
{
    pFtu->SC &= ~(uint32_t)FTU_SC_CPWMS_MASK;
}

/**
 * @brief Set FTU module filter prescale
 *
 * @param pFtu the base address of the FTU instance
 * @param eFilterPs FTU clock filter prescaler enumeration
 */
LOCAL_INLINE void FTU_HWA_ConfigModuleFilterPrescale(FTU_Type *pFtu, FTU_FilterPrescalerType eFilterPs)
{
    pFtu->SC = (pFtu->SC & (~(uint32_t)FTU_SC_FLTPS_MASK))
    		 | FTU_SC_FLTPS(eFilterPs);
}

#ifdef FTU_TCKSEL_EXIST
/**
 * @brief Selects the external clock as the FTU function clock
 *
 * @param pFtu the base address of the FTU instance
 * @param eTclk FTU external clock  enumeration
 */
LOCAL_INLINE void FTU_HWA_ConfigExternalClkSrc(FTU_Type *pFtu, FTU_TclkSelType eTclk)
{
	pFtu->SC = (pFtu->SC & (~(uint32_t)FTU_SC_TCKSEL_MASK))
			 | FTU_SC_TCKSEL(eTclk);
}
#endif

LOCAL_INLINE void FTU_HWA_ConfigChannelMode(FTU_Type *pFtu, uint8_t u8Channel, FTU_ChannelModeType eMode)
{
	pFtu->CONTROLS[u8Channel].CSCn = 	(		pFtu->CONTROLS[u8Channel].CSCn
											& 	(~(uint32_t)(FTU_CSC_MSB_MASK | FTU_CSC_MSA_MASK)))
									 | 	(		((uint32_t)eMode << FTU_CSC_MSA_SHIFT)
											& 	((uint32_t)(FTU_CSC_MSB_MASK | FTU_CSC_MSA_MASK)));
}

LOCAL_INLINE void FTU_HWA_ConfigChannelEdgeLevel(FTU_Type *pFtu, uint8_t u8Channel, FTU_ChannelEdgeLevelType eEdgeLevel)
{
	pFtu->CONTROLS[u8Channel].CSCn = 	(pFtu->CONTROLS[u8Channel].CSCn & (~(uint32_t)(FTU_CSC_ELSB_MASK | FTU_CSC_ELSA_MASK)))
									 | 	(((uint32_t)eEdgeLevel << FTU_CSC_ELSA_SHIFT) & (uint32_t)(FTU_CSC_ELSB_MASK | FTU_CSC_ELSA_MASK));
}
#ifdef FTU_ICM_FEATURE
LOCAL_INLINE uint8_t FTU_HWA_GetEdgeNumberCount(FTU_Type *pFtu, uint8_t u8Channel)
{
	return (uint8_t)((pFtu->CONTROLS[u8Channel].CSCn & FTU_CSC_ICM_ICEXP_NUM_ICM_ECNT_MASK) >> FTU_CSC_ICM_ICEXP_NUM_ICM_ECNT_SHIFT);
}

LOCAL_INLINE void FTU_HWA_ConfigEdgeNumber(FTU_Type *pFtu, uint8_t u8Channel, uint8_t u8EdgeNumber)
{
	pFtu->CONTROLS[u8Channel].CSCn = 	(	pFtu->CONTROLS[u8Channel].CSCn
											& ((uint32_t)(~FTU_CSC_ICM_ICEXP_NUM_ICM_ECNT_MASK)))
									| 	FTU_CSC_ICM_ICEXP_NUM_ICM_ECNT(u8EdgeNumber);
}

/**
 * @brief Re-start measurement when in single mode
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_SingleMeasurement(FTU_Type *pFtu, uint8_t u8Channel)
{
	pFtu->CONTROLS[u8Channel].CSCn |= (uint32_t)FTU_CSC_ICM_SINGLE_MASK;
}
/**
 * @brief Set the measurement channel to continuous mode
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_EnableMeasureContinous(FTU_Type *pFtu, uint8_t u8Channel)
{
	pFtu->CONTROLS[u8Channel].CSCn |= (uint32_t)FTU_CSC_ICM_CONT_MASK;
}
/**
 * @brief Set the measurement channel to single mode
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_DisableMeasureContinous(FTU_Type *pFtu, uint8_t u8Channel)
{
	pFtu->CONTROLS[u8Channel].CSCn &= ~(uint32_t)FTU_CSC_ICM_CONT_MASK;
}
/**
 * @brief Set the channel starts measuring after the first edge is detected
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_EnableMeasureStartImmd(FTU_Type *pFtu, uint8_t u8Channel)
{
	pFtu->CONTROLS[u8Channel].CSCn |= (uint32_t)FTU_CSC_ICM_START_MASK;
}

LOCAL_INLINE void FTU_HWA_ConfigInputCaptureMeasureMode(FTU_Type *pFtu, uint8_t u8Channel, FTU_MeasurementModeType eMode)
{
	pFtu->CONTROLS[u8Channel].CSCn = 	(pFtu->CONTROLS[u8Channel].CSCn & (~(uint32_t)FTU_CSC_ICM_MODE_MASK))
									 | 	FTU_CSC_ICM_MODE(eMode);
}

/**
 * @brief Set the measurement starts immediately after activating the channel
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_DisableMeasureStartImmd(FTU_Type *pFtu, uint8_t u8Channel)
{
	pFtu->CONTROLS[u8Channel].CSCn &= ~(uint32_t)FTU_CSC_ICM_START_MASK;
}

/**
 * @brief Get channel measure mode
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel
 * @return measure mode
 */
LOCAL_INLINE FTU_MeasurementModeType FTU_HWA_GetMeasureMode(FTU_Type *pFtu, uint8_t u8Channel)
{
	return (FTU_MeasurementModeType)((pFtu->CONTROLS[u8Channel].CSCn & FTU_CSC_ICM_MODE_MASK) >> FTU_CSC_ICM_MODE_SHIFT);
}
#endif
/**
 * @brief Configure Edge-Aligned pwm mode channel to High-true pulses(clear output on match)
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_SetChannelEpwmHighTrue(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CONTROLS[u8Channel].CSCn =  (pFtu->CONTROLS[u8Channel].CSCn & (~(uint32_t)FTU_CSC_ELSA_MASK))
    								| ((uint32_t)(FTU_CSC_MSB_MASK | FTU_CSC_ELSB_MASK));
}

/**
 * @brief Configure Edge-Aligned pwm mode channel to Low-true pulses(set output on match)
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_SetChannelEpwmLowTrue(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CONTROLS[u8Channel].CSCn |= (uint32_t)(FTU_CSC_MSB_MASK | FTU_CSC_ELSA_MASK);
}

/**
 * @brief Configure pwm link mode channel
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_ConfigChannelPwmLinkMode(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CONTROLS[u8Channel].CSCn =  (		pFtu->CONTROLS[u8Channel].CSCn
    									& 	(~(uint32_t)(FTU_CSC_ELSA_MASK | FTU_CSC_MSB_MASK | FTU_CSC_MSA_MASK)))
    								| ((uint32_t)FTU_CSC_ELSB_MASK);
}

/**
 * @brief Enable FTU channel interrupt
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_EnableChannelInterrupt(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CONTROLS[u8Channel].CSCn |= (uint32_t)FTU_CSC_CHIE_MASK;
}

/**
 * @brief Set MODE[FTUEN], this field define different free running counter and synchronization behavior.
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_SetModuleUpdateRegBySync(FTU_Type *pFtu)
{
    pFtu->MODE |= (uint32_t)FTU_MODE_FTUEN_MASK;
}

/**
 * @brief Clear MODE[FTUEN], this field define different free running counter and synchronization behavior.
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearModuleUpdateRegBySync(FTU_Type *pFtu)
{
    pFtu->MODE &= ~(uint32_t)FTU_MODE_FTUEN_MASK;
}

/**
 * @brief Enable FTU module fault interrupt
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableModuleFaultInterrupt(FTU_Type *pFtu)
{
    pFtu->MODE |= (uint32_t)FTU_MODE_FAULTIE_MASK;
}


/**
 * @brief Enable FTU channel dma
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_EnableChannelDma(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CONTROLS[u8Channel].CSCn |= (uint32_t)FTU_CSC_DMA_MASK;
}


/**
 * @brief Configure FTU module fault mode
 *
 * @param pFtu the base address of the FTU instance
 * @param eMode Fault mode type
 */
LOCAL_INLINE void FTU_HWA_ConfigModuleFaultMode(FTU_Type *pFtu, FTU_FaultModeType eMode)
{
    pFtu->MODE = (pFtu->MODE & (~(uint32_t)FTU_MODE_FAULTM_MASK))
				| FTU_MODE_FAULTM(eMode);
}

/**
 * @brief Enable synchronization hardware trigger 0
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableTrigger0Sync(FTU_Type *pFtu)
{
    pFtu->SYNC |= (uint32_t)FTU_SYNC_TRIG0_MASK;
}

/**
 * @brief Enable synchronization hardware trigger 1
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableTrigger1Sync(FTU_Type *pFtu)
{
    pFtu->SYNC |= (uint32_t)FTU_SYNC_TRIG1_MASK;
}

/**
 * @brief Enable synchronization hardware trigger 2
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableTrigger2Sync(FTU_Type *pFtu)
{
    pFtu->SYNC |= (uint32_t)FTU_SYNC_TRIG2_MASK;
}

/**
 * @brief Enable FTU module output mask synchronization
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableOutputMaskBySync(FTU_Type *pFtu)
{
    pFtu->SYNC |= (uint32_t)FTU_SYNC_SYNCHOM_MASK;
}

/**
 * @brief Disable FTU module output mask synchronization
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableOutputMaskBySync(FTU_Type *pFtu)
{
    pFtu->SYNC &= ~(uint32_t)FTU_SYNC_SYNCHOM_MASK;
}

/**
 * @brief Generate FTU software trigger
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_GenerateSwSync(FTU_Type *pFtu)
{
    pFtu->SYNC |= (uint32_t)FTU_SYNC_SWSYNC_MASK;
}

/**
 * @brief Configure FTU trigger mode
 *
 * @param pFtu the base address of the FTU instance
 * @param eTrigMode Trigger mode type
 */
LOCAL_INLINE void FTU_HWA_ConfigTrigMode(FTU_Type *pFtu, FTU_TrigModeType eTrigMode)
{
	pFtu->SYNCONF = 	(pFtu->SYNCONF & (~(uint32_t)FTU_SYNCONF_HWTRIGMODE_MASK))
					 | 	(uint32_t)FTU_SYNCONF_HWTRIGMODE(eTrigMode);
}

/**
 * @brief Enable channel(n/n+1) deadtime functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_EnableChannelDeadtime(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL |= FTU_CHCTRL_DEADTIME_CHANNEL(u8Channel);
}

/**
 * @brief Enable channel(n/n+1) complement functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_EnableChannelComplement(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL |= FTU_CHCTRL_COMPLEMENT_CHANNEL(u8Channel);
}

/**
 * @brief Enable channel(n/n+1) synchronization functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_EnableChannelSync(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL |= FTU_CHCTRL_SYNCEN_CHANNEL(u8Channel);
}

/**
 * @brief Enable channel(n/n+1) Phase Shift Mode functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_EnableChannelPhase(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL |= FTU_CHCTRL_PHASE_CHANNEL(u8Channel);
}
/**
 * @brief Disable channel(n/n+1) Phase Shift Mode functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_DisableChannelPhase(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL &= ~FTU_CHCTRL_PHASE_CHANNEL(u8Channel);
}
/**
 * @brief Enable channel(n/n+1) Enhanced Phase Shift Mode functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_EnableChannelEnhancedPhase(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL |= FTU_CHCTRL_EPHASE_CHANNEL(u8Channel);
}
/**
 * @brief Disable channel(n/n+1) Enhanced Phase Shift Mode functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_DisableChannelEnhancedPhase(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL &= ~FTU_CHCTRL_EPHASE_CHANNEL(u8Channel);
}

/**
 * @brief Enable channel(n/n+1) fault functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_EnableChannelFault(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL |= FTU_CHCTRL_FAULT_CHANNEL(u8Channel);
}

/**
 * @brief Enable channel trigger out
 *
 * @param pFtu the base address of the FTU instance
 * @param u8ChannelMask FTU channel mask, bit 0-7 indicate channel 0-7
 */
LOCAL_INLINE void FTU_HWA_EnableChannelTriggerOut(FTU_Type *pFtu, uint8_t u8ChannelMask)
{
    pFtu->TRIGCONF = 	pFtu->TRIGCONF
    				| 	FTU_TRIGCONF_CH7TRIG(((uint32_t)u8ChannelMask >> 7u) & 1u)
					|	FTU_TRIGCONF_CH6TRIG(((uint32_t)u8ChannelMask >> 6u) & 1u)
					|	FTU_TRIGCONF_CH5TRIG(((uint32_t)u8ChannelMask >> 5u) & 1u)
					|	FTU_TRIGCONF_CH4TRIG(((uint32_t)u8ChannelMask >> 4u) & 1u)
					|	FTU_TRIGCONF_CH3TRIG(((uint32_t)u8ChannelMask >> 3u) & 1u)
					|	FTU_TRIGCONF_CH2TRIG(((uint32_t)u8ChannelMask >> 2u) & 1u)
					|	FTU_TRIGCONF_CH1TRIG(((uint32_t)u8ChannelMask >> 1u) & 1u)
					|	FTU_TRIGCONF_CH0TRIG((uint32_t)u8ChannelMask & 1u);
}

/**
 * @brief Disable channel trigger out
 *
 * @param pFtu the base address of the FTU instance
 * @param u8ChannelMask FTU channel mask, bit 0-7 indicate channel 0-7
 */
LOCAL_INLINE void FTU_HWA_DisableChannelTriggerOut(FTU_Type *pFtu, uint8_t u8ChannelMask)
{
    pFtu->TRIGCONF &= 	(~(		FTU_TRIGCONF_CH7TRIG(((uint32_t)u8ChannelMask >> 7u) & 1u)
							|	FTU_TRIGCONF_CH6TRIG(((uint32_t)u8ChannelMask >> 6u) & 1u)
							|	FTU_TRIGCONF_CH5TRIG(((uint32_t)u8ChannelMask >> 5u) & 1u)
							|	FTU_TRIGCONF_CH4TRIG(((uint32_t)u8ChannelMask >> 4u) & 1u)
							|	FTU_TRIGCONF_CH3TRIG(((uint32_t)u8ChannelMask >> 3u) & 1u)
							|	FTU_TRIGCONF_CH2TRIG(((uint32_t)u8ChannelMask >> 2u) & 1u)
							|	FTU_TRIGCONF_CH1TRIG(((uint32_t)u8ChannelMask >> 1u) & 1u)
							|	FTU_TRIGCONF_CH0TRIG((uint32_t)u8ChannelMask & 1u)));
}

/**
 * @brief clear the channel trigger flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearChannelTriggerFlag(FTU_Type *pFtu)
{
	pFtu->TRIGCONF &= ~FTU_TRIGCONF_TRIGF_MASK;
}

/**
 * @brief Enable reload trigger
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableReloadTrigger(FTU_Type *pFtu)
{
    pFtu->TRIGCONF |= (uint32_t)FTU_TRIGCONF_RELOADTRIGEN_MASK;
}

/**
 * @brief Set channel polarity
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Mask FTU channel mask, bit 0-7 indicate channel 0-7
 */
LOCAL_INLINE void FTU_HWA_SetChannelPolarity(FTU_Type *pFtu, uint8_t u8Mask)
{
    pFtu->POL |= FTU_POL_POLN(u8Mask);
}

/**
 * @brief Set FTU module outmask
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel Bit of channel indicate channel number, range: 0~7 bit
 */
LOCAL_INLINE void FTU_HWA_ConfigModuleOutmask(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->OUTMASK = 	(pFtu->OUTMASK & (~(uint32_t)0xFFU))
    				 |  ((uint32_t)u8Channel & (uint32_t)0xFFU);
}

/**
 * @brief Set channel filter value
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-3
 * @param u8FilterVal FTU filter value
 */
LOCAL_INLINE void FTU_HWA_ConfigChannelFilterValue(FTU_Type *pFtu, uint8_t u8Channel, uint8_t u8FilterVal)
{
    pFtu->FILTER = 		(pFtu->FILTER & (~((uint32_t)0xFu << ((uint32_t)u8Channel << 2U))))
    				| 	((uint32_t)u8FilterVal << ((uint32_t)u8Channel << 2U));
}

/**
 * @brief Configure quadrature mode
 *
 * @param pFtu the base address of the FTU instance
 * @param eMode FTU quadrature mode
 */
LOCAL_INLINE void FTU_HWA_ConfigQuadratureMode(FTU_Type *pFtu, FTU_QuadratureModeType eMode)
{
	pFtu->QDCTRL = 		(pFtu->QDCTRL & (~(uint32_t)FTU_QDCTRL_QUADMODE_MASK))
    				| 	((uint32_t)FTU_QDCTRL_QUADMODE(eMode));
}

/**
 * @brief inverted polarity of phase B input signal
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnablePhbInv(FTU_Type *pFtu)
{
    pFtu->QDCTRL |= (uint32_t)FTU_QDCTRL_PHBPOL_MASK;
}

/**
 * @brief do not inverted polarity of phase B input signal
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisablePhbInv(FTU_Type *pFtu)
{
	pFtu->QDCTRL &= ~(uint32_t)FTU_QDCTRL_PHBPOL_MASK;
}

/**
 * @brief inverted polarity of phase A input signal
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnablePhaInv(FTU_Type *pFtu)
{
    pFtu->QDCTRL |= (uint32_t)FTU_QDCTRL_PHAPOL_MASK;
}

/**
 * @brief do not inverted polarity of phase B input signal
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisablePhaInv(FTU_Type *pFtu)
{
	pFtu->QDCTRL &= ~(uint32_t)FTU_QDCTRL_PHAPOL_MASK;
}

/**
 * @brief Enable phase A glitch filter
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnablePhaGlitchFilter(FTU_Type *pFtu)
{
    pFtu->QDCTRL |= (uint32_t)FTU_QDCTRL_PHAGFEN_MASK;
}

/**
 * @brief Disable phase A glitch filter
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisablePhaGlitchFilter(FTU_Type *pFtu)
{
    pFtu->QDCTRL &= ~(uint32_t)FTU_QDCTRL_PHAGFEN_MASK;
}

/**
 * @brief Enable phase B glitch filter
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnablePhbGlitchFilter(FTU_Type *pFtu)
{
    pFtu->QDCTRL |= (uint32_t)FTU_QDCTRL_PHBGFEN_MASK;
}

/**
 * @brief Disable phase B glitch filter
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisablePhbGlitchFilter(FTU_Type *pFtu)
{
    pFtu->QDCTRL &= ~(uint32_t)FTU_QDCTRL_PHBGFEN_MASK;
}

/**
 * @brief Enable FTU module quadrature mode
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableQuadratureMode(FTU_Type *pFtu)
{
    pFtu->QDCTRL |= (uint32_t)FTU_QDCTRL_QUADEN_MASK;
}

/**
 * @brief Disable FTU module quadrature mode
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableQuadratureMode(FTU_Type *pFtu)
{
    pFtu->QDCTRL &= ~(uint32_t)FTU_QDCTRL_QUADEN_MASK;
}

/**
 * @brief Configure FTU module debug mode
 *
 * @param pFtu the base address of the FTU instance
 * @param eDbgMode debug mode enumeration
 */
LOCAL_INLINE void FTU_HWA_ConfigModuleDebugMode(FTU_Type *pFtu, FTU_DebugModeType eDbgMode)
{
    pFtu->CONF = 	(pFtu->CONF & (~(uint32_t)FTU_CONF_DBG_MASK))
    			| 	FTU_CONF_DBG(eDbgMode);
}

/**
 * @brief Set FTU module clock source
 *
 * @param pFtu the base address of the FTU instance
 * @param eClkSrc FTU module clock source type
 */
LOCAL_INLINE void FTU_HWA_ConfigModuleClkSrc(FTU_Type *pFtu, FTU_ModuleClkSrcType eClkSrc)
{
    pFtu->SC = (pFtu->SC & (~(uint32_t)FTU_SC_CLKS_MASK))
    		 | FTU_SC_CLKS(eClkSrc);
}

/**
 * @brief Clear FTU module overflow flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearOverflowFlag(FTU_Type *pFtu)
{
    pFtu->SC &= ~(uint32_t)FTU_SC_TOF_MASK;
}

/**
 * @brief Clear FTU module reload flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearReloadFlag(FTU_Type *pFtu)
{
    pFtu->SC &= ~(uint32_t)FTU_SC_RF_MASK;
}

/**
 * @brief Enable FTU module interrupt
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_EnableOverflowInterrupt(FTU_Type *pFtu)
{
    pFtu->SC |= (uint32_t)FTU_SC_TOIE_MASK;
}

/**
 * @brief Disable FTU module overflow interrupt
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableOverflowInterrupt(FTU_Type *pFtu)
{
    pFtu->SC &= ~(uint32_t)FTU_SC_TOIE_MASK;
}

/**
 * @brief Clear FTU channel interrupt flag
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_ClearChannelInterruptFlag(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CONTROLS[u8Channel].CSCn &= ~(uint32_t)FTU_CSC_CHF_MASK;
}

/**
 * @brief Disable channel interrupt
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 */
LOCAL_INLINE void FTU_HWA_DisableChannelInterrupt(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CONTROLS[u8Channel].CSCn &= ~(uint32_t)FTU_CSC_CHIE_MASK;
}

/**
 * @brief Disable write protection
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableWriteProtection(FTU_Type *pFtu)
{
    pFtu->MODE |= (uint32_t)FTU_MODE_WPDIS_MASK;
}

/**
 * @brief Disable FTU module fault interrupt
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableModuleFaultInterrupt(FTU_Type *pFtu)
{
    pFtu->MODE &= ~(uint32_t)FTU_MODE_FAULTIE_MASK;
}

/**
 * @brief Disable synchronization hardware trigger 0
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableTrigger0Sync(FTU_Type *pFtu)
{
    pFtu->SYNC &= ~(uint32_t)FTU_SYNC_TRIG0_MASK;
}

/**
 * @brief Disable synchronization hardware trigger 1
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableTrigger1Sync(FTU_Type *pFtu)
{
    pFtu->SYNC &= ~(uint32_t)FTU_SYNC_TRIG1_MASK;
}

/**
 * @brief Disable synchronization hardware trigger 2
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableTrigger2Sync(FTU_Type *pFtu)
{
    pFtu->SYNC &= ~(uint32_t)FTU_SYNC_TRIG2_MASK;
}

/**
 * @brief Disable generate FTU software trigger
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableGenerateSwSync(FTU_Type *pFtu)
{
    pFtu->SYNC &= ~(uint32_t)FTU_SYNC_SWSYNC_MASK;
}

/**
 * @brief Disable reload trigger
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_DisableReloadTrigger(FTU_Type *pFtu)
{
    pFtu->TRIGCONF &= ~(uint32_t)FTU_TRIGCONF_RELOADTRIGEN_MASK;
}

/**
 * @brief Disable channel(n/n+1) deadtime functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_DisableChannelDeadtime(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL &= ~FTU_CHCTRL_DEADTIME_CHANNEL(u8Channel);
}

/**
 * @brief Disable channel(n/n+1) complement functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_DisableChannelComplement(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL &= ~FTU_CHCTRL_COMPLEMENT_CHANNEL(u8Channel);
}

/**
 * @brief Disable channel(n/n+1) synchronization functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_DisableChannelSync(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL &= ~FTU_CHCTRL_SYNCEN_CHANNEL(u8Channel);
}

/**
 * @brief Disable channel(n/n+1) fault functionality
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel channel number, range is 0-7
 */
LOCAL_INLINE void FTU_HWA_DisableChannelFault(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->CHCTRL &= ~FTU_CHCTRL_FAULT_CHANNEL(u8Channel);
}

/**
 * @brief Clear channel polarity
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel, bit 0-7 indicate channel 0-7
 */
LOCAL_INLINE void FTU_HWA_ClearChannelPolarity(FTU_Type *pFtu, uint8_t u8Channel)
{
    pFtu->POL &= ~FTU_POL_POLN(u8Channel);
}

/**
 * @brief Get channel polarity
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Channel FTU channel, bit 0-7 indicate channel 0-7
 * @return polarity of the channels
 */
LOCAL_INLINE uint32_t FTU_HWA_GetChannelPolarity(FTU_Type *pFtu, uint8_t u8Channel)
{
	return pFtu->POL & FTU_POL_POLN(u8Channel);
}

/**
 * @brief Clear FTU module fault flag
 *
 * @param pFtu the base address of the FTU instance
 * @param u8Flag bit 0-3 indicate fault flag 0-3.
 */
LOCAL_INLINE void FTU_HWA_ClearModuleFaultFlag(FTU_Type *pFtu, uint8_t u8Flag)
{
    pFtu->FMS &= ~(uint32_t)((uint32_t)u8Flag & 0xFu);
}

/**
 * @brief Get FTU Counter Direction In Quadrature Decoder Mode
 *
 * @param pFtu the base address of the FTU instance
 * @return FTU Counter Direction In Quadrature Decoder Mode
 */
LOCAL_INLINE FTU_QuadratureDirectionType FTU_HWA_GetQuadDirection(FTU_Type *pFtu)
{
	return (FTU_QuadratureDirectionType)((pFtu->QDCTRL & FTU_QDCTRL_QUADIR_MASK)
										  >> FTU_QDCTRL_QUADIR_SHIFT);
}

/**
 * @brief Clear FTU global fault flag
 *
 * @param pFtu the base address of the FTU instance
 */
LOCAL_INLINE void FTU_HWA_ClearGlobalFaultFlag(FTU_Type *pFtu)
{
	pFtu->FMS &= ~(uint32_t)FTU_FMS_FAULTF_MASK;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_FTU_H_ */
