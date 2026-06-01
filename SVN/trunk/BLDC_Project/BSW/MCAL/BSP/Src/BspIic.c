#include "BspDma.h"
#include "BspIic.h"
#include "BspInterrupt.h"

// void BspIicInit(struct IicDrvHandle_t *pIicDriverIf);
// void FCIIC_Write(struct IicDrvHandle_t *pIicHandle, uint32_t subAddr, uint8_t subAddrLen, uint8_t u8DataLen);
// void FCIIC_WriteAndRead(struct IicDrvHandle_t *pIicHandle, uint32_t subAddr, uint8_t subAddrLen, uint8_t u8RxDataLen);

// extern DMA_InstanceHandleType g_tDmaInstanceHandle;

// DMA_HandleType g_tIicDmaHandle[2]=
// {
//    {
// 		.tSettings =
// 		{
// 			.pInstance = &g_tDmaInstanceHandle,
// 			.u8Channel = IIC1_TX_DMA_CHNL,
// 		}
//    },

//    {
// 		.tSettings =
// 		{
// 			.pInstance = &g_tDmaInstanceHandle,
// 			.u8Channel = IIC1_RX_DMA_CHNL,
// 		}
//    }
// };


// static FCIIC_MasterHandleType s_tFciicMasterHandleBuf[FCIIC_INSTANCE_COUNT];
// static FCIIC_DmaConfigType tFciicTxDmaCfg[FCIIC_INSTANCE_COUNT];
// static FCIIC_DmaConfigType tFciicRxDmaCfg[FCIIC_INSTANCE_COUNT];

// static IicPrivateData_t stIicPrivateDataBuf[FCIIC_INSTANCE_COUNT] =
// {
// 	{
// 		.eInstance = FCIIC_INSTANCE_0,
// 		.u8_slaveAddr = 0x00u, // IMU IIC address
// 		.pau8_txDatabuf = NULL,
// 		.pau8_rxDatabuf = NULL,
// 		.ptFciicMasterHandle = &s_tFciicMasterHandleBuf[0],
// 		.ptFciicTxDmaConfig = NULL,
// 		.ptFciicRxDmaConfig = NULL,
// 	},
// 	{
// 		.eInstance = FCIIC_INSTANCE_1,
// 		.u8_slaveAddr = 0x00u, // IMU IIC address
// 		.pau8_txDatabuf = NULL,
// 		.pau8_rxDatabuf = NULL,
// 		.ptFciicMasterHandle = &s_tFciicMasterHandleBuf[1],
// 		.ptFciicTxDmaConfig = &tFciicTxDmaCfg[1],
// 		.ptFciicRxDmaConfig = &tFciicRxDmaCfg[1],
// 		.pDmaTxHandle = &g_tIicDmaHandle[0],
// 		.pDmaRxHandle = &g_tIicDmaHandle[1],
// 	}
// };
// static struct IicDrvHandle_t stFcIicHandlerBuf[FCIIC_INSTANCE_COUNT] =
// {
// 	{
// 		.name ="IIC0",
// 		.pIicPrivateData = &stIicPrivateDataBuf[0],
// 		.pIicInit = BspIicInit,
// 	},
// 	{
// 		.name ="IIC1_IMU",
// 		.pIicPrivateData = &stIicPrivateDataBuf[1],
// 		.pIicInit = BspIicInit,
// 		.pFCIIC_Write = FCIIC_Write,
// 		.IicGpio_Init = FCIicGpioInit,
// 		.pFCIIC_WriteAndRead = FCIIC_WriteAndRead,
// 	}
// };
// struct IicDrvHandle_t * BspIic_GetHandle(char *name)
// {
// 	uint8_t i;
// 	for (i = 0; i < FCSPI_INSTANCE_COUNT; i++)
// 	{
// 		if (0 == strcmp(stFcIicHandlerBuf[i].name, name))
// 		{
// 			return &stFcIicHandlerBuf[i];
// 		}
// 	}
// 	return NULL;
// }

// /**
//  * @brief IIC write operation unit for EEPROM interface
//  * @param u8IicIndex IIC instance
//  * @param u8OriDevAddr Device address
//  * @param pData write data buffer
//  * @param u8DataLen write data length
//  */
// void FCIIC_Write(struct IicDrvHandle_t * pIicHandle,  uint32_t subAddr, uint8_t subAddrLen, uint8_t u8DataLen)
// {
//     FCIIC_MasterTransferType transfer;

