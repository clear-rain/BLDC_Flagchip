#ifndef _DEVICE_FEATURES_FC4150F1M__B_I2S_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_I2S_COMMON_H_

/*********************** I2S Features ****************************/

/** Number of instances of the I2S module. */
#define I2S_INSTANCE_COUNT                       (1u)

/* I2S - Peripheral instance base addresses */
/** Peripheral I2S0 base address */
#define I2S0_BASE                                (0x40054000u)
/** Peripheral I2S0 base pointer */
#define I2S0                                     ((I2S_Type *)I2S0_BASE)

/** Array initializer of I2S peripheral base addresses */
#define I2S_BASE_ADDRS                           {I2S0_BASE}

/** Array initializer of I2S peripheral base pointers */
#define I2S_BASE_PTRS                            {I2S0}

#endif
