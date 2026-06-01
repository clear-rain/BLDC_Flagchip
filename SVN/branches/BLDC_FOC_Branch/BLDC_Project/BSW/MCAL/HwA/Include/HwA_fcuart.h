/**
 * @file HwA_fcuart.h
 * @author Flagchip
 * @brief FCUART hardware access layer
 * @version 2.0.0
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/

#ifndef _HWA_FCUART_H_
#define _HWA_FCUART_H_

#include "device_header.h"

#if FCUART_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_fcuart HwA_fcuart
 * @ingroup module_driver_fcuart
 * @ingroup module_driver_lin
 * @{
 */


/* ################################################################################## */
/* ################################### type define ################################## */

/**
 * @brief UART STAT register flag
 *
 */
typedef enum
{
    FCUART_STAT_LBKDIF = FCUART_STAT_LBKDIF_MASK, /**< FCUART_STAT_LBKDIF  LIN Break Detect Interrupt Flag,    w1c */
    FCUART_STAT_RPAEIF = FCUART_STAT_RPAEIF_MASK, /**< FCUART_STAT_RPAEIF  RXD Pin Active Edge Interrupt Flag, w1c */
    FCUART_STAT_MSBF   = FCUART_STAT_MSBF_MASK,   /**< FCUART_STAT_MSBF    MSB First,                          RW  */
    FCUART_STAT_RXINV  = FCUART_STAT_RXINV_MASK,  /**< FCUART_STAT_RXINV   Receive Data Inversion,             RW  */
    FCUART_STAT_RWUID  = FCUART_STAT_RWUID_MASK,  /**< FCUART_STAT_RWUID   Receive Wake Up Idle Detect,        RW  */
    FCUART_STAT_BCGL   = FCUART_STAT_BCGL_MASK,   /**< FCUART_STAT_BCGL    Break Character Generation Length,  RW  */
    FCUART_STAT_LBKDE  = FCUART_STAT_LBKDE_MASK,  /**< FCUART_STAT_LBKDE   LIN Break Detection Enable,         RW  */
    FCUART_STAT_RAF    = FCUART_STAT_RAF_MASK,    /**< FCUART_STAT_RAF     Receiver Active Flag,               RO  */
    FCUART_STAT_TDREF  = FCUART_STAT_TDREF_MASK,  /**< FCUART_STAT_TDREF   Transmit Data Register Empty Flag,  RO  */
    FCUART_STAT_TCF    = FCUART_STAT_TCF_MASK,    /**< FCUART_STAT_TCF     Transmission Complete Flag,         RO  */
    FCUART_STAT_RDRFF  = FCUART_STAT_RDRFF_MASK,  /**< FCUART_STAT_RDRFF   Receive Data Register Full Flag,    RO  */
    FCUART_STAT_IDLEF  = FCUART_STAT_IDLEF_MASK,  /**< FCUART_STAT_IDLEF   Idle Line Flag,                     w1c */
    FCUART_STAT_RORF   = FCUART_STAT_RORF_MASK,   /**< FCUART_STAT_RORF    Receiver Overrun Flag,              w1c */
    FCUART_STAT_NF     = FCUART_STAT_NF_MASK,     /**< FCUART_STAT_NF      Noise Flag,                         w1c */
    FCUART_STAT_FEF    = FCUART_STAT_FEF_MASK,    /**< FCUART_STAT_FEF     Frame Error Flag,                   w1c */
    FCUART_STAT_PEF    = FCUART_STAT_PEF_MASK,    /**< FCUART_STAT_PEF     Parity Error Flag,                  w1c */
    FCUART_STAT_M0F    = FCUART_STAT_M0F_MASK,    /**< FCUART_STAT_M0F     Match address 0 Flag,               w1c */
    FCUART_STAT_M1F    = FCUART_STAT_M1F_MASK,    /**< FCUART_STAT_M1F     Match address 1 Flag,               w1c */
    FCUART_STAT_RPEF   = FCUART_STAT_RPEF_MASK,   /**< FCUART_STAT_RPEF    Receive Data Parity Error Flag,     w1c */
    FCUART_STAT_TPEF   = FCUART_STAT_TPEF_MASK    /**< FCUART_STAT_TPEF    Transmit Data Parity Error Flag,    w1c */
} FCUART_StatType;



