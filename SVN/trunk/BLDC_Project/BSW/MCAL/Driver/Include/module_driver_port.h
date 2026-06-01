/**
 * @file module_driver_port.h
 * @author Flagchip032
 * @brief PORT driver type definition and API
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
#ifndef _DRIVER_MODULE_DRIVER_PORT_H_
#define _DRIVER_MODULE_DRIVER_PORT_H_

#include "HwA_port.h"

#if PORT_INSTANCE_COUNT > 0U

#include "HwA_gpio.h"
#include <stddef.h>
/**
 * @addtogroup module_driver_port
 * @{
 */

/********* global define ************/
/**
 * @name  PORT pin id
 *
 * @{
 */
#define PORT_PIN_0        ((uint32_t)0x00000001)    /**< PORT Pin 0 select */
#define PORT_PIN_1        ((uint32_t)0x00000002)    /**< PORT Pin 1 select */
#define PORT_PIN_2        ((uint32_t)0x00000004)    /**< PORT Pin 2 select */
#define PORT_PIN_3        ((uint32_t)0x00000008)    /**< PORT Pin 3 select */
#define PORT_PIN_4        ((uint32_t)0x00000010)    /**< PORT Pin 4 select */
#define PORT_PIN_5        ((uint32_t)0x00000020)    /**< PORT Pin 5 select */
#define PORT_PIN_6        ((uint32_t)0x00000040)    /**< PORT Pin 6 select */
#define PORT_PIN_7        ((uint32_t)0x00000080)    /**< PORT Pin 7 select */
#define PORT_PIN_8        ((uint32_t)0x00000100)    /**< PORT Pin 8 select */
#define PORT_PIN_9        ((uint32_t)0x00000200)    /**< PORT Pin 9 select */
#define PORT_PIN_10       ((uint32_t)0x00000400)    /**< PORT Pin 10 select */
#define PORT_PIN_11       ((uint32_t)0x00000800)    /**< PORT Pin 11 select */
#define PORT_PIN_12       ((uint32_t)0x00001000)    /**< PORT Pin 12 select */
#define PORT_PIN_13       ((uint32_t)0x00002000)    /**< PORT Pin 13 select */
#define PORT_PIN_14       ((uint32_t)0x00004000)    /**< PORT Pin 14 select */
#define PORT_PIN_15       ((uint32_t)0x00008000)    /**< PORT Pin 15 select */
#define PORT_PIN_16       ((uint32_t)0x00010000)    /**< PORT Pin 16 select */
#define PORT_PIN_17       ((uint32_t)0x00020000)    /**< PORT Pin 17 select */
#define PORT_PIN_18       ((uint32_t)0x00040000)    /**< PORT Pin 18 select */
#define PORT_PIN_19       ((uint32_t)0x00080000)    /**< PORT Pin 19 select */
#define PORT_PIN_20       ((uint32_t)0x00100000)    /**< PORT Pin 20 select */
#define PORT_PIN_21       ((uint32_t)0x00200000)    /**< PORT Pin 21 select */
#define PORT_PIN_22       ((uint32_t)0x00400000)    /**< PORT Pin 22 select */
#define PORT_PIN_23       ((uint32_t)0x00800000)    /**< PORT Pin 23 select */
#define PORT_PIN_24       ((uint32_t)0x01000000)    /**< PORT Pin 24 select */
#define PORT_PIN_25       ((uint32_t)0x02000000)    /**< PORT Pin 25 select */
#define PORT_PIN_26       ((uint32_t)0x04000000)    /**< PORT Pin 26 select */
#define PORT_PIN_27       ((uint32_t)0x08000000)    /**< PORT Pin 27 select */
#define PORT_PIN_28       ((uint32_t)0x10000000)    /**< PORT Pin 28 select */
#define PORT_PIN_29       ((uint32_t)0x20000000)    /**< PORT Pin 29 select */
#define PORT_PIN_30       ((uint32_t)0x40000000)    /**< PORT Pin 30 select */
#define PORT_PIN_31       ((uint32_t)0x80000000)    /**< PORT Pin 31 select */
/** @}*/

