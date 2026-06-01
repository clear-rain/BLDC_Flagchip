/**
 * @file module_driver_dma.h
 * @author Flagchip099
 * @brief DMA driver type definition and API
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

#ifndef _DRIVER_MODULE_DRIVER_DMA_H_
#define _DRIVER_MODULE_DRIVER_DMA_H_

#include "HwA_dma.h"
#include "HwA_dmamux.h"

#if DMA_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif
/**
 * @addtogroup module_driver_dma
 * @{
 */

#define DMA_CH_TO_DCHPRI(x)   ((x) ^ 3U)
#define DMA_CHANNEL_INVALID   (0xFFU)

/**
 * @brief DMA transfer complete callback function prototype
 *
 */
typedef void (*DMA_TransferCompleteCallbackType)(void *arg);

/**
 * @brief DMA transfer error callback function prototype
 *
 */
typedef void (*DMA_TransferErrorCallbackType)(void *arg);

/**
 * @brief Available DMA Instances
 *
 */
typedef enum
{
    DMA_INSTANCE_0  = 0U,
    DMA_INSTANCE_1  = 1U,
    DMA_INSTANCE_MAX = DMA_INSTANCE_COUNT
} DMA_InstanceType;

/**
 * @brief Available DMA channels
 *
 */
typedef enum
{
    DMA_CHANNEL_0  = 0U,
    DMA_CHANNEL_1  = 1U,
    DMA_CHANNEL_2  = 2U,
    DMA_CHANNEL_3  = 3U,
    DMA_CHANNEL_4  = 4U,
    DMA_CHANNEL_5  = 5U,
    DMA_CHANNEL_6  = 6U,
    DMA_CHANNEL_7  = 7U,
    DMA_CHANNEL_8  = 8U,
    DMA_CHANNEL_9  = 9U,
    DMA_CHANNEL_10 = 10U,
    DMA_CHANNEL_11 = 11U,
    DMA_CHANNEL_12 = 12U,
    DMA_CHANNEL_13 = 13U,
    DMA_CHANNEL_14 = 14U,
    DMA_CHANNEL_15 = 15U,
    DMA_CHANNEL_MAX = 16U
} DMA_ChannelType;

/**
 * @brief DMA operation return values
 *
 */
typedef enum
{
    DMA_STATUS_SUCCESS         = 0x00U,   /**< The DMA operation is succeeded */
    DMA_STATUS_ERROR           = 0x01U,   /**< The DMA operation is failed */
    DMA_STATUS_BUSY            = 0x02U,   /**< The DMA operation is failed because DMA engine is busy */
    DMA_STATUS_TIMEOUT         = 0x03U,   /**< The DMA operation is failed because operation time out */
    DMA_STATUS_UNSUPPORTED     = 0x04U,   /**< The DMA configuration parameter is unsupported */
    DMA_STATUS_INVALID_ADDRESS = 0x05U,   /**< The DMA source/destination address is invalid */
    DMA_STATUS_NO_RESOURCE     = 0x06U    /**< The DMA operation is failed because there is no resource */
} DMA_StatusType;

/**
 * @brief DMA data increment size
 *
 * Specify the data increment size after DMA engine transferred a datum
 *
 */
typedef enum
{
    DMA_INCREMENT_DISABLE                 = 0x0U, /**< The data address not increase */
    DMA_INCREMENT_DATA_SIZE               = 0x1U, /**< The data address increase by the data size */
    DMA_INCREMENT_DATA_SIZE_4BYTE_ALIGNED = 0x2U  /**< The data address increase by the data size,
                                                       and is 4 byte aligned */
} DMA_IncrementModeType;

/**
 * @brief The size of the circular buffer
 *
 * @note The start address of the circular buffer should be aligned by the circular
 * buffer size
 *
 */