/**
 * @brief  UART data bit length mode
 *
 */
typedef enum
{
    UART_BITMODE_8 = 0, /**< UART_BITMODE_8 */
    UART_BITMODE_9   /**< UART_BITMODE_9 */
} FCUART_BitModeType;

/**
 * @brief UART stop bits number
 *
 */
typedef enum
{
    UART_STOPBIT_NUM_1 = 0, /**< UART_STOPBIT_NUM_1 */
    UART_STOPBIT_NUM_2   /**< UART_STOPBIT_NUM_2 */
} FCUART_StopBitNumType;

/**
 * @brief UART parity check type
 *
 */
typedef enum
{
    UART_PARITY_EVEN = 0, /**< UART_PARITY_EVEN */
    UART_PARITY_ODD    /**< UART_PARITY_ODD  */
} FCUART_ParityType;




/* ################################################################################## */
/* ################################### Local Inline ################################# */
/**
 * @brief Get Stat Flag
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_SetSoftWareReset(FCUART_Type  *pUart)
{
	pUart->RST |= FCUART_RST_RST_MASK;
	pUart->RST &= ~FCUART_RST_RST_MASK;
}

/**
 * @brief Get Stat Flag
 *
 * @param pUart  UART instance value
 * @param eStatusType  stat type
 * @return FCUART STAT status flag
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetStatus(FCUART_Type  *pUart, FCUART_StatType eStatusType)
{
    return (pUart->STAT & (uint32_t)eStatusType);
}

/**
 * @brief Clear Stat Flag
 *
 * @param pUart  UART instance value
 * @param u32StatusType  stat type
 */
LOCAL_INLINE void FCUART_HWA_ClearStatus(FCUART_Type  *pUart, uint32_t u32StatusType)
{
    pUart->STAT |= u32StatusType;
}

/**
 * @brief Start transmit
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_StartTransmit(FCUART_Type  *pUart)
{
    pUart->CTRL |= FCUART_CTRL_TE_MASK; /* start transmit */
}

/**
 * @brief clear transmit
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_ClearTransmit(FCUART_Type  *pUart)
{
    pUart->CTRL &= ~FCUART_CTRL_TE_MASK; /* clear transmit */
}


/**
 * @brief Start receive
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_StartReceive(FCUART_Type  *pUart)
{
    pUart->CTRL |= FCUART_CTRL_RE_MASK; /* start receive */
}

/**
 * @brief clear receive
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_ClearReceive(FCUART_Type  *pUart)
{
    pUart->CTRL &= ~FCUART_CTRL_RE_MASK; /* clear receive */
}


/**
 * @brief Enable Interrupt
 *
 * @param pUart     UART instance value
 * @param u32Value  CTRL register value
 */
LOCAL_INLINE void FCUART_HWA_EnableInterrupt(FCUART_Type  *pUart, uint32 u32Value)
{
    pUart->CTRL |= u32Value;  /* Interrupt Enable    */
}

/**
 * @brief Disable Interrupt
 *
 * @param pUart  UART instance value
 * @param u32Value control value
 */
LOCAL_INLINE void FCUART_HWA_DisableInterrupt(FCUART_Type  *pUart, uint32 u32Value)
{
    pUart->CTRL &= ~u32Value;  /* Interrupt Disable    */
}


