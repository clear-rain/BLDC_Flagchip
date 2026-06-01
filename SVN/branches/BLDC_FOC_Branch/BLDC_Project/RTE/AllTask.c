/**
 * @file AllTask.c
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-13 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */

/* Kernel includes. */
// #include "GpioPort.h"
#include "FreeRTOS.h"
#include "task.h"
#include "IoHwAb_Dio.h"
// #include "WdgM.h"
// #include "com.h"
 #include "NvM.h"
#include "SBC.h"
#include "IoHwAb_Pwm.h"
#include "IoHwAb_Adc.h"
#include "BspFtuPwm.h"
#include "BspWdg.h"
#include "motor_foc.h"
#include "APP.h"

#ifndef ECU_ADDRESS_BLDC
#include "CanSM.h"
#include "AsrNm.h"
#include "uds_tpl.h"
#include "uds_srv.h"
#include "uds_cbk.h"
#include "PowerMode.h"
#include "uds_Dem.h"
#include "Hall.h"
#include "security_hsm.h"
#include "security_log.h"
#include "security_integrityCheck.h"
#include "Mpu.h"
#endif
#include "MotorControl.h"
#include "MotorDriver_Driver.h"
#include "motor_api.h"
#include "motor_config.h"
#include "IMU.h"
#include "SEGGER_SYSVIEW.h"
#include "BspCan.h"
#include "Spindle_Control.h"
#include "motor_encoder.h"

#include "../BSW/CompatibleInfo/CompatibleInfo.h"

/* Priorities at which the tasks are created. */
#define BSWTask_1ms_PRIORITY (tskIDLE_PRIORITY + 5)
#define BSWTask_2ms_PRIORITY (tskIDLE_PRIORITY + 4)
#define BSWTask_5ms_PRIORITY (tskIDLE_PRIORITY + 10)
#define BSWTask_10ms_PRIORITY (tskIDLE_PRIORITY + 10)

#define ASWTask_1ms_PRIORITY (tskIDLE_PRIORITY + 10)
#define ASWTask_5ms_PRIORITY (tskIDLE_PRIORITY + 8)
#define ASWTask_10ms_PRIORITY (tskIDLE_PRIORITY + 7)

#define ASWTask_100ms_PRIORITY (tskIDLE_PRIORITY + 1)

/* The rate at which data is sent to the queue, specified in milliseconds, and
converted to ticks using the portTICK_PERIOD_MS constant. */
#define TASK_DELAY_1MS (1UL / portTICK_PERIOD_MS)
#define TASK_DELAY_2MS (2UL / portTICK_PERIOD_MS)
#define TASK_DELAY_3MS (3UL / portTICK_PERIOD_MS)
#define TASK_DELAY_5MS (5UL / portTICK_PERIOD_MS)
#define TASK_DELAY_10MS (10UL / portTICK_PERIOD_MS)
#define TASK_DELAY_50MS (50UL / portTICK_PERIOD_MS)
#define TASK_DELAY_100MS (100UL / portTICK_PERIOD_MS)

/* A block time of zero simply means "don't block". */
#define mainDONT_BLOCK (0UL)

/*
 * The tasks as described in the comments at the top of this file.
 */
static void BSWTask_1ms(void *pvParameters);
static void BSWTask_2ms(void *pvParameters);
static void BSWTask_5ms(void *pvParameters);
static void BSWTask_10ms(void *pvParameters);

static void ASWTask_1ms(void *pvParameters);
static void ASWTask_5ms(void *pvParameters);
static void ASWTask_10ms(void *pvParameters);

static void ASWTask_100ms(void *pvParameters);

void FreeRTOS_Start(void);
void vApplicationMallocFailedHook(void);
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTasName);
void vApplicationIdleHook(void);
void vApplicationTickHook(void);
void Com_MainFunction(void);
void IoHwAb_Adc_MainFunction(void );
void CDD_GetBatmVoltTask(void);
void CDD_GetPCBATempCTask(void);
void Xcp_MainFunction(void);



void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    volatile size_t xFreeHeapSpace;

    /* This function is called on each cycle of the idle task.  In this case it
    does nothing useful, other than report the amount of FreeRTOS heap that
    remains unallocated. */
    xFreeHeapSpace = xPortGetFreeHeapSize();

    if( xFreeHeapSpace > 100 )
    {
        /* By now, the kernel has allocated everything it is going to, so
        if there is a lot of heap remaining unallocated then
        the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
        reduced accordingly. */
    }

}

/* A tick hook is used by the "Full" build configuration.  The Full and blinky
build configurations share a FreeRTOSConfig.h header file, so this simple build
configuration also has to define a tick hook - even though it does not actually
use it for anything. */
void vApplicationTickHook( void ) {}

