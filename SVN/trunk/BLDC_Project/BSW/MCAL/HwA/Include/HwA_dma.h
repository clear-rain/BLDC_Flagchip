/**
 * @file HwA_dma.h
 * @author Flagchip030
 * @brief DMA hardware access layer
 * @version 2.0.0
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip030   N/A          First version
*********************************************************************************/

#ifndef _HWA_DMA_H_
#define _HWA_DMA_H_

#include "device_header.h"

#if DMA_INSTANCE_COUNT > 0U

#define DMA_CH_TO_DCHPRI(x)   ((x) ^ 3U)

/**
 * @defgroup HwA_dma HwA_dma
 * @ingroup module_driver_dma
 * @{
 */

/**
 * @brief DMA running status
 *
 */
typedef enum
{
    DMA_RUNNING_STATUS_IDLE   = 0x0U,   /**< The DMA engine is idle */
    DMA_RUNNING_STATUS_ACTIVE = 0x1U    /**< The DMA engine is transferring data */
} DMA_RunningStatusType;

/**
 * @brief DMA channel arbitration algorithm used in the channel arbitration phase
 *
 */
typedef enum
{
    DMA_ARBITRATION_ALGORITHM_FIXED_PRIORITY = 0U,   /**< Use the fixed priority for arbitration */
    DMA_ARBITRATION_ALGORITHM_ROUND_ROBIN    = 1U    /**< Use the channel number for arbitration,
                                                          higher channel number has higher priority */
} DMA_ArbitrationAlgorithmType;

/**
 * @brief Defines the size of data in one transfer
 *
 * One transfer can contain multiple block, and one block may contain multiple
 * data, this parameter specifies the size of data which the DMA engine will
 * access one time in the memory.
 *
 */
typedef enum
{

    DMA_TRANSFER_SIZE_1B  = 0x0U,
    DMA_TRANSFER_SIZE_2B  = 0x1U,
    DMA_TRANSFER_SIZE_4B  = 0x2U,
    DMA_TRANSFER_SIZE_16B = 0x4U,
    DMA_TRANSFER_SIZE_32B = 0x5U
} DMA_TransferSizeType;

/**
 * @brief Get active status of the DMA instance
 *
 * @param pDma the base address of the DMA instance
 * @return DMA_RUNNING_STATUS_ACTIVE DMA is executing a channel
 * @return DMA_RUNNING_STATUS_IDLE DMA is idle
 */
LOCAL_INLINE DMA_RunningStatusType DMA_HWA_GetStatus(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_ACTIVE_MASK) >> DMA_CR_ACTIVE_SHIFT;
    return (DMA_RunningStatusType)u32TmpVal;
}

/**
 * @brief Get whether the DMA instance is cancelling
 *
 * @param pDma the base address of the DMA instance
 * @return true cancel operation is requested and has not been finished
 * @return false DMA is under normal operation
 */
LOCAL_INLINE bool DMA_HWA_GetCancelTransferStatus(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_CX_MASK) >> DMA_CR_CX_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Cancel the remaining transfer of the DMA
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_CancelTransfer(DMA_Type *const pDma)
{
    pDma->CR |= DMA_CR_CX_MASK;
}

/**
 * @brief Get whether the DMA instance is cancelling with error
 *
 * @param pDma the base address of the DMA instance
 * @return true cancel operation is requested and has not been finished
 * @return false DMA is under normal operation
 */
LOCAL_INLINE bool DMA_HWA_GetErrorCancelTransferStatus(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_ECX_MASK) >> DMA_CR_ECX_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Cancel the remaining transfer of the DMA and generate an error after finished cancelling
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_ErrorCancelTransfer(DMA_Type *const pDma)
{
    pDma->CR |= DMA_CR_ECX_MASK;
}

/**
 * @brief Get whether inner loop mapping is enabled
 *
 * @param pDma the base address of the DMA instance
 * @return true inner loop mapping is enabled
 * @return false inner loop mapping is disabled
 */
LOCAL_INLINE bool DMA_HWA_GetInnerLoopMappingEnableFlag(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_EILM_MASK) >> DMA_CR_EILM_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable inner loop mapping
 *
 * @note Only after enabling inner loop mapping, you can apply an offset to the source
 * and/or destination address after the inner loop finishes.
 *
 * @param pDma the base address of the DMA instance
 * @param bEnable whether to enable the inner loop mapping
 */
LOCAL_INLINE void DMA_HWA_SetInnerLoopMappingEnableFlag(DMA_Type *const pDma, bool bEnable)
{
    pDma->CR = (pDma->CR & ~DMA_CR_EILM_MASK) | DMA_CR_EILM(bEnable);
}

/**
 * @brief Get whether the continuous trig mode is enabled
 * When continuous trig mode is enabled, channel arbitration is not used for a inner loop
 * channel trig before being activated again. Upon inner loop completion, the channel
 * activates again if that channel has a inner loop channel trig enabled and the trig
 * channel is itself. This effectively applies the inner loop offsets and restarts the next
 * inner loop.
 *
 * @param pDma the base address of the DMA instance
 * @return true continuous trig mode is enabled
 * @return false continuous trig mode is disabled
 */
LOCAL_INLINE bool DMA_HWA_GetContinuousTrigModeEnableFlag(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_CTM_MASK) >> DMA_CR_CTM_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable the continuous trig mode
 *
 * @param pDma the base address of the DMA instance
 * @param bEnable whether to enable the continuous trig mode
 */
LOCAL_INLINE void DMA_HWA_SetContinuousTrigModeEnableFlag(DMA_Type *const pDma, bool bEnable)
{
    pDma->CR = (pDma->CR & ~DMA_CR_CTM_MASK) | DMA_CR_CTM(bEnable);
}

/**
 * @brief Get whether the DMA is halted
 * When the DMA is halted, it will ignore all service requests
 * @param pDma the base address of the DMA instance
 * @return true the DMA is halted
 * @return true the DMA is not halted
 */
LOCAL_INLINE bool DMA_HWA_GetHatlStatus(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_HALT_MASK) >> DMA_CR_HALT_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Halt the DMA operations
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_HaltOperations(DMA_Type *const pDma)
{
    pDma->CR |= DMA_CR_HALT_MASK;
}

