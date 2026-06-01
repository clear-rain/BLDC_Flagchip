// 仅保留初始化逻辑，legacy 运行/停止接口已废弃
#include "motor_app.h"
#include "motor_current.h"
#include "motor_foc.h"

#define CURRENT_OFFSET_SAMPLE_COUNT 128

MotorCurrent motor_current_0, motor_current_0_before;
MotorCurrentOffset motor_current_offset_0;
volatile MotorFocStruct motor_foc_struct;

static MotorParam motor_param = {
    .vdc = 12,
    .resis = PHASE_RESISTANCE,
    .induc = PHASE_INDUCTANCE,
    .bemf = MOTOR_BEMF_CONST,
    .bemf_phase_rad = MOTOR_BEMF_PHASE_RAD,
    .pole_pairs = NUM_POLE_PAIRS,
    .pwm_freq = PWM_FREQUENCY,
};

static MotorPid pid_speed = {
    .kp = PI_SP_CURRENT_P,
    .ki = PI_SP_CURRENT_I,
    .kd = PI_SP_CURRENT_D,
    .out_max = PI_SP_CURRENT_MAX,
    .out_min = -PI_SP_CURRENT_MAX,
};

static MotorPid pid_id = {
    .kp = PI_D_CURRENT_P,
    .ki = PI_D_CURRENT_I,
    .kd = PI_D_CURRENT_D,
    .out_max = PI_D_CURRENT_MAX,
    .out_min = -PI_D_CURRENT_MAX,
};

static MotorPid pid_iq = {
    .kp = PI_Q_CURRENT_P,
    .ki = PI_Q_CURRENT_I,
    .kd = PI_Q_CURRENT_D,
    .out_max = PI_Q_CURRENT_MAX,
    .out_min = -PI_Q_CURRENT_MAX,
};

static MotorOpenloopParam openloop_param = {
    .pre_pos_en = true,
    .pre_pos[0] =
        {
            .time_max = 2000,
            .angle = (M_PI * 1.5),
            .daxis = 6.0f,
            .qaxis = 0,
        },
    .pre_pos[1] =
        {
            .time_max = 4000,
            .angle = 0,
            .daxis = 6.0f,
            .qaxis = 0,
        },

    .openloop_time_max = OPEN_LOOP_TIME_IN_SEC,
    .openloop_qaxis_max = OPEN_LOOP_CURRENT_REF,
    .openloop_angle_speed_max = OPEN_LOOP_END_RPM,
    .openloop_pwm_freq = PWM_FREQUENCY,
    .task_freq = TASK_FREQUENCY,
};

static MotorSmoPllParam motor_smo_pll_param = {
    .k_pll = KFILTER_VELESTIM,
    .pll_pi_p = PI_PLL_P,
    .pll_pi_i = PI_PLL_I,
};

static MotorSmoEsoPllParam motor_smo_eso_pll_param = {
    .k_smo = K_SMO,
    .k_pll = KFILTER_VELESTIM,
};

static MotorNolineFluxPllParam motor_flux_pll_param = {
    .gama = GAMMA,
    .k_pll = KFILTER_VELESTIM,
    .pll_pi_p = PI_NONLINEAR_P,
    .pll_pi_i = PI_NONLINEAR_I,
};

static const MotorEstimatorParam motor_estimator_param = {
    .type = MOTOR_ESTIMATOR_TYPE,
    .smo_pll_param = &motor_smo_pll_param,
    .smo_eso_pll_param = &motor_smo_eso_pll_param,
    .nonlineflux_pll_param = &motor_flux_pll_param,
};

void Motor_Init(void)
{
    motor_foc_struct.motor_param = motor_param;

    Motor_InitCurrentOffset(&motor_current_offset_0, CURRENT_OFFSET_SAMPLE_COUNT);

    Motor_FocInit(&motor_foc_struct, &motor_estimator_param);
    Motor_ParamInit(&motor_foc_struct.motor_param);
    Motor_OpenloopInit(&motor_foc_struct.motor_openloop,
                       &motor_foc_struct.motor_openloopcurrent,
                       openloop_param);
    Motor_FocPidInit(&motor_foc_struct, pid_speed, pid_id, pid_iq);
    Motor_CtrlInit(&motor_foc_struct.motor_ctrl_param);
    Motor_SvpwmInit(&motor_foc_struct.motor_svpwm, MAX_PERIOD);

    Motor_SetSpeed(0);
}
