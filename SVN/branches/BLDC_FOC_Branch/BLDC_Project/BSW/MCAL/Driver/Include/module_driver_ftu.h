/**
 * @file module_driver_ftu.h
 * @author Flagchip032
 * @brief FTU driver type definition and API
 * @version 2.0.0
 * @date 2024-11-10
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip032   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_FTU_H_
#define _DRIVER_MODULE_DRIVER_FTU_H_

#include "HwA_ftu.h"

#if FTU_INSTANCE_COUNT > 0U

#include "stddef.h"
#if defined(FTU_GTB_CTRL_IN_SMISC)
#include "HwA_smisc.h"
#elif defined(FTU_GTB_CTRL_IN_SMISC)
#include "HwA_scm.h"
#endif
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup module_driver_ftu
 * @{
 */

/**
 * @name  FTU Channel Bit Flag
 * @brief Bit of channel indicate channel number
 *
 * @{
 */
#define BIT_FTU_CHANNEL_0   0x01U
#define BIT_FTU_CHANNEL_1   0x02U
#define BIT_FTU_CHANNEL_2   0x04U
#define BIT_FTU_CHANNEL_3   0x08U
#define BIT_FTU_CHANNEL_4   0x10U
#define BIT_FTU_CHANNEL_5   0x20U
#define BIT_FTU_CHANNEL_6   0x40U
#define BIT_FTU_CHANNEL_7   0x80U
/** @}*/

/**
 * @name  FTU API Service IDs
 *
 * @{
 */
#define FTU_COMMON_INIT_ID   			0U
#define FTU_DEINIT_ID   				1U
#define FTU_GET_DEFAULT_INIT_CFG_ID		2U
#define FTU_COUNTER_INIT_ID				3U
#define FTU_PWM_UPDATE_DUTY_ID			4U
#define FTU_PWM_UPDATE_PERIOD_ID		5U
#define FTU_PWM_SYNC_UPDATE_ID			6U
#define FTU_PWM_MODE_INIT_ID			7U
#define FTU_OC_MODE_INIT_ID				8U
#define FTU_GET_CHANNEL_VALUE_ID		9U
#define FTU_GET_COUNTER_ID				10U
#define FTU_SET_CHANNEL_VALUE_ID		11U
#define FTU_ENABLE_TRIG_OUT_ID			12U
#define FTU_DISABLE_TRIG_OUT_ID			13U
#define FTU_START_TIMER_ID				14U
#define FTU_STOP_TIMER_ID				15U
#define FTU_INTR_INIT_ID				16U
#define FTU_FAULT_INIT_ID				17U
#define FTU_FAULT_SEL_DELAY_ID			18U
#define FTU_FAULT_ENABLE_ID				19U
#define FTU_FAULT_DISABLE_ID			20U
#define FTU_IC_CHANNEL_INIT_ID			21U
#define FTU_QD_MODE_INIT_ID				22U
#define FTU_ENABLE_INTR_ID				23U
#define FTU_DISABLE_INTR_ID				24U
#define FTU_CLEAR_FAULT_ID				25U
#define FTU_GET_FAULT_FLAG_ID			26U
#define FTU_ENABLE_CHANNEL_DMA_ID		27U
#define FTU_IC_EXPENM_INIT_ID			28U
#define FTU_IC_ENM_INIT_ID				29U
#define FTU_IC_EXPENM_GET_ID			30U
#define FTU_IC_ENM_GET_ID				31U
#define FTU_IC_SIG_MEAS_INIT_ID			32U
#define FTU_IC_SIG_MEAS_SINGLE_ID		33U
#define FTU_IC_SIG_MEAS_GET_ID			34U
#define FTU_OC_MODE_UPDATE_ID			35U
/** @}*/

/**
 * @name  FTU Dev Error Code
 * @brief Error Code of calling FTU apis
 *
 * @{
 */
#define FTU_E_PARAM_INSTANCE   			0x01U
#define FTU_E_PARAM_CHANNEL   			0x02U
#define FTU_E_PARAM_POINTER   			0x03U
#define FTU_E_PARAM_COUNT				0x04U
#define FTU_E_PARAM_INVALID				0x05U
#define FTU_E_PARAM_PHASE_SHIFT			0x06U
#define FTU_E_PARAM_INVALID_CHANNEL		0x07U
/** @}*/

/**
 * @name  FTU Fault Bit Flag
 * @brief Bit of fault flag
 *
 * @{
 */
#define FTU_FAULT_INPUT_0    0x01U
#define FTU_FAULT_INPUT_1    0x02U
/** @}*/

/**
 * @brief Max number of Ftu fault channel
 *
 */
#define FTU_FAULT_CHANNEL_COUNT			4u

/**
 * @brief Max number of Ftu input count
 *
 */
#define FTU_INPUT_FILTER_COUNT	4u
/**
 * @brief FTU operation return values
 *
 */