/**
 * @brief Clear the halt flag of the DMA instance
 * After HALT is cleared, the DMA could continue to operate
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_ClearHaltFlag(DMA_Type *const pDma)
{
    pDma->CR &= ~DMA_CR_HALT_MASK;
}

/**
 * @brief Get whether halt on error is enabled on the DMA instance
 *
 * @param pDma the base address of the DMA instance
 * @return true halt on error is enabled, any error will cause HALT flag to be set
 * @return false halt on error is disabled
 */
LOCAL_INLINE bool DMA_HWA_GetHaltOnErrorFlag(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_HOE_MASK) >> DMA_CR_HOE_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable halt on error on the DMA instance
 *
 * @note Ff halt on error is enabled, any error will cause HALT flag to be set
 *
 * @param pDma the base address of the DMA instance
 * @param bEnable whether to enable halt on error
 */
LOCAL_INLINE void DMA_HWA_SetHaltOnErrorFlag(DMA_Type *const pDma, bool bEnable)
{
    pDma->CR = (pDma->CR & ~DMA_CR_HOE_MASK) | DMA_CR_HOE(bEnable);
}

/**
 * @brief Get the DMA arbitration algorithm
 *
 * @param pDma the base address of the DMA instance
 * @return DMA_ArbitrationAlgorithmType the DMA arbitration algorithm
 */
LOCAL_INLINE DMA_ArbitrationAlgorithmType DMA_HWA_GetArbitrationAlgorithm(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_ERCA_MASK) >> DMA_CR_ERCA_SHIFT;
    return (DMA_ArbitrationAlgorithmType)u32TmpVal;
}

/**
 * @brief Set the DMA arbitration algorithm
 *
 * @param pDma the base address of the DMA instance
 * @param eAlgorithm the DMA arbitration algorithm
 */
LOCAL_INLINE void DMA_HWA_SetArbitrationAlgorithm(DMA_Type *const pDma, DMA_ArbitrationAlgorithmType eAlgorithm)
{
    pDma->CR = (pDma->CR & ~DMA_CR_ERCA_MASK) | DMA_CR_ERCA(eAlgorithm);
}

/**
 * @brief Get whether the DMA is configured to stop under debug mode
 *
 * @param pDma the base address of the DMA instance
 * @return true the DMA is will stop under debug mode
 * @return true the DMA is will continue to operate under debug mode
 */
