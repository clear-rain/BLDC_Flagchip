#ifndef _DEVICE_FEATURES_FC4150_SMC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_SMC_COMMON_H_
/*********************** SMC Features ****************************/
/** Number of instances of the SMC module. */
#define SMC_INSTANCE_COUNT                       (1u)
/* SMC - Peripheral instance base addresses */
/** Peripheral SMC base address */
#define SMC_BASE                                 (0x4007E000u)
/** Peripheral SMC base pointer */
#define SMC                                      ((SMC_Type *)SMC_BASE)
/** Array initializer of SMC peripheral base addresses */
#define SMC_BASE_ADDRS                           {SMC_BASE}
/** Array initializer of SMC peripheral base pointers */
#define SMC_BASE_PTRS                            {SMC}
// need fill by yourself
///** Number of interrupt vector arrays for the SMC module. */
//#define SMC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the SMC module. */
//#define SMC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the SMC peripheral type */
//#define SMC_IRQS                                 {SMC_IRQn}
#endif
