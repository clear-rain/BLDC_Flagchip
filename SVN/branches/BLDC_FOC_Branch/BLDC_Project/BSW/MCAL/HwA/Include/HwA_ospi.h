/**
 * @file HwA_ospi.h
 * @author Flagchip
 * @brief OSPI hardware access layer
 * @version 2.0.0
 * @date 2024-06-22
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/
#ifndef _HWA_OSPI_H_
#define _HWA_OSPI_H_

#include "device_header.h"

#if OSPI_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_ospi HwA_ospi
 * @ingroup module_driver_ospi
 * @{
 */

/**
 * @brief Defines the DQS source selection types for the OSPI interface.
 */
typedef enum
{
    DQS_INTER_LOOPBACK = 0, /**< DQS internal loopback mode. */
    DQS_PAD_LOOPBACK,       /**< DQS pad loopback mode. */
    DQS_EXTERNAL_PADINPUT   /**< DQS external pad input mode. */
}OSPI_DqsSrcSelType;

/**
 * @brief Defines the clock division options for the OSPI interface.
 */
typedef enum
{
    OSPI_CLOCK_DIV_1 = 0U,  /**< Clock is not divided (divided by 1). */
    OSPI_CLOCK_DIV_2 = 1U,  /**< Clock is divided by 2. */
    OSPI_CLOCK_DIV_3 = 2U,  /**< Clock is divided by 3. */
    OSPI_CLOCK_DIV_4 = 3U,  /**< Clock is divided by 4. */
    OSPI_CLOCK_DIV_5 = 4U,  /**< Clock is divided by 5. */
    OSPI_CLOCK_DIV_6 = 5U,  /**< Clock is divided by 6. */
    OSPI_CLOCK_DIV_7 = 6U,  /**< Clock is divided by 7. */
    OSPI_CLOCK_DIV_8 = 7U   /**< Clock is divided by 8. */
}OSPI_ClockDivideType;

/**
 * @brief Defines the clock multiplexer sources for the OSPI interface.
 */
typedef enum
{
    OSPI_CLK_MUX_PLL0 = 0,  /**< Selects PLL0 as the clock source. */
    OSPI_CLK_MUX_FIRC,      /**< Selects FIRC as the clock source. */
    OSPI_CLK_MUX_FOSC,      /**< Selects FOSC as the clock source. */
    OSPI_CLK_MUX_CORE       /**< Selects CORE as the clock source. */
}OSPI_ClockMuxType;

/**
 * @brief Defines the endianess options for the OSPI interface.
 */
typedef enum
{
    OSPI_BIG_ENDIAN = 0,    /**< Big endian data format. */
    OSPI_LITTLE_ENDIAN      /**< Little endian data format. */
}OSPI_EndianType;

#define CTRL_RST_VALUE 0x34000
/********* Local inline function ************/

/**
 * @brief Generate a software reset of OSPI hardware.
 * 
 * @param pOSPI the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_SW_Reset(OSPI_Type *pOSPI)
{
    pOSPI->CTRL |= OSPI_CTRL_SWRST(1);
	pOSPI->CTRL &= ~OSPI_CTRL_SWRST(1);
}

/**
 * @brief OSPI DIO3 Default High
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_Dio3DefHigh(OSPI_Type *pOSPI)
{
    pOSPI->CTRL |= OSPI_CTRL_DSDIO3_MASK;
}

/**
 * @brief OSPI DIO3 Default Low
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_Dio3DefLow(OSPI_Type *pOSPI)
{
    pOSPI->CTRL &= ~OSPI_CTRL_DSDIO3_MASK;
}

/**
 * @brief OSPI DIO2 Default High
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_Dio2DefHigh(OSPI_Type *pOSPI)
{
    pOSPI->CTRL |= OSPI_CTRL_DSDIO2_MASK;
}

/**
 * @brief OSPI DIO2 Default Low
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_Dio2DefLow(OSPI_Type *pOSPI)
{
    pOSPI->CTRL &= ~OSPI_CTRL_DSDIO2_MASK;
}


/**
 * @brief OSPI Module Enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_ModuleEnable(OSPI_Type *pOSPI)
{
	pOSPI->CTRL &= ~OSPI_CTRL_MDIS_MASK;
}

/**
 * @brief OSPI Module Disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_ModuleDisable(OSPI_Type *pOSPI)
{    
    pOSPI->CTRL |= OSPI_CTRL_MDIS_MASK;
}

/**
 * @brief OSPI Clear Tx fifo
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_ClearTxFifo(OSPI_Type *pOSPI)
{    
    pOSPI->CTRL |= OSPI_CTRL_CLR_TF_MASK;
}

/**
 * @brief OSPI Clear Rx fifo
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_ClearRxFifo(OSPI_Type *pOSPI)
{    
    pOSPI->CTRL |= OSPI_CTRL_CLR_RF_MASK;
}


/**
 * @brief OSPI DDR Mode Enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DdrModeEnable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL |= OSPI_CTRL_DDR_EN_MASK;
}

/**
 * @brief OSPI DDR Mode Disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DdrModeDisable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL &= ~OSPI_CTRL_DDR_EN_MASK;
}

/**
 * @brief OSPI DQS Mode Enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsModeEnable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL |= OSPI_CTRL_DQS_EN_MASK;
}

/**
 * @brief OSPI DQS Mode Disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsModeDisable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL &= ~OSPI_CTRL_DQS_EN_MASK;
}

/**
 * @brief OSPI DQS Lantency Enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsLatEnable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL |= OSPI_CTRL_DQS_LAT_MASK;
}

/**
 * @brief OSPI DQS Lantency Disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsLatDisable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL &= ~OSPI_CTRL_DQS_LAT_MASK;
}

/**
 * @brief OSPI DQS Out Enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsOutEnable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL |= OSPI_CTRL_DQS_OUT_MASK;
}

/**
 * @brief OSPI DQS Out Disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsOutDisable(OSPI_Type *pOSPI)
{
    pOSPI->CTRL &= ~OSPI_CTRL_DQS_OUT_MASK;
}

/**
 * @brief Set OSPI Endian value.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param eEndian  Endian select value.
 */
