#ifndef _DEVICE_FEATURES_FC4150_RCM_COMMON_H_
#define _DEVICE_FEATURES_FC4150_RCM_COMMON_H_
/*********************** RCM Features ****************************/
/** Number of instances of the RCM module. */
#define RCM_INSTANCE_COUNT                       (1u)
/* RCM - Peripheral instance base addresses */
/** Peripheral RCM base address */
#define RCM_BASE                                 (0x4007F000u)
/** Peripheral RCM base pointer */
#define RCM                                      ((RCM_Type *)RCM_BASE)
/** Array initializer of RCM peripheral base addresses */
#define RCM_BASE_ADDRS                           {RCM_BASE}
/** Array initializer of RCM peripheral base pointers */
#define RCM_BASE_PTRS                            {RCM}
// need fill by yourself
///** Number of interrupt vector arrays for the RCM module. */
//#define RCM_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the RCM module. */
//#define RCM_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the RCM peripheral type */
//#define RCM_IRQS                                 {RCM_IRQn}


#endif
