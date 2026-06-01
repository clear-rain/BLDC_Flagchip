/**
 * @file module_driver_port.c
 * @author Flagchip032
 * @brief PORT driver source code
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

#include "module_driver_port.h"

#if PORT_INSTANCE_COUNT > 0U


#ifndef PORT_DEV_ERROR_REPORT
    #define PORT_DEV_ERROR_REPORT   STD_OFF
#endif

#if PORT_DEV_ERROR_REPORT == STD_ON
    #define PORT_ReportDevError(func, error) ReportDevError(PORT_MODULE_ID, func, error)
#endif

/********* Local Variables ************/
/** @brief PORT instance list */
static PORT_Type *const s_pPortInstanceTable[PORT_INSTANCE_COUNT] = PORT_BASE_PTRS;
/** @brief Gpio instance list */
static GPIO_Type *const s_pGpioInstanceTable[PORT_INSTANCE_COUNT] = GPIO_BASE_PTRS;
#if PORT_DEV_ERROR_REPORT == STD_ON
    /** @brief Pin mask list */
    static uint32_t const s_pPinMaskTable[GPIO_INSTANCE_COUNT] = PIN_MASK_BASE;
#endif
/** @brief port common interrupt handle function */
static void Port_CommonProcessInterrupt(PORT_HandleType *pPortHandle, const uint8_t u32Pin);


/***************PORT Global Functions*****************/
/**
 * @brief Initialize port
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param pInitStruct Initialization structure of port
 */
