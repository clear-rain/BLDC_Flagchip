/**
 * @file module_driver_enet.c
 * @author Flagchip
 * @brief ENET driver source code
 * @version 2.0.0
 * @date 2024-07-19
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/**********************************************************************************************************
*  Revision History:


*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-07-19    Flagchip085   N/A          First version
   *******************************************************************************************************/
/**
  *********************************************************************************************************
                                         How to use this driver
  *********************************************************************************************************
 *  [*] Initialize ENET IO before using this driver.
 *      Initialize system clocks before using this driver.
 *      Enable ENET PCC clock before using this driver.
 *      Configure NVIC for ENET interrupts before using this driver.
 *
 *  [*] Initialize the MDIO bus, if you want to configure the PHY before Enet_Init,
 *      For example, when the RMII reference clock is provided by PHY.
 *      The MDIO bus will be Initialized again by Enet_Init.
 *      [**] Call Enet_MDIODefaultConfig to get SMI bus default configuration.
 *      [**] Modify the ENET_MiiConfigType value according to the actual situation.
 *      [**] Call Enet_MDIOInit to initialize the MDIO bus.
 *      [**] Call Enet_MDIORead and Enet_MDIOWrite to read and write PHY registers.
 *
 *  [*] Call Enet_DeInit API to reset the ENET driver.
 *
 *  [*] Call Enet_DefaultConfig API to get default ENET configuration and modify the ENET_ConfigType value
 *       according to the actual situation.
 *
 *  [*] Call Enet_Init API to initialize the ENET driver handle and ENET peripheral.
 *
 *  [*] Start transmission and reception in polling mode,without enabling interrupts:
 *      [**] Call Enet_Start API to start transfer:
 *           Enet_SendFrame : Send frame,This API will poll the transmission status to wait transmit complete.
 *           Enet_ReadFrame : Receive frame,User must poll this API for data availability.
 *           Enet_BuildRxDescriptors: Build DMA Rx descriptors.
 *              After Enet_ReadFrame,Enet_BuildRxDescriptors must be called to free the descriptors and buffers to DMA.
 *
 *  [*] Start transmission and reception in interrupt mode,with enabling interrupts:
 *      [**] Call Enet_StartIT to start interrupt mode.
 *          Enet_SendFrame : Send frame.
 *              TxComplete will be called On transmit complete,if TxComplete is assigned.
 *              TxCompleteWait will be called to suspend current task,which can be resumed by TxComplete.
 *          For example:
 *              If you need to get the transmit time stamp for time synchronization,you can call sem_post in TxComplete
 *              and call sem_wait in TxCompleteWait,the valid time stamp will be saved in ENET_TxOptionType.
 *
 *          Enet_ReadFrame : Receive frame.
 *              When a new packet arrives,ChannelRxComplete will be called if ChannelRxComplete is assigned.
 *              User call Enet_ReadFrame to get the frame buffer and frame information.
 *          Enet_BuildRxDescriptors: Build DMA Rx descriptors.
 *              After Enet_ReadFrame,Enet_BuildRxDescriptors must be called to free the descriptors and buffers to DMA.
 *
 *  [*] Call Enet_Stop to stop the MAC and DMA operation.
 *
 *  [*] ENET events: EventCallback will be called when the following events triggered:
 *
 *  [*] IEEE1588 API usage.
 *      [**] Enet_PTPDefaultConfig to get PTP default configuration and modify the Enet_PTPConfigType value
 *           according to the actual situation.
 *
 *      [**] CALL Enet_PTPStart to start time stamp counter.
 *
 *      [**] Get the transmit time stamp of PTP packets by reading TimeStamp in ENET_TxOptionType.
 *
 *      [**] Get the receive time stamp of PTP packets by reading TimeStamp in ENET_RxInfoType.
 *
 *      [**] The following APIs are used by PTP application for time synchronization:
 *           Enet_PTPGetTime
 *           Enet_PTPSetTime
 *           Enet_PTPUpdateTime
 *           Enet_PTPAdjustFrequency
 *
 *      [**] Call the following APIs to configure the PPS output mode.
 *           Enet_PTPFixedPPSOut
 *           Enet_PTPFlexiblePPSOut
 *
 *      [**] Call Enet_PTPStop to stop time stamp counter.
 *
 *      [**] IEEE1588 events: EventCallback will be called when the following events triggered:
 *          ENET_EVENT_TARGET_TIME0_REACHED
 *          ENET_EVENT_TARGET_TIME0_ERROR
 *          ENET_EVENT_TARGET_TIME1_REACHED
 *          ENET_EVENT_TARGET_TIME1_ERROR
 *          ENET_EVENT_TARGET_TIME2_REACHED
 *          ENET_EVENT_TARGET_TIME2_ERROR
 *          ENET_EVENT_TARGET_TIME3_REACHED
 *          ENET_EVENT_TARGET_TIME3_ERROR
 *
 *  [*] There  are two ways to register callback functions:
 *      [**] Initialize callback functions in ENET_ConfigType.
 *      [**] Register functions dynamically by the following API:
 *          Enet_RegisterEventCallback
 *          Enet_RegisterRxCompleteCallback
 *          Enet_RegisterTxCompleteCallback
 *          Enet_RegisterWaitTxCompleteCallback
 *
 *  [*] MAC layer2 filter
 *      [**] After Enet_Init, MAC layer 2 filter is enabled as default configuration:
 *           UNICAST is filtered using perfect match with destination MAC address.
 *           MULTICAST is filtered using hash table match with destination MAC address.
 *      [**] You can modify the configuration by the following API:
 *           Enet_DefaultMACFilter : Get default configurations.
 *           Enet_GetMACFilter : Get current filter configurations.
 *           Enet_SetMACFilter : Set MAC layer 2 filter configurations.
 *      [**] Enet_SetMacHashTable
 *          If hash table filter is enabled, use Enet_SetMacHashTable to set hash table.
 *
 *  [*] MAC layer3 layer4 filter.There are 4 group of layer3 layer4 filters,
 *      and the filters must be enabled manually using the following API.
 *      Enet_DefaultL3L4Filter : Get layer3 layer4 filter default configurations.
 *      Enet_GetL3L4Filter : Get layer3 layer4 filter current configurations.
 *      Enet_SetL3L4Filter : Set layer3 layer4 filter configurations.
 *      Enet_EnableL3L4Filter : Enable layer3 layer4 filter.
 *
 *  [*] MAC VLAN filter.There are 4 groups of perfect filters,and a hash table filter.
 *      The VLAN perfect filter groups and hash table filter can be enabled simultaneously.
 *      [**]Complete the following steps To use MAC VLAN filter
 *          Enet_EnableVlanFilter : Enable VLAN filter with ENET_VlanFilterConfigType.
 *          Enet_SetVlanPerfectFilter : Set VLAN perfect filter configurations of any group.
 *          Enet_SetVlanHashTable: Add VLAN tag to hash table if VLAN hash table is enabled.
 *      [**] Get VLAN filter configurations and perfect filters parameters
 *          Enet_GetVlanFilterConfig : Get VLAN filter global configurations
 *          Enet_GetVlanPerfectFilter : Get VLAN perfect filter parameters of specified group.
 *
 *  [*] VLAN tag insertion delete replacement. There are two ways of transmit VLAN tag control.
 *      [**] Enabling VLAN insertion, replacement, or deletion for all packets.
 *          Enet_SetTxOuterVlanConfig : Set outer VLAN tag control configuration.
 *          Enet_SetTxInnerVlanConfig : Set inner VLAN tag control configuration.
 *          Enet_SetTxOuterVlanChannelBasedInsertion : Set channel based VLAN tag insertion.
 *
 *      [**] Enabling VLAN insertion, replacement, or deletion for selective packets controlled by DMA descriptors.
 *          Set Attributes of transmit frames with ENET_TX_ATTRIBUTES_INNER_VLAN_TAG_CTRL.
 *          Fill VlanConfig in ENET_TxOptionType.
 *          If use inner VLAN tag, set Attributes ENET_TX_ATTRIBUTES_INNER_VLAN_TAG_CTRL and
 *          fill InnerVlanConfig similarly.
 *          VLAN tag will be inserted delete of replaced when frames transmitted.
 *
 *********************************************************************************************************/

#include "module_driver_enet.h"

#if ENET_INSTANCE_COUNT > 0u

#ifndef ENET_DEV_ERROR_REPORT
#define ENET_DEV_ERROR_REPORT   STD_OFF
#endif

/** @brief PTP control poll wait timeout */
#define ENET_PTP_TIMEOUT_VALUE                  1000u
/** @brief MAC hash table index shift */
#define ENET_MAC_HASH_TABLE_INDEX_SHIFT         (37u - ENET_MAC_HASH_WIDTH_BITS)
/** @brief MAC hash table index mask */
#define ENET_MAC_HASH_TABLE_INDEX_MASK          (0x7u)
/** @brief MAC hash table bit shift */
#define ENET_MAC_HASH_TABLE_BIT_SHIFT           (32u - ENET_MAC_HASH_WIDTH_BITS)
/** @brief MAC hash table bit mask */
#define ENET_MAC_HASH_TABLE_BIT_MASK            (0x1Fu)
/** @brief VLAN hash table bit shift */
#define ENET_VLAN_HASH_TABLE_BIT_SHIFT          (32u - ENET_VLAN_HASH_WIDTH_BITS)
/** @brief VLAN hash table bit mask */
#define ENET_VLAN_HASH_TABLE_BIT_MASK           (0xFu)

static void Enet_SystemConfig(const ENET_ConfigType *pConfig);
static ENET_StatusType Enet_SoftwareReset(ENET_Type *pEnetBase);
static void Enet_DMAInit(ENET_HandleType *pEnetHandle, const ENET_DMAConfigType *pDmaConfig);
static void Enet_MACInit(ENET_HandleType *pEnetHandle, const ENET_MACConfigType *pMACConfig,
                         ENET_MAC_SpeedType eSpeed, ENET_MAC_DuplexModeType eDuplexMode);
static void Enet_MTL_SetRxQueueMap0(ENET_HandleType *pEnetHandle);
static void Enet_MTLInit(ENET_HandleType *pEnetHandle, const ENET_MTLConfigType *pMTLConfig);
static void Enet_DMATxDescInit(ENET_HandleType *pEnetHandle, const ENET_DescConfigType pTxDesc[]);
static inline void Enet_SetupRxDesc(ENET_DMADescType *pDesc, bool bItMode);
static void Enet_DMARxDescInit(ENET_HandleType *pEnetHandle, const ENET_DescConfigType pRxDesc[]);
static bool Enet_ReadTxDescTimestamp(ENET_HandleType *pEnetHandle, const ENET_DMADescType *pDesc, ENET_TimestampType *pTimestamp);
static void Enet_ReadRxDescTimestamp(ENET_HandleType *pEnetHandle, const ENET_DMADescType *pDesc, ENET_TimestampType *pTimestamp);
static inline ENET_DMADescType *Enet_NextDescriptor(ENET_DMADescType *pCurDesc, ENET_DescListType *pDescList);
static ENET_StatusType Enet_BuildTxDescriptors(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                               ENET_BufferType *pBuffers, ENET_TxOptionType *pOption);
static void Enet_ReleaseRxDescriptors(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                      ENET_DMADescType *pStart, ENET_DMADescType *pEnd);
static ENET_StatusType Enet_GetRxBuffers(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                         ENET_BufferType *pBuffers, ENET_RxInfoType *pInfo);
static ENET_StatusType Enet_MDIOWriteAddress(ENET_Type *pBase, bool bClause45, ENET_MiiOptType u8Opt, uint8_t u8PhyAddr,
                                             uint16_t u16PhyReg, uint8_t u8MmdAddr, uint16_t *pData, uint32_t u32TimeoutUs);
static void Enet_MacAddressConfig(ENET_Type *EnetBase, const uint8_t *pMacAddr, uint8_t u8MacLen);
static uint32_t Enet_ComputeCRC(const uint8_t *pData, uint32_t u32BitLen);
static inline uint32_t Enet_BitsReverse(uint32_t u32Data);
static inline void Enet_MACFilterConfig(ENET_Type *EnetBase, const ENET_MACFilterType *pMACFilter);
static ENET_StatusType Enet_VlanCtrlBusyPollWait(const ENET_Type *pEnetBase);
static ENET_StatusType Enet_VlanInclBusyPollWait(const ENET_Type *pEnetBase);
static ENET_StatusType Enet_VlanInclWrite(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                          ENET_MAC_VLANType eVlanType, uint16_t u16VlanTag);
static inline uint32_t Enet_PTPClockSourceConfig(ENET_Type *const pEnet,  const Enet_PTPConfigType *pPTPConfig);
static ENET_StatusType Enet_CheckPTPClockStepValid(const Enet_PTPConfigType *pPTPConfig, uint32_t u32ClkFreq);
static inline uint32_t Enet_PTPRegValue2Nanoseconds(uint32_t u32Subseconds);
static inline uint32_t Enet_PTPNanoseconds2RegValue(uint32_t u32Nanoseconds);
static void Enet_PTPSetIncrementValue(ENET_HandleType *pEnetHandle, const Enet_PTPConfigType *pPTPConfig, uint32_t PtpClkFreq);
static ENET_StatusType Enet_PTPCtrlPollWait(const ENET_Type *pEnetBase, uint32_t u32PollMask, uint32_t u32Timeout);
static inline ENET_StatusType Enet_PTPInitializeSystemTime(ENET_HandleType *pEnetHandle,
              ENET_MAC_TimestampRolloverType eRolloverMode, const ENET_TimestampType *pTime);
static void Enet_PTPSetIngressSyncCorrection(ENET_HandleType *pEnetHandle,
            ENET_MAC_TimestampRolloverType eRolloverMode, uint32_t PtpClkFreq);
static void Enet_PTPSetEgressSyncCorrection(ENET_HandleType *pEnetHandle,
            ENET_MAC_TimestampRolloverType eRolloverMode, uint32_t PtpClkFreq, bool bOneStep);
static void Enet_CalculatePPSIntervalWidth(ENET_HandleType *pEnetHandle,
            ENET_MAC_TimestampRolloverType eRolloverMode, uint32_t *pInterval, uint32_t *pWidth);
static ENET_StatusType Enet_PTPSetTargetTime(ENET_HandleType *pEnetHandle, ENET_MAC_PPSChannelType ePPSChannel,
                                ENET_MAC_TimestampRolloverType eRolloverMode, const ENET_TimestampType *pTime);
#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
static ENET_StatusType Enet_GclRead(ENET_Type *const pEnet, bool bGcrr, uint8_t u8Address, uint32_t *pData);
static ENET_StatusType Enet_GclWrite(ENET_Type *const pEnet, bool bGcrr, uint8_t u8Address, uint32_t u32Data);
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */
static void Enet_PTPIrqHandler(ENET_HandleType *pEnetHandle);
static void Enet_MMCIrqHandler(ENET_HandleType *pEnetHandle);
static void Enet_MACIrqHandler(ENET_HandleType *pEnetHandle);
static void Enet_MTLIrqHandler(ENET_HandleType *pEnetHandle);
static void Enet_DMAIrqHandler(ENET_HandleType *pEnetHandle, uint8_t u8Channel);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
#define ENET_ReportDevError(func, error) ReportDevError(ENET_MODULE_ID, func, error)

static uint32_t Enet_HandleInstanceCheck(const ENET_HandleType *pEnetHandle, uint16_t sid);
static uint32_t Enet_AssertMACConfiguration(const ENET_ConfigType *pConfig);
static uint32_t Enet_AssertMTLConfiguration(const ENET_ConfigType *pConfig);
static uint32_t Enet_AssertDMAConfiguration(const ENET_ConfigType *pConfig);
static uint32_t Enet_AssertConfiguration(const ENET_ConfigType *pConfig);
static uint32_t Enet_AssertDescBuffer(const ENET_DescConfigType *pTxDesc, uint8_t u8TxChannel,
                                      const ENET_DescConfigType *pRxDesc, uint8_t u8RxChannel);
static uint32_t Enet_AssertTxOption(const ENET_HandleType *pEnetHandle, const ENET_TxOptionType *pOption);
static uint32_t Enet_AssertMACFilterConfiguration(const ENET_MACFilterType *pMACFilter);
static uint32_t Enet_AssertL3L4FilterConfiguration(ENET_HandleType *pEnetHandle,
                                                   const ENET_L3L4FilterType *pL3L4Filter);
static uint32_t Enet_AssertVlanFilterConfiguration(const ENET_VlanFilterConfigType *pVlanFilterConfig);
static uint32_t Enet_AssertVlanPerfectFilterConfiguration(const ENET_VlanPerfectFilterType *pPerfectFilter);
static uint32_t Enet_AssertVlanChannelBasedInsConfiguration(ENET_HandleType *pEnetHandle,
                                                            const ENET_OuterVlanCBTIType *pVlanConfig);
static uint32_t Enet_AssertPTPConfiguration(const Enet_PTPConfigType *pPTPConfig);
static uint32_t Enet_AssertFlowControlConfiguration(const ENET_HandleType *pEnetHandle,
                                                    const ENET_FlowControlType *pFlowControl);
#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
static uint32_t Enet_AssertEstConfiguration(const ENET_EstConfigType *pEstConfig);
static uint32_t Enet_AssertGclConfiguration(const ENET_GateCtrlListType *pGatelist);
static uint32_t Enet_AssertPreemptionConfiguration(const ENET_PreemptionConfigType *pConfig);
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief                       : ENET handle and instance number development check
 * @param[in] pEnetHandle       : ENET driver handle
 * @param[in] sid               : The service id of caller
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  No development error
 * @retval ENET_STATUS_ERROR    A development error detected
 */
static uint32_t Enet_HandleInstanceCheck(const ENET_HandleType *pEnetHandle, uint16_t sid)
{
    uint32_t ret = 1u;

    if (pEnetHandle == NULL_PTR)
    {
        ENET_ReportDevError(sid, ENET_E_PARAM_HANDLE);
    }
    else
    {
        if (pEnetHandle->eInstance >= ENET_INSTANCE_COUNT)
        {
            ENET_ReportDevError(sid, ENET_E_PARAM_INSTANCE);
        }
        else
        {
            ret = 0u;
        }
    }
    return ret;
}

/**
 * @brief                       : Assert ENET configurations
 * @param[in] pConfig           : ENET configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertMACConfiguration(const ENET_ConfigType *pConfig)
{
    const ENET_MACConfigType *pMACConfig = &pConfig->MACConfig;
    uint32_t err;

    err = Enet_AssertMACFilterConfiguration(&pMACConfig->MACFilter);
    err |= ((pMACConfig->SrcAddrCtrl != ENET_MAC_SRC_ADDR_CTRL_BY_INPUT_SIGNAL) &&
            (pMACConfig->SrcAddrCtrl != ENET_MAC_SRC_ADDR_INSERT_BY_MAC_ADDR_IDX_0) &&
            (pMACConfig->SrcAddrCtrl != ENET_MAC_SRC_ADDR_REPLACE_BY_MAC_ADDR_IDX_0) &&
            (pMACConfig->SrcAddrCtrl != ENET_MAC_SRC_ADDR_INSERT_BY_MAC_ADDR_IDX_1) &&
            (pMACConfig->SrcAddrCtrl != ENET_MAC_SRC_ADDR_REPLACE_BY_MAC_ADDR_IDX_1)) ? 1u : 0u;
    err |= ((uint32_t)pMACConfig->InterPacketGap > (uint32_t)ENET_MAC_INTER_PACKET_GAP_40_BIT) ? 1u : 0u;
    err |= ((uint32_t)pMACConfig->BackOffLimit > (uint32_t)ENET_MAC_BACK_OFF_LIMIT_1_SLOT) ? 1u : 0u;
    err |= ((uint32_t)pMACConfig->ExtInterPktGap > (uint32_t)ENET_MAC_EXT_INTER_PACKET_GAP_352_BIT) ? 1u : 0u;
    err |= ((uint32_t)pMACConfig->GiantPktSizeLimit > 0x3FFFu) ? 1u : 0u;
    err |= ((uint32_t)pMACConfig->WatchdogTimeout > (uint32_t)ENET_MAC_WDG_TIMER_SIZE_15KB) ? 1u : 0u;

    return err;
}

/**
 * @brief                       : Assert ENET configurations
 * @param[in] pConfig           : ENET configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertMTLConfiguration(const ENET_ConfigType *pConfig)
{
    const ENET_MTLQueueConfigType *pMtlQueueCfg;
    uint8_t u8Channel;
    uint32_t err;
    uint32_t u32TotalSize;

    err = ((pConfig->MTLConfig.TxSchedAlgo != ENET_MTL_SCHED_ALGO_WRR) &&
           (pConfig->MTLConfig.TxSchedAlgo != ENET_MTL_SCHED_ALGO_SP)) ? 1u : 0u;
    err |= ((uint32_t)pConfig->MTLConfig.RxArbitrationAlgo > (uint32_t)ENET_MTL_RX_ARBITRATION_WEIGHTED_STRICT_POLICY) ? 1u : 0u;

    /* Transmit queue */
    u32TotalSize = 0u;
    for (u8Channel = 0u; u8Channel < pConfig->TxChannelCount; ++u8Channel)
    {
        pMtlQueueCfg = &(pConfig->MTLConfig.QueueConfigs[u8Channel]);

        err |= ((pMtlQueueCfg->TxFifoSize % 256u) != 0u) ? 1u : 0u;
        u32TotalSize += pMtlQueueCfg->TxFifoSize;

        err |= (uint32_t)((uint32_t)pMtlQueueCfg->TxQueueEnable > (uint32_t)ENET_MTL_QUEUE_ENABLE_GENERIC);
        err |= (uint32_t)(((uint32_t)pMtlQueueCfg->TxThreshold > (uint32_t)ENET_MTL_TX_THRESHOLD_256B) &&
                          (pMtlQueueCfg->TxThreshold != ENET_MTL_TX_STORE_FORWARD));

        if ((pMtlQueueCfg->TxQueueEnable == ENET_MTL_QUEUE_ENABLE_GENERIC) &&
           (pConfig->MTLConfig.TxSchedAlgo == ENET_MTL_SCHED_ALGO_WRR))
        {
            err |= ((pMtlQueueCfg->IdleSlopeQuantumWeight == 0u) || (pMtlQueueCfg->IdleSlopeQuantumWeight > 0x64u)) ? 1u : 0u;
        }
        if (pMtlQueueCfg->TxQueueEnable == ENET_MTL_QUEUE_ENABLE_AV_MODE)
        {
            err |= (pMtlQueueCfg->IdleSlopeQuantumWeight > 0x3FFFu) ? 1u : 0u;
            err |= (pMtlQueueCfg->SendSlopeCredit > 0x3FFFu) ? 1u : 0u;
            err |= (pMtlQueueCfg->HiCredit > 0x1FFFFFFFu) ? 1u : 0u;
            err |= (pMtlQueueCfg->LoCredit > 0x1FFFFFFF) ? 1u : 0u;
        }
    }
    err |= (u32TotalSize > ENET_MTL_TX_FIFO_SIZE) ? 1u : 0u;

    /* Receive queue */
    u32TotalSize = 0u;
    for (u8Channel = 0u; u8Channel < pConfig->RxChannelCount; ++u8Channel)
    {
        pMtlQueueCfg = &(pConfig->MTLConfig.QueueConfigs[u8Channel]);

        err |= ((pMtlQueueCfg->RxFifoSize % 256u) != 0u) ? 1u : 0u;
        u32TotalSize += pMtlQueueCfg->RxFifoSize;

        err |= ((uint32_t)pMtlQueueCfg->RxDeactiveThreshold > (uint32_t)ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_8_5_KB) ? 1u : 0u;
        err |= ((uint32_t)pMtlQueueCfg->RxActiveThreshold > (uint32_t)ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_8_5_KB) ? 1u : 0u;
        err |= (((uint32_t)pMtlQueueCfg->RxThreshold > ENET_MTL_RX_THRESHOLD_128B) &&
                           (pMtlQueueCfg->RxThreshold != ENET_MTL_RX_STORE_FORWARD)) ? 1u : 0u;
        err |= ((uint32_t)pMtlQueueCfg->RxQueueWeight >= (uint32_t)(1u << ENET_MTL_RXQ0_CONTROL_RXQ_WEGT_WIDTH)) ? 1u : 0u;
        err |= ((pMtlQueueCfg->RxQueueEnable != ENET_MTL_QUEUE_DISABLE) &&
                (pMtlQueueCfg->RxQueueEnable != ENET_MTL_QUEUE_ENABLE_GENERIC)) ? 1u : 0u;
    }
    err |= (u32TotalSize > ENET_MTL_RX_FIFO_SIZE) ? 1u : 0u;

    return err;
}

/**
 * @brief                       : Assert ENET configurations
 * @param[in] pConfig           : ENET configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertDMAConfiguration(const ENET_ConfigType *pConfig)
{
    const ENET_DMAChannelConfigType *pDMAChannelCfg;
    uint8_t u8Channel;
    uint32_t err;

    err = ((pConfig->DMAConfig.PriorityMode != ENET_DMA_PRIORITY_MODE_RX_TX) &&
            (pConfig->DMAConfig.PriorityMode != ENET_DMA_PRIORITY_MODE_TX_RX)) ? 1u : 0u;
    err |= ((uint32_t)pConfig->DMAConfig.PriorityRatio > (uint32_t)ENET_DMA_PRIORITY_RATIO_8_1) ? 1u : 0u;
    err |= ((uint32_t)pConfig->DMAConfig.TxArbitration > (uint32_t)ENET_DMA_TX_ARBITRATION_ALGORITHM_WEIGHTED_ROUND_ROBIN) ? 1u : 0u;
    err |= ((uint32_t)pConfig->DMAConfig.TxRxArbitration > (uint32_t)ENET_DMA_TXRX_ARBITRATION_SCHEME_FIXED_PRIORITY) ? 1u : 0u;
    err |= ((pConfig->DMAConfig.BurstMode != ENET_BURSTLENGTH_FIXED) && (pConfig->DMAConfig.BurstMode != ENET_BURSTLENGTH_MIXED)) ? 1u : 0u;

    for (u8Channel = 0u; u8Channel < pConfig->TxChannelCount; ++u8Channel)
    {
        pDMAChannelCfg = &(pConfig->DMAConfig.ChannelConfigs[u8Channel]);
        err |= ((pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_1_BEAT) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_2_BEATS) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_4_BEATS) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_8_BEATS) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_16_BEATS) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_32_BEATS) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_64_BEATS) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_128_BEATS) &&
                (pDMAChannelCfg->BurstLength != ENET_DMA_BURST_LENGTH_256_BEATS)) ? 1u : 0u;
        err |= ((uint32_t)pDMAChannelCfg->TxChannelWeight >= (uint32_t)(1u << ENET_DMA_CH0_TX_CONTROL_TCW_WIDTH)) ? 1u : 0u;
    }

    return err;
}

/**
 * @brief                       : Assert ENET configurations
 * @param[in] pConfig           : ENET configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertConfiguration(const ENET_ConfigType *pConfig)
{
    uint32_t err = 0u;

    /* Assert buffers configuration */
    err = Enet_AssertDescBuffer(pConfig->TxBD, pConfig->TxChannelCount, pConfig->RxBD, pConfig->RxChannelCount);

    err |= ((pConfig->MiiMode != ENET_MAC_PHY_MII)
#if ENET_SUPPORT_RMII
            && (pConfig->MiiMode != ENET_MAC_PHY_RMII)
#endif
#if ENET_SUPPORT_RGMII
            && (pConfig->MiiMode != ENET_MAC_PHY_RGMII)
#endif
            ) ? 1u : 0u;

#if ENET_SUPPORT_RGMII
    err |= ((pConfig->MiiMode == ENET_MAC_PHY_RGMII) &&
            (pConfig->RgmiiClk != ENET_MAC_RGMII_CLK_SEL_ENET_REF_CLK) &&
            (pConfig->RgmiiClk != ENET_MAC_RGMII_CLK_SEL_PLL0DIVH) &&
            (pConfig->RgmiiClk != ENET_MAC_RGMII_CLK_SEL_PLL1DIVH)) ? 1u : 0u;
#endif

    err |= (uint32_t)((pConfig->Speed != ENET_MAC_SPEED_100MBPS) &&
#if ENET_SUPPORT_1000MBPS
            (pConfig->Speed != ENET_MAC_SPEED_1000MBPS) &&
#endif
            (pConfig->Speed != ENET_MAC_SPEED_10MBPS)) ? 1u : 0u;
    err |= ((pConfig->Duplex != ENET_MAC_FULL_DUPLEX) && (pConfig->Duplex != ENET_MAC_HALF_DUPLEX)) ? 1u : 0u;

    /* Assert Mii configuration */
    err |= ((uint32_t)pConfig->MiiConfig.TrailingClocks > (1u << ENET_MAC_MDIO_ADDRESS_NTC_WIDTH)) ? 1u : 0u;
    err |= ((pConfig->MiiConfig.TrailingClocks == 0u) && (pConfig->MiiConfig.BackToBack == true)) ? 1u : 0u;

    err |= Enet_AssertMACConfiguration(pConfig);
    err |= Enet_AssertMTLConfiguration(pConfig);
    err |= Enet_AssertDMAConfiguration(pConfig);

    return (ENET_StatusType)err;
}