LOCAL_INLINE void OSPI_HWA_EndianSelect(OSPI_Type *pOSPI,OSPI_EndianType eEndian)
{
	pOSPI->CTRL &= ~OSPI_CTRL_ENDIAN_MASK;
	pOSPI->CTRL |= OSPI_CTRL_ENDIAN(eEndian);
}
/**
 * @brief Set OSPI CTRL value, users should write the whole value to this register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u32Value  the value which will be written to the CTRL register.
 */
LOCAL_INLINE void OSPI_HWA_SetCtrlValue(OSPI_Type *pOSPI, uint32_t u32Value)
{
    pOSPI->CTRL = u32Value;
}

/**
 * @brief Read the OSPI CTRL register value for all.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return OSPI CTRL regsiter value.
 */
LOCAL_INLINE uint32_t OSPI_HWA_GetCtrlValue(OSPI_Type *pOSPI)
{
    return pOSPI->CTRL;
}
/**
 * @brief Set CMD ID.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u16Value  Pointers of current CMD stored in LUT registers.
 */
LOCAL_INLINE void OSPI_HWA_SetCmdId(OSPI_Type *pOSPI, uint16_t u16Value)
{
	pOSPI->CMDC &= ~OSPI_CMDC_CMD_ID_MASK;
    pOSPI->CMDC |= OSPI_CMDC_CMD_ID(u16Value);
}

/**
 * @brief Set CMD SIZE.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u16Value  Transfer sizes of current CMD.
 */
LOCAL_INLINE void OSPI_HWA_SetCmdSize(OSPI_Type *pOSPI, uint16_t u16Value)
{
	pOSPI->CMDC &= ~OSPI_CMDC_CMD_SIZE_MASK;
    pOSPI->CMDC |= OSPI_CMDC_CMD_SIZE(u16Value);
}

/**
 * @brief Set CMD id and size.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u8SeqId  Pointers of current CMD stored in LUT registers.
 * @param u16Size  Transfer sizes of current CMD.
 */
LOCAL_INLINE void OSPI_HWA_SetCmdIdSize(OSPI_Type *pOSPI,uint8_t u8SeqId,uint16_t u16Size)
{
	pOSPI->CMDC = OSPI_CMDC_CMD_ID(u8SeqId)|OSPI_CMDC_CMD_SIZE(u16Size);
}
/**
 * @brief Read the OSPI CMDC register value for all.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return OSPI CMDC regsiter value.
 */
LOCAL_INLINE uint32_t OSPI_HWA_GetCmdcValue(OSPI_Type *pOSPI)
{
    return pOSPI->CMDC;
}

/**
 * @brief Set Data Hold Time,This bit should only be valid in DDR mode.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u8Value  Data Hold Time.
 */
