/*
 * MotorControl.h
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */

#ifndef BSW_CDD_MOTORDRIVER_INC_MOTORCONTROL_H_
#define BSW_CDD_MOTORDRIVER_INC_MOTORCONTROL_H_

#include "BspSpi.h"
#include "v_def.h"
#include "FreeRTOS.h"
#include "task.h"


typedef enum {
	MOTOR_STOP,
	MOTOR_PRESTART,
	MOTOR_STARTED
} MotorState;
extern MotorState g_eMotorState;

typedef enum {
	MOTOR_NOT_RUNNING,
	MOTOR_RUNNING,
} MotorRunningState;
extern MotorRunningState motor_Running_state;

Std_ReturnType MotorDriver_Init(void);
Std_ReturnType Motor_Enable(boolean bEnable);
uint8 Motor_GetErrorStatus(void);
Std_ReturnType Motor_Start(sint16 s16Duty );
Std_ReturnType Motor_SetDuty(sint16 s16Duty );
Std_ReturnType Motor_Stop(void );
Std_ReturnType Motor_SetPwmFreq(uint32 freq );
Std_ReturnType Motor_TestTask(void);
Std_ReturnType MotorDriver_SleepPrepare(void);
void Motor_MotVoltTask(void);
sint32 Motor_GetMotVolt(void);
sint32 Motor_GetCurmA(void);
sint16 Motor_GetDuty(void);
uint8_t Motor_GetDir(void);
uint8 MotorDriver_Getstopstatus(void);
uint8 MotorDriver_Getovertempstatus(void);
uint8 Motor_GetMotorState(void);

#define MotorDriver_DELAY_1MS (1UL / portTICK_PERIOD_MS)
#define MotorDriver_DELAY_2MS (2UL / portTICK_PERIOD_MS)
#define MotorDriver_DELAY_10MS (10UL / portTICK_PERIOD_MS)
#define MotorDriver_DELAY_100MS (100UL / portTICK_PERIOD_MS)
#define MotorDriver_DelayMs(x,y) vTaskDelayUntil(&(x),y)
#define MotorDriver_SysTickGet() xTaskGetTickCount()

#endif /* BSW_CDD_MOTORDRIVER_INC_MOTORCONTROL_H_ */
