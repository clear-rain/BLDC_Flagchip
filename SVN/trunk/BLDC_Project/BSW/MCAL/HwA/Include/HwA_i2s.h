/**
 * @file HwA_i2s.h
 * @author Flagchip100
 * @brief I2S hardware access layer
 * @version 2.0.0
 * @date 2024-07-16
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#ifndef _HWA_I2S_H_
#define _HWA_I2S_H_

#include "device_header.h"

#if I2S_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_i2s HwA_i2s
 * @ingroup module_driver_i2s
 * @{
 */

/**
 * @brief   The Synchronous Mode
*/
typedef enum
{
    I2S_TX_ASYNCHRONOUS_MODE = 0U,
    I2S_TX_SYNCHRONOUS_MODE  = 1U
} I2S_TX_SynchronousMode;

/**
 * @brief The MclkSel Mode
 *
 * @note Select the clock source for MCLK. For more information,
 * please refer to Clock Configuration
 */
typedef enum
{
    I2S_TX_MCLK_SEL_BUS      = 0U,
    I2S_TX_MCLK_SEL_XMCLK    = 1U,
    I2S_TX_MCLK_SEL_YMCLK    = 2U,
    I2S_TX_MCLK_SEL_RESERVED = 3U
} I2S_TX_MclkSelType;

/**
 * @brief The BCLK Polarity
 *
 */
typedef enum
{
    I2S_TX_BCLK_ACTIVEHIGH = 0U,    /**< BCLK is active high with drive outputs on rising edge and sample inputs on falling edge */
    I2S_TX_BCLK_ACTIVLOW   = 1U     /**< BCLK is active low with drive outputs on falling edge and sample inputs on rising edge */
} I2S_TX_BclkPolarityMode;


/**
 * @brief  The BCLK Direction
 *
 */
typedef enum
{
    I2S_TX_BCLKDIR_IN  = 0U,        /**< Use external BCLK in Slave mode */
    I2S_TX_BCLKDIR_OUT = 1U         /**< Use internal BCLK in Master mode */
} I2S_TX_BclkDir;

/**
 * @brief  The I2S channel
 *
 */
typedef enum
{
    I2S_TX_CHANNEL_0 = 1U,
    I2S_TX_CHANNEL_1 = 2U,
    I2S_TX_CHANNEL_2 = 4U,
    I2S_TX_CHANNEL_3 = 8U

} I2S_TX_ChannelType;

/**
 * @brief The underrun restart mode
 *
 * @note In restart mode 0, once FIFO underrun detected, the I2S will restart from the start of the next frame
 *  after the FIFO underrun flag has been cleared.In restart mode 1, once FIFO underrun detected, the I2S will
 *  restart from the same data that caused the FIFO underrun flag to set after the FIFO empty flag has been cleared.
 */
typedef enum
{
    I2S_TX_RESTART_MODE0 = 0U,
    I2S_TX_RESTART_MODE1 = 1U
} I2S_TX_RestartMode;

/**
 * @brief The FIFO Packing Mode
 *
 */
typedef enum
{
    I2S_TX_FIFOPACK_DISABLE  = 0U,
    I2S_TX_FIFOPACK_RESERVED = 1U,
    I2S_TX_FIFOPACK_8BIT     = 2U,
    I2S_TX_FIFOPACK_16BIT    = 3U
} I2S_TX_FifoPackMode;

/**
 * @brief  The Pin Mode
 *
 */
typedef enum
{
    I2S_MASKED_TRISTATED = 0U,      /**< Transmit data pins are tri-stated when data are masked or channels are disabled */
    I2S_MASKED_ZERO      = 1U       /**< Transmit data pins output zero when data are masked or channels are disabled */
} I2S_MaskedPinMode;

/**
 * @brief  MSB First
 *
 */
typedef enum
{
    I2S_TX_LSB_FIRST = 0U,          /**< LSB is transmitted first */
    I2S_TX_MSB_FIRST = 1U           /**< for most case ,MSB is transmitted first */
} I2S_TX_Priority;

/**
 * @brief  Frame Sync Early Mode
 *
 */
typedef enum
{
    I2S_TX_Firstbit  = 0U,          /**< Frame sync asserts with the first bit of the frame */
    I2S_TX_Onebitear = 1U           /**< Frame sync asserts one bit before the first bit of the frame */
} I2S_TXEarlySyncMode;

/**
 * @brief   Frame Sync Mode
 *
 */
typedef enum
{
    I2S_TX_SYNC_MODE0 = 0U,         /**< Continuous frame sync */
    I2S_TX_SYNC_MODE1 = 1U          /**< No frame sync generated when FIFO empty flag set */
} I2S_TXSyncMode;

/**
 * @brief Frame Sync Polarity
 *
 */
typedef enum
{
    I2S_TX_SYNC_POLARITY_HIGH = 0U,
    I2S_TX_SYNC_POLARITY_LOW  = 1U
} I2S_TX_SyncPolarity;

/**
 * @brief Frame Sync Direction
 *
 */
typedef enum
{
    I2S_TX_FRAME_SYNCDIR_IN  = 0U,
    I2S_TX_FRAME_SYNCDIR_OUT = 1U
} I2S_TX_FrameSyncDir;

/**
 * @brief   the I2S TX Fifo channel
 *
 */
typedef enum
{
    I2S_TX_FIFO_CHANNEL0 = 0U,
    I2S_TX_FIFO_CHANNEL1 = 1U,
    I2S_TX_FIFO_CHANNEL2 = 2U,
    I2S_TX_FIFO_CHANNEL3 = 3U
} I2S_TX_FifoChannel;

/**
 * @brief The Synchronous Mode
 *
 */
typedef enum
{
    I2S_RX_ASYNCHRONOUS_MODE = 0U,      /**< Asynchronous with receiver */
    I2S_RX_SYNCHRONOUS_MODE  = 1U       /**< Synchronous with receiver */
} I2S_RX_SynchronousMode;

/**
 * @brief The MclkSel Mode
 *
 * @note Select the clock source for MCLK. For more information, please refer to Clock Configuration.
 */
