/**
 * @file module_driver_fcuart.h
 * @author Flagchip
 * @brief FCUART driver type definition and API
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


#ifndef _DRIVER_MODULE_DRIVER_FCUART_H_
#define _DRIVER_MODULE_DRIVER_FCUART_H_

#include "HwA_fcuart.h"

#if FCUART_INSTANCE_COUNT > 0U
/**
 * @addtogroup module_driver_fcuart
 * @{
 */

/**
 * @name  FCUART API Service IDs
 * @brief Defines the service IDs for the FCUART module, which are used to identify different functions or services provided by the FCUART layer.
 *        These IDs are utilized when communicating with the FCUART module, enabling calls to or responses from various functions.
 * 
 * @{
 */
#define FCUART_INIT_ID                0U            /**< Initialization ID, used to initialize the FCUART module. */
#define FCUART_DEINIT_ID              1U            /**< Deinitialization ID, used to deinitialize the FCUART module. */
#define FCUART_SET_INTERRUPT_ID       2U            /**< Sets the interrupt mode ID, used to configure the interrupt mode of the FCUART module. */
#define FCUART_SET_WAKEUP_ID          3U            /**< Sets the wakeup threshold ID, used to configure the wakeup threshold of the FCUART module. */
#define FCUART_GET_INTERRUPT_ID       4U            /**< Gets the current interrupt status ID, used to query the interrupt status of the FCUART module. */
#define FCUART_START_RECEIVE_ID       5U            /**< Starts receiving data ID, used to start receiving data in interrupt or polling mode. */
#define FCUART_ASSIGN_TXINTRRUPT_ID   6U            /**< Assigns the transmit interrupt handler ID, used to register the transmit interrupt service routine. */
#define FCUART_START_TRANSMIT_ID      7U            /**< Starts transmitting data ID, used to start transmitting data in interrupt or polling mode. */
#define FCUART_TRANSMIT_ID            8U            /**< Transmits data ID, used to transmit a specified data. */
#define FCUART_PRINTF_ID              9U            /**< Outputs formatted data as characters ID, used to output formatted strings similar to printf. */
#define FCUART_GET_SATTUS_ID          10U           /**< Gets the current status ID, used to query the receive buffer status and error status. */
#define FCUART_RECEIVE_POLLING_ID     11U           /**< Starts receiving data in polling mode ID, used to start receiving data in polling mode. */
#define FCUART_ERROR_POLLING_ID       12U           /**< Queries the error status ID, used to query for errors in the receive buffer or transmit buffer. */
#define FCUART_SET_LOOPMODE_ID        13U           /**< Sets the loopback mode ID, used to configure the loopback mode for testing purposes. */
#define FCUART_STOP_RECEIVE_ID        14U           /**< Stops receiving data ID, used to stop receiving data. */
/** @}*/

/**
 * @name  UART_Error_Codes UART Error Codes
 * @brief Error codes for the FCUART module.
 * 
 * @{
 */
#define FCUART_E_PARAM_INSTANCE               0x01U             /**< Instance parameter error */
#define FCUART_E_PARAM_ERROR_STATE            0x02U             /**< Error state parameter */
#define FCUART_E_PARAM_POINTER                0x03U             /**< Pointer parameter error */
/** @}*/

#define FCUART_FIFO_DEPTH          4U   /**< FIFO buffer depth */

/**
 * @name  Special_Characters Special Characters
 * @brief Special characters used in UART communication.
 * 
 * @{
 */
#define ESCAPE_CHARACTER   (char)0x5c       /**< Escape character */
#define ENTER              (uint8_t)0x0d    /**< Enter character */
#define NEW_LINE           (uint8_t)0x0a    /**< New line character */
#define SPACE              (uint8_t)0x20    /**< Space character */
#define FLOAT_ZERO         0.00000001       /**< Floating point zero */
/** @}*/


/**
 * @brief Define the type of integer representation for UART printing.
 * 
 */
