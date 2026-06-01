#ifndef _DEVICE_FEATURES_FC4150_ISM_COMMON_H_
#define _DEVICE_FEATURES_FC4150_ISM_COMMON_H_
/*********************** ISM Features ****************************/

/* ISM - Peripheral instance base addresses */
/** Peripheral ISM base address */
#define ISM_BASE                                 (0x4001b000u)
/** Peripheral ISM base pointer */
#define ISM                                      ((ISM_Type *)ISM_BASE)
/** Array initializer of ISM peripheral base addresses */
#define ISM_BASE_ADDRS                           {ISM_BASE}
/** Array initializer of ISM peripheral base pointers */
#define ISM_BASE_PTRS                            {ISM}
// need fill by yourself
///** Number of interrupt vector arrays for the ISM module. */
//#define ISM_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the ISM module. */
//#define ISM_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the ISM peripheral type */
//#define ISM_IRQS                                 {ISM_IRQn}
#endif
