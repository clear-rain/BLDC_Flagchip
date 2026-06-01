/**
 * @file BspSpi.c
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */
#include "string.h"
#include "BspSpi.h"
#include "BspDma.h"
#include "BspGpio.h"

#ifndef ECU_ADDRESS_BLDC
void FCSPI1_IRQHandler(void);
void FCSPI2_IRQHandler(void);
void DMA2_IRQHandler(void);
void DMA3_IRQHandler(void);
void DMA4_IRQHandler(void);
void DMA5_IRQHandler(void);
void DMA_Error_IRQHandler(void);

extern DMA_InstanceHandleType  g_tDmaInstanceHandle;
DMA_HandleType  stFcSpiDmaHandleBuff[(FCSPI_INSTANCE_COUNT<<1u)] =
{
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		 .tSettings.u8Channel = SPI0_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		 .tSettings.u8Channel = SPI0_TX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		.tSettings.u8Channel = SPI1_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		.tSettings.u8Channel = SPI1_TX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
//		.tSettings.u8Channel = SPI2_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
//		.tSettings.u8Channel = SPI2_TX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		// .tSettings.u8Channel = SPI3_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		// .tSettings.u8Channel = SPI3_TX_DMA_CHNL
	}
};

static FCSPI_HandleType stFcSpiHandleBuff[FCSPI_INSTANCE_COUNT] =
	{{.eInstance = FCSPI_0},{.eInstance = FCSPI_1},{.eInstance = FCSPI_2},{.eInstance = FCSPI_3}};

const FCSPI_PCSType e_SPI_PCS[FCSPI_INSTANCE_COUNT] = {SPI0_CS_WHICH_PIN, SPI1_CS_WHICH_PIN, SPI2_CS_WHICH_PIN,SPI3_CS_WHICH_PIN};


static void Bsp_FCSpi_Init(struct SpiDriverIf_t *pDev)
{
    FCSPI_MasterCfgType tFCSpiInitCfg = {0};
    FCSPI_StatusType    eStat         = FCSPI_STATUS_SUCCESS;
	FCSPI_MasterSckPcsHoldTimeType tFCSpiTimecfg;

    tFCSpiInitCfg.u32FCSpiSrcClk = SCG_GetScgClockFreq(SCG_FIRCDIVM_CLK);

    tFCSpiInitCfg.ePcs                  = pDev->spiPriData->ePcs;
    tFCSpiInitCfg.ePcsPolarity          = pDev->spiPriData->ePcsPolarity;
    tFCSpiInitCfg.eIsPcsContinuous      = pDev->spiPriData->eIsPcsContinuous;
    tFCSpiInitCfg.eSckSamplePhase       = pDev->spiPriData->eSckSamplePhase;
    tFCSpiInitCfg.eSckPolarity          = pDev->spiPriData->eSckPolarity;
    tFCSpiInitCfg.eBitFirstOrder        = pDev->spiPriData->eBitFirstOrder;
    tFCSpiInitCfg.u32BitCntPerSecond    = pDev->spiPriData->u32BitCntPerSecond;
    tFCSpiInitCfg.u16BitCountPerFrame   = pDev->spiPriData->u16BitCountPerFrame;
    tFCSpiInitCfg.eTransferTriggerSrc = pDev->spiPriData->eTransferTriggerSrc;
    tFCSpiInitCfg.tTriggerDmaInf.pDmaRxInstanceHandle   = pDev->spiPriData->pDmaRxInstanceHandle;
    tFCSpiInitCfg.tTriggerDmaInf.pDmaTxInstanceHandle   = pDev->spiPriData->pDmaTxInstanceHandle;
    tFCSpiInitCfg.tTriggerDmaInf.u8RxDMAChannelPriority = pDev->spiPriData->pDmaRxInstanceHandle->tSettings.u8Channel;
    tFCSpiInitCfg.tTriggerDmaInf.u8TxDMAChannelPriority = pDev->spiPriData->pDmaTxInstanceHandle->tSettings.u8Channel;
    tFCSpiInitCfg.pStopNotifyCb       = pDev->spiPriData->pStopNotifyCb;
    tFCSpiInitCfg.ePCS23Mode          = pDev->spiPriData->ePCS23Mode;
    tFCSpiInitCfg.eTransferWidthType  = pDev->spiPriData->eTransferWidthType;
    tFCSpiInitCfg.ePinOutStatType     = pDev->spiPriData->ePinOutStatType;
    tFCSpiInitCfg.u32Sckdiv           = pDev->spiPriData->u32Sckdiv;

    eStat = FCSPI_Master_Init(&stFcSpiHandleBuff[pDev->spiPriData->eInstance],&tFCSpiInitCfg);
    if (FCSPI_STATUS_SUCCESS != eStat)
    {
        return;
    }

	tFCSpiTimecfg.u32PCStoPCSHoldUs = pDev->spiPriData->u32PCStoPCSHoldUs;
    tFCSpiTimecfg.u32SCKtoPCSHoldUs = pDev->spiPriData->u32SCKtoPCSHoldUs;
    tFCSpiTimecfg.u32PCStoSCKHoldUs = pDev->spiPriData->u32PCStoSCKHoldUs;
    FCSPI_Master_SetSckPcsHoldTime(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], (const FCSPI_MasterSckPcsHoldTimeType *)&tFCSpiTimecfg);
}

