/**
 * @file module_driver_fcspi.c
 * @author Flagchip051
 * @brief FCSPI driver source code
 * @version 2.0.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip103   N/A          First version
*********************************************************************************/

#include "module_driver_fcspi.h"

#if FCSPI_INSTANCE_COUNT > 0U

#if FCSPI_DEV_ERROR_REPORT == STD_ON
#define FCSPI_ReportDevError(func, error) ReportDevError(FCSPI_MODULE_ID, func, error)
#endif

static FCSPI_MemMapPtr s_apFCSpiInsts[FCSPI_INSTANCE_COUNT] = FCSPI_BASE_PTRS;

static void      FCSpi_Hw_Reset(FCSPI_InstanceType eInst,FCSPI_AtomicBoolType eRxFifo,FCSPI_AtomicBoolType eTxFifo,FCSPI_AtomicBoolType eSoftRst);
static void      FCSpi_Hw_ClearSomeStatusW1CFlag(FCSPI_InstanceType eInst, uint32_t u32FlagBitSet); /* refer to FCSPI_DRV_STATUS_REG_W1C_U32 */
static void      FCSpi_Hw_EnableMoreInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts); /* refer to FCSPI_INT_EN_DMIE(1) */
static void      FCSpi_Hw_DisableSomeInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts); /* refer to FCSPI_INT_EN_DMIE(1) */
static void      FCSpi_Hw_SetPcs_2_3_Mode(FCSPI_InstanceType eInst, FCSPI_PCS2_3ModeType eMode);
static void      FCSpi_Hw_SetPin(FCSPI_InstanceType eInst, FCSPI_PinModeType eMode, FCSPI_NegatedPinOutStatType eStat);
static void      FCSpi_Hw_SetOnePcsPolarity(FCSPI_InstanceType eInst,FCSPI_PCSType ePcs, FCSPI_PcsPolarityType ePolarity);
static void      FCSpi_Hw_Master_SetSckLoopbackSample(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable);
static void      FCSpi_Hw_SetContinuousCommand(FCSPI_InstanceType eInst,uint32_t *u32PreviousTrCtrl,FCSPI_AtomicBoolType eEnable);
static void      FCSpi_Hw_SelectUsePcs(FCSPI_InstanceType eInst,uint32_t *u32PreviousTrCtrl,FCSPI_PCSType ePCS);
static void      FCSpi_Hw_Get_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst, uint8_t *pbySCKPCS, uint8_t *pbyPCSSCK, uint8_t *pbyPCSPCS, uint8_t *pbySCKDIV);
static void      FCSpi_Hw_Set_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst, uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS, uint8_t u8SCKDIV);
static void      FCSpi_Hw_Set_SCK_PCS_Hold(FCSPI_InstanceType eInst, uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS);
static void      FCSpi_Hw_SetRxTxDmaEnableStatus(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eRxEnable, FCSPI_AtomicBoolType eTxEnable);
static uint32_t  FCSpi_Hw_Master_CalcBaudRate(FCSPI_InstanceType eInst, const FCSPI_MasterCfgType *pCfg, uint32_t *pdwPrescaleRegVal, uint32_t *pdwActualSckDiv);
static uint32_t  FCSpi_Calculate_TRCR(FCSPI_TxRxCtrlType *ptCtrl);
static FCSPI_StatusType           FCSpi_Hw_Disable(FCSPI_InstanceType eInst);
static FCSPI_PrescaleValueType    FCSpi_Hw_GetRegPrescalerVal(FCSPI_InstanceType eInst);

static void fcspi_read_rx_fifo(FCSPI_HandleType *pFcspiHandle);
static void fcspi_write_tx_fifo(FCSPI_HandleType *pFcspiHandle);
static void fcspi_master_clean_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInInterrupt);
static void fcspi_master_abort_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInISR);
static void fcspi_master_dma_rx_err_interrupt(void *pFcspiHandle);
static void fcspi_master_dma_rx_finish_interrupt(void *pFcspiHandle);
static void fcspi_master_dma_tx_err_interrupt(void *pFcspiHandle);
static void fcspi_master_dma_tx_finish_interrupt(void *pFcspiHandle);
static void fcspi_slave_clean_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInInterrupt);
static void fcspi_slave_abort_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInInterrupt);
static void fcspi_slave_dma_rx_err_interrupt(void *pFcspiHandle);
static void fcspi_slave_dma_rx_finish_interrupt(void *pFcspiHandle);
static void fcspi_slave_dma_tx_err_interrupt(void *pFcspiHandle);
static void fcspi_slave_dma_tx_finish_interrupt(void *pFcspiHandle);
static FCSPI_StatusType fcspi_master_async_transfer_bytes(FCSPI_HandleType *pFcspiHandle,const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer,uint16_t u16TransferByteCnt);
static FCSPI_StatusType fcspi_master_trigger(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);
static FCSPI_StatusType fcspi_slave_async_transfer_bytes(FCSPI_HandleType *pFcspiHandle,const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer, uint16_t u16TransferByteCnt);
static FCSPI_StatusType fcspi_slave_trigger(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInISR);

#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
static void FCSpi_Hw_SetFrameSizeCommand(FCSPI_InstanceType eInst,uint32_t *u32PreviousTrCtrl,uint16_t u16FrameSize);
static void FCSpi_Get_TRCR(FCSPI_TxRxCtrlType *ptCtrl, uint32_t u32PreviousTrCtrl);
static void fcspi_adjust_data_after_receive(const uint32_t raw_data, uint32_t raw_length, uint8_t *result_buffer, FCSPI_HandleType *pFcspiHandle);
static uint32_t fcspi_adjust_data_before_transmit(const uint8_t * raw_data, uint32_t raw_length, FCSPI_HandleType *pFcspiHandle);
#else
static void FCSpi_Hw_SetCpolCphaCommand(FCSPI_InstanceType eInst,uint32_t *u32PreviousTrCtrl, FCSPI_SckPolarityType eSckPolarity,FCSPI_SckSamplePhaseType eSckPhase);
#endif

static void FCSpi_Hw_Reset(FCSPI_InstanceType eInst,
                           FCSPI_AtomicBoolType eRxFifo, FCSPI_AtomicBoolType eTxFifo, FCSPI_AtomicBoolType eSoftRst)
{
    uint32_t u32Flag    = 0U;
    uint32_t u32OldFlag = FCSPI_HWA_GetCtrlValue(s_apFCSpiInsts[eInst]);
    uint32_t u32Mask    = FCSPI_CTRL_MASK;

    if (eRxFifo)
    {
        u32Flag |= FCSPI_CTRL_RST_RF(1);
    }

    if (eTxFifo)
    {
        u32Flag |= FCSPI_CTRL_RST_TF(1);
    }

    if (FCSPI_TRUE == eSoftRst)
    {
        u32Flag |= FCSPI_CTRL_SW_RST(1);
    }

    u32OldFlag |= FCSPI_CTRL_DBG_EN_MASK;
    u32Flag |= u32OldFlag;
    FCSPI_HWA_SetCtrlValue(s_apFCSpiInsts[eInst], u32Flag);

    /* no need delay */
    if (FCSPI_TRUE == eSoftRst)
    {
        FCSPI_HWA_SetCtrlValue(s_apFCSpiInsts[eInst], FCSPI_CTRL_DBG_EN_MASK);
    }
    else
    {
        FCSPI_HWA_SetCtrlValue(s_apFCSpiInsts[eInst], (u32OldFlag & u32Mask));
    }
}

static FCSPI_StatusType FCSpi_Hw_Disable(FCSPI_InstanceType eInst)
{
    FCSPI_StatusType eStatus = FCSPI_STATUS_SUCCESS;

    if (0U != (FCSPI_HWA_GetStatus(s_apFCSpiInsts[eInst]) & FCSPI_STATUS_BF_MASK))
    {
        eStatus = FCSPI_STATUS_BUSY;
    }
    else
    {
        FCSPI_HWA_ModuleDisable(s_apFCSpiInsts[eInst]);
    }

    return eStatus;
}

static void FCSpi_Hw_ClearSomeStatusW1CFlag(
            FCSPI_InstanceType eInst, uint32_t u32FlagBitSet) /* refer to FCSPI_DRV_STATUS_REG_W1C_U32 */
{
    FCSPI_HWA_ClearStatus(s_apFCSpiInsts[eInst], (u32FlagBitSet & FCSPI_DRV_STATUS_REG_W1C_MASK_U32));
}

static void FCSpi_Hw_EnableMoreInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts)
{
    uint32_t u32RegVal = FCSPI_HWA_GetIntrruptEnableReg(s_apFCSpiInsts[eInst]);
    u32RegVal |= (u32Interrupts & FCSPI_INT_EN_MASK);

    FCSPI_HWA_SetInterruptEnableReg(s_apFCSpiInsts[eInst], u32RegVal);
}

static void FCSpi_Hw_DisableSomeInterrupts(FCSPI_InstanceType eInst, uint32_t u32Interrupts)
{
    uint32_t u32RegVal = FCSPI_HWA_GetIntrruptEnableReg(s_apFCSpiInsts[eInst]);
    u32RegVal &= (~(u32Interrupts & FCSPI_INT_EN_MASK));

    FCSPI_HWA_SetInterruptEnableReg(s_apFCSpiInsts[eInst], u32RegVal);
}

static void FCSpi_Hw_SetRxTxDmaEnableStatus(
            FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eRxEnable, FCSPI_AtomicBoolType eTxEnable)
{
    uint32_t u32Flag = 0U;

    if (eRxEnable)
    {
        u32Flag |= FCSPI_DMA_EN_RFDE(1);
    }

    if (eTxEnable)
    {
        u32Flag |= FCSPI_DMA_EN_TFDE(1);
    }

    FCSPI_HWA_SetDMAEnableReg(s_apFCSpiInsts[eInst], u32Flag);
}

static void FCSpi_Hw_SetPcs_2_3_Mode(FCSPI_InstanceType eInst, FCSPI_PCS2_3ModeType eMode)
{
    uint32_t u32RegVal = FCSPI_HWA_GetCFG1Reg(s_apFCSpiInsts[eInst]);

    if (eMode == PCS2_3_PCS)
    {
        u32RegVal &= (~(FCSPI_CFG1_PCS_CFG_MASK));
    }
    else
    {
        u32RegVal |= (FCSPI_CFGR1_PCS23_DATABUS_IN_4BIT_MODE_U32);
    }

    FCSPI_HWA_SetCFG1Reg(s_apFCSpiInsts[eInst], u32RegVal);
}

static void FCSpi_Hw_SetPin(FCSPI_InstanceType eInst,
                            FCSPI_PinModeType eMode, FCSPI_NegatedPinOutStatType eStat)
{
    uint32_t u32Flag = FCSPI_HWA_GetCFG1Reg(s_apFCSpiInsts[eInst]);

    u32Flag &= (~(FCSPI_CFG1_PIN_CFG_MASK));
    u32Flag &= (~(FCSPI_CFG1_OUT_CFG_MASK));

    switch (eMode)
    {
        case SIN_INPUT_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SIN_INPUT_OUTPUT_U32;
            break;
        case SOUT_INPUT_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SOUT_INPUT_OUTPUT_U32;
            break;
        case SOUT_INPUT_SIN_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SOUT_INPUT_SIN_OUTPUT_U32;
            break;
        case SIN_INPUT_SOUT_OUTPUT:
            u32Flag |= FCSPI_CFGR1_PINCFG_SIN_INPUT_SOUT_OUTPUT_U32;
            break;
        default:
            u32Flag |= FCSPI_CFGR1_PINCFG_SIN_INPUT_SOUT_OUTPUT_U32;
            break;
    }

    if (PINOUT_RETAIN_LAST == eStat)
    {
        u32Flag |= FCSPI_CFGR1_OUTCFG_RETAIN_LAST_WHEN_NEGATE_U32;
    }
    else
    {
        u32Flag |= FCSPI_CFGR1_OUTCFG_TRISTATE_WHEN_NEGATE_U32;
    }

    FCSPI_HWA_SetCFG1Reg(s_apFCSpiInsts[eInst], u32Flag);
}

static void FCSpi_Hw_SetOnePcsPolarity(FCSPI_InstanceType eInst,
                                       FCSPI_PCSType ePcs, FCSPI_PcsPolarityType ePolarity)
{
    uint32_t u32Flag = FCSPI_HWA_GetCFG1Reg(s_apFCSpiInsts[eInst]);

    if (FCSPI_PCS_POL_ACTIVE_HIGH == ePolarity)
    {
        if (0U == ((((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs)) & u32Flag))
        {
            u32Flag |= (((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs));
        }
    }
    else /* active low */
    {
        if (0U != ((((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs)) & u32Flag))
        {
            u32Flag &= (~(((uint32_t)0x1) << (FCSPI_CFG1_PCS_POL_SHIFT + (uint32_t)ePcs)));
        }
    }

    FCSPI_HWA_SetCFG1Reg(s_apFCSpiInsts[eInst], u32Flag);
}

/* before call this function, ensure in master mode */
static void FCSpi_Hw_Master_SetSckLoopbackSample(
            FCSPI_InstanceType eInst, FCSPI_AtomicBoolType eEnable)
{
    uint32_t u32Flag = FCSPI_HWA_GetCFG1Reg(s_apFCSpiInsts[eInst]);

    if (FCSPI_TRUE == eEnable)
    {
        if (FCSPI_CFG1_SCK_LB(1) != (u32Flag & FCSPI_CFG1_SCK_LB_MASK))
        {
            u32Flag |= FCSPI_CFG1_SCK_LB(1);
        }
    }
    else
    {
        if (FCSPI_CFG1_SCK_LB(0) != (u32Flag & FCSPI_CFG1_SCK_LB_MASK))
        {
            u32Flag &= (~(FCSPI_CFG1_SCK_LB_MASK));
        }
    }

    FCSPI_HWA_SetCFG1Reg(s_apFCSpiInsts[eInst], u32Flag);
}

static void FCSpi_Hw_Set_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst,
                                          uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS, uint8_t u8SCKDIV)
{
    uint32_t u32Flag = FCSPI_HWA_GetClockConfig(s_apFCSpiInsts[eInst]);
    uint32_t u32Val  = 0U;

    {
        u32Val = u8SCKPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_SCKPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_SCKPCS_SHIFT);
    }

    {
        u32Val = u8PCSSCK;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSSCK_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSSCK_SHIFT);
    }

    {
        u32Val = u8PCSPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSPCS_SHIFT);
    }

    {
        u32Val = u8SCKDIV;
        u32Flag &= (~(FCSPI_CLK_CFG_SCKDIV_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_SCKDIV_SHIFT);
    }

    {
        FCSPI_HWA_SetClockConfig(s_apFCSpiInsts[eInst], u32Flag);
    }
}

static void FCSpi_Hw_Set_SCK_PCS_Hold(FCSPI_InstanceType eInst,
                                      uint8_t u8SCKPCS, uint8_t u8PCSSCK, uint8_t u8PCSPCS)
{
    uint32_t u32Flag = FCSPI_HWA_GetClockConfig(s_apFCSpiInsts[eInst]);
    uint32_t u32Val  = 0U;

    {
        u32Val = u8SCKPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_SCKPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_SCKPCS_SHIFT);
    }

    {
        u32Val = u8PCSSCK;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSSCK_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSSCK_SHIFT);
    }

    {
        u32Val = u8PCSPCS;
        u32Flag &= (~(FCSPI_CLK_CFG_PCSPCS_MASK));
        u32Flag |= (u32Val << FCSPI_CLK_CFG_PCSPCS_SHIFT);
    }

    {
        FCSPI_HWA_SetClockConfig(s_apFCSpiInsts[eInst], u32Flag);
    }
}

