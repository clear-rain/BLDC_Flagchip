/**
 * @file HwA_gpio.h
 * @author Flagchip032
 * @brief GPIO hardware access layer
 * @version 2.0.0
 * @date 2024-03-22
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

#ifndef _HWA_GPIO_H_
#define _HWA_GPIO_H_

#include "device_header.h"

#if GPIO_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_gpio HwA_gpio
 * @ingroup module_driver_gpio
 * @{
 */

/**
 * @brief Set port data output, port output can set 1 or 0
 *
 * @param pGpio Gpio instance
 * @param u32Pins Pin numbers
 */
LOCAL_INLINE void GPIO_HWA_SetPortDataOutput(GPIO_Type *pGpio, uint32_t u32Pins)
{
    pGpio->PDOR = u32Pins;
}

/**
 * @brief Set port output to 1
 *
 * @param pGpio Gpio instance
 * @param u32Pins Pin numbers
 */
LOCAL_INLINE void GPIO_HWA_SetPortOutput(GPIO_Type *pGpio, uint32_t u32Pins)
{
    pGpio->PSOR = u32Pins;
}

/**
 * @brief Set port output to 0
 *
 * @param pGpio Gpio instance
 * @param u32Pins Pin numbers
 */
LOCAL_INLINE void GPIO_HWA_ClearPortOutput(GPIO_Type *pGpio, uint32_t u32Pins)
{
    pGpio->PCOR = u32Pins;
}

/**
 * @brief Toggle port output
 *
 * @param pGpio Gpio instance
 * @param u32Pins Pin numbers
 */
LOCAL_INLINE void GPIO_HWA_TogglePort(GPIO_Type *pGpio, uint32_t u32Pins)
{
    pGpio->PTOR = u32Pins;
}

/**
 * @brief Set port direction Input
 *
 * @param pGpio Gpio instance
 * @param u32Pins Pin numbers
 */
LOCAL_INLINE void GPIO_HWA_SetPortDirectionInput(GPIO_Type *pGpio, uint32_t u32Pins)
{
    pGpio->PDDR &= (~u32Pins);
}

/**
 * @brief Set port direction output
 *
 * @param pGpio Gpio instance
 * @param u32Pins Pin numbers
 */
LOCAL_INLINE void GPIO_HWA_SetPortDirectionOutput(GPIO_Type *pGpio, uint32_t u32Pins)
{
    pGpio->PDDR |= u32Pins;
}

/**
 * @brief Read port data input, this register indicate data on pad.
 *
 * @param pGpio Gpio instance
 * @return PDIR register value
 */
LOCAL_INLINE uint32_t GPIO_HWA_ReadPortDataInput(GPIO_Type *pGpio)
{
    return pGpio->PDIR;
}

/**
 * @brief Set pin output to 1
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_SetPinOutput(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PSOR = (uint32_t)1 << u8Pin;
}

/**
 * @brief Set pin output to 0
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_ClearPinOutput(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PCOR = (uint32_t)1 << u8Pin;
}

/**
 * @brief Set pin direction
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_SetPinDirection(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PDDR |= (uint32_t)1 << u8Pin;
}

/**
 * @brief Clear pin direction
 *
 * @param pGpio Gpio instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void GPIO_HWA_ClearPinDirection(GPIO_Type *pGpio, uint8_t u8Pin)
{
    pGpio->PDDR &= ~((uint32_t)1 << u8Pin);
}

/** @}*/
#endif

#endif /* #ifndef _HWA_GPIO_H_ */
