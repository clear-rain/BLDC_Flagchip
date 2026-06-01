/**
 * @file module_driver_flexcan.h
 * @author Flagchip
 * @brief FLEXCAN driver type definition and API
 * @version 2.0.0
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip038   N/A          First version
*   2.0.1       2024-08-20    Flagchip038   N/A          Add busoff auto recovery paramater
*   2.0.2       2024-10-20    Flagchip038   N/A          Update Initial Parameters
*   2.1.0       2024-11-20    Flagchip038   N/A          Add clear flag interrupt macro
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_FLEXCAN_H_
#define _DRIVER_MODULE_DRIVER_FLEXCAN_H_

#include "HwA_flexcan.h"

#if FLEXCAN_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_flexcan
 * @{
 */


/* ################################################################################## */
/* ####################################### Macro #################################### */

/**
 * @name  CAN Detection Error Code
 * @brief All can det code
 *
 * @{
 */
#define FLEXCAN_DET_ERROR_ID_FUNC_CHECKINSTANCE        0x01U  /**<FLEXCAN_DET_ERROR_ID_FUNC_CHECKINSTANCE means error in check instance error function */
#define FLEXCAN_DET_ERROR_ID_FUNC_INIT                 0x01U  /**<FLEXCAN_DET_ERROR_ID_FUNC_INIT means error in initial function */
#define FLEXCAN_DET_ERROR_ID_FUNC_PROCESS              0x02U  /**<FLEXCAN_DET_ERROR_ID_FUNC_PROCESS means error in process */
#define FLEXCAN_DET_ERROR_ID_FUNC_SETINTERRUPT         0x03U  /**<FLEXCAN_DET_ERROR_ID_FUNC_SETINTERRUPT means error in set interrupt */
#define FLEXCAN_DET_ERROR_ID_FUNC_START                0x04U  /**<FLEXCAN_DET_ERROR_ID_FUNC_START means error in can start */
#define FLEXCAN_DET_ERROR_ID_FUNC_STOP                 0x05U  /**<FLEXCAN_DET_ERROR_ID_FUNC_STOP means error in can stop */
#define FLEXCAN_DET_ERROR_ID_FUNC_TRANSMIT             0x06U  /**<FLEXCAN_DET_ERROR_ID_FUNC_TRANSMIT means error in can transmit */
#define FLEXCAN_DET_ERROR_ID_FUNC_RECEIVE              0x07U  /**<FLEXCAN_DET_ERROR_ID_FUNC_RECEIVE means error in can receive */
/** @}*/

/**
 * @name  CAN Return Error Code
 * @brief All can error code
 *
 * @{
 */
#define FLEXCAN_E_OK                    0x00U               /**< FLEXCAN_E_OK means no error                                      */
#define FLEXCAN_E_INVALID_VERSION       0x01U               /**< FLEXCAN_E_INVALID_VERSION means version is not same */
#define FLEXCAN_E_FAILED                0x02U               /**< FLEXCAN_E_FAILED means operation is failed                       */
#define FLEXCAN_E_INVALID_PARAM         0x04U               /**< FLEXCAN_E_INVALID_PARAM means parameters are invalid             */
#define FLEXCAN_E_INVALID_SIZE          0x08U               /**< FLEXCAN_E_INVALID_SIZE means size is invalid                     */
#define FLEXCAN_E_INVALID_SEQUENCE      0x10U               /**< FLEXCAN_E_INVALID_SEQUENCE means sequence is error               */
#define FLEXCAN_E_NULL_POINT            0x20U               /**< FLEXCAN_E_INVALID_SEQUENCE means sequence is error               */
#define FLEXCAN_E_TIMEOUT               0x40U               /**< FLEXCAN_E_NULL_POINT means buffer point is null                  */
#define FLEXCAN_E_BUSY                  0x80U               /**< FLEXCAN_E_BUSY means current mb is busy                          */
#define FLEXCAN_E_MB_OUTOFRANGE         0x100U              /**< FLEXCAN_E_MB_OUTOFRANGE mb number is out of range                */
/** @}*/

/**
 * @name  CAN DET Function
 * @brief CAN DET Function
 *
 * @{
 */
#ifndef FLEXCAN_DEV_ERROR_REPORT
    /* if not defined development error, default set off */
    #define FLEXCAN_DEV_ERROR_REPORT   STD_OFF
#endif

#if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    #define FLEXCAN_ReportDevError(func, error) ReportDevError(FLEXCAN_MODULE_ID, func, error)
#else
    #define FLEXCAN_ReportDevError(func, error)
