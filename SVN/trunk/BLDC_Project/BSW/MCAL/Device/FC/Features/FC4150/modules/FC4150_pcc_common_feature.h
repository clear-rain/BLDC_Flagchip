#ifndef _DEVICE_FEATURES_FC4150_PCC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_PCC_COMMON_H_
/*********************** PCC Features ****************************/
/** Number of instances of the PCC module. */
#define PCC_INSTANCE_COUNT                       (1u)
/* PCC - Peripheral instance base addresses */
/** Peripheral PCC base address */
#define PCC_BASE                                 (0x40065000u)
/** Peripheral PCC base pointer */
#define PCC                                      ((PCC_Type *)PCC_BASE)
/** Array initializer of PCC peripheral base addresses */
#define PCC_BASE_ADDRS                           {PCC_BASE}
/** Array initializer of PCC peripheral base pointers */
#define PCC_BASE_PTRS                            {PCC}
// need fill by yourself
///** Number of interrupt vector arrays for the PCC module. */
//#define PCC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the PCC module. */
//#define PCC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the PCC peripheral type */
//#define PCC_IRQS                                 {PCC_IRQn}
#endif
