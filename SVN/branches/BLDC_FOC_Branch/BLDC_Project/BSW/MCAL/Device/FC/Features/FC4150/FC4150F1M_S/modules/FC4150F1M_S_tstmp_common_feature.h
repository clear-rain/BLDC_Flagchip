#ifndef _DEVICE_FEATURES_FC4150F1M__B_TSTMP_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_TSTMP_COMMON_H_
/*********************** TSTMP Features ****************************/
/** TSTMP0 Module is supported or not
 * The TSTMP0 (available on FC4150F1M_B only)*/
/** TSTMP1 Module is supported or not
 * The TSTMP1 (available on FC4150F2M, FC4150F1M_A, and FC4150F1M_B)*/
/** Number of instances of the TSTMP module. */
#define TSTMP_INSTANCE_COUNT                     (2u)

/** Peripheral TSTMP0 base address */
#define TSTMP0_BASE                              (0x40042000u)
/** Peripheral TSTMP0 base pointer */
#define TSTMP0                                   ((TSTMP_Type *)TSTMP0_BASE)

/** Peripheral TSTMP1 base address */
#define TSTMP1_BASE                              (0x4007C000u)
/** Peripheral TSTMP1 base pointer */
#define TSTMP1                                   ((TSTMP_Type *)TSTMP1_BASE)

/** Array initializer of TSTMP peripheral base addresses */
#define TSTMP_BASE_ADDRS                         {TSTMP0_BASE,TSTMP1_BASE}
/** Array initializer of TSTMP peripheral base pointers */
#define TSTMP_BASE_PTRS                          {TSTMP0,TSTMP1}

/**When running to the MODx_SETVAL value, the timer will generate an interrupt and will be zero,
 * then it will continue to run from zero.
 * (available on FC4150F1M_B only)*/
#define  TSTMP_SUPPORT_MODULATE_SUPPOT 			STD_ON
#endif
