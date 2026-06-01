#ifndef _DEVICE_FEATURES_FC4150_CCU_COMMON_H_
#define _DEVICE_FEATURES_FC4150_CCU_COMMON_H_
/*********************** CCU Features ****************************/
/** Number of instances of the CCU module. */
#define CCU_INSTANCE_COUNT                       (1u)
/* CCU - Peripheral instance base addresses */
/** Peripheral CCU base address */
#define CCU_BASE                                 (0xE0082000u)

/** Peripheral CCU base pointer */
#define CCU                                      ((CCU_Type *)CCU_BASE)
/** Array initializer of CCU peripheral base addresses */
#define CCU_BASE_ADDRS                           {CCU_BASE}
/** Array initializer of CCU peripheral base pointers */
#define CCU_BASE_PTRS                            {CCU}
// need fill by yourself
///** Number of interrupt vector arrays for the CCU module. */
//#define CCU_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the CCU module. */
//#define CCU_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the CCU peripheral type */
//#define CCU_IRQS                                 {CCU_IRQn}
#endif
