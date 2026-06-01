/**
 * @file module_driver_lin.h
 * @author Flagchip
 * @brief LIN driver source code
 * @version 2.0.0
 * @date 2024-08-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-08-23    Flagchip122   N/A          First version
*********************************************************************************/

#include "module_driver_lin.h"

#if FCUART_INSTANCE_COUNT > 0U

#include "device_header.h"
#include "module_driver_fcuart.h"

/* ################################################################################## */
/* ####################################### Macro #################################### */
#ifndef LIN_DEV_ERROR_REPORT
#define LIN_DEV_ERROR_REPORT    STD_OFF
#endif

#if LIN_DEV_ERROR_REPORT == STD_ON
#define LIN_ReportDevError(func, error) ReportDevError(LIN_MODULE_ID, func, error)
#endif

/** UART Instance Number */
#define LIN_INSTANCE_NUM FCUART_INSTANCE_COUNT

/* ################################################################################## */
/* ################################### type define ################################## */

/* ################################################################################## */
/* ################################ Local Variables ################################# */

/* UART instance array */
static FCUART_Type *const s_aFCUART_InstanceTable[FCUART_INSTANCE_COUNT] = FCUART_BASE_PTRS;

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */
static LIN_StatusType LIN_DrvCalBaudrate(LIN_HandleType *pLinHandle, uint32_t *u32OverSamp,
                                         uint32_t *u32Sbr);
static LIN_NodeType   LIN_DrvCheckMode(LIN_HandleType *pLinHandle);
LOCAL_INLINE uint8_t  BIT(uint8_t A, uint8_t B);
static void           LIN_DrvHeaderHandle(LIN_HandleType *pLinHandle, uint8_t u8ReceiveByte);
static uint8_t        LIN_DrvMakeCheckSum(LIN_HandleType *pLinHandle, uint8_t *pBuf, uint8_t u8Size,
                                        uint8_t u8Pid);
static void           LIN_DrvReceiveFrameData(LIN_HandleType *pLinHandle, uint8_t u8ReceiveByte);
static void           LIN_DrvSendFrameData(LIN_HandleType *pLinHandle, uint8_t u8ReceiveByte);
static void           LIN_DrvFrameHandle(LIN_HandleType *pLinHandle);
static void           LIN_DrvWakeupHandle(LIN_HandleType *pLinHandle);

/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */

/* ################################################################################## */
/* ################################ Local Functions ################################# */

/**
 * @brief LIN instance generate baudrate value, include oversample value and sbr value.
 */
static LIN_StatusType LIN_DrvCalBaudrate(LIN_HandleType *pLinHandle, uint32_t *u32OverSamp,
                                         uint32_t *u32Sbr)
{
    LIN_StatusType tRetVal = LIN_STATUS_ERROR;
    uint32_t       u32SbrTemp;
    uint32_t       u32OverSampTemp;
    uint32_t       u32TempSmbDiff;
    uint32_t       u32SmbDiff;
    uint32_t       u32CalcSmb;
    uint32_t       u32OverSamp1;
    uint32_t       u32Sbr1;
    uint32_t       u32Smb;

    u32OverSamp1 = 4U; /* 4..32 */
    u32Smb       = pLinHandle->tStatus.pLinConfig->clockSrcFreq / pLinHandle->tStatus.pLinConfig->baudRate;

    /* sbr = srcFreq/baudrate/oversamp */
    u32Sbr1    = (uint16_t)(u32Smb / (u32OverSamp1));
    u32CalcSmb = (u32OverSamp1) * (u32Sbr1);

    if (u32CalcSmb > u32Smb)
    {
        u32SmbDiff = u32CalcSmb - u32Smb;
    }
    else
    {
        u32SmbDiff = u32Smb - u32CalcSmb;
    }

    if (u32SmbDiff != 0U)
    {

        /* loop to find the best u32OverSamp1 value possible, one that generates minimum u32SmbDiff
         * iterate through the rest of the supported values of u32OverSamp */
        for (u32OverSampTemp = 5U; u32OverSampTemp <= 32U; u32OverSampTemp++)
        {
            /* calculate the temporary u32Sbr value   */
            u32SbrTemp = (uint32_t)(u32Smb / u32OverSampTemp);
            /* calculate the baud rate based on the temporary u32OverSamp and u32Sbr values */
            u32CalcSmb = (uint32_t)(u32OverSampTemp * u32SbrTemp);

            if (u32CalcSmb > u32Smb)
            {
                u32TempSmbDiff = u32CalcSmb - u32Smb;
            }
            else
            {
                u32TempSmbDiff = u32Smb - u32CalcSmb;
            }

            if (u32TempSmbDiff < u32SmbDiff)
            {
                u32SmbDiff   = u32TempSmbDiff;
                u32OverSamp1 = u32OverSampTemp; /* update and store the best u32OverSamp value calculated */
                u32Sbr1      = u32SbrTemp;      /* update store the best u32Sbr value calculated */
            }

            /* when differ is 0U, break */
            if (u32SmbDiff == 0U)
            {
                break;
            }
        }
    }

    /* check differ */
    if (u32SmbDiff == 0U)
    {
        tRetVal = LIN_STATUS_SUCCESS;

        /* out the calculated value */
        *u32Sbr      = u32Sbr1;
        *u32OverSamp = u32OverSamp1;
    }
    else
    {
        tRetVal = LIN_STATUS_ERROR;
    }

    return tRetVal;
}

/**
 * @brief Check the node mode, slave or master.
 */
static LIN_NodeType LIN_DrvCheckMode(LIN_HandleType *pLinHandle) { return pLinHandle->tStatus.pLinConfig->nodeMode; }

/**
 * @brief Bit function.
 */
LOCAL_INLINE uint8_t BIT(uint8_t A, uint8_t B) { return (uint8_t)((A >> B) & (uint8_t)0x01U); }

/**
 * @brief Make parity value.
 */
uint8_t LIN_DrvParityMake(uint8_t PID)
{
    uint8_t parity;
    uint8_t retVal;

    parity = (uint8_t)((((0xFFU & BIT(PID, 0U)) ^ (0xFFU & BIT(PID, 1U)) ^ 
                        (0xFFU & BIT(PID, 2U)) ^ (0xFFU & BIT(PID, 4U))) << 6U) |
                        ((0xFFU ^ (BIT(PID, 1U)) ^ (0xFFU & BIT(PID, 3U)) ^ 
                        (0xFFU & BIT(PID, 4U)) ^ (0xFFU & BIT(PID, 5U))) << 7U));

    /* Making parity bits */
    retVal = (uint8_t)(PID | parity);

    return retVal;
}