static void FCSpi_Hw_Get_SCK_PCS_DIV_Hold(FCSPI_InstanceType eInst,
                                          uint8_t *pbySCKPCS,
                                          uint8_t *pbyPCSSCK,
                                          uint8_t *pbyPCSPCS,
                                          uint8_t *pbySCKDIV)
{
    uint32_t u32Flag = FCSPI_HWA_GetClockConfig(s_apFCSpiInsts[eInst]);

    if (pbySCKPCS)
    {
        *pbySCKPCS = (uint8_t)((u32Flag & FCSPI_CLK_CFG_SCKPCS_MASK) >> FCSPI_CLK_CFG_SCKPCS_SHIFT);
    }

    if (pbyPCSSCK)
    {
        *pbyPCSSCK = (uint8_t)((u32Flag & FCSPI_CLK_CFG_PCSSCK_MASK) >> FCSPI_CLK_CFG_PCSSCK_SHIFT);
    }

    if (pbyPCSPCS)
    {
        *pbyPCSPCS = (uint8_t)((u32Flag & FCSPI_CLK_CFG_PCSPCS_MASK) >> FCSPI_CLK_CFG_PCSPCS_SHIFT);
    }

    if (pbySCKDIV)
    {
        *pbySCKDIV = ((uint8_t)(u32Flag & FCSPI_CLK_CFG_SCKDIV_MASK) >> FCSPI_CLK_CFG_SCKDIV_SHIFT);
    }
}

static uint32_t FCSpi_Calculate_TRCR(FCSPI_TxRxCtrlType *ptCtrl)
{
    uint32_t         u32Flag = 0U;

    if ((ptCtrl->u16FrameBitCnt < ((uint16_t)8)) ||
         (((uint16_t)0) != (ptCtrl->u16FrameBitCnt & ((uint16_t)0x1))))
    {
        u32Flag = 0xffffffff;
    }
    else
    {
        u32Flag |= (((uint32_t)(ptCtrl->eSckPolarity))     << FCSPI_TR_CTRL_SCK_POL_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eSckPhase))        << FCSPI_TR_CTRL_SCK_PHA_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->ePrescalerValue))  << FCSPI_TR_CTRL_PRESCALE_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->ePCSSelect))       << FCSPI_TR_CTRL_PCS_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eBitFirstOrder))   << FCSPI_TR_CTRL_LSBF_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eByteSwap))        << FCSPI_TR_CTRL_BYSW_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eContTransEnable)) << FCSPI_TR_CTRL_CT_EN_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eContCmdEnable))   << FCSPI_TR_CTRL_CT_GO_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eRxDisable))       << FCSPI_TR_CTRL_RX_MSK_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eTxDisable))       << FCSPI_TR_CTRL_TX_MSK_SHIFT);
        u32Flag |= (((uint32_t)(ptCtrl->eTransferWidth))   << FCSPI_TR_CTRL_WIDTH_SHIFT);
        u32Flag |= (((uint32_t)((uint16_t)(ptCtrl->u16FrameBitCnt - (uint16_t)1))) << FCSPI_TR_CTRL_FRM_SZ_SHIFT);
    }

    return u32Flag;
}

static void FCSpi_Get_TRCR(FCSPI_TxRxCtrlType *ptCtrl, uint32_t u32PreviousTrCtrl)
{
    uint32_t u32Flag = u32PreviousTrCtrl;

    ptCtrl->eSckPolarity = (FCSPI_SckPolarityType)
        ((u32Flag & FCSPI_TR_CTRL_SCK_POL_MASK) >> FCSPI_TR_CTRL_SCK_POL_SHIFT);
    ptCtrl->eSckPhase = (FCSPI_SckSamplePhaseType)
        ((u32Flag & FCSPI_TR_CTRL_SCK_PHA_MASK) >> FCSPI_TR_CTRL_SCK_PHA_SHIFT);
    ptCtrl->ePrescalerValue = (FCSPI_PrescaleValueType)
        ((u32Flag & FCSPI_TR_CTRL_PRESCALE_MASK) >> FCSPI_TR_CTRL_PRESCALE_SHIFT);
    ptCtrl->ePCSSelect = (FCSPI_PCSType)
        ((u32Flag & FCSPI_TR_CTRL_PCS_MASK) >> FCSPI_TR_CTRL_PCS_SHIFT);
    ptCtrl->eBitFirstOrder = (FCSPI_BitFirstOrderType)
        ((u32Flag & FCSPI_TR_CTRL_LSBF_MASK) >> FCSPI_TR_CTRL_LSBF_SHIFT);
    ptCtrl->eByteSwap = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_BYSW_MASK) >> FCSPI_TR_CTRL_BYSW_SHIFT);
    ptCtrl->eContTransEnable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_CT_EN_MASK) >> FCSPI_TR_CTRL_CT_EN_SHIFT);

    ptCtrl->eContCmdEnable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_CT_GO_MASK) >> FCSPI_TR_CTRL_CT_GO_SHIFT);
    ptCtrl->eRxDisable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_RX_MSK_MASK) >> FCSPI_TR_CTRL_RX_MSK_SHIFT);
    ptCtrl->eTxDisable = (FCSPI_AtomicBoolType)
        ((u32Flag & FCSPI_TR_CTRL_TX_MSK_MASK) >> FCSPI_TR_CTRL_TX_MSK_SHIFT);
    ptCtrl->eTransferWidth = (FCSPI_TransferWidthType)
        ((u32Flag & FCSPI_TR_CTRL_WIDTH_MASK) >> FCSPI_TR_CTRL_WIDTH_SHIFT);
    ptCtrl->u16FrameBitCnt = (uint16_t)
        (((u32Flag & FCSPI_TR_CTRL_FRM_SZ_MASK) >> FCSPI_TR_CTRL_FRM_SZ_SHIFT)+1);
}

#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
static void FCSpi_Hw_SetFrameSizeCommand(FCSPI_InstanceType eInst, uint32_t *u32PreviousTrCtrl, uint16_t u16FrameSize)
{
    uint32_t u32NewTrCtrl = *u32PreviousTrCtrl;

    u32NewTrCtrl &= (~(FCSPI_TR_CTRL_FRM_SZ_MASK));
    u32NewTrCtrl |= (((uint32_t)u16FrameSize-1u)  << FCSPI_TR_CTRL_FRM_SZ_SHIFT);

    FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[eInst], u32NewTrCtrl);
    *u32PreviousTrCtrl = u32NewTrCtrl;
}

static uint32_t fcspi_adjust_data_before_transmit(const uint8_t * raw_data, uint32_t raw_length, FCSPI_HandleType *pFcspiHandle)
{
    uint32_t u32Result=0;
    uint32_t index;

    if(raw_length>=4u)
    {
        if(((pFcspiHandle->tStatus.u32CurrentTrCtrl&FCSPI_TR_CTRL_LSBF_MASK)!=FCSPI_TR_CTRL_LSBF_MASK))
        {
            switch(pFcspiHandle->tStatus.u16BitsPerFrame)
            {
                case 16:
                    u32Result = (uint32_t)((raw_data[2]<<24)|(raw_data[3]<<16)|(raw_data[0]<<8)|raw_data[1]);
                break;

                case 32:
                    u32Result = (uint32_t)((raw_data[0]<<24)|(raw_data[1]<<16)|(raw_data[2]<<8)|raw_data[3]);
                break;

                default:
                    u32Result = (uint32_t)((raw_data[3]<<24)|(raw_data[2]<<16)|(raw_data[1]<<8)|raw_data[0]);
                    break;
            }
        }
        else
        {
            u32Result = (uint32_t)((raw_data[0]<<24)|(raw_data[1]<<16)|(raw_data[2]<<8)|raw_data[3]);
        }
    }
    else
    {
        if(((pFcspiHandle->tStatus.u32CurrentTrCtrl&FCSPI_TR_CTRL_LSBF_MASK)!=FCSPI_TR_CTRL_LSBF_MASK))
        {
            switch(pFcspiHandle->tStatus.u16BitsPerFrame)
            {
                case 16:
                    u32Result = (uint32_t)(((raw_data[0]<<8)|(raw_data[1]))<<16);
                break;

                default:
                    for(index = raw_length;index>0u;index--)
                    {
                        u32Result |= raw_data[index - 1u];
                        if(index > 1u)
                        {
                            u32Result = u32Result<<8;
                        }
                    }
                    u32Result = u32Result<<(8*(4-raw_length));
                break;
            }
        }
        else
        {
            switch (raw_length)
            {
                case 1 : u32Result = (uint32_t)(raw_data[0]<<24);break;
                case 2 : u32Result = (uint32_t)(((raw_data[0]<<8)|(raw_data[1]))<<16);break;
                case 3 : u32Result = (uint32_t)(((raw_data[0]<<16)|(raw_data[1]<<8)|raw_data[2])<<8);break;
                default: u32Result = 0; break;
            }
        }
    }
    return u32Result;
}

static void fcspi_adjust_data_after_receive(const uint32_t raw_data, uint32_t raw_length, uint8_t *result_buffer, FCSPI_HandleType *pFcspiHandle)
{
    uint32_t u32Data=raw_data;
    uint32_t index;

    if(raw_length>=4u)
    {
        if(((pFcspiHandle->tStatus.u32CurrentTrCtrl&FCSPI_TR_CTRL_LSBF_MASK)!=FCSPI_TR_CTRL_LSBF_MASK))
        {
            switch(pFcspiHandle->tStatus.u16BitsPerFrame)
            {
                case 16:
                    result_buffer[1] = (uint8_t)(raw_data);
                    result_buffer[0] = (uint8_t)(raw_data>>8u);
                    result_buffer[3] = (uint8_t)(raw_data>>16u);
                    result_buffer[2] = (uint8_t)(raw_data>>24u);
                break;

                case 32:
                    result_buffer[3] = (uint8_t)(raw_data);
                    result_buffer[2] = (uint8_t)(raw_data>>8u);
                    result_buffer[1] = (uint8_t)(raw_data>>16u);
                    result_buffer[0] = (uint8_t)(raw_data>>24u);
                    break;

                default:
                    result_buffer[0] = (uint8_t)(raw_data);
                    result_buffer[1] = (uint8_t)(raw_data>>8u);
                    result_buffer[2] = (uint8_t)(raw_data>>16u);
                    result_buffer[3] = (uint8_t)(raw_data>>24u);
                    break;
            }
        }
        else
        {
            result_buffer[3] = (uint8_t)(raw_data);
            result_buffer[2] = (uint8_t)(raw_data>>8u);
            result_buffer[1] = (uint8_t)(raw_data>>16u);
            result_buffer[0] = (uint8_t)(raw_data>>24u);
        }
    }
    else
    {
        if(((pFcspiHandle->tStatus.u32CurrentTrCtrl&FCSPI_TR_CTRL_LSBF_MASK)!=FCSPI_TR_CTRL_LSBF_MASK))
        {
            switch(pFcspiHandle->tStatus.u16BitsPerFrame)
            {
            case 16:
                for(index = 0;index<raw_length;index++)
                 {
                     result_buffer[index] = (uint8_t)((u32Data&0xff000000)>>24u);
                     u32Data = u32Data<<8u;
                 }
                break;

            default:
                for(index = raw_length;index>0;index--)
                 {
                     result_buffer[index - 1u] = (uint8_t)((u32Data&0xff000000)>>24u);
                     u32Data = u32Data<<8u;
                 }
                break;
            }
        }
        else
        {
            for(index = 0;index<raw_length;index++)
            {
                result_buffer[index] = (uint8_t)((u32Data&0xff000000)>>24u);
                u32Data = u32Data<<8u;
            }
        }
    }
}
#endif

/* caution:write TR_CTRL */
static void FCSpi_Hw_SelectUsePcs(FCSPI_InstanceType eInst,uint32_t *u32PreviousTrCtrl,FCSPI_PCSType ePCS)
{
    uint32_t u32NewTrCtrl = *u32PreviousTrCtrl;

    u32NewTrCtrl &= (~(FCSPI_TR_CTRL_PCS_MASK));
    u32NewTrCtrl |= (((uint32_t)ePCS)  << FCSPI_TR_CTRL_PCS_SHIFT);

    FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[eInst], u32NewTrCtrl);
    *u32PreviousTrCtrl = u32NewTrCtrl;
}

static FCSPI_PrescaleValueType FCSpi_Hw_GetRegPrescalerVal(FCSPI_InstanceType eInst)
{
    return (FCSPI_PrescaleValueType)((FCSPI_HWA_GetTxRxControl(s_apFCSpiInsts[eInst]) &
                                      FCSPI_TR_CTRL_PRESCALE_MASK) >> FCSPI_TR_CTRL_PRESCALE_SHIFT);
}

/* caution:write TR_CTRL */
static void FCSpi_Hw_SetContinuousCommand(FCSPI_InstanceType eInst, uint32_t *u32PreviousTrCtrl, FCSPI_AtomicBoolType eEnable)
{
    uint32_t u32NewTrCtrl = *u32PreviousTrCtrl;

    u32NewTrCtrl &= (~(FCSPI_TR_CTRL_CT_GO_MASK));
    u32NewTrCtrl |= (((uint32_t)eEnable)  << FCSPI_TR_CTRL_CT_GO_SHIFT);

    FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[eInst], u32NewTrCtrl);
    *u32PreviousTrCtrl = u32NewTrCtrl;
}

#if (SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
static void FCSpi_Hw_SetCpolCphaCommand(FCSPI_InstanceType eInst,uint32_t *u32PreviousTrCtrl,FCSPI_SckPolarityType eSckPolarity,FCSPI_SckSamplePhaseType eSckPhase)
{
    uint32_t u32NewTrCtrl = *u32PreviousTrCtrl;

    u32NewTrCtrl &= (~(FCSPI_TR_CTRL_SCK_POL_MASK));
    u32NewTrCtrl |= (((uint32_t)eSckPolarity)  << FCSPI_TR_CTRL_SCK_POL_SHIFT);
    u32NewTrCtrl &= (~(FCSPI_TR_CTRL_SCK_PHA_MASK));
    u32NewTrCtrl |= (((uint32_t)eSckPhase)  << FCSPI_TR_CTRL_SCK_PHA_SHIFT);

    FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[eInst], u32NewTrCtrl);
    *u32PreviousTrCtrl = u32NewTrCtrl;
}
#endif
/*
 * Before call this function, ensure the FCSPI is disabled and in MASTER mode.
 * Src Clk  -> Prescaler -> sck divider -> SCLK
 */
#define FCSPI_CAL_DISTANCE(x, y) ((x) > (y) ? ((x) - (y)) : ((y) - (x)))
typedef struct
{
    uint32_t u32CacheTargetBps;
    uint32_t u32CacheSrcClkHz;
    uint32_t u32CachePrescaleRegVal;
    uint32_t u32CacheBps;
    uint32_t u32CacheSckDiv;
} FCSPI_BaundrateCacheType;
#define FCSPI_PCS_CLK_CACHE_CNT ((uint8_t)2)

