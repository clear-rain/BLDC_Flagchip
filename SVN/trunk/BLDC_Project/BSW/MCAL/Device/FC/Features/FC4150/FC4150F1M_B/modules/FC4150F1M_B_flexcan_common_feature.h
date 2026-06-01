#ifndef _DEVICE_FEATURES_FC4150F1M__B_FLEXCAN_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_FLEXCAN_COMMON_H_
/*********************** FLEXCAN Features ****************************/
/** Number of instances of the FLEXCAN module. */
#define FLEXCAN_INSTANCE_COUNT                   (3u)

/**
 * @brief The instance index of the CAN peripheral
 *
 */
typedef enum
{
    FLEXCAN_INSTANCE_0 = 0U,
    FLEXCAN_INSTANCE_1,
    FLEXCAN_INSTANCE_2
} FLEXCAN_InstanceType;

/* Every CAN contains message buffer number */
#define FLEXCAN_MB_NUM_PTRS                     {32U,32U,32U}
/* Number of instances of the FLEXCAN FD module. */
#define FLEXCAN_FD_SUPPORT_PTRS                 {1U,1U,1U}
/* Support Gate */
#define FLEXCAN_GATE_BUFNUM_PTRS                {0U,0U,0U}

/* IFlag1...IFlagn, IMask1...IMaskn */
#define FLEXCAN_IFLAGMASK_NUM_PTRS              {1U,1U,1U}
#define FLEXCAN_IFLAGMASK_NUM_MAX               1U

/* MBDSR0..MBDSRn */
#define FLEXCAN_FD_DATALEN_RANGE_NUM_PTRS       {1U,0U,0U}
#define FLEXCAN_FD_DATALEN_RANGE_NUM_MAX        1U

/* Enhanced Rx FIFO */
#define FLEXCAN_ENHANCED_FIFO_ELEMENT_MAX_PTRS  {32U,32U,32U}
#define FLEXCAN_ENHANCED_FIFO_DEPTH_PTRS        {12U,12U,12U}


#define FLEXCAN_LEGACY_FIFO_DEPTH               6U
#define FLEXCAN_LEGACY_FIFO_FILTER_START        6U
#define FLEXCAN_LEGACY_FIFO_ELEMENT_MAX         104U

#define FLEXCAN_LEGACY_FIFO_NUM_TABLE_LENGTH    13U
#define FLEXCAN_LEGACY_FIFO_PTRS  { \
                                /* RFFN[3:0]    Filter Num    MB for Legacy  */ \
                                {  0U,          8U,           8U  }, \
                                {  1U,          16U,          10U }, \
                                {  2U,          24U,          12U }, \
                                {  3U,          32U,          14U }, \
                                {  4U,          40U,          16U }, \
                                {  5U,          48U,          18U }, \
                                {  6U,          56U,          20U }, \
                                {  7U,          64U,          22U }, \
                                {  8U,          72U,          24U }, \
                                {  9U,          80U,          26U }, \
                                {  0xAU,        88U,          28U }, \
                                {  0XBU,        96U,          30U }, \
                                {  0XCU,        104U,         32U } \
                            }


/* FLEXCAN - Peripheral instance base addresses */
/** Peripheral FLEXCAN0 base address */
#define FLEXCAN0_BASE                            (0x40080000u)
/** Peripheral FLEXCAN0 base pointer */
#define FLEXCAN0                                 ((FLEXCAN_Type *)FLEXCAN0_BASE)
/** Peripheral FLEXCAN1 base address */
#define FLEXCAN1_BASE                            (0x40084000u)
/** Peripheral FLEXCAN1 base pointer */
#define FLEXCAN1                                 ((FLEXCAN_Type *)FLEXCAN1_BASE)
/** Peripheral FLEXCAN2 base address */
#define FLEXCAN2_BASE                            (0x40088000u)
/** Peripheral FLEXCAN2 base pointer */
#define FLEXCAN2                                 ((FLEXCAN_Type *)FLEXCAN2_BASE)
/** Peripheral FLEXCAN3 base address */

/** Array initializer of FLEXCAN peripheral base addresses */
#define FLEXCAN_BASE_ADDRS                       {FLEXCAN0_BASE, FLEXCAN1_BASE, FLEXCAN2_BASE}
/** Array initializer of FLEXCAN peripheral base pointers */
#define FLEXCAN_BASE_PTRS                        {FLEXCAN0, FLEXCAN1, FLEXCAN2}


#define FLEXCAN_ERRATA_TRANSMIT_LIMIT           STD_ON
#define FLEXCAN_ERRATA_TRANSMIT_LM_LIST         {5U, 15U, 25U}
#define FLEXCAN_ERRATA_TRANSMIT_LM_LIST_LEN     3U

#endif