typedef enum
{
    DMA_CIRCULAR_BUFFER_SIZE_1B    = 0x1U,
    DMA_CIRCULAR_BUFFER_SIZE_2B    = 0x2U,
    DMA_CIRCULAR_BUFFER_SIZE_4B    = 0x4U,
    DMA_CIRCULAR_BUFFER_SIZE_8B    = 0x8U,
    DMA_CIRCULAR_BUFFER_SIZE_16B   = 0x10U,
    DMA_CIRCULAR_BUFFER_SIZE_32B   = 0x20U,
    DMA_CIRCULAR_BUFFER_SIZE_64B   = 0x40U,
    DMA_CIRCULAR_BUFFER_SIZE_128B  = 0x80U,
    DMA_CIRCULAR_BUFFER_SIZE_256B  = 0x100U,
    DMA_CIRCULAR_BUFFER_SIZE_512B  = 0x200U,
    DMA_CIRCULAR_BUFFER_SIZE_1KB   = 0x400U,
    DMA_CIRCULAR_BUFFER_SIZE_2KB   = 0x800U,
    DMA_CIRCULAR_BUFFER_SIZE_4KB   = 0x1000U,
    DMA_CIRCULAR_BUFFER_SIZE_8KB   = 0x2000U,
    DMA_CIRCULAR_BUFFER_SIZE_16KB  = 0x4000U,
    DMA_CIRCULAR_BUFFER_SIZE_32KB  = 0x8000U,
    DMA_CIRCULAR_BUFFER_SIZE_64KB  = 0x10000U,
    DMA_CIRCULAR_BUFFER_SIZE_128KB = 0x20000U,
    DMA_CIRCULAR_BUFFER_SIZE_256KB = 0x40000U,
    DMA_CIRCULAR_BUFFER_SIZE_512KB = 0x80000U,
    DMA_CIRCULAR_BUFFER_SIZE_1MB   = 0x100000U,
    DMA_CIRCULAR_BUFFER_SIZE_2MB   = 0x200000U,
    DMA_CIRCULAR_BUFFER_SIZE_4MB   = 0x400000U,
    DMA_CIRCULAR_BUFFER_SIZE_8MB   = 0x800000U,
    DMA_CIRCULAR_BUFFER_SIZE_16MB  = 0x1000000U,
    DMA_CIRCULAR_BUFFER_SIZE_32MB  = 0x2000000U,
    DMA_CIRCULAR_BUFFER_SIZE_64MB  = 0x4000000U,
    DMA_CIRCULAR_BUFFER_SIZE_128MB = 0x8000000U,
    DMA_CIRCULAR_BUFFER_SIZE_256MB = 0x10000000U,
    DMA_CIRCULAR_BUFFER_SIZE_512MB = 0x20000000U,
    DMA_CIRCULAR_BUFFER_SIZE_1GB   = 0x40000000U,
    DMA_CIRCULAR_BUFFER_SIZE_2GB   = 0x80000000U,
} DMA_CircularBufferSizeType;

/**
 * @brief The eBufferRole of the circular buffer
 *
 */
typedef enum
{
    DMA_CIRCULAR_BUFFEER_ROLE_SOURCE      = 0x0U, /**< The circular buffer is used as the data source */
    DMA_CIRCULAR_BUFFEER_ROLE_DESTINATION = 0x1U  /**< The circular buffer is used as the data destination */
} DMA_CircularBufferRoleType;

/**
 * @name  DMA API Service IDs
 *
 * @{
 */
#define DMA_INIT_ID                          0U
#define DMA_INIT_CHANNEL_ID                  1U
#define DMA_DEINIT_CHANNEL_ID                2U
#define DMA_INIT_CHANNEL_INT_ID              3U
#define DMA_CONFIG_CHAINED_TRANS_ID          4U
#define DMA_CONFIG_MODIFY_ADDR_ID            5U
#define DMA_CONFIG_START_CH_ID               6U
#define DMA_CONFIG_STOP_CH_ID                7U
#define DMA_CONFIG_GET_CH_REQ_SOURCE_ID      8U
#define DMA_CONFIG_GET_CH_STATUS_ID          9U
/** @}*/

/**
 * @name  DMA Dev Error Code
 * @brief Error Code of calling DMA apis
 *
 * @{
 */
#define DMA_E_PARAM_CHCFG                       0x01U
#define DMA_E_PARAM_BLOCKCNT                    0x02U
#define DMA_E_PARAM_BLOCKSIZE                   0x03U
#define DMA_E_PARAM_DESTCIRCULARBUFSIZE         0x04U
#define DMA_E_PARAM_SRCCIRCULARBUFSIZE          0x05U
#define DMA_E_PARAM_INTERRUPTCFG                0x06U
#define DMA_E_PARAM_CHANNEL                     0x07U
#define DMA_E_PARAM_INSTANCE                    0x08U
#define DMA_E_PARAM_INITCFG                     0x09U
#define DMA_E_PARAM_BLOCKSIZE_DATASIZE          0x0AU
/** @}*/

/**
 * @brief The configuration parameters of the DMA engine
 *
 */
typedef struct
{
	bool bHaltOnError;                                  /**< Whether DMA halts when error occured */
    DMA_ArbitrationAlgorithmType eArbitrationAlgorithm; /**< Channel Arbitration Algorithm */
} DMA_InitType;

/**
 * @brief The structure of the DMA processing handle
 *
 */
