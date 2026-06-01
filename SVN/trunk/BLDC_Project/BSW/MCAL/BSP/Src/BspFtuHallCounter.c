/*
 * BspFtuHallCounter.c
 *
 *  Created on: 2026年3月9日
 */

#include "BspFtuHallCounter.h"

FTU_HandleType g_tFtuHallCounterHandle;
static volatile uint8_t s_ftu2_overflow_count = 0U;

static FTU_Type * const s_pFtuBasePtrs[FTU_INSTANCE_COUNT] = FTU_BASE_PTRS;

static void Bsp_FTU2_OverflowCallback(FTU_HandleType *pHandle)
{
	(void)pHandle;
	if (s_ftu2_overflow_count < 0xFFu)
	{
		s_ftu2_overflow_count++;
	}
}

static FtuCounterPrivateData_t st_Ftu2PrivateDataBuf =
{
		.eInstance = FTU_INSTANCE_2,
		.eClkSrc = FTU_PCC_CLK,
		.ePrescaler = FTU_DIV_32,
		.pOverflowCallback = Bsp_FTU2_OverflowCallback,
		.u32InterruptMask = FTU_INTR_MASK_OVERFLOW,

		.u32InitialValue = 0,
		.u32CounterValue = BSP_FTU2_COUNTER_PERIOD_TICKS,
};

static void Bsp_Ftu2_Init(struct FtuCounterDriverIf_t *pDev)
{
	FTU_CommonType tInitConfig;
	FTU_CounterModeType tCounterConfig;

	s_ftu2_overflow_count = 0U;
	FTU_GetDefaultInitCfg(&tInitConfig);
	tInitConfig.eClkSrc = pDev->ftuPriData->eClkSrc;
	tInitConfig.ePrescaler = pDev->ftuPriData->ePrescaler;
	tInitConfig.u32InterruptMask = pDev->ftuPriData->u32InterruptMask;
	tInitConfig.pOverflowCallback = pDev->ftuPriData->pOverflowCallback;

	g_tFtuHallCounterHandle.eInstance = pDev->ftuPriData->eInstance;
	FTU_CommonInit(&g_tFtuHallCounterHandle, &tInitConfig);

	tCounterConfig.u32InitialValue = pDev->ftuPriData->u32InitialValue;
	tCounterConfig.u32CounterValue = pDev->ftuPriData->u32CounterValue;
	FTU_CounterModeInit(&g_tFtuHallCounterHandle, &tCounterConfig);
}

static void Bsp_Ftu2_Start(void)
{
	FTU_StartTimer(&g_tFtuHallCounterHandle);
}

static void Bsp_Ftu2_Stop(void)
{
	FTU_StopTimer(&g_tFtuHallCounterHandle);
}

static uint32_t Bsp_Ftu2_GetCounter(void)
{
	return FTU_GetCounter(&g_tFtuHallCounterHandle);
}

static void Bsp_Ftu2_Clear_Cnt(void)
{
	FTU_Type * const pFtu = s_pFtuBasePtrs[g_tFtuHallCounterHandle.eInstance];
	s_ftu2_overflow_count = 0U;
	FTU_HWA_ClearModuleCounter(pFtu, (uint32_t)0x1U);
}

uint8_t Bsp_Ftu2_GetOverflowFlag(void)
{
	return (uint8_t)(s_ftu2_overflow_count != 0U);
	}

uint8_t Bsp_Ftu2_GetOverflowCount(void)
{
	return s_ftu2_overflow_count;
}

void Bsp_Ftu2_ClearOverflowFlag(void)
{
	s_ftu2_overflow_count = 0U;
}

static void Bsp_Ftu2_GpioInit(uint8_t u8_ChannelIdx)
{
	(void)u8_ChannelIdx;
}

static struct FtuCounterDriverIf_t st_FtuHallCounterDriverBuff =
{
	.name = "FTU2",
	.ftuPriData = &st_Ftu2PrivateDataBuf,
	.GPIO_Init = Bsp_Ftu2_GpioInit,
	.FtuCounterInit = Bsp_Ftu2_Init,
	.FtuCounterTimerStart = Bsp_Ftu2_Start,
	.FtuCounterTimerStop = Bsp_Ftu2_Stop,
	.FtuCounterGetCnt = Bsp_Ftu2_GetCounter,
	.FtuCounterClearCnt = Bsp_Ftu2_Clear_Cnt
};

struct FtuCounterDriverIf_t * BSP_HallCounterGetDevice(char *name)
{
	(void)name;
	return &st_FtuHallCounterDriverBuff;
}

void Bsp_FtuHallCounter_DeInit(void)
{
	FTU_StopTimer(&g_tFtuHallCounterHandle);
	FTU_DeInit(&g_tFtuHallCounterHandle);
}