/**
 * @brief Check parity value.
 */
uint8_t LIN_DrvParityCheck(uint8_t PID)
{
    uint8_t parity;
    uint8_t retVal;

    parity = (uint8_t)((((0xFFU & BIT(PID, 0U)) ^ (0xFFU & BIT(PID, 1U)) ^ 
                        (0xFFU & BIT(PID, 2U)) ^ (0xFFU & BIT(PID, 4U))) << 6U) |
                        ((0xFFU ^ (BIT(PID, 1U)) ^ (0xFFU & BIT(PID, 3U)) ^ 
                        (0xFFU & BIT(PID, 4U)) ^ (0xFFU & BIT(PID, 5U))) << 7U));

    /* If parity bits are incorrect */
    if ((PID & 0xC0U) != parity)
    {
        retVal = 0xFFU;
    }
    else
    {
        retVal = (uint8_t)(PID & 0x3FU);
    }

    return retVal;
}

/**
 * @brief Handle the frame header step by step, break field, sync field and PID field.
 */
static void LIN_DrvHeaderHandle(LIN_HandleType *pLinHandle, uint8_t u8ReceiveByte)
{

    FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];
    lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

    /* Step 1: Handle the break field state. */
    if (FCUART_HWA_GetStatus(base, FCUART_STAT_LBKDIF))
    {
        FCUART_HWA_ClearStatus(base, (uint32_t)FCUART_STAT_LBKDIF);
        /* Disable the lin break detect interrupt and clean the status flag. */
        FCUART_HWA_SetLinBreakDetectInterrupt(base, false);
        /* Disable lin detect feature, so the data can be stored to RX FIFO. */
        FCUART_HWA_SetLinBreakDetectEnable(base, false);

        /* In this state, maste need send sync field character 0x55U, slave need call callback fucntion.*/
        if (LIN_NODE_MASTER == LIN_DrvCheckMode(pLinHandle))
        {
            if (xferState->currentNodeState == LIN_NODE_STATE_SEND_BREAK_FIELD)
            {
                xferState->currentNodeState = LIN_NODE_STATE_SEND_PID;
                xferState->isBusBusy        = true;

                FCUART_HWA_SetData(base, 0x55U);
                xferState->currentNodeState = LIN_NODE_STATE_RECV_SYNC;
            }
        }
        else
        {
            xferState->isBusBusy        = true;
            xferState->currentEventId   = LIN_RECV_BREAK_FIELD_OK;
            /* call user's application. */
            if (NULL != xferState->Callback)
            {
                xferState->Callback(pLinHandle, xferState);
            }
            /* Enter next state. */
            xferState->currentNodeState = LIN_NODE_STATE_RECV_SYNC;
        }
    }
    /* Step 2: receive sync filed 0x55U. */
    else if (xferState->currentNodeState == LIN_NODE_STATE_RECV_SYNC)
    {
        /* If sync byte is 0x55U,transfer success, other failed, maybe baudrate error or protocol error. */
        if (0x55U == u8ReceiveByte)
        {
            xferState->currentEventId   = LIN_SYNC_OK;
            xferState->currentNodeState = LIN_NODE_STATE_RECV_PID;

            if (LIN_NODE_MASTER == LIN_DrvCheckMode(pLinHandle))
            {
                FCUART_HWA_SetData(base, (uint32_t)xferState->currentPid);
            }
        }
        else
        {
            xferState->isBusBusy      = false;
            xferState->currentEventId = LIN_SYNC_ERROR;

            /* Inform user the transfer status. */
            if (NULL != xferState->Callback)
            {
                xferState->Callback(pLinHandle, xferState);
            }

            /* Go to IDLE state, start a new transfer. */
            LIN_DrvGoToIdleMode(pLinHandle);
        }
    }
    /* Step 3: receive and Check PID. */
    else if (xferState->currentNodeState == LIN_NODE_STATE_RECV_PID)
    {
        /* master node only check if the receive data is match current pid, then enter next state. */
        if (LIN_NODE_MASTER == LIN_DrvCheckMode(pLinHandle))
        {
            /* Update the xfer state */
            if (u8ReceiveByte == xferState->currentPid)
            {
                xferState->currentNodeState = LIN_NODE_STATE_RECV_DATA;
                xferState->isBusBusy        = false;
                xferState->currentEventId   = LIN_PID_OK;
            }
            else
            {
                xferState->currentNodeState = LIN_NODE_STATE_IDLE;
                xferState->isBusBusy        = false;
                xferState->currentEventId   = LIN_PID_ERROR;
            }

            /* Inform user the transfer status. */
            if (NULL != xferState->Callback)
            {
                xferState->Callback(pLinHandle, xferState);
            }
        }
        else
        {
            xferState->currentId  = LIN_DrvParityCheck(u8ReceiveByte);
            xferState->currentPid = u8ReceiveByte;

            /* Update xfer state. */
            if (0xFFU == xferState->currentId)
            {
                xferState->currentNodeState = LIN_NODE_STATE_IDLE;
                xferState->isBusBusy        = false;
                xferState->currentEventId   = LIN_PID_ERROR;
            }
            else
            {
                xferState->currentNodeState = LIN_NODE_STATE_RECV_DATA;
                xferState->isBusBusy        = false;
                xferState->currentEventId   = LIN_PID_OK;
            }

            /* Inform user the transfer status. */
            if (NULL != xferState->Callback)
            {
                xferState->Callback(pLinHandle, xferState);
            }
        }
    }
    else
    {
        /* Misra check */
    }
}


/**
 * @brief Make checksum byte
 */
