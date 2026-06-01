/*
 * MotorControl.c
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */
#include "MotorControl.h"
#include "MotorDriver_Diag.h"
#include "MotorDriver_Driver.h"
#include "MotorDriver_Cfg.h"
#include "IoHwAb_Dio.h"
#include "Hall.h"
#include "BspFtuPwm.h"
#include "IoHwAb_Adc.h"
#include "IoHwAb_Pwm.h"
#include "uds_Dem.h"


#define FTU_SpindleMotor_channel 0
typedef uint8 en_MotorDir;
#define MOTORDIR_INVALID                    ((en_MotorDir)0U)         /* Default value */
#define MOTORDIR_EXTEND                     ((en_MotorDir)1U)        /*CW*/
#define MOTORDIR_RETRACT                    ((en_MotorDir)2U)       /*CCW*/
#define USEC(clk, us)					((uint32_t)(clk) * (uint32_t)(us) / 1000000u)
#define MSEC(clk, ms)					((uint32_t)(clk) * (uint32_t)(ms) / 1000u)

static boolean  g_bMotorEnable = FALSE;
uint8 g_ui8StopSPI = 0;
uint8 g_ui8Motor_Inited = 0;
extern MotorErrorStatus_t  g_unMotorErrorStatus;
MotorState g_eMotorState = MOTOR_STOP;
extern MotorDriver_Offline_Diag_error g_unMotorDriverOfflineDiagErrorCode;
extern TLE92104_FaultIndicator_t  g_unFaultIndicator ;
extern HallErrorStatus_t HallErrorStatus;
MotorRunningState motor_Running_state = MOTOR_NOT_RUNNING;
sint16 g_si16MotorDuty = 0;
int gain = 20;
uint8  MotorDir = MOTORDIR_INVALID;
extern uint8  MotorDriver_Offline_diag_exit_flag;


Std_ReturnType MotorDriver_Init(void)
{
    Std_ReturnType Status = (Std_ReturnType)E_OK;
    static uint16_t delay_counter = 0;

    TLE92108_SpiInit();

	IoHwAb_Dio_WriteChannel(DRV_EN_IDX, 0);
	for(delay_counter = 0;delay_counter < 800;delay_counter++){
		static  int i = 0;
		i++;
	}
	IoHwAb_Dio_WriteChannel(DRV_EN_IDX, 1);
	for(delay_counter = 0;delay_counter < 800;delay_counter++){
		static  int i = 0;
		i++;
	}

    Status |= TLE9210x_RegInitSync();
	g_ui8Motor_Inited = 1;
    return Status;
}
Std_ReturnType Motor_Enable(boolean bEnable);
Std_ReturnType Motor_Enable(boolean bEnable)
{
	g_bMotorEnable = bEnable;
	return E_OK;
}

uint8 Motor_GetErrorStatus(void);
uint8 Motor_GetErrorStatus(void)
{
	return g_unMotorErrorStatus.byte;
}

Std_ReturnType Motor_Start(sint16 s16Duty );
Std_ReturnType Motor_Start(sint16 s16Duty )
{
    Std_ReturnType Status = (Std_ReturnType)E_OK;
    if(!g_bMotorEnable){
    	return E_NOK;
    }
	if(g_eMotorState != MOTOR_STOP)
	{
		return E_NOK;
	}
	if(g_unMotorDriverOfflineDiagErrorCode.bits.motoropenload_error||\
			g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2gnd_error||\
			g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2vcc_error||\
			HallErrorStatus.bits.shortCircuitFailure)
	{
		return E_NOK;
	}

    if(s16Duty > 1000)
    {
        s16Duty = 1000;
    }
    else if(s16Duty < -1000)
    {
        s16Duty = -1000;
    }

	g_si16MotorDuty = s16Duty;
	g_eMotorState = MOTOR_PRESTART;

    return Status;
}

Std_ReturnType Motor_SetDuty(sint16 s16Duty );
Std_ReturnType Motor_SetDuty(sint16 s16Duty )
{
	Std_ReturnType Status = (Std_ReturnType)E_OK;
    if(!g_bMotorEnable){
    	return E_NOK;
    }
	if(g_eMotorState != MOTOR_STARTED){
		return E_NOK;
	}

	motor_Running_state = MOTOR_RUNNING;
    if(s16Duty > 1000)
    {
        s16Duty = 1000;
    }
    else if(s16Duty < -1000)
    {
        s16Duty = -1000;
    }

    g_si16MotorDuty = s16Duty;//used for frequency updating

    if(s16Duty > 0)
    {
    	TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].data = 0x06;
    }
    else
    {
		/* when Duty==0 , should keep LSx and HSy on to keep the started state*/

   	 	TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].data = 0x09;
    }
    return Status;
}

