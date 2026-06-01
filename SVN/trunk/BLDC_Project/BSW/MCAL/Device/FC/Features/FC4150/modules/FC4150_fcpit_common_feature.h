#ifndef _DEVICE_FEATURES_FC4150_FCPIT_COMMON_H_
#define _DEVICE_FEATURES_FC4150_FCPIT_COMMON_H_
/*********************** FCPIT Features ****************************/
/** Number of instances of the FCPIT module. */
#define FCPIT_INSTANCE_COUNT                     (1u)
/* FCPIT - Peripheral instance base addresses */
/** Peripheral FCPIT base address */
#define FCPIT_BASE                               (0x40037000u)
/** Peripheral FCPIT base pointer */
#define FCPIT                                    ((FCPIT_Type *)FCPIT_BASE)
/** Array initializer of FCPIT peripheral base addresses */
#define FCPIT_BASE_ADDRS                         {FCPIT_BASE}
/** Array initializer of FCPIT peripheral base pointers */
#define FCPIT_BASE_PTRS                          {FCPIT}
#endif
