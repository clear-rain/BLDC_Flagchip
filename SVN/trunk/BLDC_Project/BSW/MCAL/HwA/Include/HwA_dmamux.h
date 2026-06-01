/**
 * @file HwA_dmamux.h
 * @author Flagchip030
 * @brief DMAMUX hardware access layer
 * @version 2.0.0
 * @date 2024-04-20
 * 
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 * 
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip030   N/A          First version
*********************************************************************************/

#ifndef _HWA_DMAMUX_H_
#define _HWA_DMAMUX_H_

#include "device_header.h"

#if DMAMUX_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_dmamux HwA_dmamux
 * @ingroup module_driver_dma
 * @{
 */

/**
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum
{
    DMA_REQ_DISABLED                        = 0U,
    ENET_MAC0_TIMER_OR_CH0_CH3              = 1U,
    DMA_REQ_FCUART0_RX                      = 2U,
    DMA_REQ_FCUART0_TX                      = 3U,
    DMA_REQ_FCUART1_RX                      = 4U,
    DMA_REQ_FCUART1_TX                      = 5U,
    DMA_REQ_FCUART2_RX                      = 6U,
    DMA_REQ_FCUART2_TX                      = 7U,
    DMA_REQ_FCIIC1_RX                       = 8U,
    DMA_REQ_FCIIC1_TX                       = 9U,
    DMA_REQ_I2S1_RX                         = 12U,
    DMA_REQ_I2S1_TX                         = 13U,
    DMA_REQ_FCSPI0_RX                       = 14U,
    DMA_REQ_FCSPI0_TX                       = 15U,
    DMA_REQ_FCSPI1_RX                       = 16U,
    DMA_REQ_FCSPI1_TX                       = 17U,
    DMA_REQ_FCSPI2_RX                       = 18U,
    DMA_REQ_FCSPI2_TX                       = 19U,
    DMA_REQ_FTU1_CHANNEL_0                  = 20U,
    DMA_REQ_FTU1_CHANNEL_1                  = 21U,
    DMA_REQ_FTU1_CHANNEL_2                  = 22U,
    DMA_REQ_FTU1_CHANNEL_3                  = 23U,
    DMA_REQ_FTU1_CHANNEL_4                  = 24U,
    DMA_REQ_FTU1_CHANNEL_5                  = 25U,
    DMA_REQ_FTU1_CHANNEL_6                  = 26U,
    DMA_REQ_FTU1_CHANNEL_7                  = 27U,
    DMA_REQ_FTU2_CHANNEL_0                  = 28U,
    DMA_REQ_FTU2_CHANNEL_1                  = 29U,
    DMA_REQ_FTU2_CHANNEL_2_FCUART3_RX       = 30U,
    DMA_REQ_FTU2_CHANNEL_3_FCUART3_TX       = 31U,
    DMA_REQ_FTU2_CHANNEL_4_FCUART4_RX       = 32U,
    DMA_REQ_FTU2_CHANNEL_5_FCUART4_TX       = 33U,
    DMA_REQ_FTU2_CHANNEL_6_FCUART5_RX       = 34U,
    DMA_REQ_FTU2_CHANNEL_7_FCUART5_TX       = 35U,
    DMA_REQ_FTU0_OR_CH0_CH7                 = 36U,
    DMA_REQ_FTU3_OR_CH0_CH7                 = 37U,
    DMA_REQ_FTU4_OR_CH0_CH7                 = 38U,
    DMA_REQ_FTU5_OR_CH0_CH7                 = 39U,
    DMA_REQ_CMP1_CAN3                       = 40U,
    DMA_REQ_CMP2_CAN4                       = 41U,
    DMA_REQ_ADC0                            = 42U,
    DMA_REQ_ADC1                            = 43U,
    DMA_REQ_FCIIC0_RX                       = 44U,
    DMA_REQ_FCIIC0_TX                       = 45U,
    DMA_REQ_PTIMER0                         = 46U,
    DMA_REQ_PTIMER1_CAN5                    = 47U,
    DMA_REQ_CMP0                            = 48U,
    DMA_REQ_PORTA                           = 49U,
    DMA_REQ_PORTB                           = 50U,
    DMA_REQ_PORTC                           = 51U,
    DMA_REQ_PORTD                           = 52U,
    DMA_REQ_PORTE                           = 53U,
    DMA_REQ_FLEXCAN0                        = 54U,
    DMA_REQ_FLEXCAN1                        = 55U,
    DMA_REQ_FLEXCAN2                        = 56U,
    DMA_REQ_I2S0_RX                         = 57U,
    DMA_REQ_I2S0_TX                         = 58U,
    DMA_REQ_AONTIMER0                       = 59U,
    DMA_REQ_FCSPI3_RX                       = 60U,
    DMA_REQ_FCSPI3_TX                       = 61U,
    DMA_REQ_DMAMUX_ALWAYS_ENABLED0          = 62U,
    DMA_REQ_DMAMUX_ALWAYS_ENABLED1          = 63U
} DMA_RequestSourceType;

/**
 * @brief Get whether DMAMUX is enabled for the specified DMA channel
 * 
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @return true DMAMUX is enabled for the specified DMA channel
 * @return false DMAMUX is disabled for the specified DMA channel
 */
LOCAL_INLINE bool DMAMUX_HWA_GetEnableFlag(const DMAMUX_Type *const pDmamux, uint8_t u8Channel)
{
    uint8_t u8TmpVal = (pDmamux->CHCFG[u8Channel] & DMAMUX_CHCFG_ENBL_MASK) >> DMAMUX_CHCFG_ENBL_SHIFT;
    return (bool)((u8TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the request source for the specified DMA channel
 * 
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @return DMA_RequestSourceType the request source of the specified DMA channel
 */
LOCAL_INLINE DMA_RequestSourceType DMAMUX_HWA_GetRequestSource(const DMAMUX_Type *const pDmamux, uint8_t u8Channel)
{
    uint8_t u8TmpVal = (pDmamux->CHCFG[u8Channel] & DMAMUX_CHCFG_SOURCE_MASK) >> DMAMUX_CHCFG_SOURCE_SHIFT;
    return (DMA_RequestSourceType)u8TmpVal;
}

/**
 * @brief Set the request source for the specified DMA channel
 * 
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @param bEnable whether to enable DMAMUX for the specified DMA channel
 * @param eReqSrc the request source to set for the specified DMA channel
 */
LOCAL_INLINE void DMAMUX_HWA_SetRequestSource(DMAMUX_Type *const pDmamux, uint8_t u8Channel, bool bEnable,
                                              DMA_RequestSourceType eReqSrc)
{
    pDmamux->CHCFG[u8Channel] = (uint8_t)((pDmamux->CHCFG[u8Channel] & ~(DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE_MASK)) |
                                DMAMUX_CHCFG_ENBL(bEnable) | DMAMUX_CHCFG_SOURCE(eReqSrc));
}

/**
 * @brief Get whether periodic trig is enabled for the specified DMA channel
 * 
 * @note Only DMA channel 0~3 supports periodic trig
 * 
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @return true periodic trig is enabled for the specified DMA channel
 * @return true periodic trig is disabled for the specified DMA channel
 */
LOCAL_INLINE bool DMAMUX_HWA_GetPeriodicTrigFlag(const DMAMUX_Type *const pDmamux, uint8_t u8Channel)
{
    uint8_t u8TmpVal = (pDmamux->CHCFG[u8Channel] & DMAMUX_CHCFG_TRIG_MASK) >> DMAMUX_CHCFG_TRIG_SHIFT;
    return (bool)((u8TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable periodic trig for the specified DMA channel
 * 
 * @note Only DMA channel 0~3 supports periodic trig
 * 
 * @param pDmamux the base address of the DMAMUX instance
 * @param u8Channel the selected DMA channel
 * @param bEnable whether to enable periodic trig for the specified DMA channel
 */
LOCAL_INLINE void DMAMUX_HWA_SetPeriodicTrigFlag(DMAMUX_Type *const pDmamux, uint8_t u8Channel, bool bEnable)
{
    pDmamux->CHCFG[u8Channel] = (uint8_t)((pDmamux->CHCFG[u8Channel] & ~DMAMUX_CHCFG_TRIG_MASK) | DMAMUX_CHCFG_TRIG(bEnable));
}

/** @}*/

#endif

#endif /* _HWA_DMAMUX_H_ */