// 	transfer.u8SlaveAddress = pIicHandle->pIicPrivateData->u8_slaveAddr;
//     transfer.eDirection = FCIIC_WRITE;
//     transfer.subaddress = subAddr;
//     transfer.subaddressSize = subAddrLen;
//     transfer.pData = pIicHandle->pIicPrivateData->pau8_txDatabuf;
//     transfer.u8DataSize = u8DataLen;
//     FCIIC_MasterDmaTransfer(pIicHandle->pIicPrivateData->ptFciicMasterHandle, &transfer);
// }

// /**
//  * @brief IIC Write and then read operation unit for EEPROM interface
//  *
//  * @param u8IicIndex iic instance
//  * @param u8OriDevAddr device address
//  * @param pData write data buffer
//  * @param u8DataLen write data length
//  * @param pRxData receive data buffer
//  * @param u8RxDataLen receive data length point
//  */
// void FCIIC_WriteAndRead(struct IicDrvHandle_t * pIicHandle, uint32_t subAddr, uint8_t subAddrLen, uint8_t u8RxDataLen)
// {
//     FCIIC_MasterTransferType transfer;

//     transfer.u8SlaveAddress =  pIicHandle->pIicPrivateData->u8_slaveAddr;
//     transfer.eDirection = FCIIC_READ;
//     transfer.subaddress = subAddr;
//     transfer.subaddressSize = subAddrLen;
//     transfer.pData = pIicHandle->pIicPrivateData->pau8_rxDatabuf;;
//     transfer.u8DataSize = u8RxDataLen;
//     FCIIC_MasterDmaTransfer(pIicHandle->pIicPrivateData->ptFciicMasterHandle, &transfer);
// }

// void Bsp_DMA_Channel_TransferComplete(struct IicDrvHandle_t * pIicHandle)
// {
//     FCIIC_LL_MasterDmaIRQnHandler(pIicHandle->pIicPrivateData->ptFciicMasterHandle);

//     if ((pIicHandle->pIicPrivateData->ptFciicMasterHandle->tStatus.u8DataOffset == pIicHandle->pIicPrivateData->ptFciicMasterHandle->tStatus.u8DataSize) 
// 			&& (FCIIC_CH_IDLE == pIicHandle->pIicPrivateData->ptFciicMasterHandle->tStatus.eChannelStatus))
//     {
//         if (pIicHandle->pIicPrivateData->ptFciicMasterHandle->tStatus.eDirection == FCIIC_WRITE)
//         {
//             // g_bFinishTransmit = true;
//         }
//         else
//         {
//             // g_bFinishReceive = true;
//         }
//     }
// }
// void BspIicInit(struct IicDrvHandle_t *pIicDriverIf)
// {
// 	uint32_t u32PccFuncClk;
// 	FCIIC_MasterConfigType masterConfig;

// 	/* get default Config */
// 	FCIIC_MasterGetDefaultConfig(&masterConfig);
// 		/* deinit Master Handle */
// 	FCIIC_MasterInitHandle(pIicDriverIf->pIicPrivateData->ptFciicMasterHandle, pIicDriverIf->pIicPrivateData->eInstance);

// 	/* init dma TX Config */
// 	pIicDriverIf->pIicPrivateData->ptFciicTxDmaConfig->pDmaHandle = pIicDriverIf->pIicPrivateData->pDmaTxHandle;
// 	pIicDriverIf->pIicPrivateData->ptFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_IDLE;
// 	pIicDriverIf->pIicPrivateData->pDmaTxHandle->tSettings.callback.pTransferCompleteCallback = Bsp_DMA_Channel_TransferComplete;								// Bsp_DMA_Channel_TransferComplete;

// 	/* init dma Rx Config */
// 	pIicDriverIf->pIicPrivateData->ptFciicRxDmaConfig->pDmaHandle = pIicDriverIf->pIicPrivateData->pDmaRxHandle;
// 	pIicDriverIf->pIicPrivateData->ptFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_IDLE;
// 	pIicDriverIf->pIicPrivateData->pDmaRxHandle->tSettings.callback.pTransferCompleteCallback = Bsp_DMA_Channel_TransferComplete;

// 	/*config dma for iic */
// 	pIicDriverIf->pIicPrivateData->ptFciicMasterHandle->tSettings.pFciicTxDmaConfig = pIicDriverIf->pIicPrivateData->ptFciicTxDmaConfig;
// 	pIicDriverIf->pIicPrivateData->ptFciicMasterHandle->tSettings.pFciicRxDmaConfig = pIicDriverIf->pIicPrivateData->ptFciicRxDmaConfig;

