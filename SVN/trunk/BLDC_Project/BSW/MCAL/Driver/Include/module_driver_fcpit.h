/**
 * @file module_driver_fcpit.h
 * @author Flagchip032
 * @brief FCPIT driver type definition and API
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
*   2.0.0       2024-04-20    QXW0076   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_FCPIT_H_
#define _DRIVER_MODULE_DRIVER_FCPIT_H_

#include "HwA_fcpit.h"

#if FCPIT_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_fcpit
 * @{
 */

/** 
 * @brief FCPIT instance enumeration definition
 * 
 */
typedef enum
{
    FCPIT_INSTANCE_0,   /**< The first instance of the FCPIT module */
    FCPIT_INSTANCE_MAX  /**< The maximum number of FCPIT module instances, used to indicate the end of the enumeration */
} FCPIT_InstanceType;

/**
 * @name  FCPIT API Service IDs
 *
 * @{
 */
#define FCPIT_COMMON_INIT_ID 							0U /**< Defines the common initialization identifier for FCPIT */

#define FCPIT_CHANNEL_INIT_ID 							1U /**< Defines the channel initialization identifier for FCPIT */

#define FCPIT_INIT_TRIGGER_ID 							2U /**< Defines the initialization trigger identifier for FCPIT */

#define FCPIT_DE_INIT_ID 								3U /**< Defines the de-initialization identifier for FCPIT */

#define FCPIT_INIT_INTERRUPT_ID 						4U /**< Defines the initialization interrupt identifier for FCPIT */

#define FCPIT_ENABLE_INTERRUPT_ID 						5U /**< Defines the enable interrupt identifier for FCPIT */

#define FCPIT_DISABLE_INTERRUPT_ID 						6U /**< Defines the disable interrupt identifier for FCPIT */

#define FCPIT_START_ID 									7U /**< Defines the start identifier for FCPIT */

#define FCPIT_STOP_ID 									8U /**< Defines the stop identifier for FCPIT */

#define FCPIT_UPDATEVALUE_ID 							9U /**< Defines the update value identifier for FCPIT */

#define FCPIT_UPDATEVALUE_IMMEDIATE_ID 					10U /**< Defines the immediate update value identifier for FCPIT */

#if FCPIT_SUPPORT_GET_CURRENT_VALUE == STD_ON
#define FCPIT_GET_CHANNELVALUE_ID 						11U /**< Defines the get channel value identifier for FCPIT, if supported */
#endif
/** @}*/

/**
 * @name  FCPIT Dev Error Code
 * @brief Error Code of calling FCPIT apis
 *
 * @{
 */
#define FCPIT_STATUS_FUNCTION_ERROR			0x0U /**< Indicates a function error */
#define FCPIT_E_PARAM_CHANNEL   			0x02U /**< Indicates an error in the channel parameter */
#define FCPIT_E_PARAM_POINTER   			0x03U /**< Indicates an error in the pointer parameter */
#define FCPIT_E_PARAM_COUNT					0x04U /**< Indicates an error in the count parameter */
#define FCPIT_E_PARAM_INVALID				0x05U /**< Indicates a generic invalid parameter error */
/** @}*/


/** 
 * @brief Fcpit trigger source 
 * 
 * */
typedef enum
{
    FCPIT_TRIGGER_INTERNAL_0 = 0, /**< Internal trigger source 0*/
    FCPIT_TRIGGER_INTERNAL_1,     /**<Internal trigger source 1*/
    FCPIT_TRIGGER_INTERNAL_2,     /**< Internal trigger source 2*/
    FCPIT_TRIGGER_INTERNAL_3,     /**<Internal trigger source 3*/
    FCPIT_TRIGGER_EXTERNAL,       /**< External trigger source*/
    FCPIT_NO_TRIGGER              /**< No trigger source selected*/
} FCPIT_TriggerSelectType;

/** 
 * @brief callback function type 
 * 
 * */
typedef void (*FCPIT_InterruptCallBackType)(void);


/** 
 * @brief Fcpit function trigger type
 * 
 * */
typedef struct
{
    FCPIT_ChannelType eFcpitChannel;            /**< Fcpit channel number */
    FCPIT_TriggerSelectType eTriggerSel;        /**< trigger source */
    bool bStartOnTrigger;                       /**< Fcpit timer start when triggered */
    bool bStopOnInterrupt;                      /**< Fcpit timer stop on interrupt */
    bool bReloadOnTrigger;                      /**< Fcpit timer reload when triggered */
} FCPIT_TriggerType;


/** 
 * @brief Fcpit common Init type
 * 
 * */
typedef struct
{
	bool bDebugEn;                              /**< whether to use debug mode ,if enable this mode, the counter will stop when debugging. */
	bool bLowPowerModeEn;                       /**< Configure the timer channels to continue running or stop when the device enters the LPM mode */
}FCPIT_CommonInitType;


/**
 * @brief The structure of the FCPIT processing handle
 *
 */