#endif

#ifndef FLEXCAN_TX_FLAG_CLEAR_FIRST
    /* if not defined tx flag clear first, default set off */
    #define FLEXCAN_TX_FLAG_CLEAR_FIRST    STD_OFF
#endif

#ifndef FLEXCAN_RX_FLAG_CLEAR_FIRST
    /* if not defined tx flag clear first, default set off */
    #define FLEXCAN_RX_FLAG_CLEAR_FIRST    STD_OFF
#endif

#ifndef FLEXCAN_ERROR_FLAG_CLEAR_FIRST
    /* if not defined error flag clear first, default set on */
    #define FLEXCAN_ERROR_FLAG_CLEAR_FIRST    STD_ON
#endif
/** @}*/

/* ################################################################################## */
/* ################################### Type define ################################## */


/**
 * @brief FLEXCAN error status
 *
 */
typedef uint32_t   FLEXCAN_ErrorType;


/**
 * @name  CAN enumeration definition
 * @brief CAN enumeration definition
 *
 * @{
 */
/**
 * @brief FLEXCAN ID Type
 *
 */
typedef enum
{
    FLEXCAN_ID_STD = 0x00U,    /**< FLEXCAN_ID_STD standard id */
    FLEXCAN_ID_EXT = 0x01U     /**< FLEXCAN_ID_EXT extended id */
} FLEXCAN_IdType;

/**
 * @brief FLEXCAN Data Frame Type
 *
 */
typedef enum
{
    FLEXCAN_FRAME_DATA   = 0x00U,    /**< FLEXCAN_FRAME_DATA data frame     */
    FLEXCAN_FRAME_REMOTE = 0x01U     /**< FLEXCAN_FRAME_REMOTE remote frame */
} FLEXCAN_DataType;

/**
 * @brief Baud-rate clock and divider
 *
 */
typedef struct
{
    uint32_t             u32Presdiv;  /**< Presdiv for can                   */
    uint32_t             u32Propseg;  /**< Propseg for can                   */
    uint32_t             u32Pseg1;    /**< Pseg1 for can                     */
    uint32_t             u32Pseg2;    /**< Pseg2 for can                     */
    uint32_t             u32Rjw;      /**< RJW for can                       */
} FLEXCAN_BaudRegType;




/**
 * @brief CAN Operation Sequence
 *
 */
typedef enum
{
    FLEXCAN_SEQUENCE_DEINIT,                  /**< FLEXCAN_SEQUENCE_DEINIT means CAN driver is not initialed          */
    FLEXCAN_SEQUENCE_NOTSTART,                /**< FLEXCAN_SEQUENCE_NOTSTART means can driver initialed and not start */
    FLEXCAN_SEQUENCE_STARTED                  /**< FLEXCAN_SEQUENCE_STARTED means can driver started                  */
} FLEXCAN_SequenceType;

/**
 * @brief CAN wake-up source
 *
 */
typedef enum
{
    FLEXCAN_PENT_WAKEUP_SRC_TIMEOUT,/**< FLEXCAN_PENT_WAKEUP_SRC_TIMEOUT means wake-up source is timeout */
    FLEXCAN_PENT_WAKEUP_SRC_MATCH   /**< FLEXCAN_PENT_WAKEUP_SRC_MATCH means wake-up source is match */
}FLEXCAN_PNET_WakeupSrcType;

/**
 * @brief CAN wake-up source
 *
 */
typedef enum
{
    FLEXCAN_LEGACY_FIFO,			/**< FLEXCAN_PENT_WAKEUP_SRC_TIMEOUT means wake-up source is timeout */
    FLEXCAN_ENHANCED_FIFO   		/**< FLEXCAN_PENT_WAKEUP_SRC_MATCH means wake-up source is match */
}FLEXCAN_FifoType;

/** @}*/



/**
 * @name  CAN structure definition
 * @brief CAN structure definition
 *
 * @{
 */

/**
 * @brief FLEXCAN Error Information
 *
 */
typedef struct
{
    uint32_t             u32RxErrCnt_Fast;  /**< Receive Error Counter for fast bits      */
    uint32_t             u32RxErrCnt;       /**< Receive Error Counter                    */
    uint32_t             u32TxErrCnt_Fast;  /**< Transmit Error Counter for fast bits     */
    uint32_t             u32TxErrCnt;       /**< Transmit Error Counter                   */
    uint32_t             u32ESR1Value;      /**< Error Register ESR1 Value                */
} FLEXCAN_ErrorInfoType;

