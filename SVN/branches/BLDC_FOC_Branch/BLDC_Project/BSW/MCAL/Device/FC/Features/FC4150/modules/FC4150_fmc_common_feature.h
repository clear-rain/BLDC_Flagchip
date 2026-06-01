#ifndef _DEVICE_FEATURES_FC4150_FMC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_FMC_COMMON_H_
/*********************** FMC Features ****************************/
/** Number of instances of the FMC module. */
#define FMC_INSTANCE_COUNT                       (1u)
/* FMC - Peripheral instance base addresses */
/** Peripheral FMC base address */
#define FMC_BASE                                 (0x4001E000u)
/** Peripheral FMC base pointer */
#define FMC                                      ((FMC_Type *)FMC_BASE)
/** Array initializer of FMC peripheral base addresses */
#define FMC_BASE_ADDRS                           {FMC_BASE}
/** Array initializer of FMC peripheral base pointers */
#define FMC_BASE_PTRS                            {FMC}
// need fill by yourself
///** Number of interrupt vector arrays for the FMC module. */
//#define FMC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the FMC module. */
//#define FMC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the FMC peripheral type */
//#define FMC_IRQS                                 {FMC_IRQn}
#endif