typedef struct _FCPIT_HandleType
{

	bool bDebugEn;                              /**< whether to use debug mode ,if enable this mode, the counter will stop when debugging. */
	bool bLowPowerModeEn;                       /**< Configure the timer channels to continue running or stop when the device enters the LPM mode */

	struct
	{
		FCPIT_TimerModeType eMode;                  /**< Fcpit counter mode */
		bool bChainModeEn;                          /**< whether to use chain mode, if use this mode, channel must not be the channel 0 */
		uint32_t u32TimerValue;                     /**< timer compare value, the range of value is related to the counter mode */
		bool bStartOnTrigger;                       /**< Fcpit timer start when triggered */
		bool bStopOnInterrupt;                      /**< Fcpit timer stop on interrupt */
		bool bReloadOnTrigger;                      /**< Fcpit timer reload when triggered */
		FCPIT_TriggerSelectType eTriggerSel;        /**< trigger source */

		bool bChannelIsrEn;                         /**< whether to use interrupt */
		void(*pChannelCallback)(struct _FCPIT_HandleType  *pHandle,uint32_t u32channel);
		bool bChannelStarted;
	}tChannelStatus[MAX_FCPIT_CHANNEL_NUM];

}FCPIT_HandleType;

/** @brief Fcpit interrupt structure */
typedef struct
{
    FCPIT_ChannelType eFcpitChannel;            /**< Fcpit channel number */
    bool bChannelIsrEn;                         /**< whether to use interrupt */
    void(*pChannelCallback)(struct _FCPIT_HandleType  *pHandle,uint32_t u32channel);     /**< interrupt notification function */
} FCPIT_IntType;

/** @brief Fcpit initialization type */
typedef struct
{
    FCPIT_ChannelType eFcpitChannel;            /**< Fcpit channel number */
    FCPIT_TimerModeType eMode;                  /**< Fcpit counter mode */
    bool bChainModeEn;                          /**< whether to use chain mode, if use this mode, channel must not be the channel 0 */
    uint32_t u32TimerValue;                     /**< timer compare value, the range of value is related to the counter mode */
} FCPIT_ChannelInitType;

/* global functions */
/**
 * @brief Initialize Fcpit instance common feature.
 * @param pFcpitHandle Fcpit processing handle
 * @param pInitStruct Fcpit initialization structure
 */
void FCPIT_CommonInit(FCPIT_HandleType *pFcpitHandle,const FCPIT_CommonInitType * pInitStruct);


/* global functions */
/**
 * @brief Initialize Fcpit instance.
 * @param pFcpitHandle Fcpit processing handle
 * @param pInitStruct Fcpit initialization structure
 */
void FCPIT_ChannelInit(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelInitType * pInitStruct);

/**
 * @brief Initialize Fcpit trigger configuration
 * @param pFcpitHandle Fcpit processing handle
 * @param pTrgStruct Fcpit trigger structure
 */
void FCPIT_InitTrigger(FCPIT_HandleType *pFcpitHandle,const FCPIT_TriggerType * pTrgStruct);

/**
 * @brief De-initialize Fcpit instance.
 * @param pFcpitHandle Fcpit processing handle
 */
void FCPIT_Deinit(FCPIT_HandleType *pFcpitHandle);

/**
 * @brief Initialize Fcpit interrupt functionality
 * @param pFcpitHandle Fcpit processing handle
 * @param pIntStruct Fcpit interrupt structure
 * @note this function will stop timer
 */
void FCPIT_InitInterrupt(FCPIT_HandleType *pFcpitHandle,const FCPIT_IntType * pIntStruct);

/**
 * @brief Enable Fcpit interrupt
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_EnableInterrupt(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel);

/**
 * @brief Disable Fcpit interrupt
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_DisableInterrupt(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel);

/**
 * @brief Fcpit start timer
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_Start(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel);

/**
 * @brief Fcpit stop
 * @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 */
void FCPIT_Stop(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel);

/**
 * @brief Update Fcpit channel value
* @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 */
void FCPIT_UpdateChannelValue(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue);

/**
 * @brief Immediately update Fcpit channel value
* @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 */
void FCPIT_ImmediateUpdateChannelValue(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel, const uint32_t u32ChannelValue);


#if (FCPIT_SUPPORT_GET_CURRENT_VALUE == STD_ON)
/**
 * @brief Get the  Fcpit channel value
* @param pFcpitHandle Fcpit processing handle
 * @param eChannel Fcpit channel
 * @param u32ChannelValue in/Out value
 */
void FCPIT_GetChannelValue(FCPIT_HandleType *pFcpitHandle,const FCPIT_ChannelType eChannel, uint32_t *u32ChannelValue);
#endif
/**
 * @brief fcpit interrupt function.
* @param pFcpitHandle Fcpit processing handle
 */
void FCPITn_IRQHandler(FCPIT_HandleType *pFcpitHandle);

/** @}*/ /* module_driver_fcpit */

#endif

#endif
