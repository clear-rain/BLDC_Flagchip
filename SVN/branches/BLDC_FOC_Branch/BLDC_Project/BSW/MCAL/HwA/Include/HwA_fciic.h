/**
 * @file HwA_fciic.h
 * @author flagchip
 * @brief FCIIC hardware access layer
 * @version 2.0.0
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0      2023-12-15     Flagchip038   N/A          First version for FC7300
   *   2.0.0      2024-10-12     Flagchip113   N/A          Change version and release
   ******************************************************************************** */

#ifndef _HWA_FCIIC_H_
#define _HWA_FCIIC_H_

#include "device_header.h"

#if FCIIC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_fciic HwA_fciic
 * @ingroup module_driver_fciic
 * @{
 */

/**
 * @brief FCIIC MSR flags.
 *
 */
typedef enum
{
    FCIIC_MSR_TDF   = FCIIC_MSR_TDF_MASK,  /*!< Transmit data flag */
    FCIIC_MSR_RDF   = FCIIC_MSR_RDF_MASK,  /*!< Receive data flag */
    FCIIC_MSR_EPF   = FCIIC_MSR_EPF_MASK,  /*!< End Packet flag */
    FCIIC_MSR_SDF   = FCIIC_MSR_SDF_MASK,  /*!< Stop detect flag */
    FCIIC_MSR_NDF   = FCIIC_MSR_NDF_MASK,  /*!< NACK detect flag */
    FCIIC_MSR_ALF     = FCIIC_MSR_ALF_MASK,  /*!< Arbitration lost flag */
    FCIIC_MSR_FEF   = FCIIC_MSR_FEF_MASK,  /*!< FIFO error flag */
    FCIIC_MSR_PLTF    = FCIIC_MSR_PLTF_MASK, /*!< Pin low timeout flag */
    FCIIC_MSR_DMF   = FCIIC_MSR_DMF_MASK,  /*!< Data match flag */
    FCIIC_MSR_MBF   = FCIIC_MSR_MBF_MASK,  /*!< Master busy flag */
    FCIIC_MSR_BBF   = FCIIC_MSR_BBF_MASK,  /*!< Bus busy flag */

    /** All flags which are cleared by the driver upon starting a transfer. */
    FCIIC_MasterClearFlags = FCIIC_MSR_EPF | FCIIC_MSR_SDF | FCIIC_MSR_NDF |
                             FCIIC_MSR_ALF | FCIIC_MSR_FEF |
                             FCIIC_MSR_PLTF | FCIIC_MSR_DMF,
    /** Errors to check for. */
    FCIIC_MasterErrorFlags = FCIIC_MSR_NDF | FCIIC_MSR_ALF | 
                             FCIIC_MSR_FEF | FCIIC_MSR_PLTF
} FCIIC_MsrType;

/**
 * @brief FCIIC MIER flags.
 *
 */
typedef enum
{
    FCIIC_MIER_TDIE   = FCIIC_MIER_TDIE_MASK,  /*!< Transmit data interrupt */
    FCIIC_MIER_RDIE   = FCIIC_MIER_RDIE_MASK,  /*!< Receive data interrupt */
    FCIIC_MIER_EPIE   = FCIIC_MIER_EPIE_MASK,  /*!< End Packet interrupt */
    FCIIC_MIER_SDIE   = FCIIC_MIER_SDIE_MASK,  /*!< Stop detect interrupt */
    FCIIC_MIER_NDIE   = FCIIC_MIER_NDIE_MASK,  /*!< NACK detect interrupt */
    FCIIC_MIER_ALIE   = FCIIC_MIER_ALIE_MASK,  /*!< Arbitration lost interrupt */
    FCIIC_MIER_FEIE   = FCIIC_MIER_FEIE_MASK,  /*!< FIFO error interrupt */
    FCIIC_MIER_PLTIE  = FCIIC_MIER_PLTIE_MASK, /*!< Pin low timeout interrupt */
    FCIIC_MIER_DMIE   = FCIIC_MIER_DMIE_MASK,  /*!< Data match interrupt */

    /** IRQ sources enabled for error. */
    FCIIC_MasterIrqErrorFlags = FCIIC_MIER_ALIE | FCIIC_MIER_FEIE | FCIIC_MIER_PLTIE,

   /** IRQ sources enabled by the non-blocking transactional API. */
     FCIIC_MasterIrqFlags = FCIIC_MIER_TDIE | FCIIC_MIER_RDIE |
                            FCIIC_MIER_SDIE | FCIIC_MIER_NDIE |
                            FCIIC_MIER_ALIE | FCIIC_MIER_FEIE |
                            FCIIC_MIER_PLTIE,
} FCIIC_MierType;

/**
 * @brief IIC Command Type Enumeration
 *
 */
typedef enum
{
    FCIIC_TX_CMD_TRANSMIT = 0,           /**< FCIIC_TX_CMD_TRANSMIT                 transmit command */
    FCIIC_TX_CMD_RECEIVE,                /**< FCIIC_TX_CMD_RECEIVE                  receive command*/
    FCIIC_TX_CMD_STOP,                   /**< FCIIC_TX_CMD_STOP                     stop command */
    FCIIC_TX_CMD_RECANDDISCARD,          /**< FCIIC_TX_CMD_RECANDDISCARD            receive and discard data command*/
    FCIIC_TX_CMD_STARTANDTRANSMIT,       /**< FCIIC_TX_CMD_STARTANDTRANSMIT         start and then transmit data */
    FCIIC_TX_CMD_STARTANDTRANSMIT_WITHNAK/**< FCIIC_TX_CMD_STARTANDTRANSMIT_WITHNAK start and then transmit and don't care ACK */
} FCIIC_TX_CMDType;


/**
 * @brief IIC Master status type enumeration
 *
 */
typedef enum
{
    FCIIC_MSR_BBF_STATUS    = 25U,    /**< FCIIC_MSR_BBF_STATUS  Bus Busy Flag             */
    FCIIC_MSR_MBF_STATUS    = 24U,    /**< FCIIC_MSR_MBF_STATUS  Master Busy Flag          */
    FCIIC_MSR_DMF_STATUS    = 14U,    /**< FCIIC_MSR_DMF_STATUS  Data Match Flag           */
    FCIIC_MSR_PLTF_STATUS   = 13U,    /**< FCIIC_MSR_PLTF_STATUS Pin Low Timeout Flag      */
    FCIIC_MSR_FEF_STATUS    = 12U,    /**< FCIIC_MSR_FEF_STATUS  FIFO Error Flag           */
    FCIIC_MSR_ALF_STATUS    = 11U,    /**< FCIIC_MSR_ALF_STATUS  Arbitration Lost Flag     */
    FCIIC_MSR_NDF_STATUS    = 10U,    /**< FCIIC_MSR_NDF_STATUS  NACK Detect Flag          */
    FCIIC_MSR_SDF_STATUS    = 9U,     /**< FCIIC_MSR_SDF_STATUS  STOP Detect Flag          */
    FCIIC_MSR_EPF_STATUS    = 8U,     /**< FCIIC_MSR_EPF_STATUS  End Packet Flag           */
    FCIIC_MSR_RXFPEF_STATUS = 3U,     /**< FCIIC_MSR_EPF_STATUS  RX FIFO Parity Error Flag */
    FCIIC_MSR_TXFPEF_STATUS = 2U,     /**< FCIIC_MSR_EPF_STATUS  TX FIFO Parity Error Flag */
    FCIIC_MSR_RDF_STATUS    = 1U,     /**< FCIIC_MSR_RDF_STATUS  Receive Data Flag         */
    FCIIC_MSR_TDF_STATUS    = 0U      /**< FCIIC_MSR_TDF_STATUS  Transmit Data Flag        */
} FCIIC_MasterStatusType;

/**
 * @brief FCIIC SSR flags.
 *
 */
typedef enum
{
    FCIIC_SSR_TDF   = FCIIC_SSR_TDF_MASK,   /*!< Transmit data flag */
    FCIIC_SSR_RDF   = FCIIC_SSR_RDF_MASK,   /*!< Receive data flag  */
    FCIIC_SSR_AVF   = FCIIC_SSR_AVF_MASK,   /*!< Address Valid Flag */
    FCIIC_SSR_TAF   = FCIIC_SSR_TAF_MASK,   /*!< Transmit ACK Flag */
    FCIIC_SSR_RSF   = FCIIC_SSR_RSF_MASK,   /*!< Repeated Start Flag */
    FCIIC_SSR_SDF   = FCIIC_SSR_SDF_MASK,   /*!< STOP Detect Flag */
    FCIIC_SSR_BEF   = FCIIC_SSR_BEF_MASK,   /*!< Bit Error Flag */
    FCIIC_SSR_TREF  = FCIIC_SSR_TREF_MASK,  /*!<Transmit or Receive Error Flag */
    FCIIC_SSR_AM0F  = FCIIC_SSR_AM0F_MASK,  /*!< Address Match 0 Flag */
    FCIIC_SSR_AM1F  = FCIIC_SSR_AM1F_MASK,  /*!< Address Match 1 Flag */
    FCIIC_SSR_GCF   = FCIIC_SSR_GCF_MASK,   /*!< General Call Flag */
    FCIIC_SSR_SARF  = FCIIC_SSR_SARF_MASK,  /*!< SMBus Alert Response Flag */
    FCIIC_SSR_SBF   = FCIIC_SSR_SBF_MASK,   /*!< Slave Busy Flag */
    FCIIC_SSR_BBF   = FCIIC_SSR_BBF_MASK,   /*!< Bus Busy Flag */

    /** All flags which are cleared by the driver upon starting a transfer. */
    FCIIC_SlaveClearFlags = FCIIC_SSR_TDF | FCIIC_SSR_RDF | FCIIC_SSR_AVF |
                            FCIIC_SSR_SDF | FCIIC_SSR_TAF | FCIIC_SSR_RSF |
                            FCIIC_SSR_SDF | FCIIC_SSR_TREF | FCIIC_SSR_AM0F |
                            FCIIC_SSR_AM1F | FCIIC_SSR_SARF | FCIIC_SSR_SBF |
                            FCIIC_SSR_BBF,
    /** Errors to check for. */
    FCIIC_SlaveErrorFlags = FCIIC_SSR_BEF | FCIIC_SSR_TREF

} FCIIC_SsrType;

/**
 * @brief FCIIC MIER flags.
 *
 */
typedef enum
{
    FCIIC_SIER_TDIE   = FCIIC_SIER_TDIE_MASK,  /*!< Transmit data interrupt */
    FCIIC_SIER_RDIE   = FCIIC_SIER_RDIE_MASK,  /*!< Receive data interrupt */
    FCIIC_SIER_AVIE   = FCIIC_SIER_AVIE_MASK,  /*!< Address Valid Interrupt Enable */
    FCIIC_SIER_TAIE   = FCIIC_SIER_TAIE_MASK,  /*!< Transmit ACK Interrupt Enable */
    FCIIC_SIER_RSIE   = FCIIC_SIER_RSIE_MASK,  /*!< Repeated Start Interrupt Enable */
    FCIIC_SIER_SDIE   = FCIIC_SIER_SDIE_MASK,  /*!< STOP Detect Interrupt Enable */
    FCIIC_SIER_BEIE   = FCIIC_SIER_BEIE_MASK,  /*!< Bit Error Interrupt Enable */
    FCIIC_SIER_TREIE  = FCIIC_SIER_TREIE_MASK,  /*!< Transmit or Receive Error Interrupt Enable */
    FCIIC_SIER_AM0IE  = FCIIC_SIER_AM0IE_MASK, /*!< Address Match 0 Interrupt Enable */
    FCIIC_SIER_AM1IE  = FCIIC_SIER_AM1IE_MASK,  /*!< Address Match 1 Interrupt Enable */
    FCIIC_SIER_GCIE   = FCIIC_SIER_GCIE_MASK, /*!< General Call Interrupt Enable */
    FCIIC_SIER_SARIE  = FCIIC_SIER_SARIE_MASK,  /*!< SMBus Alert Response Interrupt Enable */

    /** IRQ sources enabled by the non-blocking transactional API. */
    FCIIC_SlaveIrqFlags = FCIIC_SIER_RDIE | FCIIC_SIER_SDIE | FCIIC_SIER_TDIE |
                          FCIIC_SIER_AM0IE

} FCIIC_SierType;


/**
 * @brief IIC Slave status type enumeration
 *
 */
typedef enum
{
    FCIIC_SSR_BBF_STATUS   = 25U, /**< FCIIC_SSR_BBF_STATUS Bus Busy Flag              */
    FCIIC_SSR_SBF_STATUS   = 24U, /**< FCIIC_SSR_SBF_STATUS Slave Busy Flag            */
    FCIIC_SSR_SARF_STATUS  = 15U, /**< FCIIC_SSR_SARF_STATUS SMBus Alert Response Flag */
    FCIIC_SSR_GCF_STATUS   = 14U, /**< FCIIC_SSR_GCF_STATUS General Call Flag          */
    FCIIC_SSR_AM1F_STATUS  = 13U, /**< FCIIC_SSR_AM1F_STATUS Address Match 1 Flag      */
    FCIIC_SSR_AM0F_STATUS  = 12U, /**< FCIIC_SSR_AM0F_STATUS Address Match 0 Flag      */
    FCIIC_SSR_TREF_STATUS  = 11U, /**< FCIIC_SSR_TREF_STATUS FIFO Error Flag           */
    FCIIC_SSR_BEF_STATUS   = 10U, /**< FCIIC_SSR_BEF_STATUS Bit Error Flag             */
    FCIIC_SSR_SDF_STATUS   = 9U,  /**< FCIIC_SSR_SDF_STATUS STOP Detect Flag           */
    FCIIC_SSR_RSF_STATUS   = 8U,  /**< FCIIC_SSR_RSF_STATUS Repeated Start Flag        */
    FCIIC_SSR_TAF_STATUS   = 3U,  /**< FCIIC_SSR_TAF_STATUS Transmit ACK Flag          */
    FCIIC_SSR_AVF_STATUS   = 2U,  /**< FCIIC_SSR_AVF_STATUS Address Valid Flag         */
    FCIIC_SSR_RDF_STATUS   = 1U,  /**< FCIIC_SSR_RDF_STATUS Receive Data Flag          */
    FCIIC_SSR_TDF_STATUS   = 0U,  /**< FCIIC_SSR_TDF_STATUS Transmit Data Flag         */
} FCIIC_SlaveStatusType;

/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief Restores the FCIIC master peripheral to reset conditions.
 *
 * This function resets the FCIIC master peripheral by setting and then clearing the RST bit in the MCR register.
 *
 * @param base The FCIIC peripheral base address.
 */
LOCAL_INLINE void FCIIC_HwA_MasterReset(FCIIC_Type *const base)
{
    base->MCR = FCIIC_MCR_RST_MASK;
    base->MCR = 0;
}

/**
 * @brief Enables or disables the FCIIC module as master.
 *
 * This function sets or clears the MEN bit in the MCR register to enable or disable the FCIIC module as master.
 *
 * @param base The FCIIC peripheral base address.
 * @param enable Pass true to enable or false to disable the specified FCIIC as master.
 */
LOCAL_INLINE void FCIIC_HwA_MasterEnable(FCIIC_Type *const base, bool enable)
{
    base->MCR = (base->MCR & ~FCIIC_MCR_MEN_MASK) | FCIIC_MCR_MEN(enable);
}

/**
 * @brief Resets the FCIIC module's transmit and receive FIFOs.
 *
 * This function sets the RRF and RTF bits in the MCR register to reset the transmit and receive FIFOs.
 *
 * @param base The FCIIC peripheral base address.
 */
LOCAL_INLINE void FCIIC_HWA_MasterResetFIFO(FCIIC_Type *const base)
{
    base->MCR |= (FCIIC_MCR_RRF_MASK | FCIIC_MCR_RTF_MASK);
}

/**
 * @brief Retrieves the current status of the FCIIC master enable bit.
 *
 * This function checks the MEN bit in the MCR register to determine if the FCIIC is enabled as master.
 *
 * @param base The FCIIC peripheral base address.
 * @return State of the master enable bit: 0x01 if enabled, 0x00 if disabled.
 */
LOCAL_INLINE uint8_t FCIIC_HWA_MasterGetEnable(FCIIC_Type *const base)
{
    return (base->MCR & FCIIC_MCR_MEN_MASK) == FCIIC_MCR_MEN_MASK ? 0x01 : 0x00;
}

/**
 * @brief Gets the FCIIC master status flags.
 *
 * This function reads the MSR register to get the current status flags.
 *
 * @param base The FCIIC peripheral base address.
 * @return The value of the MSR register.
 */
LOCAL_INLINE uint32_t FCIIC_HWA_MasterGetStatusFlags(const FCIIC_Type *const base)
{
    return base->MSR;
}

/**
 * @brief Clears the FCIIC master status flag state.
 *
 * This function clears specific status flags by writing to the MSR register.
 *
 * @param base The FCIIC peripheral base address.
 * @param statusMask A bitmask of status flags that are to be cleared.
 */
LOCAL_INLINE void FCIIC_HWA_MasterClearStatusFlags(FCIIC_Type *const base, uint32_t statusMask)
{
    base->MSR = statusMask;
}

/**
 * @brief Enables the FCIIC master interrupt requests.
 *
 * This function enables specific interrupt requests by setting bits in the MIER register.
 *
 * @param base The FCIIC peripheral base address.
 * @param interruptMask Bit mask of interrupts to enable.
 */
LOCAL_INLINE void FCIIC_HWA_MasterEnableInterrupts(FCIIC_Type *const base, uint32_t interruptMask)
{
    base->MIER |= interruptMask;
}

/**
 * @brief Disables the FCIIC master interrupt requests.
 *
 * @param base The FCIIC peripheral base address.
 * @param interruptMask Bit mask of interrupts to disable.
 */
LOCAL_INLINE void FCIIC_HWA_MasterDisableInterrupts(FCIIC_Type *const base, uint32_t interruptMask)
{
    base->MIER &= ~interruptMask;
}

/**
 * @brief Returns the set of currently enabled FCIIC master interrupt requests.
 *
 * @param base The FCIIC peripheral base address.
 * @return A bitmask composed of FCIIC_MierType enumerators
 */
LOCAL_INLINE uint32_t FCIIC_HwA_MasterGetEnabledInterrupts(const FCIIC_Type *const base)
{
    return base->MIER;
}

/**
 * @brief Enables or disables FCIIC master DMA requests.
 *
 * @param base The FCIIC peripheral base address.
 * @param enableTx Enable flag for transmit DMA request. Pass true for enable, false for disable.
 * @param enableRx Enable flag for receive DMA request. Pass true for enable, false for disable.
 */
LOCAL_INLINE void FCIIC_HWA_MasterEnableDMA(FCIIC_Type *const base, bool enableTx, bool enableRx)
{
    base->MDER = FCIIC_MDER_TDDE(enableTx) | FCIIC_MDER_RDDE(enableRx);
}

/**
 * @brief Gets FCIIC master transmit data register address for DMA transfer.
 *
 * @param base The FCIIC peripheral base address.
 * @return The FCIIC Master Transmit Data Register address.
 */
LOCAL_INLINE uint32_t FCIIC_HwA_MasterGetTxFifoAddress(const FCIIC_Type *const base)
{
    return (uint32_t)&base->MTDR;
}

/**
 * @brief Gets FCIIC master receive data register address for DMA transfer.
 *
 * @param base The FCIIC peripheral base address.
 * @return The FCIIC Master Receive Data Register address.
 */
LOCAL_INLINE uint32_t FCIIC_HwA_MasterGetRxFifoAddress(const FCIIC_Type *const base)
{
    return (uint32_t)&base->MRDR;
}

/**
 * @brief Sets the watermarks for FCIIC master FIFOs.
 *
 * @param base The FCIIC peripheral base address.
 * @param txWords Transmit FIFO watermark value.
 * @param rxWords Receive FIFO watermark value.
 */
LOCAL_INLINE void FCIIC_HwA_MasterSetWatermarks(FCIIC_Type *const base, uint16_t txWords, uint16_t rxWords)
{
    base->MFCR = FCIIC_MFCR_TXWATER(txWords) | FCIIC_MFCR_RXWATER(rxWords);
}

/**
 * @brief Gets the current number of words in the FCIIC master FIFOs.
 *
 * @param base The FCIIC peripheral base address.
 * @param[out] txCount Pointer through which the current number of words in the transmit FIFO is returned.
 *      Pass NULL if this value is not required.
 * @param[out] rxCount Pointer through which the current number of words in the receive FIFO is returned.
 *      Pass NULL if this value is not required.
 */
static inline void FCIIC_HwA_MasterGetFifoCounts(const FCIIC_Type *const base, uint16_t *rxCount, uint16_t *txCount)
{
    if (NULL != txCount)
    {
        *txCount = (base->MFSR & FCIIC_MFSR_TXCOUNT_MASK) >> FCIIC_MFSR_TXCOUNT_SHIFT;
    }
    if (NULL != rxCount)
    {
        *rxCount = (base->MFSR & FCIIC_MFSR_RXCOUNT_MASK) >> FCIIC_MFSR_RXCOUNT_SHIFT;
    }
}

/**
 * @brief Master Transmit Data
 *
 * Transmits data in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @param tCmdType Command type to be sent.
 * @param u8Data Data byte to be transmitted.
 */
LOCAL_INLINE void FCIIC_Master_HWA_Transmit(FCIIC_Type *pFciic, FCIIC_TX_CMDType tCmdType, uint8_t u8Data)
{
    pFciic->MTDR = FCIIC_MTDR_CMD(tCmdType) | FCIIC_MTDR_DATA(u8Data);
}

/**
 * @brief Get the number of bytes transmitted by the master
 *
 * Returns the count of bytes transmitted by the master.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @return Number of bytes transmitted.
 */
LOCAL_INLINE uint32 FCIIC_Master_HWA_GetTxCount(FCIIC_Type *pFciic)
{
    return (pFciic->MFSR & FCIIC_MFSR_TXCOUNT_MASK);
}

/**
 * @brief Master Receive Data
 *
 * Receives a data byte in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @return Received data byte.
 */
LOCAL_INLINE uint8_t FCIIC_Master_HWA_Receive(FCIIC_Type *pFciic)
{
    /* copy data */
    return (uint8_t)((uint8_t)(pFciic->MRDR) & 0xFFU);
}

/**
 * @brief Get and clear IIC master status
 *
 * Checks and clears a specific status flag in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @param eStatus Status type to check and clear.
 */
LOCAL_INLINE void FCIIC_Master_HwA_CheckClearStatus(FCIIC_Type *pFciic, FCIIC_MasterStatusType eStatus)
{
    uint32_t u32RetVal;

    u32RetVal = (pFciic->MSR >> eStatus) & 0x01U;


    if (u32RetVal != 0U)
    {
        pFciic->MSR |= (1UL << eStatus); /* write one to clear */
    }
}

/**
 * @brief Get master status
 *
 * Reads a specific status flag in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @param eStatus Status type to read.
 * @return Status value (0 or 1), where 1 indicates the status is set.
 */
LOCAL_INLINE uint8_t FCIIC_Master_HWA_GetStatus(FCIIC_Type *pFciic, FCIIC_MasterStatusType eStatus)
{
    uint32_t u32RetVal;

    u32RetVal = (pFciic->MSR >> (uint32_t)eStatus) & 0x01U;

    return (uint8_t)(u32RetVal == 1U ? 1U : 0U);
}

/**
 * @brief Clear master status
 *
 * Clears specific status flags in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @param u32Value Bitmask of the status flags to clear.
 */
LOCAL_INLINE void FCIIC_Master_HWA_ClrStatus(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MSR = u32Value;
}

/**
 * @brief Enable Receive Interrupt
 *
 * Enables the receive interrupt in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Master_HWA_EnableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER |= FCIIC_MIER_RDIE_MASK;
}

/**
 * @brief Disable Receive Interrupt
 *
 * Disables the receive interrupt in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Master_HWA_DisableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER &= ~FCIIC_MIER_RDIE_MASK;
}

/**
 * @brief Enable Error Interrupt
 *
 * Enables the error interrupt in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Master_HWA_EnableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER |= FCIIC_MIER_FEIE_MASK;
}

/**
 * @brief Disable Error Interrupt
 *
 * Disables the error interrupt in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Master_HWA_DisableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER &= ~FCIIC_MIER_FEIE_MASK;
}

/**
 * @brief Get Error Flag
 *
 * Gets the error flag in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @return Error flag value.
 */
LOCAL_INLINE uint32_t FCIIC_Master_HWA_GetErrorFlag(FCIIC_Type *pFciic)
{
    return pFciic->MSR & FCIIC_MSR_FEF_MASK;
}

/**
 * @brief Clear Error Flag
 *
 * Clears the error flag in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Master_HWA_ClrErrorFlag(FCIIC_Type *pFciic)
{
    pFciic->MSR |= FCIIC_MSR_FEF_MASK;
}

/**
 * @brief Enable Transmit Interrupt
 *
 * Enables the transmit interrupt in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Master_HWA_EnableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER |= FCIIC_MIER_TDIE_MASK;
}

/**
 * @brief Disable Transmit Interrupt
 *
 * Disables the transmit interrupt in the master mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Master_HWA_DisableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->MIER &= ~FCIIC_MIER_TDIE_MASK;
}

LOCAL_INLINE void FCIIC_HWA_SlaveReset(FCIIC_Type *const pFciic)
{
    pFciic->SCR |= FCIIC_SCR_RST_MASK;
    //base->SCR = 0;
}

/**
 * @brief Enable FCIIC SIER register bit.
 *
 * Enables a specific bit in the SIER register of the slave mode.
 *
 * @param[in] pFciic Pointer to the FCIIC instance value.
 * @param[in] u32Mask The enable bit mask.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_EnableInterrupt(FCIIC_Type *const pFciic, uint32 u32Mask)
{
    pFciic->SIER |= u32Mask;
}

/**
 * @brief Disable FCIIC SIER register bit.
 *
 * Disables a specific bit in the SIER register of the slave mode.
 *
 * @param[in] pFciic Pointer to the FCIIC instance value.
 * @param[in] u32Mask The disable bit mask.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_DisableInterrupt(FCIIC_Type *const pFciic, uint32 u32Mask)
{
    pFciic->SIER &= ~u32Mask;
}

/**
 * @brief Enable Receive Interrupt
 *
 * Enables the receive interrupt in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_EnableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER |= FCIIC_SIER_RDIE_MASK;
}

/**
 * @brief Disable Receive Interrupt
 *
 * Disables the receive interrupt in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_DisableReceiveInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER &= ~FCIIC_SIER_RDIE_MASK;
}

/**
 * @brief Enable Error Interrupt
 *
 * Enables the error interrupt in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_EnableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER |= FCIIC_SIER_TREIE_MASK | FCIIC_SIER_BEIE_MASK ;
}

/**
 * @brief Disable Error Interrupt
 *
 * Disables the error interrupt in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_DisableErrorInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER &= ~(FCIIC_SIER_TREIE_MASK | FCIIC_SIER_BEIE_MASK);
}

/**
 * @brief Get Error Flag
 *
 * Gets the error flag in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @return Error flag value.
 */
LOCAL_INLINE uint32_t FCIIC_Slave_HWA_GetErrorFlag(FCIIC_Type *pFciic)
{
    return pFciic->SSR & (FCIIC_SSR_TREF_MASK | FCIIC_SSR_BEF_MASK);
}

/**
 * @brief Clear Error Flag
 *
 * Clears the error flag in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_ClrErrorFlag(FCIIC_Type *pFciic)
{
    pFciic->SSR |= (FCIIC_SSR_TREF_MASK | FCIIC_SSR_BEF_MASK);
}

/**
 * @brief Enable Transmit Interrupt
 *
 * Enables the transmit interrupt in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_EnableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER |= FCIIC_SIER_TDIE_MASK;
}

/**
 * @brief Disable Transmit Interrupt
 *
 * Disables the transmit interrupt in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_DisableTransmitInterrupt(FCIIC_Type *pFciic)
{
    pFciic->SIER &= ~FCIIC_SIER_TDIE_MASK;  /* Receive Interrupt Enable    */
}

