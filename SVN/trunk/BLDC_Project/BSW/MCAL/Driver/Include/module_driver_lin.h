/**
 * @file module_driver_lin.h
 * @author Flagchip
 * @brief LIN driver type definition and API
 * @version 2.0.0
 * @date 2024-08-23
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-08-23    Flagchip122   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_LIN_H_
#define _DRIVER_MODULE_DRIVER_LIN_H_

#include "HwA_fcuart.h"

#if FCUART_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_lin
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  LIN API Service IDs
 * @brief Defines the service IDs for the LIN API
 * @{
 */
#define LIN_INIT_ID                             0U          /**< Init LIN instance */
#define LIN_DEINIT_ID                           1U          /**< Deinit LIN instance */
#define LIN_GET_DEFAULT_CFG_ID                  2U          /**< Get default LIN configuration */
#define LIN_DRV_START_ID                        3U          /**< Start LIN instance */
#define LIN_DRV_SEND_HEADER_ID                  4U          /**< Send LIN header */
#define LIN_DRV_INSTALL_UAER_CALLBACK_ID        5U          /**< Install LIN user callback */
#define LIN_DRV_SEND_FRAME_BLOCKING             6U          /**< Send LIN frame blocking */
#define LIN_DRV_SEND_FRAME_NON_BLOCKING         7U          /**< Send LIN frame non blocking */
#define LIN_DRV_GET_TRANSMIT_STATUS             8U          /**< Get LIN transmit status */
#define LIN_DRV_RECEIVE_FRAME_BLOCKING          9U          /**< Receive LIN frame blocking */
#define LIN_DRV_RECEIVE_FRAME_NON_BLOCKING      10U         /**< Receive LIN frame non blocking */
#define LIN_DRV_GET_RECEIVE_STATUS              11U         /**< Get LIN receive status */
#define LIN_DRV_ABORT_TRANSFER                  12U         /**< Abort LIN transfer */
#define LIN_DRV_GOTOSLEEP_MODE                  13U         /**< Go to sleep mode */
#define LIN_DRV_GOTOIDLE_MODE                   14U         /**< Go to idle mode */
#define LIN_DRV_SEND_WAKEUP_SIGNAL              15U         /**< Send wakeup signal */
#define LIN_DRV_GET_NODE_STATE                  16U         /**< Get LIN node state */
#define LIN_DRV_TIMEOUT_SERVICE                 17U         /**< Timeout service */
#define LIN_DRV_SET_TIMEOUT_COUNTER             18U         /**< Set timeout counter */
#define LIN_DRV_GET_TIMEOUT_FLAG                19U         /**< Get timeout flag */
#define LIN_DRV_IRQ_HANDLE                      20U         /**< Interrupt handle */
/** @}*/

/**
 * @name  LIN Dev Error Code
 * @brief Error Code of calling LIN apis
 * @{
 */
#define LIN_E_PARAM_INSTANCE               0x01U    /**< Invalid LIN instance */
#define LIN_E_PARAM_ERROR_STATE            0x02U    /**< Invalid LIN error state */
#define LIN_E_PARAM_POINTER                0x03U    /**< Invalid LIN parameter pointer */
/** @}*/

/** @brief Defines the LIN bus interface handle type */
typedef struct _LIN_HandleType LIN_tHandleType;

/**
 * @brief Define the enumeration for LIN controller instances to identify different LIN controller instances.
 */
typedef enum
{
    LIN_INSTANCE_0 = 0U,     /**< LIN instance 0 */
    LIN_INSTANCE_1,          /**< LIN instance 1 */
    LIN_INSTANCE_2,          /**< LIN instance 2 */
    LIN_INSTANCE_3,          /**< LIN instance 3 */
    LIN_INSTANCE_4,          /**< LIN instance 4 */
    LIN_INSTANCE_5,          /**< LIN instance 5 */
} LIN_InstanceType;

/**
 * @brief LIN status type use in API.
 */
