/*
 * IoHwAb_Adc.c
 *
 *  Created on: 2024年11月1日
 *      Author: 14013
 */

#include "IoHwAb_Adc.h"
#include "IoHwAb_Dio.h"
#include "BspPtimer.h"
#include "BspAdc.h"
#include "Math_Control_Lib.h"
#include "IoHwAb_Counter.h"

uint32_t g_aui32Adc0ConvBuf[ADC0_CHN_NUM_EN] = {0U};
uint32_t g_aui32Adc1ConvBuf[ADC1_CHN_NUM_EN] = {0U};

uint32_t g_aui32Adc0VoltBuf[ADC0_CHN_NUM_EN] = {0U};
uint32_t g_aui32Adc1VoltBuf[ADC1_CHN_NUM_EN] = {0U};

static struct AdcGroupCfg_t *pSysAdcGroupBuff[SYS_ADC_GROUP_NUM] = {NULL,NULL};

void IoHwAb_Adc_ConvDataDeal(void);
void CDD_GetHallVoltTask(void);
uint32 CDD_GetHallVolt(void);


/**
 * @brief
 * @param  pResult
 */
static void ADC0_DmaCallBackHandler(struct _ADC_HandleType *pHandle, const uint32_t *const pBuff)
{
    (void)pHandle;
    (void)pBuff;
}
/**
 * @brief
 * @param  pResult
 */

uint16 g_aCurrentIn50Us[100] = {0};
uint8 g_ui8CurrentArrayIndex = 0;

uint32_t adcTemp[100][2];
uint8_t adcCnt ;

extern void motor_adc_IrqHandler(uint32_t ia, uint32_t ib);
uint32_t adcTemp[100][2];
uint8_t adcCnt ;
static void ADC1_DmaCallBackHandler(struct _ADC_HandleType *pHandle, const uint32_t *const pBuff)
{
    // IoHwAb_Counter_Clear();
    (void) pHandle;
    (void)pBuff;
    //  adcTemp[adcCnt][0] = g_aui32Adc1ConvBuf[0];
    //  adcTemp[adcCnt][1] = g_aui32Adc1ConvBuf[1];

    //  adcCnt++;
    //  adcCnt%=100;

    static uint8 tetttt = 0;
    if(tetttt==0)
    {

    }
    else
    {
    	motor_adc_IrqHandler(g_aui32Adc1ConvBuf[1], g_aui32Adc1ConvBuf[0]);
    }
    tetttt++;
    tetttt%=2;
    // IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 0);

    // IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 1);
    // IoHwAb_Dio_FlipChannel(VBAT_ENCODER_CTRL_IDX);
//	g_aCurrentIn50Us[g_ui8CurrentArrayIndex] = (g_aCurrentIn50Us[g_ui8CurrentArrayIndex]*2+g_aui32Adc1ConvBuf[0]*8)/10;
//	g_ui8CurrentArrayIndex++;
//	g_ui8CurrentArrayIndex%=100;
//    IoHwAb_Dio_FlipChannel(VBAT_HALL_CTRL_IDX);
}

/**
 * @brief  start ADC conversion
 * @param  u8_groupId      0-ADC0   1-ADC1
 */
void Adc_StartGroupConversion(uint8_t u8_groupId)
{
	if (SYS_ADC_GROUP_NUM <= u8_groupId)
	{
		return;
	}
	pSysAdcGroupBuff[u8_groupId]->pf_AdcStart(pSysAdcGroupBuff[u8_groupId]);
}

/**
 * @brief initialize ADC0 and ADC1
 * step1: get the adc device
 * step2: set the adc dma data buffer and callback function
 * step3: initialize the adc
 */
void Adc_Init(void)
{
#ifndef ECU_ADDRESS_BLDC
	pSysAdcGroupBuff[0u] = BSP_AdcGetDevice("Adc0");
	pSysAdcGroupBuff[1u] = BSP_AdcGetDevice("Adc1");


	FCAdcGpioInit();

#else
	FCAdcGpioInit();
	pSysAdcGroupBuff[0u] = BSP_AdcGetDevice("Adc0");
	pSysAdcGroupBuff[1u] = BSP_AdcGetDevice("Adc1");
#endif /*ECU_ADDRESS_BLDC*/
	if(NULL != pSysAdcGroupBuff[0u])
	{
		pSysAdcGroupBuff[0u]->pAdcDmaCfg->bDmaIntEnable = true;
		pSysAdcGroupBuff[0u]->pAdcDmaCfg->pResultBuffer = g_aui32Adc0ConvBuf;
		pSysAdcGroupBuff[0u]->pAdcDmaCfg->pConvCompleteCallback = &ADC0_DmaCallBackHandler;
		pSysAdcGroupBuff[0u]->pf_AdcInit(pSysAdcGroupBuff[0u]);
	}
	if(NULL != pSysAdcGroupBuff[1u])
	{
		pSysAdcGroupBuff[1u]->pAdcDmaCfg->bDmaIntEnable = true;
		pSysAdcGroupBuff[1u]->pAdcDmaCfg->pResultBuffer = g_aui32Adc1ConvBuf;
		pSysAdcGroupBuff[1u]->pAdcDmaCfg->pConvCompleteCallback = &ADC1_DmaCallBackHandler;
		pSysAdcGroupBuff[1u]->pf_AdcInit(pSysAdcGroupBuff[1u]);
		pSysAdcGroupBuff[1u]->pf_AdcStart(pSysAdcGroupBuff[1u]);
	}

}