/**
 * @brief Enables or disables FCIIC Slave DMA requests.
 *
 * Enables or disables DMA requests for transmit and receive operations in the slave mode.
 *
 * @param pFciic Pointer to the FCIIC peripheral base address.
 * @param enableTx Enable flag for transmit DMA request. Pass true for enable, false for disable.
 * @param enableRx Enable flag for receive DMA request. Pass true for enable, false for disable.
 */
LOCAL_INLINE void FCIIC_HWA_SlaveEnableDMA(FCIIC_Type *const pFciic, bool enableTx, bool enableRx)
{
    pFciic->SDER = FCIIC_SDER_TDDE(enableTx) | FCIIC_SDER_RDDE(enableRx);
}

/**
 * @brief Checks if the slave enable flag is set in the SCR register.
 *
 * This function checks if the slave is enabled by reading the SCR register.
 *
 * @param pFciic Pointer to the FCIIC module instance.
 * @return 0x01 if the slave is enabled, 0x00 otherwise.
 */
LOCAL_INLINE uint8_t FCIIC_HWA_SlaveGetEnable(FCIIC_Type *const pFciic)
{
    return (pFciic->SCR & FCIIC_SCR_SEN_MASK) == FCIIC_SCR_SEN_MASK ? 0x01 : 0x00;
}