/* Often use case, just set the same baundrate for specific external device linked with one FCSPI PCS */
static uint32_t FCSpi_Hw_Master_CalcBaudRate(FCSPI_InstanceType eInst,
                                             const FCSPI_MasterCfgType *pCfg,
                                             uint32_t *pdwPrescaleRegVal, uint32_t *pdwActualSckDiv)
{
    uint32_t u32TargetBps = pCfg->u32BitCntPerSecond;
    uint32_t u32SrcClkHz  = pCfg->u32FCSpiSrcClk;
    uint32_t u32TestFreq = 0U;
    int16_t  s16TestSckDivRegVal = (int16_t)0;
    uint8_t  u8PrescalerRegVal = (uint8_t)0;
    int16_t  s16SckDivLow, s16SckDivHigh;
    uint32_t u32Prescale = 0U;
    uint32_t u32ActualBps = 0U;
    uint32_t u32ActualSckDiv = 0U;
    uint32_t u32ActualPrescaleRegVal = 0U;
    uint32_t u32ThisPrescaleBestBps    = 0U;
    uint32_t u32ThisPrescaleBestSckDiv = 0U;
    uint32_t u32AbsDistance1, u32AbsDistance2;
    uint8_t  u8Index = (uint8_t)0;
    uint8_t  u8Find  = (uint8_t)0;
    uint32_t u32Ret  = 0U;

    static  FCSPI_BaundrateCacheType atCache[FCSPI_INSTANCE_COUNT][FCSPI_PCS_CLK_CACHE_CNT] = {0};
    static  uint8_t atCacheWriteIndex[FCSPI_INSTANCE_COUNT] = {0};

    if (u32SrcClkHz < (u32TargetBps * 2U))
    {
        u32Ret = 0U;
    }
    else
    {
        for (u8Index = (uint8_t)0; u8Index < FCSPI_PCS_CLK_CACHE_CNT; ++u8Index)
        {
            if ((atCache[eInst][u8Index].u32CacheSrcClkHz == u32SrcClkHz) &&
                (atCache[eInst][u8Index].u32CacheTargetBps == u32TargetBps))
            {
                if (NULL != pdwPrescaleRegVal)
                {
                    *pdwPrescaleRegVal = atCache[eInst][u8Index].u32CachePrescaleRegVal;
                }

                if (NULL != pdwActualSckDiv)
                {
                    *pdwActualSckDiv = atCache[eInst][u8Index].u32CacheSckDiv;
                }
                u8Find = (uint8_t)1;
                u32Ret = atCache[eInst][u8Index].u32CacheBps;
            }
        }

        if ((uint8_t)0 == u8Find)
        {
            u32ActualSckDiv = 0U;
            u32ActualPrescaleRegVal = 0U;
            u32ActualBps = (uint32_t)(u32SrcClkHz / ((uint32_t)((((uint32_t)1) <<
                                                                 u32ActualPrescaleRegVal) * (u32ActualSckDiv + (uint32_t)2U))));

            for (u8PrescalerRegVal = (uint8_t)0; u8PrescalerRegVal < FCSPI_PRESCALE_MAX; ++u8PrescalerRegVal)
            {
                s16SckDivLow  = (int16_t)0;
                s16SckDivHigh = (int16_t)255;
                u32Prescale = ((uint32_t)1) << u8PrescalerRegVal;
                u32ThisPrescaleBestSckDiv = 0U;
                u32ThisPrescaleBestBps    = (uint32_t)(u32SrcClkHz / ((uint32_t)(u32Prescale *
                                                                                 (u32ThisPrescaleBestSckDiv + (uint32_t)2U))));

                while (s16SckDivHigh >= s16SckDivLow)
                {
                    s16TestSckDivRegVal = (int16_t)(s16SckDivLow + s16SckDivHigh);
                    s16TestSckDivRegVal = (s16TestSckDivRegVal / (int16_t)2);
                    u32TestFreq = (uint32_t)(u32SrcClkHz /
                                             ((uint32_t)(u32Prescale * ((uint32_t)s16TestSckDivRegVal + (uint32_t)2U))));

                    u32AbsDistance1 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ThisPrescaleBestBps);
                    u32AbsDistance2 = FCSPI_CAL_DISTANCE(u32TargetBps, u32TestFreq);
                    if (u32AbsDistance1 > u32AbsDistance2)
                    {
                        u32ThisPrescaleBestBps = u32TestFreq;
                        u32ThisPrescaleBestSckDiv = (uint32_t)s16TestSckDivRegVal;
                    }

                    if (u32TestFreq == u32TargetBps)
                    {
                        break;
                    }
                    else if (u32TestFreq < u32TargetBps)
                    {
                        s16SckDivHigh = (int16_t)(s16TestSckDivRegVal - (int16_t)1);
                    }
                    else
                    {
                        s16SckDivLow  = (int16_t)(s16TestSckDivRegVal + (int16_t)1);
                    }
                }

                u32AbsDistance1 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ActualBps);
                u32AbsDistance2 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ThisPrescaleBestBps);

                if (u32AbsDistance1 > u32AbsDistance2)
                {
                    if ((FCSPI_BAUDRATE_CALCULATE_DUTY_CYCLE_FIRST == pCfg->eBaudCalcPriority) && (u32ThisPrescaleBestSckDiv % 2) != 0)
                    {
                        if (u32ThisPrescaleBestSckDiv == 255)
                        {
                            u32ThisPrescaleBestSckDiv = 254;
                        }
                        else
                        {
                            u32ActualBps = (uint32_t)(u32SrcClkHz /
                                                      ((uint32_t)(u32Prescale * ((uint32_t)u32ThisPrescaleBestSckDiv + (uint32_t)1U))));

                            u32AbsDistance1 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ActualBps);

                            u32ActualBps = (uint32_t)(u32SrcClkHz /
                                                      ((uint32_t)(u32Prescale * ((uint32_t)u32ThisPrescaleBestSckDiv + (uint32_t)3U))));

                            u32AbsDistance2 = FCSPI_CAL_DISTANCE(u32TargetBps, u32ActualBps);

                            if (u32AbsDistance1 > u32AbsDistance2)
                            {
                                u32ThisPrescaleBestSckDiv = u32ThisPrescaleBestSckDiv + 1U;
                            }
                            else
                            {
                                u32ThisPrescaleBestSckDiv = u32ThisPrescaleBestSckDiv - 1U;
                            }

                        }
                        u32ThisPrescaleBestBps = (uint32_t)(u32SrcClkHz /
                                                            ((uint32_t)(u32Prescale * ((uint32_t)u32ThisPrescaleBestSckDiv + (uint32_t)2U))));
                    }

                    u32ActualBps = u32ThisPrescaleBestBps;
                    u32ActualSckDiv = u32ThisPrescaleBestSckDiv;
                    u32ActualPrescaleRegVal = u8PrescalerRegVal;
                }

                if (u32ThisPrescaleBestBps == u32TargetBps)
                {
                    break;
                }
            }

            if (0U != u32ActualBps)
            {
                atCache[eInst][atCacheWriteIndex[eInst]].u32CacheTargetBps = u32TargetBps;
                atCache[eInst][atCacheWriteIndex[eInst]].u32CacheSrcClkHz = u32SrcClkHz;
                atCache[eInst][atCacheWriteIndex[eInst]].u32CachePrescaleRegVal = u32ActualPrescaleRegVal;
                atCache[eInst][atCacheWriteIndex[eInst]].u32CacheBps = u32ActualBps;
                atCache[eInst][atCacheWriteIndex[eInst]].u32CacheSckDiv = u32ActualSckDiv;
                atCacheWriteIndex[eInst] = (uint8_t)((atCacheWriteIndex[eInst] + (uint8_t)1u) % FCSPI_PCS_CLK_CACHE_CNT);

                if (NULL != pdwActualSckDiv)
                {
                    *pdwActualSckDiv = u32ActualSckDiv;
                }

                if (NULL != pdwPrescaleRegVal)
                {
                    *pdwPrescaleRegVal = u32ActualPrescaleRegVal;
                }
            }

            /* return the actual calculated baud rate */
            u32Ret = u32ActualBps;
        }
    }

    return u32Ret;
}

static void fcspi_read_rx_fifo(FCSPI_HandleType *pFcspiHandle)
{
    uint32_t u32RxWordData     = 0U;
    uint16_t u16ByteCount      = (uint16_t)0;
    uint8_t  u8ByteIndex       = (uint8_t)0;
    uint8_t  u8WordCntInRxFifo = FCSPI_HWA_GetRxFifoStoredCount(s_apFCSpiInsts[(pFcspiHandle->eInstance)]);

    while (u8WordCntInRxFifo > (uint8_t)0)
    {
        u32RxWordData = FCSPI_HWA_ReadData(s_apFCSpiInsts[(pFcspiHandle->eInstance)]);
        /* Get the number of bytes which can be read from this 32 bites */
        if (pFcspiHandle->tStatus.u16BytesCntFrameNeed <=
            (pFcspiHandle->tStatus.u16RxGetByteCntOfCurFrame + (uint16_t)4))
        {
            u16ByteCount = (uint16_t)(pFcspiHandle->tStatus.u16BytesCntFrameNeed -
                                      pFcspiHandle->tStatus.u16RxGetByteCntOfCurFrame);
        }
        else
        {
            u16ByteCount = (uint16_t)4;
        }
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
        if(FCSPI_TRUE ==pFcspiHandle->tStatus.eIsWorkAroundNeeded)
        {
            fcspi_adjust_data_after_receive(u32RxWordData,u16ByteCount,&(pFcspiHandle->tStatus.pbyRxBuff)[pFcspiHandle->tStatus.u16RxIndex],pFcspiHandle);
            (pFcspiHandle->tStatus.u16RxIndex)= (uint16_t)((pFcspiHandle->tStatus.u16RxIndex)+u16ByteCount);
        }
        else
        {
#endif
            /* Generate the word which will be write in buffer. */
            for (u8ByteIndex = (uint8_t)0; u8ByteIndex < u16ByteCount; ++u8ByteIndex)
            {
                (pFcspiHandle->tStatus.pbyRxBuff)[pFcspiHandle->tStatus.u16RxIndex] =
                            (uint8_t)((u32RxWordData >> (uint32_t)((uint32_t)u8ByteIndex * (uint32_t)8)) & (uint8_t)0xFF);
                (pFcspiHandle->tStatus.u16RxIndex)++;
            }
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
        }
#endif
        pFcspiHandle->tStatus.u16RxGetByteCntOfCurFrame =
                    (uint16_t)((pFcspiHandle->tStatus.u16RxGetByteCntOfCurFrame +
                                u16ByteCount) % pFcspiHandle->tStatus.u16BytesCntFrameNeed);

        /* Update internal variable used in transmission. */
        pFcspiHandle->tStatus.u16RxByteCntRemainToGet =
                    (uint16_t)(pFcspiHandle->tStatus.u16RxByteCntRemainToGet - u16ByteCount);
        /* Verify if all bytes were sent. */
        if ((uint16_t)0 == pFcspiHandle->tStatus.u16RxByteCntRemainToGet)
        {
            break;
        }

        u8WordCntInRxFifo--;
    }
}

static void fcspi_write_tx_fifo(FCSPI_HandleType *pFcspiHandle)
{
    uint32_t u32DataToSend       = 0U;
    uint16_t u16ThisSendByteCnt  = (uint16_t)0;
    uint8_t  u8TxFifoFreeWordCnt = (uint8_t)(pFcspiHandle->tStatus.u8TxFifoSize -
                                             (uint8_t)FCSPI_HWA_GetTxFifoStoredCount(s_apFCSpiInsts[pFcspiHandle->eInstance]));
    uint16_t u16BytesTxLeft      = pFcspiHandle->tStatus.u16TxByteCntRemainToSend;

    while ((u8TxFifoFreeWordCnt != (uint8_t)0) && ((uint16_t)0 != u16BytesTxLeft))
    {
        if (FCSPI_TRUE == pFcspiHandle->tStatus.eIsPcsContinuous)
        {
            if ((uint16_t)1 == pFcspiHandle->tStatus.u16TxByteCntRemainToSend)
            {
                /* Disable continuous PCS */
                FCSpi_Hw_SetContinuousCommand(pFcspiHandle->eInstance,(uint32_t *)&pFcspiHandle->tStatus.u32CurrentTrCtrl,FCSPI_FALSE);
                pFcspiHandle->tStatus.u16TxByteCntRemainToSend = (uint16_t)0;
                u16BytesTxLeft = (uint16_t)0;
                break;
            }
        }

        /* Get the number of bytes which can be written in a single 32 bits word. */
        if ((pFcspiHandle->tStatus.u16BytesCntFrameNeed -
             pFcspiHandle->tStatus.u16TxSendByteCntOfCurFrame) <= (uint16_t)4)
        {
            u16ThisSendByteCnt = (uint16_t)(pFcspiHandle->tStatus.u16BytesCntFrameNeed -
                                            pFcspiHandle->tStatus.u16TxSendByteCntOfCurFrame);
        }
        else
        {
            u16ThisSendByteCnt = (uint16_t)4;
        }

        u32DataToSend = 0U;

        if (NULL != pFcspiHandle->tStatus.pbyTxBuff)
        {
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
            if(FCSPI_TRUE == pFcspiHandle->tStatus.eIsWorkAroundNeeded)
            {
                u32DataToSend = fcspi_adjust_data_before_transmit((const uint8_t *)&(pFcspiHandle->tStatus.pbyTxBuff[pFcspiHandle->tStatus.u16TxIndex]),u16ThisSendByteCnt,pFcspiHandle);
                pFcspiHandle->tStatus.u16TxIndex = (uint16_t)(pFcspiHandle->tStatus.u16TxIndex + (uint16_t)(sizeof(uint32_t)));
            }
            else
            {
#endif
                switch (pFcspiHandle->tStatus.u16BytesCntFrameNeed)
                {
                    case 1:
                        u32DataToSend = *((const uint8_t *) & (pFcspiHandle->tStatus.pbyTxBuff[pFcspiHandle->tStatus.u16TxIndex]));
                        pFcspiHandle->tStatus.u16TxIndex = (uint16_t)(pFcspiHandle->tStatus.u16TxIndex + sizeof(uint8_t));
                        break;

                    case 2:
                        u32DataToSend = *((const uint16_t *) & (pFcspiHandle->tStatus.pbyTxBuff[pFcspiHandle->tStatus.u16TxIndex]));
                        pFcspiHandle->tStatus.u16TxIndex = (uint16_t)(pFcspiHandle->tStatus.u16TxIndex + sizeof(uint16_t));
                        break;

                    default:
                        u32DataToSend = *((const uint32_t *) & (pFcspiHandle->tStatus.pbyTxBuff[pFcspiHandle->tStatus.u16TxIndex]));
                        pFcspiHandle->tStatus.u16TxIndex = (uint16_t)(pFcspiHandle->tStatus.u16TxIndex + sizeof(uint32_t));
                        break;
                }
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
            }
#endif
            pFcspiHandle->tStatus.u16TxSendByteCntOfCurFrame =
                        (uint16_t)((pFcspiHandle->tStatus.u16TxSendByteCntOfCurFrame + u16ThisSendByteCnt) %
                                   pFcspiHandle->tStatus.u16BytesCntFrameNeed);
        }

        FCSPI_HWA_WriteData(s_apFCSpiInsts[pFcspiHandle->eInstance], u32DataToSend);
        /* Update internal variable used in transmission. */
        pFcspiHandle->tStatus.u16TxByteCntRemainToSend = (uint16_t)(pFcspiHandle->tStatus.u16TxByteCntRemainToSend - u16ThisSendByteCnt);
        u16BytesTxLeft = pFcspiHandle->tStatus.u16TxByteCntRemainToSend;
        u8TxFifoFreeWordCnt = (uint8_t)(u8TxFifoFreeWordCnt - 1u);
    }
}