typedef enum
{
    I2S_RX_MCLK_SEL_BUS      = 0U,
    I2S_RX_MCLK_SEL_XMCLK    = 1U,
    I2S_RX_MCLK_SEL_YMCLK    = 2U,
    I2S_RX_MCLK_SEL_RESERVED = 3U
} I2S_RX_MclkSelType;

/**
 * @brief  The BCLK Polarity
 *
 */
typedef enum
{
    I2S_RX_BCLK_ACTIVEHIGH = 0u,    /**< BCLK is active high with drive outputs on rising edge and sample inputs on falling edge */
    I2S_RX_BCLK_ACTIVLOW = 1u       /**< BCLK is active low with drive outputs on falling edge and sample inputs on rising edge */
} I2S_RX_BclkPolarityMode;

/**
 * @brief  The BCLK Direction
 *
 */
typedef enum
{
    I2S_RX_BCLKDIR_IN  = 0U,        /**< Use external BCLK in Slave mode */
    I2S_RX_BCLKDIR_OUT = 1U         /**< Use internal BCLK in Master mode */
} I2S_RX_BclkDir;

/**
 * @brief   the I2S RX channel
 *
 */
typedef enum
{
    I2S_RX_CHANNEL_0 = 1U,
    I2S_RX_CHANNEL_1 = 2U,
    I2S_RX_CHANNEL_2 = 4U,
    I2S_RX_CHANNEL_3 = 8U
} I2S_RX_ChannelType ;

/**
 * @brief The overrun restart mode
 *
 * @note In restart mode 0, once FIFO overflow detected, the I2S will restart from the
 *  start of the next frame after the FIFO overflow flag has been cleared.In restart
 *  mode 1, once FIFO overflow detected, the I2S will restart from the same data that
 *  caused the FIFO overflow flag to set after the FIFO full flag has been cleared.
 */
typedef enum
{
    I2S_RX_RESTART_MODE0 = 0U,
    I2S_RX_RESTART_MODE1 = 1U
} I2S_RX_RestartMode;

/**
 * @brief The FIFO Packing Mode
 *
 */
typedef enum
{
    I2S_RX_FIFOPACK_DISABLE  = 0U,
    I2S_RX_FIFOPACK_RESERVED = 1U,
    I2S_RX_FIFOPACK_8BIT     = 2U,
    I2S_RX_FIFOPACK_16BIT    = 3U
} I2S_RX_FifoPackMode;

/**
 * @brief  MSB First
 *
 */
typedef enum
{
    I2S_RX_LSB_FIRST = 0U,          /**< LSB is transmitted first */
    I2S_RX_MSB_FIRST = 1U           /**< for most case ,MSB is transmitted first */
} I2S_RX_Priority;

/**
 * @brief Frame Sync Early Mode
 *
 */
typedef enum
{
    I2S_RX_Firstbit  = 0U,          /**< Frame sync asserts with the first bit of the frame */
    I2S_RX_Onebitear = 1U           /**< Frame sync asserts one bit before the first bit of the frame */
} I2S_RXEarlySyncMode;

/**
 * @brief   Frame Sync Early Mode
 *
 */
typedef enum
{
    I2S_RX_SYNC_MODE0 = 0U,         /**< Frame sync asserts with the first bit of the frame */
    I2S_RX_SYNC_MODE1 = 1U          /**< Frame sync asserts one bit before the first bit of the frame */
} I2S_RXSyncMode;

/**
 * @brief Frame Sync Polarity
 *
 */
typedef enum
{
    I2S_RX_SYNC_POLARITY_HIGH = 0U,
    I2S_RX_SYNC_POLARITY_LOW  = 1U
} I2S_RX_SyncPolarity;

/**
 * @brief Frame Sync Direction
 *
 */
typedef enum
{
    I2S_RX_FRAME_SYNCDIR_IN  = 0U,
    I2S_RX_FRAME_SYNCDIR_OUT = 1U
} I2S_RX_FrameSyncDir;

/**
 * @brief I2S Rx Fifo Channel
 *
 */
typedef enum
{
    I2S_RX_FIFO_CHANNEL0 = 0U,
    I2S_RX_FIFO_CHANNEL1 = 1U,
    I2S_RX_FIFO_CHANNEL2 = 2U,
    I2S_RX_FIFO_CHANNEL3 = 3U
} I2S_RX_FifoChannel;

/**
 * @brief Enable the transmited
 *
 * @param pI2s the base address of the I2S instance
 * @note  When transmitting a frame, this bit can not be cleared
 * by software until the end of the frame.
 */
LOCAL_INLINE void I2S_HWA_TX_Enable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_TXEN_MASK;
}