typedef enum
{
    FTU_STATUS_SUCCESS 				= 0U,	/**< The FTU operation is success */
    FTU_STATUS_PARAM_INVALID,				/**< The FTU operation is failed because of parameter error */
	FTU_STATUS_NO_CLOCK_SOURCE,				/**< The FTU operation is failed because of instance clock source is not set */
} FTU_StatusType;

/**
 * @brief The instance index of the FTU peripheral
 *
 */
typedef enum
{
    FTU_INSTANCE_0 = 0U,
    FTU_INSTANCE_1,
    FTU_INSTANCE_2,
    FTU_INSTANCE_3,
    FTU_INSTANCE_4,
    FTU_INSTANCE_5,
#if FTU_INSTANCE_COUNT > 6
    FTU_INSTANCE_6,
    FTU_INSTANCE_7,
#endif
#if FTU_INSTANCE_COUNT > 8
	FTU_INSTANCE_8,
	FTU_INSTANCE_9,
	FTU_INSTANCE_10,
	FTU_INSTANCE_11,
#endif
} FTU_InstanceType;

/**
 * @brief The channel index of the FTU peripheral
 *
 */
typedef enum
{
    FTU_CHANNEL_0 = 0U,
    FTU_CHANNEL_1,
    FTU_CHANNEL_2,
    FTU_CHANNEL_3,
    FTU_CHANNEL_4,
    FTU_CHANNEL_5,
    FTU_CHANNEL_6,
    FTU_CHANNEL_7
} FTU_ChannelType;

/**
 * @brief The clock source of FTU peripheral
 *
 */
typedef enum
{
    FTU_NO_CLK 			= 0U,			/**< No clock selected */
    FTU_INTERNAL_CLK 	= 1U,			/**< FTU input clock */
	FTU_PCC_CLK			= 2U,			/**< FTU input PCC clock */
    FTU_EXTERNAL_CLK0 	= 3U,			/**< External pin 0 input clock */
    FTU_EXTERNAL_CLK1 	= 4U,			/**< External pin 1 input clock */
    FTU_EXTERNAL_CLK2 	= 5U			/**< External pin 2 input clock */
} FTU_ClkSrcType;

/**
 * @brief The channel operation of output compare mode
 *
 */
typedef enum
{
    FTU_OUTPUT_TOGGLE_PIN 	= FTU_CHANNEL_OC_TOGGLE,		/**< Toggle Output on match */
    FTU_OUTPUT_CLEAR_PIN	= FTU_CHANNEL_OC_CLEAR,			/**< Clear Output on match */
    FTU_OUTPUT_SET_PIN		= FTU_CHANNEL_OC_SET			/**< Set Output on match */
} FTU_OutputComparePinModeType;

/**
 * @brief The initial level of the output compare channel
 *
 */
typedef enum
{
	FTU_OUTPUT_CMP_INIT_LOW = 0U,	/**< The initial level is low */
	FTU_OUTPUT_CMP_INIT_HIGH,		/**< The initial level is high */
} FTU_OutputCompareInitLevelType;

/**
 * @brief The channel operation of PWM mode
 *
 */
typedef enum
{
    FTU_PWM_HIGH_TRUE_PULSE 	= FTU_CHANNEL_PWM_HIGH_TRUE,		/**< High-true pulses in PWM */
    FTU_PWM_LOW_TRUE_PULSE		= FTU_CHANNEL_PWM_LOW_TRUE,			/**< Low-true pulses in PWM */
} FTU_PwmPinModeType;

/**
 * @brief PWM Aligned Mode
 *
 */
typedef enum
{
	FTU_EDGE_ALIGNED_PWM 	= 0u,				/**< Edge-Aligned PWM */
	FTU_CENTER_ALIGNED_PWM						/**< Center-Aligned PWM */
}FTU_PwmAlignedType;

#ifdef FTU_ICM_FEATURE
/**
 * @brief The measurement is single or continuous
 *
 */
typedef enum
{
	FTU_MEASURE_SINGLE_MODE			= 0u,		/**< Single mode */
	FTU_MEASURE_CONTINUOUS_MODE					/**< Continuous mode */
} FTU_MeasureContModeType;

/**
 * @brief Timing of start measurement
 *
 */
typedef enum
{
	FTU_MEASURE_START_AFTER_EDGE		= 0u,	/**< The channel starts measuring after the first edge is detected */
	FTU_MEASURE_START_IMMEDIATELY				/**< The measurement starts immediately after activating the channel */
}FTU_MeasureStartModeType;

/** @brief FTU signal measurement mode type */
typedef enum
{
	FTU_SIGNAL_MEASURE_HIGH_TIME			= 0u,		/**< Measurement high time */
	FTU_SIGNAL_MEASURE_LOW_TIME				= 1u,		/**< Measurement low time */
	FTU_SIGNAL_MEASURE_PERIOD_RISING_EDGE	= 2u,		/**< Measurement period of rising edge */
	FTU_SIGNAL_MEASURE_PERIOD_FALLING_EDGE	= 3u		/**< Measurement period of falling edge */
} FTU_SignalMeasureModeType;
#endif
/**
 * @brief The reload point flag of FTU peripheral
 *
 */
