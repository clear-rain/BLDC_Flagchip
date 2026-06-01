/**
 * @file module_driver_i2s.c
 * @author Flagchip075
 * @brief I2S driver source code
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
*   2.0.0       2024-04-20    Flagchip075   N/A          First version
*********************************************************************************/

#include "module_driver_i2s.h"
#include "module_driver_trgsel.h"
#include "module_driver_pcc.h"

#if I2S_INSTANCE_COUNT > 0U

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef I2S_DEV_ERROR_REPORT
#define I2S_DEV_ERROR_REPORT    STD_OFF
#endif

#if I2S_DEV_ERROR_REPORT == STD_ON
#define I2S_ReportDevError(func, error)     ReportDevError(I2S_MODULE_ID, func, error)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void I2S_TXResetVar(I2S_HandleType *const pHandle);
static void I2S_RXResetVar(I2S_HandleType *const pHandle);

/*TX*/
static void I2S_SendInt(I2S_HandleType *const pHandle, const I2S_BufferType pbuffer, const uint8_t channel);
static void I2S_SendNtoLInt(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount);
static void I2S_FillDataInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish);
static void I2S_FillDataNtoLInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish);
/*RX*/
static void I2S_ReceiveInt(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, const uint8_t channel);
static void I2S_ReceiveLtoNInt(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount);
static void I2S_ReceiveDataInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish);
static void I2S_ReceiveDataLtoNInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish);
/*****************Send/Receive data by  DMA****************************/
static void I2S_TX_DMACompleteCallback(void *arg);
static void I2S_RX_DMACompleteCallback(void *arg);
static void I2S_TX_DMAInit(I2S_HandleType *const pHandle, const I2S_TX_InitType *const pInitCfg);
static void I2S_RX_DMAInit(I2S_HandleType *const pHandle, const I2S_RX_InitType *const pInitCfg);
static void I2S_SendDMA(I2S_HandleType *const pHandle, const I2S_BufferType pbuffer, const uint8_t channel);
static void I2S_SendNtoLDMA(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount);
static void I2S_ReceiveDMA(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, const uint8_t channel);
static void I2S_ReceiveLtoNDMA(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static I2S_Type *const s_apI2sBase[I2S_INSTANCE_COUNT] = I2S_BASE_PTRS ;

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Populates a given I2S transmitter initialization structure with default configuration values.
 *
 * This function initializes the `I2S_TX_InitType` structure with standard settings suitable for basic I2S transmission.
 * These defaults can be modified as needed before initializing the I2S transmitter module.
 *
 * @param pInitCfg A pointer to the I2S transmitter initialization structure to be populated with default values.
 *
 * @note The default configuration includes:
 *   - Watermark level set to 4.
 *   - MCLK source selected from the bus.
 *   - BCLK clock division factor set to 4.
 *   - No masked indices.
 *   - 32-bit data width.
 *   - First bit shift set to 32.
 *   - 2-sample frame size.
 *   - Master mode enabled.
 *   - Sample inputs on rising BCLK edge.
 *   - Other settings for restart mode, masked pin mode, channel enable, etc., are also set to default values.
 *   - Interrupts and DMA channels are disabled by default.
 *   - Callback functions for error notifications are set to NULL.
 */
void I2S_TX_GetDefaultConfig(I2S_TX_InitType *const pInitCfg)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        I2S_ReportDevError(I2S_TX_GETDEFAULT_ID, I2S_E_PARAM_NULLPTR);
    }
    else
#endif
    {
        pInitCfg->u32WaterMark          = 4;
        pInitCfg->eMclkSelType          = I2S_TX_MCLK_SEL_BUS;
        pInitCfg->u32ClkDiv             = 4;
        pInitCfg->MaskedInx             = I2S_MASKED_NONE;
        pInitCfg->u8DataWidth           = 32;
        pInitCfg->u8FirstBitShift       = 32;
        pInitCfg->u8FrameSize           = 2;
        pInitCfg->bMasterMode           = true;
        pInitCfg->eBclkPolarityMode     = I2S_TX_BCLK_ACTIVLOW;    //sample inputs on rising edge
        pInitCfg->eURRestartMode        = I2S_TX_RESTART_MODE0;
        pInitCfg->eMaskedPinMode        = I2S_MASKED_TRISTATED;
        pInitCfg->eChannelEnable        = I2S_TX_CHANNEL_0;
        pInitCfg->eMSBpriority          = I2S_TX_MSB_FIRST;
        pInitCfg->eFrameSyncMode        = I2S_TX_SYNC_MODE0;
        pInitCfg->eEarlySyncMode        = I2S_TX_Onebitear;
        pInitCfg->eSyncPolarity         = I2S_TX_SYNC_POLARITY_LOW;
        pInitCfg->eSynchronousMode      = I2S_TX_ASYNCHRONOUS_MODE;
        pInitCfg->bStopEn               = false;
        pInitCfg->bDataStartIntEn       = false;
        pInitCfg->bSyncIntEn            = false;
        pInitCfg->bFifoUnderrunIntEn    = false;
        pInitCfg->eDatasize             = I2S_DATA_WIDTH_32BITS;
        pInitCfg->eTranferMode          = I2S_TRANFER_INTERRUPT;
        pInitCfg->pDmaHandle[0]         = NULL;
        pInitCfg->pDmaHandle[1]         = NULL;
        pInitCfg->pDmaHandle[2]         = NULL;
        pInitCfg->pDmaHandle[3]         = NULL;
    }
}

/**
 * @brief Initializes the I2S transmitter module with provided configuration.
 *
 * This function initializes the I2S transmitter module based on the `I2S_TX_InitType` structure passed as a parameter.
 * It performs error checking on the input pointers and instance number, sets the channel states, and configures the I2S transmitter registers.
 * It also initializes DMA settings if applicable.
 *
 * @param pHandle A pointer to the I2S handle structure which identifies the I2S instance to initialize.
 * @param pInitCfg A pointer to the initialization configuration structure (`I2S_TX_InitType`) defining the transmitter's setup parameters.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_TX_Init(I2S_HandleType *const pHandle, const I2S_TX_InitType *const pInitCfg)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_TX_INIT_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pInitCfg == NULL)
    {
        I2S_ReportDevError(I2S_TX_INIT_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_TX_INIT_ID, I2S_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        for (uint8_t i = 0U; i < I2S_CHANNLE_NUM; i++)
        {
            if (pInitCfg->eChannelEnable & ((uint8_t)(0x01 << i)))
            {
                pHandle->tStatus.I2Sn_WORKMODEINT[i] = I2S_CHANNEL_WORKMODE_TX; /*set channel state*/
            }
        }
        pHandle->tStatus.tTx.eTranferMode          = pInitCfg->eTranferMode;
        pHandle->tStatus.tTx.u32WaterMark          = pInitCfg->u32WaterMark;
        pHandle->tStatus.tTx.eDatasize             = pInitCfg->eDatasize;

        I2S_HWA_TX_SWRST(pI2s);

        pI2s->TX_IDF = I2S_TX_IDF_FIFORST(1) |
                       I2S_TX_IDF_DATA_SF(1) |
                       I2S_TX_IDF_SYNC_EF(1) |
                       I2S_TX_IDF_FIFO_UF(1);

        pI2s->TX_IDF = I2S_TX_IDF_STOPEN(pInitCfg->bStopEn) |
                       I2S_TX_IDF_DBGEN(true) |
                       I2S_TX_IDF_DATA_SIE(pInitCfg->bDataStartIntEn) |
                       I2S_TX_IDF_SYNC_EIE(pInitCfg->bSyncIntEn) |
                       I2S_TX_IDF_FIFO_UIE(pInitCfg->bFifoUnderrunIntEn) |
                       I2S_TX_IDF_FIFO_EIE(false) |
                       I2S_TX_IDF_FIFO_EDE(false);

        pI2s->TX_FIFO_CFG = I2S_TX_FIFO_CFG_FWM(pInitCfg->u32WaterMark);
        pI2s->TX_CLK_CFG = I2S_TX_CLK_CFG_SYNC(pInitCfg->eSynchronousMode) |
                           I2S_TX_CLK_CFG_BCLK_LB(false) |
                           I2S_TX_CLK_CFG_MCLK_SEL(pInitCfg->eMclkSelType) |
                           I2S_TX_CLK_CFG_BCLK_POL(pInitCfg->eBclkPolarityMode) |
                           I2S_TX_CLK_CFG_BCLK_DIR(pInitCfg->bMasterMode) |
                           I2S_TX_CLK_CFG_BCLK_DIV(pInitCfg->u32ClkDiv);
        pI2s->TX_CHAN_CFG = I2S_TX_CHAN_CFG_CHAN_EN((pInitCfg->eChannelEnable)) |
                            I2S_TX_CHAN_CFG_DSF_CFG((pInitCfg->u8StartDataInx));
        pI2s->TX_FRAME_CFG0 = I2S_TX_FRAME_CFG0_RESTART(pInitCfg->eURRestartMode) |
                              I2S_TX_FRAME_CFG0_FIFO_PACK(0U) |
                              I2S_TX_FRAME_CFG0_FRM_SZ(pInitCfg->u8FrameSize - 1U) |
                              I2S_TX_FRAME_CFG0_SYNC_WID(pInitCfg->u8DataWidth - 1U) |
                              I2S_TX_FRAME_CFG0_PIN_CFG(pInitCfg->eMaskedPinMode) |
                              I2S_TX_FRAME_CFG0_MSBF(pInitCfg->eMSBpriority) |
                              I2S_TX_FRAME_CFG0_FSE(pInitCfg->eEarlySyncMode) |
                              I2S_TX_FRAME_CFG0_FSM(pInitCfg->eFrameSyncMode) |
                              I2S_TX_FRAME_CFG0_FSP(pInitCfg->eSyncPolarity) |
                              I2S_TX_FRAME_CFG0_FSD(pInitCfg->bMasterMode);
        pI2s->TX_FRAME_CFG1 = I2S_TX_FRAME_CFG1_RDW(pInitCfg->u8DataWidth - 1U) |
                              I2S_TX_FRAME_CFG1_FDW(pInitCfg->u8DataWidth - 1U) |
                              I2S_TX_FRAME_CFG1_FBS(pInitCfg->u8FirstBitShift - 1U);
        pI2s->TX_DATA_MASK |= pInitCfg->MaskedInx;

        I2S_TX_DMAInit(pHandle, pInitCfg);
    }
}