/** @brief Port Alternate 0 Mode */
#define PORT_ALT0_FUNC_MODE             ((Port_PinModeType)0)
/** @brief Port GPIO Mode */
#define PORT_GPIO_MODE                  ((Port_PinModeType)1)
/** @brief Port Alternate 2 Mode */
#define PORT_ALT2_FUNC_MODE             ((Port_PinModeType)2)
/** @brief Port Alternate 3 Mode */
#define PORT_ALT3_FUNC_MODE             ((Port_PinModeType)3)
/** @brief Port Alternate 4 Mode */
#define PORT_ALT4_FUNC_MODE             ((Port_PinModeType)4)
/** @brief Port Alternate 5 Mode */
#define PORT_ALT5_FUNC_MODE             ((Port_PinModeType)5)
/** @brief Port Alternate 6 Mode */
#define PORT_ALT6_FUNC_MODE             ((Port_PinModeType)6)
/** @brief Port Alternate 7 Mode */
#define PORT_ALT7_FUNC_MODE             ((Port_PinModeType)7)


/**
 * @name  PORT API Service IDs
 *
 * @{
 */
#define PORT_InitPins_ID                         0U
#define PORT_Deinit_ID                           1U
#define PORT_SetPinMode_ID                       2U
#define PORT_SetInterruptCfg_ID                  3U
#define PORT_InitDigitalFilterPort_ID            4U
#define PORT_DeinitDigitalFilterPort_ID          5U
#define PORT_EnableDigitalFilterPin_ID           6U
#define PORT_DisableDigitalFilterPin_ID          7U
#define PORT_IRQHandler_ID                       8U

/** @}*/

/**
 * @name  PORT Dev Error Code
 * @brief Error Code of calling GPIO apis
 *
 * @{
 */
#define PORT_E_PARAM_INSTANCE           0x01U
#define PORT_E_PARAM_INPUT              0x02U
#define PORT_E_PARAM_PIN                0x03U
/** @}*/

/********* global typedef ************/
/** @brief Port PCR[IRQC] configuration */
typedef enum
{
    PORT_IRQ_DISABLE = 0U,
    PORT_IRQ_DMA_RISING = 1U,
    PORT_IRQ_DMA_FALLING = 2U,
    PORT_IRQ_DMA_BOTH_EDGE = 3U,
    PORT_IRQ_LOGIC_0 = 8U,
    PORT_IRQ_RISING = 9U,
    PORT_IRQ_FALLING = 10U,
    PORT_IRQ_BOTH_EDGE = 11U,
    PORT_IRQ_LOGIC_1 = 12U,
    PORT_IRQ_TOOGLED_WHEN_LOGIC_0 = 13U,
    PORT_IRQ_TOOGLED_WHEN_LOGIC_1 = 14U
} PORT_IrqcConfigurationType;


/** @brief Port pull status */
typedef enum
{
    PORT_PULL_DOWN = 0U,
    PORT_PULL_UP
} PORT_PullStatusType;

/** @brief Gpio direction */
typedef enum
{
    PORT_GPIO_OUT = 0U,
    PORT_GPIO_IN,
    PORT_GPIO_ZERO
} PORT_GpioDirType;

/** @brief Gpio initialization level */
typedef enum
{
    PORT_GPIO_LOW = 0U,
    PORT_GPIO_HIGH
} PORT_GpioLevelType;

/** @brief Port digital filter configuration structure */
typedef struct
{
    uint32_t u32PortPinsEn;                 /**< Port pin, 0~31 bit indicates the pin 0~31 */
    PORT_DigitalFilterClkSrcType eClkSrc;   /**< Port clock source */
    uint8_t u8FilterLength;                 /**< digital filter length, the range is :0~31 */
    uint8_t RESERVED_0[2];
} PORT_DigitalFilterType;