LOCAL_INLINE bool DMA_HWA_GetDebugModeStopFlag(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = (pDma->CR & DMA_CR_DBGS_MASK) >> DMA_CR_DBGS_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the control register of the DMA instance
 *
 * @param pDma the base address of the DMA instance
 * @return uint32_t the control register settings
 */
LOCAL_INLINE uint32_t DMA_HWA_GetControlRegister(const DMA_Type *const pDma)
{
    return pDma->CR;
}

/**
 * @brief Set the control register of the DMA instance
 *
 * @param pDma the base address of the DMA instance
 * @param u32Settings the settings of the DMA control register
 */
LOCAL_INLINE void DMA_HWA_SetControlRegister(DMA_Type *const pDma, uint32_t u32Settings)
{
    pDma->CR = u32Settings;
}

/**
 * @brief Set whether to stop DMA under debug mode
 *
 * @param pDma the base address of the DMA instance
 * @param bEnable whether to stop DMA under debug mode
 */
LOCAL_INLINE void DMA_HWA_SetDebugModeStopFlag(DMA_Type *const pDma, bool bEnable)
{
    pDma->CR = (pDma->CR & ~DMA_CR_DBGS_MASK) | DMA_CR_DBGS(bEnable);
}

/**
 * @brief Get the DMA error status
 *
 * @param pDma the base address of the DMA instance
 * @return uint32_t the DMA error status
 */
LOCAL_INLINE uint32_t DMA_HWA_GetErrorStatus(const DMA_Type *const pDma)
{
    return pDma->ES;
}

/**
 * @brief Get whether there is error occured on the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true there is error on the specified channel
 * @return false there is no error on the specified channel
 */
LOCAL_INLINE bool DMA_HWA_GetChannelErrorFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal = (pDma->ERR & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the channel error status, each bit represents a channel
 *
 * @param pDma the base address of the DMA instance
 * @return uint16_t the channel error status
 */
LOCAL_INLINE uint16_t DMA_HWA_GetAllChannelErrorFlag(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = pDma->ERR;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Get whether error interrupt is enabled on the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true error interrupt is enabled on the specified channel
 * @return false error interrupt is disabled on the specified channel
 */
LOCAL_INLINE bool DMA_HWA_GetChannelErrorInterruptEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal = (pDma->EEI & (1U << u8Channel)) >> u8Channel;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get channel error interrupt enable status
 *
 * @param pDma the base address of the DMA instance
 * @return uint16_t the channel error interrupt enable status
 */
LOCAL_INLINE uint16_t DMA_HWA_GetAllChannelErrorInterruptEnableFlag(const DMA_Type *const pDma)
{
    uint32_t u32TmpVal = pDma->EEI;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Enable error interrupt for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_EnableChannelErrorInterrupt(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->SEEI = DMA_SEEI_SEEI(u8Channel);
}

/**
 * @brief Enable error interrupt for all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_EnableAllChannelErrorInterrupt(DMA_Type *const pDma)
{
    pDma->SEEI = DMA_SEEI_SAEE_MASK;
}

/**
 * @brief Disable error interrupt for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_DisableChannelErrorInterrupt(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->CEEI = DMA_CEEI_CEEI(u8Channel);
}

/**
 * @brief Disable error interrupt for all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_DisableAllChannelErrorInterrupt(DMA_Type *const pDma)
{
    pDma->CEEI = DMA_CEEI_CAEE_MASK;
}

/**
 * @brief Enable channel request for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_EnableChannelRequest(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->SERQ = DMA_SERQ_SERQ(u8Channel);
}

/**
 * @brief Enable channel request for all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_EnableAllChannelRequest(DMA_Type *const pDma)
{
    pDma->SERQ = DMA_SERQ_SAER_MASK;
}

/**
 * @brief Disable channel request for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_DisableChannelRequest(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->CERQ = DMA_CERQ_CERQ(u8Channel);
}

/**
 * @brief Disable channel request for all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_DisableAllChannelRequest(DMA_Type *const pDma)
{
    pDma->CERQ = DMA_CERQ_CAER_MASK;
}

/**
 * @brief Clear DONE bit for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_ClearChannelDoneStatus(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->CDNE = DMA_CDNE_CDNE(u8Channel);
}

/**
 * @brief Clear DONE bit for the all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_ClearAllChannelDoneStatus(DMA_Type *const pDma)
{
    pDma->CDNE = DMA_CDNE_CADN_MASK;
}

/**
 * @brief Clear ERR bit for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_ClearChannelErrorFlag(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->CERR = DMA_CERR_CERR(u8Channel);
}

/**
 * @brief Clear ERR bit for the all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_ClearAllChannelErrorFlag(DMA_Type *const pDma)
{
    pDma->CERR = DMA_CERR_CAEI_MASK;
}

/**
 * @brief Clear interrupt flag for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_ClearChannelInterruptFlag(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->CINT = DMA_CINT_CINT(u8Channel);
}

/**
 * @brief Clear interrupt flag for the all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_ClearAllChannelInterruptFlag(DMA_Type *const pDma)
{
    pDma->CINT = DMA_CINT_CAIR_MASK;
}

/**
 * @brief Set start for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_SetChannelStart(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->SSRT = DMA_SSRT_SSRT(u8Channel);
}

/**
 * @brief Set start for the all channels
 *
 * @param pDma the base address of the DMA instance
 */
LOCAL_INLINE void DMA_HWA_SetAllChannelStart(DMA_Type *const pDma)
{
    pDma->SSRT = DMA_SSRT_SAST_MASK;
}

/**
 * @brief Get whether source unalign modulo is enabled for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE bool DMA_HWA_GetSrcUnalignModuloEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal = (pDma->DUME & (DMA_DUME_SUME0_MASK << (2U * u8Channel))) >>
                         (DMA_DUME_SUME0_SHIFT + 2U * u8Channel);
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get whether destination unalign modulo is enabled for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE bool DMA_HWA_GetDestUnalignModuloEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal = (pDma->DUME & (DMA_DUME_DUME0_MASK << (2U * u8Channel))) >>
                         (DMA_DUME_DUME0_SHIFT + 2U * u8Channel);
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get whether to enable unalign modulo for the specified channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param bEnableSrcModulo whether source unalign modulo is to be enabled
 * @param bEnableDestModulo whether destination unalign modulo is to be enabled
 */
LOCAL_INLINE void DMA_HWA_SetUnalignModuloEnableFlag(DMA_Type *const pDma, uint8_t u8Channel,
        bool bEnableSrcModulo, bool bEnableDestModulo)
{
    pDma->DUME = (pDma->DUME & ~((DMA_DUME_DUME0_MASK | DMA_DUME_SUME0_MASK) << (2U * u8Channel))) |
                 ((DMA_DUME_DUME0(bEnableDestModulo) | DMA_DUME_SUME0(bEnableSrcModulo)) << (2U * u8Channel));
}

/**
 * @brief Get the source unalign modulo of the index
 *
 * @param pDma the base address of the DMA instance
 * @param u8Selection the index of the unalign modulo
 * @return uint16_t the source unalign modulo
 */
LOCAL_INLINE uint16_t DMA_HWA_GetSrcUnalignModulo(const DMA_Type *const pDma, uint8_t u8Selection)
{
    uint32_t u32TmpVal = (pDma->DUMO[u8Selection] & DMA_DUMO0_SUMO_MASK) >> DMA_DUMO0_SUMO_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Get the destination unalign modulo of the index
 *
 * @param pDma the base address of the DMA instance
 * @param u8Selection the index of the unalign modulo
 * @return uint16_t the destination unalign modulo
 */
LOCAL_INLINE uint16_t DMA_HWA_GetDestUnalignModulo(const DMA_Type *const pDma, uint8_t u8Selection)
{
    uint32_t u32TmpVal = (pDma->DUMO[u8Selection] & DMA_DUMO0_DUMO_MASK) >> DMA_DUMO0_DUMO_SHIFT;
    return (uint16_t)u32TmpVal;
}

/**
 * @brief Set unalign modulo of the index
 *
 * @param pDma the base address of the DMA instance
 * @param u8Selection the index of the unalign modulo
 * @param u16SrcModulo the source unalign modulo
 * @param u16DestModulo the destination unalign modulo
 */
LOCAL_INLINE void DMA_HWA_SetUnalignModulo(DMA_Type *const pDma, uint8_t u8Selection,
                                           uint16_t u16SrcModulo, uint16_t u16DestModulo)
{
    pDma->DUMO[u8Selection] = DMA_DUMO0_SUMO(u16SrcModulo) | DMA_DUMO0_DUMO(u16DestModulo);
}

/**
 * @brief Get priority of the channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint8_t the priority of the channel
 */
LOCAL_INLINE uint8_t DMA_HWA_GetPriority(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint8_t u8TmpVal = pDma->DCHPRI[DMA_CH_TO_DCHPRI(u8Channel)];
    return u8TmpVal;
}

/**
 * @brief Set priority of the channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u8Priority the priority of the channel
 */
LOCAL_INLINE void DMA_HWA_SetPriority(DMA_Type *const pDma, uint8_t u8Channel, uint8_t u8Priority)
{
    pDma->DCHPRI[DMA_CH_TO_DCHPRI(u8Channel)] = u8Priority;
}

/**
 * @brief Get the source address of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint32_t the source address of the DMA channel
 */
LOCAL_INLINE uint32_t DMA_HWA_GetSrcAddr(const DMA_Type *const pDma, uint8_t u8Channel)
{
    return pDma->CFG[u8Channel].SADDR;
}

/**
 * @brief Set the source address of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u32SrcAddr the source address of the DMA channel
 */
LOCAL_INLINE void DMA_HWA_SetSrcAddr(DMA_Type *const pDma, uint8_t u8Channel, uint32_t u32SrcAddr)
{
    pDma->CFG[u8Channel].SADDR = u32SrcAddr;
}

/**
 * @brief Get the destination address of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint32_t the destination address of the DMA channel
 */
LOCAL_INLINE uint32_t DMA_HWA_GetDestAddr(const DMA_Type *const pDma, uint8_t u8Channel)
{
    return pDma->CFG[u8Channel].DADDR;
}

/**
 * @brief Set the destination address of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u32DestAddr the destination address of the DMA channel
 */
LOCAL_INLINE void DMA_HWA_SetDestAddr(DMA_Type *const pDma, uint8_t u8Channel, uint32_t u32DestAddr)
{
    pDma->CFG[u8Channel].DADDR = u32DestAddr;
}

/**
 * @brief Get source data offset of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return int16_t the source data offset
 */
LOCAL_INLINE int16_t DMA_HWA_GetSrcOffset(const DMA_Type *const pDma, uint8_t u8Channel)
{
    return (int16_t)pDma->CFG[u8Channel].SOFF;
}

/**
 * @brief Set source data offset of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param s16Offset the source data offset
 */
LOCAL_INLINE void DMA_HWA_SetSrcOffset(DMA_Type *const pDma, uint8_t u8Channel, int16_t s16Offset)
{
    pDma->CFG[u8Channel].SOFF = (uint16_t)s16Offset;
}

/**
 * @brief Get destination data offset of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return int16_t the destination data offset
 */
LOCAL_INLINE int16_t DMA_HWA_GetDestOffset(const DMA_Type *const pDma, uint8_t u8Channel)
{
    return (int16_t)pDma->CFG[u8Channel].DOFF;
}

/**
 * @brief Set destination data offset of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param s16Offset the destination data offset
 */
LOCAL_INLINE void DMA_HWA_SetDestOffset(DMA_Type *const pDma, uint8_t u8Channel, int16_t s16Offset)
{
    pDma->CFG[u8Channel].DOFF = (uint16_t)s16Offset;
}

/**
 * @brief Get the source data size of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return DMA_TransferSizeType the source data size of the DMA channel
 */
LOCAL_INLINE DMA_TransferSizeType DMA_HWA_GetSrcDataSize(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].ATTR & DMA_CFG_ATTR_SSIZE_MASK) >> DMA_CFG_ATTR_SSIZE_SHIFT;
    return (DMA_TransferSizeType)u16TmpVal;
}

/**
 * @brief Set the source data size of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param eDataSize the source data size of the DMA channel
 */
LOCAL_INLINE void DMA_HWA_SetSrcDataSize(DMA_Type *const pDma, uint8_t u8Channel, DMA_TransferSizeType eDataSize)
{
    pDma->CFG[u8Channel].ATTR = (uint16_t)((pDma->CFG[u8Channel].ATTR & ~DMA_CFG_ATTR_SSIZE_MASK) | DMA_CFG_ATTR_SSIZE(eDataSize));
}

/**
 * @brief Get the destination data size of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return DMA_TransferSizeType the destination data size of the DMA channel
 */
LOCAL_INLINE DMA_TransferSizeType DMA_HWA_GetDestDataSize(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].ATTR & DMA_CFG_ATTR_DSIZE_MASK) >> DMA_CFG_ATTR_DSIZE_SHIFT;
    return (DMA_TransferSizeType)u16TmpVal;
}

/**
 * @brief Set the destination data size of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param eDataSize the destination data size of the DMA channel
 */
LOCAL_INLINE void DMA_HWA_SetDestDataSize(DMA_Type *const pDma, uint8_t u8Channel, DMA_TransferSizeType eDataSize)
{
    pDma->CFG[u8Channel].ATTR = (uint16_t)((pDma->CFG[u8Channel].ATTR & ~DMA_CFG_ATTR_DSIZE_MASK) | DMA_CFG_ATTR_DSIZE(eDataSize));
}

/**
 * @brief Get the source address aligned modulo of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint8_t the source address aligned modulo
 */
LOCAL_INLINE uint8_t DMA_HWA_GetSrcModulo(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].ATTR & DMA_CFG_ATTR_SMOD_MASK) >> DMA_CFG_ATTR_SMOD_SHIFT;
    return (uint8_t)u16TmpVal;
}

