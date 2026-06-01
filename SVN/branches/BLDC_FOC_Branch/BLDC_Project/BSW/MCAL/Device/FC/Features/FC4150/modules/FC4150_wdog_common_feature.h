#ifndef _DEVICE_FEATURES_FC4150_WDOG_COMMON_H_
#define _DEVICE_FEATURES_FC4150_WDOG_COMMON_H_
/*********************** WDOG Features ****************************/
/** Number of instances of the WDOG module. */
#define WDOG_INSTANCE_COUNT                      (2u)
/* WDOG - Peripheral instance base addresses */
/** Peripheral WDOG0 base address */
#define WDOG0_BASE                               (0x40052000u)
/** Peripheral WDOG0 base pointer */
#define WDOG0                                    ((WDOG_Type *)WDOG0_BASE)
/** Peripheral WDOG1 base address */
#define WDOG1_BASE                               (0x40053000u)
/** Peripheral WDOG1 base pointer */
#define WDOG1                                    ((WDOG_Type *)WDOG1_BASE)
/** Array initializer of WDOG peripheral base addresses */
#define WDOG_BASE_ADDRS                          {WDOG0_BASE, WDOG1_BASE}
/** Array initializer of WDOG peripheral base pointers */
#define WDOG_BASE_PTRS                           {WDOG0, WDOG1}
// need fill by yourself
///** Number of interrupt vector arrays for the WDOG module. */
//#define WDOG_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the WDOG module. */
//#define WDOG_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the WDOG peripheral type */
//#define WDOG_IRQS                                {WDOG0_IRQn, WDOG1_IRQn}
#endif