LOCAL_INLINE void OSPI_HWA_SetDataHoldTime(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->FLS_CFG &= ~OSPI_FLS_CFG_TDH_MASK;
    pOSPI->FLS_CFG |= OSPI_FLS_CFG_TDH(u8Value);
}

/**
 * @brief Set CS Hold Time.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u8Value  CS Hold Time.
 */
LOCAL_INLINE void OSPI_HWA_SetCsHoldTime(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->FLS_CFG &= ~OSPI_FLS_CFG_TCSH_MASK;
    pOSPI->FLS_CFG |= OSPI_FLS_CFG_TCSH(u8Value);
}

/**
 * @brief Set CS Setup Time.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u8Value  CS Setup Time.
 */
LOCAL_INLINE void OSPI_HWA_SetCsSetupTime(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->FLS_CFG &= ~OSPI_FLS_CFG_TCSS_MASK;
    pOSPI->FLS_CFG |= OSPI_FLS_CFG_TCSS(u8Value);
}

/**
 * @brief Read the OSPI CMDC register value for all.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return OSPI CMDC regsiter value.
 */
LOCAL_INLINE uint32_t OSPI_HWA_GetFlashCfgValue(OSPI_Type *pOSPI)
{
    return pOSPI->FLS_CFG;
}

/**
 * @brief OSPI Enable internal reference clock
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_InternalRefclkEnable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_CLK_EN_MASK;
}

/**
 * @brief OSPI Disable internal reference clock
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_InternalRefclkDisable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_CLK_EN_MASK;
}

/**
 * @brief OSPI Set Internal Reference Clock Divider.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param eClkDiv  Internal Reference Clock Divider.
 */
LOCAL_INLINE void OSPI_HWA_InternalRefclkDiv(OSPI_Type *pOSPI, OSPI_ClockDivideType eClkDiv)
{
	pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_CLK_DIV_MASK;
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_CLK_DIV(eClkDiv);
}

/**
 * @brief OSPI PAD IBE Enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_PadIbeEnable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_IBE_EN_MASK;
}

/**
 * @brief OSPI PAD IBE Disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_PadIbeDisable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_IBE_EN_MASK;
}

/**
 * @brief OSPI Select Internal Reference Clock Source.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u8Value  Internal Reference Clock Source.
 */
LOCAL_INLINE void OSPI_HWA_InternalRefclkSource(OSPI_Type *pOSPI, OSPI_ClockMuxType u8Value)
{
	pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_CLK_MUX_MASK;
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_CLK_MUX(u8Value);
}

/**
 * @brief OSPI Use inverted DQS
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsInvertedEnable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_DQS_INV_MASK;
}

/**
 * @brief OSPI Not use inverted DQS
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DqsInvertedDisable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_DQS_INV_MASK;
}

/**
 * @brief OSPI Select DQS Source.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u8Value  DQS Source.
 */
LOCAL_INLINE void OSPI_HWA_DqsSource(OSPI_Type *pOSPI, OSPI_DqsSrcSelType u8Value)
{
	pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_DQS_MUX_MASK;
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_DQS_MUX(u8Value);
}

/**
 * @brief OSPI OBE timing relax enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_ObeTimRelaxEnable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_OBE_RELAX_MASK;
}

/**
 * @brief OSPI OBE timing relax disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_ObeTimRelaxDisable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_OBE_RELAX_MASK;
}

/**
 * @brief OSPI DDR Clock Enable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DdrClkEnable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_DDR_EN_MASK;
}

/**
 * @brief OSPI DDR Clock Disable
 *
 * @param pOSPI    the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_DdrClkDisable(OSPI_Type *pOSPI)
{
    pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_DDR_EN_MASK;
}

/**
 * @brief OSPI Switch Delay Line into DQS for timing. DQS will delay for DLLINE_CFG * Tcell.
 *
 * @param pOSPI    the base address of the OSPI.
 * @param u8Value  DQS Delay Line Cfg Value.
 */
LOCAL_INLINE void OSPI_HWA_CfgDelayLine(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->SOC_CFG &= ~OSPI_SOC_CFG_DLLINE_CFG_MASK;
    pOSPI->SOC_CFG |= OSPI_SOC_CFG_DLLINE_CFG(u8Value);
}

/**
 * @brief Write the OSPI SOC CFG register.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @param u32Value  the value to be writen.
 */
LOCAL_INLINE void OSPI_HWA_SetSocCfgValue(OSPI_Type *pOSPI, uint32_t u32Value)
{
    pOSPI->SOC_CFG = u32Value;
}