typedef enum
{
    UART_PRINT_RADIX_BIN = 2U,    /**< Binary representation */
    UART_PRINT_RADIX_OCT = 8U,    /**< Octal representation */
    UART_PRINT_RADIX_DEC = 10U,   /**< Decimal representation */
    UART_PRINT_RADIX_HEX = 16U    /**< Hexadecimal representation */
} UART_PrintIntType;

/**
 * @brief Define the enumeration for available UART instances in the FCUART system.
 * 
 * This enumeration simplifies the management and operation of UART devices by assigning a unique identifier to each UART instance.
 */
typedef enum
{
    UART_INSTANCE_0 = 0U, /**< UART instance 0 */
    UART_INSTANCE_1,      /**< UART instance 1 */
    UART_INSTANCE_2,      /**< UART instance 2 */
    UART_INSTANCE_3,      /**< UART instance 3 */
    UART_INSTANCE_4,      /**< UART instance 4 */
    UART_INSTANCE_5       /**< UART instance 5 */
} FCUART_InstanceType;

/**
 * @brief Defines the number of idle characters for UART.
 */
typedef enum
{
    FCUART_IDLE_CHARCTER_1  = 0U,    /**< Number of idle characters: 1 */
    FCUART_IDLE_CHARCTER_2,          /**< Number of idle characters: 2 */
    FCUART_IDLE_CHARCTER_4,          /**< Number of idle characters: 4 */
    FCUART_IDLE_CHARCTER_8,          /**< Number of idle characters: 8 */
    FCUART_IDLE_CHARCTER_16,         /**< Number of idle characters: 16 */
    FCUART_IDLE_CHARCTER_32,         /**< Number of idle characters: 32 */
    FCUART_IDLE_CHARCTER_64,         /**< Number of idle characters: 64 */
    FCUART_IDLE_CHARCTER_128         /**< Number of idle characters: 128 */
} FCUART_IdleCharNumType;

/**
 * @brief Define the enumeration for the number of characters received when the UART receive FIFO is idle.
 */
typedef enum
{
    FCUART_FIFO_RX_IDLE_DISABLE = 0U,       /**< The UART receive FIFO is idle and character reception is disabled. */
    FCUART_FIFO_RX_IDLE_CHARACTER_1,        /**< The UART receive FIFO is idle with a 1 character reception setting. */
    FCUART_FIFO_RX_IDLE_CHARACTER_2,        /**< The UART receive FIFO is idle with a 2 character reception setting. */
    FCUART_FIFO_RX_IDLE_CHARACTER_4,        /**< The UART receive FIFO is idle with a 4 character reception setting. */
    FCUART_FIFO_RX_IDLE_CHARACTER_8,        /**< The UART receive FIFO is idle with a 8 character reception setting. */
    FCUART_FIFO_RX_IDLE_CHARACTER_16,       /**< The UART receive FIFO is idle with a 16 character reception setting. */
    FCUART_FIFO_RX_IDLE_CHARACTER_32,       /**< The UART receive FIFO is idle with a 32 character reception setting. */
    FCUART_FIFO_RX_IDLE_CHARACTER_64        /**< The UART receive FIFO is idle with a 64 character reception setting. */
} FCUART_Fifo_RxIdleCharNumType;


/**
 * @brief Defines the types of UART idle states.
 *
 * This enumeration defines the possible states for when the UART should start
 * transmission or reception.
 */
typedef enum
{
    FCUART_START_AFTER_STARTBIT = 0U,  /**< Start after detecting a start bit. */
    FCUART_START_AFTER_STOPBIT         /**< Start after detecting a stop bit. */
} FCUART_IdleStartType;


/**
 * @brief Structure for UART transmit and receive operations.
 *
 * This structure holds the data buffer and its length for UART communication.
 */
typedef struct
{
    uint8_t*            pDatas;       /**< Pointer to the data buffer. Must be initialized with an array address. */
    uint32_t            u32DataLen;   /**< Length of the data to be transmitted or received. */
} FCUART_DataType;