/* MASTER side API */
/*----------------------------------------------------------------------------*/
/**
 * @brief Init the FCSpi instance as spi master side
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configuration of the FCSpi, MUST NOT NULL
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_Master_Init(FCSPI_HandleType *pFcspiHandle, const FCSPI_MasterCfgType *pCfg)
{
    uint32_t           u32BaudRate       = 0U;
    uint32_t           u32PrescaleRegVal = 0U;
    uint32_t           u32SckDiv         = 0U;
    FCSPI_TxRxCtrlType tTxRxCtrlCfg      ;
    FCSPI_StatusType   eRet              = FCSPI_STATUS_SUCCESS;

#if FCSPI_DEV_ERROR_REPORT == STD_ON
    if (NULL == pCfg)
    {
            eRet = FCSPI_STATUS_PARAM_ERR;
            FCSPI_ReportDevError(FCSPI_MASTER_INIT_ID, FCSPI_E_PARAM_NULL_CONFIGURATION);
    }
    else
    {
#endif
        if ((pCfg->u16BitCountPerFrame >= (uint16_t)8) &&
            (pCfg->u16BitCountPerFrame <= (uint16_t)4096)) /* TR_CTRL[FRM_SZ] 12bits */
        {
//            if((pCfg->u32Sckdiv)&0xfffffff0)
//            {
                u32BaudRate = FCSpi_Hw_Master_CalcBaudRate(pFcspiHandle->eInstance, pCfg, &u32PrescaleRegVal, &u32SckDiv);
//            }
//            else
//            {
//              u32PrescaleRegVal = (uint32_t)(pCfg->ePrescalerValue);
//              u32SckDiv         = pCfg->u32Sckdiv;
//              u32BaudRate       = (uint32_t)(pCfg->u32FCSpiSrcClk / ((uint32_t)((((uint32_t)1)<<u32PrescaleRegVal) * (u32SckDiv + (uint32_t)2U))));
//            }
            if (0U != u32BaudRate)
            {
                FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_FALSE, FCSPI_FALSE, FCSPI_TRUE);
                FCSPI_HWA_SetMasterMode(s_apFCSpiInsts[pFcspiHandle->eInstance]);
                FCSpi_Hw_SetPcs_2_3_Mode(pFcspiHandle->eInstance, pCfg->ePCS23Mode);
                FCSpi_Hw_SetPin(pFcspiHandle->eInstance, SIN_INPUT_SOUT_OUTPUT, pCfg->ePinOutStatType);

                /* set internal state parameters for spi */
                pFcspiHandle->tStatus.u8TxFifoSize          = (uint8_t)FCSPI_DRV_TX_FIFO_WORD_CNT;
                pFcspiHandle->tStatus.u8RxFifoSize          = (uint8_t)FCSPI_DRV_RX_FIFO_WORD_CNT;
                pFcspiHandle->tStatus.u32DmaDummyData       = 0U;
                pFcspiHandle->tStatus.u16BitsPerFrame       = pCfg->u16BitCountPerFrame;
                pFcspiHandle->tStatus.u16BytesCntFrameNeed  = (uint16_t)(((pCfg->u16BitCountPerFrame + (uint16_t)7)) >> (uint16_t)3);
                pFcspiHandle->tStatus.eIsPcsContinuous      = pCfg->eIsPcsContinuous;
                pFcspiHandle->tStatus.u32FCSpiSrcClk        = pCfg->u32FCSpiSrcClk;
                pFcspiHandle->tStatus.eIsInTransfer         = FCSPI_FALSE;
                pFcspiHandle->tStatus.eBitFirstOrder        = pCfg->eBitFirstOrder;
                pFcspiHandle->tStatus.eTransferTriggerSrc   = pCfg->eTransferTriggerSrc;
                pFcspiHandle->tStatus.eSckPolarity          = pCfg->eSckPolarity;
                pFcspiHandle->tStatus.eSckSamplePhase       = pCfg->eSckSamplePhase;
                pFcspiHandle->tStatus.ePcs                  = pCfg->ePcs;
                pFcspiHandle->tStatus.ePcsPolarity          = pCfg->ePcsPolarity;
                pFcspiHandle->tStatus.u32Baundrate          = u32BaudRate;

                /* DMA require frames of 3 bytes per frame handled as 4 bytes per frame. */
                if (pFcspiHandle->tStatus.u16BytesCntFrameNeed == (uint16_t)3)
                {
                    pFcspiHandle->tStatus.u16BytesCntFrameNeed = (uint16_t)4;
                }
                /* 4 bytes align requirement when > 32bits */
                if (pFcspiHandle->tStatus.u16BytesCntFrameNeed > (uint16_t)4)
                {
                    pFcspiHandle->tStatus.u16BytesCntFrameNeed =
                                (uint16_t)(((((pFcspiHandle->tStatus.u16BytesCntFrameNeed + (uint16_t)3u)) >> (uint16_t)2u)) << (uint16_t)2u);
                }

                pFcspiHandle->tStatus.tTriggerDmaInf  = pCfg->tTriggerDmaInf;
                pFcspiHandle->tStatus.pStopNotifyCb   = pCfg->pStopNotifyCb;
                pFcspiHandle->tStatus.pSemaResetCb    = pCfg->pSemaResetCb;
                pFcspiHandle->tStatus.pSemaTakeCb     = pCfg->pSemaTakeCb;
                pFcspiHandle->tStatus.pSemaPostCb     = pCfg->pSemaPostCb;

                /* Configure the desired PCS polarity */
                FCSpi_Hw_SetOnePcsPolarity(pFcspiHandle->eInstance, pCfg->ePcs, pCfg->ePcsPolarity);

                /* enable sample delay */
                FCSpi_Hw_Master_SetSckLoopbackSample(pFcspiHandle->eInstance, FCSPI_TRUE);

                /* set up the baudrate */
                FCSpi_Hw_Set_SCK_PCS_DIV_Hold(pFcspiHandle->eInstance,
                                              (uint8_t)(u32SckDiv >> 1U),
                                              (uint8_t)(u32SckDiv >> 1U),
                                              (uint8_t)(u32SckDiv >> 1U),
                                              (uint8_t)u32SckDiv); /* write best baudrate scaler to SCKDIV */

                FCSpi_Get_TRCR(&tTxRxCtrlCfg,0);
                /* Write the TCR for this transfer. */
                tTxRxCtrlCfg.eSckPolarity       = pCfg->eSckPolarity;
                tTxRxCtrlCfg.eSckPhase          = pCfg->eSckSamplePhase;
                tTxRxCtrlCfg.ePrescalerValue    = (FCSPI_PrescaleValueType)u32PrescaleRegVal;
                tTxRxCtrlCfg.ePCSSelect         = pCfg->ePcs;
                tTxRxCtrlCfg.eBitFirstOrder     = pCfg->eBitFirstOrder;
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
                if((FCSPI_TRUE == pCfg->eIsPcsContinuous)&&(FCSPI_SCK_SAMPLE_SECOND_EDGE == tTxRxCtrlCfg.eSckPhase)&&(FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR != pCfg->eTransferTriggerSrc))
                {
                    tTxRxCtrlCfg.eByteSwap = FCSPI_TRUE;
                    pFcspiHandle->tStatus.eIsPcsContinuous = FCSPI_FALSE;
                    tTxRxCtrlCfg.eContTransEnable   = FCSPI_FALSE;
                    pFcspiHandle->tStatus.eIsWorkAroundNeeded = FCSPI_TRUE;
                }
                else
                {
#endif
                    tTxRxCtrlCfg.eByteSwap          = FCSPI_FALSE;
                    tTxRxCtrlCfg.eContTransEnable   = pCfg->eIsPcsContinuous;
                    tTxRxCtrlCfg.eContCmdEnable     = FCSPI_FALSE;
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
                }
#endif
                tTxRxCtrlCfg.eRxDisable         = FCSPI_FALSE;
                tTxRxCtrlCfg.eTxDisable         = FCSPI_FALSE;
                tTxRxCtrlCfg.eTransferWidth     = pCfg->eTransferWidthType;
                tTxRxCtrlCfg.u16FrameBitCnt     = pCfg->u16BitCountPerFrame;

                pFcspiHandle->tStatus.u32CurrentTrCtrl = FCSpi_Calculate_TRCR(&tTxRxCtrlCfg);
                FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance], pFcspiHandle->tStatus.u32CurrentTrCtrl);
                FCSPI_HWA_ModuleEnable(s_apFCSpiInsts[pFcspiHandle->eInstance]);
            }
            else
            {
                eRet = FCSPI_STATUS_ERROR;
            }
        }
        else
        {
            eRet = FCSPI_STATUS_PARAM_ERR;
        }
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

/**
 * @brief Deinit the FCSpi
 *
 * @param eInst Which FCSpi Hardware instance
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when deinit the FCSpi successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Deinit(FCSPI_HandleType *pFcspiHandle)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;

    if (FCSPI_TRUE != pFcspiHandle->tStatus.eIsInTransfer)
    {
        /* reset registers,  disabling spi module */
        FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_FALSE, FCSPI_FALSE, FCSPI_TRUE);
    }
    else
    {
        eRet = FCSPI_STATUS_BUSY;
    }

    return eRet;
}

/**
 * @brief Configure the holding time (in us) between PCS and SCK
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldTime(FCSPI_HandleType *pFcspiHandle,
                                                const FCSPI_MasterSckPcsHoldTimeType *pCfg)
{
    FCSPI_StatusType        eRet         = FCSPI_STATUS_SUCCESS;
    uint32_t                u32PCSPCSCycle,
                            u32SCKPCSCycle,
                            u32PCSSCKCycle;
    FCSPI_PrescaleValueType ePrescaler;
    uint32_t                u32PrescaleValue;
    uint32_t                u32ClkAfterScalePerUs;
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    if (NULL == pCfg)
    {
            eRet = FCSPI_STATUS_PARAM_ERR;
        FCSPI_ReportDevError(FCSPI_MASTER_SET_SCKPCS_HOLD_TIME_ID, FCSPI_E_PARAM_NULL_CONFIGURATION);
    }
    else
    {
#endif
        /* disable FCSPI first */
        eRet = FCSpi_Hw_Disable(pFcspiHandle->eInstance);
        if (FCSPI_STATUS_SUCCESS == eRet)
        {
            ePrescaler = FCSpi_Hw_GetRegPrescalerVal(pFcspiHandle->eInstance);
            u32PrescaleValue = FCSpi_Hw_PrescalerRegToActualVal(ePrescaler);
            if (0U != u32PrescaleValue) /* actually unreachable */
            {
                u32ClkAfterScalePerUs = (uint32_t)(pFcspiHandle->tStatus.u32FCSpiSrcClk /
                                                   u32PrescaleValue / (uint32_t)1000000);
                u32PCSPCSCycle = pCfg->u32PCStoPCSHoldUs * u32ClkAfterScalePerUs;
                u32SCKPCSCycle = pCfg->u32SCKtoPCSHoldUs * u32ClkAfterScalePerUs;
                u32PCSSCKCycle = pCfg->u32PCStoSCKHoldUs * u32ClkAfterScalePerUs;

                if (u32PCSPCSCycle > (uint32_t)257U)
                {
                    u32PCSPCSCycle = (uint32_t)257U;
                }

                if (u32SCKPCSCycle > (uint32_t)256U)
                {
                    u32SCKPCSCycle = (uint32_t)256U;
                }

                if (u32PCSSCKCycle > (uint32_t)256U)
                {
                    u32PCSSCKCycle = (uint32_t)256U;
                }

                if (u32PCSPCSCycle < (uint32_t)2U)
                {
                    u32PCSPCSCycle = (uint32_t)2U;
                }

                if (u32SCKPCSCycle == (uint32_t)0)
                {
                    u32SCKPCSCycle = (uint32_t)1U;
                }

                if (u32PCSSCKCycle == (uint32_t)0U)
                {
                    u32PCSSCKCycle = (uint32_t)1U;
                }

                FCSpi_Hw_Set_SCK_PCS_Hold(pFcspiHandle->eInstance,
                                          (uint8_t)(u32SCKPCSCycle - 1U),
                                          (uint8_t)(u32PCSSCKCycle - 1U),
                                          (uint8_t)(u32PCSPCSCycle - 2U));
                /* Enable module */
                FCSPI_HWA_ModuleEnable(s_apFCSpiInsts[pFcspiHandle->eInstance]);
            }
            else
            {
                eRet = FCSPI_STATUS_ERROR;
            }
        }
        else
        {
            eRet = FCSPI_STATUS_BUSY;
        }
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

/**
 * @brief Configure the holding time (in SCK/100) between PCS and SCK
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldSckPercentage(
            FCSPI_HandleType *pFcspiHandle, const FCSPI_MasterSckPcsHoldSckCycleType *pCfg)
{
    uint8_t             u8PCSPCSCycle;
    uint8_t             u8SCKPCSCycle;
    uint8_t             u8PCSSCKCycle;
    uint8_t             u8SckDiv;
    FCSPI_StatusType    eRet = FCSPI_STATUS_SUCCESS;
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    if (NULL == pCfg)
    {
            eRet = FCSPI_STATUS_PARAM_ERR;
        FCSPI_ReportDevError(FCSPI_MASTER_SET_SCKPCS_HOLD_SCK_PERCENT_ID, FCSPI_E_PARAM_NULL_CONFIGURATION);
    }
    else
    {
#endif
        /* disable FCSPI first */
        eRet = FCSpi_Hw_Disable(pFcspiHandle->eInstance);
        if (FCSPI_STATUS_SUCCESS == eRet)
        {
            FCSpi_Hw_Get_SCK_PCS_DIV_Hold(pFcspiHandle->eInstance, NULL, NULL, NULL, &u8SckDiv);

            u8PCSPCSCycle = (uint8_t)((uint32_t)pCfg->u32PCStoPCSHoldPercentage *
                                      (uint32_t)u8SckDiv / (uint32_t)100);
            u8SCKPCSCycle = (uint8_t)((uint32_t)pCfg->u32SCKtoPCSHoldPercentage *
                                      (uint32_t)u8SckDiv / (uint32_t)100);
            u8PCSSCKCycle = (uint8_t)((uint32_t)pCfg->u32PCStoSCKHoldPercentage *
                                      (uint32_t)u8SckDiv / (uint32_t)100);

            if (u8PCSPCSCycle < (uint8_t)2)
            {
                u8PCSPCSCycle = (uint8_t)2;
            }

            if (u8SCKPCSCycle == (uint8_t)0)
            {
                u8SCKPCSCycle = (uint8_t)1;
            }

            if (u8PCSSCKCycle == (uint8_t)0)
            {
                u8PCSSCKCycle = (uint8_t)1;
            }

            FCSpi_Hw_Set_SCK_PCS_Hold(pFcspiHandle->eInstance,
                                      (uint8_t)(u8SCKPCSCycle - (uint8_t)1),
                                      (uint8_t)(u8PCSSCKCycle - (uint8_t)1),
                                      (uint8_t)(u8PCSPCSCycle - (uint8_t)2));
            /* Enable module */
            FCSPI_HWA_ModuleEnable(s_apFCSpiInsts[pFcspiHandle->eInstance]);
        }
        else
        {
            eRet = FCSPI_STATUS_BUSY;
        }
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

/**
 * @brief Select the PCS to use and configure
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Parameters about PCS configuration, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SelectPcs(FCSPI_HandleType *pFcspiHandle, const FCSPI_MasterPcsConfType *pCfg)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    if (NULL == pCfg)
    {
            eRet = FCSPI_STATUS_PARAM_ERR;
        FCSPI_ReportDevError(FCSPI_MASTER_SELECT_PCS_ID, FCSPI_E_PARAM_NULL_CONFIGURATION);
    }
    else
    {
#endif
        eRet = FCSpi_Hw_Disable(pFcspiHandle->eInstance);
        if (FCSPI_STATUS_SUCCESS == eRet)
        {
            FCSpi_Hw_SetOnePcsPolarity(pFcspiHandle->eInstance, pCfg->ePcs, pCfg->ePolarity);
            FCSPI_HWA_ModuleEnable(s_apFCSpiInsts[pFcspiHandle->eInstance]);
            FCSpi_Hw_SelectUsePcs(pFcspiHandle->eInstance,(uint32_t *)&pFcspiHandle->tStatus.u32CurrentTrCtrl,pCfg->ePcs);
        }
        else
        {
            eRet = FCSPI_STATUS_BUSY;
        }
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

static void fcspi_master_clean_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInInterrupt)
{
    pFcspiHandle->tStatus.eIsInTransfer = FCSPI_FALSE;

    if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc)
    {
        FCSpi_Hw_SetRxTxDmaEnableStatus(pFcspiHandle->eInstance, FCSPI_FALSE, FCSPI_FALSE);
    }
    else
    {
        FCSpi_Hw_DisableSomeInterrupts(pFcspiHandle->eInstance,
                                       FCSPI_INT_EN_RFIE(1) | FCSPI_INT_EN_TFIE(1));
    }

    FCSpi_Hw_DisableSomeInterrupts(pFcspiHandle->eInstance,
                                   FCSPI_INT_EN_RFOIE(1) | FCSPI_INT_EN_TFUIE(1) | FCSPI_INT_EN_TCIE(1));
    FCSpi_Hw_ClearSomeStatusW1CFlag(pFcspiHandle->eInstance,
                                    FCSPI_STATUS_RX_FO(1) | FCSPI_STATUS_TX_FU(1) | FCSPI_STATUS_TCF(1));

    if (FCSPI_TRUE == bIsInInterrupt)
    {
        if (NULL != pFcspiHandle->tStatus.pStopNotifyCb)
        {
            pFcspiHandle->tStatus.pStopNotifyCb(pFcspiHandle, FCSPI_TRUE);
        }

        if (pFcspiHandle->tStatus.u8WaitSemaphore)
        {
            pFcspiHandle->tStatus.pSemaPostCb(pFcspiHandle, FCSPI_TRUE);
            pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
        }
    }
    else
    {
        if (NULL != pFcspiHandle->tStatus.pStopNotifyCb)
        {
            pFcspiHandle->tStatus.pStopNotifyCb(pFcspiHandle, FCSPI_FALSE);
        }

        if (pFcspiHandle->tStatus.u8WaitSemaphore)
        {
            pFcspiHandle->tStatus.pSemaPostCb(pFcspiHandle, FCSPI_FALSE);
            pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
        }
    }
}

static void fcspi_master_abort_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInISR)
{
    fcspi_master_clean_transfer(pFcspiHandle, bIsInISR);

    /* clean the fifo */
    FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
    FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* for shifter */
}

