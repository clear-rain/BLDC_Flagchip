#ifndef _DEVICE_FEATURES_FC4150F1M__A_FLEXCAN_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__A_FLEXCAN_COMMON_H_
/*********************** FLEXCAN Features ****************************/
/** Number of instances of the FLEXCAN module. */
#define FLEXCAN_INSTANCE_COUNT                   (6u)

/** Number of instances of the FLEXCAN FD module. */
#define FLEXCAN_FD_INSTANCE_COUNT                3U    /** can 0,1,2      */


/** Peripheral FLEXCAN3 base address */
#define FLEXCAN3_BASE                            (0x4008C000u)
/** Peripheral FLEXCAN3 base pointer */
#define FLEXCAN3                                 ((FLEXCAN_Type *)FLEXCAN3_BASE)
/** Peripheral FLEXCAN4 base address */
#define FLEXCAN4_BASE                            (0x40090000u)
/** Peripheral FLEXCAN4 base pointer */
#define FLEXCAN4                                 ((FLEXCAN_Type *)FLEXCAN4_BASE)
/** Peripheral FLEXCAN5 base address */
#define FLEXCAN5_BASE                            (0x40094000u)
/** Peripheral FLEXCAN5 base pointer */
#define FLEXCAN5                                 ((FLEXCAN_Type *)FLEXCAN5_BASE)
/** Array initializer of FLEXCAN peripheral base addresses */
#define FLEXCAN_BASE_ADDRS                       {FLEXCAN0_BASE, FLEXCAN1_BASE, FLEXCAN2_BASE, FLEXCAN3_BASE, FLEXCAN4_BASE, FLEXCAN5_BASE}
/** Array initializer of FLEXCAN peripheral base pointers */
#define FLEXCAN_BASE_PTRS                        {FLEXCAN0, FLEXCAN1, FLEXCAN2, FLEXCAN3, FLEXCAN4, FLEXCAN5}

/**
 * @brief The instance index of the CAN peripheral
 *
 */
typedef enum
{
    CAN_INSTANCE_0 = 0U,
    CAN_INSTANCE_1,
    CAN_INSTANCE_2,
    CAN_INSTANCE_3,
    CAN_INSTANCE_4,
    CAN_INSTANCE_5
} CAN_InstanceType;


#endif