static FCSPI_StatusType Bsp_FCSpi_AsyncTransfer(struct SpiDriverIf_t *pDev, const uint8_t *pucsendData, uint8_t *pucrecvData, uint16_t u16len)
{
    FCSPI_StatusType tStatus;
    FCSPI_AsyncDataInfType tDataInf;

    tStatus = FCSPI_GetLatestTransferStat(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], NULL); /* get transfer status */
	if(FCSPI_STATUS_SUCCESS != tStatus)
	{
		return tStatus;
	}

    tDataInf.pReceiveBuffer = pucrecvData;
    tDataInf.pSendBuffer    = (const uint8_t *)pucsendData;
    tDataInf.u16FrameCount  = u16len;
    tStatus = FCSPI_AsyncTransfer(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], &tDataInf);

    return tStatus;
}

static FCSPI_StatusType Bsp_FCSpi_SyncTransfer(struct SpiDriverIf_t *pDev, const uint8_t *pucsendData, uint8_t *pucrecvData, uint16_t u16len,uint32_t timeout)
{
    FCSPI_StatusType tStatus;
    FCSPI_SyncDataInfType tDataInf;

    tStatus = FCSPI_GetLatestTransferStat(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], NULL); /* get transfer status */
	if(FCSPI_STATUS_SUCCESS != tStatus)
	{
		return tStatus;
	}

    tDataInf.pReceiveBuffer = pucrecvData;
    tDataInf.pSendBuffer    = (const uint8_t *)pucsendData;
    tDataInf.u16FrameCount  = u16len;
	tDataInf.u32Timeout = timeout;
	tStatus = FCSPI_SyncTransfer(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], &tDataInf);

	return tStatus;
}

bool Bsp_FCSpi_CheckSendFinish(struct SpiDriverIf_t *pDev)
{
    return (FCSPI_STATUS_SUCCESS == FCSPI_GetLatestTransferStat(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], NULL));
}