/* The queue used by both tasks. */
void FreeRTOS_Start(void)
{
    //todo: move it to power manager logic
//    Dio_WriteChannel(e_IO_450M5_EN_IDX,DIO_STD_HIGH);
    SEGGER_SYSVIEW_Conf();

    xTaskCreate( BSWTask_1ms, "BSWTask_1ms", configMINIMAL_STACK_SIZE, NULL, BSWTask_1ms_PRIORITY, NULL);
    xTaskCreate( BSWTask_2ms, "BSWTask_2ms", configMINIMAL_STACK_SIZE, NULL, BSWTask_2ms_PRIORITY, NULL);
    xTaskCreate( BSWTask_5ms, "BSWTask_5ms", 600, NULL, BSWTask_5ms_PRIORITY, NULL);
    xTaskCreate( BSWTask_10ms,"BSWTask_10ms",configMINIMAL_STACK_SIZE, NULL, BSWTask_10ms_PRIORITY,NULL);

    xTaskCreate( ASWTask_1ms, "ASWTask_1ms", configMINIMAL_STACK_SIZE, NULL, ASWTask_1ms_PRIORITY, NULL);
    xTaskCreate( ASWTask_5ms, "ASWTask_5ms", configMINIMAL_STACK_SIZE, NULL, ASWTask_5ms_PRIORITY, NULL);
    xTaskCreate( ASWTask_10ms,"ASWTask_10ms",configMINIMAL_STACK_SIZE, NULL, ASWTask_10ms_PRIORITY,NULL);

    xTaskCreate( ASWTask_100ms, "ASWTask_100ms", configMINIMAL_STACK_SIZE, NULL, ASWTask_100ms_PRIORITY, NULL);

    vTaskStartScheduler();
}

static void BSWTask_1ms( void *pvParameters )
{
    TickType_t xNextWakeTime;
    (void)pvParameters;
    Motor_Encoder_LoadOffsetFromNvM();
    xNextWakeTime = xTaskGetTickCount();
    // Wdg_Init();
    vTaskDelayUntil( &xNextWakeTime, TASK_DELAY_3MS);
    for( ;; )
    {
        vTaskDelayUntil( &xNextWakeTime, TASK_DELAY_1MS);
//        XcpEventTransmit_1ms();
        IoHwAb_Adc_MainFunction();
        Motor_FocCtrl();

//        Motor_TestTask();

#ifndef ECU_ADDRESS_BLDC
        CanTP_checkL_Fifo();
		Inc_Random_Seed();
		E2E_TimeoutCheck_1ms();
#endif
//		CanRxTimeOutCheckOut_1ms();

//        Wdg_MainFunction();
    }
}

static void BSWTask_2ms( void *pvParameters )
{
    TickType_t xNextWakeTime;
    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        vTaskDelayUntil(&xNextWakeTime, TASK_DELAY_2MS);
    }
}

static void BSWTask_5ms(void *pvParameters)
{
    TickType_t xNextWakeTime;
    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;
    xNextWakeTime = xTaskGetTickCount();
    vTaskDelayUntil(&xNextWakeTime, TASK_DELAY_5MS);

//    TLE92108_Init();
//    Motor_Start(-300);
    /* Initialise xNextWakeTime - this only needs to be done once. */
    vTaskDelayUntil(&xNextWakeTime, TASK_DELAY_5MS);
#ifndef ECU_ADDRESS_BLDC
    Hall_Init();
    Dcm_ErrorCntReadNvminit();
#endif
    xNextWakeTime = xTaskGetTickCount();
    for( ;; )
    {
    	vTaskDelayUntil( &xNextWakeTime, TASK_DELAY_5MS);
#ifndef ECU_ADDRESS_BLDC
		NVM_MainFunction();
		Hall_SpeedCaculateTask();
		CanTP_Uds_Tpl_Task();
		Dcm_Srv_Task();
		Rte_UpdateOTAMode();
		Dcm_DIDReadNvmInit();
		Dcm_ErrorCntWirteNvm();
		Dcm_CheckDtcFinish();
		DTC_MainFunction();
#else
		NVM_MainFunction();
#endif

//	    IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 0);
		Com_MainFunction();
//	    IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 1);
    }
}