typedef enum
{
	FTU_RELOAD_POINT_CNTMAX 	= 1u,			/**< Maximum Loading Point */
	FTU_RELOAD_POINT_CNTMIN		= (1u << 1),	/**< Minimum Loading Point */
	FTU_RELOAD_POINT_CHANNEL_0	= (1u << 2),	/**< Channel 0 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_1	= (1u << 3),	/**< Channel 1 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_2	= (1u << 4),	/**< Channel 2 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_3	= (1u << 5),	/**< Channel 3 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_4	= (1u << 6),	/**< Channel 4 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_5	= (1u << 7),	/**< Channel 5 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_6	= (1u << 8),	/**< Channel 6 match is included as a reload opportunity */
	FTU_RELOAD_POINT_CHANNEL_7	= (1u << 9),	/**< Channel 7 match is included as a reload opportunity */
} FTU_ReloadPointCfgType;

/**
 * @brief The synchronization flag of FTU peripheral
 *
 */
typedef enum
{
	FTU_SYNC_FLAG_FTUEN 		= 1u,			/**< FTU Enable */
	FTU_SYNC_FLAG_CNTINC		= (1u << 1),	/**< CNTIN Register Synchronization */
	FTU_SYNC_FLAG_PWMSYNC		= (1u << 2),	/**< Synchronization Mode: Selects which triggers can be used
												   by MOD, CV, OUTMASK, and FTU counter synchronization. */
	FTU_SYNC_FLAG_REINIT		= (1u << 3),	/**< FTU Counter re-initialization by Synchronization */
	FTU_SYNC_FLAG_SYNCHOM		= (1u << 4),	/**< Selects when the OUTMASK register is updated with the
												   value of its buffer */
	FTU_SYNC_FLAG_SYNCEN01		= (1u << 5),	/**< synchronization of registers C(0)V and C(1)V. */
	FTU_SYNC_FLAG_SYNCEN23		= (1u << 6),	/**< synchronization of registers C(2)V and C(3)V. */
	FTU_SYNC_FLAG_SYNCEN45		= (1u << 7),	/**< synchronization of registers C(4)V and C(5)V. */
	FTU_SYNC_FLAG_SYNCEN67		= (1u << 8),	/**< synchronization of registers C(6)V and C(7)V. */
	FTU_SYNC_FLAG_HW_TRIG0		= (1u << 9),	/**< hardware trigger 0 to the synchronization */
	FTU_SYNC_FLAG_HW_TRIG1		= (1u << 10),	/**< hardware trigger 1 to the synchronization */
	FTU_SYNC_FLAG_HW_TRIG2		= (1u << 11),	/**< hardware trigger 2 to the synchronization */
} FTU_SyncFlagType;

/**
 * @brief The interrupt enable/disable mask of FTU peripheral
 *
 */
typedef enum
{
	FTU_INTR_MASK_CHANNEL_0		= 1u,			/**< interrupt mask of channel 0 */
	FTU_INTR_MASK_CHANNEL_1		= (1u << 1),	/**< interrupt mask of channel 1 */
	FTU_INTR_MASK_CHANNEL_2		= (1u << 2),	/**< interrupt mask of channel 2 */
	FTU_INTR_MASK_CHANNEL_3		= (1u << 3),	/**< interrupt mask of channel 3 */
	FTU_INTR_MASK_CHANNEL_4		= (1u << 4),	/**< interrupt mask of channel 4 */
	FTU_INTR_MASK_CHANNEL_5		= (1u << 5),	/**< interrupt mask of channel 5 */
	FTU_INTR_MASK_CHANNEL_6		= (1u << 6),	/**< interrupt mask of channel 6 */
	FTU_INTR_MASK_CHANNEL_7		= (1u << 7),	/**< interrupt mask of channel 7 */
	FTU_INTR_MASK_OVERFLOW		= (1u << 8),	/**< interrupt mask of overflow */
	FTU_INTR_MASK_FAULT			= (1u << 9),	/**< interrupt mask of fault */
	FTU_INTR_MASK_RELOAD_POINT	= (1u << 10),	/**< interrupt mask of reload point */
} FTU_IntrMaskType;

/**
 * @brief The fault control enable/disable mask for channels
 *
 */
typedef enum
{
	FTU_FAULT_FOR_CHANNEL01	= 1u,				/**< fault control for channel 0 and channel 1 */
	FTU_FAULT_FOR_CHANNEL23	= (1u << 1),		/**< fault control for channel 2 and channel 3 */
	FTU_FAULT_FOR_CHANNEL45	= (1u << 2),		/**< fault control for channel 4 and channel 5 */
	FTU_FAULT_FOR_CHANNEL67	= (1u << 3),		/**< fault control for channel 6 and channel 7 */
} FTU_FaultChannelEnableType;

/**
 * @brief the fault input polarity
 *
 */