static uint8_t LIN_DrvMakeCheckSum(LIN_HandleType *pLinHandle, uint8_t *pBuf, uint8_t u8Size, uint8_t u8Pid)
{
    lin_config_t   *pConfig     = pLinHandle->tStatus.pLinConfig;
    uint16_t        u16Checksum = 0U;
    uint8_t         u8Length    = 0U;

    if ((pConfig->numOfClassicPID != 0U))
    {
        if (pConfig->classicPID != NULL)
        {
            for (uint8_t i = 0U; i < pConfig->numOfClassicPID; i++)
            {
                if ((u8Pid & 0x3Fu) == (pConfig->classicPID[i] & 0x3Fu))
                {
                    u8Pid = 0U;
                    break;
                }
            }
        }
    }

    /* For PID is 0x3C (ID 0x3C) or 0x7D (ID 0x3D) or 0xFE (ID 0x3E) or 0xBF (ID 0x3F)*/
    if ((0x3CU == u8Pid) || (0x7DU == u8Pid) || (0xFEU == u8Pid) || (0xBFU == u8Pid))
    {
        u8Pid = 0U;
    }

    u16Checksum = (uint16_t)(u16Checksum + u8Pid);

    for (u8Length = 0U; u8Length < u8Size; u8Length++)
    {
        u16Checksum = (uint16_t)(u16Checksum + *pBuf);
        pBuf++;
        if (u16Checksum > 0xFFU)
        {
            u16Checksum = (uint16_t)(u16Checksum - 0xFFU);
        }
    }

    return (uint8_t)(~u16Checksum);
}

/**
 * @brief receive frame data in IRQ handler.
 */
static void LIN_DrvReceiveFrameData(LIN_HandleType *pLinHandle, uint8_t u8ReceiveByte)
{
    lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

    xferState->cntByte++;

    if (xferState->cntByte < xferState->rxSize)
    {
        *(xferState->rxBuff) = u8ReceiveByte;
        xferState->rxBuff++;
    }
    /* Checksum data. */
    else if (xferState->cntByte == xferState->rxSize)
    {
        xferState->checkSum = u8ReceiveByte;
        xferState->rxBuff -= (xferState->rxSize - 1U);

        /* Checksum compared. */
        if (xferState->checkSum == LIN_DrvMakeCheckSum(pLinHandle, xferState->rxBuff,
                                    (uint8_t)(xferState->rxSize - 1U), xferState->currentPid))
        {
            xferState->currentNodeState = LIN_NODE_STATE_RECV_DATA_COMPLETED;
            xferState->currentEventId   = LIN_RX_COMPLETED;
        }
        else
        {
            xferState->currentEventId = LIN_CHECKSUM_ERROR;
        }

        /* call user's application. */
        if (NULL != xferState->Callback)
        {
            xferState->Callback(pLinHandle, xferState);
        }

        /* Go to IDLE state, start a new transfer. */
        LIN_DrvGoToIdleMode(pLinHandle);
    }
    /* Maybe error occurred. */
    else
    {
        /* MISRA-2012 check. */
    }
}

/**
 * @brief This API will send frame data, due to the LIN node will receive the byte sent by itself,
 *        we will also check the receive data while sending bytes.
 */
static void LIN_DrvSendFrameData(LIN_HandleType *pLinHandle, uint8_t u8ReceiveByte)
{
    lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
    FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];

    if (xferState->cntByte < xferState->txSize)
    {
        /* The received byte should be the byte just send. */
        if (u8ReceiveByte != *(xferState->txBuff - 1))
        {
            xferState->currentEventId = LIN_READBACK_ERROR;

            /* call user's application. */
            if (NULL != xferState->Callback)
            {
                xferState->Callback(pLinHandle, xferState);
            }
        }
        else
        {
            if (xferState->cntByte == (xferState->txSize - 1U))
            {
                FCUART_HWA_SetData(base, (uint32_t)xferState->checkSum);
            }
            else
            {
                FCUART_HWA_SetData(base, (uint32_t) * (xferState->txBuff));
            }

            xferState->txBuff++;
            xferState->cntByte++;
        }
    }
    /* Last byte received, no need to send anything. */
    else if (xferState->cntByte == xferState->txSize)
    {
        if (u8ReceiveByte != xferState->checkSum)
        {
            xferState->currentEventId = LIN_READBACK_ERROR;
        }
        else
        {
            xferState->currentEventId = LIN_TX_COMPLETED;
        }

        /* call user's application. */
        if (NULL != xferState->Callback)
        {
            xferState->Callback(pLinHandle, xferState);
        }

        /* Go to IDLE state, start a new transfer. */
        LIN_DrvGoToIdleMode(pLinHandle);
    }
    else
    {
        /* MISRA Check. */
    }
}

/**
 * @brief Handle the frame data, sending or receiving frame data.
 */
static void LIN_DrvFrameHandle(LIN_HandleType *pLinHandle)
{
    lin_xfer_state_t *xferState     = pLinHandle->tStatus.pLinXfer;
    FCUART_Type      *base          = s_aFCUART_InstanceTable[pLinHandle->eInstance];
    uint8_t           u8ReceiveByte = 0U;

    if (FCUART_HWA_GetStatus(base, FCUART_STAT_RDRFF))
    {
        u8ReceiveByte = FCUART_HWA_GetData(base);
    }

    /* Handle node to recive frame data. */
    if (LIN_NODE_STATE_RECV_DATA == xferState->currentNodeState)
    {
        LIN_DrvReceiveFrameData(pLinHandle, u8ReceiveByte);
    }
    /* Handle node to send frame data. */
    else if (LIN_NODE_STATE_SEND_DATA == xferState->currentNodeState)
    {
        LIN_DrvSendFrameData(pLinHandle, u8ReceiveByte);
    }
    /* Handle header. */
    else
    {
        LIN_DrvHeaderHandle(pLinHandle, u8ReceiveByte);
    }
}

/**
 * @brief This API will handle wakeup signal, and calculate the value wakeup signal send.
 *        Actually, step 1, FCUART will wait a low level in RX pin, and than inverse the RX data
 *        while the rise edge is coming, another interrupt will be triggered, the time between this
 *        two interrupt is the wakeup time value.
 */
static void LIN_DrvWakeupHandle(LIN_HandleType *pLinHandle)
{
    lin_xfer_state_t *xferState    = pLinHandle->tStatus.pLinXfer;
    lin_config_t     *xLinCfg      = pLinHandle->tStatus.pLinConfig;
    FCUART_Type      *base         = s_aFCUART_InstanceTable[pLinHandle->eInstance];
    uint32_t          s_wakeupTime = 0U;

    /* Clear status.*/
    FCUART_HWA_ClearStatus(base, (uint32_t)FCUART_STAT_RPAEIF);

    /* Step 1, record the first receive active time. */
    if (false == FCUART_HWA_GetReceiveDataInverse(base))
    {
        /* Call the uer time value call function. */
        if (NULL != xLinCfg->getIntervalTimeValueCallback)
        {
            xLinCfg->getIntervalTimeValueCallback(&s_wakeupTime);
        }

        /* Chang the receive data inverse, and receive the next interrupt. */
        FCUART_HWA_SetReceiveDataInverse(base, true);
    }
    /* Step 2. calculate the wakeup time. */
    else
    {
        FCUART_HWA_SetReceiveDataInverse(base, false);

        /* Call the uer time value call function. */
        if (NULL != xLinCfg->getIntervalTimeValueCallback)
        {
            xLinCfg->getIntervalTimeValueCallback(&s_wakeupTime);
        }

        if (150U < s_wakeupTime)
        {
            xferState->currentEventId = LIN_WAKEUP_SIGNAL;

            /* call user's application. */
            if (NULL != xferState->Callback)
            {
                xferState->Callback(pLinHandle, xferState);
            }

            /* Enter IDLE state to prepare next transfer. */
            LIN_DrvGoToIdleMode(pLinHandle);
        }
    }
}

