/**
 * @file module_driver_i2s.h
 * @author Flagchip100
 * @brief I2S driver type definition and API
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

#ifndef DRIVER_INCLUDE_MODULE_DRIVER_I2S_H_
#define DRIVER_INCLUDE_MODULE_DRIVER_I2S_H_

#include "HwA_i2s.h"

#if I2S_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_i2s
 * @{
 */

#include "module_driver_dma.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  I2S API Service IDs
 *
 * @{
 */
#define I2S_TX_INIT_ID          0x00U
#define I2S_TX_DEINIT_ID        0x01U
#define I2S_TX_GETDEFAULT_ID    0x02U
#define I2S_SEND_ID             0x03U
#define I2S_SEND_NTOL_ID        0x04U
#define I2S_SEND_STOP_ID        0x05U
#define I2S_RX_INIT_ID          0x06U
#define I2S_RX_DEINIT_ID        0x07U
#define I2S_RX_GETDEFAULT_ID    0x08U
#define I2S_RECEIVE_ID          0x09U
#define I2S_RECEIVE_LTON_ID     0x0AU
#define I2S_RECEIVE_STOP_ID     0x0BU

/** @}*/

/**
 * @name  I2S Dev Error Code
 * @brief Error Code of calling I2S apis
 *
 * @{
 */
#define I2S_E_PARAM_NULLPTR     0x01U
#define I2S_E_PARAM_INSTANCE    0x02U
#define I2S_E_PARAM_CHANNEL     0x03U

/** @}*/

/**
 * @brief Define the number of I2S channels.
 *        This constant specifies the number of I2S channels supported.
 */
#define I2S_CHANNLE_NUM         4U


/**
 * @brief Define the depth of the I2S FIFO.
 *        This constant specifies the depth of the I2S FIFO buffer.
 */
#define I2S_FIFO_DEPTH          8U

/**
 * @brief The instance index of the I2S peripheral
 * 
 */
typedef enum
{
    I2S_INSTANCE_0  = 0U,   /**< I2S instance 0 is selected */
    I2S_INSTANCE_1  = 1U    /**< I2S instance 1 is selected */
} I2S_InstanceType;

/**
 * @brief  Masked Data Index
 * 
 */
typedef enum
{
    I2S_MASKED_NONE  = 0x0000U,
    I2S_MASKED_IDX1  = 0x0001U,
    I2S_MASKED_IDX2  = 0x0002U,
    I2S_MASKED_IDX3  = 0x0004U,
    I2S_MASKED_IDX4  = 0x0008U,
    I2S_MASKED_IDX5  = 0x0010U,
    I2S_MASKED_IDX6  = 0x0020U,
    I2S_MASKED_IDX7  = 0x0040U,
    I2S_MASKED_IDX8  = 0x0080U,
    I2S_MASKED_IDX9  = 0x0100U,
    I2S_MASKED_IDX10 = 0x0200U,
    I2S_MASKED_IDX11 = 0x0400U,
    I2S_MASKED_IDX12 = 0x0800U,
    I2S_MASKED_IDX13 = 0x1000U,
    I2S_MASKED_IDX14 = 0x2000U,
    I2S_MASKED_IDX15 = 0x4000U,
    I2S_MASKED_IDX16 = 0x8000U
} I2S_MaskedDataIDx;

/**
 *@brief I2S Channel work Mode
 *
 */
typedef enum
{
    I2S_CHANNEL_WORKMODE_IDLE = 0U, /**< channel not be configed */
    I2S_CHANNEL_WORKMODE_TX = 1U,   /**< channel work as transmit Mode */
    I2S_CHANNEL_WORKMODE_RX = 2U    /**< channel work as receiver Mode */
} I2S_Channel_Workmode;

/**
 *@brief TX transmit data Mode
 *
 */
typedef enum
{
    I2S_TRANFER_INTERRUPT = 0U,     /**< transmit data by INT */
    I2S_TRANFER_DMA = 1U            /**< transmit data by DMA */
} I2S_TranferMode;

/**
 *@brief I2S transmit data size
 *
 */
typedef enum
{
    I2S_DATA_WIDTH_INVALID = 0U,    /**< Invalid data width mode */
    I2S_DATA_WIDTH_8BITS = 1U,      /**< 8-bit data width mode */
    I2S_DATA_WIDTH_16BITS = 2U,     /**< 16-bit data width mode */
    I2S_DATA_WIDTH_32BITS = 4U      /**< 32-bit data width mode */
} I2S_DataWidthMode;

/**
 *@brief I2S transmit data container include buff and transmit datacount
 *
 */
typedef struct
{
    uint8_t *data;                  /**< Pointer to the buffer data */
    uint32_t count;                 /**< Number of elements in the buffer */
} I2S_BufferType;

/**
 *@brief I2S transmit data container ,only used in NtoL  Mode  && transmit by INT
 *
 */
typedef struct
{
    I2S_BufferType *pBufList;       /**< Pointer to the list of I2S buffers */
    uint8_t u8BufferTotal;          /**< Total number of buffers in the list */
    uint8_t u8BufferCurrent;        /**< Current buffer index */
    bool bCombine;                  /**< Indicates if combining is enabled */
    uint8_t _aligned;
} I2S_CombineBufferType;

/**
 * @brief The structure of the I2S processing handle
 *
 */
typedef struct _I2S_HandleType
{
    I2S_InstanceType eInstance;                                             /**< I2S instance*/
    uint8_t _aligned[3U];

    struct
    {
        struct {
            void (*pDataErrorNotify)(struct _I2S_HandleType *pHandle);      /**< Data error notify callback */
            void (*pSyncErrorNotify)(struct _I2S_HandleType *pHandle);      /**< Sync error notify callback */
            void (*pFifoErrorNotify)(struct _I2S_HandleType *pHandle);      /**< FIFO error notify callback */
            void (*pTransferFinishNotify)(struct _I2S_HandleType *pHandle); /**< Transfer finish notify callback */
        } tTx;
        struct {
            void (*pDataErrorNotify)(struct _I2S_HandleType *pHandle);      /**< Data error notify callback */
            void (*pSyncErrorNotify)(struct _I2S_HandleType *pHandle);      /**< Sync error notify callback */
            void (*pFifoErrorNotify)(struct _I2S_HandleType *pHandle);      /**< FIFO error notify callback */
            void (*pTransferFinishNotify)(struct _I2S_HandleType *pHandle); /**< Transfer finish notify callback */
        } tRx;
    } tSettings;

    struct
    {
        I2S_Channel_Workmode I2Sn_WORKMODEINT[I2S_CHANNLE_NUM];             /**< Work mode for each I2S channel */

        struct {
            I2S_BufferType sGlobalBuffer[I2S_CHANNLE_NUM];                  /**< Store data pointer and data count of each channel transfer */
            I2S_CombineBufferType  sGlobalBufferNtoL[I2S_CHANNLE_NUM];      /**< Store data pointer and data count ,only used in NtoL mode */
            DMA_HandleType *pDmaHandle[I2S_CHANNLE_NUM];                    /**< DMA handle for each transmit channel */

            uint32_t u32WaterMark;                                          /**< Watermark level for the FIFO */

            I2S_TranferMode  eTranferMode;                                  /**< Transfer mode */
            I2S_DataWidthMode eDatasize;                                    /**< Data width mode */

            bool finish[I2S_CHANNLE_NUM];                                   /**< Transfer completion flags for each channel */

            uint8_t _aligned[2U];
        } tTx;
        struct {
            I2S_BufferType sGlobalBuffer[I2S_CHANNLE_NUM];                  /**< Store data pointer and data count of each channel transfer */
            I2S_CombineBufferType sGlobalBufferLtoN[I2S_CHANNLE_NUM];       /**< Store data pointer and data count ,only used in NtoL mode */
            DMA_HandleType *pDmaHandle[I2S_CHANNLE_NUM];                    /**< DMA handle for each transmit channel */

            uint32_t u32WaterMark;                                          /**< Watermark level for the FIFO */

            I2S_TranferMode  eTranferMode;                                  /**< Transfer mode */
            I2S_DataWidthMode eDatasize;                                    /**< Data width mode */

            bool finish[I2S_CHANNLE_NUM];                                   /**< Transfer completion flags for each channel */

            uint8_t _aligned[2U];
        } tRx;
    } tStatus;
} I2S_HandleType;

/**
 * @brief The initialization structure for the send mode
 *
 */
typedef struct
{
    uint32_t u32WaterMark;                                  /**< Configures the watermark for all enabled transmit channels */
    uint32_t u32ClkDiv;                                     /**< If bit clock is generated internally, it is divided from master clock by this. User need to init this if master clock is external */

    DMA_HandleType *pDmaHandle[I2S_CHANNLE_NUM];            /**< DMA handle for each transmit channel */

    I2S_MaskedDataIDx  MaskedInx;                           /**< Transmit Data Mask,1b - Data N is masked. The transmit data pins are tri-stated or drive zero when masked */

    uint8_t u8DataWidth;                                    /**< Configure the width of remaining data except the 1st data in each frame */
    uint8_t u8FirstBitShift;                                /**< Shift amount for the first bit of data */
    uint8_t u8StartDataInx;                                 /**< Configures which data sets the start of data flag. The flag sets at DSF_CFG+1 data in a frame */
    uint8_t u8FrameSize;                                    /**< Configures the number of data in each frame */

    bool bMasterMode;                                       /**< Select master Mode */
    bool bStopEn;                                           /**< Enable Stop Mode */
    bool bDataStartIntEn;                                   /**< Enable Data start report */
    bool bSyncIntEn;                                        /**< Enable sync error report */
    bool bFifoUnderrunIntEn;                                /**< Underrun error report */

    I2S_TX_SynchronousMode eSynchronousMode;                /**< Sync mode */
    I2S_TX_MclkSelType eMclkSelType;                        /**< Select master clock source */
    I2S_TX_BclkPolarityMode eBclkPolarityMode;              /**< Select master BCLK Polarity */
    I2S_TX_ChannelType eChannelEnable;                      /**< Turn on each bit to enable each channel. 4 bit for 4 channels */
    I2S_TX_RestartMode eURRestartMode;                      /**< Restart Mode.used in FIFO underrun detected */
    I2S_MaskedPinMode eMaskedPinMode;                       /**< Masked Pin Configuration */
    I2S_TX_Priority eMSBpriority;                           /**< MSB First Configuration */
    I2S_TXEarlySyncMode eEarlySyncMode;                     /**< Frame Sync Early, whether the  frame sync is one bit clock early */
    I2S_TXSyncMode eFrameSyncMode ;                         /**< 0b - Continuous frame sync,1b - No frame sync generated when FIFO empty flag set */
    I2S_TX_SyncPolarity eSyncPolarity;                      /**< Frame Sync Polarity */
    I2S_DataWidthMode eDatasize;                            /**< I2S transmit data size */
    I2S_TranferMode eTranferMode;                           /**< configure I2S transmit mode INT or DMA */

    uint8_t _aligned[1U];
} I2S_TX_InitType;

/**
 * @brief The initialization structure for the receive mode
 */
typedef struct
{
    uint32_t u32ClkDiv;                                     /**< If bit clock is generated internally, it is divided from master clock by this. User need to init this if master clock is external */
    uint32_t u32WaterMark;                                  /**< Configures the watermark for all enabled receive channels */

    DMA_HandleType *pDmaHandle[I2S_CHANNLE_NUM];            /**< DMA handle for each transmit channel */

    I2S_MaskedDataIDx MaskedInx;                            /**< receive Data Mask,1b - Data N is masked. The receive data pins are tri-stated or drive zero when masked */

    I2S_DataWidthMode eDatasize;                            /**< I2S receive data size */
    I2S_TranferMode eTranferMode;                           /**< configure I2S receive mode INT or DMA */
    I2S_MaskedPinMode eMaskedPinMode;                       /**< Masked Pin Configuration */
    I2S_RX_Priority eMSBpriority;                           /**< MSB First Configuration */
    I2S_RXEarlySyncMode eEarlySyncMode;                     /**< Frame Sync Early, whether the  frame sync is one bit clock early */
    I2S_RXSyncMode eFrameSyncMode ;                         /**< 0b - Continuous frame sync,1b - No frame sync generated when FIFO full flag set */
    I2S_RX_SyncPolarity eSyncPolarity;                      /**< Frame Sync Polarity */
    I2S_RX_SynchronousMode eSynchronousMode;                /**< Sync mode */
    I2S_RX_MclkSelType eMclkSelType;                        /**< Select master clock source */
    I2S_RX_BclkPolarityMode eBclkPolarityMode;              /**< Select master BCLK Polarity */
    I2S_RX_ChannelType eChannelEnable;                      /**< Turn on each bit to enable each Receive channel. 4 bit for 4 channels */
    I2S_RX_RestartMode eORRestartMode;                      /**< Restart Mode.used in FIFO overrun detected */

    uint8_t u8DataWidth;                                    /**< Configure the width of remaining data except the 1st data in each frame */
    uint8_t u8FirstBitShift;                                /**< Shift amount for the first bit of data */
    uint8_t u8StartDataInx;                                 /**< Configures which data sets the start of data flag. The flag sets at DSF_CFG+1 data in a frame */
    uint8_t u8FrameSize;                                    /**< Configures the number of data in each frame */

    bool bMasterMode;                                       /**< Select master Mode */
    bool bStopEn;                                           /**< Enable Stop Mode */
    bool bDataStartIntEn;                                   /**< Enable Data start report */
    bool bSyncIntEn;                                        /**< Enable sync error report */
    bool bFifoOverrunIntEn;                                 /**< overrun error report */

    uint8_t _aligned[1];
} I2S_RX_InitType;

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
void I2S_TX_GetDefaultConfig(I2S_TX_InitType *const pInitCfg);

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
void I2S_TX_Init(I2S_HandleType *const pHandle, const I2S_TX_InitType *const pInitCfg);

/**
 * @brief Deinitializes the I2S transmitter module.
 *
 * This function resets the I2S transmitter module by clearing the handle status, resetting registers, and disabling interrupts and DMA.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance to deinitialize.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_TX_DeInit(I2S_HandleType *const pHandle);

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
void I2S_Send(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, uint8_t channel);

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
void I2S_SendNtoL(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount);

/**
 * @brief Stops the ongoing I2S transmission.
 *
 * This function halts an active I2S transmission by disabling the transmitter, BCLK, and performing a software reset.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance to stop.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_SendStop(I2S_HandleType *const pHandle);

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
void I2S_RX_GetDefaultConfig(I2S_RX_InitType *const pInitCfg);

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
void I2S_RX_Init(I2S_HandleType *const pHandle, const I2S_RX_InitType *const pInitCfg);

/**
 * @brief Deinitializes the I2S receiver module.
 *
 * This function resets the I2S receiver module by clearing the handle status, resetting registers, and disabling interrupts and DMA.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance to deinitialize.
 * 
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_RX_DeInit(I2S_HandleType *const pHandle);

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
void I2S_Receive(I2S_HandleType *const pHandle, I2S_BufferType pbuffer, uint8_t channel);

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
void I2S_ReceiveLtoN(I2S_HandleType *const pHandle, I2S_BufferType *pbuffer, uint8_t channel, uint8_t buffcount);

/**
 * @brief Stops the ongoing I2S receive operation.
 *
 * This function halts the current I2S receiver operation by disabling the I2S hardware block, BCLK, and performing a software reset.
 *
 * @param pHandle A pointer to the I2S handle structure identifying the I2S instance.
 *
 * @note The error reporting macros are conditionally compiled based on `I2S_DEV_ERROR_REPORT` definition.
 */
void I2S_ReceiveStop(I2S_HandleType *const pHandle);

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
void I2S_CommonIRQHandler(I2S_HandleType *const pHandle);

#if defined(__cplusplus)
}
#endif

/** @}*/ /* module_driver_i2s */

#endif

#endif /* DRIVER_INCLUDE_MODULE_DRIVER_I2S_H_ */