typedef enum
{
	FTU_FAULT_POL_ACTIVE_HIGH 	= 0u,			/**< The fault input polarity is active high.
													 1 at the fault input indicates a fault */
	FTU_FAULT_POL_ACTIVE_LOW	= 1u,			/**< The fault input polarity is active low.
													 0 at the fault input indicates a fault */
}FTU_FaultPolActiveType;

/**
 * @brief the output trigger mask
 *
 */
typedef enum
{
	FTU_TRIG_OUTPUT_MASK_CHANNEL_0_MATCH 	= 1u,			/**< Enables/Disables the channel 0 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_1_MATCH 	= (1u << 1),	/**< Enables/Disables the channel 1 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_2_MATCH 	= (1u << 2),	/**< Enables/Disables the channel 2 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_3_MATCH 	= (1u << 3),	/**< Enables/Disables the channel 3 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_4_MATCH 	= (1u << 4),	/**< Enables/Disables the channel 4 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_5_MATCH 	= (1u << 5),	/**< Enables/Disables the channel 5 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_6_MATCH 	= (1u << 6),	/**< Enables/Disables the channel 6 match trigger */
	FTU_TRIG_OUTPUT_MASK_CHANNEL_7_MATCH 	= (1u << 7),	/**< Enables/Disables the channel 7 match trigger */
	FTU_TRIG_OUTPUT_MASK_ALL_CHANNEL_MATCH	= (0xFFu),		/**< Enables/Disables all channel match trigger */
	FTU_TRIG_OUTPUT_MASK_RELOAD 		 	= (1u << 8),	/**< Enables/Disables reload trigger */
}FTU_TriggerOutputMaskType;

/** @brief Ftu input capture mode */
typedef enum
{
    FTU_INPUT_RISING_EDGE 	= FTU_CHANNEL_EDGE_RISING,								/**< capture on rising edge only */
    FTU_INPUT_FALLING_EDGE	= FTU_CHANNEL_EDGE_FALLING,									/**< capture on falling edge only */
    FTU_INPUT_BOTH_EDGE		= FTU_CHANNEL_EDGE_BOTH									/**< capture on rising or falling edge */
} FTU_InputCapturePinModeType;

/** @brief Ftu Global Time Base instance start mask */
typedef enum
{
	FTU_GTB_INSTANCE_START_FTU0		= 1u,				/**< FTU0 GTB start */
	FTU_GTB_INSTANCE_START_FTU1		= (1u << 1),		/**< FTU1 GTB start */
	FTU_GTB_INSTANCE_START_FTU2		= (1u << 2),		/**< FTU2 GTB start */
	FTU_GTB_INSTANCE_START_FTU3		= (1u << 3),		/**< FTU3 GTB start */
	FTU_GTB_INSTANCE_START_FTU4		= (1u << 4),		/**< FTU4 GTB start */
	FTU_GTB_INSTANCE_START_FTU5		= (1u << 5),		/**< FTU5 GTB start */
	FTU_GTB_INSTANCE_START_FTU6		= (1u << 6),		/**< FTU6 GTB start */
	FTU_GTB_INSTANCE_START_FTU7		= (1u << 7),		/**< FTU7 GTB start */
} FTU_GlobalTimeBaseStartInstanceType;

/** @brief Ftu Global Time Base start mask */
typedef enum
{
	FTU_GTB_START_AT_ONCE 			= 1u,				/**< GTB start at once */
	FTU_GTB_START_AT_TSTMP1_MOD0 	= (1u << 1),		/**< GTB start at modulate timer 0 of TSTMP1 */
	FTU_GTB_START_AT_TSTMP1_MOD1 	= (1u << 2),		/**< GTB start at modulate timer 1 of TSTMP1 */
	FTU_GTB_START_AT_TSTMP1_MOD2 	= (1u << 3),		/**< GTB start at modulate timer 2 of TSTMP1 */
	FTU_GTB_START_AT_TSTMP1_MOD3 	= (1u << 4),		/**< GTB start at modulate timer 3 of TSTMP1 */
} FTU_GlobalTimeBaseStartType;

#ifdef FTU_ICM_FEATURE
/** @brief FTU signal measurement configuration type */
typedef struct
{
	uint8_t 					u8Channel;				/**< selected FTU channel */
	FTU_SignalMeasureModeType 	eMeasureMode;			/**< signal measurement mode type */
	FTU_MeasureContModeType   	eContinuouslyMode;		/**< The measurement is single or continuous */
	FTU_MeasureStartModeType	eStartMode;				/**< Timing of start measurement */
} FTU_SignalMeasureType;

/** @brief FTU signal measurement result time */
typedef struct
{
	uint32_t u32StartTime;								/**< start time of measured signal */
	uint32_t u32EndTime;								/**< end time of measured signal */
} FTU_SignalMeasureValueType;

/** @brief Expect edge number result time */
typedef struct
{
	uint32_t u32FirstEdgeTime;							/**< first edge time of measured signal */
	uint32_t u32LastEdgeTime;							/**< last edge time of measured signal */
} FTU_ExpectEdgeNumberResultType;