/* ################################################################################## */
/* ################################ Global Functions ################################ */

/**
 * @brief Init the LIN instance for LIN network. This API will help initialize the FCUART to expect state,
 *        but will nots start the TX&RX function, if users want to start the LIN protocol transfer, please
 *        call the function LIN_DrvStart() after this API is called.
 *
 * @param pLinHandle    LIN processing handle
 * @param pConfig     Configuration for LIN hardware, must not be null.
 * @return operation status:
 *         - LIN_STATUS_SUCCESS  : operation is successfully.
 *         - LIN_STATUS_USEED    : The instance has been used, user should use another instance or de-initialize this instance
 * firstly.
 *         - LIN_STATUS_ERROR    : the baudrate has not been set successfully.
 */
LIN_StatusType LIN_DrvInit(LIN_HandleType *pLinHandle, lin_config_t *pConfig)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_INIT_ID, LIN_E_PARAM_INSTANCE);
    }
    else if(pConfig == NULL)
    {
        LIN_ReportDevError(LIN_INIT_ID, LIN_E_PARAM_POINTER);
    }
     /* Check the LIN instance used or not. */
    else if(pLinHandle->tStatus.u8InstanceUsed == 1U)
    {
        LIN_ReportDevError(LIN_INIT_ID, LIN_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        uint8_t        u8Index         = pLinHandle->eInstance;
        LIN_StatusType tRetVal         = LIN_STATUS_SUCCESS;
        FCUART_Type   *base            = s_aFCUART_InstanceTable[u8Index];
        uint32_t       u32BaudRegValue = 0U;
        uint32_t       u32CtrlRegValue = 0U;
        uint32_t       u32StatRegValue = 0U;
        uint32_t       u32Sbr          = 0U;
        uint32_t       u32OverSamp     = 0U;

        pLinHandle->tStatus.pLinConfig = pConfig;

        /* Reset the hardware LIN instance to expect state. */
        FCUART_HWA_SoftwareReset(base);

        /* Set BAUD register configuration:
        * - calculate the baudrate generated value.
        * - LIN break detect interrupt enable;
        * - RX pin active edge disabled, for checking the wakeup signal;
        * - Stop bit set to 1;
        */
        tRetVal = LIN_DrvCalBaudrate(pLinHandle, &u32OverSamp, &u32Sbr);
        u32BaudRegValue |= FCUART_BAUD_OVR_SAMP(u32OverSamp - 1U) | FCUART_BAUD_BEDGE_SAMP(
                            1U) | FCUART_BAUD_SBR(u32Sbr);
        FCUART_HWA_SetBaud(base, u32BaudRegValue);
        FCUART_HWA_SetLinBreakDetectInterrupt(base, true);

        /* Set LIN break send and detect to 13 bits minimum. If in slave node, only enable detect feature. */
        u32StatRegValue |= FCUART_STAT_BCGL(1U) | FCUART_STAT_LBKDE(0U);
        FCUART_HWA_WriteClearSTAT(base, u32StatRegValue);

        /* Set CTRL register configuration:
        * - Enable frame error interrupt;
        * - Enable receive interrupt;
        * - 8 bits transfer mode enabled;
        * - Parity check mode disable;
        */
        u32CtrlRegValue |= FCUART_CTRL_ORIE(1)| FCUART_CTRL_NEIE(1) | FCUART_CTRL_FEIE(1U) | FCUART_CTRL_RIE(1U) | FCUART_CTRL_BMSEL(
                            0U) | FCUART_CTRL_PE(0U);
        FCUART_HWA_SetCtrl(base, u32CtrlRegValue);

        /* Do not use the FIFO feature. the baudrate of LIN protocol is not too high, so do not use fifo feature. */
        FCUART_HWA_SetFifo(base, 0U);

        /* FIFO watermark set to 0. */
        FCUART_HWA_SetWaterMark(base, 0U);

        /* Update the instance used state. */
        pLinHandle->tStatus.u8InstanceUsed = 1U;

        LIN_DrvStart(pLinHandle, &(pConfig->g_xferState));

        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief De-Init the LIN instance used by LIN network.
 *        This API will help disable the fcuart interrupts and stop the TX/RX transfer.
 *
 * @return operation status:
 *         - LIN_STATUS_SUCCESS  : operation is successfully.
 *         - LIN_STATUS_NOT_INIT : The instance has not been initialized.
 */
void LIN_DrvDeInit(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DEINIT_ID, LIN_E_PARAM_INSTANCE);
    }
     /* Check the LIN instance used or not. */
    else if(pLinHandle->tStatus.u8InstanceUsed == 0U)
    {
        LIN_ReportDevError(LIN_DEINIT_ID, LIN_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        uint8_t           u8LinIndex = pLinHandle->eInstance;
        FCUART_Type       *base      = s_aFCUART_InstanceTable[u8LinIndex];
        lin_xfer_state_t  *xferState = pLinHandle->tStatus.pLinXfer;

        /* Check if still bytes need to be send or receive. wait the protocol is not busy. */
        while (xferState->isBusBusy)
        {
        }

        /* Update LIN instance to initialize state. */
        pLinHandle->tStatus.pLinConfig     = NULL;
        pLinHandle->tStatus.pLinXfer       = NULL;
        pLinHandle->tStatus.u8InstanceUsed = 0U;

        /* Stop TX/TX function and FCUART instance. */
        FCUART_HWA_SetTxTransfer(base, false);
        FCUART_HWA_SetRxTransfer(base, false);

        /* Reset the FCUART instance. */
        FCUART_HWA_SoftwareReset(base);

#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief Help users get the default configuration of LIN node. users should provide the configuration structure
 *        in app code, and transfer the ptr address to driver code. uses can also set this parameters in the application code
 *        as designed.
 *
 * @param u8NodeMode  LIN node mode select, 0 for slave mode and 1 for master mode.
 * @param pConfig     default configuration for LIN node, must not be null.
 */
void LIN_DrvGetDefaultConfig(LIN_NodeType eNodeMode, lin_config_t *pConfig)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    /* Check NUll ptr for bus error. */
    if(pConfig == NULL)
    {
        LIN_ReportDevError(LIN_GET_DEFAULT_CFG_ID, LIN_E_PARAM_POINTER);
    }
    else
    {
#endif
        pConfig->u8LinIndex                   = 0U;
        pConfig->nodeMode                     = eNodeMode; /**< Node mode as Master node or Slave node. 0: slave 1: master */
        pConfig->baudRate                     = 19200U;    /**< baudrate configurations for LIN protocol. */
        pConfig->getIntervalTimeValueCallback = NULL;      /**< Callback function to get time interval in nanoseconds */
        pConfig->classicPID                   = NULL;      /**< List of PIDs use classic checksum */
        pConfig->numOfClassicPID              = 0U;        /**< Number of PIDs use classic checksum */
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
void LIN_DrvStart(LIN_HandleType *pLinHandle, lin_xfer_state_t *pXferState)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DEINIT_ID, LIN_E_PARAM_INSTANCE);
    }
    /* Check NUll ptr for bus error. */
    else if(pXferState == NULL)
    {
        LIN_ReportDevError(LIN_DRV_START_ID, LIN_E_PARAM_POINTER);
    }
    /* Check the LIN instance used or not. */
    else if(pLinHandle->tStatus.u8InstanceUsed == 0U)
    {
        LIN_ReportDevError(LIN_DEINIT_ID, LIN_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        uint8_t         u8LinIndex  = pLinHandle->eInstance;
        FCUART_Type     *base       = s_aFCUART_InstanceTable[u8LinIndex];

        /* Register transfer ptr. */
        pLinHandle->tStatus.pLinXfer = pXferState;

        /* Initialize the xfer state of LIN transfer. */
        pXferState->isTxBusy           = false;
        pXferState->isRxBusy           = false;
        pXferState->isBusBusy          = false;
        pXferState->isRxBlocking       = false;
        pXferState->isTxBlocking       = false;
        pXferState->timeoutCounterFlag = false;
        pXferState->timeoutCounter     = 0U;
        pXferState->currentNodeState   = LIN_NODE_STATE_IDLE;
        pXferState->currentEventId     = LIN_NO_EVENT;

        FCUART_HWA_SetTxTransfer(base, true);
        FCUART_HWA_SetRxTransfer(base, true);

        /* Slave will enter the IDEL state, and listening the protocol all time, waiting for a break files. */
        if (LIN_NODE_SLAVE == pLinHandle->tStatus.pLinConfig->nodeMode)
        {
            /* Start hardware. */
            FCUART_HWA_SetLinBreakDetectEnable(base, true);
            FCUART_HWA_SetLinBreakDetectInterrupt(base, true);
        }

#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
LIN_StatusType LIN_DrvInstallUserCallback(LIN_HandleType *pLinHandle, lin_callback_t callback)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_INSTALL_UAER_CALLBACK_ID, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        LIN_StatusType    tRetVal   = LIN_STATUS_ERROR;
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

        if (NULL == xferState)
        {
            tRetVal = LIN_STATUS_NOT_INIT;
        }
        else
        {
            xferState->Callback = callback;
            tRetVal             = LIN_STATUS_SUCCESS;
        }

        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
LIN_StatusType LIN_DrvSendHeader(LIN_HandleType *pLinHandle, uint8_t u8Id)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_SEND_HEADER_ID, LIN_E_PARAM_INSTANCE);
    }
    /* Check NUll ptr for bus error. */
    else if(pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_SEND_HEADER_ID, LIN_E_PARAM_POINTER);
    }
    else
    {
#endif
        FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
        LIN_StatusType    tRetVal   = LIN_STATUS_SUCCESS;

        /* Check node state. */
        if (xferState->currentNodeState == LIN_NODE_STATE_UNINIT)
        {
            tRetVal = LIN_STATUS_NOT_INIT;
        }
        /* Slave node can not send header. */
        else if (pLinHandle->tStatus.pLinConfig->nodeMode == LIN_NODE_SLAVE)
        {
            tRetVal = LIN_STATUS_UNSUPPORTED;
        }
        else
        {
            if (xferState->isBusBusy == true)
            {
                tRetVal = LIN_STATUS_BUSY;
            }
            else
            {
                /* Update node state. */
                xferState->currentId        = u8Id;
                xferState->currentPid       = LIN_DrvParityMake(u8Id);
                xferState->currentEventId   = LIN_NO_EVENT;
                xferState->currentNodeState = LIN_NODE_STATE_SEND_BREAK_FIELD;
                xferState->isBusBusy        = false;

                /* Start hardware. */
                FCUART_HWA_SetLinBreakDetectEnable(base, true);
                FCUART_HWA_SetLinBreakDetectInterrupt(base, true);

                /* Send a break filed to protocol. */
                FCUART_HWA_SendBreakField(base);
            }
        }
        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
LIN_StatusType LIN_DrvSendFrameBlocking(LIN_HandleType *pLinHandle, 
                                        uint8_t *pTxBuf,
                                        uint8_t u8Length,
                                        uint32_t u32TimeOut)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_SEND_FRAME_BLOCKING, LIN_E_PARAM_INSTANCE);
    }
    /* Check NUll ptr for bus error. */
    else if(pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_SEND_FRAME_BLOCKING, LIN_E_PARAM_ERROR_STATE);
    }
    else if((pTxBuf == NULL) || (u8Length == 0))
    {
        LIN_ReportDevError(LIN_DRV_SEND_FRAME_BLOCKING, LIN_E_PARAM_POINTER);
    }
    else
    {
#endif
        uint8_t          u8LinIndex = pLinHandle->eInstance;
        FCUART_Type      *base      = s_aFCUART_InstanceTable[u8LinIndex];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
        LIN_StatusType   tRetVal    = LIN_STATUS_SUCCESS;

        /* Check node state. */
        if (xferState->currentNodeState == LIN_NODE_STATE_UNINIT)
        {
            tRetVal = LIN_STATUS_NOT_INIT;
        }
        else
        {
            if (xferState->isBusBusy)
            {
                tRetVal = LIN_STATUS_BUSY;
            }
            else
            {
                xferState->currentNodeState = LIN_NODE_STATE_SEND_DATA;
                xferState->currentEventId   = LIN_NO_EVENT;

                xferState->txBuff             = pTxBuf;
                xferState->txSize             = (uint8_t)(u8Length + 1U);
                xferState->cntByte            = 0U;
                xferState->checkSum           = LIN_DrvMakeCheckSum(pLinHandle, pTxBuf, u8Length,
                                                                    xferState->currentPid);
                xferState->isTxBusy           = true;
                xferState->isBusBusy          = true;
                xferState->isTxBlocking       = true;
                xferState->timeoutCounter     = u32TimeOut;
                xferState->timeoutCounterFlag = false;

                FCUART_HWA_SetLinBreakDetectEnable(base, false);
                FCUART_HWA_SetData(base, (uint32_t) * (xferState->txBuff));

                xferState->txBuff++;
                xferState->cntByte++;

                /* Waiting for teansfer complete. */
                while (xferState->isTxBusy == true)
                {
                    if (xferState->timeoutCounterFlag == true)
                    {
                        tRetVal = LIN_STATUS_TIMEOUT;
                        break;
                    }
                }

                LIN_DrvGoToIdleMode(pLinHandle);
            }
        }
        return tRetVal;

#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This API will help users send a frame data through LIN protocol, this API will return immediately.
 *        data will be stored in txbuffer, users can check the transmit status while data is sending.
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
LIN_StatusType LIN_DrvSendFrameNonBlocking(LIN_HandleType *pLinHandle, uint8_t *pTxBuf, uint8_t u8Length)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_SEND_FRAME_NON_BLOCKING, LIN_E_PARAM_INSTANCE);
    }
    /* Check NUll ptr for bus error. */
    else if(pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_SEND_FRAME_NON_BLOCKING, LIN_E_PARAM_ERROR_STATE);
    }
    else if((pTxBuf == NULL) || (u8Length == 0))
    {
        LIN_ReportDevError(LIN_DRV_SEND_FRAME_NON_BLOCKING, LIN_E_PARAM_POINTER);
    }
    else
    {
#endif
        uint8_t          u8LinIndex = pLinHandle->eInstance;
        FCUART_Type      *base      = s_aFCUART_InstanceTable[u8LinIndex];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
        LIN_StatusType   tRetVal    = LIN_STATUS_SUCCESS;

        /* Check node state. */
        if (xferState->currentNodeState == LIN_NODE_STATE_UNINIT)
        {
            tRetVal = LIN_STATUS_NOT_INIT;
        }
        else
        {
            if (xferState->isBusBusy)
            {
                tRetVal = LIN_STATUS_BUSY;
            }
            else
            {
                xferState->currentNodeState = LIN_NODE_STATE_SEND_DATA;
                xferState->currentEventId   = LIN_NO_EVENT;

                xferState->txBuff    = pTxBuf;
                xferState->txSize    = (uint8_t)(u8Length + 1U);
                xferState->cntByte   = 0U;
                xferState->checkSum  = LIN_DrvMakeCheckSum(pLinHandle, pTxBuf, u8Length, xferState->currentPid);
                xferState->isTxBusy  = true;
                xferState->isBusBusy = true;

                FCUART_HWA_SetLinBreakDetectEnable(base, false);
                FCUART_HWA_SetData(base, (uint32_t) * (xferState->txBuff));

                xferState->txBuff++;
                xferState->cntByte++;
            }
        }

        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
LIN_StatusType LIN_DrvGetTransmitStatus(LIN_HandleType *pLinHandle, uint8_t *pRemainBytes)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_GET_TRANSMIT_STATUS, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        LIN_StatusType    tRetVal   = LIN_STATUS_SUCCESS;
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

        /* Return the remaining byte inlcude checksun byte. */
        *pRemainBytes = (uint8_t)(xferState->txSize - xferState->cntByte);

        /* Check LIN node status. */
        if (xferState->timeoutCounterFlag == true)
        {
            tRetVal = LIN_STATUS_TIMEOUT;
        }
        else if (xferState->isTxBusy == true)
        {
            tRetVal = LIN_STATUS_BUSY;
        }
        else
        {
        }

        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
LIN_StatusType LIN_DrvReceiveFrameBlocking(LIN_HandleType *pLinHandle, 
                                            uint8_t *pRxBuf, 
                                            uint8_t u8Length,
                                            uint32_t u32TimeOut)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_RECEIVE_FRAME_BLOCKING, LIN_E_PARAM_INSTANCE);
    }
    /* Check NUll ptr for bus error. */
    else if(pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_RECEIVE_FRAME_BLOCKING, LIN_E_PARAM_ERROR_STATE);
    }
    else if((pRxBuf == NULL) || (u8Length == 0))
    {
        LIN_ReportDevError(LIN_DRV_RECEIVE_FRAME_BLOCKING, LIN_E_PARAM_POINTER);
    }
    else
    {
#endif
        FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
        LIN_StatusType   tRetVal    = LIN_STATUS_SUCCESS;

        /* Check node state. */
        if (xferState->currentNodeState == LIN_NODE_STATE_UNINIT)
        {
            tRetVal = LIN_STATUS_NOT_INIT;
        }
        else
        {
            if (xferState->isBusBusy)
            {
                tRetVal = LIN_STATUS_BUSY;
            }
            else
            {
                xferState->currentNodeState = LIN_NODE_STATE_RECV_DATA;
                xferState->currentEventId   = LIN_NO_EVENT;

                xferState->rxBuff             = pRxBuf;
                xferState->rxSize             = (uint8_t)(u8Length + 1U);
                xferState->cntByte            = 0U;
                xferState->isRxBusy           = true;
                xferState->isBusBusy          = true;
                xferState->isRxBlocking       = true;
                xferState->timeoutCounter     = u32TimeOut;
                xferState->timeoutCounterFlag = false;

                /* Waiting for complete. */
                while (xferState->isRxBusy == true)
                {
                    if (true == xferState->timeoutCounterFlag)
                    {
                        tRetVal = LIN_STATUS_TIMEOUT;
                        break;
                    }
                }

                FCUART_HWA_SetLinBreakDetectEnable(base, false);
            }
        }

        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This API will help users receive frame data through LIN protocol, this API will return immediately.
 *        data will be stored in rxbuffer, users can check the receive status while using this API.
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
LIN_StatusType LIN_DrvReceiveFrameNonBlocking(LIN_HandleType *pLinHandle, uint8_t *pRxBuf, uint8_t u8Length)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_RECEIVE_FRAME_NON_BLOCKING, LIN_E_PARAM_INSTANCE);
    }
    /* Check NUll ptr for bus error. */
    else if(pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_RECEIVE_FRAME_NON_BLOCKING, LIN_E_PARAM_ERROR_STATE);
    }
    else if((pRxBuf == NULL) || (u8Length == 0))
    {
        LIN_ReportDevError(LIN_DRV_RECEIVE_FRAME_NON_BLOCKING, LIN_E_PARAM_POINTER);
    }
    else
    {
#endif
        FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
        LIN_StatusType    tRetVal   = LIN_STATUS_SUCCESS;

        /* Check node state. */
        if (xferState->currentNodeState == LIN_NODE_STATE_UNINIT)
        {
            tRetVal = LIN_STATUS_NOT_INIT;
        }
        else
        {
            if (xferState->isBusBusy)
            {
                tRetVal = LIN_STATUS_BUSY;
            }
            else
            {
                xferState->currentNodeState = LIN_NODE_STATE_RECV_DATA;
                xferState->currentEventId   = LIN_NO_EVENT;

                xferState->rxBuff    = pRxBuf;
                xferState->rxSize    = (uint8_t)(u8Length + 1U);
                xferState->cntByte   = 0U;
                xferState->isRxBusy  = true;
                xferState->isBusBusy = true;

                FCUART_HWA_SetLinBreakDetectEnable(base, false);
            }
        }

        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This API will help users get the LIN transfer status while data is receiving. and will also
 *        help user get remainning byte in transfer still need receiving in buffer.
 *
 * @param pLinHandle    LIN processing handle
 * @param pRemainBytes  Address to be stored the remain byte value, should not be NULL.
 * @return              operation status:
 *                      - LIN_STATUS_TIMEOUT  : node transfer timeout occurred.
 *                      - LIN_STATUS_SUCCESS  : transfer complete.
 *                      - LIN_STATUS_BUSY     : transfer is going, could read the remain byte in pRemainBytes.
 */
LIN_StatusType LIN_DrvGetReceiveStatus(LIN_HandleType *pLinHandle, uint8_t *pRemainBytes)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_GET_RECEIVE_STATUS, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        LIN_StatusType    tRetVal   = LIN_STATUS_SUCCESS;
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

        /* Return the remaining byte inlcude checksun byte. */
        *pRemainBytes = (uint8_t)(xferState->rxSize - xferState->cntByte);

        if (xferState->timeoutCounterFlag == true)
        {
            tRetVal = LIN_STATUS_TIMEOUT;
        }
        else if (xferState->isRxBusy == true)
        {
            tRetVal = LIN_STATUS_BUSY;
        }
        else
        {
        }
        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief Abort transfer both sending or receiving data, actually, call this APU will enter IDLE state.
 *        will stop end and receive even data transfer is on going.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 */
void LIN_DrvAbortTransfer(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_ABORT_TRANSFER, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        /* Update the LIN state to IDLE state directly. */
        LIN_DrvGoToIdleMode(pLinHandle);

#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
void LIN_DrvGoToSleepMode(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_GOTOSLEEP_MODE, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

        /* Update software status. */
        xferState->currentEventId   = LIN_NO_EVENT;
        xferState->currentNodeState = LIN_NODE_STATE_SLEEP_MODE;
        xferState->isBusBusy        = false;
        xferState->isRxBusy         = false;
        xferState->isTxBusy         = false;

        /* Disable all enabled interrupt except receive active interrupt. */
        FCUART_HWA_SetLinBreakDetectEnable(base, true);
        FCUART_HWA_SetLinBreakDetectInterrupt(base, false);
        FCUART_HWA_DisableInterrupt(base, (uint32_t)(FCUART_INT_CTRL_ORIE | FCUART_INT_CTRL_NEIE | FCUART_INT_CTRL_FEIE | FCUART_INT_CTRL_PEIE));
        FCUART_HWA_DisableInterrupt(base, (uint32_t)FCUART_INT_CTRL_RIE);
        FCUART_HWA_SetReceiveActiveInterrupt(base, true);

#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief THis API will help confgure the mode into IDLE state. In IDLE state, node will enable receive interrupt and break
 *        field detect interrupt, slave node will wait the break field from master node, master node will prepare to send a
 *        new break filed to start a new frame.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 */
void LIN_DrvGoToIdleMode(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_GOTOIDLE_MODE, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

        /* Update software status. */
        xferState->cntByte            = 0U;
        xferState->txSize             = 0U;
        xferState->rxSize             = 0U;
        xferState->isBusBusy          = false;
        xferState->isRxBusy           = false;
        xferState->isTxBusy           = false;
        xferState->isTxBlocking       = false;
        xferState->isRxBlocking       = false;
        xferState->currentId          = 0U;
        xferState->currentPid         = 0U;
        xferState->currentEventId     = LIN_NO_EVENT;
        xferState->currentNodeState   = LIN_NODE_STATE_IDLE;
        xferState->timeoutCounter     = 0U;
        xferState->timeoutCounterFlag = false;

        /* Update hardware configration.
        * 1. Enable LIN break detect interrupr;
        * 2. Enable frame error interrupt.
        * 3. Enable receive interrupt;
        */
        FCUART_HWA_WriteClearSTAT(base, FCUART_STAT_LBKDIF | FCUART_STAT_RPAEIF | FCUART_STAT_FEF);
        FCUART_HWA_SetLinBreakDetectEnable(base, true);
        FCUART_HWA_SetLinBreakDetectInterrupt(base, true);
        FCUART_HWA_EnableInterrupt(base, (uint32_t)(FCUART_INT_CTRL_ORIE | FCUART_INT_CTRL_NEIE | FCUART_INT_CTRL_FEIE | FCUART_INT_CTRL_PEIE));
        FCUART_HWA_EnableInterrupt(base, (uint32_t)FCUART_INT_CTRL_RIE);
        FCUART_HWA_SetReceiveActiveInterrupt(base, false);
        FCUART_HWA_SetReceiveDataInverse(base, false);

#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

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
LIN_StatusType LIN_DrvSendWakeupSignal(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_SEND_WAKEUP_SIGNAL, LIN_E_PARAM_INSTANCE);
    }
    else if (pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_SEND_WAKEUP_SIGNAL, LIN_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        FCUART_Type      *base      = s_aFCUART_InstanceTable[pLinHandle->eInstance];
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
        LIN_StatusType    tRetVal   = LIN_STATUS_SUCCESS;

        /* Check node state. */
        if (xferState->currentNodeState == LIN_NODE_STATE_UNINIT)
        {
            tRetVal = LIN_STATUS_NOT_INIT;
        }
        else
        {
            if (xferState->isBusBusy == true)
            {
                tRetVal = LIN_STATUS_BUSY;
            }
            else
            {
                if (pLinHandle->tStatus.pLinConfig->baudRate > 10000U)
                {
                    /* Wakeup signal will be range from 400us to 800us depend on baudrate, 0x80U */
                    FCUART_HWA_SetData(base, 0x00U);
                }
                else
                {
                    /* Wakeup signal will be range from 400us to 4ms depend on baudrate, 0xF8U */
                    FCUART_HWA_SetData(base, 0xF8U);
                }

                tRetVal = LIN_STATUS_SUCCESS;
            }
        }

        return tRetVal;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief Get the LIN node state.
 *
 * @param pLinHandle    LIN processing handle
 * @return            the node current state, refer to @lin_node_state_t
 */
lin_node_state_t LIN_DrvGetNodeState(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_GET_NODE_STATE, LIN_E_PARAM_INSTANCE);
    }
    else if (pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_GET_NODE_STATE, LIN_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif

        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;
        return xferState->currentNodeState;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This API should be called by user's application code, and the timeout periods should be 1ms once.
 *        Better to provide a timer IRQhandler to call this APIs 1ms onces. internal timeout feature will
 *        use this API t o handle the time counter.
 *
 * @param pLinHandle    LIN processing handle
 * @return            operation status:
 *                    - LIN_STATUS_SUCCESS  : operation is successfully.
 */
void LIN_DrvTimeOutService(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_TIMEOUT_SERVICE, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif

        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

        if ((LIN_NODE_STATE_SEND_DATA == (xferState->currentNodeState)) || (LIN_NODE_STATE_RECV_DATA == (xferState->currentNodeState)))
        {
            /* time counter down to 0, timeout occurred. */
            if (0U == xferState->timeoutCounter)
            {
                xferState->timeoutCounterFlag = true;

                /* If send data blocking feature is enabled. anc callback is not NULL. */
                xferState->currentEventId = LIN_TIMEOUT;

                if (NULL != xferState->Callback)
                {
                    xferState->Callback(pLinHandle, xferState);
                }

                LIN_DrvGoToIdleMode(pLinHandle);
            }
            else
            {
                xferState->timeoutCounter--;
            }
        }

#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This API will help users set the timeout counter with one API, users should use this feature with
 *        LIN_DrvTimeOutService() called every fixed time.
 *
 * @param pLinHandle    LIN processing handle
 * @param u32TimeOutValue  Timeout value.
 * @return                 operation status:
 *                         - LIN_STATUS_SUCCESS  : operation is successfully.
 *                         - LIN_STATUS_NOT_INIT : Instance required is not initialized.
 */
void LIN_DrvSetTimeOutCounter(LIN_HandleType *pLinHandle, uint32_t u32TimeOutValue)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_SET_TIMEOUT_COUNTER, LIN_E_PARAM_INSTANCE);
    }
    else if(pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_SET_TIMEOUT_COUNTER, LIN_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

        xferState->timeoutCounterFlag = false;
        xferState->timeoutCounter     = u32TimeOutValue;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This API will help users get the Node timeout flag status.
 *
 * @param pLinHandle    LIN processing handle
 * @return            true for timeout occurred, false indicate no timeout.
 */
bool LIN_DrvGetTimeOutFlag(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_GET_TIMEOUT_FLAG, LIN_E_PARAM_INSTANCE);
    }
    else if(pLinHandle->tStatus.pLinXfer == NULL)
    {
        LIN_ReportDevError(LIN_DRV_GET_TIMEOUT_FLAG, LIN_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        return pLinHandle->tStatus.pLinXfer->timeoutCounterFlag;
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This is LIN IRQ routine code, uses should call this in the FCUART IRQhandler code. please must implement
 *        the feature in application code.
 *
 * @param pLinHandle    LIN processing handle
 */
void LIN_DrvIRQHandler(LIN_HandleType *pLinHandle)
{
#if LIN_DEV_ERROR_REPORT == STD_ON
    if(pLinHandle->eInstance >= LIN_INSTANCE_NUM)
    {
        LIN_ReportDevError(LIN_DRV_IRQ_HANDLE, LIN_E_PARAM_INSTANCE);
    }
    else
    {
#endif
    uint8_t          u8LinIndex = pLinHandle->eInstance;
    FCUART_Type      *base      = s_aFCUART_InstanceTable[u8LinIndex];
    lin_xfer_state_t *xferState = pLinHandle->tStatus.pLinXfer;

    /* Handle the wakeup feature by protocol. */
    if (true == FCUART_HWA_GetReceiveActiveInterrupt(base))
    {
        if (FCUART_HWA_GetStatus(base, FCUART_STAT_RPAEIF))
        {
            LIN_DrvWakeupHandle(pLinHandle);
        }
    }
    /* Data or lin break detect has been received from protocol. */
    else if (FCUART_HWA_GetStatus(base, (FCUART_StatType)(FCUART_STAT_LBKDIF | FCUART_STAT_RDRFF)))
    {
        LIN_DrvFrameHandle(pLinHandle);
    }
    /* Handle error status. */
    else
    {
        if (FCUART_HWA_GetStatus(base, FCUART_STAT_RORF))
        {
            xferState->currentEventId = LIN_RX_OVERRUN;
        }
        else
        {
            xferState->currentEventId = LIN_FRAME_ERROR;
        }

        FCUART_HWA_WriteClearSTAT(base, FCUART_STAT_RORF_MASK | FCUART_STAT_NF_MASK | FCUART_STAT_FEF_MASK | FCUART_STAT_PEF_MASK);

        if (NULL != xferState->Callback)
        {
            xferState->Callback(pLinHandle, xferState);
        }

        /* Error occurred, enater IDLE state. */
        LIN_DrvGoToIdleMode(pLinHandle);
    }
#if LIN_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

#endif
