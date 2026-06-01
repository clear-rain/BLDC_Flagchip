/**
 * @file HwA_enet.h
 * @author Flagchip
 * @brief ENET hardware access layer
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

#ifndef _HWA_ENET_H_
#define _HWA_ENET_H_

#include "device_header.h"

#if ENET_INSTANCE_COUNT > 0u


/**
 * @defgroup HwA_enet HwA_enet
 * @ingroup module_driver_enet
 * @{
 */

/**
 * @brief ENE MAC status type definition
 *
 */
typedef enum
{
    ENET_MAC_STATUS_IDLE = 0u,
    ENET_MAC_STATUS_BUSY = 1u
} ENET_MAC_StatusType;

/**
 * @brief ENET MAC source address insertion control type definition
 *
 */
typedef enum
{
    ENET_MAC_SRC_ADDR_CTRL_BY_INPUT_SIGNAL      = 0u,
    ENET_MAC_SRC_ADDR_INSERT_BY_MAC_ADDR_IDX_0  = 2u,
    ENET_MAC_SRC_ADDR_REPLACE_BY_MAC_ADDR_IDX_0 = 3u,
    ENET_MAC_SRC_ADDR_INSERT_BY_MAC_ADDR_IDX_1  = 6u,
    ENET_MAC_SRC_ADDR_REPLACE_BY_MAC_ADDR_IDX_1 = 7u
} ENET_MAC_SrcAddrCtrlType;

/**
 * @brief MAC inter packet gap type definition
 *
 */
typedef enum
{
    ENET_MAC_INTER_PACKET_GAP_96_BIT = 0u,
    ENET_MAC_INTER_PACKET_GAP_88_BIT = 1u,
    ENET_MAC_INTER_PACKET_GAP_80_BIT = 2u,
    ENET_MAC_INTER_PACKET_GAP_72_BIT = 3u,
    ENET_MAC_INTER_PACKET_GAP_64_BIT = 4u,
    ENET_MAC_INTER_PACKET_GAP_56_BIT = 5u,
    ENET_MAC_INTER_PACKET_GAP_48_BIT = 6u,
    ENET_MAC_INTER_PACKET_GAP_40_BIT = 7u
} ENET_MAC_InterPacketGapType;

/**
 * @brief MAC extend inner packet gap type definition
 *
 */
typedef enum
{
    ENET_MAC_EXT_INTER_PACKET_GAP_104_BIT = 0u,
    ENET_MAC_EXT_INTER_PACKET_GAP_112_BIT = 1u,
    ENET_MAC_EXT_INTER_PACKET_GAP_120_BIT = 2u,
    ENET_MAC_EXT_INTER_PACKET_GAP_128_BIT = 3u,
    ENET_MAC_EXT_INTER_PACKET_GAP_136_BIT = 4u,
    ENET_MAC_EXT_INTER_PACKET_GAP_144_BIT = 5u,
    ENET_MAC_EXT_INTER_PACKET_GAP_152_BIT = 6u,
    ENET_MAC_EXT_INTER_PACKET_GAP_160_BIT = 7u,
    ENET_MAC_EXT_INTER_PACKET_GAP_168_BIT = 8u,
    ENET_MAC_EXT_INTER_PACKET_GAP_176_BIT = 9u,
    ENET_MAC_EXT_INTER_PACKET_GAP_184_BIT = 10u,
    ENET_MAC_EXT_INTER_PACKET_GAP_192_BIT = 11u,
    ENET_MAC_EXT_INTER_PACKET_GAP_200_BIT = 12u,
    ENET_MAC_EXT_INTER_PACKET_GAP_208_BIT = 13u,
    ENET_MAC_EXT_INTER_PACKET_GAP_216_BIT = 14u,
    ENET_MAC_EXT_INTER_PACKET_GAP_224_BIT = 15u,
    ENET_MAC_EXT_INTER_PACKET_GAP_232_BIT = 16u,
    ENET_MAC_EXT_INTER_PACKET_GAP_240_BIT = 17u,
    ENET_MAC_EXT_INTER_PACKET_GAP_248_BIT = 18u,
    ENET_MAC_EXT_INTER_PACKET_GAP_256_BIT = 19u,
    ENET_MAC_EXT_INTER_PACKET_GAP_264_BIT = 20u,
    ENET_MAC_EXT_INTER_PACKET_GAP_272_BIT = 21u,
    ENET_MAC_EXT_INTER_PACKET_GAP_280_BIT = 22u,
    ENET_MAC_EXT_INTER_PACKET_GAP_288_BIT = 23u,
    ENET_MAC_EXT_INTER_PACKET_GAP_296_BIT = 24u,
    ENET_MAC_EXT_INTER_PACKET_GAP_304_BIT = 25u,
    ENET_MAC_EXT_INTER_PACKET_GAP_312_BIT = 26u,
    ENET_MAC_EXT_INTER_PACKET_GAP_320_BIT = 27u,
    ENET_MAC_EXT_INTER_PACKET_GAP_328_BIT = 28u,
    ENET_MAC_EXT_INTER_PACKET_GAP_336_BIT = 29u,
    ENET_MAC_EXT_INTER_PACKET_GAP_344_BIT = 30u,
    ENET_MAC_EXT_INTER_PACKET_GAP_352_BIT = 31u
} ENET_MAC_ExtInterPacketGapType;

/**
 * @brief MAC speed mode type definition
 *
 */
typedef enum
{
    ENET_MAC_SPEED_1000MBPS = 0u,
    ENET_MAC_SPEED_2500MBPS = 1u,
    ENET_MAC_SPEED_10MBPS   = 2u,
    ENET_MAC_SPEED_100MBPS  = 3u
} ENET_MAC_SpeedType;

/**
 * @brief MAC duplex mode type definition
 *
 */
typedef enum
{
    ENET_MAC_HALF_DUPLEX = 0u,
    ENET_MAC_FULL_DUPLEX = 1u
} ENET_MAC_DuplexModeType;

/**
 * @brief MAC back off limit type definition
 *
 */
typedef enum
{
    ENET_MAC_BACK_OFF_LIMIT_10_SLOT = 0u,
    ENET_MAC_BACK_OFF_LIMIT_8_SLOT  = 1u,
    ENET_MAC_BACK_OFF_LIMIT_4_SLOT  = 2u,
    ENET_MAC_BACK_OFF_LIMIT_1_SLOT  = 3u
} ENET_MAC_BackOffLimitType;

/**
 * @brief MAC slow protocol detect type definition
 *
 */
typedef enum
{
    ENET_MAC_SLOW_PROTOCOL_DETECT_STANDARD = 0u,
    ENET_MAC_SLOW_PROTOCOL_DETECT_EXTENDED = 1u
} ENET_MAC_SlowProtocolDetectType;

/**
 * @brief MAC address filter mode type definition
 *
 */
typedef enum
{
    ENET_MAC_ADDR_FILTER_DIRECT  = 0u,
    ENET_MAC_ADDR_FILTER_INVERSE = 1u
} ENET_MAC_AddrFilterModeType;

/**
 * @brief MAC control packets filter mode type definition
 *
 */
typedef enum
{
    ENET_MAC_CTRL_PACKET_FILTER_ALL          = 0u,
    ENET_MAC_CTRL_PACKET_FILTER_PAUSE_PACKET = 1u,
    ENET_MAC_CTRL_PACKET_FORWARD_ALL         = 2u,
    ENET_MAC_CTRL_PACKET_ADDR_FILTER         = 3u
} ENET_MAC_CtrlPacketFilterModeType;

/**
 * @brief MAC perfect or hash filter mode type definition
 *
 */
typedef enum
{
    ENET_MAC_USE_PERFECT_FILTER = 0u,
    ENET_MAC_USE_HASH_FILTER    = 1u
} ENET_MAC_HashOrPerfectModeType;

/**
 * @brief MAC watchdog timer type definition
 *
 */
typedef enum
{
    ENET_MAC_WDG_TIMER_SIZE_2KB  = 0u,
    ENET_MAC_WDG_TIMER_SIZE_3KB  = 1u,
    ENET_MAC_WDG_TIMER_SIZE_4KB  = 2u,
    ENET_MAC_WDG_TIMER_SIZE_5KB  = 3u,
    ENET_MAC_WDG_TIMER_SIZE_6KB  = 4u,
    ENET_MAC_WDG_TIMER_SIZE_7KB  = 5u,
    ENET_MAC_WDG_TIMER_SIZE_8KB  = 6u,
    ENET_MAC_WDG_TIMER_SIZE_9KB  = 7u,
    ENET_MAC_WDG_TIMER_SIZE_10KB = 8u,
    ENET_MAC_WDG_TIMER_SIZE_11KB = 9u,
    ENET_MAC_WDG_TIMER_SIZE_12KB = 10u,
    ENET_MAC_WDG_TIMER_SIZE_13KB = 11u,
    ENET_MAC_WDG_TIMER_SIZE_14KB = 12u,
    ENET_MAC_WDG_TIMER_SIZE_15KB = 13u
} ENET_MAC_WDGTimerSizeType;

/**
 * @brief MAC VLAN tag strip type
 *
 */
typedef enum
{
    ENET_MAC_VLAN_TAG_STRIP_NEVER       = 0u,
    ENET_MAC_VLAN_TAG_STRIP_FILTER_PASS = 1u,
    ENET_MAC_VLAN_TAG_STRIP_FILTER_FAIL = 2u,
    ENET_MAC_VLAN_TAG_STRIP_ALWAYS      = 3u
} ENET_MAC_VLANTagStripModeType;

/**
 * @brief MAC VLAN indirect registers access command type
 *
 */
typedef enum
{
    ENET_MAC_VLAN_COMMAND_WRITE = 0u,
    ENET_MAC_VLAN_COMMAND_READ  = 1u
} ENET_MAC_VLANCommandType;

/**
 * @brief MAC VLAN incl indirect registers access command type
 *
 */
typedef enum
{
    ENET_MAC_VLAN_INCL_COMMAND_READ  = 0u,
    ENET_MAC_VLAN_INCL_COMMAND_WRITE = 1u
} ENET_MAC_VLANInclCommandType;

/**
 * @brief MAC VLAN tag control type
 *
 */
typedef enum
{
    ENET_MAC_VLAN_TAG_NO_OPERATION = 0u,
    ENET_MAC_VLAN_TAG_DELETION     = 1u,
    ENET_MAC_VLAN_TAG_INSERTION    = 2u,
    ENET_MAC_VLAN_TAG_REPLACEMENT  = 3u
} ENET_MAC_VLANTagCtrlType;

/**
 * @brief MAC VLAN tag type
 *  S-VLAN IEEE802.1ad (Q-in-Q)
 *  C-VLAN IEEE802.1Q
 */
typedef enum
{
    ENET_MAC_VLAN_TYPE_C_VLAN = 0u,
    ENET_MAC_VLAN_TYPE_S_VLAN = 1u
} ENET_MAC_VLANType;

/**
 * @brief MAC VLAN compare mode type
 *
 */
typedef enum
{
    ENET_MAC_VLAN_16BITS_COMPARE = 0u,
    ENET_MAC_VLAN_12BITS_COMPARE = 1u
} ENET_MAC_VLANCompareType;

/**
 * @brief MAC VLAN perfect filter group index type
 *
 */
typedef enum
{
    ENET_MAC_VLAN_FILTER_GROUP_0 = 0u,
    ENET_MAC_VLAN_FILTER_GROUP_1 = 1u,
    ENET_MAC_VLAN_FILTER_GROUP_2 = 2u,
    ENET_MAC_VLAN_FILTER_GROUP_3 = 3u
} ENET_MAC_VLANFilterGroupType;

/**
 * @brief ENET flow control pause threshold type
 *
 */
typedef enum
{
    ENET_MAC_PAUSE_THRESHOLD_4SLOT_TIMES    = 0u,
    ENET_MAC_PAUSE_THRESHOLD_28SLOT_TIMES   = 1u,
    ENET_MAC_PAUSE_THRESHOLD_36SLOT_TIMES   = 2u,
    ENET_MAC_PAUSE_THRESHOLD_144SLOT_TIMES  = 3u,
    ENET_MAC_PAUSE_THRESHOLD_256SLOT_TIMES  = 4u,
    ENET_MAC_PAUSE_THRESHOLD_512SLOT_TIMES  = 5u
} ENET_MAC_PauseThresholdType;

/**
 * @brief MAC TX packet controller status type
 *
 */
typedef enum
{
    ENET_MAC_TX_PACKET_CONTROLLER_IDLE                  = 0u,
    ENET_MAC_TX_PACKET_CONTROLLER_WAIT                  = 1u,
    ENET_MAC_TX_PACKET_CONTROLLER_TRANSFER_PAUSE_PACKET = 2u,
    ENET_MAC_TX_PACKET_CONTROLLER_TRANSFER_INPUT_PACKET = 3u
} ENET_MAC_TxPacketControllerStatusType;

/**
 * @brief MTL queue enable type
 *
 */
typedef enum
{
    ENET_MTL_QUEUE_DISABLE        = 0u,
    ENET_MTL_QUEUE_ENABLE_AV_MODE = 1u,
    ENET_MTL_QUEUE_ENABLE_GENERIC = 2u
} ENET_MTL_QueueEnableType;

/**
 * @brief Tagged PTP over Ethernet packets queuing control type
 *
 */
typedef enum
{
    ENET_MAC_VLAN_PTPOE_ROUTED_AS_GENERIC   = 0u,
    ENET_MAC_VLAN_PTPOE_ROUTED_TO_PTP_QUEUE = 1u,
    ENET_MAC_VLAN_PTPOE_ROUTED_BY_PRIORITY  = 2u
} ENET_MAC_PTPoEQueueCtrlType;

#if ENET_SUPPORT_RGMII
/**
 * @brief  MAC RGMII clock select type
 *
 */
typedef enum
{
    ENET_MAC_RGMII_CLK_SEL_DISABLE      = 0u,
    ENET_MAC_RGMII_CLK_SEL_ENET_REF_CLK = 1u,
    ENET_MAC_RGMII_CLK_SEL_PLL0DIVH     = 2u,
    ENET_MAC_RGMII_CLK_SEL_PLL1DIVH     = 3u
} ENET_MAC_RGMIIClkSelType;
#endif

/**
 * @brief MAC TX clock select type
 *
 */
typedef enum
{
    ENET_MAC_TX_CLK_SEL_DISABLE     = 0u,
    ENET_MAC_TX_CLK_SEL_PLL0DIVL    = 1u,
    ENET_MAC_TX_CLK_SEL_FOSC        = 2u,
    ENET_MAC_TX_CLK_SEL_ENET_TX_CLK = 3u
} ENET_MAC_TxClkSelType;

/**
 * @brief  MAC PHY interface mode type
 *
 */
typedef enum
{
    ENET_MAC_PHY_MII   = 0u,
    ENET_MAC_PHY_RGMII = 1u,
    ENET_MAC_PHY_RMII  = 4u
} ENET_MAC_MiiModeType;

/**
 * @brief MAC MDIO access clock source range type
 *
 */
typedef enum
{
    ENET_MAC_CSR_CLOCK_RANGE_60_100MHZ  = 0u,
    ENET_MAC_CSR_CLOCK_RANGE_100_150MHZ = 1u,
    ENET_MAC_CSR_CLOCK_RANGE_20_35MHZ   = 2u,
    ENET_MAC_CSR_CLOCK_RANGE_35_60MHZ   = 3u,
    ENET_MAC_CSR_CLOCK_RANGE_150_250MHZ = 4u,
    ENET_MAC_CSR_CLOCK_RANGE_250_300MHZ = 5u
} ENET_MAC_CSRClockRangeType;

/**
 * @brief MAC MDIO bus operation command type
 *
 */
typedef enum
{
    ENET_MAC_PHY_OPERATION_WRITE                             = 1u,
    ENET_MAC_PHY_OPERATION_POST_READ_INCR_ADDR_FOR_CLAUSE_45 = 2u,
    ENET_MAC_PHY_OPERATION_READ                              = 3u
} ENET_MAC_PhyOperationCmdType;

/**
 * @brief MAC MDIO bus clause type
 *
 */
typedef enum
{
    ENET_MAC_PHY_CLAUSE_22 = 0u,
    ENET_MAC_PHY_CLAUSE_45 = 1u
} ENET_MAC_PhyClauseVersionType;

/**
 * @brief MAC address destination or source type
 *
 */
typedef enum
{
    ENET_MAC_ADDR_TYPE_DEST = 0u,
    ENET_MAC_ADDR_TYPE_SRC  = 1u
} ENET_MAC_AddrType;

/**
 * @brief MMC counter present level type
 *
 */
typedef enum
{
    ENET_MAC_MMC_COUNTER_PRESET_LEVEL_HALF = 0u,
    ENET_MAC_MMC_COUNTER_PRESET_LEVEL_FULL = 1u
} ENET_MAC_MmcCntPresetLevelType;

/**
 * @brief MAC layer 4 filter protocol type
 *
 */
typedef enum
{
    ENET_MAC_LAYER_4_PROTOCOL_TCP = 0u,
    ENET_MAC_LAYER_4_PROTOCOL_UDP = 1u
} ENET_MAC_Layer4ProtocolType;

/**
 * @brief MAC layer 3 filter protocol type
 *
 */
typedef enum
{
    ENET_MAC_LAYER_3_PROTOCOL_IPV4 = 0u,
    ENET_MAC_LAYER_3_PROTOCOL_IPV6 = 1u
} ENET_MAC_Layer3ProtocolType;

/**
 * @brief MAC layer3 layer 4 filter group index type
 *
 */
typedef enum
{
    ENET_MAC_L3_L4_FILTER_GROUP_0 = 0u,
    ENET_MAC_L3_L4_FILTER_GROUP_1 = 1u,
    ENET_MAC_L3_L4_FILTER_GROUP_2 = 2u,
    ENET_MAC_L3_L4_FILTER_GROUP_3 = 3u
} ENET_MAC_L3L4FilterGroupType;

/**
 * @brief MAC MMC transmit statistics counter type
 *
 */
typedef enum
{
    ENET_CTR_TX_OCTET_COUNT_GOOD_BAD = 0u,
    ENET_CTR_TX_PACKET_COUNT_GOOD_BAD,
    ENET_CTR_TX_BROADCAST_PACKETS_GOOD,
    ENET_CTR_TX_MULTICAST_PACKETS_GOOD,
    ENET_CTR_TX_64OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_TX_65TO127OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_TX_128TO255OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_TX_256TO511OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_TX_512TO1023OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_TX_UNICAST_PACKETS_GOOD_BAD,
    ENET_CTR_TX_MULTICAST_PACKETS_GOOD_BAD,
    ENET_CTR_TX_BROADCAST_PACKETS_GOOD_BAD,
    ENET_CTR_TX_UNDERFLOW_ERROR_PACKETS,
    ENET_CTR_TX_SINGLE_COLLISION_GOOD_PACKETS,
    ENET_CTR_TX_MULTIPLE_COLLISION_GOOD_PACKETS,
    ENET_CTR_TX_DEFERRED_PACKETS,
    ENET_CTR_TX_LATE_COLLISION_PACKETS,
    ENET_CTR_TX_EXCESSIVE_COLLISION_PACKETS,
    ENET_CTR_TX_CARRIER_ERROR_PACKETS,
    ENET_CTR_TX_OCTET_COUNT_GOOD,
    ENET_CTR_TX_PACKET_COUNT_GOOD,
    ENET_CTR_TX_EXCESSIVE_DEFERRAL_ERROR,
    ENET_CTR_TX_PAUSE_PACKETS,
    ENET_CTR_TX_VLAN_PACKETS_GOOD,
    ENET_CTR_TX_OSIZE_PACKETS_GOOD,
} Enet_MMCTxCounterType;

/**
 * @brief MAC receive statistics counter type
 *
 */
typedef enum
{
    ENET_CTR_RX_PACKETS_COUNT_GOOD_BAD = 0u,
    ENET_CTR_RX_OCTET_COUNT_GOOD_BAD,
    ENET_CTR_RX_OCTET_COUNT_GOOD,
    ENET_CTR_RX_BROADCAST_PACKETS_GOOD,
    ENET_CTR_RX_MULTICAST_PACKETS_GOOD,
    ENET_CTR_RX_CRC_ERROR_PACKETS,
    ENET_CTR_RX_ALIGNMENT_ERROR_PACKETS,
    ENET_CTR_RX_RUNT_ERROR_PACKETS,
    ENET_CTR_RX_JABBER_ERROR_PACKETS,
    ENET_CTR_RX_UNDERSIZE_PACKETS_GOOD,
    ENET_CTR_RX_OVERSIZE_PACKETS_GOOD,
    ENET_CTR_RX_64OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_RX_65TO127OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_RX_128TO255OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_RX_256TO511OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_RX_512TO1023OCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD,
    ENET_CTR_RX_UNICAST_PACKETS_GOOD,
    ENET_CTR_RX_LENGTH_ERROR_PACKETS,
    ENET_CTR_RX_OUT_OF_RANGE_TYPE_PACKETS,
    ENET_CTR_RX_PAUSE_PACKETS,
    ENET_CTR_RX_FIFO_OVERFLOW_PACKETS,
    ENET_CTR_RX_VLAN_PACKETS_GOOD_BAD,
    ENET_CTR_RX_WATCHDOG_ERROR_PACKETS,
    ENET_CTR_RX_RECEIVE_ERROR_PACKETS,
    ENET_CTR_RX_CONTROL_PACKETS_GOOD,
} Enet_MMCRxCounterType;

/**
 * @brief PTP TX status mode type
 *
 */
typedef enum
{
    ENET_MAC_TX_TIMESTAMP_STATUS_MODE_PRESERVE  = 0u,
    ENET_MAC_TX_TIMESTAMP_STATUS_MODE_OVERWRITE = 1u
} ENET_MAC_TxTimestampStatusModeType;

/**
 * @brief PTP system time input source type
 *
 */
typedef enum
{
    ENET_MAC_SYSTEM_TIME_INPUT_INTERNAL = 0u,
    ENET_MAC_SYSTEM_TIME_INPUT_EXTERNAL = 1u
} ENET_MAC_SystemTimeInputType;

/**
 * @brief PTP IEEE1588 version type
 *
 */
typedef enum
{
    ENET_MAC_PTP_IEEE_1588_V1 = 0u,
    ENET_MAC_PTP_IEEE_1588_V2 = 1u,
} ENET_MAC_PTPVersionType;

/**
 * @brief PTP counter rollover mode type
 *
 */
typedef enum
{
    ENET_MAC_TIMESTAMP_ROLLOVER_BINARY  = 0u,
    ENET_MAC_TIMESTAMP_ROLLOVER_DIGITAL = 1u,
} ENET_MAC_TimestampRolloverType;

/**
 * @brief PTP timestamp update mode type
 *
 */
typedef enum
{
    ENET_MAC_TIMESTAMP_UPDATE_COARSE = 0u,
    ENET_MAC_TIMESTAMP_UPDATE_FINE   = 1u
} ENET_MAC_TimestampUpdateMethodType;

/**
 * @brief PTP system time offset update operation type
 *
 */
typedef enum
{
    ENET_MAC_SYSTEM_TIME_ADD_TIME      = 0u,
    ENET_MAC_SYSTEM_TIME_SUBTRACT_TIME = 1u
} ENET_MAC_SystemTimeOperationType;

/**
 * @brief PTP PPS channel type
 *
 */
typedef enum
{
    ENET_MAC_PPS_CHANNEL_0 = 0u,
    ENET_MAC_PPS_CHANNEL_1 = 1u,
    ENET_MAC_PPS_CHANNEL_2 = 2u,
    ENET_MAC_PPS_CHANNEL_3 = 3u
} ENET_MAC_PPSChannelType;

/**
 * @brief PTP PPS channel operation mode type
 *
 */
typedef enum
{
    ENET_MAC_PPS_MODE_PPS  = 0u,
    ENET_MAC_PPS_MODE_MCGR = 1u
} ENET_MAC_PPSModeType;

/**
 * @brief PPS target time mode type
 *
 */
typedef enum
{
    ENET_MAC_PPS_TARGET_TIME_ONLY_INT = 0u,
    ENET_MAC_PPS_TARGET_TIME_MCGR     = 1u,
    ENET_MAC_PPS_TARGET_TIME_INT_ST   = 2u,
    ENET_MAC_PPS_TARGET_TIME_ONLY_ST  = 3u
} ENET_MAC_PPSTargetTimeModeType;

/**
 * @brief PTP fixed PPS output frequency control type
 *
 */
typedef enum
{
    ENET_MAC_PPS_CTRL_FREQ_1HZ       = 0u,
    ENET_MAC_PPS_CTRL_FREQ_2HZ       = 1u,
    ENET_MAC_PPS_CTRL_FREQ_4HZ       = 2u,
    ENET_MAC_PPS_CTRL_FREQ_8HZ       = 3u,
    ENET_MAC_PPS_CTRL_FREQ_16HZ      = 4u,
    ENET_MAC_PPS_CTRL_FREQ_32HZ      = 5u,
    ENET_MAC_PPS_CTRL_FREQ_64HZ      = 6u,
    ENET_MAC_PPS_CTRL_FREQ_128HZ     = 7u,
    ENET_MAC_PPS_CTRL_FREQ_256HZ     = 8u,
    ENET_MAC_PPS_CTRL_FREQ_512HZ     = 9u,
    ENET_MAC_PPS_CTRL_FREQ_1KHZ      = 10u,
    ENET_MAC_PPS_CTRL_FREQ_2KHZ      = 11u,
    ENET_MAC_PPS_CTRL_FREQ_4KHZ      = 12u,
    ENET_MAC_PPS_CTRL_FREQ_8KHZ      = 13u,
    ENET_MAC_PPS_CTRL_FREQ_16KHZ     = 14u,
    ENET_MAC_PPS_CTRL_FREQ_32K768HZ  = 15u
} ENET_MAC_PPSFreqCtrlType;

/**
 * @brief PTP flexible PPS output command type
 *
 */
typedef enum
{
    ENET_MAC_PPS_NO_COMMAND                   = 0u,
    ENET_MAC_PPS_START_SINGLE_PULSE           = 1u,
    ENET_MAC_PPS_START_PULSE_TRAIN            = 2u,
    ENET_MAC_PPS_CANCEL_START                 = 3u,
    ENET_MAC_PPS_STOP_PULSE_TRAIN_AT_TIME     = 4u,
    ENET_MAC_PPS_STOP_PULSE_TRAIN_IMMEDIATELY = 5u,
    ENET_MAC_PPS_CANCEL_STOP_PULSE_TRAIN      = 6u
} ENET_MAC_PPSCmdType;

/**
 * @brief PTP flexible MCGR command type
 *
 */
typedef enum
{
    ENET_MAC_MCGR_OPERATION_NOT_CARRIED_OUT    = 0u,
    ENET_MAC_MCGR_CAPTURE_RISING_EDGE          = 1u,
    ENET_MAC_MCGR_CAPTURE_FALLING_EDGE         = 2u,
    ENET_MAC_MCGR_CAPTURE_BOTH_EDGE            = 3u,
    ENET_MAC_MCGR_TOGGLE_OUTPUT_ON_COMPARE     = 9u,
    ENET_MAC_MCGR_PULSE_OUTPUT_LOW_ON_COMPARE  = 10u,
    ENET_MAC_MCGR_PULSE_OUTPUT_HIGH_ON_COMPARE = 11u
} ENET_MAC_MCGRCmdType;

/**
 * @brief PTP snapshot packet select type
 *
 */
typedef enum
{
    ENET_MAC_PTP_SNAPSHOT_FOR_E2E                   = (0x0u << 14u),
    ENET_MAC_PTP_SNAPSHOT_FOR_SYNC                  = (0x1u << 14u),
    ENET_MAC_PTP_SNAPSHOT_FOR_DELAYREQ              = (0x3u << 14u),
    ENET_MAC_PTP_SNAPSHOT_FOR_ALL_PTP               = (0x4u << 14u),
    ENET_MAC_PTP_SNAPSHOT_FOR_SLAVE_NODE_EVENT      = (0x5u << 14u),
    ENET_MAC_PTP_SNAPSHOT_FOR_MASTER_NODE_EVENT     = (0x7u << 14u),
    ENET_MAC_PTP_SNAPSHOT_FOR_E2E_EVENT             = (0x8u << 14u),
    ENET_MAC_PTP_SNAPSHOT_FOR_P2P_EVENT             = (0xCu << 14u),
} ENET_MAC_PTPSnapshotMsgType;

/**
 * @brief PTP snapshot network layer select type
 *
 */
typedef enum
{
    ENET_MAC_PTP_OVER_ETHERNET = ENET_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK,
    ENET_MAC_PTP_OVER_IPV4 = ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK,
    ENET_MAC_PTP_OVER_IPV6 = ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK,
} ENET_MAC_PTPPacketLayerType;

/**
 * @brief MAC PTP clock select type
 *
 */
typedef enum
{
    ENET_MAC_PTP_CLK_SEL_PCC        = 0u,
    ENET_MAC_PTP_CLK_SEL_TX_CLK     = 1u
#if ENET_SUPPORT_REFCLK_PIN
    ,
    ENET_MAC_PTP_CLK_SEL_REFCLK_PIN = 2u
#endif
} ENET_MAC_PTPClkSelType;

/**
 * @brief PTP PPS channel direction type
 *
 */
typedef enum
{
    ENET_PTP_PPS_DIR_INPUT  = 0u,
    ENET_PTP_PPS_DIR_OUTPUT = 1u
} ENET_MAC_PPSPinDirType;

/**
 * @brief ENET MTL queue type
 *
 */
typedef enum
{
    ENET_MTL_QUEUE_0 = 0u,
    ENET_MTL_QUEUE_1 = 1u
} ENET_MTL_QueueType;

/**
 * @brief ENET TX schedule algorithm type
 *
 */
typedef enum
{
    ENET_MTL_SCHED_ALGO_WRR  = 0u,  /**< Weighted round robin algorithm. */
    ENET_MTL_SCHED_ALGO_SP   = 3u   /**< Strict priority algorithm. */
} ENET_MTL_TxScheduleAlgorithmType;

/**
 * @brief ENET RX arbitration type
 *
 */
typedef enum
{
    ENET_MTL_RX_ARBITRATION_STRICT_POLICY          = 0u,
    ENET_MTL_RX_ARBITRATION_WEIGHTED_STRICT_POLICY = 1u
} ENET_MTL_RxArbitrationAlgorithmType;

/**
 * @brief MTL debug access type
 *
 */
typedef enum
{
    ENET_MTL_DEBUG_ACCESS_TX_FIFO        = 0u,
    ENET_MTL_DEBUG_ACCESS_TX_STATUS_FIFO = 1u,
    ENET_MTL_DEBUG_ACCESS_TSO_FIFO       = 2u,
    ENET_MTL_DEBUG_ACCESS_RX_FIFO        = 3u
} ENET_MTL_DebugAccessFIFOType;

/**
 * @brief MTL fifo packet status type
 *
 */
typedef enum
{
    ENET_MTL_PACKET_STATE_PACKET_DATA                   = 0u,
    ENET_MTL_PACKET_STATE_TX_CTRL_WORD_RX_NORMAL_STATUS = 1u,
    ENET_MTL_PACKET_STATE_TX_SOP_DATA_RX_LAST_STATUS    = 2u,
    ENET_MTL_PACKET_STATE_TX_EOP_DATA_RX_EOP            = 3u
} ENET_MTL_FIFOPacketStatusType;

/**
 * @brief MTL byte enable type
 *
 */
typedef enum
{
    ENET_MTL_BYTE_0_VALID     = 0u,
    ENET_MTL_BYTE_0_1_VALID   = 1u,
    ENET_MTL_BYTE_0_1_2_VALID = 2u,
    ENET_MTL_BYTE_ALL_VALID   = 3u
} ENET_MTL_ByteEnableType;

/**
 * @brief MTL fifo debug access type
 *
 */
typedef enum
{
    ENET_MTL_FIFO_DEBUG_ACCESS_RESTRICTED   = 0u,
    ENET_MTL_FIFO_DEBUG_ACCESS_UNRESTRICTED = 1u
} ENET_MTL_FIFODebugAccessType;

/**
 * @brief MTL TX threshold type
 *
 */
typedef enum
{
    ENET_MTL_TX_THRESHOLD_32B  = 0u,
    ENET_MTL_TX_THRESHOLD_64B  = 1u,
    ENET_MTL_TX_THRESHOLD_96B  = 2u,
    ENET_MTL_TX_THRESHOLD_128B = 3u,
    ENET_MTL_TX_THRESHOLD_192B = 4u,
    ENET_MTL_TX_THRESHOLD_256B = 5u,
    ENET_MTL_TX_STORE_FORWARD  = (1u << ENET_MTL_TXQ0_OPERATION_MODE_TTC_WIDTH)
} ENET_MTL_TxThresholdType;

/**
 * @brief MTL write controller status type
 *
 */
typedef enum
{
    ENET_MTL_WRITE_CONTROLLER_IDLE   = 0u,
    ENET_MTL_WRITE_CONTROLLER_ACTIVE = 1u
} ENET_MTL_WriteControllerStatusType;

/**
 * @brief MTL read controller status type
 *
 */
typedef enum
{
    ENET_MTL_READ_CONTROLLER_IDLE  = 0u,
    ENET_MTL_READ_CONTROLLER_READ  = 1u,
    ENET_MTL_READ_CONTROLLER_WAIT  = 2u,
    ENET_MTL_READ_CONTROLLER_FLUSH = 3u
} ENET_MTL_ReadControllerStatusType;

/**
 * @brief MTL RX flow control threshold type
 *
 */
typedef enum
{
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_1_KB   = 0u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_1_5_KB = 1u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_2_KB   = 2u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_2_5_KB = 3u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_3_KB   = 4u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_3_5_KB = 5u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_4_KB   = 6u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_4_5_KB = 7u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_5_KB   = 8u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_5_5_KB = 9u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_6_KB   = 10u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_6_5_KB = 11u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_7_KB   = 12u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_7_5_KB = 13u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_8_KB   = 14u,
    ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_8_5_KB = 15u
} ENET_MTL_RxFlowCtrlThresholdType;

/**
 * @brief MTL RX threshold type
 *
 */
typedef enum
{
    ENET_MTL_RX_THRESHOLD_64B  = 0u,
    ENET_MTL_RX_THRESHOLD_32B  = 1u,
    ENET_MTL_RX_THRESHOLD_96B  = 2u,
    ENET_MTL_RX_THRESHOLD_128B = 3u,
    ENET_MTL_RX_STORE_FORWARD  = (1u << ENET_MTL_RXQ0_OPERATION_MODE_RTC_WIDTH)
} ENET_MTL_RxThresholdType;

/**
 * @brief MTL RX queue status type
 *
 */
typedef enum
{
    ENET_MTL_RX_QUEUE_EMPTY                            = 0u,
    ENET_MTL_RX_QUEUE_BELOW_FLOW_CTRL_DEACTIVATE_THRES = 1u,
    ENET_MTL_RX_QUEUE_ABOVE_FLOW_CTRL_ACTIVATE_THRES   = 2u,
    ENET_MTL_RX_QUEUE_FULL                             = 3u
} ENET_MTL_RxQueueStatusType;

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief Multiple of gate control list interval time
 *
 */
typedef enum
{
    ENET_MTL_GCL_INTERVAL_X_1   = 0x0u,
    ENET_MTL_GCL_INTERVAL_X_2   = 0x1u,
    ENET_MTL_GCL_INTERVAL_X_4   = 0x2u,
    ENET_MTL_GCL_INTERVAL_X_8   = 0x3u,
    ENET_MTL_GCL_INTERVAL_X_16  = 0x4u,
    ENET_MTL_GCL_INTERVAL_X_32  = 0x5u,
    ENET_MTL_GCL_INTERVAL_X_64  = 0x6u,
    ENET_MTL_GCL_INTERVAL_X_128 = 0x7u
} ENET_MTL_GCLIntervalMultipleType;

/**
 * @brief Loop count to report Scheduling Error
 *
 */
typedef enum
{
    ENET_MTL_GCL_4_ITERATIONS  = 0x0u,
    ENET_MTL_GCL_8_ITERATIONS  = 0x1u,
    ENET_MTL_GCL_16_ITERATIONS = 0x2u,
    ENET_MTL_GCL_32_ITERATIONS = 0x3u
} ENET_MTL_ScheduleErrorLoopCountType;

/**
 * @brief Gcl related registers
 *
 */
typedef enum
{
    ENET_MTL_GCL_BTR_LOW  = 0x0u,
    ENET_MTL_GCL_BTR_HIGH = 0x1u,
    ENET_MTL_GCL_CTR_LOW  = 0x2u,
    ENET_MTL_GCL_CTR_HIGH = 0x3u,
    ENET_MTL_GCL_TER      = 0x4u,
    ENET_MTL_GCL_LLR      = 0x5
} ENET_MTL_GclRegistersType;

/**
 * @brief Gcl operation type
 *
 */
typedef enum
{
    ENET_MTL_GCL_WRITE = 0x0u,
    ENET_MTL_GCL_READ  = 0x1u
} ENET_MTL_GclOperationType;

/**
 * @brief MTL gate control list index type
 *
 */
typedef enum
{
    ENET_MTL_GCL_NUMBER_0 = 0x0u,
    ENET_MTL_GCL_NUMBER_1 = 0x1u
} ENET_MTL_GateControlListType;
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief ENET DMA channel index type
 *
 */
typedef enum
{
    ENET_DMA_CHANNEL_0 = 0x0u,
    ENET_DMA_CHANNEL_1 = 0x1u
} ENET_DMA_ChannelType;

/**
 * @brief ENET DMA running status
 *
 */
typedef enum
{
    ENET_DMA_STATUS_IDLE   = 0x0u,   /**< The ENET DMA engine is stoppeed */
    ENET_DMA_STATUS_ACTIVE = 0x1u    /**< The ENET DMA engine is running */
} ENET_DMA_StatusType;

/**
 * @brief The interrupt mode of ENET DMA
 *
 */
typedef enum
{
    ENET_DMA_INTM_SBD_PERCH_PULSE           = 0u,  /**< sbd_perch_* are pulse signals and sbd_inter_o will assert */
    ENET_DMA_INTM_SBD_PERCH_LEVEL           = 1u,  /**< sbd_perch_* are level signals and sbd_inter_o will not assert */
    ENET_DMA_INTM_SBD_PERCH_LEVEL_REENTRANT = 2u   /**< sbd_perch_* are level signals and will regenerate if the same event
                                                        occur again before the signals cleared. sbd_inter_o will not assert */
} ENET_DMA_IntModeType;

/**
 * @brief ENET DMA priority ratio type
 *
 */
typedef enum
{
    ENET_DMA_PRIORITY_RATIO_1_1 = 0u, /**< The priority ratio is 1:1 */
    ENET_DMA_PRIORITY_RATIO_2_1 = 1u, /**< The priority ratio is 2:1 */
    ENET_DMA_PRIORITY_RATIO_3_1 = 2u, /**< The priority ratio is 3:1 */
    ENET_DMA_PRIORITY_RATIO_4_1 = 3u, /**< The priority ratio is 4:1 */
    ENET_DMA_PRIORITY_RATIO_5_1 = 4u, /**< The priority ratio is 5:1 */
    ENET_DMA_PRIORITY_RATIO_6_1 = 5u, /**< The priority ratio is 6:1 */
    ENET_DMA_PRIORITY_RATIO_7_1 = 6u, /**< The priority ratio is 7:1 */
    ENET_DMA_PRIORITY_RATIO_8_1 = 7u  /**< The priority ratio is 8:1 */
} ENET_DMA_PriorityRatioType;

/**
 * @brief ENET DMA priority mode type
 *
 */
typedef enum
{
    ENET_DMA_PRIORITY_MODE_RX_TX = 0u, /**< The priority ratio is RX:TX */
    ENET_DMA_PRIORITY_MODE_TX_RX = 1u  /**< The priority ratio is TX:RX */
} ENET_DMA_PriorityModeType;

/**
 * @brief ENET DMA arbitration algorithm between transmit channels
 *
 */
typedef enum
{
    ENET_DMA_TX_ARBITRATION_ALGORITHM_FIXED_PRIORITY          = 0u,   /**< Use the fixed priority for arbitration  */
    ENET_DMA_TX_ARBITRATION_ALGORITHM_WEIGHTED_FIXED_PRIORITY = 1u,   /**< Use the weighted fixed priority for arbitration  */
    ENET_DMA_TX_ARBITRATION_ALGORITHM_WEIGHTED_ROUND_ROBIN    = 2u    /**< Use the weighted round-robin for arbitration */
} ENET_DMA_TxArbitrationAlgorithmType;

/**
 * @brief ENET DMA arbitration scheme between the transmit and receive paths
 *
 */
typedef enum
{
    ENET_DMA_TXRX_ARBITRATION_SCHEME_WEIGHTED_ROUND_ROBIN = 0u,   /**< Use the weighted round-robin for arbitration */
    ENET_DMA_TXRX_ARBITRATION_SCHEME_FIXED_PRIORITY       = 1u    /**< Use the fixed priority for arbitration  */
} ENET_DMA_ArbitrationSchemeType;

/**
 * @brief ENET DMA burst mode type
 *
 */
typedef enum
{
    ENET_BURSTLENGTH_FIXED      = ENET_DMA_SYSBUS_MODE_FB_MASK,   /**< Use the fixed burst */
    ENET_BURSTLENGTH_MIXED      = ENET_DMA_SYSBUS_MODE_MB_MASK    /**< Use the mixed burst Length  */
} ENET_DMA_BurstModeType;

/**
 * @brief ENET DMA interrupt flag type
 *
 */
typedef enum
{
    ENET_DMA_TX_INTERRUPT                       = ENET_DMA_CH0_INTERRUPT_ENABLE_TIE_MASK,
    ENET_DMA_TX_STOPPED_INTERRUPT               = ENET_DMA_CH0_INTERRUPT_ENABLE_TXSE_MASK,
    ENET_DMA_TX_BUFFER_UNAVAILABLE_INTERRUPT    = ENET_DMA_CH0_INTERRUPT_ENABLE_TBUE_MASK,
    ENET_DMA_RX_INTERRUPT                       = ENET_DMA_CH0_INTERRUPT_ENABLE_RIE_MASK,
    ENET_DMA_RX_BUFFER_UNAVAILABLE_INTERRUPT    = ENET_DMA_CH0_INTERRUPT_ENABLE_RBUE_MASK,
    ENET_DMA_RX_STOPPED_INTERRUPT               = ENET_DMA_CH0_INTERRUPT_ENABLE_RSE_MASK,
    ENET_DMA_RX_WATCHDOG_TIMEOUT_INTERRUPT      = ENET_DMA_CH0_INTERRUPT_ENABLE_RWTE_MASK,
    ENET_DMA_EARLY_TX_INTERRUPT                 = ENET_DMA_CH0_INTERRUPT_ENABLE_ETIE_MASK,
    ENET_DMA_EARLY_RX_INTERRUPT                 = ENET_DMA_CH0_INTERRUPT_ENABLE_ERIE_MASK,
    ENET_DMA_FATAL_BUS_ERROR_INTERRUPT          = ENET_DMA_CH0_INTERRUPT_ENABLE_FBEE_MASK,
    ENET_DMA_CONTEXT_DESCRIPTOR_ERROR_INTERRUPT = ENET_DMA_CH0_INTERRUPT_ENABLE_CDEE_MASK,
    ENET_DMA_ABNORMAL_INTERRUPT                 = ENET_DMA_CH0_INTERRUPT_ENABLE_AIE_MASK,
    ENET_DMA_NORMAL_INTERRUPT                   = ENET_DMA_CH0_INTERRUPT_ENABLE_NIE_MASK
} ENET_DMA_InterruptFlagType;

/**
 * @brief ENET DMA watchdog counter unit type
 *
 */
typedef enum
{
    ENET_DMA_WDG_COUNTER_UNIT_256_CYCLE  = 0x0u,
    ENET_DMA_WDG_COUNTER_UNIT_512_CYCLE  = 0x1u,
    ENET_DMA_WDG_COUNTER_UNIT_1024_CYCLE = 0x2u,
    ENET_DMA_WDG_COUNTER_UNIT_2048_CYCLE = 0x3u
} ENET_DMA_WDGCounterUnitType;

/**
 * @brief ENET DMA RX error type
 *
 */
typedef enum
{
    ENET_DMA_RX_NO_ERROR               = 0x0u,
    ENET_DMA_RX_READ_DESCRIPTER_ERROR  = 0x7u,
    ENET_DMA_RX_WRITE_DESCRIPTER_ERROR = 0x6u,
    ENET_DMA_RX_READ_BUFFER_ERROR      = 0x5u,
    ENET_DMA_RX_WRITE_BUFFER_ERROR     = 0x4u
} ENET_DMA_RxErrorType;

/**
 * @brief ENET DMA TX error type
 *
 */
typedef enum
{
    ENET_DMA_TX_NO_ERROR               = 0x0u,
    ENET_DMA_TX_READ_DESCRIPTER_ERROR  = 0x7u,
    ENET_DMA_TX_WRITE_DESCRIPTER_ERROR = 0x6u,
    ENET_DMA_TX_READ_BUFFER_ERROR      = 0x5u,
    ENET_DMA_TX_WRITE_BUFFER_ERROR     = 0x4u
} ENET_DMA_TxErrorType;


/** ================================================================ *
 *                      ENET system control
 * ================================================================ */

#if ENET_SYSTEM_CONTROL_SMISC
/**
 * @brief Set ENET clock software reset
 *
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetEnetClkSoftwareResetEnFlag(void)
{
    SMISC->PERICTLR |= SMISC_PERICTLR_ENET_CLK_SW_RESET_MASK;
}

/**
 * @brief Set PHY interface mode
 *
 * @param [in] eMode PHY interface mode
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetPhyMiiMode(ENET_MAC_MiiModeType eMode)
{
    SMISC->PERICTLR = (SMISC->PERICTLR & ~SMISC_PERICTLR_ENET_RMIIEN_MASK) |
                       SMISC_PERICTLR_ENET_RMIIEN((eMode == ENET_MAC_PHY_RMII) ? 1u : 0u);
}

/**
 * @brief Get TX clock select source
 *
 * @return ENET_MAC_TxClkSelType
 */
LOCAL_INLINE ENET_MAC_TxClkSelType ENET_HWA_Sysctrl_GetTxClockSrc(void)
{
    uint32_t u32TmpVal = 0u;
    u32TmpVal = (SMISC->PERICTLR & SMISC_PERICTLR_RMII_CLK_SEL_MASK) >> SMISC_PERICTLR_RMII_CLK_SEL_SHIFT;
    return (ENET_MAC_TxClkSelType)(u32TmpVal + 1u);
}

/**
 * @brief Set TX clock select source
 *
 * @param [in] eClkSrc TX clock source
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetTxClockSrc(ENET_MAC_TxClkSelType eClkSrc)
{
    uint32_t u32TmpVal = (uint32_t)eClkSrc - 1u;
    SMISC->PERICTLR = (SMISC->PERICTLR & ~SMISC_PERICTLR_RMII_CLK_SEL_MASK) |
                       SMISC_PERICTLR_RMII_CLK_SEL(u32TmpVal);
}

/**
 * @brief Select the clock source of PTP module.
 *
 * @param [in] eClkSrc The clock source type
 */
LOCAL_INLINE ENET_MAC_PTPClkSelType ENET_HWA_Sysctrl_GetPTPClkSrc(void)
{
    return (ENET_MAC_PTPClkSelType)((SMISC->PERICTLR & SMISC_PERICTLR_ENET_TS_CLKSEL_MASK) >> SMISC_PERICTLR_ENET_TS_CLKSEL_SHIFT);
}

/**
 * @brief Select the clock source of PTP module.
 *
 * @param [in] eClkSrc The clock source type
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetPTPClkSrc(ENET_MAC_PTPClkSelType eClkSrc)
{
    SMISC->PERICTLR = (SMISC->PERICTLR & ~SMISC_PERICTLR_ENET_TS_CLKSEL_MASK) |
                       SMISC_PERICTLR_ENET_TS_CLKSEL(eClkSrc);
}

/**
 * @brief Get MAC 5M mode enable flag
 *
 * @return true 5M mode is enabled
 * @return false 5M mode is disabled
 */
LOCAL_INLINE bool ENET_HWA_Sysctrl_Get5MModeEnFlag(void)
{
    return ((SMISC->PERICTLR & SMISC_PERICTLR_ENET_5M_MODE_MASK) != 0u) ? true : false;
}

/**
 * @brief Set MAC 5M mode enable flag
 *
 * @param [in] bEnable enable or disable 5M mode
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_Set5MModeEnFlag(bool bEnable)
{
    SMISC->PERICTLR = (SMISC->PERICTLR & ~SMISC_PERICTLR_ENET_5M_MODE_MASK) |
                       SMISC_PERICTLR_ENET_5M_MODE(bEnable);
}

/**
 * @brief Get PPS IO port direction
 *
 * @param [in] eChannel PPS channel
 * @return ENET_MAC_PPSPinDirType
 */
LOCAL_INLINE ENET_MAC_PPSPinDirType ENET_HWA_Sysctrl_GetPPSPinDirection(ENET_MAC_PPSChannelType eChannel)
{
    uint32_t u32TmpVal;
    u32TmpVal = (SMISC->PERICTLR & (1u << (SMISC_PERICTLR_ENET_PPS0_OBECTL_SHIFT + eChannel)));
    return (u32TmpVal != 0u) ? ENET_PTP_PPS_DIR_OUTPUT : ENET_PTP_PPS_DIR_INPUT;
}

/**
 * @brief Set PPS IO port direction
 *
 * @param [in] eChannel PPS channel
 * @param [in] eDir IO port direction
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetPPSPinDirection(ENET_MAC_PPSChannelType eChannel,
                                                      ENET_MAC_PPSPinDirType eDir)
{
    SMISC->PERICTLR = (SMISC->PERICTLR & (~(1u << (SMISC_PERICTLR_ENET_PPS0_OBECTL_SHIFT + eChannel)))) |
                       ((uint32_t)(((uint32_t)(eDir)) << (SMISC_PERICTLR_ENET_PPS0_OBECTL_SHIFT + eChannel)));
}
#endif /* ENET_SYSTEM_CONTROL_SMISC */

#if ENET_SYSTEM_CONTROL_SCM
/**
 * @brief Set ENET clock software reset
 *
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetEnetClkSoftwareResetEnFlag(void)
{
    SCM->SCM_ENET |= SCM_ENET_ENET_CLK_SWRST_MASK;
}

/**
 * @brief Set PHY interface mode
 *
 * @param [in] eMode PHY interface mode
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetPhyMiiMode(ENET_MAC_MiiModeType eMode)
{
    SCM->SCM_ENET = (SCM->SCM_ENET & (~SCM_ENET_PHY_SEL_MASK)) | SCM_ENET_PHY_SEL(eMode);
}

#if ENET_SUPPORT_RGMII
/**
 * @brief Get RGMII clock select source
 *
 * @return ENET_MAC_RGMIIClkSelType
 */
LOCAL_INLINE ENET_MAC_RGMIIClkSelType ENET_HWA_Sysctrl_GetRGMIIClockSrc(void)
{
    return (ENET_MAC_RGMIIClkSelType)((SCM->SCM_ENET & SCM_ENET_ENET_RGMII_CLK_SEL_MASK) >> SCM_ENET_ENET_RGMII_CLK_SEL_SHIFT);
}

/**
 * @brief Set RGMII clock select source
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eClkSrc RGMII clock source
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetRGMIIClockSrc(ENET_MAC_RGMIIClkSelType eClkSrc)
{
    SCM->SCM_ENET = (SCM->SCM_ENET & ~SCM_ENET_ENET_RGMII_CLK_SEL_MASK) | SCM_ENET_ENET_RGMII_CLK_SEL(eClkSrc);
}
#endif

/**
 * @brief Get TX clock select source
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_TxClkSelType
 */
LOCAL_INLINE ENET_MAC_TxClkSelType ENET_HWA_Sysctrl_GetTxClockSrc(void)
{
    return (ENET_MAC_TxClkSelType)((SCM->SCM_ENET & SCM_ENET_ENET_TXCLK_SEL_MASK) >> SCM_ENET_ENET_TXCLK_SEL_SHIFT);
}

/**
 * @brief Set TX clock select source
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eClkSrc TX clock source
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetTxClockSrc(ENET_MAC_TxClkSelType eClkSrc)
{
    SCM->SCM_ENET = (SCM->SCM_ENET & ~SCM_ENET_ENET_TXCLK_SEL_MASK) | SCM_ENET_ENET_TXCLK_SEL(eClkSrc);
}

/**
 * @brief Select the clock source of PTP module.
 *
 * @return eClkSrc The clock source type
 */
LOCAL_INLINE ENET_MAC_PTPClkSelType ENET_HWA_Sysctrl_GetPTPClkSrc(void)
{
    return (ENET_MAC_PTPClkSelType)((SCM->SCM_ENET & SCM_ENET_PTPCLK_SEL_MASK) >> SCM_ENET_PTPCLK_SEL_SHIFT);
}

/**
 * @brief Select the clock source of PTP module.
 *
 * @param [in] eClkSrc The PTP clock source
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetPTPClkSrc(ENET_MAC_PTPClkSelType eClkSrc)
{
    SCM->SCM_ENET = (SCM->SCM_ENET & ~SCM_ENET_PTPCLK_SEL_MASK) | SCM_ENET_PTPCLK_SEL(eClkSrc);
}

/**
 * @brief Get MAC 5M mode enable flag
 *
 * @return true 5M mode is enabled
 * @return false 5M mode is disabled
 */
LOCAL_INLINE bool ENET_HWA_Sysctrl_Get5MModeEnFlag(void)
{
    return ((SCM->SCM_ENET & SCM_ENET_RMII_5M_MASK) != 0u) ? true : false;
}

/**
 * @brief Set MAC 5M mode enable flag
 *
 * @param [in] bEnable enable or disable 5M mode
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_Set5MModeEnFlag(bool bEnable)
{
    SCM->SCM_ENET = (SCM->SCM_ENET & ~SCM_ENET_RMII_5M_MASK) | SCM_ENET_RMII_5M(bEnable);
}

/**
 * @brief Get PPS IO port direction
 *
 * @param [in] eChannel PPS channel
 * @return ENET_MAC_PPSPinDirType
 */
LOCAL_INLINE ENET_MAC_PPSPinDirType ENET_HWA_Sysctrl_GetPPSPinDirection(ENET_MAC_PPSChannelType eChannel)
{
    uint32_t u32TmpVal;
    u32TmpVal = SCM->SCM_ENET & (1u << (SCM_ENET_ENET_TIMER_OBE_SHIFT + (uint32_t)eChannel));
    return (u32TmpVal != 0u) ? ENET_PTP_PPS_DIR_OUTPUT : ENET_PTP_PPS_DIR_INPUT;
}

/**
 * @brief Set PPS IO port direction
 *
 * @param [in] eChannel PPS channel
 * @param [in] eDir IO port direction
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetPPSPinDirection(ENET_MAC_PPSChannelType eChannel,
                                                      ENET_MAC_PPSPinDirType eDir)
{
    SCM->SCM_ENET = (SCM->SCM_ENET & (~(1u << (SCM_ENET_ENET_TIMER_OBE_SHIFT + (uint32_t) eChannel)))) |
                     SCM_ENET_ENET_TIMER_OBE((uint32_t)eDir << (uint32_t)eChannel);
}

/**
 * @brief Get Mii TX clock output enable flag
 *
 * @return true Mii TX clock output is enabled
 * @return false Mii TX clock output is disabled
 */
LOCAL_INLINE bool ENET_HWA_Sysctrl_GetMiiTxClkOutputEnFlag(void)
{
    return ((SCM->SCM_ENET & SCM_ENET_MII_TX_CLK_OBE_MASK) != 0u) ? true : false;
}

/**
 * @brief Set Mii TX clock output enable flag
 *
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_Sysctrl_SetMiiTxClkOutputEnFlag(bool bEnable)
{
    SCM->SCM_ENET = (SCM->SCM_ENET & ~SCM_ENET_MII_TX_CLK_OBE_MASK) | SCM_ENET_MII_TX_CLK_OBE(bEnable);
}
#endif /* ENET_SYSTEM_CONTROL_SCM */


/** ================================================================ *
 *                  ENET MAC Configuration and Status               *
 * ================================================================ */


/**
 * @brief Get the MAC Configuration Register value.
 *
 * @param [in] pEnet The base address of the ENET instance
 * @return  The Register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetConfiguration(const ENET_Type *const pEnet)
{
    return pEnet->MAC_CONFIGURATION;
}

/**
 * @brief Set the MAC Configuration Register value.
 *
 * @param [in] pEnet The base address of the ENET instance
 * @param [in] u32Config The Configuration Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetConfiguration(ENET_Type *const pEnet, uint32_t u32Config)
{
    pEnet->MAC_CONFIGURATION = u32Config;
}

/**
 * @brief Get the source address insertion or replacement control type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return source address insertion or replacement control type
 */
LOCAL_INLINE ENET_MAC_SrcAddrCtrlType ENET_HWA_MAC_GetSrcAddrInsertReplaceCtrl(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_SARC_MASK) >> ENET_MAC_CONFIGURATION_SARC_SHIFT;
    return (ENET_MAC_SrcAddrCtrlType)u32TmpVal;
}

/**
 * @brief Set the source address insertion or replacement control type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eInsertReplaceCtrl source address insertion or replacement control type
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSrcAddrInsertReplaceCtrl(ENET_Type *const pEnet,
                                                           ENET_MAC_SrcAddrCtrlType eInsertReplaceCtrl)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_SARC_MASK) |
                               ENET_MAC_CONFIGURATION_SARC(eInsertReplaceCtrl);
}

/**
 * @brief Get checksum offload function enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Checksum offload function is enabled
 * @return false Checksum offload function is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetIPChecksumOffloadEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_IPC_MASK) >> ENET_MAC_CONFIGURATION_IPC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set checksum offload function enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetIPChecksumOffloadEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_IPC_MASK) |
                               ENET_MAC_CONFIGURATION_IPC(bEnable ? 1u : 0u);
}

/**
 * @brief Get the minimum Inter-Packet Gap
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_InterPacketGapType.
 */
LOCAL_INLINE ENET_MAC_InterPacketGapType ENET_HWA_MAC_GetMinInterPacketGap(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_IPG_MASK) >> ENET_MAC_CONFIGURATION_IPG_SHIFT;
    return (ENET_MAC_InterPacketGapType)u32TmpVal;
}

/**
 * @brief Set the minimum Inter-Packet Gap value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eGap Inter-Packet Gap value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMinInterPacketGap(ENET_Type *const pEnet, ENET_MAC_InterPacketGapType eGap)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_IPG_MASK) |
                               ENET_MAC_CONFIGURATION_IPG(eGap);
}

/**
 * @brief Get giant packet size Limit control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Giant packet size Limit control is enabled
 * @return false Giant packet size Limit control is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetGiantPacketSizeLimitCtrlEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_GPSLCE_MASK) >>
                         ENET_MAC_CONFIGURATION_GPSLCE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set giant packet size Limit control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetGiantPacketSizeLimitCtrlEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_GPSLCE_MASK) |
                               ENET_MAC_CONFIGURATION_GPSLCE(bEnable ? 1u : 0u);
}

/**
 * @brief Get 2K packet support enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true 2K packet support is enabled
 * @return false 2K packet support is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_Get2KPacketSupportFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_S2KP_MASK) >>
                         ENET_MAC_CONFIGURATION_S2KP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set 2K packet support enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_Set2KPacketSupportFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_S2KP_MASK) |
                               ENET_MAC_CONFIGURATION_S2KP(bEnable ? 1u : 0u);
}

/**
 * @brief Get CRC stripping for type packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true CRC stripping for type packets is enabled
 * @return false CRC stripping for type packets is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetStripTypePacketCRCEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_CST_MASK) >>
                         ENET_MAC_CONFIGURATION_CST_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set CRC stripping for type packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetStripTypePacketCRCEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_CST_MASK) |
                               ENET_MAC_CONFIGURATION_CST(bEnable ? 1u : 0u);
}

/**
 * @brief Get automatic Pad or CRC stripping enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Automatic Pad or CRC stripping is enabled
 * @return false Automatic Pad or CRC stripping is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetAutoStripPadOrCRCEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_ACS_MASK) >> ENET_MAC_CONFIGURATION_ACS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set automatic Pad or CRC stripping enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetAutoStripPadOrCRCEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_ACS_MASK) |
                               ENET_MAC_CONFIGURATION_ACS(bEnable ? 1u : 0u);
}

/**
 * @brief Get receiver watchdog timer disabled flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Receiver watchdog timer is disabled
 * @return false Receiver watchdog timer is enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetWatchdogDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_WD_MASK) >> ENET_MAC_CONFIGURATION_WD_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receiver watchdog timer disabled flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetWatchdogDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_WD_MASK) |
                               ENET_MAC_CONFIGURATION_WD(bDisable ? 1u : 0u);
}

/**
 * @brief Get transmitter jabber timer disabled flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Transmitter jabber timer is disabled
 * @return false Transmitter jabber timer is enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetJabberTimerDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_JD_MASK) >> ENET_MAC_CONFIGURATION_JD_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set transmitter jabber timer disabled flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetJabberTimerDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_JD_MASK) |
                               ENET_MAC_CONFIGURATION_JD(bDisable ? 1u : 0u);
}

/**
 * @brief Get jumbo packet enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Jumbo packet is enabled
 * @return false Jumbo packet is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetJumboPacketEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_JE_MASK) >> ENET_MAC_CONFIGURATION_JE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set jumbo packet enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetJumboPacketEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_JE_MASK) |
                               ENET_MAC_CONFIGURATION_JE(bEnable ? 1u : 0u);
}

/**
 * @brief Get ethernet line speed
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_SpeedType
 */
LOCAL_INLINE ENET_MAC_SpeedType ENET_HWA_MAC_GetSpeed(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & (ENET_MAC_CONFIGURATION_FES_MASK | ENET_MAC_CONFIGURATION_PS_MASK))
                         >> ENET_MAC_CONFIGURATION_FES_SHIFT;
    return (ENET_MAC_SpeedType)u32TmpVal;
}

/**
 * @brief Set ethernet line speed
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eSpeed Ethernet line speed
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSpeed(ENET_Type *const pEnet, ENET_MAC_SpeedType eSpeed)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~(ENET_MAC_CONFIGURATION_FES_MASK | ENET_MAC_CONFIGURATION_PS_MASK)) |
                               (((uint32_t)eSpeed << ENET_MAC_CONFIGURATION_FES_SHIFT) &
                               (ENET_MAC_CONFIGURATION_FES_MASK | ENET_MAC_CONFIGURATION_PS_MASK));
}

/**
 * @brief Get ethernet duplex mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_DuplexModeType
 */
LOCAL_INLINE ENET_MAC_DuplexModeType ENET_HWA_MAC_GetDuplexMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_DM_MASK) >> ENET_MAC_CONFIGURATION_DM_SHIFT;
    return (ENET_MAC_DuplexModeType)u32TmpVal;
}

/**
 * @brief Set ethernet duplex mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eMode Ethernet duplex mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetDuplexMode(ENET_Type *const pEnet, ENET_MAC_DuplexModeType eMode)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_DM_MASK) |
                               ENET_MAC_CONFIGURATION_DM(eMode);
}

/**
 * @brief Get loopback mode enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Loopback mode is enabled
 * @return false Loopback mode is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLoopbackModeEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_LM_MASK) >> ENET_MAC_CONFIGURATION_LM_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set loopback mode enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLoopbackModeEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_LM_MASK) |
                               ENET_MAC_CONFIGURATION_LM(bEnable ? 1u : 0u);
}

/**
 * @brief Get carrier sense before transmission enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Carrier sense before transmission is enabled
 * @return false Carrier sense before transmission is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetFullDuplexCRSEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_ECRSFD_MASK) >>
                         ENET_MAC_CONFIGURATION_ECRSFD_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set carrier sense before transmission enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetFullDuplexCRSEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_ECRSFD_MASK) |
                               ENET_MAC_CONFIGURATION_ECRSFD(bEnable ? 1u : 0u);
}

/**
 * @brief Get receive own disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Receive own is disabled
 * @return false Receive own is enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetReceiveOwnDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_DO_MASK) >>
                         ENET_MAC_CONFIGURATION_DO_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive own disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetReceiveOwnDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_DO_MASK) |
                               ENET_MAC_CONFIGURATION_DO(bDisable ? 1u : 0u);
}

/**
 * @brief Get carrier sense during transmission disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Carrier sense during transmission is disabled
 * @return false Carrier sense during transmission is enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetHalfDuplexCRSDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_DCRS_MASK) >>
                         ENET_MAC_CONFIGURATION_DCRS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set carrier sense during transmission disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetHalfDuplexCRSDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_DCRS_MASK) |
                               ENET_MAC_CONFIGURATION_DCRS(bDisable ? 1u : 0u);
}

/**
 * @brief Get transmission retry disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Ttransmission retry is disabled
 * @return false Transmission retry is enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRetryDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_DR_MASK) >>
                         ENET_MAC_CONFIGURATION_DR_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set transmission retry disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRetryDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_DR_MASK) |
                               ENET_MAC_CONFIGURATION_DR(bDisable ? 1u : 0u);
}

/**
 * @brief Get back-off limit
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_BackOffLimitType
 */
LOCAL_INLINE ENET_MAC_BackOffLimitType ENET_HWA_MAC_GetBackOffLimit(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_BL_MASK) >>
                         ENET_MAC_CONFIGURATION_BL_SHIFT;
    return (ENET_MAC_BackOffLimitType)u32TmpVal;
}

/**
 * @brief Set back-off limit
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eLimit Back-off limit type value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetBackOffLimit(ENET_Type *const pEnet, ENET_MAC_BackOffLimitType eLimit)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_BL_MASK) |
                               ENET_MAC_CONFIGURATION_BL(eLimit);
}

/**
 * @brief Get deferral check enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Deferral check is enabled
 * @return false Deferral check is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetDeferralCheckEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_DC_MASK) >>
                         ENET_MAC_CONFIGURATION_DC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set deferral check enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetDeferralCheckEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_DC_MASK) |
                               ENET_MAC_CONFIGURATION_DC(bEnable ? 1u : 0u);
}

/**
 * @brief Get transmitter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Transmitter is enabled
 * @return false Transmitter is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_TE_MASK) >>
                         ENET_MAC_CONFIGURATION_TE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set transmitter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTxEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_TE_MASK) |
                               ENET_MAC_CONFIGURATION_TE(bEnable ? 1u : 0u);
}

/**
 * @brief Get receiver enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Receiver is enabled
 * @return false Receiver is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_RE_MASK) >>
                         ENET_MAC_CONFIGURATION_RE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receiver enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_CONFIGURATION = (pEnet->MAC_CONFIGURATION & ~ENET_MAC_CONFIGURATION_RE_MASK) |
                               ENET_MAC_CONFIGURATION_RE(bEnable ? 1u : 0u);
}

/**
 * @brief Get the MAC extended configuration register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return The register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetExtConfiguration(const ENET_Type *const pEnet)
{
    return pEnet->MAC_EXT_CONFIGURATION;
}

/**
 * @brief Set the MAC extended configuration register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Configuration The configuration register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetExtConfiguration(ENET_Type *const pEnet, uint32_t u32Configuration)
{
    pEnet->MAC_EXT_CONFIGURATION = u32Configuration;
}

/**
 * @brief Get the MAC extended inter-packet gap
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_ExtInterPacketGapType
 */
LOCAL_INLINE ENET_MAC_ExtInterPacketGapType ENET_HWA_MAC_GetExtInterPacketGap(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_EXT_CONFIGURATION & ENET_MAC_EXT_CONFIGURATION_EIPG_MASK) >>
                         ENET_MAC_EXT_CONFIGURATION_EIPG_SHIFT;
    return (ENET_MAC_ExtInterPacketGapType)u32TmpVal;
}

/**
 * @brief Set the MAC extended inter-packet gap
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eGap The MAC extended inter-packet gap value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetExtInterPacketGap(ENET_Type *const pEnet, ENET_MAC_ExtInterPacketGapType eGap)
{
    pEnet->MAC_EXT_CONFIGURATION = (pEnet->MAC_EXT_CONFIGURATION & ~ENET_MAC_EXT_CONFIGURATION_EIPG_MASK) |
                                   ENET_MAC_EXT_CONFIGURATION_EIPG(eGap);
}

/**
 * @brief Get extended inter-packet gap enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Extended inter-packet gapis enabled
 * @return false Extended inter-packet gap is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetExtInterPacketGapEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_EXT_CONFIGURATION & ENET_MAC_EXT_CONFIGURATION_EIPGEN_MASK) >>
                         ENET_MAC_EXT_CONFIGURATION_EIPGEN_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set extended inter-packet gap enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetExtInterPacketGapEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_EXT_CONFIGURATION = (pEnet->MAC_EXT_CONFIGURATION & ~ENET_MAC_EXT_CONFIGURATION_EIPGEN_MASK) |
                                   ENET_MAC_EXT_CONFIGURATION_EIPGEN(bEnable ? 1u : 0u);
}

/**
 * @brief Get packet duplication control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Packet duplication control enabled
 * @return false Packet duplication control is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPacketDuplicationCtrlEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_EXT_CONFIGURATION & ENET_MAC_EXT_CONFIGURATION_PDC_MASK) >>
                         ENET_MAC_EXT_CONFIGURATION_PDC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set packet duplication control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPacketDuplicationCtrlEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_EXT_CONFIGURATION = (pEnet->MAC_EXT_CONFIGURATION & ~ENET_MAC_EXT_CONFIGURATION_PDC_MASK) |
                                   ENET_MAC_EXT_CONFIGURATION_PDC(bEnable ? 1u : 0u);
}

/**
 * @brief Get unicast slow protocol packet detect method
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_SlowProtocolDetectType
 */
LOCAL_INLINE ENET_MAC_SlowProtocolDetectType ENET_HWA_MAC_GetUnicastSlowProtocolPacketDetectMethod(
            const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_EXT_CONFIGURATION & ENET_MAC_EXT_CONFIGURATION_USP_MASK) >>
                         ENET_MAC_EXT_CONFIGURATION_USP_SHIFT;
    return (ENET_MAC_SlowProtocolDetectType)u32TmpVal;
}

/**
 * @brief Set unicast slow protocol packet detect method
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eMethod Unicast slow protocol packet detect method value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetUnicastSlowProtocolPacketDetectMethod(ENET_Type *const pEnet,
                                                                        ENET_MAC_SlowProtocolDetectType eMethod)
{
    pEnet->MAC_EXT_CONFIGURATION = (pEnet->MAC_EXT_CONFIGURATION & ~ENET_MAC_EXT_CONFIGURATION_USP_MASK) |
                                   ENET_MAC_EXT_CONFIGURATION_USP(eMethod);
}

/**
 * @brief Get slow protocol detection enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Slow protocol detection enabled
 * @return false Slow protocol detection is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetSlowDetectEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_EXT_CONFIGURATION & ENET_MAC_EXT_CONFIGURATION_SPEN_MASK) >>
                         ENET_MAC_EXT_CONFIGURATION_SPEN_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set slow protocol detection enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSlowDetectEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_EXT_CONFIGURATION = (pEnet->MAC_EXT_CONFIGURATION & ~ENET_MAC_EXT_CONFIGURATION_SPEN_MASK) |
                                   ENET_MAC_EXT_CONFIGURATION_SPEN(bEnable ? 1u : 0u);
}

/**
 * @brief Get CRC checking for Received packets disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true CRC checking for rReceived packets is disabled
 * @return false CRC checking for rReceived packets is enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxCRCCheckDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_EXT_CONFIGURATION & ENET_MAC_EXT_CONFIGURATION_DCRCC_MASK) >>
                         ENET_MAC_EXT_CONFIGURATION_DCRCC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set CRC checking for rReceived packets disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxCRCCheckDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_EXT_CONFIGURATION = (pEnet->MAC_EXT_CONFIGURATION & ~ENET_MAC_EXT_CONFIGURATION_DCRCC_MASK) |
                                   ENET_MAC_EXT_CONFIGURATION_DCRCC(bDisable ? 1u : 0u);
}

/**
 * @brief Get giant packet size limit value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Giant packet size limit value
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetGiantPacketSizeLimit(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_EXT_CONFIGURATION & ENET_MAC_EXT_CONFIGURATION_GPSL_MASK) >>
                         ENET_MAC_EXT_CONFIGURATION_GPSL_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set giant packet size limit value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u16SizeLimit Giant packet size limit value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetGiantPacketSizeLimit(ENET_Type *const pEnet, uint16_t u16SizeLimit)
{
    pEnet->MAC_EXT_CONFIGURATION = (pEnet->MAC_EXT_CONFIGURATION & ~ENET_MAC_EXT_CONFIGURATION_GPSL_MASK) |
                                   ENET_MAC_EXT_CONFIGURATION_GPSL(u16SizeLimit);
}

/**
 * @brief Get the MAC packet filter register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return The register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPacketFilter(const ENET_Type *const pEnet)
{
    return pEnet->MAC_PACKET_FILTER;
}

/**
 * @brief Set the MAC packet filter register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32FilterCtrl The filter control value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPacketFilter(ENET_Type *const pEnet, uint32_t u32FilterCtrl)
{
    pEnet->MAC_PACKET_FILTER = u32FilterCtrl;
}

/**
 * @brief Get receive all packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Receive all packets enabled
 * @return false Receive all packets is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetReceiveAllEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_RA_MASK) >> ENET_MAC_PACKET_FILTER_RA_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive all packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetReceiveAllEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_RA_MASK) |
                               ENET_MAC_PACKET_FILTER_RA(bEnable ? 1u : 0u);
}

/**
 * @brief Get drop non-TCP/UDP over IP packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Drop non-TCP/UDP over IP packets
 * @return false Forward non-TCP/UDP over IP packets
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetDropNonTCPUDPOverIPEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_DNTU_MASK) >> ENET_MAC_PACKET_FILTER_DNTU_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set drop non-TCP/UDP over IP packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Drop or forward non-TCP/UDP over IP packets
 */
LOCAL_INLINE void ENET_HWA_MAC_SetDropNonTCPUDPOverIPEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_DNTU_MASK) |
                               ENET_MAC_PACKET_FILTER_DNTU(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 3 and layer 4 filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Enable layer 3 and layer 4 filter
 * @return false Disable layer 3 and layer 4 filter
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer3Layer4FilterEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_IPFE_MASK) >> ENET_MAC_PACKET_FILTER_IPFE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 3 and layer 4 filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Layer4FilterEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_IPFE_MASK) |
                               ENET_MAC_PACKET_FILTER_IPFE(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Enable VLAN tag filter
 * @return false Disable VLAN tag filter
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetVLANTagFilterEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_VTFE_MASK) >> ENET_MAC_PACKET_FILTER_VTFE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN tag filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagFilterFilterEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_VTFE_MASK) |
                               ENET_MAC_PACKET_FILTER_VTFE(bEnable ? 1u : 0u);
}

/**
 * @brief Get hash or perfect filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Enable hash or pPerfect filter
 * @return false Disable hash or pPerfect filter
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetHashOrPerfectFilterEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_HPF_MASK) >> ENET_MAC_PACKET_FILTER_HPF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set hash or perfect filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetHashOrPerfectFilterEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_HPF_MASK) |
                               ENET_MAC_PACKET_FILTER_HPF(bEnable ? 1u : 0u);
}

/**
 * @brief Get source address filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Enable source address  filter
 * @return false Disable source address fFilter
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetSourceAddressFilterEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_SAF_MASK) >> ENET_MAC_PACKET_FILTER_SAF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set source address filter enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSourceAddressFilterEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_SAF_MASK) |
                               ENET_MAC_PACKET_FILTER_SAF(bEnable ? 1u : 0u);
}

/**
 * @brief Get source address filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_AddrFilterModeType
 */
LOCAL_INLINE ENET_MAC_AddrFilterModeType ENET_HWA_MAC_GetSrcAddrFilterMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_SAIF_MASK) >> ENET_MAC_PACKET_FILTER_SAIF_SHIFT;
    return (ENET_MAC_AddrFilterModeType)u32TmpVal;
}

/**
 * @brief Set source address filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eFilterMode Source address filter mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSrcAddrFilterMode(ENET_Type *const pEnet, ENET_MAC_AddrFilterModeType eFilterMode)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_SAIF_MASK) |
                               ENET_MAC_PACKET_FILTER_SAIF(eFilterMode);
}

/**
 * @brief Get control packets filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_CtrlPacketFilterModeType
 */
LOCAL_INLINE ENET_MAC_CtrlPacketFilterModeType ENET_HWA_MAC_GetCtrlPacketFilterMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_PCF_MASK) >> ENET_MAC_PACKET_FILTER_PCF_SHIFT;
    return (ENET_MAC_CtrlPacketFilterModeType)u32TmpVal;
}

/**
 * @brief Set control packets filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eFilterMode Control packets filter mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetCtrlPacketFilterMode(ENET_Type *const pEnet,
                                                       ENET_MAC_CtrlPacketFilterModeType eFilterMode)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_PCF_MASK) |
                               ENET_MAC_PACKET_FILTER_PCF(eFilterMode);
}

/**
 * @brief Get broadcast packets disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Drop broadcast packets
 * @return false receive broadcast packets
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetBroadcastPacketDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_DBF_MASK) >> ENET_MAC_PACKET_FILTER_DBF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set broadcast packets disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetBroadcastPacketDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_DBF_MASK) |
                               ENET_MAC_PACKET_FILTER_DBF(bDisable ? 1u : 0u);
}

/**
 * @brief Get pass all the received multicast packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Pass all the received multicast packets
 * @return false Pass multicast packets that match the multicast filter
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPassAllMulticastEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_PM_MASK) >> ENET_MAC_PACKET_FILTER_PM_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set pass all the received multicast packets enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPassAllMulticastEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_PM_MASK) |
                               ENET_MAC_PACKET_FILTER_PM(bEnable ? 1u : 0u);
}

/**
 * @brief Get destination address filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_AddrFilterModeType
 */
LOCAL_INLINE ENET_MAC_AddrFilterModeType ENET_HWA_MAC_GetDestAddrFilterMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_DAIF_MASK) >> ENET_MAC_PACKET_FILTER_DAIF_SHIFT;
    return (ENET_MAC_AddrFilterModeType)u32TmpVal;
}

/**
 * @brief Set destination address filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param eFilterMode Destination address filter mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetDestAddrFilterMode(ENET_Type *const pEnet, ENET_MAC_AddrFilterModeType eFilterMode)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_DAIF_MASK) |
                               ENET_MAC_PACKET_FILTER_DAIF(eFilterMode);
}

/**
 * @brief Get hash or perfect multicast filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_HashOrPerfectModeType
 */
LOCAL_INLINE ENET_MAC_HashOrPerfectModeType ENET_HWA_MAC_GetHashOrPerfectMulticastMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_HMC_MASK) >> ENET_MAC_PACKET_FILTER_HMC_SHIFT;
    return (ENET_MAC_HashOrPerfectModeType)u32TmpVal;
}

/**
 * @brief Set hash or perfect multicast filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param eMode Hash or perfect multicast filter mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetHashOrPerfectMulticastMode(ENET_Type *const pEnet, ENET_MAC_HashOrPerfectModeType eMode)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_HMC_MASK) |
                               ENET_MAC_PACKET_FILTER_HMC(eMode);
}

/**
 * @brief Get hash or perfect unicast filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_HashOrPerfectModeType
 */
LOCAL_INLINE ENET_MAC_HashOrPerfectModeType ENET_HWA_MAC_GetHashOrPerfectUnicastMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_HMC_MASK) >> ENET_MAC_PACKET_FILTER_HMC_SHIFT;
    return (ENET_MAC_HashOrPerfectModeType)u32TmpVal;
}

/**
 * @brief Set hash or perfect unicast filter mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param eMode Hash or perfect unicast filter mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetHashOrPerfectUnicastMode(ENET_Type *const pEnet, ENET_MAC_HashOrPerfectModeType eMode)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_HUC_MASK) |
                               ENET_MAC_PACKET_FILTER_HUC(eMode);
}

/**
 * @brief Get promiscuous mode enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Enable promiscuous mode
 * @return false Disable promiscuous mode
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPromiscuousModeEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_PACKET_FILTER & ENET_MAC_PACKET_FILTER_PR_MASK) >> ENET_MAC_PACKET_FILTER_PR_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set promiscuous mode enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPromiscuousModeEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_PACKET_FILTER = (pEnet->MAC_PACKET_FILTER & ~ENET_MAC_PACKET_FILTER_PR_MASK) |
                               ENET_MAC_PACKET_FILTER_PR(bEnable ? 1u : 0u);
}

/**
 * @brief Get programmable watchdog timeout register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Watchdog timeout register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetWatchdogTimeout(const ENET_Type *const pEnet)
{
    return pEnet->MAC_WATCHDOG_TIMEOUT;
}

/**
 * @brief Set programmable watchdog timeout register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Settings Watchdog timeout register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetWatchdogTimeout(ENET_Type *const pEnet, uint32_t u32Settings)
{
    pEnet->MAC_WATCHDOG_TIMEOUT = u32Settings;
}

/**
 * @brief Get programmable watchdog enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Programmable watchdog enabled
 * @return false Programmable watchdog disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetWatchdogEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_WATCHDOG_TIMEOUT & ENET_MAC_WATCHDOG_TIMEOUT_PWE_MASK) >>
                         ENET_MAC_WATCHDOG_TIMEOUT_PWE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set programmable watchdog enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetWatchdogEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_WATCHDOG_TIMEOUT = (pEnet->MAC_WATCHDOG_TIMEOUT & ~ENET_MAC_WATCHDOG_TIMEOUT_PWE_MASK) |
                                  ENET_MAC_WATCHDOG_TIMEOUT_PWE(bEnable ? 1u : 0u);
}

/**
 * @brief Get programmable watchdog timer size value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_WDGTimerSizeType
 */
LOCAL_INLINE ENET_MAC_WDGTimerSizeType ENET_HWA_MAC_GetWatchdogTimerSize(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_WATCHDOG_TIMEOUT & ENET_MAC_WATCHDOG_TIMEOUT_WTO_MASK) >>
                         ENET_MAC_WATCHDOG_TIMEOUT_WTO_SHIFT;
    return (ENET_MAC_WDGTimerSizeType)u32TmpVal;
}

/**
 * @brief Set programmable watchdog timer size
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eSize Watchdog timer size
 */
LOCAL_INLINE void ENET_HWA_MAC_SetWatchdogTimerSize(ENET_Type *const pEnet, ENET_MAC_WDGTimerSizeType eSize)
{
    pEnet->MAC_WATCHDOG_TIMEOUT = (pEnet->MAC_WATCHDOG_TIMEOUT & ~ENET_MAC_WATCHDOG_TIMEOUT_WTO_MASK) |
                                  ENET_MAC_WATCHDOG_TIMEOUT_WTO(eSize);
}

/**
 * @brief Get the hash table first 32 bits value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Hash table first 32 bits value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetHashTableFirst32Bits(const ENET_Type *const pEnet)
{
    return pEnet->MAC_HASH_TABLE_REG0;
}

/**
 * @brief Set the hash table first 32 bits value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param u32Hash0 Hash table first 32 bits value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetHashTableFirst32Bits(ENET_Type *const pEnet, uint32_t u32Hash0)
{
    pEnet->MAC_HASH_TABLE_REG0 = u32Hash0;
}

/**
 * @brief Get the hash table second 32 bits value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Hash table second 32 bits value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetHashTableSecond32Bits(const ENET_Type *const pEnet)
{
    return pEnet->MAC_HASH_TABLE_REG1;
}

/**
 * @brief Set the hash table second 32 bits value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Hash1 Hash table second 32 bits value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetHashTableSecond32Bits(ENET_Type *const pEnet, uint32_t u32Hash1)
{
    pEnet->MAC_HASH_TABLE_REG1 = u32Hash1;
}

/**
 * @brief Get VLAN tag control register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return VLAN tag control register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetVLANTagCtrl(const ENET_Type *const pEnet)
{
    return pEnet->MAC_VLAN_TAG_CTRL;
}

/**
 * @brief Set VLAN tag control register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32VlanCtrl Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagCtrl(ENET_Type *const pEnet, uint32_t u32VlanCtrl)
{
    pEnet->MAC_VLAN_TAG_CTRL = u32VlanCtrl;
}

/**
 * @brief Get inner VLAN tag enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Inner VLAN tag is enabled
 * @return false Inner VLAN tag is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxStatusInnerVLANTagEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_EIVLRXS_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_EIVLRXS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set inner VLAN tag enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxStatusInnerVLANTagEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_EIVLRXS_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_EIVLRXS(bEnable ? 1u : 0u);
}

/**
 * @brief Get inner VLAN tag stripping mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_VLANTagStripModeType
 */
LOCAL_INLINE ENET_MAC_VLANTagStripModeType ENET_HWA_MAC_GetInnerVLANTagStripMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_EIVLS_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_EIVLS_SHIFT;
    return (ENET_MAC_VLANTagStripModeType)u32TmpVal;
}

/**
 * @brief Set inner VLAN tag stripping mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eMode Inner VLAN tag stripping mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInnerVLANTagStripMode(ENET_Type *const pEnet, ENET_MAC_VLANTagStripModeType eMode)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_EIVLS_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_EIVLS(eMode);
}

/**
 * @brief Get inner VLAN tag comparison enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Inner VLAN tag comparison is enabled
 * @return false Inner VLAN tag comparison is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetInnerVLANTagCmpEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ERIVLT_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_ERIVLT_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set inner VLAN tag comparison enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInnerVLANTagCmpEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_ERIVLT_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_ERIVLT(bEnable ? 1u : 0u);
}

/**
 * @brief Get double VLAN processing enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Double VLAN processing is enabled
 * @return false Double VLAN processing is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetDoubleVLANProcessEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_EDVLP_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_EDVLP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set double VLAN processing enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetDoubleVLANProcessEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_EDVLP_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_EDVLP(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag hash table match enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true VLAN tag hash table match is enabled
 * @return false VLAN tag hash table match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetVLANTagHashTableMatchEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_VTHM_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_VTHM_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN tag hash table match enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagHashTableMatchEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_VTHM_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_VTHM(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag in rx status enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true VLAN tag in rx status is enabled
 * @return false VLAN tag in rx status is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxStatusVLANTagEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_EVLRXS_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_EVLRXS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN tag in rx status enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxStatusVLANTagEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_EVLRXS_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_EVLRXS(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag stripping mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_VLANTagStripModeType
 */
LOCAL_INLINE ENET_MAC_VLANTagStripModeType ENET_HWA_MAC_GetVLANTagStripMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_EVLS_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_EVLS_SHIFT;
    return (ENET_MAC_VLANTagStripModeType)u32TmpVal;
}

/**
 * @brief Set VLAN tag stripping mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eMode VLAN tag stripping mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagStripMode(ENET_Type *const pEnet, ENET_MAC_VLANTagStripModeType eMode)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_EVLS_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_EVLS(eMode);
}

/**
 * @brief Get VLAN type check disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true VLAN type check is disabled
 * @return false VLAN type check is enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetVLANTypeCheckDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_DOVLTC_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_DOVLTC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN type check disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTypeCheckDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_DOVLTC_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_DOVLTC(bDisable ? 1u : 0u);
}

/**
 * @brief Get Receive S-VLAN match enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Receive S-VLAN match is enabled
 * @return false Receive S-VLAN match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxSVLANMatchEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ERSVLM_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_ERSVLM_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set Receive S-VLAN match enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxSVLANMatchEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_ERSVLM_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_ERSVLM(bEnable ? 1u : 0u);
}

/**
 * @brief Get S-VLAN enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true S-VLAN is enabled
 * @return false S-VLAN is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetSVLANEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ESVL_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_ESVL_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set S-VLAN enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSVLANEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_ESVL_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_ESVL(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag inverse match enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true VLAN tag inverse match is enabled
 * @return false VLAN tag inverse match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetVLANInverseMatchEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_VTIM_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_VTIM_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN tag inverse match enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANInverseMatchEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_VTIM_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_VTIM(bEnable ? 1u : 0u);
}

/**
 * @brief Get 12-Bit VLAN tag comparison enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true 12-Bit VLAN tag comparison is enabled
 * @return false 12-Bit VLAN tag comparison is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_Get12BitVLANTagEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ETV_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_ETV_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set 12-Bit VLAN tag comparison enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_Set12BitVLANTagEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_ETV_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_ETV(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag filter register address offset
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return VLAN tag filter register address offset
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetVLANTagFilterRegOffset(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OFS_MASK) >>
                         ENET_MAC_VLAN_TAG_CTRL_OFS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set VLAN tag filter register address offset
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u8Offset VLAN tag filter register address offset
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagFilterRegOffset(ENET_Type *const pEnet, uint8_t u8Offset)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_OFS_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_OFS(u8Offset);
}

/**
 * @brief Get VLAN tag filter register command type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_VLANCommandType
 */
LOCAL_INLINE ENET_MAC_VLANCommandType ENET_HWA_MAC_GetVLANCommandType(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_CT_MASK) >> ENET_MAC_VLAN_TAG_CTRL_CT_SHIFT;
    return (ENET_MAC_VLANCommandType)u32TmpVal;
}

/**
 * @brief Set VLAN tag filter register command type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eCommand Command type
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANCommandType(ENET_Type *const pEnet, ENET_MAC_VLANCommandType eCommand)
{
    pEnet->MAC_VLAN_TAG_CTRL = (pEnet->MAC_VLAN_TAG_CTRL & ~ENET_MAC_VLAN_TAG_CTRL_CT_MASK) |
                               ENET_MAC_VLAN_TAG_CTRL_CT(eCommand);
}

/**
 * @brief Get VLAN tag filter register operation status
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_StatusType
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetVLANOperationStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB_MASK) >> ENET_MAC_VLAN_TAG_CTRL_OB_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief Set VLAN tag filter register operation busy status
 *
 * @param [in] pEnet the base address of the Ethernet instance
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANOperationBusy(ENET_Type *const pEnet)
{
    pEnet->MAC_VLAN_TAG_CTRL |= ENET_MAC_VLAN_TAG_CTRL_OB_MASK;
}

/**
 * @brief Get VLAN tag data registers value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return VLAN tag data registers value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetVLANTagData(const ENET_Type *const pEnet)
{
    return pEnet->MAC_VLAN_TAG.MAC_VLAN_TAG_DATA;
}

/**
 * @brief Set VLAN tag data registers value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32VLANData Data value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagData(ENET_Type *const pEnet, uint32_t u32VLANData)
{
    pEnet->MAC_VLAN_TAG.MAC_VLAN_TAG_DATA = u32VLANData;
}

/**
 * @brief Get VLAN hash table registers value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return VLAN hash tTable registers value
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetVLANHashTable(const ENET_Type *const pEnet)
{
    return (uint16_t)(pEnet->MAC_VLAN_HASH_TABLE & ENET_MAC_VLAN_HASH_TABLE_VLHT_MASK);
}

/**
 * @brief Set VLAN hash table registers value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u16HashTable VLAN hash table registers value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANHashTable(ENET_Type *const pEnet, uint16_t u16HashTable)
{
    pEnet->MAC_VLAN_HASH_TABLE = ENET_MAC_VLAN_HASH_TABLE_VLHT(u16HashTable);
}

/**
 * @brief Get VLAN tag inclusion register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return VLAN tag inclusion registers value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetVLANInclusion(const ENET_Type *const pEnet)
{
    return pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA;
}

/**
 * @brief Set VLAN tag inclusion register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Inclusion VLAN tag inclusion register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANInclusion(ENET_Type *const pEnet, uint32_t u32Inclusion)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = u32Inclusion;
}

/**
 * @brief Get VLAN inclusion operation status
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_StatusType
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetVLANInclusionOperationStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_BUSY_MASK) >>
                         ENET_MAC_VLAN_INCL_BUSY_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief Set VLAN inclusion operation status
 *
 * @param [in] pEnet the base address of the Ethernet instance
 */
LOCAL_INLINE ENET_MAC_VLANInclCommandType ENET_HWA_MAC_GetVLANInclusionCommandType(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_RDWR_MASK) >>
                         ENET_MAC_VLAN_INCL_RDWR_SHIFT;
    return (ENET_MAC_VLANInclCommandType)u32TmpVal;
}

/**
 * @brief Set VLAN tag inclusion command
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eCommand VLAN tag inclusion command
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANInclusionCommandType(ENET_Type *const pEnet, ENET_MAC_VLANInclCommandType eCommand)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_RDWR_MASK) |
                                              ENET_MAC_VLAN_INCL_RDWR(eCommand);
}

/**
 * @brief Get VLAN inclusion address
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return VLAN inclusion address value
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetVLANInclusionAddr(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_ADDR_MASK) >>
                         ENET_MAC_VLAN_INCL_ADDR_SHIFT;
    return (uint8_t) u32TmpVal;
}

/**
 * @brief Set VLAN inclusion address
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u8Addr VLAN tag inclusion address value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANInclusionAddr(ENET_Type *const pEnet, uint8_t u8Addr)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_ADDR_MASK) |
                                              ENET_MAC_VLAN_INCL_ADDR(u8Addr);
}

/**
 * @brief Get channel based tag insertion enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Channel based tag insertion is enabled
 * @return false Channel based tag insertion is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetChannelBasedVLANTagInsertEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_CBTI_MASK) >>
                         ENET_MAC_VLAN_INCL_CBTI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set channel based tag insertion enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetChannelBasedVLANTagInsertEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_CBTI_MASK) |
                                              ENET_MAC_VLAN_INCL_CBTI(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag input enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true VLAN tag input is enabled
 * @return false VLAN tag input is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetVLANTagInputEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_VLTI_MASK) >>
                         ENET_MAC_VLAN_INCL_VLTI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN tag input enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagInputEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_VLTI_MASK) |
                                              ENET_MAC_VLAN_INCL_VLTI(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_VLANType
 */
LOCAL_INLINE ENET_MAC_VLANType ENET_HWA_MAC_GetVLANType(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_CSVL_MASK) >>
                         ENET_MAC_VLAN_INCL_CSVL_SHIFT;
    return (ENET_MAC_VLANType)u32TmpVal;
}

/**
 * @brief Set VLAN type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eType VLAN type
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANType(ENET_Type *const pEnet, ENET_MAC_VLANType eType)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_CSVL_MASK) |
                                              ENET_MAC_VLAN_INCL_CSVL(eType);
}

/**
 * @brief Get VLAN priority control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true VLAN priority control is enabled
 * @return false VLAN priority control is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetVLANPriorityCtrlEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_VLP_MASK) >>
                         ENET_MAC_VLAN_INCL_VLP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN tag input enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANPriorityCtrlEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_VLP_MASK) |
                                              ENET_MAC_VLAN_INCL_VLP(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag control mode in transmit packets
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_VLANTagCtrlType
 */
LOCAL_INLINE ENET_MAC_VLANTagCtrlType ENET_HWA_MAC_GetVLANTagCtrlOperation(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_VLC_MASK) >>
                         ENET_MAC_VLAN_INCL_VLC_SHIFT;
    return (ENET_MAC_VLANTagCtrlType)u32TmpVal;
}

/**
 * @brief Set VLAN tag control mode in transmit packets
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eCtrl VLAN tag control mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagCtrlOperation(ENET_Type *const pEnet, ENET_MAC_VLANTagCtrlType eCtrl)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_VLC_MASK) |
                                              ENET_MAC_VLAN_INCL_VLC(eCtrl);
}

/**
 * @brief Get Tx VLAN tag value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Tx VLAN tag value
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetTxVLANTag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ENET_MAC_VLAN_INCL_VLT_MASK) >>
                         ENET_MAC_VLAN_INCL_VLT_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set Tx VLAN tag value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u16VLANTag VLAN tag value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTxVLANTag(ENET_Type *const pEnet, uint16_t u16VLANTag)
{
    pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA = (pEnet->MAC_VLAN_INCL.MAC_VLAN_INCL_DATA & ~ENET_MAC_VLAN_INCL_VLT_MASK) |
                                              ENET_MAC_VLAN_INCL_VLT(u16VLANTag);
}

/**
 * @brief Get inner VLAN tag inclusion or replacement register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return The register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetInnerVLANInclusion(const ENET_Type *const pEnet)
{
    return pEnet->MAC_INNER_VLAN_INCL;
}

/**
 * @brief Set inner VLAN tag inclusion or replacement register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Inclusion Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInnerVLANInclusion(ENET_Type *const pEnet, uint32_t u32Inclusion)
{
    pEnet->MAC_INNER_VLAN_INCL = u32Inclusion;
}

/**
 * @brief Get inner VLAN tag input enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Inner VLAN tag input is enabled
 * @return false Inner VLAN tag input is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetInnerVLANTagInputEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INNER_VLAN_INCL & ENET_MAC_INNER_VLAN_INCL_VLTI_MASK) >>
                         ENET_MAC_INNER_VLAN_INCL_VLTI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set inner VLAN tag input enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInnerVLANTagInputEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_INNER_VLAN_INCL = (pEnet->MAC_INNER_VLAN_INCL & ~ENET_MAC_INNER_VLAN_INCL_VLTI_MASK) |
                                 ENET_MAC_INNER_VLAN_INCL_VLTI(bEnable ? 1u : 0u);
}

/**
 * @brief Get inner VLAN type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_VLANType
 */
LOCAL_INLINE ENET_MAC_VLANType ENET_HWA_MAC_GetInnerVLANType(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INNER_VLAN_INCL & ENET_MAC_INNER_VLAN_INCL_CSVL_MASK) >>
                         ENET_MAC_INNER_VLAN_INCL_CSVL_SHIFT;
    return (ENET_MAC_VLANType)u32TmpVal;
}

/**
 * @brief Set inner VLAN type
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eType Inner VLAN type
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInnerVLANType(ENET_Type *const pEnet, ENET_MAC_VLANType eType)
{
    pEnet->MAC_INNER_VLAN_INCL = (pEnet->MAC_INNER_VLAN_INCL & ~ENET_MAC_INNER_VLAN_INCL_CSVL_MASK) |
                                 ENET_MAC_INNER_VLAN_INCL_CSVL(eType);
}

/**
 * @brief Get inner VLAN priority control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Inner VLAN priority control is enabled
 * @return false Inner VLAN priority control is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetInnerVLANPriorityCtrlEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INNER_VLAN_INCL & ENET_MAC_INNER_VLAN_INCL_VLP_MASK) >>
                         ENET_MAC_INNER_VLAN_INCL_VLP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set inner VLAN priority control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInnerVLANPriorityCtrlEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_INNER_VLAN_INCL = (pEnet->MAC_INNER_VLAN_INCL & ~ENET_MAC_INNER_VLAN_INCL_VLP_MASK) |
                                 ENET_MAC_INNER_VLAN_INCL_VLP(bEnable ? 1u : 0u);
}

/**
 * @brief Get inner VLAN tag control mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_VLANTagCtrlType
 */
LOCAL_INLINE ENET_MAC_VLANTagCtrlType ENET_HWA_MAC_GetInnerVLANTagCtrl(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INNER_VLAN_INCL & ENET_MAC_INNER_VLAN_INCL_VLC_MASK) >>
                         ENET_MAC_INNER_VLAN_INCL_VLC_SHIFT;
    return (ENET_MAC_VLANTagCtrlType)u32TmpVal;
}

/**
 * @brief Set inner VLAN tag control mode
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eCtrl Inner VLAN tag control mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInnerVLANTagCtrl(ENET_Type *const pEnet, ENET_MAC_VLANTagCtrlType eCtrl)
{
    pEnet->MAC_INNER_VLAN_INCL = (pEnet->MAC_INNER_VLAN_INCL & ~ENET_MAC_INNER_VLAN_INCL_VLC_MASK) |
                                 ENET_MAC_INNER_VLAN_INCL_VLC(eCtrl);
}

/**
 * @brief Get inner VLAN tag value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Inner VLAN tag value
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetTxInnerVLANTag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INNER_VLAN_INCL & ENET_MAC_INNER_VLAN_INCL_VLT_MASK) >>
                         ENET_MAC_INNER_VLAN_INCL_VLT_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set inner VLAN tag value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u16VLANTag Inner VLAN tag value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTxInnerVLANTag(ENET_Type *const pEnet, uint16_t u16VLANTag)
{
    pEnet->MAC_INNER_VLAN_INCL = (pEnet->MAC_INNER_VLAN_INCL & ~ENET_MAC_INNER_VLAN_INCL_VLT_MASK) |
                                 ENET_MAC_INNER_VLAN_INCL_VLT(u16VLANTag);
}

/**
 * @brief Get Queue0 tx flow control register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return The register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetQueue0TxFlowCtrl(const ENET_Type *const pEnet)
{
    return pEnet->MAC_Q0_TX_FLOW_CTRL;
}

/**
 * @brief Set Queue0 tx flow control register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32FlowCtrl The register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetQueue0TxFlowCtrl(ENET_Type *const pEnet, uint32_t u32FlowCtrl)
{
    pEnet->MAC_Q0_TX_FLOW_CTRL = u32FlowCtrl;
}

/**
 * @brief Get Queue0 tx pause time value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Pause time value
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetQueue0TxPauseTime(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_Q0_TX_FLOW_CTRL & ENET_MAC_Q0_TX_FLOW_CTRL_PT_MASK) >>
                         ENET_MAC_Q0_TX_FLOW_CTRL_PT_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set Queue0 tx pause time value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u16PauseTime Pause time value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetQueue0TxPauseTime(ENET_Type *const pEnet, uint16_t u16PauseTime)
{
    pEnet->MAC_Q0_TX_FLOW_CTRL = (pEnet->MAC_Q0_TX_FLOW_CTRL &
                                  ~(ENET_MAC_Q0_TX_FLOW_CTRL_PT_MASK | ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA_MASK)) |
                                 ENET_MAC_Q0_TX_FLOW_CTRL_PT(u16PauseTime);
}

/**
 * @brief Get Queue0 tx zero quanta pause disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true Queue0 tx zero quanta pause is disabled
 * @return false is Queue0 tx zero quanta pause enabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetQueue0TxZeroQuantaPauseDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_Q0_TX_FLOW_CTRL & ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ_MASK) >>
                         ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set Queue0 tx zero quanta pause disable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bDisable Disable or enable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetQueue0TxZeroQuantaPauseDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MAC_Q0_TX_FLOW_CTRL = (pEnet->MAC_Q0_TX_FLOW_CTRL &
                                  ~(ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ_MASK | ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA_MASK)) |
                                 ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ(bDisable ? 1u : 0u);
}

/**
 * @brief Get Queue0 tx pause low threshold
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_PauseThresholdType
 */
LOCAL_INLINE ENET_MAC_PauseThresholdType ENET_HWA_MAC_GetQueue0TxPauseLowThreshold(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_Q0_TX_FLOW_CTRL & ENET_MAC_Q0_TX_FLOW_CTRL_PLT_MASK) >>
                         ENET_MAC_Q0_TX_FLOW_CTRL_PLT_SHIFT;
    return (ENET_MAC_PauseThresholdType)u32TmpVal;
}

/**
 * @brief Set Queue0 tx pause low threshold
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] ePauseThreshold Threshold value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetQueue0TxPauseLowThreshold(ENET_Type *const pEnet, ENET_MAC_PauseThresholdType ePauseThreshold)
{
    pEnet->MAC_Q0_TX_FLOW_CTRL = (pEnet->MAC_Q0_TX_FLOW_CTRL &
                                  ~(ENET_MAC_Q0_TX_FLOW_CTRL_PLT_MASK | ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA_MASK)) |
                                 ENET_MAC_Q0_TX_FLOW_CTRL_PLT(ePauseThreshold);
}

/**
 * @brief Get queue0 tx flow control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @retval true Queue0 tx flow control is enabled
 * @retval false Queue0 tx flow control is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetQueue0TxFlowCtrlEnableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_Q0_TX_FLOW_CTRL & ENET_MAC_Q0_TX_FLOW_CTRL_TFE_MASK) >>
                         ENET_MAC_Q0_TX_FLOW_CTRL_TFE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set queue0 tx flow control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetQueue0TxFlowCtrlEnableFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_Q0_TX_FLOW_CTRL = (pEnet->MAC_Q0_TX_FLOW_CTRL &
                                  ~(ENET_MAC_Q0_TX_FLOW_CTRL_TFE_MASK | ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA_MASK)) |
                                 ENET_MAC_Q0_TX_FLOW_CTRL_TFE(bEnable ? 1u : 0u);
}

/**
 * @brief Get flow control busy or backpressure status
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_StatusType
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetFlowCtrlOrBackpressureStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_Q0_TX_FLOW_CTRL & ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA_MASK) >>
                         ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief Initiate flow control busy or backpressure
 *
 * @param [in] pEnet the base address of the Ethernet instance
 */
LOCAL_INLINE void ENET_HWA_MAC_InitiatePausePacketOrBackpressure(ENET_Type *const pEnet)
{
    pEnet->MAC_Q0_TX_FLOW_CTRL |= ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA_MASK;
}

/**
 * @brief Get receive flow control register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxFlowCtrl(const ENET_Type *const pEnet)
{
    return pEnet->MAC_RX_FLOW_CTRL;
}

/**
 * @brief Set receive flow control register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32FlowCtrl Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxFlowCtrl(ENET_Type *const pEnet, uint32_t u32FlowCtrl)
{
    pEnet->MAC_RX_FLOW_CTRL = u32FlowCtrl;
}

/**
 * @brief Get unicast pause packet detect enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @retval true Unicast pause packet detect is enabled
 * @retval false Unicast pause packet detect is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetUnicastPausePacketDetectEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_FLOW_CTRL & ENET_MAC_RX_FLOW_CTRL_UP_MASK) >> ENET_MAC_RX_FLOW_CTRL_UP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set unicast pause packet detect enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetUnicastPausePacketDetectEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_RX_FLOW_CTRL = (pEnet->MAC_RX_FLOW_CTRL & ~ENET_MAC_RX_FLOW_CTRL_UP_MASK) |
                              ENET_MAC_RX_FLOW_CTRL_UP(bEnable ? 1u : 0u);
}

/**
 * @brief Get receive flow control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @retval true Receive flow control is enabled
 * @retval false Receive flow control is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxFlowCtrlEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_FLOW_CTRL & ENET_MAC_RX_FLOW_CTRL_RFE_MASK) >> ENET_MAC_RX_FLOW_CTRL_RFE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive flow control enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable Enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxFlowCtrlEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_RX_FLOW_CTRL = (pEnet->MAC_RX_FLOW_CTRL & ~ENET_MAC_RX_FLOW_CTRL_RFE_MASK) |
                              ENET_MAC_RX_FLOW_CTRL_RFE(bEnable ? 1u : 0u);
}

/**
 * @brief Get Receive queue control 0 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxQueueCtrl0(const ENET_Type *const pEnet)
{
    return pEnet->MAC_RXQ_CTRL0;
}

/**
 * @brief Set Receive queue control 0 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Ctrl Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxQueueCtrl0(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->MAC_RXQ_CTRL0 = u32Ctrl;
}

/**
 * @brief Get Receive queue control 1 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxQueueCtrl1(const ENET_Type *const pEnet)
{
    return pEnet->MAC_RXQ_CTRL1;
}

/**
 * @brief Set Receive queue control 1 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Ctrl Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxQueueCtrl1(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->MAC_RXQ_CTRL1 = u32Ctrl;
}

/**
 * @brief Get Receive queue control 2 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxQueueCtrl2(const ENET_Type *const pEnet)
{
    return pEnet->MAC_RXQ_CTRL2;
}

/**
 * @brief Set Receive queue control 2 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Ctrl Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxQueueCtrl2(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->MAC_RXQ_CTRL2 = u32Ctrl;
}

/**
 * @brief Get Receive queue control 4 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return Register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxQueueCtrl4(const ENET_Type *const pEnet)
{
    return pEnet->MAC_RXQ_CTRL4;
}

/**
 * @brief Set Receive queue control 4 register value
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] u32Ctrl Register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxQueueCtrl4(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->MAC_RXQ_CTRL4 = u32Ctrl;
}

/**
 * @brief Get Receive queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue the queue number
 * @return ENET_MTL_QueueEnableType
 */
LOCAL_INLINE ENET_MTL_QueueEnableType ENET_HWA_MTL_GetRxQueueEnStatus(const ENET_Type *const pEnet,
                                                                      ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL0 &
                          ((uint32_t)ENET_MAC_RXQ_CTRL0_RXQ0EN_MASK <<
                           (ENET_MAC_RXQ_CTRL0_RXQ0EN_SHIFT +
                            (ENET_MAC_RXQ_CTRL0_RXQ1EN_SHIFT - ENET_MAC_RXQ_CTRL0_RXQ0EN_SHIFT) * (uint32_t)eQueue))) >>
                         (ENET_MAC_RXQ_CTRL0_RXQ0EN_SHIFT +
                          (ENET_MAC_RXQ_CTRL0_RXQ1EN_SHIFT - ENET_MAC_RXQ_CTRL0_RXQ0EN_SHIFT) * (uint32_t)eQueue);
    return (ENET_MTL_QueueEnableType)u32TmpVal;
}

/**
 * @brief Set Receive queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue the queue number
 * @param [in] eEnable receive queue enable mode
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxQueueEnStatus(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                  ENET_MTL_QueueEnableType eEnable)
{
    pEnet->MAC_RXQ_CTRL0 = (pEnet->MAC_RXQ_CTRL0 &
                            ~((uint32_t)ENET_MAC_RXQ_CTRL0_RXQ0EN_MASK <<
                              (ENET_MAC_RXQ_CTRL0_RXQ0EN_SHIFT +
                               (ENET_MAC_RXQ_CTRL0_RXQ1EN_SHIFT - ENET_MAC_RXQ_CTRL0_RXQ0EN_SHIFT) * (uint32_t)eQueue))) |
                           (ENET_MAC_RXQ_CTRL0_RXQ0EN(eEnable) <<
                            ((ENET_MAC_RXQ_CTRL0_RXQ1EN_SHIFT - ENET_MAC_RXQ_CTRL0_RXQ0EN_SHIFT) * (uint32_t)eQueue));
}

/**
 * @brief Get tagged PTP over ethernet packets queuing control
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MAC_PTPoEQueueCtrlType
 */
LOCAL_INLINE ENET_MAC_PTPoEQueueCtrlType ENET_HWA_MAC_GetTaggedPTPoEQueueCtrl(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL1 & ENET_MAC_RXQ_CTRL1_TPQC_MASK) >> ENET_MAC_RXQ_CTRL1_TPQC_SHIFT;
    return (ENET_MAC_PTPoEQueueCtrlType)u32TmpVal;
}

/**
 * @brief Set tagged PTP over ethernet packets queuing control
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eCtrl the control mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTaggedPTPoEQueueCtrl(ENET_Type *const pEnet, ENET_MAC_PTPoEQueueCtrlType eCtrl)
{
    pEnet->MAC_RXQ_CTRL1 = (pEnet->MAC_RXQ_CTRL1 & ~ENET_MAC_RXQ_CTRL1_TPQC_MASK) |
                           ENET_MAC_RXQ_CTRL1_TPQC(eCtrl);
}

/**
 * @brief Get tagged AV control packets queuing enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true tagged AV control packets queue is enabled
 * @return false tagged AV control packets queue is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTaggedAVCtrlPacketQueueEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL1 & ENET_MAC_RXQ_CTRL1_TACPQE_MASK) >> ENET_MAC_RXQ_CTRL1_TACPQE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set tagged AV control packets queuing enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTaggedAVCtrlPacketQueueEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_RXQ_CTRL1 = (pEnet->MAC_RXQ_CTRL1 & ~ENET_MAC_RXQ_CTRL1_TACPQE_MASK) |
                           ENET_MAC_RXQ_CTRL1_TACPQE(bEnable ? 1u : 0u);
}

/**
 * @brief Get multicast and broadcast queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true multicast and broadcast queue is enabled
 * @return false multicast and broadcast queue is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMulticastAndBroadcastQueueEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL1 & ENET_MAC_RXQ_CTRL1_MCBCQEN_MASK) >> ENET_MAC_RXQ_CTRL1_MCBCQEN_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set multicast and broadcast queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMulticastAndBroadcastQueueEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_RXQ_CTRL1 = (pEnet->MAC_RXQ_CTRL1 & ~ENET_MAC_RXQ_CTRL1_MCBCQEN_MASK) |
                           ENET_MAC_RXQ_CTRL1_MCBCQEN(bEnable ? 1u : 0u);
}

/**
 * @brief Get multicast and broadcast queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MTL_QueueType
 */
LOCAL_INLINE ENET_MTL_QueueType ENET_HWA_MAC_GetMulticastAndBroadcastQueue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL1 & ENET_MAC_RXQ_CTRL1_MCBCQ_MASK) >> ENET_MAC_RXQ_CTRL1_MCBCQ_SHIFT;
    return (ENET_MTL_QueueType)u32TmpVal;
}

/**
 * @brief Set multicast and broadcast queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue the queue id
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMulticastAndBroadcastQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MAC_RXQ_CTRL1 = (pEnet->MAC_RXQ_CTRL1 & ~ENET_MAC_RXQ_CTRL1_MCBCQ_MASK) |
                           ENET_MAC_RXQ_CTRL1_MCBCQ(eQueue);
}

/**
 * @brief Get untagged packet queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MTL_QueueType
 */
LOCAL_INLINE ENET_MTL_QueueType ENET_HWA_MAC_GetUntaggedPacketQueue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL1 & ENET_MAC_RXQ_CTRL1_UPQ_MASK) >> ENET_MAC_RXQ_CTRL1_UPQ_SHIFT;
    return (ENET_MTL_QueueType)u32TmpVal;
}

/**
 * @brief Set untagged packet queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue the queue id
 */
LOCAL_INLINE void ENET_HWA_MAC_SetUntaggedPacketQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MAC_RXQ_CTRL1 = (pEnet->MAC_RXQ_CTRL1 & ~ENET_MAC_RXQ_CTRL1_UPQ_MASK) |
                           ENET_MAC_RXQ_CTRL1_UPQ(eQueue);
}

/**
 * @brief Get PTP over ethernet packet queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MTL_QueueType
 */
LOCAL_INLINE ENET_MTL_QueueType ENET_HWA_MAC_GetPTPoEQueue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL1 & ENET_MAC_RXQ_CTRL1_PTPQ_MASK) >> ENET_MAC_RXQ_CTRL1_PTPQ_SHIFT;
    return (ENET_MTL_QueueType)u32TmpVal;
}

/**
 * @brief Set PTP over ethernet packet queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue the queue id
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPTPoEQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MAC_RXQ_CTRL1 = (pEnet->MAC_RXQ_CTRL1 & ~ENET_MAC_RXQ_CTRL1_PTPQ_MASK) |
                           ENET_MAC_RXQ_CTRL1_PTPQ(eQueue);
}

/**
 * @brief Get AV untagged control packets queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MTL_QueueType
 */
LOCAL_INLINE ENET_MTL_QueueType ENET_HWA_MAC_GetAVCtrlPacketQueue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL1 & ENET_MAC_RXQ_CTRL1_AVCPQ_MASK) >> ENET_MAC_RXQ_CTRL1_AVCPQ_SHIFT;
    return (ENET_MTL_QueueType)u32TmpVal;
}

/**
 * @brief Set AV untagged control packets queue id
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue the queue id
 */
LOCAL_INLINE void ENET_HWA_MAC_SetAVCtrlPacketQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MAC_RXQ_CTRL1 = (pEnet->MAC_RXQ_CTRL1 & ~ENET_MAC_RXQ_CTRL1_AVCPQ_MASK) |
                           ENET_MAC_RXQ_CTRL1_AVCPQ(eQueue);
}

/**
 * @brief Get receive queue priorities
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue queue id
 * @return eQueue priorities value
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetRxQueueSelectedPriorities(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL2 &
                          ((uint32_t)ENET_MAC_RXQ_CTRL2_PSRQ0_MASK <<
                           (ENET_MAC_RXQ_CTRL2_PSRQ0_SHIFT +
                            (ENET_MAC_RXQ_CTRL2_PSRQ1_SHIFT - ENET_MAC_RXQ_CTRL2_PSRQ0_SHIFT) * (uint32_t)eQueue))) >>
                         (ENET_MAC_RXQ_CTRL2_PSRQ0_SHIFT +
                          (ENET_MAC_RXQ_CTRL2_PSRQ1_SHIFT - ENET_MAC_RXQ_CTRL2_PSRQ0_SHIFT) * (uint32_t)eQueue);
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set receive queue priorities
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue queue id
 * @param [in] u8SelPrio priorities value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxQueueSelectedPriorities(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                            uint8_t u8SelPrio)
{
    pEnet->MAC_RXQ_CTRL2 = (pEnet->MAC_RXQ_CTRL2 &
                            ~(ENET_MAC_RXQ_CTRL2_PSRQ0_MASK <<
                              (ENET_MAC_RXQ_CTRL2_PSRQ0_SHIFT +
                               (ENET_MAC_RXQ_CTRL2_PSRQ1_SHIFT - ENET_MAC_RXQ_CTRL2_PSRQ0_SHIFT) * (uint32_t)eQueue))) |
                           (ENET_MAC_RXQ_CTRL2_PSRQ0(u8SelPrio) <<
                            ((ENET_MAC_RXQ_CTRL2_PSRQ1_SHIFT - ENET_MAC_RXQ_CTRL2_PSRQ0_SHIFT) * (uint32_t)eQueue)) ;
}

/**
 * @brief Get VLAN tag filter fail packets queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true VLAN tag filter fail packets queue is enabled
 * @return false VLAN tag filter fail packets queue is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetVLANTagFilterFailPacketQueueEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL4 & ENET_MAC_RXQ_CTRL4_VFFQE_MASK) >> ENET_MAC_RXQ_CTRL4_VFFQE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set VLAN tag filter fail packets queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagFilterFailPacketQueueEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_RXQ_CTRL4 = (pEnet->MAC_RXQ_CTRL4 & ~ENET_MAC_RXQ_CTRL4_VFFQE_MASK) |
                           ENET_MAC_RXQ_CTRL4_VFFQE(bEnable ? 1u : 0u);
}

/**
 * @brief Get VLAN tag filter fail packets queue
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MTL_QueueType
 */
LOCAL_INLINE ENET_MTL_QueueType ENET_HWA_MAC_GetVLANTagFilterFailPacketQueue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL4 & ENET_MAC_RXQ_CTRL4_VFFQ_MASK) >> ENET_MAC_RXQ_CTRL4_VFFQ_SHIFT;
    return (ENET_MTL_QueueType)u32TmpVal;
}

/**
 * @brief Set VLAN tag filter fail packets queue
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue queue id
 */
LOCAL_INLINE void ENET_HWA_MAC_SetVLANTagFilterFailPacketQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MAC_RXQ_CTRL4 = (pEnet->MAC_RXQ_CTRL4 & ~ENET_MAC_RXQ_CTRL4_VFFQ_MASK) |
                           ENET_MAC_RXQ_CTRL4_VFFQ(eQueue);
}

/**
 * @brief Get multicast address filter fail packets queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true multicast address filter fail packets queue is enabled
 * @return false multicast address filter fail packets queue is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMulticastAddrFilterFailPacketQueueEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL4 & ENET_MAC_RXQ_CTRL4_MFFQE_MASK) >> ENET_MAC_RXQ_CTRL4_MFFQE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set multicast address filter fail packets queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMulticastAddrFilterFailPacketQueueEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_RXQ_CTRL4 = (pEnet->MAC_RXQ_CTRL4 & ~ENET_MAC_RXQ_CTRL4_MFFQE_MASK) |
                           ENET_MAC_RXQ_CTRL4_MFFQE(bEnable ? 1u : 0u);
}

/**
 * @brief Get multicast address filter fail packets queue
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MTL_QueueType
 */
LOCAL_INLINE ENET_MTL_QueueType ENET_HWA_MAC_GetMulticastAddrFilterFailPacketQueue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL4 & ENET_MAC_RXQ_CTRL4_MFFQ_MASK) >> ENET_MAC_RXQ_CTRL4_MFFQ_SHIFT;
    return (ENET_MTL_QueueType)u32TmpVal;
}

/**
 * @brief Set multicast address filter fail packets queue
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue queue id
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMulticastAddrFilterFailPacketQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MAC_RXQ_CTRL4 = (pEnet->MAC_RXQ_CTRL4 & ~ENET_MAC_RXQ_CTRL4_MFFQ_MASK) |
                           ENET_MAC_RXQ_CTRL4_MFFQ(eQueue);
}

/**
 * @brief Get unicast address filter fail packets queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return true unicast address filter fail packets queue is enabled
 * @return false unicast address filter fail packets queue is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetUnicastAddrFilterFailPacketQueueEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL4 & ENET_MAC_RXQ_CTRL4_UFFQE_MASK) >> ENET_MAC_RXQ_CTRL4_UFFQE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set unicast address filter fail packets queue enable flag
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetUnicastAddrFilterFailPacketQueueEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_RXQ_CTRL4 = (pEnet->MAC_RXQ_CTRL4 & ~ENET_MAC_RXQ_CTRL4_UFFQE_MASK) |
                           ENET_MAC_RXQ_CTRL4_UFFQE(bEnable ? 1u : 0u);
}

/**
 * @brief Get unicast address filter fail packets queue
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @return ENET_MTL_QueueType
 */
LOCAL_INLINE ENET_MTL_QueueType ENET_HWA_MAC_GetUnicastAddrFilterFailPacketQueue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RXQ_CTRL4 & ENET_MAC_RXQ_CTRL4_UFFQ_MASK) >> ENET_MAC_RXQ_CTRL4_UFFQ_SHIFT;
    return (ENET_MTL_QueueType)u32TmpVal;
}

/**
 * @brief Set unicast address filter fail packets queue
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eQueue queue id
 */
LOCAL_INLINE void ENET_HWA_MAC_SetUnicastAddrFilterFailPacketQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MAC_RXQ_CTRL4 = (pEnet->MAC_RXQ_CTRL4 & ~ENET_MAC_RXQ_CTRL4_UFFQ_MASK) |
                           ENET_MAC_RXQ_CTRL4_UFFQ(eQueue);
}

/**
 * @brief Get the interrupt status of ENET MAC
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t the interrupt status
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetInterruptStatus(const ENET_Type *const pEnet)
{
    return pEnet->MAC_INTERRUPT_STATUS;
}

/**
 * @brief Clear the interrupt flags of MAC
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Interrupt the interrupt events to be cleared
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearInterruptStatus(ENET_Type *const pEnet, uint32_t u32Interrupt)
{
    pEnet->MAC_INTERRUPT_STATUS = u32Interrupt;
}

/**
 * @brief Get the MDIO interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true the MDIO operation is complete
 * @return false there is no MDIO operation completion event
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMDIOInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_MDIOIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_MDIOIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the MDIO interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearMDIOInterruptStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_INTERRUPT_STATUS |= ENET_MAC_INTERRUPT_STATUS_MDIOIS_MASK;
}

/**
 * @brief Get the receive interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return bool indicate the status of received packets
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_RXSTSIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_RXSTSIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the transmit interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return bool indicate the status of transmit packets
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_TXSTSIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_TXSTSIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the timestamp interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return bool indicate the status of timestamp interrupt
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTimestampInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_TSIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_TSIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the MMC transmit interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 * @note This field is valid only when you enable MAC Management Counters(MMC)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return bool indicate the status of MMC transmit
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMMCTxInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_MMCTXIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_MMCTXIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the MMC receive interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 * @note This field is valid only when you enable MAC Management Counters(MMC)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return bool indicate the status of MMC receive
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMMCRxInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_MMCRXIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_MMCRXIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the MMC interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 * @note This field is valid only when you enable MAC Management Counters(MMC)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return bool indicate the status of MMC interrupt
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMMCInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_MMCIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_MMCIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the PHY interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return bool indicate whether the PHY interrupt is detected
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPhyInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_STATUS & ENET_MAC_INTERRUPT_STATUS_PHYIS_MASK) >>
                         ENET_MAC_INTERRUPT_STATUS_PHYIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the PHY interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearPhyInterruptStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_INTERRUPT_STATUS |= ENET_MAC_INTERRUPT_STATUS_MDIOIS_MASK;
}

/**
 * @brief Get the MAC interrupts enable register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC interrupts enable register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetInterruptEnable(const ENET_Type *const pEnet)
{
    return pEnet->MAC_INTERRUPT_ENABLE;
}

/**
 * @brief Set the MAC interrupts enable register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32IntEnable interrupts enable value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetInterruptEnable(ENET_Type *const pEnet, uint32_t u32IntEnable)
{
    pEnet->MAC_INTERRUPT_ENABLE = u32IntEnable;
}

/**
 * @brief Get MDIO interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MDIO interrupt is enabled
 * @return false MDIO interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMDIOInterruptEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_ENABLE & ENET_MAC_INTERRUPT_ENABLE_MDIOIE_MASK) >>
                         ENET_MAC_INTERRUPT_ENABLE_MDIOIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MDIO interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMDIOInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_INTERRUPT_ENABLE = (pEnet->MAC_INTERRUPT_ENABLE & ~ENET_MAC_INTERRUPT_ENABLE_MDIOIE_MASK) |
                                  ENET_MAC_INTERRUPT_ENABLE_MDIOIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get receive status interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true receive status interrupt is enabled
 * @return false receive status interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxStatusInterruptEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_ENABLE & ENET_MAC_INTERRUPT_ENABLE_RXSTSIE_MASK) >>
                         ENET_MAC_INTERRUPT_ENABLE_RXSTSIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive status interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetRxStatusInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_INTERRUPT_ENABLE = (pEnet->MAC_INTERRUPT_ENABLE & ~ENET_MAC_INTERRUPT_ENABLE_RXSTSIE_MASK) |
                                  ENET_MAC_INTERRUPT_ENABLE_RXSTSIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get transmit status interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true transmit status interrupt is enabled
 * @return false transmit status interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxStatusInterruptEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_ENABLE & ENET_MAC_INTERRUPT_ENABLE_TXSTSIE_MASK) >>
                         ENET_MAC_INTERRUPT_ENABLE_TXSTSIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set transmit status interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTxStatusInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_INTERRUPT_ENABLE = (pEnet->MAC_INTERRUPT_ENABLE & ~ENET_MAC_INTERRUPT_ENABLE_TXSTSIE_MASK) |
                                  ENET_MAC_INTERRUPT_ENABLE_TXSTSIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get timestamp interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true timestamp interrupt is enabled
 * @return false timestamp interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTimestampInterruptEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_ENABLE & ENET_MAC_INTERRUPT_ENABLE_TSIE_MASK) >>
                         ENET_MAC_INTERRUPT_ENABLE_TSIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set timestamp interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_INTERRUPT_ENABLE = (pEnet->MAC_INTERRUPT_ENABLE & ~ENET_MAC_INTERRUPT_ENABLE_TSIE_MASK) |
                                  ENET_MAC_INTERRUPT_ENABLE_TSIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get phy interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true phy interrupt is enabled
 * @return false phy interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPhyInterruptEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_INTERRUPT_ENABLE & ENET_MAC_INTERRUPT_ENABLE_PHYIE_MASK) >>
                         ENET_MAC_INTERRUPT_ENABLE_PHYIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set phy interrupt enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPhyInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_INTERRUPT_ENABLE = (pEnet->MAC_INTERRUPT_ENABLE & ~ENET_MAC_INTERRUPT_ENABLE_PHYIE_MASK) |
                                  ENET_MAC_INTERRUPT_ENABLE_PHYIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get the MAC receive and transmit status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t the MAC receive and transmit status
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxTxStatus(const ENET_Type *const pEnet)
{
    return pEnet->MAC_RX_TX_STATUS;
}

/**
 * @brief Clear the MAC receive and transmit status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Status the status flags to be cleared
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearRxTxStatus(ENET_Type *const pEnet, uint32_t u32Status)
{
    pEnet->MAC_RX_TX_STATUS = u32Status;
}

/**
 * @brief Get the receive watchdog timeout status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true receive watchdog timeout
 * @return false no receive watchdog timeout
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxWDGTimeoutStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_TX_STATUS & ENET_MAC_RX_TX_STATUS_RWT_MASK) >> ENET_MAC_RX_TX_STATUS_RWT_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the receive watchdog timeout status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearRxWDGTimeoutStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_RX_TX_STATUS |= ENET_MAC_RX_TX_STATUS_RWT_MASK;
}

/**
 * @brief Get the excessive collision status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true excessive collision is sensed
 * @return false no collision
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxExcessiveCollisionStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_TX_STATUS & ENET_MAC_RX_TX_STATUS_EXCOL_MASK) >> ENET_MAC_RX_TX_STATUS_EXCOL_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the excessive collision status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTxExcessiveCollisionStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_RX_TX_STATUS |= ENET_MAC_RX_TX_STATUS_EXCOL_MASK;
}

/**
 * @brief Get the late collision status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true late collision is sensed
 * @return false no collision
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxLateCollisionStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_TX_STATUS & ENET_MAC_RX_TX_STATUS_LCOL_MASK) >> ENET_MAC_RX_TX_STATUS_LCOL_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the late collision status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTxLateCollisionStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_RX_TX_STATUS |= ENET_MAC_RX_TX_STATUS_LCOL_MASK;
}

/**
 * @brief Get the excessive deferral status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true excessive deferral is sensed
 * @return false no excessive deferral
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxExcessiveDeferralStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_TX_STATUS & ENET_MAC_RX_TX_STATUS_EXDEF_MASK) >> ENET_MAC_RX_TX_STATUS_EXDEF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the excessive deferral status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearExcessiveDeferralStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_RX_TX_STATUS |= ENET_MAC_RX_TX_STATUS_EXDEF_MASK;
}

/**
 * @brief Indicates the status of carrier signal
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true loss of carrier
 * @return false carrier is present
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxLossOfCarrierStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_TX_STATUS & ENET_MAC_RX_TX_STATUS_LCARR_MASK) >> ENET_MAC_RX_TX_STATUS_LCARR_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the loss of carrier status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearLossOfCarrierStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_RX_TX_STATUS |= ENET_MAC_RX_TX_STATUS_LCARR_MASK;
}

/**
 * @brief Indicates whether the carrier signal is present from the PHY at the end of preamble transmission
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true carrier is absent
 * @return false carrier is present
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxNoCarrierStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_TX_STATUS & ENET_MAC_RX_TX_STATUS_NCARR_MASK) >> ENET_MAC_RX_TX_STATUS_NCARR_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the no carrier status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTxNoCarrierStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_RX_TX_STATUS |= ENET_MAC_RX_TX_STATUS_NCARR_MASK;
}

/**
 * @brief Indicates whether a transmit jabber timer timeout occurred
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true transmit jabber timeout occured
 * @return false no transmit jabber timeout occured
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxJabberTimeoutStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_RX_TX_STATUS & ENET_MAC_RX_TX_STATUS_TJT_MASK) >> ENET_MAC_RX_TX_STATUS_TJT_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the transmit jabber timer timeout status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTxJabberTimeoutStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_RX_TX_STATUS |= ENET_MAC_RX_TX_STATUS_TJT_MASK;
}

/**
 * @brief Get MAC version
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC version number
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMACVersion(const ENET_Type *const pEnet)
{
    return pEnet->MAC_VERSION;
}

/**
 * @brief Get MAC debug status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC debug status
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetDebugStatus(const ENET_Type *const pEnet)
{
    return pEnet->MAC_DEBUG;
}

/**
 * @brief Get MAC transmit packet controller status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_TxPacketControllerStatusType
 */
LOCAL_INLINE ENET_MAC_TxPacketControllerStatusType ENET_HWA_MAC_GetTxPacketControllerStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_DEBUG & ENET_MAC_DEBUG_TFCSTS_MASK) >> ENET_MAC_DEBUG_TFCSTS_SHIFT;
    return (ENET_MAC_TxPacketControllerStatusType)u32TmpVal;
}

/**
 * @brief Get MAC GMII or MII transmit protocol engine status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true transmit protocol engine is active
 * @return false transmit protocol engine is inactive
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxPacketEngineStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_DEBUG & ENET_MAC_DEBUG_TPESTS_MASK) >> ENET_MAC_DEBUG_TPESTS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get MAC receive packet controller FIFO status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true receive packet controller FIFO is active
 * @return false receive packet controller FIFO is inactive
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxPacketControllerFIFOStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_DEBUG & ENET_MAC_DEBUG_RFCFCSTS_MASK) >> ENET_MAC_DEBUG_RFCFCSTS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get MAC GMII or MII receive protocol engine status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true receive protocol engine is active
 * @return false receive protocol engine is inactive
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetRxProtocalEngineStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_DEBUG & ENET_MAC_DEBUG_RPESTS_MASK) >> ENET_MAC_DEBUG_RPESTS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get MAC hardware features 0
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC hardware features 0
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetHwFeature0(const ENET_Type *const pEnet)
{
    return pEnet->MAC_HW_FEATURE0;
}

/**
 * @brief Get phy interface mii mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_MiiModeType
 */
LOCAL_INLINE ENET_MAC_MiiModeType ENET_HWA_MAC_GetPhyMiiMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_HW_FEATURE0 & ENET_MAC_HW_FEATURE0_ACTPHYSEL_MASK) >>
                         ENET_MAC_HW_FEATURE0_ACTPHYSEL_SHIFT;
    return (ENET_MAC_MiiModeType)u32TmpVal;
}

/**
 * @brief Get MAC hardware features 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC hardware features 1
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetHwFeature1(const ENET_Type *const pEnet)
{
    return pEnet->MAC_HW_FEATURE1;
}

/**
 * @brief Get MAC hardware features 2
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC hardware features 2
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetHwFeature2(const ENET_Type *const pEnet)
{
    return pEnet->MAC_HW_FEATURE2;
}

/**
 * @brief Get MAC hardware features 3
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC hardware features 3
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetHwFeature3(const ENET_Type *const pEnet)
{
    return pEnet->MAC_HW_FEATURE3;
}

/**
 * @brief Get MAC MDIO address register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MDIO address register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMDIOAddress(const ENET_Type *const pEnet)
{
    return pEnet->MAC_MDIO_ADDRESS;
}

/**
 * @brief Set MAC MDIO address register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32MDIOAddr MDIO address register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMDIOAddress(ENET_Type *const pEnet, uint32_t u32MDIOAddr)
{
    pEnet->MAC_MDIO_ADDRESS = u32MDIOAddr;
}

/**
 * @brief Get preamble suppression enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MDIO preamble suppression is enabled
 * @return false MDIO preamble suppression is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPreambleSuppressionEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_PSE_MASK) >> ENET_MAC_MDIO_ADDRESS_PSE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MDIO preamble suppression enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPreambleSuppressionEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_PSE_MASK) |
                              ENET_MAC_MDIO_ADDRESS_PSE(bEnable ? 1u : 0u);
}

/**
 * @brief Get MDIO back to back transactions enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MDIO back to back transactions is enabled
 * @return false MDIO back to back transactions is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetBackToBackTransactionEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_BTB_MASK) >> ENET_MAC_MDIO_ADDRESS_BTB_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MDIO back to back transactions enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetBackToBackTransactionEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_BTB_MASK) |
                              ENET_MAC_MDIO_ADDRESS_BTB(bEnable ? 1u : 0u);
}

/**
 * @brief Get MDIO physical layer address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return phy address
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetPhysicalLayerAddr(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_PA_MASK) >> ENET_MAC_MDIO_ADDRESS_PA_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MDIO physical layer address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Addr phy address
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPhysicalLayerAddr(ENET_Type *const pEnet, uint8_t u8Addr)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_PA_MASK) |
                              ENET_MAC_MDIO_ADDRESS_PA(u8Addr);
}

/**
 * @brief Get MDIO phy register(clause22) or MMD device(clause 45)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return phy register or device address
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetPhyRegisterOrDeviceAddr(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_RDA_MASK) >> ENET_MAC_MDIO_ADDRESS_RDA_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MDIO phy register(clause22) or MMD device(clause 45)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Addr phy register or device address
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPhyRegisterOrDeviceAddr(ENET_Type *const pEnet, uint8_t u8Addr)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_RDA_MASK) |
                              ENET_MAC_MDIO_ADDRESS_RDA(u8Addr);
}

/**
 * @brief Get the number of trailing clock cycles
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return trailing clock cycles
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetTrailingClockCnt(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_NTC_MASK) >> ENET_MAC_MDIO_ADDRESS_NTC_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MDIO trailing clock cycles
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Cnt trailing clock cycles(range 0~7)
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTrailingClockCnt(ENET_Type *const pEnet, uint8_t u8Cnt)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_NTC_MASK) |
                              ENET_MAC_MDIO_ADDRESS_NTC(u8Cnt);
}

/**
 * @brief Get the MDC clock range
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_CSRClockRangeType
 */
LOCAL_INLINE ENET_MAC_CSRClockRangeType ENET_HWA_MAC_GetCSRClockRange(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_CR_MASK) >> ENET_MAC_MDIO_ADDRESS_CR_SHIFT;
    return (ENET_MAC_CSRClockRangeType)u32TmpVal;
}

/**
 * @brief Set the MDC clock range
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eRange values defined in ENET_MAC_CSRClockRangeType
 */
LOCAL_INLINE void ENET_HWA_MAC_SetCSRClockRange(ENET_Type *const pEnet, ENET_MAC_CSRClockRangeType eRange)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_CR_MASK) |
                              ENET_MAC_MDIO_ADDRESS_CR(eRange);
}

/**
 * @brief Get skip address packet enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true skip address packet is enabled
 * @return false skip address packet is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetSkipAddrPacketEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_SKAP_MASK) >> ENET_MAC_MDIO_ADDRESS_SKAP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set skip address packet enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSkipAddrPacketEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_SKAP_MASK) |
                              ENET_MAC_MDIO_ADDRESS_SKAP(bEnable ? 1u : 0u);
}

/**
 * @brief Get phy operation command
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return Commands defined in ENET_MAC_PhyOperationCmdType
 */
LOCAL_INLINE ENET_MAC_PhyOperationCmdType ENET_HWA_MAC_GetPhyOperationCommand(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & (ENET_MAC_MDIO_ADDRESS_GOC_0_MASK |
                                                     ENET_MAC_MDIO_ADDRESS_GOC_1_MASK)) >>
                         ENET_MAC_MDIO_ADDRESS_GOC_0_SHIFT;
    return (ENET_MAC_PhyOperationCmdType)u32TmpVal;
}

/**
 * @brief Set phy operation command
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eCmd Commands defined in ENET_MAC_PhyOperationCmdType
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPhyOperationCommand(ENET_Type *const pEnet, ENET_MAC_PhyOperationCmdType eCmd)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~(ENET_MAC_MDIO_ADDRESS_GOC_0_MASK |
                                                           ENET_MAC_MDIO_ADDRESS_GOC_1_MASK)) |
                              ENET_MAC_MDIO_ADDRESS_GOC_0((uint32_t)eCmd & 0x01u) |
                              ENET_MAC_MDIO_ADDRESS_GOC_1(((uint32_t)eCmd & 0x02u) >> 1u);
}

/**
 * @brief Get MDIO clause version
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_PHY_CLAUSE_22 access phy use clause 22 mode
   @return ENET_MAC_PHY_CLAUSE_45 access phy use clause 45 mode
 */
LOCAL_INLINE ENET_MAC_PhyClauseVersionType ENET_HWA_MAC_GetPhyClauseVersion(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_C45E_MASK) >> ENET_MAC_MDIO_ADDRESS_C45E_SHIFT;
    return (ENET_MAC_PhyClauseVersionType)u32TmpVal;
}

/**
 * @brief Set MDIO clause version
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eVersion ENET_MAC_PHY_CLAUSE_22 or ENET_MAC_PHY_CLAUSE_45
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPhyClauseVersion(ENET_Type *const pEnet, ENET_MAC_PhyClauseVersionType eVersion)
{
    pEnet->MAC_MDIO_ADDRESS = (pEnet->MAC_MDIO_ADDRESS & ~ENET_MAC_MDIO_ADDRESS_C45E_MASK) |
                              ENET_MAC_MDIO_ADDRESS_C45E(eVersion);
}

/**
 * @brief Get MDIO busy status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_STATUS_IDLE GMII status is idle
   @return ENET_MAC_STATUS_BUSY GMII status is busy,
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetGMIIStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_GB_MASK) >> ENET_MAC_MDIO_ADDRESS_GB_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief Set MDIO busy to initiate a read or write access
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_SetGMIIBusy(ENET_Type *const pEnet)
{
    pEnet->MAC_MDIO_ADDRESS |= ENET_MAC_MDIO_ADDRESS_GB_MASK;
}

/**
 * @brief Get MDIO data register value
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMDIOData(const ENET_Type *const pEnet)
{
    return pEnet->MAC_MDIO_DATA;
}

/**
 * @brief Set MDIO data register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Data data register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMDIOData(ENET_Type *const pEnet, uint32_t u32Data)
{
    pEnet->MAC_MDIO_DATA = u32Data;
}

/**
 * @brief Get phy register address
 * @note This field is valid only in clause 45 mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return phy register address
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetPhyRegisterAddr(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_DATA & ENET_MAC_MDIO_DATA_RA_MASK) >> ENET_MAC_MDIO_DATA_RA_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set phy register address
 * @note This field is valid only in clause 45 mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u16Addr phy register address
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPhyRegisterAddr(ENET_Type *const pEnet, uint16_t u16Addr)
{
    pEnet->MAC_MDIO_DATA = (pEnet->MAC_MDIO_DATA & ~ENET_MAC_MDIO_DATA_RA_MASK) | ENET_MAC_MDIO_DATA_RA(u16Addr);
}

/**
 * @brief Get MDIO data
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return data value
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetGMIIData(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_MDIO_DATA & ENET_MAC_MDIO_DATA_GD_MASK) >> ENET_MAC_MDIO_DATA_GD_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set MDIO data
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u16Data MDIO data
 */
LOCAL_INLINE void ENET_HWA_MAC_SetGMIIData(ENET_Type *const pEnet, uint16_t u16Data)
{
    pEnet->MAC_MDIO_DATA = (pEnet->MAC_MDIO_DATA & ~ENET_MAC_MDIO_DATA_GD_MASK) | ENET_MAC_MDIO_DATA_GD(u16Data);
}

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief Enable TX frame preemption
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable 1U enable or 0U disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetFramePreemptionEnFlag(ENET_Type *const pEnet, uint8 bEnable)
{
    pEnet->MAC_FPE_CTRL_STS = (pEnet->MAC_FPE_CTRL_STS & ~ENET_MAC_FPE_CTRL_STS_EFPE_MASK) |
                              ENET_MAC_FPE_CTRL_STS_EFPE(bEnable);
}
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief Get presentation time in ns
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return presentation time
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPresentationTime(const ENET_Type *const pEnet)
{
    return pEnet->MAC_PRESN_TIME_NS;
}

/**
 * @brief Get presentation time update
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return update time value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPresentationTimeUpdata(const ENET_Type *const pEnet)
{
    return pEnet->MAC_PRESN_TIME_UPDT;
}

/**
 * @brief Set presentation time update
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32NanoSeconds update time value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPresentationTimeUpdata(ENET_Type *const pEnet, uint32_t u32NanoSeconds)
{
    pEnet->MAC_PRESN_TIME_UPDT = u32NanoSeconds;
}

/**
 * @brief Get MAC address0 high register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address0 high register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMacAddr0High(const ENET_Type *const pEnet)
{
    return pEnet->MAC_ADDRESS0_HIGH;
}

/**
 * @brief Set MAC address0 high register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32AddrHigh MAC address0 high register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetAddr0High(ENET_Type *const pEnet, uint32_t u32AddrHigh)
{
    pEnet->MAC_ADDRESS0_HIGH = u32AddrHigh;
}

/**
 * @brief Get MAC address0 low register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address0 low register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMacAddr0Low(const ENET_Type *const pEnet)
{
    return pEnet->MAC_ADDRESS0_LOW;
}

/**
 * @brief Set MAC address0 low register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32AddrLow MAC address0 low register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr0Low(ENET_Type *const pEnet, uint32_t u32AddrLow)
{
    pEnet->MAC_ADDRESS0_LOW = u32AddrLow;
}

/**
 * @brief Get MAC address0 enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MAC address0 is enabled
 * @return false MAC address0 is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMacAddr0EnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS0_HIGH & ENET_MAC_ADDRESS0_HIGH_AE_MASK) >> ENET_MAC_ADDRESS0_HIGH_AE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get MAC address0 DMA channel select
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address0 DMA channel select
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetMacAddr0DMAChannelSelect(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS0_HIGH & ENET_MAC_ADDRESS0_HIGH_DCS_MASK) >> ENET_MAC_ADDRESS0_HIGH_DCS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MAC address0 DMA channel select
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8DMAChannelSel MAC address0 DMA channel select
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr0DMAChannelSelect(ENET_Type *const pEnet, uint8_t u8DMAChannelSel)
{
    pEnet->MAC_ADDRESS0_HIGH = (pEnet->MAC_ADDRESS0_HIGH & ~ENET_MAC_ADDRESS0_HIGH_DCS_MASK) |
                               ENET_MAC_ADDRESS0_HIGH_DCS(u8DMAChannelSel);
}

/**
 * @brief Get MAC address1 high register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address1 high register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMacAddr1High(const ENET_Type *const pEnet)
{
    return pEnet->MAC_ADDRESS1_HIGH;
}

/**
 * @brief Set MAC address1 high register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32AddrHigh MAC address1 high register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetAddr1High(ENET_Type *const pEnet, uint32_t u32AddrHigh)
{
    pEnet->MAC_ADDRESS1_HIGH = u32AddrHigh;
}

/**
 * @brief Get MAC address1 low register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address1 low register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMacAddr1Low(const ENET_Type *const pEnet)
{
    return pEnet->MAC_ADDRESS1_LOW;
}

/**
 * @brief Set MAC address1 low register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32AddrLow MAC address1 low register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr1Low(ENET_Type *const pEnet, uint32_t u32AddrLow)
{
    pEnet->MAC_ADDRESS1_LOW = u32AddrLow;
}

/**
 * @brief Get MAC address1 enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MAC address1 is enabled
 * @return false MAC address1 is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMacAddr1EnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS1_HIGH & ENET_MAC_ADDRESS1_HIGH_AE_MASK) >> ENET_MAC_ADDRESS1_HIGH_AE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MAC address1 enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr1EnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_ADDRESS1_HIGH = (pEnet->MAC_ADDRESS1_HIGH & ~ENET_MAC_ADDRESS1_HIGH_AE_MASK) |
                               ENET_MAC_ADDRESS1_HIGH_AE(bEnable ? 1u : 0u);
}

/**
 * @brief Get MAC address1 compare mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_ADDR_TYPE_DEST MAC Address1 is used to compare with the DA fields
 * @return ENET_MAC_ADDR_TYPE_SRC MAC Address1 is used to compare with the SA fields
 */
LOCAL_INLINE ENET_MAC_AddrType ENET_HWA_MAC_GetMacAddr1Type(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS1_HIGH & ENET_MAC_ADDRESS1_HIGH_SA_MASK) >> ENET_MAC_ADDRESS1_HIGH_SA_SHIFT;
    return (ENET_MAC_AddrType)u32TmpVal;
}

/**
 * @brief Set MAC address1 compare mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eAddrType ENET_MAC_ADDR_TYPE_DEST or ENET_MAC_ADDR_TYPE_SRC
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr1Type(ENET_Type *const pEnet, ENET_MAC_AddrType eAddrType)
{
    pEnet->MAC_ADDRESS1_HIGH = (pEnet->MAC_ADDRESS1_HIGH & ~ENET_MAC_ADDRESS1_HIGH_SA_MASK) |
                               ENET_MAC_ADDRESS1_HIGH_SA(eAddrType);
}

/**
 * @brief Get MAC address1 mask byte control
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address1 mask byte value
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetMacAddr1MaskByteCtrl(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS1_HIGH & ENET_MAC_ADDRESS1_HIGH_MBC_MASK) >> ENET_MAC_ADDRESS1_HIGH_MBC_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MAC address1 mask byte control
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8MaskCtrl MAC address1 mask byte value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr1MaskByteCtrl(ENET_Type *const pEnet, uint8_t u8MaskCtrl)
{
    pEnet->MAC_ADDRESS1_HIGH = (pEnet->MAC_ADDRESS1_HIGH & ~ENET_MAC_ADDRESS1_HIGH_MBC_MASK) |
                               ENET_MAC_ADDRESS1_HIGH_MBC(u8MaskCtrl);
}

/**
 * @brief Get MAC address1 DMA channel select
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address1 DMA channel select
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetMacAddr1DMAChannelSelect(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS1_HIGH & ENET_MAC_ADDRESS1_HIGH_DCS_MASK) >> ENET_MAC_ADDRESS1_HIGH_DCS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MAC address1 DMA channel select
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8DMAChannelSel MAC address1 DMA channel select
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr1DMAChannelSelect(ENET_Type *const pEnet, uint8_t u8DMAChannelSel)
{
    pEnet->MAC_ADDRESS1_HIGH = (pEnet->MAC_ADDRESS1_HIGH & ~ENET_MAC_ADDRESS1_HIGH_DCS_MASK) |
                               ENET_MAC_ADDRESS1_HIGH_DCS(u8DMAChannelSel);
}

/**
 * @brief Get MAC address2 high register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address2 high register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMacAddr2High(const ENET_Type *const pEnet)
{
    return pEnet->MAC_ADDRESS2_HIGH;
}

/**
 * @brief Set MAC address2 high register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32AddrHigh MAC address2 high register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetAddr2High(ENET_Type *const pEnet, uint32_t u32AddrHigh)
{
    pEnet->MAC_ADDRESS2_HIGH = u32AddrHigh;
}

/**
 * @brief Get MAC address2 low register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address2 low register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMacAddr2Low(const ENET_Type *const pEnet)
{
    return pEnet->MAC_ADDRESS2_LOW;
}

/**
 * @brief Set MAC address2 low register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32AddrLow MAC address2 low register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr2Low(ENET_Type *const pEnet, uint32_t u32AddrLow)
{
    pEnet->MAC_ADDRESS2_LOW = u32AddrLow;
}

/**
 * @brief Get MAC address2 enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MAC address2 is enabled
 * @return false MAC address2 is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMacAddr2EnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS2_HIGH & ENET_MAC_ADDRESS2_HIGH_AE_MASK) >> ENET_MAC_ADDRESS2_HIGH_AE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MAC address2 enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr2EnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_ADDRESS2_HIGH = (pEnet->MAC_ADDRESS2_HIGH & ~ENET_MAC_ADDRESS2_HIGH_AE_MASK) |
                               ENET_MAC_ADDRESS2_HIGH_AE(bEnable ? 1u : 0u);
}

/**
 * @brief Get MAC address2 compare mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_ADDR_TYPE_DEST MAC Address2 is used to compare with the DA fields
 * @return ENET_MAC_ADDR_TYPE_SRC MAC Address2 is used to compare with the SA fields
 */
LOCAL_INLINE ENET_MAC_AddrType ENET_HWA_MAC_GetMacAddr2Type(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS2_HIGH & ENET_MAC_ADDRESS2_HIGH_SA_MASK) >> ENET_MAC_ADDRESS2_HIGH_SA_SHIFT;
    return (ENET_MAC_AddrType)u32TmpVal;
}

/**
 * @brief Set MAC address2 compare mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eAddrType ENET_MAC_ADDR_TYPE_DEST or ENET_MAC_ADDR_TYPE_SRC
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr2Type(ENET_Type *const pEnet, ENET_MAC_AddrType eAddrType)
{
    pEnet->MAC_ADDRESS2_HIGH = (pEnet->MAC_ADDRESS2_HIGH & ~ENET_MAC_ADDRESS2_HIGH_SA_MASK) |
                               ENET_MAC_ADDRESS2_HIGH_SA(eAddrType);
}

/**
 * @brief Get MAC address2 mask byte control
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address2 mask byte value
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetMacAddr2MaskByteCtrl(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS2_HIGH & ENET_MAC_ADDRESS2_HIGH_MBC_MASK) >> ENET_MAC_ADDRESS2_HIGH_MBC_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MAC address2 mask byte control
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8MaskCtrl MAC address2 mask byte value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr2MaskByteCtrl(ENET_Type *const pEnet, uint8_t u8MaskCtrl)
{
    pEnet->MAC_ADDRESS2_HIGH = (pEnet->MAC_ADDRESS2_HIGH & ~ENET_MAC_ADDRESS2_HIGH_MBC_MASK) |
                               ENET_MAC_ADDRESS2_HIGH_MBC(u8MaskCtrl);
}

/**
 * @brief Get MAC address2 DMA channel select
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MAC address2 DMA channel select
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetMacAddr2DMAChannelSelect(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_ADDRESS2_HIGH & ENET_MAC_ADDRESS2_HIGH_DCS_MASK) >> ENET_MAC_ADDRESS2_HIGH_DCS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MAC address2 DMA channel select
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8DMAChannelSel MAC address2 DMA channel select
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMacAddr2DMAChannelSelect(ENET_Type *const pEnet, uint8_t u8DMAChannelSel)
{
    pEnet->MAC_ADDRESS2_HIGH = (pEnet->MAC_ADDRESS2_HIGH & ~ENET_MAC_ADDRESS2_HIGH_DCS_MASK) |
                               ENET_MAC_ADDRESS2_HIGH_DCS(u8DMAChannelSel);
}

/* ================================================================ *
 *                 ENET MAC Management Counters (MMC)               *
 * ================================================================ */

/**
 * @brief Get MMC control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC control register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMmcControl(const ENET_Type *const pEnet)
{
    return pEnet->MMC_CONTROL;
}

/**
 * @brief Set MMC control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Ctrl MMC control register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMmcControl(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->MMC_CONTROL = u32Ctrl;
}

/**
 * @brief Get update MMC counters for dropped broadcast packets enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true update MMC counters for dropped broadcast packets
 * @return false do not update MMC counters for dropped broadcast packets
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetUpdateMmcCntForDroppedBroadcastPktEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MMC_CONTROL & ENET_MMC_CONTROL_UCDBC_MASK) >> ENET_MMC_CONTROL_UCDBC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set update MMC counters for dropped broadcast packets enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetUpdateMmcCntForDroppedBroadcastPktEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MMC_CONTROL = (pEnet->MMC_CONTROL & ~ENET_MMC_CONTROL_UCDBC_MASK) |
                         ENET_MMC_CONTROL_UCDBC(bEnable ? 1u : 0u);
}

/**
 * @brief Get MMC counters full-half preset level
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_MMC_COUNTER_PRESET_LEVEL_FULL MMC counter preset to almost-full value
 * @return ENET_MAC_MMC_COUNTER_PRESET_LEVEL_HALF MMC counter preset to almost-half value
 */
LOCAL_INLINE ENET_MAC_MmcCntPresetLevelType ENET_HWA_MAC_GetMmcCounterPresetLevel(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MMC_CONTROL & ENET_MMC_CONTROL_CNTPRSTLVL_MASK) >> ENET_MMC_CONTROL_CNTPRSTLVL_SHIFT;
    return (ENET_MAC_MmcCntPresetLevelType)u32TmpVal;
}

/**
 * @brief Set MMC counters full-half preset level
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eLevel ENET_MAC_MMC_COUNTER_PRESET_LEVEL_FULL or ENET_MAC_MMC_COUNTER_PRESET_LEVEL_HALF
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMmcCounterPresetLevel(ENET_Type *const pEnet, ENET_MAC_MmcCntPresetLevelType eLevel)
{
    pEnet->MMC_CONTROL = (pEnet->MMC_CONTROL & ~ENET_MMC_CONTROL_CNTPRSTLVL_MASK) |
                         ENET_MMC_CONTROL_CNTPRSTLVL(eLevel);
}

/**
 * @brief Get MMC counters preset status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MMC counter preset is enabled
 * @return false MMC counter preset is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMmcCounterPresetStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MMC_CONTROL & ENET_MMC_CONTROL_CNTPRST_MASK) >> ENET_MMC_CONTROL_CNTPRST_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MMC counters preset
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_PresetMmcCounters(ENET_Type *const pEnet)
{
    pEnet->MMC_CONTROL |= ENET_MMC_CONTROL_CNTPRST_MASK;
}

/**
 * @brief Get MMC counters freeze status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MMC counter freeze is enabled
 * @return false MMC counter freeze is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMmcCounterFreezeStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MMC_CONTROL & ENET_MMC_CONTROL_CNTFREEZ_MASK) >> ENET_MMC_CONTROL_CNTFREEZ_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MMC counters freeze
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bFreeze enable or disable freeze
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMmcCounterFreezeStatus(ENET_Type *const pEnet, bool bFreeze)
{
    pEnet->MMC_CONTROL = (pEnet->MMC_CONTROL & ~ENET_MMC_CONTROL_CNTFREEZ_MASK) |
                         ENET_MMC_CONTROL_CNTFREEZ(bFreeze ? 1u : 0u);
}

/**
 * @brief Get MMC counters reset on read enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MMC counters are reset to zero after read
 * @return false MMC counters are not reset to zero after read
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMmcCounterResetOnReadEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MMC_CONTROL & ENET_MMC_CONTROL_RSTONRD_MASK) >> ENET_MMC_CONTROL_RSTONRD_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MMC counters reset on read enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMmcCounterResetOnReadEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MMC_CONTROL = (pEnet->MMC_CONTROL & ~ENET_MMC_CONTROL_RSTONRD_MASK) |
                         ENET_MMC_CONTROL_RSTONRD(bEnable ? 1u : 0u);
}

/**
 * @brief Get MMC counters stop rollover enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MMC counters does not roll over to zero after reaching the maximum value
 * @return false MMC counters roll over to zero after reaching the maximum value
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMmcCounterStopRolloverEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MMC_CONTROL & ENET_MMC_CONTROL_CNTSTOPRO_MASK) >> ENET_MMC_CONTROL_CNTSTOPRO_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MMC counters stop rollover enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMmcCounterStopRolloverEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MMC_CONTROL = (pEnet->MMC_CONTROL & ~ENET_MMC_CONTROL_CNTSTOPRO_MASK) |
                         ENET_MMC_CONTROL_CNTSTOPRO(bEnable ? 1u : 0u);
}

/**
 * @brief Get MMC counters reset status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true All MMC counters are reset
 * @return false MMC counters are not reset
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMmcCounterResetStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MMC_CONTROL & ENET_MMC_CONTROL_CNTRST_MASK) >> ENET_MMC_CONTROL_CNTRST_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Reset all MMC counters
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ResetMmcCounters(ENET_Type *const pEnet)
{
    pEnet->MMC_CONTROL |= ENET_MMC_CONTROL_CNTRST_MASK;
}

/**
 * @brief Get MMC interrupts of receive statistics counters
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC interrupts status
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMmcRxInterruptStatus(const ENET_Type *const pEnet)
{
    return pEnet->MMC_RX_INTERRUPT;
}

/**
 * @brief Get MMC interrupts of transmit statistics counters
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC interrupts status
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMmcTxInterruptStatus(const ENET_Type *const pEnet)
{
    return pEnet->MMC_TX_INTERRUPT;
}

/**
 * @brief Get MMC interrupts mask of receive statistics counters
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC interrupts mask
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMmcRxInterruptMask(const ENET_Type *const pEnet)
{
    return pEnet->MMC_RX_INTERRUPT_MASK;
}

/**
 * @brief Set MMC interrupts mask of receive statistics counters
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Mask MMC interrupts mask value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMmcRxInterruptMask(ENET_Type *const pEnet, uint32_t u32Mask)
{
    pEnet->MMC_RX_INTERRUPT_MASK = u32Mask;
}

/**
 * @brief Get MMC interrupts mask of transmit statistics counters
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC interrupts mask
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetMmcTxInterruptMask(const ENET_Type *const pEnet)
{
    return pEnet->MMC_TX_INTERRUPT_MASK;
}

/**
 * @brief Set MMC interrupts mask of transmit statistics counters
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Mask MMC interrupts mask value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMmcTxInterruptMask(ENET_Type *const pEnet, uint32_t u32Mask)
{
    pEnet->MMC_TX_INTERRUPT_MASK = u32Mask;
}

/**
 * @brief Get transmitted bytes of good and bad packets
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxOctetCntGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_OCTET_COUNT_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_PACKET_COUNT_GOOD_BAD;
}

/**
 * @brief Get the number of good broadcast packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxBroadcastPacketGood(const ENET_Type *const pEnet)
{
    return pEnet->TX_BROADCAST_PACKETS_GOOD;
}

/**
 * @brief Get the number of good multicast packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxMulticastPacketGood(const ENET_Type *const pEnet)
{
    return pEnet->TX_MULTICAST_PACKETS_GOOD;
}

/**
 * @brief Get the number of good and bad packets transmitted with length 64 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTx64OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_64OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad packets transmitted with length between 65 and 127 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTx65To127OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_65TO127OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad packets transmitted with length between 128 and 255 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTx128To255OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_128TO255OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad packets transmitted with length between 256 and 511 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTx256To511OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_256TO511OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad packets transmitted with length between 512 and 1023 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTx512To1023OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_512TO1023OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad packets transmitted with length 1024 to maxsize bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTx1024ToMaxOctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad unicast packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxUnicastPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_UNICAST_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad multicast packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxMulticastPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_MULTICAST_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good and bad broadcast packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxBroadcastPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->TX_BROADCAST_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of packets with transmit underflow error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxUnderflowErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_UNDERFLOW_ERROR_PACKETS;
}

/**
 * @brief Get the number of successfully transmitted packets after a single collision in half-duplex mode.
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxSingleCollisionGoodPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_SINGLE_COLLISION_GOOD_PACKETS;
}

/**
 * @brief Get the number of successfully transmitted packets after a multiple collision in half-duplex mode.
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxMultipleCollisionGoodPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_MULTIPLE_COLLISION_GOOD_PACKETS;
}

/**
 * @brief Get the number of successfully transmitted packets after a deferral in half-duplex mode.
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxDeferredPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_DEFERRED_PACKETS;
}

/**
 * @brief Get the number of packets with transmit late collision error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxLateCollisionPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_LATE_COLLISION_PACKETS;
}

/**
 * @brief Get the number of packets with transmit excessive collision errors
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxExcessiveCollisionPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_EXCESSIVE_COLLISION_PACKETS;
}

/**
 * @brief Get the number of packets with transmit carrier sense error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxCarrierErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_CARRIER_ERROR_PACKETS;
}

/**
 * @brief Get the number of bytes of good packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxOctetCntGood(const ENET_Type *const pEnet)
{
    return pEnet->TX_OCTET_COUNT_GOOD;
}

/**
 * @brief Get the number of good packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxPacketCntGood(const ENET_Type *const pEnet)
{
    return pEnet->TX_PACKET_COUNT_GOOD;
}

/**
 * @brief Get the number of packets with transmit excessive deferral error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxExcessiveDeferralErrorCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_EXCESSIVE_DEFERRAL_ERROR;
}

/**
 * @brief Get the number of good pause packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxPausePacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->TX_PAUSE_PACKETS;
}

/**
 * @brief Get the number of good VLAN packets transmitted
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxVLANPacketGood(const ENET_Type *const pEnet)
{
    return pEnet->TX_VLAN_PACKETS_GOOD;
}

/**
 * @brief Get the number of transmitted packets without errors and with length greater than the maxsize
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxOverSizePacketGood(const ENET_Type *const pEnet)
{
    return pEnet->TX_OSIZE_PACKETS_GOOD;
}

/**
 * @brief Get the number of good and bad packets received
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxPacketCntGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_PACKETS_COUNT_GOOD_BAD;
}

/**
 * @brief Get the number of bytes received in good and bad packets
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxOctetCntGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_OCTET_COUNT_GOOD_BAD;
}

/**
 * @brief Get the number of bytes received in good packets
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxOctetCntGood(const ENET_Type *const pEnet)
{
    return pEnet->RX_OCTET_COUNT_GOOD;
}

/**
 * @brief Get the number of good broadcast packets received
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxBroadcastPacketGood(const ENET_Type *const pEnet)
{
    return pEnet->RX_BROADCAST_PACKETS_GOOD;
}

/**
 * @brief Get the number of good multicast packets received
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxMulticastPacketGood(const ENET_Type *const pEnet)
{
    return pEnet->RX_MULTICAST_PACKETS_GOOD;
}

/**
 * @brief Get the number of packets received with CRC error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxCRCErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_CRC_ERROR_PACKETS;
}

/**
 * @brief Get the number of packets received with alignment error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxAlignmentErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_ALIGNMENT_ERROR_PACKETS;
}

/**
 * @brief Get the number of packets received with runt error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxRuntErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_RUNT_ERROR_PACKETS;
}

/**
 * @brief Get the number of packets received with jabber error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxJabberErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_JABBER_ERROR_PACKETS;
}

/**
 * @brief Get the number of packets received with length less than 64 bytes, without any errors
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxUndersizePacketGood(const ENET_Type *const pEnet)
{
    return pEnet->RX_UNDERSIZE_PACKETS_GOOD;
}

/**
 * @brief Get the number of packets received withouterrors and with length greater than maxsize
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxOverSizeGood(const ENET_Type *const pEnet)
{
    return pEnet->RX_OVERSIZE_PACKETS_GOOD;
}

/**
 * @brief Get the number of packets received with length 64 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRx64OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_64OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of packets received with length 65 to 127 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRx65To127OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_65TO127OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of packets received with length 128 to 255 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRx128To255OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_128TO255OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of packets received with length 256 to 511 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRx256To511OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_256TO511OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of packets received with length 512 to 1023 bytes
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRx512To1023OctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_512TO1023OCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of packets received with length 1024 to maxsize
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRx1024ToMaxOctetPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of good unicast packets received
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetUnicastPacketGood(const ENET_Type *const pEnet)
{
    return pEnet->RX_UNICAST_PACKETS_GOOD;
}

/**
 * @brief Get the number of packets received with length error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxLengthErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_LENGTH_ERROR_PACKETS;
}

/**
 * @brief Get the number of packets received with length greater than 1500 but less than 1536
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxOutOfRangeTypePacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_OUT_OF_RANGE_TYPE_PACKETS;
}

/**
 * @brief Get the number of good and valid pause packets received
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxPausePacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_PAUSE_PACKETS;
}

/**
 * @brief Get the number of missed received packets because of FIFO overflow
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxFIFOOverflowPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_FIFO_OVERFLOW_PACKETS;
}

/**
 * @brief Get the number of good and bad VLAN packets received
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxVLANPacketGoodBad(const ENET_Type *const pEnet)
{
    return pEnet->RX_VLAN_PACKETS_GOOD_BAD;
}

/**
 * @brief Get the number of packets received with error because of watchdog timeout error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxWatchdogErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_WATCHDOG_ERROR_PACKETS;
}

/**
 * @brief Get the number of packets received with receive error or Packet Extension error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxReceiveErrorPacketCnt(const ENET_Type *const pEnet)
{
    return pEnet->RX_RECEIVE_ERROR_PACKETS;
}

/**
 * @brief Get the number of good control packets received
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return MMC counter value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetRxControlPacketGood(const ENET_Type *const pEnet)
{
    return pEnet->RX_CONTROL_PACKETS_GOOD;
}

/* ================================================================ *
 *                 ENET MAC Layer 3 and Layer 4 Filter              *
 * ================================================================ */

/**
 * @brief Get the layer 3 and layer 4 control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 3 and layer 4 control register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer3Layer4Ctrl(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL;
}

/**
 * @brief Set the layer 3 and layer 4 control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32Ctrl control value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Layer4Ctrl(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32Ctrl)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = u32Ctrl;
}

/**
 * @brief Get layer 3 and layer 4 control DMA channel select enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true DMA channel select is enabled
 * @return false DMA channel select is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer3Layer4DMASelectEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_DMCHEN0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_DMCHEN0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 3 and layer 4 control DMA channel select enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Layer4DMASelectEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_DMCHEN0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_DMCHEN0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 3 and layer 4 control DMA channel number
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return ENET_DMA_ChannelType
 */
LOCAL_INLINE ENET_DMA_ChannelType ENET_HWA_MAC_GetLayer3Layer4DMAChannel(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_DMCHN0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_DMCHN0_SHIFT;
    return (ENET_DMA_ChannelType)u32TmpVal;
}

/**
 * @brief Set layer 3 and layer 4 control DMA channel number
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] eChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Layer4DMAChannel(ENET_Type *const pEnet, uint8_t u8Index,
                                                         ENET_DMA_ChannelType eChannel)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_DMCHN0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_DMCHN0(eChannel);
}

/**
 * @brief Get layer 4 destination port inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 4 destination port inverse match is enabled
 * @return false layer 4 destination port inverse match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer4DestPortInvMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L4DPIM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L4DPIM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 4 destination port inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer4DestPortInvMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L4DPIM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L4DPIM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 4 destination port match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 4 destination port match is enabled
 * @return false layer 4 destination port match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer4DestPortMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L4DPM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L4DPM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 4 destination port match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer4DestPortMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L4DPM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L4DPM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 4 source port inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 4 source port inverse match is enabled
 * @return false layer 4 source port inverse match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer4SrcPortInvMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L4SPIM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L4SPIM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 4 source port inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer4SrcPortInvMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L4SPIM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L4SPIM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 4 source port match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 4 source port match is enabled
 * @return false layer 4 source port match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer4SrcPortMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L4SPM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L4SPM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 4 source port match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer4SrcPortMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L4SPM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L4SPM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 4 protocol type (UDP or TCP)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return ENET_MAC_Layer4ProtocolType
 */
LOCAL_INLINE ENET_MAC_Layer4ProtocolType ENET_HWA_MAC_GetLayer4ProtocalType(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L4PEN0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L4PEN0_SHIFT;
    return (ENET_MAC_Layer4ProtocolType)u32TmpVal;
}

/**
 * @brief Set layer 4 protocol type (UDP or TCP)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] eProtocol protocol type (UDP or TCP)
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer4ProtocalType(ENET_Type *const pEnet, uint8_t u8Index,
                                                     ENET_MAC_Layer4ProtocolType eProtocol)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L4PEN0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L4PEN0(eProtocol);
}

/**
 * @brief Get layer3 IPv4 destination address bits match
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return lower retval bits are masked
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetLayer3IPv4DestAddrBitsMatch(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L3HDBM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L3HDBM0_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set layer3 IPv4 destination address bits match
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u8MaskBits lower u8MaskBits bits are masked
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3IPv4DestAddrBitsMatch(ENET_Type *const pEnet, uint8_t u8Index, uint8_t u8MaskBits)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L3HDBM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L3HDBM0(u8MaskBits);
}

/**
 * @brief Get layer3 IPv4 source address bits match
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return lower retval bits are masked
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetLayer3IPv4SrcAddrBitsMatch(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L3HSBM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L3HSBM0_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set layer3 IPv4 source address bits match
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u8MaskBits lower u8MaskBits bits are masked
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3IPv4SrcAddrBitsMatch(ENET_Type *const pEnet, uint8_t u8Index, uint8_t u8MaskBits)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L3HSBM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L3HSBM0(u8MaskBits);
}

/**
 * @brief Get layer3 IPv6 address bits match
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return lower retval bits are masked
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetLayer3IPv6AddrBitsMatch(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                          (ENET_MAC_L3_L4_CONTROL0_L3HDBM0_MASK | ENET_MAC_L3_L4_CONTROL0_L3HSBM0_MASK)) >>
                         ENET_MAC_L3_L4_CONTROL0_L3HSBM0_SHIFT;
    return (uint8_t)(u32TmpVal & 0x7Fu);
}

/**
 * @brief Set layer3 IPv6 address bits match
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u8MaskBits lower u8MaskBits bits are masked
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3IPv6AddrBitsMatch(ENET_Type *const pEnet, uint8_t u8Index, uint8_t u8MaskBits)
{
    uint8_t u8HighBits = (u8MaskBits & 0x60u) >> 5u;
    uint8_t u8LowBits = u8MaskBits & 0x1Fu;
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~(ENET_MAC_L3_L4_CONTROL0_L3HDBM0_MASK | ENET_MAC_L3_L4_CONTROL0_L3HSBM0_MASK)) |
                                                     (ENET_MAC_L3_L4_CONTROL0_L3HDBM0(u8HighBits) | ENET_MAC_L3_L4_CONTROL0_L3HSBM0(u8LowBits));
}

/**
 * @brief Get layer 3 destination address inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 3 destination address inverse match is enabled
 * @return false layer 3 destination address inverse match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer3DestAddrInvMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L3DAIM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L3DAIM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 3 destination address inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3DestAddrInvMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L3DAIM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L3DAIM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 3 destination address match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 3 destination address match is enabled
 * @return false layer 3 destination address match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer3DestAddrMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L3DAM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L3DAM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 3 destination address match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3DestAddrMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L3DAM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L3DAM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 3 source address inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 3 source address inverse match is enabled
 * @return false layer 3 source address inverse match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer3SrcAddrInvMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L3SAIM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L3SAIM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 3 source address inverse match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3SrcAddrInvMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L3SAIM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L3SAIM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 3 source address match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return true layer 3 source address match is enabled
 * @return false layer 3 source address match is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetLayer3SrcAddrMatchEnFlag(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L3SAM0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L3SAM0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set layer 3 source address match enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] bEnable enabled or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3SrcAddrMatchEnFlag(ENET_Type *const pEnet, uint8_t u8Index, bool bEnable)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L3SAM0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L3SAM0(bEnable ? 1u : 0u);
}

/**
 * @brief Get layer 3 protocol type (IPV4 or IPV6)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return ENET_MAC_Layer3ProtocolType (IPV4 or IPV6)
 */
LOCAL_INLINE ENET_MAC_Layer3ProtocolType ENET_HWA_MAC_GetLayer3ProtocolType(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL & ENET_MAC_L3_L4_CONTROL0_L3PEN0_MASK) >>
                         ENET_MAC_L3_L4_CONTROL0_L3PEN0_SHIFT;
    return (ENET_MAC_Layer3ProtocolType)u32TmpVal;
}

/**
 * @brief Set layer 3 protocol type (IPV4 or IPV6)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] eProtocol IPV4 or IPV6
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3ProtocolType(ENET_Type *const pEnet, uint8_t u8Index,
                                                     ENET_MAC_Layer3ProtocolType eProtocol)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL = (pEnet->L3_L4_FILTER[u8Index].MAC_L3_L4_CONTROL &
                                                      ~ENET_MAC_L3_L4_CONTROL0_L3PEN0_MASK) |
                                                     ENET_MAC_L3_L4_CONTROL0_L3PEN0(eProtocol);
}

/**
 * @brief Get layer 4 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 4 address value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer4Addr(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS;
}

/**
 * @brief Set layer 4 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32Addr layer 4 address value
 */
LOCAL_INLINE void ENET_MAC_SetLayer4Addr(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32Addr)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS = u32Addr;
}

/**
 * @brief Get layer 4 destination port number
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 4 destination port number
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetLayer4DestPort(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS & ENET_MAC_LAYER4_ADDRESS0_L4DP0_MASK) >>
                         ENET_MAC_LAYER4_ADDRESS0_L4DP0_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set layer 4 destination port number
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u16DestPort port number
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer4DestPort(ENET_Type *const pEnet, uint8_t u8Index, uint16_t u16DestPort)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS = (pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS &
                                                       ~ENET_MAC_LAYER4_ADDRESS0_L4DP0_MASK) |
                                                      ENET_MAC_LAYER4_ADDRESS0_L4DP0(u16DestPort);
}

/**
 * @brief Get layer 4 source port number
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 4 source port number
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetLayer4SrcPort(const ENET_Type *const pEnet, uint8_t u8Index)
{
    uint32_t u32TmpVal = (pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS & ENET_MAC_LAYER4_ADDRESS0_L4SP0_MASK) >>
                         ENET_MAC_LAYER4_ADDRESS0_L4SP0_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set layer 4 source port number
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u16SrcPort port number
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer4SrcPort(ENET_Type *const pEnet, uint8_t u8Index, uint16_t u16SrcPort)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS = (pEnet->L3_L4_FILTER[u8Index].MAC_LAYER4_ADDRESS &
                                                       ~ENET_MAC_LAYER4_ADDRESS0_L4SP0_MASK) |
                                                      ENET_MAC_LAYER4_ADDRESS0_L4SP0(u16SrcPort);
}

/**
 * @brief Get layer 3 address0
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 3 address0 value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer3Addr0(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR0_REG;
}

/**
 * @brief Set layer 3 address0
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32Addr layer 3 address0 value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Addr0(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32Addr)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR0_REG = u32Addr;
}

/**
 * @brief Get layer 3 address1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 3 address1 value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer3Addr1(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR1_REG;
}

/**
 * @brief Set layer 3 address1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32Addr layer 3 address1 value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Addr1(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32Addr)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR1_REG = u32Addr;
}

/**
 * @brief Get layer 3 address2
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 3 address2 value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer3Addr2(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR2_REG;
}

/**
 * @brief Set layer 3 address2
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32Addr layer 3 address2 value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Addr2(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32Addr)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR2_REG = u32Addr;
}

/**
 * @brief Get layer 3 address3
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 3 address3 value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer3Addr3(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR3_REG;
}

/**
 * @brief Set layer 3 address3
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32Addr layer 3 address3 value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3Addr3(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32Addr)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR3_REG = u32Addr;
}

/**
 * @brief Get layer 3 source IPv4 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 3 source IPv4 address value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer3SrcIPv4Addr(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR0_REG;
}

/**
 * @brief Set layer 3 source IPv4 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32SrcAddr layer 3 source IPv4 address value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3SrcIPv4Addr(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32SrcAddr)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR0_REG = u32SrcAddr;
}

/**
 * @brief Get layer 3 destination IPv4 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @return layer 3 destination IPv4 address value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetLayer3DestIPv4Addr(const ENET_Type *const pEnet, uint8_t u8Index)
{
    return pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR1_REG;
}

/**
 * @brief Set layer 3 destination IPv4 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] u32DestAddr layer 3 destination IPv4 address value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3DestIPv4Addr(ENET_Type *const pEnet, uint8_t u8Index, uint32_t u32DestAddr)
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR1_REG = u32DestAddr;
}

/**
 * @brief Get layer 3 IPv6 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [out] aIPv6Addr layer 3 IPv6 address value
 */
LOCAL_INLINE void ENET_HWA_MAC_GetLayer3IPv6Addr(const ENET_Type *const pEnet, uint8_t u8Index, uint8_t aIPv6Addr[16u])
{
    uint32_t u32AddrHH = pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR3_REG;
    uint32_t u32AddrHL = pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR2_REG;
    uint32_t u32AddrLH = pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR1_REG;
    uint32_t u32AddrLL = pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR0_REG;

    aIPv6Addr[0u]  = (uint8_t)((u32AddrHH & 0xFF000000u) >> 24u);
    aIPv6Addr[1u]  = (uint8_t)((u32AddrHH & 0x00FF0000u) >> 16u);
    aIPv6Addr[2u]  = (uint8_t)((u32AddrHH & 0x0000FF00u) >> 8u);
    aIPv6Addr[3u]  = (uint8_t)(u32AddrHH & 0x000000FFu);
    aIPv6Addr[4u]  = (uint8_t)((u32AddrHL & 0xFF000000u) >> 24u);
    aIPv6Addr[5u]  = (uint8_t)((u32AddrHL & 0x00FF0000u) >> 16u);
    aIPv6Addr[6u]  = (uint8_t)((u32AddrHL & 0x0000FF00u) >> 8u);
    aIPv6Addr[7u]  = (uint8_t)(u32AddrHL & 0x000000FFu);
    aIPv6Addr[8u]  = (uint8_t)((u32AddrLH & 0xFF000000u) >> 24u);
    aIPv6Addr[9u]  = (uint8_t)((u32AddrLH & 0x00FF0000u) >> 16u);
    aIPv6Addr[10u] = (uint8_t)((u32AddrLH & 0x0000FF00u) >> 8u);
    aIPv6Addr[11u] = (uint8_t)(u32AddrLH & 0x000000FFu);
    aIPv6Addr[12u] = (uint8_t)((u32AddrLL & 0xFF000000u) >> 24u);
    aIPv6Addr[13u] = (uint8_t)((u32AddrLL & 0x00FF0000u) >> 16u);
    aIPv6Addr[14u] = (uint8_t)((u32AddrLL & 0x0000FF00u) >> 8u);
    aIPv6Addr[15u] = (uint8_t)(u32AddrLL & 0x000000FFu);
}

/**
 * @brief Set layer 3 IPv6 address
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Index layer 3 and layer 4 filter group index
 * @param [in] aIPv6Addr layer 3 IPv6 address value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetLayer3IPv6Addr(ENET_Type *const pEnet, uint8_t u8Index, const uint8_t aIPv6Addr[16])
{
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR3_REG = ((uint32_t)aIPv6Addr[0u] << 24u) |
                                                        ((uint32_t)aIPv6Addr[1u] << 16u) |
                                                        ((uint32_t)aIPv6Addr[2u] << 8u) |
                                                        ((uint32_t)aIPv6Addr[3u]);
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR2_REG = ((uint32_t)aIPv6Addr[4u] << 24u) |
                                                        ((uint32_t)aIPv6Addr[5u] << 16u) |
                                                        ((uint32_t)aIPv6Addr[6u] << 8u) |
                                                        ((uint32_t)aIPv6Addr[7u]);
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR1_REG = ((uint32_t)aIPv6Addr[8u] << 24u) |
                                                        ((uint32_t)aIPv6Addr[9u] << 16u) |
                                                        ((uint32_t)aIPv6Addr[10u] << 8u) |
                                                        ((uint32_t)aIPv6Addr[11u]);
    pEnet->L3_L4_FILTER[u8Index].MAC_LAYER3_ADDR0_REG = ((uint32_t)aIPv6Addr[12u] << 24u) |
                                                        ((uint32_t)aIPv6Addr[13u] << 16u) |
                                                        ((uint32_t)aIPv6Addr[14u] << 8u) |
                                                        ((uint32_t)aIPv6Addr[15u]);
}

/* ================================================================ *
 *                     ENET MAC Timestamp Control                   *
 * ================================================================ */

/**
 * @brief Get time stamp control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return time stamp control value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTimestampControl(const ENET_Type *const pEnet)
{
    return pEnet->MAC_TIMESTAMP_CONTROL;
}

/**
 * @brief Set time stamp control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Ctrl time stamp control value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampControl(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->MAC_TIMESTAMP_CONTROL = u32Ctrl;
}


/**
 * @brief Get time stamp AV802_1AS mode enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true time stamp AV802_1AS mode is enabled
 * @return false time stamp AV802_1AS mode is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetAV802_1ASModeEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_AV8021ASMEN_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_AV8021ASMEN_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set time stamp AV802_1AS mode enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetAV802_1ASModeEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_AV8021ASMEN_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_AV8021ASMEN(bEnable ? 1u : 0u);
}

/**
 * @brief Get transmit timestamp status mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_TxTimestampStatusModeType
 */
LOCAL_INLINE ENET_MAC_TxTimestampStatusModeType ENET_HWA_MAC_GetTxTimestampStatusMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TXTSSTSM_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TXTSSTSM_SHIFT;
    return (ENET_MAC_TxTimestampStatusModeType)u32TmpVal;
}

/**
 * @brief Set transmit timestamp status mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eMode transmit timestamp status mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTxTimestampStatusMode(ENET_Type *const pEnet, ENET_MAC_TxTimestampStatusModeType eMode)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TXTSSTSM_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TXTSSTSM(eMode);
}

/**
 * @brief Get system time input mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_SystemTimeInputType
 */
LOCAL_INLINE ENET_MAC_SystemTimeInputType ENET_HWA_MAC_GetSystemTimeInput(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_ESTI_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_ESTI_SHIFT;
    return (ENET_MAC_SystemTimeInputType)u32TmpVal;
}

/**
 * @brief Set system time input mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eInput system time input mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSystemTimeInput(ENET_Type *const pEnet, ENET_MAC_SystemTimeInputType eInput)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_ESTI_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_ESTI(eInput);
}

/**
 * @brief Get MAC address for PTP packet filter enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true MAC address for PTP packet filter is enabled
 * @return false MAC address for PTP packet filter is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetUseMACAddrForPTPPacketFilterEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSENMACADDR_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSENMACADDR_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set MAC address for PTP packet filter enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetUseMACAddrForPTPPacketFilterEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSENMACADDR_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSENMACADDR(bEnable ? 1u : 0u);
}

/**
 * @brief Get PTP packets type for taking snapshots
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return PTP packets type
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetSnapshotPTPPacketType(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set PTP packets type for taking snapshots
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Type PTP packets type
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSnapshotPTPPacketType(ENET_Type *const pEnet, uint8_t u8Type)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(u8Type);
}

/**
 * @brief Get snapshot for messages relevant to master enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true snapshot for messages relevant to master
 * @return false snapshot for messages relevant to slave
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetMasterMsgSanpshotEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set snapshot for messages relevant to master enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetMasterMsgSanpshotEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA(bEnable ? 1u : 0u);
}

/**
 * @brief Get snapshot for event messages enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true snapshot for event messages is enabled
 * @return false snapshot for event messages is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetEventMsgSnapshotEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set snapshot for event messages enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetEventMsgSanpshotEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA(bEnable ? 1u : 0u);
}

/**
 * @brief Get processing of PTP packets over IPv4-UDP enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true processing of PTP packets over IPv4-UDP is enabled
 * @return false processing of PTP packets over IPv4-UDP is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetIPv4UDPPTPPacketProcessEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set processing of PTP packets over IPv4-UDP enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetIPv4UDPPTPPacketProcessEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA(bEnable ? 1u : 0u);
}

/**
 * @brief Get processing of PTP packets over IPv6-UDP enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true processing of PTP packets over IPv6-UDP is enabled
 * @return false processing of PTP packets over IPv6-UDP is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetIPv6UDPPTPPacketProcessEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set processing of PTP packets over IPv6-UDP enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetIPv6UDPPTPPacketProcessEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA(bEnable ? 1u : 0u);
}

/**
 * @brief Get processing of PTP packets over ethernet enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true processing of PTP packets over ethernet is enabled
 * @return false processing of PTP packets over ethernet is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetEthernetPTPPacketProcessEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSIPENA_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set processing of PTP packets over ethernet enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetEthernetPTPPacketProcessEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSIPENA(bEnable ? 1u : 0u);
}

/**
 * @brief Get PTP packets processing format version
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_PTPVersionType
 */
LOCAL_INLINE ENET_MAC_PTPVersionType ENET_HWA_MAC_GetPTPPacketVersion(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA_SHIFT;
    return (ENET_MAC_PTPVersionType)u32TmpVal;
}

/**
 * @brief Set PTP packets processing format version
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eVersion PTP version
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPTPPacketVersion(ENET_Type *const pEnet, ENET_MAC_PTPVersionType eVersion)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA(eVersion);
}

/**
 * @brief Get PTP timestamp rollover mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_TimestampRolloverType
 */
LOCAL_INLINE ENET_MAC_TimestampRolloverType ENET_HWA_MAC_GetTimestampRolloverCtrl(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_SHIFT;
    return (ENET_MAC_TimestampRolloverType)u32TmpVal;
}

/**
 * @brief Set PTP timestamp rollover mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eCtrl timestamp rollover mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetIimestampRolloverCtrl(ENET_Type *const pEnet, ENET_MAC_TimestampRolloverType eCtrl)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR(eCtrl);
}

/**
 * @brief Get timestamp for all packets enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true timestamp for all packets is enabled
 * @return false timestamp for all packets is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTimestampForAllPacketEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSENALL_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSENALL_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set timestamp for all packets enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampForAllPacketEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSENALL_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSENALL(bEnable ? 1u : 0u);
}

/**
 * @brief Get presentation time generation enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true presentation time generation is enabled
 * @return false presentation time generation is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPresentationTimeGenerationEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_PTGE_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_PTGE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set presentation time generation enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPresentationTimeGenerationEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_PTGE_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_PTGE(bEnable ? 1u : 0u);
}

/**
 * @brief Get PTP addend register update status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_StatusType
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetAddendRegisterUpdateStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief Initiate the  addend register update operation
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_UpdateAddendRegister(ENET_Type *const pEnet)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK;
}

/**
 * @brief Get timestamp update status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_StatusType
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetTimestampUpdateStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief Initiate the timestamp update operation
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_UpdateTimestamp(ENET_Type *const pEnet)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK;
}

/**
 * @brief Get timestamp initialize status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_StatusType
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetTimestampInitStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSINIT_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief Initialize PTP timestamp
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_InitTimestamp(ENET_Type *const pEnet)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK;
}

/**
 * @brief Get timestamp update method (fine or coarse)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_TimestampUpdateMethodType
 */
LOCAL_INLINE ENET_MAC_TimestampUpdateMethodType ENET_HWA_MAC_GetTimestampUpdateMethod(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT_SHIFT;
    return (ENET_MAC_TimestampUpdateMethodType)u32TmpVal;
}

/**
 * @brief Set timestamp update method (fine or coarse)
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eMethod (fine update or coarse update)
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampUpdateMethod(ENET_Type *const pEnet, ENET_MAC_TimestampUpdateMethodType eMethod)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT(eMethod);
}

/**
 * @brief Get timestamp enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true timestamp processing is enabled
 * @return false timestamp processing is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTimestampEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSENA_MASK) >>
                         ENET_MAC_TIMESTAMP_CONTROL_TSENA_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}


/**
 * @brief Set timestamp processing enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable timestamp processing
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MAC_TIMESTAMP_CONTROL = (pEnet->MAC_TIMESTAMP_CONTROL &
                                    ~(ENET_MAC_TIMESTAMP_CONTROL_TSENA_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK |
                                      ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK)) |
                                   ENET_MAC_TIMESTAMP_CONTROL_TSENA(bEnable ? 1u : 0u);
}

/**
 * @brief Get PTP sub-second increment register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return sub-second increment register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetSubSecondIncrementReg(const ENET_Type *const pEnet)
{
    return pEnet->MAC_SUB_SECOND_INCREMENT;
}

/**
 * @brief Set PTP sub-second increment register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Increment increment value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSubSecondIncrementReg(ENET_Type *const pEnet, uint32_t u32Increment)
{
    pEnet->MAC_SUB_SECOND_INCREMENT = u32Increment;
}

/**
 * @brief Get PTP sub-second increment value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return sub-second increment value
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetSubSecondIncrementValue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_SUB_SECOND_INCREMENT & ENET_MAC_SUB_SECOND_INCREMENT_SSINC_MASK) >>
                         ENET_MAC_SUB_SECOND_INCREMENT_SSINC_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set PTP sub-second increment value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Increment sub-second increment value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSubSecondIncrementValue(ENET_Type *const pEnet, uint8_t u8Increment)
{
    pEnet->MAC_SUB_SECOND_INCREMENT = (pEnet->MAC_SUB_SECOND_INCREMENT & ~ENET_MAC_SUB_SECOND_INCREMENT_SSINC_MASK) |
                                      ENET_MAC_SUB_SECOND_INCREMENT_SSINC(u8Increment);
}

/**
 * @brief Get PTP sub-nanosecond increment value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return sub-nanosecond increment value
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetSubNanoSecondIncrementValue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_SUB_SECOND_INCREMENT & ENET_MAC_SUB_SECOND_INCREMENT_SNSINC_MASK) >>
                         ENET_MAC_SUB_SECOND_INCREMENT_SNSINC_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set PTP sub-nanosecond increment value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Increment sub-nanosecond increment value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSubNanoSecondIncrementValue(ENET_Type *const pEnet, uint8_t u8Increment)
{
    pEnet->MAC_SUB_SECOND_INCREMENT = (pEnet->MAC_SUB_SECOND_INCREMENT & ~ENET_MAC_SUB_SECOND_INCREMENT_SNSINC_MASK) |
                                      ENET_MAC_SUB_SECOND_INCREMENT_SNSINC(u8Increment);
}

/**
 * @brief Get PTP system time seconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return seconds value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetSystemTimeSeconds(const ENET_Type *const pEnet)
{
    return pEnet->MAC_SYSTEM_TIME_SECONDS;
}

/**
 * @brief Get PTP system time nanoseconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return nanoseconds value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetSystemTimeNanoSeconds(const ENET_Type *const pEnet)
{
    return pEnet->MAC_SYSTEM_TIME_NANOSECONDS;
}

/**
 * @brief Get PTP system time seconds update register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return seconds update register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetSystemTimeSecondsUpdateValue(const ENET_Type *const pEnet)
{
    return pEnet->MAC_SYSTEM_TIME_SECONDS_UPDATE;
}

/**
 * @brief Set PTP system time seconds update register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Seconds seconds update register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSystemTimeSecondsUpdateValue(ENET_Type *const pEnet, uint32_t u32Seconds)
{
    pEnet->MAC_SYSTEM_TIME_SECONDS_UPDATE = u32Seconds;
}

/**
 * @brief Get PTP system time nanoseconds update register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return nanoseconds update register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetSystemTimeNanoSecondsUpdateReg(const ENET_Type *const pEnet)
{
    return pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE;
}

/**
 * @brief Set PTP system time nanoseconds update register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Reg nanoseconds update register value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSystemTimeNanoSecondsUpdateReg(ENET_Type *const pEnet, uint32_t u32Reg)
{
    pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = u32Reg;
}

/**
 * @brief Get PTP system time update operation,add or subtract time
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_SystemTimeOperationType
 */
LOCAL_INLINE ENET_MAC_SystemTimeOperationType ENET_HWA_MAC_GetTimeUpdateOperation(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE &
                          ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK) >>
                         ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_SHIFT;
    return (ENET_MAC_SystemTimeOperationType)u32TmpVal;
}

/**
 * @brief Set PTP system time update operation,add or subtract time
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eOperation add or subtract time
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimeUpdateOperation(ENET_Type *const pEnet, ENET_MAC_SystemTimeOperationType eOperation)
{
    pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = (pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE &
                                                 ~ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB_MASK) |
                                                ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB(eOperation);
}

/**
 * @brief Get PTP system time nanoseconds update value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return nanoseconds update value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetSystemTimeNanoSecondsUpdateValue(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE &
                          ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK) >>
                         ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Set PTP system time nanoseconds update value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32NanoSeconds nanoseconds update value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSystemTimeNanoSecondsUpdateValue(ENET_Type *const pEnet, uint32_t u32NanoSeconds)
{
    pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = (pEnet->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE &
                                                 ~ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS_MASK) |
                                                ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(u32NanoSeconds);
}

/**
 * @brief Get PTP timestamp addend register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return timestamp addend value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTimestampAddend(const ENET_Type *const pEnet)
{
    return pEnet->MAC_TIMESTAMP_ADDEND;
}

/**
 * @brief Set PTP timestamp addend register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Time timestamp addend value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampAddend(ENET_Type *const pEnet, uint32_t u32Time)
{
    pEnet->MAC_TIMESTAMP_ADDEND = u32Time;
}

/**
 * @brief Get PTP system time seconds bits[47:32] value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return seconds bits[47:32] value
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetSystemTimeHigherWordSeconds(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS &
                          ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK) >>
                         ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set PTP system time seconds bits[47:32] value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u16Seconds seconds bits[47:32] value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetSystemTimeHigherWordSeconds(ENET_Type *const pEnet, uint16_t u16Seconds)
{
    pEnet->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS = ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR(u16Seconds);
}

/**
 * @brief Get the timestamp status
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t the timestamp status
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTimestampStatus(const ENET_Type *const pEnet)
{
    return pEnet->MAC_TIMESTAMP_STATUS;
}

/**
 * @brief Indicates whether the transmit timestamp interrupt status is detected
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true transmit timestamp interrupt is detected
 * @return false transmit timestamp interrupt is not detected
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTxTimestampInterruptStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_STATUS & ENET_MAC_TIMESTAMP_STATUS_TXTSSIS_MASK) >>
                         ENET_MAC_TIMESTAMP_STATUS_TXTSSIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}


/**
 * @brief Clear the transmit timestamp interrupt status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTxTimestampInterruptStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_TIMESTAMP_STATUS |= ENET_MAC_TIMESTAMP_STATUS_TXTSSIS_MASK;
}

/**
 * @brief Indicates whether the timestamp target time error status of the PPS channel is detected
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann the channel number of PPS
 * @return true timestamp target time error is detected
 * @return false timestamp target time error is not detected
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTimestampTargetTimeError(const ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_STATUS &
                          ((uint32_t)ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR0_MASK << (2u * (uint32_t)ePPSChann))) >>
                         ((uint32_t)ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR0_SHIFT + 2u * (uint32_t)ePPSChann);
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the timestamp target time error status of the PPS channel
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann the channel number of PPS
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTimestampTargetTimeError(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann)
{
    pEnet->MAC_TIMESTAMP_STATUS |= (uint32_t)ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR0_MASK << (2u * (uint32_t)ePPSChann);
}

/**
 * @brief Indicates whether the timestamp target time reached for target time of the PPS channel
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann the channel number of PPS
 * @return true timestamp target time is reached
 * @return false timestamp target time is not reached
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTimestampTargetTimeReachedStatus(const ENET_Type *const pEnet,
                                                                   ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_STATUS &
                          ((uint32_t)ENET_MAC_TIMESTAMP_STATUS_TSTARGT0_MASK << (2u * (uint32_t)ePPSChann))) >>
                         ((uint32_t)ENET_MAC_TIMESTAMP_STATUS_TSTARGT0_SHIFT + 2u * (uint32_t)ePPSChann);
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the status of the timestamp target time reached for target time of the PPS channel
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann the channel number of PPS
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTimestampTargetTimeReachedStatus(ENET_Type *const pEnet,
                                                                     ENET_MAC_PPSChannelType ePPSChann)
{
    pEnet->MAC_TIMESTAMP_STATUS |= (uint32_t)ENET_MAC_TIMESTAMP_STATUS_TSTARGT0_MASK << (2u * (uint32_t)ePPSChann);
}

/**
 * @brief Indicates whether the timestamp seconds overflow status is detected
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true timestamp seconds overflow status is detected
 * @return false timestamp seconds overflow status is not detected
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetTimestampSecondsOverflowStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_STATUS & ENET_MAC_TIMESTAMP_STATUS_TSSOVF_MASK) >>
                         ENET_MAC_TIMESTAMP_STATUS_TSSOVF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear the timestamp seconds overflow status
 * @note This function shall only be called when MAC_CSR_SW_CTRL[RCWE] = 1
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MAC_ClearTimestampSecondsOverflowStatus(ENET_Type *const pEnet)
{
    pEnet->MAC_TIMESTAMP_STATUS |= ENET_MAC_TIMESTAMP_STATUS_TSSOVF_MASK;
}

/**
 * @brief  Contains the nanosecond part of timestamp captured for transmit packets when tx status is disabled
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  transmit timestamp status in nanoseconds
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxTimestampStatusInNanoseconds(const ENET_Type *const pEnet)
{
    return pEnet->MAC_TX_TIMESTAMP_STATUS_NANOSECONDS;
}

/**
 * @brief  Contains the second part of timestamp captured for transmit packets when tx status is disabled
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  transmit timestamp status in seconds
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTxTimestampStatusInSeconds(const ENET_Type *const pEnet)
{
    return pEnet->MAC_TX_TIMESTAMP_STATUS_SECONDS;
}

/**
 * @brief  Get timestamp ingress asymmetry correction, used for PDelay_Resp PTP messages
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  correction value
 */
LOCAL_INLINE int32_t ENET_HWA_MAC_GetTimestampIngressAsymmetryCorrection(const ENET_Type *const pEnet)
{
    return (int32_t)pEnet->MAC_TIMESTAMP_INGRESS_ASYM_CORR;
}

/**
 * @brief  Set timestamp ingress asymmetry correction, used for PDelay_Resp PTP messages
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] s32Correction  correction value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampIngressAsymmetryCorrection(ENET_Type *const pEnet, int32_t s32Correction)
{
    pEnet->MAC_TIMESTAMP_INGRESS_ASYM_CORR = (uint32_t)s32Correction;
}

/**
 * @brief  Get timestamp egress asymmetry correction, used for PDelay_Req PTP messages
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  correction value
 */
LOCAL_INLINE int32_t ENET_HWA_MAC_GetTimestampEgressAsymmetryCorrection(const ENET_Type *const pEnet)
{
    return (int32_t)pEnet->MAC_TIMESTAMP_EGRESS_ASYM_CORR;
}

/**
 * @brief  Set timestamp egress asymmetry correction, used for PDelay_Req PTP messages
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] s32Correction  correction value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampEgressAsymmetryCorrection(ENET_Type *const pEnet, int32_t s32Correction)
{
    pEnet->MAC_TIMESTAMP_EGRESS_ASYM_CORR = (uint32_t)s32Correction;
}

/**
 * @brief  Get timestamp ingress correction in nanoseconds, used for timestamp in ingress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  correction value
 */
LOCAL_INLINE int32_t ENET_HWA_MAC_GetTimestampIngressCorrectionInNanoseconds(const ENET_Type *const pEnet)
{
    return (int32_t)pEnet->MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND;
}

/**
 * @brief  Set timestamp ingress correction in nanoseconds, used for timestamp in ingress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] s32NanoSec  correction value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampIngressCorrectionInNanoseconds(ENET_Type *const pEnet, int32_t s32NanoSec)
{
    pEnet->MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND = (uint32_t)s32NanoSec;
}

/**
 * @brief  Get timestamp egress correction in nanoseconds, used for timestamp in egress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  correction value
 */
LOCAL_INLINE int32_t ENET_HWA_MAC_GetTimestampEgressCorrectionInNanoseconds(const ENET_Type *const pEnet)
{
    return (int32_t)pEnet->MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND;
}

/**
 * @brief  Set timestamp egress correction in nanoseconds, used for timestamp in egress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] s32NanoSec  correction value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampEgressCorrectionInNanoseconds(ENET_Type *const pEnet, int32_t s32NanoSec)
{
    pEnet->MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND = (uint32_t)s32NanoSec;
}

/**
 * @brief  Get timestamp ingress correction in sub-nanoseconds, used for timestamp in ingress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  correction value
 */
LOCAL_INLINE int8_t ENET_HWA_MAC_GetTimestampIngressCorrectionInSubNanoseconds(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC &
                          ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_MASK) >>
                         ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS_SHIFT;
    return (int8_t)u32TmpVal;
}

/**
 * @brief  Set timestamp ingress correction in sub-nanoseconds, used for timestamp in ingress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] s8SubNanoSec  correction value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampIngressCorrectionInSubNanoseconds(ENET_Type *const pEnet, int8_t s8SubNanoSec)
{
    pEnet->MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC = ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS(s8SubNanoSec);
}

/**
 * @brief  Get timestamp egress correction in sub-nanoseconds, used for timestamp in egress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  correction value
 */
LOCAL_INLINE int8_t ENET_HWA_MAC_GetTimestampEgressCorrectionInSubNanoseconds(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC &
                          ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_MASK) >>
                         ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS_SHIFT;
    return (int8_t)u32TmpVal;
}

/**
 * @brief  Set timestamp egress correction in sub-nanoseconds, used for timestamp in egress path
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] s8SubNanoSec  correction value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetTimestampEgressCorrectionInSubNanoseconds(ENET_Type *const pEnet, int8_t s8SubNanoSec)
{
    pEnet->MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC = ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS(s8SubNanoSec);
}

/**
 * @brief  Get the ingress MAC latency
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  ingress latency
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTimestampIngressLatency(const ENET_Type *const pEnet)
{
    return pEnet->MAC_TIMESTAMP_INGRESS_LATENCY;
}

/**
 * @brief  Get the ingress MAC latency in nanoseconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  ingress latency in nanoseconds
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetTimestampIngressLatencyInNanoseconds(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_INGRESS_LATENCY & ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS_MASK) >>
                         ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief  Get the ingress MAC latency in sub-nanoseconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  ingress latency in sub-nanoseconds
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetTimestampIngressLatencyInSubNanoseconds(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_INGRESS_LATENCY & ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS_MASK) >>
                         ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief  Get the egress MAC latency
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  egress latency
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetTimestampEgressLatency(const ENET_Type *const pEnet)
{
    return pEnet->MAC_TIMESTAMP_EGRESS_LATENCY;
}

/**
 * @brief  Get the egress MAC latency in nanoseconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  egress latency in nanoseconds
 */
LOCAL_INLINE uint16_t ENET_HWA_MAC_GetTimestampEgressLatencyInNanoseconds(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_EGRESS_LATENCY & ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS_MASK) >>
                         ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS_SHIFT;
    return (uint16_t)u32TmpVal;
}


/**
 * @brief  Get the egress MAC latency in sub-nanoseconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  egress latency in sub-nanoseconds
 */
LOCAL_INLINE uint8_t ENET_HWA_MAC_GetTimestampEgressLatencyInSubNanoseconds(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MAC_TIMESTAMP_EGRESS_LATENCY & ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS_MASK) >>
                         ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief  Get PPS control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  PPS control value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPPSControl(const ENET_Type *const pEnet)
{
    return pEnet->PPS.CONTROL;
}

/**
 * @brief  Set PPS control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Ctrl  PPS control value
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPPSControl(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->PPS.CONTROL = u32Ctrl;
}

/**
 * @brief  Get PPS MCGR Mode enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return true PPS MCGR Mode is enabled
 * @return false PPS MCGR Mode is disabled
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetPPSMCGRModeEnFlag(const ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = pEnet->PPS.CONTROL & ((uint32_t)ENET_MAC_PPS_CONTROL_MCGREN0_MASK << (8u * (uint32_t)ePPSChann));
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set PPS MCGR Mode enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] bEnable  enable or disable
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPPSMCGRModeEnFlag(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann, bool bEnable)
{
    pEnet->PPS.CONTROL = (pEnet->PPS.CONTROL & (~(ENET_MAC_PPS_CONTROL_MCGREN0_MASK << (8u * (uint32_t)ePPSChann)))) |
                         ((uint32_t)ENET_MAC_PPS_CONTROL_MCGREN0(bEnable ? 1u : 0u) << (8u * (uint32_t)ePPSChann));
}

/**
 * @brief  Get PPS channel target time register operating mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return ENET_MAC_PPSTargetTimeModeType
 */
LOCAL_INLINE ENET_MAC_PPSTargetTimeModeType ENET_HWA_MAC_GetChannelPPSTargetTimeModeSelect(const ENET_Type *const pEnet,
        ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = (pEnet->PPS.CONTROL & (ENET_MAC_PPS_CONTROL_TRGTMODSEL0_MASK  << (8u * (uint32_t)ePPSChann))) >>
                         (ENET_MAC_PPS_CONTROL_TRGTMODSEL0_SHIFT + (8u * (uint32_t)ePPSChann));
    return (ENET_MAC_PPSTargetTimeModeType)u32TmpVal;
}

/**
 * @brief  Set PPS channel target time register operating mode
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] eTrgtMode target time operating mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetChannelPPSTargetTimeModeSelect(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann,
                                                                 ENET_MAC_PPSTargetTimeModeType eTrgtMode)
{
    pEnet->PPS.CONTROL = (pEnet->PPS.CONTROL & (~(ENET_MAC_PPS_CONTROL_TRGTMODSEL0_MASK << (8u * (uint32_t)ePPSChann)))) |
                         (ENET_MAC_PPS_CONTROL_TRGTMODSEL0(eTrgtMode) << (8u * (uint32_t)ePPSChann));
}

/**
 * @brief  Get PPS flexible mode enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return true PPS work in flexible mode
 * @return false PPS work in fixed mode
 */
LOCAL_INLINE bool ENET_HWA_MAC_GetChannelFlexiblePPSOutputEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->PPS.CONTROL & ENET_MAC_PPS_CONTROL_PPSEN0_MASK) >> ENET_MAC_PPS_CONTROL_PPSEN0_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set PPS flexible mode enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable PPS flexible or fixed mode
 */
LOCAL_INLINE void ENET_HWA_MAC_SetChannelFlexiblePPSOutputEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->PPS.CONTROL = (pEnet->PPS.CONTROL & (~ENET_MAC_PPS_CONTROL_PPSEN0_MASK)) |
                         ENET_MAC_PPS_CONTROL_PPSEN0(bEnable ? 1u : 0u);
}

/**
 * @brief  Get PPS MCGR command
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return ENET_MAC_MCGRCmdType
 */
LOCAL_INLINE ENET_MAC_MCGRCmdType ENET_HWA_MAC_GetPPSMCGRCommand(const ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = (pEnet->PPS.CONTROL & ((uint32_t)ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_MASK << (8u * (uint32_t)ePPSChann))) >>
                         ((uint32_t)ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_SHIFT + (8u * (uint32_t)ePPSChann));
    return (ENET_MAC_MCGRCmdType)u32TmpVal;
}

/**
 * @brief  Set PPS MCGR command
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] eCmd MCGR command
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPPSMCGRCommand(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann,
                                                 ENET_MAC_MCGRCmdType eCmd)
{
    pEnet->PPS.CONTROL = (pEnet->PPS.CONTROL & (~(ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_MASK << (8u * (uint32_t)ePPSChann)))) |
                         (ENET_MAC_PPS_CONTROL_MCGREN0(1u) << (8u * (uint32_t)ePPSChann)) |
                         (ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD(eCmd) << (8u * (uint32_t)ePPSChann));
}

/**
 * @brief  Get flexible PPS command
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return ENET_MAC_PPSCmdType
 */
LOCAL_INLINE ENET_MAC_PPSCmdType ENET_HWA_MAC_GetFlexiblePPSCommand(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = (pEnet->PPS.CONTROL & ((uint32_t)ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_MASK << (8u * (uint32_t)ePPSChann))) >>
                         ((uint32_t)ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_SHIFT + (8u * (uint32_t)ePPSChann));
    return (ENET_MAC_PPSCmdType)u32TmpVal;
}

/**
 * @brief  Set flexible PPS command
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] eCmd flexible PPS command
 */
LOCAL_INLINE void ENET_HWA_MAC_SetFlexiblePPSCommand(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann,
                                                     ENET_MAC_PPSCmdType eCmd)
{
    pEnet->PPS.CONTROL = (pEnet->PPS.CONTROL & (~(ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_MASK << (8u * (uint32_t)ePPSChann)))) |
                         (ENET_MAC_PPS_CONTROL_PPSEN0(1u)) |
                         (ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD(eCmd) << (8u * (uint32_t)ePPSChann));
}

/**
 * @brief  Get fixed PPS output frequency
 *
 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MAC_PPSFreqCtrlType
 */
LOCAL_INLINE ENET_MAC_PPSFreqCtrlType ENET_HWA_MAC_GetFixedPPSOutputFrequency(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->PPS.CONTROL & ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_MASK) >>
                         ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD_SHIFT;
    return (ENET_MAC_PPSFreqCtrlType)u32TmpVal;
}

/**
 * @brief  Set fixed PPS output frequency
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eFreq frequency value defined in ENET_MAC_PPSFreqCtrlType
 */
LOCAL_INLINE void ENET_HWA_MAC_SetFixedPPSOutputFrequency(ENET_Type *const pEnet, ENET_MAC_PPSFreqCtrlType eFreq)
{
    pEnet->PPS.CONTROL = ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD(eFreq);
}

/**
 * @brief  Get PPS target time seconds

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return uint32_t target time seconds
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPPSTargetTimeInSeconds(const ENET_Type *const pEnet,
                                                             ENET_MAC_PPSChannelType ePPSChann)
{
    return pEnet->PPS.CH[ePPSChann].TARGET_TIME_SECONDS;
}

/**
 * @brief  Set PPS target time seconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] u32Seconds target time seconds
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPPSTargetTimeInSeconds(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann,
                                                         uint32_t u32Seconds)
{
    pEnet->PPS.CH[ePPSChann].TARGET_TIME_SECONDS = u32Seconds;
}

/**
 * @brief  Get PPS target time busy status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return ENET_MAC_StatusType
 */
LOCAL_INLINE ENET_MAC_StatusType ENET_HWA_MAC_GetPPSTargetTimeBusyStatus(const ENET_Type *const pEnet,
                                                                         ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = (pEnet->PPS.CH[ePPSChann].TARGET_TIME_NANOSECONDS &
                          ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0_MASK) >>
                         ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS_TRGTBUSY0_SHIFT;
    return (ENET_MAC_StatusType)u32TmpVal;
}

/**
 * @brief  Get PPS target time nanoseconds

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return uint32_t target time nanoseconds
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPPSTargetTimeInNanoseconds(const ENET_Type *const pEnet,
                                                                 ENET_MAC_PPSChannelType ePPSChann)
{
    uint32_t u32TmpVal = (pEnet->PPS.CH[ePPSChann].TARGET_TIME_NANOSECONDS &
                          ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0_MASK) >>
                         ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0_SHIFT;
    return u32TmpVal;
}

/**
 * @brief  Set PPS target time nanoseconds
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] u32NanoSeconds target time nanoseconds
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPPSTargetTimeInNanoseconds(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann,
                                                             uint32_t u32NanoSeconds)
{
    pEnet->PPS.CH[ePPSChann].TARGET_TIME_NANOSECONDS = ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS_TTSL0(u32NanoSeconds);
}

/**
 * @brief  Get PPS pulse interval

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return uint32_t PPS interval value
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPPSInterval(const ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann)
{
    return pEnet->PPS.CH[ePPSChann].INTERVAL;
}

/**
 * @brief  Set PPS pulse interval
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] u32Interval PPS pulse interval
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPPSInterval(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann,
                                              uint32_t u32Interval)
{
    pEnet->PPS.CH[ePPSChann].INTERVAL = u32Interval;
}

/**
 * @brief  Get PPS pulse width

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @return uint32_t PPS pulse width
 */
LOCAL_INLINE uint32_t ENET_HWA_MAC_GetPPSWidth(const ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann)
{
    return pEnet->PPS.CH[ePPSChann].WIDTH;
}

/**
 * @brief  Set PPS pulse width
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePPSChann PPS channel
 * @param [in] u32Width PPS pulse width
 */
LOCAL_INLINE void ENET_HWA_MAC_SetPPSWidth(ENET_Type *const pEnet, ENET_MAC_PPSChannelType ePPSChann, uint32_t u32Width)
{
    pEnet->PPS.CH[ePPSChann].WIDTH = u32Width;
}

/* ================================================================ *
 *                  ENET MTL Configuration and Status               *
 * ================================================================ */

/**
 * @brief  Get MTL operation mode register value

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t MTL operation mode
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetOperationMode(const ENET_Type *const pEnet)
{
    return pEnet->MTL.OPERATION_MODE;
}

/**
 * @brief  Set MTL operation mode register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32OpMode MTL operation mode
 */
LOCAL_INLINE void ENET_HWA_MTL_SetOperationMode(ENET_Type *const pEnet, uint32_t u32OpMode)
{
    pEnet->MTL.OPERATION_MODE = u32OpMode;
}

/**
 * @brief  Get MTL counter reset status

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t counter reset status
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetCounterResetStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.OPERATION_MODE & ENET_MTL_OPERATION_MODE_CNTCLR_MASK) >>
                         ENET_MTL_OPERATION_MODE_CNTCLR_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Reset MTL counters
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ResetCounters(ENET_Type *const pEnet)
{
    pEnet->MTL.OPERATION_MODE |= ENET_MTL_OPERATION_MODE_CNTCLR_MASK;
}

/**
 * @brief  Get MTL counter preset status

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t counter preset status
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetPresetCounterStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.OPERATION_MODE & ENET_MTL_OPERATION_MODE_CNTPRST_MASK) >>
                         ENET_MTL_OPERATION_MODE_CNTPRST_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Preset MTL counters
 *
 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_InitPresetCounters(ENET_Type *const pEnet)
{
    pEnet->MTL.OPERATION_MODE |= ENET_MTL_OPERATION_MODE_CNTPRST_MASK;
}

/**
 * @brief  Get MTL algorithm for transmit scheduling

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_TxScheduleAlgorithmType
 */
LOCAL_INLINE ENET_MTL_TxScheduleAlgorithmType ENET_HWA_MTL_GetTxSchedulingAlgorithm(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.OPERATION_MODE & ENET_MTL_OPERATION_MODE_SCHALG_MASK) >>
                         ENET_MTL_OPERATION_MODE_SCHALG_SHIFT;
    return (ENET_MTL_TxScheduleAlgorithmType)u32TmpVal;
}

/**
 * @brief  Set MTL algorithm for transmit scheduling
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eScheduleAlgorithm algorithm mode
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxSchedulingAlgorithm(ENET_Type *const pEnet,
                                                        ENET_MTL_TxScheduleAlgorithmType eScheduleAlgorithm)
{
    pEnet->MTL.OPERATION_MODE = (pEnet->MTL.OPERATION_MODE & ~ENET_MTL_OPERATION_MODE_SCHALG_MASK) |
                                ENET_MTL_OPERATION_MODE_SCHALG(eScheduleAlgorithm);
}

/**
 * @brief  Get MTL algorithm for receive arbitration

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_RxArbitrationAlgorithmType
 */
LOCAL_INLINE ENET_MTL_RxArbitrationAlgorithmType ENET_HWA_MTL_GetRxArbitrationAlgorithm(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.OPERATION_MODE & ENET_MTL_OPERATION_MODE_RAA_MASK) >>
                         ENET_MTL_OPERATION_MODE_RAA_SHIFT;
    return (ENET_MTL_RxArbitrationAlgorithmType)u32TmpVal;
}

/**
 * @brief  Set MTL algorithm for receive arbitration
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eArbitrationAlgorithm arbitration algorithm mode
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxArbitrationAlgorithm(ENET_Type *const pEnet,
                                                         ENET_MTL_RxArbitrationAlgorithmType eArbitrationAlgorithm)
{
    pEnet->MTL.OPERATION_MODE = (pEnet->MTL.OPERATION_MODE & ~ENET_MTL_OPERATION_MODE_RAA_MASK) |
                                ENET_MTL_OPERATION_MODE_RAA(eArbitrationAlgorithm);
}

/**
 * @brief  Get whether tx packet status received from the MAC is droped or not

 * @param [in] pEnet the base address of the ENET instance
 * @return true tx packet status is droped
 * @return false tx packet status is forwarded to application
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetDropTxPacketStatusEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.OPERATION_MODE & ENET_MTL_OPERATION_MODE_DTXSTS_MASK) >>
                         ENET_MTL_OPERATION_MODE_DTXSTS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set drop tx packet status enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable drop or forward tx packet status
 */
LOCAL_INLINE void ENET_HWA_MTL_SetDropTxPacketStatusEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.OPERATION_MODE = (pEnet->MTL.OPERATION_MODE & ~ENET_MTL_OPERATION_MODE_DTXSTS_MASK) |
                                ENET_MTL_OPERATION_MODE_DTXSTS(bEnable ? 1u : 0u);
}

/**
 * @brief  Get MTL debug control register value

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t MTL debug control value
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetDebugCtrl(const ENET_Type *const pEnet)
{
    return pEnet->MTL.DBG_CTL;
}

/**
 * @brief  Set MTL debug control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32DebugCtrl control value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetDebugCtrl(ENET_Type *const pEnet, uint32_t u32DebugCtrl)
{
    pEnet->MTL.DBG_CTL = u32DebugCtrl;
}

/**
 * @brief  Get transmit status available interrupt status enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true transmit status available interrupt status is enabled
 * @return false transmit status available interrupt status is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxStatusAvailableIntEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_STSIE_MASK) >> ENET_MTL_DBG_CTL_STSIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set transmit status available interrupt status enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxStatusAvailableIntEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_STSIE_MASK) | ENET_MTL_DBG_CTL_STSIE(bEnable ? 1u : 0u);
}

/**
 * @brief  Get receive packet available interrupt status enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true receive packet available interrupt status is enabled
 * @return false receive packet available interrupt status is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxPacketAvailableIntEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_PKTIE_MASK) >> ENET_MTL_DBG_CTL_PKTIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set receive packet available interrupt status enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxPacketAvailableIntEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_PKTIE_MASK) | ENET_MTL_DBG_CTL_PKTIE(bEnable ? 1u : 0u);
}

/**
 * @brief  Get the FIFO selected for debug access

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_DebugAccessFIFOType
 */
LOCAL_INLINE ENET_MTL_DebugAccessFIFOType ENET_HWA_MTL_GetDebugAccessFIFO(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_FIFOSEL_MASK) >> ENET_MTL_DBG_CTL_FIFOSEL_SHIFT;
    return (ENET_MTL_DebugAccessFIFOType)u32TmpVal;
}

/**
 * @brief  Set the FIFO selected for debug access
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eFIFOType debug FIFO defined in ENET_MTL_DebugAccessFIFOType
 */
LOCAL_INLINE void ENET_HWA_MTL_SetDebugAccessFIFO(ENET_Type *const pEnet, ENET_MTL_DebugAccessFIFOType eFIFOType)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_FIFOSEL_MASK) | ENET_MTL_DBG_CTL_FIFOSEL(eFIFOType);
}

/**
 * @brief  Get write operation on selected FIFO enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true write operation on selected FIFO is enabled
 * @return false write operation on selected FIFO is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetFIFOWriteEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_FIFOWREN_MASK) >> ENET_MTL_DBG_CTL_FIFOWREN_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set write operation on selected FIFO enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetFIFOWriteEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_FIFOWREN_MASK) | ENET_MTL_DBG_CTL_FIFOWREN(bEnable ? 1u : 0u);
}

/**
 * @brief  Get pointers of selected FIFO reset status

 * @param [in] pEnet the base address of the ENET instance
 * @return true FIFO reset is enabled
 * @return false FIFO reset is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetSelectedFIFOPointerResetStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_RSTSEL_MASK) >> ENET_MTL_DBG_CTL_RSTSEL_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Reset pointers of selected FIFO
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetSelectedFIFOPointerResetFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_RSTSEL_MASK) | ENET_MTL_DBG_CTL_RSTSEL(bEnable ? 1u : 0u);
}

/**
 * @brief  Get pointers of all FIFOs reset status

 * @param [in] pEnet the base address of the ENET instance
 * @return true all FIFOs reset is enabled
 * @return false all FIFOs reset is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetAllFIFOPointersResetStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_RSTALL_MASK) >> ENET_MTL_DBG_CTL_RSTALL_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Reset pointers of all FIFOs
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetAllFIFOPointerResetFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_RSTALL_MASK) | ENET_MTL_DBG_CTL_RSTALL(bEnable ? 1u : 0u);
}

/**
 * @brief  Encoded packet state,the control information to the Tx FIFO or Rx FIFO
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eState
 */
LOCAL_INLINE void ENET_HWA_MTL_SetFIFOPacketState(ENET_Type *const pEnet, ENET_MTL_FIFOPacketStatusType eState)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_PKTSTATE_MASK) | ENET_MTL_DBG_CTL_PKTSTATE(eState);
}

/**
 * @brief  Indicates the number of data bytes valid in the data register during Write operation
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eByteValid the number of data bytes valid
 */
LOCAL_INLINE void ENET_HWA_MTL_SetByteEnable(ENET_Type *const pEnet, ENET_MTL_ByteEnableType eByteValid)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_BYTEEN_MASK) | ENET_MTL_DBG_CTL_BYTEEN(eByteValid);
}

/**
 * @brief  Get pointers of all FIFOs reset status

 * @param [in] pEnet the base address of the ENET instance
 * @return true all FIFOs reset is enabled
 * @return false all FIFOs reset is disabled
 */
LOCAL_INLINE ENET_MTL_FIFODebugAccessType ENET_HWA_MTL_GetFIFODebugModeAccessType(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_DBGMOD_MASK) >> ENET_MTL_DBG_CTL_DBGMOD_SHIFT;
    return (ENET_MTL_FIFODebugAccessType)u32TmpVal;
}

/**
 * @brief  Set the debug mode of accessing to fifo
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eAccessType accessing to fifo is restricted or not
 */
LOCAL_INLINE void ENET_HWA_MTL_SetFIFODebugModeAccessType(ENET_Type *const pEnet, ENET_MTL_FIFODebugAccessType eAccessType)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_DBGMOD_MASK) | ENET_MTL_DBG_CTL_DBGMOD(eAccessType);
}

/**
 * @brief  Get FIFO debug access enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true the debug mode access to the FIFO is enabled
 * @return false the debug mode access to the FIFO is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetFIFODebugAccessEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_CTL & ENET_MTL_DBG_CTL_FDBGEN_MASK) >> ENET_MTL_DBG_CTL_FDBGEN_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set FIFO debug access enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetFIFODebugAccessEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.DBG_CTL = (pEnet->MTL.DBG_CTL & ~ENET_MTL_DBG_CTL_FDBGEN_MASK) | ENET_MTL_DBG_CTL_FDBGEN(bEnable ? 1u : 0u);
}

/**
 * @brief  Get MTL debug status register value

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t debug status
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetDebugStatus(const ENET_Type *const pEnet)
{
    return pEnet->MTL.DBG_STS;
}

/**
 * @brief  Get MTL remaining locations in the FIFO

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetFIFORemainingLocation(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_STS & ENET_MTL_DBG_STS_LOCR_MASK) >> ENET_MTL_DBG_STS_LOCR_SHIFT;
    return u32TmpVal;
}

/**
 * @brief  Get MTL transmit status available interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true transmit status available interrupt not detected
 * @return false transmit status available interrupt detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxStatusAvailableIntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_STS & ENET_MTL_DBG_STS_STSI_MASK) >> ENET_MTL_DBG_STS_STSI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Clear MTL transmit status available interrupt status

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearTxStatusAvailableIntStatus(ENET_Type *const pEnet)
{
    pEnet->MTL.DBG_STS = ENET_MTL_DBG_STS_STSI_MASK;
}

/**
 * @brief  Get MTL receive packet available interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true receive packet available interrupt not detected
 * @return false receive packet available interrupt detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxPacketAvailableIntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_STS & ENET_MTL_DBG_STS_PKTI_MASK) >> ENET_MTL_DBG_STS_PKTI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Clear MTL receive packet available interrupt status

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearRxPacketAvailableIntStatus(ENET_Type *const pEnet)
{
    pEnet->MTL.DBG_STS = ENET_MTL_DBG_STS_PKTI_MASK;
}

/**
 * @brief  Get the number of data bytes valid in the data register during Read operation

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_ByteEnableType
 */
LOCAL_INLINE ENET_MTL_ByteEnableType ENET_HWA_MTL_GetByteEnable(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_STS & ENET_MTL_DBG_STS_BYTEEN_MASK) >> ENET_MTL_DBG_STS_BYTEEN_SHIFT;
    return (ENET_MTL_ByteEnableType)u32TmpVal;
}

/**
 * @brief  Get the control or status information of the selected FIFO.

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_FIFOPacketStatusType
 */
LOCAL_INLINE ENET_MTL_FIFOPacketStatusType ENET_HWA_MTL_GetFIFOPacketState(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_STS & ENET_MTL_DBG_STS_PKTSTATE_MASK) >> ENET_MTL_DBG_STS_PKTSTATE_SHIFT;
    return (ENET_MTL_FIFOPacketStatusType)u32TmpVal;
}

/**
 * @brief  Get MTL FIFO busy status

 * @param [in] pEnet the base address of the ENET instance
 * @return true FIFO is busy
 * @return false FIFO is not busy
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetFIFOBusy(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.DBG_STS & ENET_MTL_DBG_STS_FIFOBUSY_MASK) >> ENET_MTL_DBG_STS_FIFOBUSY_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Get MTL FIFO debug data

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t FIFO debug data
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetFIFODebugData(const ENET_Type *const pEnet)
{
    return pEnet->MTL.FIFO_DEBUG_DATA;
}

/**
 * @brief  Set MTL FIFO debug data
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Data debug data to set
 */
LOCAL_INLINE void ENET_HWA_MTL_SetFIFODebugData(ENET_Type *const pEnet, uint32_t u32Data)
{
    pEnet->MTL.FIFO_DEBUG_DATA = u32Data;
}

/**
 * @brief  Get MTL interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t MTL interrupt status
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetIntStatus(const ENET_Type *const pEnet)
{
    return pEnet->MTL.INTERRUPT_STATUS;
}

/**
 * @brief  Get debug interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true Debug interrupt status detected
 * @return false Debug interrupt status not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetDebugIntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.INTERRUPT_STATUS & ENET_MTL_INTERRUPT_STATUS_DBGIS_MASK) >>
                         ENET_MTL_INTERRUPT_STATUS_DBGIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Get Queue 1 interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true Queue 1 interrupt status detected
 * @return false Queue 1 interrupt status not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetQueue1IntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.INTERRUPT_STATUS & ENET_MTL_INTERRUPT_STATUS_Q1IS_MASK) >>
                         ENET_MTL_INTERRUPT_STATUS_Q1IS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Get Queue 0 interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true Queue 0 interrupt status detected
 * @return false Queue 0 interrupt status not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetQueue0IntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.INTERRUPT_STATUS & ENET_MTL_INTERRUPT_STATUS_Q0IS_MASK) >>
                         ENET_MTL_INTERRUPT_STATUS_Q0IS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Get DA-based DMA channel selection enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true eQueue is enabled for DA-based DMA channel selection
 * @return false eQueue is disabled for DA-based DMA channel selection
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxDABasedDMAChannelSelectionEnFlag(const ENET_Type *const pEnet,
                                                                     ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.RXQ_DMA_MAP0 &
                          ((uint32_t)ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH_MASK <<
                           ((uint32_t)ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH_SHIFT +
                            ((uint32_t)ENET_MTL_RXQ_DMA_MAP0_Q1DDMACH_SHIFT - ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH_SHIFT) * (uint32_t)eQueue)));
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set DA-based DMA channel selection enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxDABasedDMAChannelSelectionEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                                     bool bEnable)
{
    pEnet->MTL.RXQ_DMA_MAP0 = (pEnet->MTL.RXQ_DMA_MAP0 &
                               ~(ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH_MASK <<
                                 (ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH_SHIFT +
                                  (ENET_MTL_RXQ_DMA_MAP0_Q1DDMACH_SHIFT - ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH_SHIFT) * (uint32_t)eQueue))) |
                              (ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH(bEnable ? 1u : 0u) <<
                               ((ENET_MTL_RXQ_DMA_MAP0_Q1DDMACH_SHIFT - ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH_SHIFT) * (uint32_t)eQueue));
}

/**
 * @brief  Get DMA channel mapped to eQueue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_DMA_ChannelType
 */
LOCAL_INLINE ENET_DMA_ChannelType ENET_HWA_MTL_GetRxDMAChannelMap(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.RXQ_DMA_MAP0 &
                          ((uint32_t)ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_MASK <<
                           ((uint32_t)ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT +
                            (uint32_t)(ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH_SHIFT - ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT) * (uint32_t)eQueue))) >>
                         ((uint32_t)ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT +
                          (uint32_t)(ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH_SHIFT - ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT) * (uint32_t)eQueue);
    return (ENET_DMA_ChannelType)u32TmpVal;
}

/**
 * @brief  Set DMA channel mapped to eQueue
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxDMAChannelMap(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                  ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->MTL.RXQ_DMA_MAP0 = (pEnet->MTL.RXQ_DMA_MAP0 &
                               ~(ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_MASK <<
                                 (ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT +
                                  (ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH_SHIFT - ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT) * (uint32_t)eQueue))) |
                              (ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH(eDMAChannel) <<
                               ((ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH_SHIFT - ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH_SHIFT) * (uint32_t)eQueue));
}

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief  Get Time Based Scheduling control register

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t Time Based Scheduling control
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetTBSCtrl(const ENET_Type *const pEnet)
{
    return pEnet->MTL.TBS_CTRL;
}

/**
 * @brief  Set Time Based Scheduling control register
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Ctrl control value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTBSCtrl(ENET_Type *const pEnet, uint32_t u32Ctrl)
{
    pEnet->MTL.TBS_CTRL = u32Ctrl;
}

/**
 * @brief  Get launch expiry offset

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t launch expiry offset
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetLaunchExpiryOffset(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.TBS_CTRL & ENET_MTL_TBS_CTRL_LEOS_MASK) >> ENET_MTL_TBS_CTRL_LEOS_SHIFT;
    return u32TmpVal;
}

/**
 * @brief  Set launch expiry offset
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32ExpiryOffset launch expiry offset value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetLaunchExpiryOffset(ENET_Type *const pEnet, uint32_t u32ExpiryOffset)
{
    pEnet->MTL.TBS_CTRL = (pEnet->MTL.TBS_CTRL & ~ENET_MTL_TBS_CTRL_LEOS_MASK) | ENET_MTL_TBS_CTRL_LEOS(u32ExpiryOffset);
}

/**
 * @brief  Get launch expiry offset enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true launch expiry offset is valid
 * @return false launch expiry offset is invalid
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetLaunchExpiryOffsetEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.TBS_CTRL & ENET_MTL_TBS_CTRL_LEOV_MASK) >> ENET_MTL_TBS_CTRL_LEOV_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief  Set launch expiry offset enable flag
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable launch expiry offset
 */
LOCAL_INLINE void ENET_HWA_MTL_SetLaunchExpiryOffsetEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.TBS_CTRL = (pEnet->MTL.TBS_CTRL & ~ENET_MTL_TBS_CTRL_LEOV_MASK) | ENET_MTL_TBS_CTRL_LEOV(bEnable ? 1u : 0u);
}

/**
 * @brief  Get enhancements to scheduled transmission control register value

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t EST control value
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetEstControl(const ENET_Type *const pEnet)
{
    return pEnet->MTL.EST_CONTROL;
}

/**
 * @brief  Set enhancements to scheduled transmission control register value
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32EstControl EST control value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstControl(ENET_Type *const pEnet, uint32_t u32EstControl)
{
    pEnet->MTL.EST_CONTROL = u32EstControl;
}

/**
 * @brief  Get enhancements to scheduled transmission PTP time offset

 * @param [in] pEnet the base address of the ENET instance
 * @return uint8_t PTP time offset
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetEstPtpTimeOffset(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_PTOV_MASK) >>
                         ENET_MTL_EST_CONTROL_PTOV_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief  Set enhancements to scheduled transmission PTP time offset
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8Value PTP time offset
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstPtpTimeOffset(ENET_Type *const pEnet, uint8_t u8Value)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_PTOV_MASK) |
                             ENET_MTL_EST_CONTROL_PTOV(u8Value);
}

/**
 * @brief  Get enhancements to scheduled transmission current time offset

 * @param [in] pEnet the base address of the ENET instance
 * @return uint16_t current time offset
 */
LOCAL_INLINE uint16_t ENET_HWA_MTL_GetEstCurrentTimeOffset(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_CTOV_MASK) >>
                         ENET_MTL_EST_CONTROL_CTOV_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief  Set enhancements to scheduled transmission current time offset
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u16Value current time offset
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstCurrentTimeOffset(ENET_Type *const pEnet, uint16_t u16Value)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_CTOV_MASK) |
                             ENET_MTL_EST_CONTROL_CTOV(u16Value);
}

/**
 * @brief  Get EST time interval left shift amount

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_GCLIntervalMultipleType
 */
LOCAL_INLINE ENET_MTL_GCLIntervalMultipleType ENET_HWA_MTL_GetEstTimeIntervalLeftShift(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_TILS_MASK) >>
                         ENET_MTL_EST_CONTROL_TILS_SHIFT;
    return (ENET_MTL_GCLIntervalMultipleType)u32TmpVal;
}

/**
 * @brief  Set EST time interval left shift amount
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eValue left shift amount
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstTimeIntervalLeftShift(ENET_Type *const pEnet, ENET_MTL_GCLIntervalMultipleType eValue)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_TILS_MASK) |
                             ENET_MTL_EST_CONTROL_TILS(eValue);
}

/**
 * @brief  Get the loop count to report scheduling error

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_ScheduleErrorLoopCountType
 */
LOCAL_INLINE ENET_MTL_ScheduleErrorLoopCountType ENET_HWA_MTL_GetEstScheduleErrorLoopCount(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_LCSE_MASK) >>
                         ENET_MTL_EST_CONTROL_LCSE_SHIFT;
    return (ENET_MTL_ScheduleErrorLoopCountType)u32TmpVal;
}

/**
 * @brief  Set the loop count to report scheduling error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eValue loop count
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstScheduleErrorLoopCount(ENET_Type *const pEnet, ENET_MTL_ScheduleErrorLoopCountType eValue)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_LCSE_MASK) |
                             ENET_MTL_EST_CONTROL_LCSE(eValue);
}

/**
 * @brief  Drop frames causing scheduling error

 * @param [in] pEnet the base address of the ENET instance
 * @return true Drop frames causing scheduling error
 * @return false Do not drop frames causing scheduling error
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetDropSchedulingErrorFramesEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_DFBS_MASK) >>
                         ENET_MTL_EST_CONTROL_DFBS_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief  Enable dropping frames causing scheduling error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetDropSchedulingErrorFramesEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_DFBS_MASK) |
                             ENET_MTL_EST_CONTROL_DFBS(bEnable ? 1u : 0u);
}

/**
 * @brief  Drop frames during frame size error

 * @param [in] pEnet the base address of the ENET instance
 * @return true Do not drop frames during frame size error
 * @return false Drop frames during frame size error
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetDropFrameSizeErrorFramesDisableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_DDBF_MASK) >>
                         ENET_MTL_EST_CONTROL_DDBF_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief  Enable dropping frames causing scheduling error
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bDisable disable or enable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetDropFrameSizeErrorFramesDisableFlag(ENET_Type *const pEnet, bool bDisable)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_DDBF_MASK) |
                             ENET_MTL_EST_CONTROL_DDBF(bDisable ? 1u : 0u);
}

/**
 * @brief  Get switch gate control list enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true switch gate control list is enabled
 * @return false switch gate control list is diabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetSwitchGateControlListEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_SSWL_MASK) >>
                         ENET_MTL_EST_CONTROL_SSWL_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief Switch gate control list
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetSwitchGateControlListEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_SSWL_MASK) |
                             ENET_MTL_EST_CONTROL_SSWL(bEnable ? 1u : 0u);
}

/**
 * @brief  Get EST enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true EST is enabled
 * @return false EST is diabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetEstEnableFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_CONTROL & ENET_MTL_EST_CONTROL_EEST_MASK) >>
                         ENET_MTL_EST_CONTROL_EEST_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief Enable EST
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstEnableFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_CONTROL &
                              ~ENET_MTL_EST_CONTROL_EEST_MASK) |
                             ENET_MTL_EST_CONTROL_EEST(bEnable ? 1u : 0u);
}

/**
 * @brief  Get EST overhead bytes value

 * @param [in] pEnet the base address of the ENET instance
 * @return uint8_t EST overhead bytes value
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetEstOverheadBytes(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_EXT_CONTROL & ENET_MTL_EST_EXT_CONTROL_OVHD_MASK) >>
                         ENET_MTL_EST_EXT_CONTROL_OVHD_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief  Set EST overhead bytes value
 *
 * @param[in] pEnet the base address of the ENET instance
 * @param[in] u8Value EST overhead bytes value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstOverheadBytes(ENET_Type *const pEnet, uint8_t u8Value)
{
    pEnet->MTL.EST_CONTROL = (pEnet->MTL.EST_EXT_CONTROL &
                              ~ENET_MTL_EST_EXT_CONTROL_OVHD_MASK) |
                             ENET_MTL_EST_EXT_CONTROL_OVHD(u8Value);
}

/**
 * @brief  Get EST status register value

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t EST status register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetEstStatus(const ENET_Type *const pEnet)
{
    return pEnet->MTL.EST_STATUS;
}

/**
 * @brief  Get current GCL slot number

 * @param [in] pEnet the base address of the ENET instance
 * @return uint8_t current GCL slot number
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetCurrentGCLSlotNumber(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_CGSN_MASK) >>
                         ENET_MTL_EST_STATUS_CGSN_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief  Get BTR error loop count

 * @param [in] pEnet the base address of the ENET instance
 * @return uint8_t BTR error loop count
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetBTRErrorLoopCount(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_BTRL_MASK) >>
                         ENET_MTL_EST_STATUS_BTRL_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief  Get the gate control list owned by software

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_GateControlListType
 */
LOCAL_INLINE ENET_MTL_GateControlListType ENET_HWA_MTL_GetSoftwareOwnedList(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_SWOL_MASK) >>
                         ENET_MTL_EST_STATUS_SWOL_SHIFT;
    return (ENET_MTL_GateControlListType)u32TmpVal;
}

/**
 * @brief  Get constant gate control error

 * @param [in] pEnet the base address of the ENET instance
 * @return true constant gate control error detected
 * @return false constant gate control error not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetConstantGateControlErrorFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_CGCE_MASK) >>
                         ENET_MTL_EST_STATUS_CGCE_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief  Clear constant gate control error flag

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearConstantGateControlErrorFlag(ENET_Type *const pEnet)
{
    pEnet->MTL.EST_STATUS = pEnet->MTL.EST_STATUS | ENET_MTL_EST_STATUS_CGCE_MASK;
}

/**
 * @brief  Get Head-Of-Line blocking due to scheduling

 * @param [in] pEnet the base address of the ENET instance
 * @return true Head-Of-Line blocking due to scheduling detected
 * @return false Head-Of-Line blocking due to scheduling not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetHeadOfLineBlockingDueToSchedulingFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_HLBS_MASK) >>
                         ENET_MTL_EST_STATUS_HLBS_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief  Get Head-Of-Line blocking due to frame size

 * @param [in] pEnet the base address of the ENET instance
 * @return true Head-Of-Line blocking due to frame size detected
 * @return false Head-Of-Line blocking due to frame size not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetHeadOfLineBlockingDueToFrameSizeFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_HLBF_MASK) >>
                         ENET_MTL_EST_STATUS_HLBF_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief  Get BTR error flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true BTR error detected
 * @return false BTR error not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetBTRErrorFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_BTRE_MASK) >>
                         ENET_MTL_EST_STATUS_BTRE_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief  Clear BTR error flag

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearBTRErrorFlag(ENET_Type *const pEnet)
{
    pEnet->MTL.EST_STATUS = pEnet->MTL.EST_STATUS | ENET_MTL_EST_STATUS_BTRE_MASK;
}

/**
 * @brief  Get switch gate control list complete status

 * @param [in] pEnet the base address of the ENET instance
 * @return true Switching to S/W owned list completed
 * @return false Switching to S/W owned list not completed
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetSwitchGateControlListCompleteFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_STATUS & ENET_MTL_EST_STATUS_SWLC_MASK) >>
                         ENET_MTL_EST_STATUS_SWLC_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief  Clear switch gate control list complete status

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearSwitchGateControlListCompleteFlag(ENET_Type *const pEnet)
{
    pEnet->MTL.EST_STATUS = pEnet->MTL.EST_STATUS | ENET_MTL_EST_STATUS_SWLC_MASK;
}

/**
 * @brief Get the One Hot encoded queue numbers that are having the scheduling related error

 * @param [in] pEnet the base address of the ENET instance
 * @return true queue 1 caused scheduling error
 * @return false queue 0 caused scheduling error
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetScheduleErrorQueueNumber(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_SCH_ERROR & ENET_MTL_EST_SCH_ERROR_SEQN_MASK) >>
                         ENET_MTL_EST_SCH_ERROR_SEQN_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief Clear the value of schedule error queue number register

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearScheduleErrorQueueNumber(ENET_Type *const pEnet)
{
    pEnet->MTL.EST_SCH_ERROR = pEnet->MTL.EST_SCH_ERROR | ENET_MTL_EST_SCH_ERROR_SEQN_MASK;
}

/**
 * @brief Get the One Hot encoded queue numbers that are having the frame size error

 * @param [in] pEnet the base address of the ENET instance
 * @return true queue 1 caused frame size error
 * @return false queue 0 caused frame size error
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetFrameSizeErrorQueueNumber(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_FRM_SIZE_ERROR & ENET_MTL_EST_FRM_SIZE_ERROR_FEQN_MASK) >>
                         ENET_MTL_EST_FRM_SIZE_ERROR_FEQN_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief Clear the value of frame size error queue number register

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearFrameSizeErrorQueueNumber(ENET_Type *const pEnet)
{
    pEnet->MTL.EST_FRM_SIZE_ERROR = pEnet->MTL.EST_FRM_SIZE_ERROR | ENET_MTL_EST_FRM_SIZE_ERROR_FEQN_MASK;
}

/**
 * @brief Get the queue numbers that are having the first frame size error

 * @param [in] pEnet the base address of the ENET instance
 * @return true queue 1 caused the first frame size error
 * @return false queue 0 caused the first frame size error
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetFrameSizeErrorFirstQueueNumber(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_FRM_SIZE_CAPTURE & ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFQ_MASK) >>
                         ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFQ_SHIFT;
    return (bool)u32TmpVal;
}

/**
 * @brief Get the frame size of the first frame size error

 * @param [in] pEnet the base address of the ENET instance
 * @return uint16_t frame size of the first frame size error
 */
LOCAL_INLINE uint16_t ENET_HWA_MTL_GetFrameSizeErrorFirstFrameSize(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_FRM_SIZE_CAPTURE & ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFS_MASK) >>
                         ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFS_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Get enable flag of constant gate control error interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @return true CGCE interrupt is enabled
 * @return false CGCE interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetConstantGateControlErrorInterruptEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_INTR_ENABLE & ENET_MTL_EST_INTR_ENABLE_CGCE_MASK) >>
                         ENET_MTL_EST_INTR_ENABLE_CGCE_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set enable flag of constant gate control error interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetConstantGateControlErrorInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_INTR_ENABLE = (pEnet->MTL.EST_INTR_ENABLE & ~ENET_MTL_EST_INTR_ENABLE_CGCE_MASK) |
                                 ENET_MTL_EST_INTR_ENABLE_CGCE(bEnable ? 1u : 0u);
}

/**
 * @brief Get enable flag of head of line blocking due to scheduling interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @return true HLBS interrupt is enabled
 * @return false HLBS interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetHeadofLineBlockingDueToSchedulingInterruptEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_INTR_ENABLE & ENET_MTL_EST_INTR_ENABLE_IEHS_MASK) >>
                         ENET_MTL_EST_INTR_ENABLE_IEHS_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set enable flag of head of line blocking due to scheduling interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetHeadofLineBlockingDueToSchedulingInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_INTR_ENABLE = (pEnet->MTL.EST_INTR_ENABLE & ~ENET_MTL_EST_INTR_ENABLE_IEHS_MASK) |
                                 ENET_MTL_EST_INTR_ENABLE_IEHS(bEnable ? 1u : 0u);
}

/**
 * @brief Get enable flag of head of line blocking due to frame size interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @return true HLBF interrupt is enabled
 * @return false HLBF interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetHeadofLineBlockingDueToFrameSizeInterruptEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_INTR_ENABLE & ENET_MTL_EST_INTR_ENABLE_IEHF_MASK) >>
                         ENET_MTL_EST_INTR_ENABLE_IEHF_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set enable flag of head of line blocking due to frame size interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetHeadofLineBlockingDueToFrameSizeInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_INTR_ENABLE = (pEnet->MTL.EST_INTR_ENABLE & ~ENET_MTL_EST_INTR_ENABLE_IEHF_MASK) |
                                 ENET_MTL_EST_INTR_ENABLE_IEHF(bEnable ? 1u : 0u);
}

/**
 * @brief Get enable flag of base time register error interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @return true  BTR Error interrupt is enabled
 * @return false  BTR Error interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetBaseTimeRegisterErrorInterruptEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_INTR_ENABLE & ENET_MTL_EST_INTR_ENABLE_IEBE_MASK) >>
                         ENET_MTL_EST_INTR_ENABLE_IEBE_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set enable flag of base time register error interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetBaseTimeRegisterErrorInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_INTR_ENABLE = (pEnet->MTL.EST_INTR_ENABLE & ~ENET_MTL_EST_INTR_ENABLE_IEBE_MASK) |
                                 ENET_MTL_EST_INTR_ENABLE_IEBE(bEnable ? 1u : 0u);
}

/**
 * @brief Get enable flag of switch GCL completion interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @return true  BTR Error interrupt is enabled
 * @return false  BTR Error interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetSwitchListInterruptEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_INTR_ENABLE & ENET_MTL_EST_INTR_ENABLE_IECC_MASK) >>
                         ENET_MTL_EST_INTR_ENABLE_IECC_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set enable flag of base time switch GCL completion interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetSwitchListInterruptEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_INTR_ENABLE = (pEnet->MTL.EST_INTR_ENABLE & ~ENET_MTL_EST_INTR_ENABLE_IECC_MASK) |
                                 ENET_MTL_EST_INTR_ENABLE_IECC(bEnable ? 1u : 0u);
}

/**
 * @brief Get the mode of EST ECC inject error control for EST memory

 * @param [in] pEnet the base address of the ENET instance
 * @return true  inject 2 bit errors
 * @return false inject 1 bit error
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetEstEccInjectErrorControl(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_ESTEIEC_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_ESTEIEC_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set the mode of EST ECC inject error control for EST memory

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable true inject 2 bit errors,false inject 1 bit error
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstEccInjectErrorControl(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_ESTEIEC_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_ESTEIEC(bEnable ? 1u : 0u);
}

/**
 * @brief Get enable flag of EST ECC address error injection

 * @param [in] pEnet the base address of the ENET instance
 * @return true  inject 2 bit errors
 * @return false inject 1 bit error
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetEstEccInjectAddressErrorEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_ESTEIAEE_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_ESTEIAEE_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set enable flag of EST ECC address error injection

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstEccInjectAddressErrorEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_ESTEIAEE_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_ESTEIAEE(bEnable ? 1u : 0u);
}

/**
 * @brief Get enable flag of EST ECC error injection

 * @param [in] pEnet the base address of the ENET instance
 * @return true  EST ECC inject error is enabled
 * @return false EST ECC inject error is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetEstEccInjectErrorEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_ESTEIEE_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_ESTEIEE_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set enable flag of EST ECC error injection

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstEccInjectErrorEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_ESTEIEE_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_ESTEIEE(bEnable ? 1u : 0u);
}

/**
 * @brief Get GCL address or GCL related registers address depend on GCRR bit

 * @param [in] pEnet the base address of the ENET instance
 * @return uint8_t GCL address or GCL related registers address
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetEstGateControlListAddress(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_ADDR_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_ADDR_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set GCL address or GCL related registers address depend on GCRR bit

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eAddress GCL address or GCL related registers address
 */
LOCAL_INLINE void ENET_HWA_MTL_SetEstGateControlListAddress(ENET_Type *const pEnet, uint8_t eAddress)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_ADDR_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_ADDR(eAddress);
}

/**
 * @brief Get GCL debug mode bank selected

 * @param [in] pEnet the base address of the ENET instance
 * @return uint8_t debug mode bank
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetGclDebugModeBankSelect(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_DBGB_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_DBGB_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set GCL debug mode bank

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eBank debug mode bank
 */
LOCAL_INLINE void ENET_HWA_MTL_SetGclDebugModeBankSelect(ENET_Type *const pEnet, uint8_t eBank)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_DBGB_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_DBGB(eBank);
}

/**
 * @brief Get GCL debug mode enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true  debug mode is enabled
 * @return false debug mode is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetGclDebugModeEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_DBGM_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_DBGM_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set GCL debug mode enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetGclDebugModeEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_DBGM_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_DBGM(bEnable ? 1u : 0u);
}

/**
 * @brief Get gate control releated registers enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true  ADDR fields is used for gate control releated registers
 * @return false ADDR fields is used for gate control list address
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetGateControlReleatedRegistersEnFlag(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_GCRR_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_GCRR_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Set gate control releated registers enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetGateControlReleatedRegistersEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_GCRR_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_GCRR(bEnable ? 1u : 0u);
}

/**
 * @brief Get GCL operation mode (read or write)

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_MTL_GclOperationType (read or write)
 */
LOCAL_INLINE ENET_MTL_GclOperationType ENET_HWA_MTL_GetGclOperation(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_R1W0_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_R1W0_SHIFT;
    return (ENET_MTL_GclOperationType)u32TmpVal;
}

/**
 * @brief Set GCL operation mode (read or write)

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eOperation (read or write)
 */
LOCAL_INLINE void ENET_HWA_MTL_SetGclOperation(ENET_Type *const pEnet, ENET_MTL_GclOperationType eOperation)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_R1W0_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_R1W0(eOperation);
}

/**
 * @brief Get GCL operation busy status

 * @param [in] pEnet the base address of the ENET instance
 * @return true  Start Read/Write operation is enabled,status is busy
 * @return false Start Read/Write operation is disabled,status is idle
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetGclOperationBusyState(ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->MTL.EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO_MASK) >>
                         ENET_MTL_EST_GCL_CONTROL_SRWO_SHIFT;
    return u32TmpVal != 0u ? true : false;
}

/**
 * @brief Start GCL Read/Write operation

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetGclOperationStartFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->MTL.EST_GCL_CONTROL = (pEnet->MTL.EST_GCL_CONTROL & ~ENET_MTL_EST_GCL_CONTROL_SRWO_MASK) |
                                 ENET_MTL_EST_GCL_CONTROL_SRWO(bEnable ? 1u : 0u);
}

/**
 * @brief Get GCL data

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t  GCL data value
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetGclData(ENET_Type *const pEnet)
{
    return pEnet->MTL.EST_GCL_DATA;
}

/**
 * @brief Set GCL data register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eData data to set
 */
LOCAL_INLINE void ENET_HWA_MTL_SetGclData(ENET_Type *const pEnet, uint32_t eData)
{
    pEnet->MTL.EST_GCL_DATA = eData;
}

/**
 * @brief  Set the corresponding Queue classified as express or preemptable.
 * @details Set the Classification of Queues.A bit indicates a queue, when '1' indicates the
 *             corresponding Queue must be classified as preemptable, when '0' Queue is classified
 *             as express.
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u8value Preemption classification value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetPreemptionClassification(ENET_Type *const pEnet, uint8 u8value)
{
    pEnet->MTL.FPE_CTRL_STS = (pEnet->MTL.FPE_CTRL_STS & ~ENET_MTL_FPE_CTRL_STS_PEC_MASK) |
                              ENET_MTL_FPE_CTRL_STS_PEC(u8value);
}

/**
 * @brief  Set the maximum time in nanoseconds that can elapse between issuing a RELEASE to the MAC
 *            and the MAC being ready to resume transmission of preemptable frames.
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u16value Release Advance time value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetPreemptionReleaseAdvance(ENET_Type *const pEnet, uint16 u16value)
{
    pEnet->MTL.FPE_ADVANCE = (pEnet->MTL.FPE_ADVANCE & ~ENET_MTL_FPE_ADVANCE_RADV_MASK) |
                             ENET_MTL_FPE_ADVANCE_RADV(u16value);
}

/**
 * @brief  Set the maximum time in nanoseconds that can elapse between issuing a HOLD to the MAC
 *            and the MAC ceasing to transmit any preemptable frame.
 *
 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u16value Hold Advance time value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetPreemptionHoldAdvance(ENET_Type *const pEnet, uint16 u16value)
{
    pEnet->MTL.FPE_ADVANCE = (pEnet->MTL.FPE_ADVANCE & ~ENET_MTL_FPE_ADVANCE_HADV_MASK) |
                             ENET_MTL_FPE_ADVANCE_HADV(u16value);
}
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief Get MTL queue Tx operation mode register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t  MTL queue Tx operation mode
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetTxOperationMode(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    return pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE;
}

/**
 * @brief Set MTL queue Tx operation mode register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32OpMode  MTL queue Tx operation mode
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxOperationMode(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, uint32_t u32OpMode)
{
    pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE = u32OpMode;
}

/**
 * @brief Get MTL transmit queue size

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint8_t  queue size in blocks of 256 bytes
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetTxQueueSize(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE & ENET_MTL_TXQ0_OPERATION_MODE_TQS_MASK) >>
                         ENET_MTL_TXQ0_OPERATION_MODE_TQS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set MTL transmit queue size

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u8QueueSize  queue size in blocks of 256 bytes,range(0~15)
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxQueueSize(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, uint8_t u8QueueSize)
{
    pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE &
                                                  ~ENET_MTL_TXQ0_OPERATION_MODE_TQS_MASK) |
                                                 ENET_MTL_TXQ0_OPERATION_MODE_TQS(u8QueueSize);
}

/**
 * @brief Get the threshold level of the MTL Tx Queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_TxThresholdType_t  threshold level
 */
LOCAL_INLINE ENET_MTL_TxThresholdType ENET_HWA_MTL_GetTxThreshold(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE;
    uint32_t u32Threshold = (u32TmpVal & ENET_MTL_TXQ0_OPERATION_MODE_TTC_MASK) >> ENET_MTL_TXQ0_OPERATION_MODE_TTC_SHIFT;
    return ((u32TmpVal & ENET_MTL_TXQ0_OPERATION_MODE_TSF_MASK) == ENET_MTL_TXQ0_OPERATION_MODE_TSF_MASK) ?
           ENET_MTL_TX_STORE_FORWARD : (ENET_MTL_TxThresholdType)u32Threshold;
}

/**
 * @brief Set the threshold level of the MTL Tx Queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] eThreshold  threshold level
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxThreshold(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                              ENET_MTL_TxThresholdType eThreshold)
{
    pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE &
                                                  ~(ENET_MTL_TXQ0_OPERATION_MODE_TTC_MASK | ENET_MTL_TXQ0_OPERATION_MODE_TSF_MASK)) |
                                                 (ENET_MTL_TXQ0_OPERATION_MODE_TTC(eThreshold) |
                                                  ENET_MTL_TXQ0_OPERATION_MODE_TSF((uint32_t)eThreshold >> ENET_MTL_TXQ0_OPERATION_MODE_TTC_WIDTH));
}

/**
 * @brief Get the transmit queue enable mode

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_QueueEnableType  queue enable mode
 */
LOCAL_INLINE ENET_MTL_QueueEnableType ENET_HWA_MTL_GetTxQueueEnStatus(const ENET_Type *const pEnet,
                                                                      ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE & ENET_MTL_TXQ0_OPERATION_MODE_TXQEN_MASK) >>
                         ENET_MTL_TXQ0_OPERATION_MODE_TXQEN_SHIFT;
    return (ENET_MTL_QueueEnableType)u32TmpVal;
}

/**
 * @brief Set the transmit queue enable mode

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] eEnable  queue enable mode
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxQueueEnStatus(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                  ENET_MTL_QueueEnableType eEnable)
{
    pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE &
                                                  ~ENET_MTL_TXQ0_OPERATION_MODE_TXQEN_MASK) |
                                                 ENET_MTL_TXQ0_OPERATION_MODE_TXQEN(eEnable);
}

/**
 * @brief Get transmit queue store and forward enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true  store and forward is enabled
 * @return false  store and forward is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxStoreForwardModeEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE & ENET_MTL_TXQ0_OPERATION_MODE_TSF_MASK) >>
                         ENET_MTL_TXQ0_OPERATION_MODE_TSF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set transmit queue store and forward enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxStoreForwardModeEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                           bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE &
                                                  ~ENET_MTL_TXQ0_OPERATION_MODE_TSF_MASK) |
                                                 ENET_MTL_TXQ0_OPERATION_MODE_TSF(bEnable ? 1u : 0u);
}

/**
 * @brief Get transmit queue flush state

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true  flush transmit queue is enabled
 * @return false flush transmit queue is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxFlushState(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE & ENET_MTL_TXQ0_OPERATION_MODE_FTQ_MASK) >>
                         ENET_MTL_TXQ0_OPERATION_MODE_FTQ_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Flush transmit queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 */
LOCAL_INLINE void ENET_HWA_MTL_FlushTxQueue(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MTL.QUEUE[eQueue].TX_OPERATION_MODE |= ENET_MTL_TXQ0_OPERATION_MODE_FTQ_MASK;
}

/**
 * @brief Get the underflow counter register of transmit queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [out] pPacketCnt packet counter value
 * @retval true  Underflow packet counter overflow and rollover happened
 * @retval false Underflow packet counter is not overflowed
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxUnderflowPacketCount(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                         uint16_t *pPacketCnt)
{
    bool bRet;
    uint32_t u32TmpVal = pEnet->MTL.QUEUE[eQueue].TX_UNDERFLOW;
    *pPacketCnt = (uint16_t)(u32TmpVal & ENET_MTL_TXQ0_UNDERFLOW_UFFRMCNT_MASK) >> ENET_MTL_TXQ0_UNDERFLOW_UFFRMCNT_SHIFT;
    bRet = (((u32TmpVal & ENET_MTL_TXQ0_UNDERFLOW_UFCNTOVF_MASK) >> ENET_MTL_TXQ0_UNDERFLOW_UFCNTOVF_SHIFT) != 0u) ?
           true : false;
    return bRet;
}

/**
 * @brief Get transmit queue debug status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t  transmit queue debug status register value
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetTxDebugStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    return pEnet->MTL.QUEUE[eQueue].TX_DEBUG;
}

/**
 * @brief Get the current number of status in the transmit Status FIFO of this queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint8_t number of status
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetTxStatusWordCount(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_DEBUG & ENET_MTL_TXQ0_DEBUG_STXSTSF_MASK) >>
                         ENET_MTL_TXQ0_DEBUG_STXSTSF_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get the current number of packets in the transmit queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint8_t number of packets
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetTxPacketCount(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_DEBUG & ENET_MTL_TXQ0_DEBUG_PTXQ_MASK) >>
                         ENET_MTL_TXQ0_DEBUG_PTXQ_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get the full flag of transmit Status FIFO

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true  transmit Status FIFO is full
 * @return false transmit Status FIFO is not full
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxStatusFIFOFullStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_DEBUG & ENET_MTL_TXQ0_DEBUG_TXSTSFSTS_MASK) >>
                         ENET_MTL_TXQ0_DEBUG_TXSTSFSTS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the not empty flag of transmit queue data

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true  transmit queue data is empty
 * @return false transmit queue data is not empty
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxQueueNotEmptyStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_DEBUG & ENET_MTL_TXQ0_DEBUG_TXQSTS_MASK) >>
                         ENET_MTL_TXQ0_DEBUG_TXQSTS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get the transmit queue write controller status,indicates that the MTL Tx Queue Write
          controller is active, and it is transferring the data to the transmit queue.

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_WriteControllerStatusType
 */
LOCAL_INLINE ENET_MTL_WriteControllerStatusType ENET_HWA_MTL_GetTxQueueWriteControllerStatus(const ENET_Type *const pEnet,
        ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_DEBUG & ENET_MTL_TXQ0_DEBUG_TWCSTS_MASK) >>
                         ENET_MTL_TXQ0_DEBUG_TWCSTS_SHIFT;
    return (ENET_MTL_WriteControllerStatusType)u32TmpVal;
}

/**
 * @brief Get the transmit queue read controller status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_ReadControllerStatusType
 */
LOCAL_INLINE ENET_MTL_ReadControllerStatusType ENET_HWA_MTL_GetTxQueueReadControllerStatus(const ENET_Type *const pEnet,
        ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_DEBUG & ENET_MTL_TXQ0_DEBUG_TRCSTS_MASK) >>
                         ENET_MTL_TXQ0_DEBUG_TRCSTS_SHIFT;
    return (ENET_MTL_ReadControllerStatusType)u32TmpVal;
}

/**
 * @brief Get the transmit queue paused status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true  transmit queue is paused
 * @return false transmit queue is not paused
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxQueuePausedStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_DEBUG & ENET_MTL_TXQ0_DEBUG_TXQPAUSED_MASK) >>
                         ENET_MTL_TXQ0_DEBUG_TXQPAUSED_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set AV algorithm for strict priority or credit based shaper.

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable 1U use credit based shaper or 0U use strict priority.
 */
LOCAL_INLINE void ENET_HWA_MTL_SetAVAlgorithmCBSEnFlag(ENET_Type *const pEnet,
                                                       ENET_MTL_QueueType eQueue, uint8 bEnable)
{
    pEnet->MTL.QUEUE[eQueue].TX_ETS_CONTROL = (pEnet->MTL.QUEUE[eQueue].TX_ETS_CONTROL &
                                               ~ENET_MTL_TXQ1_ETS_CONTROL_AVALG_MASK) |
                                              ENET_MTL_TXQ1_ETS_CONTROL_AVALG(bEnable);
}

/**
 * @brief Get the average bits per slot,when the DCB operation is enabled for the queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t average bits per slot
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetSlotAverageBits(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_ETS_STATUS & ENET_MTL_TXQ0_ETS_STATUS_ABS_MASK) >>
                         ENET_MTL_TXQ0_ETS_STATUS_ABS_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Get the quantum or weights for transmit algorithm (DWRR WRR WFQ)

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t quantum or weights
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetTxQueueQuantumOrWeight(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].TX_QUANTUM_WEIGHT & ENET_MTL_TXQ0_QUANTUM_WEIGHT_ISCQW_MASK) >>
                         ENET_MTL_TXQ0_QUANTUM_WEIGHT_ISCQW_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Set the quantum or weights for transmit algorithm (DWRR WRR WFQ)

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32QuantumWeight quantum or weights
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxQueueQuantumOrWeight(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                         uint32_t u32QuantumWeight)
{
    pEnet->MTL.QUEUE[eQueue].TX_QUANTUM_WEIGHT = ENET_MTL_TXQ0_QUANTUM_WEIGHT_ISCQW(u32QuantumWeight);
}

/**
 * @brief Set the sendSlope credit value required for the credit-based shaper algorithm for the
 *           Queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32SendSlopeCredit sendSlope credit credit based shaper.
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxQueueSendSlopeCredit(ENET_Type *const pEnet,
                                            ENET_MTL_QueueType eQueue,  uint32 u32SendSlopeCredit)
{
    pEnet->MTL.QUEUE[eQueue].TX_SEND_SLOPE_CREDIT =
                ENET_MTL_TXQ1_SEND_SLOPE_CREDIT_SSC(u32SendSlopeCredit);
}

/**
 * @brief Set hiCredit value required for the credit-based shaper algorithm for the Queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32hiCredit hiCredit credit based shaper.
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxQueueHiCredit(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                  uint32 u32hiCredit)
{
    pEnet->MTL.QUEUE[eQueue].TX_HICREDIT = ENET_MTL_TXQ1_HICREDIT_HC(u32hiCredit);
}

/**
 * @brief Set the loCredit value required for the credit-based shaper algorithm for the Queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32LoCredit loCredit credit based shaper.
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxQueueLoCredit(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                  uint32 u32LoCredit)
{
    pEnet->MTL.QUEUE[eQueue].TX_LOCREDIT = ENET_MTL_TXQ1_LOCREDIT_LC(u32LoCredit);
}

/**
 * @brief Get the interrupt enable and status for the queue interrupts

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t interrupt enable and status
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetInterruptCtrlStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    return pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS;
}

/**
 * @brief Set the interrupt enable and status for the queue interrupts

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32CtrlStatus interrupt enable and status
 */
LOCAL_INLINE void ENET_HWA_MTL_SetInterruptCtrlStatus(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                      uint32_t u32CtrlStatus)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = u32CtrlStatus;
}

/**
 * @brief Clear all the interrupts of the MTL queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearAllIntStatus(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS;
}

/**
 * @brief Get receive queue overflow interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true receive queue overflow interrupt is enabled
 * @return false receive queue overflow interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxQueueOverflowIntEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                          ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE_MASK) >>
                         ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive queue overflow interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable enable receive queue overflow interrupt
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxQueueOverflowIntEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                           bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                                                         ~(ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK)) |
                                                        ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get receive queue overflow interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true receive queue overflow interrupt detected
 * @return false receive queue overflow interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxQueueOverflowIntStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                          ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK) >>
                         ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear receive queue overflow interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearRxQueueOverflowIntStatus(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                                                         ~(ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK)) |
                                                        ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK;
}

/**
 * @brief Get average bits per slot interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true average bits per slot interrupt is enabled
 * @return false average bits per slot interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetSlotAverageBitsIntEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                          ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIE_MASK) >>
                         ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set average bits per slot interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable enable average bits per slot interrupt
 */
LOCAL_INLINE void ENET_HWA_MTL_SetSlotAverageBitsIntEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                           bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                                                         ~(ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIE_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK)) |
                                                        ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get transmit queue underflow interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @retval true transmit queue underflow interrupt is enabled
 * @retval false transmit queue underflow interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxQueueUnderflowIntEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                          ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE_MASK) >>
                         ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set transmit queue underflow interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable enable transmit queue underflow interrupt
 */
LOCAL_INLINE void ENET_HWA_MTL_SetTxQueueUnderflowIntEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                            bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                                                         ~(ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK)) |
                                                        ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE(bEnable ? 1u : 0u);
}

/**
 * @brief Get average bits per slot interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true average bits per slot interrupt detected
 * @return false average bits per slot interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetSlotAverageBitsIntStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                          ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK) >>
                         ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear average bits per slot interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearSlotAverageBitsIntStatus(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                                                         ~(ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK)) |
                                                        ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK;
}

/**
 * @brief Get transmit queue underflow interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true transmit queue underflow interrupt detected
 * @return false transmit queue underflow interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetTxQueueUnderflowIntStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                          ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK) >>
                         ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear transmit queue underflow interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 */
LOCAL_INLINE void ENET_HWA_MTL_ClearTxQueueUnderflowIntStatus(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS = (pEnet->MTL.QUEUE[eQueue].INTERRUPT_CONTROL_STATUS &
                                                         ~(ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK |
                                                           ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK)) |
                                                        ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK;
}

/**
 * @brief Get receive operation mode of the queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t receive operation mode
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetRxOperationMode(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    return pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE;
}

/**
 * @brief Set receive operation mode of the queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32OpMode receive operation mode
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxOperationMode(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, uint32_t u32OpMode)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = u32OpMode;
}

/**
 * @brief Get receive queue size

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint8_t receive queues size in blocks of 256 bytes
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetRxQueueSize(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_RQS_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_RQS_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set receive queue size

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u8QueueSize receive queues size in blocks of 256 bytes, range(0~15)
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxQueueSize(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, uint8_t u8QueueSize)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~ENET_MTL_RXQ0_OPERATION_MODE_RQS_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_RQS(u8QueueSize);
}

/**
 * @brief Get the threshold of receive queue at which the flow control is deactivated

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_RxFlowCtrlThresholdType flow control deactivating threshold
 */
LOCAL_INLINE ENET_MTL_RxFlowCtrlThresholdType ENET_HWA_MTL_GetRxDeactivateFlowCtrlThres(const ENET_Type *const pEnet,
        ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_RFD_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_RFD_SHIFT;
    return (ENET_MTL_RxFlowCtrlThresholdType)u32TmpVal;
}

/**
 * @brief Set the threshold of receive queue at which the flow control is deactivated

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] eThreshold flow control deactivating threshold
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxDeactivateFlowCtrlThres(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                            ENET_MTL_RxFlowCtrlThresholdType eThreshold)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~ENET_MTL_RXQ0_OPERATION_MODE_RFD_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_RFD(eThreshold);
}

/**
 * @brief Get the threshold of receive queue at which the flow control is activated

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_RxFlowCtrlThresholdType flow control activating threshold
 */
LOCAL_INLINE ENET_MTL_RxFlowCtrlThresholdType ENET_HWA_MTL_GetRxActivateFlowCtrlThres(const ENET_Type *const pEnet,
        ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_RFA_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_RFA_SHIFT;
    return (ENET_MTL_RxFlowCtrlThresholdType)u32TmpVal;
}

/**
 * @brief Set the threshold of receive queue at which the flow control is activated

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] eThreshold flow control activating threshold
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxActivateFlowCtrlThres(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                          ENET_MTL_RxFlowCtrlThresholdType eThreshold)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~ENET_MTL_RXQ0_OPERATION_MODE_RFA_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_RFA(eThreshold);
}

/**
 * @brief Get receive queue hardware flow control enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true receive queue hardware flow control is enabled
 * @return false receive queue hardware flow control is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxHwFlowCtrlEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_EHFC_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_EHFC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive queue hardware flow control enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable enable hardware flow control
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxHwFlowCtrlEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~ENET_MTL_RXQ0_OPERATION_MODE_EHFC_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_EHFC(bEnable ? 1u : 0u);
}

/**
 * @brief Get forwarding of TCP/IP checksum error packets enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true forward TCP/IP checksum error packets to application
 * @return false drop TCP/IP checksum error packets
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetForwardTCPChecksumErrorPacketEnFlag(const ENET_Type *const pEnet,
                                                                      ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set forwarding of TCP/IP checksum error packets enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable forward TCP/IP checksum error packets
 */
LOCAL_INLINE void ENET_HWA_MTL_SetForwardTCPChecksumErrorPacketEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                                      bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (uint32_t)(pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                            ~ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF(bEnable ? 1u : 0u);
}

/**
 * @brief Get receive queue store and forward enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true store and forward is enabled
 * @return false store and forward is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxStoreForwardModeEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_RSF_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_RSF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive queue store and forward enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxStoreForwardModeEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                           bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~ENET_MTL_RXQ0_OPERATION_MODE_RSF_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_RSF(bEnable ? 1u : 0u);
}

/**
 * @brief Get forward error packets enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true forward error packets to application
 * @return false drop error packets
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetForwardErrorPacketEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_FEP_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_FEP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set forward error packets enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetForwardErrorPacketEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~ENET_MTL_RXQ0_OPERATION_MODE_FEP_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_FEP(bEnable ? 1u : 0u);
}

/**
 * @brief Get forward undersized good packets enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true forward undersized good packets to application
 * @return false drop undersized good packets
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetForwardUndersizedPacketEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE & ENET_MTL_RXQ0_OPERATION_MODE_FUP_MASK) >>
                         ENET_MTL_RXQ0_OPERATION_MODE_FUP_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set forward undersized good packets enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetForwardUndersizedPacketEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                                bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~ENET_MTL_RXQ0_OPERATION_MODE_FUP_MASK) |
                                                 ENET_MTL_RXQ0_OPERATION_MODE_FUP(bEnable ? 1u : 0u);
}

/**
 * @brief Get the receive queue threshold control

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_RxThresholdType
 */
LOCAL_INLINE ENET_MTL_RxThresholdType ENET_HWA_MTL_GetRxThreshold(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE;
    uint32_t u32Thrshold = (u32TmpVal & ENET_MTL_RXQ0_OPERATION_MODE_RTC_MASK) >> ENET_MTL_RXQ0_OPERATION_MODE_RTC_SHIFT;
    return ((u32TmpVal & ENET_MTL_RXQ0_OPERATION_MODE_RSF_MASK) == ENET_MTL_RXQ0_OPERATION_MODE_RSF_MASK) ?
           ENET_MTL_RX_STORE_FORWARD : (ENET_MTL_RxThresholdType)u32Thrshold;
}

/**
 * @brief Set the receive queue threshold

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] eThreshold receive queue threshold
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxThreshold(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                              ENET_MTL_RxThresholdType eThreshold)
{
    pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE = (pEnet->MTL.QUEUE[eQueue].RX_OPERATION_MODE &
                                                  ~(ENET_MTL_RXQ0_OPERATION_MODE_RTC_MASK | ENET_MTL_RXQ0_OPERATION_MODE_RSF_MASK)) |
                                                 (ENET_MTL_RXQ0_OPERATION_MODE_RTC(eThreshold) |
                                                  ENET_MTL_RXQ0_OPERATION_MODE_RSF((uint32_t)eThreshold >> ENET_MTL_RXQ0_OPERATION_MODE_RTC_WIDTH));
}

/**
 * @brief Get the missed packet and overflow counters of the queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [out] pMissedPacketCntOverflowFlag    missed packet counter overflow detected
 * @param [out] pMissedPacketCnt                missed pPacket counter
 * @param [out] pOverflowPacketCntOverflowFlag  overflow packet counter overflow detected
 * @param [out] pOverflowPacketCnt overflow     packet counter
 */
LOCAL_INLINE void ENET_HWA_MTL_GetRxMissedPacketOverflowCount(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                              bool *pMissedPacketCntOverflowFlag, uint16_t *pMissedPacketCnt,
                                                              bool *pOverflowPacketCntOverflowFlag, uint16_t *pOverflowPacketCnt)
{
    uint32_t u32TmpVal = pEnet->MTL.QUEUE[eQueue].RX_MISSED_PACKET_OVERFLOW_CNT;
    *pMissedPacketCntOverflowFlag = ((u32TmpVal & ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISCNTOVF_MASK) ==
                                     ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISCNTOVF_MASK) ? true : false;
    *pMissedPacketCnt = (uint16_t)((u32TmpVal & ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISPKTCNT_MASK) >>
                                   ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISPKTCNT_SHIFT);
    *pOverflowPacketCntOverflowFlag = ((u32TmpVal & ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFCNTOVF_MASK) ==
                                       ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFCNTOVF_MASK) ? true : false;
    *pOverflowPacketCnt = (uint16_t)((u32TmpVal & ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT_MASK) >>
                                     ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT_SHIFT);
}

/**
 * @brief Get the receive queue debug status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t receive queue debug status
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetRxDebugStatus(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    return pEnet->MTL.QUEUE[eQueue].RX_DEBUG;
}

/**
 * @brief Get the number of packets in receive queue

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint8_t packets number
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetRxPacketCount(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_DEBUG & ENET_MTL_RXQ0_DEBUG_PRXQ_MASK) >>
                         ENET_MTL_RXQ0_DEBUG_PRXQ_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Get receive queue Fill-Level status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_RxQueueStatusType (empty,below flow-control deactivate threshold,above flow-control activate threshold,full)
 */
LOCAL_INLINE ENET_MTL_RxQueueStatusType ENET_HWA_MTL_GetRxFillLevelStatus(const ENET_Type *const pEnet,
                                                                          ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_DEBUG & ENET_MTL_RXQ0_DEBUG_RXQSTS_MASK) >>
                         ENET_MTL_RXQ0_DEBUG_RXQSTS_SHIFT;
    return (ENET_MTL_RxQueueStatusType)u32TmpVal;
}

/**
 * @brief Get receive queue read controller state

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_ReadControllerStatusType
 */
LOCAL_INLINE ENET_MTL_ReadControllerStatusType ENET_HWA_MTL_GetRxQueueReadControllerStatus(const ENET_Type *const pEnet,
        ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_DEBUG & ENET_MTL_RXQ0_DEBUG_RRCSTS_MASK) >>
                         ENET_MTL_RXQ0_DEBUG_RRCSTS_SHIFT;
    return (ENET_MTL_ReadControllerStatusType)u32TmpVal;
}

/**
 * @brief Get receive queue write controller state

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return ENET_MTL_WriteControllerStatusType
 */
LOCAL_INLINE ENET_MTL_WriteControllerStatusType ENET_HWA_MTL_GetRxQueueWriteControllerStatus(const ENET_Type *const pEnet,
        ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_DEBUG & ENET_MTL_RXQ0_DEBUG_RWCSTS_MASK) >>
                         ENET_MTL_RXQ0_DEBUG_RWCSTS_SHIFT;
    return (ENET_MTL_WriteControllerStatusType)u32TmpVal;
}

/**
 * @brief Get MTL queue receive control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint32_t receive control value
 */
LOCAL_INLINE uint32_t ENET_HWA_MTL_GetRxControl(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    return pEnet->MTL.QUEUE[eQueue].RX_CONTROL;
}

/**
 * @brief Set MTL queue receive control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u32Ctrl receive control value
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxControl(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, uint32_t u32Ctrl)
{
    pEnet->MTL.QUEUE[eQueue].RX_CONTROL = u32Ctrl;
}

/**
 * @brief Get receive queue packet arbitration enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return true receive queue packet arbitration is enabled
 * @return false receive queue packet arbitration is disabled
 */
LOCAL_INLINE bool ENET_HWA_MTL_GetRxQueuePacketArbitrationEnFlag(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_CONTROL & ENET_MTL_RXQ0_CONTROL_RXQ_FRM_ARBIT_MASK) >>
                         ENET_MTL_RXQ0_CONTROL_RXQ_FRM_ARBIT_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set receive queue packet arbitration enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] bEnable enable or disable
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxQueuePacketArbitrationEnFlag(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue,
                                                                 bool bEnable)
{
    pEnet->MTL.QUEUE[eQueue].RX_CONTROL = (pEnet->MTL.QUEUE[eQueue].RX_CONTROL & ~ENET_MTL_RXQ0_CONTROL_RXQ_FRM_ARBIT_MASK)
                                          | ENET_MTL_RXQ0_CONTROL_RXQ_FRM_ARBIT(bEnable ? 1u : 0u);
}

/**
 * @brief Get receive queue weight

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @return uint8_t receive queue weight
 */
LOCAL_INLINE uint8_t ENET_HWA_MTL_GetRxQueueWeight(const ENET_Type *const pEnet, ENET_MTL_QueueType eQueue)
{
    uint32_t u32TmpVal = (pEnet->MTL.QUEUE[eQueue].RX_CONTROL & ENET_MTL_RXQ0_CONTROL_RXQ_WEGT_MASK) >>
                         ENET_MTL_RXQ0_CONTROL_RXQ_WEGT_SHIFT;
    return (uint8_t)(u32TmpVal + 1u);
}

/**
 * @brief Set receive queue weight

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eQueue MTL queue id
 * @param [in] u8Weight receive queue weight
 */
LOCAL_INLINE void ENET_HWA_MTL_SetRxQueueWeight(ENET_Type *const pEnet, ENET_MTL_QueueType eQueue, uint8_t u8Weight)
{
    pEnet->MTL.QUEUE[eQueue].RX_CONTROL = (pEnet->MTL.QUEUE[eQueue].RX_CONTROL & ~ENET_MTL_RXQ0_CONTROL_RXQ_WEGT_MASK)
                                          | ENET_MTL_RXQ0_CONTROL_RXQ_WEGT((uint32_t)u8Weight - 1u);
}

/* ================================================================ *
 *                  ENET DMA Configuration and Status               *
 * ================================================================ */

/**
 * @brief Get DMA bus mode register value

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t DMA bus mode register value
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetMode(const ENET_Type *const pEnet)
{
    return pEnet->ENET_DMA.MODE;
}

/**
 * @brief Set DMA bus mode register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] u32Mode DMA bus mode value
 */
LOCAL_INLINE void ENET_HWA_DMA_SetMode(ENET_Type *const pEnet, uint32_t u32Mode)
{
    pEnet->ENET_DMA.MODE = u32Mode;
}

/**
 * @brief Get DMA software reset status

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_DMA_StatusType
 */
LOCAL_INLINE ENET_DMA_StatusType ENET_HWA_DMA_GetSwResetStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.MODE & ENET_DMA_MODE_SWR_MASK) >> ENET_DMA_MODE_SWR_SHIFT;
    return (ENET_DMA_StatusType)u32TmpVal;
}

/**
 * @brief Initiate DMA software reset

 * @param [in] pEnet the base address of the ENET instance
 */
LOCAL_INLINE void ENET_HWA_DMA_SwReset(ENET_Type *const pEnet)
{
    pEnet->ENET_DMA.MODE |= ENET_DMA_MODE_SWR_MASK;
}

/**
 * @brief Get DMA interrupt mode

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_DMA_IntModeType
 */
LOCAL_INLINE ENET_DMA_IntModeType ENET_HWA_DMA_GetInterruptMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.MODE & ENET_DMA_MODE_INTM_MASK) >> ENET_DMA_MODE_INTM_SHIFT;
    return (ENET_DMA_IntModeType)u32TmpVal;
}

/**
 * @brief Set DMA interrupt mode

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eIntMode DMA interrupt mode
 */
LOCAL_INLINE void ENET_HWA_DMA_SetInterruptMode(ENET_Type *const pEnet, ENET_DMA_IntModeType eIntMode)
{
    pEnet->ENET_DMA.MODE = (pEnet->ENET_DMA.MODE & ~ENET_DMA_MODE_INTM_MASK) | ENET_DMA_MODE_INTM(eIntMode);
}

/**
 * @brief Get DMA Rx:Tx or Tx:Rx priority ratio

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_DMA_PriorityRatioType
 */
LOCAL_INLINE ENET_DMA_PriorityRatioType ENET_HWA_DMA_GetPriorityRatio(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.MODE & ENET_DMA_MODE_PR_MASK) >> ENET_DMA_MODE_PR_SHIFT;
    return (ENET_DMA_PriorityRatioType)u32TmpVal;
}

/**
 * @brief Set DMA Rx:Tx or Tx:Rx priority ratio

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePriorityRatio priority ratio
 */
LOCAL_INLINE void ENET_HWA_DMA_SetPriorityRatio(ENET_Type *const pEnet, ENET_DMA_PriorityRatioType ePriorityRatio)
{
    pEnet->ENET_DMA.MODE = (pEnet->ENET_DMA.MODE & ~ENET_DMA_MODE_PR_MASK) | ENET_DMA_MODE_PR(ePriorityRatio);
}

/**
 * @brief Get DMA priority mode

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_DMA_PRIORITY_MODE_RX_TX the priority ratio is RX:TX
 * @return ENET_DMA_PRIORITY_MODE_TX_RX the priority ratio is TX:RX
 */
LOCAL_INLINE ENET_DMA_PriorityModeType ENET_HWA_DMA_GetPriorityMode(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.MODE & ENET_DMA_MODE_TXPR_MASK) >> ENET_DMA_MODE_TXPR_SHIFT;
    return (ENET_DMA_PriorityModeType)u32TmpVal;
}

/**
 * @brief Set DMA priority mode,Rx:Tx or Tx:Rx

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] ePriorityMode priority mode
 */
LOCAL_INLINE void ENET_HWA_DMA_SetPriorityMode(ENET_Type *const pEnet, ENET_DMA_PriorityModeType ePriorityMode)
{
    pEnet->ENET_DMA.MODE = (pEnet->ENET_DMA.MODE & ~ENET_DMA_MODE_TXPR_MASK) | ENET_DMA_MODE_TXPR(ePriorityMode);
}

/**
 * @brief Get DMA arbitration algorithm between transmit channels

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_DMA_TxArbitrationAlgorithmType
 */
LOCAL_INLINE ENET_DMA_TxArbitrationAlgorithmType ENET_HWA_DMA_GetTxArbitrationAlgorithm(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.MODE & ENET_DMA_MODE_TAA_MASK) >> ENET_DMA_MODE_TAA_SHIFT;
    return (ENET_DMA_TxArbitrationAlgorithmType)u32TmpVal;
}

/**
 * @brief Set DMA arbitration algorithm between transmit channels

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eArbitrationAlgorithm DMA arbitration algorithm
 */
LOCAL_INLINE void ENET_HWA_DMA_SetTxArbitrationAlgorithm(ENET_Type *const pEnet, ENET_DMA_TxArbitrationAlgorithmType eArbitrationAlgorithm)
{
    pEnet->ENET_DMA.MODE = (pEnet->ENET_DMA.MODE & ~ENET_DMA_MODE_TAA_MASK) | ENET_DMA_MODE_TAA(eArbitrationAlgorithm);
}

/**
 * @brief Get DMA arbitration scheme between the transmit and receive paths

 * @param [in] pEnet the base address of the ENET instance
 * @return ENET_DMA_ArbitrationSchemeType
 */
LOCAL_INLINE ENET_DMA_ArbitrationSchemeType ENET_HWA_DMA_GetTxRxArbitrationScheme(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.MODE & ENET_DMA_MODE_DA_MASK) >> ENET_DMA_MODE_DA_SHIFT;
    return (ENET_DMA_ArbitrationSchemeType)u32TmpVal;
}

/**
 * @brief Set DMA arbitration scheme between the transmit and receive paths

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eArbitrationScheme DMA arbitration algorithm
 */
LOCAL_INLINE void ENET_HWA_DMA_SetTxRxArbitrationScheme(ENET_Type *const pEnet, ENET_DMA_ArbitrationSchemeType eArbitrationScheme)
{
    pEnet->ENET_DMA.MODE = (pEnet->ENET_DMA.MODE & ~ENET_DMA_MODE_DA_MASK) | ENET_DMA_MODE_DA(eArbitrationScheme);
}

/**
 * @brief Get DMA rebuild INCRx burst enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true rebuild INCRx burst is enabled
 * @return false rebuild INCRx burst is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetRebuildINCRxBurstEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.SYSBUS_MODE & ENET_DMA_SYSBUS_MODE_RB_MASK) >> ENET_DMA_SYSBUS_MODE_RB_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA rebuild INCRx burst enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRebuildINCRxBurstEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->ENET_DMA.SYSBUS_MODE = (pEnet->ENET_DMA.SYSBUS_MODE & ~ENET_DMA_SYSBUS_MODE_RB_MASK) |
                                  ENET_DMA_SYSBUS_MODE_RB(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA mixed burst length enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true mixed burst is enabled
 * @return false mixed burst is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetMixedBurstEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.SYSBUS_MODE & ENET_DMA_SYSBUS_MODE_MB_MASK) >> ENET_DMA_SYSBUS_MODE_MB_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA mixed burst length enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetMixedBurstEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->ENET_DMA.SYSBUS_MODE = (pEnet->ENET_DMA.SYSBUS_MODE & ~ENET_DMA_SYSBUS_MODE_MB_MASK) |
                                  ENET_DMA_SYSBUS_MODE_MB(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA Address-Aligned Beats enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true Address-Aligned Beats is enabled
 * @return false Address-Aligned Beats is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetAddressAlignedBeatsEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.SYSBUS_MODE & ENET_DMA_SYSBUS_MODE_AAL_MASK) >> ENET_DMA_SYSBUS_MODE_AAL_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA Address-Aligned Beats enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetAddressAlignedBeatsEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->ENET_DMA.SYSBUS_MODE = (pEnet->ENET_DMA.SYSBUS_MODE & ~ENET_DMA_SYSBUS_MODE_AAL_MASK) |
                                  ENET_DMA_SYSBUS_MODE_AAL(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA fixed burst length enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @return true fixed burst length is enabled
 * @return false fixed burst length is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetFixedBurstLengthEnFlag(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.SYSBUS_MODE & ENET_DMA_SYSBUS_MODE_FB_MASK) >> ENET_DMA_SYSBUS_MODE_FB_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA fixed burst length enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetFixedBurstLengthEnFlag(ENET_Type *const pEnet, bool bEnable)
{
    pEnet->ENET_DMA.SYSBUS_MODE = (pEnet->ENET_DMA.SYSBUS_MODE & ~ENET_DMA_SYSBUS_MODE_FB_MASK) |
                                  ENET_DMA_SYSBUS_MODE_FB(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return uint32_t DMA interrupt status value
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetDMAIntStatus(const ENET_Type *const pEnet)
{
    return pEnet->ENET_DMA.INTERRUPT_STATUS;
}

/**
 * @brief Get MAC interrupt event in DMA interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true MAC interrupt event detected
 * @return false MAC interrupt event not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetMACIntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.INTERRUPT_STATUS & ENET_DMA_INTERRUPT_STATUS_MACIS_MASK) >>
                         ENET_DMA_INTERRUPT_STATUS_MACIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get MTL interrupt event in DMA interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true MTL interrupt event detected
 * @return false MTL interrupt event not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetMTLIntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.INTERRUPT_STATUS & ENET_DMA_INTERRUPT_STATUS_MTLIS_MASK) >>
                         ENET_DMA_INTERRUPT_STATUS_MTLIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get DMA channel0 interrupt event in DMA interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true DMA channel0 interrupt event detected
 * @return false DMA channel0 interrupt event not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetDMAChannel0IntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.INTERRUPT_STATUS & ENET_DMA_INTERRUPT_STATUS_DC0IS_MASK) >>
                         ENET_DMA_INTERRUPT_STATUS_DC0IS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get DMA channel1 interrupt event in DMA interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @return true DMA channel1 interrupt event detected
 * @return false DMA channel1 interrupt event not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetDMAChannel1IntStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.INTERRUPT_STATUS & ENET_DMA_INTERRUPT_STATUS_DC1IS_MASK) >>
                         ENET_DMA_INTERRUPT_STATUS_DC1IS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get DMA channel interrupt event in DMA interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eChannel DMA channel
 * @return true eChannel interrupt event detected
 * @return false eChannel interrupt event not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetDMAChannelIntStatus(const ENET_Type *const pEnet, ENET_DMA_ChannelType eChannel)
{
    uint32_t u32TmpVal = pEnet->ENET_DMA.INTERRUPT_STATUS & ((uint32_t)1u << (uint32_t)eChannel);
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Get AXI Master Read Channel Status

 * @param [in] pEnet the base address of the ENET instance
 * @return true AXI Master Read Channel  detected
 * @return false AXI Master Read Channel  not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetAHBMasterBusyStatus(const ENET_Type *const pEnet)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.DEBUG_STATUS0 & ENET_DMA_DEBUG_STATUS0_AXWHSTS_MASK) >>
                         ENET_DMA_DEBUG_STATUS0_AXWHSTS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief Get DMA TBS fetch time offset

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eCtrlIndex DMA TBS control index
 * @return uint32_t DMA TBS fetch time offset
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetFetchTimeOffset(const ENET_Type *const pEnet, uint8_t eCtrlIndex)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.TBS_CTRL[eCtrlIndex] & ENET_DMA_TBS_CTRL_FTOS_MASK) >> ENET_DMA_TBS_CTRL_FTOS_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Set DMA TBS fetch time offset

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eCtrlIndex DMA TBS control index
 * @param [in] u32FetchTimeOffset DMA TBS fetch time offset
 */
LOCAL_INLINE void ENET_HWA_DMA_SetFetchTimeOffset(ENET_Type *const pEnet, uint8_t eCtrlIndex, uint32_t u32FetchTimeOffset)
{
    pEnet->ENET_DMA.TBS_CTRL[eCtrlIndex] = (pEnet->ENET_DMA.TBS_CTRL[eCtrlIndex] & ~ENET_DMA_TBS_CTRL_FTOS_MASK) |
                                           ENET_DMA_TBS_CTRL_FTOS(u32FetchTimeOffset);
}

/**
 * @brief Get DMA TBS fetch time offset valid

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eCtrlIndex DMA TBS control index
 * @return true TBS fetch time offset is valid
 * @return false TBS fetch time offset is invalid
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetFetchTimeOffsetValid(const ENET_Type *const pEnet, uint8_t eCtrlIndex)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.TBS_CTRL[eCtrlIndex] & ENET_DMA_TBS_CTRL_FTOV_MASK) >> ENET_DMA_TBS_CTRL_FTOV_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA TBS fetch time offset valid

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eCtrlIndex DMA TBS control index
 * @param [in] bEnable set valid
 */
LOCAL_INLINE void ENET_HWA_DMA_SetFetchTimeOffsetValid(ENET_Type *const pEnet, uint8_t eCtrlIndex, bool bEnable)
{
    pEnet->ENET_DMA.TBS_CTRL[eCtrlIndex] = (pEnet->ENET_DMA.TBS_CTRL[eCtrlIndex] & ~ENET_DMA_TBS_CTRL_FTOV_MASK) |
                                           ENET_DMA_TBS_CTRL_FTOV(bEnable ? 1u : 0u);
}
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief Get DMA channel control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t register value
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetChannelCtrl(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].CONTROL;
}

/**
 * @brief Set DMA channel control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32ChannelCtrl control value
 */
LOCAL_INLINE void ENET_HWA_DMA_SetChannelCtrl(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                              uint32_t u32ChannelCtrl)
{
    pEnet->ENET_DMA.CH[eDMAChannel].CONTROL = u32ChannelCtrl;
}

/**
 * @brief Get DMA descriptor skip length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint8_t descriptor skip length
 */
LOCAL_INLINE uint8_t ENET_HWA_DMA_GetDescriptorSkipLength(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].CONTROL & ENET_DMA_CH0_CONTROL_DSL_MASK) >>
                         ENET_DMA_CH0_CONTROL_DSL_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set DMA descriptor skip length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u8Length descriptor skip length
 */
LOCAL_INLINE void ENET_HWA_DMA_SetDescriptorSkipLength(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                       uint8_t u8Length)
{
    pEnet->ENET_DMA.CH[eDMAChannel].CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].CONTROL & ~ENET_DMA_CH0_CONTROL_DSL_MASK) |
                                              ENET_DMA_CH0_CONTROL_DSL(u8Length);
}

/**
 * @brief Get DMA burst length multiply by 8 mode

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true DMA Tx and Rx burst length is multipled by 8
 * @return false use DMA Tx and Rx burst length
 */
LOCAL_INLINE bool ENET_HWA_DMA_Get8xPBLModeEnFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].CONTROL & ENET_DMA_CH0_CONTROL_PBLX8_MASK) >>
                         ENET_DMA_CH0_CONTROL_PBLX8_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA burst length multiply by 8 mode

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable enable x8 mode
 */
LOCAL_INLINE void ENET_HWA_DMA_Set8xPBLModeEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                  bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].CONTROL & ~ENET_DMA_CH0_CONTROL_PBLX8_MASK) |
                                              ENET_DMA_CH0_CONTROL_PBLX8(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA transmit channel control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t register value
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetChannelTxCtrl(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL;
}

/**
 * @brief Set DMA transmit channel control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32TxCtrl control value
 */
LOCAL_INLINE void ENET_HWA_DMA_SetChannelTxCtrl(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                uint32_t u32TxCtrl)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL = u32TxCtrl;
}

/**
 * @brief Get DMA enhanced descriptor enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true enhanced descriptor is enabled
 * @return false enhanced descriptor is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetEnhancedDescriptorEnFlag(const ENET_Type *const pEnet,
                                                           ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL & ENET_DMA_CH0_TX_CONTROL_EDSE_MASK) >>
                         ENET_DMA_CH0_TX_CONTROL_EDSE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA enhanced descriptor enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetEnhancedDescriptorEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                           bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL &
                                                  ~ENET_DMA_CH0_TX_CONTROL_EDSE_MASK) |
                                                 ENET_DMA_CH0_TX_CONTROL_EDSE(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA early transmit interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true early transmit interrupt is enabled
 * @return false early transmit interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetEarlyTxIntEnFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL & ENET_DMA_CH0_TX_CONTROL_ETIC_MASK) >>
                         ENET_DMA_CH0_TX_CONTROL_ETIC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA early transmit interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetEarlyTxIntEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                   bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL &
                                                  ~ENET_DMA_CH0_TX_CONTROL_ETIC_MASK) |
                                                 ENET_DMA_CH0_TX_CONTROL_ETIC(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA transmit programmable burst length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint8_t transmit burst length
 */
LOCAL_INLINE uint8_t ENET_HWA_DMA_GetTxBurstLength(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL & ENET_DMA_CH0_TX_CONTROL_TXPBL_MASK) >>
                         ENET_DMA_CH0_TX_CONTROL_TXPBL_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set DMA transmit programmable burst length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u8Length transmit burst length
 */
LOCAL_INLINE void ENET_HWA_DMA_SetTxBurstLength(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel, uint8_t u8Length)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL &
                                                  ~ENET_DMA_CH0_TX_CONTROL_TXPBL_MASK) |
                                                 ENET_DMA_CH0_TX_CONTROL_TXPBL(u8Length);
}

/**
 * @brief Get DMA operate on second packet enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true operate on second packet is enabled
 * @return false operate on second packet is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetOperateOnSecondPacketEnFlag(const ENET_Type *const pEnet,
                                                              ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL & ENET_DMA_CH0_TX_CONTROL_OSF_MASK) >>
                         ENET_DMA_CH0_TX_CONTROL_OSF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA operate on second packet enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetOperateOnSecondPacketEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                              bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL &
                                                  ~ENET_DMA_CH0_TX_CONTROL_OSF_MASK) |
                                                 ENET_DMA_CH0_TX_CONTROL_OSF(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA transmit channel weight

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint8_t transmit channel weight
 */
LOCAL_INLINE uint8_t ENET_HWA_DMA_GetTxChannelWeight(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL & ENET_DMA_CH0_TX_CONTROL_TCW_MASK) >>
                         ENET_DMA_CH0_TX_CONTROL_TCW_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set DMA transmit channel weight

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u8Weight transmit channel weight
 */
LOCAL_INLINE void ENET_HWA_DMA_SetTxChannelWeight(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                  uint8_t u8Weight)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL &
                                                  ~ENET_DMA_CH0_TX_CONTROL_TCW_MASK) |
                                                 ENET_DMA_CH0_TX_CONTROL_TCW(u8Weight);
}

/**
 * @brief Get DMA transmit channel active status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return ENET_DMA_STATUS_IDLE    DMA transmission is stopped
 * @return ENET_DMA_STATUS_ACTIVE  DMA transmission is running
 */
LOCAL_INLINE ENET_DMA_StatusType ENET_HWA_DMA_GetTxActiveStatus(const ENET_Type *const pEnet,
                                                                ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL & ENET_DMA_CH0_TX_CONTROL_ST_MASK) >>
                         ENET_DMA_CH0_TX_CONTROL_ST_SHIFT;
    return (ENET_DMA_StatusType)u32TmpVal;
}

/**
 * @brief Start DMA transmission

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_StartTx(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL |= ENET_DMA_CH0_TX_CONTROL_ST_MASK;
}

/**
 * @brief Stop DMA transmission

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_StopTx(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TX_CONTROL &= ~ENET_DMA_CH0_TX_CONTROL_ST_MASK;
}

/**
 * @brief Get DMA receive channel control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t register value
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetChannelRxCtrl(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL;
}

/**
 * @brief Set DMA receive channel control register value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32RxCtrl control value
 */
LOCAL_INLINE void ENET_HWA_DMA_SetChannelRxCtrl(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                uint32_t u32RxCtrl)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL = u32RxCtrl;
}

/**
 * @brief Get DMA receive packet flush enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true Rx packet flush is enabled
 * @return false Rx packet flush is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetRxPacketFlushEnFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL & ENET_DMA_CH0_RX_CONTROL_RPF_MASK) >>
                         ENET_DMA_CH0_RX_CONTROL_RPF_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA receive packet flush enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxPacketFlushEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                      bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL &
                                                  ~ENET_DMA_CH0_RX_CONTROL_RPF_MASK) |
                                                 ENET_DMA_CH0_RX_CONTROL_RPF(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA early receive interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true early receive interrupt is enabled
 * @return false early receive interrupt is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetEarlyRxIntEnFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL & ENET_DMA_CH0_RX_CONTROL_ERIC_MASK) >>
                         ENET_DMA_CH0_RX_CONTROL_ERIC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set DMA early receive interrupt enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetEarlyRxIntEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                   bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL &
                                                  ~ENET_DMA_CH0_RX_CONTROL_ERIC_MASK) |
                                                 ENET_DMA_CH0_RX_CONTROL_ERIC(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA receive programmable burst length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint8_t receive burst length
 */
LOCAL_INLINE uint8_t ENET_HWA_DMA_GetRxBurstLength(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL & ENET_DMA_CH0_RX_CONTROL_RXPBL_MASK) >>
                         ENET_DMA_CH0_RX_CONTROL_RXPBL_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set DMA receive programmable burst length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u8Length receive burst length
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxBurstLength(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel, uint8_t u8Length)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL &
                                                  ~ENET_DMA_CH0_RX_CONTROL_RXPBL_MASK) |
                                                 ENET_DMA_CH0_RX_CONTROL_RXPBL(u8Length);
}

/**
 * @brief Get DMA receive buffer size

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint16_t receive buffer size
 */
LOCAL_INLINE uint16_t ENET_HWA_DMA_GetRxBufferSize(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL &
                          (ENET_DMA_CH0_RX_CONTROL_RBSZ_13_Y_MASK | ENET_DMA_CH0_RX_CONTROL_RBSZ_X_0_MASK)) >>
                         ENET_DMA_CH0_RX_CONTROL_RBSZ_X_0_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set DMA receive buffer size

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u16BufferSize receive buffer size
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxBufferSize(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                               uint16_t u16BufferSize)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL &
                                                  ~ENET_DMA_CH0_RX_CONTROL_RBSZ_13_Y_MASK) |
                                                 ENET_DMA_CH0_RX_CONTROL_RBSZ_13_Y(((uint32_t)u16BufferSize >>
                                                 (ENET_DMA_CH0_RX_CONTROL_RBSZ_13_Y_SHIFT -
                                                 ENET_DMA_CH0_RX_CONTROL_RBSZ_X_0_SHIFT)));
}

/**
 * @brief Get DMA receive channel active status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return ENET_DMA_STATUS_IDLE    DMA reception is stopped
 * @return ENET_DMA_STATUS_ACTIVE  DMA reception is running
 */
LOCAL_INLINE ENET_DMA_StatusType ENET_HWA_DMA_GetRxActiveStatus(const ENET_Type *const pEnet,
                                                                ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL & ENET_DMA_CH0_RX_CONTROL_SR_MASK) >>
                         ENET_DMA_CH0_RX_CONTROL_SR_SHIFT;
    return (ENET_DMA_StatusType)u32TmpVal;
}

/**
 * @brief Start DMA reception

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_StartRx(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL |= ENET_DMA_CH0_RX_CONTROL_SR_MASK;
}

/**
 * @brief Stop DMA reception

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_StopRx(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_CONTROL &= ~ENET_DMA_CH0_RX_CONTROL_SR_MASK;
}

/**
 * @brief Get DMA channel Tx descriptor list header address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t Tx descriptor list header address
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetTxDescListHeadAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].TXDESC_LIST_ADDRESS;
}

/**
 * @brief Set DMA channel Tx descriptor list header address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32TxAddr Tx descriptor list header address
 */
LOCAL_INLINE void ENET_HWA_DMA_SetTxDescListHeadAddr(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                     uint32_t u32TxAddr)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TXDESC_LIST_ADDRESS = ENET_DMA_CH0_TXDESC_LIST_ADDRESS_TDESLA(
                                                                      u32TxAddr >> ENET_DMA_CH0_TXDESC_LIST_ADDRESS_TDESLA_SHIFT);
}

/**
 * @brief Get DMA channel Rx descriptor list header address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t Rx descriptor list header address
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetRxDescListHeadAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].RXDESC_LIST_ADDRESS;
}

/**
 * @brief Set DMA channel Rx descriptor list header address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32RxAddr Rx descriptor list header address
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxDescListHeadAddr(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                     uint32_t u32RxAddr)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RXDESC_LIST_ADDRESS = ENET_DMA_CH0_RXDESC_LIST_ADDRESS_RDESLA(
                                                                      u32RxAddr >> ENET_DMA_CH0_RXDESC_LIST_ADDRESS_RDESLA_SHIFT);
}

/**
 * @brief Get DMA channel Tx descriptor list tail address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t Tx descriptor list tail address
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetTxDescListTailAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].TXDESC_TAIL_POINTER;
}

/**
 * @brief Set DMA channel Tx descriptor list tail address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32TxAddr Tx descriptor list tail address
 */
LOCAL_INLINE void ENET_HWA_DMA_SetTxDescListTailAddr(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                     uint32_t u32TxAddr)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TXDESC_TAIL_POINTER = ENET_DMA_CH0_TXDESC_TAIL_POINTER_TDTP(
                                                                      u32TxAddr >> ENET_DMA_CH0_TXDESC_TAIL_POINTER_TDTP_SHIFT);
}

/**
 * @brief Get DMA channel Rx descriptor list tail address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t Rx descriptor list tail address
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetRxDescListTailAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].RXDESC_TAIL_POINTER;
}

/**
 * @brief Set DMA channel Rx descriptor list tail address

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32RxAddr Rx descriptor list tail address
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxDescListTailAddr(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                     uint32_t u32RxAddr)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RXDESC_TAIL_POINTER = ENET_DMA_CH0_RXDESC_TAIL_POINTER_RDTP(
                                                                      u32RxAddr >> ENET_DMA_CH0_RXDESC_TAIL_POINTER_RDTP_SHIFT);
}

/**
 * @brief Get DMA channel Tx descriptor ring length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint16_t Tx descriptor ring length
 */
LOCAL_INLINE uint16_t ENET_HWA_DMA_GetTxDescRingLength(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].TXDESC_RING_LENGTH & ENET_DMA_CH0_TXDESC_RING_LENGTH_TDRL_MASK) >>
                         ENET_DMA_CH0_TXDESC_RING_LENGTH_TDRL_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set DMA channel Tx descriptor ring length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u16Length Tx descriptor ring length
 */
LOCAL_INLINE void ENET_HWA_DMA_SetTxDescRingLength(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                   uint16_t u16Length)
{
    pEnet->ENET_DMA.CH[eDMAChannel].TXDESC_RING_LENGTH = ENET_DMA_CH0_TXDESC_RING_LENGTH_TDRL(u16Length);
}

/**
 * @brief Get DMA channel Rx descriptor ring length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t Rx descriptor ring length
 */
LOCAL_INLINE uint16_t ENET_HWA_DMA_GetRxDescRingLength(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RXDESC_RING_LENGTH & ENET_DMA_CH0_RXDESC_RING_LENGTH_RDRL_MASK) >>
                         ENET_DMA_CH0_RXDESC_RING_LENGTH_RDRL_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set DMA channel Rx descriptor ring length

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u16Length Rx descriptor ring length
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxDescRingLength(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                   uint16_t u16Length)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RXDESC_RING_LENGTH = ENET_DMA_CH0_RXDESC_RING_LENGTH_RDRL(u16Length);
}

/**
 * @brief Get DMA channel enabled interrupts

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t enabled interrupts
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetEnabledInterrupts(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].INTERRUPT_ENABLE;
}

/**
 * @brief Set DMA channel interrupts enable state

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32IntEnable interrupts to be enabled
 */
LOCAL_INLINE void ENET_HWA_DMA_SetEnabledInterrupts(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                    uint32_t u32IntEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].INTERRUPT_ENABLE = u32IntEnable;
}

/**
 * @brief Enable one of the DMA channel interrupts

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] eIntFlag interrupt to be enabled
 */
LOCAL_INLINE void ENET_HWA_DMA_EnableInterrupt(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                               ENET_DMA_InterruptFlagType eIntFlag)
{
    pEnet->ENET_DMA.CH[eDMAChannel].INTERRUPT_ENABLE |= (uint32_t)eIntFlag;
}

/**
 * @brief Disable one of the DMA channel interrupts

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] eIntFlag interrupt to be disbled
 */
LOCAL_INLINE void ENET_HWA_DMA_DisableInterrupt(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                ENET_DMA_InterruptFlagType eIntFlag)
{
    pEnet->ENET_DMA.CH[eDMAChannel].INTERRUPT_ENABLE &= ~(uint32_t)eIntFlag;
}

/**
 * @brief Get receive interrupt watchdog timer count unit

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return ENET_DMA_WDGCounterUnitType
 */
LOCAL_INLINE ENET_DMA_WDGCounterUnitType ENET_HWA_DMA_GetRxWDGCounterUnit(const ENET_Type *const pEnet,
                                                                          ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_INTERRUPT_WATCHDOG_TIMER &
                          ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWTU_MASK) >>
                         ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWTU_SHIFT;
    return (ENET_DMA_WDGCounterUnitType)u32TmpVal;
}

/**
 * @brief Set receive interrupt watchdog timer count unit

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] eCounterUnit watchdog timer count unit
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxWDGCounterUnit(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                   ENET_DMA_WDGCounterUnitType eCounterUnit)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_INTERRUPT_WATCHDOG_TIMER =
                (pEnet->ENET_DMA.CH[eDMAChannel].RX_INTERRUPT_WATCHDOG_TIMER &
                 ~ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWTU_MASK) |
                ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWTU(eCounterUnit);
}

/**
 * @brief Get receive interrupt watchdog timer count

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint8_t watchdog timer count value
 */
LOCAL_INLINE uint8_t ENET_HWA_DMA_GetRxWDGCount(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_INTERRUPT_WATCHDOG_TIMER &
                          ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWT_MASK) >>
                         ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWT_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set receive interrupt watchdog timer count

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u8WDGCnt watchdog timer count
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRxWDGCount(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel, uint8_t u8WDGCnt)
{
    pEnet->ENET_DMA.CH[eDMAChannel].RX_INTERRUPT_WATCHDOG_TIMER =
                (pEnet->ENET_DMA.CH[eDMAChannel].RX_INTERRUPT_WATCHDOG_TIMER &
                 ~ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWT_MASK) |
                ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER_RWT(u8WDGCnt);
}

/**
 * @brief Get reference slot number in the DMA

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint8_t reference slot number
 */
LOCAL_INLINE uint8_t ENET_HWA_DMA_GetRefSlotNumber(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                          ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_RSN_MASK) >>
                         ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_RSN_SHIFT;
    return (uint8_t)u32TmpVal;
}

/**
 * @brief Set reference slot number in the DMA

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u8SlotNumber reference slot number
 */
LOCAL_INLINE void ENET_HWA_DMA_SetRefSlotNumber(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                uint8_t u8SlotNumber)
{
    pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS =
                (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                 ~ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_RSN_MASK) |
                ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_RSN(u8SlotNumber);
}

/**
 * @brief Get slot interval value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint16_t slot interval
 */
LOCAL_INLINE uint16_t ENET_HWA_DMA_GetSlotInterval(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                          ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_SIV_MASK) >>
                         ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_SIV_SHIFT;
    return (uint16_t)(u32TmpVal + 1u);
}

/**
 * @brief Set slot interval value

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u16SlotInterval slot interval
 */
LOCAL_INLINE void ENET_HWA_DMA_SetSlotInterval(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                               uint16_t u16SlotInterval)
{
    pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS =
                (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                 ~ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_SIV_MASK) |
                ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_SIV((uint32_t)(u16SlotInterval - (uint32_t)1u));
}

/**
 * @brief Get advance slot check enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true advance slot check is enabled
 * @return false advance slot check is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetAdvanceSlotCheckEnFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                          ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ASC_MASK) >>
                         ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ASC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set advance slot check enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetAdvanceSlotCheckEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                         bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS =
                (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                 ~ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ASC_MASK) |
                ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ASC(bEnable ? 1u : 0u);
}

/**
 * @brief Get slot comparison enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true slot comparison is enabled
 * @return false slot comparison is disabled
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetSlotComparisonEnFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                          ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ESC_MASK) >>
                         ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ESC_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Set slot comparison enable flag

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] bEnable
 */
LOCAL_INLINE void ENET_HWA_DMA_SetSlotComparisonEnFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                       bool bEnable)
{
    pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS =
                (pEnet->ENET_DMA.CH[eDMAChannel].SLOT_FUNCTION_CONTROL_STATUS &
                 ~ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ESC_MASK) |
                ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS_ESC(bEnable ? 1u : 0u);
}

/**
 * @brief Get DMA current Tx descriptor address pointer

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t current Tx descriptor
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetCurrentTxDescAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].CURRENT_APP_TXDESC;
}

/**
 * @brief Get DMA current Rx descriptor address pointer

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t current Rx descriptor
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetCurrentRxDescAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].CURRENT_APP_RXDESC;
}

/**
 * @brief Get DMA current Tx buffer address pointer

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t current Tx buffer
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetCurrentTxBufAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].CURRENT_APP_TXBUFFER;
}

/**
 * @brief Get DMA current Rx buffer address pointer

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t current Rx buffer
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetCurrentRxBufAddr(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].CURRENT_APP_RXBUFFER;
}

/**
 * @brief Get DMA current status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return uint32_t DMA status
 */
LOCAL_INLINE uint32_t ENET_HWA_DMA_GetCurrentStatus(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    return pEnet->ENET_DMA.CH[eDMAChannel].STATUS;
}

/**
 * @brief Set DMA current status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @param [in] u32Status DMA status
 */
LOCAL_INLINE void ENET_HWA_DMA_SetCurrentStatus(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                uint32_t u32Status)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = u32Status;
}

/**
 * @brief Clear all DMA abnormal interrupts

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearAllAbnormalInterruptFlags(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_AIS_MASK |
                                             ENET_DMA_CH0_STATUS_CDE_MASK |
                                             ENET_DMA_CH0_STATUS_FBE_MASK |
                                             ENET_DMA_CH0_STATUS_ETI_MASK |
                                             ENET_DMA_CH0_STATUS_RPS_MASK |
                                             ENET_DMA_CH0_STATUS_RBU_MASK |
                                             ENET_DMA_CH0_STATUS_TPS_MASK;
}

/**
 * @brief Clear all DMA normal interrupts

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearAllNormalInterruptFlags(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_NIS_MASK |
                                             ENET_DMA_CH0_STATUS_ERI_MASK |
                                             ENET_DMA_CH0_STATUS_RI_MASK  |
                                             ENET_DMA_CH0_STATUS_TBU_MASK |
                                             ENET_DMA_CH0_STATUS_TI_MASK;
}

/**
 * @brief Get DMA Rx error status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return ENET_DMA_RxErrorType
 */
LOCAL_INLINE ENET_DMA_RxErrorType ENET_HWA_DMA_GetRxError(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_REB_MASK) >>
                         ENET_DMA_CH0_STATUS_REB_SHIFT;
    return (ENET_DMA_RxErrorType)u32TmpVal;
}

/**
 * @brief Clear DMA Rx error status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearRxError(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_TEB_MASK) &
                                             ~ENET_DMA_CH0_STATUS_REB_MASK;
}

/**
 * @brief Get DMA Tx error status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return ENET_DMA_TxErrorType
 */
LOCAL_INLINE ENET_DMA_TxErrorType ENET_HWA_DMA_GetTxError(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_TEB_MASK) >>
                         ENET_DMA_CH0_STATUS_TEB_SHIFT;
    return (ENET_DMA_TxErrorType)u32TmpVal;
}

/**
 * @brief Clear DMA Tx error status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearTxError(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_REB_MASK) &
                                             ~ENET_DMA_CH0_STATUS_TEB_MASK;
}

/**
 * @brief Get DMA normal interrupt summary

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true normal interrupt detected
 * @return false normal interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetNormalInterruptFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_NIS_MASK) >>
                         ENET_DMA_CH0_STATUS_NIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA normal interrupt summary

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearNormalInterruptFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_NIS_MASK;
}

/**
 * @brief Get DMA abnormal interrupt summary

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true abnormal interrupt detected
 * @return false abnormal interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetAbnormalInterruptFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_AIS_MASK) >>
                         ENET_DMA_CH0_STATUS_AIS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA abnormal interrupt summary

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearAbnormalInterruptFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_AIS_MASK;
}

/**
 * @brief Get DMA context descriptor error

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true context descriptor error detected
 * @return false context descriptor error not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetContextDescriptorErrorFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_CDE_MASK) >>
                         ENET_DMA_CH0_STATUS_CDE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA context descriptor error

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearContextDescriptorErrorFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_CDE_MASK;
}

/**
 * @brief Get DMA fatal bus error

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true fatal bus error detected
 * @return false fatal bus error not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetFatalBusErrorFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_FBE_MASK) >>
                         ENET_DMA_CH0_STATUS_FBE_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA fatal bus error

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearFatalBusErrorFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    /* When FBE cleared, REB and TEB becomes invalid and shall also be cleared */
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = ENET_DMA_CH0_STATUS_FBE_MASK;
}

/**
 * @brief Get DMA early receive interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true early receive interrupt detected
 * @return false early receive interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetEarlyRxInterruptFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_ERI_MASK) >>
                         ENET_DMA_CH0_STATUS_ERI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA early receive interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearEarlyRxInterruptFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_ERI_MASK;
}

/**
 * @brief Get DMA early transmit interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true early transmit interrupt detected
 * @return false early transmit interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetEarlyTxInterruptFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_ETI_MASK) >>
                         ENET_DMA_CH0_STATUS_ETI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA early transmit interrupt

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearEarlyTxInterruptFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_ETI_MASK;
}

/**
 * @brief Get DMA receive watchdog timeout status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true receive watchdog timeout status detected
 * @return false receive watchdog timeout status not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetRxWDGTimeoutFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_RWT_MASK) >>
                         ENET_DMA_CH0_STATUS_RWT_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA receive watchdog timeout status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearRxWDGTimeoutFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_RWT_MASK;
}

/**
 * @brief Get DMA receive process stopped status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true receive process stopped status detected
 * @return false receive process stopped status not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetRxProcessStoppedFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_RPS_MASK) >>
                         ENET_DMA_CH0_STATUS_RPS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA receive process stopped status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearRxProcessStoppedFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_RPS_MASK;
}

/**
 * @brief Get DMA receive buffer unavailable status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true receive buffer unavailable status detected
 * @return false receive buffer unavailable status not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetRxBufferUnavailableFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_RBU_MASK) >>
                         ENET_DMA_CH0_STATUS_RBU_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA receive buffer unavailable status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearRxBufferUnavailableFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_RBU_MASK;
}

/**
 * @brief Get DMA receive interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true receive interrupt detected
 * @return false receive interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetRxInterruptFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_RI_MASK) >>
                         ENET_DMA_CH0_STATUS_RI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA receive interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearRxInterruptFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_RI_MASK;
}

/**
 * @brief Get DMA transmit buffer unavailable status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true transmit buffer unavailable status detected
 * @return false transmit buffer unavailable status not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetTxBufferUnavailableFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_TBU_MASK) >>
                         ENET_DMA_CH0_STATUS_TBU_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA transmit buffer unavailable status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearTxBufferUnavailableFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_TBU_MASK;
}

/**
 * @brief Get DMA transmit process stopped status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true transmit process stopped status detected
 * @return false transmit process stopped status not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetTxProcessStoppedFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_TPS_MASK) >>
                         ENET_DMA_CH0_STATUS_TPS_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA transmit process stopped status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearTxProcessStoppedFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_TPS_MASK;
}

/**
 * @brief Get DMA transmit interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 * @return true transmit interrupt detected
 * @return false transmit interrupt not detected
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetTxInterruptFlag(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS & ENET_DMA_CH0_STATUS_TI_MASK) >>
                         ENET_DMA_CH0_STATUS_TI_SHIFT;
    return (u32TmpVal != 0u) ? true : false;
}

/**
 * @brief Clear DMA transmit interrupt status

 * @param [in] pEnet the base address of the ENET instance
 * @param [in] eDMAChannel DMA channel
 */
LOCAL_INLINE void ENET_HWA_DMA_ClearTxInterruptFlag(ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    pEnet->ENET_DMA.CH[eDMAChannel].STATUS = (pEnet->ENET_DMA.CH[eDMAChannel].STATUS &
                                              (ENET_DMA_CH0_STATUS_REB_MASK | ENET_DMA_CH0_STATUS_TEB_MASK)) |
                                             ENET_DMA_CH0_STATUS_TI_MASK;
}

/**
 * @brief Get the miss frame count and overflow status of the Ethernet DMA channel
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eDMAChannel the DMA channel of the Ethernet instance
 * @param [out] pMissPacketCnt the miss frame count of the channel
 * @return true The miss frame count is overflow
 * @return false the miss frame count is not overflow
 */
LOCAL_INLINE bool ENET_HWA_DMA_GetMissFrameCount(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel,
                                                 uint16_t *pMissPacketCnt)
{
    bool bRet;
    uint32_t u32TmpVal = pEnet->ENET_DMA.CH[eDMAChannel].MISS_FRAME_CNT;
    *pMissPacketCnt = (uint16_t)((u32TmpVal & ENET_DMA_CH0_MISS_FRAME_CNT_MFC_MASK) >>
                                 ENET_DMA_CH0_MISS_FRAME_CNT_MFC_SHIFT);
    bRet = (((u32TmpVal & ENET_DMA_CH0_MISS_FRAME_CNT_MFCO_MASK) >> ENET_DMA_CH0_MISS_FRAME_CNT_MFCO_SHIFT) != 0u) ?
           true : false;
    return bRet;
}

/**
 * @brief Get the count of the number of times Early Receive Interrupt was asserted.
 *
 * @param [in] pEnet the base address of the Ethernet instance
 * @param [in] eDMAChannel the DMA channel of the Ethernet instance
 * @return The count value
 */
LOCAL_INLINE uint16_t ENET_HWA_DMA_GetEarlyRxInterruptCount(const ENET_Type *const pEnet, ENET_DMA_ChannelType eDMAChannel)
{
    uint32_t u32TmpVal = (pEnet->ENET_DMA.CH[eDMAChannel].RX_ERI_CNT & ENET_DMA_CH0_RX_ERI_CNT_ECNT_MASK) >>
                         ENET_DMA_CH0_RX_ERI_CNT_ECNT_SHIFT;
    return (uint16_t)u32TmpVal;
}

/** @}*/

#endif /* ENET_INSTANCE_COUNT > 0u */

#endif /* _HWA_ENET_H_ */