/**
 * @brief                       Assert the ENET DMA descriptors parameters
 * @param[in] pTxDesc           TX descriptors configure structure
 * @param[in] u8TxChannel       The number of DMA RX channels to use
 * @param[in] pRxDesc           RX descriptors configure structure
 * @param[in] u8RxChannel       The number of DMA TX channels to use
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertDescBuffer(const ENET_DescConfigType *pTxDesc, uint8_t u8TxChannel,
                                      const ENET_DescConfigType *pRxDesc, uint8_t u8RxChannel)
{
    uint8_t u8Channel;
    uint32_t err = 0u;

    for (u8Channel = 0u; u8Channel < u8TxChannel; ++u8Channel)
    {
        if ((pTxDesc[u8Channel].DescList == NULL_PTR) ||
            (pTxDesc[u8Channel].RingSize < 4u) ||
            (pTxDesc[u8Channel].BufferLen > ENET_MAX_FRAME_LENGTH))
        {
            err = 1u;
            break;
        }
    }

    for (u8Channel = 0u; u8Channel < u8RxChannel; ++u8Channel)
    {
        if ((pRxDesc[u8Channel].DescList == NULL_PTR) ||
            (pRxDesc[u8Channel].Buffer == NULL_PTR)   ||
            (pRxDesc[u8Channel].RingSize <= 2u)       ||
            ((pRxDesc[u8Channel].BufferLen % ENET_DATA_BUS_WIDTH_BYTES) != 0u))
        {
            err = 1u;
            break;
        }
    }
    return err;
}

/**
 * @brief                       Assert the ENET transmit option parameters
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pOption           Transmit option parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertTxOption(const ENET_HandleType *pEnetHandle, const ENET_TxOptionType *pOption)
{
    uint32_t err = 0u;

    if (pOption != NULL_PTR)
    {
        if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_CRC_PAD_CTRL))
        {
            err |= (pOption->CrcPadCtrl > ENET_CRC_REPLACEMENT) ? 1u : 0u;
        }
        if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_CHECKSUM_INSERTION))
        {
            err |= (pOption->CheckSumCtrl > ENET_CHECKSUM_INSERTION_PROTO_PSEUDOH) ? 1u : 0u;
#if (0 == ENET_ALL_TXQUEUES_SUPPORT_CHECKSUM)
            err |= (pEnetHandle->TxChannelCount > 1u) ? 1u : 0u;
#else
            (void)pEnetHandle;
#endif
        }
        if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_VLAN_TAG_CTRL))
        {
            err |= ((uint32_t)pOption->VlanConfig.VlanCtrl > (uint32_t)ENET_MAC_VLAN_TAG_REPLACEMENT) ? 1u : 0u;
            err |= ((pOption->VlanConfig.VlanType != ENET_MAC_VLAN_TYPE_C_VLAN) &&
                    (pOption->VlanConfig.VlanType != ENET_MAC_VLAN_TYPE_S_VLAN)) ? 1u : 0u;
        }
        if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_INNER_VLAN_TAG_CTRL))
        {
            err |= ((uint32_t)pOption->InnerVlanConfig.VlanCtrl > (uint32_t)ENET_MAC_VLAN_TAG_REPLACEMENT) ? 1u : 0u;
            err |= ((pOption->InnerVlanConfig.VlanType != ENET_MAC_VLAN_TYPE_C_VLAN) &&
                    (pOption->InnerVlanConfig.VlanType != ENET_MAC_VLAN_TYPE_S_VLAN)) ? 1u : 0u;
        }
    }
    return err;
}

/**
 * @brief                       Assert MAC filter configurations
 * @param[in] pMACFilter        MAC filter Configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertMACFilterConfiguration(const ENET_MACFilterType *pMACFilter)
{
    uint32_t err;

    err = ((uint32_t)pMACFilter->PassCtrlPkts > (uint32_t)ENET_MAC_CTRL_PACKET_ADDR_FILTER) ? 1u : 0u;
    err |= ((uint32_t)pMACFilter->SAFilter > (uint32_t)ENET_FILTER_INVERSE_ENABLE) ? 1u : 0u;
    err |= ((uint32_t)pMACFilter->DAFilter > (uint32_t)ENET_FILTER_INVERSE_ENABLE) ? 1u : 0u;
    return err;
}

/**
 * @brief                       Assert layer3 layer4 filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pL3L4Filter       Layer3 layer4 filter configurations
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertL3L4FilterConfiguration(ENET_HandleType *pEnetHandle,
                                                   const ENET_L3L4FilterType *pL3L4Filter)
{
    uint32_t err = 0u;

    if (pL3L4Filter->DMAChannelSelect)
    {
        err |= (pL3L4Filter->DMAChannel >= pEnetHandle->RxChannelCount) ? 1u : 0u;
    }
    err |= ((pL3L4Filter->L4Protocol != ENET_MAC_LAYER_4_PROTOCOL_TCP) &&
            (pL3L4Filter->L4Protocol != ENET_MAC_LAYER_4_PROTOCOL_UDP)) ? 1u : 0u;
    err |= ((uint32_t)pL3L4Filter->DstPortFilter > (uint32_t)ENET_FILTER_INVERSE_ENABLE) ? 1u : 0u;
    err |= ((uint32_t)pL3L4Filter->SrcPortFilter > (uint32_t)ENET_FILTER_INVERSE_ENABLE) ? 1u : 0u;

    err |= ((pL3L4Filter->L3Protocol != ENET_MAC_LAYER_3_PROTOCOL_IPV4) &&
            (pL3L4Filter->L3Protocol != ENET_MAC_LAYER_3_PROTOCOL_IPV6)) ? 1u : 0u;
    err |= ((uint32_t)pL3L4Filter->DstIPFilter > (uint32_t)ENET_FILTER_INVERSE_ENABLE) ? 1u : 0u;
    err |= ((uint32_t)pL3L4Filter->SrcIPFilter > (uint32_t)ENET_FILTER_INVERSE_ENABLE) ? 1u : 0u;
    if (pL3L4Filter->L3Protocol == ENET_MAC_LAYER_3_PROTOCOL_IPV4)
    {
        err |= (pL3L4Filter->Ipv4DAMaskBit > 31u) ? 1u : 0u;
        err |= (pL3L4Filter->Ipv4SAMaskBit > 31u) ? 1u : 0u;
    }
    else
    {
        err |= (pL3L4Filter->Ipv6MaskBit > 127u) ? 1u : 0u;
    }
    return err;
}

/**
 * @brief                       Assert MAC VLAN filter configurations
 * @param[in] pVlanFilterConfig MAC VLAN filter configurations
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertVlanFilterConfiguration(const ENET_VlanFilterConfigType *pVlanFilterConfig)
{
    uint32_t err = 0u;

    err |= ((uint32_t)pVlanFilterConfig->InnerVlanStrip > (uint32_t)ENET_MAC_VLAN_TAG_STRIP_ALWAYS) ? 1u : 0u;
    err |= ((uint32_t)pVlanFilterConfig->OuterVlanStrip > (uint32_t)ENET_MAC_VLAN_TAG_STRIP_ALWAYS) ? 1u : 0u;
    err |= ((uint32_t)pVlanFilterConfig->HashFilterMode > (uint32_t)ENET_VLAN_FILTER_INNER_ANYTYPE) ? 1u : 0u;
    err |= ((pVlanFilterConfig->HashCompareMode !=  ENET_MAC_VLAN_16BITS_COMPARE) &&
            (pVlanFilterConfig->HashCompareMode !=  ENET_MAC_VLAN_12BITS_COMPARE)) ? 1u : 0u;
    return err;
}

/**
 * @brief                       Assert VLAN perfect filter configurations
 * @param[in] pPerfectFilter    VLAN perfect filter configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertVlanPerfectFilterConfiguration(const ENET_VlanPerfectFilterType *pPerfectFilter)
{
    uint32_t err = 0u;

    err |= (((uint32_t)pPerfectFilter->DMAChannel > (uint32_t)ENET_CHANNEL_1)) ? 1u : 0u;
    err |= ((uint32_t)pPerfectFilter->FilterMode > (uint32_t)ENET_VLAN_FILTER_INNER_ANYTYPE) ? 1u : 0u;
    return err;
}

/**
 * @brief                       Assert VLAN  perfect filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanConfig       VLAN perfect filter configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertVlanChannelBasedInsConfiguration(ENET_HandleType *pEnetHandle,
                                                            const ENET_OuterVlanCBTIType *pVlanConfig)
{
    uint8_t u8Channel;
    uint32_t err = 0u;

    for(u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
    {
        if ((pVlanConfig->VlanType[u8Channel] != ENET_MAC_VLAN_TYPE_C_VLAN) &&
            (pVlanConfig->VlanType[u8Channel] != ENET_MAC_VLAN_TYPE_S_VLAN))
        {
            err = 1u;
            break;
        }
    }
    return err;
}

/**
 * @brief                       Assert the PTP configure parameters
 * @param[in] pPTPConfig        PTP default configurations
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertPTPConfiguration(const Enet_PTPConfigType *pPTPConfig)
{
    uint32_t err = 0u;

    err |= ((pPTPConfig->TXTSSTSM != ENET_MAC_TX_TIMESTAMP_STATUS_MODE_PRESERVE) &&
            (pPTPConfig->TXTSSTSM != ENET_MAC_TX_TIMESTAMP_STATUS_MODE_OVERWRITE)) ? 1u : 0u;

    err |= ((pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_E2E)               &&
            (pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_SYNC)              &&
            (pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_DELAYREQ)          &&
            (pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_ALL_PTP)           &&
            (pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_SLAVE_NODE_EVENT)  &&
            (pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_MASTER_NODE_EVENT) &&
            (pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_E2E_EVENT)         &&
            (pPTPConfig->SnapshotType != ENET_MAC_PTP_SNAPSHOT_FOR_P2P_EVENT)) ? 1u : 0u;

    err |= ((pPTPConfig->PtpLayer != ENET_MAC_PTP_OVER_ETHERNET) &&
            (pPTPConfig->PtpLayer != ENET_MAC_PTP_OVER_IPV4)     &&
            (pPTPConfig->PtpLayer != ENET_MAC_PTP_OVER_IPV6)) ? 1u : 0u;

    err |= ((pPTPConfig->PtpVersion != ENET_MAC_PTP_IEEE_1588_V1) &&
            (pPTPConfig->PtpVersion != ENET_MAC_PTP_IEEE_1588_V2)) ? 1u : 0u;

    err |= ((pPTPConfig->RolloverMode != ENET_MAC_TIMESTAMP_ROLLOVER_BINARY) &&
            (pPTPConfig->RolloverMode != ENET_MAC_TIMESTAMP_ROLLOVER_DIGITAL)) ? 1u : 0u;

    err |= ((pPTPConfig->UpdateMethod != ENET_MAC_TIMESTAMP_UPDATE_COARSE) &&
            (pPTPConfig->UpdateMethod != ENET_MAC_TIMESTAMP_UPDATE_FINE)) ? 1u : 0u;

    err |= ((pPTPConfig->ClkSource != ENET_MAC_PTP_CLK_SEL_PCC) &&
            (pPTPConfig->ClkSource != ENET_MAC_PTP_CLK_SEL_TX_CLK)
#if ENET_SUPPORT_REFCLK_PIN
            && (pPTPConfig->ClkSource != ENET_MAC_PTP_CLK_SEL_REFCLK_PIN)
#endif
           ) ? 1u : 0u;

    /* Due to the bug in 5.20a errata, the MAC unable to identify PTP SYNC and Follow_Up Messages
       with Peer Delay Reserved Multicast Address in the 802.1AS Mixed Mode, therefore,
       enable timestamp for all packets(MAC_TIMESTAMP_CONTROL[8]) must be enabled. */
    if ((pPTPConfig->Av8021ASMode == true) && (pPTPConfig->TimeStampForAll == false))
    {
        err = 1u;
    }

    return err;
}

/**
 * @brief                       Assert flow control configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFlowControl      MAC flow control Configure parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertFlowControlConfiguration(const ENET_HandleType *pEnetHandle,
                                                    const ENET_FlowControlType *pFlowControl)
{
    const ENET_FlowControlRxQType *pFlowCtrlRxQCfg;
    uint32_t u8Channel;
    uint32_t err = 0u;

    err |= ((uint32_t)pFlowControl->PauseThreshold > (uint32_t)ENET_MAC_PAUSE_THRESHOLD_512SLOT_TIMES) ? 1u : 0u;

    for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
    {
        pFlowCtrlRxQCfg = &(pFlowControl->RxQueueConfig[u8Channel]);
        err |= ((uint32_t)pFlowCtrlRxQCfg->RxDeactiveThreshold > (uint32_t)ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_8_5_KB) ? 1u : 0u;
        err |= ((uint32_t)pFlowCtrlRxQCfg->RxActiveThreshold > (uint32_t)ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_8_5_KB) ? 1u : 0u;
    }
    return (ENET_StatusType)err;
}

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief                       Assert Enhancements to Scheduled Traffic configurations
 * @param[in] pEstConfig        Enhancements to Scheduled Traffic Configuration parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertEstConfiguration(const ENET_EstConfigType *pEstConfig)
{
    uint32_t err = 0u;

    err |= ((uint32_t)pEstConfig->CurrentTimeOffset > (uint32_t)4096u) ? 1u : 0u;
    err |= ((uint32_t)pEstConfig->IntervalLeftShift > (uint32_t)ENET_MTL_GCL_INTERVAL_X_128) ? 1u : 0u;
    err |= ((uint32_t)pEstConfig->SchedErrLoopCount > (uint32_t)ENET_MTL_GCL_32_ITERATIONS) ? 1u : 0u;
    err |= ((uint32_t)pEstConfig->Overhead > (uint32_t)64u) ? 1u : 0u;

    /* Due to the bug in 5.20a errata, the HLBS or HLBF may be detected incorrectly, and the packets
       may be dropped, therefore, DropSchedErrFrame must be false, NotDropFrameSizeErr must be true. */
    if ((pEstConfig->DropSchedErrFrame == true) || (pEstConfig->NotDropFrameSizeErr == false))
    {
        err = 1u;
    }

    return err;
}

/**
 * @brief                       Assert Gate control list configurations
 * @param[in] pGatelist         Gate control list Configuration parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertGclConfiguration(const ENET_GateCtrlListType *pGatelist)
{
    uint32_t err = 0u;
    uint32_t i;

    if (pGatelist->GclLength > ENET_TSN_GCL_DEPTH)
    {
        err = 1u;
    }
    else
    {
        for (i = 0u; i < pGatelist->GclLength; ++i)
        {
            if (pGatelist->Gate[i].TimeInterval >= (1u << ENET_TSN_GCL_INTERVAL_WIDTH_BITS))
            {
                err = 1u;
                break;
            }
        }
    }
    return err;
}

/**
 * @brief                       Assert Preemption configurations
 * @param[in] pConfig           Preemption Configuration parameters
 * @return                      uint32_t
 * @retval 0                    No error in parameters
 * @retval None-zero            An error is detected in parameters
 */
static uint32_t Enet_AssertPreemptionConfiguration(const ENET_PreemptionConfigType *pConfig)
{
    uint32_t err = 0u;
    uint32_t i;

    if (pConfig->PreemptionEnable)
    {
        for (i = 0u; i < ENET_CHANNEL_COUNT; ++i)
        {
            if ((uint32_t)pConfig->Classification[i] > (uint32_t)ENET_CLISSIFICATION_PREEMPTABLE)
            {
                err = 1u;
                break;
            }
        }
    }

    return err;
}
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

#endif /* ENET_DEV_ERROR_REPORT */

/**
 * @brief                       Ethernet system control configuration.
 * @details                     Set the system control in the system module.
 * @param[in] pConfig           ENET configuration parameters
 */
static void Enet_SystemConfig(const ENET_ConfigType *pConfig)
{
    ENET_HWA_Sysctrl_SetPhyMiiMode(pConfig->MiiMode);

#if ENET_SUPPORT_RGMII
    if (pConfig->MiiMode == ENET_MAC_PHY_RGMII)
    {
        ENET_HWA_Sysctrl_SetRGMIIClockSrc(pConfig->RgmiiClk);
        ENET_HWA_Sysctrl_SetTxClockSrc(ENET_MAC_TX_CLK_SEL_ENET_TX_CLK);
        ENET_HWA_Sysctrl_SetMiiTxClkOutputEnFlag(ENET_TRUE);
    }
#endif
}

/**
 * @brief                       Ethernet controller soft reset.
 * @details                     Reset the logic and all internal registers of the DMA, MTL, and MAC.
 * @param[in] pEnetBase         ENET controller register base address
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  The reset operation is complete
 * @retval ENET_STATUS_TIMEOUT  The reset operation is failed
 */
static ENET_StatusType Enet_SoftwareReset(ENET_Type *pEnetBase)
{
    uint32_t u32Tmo = 1500u;

    ENET_HWA_DMA_SwReset(pEnetBase);
    while ((ENET_HWA_DMA_GetSwResetStatus(pEnetBase) != ENET_DMA_STATUS_IDLE) && (u32Tmo > 0u))
    {
        --u32Tmo;
    }
    return (u32Tmo == 0u) ? ENET_STATUS_TIMEOUT : ENET_STATUS_SUCCESS;
}

/**
 * @brief                       Initializes the ENET DMA
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pDmaConfig        ENET DMA configuration structure
 */
static void Enet_DMAInit(ENET_HandleType *pEnetHandle, const ENET_DMAConfigType *pDmaConfig)
{
    uint8_t u8Channel, u8SkipLen, u8RingCount, u8BurstLength;

    ENET_HWA_DMA_SetInterruptMode(pEnetHandle->EnetBase, ENET_DMA_INTM_SBD_PERCH_LEVEL);
    ENET_HWA_DMA_SetPriorityMode(pEnetHandle->EnetBase, pDmaConfig->PriorityMode);
    ENET_HWA_DMA_SetPriorityRatio(pEnetHandle->EnetBase, pDmaConfig->PriorityRatio);
    ENET_HWA_DMA_SetTxArbitrationAlgorithm(pEnetHandle->EnetBase, pDmaConfig->TxArbitration);
    ENET_HWA_DMA_SetTxRxArbitrationScheme(pEnetHandle->EnetBase, pDmaConfig->TxRxArbitration);

    ENET_HWA_DMA_SetRebuildINCRxBurstEnFlag(pEnetHandle->EnetBase, pDmaConfig->RebuildINCRxBurst);
    ENET_HWA_DMA_SetAddressAlignedBeatsEnFlag(pEnetHandle->EnetBase, pDmaConfig->AddressAlignedBeats);
    if (pDmaConfig->BurstMode == ENET_BURSTLENGTH_FIXED)
    {
        ENET_HWA_DMA_SetFixedBurstLengthEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
    }
    else
    {
        ENET_HWA_DMA_SetMixedBurstEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
    }

    u8SkipLen = (uint8_t)(sizeof(ENET_DMADescType) - ENET_DMA_DESC_LEN_BYTES) / ENET_DATA_BUS_WIDTH_BYTES;
    u8RingCount = (pEnetHandle->TxChannelCount >= pEnetHandle->RxChannelCount) ? pEnetHandle->TxChannelCount : pEnetHandle->RxChannelCount;

    for (u8Channel = 0; u8Channel < u8RingCount; ++u8Channel)
    {
        ENET_HWA_DMA_SetDescriptorSkipLength(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, u8SkipLen);
        ENET_HWA_DMA_SetEnabledInterrupts(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, 0u);

        if ((uint32_t)pDmaConfig->ChannelConfigs[u8Channel].BurstLength > 32u)
        {
            u8BurstLength = (uint8_t)((uint32_t)pDmaConfig->ChannelConfigs[u8Channel].BurstLength / 8u);
            ENET_HWA_DMA_Set8xPBLModeEnFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_TRUE);
        }
        else
        {
            u8BurstLength = (uint8_t)pDmaConfig->ChannelConfigs[u8Channel].BurstLength;
            ENET_HWA_DMA_Set8xPBLModeEnFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_FALSE);

        }
        if (u8Channel < pEnetHandle->TxChannelCount)
        {
            ENET_HWA_DMA_SetEnhancedDescriptorEnFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_FALSE);
            ENET_HWA_DMA_SetEarlyTxIntEnFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                             pDmaConfig->ChannelConfigs[u8Channel].EarlySendIntEnable);
            ENET_HWA_DMA_SetTxBurstLength(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, u8BurstLength);
            ENET_HWA_DMA_SetOperateOnSecondPacketEnFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                                        pDmaConfig->ChannelConfigs[u8Channel].OperateSecondPacket);
            ENET_HWA_DMA_SetTxChannelWeight(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                            pDmaConfig->ChannelConfigs[u8Channel].TxChannelWeight);
        }
        if (u8Channel < pEnetHandle->RxChannelCount)
        {
            ENET_HWA_DMA_SetRxPacketFlushEnFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_TRUE);
            ENET_HWA_DMA_SetEarlyRxIntEnFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                             pDmaConfig->ChannelConfigs[u8Channel].EarlyReceiveIntEnable);
            ENET_HWA_DMA_SetRxBurstLength(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, u8BurstLength);
        }
    }
}

/**
 * @brief                       Initializes the ENET MAC
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMACConfig        ENET MAC configuration structure
 * @param[in] eSpeed            ENET MAC connection speed
 * @param[in] eDuplexMode       ENET MAC connection duplex mode
 */
static void Enet_MACInit(ENET_HandleType *pEnetHandle, const ENET_MACConfigType *pMACConfig,
                         ENET_MAC_SpeedType eSpeed, ENET_MAC_DuplexModeType eDuplexMode)
{
    uint32_t u32RegValue;

    pEnetHandle->EnetBase->MAC_INTERRUPT_ENABLE = 0u;
    pEnetHandle->EnetBase->MMC_RX_INTERRUPT_MASK = 0xFFFFFFFFu;
    pEnetHandle->EnetBase->MMC_TX_INTERRUPT_MASK = 0xFFFFFFFFu;

    u32RegValue = pEnetHandle->EnetBase->MAC_CONFIGURATION;
    u32RegValue &= ~(ENET_MAC_CONFIGURATION_SARC_MASK   |
                     ENET_MAC_CONFIGURATION_IPC_MASK    |
                     ENET_MAC_CONFIGURATION_IPG_MASK    |
                     ENET_MAC_CONFIGURATION_GPSLCE_MASK |
                     ENET_MAC_CONFIGURATION_S2KP_MASK   |
                     ENET_MAC_CONFIGURATION_CST_MASK    |
                     ENET_MAC_CONFIGURATION_ACS_MASK    |
                     ENET_MAC_CONFIGURATION_WD_MASK     |
                     ENET_MAC_CONFIGURATION_JD_MASK     |
                     ENET_MAC_CONFIGURATION_JE_MASK     |
                     ENET_MAC_CONFIGURATION_LM_MASK     |
                     ENET_MAC_CONFIGURATION_ECRSFD_MASK |
                     ENET_MAC_CONFIGURATION_DO_MASK     |
                     ENET_MAC_CONFIGURATION_DCRS_MASK   |
                     ENET_MAC_CONFIGURATION_DR_MASK     |
                     ENET_MAC_CONFIGURATION_BL_MASK     |
                     ENET_MAC_CONFIGURATION_DC_MASK     |
                     ENET_MAC_CONFIGURATION_TE_MASK     |
                     ENET_MAC_CONFIGURATION_RE_MASK);

    u32RegValue |= ENET_MAC_CONFIGURATION_SARC(pMACConfig->SrcAddrCtrl)                      |
                   ENET_MAC_CONFIGURATION_IPC(pMACConfig->ChecksumOffload ? 1u : 0u)         |
                   ENET_MAC_CONFIGURATION_IPG(pMACConfig->InterPacketGap)                    |
                   ENET_MAC_CONFIGURATION_GPSLCE(pMACConfig->GiantPacketLimit ? 1u : 0u)     |
                   ENET_MAC_CONFIGURATION_S2KP(pMACConfig->Support2KPacket ? 1u : 0u)        |
                   ENET_MAC_CONFIGURATION_CST(pMACConfig->CrcStripForTypePkt ? 1u : 0u)      |
                   ENET_MAC_CONFIGURATION_ACS(pMACConfig->AutoPadOrCrCStrip ? 1u : 0u)       |
                   ENET_MAC_CONFIGURATION_WD(pMACConfig->WatchDogDisable ? 1u : 0u)          |
                   ENET_MAC_CONFIGURATION_JD(pMACConfig->JabberDisable ? 1u : 0u)            |
                   ENET_MAC_CONFIGURATION_JE(pMACConfig->JumboEnable ? 1u : 0u)              |
                   ENET_MAC_CONFIGURATION_LM(pMACConfig->LoopbackMode ? 1u : 0u)             |
                   ENET_MAC_CONFIGURATION_ECRSFD(pMACConfig->CarrierSenseBeforeTx ? 1u : 0u) |
                   ENET_MAC_CONFIGURATION_DO(pMACConfig->DisableReceiveOwn ? 1u : 0u)        |
                   ENET_MAC_CONFIGURATION_DCRS(pMACConfig->DisCarrierSenseDurTx ? 1u : 0u)   |
                   ENET_MAC_CONFIGURATION_DR(pMACConfig->DisableRetry ? 1u : 0u)             |
                   ENET_MAC_CONFIGURATION_BL(pMACConfig->BackOffLimit)                       |
                   ENET_MAC_CONFIGURATION_DC(pMACConfig->DeferralCheck ? 1u : 0u);
    pEnetHandle->EnetBase->MAC_CONFIGURATION = u32RegValue;

    ENET_HWA_MAC_SetSpeed(pEnetHandle->EnetBase, eSpeed);
    ENET_HWA_MAC_SetDuplexMode(pEnetHandle->EnetBase, eDuplexMode);

    u32RegValue = pEnetHandle->EnetBase->MAC_EXT_CONFIGURATION;
    u32RegValue &= ~(ENET_MAC_EXT_CONFIGURATION_EIPG_MASK   |
                     ENET_MAC_EXT_CONFIGURATION_EIPGEN_MASK |
                     ENET_MAC_EXT_CONFIGURATION_PDC_MASK    |
                     ENET_MAC_EXT_CONFIGURATION_USP_MASK    |
                     ENET_MAC_EXT_CONFIGURATION_SPEN_MASK   |
                     ENET_MAC_EXT_CONFIGURATION_DCRCC_MASK  |
                     ENET_MAC_EXT_CONFIGURATION_GPSL_MASK);

    u32RegValue |= ENET_MAC_EXT_CONFIGURATION_EIPG(pMACConfig->ExtInterPktGap)                  |
                   ENET_MAC_EXT_CONFIGURATION_EIPGEN(pMACConfig->ExtInterPktGapEn ? 1u : 0u)    |
                   ENET_MAC_EXT_CONFIGURATION_PDC(pMACConfig->PacketDuplication ? 1u : 0u)      |
                   ENET_MAC_EXT_CONFIGURATION_USP(pMACConfig->UnicastSlowProtoDetect ? 1u : 0u) |
                   ENET_MAC_EXT_CONFIGURATION_SPEN(pMACConfig->SlowProtoDetectEnable ? 1u : 0u) |
                   ENET_MAC_EXT_CONFIGURATION_DCRCC(pMACConfig->DisableCrcCheck ? 1u : 0u)      |
                   ENET_MAC_EXT_CONFIGURATION_GPSL(pMACConfig->GiantPktSizeLimit);
    pEnetHandle->EnetBase->MAC_EXT_CONFIGURATION = u32RegValue;

    ENET_HWA_MAC_SetLayer3Layer4FilterEnFlag(pEnetHandle->EnetBase, false);
    ENET_HWA_MAC_SetVLANTagFilterFilterEnFlag(pEnetHandle->EnetBase, false);
    Enet_MACFilterConfig(pEnetHandle->EnetBase, &pMACConfig->MACFilter);

    u32RegValue = pEnetHandle->EnetBase->MAC_WATCHDOG_TIMEOUT;
    u32RegValue &= ~(ENET_MAC_WATCHDOG_TIMEOUT_PWE_MASK | ENET_MAC_WATCHDOG_TIMEOUT_WTO_MASK);
    u32RegValue |= ENET_MAC_WATCHDOG_TIMEOUT_PWE(pMACConfig->ProgramWatchdogEnable ? 1u : 0u) |
                   ENET_MAC_WATCHDOG_TIMEOUT_WTO(pMACConfig->WatchdogTimeout);
    pEnetHandle->EnetBase->MAC_WATCHDOG_TIMEOUT = u32RegValue;
}

/**
 * @brief                       Set up DMA channels and MTL queues map
 * @param[in] pEnetHandle       ENET driver handle
 */
static void Enet_MTL_SetRxQueueMap0(ENET_HandleType *pEnetHandle)
{
    uint32_t u32RegValue = 0u;

#if ENET_CHANNEL_COUNT > 0u
    u32RegValue |= ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH(0u) | ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH(0u);
#endif
#if ENET_CHANNEL_COUNT > 1u
    if (pEnetHandle->RxChannelCount > 1u)
    {
        u32RegValue |= ENET_MTL_RXQ_DMA_MAP0_Q1DDMACH(0u) | ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH(1u);
    }
#endif
    pEnetHandle->EnetBase->MTL.RXQ_DMA_MAP0 = u32RegValue;
}

/**
 * @brief                       Initializes the ENET MTL
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMTLConfig        ENET MTL configuration structure
 */
static void Enet_MTLInit(ENET_HandleType *pEnetHandle, const ENET_MTLConfigType *pMTLConfig)
{
    const ENET_MTLQueueConfigType *pMtlQueueCfg;
    uint32_t u32RegValue;
    uint8_t u8FifoSize;
    uint8_t u8Channel;

    for (u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
    {
        pMtlQueueCfg = &(pMTLConfig->QueueConfigs[u8Channel]);
        if (ENET_MTL_QUEUE_ENABLE_GENERIC == pMtlQueueCfg->TxQueueEnable)
        {
            ENET_HWA_MTL_SetTxQueueQuantumOrWeight(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                   pMtlQueueCfg->IdleSlopeQuantumWeight);
        }
        else if ((u8Channel > 0u) && (ENET_MTL_QUEUE_ENABLE_AV_MODE == pMtlQueueCfg->TxQueueEnable))
        {
            /* AV mode  */
            ENET_HWA_MTL_SetTxQueueQuantumOrWeight(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                    pMtlQueueCfg->IdleSlopeQuantumWeight);
            ENET_HWA_MTL_SetTxQueueSendSlopeCredit(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                    pMtlQueueCfg->SendSlopeCredit);
            ENET_HWA_MTL_SetTxQueueHiCredit(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                    pMtlQueueCfg->HiCredit);
            ENET_HWA_MTL_SetTxQueueLoCredit(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                    (uint32_t)pMTLConfig->QueueConfigs[u8Channel].LoCredit);
            ENET_HWA_MTL_SetAVAlgorithmCBSEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel, ENET_TRUE);
        }

        u8FifoSize = (uint8_t)((pMtlQueueCfg->TxFifoSize / 256u) - 1u);
        ENET_HWA_MTL_SetTxQueueSize(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel, u8FifoSize);
        ENET_HWA_MTL_SetTxThreshold(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                    pMtlQueueCfg->TxThreshold);
        ENET_HWA_MTL_SetTxQueueEnStatus(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                        pMtlQueueCfg->TxQueueEnable);
    }

    Enet_MTL_SetRxQueueMap0(pEnetHandle);

    for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
    {
        pMtlQueueCfg = &(pMTLConfig->QueueConfigs[u8Channel]);
        u8FifoSize = (uint8_t)((pMtlQueueCfg->RxFifoSize / 256u) - 1u);
        ENET_HWA_MTL_SetRxQueueSize(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel, u8FifoSize);
        ENET_HWA_MTL_SetRxDeactivateFlowCtrlThres(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMTLConfig->QueueConfigs[u8Channel].RxDeactiveThreshold);
        ENET_HWA_MTL_SetRxActivateFlowCtrlThres(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMTLConfig->QueueConfigs[u8Channel].RxActiveThreshold);
        ENET_HWA_MTL_SetRxHwFlowCtrlEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMTLConfig->QueueConfigs[u8Channel].RxHwFlowCtrlEnable);
        ENET_HWA_MTL_SetForwardTCPChecksumErrorPacketEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMtlQueueCfg->ReveiveTCPIPCksumErrPkts);
        ENET_HWA_MTL_SetForwardErrorPacketEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMtlQueueCfg->ReveiveErrorPkts);
        ENET_HWA_MTL_SetForwardUndersizedPacketEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMtlQueueCfg->ReveiveUndersizeGoodPkts);
        ENET_HWA_MTL_SetRxThreshold(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMtlQueueCfg->RxThreshold);

        if (ENET_MTL_RX_ARBITRATION_WEIGHTED_STRICT_POLICY == pMTLConfig->RxArbitrationAlgo)
        {
            ENET_HWA_MTL_SetRxQueuePacketArbitrationEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMtlQueueCfg->RxQueueArbitration);
            ENET_HWA_MTL_SetRxQueueWeight(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMTLConfig->QueueConfigs[u8Channel].RxQueueWeight);
        }
        ENET_HWA_MAC_SetRxQueueSelectedPriorities(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                pMtlQueueCfg->RxQueuePriority);
    }

    ENET_HWA_MTL_SetTxSchedulingAlgorithm(pEnetHandle->EnetBase, pMTLConfig->TxSchedAlgo);
    ENET_HWA_MTL_SetRxArbitrationAlgorithm(pEnetHandle->EnetBase, pMTLConfig->RxArbitrationAlgo);
    ENET_HWA_MTL_SetDropTxPacketStatusEnFlag(pEnetHandle->EnetBase,
                                             pMTLConfig->EnableTransmitStatus ? false : true);

    u32RegValue = 0u;
    for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
    {
        u32RegValue |= ((uint32_t)pMTLConfig->QueueConfigs[u8Channel].RxQueueEnable & ENET_MAC_RXQ_CTRL0_RXQ0EN_MASK) <<
                       (ENET_MAC_RXQ_CTRL0_RXQ0EN_WIDTH * (uint32_t)u8Channel);
    }
    ENET_HWA_MAC_SetRxQueueCtrl0(pEnetHandle->EnetBase, u32RegValue);
}