/**
 * @brief Defines the sequence of operations for the FCUART driver.
 *
 * This enumeration specifies the different stages of the UART driver's operation.
 */
typedef enum
{
    FCUART_SEQUENCE_VAR_NOINIT,             /**< Variables are not initialized. */
    FCUART_SEQUENCE_DEINIT,                 /**< The driver is not initialized. */
    FCUART_SEQUENCE_NOTSTART_RECEIVE,       /**< The driver is initialized but not started. */
    FCUART_SEQUENCE_START_RECEIVE           /**< The driver has started receiving data. */
} FCUART_SequenceType;

/**
 * @brief Define the UART handle structure type.
 */
typedef struct _FCUART_HandleType
{
    FCUART_InstanceType eInstance;       /**< UART instance */
    uint8_t _aligned[3];                 /**< Alignment bytes */

    /**
     * @brief UART status information structure.
     */
    struct
    {
        FCUART_DataType *tFCUART_RxMsg;         /**< Pointer to the receive message buffer */
        FCUART_DataType *tFCUART_TxMsg;         /**< Pointer to the transmit message buffer */
        uint32_t u32FCUART_TransmitTimeout;     /**< Timeout value for transmission */
        FCUART_SequenceType eCurrentSequence;   /**< Current sequence type */
        uint8_t u8FCUART_Print_Buffer[200U];    /**< UART print buffer */
        uint8_t u8FCUART_UartUsed;              /**< UART usage status, 0 means not used, 1 means used.*/

        void (*pFCUART_ErrorNotify)(struct _FCUART_HandleType *pUartHandle, uint32_t u32Error);                 /**< Error notification callback function pointer */
        void (*pFCUART_RxNotify)(struct _FCUART_HandleType *pUartHandle, FCUART_DataType *pTxRxCfg);            /**< Receive notification callback function pointer */
        void (*pFCUART_TxEmptyNotify)(struct _FCUART_HandleType *pUartHandle, FCUART_DataType *pTxRxCfg);       /**< Transmission empty notification callback function pointer */
        void (*pFCUART_TxCompleteNotify)(struct _FCUART_HandleType *pUartHandle, FCUART_DataType *pTxRxCfg);    /**< Transmission complete notification callback function pointer */
        void (*pFCUART_IdleNotify)(struct _FCUART_HandleType *pUartHandle);                                     /**< Idle state notification callback function pointer */
    } tStatus;
} FCUART_HandleType;

/**
 * @brief FCUART error interrupt callback function type
 * 
 * This function type is used to define the callback function that is invoked when an error occurs in the FCUART module.
 * It combines the error status with the FCUART_ErrorStatusType to notify the user of specific error conditions.
 * This design allows users to perform custom operations when errors occur, enhancing the flexibility and error handling capabilities of UART communication.
 * 
 * @param pUartHandle Pointer to the UART handle structure containing configuration and state information.
 * @param u32Error The error code indicating the specific error that occurred.
 */
typedef void (*FCUART_ErrorInterrupt_CallBackType)(FCUART_HandleType *pUartHandle, uint32_t u32Error);

/**
 * @brief FCUART transmit/receive interrupt callback function type
 * 
 * This function type is used to define the callback function that is invoked when a transmission or reception operation completes.
 * It provides the UART handle and data configuration parameters to allow the user to process the transmitted or received data.
 * 
 * @param pUartHandle Pointer to the UART handle structure containing configuration and state information.
 * @param pTxRxCfg Pointer to the configuration structure for the transmitted or received data.
 */
typedef void (*FCUART_TxRxInterrupt_CallBackType)(FCUART_HandleType *pUartHandle, FCUART_DataType *pTxRxCfg);

/**
 * @brief FCUART idle interrupt callback function type
 * 
 * This function type is used to define the callback function that is invoked when the UART module enters an idle state.
 * It can be used to perform any necessary actions when there is no ongoing transmission or reception.
 * 
 * @param pUartHandle Pointer to the UART handle structure containing configuration and state information.
 */