/**
 * @brief This Function is used to get slave status
 *
 * Reads a specific status flag in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @param eStatus Status type to read.
 * @return Status value (0 or 1), where 1 indicates the status is set.
 */
LOCAL_INLINE uint8_t FCIIC_Slave_HWA_GetStatus(FCIIC_Type *pFciic, FCIIC_SlaveStatusType eStatus)
{
    uint32_t u32RetVal;

    u32RetVal = (pFciic->SSR >> (uint32_t)eStatus) & 0x01U;

    return (uint8_t)(u32RetVal == 1U ? 1U : 0U);
}

/**
 * @brief This Function is used to clear slave status
 *
 * Clears specific status flags in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @param u32Value Bitmask of the status flags to clear.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_ClrStatus(FCIIC_Type *pFciic, uint32_t eStatus)
{
    pFciic->SSR = ((uint32)1U << (uint8)eStatus);  /* w1c */;
}

/**
 * @brief get FCIIC SIER register.
 *
 * Reads the SIER register value in the slave mode.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @return SIER register value.
 */
LOCAL_INLINE uint32 FCIIC_HWA_GetSIER(const FCIIC_Type *const pFciic)
{
    return (pFciic->SIER & FCIIC_SIER_MASK);
}

/**
 * @brief        Clear FCIIC SSR register bit.
 *
 * @param[in]    pFciic          The FCIIC instance value.
 * @param[in]    eStatus         The clear bit offset.
 *
 * @return       void.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_ClearStatus(FCIIC_Type *const pFciic, FCIIC_SlaveStatusType eStatus)
{
     pFciic->SSR = ((uint32)1U << (uint8)eStatus);  /* w1c */
}

