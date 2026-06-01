#ifndef _DEVICE_FEATURES_FC4150_WKU_COMMON_H_
#define _DEVICE_FEATURES_FC4150_WKU_COMMON_H_
/*********************** WKU Features ****************************/
/** Number of instances of the WKU module. */
#define WKU_INSTANCE_COUNT                       (1u)
/* WKU - Peripheral instance base addresses */
/** Peripheral WKU base address */
#define WKU_BASE                                 (0x4004F000u)
/** Peripheral WKU base pointer */
#define WKU                                      ((WKU_Type *)WKU_BASE)
/** Array initializer of WKU peripheral base addresses */
#define WKU_BASE_ADDRS                           {WKU_BASE}
/** Array initializer of WKU peripheral base pointers */
#define WKU_BASE_PTRS                            {WKU}
// need fill by yourself
///** Number of interrupt vector arrays for the WKU module. */
//#define WKU_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the WKU module. */
//#define WKU_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the WKU peripheral type */
//#define WKU_IRQS                                 {WKU_IRQn}
#endif
