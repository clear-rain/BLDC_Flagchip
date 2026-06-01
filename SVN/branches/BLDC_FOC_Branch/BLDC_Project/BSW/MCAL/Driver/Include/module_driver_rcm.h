/**
 * @file module_driver_rcm.h
 * @author Flagchip032
 * @brief RCM driver type definition and API
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
#ifndef _DRIVER_MODULE_DRIVER_RCM_H_
#define _DRIVER_MODULE_DRIVER_RCM_H_

#include "HwA_rcm.h"

#if RCM_INSTANCE_COUNT > 0U
/**
 * @addtogroup module_driver_rcm
 * @{
 */

/**
 * @name  RCM API Service IDs
 *
 * @{
 */
#define RCM_INIT_ID              0x00U
/** @}*/

/**
 * @name  RCM Dev Error Code
 * @brief Error Code of calling RCM apis
 *
 * @{
 */
#define RCM_E_PARAM_DELAY_TIME  		0x01U
#define RCM_E_PARAM_POINTER   			0x02U
/** @}*/


/** @brief Rcm instance type. */ 
typedef enum
{
	RCM_INSTANCE_0 = 0U, /**< RCM instance 0 */
	RCM_INSTANCE_ERR     /**< RCM instance error */
} RCM_InstanceType;


/** @brief Rcm return type. */
typedef enum
{
    RCM_STATUS_SUCCESS = 0U,        /**< RCM status success */
    RCM_STATUS_PARAM_INVALID = 1U,  /**< RCM status param invalid */
    RCM_STATUS_CLOCK_INVALID = 2U   /**< RCM status clock invalid */
} RCM_StatusType;

/** @brief Rcm reset pin filter clock type. */
typedef enum
{
    RCM_RESET_FILTER_BUS_CLOCK = 0U,           /**< Reset Pin Filter Bus Clock */
#if	RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K  
    RCM_RESET_FILTER_AON32K_CLOCK = 1U        /**< Reset Pin Filter AON32K Clock */
#endif /* end for RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K */
} RCM_FilterClkSrc;

/**
 * @brief The structure of the SCG processing handle
 *
 */
typedef struct _RCM_HandleType
{
	void (*pRcmResetInterruptNotify)(struct _RCM_HandleType *pHandle, uint32_t u32ResetReson);	/**< Reset interrupt callback */
} RCM_HandleType;

/** @brief Rcm configure type */
typedef struct
{
    boolean bResetfiltAonLp;            /**< Reset Pin Filter using AON32K Clock in Low Power Mode */
	uint8_t u8BusClockFilterWidth;      /**< Reset Pin Filter Bus Clock Width Configuration */
    RCM_FilterClkSrc  eFliterClkSrc;    /**< Reset Pin Filter Clock source */
    RCM_ResetDelayType eDelay;			/**< reset delay after interrupt assert */
	uint32_t u32InterruptMask;			/**< interrupt enable mask */
    void (*pRcmResetInterruptNotify)(RCM_HandleType *pHandle, uint32_t u32ResetReson);	/**< Reset interrupt callback */
} RCM_ConfigType;


/**
 * @brief This api can get RCM register that indicate the source of the most recent reset.
 *
 * @return RCM->SRS register, bit 0-13 corresponding to RCM_ResetEventType 0-13, refer to reference manual for details.
 * @note Multiple flags can be set if multiple reset events occur at the same time
 */
uint32_t RCM_GetLastResetFLag(void);

/**
 * @brief This api can get RCM register that indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @return RCM->SSRS register, bit 0-13 corresponding to RCM_ResetEventType 0-13, refer to reference manual for details.
 */
uint32_t RCM_GetAllResetFlag(void);

/**
 * @brief This api can clear reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Enumeration of reset event flag
 */
void RCM_ClearResetFlagAfterPOR(const RCM_ResetEventType eReset);

/**
 * @brief This api can clear all reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
void RCM_ClearAllResetFlagAfterPOR(void);

/**
 * @brief Enable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param u8BusClockFilterWidth Bus clock filter width
 * @param bLpClkEn select AON clock at low power mode
 * @return RCM return type
 * @note If use AON32K clock, the filter width less than 3 AON32K clock.
 */
RCM_StatusType RCM_EnableResetFilter(RCM_FilterClkSrc eClk, uint8_t u8BusClockFilterWidth, bool bLpClkEn);

/**
 * @brief Disable reset pin filter
 *
 * @param eClk Reset pin filter clock source
 * @param bLpClkEn select AON clock at low power mode
 * @return RCM return type
 */
RCM_StatusType RCM_DisableResetFilter(RCM_FilterClkSrc eClk, bool bLpClkEn);

/**
 * @brief Generate software reset through cotex-m register
 *
 */
void RCM_GenerateSwReset(void);

/**
 * @brief RCM interrupt process function
 *
 */
void RCM_UserIRQHandler(RCM_HandleType* pRcmHandle);

/**
 * @brief RCM initialize function
 *
 * @param pRcmHandle rcm handle
 * @param pInitCfg  Initial pointer
 */
void RCM_Init(RCM_HandleType* pRcmHandle, RCM_ConfigType *pInitCfg);

/**
 * @brief RCM Deinitialize function
 *
 * @param pRcmHandle Rcm handle
 *
 */
void RCM_DeInit(RCM_HandleType* pRcmHandle);

/** @}*/ /* module_driver_rcm */

#endif

#endif
