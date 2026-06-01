/**
 * @file module_driver_enet.h
 * @author Flagchip
 * @brief ENET driver type definition and API
 * @version 2.0.0
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-07-19    Flagchip085   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_ENET_H_
#define _DRIVER_MODULE_DRIVER_ENET_H_

#include "HwA_enet.h"

#if ENET_INSTANCE_COUNT > 0u

#include "module_driver_scg.h"
#include "module_driver_pcc.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup module_driver_enet
 * @{
 */


/**
 * @name  ENET API Service IDs
 * @brief  ENET API Service IDs
 *
 * @{
 */
#define ENET_DEFAULT_CONFIG_SERVICE_ID          0u
#define ENET_DEINIT_SERVICE_ID                  1u
#define ENET_INIT_SERVICE_ID                    2u
#define ENET_PREPARE_DESC_SERVICE_ID            3u
#define ENET_START_SERVICE_ID                   4u
#define ENET_STOP_SERVICE_ID                    5u
#define ENET_STARTIT_SERVICE_ID                 6u
#define ENET_STOPIT_SERVICE_ID                  7u
#define ENET_SEND_FRAME_SERVICE_ID              8u
#define ENET_READ_FRAME_SERVICE_ID              9u
#define ENET_BUILD_RXDESC_SERVICE_ID            10u
#define ENET_SET_MACADDR_SERVICE_ID             11u
#define ENET_CKSUM_ERROR_FILTER_SERVICE_ID      12u
#define ENET_SET_MACHASH_SERVICE_ID             13u
#define ENET_DEFAULT_MACFILTER_SERVICE_ID       14u
#define ENET_GET_MACFILTER_SERVICE_ID           15u
#define ENET_SET_MACFILTER_SERVICE_ID           16u
#define ENET_DEFAULT_L3L4FILTER_SERVICE_ID      17u
#define ENET_GET_L3L4FILTER_SERVICE_ID          18u
#define ENET_SET_L3L4FILTER_SERVICE_ID          19u
#define ENET_ENABLE_L3L4FILTER_SERVICE_ID       20u
#define ENET_GET_VLANFILTER_CFG_SERVICE_ID      21u
#define ENET_ENABLE_VLANFILTER_SERVICE_ID       22u
#define ENET_SET_VLANHASH_SERVICE_ID            23u
#define ENET_GET_VLAN_PERFECTFILTER_SERVICE_ID  24u
#define ENET_SET_VLAN_PERFECTFILTER_SERVICE_ID  25u
#define ENET_SET_TXOUTERVLAN_SERVICE_ID         26u
#define ENET_SET_TXOUTVLAN_CBI_SERVICE_ID       27u
#define ENET_SET_TXINNERVLAN_SERVICE_ID         28u
#define ENET_REGISTER_SYSEVENT_SERVICE_ID       29u
#define ENET_REGISTER_RXCOMP_SERVICE_ID         30u
#define ENET_REGISTER_TXCOMP_SERVICE_ID         31u
#define ENET_REGISTER_TXWAIT_SERVICE_ID         32u
#define ENET_MDIO_DEFCONFIG_SERVICE_ID          33u
#define ENET_MDIO_INIT_SERVICE_ID               34u
#define ENET_MDIO_READ_SERVICE_ID               35u
#define ENET_MDIO_WRITE_SERVICE_ID              36u
#define ENET_MMD_READ_SERVICE_ID                37u
#define ENET_MMD_WRITE_SERVICE_ID               38u
#define ENET_PTP_DEFCONFIG_SERVICE_ID           39u
#define ENET_PTP_START_SERVICE_ID               40u
#define ENET_PTP_STOP_SERVICE_ID                41u
#define ENET_PTP_GETTIME_SERVICE_ID             42u
#define ENET_PTP_SETTIME_SERVICE_ID             43u
#define ENET_PTP_UPDATETIME_SERVICE_ID          44u
#define ENET_PTP_ADJUST_FREQ_SERVICE_ID         45u
#define ENET_PTP_FIXED_PPSOUT_SERVICE_ID        46u
#define ENET_PTP_FLEXIBLE_PPSOUT_SERVICE_ID     47u
#define ENET_GET_MMCCONFIG_SERVICE_ID           48u
#define ENET_SET_MMCCONFIG_SERVICE_ID           49u
#define ENET_MMC_COUNTER_PRESET_SERVICE_ID      50u
#define ENET_MMC_COUNTER_FREEZE_SERVICE_ID      51u
#define ENET_MMC_COUNTER_RESET_SERVICE_ID       52u
#define ENET_MMC_GET_TXINT_SERVICE_ID           53u
#define ENET_MMC_GET_RXINT_SERVICE_ID           54u
#define ENET_MMC_GET_TXCOUNTER_SERVICE_ID       55u
#define ENET_MMC_GET_RXCOUNTER_SERVICE_ID       56u
#define ENET_GET_FLOWCTRL_SERVICE_ID            57u
#define ENET_SET_FLOWCTRL_SERVICE_ID            58u
#define ENET_FLOWCTRL_SOFTTRIG_SERVICE_ID       59u
#define ENET_SYSIRQ_HANDLER_SERVICE_ID          60u
#define ENET_RXIRQ_HANDLER_SERVICE_ID           61u
#define ENET_TXIRQ_HANDLER_SERVICE_ID           62u
#define ENET_GET_ESTCONFIG_SERVICE_ID           63u
#define ENET_EST_CONFIG_SERVICE_ID              64u
#define ENET_EST_ENABLE_SERVICE_ID              65u
#define ENET_EST_GCLCONFIG_SERVICE_ID           66u
#define ENET_EST_GETGCLCONFIG_SERVICE_ID        67u
#define ENET_PREEMPTION_CONFIG_SERVICE_ID       68u
/** @}*/

/**
 * @name ENET DEV Error Code
 * @brief ENET DEV Error Code
 *
 * @{
 */
#define ENET_E_DRIVER_UNINIT                    0u
#define ENET_E_DRIVER_REPEAT_INIT               1u
#define ENET_E_CONTROLLER_MODE                  2u
#define ENET_E_PARAM_HANDLE                     3u
#define ENET_E_PARAM_INSTANCE                   4u
#define ENET_E_PARAM_POINTER                    5u
#define ENET_E_PARAM_TXCHANNEL                  6u
#define ENET_E_PARAM_RXCHANNEL                  7u
#define ENET_E_PARAM_GROUP                      8u
#define ENET_E_PARAM_ASSERTION                  9u
#define ENET_E_PARAM_MACLEN                     10u
#define ENET_E_PARAM_PPSCHANNEL                 11u
/** @}*/

/** @brief ENET DMA descriptor length */
#define ENET_DATA_BUS_WIDTH_BYTES               (ENET_DATA_BUS_WIDTH_BITS / 8u)
/** @brief ENET DMA descriptor length */
#define ENET_DMA_DESC_LEN_BYTES                 (16u)
/** @brief Max Ethernet frame length */
#define ENET_MAX_FRAME_LENGTH                   1536u
/** @brief Ethernet MAC address length */
#define ENET_MAC_ADDRESS_LENGTH                 6u

/** @brief ENET Boolean true */
#define ENET_TRUE                               (bool)1u
/** @brief ENET Boolean false */
#define ENET_FALSE                              (bool)0u

/** @brief ENET data barrier */
#define ENET_DATA_BARRIER()                     DMB()

/** @brief TDESC2 Interrupt Enabled on Completion in transmit descriptor 2 read format */
#define ENET_TDES2_IOC_MASK                     (0x80000000u)
/** @brief TDESC2 Transmit Timestamp Enable in transmit descriptor 2 read format */
#define ENET_TDES2_TTSE_MASK                    (0x40000000u)
/** @brief TDESC2 VLAN Tag Insertion or Replacement in transmit descriptor 2 read format */
#define ENET_TDES2_VTIR(x)                      (((uint32_t)(((uint32_t)(x)) << 14u)) & 0x0000C000u)
/** @brief TDESC2 Header Length or Buffer 1 Length in transmit descriptor 2 read format */
#define ENET_TDES2_BUFFER1_LEN(x)               (((uint32_t)(((uint32_t)(x)) << 0u)) & 0x00003FFFu)
/** @brief TDESC2 Buffer 2 Length in transmit descriptor 2 read format */
#define ENET_TDES2_BUFFER2_LEN(x)               (((uint32_t)(((uint32_t)(x)) << 16u)) & 0x3FFF0000u)

/** @brief CRC Pad Control in transmit descriptor 3 read format */
#define ENET_TDES3_CPC(x)                       (((uint32_t)(((uint32_t)(x)) << 26u)) & 0x0C000000u)
/** @brief Checksum Insertion Control in transmit descriptor 3 read format */
#define ENET_TDES3_CIC(x)                       (((uint32_t)(((uint32_t)(x)) << 16u)) & 0x00030000u)
/** @brief First Descriptor in transmit descriptor 3 read format */
#define ENET_TDES3_FD_MASK                      (0x20000000u)
/** @brief Last Descriptor in transmit descriptor 3 read format */
#define ENET_TDES3_LD_MASK                      (0x10000000u)
/** @brief TCP/UDP Header Length in transmit descriptor 3 read format */
#define ENET_TDES3_THL(x)                       (((uint32_t)(((uint32_t)(x)) << 19u)) & 0x00780000u)
/** @brief TCP Segmentation Enable in transmit descriptor 3 read format */
#define ENET_TDES3_TSE_MASK                     (0x00040000u)
/** @brief TCP Payload Length mask in transmit descriptor 3 read format */
#define ENET_TDES3_TPL_MASK                     (0x0003FFFFu)
/** @brief TCP Payload Length in transmit descriptor 3 read format */
#define ENET_TDES3_TPL(x)                       (((uint32_t)(((uint32_t)(x)) << 0u)) & 0x0003FFFFu)
/** @brief Frame Length mask in transmit descriptor 3 read format */
#define ENET_TDES3_FL_MASK                      (0x00007FFFu)
/** @brief Frame Length in transmit descriptor 3 read format */
#define ENET_TDES3_FL(x)                        (((uint32_t)(((uint32_t)(x)) << 0u)) & 0x00007FFFu)

