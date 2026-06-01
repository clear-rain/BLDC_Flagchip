/*
 * MotorControl.c
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */
#include "MotorControl.h"
#include "MotorDriver_Driver.h"
#include "MotorDriver_Cfg.h"
#include "IoHwAb_Dio.h"
#include "BspFtuPwm.h"
#include "IoHwAb_Adc.h"
#include "IoHwAb_Pwm.h"


#define FTU_SpindleMotor_channel 0
typedef uint8 en_MotorDir;
#define MOTORDIR_INVALID                    ((en_MotorDir)0U)         /* Default value */
#define MOTORDIR_EXTEND                     ((en_MotorDir)1U)        /*CW*/
#define MOTORDIR_RETRACT                    ((en_MotorDir)2U)       /*CCW*/
#define USEC(clk, us)					((uint32_t)(clk) * (uint32_t)(us) / 1000000u)
#define MSEC(clk, ms)					((uint32_t)(clk) * (uint32_t)(ms) / 1000u)

;
MotorRunningState motor_Running_state = MOTOR_NOT_RUNNING;



Std_ReturnType MotorDriver_Init(void)
{
    Std_ReturnType Status = (Std_ReturnType)E_OK;
    MotorDriver_SpiInit();
    MotorDriver_RegInitSync();
    return Status;
}


Std_ReturnType Motor_Mainfunction(void)
{
	Std_ReturnType Status = (Std_ReturnType)E_OK;



	return Status;
}

//
//extern uint16 g_ui32PtimerCntMax;
//extern uint16 g_ui16PtimerCntNow;
//extern uint8 g_ui8PtimerCntAdd;
//Std_ReturnType Motor_SetPwmFreq(uint32 freq )
//{
//	FCSPI_StatusType SetStatus = 0u;
//	if(freq < 16000)
//	{
//		freq = 16000;
//	}
//	else if(freq > 25000)
//	{
//		freq = 25000;
//	}
////	uint16 l_ui16PtimerUsMax = 1000000 / freq;
////	g_ui32PtimerCntMax = l_ui16PtimerUsMax *100 /8;
//	g_ui32PtimerCntMax = 1000000 * 100 / freq / 8;
//	g_ui8PtimerCntAdd = g_ui32PtimerCntMax / 50;
//
//
//	uint64_t target_us_plus_1k = 1000000 * 1000 / freq;
//	period_us_plus_1k = target_us_plus_1k;
//	uint32_t target_modcnt = (uint32_t)USEC(25000, target_us_plus_1k);
//
//
//	struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
////	FTU_PwmUpdatePeriod(pPwmDevBuff, target_modcnt);
//	pPwmDevBuff->FtuPwmPeriodSet(pPwmDevBuff, target_modcnt);
////	Motor_Running_Status = Motor_SetDuty(motor_duty);
//
//	return E_OK;
//}
//Std_ReturnType Motor_Mainfunction(void);
//Std_ReturnType Motor_Mainfunction(void)
//{
//    if(get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 0)==0 &&\
//    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 1)==0 &&\
//    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 2)==0 &&\
//    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 3)==0 &&\
//     g_eMotorState!=MOTOR_PRESTART)
//	{
//		//motor stop
//		motor_Running_state = MOTOR_NOT_RUNNING;
//		g_eMotorState = MOTOR_STOP;
//		MotorDir = MOTORDIR_INVALID;
//
//	}
//    if((get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 0) != 0 || get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 1) != 0 ||\
//    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 2) != 0 ||get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 3) != 0 )  &&\
//    g_eMotorState != MOTOR_STOP && \
//    motor_Running_state == MOTOR_RUNNING)
//    {
//		MotorDriver_Offline_diag_exit_flag = 0;
//		g_eMotorState = MOTOR_STARTED;
//
//        if(g_si16MotorDuty > 0)
//		{
//            struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
//            pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff,FTU_SpindleMotor_channel, g_si16MotorDuty);
//            MotorDir = MOTORDIR_EXTEND;
//        }
//        else if(g_si16MotorDuty < 0)
//        {
//            struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
//            pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff,FTU_SpindleMotor_channel, -g_si16MotorDuty);
//            MotorDir = MOTORDIR_RETRACT;
//        }
//        else{
//            struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
//            pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff,FTU_SpindleMotor_channel, 0);
//            MotorDir = MOTORDIR_INVALID;
//        }
//    }
//
//    return E_OK;
//
//}


 Std_ReturnType Motor_Task(void)
 {
     Std_ReturnType Status = (Std_ReturnType)E_OK;
#ifndef ECU_ADDRESS_BLDC
     if(!g_bMotorEnable)
     {
         return Status;
     }
//     Status |= MotorDriver_GetAllResponse();
//     Motor_GainCheck();
    Status |= Motor_Mainfunction();

    Status |= MotorDriver_Offline_diag();
    Status |= MotorDriver_Online_diag();
    Motor_DTC_Task();
    MotorDriver_Current_diag();
    Status |= MotorDriver_MotorErrorSet();

	if(g_ui8StopSPI)
	{
		return Status;
	}
	Status |= TLE9210x_RegSendAsyncTask();
#else
//	Bsp_PWM_DutySet(e_PWM_INA_IDX, 750);
//	Bsp_PWM_DutySet(e_PWM_INB_IDX, 1500);
//	Bsp_PWM_DutySet(e_PWM_INC_IDX, 2250);
#endif
	return Status;
 }