/**
 * @brief                       Get ENET default configuration
 * @param[out] pConfig          ENET default configurations
 */
void Enet_DefaultConfig(ENET_ConfigType *pConfig)
{
    uint8_t u8Channel;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (pConfig == NULL_PTR)
    {
        ENET_ReportDevError(ENET_DEFAULT_CONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
    }
    else
    {
#endif
        pConfig->TxChannelCount = ENET_CHANNEL_COUNT;
        pConfig->RxChannelCount = ENET_CHANNEL_COUNT;

        Enet_MDIODefaultConfig(&pConfig->MiiConfig);

#if ENET_SUPPORT_RGMII
        pConfig->MiiMode = ENET_MAC_PHY_RGMII;
        pConfig->RgmiiClk = ENET_MAC_RGMII_CLK_SEL_PLL1DIVH;
#else
        pConfig->MiiMode = ENET_MAC_PHY_MII;
#endif
#if ENET_SUPPORT_1000MBPS
        pConfig->Speed = ENET_MAC_SPEED_1000MBPS;
#else
        pConfig->Speed = ENET_MAC_SPEED_100MBPS;
#endif
        /* MAC configurations */
        pConfig->Duplex = ENET_MAC_FULL_DUPLEX;
        pConfig->MACConfig.SrcAddrCtrl = ENET_MAC_SRC_ADDR_CTRL_BY_INPUT_SIGNAL;
        pConfig->MACConfig.ChecksumOffload = ENET_FALSE;
        pConfig->MACConfig.InterPacketGap = ENET_MAC_INTER_PACKET_GAP_96_BIT;
        pConfig->MACConfig.GiantPacketLimit = ENET_FALSE;
        pConfig->MACConfig.Support2KPacket = ENET_FALSE;
        pConfig->MACConfig.CrcStripForTypePkt = ENET_TRUE;
        pConfig->MACConfig.AutoPadOrCrCStrip = ENET_TRUE;
        pConfig->MACConfig.WatchDogDisable = ENET_FALSE;
        pConfig->MACConfig.JabberDisable = ENET_FALSE;
        pConfig->MACConfig.JumboEnable = ENET_FALSE;
        pConfig->MACConfig.LoopbackMode = ENET_FALSE;
        pConfig->MACConfig.CarrierSenseBeforeTx = ENET_FALSE;
        pConfig->MACConfig.DisableReceiveOwn = ENET_FALSE;
        pConfig->MACConfig.DisCarrierSenseDurTx = ENET_FALSE;
        pConfig->MACConfig.DisableRetry = ENET_FALSE;
        pConfig->MACConfig.BackOffLimit = ENET_MAC_BACK_OFF_LIMIT_10_SLOT;
        pConfig->MACConfig.DeferralCheck = ENET_FALSE;
        pConfig->MACConfig.ExtInterPktGap = ENET_MAC_EXT_INTER_PACKET_GAP_104_BIT;
        pConfig->MACConfig.ExtInterPktGapEn = ENET_FALSE;
        pConfig->MACConfig.PacketDuplication = ENET_FALSE;
        pConfig->MACConfig.UnicastSlowProtoDetect = ENET_FALSE;
        pConfig->MACConfig.SlowProtoDetectEnable = ENET_FALSE;
        pConfig->MACConfig.DisableCrcCheck = ENET_FALSE;
        pConfig->MACConfig.GiantPktSizeLimit = 0u;
        pConfig->MACConfig.ProgramWatchdogEnable = ENET_FALSE;
        pConfig->MACConfig.WatchdogTimeout = ENET_MAC_WDG_TIMER_SIZE_2KB;
        Enet_DefaultMACFilter(&pConfig->MACConfig.MACFilter);

        /* MTL Transmit and Receive Scheduling Algorithm configurations */
        pConfig->MTLConfig.TxSchedAlgo = ENET_MTL_SCHED_ALGO_SP;
        pConfig->MTLConfig.RxArbitrationAlgo = ENET_MTL_RX_ARBITRATION_WEIGHTED_STRICT_POLICY;
        pConfig->MTLConfig.EnableTransmitStatus = ENET_TRUE;

        /* MTL Transmit Queues configurations */
        for (u8Channel = 0u; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
        {
            pConfig->MTLConfig.QueueConfigs[u8Channel].TxFifoSize = ENET_MTL_TX_FIFO_SIZE / ENET_CHANNEL_COUNT;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxFifoSize = ENET_MTL_RX_FIFO_SIZE / ENET_CHANNEL_COUNT;
            pConfig->MTLConfig.QueueConfigs[u8Channel].TxQueueEnable = ENET_MTL_QUEUE_ENABLE_GENERIC;
            pConfig->MTLConfig.QueueConfigs[u8Channel].IdleSlopeQuantumWeight = 0u;
            pConfig->MTLConfig.QueueConfigs[u8Channel].SendSlopeCredit = 0u;
            pConfig->MTLConfig.QueueConfigs[u8Channel].HiCredit = 0u;
            pConfig->MTLConfig.QueueConfigs[u8Channel].LoCredit = 0u;
            pConfig->MTLConfig.QueueConfigs[u8Channel].TxThreshold = ENET_MTL_TX_STORE_FORWARD;
        }

        /* MTL Transmit Queues configurations */
        for (u8Channel = 0u; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
        {
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxQueueEnable = ENET_MTL_QUEUE_ENABLE_GENERIC;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxThreshold = ENET_MTL_RX_STORE_FORWARD;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxDeactiveThreshold = ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_1_KB;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxActiveThreshold = ENET_MTL_RX_FLOWCTRL_THRESHOLD_FULL_1_KB;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxHwFlowCtrlEnable = ENET_FALSE;
            pConfig->MTLConfig.QueueConfigs[u8Channel].ReveiveTCPIPCksumErrPkts = ENET_FALSE;
            pConfig->MTLConfig.QueueConfigs[u8Channel].ReveiveErrorPkts = ENET_FALSE;
            pConfig->MTLConfig.QueueConfigs[u8Channel].ReveiveUndersizeGoodPkts = ENET_FALSE;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxQueueArbitration = ENET_TRUE;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxQueueWeight = 0u;
            pConfig->MTLConfig.QueueConfigs[u8Channel].RxQueuePriority =
                                                       (0xFu << (uint32_t)(u8Channel * 4u)) & 0xFFu;
        }

        /* The DMA Arbitration Algorithm between Receive and Transmit Paths */
        pConfig->DMAConfig.PriorityMode = ENET_DMA_PRIORITY_MODE_RX_TX;
        pConfig->DMAConfig.PriorityRatio = ENET_DMA_PRIORITY_RATIO_1_1;
        pConfig->DMAConfig.TxRxArbitration = ENET_DMA_TXRX_ARBITRATION_SCHEME_WEIGHTED_ROUND_ROBIN;
        /* The Transmit Arbitration Algorithm for multiple DMA channels */
        pConfig->DMAConfig.TxArbitration = ENET_DMA_TX_ARBITRATION_ALGORITHM_WEIGHTED_FIXED_PRIORITY;

        pConfig->DMAConfig.BurstMode = ENET_BURSTLENGTH_MIXED;
        pConfig->DMAConfig.RebuildINCRxBurst = ENET_FALSE;
        pConfig->DMAConfig.AddressAlignedBeats = ENET_TRUE;

        for (u8Channel = 0u; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
        {
            pConfig->DMAConfig.ChannelConfigs[u8Channel].BurstLength = ENET_DMA_BURST_LENGTH_32_BEATS;
            pConfig->DMAConfig.ChannelConfigs[u8Channel].EnhancedDescriptor = ENET_FALSE;
            pConfig->DMAConfig.ChannelConfigs[u8Channel].EarlySendIntEnable = ENET_FALSE;
            pConfig->DMAConfig.ChannelConfigs[u8Channel].OperateSecondPacket = ENET_TRUE;
            pConfig->DMAConfig.ChannelConfigs[u8Channel].TxChannelWeight = 0u;
        }
        for (u8Channel = 0u; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
        {
            pConfig->DMAConfig.ChannelConfigs[u8Channel].BurstLength = ENET_DMA_BURST_LENGTH_32_BEATS;
            pConfig->DMAConfig.ChannelConfigs[u8Channel].EarlyReceiveIntEnable = ENET_FALSE;
        }

        pConfig->EventCallback = NULL_PTR;
        pConfig->RxReady = NULL_PTR;
        pConfig->TxComplete = NULL_PTR;
        pConfig->TxCompleteWait = NULL_PTR;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Reset ENET driver
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_DeInit(ENET_HandleType *pEnetHandle)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_DEINIT_SERVICE_ID))
    {
#endif
        pEnetHandle->EnetBase = NULL_PTR;
        pEnetHandle->State = ENET_STATE_UNINIT;
        pEnetHandle->TxState = ENET_STATE_UNINIT;
        pEnetHandle->RxState = ENET_STATE_UNINIT;
        pEnetHandle->PTPState = ENET_STATE_UNINIT;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Initialize ENET driver handle and peripheral
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pConfig           ENET configure parameters
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET initialize succeeded
 * @retval other values         ENET initialize failed
 */
ENET_StatusType Enet_Init(ENET_HandleType *pEnetHandle, const ENET_ConfigType *pConfig)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    ENET_Type *pEnetBase[ENET_INSTANCE_COUNT] = ENET_BASE_PTRS;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_INIT_SERVICE_ID))
    {
        if (pConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_INIT_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State != ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_INIT_SERVICE_ID, ENET_E_DRIVER_REPEAT_INIT);
            }
            else
            {
                if ((pConfig->TxChannelCount == 0u) || (pConfig->TxChannelCount > ENET_CHANNEL_COUNT))
                {
                    ENET_ReportDevError(ENET_INIT_SERVICE_ID, ENET_E_PARAM_TXCHANNEL);
                }
                else
                {
                    if ((pConfig->RxChannelCount == 0u) || (pConfig->RxChannelCount > ENET_CHANNEL_COUNT))
                    {
                        ENET_ReportDevError(ENET_INIT_SERVICE_ID, ENET_E_PARAM_RXCHANNEL);
                    }
                    else
                    {
                        if (0u != Enet_AssertConfiguration(pConfig))
                        {
                            ENET_ReportDevError(ENET_INIT_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                        }
                        else
                        {
#endif

                            pEnetHandle->State = ENET_STATE_UNINIT;
                            pEnetHandle->TxState = ENET_STATE_UNINIT;
                            pEnetHandle->RxState = ENET_STATE_UNINIT;
                            pEnetHandle->PTPState = ENET_STATE_UNINIT;
                            pEnetHandle->EnetBase = pEnetBase[pEnetHandle->eInstance];
                            pEnetHandle->TxChannelCount = pConfig->TxChannelCount;
                            pEnetHandle->RxChannelCount = pConfig->RxChannelCount;

                            Enet_SystemConfig(pConfig);

                            /** DMA software reset */
                            eStatus = Enet_SoftwareReset(pEnetHandle->EnetBase);

                            if (ENET_STATUS_SUCCESS == eStatus)
                            {
                                eStatus = Enet_MDIOInit(pEnetHandle, &pConfig->MiiConfig);
                                if (ENET_STATUS_SUCCESS == eStatus)
                                {
                                    Enet_DMARxDescInit(pEnetHandle, pConfig->RxBD);
                                    Enet_DMATxDescInit(pEnetHandle, pConfig->TxBD);
                                    Enet_DMAInit(pEnetHandle, &pConfig->DMAConfig);
                                    Enet_MTLInit(pEnetHandle, &pConfig->MTLConfig);
                                    Enet_MACInit(pEnetHandle, &pConfig->MACConfig, pConfig->Speed, pConfig->Duplex);
                                    Enet_MacAddressConfig(pEnetHandle->EnetBase, pConfig->MACAddress, ENET_MAC_ADDRESS_LENGTH);
                                    pEnetHandle->EventCallback = pConfig->EventCallback;
                                    pEnetHandle->RxReady = pConfig->RxReady;
                                    pEnetHandle->TxComplete = pConfig->TxComplete;
                                    pEnetHandle->TxCompleteWait = pConfig->TxCompleteWait;
                                    pEnetHandle->State = ENET_STATE_INITIALIZED;
                                }
                            }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                        }
                    }
                }
            }
        }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Initializes the ENET DMA TX descriptors
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pTxDesc           An Array of TX channel descriptors configure structures
 */
static void Enet_DMATxDescInit(ENET_HandleType *pEnetHandle, const ENET_DescConfigType pTxDesc[])
{
    uint8_t u8Channel, u8RingIndex;
    uint16_t u16RingSize;
    uint16_t u16BufferLen;
    uint8_t *pTemp;

    for (u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
    {
        u16BufferLen = pTxDesc[u8Channel].BufferLen;
        u16RingSize = pTxDesc[u8Channel].RingSize;
        pEnetHandle->TxDescLists[u8Channel].DescList = pTxDesc[u8Channel].DescList;
        pEnetHandle->TxDescLists[u8Channel].BufferLen = u16BufferLen;
        pEnetHandle->TxDescLists[u8Channel].RingSize = u16RingSize;

        for (u8RingIndex = 0u; u8RingIndex < u16RingSize; ++u8RingIndex)
        {
            pEnetHandle->TxDescLists[u8Channel].DescList[u8RingIndex].Des0 = 0u;
            pEnetHandle->TxDescLists[u8Channel].DescList[u8RingIndex].Des1 = 0u;
            pEnetHandle->TxDescLists[u8Channel].DescList[u8RingIndex].Des2 = 0u;
            pEnetHandle->TxDescLists[u8Channel].DescList[u8RingIndex].Des3 = 0u;
            if (pTxDesc[u8Channel].Buffer != NULL_PTR)
            {
                pTemp = &pTxDesc[u8Channel].Buffer[u16BufferLen * u8RingIndex];
                pEnetHandle->TxDescLists[u8Channel].DescList[u8RingIndex].BackupInfo0 = (uint32_t)pTemp;
            }
            else
            {
                pEnetHandle->TxDescLists[u8Channel].DescList[u8RingIndex].BackupInfo0 = 0u;
            }
            pEnetHandle->TxDescLists[u8Channel].DescList[u8RingIndex].BackupInfo1 = 0u;
        }

        ENET_HWA_DMA_SetTxDescListHeadAddr(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                           (uint32_t)pEnetHandle->TxDescLists[u8Channel].DescList);
        ENET_HWA_DMA_SetTxDescListTailAddr(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                           (uint32_t)pEnetHandle->TxDescLists[u8Channel].DescList);
        ENET_HWA_DMA_SetTxDescRingLength(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, (uint16_t)(u16RingSize - 1u));
    }
}

/**
 * @brief                       Setup the ENET DMA RX descriptor for receiving
 * @param[in] pDesc             Pointer to the DMA descriptor
 * @param[in] bItMode           Whether to enable the interrupt mode
 */
static inline void Enet_SetupRxDesc(ENET_DMADescType *pDesc, bool bItMode)
{
    pDesc->Des0 = pDesc->BackupInfo0;
    pDesc->Des1 = 0u;
    pDesc->Des2 = pDesc->BackupInfo1;
    pDesc->Des3 = ENET_RDES3_BUFFER1_VALID_MASK;

    if (pDesc->BackupInfo1 != 0u)
    {
        pDesc->Des3 |= ENET_RDES3_BUFFER2_VALID_MASK;
    }

    if (bItMode)
    {
        pDesc->Des3 |= ENET_RDES3_IOC_MASK;
    }
    pDesc->Des3 |= ENET_DES3_OWN_MASK;
}

/**
 * @brief                       Initializes the ENET DMA TX descriptors
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pRxDesc           AN array of RX channel descriptors configure structures
 */
static void Enet_DMARxDescInit(ENET_HandleType *pEnetHandle, const ENET_DescConfigType pRxDesc[])
{
    uint8_t u8Channel, u8RingIndex;
    uint16_t u16RingSize;
    uint16_t u16BufferLen;
    uint8_t *pTemp;

    for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
    {
        u16BufferLen = pRxDesc[u8Channel].BufferLen;
        u16RingSize = pRxDesc[u8Channel].RingSize;
        pEnetHandle->RxDescLists[u8Channel].DescList = pRxDesc[u8Channel].DescList;
        pEnetHandle->RxDescLists[u8Channel].BufferLen = u16BufferLen;
        pEnetHandle->RxDescLists[u8Channel].RingSize = u16RingSize;

        for (u8RingIndex = 0u; u8RingIndex < u16RingSize; ++u8RingIndex)
        {
            pTemp = &pRxDesc[u8Channel].Buffer[u16BufferLen * u8RingIndex];
            pEnetHandle->RxDescLists[u8Channel].DescList[u8RingIndex].BackupInfo0 = (uint32_t)pTemp;
            pEnetHandle->RxDescLists[u8Channel].DescList[u8RingIndex].BackupInfo1 = 0u;
            Enet_SetupRxDesc(&pEnetHandle->RxDescLists[u8Channel].DescList[u8RingIndex], false);
        }

        ENET_HWA_DMA_SetRxDescListHeadAddr(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                           (uint32_t)pEnetHandle->RxDescLists[u8Channel].DescList);
        ENET_HWA_DMA_SetRxDescListTailAddr(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                           (uint32_t)(&pEnetHandle->RxDescLists[u8Channel].DescList[u16RingSize - 1u]));
        ENET_HWA_DMA_SetRxDescRingLength(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, (uint16_t)(u16RingSize - 1u));

        ENET_HWA_DMA_SetRxBufferSize(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel,
                                     pEnetHandle->RxDescLists[u8Channel].BufferLen);
    }
}

/**
 * @brief                       Start ENET transmission and reception process in polling mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET start succeeded
 * @retval other values         ENET start failed
 */
ENET_StatusType Enet_Start(ENET_HandleType *pEnetHandle)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint8_t u8Channel;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_START_SERVICE_ID))
    {
#endif

        if ((ENET_STATE_INITIALIZED == pEnetHandle->State) || (ENET_STATE_STOPPED == pEnetHandle->State))
        {
            pEnetHandle->ItMode = false;

            for (u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
            {
                /* Enable DMA transmission */
                ENET_HWA_DMA_StartTx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                ENET_HWA_DMA_ClearTxProcessStoppedFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                /* Flush Transmit Queues FIFO  */
                ENET_HWA_MTL_FlushTxQueue(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel);
            }

            for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
            {
                /* Enable DMA reception */
                ENET_HWA_DMA_StartRx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                ENET_HWA_DMA_ClearRxProcessStoppedFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
            }

            /* Enable MAC transmission and reception */
            ENET_HWA_MAC_SetTxEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
            ENET_HWA_MAC_SetRxEnFlag(pEnetHandle->EnetBase, ENET_TRUE);

            pEnetHandle->State = ENET_STATE_READY;
            pEnetHandle->TxState = ENET_STATE_READY;
            pEnetHandle->RxState = ENET_STATE_READY;
            eStatus = ENET_STATUS_SUCCESS;
        }
        else
        {
            eStatus = ENET_STATUS_NOT_READY;
        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
    return eStatus;
}

/**
 * @brief                       Stop ENET transmission and reception process in polling mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET Stop succeeded
 * @retval other values         ENET Stop failed
 */
ENET_StatusType Enet_Stop(ENET_HandleType *pEnetHandle)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint8_t u8Channel;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_STOP_SERVICE_ID))
    {
#endif

        if (ENET_STATE_READY == pEnetHandle->State)
        {
            if ((ENET_STATE_READY == pEnetHandle->TxState) && (ENET_STATE_READY == pEnetHandle->RxState))
            {
                pEnetHandle->State = ENET_STATE_BUSY;

                /* Disable DMA transmission */
                for (u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
                {
                    ENET_HWA_DMA_StopTx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                    ENET_HWA_MTL_FlushTxQueue(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel);
                }

                /* Disable MAC transmission and reception */
                ENET_HWA_MAC_SetTxEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                ENET_HWA_MAC_SetRxEnFlag(pEnetHandle->EnetBase, ENET_FALSE);

                /* Disable DMA reception */
                for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
                {
                    ENET_HWA_DMA_StopRx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                }
                pEnetHandle->State = ENET_STATE_STOPPED;
                pEnetHandle->TxState = ENET_STATE_STOPPED;
                pEnetHandle->RxState = ENET_STATE_STOPPED;
                eStatus = ENET_STATUS_SUCCESS;
            }
            else
            {
                eStatus = ENET_STATUS_BUSY;
            }
        }
        else
        {
            eStatus = ENET_STATUS_ERROR;
        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
    return eStatus;
}

/**
 * @brief                       Start ENET transmission and reception in interrupt mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET start succeeded
 * @retval other values         ENET start failed
 */
ENET_StatusType Enet_StartIT(ENET_HandleType *pEnetHandle)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint8_t u8Channel, u8RingIndex;
    ENET_DescListType *pDescList;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_STARTIT_SERVICE_ID))
    {
#endif

       if ((ENET_STATE_INITIALIZED == pEnetHandle->State) || (ENET_STATE_STOPPED == pEnetHandle->State))
        {
            pEnetHandle->ItMode = true;

            for (u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
            {
                /* Enable DMA interrupts */
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_NORMAL_INTERRUPT);
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_ABNORMAL_INTERRUPT);
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_TX_INTERRUPT);
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_FATAL_BUS_ERROR_INTERRUPT);
                /* Enable DMA transmission */
                ENET_HWA_DMA_StartTx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                ENET_HWA_DMA_ClearTxProcessStoppedFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                /* Flush Transmit Queues FIFO */
                ENET_HWA_MTL_FlushTxQueue(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel);
            }

            for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
            {
                /* Set interrupt bits in RX descriptors */
                pDescList = &pEnetHandle->RxDescLists[u8Channel];
                for (u8RingIndex = 0u; u8RingIndex < pDescList->RingSize; u8RingIndex++)
                {
                    pDescList->DescList[u8RingIndex].Des3 |= ENET_RDES3_IOC_MASK;
                }
                /* Enable DMA interrupts */
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_NORMAL_INTERRUPT);
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_ABNORMAL_INTERRUPT);
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_RX_INTERRUPT);
                ENET_HWA_DMA_EnableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_FATAL_BUS_ERROR_INTERRUPT);
                /* Enable DMA reception */
                ENET_HWA_DMA_StartRx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                ENET_HWA_DMA_ClearRxProcessStoppedFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
            }

            /* Enable MAC transmission and reception */
            ENET_HWA_MAC_SetTxEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
            ENET_HWA_MAC_SetRxEnFlag(pEnetHandle->EnetBase, ENET_TRUE);

            pEnetHandle->State = ENET_STATE_READY;
            pEnetHandle->TxState = ENET_STATE_READY;
            pEnetHandle->RxState = ENET_STATE_READY;
            eStatus = ENET_STATUS_SUCCESS;
        }
        else
        {
           eStatus = ENET_STATUS_NOT_READY;
        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
    return eStatus;
}

/**
 * @brief                       Stop ENET transmission and reception in interrupt mode
 * @param[in] pEnetHandle       ENET driver handle
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  ENET Stop succeeded
 * @retval other values         ENET Stop failed
 */