static  void fcspi_master_dma_rx_err_interrupt(void *pFcspiHandle)
{
    ((FCSPI_HandleType*)pFcspiHandle)->tStatus.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
    fcspi_master_abort_transfer((FCSPI_HandleType*)pFcspiHandle, FCSPI_TRUE);
}

static void fcspi_master_dma_rx_finish_interrupt(void *pFcspiHandle)
{
    (void)(pFcspiHandle); /* in master mode, the tx trigger the sclk output, so when rx finish, ignore. */
}

static  void fcspi_master_dma_tx_err_interrupt(void *pFcspiHandle)
{
    ((FCSPI_HandleType*)pFcspiHandle)->tStatus.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
    fcspi_master_abort_transfer((FCSPI_HandleType*)pFcspiHandle, FCSPI_TRUE);
}

static  void fcspi_master_dma_tx_finish_interrupt(void *pFcspiHandle)
{
    if (FCSPI_TRUE == ((FCSPI_HandleType*)pFcspiHandle)->tStatus.eIsPcsContinuous)
    {
        FCSpi_Hw_SetContinuousCommand(((FCSPI_HandleType*)pFcspiHandle)->eInstance,(uint32_t *)&(((FCSPI_HandleType*)pFcspiHandle)->tStatus.u32CurrentTrCtrl),FCSPI_FALSE);
    }

    ((FCSPI_HandleType*)pFcspiHandle)->tStatus.u16TxByteCntRemainToSend = (uint16_t)0;
    ((FCSPI_HandleType*)pFcspiHandle)->tStatus.u16RxByteCntRemainToGet  = (uint16_t)0;

    /* DMA -> TX FIFO -> PIN, DMA send to tx fifo finish, enable tx fifo finish interrupt */
    FCSpi_Hw_EnableTransmitCompleteInterrupt(((FCSPI_HandleType*)pFcspiHandle)->eInstance);
}

/* if enter transfer state, return success, others, not start tranfer */
static FCSPI_StatusType fcspi_master_async_transfer_bytes(FCSPI_HandleType *pFcspiHandle,
                                                          const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer,
                                                          uint16_t u16TransferByteCnt)
{
    DMA_ChannelCfgType   tDmaTxChnlCfg      = {0};
    uint8_t              u8DmaTxBlkByteCnt  = (uint8_t)1;
    DMA_ChannelCfgType   tDmaRxChnlCfg      = {0};
    uint8_t              u8DmaRxBlkByteCnt  = (uint8_t)1;
    FCSPI_StatusType     eRet               = FCSPI_STATUS_SUCCESS;
    uint32_t             u32StatRegVal      = 0u;

    if ((uint16_t)0 != pFcspiHandle->tStatus.u16BytesCntFrameNeed)
    {
        if ((uint16_t)0 != u16TransferByteCnt)
        {
            if ((u16TransferByteCnt % pFcspiHandle->tStatus.u16BytesCntFrameNeed) == (uint16_t)0)
            {
                u32StatRegVal = FCSPI_HWA_GetStatus(s_apFCSpiInsts[pFcspiHandle->eInstance]);
                if ((FCSPI_TRUE != pFcspiHandle->tStatus.eIsInTransfer) &&
                    (!FCSpi_Hw_ChkBusy(u32StatRegVal)))
                {
                    if (!FCSpi_Hw_ChkBusy(FCSPI_HWA_GetStatus(s_apFCSpiInsts[pFcspiHandle->eInstance])))
                    {
                        FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
                        FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* ensure clear data in shifter */
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
                        if((FCSPI_TRUE == pFcspiHandle->tStatus.eIsWorkAroundNeeded))
                        {
                            FCSpi_Hw_SetFrameSizeCommand(pFcspiHandle->eInstance,(uint32_t *)&pFcspiHandle->tStatus.u32CurrentTrCtrl,(uint16_t)(u16TransferByteCnt<<3u));
                            pFcspiHandle->tStatus.u16BytesCntWorkAroundFrameNeed = pFcspiHandle->tStatus.u16BytesCntFrameNeed;
                            pFcspiHandle->tStatus.u16BytesCntFrameNeed = u16TransferByteCnt;
                        }
#endif
                        /* if pcs need continuous, set command continuous bit */
                        if (pFcspiHandle->tStatus.eIsPcsContinuous)
                        {
                            FCSpi_Hw_SetContinuousCommand(pFcspiHandle->eInstance,(uint32_t *)&pFcspiHandle->tStatus.u32CurrentTrCtrl,FCSPI_TRUE);
                        }

                        pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_OK;

                        FCSPI_HWA_SetWatermark(s_apFCSpiInsts[pFcspiHandle->eInstance], (uint8_t)0, (uint8_t)2);

                        FCSpi_Hw_ClearSomeStatusW1CFlag(pFcspiHandle->eInstance, FCSPI_DRV_STATUS_REG_W1C_U32);
                        FCSpi_Hw_EnableMoreInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_TFUIE(1));

                        /* if rx needed, enable overflow interrupt and rx */
                        if (NULL != pReceiveBuffer)
                        {
                            FCSpi_Hw_EnableMoreInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_RFOIE(1));
                            pFcspiHandle->tStatus.u16RxByteCntRemainToGet = u16TransferByteCnt;
                            pFcspiHandle->tStatus.u32CurrentTrCtrl&=(~FCSPI_TR_CTRL_RX_MSK_MASK);
                            FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance],pFcspiHandle->tStatus.u32CurrentTrCtrl);
                        }
                        else
                        {
                            pFcspiHandle->tStatus.u16RxByteCntRemainToGet = (uint16_t)0;
                            pFcspiHandle->tStatus.u32CurrentTrCtrl|=FCSPI_TR_CTRL_RX_MSK_MASK;
                            FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance],pFcspiHandle->tStatus.u32CurrentTrCtrl);
                        }

                        if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc)
                        {
                            /* TX */
                            tDmaTxChnlCfg.u8ChannelPriority     = pFcspiHandle->tStatus.tTriggerDmaInf.u8TxDMAChannelPriority;
                            tDmaTxChnlCfg.bDestAddrLoopbackEn   = false;
                            tDmaTxChnlCfg.bSrcAddrLoopbackEn    = false;
                            tDmaTxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
                            tDmaTxChnlCfg.bSrcCircularBufferEn  = false;
                            tDmaTxChnlCfg.bDestCircularBufferEn = false;

                            switch (pFcspiHandle->tStatus.u16BytesCntFrameNeed)
                            {
                                case 1:
                                    tDmaTxChnlCfg.eSrcDataSize          = DMA_TRANSFER_SIZE_1B;
                                    tDmaTxChnlCfg.eDestDataSize         = DMA_TRANSFER_SIZE_1B;
                                    tDmaTxChnlCfg.bSrcBlockOffsetEn     = true;
                                    tDmaTxChnlCfg.s32BlockOffset        = (int32_t)1;
                                    u8DmaTxBlkByteCnt                   = (uint8_t)1;
                                    break;

                                case 2:
                                    tDmaTxChnlCfg.eSrcDataSize          = DMA_TRANSFER_SIZE_2B;
                                    tDmaTxChnlCfg.eDestDataSize         = DMA_TRANSFER_SIZE_2B;
                                    tDmaTxChnlCfg.bSrcBlockOffsetEn     = true;
                                    tDmaTxChnlCfg.s32BlockOffset        = (int32_t)2;
                                    u8DmaTxBlkByteCnt                   = (uint8_t)2;
                                    break;

                                default:
                                    tDmaTxChnlCfg.eSrcDataSize          = DMA_TRANSFER_SIZE_4B;
                                    tDmaTxChnlCfg.eDestDataSize         = DMA_TRANSFER_SIZE_4B;
                                    tDmaTxChnlCfg.bSrcBlockOffsetEn     = true;
                                    tDmaTxChnlCfg.s32BlockOffset        = (int32_t)4;
                                    u8DmaTxBlkByteCnt                   = (uint8_t)4;
                                    break;
                            }

                            tDmaTxChnlCfg.u16BlockCount      = (uint16_t)(u16TransferByteCnt / u8DmaTxBlkByteCnt);
                            tDmaTxChnlCfg.bDestBlockOffsetEn = false;

                            tDmaTxChnlCfg.bTransferCompleteIntEn = true;
                            tDmaTxChnlCfg.bTransferErrorIntEn    = true;
                            tDmaTxChnlCfg.completedata           = pFcspiHandle;
                            tDmaTxChnlCfg.errdata                = pFcspiHandle;
                            tDmaTxChnlCfg.pTransferCompleteNotify = fcspi_master_dma_tx_finish_interrupt;
                            tDmaTxChnlCfg.pTransferErrorNotify    = fcspi_master_dma_tx_err_interrupt;
                            switch (pFcspiHandle->eInstance)
                            {
                                case FCSPI_0:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_TX;
                                    break;

                                case FCSPI_1:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_TX;
                                    break;

                                case FCSPI_2:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_TX;
                                    break;

                                case FCSPI_3:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                                    break;

                                default:
                                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                                    break;
                            }

                            tDmaTxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
                            tDmaTxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
                            tDmaTxChnlCfg.pDestBuffer  = FCSPI_HWA_GetTxDataAddr(s_apFCSpiInsts[pFcspiHandle->eInstance]);
                            tDmaTxChnlCfg.u32BlockSize = (uint32_t)u8DmaTxBlkByteCnt;

                            if (NULL != pSendBuffer)
                            {
                                tDmaTxChnlCfg.pSrcBuffer = pSendBuffer;
                            }
                            else
                            {
                                tDmaTxChnlCfg.bSrcBlockOffsetEn = false; /* if send buffer is NULL, just send dummy data, MUST fix the source to the dummy variable */
                                tDmaTxChnlCfg.pSrcBuffer        = &(pFcspiHandle->tStatus.u32DmaDummyData);
                                tDmaTxChnlCfg.s32BlockOffset    = (int32_t)0;
                            }
                            DMA_InitChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaTxInstanceHandle,&tDmaTxChnlCfg);

                            /* RX */
                            /* if needed, configure the DMA Rx function */
                            if (NULL != pReceiveBuffer)
                            {
                                tDmaRxChnlCfg.u8ChannelPriority     = pFcspiHandle->tStatus.tTriggerDmaInf.u8RxDMAChannelPriority;
                                tDmaRxChnlCfg.bDestAddrLoopbackEn   = false;
                                tDmaRxChnlCfg.bSrcAddrLoopbackEn    = false;
                                tDmaRxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
                                tDmaRxChnlCfg.bSrcCircularBufferEn  = false;
                                tDmaRxChnlCfg.bDestCircularBufferEn = false;

                                switch (pFcspiHandle->tStatus.u16BytesCntFrameNeed)
                                {
                                    case 1:
                                        tDmaRxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_1B;
                                        tDmaRxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_1B;
                                        tDmaRxChnlCfg.bDestBlockOffsetEn     = true;
                                        tDmaRxChnlCfg.s32BlockOffset         = (int32_t)1;
                                        u8DmaRxBlkByteCnt                    = (uint8_t)1;
                                        break;

                                    case 2:
                                        tDmaRxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_2B;
                                        tDmaRxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_2B;
                                        tDmaRxChnlCfg.bDestBlockOffsetEn     = true;
                                        tDmaRxChnlCfg.s32BlockOffset         = (int32_t)2;
                                        u8DmaRxBlkByteCnt                    = (uint8_t)2;
                                        break;

                                    default:
                                        tDmaRxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_4B;
                                        tDmaRxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_4B;
                                        tDmaRxChnlCfg.bDestBlockOffsetEn     = true;
                                        tDmaRxChnlCfg.s32BlockOffset         = (int32_t)4;
                                        u8DmaRxBlkByteCnt                    = (uint8_t)4;
                                        break;
                                }

                                tDmaRxChnlCfg.u16BlockCount      = (uint16_t)(u16TransferByteCnt / u8DmaRxBlkByteCnt);
                                tDmaRxChnlCfg.bSrcBlockOffsetEn  = false;

                                tDmaRxChnlCfg.bTransferCompleteIntEn = true;
                                tDmaRxChnlCfg.bTransferErrorIntEn    = true;
                                tDmaRxChnlCfg.completedata           = pFcspiHandle;
                                tDmaRxChnlCfg.errdata                = pFcspiHandle;
                                tDmaRxChnlCfg.pTransferCompleteNotify = fcspi_master_dma_rx_finish_interrupt;
                                tDmaRxChnlCfg.pTransferErrorNotify    = fcspi_master_dma_rx_err_interrupt;
                                switch (pFcspiHandle->eInstance)
                                {
                                    case FCSPI_0:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_RX;
                                        break;

                                    case FCSPI_1:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_RX;
                                        break;

                                    case FCSPI_2:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_RX;
                                        break;

                                    case FCSPI_3:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                                        break;

                                    default:
                                        tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                                        break;
                                }

                                tDmaRxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
                                tDmaRxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
                                tDmaRxChnlCfg.pSrcBuffer   = FCSPI_HWA_GetRxDataAddr(s_apFCSpiInsts[pFcspiHandle->eInstance]);
                                tDmaRxChnlCfg.pDestBuffer  = pReceiveBuffer;
                                tDmaRxChnlCfg.u32BlockSize = (uint32_t)u8DmaRxBlkByteCnt;
                                DMA_InitChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaRxInstanceHandle,&tDmaRxChnlCfg);
                                DMA_StartChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaRxInstanceHandle);
                            }
                            DMA_StartChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaTxInstanceHandle);
                            pFcspiHandle->tStatus.eIsInTransfer = FCSPI_TRUE;

                            if (pReceiveBuffer)
                            {
                                FCSpi_Hw_SetRxTxDmaEnableStatus(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE);
                            }
                            else
                            {
                                /* only enable TX DMA */
                                FCSpi_Hw_SetRxTxDmaEnableStatus(pFcspiHandle->eInstance, FCSPI_FALSE, FCSPI_TRUE);
                            }
                        }
                        else
                        {
                            pFcspiHandle->tStatus.pbyTxBuff                  = pSendBuffer;
                            pFcspiHandle->tStatus.pbyRxBuff                  = pReceiveBuffer;
                            pFcspiHandle->tStatus.u16TxIndex                 = (uint16_t)0;
                            pFcspiHandle->tStatus.u16RxIndex                 = (uint16_t)0;
                            pFcspiHandle->tStatus.u16TxSendByteCntOfCurFrame = (uint16_t)0;
                            pFcspiHandle->tStatus.u16RxGetByteCntOfCurFrame  = (uint16_t)0;
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
                            if(FCSPI_TRUE == pFcspiHandle->tStatus.eIsWorkAroundNeeded)
                            {
                                pFcspiHandle->tStatus.u16TxByteCntRemainToSend   = u16TransferByteCnt&(((FCSPI_TR_CTRL_FRM_SZ_MASK+1u)>>3u)-1u);
                            }
                            else
                            {
#endif
                                pFcspiHandle->tStatus.u16TxByteCntRemainToSend   = u16TransferByteCnt;
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
                            }
#endif
                            if (FCSPI_TRUE == pFcspiHandle->tStatus.eIsPcsContinuous)
                            {
                                /* continuous transfer need an extra word to negate PCS */
                                pFcspiHandle->tStatus.u16TxByteCntRemainToSend++;
                            }
                            pFcspiHandle->tStatus.eIsInTransfer = FCSPI_TRUE;

                            if (NULL != pReceiveBuffer) /* need rx fifo */
                            {
                                FCSpi_Hw_EnableMoreInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_RFIE(1) | FCSPI_INT_EN_TFIE(1));
                            }
                            else
                            {
                                FCSpi_Hw_EnableMoreInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_TFIE(1));
                            }
                        }
                        eRet = FCSPI_STATUS_SUCCESS;
                    }
                    else
                    {
                        eRet = FCSPI_STATUS_BUSY;
                    }
                }
                else
                {
                    eRet = FCSPI_STATUS_BUSY;
                }
            }
            else
            {
                eRet = FCSPI_STATUS_ERROR;
            }
        }
        else
        {
            eRet = FCSPI_STATUS_NO_DATA;
        }
    }
    else
    {
        eRet = FCSPI_STATUS_ERROR;
    }

    return eRet;
}

