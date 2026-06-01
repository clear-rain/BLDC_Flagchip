#ifndef _DEVICE_FEATURES_FC4150_SEC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_SEC_COMMON_H_
/*********************** SEC Features ****************************/
/** Number of instances of the SEC module. */
#define SEC_INSTANCE_COUNT                       (1u)
/* SEC - Peripheral instance base addresses */
/** Peripheral SEC base address */
#define SEC_BASE                                 (0x40014000u)
/** Peripheral SEC base pointer */
#define SEC                                      ((SEC_Type *)SEC_BASE)
/** Array initializer of SEC peripheral base addresses */
#define SEC_BASE_ADDRS                           {SEC_BASE}
/** Array initializer of SEC peripheral base pointers */
#define SEC_BASE_PTRS                            {SEC}
// need fill by yourself
///** Number of interrupt vector arrays for the SEC module. */
//#define SEC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the SEC module. */
//#define SEC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the SEC peripheral type */
//#define SEC_IRQS                                 {SEC_IRQn}
#endif
