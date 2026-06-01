#ifndef _DEVICE_FEATURES_FC4150_RTC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_RTC_COMMON_H_
/*********************** RTC Features ****************************/
/** Number of instances of the RTC module. */
#define RTC_INSTANCE_COUNT                       (1u)
/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE                                 (0x4003D000u)
/** Peripheral RTC base pointer */
#define RTC                                      ((RTC_Type *)RTC_BASE)
/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS                           {RTC_BASE}
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                            {RTC}
// need fill by yourself
///** Number of interrupt vector arrays for the RTC module. */
//#define RTC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the RTC module. */
//#define RTC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the RTC peripheral type */
//#define RTC_IRQS                                 {RTC_IRQn}
#endif
