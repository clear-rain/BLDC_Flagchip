/*
 * IoHwAb_Pwm.c
 *
 *  Created on: 2024年11月4日
 *      Author: 14013
 */


#include "IoHwAb_Pwm.h"
#include "BspFtuPwm.h"
#include "BspGpio.h"

static struct FtuPwmDriverIf_t *pPwmDevBuff = NULL;

void Bsp_PWM_Init(void)
{
	uint8_t u8_idx = 0u;
	pPwmDevBuff = BSP_PwmGetDevice("FTU0");

	DEV_ASSERT(pPwmDevBuff != NULL);

	for(u8_idx = 0u; u8_idx < e_PWM_NUM_MAX; u8_idx++)
	{
		pPwmDevBuff->GPIO_Init(u8_idx);
	}

	pPwmDevBuff->FtuPwmInit(pPwmDevBuff);
	pPwmDevBuff->FtuPwmTimerStart();
//		 pPwmDevBuff[u8_idx]->FtuPwmTimerStop(pPwmDevBuff[u8_idx]);
//	for(u8_idx = 0u; u8_idx < e_PWM_NUM_MAX; u8_idx++)
//	{
//		pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff, u8_idx, 0U);
//	}
	pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff, 0, 0U);
	pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff, 1, 0U);
	pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff, 2, 0U);
}


void Bsp_PWM_DutySet(uint8_t channel, uint16 duty)
{
	if(duty >= 3000)
	{
		duty = 3000;
	}
//	pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff, channel, duty);
	Bsp_Ftu_SetDuty(channel, duty);
}


