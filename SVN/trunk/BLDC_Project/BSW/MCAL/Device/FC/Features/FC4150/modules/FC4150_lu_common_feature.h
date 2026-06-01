#ifndef _DEVICE_FEATURES_FC4150_LU_COMMON_H_
#define _DEVICE_FEATURES_FC4150_LU_COMMON_H_
#if 1
/*********************** LU Features ****************************/
#define LG_CNT 4

/** Number of instances of the LU module. */
#define LU_INSTANCE_COUNT                        (1u)
/* LU - Peripheral instance base addresses */
/** Peripheral LU base address */
#define LU_BASE                                  (0x40070000u)
/** Peripheral LU base pointer */
#define LU                                       ((LU_Type *)LU_BASE)
/** Array initializer of LU peripheral base addresses */
#define LU_BASE_ADDRS                            {LU_BASE}
/** Array initializer of LU peripheral base pointers */
#define LU_BASE_PTRS                             {LU}
// need fill by yourself
///** Number of interrupt vector arrays for the LU module. */
//#define LU_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the LU module. */
//#define LU_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the LU peripheral type */
//#define LU_IRQS                                  {LU_IRQn}
#endif
#endif