/** @brief Tx Timestamp Status in transmit descriptor 3 write back format */
#define ENET_TDES3_TTSS_MASK                    (0x00020000u)

/** @brief Inner VLAN Tag in transmit descriptor 2 context format */
#define ENET_TDES2_IVT(x)                       (((uint32_t)(((uint32_t)(x)) << 16u)) & 0xFFFF0000u)
/** @brief Maximum Segment Size in transmit descriptor 2 context format */
#define ENET_TDES2_MSS(x)                       (((uint32_t)(((uint32_t)(x)) << 0u)) & 0x00003FFFu)

/** @brief One-Step Timestamp Correction Input or MSS Valid in transmit descriptor 3 context format */
#define ENET_TDES3_TCMSSV_MASK                  (0x04000000u)
/** @brief Inner VLAN Tag Insert or Replace in transmit descriptor 3 context format */
#define ENET_TDES3_IVTIR(x)                     (((uint32_t)(((uint32_t)(x)) << 18u)) & 0x000C0000u)
/** @brief Inner VLAN Tag Valid in transmit descriptor 3 context format */
#define ENET_TDES3_IVLTV_MASK                   (0x00020000u)
/** @brief VLAN Tag Valid in transmit descriptor 3 context format */
#define ENET_TDES3_VLTV_MASK                    (0x00010000u)
/** @brief VLAN Tag in transmit descriptor 3 context format */
#define ENET_TDES3_VT(x)                        (((uint32_t)(((uint32_t)(x)) << 0u)) & 0x0000FFFFu)

/** @brief Interrupt Enabled on Completion in receive descriptor 3 read format */
#define ENET_RDES3_IOC_MASK                     (0x40000000u)
/** @brief Buffer 1 Address Valid in receive descriptor 3 read format */
#define ENET_RDES3_BUFFER1_VALID_MASK           (0x01000000u)
/** @brief Buffer 2 Address Valid in receive descriptor 3 read format */
#define ENET_RDES3_BUFFER2_VALID_MASK           (0x02000000u)

/** @brief Inner VLAN Tag mask in receive descriptor 0 write back format */
#define ENET_RDES0_INNER_VLAN_TAG_MASK          (0xFFFF0000u)
/** @brief Inner VLAN Tag shift in receive descriptor 0 write back format */
#define ENET_RDES0_INNER_VLAN_TAG_SHIFT         (16u)
/** @brief Outer VLAN Tag mask in receive descriptor 0 write back format */
#define ENET_RDES0_OUTER_VLAN_TAG_MASK          (0x0000FFFFu)

/** @brief Timestamp Available in receive descriptor 1 write back format */
#define ENET_RDES1_TIMESTAMP_AVAILABLE_MASK     (0x00004000u)
/** @brief IP Payload Error in receive descriptor 1 write back format */
#define ENET_RDES1_IP_PAYLOAD_ERROR_MASK        (0x00000080u)
/** @brief IPv6 header Present in receive descriptor 1 write back format */
#define ENET_RDES1_IPV6_HEADER_MASK             (0x00000020u)
/** @brief IPV4 Header Present in receive descriptor 1 write back format */
#define ENET_RDES1_IPV4_HEADER_MASK             (0x00000010u)
/** @brief IP Header Error in receive descriptor 1 write back format */
#define ENET_RDES1_IP_HEADER_ERROR_MASK         (0x00000008u)
/** @brief Payload Type in receive descriptor 1 write back format */
#define ENET_RDES1_IP_PAYLOAD_TYPE_MASK         (0x00000007u)

/** @brief First Descriptor in receive descriptor 3 write back format */
#define ENET_RDES3_FD_MASK                      (0x20000000u)
/** @brief Last Descriptor in receive descriptor 3 write back format */
#define ENET_RDES3_LD_MASK                      (0x10000000u)
/** @brief Packet Length in receive descriptor 3 write back format */
#define ENET_RDES3_PACKET_LENGTH_MASK           (0x00007FFFu)
/** @brief Receive Status RDES0 Valid in receive descriptor 3 write back format */
#define ENET_RDES3_RDES0_VALID_MASK             (0x02000000u)
/** @brief Receive Status RDES1 Valid in receive descriptor 3 write back format */
#define ENET_RDES3_RDES1_VALID_MASK             (0x04000000u)
/** @brief Receive Status RDES2 Valid in receive descriptor 3 write back format */
#define ENET_RDES3_RDES2_VALID_MASK             (0x08000000u)

/** @brief Own Bit for all format */
#define ENET_DES3_OWN_MASK                      (0x80000000u)
/** @brief Context Descriptor bit for all format */
#define ENET_DES3_CTXT_MASK                     (0x40000000u)

/**
 * @brief ENET instances
 *
 */
typedef enum
{
    ENET_INSTANCE_0 = 0x0u
} ENET_InstanceType;

/**
 * @brief ENET channel index type
 *
 */
typedef enum
{
    ENET_CHANNEL_0 = ENET_DMA_CHANNEL_0,
    ENET_CHANNEL_1 = ENET_DMA_CHANNEL_1
} ENET_ChannelType;

/**
 * @brief ENET operation return values type
 *
 */
typedef enum
{
    ENET_STATUS_SUCCESS         = 0x00u,   /**< The ENET operation is succeed */
    ENET_STATUS_ERROR           = 0x01u,   /**< The ENET operation is failed */
    ENET_STATUS_BUSY            = 0x02u,   /**< The ENET operation is failed because ENET is busy */
    ENET_STATUS_TIMEOUT         = 0x03u,   /**< The ENET operation is failed because of time out */
    ENET_STATUS_INVALID_PARAM   = 0x04u,   /**< The ENET operation is failed because of the param is invalid */
    ENET_STATUS_UNSUPPORTED     = 0x05u,   /**< The ENET configuration parameter is unsupported */
    ENET_STATUS_NOT_READY       = 0x06u    /**< The ENET operation is not ready */
} ENET_StatusType;

/**
 * @brief ENET driver state values type
 *
 */
typedef enum
{
    ENET_STATE_UNINIT = 0u,                 /**< The ENET driver not initialized */
    ENET_STATE_INITIALIZED,                 /**< The ENET driver initialized */
    ENET_STATE_READY,                       /**< The ENET driver is ready for transmission and reception */
    ENET_STATE_BUSY,                        /**< The ENET driver is busy for transmission for reception */
    ENET_STATE_STOPPED,                     /**< The ENET driver is stopped */
    ENET_STATE_ERROR,                       /**< The ENET driver error occurred */
    ENET_STATE_WAIT_RELEASE                 /**< The ENET driver wait Enet_BuildRxDescriptors */
} ENET_StateType;

/**
 * @brief ENET DMA system bus mode type
 *
 */
typedef enum
{
    ENET_DMA_SYSBUS_MODE_FIXED = 0x0u,
    ENET_DMA_SYSBUS_MODE_MIXED = 0x1u
} ENET_DMA_SysbusModeType;

/**
 * @brief The burst length for DMA TX and RX
 *
 */
typedef enum
{
    ENET_DMA_BURST_LENGTH_1_BEAT    = 1u,
    ENET_DMA_BURST_LENGTH_2_BEATS   = 2u,
    ENET_DMA_BURST_LENGTH_4_BEATS   = 4u,
    ENET_DMA_BURST_LENGTH_8_BEATS   = 8u,
    ENET_DMA_BURST_LENGTH_16_BEATS  = 16u,
    ENET_DMA_BURST_LENGTH_32_BEATS  = 32u,
    ENET_DMA_BURST_LENGTH_64_BEATS  = 64u,
    ENET_DMA_BURST_LENGTH_128_BEATS = 128u,
    ENET_DMA_BURST_LENGTH_256_BEATS = 256u
} ENET_DMABurstLengthType;

/**
 * @brief ENET general event type
 *
 */
typedef enum
{
    ENET_EVENT_NONE    = 0u,
    ENET_EVENT_TARGET_TIME0_REACHED,        /**< PTP PPS target time register0 reached */
    ENET_EVENT_TARGET_TIME0_ERROR,          /**< PTP PPS target time register0  elapsed */
    ENET_EVENT_TARGET_TIME1_REACHED,        /**< PTP PPS target time register1 reached */
    ENET_EVENT_TARGET_TIME1_ERROR,          /**< PTP PPS target time register1 elapsed */
    ENET_EVENT_TARGET_TIME2_REACHED,        /**< PTP PPS target time register2 reached */
    ENET_EVENT_TARGET_TIME2_ERROR,          /**< PTP PPS target time register2 elapsed */
    ENET_EVENT_TARGET_TIME3_REACHED,        /**< PTP PPS target time register3 reached */
    ENET_EVENT_TARGET_TIME3_ERROR,          /**< PTP PPS target time register3 elapsed */
    ENET_EVENT_MMC_TX_COUNTER,              /**< MMC TX counters interrupt is triggered,
                                                 user must call Enet_GetMMCTxInterrupts to get the interrupt source,
                                                 and call Enet_GetMMCTxCounter to clear the MMC interrupt bit */
    ENET_EVENT_MMC_RX_COUNTER,              /**< MMC TX counters interrupt is triggered,
                                                 user must call Enet_GetMMCTxInterrupts to get the interrupt source,
                                                 and call Enet_GetMMCRxCounter to clear the MMC interrupt bit */
} ENET_EventType;

typedef struct ENET_DrvHandle ENET_HandleType;

/**
 * @brief Callback function invoked when a general event is encountered
 *
 */
typedef ENET_StatusType(*ENET_EventCallbackType)(const ENET_HandleType *pEnetHandle, ENET_EventType eEvent);

/** @brief Callback function invoked when a channel event is encountered */
typedef ENET_StatusType(*ENET_ChannelCallbackType)(const ENET_HandleType *pEnetHandle, const uint8 u8Channel);


/**
 * @brief Mdio operation type
 *
 */