void IoHwAb_Adc_ConvDataDeal(void)
{
	for(uint8 i = 0;i<ADC0_CHN_NUM_EN;i++)
	{
		g_aui32Adc0VoltBuf[i] = g_aui32Adc0ConvBuf[i] * 5000 / 4096;
	}
	for(uint8 i = 0;i<ADC1_CHN_NUM_EN;i++)
	{
		g_aui32Adc1VoltBuf[i] = g_aui32Adc1ConvBuf[i] * 5000 / 4096;
	}
}


void IoHwAb_Adc_MainFunction(void )// 1ms task
{
	IoHwAb_Adc_ConvDataDeal();
    Adc_StartGroupConversion(ADC_INSTANCE_0);
//    Adc_StartGroupConversion(ADC_INSTANCE_1);
//    Bsp_Ptimer_TriggerStart();
}


#include "Math_Control_Lib.h"

uint32 g_ui32BatVoltage = 0u;
uint32 g_ui32LastBatVoltage = 0u;

uint32 g_ui32HallVoltage = 0u;
uint32 g_ui32LastHallVoltage = 0u;

sint32 g_si32PcbaTemparature = 0;
sint32 g_si32LastPcbaTemparature = 0u;


void IoHwAb_Adc_HallVoltTask(void)
{
	uint32_t Hall_Voltage_ADC = 0u;

	Hall_Voltage_ADC = g_aui32Adc1VoltBuf[Adc1Channel_15_Vbat_Hall]*6;

	Hall_Voltage_ADC = (Hall_Voltage_ADC*50 + g_ui32LastHallVoltage*50)/100;

	if(Hall_Voltage_ADC > 5880 && Hall_Voltage_ADC<16754)
	{
		g_ui32HallVoltage = Lib_Linear_6P_Interpo(Hall_Voltage_ADC, 5880,7947,9840,11936,14839,16754, 6000,8000,10000,12000,15000,17000) + 1500;
	}
	else
	{
		g_ui32HallVoltage = Hall_Voltage_ADC + 1500;
	}
//	g_ui32BatVoltage = g_ui32BatVoltage + 50u;//调节偏差

	g_ui32LastHallVoltage = Hall_Voltage_ADC;
}

uint32 CDD_GetHallVolt(void)
{
	return g_ui32HallVoltage;
}


void IoHwAb_Adc_BatmVoltTask(void)
{
	uint32_t MCU_Voltage_ADC = 0u;

	MCU_Voltage_ADC = g_aui32Adc0VoltBuf[Adc0Channel_10_K30]*6;

	MCU_Voltage_ADC = (MCU_Voltage_ADC*50 + g_ui32LastBatVoltage*50)/100;

	if(MCU_Voltage_ADC<14064)
	{
		g_ui32BatVoltage = Lib_Linear_6P_Interpo(MCU_Voltage_ADC,5268,6195,8168,10122,12089,14064	, 6000,7000,9000,11000,13000,15000);
	}
	else if(MCU_Voltage_ADC<22050)
	{
		g_ui32BatVoltage = Lib_Linear_6P_Interpo(MCU_Voltage_ADC,14085,16075,18060,20052,22049,22050, 15000,17000,19000,21000,23000,23001);
	}
	else
	{
		g_ui32BatVoltage = Lib_Linear_6P_Interpo(MCU_Voltage_ADC,22050,23064,24063,25116,26097,27092, 23000,24000,25000,26000,27000,28000);
	}
//	g_ui32BatVoltage = g_ui32BatVoltage + 50u;//调节偏差

	g_ui32LastBatVoltage = MCU_Voltage_ADC;
}

uint32 CDD_GetBatmVolt(void)
{
	return g_ui32BatVoltage;
}

void IoHwAb_Adc_PCBATempCTask(void)
{
	uint32_t MCU_Temparature_ADC = 0u;


	MCU_Temparature_ADC = (g_aui32Adc1VoltBuf[Adc1Channel_13_Temp] * 50 + g_si32LastPcbaTemparature * 50)/100;

	if(MCU_Temparature_ADC<=3346)
	{
		g_si32PcbaTemparature = Lib_Linear_6P_Interpo(MCU_Temparature_ADC, 266, 425, 670, 1375,2483,3346,
																			  -400, -300, -200, 0, 200, 400);
	}
	else
	{
		g_si32PcbaTemparature = Lib_Linear_4P_Interpo(MCU_Temparature_ADC, 3346, 3960, 4360, 4490, 400, 600, 800, 900);
	}
	g_si32LastPcbaTemparature = MCU_Temparature_ADC;
}

sint32 CDD_GetPCBATempC(void)
{
	return g_si32PcbaTemparature;
}