/**
 * @brief Disable the transmited
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_Disable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_TXEN_MASK;
}

/**
 * @brief Enable the transmitter in stop mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_STOP_Enable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_STOPEN_MASK;
}

/**
 * @brief Disable the transmitter in stop mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_STOP_Disable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_STOPEN_MASK;
}

/**
 * @brief Enable the transmitter in Debug mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DBG_Enable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_DBGEN_MASK;
}

/**
 * @brief Disable the transmitter in Debug mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DBG_Disable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_DBGEN_MASK;
}

/**
 * @brief Enable BCLK of transmitter
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_BCLK_Enable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_BCKEN_MASK;
}

/**
 * @brief Disable BCLK of transmitter
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_BCLK_Disable(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_BCKEN_MASK;
}

/**
 * @brief Reset all transmit FIFOs
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_RSTAllFifo(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_FIFORST_MASK;
}

/**
 * @brief Reset the internal transmitter logic including the FIFO read and write pointers
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_SWRST(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_SWRST_MASK;
}

/**
 * @brief Clear the Data Start Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_ClearDataFlag(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_DATA_SF_MASK;
}

/**
 * @brief Get the Data Start Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_TX_GetDataFlag(I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->TX_IDF & I2S_TX_IDF_DATA_SF_MASK) >> I2S_TX_IDF_DATA_SF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Clear the sync error Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_ClearSyncFlag(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_SYNC_EF_MASK;
}

/**
 * @brief Get the sync error Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_TX_GetSyncFlag(I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->TX_IDF & I2S_TX_IDF_SYNC_EF_MASK) >> I2S_TX_IDF_SYNC_EF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Clear the underrun Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_ClearUnderrunFlag(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_FIFO_UF_MASK;
}

/**
 * @brief Get the underrun Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_TX_GetUnderrunFlag(I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->TX_IDF & I2S_TX_IDF_FIFO_UF_MASK) >> I2S_TX_IDF_FIFO_UF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Get the FIFO empty Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_TX_GetFifoEmptyFlag(const I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->TX_IDF & I2S_TX_IDF_FIFO_EF_MASK) >> I2S_TX_IDF_FIFO_EF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Get the FIFO request Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_TX_GetFifoRequestFlag(const I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->TX_IDF & I2S_TX_IDF_FIFO_RF_MASK) >> I2S_TX_IDF_FIFO_RF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Data Start Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_EnableDataInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_DATA_SIE_MASK;
}

/**
 * @brief Data Start Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DisableDataInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_DATA_SIE_MASK;
}

/**
 * @brief Sync Error Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_EnableSyncInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_SYNC_EIE_MASK;
}

/**
 * @brief Sync Error Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DisableSyncInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_SYNC_EIE_MASK;
}

/**
 * @brief FIFO Underrun Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_EnableFifounderrunInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_FIFO_UIE_MASK;
}

/**
 * @brief FIFO Underrun Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DisableFifounderrunInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_FIFO_UIE_MASK;
}

/**
 * @brief FIFO empty Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_EnableFifoEmptyInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_FIFO_EIE_MASK;
}

/**
 * @brief FIFO empty Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DisableFifoEmptyInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_FIFO_EIE_MASK;
}

/**
 * @brief FIFO request Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_EnableFifoRequestInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_FIFO_RIE_MASK;
}

/**
 * @brief FIFO request Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DisableFifoRequestInterrupt(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_FIFO_RIE_MASK;
}

/**
 * @brief FIFO empty DMA Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_EnableFifoEmptyDMA(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_FIFO_EDE_MASK;
}

/**
 * @brief FIFO empty DMA Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DisableFifoEmptyDMA(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_FIFO_EDE_MASK;
}

/**
 * @brief FIFO Request DMA Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_EnableFifoRequestDMA(I2S_Type *const pI2s)
{
    pI2s->TX_IDF |= (uint32_t)I2S_TX_IDF_FIFO_RDE_MASK;
}

/**
 * @brief FIFO Request DMA Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_TX_DisableFifoRequestDMA(I2S_Type *const pI2s)
{
    pI2s->TX_IDF &= ~(uint32_t)I2S_TX_IDF_FIFO_RDE_MASK;
}

/**
 * @brief Configures the watermark for all enabled transmit channels
 *
 * @param pI2s the base address of the I2S instance
 * @param Watermark the Watermak
 */
LOCAL_INLINE void I2S_HWA_TX_SetWatermark(I2S_Type *const pI2s, uint32_t Watermark)
{
    if (Watermark > 7u)
    {
        Watermark = 7u;
    }
    pI2s->TX_FIFO_CFG = (pI2s->TX_FIFO_CFG & ~I2S_TX_FIFO_CFG_FWM_MASK) | I2S_TX_FIFO_CFG_FWM(Watermark);
}

/**
 * @brief Select the Synchronous Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the Syncchronous Mode
 * @note The receiver must be configured as asynchronous mode, if the transmitter is configured as
 * synchronous mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetTxSynchronousMode(I2S_Type *const pI2s, I2S_TX_SynchronousMode TempMode)
{
    pI2s->TX_CLK_CFG = (pI2s->TX_CLK_CFG & ~I2S_TX_CLK_CFG_SYNC_MASK) | I2S_TX_CLK_CFG_SYNC(TempMode);
}

/**
 * @brief Bit Clock Loopback  from PAD
 *
 * @param pI2s the base address of the I2S instance
 * @note if Set BitLookback ,should set Synchronous Mode too
 */
LOCAL_INLINE void I2S_HWA_TX_SetBitLookback(I2S_Type *const pI2s)
{
    pI2s->TX_CLK_CFG |= I2S_TX_CLK_CFG_BCLK_LB_MASK;
}

/**
 * @brief Select the MCLK source
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the source Mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetTxMclkSelect(I2S_Type *const pI2s, I2S_TX_MclkSelType TempMode)
{
    pI2s->TX_CLK_CFG = (pI2s->TX_CLK_CFG & ~I2S_TX_CLK_CFG_MCLK_SEL_MASK) | I2S_TX_CLK_CFG_MCLK_SEL(TempMode);
}

/**
 * @brief Select the BCLK Polarity
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the BCLK Polarity Mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetTxBclkPolarity(I2S_Type *const pI2s, I2S_TX_BclkPolarityMode TempMode)
{
    pI2s->TX_CLK_CFG = (pI2s->TX_CLK_CFG & ~I2S_TX_CLK_CFG_BCLK_POL_MASK) | I2S_TX_CLK_CFG_BCLK_POL(TempMode);
}

/**
 * @brief Select the BCLK Direction
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the BCLK Direction
 */
LOCAL_INLINE void I2S_HWA_TX_SetTxBclkDir(I2S_Type *const pI2s, I2S_TX_BclkDir TempMode)
{
    pI2s->TX_CLK_CFG = (pI2s->TX_CLK_CFG & ~I2S_TX_CLK_CFG_BCLK_DIR_MASK) | I2S_TX_CLK_CFG_BCLK_DIR(TempMode);
}

/**
 * @brief Configure the divide ratio to divide down the MCLK to generate BCLK
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the BCLK Divider
 * @note Ratio = (BCLK_DIV + 1) * 2.
 */
