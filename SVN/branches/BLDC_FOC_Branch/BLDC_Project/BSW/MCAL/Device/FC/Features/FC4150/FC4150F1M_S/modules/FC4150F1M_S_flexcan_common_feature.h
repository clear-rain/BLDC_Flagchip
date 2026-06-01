#ifndef _DEVICE_FEATURES_FC4150F1M__B_FLEXCAN_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_FLEXCAN_COMMON_H_
/*********************** FLEXCAN Features ****************************/
/** Number of instances of the FLEXCAN module. */
#define FLEXCAN_INSTANCE_COUNT                   (3u)

/** Number of instances of the FLEXCAN FD module. */
#define FLEXCAN_FD_INSTANCE_COUNT                1U    /** can 0,1,2      */

/** Array initializer of FLEXCAN peripheral base addresses */
#define FLEXCAN_BASE_ADDRS                       {FLEXCAN0_BASE, FLEXCAN1_BASE, FLEXCAN2_BASE}
/** Array initializer of FLEXCAN peripheral base pointers */
#define FLEXCAN_BASE_PTRS                        {FLEXCAN0, FLEXCAN1, FLEXCAN2}

/**
 * @brief The instance index of the CAN peripheral
 *
 */
typedef enum
{
    CAN_INSTANCE_0 = 0U,
    CAN_INSTANCE_1,
    CAN_INSTANCE_2
} CAN_InstanceType;


#endif
