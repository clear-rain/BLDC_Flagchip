#ifndef _DEVICE_FEATURES_FC4150_MCM_COMMON_H_
#define _DEVICE_FEATURES_FC4150_MCM_COMMON_H_
/*********************** MCM Features ****************************/
/** Number of instances of the MCM module. */
#define MCM_INSTANCE_COUNT                       (1u)
/* MCM - Peripheral instance base addresses */
/** Peripheral MCM base address */
#define MCM_BASE                                 (0xE0080000u)
/** Peripheral MCM base pointer */
#define MCM                                      ((MCM_Type *)MCM_BASE)
/** Array initializer of MCM peripheral base addresses */
#define MCM_BASE_ADDRS                           {MCM_BASE}
/** Array initializer of MCM peripheral base pointers */
#define MCM_BASE_PTRS                            {MCM}
// need fill by yourself
///** Number of interrupt vector arrays for the MCM module. */
//#define MCM_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the MCM module. */
//#define MCM_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the MCM peripheral type */
//#define MCM_IRQS                                 {MCM_IRQn}
#endif