LOCAL_INLINE void I2S_HWA_TX_SetTxBclkDiv(I2S_Type *const pI2s, uint32 TempVal)
{
    if (TempVal > 255U)
    {
        TempVal = 255U;
    }
    pI2s->TX_CLK_CFG = (pI2s->TX_CLK_CFG & ~I2S_TX_CLK_CFG_BCLK_DIV_MASK) | I2S_TX_CLK_CFG_BCLK_DIV(TempVal);
}

/**
 * @brief Reset channel N FIFO of the transmitter
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE void I2S_HWA_TX_Fiforeset(I2S_Type *const pI2s, I2S_TX_ChannelType TempVal)
{
    pI2s->TX_CHAN_CFG |= I2S_TX_CHAN_CFG_FIFO_RST(TempVal);
}

/**
 * @brief Enable transmit channel N
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE void I2S_HWA_TX_ChannelEnable(I2S_Type *const pI2s, I2S_TX_ChannelType TempVal)
{
    pI2s->TX_CHAN_CFG |= I2S_TX_CHAN_CFG_CHAN_EN(TempVal);
}

/**
 * @brief Disable transmit channel N
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE void I2S_HWA_TX_ChannelDisable(I2S_Type *const pI2s, I2S_TX_ChannelType TempVal)
{
    pI2s->TX_CHAN_CFG &= ~I2S_TX_CHAN_CFG_CHAN_EN(TempVal);
}

/**
 * @brief GET transmit channel N stat
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE bool I2S_HWA_TX_GetChannelState(I2S_Type *const pI2s, I2S_TX_ChannelType TempVal)
{
    uint32_t TempVall = (pI2s->TX_CHAN_CFG & I2S_TX_CHAN_CFG_CHAN_EN_MASK & I2S_TX_CHAN_CFG_CHAN_EN(TempVal)) >> I2S_TX_CHAN_CFG_CHAN_EN_SHIFT;
    return (bool)((TempVall != 0u) ? true : false);
}

/**
 * @brief Data Start Flag Configuration
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the number of start data
 * @note Configures which data sets the start of data flag.
 * The flag sets at DSF_CFG+1 data in a frame.
 */
LOCAL_INLINE void I2S_HWA_TX_SetStartData(I2S_Type *const pI2s, uint8_t TempVal)
{
    if (TempVal > 15U) { TempVal = 15U; }
    pI2s->TX_CHAN_CFG = (pI2s->TX_CHAN_CFG & ~I2S_TX_CHAN_CFG_DSF_CFG_MASK) | I2S_TX_CHAN_CFG_DSF_CFG((uint32_t)(TempVal));
}

/**
 * @brief Set Restart Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the Restart Mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetRestartMode(I2S_Type *const pI2s, I2S_TX_RestartMode TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_RESTART_MASK) | I2S_TX_FRAME_CFG0_RESTART(TempMode);
}

/**
 * @brief Set Restart Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the Restart Mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetPackMode(I2S_Type *const pI2s, I2S_TX_FifoPackMode TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_FIFO_PACK_MASK) | I2S_TX_FRAME_CFG0_FIFO_PACK(TempMode);
}

/**
 * @brief Set Frame size
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the Frame size
 * @note Configures the number of data in each frame. The number of data in a frame is FRSZ+1
 */
LOCAL_INLINE void I2S_HWA_TX_SetFrameSize(I2S_Type *const pI2s, uint8_t TempVal)
{
    if (TempVal > 15U) { TempVal = 15U; }
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_FRM_SZ_MASK) | I2S_TX_FRAME_CFG0_FRM_SZ((uint32_t)TempVal);
}

/**
 * @brief Set Sync Width
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the Sync Width
 * @note The length is SYNC_WID+1 cycles of BCLK.
 *  The sync width cannot be configured longer than the first data of the frame.
 */
LOCAL_INLINE void I2S_HWA_TX_SetSyncWith(I2S_Type *const pI2s, uint8_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }

    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_SYNC_WID_MASK) | I2S_TX_FRAME_CFG0_SYNC_WID((uint32_t)TempVal);
}

/**
 * @brief Set the Pin Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the Pin Mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetMaskedPinMode(I2S_Type *const pI2s, I2S_MaskedPinMode TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_PIN_CFG_MASK) | I2S_TX_FRAME_CFG0_PIN_CFG(TempMode);
}

/**
 * @brief Set the  MSB First
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  MSB First
 */
LOCAL_INLINE void I2S_HWA_TX_SetPriority(I2S_Type *const pI2s, I2S_TX_Priority TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_MSBF_MASK) | I2S_TX_FRAME_CFG0_MSBF(TempMode);
}

/**
 * @brief Set the Frame Sync Early Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Early Mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetEarlySyncMode(I2S_Type *const pI2s, I2S_TXEarlySyncMode TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~ I2S_TX_FRAME_CFG0_FSE_MASK) | I2S_TX_FRAME_CFG0_FSE(TempMode);
}

/**
 * @brief Set the Frame Sync Early Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Early Mode
 */
LOCAL_INLINE void I2S_HWA_TX_SetSyncMode(I2S_Type *const pI2s, I2S_TXSyncMode TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~ I2S_TX_FRAME_CFG0_FSM_MASK) | I2S_TX_FRAME_CFG0_FSM(TempMode);
}

/**
 * @brief Set the Frame Sync Polarity
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Polarity
 */
LOCAL_INLINE void I2S_HWA_TX_SetSyncPolarity(I2S_Type *const pI2s, I2S_TX_SyncPolarity TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_FSP_MASK) | I2S_TX_FRAME_CFG0_FSP(TempMode);
}

/**
 * @brief Set the Frame Sync Direction
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Direction
 */
LOCAL_INLINE void I2S_HWA_TX_SetFrameSysDir(I2S_Type *const pI2s, I2S_TX_FrameSyncDir TempMode)
{
    pI2s->TX_FRAME_CFG0 = (pI2s->TX_FRAME_CFG0 & ~I2S_TX_FRAME_CFG0_FSD_MASK) | I2S_TX_FRAME_CFG0_FSD(TempMode);
}

/**
 * @brief Set Remaining Data Width
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the Remaining Data Width
 * @note WIDTH = RDW + 1(WIDTH must not be less than 8 bits).
 */