typedef struct
{
    struct
    {
        uint8_t u8DmaDumoUsedStatus[DMA_DUMO_COUNT];    /**< tStatus can not be set by user */
    } tStatus;
    struct
    {
        uint8_t u8Instance;                                        /**< DMA Instance*/
        void (*pTransferErrorCallback[DMA_CFG_COUNT])(void *arg);  /**< fault interrupt callback */
        void *errdata[DMA_CFG_COUNT];                              /**< Error data buffer */
    } tSettings;
} DMA_InstanceHandleType;

/**
 * @brief DMA handle structure definition.
 *
 * This structure contains all the necessary settings and callbacks for a DMA channel.
 */
typedef struct _DMA_HandleType
{
    struct
    {
        uint8_t u8Channel;                   /**< DMA Channel*/
        DMA_InstanceHandleType *pInstance;   /**< DMA instance */
        struct
        {
            void *completedata;                           /**< Completed data buffer */
            void (*pTransferCompleteCallback)(void *arg); /**< channel interrupt callback */
        } callback;
    } tSettings;
} DMA_HandleType;

/**
 * @brief The configutation parameters of the DMA channel
 *
 * @note The u8ChannelPriority must be unique for different channels, the default is the channel number.
 * The u16BlockCount must be greater than 0.
 * @note When Circular buffer is enabled, the data address should be power of 2 aligned to the buffer size.
 * For example, if the circular buffer size is 32 byte, the data address should be 32 byte aligned. If the
 * circular buffer size is 40 byte, then the data address should be 64 byte aligned.
 *
 */
typedef struct
{
    const volatile void *pSrcBuffer;       /**< the source address of the data */
    volatile void *pDestBuffer;            /**< the destination address of the data */
    void *completedata;
    void *errdata;
    uint32_t u32BlockSize;                 /**< the data size of one block in byte */
    uint16_t u16BlockCount;                /**< the number of data blocks in one transfer */
    uint8_t u8ChannelPriority;             /**< channel priority, greater number means higher priority */
    DMA_TransferSizeType eSrcDataSize;     /**< source data size */
    DMA_TransferSizeType eDestDataSize;    /**< destination data size */
    DMA_IncrementModeType eSrcIncMode;     /**< source data address increment mode */
    DMA_IncrementModeType eDestIncMode;    /**< destination data address increment mode */
    bool bSrcBlockOffsetEn;                /**< whether to add a block offset to the source address after
                                                a block transfer */
    bool bDestBlockOffsetEn;               /**< whether to add a block offset to the destination address after
                                                a block transfer */
    int32_t s32BlockOffset;                /**< the signed address offset applied to the src/dest address
                                                after a block transfer */
    bool bSrcAddrLoopbackEn;               /**< whether the source address return to the set value after transfer */
    bool bDestAddrLoopbackEn;              /**< whether the destination address return to the set value after transfer */
    bool bAutoStop;                        /**< whether the DMA channel transfer automatically stops after one
                                                transfer finishes when the channel is triggered by hardware */
    bool bSrcCircularBufferEn;             /**< the source buffer of the DMA channel is a circular buffer */
    uint32_t u32SrcCircBufferSize;         /**< the source circular buffer size in byte, the buffer size is suggested
                                                to be power of 2 aligned */
    bool bDestCircularBufferEn;            /**< the destination buffer of the DMA channel is a circular buffer */
    uint32_t u32DestCircBufferSize;        /**< the destination circular buffer size in byte, the buffer size is suggested
                                                to be power of 2 aligned */
    bool bInnerChannelChain;
    DMA_RequestSourceType eTriggerSrc;     /**< Select the DMA channel trigger source, if the trigger source is
                                                DMA_REQ_DISABLED, the channel is triggered by software */
    bool bTransferCompleteIntEn;           /**< Enable interrupt after transfer complete */
    DMA_TransferCompleteCallbackType pTransferCompleteNotify; /**< transfer complete notification */
    bool bTransferErrorIntEn;              /**< Enable interrupt when transfer error occured */
    DMA_TransferErrorCallbackType pTransferErrorNotify;       /**< transfer error notification */
} DMA_ChannelCfgType;

/**
 * @brief The parameters to configure the DMA channel as a circular buffer engine
 *
 */
typedef struct
{
    DMA_CircularBufferRoleType eBufferRole; /**< the source or the destination address is a circular buffer */
    DMA_CircularBufferSizeType eBufferSize; /**< the circular buffer size */
    bool bCircularBufferEn;                 /**< enable the DMA channel as a circular buffer engine */
} DMA_CircularBufferType;

/**
 * @brief The paarameters to configure the DMA chainned transfer
 *
 */
typedef struct
{
    bool bChanelChainEn;      /**< Whether to start the chained channel when the current completed */
    uint8_t u8ChainedChannel; /**< The chained channel */
} DMA_ChainTransferType;