typedef enum
{
    ENET_MII_WRITE = ENET_MAC_MDIO_ADDRESS_GOC_0_MASK,
    ENET_MII_READ_INCREMENT = ENET_MAC_MDIO_ADDRESS_GOC_1_MASK,
    ENET_MII_READ = ENET_MAC_MDIO_ADDRESS_GOC_1_MASK | ENET_MAC_MDIO_ADDRESS_GOC_0_MASK
} ENET_MiiOptType;

/**
 * @brief Descriptor TX and RX attributes type
 *
 */
typedef enum
{
    /** TX Option Attributes */
    ENET_TX_ATTRIBUTES_CRC_PAD_CTRL             = 0x00000001u,      /**< CRC and PAD insertion. */
    ENET_TX_ATTRIBUTES_SA_INSERTION             = 0x00000002u,      /**< Source MAC address insertion. */
    ENET_TX_ATTRIBUTES_TCP_SEGMENTATION         = 0x00000004u,      /**< TCP segmentation not supported by hardware. */
    ENET_TX_ATTRIBUTES_CHECKSUM_INSERTION       = 0x00000008u,      /**< Checksum insertion control. */
    ENET_TX_ATTRIBUTES_VLAN_TAG_CTRL            = 0x00000010u,      /**< Add outer VLAN tag. */
    ENET_TX_ATTRIBUTES_INNER_VLAN_TAG_CTRL      = 0x00000020u,      /**< Add inner VLAN tag. */
    ENET_TX_ATTRIBUTES_TIMESTAMP_SNAPSHOOT      = 0x80000000u,      /**< Enable TX PTP packet snap shoot. */

    /** TX Result Attributes */
    ENET_TX_ATTRIBUTES_TIMESTAMP_VALID          = 0x80000000u,      /**< Transmitted PTP packet time stamp valid. */

    /** RX Attributes */
    ENET_RX_ATTRIBUTES_TIMESTAMP_VALID          = 0x80000000u       /**< Received PTP packet time stamp valid. */

} ENET_AttributeType;

/**
 * @brief TX descriptor CRC and Pad insertion control type
 *
 */
typedef enum
{
    ENET_CRC_AND_PAD_INSERTION = 0u,  /**< Appends the CRC at the end of the transmitted packet of length greater than or equal
                                           to 60 bytes. Appends padding and CRC to a packet with length less than 60 bytes.*/
    ENET_CRC_INSERTION         = 1u,  /**< Appends the CRC at the end of the transmitted packet but it does not append padding.
                                           The application should ensure that the padding bytes are present in the packet being transferred. */
    ENET_CRC_INSERTION_DISABLE = 2u,  /**< Does not append the CRC at the end of the transmitted packet. The application should
                                           ensure that the padding and CRC bytes are present in the packet being transferred. */
    ENET_CRC_REPLACEMENT       = 3u   /**< Replaces the last four bytes of the transmitted packet with recalculated CRC bytes.
                                           The application should ensure that the padding and CRC bytes are present in the packet being transferred. */
} ENET_TxDescCrcPadType;

/**
 * @brief TX descriptor Checksum insertion control type
 *
 */
typedef enum
{
    ENET_CHECKSUM_INSERTION_DISABLE          = 0u,  /**< Checksum insertion is disabled. */
    ENET_CHECKSUM_INSERTION_IP               = 1u,  /**< IP header checksum calculation and insertion are enabled. */
    ENET_CHECKSUM_INSERTION_PROTO_NO_PSEUDOH = 2u,  /**< Protocol checksum calculation and insertion are enabled,
                                                         but pseudo-header checksum is not calculated in hardware. */
    ENET_CHECKSUM_INSERTION_PROTO_PSEUDOH    = 3u   /**< Protocol checksum calculation and insertion are enabled,
                                                         and pseudo-header checksum is calculated in hardware. */
} ENET_TxDescChecksumType;

/**
 * @brief ENET filter enable type
 *
 */
typedef enum
{
    ENET_FILTER_DISABLE        = 0u,    /**< Disable filter,all packets are forwarded to the application */
    ENET_FILTER_ENABLE         = 1u,    /**< Enable filter,the matched packets are forwarded to the application */
    ENET_FILTER_INVERSE_ENABLE = 2u     /**< Enable inverse filter,the packets match failed are forwarded to the application */
} ENET_FilterEnableType;

/**
 * @brief ENET filter mode type
 *
 */
typedef enum
{
    ENET_VLAN_FILTER_OUTER_CVLAN   = 0u,    /**< Outer VLAN Tag Comparison,only filter packets with C-VLAN tag  */
    ENET_VLAN_FILTER_OUTER_SVLAN   = 1u,    /**< Outer VLAN Tag Comparison,only filter packets with S-VLAN tag  */
    ENET_VLAN_FILTER_INNER_CVLAN   = 2u,    /**< Inner VLAN Tag Comparison,only filter packets with C-VLAN tag  */
    ENET_VLAN_FILTER_INNER_SVLAN   = 3u,    /**< Inner VLAN Tag Comparison,only filter packets with S-VLAN tag  */
    ENET_VLAN_FILTER_OUTER_ANYTYPE = 4u,    /**< Outer VLAN Tag Comparison, do not check VLAN type */
    ENET_VLAN_FILTER_INNER_ANYTYPE = 5u     /**< Inner VLAN Tag Comparison, do not check VLAN type */
} ENET_VLANFilterModeType;

/**
 * @brief ENET DMA descriptor type
 *
 */
typedef struct
{
    __IO uint32_t Des0;
    __IO uint32_t Des1;
    __IO uint32_t Des2;
    __IO uint32_t Des3;
    uint32_t BackupInfo0;
    uint32_t BackupInfo1;
} ENET_DMADescType;

/**
 * @brief Mdio configuration type
 *
 */
typedef struct
{
    bool PreambleSuppress;      /**< MAC_MDIO_ADDRESS[27] Preamble Suppression Enable  */
    bool BackToBack;            /**< MAC_MDIO_ADDRESS[26] Back to Back transactions */
    uint8_t TrailingClocks;     /**< MAC_MDIO_ADDRESS[14:12] Number of Training Clocks */
} ENET_MiiConfigType;

/**
 * @brief IEEE1588 time stamp type
 *
 */
typedef struct
{
    uint32_t Nanoseconds;  /**< Nanoseconds part of the time. */
    uint32_t Seconds;      /**< The 32 least significant bits of the 48 bits seconds part of the time. */
    uint16_t SecondsHi;    /**< The 16 most significant bits of the 48 bit seconds part of the time. */
} ENET_TimestampType;

/**
 * @brief IEEE1588 flexible PPS configuration type
 *
 */
typedef struct
{
    ENET_MAC_PPSCmdType Cmd;        /**< Flexible PPS CMD */
    ENET_TimestampType TargetTime;  /**< Flexible PPS target time,SecondsHi value is ignored */
    uint32_t PPSInterval;           /**< The interval between the rising edges of Flexible PPS in nanoseconds */
    uint32_t PPSWidth;              /**< The width between the rising edge and falling edge of Flexible PPS,in nanoseconds */
} ENET_FlexPPSConfigType;

/**
 * @brief IEEE1588 time stamp configuration type
 *
 */
typedef struct Enet_PTPConfig
{
    bool OneStepMode;                               /**< PTP run in one step mode,currently not supported. */
    bool Av8021ASMode;                              /**< MAC_TIMESTAMP_CONTROL[28] AV 802.1AS mode enable */
    bool MacFilterForPtp;                           /**< MAC_TIMESTAMP_CONTROL[18] Enable MAC filter for PTP frames over ethernet */
    bool TimeStampForAll;                           /**< MAC_TIMESTAMP_CONTROL[8] Enable Timestamp For All Packets */
    bool PresentationTimeGen;                       /**< MAC_TIMESTAMP_CONTROL[6] Presentation Time Generation Enable */
    uint8_t IncrementStep;                          /**< PTP system time increment step in nanoseconds */
    ENET_MAC_TxTimestampStatusModeType TXTSSTSM;    /**< MAC_TIMESTAMP_CONTROL[24] Transmit Timestamp Status Mode */
    ENET_MAC_PTPSnapshotMsgType SnapshotType;       /**< MAC_TIMESTAMP_CONTROL[17:14] Enable the frame type for time snapshotting */
    ENET_MAC_PTPPacketLayerType PtpLayer;           /**< MAC_TIMESTAMP_CONTROL[13:11] Snapshot for ethernet packet layer */
    ENET_MAC_PTPVersionType PtpVersion;             /**< MAC_TIMESTAMP_CONTROL[10] IEEE1588 version */
    ENET_MAC_TimestampRolloverType RolloverMode;    /**< MAC_TIMESTAMP_CONTROL[9] Time counter roll over mode */
    ENET_MAC_TimestampUpdateMethodType UpdateMethod;/**< MAC_TIMESTAMP_CONTROL[1] Time stamp update mode */
    ENET_MAC_PTPClkSelType ClkSource;               /**< PTP reference clock source(PCC, TXCLK or reference clock pin input)
                                                         If the PCC clock is selected, the PCC_ENET clock must be enabled,
                                                         and if reference pin input is selected, the parameter
                                                         RefClkPinInputFreq must be assigned a frequency value */
#if ENET_SUPPORT_REFCLK_PIN
    uint32_t RefClkPinInputFreq;                    /**< PTP reference clock pin input frequency */
#endif
    ENET_TimestampType InitTime;                    /**< The time stamp for Initialization */
} Enet_PTPConfigType;

/**
 * @brief Defines MMC counter configuration
 *
 */
typedef struct ENET_MMCConfig
{
    bool UpdateDropedBroadcast;                     /**< MMC_CONTROL[8] Update MMC counters for dropped broadcast packets */
    bool ResetOnRead;                               /**< MMC_CONTROL[2] MMC counters are reset to zero after read */
    bool CounterRollover;                           /**< MMC_CONTROL[1] MMC counters roll over to zero after reaching the maximum value */
    ENET_MAC_MmcCntPresetLevelType  PresetLevel;    /**< MMC_CONTROL[5] Enable MMC counters preset to almost-full value */
    uint32_t MmcTxCntIntEn;                         /**< MMC_TX_INTERRUPT_MASK[25:0] Enable MMC TX counters interrupts,
                                                         each bit represents an event of Enet_MMCTxCounterType */
    uint32_t MmcRxCntIntEn;                         /**< MMC_RX_INTERRUPT_MASK[25:0] Enable MMC RX counters interrupts,
                                                         each bit represents an event of Enet_MMCRxCounterType */
} ENET_MMCConfigType;

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief ENET EST configuration type
 *
 */