/**
 * @brief Slave Transmit Data
 *
 * Transmits data in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @param u8Data Data byte to be transmitted.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_Transmit(FCIIC_Type *pFciic, uint8_t u8Data)
{
    pFciic->STDR = FCIIC_STDR_DATA(u8Data);
}

/**
 * @brief Slave Get Data
 *
 * Receives a data byte in the slave mode.
 *
 * @param pFciic Pointer to the IIC instance value.
 * @return Received data byte.
 */
LOCAL_INLINE uint8_t FCIIC_Slave_HWA_Receive(FCIIC_Type *pFciic)
{
    /* copy data */
    return (uint8_t)((uint8_t)(pFciic->SRDR) & 0xFFU);
}

/**
 * @brief Set FCIIC STAR register.
 *
 * Sets the STAR register value in the slave mode.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @param u32Value Register value to set.
 */
LOCAL_INLINE void FCIIC_Slave_HWA_NACK(FCIIC_Type *const pFciic, uint32 u32Value)
{
    pFciic->STAR = u32Value;
}

/**
 * @brief Set FCIIC MCR register
 *
 * Sets the MCR register value.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @param u32Value Register value to set.
 */
LOCAL_INLINE void FCIIC_HWA_SetMcr(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCR = u32Value;
}

/**
 * @brief Set FCIIC SSR register
 *
 * Reads the MSR register value.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @return MSR register value.
 */