/**
 * @brief Send and receive asynchronously
 * 1) If the trigger source is driver user poll, this api not support this mode.
 * 2) If the trigger source is interrupt or DMA, this api will start the transmission, then return immediately.
 *    After transmission stop, it will trigger an interrupt.
 *    During the transmission, the send data buffer and receive data buffer
 *    should keep valid until the transmission stop.
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when start transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_AsyncTransfer(FCSPI_HandleType *pFcspiHandle, const FCSPI_AsyncDataInfType *pCfg)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;

#if FCSPI_DEV_ERROR_REPORT == STD_ON
    if (NULL == pCfg)
    {
            eRet = FCSPI_STATUS_PARAM_ERR;
        FCSPI_ReportDevError(FCSPI_ASYNC_TRANSFER_ID, FCSPI_E_PARAM_NULL_CONFIGURATION);
    }
    else
    {
#endif
        if (FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL != pFcspiHandle->tStatus.eTransferTriggerSrc)
        {
            if (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_apFCSpiInsts[pFcspiHandle->eInstance]))
            {
                eRet = fcspi_master_async_transfer_bytes(pFcspiHandle,
                                                         pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                                                         (uint16_t)(pCfg->u16FrameCount * pFcspiHandle->tStatus.u16BytesCntFrameNeed));
            }
            else
            {
                eRet = fcspi_slave_async_transfer_bytes(pFcspiHandle, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                                                        (uint16_t)(pFcspiHandle->tStatus.u16BytesCntFrameNeed * pCfg->u16FrameCount));
            }
        }
        else
        {
            eRet = FCSPI_STATUS_ERROR;
        }
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

/**
 * @brief Send and receive synchronously
 * 1) If the semaphore callbacks are configured,
 *    and the driver is configured transmitting triggered by interrupt, or by DMA,
 *    the driver will use semaphore to wait the transmission stopped.
 *    In this case, the timeout value is passed to semaphore callback directly.
 * 2) If the semaphore callbacks are not configured,
 *    this api will poll the status when triggered by interrupt or DMA,
 *    or poll to trigger the transmission when the mode is "FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL".
 *    In this case, the timeout value has different meaning for different trigger mode.
 *    Read the source code for detail.
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_SyncTransfer(FCSPI_HandleType *pFcspiHandle, const FCSPI_SyncDataInfType *pCfg)
{
    FCSPI_StatusType          tStatus;
    FCSPI_SemaphoreStatType   tSemaStat;
    FCSPI_StatusType          eRet = FCSPI_STATUS_SUCCESS;
    FCSPI_AtomicBoolType      bIsMaster;
    uint32_t                  u32MonitorTimeout  = 0xFFFFFFFFu;
    uint16_t                  u16RxRemain = (uint16_t)0;
    uint16_t                  u16TxRemain = (uint16_t)0;
    uint16_t                  u16PreRxRemain = (uint16_t)0;
    uint16_t                  u16PreTxRemain = (uint16_t)0;
    uint32_t                  u32TryTimeout = 0xFFFFFFFFu;
    FCSPI_AtomicBoolType      bIsBlockType = FCSPI_TRUE;
    bIsMaster = (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_apFCSpiInsts[pFcspiHandle->eInstance])) ? FCSPI_TRUE : FCSPI_FALSE;
    FCSPI_AtomicBoolType      bNeedExitLoop = FCSPI_FALSE;

#if FCSPI_DEV_ERROR_REPORT == STD_ON
    if (NULL == pCfg)
    {
            eRet = FCSPI_STATUS_PARAM_ERR;
        FCSPI_ReportDevError(FCSPI_SYNC_TRANSFER_ID, FCSPI_E_PARAM_NULL_CONFIGURATION);
    }
    else
    {
#endif
        if ((uint16_t)0 != pCfg->u16FrameCount)
        {
            if ((NULL != pFcspiHandle->tStatus.pSemaResetCb) &&
                (NULL != pFcspiHandle->tStatus.pSemaTakeCb) &&
                (NULL != pFcspiHandle->tStatus.pSemaPostCb) &&
                ((FCSPI_TRANSFER_TRIGGER_SRC_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc) ||
                 (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc)))
            {
                if (FCSPI_SEMAPHORE_SUCCESS == pFcspiHandle->tStatus.pSemaResetCb(pFcspiHandle))
                {
                    pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)1;

                    if (FCSPI_TRUE == bIsMaster)
                    {
                        tStatus = fcspi_master_async_transfer_bytes(pFcspiHandle, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                                                                    (uint16_t)(pFcspiHandle->tStatus.u16BytesCntFrameNeed * pCfg->u16FrameCount));
                    }
                    else
                    {
                        tStatus = fcspi_slave_async_transfer_bytes(pFcspiHandle, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                                                                  (uint16_t)(pFcspiHandle->tStatus.u16BytesCntFrameNeed * pCfg->u16FrameCount));
                    }

                    if (FCSPI_STATUS_SUCCESS == tStatus)
                    {
                        tSemaStat = pFcspiHandle->tStatus.pSemaTakeCb(pFcspiHandle, pCfg->u32Timeout);
                        if (FCSPI_SEMAPHORE_FAIL == tSemaStat)
                        {
                            pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
                            pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }

                            eRet = FCSPI_STATUS_ERROR;
                        }
                        else if (FCSPI_SEMAPHORE_TIMEOUT == tSemaStat)
                        {
                            pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
                            pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }
                            eRet = FCSPI_STATUS_SYNC_TIMEOUT;
                        }
                        else
                        {
                            pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
                            if (FCSPI_TRANSFER_OK != pFcspiHandle->tStatus.eTransferStat)
                            {
                                eRet = FCSPI_STATUS_TRANSFER_FAIL;
                            }
                            else
                            {
                                eRet = FCSPI_STATUS_SUCCESS;
                            }
                        }
                    }
                    else
                    {
                        pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
                        eRet = tStatus;
                    }
                }
                else
                {
                    eRet = FCSPI_STATUS_ERROR;
                }
            }
            else
            {
                if (FCSPI_TRUE == bIsMaster)
                {
                    tStatus = fcspi_master_async_transfer_bytes(pFcspiHandle, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                            (uint16_t)(pFcspiHandle->tStatus.u16BytesCntFrameNeed * pCfg->u16FrameCount));
                }
                else
                {
                    tStatus = fcspi_slave_async_transfer_bytes(pFcspiHandle, pCfg->pSendBuffer, pCfg->pReceiveBuffer,
                                                               (uint16_t)(pFcspiHandle->tStatus.u16BytesCntFrameNeed * pCfg->u16FrameCount));
                }

                if (FCSPI_STATUS_SUCCESS == tStatus)
                {
                    if (pCfg->u32Timeout > 0u)
                    {
                        u32TryTimeout = pCfg->u32Timeout;
                        bIsBlockType = FCSPI_FALSE;
                    }
                    else
                    {
                        bIsBlockType = FCSPI_TRUE;
                    }

                    if (FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL == pFcspiHandle->tStatus.eTransferTriggerSrc)
                    {
                        if (FCSPI_TRUE == bIsMaster)
                        {
                            do
                            {
                                eRet = fcspi_master_trigger(pFcspiHandle, FCSPI_FALSE);
                                if (FCSPI_FALSE == bIsBlockType)
                                {
                                    u32TryTimeout--;
                                    if (0u == u32TryTimeout)
                                    {
                                        break;
                                    }
                                }
                            } while (FCSPI_STATUS_TRIGGER_OK == eRet);
                        }
                        else
                        {
                            do
                            {
                                eRet = fcspi_slave_trigger(pFcspiHandle, FCSPI_FALSE);

                                if (FCSPI_FALSE == bIsBlockType)
                                {
                                    u32TryTimeout--;
                                    if (0u == u32TryTimeout)
                                    {
                                        break;
                                    }
                                }
                            } while (FCSPI_STATUS_TRIGGER_OK == eRet);
                        }

                        if (FCSPI_STATUS_TRIGGER_FINISH == eRet)
                        {
                            eRet = FCSPI_STATUS_SUCCESS;
                        }
                        else if ((FCSPI_FALSE == bIsBlockType) && (0u == u32TryTimeout))
                        {
                            pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }
                            eRet = FCSPI_STATUS_SYNC_TIMEOUT;
                        }
                        else
                        {
                            eRet = FCSPI_STATUS_TRANSFER_FAIL;
                        }
                    }
                    else if ((FCSPI_TRANSFER_TRIGGER_SRC_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc) ||
                             (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc))
                    {
                        u32MonitorTimeout = 0xfffff00u; /* ensure 1s */

                        u16PreRxRemain = pFcspiHandle->tStatus.u16RxByteCntRemainToGet;
                        u16PreTxRemain = pFcspiHandle->tStatus.u16TxByteCntRemainToSend;

                        while (FCSPI_TRUE == pFcspiHandle->tStatus.eIsInTransfer)
                        {
                            u32MonitorTimeout--;
                            if (0u == u32MonitorTimeout)
                            {
                                bNeedExitLoop = FCSPI_FALSE;
                                u16RxRemain = pFcspiHandle->tStatus.u16RxByteCntRemainToGet;
                                u16TxRemain = pFcspiHandle->tStatus.u16TxByteCntRemainToSend;
                                if (((u16PreRxRemain == u16RxRemain) && ((uint16_t)0 != u16RxRemain)) ||
                                    ((u16PreTxRemain == u16TxRemain) && ((uint16_t)0 != u16TxRemain)))
                                {
                                    pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_ABORT;
                                    if (FCSPI_TRUE == bIsMaster)
                                    {
                                        fcspi_master_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                                    }
                                    else
                                    {
                                        fcspi_slave_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                                    }

                                    bNeedExitLoop = FCSPI_TRUE;
                                }
                                else
                                {
                                    u16PreRxRemain = u16RxRemain;
                                    u16PreTxRemain = u16TxRemain;
                                    u32MonitorTimeout = 0xfffff00u;

                                    if (FCSPI_FALSE == bIsBlockType)
                                    {
                                        u32TryTimeout--;
                                        if (0u == u32TryTimeout)
                                        {
                                            bNeedExitLoop = FCSPI_TRUE;
                                        }
                                    }
                                }

                                if (FCSPI_TRUE == bNeedExitLoop)
                                {
                                    break;
                                }
                            }
                        }

                        if ((FCSPI_FALSE == bIsBlockType) && (0u == u32TryTimeout))
                        {
                            pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_ABORT;
                            if (FCSPI_TRUE == bIsMaster)
                            {
                                fcspi_master_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }
                            else
                            {
                                fcspi_slave_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                            }
                            eRet = FCSPI_STATUS_SYNC_TIMEOUT;
                        }
                        else if (FCSPI_TRANSFER_OK == pFcspiHandle->tStatus.eTransferStat)
                        {
                            eRet = FCSPI_STATUS_SUCCESS;
                        }
                        else
                        {
                            eRet = FCSPI_STATUS_TRANSFER_FAIL;
                        }
                    }
                    else
                    {
                        pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_ABORT;
                        if (FCSPI_TRUE == bIsMaster)
                        {
                            fcspi_master_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                        }
                        else
                        {
                            fcspi_slave_abort_transfer(pFcspiHandle, FCSPI_FALSE);
                        }

                        eRet = FCSPI_STATUS_TRANSFER_FAIL;
                    }
                }
                else
                {
                    eRet = tStatus;
                }
            }
        }
        else
        {
            eRet = FCSPI_STATUS_SUCCESS;
        }
#if FCSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

static FCSPI_StatusType fcspi_master_trigger(
            FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr)
{
    uint32_t   u32StatusRegValue;
    FCSPI_StatusType eRet = FCSPI_STATUS_TRIGGER_OK;

    /* if an error is detected the transfer will be aborted */
    u32StatusRegValue = FCSPI_HWA_GetStatus(s_apFCSpiInsts[pFcspiHandle->eInstance]);

    /* if tx need more data but hungry, and has data, sth wrong */
    if (FCSpi_Hw_ChkTxFifoUnderrun(u32StatusRegValue) &&
        (NULL != pFcspiHandle->tStatus.pbyTxBuff))
    {
        pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
        fcspi_master_abort_transfer(pFcspiHandle, bIsInIsr);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_TX_FAIL;
    }
    /* if rx need more space but overflow, and has space to store, sth wrong */
    else if (FCSpi_Hw_ChkRxFifoOverflow(u32StatusRegValue) &&
             (NULL != pFcspiHandle->tStatus.pbyRxBuff))
    {
        pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
        fcspi_master_abort_transfer(pFcspiHandle, bIsInIsr);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_RX_FAIL;
    }
    /* rx data ready */
    else
    {
        if (FCSpi_Hw_ChkRxGreaterThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != pFcspiHandle->tStatus.u16RxByteCntRemainToGet)
            {
                fcspi_read_rx_fifo(pFcspiHandle);
            }
        }

        /* transmit some, need add more */
        if (FCSpi_Hw_ChkTxEqualOrLessThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != pFcspiHandle->tStatus.u16TxByteCntRemainToSend)
            {
                fcspi_write_tx_fifo(pFcspiHandle);
            }
        }

        if ((uint16_t)0 == pFcspiHandle->tStatus.u16TxByteCntRemainToSend)
        {
            /* disable tx interrupt. enable tx completion interrupt.*/
            FCSpi_Hw_DisableTransmitDataInterrupt(pFcspiHandle->eInstance);
            FCSpi_Hw_EnableTransmitCompleteInterrupt(pFcspiHandle->eInstance);

            /* tx finish first, if rx also finish, just check completion */
            if ((uint16_t)0 == pFcspiHandle->tStatus.u16RxByteCntRemainToGet)
            {
#if(!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
                if(FCSPI_TRUE == pFcspiHandle->tStatus.eIsWorkAroundNeeded)
                {
                    pFcspiHandle->tStatus.u16BytesCntFrameNeed = pFcspiHandle->tStatus.u16BytesCntWorkAroundFrameNeed;
                }
#endif
                u32StatusRegValue = FCSPI_HWA_GetStatus(s_apFCSpiInsts[pFcspiHandle->eInstance]);
                if (FCSpi_Hw_ChkTransferComplete(u32StatusRegValue))
                {
                    fcspi_master_clean_transfer(pFcspiHandle, bIsInIsr);
                    eRet = FCSPI_STATUS_TRIGGER_FINISH;
                }
            }
        }
    }

    return eRet;
}