/**
 * @brief Deinitializes the I2S transmitter module.
 *
 * This function resets the I2S transmitter module by clearing the handle status, resetting registers, and disabling interrupts and DMA.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance to deinitialize.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_TX_DeInit(I2S_HandleType *const pHandle)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_TX_DEINIT_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_TX_DEINIT_ID, I2S_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];

        I2S_TXResetVar(pHandle);
        pI2s->TX_IDF        = 0U;
        pI2s->TX_IDF       |= I2S_TX_IDF_FIFORST_MASK;
        pI2s->TX_IDF        = I2S_TX_IDF_SWRST_MASK;
        pI2s->TX_DATA_MASK  = 0U;
        pI2s->TX_FRAME_CFG0 = 0U;
        pI2s->TX_CLK_CFG    = 0U;
        I2S_HWA_TX_DisableFifoRequestInterrupt(pI2s);
        I2S_HWA_TX_DisableFifoRequestDMA(pI2s);
    }
}

/**
 * @brief Sends data over the I2S transmitter using the specified transfer mode (interrupt or DMA).
 *
 * This function initiates the transmission of data through the I2S transmitter module. It performs error
 * checks on the handle, buffer, and channel number.
 * Depending on the configured transfer mode (interrupt or DMA), it calls the corresponding send function
 * and enables the necessary interrupts or DMA requests.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A buffer structure containing the data to be transmitted.
 * @param channel The channel number to use for transmission (0-based index).
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_Send(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, uint8_t channel)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_SEND_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_SEND_ID, I2S_E_PARAM_INSTANCE);
    }
    else if (pbuffer.data == NULL)
    {
        I2S_ReportDevError(I2S_SEND_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (channel >= I2S_CHANNLE_NUM)
    {
        I2S_ReportDevError(I2S_SEND_ID, I2S_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];

        if (pHandle->tStatus.tTx.eTranferMode == I2S_TRANFER_INTERRUPT)
        {
            pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].bCombine = false;
            I2S_SendInt(pHandle, pbuffer, channel);
            I2S_HWA_TX_EnableFifoRequestInterrupt(pI2s);
        }
        else if (pHandle->tStatus.tTx.eTranferMode == I2S_TRANFER_DMA)
        {
            pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].bCombine = false;
            I2S_SendDMA(pHandle, pbuffer, channel);
            I2S_HWA_TX_EnableFifoRequestDMA(pI2s);
        }
        else
        {

        }

        I2S_HWA_TX_Enable(pI2s);
    }
}

/**
 * @brief Sends a sequence of buffers over the I2S transmitter using the specified transfer mode (interrupt or DMA).
 *
 * This function initiates the transmission of multiple data buffers through the I2S transmitter module. It performs
 * error checks on the handle, buffer array, channel number, and buffer count.
 * Depending on the configured transfer mode (interrupt or DMA), it calls the corresponding multi-buffer send function
 * and enables the necessary interrupts or DMA requests.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A pointer to an array of buffer structures containing the data to be transmitted.
 * @param channel The channel number to use for transmission (0-based index).
 * @param buffcount The number of buffers in the `pbuffer` array.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_SendNtoL(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_SEND_NTOL_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_SEND_NTOL_ID, I2S_E_PARAM_INSTANCE);
    }
    else if (pbuffer == NULL)
    {
        I2S_ReportDevError(I2S_SEND_NTOL_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (channel >= I2S_CHANNLE_NUM)
    {
        I2S_ReportDevError(I2S_SEND_NTOL_ID, I2S_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        if (pHandle->tStatus.tTx.eTranferMode == I2S_TRANFER_INTERRUPT)
        {
            I2S_SendNtoLInt(pHandle, pbuffer, channel, buffcount);
            I2S_HWA_TX_EnableFifoRequestInterrupt(pI2s);
        }
        else if (pHandle->tStatus.tTx.eTranferMode == I2S_TRANFER_DMA)
        {
            I2S_SendNtoLDMA(pHandle, pbuffer, channel, buffcount);
            I2S_HWA_TX_EnableFifoRequestDMA(pI2s);
        }
        else
        {

        }

        I2S_HWA_TX_Enable(pI2s);
    }
}

/**
 * @brief Stops the ongoing I2S transmission.
 *
 * This function halts an active I2S transmission by disabling the transmitter, BCLK, and performing a software reset.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance to stop.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_SendStop(I2S_HandleType *const pHandle)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_SEND_STOP_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_SEND_STOP_ID, I2S_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        I2S_HWA_TX_Disable(pI2s);
        I2S_HWA_TX_BCLK_Disable(pI2s);
        I2S_HWA_TX_SWRST(pI2s);
    }
}

/**
 * @brief Populates a given I2S receiver initialization structure with default configuration values.
 *
 * This function initializes the `I2S_RX_InitType` structure with standard settings suitable for basic I2S reception.
 * These defaults can be modified as needed before initializing the I2S receiver module.
 *
 * @param pInitCfg A pointer to the I2S receiver initialization structure to be populated with default values.
 *
 * @note The default configuration includes:
 *   - Watermark level set to 4.
 *   - MCLK source selected from the bus.
 *   - BCLK clock division factor set to 4.
 *   - No masked indices.
 *   - 32-bit data width.
 *   - First bit shift set to 32.
 *   - 2-sample frame size.
 *   - Master mode enabled.
 *   - Sample inputs on rising BCLK edge.
 *   - Other settings for restart mode, masked pin mode, channel enable, etc., are also set to default values.
 *   - Interrupts and DMA channels are disabled by default.
 *   - Callback functions for error notifications are set to NULL.
 */
void I2S_RX_GetDefaultConfig(I2S_RX_InitType *const pInitCfg)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        I2S_ReportDevError(I2S_RX_GETDEFAULT_ID, I2S_E_PARAM_NULLPTR);
    }
    else
#endif
    {
        pInitCfg->u32WaterMark          = 4;
        pInitCfg->eMclkSelType          = I2S_RX_MCLK_SEL_BUS;
        pInitCfg->u32ClkDiv             = 4;
        pInitCfg->MaskedInx             = I2S_MASKED_NONE;
        pInitCfg->u8DataWidth           = 32;
        pInitCfg->u8FirstBitShift       = 32;
        pInitCfg->u8FrameSize           = 2;
        pInitCfg->bMasterMode           = true;
        pInitCfg->eBclkPolarityMode     = I2S_RX_BCLK_ACTIVLOW;    //sample inputs on rising edge
        pInitCfg->eORRestartMode        = I2S_RX_RESTART_MODE0;
        pInitCfg->eMaskedPinMode        = I2S_MASKED_ZERO;
        pInitCfg->eChannelEnable        = I2S_RX_CHANNEL_0;
        pInitCfg->eMSBpriority          = I2S_RX_MSB_FIRST;
        pInitCfg->eFrameSyncMode        = I2S_RX_SYNC_MODE0;
        pInitCfg->eEarlySyncMode        = I2S_RX_Onebitear;
        pInitCfg->eSyncPolarity         = I2S_RX_SYNC_POLARITY_LOW;
        pInitCfg->eSynchronousMode      = I2S_RX_ASYNCHRONOUS_MODE;
        pInitCfg->bStopEn               = false;
        pInitCfg->bDataStartIntEn       = false;
        pInitCfg->bSyncIntEn            = false;
        pInitCfg->bFifoOverrunIntEn     = false;
        pInitCfg->eDatasize             = I2S_DATA_WIDTH_32BITS;
        pInitCfg->eTranferMode          = I2S_TRANFER_INTERRUPT;
        pInitCfg->pDmaHandle[0]         = NULL;
        pInitCfg->pDmaHandle[1]         = NULL;
        pInitCfg->pDmaHandle[2]         = NULL;
        pInitCfg->pDmaHandle[3]         = NULL;
    }
}

