/**
 * @file module_driver_dma.c
 * @author Flagchip099
 * @brief DMA driver source code
 * @version 2.0.0
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   1.0.0       2022-04-20    Flagchip030   N/A          First version for FC4150
   *   2.0.0       2024-08-23    Flagchip099   N/A          Update for skd2.0
   ******************************************************************************** */

#include "module_driver_dma.h"

#if DMA_INSTANCE_COUNT > 0U


#ifndef DMA_DEV_ERROR_REPORT
    #define DMA_DEV_ERROR_REPORT   STD_OFF
#endif

#if DMA_DEV_ERROR_REPORT == STD_ON
    #define DMA_ReportDevError(func, error) ReportDevError(DMA_MODULE_ID, func, error)
#endif

/**
 * @brief Get the first unused DUMO register index
 *
 * @param [out] pDumoIndex the DUMO register index
 * @return DMA_StatusType whether there is unused DUMO index
 * @return DMA_STATUS_SUCCESS the DUMO register index is successfully get
 * @return DMA_STATUS_NO_RESOURCE all DUMO registers are already occupied
 */
static inline DMA_StatusType DMA_GetDumoIndex(DMA_HandleType *pDmaHandle, uint8_t *pDumoIndex);

/**
 * @brief Check whether the value is power of 2 and return the ceil value of the log2(u32Value)
 *
 * @param [in] u32Value the value to check
 * @param [out] u8Log2 the ceil value of log2(u32Value)
 * @return true the u32Value is power of 2
 * @return false the u32Value is not power of 2
 */
static bool DMA_IsPowerOf2(uint32_t u32Value, uint8_t *u8Log2);

/**
 * @brief Reset the DMAMUX config values
 *
 */
static inline void Dmamux_Reset(void);

/**
 * @brief Get the data offset value of the selected increment mode and data size
 *
 * @param eIncMode the selected increment mode
 * @param eDataSize the selected data size
 * @return int16_t the calculated data offset
 */
static inline uint16_t DMA_GetDataOffset(DMA_IncrementModeType eIncMode,
                                         DMA_TransferSizeType eDataSize);

/**
 * @brief Init the channel interrupt
 *
 * @param pChnCfg the selected DMA channel config parameters
 * @return void
 */

static inline void DMA_InitChannelInterrupt(DMA_HandleType *pDmaHandle, const DMA_ChannelCfgType *const pChnCfg);

/**
 * @brief Gets a free DUMO index for DMA operations.
 *
 * This function iterates through the DUMO indices in the DMA handle structure to find an unused one.
 *
 * @param pDmaHandle Pointer to the DMA handle structure containing DMA configuration and status information.
 * @param pDumoIndex Pointer to a uint8_t variable where the found free DUMO index will be stored.
 *
 * @return DMA_StatusType The status code indicating the result of the function:
 *         - DMA_STATUS_ERROR: An error occurred.
 *         - DMA_STATUS_SUCCESS: A free DUMO was successfully found.
 *         - DMA_STATUS_NO_RESOURCE: No available DUMO resources.
 */
static inline DMA_StatusType DMA_GetDumoIndex(DMA_HandleType *pDmaHandle, uint8_t *pDumoIndex)
{
    DMA_StatusType ret = DMA_STATUS_ERROR;
    for (*pDumoIndex = 0U; *pDumoIndex < DMA_DUMO_COUNT; (*pDumoIndex)++)
    {
        if (pDmaHandle->tSettings.pInstance->tStatus.u8DmaDumoUsedStatus[*pDumoIndex] == DMA_CHANNEL_INVALID)
        {
            ret = DMA_STATUS_SUCCESS;
            break;
        }
    }
    if (*pDumoIndex == DMA_DUMO_COUNT)
    {
        ret = DMA_STATUS_NO_RESOURCE;
    }
    return ret;
}

/**
 * @brief Checks if a given value is a power of two.
 *
 * This function determines whether the provided 32-bit unsigned integer is a power of two.
 * If it is, the function also calculates the exponent such that 2 raised to this exponent equals the input value.
 *
 * @param u32Value The 32-bit unsigned integer value to check.
 * @param u8Log2 Pointer to a uint8_t variable where the calculated exponent will be stored if the value is a power of two.
 *
 * @return bool Returns true if the value is a power of two, false otherwise.
 *
 */
static bool DMA_IsPowerOf2(uint32_t u32Value, uint8_t *u8Log2)
{
    bool ret = (bool)false;
    *u8Log2 = 0U;
    while (u32Value > (1UL << *u8Log2))
    {
        (*u8Log2)++;
    }
    if ((u32Value & ((1UL << *u8Log2) - 1U)) == 0U)
    {
        ret = (bool)true;
    }
    return ret;
}