Std_ReturnType Motor_Stop(void );
Std_ReturnType Motor_Stop(void )
{
	Std_ReturnType Status = (Std_ReturnType)E_OK;
    if(!g_bMotorEnable){
    	return E_NOK;
    }
	if(g_eMotorState != MOTOR_STARTED){
		return E_NOK;
	}

	struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
	pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff, FTU_SpindleMotor_channel, 0);

//	motor_Running_state = MOTOR_NOT_RUNNING;
//	g_eMotorState = MOTOR_STOP;
//	MotorDir = MOTORDIR_INVALID;
	g_si16MotorDuty = 0;

//    SET_TLE9210X_SPI_FRAME(message, 0x00, OP_Read_And_WriteOrClear_Bit, HBMODE_ADDR,LABT_Bit, MSB_Bit);
//    g_au32MotorDriverSpiSendTaskTxData[Usual_Use_CTRL_HBMODE_INDEX] = message;
    TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].data = 0x00;
    TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].OP = OP_Read_And_WriteOrClear_Bit;

    /*MOTOR_STARTED ; duty ==0 ; wait for close gate driver*/
    return Status;
}

extern uint16 g_ui32PtimerCntMax;
extern uint16 g_ui16PtimerCntNow;
extern uint8 g_ui8PtimerCntAdd;
Std_ReturnType Motor_SetPwmFreq(uint32 freq );
Std_ReturnType Motor_SetPwmFreq(uint32 freq )
{
	FCSPI_StatusType SetStatus = 0u;
	if(freq < 16000)
	{
		freq = 16000;
	}
	else if(freq > 25000)
	{
		freq = 25000;
	}
//	uint16 l_ui16PtimerUsMax = 1000000 / freq;
//	g_ui32PtimerCntMax = l_ui16PtimerUsMax *100 /8;
	g_ui32PtimerCntMax = 1000000 * 100 / freq / 8;
	g_ui8PtimerCntAdd = g_ui32PtimerCntMax / 50;


	uint64_t target_us_plus_1k = 1000000 * 1000 / freq;
	period_us_plus_1k = target_us_plus_1k;
	uint32_t target_modcnt = (uint32_t)USEC(25000, target_us_plus_1k);


	struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
//	FTU_PwmUpdatePeriod(pPwmDevBuff, target_modcnt);
	pPwmDevBuff->FtuPwmPeriodSet(pPwmDevBuff, target_modcnt);
//	Motor_Running_Status = Motor_SetDuty(motor_duty);

	return E_OK;
}
Std_ReturnType Motor_Mainfunction(void);
Std_ReturnType Motor_Mainfunction(void)
{
    if(get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 0)==0 &&\
    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 1)==0 &&\
    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 2)==0 &&\
    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 3)==0 &&\
     g_eMotorState!=MOTOR_PRESTART)
	{
		//motor stop
		motor_Running_state = MOTOR_NOT_RUNNING;
		g_eMotorState = MOTOR_STOP;
		MotorDir = MOTORDIR_INVALID;
	
	}
    if((get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 0) != 0 || get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 1) != 0 ||\
    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 2) != 0 ||get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 3) != 0 )  &&\
    g_eMotorState != MOTOR_STOP && \
    motor_Running_state == MOTOR_RUNNING)
    {
		MotorDriver_Offline_diag_exit_flag = 0;
		g_eMotorState = MOTOR_STARTED;

        if(g_si16MotorDuty > 0)
		{
            struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
            pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff,FTU_SpindleMotor_channel, g_si16MotorDuty);
            MotorDir = MOTORDIR_EXTEND;
        }
        else if(g_si16MotorDuty < 0)
        {
            struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
            pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff,FTU_SpindleMotor_channel, -g_si16MotorDuty);
            MotorDir = MOTORDIR_RETRACT;
        }
        else{
            struct FtuPwmDriverIf_t *pPwmDevBuff = BSP_PwmGetDevice("FTU0");
            pPwmDevBuff->FtuPwmDutySet(pPwmDevBuff,FTU_SpindleMotor_channel, 0);
            MotorDir = MOTORDIR_INVALID;
        }
    }

    return E_OK;

}

extern uint16 g_aCurrentIn50Us[100];
sint32 g_si32MotorCurrent = 0;
sint32 Motor_CurrentCaculate(void);
sint32 Motor_CurrentCaculate(void){

	sint32 current_temp = 0;

	uint32 volttemp = 0;
	for(uint8 i = 0;i<100;i++)
	{
		volttemp += g_aCurrentIn50Us[i];
	}

//	uint32 volt = (volttemp/100)* 5000 / 4096;
	uint32 volt = volttemp* 50 / 4096;

	if(volt>=2500)
	{
		current_temp = (sint32)((volt - 2500) * 200 / gain);//5mO : /gain*1000/5=*200/gain
	}
	else{
		current_temp = (sint32)(-((2500 - volt) * 200 / gain));
	}

	g_si32MotorCurrent = current_temp;


	return g_si32MotorCurrent;
}


