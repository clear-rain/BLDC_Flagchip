/**
 * @file module_driver_intm.h
 * @author Flagchip100
 * @brief INTM driver type definition and API
 * @version 2.0.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_INTM_H_
#define _DRIVER_MODULE_DRIVER_INTM_H_

#include "HwA_intm.h"

#if INTM_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_intm
 * @{
 */

/**
 * @name  INTM API Service IDs
 *
 * @{
 */
#define INTM_INIT_ID                0U
#define INTM_ENABLE_ID              1U
#define INTM_START_INACTIVE_ID      2U
#define INTM_STOP_INACTIVE_ID       3U
#define INTM_SET_ACKNOWLEDGE_ID     4U
#define INTM_GET_COUNTER_ID         5U
#define INTM_CLEAR_INT_FLAG_ID      6U
#define INTM_GET_TIMEOUT_STAT_ID    7U
#define INTM_IRQ_PRCE_ID            8U
/** @}*/

/**
 * @name  INTM Dev Error Code
 * @brief Error Code of calling INTM apis
 *
 * @{
 */
#define INTM_E_PARAM_INSTANCE		   	0x01U
#define INTM_E_PARAM_POINTER		   	0x02U
#define INTM_E_PARAM_PARAM 		        0x03U
#define INTM_E_PARAM_NO_SUPPORT      	0x04U
/** @}*/

/**
 * @brief The INTM instance
 *
 */
typedef enum
{
    INTM_INSTANCE_0   = 0U,
    INTM_INSTANCE_MAX,
} INTM_InstanceType;

/**
 * @brief The INTM monitor
 *
 */
typedef enum
{
    INTM_IRQ_MONITOR_0   = 0U,
    INTM_IRQ_MONITOR_1,
    INTM_IRQ_MONITOR_MAX,
} INTM_IrqMonitorType;

/**
 * @brief The structure of the INTM handle
 *
 */
typedef struct _INTM_HandleType
{
	INTM_InstanceType eInstance;		/**< INTM instance*/
	char _aligned[3];
	struct
	{
		void (*pIntmIsrCallback[INTM_IRQ_MONITOR_MAX])(struct _INTM_HandleType *pHandle);						/**< INTM interrupt callback */
	} tSettings;
} INTM_HandleType;

typedef enum
{
    INTM_INTERRUPT_MODE_ACTIVE = 0x00U, /**< INTM is configured as active mode */
    INTM_INTERRUPT_MODE_INACTIVE        /**< INTM is configured as inactive mode */
} INTM_InterruptModeType;

/**
 * @brief INTM Channel ISR callback function prototype
 *
 */
typedef void (*INTM_ISRCallbackType)(INTM_HandleType *pHandle);

/**
 * @brief The structure of the INTM init
 *
 */
typedef struct
{
	INTM_IrqMonitorType    eIrqMonitorIndex;    /**< index of INTM channel*/
    INTM_InterruptModeType eMode;               /**< INTM active mode */
    bool                   bEnReset;            /**< Enable Reset */
    bool                   bEnInterrupt;        /**< Enable Interrupt */
    uint32_t               u32SrcDelayCnt;      /**< Enable Interrupt */
    uint16_t               u16IrqNumber;        /**< Monitored interrupt number */
    char aligned[2];
} INTM_InitType;

/**
 * @brief Init the INTM.
 * 
 * @param pIntmHandle INTM instance.
 * @param pInitCfg Init Configuration.
 */
void INTM_Init(INTM_HandleType* pIntmHandle, const INTM_InitType *const pInitCfg);

/**
 * @brief Enable INTM.
 *
 * @param pIntmHandle INTM instance.
 * @param bEnable Enable INTM.
 */
void INTM_enable(INTM_HandleType* pIntmHandle, const bool bEnable);

/**
 * @brief Start INTM inactive mode.
 * 
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 */
void INTM_StartInactiveMode(INTM_HandleType* pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief
 * 
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 */
void INTM_StopInactiveMode(INTM_HandleType* pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief Write the interrupt acknowledge.
 *
 * @param pIntmHandle INTM instance.
 * @param u16IrqNumber Interrupt nunmber.
 */
void INTM_SetAcknowledge(INTM_HandleType* pIntmHandle, const uint16_t u16IrqNumber);

/**
 * @brief Return counter value.
 *
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return Counter value.
 */
uint32_t INTM_GetCounterValue(INTM_HandleType* pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief Clear the interrupt flag.
 *
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 */
void INTM_ClearIntFlag(INTM_HandleType* pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief Get the timeout flag. Return true if INTM_TMR value has exceeded the INTM_LATR value.
 *
 * @param pIntmHandle INTM instance.
 * @param eIrqMonitorIndex Monitor index.
 * @return Timeout flag.
 */
bool INTM_GetTimeoutStatus(INTM_HandleType* pIntmHandle, const INTM_IrqMonitorType eIrqMonitorIndex);

/**
 * @brief intm process interrupt function
 * 
 * @param pIntmHandle INTM instance.
 */
void INTM_IRQProcess(INTM_HandleType* pIntmHandle);

/** @}*/

#endif

#endif /* end of _DRIVER_MODULE_DRIVER_INTM_H_ */
