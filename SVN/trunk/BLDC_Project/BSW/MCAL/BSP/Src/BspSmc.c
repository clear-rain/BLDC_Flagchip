/*
 * BspSmc.c
 *
 *  Created on: 2024年12月6日
 *      Author: 14013
 */

#include "BspSmc.h"


void Bsp_SmcEnterStop(void)
{
    SMC_SetSystemMode(SMC_MODE_STOP);
}

void Bsp_SmcEnterWait(void)
{
    SMC_SetSystemMode(SMC_MODE_WAIT);
}

void Bsp_SmcEnterStandby0(void)
{
    SMC_SetSystemMode(SMC_MODE_STANBY_0);
}

void Bsp_SmcEnterStandby1(void)
{
    SMC_SetSystemMode(SMC_MODE_STANBY_1);
}

void Bsp_SmcEnterStandby2(void)
{
    SMC_SetSystemMode(SMC_MODE_STANBY_2);
}

void Bsp_SmcEnterStandby3(void)
{
    SMC_SetSystemMode(SMC_MODE_STANBY_3);
}

void Bsp_SetWakeupSource(void)
{
    WKU_EnableWakeupSource((uint32_t)WKU_INPUT_GPIOA);    /* set wakeup source is GPIOA interrupt */
    WKU_EnableWakeupSource((uint32_t)WKU_INPUT_GPIOE);
    WKU_EnableWakeupSource((uint32_t)WKU_INPUT_GPIOC);
//    WKU_EnableWakeupSource((uint32_t)WKU_INPUT_GPIOD);

}