/**
 * @brief Set the source address aligned modulo of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u8SrcModulo the source address aligned modulo
 */
LOCAL_INLINE void DMA_HWA_SetSrcModulo(DMA_Type *const pDma, uint8_t u8Channel, uint8_t u8SrcModulo)
{
    pDma->CFG[u8Channel].ATTR = (uint16_t)((pDma->CFG[u8Channel].ATTR & ~DMA_CFG_ATTR_SMOD_MASK) | DMA_CFG_ATTR_SMOD(u8SrcModulo));
}

/**
 * @brief Get the destination address aligned modulo of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint8_t the destination address aligned modulo
 */
LOCAL_INLINE uint8_t DMA_HWA_GetDestModulo(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].ATTR & DMA_CFG_ATTR_DMOD_MASK) >> DMA_CFG_ATTR_DMOD_SHIFT;
    return (uint8_t)u16TmpVal;
}

/**
 * @brief Set the destination address aligned modulo of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u8DestModulo the destination address aligned modulo
 */
LOCAL_INLINE void DMA_HWA_SetDestModulo(DMA_Type *const pDma, uint8_t u8Channel, uint8_t u8DestModulo)
{
    pDma->CFG[u8Channel].ATTR = (uint16_t)((pDma->CFG[u8Channel].ATTR & ~DMA_CFG_ATTR_DMOD_MASK) | DMA_CFG_ATTR_DMOD(u8DestModulo));
}

/**
 * @brief Get the address adjustment applied to the source address after major loop finished
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return int32_t the address adjustment applied to the source address after major loop finished
 */
LOCAL_INLINE int32_t DMA_HWA_GetSrcLastAddrAdjustment(const DMA_Type *const pDma, uint8_t u8Channel)
{
    return (int32_t)pDma->CFG[u8Channel].SLAST;
}

/**
 * @brief Set the address adjustment applied to the source address after major loop finished
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param s32LastAdj the address adjustment applied to the source address after major loop finished
 */
LOCAL_INLINE void DMA_HWA_SetSrcLastAddrAdjustment(DMA_Type *const pDma, uint8_t u8Channel, int32_t s32LastAdj)
{
    pDma->CFG[u8Channel].SLAST = (uint32_t)s32LastAdj;
}

/**
 * @brief Get the address adjustment applied to the destination address after major loop finished
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return int32_t the address adjustment applied to the destination address after major loop finished
 */
LOCAL_INLINE int32_t DMA_HWA_GetDestLastAddrAdjustment(const DMA_Type *const pDma, uint8_t u8Channel)
{
    return (int32_t)pDma->CFG[u8Channel].DLAST;
}

/**
 * @brief Set the address adjustment applied to the destination address after major loop finished
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param s32LastAdj the address adjustment applied to the destination address after major loop finished
 */