typedef enum
{
    LIN_STATUS_SUCCESS = 0x00U, /**< API execute successfully */
    LIN_STATUS_ERROR,           /**< API excute error */
    LIN_STATUS_BUSY,            /**< currently instance busy. */
    LIN_STATUS_TIMEOUT,         /**< timeout status */
    LIN_STATUS_PARAM_ERROR,     /**< Parameter error. */
    LIN_STATUS_NOT_INIT,        /**< LIN node has not been initialized. */
    LIN_STATUS_USEED,           /**< LIN node has not been initialized. */
    LIN_STATUS_NOT_START,       /**< LIN node has not been started. */
    LIN_STATUS_UNSUPPORTED,     /**< unsupport status */
} LIN_StatusType;

/**
 * @brief LIN node type use in API, master or slave.
 */
typedef enum
{
    LIN_NODE_MASTER, /**< LIN Master node. */
    LIN_NODE_SLAVE,  /**< LIN slave node. */
} LIN_NodeType;

/**
 * @brief Types for an event related Identifier.
 */
typedef enum
{
    LIN_NO_EVENT = 0x00U,    /**< No event occurred. */
    LIN_WAKEUP_SIGNAL,       /**< Wakeup signal */
    LIN_BAUDRATE_ADJUSTED,   /**< Baudrate was adjusted in slave autobaud mode. */
    LIN_RECV_BREAK_FIELD_OK, /**< Break Field was received */
    LIN_SYNC_OK,             /**< Sync field is correct */
    LIN_SYNC_ERROR,          /**< Sync field is incorrect */
    LIN_PID_OK,              /**< PID receive correct */
    LIN_PID_ERROR,           /**< PID receive incorrect */
    LIN_FRAME_ERROR,         /**< Frame receive error */
    LIN_READBACK_ERROR,      /**< Readback words are incorrect */
    LIN_CHECKSUM_ERROR,      /**< Checksum byte error */
    LIN_TX_COMPLETED,        /**< TX data completed */
    LIN_RX_COMPLETED,        /**< rx data completed */
    LIN_RX_OVERRUN,          /**< RX overflow occurred */
    LIN_TIMEOUT,             /**< RX overflow occurred */
} lin_event_id_t;

/**
 * @brief Define type for an enumerating LIN Node state.
 */
typedef enum
{
    LIN_NODE_STATE_UNINIT = 0x00U,      /**< LIN hardware uninitialized state */
    LIN_NODE_STATE_SLEEP_MODE,          /**< LIN node in sleep mode state */
    LIN_NODE_STATE_IDLE,                /**< LIN node in idle state */
    LIN_NODE_STATE_SEND_BREAK_FIELD,    /**< LIN node in send break field state */
    LIN_NODE_STATE_RECV_SYNC,           /**< LIN node in receive the synchronization byte state */
    LIN_NODE_STATE_SEND_PID,            /**< LIN node in rend PID state */
    LIN_NODE_STATE_RECV_PID,            /**< LIN node in receive PID state */
    LIN_NODE_STATE_RECV_DATA,           /**< LIN node in receive data state */
    LIN_NODE_STATE_RECV_DATA_COMPLETED, /**< LIN node in receive data completed state */
    LIN_NODE_STATE_SEND_DATA,           /**< LIN node in send data state */
    LIN_NODE_STATE_SEND_DATA_COMPLETED  /**< LIN node in send data completed state */
} lin_node_state_t;

/**
 * @brief A callback function to get the interval time value in nanoseconds.
 */
typedef uint32_t (*lin_get_interval_time_t)(uint32_t *nanoSeconds);

/**
 * @brief LIN Driver callback function type
 */
typedef void (*lin_callback_t)(LIN_tHandleType *pLinHandle, void *linState);

/**
 * @brief Runtime state of the LIN driver.
 *
 * Note that the caller provides memory for the driver state structures during
 * initialization because the driver does not statically allocate memory.
 */