static SpiPrivateData_t s_fcSpiPriDataBuff[FCSPI_INSTANCE_COUNT] =
{
    {
        .eInstance = FCSPI_0,
        .u32BitCntPerSecond = 2000000,
//        .ePcs = e_SPI_PCS[FCSPI_0],
		.ePcs = SPI0_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eIsPcsContinuous = FCSPI_FALSE,
        .u16BitCountPerFrame = 16,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_SECOND_EDGE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_LSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[0],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[1],
        .u32PCStoPCSHoldUs = 6u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    },
    {
        .eInstance = FCSPI_1,
        .u32BitCntPerSecond = 5000000,
//        .ePcs = e_SPI_PCS[FCSPI_1],
		.ePcs = SPI1_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eIsPcsContinuous = FCSPI_FALSE,
        .u16BitCountPerFrame = 24,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_SECOND_EDGE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_MSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[2],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[3],
        .u32PCStoPCSHoldUs = 10u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    },
    {
        .eInstance = FCSPI_2,
        .u32BitCntPerSecond = 2000000,
//        .ePcs = e_SPI_PCS[FCSPI_2],
		.ePcs = SPI2_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eIsPcsContinuous = FCSPI_FALSE,
        .u16BitCountPerFrame = 16,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_SECOND_EDGE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_LSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[4],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[5],
        .u32PCStoPCSHoldUs = 10u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    },
    {
        .eInstance = FCSPI_3,
        .u32BitCntPerSecond = 1000000,
//        .ePcs = e_SPI_PCS[FCSPI_3],
		.ePcs = SPI3_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_SECOND_EDGE,
        .u16BitCountPerFrame = 32,
        .eIsPcsContinuous = FCSPI_FALSE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_MSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[6],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[7],
        .u32PCStoPCSHoldUs = 1u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    }
};

static struct SpiDriverIf_t stFcSpiHandlerBuf[FCSPI_INSTANCE_COUNT] =
{
	{
		.name = "SBC_Spi",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_0],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	},
	{
		.name = "TLE92108_Spi",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_1],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	},
	{
		.name = "NULL0",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_2],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	},
	{
		.name = "NULL1",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_3],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	}
};

struct SpiDriverIf_t *Bsp_FCSpi_GetDevice(char *name)
{
	uint8_t i;
	for (i = 0; i < FCSPI_INSTANCE_COUNT; i++)
	{
		if (0 == strcmp(stFcSpiHandlerBuf[i].name, name))
		{
			return &stFcSpiHandlerBuf[i];
		}
	}
	return NULL;
}
 void FCSPI0_IRQHandler(void)
 {
     fcspi_irq_handler(&stFcSpiHandleBuff[0]);
 }

void FCSPI1_IRQHandler(void)
{
    fcspi_irq_handler(&stFcSpiHandleBuff[1]);
}

//void FCSPI2_IRQHandler(void)
//{
//    fcspi_irq_handler(&stFcSpiHandleBuff[2]);
//}

//void FCSPI3_IRQHandler(void)
//{
// 	fcspi_irq_handler(&stFcSpiHandleBuff[3]);
//}

void DMA2_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[0]);
}

void DMA3_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[1]);
}
void DMA4_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[2]);
}

void DMA5_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[3]);
}

void DMA_Error_IRQHandler(void)
{
	DMA_ProcessErrorInterrupt(&g_tDmaInstanceHandle);
}


void Bsp_FCSpi_DeInit(void)
{
	FCSPI_AbortTransfer(&stFcSpiHandleBuff[0]);
	FCSPI_Deinit(&stFcSpiHandleBuff[0]);
	FCSPI_AbortTransfer(&stFcSpiHandleBuff[1]);
	FCSPI_Deinit(&stFcSpiHandleBuff[1]);
//	FCSPI_AbortTransfer(&stFcSpiHandleBuff[2]);
//	FCSPI_Deinit(&stFcSpiHandleBuff[2]);
//	FCSPI_AbortTransfer(&stFcSpiHandleBuff[3]);
//	FCSPI_Deinit(&stFcSpiHandleBuff[3]);
}


#else

void FCSPI1_IRQHandler(void);
void FCSPI2_IRQHandler(void);
void DMA2_IRQHandler(void);
void DMA3_IRQHandler(void);
void DMA4_IRQHandler(void);
void DMA5_IRQHandler(void);
void DMA_Error_IRQHandler(void);