/******************************************************************************/

static void fcspi_slave_clean_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInInterrupt)
{
    pFcspiHandle->tStatus.eIsInTransfer = FCSPI_FALSE;

    if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc)
    {
        FCSpi_Hw_SetRxTxDmaEnableStatus(pFcspiHandle->eInstance, FCSPI_FALSE, FCSPI_FALSE);
    }
    else
    {
        FCSpi_Hw_DisableSomeInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_RFIE(1) | FCSPI_INT_EN_TFIE(1));
    }

    FCSpi_Hw_DisableSomeInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_RFOIE(1) | FCSPI_INT_EN_TFUIE(1));
    FCSpi_Hw_ClearSomeStatusW1CFlag(pFcspiHandle->eInstance, FCSPI_STATUS_RX_FO(1) | FCSPI_STATUS_TX_FU(1));

    if (FCSPI_TRUE == bIsInInterrupt)
    {
        if (NULL != pFcspiHandle->tStatus.pStopNotifyCb)
        {
            pFcspiHandle->tStatus.pStopNotifyCb(pFcspiHandle, FCSPI_TRUE);
        }

        if (pFcspiHandle->tStatus.u8WaitSemaphore)
        {
            pFcspiHandle->tStatus.pSemaPostCb(pFcspiHandle, FCSPI_TRUE);
            pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
        }
    }
    else
    {
        if (NULL != pFcspiHandle->tStatus.pStopNotifyCb)
        {
            pFcspiHandle->tStatus.pStopNotifyCb(pFcspiHandle, FCSPI_FALSE);
        }

        if (pFcspiHandle->tStatus.u8WaitSemaphore)
        {
            pFcspiHandle->tStatus.pSemaPostCb(pFcspiHandle, FCSPI_FALSE);
            pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
        }
    }
}

static void fcspi_slave_abort_transfer(FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInInterrupt)
{
    fcspi_slave_clean_transfer(pFcspiHandle, bIsInInterrupt);
    FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
    FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* for shifter */
}

/**
 * @brief Init the FCSpi instance as spi slave side
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg Configuration of the FCSpi
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_Slave_Init(FCSPI_HandleType *pFcspiHandle, const FCSPI_SlaveCfgType *pCfg)
{
    FCSPI_TxRxCtrlType tTxRxCtrlCfg;
    FCSPI_StatusType   eRet = FCSPI_STATUS_SUCCESS;

#if FCSPI_DEV_ERROR_REPORT == STD_ON
    if (NULL == pCfg)
    {
            eRet = FCSPI_STATUS_PARAM_ERR;
        FCSPI_ReportDevError(FCSPI_SLAVE_INIT_ID, FCSPI_E_PARAM_NULL_CONFIGURATION);
    }
    else
    {
#endif
        pFcspiHandle->tStatus.eBitFirstOrder          = pCfg->eBitFirstOrder;
        pFcspiHandle->tStatus.u16BitsPerFrame         = pCfg->u16BitCountPerFrame;
        pFcspiHandle->tStatus.eTransferTriggerSrc     = pCfg->eTransferTriggerSrc;
        pFcspiHandle->tStatus.tTriggerDmaInf          = pCfg->tTriggerDmaInf;
        pFcspiHandle->tStatus.pStopNotifyCb           = pCfg->pStopNotifyCb;
        pFcspiHandle->tStatus.pSemaResetCb            = pCfg->pSemaResetCb;
        pFcspiHandle->tStatus.pSemaTakeCb             = pCfg->pSemaTakeCb;
        pFcspiHandle->tStatus.pSemaPostCb             = pCfg->pSemaPostCb;
        pFcspiHandle->tStatus.eSckPolarity            = pCfg->eSckPolarity;
        pFcspiHandle->tStatus.eSckSamplePhase         = pCfg->eSckSamplePhase;
        pFcspiHandle->tStatus.ePcs                    = pCfg->ePcs;
        pFcspiHandle->tStatus.ePcsPolarity            = pCfg->ePcsPolarity;

        pFcspiHandle->tStatus.u16BytesCntFrameNeed   =
                    (uint16_t)((pFcspiHandle->tStatus.u16BitsPerFrame + (uint16_t)7) >> (uint16_t)3);

        /* DMA use 4 bytes/frame. */
        if ((uint16_t)3 == pFcspiHandle->tStatus.u16BytesCntFrameNeed)
        {
            pFcspiHandle->tStatus.u16BytesCntFrameNeed = (uint16_t)4;
        }

        /* FCSPI require 4 bytes align when > 32bits. */
        if (pFcspiHandle->tStatus.u16BytesCntFrameNeed > (uint16_t)4)
        {
            pFcspiHandle->tStatus.u16BytesCntFrameNeed = (uint16_t)
                                                                    ((((pFcspiHandle->tStatus.u16BytesCntFrameNeed + (uint16_t)3)) >> (uint16_t)2) << (uint16_t)2);
        }

        pFcspiHandle->tStatus.eIsInTransfer = FCSPI_FALSE;

        FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_FALSE, FCSPI_FALSE, FCSPI_TRUE);
        FCSPI_HWA_SetSlaveMode(s_apFCSpiInsts[pFcspiHandle->eInstance]);
        FCSpi_Hw_SetPcs_2_3_Mode(pFcspiHandle->eInstance, pCfg->ePCS23Mode);
        FCSpi_Hw_SetPin(pFcspiHandle->eInstance, SIN_INPUT_SOUT_OUTPUT, pCfg->ePinOutStatType);
        /* set fifo size param */
        pFcspiHandle->tStatus.u8TxFifoSize     = (uint8_t)FCSPI_DRV_TX_FIFO_WORD_CNT;
        pFcspiHandle->tStatus.u8RxFifoSize     = (uint8_t)FCSPI_DRV_RX_FIFO_WORD_CNT;
        pFcspiHandle->tStatus.u32DmaDummyData   = 0xFFu;

        /* Set polarity */
        FCSpi_Hw_SetOnePcsPolarity(pFcspiHandle->eInstance, pCfg->ePcs, pCfg->ePcsPolarity);

        /* Write the TCR for this transfer */
        tTxRxCtrlCfg.eSckPolarity       = pCfg->eSckPolarity;
        tTxRxCtrlCfg.eSckPhase          = pCfg->eSckSamplePhase;
        tTxRxCtrlCfg.ePrescalerValue    = FCSPI_PRESCALE_1; /* not use */
        tTxRxCtrlCfg.ePCSSelect         = pCfg->ePcs;
        tTxRxCtrlCfg.eBitFirstOrder     = pCfg->eBitFirstOrder;
        tTxRxCtrlCfg.eByteSwap          = FCSPI_FALSE;
        tTxRxCtrlCfg.eContTransEnable   = FCSPI_FALSE; /* not use */
        tTxRxCtrlCfg.eContCmdEnable     = FCSPI_FALSE; /* not use */
        tTxRxCtrlCfg.eRxDisable         = FCSPI_FALSE;
        tTxRxCtrlCfg.eTxDisable         = FCSPI_FALSE;
        tTxRxCtrlCfg.eTransferWidth     = pCfg->eTransferWidthType;
        tTxRxCtrlCfg.u16FrameBitCnt     = pCfg->u16BitCountPerFrame;

        pFcspiHandle->tStatus.u32CurrentTrCtrl = FCSpi_Calculate_TRCR(&tTxRxCtrlCfg);
        FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance],pFcspiHandle->tStatus.u32CurrentTrCtrl);
        FCSPI_HWA_ModuleEnable(s_apFCSpiInsts[pFcspiHandle->eInstance]);

#if FCSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eRet;
}

static  void fcspi_slave_dma_rx_err_interrupt(void *pFcspiHandle)
{
    ((FCSPI_HandleType *)pFcspiHandle)->tStatus.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
    fcspi_slave_abort_transfer((FCSPI_HandleType *)pFcspiHandle, FCSPI_TRUE);
}

static  void fcspi_slave_dma_rx_finish_interrupt(void *pFcspiHandle)
{
    fcspi_slave_abort_transfer((FCSPI_HandleType *)pFcspiHandle, FCSPI_TRUE);
}

static  void fcspi_slave_dma_tx_err_interrupt(void *pFcspiHandle)
{
    ((FCSPI_HandleType *)pFcspiHandle)->tStatus.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
    fcspi_slave_abort_transfer((FCSPI_HandleType *)pFcspiHandle, FCSPI_TRUE);
}

static  void fcspi_slave_dma_tx_finish_interrupt(void *pFcspiHandle)
{
    FCSpi_Hw_SetRxTxDmaEnableStatus(((FCSPI_HandleType *)pFcspiHandle)->eInstance, FCSPI_TRUE, FCSPI_FALSE);
}

static FCSPI_StatusType fcspi_slave_async_transfer_bytes(FCSPI_HandleType *pFcspiHandle,
                                                         const uint8_t *pSendBuffer, uint8_t *pReceiveBuffer, uint16_t u16TransferByteCnt)
{
    DMA_ChannelCfgType   tDmaTxChnlCfg = {0};
    uint8_t              u8DmaTxBlkByteCnt = (uint8_t)1;
    DMA_ChannelCfgType   tDmaRxChnlCfg = {0};
    uint8_t              u8DmaRxBlkByteCnt = (uint8_t)1;
    FCSPI_StatusType     eRet = FCSPI_STATUS_SUCCESS;

    if ((NULL == pSendBuffer) && (NULL == pReceiveBuffer))
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if ((uint16_t)0 == pFcspiHandle->tStatus.u16BytesCntFrameNeed)
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if ((uint16_t)0 == u16TransferByteCnt)
    {
        eRet = FCSPI_STATUS_NO_DATA;
    }
    else if ((uint16_t)0 != (u16TransferByteCnt % pFcspiHandle->tStatus.u16BytesCntFrameNeed))
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if (FCSPI_TRUE == pFcspiHandle->tStatus.eIsInTransfer)
    {
        eRet = FCSPI_STATUS_BUSY;
    }
    else
    {
        pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_OK;
        FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE);
        FCSpi_Hw_Reset(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE, FCSPI_FALSE); /* for shifter */

        FCSpi_Hw_ClearSomeStatusW1CFlag(pFcspiHandle->eInstance, FCSPI_DRV_STATUS_REG_W1C_U32);

        /* in slave mode, rx and tx all enabled */
        FCSpi_Hw_EnableMoreInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_TFUIE(1) | FCSPI_INT_EN_RFOIE(1));

        pFcspiHandle->tStatus.pbyTxBuff  = pSendBuffer;
        pFcspiHandle->tStatus.pbyRxBuff  = pReceiveBuffer;
        pFcspiHandle->tStatus.u16TxIndex = (uint16_t)0;
        pFcspiHandle->tStatus.u16RxIndex = (uint16_t)0;

        if (FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR == pFcspiHandle->tStatus.eTransferTriggerSrc)
        {
            FCSPI_HWA_SetWatermark(s_apFCSpiInsts[pFcspiHandle->eInstance], (uint8_t)0, (uint8_t)3);

            /* TX */
            tDmaTxChnlCfg.u8ChannelPriority     = pFcspiHandle->tStatus.tTriggerDmaInf.u8TxDMAChannelPriority;
            tDmaTxChnlCfg.bDestAddrLoopbackEn   = false;
            tDmaTxChnlCfg.bSrcAddrLoopbackEn    = false;
            tDmaTxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
            tDmaTxChnlCfg.bSrcCircularBufferEn  = false;
            tDmaTxChnlCfg.bDestCircularBufferEn = false;

            switch (pFcspiHandle->tStatus.u16BytesCntFrameNeed)
            {
                case 1:
                    tDmaTxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_1B;
                    tDmaTxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_1B;
                    tDmaTxChnlCfg.bSrcBlockOffsetEn      = true;
                    tDmaTxChnlCfg.s32BlockOffset         = (int32_t)1;
                    u8DmaTxBlkByteCnt                    = (uint8_t)1;
                    break;

                case 2:
                    tDmaTxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_2B;
                    tDmaTxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_2B;
                    tDmaTxChnlCfg.bSrcBlockOffsetEn      = true;
                    tDmaTxChnlCfg.s32BlockOffset         = (int32_t)2;
                    u8DmaTxBlkByteCnt                    = (uint8_t)2;
                    break;

                default:
                    tDmaTxChnlCfg.eSrcDataSize           = DMA_TRANSFER_SIZE_4B;
                    tDmaTxChnlCfg.eDestDataSize          = DMA_TRANSFER_SIZE_4B;
                    tDmaTxChnlCfg.bSrcBlockOffsetEn      = true;
                    tDmaTxChnlCfg.s32BlockOffset         = (int32_t)4;
                    u8DmaTxBlkByteCnt                    = (uint8_t)4;
                    break;
            }

            tDmaTxChnlCfg.u16BlockCount               = (uint16_t)(u16TransferByteCnt / u8DmaTxBlkByteCnt);
            tDmaTxChnlCfg.bDestBlockOffsetEn          = false;
            tDmaTxChnlCfg.bTransferCompleteIntEn = true;
            tDmaTxChnlCfg.bTransferErrorIntEn    = true;
            tDmaTxChnlCfg.completedata           = pFcspiHandle;
            tDmaTxChnlCfg.errdata                = pFcspiHandle;
            tDmaTxChnlCfg.pTransferCompleteNotify = fcspi_slave_dma_tx_finish_interrupt;
            tDmaTxChnlCfg.pTransferErrorNotify    = fcspi_slave_dma_tx_err_interrupt;
            switch (pFcspiHandle->eInstance)
            {
                case FCSPI_0:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_TX;
                    break;

                case FCSPI_1:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_TX;
                    break;

                case FCSPI_2:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_TX;
                    break;

                case FCSPI_3:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                    break;

                default:
                    tDmaTxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_TX;
                    break;
            }

            tDmaTxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
            tDmaTxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
            tDmaTxChnlCfg.pDestBuffer  = FCSPI_HWA_GetTxDataAddr(s_apFCSpiInsts[pFcspiHandle->eInstance]);
            tDmaTxChnlCfg.u32BlockSize = (uint32_t)u8DmaTxBlkByteCnt;

            if (NULL != pSendBuffer)
            {
                pFcspiHandle->tStatus.u16TxByteCntRemainToSend = u16TransferByteCnt;
                tDmaTxChnlCfg.pSrcBuffer                       = pSendBuffer;
            }
            else
            {
                pFcspiHandle->tStatus.u16TxByteCntRemainToSend = (uint16_t)0;
                tDmaTxChnlCfg.bSrcBlockOffsetEn                = false; /* if send buffer is NULL, just send dummy data, MUST fix the source to the dummy variable */
                tDmaTxChnlCfg.s32BlockOffset                   = (int32_t)0;
                tDmaTxChnlCfg.pSrcBuffer                       = &(pFcspiHandle->tStatus.u32DmaDummyData);
            }
            DMA_InitChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaTxInstanceHandle,&tDmaTxChnlCfg);

            /* RX */
            tDmaRxChnlCfg.u8ChannelPriority     = pFcspiHandle->tStatus.tTriggerDmaInf.u8RxDMAChannelPriority;
            tDmaRxChnlCfg.bDestAddrLoopbackEn   = false;
            tDmaRxChnlCfg.bSrcAddrLoopbackEn    = false;
            tDmaRxChnlCfg.bAutoStop             = true; /* auto stop dma after send finish */
            tDmaRxChnlCfg.bSrcCircularBufferEn  = false;
            tDmaRxChnlCfg.bDestCircularBufferEn = false;

            switch (pFcspiHandle->tStatus.u16BytesCntFrameNeed)
            {
                case 1:
                    tDmaRxChnlCfg.eDestDataSize      = DMA_TRANSFER_SIZE_1B;
                    tDmaRxChnlCfg.eSrcDataSize       = DMA_TRANSFER_SIZE_1B;
                    tDmaRxChnlCfg.bDestBlockOffsetEn = true;
                    tDmaRxChnlCfg.s32BlockOffset     = (int32_t)1;
                    u8DmaRxBlkByteCnt                = (uint8_t)1;
                    break;

                case 2:
                    tDmaRxChnlCfg.eDestDataSize      = DMA_TRANSFER_SIZE_2B;
                    tDmaRxChnlCfg.eSrcDataSize       = DMA_TRANSFER_SIZE_2B;
                    tDmaRxChnlCfg.bDestBlockOffsetEn = true;
                    tDmaRxChnlCfg.s32BlockOffset     = (int32_t)2;
                    u8DmaRxBlkByteCnt                = (uint8_t)2;
                    break;

                default:
                    tDmaRxChnlCfg.eDestDataSize      = DMA_TRANSFER_SIZE_4B;
                    tDmaRxChnlCfg.eSrcDataSize       = DMA_TRANSFER_SIZE_4B;
                    tDmaRxChnlCfg.bDestBlockOffsetEn = true;
                    tDmaRxChnlCfg.s32BlockOffset     = (int32_t)4;
                    u8DmaRxBlkByteCnt                = (uint8_t)4;
                    break;
            }

            tDmaRxChnlCfg.u16BlockCount               = (uint16_t)(u16TransferByteCnt / u8DmaRxBlkByteCnt);
            tDmaRxChnlCfg.bSrcBlockOffsetEn           = false;
            tDmaRxChnlCfg.bTransferCompleteIntEn = true;
            tDmaRxChnlCfg.bTransferErrorIntEn    = true;
            tDmaRxChnlCfg.completedata           = pFcspiHandle;
            tDmaRxChnlCfg.errdata                = pFcspiHandle;
            tDmaRxChnlCfg.pTransferCompleteNotify = fcspi_slave_dma_rx_finish_interrupt;
            tDmaRxChnlCfg.pTransferErrorNotify    = fcspi_slave_dma_rx_err_interrupt;
            switch (pFcspiHandle->eInstance)
            {
                case FCSPI_0:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI0_RX;
                    break;

                case FCSPI_1:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI1_RX;
                    break;

                case FCSPI_2:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI2_RX;
                    break;

                case FCSPI_3:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                    break;

                default:
                    tDmaRxChnlCfg.eTriggerSrc = DMA_REQ_FCSPI3_RX;
                    break;
            }

            tDmaRxChnlCfg.eSrcIncMode  = DMA_INCREMENT_DISABLE;
            tDmaRxChnlCfg.eDestIncMode = DMA_INCREMENT_DISABLE;
            tDmaRxChnlCfg.pSrcBuffer   = FCSPI_HWA_GetRxDataAddr(s_apFCSpiInsts[pFcspiHandle->eInstance]);
            tDmaRxChnlCfg.u32BlockSize = (uint32_t)u8DmaRxBlkByteCnt;

            if (NULL != pReceiveBuffer)
            {
                pFcspiHandle->tStatus.u16RxByteCntRemainToGet = u16TransferByteCnt;
                tDmaRxChnlCfg.pDestBuffer                     = pReceiveBuffer;
            }
            else
            {
                pFcspiHandle->tStatus.u16RxByteCntRemainToGet = (uint16_t)0;
                tDmaRxChnlCfg.pDestBuffer                     = &(pFcspiHandle->tStatus.u32DmaDummyData);
                tDmaRxChnlCfg.bDestBlockOffsetEn              = false;
                tDmaRxChnlCfg.s32BlockOffset                  = (int32_t)0;

            }

            DMA_InitChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaRxInstanceHandle,&tDmaRxChnlCfg);

            pFcspiHandle->tStatus.eIsInTransfer = FCSPI_TRUE;

            DMA_StartChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaRxInstanceHandle);
            DMA_StartChannel(pFcspiHandle->tStatus.tTriggerDmaInf.pDmaTxInstanceHandle);
            FCSpi_Hw_SetRxTxDmaEnableStatus(pFcspiHandle->eInstance, FCSPI_TRUE, FCSPI_TRUE);
        }
        else
        {
            FCSPI_HWA_SetWatermark(s_apFCSpiInsts[pFcspiHandle->eInstance], (uint8_t)0, (uint8_t)2);

            if (NULL == pFcspiHandle->tStatus.pbyTxBuff)
            {
                pFcspiHandle->tStatus.u16TxByteCntRemainToSend = (uint16_t)0;
                pFcspiHandle->tStatus.u32CurrentTrCtrl|=FCSPI_TR_CTRL_TX_MSK_MASK;
                FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance],pFcspiHandle->tStatus.u32CurrentTrCtrl);
            }
            else
            {
                pFcspiHandle->tStatus.u16TxByteCntRemainToSend = u16TransferByteCnt;
                pFcspiHandle->tStatus.u32CurrentTrCtrl&=(~FCSPI_TR_CTRL_TX_MSK_MASK);
                FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance],pFcspiHandle->tStatus.u32CurrentTrCtrl);
            }

            if (NULL == pFcspiHandle->tStatus.pbyRxBuff)
            {
                pFcspiHandle->tStatus.u16RxByteCntRemainToGet = (uint16_t)0;
                pFcspiHandle->tStatus.u32CurrentTrCtrl|=FCSPI_TR_CTRL_RX_MSK_MASK;
                FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance],pFcspiHandle->tStatus.u32CurrentTrCtrl);
            }
            else
            {
                pFcspiHandle->tStatus.u16RxByteCntRemainToGet = u16TransferByteCnt;
                pFcspiHandle->tStatus.u32CurrentTrCtrl&=(~FCSPI_TR_CTRL_RX_MSK_MASK);
                FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance],pFcspiHandle->tStatus.u32CurrentTrCtrl);
            }

            pFcspiHandle->tStatus.u16RxGetByteCntOfCurFrame   = (uint16_t)0;
            pFcspiHandle->tStatus.u16TxSendByteCntOfCurFrame  = (uint16_t)0;
            pFcspiHandle->tStatus.eIsPcsContinuous          = FCSPI_FALSE;
            pFcspiHandle->tStatus.eIsInTransfer             = FCSPI_TRUE;

            if (NULL != pReceiveBuffer) /* need rx fifo */
            {
                FCSpi_Hw_EnableMoreInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_RFIE(1));
            }

            if (NULL != pSendBuffer)
            {
                FCSpi_Hw_EnableMoreInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_TFIE(1));
            }
        }
    }

    return eRet;
}