/**
  * @brief  FLEXCAN receive message
  */
typedef struct
{
    uint8_t             u8CanIndex;    /**< FLEXCAN Index, 0,1,2..NUM        */
    uint8_t             u8RxHandle;    /**< Handle set by user, FIFO always FF */
    uint8_t             bEnFd;         /**< enable FLEXCAN fd                */
    uint8_t             bEnBrs;        /**< enable canfd data bit switch     */
    FLEXCAN_IdType      eFrameType;    /**< 0 STD, 1 EXT                     */
    FLEXCAN_DataType    eDataType;     /**< 0 Data, 1 remote                 */
    uint32_t            u32CanId;      /**< FLEXCAN id                       */
    uint32_t            u32DataLen;    /**< data length                      */
    uint8_t             aData[80];     /**< data buffer                      */

} FLEXCAN_RxMsgType;



/**
 * @brief Receive Message Buffer Configuration
 *
 */
typedef struct
{
    FLEXCAN_IdType           eRxFrameType;   /**< FLEXCAN ID type, 0 STD, 1 EXT */
    uint32_t                 u32RxCanId;     /**< FLEXCAN received ID           */
    uint32_t                 u32RxCanIdMask; /**< FLEXCAN received ID mask, if mask bit is 1, received FLEXCAN id bit must same to u32RxCanId, or mask bit is 0, id bit is ignored */
} FLEXCAN_FifoFilterType;

/**
 * @brief Message Buffer Configuration
 *
 */
typedef struct
{
    uint8_t                  bIsTxMB;        /**< 0 is rx, 1 is tx                            */
    uint8_t                  bEnMBInt;       /**< if enable can current MB interrupt, set 1U  */
    FLEXCAN_IdType           eRxFrameType;   /**< FLEXCAN ID type, 0 STD, 1 EXT               */
    uint32_t                 u32RxCanId;     /**< FLEXCAN received ID                         */
    uint32_t                 u32RxCanIdMask; /**< FLEXCAN received ID mask, if mask bit is 1, received FLEXCAN id bit must same to u32RxCanId, or mask bit is 0, id bit is ignored */
} FLEXCAN_MbSettingType;

/**
  * @brief  FLEXCAN legacy fifo configuration structure definition
  */
typedef struct
{
    uint8_t                  bEnFifoDMA;            /**< if enable can fifo dma, set 1U, only fifo support    */
    uint8_t                  bDataAvaliableInt;     /**< if at least one message in fifo interrupt, can trigger dma */
    uint8_t                  bWarningInt;           /**< increase from 4 to 5 messages in fifo interrupt      */
    uint8_t                  bOverflowInt;          /**< more than 5 messages in fifo and data lost interrupt */
    uint8_t                  u8RxFilterFifoCnt;     /**< rx id filter count, in fifo                          */
    FLEXCAN_FifoFilterType     *pRxFilterFifoList;    /**< rx id list in fifo                                   */

} FLEXCAN_LegacyFifoConfigType;


/**
  * @brief  FLEXCAN enhanced fifo configuration structure definition
  */
typedef struct
{
    uint8_t                  bEnFifoDMA;            /**< if enable can fifo dma, set 1U, only fifo support  */
    uint8_t                  bDataAvaliableInt;     /**< if at least one message in fifo interrupt          */
    uint8_t                  u8FifoWaterMark;       /**< The watermark for only in Enhanced FIFO mode, can trigger dma */
    uint8_t                  bWaterMarkInt;         /**< if fifo depth greater than or equal watermark will trigger interrupt */
    uint8_t                  bOverflowInt;          /**< fifo full and data lost in fifo interrupt          */
    uint8_t                  bUnderflowInt;         /**< no data in fifo but read data from fifo cause interrupt */
    FLEXCAN_DataWidthType    eFifoDataLength;      /**< data length for enhanced rx fifo DMALW             */
    uint8_t                  u8RxFilterFifoCnt;     /**< rx id filter count, in fifo                        */
    FLEXCAN_FifoFilterType   *pRxFilterFifoList;    /**< rx id list in fifo                                 */

} FLEXCAN_EnhancedFifoConfigType;

/**
  * @brief  FLEXCAN fifo configuration structure definition
  */
