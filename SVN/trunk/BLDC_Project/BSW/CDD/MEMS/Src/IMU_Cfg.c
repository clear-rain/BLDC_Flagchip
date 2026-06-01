#include "IMU_Cfg.h"
#include "BspIic.h"
//#include "NvM.h"
#include "IMU.h"
#include "IMU_Driver.h"

static uint8_t sui8_ImuTxdata = 0;
static uint8_t sui8_ReadFlg = 5U;
static uint8_t sui8_ReadCnt = 0U;
int8_t g_i8AccChipTemp = 0;
static uint8_t *p_RxData = NULL;
static uint8_t sui8_WriteRegBuff[2] = {0x00, 0x00};
extern FCIIC_MasterHandleType g_tFciicMasterHandle;
extern void FCIIC_Write(FCIIC_MasterHandleType *pFciicMasterHandle, uint8_t u8OriDevAddr, uint32_t subAddr, uint8_t subAddrLen, uint8_t *pData, uint8_t u8DataLen);
extern void FCIIC_WriteAndRead(FCIIC_MasterHandleType *pFciicMasterHandle, uint8_t u8OriDevAddr, uint32_t subAddr, uint8_t subAddrLen, uint8_t *pData, uint8_t u8DataLen);

void FCIIC_Interrupt_CallBack(FCIIC_MasterHandleType *pFciicMasterHandle, FCIIC_StatusType Status)
{
   // (void)pFciicMasterHandle;
    (void)Status;
	if (FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
	{
    }
    else
    {
    }
}

static struct SpiDriverIf_t *pIMU_Spi;

void IMU_SpiInit(void)
{
	pIMU_Spi = Bsp_FCSpi_GetDevice("IMU_Spi");
	if (NULL != pIMU_Spi)
	{
		pIMU_Spi->spiPriData->pStopNotifyCb = Cdd_ImuSpiCompleteCallback;
		pIMU_Spi->GPIO_Init(pIMU_Spi->spiPriData->eInstance);
		pIMU_Spi->SpiInit(pIMU_Spi);
	}
}

void IMU_SpiSendSync(uint8_t *pTxData, uint8_t *pRxData, uint16_t u16Len)
{
	if (NULL != pIMU_Spi)
	{
		pIMU_Spi->TransmitSync(pIMU_Spi, pTxData, pRxData, u16Len, 100);
	}
}

void IMU_WriteReg(uint8 addr, uint8 val)
{
//	I2c_RequestType request;
//
//    sui8_ReadFlg = 100U;
//    sui8_WriteRegBuff[0] = addr;
//	sui8_WriteRegBuff[1] = val;
//   	request.DataDirection= I2C_SEND_DATA;
//    request.BitsSlaveAddressSize = 0;
//    request.BufferSize = 2;
//    request.RepeatedStart = 0;
//    request.DataBuffer = sui8_WriteRegBuff;
//    request.SlaveAddress = IMU_I2C_ADDR;
//	(void)I2c_SyncTransmit(0, &request);
#ifndef IMU_SPI_COMM
	sui8_ImuTxdata = val;
	FCIIC_Write(&g_tFciicMasterHandle, IMU_I2C_ADDR, addr, 1, &sui8_ImuTxdata, 1);
#else
	uint8_t au8TxData[3] = {0};
	uint8_t au8RxData[3] = {0};

	au8TxData[2] = addr;
	au8TxData[1] = 0x00;
	au8TxData[0] = val;

	IMU_SpiSendSync(au8TxData, au8RxData, 1);
#endif /*ECU_ADDRESS_BLDC*/
}

void IMU_ReadRegSync(uint8 addr, uint8* pData, uint8 ui8_readCnt)
{
//	I2c_RequestType request;
//	sui8_WriteRegBuff[0] = addr;
//   	request.DataDirection= I2C_SEND_DATA;
//	request.BitsSlaveAddressSize = 0;
//	request.BufferSize = 1;
//	request.RepeatedStart = 0;
//	request.DataBuffer = sui8_WriteRegBuff;
//	request.SlaveAddress = IMU_I2C_ADDR;
//	(void)I2c_SyncTransmit(0, &request);
//
//	request.DataDirection= I2C_RECEIVE_DATA;
//	request.BitsSlaveAddressSize = 0;
//	request.BufferSize = ui8_readCnt;
//	request.RepeatedStart = 0;
//	request.DataBuffer = pData;
//	request.SlaveAddress = IMU_I2C_ADDR;
//	(void)I2c_SyncTransmit(0, &request);
#ifndef IMU_SPI_COMM
	FCIIC_WriteAndRead(&g_tFciicMasterHandle, IMU_I2C_ADDR, addr, 1, pData, ui8_readCnt);
#else
	uint8_t au8TxData[3] = {0};
	uint8_t au8RxData[3] = {0};

	au8TxData[0] = 0x55;
	au8TxData[1] = 0x55;
	au8TxData[2] = addr|0x80;

	IMU_SpiSendSync(au8TxData, au8RxData, ui8_readCnt);
	*pData = au8RxData[0];
#endif /*ECU_ADDRESS_BLDC*/
}


void IMU_ReadData(uint8 addr, uint8 *val, uint8 len)
{
//	I2c_RequestType request;
//    p_RxData = val;
//    sui8_ReadFlg = 1U;
//    sui8_ReadCnt = len;
//
//    sui8_WriteRegBuff[0] = addr;
//   	request.DataDirection= I2C_SEND_DATA;
//    request.BitsSlaveAddressSize = 0;
//    request.BufferSize = 1;
//    request.RepeatedStart = 0;
//    request.DataBuffer = sui8_WriteRegBuff;
//    request.SlaveAddress = IMU_I2C_ADDR;
//	(void)I2c_AsyncTransmit(0, &request);
#ifndef IMU_SPI_COMM
	FCIIC_WriteAndRead(&g_tFciicMasterHandle, IMU_I2C_ADDR, addr, 1, val, len);
#else
	uint8_t au8TxData[3] = {0};
	uint8_t au8RxData[3] = {0};

	au8TxData[0] = 0;
	au8TxData[1] = 0;
	au8TxData[2] = addr | 0x80;

	IMU_SpiSendSync(au8TxData, au8RxData, len);
	*val = au8RxData[0];
#endif /*ECU_ADDRESS_BLDC*/
}

void I2c_Callback(uint8 ui8Event,uint8 ui8Channel)
{
//	I2c_RequestType tRequestType;
//	if(ui8Event == I2C_EVENT_END_TRANSFER_MASTER)
//	{
//		if(1 == sui8_ReadFlg)// read acc data
//		{
//		    tRequestType.DataDirection= I2C_RECEIVE_DATA;
//		    tRequestType.BitsSlaveAddressSize = 0;
//		    tRequestType.BufferSize = sui8_ReadCnt;
//		    tRequestType.RepeatedStart = 0;
//		    tRequestType.DataBuffer = p_RxData;
//		    tRequestType.SlaveAddress = IMU_I2C_ADDR;
//			(void)I2c_AsyncTransmit(0, &tRequestType);
//			sui8_ReadFlg = 2;
//		}
//		else if(2 == sui8_ReadFlg)// read temperature
//		{
//			I2c_RequestType request;
//
//			sui8_ReadFlg = 3U;
//			sui8_WriteRegBuff[0] = IMU_TEMP_OUT_ADDR;
//			request.DataDirection= I2C_SEND_DATA;
//			request.BitsSlaveAddressSize = 0;
//			request.BufferSize = 1;
//			request.RepeatedStart = 0;
//			request.DataBuffer = sui8_WriteRegBuff;
//			request.SlaveAddress = IMU_I2C_ADDR;
//			(void)I2c_AsyncTransmit(0, &request);
//		}
//		else if(3 == sui8_ReadFlg)// read temperature data
//		{
//			sui8_ReadFlg = 100U;
//			tRequestType.DataDirection= I2C_RECEIVE_DATA;
//		    tRequestType.BitsSlaveAddressSize = 0;
//		    tRequestType.BufferSize = 1;
//		    tRequestType.RepeatedStart = 0;
//		    tRequestType.DataBuffer = (uint8_t *)&g_i8AccChipTemp;
//		    tRequestType.SlaveAddress = IMU_I2C_ADDR;
//			(void)I2c_AsyncTransmit(0, &tRequestType);
//		}
//	}
}

Std_ReturnType Imu_StudyDataWirteNvm(void)
{
//	if ((NVM_IDLE == NVM_GetStatus()) && (FALSE == NVM_GetIsReachAge()))
//	{
//		if(NVM_OK == NVM_WriteBlockData(CDD_IMU_NVM_NUM))
//		{
//			return E_OK;
//		}
//		else
//		{
//			return E_NOT_OK;
//		}
//	}
//	return E_NOT_OK;
	return E_OK;
}
Std_ReturnType Imu_StudyDataReadNvm(void)
{
//	if(NVM_IDLE == NVM_GetStatus())
//	{
//		if(NVM_OK == NVM_ReadBlockData(CDD_IMU_NVM_NUM))
//		{
//			// todo: if write success, read value
//			return E_OK;
//		}
//		else
//		{
//			return E_NOT_OK;
//		}
//	}
//	return E_NOT_OK;
	return E_OK;
}
