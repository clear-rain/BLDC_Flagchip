/**
 * @file module_driver_tstmp.h
 * @author Flagchip074
 * @brief TSTMP driver type definition and API
 * @version 2.0.0
 * @date 2024-11-08
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
#ifndef _DRIVER_MODULE_DRIVER_TSTMP_H_
#define _DRIVER_MODULE_DRIVER_TSTMP_H_

#include "HwA_tstmp.h"

#if TSTMP_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif
/**
 * @addtogroup module_driver_tstmp
 * @{
 */

/** @brief TSTMP max mod number*/
#define MAX_MOD_NUMBER  4U

/** @brief TSTMP instance */
typedef enum
{
#if TSTMP_INSTANCE_COUNT > 1U
	TSTMP_INSTANCE_0,							/**< TSTMP Instance 0*/
#endif
#if (TSTMP_INSTANCE_COUNT >= 1u)
    TSTMP_INSTANCE_1,							/**< TSTMP Instance 1*/
#endif
    TSTMP_INSTANCE_MAX
} TSTMP_InstanceType;

/**
 * @name  TSTMP API Service IDs
 *
 * @{
 */
#define TSTMP_INIT_ID 							0U    /**< Init TSTMP instance */
#define TSTMP_DEINIT_ID 						1U    /**< DeInit TSTMP instance */
#define TSTMP_SET_COUNTER_MODE_ID 				2U	  /**< Set TSTMP counter mode */
#define TSTMP_START_COUNTER_ID 					3U    /**< Start TSTMP counter  */
#define TSTMP_STOP_COUNTER_ID 					4U    /**< Stop TSTMP counter  */
#define TSTMP_INIT_INTERRUPT_ID 				5U    /**< Init TSTMP Interrupt  */
#define TSTMP_EN_INTERRUPT_ID 					6U    /**< Enable TSTMP Interrupt  */
#define TSTMP_DIS_INTERRUPT_ID 					7U    /**< Disable TSTMP Interrupt  */
#define TSTMP_GET_TSTMP_VALUE_ID 				8U    /**< Get TSTMP value  */
#define TSTMP_UPDATE_MOD_ID 					9U    /**< Update TSTMP Mod  */
/** @}*/

/**
 * @name  TSTMP Dev Error Code
 * @brief Error Code of calling TSTMP apis
 *
 * @{
 */
#define TSTMP_E_PARAM_INSTANCE   			0x01U       /**< Invalid instance */
#define TSTMP_E_PARAM_CHANNEL   			0x02U       /**< Invalid channel */
#define TSTMP_E_PARAM_POINTER   			0x03U       /**< Invalid pointer */
#define TSTMP_E_PARAM_COUNT					0x04U       /**< Invalid counter */
#define TSTMP_E_PARAM_INVALID				0x05U       /**< Invalid paramter */
/** @}*/


/**
 * @brief The structure of the Tstmp processing handle
 *
 */
typedef struct _TSTMP_HandleType
{
	TSTMP_InstanceType eInstance; /**< TSTMP instance*/
	struct
	{
		uint32_t u32ModulateValue[MAX_MOD_NUMBER];                         /**< modulate  value */

#if (TSTMP_SUPPORT_MODULATE_SUPPOT == STD_ON)
		TSTMP_ModeCounterRunningMode gModRunningMode[MAX_MOD_NUMBER];		 /**< Channel Running  value */
#endif
		bool bModulateIntEn[MAX_MOD_NUMBER];															 /**< Channel interrupt status */	
		void(*pChannelCallback[MAX_MOD_NUMBER])(struct _TSTMP_HandleType  *pHandle,uint32_t u32channel);  /**< Channel interrupt callback */
	}tStatus;
}TSTMP_HandleType;


/** @brief TSTMP interrupt type */
typedef struct
{
    bool bModulateIntEn[MAX_MOD_NUMBER];                             					  				/**< whether use the modulate n interrupt */
	void(*pChannelCallback[MAX_MOD_NUMBER])(TSTMP_HandleType *pHandle,uint32_t u32channel);    /**< modulate n interrupt function pointer */
} TSTMP_IntType;