LOCAL_INLINE void DMA_HWA_SetDestLastAddrAdjustment(DMA_Type *const pDma, uint8_t u8Channel, int32_t s32LastAdj)
{
    pDma->CFG[u8Channel].DLAST = (uint32_t)s32LastAdj;
}

/**
 * @brief Get whether source address inner loop offset is enabled
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true source address inner loop offset is enabled
 * @return false source address inner loop offset is disabled
 */
LOCAL_INLINE bool DMA_HWA_GetInnerLoopSrcOffsetEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal;
    if (DMA_HWA_GetInnerLoopMappingEnableFlag(pDma) == false)
    {
        u32TmpVal = 0U;
    }
    else
    {
        u32TmpVal = (pDma->CFG[u8Channel].NBYTES.ILOFFNO & DMA_CFG_NBYTES_ILOFFNO_SILOE_MASK) >>
                    DMA_CFG_NBYTES_ILOFFNO_SILOE_SHIFT;
    }
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get whether destination address inner loop offset is enabled
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true destination address inner loop offset is enabled
 * @return false destination address inner loop offset is disabled
 */
LOCAL_INLINE bool DMA_HWA_GetInnerLoopDestOffsetEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal;
    if (DMA_HWA_GetInnerLoopMappingEnableFlag(pDma) == false)
    {
        u32TmpVal = 0U;
    }
    else
    {
        u32TmpVal = (pDma->CFG[u8Channel].NBYTES.ILOFFNO & DMA_CFG_NBYTES_ILOFFNO_DILOE_MASK) >>
                    DMA_CFG_NBYTES_ILOFFNO_DILOE_SHIFT;
    }
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the inner loop offset of the DMA channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return int32_t the signed inner loop offset
 */
LOCAL_INLINE int32_t DMA_HWA_GetInnerLoopOffset(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal;
    if (DMA_HWA_GetInnerLoopMappingEnableFlag(pDma) == false)
    {
        u32TmpVal = 0U;
    }
    else
    {
        bool bDmaInnerLoopSrcOffsetEnable = DMA_HWA_GetInnerLoopSrcOffsetEnableFlag(pDma, u8Channel);
        bool bDmaInnerLoopDestOffsetEnable = DMA_HWA_GetInnerLoopDestOffsetEnableFlag(pDma, u8Channel);
        if ((bDmaInnerLoopSrcOffsetEnable == false) && (bDmaInnerLoopDestOffsetEnable == false))
        {
            u32TmpVal = 0U;
        }
        else
        {
            u32TmpVal = (pDma->CFG[u8Channel].NBYTES.ILOFFYES & DMA_CFG_NBYTES_ILOFFYES_ILOFF_MASK) >>
                        DMA_CFG_NBYTES_ILOFFYES_ILOFF_SHIFT;
        }
    }
    /* Convert sign-extended 20bit value to signed 32bit value */
    if ((u32TmpVal & (1U << 19U)) != 0U)
    {
        u32TmpVal |= 0xFFF00000U;
    }
    return (int32_t)u32TmpVal;
}

/**
 * @brief Get the transfer data size of the inner loop
 * @note if inner loop mapping is disabled, the range is 0~2^31-1
 * if inner loop mapping is enabled and inner loop offset is disabled, the range is 0~2^30-1
 * if inner loop mapping is enabled and inner loop offset is enabled, the range is 0~2^10-1
 * 0 means 2^32
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint32_t the transfer data size of the inner loop
 */
LOCAL_INLINE uint32_t DMA_HWA_GetInnerLoopSize(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint32_t u32TmpVal;
    if (DMA_HWA_GetInnerLoopMappingEnableFlag(pDma) == false)
    {
        u32TmpVal = pDma->CFG[u8Channel].NBYTES.ILNO;
    }
    else
    {
        bool bDmaInnerLoopSrcOffsetEnable = DMA_HWA_GetInnerLoopSrcOffsetEnableFlag(pDma, u8Channel);
        bool bDmaInnerLoopDestOffsetEnable = DMA_HWA_GetInnerLoopDestOffsetEnableFlag(pDma, u8Channel);
        if ((bDmaInnerLoopSrcOffsetEnable == false) && (bDmaInnerLoopDestOffsetEnable == false))
        {
            u32TmpVal = (pDma->CFG[u8Channel].NBYTES.ILOFFNO & DMA_CFG_NBYTES_ILOFFNO_NBYTES_MASK) >>
                        DMA_CFG_NBYTES_ILOFFNO_NBYTES_SHIFT;
        }
        else
        {
            u32TmpVal = (pDma->CFG[u8Channel].NBYTES.ILOFFYES & DMA_CFG_NBYTES_ILOFFYES_NBYTES_MASK) >>
                        DMA_CFG_NBYTES_ILOFFYES_NBYTES_SHIFT;
        }
    }
    return u32TmpVal;
}

/**
 * @brief Set the inner loop offset of the DMA channel
 *
 * @note the inner loop offset can only be enabled when inner loop mapping is enabled
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param bEnableSrcOffset whether to enable source address inner loop offset
 * @param bEnableDestOffset whether to enable destination address inner loop offset
 * @param s32Offset the inner loop offset
 * @return true the inner loop mapping is enabled, the setting is applied
 * @return false the inner loop mapping is disabled, the setting is ignored
 */