extern DMA_InstanceHandleType  g_tDmaInstanceHandle;
DMA_HandleType  stFcSpiDmaHandleBuff[(FCSPI_INSTANCE_COUNT<<1u)] =
{	
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		 .tSettings.u8Channel = SPI0_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		 .tSettings.u8Channel = SPI0_TX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		.tSettings.u8Channel = SPI1_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		.tSettings.u8Channel = SPI1_TX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		.tSettings.u8Channel = SPI2_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		.tSettings.u8Channel = SPI2_TX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		// .tSettings.u8Channel = SPI3_RX_DMA_CHNL
	},
	{
		.tSettings.pInstance = &g_tDmaInstanceHandle,
		// .tSettings.u8Channel = SPI3_TX_DMA_CHNL
	}
};

static FCSPI_HandleType stFcSpiHandleBuff[FCSPI_INSTANCE_COUNT] = 
	{{.eInstance = FCSPI_0},{.eInstance = FCSPI_1},{.eInstance = FCSPI_2},{.eInstance = FCSPI_3}};

const FCSPI_PCSType e_SPI_PCS[FCSPI_INSTANCE_COUNT] = {SPI0_CS_WHICH_PIN, SPI1_CS_WHICH_PIN, SPI2_CS_WHICH_PIN,SPI3_CS_WHICH_PIN};


static void Bsp_FCSpi_Init(struct SpiDriverIf_t *pDev)
{
    FCSPI_MasterCfgType tFCSpiInitCfg = {0};
    FCSPI_StatusType    eStat         = FCSPI_STATUS_SUCCESS;    
	FCSPI_MasterSckPcsHoldTimeType tFCSpiTimecfg;

    tFCSpiInitCfg.u32FCSpiSrcClk = SCG_GetScgClockFreq(SCG_FIRCDIVM_CLK);

    tFCSpiInitCfg.ePcs                  = pDev->spiPriData->ePcs;
    tFCSpiInitCfg.ePcsPolarity          = pDev->spiPriData->ePcsPolarity;
    tFCSpiInitCfg.eIsPcsContinuous      = pDev->spiPriData->eIsPcsContinuous;
    tFCSpiInitCfg.eSckSamplePhase       = pDev->spiPriData->eSckSamplePhase;
    tFCSpiInitCfg.eSckPolarity          = pDev->spiPriData->eSckPolarity;
    tFCSpiInitCfg.eBitFirstOrder        = pDev->spiPriData->eBitFirstOrder;
    tFCSpiInitCfg.u32BitCntPerSecond    = pDev->spiPriData->u32BitCntPerSecond;
    tFCSpiInitCfg.u16BitCountPerFrame   = pDev->spiPriData->u16BitCountPerFrame;
    tFCSpiInitCfg.eTransferTriggerSrc = pDev->spiPriData->eTransferTriggerSrc;
    tFCSpiInitCfg.tTriggerDmaInf.pDmaRxInstanceHandle   = pDev->spiPriData->pDmaRxInstanceHandle;
    tFCSpiInitCfg.tTriggerDmaInf.pDmaTxInstanceHandle   = pDev->spiPriData->pDmaTxInstanceHandle;
    tFCSpiInitCfg.tTriggerDmaInf.u8RxDMAChannelPriority = pDev->spiPriData->pDmaRxInstanceHandle->tSettings.u8Channel;
    tFCSpiInitCfg.tTriggerDmaInf.u8TxDMAChannelPriority = pDev->spiPriData->pDmaTxInstanceHandle->tSettings.u8Channel;
    tFCSpiInitCfg.pStopNotifyCb       = pDev->spiPriData->pStopNotifyCb;
    tFCSpiInitCfg.ePCS23Mode          = pDev->spiPriData->ePCS23Mode;
    tFCSpiInitCfg.eTransferWidthType  = pDev->spiPriData->eTransferWidthType;
    tFCSpiInitCfg.ePinOutStatType     = pDev->spiPriData->ePinOutStatType;
    tFCSpiInitCfg.u32Sckdiv           = pDev->spiPriData->u32Sckdiv;

    eStat = FCSPI_Master_Init(&stFcSpiHandleBuff[pDev->spiPriData->eInstance],&tFCSpiInitCfg);
    if (FCSPI_STATUS_SUCCESS != eStat)
    {
        return;
    }

	tFCSpiTimecfg.u32PCStoPCSHoldUs = pDev->spiPriData->u32PCStoPCSHoldUs;
    tFCSpiTimecfg.u32SCKtoPCSHoldUs = pDev->spiPriData->u32SCKtoPCSHoldUs;
    tFCSpiTimecfg.u32PCStoSCKHoldUs = pDev->spiPriData->u32PCStoSCKHoldUs;
    FCSPI_Master_SetSckPcsHoldTime(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], (const FCSPI_MasterSckPcsHoldTimeType *)&tFCSpiTimecfg);
}