LOCAL_INLINE void I2S_HWA_TX_SetRemainDataWidth(I2S_Type *const pI2s, uint8_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }
    pI2s->TX_FRAME_CFG1 = (pI2s->TX_FRAME_CFG1 & ~I2S_TX_FRAME_CFG1_RDW_MASK) | I2S_TX_FRAME_CFG1_RDW((uint32_t)(TempVal));
}

/**
 * @brief Set First Data Width
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the First Data Width
 * @note WIDTH = FDW + 1(WIDTH must not be less than 8 bits if there is only one data per frame)
 */
LOCAL_INLINE void I2S_HWA_TX_SetFirstDataWidth(I2S_Type *const pI2s, uint8_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }
    pI2s->TX_FRAME_CFG1 = (pI2s->TX_FRAME_CFG1 & ~I2S_TX_FRAME_CFG1_FDW_MASK) | I2S_TX_FRAME_CFG1_FDW((uint32_t)(TempVal));
}

/**
 * @brief Set First Bit Shifted
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the First Bit Shifted
 * @note Configures which bit of each data in a frame is the first bit to be transmitted.
 */
LOCAL_INLINE void I2S_HWA_TX_SetFirstBitShifted(I2S_Type *const pI2s, uint8_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }
    pI2s->TX_FRAME_CFG1 = (pI2s->TX_FRAME_CFG1 & ~I2S_TX_FRAME_CFG1_FBS_MASK) | I2S_TX_FRAME_CFG1_FBS((uint32_t)(TempVal));
}

/**
 * @brief Write FIFO Data
 *
 * @param pI2s the base address of the I2S instance
 * @param Fifo_channel the channeln
 * @param TempVal the  write FIFO Data
 * @note The value written to this register will be stored in the transmitter FIFO.
 *  Please do not write to the register when the FIFO is full.
 */
LOCAL_INLINE void I2S_HWA_TX_WriteOneDataToFifo(I2S_Type *const pI2s, I2S_TX_FifoChannel Fifo_channel, uint32_t TempVal)
{
    pI2s->TX_DATA[(uint32_t)Fifo_channel] = TempVal;
}

/**
 * @brief Get the FIFO Write Address
 *
 * @param pI2s the base address of the I2S instance
 * @param Fifo_channel the channeln
 * @return  FIFO Write Address
 * @note Indicates which address of the transmit FIFO is the next to be written.
 */
LOCAL_INLINE uint32_t I2S_HWA_TX_GetFifoWaddr(I2S_Type *const pI2s, I2S_TX_FifoChannel Fifo_channel)
{
    uint32_t tempval = 0U;
    tempval = (pI2s->TX_FIFO_STATUS[(uint8_t)Fifo_channel] & I2S_TX_FIFO_STATUS_FIFO_WADDR_MASK) >> I2S_TX_FIFO_STATUS_FIFO_WADDR_SHIFT;
    return tempval;
}

/**
 * @brief Get the FIFO read Address
 *
 * @param pI2s the base address of the I2S instance
 * @param Fifo_channel the channeln
 * @return FIFO read Address
 * @note Indicates which address of the transmit FIFO is the next to be read.
 */
LOCAL_INLINE uint32_t I2S_HWA_TX_GetFifoRaddr(I2S_Type *const pI2s, I2S_TX_FifoChannel Fifo_channel)
{
    uint32_t tempval = 0U;
    tempval = (pI2s->TX_FIFO_STATUS[(uint8_t)Fifo_channel] & I2S_TX_FIFO_STATUS_FIFO_RADDR_MASK) >> I2S_TX_FIFO_STATUS_FIFO_RADDR_SHIFT;
    return tempval;
}

/**
 * @brief set Transmit Data Mask
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal Transmit Data Mask
 * @note  The transmit data pins are tri-stated or drive zero when masked.
 */
LOCAL_INLINE void I2S_HWA_TX_SetDataMask(I2S_Type *const pI2s, uint32_t TempVal)
{
    pI2s->TX_DATA_MASK |= (uint32_t)(1 << TempVal);
}

/**
 * @brief Get Transmit Data Mask
 *
 * @param pI2s the base address of the I2S instance
 * @return Transmit Data Mask
 * @note get transmit data pins are tri-stated or drive zero when masked.
 */
LOCAL_INLINE  uint16_t  I2S_HWA_TX_GetDataMask(const I2S_Type *const pI2s)
{
    uint16_t tempval = 0U;
    tempval = (uint16_t)((pI2s->TX_DATA_MASK & I2S_TX_DATA_MASK_TDM_MASK) >> I2S_TX_DATA_MASK_TDM_SHIFT);
    return tempval;
}

/**
 * @brief Enable the receiver
 *
 * @param pI2s the base address of the I2S instance
 * @note  When receiving a frame, this bit can not be cleared
 * by software until the end of the frame.
 */
LOCAL_INLINE void I2S_HWA_RX_Enable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_RXEN_MASK;
}

