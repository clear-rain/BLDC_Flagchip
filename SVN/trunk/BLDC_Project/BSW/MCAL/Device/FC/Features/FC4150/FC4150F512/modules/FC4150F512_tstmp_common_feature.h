#ifndef _DEVICE_FEATURES_FC4150F512_TSTMP_COMMON_H_
#define _DEVICE_FEATURES_FC4150F512_TSTMP_COMMON_H_
/*********************** TSTMP Features ****************************/
/** TSTMP0 Module is supported or not
 * The TSTMP0 (available on FC4150F1M_B only)*/
/** TSTMP1 Module is supported or not
 * The TSTMP1 (available on FC4150F2M, FC4150F1M_A, and FC4150F1M_B)*/
/** Number of instances of the TSTMP module. */
#define TSTMP_INSTANCE_COUNT                     (0u)


/**When running to the MODx_SETVAL value, the timer will generate an interrupt and will be zero,
 * then it will continue to run from zero.
 * (available on FC4150F1M_B only)*/
#define  TSTMP_SUPPORT_MODULATE_SUPPOT 			STD_OFF

#endif