typedef struct ENET_EstConfig
{
    uint8_t Overhead;                                     /**< MTL_EST_EXT_CONTROL[5:0] Overhead Bytes Value */
    uint8_t PtpTimeOffset;                                /**< MTL_EST_CONTROL[31:24] PTP time offset value */
    uint16_t CurrentTimeOffset;                           /**< MTL_EST_CONTROL[23:12] Current Time Offset Value */
    ENET_MTL_GCLIntervalMultipleType IntervalLeftShift;   /**< MTL_EST_CONTROL[10:8] Time Interval Left Shift Amount */
    ENET_MTL_ScheduleErrorLoopCountType SchedErrLoopCount;/**< MTL_EST_CONTROL[7:6] Loop count to report scheduling error */
    bool DropSchedErrFrame;                               /**< MTL_EST_CONTROL[5] Drop frames causing Scheduling error,
                                                               due to the bug in 5.20a errata, this parameter shell always be false */
    bool NotDropFrameSizeErr;                             /**< MTL_EST_CONTROL[4] Do not Drop frames during Frame Size Error,
                                                               due to the bug in 5.20a errata, this parameter shell always be true */
} ENET_EstConfigType;

/**
 * @brief The ENET EST Gate control type
 *
 */
typedef struct ENET_GateCtrl
{
    bool GateOpen[ENET_CHANNEL_COUNT];  /**< Gate state, bit 0 - channel 0, bit 1- channel 1 */
    uint32_t TimeInterval;              /**< Gate control time interval (24 bits value) */
} ENET_GateCtrlType;

/**
 * @brief The ENET EST Gate control List type
 *
 */
typedef struct ENET_GateCtrlList
{
    uint32_t BaseTimeS;                         /**< Base time seconds */
    uint32_t BaseTimeNs;                        /**< Base time nanoseconds */
    uint8_t CycleTimeS;                         /**< Cycle time seconds */
    uint32_t CycleTimeNs;                       /**< Cycle time nanoseconds */
    uint32_t TimeExtension;                     /**< Time extension in nanoseconds */
    uint16_t GclLength;                         /**< The length of gate control List */
    ENET_GateCtrlType Gate[ENET_TSN_GCL_DEPTH]; /**< The gate control List */
} ENET_GateCtrlListType;

/**
 * @brief ENET Frame Preemption Classification type
 *
 */
typedef enum
{
    ENET_CLISSIFICATION_EXPRESS     = 0u, /**< MTL Queue is classified as express */
    ENET_CLISSIFICATION_PREEMPTABLE = 1u  /**< MTL Queue is classified as preemptable */
} ENET_QueueClassificType;

/**
 * @brief The ENET EST Frame Preemption configuration  type
 *
 */
typedef struct ENET_PreemptionConfig
{
    bool PreemptionEnable;                                      /**< Enable frame preemption */
    ENET_QueueClassificType Classification[ENET_CHANNEL_COUNT]; /**< Preemption Classification */
    uint16_t ReleaseAdvance;                                    /**< The maximum time in nanoseconds that can elapse between
                                                                     issuing a RELEASE to the MAC and the MAC being ready to
                                                                     resume transmission of preemptable frames */
    uint16_t HoldAdvance;                                       /**< The maximum time in nanoseconds that can elapse between
                                                                     issuing a HOLD to the MAC and the MAC ceasing to transmit
                                                                     any preemptable frame */
} ENET_PreemptionConfigType;
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief Defines the buffer type for ENET driver
 *
 */
typedef struct ENET_Buffer
{
    struct ENET_Buffer *Next;   /**< Pointer to the next buffer,the buffer chain should be ended with NULL */
    uint8 *Data;                /**< Pointer to the data buffer */
    uint16 Length;              /**< Length of the current buffer */
    uint16 TotalLength;         /**< Total length of the buffer chain,TotalLength is valid for the first buffer */
} ENET_BufferType;

/**
 * @brief ENET transmit VLAN configuration type
 *
 */
typedef struct ENET_TxVlanConfig
{
    ENET_MAC_VLANTagCtrlType VlanCtrl;               /**< VLAN tag control : delete insert or replace */
    ENET_MAC_VLANType VlanType;                      /**< VLAN type : C-VLAN or S-VLAN */
    uint16_t VlanTag;                                /**< VLAN type tag value */
} ENET_TxVlanConfigType;

/**
 * @brief ENET Channel based VLAN insertion type
 *
 */
typedef struct ENET_OuterVlanCBTI
{
    ENET_MAC_VLANType VlanType[ENET_CHANNEL_COUNT];  /**< VLAN type for ENET_CHANNEL_0 ~ ENET_CHANNEL_1 : C-VLAN or S-VLAN */
    uint16_t VlanTag[ENET_CHANNEL_COUNT];            /**< VLAN tag for ENET_CHANNEL_0 ~ ENET_CHANNEL_1 */
} ENET_OuterVlanCBTIType;

/**
 * @brief Defines the options for the Tx packet
 *
 */
typedef struct ENET_TxOption
{
    uint32_t Attributes;                    /**< Send attributes defined in ENET_AttributeType */
    ENET_TimestampType TimeStamp;           /**< Transmitted frame time stamp,available for ENET_TX_ATTRIBUTES_TIMESTAMP_SNAPSHOOT*/
    ENET_TxDescCrcPadType CrcPadCtrl;       /**< CRC pad control,available for ENET_TX_ATTRIBUTES_CRC_PAD_CTRL */
    ENET_TxDescChecksumType CheckSumCtrl;   /**< Checksum control,available for ENET_TX_ATTRIBUTES_CHECKSUM_INSERTION */
    ENET_TxVlanConfigType VlanConfig;       /**< VLAN tag control,available for ENET_TX_ATTRIBUTES_VLAN_TAG_CTRL */
    ENET_TxVlanConfigType InnerVlanConfig;  /**< Inner VLAN tag control,available for ENET_TX_ATTRIBUTES_INNER_VLAN_TAG_CTRL */
} ENET_TxOptionType;

/**
 * @brief Defines the received buffer information
 *
 */
typedef struct ENET_RxInfo
{
    uint32_t Attributes;            /**< Receive attributes defined in ENET_AttributeType */
    ENET_TimestampType TimeStamp;   /**< Time stamp snapshot for the received packet */
} ENET_RxInfoType;

/**
 * @brief DMA descriptor list type for internal use by ENET driver
 *
 */
typedef struct ENET_DescList
{
    ENET_DMADescType *DescList;     /**< DMA descriptor list start address */
    uint16_t BufferLen;             /**< DMA descriptor buffer length */
    uint16_t RingSize;              /**< Number of DMA descriptors in DescList */
    ENET_DMADescType *FirstDesc;    /**< First descriptor used by ENET driver */
    ENET_DMADescType *LastDesc;     /**< Last descriptor used by ENET driver */
} ENET_DescListType;

/**
 * @brief DMA channel configuration type
 *
 */
typedef struct ENET_DMAChannelConfig
{
    ENET_DMABurstLengthType BurstLength;/**< Assumption transmit BurstLength = receive BurstLength */
    bool EnhancedDescriptor;            /**< DMA_CHn_TX_CONTROL[28] Enhanced Descriptor Enable, Not supported yet */
    bool EarlySendIntEnable;            /**< DMA_CHn_TX_CONTROL[22] Enable early transmit interrupt */
    bool OperateSecondPacket;           /**< DMA_CHn_TX_CONTROL[4] Enable operation on second packet for transmission */
    uint8_t TxChannelWeight;            /**< DMA_CHn_TX_CONTROL[3:1] Transmit Channel Weight,range 0 ~ 7 */
    bool EarlyReceiveIntEnable;         /**< DMA_CHn_RX_CONTROL[22] Enable early receive interrupt */
} ENET_DMAChannelConfigType;

/**
 * @brief ENET DMA configuration type
 *
 */
typedef struct ENET_DMAConfig
{
    ENET_DMA_PriorityRatioType PriorityRatio;           /**< DMA_MOD[14:12] Priority Ratio between transmit and receive */
    ENET_DMA_PriorityModeType PriorityMode;             /**< DMA_MOD[11] Priority mode between transmit and receive */
    ENET_DMA_TxArbitrationAlgorithmType TxArbitration;  /**< DMA_MOD[4:2] Arbitration mode between the transmit channels */
    ENET_DMA_ArbitrationSchemeType TxRxArbitration;     /**< DMA_MOD[1] Arbitration mode between the transmit and receive */
    ENET_DMA_BurstModeType BurstMode;                   /**< DMA_SYSBUS_MOD[14,0] Burst length mode */
    bool RebuildINCRxBurst;                             /**< DMA_SYSBUS_MOD[15] Enable rebuild INCRx burst */
    bool AddressAlignedBeats;                           /**< DMA_SYSBUS_MOD[12] Enable address-aligned beats */
    ENET_DMAChannelConfigType ChannelConfigs[ENET_CHANNEL_COUNT];
} ENET_DMAConfigType;

/**
 * @brief ENET MAC filter configuration type
 *
 */
