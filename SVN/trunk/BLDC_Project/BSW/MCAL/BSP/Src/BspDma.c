/**
 * @file BspDma.c
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-19 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */
#include "BspDma.h"

volatile DMA_HandleType g_tAdcDmaHandle[2];
volatile DMA_InstanceHandleType g_tDmaInstanceHandle;
const DMA_InitType dmaInitCfg =
{
    .eArbitrationAlgorithm = DMA_ARBITRATION_ALGORITHM_FIXED_PRIORITY,
    .bHaltOnError = false
};

void Bsp_DmaInit(void)
{
    DMA_Init(&g_tDmaInstanceHandle, &dmaInitCfg);
    g_tAdcDmaHandle[0].tSettings.pInstance = &g_tDmaInstanceHandle;
    g_tAdcDmaHandle[1].tSettings.pInstance = &g_tDmaInstanceHandle;
}

void Bsp_DmaStart(void)
{
    DMA_StartChannel(&g_tAdcDmaHandle[0]);
    DMA_StartChannel(&g_tAdcDmaHandle[1]);
}

void Bsp_DmaDeInit(void)
{
	DMA_DeInit();
}
