#ifndef _DEVICE_FEATURES_FC4150_FWM_COMMON_H_
#define _DEVICE_FEATURES_FC4150_FWM_COMMON_H_
/*********************** FWM Features ****************************/
/** Number of instances of the FWM module. */
#define FWM_INSTANCE_COUNT                       (1u)
/* FWM - Peripheral instance base addresses */
/** Peripheral FWM base address */
#define FWM_BASE                                 (0x40061000u)
/** Peripheral FWM base pointer */
#define FWM                                      ((FWM_Type *)FWM_BASE)
/** Array initializer of FWM peripheral base addresses */
#define FWM_BASE_ADDRS                           {FWM_BASE}
/** Array initializer of FWM peripheral base pointers */
#define FWM_BASE_PTRS                            {FWM}
// need fill by yourself
///** Number of interrupt vector arrays for the FWM module. */
//#define FWM_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the FWM module. */
//#define FWM_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the FWM peripheral type */
//#define FWM_IRQS                                 {FWM_IRQn}
#endif
