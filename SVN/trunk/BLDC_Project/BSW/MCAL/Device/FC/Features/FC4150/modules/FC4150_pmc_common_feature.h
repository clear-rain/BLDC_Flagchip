#ifndef _DEVICE_FEATURES_FC4150_PMC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_PMC_COMMON_H_
/*********************** PMC Features ****************************/
/** Number of instances of the PMC module. */
#define PMC_INSTANCE_COUNT                       (1u)
/* PMC - Peripheral instance base addresses */
/** Peripheral PMC base address */
#define PMC_BASE                                 (0x4007D000u)
/** Peripheral PMC base pointer */
#define PMC                                      ((PMC_Type *)PMC_BASE)
/** Array initializer of PMC peripheral base addresses */
#define PMC_BASE_ADDRS                           {PMC_BASE}
/** Array initializer of PMC peripheral base pointers */
#define PMC_BASE_PTRS                            {PMC}
// need fill by yourself
///** Number of interrupt vector arrays for the PMC module. */
//#define PMC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the PMC module. */
//#define PMC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the PMC peripheral type */
//#define PMC_IRQS                                 {PMC_IRQn}
#endif
