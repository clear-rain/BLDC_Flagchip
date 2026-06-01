#ifndef _DEVICE_FEATURES_FC4150_AONTIMER_COMMON_H_
#define _DEVICE_FEATURES_FC4150_AONTIMER_COMMON_H_
/*********************** AonTimer Features ****************************/
/** Number of instances of the AONTIMER module. */
#define AONTIMER_INSTANCE_COUNT                  (1u)
/* AONTIMER - Peripheral instance base addresses */
/** Peripheral AONTIMER base address */
#define AONTIMER_BASE                            (0x40040000u)

/** Peripheral AONTIMER base pointer */
#define AONTIMER                                 ((AONTIMER_Type *)AONTIMER_BASE)
/** Array initializer of AONTIMER peripheral base addresses */
#define AONTIMER_BASE_ADDRS                      {AONTIMER_BASE}
/** Array initializer of AONTIMER peripheral base pointers */
#define AONTIMER_BASE_PTRS                       {AONTIMER}

#endif
