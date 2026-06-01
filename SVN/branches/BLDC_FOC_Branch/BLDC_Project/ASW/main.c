/**
 * @file main.c
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th> Date       <th> Version         <th> Author           <th> Description
 * <tr><td> 2024-09-18 <td> m00.a00.b01     <td> HongChunfeng     <td> 1.Initialization Version
 * </table>
 */

#include "main.h"
#include "BspClock.h"
#include "BspGpio.h"
#include "BspDma.h"
#include "BspInterrupt.h"
#include "IoHwAb_Pwm.h"
#include "IoHwAb_Adc.h"
#include "IoHwAb_Dio.h"
#ifndef ECU_ADDRESS_BLDC
#include "CanSM.h"
#include "AsrNm.h"
#include "NVM.h"
#include "security_hsm.h"
#include "security_log.h"
#include "security_integrityCheck.h"
#include "Mpu.h"
#include "aes128.h"
#include "uds_srv.h"
#include "uds_tpl.h"
#endif
#include "NVM.h"
#include "BspPtimer.h"
#include "com.h"
#include "BspCan.h"
#include "IoHwAb_Counter.h"
#include "BspRtc.h"
#include "motor_api.h"
#include "module_driver_cache.h"

uint32_t SystemCoreClock;

extern void  FreeRTOS_Start(void);
extern boolean txRdy[CANTX_NUM];

int main(void)
{
    FCCACHE_Driver_Enable();
    Bsp_ClockInit();
#ifndef ECU_ADDRESS_BLDC
    Get_WakeupSource();
#endif

    Bsp_GpioOutInit();
    Bsp_GpioInInit();

    Bsp_DmaInit();
    Adc_Init();
    Bsp_Ptimer_Init();
    BSP_CAN_Init();
    Interrupt_Init();
    FCCanGpioInit();

    Bsp_PWM_Init();
    Bsp_DmaStart();
#ifndef ECU_ADDRESS_BLDC
    IoHwAb_Counter_Init();
    IMU_IicInit();
	/*CanSM*/
    CanSM_Init();
	/*AsrNm*/
    AsrNm_Init();
    /*XcpFifoStruct init*/
    XcpFifoStructInit();
    NVM_Init();
    CanTp_Init();
    Dcm_Srv_Init();
    Rte_OTAModeInit();
    Bsp_Mpu_Init();
    Bsp_Hsm_Init(); //interrupt not supported for SHA,RSA,prefer to use polling mode
    securityLog_init();
    SecItgChk_Init();
#else
    NVM_Init();
    IoHwAb_Counter_Init();
    // Cdd_SbcTurnOnVcc2();
    // MotorDriver_Init();
    // Cdd_SbcInit();
//    XcpFifoStructInit();

#endif
    SystemCoreClock = SCG_GetScgClockFreq(SCG_CORE_CLK);
    FreeRTOS_Start();

    while(1);
    return 0;
}