/** @brief FTU edge number measurement configuration type */
typedef struct
{
	uint8_t 					u8Channel;			/**< selected FTU channel */
	FTU_InputCapturePinModeType	eEdgeMode;			/**< input capture mode */
	FTU_MeasureContModeType   	eContinuouslyMode;	/**< The measurement is single or continuous */
	uint32_t 					u32StartWindow;		/**< start-point window */
	uint32_t					u32EndWindow;		/**< end-point window */
} FTU_EdgeNumberMeasureType;

/** @brief FTU expect edge number measurement configuration type */
typedef struct
{
	uint8_t 					u8Channel;			/**< selected FTU channel */
	FTU_InputCapturePinModeType	eEdgeMode;			/**< input capture mode */
	uint8_t						u8ExpectEdgeNumber;	/**< Expected number of edges */
	FTU_MeasureContModeType   	eContinuouslyMode;	/**< The measurement is single or continuous */
} FTU_ExpectEdgeNumberMeasureType;
#endif

typedef enum
{
	FTU_PWM_UPDATE_IMMEDIATELY,					/**< Pwm duty and period update immediately */
	FTU_PWM_UPDATE_END_PERIOD,					/**< Pwm duty and period update when instance count reload */
	FTU_PWM_UPDATE_HALF_PERIOD,					/**< Pwm duty and period update when instance count overflow(only for CPWM) */
	FTU_PWM_UPDATE_BOTH_HALF_AND_END_PERIOD		/**< Pwm duty and period update both instance count overflow and reload(only for CPWM) */
}FTU_PwmUpdateModeType;

/**
 * @brief The structure of the FTU processing handle
 *
 */
typedef struct _FTU_HandleType
{
	FTU_InstanceType eInstance;		/**< FTU instance*/

	struct
	{
		FTU_ClkSrcType 				eFtuClkSrc;												/**< Ftu clock source */
		FTU_PwmUpdateModeType		aPwmUpdateMode;											/**< pwm Update Mode of Period and duty*/
		FTU_PwmAlignedType			aPwmAlignedMode;										/**< pwm Aligned Mode */
		uint8_t						u8PhaseShiftEnable;										/**< phase shift enable flag of each channel */
		uint32_t					u32PwmPeriod;											/**< pwm period (timer ticks) */
		void (*pChannelCallback)(struct _FTU_HandleType *pHandle, uint32_t u32Channel, uint32_t u32Timestamp);	/**< channel interrupt callback */
		void (*pFaultCallback)(struct _FTU_HandleType *pHandle, uint32_t u32Fault);			/**< fault interrupt callback */
		void (*pOverflowCallback)(struct _FTU_HandleType *pHandle);							/**< overflow interrupt callback */
		void (*pReloadPointCallback)(struct _FTU_HandleType *pHandle);						/**< reload point interrupt callback */
	} tStatus;
} FTU_HandleType;

/**
 * @brief The configuration for the Pwm channel
 *
 */
typedef struct
{
    uint8_t u8Channel;                    /**< selected FTU channel */
    FTU_PwmPinModeType ePinMode;          /**< pwm mode */
    uint32_t u32PwmDuty;                  /**< pwm duty (timer ticks) */
    uint32_t u32PhaseShift;				  /**< pwm phase shift (timer ticks)*/
    bool bLinkMode;                       /**< pwm channel link mode enable, channel num must be even,and the linked channel is current_channel+1*/
    bool bLinkChannelComplement;          /**< pwm link channel output complement */
    bool bDeadtimeEnable;				  /**< Deadtime Enable */
    uint32_t u32ChannelDeadtime;          /**< The separated deadtime (source clock ticks) */
} FTU_PwmChannelType;

/**
 * @brief The configuration option for the Pwm Mode
 *
 */
typedef struct
{
    uint32_t u32PwmPeriod;                	/**< pwm period (timer ticks) */
    FTU_PwmAlignedType	eAlignedMode;	  	/**< pwm Aligned Mode */
    FTU_PwmUpdateModeType	eUpdateMode;	/**< pwm Update Mode of Period and duty*/
    uint32_t u32ChannelCount;			  	/**< channel count of the Ftu instance */
    FTU_PwmChannelType *pPwmChannels;	  	/**< point to the pwm channel  */
} FTU_PwmModeType;

/**
 * @brief The configuration option for the output compare mode
 *
 */
typedef struct
{
    uint8_t u8Channel;                              /**< selected FTU channel */
    FTU_OutputComparePinModeType eOutputMode;       /**< ouput compare mode */
    uint32_t u32CompareValue;                       /**< output compare value (timer ticks) */
} FTU_OutputCompareModeType;

/**
 * @brief The configuration option for the time counter mode
 *
 */
typedef struct
{
    uint32_t u32CounterValue;                       /**< counter overflow value (timer ticks) */
    uint32_t u32InitialValue;						/**< counter initial value (timer ticks) */
} FTU_CounterModeType;

/**
 * @brief The configuration option for update PWM Duty
 *
 */
