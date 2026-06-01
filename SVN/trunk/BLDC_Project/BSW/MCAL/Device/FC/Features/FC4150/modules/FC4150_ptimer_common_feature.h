#ifndef _DEVICE_FEATURES_FC4150_PTIMER_COMMON_H_
#define _DEVICE_FEATURES_FC4150_PTIMER_COMMON_H_
/*********************** PTIMER Features ****************************/
/** Number of instances of the PTIMER module. */
#define PTIMER_INSTANCE_COUNT                    (2u)
/* PTIMER - Peripheral instance base addresses */
/** Peripheral PTIMER0 base address */
#define PTIMER0_BASE                             (0x40036000u)
/** Peripheral PTIMER0 base pointer */
#define PTIMER0                                  ((PTIMER_Type *)PTIMER0_BASE)
/** Peripheral PTIMER1 base address */
#define PTIMER1_BASE                             (0x40031000u)
/** Peripheral PTIMER1 base pointer */
#define PTIMER1                                  ((PTIMER_Type *)PTIMER1_BASE)
/** Array initializer of PTIMER peripheral base addresses */
#define PTIMER_BASE_ADDRS                        {PTIMER0_BASE, PTIMER1_BASE}
/** Array initializer of PTIMER peripheral base pointers */
#define PTIMER_BASE_PTRS                         {PTIMER0, PTIMER1}
// need fill by yourself
///** Number of interrupt vector arrays for the PTIMER module. */
//#define PTIMER_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the PTIMER module. */
//#define PTIMER_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the PTIMER peripheral type */
//#define PTIMER_IRQS                              {PTIMER0_IRQn, PTIMER1_IRQn}
#endif
