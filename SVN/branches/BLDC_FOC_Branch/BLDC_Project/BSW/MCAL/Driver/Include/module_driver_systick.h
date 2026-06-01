/**
 * @file module_driver_systick.h
 * @author Flagchip
 * @brief SYSTICK driver type definition and API
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip113   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_SYSTICK_H_
#define _DRIVER_MODULE_DRIVER_SYSTICK_H_
#include "device_header.h"

/**
 * @addtogroup module_driver_systick
 * @{
 */

/**
 * @brief Initialization service identifier.
 */
#define SYSTICK_INIT_ID                  0x00

/**
 * @brief Enable service identifier.
 */
#define SYSTICK_ENABLE_ID                0x01

/**
 * @brief Disable service identifier.
 */
#define SYSTICK_DISABLE_ID               0x02

/**
 * @brief Get count value service identifier.
 */
#define SYSTICK_GETCNTVALUE_ID           0x03


/**
 * @brief Error code indicating a null pointer parameter.
 */
#define SYSTICK_E_PARAM_NULLPTR          0x01


/**
 * @struct systickType
 * @brief Configuration structure for the SysTick timer.
 *
 * This structure defines the configuration parameters for initializing the SysTick timer.
 *
 * @var systickType::bUseProcessorclock
 * @brief Flag indicating whether to use the processor clock.
 *
 * @var systickType::bTickInt
 * @brief Flag to enable or disable the SysTick interrupt.
 *
 * @var systickType::u32LoadValue
 * @brief Reload value for the SysTick timer's counter.
 */
typedef struct
{
    bool bUseProcessorclock; /**< Use processor clock flag. */
    bool bTickInt;           /**< SysTick interrupt enable flag. */
    uint32_t u32LoadValue;   /**< Counter reload value. */
} systickType;


/**
 * @brief Initializes the SysTick timer.
 *
 * This function initializes the SysTick timer with the given configuration.
 *
 * @param pTickCfg Pointer to the configuration for the SysTick timer.
 */
void SYSTICK_Init(systickType *pTickCfg);

/**
 * @brief Enables the SysTick timer.
 *
 * This function enables the SysTick timer.
 */
void SysTick_Enable(void);

/**
 * @brief Disables the SysTick timer.
 *
 * This function disables the SysTick timer.
 */
void SysTick_Disable(void);

/**
 * @brief Returns the current count value of the SysTick timer.
 *
 * This function returns the current count value of the SysTick timer.
 *
 * @return The current count value.
 */
uint32_t SysTick_GetCntValue(void);

/** @}*/

#endif 


