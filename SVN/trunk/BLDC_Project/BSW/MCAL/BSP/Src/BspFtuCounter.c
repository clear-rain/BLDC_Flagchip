/*
 * BspFtuCounter.c
 *
 *  Created on: 2024年11月20日
 *      Author: 14013
 */



#include "BspFtuCounter.h"
#include "BspGpio.h"
#include "IoHwAb_Dio.h"
#include "string.h"

#ifndef ECU_ADDRESS_BLDC
#include "hall.h"
#endif

#define USEC(clk, us)					((uint32_t)(clk) / 1000000u * (uint32_t)(us))
#define MSEC(clk, ms)					((uint32_t)(clk) / 1000u * (uint32_t)(ms))

FTU_HandleType	g_tFtuCounterHandle;

static FTU_Type * const s_pFtuBasePtrs[FTU_INSTANCE_COUNT] = FTU_BASE_PTRS;
#ifndef ECU_ADDRESS_BLDC
extern sint32 g_ui32LastHallPulsePeriod;
extern uint8 g_ui8HallInterruptOpened;
extern uint8 g_ui8HallRotateDir;
void Bsp_FTU_OverflowCallback(FTU_HandleType *pHandle);
#endif
struct FtuCounterDriverIf_t * BSP_CounterGetDevice(char *name);

void Bsp_FTU1_OverflowCallback(FTU_HandleType *pHandle)
{
	(void)pHandle;
//	__NVIC_DisableIRQ(FTU1_IRQn);
//	IoHwAb_Dio_FlipChannel(VBAT_ENCODER_CTRL_IDX);
//	g_ui32LastHallPulsePeriod = 0;
//	g_ui8HallInterruptOpened = 0;
//	g_ui8HallRotateDir = 0;
}

static FtuCounterPrivateData_t st_Ftu1PrivateDataBuf =
{
		.eInstance = FTU_INSTANCE_1,
		.eClkSrc = FTU_PCC_CLK,
		.ePrescaler = FTU_DIV_2,
		.pOverflowCallback = Bsp_FTU1_OverflowCallback,
		.u32InterruptMask = FTU_INTR_MASK_OVERFLOW,

		.u32InitialValue = 0,
		.u32CounterValue = 8000,
};

static void Bsp_Ftu1_Init(struct FtuCounterDriverIf_t *pDev)
{
	FTU_CommonType 			tInitConfig;
	FTU_CounterModeType 	tCounterConfig;
	FTU_GetDefaultInitCfg(&tInitConfig);
	tInitConfig.eClkSrc = pDev->ftuPriData->eClkSrc;
	tInitConfig.ePrescaler =  pDev->ftuPriData->ePrescaler;

	tInitConfig.u32InterruptMask = pDev->ftuPriData->u32InterruptMask;
	tInitConfig.pOverflowCallback = pDev->ftuPriData->pOverflowCallback;

	g_tFtuCounterHandle.eInstance = pDev->ftuPriData->eInstance;
	//FTU_DeInit(EXAMPLE_FTU_INSTANCE);
	FTU_CommonInit(&g_tFtuCounterHandle, &tInitConfig);

	tCounterConfig.u32InitialValue = pDev->ftuPriData->u32InitialValue;
	tCounterConfig.u32CounterValue = pDev->ftuPriData->u32CounterValue;
	FTU_CounterModeInit(&g_tFtuCounterHandle, &tCounterConfig);

}

static void Bsp_Ftu1_Start(void)
{
    FTU_StartTimer(&g_tFtuCounterHandle);
}

static void Bsp_Ftu1_Stop(void)
{
	FTU_StopTimer(&g_tFtuCounterHandle);
}

static uint32_t Bsp_Ftu1_GetCounter(void)
{
	return FTU_GetCounter(&g_tFtuCounterHandle);
}

static void Bsp_Ftu1_Clear_Cnt(void)
{
	FTU_Type * const pFtu = s_pFtuBasePtrs[g_tFtuCounterHandle.eInstance];
	FTU_HWA_ClearModuleCounter(pFtu, (uint32_t)0x1U);

}

void Bsp_Ftu1_GpioInit(uint8_t u8_ChannelIdx)
{
	(void)u8_ChannelIdx;
}

static struct FtuCounterDriverIf_t st_FtuCounterDriverBuff=
{
	.name = "FTU1",
	.ftuPriData = &st_Ftu1PrivateDataBuf,
	.GPIO_Init = Bsp_Ftu1_GpioInit,
	.FtuCounterInit = Bsp_Ftu1_Init,
	.FtuCounterTimerStart = Bsp_Ftu1_Start,
	.FtuCounterTimerStop = Bsp_Ftu1_Stop,
	.FtuCounterGetCnt = Bsp_Ftu1_GetCounter,
	.FtuCounterClearCnt = Bsp_Ftu1_Clear_Cnt
};

struct FtuCounterDriverIf_t * BSP_CounterGetDevice(char *name)
{
	(void)name;
	return &st_FtuCounterDriverBuff;
}

void Bsp_FtuCounter_DeInit(void)
{
	FTU_StopTimer(&g_tFtuCounterHandle);
	FTU_DeInit(&g_tFtuCounterHandle);
}