LOCAL_INLINE bool DMA_HWA_SetInnerLoopOffset(DMA_Type *const pDma, uint8_t u8Channel, bool bEnableSrcOffset,
                                             bool bEnableDestOffset, int32_t s32Offset)
{
    bool bRet;
    if (DMA_HWA_GetInnerLoopMappingEnableFlag(pDma) == false)
    {
        bRet = false;
    }
    else
    {
        if ((bEnableSrcOffset == false) && (bEnableDestOffset == false))
        {
            bool bDmaInnerLoopSrcOffsetEnable = DMA_HWA_GetInnerLoopSrcOffsetEnableFlag(pDma, u8Channel);
            bool bDmaInnerLoopDestOffsetEnable = DMA_HWA_GetInnerLoopDestOffsetEnableFlag(pDma, u8Channel);
            /* If inner loop offset is enabled, to disable inner loop offset, we should clear the inner
               loop offset enable bit and meanwhile the inner loop offset bits */
            if ((bDmaInnerLoopSrcOffsetEnable == true) || (bDmaInnerLoopDestOffsetEnable == true))
            {
                pDma->CFG[u8Channel].NBYTES.ILOFFNO &= ~(DMA_CFG_NBYTES_ILOFFNO_SILOE_MASK | DMA_CFG_NBYTES_ILOFFNO_DILOE_MASK |
                                                         DMA_CFG_NBYTES_ILOFFYES_ILOFF_MASK);
            }
        }
        else
        {
            pDma->CFG[u8Channel].NBYTES.ILOFFYES = (pDma->CFG[u8Channel].NBYTES.ILOFFYES & ~(DMA_CFG_NBYTES_ILOFFYES_SILOE_MASK |
                                                    DMA_CFG_NBYTES_ILOFFYES_DILOE_MASK | DMA_CFG_NBYTES_ILOFFYES_ILOFF_MASK)) |
                                                   DMA_CFG_NBYTES_ILOFFYES_SILOE(bEnableSrcOffset) |
                                                   DMA_CFG_NBYTES_ILOFFYES_DILOE(bEnableDestOffset) |
                                                   DMA_CFG_NBYTES_ILOFFYES_ILOFF(s32Offset);
        }
        bRet = true;
    }
    return bRet;
}

/**
 * @brief Set the transfer data size of the inner loop
 * @note if inner loop mapping is disabled, the range is 0~2^31-1
 * if inner loop mapping is enabled and inner loop offset is disabled, the range is 0~2^30-1
 * if inner loop mapping is enabled and inner loop offset is enabled, the range is 0~2^10-1
 * 0 means 2^32
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u32Size the transfer data size of the inner loop
 */
LOCAL_INLINE void DMA_HWA_SetInnerLoopSize(DMA_Type *const pDma, uint8_t u8Channel, uint32_t u32Size)
{
    if (DMA_HWA_GetInnerLoopMappingEnableFlag(pDma) == false)
    {
        pDma->CFG[u8Channel].NBYTES.ILNO = DMA_CFG_NBYTES_ILNO_NBYTES(u32Size);
    }
    else
    {
        bool bDmaInnerLoopSrcOffsetEnable = DMA_HWA_GetInnerLoopSrcOffsetEnableFlag(pDma, u8Channel);
        bool bDmaInnerLoopDestOffsetEnable = DMA_HWA_GetInnerLoopDestOffsetEnableFlag(pDma, u8Channel);
        if ((bDmaInnerLoopSrcOffsetEnable == false) && (bDmaInnerLoopDestOffsetEnable == false))
        {
            pDma->CFG[u8Channel].NBYTES.ILOFFNO = (pDma->CFG[u8Channel].NBYTES.ILOFFNO & ~DMA_CFG_NBYTES_ILOFFNO_NBYTES_MASK) |
                                                  DMA_CFG_NBYTES_ILOFFNO_NBYTES(u32Size);
        }
        else
        {
            pDma->CFG[u8Channel].NBYTES.ILOFFYES = (pDma->CFG[u8Channel].NBYTES.ILOFFYES & ~DMA_CFG_NBYTES_ILOFFYES_NBYTES_MASK) |
                                                   DMA_CFG_NBYTES_ILOFFYES_NBYTES(u32Size);
        }
    }
}

/**
 * @brief Get whether current channel to channel trig is enabled when inner loop complete
 * @note this field shall always be same with the beginning channel to channel trig enable flag
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true channel to channel trig is enabled when inner loop complete
 * @return false channel to channel trig is disabled when inner loop complete
 */
LOCAL_INLINE bool DMA_HWA_GetCurrentChannelToChannelTrigEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CLC.CHTRGENNO & DMA_CFG_CLC_CHTRGENNO_CHTRGEN_MASK) >>
                         DMA_CFG_CLC_CHTRGENNO_CHTRGEN_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the target channel when current channel to channel trig is enabled
 * @note this field shall always be same with the beginning traget channel trig field
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint8_t the target channel
 */
LOCAL_INLINE uint8_t DMA_HWA_GetCurrentChannelToChannelTrigChannel(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal;
    if (DMA_HWA_GetCurrentChannelToChannelTrigEnableFlag(pDma, u8Channel) == true)
    {
        u16TmpVal = (pDma->CFG[u8Channel].CLC.CHTRGENYES & DMA_CFG_CLC_CHTRGENYES_TRGCH_MASK) >>
                    DMA_CFG_CLC_CHTRGENYES_TRGCH_SHIFT;
    }
    else
    {
        u16TmpVal = 0U;
    }
    return (uint8_t)u16TmpVal;
}

/**
 * @brief Get the current loop count
 * The current loop count is the same as the beginning loop count initially, and it will decrement
 * each time a inner loop finishes
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint16_t the current loop count
 */
LOCAL_INLINE uint16_t DMA_HWA_GetCurrentLoopCount(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal;
    if (DMA_HWA_GetCurrentChannelToChannelTrigEnableFlag(pDma, u8Channel) == false)
    {
        u16TmpVal = (pDma->CFG[u8Channel].CLC.CHTRGENNO & DMA_CFG_CLC_CHTRGENNO_CLC_MASK) >> DMA_CFG_CLC_CHTRGENNO_CLC_SHIFT;
    }
    else
    {
        u16TmpVal = (pDma->CFG[u8Channel].CLC.CHTRGENYES & DMA_CFG_CLC_CHTRGENYES_CLC_MASK) >> DMA_CFG_CLC_CHTRGENYES_CLC_SHIFT;
    }
    return u16TmpVal;
}

/**
 * @brief Get whether beginning channel to channel trig is enabled when inner loop complete
 * @note this field shall always be same with the current channel to channel trig enable flag
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true channel to channel trig is enabled when inner loop complete
 * @return false channel to channel trig is disabled when inner loop complete
 */
LOCAL_INLINE bool DMA_HWA_GetBeginningChannelToChannelTrigEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].BLC.CHTRGENNO & DMA_CFG_BLC_CHTRGENNO_CHTRGEN_MASK) >>
                         DMA_CFG_BLC_CHTRGENNO_CHTRGEN_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the target channel when beginning channel to channel trig is enabled
 * @note this field shall always be same with the current traget channel trig field
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint8_t the target channel
 */
