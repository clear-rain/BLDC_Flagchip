#include "BspGpio.h"
#include "BspSpi.h"
#include "SBC_Cfg.h"
#include "SBC_Types.h"
#include "SBC_Driver.h"

static struct SpiDriverIf_t *pSBC_Spi;
static uint8_t *pui8_TxData = NULL;
static uint8_t *pui8_RxData = NULL;	
static uint16_t sui16_DataLen = 0u;

const SBC_Reg_t gtSBC_CtrlRegBuff[SBC_CTRL_REG_NUM] = {
	{.u8Addr = SBC_M_S_CTRL_ADDR, .u8Data = 0x0C, .u8OpFlg = 1},
	{.u8Addr = SBC_HW_CTRL_0_ADDR, .u8Data = 0x04, .u8OpFlg = 1},
	{.u8Addr = SBC_FAM_PROD_STATE_ADDR, .u8Data = 0x00, .u8OpFlg = 0}, // and also for watchdog
	{.u8Addr = SBC_BUS_CTRL_0_ADDR, .u8Data = 0x03, .u8OpFlg = 1},	   // Normal CAN
	{.u8Addr = SBC_WK_CTRL_0_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_WK_CTRL_1_ADDR, .u8Data = 0x00, .u8OpFlg = 1},
	{.u8Addr = SBC_WK_PUPD_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_BUS_CTRL_3_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_TIMER_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_HW_CTRL_1_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_HW_CTRL_2_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_GPIO_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_PWM_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_PWM_FREQ_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_HW_CTRL_3_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SYS_STAT_CTRL_0_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SYS_STAT_CTRL_1_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
};

const SBC_Reg_t gtSBC_SwkCtrlRegBuff[SBC_SWK_CTRL_REG_NUM] = {
	{.u8Addr = SBC_SWK_CTRL_ADDR, .u8Data = 0x60, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_BTL0_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_BTL1_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_ID3_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID3, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_ID2_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID2, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_ID1_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID1, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_ID0_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID0, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_MASK_ID3_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID_MASK3, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_MASK_ID2_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID_MASK2, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_MASK_ID1_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID_MASK1, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_MASK_ID0_CTRL_ADDR, .u8Data = SBC_SWK_CAN_ID_MASK0, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_DLC_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DLC, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA7_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA7, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA6_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA6, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA5_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA5, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA4_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA4, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA3_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA3, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA2_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA2, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA1_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA1, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_DATA0_CTRL_ADDR, .u8Data = SBC_SWK_CAN_DATA0, .u8OpFlg = 1},
	{.u8Addr = SBC_SWK_CAN_FD_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
};

const SBC_Reg_t gtSBC_SwkTrimCtrlRegBuff[SBC_SWK_TRIM_CTRL_REG_NUM] = {
	{.u8Addr = SBC_SWK_OSC_TRIM_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_OPT_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_OSC_CAL_H_STAT_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_OSC_CAL_L_STAT_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_CDR_CTRL_1_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_CDR_CTRL_2_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_CDR_LIMIT_HIGH_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
	{.u8Addr = SBC_SWK_CDR_LIMIT_LOW_CTRL_ADDR, .u8Data = 0x00, .u8OpFlg = 0},
};
const uint8_t gau8_SBCStatAddrBuf[SBC_STAT_REG_NUM] =
	{
		SBC_SUP_STAT_1_ADDR,
		SBC_SUP_STAT_0_ADDR,
		SBC_TRIM_STAT_ADDR,
		SBC_DEV_STAT_ADDR,
		SBC_BUS_STAT_ADDR,
		SBC_WK_STAT_0_ADDR,
		SBC_WK_STAT_1_ADDR,
		SBC_WK_LVL_STAT_ADDR,
		SBC_GPIO_OC_STAT_ADDR,
		SBC_GPIO_OL_STAT_ADDR,
};

void SBC_SpiInit(void)
{
	pSBC_Spi = Bsp_FCSpi_GetDevice("SBC_Spi");
	if (NULL != pSBC_Spi)
	{
		pSBC_Spi->spiPriData->pStopNotifyCb = Cdd_SbcSpiCompleteCallback;
		pSBC_Spi->GPIO_Init(pSBC_Spi->spiPriData->eInstance);
		pSBC_Spi->SpiInit(pSBC_Spi);
	}
}
void SBC_SpiSendSync(uint8_t *pTxData, uint8_t *pRxData, uint16_t u16Len)
{
	if (NULL != pSBC_Spi)
	{
		pSBC_Spi->TransmitSync(pSBC_Spi, pTxData, pRxData, u16Len, 100);
	}
}

void SBC_SpiSendDataSetEB(uint8_t *pTxData, uint8_t *pRxData, uint16_t u16Len)
{
	pui8_TxData = pTxData;
	pui8_RxData = pRxData;	
	sui16_DataLen = u16Len;
}

void SBC_SpiSendDataSeqAsync(void)
{
	if (NULL != pSBC_Spi)
	{
		pSBC_Spi->TransmitAsync(pSBC_Spi, pui8_TxData, pui8_RxData, sui16_DataLen);
	}
}
void SBC_WriteRegSync(uint8_t u8Addr, uint8_t u8Data)
{
	uint8_t au8TxData[2] = {0};
	uint8_t au8RxData[2] = {0};

	au8TxData[0] = u8Addr | 0x80;
	au8TxData[1] = u8Data;

	SBC_SpiSendSync(au8TxData, au8RxData, 1);
}

void SBC_ReadRegSync(uint8_t u8Addr, uint8_t *pu8Data)
{
	uint8_t au8TxData[2] = {0};
	uint8_t au8RxData[2] = {0};

	au8TxData[0] = u8Addr;
	au8TxData[1] = 0;

	SBC_SpiSendSync(au8TxData, au8RxData, 1);
	*pu8Data = au8RxData[1];
}