LOCAL_INLINE uint32_t FCIIC_HWA_GetMSR(FCIIC_Type *pFciic)
{
    return pFciic->MSR;
}

/**
 * @brief Attach FCIIC MCR register
 *
 * Attaches a value to the MCR register.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @param u32Value Value to attach.
 */
LOCAL_INLINE void FCIIC_HWA_AttachMcr(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCR |= u32Value;
}

/**
 * @brief Set FCIIC MDER register
 *
 * Sets the MDER register value.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @param u32Value Register value to set.
 */
LOCAL_INLINE void FCIIC_HWA_SetMder(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MDER = u32Value;
}

/**
 * @brief get FCIIC MIER register.
 *
 * Reads the MIER register value.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @return MIER register value.
 */
LOCAL_INLINE uint32 FCIIC_HWA_GetMIER(const FCIIC_Type *const pFciic)
{
    return (pFciic->MIER & FCIIC_MIER_MASK);
}

/**
 * @brief Set FCIIC MCFGR0 register
 *
 * Sets the MCFGR0 register value.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 * @param u32Value Register value to set.
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR0(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR0 = u32Value;
}

/**
 * @brief get FCIIC MCFGR1 register
 *
 * Sets the MCFGR1 register value.
 *
 * @param pFciic Pointer to the FCIIC instance value.
 */