LOCAL_INLINE uint8_t DMA_HWA_GetBeginningChannelToChannelTrigChannel(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal;
    if (DMA_HWA_GetBeginningChannelToChannelTrigEnableFlag(pDma, u8Channel) == true)
    {
        u16TmpVal = (pDma->CFG[u8Channel].BLC.CHTRGENYES & DMA_CFG_BLC_CHTRGENYES_TRGCH_MASK) >>
                    DMA_CFG_BLC_CHTRGENYES_TRGCH_SHIFT;
    }
    else
    {
        u16TmpVal = 0U;
    }
    return (uint8_t)u16TmpVal;
}

/**
 * @brief Get the beginning loop count
 * This field specifies how many inner loops will be executed in a DMA transfer
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint16_t the beginning loop count
 */
LOCAL_INLINE uint16_t DMA_HWA_GetBeginningLoopCount(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal;
    if (DMA_HWA_GetBeginningChannelToChannelTrigEnableFlag(pDma, u8Channel) == false)
    {
        u16TmpVal = (pDma->CFG[u8Channel].BLC.CHTRGENNO & DMA_CFG_BLC_CHTRGENNO_BLC_MASK) >> DMA_CFG_BLC_CHTRGENNO_BLC_SHIFT;
    }
    else
    {
        u16TmpVal = (pDma->CFG[u8Channel].BLC.CHTRGENYES & DMA_CFG_BLC_CHTRGENYES_BLC_MASK) >> DMA_CFG_BLC_CHTRGENYES_BLC_SHIFT;
    }
    return u16TmpVal;
}

/**
 * @brief Set channel to channel trig when inner loop complete
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param bEnable whether to enbable channel to channel trig when inner loop complete
 * @param u8TrigChannel the target channel
 */
LOCAL_INLINE void DMA_HWA_SetChannelToChannelTrig(DMA_Type *const pDma, uint8_t u8Channel, bool bEnable,
                                                  uint8_t u8TrigChannel)
{
    if (bEnable == false)
    {
        pDma->CFG[u8Channel].CLC.CHTRGENNO &= (uint16_t)~(DMA_CFG_CLC_CHTRGENNO_CHTRGEN_MASK);
        pDma->CFG[u8Channel].BLC.CHTRGENNO &= (uint16_t)~(DMA_CFG_BLC_CHTRGENNO_CHTRGEN_MASK);
    }
    else
    {
        pDma->CFG[u8Channel].BLC.CHTRGENYES = (uint16_t)((pDma->CFG[u8Channel].BLC.CHTRGENYES &
                                               ~(DMA_CFG_BLC_CHTRGENYES_CHTRGEN_MASK | DMA_CFG_BLC_CHTRGENYES_TRGCH_MASK)) |
                                              DMA_CFG_BLC_CHTRGENYES_CHTRGEN(bEnable) | DMA_CFG_BLC_CHTRGENYES_TRGCH(u8TrigChannel));
        pDma->CFG[u8Channel].CLC.CHTRGENYES = (uint16_t)((pDma->CFG[u8Channel].CLC.CHTRGENYES &
                                               ~(DMA_CFG_CLC_CHTRGENYES_CHTRGEN_MASK | DMA_CFG_CLC_CHTRGENYES_TRGCH_MASK)) |
                                              DMA_CFG_CLC_CHTRGENYES_CHTRGEN(bEnable) | DMA_CFG_CLC_CHTRGENYES_TRGCH(u8TrigChannel));
    }
}

/**
 * @brief Set the loop count of the DMA transfer
 * This field specifies how many inner loops will be executed in a DMA transfer
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u16LoopCnt the inner loop count in a DMA transfer
 */
LOCAL_INLINE void DMA_HWA_SetLoopCount(DMA_Type *const pDma, uint8_t u8Channel, uint16_t u16LoopCnt)
{
    if (DMA_HWA_GetBeginningChannelToChannelTrigEnableFlag(pDma, u8Channel) == false)
    {
        pDma->CFG[u8Channel].BLC.CHTRGENNO = (uint16_t)((pDma->CFG[u8Channel].BLC.CHTRGENNO & ~DMA_CFG_BLC_CHTRGENNO_BLC_MASK) |
                                             DMA_CFG_BLC_CHTRGENNO_BLC(u16LoopCnt));
        pDma->CFG[u8Channel].CLC.CHTRGENNO = (uint16_t)((pDma->CFG[u8Channel].CLC.CHTRGENNO & ~DMA_CFG_CLC_CHTRGENNO_CLC_MASK) |
                                             DMA_CFG_CLC_CHTRGENNO_CLC(u16LoopCnt));
    }
    else
    {
        pDma->CFG[u8Channel].BLC.CHTRGENYES = (uint16_t)((pDma->CFG[u8Channel].BLC.CHTRGENYES & ~DMA_CFG_BLC_CHTRGENYES_BLC_MASK) |
                                              DMA_CFG_BLC_CHTRGENYES_BLC(u16LoopCnt));
        pDma->CFG[u8Channel].CLC.CHTRGENYES = (uint16_t)((pDma->CFG[u8Channel].CLC.CHTRGENYES & ~DMA_CFG_CLC_CHTRGENYES_CLC_MASK) |
                                              DMA_CFG_CLC_CHTRGENYES_CLC(u16LoopCnt));
    }
}

/**
 * @brief Get the unalign modulo index selection
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint8_t the unalign modulo index selection
 */
LOCAL_INLINE uint8_t DMA_HWA_GetUnalignModuloSel(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_UMS_MASK) >> DMA_CFG_CSR_UMS_SHIFT;
    return (uint8_t)u16TmpVal;
}

/**
 * @brief Set the unalign modulo index selection
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u8UnalignModuloSel the unalign modulo index selection
 */
LOCAL_INLINE void DMA_HWA_SetUnalignModuloSel(DMA_Type *const pDma, uint8_t u8Channel, uint8_t u8UnalignModuloSel)
{
    pDma->CFG[u8Channel].CSR = (uint16_t)((pDma->CFG[u8Channel].CSR & ~DMA_CFG_CSR_UMS_MASK) | DMA_CFG_CSR_UMS(u8UnalignModuloSel));
}

/**
 * @brief Get the target channel to trig when outer loop is completed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint8_t the target channel
 */
LOCAL_INLINE uint8_t DMA_HWA_GetOuterLoopTrigChannel(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_OTRGCH_MASK) >> DMA_CFG_CSR_OTRGCH_SHIFT;
    return (uint8_t)u16TmpVal;
}

/**
 * @brief Set the target channel to trig when outer loop is completed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u8TrigChannel the target channel
 */
