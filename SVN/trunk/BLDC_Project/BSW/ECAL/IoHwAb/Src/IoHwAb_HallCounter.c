/*
 * IoHwAb_HallCounter.c
 *
 *  Created on: 2026年3月9日
 */

#include "IoHwAb_HallCounter.h"

static struct FtuCounterDriverIf_t *pHallCounterDevBuff = NULL;

void IoHwAb_HallCounter_Init(void)
{
	pHallCounterDevBuff = BSP_HallCounterGetDevice("FTU2");

	DEV_ASSERT(pHallCounterDevBuff != NULL);

	pHallCounterDevBuff->FtuCounterInit(pHallCounterDevBuff);
	pHallCounterDevBuff->FtuCounterTimerStart();
}

void IoHwAb_HallCounter_Start(void)
{
	pHallCounterDevBuff = BSP_HallCounterGetDevice("FTU2");

	DEV_ASSERT(pHallCounterDevBuff != NULL);

	pHallCounterDevBuff->FtuCounterTimerStart();
}

void IoHwAb_HallCounter_Stop(void)
{
	pHallCounterDevBuff = BSP_HallCounterGetDevice("FTU2");

	DEV_ASSERT(pHallCounterDevBuff != NULL);

	pHallCounterDevBuff->FtuCounterTimerStop();
}

uint32_t IoHwAb_HallCounter_GetCnt(void)
{
	pHallCounterDevBuff = BSP_HallCounterGetDevice("FTU2");

	DEV_ASSERT(pHallCounterDevBuff != NULL);

	return pHallCounterDevBuff->FtuCounterGetCnt();
}

void IoHwAb_HallCounter_Clear(void)
{
	pHallCounterDevBuff = BSP_HallCounterGetDevice("FTU2");

	DEV_ASSERT(pHallCounterDevBuff != NULL);

	pHallCounterDevBuff->FtuCounterClearCnt();
}

uint8_t IoHwAb_HallCounter_GetOverflowFlag(void)
{
	return Bsp_Ftu2_GetOverflowFlag();
}

uint8_t IoHwAb_HallCounter_GetOverflowCount(void)
{
	return Bsp_Ftu2_GetOverflowCount();
}

void IoHwAb_HallCounter_ClearOverflowFlag(void)
{
	Bsp_Ftu2_ClearOverflowFlag();
}