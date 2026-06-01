/**
 * @file HwA_port.h
 * @author Flagchip032
 * @brief PORT hardware access layer
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

#ifndef _HWA_PORT_H_
#define _HWA_PORT_H_

#include "device_header.h"

#if PORT_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_port HwA_port
 * @ingroup module_driver_port
 * @{
 */

/********* Local inline function ************/
/**
 * @brief Configure pin
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @param u32PcrReg Pin PCR register value
 */
LOCAL_INLINE void PORT_HWA_ConfigPin(PORT_Type *pPort, uint8_t u8Pin, uint32_t u32PcrReg)
{
    pPort->PCR[u8Pin] = u32PcrReg;
}


/**
 * @brief Read pin interrupt flag
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @return interrupt flag value
 */
LOCAL_INLINE uint32_t PORT_HWA_ReadPinInterruptFlag(PORT_Type *pPort, uint8_t u8Pin)
{
    return pPort->PCR[u8Pin] & (uint32_t)PORT_PCR_ISF_MASK;
}


/**
 * @brief Set pin multiplexing
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @param u32PinMux Pin MXU configuration value
 */
LOCAL_INLINE void PORT_HWA_SetPinMux(PORT_Type *pPort, uint8_t u8Pin, Port_PinMuxType u32PinMux)
{
    uint32_t u32TempRegVal = (uint32_t)(pPort->PCR[u8Pin]);
    pPort->PCR[u8Pin] = ((u32TempRegVal & ~(uint32_t)PORT_PCR_MUX_MASK) | PORT_PCR_MUX(u32PinMux.u32PortPinMode));
}

/**
 * @brief Set pin interrupt mode
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @param u32PinIrqc Pin IRQC configuration value
 */
LOCAL_INLINE void PORT_HWA_SetPinInterruptMode(PORT_Type *pPort, uint8_t u8Pin, uint32_t u32PinIrqc)
{
    uint32_t u32TempRegVal = (uint32_t)(pPort->PCR[u8Pin]);
    pPort->PCR[u8Pin] = ((u32TempRegVal & ~(uint32_t)PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(u32PinIrqc));
}

/**
 * @brief Set pin pull enable
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @param u8PeValue Pin PE configuration value(1/0)
 */
LOCAL_INLINE void PORT_HWA_SetPinPullEnable(PORT_Type *pPort, uint8_t u8Pin, uint8_t u8PeValue)
{
    if (u8PeValue)
    {
        pPort->PCR[u8Pin] |= (uint32_t)PORT_PCR_PE_MASK;
    }
    else
    {
        pPort->PCR[u8Pin] &= ~(uint32_t)PORT_PCR_PE_MASK;
    }
}

/**
 * @brief Set pin pull mode
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @param u8PsValue Pin PS configuration value(1/0)
 */
LOCAL_INLINE void PORT_HWA_SetPinPullMode(PORT_Type *pPort, uint8_t u8Pin, uint8_t u8PsValue)
{
    if (u8PsValue)
    {
        pPort->PCR[u8Pin] |= (uint32_t)PORT_PCR_PS_MASK;
    }
    else
    {
        pPort->PCR[u8Pin] &= ~(uint32_t)PORT_PCR_PS_MASK;
    }
}

/**
 * @brief Set pin drive strength
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @note only hs PAD use this bit
 */
LOCAL_INLINE void PORT_HWA_SetPinDriveStrength(PORT_Type *pPort, uint8_t u8Pin)
{
    pPort->PCR[u8Pin] |= (uint32_t)PORT_PCR_DSE0_MASK;
}

/**
 * @brief Set pin passive filter enable
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 * @param u8PfeValue Pin PFE configuration value(1/0)
 */
LOCAL_INLINE void PORT_HWA_SetPinPassiveFilterEnable(PORT_Type *pPort, uint8_t u8Pin, uint8_t u8PfeValue)
{
    if (u8PfeValue)
    {
        pPort->PCR[u8Pin] |= (uint32_t)PORT_PCR_PFE_MASK;
    }
    else
    {
        pPort->PCR[u8Pin] &= ~(uint32_t)PORT_PCR_PFE_MASK;
    }
}

/**
 * @brief Configure port digital filter
 *
 * @param pPort Port instance
 * @param u32RegValue Enable bit,0-31 bit indicate pin 0-31
 */
LOCAL_INLINE void PORT_HWA_ConfigDigitalFilter(PORT_Type *pPort, uint32_t u32RegValue)
{
    pPort->DFER = u32RegValue;
}

/**
 * @brief Set port digital filter enable
 *
 * @param pPort Port instance
 * @param u8RegBit DFER register bit
 */
LOCAL_INLINE void PORT_HWA_SetDigitalFilterEnable(PORT_Type *pPort, uint8_t u8RegBit)
{
    pPort->DFER |= (uint32_t)1 << u8RegBit;
}

/**
 * @brief Set port digital filter clock source
 *
 * @param pPort Port instance
 * @param eClkSrc Digital filter clock source
 */
LOCAL_INLINE void PORT_HWA_SetDigitalFilterClkSrc(PORT_Type *pPort, PORT_DigitalFilterClkSrcType eClkSrc)
{
    pPort->DFCR |= PORT_DFCR_CS(eClkSrc);
}

/**
 * @brief Configure digital filter width
 * @param pPort Port instance
 * @param u32FilterWidth Digital filter length value,range:0-31
 */
LOCAL_INLINE void PORT_HWA_ConfigDigitalFilterWidth(PORT_Type *pPort, uint32_t u32FilterWidth)
{
    pPort->DFWR = PORT_DFWR_FILT(u32FilterWidth);
}

/**
 * @brief Clear pin interrupt mode
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void PORT_HWA_ClearPinInterruptMode(PORT_Type *pPort, uint8_t u8Pin)
{
    pPort->PCR[u8Pin] &= ~(uint32_t)PORT_PCR_IRQC_MASK;
}

/**
 * @brief Clear pin interrupt flag
 *
 * @param pPort Port instance
 * @param u8Pin Pin number
 */
LOCAL_INLINE void PORT_HWA_ClearPinInterruptFlag(PORT_Type *pPort, uint8_t u8Pin)
{
    pPort->PCR[u8Pin] |= (uint32_t)PORT_PCR_ISF_MASK;
}

/**
 * @brief CLear port digital filter enable
 *
 * @param pPort Port instance
 */
LOCAL_INLINE void PORT_HWA_ClearDigitalFilterEnable(PORT_Type *pPort)
{
    pPort->DFER = (uint32_t)0U;
}

/**
 * @brief Clear port digital filter enable for specific pin
 *
 * @param pPort Port instance
 * @param u8RegBit DFER register bit
 */
LOCAL_INLINE void PORT_HWA_ClearDigitalFilterPin(PORT_Type *pPort, uint8_t u8RegBit)
{
    pPort->DFER &= (uint32_t)~((uint32_t)1 << u8RegBit);
}

/**
 * @brief Clear port digital filter clock source
 *
 * @param pPort Port instance
 */
LOCAL_INLINE void PORT_HWA_ClearDigitalFilterClkSrc(PORT_Type *pPort)
{
    pPort->DFCR &= ~(uint32_t)PORT_DFCR_CS_MASK;
}

/**
 * @brief Clear port digital filter width
 *
 * @param pPort Port instance
 */
LOCAL_INLINE void PORT_HWA_ClearDigitalFilterWidth(PORT_Type *pPort)
{
    pPort->DFWR &= ~(uint32_t)PORT_DFWR_FILT_MASK;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_PORT_H_ */