sint32 Motor_GetCurmA(void)
{
	return Motor_CurrentCaculate();
}

sint16 Motor_GetDuty(void)
{
	return g_si16MotorDuty;
}

uint8_t Motor_GetDir(void)
{
	return MotorDir;
}

sint32 Motor_MotVolt = 0;

void Motor_MotVoltTask(void)
{
	uint32_t Adc0VoltBuf_23_temp = g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE];
	uint32_t Adc1VoltBuf_24_temp = g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE];
	if(Adc0VoltBuf_23_temp > Adc1VoltBuf_24_temp)
	{
		Motor_MotVolt = (Adc0VoltBuf_23_temp-Adc1VoltBuf_24_temp)*448/100;
	}
	else if(Adc1VoltBuf_24_temp > Adc0VoltBuf_23_temp)
	{
		Motor_MotVolt = (Adc1VoltBuf_24_temp-Adc0VoltBuf_23_temp)*448/100;
		Motor_MotVolt = -Motor_MotVolt;
	}
	else
	{
		Motor_MotVolt = 0;
	}

}

sint32 Motor_GetMotVolt(void)
{
	return Motor_MotVolt;
}
sint32 temp_current = 0;
void MotorDriver_Current_diag(void)
{
	static uint8 OverCurrent_cnt = 0;
	temp_current = Motor_CurrentCaculate();
	if(temp_current>30000 || temp_current<-30000)//to be define
	{
		if(OverCurrent_cnt < 20)
		{
			OverCurrent_cnt++;
		}
	}
	else
	{
		OverCurrent_cnt = 0;
	}

	if(OverCurrent_cnt == 20)
	{
		g_unMotorErrorStatus.bits.MotorOverCurrentFailure = 1;
		Motor_Stop();
	}
	else
	{
		g_unMotorErrorStatus.bits.MotorOverCurrentFailure = 0;
	}
}
void Motor_DTC_Task(void);
void Motor_DTC_Task(void)
{
	if(g_unMotorErrorStatus.bits.MotorOpenCircuitFailure == 1)
	{
		set_DTC_Exist(DTC_9AE013_PdmPowerDoorMotoOpenCircuitFailure,1);
	}
	else
	{
		set_DTC_Exist(DTC_9AE013_PdmPowerDoorMotoOpenCircuitFailure,0);
	}
	if(g_unMotorErrorStatus.bits.MotorOverCurrentFailure == 1)
	{
		set_DTC_Exist(DTC_9AE019_PdmPowerDoorMotorOverCurrentFailure,1);
	}
	else
	{
		set_DTC_Exist(DTC_9AE019_PdmPowerDoorMotorOverCurrentFailure,0);
	}
	if(g_unMotorErrorStatus.bits.MotorShortCircuitFailure == 1)
	{
		set_DTC_Exist(DTC_9AE001_PdmPowerDoorMotorShortCircuitFailure,1);
	}
	else
	{
		set_DTC_Exist(DTC_9AE001_PdmPowerDoorMotorShortCircuitFailure,0);
	}
	if(g_unMotorErrorStatus.bits.MotorDriverChipFailure == 1)
	{
		set_DTC_Exist(DTC_9AE509_PdmMotorDriverChipInternalFailure,1);
	}
	else
	{
		set_DTC_Exist(DTC_9AE509_PdmMotorDriverChipInternalFailure,0);
	}
}

 Std_ReturnType Motor_Task(void)
 {
     Std_ReturnType Status = (Std_ReturnType)E_OK;
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
	return Status;
 }

 Std_ReturnType MotorDriver_SleepPrepare(void)
 {
 	Std_ReturnType Status = (Std_ReturnType)E_OK;
 	TickType_t xNextWakeTime;
	IoHwAb_Dio_WriteChannel(DRV_EN_IDX,DIO_STD_LOW);
 	Status |= Motor_Stop();
 	xNextWakeTime = MotorDriver_SysTickGet();
 	g_ui8StopSPI = 1;
 	MotorDriver_DelayMs(xNextWakeTime, MotorDriver_DELAY_10MS);
 	MotorDriver_DelayMs(xNextWakeTime, MotorDriver_DELAY_10MS);
 	return Status;
 }

uint8 MotorDriver_Getstopstatus(void)
{
	if(MOTOR_STOP == g_eMotorState)return 1;
	else{
		return 0;
	}
}
uint8 MotorDriver_Getovertempstatus(void)
{
	if(g_unFaultIndicator.bits.Thermal_Shutdown)return 1;
	else{
		return 0;
	}
}

uint8 Motor_GetMotorState(void)
{
	return g_eMotorState;
}