static FCSPI_StatusType Bsp_FCSpi_AsyncTransfer(struct SpiDriverIf_t *pDev, const uint8_t *pucsendData, uint8_t *pucrecvData, uint16_t u16len)
{
    FCSPI_StatusType tStatus;
    FCSPI_AsyncDataInfType tDataInf;

    tStatus = FCSPI_GetLatestTransferStat(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], NULL); /* get transfer status */
	if(FCSPI_STATUS_SUCCESS != tStatus)
	{
		return tStatus;
	}

    tDataInf.pReceiveBuffer = pucrecvData;
    tDataInf.pSendBuffer    = (const uint8_t *)pucsendData;
    tDataInf.u16FrameCount  = u16len;
    tStatus = FCSPI_AsyncTransfer(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], &tDataInf);

    return tStatus;
}

static FCSPI_StatusType Bsp_FCSpi_SyncTransfer(struct SpiDriverIf_t *pDev, const uint8_t *pucsendData, uint8_t *pucrecvData, uint16_t u16len,uint32_t timeout)
{
    FCSPI_StatusType tStatus;
    FCSPI_SyncDataInfType tDataInf;

    tStatus = FCSPI_GetLatestTransferStat(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], NULL); /* get transfer status */
	if(FCSPI_STATUS_SUCCESS != tStatus)
	{
		return tStatus;
	}

    tDataInf.pReceiveBuffer = pucrecvData;
    tDataInf.pSendBuffer    = (const uint8_t *)pucsendData;
    tDataInf.u16FrameCount  = u16len;
	tDataInf.u32Timeout = timeout;
	tStatus = FCSPI_SyncTransfer(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], &tDataInf);

	return tStatus;
}

bool Bsp_FCSpi_CheckSendFinish(struct SpiDriverIf_t *pDev)
{
    return (FCSPI_STATUS_SUCCESS == FCSPI_GetLatestTransferStat(&stFcSpiHandleBuff[pDev->spiPriData->eInstance], NULL));
}

static SpiPrivateData_t s_fcSpiPriDataBuff[FCSPI_INSTANCE_COUNT] =
{
    {
        .eInstance = FCSPI_0,
        .u32BitCntPerSecond = 2000000,
//        .ePcs = e_SPI_PCS[FCSPI_0],
		.ePcs = SPI0_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eIsPcsContinuous = FCSPI_FALSE,
        .u16BitCountPerFrame = 24,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_FIRST_EDGE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_MSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[0],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[1],
        .u32PCStoPCSHoldUs = 6u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    },
    {
        .eInstance = FCSPI_1,
        .u32BitCntPerSecond = 2000000,
//        .ePcs = e_SPI_PCS[FCSPI_1],
		.ePcs = SPI1_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eIsPcsContinuous = FCSPI_FALSE,
        .u16BitCountPerFrame = 16,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_SECOND_EDGE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_MSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[2],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[3],
        .u32PCStoPCSHoldUs = 6u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    },
    {
        .eInstance = FCSPI_2,
        .u32BitCntPerSecond = 2000000,
//        .ePcs = e_SPI_PCS[FCSPI_2],
		.ePcs = SPI2_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eIsPcsContinuous = FCSPI_FALSE,
        .u16BitCountPerFrame = 16,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_FIRST_EDGE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_MSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[4],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[5],
        .u32PCStoPCSHoldUs = 6u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    },
    {
        .eInstance = FCSPI_3,
        .u32BitCntPerSecond = 1000000,
//        .ePcs = e_SPI_PCS[FCSPI_3],
		.ePcs = SPI3_CS_WHICH_PIN,
        .ePcsPolarity = FCSPI_PCS_POL_ACTIVE_LOW,
        .eSckSamplePhase = FCSPI_SCK_SAMPLE_SECOND_EDGE,
        .u16BitCountPerFrame = 32,
        .eIsPcsContinuous = FCSPI_FALSE,
        .eSckPolarity = FCSPI_SCK_ACTIVE_HIGH,
        .eBitFirstOrder = FCSPI_MSB_FIRST,
        .eTransferTriggerSrc = FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,
        .pStopNotifyCb = NULL,
        .ePCS23Mode = PCS2_3_PCS,
        .eTransferWidthType = FCSPI_TRANSFER_1_BIT,
        .ePinOutStatType = PINOUT_RETAIN_LAST,
        .pDmaRxInstanceHandle = &stFcSpiDmaHandleBuff[6],
        .pDmaTxInstanceHandle = &stFcSpiDmaHandleBuff[7],
        .u32PCStoPCSHoldUs = 1u,
        .u32SCKtoPCSHoldUs = 1u,
        .u32PCStoSCKHoldUs = 1u,
		.u32Sckdiv = 0xff
    }
};