typedef void (*FCUART_IdleInterrupt_CallBackType)(FCUART_HandleType *pUartHandle);

/**
 * @brief UART callback functions data define
 *
 */
typedef struct
{
    bool                                bEnErrorInterrupt;  /**< enable error interrupt                      */
    bool                                bEnRxInterrupt;     /**< enable receive interrupt                    */
    bool                                bEnTxInterrupt;     /**< enable receive interrupt                    */
    bool                                bEnIdleInterrupt;   /**< enable idle interrupt                          */
    FCUART_DataType                     *pRxBuf;            /**< receive interrupt message buffer            */
    FCUART_DataType                     *pTxBuf;            /**< transfer interrupt message buffer            */
    FCUART_TxRxInterrupt_CallBackType   pRxNotify;          /**< receive interrupt callback function address */
    FCUART_TxRxInterrupt_CallBackType   pTxEmptyNotify;     /**< transfer empty interrupt callback function address */
    FCUART_TxRxInterrupt_CallBackType   pTxCompleteNotify;  /**< transfer complete interrupt callback function address */
    FCUART_ErrorInterrupt_CallBackType  pErrorNotify;       /**< error interrupt callback function address   */
    FCUART_IdleInterrupt_CallBackType   pIdleNotify;        /**< idle interrupt callback function address */
} FCUART_InterruptType;

/**
 * @brief UART initial data define
 *
 */
typedef struct
{
    FCUART_InterruptType           tInterruptCfg;      /**<interrupt configuration parameter           */
    uint32_t                       u32ClkSrcHz;        /**< module clock hz                            */
    uint32_t                       u32Baudrate;        /**< normal baud-rate                           */
    uint32_t                       u32TransmitTimeout; /**< transmit timeout tick, default 3000        */
    FCUART_BitModeType             eBitMode;           /**< 8bits or 9bits with parity                 */
    FCUART_ParityType              eParityType;        /**< parity type                                */
    FCUART_StopBitNumType          eStopBit;           /**< stop bit num;                              */
    FCUART_IdleCharNumType         eIdleCharNum;       /**< Idle character number                      */
    FCUART_Fifo_RxIdleCharNumType  eFifoRxIdleCharNum; /**< Fifo Rx idle character number              */
    FCUART_IdleStartType           eIdleStart;         /**< Idle character start type                  */
    uint8_t                        bParityEnable;      /**< Parity Enable=1                            */
    uint8_t                        bEnTxFifo;          /**< Enable Tx FIFO, 4bits depth                */
    uint8_t                        u8TxFifoWM;         /**< Tx FIFO water mark, less than or equal must generate request, 0-3  */
    uint8_t                        bEnRxFifo;          /**< Enable Rx FIFO, 4bits depth                */
    uint8_t                        u8RxFifoWM;         /**< Rx FIFO water mark, greater than must generate request, 0-3  */
    uint8_t                        bEnTxEmptyDma;      /**< Enable Tx DMA                                 */
    uint8_t                        bEnRxFullDma;       /**< Enable Rx DMA                                 */
    uint8_t                        bEnRxIdleDma;       /**< Enable Rx Idle DMA                                 */
} FCUART_InitType;

/**
 * @brief UART error status type
 *
 */
typedef enum
{
    FCUART_ERROR_NONE = 0x0000U,   /**< FCUART_ERROR_NONE    No Error,                            */
    FCUART_ERROR_RORF = 0x0001U,   /**< FCUART_ERROR_RORF    Receiver Overrun Flag,               */
    FCUART_ERROR_NF   = 0x0002U,   /**< FCUART_ERROR_NF      Noise Flag,                          */
    FCUART_ERROR_FEF  = 0x0004U,   /**< FCUART_ERROR_FEF     Frame Error Flag,                    */
    FCUART_ERROR_PEF  = 0x0008U,   /**< FCUART_ERROR_PEF     Parity Error Flag,                   */
    FCUART_ERROR_RPEF = 0x0010U,   /**< FCUART_ERROR_RPEF    Receive Data Parity Error Flag,      */
    FCUART_ERROR_TPEF = 0x0020U    /**< FCUART_ERROR_TPEF    Transmit Data Parity Error Flag,     */
}FCUART_ErrorStatusType;