// 	u32PccFuncClk = PCC_GetPccFunctionClock(pIicDriverIf->pIicPrivateData->eInstance);
// 	FCIIC_MasterInit(pIicDriverIf->pIicPrivateData->ptFciicMasterHandle, &masterConfig, u32PccFuncClk);
// }

// void DMA6_IRQHandler(void)
// {
//     DMA_Transfer_Complete_IRQHandler(&g_tIicDmaHandle[1]);
// }


// void DMA7_IRQHandler(void)
// {
//     DMA_Transfer_Complete_IRQHandler(&g_tIicDmaHandle[0]);
// }















/****************************************************************** */

FCIIC_MasterHandleType g_tFciicMasterHandle;
// bool g_bFinishTransmit;
// bool g_bFinishReceive;

typedef struct
{
    uint8_t  u8OriDevAddr;  /* original 7bits device address,  like 0b1010000U */
    uint8_t  u8DataLen;
    uint16_t u16MemAddr;
    uint8_t  *pData;
}FCIIC_EEPROM_DataType;

extern void FCIIC_Interrupt_CallBack(FCIIC_MasterHandleType *pFciicMasterHandle, FCIIC_StatusType Status);
static void FCIIC_ErrorInterrupt_CallBack(FCIIC_MasterHandleType *pFciicMasterHandle,FCIIC_StatusType Status);

/* ################################################################################## */
/* ################################ Local Functions ################################# */


/* ################################################################################## */
/* ################################ Global Functions ################################ */

/**
 * @brief Demo Initial function
 *
 */
void BSP_FCIIC_Init(void)
{
	FCIIC_MasterConfigType masterConfig;
    FCIIC_MasterGetDefaultConfig(&masterConfig);
    FCIIC_MasterInitHandle(&g_tFciicMasterHandle,FCIIC_INSTANCE_0);
    FCIIC_MasterInit(&g_tFciicMasterHandle, &masterConfig, PCC_GetPccFunctionClock(PCC_CLK_FCIIC0));
    FCIIC_MasterEnableInterrupt(&g_tFciicMasterHandle, FCIIC_Interrupt_CallBack,FCIIC_ErrorInterrupt_CallBack, NULL);
}

/**
 * @brief IIC write operation unit for EEPROM interface
 *
 * @param u8IicIndex IIC instance
 * @param u8OriDevAddr Device address
 * @param pData write data buffer
 * @param u8DataLen write data length
 */
void FCIIC_Write(FCIIC_MasterHandleType *pFciicMasterHandle, uint8_t u8OriDevAddr, uint32_t subAddr, uint8_t subAddrLen, uint8_t *pData, uint16_t u16DataLen)
{
	FCIIC_MasterTransferType transfer;

	transfer.u8SlaveAddress = u8OriDevAddr;
	transfer.eDirection = FCIIC_WRITE;
	transfer.subaddress = subAddr;
	transfer.subaddressSize = subAddrLen;
	transfer.pData = pData;
	transfer.u16DataSize = u16DataLen;
	FCIIC_MasterTransferNonBlocking(pFciicMasterHandle, &transfer);
}

/**
 * @brief IIC Write and then read operation unit for EEPROM interface
 *
 * @param pFciicMasterHandle iic Handle
 * @param u8OriDevAddr device address
 * @param pData write data buffer
 * @param u8DataLen write data length
 */
void FCIIC_WriteAndRead(FCIIC_MasterHandleType *pFciicMasterHandle, uint8_t u8OriDevAddr, uint32_t subAddr, uint8_t subAddrLen, uint8_t *pData, uint16_t u16DataLen)
{
	FCIIC_MasterTransferType transfer;

	transfer.u8SlaveAddress = u8OriDevAddr;
	transfer.eDirection = FCIIC_READ;
	transfer.subaddress = subAddr;
	transfer.subaddressSize = subAddrLen;
	transfer.pData = pData;
	transfer.u16DataSize = u16DataLen;
	FCIIC_MasterTransferNonBlocking(pFciicMasterHandle, &transfer);
}


static void FCIIC_ErrorInterrupt_CallBack(FCIIC_MasterHandleType *pFciicMasterHandle, FCIIC_StatusType Status)
{
	(void)pFciicMasterHandle;
	(void)Status;

}


void BSP_FCIIC_DEInit(void)
{
	FCIIC_MasterDeinit(&g_tFciicMasterHandle);
}