typedef struct
{
    uint8_t                         bEnFifo;               /**< 0 is disable, 1 is enable                               */
    FLEXCAN_FifoType                eFifoType;             /**< 0 is legacy fifo, 1 is enhanced fifo, only one of them  */
    FLEXCAN_LegacyFifoConfigType    tLegacyFifoCfg;        /**< Legacy Rx FIFO configuration                            */
    FLEXCAN_EnhancedFifoConfigType  tEnhancedFifoCfg;      /**< Enhanced Rx FIFO configuration                          */
} FLEXCAN_FifoConfigType;

/**
  * @brief  FLEXCAN mb configuration structure definition
  */
typedef struct
{
    FLEXCAN_DataWidthType    aDataWidthRange[FLEXCAN_FD_DATALEN_RANGE_NUM_MAX];   /**< data length range buffer, MBDSR0..MBDSRn, only used in canfd        */
    uint8_t                  u8MBCnt;                                             /**< rx id filter count in MB                        */
    FLEXCAN_MbSettingType    *pMBList;                                            /**< rx id list in MB                                */
} FLEXCAN_MbConfigType;


/**
  * @brief  FLEXCAN transmit message
  */
typedef struct
{
    uint8_t                 u8TxHandle;      /**< one message buffer used one handler, range 0 ~ txMbCnt-1     */
    uint8_t                 bEnFd;           /**< enable FLEXCAN fd                                            */
    uint8_t                 bEnBrs;          /**< enable canfd data bit switch                                 */
    uint32_t                u32CanId;        /**< FLEXCAN id                                                   */
    FLEXCAN_IdType          eFrameType;      /**< 0 STD, 1 EXT                                                 */
    FLEXCAN_DataType        eDataType;       /**< 0 Data, 1 remote                                             */
    uint32_t                u32DataLen;      /**< data length                                                  */
    uint8_t                 aData[64];       /**< data buffer                                                  */
} FLEXCAN_TxMsgType;


/**
  * @brief  FLEXCAN polling receive message
  */
typedef struct
{
    uint8_t             u8RxMsgCnt;     /**< Receive Message Buffer Count    */
    FLEXCAN_RxMsgType   *pRxMsgBuf;     /**< Receive Message Buffer Address  */

} FLEXCAN_RxMsgListType;

/**
 * @brief FIFO error response type
 *
 */
typedef struct
{
    FLEXCAN_FifoType  eFifoType;      /**< 0 means legacy fifo, 1 means enhanced fifo, only one of them  */
    uint8_t           u8FifoWarings;   /**< 0 means no legacy fifo waring, 0 means contain legacy fifo waring  */
    uint8_t           u8FifoOverflow;  /**< 0 means data lost  */
    uint8_t           u8FifoUnderflow; /**< 0 means no enhanced fifo underflow, 0 means contain enhanced fifo underflow */
}FLEXCAN_FifoIssueType;


/**
 * @brief CAN ID filter setting
 *
 */
typedef struct
{
    uint8_t   u8IDE;    /**< 0-Standard ID, 1-Extended ID */
    uint8_t   u8RTR;    /**< 0-Data Frame, 1-Remote Frame */
    uint32_t  u32Id;    /**< CAN ID for wake-up           */
}FLEXCAN_PNET_IdSettingType;

/**
 * @brief CAN Pretended network id filter setting
 *
 */
typedef struct
{
    FLEXCAN_PNET_IdFilterType  eFilterType;   /**< ID filter type for Pretented Network */
    FLEXCAN_PNET_IdSettingType tID1;           /**< ID1 for filter                       */
    FLEXCAN_PNET_IdSettingType tID2_Mask;      /**< ID2 for filter range or mask         */
}FLEXCAN_PNET_IDConfgType;

typedef struct
{
    FLEXCAN_PNET_PayloadFilterType  eFilterType;      /**< Payload filter type for Pretented Network */
    uint8_t                         u8DataLen1;       /**< Data length 1 for filter                  */
    uint8_t                         u8DataLen2;       /**< Data length 2 for filter                  */
    uint32_t                        aData1[2];        /**< Data Payload 1, LO+HI                     */
    uint32_t                        aData2[2];        /**< Data Payload 2, LO+HI                     */
}FLEXCAN_PNET_PayloadConfgType;

/**
 * @brief CAN Pretended network configuration
 *
 */