LOCAL_INLINE uint32_t FCIIC_HWA_GetMCFGR1(FCIIC_Type *pFciic)
{
    return pFciic->MCFGR1;
}

/**
 * @brief Set FCIIC MCFGR1 register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR1(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR1 = u32Value;
}

/**
 * @brief Set FCIIC MCFGR2 register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR2(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR2 = u32Value;
}

/**
 * @brief Set FCIIC MCFGR2 register
 *
 * @param pFciic FCIIC instance value
 */
LOCAL_INLINE uint32_t FCIIC_HWA_GetMCFGR2(FCIIC_Type *pFciic)
{
    return pFciic->MCFGR2;
}

/**
 * @brief Set FCIIC MCFGR3 register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCFGR3(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCFGR3 = u32Value;
}

/**
 * @brief Set FCIIC MFCR register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMFCR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MFCR = u32Value;
}

/**
 * @brief Set FCIIC MCCR register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetMCCR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->MCCR = u32Value;
}

/**
 * @brief Set FCIIC SDER register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSDER(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SDER = u32Value;
}

/**
 * @brief Set FCIIC SCFGR1 register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSCFGR1(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SCFGR1 = u32Value;
}

/**
 * @brief Set FCIIC SSR register
 *
 * @param pFciic FCIIC instance value
 */