typedef struct ENET_MACFilter
{
    bool ReceiveAll;                               /**< MAC_PACKET_FILTER[31] Receive all packets to the application */
    bool PromiscuousMode;                          /**< MAC_PACKET_FILTER[0] Enable promiscuous mode */
    bool DropNonTcpUdpOverIp;                      /**< MAC_PACKET_FILTER[21] Drop Non-TCP/UDP Over IP Packets */
    bool HashOrPerfectFilter;                      /**< MAC_PACKET_FILTER[10] Hash Or Perfect Filter Enable */
    ENET_FilterEnableType SAFilter;                /**< MAC_PACKET_FILTER[9:8] Source Address Filter type */
    ENET_FilterEnableType DAFilter;                /**< MAC_PACKET_FILTER[3] Source Address Filter type */
    ENET_MAC_CtrlPacketFilterModeType PassCtrlPkts;/**< MAC_PACKET_FILTER[7:6] Control packets filter mode */
    bool DisableBroadcast;                         /**< MAC_PACKET_FILTER[5] Disable Broadcast Packets */
    bool PassAllMulticast;                         /**< MAC_PACKET_FILTER[4] Pass All Multicast */
    bool HashMulticast;                            /**< MAC_PACKET_FILTER[2] Enable Hash Table Filter for Multicast Packets */
    bool HashUnicast;                              /**< MAC_PACKET_FILTER[1] Enable Hash Table Filter for Unicast Packets */
} ENET_MACFilterType;

/**
 * @brief ENET Layer3 Layer4 filter configuration type
 *
 */
typedef struct ENET_L3L4Filter
{
    bool DMAChannelSelect;                  /**< MAC_L3_L4_CONTROLn[28] Enable DMA channel select for the filter */
    ENET_ChannelType DMAChannel;            /**< MAC_L3_L4_CONTROLn[24] The DMA channel number for the filter */
    ENET_MAC_Layer4ProtocolType L4Protocol; /**< MAC_L3_L4_CONTROLn[16] The TCP/UDP protocol for the layer4 filter */
    ENET_FilterEnableType DstPortFilter;    /**< MAC_L3_L4_CONTROLn[21:20] The destination port filter mode */
    ENET_FilterEnableType SrcPortFilter;    /**< MAC_L3_L4_CONTROLn[19:18] The source port filter mode */
    uint16_t DstPort;                       /**< MAC_LAYER4_ADDRESSn[31:16] The destination port in little-endian */
    uint16_t SrcPort;                       /**< MAC_LAYER4_ADDRESSn[15:0] The source port in little-endian */
    ENET_MAC_Layer3ProtocolType L3Protocol; /**< MAC_L3_L4_CONTROLn[0] The IPV4/IPV6 protocol for the layer3 filter */
    ENET_FilterEnableType DstIPFilter;      /**< MAC_L3_L4_CONTROLn[5:4] The destination IP address filter mode */
    ENET_FilterEnableType SrcIPFilter;      /**< MAC_L3_L4_CONTROLn[3:2] The source IP address filter mode */
    uint8_t Ipv4DAMaskBit;                  /**< MAC_L3_L4_CONTROLn[15:11] The number of ipv4 destination address lower bits mask,
                                                 the filter will match the higher bits that are not masked */
    uint8_t Ipv4SAMaskBit;                  /**< MAC_L3_L4_CONTROLn[10:6] The number of ipv4 source address lower bits mask,like Ipv4DAMaskBit */
    uint8_t Ipv6MaskBit;                    /**< MAC_L3_L4_CONTROLn[12:6] The number of ipv6 address lower bits mask,like Ipv4DAMaskBit */
    uint32_t IPv4DstAddr;                   /**< MAC_LAYER3_ADDRn_REG1[31:0] Ipv4 destination IP address in little-endian
                                                 To match"224.0.0.1", ipv4 address must be 0xE0000001 */
    uint32_t IPv4SrcAddr;                   /**< MAC_LAYER3_ADDRn_REG0[31:0] Ipv4 source IP address in little-endian, like IPv4DstAddr */
    uint8_t IPv6Addr[16u];                  /**< MAC_LAYER3_ADDRn_REG0~4 Ipv6 IP address  */
} ENET_L3L4FilterType;

/**
 * @brief ENET VLAN filter configuration type
 *
 */
typedef struct ENET_VlanFilterConfig
{
    bool VlanFilterEnable;                          /**< MAC_PACKET_FILTER[16] Enable inner VLAN tag in RX status */
    bool InnerVlanRxStatus;                         /**< MAC_PACKET_FILTER[31] Enable inner VLAN tag in RX status */
    bool OuterVlanRxStatus;                         /**< MAC_VLAN_TAG_CTR[24] Enable outer VLAN tag in RX status */
    bool DoubleVlanEnable;                          /**< MAC_VLAN_TAG_CTR[26] Enable double VLAN processing */
    bool SVlanEnable;                               /**< MAC_VLAN_TAG_CTR[18] Enable S-VLAN processing */
    bool VlanInverseMatch;                          /**< MAC_VLAN_TAG_CTR[17] Enable VLAN tag inverse match */
    bool HashFilterEnable;                          /**< MAC_VLAN_TAG_CTR[25] Enable VLAN hash table filtering */
    ENET_MAC_VLANCompareType HashCompareMode;       /**< MAC_VLAN_TAG_CTR[16] VLAN tag hash compare mode, 16bits or 12 bits comparison */
    ENET_VLANFilterModeType HashFilterMode;         /**< MAC_VLAN_TAG_CTR[27,20,19] VLAN hash table filter mode */
    ENET_MAC_VLANTagStripModeType InnerVlanStrip;   /**< MAC_PACKET_FILTER[29:28] Stripping operation on the inner VLAN tag */
    ENET_MAC_VLANTagStripModeType OuterVlanStrip;   /**< MAC_PACKET_FILTER[22:21] Stripping operation on the outer VLAN tag */
} ENET_VlanFilterConfigType;

/**
 * @brief ENET VLAN perfect filter type
 *
 */
typedef struct ENET_VlanPerfectFilter
{
    bool FilterGroupEnable;                 /**< MAC_VLAN_TAG_DATA[16] VLAN perfect filter group enable */
    bool DMAChannelEnable;                  /**< MAC_VLAN_TAG_DATA[24] Enable DMA channel select for VLAN tag filter */
    uint16_t VlanTag;                       /**< MAC_VLAN_TAG_DATA[15:0] VLAN tag value */
    ENET_ChannelType DMAChannel;            /**< MAC_VLAN_TAG_DATA[25] The DMA channel number for the filter */
    ENET_MAC_VLANCompareType CompareMode;   /**< MAC_VLAN_TAG_DATA[17] Compare mode, 12 bits or 16 bits comparison */
    ENET_VLANFilterModeType FilterMode;     /**< MAC_VLAN_TAG_DATA[20:18] VLAN tag filter comparison mode */
} ENET_VlanPerfectFilterType;

/**
 * @brief ENET flow control receive queue configuration type
 *
 */
typedef struct ENET_FlowControlRxQ
{
    bool RxHwFlowCtrlEnable;                              /**< MTL_RXQn_OPERATION_MODE[7] Enable hardware flow control to trigger
                                                               generation of pause packet */
    ENET_MTL_RxFlowCtrlThresholdType RxDeactiveThreshold; /**< MTL_RXQn_OPERATION_MODE[17:14] Threshold for deactivating flow control  */
    ENET_MTL_RxFlowCtrlThresholdType RxActiveThreshold;   /**< MTL_RXQn_OPERATION_MODE[11:8] Threshold for activating flow control */
} ENET_FlowControlRxQType;

/**
 * @brief ENET flow control configuration type
 *
 */
typedef struct ENET_FlowControl
{
    bool MacTxFlowCtrlEnable;                                   /**< MAC_Q0_TX_FLOW_CTRL[1] Enable MAC to transmit flow control Pause packets */
    bool ZeroQuantaPauseDisable;                                /**< MAC_Q0_TX_FLOW_CTRL[7] Disable automatic generation of zero-quanta Pause packets */
    uint16_t PauseTime;                                         /**< MAC_Q0_TX_FLOW_CTRL[31：16] Pause time field in the TX control packet */
    ENET_MAC_PauseThresholdType PauseThreshold;                 /**< MAC_Q0_TX_FLOW_CTRL[6：4] Pause threshold for automatic retransmission Pause packets */
    ENET_FlowControlRxQType RxQueueConfig[ENET_CHANNEL_COUNT];  /**< MTL receive queue configuration for hardware trigger flow control */
    bool MacRxFlowCtrlEnable;                                   /**< MAC_RX_FLOW_CTRL[0] Enable MAC to receive and handle flow control pause packets */
    bool UnicastPauseEnable;                                    /**< MAC_RX_FLOW_CTRL[1] Enable MAC to handle unicast flow control Pause packets */
} ENET_FlowControlType;

/**
 * @brief ENET MAC configuration type
 *
 */