typedef struct
{
    volatile uint32_t         timeoutCounter;     /**< Value of the timeout counter */
    lin_callback_t            Callback;           /**< Callback function to invoke after receiving a byte or transmitting a byte. */
    const uint8_t *           txBuff;             /**< The buffer of data being sent. */
    uint8_t *                 rxBuff;             /**< The buffer of received data. */
    volatile lin_event_id_t   currentEventId;     /**< Current ID Event */
    volatile lin_node_state_t currentNodeState;   /**< Current Node state */
    uint8_t                   cntByte;            /**< To count number of bytes already transmitted or received. */
    volatile uint8_t          txSize;             /**< The remaining number of bytes to be transmitted. */
    volatile uint8_t          rxSize;             /**< The remaining number of bytes to be received. */
    uint8_t                   checkSum;           /**< Checksum byte. */
    uint8_t                   currentId;          /**< Current ID */
    uint8_t                   currentPid;         /**< Current PID */
    volatile bool             isTxBusy;           /**< True if the LIN interface is transmitting frame data. */
    volatile bool             isRxBusy;           /**< True if the LIN interface is receiving frame data. */
    volatile bool             isBusBusy;          /**< True if there are data, frame headers being transferred on bus */
    volatile bool             isTxBlocking;       /**< True if transmit is blocking transaction. */
    volatile bool             isRxBlocking;       /**< True if receive is blocking transaction. */
    volatile bool             timeoutCounterFlag; /**< Timeout counter flag */
    uint8_t                   _aligned[2];
} lin_xfer_state_t;

/**
 * @brief Structure for LIN hardware configurations.
 */
typedef struct
{
    lin_xfer_state_t        g_xferState;                  /**< Runtime state of the LIN driver */
    uint32_t                baudRate;                     /**< baudrate configurations for LIN protocol. */
    uint32_t                clockSrcFreq;                 /**< LIN instance clock source frequency. */
    uint8_t *               classicPID;                   /**< List of PIDs use classic checksum */
    lin_get_interval_time_t getIntervalTimeValueCallback; /**< Callback function to get time interval in nanoseconds */
    LIN_NodeType            nodeMode;                     /**< Node mode as Master node or Slave node. 0: slave 1: master */
    uint8_t                 u8LinIndex;                   /**<index of Lin instance */
    uint8_t                 numOfClassicPID;              /**< Number of PIDs use classic checksum */
    uint8_t                 _aligned;
} lin_config_t;

/**
 * @brief The structure of the LIN processing handle
 *
 */
typedef struct _LIN_HandleType
{
    LIN_InstanceType eInstance;        /**< The LIN instance identifier, specifying the particular LIN controller. */
    uint8_t _aligned[3];               /**< Alignment bytes for hardware address alignment. */
    struct
    {
        lin_xfer_state_t        *pLinXfer;   /**< Pointer to the LIN transfer state. */
        lin_config_t            *pLinConfig; /**< Pointer to the LIN configuration structure. */
        uint8_t                 u8InstanceUsed; /**< Indicates if the instance is in use. */
    } tStatus;
} LIN_HandleType;

/**
 * @name    API declaration for LIN driver.
 * @brief   LIN driver APIs
 * @{
 */

/**
 * @brief Init the LIN instance for LIN network. This API will help initialize the FCUART to expect state,
 *        but will nots start the TX&RX function, if users want to start the LIN protocol transfer, please
 *        call the function LIN_DrvStart() after this API is called.
 *
 * @param pLinHandle    LIN processing handle
 * @param pConfig     Configuration for LIN hardware, must not be null.
 * @return operation status:
 *         - LIN_STATUS_SUCCESS  : operation is successfully.
 *         - LIN_STATUS_USEED    : The instance has been used, user should use another instance or de-initialize this instance firstly.
 *         - LIN_STATUS_ERROR    : the baudrate has not been set successfully.
 */
LIN_StatusType LIN_DrvInit(LIN_HandleType *pLinHandle, lin_config_t *pConfig);

/**
 * @brief De-Init the LIN instance used by LIN network.
 *        This API will help disable the fcuart interrupts and stop the TX/RX transfer.
 * @param pLinHandle    LIN processing handle
 * @return operation status:
 *         - LIN_STATUS_SUCCESS  : operation is successfully.
 *         - LIN_STATUS_NOT_INIT : The instance has not been initialized.
 */
void LIN_DrvDeInit(LIN_HandleType *pLinHandle);