/**
 * @brief Disable the receiver
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_Disable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_RXEN_MASK;
}

/**
 * @brief Enable the receiver in stop mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_STOP_Enable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_STOPEN_MASK;
}

/**
 * @brief Disable the receiver in stop mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_STOP_Disable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_STOPEN_MASK;
}

/**
 * @brief Enable the receiver in Debug mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DBG_Enable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_DBGEN_MASK;
}

/**
 * @brief Disable the receiver in Debug mode
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DBG_Disable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_DBGEN_MASK;
}

/**
 * @brief Enable BCLK of receiver
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_BCK_Enable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_BCKEN_MASK;
}

/**
 * @brief Disable BCLK of receiver
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_BCLK_Disable(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_BCKEN_MASK;
}

/**
 * @brief Reset all receive FIFOs
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_RSTAllFifo(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_FIFORST_MASK;
}

/**
 * @brief Reset the internal receiver logic including the FIFO read and write pointers
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_SWRST(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_SWRST_MASK;
}

/**
 * @brief Clear the Data Start Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_ClearDataFlag(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_DATA_SF_MASK;
}

/**
 * @brief Get the Data Start Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_RX_GetDataFlag(I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->RX_IDF & I2S_RX_IDF_DATA_SF_MASK) >> I2S_RX_IDF_DATA_SF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Clear the sync error Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_ClearSyncFlag(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_SYNC_EF_MASK  ;
}

/**
 * @brief Get the sync error Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_RX_GetSyncFlag(I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->RX_IDF & I2S_RX_IDF_SYNC_EF_MASK) >> I2S_RX_IDF_SYNC_EF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Clear the overrun Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_ClearOverrunFlag(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_FIFO_OF_MASK;
}

/**
 * @brief Get the overrun Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_RX_GetOverrunFlag(I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->RX_IDF & I2S_RX_IDF_FIFO_OF_MASK) >> I2S_RX_IDF_FIFO_OF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Get the FIFO Full Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_RX_GetFifoFullFlag(const I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->RX_IDF & I2S_RX_IDF_FIFO_FF_MASK) >> I2S_RX_IDF_FIFO_FF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Get the FIFO request Flag
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE bool I2S_HWA_RX_GetFifoRequestFlag(const I2S_Type *const pI2s)
{
    uint32_t TempVal = (pI2s->RX_IDF & I2S_RX_IDF_FIFO_RF_MASK) >> I2S_RX_IDF_FIFO_RF_SHIFT;
    return (bool)((TempVal != 0u) ? true : false);
}

/**
 * @brief Data Start Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_EnableDataInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_DATA_SIE_MASK;
}

/**
 * @brief Data Start Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DisableDataInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_DATA_SIE_MASK;
}

/**
 * @brief Sync Error Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_EnableSyncInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_SYNC_EIE_MASK;
}

/**
 * @brief Sync Error Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DisableSyncInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_SYNC_EIE_MASK;
}

/**
 * @brief FIFO overrun Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_EnableFifoOverrunInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_FIFO_OIE_MASK;
}

/**
 * @brief FIFO overrun Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DisableFifoOverrunInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_FIFO_OIE_MASK;
}

/**
 * @brief FIFO Full Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_EnableFifoFullInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_FIFO_FIE_MASK;
}

/**
 * @brief FIFO Full Interrupt Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DisableFifoFullInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_FIFO_FIE_MASK;
}

/**
 * @brief FIFO request Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_EnableFifoRequestInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_FIFO_RIE_MASK;
}

/**
 * @brief FIFO request Interrupt Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DisableFifoRequestInterrupt(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_FIFO_RIE_MASK;
}

/**
 * @brief FIFO full DMA Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_EnableFifoFullDMA(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_FIFO_FDE_MASK;
}

/**
 * @brief FIFO full DMA Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DisableFifoFullDMA(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_FIFO_FDE_MASK;
}

/**
 * @brief FIFO Request DMA Enable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_EnableFifoRequestDMA(I2S_Type *const pI2s)
{
    pI2s->RX_IDF |= (uint32_t)I2S_RX_IDF_FIFO_RDE_MASK;
}

/**
 * @brief FIFO Request DMA Disable
 *
 * @param pI2s the base address of the I2S instance
 */
LOCAL_INLINE void I2S_HWA_RX_DisableFifoRequestDMA(I2S_Type *const pI2s)
{
    pI2s->RX_IDF &= ~(uint32_t)I2S_RX_IDF_FIFO_RDE_MASK;
}

/**
 * @brief Configures the watermark for all enabled  receive channels
 *
 * @param pI2s the base address of the I2S instance
 * @param Watermark the Watermak
 */
LOCAL_INLINE void I2S_HWA_RX_SetWatermark(I2S_Type *const pI2s, uint32_t Watermark)
{
    if (Watermark > 7U) { Watermark = 7U; }
    pI2s->RX_FIFO_CFG = (pI2s->RX_FIFO_CFG & ~I2S_RX_FIFO_CFG_FWM_MASK) | I2S_RX_FIFO_CFG_FWM(Watermark);
}

/**
 * @brief Select the Synchronous Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the Syncchronous Mode
 * @note The receiver must be configured as asynchronous mode, if the receiver is configured as
 * synchronous mode.
 */
LOCAL_INLINE void I2S_HWA_RX_SetRxSynchronousMode(I2S_Type *const pI2s, I2S_RX_SynchronousMode TempMode)
{
    pI2s->RX_CLK_CFG = (pI2s->RX_CLK_CFG & ~I2S_RX_CLK_CFG_SYNC_MASK) | I2S_RX_CLK_CFG_SYNC(TempMode);
}

/**
 * @brief Bit Clock Loopback from PAD
 *
 * @param pI2s the base address of the I2S instance
 * @note if Set BitLookback ,should set Synchronous Mode too
 */
LOCAL_INLINE void I2S_HWA_RX_SetBitLookback(I2S_Type *const pI2s)
{
    pI2s->RX_CLK_CFG |= I2S_RX_CLK_CFG_BCLK_LB_MASK;
}

/**
 * @brief Select the MCLK source
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the source Mode
 */
LOCAL_INLINE void I2S_HWA_RX_SetRxMclkSelect(I2S_Type *const pI2s, I2S_RX_MclkSelType TempMode)
{
    pI2s->RX_CLK_CFG = (pI2s->RX_CLK_CFG & ~I2S_RX_CLK_CFG_MCLK_SEL_MASK) | I2S_RX_CLK_CFG_MCLK_SEL(TempMode);
}

/**
 * @brief Select the BCLK Polarity
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the BCLK Polarity Mode
 */
LOCAL_INLINE void I2S_HWA_RX_SetRxBclkPolarity(I2S_Type *const pI2s, I2S_RX_BclkPolarityMode TempMode)
{
    pI2s->RX_CLK_CFG = (pI2s->RX_CLK_CFG & ~I2S_RX_CLK_CFG_BCLK_POL_MASK) | I2S_RX_CLK_CFG_BCLK_POL(TempMode);
}

