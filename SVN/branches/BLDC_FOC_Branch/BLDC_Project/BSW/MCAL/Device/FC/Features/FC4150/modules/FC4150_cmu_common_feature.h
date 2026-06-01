#ifndef _DEVICE_FEATURES_FC4150_CMU_COMMON_H_
#define _DEVICE_FEATURES_FC4150_CMU_COMMON_H_

/*********************** CMU Features ****************************/

/** Number of instances of the CMU module. */
#define CMU_INSTANCE_COUNT                       (4u)
/* CMU - Peripheral instance base addresses */

/** Peripheral CMU0 base address */
#define CMU0_BASE                                (0x4003E000u)
/** Peripheral CMU0 base pointer */
#define CMU0                                     ((CMU_Type *)CMU0_BASE)
/** Peripheral CMU1 base address */
#define CMU1_BASE                                (0x4003F000u)
/** Peripheral CMU1 base pointer */
#define CMU1                                     ((CMU_Type *)CMU1_BASE)
/** Peripheral CMU2 base address */
#define CMU2_BASE                                (0x40043000u)
/** Peripheral CMU2 base pointer */
#define CMU2                                     ((CMU_Type *)CMU2_BASE)
/** Peripheral CMU3 base address */
#define CMU3_BASE                                (0x40044000u)
/** Peripheral CMU3 base pointer */
#define CMU3                                     ((CMU_Type *)CMU3_BASE)

/** Array initializer of CMU peripheral base addresses */
#define CMU_BASE_ADDRS                           {CMU0_BASE, CMU1_BASE, CMU2_BASE, CMU3_BASE}

/** Array initializer of CMU peripheral base pointers */
#define CMU_BASE_PTRS                            {CMU0, CMU1, CMU2, CMU3}

#endif