typedef struct
{
    uint8_t                       bPNetEnable;         /**< Enable Pretended network settings */
    uint8_t                       bTimeoutEn;          /**< Enable timeout for no message matched */
    uint16_t                      u16Timeout;          /**< time start after MCR[PNET_EN] set, period is 64 times of can bit time */
    uint8_t                       bFilterEnable;       /**< Enable filter message wake-up */
    FLEXCAN_PNET_FilterType       ePnetFilterType;     /**< Pretended network filter type */
    uint8                         u8MatchTimes;        /**< when match times reached, interrupt will be trigger, 1-255 */
    FLEXCAN_PNET_IDConfgType      tIdCfg;              /**< When id selection set, configure this structure */
    FLEXCAN_PNET_PayloadConfgType tPayloadCfg;         /**< When payload selection set, configure this structure */
}FLEXCAN_PNET_ConfigType;


/**
  * @brief  FLEXCAN wake-up receive message
  */
typedef struct
{
    uint8_t                    u8CanIndex;    /**< FLEXCAN Index, 0,1,2..NUM         */
    FLEXCAN_PNET_WakeupSrcType eWakeupSrc;    /**< Wake-up source                    */
    FLEXCAN_IdType             eFrameType;    /**< 0 STD, 1 EXT                      */
    FLEXCAN_DataType           eDataType;     /**< 0 Data, 1 remote                  */
    uint32_t                   u32CanId;      /**< FLEXCAN id                        */
    uint32_t                   u32DataLen;    /**< data length                       */
    uint8_t                    aData[8];      /**< data buffer, do not support canfd */

} FLEXCAN_WakeupMsgType;


/**
 * @brief The structure of the CAN processing handle
 *
 */
typedef struct _FLEXCAN_HandleType
{
    FLEXCAN_InstanceType        eInstance; /**< CAN instance */

    /**
     * @brief can inner status
     *     tStatus Can't be set by user
     *
     */
    struct
    {
        FLEXCAN_SequenceType     eStatusSeq;                                       /**< Can statue sequence                                                      */
        uint8_t                  u8MbStart;                                        /**< if legacy rx fifo enabled, mb start after n/4+6                          */
        FLEXCAN_DataWidthType    aMbDataWidth[FLEXCAN_FD_DATALEN_RANGE_NUM_MAX];   /**< Message Buffer Data Width, only used in canfd                            */
        uint32_t                 aRxInterruptMask[FLEXCAN_IFLAGMASK_NUM_MAX];      /**< rx mask value for interrupt                                              */
        uint32_t                 aTxInterruptMask[FLEXCAN_IFLAGMASK_NUM_MAX];      /**< tx mask value for interrupt                                              */
        uint32_t                 aInterruptMask[FLEXCAN_IFLAGMASK_NUM_MAX];        /**< tx mask value for interrupt                                              */
        uint32_t                 aRxPollingMask[FLEXCAN_IFLAGMASK_NUM_MAX];        /**< rx mask value for polling                                                */
        uint32_t                 aTxPollingMask[FLEXCAN_IFLAGMASK_NUM_MAX];        /**< tx mask value for polling                                                */
        uint32_t                 aPollingMask[FLEXCAN_IFLAGMASK_NUM_MAX];          /**< tx mask value for polling                                                */
    } tStatus;

    /**
     * @brief CAN global settings, include callback function and special value like buffer address
     *
     */
    struct
    {

        FLEXCAN_RxMsgType        *pRxBuf;                                                                 /**< receive buffer address */
        FLEXCAN_WakeupMsgType    *pWakeMsg;                                                               /**< Wake-up message buffer address */

        void (*pErrorNotify)(struct _FLEXCAN_HandleType *pHandle, FLEXCAN_ErrorInfoType *pErrorInfo);     /**< Error callback function type */
        void (*pFifoIssueNotify)(struct _FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue); /**< FIFO issue callback function type */
        void (*pTxNotify)(struct _FLEXCAN_HandleType *pHandle, uint8_t u8TxHandle);                       /**< transmit callback function type, u8TxHandle is the handle for message */
        void (*pRxNotify)(struct _FLEXCAN_HandleType *pHandle, FLEXCAN_RxMsgType *pRxMsg);                /**< Receive callback function type */
        void (*pWakeNotify)(struct _FLEXCAN_HandleType *pHandle, FLEXCAN_WakeupMsgType *pWakeMsg);        /**< Pretended Network wake-up callback function type */
    } tSettings;

} FLEXCAN_HandleType;

/**
  * @brief  FLEXCAN init structure definition
  */