/**
 * @brief Set FCUART Ctrl register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetCtrl(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->CTRL = u32Value;
}

/**
 * @brief Get FCUART Ctrl register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetCtrl(FCUART_Type  *pUart)
{
    return pUart->CTRL;
}

/**
 * @brief Attach FCUART Ctrl register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachCtrl(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->CTRL |= u32Value;
}


/**
 * @brief Set FCUART Baud register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetBaud(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->BAUD = u32Value;
}

/**
 * @brief Attach FCUART Baud register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachBaud(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->BAUD |= u32Value;
}

/**
 * @brief Set FCUART Fifo register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetFifo(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->FIFO = u32Value;
}

/**
 * @brief Attach FCUART Fifo register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachFifo(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->FIFO |= u32Value;
}

/**
 * @brief Set FCUART WaterMark register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetWaterMark(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->WATERMARK = u32Value;
}

/**
 * @brief Attach FCUART WaterMark register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachWaterMark(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->WATERMARK |= u32Value;
}

/**
 * @brief Set FCUART Match register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_SetMatch(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->MATCH = u32Value;
}

/**
 * @brief Attach FCUART Match register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_AttachMatch(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->MATCH |= u32Value;
}

/**
 * @brief Read FCUART STAT register
 *
 * @param pUart UART instance value
 * @return STAT read value
 */
LOCAL_INLINE uint32_t FCUART_HWA_ReadSTAT(FCUART_Type  *pUart)
{
    return pUart->STAT;
}

/**
 * @brief Write 1 Clear FCUART STAT register
 *
 * @param pUart UART instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FCUART_HWA_WriteClearSTAT(FCUART_Type  *pUart, uint32_t u32Value)
{
    pUart->STAT |= u32Value;
}

/**
 * @brief Set Bit Mode and Parity
 *
 * @param pUart  UART instance value
 * @param eBitMode  is bit mode, 8 or 9 bits
 * @param bParityEnable  If enable Parity, set 1U, or set 0U
 * @param eParityType  Parity type, odd-even
 * @param eStopBit  stop bits number 1 or 2 bits
 */
LOCAL_INLINE void FCUART_HWA_SetBitModeAndParity(FCUART_Type  *pUart, FCUART_BitModeType eBitMode, uint8_t bParityEnable, FCUART_ParityType eParityType,
                                                 FCUART_StopBitNumType  eStopBit)
{
    /* clear last value */
    pUart->CTRL &= ~(FCUART_CTRL_BMSEL_MASK | FCUART_CTRL_PE_MASK | FCUART_CTRL_PT_MASK);
    pUart->BAUD &= ~FCUART_BAUD_SBNS_MASK;

    /* set new value */
    pUart->CTRL |= FCUART_CTRL_BMSEL(eBitMode)       |  /* 9-Bit or 8-Bit Mode Select                           */
                   FCUART_CTRL_PE(bParityEnable)    |  /* Parity Enable                                        */
                   FCUART_CTRL_PT(eParityType);        /* Parity Type                                          */
    pUart->BAUD |= FCUART_BAUD_SBNS(eStopBit);          /* Stop Bit Number Select                               */
}



/**
 * @brief Enable Receive DMA
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableReceiveDMA(FCUART_Type  *pUart)
{
    pUart->BAUD |= FCUART_BAUD_RDMAEN_MASK;
}

/**
 * @brief Disable Receive DMA
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableReceiveDMA(FCUART_Type  *pUart)
{
    pUart->BAUD &= ~FCUART_BAUD_RDMAEN_MASK;

}


/**
 * @brief Enable Receive FIFO
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableReceiveFIFO(FCUART_Type  *pUart)
{
    pUart->FIFO |= FCUART_FIFO_RXFEN_MASK;
}

/**
 * @brief Disable Receive FIFO
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableReceiveFIFO(FCUART_Type  *pUart)
{
    pUart->FIFO &= ~FCUART_FIFO_RXFEN_MASK;

}

/**
 * @brief Get FCUART fifo register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE bool FCUART_HWA_GetEnStatusRxFifo(FCUART_Type  *pUart)
{
	return ((((pUart->FIFO & FCUART_FIFO_RXFEN_MASK) >> FCUART_FIFO_RXFEN_SHIFT) == 1U) ? true: false);
}

/**
 * @brief Get FCUART fifo register
 *
 * @param pUart UART instance value
 * @return Register value
 */