/**
 * @brief Read the OSPI SOC CFG register value for all.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return OSPI SOC_CFG regsiter value.
 */
LOCAL_INLINE uint32_t OSPI_HWA_GetSocCfgValue(OSPI_Type *pOSPI)
{
    return pOSPI->SOC_CFG;
}

/**
 * @brief Set flash address, users should write the whole value to this register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u32Value  the value which will be written to the FLS_AR register.
 */
LOCAL_INLINE void OSPI_HWA_SetFlashAddr(OSPI_Type *pOSPI, uint32_t u32Value)
{
    pOSPI->FLS_AR = u32Value;
}

/**
 * @brief Set flash addressable mode.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Value  the value of addressable mode.
 */
LOCAL_INLINE void OSPI_HWA_SetFlashAddrMode(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->FLS_CAR &= ~OSPI_FLS_CAR_WA_MASK;
    pOSPI->FLS_CAR |= OSPI_FLS_CAR_WA(u8Value);
}

/**
 * @brief Set Column Address Space.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Value  the value of Column Address Space.
 */
LOCAL_INLINE void OSPI_HWA_SetColAddrSpace(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->FLS_CAR &= ~OSPI_FLS_CAR_CAS_MASK;
    pOSPI->FLS_CAR |= OSPI_FLS_CAR_CAS(u8Value);
}

/**
 * @brief Set Sample delay clock cycle.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Value  the value of Sample Delay clock cycle.
 */
LOCAL_INLINE void OSPI_HWA_SetSampleDlyClkCycle(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->SAMP_CTRL &= ~OSPI_SAMP_CTRL_DLY_MASK;
    pOSPI->SAMP_CTRL |= OSPI_SAMP_CTRL_DLY(u8Value);
}

/**
 * @brief Selects reference clock edge for valid sampling phase.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Value  the value of reference clock edge.
 */
LOCAL_INLINE void OSPI_HWA_SelectRefClkEdge(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->SAMP_CTRL &= ~OSPI_SAMP_CTRL_PHS_MASK;
    pOSPI->SAMP_CTRL |= OSPI_SAMP_CTRL_PHS(u8Value);
}

/**
 * @brief Read RX FIFO Counter,Indicates the current RX FIFO read pointer; 
 *        Automatically increases when RX FIFO pops an event.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return RX FIFO Counter.
 */
LOCAL_INLINE uint16_t OSPI_HWA_GetRxFifoCnt(OSPI_Type *pOSPI)
{
    return (uint16_t)((pOSPI->RFSR&OSPI_RFSR_RFCTR_MASK)>>OSPI_RFSR_RFCTR_SHIFT);
}

/**
 * @brief Read RX FIFO Fill Level,Indicates how many words are available in RX FIFO.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return RX FIFO Fill Level.
 */
LOCAL_INLINE uint8_t OSPI_HWA_GetRxFifoFillLevel(OSPI_Type *pOSPI)
{
    return (uint8_t)((pOSPI->RFSR&OSPI_RFSR_RFFL_MASK)>>OSPI_RFSR_RFFL_SHIFT);
}

/**
 * @brief Set RX FIFO Watermark,
 *        Indicates how many valid entries will trigger a readout action.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Value  the value of RX FIFO Watermark.
 */
LOCAL_INLINE void OSPI_HWA_SetRxFifoWaterMark(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->RF_CFG &= ~OSPI_RF_CFG_WMRK_MASK;
    pOSPI->RF_CFG |= OSPI_RF_CFG_WMRK(u8Value);
}

/**
 * @brief Read TX FIFO Counter,Indicates the current TX FIFO stored data pointer; 
 *        Automatically increases when TX FIFO pops an event.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return TX FIFO Counter.
 */
LOCAL_INLINE uint16_t OSPI_HWA_GetTxFifoCnt(OSPI_Type *pOSPI)
{
    return (uint16_t)((pOSPI->TFSR&OSPI_TFSR_TFCTR_MASK)>>OSPI_TFSR_TFCTR_SHIFT);
}

/**
 * @brief Read TX FIFO Fill Level,Indicates how many words are available in TX FIFO.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return TX FIFO Fill Level.
 */
LOCAL_INLINE uint8_t OSPI_HWA_GetTxFifoFillLevel(OSPI_Type *pOSPI)
{
    return (uint8_t)((pOSPI->TFSR&OSPI_TFSR_TFFL_MASK)>>OSPI_TFSR_TFFL_SHIFT);
}

/**
 * @brief Writing this register will trigger data entry of TX FIFO.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u32Value  the value of tx data.
 */