typedef struct
{
	uint8_t 	u8Channel;		/**< the selected FTU channel */
	uint32_t 	u32Duty;		/**< duty cycle */
	uint32_t	u32PhaseShift;	/**< phase shift of the PWM channel(only available for phase shift channel) */
	bool		bUpdate;		/**< whether to allow the update to take effect(not available for FTU_PWM_UPDATE_IMMEDIATELY) */
} FTU_PwmDutyUpdateType;

/**
 * @brief The basic configuration option for the FTU peripheral
 *
 */
typedef struct
{
    FTU_PrescalerType 		ePrescaler;            													/**< Ftu prescaler */
    FTU_ClkSrcType 			eClkSrc;                												/**< Ftu clock source */
	FTU_FilterPrescalerType eFliterPrescaler;														/**< Select the prescaler of the FTU filter */
    uint32_t				u32OverflowValue;														/**< Ftu modulo value */
    uint8_t					u8ReloadFreq;															/**< Frequency of the Reload Opportunities. Range is 0-31, */
    FTU_TrigModeType		eHwTrigMode;															/**< hardware trigger mode */
    FTU_DebugModeType 		eDbgMode;																/**< Ftu debug mode */
#ifdef FTU_UPDOWN_DIS_FEATURE
    FTU_UpDownDisableType	eUpDownDisable;															/**< Disable channel match trigger/interrupt when count-up/down in CPWM/QUAD mode */
#endif
    bool					bGtbEnable;																/**< Global Time Base Enable */
    uint32_t 				u32InterruptMask;														/**< interrupt enable mask */
    void (*pChannelCallback)(FTU_HandleType *pHandle, uint32_t u32Channel, uint32_t u32Timestamp);	/**< channel interrupt callback */
	void (*pFaultCallback)(FTU_HandleType *pHandle, uint32_t u32Fault);								/**< fault interrupt callback */
	void (*pOverflowCallback)(FTU_HandleType *pHandle);         									/**< overflow interrupt callback */
	void (*pReloadPointCallback)(FTU_HandleType *pHandle);											/**< reload point interrupt callback */
} FTU_CommonType;

/**
 * @brief The configuration option for initializing FTU fault
 *
 */
typedef struct
{
	FTU_FaultModeType 		eFaultMode;               	/**< fault control mode */
	uint8_t 				u8FilterValue;				/**< selects the filter value for the fault inputs */
	uint8_t					u8FaultChannelEnable;		/**< fault control for channel */
#ifdef FTU_FAULT_DIS_DELAY_FEATURE
	uint8_t 				u8FaultDisableDelay0;		/**< Fault Disable Channel Output Delay Value 0 (timer ticks) */
	uint8_t 				u8FaultDisableDelay1;		/**< Fault Disable Channel Output Delay Value 1 (timer ticks) */
#endif
} FTU_FaultInitType;

/**
 * @brief The configuration option for enabling a FTU fault
 *
 */
typedef struct
{
	uint8_t 				u8FaultIndex;				/**< fault index */
	FTU_FaultPolActiveType 	eFaultPol;					/**< the fault input active polarity */
	bool					bFaultFilterEnable;			/**< whether to enable fault input glitch filter*/
} FTU_FaultControlType;

/**
 * @brief The configuration option for a input capture channel
 *
 */
typedef struct
{
	uint8_t u8Channel;								/**< selected FTU channel */
	FTU_InputCapturePinModeType eInputMode;        	/**< input capture mode */
	uint8_t	u8FilterValue;							/**< selects the filter value for the channel input */
} FTU_InputChannelType;

/**
 * @brief The configuration option for the quadrature decoder mode
 *
 */
typedef struct
{
	FTU_QuadratureModeType 			eQuadMode;			/**< selects the encoding mode used in the Quadrature Decoder mode */
	uint8_t 						u8PhaFilterVal;		/**< The filter value for the phase A input */
	uint8_t 						u8PhbFilterVal;		/**< The filter value for the phase B input */
	bool 							bPhaInverted;		/**< whether to inverted polarity of phase A input */
	bool 							bPhbInverted;		/**< whether to inverted polarity of phase B input */
	uint16_t						u16TopValue;		/**< the top value of counting */
	uint16_t						u16BottomValue;		/**< the bottom value of counting */
} FTU_QuadratureInitType;

/**
 * @brief Initialize FTU basic configuration
 *
 * @param pFtuHandle FTU processing handle
 * @param pCommonStruct the basic configurations of the FTU instance
 */
void FTU_CommonInit(FTU_HandleType *pFtuHandle, const FTU_CommonType *const pCommonStruct);

/**
 * @brief Fills in the FTU configuration structure with the default settings.
 *
 * @param pCommonStruct Pointer to the user configuration structure
 */
void FTU_GetDefaultInitCfg(FTU_CommonType *pCommonStruct);

/**
 * @brief Configure FTU to counter mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pCounterStruct the configurations of the counter mode
 * @note This function will stop timer
 */
void FTU_CounterModeInit(FTU_HandleType *pFtuHandle,
                         const FTU_CounterModeType *const pCounterStruct);