typedef struct
{
    FLEXCAN_ClockSrcType        eClkSrcSel;               /**< Clock Source Select                                                      */
    uint8_t                     bListenOnly;              /**< Listen Only                                                              */
    FLEXCAN_BaudRegType         tNormalBaud;              /**< Presdiv,Propseg,Pseg1,Pseg2,rjw for can baud                             */
    uint8_t                     bEnFd;                    /**< enable FLEXCAN fd                                                        */
    FLEXCAN_BaudRegType         tFdBaud;                  /**< Presdiv,Propseg,Pseg1,Pseg2,rjw for can fd data baud                     */

    uint8_t                     bEnSsp;                   /**< Enable Second Sample Point for data baudrate                             */
    uint8_t                     bEnAutoRec;               /**< Enable auto recovery after bus-off                                       */
    FLEXCAN_FifoConfigType      tRxFifoFilterCfg;         /**< Can Rx fifo Filter configuration parameter                               */
    FLEXCAN_MbConfigType        tMbCfg;                   /**< Can Tx MB and Rx MB Filter configuration parameter                       */

    /* ESR1,CTRL1,CTRL2 */
    uint8_t                     bEnErrInt;                /**< if enable can error interrupt, set 1U                                    */
    uint8_t                     bEnBusOffInt;             /**< if enable can busoff interrupt, set 1U                                   */
    uint8_t                     bEnBusOffDoneInt;         /**< if enable can busoff leaved interrupt(only occured autorecovery), set 1U */
    uint8_t                     bEnWarningInt;            /**< if enable can tx/rx warning interrupt, set 1U                            */
    FLEXCAN_PNET_ConfigType     tPnetCfg;                 /**< Pretended Network configuration for wake-up in STOP Mode                 */
} FLEXCAN_InitType;

/** @}*/


/* ################################################################################## */
/* ################################ Global Functions ################################ */

/**
 * @name  CAN api definition
 * @brief CAN api definition
 *
 * @{
 */

/**
 * @brief Get CAN Data width number for current can
 *    MBDSR0..MBDSRn
 *
 * @param pCanHandle Can Handle point
 * @return data width array number
 */
uint8_t FLEXCAN_GetDataWidthArrayLen(FLEXCAN_HandleType *pCanHandle);

/**
 * @brief Initial CAN
 *
 * @param pCanHandle Can Handle point
 * @param pInitCfg  clock, baud-rate, canfd, data length and so on.
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_Init(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg);

/**
 * @brief De-initial can instance
 *
 * @param pCanHandle Can Handle point
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_DeInit(FLEXCAN_HandleType *pCanHandle);


/**
 * @brief Start can instance
 *
 * @param pCanHandle Can Handle point
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_Start(FLEXCAN_HandleType *pCanHandle);

/**
 * @brief Stop can instance
 *
 * @param pCanHandle Can Handle point
 */
FLEXCAN_ErrorType FLEXCAN_Stop(FLEXCAN_HandleType *pCanHandle);

/**
 * @brief Transmit data, if tx disable, must call FLEXCAN_TransmitProcess after transmiting
 *
 * @param pCanHandle Can Handle point
 * @param pTxMsg contains CAN instance, CAN ID, CAN FD and CAN data.
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitData(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_TxMsgType *const pTxMsg);


/**
 * @brief Abort transmit with special transmit handler
 *
 * @param pCanHandle Can Handle point
 * @param u8TxHandle Transmit handler
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitAbort(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle);



/**
 * @brief Clear can error
 *
 * @param pCanHandle Can Handle point
 * @param pErrorInfo is error information
 * @return 0 is no error, others contains error
 */
FLEXCAN_ErrorType FLEXCAN_ClrErrorInfo(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_ErrorInfoType *const pErrorInfo);


/**
 * @brief Transfer Data length to DLC
 *
 * @param u32DataLen data length
 * @return DLC
 */
uint32_t FLEXCAN_DataLenToDlc(uint32_t u32DataLen);

/**
 * @brief Transfer DLC to Data length
 *
 * @param u32Dlc DLC Data Length
 * @return
 */
uint32_t FLEXCAN_DlcToDataLen(uint32_t u32Dlc);

/**
 * @brief Can process for interrupt
 *
 * @param pCanHandle Can Handle point
 */
void FLEXCAN_InterruptProcess(FLEXCAN_HandleType *pCanHandle);

/**
 * @brief Can process for polling
 *
 * @param pCanHandle Can Handle point
 */
void FLEXCAN_PollingProcess(FLEXCAN_HandleType *pCanHandle);
/** @}*/


/** @}*/

#endif

#endif