static void BSWTask_10ms(void *pvParameters)
{
    TickType_t xNextWakeTime;
    (void)pvParameters;

    Cdd_SbcTurnOnVcc2();
    MotorDriver_Init();
#ifndef ECU_ADDRESS_BLDC

    Motor_Enable(1);
    Motor_SetPwmFreq(20000);
#endif
//    Bsp_PWM_Init();


    Cdd_SbcInit();
#ifndef ECU_ADDRESS_BLDC
    GetWakeupSource_SBC();
#endif
    Cdd_ImuInit();
    xNextWakeTime = xTaskGetTickCount();
    for( ;; )
    {
        vTaskDelayUntil(&xNextWakeTime, TASK_DELAY_10MS);
        Cdd_SbcMainFunction();
#ifndef ECU_ADDRESS_BLDC
        Cdd_ImuMainFunctionAsilB_10ms();
		Cdd_ImuMainFunctionQm_5ms();
#else
//        Cdd_ImuMainFunction();
#endif
//        IoHwAb_Adc_HallVoltTask();
//        IoHwAb_Adc_BatmVoltTask();
//        IoHwAb_Adc_PCBATempCTask();





#ifndef ECU_ADDRESS_BLDC
		Dcm_27_delay();
		Motor_MotVoltTask();
		Hsm_mainFunction(10);
//       
		/*HALL error detect task */
		HALL_Safety_Task();
		Hall_DTC_Task();


#else
		//MotorDriver_RegSendAsyncTask();
#endif
    }
}

static void ASWTask_1ms(void *pvParameters)
{
    TickType_t xNextWakeTime;
    (void)pvParameters;

    xNextWakeTime = xTaskGetTickCount();
    for( ;; )
    {
        vTaskDelayUntil( &xNextWakeTime, TASK_DELAY_1MS);
//    	Xcp_MainFunction();
        extern void Motor_Encoder_StrokeUpdate_1msTask(void);
        Motor_Encoder_StrokeUpdate_1msTask();
    }
    
}

static void ASWTask_5ms( void *pvParameters )
{
    TickType_t xNextWakeTime;
    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;
    
    Spindle_Control_Init();
    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();


    for (;;)
    {
        vTaskDelayUntil( &xNextWakeTime, TASK_DELAY_5MS );
#ifndef ECU_ADDRESS_BLDC
    	CanSM_MainFunction();
    	AsrNm_MainFunction();
#endif
#if 0
        APP_5ms();
        Spindle_Control_Task_5ms();
        #else
        // CONTROL BY DRIVER Test
        #define CONTROL_DRIVER_TEST
        #endif
//        GetCanRxTimeOutResult_100ms();
//        XcpEvent(0);
    }
}
static void ASWTask_10ms( void *pvParameters )
{
    TickType_t xNextWakeTime;
    /* Casting pvParameters to void because it is unused */
    (void)pvParameters;

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for(;;)
    {
        vTaskDelayUntil(&xNextWakeTime, TASK_DELAY_10MS);
	}
}

extern  sint32 NvMEncoderStroke[2];
volatile uint8_t debugStartFlag = 0;
static uint8_t timer0=0;
static void ASWTask_100ms( void *pvParameters)
{
    TickType_t xNextWakeTime;
    (void)pvParameters;
    // static uint8_t ui8_studyFlag = 0;

    xNextWakeTime = xTaskGetTickCount();
#ifndef ECU_ADDRESS_BLDC
    Uds_CBK_GenerateRandomSeed();
#endif
    for(;;)
    {
        vTaskDelayUntil(&xNextWakeTime, TASK_DELAY_100MS); // todo: this time should be 1s rather than 50ms


        #ifdef CONTROL_DRIVER_TEST
        if(timer0<=100){
        	timer0 ++;
        }
        if(timer0 == 20 && debugStartFlag !=2){

        	MotorAPI_ModeSet(MOTOR_CTRL_MODE_SPEED);
        	MotorAPI_SpeedSetRPM(SPEED_SET);;
        	(void)MotorAPI_StatusSet(true);
        }

        if(timer0 >= 100 && debugStartFlag !=2){

        	MotorSpeedTest();
        }
        else if(debugStartFlag == 2)        {
            //Stop
            if (MotorAPI_StatusGet())
            {
                (void)MotorAPI_StatusSet(false);
            }
        }

        #endif
#if 0
        	if (!MotorAPI_StatusGet())
            {
                // 速度环
                MotorAPI_ModeSet(MOTOR_CTRL_MODE_SPEED);
//                MotorAPI_SpeedSetRPM(SPEED_SET);
//        	   (void)MotorAPI_StatusSet(true);

                // // 电流环
                // MotorAPI_ModeSet(MOTOR_CTRL_MODE_CURRENT);
                // MotorAPI_CurrentSetDQ(0.0f, 0.3f);
                // (void)MotorAPI_StatusSet(true);

                // // 固定电压输出
                // MotorAPI_ModeSet(MOTOR_CTRL_MODE_VOLTAGE);
                // MotorAPI_VoltageSetDQ(0.0f, 0.5f);
                // (void)MotorAPI_StatusSet(true);

            }
#endif


    }
}



