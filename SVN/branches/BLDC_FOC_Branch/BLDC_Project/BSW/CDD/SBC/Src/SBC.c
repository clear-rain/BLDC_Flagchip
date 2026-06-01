/**
 * @file SBC.c
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-19 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */

#include "SBC_Cfg.h"
#include "SBC_Driver.h"
#include "SBC_Types.h"
#include "SBC_Diag.h"
#include "SBC.h"

extern uint16_t g_ui16WdgCount;
extern E_CDD_SBC_MODE g_eSBC_RunMode;

void Cdd_SbcWdg_SetTriggerCondition(uint16_t timeout)
{
    g_ui16WdgCount = timeout;
}

 void Cdd_SbcInit(void)
{
	SBC_DiagInit();

	SBC_AllRegsInitSync();
}


 void Cdd_SbcMainFunction(void)
{
	Cdd_SbcWdg_SetTriggerCondition(1000);//todo: should be called by other module

	SBC_NormalRun();	// normal run mode logic

	SBC_StopRun();		// stop run mode logic

	SBC_SleepRun();		// Sleep run mode logic

	SBC_RestartModeRun();	// restart SBC and reset MCU
}