typedef struct ENET_MACConfig
{
    ENET_MAC_SrcAddrCtrlType SrcAddrCtrl;           /**< MAC_CONFIGURATION[30:28] MAC source address insertion or replacement control */
    ENET_MAC_InterPacketGapType InterPacketGap;     /**< MAC_CONFIGURATION[26:24] The minimum inter packet gap between packets during transmission */
    bool ChecksumOffload;                           /**< MAC_CONFIGURATION[27] Checksum Offload */
    bool GiantPacketLimit;                          /**< MAC_CONFIGURATION[23] Giant packet size limit control Enable */
    bool Support2KPacket;                           /**< MAC_CONFIGURATION[22] Support for 2K packets */
    bool CrcStripForTypePkt;                        /**< MAC_CONFIGURATION[21] Enable CRC stripping for type packets */
    bool AutoPadOrCrCStrip;                         /**< MAC_CONFIGURATION[20] Automatic pad or CRC stripping */
    bool WatchDogDisable;                           /**< MAC_CONFIGURATION[19] Watchdog Disable */
    bool JabberDisable;                             /**< MAC_CONFIGURATION[17] Jabber Disable, if disabled 16383 bytes can be transmitted */
    bool JumboEnable;                               /**< MAC_CONFIGURATION[16] Jumbo Packet Enable, if enabled 9018/9022 bytes can be received */
    bool LoopbackMode;                              /**< MAC_CONFIGURATION[12] Enable MAC loopback mode */
    bool CarrierSenseBeforeTx;                      /**< MAC_CONFIGURATION[11] Enable Carrier Sense Before Transmission in Full-Duplex Mode */
    bool DisableReceiveOwn;                         /**< MAC_CONFIGURATION[10] Disable Receive Own in half-duplex mode */
    bool DisCarrierSenseDurTx;                      /**< MAC_CONFIGURATION[9] Disable Carrier Sense During Transmission */
    bool DisableRetry;                              /**< MAC_CONFIGURATION[8] Disable Retry when a collision occurs in half-duplex mode */
    ENET_MAC_BackOffLimitType BackOffLimit;         /**< MAC_CONFIGURATION[6:5] Back-Off Limit */
    bool DeferralCheck;                             /**< MAC_CONFIGURATION[4] Deferral Check enable */
    ENET_MAC_ExtInterPacketGapType ExtInterPktGap;  /**< MAC_EXT_CONFIGURATION[29:25] Extended inter-packet gap value */
    bool ExtInterPktGapEn;                          /**< MAC_EXT_CONFIGURATION[24] Extended Inter-Packet Gap Enable */
    bool PacketDuplication;                         /**< MAC_EXT_CONFIGURATION[19] Packet Duplication Control */
    bool UnicastSlowProtoDetect;                    /**< MAC_EXT_CONFIGURATION[18] Unicast Slow Protocol Packet Detect */
    bool SlowProtoDetectEnable;                     /**< MAC_EXT_CONFIGURATION[17] Slow Protocol Detection Enable */
    bool DisableCrcCheck;                           /**< MAC_EXT_CONFIGURATION[16] Disable CRC Checking for Received Packets  */
    uint16_t GiantPktSizeLimit;                     /**< MAC_EXT_CONFIGURATION[13:0] Giant Packet Size Limit */
    ENET_MACFilterType  MACFilter;                  /**< MAC_PACKET_FILTER  */
    bool ProgramWatchdogEnable;                     /**< MAC_WATCHDOG_TIMEOUT[8] Programmable Watchdog Enable */
    ENET_MAC_WDGTimerSizeType WatchdogTimeout;      /**< MAC_WATCHDOG_TIMEOUT[3:0] Programmable Watchdog Timeout */
} ENET_MACConfigType;

/**
 * @brief ENET MTL Queue configuration type
 *
 */
typedef struct ENET_MTLQueueConfig
{
    uint32_t TxFifoSize;                                 /**< MTL Transmit FIFO size in bytes */
    uint32_t RxFifoSize;                                 /**< MTL Receive FIFO size in bytes */
    ENET_MTL_QueueEnableType TxQueueEnable;              /**< MTL_TXQn_OPERATION_MODE[3:2] Transmit Queue Enable mode */
    ENET_MTL_TxThresholdType TxThreshold;                /**< MTL_TXQn_OPERATION_MODE[6:4,1] TTransmit Threshold Control */
    uint32_t IdleSlopeQuantumWeight;                     /**< MTL_TXQn_QUANTUM_WEIGHT[20:0] idleSlopeCredit, Quantum or Weights */
    uint32_t SendSlopeCredit;                            /**< MTL_TXQn_SENDSLOPECREDIT[13:0] Send slope credit for AVB queues */
    uint32_t HiCredit;                                   /**< MTL_TXQn_HICREDIT[28:0] High credit limit for AVB queues */
    int32_t LoCredit;                                    /**< MTL_TXQn_LOCREDIT[28:0] Low credit limit for AVB queues */
    ENET_MTL_QueueEnableType RxQueueEnable;              /**< Receive queue enable mode */
    ENET_MTL_RxThresholdType RxThreshold;                /**< MTL_RXQn_OPERATION_MODE[1:0,5] Threshold level of the MTL receive queue */
    ENET_MTL_RxFlowCtrlThresholdType RxDeactiveThreshold;/**< MTL_RXQn_OPERATION_MODE[17:14] Threshold for deactivating flow control  */
    ENET_MTL_RxFlowCtrlThresholdType RxActiveThreshold;  /**< MTL_RXQn_OPERATION_MODE[11:8] Threshold for activating flow control */
    bool RxHwFlowCtrlEnable;                             /**< MTL_RXQn_OPERATION_MODE[7] Enable Hardware Flow Control */
    bool ReveiveTCPIPCksumErrPkts;                       /**< MTL_RXQn_OPERATION_MODE[6] Disable Dropping of TCP/IP Checksum Error Packets */
    bool ReveiveErrorPkts;                               /**< MTL_RXQn_OPERATION_MODE[4] Forward error packets to application */
    bool ReveiveUndersizeGoodPkts;                       /**< MTL_RXQn_OPERATION_MODE[3] Forward undersized good packets to application */
    bool RxQueueArbitration;                             /**< Enable receive queue packet arbitration */
    uint8_t RxQueueWeight;                               /**< Receive queue weight */
    uint8_t RxQueuePriority;                             /**< Receive queue priority to match the priority field of tagged packets
                                                             bit n is set to 1 ,represent priority n is matched to the receive queue */
} ENET_MTLQueueConfigType;

/**
 * @brief ENET MTL configuration type
 *
 */
typedef struct ENET_MTLConfig
{
    ENET_MTL_TxScheduleAlgorithmType TxSchedAlgo;               /**< TX scheduling algorithm */
    ENET_MTL_RxArbitrationAlgorithmType RxArbitrationAlgo;      /**< RX arbitration algorithm */
    bool EnableTransmitStatus;                                  /**< Enable MTL to forward transmit status to application */

    ENET_MTLQueueConfigType QueueConfigs[ENET_CHANNEL_COUNT];
} ENET_MTLConfigType;

/**
 * @brief ENET DMA descriptor configuration type
 * Note:
 *  For TX DMA descriptor:
 *      Buffer is not necessary.
 *      DescList will be accessed by MCU and DMA.It is best to place DescList in a non-cacheable area,
 *      or users need to manually refresh the cache.
 *
 *  For RX DMA descriptor:
 *      Buffer is necessary.
 *      DescList Buffer will be accessed by MCU and DMA.It is best to place these buffers in a non-cacheable area,
 *      or users need to manually refresh the cache.
 *  */
typedef struct ENET_DescConfig
{
    ENET_DMADescType *DescList;                 /**< Buffer descriptor ring start address. */
    uint8_t *Buffer;                            /**< Buffer data pool start address, size = BufferLen * RingSize
                                                     The buffer must be 4 bytes aligned */
    uint16_t BufferLen;                         /**< Length of each individual buffer in the pool
                                                     The buffer length must be 4 bytes aligned */
    uint16_t RingSize;                          /**< The number of descriptors in DescList. */
} ENET_DescConfigType;

/**
 * @brief ENET configuration type
 *
 */
typedef struct ENET_Config
{
    uint8_t RxChannelCount;                         /**< The number of Receive Channel used by the driver. */
    uint8_t TxChannelCount;                         /**< The number of Transmit Channel used by the driver. */
    uint8_t MACAddress[ENET_MAC_ADDRESS_LENGTH];
    ENET_MAC_MiiModeType MiiMode;                   /**< PHY interface mode select */
#if ENET_SUPPORT_RGMII
    ENET_MAC_RGMIIClkSelType RgmiiClk;              /**< RGMII clock source select,this clock must be 125/25/2.5 MHZ */
#endif
    ENET_MAC_SpeedType Speed;                       /**< MAC link speed */
    ENET_MAC_DuplexModeType Duplex;                 /**< MAC communication duplex mode */

    ENET_DescConfigType RxBD[ENET_CHANNEL_COUNT];   /**< Receive Buffer Descriptors configuration */
    ENET_DescConfigType TxBD[ENET_CHANNEL_COUNT];   /**< Transmit Buffer Descriptors configuration */
    ENET_MiiConfigType MiiConfig;                   /**< PHY MDIO access configuration parameters */
    ENET_MACConfigType MACConfig;                   /**< MAC control registers configuration */
    ENET_MTLConfigType MTLConfig;                   /**< MTL control registers configuration */
    ENET_DMAConfigType DMAConfig;                   /**< DMA control registers configuration */

    /* Callback functions */
    ENET_EventCallbackType EventCallback;           /**< ENET general event callback */
    ENET_ChannelCallbackType RxReady;               /**< ENET receive data ready callback */
    ENET_ChannelCallbackType TxComplete;            /**< ENET send packet complete callback */
    ENET_ChannelCallbackType TxCompleteWait;        /**< ENET wait sending packet complete callback */
} ENET_ConfigType;

/**
 * @brief ENET handle is internal used by ENET driver
 *
 */
struct ENET_DrvHandle
{
    ENET_InstanceType eInstance;
    uint8_t ItMode;
    uint8_t TxChannelCount;
    uint8_t RxChannelCount;
    ENET_Type *EnetBase;
    ENET_DescListType TxDescLists[ENET_CHANNEL_COUNT];
    ENET_DescListType RxDescLists[ENET_CHANNEL_COUNT];

    /* Callback functions */
    ENET_EventCallbackType EventCallback;
    ENET_ChannelCallbackType RxReady;
    ENET_ChannelCallbackType TxComplete;
    ENET_ChannelCallbackType TxCompleteWait;

    ENET_StateType State;
    ENET_StateType TxState;
    ENET_StateType RxState;
    ENET_StateType PTPState;
    uint32_t PtpClkFreq;
    uint32_t PtpAddend;
    uint32_t PpsInterval;
    uint32_t PpsWidth;
};

/**
 * @brief                       Get ENET default configuration
 * @param[out] pConfig          ENET default configurations
 */
void Enet_DefaultConfig(ENET_ConfigType *pConfig);

/**
 * @brief                       Reset ENET driver
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_DeInit(ENET_HandleType *pEnetHandle);

/**
 * @brief                       Initialize ENET driver handle and peripheral
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pConfig           ENET configure parameters
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET initialize succeeded
 * @retval other values         ENET initialize failed
 */
ENET_StatusType Enet_Init(ENET_HandleType *pEnetHandle, const ENET_ConfigType *pConfig);

/**
 * @brief                       Start ENET transmission and reception process in polling mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET start succeeded
 * @retval other values         ENET start failed
 */
ENET_StatusType Enet_Start(ENET_HandleType *pEnetHandle);

/**
 * @brief                       Stop ENET transmission and reception process in polling mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET Stop succeeded
 * @retval other values         ENET Stop failed
 */
ENET_StatusType Enet_Stop(ENET_HandleType *pEnetHandle);

