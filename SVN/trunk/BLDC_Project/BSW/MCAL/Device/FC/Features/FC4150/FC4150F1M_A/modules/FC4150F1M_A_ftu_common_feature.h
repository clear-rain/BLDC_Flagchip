#ifndef _DEVICE_FEATURES_FC4150F1M__A_FTU_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__A_FTU_COMMON_H_
/*********************** FTU Features ****************************/
/** Number of instances of the FTU module. */
#define FTU_INSTANCE_COUNT                       (8u)
/** Peripheral FTU6 base address */
#define FTU6_BASE                                (0x40056000u)
/** Peripheral FTU6 base pointer */
#define FTU6                                     ((FTU_Type *)FTU6_BASE)
/** Peripheral FTU7 base address */
#define FTU7_BASE                                (0x40057000u)
/** Peripheral FTU7 base pointer */
#define FTU7                                     ((FTU_Type *)FTU7_BASE)
/** Array initializer of FTU peripheral base addresses */
#define FTU_BASE_ADDRS                           {FTU0_BASE, FTU1_BASE, FTU2_BASE, FTU3_BASE, FTU4_BASE, FTU5_BASE, FTU6_BASE, FTU7_BASE}
/** Array initializer of FTU peripheral base pointers */
#define FTU_BASE_PTRS                            {FTU0, FTU1, FTU2, FTU3, FTU4, FTU5, FTU6, FTU7}

#define FTU_GET_MAX_COUNTER(base)                 0xFFFFu
#define FTU_INSTANCE_QD_SUPPORT(base)             ((((uint32_t)base) == FTU1_BASE) || (((uint32_t)base) == FTU2_BASE) ? 1 : 0)

/**
 * @brief Max number of Ftu fault
 *
 */
#define FTU_FAULT_INPUT_COUNT(base)               ((((uint32_t)base) == FTU4_BASE) || (((uint32_t)base) == FTU5_BASE) ? 2 : 4)


#endif