/**
 * @brief Initializes the I2S receiver module with provided configuration.
 *
 * This function initializes the I2S receiver module based on the `I2S_RX_InitType` structure passed as a parameter.
 * It performs error checking on the input pointers and instance number, sets the channel states, and configures the I2S receiver registers.
 * It also initializes DMA settings if applicable.
 *
 * @param pHandle A pointer to the I2S handle structure which identifies the I2S instance to initialize.
 * @param pInitCfg A pointer to the initialization configuration structure (`I2S_RX_InitType`) defining the receiver's setup parameters.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_RX_Init(I2S_HandleType *const pHandle, const I2S_RX_InitType *const pInitCfg)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_RX_INIT_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pInitCfg == NULL)
    {
        I2S_ReportDevError(I2S_RX_INIT_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_RX_INIT_ID, I2S_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        for (uint8_t i = 0U; i < I2S_CHANNLE_NUM; i++)
        {
            if ((pInitCfg->eChannelEnable) & ((uint8_t)(0x01 << i)))
            {
                pHandle->tStatus.I2Sn_WORKMODEINT[i] = I2S_CHANNEL_WORKMODE_RX; /*set channel state*/
            }
        }

        pHandle->tStatus.tRx.eTranferMode          = pInitCfg->eTranferMode;
        pHandle->tStatus.tRx.u32WaterMark          = pInitCfg->u32WaterMark;
        pHandle->tStatus.tRx.eDatasize             = pInitCfg->eDatasize;

        I2S_HWA_RX_SWRST(pI2s);

        pI2s->RX_IDF = I2S_RX_IDF_FIFORST(1) |
                       I2S_RX_IDF_DATA_SF(1) |
                       I2S_RX_IDF_SYNC_EF(1) |
                       I2S_RX_IDF_FIFO_OF(1);
        pI2s->RX_IDF = I2S_RX_IDF_STOPEN(pInitCfg->bStopEn) |
                       I2S_RX_IDF_DBGEN(true) |
                       I2S_RX_IDF_DATA_SIE(pInitCfg->bDataStartIntEn) |
                       I2S_RX_IDF_SYNC_EIE(pInitCfg->bSyncIntEn) |
                       I2S_RX_IDF_FIFO_OIE(pInitCfg->bFifoOverrunIntEn) |
                       I2S_RX_IDF_FIFO_FIE(false) |
                       I2S_RX_IDF_FIFO_FDE(false);

        pI2s->RX_FIFO_CFG = I2S_RX_FIFO_CFG_FWM(pInitCfg->u32WaterMark);
        pI2s->RX_CLK_CFG = I2S_RX_CLK_CFG_SYNC(pInitCfg->eSynchronousMode) |
                           I2S_RX_CLK_CFG_BCLK_LB(false) |
                           I2S_RX_CLK_CFG_MCLK_SEL(pInitCfg->eMclkSelType) |
                           I2S_RX_CLK_CFG_BCLK_POL(pInitCfg->eBclkPolarityMode) |
                           I2S_RX_CLK_CFG_BCLK_DIR(pInitCfg->bMasterMode) |
                           I2S_RX_CLK_CFG_BCLK_DIV(pInitCfg->u32ClkDiv);
        pI2s->RX_CHAN_CFG = I2S_RX_CHAN_CFG_CHAN_EN(pInitCfg->eChannelEnable) |
                            I2S_RX_CHAN_CFG_DSF_CFG(pInitCfg->u8StartDataInx);

        pI2s->RX_FRAME_CFG0 = I2S_RX_FRAME_CFG0_RESTART(pInitCfg->eORRestartMode) |
                              I2S_RX_FRAME_CFG0_FIFO_PACK(false) |
                              I2S_RX_FRAME_CFG0_FRM_SZ(pInitCfg->u8FrameSize - 1U) |
                              I2S_RX_FRAME_CFG0_SYNC_WID(pInitCfg->u8DataWidth - 1U) |
                              I2S_RX_FRAME_CFG0_MSBF(pInitCfg->eMSBpriority) |
                              I2S_RX_FRAME_CFG0_FSE(pInitCfg->eEarlySyncMode) |
                              I2S_RX_FRAME_CFG0_FSM(pInitCfg->eFrameSyncMode) |
                              I2S_RX_FRAME_CFG0_FSP(pInitCfg->eSyncPolarity) |
                              I2S_RX_FRAME_CFG0_FSD(pInitCfg->bMasterMode);

        pI2s->RX_FRAME_CFG1 = I2S_RX_FRAME_CFG1_RDW(pInitCfg->u8DataWidth - 1U) |
                              I2S_RX_FRAME_CFG1_FDW(pInitCfg->u8DataWidth - 1U) |
                              I2S_RX_FRAME_CFG1_FBS(pInitCfg->u8FirstBitShift - 1U);
        pI2s->RX_DATA_MASK |= pInitCfg->MaskedInx;

        I2S_RX_DMAInit(pHandle, pInitCfg);
    }
}

/**
 * @brief Deinitializes the I2S receiver module.
 *
 * This function resets the I2S receiver module by clearing the handle status, resetting registers, and disabling interrupts and DMA.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance to deinitialize.
 * 
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_RX_DeInit(I2S_HandleType *const pHandle)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_RX_DEINIT_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_RX_DEINIT_ID, I2S_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        I2S_RXResetVar(pHandle);
        pI2s->RX_IDF        = 0U;
        pI2s->RX_IDF       |= I2S_RX_IDF_FIFORST_MASK;
        pI2s->RX_IDF        = I2S_RX_IDF_SWRST_MASK;
        pI2s->RX_DATA_MASK  = 0U;
        pI2s->RX_FRAME_CFG0 = 0U;
        pI2s->RX_CLK_CFG    = 0U;
        I2S_HWA_RX_DisableFifoRequestInterrupt(pI2s);
        I2S_HWA_RX_DisableFifoRequestDMA(pI2s);
    }
}

/**
 * @brief Receives data from the I2S receiver using the specified transfer mode (interrupt or DMA).
 *
 * This function initiates the reception of data through the I2S receiver module. It performs error checks on the handle, buffer, and channel number.
 * Depending on the configured transfer mode (interrupt or DMA), it calls the corresponding receive function and enables the necessary interrupts or DMA requests.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A buffer structure to store the received data.
 * @param channel The channel number to use for reception (0-based index).
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_Receive(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, uint8_t channel)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_RECEIVE_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_RECEIVE_ID, I2S_E_PARAM_INSTANCE);
    }
    else if (pbuffer.data == NULL)
    {
        I2S_ReportDevError(I2S_RECEIVE_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (channel >= I2S_CHANNLE_NUM)
    {
        I2S_ReportDevError(I2S_RECEIVE_ID, I2S_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        if (pHandle->tStatus.tRx.eTranferMode == I2S_TRANFER_INTERRUPT)
        {
            pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].bCombine = false;
            I2S_ReceiveInt(pHandle, pbuffer, channel);
            I2S_HWA_RX_EnableFifoRequestInterrupt(pI2s);
        }
        else if (pHandle->tStatus.tRx.eTranferMode == I2S_TRANFER_DMA)
        {
            pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].bCombine = false;
            I2S_ReceiveDMA(pHandle, pbuffer, channel);
            I2S_HWA_RX_EnableFifoRequestDMA(pI2s);
        }
        else
        {

        }
        I2S_HWA_RX_Enable(pI2s);
    }
}

/**
 * @brief Receives a sequence of buffers from the I2S receiver using the specified transfer mode (interrupt or DMA).
 *
 * This function initiates the reception of multiple data buffers through the I2S receiver module. It performs error
 * checks on the handle, buffer array, channel number, and buffer count.
 * Depending on the configured transfer mode (interrupt or DMA), it calls the corresponding multi-buffer receive
 * function and enables the necessary interrupts or DMA requests.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A pointer to an array of buffer structures to store the received data.
 * @param channel The channel number to use for reception (0-based index).
 * @param buffcount The number of buffers in the `pbuffer` array.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_ReceiveLtoN(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_RECEIVE_LTON_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_RECEIVE_LTON_ID, I2S_E_PARAM_INSTANCE);
    }
    else if (pbuffer == NULL)
    {
        I2S_ReportDevError(I2S_RECEIVE_LTON_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (channel >= I2S_CHANNLE_NUM)
    {
        I2S_ReportDevError(I2S_RECEIVE_LTON_ID, I2S_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        if (pHandle->tStatus.tRx.eTranferMode == I2S_TRANFER_INTERRUPT)
        {
            I2S_ReceiveLtoNInt(pHandle, pbuffer, channel, buffcount);
            I2S_HWA_RX_EnableFifoRequestInterrupt(pI2s);
        }
        else if (pHandle->tStatus.tRx.eTranferMode == I2S_TRANFER_DMA)
        {
            I2S_ReceiveLtoNDMA(pHandle, pbuffer, channel, buffcount);
            I2S_HWA_RX_EnableFifoRequestDMA(pI2s);
        }
        else
        {

        }
        I2S_HWA_RX_Enable(pI2s);
    }
}

/**
 * @brief Stops the ongoing I2S receive operation.
 *
 * This function halts the current I2S receiver operation by disabling the I2S hardware block, BCLK, and performing a software reset.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_ReceiveStop(I2S_HandleType *const pHandle)
{
#if I2S_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        I2S_ReportDevError(I2S_RECEIVE_STOP_ID, I2S_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= I2S_INSTANCE_COUNT)
    {
        I2S_ReportDevError(I2S_RECEIVE_STOP_ID, I2S_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
        I2S_HWA_RX_Disable(pI2s);
        I2S_HWA_RX_BCLK_Disable(pI2s);
        I2S_HWA_RX_SWRST(pI2s);
    }
}

/**
 * @brief Resets the internal variables related to the I2S transmit module.
 *
 * This function resets the I2S transmit status structure to its initial state, preparing it for a new transmission.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 */
