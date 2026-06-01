#ifndef _DEVICE_FEATURES_FC4150_MAP_COMMON_H_
#define _DEVICE_FEATURES_FC4150_MAP_COMMON_H_
/*********************** MAP Features ****************************/
/** Number of instances of the MAP module. */
#define MAP_INSTANCE_COUNT                       (1u)
/* MAP - Peripheral instance base addresses */
/** Peripheral MAP base address */
#define MAP_BASE                                 (0x4000D000u)
/** Peripheral MAP base pointer */
#define MAP                                      ((MAP_Type *)MAP_BASE)
/** Array initializer of MAP peripheral base addresses */
#define MAP_BASE_ADDRS                           {MAP_BASE}
/** Array initializer of MAP peripheral base pointers */
#define MAP_BASE_PTRS                            {MAP}
// need fill by yourself
///** Number of interrupt vector arrays for the MAP module. */
//#define MAP_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the MAP module. */
//#define MAP_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the MAP peripheral type */
//#define MAP_IRQS                                 {MAP_IRQn}
#endif