/**
 * @brief                       Start ENET transmission and reception in interrupt mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET start succeeded
 * @retval other values         ENET start failed
 */
ENET_StatusType Enet_StartIT(ENET_HandleType *pEnetHandle);

/**
 * @brief                       Stop ENET transmission and reception in interrupt mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET Stop succeeded
 * @retval other values         ENET Stop failed
 */
ENET_StatusType Enet_StopIT(ENET_HandleType *pEnetHandle);

/**
 * @brief                       ENET transmit frame
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          DMA channel to use
 * @param[in] pBuffers          Data buffer chain to transmit,The valid buffers must be ended with NULL pointer.
 *                                The member TotalLength of the first buffer will be used by this driver.
 *                                The member Length of all buffers will be used by this driver.
 *                                The member Data of all buffers will be accessed by DMA.
 *                                It is recommended that the Data buffer be placed in a non-cacheable area,
 *                                otherwise users need to manually refresh the cache.
 * @param[inout] pOption        Transmit options and results,set NULL if not needed
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Send frame successfully
 * @retval other values         Send frame failed
 */
ENET_StatusType Enet_SendFrame(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                               ENET_BufferType *pBuffers, ENET_TxOptionType *pOption);

/**
 * @brief                       Read frame from ENET
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          DMA channel to use
 * @param[out] pBuffers         Buffer chain to receive data,The valid buffers must be ended with NULL pointer.
 *                                The member TotalLength of the first buffer will be assigned by this driver.
 *                                The member Length of available buffers will be assigned by this driver.
 *                                The member Data of available buffers will be filled by DMA.
 * @param[out] pInfo            Received frame information,set NULL if not needed
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Receive frame successfully
 * @retval other values         Receive frame failed
 */
ENET_StatusType Enet_ReadFrame(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                               ENET_BufferType *pBuffers, ENET_RxInfoType *pInfo);

/**
 * @brief                       Build RX Descriptors to DMA
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          DMA channel to use
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Descriptors are released to DMA successfully
 * @retval other values         Descriptors are released to DMA failed
 */
ENET_StatusType Enet_BuildRxDescriptors(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel);

/**
 * @brief                       Set MAC0 address
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMacAddr          MAC address
 * @param[in] u8MacLen          MAC address length
 */
void Enet_SetMacAddress(ENET_HandleType *pEnetHandle, const uint8_t *pMacAddr, uint8_t u8MacLen);

/**
 * @brief                       Enable TCPIP checksum error filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          ENET channel
 * @param[in] bEnable           Enable MAC to drop packets with checksum error
 */
void Enet_CheckSumErrorFilter(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel, bool bEnable);

/**
 * @brief                       Set hash table for MAC hash filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bAddOrRemove      true: add,false: remove
 * @param[in] pMacAddr          MAC address
 * @param[in] u8MacLen          MAC address length
 */
void Enet_SetMacHashTable(ENET_HandleType *pEnetHandle, bool bAddOrRemove, const uint8_t *pMacAddr, uint8_t u8MacLen);

/**
 * @brief                       Get default MAC filter configurations
 * @param[in] pMACFilter        MAC filter Default configurations
 */
void Enet_DefaultMACFilter(ENET_MACFilterType *pMACFilter);

/**
 * @brief                       Get current MAC filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMACFilter        MAC filter Current configurations
 */
void Enet_GetMACFilter(const ENET_HandleType *pEnetHandle, ENET_MACFilterType *pMACFilter);

/**
 * @brief                       Set MAC filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMACFilter        MAC filter configurations
 */
void Enet_SetMACFilter(ENET_HandleType *pEnetHandle, const ENET_MACFilterType *pMACFilter);

/**
 * @brief                       Get default layer3 layer4 filter configurations
 * @param[out] pL3L4Filter      Default layer3 layer4 filter configurations
 */
void Enet_DefaultL3L4Filter(ENET_L3L4FilterType *pL3L4Filter);

/**
 * @brief                       Get current layer3 layer4 filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFilterGroup      Layer3 layer4 filter group
 * @param[in] pL3L4Filter       Current layer3 layer4 filter configurations
 */
void Enet_GetL3L4Filter(const ENET_HandleType *pEnetHandle, ENET_MAC_L3L4FilterGroupType pFilterGroup,
                        ENET_L3L4FilterType *pL3L4Filter);

/**
 * @brief                       Set layer3 layer4 filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFilterGroup      Layer3 layer4 filter group
 * @param[in] pL3L4Filter       Layer3 layer4 filter configurations
 */
void Enet_SetL3L4Filter(ENET_HandleType *pEnetHandle, ENET_MAC_L3L4FilterGroupType pFilterGroup,
                        const ENET_L3L4FilterType *pL3L4Filter);

/**
 * @brief                       Enable MAC layer3 layer4 filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bEnable           true: enable layer3 layer4 filter, false: disable
 */
void Enet_EnableL3L4Filter(ENET_HandleType *pEnetHandle, bool bEnable);

/**
 * @brief                       Get MAC VLAN filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanFilterConfig MAC VLAN filter configurations
 */
void Enet_GetVlanFilterConfig(const ENET_HandleType *pEnetHandle, ENET_VlanFilterConfigType *pVlanFilterConfig);

/**
 * @brief                       Enable MAC VLAN filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanFilterConfig MAC VLAN filter configurations
 */
void Enet_EnableVlanFilter(ENET_HandleType *pEnetHandle, const ENET_VlanFilterConfigType *pVlanFilterConfig);

/**
 * @brief                       Set vlan hash table
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bAddOrRemove      true add to hash table,false remove from hash table
 * @param[in] u16VlanTag        VLAN tag ID
 */
void Enet_SetVlanHashTable(ENET_HandleType *pEnetHandle, bool bAddOrRemove, uint16_t u16VlanTag);

/**
 * @brief                       Get current VLAN perfect filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFilterGroup      VLAN perfect filter group
 * @param[out] pPerfectFilter   VLAN perfect filter configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Get VLAN perfect filter configurations successfully
 * @retval other values         Get VLAN perfect filter configurations failed
 */
ENET_StatusType Enet_GetVlanPerfectFilter(ENET_HandleType *pEnetHandle, ENET_MAC_VLANFilterGroupType pFilterGroup,
                                          ENET_VlanPerfectFilterType *pPerfectFilter);

/**
 * @brief                       Set VLAN perfect filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFilterGroup      VLAN perfect filter group
 * @param[in] pPerfectFilter    VLAN perfect filter configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Set VLAN perfect filter configurations successfully
 * @retval other values         Set VLAN perfect filter configurations failed
 */
ENET_StatusType Enet_SetVlanPerfectFilter(ENET_HandleType *pEnetHandle, ENET_MAC_VLANFilterGroupType pFilterGroup,
                                          const ENET_VlanPerfectFilterType *pPerfectFilter);

/**
 * @brief                       Set outer VLAN insertion replacement or deletion
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanConfig       Outer VLAN operation parameters
 */
void Enet_SetTxOuterVlanConfig(ENET_HandleType *pEnetHandle, const ENET_TxVlanConfigType *pVlanConfig);

/**
 * @brief                       Set outer VLAN channel based insertion
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanConfig       Outer VLAN channel based configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  successful
 * @retval other values         failed
 */
ENET_StatusType Enet_SetTxOuterVlanChannelBasedInsertion(ENET_HandleType *pEnetHandle,
                                            const ENET_OuterVlanCBTIType *pVlanConfig);

/**
 * @brief                       Set inner VLAN insertion replacement or deletion
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanConfig       Inner VLAN operation parameters
 */
void Enet_SetTxInnerVlanConfig(ENET_HandleType *pEnetHandle, const ENET_TxVlanConfigType *pVlanConfig);

/**
 * @brief                       Register ENET system event callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterSystemEventCallback(ENET_HandleType *pEnetHandle, ENET_EventCallbackType eCallback);

/**
 * @brief                       Register receive frame callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterRxCompleteCallback(ENET_HandleType *pEnetHandle, ENET_ChannelCallbackType eCallback);

/**
 * @brief                       Register send frame complete callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterTxCompleteCallback(ENET_HandleType *pEnetHandle, ENET_ChannelCallbackType eCallback);

/**
 * @brief                       Register wait send frame complete callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterWaitTxCompleteCallback(ENET_HandleType *pEnetHandle, ENET_ChannelCallbackType eCallback);

/**
 * @brief                       Get MDIO bus default configuration
 * @param[out] pMiiConfig       MDIO configure parameters
 */
void Enet_MDIODefaultConfig(ENET_MiiConfigType *pMiiConfig);

/**
 * @brief                       Initialize the MDIO bus
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMiiConfig        MDIO configure parameters
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Initialize the MDIO bus successfully
 * @retval other values         Initialize the MDIO bus failed
 */
ENET_StatusType Enet_MDIOInit(ENET_HandleType *pEnetHandle, const ENET_MiiConfigType *pMiiConfig);

/**
 * @brief                       Read the PHY register using clause 22
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] u8PhyAddr         PHY device address
 * @param[in] u8PhyReg          PHY register address
 * @param[in] pData             Data buffer
 * @param[in] u32TimeoutUs      Wait time out value in microsecond
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  DMIO read successfully
 * @retval other values         DMIO read failed
 */
ENET_StatusType Enet_MDIORead(ENET_HandleType *pEnetHandle, uint8_t u8PhyAddr, uint8_t u8PhyReg,
                              uint16_t *pData, uint32_t u32TimeoutUs);

/**
 * @brief                       Write the PHY register using clause 22
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] u8PhyAddr         PHY device address
 * @param[in] u8PhyReg          PHY register address
 * @param[in] u16Data           Data to write
 * @param[in] u32TimeoutUs      Wait time out value in microsecond
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  DMIO write successfully
 * @retval other values         DMIO write failed
 */
ENET_StatusType Enet_MDIOWrite(ENET_HandleType *pEnetHandle, uint8_t u8PhyAddr, uint8_t u8PhyReg,
                               uint16_t u16Data, uint32_t u32TimeoutUs);

