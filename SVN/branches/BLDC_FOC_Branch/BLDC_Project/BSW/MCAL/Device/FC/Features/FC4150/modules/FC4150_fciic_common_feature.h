#ifndef _DEVICE_FEATURES_FC4150_FCIIC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_FCIIC_COMMON_H_
/*********************** FCIIC Features ****************************/
/** Number of instances of the FCIIC module. */
#define FCIIC_INSTANCE_COUNT                     (2u)
/* FCIIC - Peripheral instance base addresses */
/** Peripheral FCIIC0 base address */
#define FCIIC0_BASE                              (0x40066000u)
/** Peripheral FCIIC0 base pointer */
#define FCIIC0                                   ((FCIIC_Type *)FCIIC0_BASE)
/** Peripheral FCIIC1 base address */
#define FCIIC1_BASE                              (0x40067000u)
/** Peripheral FCIIC1 base pointer */
#define FCIIC1                                   ((FCIIC_Type *)FCIIC1_BASE)
/** Array initializer of FCIIC peripheral base addresses */
#define FCIIC_BASE_ADDRS                         {FCIIC0_BASE, FCIIC1_BASE}
/** Array initializer of FCIIC peripheral base pointers */
#define FCIIC_BASE_PTRS                          {FCIIC0, FCIIC1}
// need fill by yourself
///** Number of interrupt vector arrays for the FCIIC module. */
//#define FCIIC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the FCIIC module. */
//#define FCIIC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the FCIIC peripheral type */
//#define FCIIC_IRQS                               {FCIIC0_IRQn, FCIIC1_IRQn}
#endif
