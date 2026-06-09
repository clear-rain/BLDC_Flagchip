#include "motor_adc.h"
#include "motor_foc.h"
#include "motor_current.h"
#include "motor_voltage_injection_inductance.h"

extern MotorCurrent motor_current_0, motor_current_0_before;
extern MotorCurrentOffset motor_current_offset_0;
extern MotorFocStruct motor_foc_struct;
extern uint8 Lmtest;

#if MOTOR_DEBUG_CAPTURE
volatile uint16_t testIProducerCnt = 0;
volatile float testArrayIa[MOTOR_DEBUG_CAPTURE_LEN];
volatile float testArrayIb[MOTOR_DEBUG_CAPTURE_LEN];
#endif
void motor_adc_IrqHandler(uint32_t ia, uint32_t ib)
{
    motor_current_0_before.ia = ia;//U
    motor_current_0_before.ib = ib;//V


    static uint8_t flag1 =0;
    if (!Motor_IsDoneCalCurrentOffset(motor_current_offset_0))
    {
        Motor_CalCurrentOffset(&motor_current_offset_0, &motor_current_0_before);
    }
    else
    {
        motor_current_0.ia = (motor_current_0_before.ia - motor_current_offset_0.ia_offset_raw) * CURRENT_ADC_SCALE;
        motor_current_0.ib = (motor_current_0_before.ib - motor_current_offset_0.ib_offset_raw) * CURRENT_ADC_SCALE;

//        flag1++;
//        flag1 %= 100;
//        if(flag1 == 0){
        if(Lmtest==1)
        {
        	SynInitPosDetect();
        }
        else
        {
        	Motor_FocRunning(&motor_current_0, &motor_foc_struct);
        }

//        }

        // TEST 当前监控频率跟不上实际采样频率   需要通过存储采样值来解决
#if MOTOR_DEBUG_CAPTURE
        if (testIProducerCnt < MOTOR_DEBUG_CAPTURE_LEN)
        {
            testArrayIa[testIProducerCnt] = motor_current_0.ia;
            testArrayIb[testIProducerCnt] = motor_current_0.ib;
            testIProducerCnt++;
        }
#endif
    }
}
