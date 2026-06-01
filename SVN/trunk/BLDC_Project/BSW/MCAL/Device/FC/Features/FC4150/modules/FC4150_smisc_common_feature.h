#ifndef _DEVICE_FEATURES_FC4150_SMISC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_SMISC_COMMON_H_
/*********************** SMISC Features ****************************/
/** Number of instances of the SMISC module. */
#define SMISC_INSTANCE_COUNT                     (1u)
/* SMISC - Peripheral instance base addresses */
/** Peripheral SMISC base address */
#define SMISC_BASE                               (0x40048000u)
/** Peripheral SMISC base pointer */
#define SMISC                                    ((SMISC_Type *)SMISC_BASE)
/** Array initializer of SMISC peripheral base addresses */
#define SMISC_BASE_ADDRS                         {SMISC_BASE}
/** Array initializer of SMISC peripheral base pointers */
#define SMISC_BASE_PTRS                          {SMISC}
// need fill by yourself
///** Number of interrupt vector arrays for the SMISC module. */
//#define SMISC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the SMISC module. */
//#define SMISC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the SMISC peripheral type */
//#define SMISC_IRQS                               {SMISC_IRQn}
#endif