#if PORT_INSTANCE_COUNT < 6U
/** @brief Port instance number */
typedef enum
{
    PORT_A = 0U,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
} PORT_InstanceType;
#else
/** @brief Port instance number */
typedef enum
{
    PORT_A = 0U,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
	PORT_F,
	PORT_G,
	PORT_H,
	PORT_I
} PORT_InstanceType;
#endif
/**
 * @brief The structure of the PORT processing handle
 *
 */
typedef struct _PORT_HandleType
{
    PORT_InstanceType eInstance;        /**< PORT instance*/
    uint8_t RESERVED_0[3];
    struct
    {
        void (*PORT_PinInterruptCallBackType)(struct _PORT_HandleType *pHandle, uint32_t u32PIns);      /**< PORT user defined interrupt function*/
    } tSettings;
} PORT_HandleType;

/** @brief Port interrupt configuration structure */
typedef struct
{
    PORT_IrqcConfigurationType ePortIsrMode;            /**< Port interrupt mode */
    uint8_t RESERVED_0[3];
} PORT_InterruptType;

/** @brief Port initialization structure */
typedef struct
{
    uint32_t u32PortPins;                       /**< Port pin, 0~31 bit indicates the pin 0~31 */
    Port_PinMuxType uPortPinMux;                /**< Port pin mode */
    PORT_GpioDirType ePortGpioDir;              /**< Gpio direction */
    PORT_GpioLevelType ePortGpioLevel;          /**< Gpio level */
    bool bPullEn;                               /**< whether to pull the port pin */
    PORT_PullStatusType ePullSel;               /**< pull status, pull up or pull down */
    bool bDrvStrengthEn;                        /**< whether to enable pad drive strength, only hs PAD used */
    bool u8PassiveFilterEn;                     /**< whether to use passive filter, please refer to reference manual for details */
    uint8_t RESERVED_0[1];
    PORT_InterruptType tInterruptCfg;           /**< Port interrupt config */
} PORT_InitType;
/********* global API ************/
/**
 * @brief Initialize port pins
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param pInitStruct Initialization structure of port
 */
void PORT_InitPins(PORT_HandleType *pPortHandle, const PORT_InitType *const pInitStruct);

/**
 * @brief De-initialize the Port instance
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 */
void PORT_Deinit(PORT_HandleType *pPortHandle, const uint32_t u32Pins);

/**
 * @brief Set port pin mode
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @param uPinMux Port mux function.
 */
void PORT_SetPinMode(PORT_HandleType *pPortHandle, const uint32_t u32Pins, const Port_PinMuxType uPinMux);

/**
 * @brief set interrupt config of port
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @param ePortPinIrq The config of interrupt.
 */
void PORT_SetInterruptCfg(PORT_HandleType *pPortHandle, const uint32_t u32Pins, PORT_IrqcConfigurationType ePortPinIrq);

/**
 * @brief Initialize digital filter for Port instance
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param pDFStruct Digital filter initialization structure of port
 */
void PORT_InitDigitalFilterPort(PORT_HandleType *pPortHandle,
                                const PORT_DigitalFilterType * const pDFStruct);

/**
 * @brief De-initialize digital filter for Port instance
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 */
void PORT_DeinitDigitalFilterPort(PORT_HandleType *pPortHandle);

/**
 * @brief Enable the digital filter function for the specific pin.
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 */
void PORT_EnableDigitalFilterPin(PORT_HandleType *pPortHandle, const uint32_t u32Pins);

/**
 * @brief Disable the digital filter function for the specific pin.
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 */
void PORT_DisableDigitalFilterPin(PORT_HandleType *pPortHandle, const uint32_t u32Pins);

/**
 * @brief PORT interrupt process function
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 */
void PORT_IRQHandler(PORT_HandleType *pPortHandle);

/** @}*/ /* module_driver_port */

uint32_t PORT_GetIntFlag(PORT_InstanceType ePort, uint8_t u8Pin);

#endif

#endif
