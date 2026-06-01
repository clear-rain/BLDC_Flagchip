#ifndef _DEVICE_FEATURES_FC4150F2M__ENET_COMMON_H_
#define _DEVICE_FEATURES_FC4150F2M__ENET_COMMON_H_

/*********************** ENET Features ****************************/

/** Number of instances of the ENET module. */
#define ENET_INSTANCE_COUNT                             (1u)

/** Peripheral ENET base address */
#define ENET_BASE                                       (0x40078000u)

/** Array initializer of ENET peripheral base addresses */
#define ENET_BASE_ADDRS                                 {ENET_BASE}

/** Peripheral ENET base pointer */
#define ENET                                            ((ENET_Type *)ENET_BASE)

/** Array initializer of ENET peripheral base pointers */
#define ENET_BASE_PTRS                                  {ENET}

/** ENET system control in SMISC module */
#define ENET_SYSTEM_CONTROL_SMISC                       (1u)

/** ENET system control in SCM module */
#define ENET_SYSTEM_CONTROL_SCM                         (0u)

/** ENET control status register clock from core clock or bus clock(default) */
#define ENET_CSR_INTERFACE_CORE_CLOCK                   (1u)

/** Number of MTL queues and DMA channels */
#define ENET_CHANNEL_COUNT                              (2u)

/** ENET DMA data bus width in bits */
#define ENET_DATA_BUS_WIDTH_BITS                        (32u)

/** ENET MTL Transmit FIFO total size in bytes */
#define ENET_MTL_TX_FIFO_SIZE                           (4096u)

/** ENET MTL Receive FIFO total size in bytes */
#define ENET_MTL_RX_FIFO_SIZE                           (4096u)

/** ENET MAC hash table bits width */
#define ENET_MAC_HASH_WIDTH_BITS                        (6u)

/** ENET VLAN hash table bits width */
#define ENET_VLAN_HASH_WIDTH_BITS                       (4u)

/** Number of ENET PPS channels */
#define ENET_PPS_CHANNEL_COUNT                          (4u)

/** Number of ENET layer 3 and layer 4 filters */
#define ENET_L3L4_FILTER_COUNT                          (4u)

/** Number of ENET VLAN perfect filters */
#define ENET_VLAN_FILTER_COUNT                          (4u)

/** ENET support 1000Mbps (10M and 100M are always supported) */
#define ENET_SUPPORT_1000MBPS                           (0u)

/** ENET supported RMII mode */
#define ENET_SUPPORT_RMII                               (1u)

/** ENET supported RGMII mode */
#define ENET_SUPPORT_RGMII                              (0u)

/** ENET support reference clock pin */
#define ENET_SUPPORT_REFCLK_PIN                         (0u)

/** ENET support time sensitive networking */
#define ENET_SUPPORT_TIME_SENSITIVE_NETWORK             (0u)

/** ENET support automotive safety features */
#define ENET_SUPPORT_AUTOMOTIVE_SAFETY                  (0u)

#endif /* _DEVICE_FEATURES_FC4150F2M__ENET_COMMON_H_ */