static struct SpiDriverIf_t stFcSpiHandlerBuf[FCSPI_INSTANCE_COUNT] =
{
	{
		.name = "IMU_Spi",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_0],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	},
	{
		.name = "SBC_Spi",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_1],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	},
	{
		.name = "MotorDriver_Spi",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_2],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	},
	{
		.name = "NULL1",
		.spiPriData = &s_fcSpiPriDataBuff[FCSPI_3],
		.GPIO_Init = FCSpiGpioInit,
		.SpiInit = Bsp_FCSpi_Init,
		.TransmitSync = Bsp_FCSpi_SyncTransfer,
		.TransmitAsync = Bsp_FCSpi_AsyncTransfer
	}
};

struct SpiDriverIf_t *Bsp_FCSpi_GetDevice(char *name)
{
	uint8_t i;
	for (i = 0; i < FCSPI_INSTANCE_COUNT; i++)
	{
		if (0 == strcmp(stFcSpiHandlerBuf[i].name, name))
		{
			return &stFcSpiHandlerBuf[i];
		}
	}
	return NULL;
}
 void FCSPI0_IRQHandler(void)
 {
     fcspi_irq_handler(&stFcSpiHandleBuff[0]);
 }

void FCSPI1_IRQHandler(void)
{
    fcspi_irq_handler(&stFcSpiHandleBuff[1]);
}

void FCSPI2_IRQHandler(void)
{
    fcspi_irq_handler(&stFcSpiHandleBuff[2]);
}

//void FCSPI3_IRQHandler(void)
//{
// 	fcspi_irq_handler(&stFcSpiHandleBuff[3]);
//}

void DMA2_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[0]);
}

void DMA3_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[1]);
}
void DMA4_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[2]);
}

void DMA5_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[3]);
}

void DMA6_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[4]);
}

void DMA7_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&stFcSpiDmaHandleBuff[5]);
}

void DMA_Error_IRQHandler(void)
{
	DMA_ProcessErrorInterrupt(&g_tDmaInstanceHandle);
}


void Bsp_FCSpi_DeInit(void)
{
	FCSPI_AbortTransfer(&stFcSpiHandleBuff[0]);
	FCSPI_Deinit(&stFcSpiHandleBuff[0]);
	FCSPI_AbortTransfer(&stFcSpiHandleBuff[1]);
	FCSPI_Deinit(&stFcSpiHandleBuff[1]);
	FCSPI_AbortTransfer(&stFcSpiHandleBuff[2]);
	FCSPI_Deinit(&stFcSpiHandleBuff[2]);
//	FCSPI_AbortTransfer(&stFcSpiHandleBuff[3]);
//	FCSPI_Deinit(&stFcSpiHandleBuff[3]);
}
#endif