void PORT_InitPins(PORT_HandleType *pPortHandle, const PORT_InitType *const pInitStruct)
{
    #if PORT_DEV_ERROR_REPORT == STD_ON

    uint32_t u32DetPins = pInitStruct->u32PortPins;
    uint32_t u32ValidPins = s_pPinMaskTable[pPortHandle->eInstance];

    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_InitPins_ID, PORT_E_PARAM_INSTANCE);
    }
    else if (NULL == pInitStruct)
    {
        PORT_ReportDevError(PORT_InitPins_ID, PORT_E_PARAM_INPUT);
    }
    else if (u32DetPins != (u32DetPins & u32ValidPins))
    {
        PORT_ReportDevError(PORT_InitPins_ID, PORT_E_PARAM_PIN);
    }
    else
    {
    #endif

        uint32_t u32PcrRegValue = 0U;
        uint32_t u32TempPins = 0U;
        uint8_t u8PinIndex = 0U;
        PORT_InstanceType ePort = pPortHandle->eInstance;
        PORT_Type *const pPort = s_pPortInstanceTable[ePort];
        GPIO_Type *const pGpio = s_pGpioInstanceTable[ePort];
        u32TempPins = pInitStruct->u32PortPins;
        while (u32TempPins)
        {
            if (u32TempPins & ((uint32_t)1 << u8PinIndex))
            {
                u32PcrRegValue |= PORT_PCR_MUX(pInitStruct->uPortPinMux.u32PortPinMode);
                if (pInitStruct->bPullEn)
                {
                    if (PORT_ALT0_FUNC_MODE != pInitStruct->uPortPinMux.u32PortPinMode)
                    {
                        u32PcrRegValue |= PORT_PCR_PE(1U);
                        if (PORT_PULL_UP == pInitStruct->ePullSel)
                        {
                            u32PcrRegValue |= PORT_PCR_PS(1U);
                        }
                        else
                        {
                            u32PcrRegValue &= ~(uint32_t)PORT_PCR_PS_MASK;
                        }
                    }
                }
                else
                {
                    u32PcrRegValue &= ~(uint32_t)PORT_PCR_PE_MASK;
                }

                if (pInitStruct->bDrvStrengthEn)
                {
                    u32PcrRegValue |= (uint32_t)PORT_PCR_DSE0_MASK;
                }

                if (pInitStruct->u8PassiveFilterEn)
                {
                    u32PcrRegValue |= PORT_PCR_PFE(1);
                }
                else
                {
                    u32PcrRegValue &= ~(uint32_t)PORT_PCR_PFE_MASK;
                }

                u32PcrRegValue |= PORT_PCR_ISF_MASK;

                if (PORT_GPIO_MODE == pInitStruct->uPortPinMux.u32PortPinMode)
                {
                    if (PORT_GPIO_OUT == pInitStruct->ePortGpioDir)
                    {
                        if (PORT_GPIO_LOW == pInitStruct->ePortGpioLevel)
                        {
                            GPIO_HWA_ClearPinOutput(pGpio, u8PinIndex);
                        }
                        else
                        {
                            GPIO_HWA_SetPinOutput(pGpio, u8PinIndex);
                        }
                        GPIO_HWA_SetPinDirection(pGpio, u8PinIndex);
                    }
                    else if (PORT_GPIO_IN == pInitStruct->ePortGpioDir)
                    {
                        GPIO_HWA_ClearPinDirection(pGpio, u8PinIndex);
                    }
                    else
                    {
                        u32PcrRegValue &= ~(PORT_PCR_MUX_MASK);
                    }
                }

                PORT_HWA_ConfigPin(pPort, u8PinIndex, u32PcrRegValue);
                PORT_HWA_ClearPinInterruptFlag(pPort, u8PinIndex);
                PORT_HWA_SetPinInterruptMode(pPort, u8PinIndex, (PORT_IrqcConfigurationType)pInitStruct->tInterruptCfg.ePortIsrMode);

            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief De-initialize the Port instance
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 */
void PORT_Deinit(PORT_HandleType *pPortHandle, const uint32_t u32Pins)
{
    #if PORT_DEV_ERROR_REPORT == STD_ON

    uint32_t u32DetPins = u32Pins;
    uint32_t u32ValidPins = s_pPinMaskTable[pPortHandle->eInstance];

    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_Deinit_ID, PORT_E_PARAM_INSTANCE);
    }
    else if (u32DetPins != (u32DetPins & u32ValidPins))
    {
        PORT_ReportDevError(PORT_Deinit_ID, PORT_E_PARAM_PIN);
    }
    else
    {
    #endif
        PORT_InstanceType ePort = pPortHandle->eInstance;
        PORT_Type *const pPort = s_pPortInstanceTable[ePort];
        uint8_t u8PinIndex = 0U;
        uint32_t u32TempPins = u32Pins;

        while (u32TempPins)
        {
            if (u32TempPins & ((uint32_t)1 << u8PinIndex))
            {
                PORT_HWA_ConfigPin(pPort, u8PinIndex, (uint32_t)0U);

                pPortHandle->tSettings.PORT_PinInterruptCallBackType = NULL;
                
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
        __NVIC_DisableIRQ((IRQn_Type)((uint32_t)PORTA_IRQn + (uint32_t)ePort));
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


/**
 * @brief Set port pin mode
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @param uPinMux Port mux function.
 */
void PORT_SetPinMode(PORT_HandleType *pPortHandle, const uint32_t u32Pins, const Port_PinMuxType uPinMux)
{
    #if PORT_DEV_ERROR_REPORT == STD_ON

    uint32_t u32DetPins = u32Pins;
    uint32_t u32ValidPins = (uint32_t)s_pPinMaskTable[pPortHandle->eInstance];

    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_SetPinMode_ID, PORT_E_PARAM_INSTANCE);
    }
    else if (u32DetPins != (u32DetPins & u32ValidPins))
    {
        PORT_ReportDevError(PORT_SetPinMode_ID, PORT_E_PARAM_PIN);
    }
    else
    {
    #endif

        uint8_t u8PinIndex = 0U;
        uint32_t u32TempPins = 0U;
        PORT_InstanceType ePort = pPortHandle->eInstance;
        PORT_Type *const pPort = s_pPortInstanceTable[ePort];

        u32TempPins = u32Pins;
        while (u32TempPins)
        {
            if (u32TempPins & ((uint32_t)1 << u8PinIndex))
            {
                PORT_HWA_SetPinMux(pPort, u8PinIndex, uPinMux);
            }

            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief set interrupt config of port
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 * @param ePortPinIrq The config of interrupt.
 */
void PORT_SetInterruptCfg(PORT_HandleType *pPortHandle, const uint32_t u32Pins, PORT_IrqcConfigurationType ePortPinIrq)
{
    #if PORT_DEV_ERROR_REPORT == STD_ON

    uint32_t u32DetPins = u32Pins;
    uint32_t u32ValidPins = s_pPinMaskTable[pPortHandle->eInstance];

    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_SetInterruptCfg_ID, PORT_E_PARAM_INSTANCE);
    }
    else if (u32DetPins != (u32DetPins & u32ValidPins))
    {
        PORT_ReportDevError(PORT_SetInterruptCfg_ID, PORT_E_PARAM_PIN);
    }
    else
    {
    #endif
        uint8_t u8PinIndex = 0U;
        uint32_t u32TempPins = u32Pins;
        PORT_InstanceType ePort = pPortHandle->eInstance;
        PORT_Type *const pPort = s_pPortInstanceTable[ePort];

        while (u32TempPins)
        {
            if (u32TempPins & ((uint32_t)1 << u8PinIndex))
            {
                PORT_HWA_ClearPinInterruptFlag(pPort, u8PinIndex);
                PORT_HWA_SetPinInterruptMode(pPort, u8PinIndex, ePortPinIrq);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Initialize digital filter for Port instance
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param pDFStruct Digital filter initialization structure of port
 */
void PORT_InitDigitalFilterPort(PORT_HandleType *pPortHandle, const PORT_DigitalFilterType * const pDFStruct)
{
    #if PORT_DEV_ERROR_REPORT == STD_ON

    uint32_t u32DetPins = pDFStruct->u32PortPinsEn;
    uint32_t u32ValidPins = s_pPinMaskTable[pPortHandle->eInstance];

    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_InitDigitalFilterPort_ID, PORT_E_PARAM_INSTANCE);
    }
    else if (u32DetPins != (u32DetPins & u32ValidPins))
    {
        PORT_ReportDevError(PORT_InitDigitalFilterPort_ID, PORT_E_PARAM_PIN);
    }
    else
    {
    #endif

        PORT_InstanceType ePort = pPortHandle->eInstance;

        PORT_Type *const pPort = s_pPortInstanceTable[ePort];

        if (0u != pDFStruct->u32PortPinsEn)
        {

            if (PORT_FILTER_CLOCL_SRC == pDFStruct->eClkSrc)
            {
                PORT_HWA_SetDigitalFilterClkSrc(pPort, pDFStruct->eClkSrc);
            }
            else
            {
                PORT_HWA_ClearDigitalFilterClkSrc(pPort);
            }
            PORT_HWA_ConfigDigitalFilterWidth(pPort, (uint32_t)pDFStruct->u8FilterLength);
            PORT_HWA_ConfigDigitalFilter(pPort, pDFStruct->u32PortPinsEn);
        }
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief De-initialize digital filter for Port instance
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 */
void PORT_DeinitDigitalFilterPort(PORT_HandleType *pPortHandle)
{

    #if PORT_DEV_ERROR_REPORT == STD_ON
    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_DeinitDigitalFilterPort_ID, PORT_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        PORT_InstanceType ePort = pPortHandle->eInstance;
        PORT_Type *const pPort = s_pPortInstanceTable[ePort];
        PORT_HWA_ClearDigitalFilterClkSrc(pPort);
        PORT_HWA_ClearDigitalFilterWidth(pPort);
        PORT_HWA_ClearDigitalFilterEnable(pPort);
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Enable the digital filter function for the specific pin.
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 */
void PORT_EnableDigitalFilterPin(PORT_HandleType *pPortHandle, const uint32_t u32Pins)
{
    #if PORT_DEV_ERROR_REPORT == STD_ON

    uint32_t u32DetPins = u32Pins;
    uint32_t u32ValidPins = s_pPinMaskTable[pPortHandle->eInstance];

    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_EnableDigitalFilterPin_ID, PORT_E_PARAM_INSTANCE);
    }
    else if (u32DetPins != (u32DetPins & u32ValidPins))
    {
        PORT_ReportDevError(PORT_EnableDigitalFilterPin_ID, PORT_E_PARAM_PIN);
    }
    else
    {
    #endif
        PORT_InstanceType ePort = pPortHandle->eInstance;
        uint8_t u8PinIndex = 0U;
        uint32_t u32TempPins = u32Pins;
        PORT_Type *const pPort = s_pPortInstanceTable[ePort];
        while (u32TempPins)
        {
            if (u32TempPins & ((uint32_t)1 << u8PinIndex))
            {
                PORT_HWA_SetDigitalFilterEnable(pPort, u8PinIndex);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Disable the digital filter function for the specific pin.
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u32Pins The bit of u32Pins indicate the Pin number of this Port.
 */
void PORT_DisableDigitalFilterPin(PORT_HandleType *pPortHandle, const uint32_t u32Pins)
{
    #if PORT_DEV_ERROR_REPORT == STD_ON

    uint32_t u32DetPins = u32Pins;
    uint32_t u32ValidPins = s_pPinMaskTable[pPortHandle->eInstance];

    if (pPortHandle->eInstance >= PORT_INSTANCE_COUNT)
    {
        PORT_ReportDevError(PORT_DisableDigitalFilterPin_ID, PORT_E_PARAM_INSTANCE);
    }
    else if (u32DetPins != (u32DetPins & u32ValidPins))
    {
        PORT_ReportDevError(PORT_DisableDigitalFilterPin_ID, PORT_E_PARAM_PIN);
    }
    else
    {
    #endif
        PORT_InstanceType ePort = pPortHandle->eInstance;
        uint8_t u8PinIndex = 0U;
        uint32_t u32TempPins = u32Pins;
        PORT_Type *pPort;
        pPort = s_pPortInstanceTable[ePort];
        while (u32TempPins)
        {
            if (u32TempPins & ((uint32_t)1 << u8PinIndex))
            {
                PORT_HWA_ClearDigitalFilterPin(pPort, u8PinIndex);
            }
            u32TempPins &= (uint32_t)~((uint32_t)1 << u8PinIndex);
            u8PinIndex++;
        }
        #if PORT_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief port common interrupt handle function
 *
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 * @param u8Pin bit of u8Pin indicate pin number
 */
static void Port_CommonProcessInterrupt(PORT_HandleType *pPortHandle, const uint8_t u8Pin)
{
    if (NULL != pPortHandle->tSettings.PORT_PinInterruptCallBackType)
    {
        pPortHandle->tSettings.PORT_PinInterruptCallBackType(pPortHandle, (uint32_t)1 << u8Pin);
    }
}


/***************PORT IRQ Functions*****************/
/**
 * @brief PORT interrupt process function
 * @param pPortHandle pPortHandle PORT handle for PORT functionality
 */
void PORT_IRQHandler(PORT_HandleType *pPortHandle)
{
    uint8_t u8PinIndex;
    PORT_InstanceType ePort = pPortHandle->eInstance;
    PORT_Type *pPort = s_pPortInstanceTable[ePort];
    for (u8PinIndex = 0U; u8PinIndex < (uint32_t)32; u8PinIndex++)
    {
        if (PORT_HWA_ReadPinInterruptFlag(pPort, u8PinIndex))
        {
            PORT_HWA_ClearPinInterruptFlag(pPort, u8PinIndex);
            Port_CommonProcessInterrupt(pPortHandle, u8PinIndex);
        }
    }
}

uint32_t PORT_GetIntFlag(PORT_InstanceType ePort, uint8_t u8Pin)
{
	PORT_Type *const pPort = s_pPortInstanceTable[ePort];
	return PORT_HWA_ReadPinInterruptFlag(pPort, u8Pin);
}


#endif

