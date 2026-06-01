#ifndef MOTOR_LIB_MOTOR_CONFIG_H_
#define MOTOR_LIB_MOTOR_CONFIG_H_

#include "motor_math.h"

#define ENABLE_RTT 0

/* Debug capture buffers (waveform sampling)
 * - 1: enable testArray/testCnt/testView debug buffers
 * - 0: compile out all related code/data
 */
#ifndef MOTOR_DEBUG_CAPTURE
#define MOTOR_DEBUG_CAPTURE 0
#endif

#ifndef MOTOR_DEBUG_CAPTURE_LEN
#define MOTOR_DEBUG_CAPTURE_LEN 1000U
#endif

#ifndef ENABLED_BLDC
//#define  MOTOR_SENSOR_TYPE                  SENSOR_HALL
// #define MOTOR_SENSOR_TYPE SENSOR_SENSORLESS
//#define  PIT_HALL_SAMPLE
#endif

// #define HongQi
// #define MOTOR_57BL95S15
// #define GEELY_MOTOR
#define MOTOR_57BL55S06

#define CURRENT_OFFSET_SAMPLE_COUNT 128
#define CURRENT_ADC_SCALE (float)(5000 / (float)(4096) / 25.56 /3)

#define MAIN_CLOCK_HZ (120000000UL)
#define TIMER_PRESCALER (2UL)
#define PWM_FREQUENCY (20000UL)
#define TASK_FREQUENCY (1000UL)
#define MAX_PERIOD (MAIN_CLOCK_HZ / TIMER_PRESCALER / PWM_FREQUENCY)
#define PWM_PERIOD_TIME_SEC (float)(1 / (float)PWM_FREQUENCY)
#define MAX_PERIOD_LIMIT ((float)MAX_PERIOD * 0.02)
#define PWM_START_DELAY (float)((((1.0f / PWM_FREQUENCY) * 1000.0f * 1000.0f) / 3.0f) / (1.0f / 150.0f))

//57BL115S21-230TF8
#ifdef MOTOR_57BL115S21
#ifdef ENABLED_BLDC
#define BLDC_RAMPUP_TIME_IN_MS 800
#define BLDC_RAMPUP_PWM_MAX (((float)MAX_PERIOD * 16.0f) / 32.0f)
#endif
#define HALL_ANGLE_OFFSET_1 (30.0f / 360.0f) * (2.0f * M_PI)
#define HALL_ANGLE_OFFSET_2 (30.0f / 360.0f) * (2.0f * M_PI)
#define PHASE_INDUCTANCE ((float)0.000289f)
#define PHASE_RESISTANCE ((float)0.245f)
#define NUM_POLE_PAIRS ((float)2.0f)
#define MOTOR_BEMF_CONST ((float)3.62) //((float)3.62)    //((float)7.24)
#define RATED_SPEED_RPM ((float)3000)
#define MAX_MOTOR_CURRENT ((float)4)
#define OPEN_LOOP_END_RPM (180)
#define OPEN_LOOP_TIME_IN_SEC (float)(0.2)
#define OPEN_LOOP_CURRENT_REF ((float)1.0)
//57BL115S21-230TF8
#endif

//----------------------------------------------------------------------------
//57BL55S06-230TF9
#ifdef MOTOR_57BL55S06
#ifdef ENABLED_BLDC
#define BLDC_RAMPUP_TIME_IN_MS 10
#define BLDC_RAMPUP_PWM_MAX (((float)MAX_PERIOD * 20.0f) / 32.0f)
#endif

#define HALL_ANGLE_OFFSET_1 (5.0f / 360.0f) * (2.0f * M_PI)
#define HALL_ANGLE_OFFSET_2 (55.0f / 360.0f) * (2.0f * M_PI)

//#define PHASE_INDUCTANCE ((float)0.001f)
//#define PHASE_RESISTANCE ((float)0.59f)


