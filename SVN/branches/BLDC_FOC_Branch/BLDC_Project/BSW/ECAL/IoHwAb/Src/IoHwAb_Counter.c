/*
 * IoHwAb_Counter.c
 *
 *  Created on: 2024年11月20日
 *      Author: 14013
 */




#include "IoHwAb_Counter.h"
#include "BspFtuCounter.h"
#include "BspGpio.h"

static struct FtuCounterDriverIf_t *pCounterDevBuff = NULL;

void IoHwAb_Counter_Init(void)
{
	pCounterDevBuff = BSP_CounterGetDevice("FTU1");

	DEV_ASSERT(pCounterDevBuff != NULL);

	pCounterDevBuff->FtuCounterInit(pCounterDevBuff);
	pCounterDevBuff->FtuCounterTimerStart();

}

void IoHwAb_Counter_Start(void)
{
	pCounterDevBuff = BSP_CounterGetDevice("FTU1");

	DEV_ASSERT(pCounterDevBuff != NULL);

	pCounterDevBuff->FtuCounterTimerStart();

}

void IoHwAb_Counter_Stop(void)
{
	pCounterDevBuff = BSP_CounterGetDevice("FTU1");

	DEV_ASSERT(pCounterDevBuff != NULL);

	pCounterDevBuff->FtuCounterTimerStop();

}

uint32_t IoHwAb_Counter_GetCnt(void)
{
	pCounterDevBuff = BSP_CounterGetDevice("FTU1");

	DEV_ASSERT(pCounterDevBuff != NULL);

	return pCounterDevBuff->FtuCounterGetCnt();

}

void IoHwAb_Counter_Clear(void)
{
	pCounterDevBuff = BSP_CounterGetDevice("FTU1");

	DEV_ASSERT(pCounterDevBuff != NULL);

	pCounterDevBuff->FtuCounterClearCnt();
}