LOCAL_INLINE bool FCUART_HWA_GetEnStatusTxFifo(FCUART_Type  *pUart)
{
	return ((((pUart->FIFO & FCUART_FIFO_TXFEN_MASK) >> FCUART_FIFO_TXFEN_SHIFT) == 1U) ? true: false);
}

/**
 * @brief Get FCUART Rx WaterMark
 *
 * @param pUart UART instance value
 * @return Rxcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetRxWaterMark(FCUART_Type  *pUart)
{
	return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_RXWATER_MASK) >> FCUART_WATERMARK_RXWATER_SHIFT));
}

/**
 * @brief Get FCUART Tx WaterMark
 *
 * @param pUart UART instance value
 * @return Rxcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetTxWaterMark(FCUART_Type  *pUart)
{
	return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_TXWATER_MASK) >> FCUART_WATERMARK_TXWATER_SHIFT));
}

/**
 * @brief Get FCUART FIFO Rxcount
 *
 * @param pUart UART instance value
 * @return Rxcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetFifoRxCount(FCUART_Type  *pUart)
{
	return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_RXCOUNT_MASK) >> FCUART_WATERMARK_RXCOUNT_SHIFT));
}

/**
 * @brief Get FCUART FIFO Txcount
 *
 * @param pUart UART instance value
 * @return Txcount value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetFifoTxCount(FCUART_Type  *pUart)
{
	return ((uint8_t)(((pUart->WATERMARK) & FCUART_WATERMARK_TXCOUNT_MASK) >> FCUART_WATERMARK_TXCOUNT_SHIFT));
}


/**
 * @brief Set Data Value
 *
 * @param pUart  UART instance value
 * @param u32Data Set data
 */
LOCAL_INLINE void FCUART_HWA_SetData(FCUART_Type  *pUart, uint32_t u32Data)
{
    pUart->DATA = u32Data; /* data 32 bit */
}

/**
 * @brief Get Data Value
 *
 * @param pUart  UART instance value
 * @return the data value
 */
LOCAL_INLINE uint8_t FCUART_HWA_GetData(FCUART_Type  *pUart)
{
    uint8_t u8Data;

    u8Data = *((volatile uint8_t *)&pUart->DATA); /* data 32 bit */

    return u8Data;
}

/**
 * @brief Reset the instance by software.
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_SoftwareReset(FCUART_Type  *pUart)
{
    pUart->RST |= FCUART_RST_RST_MASK;
    pUart->RST &= ~FCUART_RST_RST_MASK;
}

/**
 * @brief Set fcuart TX Transfer enable or disable.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetTxTransfer(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->CTRL |= FCUART_CTRL_TE_MASK;
    }
    else
    {
        pUart->CTRL &= ~FCUART_CTRL_TE_MASK;
    }
}

/**
 * @brief Set fcuart RX Transfer enable or disable.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetRxTransfer(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->CTRL |= FCUART_CTRL_RE_MASK;
    }
    else
    {
        pUart->CTRL &= ~FCUART_CTRL_RE_MASK;
    }
}

/**
 * @brief Set lin break detect interrupt.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetLinBreakDetectInterrupt(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->BAUD |= FCUART_BAUD_LBKDIE_MASK;
    }
    else
    {
        pUart->BAUD &= ~FCUART_BAUD_LBKDIE_MASK;
    }
}

/**
 * @brief Set lin break detect feature enable.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetLinBreakDetectEnable(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->STAT |= (FCUART_STAT_LBKDE_MASK | FCUART_STAT_BCGL_MASK);
    }
    else
    {
        pUart->STAT &= ~(FCUART_STAT_LBKDE_MASK | FCUART_STAT_BCGL_MASK);
    }
}

/**
 * @brief Send a lin break field.
 *
 * @param pUart  UART instance value
 */