/**
 * @brief Help users get the default configuration of LIN node. users should provide the configuration structure
 *        in app code, and transfer the ptr address to driver code. uses can also set this parameters in the application code
 *        as designed.
 *
 * @param eNodeMode  LIN node mode select, 0 for slave mode and 1 for master mode.
 * @param pConfig     default configuration for LIN node, must not be null.
 */
void LIN_DrvGetDefaultConfig(LIN_NodeType eNodeMode, lin_config_t *pConfig);

/**
 * @brief Start LIN node transfer, this API should be called after LIN hardware has been initialized, and must
 *        be called before starting a LIN node transfer. Users should provide a tansfer structure for storing the
 *        transfer state, ant LIN node state changed will be stored to this xfer state.
 *
 * @param pLinHandle    LIN processing handle
 * @param pXferState  Transfer state structure which will help store the trasnfer state.
 * @return operation status:
 *         - LIN_STATUS_SUCCESS    : operation is successfully.
 *         - LIN_STATUS_PARAM_ERROR: the parameter setting maybe not correct, maybe instance has bot been initialized.
 */
void LIN_DrvStart(LIN_HandleType *pLinHandle, lin_xfer_state_t *pXferState);

/**
 * @brief This function will help install callback function that used by application code.
 *        users can handle some needed operations in driver code or get some important states.
 *        or uses can also setting this in transfer state structure.
 *
 * @param pLinHandle    LIN processing handle
 * @param callback    user's callbak function that need be called in driver code.
 * @return operation status:
 *         - LIN_STATUS_SUCCESS    : operation is successfully.
 *         - LIN_STATUS_NOT_INIT   : The instance required has bot been initialized.
 */
LIN_StatusType LIN_DrvInstallUserCallback(LIN_HandleType *pLinHandle, lin_callback_t callback);

/**
 * @brief This function will help users send a header in master node which will help start a new
 *        frame transfer. please do not used this API will LIN instance is configured as slave node.
 *        This API will make a parity ID, and only send a break field to the protocol, all the other
 *        filed like sync filed and pid byte will be handled in FCUART IRQHandler. more details can
 *        refer to IRQ routine.
 *
 * @param pLinHandle    LIN processing handle
 * @param u8Id        The ID data that useds need to send in header.
 * @return operation status:
 *         - LIN_STATUS_SUCCESS     : operation is successfully.
 *         - LIN_STATUS_NOT_INIT    : Instance required has not been intialized.
 *         - LIN_STATUS_UNSUPPORTED : Current node is slave not, could not send header to protocol.
 *         - LIN_STATUS_BUSY        : Bus busy which means node is sending or receiving another frame.
 */
LIN_StatusType LIN_DrvSendHeader(LIN_HandleType *pLinHandle, uint8_t u8Id);

/**
 * @brief This API will help users send a frame data through LIN protocol, and will return only when
 *        all frame data has been sent to the protocol, or while timeout occurred, so please configure
 *        the u32TimeOut parameter as needed. And currentlyt this API has not implement the OS feature,
 *        so do not call this API in interrupt routine, otherwise, routine maybe halted by this API.
 *
 * @param pLinHandle    LIN processing handle
 * @param pTxBuf        TX buffer whihc will be sent to protocol, MUST NOT BE NULL.
 * @param u8Length      bytes lengths in TX buffer.
 * @param u32TimeOut    Timeout value, 0 indicates timeout feature is not used, in unit of millieconds.
 * @return              operation status:
 *                      - LIN_STATUS_SUCCESS  : operation is successfully.
 *                      - LIN_STATUS_NOT_INIT : Instance required has not been initialized.
 *                      - LIN_STATUS_BUSY     : Bus busy, node is transfer state.
 */
LIN_StatusType LIN_DrvSendFrameBlocking(LIN_HandleType *pLinHandle, uint8_t *pTxBuf, uint8_t u8Length, uint32_t u32TimeOut);