/**
 * @brief                       Read the PHY register using clause 45
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] u8PhyAddr         PHY device address
 * @param[in] u8Mmd             MMD device address
 * @param[in] u16PhyReg         PHY register address
 * @param[in] pData             Data buffer
 * @param[in] u32TimeoutUs      Wait time out value in microsecond
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  DMIO read successfully
 * @retval other values         DMIO read failed
 */
ENET_StatusType Enet_MMDRead(ENET_HandleType *pEnetHandle, uint8_t u8PhyAddr, uint8_t u8Mmd,
                             uint16_t u16PhyReg, uint16_t *pData, uint32_t u32TimeoutUs);

/**
 * @brief                       Write the PHY register using clause 45
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] u8PhyAddr         PHY device address
 * @param[in] u8Mmd             MMD device address
 * @param[in] u16PhyReg         PHY register address
 * @param[in] u16Data           Data to write
 * @param[in] u32TimeoutUs      Wait time out value in microsecond
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  DMIO write successfully
 * @retval other values         DMIO write failed
 */
ENET_StatusType Enet_MMDWrite(ENET_HandleType *pEnetHandle, uint8_t u8PhyAddr, uint8_t u8Mmd,
                              uint16_t u16PhyReg, uint16_t u16Data, uint32_t u32TimeoutUs);

/**
 * @brief                       Get PTP default configuration
 * @param[out] pPTPConfig       PTP default configurations
 */
void Enet_PTPDefaultConfig(Enet_PTPConfigType *pPTPConfig);

/**
 * @brief                       Start PTP counter process
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pPTPConfig        PTP initialize configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Start PTP successfully
 * @retval other values         Start PTP failed
 */
ENET_StatusType Enet_PTPStart(ENET_HandleType *pEnetHandle, const Enet_PTPConfigType *pPTPConfig);

/**
 * @brief                       Stop PTP counter process
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_PTPStop(ENET_HandleType *pEnetHandle);

/**
 * @brief                       Get PTP current system time
 * @param[in] pEnetHandle       ENET driver handle
 * @param[out] pTime            PTP system time
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Get PTP system time successfully
 * @retval other values         Get PTP system time failed
 */
ENET_StatusType Enet_PTPGetTime(const ENET_HandleType *pEnetHandle, ENET_TimestampType *pTime);

/**
 * @brief                       Set PTP system time
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pTime             Time to set
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Set PTP time successfully
 * @retval other values         Set PTP time failed
 */
ENET_StatusType Enet_PTPSetTime(ENET_HandleType *pEnetHandle, const ENET_TimestampType *pTime);

/**
 * @brief                       Update PTP system time offset
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pTime             Time offset
 * @param[in] bSubtraction      Subtract from PTP system time,or add to PTP system time
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Update PTP time successfully
 * @retval other values         Update PTP time failed
 */
ENET_StatusType Enet_PTPUpdateTime(ENET_HandleType *pEnetHandle, const ENET_TimestampType *pTime, bool bSubtraction);

/**
 * @brief                       Adjust the PTP counter frequency
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] PPb               PTP frequency bias in PPB
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Adjust PTP frequency successfully
 * @retval ENET_STATUS_INVALID_PARAM Parameter invalid
 * @retval ENET_STATUS_UNSUPPORTED Time stamp update mode unsupported
 * @retval ENET_STATUS_NOT_READY Time stamp not ready
 */
ENET_StatusType Enet_PTPAdjustFrequency(ENET_HandleType *pEnetHandle, int PPb);

/**
 * @brief                       Enable PTP channel PPS out in fixed mode
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] ePPSChannel       PTP PPS channel
 * @param[in] eFreqCtrl         PTP fixed PPS out frequency control
 *                                In binary rollover mode: PPS frequency = 2^eFreqCtrl
 *                                In digital rollover mode: PPS frequency = (eFreqCtrl == 0) ? 1 : 2^(eFreqCtrl - 1)
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Enable PTP channel PPS out successfully
 * @retval other values         Enable PTP channel PPS out failed
 */
ENET_StatusType Enet_PTPFixedPPSOut(ENET_HandleType *pEnetHandle, ENET_MAC_PPSChannelType ePPSChannel,
                                    ENET_MAC_PPSFreqCtrlType eFreqCtrl);

/**
 * @brief                       Enable PTP channel PPS out in flexible mode
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] ePPSChannel       PTP PPS channel
 * @param[in] PPSConfig         PTP flexible PPS out configuration
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Enable PTP flexible PPS out successfully
 * @retval other values         Enable PTP flexible PPS out failed
 * @note                        The Enet_PTPSetTime API may be called by application before target time reached,
 *                              in this case,the target time reached interrupt will not be triggered,
 *                              so users need to use some method to handle this event ,such as a timeout mechanism.
 */
ENET_StatusType Enet_PTPFlexiblePPSOut(ENET_HandleType *pEnetHandle, ENET_MAC_PPSChannelType ePPSChannel,
                                       const ENET_FlexPPSConfigType *PPSConfig);

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief                       Get EST configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[out] pEstConfig       Structure to save configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Get EST configurations successfully
 * @retval other values         Get EST configurations failed
 */
ENET_StatusType Enet_TSN_GetEstConfig(ENET_HandleType *pEnetHandle, ENET_EstConfigType *pEstConfig);

/**
 * @brief                       Set EST configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pEstConfig        EST configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Set EST configurations successfully
 * @retval other values         Set EST configurations failed
 */
ENET_StatusType Enet_TSN_EstConfig(ENET_HandleType *pEnetHandle, const ENET_EstConfigType *pEstConfig);

/**
 * @brief                       Enable EST processing
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bEnable           Enable or disable
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Enable EST function successfully
 * @retval other values         Enable EST function failed
 */
ENET_StatusType Enet_TSN_EstEnable(ENET_HandleType *pEnetHandle, bool bEnable);

/**
 * @brief                       Read the current gate control list
 * @param[in] pEnetHandle       ENET driver handle
 * @param[out] pGatelist        Gate control list
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Read GCL successfully
 * @retval other values         Read GCL failed
 */
ENET_StatusType Enet_TSN_GetEstGclConfig(ENET_HandleType *pEnetHandle, ENET_GateCtrlListType *pGatelist);

/**
 * @brief                       Install new gate control list
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pGatelist         Gate control list
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Install new GCL successfully
 * @retval other values         Install new GCL failed
 */
ENET_StatusType Enet_TSN_EstGclConfig(ENET_HandleType *pEnetHandle, const ENET_GateCtrlListType *pGatelist);

/**
 * @brief                       Enable or disable the frame preemption function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pConfig           Preemption configuration structure
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Enable or disable frame preemption successfully
 * @retval other values         Enable or disable frame preemption failed
 */
ENET_StatusType Enet_TSN_PreemptionConfig(ENET_HandleType *pEnetHandle, const ENET_PreemptionConfigType *pConfig);
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief                       ENET get MAC management counters configuration
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMMCConfig        MAC management configuration type
 */
void Enet_GetMMCConfig(const ENET_HandleType *pEnetHandle, ENET_MMCConfigType *pMMCConfig);

/**
 * @brief                       ENET set MAC management counters configuration
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMMCConfig        MAC management configuration type
 */
void Enet_SetMMCConfig(ENET_HandleType *pEnetHandle, const ENET_MMCConfigType *pMMCConfig);

/**
 * @brief                       Preset MAC management counters
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_MMCCounterPreset(ENET_HandleType *pEnetHandle);

/**
 * @brief                       Freeze MMC counters to their current value
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bFreeze           Enable or disable Freeze
 */
void Enet_MMCCounterFreeze(ENET_HandleType *pEnetHandle, bool bFreeze);

/**
 * @brief                       Reset MAC management counters to zero
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_MMCCounterReset(ENET_HandleType *pEnetHandle);

/**
 * @brief                       Get MMC transmit counters interrupt status
 * @param[in] pEnetHandle       ENET driver handle
 * @note                        User must read the respective counter to clear the MMC interrupt bit.
 */
uint32_t Enet_GetMMCTxInterrupts(const ENET_HandleType *pEnetHandle);

/**
 * @brief                       Get MMC receive counters interrupt status
 * @param[in] pEnetHandle       ENET driver handle
 * @note                        User must read the respective counter to clear the MMC interrupt bit.
 */
uint32_t Enet_GetMMCRxInterrupts(const ENET_HandleType *pEnetHandle);

/**
 * @brief                       Get ENET MAC management transmit counters
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCounter          MAC management transmit counter type
 */
uint32_t Enet_GetMMCTxCounter(const ENET_HandleType *pEnetHandle, Enet_MMCTxCounterType eCounter);

/**
 * @brief                       Get ENET MAC management receive counters
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCounter          MAC management receive counter type
 */
uint32_t Enet_GetMMCRxCounter(const ENET_HandleType *pEnetHandle, Enet_MMCRxCounterType eCounter);

/**
 * @brief                       Get flow control configuration
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFlowControl      MAC flow control configuration
 */
void Enet_GetFlowControlConfig(const ENET_HandleType *pEnetHandle, ENET_FlowControlType *pFlowControl);

/**
 * @brief                       Configure and enable flow control
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFlowControl      MAC flow control configuration
 */
void Enet_FlowControlConfig(ENET_HandleType *pEnetHandle, const ENET_FlowControlType *pFlowControl);

/**
 * @brief                       Generate and transmits a single pause packet
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_FlowControlSoftwareTrigger(ENET_HandleType *pEnetHandle);

/**
 * @brief                       ENET driver system interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_SystemIrqHandler(ENET_HandleType *pEnetHandle);

/**
 * @brief                       ENET driver DMA TX channel interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          ENET DMA channel
*/
void Enet_TxIrqHandler(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel);

/**
 * @brief                       ENET driver DMA RX channel interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          ENET DMA channel
 */
void Enet_RxIrqHandler(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel);


/** @}*/ /* module_driver_enet */

#if defined(__cplusplus)
}
#endif

#endif /* ENET_INSTANCE_COUNT > 0u */

#endif /* _DRIVER_MODULE_DRIVER_ENET_H_ */