LOCAL_INLINE void FCUART_HWA_SendBreakField(FCUART_Type  *pUart)
{
    pUart->DATA = FCUART_DATA_FETSC_MASK;
}

/**
 * @brief Set uart receive active interrupt.
 *
 * @param pUart  UART instance value
 * @param bEnable  Enable cmd, false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetReceiveActiveInterrupt(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->BAUD |= FCUART_BAUD_RIAEIE_MASK;
    }
    else
    {
        pUart->BAUD &= ~FCUART_BAUD_RIAEIE_MASK;
    }
}

/**
 * @brief Set uart receive active interrupt.
 *
 * @param pUart  UART instance value
 * @return   false for disable, true for enable.
 */
LOCAL_INLINE bool FCUART_HWA_GetReceiveActiveInterrupt(FCUART_Type  *pUart)
{
    bool bRetVal = false;
    
    if (0U != (pUart->BAUD & FCUART_BAUD_RIAEIE_MASK))
    {
        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief Set FCUART inverse feature.
 *
 * @param pUart  UART instance value
 * @param bEnable   false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetReceiveDataInverse(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->STAT |= FCUART_STAT_RXINV_MASK;
    }
    else
    {
        pUart->STAT &= ~FCUART_STAT_RXINV_MASK;
    }
}

/**
 * @brief Get the FCUART inverse bit value.
 *
 * @param pUart  UART instance value
 * @return   false for disable, true for enable.
 */
LOCAL_INLINE bool FCUART_HWA_GetReceiveDataInverse(FCUART_Type  *pUart)
{
    bool bRetVal = false;
    
    if (0U != (pUart->STAT & FCUART_STAT_RXINV_MASK))
    {
        bRetVal = true;
    }

    return bRetVal;
}

/**
 * @brief Set the FCUART frame error interrupt.
 *
 * @param pUart     UART instance value
 * @param bEnable   false for disable, true for enable.
 */
LOCAL_INLINE void FCUART_HWA_SetFrameErrorInterrupt(FCUART_Type  *pUart, bool bEnable)
{
    if (true == bEnable)
    {
        pUart->CTRL |= FCUART_CTRL_FEIE_MASK;
    }
    else
    {
        pUart->CTRL &= ~FCUART_CTRL_FEIE_MASK;
    }
}

/**
 * @brief Enable the FCUART loop mode.
 *
 * @param pUart     UART instance value
 */
LOCAL_INLINE void FCUART_HWA_EnableLoopMode(FCUART_Type  *pUart)
{
	pUart->CTRL |= FCUART_CTRL_LOOPMS_MASK;
}

/**
 * @brief Disable the FCUART loop mode.
 *
 * @param pUart     UART instance value
 */
LOCAL_INLINE void FCUART_HWA_DisableLoopMode(FCUART_Type  *pUart)
{
	pUart->CTRL &= ~FCUART_CTRL_LOOPMS_MASK;
}


/**
 * @brief Set FCUART MODIR value
 *
 * @param pUart  UART instance value
 * @param u32Data Set data
 */
LOCAL_INLINE void FCUART_HWA_SetModir(FCUART_Type  *pUart, uint32_t u32Data)
{
    pUart->MODIR = u32Data; /* data 32 bit */
}

/**
 * @brief Get FCUART MODIR value
 *
 * @param pUart  UART instance value
 * @return MODIR value
 */
LOCAL_INLINE uint32_t FCUART_HWA_GetModir(FCUART_Type  *pUart)
{
    return pUart->MODIR ;
}


/** @}*/

#endif

#endif /* end for #ifndef _HWA_FCUART_H_ */