/**
 * @brief Configure FTU to output compare mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pOCConfig the configurations of the output compare mode
 * @note This function will stop timer
 */
void FTU_OutputCompareModeInit(FTU_HandleType *pFtuHandle,
                               const FTU_OutputCompareModeType *const pOCConfig);
/**
 * @brief Update the behavior of Output compare channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pOCConfig the configurations of the output compare mode
 */
void FTU_OutputCompareUpdate(FTU_HandleType *pFtuHandle,
                             const FTU_OutputCompareModeType *const pOCConfig);
/**
 * @brief Set the value of the FTU Channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Channel FTU Channel
 *
 * @return the value of the FTU Channel
 */
uint32_t FTU_GetChannelValue(FTU_HandleType *pFtuHandle, uint32_t u32Channel);
/**
 * @brief Get the value of the FTU counter
 *
 * @param pFtuHandle FTU processing handle
 * @return the counter of the FTU
 */
uint32_t FTU_GetCounter(FTU_HandleType *pFtuHandle);
/**
 * @brief Set the value of the FTU Channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Channel FTU Channel
 * @param u32Value the value to set
 */
void FTU_SetChannelValue(FTU_HandleType *pFtuHandle, uint32_t u32Channel, uint32_t u32Value);

/**
 * @brief Configure FTU to PWM mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pPwmModeStruct the configurations of the PWM mode
 * @note This function will stop timer
 */
void FTU_PwmModeInit(FTU_HandleType *pFtuHandle, const FTU_PwmModeType *const pPwmModeStruct);

/**
 * @brief Update the duty cycle of the FTU Channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pConfig The configuration option for update PWM Duty
 */
void FTU_PwmUpdateDuty(FTU_HandleType *pFtuHandle, FTU_PwmDutyUpdateType *pConfig);

void FTU_PwmUpdateDuty_modify(FTU_HandleType *pFtuHandle, FTU_PwmDutyUpdateType *pConfig);
/**
 * @brief Update the Period cycle of the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Period period of the PWM mode
 * @param bUpdate Update/Disupdate pwm
 */
void FTU_PwmUpdatePeriod(FTU_HandleType *pFtuHandle, uint32_t u32Period, bool bUpdate);

/**
 * @brief Synchronous update cycle and period of the FTU instance
 * @param pFtuHandle FTU processing handle
 */
void FTU_PwmSyncUpdate(FTU_HandleType *pFtuHandle);

/**
 * @brief Enable FTU interrupt
 *
 * @param pFtuHandle FTU processing handle
 * @param u32InterruptMask interrupt enable mask
 */
void FTU_EnableInterrupt(FTU_HandleType *pFtuHandle, uint32_t u32InterruptMask);

/**
 * @brief Disable FTU interrupt
 *
 * @param pFtuHandle FTU processing handle
 * @param u32InterruptMask interrupt disable mask
 */
void FTU_DisableInterrupt(FTU_HandleType *pFtuHandle, uint32_t u32InterruptMask);
/**
 * @brief Start the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 */
void FTU_StartTimer(FTU_HandleType *pFtuHandle);

#ifdef FTU_GTB_ADVANCED_CTRL
/**
 * @brief Stop the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 */
void FTU_StopGlobalTimeBase(uint32_t u32InstanceMask);
/**
 * @brief Start the FTU global time base
 *
 * @param u32InstanceMask The selected FTU, each bit represents an instance
 * @param u32StartMask Start time, refer to FTU_GlobalTimeBaseStartType
 */
void FTU_StartGlobalTimeBase(uint32_t u32InstanceMask, uint32_t u32StartMask);
#else
/**
 * @brief Stop the FTU global time base
 *
 */
#if defined(FTU_GTB_CTRL_IN_SMISC)
#define FTU_StopGlobalTimeBase		SMISC_HWA_EnabeFtuGTB
#endif
/**
 * @brief Start the FTU global time base
 *
 */
#if defined(FTU_GTB_CTRL_IN_SMISC)
#define FTU_StartGlobalTimeBase		SMISC_HWA_DisabeFtuGTB
#endif
#endif



/**
 * @brief De-initialize the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 */
void FTU_DeInit(FTU_HandleType *pFtuHandle);

/**
 * @brief initialize fault input of the selected Ftu instance
 *
 * @param pFtuHandle FTU processing handle
 * @param pFaultInit the fault configurations of the FTU instance
 */
void FTU_FaultInit(FTU_HandleType *pFtuHandle, const FTU_FaultInitType *const pFaultInit);

/**
 * @brief Stop the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 */
void FTU_StopTimer(FTU_HandleType *pFtuHandle);

/**
 * @brief Enable a fault input
 *
 * @param pFtuHandle FTU processing handle
 * @param pFaultCtrl configurations of the fault input
 */
void FTU_FaultEnable(FTU_HandleType *pFtuHandle, const FTU_FaultControlType *const pFaultCtrl);
#ifdef FTU_FAULT_DIS_DELAY_FEATURE
/**
 * @brief Select fault disable channel output delay value
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 * @param eDelaySelection Fault disable channel output delay value selection.
 */