static FCSPI_StatusType fcspi_slave_trigger(
            FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInISR)
{
    uint32_t   u32StatusRegValue;
    uint16_t   u16RemainTx = (uint16_t)0;
    uint16_t   u16RemainRx = (uint16_t)0;
    FCSPI_StatusType eRet = FCSPI_STATUS_TRIGGER_OK;

    /* If an error is detected the transfer will be aborted */
    u32StatusRegValue = FCSPI_HWA_GetStatus(s_apFCSpiInsts[pFcspiHandle->eInstance]);
    if (FCSpi_Hw_ChkTxFifoUnderrun(u32StatusRegValue) &&
        (NULL != pFcspiHandle->tStatus.pbyTxBuff))
    {
        pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_TX_FAIL;
        fcspi_slave_abort_transfer(pFcspiHandle, bIsInISR);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_TX_FAIL;
    }
    else if (FCSpi_Hw_ChkRxFifoOverflow(u32StatusRegValue) &&
             (NULL != pFcspiHandle->tStatus.pbyRxBuff))
    {
        pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_RX_FAIL;
        fcspi_slave_abort_transfer(pFcspiHandle, bIsInISR);
        eRet = FCSPI_STATUS_TRIGGER_ABORT_RX_FAIL;
    }
    /* rx data ready */
    else
    {
        if (FCSpi_Hw_ChkRxGreaterThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != pFcspiHandle->tStatus.u16RxByteCntRemainToGet)
            {
                fcspi_read_rx_fifo(pFcspiHandle);
            }
        }

        /* transmit some, need add more */
        if (FCSpi_Hw_ChkTxEqualOrLessThanWater(u32StatusRegValue))
        {
            if ((uint16_t)0 != pFcspiHandle->tStatus.u16TxByteCntRemainToSend)
            {
                fcspi_write_tx_fifo(pFcspiHandle);
            }
        }

        if ((uint16_t)0 == pFcspiHandle->tStatus.u16TxByteCntRemainToSend)
        {
            /* Disable TX flag. Software buffer is empty.*/
            FCSpi_Hw_DisableTransmitDataInterrupt(pFcspiHandle->eInstance);
        }

        if ((uint16_t)0 == pFcspiHandle->tStatus.u16RxByteCntRemainToGet)
        {
            FCSpi_Hw_DisableReceiveDataInterrupt(pFcspiHandle->eInstance);
        }

        u16RemainTx = pFcspiHandle->tStatus.u16TxByteCntRemainToSend;
        u16RemainRx = pFcspiHandle->tStatus.u16RxByteCntRemainToGet;
        if (((uint16_t)0 == u16RemainTx) && ((uint16_t)0 == u16RemainRx))
        {
            FCSpi_Hw_DisableSomeInterrupts(pFcspiHandle->eInstance, FCSPI_INT_EN_RFOIE(1) | FCSPI_INT_EN_TFUIE(1));

            if (pFcspiHandle->tStatus.pStopNotifyCb)
            {
                pFcspiHandle->tStatus.pStopNotifyCb(pFcspiHandle, bIsInISR);
            }

            if (pFcspiHandle->tStatus.u8WaitSemaphore)
            {
                pFcspiHandle->tStatus.pSemaPostCb(pFcspiHandle, bIsInISR);
                pFcspiHandle->tStatus.u8WaitSemaphore = (uint8_t)0;
            }

            pFcspiHandle->tStatus.eIsInTransfer = FCSPI_FALSE;
            eRet = FCSPI_STATUS_TRIGGER_FINISH;
        }
    }

    return eRet;
}

/*----------------------------------------------------------------------------*/
/**
 * @brief If it's in transfer, get its stat, or get the last transfer's stat.
 *
 * @param eInst Which FCSpi Hardware instance
 * @param pCfg the transfer information, can be null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when the last transfer is finish successfully. Others, busy or error occur.
 */
FCSPI_StatusType FCSPI_GetLatestTransferStat(FCSPI_HandleType *pFcspiHandle, FCSPI_TransferRemainInfType *pCfg)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;

    if (NULL != pCfg)
    {
        pCfg->u32ByteCountReceiveRemained  = pFcspiHandle->tStatus.u16RxByteCntRemainToGet;
        pCfg->u32ByteCountSendRemained = pFcspiHandle->tStatus.u16TxByteCntRemainToSend;
    }

    if (FCSPI_TRANSFER_OK != pFcspiHandle->tStatus.eTransferStat)
    {
        eRet = FCSPI_STATUS_ERROR;
    }
    else if (FCSPI_TRUE == pFcspiHandle->tStatus.eIsInTransfer)
    {
        eRet = FCSPI_STATUS_BUSY;
    }
    else
    {
        eRet = FCSPI_STATUS_SUCCESS;
    }

    return eRet;
}

/**
 * @brief Set Spi Operation Mode
 *
 * @param eInst Which FCSpi Hardware instance
 * @param SckPorality FCSPI_SCK_ACTIVE_HIGH or FCSPI_SCK_ACTIVE_LOW
 * @param SckPhase FCSPI_SCK_SAMPLE_FIRST_EDGE or FCSPI_SCK_SAMPLE_SECOND_EDGE
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when successfully. Others, error.
 */
FCSPI_StatusType FCSPI_SetClockPolarityClockPhase(FCSPI_HandleType *pFcspiHandle, FCSPI_SckPolarityType SckPorality, FCSPI_SckSamplePhaseType SckPhase)
{
    FCSPI_StatusType eRet = FCSPI_STATUS_SUCCESS;
#if (!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
    FCSPI_TxRxCtrlType tNewTrCtrl ;
#endif
    if((SckPorality != pFcspiHandle->tStatus.eSckPolarity) || (SckPhase != pFcspiHandle->tStatus.eSckSamplePhase))
    {
        if(FCSPI_FALSE == pFcspiHandle->tStatus.eIsInTransfer)
        {
#if (!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
            FCSpi_Get_TRCR(&tNewTrCtrl,pFcspiHandle->tStatus.u32CurrentTrCtrl);
            if((FCSPI_TRUE == pFcspiHandle->tStatus.eIsWorkAroundNeeded))
            {
                pFcspiHandle->tStatus.u16BytesCntFrameNeed = pFcspiHandle->tStatus.u16BytesCntWorkAroundFrameNeed;
                pFcspiHandle->tStatus.eIsWorkAroundNeeded = FCSPI_FALSE;
                pFcspiHandle->tStatus.eIsPcsContinuous = FCSPI_TRUE;

                tNewTrCtrl.eContTransEnable = FCSPI_TRUE;
                tNewTrCtrl.u16FrameBitCnt = pFcspiHandle->tStatus.u16BitsPerFrame;
                tNewTrCtrl.eByteSwap = FCSPI_FALSE;
            }
            else
            {
                if((SckPhase == FCSPI_SCK_SAMPLE_SECOND_EDGE)&&(FCSPI_TRUE == pFcspiHandle->tStatus.eIsPcsContinuous)&&(FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR != pFcspiHandle->tStatus.eTransferTriggerSrc))
                {
                    pFcspiHandle->tStatus.eIsWorkAroundNeeded = FCSPI_TRUE;
                    pFcspiHandle->tStatus.eIsPcsContinuous = FCSPI_FALSE;

                    tNewTrCtrl.eContTransEnable = FCSPI_FALSE;
                    tNewTrCtrl.eByteSwap = FCSPI_TRUE;
                }
            }
            pFcspiHandle->tStatus.eSckSamplePhase = SckPhase;
            tNewTrCtrl.eSckPhase = SckPhase;
            pFcspiHandle->tStatus.u32CurrentTrCtrl = FCSpi_Calculate_TRCR(&tNewTrCtrl);
            FCSPI_HWA_SetTxRxControl(s_apFCSpiInsts[pFcspiHandle->eInstance], pFcspiHandle->tStatus.u32CurrentTrCtrl);
#else
            FCSpi_Hw_SetCpolCphaCommand(pFcspiHandle->eInstance,(uint32_t *)&pFcspiHandle->tStatus.u32CurrentTrCtrl,SckPorality,SckPhase);
#endif
        }
        else
        {
            eRet= FCSPI_STATUS_BUSY;
        }
    }
    return eRet;
}

/**
 * @brief Abort current transfer if exist, or just recovery the hardware.
 *
 * @param eInst Which FCSpi Hardware instance
 */
void FCSPI_AbortTransfer(FCSPI_HandleType *pFcspiHandle)
{
    pFcspiHandle->tStatus.eTransferStat = FCSPI_TRANSFER_ABORT;

    if (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_apFCSpiInsts[pFcspiHandle->eInstance]))
    {
        fcspi_master_abort_transfer(pFcspiHandle, FCSPI_FALSE);
    }
    else
    {
        fcspi_slave_abort_transfer(pFcspiHandle, FCSPI_FALSE);
    }
}

void fcspi_irq_handler(FCSPI_HandleType *pFcspiHandle)
{
    if (FCSPI_MODE_MASTER == FCSPI_HWA_CheckMode(s_apFCSpiInsts[pFcspiHandle->eInstance]))
    {
        fcspi_master_trigger(pFcspiHandle, FCSPI_TRUE);
    }
    else
    {
        fcspi_slave_trigger(pFcspiHandle, FCSPI_TRUE);
    }
}

#endif

