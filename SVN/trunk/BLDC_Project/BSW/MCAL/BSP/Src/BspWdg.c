/*
 * BspWdg.c
 *
 *  Created on: 2024年11月21日
 *      Author: 14013
 */



#include "BspWdg.h"

WDOG_HandleType g_tWdogHandle;

void WDOG0_IRQHandler_Callback(WDOG_HandleType *pHandle);
void Wdg_MainFunction(void);

void WDOG0_IRQHandler_Callback(WDOG_HandleType *pHandle)
{
    PROCESS_UNUSED_VAR(pHandle);
    (RCM->SRIE) += 1U;
}

void Bsp_WDOG_Init(void)
{
    WDOG_CfgType Wdog_InitStruct = {0};

    Wdog_InitStruct.bWinEnable = true;
    /* 256 pre-scaler enable */
    Wdog_InitStruct.bPrescalerEnable = true;
    /* set WDOG source as BUS_CLK, current value is 25 000 000 Hz  */
    Wdog_InitStruct.eClkSource = WDOG_BUS_CLK;
#if WDOG_RESET_DELAY_SUPPORT
    Wdog_InitStruct.bInterruptEnable = true;
    Wdog_InitStruct.eTimeoutReaction = WDOG_REACTION_INT_1024_CYCLE;
#else
    Wdog_InitStruct.bInterruptEnable = true;
#endif
    Wdog_InitStruct.bEnable = true;
    Wdog_InitStruct.eTesttype = WDOG_TST_DISABLED;
    Wdog_InitStruct.bEnableInDebug = false;
    Wdog_InitStruct.bEnableInWait = false;
    Wdog_InitStruct.bEnableInStop = false;

    /*25 000 000 Hz / 256 = 97,656.25 Hz*/
    /*97,656.25 * 0.07 = 6836 */
    Wdog_InitStruct.u16WindowValue = 6836U;
    /*97,656.25 * 0.12 = 11718.75  */
    Wdog_InitStruct.u16TimeoutValue = 11719;

    g_tWdogHandle.eIntance = WDOG_INSTANCE_0;
    /* set the IRQ callback function */
    g_tWdogHandle.tSettings.pISRCallback = WDOG0_IRQHandler_Callback;

    WDOG_Init(&g_tWdogHandle, &Wdog_InitStruct);
}

void Bsp_WDOG_DeInit(void)
{
	WDOG_DeInit(&g_tWdogHandle);
}


void Bsp_WDOG_Refresh(void)
{
    WDOG_Refresh(&g_tWdogHandle);
}

uint8 Wdg_started = 0;
uint8 Wdg_cnt = 0;

void Wdg_MainFunction(void)
{
	if(!Wdg_started)
	{
		Bsp_WDOG_Init();
		Wdg_started = 1;
	}
	else
	{
		if(Wdg_cnt == 99)
		{
			DISABLE_INTERRUPTS();
            Bsp_WDOG_Refresh();
            ENABLE_INTERRUPTS();
		}
		Wdg_cnt++;
		Wdg_cnt%=100;
	}
}