/**
 * @brief UART CTRL register interrupt
 *
 */
typedef enum
{
    FCUART_INT_CTRL_ORIE = FCUART_CTRL_ORIE_MASK,       /**< ORIE: Overrun Error Interrupt Enable */
    FCUART_INT_CTRL_NEIE = FCUART_CTRL_NEIE_MASK,       /**< NEIE: Noise Error Interrupt Enable */
    FCUART_INT_CTRL_FEIE = FCUART_CTRL_FEIE_MASK,       /**< FEIE: Frame Error Interrupt Enable */
    FCUART_INT_CTRL_PEIE = FCUART_CTRL_PEIE_MASK,       /**< PEIE: Parity Error Interrupt Enable */
    FCUART_INT_CTRL_TIE  = FCUART_CTRL_TIE_MASK,        /**< TIE: Transmitter Interrupt Enable */
    FCUART_INT_CTRL_TCIE = FCUART_CTRL_TCIE_MASK,       /**< TCIE: Transmitter Complete Interrupt Enable */
    FCUART_INT_CTRL_RIE  = FCUART_CTRL_RIE_MASK,        /**< RIE: Receiver Interrupt Enable */
    FCUART_INT_CTRL_IIE  = FCUART_CTRL_IIE_MASK,        /**< IIE: Idle Line Interrupt Enable */
    FCUART_INT_CTRL_TE   = FCUART_CTRL_TE_MASK,         /**< TE: Transmitter Enable */
    FCUART_INT_CTRL_RE   = FCUART_CTRL_RE_MASK,         /**< RE: Receiver Enable */
    FCUART_INT_CTRL_M0IE = FCUART_CTRL_M0IE_MASK,       /**< M0IE: Modem Control 0 Interrupt Enable */
    FCUART_INT_CTRL_M1IE = FCUART_CTRL_M1IE_MASK        /**< M1IE: Modem Control 1 Interrupt Enable */
} FCUART_InterruptSel;

/**
 * @brief UART WakeUp functions data define
 *
 */
typedef struct
{
    uint8_t  bEnWakeup;          /**< enable wake-up   */
    uint8_t  u32WakeUpData;      /**< wake-up data  */

} FCUART_WakeupType;

/**
 * @brief FCUART error status
 *
 */
typedef enum
{
    FCUART_ERROR_OK               = 0x00U,    /**< FCUART_ERROR_OK means no error                                      */
    FCUART_ERROR_INVALID_VERSION  = 0x01U,    /**< FCUART_ERROR_INVALID_VERSION means version is not same */
    FCUART_ERROR_FAILED           = 0x02U,    /**< FCUART_ERROR_FAILED means operation is failed                       */
    FCUART_ERROR_INVALID_PARAM    = 0x04U,    /**< FCUART_ERROR_INVALID_PARAM means parameters are invalid             */
    FCUART_ERROR_INVALID_SIZE     = 0x08U,    /**< FCUART_ERROR_INVALID_SIZE means size is invalid                     */
    FCUART_ERROR_INVALID_SEQUENCE = 0x10U,    /**< FCUART_ERROR_INVALID_SEQUENCE means sequence is error               */
    FCUART_ERROR_TIMEOUT          = 0x20U,    /**< FCUART_ERROR_TIMEOUT means operation is timeout                     */
}FCUART_ErrorTypeEnum;

/** @brief Errortype Define as uint8 */
typedef uint8_t  FCUART_ErrorType;

/**
 * @brief Initializes the memory for the UART handle.
 * 
 * This function should be called during the initialization phase of UART communication
 * to ensure that the memory pointed to by the UART handle is correctly allocated.
 * 
 * @param pUartHandle Pointer to the UART handle structure.
 */
