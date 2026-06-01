/**
 * @file BspDma.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */
#ifndef BSW_MCAL_BSP_INC_BSPDMA_H_
#define BSW_MCAL_BSP_INC_BSPDMA_H_

#include "main.h"



#define ADC0_DMA_CHANNEL DMA_CHANNEL_0
#define ADC1_DMA_CHANNEL DMA_CHANNEL_1

#define SPI0_RX_DMA_CHNL DMA_CHANNEL_2
#define SPI0_TX_DMA_CHNL DMA_CHANNEL_3
#define SPI1_RX_DMA_CHNL DMA_CHANNEL_4
#define SPI1_TX_DMA_CHNL DMA_CHANNEL_5
#define SPI2_RX_DMA_CHNL DMA_CHANNEL_6
#define SPI2_TX_DMA_CHNL DMA_CHANNEL_7
#define SPI3_RX_DMA_CHNL //DMA_CHANNEL_6
#define SPI3_TX_DMA_CHNL //DMA_CHANNEL_7

// #define IIC1_RX_DMA_CHNL DMA_CHANNEL_6
// #define IIC1_TX_DMA_CHNL DMA_CHANNEL_7

extern void Bsp_DmaInit(void);
void Bsp_DmaDeInit(void);
extern void Bsp_DmaStart(void);

#endif /* BSW_MCAL_BSP_INC_BSPDMA_H_ */