LOCAL_INLINE void OSPI_HWA_WriteTxData(OSPI_Type *pOSPI, uint32_t u32Value)
{
	pOSPI->TFDR = u32Value;
}

/**
 * @brief Set TX FIFO Watermark,
 *        Indicates how many valid entries will trigger a transmit action.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Value  the value of TX FIFO Watermark.
 */
LOCAL_INLINE void OSPI_HWA_SetTxFifoWaterMark(OSPI_Type *pOSPI, uint8_t u8Value)
{
	pOSPI->TF_CFG &= ~OSPI_TF_CFG_WMRK_MASK;
    pOSPI->TF_CFG |= OSPI_TF_CFG_WMRK(u8Value);
}

/**
 * @brief Read status register.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return Status register.
 */
LOCAL_INLINE uint32_t OSPI_HWA_GetStatus(OSPI_Type *pOSPI)
{
    return pOSPI->STATUS&OSPI_STATUS_MASK;
}

/**
 * @brief Read flag register.
 *
 * @param pOSPI  pOSPI  the base address of the OSPI.
 * @return flag register.
 */
LOCAL_INLINE uint32_t OSPI_HWA_GetFlag(OSPI_Type *pOSPI)
{
    return pOSPI->FLAG&OSPI_FLAG_MASK;
}

/**
 * @brief Writing this register will clear ospi flag.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u32Value  the value of flag to be cleared.
 */ 
LOCAL_INLINE void OSPI_HWA_ClearFlag(OSPI_Type *pOSPI, uint32_t u32Value)
{
	pOSPI->FLAG = (u32Value&OSPI_FLAG_MASK);
}

/**
 * @brief Set the OSPI IND_EN register value for enable or disable  interrupts&DMA.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void OSPI_HWA_SetIntDmasEnableReg(OSPI_Type *pOSPI, uint32_t u32Value)
{
    pOSPI->IND_EN = (u32Value&OSPI_IND_EN_MASK);
}

/**
 * @brief Set flash top address register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u32Value Top Address of Flash Device.
 */
LOCAL_INLINE void OSPI_HWA_SetFlashTopAddr(OSPI_Type *pOSPI, uint32_t u32Value)
{
    pOSPI->FLS_TAR = (u32Value&OSPI_FLS_TAR_MASK);
}

/**
 * @brief Read receive fifo data register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Idx  Fifo index to be read.
 * @return Receive fifo data register.
 */
LOCAL_INLINE uint32_t OSPI_HWA_ReadRcvFifoReg(OSPI_Type *pOSPI,uint8_t u8Idx)
{
    return pOSPI->RFDR[u8Idx];
}

/**
 * @brief Read secondary receive fifo data register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @return Secondary receive fifo data register.
 */
LOCAL_INLINE uint32_t OSPI_HWA_ReadSecondaryRcvFifoReg(OSPI_Type *pOSPI)
{
    return pOSPI->RFD2R;
}

/**
 * @brief Write LUT Key register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u32Value LUT Key Value to be writed.
 */
LOCAL_INLINE void OSPI_HWA_WriteLutKey(OSPI_Type *pOSPI, uint32_t u32Value)
{
    pOSPI->LUT_KEY = u32Value;
}

/**
 * @brief Read LUT Key register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @return LUT Key Value.
 */
LOCAL_INLINE uint32_t OSPI_HWA_ReadLutKey(OSPI_Type *pOSPI)
{
    return pOSPI->LUT_KEY;
}

/**
 * @brief Lock the LUT.
 *
 * @param pOSPI  the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_LockLut(OSPI_Type *pOSPI)
{
    pOSPI->LUT_CFG = OSPI_LUT_CFG_LOCK_MASK;
}

/**
 * @brief Unlock the LUT.
 *
 * @param pOSPI  the base address of the OSPI.
 */
LOCAL_INLINE void OSPI_HWA_UnlockLut(OSPI_Type *pOSPI)
{
    pOSPI->LUT_CFG = OSPI_LUT_CFG_UNLOCK_MASK;
}

/**
 * @brief Write lookup table register.
 *
 * @param pOSPI  the base address of the OSPI.
 * @param u8Idx Index of LUT.
 * @param u32Value LUT Value to be writed.
 */
LOCAL_INLINE void OSPI_HWA_WriteLut(OSPI_Type *pOSPI, uint8_t u8Idx, uint32_t u32Value)
{
    pOSPI->LUT[u8Idx] = u32Value;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_OSPI_H_ */