void FCUART_InitMemory(FCUART_HandleType *pUartHandle);

/**
 * @brief Initializes the UART module based on the provided configuration.
 * 
 * This function configures and initializes a UART handle structure according to the given settings, enabling serial communication. It allows users to set parameters such as baud rate, data bit length, parity, and stop bits, which are specified in the initialization configuration structure.
 * 
 * @param pUartHandle Pointer to the UART handle structure that contains UART configuration and status information.
 * @param pInitCfg Pointer to the initialization configuration structure containing UART settings.
 * 
 * @return FCUART_ErrorType Indicates whether the initialization was successful or if an error occurred.
 */
FCUART_ErrorType FCUART_Init(FCUART_HandleType *pUartHandle, FCUART_InitType *pInitCfg);

/**
 * @brief This Function is used to de-initial UART instance
 *
 * @param pUartHandle The structure of the UART processing handle
 * @return void
 */
void FCUART_DeInit(FCUART_HandleType *pUartHandle);

/**
 * @brief This Function is used to set UART WakeUp
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pWakeupCfg contains UART wake-up parameters
 */
void FCUART_SetWakeup(FCUART_HandleType *pUartHandle, FCUART_WakeupType *pWakeupCfg);

/**
 * @brief This Function is used to start receiving
 *
 * @param pUartHandle The structure of the UART processing handle
 */
void FCUART_StartReceive(FCUART_HandleType *pUartHandle);

/**
 * @brief This Function is used to stop receiving
 *
 * @param pUartHandle The structure of the UART processing handle
 */
void FCUART_StopReceive(FCUART_HandleType *pUartHandle);

/**
 * @brief This Function is used to transmit UART data
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pUartData contains UART data and length
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Transmit(FCUART_HandleType *pUartHandle, FCUART_DataType *pUartData);

/**
 * @brief This Function is used to print ASCII char from UART
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param fmt is char format
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Printf(FCUART_HandleType *pUartHandle, char* fmt,...);

/**
 * @brief Get Stat Flag
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param eStatusType  stat type
 * @return FCUART STAT status flag
 */
uint32_t FCUART_GetStatus(FCUART_HandleType *pUartHandle, FCUART_StatType eStatusType);

/**
 * @brief This Function is used to receive data when polling (not used when rx interrupt enabled)
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pRxMsg is data buffer address, and pDatas need to be initialed with external buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Receive_Polling(FCUART_HandleType *pUartHandle, FCUART_DataType *pRxMsg);


/**
 * @brief This Function is used to get error when polling (not used when error interrupt enabled)
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pErrorValue is error value
 */
void FCUART_Error_Polling(FCUART_HandleType *pUartHandle, uint32_t *pErrorValue);

/**
 * @brief This Function is used to enable fcuart loop mode
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param bStatus  enable/disable status of loop mode
 *
 */
void FCUART_SetLoopMode(FCUART_HandleType *pUartHandle, bool bStatus);

/**
 * @brief This Function is used to Get current interrupt mode
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param u32Data  Interrupt type to get
 * @return true/false
 *
 */
bool FCUART_GetInterruptMode(FCUART_HandleType *pUartHandle, uint32_t u32Data);

/**
 * @brief This Function is used to start transmit
 *
 * @param pUartHandle The structure of the UART processing handle
 */
void FCUART_StartTransmit(FCUART_HandleType *pUartHandle);

/**
 * @brief This Function is used to assign data to send through interrupt
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pData  data pointer
 * @param u32Length data length to send
 *
 */
void FCUART_AssignTxInterruptData(FCUART_HandleType *pUartHandle, uint8_t * pData, uint32_t u32Length);

/**
 * @brief This Function is used to enable fcuart irq handler
 *
 * @param pUartHandle The structure of the UART processing handle
 *
 */
void FCUARTN_RxTx_IRQHandler(FCUART_HandleType *pUartHandle);

/** @}*/

#endif

#endif