/** @brief TSTMP initialization type */
typedef struct
{
	uint32_t u32Modulate0Value;                         /**< modulate 0 value */
    uint32_t u32Modulate1Value;                         /**< modulate 1 value */
    uint32_t u32Modulate2Value;                         /**< modulate 2 value */
    uint32_t u32Modulate3Value;                         /**< modulate 3 value */
} TSTMP_InitType;


/** @brief TSTMP update type */
typedef struct
{
	TSTMP_ModChannelType eMod;                       					/**< TSTMP modulate */
	uint32_t u32ModValue;                           					/**< TSTMP modulate value */
	void(*pChannelCallback)(TSTMP_HandleType *pHandle,uint32_t u32channel);      	/**< modulate n interrupt function pointer */
	bool bIntEn;                                    					/**< whether enable TSTMP modulate interrupt */
} TSTMP_UpdateType;


/* global functions */
/**
 * @brief Initialize TSTMP instance
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param pInitStruct TSTMP initialization structure
 * @note TSTMP will auto start the modulate when write MODn_SETVAL register
 *       TSTMP1 clock source is core clock
 */
void TSTMP_Init(TSTMP_HandleType *pTstmpHandle,const TSTMP_InitType *const pInitStruct);

/**
 * @brief De-initialize TSTMP instance
 * @param pTstmpHandle TSTMP processing handle
 */
void TSTMP_Deinit(TSTMP_HandleType *pTstmpHandle);

#if (TSTMP_SUPPORT_MODULATE_SUPPOT == STD_ON)
/**
 * @brief Set the Counting mode of modulate timer counter0,1,2,3
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 * @param eCounterMode Counting mode of counter0
 */
void TSTMP_SetCounterMode(TSTMP_HandleType *pTstmpHandle, const TSTMP_ModChannelType eMod,const TSTMP_ModeCounterRunningMode eCounterMode);

/**
 * @brief Start counter MOD(n) counting
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration

 */
void TSTMP_StartCounter(TSTMP_HandleType *pTstmpHandle,const TSTMP_ModChannelType eMod);

/**
 * @brief Stop counter MOD(n) counting
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 *
 */
void TSTMP_StopCounter(TSTMP_HandleType *pTstmpHandle,const TSTMP_ModChannelType eMod);
#endif

/**
 * @brief Initialize TSTMP interrupt functionality
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param pIntStruct TSTMP interrupt structure
 */
void TSTMP_InitInterrupt(TSTMP_HandleType *pTstmpHandle, const TSTMP_IntType *const pIntStruct);

/**
 * @brief Enable TSTMP interrupt function
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 */
void TSTMP_EnableInterrupt(TSTMP_HandleType *pTstmpHandle, const TSTMP_ModChannelType eMod);

/**
 * @brief Disable TSTMP interrupt function
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param eMod TSTMP modulate enumeration
 */
void TSTMP_DisableInterrupt(TSTMP_HandleType *pTstmpHandle, const TSTMP_ModChannelType eMod);

/**
 * @brief Get TSTMP count value
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param u64TstmpValue the timestamp value
 */
void TSTMP_GetTstmpValue(TSTMP_HandleType *pTstmpHandle, uint64_t *const u64TstmpValue);

/**
 * @brief Update Modulate configuration
 *
 * @param pTstmpHandle TSTMP processing handle
 * @param pUpdateStruct TSTMP update structure pointer
 */
void TSTMP_UpdateMod(TSTMP_HandleType *pTstmpHandle,
                                 const TSTMP_UpdateType *const pUpdateStruct);


#if (TSTMP_INSTANCE_COUNT == 1u || TSTMP_INSTANCE_COUNT == 2u)

/**
 * @brief TSTMP interrupt process function
 *
 * @param pTstmpHandle TSTMP processing handle
 */
void TSTMPn_IRQHandler(TSTMP_HandleType *pTstmpHandle);
#endif


/** @}*/ /* module_driver_tstmp */
#if defined(__cplusplus)
}
#endif

#endif

#endif