#define PHASE_INDUCTANCE ((float)0.0015f)
#define PHASE_RESISTANCE ((float)0.4f)
#define NUM_POLE_PAIRS ((float)2.0f)
#define MOTOR_BEMF_CONST  (4.6f)//((float)3.62)    //
#define RATED_SPEED_RPM ((float)4000)
#define MAX_MOTOR_CURRENT ((float)3.3)
#define OPEN_LOOP_END_RPM (300)             //300
#define OPEN_LOOP_TIME_IN_SEC (float)(0.8f) //0.1
#define OPEN_LOOP_CURRENT_REF ((float)0.8f) //0.8
//57BL55S06-230TF9
#endif
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//57BL95S15-230TF9
#ifdef MOTOR_57BL95S15
#define HALL_ANGLE_OFFSET_1 (20.0f / 360.0f) * (2.0f * M_PI)
#define HALL_ANGLE_OFFSET_2 (55.0f / 360.0f) * (2.0f * M_PI)
#define PHASE_INDUCTANCE ((float)0.001f)
#define PHASE_RESISTANCE ((float)0.59f)
#define NUM_POLE_PAIRS ((float)2.0f)
#define MOTOR_BEMF_CONST ((float)3.62) //((float)3.62)    //((float)7.24)
#define RATED_SPEED_RPM ((float)3000)
#define MAX_MOTOR_CURRENT ((float)8.7)
#define OPEN_LOOP_END_RPM (300)             //300
#define OPEN_LOOP_TIME_IN_SEC (float)(0.1f) //0.1
#define OPEN_LOOP_CURRENT_REF ((float)0.2f) //0.8
#endif


//GEELY_MOTOR
#ifdef GEELY_MOTOR
#define ENCODER_ELEC_ANGLE_OFFSET (-0.168f * M_PI)
#define HALL_ANGLE_OFFSET_1  (-0.26f * M_PI)
#define HALL_ANGLE_OFFSET_2 (55.0f / 360.0f) * (2.0f * M_PI)
#define PHASE_INDUCTANCE ((float)0.001f)
#define PHASE_RESISTANCE ((float)0.59f)
#define NUM_POLE_PAIRS ((float)3.0f)
#define MOTOR_BEMF_CONST ((float)3.62) //((float)3.62)    //((float)7.24)
#define RATED_SPEED_RPM ((float)3000)
#define MAX_MOTOR_CURRENT ((float)20.0)
#define OPEN_LOOP_END_RPM (100)             //300
#define OPEN_LOOP_TIME_IN_SEC (float)(0.1f) //0.1
#define OPEN_LOOP_CURRENT_REF ((float)0.8f) //0.8
#endif



//57BL95S15-230TF9
//----------------------------------------------------------------------------

#ifdef HongQi
#define HALL_ANGLE_OFFSET_1 (20.0f / 360.0f) * (2.0f * M_PI)
#define HALL_ANGLE_OFFSET_2 (55.0f / 360.0f) * (2.0f * M_PI)
#define PHASE_INDUCTANCE ((float)0.0348f)
#define PHASE_RESISTANCE ((float)0.12f)
#define NUM_POLE_PAIRS ((float)3.0f)
#define MOTOR_BEMF_CONST ((float)3.33) //((float)3.62)    //((float)7.24)
#define RATED_SPEED_RPM ((float)5000)
#define MAX_MOTOR_CURRENT ((float)8.7)
#define OPEN_LOOP_END_RPM (300)             //300
#define OPEN_LOOP_TIME_IN_SEC (float)(0.1f) //0.1
#define OPEN_LOOP_CURRENT_REF ((float)0.4f) //0.8
#endif

//----------------------------------------------------------------------------
//CHB-BL3650
#ifdef MOTOR_CHB_BL3650
#define HALL_ANGLE_OFFSET (0.0f / 360.0f) * (2.0f * M_PI)
#define PHASE_INDUCTANCE ((float)0.000783)
#define PHASE_RESISTANCE ((float)1.339)
#define NUM_POLE_PAIRS ((float)4.0f)
#define MOTOR_BEMF_CONST ((float)3.62)
#define RATED_SPEED_RPM ((float)8000)
#define MAX_MOTOR_CURRENT ((float)4)
#define OPEN_LOOP_END_RPM (120)
#define OPEN_LOOP_TIME_IN_SEC (float)(0.06)
#define OPEN_LOOP_CURRENT_REF ((float)0.8)
#endif
//----------------------------------------------------------------------------

#define DISABLED_OPEN_LOOP_TEST 1

