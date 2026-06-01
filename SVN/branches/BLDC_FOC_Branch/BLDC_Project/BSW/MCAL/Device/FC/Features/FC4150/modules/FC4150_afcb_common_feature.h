#ifndef _DEVICE_FEATURES_FC4150__AFCB_COMMON_H_
#define _DEVICE_FEATURES_FC4150__AFCB_COMMON_H_
/*********************** ACFB Features ****************************/
/** AFCB - Size of Registers Arrays */
#define SEG0CNT        4
#define SEG1CNT        16

/** Number of instances of the AFCB module. */
#define AFCB_INSTANCE_COUNT                      (1u)
/* AFCB - Peripheral instance base addresses */
/** Peripheral AFCB base address */
#define AFCB_BASE                                (0x40000000u)

/** Peripheral AFCB base pointer */
#define AFCB                                     ((AFCB_Type *)AFCB_BASE)
/** Array initializer of AFCB peripheral base addresses */
#define AFCB_BASE_ADDRS                          {AFCB_BASE}
/** Array initializer of AFCB peripheral base pointers */
#define AFCB_BASE_PTRS                           {AFCB}
// need fill by yourself
///** Number of interrupt vector arrays for the AFCB module. */
//#define AFCB_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the AFCB module. */
//#define AFCB_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the AFCB peripheral type */
//#define AFCB_IRQS                                {AFCB_IRQn}
#endif
