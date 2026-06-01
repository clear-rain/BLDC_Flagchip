/*
 * MotorDriver_Driver.c
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */
#include "BspGpio.h"
#include "BspSpi.h"
#include "MotorDriver_Cfg.h"
#include "MotorDriver_Driver.h"


extern MotorDriver_SPI_RegTXD_T MotorDriver_SPI_RegTXD[MOTORDRIVER_SPIREG_NUM];
extern MotorDriver_SPI_RegRXD_T MotorDriver_SPI_RegRXD[MOTORDRIVER_SPIREG_NUM];
extern MotorDriver_SPI_RegTXD_T MotorDriver_SPI_RegTXD_Read[MOTORDRIVER_SPIREG_NUM];
static struct SpiDriverIf_t *pMotorDriver_Spi;
//static struct SpiDriverIf_t *pTLE92108_Spi_temp;


void MotorDriver_SpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr)
{
	(void)pFcspiHandle;
	(void)bIsInIsr;
}
void MotorDriver_SpiInit(void)
{
	pMotorDriver_Spi = Bsp_FCSpi_GetDevice("MotorDriver_Spi");
	if(NULL != pMotorDriver_Spi)
	{
		pMotorDriver_Spi->spiPriData->pStopNotifyCb = MotorDriver_SpiCompleteCallback;
		pMotorDriver_Spi->GPIO_Init(pMotorDriver_Spi->spiPriData->eInstance);
		pMotorDriver_Spi->SpiInit(pMotorDriver_Spi);
	}
}
FCSPI_StatusType TLE92108_SpiSendSync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len)
{
//	pTLE92108_Spi_temp = Bsp_FCSpi_GetDevice("TLE92108_Spi");
	 while (true != Bsp_FCSpi_CheckSendFinish(pMotorDriver_Spi)){
	 }
	return pMotorDriver_Spi->TransmitSync(pMotorDriver_Spi,pTxData,pRxData,u16Len,100);
}

FCSPI_StatusType MotorDriver_SpiSendAsync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len)
{
	return pMotorDriver_Spi->TransmitAsync(pMotorDriver_Spi,pTxData,pRxData,u16Len);
}


FCSPI_StatusType MotorDriver_RegInitSync(void)
{
    FCSPI_StatusType ret=FCSPI_STATUS_SUCCESS;
    /*configuration*/
    //test read
    for(uint8_t i = 0u; i < MOTORDRIVER_SPIREG_NUM; i++)
    {
    	TLE92108_SpiSendSync((uint8_t *)(&MotorDriver_SPI_RegTXD[i].RegData),(uint8_t *)(&MotorDriver_SPI_RegRXD[i].RegData),1);
    }


//	pTLE92108_Spi_temp = Bsp_FCSpi_GetDevice("TLE92108_Spi");
//
//	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[0]);
//	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
//	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[1]);
//	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
//	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[2]);
//	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
//
//	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[0]);
//	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
//	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[1]);
//	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
//	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[2]);
//	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
//
//    for(int i = 0; i < TLE92104_BANK0_CTRL_Registers_Send_Count; i++)
//    {
//        g_au32MotorDriverSpiInitTxData[i] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK0_CTRL_REG_SPI_Frame_Table[i]);
//    }
//    for(int i  = 0; i < TLE92104_BANK1_CTRL_Registers_Send_Count; i++)
//    {
//        g_au32MotorDriverSpiInitTxData[i + TLE92104_BANK0_CTRL_Registers_Send_Count] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[i]);
//    }
//
//	 while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
//	 }
//	ret |= TLE92108_SpiSendSync((uint8_t *)&g_au32MotorDriverSpiInitTxData, (uint8_t *)&g_au32MotorDriverSpiInitRxData,\
//    (uint16_t)INIT_REG_COUNT);
//
//	while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
//	}
//
//    for(int i = 0; i < TLE92104_All_CTRL_REG_COUNT; i++)
//    {
//        g_au32MotorDriverSpiInitReadBackTxData[i] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[i]);
//    }
//    while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
//    }
//    ret |= TLE92108_SpiSendSync((uint8_t *)&g_au32MotorDriverSpiInitReadBackTxData, (uint8_t *)&g_au32MotorDriverSpiInitReadBackRxData,\
//    (uint16_t)TLE92104_All_CTRL_REG_COUNT);
//    while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
//    }
//
    return ret;

}

FCSPI_StatusType MotorDriver_RegSendAsyncTask(void)
{
    FCSPI_StatusType ret=FCSPI_STATUS_SUCCESS;

	for(uint8_t i = 0u; i < MOTORDRIVER_SPIREG_NUM; i++)
	{
		TLE92108_SpiSendSync((uint8_t *)(&MotorDriver_SPI_RegTXD_Read[i].RegData),(uint8_t *)(&MotorDriver_SPI_RegRXD[i].RegData),1);
	}
//	pTLE92108_Spi_temp = Bsp_FCSpi_GetDevice("TLE92108_Spi");
//
//    for(int i = 0; i < TLE92104_Usual_Use_CTRL_Registers_Count; i++)
//    {
//        g_au32MotorDriverSpiSendTaskTxData[i] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[i]);
//    }
//
//    //after set send buffer, set status to read only
//    TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_GENSTAT_INDEX].OP = OP_Read_Only_Bit;
//    TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_DSOV_INDEX].OP = OP_Read_Only_Bit;
//
//    ret |= TLE92108_SpiSendAsync((uint8_t *)&g_au32MotorDriverSpiSendTaskTxData, (uint8_t *)&g_au32MotorDriverSpiSendTaskRxData,\
//    (uint16_t)TLE92104_Usual_Use_CTRL_Registers_Count);
//
    return ret;

}