/**
 * @brief This API will help users send a frame data through LIN protocol, this API will return immediately.
 *        data will be stored in txbuffer, users can check the transmit status while data is sending.
 *
 * @param pLinHandle    LIN processing handle
 * @param pTxBuf        TX buffer whihc will be sent to protocol, MUST NOT BE NULL.
 * @param u8Length      bytes lengths in TX buffer.
 * @return              operation status:
 *                      - LIN_STATUS_SUCCESS  : operation is successfully.
 *                      - LIN_STATUS_NOT_INIT : Instance required has not been initialized.
 *                      - LIN_STATUS_BUSY     : Bus busy, node is transfer state.
 */
LIN_StatusType LIN_DrvSendFrameNonBlocking(LIN_HandleType *pLinHandle, uint8_t *pTxBuf, uint8_t u8Length);

/**
 * @brief This API will help users get the LIN transfer status while data is sending. and will also
 *        help user get remainning byte in transfer still need sending in buffer.
 *
 * @param pLinHandle    LIN processing handle
 * @param pRemainBytes  Address to be stored the remain byte value, should not be NULL.
 * @return              operation status:
 *                      - LIN_STATUS_TIMEOUT  : node transfer timeout occurred.
 *                      - LIN_STATUS_SUCCESS  : transfer complete.
 *                      - LIN_STATUS_BUSY     : transfer is going
 */
LIN_StatusType LIN_DrvGetTransmitStatus(LIN_HandleType *pLinHandle, uint8_t *pRemainBytes);

/**
 * @brief This API will help users receive frame data through LIN protocol, this API will return only when
 *        all frame data has been received from the protocol, or while timeout occurred, so please configure
 *        the u32TimeOut parameter as needed. And currently, this API has not implement the OS feature,
 *        so do not call this API in interrupt routine, otherwise, routine maybe halted by this API.
 *
 * @param pLinHandle    LIN processing handle
 * @param pRxBuf        RX buffer which will be received from protocol, MUST not be NULL.
 * @param u8Length      bytes lengths should be received.
 * @param u32TimeOut    Timeout value, 0 indicates timeout feature is not used, in millieconds.
 * @return              operation status:
 *                      - LIN_STATUS_SUCCESS  : operation is successfully.
 *                      - LIN_STATUS_NOT_INIT : Instance has not been initialized
 *                      - LIN_STATUS_BUSY     : Bus in busy state, need wait bus idle.
 *                      - LIN_STATUS_TIMEOUT  : Timeout occurred, data received may not successful.
 */
LIN_StatusType LIN_DrvReceiveFrameBlocking(LIN_HandleType *pLinHandle, uint8_t *pRxBuf, uint8_t u8Length, uint32_t u32TimeOut);

/**
 * @brief This API will help users received frame data through LIN protocol, this API will return immediately.
 *        data will be stored in rxbuffer, users can check the receive status while using this API.
 *
 * @param pLinHandle    LIN processing handle
 * @param pRxBuf        RX buffer which will be received from protocol, MUST not be NULL.
 * @param u8Length      bytes lengths should be received.
 * @return              operation status:
 *                      - LIN_STATUS_SUCCESS  : operation is successfully.
 *                      - LIN_STATUS_NOT_INIT : Instance has not been initialized
 *                      - LIN_STATUS_BUSY     : Bus in busy state, need wait bus idle.
 *                      - LIN_STATUS_TIMEOUT  : Timeout occurred, data received may not successful.
 */
LIN_StatusType LIN_DrvReceiveFrameNonBlocking(LIN_HandleType *pLinHandle, uint8_t *pRxBuf, uint8_t u8Length);

/**
 * @brief This API will help users get the LIN transfer status while data is receiving. and will also
 *        help user get remainning byte in transfer still need receiving in buffer.
 *
 * @param pLinHandle    LIN processing handle
 * @param pRemainBytes  Address to be stored the remain byte value, should not be NULL.
 * @return              operation status:
 *                      - LIN_STATUS_SUCCESS  : operation is successfully.
 *                      - others are not successfully.
 */
LIN_StatusType LIN_DrvGetReceiveStatus(LIN_HandleType *pLinHandle, uint8_t *pRemainBytes);

