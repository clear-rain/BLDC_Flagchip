#ifndef _DEVICE_FEATURES_FC4150_INTM_COMMON_H_
#define _DEVICE_FEATURES_FC4150_INTM_COMMON_H_
/*********************** INTM Features ****************************/
/** Number of instances of the INTM module. */
#define INTM_INSTANCE_COUNT                      (1u)
/* INTM - Peripheral instance base addresses */
/** Peripheral INTM base address */
#define INTM_BASE                                (0x4001A000u)
/** Peripheral INTM base pointer */
#define INTM                                     ((INTM_Type *)INTM_BASE)
/** Array initializer of INTM peripheral base addresses */
#define INTM_BASE_ADDRS                          {INTM_BASE}
/** Array initializer of INTM peripheral base pointers */
#define INTM_BASE_PTRS                           {INTM}
// need fill by yourself
///** Number of interrupt vector arrays for the INTM module. */
//#define INTM_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the INTM module. */
//#define INTM_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the INTM peripheral type */
//#define INTM_IRQS                                {INTM_IRQn}
/** Configuration of INTM as interrupt inactive mode is supported or not
 * For FC4150F1M_B Only*/

#endif