/**
 * @brief Calculates the data offset based on the increment mode and transfer size.
 *
 * This function computes the data offset required for DMA transfers according to the specified increment mode and data size.
 * The data offset is used to adjust the source or destination address in each DMA transfer cycle.
 *
 * @param eIncMode The increment mode of the DMA transfer (DMA_INCREMENT_DISABLE, DMA_INCREMENT_DATA_SIZE, DMA_INCREMENT_DATA_SIZE_4BYTE_ALIGNED).
 * @param eDataSize The size of each data element being transferred (DMA_TRANSFER_SIZE_1B, DMA_TRANSFER_SIZE_2B, DMA_TRANSFER_SIZE_4B, DMA_TRANSFER_SIZE_16B, DMA_TRANSFER_SIZE_32B).
 *
 * @return uint16_t The calculated data offset in bytes.
 */
static inline uint16_t DMA_GetDataOffset(DMA_IncrementModeType eIncMode,
                                         DMA_TransferSizeType eDataSize)
{
    uint16_t u16DataOffset = 0U;
    switch (eIncMode)
    {
        case DMA_INCREMENT_DISABLE:
        {
            u16DataOffset = 0U;
        }
        break;

        case DMA_INCREMENT_DATA_SIZE:
        {
            u16DataOffset = (uint16_t)(1UL << ((uint8_t)eDataSize));
        }
        break;

        case DMA_INCREMENT_DATA_SIZE_4BYTE_ALIGNED:
        {
            switch (eDataSize)
            {
                case DMA_TRANSFER_SIZE_1B:
                case DMA_TRANSFER_SIZE_2B:
                case DMA_TRANSFER_SIZE_4B:
                    u16DataOffset = 4U;
                    break;

                case DMA_TRANSFER_SIZE_16B:
                    u16DataOffset = 16U;
                    break;

                case DMA_TRANSFER_SIZE_32B:
                    u16DataOffset = 32U;
                    break;

                default:
                    break;
            }
        }
        break;

        default:
            break;
    }
    return u16DataOffset;
}

/**
 * @brief Processes DMA error interrupts by clearing flags and invoking error callbacks.
 *
 * This function iterates through all DMA channels and checks for error flags. If an error flag is set,
 * it clears the flag and invokes the associated error callback if one is registered.
 *
 * @param pDmaInstanceHandle Pointer to the DMA instance handle structure containing DMA settings and callbacks.
 */
void DMA_ProcessErrorInterrupt(DMA_InstanceHandleType *pDmaInstanceHandle)
{
    DMA_Type *const pDma = DMA;
    uint8_t u8Channel;
    for (u8Channel = 0U; u8Channel < DMA_CFG_COUNT; u8Channel++)
    {
        if (DMA_HWA_GetChannelErrorFlag(pDma, u8Channel) == true)
        {
            DMA_HWA_ClearChannelErrorFlag(pDma, u8Channel);
            if (pDmaInstanceHandle->tSettings.pTransferErrorCallback[u8Channel] != NULL)
            {
                pDmaInstanceHandle->tSettings.pTransferErrorCallback[u8Channel](pDmaInstanceHandle->tSettings.errdata[u8Channel]);
            }
        }
    }
}

/**
 * @brief DMA transfer complete interrupt service routine.
 *
 * This function is called when a DMA transfer completes. It clears the DMA channel interrupt flag and invokes
 * the transfer complete callback if one is registered.
 *
 * @param pDmaHandle Pointer to the DMA handle structure containing DMA settings and callbacks.
 */
void DMA_Transfer_Complete_IRQHandler(DMA_HandleType *pDmaHandle)
{
    DMA_Type *const pDma = DMA;
    DMA_HWA_ClearChannelInterruptFlag(pDma, pDmaHandle->tSettings.u8Channel);
    if (pDmaHandle->tSettings.callback.pTransferCompleteCallback != NULL)
    {
        pDmaHandle->tSettings.callback.pTransferCompleteCallback(pDmaHandle->tSettings.callback.completedata);
    }
}

/**
 * @brief Resets the DMAMUX configuration.
 *
 * This function resets the DMAMUX by disabling all request sources and clearing all periodic trigger flags.
 *
 * @note This function uses the DMAMUX hardware abstraction layer (HWA) functions to interact with the DMAMUX hardware.
 */
static inline void Dmamux_Reset(void)
{
    DMAMUX_Type *const pDmamux = DMAMUX;
    uint8_t u8Index;
    for (u8Index = 0U; u8Index < DMAMUX_CHCFG_COUNT; u8Index++)
    {
        DMAMUX_HWA_SetRequestSource(pDmamux, u8Index, false, DMA_REQ_DISABLED);
        DMAMUX_HWA_SetPeriodicTrigFlag(pDmamux, u8Index, false);
    }
}

/**
 * @brief Initializes the DMA instance with the specified configuration.
 *
 * This function initializes a DMA instance using the provided configuration parameters. It performs basic parameter checks
 * and sets up the DMA hardware according to the initialization settings.
 *
 * @param pDmaInstanceHandle Pointer to the DMA instance handle structure.
 * @param pInitCfg Pointer to the DMA initialization configuration structure.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 */
