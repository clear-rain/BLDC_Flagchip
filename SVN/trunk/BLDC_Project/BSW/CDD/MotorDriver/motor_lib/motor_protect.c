#include "motor_protect.h"
#include "motor_foc.h"

uint16_t over_current_mon_a = 0, over_current_mon_b = 0, over_current_mon_c = 0;
extern MotorFocStruct motor_foc_struct;

void exception_led() { set_led2(); }
inline void current_exception(void)
{
    motor_pwm_out_disabled();
    motor_foc_struct.motor_ctrl_param.foc_status = MOTOR_STATUS_OFF;
    exception_led();
}
