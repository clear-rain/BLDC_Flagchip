/**
 * @file module_driver_gpio.h
 * @author Flagchip032
 * @brief GPIO driver type definition and API
 * @version 2.0.0
 * @date 2024-04-19
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
#ifndef _DRIVER_MODULE_DRIVER_GPIO_H_
#define _DRIVER_MODULE_DRIVER_GPIO_H_

#include "HwA_gpio.h"

#if GPIO_INSTANCE_COUNT > 0U

#include <stddef.h>

/**
 * @addtogroup module_driver_gpio
 * @{
 */
/********* global define ************/
/** @brief Gpio max pins */
#define GPIO_MAX_PORT_PINS   32

/**
 * @name  PORT pin id
 *
 * @{
 */
#define GPIO_PIN_0        ((uint32_t)0x00000001)    /**< GPIO Pin 0 select */
#define GPIO_PIN_1        ((uint32_t)0x00000002)    /**< GPIO Pin 1 select */
#define GPIO_PIN_2        ((uint32_t)0x00000004)    /**< GPIO Pin 2 select */
#define GPIO_PIN_3        ((uint32_t)0x00000008)    /**< GPIO Pin 3 select */
#define GPIO_PIN_4        ((uint32_t)0x00000010)    /**< GPIO Pin 4 select */
#define GPIO_PIN_5        ((uint32_t)0x00000020)    /**< GPIO Pin 5 select */
#define GPIO_PIN_6        ((uint32_t)0x00000040)    /**< GPIO Pin 6 select */
#define GPIO_PIN_7        ((uint32_t)0x00000080)    /**< GPIO Pin 7 select */
#define GPIO_PIN_8        ((uint32_t)0x00000100)    /**< GPIO Pin 8 select */
#define GPIO_PIN_9        ((uint32_t)0x00000200)    /**< GPIO Pin 9 select */
#define GPIO_PIN_10       ((uint32_t)0x00000400)    /**< GPIO Pin 10 select */
#define GPIO_PIN_11       ((uint32_t)0x00000800)    /**< GPIO Pin 11 select */
#define GPIO_PIN_12       ((uint32_t)0x00001000)    /**< GPIO Pin 12 select */
#define GPIO_PIN_13       ((uint32_t)0x00002000)    /**< GPIO Pin 13 select */
#define GPIO_PIN_14       ((uint32_t)0x00004000)    /**< GPIO Pin 14 select */
#define GPIO_PIN_15       ((uint32_t)0x00008000)    /**< GPIO Pin 15 select */
#define GPIO_PIN_16       ((uint32_t)0x00010000)    /**< GPIO Pin 16 select */
#define GPIO_PIN_17       ((uint32_t)0x00020000)    /**< GPIO Pin 17 select */
#define GPIO_PIN_18       ((uint32_t)0x00040000)    /**< GPIO Pin 18 select */
#define GPIO_PIN_19       ((uint32_t)0x00080000)    /**< GPIO Pin 19 select */
#define GPIO_PIN_20       ((uint32_t)0x00100000)    /**< GPIO Pin 20 select */
#define GPIO_PIN_21       ((uint32_t)0x00200000)    /**< GPIO Pin 21 select */
#define GPIO_PIN_22       ((uint32_t)0x00400000)    /**< GPIO Pin 22 select */
#define GPIO_PIN_23       ((uint32_t)0x00800000)    /**< GPIO Pin 23 select */
#define GPIO_PIN_24       ((uint32_t)0x01000000)    /**< GPIO Pin 24 select */
#define GPIO_PIN_25       ((uint32_t)0x02000000)    /**< GPIO Pin 25 select */
#define GPIO_PIN_26       ((uint32_t)0x04000000)    /**< GPIO Pin 26 select */
#define GPIO_PIN_27       ((uint32_t)0x08000000)    /**< GPIO Pin 27 select */
#define GPIO_PIN_28       ((uint32_t)0x10000000)    /**< GPIO Pin 28 select */
#define GPIO_PIN_29       ((uint32_t)0x20000000)    /**< GPIO Pin 29 select */
#define GPIO_PIN_30       ((uint32_t)0x40000000)    /**< GPIO Pin 30 select */
#define GPIO_PIN_31       ((uint32_t)0x80000000)    /**< GPIO Pin 31 select */
/** @}*/

/**
 * @name  GPIO API Service IDs
 *
 * @{
 */
#define GPIO_Toggle_ID          0U
#define GPIO_ReadPins_ID        1U
#define GPIO_WritePins_ID       2U
#define GPIO_SetPinsDir_ID      3U

/** @}*/

/**
 * @name  GPIO Dev Error Code
 * @brief Error Code of calling GPIO apis
 *
 * @{
 */
#define GPIO_E_PARAM_INSTANCE           0x01U
#define GPIO_E_PARAM_LEVEL              0x02U
#define GPIO_E_PARAM_PIN                0x03U
#define GPIO_E_PARAM_DIRECTION          0x04U
/** @}*/

/********* global typedef ************/
#if GPIO_INSTANCE_COUNT < 6U
/** @brief Port instance number */
typedef enum
{
    GPIO_A = 0U,
    GPIO_B,
    GPIO_C,
    GPIO_D,
    GPIO_E
} GPIO_InstanceType;
#else
/** @brief Port instance number */
typedef enum
{
    GPIO_A = 0U,
    GPIO_B,
    GPIO_C,
    GPIO_D,
    GPIO_E,
    GPIO_F,
    GPIO_G,
    GPIO_H,
    GPIO_I
} GPIO_InstanceType;
#endif

/** @brief Gpio level */
typedef enum
{
    GPIO_LOW = 0U,
    GPIO_HIGH
} Gpio_LevelType;


/** @brief Gpio Direction */
typedef enum
{
    GPIO_IN = 0U,
    GPIO_OUT
} Gpio_Direction;

/**
 * @brief Toggle gpio api
 *
 * @param eGpio GPIO Instance
 * @param u32Pins The bit of u8Pins indicate the pin number of this Port.
 */
void GPIO_Toggle(const GPIO_InstanceType eGpio, const uint32_t u32Pins);

/**
 * @brief Read level of input port pins.
 *
 * @param eGpio GPIO Instance
 * @param u32Pins The bit of u8Pins indicate the pin number of this Port.
 * @return Pins level
 */
uint32_t GPIO_ReadPins(const GPIO_InstanceType eGpio, const uint32_t u32Pins);

/**
 * @brief Write gpio level to u8Pins.
 *
 * @param eGpio GPIO Instance
 * @param u32Pins The bit of u8Pins indicate the pin number of this Port.
 * @param eOutput Output level enumeration
 */
void GPIO_WritePins(const GPIO_InstanceType eGpio, const uint32_t u32Pins,
                    const Gpio_LevelType eOutput);

/**
 * @brief Set Pins Direction.
 *
 * @param eGpio GPIO Instance
 * @param u32Pins The bit of u8Pins indicate the pin number of this Port.
 * @param ePindir Pin direction enumeration
 */
void GPIO_SetPinsDir(const GPIO_InstanceType eGpio, const uint32_t u32Pins, const Gpio_Direction ePindir);

/** @}*/ /* module_driver_gpio */

#endif

#endif