void FTU_FaultSelectDelayValue(FTU_HandleType *pFtuHandle, uint8_t u8Channel, FTU_FaultDisableDelayType eDelaySelection);
#endif
#ifdef FTU_ICM_FEATURE
/**
 * @brief Get Edge number counter
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number.
 * @return uint8_t Edge number counter
 */
uint8_t FTU_GetEdgeNumberCount(FTU_HandleType *pFtuHandle, uint8_t u8Channel);
/**
 * @brief Initialize a Edge Number Measurement channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pEdgeNumMeasure measurement configuration.
 */
void FTU_EdgeNumberMeasureChannelInit(FTU_HandleType *pFtuHandle, FTU_EdgeNumberMeasureType *pEdgeNumMeasure);
/**
 * @brief Initialize a signal measure channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pMeasure measurement configuration.
 */
void FTU_SignalMeasureChannelInit(FTU_HandleType *pFtuHandle, FTU_SignalMeasureType *pMeasure);
/**
 * @brief Re-start measurement when in single mode
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 */
void FTU_SignalMeasureChannelSingle(FTU_HandleType *pFtuHandle, uint8_t u8Channel);
/**
 * @brief Get the measurement result of the channel
 *
 * @param eInstance the selected FTU instance
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 */
void FTU_GetSignaMeasureResult(const FTU_InstanceType eInstance, uint8_t u8Channel, FTU_SignalMeasureValueType *pResult);
#endif

/**
 * @brief Disable a fault input
 *
 * @param pFtuHandle FTU processing handle
 * @param u32FaultIndex index of the fault input
 */
void FTU_FaultDisable(FTU_HandleType *pFtuHandle, uint32_t u32FaultIndex);

/**
 * @brief Clear the fault flag of the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32FaultFlag flag to clear
 */
void FTU_ClearFault(FTU_HandleType *pFtuHandle, uint32_t u32FaultFlag);

/**
 * @brief Get the fault flag of the FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @return uint32_t the fault flag of the selected Ftu instance
 */
uint32_t FTU_GetFaultFlag(FTU_HandleType *pFtuHandle);

/**
 * @brief initialize a input capture channel of the selected Ftu instance
 *
  * @param pFtuHandle FTU processing handle
 * @param pInputChannel configurations of the input capture channel
 */
void FTU_InputCaptureChannelInit(FTU_HandleType *pFtuHandle,
                                 const FTU_InputChannelType *const pInputChannel);
/**
 * @brief Enable the output trigger of the selected FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32TriggerOutputMask the output trigger mask
 */
void FTU_EnableTriggerOutput(FTU_HandleType *pFtuHandle, uint32_t u32TriggerOutputMask);
/**
 * @brief Disable the output trigger of the selected FTU instance
 *
 * @param pFtuHandle FTU processing handle
 * @param u32TriggerOutputMask the output trigger mask
 */
void FTU_DisableTriggerOutput(FTU_HandleType *pFtuHandle, uint32_t u32TriggerOutputMask);
/**
 * @brief initialize the quadrature decoder mode
 *
 * @param pFtuHandle FTU processing handle
 * @param pQuadInit configurations of the quadrature decoder
 */
void FTU_QuadratureModeInit(FTU_HandleType *pFtuHandle,
                            const FTU_QuadratureInitType *const pQuadInit);
/**
 * @brief Enable ftu channel DMA
 *
 * @param pFtuHandle FTU processing handle
 * @param u32Channel The FTU channel .
 */
void FTU_EnableChannelDma(FTU_HandleType *pFtuHandle, uint32_t u32Channel);
#ifdef FTU_ICM_FEATURE
/**
 * @brief Get the expect edge number result of the channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 */
void FTU_GetExpectEdgeNumberResult(FTU_HandleType *pFtuHandle, uint8_t u8Channel, FTU_ExpectEdgeNumberResultType *pResult);
/**
 * @brief Initialize a Expect Edge Number Measurement channel
 *
 * @param pFtuHandle FTU processing handle
 * @param pExpectEdgeNumMeasure measurement configuration.
 */
void FTU_ExpectEdgeNumberMeasureChannelInit(FTU_HandleType *pFtuHandle, FTU_ExpectEdgeNumberMeasureType *pExpectEdgeNumMeasure);
/**
 * @brief Get the measurement result of the channel
 *
 * @param pFtuHandle FTU processing handle
 * @param u8Channel FTU channel number, range is 0-7.
 * @param pResult point to the result buffer.
 */
void FTU_GetSignalMeasureResult(FTU_HandleType *pFtuHandle, uint8_t u8Channel, FTU_SignalMeasureValueType *pResult);
#endif
/**
 * @brief Interrupt IRQ handle of FTU instance
 *
  * @param pFtuHandle FTU processing handle
 */
void FTUn_IRQHandler(FTU_HandleType *pFtuHandle);
/** @}*/ /* module_driver_ftu */
#if defined(__cplusplus)
}
#endif

#endif

#endif