ENET_StatusType Enet_StopIT(ENET_HandleType *pEnetHandle)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint8_t u8Channel, u8RingIndex;
    ENET_DescListType *pDescList;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_STOPIT_SERVICE_ID))
    {
#endif

        if (ENET_STATE_READY == pEnetHandle->State)
        {
            if ((ENET_STATE_READY == pEnetHandle->TxState) && (ENET_STATE_READY == pEnetHandle->RxState))
            {
                pEnetHandle->State = ENET_STATE_BUSY;

                 /* Disable DMA interrupts */
                for (u8Channel = 0u; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
                {
                    ENET_HWA_DMA_SetEnabledInterrupts(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, 0u);
                }

                /* Disable DMA transmission */
                for (u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
                {
                    ENET_HWA_DMA_StopTx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                    ENET_HWA_MTL_FlushTxQueue(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel);
                }

                /* Disable MAC transmission and reception */
                ENET_HWA_MAC_SetTxEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                ENET_HWA_MAC_SetRxEnFlag(pEnetHandle->EnetBase, ENET_FALSE);

                /* Disable DMA reception */
                for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
                {
                    ENET_HWA_DMA_StopRx(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                    ENET_HWA_DMA_ClearRxProcessStoppedFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
                    /* Clear interrupt bits in RX descriptors */
                    pDescList = &pEnetHandle->RxDescLists[u8Channel];
                    for (u8RingIndex = 0u; u8RingIndex < pDescList->RingSize; u8RingIndex++)
                    {
                        pDescList->DescList[u8RingIndex].Des3 &= ~ENET_RDES3_IOC_MASK;
                    }
                }

                pEnetHandle->ItMode = false;
                pEnetHandle->State = ENET_STATE_STOPPED;
                pEnetHandle->TxState = ENET_STATE_STOPPED;
                pEnetHandle->RxState = ENET_STATE_STOPPED;
                eStatus = ENET_STATUS_SUCCESS;
            }
            else
            {
                eStatus = ENET_STATUS_BUSY;
            }
        }
        else
        {
           eStatus = ENET_STATUS_ERROR;
        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
    return eStatus;
}

/**
 * @brief                       Get IEEE1588 time stamp from the ENET DMA TX descriptor
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pDesc             Pointer to DMA TX descriptor
 * @param[out] pTimestamp       Time stamp value
 * @return                      boolean
 * @retval true                 Time stamp of transmitted frame is valid
 * @retval false                Time stamp of transmitted frame is invalid
 */
static bool Enet_ReadTxDescTimestamp(ENET_HandleType *pEnetHandle, const ENET_DMADescType *pDesc, ENET_TimestampType *pTimestamp)
{
    uint32_t u32Des3, u32CurrTimeSec;
    bool bRet = false;

    u32Des3 = pDesc->Des3;
    if (((u32Des3 & ENET_DES3_CTXT_MASK) == 0u) &&
        ((u32Des3 & ENET_TDES3_LD_MASK) != 0u) &&
        ((u32Des3 & ENET_TDES3_TTSS_MASK) != 0u))
    {
        pTimestamp->Nanoseconds = pDesc->Des0;
        pTimestamp->Seconds = pDesc->Des1;
        u32CurrTimeSec = (uint32_t)(pEnetHandle->EnetBase->MAC_SYSTEM_TIME_SECONDS);
        pTimestamp->SecondsHi = (uint16_t)pEnetHandle->EnetBase->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS;

        if (pTimestamp->Seconds > u32CurrTimeSec)
        {
            pTimestamp->SecondsHi = (uint16_t)(pTimestamp->SecondsHi - 1u);
        }
        if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == ENET_HWA_MAC_GetTimestampRolloverCtrl(pEnetHandle->EnetBase))
        {
            pTimestamp->Nanoseconds = Enet_PTPRegValue2Nanoseconds(pTimestamp->Nanoseconds);
        }
        bRet = true;
    }
    return bRet;
}

/**
 * @brief                       Get IEEE1588 time stamp from the ENET DMA RX descriptor
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pDesc             Pointer to DMA RX descriptor
 * @param[out] pTimestamp       Time stamp value
 */
static void Enet_ReadRxDescTimestamp(ENET_HandleType *pEnetHandle, const ENET_DMADescType *pDesc, ENET_TimestampType *pTimestamp)
{
    uint32_t CurrTimeSec;

    pTimestamp->Nanoseconds = pDesc->Des0;
    pTimestamp->Seconds = pDesc->Des1;
    CurrTimeSec = (uint32_t)(pEnetHandle->EnetBase->MAC_SYSTEM_TIME_SECONDS);
    pTimestamp->SecondsHi = (uint16_t)pEnetHandle->EnetBase->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS;

    if (pTimestamp->Seconds > CurrTimeSec)
    {
        pTimestamp->SecondsHi = (uint16_t)(pTimestamp->SecondsHi - 1u);
    }
    if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == ENET_HWA_MAC_GetTimestampRolloverCtrl(pEnetHandle->EnetBase))
    {
        pTimestamp->Nanoseconds = Enet_PTPRegValue2Nanoseconds(pTimestamp->Nanoseconds);
    }
}

/**
 * @brief                       Get next descriptor from the descriptor list
 * @param[in] pCurDesc          Pointer to current descriptor
 * @param[in] pDescList         Pointer to DMA descriptors list start address
 * @return                      ENET_DMADescType
 * @retval                      Pointer to next DMA descriptor
 */
static inline ENET_DMADescType *Enet_NextDescriptor(ENET_DMADescType *pCurDesc, ENET_DescListType *pDescList)
{
    uint32_t pTemp = (uint32_t)(&pDescList->DescList[pDescList->RingSize - 1u]);
    if ((uint32_t)pCurDesc >= pTemp)
    {
        return pDescList->DescList;
    }
    else
    {
        return &pCurDesc[1u];
    }
}

/**
 * @brief                       Build TX descriptors to DMA
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          DMA channel to use
 * @param[in] pBuffers          Data buffer chain to transmit
 * @param[inout] pOption        Transmit options and results,set NULL if not needed
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  TX descriptors are prepared to DMA successfully
 * @retval other values         TX descriptors are prepared to DMA failed
 */
static ENET_StatusType Enet_BuildTxDescriptors(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                               ENET_BufferType *pBuffers, ENET_TxOptionType *pOption)
{
    ENET_StatusType eStatus = ENET_STATUS_SUCCESS;
    ENET_DescListType *pDescList;
    ENET_DMADescType *pDesc;
    ENET_BufferType *pBuf = pBuffers;
    uint32_t ContextDesc = 0u;
    uint32_t FrameLength = pBuf->TotalLength;

    pDescList = &pEnetHandle->TxDescLists[eChannel];

    pDesc = (ENET_DMADescType *)ENET_HWA_DMA_GetTxDescListTailAddr(pEnetHandle->EnetBase,
                                                        (ENET_DMA_ChannelType)eChannel);
    pDescList->FirstDesc = pDesc;
    pDescList->LastDesc = pDesc;

    /* Add context descriptor if VLAN tag or TCP segmentation is enabled */
    if (pOption != NULL_PTR)
    {
        if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_VLAN_TAG_CTRL))
        {
            /* Add context descriptor */
            if (0u != (pDesc->Des3 & ENET_DES3_OWN_MASK))
            {
                eStatus = ENET_STATUS_ERROR;
            }
            else
            {
                pDesc->Des0 = 0u;
                pDesc->Des1 = 0u;
                pDesc->Des2 = 0u;
                pDesc->Des3 = 0u;
                if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_VLAN_TAG_CTRL))
                {
                    /* Set VLAN tag */
                    pDesc->Des3 |= ENET_TDES3_VT(pOption->VlanConfig.VlanTag);
                    pDesc->Des3 |= ENET_TDES3_VLTV_MASK;
                    /* Set VLAN tag input source from Tx descriptor */
                    ENET_HWA_MAC_SetVLANTagInputEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    ENET_HWA_MAC_SetVLANPriorityCtrlEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                    ENET_HWA_MAC_SetVLANType(pEnetHandle->EnetBase, pOption->VlanConfig.VlanType);
                    if (pOption->VlanConfig.VlanType == ENET_MAC_VLAN_TYPE_S_VLAN)
                    {
                        ENET_HWA_MAC_SetSVLANEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    }

                    if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_INNER_VLAN_TAG_CTRL))
                    {
                        pDesc->Des2 |= ENET_TDES2_IVT(pOption->InnerVlanConfig.VlanTag);
                        pDesc->Des3 |= ENET_TDES3_IVLTV_MASK;
                        pDesc->Des3 |= ENET_TDES3_IVTIR(pOption->InnerVlanConfig.VlanCtrl);
                        /* Set inner VLAN tag input source from Tx descriptor */
                        ENET_HWA_MAC_SetInnerVLANTagInputEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                        ENET_HWA_MAC_SetInnerVLANType(pEnetHandle->EnetBase, pOption->InnerVlanConfig.VlanType);
                        ENET_HWA_MAC_SetInnerVLANPriorityCtrlEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                        ENET_HWA_MAC_SetDoubleVLANProcessEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                        if (pOption->InnerVlanConfig.VlanType == ENET_MAC_VLAN_TYPE_S_VLAN)
                        {
                            ENET_HWA_MAC_SetSVLANEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                        }
                    }
                }
                pDesc->Des3 |= ENET_DES3_CTXT_MASK;
                pDesc->Des3 |= ENET_DES3_OWN_MASK;
                pDesc = Enet_NextDescriptor(pDesc, pDescList);
                ContextDesc = 1u;
            }
        }
    }

    if (ENET_STATUS_SUCCESS == eStatus)
    {
        while (pBuf != NULL_PTR)
        {
            if ((0u != (pDesc->Des3 & ENET_DES3_OWN_MASK)) ||
                (pBuf->Data == NULL_PTR) ||
                (pBuf->Length == 0u) ||
                (pBuf->Length > pDescList->BufferLen))
            {
                eStatus = ENET_STATUS_ERROR;
                break;
            }

            pDescList->LastDesc = pDesc;
            pDesc->BackupInfo0 = (uint32_t)pBuf->Data;
            pDesc->Des0 = pDesc->BackupInfo0;
            pDesc->Des1 = 0u;
            pDesc->Des2 = ENET_TDES2_BUFFER1_LEN(pBuf->Length);
            pDesc->Des3 = ENET_DES3_OWN_MASK | ENET_TDES3_FL(FrameLength);

            pDesc = Enet_NextDescriptor(pDesc, pDescList);
            pBuf = pBuf->Next;
        }
    }

    if (ENET_STATUS_SUCCESS == eStatus)
    {
        /* Set first Descriptor */
        pDesc = pDescList->FirstDesc;
        if (ContextDesc != 0u)
        {
            pDesc = Enet_NextDescriptor(pDesc, pDescList);
        }
        pDesc->Des3 |= ENET_TDES3_FD_MASK;

        if (pOption != NULL_PTR)
        {
            /* Set first descriptor enable CRC pad*/
            if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_CRC_PAD_CTRL))
            {
                pDesc->Des3 |= ENET_TDES3_CPC(pOption->CrcPadCtrl);
            }
            /* Set first descriptor enable checksum */
            if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_CHECKSUM_INSERTION))
            {
                pDesc->Des3 |= ENET_TDES3_CIC(pOption->CheckSumCtrl);
            }
            /* Set first descriptor enable VLAN tag */
            if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_VLAN_TAG_CTRL))
            {
                pDesc->Des2 |= ENET_TDES2_VTIR(pOption->VlanConfig.VlanCtrl);
            }

            /* Set last descriptor enable time stamp */
            if (0u != (pOption->Attributes & (uint32_t)ENET_TX_ATTRIBUTES_TIMESTAMP_SNAPSHOOT))
            {
                pDescList->LastDesc->Des2 |= ENET_TDES2_TTSE_MASK;
            }
        }
        /* Set last descriptor interrupt */
        if (0u != (pEnetHandle->ItMode))
        {
            pDescList->LastDesc->Des2 |= ENET_TDES2_IOC_MASK;
        }
        /* Set last descriptor flag */
        pDescList->LastDesc->Des3 |= ENET_TDES3_LD_MASK;
    }
    else
    {
        /* Release Descriptors on error state */
        pDesc = pDescList->FirstDesc;
        while (pDesc != pDescList->LastDesc)
        {
            pDesc->Des3 &= ~ENET_DES3_OWN_MASK;
            pDesc = Enet_NextDescriptor(pDesc, pDescList);
        }
        pDesc->Des3 &= ~ENET_DES3_OWN_MASK;
    }

    return eStatus;
}

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
                               ENET_BufferType *pBuffers, ENET_TxOptionType *pOption)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    ENET_DMADescType *pLastDesc = NULL_PTR, *pTailDesc = NULL_PTR;
    uint32_t u32Timeout = 150000u;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SEND_FRAME_SERVICE_ID))
    {
        if ((pBuffers == NULL_PTR) || (pBuffers->Data == NULL_PTR))
        {
            ENET_ReportDevError(ENET_SEND_FRAME_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State != ENET_STATE_READY)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_SEND_FRAME_SERVICE_ID, ENET_E_CONTROLLER_MODE);
            }
            else
            {
                if ((uint8_t)eChannel >= pEnetHandle->TxChannelCount)
                {
                    ENET_ReportDevError(ENET_SEND_FRAME_SERVICE_ID, ENET_E_PARAM_TXCHANNEL);
                }
                else
                {
                    if (0u != Enet_AssertTxOption(pEnetHandle, pOption))
                    {
                        ENET_ReportDevError(ENET_SEND_FRAME_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                    }
                    else
                    {
#endif

                        if (ENET_STATE_READY == pEnetHandle->TxState)
                        {
                            pEnetHandle->TxState = ENET_STATE_BUSY;
                            eStatus = Enet_BuildTxDescriptors(pEnetHandle, eChannel, pBuffers, pOption);
                            if (ENET_STATUS_SUCCESS == eStatus)
                            {
                                pLastDesc = pEnetHandle->TxDescLists[eChannel].LastDesc;
                                if (pLastDesc != NULL_PTR)
                                {
                                    pTailDesc = Enet_NextDescriptor(pLastDesc, &pEnetHandle->TxDescLists[(uint32_t)eChannel]);
                                    ENET_DATA_BARRIER();
                                    ENET_HWA_DMA_SetTxDescListTailAddr(pEnetHandle->EnetBase,
                                            (ENET_DMA_ChannelType)eChannel, (uint32_t)pTailDesc);

                                    if (0u != (pEnetHandle->ItMode))
                                    {
                                        /* Call WaitTxCompleteCallback for TX time stamp valid */
                                        if (pEnetHandle->TxCompleteWait != NULL_PTR)
                                        {
                                            eStatus = pEnetHandle->TxCompleteWait(pEnetHandle, eChannel);
                                        }
                                    }
                                    else
                                    {
                                        /* Poll DMA send complete */
                                        while ((pLastDesc->Des3 & ENET_DES3_OWN_MASK) != (uint32_t)0u)
                                        {
                                            if (--u32Timeout == 0u)
                                            {
                                                eStatus = ENET_STATUS_TIMEOUT;
                                                break;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    eStatus = ENET_STATUS_ERROR;
                                }
                            }

                            if (ENET_STATUS_SUCCESS == eStatus)
                            {
                                if (pOption != NULL_PTR)
                                {
                                    pOption->Attributes = 0u;
                                    /* read IEEE1588 time stamp */
                                    if (Enet_ReadTxDescTimestamp(pEnetHandle, pLastDesc, &pOption->TimeStamp) != false)
                                    {
                                        pOption->Attributes |= (uint32_t)ENET_TX_ATTRIBUTES_TIMESTAMP_VALID;
                                    }
                                }
                            }
                            pEnetHandle->TxState = ENET_STATE_READY;
                        }
                        else
                        {
                            eStatus = ENET_STATUS_BUSY;
                        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                   Release RX descriptors to DMA
 * @param[in] pEnetHandle   ENET driver handle
 * @param[in] eChannel      DMA channel to use
 * @param[in] pStart        Pointer to the first descriptor
 * @param[inout] pEnd       Pointer to the last descriptor
 */
static void Enet_ReleaseRxDescriptors(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                      ENET_DMADescType *pStart, ENET_DMADescType *pEnd)
{
    ENET_DMADescType *pDesc;

    if ((pStart != NULL_PTR) && (pEnd != NULL_PTR))
    {
        pDesc = pStart;

        while (pDesc != pEnd)
        {
            Enet_SetupRxDesc(pDesc, 0u != pEnetHandle->ItMode);
            pDesc = Enet_NextDescriptor(pDesc, &pEnetHandle->RxDescLists[eChannel]);
        }
        Enet_SetupRxDesc(pDesc, 0u != pEnetHandle->ItMode);
        ENET_HWA_DMA_SetRxDescListTailAddr(pEnetHandle->EnetBase,
                                (ENET_DMA_ChannelType)eChannel, (uint32_t)pDesc);
    }
}

/**
 * @brief                       Get available data from DMA RX descriptors
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          DMA channel to use
 * @param[out] pBuffers         Buffer chain to receive data
 * @param[out] pInfo            Received data information
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Receive frame successfully
 * @retval other values         No frame is available,or an error occurred
 */
static ENET_StatusType Enet_GetRxBuffers(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                         ENET_BufferType *pBuffers, ENET_RxInfoType *pInfo)
{
    ENET_StatusType eStatus = ENET_STATUS_ERROR;
    ENET_DescListType *pDescList;
    ENET_DMADescType *pDescTail, *pDesc;
    ENET_BufferType *pBuf = pBuffers;
    uint16_t u32AccumulatedLen = 0u;

    pDescList = &pEnetHandle->RxDescLists[eChannel];
    pDescTail = (ENET_DMADescType *)ENET_HWA_DMA_GetRxDescListTailAddr(pEnetHandle->EnetBase,
                                                              (ENET_DMA_ChannelType)eChannel);

    pDesc = Enet_NextDescriptor(pDescTail, pDescList);
    pDescList->FirstDesc = NULL_PTR;
    pDescList->LastDesc = NULL_PTR;

    while (((pDesc->Des3 & ENET_DES3_OWN_MASK) == 0u) && (pBuf != NULL_PTR) && (pDesc != pDescTail))
    {
        /* Handle LD descriptor */
        if ((pDesc->Des3 & ENET_RDES3_LD_MASK) != 0u)
        {
            if (((pDesc->Des3 & ENET_RDES3_FD_MASK) != 0u) || (pDescList->FirstDesc != NULL_PTR))
            {
                /* Single descriptor frame */
                if ((pDesc->Des3 & ENET_RDES3_FD_MASK) != 0u)
                {
                    if (pDescList->FirstDesc != NULL_PTR)
                    {
                        Enet_ReleaseRxDescriptors(pEnetHandle, eChannel, pDescList->FirstDesc, pDescList->LastDesc);
                    }
                    pDescList->FirstDesc = pDesc;
                    pBuf = pBuffers;
                    u32AccumulatedLen = 0u;
                }

                pDescList->LastDesc = pDesc;
                pBuffers->TotalLength = (uint16_t)(pDesc->Des3 & ENET_RDES3_PACKET_LENGTH_MASK);
                pBuf->Data = (uint8_t *)pDesc->BackupInfo0;
                pBuf->Length = (uint16_t)(pBuffers->TotalLength - u32AccumulatedLen);
                pBuf->Next = NULL_PTR;

                /* Check following descriptor is context descriptor or not */
                pDesc = Enet_NextDescriptor(pDesc, pDescList);
                if ((pDesc->Des3 & ENET_DES3_OWN_MASK) == 0u)
                {
                    if (0u != (pDesc->Des3 & ENET_DES3_CTXT_MASK))
                    {
                        pDescList->LastDesc = pDesc;
                        if (pInfo != NULL_PTR)
                        {
                            Enet_ReadRxDescTimestamp(pEnetHandle, pDesc, &pInfo->TimeStamp);
                            pInfo->Attributes |= (uint32_t)ENET_RX_ATTRIBUTES_TIMESTAMP_VALID;
                        }
                    }
                }

                eStatus = ENET_STATUS_SUCCESS;
                break;
            }
            else
            {
                /* NO FD descriptor found, release current descriptor and jump to next descriptor */
                Enet_ReleaseRxDescriptors(pEnetHandle, eChannel, pDesc, pDesc);
                pDescList->LastDesc = NULL_PTR;
                pDesc = Enet_NextDescriptor(pDesc, pDescList);
            }
        }
        /* Handle FD descriptor */
        else if ((pDesc->Des3 & ENET_RDES3_FD_MASK) != 0u)
        {
            if (pDescList->FirstDesc != NULL_PTR)
            {
                /* continuous FD descriptors with no LD descriptor, eg: FD ... FD .. LD */
                Enet_ReleaseRxDescriptors(pEnetHandle, eChannel, pDescList->FirstDesc, pDescList->LastDesc);
            }
            /* Start receive data */
            pBuf = pBuffers;
            pDescList->FirstDesc = pDesc;
            pDescList->LastDesc = pDesc;
            u32AccumulatedLen = (uint16_t)(pDesc->Des3 & ENET_RDES3_PACKET_LENGTH_MASK);
            pBuf->Data = (uint8_t *)pDesc->BackupInfo0;
            pBuf->Length = pDescList->BufferLen;

            pBuf = pBuf->Next;
            pDesc = Enet_NextDescriptor(pDesc, pDescList);
        }
        /* Handle descriptor with FD LD not set */
        else
        {
            if (pDescList->FirstDesc == NULL_PTR)
            {
                /* First descriptor not found,release current  descriptor to DMA */
                Enet_ReleaseRxDescriptors(pEnetHandle, eChannel, pDesc, pDesc);
                pDesc = Enet_NextDescriptor(pDesc, pDescList);
            }
            else
            {
                /* Handle descriptors between FD and LD */
                if ((pDesc->Des3 & ENET_DES3_CTXT_MASK) == 0u)
                {
                    pDescList->LastDesc = pDesc;
                    u32AccumulatedLen = (uint16_t)(pDesc->Des3 & ENET_RDES3_PACKET_LENGTH_MASK);
                    pBuf->Data = (uint8_t *)pDesc->BackupInfo0;
                    pBuf->Length = pDescList->BufferLen;
                    pBuf = pBuf->Next;
                }
                else
                {
                    /* Abnormal context descriptor,handle nothing */
                    pDescList->LastDesc = pDesc;
                }

                pDesc = Enet_NextDescriptor(pDesc, pDescList);
            }
        }
    }

    /* If receive failed, release RX descriptors */
    if (ENET_STATUS_SUCCESS != eStatus)
    {
        Enet_ReleaseRxDescriptors(pEnetHandle, eChannel, pDescList->FirstDesc, pDescList->LastDesc);
        pDescList->FirstDesc = NULL_PTR;
        pDescList->LastDesc = NULL_PTR;
    }

    return eStatus;
}

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
                               ENET_BufferType *pBuffers, ENET_RxInfoType *pInfo)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_READ_FRAME_SERVICE_ID))
    {
        if (pBuffers == NULL_PTR)
        {
            ENET_ReportDevError(ENET_READ_FRAME_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State != ENET_STATE_READY)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_READ_FRAME_SERVICE_ID, ENET_E_CONTROLLER_MODE);
            }
            else
            {
                if (eChannel >=  pEnetHandle->RxChannelCount)
                {
                    ENET_ReportDevError(ENET_READ_FRAME_SERVICE_ID, ENET_E_PARAM_RXCHANNEL);
                }
                else
                {
#endif

                    if (ENET_STATE_READY == pEnetHandle->RxState)
                    {
                        pEnetHandle->RxState = ENET_STATE_BUSY;
                        if (pInfo != NULL_PTR)
                        {
                            pInfo->Attributes = 0u;
                        }
                        eStatus = Enet_GetRxBuffers(pEnetHandle, eChannel, pBuffers, pInfo);
                        if (ENET_STATUS_SUCCESS == eStatus)
                        {
                            pEnetHandle->RxState = ENET_STATE_WAIT_RELEASE;
                        }
                        else
                        {
                            pEnetHandle->RxState = ENET_STATE_READY;
                        }
                    }
                    else
                    {
                        eStatus = ENET_STATUS_BUSY;
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Build RX Descriptors to DMA
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          DMA channel to use
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Descriptors are released to DMA successfully
 * @retval other values         Descriptors are released to DMA failed
 */
ENET_StatusType Enet_BuildRxDescriptors(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel)
{
    ENET_DescListType *pDescList;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_BUILD_RXDESC_SERVICE_ID))
    {
        if (pEnetHandle->State != ENET_STATE_READY)
        {
            eStatus = ENET_STATUS_NOT_READY;
            ENET_ReportDevError(ENET_BUILD_RXDESC_SERVICE_ID, ENET_E_CONTROLLER_MODE);
        }
        else
        {
            if (eChannel >=  pEnetHandle->RxChannelCount)
            {
                ENET_ReportDevError(ENET_BUILD_RXDESC_SERVICE_ID, ENET_E_PARAM_RXCHANNEL);
            }
            else
            {
#endif

                if (ENET_STATE_WAIT_RELEASE == pEnetHandle->RxState)
                {
                    pDescList = &pEnetHandle->RxDescLists[eChannel];
                    Enet_ReleaseRxDescriptors(pEnetHandle, eChannel, pDescList->FirstDesc, pDescList->LastDesc);
                    pEnetHandle->RxState = ENET_STATE_READY;
                    eStatus = ENET_STATUS_SUCCESS;
                }
                else
                {
                    eStatus = ENET_STATUS_NOT_READY;
                }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Get MDIO bus default configuration
 * @param[out] pMiiConfig       MDIO configure parameters
 */
void Enet_MDIODefaultConfig(ENET_MiiConfigType *pMiiConfig)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (pMiiConfig == NULL_PTR)
    {
        ENET_ReportDevError(ENET_MDIO_DEFCONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
    }
    else
    {
#endif

        pMiiConfig->PreambleSuppress = false;
        pMiiConfig->BackToBack = false;
        pMiiConfig->TrailingClocks = 0u;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Initialize the MDIO bus
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMiiConfig        MDIO configure parameters
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Initialize the MDIO bus successfully
 * @retval other values         Initialize the MDIO bus failed
 */
ENET_StatusType Enet_MDIOInit(ENET_HandleType *pEnetHandle, const ENET_MiiConfigType *pMiiConfig)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint8_t i;
    uint8_t u8Csr = ENET_MAC_CSR_CLOCK_RANGE_100_150MHZ;
    uint32_t u32CsrClk;
    ENET_Type *pEnetBase[ENET_INSTANCE_COUNT] = ENET_BASE_PTRS;
    const uint32_t FreqRange[] = {35000000u, 60000000u, 100000000u, 150000000u, 250000000u, 300000000u};
    const uint8_t CsrValues[] = {(uint8_t)ENET_MAC_CSR_CLOCK_RANGE_20_35MHZ,
                                 (uint8_t)ENET_MAC_CSR_CLOCK_RANGE_35_60MHZ,
                                 (uint8_t)ENET_MAC_CSR_CLOCK_RANGE_60_100MHZ,
                                 (uint8_t)ENET_MAC_CSR_CLOCK_RANGE_100_150MHZ,
                                 (uint8_t)ENET_MAC_CSR_CLOCK_RANGE_150_250MHZ,
                                 (uint8_t)ENET_MAC_CSR_CLOCK_RANGE_250_300MHZ
                                };

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MDIO_INIT_SERVICE_ID))
    {
        if (pMiiConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_MDIO_INIT_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if ((pMiiConfig->TrailingClocks >= (1u << ENET_MAC_MDIO_ADDRESS_NTC_WIDTH)) ||
                (pMiiConfig->TrailingClocks == 0u && pMiiConfig->BackToBack == true))
            {
                ENET_ReportDevError(ENET_MDIO_INIT_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
#endif
                if (pEnetHandle->EnetBase == NULL_PTR)
                {
                    pEnetHandle->EnetBase = pEnetBase[pEnetHandle->eInstance];
                }

#if ENET_CSR_INTERFACE_CORE_CLOCK
                u32CsrClk = SCG_GetScgClockFreq(SCG_CORE_CLK);
#else
                u32CsrClk = SCG_GetScgClockFreq(SCG_BUS_CLK);
#endif
                if (u32CsrClk != 0u)
                {
                    for (i = 0u; i < sizeof(FreqRange) / sizeof(uint32_t); ++i)
                    {
                        if (u32CsrClk <= FreqRange[i])
                        {
                            u8Csr = CsrValues[i];
                            break;
                        }
                    }

                    ENET_HWA_MAC_SetMDIOAddress(pEnetHandle->EnetBase,
                                ENET_MAC_MDIO_ADDRESS_PSE(pMiiConfig->PreambleSuppress ? 1u : 0u) |
                                ENET_MAC_MDIO_ADDRESS_BTB(pMiiConfig->BackToBack ? 1u : 0u)       |
                                ENET_MAC_MDIO_ADDRESS_NTC(pMiiConfig->TrailingClocks)             |
                                ENET_MAC_MDIO_ADDRESS_CR(u8Csr));
                    eStatus = ENET_STATUS_SUCCESS;
                }
                else
                {
                    eStatus = ENET_STATUS_ERROR;
                }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
         }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Writes the MDIO bus access register
 * @param[in] pBase             ENET base
 * @param[in] bClause45         Enable clause 45 mode
 * @param[in] u8Opt             MDIO operation,read write or read increment address
 * @param[in] u8PhyAddr         PHY device address
 * @param[in] u16PhyReg         PHY register address
 * @param[in] u8MmdAddr         Clause 45 MMD address
 * @param[in] pData             Data to write
 * @param[in] u32TimeoutUs      Wait time out value in microsecond
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  MDIO write successfully
 * @retval other values         MDIO write failed
 */
static ENET_StatusType Enet_MDIOWriteAddress(ENET_Type *pBase, bool bClause45, ENET_MiiOptType u8Opt, uint8_t u8PhyAddr,
                                             uint16_t u16PhyReg, uint8_t u8MmdAddr, uint16_t *pData, uint32_t u32TimeoutUs)
{
    uint32_t AddressReg = 0u, DataReg = 0u;
    ENET_StatusType eStatus = ENET_STATUS_SUCCESS;

    AddressReg = ENET_HWA_MAC_GetMDIOAddress(pBase);

    AddressReg &= ~(ENET_MAC_MDIO_ADDRESS_PA_MASK |
                    ENET_MAC_MDIO_ADDRESS_RDA_MASK |
                    ENET_MAC_MDIO_ADDRESS_GOC_0_MASK |
                    ENET_MAC_MDIO_ADDRESS_GOC_1_MASK |
                    ENET_MAC_MDIO_ADDRESS_C45E_MASK);

    AddressReg |= ENET_MAC_MDIO_ADDRESS_C45E(bClause45 ? 1u : 0u) |
                  (uint32_t)u8Opt |
                  ENET_MAC_MDIO_ADDRESS_PA(u8PhyAddr) |
                  ENET_MAC_MDIO_ADDRESS_RDA(bClause45 ? u8MmdAddr : u16PhyReg) |
                  ENET_MAC_MDIO_ADDRESS_GB_MASK;

    if (bClause45 || (ENET_MII_WRITE == u8Opt))
    {
        DataReg = ENET_MAC_MDIO_DATA_RA(bClause45 ? u16PhyReg : 0u) |
                  ENET_MAC_MDIO_DATA_GD((ENET_MII_WRITE == u8Opt) ? *pData : 0u);
        ENET_HWA_MAC_SetMDIOData(pBase, DataReg);
    }

    ENET_HWA_MAC_SetMDIOAddress(pBase, AddressReg);

    /* Wait for completion */
    while (0u != (ENET_HWA_MAC_GetMDIOAddress(pBase) & ENET_MAC_MDIO_ADDRESS_GB_MASK))
    {
        if (--u32TimeoutUs == 0u)
        {
            eStatus = ENET_STATUS_TIMEOUT;
            break;
        }
    }

    return eStatus;
}

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
                              uint16_t *pData, uint32_t u32TimeoutUs)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MDIO_READ_SERVICE_ID))
    {
        if (pData == NULL_PTR)
        {
            ENET_ReportDevError(ENET_MDIO_READ_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if ((u8PhyAddr >= 32u) || (u8PhyReg >= 32u))
            {
                ENET_ReportDevError(ENET_MDIO_READ_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->EnetBase == NULL_PTR)
                {
                    eStatus = ENET_STATUS_NOT_READY;
                    ENET_ReportDevError(ENET_MDIO_READ_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    eStatus = Enet_MDIOWriteAddress(pEnetHandle->EnetBase, false, ENET_MII_READ, u8PhyAddr, (uint16_t)u8PhyReg, 0u, pData, u32TimeoutUs);
                    if (eStatus == ENET_STATUS_SUCCESS)
                    {
                        *pData = (uint16_t)ENET_HWA_MAC_GetMDIOData(pEnetHandle->EnetBase);
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
    return eStatus;
}

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
                               uint16_t u16Data, uint32_t u32TimeoutUs)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MDIO_WRITE_SERVICE_ID))
    {

        if ((u8PhyAddr >= 32u) || (u8PhyReg >= 32u))
        {
            ENET_ReportDevError(ENET_MDIO_WRITE_SERVICE_ID, ENET_E_PARAM_ASSERTION);
        }
        else
        {
            if (pEnetHandle->EnetBase == NULL_PTR)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_MDIO_WRITE_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                eStatus = Enet_MDIOWriteAddress(pEnetHandle->EnetBase, false, ENET_MII_WRITE, u8PhyAddr,
                                                (uint16_t)u8PhyReg, 0u, &u16Data, u32TimeoutUs);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
    return eStatus;
}

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
                             uint16_t u16PhyReg, uint16_t *pData, uint32_t u32TimeoutUs)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMD_READ_SERVICE_ID))
    {
        if (pData == NULL_PTR)
        {
            ENET_ReportDevError(ENET_MMD_READ_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (u8PhyAddr >= 32u)
            {
                ENET_ReportDevError(ENET_MMD_READ_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->EnetBase == NULL_PTR)
                {
                    eStatus = ENET_STATUS_NOT_READY;
                    ENET_ReportDevError(ENET_MMD_READ_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    eStatus = Enet_MDIOWriteAddress(pEnetHandle->EnetBase, true, ENET_MII_READ,
                                             u8PhyAddr, u16PhyReg, u8Mmd, pData, u32TimeoutUs);
                    if (eStatus == ENET_STATUS_SUCCESS)
                    {
                        *pData = (uint16_t)ENET_HWA_MAC_GetMDIOData(pEnetHandle->EnetBase);
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif

    return eStatus;
}

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
                              uint16_t u16PhyReg, uint16_t u16Data, uint32_t u32TimeoutUs)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMD_WRITE_SERVICE_ID))
    {
        if (u8PhyAddr >= 32u)
        {
            ENET_ReportDevError(ENET_MMD_WRITE_SERVICE_ID, ENET_E_PARAM_ASSERTION);
        }
        else
        {
            if (pEnetHandle->EnetBase == NULL_PTR)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_MMD_WRITE_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                eStatus = Enet_MDIOWriteAddress(pEnetHandle->EnetBase, true, ENET_MII_WRITE,
                                        u8PhyAddr, u16PhyReg, u8Mmd, &u16Data, u32TimeoutUs);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Set MAC0 address
 * @param[in] EnetBase          ENET register base address
 * @param[in] pMacAddr          MAC address
 * @param[in] u8MacLen          MAC address length
 */
static void Enet_MacAddressConfig(ENET_Type *EnetBase, const uint8_t *pMacAddr, uint8_t u8MacLen)
{
    uint32_t u32RegVal;
    (void)u8MacLen;

    /* Set physical address high register. */
    u32RegVal = (uint32_t)pMacAddr[4u]         |
                ((uint32_t)pMacAddr[5u] << 8u) |
                ENET_MAC_ADDRESS0_HIGH_AE_MASK;
    ENET_HWA_MAC_SetAddr0High(EnetBase, u32RegVal);

    /* Set physical address lower register. */
    u32RegVal = (uint32_t)pMacAddr[0u]         |
                ((uint32_t)pMacAddr[1u] << 8u) |
                ((uint32_t)pMacAddr[2u] << 16u) |
                ((uint32_t)pMacAddr[3u] << 24u);
    ENET_HWA_MAC_SetMacAddr0Low(EnetBase, u32RegVal);
}

/**
 * @brief                       Set MAC0 address
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMacAddr          MAC address
 * @param[in] u8MacLen          MAC address length
 */
void Enet_SetMacAddress(ENET_HandleType *pEnetHandle, const uint8_t *pMacAddr, uint8_t u8MacLen)
{

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_MACADDR_SERVICE_ID))
    {
        if (pMacAddr == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_MACADDR_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (u8MacLen != ENET_MAC_ADDRESS_LENGTH)
            {
                ENET_ReportDevError(ENET_SET_MACADDR_SERVICE_ID, ENET_E_PARAM_MACLEN);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_SET_MACADDR_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    Enet_MacAddressConfig(pEnetHandle->EnetBase, pMacAddr, u8MacLen);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Enable TCPIP checksum error filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          ENET channel
 * @param[in] bEnable           Enable MAC to drop packets with checksum error
 */
void Enet_CheckSumErrorFilter(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel, bool bEnable)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_CKSUM_ERROR_FILTER_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_CKSUM_ERROR_FILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
            if ((uint8_t)eChannel >=  pEnetHandle->RxChannelCount)
            {
                ENET_ReportDevError(ENET_CKSUM_ERROR_FILTER_SERVICE_ID, ENET_E_PARAM_RXCHANNEL);
            }
            else
            {
#endif

                ENET_HWA_MTL_SetForwardTCPChecksumErrorPacketEnFlag(pEnetHandle->EnetBase,
                                                                    (ENET_MTL_QueueType)eChannel, !bEnable);
                if (bEnable)
                {
                    ENET_HWA_MAC_SetIPChecksumOffloadEnFlag(pEnetHandle->EnetBase, bEnable);
                }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
}

/**
 * @brief                       Compute CRC value
 * @param[in] pData             Pointer to data
 * @param[in] u32BitLen         Data bits length
 */
static uint32_t Enet_ComputeCRC(const uint8_t *pData, uint32_t u32BitLen)
{
    uint32_t u32Crc = 0xFFFFFFFFu;
    uint32_t i, j, bytes, bits;

    bytes = (u32BitLen + 0x7u) >> 3u;
    for (i = 0u; i < bytes; ++i)
    {
        u32Crc = u32Crc ^ pData[i];
        bits = (u32BitLen >= 0x8u) ? 0x8u : u32BitLen;
        for (j = 0u; j < bits; ++j)
        {
            if ((u32Crc & 0x1u) != 0u)
            {
                u32Crc = (u32Crc >> 1u) ^ 0xEDB88320u;
            }
            else
            {
                u32Crc = (u32Crc >> 1u);
            }
        }
        u32BitLen -= bits;
    }

    return ~u32Crc;
}

/**
 * @brief                       Reverse bits of uint32_t
 * @param[in] u32Data           Original data
 * @return                      Reversed data
 */
static inline uint32_t Enet_BitsReverse(uint32_t u32Data)
{
    uint32_t u32Tmp = u32Data;
    u32Tmp = (((u32Tmp & (0xAAAAAAAAu)) >> 1u) | ((u32Tmp & (0x55555555u)) << 1u));
    u32Tmp = (((u32Tmp & (0xCCCCCCCCu)) >> 2u) | ((u32Tmp & (0x33333333u)) << 2u));
    u32Tmp = (((u32Tmp & (0xF0F0F0F0u)) >> 4u) | ((u32Tmp & (0x0F0F0F0Fu)) << 4u));
    u32Tmp = (((u32Tmp & (0xFF00FF00u)) >> 8u) | ((u32Tmp & (0x00FF00FFu)) << 8u));
    return ((u32Tmp >> 16u) | (u32Tmp << 16u));
}

/**
 * @brief                       Set hash table for MAC hash filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bAddOrRemove      true: add,false: remove
 * @param[in] pMacAddr          MAC address
 * @param[in] u8MacLen          MAC address length
 */
void Enet_SetMacHashTable(ENET_HandleType *pEnetHandle, bool bAddOrRemove, const uint8_t *pMacAddr, uint8_t u8MacLen)
{
    volatile uint32_t *pHashTable;
    uint32_t u32CrcVal;
    uint32_t u32Index, u32HashBit;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_MACHASH_SERVICE_ID))
    {
        if (pMacAddr == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_MACHASH_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (u8MacLen != ENET_MAC_ADDRESS_LENGTH)
            {
                ENET_ReportDevError(ENET_SET_MACHASH_SERVICE_ID, ENET_E_PARAM_MACLEN);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_SET_MACHASH_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#else
                    (void)u8MacLen;
#endif

                    pHashTable = (volatile uint32_t *)&pEnetHandle->EnetBase->MAC_HASH_TABLE_REG0;

                    u32CrcVal = Enet_ComputeCRC(pMacAddr, ENET_MAC_ADDRESS_LENGTH * 0x8u);
                    u32CrcVal = Enet_BitsReverse(u32CrcVal);
                    u32Index = (u32CrcVal >> ENET_MAC_HASH_TABLE_INDEX_SHIFT) & ENET_MAC_HASH_TABLE_INDEX_MASK;
                    u32HashBit = (u32CrcVal >> ENET_MAC_HASH_TABLE_BIT_SHIFT) & ENET_MAC_HASH_TABLE_BIT_MASK;

                    if (bAddOrRemove)
                    {
                        pHashTable[u32Index] |= 1u << u32HashBit;
                    }
                    else
                    {
                        pHashTable[u32Index] &= ~(1u << u32HashBit);
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Get default MAC filter configurations
 * @param[in] pMACFilter        MAC filter Default configurations
 */
void Enet_DefaultMACFilter(ENET_MACFilterType *pMACFilter)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (pMACFilter == NULL_PTR)
    {
        ENET_ReportDevError(ENET_DEFAULT_MACFILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
    }
    else
    {
#endif
        pMACFilter->ReceiveAll = ENET_FALSE;
        pMACFilter->DropNonTcpUdpOverIp = ENET_FALSE;
        pMACFilter->HashOrPerfectFilter = ENET_TRUE;
        pMACFilter->SAFilter = ENET_FILTER_DISABLE;
        pMACFilter->PassCtrlPkts = ENET_MAC_CTRL_PACKET_FILTER_ALL;
        pMACFilter->DisableBroadcast = ENET_FALSE;
        pMACFilter->PassAllMulticast = ENET_FALSE;
        pMACFilter->DAFilter = ENET_FILTER_ENABLE;
        pMACFilter->HashMulticast = ENET_TRUE;
        pMACFilter->HashUnicast = ENET_FALSE;
        pMACFilter->PromiscuousMode = ENET_FALSE;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Get current MAC filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMACFilter        MAC filter Current configurations
 */
void Enet_GetMACFilter(const ENET_HandleType *pEnetHandle, ENET_MACFilterType *pMACFilter)
{
    uint32_t u32FilterCtrl, u32Temp;
    bool bInverse;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_GET_MACFILTER_SERVICE_ID))
    {
        if (pMACFilter == NULL_PTR)
        {
            ENET_ReportDevError(ENET_GET_MACFILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_GET_MACFILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                u32FilterCtrl = ENET_HWA_MAC_GetPacketFilter(pEnetHandle->EnetBase);

                pMACFilter->ReceiveAll = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_RA_MASK);
                pMACFilter->PromiscuousMode = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_PR_MASK);
                pMACFilter->DropNonTcpUdpOverIp = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_DNTU_MASK);
                pMACFilter->HashOrPerfectFilter = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_HPF_MASK);
                bInverse = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_SAIF_MASK);
                pMACFilter->SAFilter = (0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_SAF_MASK)) ?
                                            (bInverse ? ENET_FILTER_INVERSE_ENABLE : ENET_FILTER_ENABLE) : ENET_FILTER_DISABLE;
                u32Temp = (u32FilterCtrl & ENET_MAC_PACKET_FILTER_PCF_MASK) >> ENET_MAC_PACKET_FILTER_PCF_SHIFT;
                pMACFilter->PassCtrlPkts = (ENET_MAC_CtrlPacketFilterModeType)u32Temp;
                pMACFilter->DisableBroadcast = (u32FilterCtrl & ENET_MAC_PACKET_FILTER_DBF_MASK) != 0u ? true : false;
                pMACFilter->PassAllMulticast = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_PM_MASK);
                pMACFilter->DAFilter = (0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_DAIF_MASK)) ?
                                            ENET_FILTER_INVERSE_ENABLE : ENET_FILTER_ENABLE;
                pMACFilter->HashMulticast = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_HMC_MASK);
                pMACFilter->HashUnicast = 0u != (u32FilterCtrl & ENET_MAC_PACKET_FILTER_HUC_MASK);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
}

/**
 * @brief                       Configure the MAC filter register
 * @param[in] pEnetBase         ENET register base address
 * @param[in] pMACFilter        MAC filter configurations
 */
static inline void Enet_MACFilterConfig(ENET_Type *pEnetBase, const ENET_MACFilterType *pMACFilter)
{
    uint32_t u32FilterCtrl;

    u32FilterCtrl = ENET_HWA_MAC_GetPacketFilter(pEnetBase);
    u32FilterCtrl &= ~(ENET_MAC_PACKET_FILTER_RA_MASK   |
                       ENET_MAC_PACKET_FILTER_DNTU_MASK   |
                       ENET_MAC_PACKET_FILTER_HPF_MASK    |
                       ENET_MAC_PACKET_FILTER_SAF_MASK    |
                       ENET_MAC_PACKET_FILTER_SAIF_MASK   |
                       ENET_MAC_PACKET_FILTER_PCF_MASK    |
                       ENET_MAC_PACKET_FILTER_DBF_MASK    |
                       ENET_MAC_PACKET_FILTER_PM_MASK     |
                       ENET_MAC_PACKET_FILTER_DAIF_MASK   |
                       ENET_MAC_PACKET_FILTER_HMC_MASK    |
                       ENET_MAC_PACKET_FILTER_HUC_MASK    |
                       ENET_MAC_PACKET_FILTER_PR_MASK);

    u32FilterCtrl |= ENET_MAC_PACKET_FILTER_RA(pMACFilter->ReceiveAll ? 1u : 0u)                               |
                     ENET_MAC_PACKET_FILTER_DNTU(pMACFilter->DropNonTcpUdpOverIp ? 1u : 0u)                    |
                     ENET_MAC_PACKET_FILTER_HPF(pMACFilter->HashOrPerfectFilter ? 1u : 0u)                     |
                     ENET_MAC_PACKET_FILTER_SAF(pMACFilter->SAFilter != ENET_FILTER_DISABLE ? 1u : 0u)         |
                     ENET_MAC_PACKET_FILTER_SAIF(pMACFilter->SAFilter == ENET_FILTER_INVERSE_ENABLE ? 1u : 0u) |
                     ENET_MAC_PACKET_FILTER_PCF(pMACFilter->PassCtrlPkts)                                      |
                     ENET_MAC_PACKET_FILTER_DBF(pMACFilter->DisableBroadcast ? 1u : 0u)                        |
                     ENET_MAC_PACKET_FILTER_PM(pMACFilter->PassAllMulticast ? 1u : 0u)                         |
                     ENET_MAC_PACKET_FILTER_DAIF(pMACFilter->DAFilter == ENET_FILTER_INVERSE_ENABLE ? 1u : 0u) |
                     ENET_MAC_PACKET_FILTER_HMC(pMACFilter->HashMulticast ? 1u : 0u)                           |
                     ENET_MAC_PACKET_FILTER_HUC(pMACFilter->HashUnicast ? 1u : 0u)                             |
                     ENET_MAC_PACKET_FILTER_PR(pMACFilter->PromiscuousMode ? 1u : 0u);

    ENET_HWA_MAC_SetPacketFilter(pEnetBase, u32FilterCtrl);
}

/**
 * @brief                       Set MAC filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMACFilter        MAC filter configurations
 */
void Enet_SetMACFilter(ENET_HandleType *pEnetHandle, const ENET_MACFilterType *pMACFilter)
{

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_MACFILTER_SERVICE_ID))
    {
        if (pMACFilter == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_MACFILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (0u != Enet_AssertMACFilterConfiguration(pMACFilter))
            {
                ENET_ReportDevError(ENET_SET_MACFILTER_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_SET_MACFILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    Enet_MACFilterConfig(pEnetHandle->EnetBase, pMACFilter);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Get default layer3 layer4 filter configurations
 * @param[out] pL3L4Filter      Default layer3 layer4 filter configurations
 */
void Enet_DefaultL3L4Filter(ENET_L3L4FilterType *pL3L4Filter)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (pL3L4Filter == NULL_PTR)
    {
        ENET_ReportDevError(ENET_DEFAULT_L3L4FILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
    }
    else
    {
#endif

        pL3L4Filter->DMAChannelSelect = false;
        pL3L4Filter->DMAChannel = ENET_CHANNEL_0;
        pL3L4Filter->L4Protocol = ENET_MAC_LAYER_4_PROTOCOL_TCP;
        pL3L4Filter->DstPortFilter = ENET_FILTER_DISABLE;
        pL3L4Filter->SrcPortFilter = ENET_FILTER_DISABLE;
        pL3L4Filter->DstPort = 0u;
        pL3L4Filter->SrcPort = 0u;
        pL3L4Filter->L3Protocol = ENET_MAC_LAYER_3_PROTOCOL_IPV4;
        pL3L4Filter->DstIPFilter = ENET_FILTER_DISABLE;
        pL3L4Filter->SrcIPFilter = ENET_FILTER_DISABLE;
        pL3L4Filter->Ipv4DAMaskBit = 0u;
        pL3L4Filter->Ipv4SAMaskBit = 0u;
        pL3L4Filter->IPv4SrcAddr = 0u;
        pL3L4Filter->IPv4DstAddr = 0u;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Get current layer3 layer4 filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFilterGroup      Layer3 layer4 filter group
 * @param[in] pL3L4Filter       Current layer3 layer4 filter configurations
 */
void Enet_GetL3L4Filter(const ENET_HandleType *pEnetHandle, ENET_MAC_L3L4FilterGroupType pFilterGroup,
                        ENET_L3L4FilterType *pL3L4Filter)
{
    bool bInverse;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_GET_L3L4FILTER_SERVICE_ID))
    {
        if (pL3L4Filter == NULL_PTR)
        {
            ENET_ReportDevError(ENET_GET_L3L4FILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if((uint32_t)pFilterGroup >= (uint32_t)ENET_L3L4_FILTER_COUNT)
            {
                ENET_ReportDevError(ENET_GET_L3L4FILTER_SERVICE_ID, ENET_E_PARAM_GROUP);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_GET_L3L4FILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    pL3L4Filter->DMAChannelSelect = ENET_HWA_MAC_GetLayer3Layer4DMASelectEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    pL3L4Filter->DMAChannel = (ENET_ChannelType)ENET_HWA_MAC_GetLayer3Layer4DMAChannel(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);

                    bInverse = ENET_HWA_MAC_GetLayer4DestPortInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    pL3L4Filter->DstPortFilter = ENET_HWA_MAC_GetLayer4DestPortMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup) ?
                                                 (bInverse ? ENET_FILTER_INVERSE_ENABLE : ENET_FILTER_ENABLE) : ENET_FILTER_DISABLE;
                    bInverse = ENET_HWA_MAC_GetLayer4SrcPortInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    pL3L4Filter->SrcPortFilter = ENET_HWA_MAC_GetLayer4SrcPortMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup) ?
                                                 (bInverse ? ENET_FILTER_INVERSE_ENABLE : ENET_FILTER_ENABLE) : ENET_FILTER_DISABLE;
                    pL3L4Filter->L4Protocol = ENET_HWA_MAC_GetLayer4ProtocalType(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    pL3L4Filter->DstPort = ENET_HWA_MAC_GetLayer4DestPort(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    pL3L4Filter->SrcPort = ENET_HWA_MAC_GetLayer4SrcPort(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);

                    pL3L4Filter->L3Protocol = ENET_HWA_MAC_GetLayer3ProtocolType(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    bInverse = ENET_HWA_MAC_GetLayer3DestAddrInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    pL3L4Filter->DstIPFilter = ENET_HWA_MAC_GetLayer3DestAddrMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup) ?
                                               (bInverse ? ENET_FILTER_INVERSE_ENABLE : ENET_FILTER_ENABLE) : ENET_FILTER_DISABLE;
                    bInverse = ENET_HWA_MAC_GetLayer3SrcAddrInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    pL3L4Filter->SrcIPFilter = ENET_HWA_MAC_GetLayer3SrcAddrMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup) ?
                                               (bInverse ? ENET_FILTER_INVERSE_ENABLE : ENET_FILTER_ENABLE) : ENET_FILTER_DISABLE;

                    if (pL3L4Filter->L3Protocol == ENET_MAC_LAYER_3_PROTOCOL_IPV4)
                    {
                        pL3L4Filter->Ipv4DAMaskBit = ENET_HWA_MAC_GetLayer3IPv4DestAddrBitsMatch(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                        pL3L4Filter->Ipv4SAMaskBit = ENET_HWA_MAC_GetLayer3IPv4SrcAddrBitsMatch(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                        pL3L4Filter->IPv4DstAddr = ENET_HWA_MAC_GetLayer3DestIPv4Addr(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                        pL3L4Filter->IPv4SrcAddr = ENET_HWA_MAC_GetLayer3SrcIPv4Addr(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    }
                    else
                    {
                        pL3L4Filter->Ipv6MaskBit = ENET_HWA_MAC_GetLayer3IPv6AddrBitsMatch(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                        ENET_HWA_MAC_GetLayer3IPv6Addr(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->IPv6Addr);
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Set layer3 layer4 filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFilterGroup      Layer3 layer4 filter group
 * @param[in] pL3L4Filter       Layer3 layer4 filter configurations
 */
void Enet_SetL3L4Filter(ENET_HandleType *pEnetHandle, ENET_MAC_L3L4FilterGroupType pFilterGroup,
                        const ENET_L3L4FilterType *pL3L4Filter)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_L3L4FILTER_SERVICE_ID))
    {
        if (pL3L4Filter == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_L3L4FILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if((uint32_t)pFilterGroup >= (uint32_t)ENET_L3L4_FILTER_COUNT)
            {
                ENET_ReportDevError(ENET_SET_L3L4FILTER_SERVICE_ID, ENET_E_PARAM_GROUP);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_SET_L3L4FILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
                    if (0u != Enet_AssertL3L4FilterConfiguration(pEnetHandle, pL3L4Filter))
                    {
                        ENET_ReportDevError(ENET_SET_L3L4FILTER_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                    }
                    else
                    {
#endif

                        ENET_HWA_MAC_SetLayer3Layer4DMASelectEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->DMAChannelSelect);
                        ENET_HWA_MAC_SetLayer3Layer4DMAChannel(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                               (ENET_DMA_ChannelType)pL3L4Filter->DMAChannel);
                        ENET_HWA_MAC_SetLayer4DestPortMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                  pL3L4Filter->DstPortFilter != ENET_FILTER_DISABLE);
                        ENET_HWA_MAC_SetLayer4DestPortInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                     pL3L4Filter->DstPortFilter == ENET_FILTER_INVERSE_ENABLE);
                        ENET_HWA_MAC_SetLayer4SrcPortMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                 pL3L4Filter->SrcPortFilter != ENET_FILTER_DISABLE);
                        ENET_HWA_MAC_SetLayer4SrcPortInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                    pL3L4Filter->SrcPortFilter == ENET_FILTER_INVERSE_ENABLE);
                        ENET_HWA_MAC_SetLayer4ProtocalType(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->L4Protocol);
                        ENET_HWA_MAC_SetLayer4DestPort(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->DstPort);
                        ENET_HWA_MAC_SetLayer4SrcPort(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->SrcPort);
                        ENET_HWA_MAC_SetLayer3DestAddrMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                  pL3L4Filter->DstIPFilter != ENET_FILTER_DISABLE);
                        ENET_HWA_MAC_SetLayer3DestAddrInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                     pL3L4Filter->DstIPFilter == ENET_FILTER_INVERSE_ENABLE);
                        ENET_HWA_MAC_SetLayer3SrcAddrMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                 pL3L4Filter->SrcIPFilter != ENET_FILTER_DISABLE);
                        ENET_HWA_MAC_SetLayer3SrcAddrInvMatchEnFlag(pEnetHandle->EnetBase, (uint8_t)pFilterGroup,
                                                                    pL3L4Filter->SrcIPFilter == ENET_FILTER_INVERSE_ENABLE);
                        ENET_HWA_MAC_SetLayer3ProtocolType(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->L3Protocol);

                        if (pL3L4Filter->L3Protocol == ENET_MAC_LAYER_3_PROTOCOL_IPV4)
                        {
                            ENET_HWA_MAC_SetLayer3IPv4DestAddrBitsMatch(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->Ipv4DAMaskBit);
                            ENET_HWA_MAC_SetLayer3IPv4SrcAddrBitsMatch(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->Ipv4SAMaskBit);
                            ENET_HWA_MAC_SetLayer3DestIPv4Addr(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->IPv4DstAddr);
                            ENET_HWA_MAC_SetLayer3SrcIPv4Addr(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->IPv4SrcAddr);
                        }
                        else
                        {
                            ENET_HWA_MAC_SetLayer3IPv6AddrBitsMatch(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->Ipv6MaskBit);
                            ENET_HWA_MAC_SetLayer3IPv6Addr(pEnetHandle->EnetBase, (uint8_t)pFilterGroup, pL3L4Filter->IPv6Addr);
                        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Enable MAC layer3 layer4 filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bEnable           true: enable layer3 layer4 filter, false: disable
 */
void Enet_EnableL3L4Filter(ENET_HandleType *pEnetHandle, bool bEnable)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_ENABLE_L3L4FILTER_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_ENABLE_L3L4FILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            ENET_HWA_MAC_SetLayer3Layer4FilterEnFlag(pEnetHandle->EnetBase, bEnable);
            ENET_HWA_MAC_SetIPChecksumOffloadEnFlag(pEnetHandle->EnetBase, bEnable);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       Get MAC VLAN filter configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanFilterConfig MAC VLAN filter configurations
 */
void Enet_GetVlanFilterConfig(const ENET_HandleType *pEnetHandle, ENET_VlanFilterConfigType *pVlanFilterConfig)
{
    bool u32Erivt, u32Ersvlm, u32Dovltc;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_GET_VLANFILTER_CFG_SERVICE_ID))
    {
        if (pVlanFilterConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_GET_VLANFILTER_CFG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_GET_VLANFILTER_CFG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                pVlanFilterConfig->VlanFilterEnable = ENET_HWA_MAC_GetVLANTagFilterEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->InnerVlanRxStatus = ENET_HWA_MAC_GetRxStatusInnerVLANTagEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->OuterVlanRxStatus = ENET_HWA_MAC_GetRxStatusVLANTagEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->DoubleVlanEnable = ENET_HWA_MAC_GetDoubleVLANProcessEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->SVlanEnable = ENET_HWA_MAC_GetSVLANEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->VlanInverseMatch = ENET_HWA_MAC_GetVLANInverseMatchEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->HashFilterEnable = ENET_HWA_MAC_GetVLANTagHashTableMatchEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->HashCompareMode = (ENET_MAC_VLANCompareType)ENET_HWA_MAC_Get12BitVLANTagEnFlag(pEnetHandle->EnetBase);
                pVlanFilterConfig->InnerVlanStrip = ENET_HWA_MAC_GetInnerVLANTagStripMode(pEnetHandle->EnetBase);
                pVlanFilterConfig->OuterVlanStrip = ENET_HWA_MAC_GetVLANTagStripMode(pEnetHandle->EnetBase);

                u32Erivt = ENET_HWA_MAC_GetInnerVLANTagCmpEnFlag(pEnetHandle->EnetBase);
                u32Ersvlm = ENET_HWA_MAC_GetRxSVLANMatchEnFlag(pEnetHandle->EnetBase);
                u32Dovltc = ENET_HWA_MAC_GetVLANTypeCheckDisableFlag(pEnetHandle->EnetBase);
                if (u32Dovltc)
                {
                    pVlanFilterConfig->HashFilterMode = u32Erivt ? ENET_VLAN_FILTER_INNER_ANYTYPE : ENET_VLAN_FILTER_OUTER_ANYTYPE;
                }
                else
                {
                    if (u32Erivt)
                    {
                        pVlanFilterConfig->HashFilterMode = u32Ersvlm ? ENET_VLAN_FILTER_INNER_SVLAN : ENET_VLAN_FILTER_INNER_CVLAN;
                    }
                    else
                    {
                        pVlanFilterConfig->HashFilterMode = u32Ersvlm ? ENET_VLAN_FILTER_OUTER_SVLAN : ENET_VLAN_FILTER_OUTER_CVLAN;
                    }
                }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
}

/**
 * @brief                       Enable MAC VLAN filter
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanFilterConfig MAC VLAN filter configurations
 */
void Enet_EnableVlanFilter(ENET_HandleType *pEnetHandle, const ENET_VlanFilterConfigType *pVlanFilterConfig)
{
    bool u32Erivt, u32Ersvlm, u32Dovltc;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_ENABLE_VLANFILTER_SERVICE_ID))
    {
        if (pVlanFilterConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_ENABLE_VLANFILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (0u != Enet_AssertVlanFilterConfiguration(pVlanFilterConfig))
            {
                ENET_ReportDevError(ENET_ENABLE_VLANFILTER_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_ENABLE_VLANFILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    ENET_HWA_MAC_SetRxStatusInnerVLANTagEnFlag(pEnetHandle->EnetBase, pVlanFilterConfig->InnerVlanRxStatus);
                    ENET_HWA_MAC_SetInnerVLANTagStripMode(pEnetHandle->EnetBase, pVlanFilterConfig->InnerVlanStrip);
                    ENET_HWA_MAC_SetDoubleVLANProcessEnFlag(pEnetHandle->EnetBase, pVlanFilterConfig->DoubleVlanEnable);
                    ENET_HWA_MAC_SetRxStatusVLANTagEnFlag(pEnetHandle->EnetBase, pVlanFilterConfig->OuterVlanRxStatus);
                    ENET_HWA_MAC_SetVLANTagStripMode(pEnetHandle->EnetBase, pVlanFilterConfig->OuterVlanStrip);
                    ENET_HWA_MAC_SetSVLANEnFlag(pEnetHandle->EnetBase, pVlanFilterConfig->SVlanEnable);
                    ENET_HWA_MAC_SetVLANInverseMatchEnFlag(pEnetHandle->EnetBase, pVlanFilterConfig->VlanInverseMatch);
                    ENET_HWA_MAC_SetVLANTagHashTableMatchEnFlag(pEnetHandle->EnetBase, pVlanFilterConfig->HashFilterEnable);
                    ENET_HWA_MAC_Set12BitVLANTagEnFlag(pEnetHandle->EnetBase, (bool)pVlanFilterConfig->HashCompareMode);

                    u32Erivt = ((pVlanFilterConfig->HashFilterMode == ENET_VLAN_FILTER_INNER_CVLAN) ||
                                (pVlanFilterConfig->HashFilterMode == ENET_VLAN_FILTER_INNER_SVLAN) ||
                                (pVlanFilterConfig->HashFilterMode == ENET_VLAN_FILTER_INNER_ANYTYPE)) ? true : false;
                    u32Ersvlm = ((pVlanFilterConfig->HashFilterMode == ENET_VLAN_FILTER_OUTER_SVLAN) ||
                                 (pVlanFilterConfig->HashFilterMode == ENET_VLAN_FILTER_INNER_SVLAN)) ? true : false;
                    u32Dovltc = ((pVlanFilterConfig->HashFilterMode == ENET_VLAN_FILTER_OUTER_ANYTYPE) ||
                                 (pVlanFilterConfig->HashFilterMode == ENET_VLAN_FILTER_INNER_ANYTYPE)) ? true : false;
                    ENET_HWA_MAC_SetInnerVLANTagCmpEnFlag(pEnetHandle->EnetBase, u32Erivt);
                    ENET_HWA_MAC_SetVLANTypeCheckDisableFlag(pEnetHandle->EnetBase, u32Dovltc);
                    ENET_HWA_MAC_SetRxSVLANMatchEnFlag(pEnetHandle->EnetBase, u32Ersvlm);

                    ENET_HWA_MAC_SetVLANTagFilterFilterEnFlag(pEnetHandle->EnetBase, pVlanFilterConfig->VlanFilterEnable);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Set vlan hash table
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bAddOrRemove      true add to hash table,false remove from hash table
 * @param[in] u16VlanTag        VLAN tag ID
 */
void Enet_SetVlanHashTable(ENET_HandleType *pEnetHandle, bool bAddOrRemove, uint16_t u16VlanTag)
{
    uint32_t u32CrcVal, u32HashBit;
    uint8_t *pTag = (uint8_t *)&u16VlanTag;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_VLANHASH_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_SET_VLANHASH_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            if (ENET_HWA_MAC_Get12BitVLANTagEnFlag(pEnetHandle->EnetBase))
            {
                u32CrcVal = Enet_ComputeCRC(pTag, 12u);
            }
            else
            {
                u32CrcVal = Enet_ComputeCRC(pTag, 16u);
            }

            u32CrcVal = Enet_BitsReverse(u32CrcVal);
            u32HashBit = (u32CrcVal >> ENET_VLAN_HASH_TABLE_BIT_SHIFT) & ENET_VLAN_HASH_TABLE_BIT_MASK;
            if (bAddOrRemove)
            {
                pEnetHandle->EnetBase->MAC_VLAN_HASH_TABLE |= 1u << u32HashBit;
            }
            else
            {
                pEnetHandle->EnetBase->MAC_VLAN_HASH_TABLE &= ~(1u << u32HashBit);
            }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       Poll wait VLAN perfect filter indirect registers operation complete
 * @param[in] pEnetBase         ENET base address
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Access to VLAN perfect filter indirect register is complete
 * @retval other values         Access to VLAN perfect filter indirect register is failed
 */
static ENET_StatusType Enet_VlanCtrlBusyPollWait(const ENET_Type *pEnetBase)
{
    uint32_t u32TimeOut = 1000u;

    while (ENET_MAC_STATUS_BUSY == ENET_HWA_MAC_GetVLANOperationStatus(pEnetBase))
    {
        if (--u32TimeOut == 0u)
        {
            break;
        }
    }

    return u32TimeOut > 0u ? ENET_STATUS_SUCCESS : ENET_STATUS_TIMEOUT;
}

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
                                          ENET_VlanPerfectFilterType *pPerfectFilter)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint32_t u32VlanTagData, u32Erivt, u32Ersvlm, u32Dovltc, u32Temp;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_GET_VLAN_PERFECTFILTER_SERVICE_ID))
    {
        if (pPerfectFilter == NULL_PTR)
        {
            ENET_ReportDevError(ENET_GET_VLAN_PERFECTFILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if ((uint32_t)pFilterGroup >= (uint32_t)ENET_VLAN_FILTER_COUNT)
            {
                ENET_ReportDevError(ENET_GET_VLAN_PERFECTFILTER_SERVICE_ID, ENET_E_PARAM_GROUP);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    eStatus = ENET_STATUS_NOT_READY;
                    ENET_ReportDevError(ENET_GET_VLAN_PERFECTFILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    ENET_HWA_MAC_SetVLANTagFilterRegOffset(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                    ENET_HWA_MAC_SetVLANCommandType(pEnetHandle->EnetBase, ENET_MAC_VLAN_COMMAND_READ);
                    ENET_HWA_MAC_SetVLANOperationBusy(pEnetHandle->EnetBase);
                    eStatus = Enet_VlanCtrlBusyPollWait(pEnetHandle->EnetBase);

                    if (ENET_STATUS_SUCCESS == eStatus)
                    {
                        u32VlanTagData = ENET_HWA_MAC_GetVLANTagData(pEnetHandle->EnetBase);

                        pPerfectFilter->FilterGroupEnable = 0u != (u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_VEN_MASK);
                        u32Temp = u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_ETV_MASK;
                        pPerfectFilter->CompareMode = (ENET_MAC_VLANCompareType)u32Temp;
                        pPerfectFilter->DMAChannelEnable = 0u != (u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_DMACHEN_MASK);
                        u32Temp = (u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_DMACHN_MASK) >> ENET_MAC_VLAN_TAG_DATA_DMACHN_SHIFT;
                        pPerfectFilter->DMAChannel = (ENET_ChannelType)u32Temp;
                        pPerfectFilter->VlanTag = (uint16_t)((u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_VID_MASK) >>
                                                             ENET_MAC_VLAN_TAG_DATA_VID_SHIFT);
                        u32Erivt = u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_ERIVLT_MASK;
                        u32Ersvlm = u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_ERSVLM_MASK;
                        u32Dovltc = u32VlanTagData & ENET_MAC_VLAN_TAG_DATA_DOVLTC_MASK;

                        if (u32Dovltc != 0u)
                        {
                            pPerfectFilter->FilterMode = (u32Erivt != 0u) ? ENET_VLAN_FILTER_INNER_ANYTYPE : ENET_VLAN_FILTER_OUTER_ANYTYPE;
                        }
                        else
                        {
                            if (u32Erivt != 0u)
                            {
                                pPerfectFilter->FilterMode = (u32Ersvlm != 0u) ? ENET_VLAN_FILTER_INNER_SVLAN : ENET_VLAN_FILTER_INNER_CVLAN;
                            }
                            else
                            {
                                pPerfectFilter->FilterMode = (u32Ersvlm != 0u) ? ENET_VLAN_FILTER_OUTER_SVLAN : ENET_VLAN_FILTER_OUTER_CVLAN;
                            }
                        }
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
    return eStatus;
}

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
                                          const ENET_VlanPerfectFilterType *pPerfectFilter)
{
    uint32_t u32VlanTagData, u32Erivt, u32Ersvlm, u32Dovltc;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_VLAN_PERFECTFILTER_SERVICE_ID))
    {
        if (pPerfectFilter == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_VLAN_PERFECTFILTER_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if ((uint32_t)pFilterGroup >= (uint32_t)ENET_VLAN_FILTER_COUNT)
            {
                ENET_ReportDevError(ENET_SET_VLAN_PERFECTFILTER_SERVICE_ID, ENET_E_PARAM_GROUP);
            }
            else
            {
                if (0u != Enet_AssertVlanPerfectFilterConfiguration(pPerfectFilter))
                {
                    ENET_ReportDevError(ENET_SET_VLAN_PERFECTFILTER_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                }
                else
                {
                    if (pEnetHandle->State == ENET_STATE_UNINIT)
                    {
                        eStatus = ENET_STATUS_NOT_READY;
                        ENET_ReportDevError(ENET_SET_VLAN_PERFECTFILTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                    }
                    else
                    {
#endif

                        u32Erivt = ((pPerfectFilter->FilterMode == ENET_VLAN_FILTER_INNER_CVLAN)    ||
                                    (pPerfectFilter->FilterMode == ENET_VLAN_FILTER_INNER_SVLAN)    ||
                                    (pPerfectFilter->FilterMode == ENET_VLAN_FILTER_INNER_ANYTYPE)) ? 1u : 0u;
                        u32Ersvlm = ((pPerfectFilter->FilterMode == ENET_VLAN_FILTER_OUTER_SVLAN)   ||
                                     (pPerfectFilter->FilterMode == ENET_VLAN_FILTER_INNER_SVLAN)) ? 1u : 0u;
                        u32Dovltc = ((pPerfectFilter->FilterMode == ENET_VLAN_FILTER_OUTER_ANYTYPE) ||
                                     (pPerfectFilter->FilterMode == ENET_VLAN_FILTER_INNER_ANYTYPE)) ? 1u : 0u;

                        u32VlanTagData = ENET_MAC_VLAN_TAG_DATA_DMACHN(pPerfectFilter->DMAChannel)                  |
                                         ENET_MAC_VLAN_TAG_DATA_DMACHEN(pPerfectFilter->DMAChannelEnable ? 1u : 0u) |
                                         ENET_MAC_VLAN_TAG_DATA_ERIVLT(u32Erivt)                                    |
                                         ENET_MAC_VLAN_TAG_DATA_ERSVLM(u32Ersvlm)                                   |
                                         ENET_MAC_VLAN_TAG_DATA_DOVLTC(u32Dovltc)                                   |
                                         ENET_MAC_VLAN_TAG_DATA_ETV(pPerfectFilter->CompareMode)                    |
                                         ENET_MAC_VLAN_TAG_DATA_VEN(pPerfectFilter->FilterGroupEnable ? 1u : 0u)    |
                                         ENET_MAC_VLAN_TAG_DATA_VID(pPerfectFilter->VlanTag);

                        ENET_HWA_MAC_SetVLANTagData(pEnetHandle->EnetBase, u32VlanTagData);
                        ENET_HWA_MAC_SetVLANTagFilterRegOffset(pEnetHandle->EnetBase, (uint8_t)pFilterGroup);
                        ENET_HWA_MAC_SetVLANCommandType(pEnetHandle->EnetBase, ENET_MAC_VLAN_COMMAND_WRITE);
                        ENET_HWA_MAC_SetVLANOperationBusy(pEnetHandle->EnetBase);
                        eStatus = Enet_VlanCtrlBusyPollWait(pEnetHandle->EnetBase);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Poll the busy bit in VLAN inclusion or replacement register
 * @param[in] pEnetBase         ENET base address
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  : Access to VLAN inclusion or replacement register is complete
 * @retval other values         : Access to VLAN inclusion or replacement register is failed
 */
static ENET_StatusType Enet_VlanInclBusyPollWait(const ENET_Type *pEnetBase)
{
    uint32_t u32TimeOut = 1000u;

    while (ENET_MAC_STATUS_BUSY == ENET_HWA_MAC_GetVLANInclusionOperationStatus(pEnetBase))
    {
        if (--u32TimeOut == 0u)
        {
            break;
        }
    }

    return u32TimeOut > 0u ? ENET_STATUS_SUCCESS : ENET_STATUS_TIMEOUT;
}

/**
 * @brief                       Write the indirect registers for channel based VLAN insertion
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          ENET DMA channel
 * @param[in] eVlanType         VLAN type: C-VLAN or S-VLAN
 * @param[in] u16VlanTag        VLAN tag value
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Write the indirect registers successfully
 * @retval other values         Write the indirect registers failed
 */
static ENET_StatusType Enet_VlanInclWrite(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel,
                                          ENET_MAC_VLANType eVlanType, uint16_t u16VlanTag)
{
    ENET_StatusType eStatus;

    /* Check busy state */
    eStatus = Enet_VlanInclBusyPollWait(pEnetHandle->EnetBase);
    if (ENET_STATUS_SUCCESS == eStatus)
    {
        ENET_HWA_MAC_SetVLANInclusionCommandType(pEnetHandle->EnetBase, ENET_MAC_VLAN_INCL_COMMAND_WRITE);
        ENET_HWA_MAC_SetVLANInclusionAddr(pEnetHandle->EnetBase, (uint8_t)eChannel);
        ENET_HWA_MAC_SetVLANType(pEnetHandle->EnetBase, eVlanType);
        ENET_HWA_MAC_SetTxVLANTag(pEnetHandle->EnetBase, u16VlanTag);
        /* Check busy state */
        eStatus = Enet_VlanInclBusyPollWait(pEnetHandle->EnetBase);
    }

    return eStatus;
}

/**
 * @brief                       Set outer VLAN insertion replacement or deletion
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanConfig       Outer VLAN operation parameters
 */
void Enet_SetTxOuterVlanConfig(ENET_HandleType *pEnetHandle, const ENET_TxVlanConfigType *pVlanConfig)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_TXOUTERVLAN_SERVICE_ID))
    {
        if (pVlanConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_TXOUTERVLAN_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (((uint32_t)pVlanConfig->VlanCtrl > (uint32_t)ENET_MAC_VLAN_TAG_REPLACEMENT) ||
                ((pVlanConfig->VlanType != ENET_MAC_VLAN_TYPE_C_VLAN) && (pVlanConfig->VlanType != ENET_MAC_VLAN_TYPE_S_VLAN)))
            {
                ENET_ReportDevError(ENET_SET_TXOUTERVLAN_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_SET_TXOUTERVLAN_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    if (pVlanConfig->VlanType == ENET_MAC_VLAN_TYPE_S_VLAN)
                    {
                        ENET_HWA_MAC_SetSVLANEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    }
                    ENET_HWA_MAC_SetChannelBasedVLANTagInsertEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                    ENET_HWA_MAC_SetVLANTagInputEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                    ENET_HWA_MAC_SetVLANType(pEnetHandle->EnetBase, pVlanConfig->VlanType);
                    ENET_HWA_MAC_SetVLANPriorityCtrlEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    ENET_HWA_MAC_SetTxVLANTag(pEnetHandle->EnetBase, pVlanConfig->VlanTag);
                    ENET_HWA_MAC_SetVLANTagCtrlOperation(pEnetHandle->EnetBase, pVlanConfig->VlanCtrl);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Set outer VLAN channel based insertion
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanConfig       Outer VLAN channel based configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  successful
 * @retval other values         failed
 */
ENET_StatusType Enet_SetTxOuterVlanChannelBasedInsertion(ENET_HandleType *pEnetHandle,
                                            const ENET_OuterVlanCBTIType *pVlanConfig)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint8_t u8Channel;
    bool sVlanEnabled = ENET_FALSE;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_TXOUTVLAN_CBI_SERVICE_ID))
    {
        if (pVlanConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_TXOUTVLAN_CBI_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_SET_TXOUTVLAN_CBI_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
                if (0u != Enet_AssertVlanChannelBasedInsConfiguration(pEnetHandle, pVlanConfig))
                {
                    ENET_ReportDevError(ENET_SET_TXOUTVLAN_CBI_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                }
                else
                {
#endif

                    ENET_HWA_MAC_SetChannelBasedVLANTagInsertEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    for (u8Channel = 0u; u8Channel < pEnetHandle->TxChannelCount; ++u8Channel)
                    {
                        eStatus = Enet_VlanInclWrite(pEnetHandle, (ENET_ChannelType)u8Channel, pVlanConfig->VlanType[u8Channel],
                                                     pVlanConfig->VlanTag[u8Channel]);
                        if (ENET_STATUS_SUCCESS != eStatus)
                        {
                            break;
                        }
                        if ((!sVlanEnabled) && (pVlanConfig->VlanType[u8Channel] == ENET_MAC_VLAN_TYPE_S_VLAN))
                        {
                            sVlanEnabled = ENET_TRUE;
                            ENET_HWA_MAC_SetSVLANEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                        }
                    }
                    if (ENET_STATUS_SUCCESS != eStatus)
                    {
                        ENET_HWA_MAC_SetChannelBasedVLANTagInsertEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Set inner VLAN insertion replacement or deletion
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pVlanConfig       Inner VLAN operation parameters
 */
void Enet_SetTxInnerVlanConfig(ENET_HandleType *pEnetHandle, const ENET_TxVlanConfigType *pVlanConfig)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_TXINNERVLAN_SERVICE_ID))
    {
        if (pVlanConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_TXINNERVLAN_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (((uint32_t)pVlanConfig->VlanCtrl > (uint32_t)ENET_MAC_VLAN_TAG_REPLACEMENT) ||
                ((pVlanConfig->VlanType != ENET_MAC_VLAN_TYPE_C_VLAN) && (pVlanConfig->VlanType != ENET_MAC_VLAN_TYPE_S_VLAN)))
            {
                ENET_ReportDevError(ENET_SET_TXINNERVLAN_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    ENET_ReportDevError(ENET_SET_TXINNERVLAN_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    if (pVlanConfig->VlanType == ENET_MAC_VLAN_TYPE_S_VLAN)
                    {
                        ENET_HWA_MAC_SetSVLANEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    }
                    ENET_HWA_MAC_SetDoubleVLANProcessEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    ENET_HWA_MAC_SetInnerVLANTagInputEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                    ENET_HWA_MAC_SetInnerVLANType(pEnetHandle->EnetBase, pVlanConfig->VlanType);
                    ENET_HWA_MAC_SetInnerVLANPriorityCtrlEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                    ENET_HWA_MAC_SetTxInnerVLANTag(pEnetHandle->EnetBase, pVlanConfig->VlanTag);
                    ENET_HWA_MAC_SetInnerVLANTagCtrl(pEnetHandle->EnetBase, pVlanConfig->VlanCtrl);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Register ENET system event callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterSystemEventCallback(ENET_HandleType *pEnetHandle, ENET_EventCallbackType eCallback)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_REGISTER_SYSEVENT_SERVICE_ID))
    {
#endif

        pEnetHandle->EventCallback = eCallback;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Register receive frame callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterRxCompleteCallback(ENET_HandleType *pEnetHandle, ENET_ChannelCallbackType eCallback)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_REGISTER_RXCOMP_SERVICE_ID))
    {
#endif

    pEnetHandle->RxReady = eCallback;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Register send frame complete callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterTxCompleteCallback(ENET_HandleType *pEnetHandle, ENET_ChannelCallbackType eCallback)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_REGISTER_TXCOMP_SERVICE_ID))
    {
#endif

    pEnetHandle->TxComplete = eCallback;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Register wait send frame complete callback function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCallback         Callback function
 */
void Enet_RegisterWaitTxCompleteCallback(ENET_HandleType *pEnetHandle, ENET_ChannelCallbackType eCallback)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_REGISTER_TXWAIT_SERVICE_ID))
    {
#endif

    pEnetHandle->TxCompleteWait = eCallback;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Get PTP default configuration
 * @param[out] pPTPConfig       PTP default configurations
 */
void Enet_PTPDefaultConfig(Enet_PTPConfigType *pPTPConfig)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (pPTPConfig == NULL_PTR)
    {
        ENET_ReportDevError(ENET_PTP_DEFCONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
    }
    else
    {
#endif

        pPTPConfig->IncrementStep = 20u;
        pPTPConfig->OneStepMode = ENET_FALSE;
        pPTPConfig->Av8021ASMode = ENET_FALSE;
        pPTPConfig->TXTSSTSM = ENET_MAC_TX_TIMESTAMP_STATUS_MODE_PRESERVE;
        pPTPConfig->MacFilterForPtp = ENET_FALSE;
        pPTPConfig->SnapshotType = ENET_MAC_PTP_SNAPSHOT_FOR_E2E_EVENT;
        pPTPConfig->PtpLayer = ENET_MAC_PTP_OVER_IPV4;
        pPTPConfig->PtpVersion = ENET_MAC_PTP_IEEE_1588_V2;
        pPTPConfig->RolloverMode = ENET_MAC_TIMESTAMP_ROLLOVER_BINARY;
        pPTPConfig->TimeStampForAll = ENET_FALSE;
        pPTPConfig->PresentationTimeGen = ENET_FALSE;
        pPTPConfig->UpdateMethod = ENET_MAC_TIMESTAMP_UPDATE_FINE;
        pPTPConfig->ClkSource = ENET_MAC_PTP_CLK_SEL_PCC;
#if ENET_SUPPORT_REFCLK_PIN
        pPTPConfig->RefClkPinInputFreq = 0U;
#endif
        pPTPConfig->InitTime.Nanoseconds = 0u;
        pPTPConfig->InitTime.Seconds = 0u;
        pPTPConfig->InitTime.SecondsHi = 0u;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    }
#endif
}

/**
 * @brief                       Select the PTP source clock
 * @param[in] pEnet             ENET instance base
 * @param[in] pPTPConfig        PTP configurations
 * @return                      PTP source clock frequency
 */
static inline uint32_t Enet_PTPClockSourceConfig(ENET_Type *const pEnet,  const Enet_PTPConfigType *pPTPConfig)
{
    ENET_MAC_MiiModeType eMiiMode;
    ENET_MAC_SpeedType eSpeed;
    uint32_t u32Frequency;

    switch (pPTPConfig->ClkSource)
    {
        case ENET_MAC_PTP_CLK_SEL_PCC:
            ENET_HWA_Sysctrl_SetPTPClkSrc(ENET_MAC_PTP_CLK_SEL_PCC);
            u32Frequency = PCC_GetPccFunctionClock(PCC_CLK_ENET);
            break;
        case ENET_MAC_PTP_CLK_SEL_TX_CLK:
            ENET_HWA_Sysctrl_SetPTPClkSrc(ENET_MAC_PTP_CLK_SEL_TX_CLK);
            eMiiMode = ENET_HWA_MAC_GetPhyMiiMode(pEnet);
            if (eMiiMode == ENET_MAC_PHY_RGMII)
            {
                eSpeed = ENET_HWA_MAC_GetSpeed(pEnet);
                if (eSpeed == ENET_MAC_SPEED_1000MBPS)
                {
                   u32Frequency = 125000000u;
                }
                else if (eSpeed == ENET_MAC_SPEED_100MBPS)
                {
                   u32Frequency = 25000000u;
                }
                else
                {
                    u32Frequency = 2500000u;
                }
            }
            if (eMiiMode == ENET_MAC_PHY_RMII)
            {
                u32Frequency = 50000000u;
            }
            else
            {
                u32Frequency = 25000000u;
            }
            break;
#if ENET_SUPPORT_REFCLK_PIN
        case ENET_MAC_PTP_CLK_SEL_REFCLK_PIN:
            ENET_HWA_Sysctrl_SetPTPClkSrc(ENET_MAC_PTP_CLK_SEL_REFCLK_PIN);
            u32Frequency = pPTPConfig->RefClkPinInputFreq;
            break;
#endif
        default:
            u32Frequency = 0u;
            break;
    }

    return u32Frequency;
}

/**
 * @brief                       Check the PTP clock and increment step valid
 * @param[in] pPTPConfig        PTP default configurations
 * @param[in] u32ClkFreq        PTP clock frequency
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  The PTP clock and increment step are valid
 * @retval ENET_STATUS_ERROR    One of the PTP clock and increment step is invalid
 */
static ENET_StatusType Enet_CheckPTPClockStepValid(const Enet_PTPConfigType *pPTPConfig, uint32_t u32ClkFreq)
{
    ENET_StatusType eStatus = ENET_STATUS_SUCCESS;
    uint32_t u32Tmp;
    int s32Sub;

    if (u32ClkFreq == 0u)
    {
        eStatus = ENET_STATUS_INVALID_PARAM;
    }
    else
    {
        u32Tmp = u32ClkFreq * (uint32_t)pPTPConfig->IncrementStep;

        if (pPTPConfig->UpdateMethod == ENET_MAC_TIMESTAMP_UPDATE_COARSE)
        {
            /* In coarse method the system clock increment is directly triggered by u32ClkFreq,
             * the u32ClkFreq * IncrementStep must be close to 1000000000
             */
            s32Sub = (int32_t)(u32Tmp - 1000000000u);
            if (s32Sub > 512 || s32Sub < -512)
            {
                eStatus = ENET_STATUS_ERROR;
            }
        }
        else
        {
            /* In fine method the system clock increment is triggered by clock divided from u32ClkFreq,
             * the u32ClkFreq * IncrementStep must be greater than 1000000000
             */
            if (u32Tmp < 1000000000u)
            {
                eStatus = ENET_STATUS_ERROR;
            }
        }
    }

    return eStatus;
}

/**
 * @brief                       Convert PTP register value to nanoseconds value
 * @param[in] u32Subseconds     PTP subseconds register value
 * @return                      PTP nanoseconds value
 */
static inline uint32_t Enet_PTPRegValue2Nanoseconds(uint32_t u32Subseconds)
{
    uint64_t u64Value = (uint64_t)u32Subseconds * (uint64_t)1000000000u;
    return (uint32_t)(u64Value >> 31u);
}

/**
 * @brief                       Convert nanoseconds value to PTP register value
 * @param[in] u32Nanoseconds    PTP nanoseconds value
 * @return                      PTP subseconds register value
 */
static inline uint32_t Enet_PTPNanoseconds2RegValue(uint32_t u32Nanoseconds)
{
    uint64_t u64Value = (uint64_t)u32Nanoseconds * (uint64_t)0x80000000u;
    return (uint32_t)(u64Value / (uint64_t)1000000000u);
}

/**
 * @brief                       Set PTP counter increment value
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pPTPConfig        PTP configurations
 * @param[in] PtpClkFreq        PTP reference clock source frequency
 * @note                        Attempt to set base Addend value close to 0x80000000u
 *                              Binary rollover mode :
 *                              IncrementValue * AddendValue = 2^31 * 2^32 / PtpClkFreq
 *                              IncrementValue = 2^31 * 2 / PtpClkFreq
 *
 *                              Digital rollover mode :
 *                              IncrementValue * AddendValue = 10^9 * 2^32 / PtpClkFreq
 *                              IncrementValue = 10^9 * 2 / PtpClkFreq
 */
static void Enet_PTPSetIncrementValue(ENET_HandleType *pEnetHandle, const Enet_PTPConfigType *pPTPConfig, uint32_t PtpClkFreq)
{
    uint32_t u32IncValue;
    uint32_t u32Ssinc;
    uint64_t u64Temp;

    /* The fractional part of SUB_SECOND_INCREMENT register is ignored,which is compensated in AddendValue */
    if (pPTPConfig->RolloverMode == ENET_MAC_TIMESTAMP_ROLLOVER_BINARY)
    {
        u64Temp = (uint64_t)0x80000000u * (uint64_t)pPTPConfig->IncrementStep + (uint64_t)500000000u;
        u32Ssinc = (uint32_t)(u64Temp / (uint64_t)1000000000u);
        pEnetHandle->PtpAddend = (uint32_t)(((uint64_t)0x80000000u * (uint64_t)0x100000000ull) / ((uint64_t)PtpClkFreq * (uint64_t)u32Ssinc));
    }
    else
    {
        u32Ssinc = (uint32_t)pPTPConfig->IncrementStep;

        pEnetHandle->PtpAddend = (uint32_t)(((uint64_t)1000000000u * (uint64_t)0x100000000ull) / ((uint64_t)PtpClkFreq * (uint64_t)u32Ssinc));
    }
    u32IncValue = ENET_MAC_SUB_SECOND_INCREMENT_SSINC(u32Ssinc) | ENET_MAC_SUB_SECOND_INCREMENT_SNSINC(0u);
    ENET_HWA_MAC_SetSubSecondIncrementReg(pEnetHandle->EnetBase, u32IncValue);
}

/**
 * @brief                       Poll wait PTP control register u32PollMask bit cleared
 * @param[in] pEnetBase         ENET base address
 * @param[in] u32PollMask       PTP control register mask bit
 * @param[in] u32Timeout        Timeout counter
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  PTP control poll mask completed
 * @retval ENET_STATUS_TIMEOUT  PTP control poll mask timeout
 */
static ENET_StatusType Enet_PTPCtrlPollWait(const ENET_Type *pEnetBase, uint32_t u32PollMask, uint32_t u32Timeout)
{

    while (0u != (ENET_HWA_MAC_GetTimestampControl(pEnetBase) & u32PollMask))
    {
        if (--u32Timeout == 0u)
        {
            break;
        }
    }
    return u32Timeout > 0u ? ENET_STATUS_SUCCESS : ENET_STATUS_TIMEOUT;
}

/**
 * @brief                       Initialize the PTP system time
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eRolloverMode     PTP subseconds register rollover mode
 * @param[in] pTime             The time to initialize
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Initialize PTP system time successfully
 * @retval other values         Initialize PTP system time failed
 */
static inline ENET_StatusType Enet_PTPInitializeSystemTime(ENET_HandleType *pEnetHandle,
              ENET_MAC_TimestampRolloverType eRolloverMode, const ENET_TimestampType *pTime)
{
    uint32_t u32NsValue;

    ENET_HWA_MAC_SetSystemTimeHigherWordSeconds(pEnetHandle->EnetBase, pTime->SecondsHi);
    ENET_HWA_MAC_SetSystemTimeSecondsUpdateValue(pEnetHandle->EnetBase, pTime->Seconds);
    u32NsValue = pTime->Nanoseconds;
    if (eRolloverMode == ENET_MAC_TIMESTAMP_ROLLOVER_BINARY)
    {
        u32NsValue = Enet_PTPNanoseconds2RegValue(u32NsValue);
    }
    ENET_HWA_MAC_SetSystemTimeNanoSecondsUpdateValue(pEnetHandle->EnetBase, u32NsValue);
    ENET_HWA_MAC_SetTimeUpdateOperation(pEnetHandle->EnetBase, ENET_MAC_SYSTEM_TIME_ADD_TIME);
    ENET_HWA_MAC_InitTimestamp(pEnetHandle->EnetBase);
    return Enet_PTPCtrlPollWait(pEnetHandle->EnetBase, ENET_MAC_TIMESTAMP_CONTROL_TSINIT_MASK, ENET_PTP_TIMEOUT_VALUE);
}

/**
 * @brief                       Set PTP ingress synchronization correction value
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eRolloverMode     PTP subseconds register rollover mode
 * @param[in] PtpClkFreq        PTP clock source frequency
 * @note                        MAC_Ingress_Timestamp_Latency  + 2 times the clock-period of the PTP clock,
 *                              and the subnanoseconds is ignored
 */
static void Enet_PTPSetIngressSyncCorrection(ENET_HandleType *pEnetHandle,
            ENET_MAC_TimestampRolloverType eRolloverMode, uint32_t PtpClkFreq)
{
    uint32_t u32LatencyNs, u32ClkLatency, u32Correction, u32Regvalue;

    u32LatencyNs = ENET_HWA_MAC_GetTimestampIngressLatencyInNanoseconds(pEnetHandle->EnetBase);

    /* 2 times the PTP clock-period */
    u32ClkLatency = (uint32_t)((uint32_t)2u * (uint32_t)1000000000u / PtpClkFreq);

    u32Correction = u32LatencyNs + u32ClkLatency;

    if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == eRolloverMode)
    {
        u32Correction = Enet_PTPNanoseconds2RegValue(u32Correction);
        u32Regvalue = (~u32Correction) + (uint32_t)1u;
    }
    else
    {
        u32Regvalue = (uint32_t)((uint32_t)1000000000u - u32Correction) | (uint32_t)0x80000000u;
    }
    ENET_HWA_MAC_SetTimestampIngressCorrectionInNanoseconds(pEnetHandle->EnetBase, (int32_t)u32Regvalue);
    ENET_HWA_MAC_SetTimestampIngressCorrectionInSubNanoseconds(pEnetHandle->EnetBase, (int8_t)0);
}

/**
 * @brief                       Set PTP egress synchronization correction value
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eRolloverMode     PTP subseconds register rollover mode
 * @param[in] PtpClkFreq        PTP clock source frequency
 * @param[in] bOneStep          PTP one step mode enabled
 * @note                        MAC_Egress_Timestamp_Latency  + 2 times the clock-period of the PTP clock,
 *                              and the subnanoseconds is ignored
 */
static void Enet_PTPSetEgressSyncCorrection(ENET_HandleType *pEnetHandle,
            ENET_MAC_TimestampRolloverType eRolloverMode, uint32_t PtpClkFreq, bool bOneStep)
{
    uint32_t u32LatencyNs, u32ClkLatency, u32Correction, u32Regvalue;

    u32LatencyNs = ENET_HWA_MAC_GetTimestampEgressLatencyInNanoseconds(pEnetHandle->EnetBase);

    if (bOneStep)
    {
        /* One step mode is not currently supported  */
        u32ClkLatency = 0u;
    }
    else
    {
        u32ClkLatency = (uint32_t)((uint32_t)2u * (uint32_t)1000000000u / PtpClkFreq);
    }

    u32Correction = u32LatencyNs + u32ClkLatency;

    if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == eRolloverMode)
    {
        u32Correction = Enet_PTPNanoseconds2RegValue(u32Correction);
        u32Regvalue = (~u32Correction) + (uint32_t)1u;
    }
    else
    {
        u32Regvalue = (uint32_t)((uint32_t)1000000000u - u32Correction) | (uint32_t)0x80000000u;
    }
    ENET_HWA_MAC_SetTimestampEgressCorrectionInNanoseconds(pEnetHandle->EnetBase, (int32_t)u32Regvalue);
    ENET_HWA_MAC_SetTimestampEgressCorrectionInSubNanoseconds(pEnetHandle->EnetBase, (int8_t)0);
}

/**
 * @brief                       Start PTP counter process
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pPTPConfig        PTP initialize configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Start PTP successfully
 * @retval other values         Start PTP failed
 */
ENET_StatusType Enet_PTPStart(ENET_HandleType *pEnetHandle, const Enet_PTPConfigType *pPTPConfig)
{
    uint32_t u32RegValue;
    uint32_t PtpClkFreq;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_START_SERVICE_ID))
    {
        if (pPTPConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_PTP_START_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_PTP_START_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
                if (0u != Enet_AssertPTPConfiguration(pPTPConfig))
                {
                    ENET_ReportDevError(ENET_PTP_START_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                }
                else
                {
                    if (pEnetHandle->PTPState != ENET_STATE_UNINIT)
                    {
                        eStatus = ENET_STATUS_ERROR;
                        ENET_ReportDevError(ENET_PTP_START_SERVICE_ID, ENET_E_DRIVER_REPEAT_INIT);
                    }
                    else
                    {
#endif

                        /* Disable timestamp interrupt */
                        ENET_HWA_MAC_SetTimestampInterruptEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                        ENET_HWA_MAC_SetTimestampControl(pEnetHandle->EnetBase, 0x00002000u);

                        /* Set ptp reference clock and get clock frequency */
                        PtpClkFreq = Enet_PTPClockSourceConfig(pEnetHandle->EnetBase, pPTPConfig);

                        if (ENET_STATUS_SUCCESS == Enet_CheckPTPClockStepValid(pPTPConfig, PtpClkFreq))
                        {
                            /* Enable timestamping */
                            ENET_HWA_MAC_SetTimestampEnFlag(pEnetHandle->EnetBase, true);

                            /* Timestamping config */
                            ENET_HWA_MAC_SetAV802_1ASModeEnFlag(pEnetHandle->EnetBase, pPTPConfig->Av8021ASMode);
                            ENET_HWA_MAC_SetTxTimestampStatusMode(pEnetHandle->EnetBase, pPTPConfig->TXTSSTSM);
                            ENET_HWA_MAC_SetUseMACAddrForPTPPacketFilterEnFlag(pEnetHandle->EnetBase,
                                                                               pPTPConfig->MacFilterForPtp);
                            u32RegValue = ENET_HWA_MAC_GetTimestampControl(pEnetHandle->EnetBase);
                            u32RegValue &= ~(ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL_MASK |
                                             ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA_MASK  |
                                             ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA_MASK  |
                                             ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA_MASK  |
                                             ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA_MASK  |
                                             ENET_MAC_TIMESTAMP_CONTROL_TSIPENA_MASK);
                            u32RegValue |= (uint32_t)pPTPConfig->SnapshotType | (uint32_t)pPTPConfig->PtpLayer;
                            ENET_HWA_MAC_SetTimestampControl(pEnetHandle->EnetBase, u32RegValue);
                            ENET_HWA_MAC_SetPTPPacketVersion(pEnetHandle->EnetBase, pPTPConfig->PtpVersion);
                            ENET_HWA_MAC_SetIimestampRolloverCtrl(pEnetHandle->EnetBase, pPTPConfig->RolloverMode);
                            ENET_HWA_MAC_SetTimestampForAllPacketEnFlag(pEnetHandle->EnetBase, pPTPConfig->TimeStampForAll);
                            ENET_HWA_MAC_SetPresentationTimeGenerationEnFlag(pEnetHandle->EnetBase,
                                                                             pPTPConfig->PresentationTimeGen);
                            ENET_HWA_MAC_SetTimestampUpdateMethod(pEnetHandle->EnetBase, pPTPConfig->UpdateMethod);

                            Enet_PTPSetIncrementValue(pEnetHandle, pPTPConfig, PtpClkFreq);

                            /* Initialize the Timestamp Addend register in fine update mode */
                            if (pPTPConfig->UpdateMethod == ENET_MAC_TIMESTAMP_UPDATE_FINE)
                            {
                                ENET_HWA_MAC_SetTimestampAddend(pEnetHandle->EnetBase, pEnetHandle->PtpAddend);
                                ENET_HWA_MAC_UpdateAddendRegister(pEnetHandle->EnetBase);
                                eStatus = Enet_PTPCtrlPollWait(pEnetHandle->EnetBase, ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK,
                                                               ENET_PTP_TIMEOUT_VALUE);
                            }

                            if (ENET_STATUS_SUCCESS == eStatus)
                            {
                                Enet_PTPSetIngressSyncCorrection(pEnetHandle, pPTPConfig->RolloverMode, PtpClkFreq);
                                Enet_PTPSetEgressSyncCorrection(pEnetHandle, pPTPConfig->RolloverMode,
                                                                PtpClkFreq, pPTPConfig->OneStepMode);

                                /* Setting the initial time */
                                eStatus = Enet_PTPInitializeSystemTime(pEnetHandle, pPTPConfig->RolloverMode, &pPTPConfig->InitTime);
                                if (ENET_STATUS_SUCCESS == eStatus)
                                {
                                    pEnetHandle->PpsInterval = 0u;
                                    pEnetHandle->PpsWidth = 0u;
                                    pEnetHandle->PTPState = ENET_STATE_READY;
                                    ENET_HWA_MAC_SetTimestampInterruptEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                                }
                            }

                            /* Disable timestamping function if an error occurs */
                            if (ENET_STATUS_SUCCESS != eStatus)
                            {
                                ENET_HWA_MAC_SetTimestampEnFlag(pEnetHandle->EnetBase, false);
                            }
                        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Stop PTP counter process
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_PTPStop(ENET_HandleType *pEnetHandle)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_STOP_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_PTP_STOP_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            ENET_HWA_MAC_SetTimestampInterruptEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
            ENET_HWA_MAC_SetTimestampEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
            pEnetHandle->PpsInterval = 0u;
            pEnetHandle->PpsWidth = 0u;
            pEnetHandle->PTPState = ENET_STATE_STOPPED;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       Get PTP current system time
 * @param[in] pEnetHandle       ENET driver handle
 * @param[out] pTime            PTP system time
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Get PTP system time successfully
 * @retval other values         Get PTP system time failed
 */
ENET_StatusType Enet_PTPGetTime(const ENET_HandleType *pEnetHandle, ENET_TimestampType *pTime)
{
    uint32_t u32Seconds, u32Nanoseconds;
    uint16_t u16SecondsHi;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_GETTIME_SERVICE_ID))
    {
        if (pTime == NULL_PTR)
        {
            ENET_ReportDevError(ENET_PTP_GETTIME_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_PTP_GETTIME_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                if (pEnetHandle->PTPState == ENET_STATE_READY)
                {
                    pTime->SecondsHi = ENET_HWA_MAC_GetSystemTimeHigherWordSeconds(pEnetHandle->EnetBase);
                    pTime->Seconds = ENET_HWA_MAC_GetSystemTimeSeconds(pEnetHandle->EnetBase);
                    u32Nanoseconds = ENET_HWA_MAC_GetSystemTimeNanoSeconds(pEnetHandle->EnetBase);
                    u32Seconds = ENET_HWA_MAC_GetSystemTimeSeconds(pEnetHandle->EnetBase);
                    u16SecondsHi = ENET_HWA_MAC_GetSystemTimeHigherWordSeconds(pEnetHandle->EnetBase);

                    if ((u32Seconds != pTime->Seconds) && (pTime->Nanoseconds < 500000000u))
                    {
                        pTime->Seconds = u32Seconds;
                    }
                    if ((u16SecondsHi != pTime->SecondsHi) && (pTime->Seconds < 100u))
                    {
                        pTime->SecondsHi = u16SecondsHi;
                    }
                    if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == ENET_HWA_MAC_GetTimestampRolloverCtrl(pEnetHandle->EnetBase))
                    {
                        u32Nanoseconds = Enet_PTPRegValue2Nanoseconds(u32Nanoseconds);
                    }

                    pTime->Nanoseconds = u32Nanoseconds;
                    eStatus = ENET_STATUS_SUCCESS;
                }
                else
                {
                    eStatus = ENET_STATUS_NOT_READY;
                }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Set PTP system time
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pTime             Time to set
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Set PTP time successfully
 * @retval other values         Set PTP time failed
 */
ENET_StatusType Enet_PTPSetTime(ENET_HandleType *pEnetHandle, const ENET_TimestampType *pTime)
{
    ENET_MAC_TimestampRolloverType eRolloverMode;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_SETTIME_SERVICE_ID))
    {
        if (pTime == NULL_PTR)
        {
            ENET_ReportDevError(ENET_PTP_SETTIME_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_PTP_SETTIME_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                if (pEnetHandle->PTPState == ENET_STATE_READY)
                {
                    eRolloverMode = ENET_HWA_MAC_GetTimestampRolloverCtrl(pEnetHandle->EnetBase);
                    eStatus = Enet_PTPInitializeSystemTime(pEnetHandle, eRolloverMode, pTime);
                }
                else
                {
                    eStatus = ENET_STATUS_NOT_READY;
                }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Update PTP system time offset
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pTime             Time offset
 * @param[in] bSubtraction      Subtract from PTP system time,or add to PTP system time
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Update PTP time successfully
 * @retval other values         Update PTP time failed
 */
ENET_StatusType Enet_PTPUpdateTime(ENET_HandleType *pEnetHandle, const ENET_TimestampType *pTime, bool bSubtraction)
{
    ENET_MAC_TimestampRolloverType eRolloverMode;
    uint32_t u32RegValue, u32Subns, u32Addend;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_UPDATETIME_SERVICE_ID))
    {
        if (pTime == NULL_PTR)
        {
            ENET_ReportDevError(ENET_PTP_UPDATETIME_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pTime->SecondsHi != 0u)
            {
                ENET_ReportDevError(ENET_PTP_UPDATETIME_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    eStatus = ENET_STATUS_NOT_READY;
                    ENET_ReportDevError(ENET_PTP_UPDATETIME_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
#endif

                    if (pEnetHandle->PTPState == ENET_STATE_READY)
                    {
                        u32Subns = pTime->Nanoseconds;
                        u32Addend = ENET_HWA_MAC_GetTimestampAddend(pEnetHandle->EnetBase);
                        eRolloverMode = ENET_HWA_MAC_GetTimestampRolloverCtrl(pEnetHandle->EnetBase);
                        if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == eRolloverMode)
                        {
                            u32Subns = Enet_PTPNanoseconds2RegValue(u32Subns);
                        }

                        if (bSubtraction)
                        {
                            ENET_HWA_MAC_SetTimeUpdateOperation(pEnetHandle->EnetBase, ENET_MAC_SYSTEM_TIME_SUBTRACT_TIME);
                            u32RegValue = pTime->Seconds != 0u ? (0xFFFFFFFFu - (pTime->Seconds - 1u)) : 0u;
                            ENET_HWA_MAC_SetSystemTimeSecondsUpdateValue(pEnetHandle->EnetBase, u32RegValue);

                            if (u32Subns != 0u)
                            {
                                u32RegValue = (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == eRolloverMode) ?
                                               (0x80000000u - u32Subns) : (1000000000u - u32Subns);
                            }
                            else
                            {
                                u32RegValue = 0u;
                            }
                            ENET_HWA_MAC_SetSystemTimeNanoSecondsUpdateValue(pEnetHandle->EnetBase, u32RegValue);
                        }
                        else
                        {
                            ENET_HWA_MAC_SetTimeUpdateOperation(pEnetHandle->EnetBase, ENET_MAC_SYSTEM_TIME_ADD_TIME);
                            ENET_HWA_MAC_SetSystemTimeSecondsUpdateValue(pEnetHandle->EnetBase, pTime->Seconds);
                            ENET_HWA_MAC_SetSystemTimeNanoSecondsUpdateValue(pEnetHandle->EnetBase, u32Subns);
                        }
                        ENET_HWA_MAC_UpdateTimestamp(pEnetHandle->EnetBase);
                        Enet_PTPCtrlPollWait(pEnetHandle->EnetBase, ENET_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK, ENET_PTP_TIMEOUT_VALUE);
                        if (ENET_STATUS_SUCCESS == eStatus)
                        {
                            ENET_HWA_MAC_SetTimestampAddend(pEnetHandle->EnetBase, u32Addend);
                            ENET_HWA_MAC_UpdateAddendRegister(pEnetHandle->EnetBase);
                            Enet_PTPCtrlPollWait(pEnetHandle->EnetBase, ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK, ENET_PTP_TIMEOUT_VALUE);
                        }
                    }
                    else
                    {
                        eStatus = ENET_STATUS_NOT_READY;
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
    return eStatus;
}

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
ENET_StatusType Enet_PTPAdjustFrequency(ENET_HandleType *pEnetHandle, int PPb)
{
    uint64_t u64Addend;
    int s32Temp;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_ADJUST_FREQ_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            eStatus = ENET_STATUS_NOT_READY;
            ENET_ReportDevError(ENET_PTP_ADJUST_FREQ_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else if ((PPb > 1024000) || (PPb < -1024000))
        {
            ENET_ReportDevError(ENET_PTP_ADJUST_FREQ_SERVICE_ID, ENET_E_PARAM_ASSERTION);
        }
        else
        {
#endif

            if (pEnetHandle->PTPState == ENET_STATE_READY)
            {
                if (ENET_MAC_TIMESTAMP_UPDATE_FINE == ENET_HWA_MAC_GetTimestampUpdateMethod(pEnetHandle->EnetBase))
                {
                    s32Temp = (int)1000000000 - PPb;
                    u64Addend = ((uint64_t)pEnetHandle->PtpAddend * (uint64_t)1000000000u) / (uint32_t)s32Temp;

                    ENET_HWA_MAC_SetTimestampAddend(pEnetHandle->EnetBase, (uint32_t)u64Addend);
                    ENET_HWA_MAC_UpdateAddendRegister(pEnetHandle->EnetBase);
                    Enet_PTPCtrlPollWait(pEnetHandle->EnetBase, ENET_MAC_TIMESTAMP_CONTROL_TSADDREG_MASK, ENET_PTP_TIMEOUT_VALUE);
                }
                else
                {
                    eStatus = ENET_STATUS_UNSUPPORTED;
                }
            }
            else
            {
                eStatus = ENET_STATUS_NOT_READY;
            }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
    return eStatus;
}

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
                                    ENET_MAC_PPSFreqCtrlType eFreqCtrl)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_FIXED_PPSOUT_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            eStatus = ENET_STATUS_NOT_READY;
            ENET_ReportDevError(ENET_PTP_FIXED_PPSOUT_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
            if ((uint32_t)ePPSChannel >= (uint32_t)ENET_PPS_CHANNEL_COUNT)
            {
                ENET_ReportDevError(ENET_PTP_FIXED_PPSOUT_SERVICE_ID, ENET_E_PARAM_PPSCHANNEL);
            }
            else
            {
                if ((uint32_t)eFreqCtrl > (uint32_t)ENET_MAC_PPS_CTRL_FREQ_32K768HZ)
                {
                    ENET_ReportDevError(ENET_PTP_FIXED_PPSOUT_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                }
                else
                {
#endif

                    if (pEnetHandle->PTPState == ENET_STATE_READY)
                    {
                        ENET_HWA_MAC_SetChannelFlexiblePPSOutputEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                        ENET_HWA_MAC_SetFixedPPSOutputFrequency(pEnetHandle->EnetBase, eFreqCtrl);
                        if (ENET_PTP_PPS_DIR_OUTPUT != ENET_HWA_Sysctrl_GetPPSPinDirection(ePPSChannel))
                        {
                            ENET_HWA_Sysctrl_SetPPSPinDirection(ePPSChannel, ENET_PTP_PPS_DIR_OUTPUT);
                        }
                        eStatus = ENET_STATUS_SUCCESS;
                    }
                    else
                    {
                        eStatus = ENET_STATUS_NOT_READY;
                    }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
    return eStatus;
}

/**
 * @brief                       Calculate flexible PPS out pulse interval and width
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eRolloverMode     Roll over mode
 * @param[out] pInterval        PTP flexible PPS out pulse interval
 * @param[out] pWidth           PTP flexible PPS out pulse width
 * @note
 *  Interval register value = (Interval nanoseconds value / MAC_Sub_Second_Increment) - 1
 *  Width register value = (Width nanoseconds value / MAC_Sub_Second_Increment) - 1
 */
static void Enet_CalculatePPSIntervalWidth(ENET_HandleType *pEnetHandle,
            ENET_MAC_TimestampRolloverType eRolloverMode, uint32_t *pInterval, uint32_t *pWidth)
{
    uint32_t u32IncValue, u32Interval, u32Width;

    u32IncValue = pEnetHandle->EnetBase->MAC_SUB_SECOND_INCREMENT;
    DEV_ASSERT(u32IncValue != 0u);
    u32IncValue = ((u32IncValue & ENET_MAC_SUB_SECOND_INCREMENT_SSINC_MASK) >> ENET_MAC_SUB_SECOND_INCREMENT_SSINC_SHIFT) * 256u +
                  ((u32IncValue & ENET_MAC_SUB_SECOND_INCREMENT_SNSINC_MASK) >> ENET_MAC_SUB_SECOND_INCREMENT_SNSINC_SHIFT);

    if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == eRolloverMode)
    {
        u32IncValue = Enet_PTPRegValue2Nanoseconds(u32IncValue);
    }

    if (pInterval != NULL_PTR)
    {
        u32Interval = pEnetHandle->PpsInterval / u32IncValue * 256u;
        *pInterval = u32Interval > 0u ? u32Interval - 1u : 0u;
    }
    if (pWidth != NULL_PTR)
    {
        u32Width = pEnetHandle->PpsWidth / u32IncValue * 256u;
        *pWidth = u32Width > 0u ? u32Width - 1u : 0u;
    }
}

/**
 * @brief                       Set PTP PPS channel target time
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] ePPSChannel       PTP PPS channel
 * @param[in] eRolloverMode     PTP subseconds register rollover mode
 * @param[in] pTime             PTP target time value , SecondsHi is ignored
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Set PTP target time successfully
 * @retval other values         Set PTP target time failed
 */
static ENET_StatusType Enet_PTPSetTargetTime(ENET_HandleType *pEnetHandle, ENET_MAC_PPSChannelType ePPSChannel,
                                ENET_MAC_TimestampRolloverType eRolloverMode, const ENET_TimestampType *pTime)
{
    uint32_t u32RegValue, u32Timeout = ENET_PTP_TIMEOUT_VALUE;
    ENET_StatusType eStatus = ENET_STATUS_SUCCESS;
    ENET_MAC_StatusType eBusy;

    do
    {
        if (--u32Timeout == 0u)
        {
            eStatus = ENET_STATUS_ERROR;
            break;
        }
        eBusy = ENET_HWA_MAC_GetPPSTargetTimeBusyStatus(pEnetHandle->EnetBase, ePPSChannel);
    } while (eBusy == ENET_MAC_STATUS_BUSY);

    if (ENET_STATUS_SUCCESS == eStatus)
    {
        if (ENET_MAC_TIMESTAMP_ROLLOVER_BINARY == eRolloverMode)
        {
            u32RegValue = Enet_PTPNanoseconds2RegValue(pTime->Nanoseconds);
        }
        else
        {
            u32RegValue = pTime->Nanoseconds;
        }

        ENET_HWA_MAC_SetPPSTargetTimeInSeconds(pEnetHandle->EnetBase, ePPSChannel, pTime->Seconds);
        ENET_HWA_MAC_SetPPSTargetTimeInNanoseconds(pEnetHandle->EnetBase, ePPSChannel, u32RegValue);
    }
    return eStatus;
}

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
                                       const ENET_FlexPPSConfigType *PPSConfig)
{
    uint32_t u32Interval, u32Width;
    ENET_MAC_TimestampRolloverType eRolloverMode;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PTP_FLEXIBLE_PPSOUT_SERVICE_ID))
    {
        if (PPSConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_PTP_FLEXIBLE_PPSOUT_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_PTP_FLEXIBLE_PPSOUT_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
                if ((uint32_t)ePPSChannel >= (uint32_t)ENET_PPS_CHANNEL_COUNT)
                {
                    ENET_ReportDevError(ENET_PTP_FLEXIBLE_PPSOUT_SERVICE_ID, ENET_E_PARAM_PPSCHANNEL);
                }
                else
                {
                    if ((uint32_t)PPSConfig->Cmd > (uint32_t)ENET_MAC_PPS_CANCEL_STOP_PULSE_TRAIN)
                    {
                        ENET_ReportDevError(ENET_PTP_FLEXIBLE_PPSOUT_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                    }
                    else
                    {
#endif

                        if (pEnetHandle->PTPState == ENET_STATE_READY)
                        {
                            eRolloverMode = ENET_HWA_MAC_GetTimestampRolloverCtrl(pEnetHandle->EnetBase);
                            switch (PPSConfig->Cmd)
                            {
                                case ENET_MAC_PPS_START_SINGLE_PULSE:
                                    eStatus = Enet_PTPSetTargetTime(pEnetHandle, ePPSChannel, eRolloverMode, &PPSConfig->TargetTime);
                                    if (ENET_STATUS_SUCCESS == eStatus)
                                    {
                                        if (pEnetHandle->PpsWidth != PPSConfig->PPSWidth)
                                        {
                                            pEnetHandle->PpsWidth = PPSConfig->PPSWidth;
                                            Enet_CalculatePPSIntervalWidth(pEnetHandle, eRolloverMode, NULL_PTR, &u32Width);
                                            ENET_HWA_MAC_SetPPSWidth(pEnetHandle->EnetBase, ePPSChannel, u32Width);
                                        }
                                    }
                                    break;
                                case ENET_MAC_PPS_START_PULSE_TRAIN:
                                    eStatus = Enet_PTPSetTargetTime(pEnetHandle, ePPSChannel, eRolloverMode, &PPSConfig->TargetTime);
                                    if (ENET_STATUS_SUCCESS == eStatus)
                                    {
                                        if ((pEnetHandle->PpsInterval != PPSConfig->PPSInterval) || (pEnetHandle->PpsWidth != PPSConfig->PPSWidth))
                                        {
                                            pEnetHandle->PpsInterval = PPSConfig->PPSInterval;
                                            pEnetHandle->PpsWidth = PPSConfig->PPSWidth;
                                            Enet_CalculatePPSIntervalWidth(pEnetHandle, eRolloverMode, &u32Interval, &u32Width);
                                            ENET_HWA_MAC_SetPPSInterval(pEnetHandle->EnetBase, ePPSChannel, u32Interval);
                                            ENET_HWA_MAC_SetPPSWidth(pEnetHandle->EnetBase, ePPSChannel, u32Width);
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                            if (ENET_STATUS_SUCCESS == eStatus)
                            {
                                ENET_HWA_MAC_SetChannelPPSTargetTimeModeSelect(pEnetHandle->EnetBase, ePPSChannel, ENET_MAC_PPS_TARGET_TIME_INT_ST);
                                ENET_HWA_MAC_SetFlexiblePPSCommand(pEnetHandle->EnetBase, ePPSChannel, PPSConfig->Cmd);
                                if (ENET_PTP_PPS_DIR_OUTPUT != ENET_HWA_Sysctrl_GetPPSPinDirection(ePPSChannel))
                                {
                                    ENET_HWA_Sysctrl_SetPPSPinDirection(ePPSChannel, ENET_PTP_PPS_DIR_OUTPUT);
                                }
                            }
                        }
                        else
                        {
                            eStatus = ENET_STATUS_NOT_READY;
                        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif
    return eStatus;
}

#if ENET_SUPPORT_TIME_SENSITIVE_NETWORK
/**
 * @brief                       Get EST configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[out] pEstConfig       Structure to save configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Get EST configurations successfully
 * @retval other values         Get EST configurations failed
 */
ENET_StatusType Enet_TSN_GetEstConfig(ENET_HandleType *pEnetHandle, ENET_EstConfigType *pEstConfig)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_GET_ESTCONFIG_SERVICE_ID))
    {
        if (pEstConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_GET_ESTCONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_GET_ESTCONFIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                pEstConfig->PtpTimeOffset = ENET_HWA_MTL_GetEstPtpTimeOffset(pEnetHandle->EnetBase);
                pEstConfig->CurrentTimeOffset = ENET_HWA_MTL_GetEstCurrentTimeOffset(pEnetHandle->EnetBase);
                pEstConfig->IntervalLeftShift = ENET_HWA_MTL_GetEstTimeIntervalLeftShift(pEnetHandle->EnetBase);
                pEstConfig->SchedErrLoopCount = ENET_HWA_MTL_GetEstScheduleErrorLoopCount(pEnetHandle->EnetBase);
                pEstConfig->DropSchedErrFrame = ENET_HWA_MTL_GetDropSchedulingErrorFramesEnFlag(pEnetHandle->EnetBase);
                pEstConfig->NotDropFrameSizeErr = ENET_HWA_MTL_GetDropFrameSizeErrorFramesDisableFlag(pEnetHandle->EnetBase);
                pEstConfig->Overhead = ENET_HWA_MTL_GetEstOverheadBytes(pEnetHandle->EnetBase);
                eStatus =  ENET_STATUS_SUCCESS;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Set EST configurations
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pEstConfig        EST configurations
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Set EST configurations successfully
 * @retval other values         Set EST configurations failed
 */
ENET_StatusType Enet_TSN_EstConfig(ENET_HandleType *pEnetHandle, const ENET_EstConfigType *pEstConfig)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_EST_CONFIG_SERVICE_ID))
    {
        if (pEstConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_EST_CONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (0u != Enet_AssertEstConfiguration(pEstConfig))
            {
                ENET_ReportDevError(ENET_EST_CONFIG_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    eStatus = ENET_STATUS_NOT_READY;
                    ENET_ReportDevError(ENET_EST_CONFIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
                    if (pEnetHandle->TxChannelCount < 2u)
                    {
                       ENET_ReportDevError(ENET_EST_CONFIG_SERVICE_ID, ENET_E_PARAM_TXCHANNEL);
                    }
                    else
                    {
#endif

                        ENET_HWA_MTL_SetEstPtpTimeOffset(pEnetHandle->EnetBase, (uint8_t)pEstConfig->PtpTimeOffset);
                        ENET_HWA_MTL_SetEstCurrentTimeOffset(pEnetHandle->EnetBase, pEstConfig->CurrentTimeOffset);
                        ENET_HWA_MTL_SetEstTimeIntervalLeftShift(pEnetHandle->EnetBase, pEstConfig->IntervalLeftShift);
                        ENET_HWA_MTL_SetEstScheduleErrorLoopCount(pEnetHandle->EnetBase, pEstConfig->SchedErrLoopCount);
                        ENET_HWA_MTL_SetDropSchedulingErrorFramesEnFlag(pEnetHandle->EnetBase, pEstConfig->DropSchedErrFrame);
                        ENET_HWA_MTL_SetDropFrameSizeErrorFramesDisableFlag(pEnetHandle->EnetBase, pEstConfig->NotDropFrameSizeErr);
                        ENET_HWA_MTL_SetEstOverheadBytes(pEnetHandle->EnetBase, pEstConfig->Overhead);
                        eStatus =  ENET_STATUS_SUCCESS;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Enable EST processing
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bEnable           Enable or disable
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Enable EST function successfully
 * @retval other values         Enable EST function failed
 */
ENET_StatusType Enet_TSN_EstEnable(ENET_HandleType *pEnetHandle, bool bEnable)
{
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_EST_ENABLE_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            eStatus = ENET_STATUS_NOT_READY;
            ENET_ReportDevError(ENET_EST_ENABLE_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
            if (pEnetHandle->TxChannelCount < 2u)
            {
               ENET_ReportDevError(ENET_EST_ENABLE_SERVICE_ID, ENET_E_PARAM_TXCHANNEL);
            }
            else
            {
#endif

                ENET_HWA_MTL_SetEstEnableFlag(pEnetHandle->EnetBase, bEnable);
                eStatus = ENET_STATUS_SUCCESS;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Read gate control list data
 * @param[in] pEnet             ENET instance base
 * @param[in] bGcrr             Enables or disables gate control related registers
 * @param[in] u8Address         GCL items address
 * @param[out] pData            Pointer to GCL data
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Read GCL data successfully
 * @retval ENET_STATUS_TIMEOUT  Read GCL data failed
 */
static ENET_StatusType Enet_GclRead(ENET_Type *const pEnet, bool bGcrr, uint8_t u8Address, uint32_t *pData)
{
    ENET_StatusType eStatus = ENET_STATUS_SUCCESS;
    uint32_t u32Timeout = 1000U;

    ENET_HWA_MTL_SetEstGateControlListAddress(pEnet, u8Address);
    ENET_HWA_MTL_SetGateControlReleatedRegistersEnFlag(pEnet, bGcrr);
    ENET_HWA_MTL_SetGclOperation(pEnet, ENET_MTL_GCL_READ);
    ENET_HWA_MTL_SetGclOperationStartFlag(pEnet, true);

    do
    {
        if (--u32Timeout == 0U)
        {
            eStatus = ENET_STATUS_TIMEOUT;
            break;
        }
    } while (ENET_HWA_MTL_GetGclOperationBusyState(pEnet));

    if (ENET_STATUS_SUCCESS == eStatus)
    {
        *pData = ENET_HWA_MTL_GetGclData(pEnet);
    }
    return eStatus;
}

/**
 * @brief                       Write gate control list data
 * @param[in] pEnet             ENET instance base
 * @param[in] bGcrr             Enables or disables gate control related registers
 * @param[in] eAddress          GCL items address
 * @param[in] eData             GCL data
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Write GCL data successfully
 * @retval ENET_STATUS_TIMEOUT  Write GCL data failed
 */
static ENET_StatusType Enet_GclWrite(ENET_Type *const pEnet, bool bGcrr, uint8_t u8Address, uint32_t u32Data)
{
    ENET_StatusType eStatus = ENET_STATUS_SUCCESS;
    uint32_t u32Timeout = 1000U;

    ENET_HWA_MTL_SetGclData(pEnet, u32Data);
    ENET_HWA_MTL_SetEstGateControlListAddress(pEnet, u8Address);
    ENET_HWA_MTL_SetGateControlReleatedRegistersEnFlag(pEnet, bGcrr);
    ENET_HWA_MTL_SetGclOperation(pEnet, ENET_MTL_GCL_WRITE);
    ENET_HWA_MTL_SetGclOperationStartFlag(pEnet, true);

    do
    {
        if (--u32Timeout == 0U)
        {
            eStatus = ENET_STATUS_TIMEOUT;
            break;
        }
    } while (ENET_HWA_MTL_GetGclOperationBusyState(pEnet));

    return eStatus;
}

/**
 * @brief                       Read the current gate control list
 * @param[in] pEnetHandle       ENET driver handle
 * @param[out] pGatelist        Gate control list
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Read GCL successfully
 * @retval other values         Read GCL failed
 */
ENET_StatusType Enet_TSN_GetEstGclConfig(ENET_HandleType *pEnetHandle, ENET_GateCtrlListType *pGatelist)
{
    uint32_t u32Channel, u32Index, u32Value;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_EST_GETGCLCONFIG_SERVICE_ID))
    {
        if (pGatelist == NULL_PTR)
        {
            ENET_ReportDevError(ENET_EST_GETGCLCONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                eStatus = ENET_STATUS_NOT_READY;
                ENET_ReportDevError(ENET_EST_GETGCLCONFIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif
                eStatus = Enet_GclRead(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_BTR_LOW, &pGatelist->BaseTimeS);
                if (ENET_STATUS_SUCCESS == eStatus)
                {
                    eStatus = Enet_GclRead(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_BTR_HIGH, &pGatelist->BaseTimeNs);
                    if (ENET_STATUS_SUCCESS == eStatus)
                    {
                        eStatus = Enet_GclRead(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_CTR_LOW, &u32Value);
                        if (ENET_STATUS_SUCCESS == eStatus)
                        {
                            pGatelist->CycleTimeS = (uint8_t)u32Value;
                            eStatus = Enet_GclRead(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_CTR_HIGH, &pGatelist->CycleTimeNs);
                            if (ENET_STATUS_SUCCESS == eStatus)
                            {
                                eStatus = Enet_GclRead(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_TER, &pGatelist->TimeExtension);
                                if (ENET_STATUS_SUCCESS == eStatus)
                                {
                                    eStatus = Enet_GclRead(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_LLR, &u32Value);
                                    if (ENET_STATUS_SUCCESS == eStatus)
                                    {
                                        pGatelist->GclLength = (uint16_t)u32Value;
                                        for (u32Index = 0U; u32Index < (uint32_t)pGatelist->GclLength; ++u32Index)
                                        {
                                            eStatus = Enet_GclRead(pEnetHandle->EnetBase, false, (uint8_t)u32Index, &u32Value);
                                            if (ENET_STATUS_SUCCESS != eStatus)
                                            {
                                                break;
                                            }

                                            pGatelist->Gate[u32Index].TimeInterval = u32Value & ((1u << ENET_TSN_GCL_INTERVAL_WIDTH_BITS) - 1u);
                                            for (u32Channel = 0U; u32Channel < pEnetHandle->TxChannelCount; ++u32Channel)
                                            {
                                                pGatelist->Gate[u32Index].GateOpen[u32Channel] =
                                                    (u32Value & (1u << (ENET_TSN_GCL_INTERVAL_WIDTH_BITS + u32Channel))) ? ENET_TRUE : ENET_FALSE;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Install new gate control list
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pGatelist         The Gate control list information
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Install new GCL successfully
 * @retval other values         Install new GCL failed
 */
ENET_StatusType Enet_TSN_EstGclConfig(ENET_HandleType *pEnetHandle, const ENET_GateCtrlListType *pGatelist)
{
    uint32_t u32Channel, u32Index, u32Value;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;
    uint32_t u32Timeout = 1500u;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_EST_GCLCONFIG_SERVICE_ID))
    {
        if (pGatelist == NULL_PTR)
        {
            ENET_ReportDevError(ENET_EST_GCLCONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (0u != Enet_AssertGclConfiguration(pGatelist))
            {
                ENET_ReportDevError(ENET_EST_GCLCONFIG_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    eStatus = ENET_STATUS_NOT_READY;
                    ENET_ReportDevError(ENET_EST_GCLCONFIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
                    if (pEnetHandle->TxChannelCount < 2u)
                    {
                       ENET_ReportDevError(ENET_EST_GCLCONFIG_SERVICE_ID, ENET_E_PARAM_TXCHANNEL);
                    }
                    else
                    {
#endif

                        for (u32Index = 0U; u32Index < (uint32_t)pGatelist->GclLength; ++u32Index)
                        {
                            u32Value = pGatelist->Gate[u32Index].TimeInterval & ((1u << ENET_TSN_GCL_INTERVAL_WIDTH_BITS) - 1u);
                            for (u32Channel = 0U; u32Channel < pEnetHandle->TxChannelCount; ++u32Channel)
                            {
                                if (ENET_TRUE == pGatelist->Gate[u32Index].GateOpen[u32Channel])
                                {
                                    u32Value |= 1u << (ENET_TSN_GCL_INTERVAL_WIDTH_BITS + u32Channel);
                                }
                            }
                            eStatus = Enet_GclWrite(pEnetHandle->EnetBase, false, (uint8_t)u32Index, u32Value);
                            if (ENET_STATUS_SUCCESS != eStatus)
                            {
                                break;
                            }
                        }

                        if (ENET_STATUS_SUCCESS == eStatus)
                        {
                            eStatus = Enet_GclWrite(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_BTR_LOW, pGatelist->BaseTimeS);
                            if (ENET_STATUS_SUCCESS == eStatus)
                            {
                                eStatus = Enet_GclWrite(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_BTR_HIGH, pGatelist->BaseTimeNs);
                                if (ENET_STATUS_SUCCESS == eStatus)
                                {
                                    eStatus = Enet_GclWrite(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_CTR_LOW, pGatelist->CycleTimeS);
                                    if (ENET_STATUS_SUCCESS == eStatus)
                                    {
                                        eStatus = Enet_GclWrite(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_CTR_HIGH, pGatelist->CycleTimeNs);
                                        if (ENET_STATUS_SUCCESS == eStatus)
                                        {
                                            eStatus = Enet_GclWrite(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_TER, pGatelist->TimeExtension);
                                            if (ENET_STATUS_SUCCESS == eStatus)
                                            {
                                                eStatus = Enet_GclWrite(pEnetHandle->EnetBase, true, (uint8_t)ENET_MTL_GCL_LLR, pGatelist->GclLength);
                                                if (ENET_STATUS_SUCCESS == eStatus)
                                                {
                                                    ENET_HWA_MTL_SetSwitchGateControlListEnFlag(pEnetHandle->EnetBase, true);
                                                    while (!ENET_HWA_MTL_GetSwitchGateControlListCompleteFlag(pEnetHandle->EnetBase))
                                                    {
                                                        if (--u32Timeout == 0u)
                                                        {
                                                            eStatus = ENET_STATUS_TIMEOUT;
                                                            break;
                                                        }
                                                    }

                                                    if (ENET_STATUS_SUCCESS == eStatus)
                                                    {
                                                        ENET_HWA_MTL_ClearSwitchGateControlListCompleteFlag(pEnetHandle->EnetBase);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif

    return eStatus;
}

/**
 * @brief                       Enable or disable the frame preemption function
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pConfig           Preemption configuration structure
 * @return                      ENET_StatusType
 * @retval ENET_STATUS_SUCCESS  Enable or disable frame preemption successfully
 * @retval other values         Enable or disable frame preemption failed
 */
ENET_StatusType Enet_TSN_PreemptionConfig(ENET_HandleType *pEnetHandle, const ENET_PreemptionConfigType *pConfig)
{
    uint8_t u8Channel;
    uint32_t u32Classification;
    ENET_StatusType eStatus = ENET_STATUS_INVALID_PARAM;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_PREEMPTION_CONFIG_SERVICE_ID))
    {
        if (pConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_PREEMPTION_CONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (0u != Enet_AssertPreemptionConfiguration(pConfig))
            {
                ENET_ReportDevError(ENET_PREEMPTION_CONFIG_SERVICE_ID, ENET_E_PARAM_ASSERTION);
            }
            else
            {
                if (pEnetHandle->State == ENET_STATE_UNINIT)
                {
                    eStatus = ENET_STATUS_NOT_READY;
                    ENET_ReportDevError(ENET_PREEMPTION_CONFIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
                }
                else
                {
                    if (pEnetHandle->TxChannelCount < 2u)
                    {
                       ENET_ReportDevError(ENET_PREEMPTION_CONFIG_SERVICE_ID, ENET_E_PARAM_TXCHANNEL);
                    }
                    else
                    {
#endif

                        if (pConfig->PreemptionEnable)
                        {
                            u32Classification = 0u;
                            for (u8Channel = 0u; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
                            {
                                if (pConfig->Classification[u8Channel] == ENET_CLISSIFICATION_PREEMPTABLE)
                                {
                                    u32Classification |= 1u << u8Channel;
                                }
                            }
                            ENET_HWA_MTL_SetPreemptionClassification(pEnetHandle->EnetBase, (uint8_t)u32Classification);
                            ENET_HWA_MTL_SetPreemptionReleaseAdvance(pEnetHandle->EnetBase, pConfig->ReleaseAdvance);
                            ENET_HWA_MTL_SetPreemptionHoldAdvance(pEnetHandle->EnetBase, pConfig->HoldAdvance);
                            ENET_HWA_MAC_SetFramePreemptionEnFlag(pEnetHandle->EnetBase, ENET_TRUE);
                        }
                        else
                        {
                            ENET_HWA_MAC_SetFramePreemptionEnFlag(pEnetHandle->EnetBase, ENET_FALSE);
                        }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                    }
                }
            }
        }
    }
#endif

    return eStatus;
}
#endif /* ENET_SUPPORT_TIME_SENSITIVE_NETWORK */

/**
 * @brief                       ENET get MAC management counters configuration
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMMCConfig        MAC management configuration type
 */
void Enet_GetMMCConfig(const ENET_HandleType *pEnetHandle, ENET_MMCConfigType *pMMCConfig)
{
    uint32_t u32IntMask = 0u;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_GET_MMCCONFIG_SERVICE_ID))
    {
        if (pMMCConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_GET_MMCCONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_GET_MMCCONFIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                pMMCConfig->UpdateDropedBroadcast = ENET_HWA_MAC_GetUpdateMmcCntForDroppedBroadcastPktEnFlag(pEnetHandle->EnetBase);
                pMMCConfig->PresetLevel = ENET_HWA_MAC_GetMmcCounterPresetLevel(pEnetHandle->EnetBase);
                pMMCConfig->ResetOnRead = ENET_HWA_MAC_GetMmcCounterResetOnReadEnFlag(pEnetHandle->EnetBase);
                pMMCConfig->CounterRollover = !ENET_HWA_MAC_GetMmcCounterStopRolloverEnFlag(pEnetHandle->EnetBase);
                u32IntMask = ENET_HWA_MAC_GetMmcRxInterruptMask(pEnetHandle->EnetBase);
                pMMCConfig->MmcRxCntIntEn = (~u32IntMask) & 0x03FFFFFFu;
                u32IntMask = ENET_HWA_MAC_GetMmcTxInterruptMask(pEnetHandle->EnetBase);
                pMMCConfig->MmcTxCntIntEn = (~u32IntMask) & 0x03FFFFFFu;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
}

/**
 * @brief                       ENET set MAC management counters configuration
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pMMCConfig        MAC management configuration type
 */
void Enet_SetMMCConfig(ENET_HandleType *pEnetHandle, const ENET_MMCConfigType *pMMCConfig)
{
    uint32_t u32IntMask = 0u;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_MMCCONFIG_SERVICE_ID))
    {
        if (pMMCConfig == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_MMCCONFIG_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_SET_MMCCONFIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                ENET_HWA_MAC_SetUpdateMmcCntForDroppedBroadcastPktEnFlag(pEnetHandle->EnetBase, pMMCConfig->UpdateDropedBroadcast);
                ENET_HWA_MAC_SetMmcCounterPresetLevel(pEnetHandle->EnetBase, pMMCConfig->PresetLevel);
                ENET_HWA_MAC_SetMmcCounterResetOnReadEnFlag(pEnetHandle->EnetBase, pMMCConfig->ResetOnRead);
                ENET_HWA_MAC_SetMmcCounterStopRolloverEnFlag(pEnetHandle->EnetBase, pMMCConfig->CounterRollover ? false : true);
                u32IntMask = ENET_HWA_MAC_GetMmcRxInterruptMask(pEnetHandle->EnetBase);
                u32IntMask = (u32IntMask & 0xFC000000u) | (~(pMMCConfig->MmcRxCntIntEn & 0x03FFFFFFu));
                ENET_HWA_MAC_SetMmcRxInterruptMask(pEnetHandle->EnetBase, u32IntMask);
                u32IntMask = ENET_HWA_MAC_GetMmcTxInterruptMask(pEnetHandle->EnetBase);
                u32IntMask = (u32IntMask & 0xFC000000u) | (~(pMMCConfig->MmcTxCntIntEn & 0x03FFFFFFu));
                ENET_HWA_MAC_SetMmcTxInterruptMask(pEnetHandle->EnetBase, u32IntMask);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
}

/**
 * @brief                       Preset MAC management counters
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_MMCCounterPreset(ENET_HandleType *pEnetHandle)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMC_COUNTER_PRESET_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_MMC_COUNTER_PRESET_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

        ENET_HWA_MAC_PresetMmcCounters(pEnetHandle->EnetBase);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       Freeze MMC counters to their current value
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] bFreeze           Enable or disable Freeze
 */
void Enet_MMCCounterFreeze(ENET_HandleType *pEnetHandle, bool bFreeze)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMC_COUNTER_FREEZE_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_MMC_COUNTER_FREEZE_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            ENET_HWA_MAC_SetMmcCounterFreezeStatus(pEnetHandle->EnetBase, bFreeze);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       Reset MAC management counters to zero
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_MMCCounterReset(ENET_HandleType *pEnetHandle)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMC_COUNTER_RESET_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_MMC_COUNTER_RESET_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            ENET_HWA_MAC_ResetMmcCounters(pEnetHandle->EnetBase);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       Get MMC transmit counters interrupt status
 * @param[in] pEnetHandle       ENET driver handle
 * @note                        User must read the respective counter to clear the MMC interrupt bit.
 */
uint32_t Enet_GetMMCTxInterrupts(const ENET_HandleType *pEnetHandle)
{
    uint32_t u32Status = 0;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMC_GET_TXINT_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_MMC_GET_TXINT_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            u32Status = ENET_HWA_MAC_GetMmcTxInterruptStatus(pEnetHandle->EnetBase) & 0x03FFFFFFu;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
    return u32Status;
}

/**
 * @brief                       Get MMC receive counters interrupt status
 * @param[in] pEnetHandle       ENET driver handle
 * @note                        User must read the respective counter to clear the MMC interrupt bit.
 */
uint32_t Enet_GetMMCRxInterrupts(const ENET_HandleType *pEnetHandle)
{
    uint32_t u32Status = 0;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMC_GET_RXINT_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_MMC_GET_RXINT_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

        u32Status = ENET_HWA_MAC_GetMmcRxInterruptStatus(pEnetHandle->EnetBase) & 0x03FFFFFFu;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif

    return u32Status;
}

/**
 * @brief                       Get ENET MAC management transmit counters
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCounter          MAC management transmit counter type
 */
uint32_t Enet_GetMMCTxCounter(const ENET_HandleType *pEnetHandle, Enet_MMCTxCounterType eCounter)
{
    volatile const uint32_t *pCounters;
    uint32_t u32Counter = 0;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMC_GET_TXCOUNTER_SERVICE_ID))
    {
        if ((uint32_t)eCounter > (uint32_t)ENET_CTR_TX_OSIZE_PACKETS_GOOD)
        {
            ENET_ReportDevError(ENET_MMC_GET_TXCOUNTER_SERVICE_ID, ENET_E_PARAM_ASSERTION);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_MMC_GET_TXCOUNTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                pCounters = ((volatile const uint32_t *)&(pEnetHandle->EnetBase->TX_OCTET_COUNT_GOOD_BAD)) + (uint32_t)eCounter;
                u32Counter = *pCounters;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
    return u32Counter;
}

/**
 * @brief                       Get ENET MAC management receive counters
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eCounter          MAC management receive counter type
 */
uint32_t Enet_GetMMCRxCounter(const ENET_HandleType *pEnetHandle, Enet_MMCRxCounterType eCounter)
{
    volatile const uint32_t *pCounters;
    uint32_t u32Counter = 0;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_MMC_GET_RXCOUNTER_SERVICE_ID))
    {
        if ((uint32_t)eCounter > (uint32_t)ENET_CTR_RX_CONTROL_PACKETS_GOOD)
        {
            ENET_ReportDevError(ENET_MMC_GET_RXCOUNTER_SERVICE_ID, ENET_E_PARAM_ASSERTION);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_MMC_GET_RXCOUNTER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                pCounters = ((volatile const uint32_t *)&(pEnetHandle->EnetBase->RX_PACKETS_COUNT_GOOD_BAD)) + (uint32_t)eCounter;
                u32Counter = *pCounters;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
    return u32Counter;
}

/**
 * @brief                       Get flow control configuration
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFlowControl      MAC flow control configuration
 */
void Enet_GetFlowControlConfig(const ENET_HandleType *pEnetHandle, ENET_FlowControlType *pFlowControl)
{
    uint32_t u8Channel;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_GET_FLOWCTRL_SERVICE_ID))
    {
        if (pFlowControl == NULL_PTR)
        {
            ENET_ReportDevError(ENET_GET_FLOWCTRL_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_GET_FLOWCTRL_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
#endif

                for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
                {
                    pFlowControl->RxQueueConfig[u8Channel].RxDeactiveThreshold =
                            ENET_HWA_MTL_GetRxDeactivateFlowCtrlThres(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel);
                    pFlowControl->RxQueueConfig[u8Channel].RxActiveThreshold =
                            ENET_HWA_MTL_GetRxActivateFlowCtrlThres(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel);
                    pFlowControl->RxQueueConfig[u8Channel].RxHwFlowCtrlEnable =
                            ENET_HWA_MTL_GetRxHwFlowCtrlEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel);
                }
                pFlowControl->PauseTime = ENET_HWA_MAC_GetQueue0TxPauseTime(pEnetHandle->EnetBase);
                pFlowControl->ZeroQuantaPauseDisable = ENET_HWA_MAC_GetQueue0TxZeroQuantaPauseDisableFlag(pEnetHandle->EnetBase);
                pFlowControl->PauseThreshold = ENET_HWA_MAC_GetQueue0TxPauseLowThreshold(pEnetHandle->EnetBase);
                pFlowControl->MacTxFlowCtrlEnable = ENET_HWA_MAC_GetQueue0TxFlowCtrlEnableFlag(pEnetHandle->EnetBase);
                pFlowControl->UnicastPauseEnable = ENET_HWA_MAC_GetUnicastPausePacketDetectEnFlag(pEnetHandle->EnetBase);
                pFlowControl->MacRxFlowCtrlEnable = ENET_HWA_MAC_GetRxFlowCtrlEnFlag(pEnetHandle->EnetBase);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
            }
        }
    }
#endif
}

/**
 * @brief                       Configure and enable flow control
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] pFlowControl      MAC flow control configuration
 */
void Enet_FlowControlConfig(ENET_HandleType *pEnetHandle, const ENET_FlowControlType *pFlowControl)
{
    uint32_t u8Channel;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SET_FLOWCTRL_SERVICE_ID))
    {
        if (pFlowControl == NULL_PTR)
        {
            ENET_ReportDevError(ENET_SET_FLOWCTRL_SERVICE_ID, ENET_E_PARAM_POINTER);
        }
        else
        {
            if (pEnetHandle->State == ENET_STATE_UNINIT)
            {
                ENET_ReportDevError(ENET_SET_FLOWCTRL_SERVICE_ID, ENET_E_DRIVER_UNINIT);
            }
            else
            {
                if (0u != Enet_AssertFlowControlConfiguration(pEnetHandle, pFlowControl))
                {
                    ENET_ReportDevError(ENET_SET_FLOWCTRL_SERVICE_ID, ENET_E_PARAM_ASSERTION);
                }
                else
                {
#endif

                    for (u8Channel = 0u; u8Channel < pEnetHandle->RxChannelCount; ++u8Channel)
                    {
                        ENET_HWA_MTL_SetRxDeactivateFlowCtrlThres(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                                  pFlowControl->RxQueueConfig[u8Channel].RxDeactiveThreshold);
                        ENET_HWA_MTL_SetRxActivateFlowCtrlThres(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                                pFlowControl->RxQueueConfig[u8Channel].RxActiveThreshold);
                        ENET_HWA_MTL_SetRxHwFlowCtrlEnFlag(pEnetHandle->EnetBase, (ENET_MTL_QueueType)u8Channel,
                                                           pFlowControl->RxQueueConfig[u8Channel].RxHwFlowCtrlEnable);
                    }

                    ENET_HWA_MAC_SetQueue0TxPauseTime(pEnetHandle->EnetBase, pFlowControl->PauseTime);
                    ENET_HWA_MAC_SetQueue0TxZeroQuantaPauseDisableFlag(pEnetHandle->EnetBase, pFlowControl->ZeroQuantaPauseDisable);
                    ENET_HWA_MAC_SetQueue0TxPauseLowThreshold(pEnetHandle->EnetBase, pFlowControl->PauseThreshold);
                    ENET_HWA_MAC_SetQueue0TxFlowCtrlEnableFlag(pEnetHandle->EnetBase, pFlowControl->MacTxFlowCtrlEnable);

                    ENET_HWA_MAC_SetUnicastPausePacketDetectEnFlag(pEnetHandle->EnetBase, pFlowControl->UnicastPauseEnable);
                    ENET_HWA_MAC_SetRxFlowCtrlEnFlag(pEnetHandle->EnetBase, pFlowControl->MacRxFlowCtrlEnable);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
                }
            }
        }
    }
#endif
}

/**
 * @brief                       Generate and transmits a single pause packet
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_FlowControlSoftwareTrigger(ENET_HandleType *pEnetHandle)
{
#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_FLOWCTRL_SOFTTRIG_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_FLOWCTRL_SOFTTRIG_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            ENET_HWA_MAC_InitiatePausePacketOrBackpressure(pEnetHandle->EnetBase);

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}


/**
 * @brief                       ENET driver PTP interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 */
static void Enet_PTPIrqHandler(ENET_HandleType *pEnetHandle)
{
    uint32_t u32PTPStatus;

    u32PTPStatus = pEnetHandle->EnetBase->MAC_TIMESTAMP_STATUS;

    if (pEnetHandle->EventCallback != NULL_PTR)
    {
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTARGT0_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME0_REACHED);
        }
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR0_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME0_ERROR);
        }
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTARGT1_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME1_REACHED);
        }
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR1_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME1_ERROR);
        }
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTARGT2_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME2_REACHED);
        }
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR2_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME2_ERROR);
        }
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTARGT3_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME3_REACHED);
        }
        if (0u != (u32PTPStatus & ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR3_MASK))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_TARGET_TIME3_ERROR);
        }
    }
}

/**
 * @brief                       ENET driver MMC interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 */
static void Enet_MMCIrqHandler(ENET_HandleType *pEnetHandle)
{
    uint32_t u32RxStatus, u32TxStatus, i;

    u32RxStatus = pEnetHandle->EnetBase->MMC_RX_INTERRUPT;
    u32TxStatus = pEnetHandle->EnetBase->MMC_TX_INTERRUPT;

    if (pEnetHandle->EventCallback != NULL_PTR)
    {
        if (0u != (u32RxStatus & 0x03FFFFFFu))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_MMC_RX_COUNTER);
        }
        if (0u != (u32TxStatus & 0x03FFFFFFu))
        {
            pEnetHandle->EventCallback(pEnetHandle, ENET_EVENT_MMC_TX_COUNTER);
        }
    }
    else
    {
        for (i = (uint32_t)ENET_CTR_RX_PACKETS_COUNT_GOOD_BAD; i <= (uint32_t)ENET_CTR_RX_CONTROL_PACKETS_GOOD; ++i)
        {
            if (0u != (u32RxStatus & (1u << i)))
            {
                (void)(*(volatile const uint32_t *)(&(pEnetHandle->EnetBase->RX_PACKETS_COUNT_GOOD_BAD) + i));
            }
        }
        for (i = (uint32_t)ENET_CTR_TX_OCTET_COUNT_GOOD_BAD; i <= (uint32_t)ENET_CTR_TX_OSIZE_PACKETS_GOOD; ++i)
        {
            if (0u != (u32TxStatus & (1u << i)))
            {
                (void)(*(volatile const uint32_t *)(&(pEnetHandle->EnetBase->TX_OCTET_COUNT_GOOD_BAD) + i));
            }
        }
    }
}

/**
 * @brief                       ENET driver MAC interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 */
static void Enet_MACIrqHandler(ENET_HandleType *pEnetHandle)
{
    uint32_t u32Status, u32IntEnable;

    u32Status = ENET_HWA_MAC_GetInterruptStatus(pEnetHandle->EnetBase);
    u32IntEnable = ENET_HWA_MAC_GetInterruptEnable(pEnetHandle->EnetBase);

    if (0u != (u32Status & ENET_MAC_INTERRUPT_STATUS_MDIOIS_MASK) &&
        0u != (u32IntEnable & ENET_MAC_INTERRUPT_ENABLE_MDIOIE_MASK))
    {

    }

    if (0u != (u32Status & ENET_MAC_INTERRUPT_STATUS_RXSTSIS_MASK) &&
        0u != (u32IntEnable & ENET_MAC_INTERRUPT_ENABLE_RXSTSIE_MASK))
    {

    }

    if (0u != (u32Status & ENET_MAC_INTERRUPT_STATUS_TXSTSIS_MASK) &&
        0u != (u32IntEnable & ENET_MAC_INTERRUPT_ENABLE_TXSTSIE_MASK))
    {

    }

    if (0u != (u32Status & ENET_MAC_INTERRUPT_STATUS_TSIS_MASK) &&
        0u != (u32IntEnable & ENET_MAC_INTERRUPT_ENABLE_TSIE_MASK))
    {
        Enet_PTPIrqHandler(pEnetHandle);
    }

    if (0u != (u32Status & ENET_MAC_INTERRUPT_STATUS_MMCIS_MASK))
    {
        Enet_MMCIrqHandler(pEnetHandle);
    }

    if (0u != (u32Status & ENET_MAC_INTERRUPT_STATUS_PHYIS_MASK) &&
        0u != (u32IntEnable & ENET_MAC_INTERRUPT_ENABLE_PHYIE_MASK))
    {

    }
}

/**
 * @brief                       ENET driver MTL interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 */
static void Enet_MTLIrqHandler(ENET_HandleType *pEnetHandle)
{
    ENET_Type *EnetBase = pEnetHandle->EnetBase;
    uint32_t u32Status;
    uint8_t u8Channel;

    for (u8Channel = 0u; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
    {
        if (0u != (EnetBase->MTL.INTERRUPT_STATUS & (1u << u8Channel)))
        {
            u32Status = ENET_HWA_MTL_GetInterruptCtrlStatus(EnetBase, (ENET_MTL_QueueType)u8Channel);
            if (0u != (u32Status & ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS_MASK) &&
                0u != (u32Status & ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE_MASK))
            {

            }
            if (0u != (u32Status & ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS_MASK) &&
                0u != (u32Status & ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIE_MASK))
            {

            }
            if (0u != (u32Status & ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUNFIS_MASK) &&
                0u != (u32Status & ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE_MASK))
            {

            }
            ENET_HWA_MTL_ClearAllIntStatus(EnetBase, (ENET_MTL_QueueType)u8Channel);
        }
    }
}

/**
 * @brief                       ENET driver DMA interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] u8Channel         ENET DMA channel
 */
static void Enet_DMAIrqHandler(ENET_HandleType *pEnetHandle, uint8_t u8Channel)
{
    uint32_t u32IntEn;
    uint32_t u32IntStatus;

    u32IntEn = ENET_HWA_DMA_GetEnabledInterrupts(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
    u32IntStatus = ENET_HWA_DMA_GetCurrentStatus(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);

    /* Handle DMA Abnormal Interrupts */
    if (0u != (u32IntStatus & ENET_DMA_CH0_STATUS_AIS_MASK) &&
        0u != (u32IntEn & ENET_DMA_CH0_INTERRUPT_ENABLE_AIE_MASK))
    {
        if (0u != (u32IntStatus & ENET_DMA_CH0_STATUS_FBE_MASK))
        {
            ENET_HWA_DMA_DisableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_ABNORMAL_INTERRUPT);
            ENET_HWA_DMA_DisableInterrupt(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel, ENET_DMA_NORMAL_INTERRUPT);
            pEnetHandle->State = ENET_STATE_ERROR;
        }
        else
        {


        }
        /* Clear Abnormal Interrupt status */
        ENET_HWA_DMA_ClearAllAbnormalInterruptFlags(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
    }

    /* Handle DMA Normal Interrupts */
    if (0u != (u32IntStatus & ENET_DMA_CH0_STATUS_NIS_MASK) &&
        0u != (u32IntEn & ENET_DMA_CH0_INTERRUPT_ENABLE_NIE_MASK))
    {

        /* Clear Normal Interrupt status */
        ENET_HWA_DMA_ClearAllNormalInterruptFlags(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel);
    }
}

/**
 * @brief                       ENET driver system interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 */
void Enet_SystemIrqHandler(ENET_HandleType *pEnetHandle)
{
    uint8_t u8Channel;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_SYSIRQ_HANDLER_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_SYSIRQ_HANDLER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            if (ENET_HWA_DMA_GetMACIntStatus(pEnetHandle->EnetBase))
            {
                Enet_MACIrqHandler(pEnetHandle);
            }
            if (ENET_HWA_DMA_GetMTLIntStatus(pEnetHandle->EnetBase))
            {
                Enet_MTLIrqHandler(pEnetHandle);
            }

            for (u8Channel = 0; u8Channel < ENET_CHANNEL_COUNT; ++u8Channel)
            {
                if (ENET_HWA_DMA_GetDMAChannelIntStatus(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)u8Channel))
                {
                    Enet_DMAIrqHandler(pEnetHandle, u8Channel);
                }
            }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       ENET driver DMA RX channel interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          ENET DMA channel
 */
void Enet_RxIrqHandler(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel)
{
    uint32_t u32IntEn;
    uint32_t u32IntStatus;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_RXIRQ_HANDLER_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_RXIRQ_HANDLER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            u32IntEn = ENET_HWA_DMA_GetEnabledInterrupts(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)eChannel);
            u32IntStatus = ENET_HWA_DMA_GetCurrentStatus(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)eChannel);

            if ((0u != (u32IntStatus & ENET_DMA_CH0_STATUS_RI_MASK)) &&
                (0u != (u32IntEn & ENET_DMA_CH0_INTERRUPT_ENABLE_RIE_MASK)))
            {
                /* Clear RI flag bit */
                ENET_HWA_DMA_ClearRxInterruptFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)eChannel);
                if (pEnetHandle->RxReady != NULL_PTR)
                {
                    pEnetHandle->RxReady(pEnetHandle, eChannel);
                }
            }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

/**
 * @brief                       ENET driver DMA TX channel interrupt handler
 * @param[in] pEnetHandle       ENET driver handle
 * @param[in] eChannel          ENET DMA channel
*/
void Enet_TxIrqHandler(ENET_HandleType *pEnetHandle, ENET_ChannelType eChannel)
{
    uint32_t u32IntEn;
    uint32_t u32IntStatus;

#if (ENET_DEV_ERROR_REPORT == STD_ON)
    if (0u == Enet_HandleInstanceCheck(pEnetHandle, ENET_TXIRQ_HANDLER_SERVICE_ID))
    {
        if (pEnetHandle->State == ENET_STATE_UNINIT)
        {
            ENET_ReportDevError(ENET_TXIRQ_HANDLER_SERVICE_ID, ENET_E_DRIVER_UNINIT);
        }
        else
        {
#endif

            u32IntEn = ENET_HWA_DMA_GetEnabledInterrupts(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)eChannel);
            u32IntStatus = ENET_HWA_DMA_GetCurrentStatus(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)eChannel);

            if ((0u != (u32IntStatus & ENET_DMA_CH0_STATUS_TI_MASK)) &&
                (0u != (u32IntEn & ENET_DMA_CH0_INTERRUPT_ENABLE_TIE_MASK)))
            {
                /* Clear TI flag bit */
                ENET_HWA_DMA_ClearTxInterruptFlag(pEnetHandle->EnetBase, (ENET_DMA_ChannelType)eChannel);
                if (pEnetHandle->TxComplete != NULL_PTR)
                {
                    pEnetHandle->TxComplete(pEnetHandle, eChannel);
                }
            }

#if (ENET_DEV_ERROR_REPORT == STD_ON)
        }
    }
#endif
}

#endif /* ENET_INSTANCE_COUNT > 0u */
