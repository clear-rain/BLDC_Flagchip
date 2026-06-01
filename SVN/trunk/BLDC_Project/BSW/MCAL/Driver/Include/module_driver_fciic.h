/**
 * @file module_driver_fciic.h
 * @author Flagchip
 * @brief FCIIC driver type definition and API
 * @version 2.0.0
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    qxw0113   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER__FCIIC_H_
#define _DRIVER_MODULE_DRIVER__FCIIC_H_

#include "HwA_fciic.h"

#if FCIIC_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_fciic
 * @{
 */

#include "module_driver_dma.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  FCIIC API Service IDs
 *
 * @{
 */

#define FCIIC_MASTERCHECKFORBUSYBUS_ID                                    0x00 /**< ID for checking the bus busy status. */
#define FCIIC_MASTERGETDEFAULTCONFIG_ID                                   0x01 /**< ID for getting the default configuration. */
#define FCIIC_MASTERSETBAUDRATE_ID                                        0x02 /**< ID for setting the baud rate. */
#define FCIIC_MASTERINIT_ID                                               0x03 /**< ID for initializing the master. */
#define FCIIC_MASTERDEINIT_ID                                             0x04 /**< ID for deinitializing the master. */
#define FCIIC_MASTERINITHANDLE_ID                                         0x05 /**< ID for initializing the master handle. */
#define FCIIC_MASTERENABLEINTERRUPT_ID                                    0x06 /**< ID for enabling interrupts. */
#define FCIIC_MASTERCHECKANDCLEARERROR_ID                                 0x07 /**< ID for checking and clearing errors. */
#define FCIIC_MASTERWAITFLAG_ID                                           0x08 /**< ID for waiting on a flag. */
#define FCIIC_MASTERSTART_ID                                              0x09 /**< ID for starting the transfer. */
#define FCIIC_MASTERREPEATEDSTART_ID                                      0x0a /**< ID for initiating a repeated start. */
#define FCIIC_MASTERSENDSTARTCOMMAND_ID                                   0x0b /**< ID for sending a start command. */
#define FCIIC_MASTERSEND_ID                                               0x0c /**< ID for sending data. */
#define FCIIC_MASTERRECEIVE_ID                                            0x0d /**< ID for receiving data. */
#define FCIIC_MASTERSTOP_ID                                               0x0e /**< ID for stopping the transfer. */
#define FCIIC_MASTERTRANSFERABORT_ID                                      0x0f /**< ID for aborting the transfer. */
#define FCIIC_MASTERSETRECEIVELEN_ID                                      0x10 /**< ID for setting the receive length. */
#define FCIIC_MASTERTRANSMIT_ID                                           0x11 /**< ID for transmitting data. */
#define FCIIC_MASTERGETSTATUS_ID                                          0x12 /**< ID for getting the status. */
#define FCIIC_MASTERCLRSTATUS_ID                                          0x13 /**< ID for clearing the status. */
#define FCIIC_MASTERTRANSFERBLOCKING_ID                                   0x14 /**< ID for performing a blocking transfer. */
#define FCIIC_MASTERDMAPREPARE_ID                                         0x15 /**< ID for preparing DMA. */
#define FCIIC_MASTERDMASTOP_ID                                            0x16 /**< ID for stopping DMA. */
#define FCIIC_MASTERDMATRANSMIT_ID                                        0x17 /**< ID for DMA transmission. */
#define FCIIC_MASTERDMARECEIVE_ID                                         0x18 /**< ID for DMA reception. */
#define FCIIC_MASTERDMASTART_ID                                           0x19 /**< ID for starting DMA. */
#define FCIIC_MASTERDMASTAGENOTIFICATION_ID                               0x1a /**< ID for DMA stage notification. */
#define FCIIC_MASTERDMASTAGEDATA_ID                                       0x1b /**< ID for DMA stage data. */
#define FCIIC_LL_MASTERDMAIRQNHANDLER_ID                                  0x1c /**< ID for the low-level master DMA IRQ handler. */
#define FCIIC_MASTERDMATRANSFER_ID                                        0x1d /**< ID for DMA transfer. */
#define FCIIC_MASTERINTERRUPTPROCESSSTOP_ID                               0x1e /**< ID for processing the stop interrupt. */
#define FCIIC_MASTERINTERRUPTPROCESSTRANSMIT_ID                           0x1f /**< ID for processing the transmit interrupt. */
#define FCIIC_MASTERINTERRUPTPROCESSRECEIVE_ID                            0x20 /**< ID for processing the receive interrupt. */
#define FCIIC_MASTERINTERRUPTPROCESSSTART_ID                              0x21 /**< ID for processing the start interrupt. */
#define FCIIC_LL_MASTERIRQNHANDLER_ID                                     0x21 /**< ID for the low-level master IRQ handler. */
#define FCIIC_MASTERGENERATESTARTCOMMAND_ID                               0x23 /**< ID for generating a start command. */
#define FCIIC_MASTERTRANSFERNONBLOCKING_ID                                0x24 /**< ID for non-blocking transfer. */
#define FCIIC_SLAVEINIT_ID                                                0x25 /**< ID for initializing the slave. */
#define FCIIC_SLAVELISTENING_ID                                           0x26 /**< ID for listening mode. */
#define FCIIC_SLAVEDEINIT_ID                                              0x27 /**< ID for deinitializing the slave. */
#define FCIIC_SLAVEDEINITHANDLE_ID                                        0x28 /**< ID for deinitializing the slave handle. */
#define FCIIC_SLAVEACK_ID                                                 0x29 /**< ID for acknowledging. */
#define FCIIC_SLAVECLRSTATUS_ID                                           0x2a /**< ID for clearing the status. */
#define FCIIC_SLAVEGETSTATUS_ID                                           0x2b /**< ID for getting the status. */
#define FCIIC_SLAVEENABLEINTERRUPT_ID                                     0x2c /**< ID for enabling interrupts. */
#define FCIIC_SLAVECHECKFORBUSYBUS_ID                                     0x2d /**< ID for checking the bus busy status. */
#define FCIIC_SLAVECHECKANDCLEARERROR_ID                                  0x2e /**< ID for checking and clearing errors. */
#define FCIIC_SLAVEGETDEFAULTCONFIG_ID                                    0x2f /**< ID for getting the default configuration. */
#define FCIIC_SLAVERECEIVE_ID                                             0x30 /**< ID for receiving data. */
#define FCIIC_SLAVEGETERROR_ID                                            0x31 /**< ID for getting the error. */
#define FCIIC_SLAVECLRERROR_ID                                            0x32 /**< ID for clearing the error. */
#define FCIIC_SLAVEGETDIR_ID                                              0x33 /**< ID for getting the direction. */
#define FCIIC_SLAVEINTERRUPTPROCESSADDRESSMATCH_ID                        0x34 /**< ID for processing address match interrupt. */
#define FCIIC_SLAVEINTERRUPTPROCESSRECEIVE_ID                             0x35 /**< ID for processing the receive interrupt. */
#define FCIIC_SLAVEINTERRUPTPROCESSTRANSMIT_ID                            0x36 /**< ID for processing the transmit interrupt. */
#define FCIIC_SLAVEINTERRUPTPROCESSSTOP_ID                                0x37 /**< ID for processing the stop interrupt. */
#define FCIIC_LL_SLAVEIRQNHANDLER_ID                                      0x38 /**< ID for the low-level slave IRQ handler. */
#define FCIIC_SLAVETRANSFERNONBLOCKING_ID                                 0x39 /**< ID for non-blocking transfer. */
#define FCIIC_SLAVEDMAPREPARE_ID                                          0x3a /**< ID for preparing DMA. */
#define FCIIC_SLAVETRANSFERDMA_ID                                         0x3b /**< ID for DMA transfer. */
#define FCIIC_SLAVEDMASTAGENOTIFICATION_ID                                0x3c /**< ID for DMA stage notification. */
#define FCIIC_SLAVESTARTDMA_ID                                            0x3d /**< ID for starting DMA. */
#define FCIIC_LL_SLAVEDMAIRQNHANDLER_ID                                   0x3e /**< ID for the low-level slave DMA IRQ handler. */

/** @}*/


/**
 * @def FCIIC_E_PARAM_NULLPTR
 * @brief Error code indicating a null pointer parameter.
 */
#define FCIIC_E_PARAM_NULLPTR     0x01U

/**
 * @def FCIIC_E_PARAM_INSTANCE
 * @brief Error code indicating an invalid instance parameter.
 */
#define FCIIC_E_PARAM_INSTANCE    0x02U

/**
 * @def FCIIC_E_PARAM_CHANNEL
 * @brief Error code indicating an invalid channel parameter.
 */
#define FCIIC_E_PARAM_CHANNEL     0x03U


/**
 * @def FCIIC_DIR_MASK
 * @brief Mask to extract the direction bit from the status register.
 */
#define FCIIC_DIR_MASK                         (0x1U)

/**
 * @def FCIIC_MASTER_CMD_SIZE
 * @brief Defines the size of the master command in bytes.
 */
#define FCIIC_MASTER_CMD_SIZE                  (0x8U)

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/**
 * @enum FCIIC_InstanceType
 * @brief Enumeration for selecting the FCIIC instance.
 */
typedef enum
{
    FCIIC_INSTANCE_0 = 0U,  /*!< FCIIC instance 0 is selected. Corresponds to the first available FCIIC module. */
    FCIIC_INSTANCE_1 = 1U   /*!< FCIIC instance 1 is selected. Corresponds to the second available FCIIC module. */
} FCIIC_InstanceType;


/**
 * @enum FCIIC_StatusType
 * @brief Enumerates the possible return status codes for FCIIC (Fast Communication Interface IC) operations.
 *
 * This enumeration defines the status values returned by FCIIC functions, indicating success or various errors
 * that can occur during communication. These codes provide information about the outcome of a particular operation.
 *
 * @note Check the specific function documentation for the meaning of each status code in the context of the operation performed.
 */
typedef enum
{
    FCIIC_SUCCESS = 0,          /**< Generic status for successful completion of an operation. */
    FCIIC_BUSY,                 /**< The FCIIC Master is already performing a transfer. */
    FCIIC_IDLE,                 /**< The FCIIC Slave driver is currently idle, no transfer is in progress. */
    FCIIC_NAK,                  /**< The slave device sent a Negative Acknowledge (NAK) in response to a byte. */
    FCIIC_FIFOERROR,            /**< FIFO underflow or overflow error occurred. */
    FCIIC_BITERROR,             /**< A transferred bit was not recognized on the bus. */
    FCIIC_TRAMSMITORRECEIVEERROR,/**< The slave device transmit or receive Error. */
    FCIIC_REPEATEDSTARTERROR,    /**< The FCIIC slave not detects a repeated START condition and if the FCIIC slave matched the last address byte,but should detect. */
    FCIIC_ADDRESSVALID,          /**< Indicates whether the Address Status Register is valid. */
    FCIIC_ARBITRATIONLOST,      /**< Lost arbitration during a transfer. */
    FCIIC_PINLOWTIMEOUT,        /**< SCL or SDA line was held low longer than the timeout period. */
    FCIIC_NOTRANSFERINPROGRESS, /**< Attempted to abort a transfer when none was in progress. */
    FCIIC_DMAREQUESTFAIL,       /**< DMA request failed to initiate or complete. */
    FCIIC_TIMEOUT,              /**< Timeout while polling for a status flag. */
    FCIIC_DIRECTIONERROR,      /**< Direction does not match the desired direction Error. */
    FCIIC_STATEMACHINEERROR,      /**< State machine error due to unknown error. */
    FCIIC_OVERFLOWERROR,          /**< The slave device transmit or receive byte number Error,Exceeding the maximum limit length. */
    FCIIC_SLAVEDMANUMBERERROR,   /**< The slave device  DMA transmit or receive byte number Error,The number of bytes transferred is less or more than the number required to trigger a DMA completion interrupt. */
    FCIIC_FAIL,                /**< parameter error or others. */
} FCIIC_StatusType;


/**
 * @enum FCIIC_MasterPinConfigType
 * @brief Specifies the pin configuration options for the FCIIC Master.
 *
 * This enumeration defines the pin configurations for the FCIIC Master interface, which can be set to either
 * open-drain mode or push-pull mode.
 */
typedef enum
{
    FCIIC_OPENDRAIN = 0x0U,  /**< FCIIC configured for 2-pin open-drain mode, suitable for standard and fast modes. */
    FCIIC_PUSHPULL  = 0x1U   /**< FCIIC configured for 2-pin output-only (push-pull) mode, typically used for ultra-fast mode. */
} FCIIC_MasterPinConfigType;


/**
 * @enum FCIIC_DirectionType
 * @brief Specifies the direction of data transfer for the FCIIC Master.
 *
 * This enumeration defines the direction of data transfer for the FCIIC Master, indicating whether the operation
 * is a write (transmit) or read (receive).
 */
typedef enum
{
    FCIIC_WRITE = 0U,  /**< Indicates a Master transmit operation, writing data to a slave. */
    FCIIC_READ  = 1U,  /**< Indicates a Master receive operation, reading data from a slave. */
    FCIIC_DIRNOCONFIG = 2U  /**< Indicates no configuration for direction. */
} FCIIC_DirectionType;

/**
 * @struct FCIIC_TxDataType
 * @brief Structure for holding transmit data for FCIIC operations.
 *
 * This structure contains the necessary fields to define a transmit command and its associated data.
 */
typedef struct
{
    FCIIC_TX_CMDType     eCmd;       /**< Command type. */
    uint8_t              u8Data;     /**< 8-bit data. */
} FCIIC_TxDataType;


/**
 * @struct FCIIC_RxDataType
 * @brief Structure for holding received data from FCIIC operations.
 *
 * This structure contains the field to store the received 8-bit data.
 */
typedef struct
{
    uint8_t              u8Data;     /**< 8-bit data. */
} FCIIC_RxDataType;

/**
 * @enum FCIIC_DmaStatusType
 * @brief Specifies the status of the DMA (Direct Memory Access) for FCIIC operations.
 *
 * This enumeration defines the different states of the DMA for FCIIC, indicating the current or next stage of the DMA process.
 */
typedef enum
{
    FCIIC_DMA_NO_CONFIG               = 0U,    /**< DMA mode is not configured. */
    FCIIC_DMA_NEXT_STAGE_IDLE         = 1U,    /**< DMA next stage is idle. */
    FCIIC_DMA_NEXT_STAGE_DATA         = 2U,    /**< DMA next stage is transmit/receive data. */
    FCIIC_DMA_NEXT_STAGE_STOP         = 3U,    /**< DMA next stage is transmit stop. */
    FCIIC_DMA_NEXT_STAGE_NOTIFICATION = 4U     /**< DMA next stage is notification to the user. */
} FCIIC_DmaStatusType;


/**
 * @enum FCIIC_ChannelStatusType
 * @brief Specifies the status of the FCIIC channel.
 *
 * This enumeration defines the different states of the FCIIC channel, indicating the current state of the channel during communication.
 */
typedef enum
{
    FCIIC_CH_IDLE           = 0U,   /**< I2C channel is idle. */
    FCIIC_CH_LISTENING_READ,        /**< I2C channel is listening for slave reading. */
    FCIIC_CH_LISTENING,       /**< I2C channel is listening for slave writing. */
    FCIIC_CH_START_READ,           /**< I2C channel will be reading for master. */
    FCIIC_CH_START_WRITE,           /**< I2C channel will be writing for master. */
    FCIIC_CH_SENDING,               /**< I2C channel is sending. */
    FCIIC_CH_RECEIVING,             /**< I2C channel is receiving. */
    FCIIC_CH_TRANSFER_FINISHED,      /**< I2C channel has finished transferring data. */
    FCIIC_CH_ERROR_PRESENT,         /**< I2C channel has an error present. */
    FCIIC_CH_CLOSED,                /**< I2C channel is closed. */
} FCIIC_ChannelStatusType;


/**
 * @struct FCIIC_MasterConfigType
 * @brief Structure for configuring the FCIIC Master.
 *
 * This structure contains the configuration parameters for setting up the FCIIC Master.
 */
typedef struct
{
    bool bEnableMaster;                    /**< Enables Master mode if set to true. */
    bool bDebugEnable;                     /**< Allows transfers to continue even when the debugger halts execution. */
    uint8_t u8SdaGlitchFilterWidth;        /**< Width of the SDA glitch filter in nanoseconds. Set to 0 to disable. */
    uint8_t u8SclGlitchFilterWidth;        /**< Width of the SCL glitch filter in nanoseconds. Set to 0 to disable. */
    FCIIC_MasterPinConfigType ePinConfig;  /**< Selects the pin configuration for the FCIIC pins. */
    uint8_t _aligned[3];                   /**< Populate Fields. */
    uint32_t u32BaudRate;                  /**< Target baud rate in Hz for the communication. */
    uint32_t u32BusIdleTimeout;            /**< Bus idle timeout in nanoseconds. Set to 0 to disable timeout. */
    uint32_t u32PinLowTimeout;             /**< Pin low timeout in nanoseconds. Set to 0 to disable timeout. */
} FCIIC_MasterConfigType;


/**
 * @brief Configuration structure for initializing the FCIIC (Fast Communication Interface IC) Slave module.
 *
 * This structure contains various settings to configure the FCIIC Slave module according to the desired operation.
 * Initialize this structure with default values by calling the FCIIC_SlaveGetDefaultConfig() function, then modify
 * the fields as needed.
 *
 * The structure can be declared const to store the configuration in flash memory to save RAM resources.
 */
typedef struct
{
    bool bEnableSlave;                   /*!< Enables Slave mode if set to true. */
    bool bI2cSlaveFilterEnable;          /*!< Enable or disable digital filter and output delay counter for slave mode.  */
    bool bUsedDMA;                       /*!< Enable DMA mode to transfer data. */
    bool bI2cSlaveAckStall;              /*!< Enable SCL clock stretching when SSR[AVF] = 1. */
    bool bI2cSlaveTxStall;               /*!< Enable SCL clock stretching when the SSR[TDF] = 1 during a slave-transmit transfer. */
    bool bI2cSlaveRxStall;               /*!< Enable SCL clock stretching when SSR[RDF] = 1 during a slave-receive transfer. */
    bool bI2cSlaveAdrStall;              /*!< Enables Slave mode if set to true. */
    uint8_t u8AddrCfg;                   /*!< Configure different address-matching strategies. */
    uint8_t u8SdaGlitchFilterWidth;      /*!< Width of the SDA glitch filter in nanoseconds. Set to 0 to disable. */
    uint8_t u8SclGlitchFilterWidth;      /*!< Width of the SCL glitch filter in nanoseconds. Set to 0 to disable. */
    uint8_t _aligned[4];                 /*!< Populate Fields. */
    uint16_t slaveAddress;               /*!< A slave address configuration. */
    uint32_t u32BusIdleTimeout;          /*!< Bus idle timeout in nanoseconds. Set to 0 to disable timeout. */
    uint32_t u32PinLowTimeout;           /*!< Pin low timeout in nanoseconds. Set to 0 to disable timeout. */
} FCIIC_SlaveConfigType;

/**
 * @struct FCIIC_MasterTransferType
 * @brief Structure for defining a master transfer in the FCIIC.
 *
 * This structure holds the configuration and data for a master transfer operation.
 */
typedef struct
{
    uint8_t u8SlaveAddress;             /**< The 7-bit slave address of the target device. */
    FCIIC_DirectionType eDirection;     /**< Transfer direction: either #FCIIC_WRITE or #FCIIC_READ. */
    uint16_t u16DataSize;                 /**< Total number of bytes to transfer. */
    uint8_t subaddressSize;             /**< Size of the sub-address in bytes. Maximum is 4 bytes. */
    uint32_t subaddress;                /**< Sub-address for targeted register. Sent most significant byte first. */
    uint8_t *pData;                     /**< Pointer to the buffer containing data to transfer or receive. */
} FCIIC_MasterTransferType;

/**
 * @struct FCIIC_SlaveTransferType
 * @brief Structure for defining a slave transfer in the FCIIC.
 *
 * This structure holds the configuration and data for a slave transfer operation.
 */
typedef struct
{
    uint8_t u8SlaveAddress;             /**< The 7-bit slave address of the target device. */
    uint8_t subaddressSize;             /**< Size of the sub-address in bytes. Maximum is 4 bytes. */
    uint16_t u16DataSize;               /**< Maximum length of bytes allowed to be transmitted,Avoiding array out-of-bounds*/
    uint8_t _aligned[4];                /**< Populate Fields. */
    uint32_t subaddress;                /**< Sub-address for targeted register. Sent most significant byte first.*/
    uint8_t *pData;                     /**< Transfer buffer,which the buffer must be a legitimate address. */
} FCIIC_SlaveTransferType;


/**
 * @brief Structure for configuring DMA for I2C Master and Slave operations.
 *
 * This structure holds the configuration for DMA operations in both I2C Master and Slave modes.
 */
typedef struct _FCIIC_DmaConfig
{
    FCIIC_DmaStatusType u8I2cDmaNextStage;                    /**< Represents the next stage of the IIC DMA state machine. */
    uint8_t _aligned[3];                                      /**< Populate Fields. */
    DMA_HandleType *pDmaHandle;                               /**< DMA_Handle which should be initialized before using. */
} FCIIC_DmaConfigType;

/**
 * @brief Structure for handling the FCIIC Master operations.
 * Implements : _FCIIC_MasterHandle
 *
 * This structure represents the handle for managing FCIIC Master operations, including the current state and settings.
 */
typedef struct _FCIIC_MasterHandle
{
    FCIIC_InstanceType eInstance;                            /**< I2C instance. */
    uint8_t _aligned[3];                                     /**< Populate Fields. */

    struct
    {
        bool bUsed;                                          /**< Whether it is being used. */
        FCIIC_DirectionType eDirection;                      /**< Master transfer direction. */
        uint8_t u8CmdSize;                                   /**< Master command data size, prepared for transfer. */
        uint8_t u8CmdOffset;                                 /**< Master had sent the data of size, prepared for transfer. */
        uint8_t u8DmaCmdSize;                                /**< Master had sent the command data of size, prepared for DMA transfer. */
        FCIIC_ChannelStatusType eChannelStatus;              /**< Master channel current state. */
        uint8_t u8DmaCmdOffset;                              /**< Master had sent the command data of size, prepared for DMA transfer. */
        uint16_t u16DataSize;                                  /**< Master will transfer the size of data. */
        uint16_t u16DataOffset;                                /**< Master had sent the command data of size. */
        uint8_t _aligned[7];                                 /**< Populate Fields. */
        uint16_t u16DmaCmdData[FCIIC_MASTER_CMD_SIZE];       /**< The Master command data, prepared for DMA transfer. */
        FCIIC_TX_CMDType u8Cmd[FCIIC_MASTER_CMD_SIZE];       /**< The Master data, prepared for Interrupt transfer. */
        uint8_t u8CmdData[FCIIC_MASTER_CMD_SIZE];            /**< The Master command data, prepared for Interrupt transfer. */
    } tStatus;                                               /**< The field of tStatus cannot be allowed modifying by the user. */

    struct
    {
        uint8_t *pData;                                      /**< Pointer to transfer data. */
        FCIIC_DmaConfigType *pFciicTxDmaConfig;              /**< DMA config instance used for sending. */
        FCIIC_DmaConfigType *pFciicRxDmaConfig;              /**< DMA config instance used for receiving. */
        void(*pCallback)(struct _FCIIC_MasterHandle *pFciicMasterHandle, FCIIC_StatusType status);          /**< Success callback function, can be designed when successfully transferred. */
        void(*pErrorCallback)(struct _FCIIC_MasterHandle *pFciicMasterHandle, FCIIC_StatusType status);     /**< Error callback function, would return the error state. */
        void *pUserData;                                     /**< User data. */
    } tSettings;                                             /**< The field of tSettings allows the user to set. */
} FCIIC_MasterHandleType;



/**
 * @brief Structure for handling the FCIIC Slave operations.
 * Implements : _FCIIC_SlaveHandle
 *
 * This structure represents the handle for managing FCIIC Slave operations, including the current state and settings.
 */
typedef struct _FCIIC_SlaveHandle
{
    FCIIC_InstanceType eInstance;                               /**< I2C instance. */
    uint8_t _aligned[3];                                        /**< Populate Fields. */

    struct
    {
        bool bUsed;                                             /**< Whether it is being used. */
        bool bIsGenRsf;                                        /**< Whether RSF signal is received. */
        FCIIC_StatusType eRunStatus;                            /**< This field records the errors encountered in a communication. */
        FCIIC_ChannelStatusType eChannelStatus;                 /**< salve channel current state. */
        uint8_t subaddressSize;                                /**< Size of the sub-address in bytes. Maximum is 4 bytes. */
        uint8_t curSubaddressSize;                             /**< Current received subaddress length. Maximum is 4 bytes. */
        uint16_t u16DataSize;                                     /**< The lengest length of data received or sent by the slave in a single communication. */
        uint16_t u16DataOffset;                                   /**< Slave had sent or received the  data of size. */
        uint32_t u32CurSubaddress;                               /**< Sub-address for targeted buffer address received from master. Sent most significant byte first.*/
        uint32_t u32Subaddress;                                  /**< Sub-address for targeted buffer address. Sent most significant byte first.*/
    } tStatus;                                                  /**< The field of tStatus cannot be allowed modifying by the user. */

    struct
    {
        uint8_t *pData;                                         /**< Pointer to transfer data. */
        FCIIC_DmaConfigType *pFciicTxDmaConfig;                 /**< DMA config instance used for sending. */
        FCIIC_DmaConfigType *pFciicRxDmaConfig;                 /**< DMA config instance used for receiving. */
        void(*pCallback)(struct _FCIIC_SlaveHandle *pFciicSlaveHandle);           /**< Success callback function, can be designed when successfully transferred. */
        void(*pErrorCallback)(struct _FCIIC_SlaveHandle *pFciicSlaveHandle);     /**< Error callback function, would return the error state. */
        void *pUserData;                                        /**< User data. */
    } tSettings;                                                /**< The field of tSettings allows the user to set. */
} FCIIC_SlaveHandleType;


/**
 * @typedef FCIIC_MasterTransfer_CallbackType
 * @brief Callback function type for master receive operations.
 *
 * This callback function is called when a master receive operation completes.
 *
 * @param pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param Status The status of the operation.
 */
typedef void (*FCIIC_MasterTransfer_CallbackType)(struct _FCIIC_MasterHandle *pFciicMasterHandle, FCIIC_StatusType Status);

/**
 * @typedef FCIIC_MasterError_CallBackType
 * @brief Callback function type for master error operations.
 *
 * This callback function is called when an error occurs during a master operation.
 *
 * @param pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param Status The status of the error.
 */
typedef void (*FCIIC_MasterError_CallBackType)(struct _FCIIC_MasterHandle *pFciicMasterHandle, FCIIC_StatusType Status);

/**
 * @typedef FCIIC_SlaveTransfer_CallbackType
 * @brief Callback function type for slave receive operations.
 *
 * This callback function is called when a slave receive operation completes.
 *
 * @param pFciicSlaveHandle Pointer to the FCIIC slave handle.
 */
typedef void (*FCIIC_SlaveTransfer_CallbackType)(struct _FCIIC_SlaveHandle *pFciicSlaveHandle);

/**
 * @typedef FCIIC_SlaveError_CallBackType
 * @brief Callback function type for slave error operations.
 *
 * This callback function is called when an error occurs during a slave operation.
 *
 * @param pFciicSlaveHandle Pointer to the FCIIC slave handle.
 */
typedef void (*FCIIC_SlaveError_CallBackType)(struct _FCIIC_SlaveHandle *pFciicSlaveHandle);

/**
 * @typedef FCIIC_RxInterrupt_CallBackType
 * @brief Callback function type for receive interrupt operations.
 *
 * This callback function is called when a receive interrupt occurs.
 *
 * @param pFciicSlaveHandle Pointer to the FCIIC slave handle.
 * @param status The status of the interrupt.
 */
typedef void (*FCIIC_RxInterrupt_CallBackType)(struct _FCIIC_SlaveHandle *pFciicSlaveHandle, FCIIC_StatusType status);

/**
 * @struct FCIIC_InterruptType
 * @brief Structure for configuring FCIIC interrupts.
 *
 * This structure holds the configuration for enabling and handling interrupts in the FCIIC.
 */
typedef struct
{
    uint8_t bEnErrorInterrupt;   /**< Enable error interrupt. */
    uint8_t bEnRxInterrupt;      /**< Enable receive interrupt. */
    uint8_t _aligned[6];         /**< Populate Fields. */
    FCIIC_SlaveError_CallBackType pErrorNotify;        /**< Error interrupt callback function address. */
    FCIIC_RxInterrupt_CallBackType pRxNotify;           /**< Receive interrupt callback function address. */
} FCIIC_InterruptType;


/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief Checks if the I2C bus is busy for the master.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC Master handle.
 *
 * @return FCIIC_StatusType Indicates whether the bus is busy or not.
 * @retval FCIIC_SUCCESS Bus is not busy.
 * @retval FCIIC_BUSY Bus is busy.
 */
FCIIC_StatusType FCIIC_MasterCheckForBusyBus(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Initializes a default configuration for the I2C master.
 *
 * This function sets up the default configuration parameters for the I2C master.
 *
 * @param[out] pMasterConfig Pointer to the structure where the default configuration will be stored.
 *
 * The following configurations are set:
 * - bEnableMaster: Enables the master functionality.
 * - bDebugEnable: Disables debug mode by default.
 * - ePinConfig: Sets the pin configuration to open-drain.
 * - u32BaudRate: Sets the baud rate to 100 kHz.
 * - u32BusIdleTimeout: Disables the bus idle timeout.
 * - u32PinLowTimeout: Disables the pin low timeout.
 * - u8SdaGlitchFilterWidth: Disables the SDA glitch filter.
 * - u8SclGlitchFilterWidth: Disables the SCL glitch filter.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
void FCIIC_MasterGetDefaultConfig(FCIIC_MasterConfigType *const pMasterConfig);

/**
 * @brief Sets the baud rate for the I2C master.
 *
 * This function calculates and sets the baud rate for the I2C master based on the given source clock frequency and desired baud rate.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] sourceClock_Hz The source clock frequency in Hz.
 * @param[in] baudRate_Hz The desired baud rate in Hz.
 *
 * The function performs the following steps:
 * - Calculates the optimal values for CLKHI, CLKLO, and PRESCALE to achieve the closest possible baud rate to the desired one.
 * - Configures the MCCR and MCFGR1 registers with the calculated values.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterSetBaudRate(FCIIC_MasterHandleType *const pFciicMasterHandle, uint32_t sourceClock_Hz, uint32_t baudRate_Hz);


/**
 * @brief Initializes the I2C master with the specified configuration.
 *
 * This function initializes the I2C master with the provided configuration and sets up the baud rate.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] pMasterConfig Pointer to the master configuration structure.
 * @param[in] sourceClock_Hz The source clock frequency in Hz.
 *
 * The function performs the following steps:
 * - Resets the I2C hardware.
 * - Sets the baud rate using the `FCIIC_MasterSetBaudRate` function.
 * - Configures the master control register (MCR); for debug enablement.
 * - Configures the master configuration registers (MCFGR1, MCFGR2, MCFGR3); for pin configuration, glitch filters, and timeouts.
 * - Enables the master operation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointers are null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterInit(FCIIC_MasterHandleType *const pFciicMasterHandle, const FCIIC_MasterConfigType *const pMasterConfig, uint32_t sourceClock_Hz);


/**
 * @brief Deinitializes the I2C master.
 *
 * This function deinitializes the I2C master by resetting it and clearing its configuration.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Resets the master control register (MCR); to disable the master, reset, and clear DMA and buffer flags.
 * - Disables DMA operations by setting the master DMA enable register (MDER);.
 * - Clears the pin configuration and glitch filter settings in the master configuration registers (MCFGR1, MCFGR2, MCFGR3);.
 * - Resets the I2C hardware.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
void FCIIC_MasterDeinit(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Initializes the I2C master handle.
 *
 * This function initializes the I2C master handle with the specified instance and clears its status and settings.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] eInstance The instance of the I2C master to initialize.
 *
 * The function performs the following steps:
 * - Sets the instance of the handle.
 * - Clears the status fields including command data, direction, channel status, and offsets.
 * - Sets callback functions and user data pointers to null.
 * - Initializes DMA-related settings to null or zero.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterInitHandle(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_InstanceType eInstance);

/**
 * @brief Enables interrupt handling for the I2C master.
 *
 * This function sets the callback functions and user data for interrupt handling in the I2C master.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] pCallback Pointer to the transfer callback function.
 * @param[in] pErrorCallback Pointer to the error callback function.
 * @param[in] pUserData User-defined data to be passed to the callback functions.
 *
 * The function performs the following steps:
 * - Sets the transfer callback, error callback, and user data pointers in the handle's settings.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
void FCIIC_MasterEnableInterrupt(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransfer_CallbackType pCallback, FCIIC_MasterError_CallBackType pErrorCallback,
                                 void *pUserData);

/**
 * @brief Checks and clears errors in the I2C master.
 *
 * This function checks for specific error conditions in the I2C master and clears them if present.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] status The status flags to check and clear.
 *
 * @return FCIIC_StatusType The error status or FCIIC_SUCCESS if no errors were detected.
 *
 * The function performs the following steps:
 * - Checks the status flags against known error conditions.
 * - Selects the appropriate error code based on the severity and type of error.
 * - Clears the error flags in the I2C hardware.
 * - Resets the FIFOs if necessary.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterCheckAndClearError(FCIIC_MasterHandleType *const pFciicMasterHandle, uint32_t status);


/**
 * @brief Waits for a specific flag to be set in the I2C master.
 *
 * This function waits for a given flag to be set in the I2C master status and returns the result.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] u32Flag The flag to wait for.
 *
 * @return FCIIC_StatusType The status indicating success or timeout.
 *
 * The function performs the following steps:
 * - Waits for the specified flag to be set within a certain number of attempts.
 * - Returns FCIIC_SUCCESS if the flag is set, or FCIIC_TIMEOUT if the flag is not set within the timeout period.
 * - Checks and clears any errors that may have occurred during the wait.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterWaitFlag(FCIIC_MasterHandleType *const pFciicMasterHandle, uint32_t u32Flag);


/**
 * @brief Initiates an I2C start condition.
 *
 * This function initiates an I2C start condition and sends the device address along with the read/write direction.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] address The 7-bit I2C address of the target device.
 * @param[in] dir The direction of the communication (read or write);.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Checks if the bus is busy before starting.
 * - Clears all relevant flags in the I2C hardware.
 * - Sends a start condition followed by the address and direction.
 * - Waits for the transmission done flag to be set.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterStart(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8_t address, FCIIC_DirectionType dir);


/**
 * @brief Initiates an I2C repeated start condition.
 *
 * This function initiates an I2C repeated start condition and sends the device address along with the read/write direction.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] address The 7-bit I2C address of the target device.
 * @param[in] dir The direction of the communication (read or write);.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Sends a repeated start condition followed by the address and direction.
 * - Waits for the transmission done flag to be set.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterRepeatedStart(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8_t address, FCIIC_DirectionType dir);


/**
 * @brief Sends a sequence of commands in the I2C master.
 *
 * This function sends a sequence of commands and data to the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Iterates through each command in the command buffer.
 * - Sends the command and corresponding data.
 * - Waits for the transmission done flag to be set for each command.
 * - Increments the command offset after each successful transmission.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterSendStartCommand(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Sends data over the I2C bus.
 *
 * This function sends a block of data over the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] txBuff Pointer to the transmit buffer containing the data to send.
 * @param[in] txSize The size of the data to send in bytes.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Iterates through each byte in the transmit buffer.
 * - Sends the byte over the I2C bus.
 * - Waits for the transmission done flag to be set for each byte.
 * - Increments the data offset after each successful transmission.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterSend(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8 *txBuff, uint16 txSize);


/**
 * @brief Receives data over the I2C bus.
 *
 * This function receives a block of data over the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Iterates through each byte of the receive buffer.
 * - Waits for the receive data flag to be set.
 * - Reads the received byte from the I2C bus.
 * - Stores the received byte in the receive buffer.
 * - Increments the data offset after each successful reception.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterReceive(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Sends a stop condition over the I2C bus.
 *
 * This function sends a stop condition over the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Sends a stop condition over the I2C bus.
 * - Waits for the transmission done flag to be set.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterStop(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Aborts an ongoing I2C transfer.
 *
 * This function aborts an ongoing I2C transfer by disabling interrupts, resetting the FIFO, and marking the handle as unused.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Disables interrupts for the I2C master.
 * - Resets the FIFO.
 * - Marks the handle as unused.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterTransferAbort(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Sets the receive length for an ongoing I2C transfer.
 *
 * This function sets the number of bytes to receive during an ongoing I2C transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] u8Len The number of bytes to receive.
 *
 * @return uint8_t Returns 1 if the receive length was successfully set, otherwise 0.
 *
 * The function performs the following steps:
 * - Checks if the transmit count is less than 8.
 * - If the condition is met, sends a receive command with the specified length minus one.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
uint8_t FCIIC_MasterSetReceiveLen(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8 u8Len);

/**
 * @brief Transmits data over the I2C bus.
 *
 * This function transmits data over the I2C bus if the transmission data flag is set.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] pTxData Pointer to the transmit data structure containing the command and data to send.
 *
 * @return uint8_t Returns 1 if the transmission was initiated, otherwise 0.
 *
 * The function performs the following steps:
 * - Clears any error flags.
 * - Checks the transmission data flag.
 * - If the flag is set, sends the command and data.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointers are null and report an error accordingly. It also checks if the instance is valid.
 */
uint8_t FCIIC_MasterTransmit(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_TxDataType *pTxData);


/**
 * @brief Gets the status of the I2C master.
 *
 * This function retrieves the status of the I2C master based on the specified status type.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] eStatus The status type to retrieve.
 *
 * @return uint8_t Returns the status value as a bit mask.
 *
 * The function performs the following steps:
 * - Retrieves the status based on the specified status type.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
uint8_t FCIIC_MasterGetStatus(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterStatusType eStatus);

/**
 * @brief Clears the status flags of the I2C master.
 *
 * This function clears specific status flags of the I2C master.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Clears the data match flag, protocol error flag, FIFO error flag, address lost flag,
 *   not data flag, start detection flag, and end packet flag.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterClrStatus(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Performs a blocking I2C transfer.
 *
 * This function performs a blocking I2C transfer, which includes sending commands and data, and handling the transfer completion or errors.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] transfer Pointer to the I2C transfer parameters.
 *
 * @return FCIIC_StatusType Returns the status of the transfer operation.
 *
 * The function performs the following steps:
 * - Checks if the bus is busy or the handle is already in use.
 * - Clears the status flags.
 * - Initializes the handle's status fields.
 * - Generates and sends the start command.
 * - Sends or receives data based on the direction.
 * - Sends a stop signal after the data transfer.
 * - Calls the callback function upon successful transfer completion.
 * - Calls the error callback function if an error occurs during the transfer.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointers are null and report an error accordingly.
 */
FCIIC_StatusType FCIIC_MasterTransferBlocking(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer);

/**
 * @brief Prepares the DMA channel for I2C master transfer.
 *
 * This function prepares the DMA channel for data transfer by configuring the DMA attributes and starting the DMA transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Configures the DMA channel attributes based on the transfer direction (read/write);.
 * - Sets up the DMA source and destination buffers, block size, and other settings.
 * - Starts the DMA transfer.
 * - Updates the channel status based on the transfer direction.
 * - Calls the error callback function if an error occurs during preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterDmaPrepare(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Stops the DMA transfer for the I2C master.
 *
 * This function stops the DMA transfer by preparing a stop command and updating the DMA configuration.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Sets up the stop command in the DMA command buffer.
 * - Prepares the DMA for the stop command.
 * - Updates the channel status to indicate the transfer has been stopped.
 * - Adjusts the next DMA stage based on the transfer direction.
 * - Calls the error callback function if an error occurs during the preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterDmaStop(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Initiates a DMA transmit operation for the I2C master.
 *
 * This function initiates the DMA transmit operation by preparing the DMA for transmission and setting the next DMA stage to stop.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Prepares the DMA for the transmit operation.
 * - Sets the next DMA stage to stop after the transmission.
 * - Calls the error callback function if an error occurs during preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void  FCIIC_MasterDmaTransmit(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Initiates a DMA receive operation for the I2C master.
 *
 * This function initiates the DMA receive operation by preparing the DMA for reception and setting the next DMA stage to stop.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Prepares the DMA for the receive operation.
 * - Sets the next DMA stage to stop after the reception.
 * - Calls the error callback function if an error occurs during preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void  FCIIC_MasterDmaReceive(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Starts the DMA transfer for the FCIIC master.
 *
 * This function initializes the DMA command sequence based on the given transfer parameters.
 * It checks for valid input parameters and then prepares the DMA commands to be sent.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle structure.
 * @param[in] transfer Pointer to the FCIIC master transfer structure containing transfer details.
 */
void  FCIIC_MasterDmaStart(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer);


/**
 * @brief Handles the notification stage after a DMA transmission.
 *
 * This function updates the channel status and triggers a callback if one is registered.
 * It also manages the next stage of DMA operations based on the direction of the transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterDmaStageNotification(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Handles the data stage of a DMA transmission.
 *
 * This function updates the channel status and triggers the data transfer phase
 * based on the current state and direction of the transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterDmaStageData(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief DMA interrupt handler for the FCIIC master.
 *
 * This function handles DMA interrupts by determining the next stage of the DMA operation,
 * updating the channel status, and managing error conditions.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_LL_MasterDmaIRQnHandler(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Initiates a DMA transfer for the FCIIC master.
 *
 * This function starts a DMA transfer by configuring the DMA settings and initiating the transfer process.
 * It checks for valid parameters, ensures the bus is not busy, and configures the DMA accordingly.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] transfer Pointer to the FCIIC master transfer structure containing transfer details.
 *
 * @return FCIIC_StatusType The status of the DMA transfer initiation.
 */
FCIIC_StatusType FCIIC_MasterDmaTransfer(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer);


/**
 * @brief Stops the interrupt process for the FCIIC master.
 *
 * This function disables all interrupts, updates the channel status, and triggers a callback if the data transfer is complete.
 * It also handles error conditions if the data offset does not match the expected size.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessStop(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Processes the transmit phase in interrupt mode for the FCIIC master.
 *
 * This function transmits data and updates the data offset. It stops the transfer and updates the channel status when the data transfer is complete.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessTransmit(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Processes the receive phase in interrupt mode for the FCIIC master.
 *
 * This function receives data and updates the data offset. It stops the transfer and updates the channel status when the data reception is complete.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessReceive(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Processes the start phase in interrupt mode for the FCIIC master.
 *
 * This function manages the command transmission and updates the command offset. It transitions the channel status based on the current phase of the transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessStart(FCIIC_MasterHandleType *const pFciicMasterHandle);


/**
 * @brief Handles the interrupt for the FCIIC master.
 *
 * This function processes various interrupt sources and updates the state of the transfer based on the current channel status.
 * It also handles errors and calls appropriate callbacks.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_LL_MasterIRQnHandler(FCIIC_MasterHandleType *const pFciicMasterHandle);

/**
 * @brief Generates a start command for the FCIIC Master.
 *
 * This function initializes the master for transmission by generating the necessary commands for the start of a transfer.
 *
 * @param[in] pFciicMasterHandle The FCIIC Master Handle.
 * @param[in] transfer Pointer to the `FCIIC_MasterTransferType` structure containing the transfer details.
 * @return void
 */
void FCIIC_MasterGenerateStartCommand(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer);

/**
 * @brief Initiates a non-blocking I2C Master transfer.
 *
 * Sets up and initiates a non-blocking I2C Master transfer, including handling of START, addressing, subaddress (if provided);,
 * data transfer, and STOP conditions. Returns immediately after starting the transfer, and the transfer is managed asynchronously
 * using interrupts.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC Master Handle.
 * @param[in] transfer Pointer to the `FCIIC_MasterTransferType` structure containing the transfer details.
 * @return A status code indicating the outcome of the initiation process:
 *         - FCIIC_SUCCESS: The transfer was initiated successfully.
 *         - FCIIC_BSY: Another non-blocking transfer is already in progress.
 *         - Other error codes: Errors encountered during the transfer setup, such as a busy bus.
 */
FCIIC_StatusType FCIIC_MasterTransferNonBlocking(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer);

/**
 * @brief Initializes the I2C Slave mode.
 *
 * Configures the I2C interface for slave mode operation according to the parameters provided.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave Handle.
 * @param[in] pInitReg Pointer to the `FCIIC_SlaveConfigType` structure containing the initialization settings.
 * @return void
 */
void FCIIC_SlaveInit(FCIIC_SlaveHandleType *const pFciicSlaveHandle,  const FCIIC_SlaveConfigType *pInitReg);

/**
 * @brief De-initializes the IIC Slave mode.
 *
 * This function de-initializes the IIC Slave mode by resetting the handle and disabling the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the slave handle structure.
 * @param[in] transfer Pointer to the I2C transfer parameters.
 *
 * @return FCIIC_StatusType indicating the status of the operation.
 */
FCIIC_StatusType FCIIC_Slavelistening(FCIIC_SlaveHandleType *const pFciicSlaveHandle, FCIIC_SlaveTransferType *const transfer);

/**
 * @brief Deinitializes the FCIIC slave configuration.
 *
 * This function resets the FCIIC slave peripheral to its default state.
 * It disables the FCIIC slave, clears all registers, and disables interrupts.
 *
 * @param pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveDeInit(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Deinitializes the FCIIC slave handle.
 *
 * This function resets the FCIIC slave handle to its default state.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveDeinitHandle(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Sends an ACK/NACK signal in IIC Slave mode.
 *
 * This function sends an ACK or NACK signal based on the input parameter.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] bAck Boolean flag to indicate whether to send ACK (true); or NACK (false);.
 */
void  FCIIC_SlaveAck(FCIIC_SlaveHandleType *const pFciicSlaveHandle, boolean bAck);

/**
 * @brief Clears the I2C master status flag state.
 *
 * This function clears the status flags of the I2C master.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveClrStatus(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Gets the slave SSR status.
 *
 * This function retrieves the current status of the slave SSR register.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return The current SSR status as a 32-bit unsigned integer.
 */
uint32_t FCIIC_SlaveGetStatus(FCIIC_SlaveHandleType *const pFciicSlaveHandle);


/**
 * @brief Enables the interrupt for the specified FCIIC Slave instance.
 *
 * This function configures the interrupt system to handle non-blocking transfers for the given FCIIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] pCallback Pointer to a callback function that will be invoked when a non-blocking transfer completes.
 * @param[in] pErrorCallBack Pointer to a callback function that will be invoked when an error occurs.
 * @param[in] pUserData Pointer to user-defined data that will be passed back to the callback function when it is called.
 */
void FCIIC_SlaveEnableInterrupt(FCIIC_SlaveHandleType *const pFciicSlaveHandle,
                                FCIIC_SlaveTransfer_CallbackType pCallback, FCIIC_SlaveError_CallBackType pErrorCallBack, void *pUserData);


/**
 * @brief Checks if the FCIIC bus is busy.
 *
 * This function determines if the FCIIC bus is currently busy.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return FCIIC_StatusType indicating the bus status.
 */
FCIIC_StatusType FCIIC_SlaveCheckForBusyBus(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Checks for and clears I2C Slave errors.
 *
 * This function checks the provided status register for any I2C Slave errors and clears them.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] status The current status register value.
 *
 * @return FCIIC_StatusType indicating the encountered error or FCIIC_SUCCESS if no error is found.
 */
FCIIC_StatusType FCIIC_SlaveCheckAndClearError(FCIIC_SlaveHandleType *const pFciicSlaveHandle, uint32_t status);


/**
 * @brief Sets the default configuration for the I2C Slave.
 *
 * This function sets the default configuration parameters for the I2C Slave.
 *
 * @param[in] slaveConfig Pointer to the configuration structure.
 * @param[in] bUsedDMA Boolean flag indicating whether DMA is used.
 */
void FCIIC_SlaveGetDefaultConfig(FCIIC_SlaveConfigType *const slaveConfig, boolean bUsedDMA);

/**
 * @brief Receives data in IIC Slave mode.
 *
 * This function receives data when polling (not used when RX interrupt is enabled); in Slave mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[out] pData Pointer to the data buffer where the received data will be stored.
 *
 * @return 0 if successful, non-zero otherwise.
 */
uint8_t FCIIC_SlaveReceive(FCIIC_SlaveHandleType *const pFciicSlaveHandle, uint8_t *pData);

/**
 * @brief Gets the slave error value.
 *
 * This function retrieves the current error value of the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return The current error value as a 32-bit unsigned integer.
 */
uint32_t FCIIC_SlaveGetError(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Clears the slave error value.
 *
 * This function clears the error value of the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveClrError(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Gets the current direction of the slave.
 *
 * This function retrieves the current direction (read/write); of the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return The current direction as an FCIIC_DirectionType enum value.
 */
FCIIC_DirectionType FCIIC_SlaveGetDir(FCIIC_SlaveHandleType *const pFciicSlaveHandle);


/**
 * @brief Processes the IIC Slave AM0F interrupt.
 *
 * This function processes the Address Match 0 Flag interrupt for the IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] u32IsrStatus    The status of the SSR flags.
 */
void FCIIC_SlaveInterruptProcessAddressMatch(FCIIC_SlaveHandleType *const pFciicSlaveHandle,uint32 u32IsrStatus);

/**
 * @brief Processes the IIC Slave RDF interrupt.
 *
 * This function processes the Receive Data Flag interrupt for the IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveInterruptProcessReceive(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Processes IIC Slave TDF interrupt.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveInterruptProcessTransmit(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Processes IIC Slave SDF interrupt.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveInterruptProcessStop(FCIIC_SlaveHandleType *const pFciicSlaveHandle);


/**
 * @brief I2C Slave Interrupt Service Routine (ISR);.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_LL_SlaveIRQnHandler(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Starts accepting slave transfers in non-blocking mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 *
 * @return FCIIC_StatusType Status indicating whether the start was successful.
 */
FCIIC_StatusType FCIIC_SlaveTransferNonBlocking(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Prepares DMA configuration for IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */

void FCIIC_SlaveDmaPrepare(FCIIC_SlaveHandleType *const pFciicSlaveHandle);


/**
 * @brief Initiates an IIC Slave Asynchronous DMA transfer.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 *
 * @return FCIIC_StatusType Status indicating whether the DMA transfer was successful.
 */
FCIIC_StatusType FCIIC_SlaveTransferDMA(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief Starts DMA for IIC Slave in asynchronous mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveDMAStageNotification(FCIIC_SlaveHandleType *const pFciicSlaveHandle);


/**
 * @brief Starts DMA for IIC Slave in asynchronous mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveStartDMA(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

/**
 * @brief DMA handler for IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_LL_SlaveDmaIRQnHandler(FCIIC_SlaveHandleType *const pFciicSlaveHandle);

#if defined(__cplusplus)
}
#endif

/** @}*/
#endif

#endif