/**
 * @brief Select the BCLK Direction
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the BCLK Direction
 */
LOCAL_INLINE void I2S_HWA_RX_SetRxBclkDir(I2S_Type *const pI2s, I2S_RX_BclkDir TempMode)
{
    pI2s->RX_CLK_CFG = (pI2s->RX_CLK_CFG & ~I2S_RX_CLK_CFG_BCLK_DIR_MASK) | I2S_RX_CLK_CFG_BCLK_DIR(TempMode);
}

/**
 * @brief Configure the divide ratio to divide down the MCLK to generate BCLK
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the BCLK Divider
 * @note Ratio = (BCLK_DIV + 1) * 2.
 */
LOCAL_INLINE void I2S_HWA_RX_SetRxBclkDiv(I2S_Type *const pI2s, uint32 TempVal)
{
    if (TempVal > 255U) { TempVal = 255U; }
    pI2s->RX_CLK_CFG = (pI2s->RX_CLK_CFG & ~I2S_RX_CLK_CFG_BCLK_DIV_MASK) | I2S_RX_CLK_CFG_BCLK_DIV(TempVal);
}

/**
 * @brief Reset channel N FIFO of the receiver
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE void I2S_HWA_RX_Fiforeset(I2S_Type *const pI2s, I2S_RX_ChannelType TempVal)
{
    pI2s->RX_CHAN_CFG |= I2S_RX_CHAN_CFG_FIFO_RST(TempVal);
}

/**
 * @brief Enable receive channel N
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE void I2S_HWA_RX_ChannelEnable(I2S_Type *const pI2s, I2S_RX_ChannelType TempVal)
{
    pI2s->RX_CHAN_CFG |= I2S_RX_CHAN_CFG_CHAN_EN(TempVal);
}

/**
 * @brief Disable receive channel N
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE void I2S_HWA_RX_ChannelDisable(I2S_Type *const pI2s, I2S_RX_ChannelType TempVal)
{
    pI2s->RX_CHAN_CFG &= ~I2S_RX_CHAN_CFG_CHAN_EN(TempVal);
}

/**
 * @brief GET RECEIVER channel N stat
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the I2S channeln
 */
LOCAL_INLINE bool I2S_HWA_RX_GetChannelState(I2S_Type *const pI2s, I2S_RX_ChannelType TempVal)
{
    uint32_t TempVall = (pI2s->RX_CHAN_CFG & I2S_RX_CHAN_CFG_CHAN_EN_MASK & I2S_RX_CHAN_CFG_CHAN_EN(TempVal)) >> I2S_RX_CHAN_CFG_CHAN_EN_SHIFT;
    return (bool)((TempVall != 0u) ? true : false);
}

/**
 * @brief Data Start Flag Configuration
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the number of start data
 * @note Configures which data sets the start of data flag.
 * The flag sets at DSF_CFG+1 data in a frame.
 */
LOCAL_INLINE void I2S_HWA_RX_SetStartData(I2S_Type *const pI2s, uint32_t TempVal)
{
    if (TempVal > 15U) { TempVal = 15U; }
    pI2s->RX_CHAN_CFG = (pI2s->RX_CHAN_CFG & ~I2S_RX_CHAN_CFG_DSF_CFG_MASK) | I2S_RX_CHAN_CFG_DSF_CFG((TempVal));
}

/**
 * @brief Set restart Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the Restart Mode
 */
LOCAL_INLINE void I2S_HWA_RX_SetRestartMode(I2S_Type *const pI2s, I2S_RX_RestartMode TempMode)
{
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~I2S_RX_FRAME_CFG0_RESTART_MASK) | I2S_RX_FRAME_CFG0_RESTART(TempMode);
}

/**
 * @brief Set Restart Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the Restart Mode
 */
LOCAL_INLINE void I2S_HWA_RX_SetPackMode(I2S_Type *const pI2s, I2S_RX_FifoPackMode TempMode)
{
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~I2S_RX_FRAME_CFG0_FIFO_PACK_MASK) | I2S_RX_FRAME_CFG0_FIFO_PACK(TempMode);
}

/**
 * @brief Set Frame size
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the Frame size
 * @note Configures the number of data in each frame. The number of data in a frame is FRSZ+1
 */
LOCAL_INLINE void I2S_HWA_RX_SetFrameSize(I2S_Type *const pI2s, uint32_t TempVal)
{
    if (TempVal > 15U) { TempVal = 15U; }
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~I2S_RX_FRAME_CFG0_FRM_SZ_MASK) | I2S_RX_FRAME_CFG0_FRM_SZ(TempVal);
}

/**
 * @brief Set Sync Width
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the Sync Width
 * @note The length is SYNC_WID+1 cycles of BCLK.
 * The sync width cannot be configured longer than the first data of the frame.
 */
LOCAL_INLINE void I2S_HWA_RX_SetSyncWith(I2S_Type *const pI2s, uint32_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~I2S_RX_FRAME_CFG0_SYNC_WID_MASK) | I2S_RX_FRAME_CFG0_SYNC_WID(TempVal);
}

/**
 * @brief Set the  MSB First
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  MSB First
 */
LOCAL_INLINE void I2S_HWA_RX_SetMaskedPinMode(I2S_Type *const pI2s, I2S_RX_Priority TempMode)
{
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~I2S_RX_FRAME_CFG0_MSBF_MASK) | I2S_RX_FRAME_CFG0_MSBF(TempMode);
}

/**
 * @brief Set the Frame Sync Early Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Early Mode
 */
LOCAL_INLINE void I2S_HWA_RX_SetEarlySyncMode(I2S_Type *const pI2s, I2S_RXEarlySyncMode TempMode)
{
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~ I2S_RX_FRAME_CFG0_FSE_MASK) | I2S_RX_FRAME_CFG0_FSE(TempMode);
}

/**
 * @brief Set the Frame Sync Early Mode
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Early Mode
 */
LOCAL_INLINE void I2S_HWA_RX_SetSyncMode(I2S_Type *const pI2s, I2S_RXSyncMode TempMode)
{
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~ I2S_RX_FRAME_CFG0_FSM_MASK) | I2S_RX_FRAME_CFG0_FSM(TempMode);
}

