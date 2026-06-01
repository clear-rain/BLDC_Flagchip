/**
 * @file module_driver_aontimer.h
 * @author Flagchip032
 * @brief AONTIMER driver type definition and API
 * @version 2.0.0
 * @date 2024-06-10
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_AONTIMER_H_
#define _DRIVER_MODULE_DRIVER_AONTIMER_H_

#include "HwA_aontimer.h"

#if AONTIMER_INSTANCE_COUNT > 0U

#include "module_driver_smisc.h"
#include <stddef.h>
/**
 * @addtogroup module_driver_aontimer
 * @{
 */

/**
 * @name  AONTIMER API Service IDs
 *
 * @{
 */
#define AONTIMER_INIT_ID                     0U
#define AONTIMER_DEINIT_ID                   1U
#define AONTIMER_START_ID                    2U
#define AONTIMER_STOP_ID                     3U
#define AONTIMER_UPDATE_COUNT_ID             4U
#define AONTIMER_INTE_PROC_ID                5U
/** @}*/

/**
 * @name  AONTIMER Dev Error Code
 * @brief Error Code of calling AONTIMER apis
 *
 * @{
 */
#define AONTIMER_E_PARAM_INSTANCE   		0x01U
#define AONTIMER_E_PARAM_CLOCK   			0x02U
#define AONTIMER_E_PARAM_POINTER   			0x03U
/** @}*/


/**
 * @brief The instance index of the FTU peripheral
 *
 */
typedef enum
{
	AONTIMER_INSTANCE_0 = 0U
} AONTIMER_InstanceType;

#if AONTIMER_DEBUG_MODE_SUPPORT
/** @brief Aontimer debug mode */
typedef enum
{
    AONTIMER_DBG_COUNTER_STOP = 0x00U,
    AONTIMER_DBG_COUNTER_RUNNING = 0x01U
} AONTIMER_DebugType;
#endif /* end for AONTIMER_DEBUG_MODE_SUPPORT */


/**
 * @brief Aontimer mode.
 *
 */
typedef enum
{
    AONTIMER_COUNTER_MODE = 0,          /**< In this mode ,the clock source is internal.*/
    AONTIMER_PULSE_MODE                 /**< In this mode ,the clock source is external(pin/trgsel).*/
} AONTIMER_ModeType;


/**
 * @brief The structure of the AONTIMER processing handle
 *
 */
typedef struct _AONTIMER_HandleType
{
	AONTIMER_InstanceType eInstance;		/**< AONTIMER instance*/
	char _aligned[3];
	struct
	{
		void (*pAontimerCallback)(struct _AONTIMER_HandleType *pHandle);		/**< fault interrupt callback */
	} tSettings;
} AONTIMER_HandleType;

/**
 *  @brief Aontimer Initialization struct type
 *
 */
typedef struct
{
    AONTIMER_ModeType eMode;                                    /**< enumeration of aontier mode */
    bool bBypassEn;                                             /**< Whether to use prescaler in counter mode or use glitch filter in pulse mode,
                                                                    if set input value is true ,then not use the prescaler or glitch filter.*/
    AONTIMER_PulseClkSrcType ePulseClkSrc;                      /**< clock source of pulse mode */
    AONTIMER_PulsePolarityType ePulsePol;                       /**< polarity of pulse mode */
    uint8_t u8PulseFilterWidth;                                 /**< the width of glitch filter in pulse mode , the range of the input value is :1~15,
                                                                    and the range of glitch filter is :2^1 ~ 2^15. */
    uint8_t u8Prescaler;                                        /**< the width of prescaler in counter mode, the range of the input value is :0~15,
                                                                    and the range of prescaler is :2^1 ~ 2^16. */
    uint16_t u16StartValue;                                     /**< start value of counter mode ,the range is : 0 ~ 65535 */
    void (*pAontimerCallback)(AONTIMER_HandleType *pHandle);    /**< the notification function of interrupt */
    bool bIntEn;                                                /**<Whether enable interrupt */
    AONTIMER_ClkSrcType eClkSrc;                                /**< clock source of counter mode */
    char _aligned0[2];

#if AONTIMER_DEBUG_MODE_SUPPORT
    AONTIMER_DebugType eDbgMode;                    /**< enumeration of aontier debug mode */
    char _aligned1[3];
#endif /* end for AONTIMER_DEBUG_MODE_SUPPORT */

} AONTIMER_InitType;


/* global function */
/**
 * @brief Initialize aontimer instance
 *
 * @param pAontimerHandle the Aontimer instance to use
 * @param pInitStruct Aontimer Initialize structure
 */
void AONTIMER_Init(AONTIMER_HandleType* pAontimerHandle, const AONTIMER_InitType *const pInitStruct);

/**
 * @brief De-initialize aontimer instance
 *
 * @param pAontimerHandle the Aontimer instance to use
 */
void AONTIMER_Deinit(AONTIMER_HandleType* pAontimerHandle);

/**
 * @brief Start Aontimer
 *
 * @param pAontimerHandle the Aontimer instance to use
 */
void AONTIMER_StartTimer(AONTIMER_HandleType* pAontimerHandle);

/**
 * @brief Stop Aontimer
 *
 * @param pAontimerHandle the Aontimer instance to use
 */
void AONTIMER_StopTimer(AONTIMER_HandleType* pAontimerHandle);

/**
 * @brief Update value of aontimer counter
 *
 * @param pAontimerHandle the Aontimer instance to use
 * @param u16StartValue input value, range : 0~65535
 */
void AONTIMER_UpdateCounterValue(AONTIMER_HandleType* pAontimerHandle, const uint16_t u16StartValue);

/**
 * @brief Aontimer common interrupt handle function
 *
 * @param pAontimerHandle the Aontimer instance to use
 */
void Aontimer_CommonProcessInterrupt(AONTIMER_HandleType* pAontimerHandle);


/** @}*/ /* module_driver_aontimer */

#endif

#endif