LOCAL_INLINE void DMA_HWA_SetOuterLoopTrigChannel(DMA_Type *const pDma, uint8_t u8Channel, uint8_t u8TrigChannel)
{
    pDma->CFG[u8Channel].CSR = (uint16_t)((pDma->CFG[u8Channel].CSR & ~DMA_CFG_CSR_OTRGCH_MASK) | DMA_CFG_CSR_OTRGCH(u8TrigChannel));
}

/**
 * @brief Get whether the transfer is done on the selected channel
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true the transfer is done
 * @return false the transfer has not done
 */
LOCAL_INLINE bool DMA_HWA_GetChannelDoneStatus(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_DONE_MASK) >> DMA_CFG_CSR_DONE_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Get the active status of the DMA channel
 * This flag signals the channel is currently in execution. It is set when channel service begins,
 * and is cleared by the DMA as the inner loop completes or when any error condition is detected
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true the channel is in execution
 * @return false the channel is idle
 */
LOCAL_INLINE DMA_RunningStatusType DMA_HWA_GetChannelActiveStatus(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_ACTIVE_MASK) >> DMA_CFG_CSR_ACTIVE_SHIFT;
    return (DMA_RunningStatusType)u16TmpVal;
}

/**
 * @brief Get channel to channel trig is enabled when outer loop is completed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true the target channel will be trigged when outer loop is completed
 * @return false the channel to channel trig when outer loop is completed is disabled
 */
LOCAL_INLINE bool DMA_HWA_GetOuterLoopTrigEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_OCHTRGEN_MASK) >> DMA_CFG_CSR_OCHTRGEN_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable channel to channel trig when outer loop is completed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param bEnable whether to enable channel to channel trig when outer loop is completed
 */
LOCAL_INLINE void DMA_HWA_SetOuterLoopTrigEnableFlag(DMA_Type *const pDma, uint8_t u8Channel, bool bEnable)
{
    pDma->CFG[u8Channel].CSR = (uint16_t)((pDma->CFG[u8Channel].CSR & ~DMA_CFG_CSR_OCHTRGEN_MASK) | DMA_CFG_CSR_OCHTRGEN(bEnable));
}

/**
 * @brief Get whether DMA request will be disabled automatically when outer loop is completed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true DMA request will be disabled automatically when outer loop is completed
 * @return false DMA request will not be cleared when outer loop is completed
 */
LOCAL_INLINE bool DMA_HWA_GetAutoDisableReuqestEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_DREQ_MASK) >> DMA_CFG_CSR_DREQ_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to disable DMA request automatically when outer loop is completed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param bEnable whether to disable DMA request automatically when outer loop is completed
 */
LOCAL_INLINE void DMA_HWA_SetAutoDisableReuqestEnableFlag(DMA_Type *const pDma, uint8_t u8Channel, bool bEnable)
{
    pDma->CFG[u8Channel].CSR = (uint16_t)((pDma->CFG[u8Channel].CSR & ~DMA_CFG_CSR_DREQ_MASK) | DMA_CFG_CSR_DREQ(bEnable));
}

/**
 * @brief Get whether DMA interrupt wiil be generated when the outer loop is half done
 * @note When outer loop count is 1, do not enable half complete interrupt
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true DMA will generate interrupt when outer loop is half done
 * @return true DMA will not generate interrupt when outer loop is half done
 */
LOCAL_INLINE bool DMA_HWA_GetHalfCompleteInterruptEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_INTHALF_MASK) >> DMA_CFG_CSR_INTHALF_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable DMA interrupt when the outer loop is half done
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param bEnable whether to enable DMA interrupt when the outer loop is half done
 */
LOCAL_INLINE void DMA_HWA_SetHalfCompleteInterruptEnableFlag(DMA_Type *const pDma, uint8_t u8Channel, bool bEnable)
{
    pDma->CFG[u8Channel].CSR = (uint16_t)((pDma->CFG[u8Channel].CSR & ~DMA_CFG_CSR_INTHALF_MASK) | DMA_CFG_CSR_INTHALF(bEnable));
}

/**
 * @brief Get whether DMA interrupt is enabled when DMA transfer is completed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true DMA will generate interrupt when outer loop is completed
 * @return false DMA will not generate interrupt when outer loop is completed
 */
LOCAL_INLINE bool DMA_HWA_GetTransferCompleteInterruptEnableFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_INTOUTER_MASK) >> DMA_CFG_CSR_INTOUTER_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable DMA transfer complete interrupt
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_EnableTransferCompleteInterrupt(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->CFG[u8Channel].CSR |= DMA_CFG_CSR_INTOUTER_MASK;
}

/**
 * @brief Disable DMA transfer complete interrupt
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 */
LOCAL_INLINE void DMA_HWA_DisableTransferCompleteInterrupt(DMA_Type *const pDma, uint8_t u8Channel)
{
    pDma->CFG[u8Channel].CSR &= (uint16_t)~DMA_CFG_CSR_INTOUTER_MASK;
}

/**
 * @brief Get whether the DMA start is requested but has not been executed
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return true the DMA start is requested but has not been executed
 * @return false the DMA start is not requested or it has started execution
 */
LOCAL_INLINE bool DMA_HWA_GetWaitStartFlag(const DMA_Type *const pDma, uint8_t u8Channel)
{
    uint16_t u16TmpVal = (pDma->CFG[u8Channel].CSR & DMA_CFG_CSR_START_MASK) >> DMA_CFG_CSR_START_SHIFT;
    return (bool)((u16TmpVal != 0U) ? true : false);
}

/**
 * @brief Get DMA channel control and status
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @return uint16_t control and status of the selected channel
 */
LOCAL_INLINE uint16_t DMA_HWA_GetChannelControlStatus(const DMA_Type *const pDma, uint8_t u8Channel)
{
    return pDma->CFG[u8Channel].CSR;
}

/**
 * @brief Set DMA channel control and status
 *
 * @param pDma the base address of the DMA instance
 * @param u8Channel the selected channel
 * @param u16Setting control settings of the selected channel
 */
LOCAL_INLINE void DMA_HWA_SetChannelControlStatus(DMA_Type *const pDma, uint8_t u8Channel, uint16_t u16Setting)
{
    pDma->CFG[u8Channel].CSR = u16Setting;
}

/** @}*/

#endif

#endif /* _HWA_DMA_H_ */