/**
 * @brief Abort transfer both sending or receiving data, actually, call this APU will enter IDLE state.
 *        will stop end and receive even data transfer is on going.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 */
void LIN_DrvAbortTransfer(LIN_HandleType *pLinHandle);

/**
 * @brief This API should be called while no data is transferring, once this API is called, node will
 *        enter sleep mode, TX/RX and interrupts will also be disabled, and node will wait a wakeup signal
 *        on the protocol. This API will enable receive active interrupt, once a wakeup signal triggered,
 *        routine will entern uart IRQHandler to handle this case, and then wakeup the LIN node.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 */
void LIN_DrvGoToSleepMode(LIN_HandleType *pLinHandle);

/**
 * @brief THis API will help confgure the mode into IDLE state. In IDLE state, node will enable receive interrupt and break
 *        field detect interrupt, slave node will wait the break field from master node, master node will prepare to send a
 *        new break filed to start a new frame.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 */
void LIN_DrvGoToIdleMode(LIN_HandleType *pLinHandle);

/**
 * @brief Sending a wakeup signal to the protocol, all LIN network nodes receive this signal will
 *        wakeup from sleep mode. Actually, the master will send a character which will cause a 150us
 *        larger active level to the protocol. while receiving this signal, LIN node will wake up
 *        from sleep mode.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 *                    - LIN_STATUS_NOT_INIT : Instance required is not initialized.
 *                    - LIN_STATUS_BUSY     ：LIN node state is not correct, need update state firstly.
 */
LIN_StatusType LIN_DrvSendWakeupSignal(LIN_HandleType *pLinHandle);

/**
 * @brief Get the LIN node state.
 *
 * @param pLinHandle    LIN processing handle
 * @return            the node current state, refer to lin_node_state_t
 */
lin_node_state_t LIN_DrvGetNodeState(LIN_HandleType *pLinHandle);

/**
 * @brief This API should be called by user's application code, and the timeout periods should be 500ms once.
 *        Better to provide a timer IRQhandler to call this APIs 500ms onces.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 *                    - others are not successfully.
 */
void LIN_DrvTimeOutService(LIN_HandleType *pLinHandle);

/**
 * @brief This API will help users set the timeout counter with one API, users should use this feature with LIN_DrvTimeOutService()
 *        called every fixed time.
 *
 * @param pLinHandle    LIN processing handle
 * @param u32TimeOutValue  Timeout value.
 * @return                 operation status:
 *                         - LIN_STATUS_SUCCESS  : operation is successfully.
 *                         - LIN_STATUS_NOT_INIT : Instance required is not initialized.
 */
void LIN_DrvSetTimeOutCounter(LIN_HandleType *pLinHandle, uint32_t u32TimeOutValue);

/**
 * @brief This API will help users get the Node timeout flag status.
 *
 * @param pLinHandle    LIN processing handle
 * @return            true for timeout occurred, false indicate no timeout.
 */
bool LIN_DrvGetTimeOutFlag(LIN_HandleType *pLinHandle);

/**
 * @brief This is LIN IRQ routine code, uses should call this in the FCUART IRQhandler code. please must implement
 *        the feature in application code.
 *
 * @param pLinHandle    LIN processing handle
 */
void LIN_DrvIRQHandler(LIN_HandleType *pLinHandle);

/**
 * @brief Makes a parity value.
 * This function calculates the parity bit for a given PID (Process Identifier).
 * 
 * @param PID The Process Identifier for which the parity is calculated.
 * @return The calculated parity value as a uint8_t.
 */
uint8_t LIN_DrvParityMake(uint8_t PID);

/**
 * @brief Checks a parity value.
 * This function verifies the correctness of the parity bit for a given PID (Process Identifier).
 * 
 * @param PID The Process Identifier whose parity is checked.
 * @return The result of the parity check as a uint8_t, indicating whether the parity is correct or not.
 */
uint8_t LIN_DrvParityCheck(uint8_t PID);

/**@}*/

/** @}*/ /* module_driver_lin */
#if defined(__cplusplus)
}
#endif

#endif

#endif /* _DRIVER_MODULE_DRIVER_LIN_H_ */
