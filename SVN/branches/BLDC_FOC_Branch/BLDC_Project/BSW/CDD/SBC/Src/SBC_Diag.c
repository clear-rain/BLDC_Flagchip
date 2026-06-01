#include "SBC.h"
#include "SBC_Diag.h"
#include "SBC_Cfg.h"
#include "SBC_Types.h"
#include "SBC_Driver.h"
#ifndef ECU_ADDRESS_BLDC
#include "uds_Dem.h"
#endif

extern uint8_t gui8_SbcWk0;
extern uint8_t gui8_SbcWk1;
extern uint8_t gui8_SbcResetReason;
extern uint16_t gau16_SBCSpiRxBuff[];
extern const uint8_t gau8_SBCStatAddrBuf[SBC_STAT_REG_NUM];
static SBC_Reg_t stSBC_StatRegBuff[SBC_STAT_REG_NUM];

#ifndef ECU_ADDRESS_BLDC
static void SBC_InternalFailureDeal(uint8_t u8FaultCode);
#endif
// Function to initialize the SBC diagnostics
void SBC_DiagInit(void)
{
	uint8_t u8_idx = 0;
	for (u8_idx = 0; u8_idx < SBC_STAT_REG_NUM; u8_idx++)
	{
	    stSBC_StatRegBuff[u8_idx].u8Addr = gau8_SBCStatAddrBuf[u8_idx];
		stSBC_StatRegBuff[u8_idx].u8Data = 0x00u;
		stSBC_StatRegBuff[u8_idx].u8OpFlg = 0u;
	}
}

// Function to read diagnostic status
uint8_t SBC_Diag_ReadStatus(void)
{
	uint8_t u8_idx = 0;
	uint8_t status = 0;
	uint8_t ui8_rxData1;
	uint8_t ui8_rxData2;
	static uint8_t sui8_errCnt = 0;
	ui8_rxData1 = (uint8_t)((gau16_SBCSpiRxBuff[0] >> 8) & 0x00FF); // read chip id
	ui8_rxData2 = (uint8_t)((gau16_SBCSpiRxBuff[1] >> 8) & 0x00FF); // read run mode status
#ifndef ECU_ADDRESS_BLDC
	if((SBC_CHIP_TYPE != ui8_rxData1)|| (0x0CU != ui8_rxData2))
	{
		sui8_errCnt++;
	}
	else
	{
		sui8_errCnt = 0;
	}
	if (sui8_errCnt > 3)
	{
		sui8_errCnt = 0;
		SBC_InternalFailureDeal(1); // 诊断失败上报
	}
#endif
	for (u8_idx = 0; u8_idx < SBC_ALL_REG_NUM; u8_idx++)
	{
		if (u8_idx > SBC_STAT_REG_IDX)
		{
			stSBC_StatRegBuff[u8_idx - SBC_STAT_REG_IDX - 1].u8Data = (uint8_t)((gau16_SBCSpiRxBuff[u8_idx] >> 8) & 0x00FF);
		}
		// clear SBC rx buffer
		gau16_SBCSpiRxBuff[u8_idx] = 0x0000u;
	}
	
	for (u8_idx = 0; u8_idx < SBC_ALL_REG_NUM; u8_idx++)
	{
		gau16_SBCSpiRxBuff[u8_idx] = 0x0000u;
	}
	//todo: 对诊断数据进行处理  过温/欠压/过压/短路等
	
	return status;
}

E_CDD_SBC_ERR_STATUS SBC_Diag_ReadChipId(void)
{
	uint8_t u8_idx = 0;
	uint8_t u8RxData;
	for(u8_idx = 0; u8_idx < 3U; u8_idx++) 		
	{
		SBC_ReadRegSync(SBC_FAM_PROD_STATE_ADDR,&u8RxData);
		if(SBC_CHIP_TYPE == u8RxData) 
		{
			return e_CDD_SBC_OK; 
		}
	}
#ifndef ECU_ADDRESS_BLDC
	SBC_InternalFailureDeal(1);
#endif
	return e_CDD_SBC_ERROR; 
}
/**
 * *********************************************************************************************************************
 * Name         : 
 * Description  : 
 * Algorithm    : Void
 * Input        : Void
 * Output       : Void
 * Return       : Void
 * *********************************************************************************************************************
 */
uint8_t Cdd_SbcResetReasonGet(void)
{
	return gui8_SbcResetReason;
}
// Function to clear diagnostic status
void SBC_Diag_ClearStatus(void)
{
	// Code to clear status in SBC
}

// Function to handle diagnostic errors
void SBC_Diag_HandleError(uint8_t errorCode)
{
	// Code to handle errors based on errorCode

}
#ifndef ECU_ADDRESS_BLDC
static void SBC_InternalFailureDeal(uint8_t u8FaultCode)
{
	if(0U == u8FaultCode)
	{
		set_DTC_Exist(DTC_9AE709_PdmSBCInternalFailures,0);
	}
	else{
		set_DTC_Exist(DTC_9AE709_PdmSBCInternalFailures,1);
	}
}
#endif

// Main diagnostic function
void SBC_DiagDeal(void) 
{
	// todo: 增加对控制寄存器的诊断处理
	uint8_t status = SBC_Diag_ReadStatus();

	if (status != 0)
	{
		SBC_Diag_HandleError(status);
		SBC_Diag_ClearStatus();
	}
}

uint8_t Cdd_SbcWkStat0Get(void)
{
	return gui8_SbcWk0;
}

uint8_t Cdd_SbcWkStat1Get(void)
{
	return gui8_SbcWk1;
}