LOCAL_INLINE uint32_t FCIIC_HWA_GetSCFGR1(FCIIC_Type *pFciic)
{
    return pFciic->SCFGR1;
}

/**
 * @brief Set FCIIC MCCR register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSCFGR2(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SCFGR2 = u32Value;
}

/**
 * @brief Set FCIIC MCCR register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSAMR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SAMR = u32Value;
}

/**
 * @brief Set FCIIC MCCR register
 *
 * @param pFciic FCIIC instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCIIC_HWA_SetSCR(FCIIC_Type *pFciic, uint32_t u32Value)
{
    pFciic->SCR = u32Value;
}

/**
 * @brief Set FCIIC SSR register
 *
 * @param pFciic FCIIC instance value
 */
LOCAL_INLINE uint32_t FCIIC_HWA_GetSSR(FCIIC_Type *pFciic)
{
    return pFciic->SSR;
}

/**
 * @brief        Set FCIIC SDER register.
 *
 * @param[in]    pFciic          The FCIIC instance value.
 *
 * @return       void.
 */
LOCAL_INLINE uint32 FCIIC_HWA_GetSDER(FCIIC_Type *const pFciic)
{
    return pFciic->SDER ;
}
/**
 * @brief        Get FCIIC slave received address.
 *
 * @param[in]    pFciic          The FCIIC instance value.
 *
 * @return       uint32          The received address.
 */
LOCAL_INLINE uint32 FCIIC_HWA_GetSASR(const FCIIC_Type *const pFciic)
{
    return (pFciic->SASR & FCIIC_SASR_RADDR_MASK);
}

/** @}*/
#endif

#endif /* end for #ifndef _HWA_FCIIC_H_ */