void DMA_Init(DMA_InstanceHandleType *pDmaInstanceHandle, const DMA_InitType *const pInitCfg)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pDmaInstanceHandle->tSettings.u8Instance >= DMA_INSTANCE_MAX)
    {
        DMA_ReportDevError(DMA_INIT_ID, DMA_E_PARAM_INSTANCE);
    }
    else if (pInitCfg == NULL)
    {
        DMA_ReportDevError(DMA_INIT_ID, DMA_E_PARAM_INITCFG);
    }
    else
    {
    #endif
        DMA_Type *const pDma = DMA;
        pDmaInstanceHandle->tStatus.u8DmaDumoUsedStatus[0] = 0xFF;
        pDmaInstanceHandle->tStatus.u8DmaDumoUsedStatus[1] = 0xFF;
        pDmaInstanceHandle->tStatus.u8DmaDumoUsedStatus[2] = 0xFF;
        pDmaInstanceHandle->tStatus.u8DmaDumoUsedStatus[3] = 0xFF;
        DMA_DeInit();
        DMA_HWA_SetHaltOnErrorFlag(pDma, pInitCfg->bHaltOnError);
        DMA_HWA_SetArbitrationAlgorithm(pDma, pInitCfg->eArbitrationAlgorithm);
        DMA_HWA_SetInnerLoopMappingEnableFlag(pDma, true);
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Deinitializes the DMA module and resets all configurations.
 *
 * This function deinitializes the DMA module by resetting all channel configurations, clearing control registers,
 * and disabling interrupts. It also resets the DMAMUX.
 */
void DMA_DeInit(void)
{
    DMA_Type *const pDma = DMA;
    uint8_t u8Index;
    DMA_HWA_SetControlRegister(pDma, 0U);
    DMA_HWA_DisableAllChannelErrorInterrupt(pDma);
    DMA_HWA_DisableAllChannelRequest(pDma);
    DMA_HWA_ClearAllChannelDoneStatus(pDma);
    DMA_HWA_ClearAllChannelErrorFlag(pDma);
    DMA_HWA_ClearAllChannelInterruptFlag(pDma);
    pDma->DUME = 0U;
    for (u8Index = 0U; u8Index < DMA_DUMO_COUNT; u8Index++)
    {
        DMA_HWA_SetUnalignModulo(pDma, u8Index, 0U, 0U);
    }
    for (u8Index = 0U; u8Index < DMA_CFG_COUNT; u8Index++)
    {
        DMA_HWA_SetPriority(pDma, u8Index, u8Index);
        pDma->CFG[u8Index].SADDR = 0UL;
        pDma->CFG[u8Index].SOFF = 0U;
        pDma->CFG[u8Index].SLAST = 0UL;
        pDma->CFG[u8Index].DADDR = 0UL;
        pDma->CFG[u8Index].DOFF = 0U;
        pDma->CFG[u8Index].DLAST = 0U;
        pDma->CFG[u8Index].ATTR = 0U;
        pDma->CFG[u8Index].NBYTES.ILNO = 0UL;
        pDma->CFG[u8Index].NBYTES.ILOFFNO = 0UL;
        pDma->CFG[u8Index].NBYTES.ILOFFYES = 0UL;
        pDma->CFG[u8Index].CSR = 0U;
        pDma->CFG[u8Index].BLC.CHTRGENNO = 0U;
        pDma->CFG[u8Index].CLC.CHTRGENNO = 0U;
        pDma->CFG[u8Index].BLC.CHTRGENYES = 0U;
        pDma->CFG[u8Index].CLC.CHTRGENYES = 0U;
    }
    Dmamux_Reset();
}

/**
 * @brief Initializes a DMA channel with the specified configuration.
 *
 * This function initializes a DMA channel using the provided configuration parameters. It performs error checking on
 * the input parameters and configures the DMA channel accordingly.
 *
 * @param pDmaHandle Pointer to the DMA handle structure.
 * @param pChnCfg Pointer to the DMA channel configuration structure.
 *
 * @return DMA_StatusType Indicates the status of the initialization operation.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 */
DMA_StatusType DMA_InitChannel(DMA_HandleType *pDmaHandle, const DMA_ChannelCfgType *const pChnCfg)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_INIT_CHANNEL_ID, DMA_E_PARAM_CHANNEL);
    }
    else if (pChnCfg == NULL)
    {
        DMA_ReportDevError(DMA_INIT_CHANNEL_ID, DMA_E_PARAM_CHCFG);
    }
    else if (pChnCfg->u16BlockCount == 0U)
    {
        DMA_ReportDevError(DMA_INIT_CHANNEL_ID, DMA_E_PARAM_BLOCKCNT);
    }
    else if (pChnCfg->u32BlockSize == 0U)
    {
        DMA_ReportDevError(DMA_INIT_CHANNEL_ID, DMA_E_PARAM_BLOCKSIZE);
    }
    else if (((pChnCfg->u32BlockSize >> pChnCfg->eSrcDataSize) << pChnCfg->eSrcDataSize != pChnCfg->u32BlockSize) ||
             ((pChnCfg->u32BlockSize >> pChnCfg->eDestDataSize) << pChnCfg->eDestDataSize != pChnCfg->u32BlockSize))
    {
        DMA_ReportDevError(DMA_INIT_CHANNEL_ID, DMA_E_PARAM_BLOCKSIZE_DATASIZE);
    }
    else
    {
    #endif
        uint8_t u8Channel = pDmaHandle->tSettings.u8Channel;
        DMA_Type *const pDma = DMA;
        DMAMUX_Type *const pDmamux = DMAMUX;

        DMA_StatusType ret = DMA_STATUS_ERROR;

        uint16_t u16SrcDataOffset = DMA_GetDataOffset(pChnCfg->eSrcIncMode, pChnCfg->eSrcDataSize);
        uint16_t u16DestDataOffset = DMA_GetDataOffset(pChnCfg->eDestIncMode, pChnCfg->eDestDataSize);

        int32_t s32SrcLastOffset;
        int32_t s32DestLastOffset;

        uint8_t u8SrcMod = 0U;
        uint8_t u8DestMod = 0U;

        bool bUseSrcDumo = (bool)false;
        bool bUseDestDumo = (bool)false;
        uint8_t u8DumoIndex = 0U;
        uint16_t u16Sumo = 0U;
        uint16_t u16Dumo = 0U;

        if ((pChnCfg->bSrcCircularBufferEn == true) || (pChnCfg->bDestCircularBufferEn == true))
        {
            /* If the circular buffer size is not power of 2 aligned, need to use the DUMO */
            if (pChnCfg->bSrcCircularBufferEn == true)
            {
                #if DMA_DEV_ERROR_REPORT == STD_ON
                if (pChnCfg->u32SrcCircBufferSize == 0U)
                {
                    DMA_ReportDevError(DMA_INIT_CHANNEL_ID, DMA_E_PARAM_SRCCIRCULARBUFSIZE);
                }
                else
                {
                #endif
                    bUseSrcDumo = (bool)(DMA_IsPowerOf2(pChnCfg->u32SrcCircBufferSize, &u8SrcMod) ? false : true);
                    #if DMA_DEV_ERROR_REPORT == STD_ON
                }
                    #endif
            }
            if (pChnCfg->bDestCircularBufferEn == true)
            {
                #if DMA_DEV_ERROR_REPORT == STD_ON
                if (pChnCfg->u32DestCircBufferSize == 0U)
                {
                    DMA_ReportDevError(DMA_INIT_CHANNEL_ID, DMA_E_PARAM_DESTCIRCULARBUFSIZE);
                }
                else
                {
                #endif
                    bUseDestDumo = (bool)(DMA_IsPowerOf2(pChnCfg->u32DestCircBufferSize, &u8DestMod) ? false : true);
                    #if DMA_DEV_ERROR_REPORT == STD_ON
                }
                    #endif
            }

            if (((pChnCfg->bSrcCircularBufferEn == true) &&
                  (pChnCfg->u32SrcCircBufferSize < u16SrcDataOffset)) ||
                ((pChnCfg->bDestCircularBufferEn == true) &&
                  (pChnCfg->u32DestCircBufferSize < u16DestDataOffset)))
            {
                ret = DMA_STATUS_UNSUPPORTED;
            }
            /* If source or destination unalign modulo is used, check whether all DUMO registers are occupied */
            else if ((bUseSrcDumo == true) || (bUseDestDumo == true))
            {
                ret = DMA_GetDumoIndex(pDmaHandle, &u8DumoIndex);
                if (ret == DMA_STATUS_SUCCESS)
                {
                    pDmaHandle->tSettings.pInstance->tStatus.u8DmaDumoUsedStatus[u8DumoIndex] = u8Channel;
                }
            }
            else
            {
                ret = DMA_STATUS_SUCCESS;
            }
        }
        else
        {
            ret = DMA_STATUS_SUCCESS;
        }

        if (ret == DMA_STATUS_SUCCESS)
        {
            if (pChnCfg->bSrcAddrLoopbackEn == true)
            {
                if (pChnCfg->bSrcBlockOffsetEn == false)
                {
                    s32SrcLastOffset = -((int32_t)((pChnCfg->u32BlockSize >> pChnCfg->eSrcDataSize) * u16SrcDataOffset) *
                                         (int32_t)(pChnCfg->u16BlockCount));
                }
                else
                {
                    s32SrcLastOffset = -(((int32_t)((pChnCfg->u32BlockSize >> pChnCfg->eSrcDataSize) * u16SrcDataOffset)) *
                                         (int32_t)(pChnCfg->u16BlockCount)) - ((pChnCfg->s32BlockOffset) * (int32_t)(pChnCfg->u16BlockCount - 1U));
                }
            }
            else
            {
                s32SrcLastOffset = 0;
            }
            if (pChnCfg->bDestAddrLoopbackEn == true)
            {
                if (pChnCfg->bDestBlockOffsetEn == false)
                {
                    s32DestLastOffset = -((int32_t)((pChnCfg->u32BlockSize >> pChnCfg->eDestDataSize) * u16DestDataOffset) *
                                          (int32_t)(pChnCfg->u16BlockCount));
                }
                else
                {
                    s32DestLastOffset = -(((int32_t)((pChnCfg->u32BlockSize >> pChnCfg->eDestDataSize) * u16DestDataOffset)) *
                                          (int32_t)(pChnCfg->u16BlockCount)) - ((pChnCfg->s32BlockOffset) * (int32_t)(pChnCfg->u16BlockCount - 1U));
                }
            }
            else
            {
                s32DestLastOffset = 0;
            }

            DMA_HWA_SetSrcAddr(pDma, u8Channel, (uint32_t)pChnCfg->pSrcBuffer);
            DMA_HWA_SetDestAddr(pDma, u8Channel, (uint32_t)pChnCfg->pDestBuffer);
            DMA_HWA_SetPriority(pDma, u8Channel, pChnCfg->u8ChannelPriority);

            if ((pChnCfg->bSrcCircularBufferEn == true) && (pChnCfg->bDestCircularBufferEn == true))
            {
                DMA_HWA_SetSrcDataSize(pDma, u8Channel, pChnCfg->eSrcDataSize);
                DMA_HWA_SetSrcModulo(pDma, u8Channel, u8SrcMod);
                DMA_HWA_SetDestDataSize(pDma, u8Channel, pChnCfg->eDestDataSize);
                DMA_HWA_SetDestModulo(pDma, u8Channel, u8DestMod);
            }
            else if (pChnCfg->bSrcCircularBufferEn == true)
            {
                DMA_HWA_SetSrcDataSize(pDma, u8Channel, pChnCfg->eSrcDataSize);
                DMA_HWA_SetSrcModulo(pDma, u8Channel, u8SrcMod);
                DMA_HWA_SetDestDataSize(pDma, u8Channel, pChnCfg->eDestDataSize);
                DMA_HWA_SetDestModulo(pDma, u8Channel, 0U);
            }
            else if (pChnCfg->bDestCircularBufferEn == true)
            {
                DMA_HWA_SetSrcDataSize(pDma, u8Channel, pChnCfg->eSrcDataSize);
                DMA_HWA_SetSrcModulo(pDma, u8Channel, 0U);
                DMA_HWA_SetDestDataSize(pDma, u8Channel, pChnCfg->eDestDataSize);
                DMA_HWA_SetDestModulo(pDma, u8Channel, u8DestMod);
            }
            else
            {
                DMA_HWA_SetSrcDataSize(pDma, u8Channel, pChnCfg->eSrcDataSize);
                DMA_HWA_SetSrcModulo(pDma, u8Channel, 0U);
                DMA_HWA_SetDestDataSize(pDma, u8Channel, pChnCfg->eDestDataSize);
                DMA_HWA_SetDestModulo(pDma, u8Channel, 0U);
            }

            if (bUseSrcDumo == true)
            {
                u16Sumo = (uint16_t)((pChnCfg->u32SrcCircBufferSize / u16SrcDataOffset - 1U) * u16SrcDataOffset);
            }
            if (bUseDestDumo == true)
            {
                u16Dumo = (uint16_t)((pChnCfg->u32DestCircBufferSize / u16DestDataOffset - 1U) * u16DestDataOffset);
            }
            if ((bUseSrcDumo == true) || (bUseDestDumo == true))
            {
                DMA_HWA_SetUnalignModulo(pDma, u8DumoIndex, u16Sumo, u16Dumo);
                DMA_HWA_SetUnalignModuloEnableFlag(pDma, u8Channel, bUseSrcDumo, bUseDestDumo);
                DMA_HWA_SetUnalignModuloSel(pDma, u8Channel, u8DumoIndex);
            }
            DMA_HWA_SetAutoDisableReuqestEnableFlag(pDma, u8Channel, pChnCfg->bAutoStop);

            DMA_HWA_SetSrcOffset(pDma, u8Channel, (int16_t)u16SrcDataOffset);
            DMA_HWA_SetDestOffset(pDma, u8Channel, (int16_t)u16DestDataOffset);

            DMA_HWA_SetInnerLoopOffset(pDma, u8Channel, pChnCfg->bSrcBlockOffsetEn, pChnCfg->bDestBlockOffsetEn,
                                       pChnCfg->s32BlockOffset);
            DMA_HWA_SetInnerLoopSize(pDma, u8Channel, pChnCfg->u32BlockSize);

            if ((pChnCfg->u16BlockCount > 1U) && (true == pChnCfg->bInnerChannelChain))
            {
                DMA_HWA_SetChannelToChannelTrig(pDma, u8Channel, true, u8Channel);
                DMA_HWA_SetLoopCount(pDma, u8Channel, pChnCfg->u16BlockCount);
            }
            else
            {
                DMA_HWA_SetChannelToChannelTrig(pDma, u8Channel, false, 0U);
                DMA_HWA_SetLoopCount(pDma, u8Channel, pChnCfg->u16BlockCount);
            }

            DMA_HWA_SetSrcLastAddrAdjustment(pDma, u8Channel, s32SrcLastOffset);
            DMA_HWA_SetDestLastAddrAdjustment(pDma, u8Channel, s32DestLastOffset);

            if (pChnCfg->eTriggerSrc == DMA_REQ_DISABLED)
            {
                DMAMUX_HWA_SetRequestSource(pDmamux, u8Channel, false, DMA_REQ_DISABLED);
            }
            else
            {
                DMAMUX_HWA_SetRequestSource(pDmamux, u8Channel, true, pChnCfg->eTriggerSrc);
            }
            DMA_InitChannelInterrupt(pDmaHandle, pChnCfg);
        }
        return ret;
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Deinitializes a DMA channel.
 *
 * This function deinitializes a DMA channel by resetting its configuration and clearing any associated settings or flags.
 *
 * @param pDmaHandle Pointer to the DMA handle structure.
 */
void DMA_DeinitChannel(DMA_HandleType *pDmaHandle)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CFG_COUNT)
    {
        DMA_ReportDevError(DMA_DEINIT_CHANNEL_ID, DMA_E_PARAM_DESTCIRCULARBUFSIZE);
    }
    else
    {
    #endif
        DMA_Type *const pDma = DMA;
        uint8_t u8DumoIndex = 0U;
        for (u8DumoIndex = 0U; u8DumoIndex < DMA_DUMO_COUNT; u8DumoIndex++)
        {
            if (pDmaHandle->tSettings.pInstance->tStatus.u8DmaDumoUsedStatus[u8DumoIndex] == pDmaHandle->tSettings.u8Channel)
            {
                pDmaHandle->tSettings.pInstance->tStatus.u8DmaDumoUsedStatus[u8DumoIndex] = DMA_CHANNEL_INVALID;
                DMA_HWA_SetUnalignModulo(pDma, u8DumoIndex, 0U, 0U);
            }
        }
        DMA_HWA_SetUnalignModuloEnableFlag(pDma, pDmaHandle->tSettings.u8Channel, false, false);
        DMA_HWA_DisableChannelErrorInterrupt(pDma, pDmaHandle->tSettings.u8Channel);
        DMA_HWA_DisableChannelRequest(pDma, pDmaHandle->tSettings.u8Channel);
        DMA_HWA_ClearChannelDoneStatus(pDma, pDmaHandle->tSettings.u8Channel);
        DMA_HWA_ClearChannelErrorFlag(pDma, pDmaHandle->tSettings.u8Channel);
        DMA_HWA_ClearChannelInterruptFlag(pDma, pDmaHandle->tSettings.u8Channel);

        pDma->CFG[pDmaHandle->tSettings.u8Channel].SADDR = 0UL;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].SOFF = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].SLAST = 0UL;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].DADDR = 0UL;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].DOFF = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].DLAST = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].ATTR = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].NBYTES.ILNO = 0UL;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].NBYTES.ILOFFNO = 0UL;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].NBYTES.ILOFFYES = 0UL;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].CSR = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].BLC.CHTRGENNO = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].CLC.CHTRGENNO = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].BLC.CHTRGENYES = 0U;
        pDma->CFG[pDmaHandle->tSettings.u8Channel].CLC.CHTRGENYES = 0U;
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Initializes the interrupts for a DMA channel.
 *
 * This function configures the DMA channel's interrupt settings based on the provided configuration.
 *
 * @param pDmaHandle Pointer to the DMA handle structure. Must point to a valid DMA handle.
 * @param pChnCfg Pointer to the DMA channel configuration structure. Must not be NULL.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 *       - Checks if the channel index is within the valid range.
 *       - Checks if the provided channel configuration pointer is not NULL.
 */