#define ROTOR_ALIGN_TIME (uint32_t)((float)LOCK_TIME_IN_SEC / PWM_PERIOD_TIME_SEC)
#define Q_CURRENT_OPENLOOP_STEP ((float)0.0001)

#define SINGLE_ELEC_ROTATION_RAD ((float)((float)(2.0f) * (float)M_PI))
#define MOTOR_BEMF_PHASE_RAD                                                                                           \
    (float)((float)(((MOTOR_BEMF_CONST / M_SQRT3) / 1000.0) / (float)(2.0f * M_PI / 60.0)) / NUM_POLE_PAIRS)

#define FC_MOTOR_ROTOR_lsDt (float)(PHASE_INDUCTANCE / (float)(1 / (float)PWM_FREQUENCY))
#define FC_MOTOR_ROTOR_rs PHASE_RESISTANCE
#define KFILTER_ESDQ (float)((float)0.0183f)
#define DECIMATE_RATED_SPEED (float)((RATED_SPEED_RPM * ((float)M_PI / 30)) * NUM_POLE_PAIRS / 10)
#define KFILTER_VELESTIM (float)((float)0.0053f)
#define K_WE_TO_SPEED (float)((float)(30 / M_PI) / NUM_POLE_PAIRS)
#define PLL_PI_LIMIT_K (float)(2.0)

#define SPEED_SET 1000

// #define PI_D_CURRENT_P                      (float)(0.5)//0.65
// #define PI_D_CURRENT_I                  	(float)(0.01)//0.04
// #define PI_D_CURRENT_D                 	    (float)(0.5)
// #define PI_D_CURRENT_MAX                	(float)(0.98)

// #define PI_Q_CURRENT_P                  	(float)(0.5)//0.65
// #define PI_Q_CURRENT_I                  	(float)(0.01)//0.04
// #define PI_Q_CURRENT_D                  	(float)(0.5)
// #define PI_Q_CURRENT_MAX                	(float)(0.98)

// #define PI_SP_CURRENT_P                 	(float)(0.0001)//0.001
// #define PI_SP_CURRENT_I                 	(float)(0.0000018 * 0.01f)//0.00005
// #define PI_SP_CURRENT_D                 	(float)(0.01)
// #define PI_SP_CURRENT_MAX               	(float)(4)

#define PI_D_CURRENT_P (float)(0.01)  //0.65
#define PI_D_CURRENT_I (float)(0.005) //0.04
#define PI_D_CURRENT_D (float)(0)
#define PI_D_CURRENT_MAX (float)(0.95)
#define PI_D_CURRENT_MAX (float)(0.95)

#define PI_Q_CURRENT_P (float)(0.01)  //0.65
#define PI_Q_CURRENT_I (float)(0.005) //0.04
#define PI_Q_CURRENT_D (float)(0)
#define PI_Q_CURRENT_MAX (float)(0.95)

#define PI_SP_CURRENT_P (float)(0.001)     //0.001
#define PI_SP_CURRENT_I (float)(0.0000) //0.00005
#define PI_SP_CURRENT_D (float)(0.01)
#define PI_SP_CURRENT_MAX (float)(10)

#define PI_SP_BLCDC_P (float)(0.03)
#define PI_SP_BLCDC_I (float)(0.001f)
#define PI_SP_BLCDC_D (float)(4)
#define PI_SP_BLCDC_MAX (float)(MAX_PERIOD)
#define PI_SP_BLCDC_MIN (float)(1)

#define PI_PLL_P (float)(35)   //35
#define PI_PLL_I (float)(0.06) //0.08 0.06

#define K_SMO (float)(120) //120-Dynamic response is faster 38-Lower speed has less fluctuation

#define GAMMA (float)(1000000)
#define FLUX (float)(MOTOR_BEMF_PHASE_RAD)

#define PI_NONLINEAR_P (float)(2 * ZATA_NO * WM_NO) //2*ZATA*WM 800
#define PI_NONLINEAR_I (float)(WM_NO * WM_NO)       //WM*WM 160000
#define WM_NO (float)(1600)
#define ZATA_NO (float)(1.8) //0.707

#ifndef ENCODER_ELEC_ANGLE_OFFSET
#define ENCODER_ELEC_ANGLE_OFFSET 0
#endif
#endif /* MOTOR_LIB_MOTOR_CONFIG_H_ */
