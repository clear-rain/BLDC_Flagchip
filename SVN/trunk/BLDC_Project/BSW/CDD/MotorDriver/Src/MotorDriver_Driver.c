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

#define INIT_REG_COUNT 31

static struct SpiDriverIf_t *pTLE92108_Spi;
static struct SpiDriverIf_t *pTLE92108_Spi_temp;
uint32 g_au32MotorDriverSpiInitTxData[INIT_REG_COUNT] = {0};
uint32 g_au32MotorDriverSpiInitRxData[INIT_REG_COUNT] = {0};
uint32 g_au32MotorDriverSpiInitReadBackTxData[TLE92104_All_CTRL_REG_COUNT] = {0};
uint32 g_au32MotorDriverSpiInitReadBackRxData[TLE92104_All_CTRL_REG_COUNT] = {0};
uint32 g_au32MotorDriverSpiSendTaskTxData[TLE92104_Usual_Use_CTRL_Registers_Count] = {0};
uint32 g_au32MotorDriverSpiSendTaskRxData[TLE92104_Usual_Use_CTRL_Registers_Count] = {0};

extern TLE9210X_SPI_Frame TLE92104_BANK0_CTRL_REG_SPI_Frame_Table[TLE92104_BANK0_CTRL_Registers_Send_Count];
extern TLE9210X_SPI_Frame TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[TLE92104_BANK1_CTRL_Registers_Send_Count];
extern TLE9210X_SPI_Frame TLE92104_All_CTRL_REG_SPI_Frame_Table[TLE92104_All_CTRL_REG_COUNT];

void TLE92108_SpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);
void TLE92108_SpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr)
{
	(void)pFcspiHandle;
	(void)bIsInIsr;
}
void TLE92108_SpiInit(void)
{
	pTLE92108_Spi = Bsp_FCSpi_GetDevice("TLE92108_Spi");
	if(NULL != pTLE92108_Spi)
	{
		pTLE92108_Spi->spiPriData->pStopNotifyCb = TLE92108_SpiCompleteCallback;
		pTLE92108_Spi->GPIO_Init(pTLE92108_Spi->spiPriData->eInstance);
		pTLE92108_Spi->SpiInit(pTLE92108_Spi);
	}
}
FCSPI_StatusType TLE92108_SpiSendSync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len)
{
	pTLE92108_Spi_temp = Bsp_FCSpi_GetDevice("TLE92108_Spi");
	 while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
	 }
	return pTLE92108_Spi->TransmitSync(pTLE92108_Spi,pTxData,pRxData,u16Len,100);
}

FCSPI_StatusType TLE92108_SpiSendAsync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len)
{
	return pTLE92108_Spi->TransmitAsync(pTLE92108_Spi,pTxData,pRxData,u16Len);
}



uint8_t get_bit_from_rx_data(uint8_t m, uint8_t n)
{
    if (m >= TLE92104_Usual_Use_CTRL_Registers_Count || n >= 24)
    {
        return 0; // Out of bounds
    }
    return (g_au32MotorDriverSpiSendTaskRxData[m] >> n) & 0x01;
}

uint32 TLE9210X_SPI_Frame_To_Uint32(TLE9210X_SPI_Frame frame) {
    uint32 result = 0;
    result |= (frame.data & 0xFFFF) << 0;       // Bits 0-15: Data
    result |= (frame.OP & 0x01) << 16;          // Bit 16: Control bit
    result |= (frame.address & 0x1F) << 17;     // Bits 17-21: Address
    result |= (frame.labt & 0x01) << 22;        // Bit 22: LABT
    result |= (frame.msb & 0x01) << 23;         // Bit 23: MSB
    result &= 0xFFFFFF;                         // Ensure remaining bits are set to 0
    return result;
}

FCSPI_StatusType TLE9210x_SpiSendSync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len)
{
	return pTLE92108_Spi->TransmitSync(pTLE92108_Spi,pTxData,pRxData,u16Len,100);
}

FCSPI_StatusType TLE9210x_SpiSendAsync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len)
{
	return pTLE92108_Spi->TransmitAsync(pTLE92108_Spi,pTxData,pRxData,u16Len);
}
uint32_t adwBspFCSpiData[1] = {12};
uint32_t adwBspFCSpiDataRecv[1] = {0};
FCSPI_StatusType TLE9210x_RegInitSync(void)
{
    FCSPI_StatusType ret=FCSPI_STATUS_SUCCESS;
	pTLE92108_Spi_temp = Bsp_FCSpi_GetDevice("TLE92108_Spi");
	
	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[0]);
	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[1]);
	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[2]);
	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);

	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[0]);
	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[1]);
	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);
	adwBspFCSpiData[0] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[2]);
	TLE92108_SpiSendSync((uint8_t *)&adwBspFCSpiData, (uint8_t *)&adwBspFCSpiDataRecv,(uint16_t)1);

    for(int i = 0; i < TLE92104_BANK0_CTRL_Registers_Send_Count; i++)
    {
        g_au32MotorDriverSpiInitTxData[i] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK0_CTRL_REG_SPI_Frame_Table[i]);
    }
    for(int i  = 0; i < TLE92104_BANK1_CTRL_Registers_Send_Count; i++)
    {
        g_au32MotorDriverSpiInitTxData[i + TLE92104_BANK0_CTRL_Registers_Send_Count] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[i]);
    }

	 while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
	 }
	ret |= TLE92108_SpiSendSync((uint8_t *)&g_au32MotorDriverSpiInitTxData, (uint8_t *)&g_au32MotorDriverSpiInitRxData,\
    (uint16_t)INIT_REG_COUNT);

	while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
	}

    for(int i = 0; i < TLE92104_All_CTRL_REG_COUNT; i++)
    {
        g_au32MotorDriverSpiInitReadBackTxData[i] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_All_CTRL_REG_SPI_Frame_Table[i]);
    }
    while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
    }
    ret |= TLE92108_SpiSendSync((uint8_t *)&g_au32MotorDriverSpiInitReadBackTxData, (uint8_t *)&g_au32MotorDriverSpiInitReadBackRxData,\
    (uint16_t)TLE92104_All_CTRL_REG_COUNT);
    while (true != Bsp_FCSpi_CheckSendFinish(pTLE92108_Spi_temp)){
    }     

    return ret;

}

FCSPI_StatusType TLE9210x_RegSendAsyncTask(void)
{
    FCSPI_StatusType ret=FCSPI_STATUS_SUCCESS;
	pTLE92108_Spi_temp = Bsp_FCSpi_GetDevice("TLE92108_Spi");

    for(int i = 0; i < TLE92104_Usual_Use_CTRL_Registers_Count; i++)
    {
        g_au32MotorDriverSpiSendTaskTxData[i] = TLE9210X_SPI_Frame_To_Uint32(TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[i]);
    }

    //after set send buffer, set status to read only
    TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_GENSTAT_INDEX].OP = OP_Read_Only_Bit;
    TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_DSOV_INDEX].OP = OP_Read_Only_Bit;

    ret |= TLE92108_SpiSendAsync((uint8_t *)&g_au32MotorDriverSpiSendTaskTxData, (uint8_t *)&g_au32MotorDriverSpiSendTaskRxData,\
    (uint16_t)TLE92104_Usual_Use_CTRL_Registers_Count);

    return ret;

}