static void I2S_TXResetVar(I2S_HandleType *const pHandle)
{
    pHandle->tStatus.tTx.eTranferMode = I2S_TRANFER_INTERRUPT;
    for (uint8_t i = 0U ; i < I2S_CHANNLE_NUM; i++)
    {
        pHandle->tStatus.tTx.finish[i]              = false;
        pHandle->tStatus.tTx.sGlobalBuffer[i].data  = NULL;
        pHandle->tStatus.tTx.eDatasize              = I2S_DATA_WIDTH_INVALID;
        pHandle->tStatus.tTx.sGlobalBuffer[i].count = 0U;
    }
}

/**
 * @brief Sends data to the I2S transmitter using interrupt mode.
 *
 * This function writes data to the I2S transmitter FIFO based on the specified data width and buffer information.
 * It supports 8-bit, 16-bit, and 32-bit data widths and handles scenarios where the buffer count is less than or equal to the FIFO depth,
 * as well as cases where it exceeds the FIFO depth, requiring multiple write operations.

 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A buffer structure containing the data to send.
 * @param channel The channel number to use for transmission (0-based index).

 * @note This is a static function intended for internal use within the I2S driver.
 */
static void  I2S_SendInt(I2S_HandleType *const pHandle, const I2S_BufferType pbuffer, const uint8_t channel)
{
    I2S_Type  *const pI2s = s_apI2sBase[pHandle->eInstance];
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tTx.eDatasize;
    uint8_t *pdata = pbuffer.data;

    pHandle->tStatus.tTx.sGlobalBuffer[channel].count = pbuffer.count;
    pHandle->tStatus.tTx.sGlobalBuffer[channel].data  = pbuffer.data;
    pHandle->tStatus.tTx.finish[channel]              = false;

    if (pbuffer.count <= I2S_FIFO_DEPTH)
    {
        for (uint8_t i = 0U; i < pbuffer.count; i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tTx.finish[channel] = true;
    }
    else
    {
        for (uint8_t i = 0U; i < I2S_FIFO_DEPTH; i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tTx.sGlobalBuffer[channel].count -= I2S_FIFO_DEPTH ;
        pHandle->tStatus.tTx.sGlobalBuffer[channel].data = pdata;
    }
}

/**
 * @brief Fills the I2S transmitter FIFO with data in interrupt mode.
 *
 * This function writes data to the I2S transmitter FIFO based on the specified data width, buffer information, and watermark level.
 * It supports 8-bit, 16-bit, and 32-bit data widths and updates the buffer and finish status accordingly.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param channel The channel number to use for transmission (0-based index).
 * @param[out] finish A pointer to a boolean flag indicating whether the data transfer for the given channel is complete.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_FillDataInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    uint8_t *pdata = pHandle->tStatus.tTx.sGlobalBuffer[channel].data;
    I2S_BufferType pbuffer = pHandle->tStatus.tTx.sGlobalBuffer[channel];
    uint32_t tempwatermark = pHandle->tStatus.tTx.u32WaterMark;
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tTx.eDatasize;

    pHandle->tStatus.tTx.finish[channel] = false;
    *finish = false;

    if (pbuffer.count < (I2S_FIFO_DEPTH - tempwatermark))
    {
        for (uint8_t i = 0U; i < pbuffer.count; i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tTx.finish[channel] = true;
    }
    else
    {
        for (uint8_t i = 0U; i < (I2S_FIFO_DEPTH - tempwatermark); i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tTx.sGlobalBuffer[channel].count -= (I2S_FIFO_DEPTH - tempwatermark);
        pHandle->tStatus.tTx.sGlobalBuffer[channel].data = pdata;
    }
    *finish = pHandle->tStatus.tTx.finish[channel];
}

/**
 * @brief Fills the I2S transmitter FIFO with data from a list of buffers in interrupt mode.
 *
 * This function writes data from a list of buffers to the I2S transmitter FIFO based on the specified data width, watermark level, and buffer count.
 * It supports 8-bit, 16-bit, and 32-bit data widths and updates the buffer and finish status accordingly.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param channel The channel number to use for transmission (0-based index).
 * @param[out] finish A pointer to a boolean flag indicating whether the data transfer for the given channel is complete.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_FillDataNtoLInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tTx.eDatasize;
    uint32_t tempwatermark = pHandle->tStatus.tTx.u32WaterMark;
    uint32_t totalcount = pHandle->tStatus.tTx.sGlobalBuffer[channel].count;
    uint8_t buffercount = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferTotal;

    pHandle->tStatus.tTx.finish[channel] = false;

    if (totalcount < (I2S_FIFO_DEPTH - tempwatermark))
    {
        uint8_t nextbuff = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent;
        for (uint32_t i = 0U; i < totalcount; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[nextbuff].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            nextbuff++;
            if (nextbuff == buffercount)
            {
                nextbuff = 0U;
            }
        }
        pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent = nextbuff;
        pHandle->tStatus.tTx.finish[channel] = true;
    }
    else
    {
        uint8_t nextbuff = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent;
        for (uint8_t i = 0U; i < I2S_FIFO_DEPTH - tempwatermark; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[nextbuff].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {

                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, *((uint32_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[nextbuff].data = pdata;
            nextbuff++;
            if (nextbuff == buffercount)
            {
                nextbuff = 0U;
            }
        }
        pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent = nextbuff;
        pHandle->tStatus.tTx.sGlobalBuffer[channel].count -= (I2S_FIFO_DEPTH - tempwatermark);
    }

    *finish =  pHandle->tStatus.tTx.finish[channel];
}

/**
 * @brief Sends a list of buffers to the I2S transmitter using interrupt mode.
 *
 * This function combines multiple buffers into a single buffer and writes the data to the I2S transmitter FIFO based on the specified data width.
 * It supports 8-bit, 16-bit, and 32-bit data widths and handles scenarios where the combined buffer size is less than or equal to the FIFO depth.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A pointer to an array of buffer structures containing the data to send.
 * @param channel The channel number to use for transmission (0-based index).
 * @param buffcount The number of buffers in the `pbuffer` array.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_SendNtoLInt(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tTx.eDatasize;
    uint32_t totalcount = buffcount * (pbuffer[0].count);
    uint8_t buffercount = buffcount;

    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].bCombine        = true;
    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent = 0U;
    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList        = pbuffer;
    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferTotal   = buffcount;
    pHandle->tStatus.tTx.sGlobalBuffer[channel].count               = buffcount * (pbuffer[0].count);
    pHandle->tStatus.tTx.finish[channel]                            = false;

    if (totalcount <= I2S_FIFO_DEPTH)
    {
        uint8_t nextbuff = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent;
        for (uint8_t i = 0U; i < totalcount; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[nextbuff].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            nextbuff++;
            if (nextbuff == buffercount)
            {
                nextbuff = 0U;
            }
        }
        pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent = nextbuff;
        pHandle->tStatus.tTx.finish[channel] = true;
    }
    else
    {
        uint8_t nextbuff = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent;
        for (uint8_t i = 0U; i < I2S_FIFO_DEPTH; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[nextbuff].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {

                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, *((uint32_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[nextbuff].data = pdata;
            nextbuff++;
            if (nextbuff == buffercount)
            {
                nextbuff = 0U;
            }
        }
        pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent = nextbuff;
        pHandle->tStatus.tTx.sGlobalBuffer[channel].count -= I2S_FIFO_DEPTH;
    }
}

/**
 * @brief Sends data via DMA to the I2S transmitter.
 *
 * This function sends a buffer of data to the I2S transmitter using DMA. It initializes the DMA transfer
 * based on the specified data width and channel configuration.
 * Supports 8-bit, 16-bit, and 32-bit data widths.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A buffer structure containing the data to be sent.
 * @param channel The channel number to use for transmission (0-based index).
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void  I2S_SendDMA(I2S_HandleType *const pHandle, const I2S_BufferType pbuffer, const uint8_t channel)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tTx.eDatasize;
    uint8_t *pdata = pbuffer.data;

    pHandle->tStatus.tTx.sGlobalBuffer[channel].count = pbuffer.count;
    pHandle->tStatus.tTx.sGlobalBuffer[channel].data  = pbuffer.data;
    pHandle->tStatus.tTx.finish[channel]              = false;

    if (pbuffer.count <= I2S_FIFO_DEPTH)
    {
        for (uint8_t i = 0U; i < pbuffer.count; i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tTx.finish[channel] = true;
    }
    else
    {
        for (uint8_t i = 0U; i < I2S_FIFO_DEPTH; i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tTx.sGlobalBuffer[channel].count -= I2S_FIFO_DEPTH ;
        pHandle->tStatus.tTx.sGlobalBuffer[channel].data = pdata;
    }

    if (pHandle->tStatus.tTx.finish[channel] != true)
    {
        DMA_RequestSourceType temptype ;
        if (pHandle->eInstance == I2S_INSTANCE_0)
        {
            temptype = DMA_REQ_I2S0_TX;
        }
        else if (pHandle->eInstance == I2S_INSTANCE_1)
        {
            temptype = DMA_REQ_I2S1_TX;
        }
        else
        {
            temptype = DMA_REQ_I2S0_TX;
        }

        DMA_TransferSizeType tempSize;
        if (tempDatasize == I2S_DATA_WIDTH_8BITS)
        {
            tempSize = DMA_TRANSFER_SIZE_1B;
        }
        else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
        {
            tempSize = DMA_TRANSFER_SIZE_2B;
        }
        else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
        {
            tempSize = DMA_TRANSFER_SIZE_4B;
        }
        else
        {
            tempSize = DMA_TRANSFER_SIZE_1B;
        }

        DMA_ChannelCfgType s_tDmaChannel0Cfg =
        {
            .pSrcBuffer              = pHandle->tStatus.tTx.sGlobalBuffer[channel].data,
            .pDestBuffer             = (&(pI2s->TX_DATA[channel])),
            .u32BlockSize            = (uint32_t)pHandle->tStatus.tTx.eDatasize,
            .u16BlockCount           = (uint16_t)pHandle->tStatus.tTx.sGlobalBuffer[channel].count,
            .u8ChannelPriority       = pHandle->tStatus.tTx.pDmaHandle[channel]->tSettings.u8Channel,

            .eSrcDataSize            = tempSize,
            .eDestDataSize           = tempSize,
            .eSrcIncMode             = DMA_INCREMENT_DATA_SIZE,
            .eDestIncMode            = DMA_INCREMENT_DISABLE,
            .bSrcBlockOffsetEn       = false,
            .bDestBlockOffsetEn      = false,
            .s32BlockOffset          = 0,
            .bSrcAddrLoopbackEn      = false,
            .bDestAddrLoopbackEn     = false,
            .bAutoStop               = true,
            .bSrcCircularBufferEn    = false,
            .u32SrcCircBufferSize    = 0U,
            .bDestCircularBufferEn   = false,
            .u32DestCircBufferSize   = 0U,
            .eTriggerSrc             = temptype,

            .bTransferCompleteIntEn  = true,
            .pTransferCompleteNotify = I2S_TX_DMACompleteCallback,
            .completedata            = (void *)pHandle,
        };
        s_tDmaChannel0Cfg.bTransferErrorIntEn     = false;
        s_tDmaChannel0Cfg.pTransferErrorNotify    = NULL;
        s_tDmaChannel0Cfg.errdata                 = NULL;
        DMA_InitChannel(pHandle->tStatus.tTx.pDmaHandle[channel], &s_tDmaChannel0Cfg);
        DMA_StartChannel(pHandle->tStatus.tTx.pDmaHandle[channel]);
    }
}

/**
 * @brief Sends a list of buffers to the I2S transmitter using DMA in non-blocking mode.
 *
 * This function combines multiple buffers and initiates a DMA transfer to the I2S transmitter. It sets up the DMA
 * channels for each buffer and configures the transfer parameters based on the data width.
 * Supports 8-bit, 16-bit, and 32-bit data widths.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer An array of buffer structures containing the data to send.
 * @param channel The channel number to use for transmission (0-based index).
 * @param buffcount The number of buffers in the `pbuffer` array.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void  I2S_SendNtoLDMA(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    DMA_Type *const pDma = DMA;
    uint16_t u16Temp;
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tTx.eDatasize;
    uint32_t totalcount = buffcount * (pbuffer[0].count);
    uint8_t buffercount = buffcount;

    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].bCombine        = true;
    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent = 0U;
    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList        = pbuffer;
    pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferTotal   = buffcount;
    pHandle->tStatus.tTx.sGlobalBuffer[channel].count               = buffcount * (pbuffer[0].count);
    pHandle->tStatus.tTx.finish[channel]                            = false;

    if (totalcount <= I2S_FIFO_DEPTH)
    {
        uint8_t nextbuff = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent;
        for (uint8_t i = 0U; i < totalcount; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[nextbuff].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (*((uint32_t *)pdata)));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            nextbuff++;
            if (nextbuff == buffercount)
            {
                nextbuff = 0U;
            }
        }
        pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].u8BufferCurrent = nextbuff;
        pHandle->tStatus.tTx.finish[channel] = true;
    }
    else
    {
        for (uint32_t i = 0U; i < buffercount; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[i].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t)(*pdata));
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, (uint32_t) * ((uint16_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                I2S_HWA_TX_WriteOneDataToFifo(pI2s, (I2S_TX_FifoChannel)channel, *((uint32_t *)pdata));
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[i].data = pdata;
        }
        pHandle->tStatus.tTx.sGlobalBuffer[channel].count -= buffercount;
    }

    if (pHandle->tStatus.tTx.finish[channel] != true)
    {
        DMA_RequestSourceType temptype ;
        if (pHandle->eInstance == I2S_INSTANCE_0)
        {
            temptype = DMA_REQ_I2S0_TX;
        }
        else if (pHandle->eInstance == I2S_INSTANCE_1)
        {
            temptype = DMA_REQ_I2S1_TX;
        }
        else
        {
            temptype = DMA_REQ_I2S1_TX;
        }

        DMA_TransferSizeType tempSize = DMA_TRANSFER_SIZE_1B;
        if (tempDatasize == I2S_DATA_WIDTH_8BITS)
        {
            tempSize = DMA_TRANSFER_SIZE_1B;
        }
        else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
        {
            tempSize = DMA_TRANSFER_SIZE_2B;
        }
        else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
        {
            tempSize = DMA_TRANSFER_SIZE_4B;
        }
        else
        {
            tempSize = DMA_TRANSFER_SIZE_1B;
        }

        DMA_ChannelCfgType s_tDmaChannel0Cfg = {0};

        s_tDmaChannel0Cfg .pDestBuffer            = (&(pI2s->TX_DATA[channel]));
        s_tDmaChannel0Cfg.u8ChannelPriority       = 0u;
        s_tDmaChannel0Cfg.eSrcDataSize            = tempSize;
        s_tDmaChannel0Cfg.eDestDataSize           = tempSize;
        s_tDmaChannel0Cfg.eSrcIncMode             = DMA_INCREMENT_DATA_SIZE;
        s_tDmaChannel0Cfg .eDestIncMode           = DMA_INCREMENT_DISABLE;
        s_tDmaChannel0Cfg.bSrcBlockOffsetEn       = false;
        s_tDmaChannel0Cfg.bDestBlockOffsetEn      = false;
        s_tDmaChannel0Cfg.s32BlockOffset          = 0;
        s_tDmaChannel0Cfg .bSrcAddrLoopbackEn     = false;
        s_tDmaChannel0Cfg .bDestAddrLoopbackEn    = false;
        s_tDmaChannel0Cfg .bAutoStop              = true;
        s_tDmaChannel0Cfg .bSrcCircularBufferEn   = false;
        s_tDmaChannel0Cfg .u32SrcCircBufferSize   = 0U;
        s_tDmaChannel0Cfg .bDestCircularBufferEn  = false;
        s_tDmaChannel0Cfg .u32DestCircBufferSize  = 0U;
        s_tDmaChannel0Cfg.u32BlockSize            = (uint32_t)pHandle->tStatus.tTx.eDatasize;
        s_tDmaChannel0Cfg.bTransferCompleteIntEn  = true;
        s_tDmaChannel0Cfg.pTransferCompleteNotify = I2S_TX_DMACompleteCallback;
        s_tDmaChannel0Cfg.completedata            = (void *)pHandle;

        for (uint8_t i = 0U; i < buffcount; i++)
        {
            s_tDmaChannel0Cfg.bTransferErrorIntEn     = false;
            s_tDmaChannel0Cfg.pTransferErrorNotify    = NULL;
            s_tDmaChannel0Cfg.errdata                 = NULL;
            s_tDmaChannel0Cfg.pSrcBuffer         = pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[i].data;
            s_tDmaChannel0Cfg.u16BlockCount      = (uint16_t)(pHandle->tStatus.tTx.sGlobalBufferNtoL[channel].pBufList[i].count - 1U);
            if (i == 0U)
            {
                s_tDmaChannel0Cfg .eTriggerSrc   = temptype;
            }
            else
            {
                s_tDmaChannel0Cfg .eTriggerSrc   = DMA_REQ_DISABLED;
            }

            DMA_InitChannel(pHandle->tStatus.tTx.pDmaHandle[i], &s_tDmaChannel0Cfg);
            DMA_HWA_SetChannelToChannelTrig(pDma, pHandle->tStatus.tTx.pDmaHandle[i]->tSettings.u8Channel, false, 0U);
            if (i < buffcount - 1U)
            {
                u16Temp = pDma->CFG[pHandle->tStatus.tTx.pDmaHandle[i]->tSettings.u8Channel].CSR;
                u16Temp = (uint16_t)(u16Temp | DMA_CFG_CSR_OCHTRGEN(1) | DMA_CFG_CSR_OTRGCH(pHandle->tStatus.tTx.pDmaHandle[i + 1U]->tSettings.u8Channel));
                pDma->CFG[pHandle->tStatus.tTx.pDmaHandle[i]->tSettings.u8Channel].CSR = u16Temp;

                u16Temp = pDma->CFG[pHandle->tStatus.tTx.pDmaHandle[i]->tSettings.u8Channel].BLC.CHTRGENYES;
                u16Temp &= (uint16_t)(~DMA_CFG_BLC_CHTRGENYES_TRGCH_MASK);
                u16Temp =(uint16_t)(u16Temp | DMA_CFG_BLC_CHTRGENYES_CHTRGEN(1U) | DMA_CFG_BLC_CHTRGENYES_TRGCH(pHandle->tStatus.tTx.pDmaHandle[i + 1U]->tSettings.u8Channel));
                pDma->CFG[pHandle->tStatus.tTx.pDmaHandle[i]->tSettings.u8Channel].BLC.CHTRGENYES = u16Temp;

                u16Temp = pDma->CFG[pHandle->tStatus.tTx.pDmaHandle[i]->tSettings.u8Channel].CLC.CHTRGENYES;
                u16Temp &= (uint16_t)(~DMA_CFG_CLC_CHTRGENYES_TRGCH_MASK);
                u16Temp = (uint16_t)(u16Temp | DMA_CFG_CLC_CHTRGENYES_CHTRGEN(1U) | DMA_CFG_CLC_CHTRGENYES_TRGCH(pHandle->tStatus.tTx.pDmaHandle[i + 1U]->tSettings.u8Channel));
                pDma->CFG[pHandle->tStatus.tTx.pDmaHandle[i]->tSettings.u8Channel].CLC.CHTRGENYES = u16Temp;
            }
        }

        DMA_StartChannel(pHandle->tStatus.tTx.pDmaHandle[0]);
    }
}

/**
 * @brief DMA Transfer Complete Callback for I2S Transmission.
 *
 * This function is called when an I2S transmission DMA transfer completes.
 * It notifies the application layer about the completion of the transfer, if a notification callback is set.
 *
 * @param arg Pointer to the I2S handle, containing context and status information.
 */
static void I2S_TX_DMACompleteCallback(void *arg)
{
    I2S_HandleType *pHandle = (I2S_HandleType *)arg;

    if (pHandle->tSettings.tTx.pTransferFinishNotify != NULL)
    {
        pHandle->tSettings.tTx.pTransferFinishNotify(pHandle);
    }
}

/**
 * @brief Initializes the DMA for I2S transmit operations.
 *
 * This function sets up the DMA channels for I2S transmit operations according to the provided initialization configuration.
 * It enables the transfer complete interrupt and assigns a callback function for notification when the DMA transfer is finished.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pInitCfg A pointer to the I2S TX initialization configuration structure containing DMA channel settings and transfer mode.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_TX_DMAInit(I2S_HandleType *const pHandle, const I2S_TX_InitType *const pInitCfg)
{
    if (pInitCfg->eTranferMode == I2S_TRANFER_DMA)
    {
        for (uint8_t i = 0U; i < I2S_CHANNLE_NUM; i++)
        {
            pHandle->tStatus.tTx.pDmaHandle[i]   = pInitCfg->pDmaHandle[i];
        }
    }
}

/**
 * @brief Resets the I2S receive variables to their default values.
 *
 * This function resets the I2S receive-related variables to their initial state, preparing for a new receive operation.
 * It sets the transfer mode to interrupt, clears the finish flags, buffer pointers, data size, and error notification pointers.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_RXResetVar(I2S_HandleType *const pHandle)
{
    pHandle->tStatus.tRx.eTranferMode = I2S_TRANFER_INTERRUPT;
    for (uint8_t i = 0U; i < I2S_CHANNLE_NUM; i++)
    {
        pHandle->tStatus.tRx.finish[i]              = false;
        pHandle->tStatus.tRx.sGlobalBuffer[i].data  = NULL;
        pHandle->tStatus.tRx.eDatasize              = I2S_DATA_WIDTH_INVALID;
        pHandle->tStatus.tRx.sGlobalBuffer[i].count = 0U;
    }
}

/**
 * @brief Sets up the I2S receive buffer for interrupt-driven reception.
 *
 * This function prepares the I2S receive buffer for an interrupt-driven receive operation. It stores the buffer's count
 * and data pointer and initializes the finish flag to false, indicating that the receive operation has not yet completed.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A buffer structure containing the data buffer to receive.
 * @param channel The channel number to use for reception (0-based index).

 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_ReceiveInt(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, const uint8_t channel)
{
    pHandle->tStatus.tRx.sGlobalBuffer[channel].count = pbuffer.count;
    pHandle->tStatus.tRx.sGlobalBuffer[channel].data  = pbuffer.data;
    pHandle->tStatus.tRx.finish[channel]              = false;
}

/**
 * @brief Receives data from the I2S interface using interrupts.
 *
 * This function reads data from the I2S receiver into a pre-configured buffer based on the specified data width.
 * It supports 8-bit, 16-bit, and 32-bit data widths and can process either up to a watermark count or the entire buffer count,
 * updating the buffer status accordingly.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param channel The channel number from which to receive data (0-based index).
 * @param finish A pointer to a boolean indicating whether the receive operation has finished after this interrupt handling.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_ReceiveDataInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    uint8_t *pdata = pHandle->tStatus.tRx.sGlobalBuffer[channel].data;
    I2S_BufferType pbuffer = pHandle->tStatus.tRx.sGlobalBuffer[channel];
    uint32_t tempwatermark = pHandle->tStatus.tRx.u32WaterMark;
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tRx.eDatasize;

    pHandle->tStatus.tRx.finish[channel] = false;
    *finish = false;

    if (pbuffer.count <= tempwatermark)
    {
        for (uint32_t i = 0U; i < pbuffer.count; i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                *pdata = (uint8_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                *(uint16_t *)pdata = (uint16_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                *(uint32_t *)pdata = I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tRx.finish[channel] = true;
    }
    else
    {
        for (uint32_t i = 0U; i < tempwatermark; i++)
        {
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                *pdata = (uint8_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                *(uint16_t *)pdata = (uint16_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                *(uint32_t *)pdata = I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }
        }
        pHandle->tStatus.tRx.sGlobalBuffer[channel].count -= (tempwatermark) ;
        pHandle->tStatus.tRx.sGlobalBuffer[channel].data = pdata;
    }

    *finish = pHandle->tStatus.tRx.finish[channel];
}

/**
 * @brief Processes the I2S receive data using a linked list of buffers with interrupts.
 *
 * This function reads data from the I2S receiver into a linked list of buffers based on the specified data width.
 * It supports 8-bit, 16-bit, and 32-bit data widths and can process either up to a watermark count or the entire buffer count,
 * updating the buffer status accordingly. The function iterates through the linked list as needed.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param channel The channel number from which to receive data (0-based index).
 * @param finish A pointer to a boolean indicating whether the receive operation has finished after this interrupt handling.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_ReceiveDataLtoNInt(I2S_HandleType *const pHandle, const uint8_t channel, bool *finish)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    uint8_t buffercount = pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].u8BufferTotal;
    uint32_t tempwatermark = pHandle->tStatus.tRx.u32WaterMark;
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tRx.eDatasize;
    uint32_t totalcount = pHandle->tStatus.tRx.sGlobalBuffer[channel].count;

    pHandle->tStatus.tRx.finish[channel] = false;

    if (totalcount <= tempwatermark)
    {
        uint8_t nextbuff = pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].u8BufferCurrent;
        for (uint32_t i = 0U; i < totalcount; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList[nextbuff].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                *pdata = (uint8_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                *(uint16_t *)pdata = (uint16_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                *(uint32_t *)pdata = I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList[nextbuff].data = pdata;
            nextbuff++;
            if (nextbuff == buffercount)
            {
                nextbuff = 0U;
            }
            pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].u8BufferCurrent = nextbuff;
        }
        pHandle->tStatus.tRx.finish[channel] = true;
    }
    else
    {
        uint8_t nextbuff = pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].u8BufferCurrent;
        for (uint32_t i = 0U; i < tempwatermark; i++)
        {
            uint8_t *pdata = pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList[nextbuff].data;
            if (tempDatasize == I2S_DATA_WIDTH_8BITS)
            {
                *pdata = (uint8_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_8BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
            {
                *(uint16_t *)pdata = (uint16_t) I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_16BITS;
            }
            else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
            {
                *(uint32_t *)pdata = I2S_HWA_RX_ReadOneDataFromFifo(pI2s, (I2S_RX_FifoChannel)channel);
                pdata = pdata + I2S_DATA_WIDTH_32BITS;
            }
            else
            {

            }

            pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList[nextbuff].data = pdata;
            nextbuff++;
            if (nextbuff == buffercount)
            {
                nextbuff = 0U;
            }
            pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].u8BufferCurrent = nextbuff;
        }
        pHandle->tStatus.tRx.sGlobalBuffer[channel].count -= (tempwatermark) ;
    }

    *finish = pHandle->tStatus.tRx.finish[channel];

}

/**
 * @brief Configures and starts the DMA for I2S receive operations.
 *
 * This function initializes a DMA channel to transfer data from the I2S receiver to a user-specified buffer.
 * It sets up the DMA configuration based on the I2S data width and instance, then initiates the DMA transfer.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A buffer structure containing the destination buffer for received data.
 * @param channel The channel number from which to receive data (0-based index).
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_ReceiveDMA(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, const uint8_t channel)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tRx.eDatasize;
    DMA_RequestSourceType temptype;

    pHandle->tStatus.tRx.finish[channel]              = false;
    pHandle->tStatus.tRx.sGlobalBuffer[channel].count = pbuffer.count;
    pHandle->tStatus.tRx.sGlobalBuffer[channel].data  = pbuffer.data;

    if (pHandle->eInstance == I2S_INSTANCE_0)
    {
        temptype = DMA_REQ_I2S0_RX;
    }
    else if (pHandle->eInstance == I2S_INSTANCE_1)
    {
        temptype = DMA_REQ_I2S1_RX;
    }
    else
    {
        temptype = DMA_REQ_I2S0_RX;
    }

    DMA_TransferSizeType tempSize = DMA_TRANSFER_SIZE_1B;
    if (tempDatasize == I2S_DATA_WIDTH_8BITS)
    {
        tempSize = DMA_TRANSFER_SIZE_1B;
    }
    else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
    {
        tempSize = DMA_TRANSFER_SIZE_2B;
    }
    else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
    {
        tempSize = DMA_TRANSFER_SIZE_4B;
    }
    else
    {
        tempSize = DMA_TRANSFER_SIZE_1B;
    }

    DMA_ChannelCfgType s_tDmaChannel0Cfg =
    {
        .pDestBuffer             = pHandle->tStatus.tRx.sGlobalBuffer[channel].data,
        .pSrcBuffer              = (&(pI2s->RX_DATA[channel])),
        .u32BlockSize            = (uint32_t)pHandle->tStatus.tRx.eDatasize,
        .u16BlockCount           = (uint16_t)pHandle->tStatus.tRx.sGlobalBuffer[channel].count,
        .u8ChannelPriority       = pHandle->tStatus.tRx.pDmaHandle[channel]->tSettings.u8Channel,
        .eSrcDataSize            = tempSize,
        .eDestDataSize           = tempSize,

        .eSrcIncMode             = DMA_INCREMENT_DISABLE,
        .eDestIncMode            = DMA_INCREMENT_DATA_SIZE,

        .bSrcBlockOffsetEn       = false,
        .bDestBlockOffsetEn      = false,
        .s32BlockOffset          = 0,

        .bSrcAddrLoopbackEn      = false,
        .bDestAddrLoopbackEn     = false,

        .bAutoStop               = true,

        .bSrcCircularBufferEn    = false,
        .u32SrcCircBufferSize    = 0U,
        .bDestCircularBufferEn   = false,
        .u32DestCircBufferSize   = 0U,

        .eTriggerSrc             = temptype,

        .bTransferCompleteIntEn  = true,
        .pTransferCompleteNotify = I2S_RX_DMACompleteCallback,
        .completedata            = (void *)pHandle,
    };
    s_tDmaChannel0Cfg.bTransferErrorIntEn     = false;
    s_tDmaChannel0Cfg.pTransferErrorNotify    = NULL;
    s_tDmaChannel0Cfg.errdata                 = NULL;
    DMA_InitChannel(pHandle->tStatus.tRx.pDmaHandle[channel], &s_tDmaChannel0Cfg);
    DMA_StartChannel(pHandle->tStatus.tRx.pDmaHandle[channel]);
}

/**
 * @brief Configures the I2S receive operation for a linked list of buffers with interrupts.
 *
 * This function sets up the I2S receive operation to use a linked list of buffers. It initializes the necessary structures,
 * including the current buffer index, total buffer count, and combines the buffer counts for the overall receive buffer size.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A pointer to an array of buffer structures containing the source buffers for received data.
 * @param channel The channel number from which to receive data (0-based index).
 * @param buffcount The total number of buffers in the linked list.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void  I2S_ReceiveLtoNInt(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount)
{
    pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].bCombine        = true;
    pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].u8BufferCurrent = 0U;
    pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList        = pbuffer;
    pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].u8BufferTotal   = buffcount;
    pHandle->tStatus.tRx.sGlobalBuffer[channel].count               = buffcount * (pbuffer[0].count);
}

/**
 * @brief Configures and starts the DMA for I2S receive operations with a linked list of buffers.
 *
 * This function initializes multiple DMA channels to transfer data from the I2S receiver to a linked list of buffers.
 * It sets up the DMA configuration based on the I2S data width, instance, and buffer list, then initiates the DMA transfers.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pbuffer A pointer to an array of buffer structures containing the destination buffers for received data.
 * @param channel The channel number from which to receive data (0-based index).
 * @param buffcount The total number of buffers in the linked list.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void  I2S_ReceiveLtoNDMA(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    DMA_Type *const pDma = DMA;
    uint16_t u16Temp;
    I2S_DataWidthMode tempDatasize = pHandle->tStatus.tRx.eDatasize;
    DMA_RequestSourceType temptype;

    pHandle->tStatus.tRx.finish[channel]                           = false;
    pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList       = pbuffer;
    pHandle->tStatus.tRx.sGlobalBufferLtoN[channel]. u8BufferTotal = buffcount;

    if (pHandle->eInstance == I2S_INSTANCE_0)
    {
        temptype = DMA_REQ_I2S0_RX;
    }
    else if (pHandle->eInstance == I2S_INSTANCE_1)
    {
        temptype = DMA_REQ_I2S1_RX;
    }
    else
    {
        temptype = DMA_REQ_I2S0_RX;
    }

    DMA_TransferSizeType tempSize;
    if (tempDatasize == I2S_DATA_WIDTH_8BITS)
    {
        tempSize = DMA_TRANSFER_SIZE_1B;
    }
    else if (tempDatasize == I2S_DATA_WIDTH_16BITS)
    {
        tempSize = DMA_TRANSFER_SIZE_2B;
    }
    else if (tempDatasize == I2S_DATA_WIDTH_32BITS)
    {
        tempSize = DMA_TRANSFER_SIZE_4B;
    }
    else
    {
        tempSize = DMA_TRANSFER_SIZE_1B;
    }

    DMA_ChannelCfgType s_tDmaChannel0Cfg = {0};

    s_tDmaChannel0Cfg .pSrcBuffer             = (&(pI2s->RX_DATA[channel]));
    s_tDmaChannel0Cfg.u8ChannelPriority       = 0U;
    s_tDmaChannel0Cfg.eSrcDataSize            = tempSize;
    s_tDmaChannel0Cfg.eDestDataSize           = tempSize;
    s_tDmaChannel0Cfg.eSrcIncMode             = DMA_INCREMENT_DISABLE;
    s_tDmaChannel0Cfg .eDestIncMode           = DMA_INCREMENT_DATA_SIZE;

    s_tDmaChannel0Cfg.bSrcBlockOffsetEn       = false;
    s_tDmaChannel0Cfg.bDestBlockOffsetEn      = false;
    s_tDmaChannel0Cfg.s32BlockOffset          = 0;

    s_tDmaChannel0Cfg .bSrcAddrLoopbackEn     = false;
    s_tDmaChannel0Cfg .bDestAddrLoopbackEn    = false;
    s_tDmaChannel0Cfg .bAutoStop              = true;
    s_tDmaChannel0Cfg .bSrcCircularBufferEn   = false;
    s_tDmaChannel0Cfg .u32SrcCircBufferSize   = 0U;
    s_tDmaChannel0Cfg .bDestCircularBufferEn  = false;
    s_tDmaChannel0Cfg .u32DestCircBufferSize  = 0U;
    s_tDmaChannel0Cfg.u32BlockSize            = (uint32_t)pHandle->tStatus.tRx.eDatasize;

    s_tDmaChannel0Cfg.bTransferCompleteIntEn  = true;
    s_tDmaChannel0Cfg.pTransferCompleteNotify = I2S_RX_DMACompleteCallback;
    s_tDmaChannel0Cfg.completedata            = (void *)pHandle;

    for (uint8_t i = 0U; i < buffcount; i++)
    {
        s_tDmaChannel0Cfg.bTransferErrorIntEn     = false;
        s_tDmaChannel0Cfg.pTransferErrorNotify    = NULL;
        s_tDmaChannel0Cfg.errdata                 = NULL;
        s_tDmaChannel0Cfg.pDestBuffer   = pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList[i].data;
        s_tDmaChannel0Cfg.u16BlockCount = (uint16_t)pHandle->tStatus.tRx.sGlobalBufferLtoN[channel].pBufList[i].count;
        if (i == 0U)
        {
            s_tDmaChannel0Cfg .eTriggerSrc = temptype;
        }
        else
        {
            s_tDmaChannel0Cfg .eTriggerSrc = DMA_REQ_DISABLED;
        }

        DMA_InitChannel(pHandle->tStatus.tRx.pDmaHandle[i], &s_tDmaChannel0Cfg);
        DMA_HWA_SetChannelToChannelTrig(pDma, pHandle->tStatus.tRx.pDmaHandle[i]->tSettings.u8Channel, false, 0U);
        if (i < buffcount - 1U)
        {
            u16Temp = pDma->CFG[pHandle->tStatus.tRx.pDmaHandle[i]->tSettings.u8Channel].CSR;
            u16Temp |= (uint16_t)(DMA_CFG_CSR_OCHTRGEN(1) | DMA_CFG_CSR_OTRGCH(pHandle->tStatus.tRx.pDmaHandle[i + 1U]->tSettings.u8Channel));
            pDma->CFG[pHandle->tStatus.tRx.pDmaHandle[i]->tSettings.u8Channel].CSR = u16Temp;

            u16Temp = pDma->CFG[pHandle->tStatus.tRx.pDmaHandle[i]->tSettings.u8Channel].BLC.CHTRGENYES;
            u16Temp &= (uint16_t)(~DMA_CFG_BLC_CHTRGENYES_TRGCH_MASK);
            u16Temp |= (uint16_t)(DMA_CFG_BLC_CHTRGENYES_CHTRGEN(1U) | DMA_CFG_BLC_CHTRGENYES_TRGCH(pHandle->tStatus.tRx.pDmaHandle[i + 1U]->tSettings.u8Channel));
            pDma->CFG[pHandle->tStatus.tRx.pDmaHandle[i]->tSettings.u8Channel].BLC.CHTRGENYES = u16Temp;

            u16Temp = pDma->CFG[pHandle->tStatus.tRx.pDmaHandle[i]->tSettings.u8Channel].CLC.CHTRGENYES;
            u16Temp &= (uint16_t)(~DMA_CFG_CLC_CHTRGENYES_TRGCH_MASK);
            u16Temp |= (uint16_t)(DMA_CFG_CLC_CHTRGENYES_CHTRGEN(1U) | DMA_CFG_CLC_CHTRGENYES_TRGCH(pHandle->tStatus.tRx.pDmaHandle[i + 1U]->tSettings.u8Channel));
            pDma->CFG[pHandle->tStatus.tRx.pDmaHandle[i]->tSettings.u8Channel].CLC.CHTRGENYES = u16Temp;
        }
    }
    DMA_StartChannel(pHandle->tStatus.tRx.pDmaHandle[0]);
}

/**
 * @brief DMA Transfer Complete Callback for I2S Reception.
 *
 * This function is triggered when an I2S reception DMA transfer finishes.
 * If a user-defined callback is registered, it is invoked to notify the application about the completed transfer.
 *
 * @param arg Pointer to the I2S handle, containing context and status information.
 */
static void I2S_RX_DMACompleteCallback(void *arg)
{
    I2S_HandleType *pHandle = (I2S_HandleType *)arg;

    if (pHandle->tSettings.tRx.pTransferFinishNotify != NULL)
    {
        pHandle->tSettings.tRx.pTransferFinishNotify(pHandle);
    }
}

/**
 * @brief Initializes the DMA for I2S receive operations based on the provided configuration.
 *
 * This function configures the DMA channels for I2S receive operations according to the specified initialization parameters.
 * It enables the transfer complete interrupt and assigns a callback for notification when the transfer is finished.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 * @param pInitCfg A pointer to the I2S RX initialization structure containing DMA channel configurations and transfer mode.
 *
 * @note This is a static function intended for internal use within the I2S driver.
 */
static void I2S_RX_DMAInit(I2S_HandleType *const pHandle, const I2S_RX_InitType *const pInitCfg)
{
    if (pInitCfg->eTranferMode == I2S_TRANFER_DMA)
    {
        for (uint8_t i = 0U; i < I2S_CHANNLE_NUM; i++)
        {
            pHandle->tStatus.tRx.pDmaHandle[i] = pInitCfg->pDmaHandle[i];
        }
    }
}

/**
 * @brief Handles common I2S interrupt requests for both transmit and receive operations.
 *
 * This function serves as a unified interrupt service routine for I2S. It checks for various interrupt flags, handles transmit and
 * receive FIFO requests, data errors, sync errors, and underrun/overrun conditions. Depending on the transfer mode,
 * it calls the appropriate functions to fill or receive data, and invokes user-defined callbacks for error notifications or transfer completion.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 *
 * @note This function is intended to be used internally by the I2S driver.
 */
void I2S_CommonIRQHandler(I2S_HandleType *const pHandle)
{
    I2S_Type *const pI2s = s_apI2sBase[pHandle->eInstance];
    bool finishTX = false;
    bool finishRX = false;

    if ((I2S_HWA_TX_GetFifoRequestFlag(pI2s)) && (pHandle->tStatus.tTx.eTranferMode == I2S_TRANFER_INTERRUPT))
    {
        for (uint8_t i = 0U; i < I2S_CHANNLE_NUM; i++)
        {
            if ((I2S_HWA_TX_GetChannelState(pI2s, (I2S_TX_ChannelType)(1 << i))) && (pHandle->tStatus.tTx.finish[i] != true) &&
                (pHandle->tStatus.I2Sn_WORKMODEINT[i] == I2S_CHANNEL_WORKMODE_TX))
            {
                if (pHandle->tStatus.tTx.sGlobalBufferNtoL[i].bCombine == true)
                {
                    I2S_FillDataNtoLInt(pHandle, i, &finishTX);
                }
                else
                {
                    I2S_FillDataInt(pHandle, i, &finishTX);
                }
            }
        }

    }

    if (finishTX)
    {
        I2S_HWA_TX_DisableFifoRequestInterrupt(pI2s);
        if (pHandle->tSettings.tTx.pTransferFinishNotify != NULL)
        {
            pHandle->tSettings.tTx.pTransferFinishNotify(pHandle);
        }
    }

    if (I2S_HWA_TX_GetDataFlag(pI2s))
    {
        if (pHandle->tSettings.tTx.pDataErrorNotify != NULL)
        {
            pHandle->tSettings.tTx.pDataErrorNotify(pHandle);
        }
        I2S_HWA_TX_ClearDataFlag(pI2s);
    }

    if (I2S_HWA_TX_GetSyncFlag(pI2s))
    {
        if (pHandle->tSettings.tTx.pSyncErrorNotify != NULL)
        {
            pHandle->tSettings.tTx.pSyncErrorNotify(pHandle);
        }
        I2S_HWA_TX_ClearSyncFlag(pI2s);
    }

    if (I2S_HWA_TX_GetUnderrunFlag(pI2s))
    {
        if (pHandle->tSettings.tTx.pFifoErrorNotify != NULL)
        {
            pHandle->tSettings.tTx.pFifoErrorNotify(pHandle);
        }

        I2S_HWA_TX_ClearUnderrunFlag(pI2s);
    }

    /*RX*/
    if ((I2S_HWA_RX_GetFifoRequestFlag(pI2s)) && (pHandle->tStatus.tRx.eTranferMode == I2S_TRANFER_INTERRUPT))
    {
        for (uint8_t i = 0U; i < I2S_CHANNLE_NUM; i++)
        {
            if ((I2S_HWA_RX_GetChannelState(pI2s, (I2S_RX_ChannelType)(1 << i))) && (pHandle->tStatus.tRx.finish[i] != true) &&
                (pHandle->tStatus.I2Sn_WORKMODEINT[i] == I2S_CHANNEL_WORKMODE_RX))
            {
                if (pHandle->tStatus.tRx.sGlobalBufferLtoN[i].bCombine == true)
                {
                    I2S_ReceiveDataLtoNInt(pHandle, i, &finishRX);
                }
                else
                {
                    I2S_ReceiveDataInt(pHandle, i, &finishRX);
                }
            }
        }
    }

    if (finishRX)
    {
        I2S_HWA_RX_DisableFifoRequestInterrupt(pI2s);
        if (pHandle->tSettings.tRx.pTransferFinishNotify != NULL)
        {
            pHandle->tSettings.tRx.pTransferFinishNotify(pHandle);
        }

    }

    if (I2S_HWA_RX_GetDataFlag(pI2s))
    {
        if (pHandle->tSettings.tRx.pDataErrorNotify != NULL)
        {
            pHandle->tSettings.tRx.pDataErrorNotify(pHandle);
        }
        I2S_HWA_RX_ClearDataFlag(pI2s);
    }

    if (I2S_HWA_RX_GetSyncFlag(pI2s))
    {
        if (pHandle->tSettings.tRx.pSyncErrorNotify != NULL)
        {
            pHandle->tSettings.tRx.pSyncErrorNotify(pHandle);
        }
        I2S_HWA_RX_ClearSyncFlag(pI2s);
    }

    if (I2S_HWA_RX_GetOverrunFlag(pI2s))
    {
        if (pHandle->tSettings.tRx.pFifoErrorNotify != NULL)
        {
            pHandle->tSettings.tRx.pFifoErrorNotify(pHandle);
        }
        I2S_HWA_RX_ClearOverrunFlag(pI2s);
    }
}

#endif