static inline void DMA_InitChannelInterrupt(DMA_HandleType *pDmaHandle, const DMA_ChannelCfgType *const pChnCfg)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_INIT_CHANNEL_INT_ID, DMA_E_PARAM_CHANNEL);
    }
    else if (pChnCfg == NULL)
    {
        DMA_ReportDevError(DMA_INIT_CHANNEL_INT_ID, DMA_E_PARAM_INTERRUPTCFG);
    }
    else
    {
    #endif

        DMA_Type *const pDma = DMA;

        if (pChnCfg->bTransferCompleteIntEn)
        {
            pDmaHandle->tSettings.callback.pTransferCompleteCallback = pChnCfg->pTransferCompleteNotify;
            pDmaHandle->tSettings.callback.completedata = pChnCfg->completedata;
            DMA_HWA_EnableTransferCompleteInterrupt(pDma, pDmaHandle->tSettings.u8Channel);
        }
        else
        {
            DMA_HWA_DisableTransferCompleteInterrupt(pDma, pDmaHandle->tSettings.u8Channel);
            pDmaHandle->tSettings.callback.pTransferCompleteCallback = NULL;
        }

        if (pChnCfg->bTransferErrorIntEn)
        {
            pDmaHandle->tSettings.pInstance->tSettings.pTransferErrorCallback[pDmaHandle->tSettings.u8Channel] = pChnCfg->pTransferErrorNotify;
            pDmaHandle->tSettings.pInstance->tSettings.errdata[pDmaHandle->tSettings.u8Channel] = pChnCfg->errdata;
            DMA_HWA_EnableChannelErrorInterrupt(pDma, pDmaHandle->tSettings.u8Channel);
        }
        else
        {
            pDmaHandle->tSettings.pInstance->tSettings.pTransferErrorCallback[pDmaHandle->tSettings.u8Channel] = NULL;
        }
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Configures chained transfer for a DMA channel.
 *
 * This function sets up the chaining of transfers between two DMA channels.
 *
 * @param pDmaHandle Pointer to the DMA handle structure. Must point to a valid DMA handle.
 * @param pChainTransferCfg Pointer to the chained transfer configuration structure. Must not be NULL.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 *       - Checks if the channel index is within the valid range.
 *       - Checks if the provided chained transfer configuration pointer is not NULL.
 */
void DMA_ConfigChainedTransfer(DMA_HandleType *pDmaHandle,
                               const DMA_ChainTransferType *const pChainTransferCfg)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_CONFIG_CHAINED_TRANS_ID, DMA_E_PARAM_CHANNEL);
    }
    else if (pChainTransferCfg == NULL)
    {
        DMA_ReportDevError(DMA_CONFIG_CHAINED_TRANS_ID, DMA_E_PARAM_INTERRUPTCFG);
    }
    else
    {
    #endif
        DMA_Type *const pDma = DMA;

        DMA_HWA_SetOuterLoopTrigEnableFlag(pDma, pDmaHandle->tSettings.u8Channel, pChainTransferCfg->bChanelChainEn);
        DMA_HWA_SetOuterLoopTrigChannel(pDma, pDmaHandle->tSettings.u8Channel, pChainTransferCfg->u8ChainedChannel);
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Modifies source and/or destination addresses for a DMA channel.
 *
 * This function modifies the source and/or destination addresses for a DMA channel if it is in an idle state.
 *
 * @param pDmaHandle Pointer to the DMA handle structure. Must point to a valid DMA handle.
 * @param pSrcBuffer Pointer to the new source buffer address. Can be NULL if no change is needed.
 * @param pDestBuffer Pointer to the new destination buffer address. Can be NULL if no change is needed.
 *
 * @return DMA_StatusType Returns DMA_STATUS_SUCCESS if the operation was successful, DMA_STATUS_BUSY if the channel is busy, or DMA_STATUS_ERROR for other errors.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 *       - Checks if the channel index is within the valid range.
 */
DMA_StatusType DMA_ModifyAddress(DMA_HandleType *pDmaHandle, const volatile void *pSrcBuffer,
                                 const volatile void *pDestBuffer)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_CONFIG_MODIFY_ADDR_ID, DMA_E_PARAM_CHANNEL);
    }
    else
    {
    #endif
        DMA_Type *const pDma = DMA;
        DMA_StatusType ret = DMA_STATUS_ERROR;

        if (DMA_GetChannelStatus(pDmaHandle) == DMA_RUNNING_STATUS_IDLE)
        {
            if (pSrcBuffer != NULL)
            {
                DMA_HWA_SetSrcAddr(pDma, pDmaHandle->tSettings.u8Channel, (uint32_t)pSrcBuffer);
            }
            if (pDestBuffer != NULL)
            {
                DMA_HWA_SetDestAddr(pDma, pDmaHandle->tSettings.u8Channel, (uint32_t)pDestBuffer);
            }
            ret = DMA_STATUS_SUCCESS;
        }
        else
        {
            ret = DMA_STATUS_BUSY;
        }
        return ret;
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Starts a DMA channel.
 *
 * This function starts the specified DMA channel either by enabling the channel request or by directly starting it.
 *
 * @param pDmaHandle Pointer to the DMA handle structure. Must point to a valid DMA handle.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 *       - Checks if the channel index is within the valid range.
 */
void DMA_StartChannel(DMA_HandleType *pDmaHandle)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_CONFIG_START_CH_ID, DMA_E_PARAM_CHANNEL);
    }
    else
    {
    #endif
        DMA_Type *const pDma = DMA;

        if (DMA_GetChannelRequestSrc(pDmaHandle) == DMA_REQ_DISABLED)
        {
            DMA_HWA_SetChannelStart(pDma, pDmaHandle->tSettings.u8Channel);
        }
        else
        {
            DMA_HWA_EnableChannelRequest(pDma, pDmaHandle->tSettings.u8Channel);
        }
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Stops a DMA channel.
 *
 * This function stops the specified DMA channel by disabling its request.
 *
 * @param pDmaHandle Pointer to the DMA handle structure. Must point to a valid DMA handle.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 *       - Checks if the channel index is within the valid range.
 */
void DMA_StopChannel(DMA_HandleType *pDmaHandle)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_CONFIG_STOP_CH_ID, DMA_E_PARAM_CHANNEL);
    }
    else
    {
    #endif
        DMA_Type *const pDma = DMA;

        DMA_HWA_DisableChannelRequest(pDma, pDmaHandle->tSettings.u8Channel);
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Cancels a DMA transfer.
 *
 * This function cancels the current DMA transfer, optionally generating an error flag.
 *
 * @param bGenerateErr Flag indicating whether to generate an error during cancellation.
 *
 * @return DMA_StatusType Returns DMA_STATUS_SUCCESS if the cancellation was successful, DMA_STATUS_TIMEOUT if the timeout occurred, or DMA_STATUS_ERROR for other errors.
 *
 * @note The function uses a timeout mechanism to ensure that the cancellation process completes within a reasonable time frame.
 */
DMA_StatusType DMA_CancelTransfer(bool bGenerateErr)
{
    DMA_Type *const pDma = DMA;
    DMA_StatusType eRet = DMA_STATUS_ERROR;
    uint32_t u32TimeOut = 15000000U;

    if (bGenerateErr)
    {
        DMA_HWA_ErrorCancelTransfer(pDma);
        while ((DMA_HWA_GetErrorCancelTransferStatus(pDma) == true) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
    }
    else
    {
        DMA_HWA_CancelTransfer(pDma);
        while ((DMA_HWA_GetCancelTransferStatus(pDma) == true) && (u32TimeOut != 0U))
        {
            u32TimeOut--;
        }
    }
    if (u32TimeOut != 0U)
    {
        eRet = DMA_STATUS_SUCCESS;
    }
    else
    {
        eRet = DMA_STATUS_TIMEOUT;
    }
    return eRet;
}

/**
 * @brief Gets the request source for a DMA channel.
 *
 * This function retrieves the request source for the specified DMA channel.
 *
 * @param pDmaHandle Pointer to the DMA handle structure. Must point to a valid DMA handle.
 *
 * @return DMA_RequestSourceType Returns the request source type for the DMA channel.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 *       - Checks if the channel index is within the valid range.
 */
DMA_RequestSourceType DMA_GetChannelRequestSrc(DMA_HandleType *pDmaHandle)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_CONFIG_GET_CH_REQ_SOURCE_ID, DMA_E_PARAM_CHANNEL);
    }
    else
    {
    #endif
        DMAMUX_Type *const pDmamux = DMAMUX;

        DMA_RequestSourceType eReqSrc = DMAMUX_HWA_GetRequestSource(pDmamux, pDmaHandle->tSettings.u8Channel);

        return eReqSrc;
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Retrieves the current status of the DMA controller.
 *
 * This function returns the running status of the DMA controller.
 *
 * @return DMA_RunningStatusType Returns the running status of the DMA controller.
 */
DMA_RunningStatusType DMA_GetStatus(void)
{
    const DMA_Type *const pDma = DMA;
    DMA_RunningStatusType eDMAStatus = DMA_HWA_GetStatus(pDma);
    return eDMAStatus;
}

/**
 * @brief Retrieves the status of a DMA channel.
 *
 * This function returns the running status of the specified DMA channel.
 *
 * @param pDmaHandle Pointer to the DMA handle structure. Must point to a valid DMA handle.
 *
 * @return DMA_RunningStatusType Returns the running status of the DMA channel.
 *
 * @note Error checking is performed if DMA_DEV_ERROR_REPORT is defined as STD_ON.
 *       - Checks if the channel index is within the valid range.
 */
DMA_RunningStatusType DMA_GetChannelStatus(DMA_HandleType *pDmaHandle)
{
    #if DMA_DEV_ERROR_REPORT == STD_ON
    if (pDmaHandle->tSettings.u8Channel >= DMA_CHANNEL_MAX)
    {
        DMA_ReportDevError(DMA_CONFIG_GET_CH_STATUS_ID, DMA_E_PARAM_CHANNEL);
    }
    else
    {
    #endif
        const DMA_Type *const pDma = DMA;
        DMA_RunningStatusType eChannelStatus = DMA_HWA_GetChannelActiveStatus(pDma, pDmaHandle->tSettings.u8Channel);
        return eChannelStatus;
        #if DMA_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

#endif
