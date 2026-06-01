#ifndef _DEVICE_FEATURES_FC4150F1M__A_I2S_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__A_I2S_COMMON_H_

/*********************** I2S Features ****************************/

/** Number of instances of the I2S module. */
#define I2S_INSTANCE_COUNT                       (2u)

/* I2S - Peripheral instance base addresses */
/** Peripheral I2S0 base address */
#define I2S0_BASE                                (0x40054000u)
/** Peripheral I2S0 base pointer */
#define I2S0                                     ((I2S_Type *)I2S0_BASE)
/** Peripheral I2S1 base address */
#define I2S1_BASE                                (0x40055000u)
/** Peripheral I2S1 base pointer */
#define I2S1                                     ((I2S_Type *)I2S1_BASE)

/** Array initializer of I2S peripheral base addresses */
#define I2S_BASE_ADDRS                           {I2S0_BASE, I2S1_BASE}

/** Array initializer of I2S peripheral base pointers */
#define I2S_BASE_PTRS                            {I2S0, I2S1}

#endif