/**
 * @brief Initializes the DMA instance.
 *
 * This function initializes the DMA instance with the specified configuration.
 *
 * @param pDmaInstanceHandle Pointer to the DMA instance handle.
 * @param pInitCfg Pointer to the initialization configuration structure.
 */
void DMA_Init(DMA_InstanceHandleType *pDmaInstanceHandle, const DMA_InitType *const pInitCfg);

/**
 * @brief Deinitializes the DMA instance.
 *
 * This function disables the DMA and restores its configuration to default.
 */
void DMA_DeInit(void);

/**
 * @brief Initializes the DMA channel.
 *
 * This function initializes the DMA channel with the specified configuration.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 * @param pChnCfg Pointer to the channel configuration structure.
 *
 * @return DMA_StatusType Indicates whether the channel was initialized successfully.
 */
DMA_StatusType DMA_InitChannel(DMA_HandleType *pDmaHandle, const DMA_ChannelCfgType *const pChnCfg);

/**
 * @brief Deinitializes the DMA channel.
 *
 * This function deinitializes the specified DMA channel.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 */
void DMA_DeinitChannel(DMA_HandleType *pDmaHandle);

/**
 * @brief Configures the chained transfer for the DMA channel.
 *
 * This function configures the chained transfer parameters for the specified DMA channel.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 * @param pChainTransferCfg Pointer to the chained transfer configuration structure.
 */
void DMA_ConfigChainedTransfer(DMA_HandleType *pDmaHandle,
                               const DMA_ChainTransferType *const pChainTransferCfg);

/**
 * @brief Modifies the source and destination addresses of the DMA channel.
 *
 * This function modifies the source and/or destination addresses of the specified DMA channel.
 * It should only be called when the DMA channel is not actively transferring.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 * @param pSrcBuffer Pointer to the new source buffer address. Set NULL to keep the current address.
 * @param pDestBuffer Pointer to the new destination buffer address. Set NULL to keep the current address.
 *
 * @return DMA_StatusType Indicates whether the addresses were modified successfully.
 */
DMA_StatusType DMA_ModifyAddress(DMA_HandleType *pDmaHandle, const volatile void *pSrcBuffer,
                                 const volatile void *pDestBuffer);

/**
 * @brief Starts the DMA channel transfer.
 *
 * If the trigger source for the DMA channel is disabled, the channel starts immediately.
 * Otherwise, the channel starts when the trigger source is generated.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 */
void DMA_StartChannel(DMA_HandleType *pDmaHandle);

/**
 * @brief Stops the DMA channel transfer.
 *
 * If the trigger source for the DMA channel is disabled, the channel stops automatically
 * after the transfer completes. Otherwise, this function must be called to prevent the
 * DMA from being triggered when the hardware request is generated.
 *
 * Note: If there is an ongoing transfer on the channel, the channel will stop after the
 * transfer completes.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 */
void DMA_StopChannel(DMA_HandleType *pDmaHandle);

/**
 * @brief Cancels the ongoing DMA transfer.
 *
 * This function cancels the ongoing DMA transfer on the specified channel.
 *
 * @param bGenerateErr Indicates whether to generate an error on the transferring channel.
 *
 * @return DMA_StatusType Indicates whether the transfer was canceled successfully.
 */
DMA_StatusType DMA_CancelTransfer(bool bGenerateErr);

/**
 * @brief Retrieves the request source of the selected DMA channel.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 *
 * @return DMA_RequestSourceType The request source of the selected DMA channel.
 */
DMA_RequestSourceType DMA_GetChannelRequestSrc(DMA_HandleType *pDmaHandle);

/**
 * @brief Retrieves the status of the DMA engine.
 *
 * @return DMA_RunningStatusType The status of the DMA engine.
 */
DMA_RunningStatusType DMA_GetStatus(void);

/**
 * @brief Retrieves the status of the specified DMA channel.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 *
 * @return DMA_RunningStatusType The status of the DMA channel.
 */
DMA_RunningStatusType DMA_GetChannelStatus(DMA_HandleType *pDmaHandle);

/**
 * @brief Internal interrupt handler for DMA transfer complete.
 *
 * This function handles the DMA transfer complete interrupt.
 *
 * @param pDmaHandle Pointer to the DMA handle.
 */
void DMA_Transfer_Complete_IRQHandler(DMA_HandleType *pDmaHandle);

/**
 * @brief Internal interrupt handler for DMA error processing.
 *
 * This function handles DMA errors.
 *
 * @param pDmaInstanceHandle Pointer to the DMA instance handle.
 */
void DMA_ProcessErrorInterrupt(DMA_InstanceHandleType *pDmaInstanceHandle);


/** @}*/ /* module_driver_dma */
#if defined(__cplusplus)
}
#endif

#endif

#endif