/**
 * @brief Set the Frame Sync Polarity
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Polarity
 */
LOCAL_INLINE void I2S_HWA_RX_SetSyncPolarity(I2S_Type *const pI2s, I2S_RX_SyncPolarity TempMode)
{
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~I2S_RX_FRAME_CFG0_FSP_MASK) | I2S_RX_FRAME_CFG0_FSP(TempMode);
}

/**
 * @brief Set the Frame Sync Direction
 *
 * @param pI2s the base address of the I2S instance
 * @param TempMode the  Frame Sync Direction
 */
LOCAL_INLINE void I2S_HWA_RX_SetFrameSysDir(I2S_Type *const pI2s, I2S_RX_FrameSyncDir TempMode)
{
    pI2s->RX_FRAME_CFG0 = (pI2s->RX_FRAME_CFG0 & ~I2S_RX_FRAME_CFG0_FSD_MASK) | I2S_RX_FRAME_CFG0_FSD(TempMode);
}

/**
 * @brief Set Remaining Data Width
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the Remaining Data Width
 * @note WIDTH = RDW + 1(WIDTH must not be less than 8 bits).
 */
LOCAL_INLINE void I2S_HWA_RX_SetRemainDataWidth(I2S_Type *const pI2s, uint32_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }
    pI2s->RX_FRAME_CFG1 = (pI2s->RX_FRAME_CFG1 & ~I2S_RX_FRAME_CFG1_RDW_MASK) | I2S_RX_FRAME_CFG1_RDW((TempVal));
}

/**
 * @brief Set First Data Width
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the First Data Width
 * @note WIDTH = FDW + 1(WIDTH must not be less than 8 bits if there is only one data per frame)
 */
LOCAL_INLINE void I2S_HWA_RX_SetFirstDataWidth(I2S_Type *const pI2s, uint32_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }
    pI2s->RX_FRAME_CFG1 = (pI2s->RX_FRAME_CFG1 & ~I2S_RX_FRAME_CFG1_FDW_MASK) | I2S_RX_FRAME_CFG1_FDW(TempVal);
}

/**
 * @brief Set First Bit Shifted
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal the First Bit Shifted
 * @note Configures which bit of each data in a frame is the first bit to be received.
 */
LOCAL_INLINE void I2S_HWA_RX_SetFirstBitShifted(I2S_Type *const pI2s, uint32_t TempVal)
{
    if (TempVal > 31U) { TempVal = 31U; }
    pI2s->RX_FRAME_CFG1 = (pI2s->RX_FRAME_CFG1 & ~I2S_RX_FRAME_CFG1_FBS_MASK) | I2S_RX_FRAME_CFG1_FBS((TempVal));
}

/**
 * @brief Write FIFO Data
 *
 * @param pI2s the base address of the I2S instance
 * @param Fifo_channel the channeln
 * @return The read FIFO Data
 * @note Read the register will get the received data stored in the RX FIFO sequentially
 */
LOCAL_INLINE uint32_t I2S_HWA_RX_ReadOneDataFromFifo(I2S_Type *const pI2s, I2S_RX_FifoChannel Fifo_channel)
{
    uint32_t TempVal = 0U;
    TempVal = pI2s->RX_DATA[(uint32_t)Fifo_channel];
    return  TempVal;
}

/**
 * @brief Get the FIFO read Address
 *
 * @param pI2s the base address of the I2S instance
 * @param Fifo_channel the channeln
 * @return FIFO Write Address
 * @note Indicates which address of the transmit FIFO is the next to be written.
 */
LOCAL_INLINE uint32_t I2S_HWA_RX_GetFifoWaddr(I2S_Type *const pI2s, I2S_RX_FifoChannel Fifo_channel)
{
    uint32_t tempval = 0U;
    tempval = (pI2s->RX_FIFO_STATUS[(uint8_t)Fifo_channel] & I2S_RX_FIFO_STATUS_FIFO_WADDR_MASK) >> I2S_RX_FIFO_STATUS_FIFO_WADDR_SHIFT;
    return tempval;
}

/**
 * @brief Get the FIFO read Address
 *
 * @param pI2s the base address of the I2S instance
 * @param Fifo_channel the channeln
 * @return  FIFO read Address
 * @note Indicates which address of the receive FIFO is the next to be read.
 */
LOCAL_INLINE uint32_t I2S_HWA_RX_GetFifoRaddr(I2S_Type *const pI2s, I2S_RX_FifoChannel Fifo_channel)
{
    uint32_t tempval = 0U;
    tempval = (pI2s->RX_FIFO_STATUS[(uint8_t)Fifo_channel] & I2S_RX_FIFO_STATUS_FIFO_RADDR_MASK) >> I2S_RX_FIFO_STATUS_FIFO_RADDR_SHIFT;
    return tempval;
}

/**
 * @brief Set receive Data Mask
 *
 * @param pI2s the base address of the I2S instance
 * @param TempVal receive Data Mask
 * @note  The receive data pins are tri-stated or drive zero when masked.
 */
LOCAL_INLINE void I2S_HWA_RX_SetDataMask(I2S_Type *const pI2s, uint32_t TempVal)
{
    pI2s->RX_DATA_MASK |= (uint32_t)(1U << TempVal);
}

/**
 * @brief Get receive Data Mask
 *
 * @param pI2s the base address of the I2S instance
 * @return Receiver Data Mask
 * @note  getreceive data pins are tri-stated or drive zero when masked.
 */
LOCAL_INLINE uint16_t I2S_HWA_RX_GetDataMask(const I2S_Type *const pI2s)
{
    uint16_t tempval = 0U;
    tempval = (uint16_t)((pI2s->RX_DATA_MASK & I2S_RX_DATA_MASK_RDM_MASK) >> I2S_RX_DATA_MASK_RDM_SHIFT);
    return tempval;
}

/** @}*/

#endif

#endif /* _HWA_I2S_H_ */
