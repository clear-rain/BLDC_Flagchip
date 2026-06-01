/**
 * @file module_driver_fcuart.c
 * @author Flagchip
 * @brief FCUART driver source code
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

#include "module_driver_fcuart.h"

#if FCUART_INSTANCE_COUNT > 0U

#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/* ################################################################################## */
/* ####################################### Macro #################################### */
#ifndef FCUART_DEV_ERROR_REPORT
#define FCUART_DEV_ERROR_REPORT    STD_OFF
#endif

#if FCUART_DEV_ERROR_REPORT == STD_ON
#define FCUART_ReportDevError(func, error) ReportDevError(FCUART_MODULE_ID, func, error)
#endif

/* ################################################################################## */
/* ################################### type define ################################## */


/* ################################################################################## */
/* ################################ Local Variables ################################# */

/* UART instance array */
static FCUART_Type *const s_aFCUART_InstanceTable[FCUART_INSTANCE_COUNT] = FCUART_BASE_PTRS;

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */

static uint32_t FCUART_LL_Error(uint8_t u8UartIndex);

static FCUART_ErrorType FCUART_LL_ProcessBaud(uint32_t u32Smb, uint32_t *u32OverSamp, uint32_t *u32Sbr);

static FCUART_ErrorType FCUART_LL_Transmit_Char(FCUART_Type *pUart, uint8_t u8Data, uint32_t u32TimeoutTick);

static FCUART_ErrorType FCUART_LL_Receive(uint8_t u8UartIndex, FCUART_DataType *pUartData);

static FCUART_ErrorType FCUART_LL_Transmit_Empty(uint8_t u8UartIndex, FCUART_DataType *pUartData);

static FCUART_ErrorType FCUART_LL_Transmit_Complete(uint8_t u8UartIndex);

static FCUART_ErrorType FCUART_LL_Transmit_Idle(uint8_t u8UartIndex);

static FCUART_ErrorType FCUART_SetInterrupt(FCUART_HandleType *pUartHandle, FCUART_InterruptType *pInterruptCfg);

static uint8_t FCUART_Float2Char(double Value, char *pOutStr, uint32_t u32Eps);

static uint8_t FCUART_Int2Char(int i32Value, char *pOutStr, UART_PrintIntType eRadix, bool bHexUpper);

static uint8_t FCUART_LongLongInt2Char(long long int i64Value, char *pOutStr, UART_PrintIntType eRadix, bool bHexUpper);
/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */



/* ################################################################################## */
/* ################################ Local Functions ################################# */

/**
 * @brief Process get OverSamp and SBR
 *
 * @param u32Smb   the value OverSame*SBR
 * @param u32OverSamp out OverSampe
 * @param u32Sbr out
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_ProcessBaud(uint32_t u32Smb, uint32_t *u32OverSamp, uint32_t *u32Sbr)
{
    FCUART_ErrorType tRetVal;
    uint32_t          u32SbrTemp;
    uint32_t          u32OverSampTemp;
    uint32_t          u32TempSmbDiff;
    uint32_t          u32SmbDiff;
    uint32_t          u32CalcSmb;
    uint32_t          u32OverSamp1;
    uint32_t          u32Sbr1;
    uint32_t          u32OriginDiff;

    u32OverSamp1 = 4U;  /* 4..32 */

    /* sbr = smb / oversamp */
    u32Sbr1 = (uint16_t)(u32Smb / (u32OverSamp1));
    u32CalcSmb = (u32OverSamp1) * (u32Sbr1) ;

    if (u32CalcSmb > u32Smb)
    {
        u32SmbDiff = u32CalcSmb - u32Smb;
    }
    else
    {
        u32SmbDiff = u32Smb - u32CalcSmb;
    }
    u32OriginDiff = u32SmbDiff;

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
                u32SmbDiff = u32TempSmbDiff;
                u32OverSamp1 = u32OverSampTemp;  /* update and store the best u32OverSamp value calculated */
                u32Sbr1 = u32SbrTemp;  /* update store the best u32Sbr value calculated */
            }

            /* when differ is 0U, break */
            if (u32SmbDiff == 0U)
            {
                break;
            }
        }
    }

    /* check differ */
    if (u32SmbDiff <= u32OriginDiff)
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;

        /* out the calculated value */
        *u32Sbr = u32Sbr1;
        *u32OverSamp = u32OverSamp1;
    }
    else
    {
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_FAILED;
    }

    return tRetVal;
}


/**
 * @brief Function to Transmit single Char
 *
 * @param pUart UART Instance point
 * @param u8Data UART data
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Transmit_Char(FCUART_Type *pUart, uint8_t u8Data, uint32_t u32TimeoutTick)
{
    uint32_t         u32Result;
    uint32_t         u32TryCount;

    /* check transmit ready flag */
    u32Result = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TDREF);

    if (u32Result)
    {
        FCUART_HWA_SetData(pUart, (uint32_t)u8Data);               /* Send data */
        FCUART_HWA_StartTransmit(pUart); /* start transmit */

        u32Result = 0U;
        u32TryCount = 0U;

        while ((u32Result == 0U) && (u32TryCount < u32TimeoutTick))
        {
            /* check transmit flag */
            u32Result = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TCF);
            u32TryCount++;
        }

        /* after transmit completed, close TE */
        FCUART_HWA_ClearTransmit(pUart);
    }

    return (u32Result == 0U) ? FCUART_ERROR_FAILED : FCUART_ERROR_OK;
}

/**
 * @brief Function to Transmit single Char by interrupt
 *
 * @param u8UartIndex UART Instance
 * @param pUartData UART receive buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Transmit_Empty(uint8_t u8UartIndex, FCUART_DataType *pUartData)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint32_t u32TempStats;
    uint8_t u8TxWaterMark;
    uint8_t u8Index;

    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
    if ((pUartData != NULL) && (pUartData->pDatas != NULL))
    {
        /* get and clear receive flag */
        u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TDREF);
        if (u32TempStats > 0U)
        {
            /* TDRFF Flag has been got */
            tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
            if(pUartData->u32DataLen > 0U)
            {
                if(true == FCUART_HWA_GetEnStatusTxFifo(pUart))
                {
                    /* Tx fifo enable */
                    u8TxWaterMark = FCUART_HWA_GetTxWaterMark(pUart);

                    if(((pUartData->u32DataLen) >= (FCUART_FIFO_DEPTH - u8TxWaterMark) ))
                    {
                        for(u8Index=0U; u8Index<(FCUART_FIFO_DEPTH - u8TxWaterMark); u8Index++)
                        {
                            FCUART_HWA_SetData(pUart, (uint8_t)(pUartData->pDatas[0U])); /* Send data */

                            /* Update pointer position */
                            (pUartData->pDatas)++;
                            (pUartData->u32DataLen)--;
                        }
                    }
                    else
                    {
                        for(u8Index=0U; u8Index<(pUartData->u32DataLen); u8Index++)
                        {
                            FCUART_HWA_SetData(pUart, (uint8_t)(pUartData->pDatas[0U])); /* Send data */

                            /* Update pointer position */
                            (pUartData->pDatas)++;
                            (pUartData->u32DataLen)--;
                        }
                    }
                }
                else
                {
                    /* Tx fifo disable */
                    FCUART_HWA_SetData(pUart, (uint8_t)(pUartData->pDatas[0U])); /* Send data */

                    /* Update pointer position */
                    (pUartData->pDatas)++;
                    (pUartData->u32DataLen)--;
                }

                if(0U == pUartData->u32DataLen)
                {
                    /* There's no new data, disable transmit empty interrupt and enable transmit complete interrupt */
                    FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
                    FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TCIE);
                }
            }
        }
    }

    return tRetVal;
}

/**
 * @brief Function to deal transmit complete
 *
 * @param u8UartIndex UART Instance
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Transmit_Complete(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint32_t u32TempStats;

    /* No need to check instance */
    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
    /* get and clear receive flag */
    u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TCF);

    if (u32TempStats > 0U)
    {
        /* TCF Flag has been got */
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;

        FCUART_HWA_DisableInterrupt(pUart, (uint32_t)(FCUART_INT_CTRL_TE | FCUART_INT_CTRL_TCIE));
    }
    return tRetVal;
}

/**
 * @brief Function to deal idle line
 *
 * @param u8UartIndex UART Instance
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Transmit_Idle(uint8_t u8UartIndex)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint32_t u32TempStats;

    /* get and clear receive flag */
    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];
    /* No need to check instance */
    u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_IDLEF);

    if (u32TempStats > 0U)
    {
        /* IDLF Flag has been got */
        tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;
        FCUART_HWA_ClearStatus(pUart, (uint32_t)FCUART_STAT_IDLEF);
    }
    return tRetVal;
}


/**
 * @brief Receive UART data
 *
 * @param u8UartIndex UART Instance
 * @param pUartData UART receive buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_LL_Receive(uint8_t u8UartIndex, FCUART_DataType *pUartData)
{
    FCUART_ErrorType tRetVal = (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
    FCUART_Type *pUart;
    uint8_t u8ReadData;
    uint32_t u32TempStats;
    uint8_t  u8RxCount;
    uint8_t  u8Index;

    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

    if ((pUartData != NULL) && (pUartData->pDatas != NULL))
    {
        /* get and clear receive flag */
        u32TempStats = FCUART_HWA_GetStatus(pUart, FCUART_STAT_RDRFF);

        if (u32TempStats > 0U)
        {
            /* RDRFF Flag has been got */
            tRetVal = (FCUART_ErrorType)FCUART_ERROR_OK;

            pUartData->u32DataLen = 0U;
            if( true == FCUART_HWA_GetEnStatusRxFifo(pUart))
            {
                /* Rx fifo enable */
                u8RxCount = FCUART_HWA_GetFifoRxCount(pUart);
                for(u8Index = 0U; u8Index < u8RxCount; u8Index++)
                {
                    u8ReadData = FCUART_HWA_GetData(pUart);
                    pUartData->pDatas[u8Index] = u8ReadData;
                    pUartData->u32DataLen++;
                }
            }
            else
            {
                /* Rx fifo disable */
                u8ReadData = FCUART_HWA_GetData(pUart);
                pUartData->pDatas[0U] = u8ReadData;
                pUartData->u32DataLen++;
            }
        }
    }

    return tRetVal;
}


/**
 * @brief Get Error Status
 *
 * @param u8UartIndex
 * @return All Error Combine, 0U is no error
 */
static uint32_t FCUART_LL_Error(uint8_t u8UartIndex)
{
    uint32_t      u32RetVal;
    uint32_t      u32ErrorValue;
    FCUART_Type   *pUart;

    u32ErrorValue = 0U;

    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex];

    /* receive overrun */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_RORF);

    /* FCUART_HWA_ClearStatus(pUart, FCUART_STAT_RORF); */
    if (u32RetVal != 0U)
    {
        u32ErrorValue = (uint32_t)FCUART_ERROR_RORF;
    }

    /* noise flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_NF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_NF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_NF;
    }

    /* Frame Error flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_FEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_FEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_FEF;
    }

    /* Parity Error Flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_PEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_PEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_PEF;
    }

    /* Receive Data Parity Error Flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_RPEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_RPEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_RPEF;
    }

    /* Transmit Data Parity Error Flag */
    u32RetVal = FCUART_HWA_GetStatus(pUart, FCUART_STAT_TPEF);

    /*FCUART_HWA_ClearStatus(pUart, FCUART_STAT_TPEF);*/
    if (u32RetVal != 0U)
    {
        u32ErrorValue |= (uint32_t)FCUART_ERROR_TPEF;
    }

    /* clear error flags */
    FCUART_HWA_ClearStatus(pUart, u32ErrorValue);

    return u32ErrorValue;
}


/* ################################################################################## */
/* ################################ Global Functions ################################ */

/**
 * @brief Initial UART variables Memory
 *
 */
void FCUART_InitMemory(FCUART_HandleType *pUartHandle)
{
    uint8_t u8UartIndex;

    for (u8UartIndex = 0U; u8UartIndex < FCUART_INSTANCE_COUNT; u8UartIndex++)
    {
        pUartHandle->tStatus.pFCUART_ErrorNotify = NULL;
        pUartHandle->tStatus.pFCUART_RxNotify = NULL;
        pUartHandle->tStatus.pFCUART_TxEmptyNotify = NULL;
        pUartHandle->tStatus.pFCUART_TxCompleteNotify = NULL;
        pUartHandle->tStatus.pFCUART_IdleNotify = NULL;
        pUartHandle->tStatus.u8FCUART_UartUsed = 0U;
        pUartHandle->tStatus.eCurrentSequence = FCUART_SEQUENCE_DEINIT;
    }
}

/**
 * @brief This Function is used to initial UART instance
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pInitCfg contains clock, baud-rate, Bit Mode, parity and so on.
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Init(FCUART_HandleType *pUartHandle, FCUART_InitType *pInitCfg)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_INIT_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence != FCUART_SEQUENCE_DEINIT)
    {
        FCUART_ReportDevError(FCUART_INIT_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else if(pInitCfg == NULL)
    {
        FCUART_ReportDevError(FCUART_INIT_ID, FCUART_E_PARAM_POINTER);
    }
    else
    {
#endif
        FCUART_ErrorType tRetVal = FCUART_ERROR_OK;
        uint32_t         u32TempBaudReg;
        uint32_t         u32TempCtrlReg;
        uint32_t         u32TempFifoReg;
        uint32_t         u32TempWatermarkReg;
        uint32_t         u32TempStat;
        uint32_t         u32TempModir;
        FCUART_Type      *pUart;
        uint32_t         u32Sbr      = 0U;
        uint32_t         u32OverSamp = 0U;
        uint32_t         u32Smb      = 0U;


        /* set not start state */
        pUartHandle->tStatus.eCurrentSequence = FCUART_SEQUENCE_NOTSTART_RECEIVE;

        u32Smb = pInitCfg->u32ClkSrcHz / pInitCfg->u32Baudrate;

        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        /* process for baud-rate */
        FCUART_LL_ProcessBaud(u32Smb, &u32OverSamp, &u32Sbr);

        /* temporary BAUD register */
        u32TempBaudReg = (uint32_t)0U                            |  /* initial value                                                           */
                        FCUART_BAUD_MAEN0(0U)                   |  /* Match mode enable 0                                                     */
                        FCUART_BAUD_MAEN1(0U)                   |  /* Match mode enable 1                                                     */
                        FCUART_BAUD_10BIT_MODE(0U)              |  /* 10bit mode select                                                       */
                        FCUART_BAUD_OVR_SAMP(u32OverSamp - 1U)  | /* Over sampling Ratio, n+1                                                 */
                        FCUART_BAUD_TDMAEN(pInitCfg->bEnTxEmptyDma)   |  /* Transmitter DMA Enable                                                  */
                        FCUART_BAUD_RDMAEN(pInitCfg->bEnRxFullDma)    |  /* Receiver Full DMA Enable                                                */
                        FCUART_BAUD_RIDMAEN(0U)                 |  /* Receiver Idle DMA Enable                                                */
                        FCUART_BAUD_MATCH_CFG(0U)               |  /* Match Configuration                                                     */
                        FCUART_BAUD_BEDGE_SAMP(1U)              |  /* Both Edge Sampling                                                      */
                        FCUART_BAUD_RESYNC_DIS(0U)              |  /* Re-synchronization Disable                                              */
                        FCUART_BAUD_LBKDIE(0U)                  |  /* LIN Break Detect Interrupt Enable                                       */
                        FCUART_BAUD_RIAEIE(0U)                  |  /* RX Input Active Edge Interrupt Enable                                   */
                        FCUART_BAUD_SBNS(pInitCfg->eStopBit)    |  /* Stop Bit Number Select                                                  */
                        FCUART_BAUD_SBR(u32Sbr);                   /* Baud Rate Modulo Divisor. baud-rate = baud clock / ((OVR_SAMP+1) * SBR) */

        /* temporary CTRL register */
        u32TempCtrlReg = (uint32_t)0U                                |   /* initial value                                       */
                        FCUART_CTRL_R8T9(0U)                        |  /* Receive Bit 8 / Transmit Bit 9                       */
                        FCUART_CTRL_R9T8(0U)                        |  /* Receive Bit 9 / Transmit Bit 8                       */
                        FCUART_CTRL_TXDIR(0U)                       |  /* TXD Pin Direction in Single-Wire Mode                */
                        FCUART_CTRL_TXINV(0U)                       |  /* Transmit Data Inversion                              */
                        FCUART_CTRL_ORIE(0U)                        |  /* Overrun Interrupt Enable                             */
                        FCUART_CTRL_NEIE(0U)                        |  /* Noise Error Interrupt Enable                         */
                        FCUART_CTRL_FEIE(0U)                        |  /* Frame Error Interrupt Enable                         */
                        FCUART_CTRL_PEIE(0U)                        |  /* Parity Error Interrupt Enable                        */
                        FCUART_CTRL_TIE(0U)                         |  /* Transmit Interrupt Enable                            */
                        FCUART_CTRL_TCIE(0U)                        |  /* Transmission Complete Interrupt Enable               */
                        FCUART_CTRL_RIE(0U)                         |  /* Receiver Interrupt Enable                            */
                        FCUART_CTRL_IIE(0U)                         |  /* Idle Line Interrupt Enable                           */
                        FCUART_CTRL_TE(0U)                          |  /* Transmitter Enable                                   */
                        FCUART_CTRL_RE(0U)                          |  /* Receiver Enable                                      */
                        FCUART_CTRL_RWC(0U)                         |  /* Receiver WakeUp Control                              */
                        FCUART_CTRL_SBK(0U)                         |  /* Send Break                                           */
                        FCUART_CTRL_M0IE(0U)                        |  /* Match address 0 Interrupt Enable                     */
                        FCUART_CTRL_M1IE(0U)                        |  /* Match address 1 Interrupt Enable                     */
                        FCUART_CTRL_7BMS(0U)                        |  /* 7-Bit Mode Select                                    */
                        FCUART_CTRL_IDLECFG(pInitCfg->eIdleCharNum) | /* Idle Configuration 2^n bytes time no data entry IDLE */
                        FCUART_CTRL_LOOPMS(0U)                      |  /* Loop Mode Select                                     */
                        FCUART_CTRL_WAITEN(0U)                      |  /* WAIT Enable                                          */
                        FCUART_CTRL_RXSRC(0U)                       |  /* Receiver Source Select                               */
                        FCUART_CTRL_BMSEL(pInitCfg->eBitMode)       |  /* 9-Bit or 8-Bit Mode Select                           */
                        FCUART_CTRL_RSWMS(0U)                       |  /* Receiver WakeUp Method Select                        */
                        FCUART_CTRL_ITS(pInitCfg->eIdleStart)       |  /* Idle Line Type Select                                */
                        FCUART_CTRL_PE(pInitCfg->bParityEnable)     |  /* Parity Enable                                        */
                        FCUART_CTRL_PT(pInitCfg->eParityType);         /* Parity Type                                          */

        /* temporary FIFO register */
        u32TempFifoReg = (uint32_t)0U                              |   /* initial value                             */
                        FCUART_FIFO_TXEMPTY(0U)                   |  /* Transmit Buffer/FIFO Empty                 */
                        FCUART_FIFO_RXEMPTY(0U)                   |  /* Receive Buffer/FIFO Empty                  */
                        FCUART_FIFO_TXOF(0U)                      |  /* Transmitter Buffer Overflow Flag           */
                        FCUART_FIFO_RXUF(0U)                      |  /* Receiver Buffer Underflow Flag             */
                        FCUART_FIFO_TXFLUSH(1U)                   |  /* Transmit FIFO/Buffer Flush                 */
                        FCUART_FIFO_RXFLUSH(1U)                   |  /* Receive FIFO/Buffer Flush                  */
                        FCUART_FIFO_RXIDEN(pInitCfg->eFifoRxIdleCharNum) |  /* Receiver Idle Empty Enable          */
                        FCUART_FIFO_TXOFIE(0U)                    |  /* Transmit FIFO Overflow Interrupt Enable    */
                        FCUART_FIFO_RXUFIE(0U)                    |  /* Receive FIFO Underflow Interrupt Enable    */
                        FCUART_FIFO_TXFEN(pInitCfg->bEnTxFifo)    |  /* Transmit FIFO Enable                       */
                        FCUART_FIFO_TXFIFODEP(1U)                 |  /* Transmit FIFO Buffer Depth 4               */
                        FCUART_FIFO_RXFEN(pInitCfg->bEnRxFifo)    |  /* Receive FIFO Enable, enable RX FIFO        */
                        FCUART_FIFO_RXFIFODEP(1U);                   /* Receive FIFO Buffer Depth, 4 data FIFO     */

        /* temporary WATERMARK register */
        u32TempWatermarkReg = (uint32_t)0U                                    |   /* initial value                                          */
                            FCUART_WATERMARK_RXCOUNT(0U)                    |  /* Receive Counter                                         */
                            FCUART_WATERMARK_RXWATER(pInitCfg->u8RxFifoWM)  |  /* Receive WaterMark, receive n-1 request interrupt or DMA */
                            FCUART_WATERMARK_TXCOUNT(0U)                    |  /* Transmit Counter                                        */
                            FCUART_WATERMARK_TXWATER(pInitCfg->u8TxFifoWM);    /* Transmit WaterMark                                      */

        /* temporary MODIR register */
        u32TempModir = (uint32_t)0U                 |   /* initial value                                          */
                    FCUART_MODIR_RXRTSCFG(0U)    |   /* Receive RTS Configuration                              */
                    FCUART_MODIR_TXCTSSRC(0U)    |   /* Transmit CTS Source                                    */
                    FCUART_MODIR_TXCTSCFG(0U)    |   /* Transmit CTS Configuration                             */
                    FCUART_MODIR_RXRTSEN(0U)     |   /* Receiver Request-to-Send Enable                        */
                    FCUART_MODIR_TXRTSPOL(0U)    |   /* Transmitter Request-to-Send Polarity                   */
                    FCUART_MODIR_TXRTSEN(0U)     |   /* Transmitter Request-to-Send Enable                     */
                    FCUART_MODIR_TXCTSEN(0U);        /* Transmitter Clear-to-Send Enable                       */

        /* write register with temporary data */
        FCUART_HWA_SetBaud(pUart, u32TempBaudReg); /* 0x19000008; */
        FCUART_HWA_SetFifo(pUart, u32TempFifoReg);
        FCUART_HWA_SetWaterMark(pUart, u32TempWatermarkReg);
        FCUART_HWA_SetModir(pUart, u32TempModir);

        FCUART_HWA_SetCtrl(pUart, u32TempCtrlReg);

        /* clear all status */
        u32TempStat = FCUART_HWA_ReadSTAT(pUart);
        FCUART_HWA_WriteClearSTAT(pUart, u32TempStat);

        /* instance used */
        pUartHandle->tStatus.u8FCUART_UartUsed = 1U;
        pUartHandle->tStatus.u32FCUART_TransmitTimeout = pInitCfg->u32TransmitTimeout > 0U ? pInitCfg->u32TransmitTimeout : 3000U;

        tRetVal = FCUART_SetInterrupt(pUartHandle, &(pInitCfg->tInterruptCfg));

        return tRetVal;
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}


/**
 * @brief This Function is used to de-initial UART instance
 *
 * @param pUartHandle The structure of the UART processing handle
 * @return void
 */
void FCUART_DeInit(FCUART_HandleType *pUartHandle)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_DEINIT_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence <= FCUART_SEQUENCE_DEINIT)
    {
        FCUART_ReportDevError(FCUART_DEINIT_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        FCUART_Type      *pUart;

        /* set deinit state */
        pUartHandle->tStatus.eCurrentSequence = FCUART_SEQUENCE_DEINIT;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        FCUART_HWA_SetSoftWareReset(pUart);
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to set UART interrupt
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pIntCfg contains callback functions
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
static FCUART_ErrorType FCUART_SetInterrupt(FCUART_HandleType *pUartHandle, FCUART_InterruptType *pInterruptCfg)
{
    FCUART_ErrorType tRetVal = FCUART_ERROR_OK;
    FCUART_Type *pUart;

    pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

    /* error interrupt */
    if (true == pInterruptCfg->bEnErrorInterrupt)
    {
        FCUART_HWA_EnableInterrupt(pUart, (uint32_t)(FCUART_INT_CTRL_ORIE |FCUART_INT_CTRL_NEIE |FCUART_INT_CTRL_FEIE |FCUART_INT_CTRL_PEIE));
        pUartHandle->tStatus.pFCUART_ErrorNotify = pInterruptCfg->pErrorNotify;
    }
    else
    {
        FCUART_HWA_DisableInterrupt(pUart, (uint32_t)(FCUART_INT_CTRL_ORIE |FCUART_INT_CTRL_NEIE |FCUART_INT_CTRL_FEIE |FCUART_INT_CTRL_PEIE));
    }

    /* receive interrupt */
    if (true == pInterruptCfg->bEnRxInterrupt)
    {
        /* check buffer point if it is null */
        if (pInterruptCfg->pRxBuf != NULL)
        {
            FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_RIE);

            pUartHandle->tStatus.tFCUART_RxMsg = pInterruptCfg->pRxBuf;
            pUartHandle->tStatus.pFCUART_RxNotify = pInterruptCfg->pRxNotify;
        }
        else
        {
            tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
        }

    }
    else
    {
        FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_RIE);
    }

    /* Transfer interrupt */
    if (true == pInterruptCfg->bEnTxInterrupt)
    {
        /* check buffer point if it is null */
        if (pInterruptCfg->pTxBuf != NULL)
        {
            FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
            pUartHandle->tStatus.tFCUART_TxMsg = pInterruptCfg->pTxBuf;
            pUartHandle->tStatus.pFCUART_TxEmptyNotify = pInterruptCfg->pTxEmptyNotify;
            pUartHandle->tStatus.pFCUART_TxCompleteNotify = pInterruptCfg->pTxCompleteNotify;
        }
        else
        {
            tRetVal |= (FCUART_ErrorType)FCUART_ERROR_INVALID_PARAM;
        }

    }
    else
    {
        FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
    }

    /* Idle interrupt */
    if (true == pInterruptCfg->bEnIdleInterrupt)
    {
        FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_IIE);
        pUartHandle->tStatus.pFCUART_IdleNotify = pInterruptCfg->pIdleNotify;
    }
    else
    {
        FCUART_HWA_DisableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_IIE);
    }

    return tRetVal;
}


/**
 * @brief This Function is used to set UART WakeUp
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pWakeupCfg contains UART wake-up parameters
 * @return void
 */
void FCUART_SetWakeup(FCUART_HandleType *pUartHandle, FCUART_WakeupType *pWakeupCfg)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_SET_WAKEUP_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence != FCUART_SEQUENCE_NOTSTART_RECEIVE)
    {
        FCUART_ReportDevError(FCUART_SET_WAKEUP_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else if(pWakeupCfg == NULL)
    {
        FCUART_ReportDevError(FCUART_SET_WAKEUP_ID, FCUART_E_PARAM_POINTER);
    }
    else
    {
#endif
        FCUART_Type      *pUart;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        /*
         * RWC   MATCH0|MATCH1   MATCH_CFG  [RSWMS,RWUID]    Receiver Wakeup
            0    0                X           X               Normal operation
            1    0                00          00              Receiver wakeup on idle line, IDLE flag not set
            1    0                00          01              Receiver wakeup on idle line, IDLE flag set
            1    0                00          10              Receiver wakeup on address mark
            1    1                11          10              Receiver wakeup on address match
            0    1                00          X0              Address mark address match, IDLE flag not set for discarded characters
            0    1                00          X1              Address mark address match, IDLE flag set for discarded characters
            0    1                01          X0              Idle line address match
            0    1                10          X0              Address match on and address match off, IDLE flag not set for discarded characters
            0    1                10          X1              Address match on and address match off, IDLE flag set for discarded characters
            *
         */

        FCUART_HWA_AttachCtrl(pUart, FCUART_CTRL_RWC_MASK | FCUART_CTRL_RSWMS_MASK);      /* WakeUp enable and method select address-mark */
        FCUART_HWA_AttachBaud(pUart, FCUART_BAUD_MATCH_CFG(3U) | FCUART_BAUD_MAEN0(1U));  /* match0 data                                  */
        FCUART_HWA_AttachMatch(pUart, FCUART_MATCH_MATCH0(pWakeupCfg->u32WakeUpData));    /* set wake-up data*/

#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to Get current interrupt mode
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param u32Data  Interrupt type to get
 * @return true/false
 *
 */
bool FCUART_GetInterruptMode(FCUART_HandleType *pUartHandle, uint32_t u32Data)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_GET_INTERRUPT_ID, FCUART_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        bool bRetVal;
        FCUART_Type *pUart;
        uint32_t u32CtrlRegData;

        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        u32CtrlRegData = FCUART_HWA_GetCtrl(pUart);
        bRetVal = ((u32CtrlRegData & u32Data) > 0U ) ? true : false;

        return bRetVal;
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to start receiving
 *
 * @param pUartHandle The structure of the UART processing handle
 * @return void
 */
void FCUART_StartReceive(FCUART_HandleType *pUartHandle)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_START_RECEIVE_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence != FCUART_SEQUENCE_NOTSTART_RECEIVE)
    {
        FCUART_ReportDevError(FCUART_START_RECEIVE_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        FCUART_Type      *pUart;

        /* set started receive state */
        pUartHandle->tStatus.eCurrentSequence = FCUART_SEQUENCE_START_RECEIVE;

        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        /* start receive */
        FCUART_HWA_StartReceive(pUart);
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to assign data to send through interrupt
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pData  data pointer
 * @param u32Length data length to send
 * @return void
 *
 */
void FCUART_AssignTxInterruptData(FCUART_HandleType *pUartHandle, uint8_t * pData, uint32_t u32Length)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_ASSIGN_TXINTRRUPT_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pData == NULL)
    {
        FCUART_ReportDevError(FCUART_ASSIGN_TXINTRRUPT_ID, FCUART_E_PARAM_POINTER);
    }
    else
    {
#endif

        pUartHandle->tStatus.tFCUART_TxMsg->pDatas    = pData;
        pUartHandle->tStatus.tFCUART_TxMsg->u32DataLen = u32Length;

#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to start transmit through interrupt
 *
 * @param pUartHandle The structure of the UART processing handle
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
void FCUART_StartTransmit(FCUART_HandleType *pUartHandle)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_START_TRANSMIT_ID, FCUART_E_PARAM_INSTANCE);
    }
    else
    {
#endif

        FCUART_Type *pUart;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        /* start transmit */
        FCUART_HWA_SetTxTransfer(pUart, true);

        if(false == FCUART_GetInterruptMode(pUartHandle, (uint32_t)FCUART_INT_CTRL_TIE))
        {
            FCUART_HWA_EnableInterrupt(pUart, (uint32_t)FCUART_INT_CTRL_TIE);
        }

#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to stop receiving
 *
 * @param pUartHandle The structure of the UART processing handle
 * @return void
 */
void FCUART_StopReceive(FCUART_HandleType *pUartHandle)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_STOP_RECEIVE_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence == FCUART_SEQUENCE_VAR_NOINIT || 
            pUartHandle->tStatus.eCurrentSequence == FCUART_SEQUENCE_DEINIT)
    {
        FCUART_ReportDevError(FCUART_STOP_RECEIVE_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        FCUART_Type      *pUart;

        /* set stop state */
        pUartHandle->tStatus.eCurrentSequence = FCUART_SEQUENCE_NOTSTART_RECEIVE;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        /* stop receive */
        FCUART_HWA_ClearReceive(pUart);
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to transmit UART data
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pUartData contains UART data and length
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Transmit(FCUART_HandleType *pUartHandle, FCUART_DataType *pUartData)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_TRANSMIT_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence == FCUART_SEQUENCE_VAR_NOINIT || 
            pUartHandle->tStatus.eCurrentSequence == FCUART_SEQUENCE_DEINIT)
    {
        FCUART_ReportDevError(FCUART_TRANSMIT_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else if((pUartData == NULL) || (pUartData->pDatas == NULL))
    {
        FCUART_ReportDevError(FCUART_TRANSMIT_ID, FCUART_E_PARAM_POINTER);
    }
    else
    {
#endif
        FCUART_ErrorType tRetVal;

        FCUART_Type     *pUart;
        uint8_t         *pData;
        uint32_t         u32Index;
        uint32_t         u32DataLen;

        pData = pUartData->pDatas;
        u32DataLen = pUartData->u32DataLen;
        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];
        tRetVal = FCUART_ERROR_FAILED;

        for (u32Index = 0U; u32Index < u32DataLen; u32Index++)
        {
            tRetVal = FCUART_LL_Transmit_Char(pUart, pData[u32Index], pUartHandle->tStatus.u32FCUART_TransmitTimeout);

            if (tRetVal != (FCUART_ErrorType)FCUART_ERROR_OK)
            {
                break;
            }
        }
        return tRetVal;
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to print ASCII char from UART
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param fmt is char format
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Printf(FCUART_HandleType *pUartHandle, char *fmt, ...)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_PRINTF_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence == FCUART_SEQUENCE_VAR_NOINIT || 
            pUartHandle->tStatus.eCurrentSequence == FCUART_SEQUENCE_DEINIT)
    {
        FCUART_ReportDevError(FCUART_PRINTF_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        FCUART_Type *pUart;
        FCUART_ErrorType tRetVal = FCUART_ERROR_OK;
        const char *pStr;
        int i32Temp;
        unsigned char TxData;
        uint8_t u8Number;
        uint8_t u8LenthNumber = 4U;
        char TempBuffer[32];
        int u32Count = 0U;
        va_list ap;

        va_start(ap, fmt);

        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        while (*fmt != (char)0)
        {
            /* Escape character */
            if ((*fmt) == ESCAPE_CHARACTER)
            {
                switch (*(++fmt))
                {
                case 'r':
                {
                    TxData = ENTER;
                    tRetVal = FCUART_LL_Transmit_Char(pUart, TxData, pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                    fmt++;
                }
                break;

                case 'n':
                {
                    TxData = NEW_LINE;
                    tRetVal = FCUART_LL_Transmit_Char(pUart, TxData, pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                    fmt++;
                }
                break;

                default:
                    fmt++;
                    break;
                }
            }
            else if ((*fmt) == (char)'%')
            {
                switch (*(++fmt))
                {
                case 's':
                {
                    u32Count++;
                    pStr = va_arg(ap, const char *);
                    for (; *pStr; pStr++)
                    {
                        tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                    }
                    fmt++;
                }
                break;

                case 'l':
                {
                    if (*(++fmt) == 'l' && *(++fmt) == 'd')
                    {
                        if(u32Count & 1)
                        {
#if defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM) || (defined(__ARMCC_VERSION) && __ARMCC_VERSION >= 6000000)
                            (void)va_arg(ap, int);
#endif
                        }
                        u32Count = 0U;

                        long long int i64Temp = 0;
                        *(int *)(&i64Temp) = va_arg(ap, int);
                        *((int *)(&i64Temp)+1) = va_arg(ap, int);
                        if (0U == FCUART_LongLongInt2Char(i64Temp, TempBuffer, UART_PRINT_RADIX_DEC, false))
                        {
                            for (pStr = TempBuffer; *pStr; pStr++)
                            {
                                tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                            }
                        }
                        fmt++;
                    }
                }
                break;

                case 'd':
                {
                    u32Count++;
                    i32Temp = va_arg(ap, int);
                    if (0U == FCUART_Int2Char(i32Temp, TempBuffer, UART_PRINT_RADIX_DEC, false))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                        }
                    }
                    fmt++;
                }
                break;

                case 'x':
                {
                    u32Count++;
                    i32Temp = va_arg(ap, int);
                    if (0U == FCUART_Int2Char(i32Temp, TempBuffer, UART_PRINT_RADIX_HEX, false))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                        }
                    }
                    fmt++;
                }
                break;

                case 'X':
                {
                    u32Count++;
                    i32Temp = va_arg(ap, int);
                    if (0U == FCUART_Int2Char(i32Temp, TempBuffer, UART_PRINT_RADIX_HEX, true))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                        }
                    }
                    fmt++;
                }
                break;

                case '.':
                {
                    u8Number = (uint8_t)(*(++fmt) - '0');
                    if ((*(++fmt)) == 'f')
                    {
                        if(u32Count & 1)
                        {
#if defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM) || (defined(__ARMCC_VERSION) && __ARMCC_VERSION >= 6000000)
                            (void)va_arg(ap, int);
#endif
                        }
                        u32Count = 0U;

                        double num = 0;
                        *(int *)(&num) = va_arg(ap, int);
                        *((int *)(&num)+1) = va_arg(ap, int);
                        if (0U == FCUART_Float2Char(num, TempBuffer, u8Number))
                        {
                            for (pStr = TempBuffer; *pStr; pStr++)
                            {
                                tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                            }
                        }
                        fmt++;
                    }
                }
                break;

                case 'f':
                {
                    if(u32Count & 1)
                    {
#if defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM) || (defined(__ARMCC_VERSION) && __ARMCC_VERSION >= 6000000)
                        (void)va_arg(ap, int);
#endif
                    }
                    u32Count = 0U;

                    double num = 0;
                    *(int *)(&num) = va_arg(ap, int);
                    *((int *)(&num)+1) = va_arg(ap, int);
                    if (0U == FCUART_Float2Char(num, TempBuffer, u8LenthNumber))
                    {
                        for (pStr = TempBuffer; *pStr; pStr++)
                        {
                            tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)pStr), pUartHandle->tStatus.u32FCUART_TransmitTimeout);
                        }
                    }
                    fmt++;
                }
                break;

                default:
                    fmt++;
                    break;
                }
            }
            else
            {
                tRetVal = FCUART_LL_Transmit_Char(pUart, *((unsigned char *)fmt), pUartHandle->tStatus.u32FCUART_TransmitTimeout);

                if (tRetVal != FCUART_ERROR_OK)
                {
                    break;
                }

                fmt++;
            }
        }

        va_end(ap);

        return tRetVal;
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief  Convert integer to char
 *
 * @param  i32Value
 * @param  pOutStr
 * @param  eRadix
 * @return 0 is ok
 */
static uint8_t FCUART_Int2Char(int i32Value, char *pOutStr, UART_PrintIntType eRadix, bool bHexUpper)
{
    uint8_t u8Retval;
    char aCharListUpper[] = "0123456789ABCDEF";
    char aCharListLower[] = "0123456789abcdef";
    char aNumList[]       = "0123456789";
    char *pCharList;
    uint32_t u32Temp;
    uint8_t u8Index = 0U;
    uint8_t u8ValueStart = 0U;
    char Temp = 0;
    uint32_t j;

    if (NULL == pOutStr)
    {
        u8Retval = 1U;
    }
    else
    {
        u8Retval = 0U;
        if ((UART_PRINT_RADIX_DEC == eRadix) && (i32Value < 0))
        {
            // Decimal and negative
            u32Temp = (uint32_t)(0 - i32Value);
            pOutStr[u8Index++] = '-';
            u8ValueStart = 1U;
            pCharList = aNumList;
        }
        else
        {
            if (true == bHexUpper)
            {
                pCharList = aCharListUpper;
            }
            else
            {
                pCharList = aCharListLower;
            }
            u32Temp = (uint32_t)i32Value;
        }

        // Data is converted to a string and stored in reverse order
        do
        {
            pOutStr[u8Index++] = pCharList[u32Temp % (uint8_t)eRadix];
            u32Temp /= (uint8_t)eRadix;
        } while (u32Temp);

        pOutStr[u8Index] = '\0';

        // Convert the string with reverse order to positive
        for (j = u8ValueStart; j < (uint32_t)((u8Index + u8ValueStart) / 2); j++)
        {
            Temp = pOutStr[j];
            pOutStr[j] = pOutStr[u8Index - j - 1U + u8ValueStart];
            pOutStr[u8Index - j - 1U + u8ValueStart] = Temp;
        }
    }
    return u8Retval;
}

/**
 * @brief  Convert integer to char
 *
 * @param  i64Value
 * @param  pOutStr
 * @param  eRadix
 * @return 0 is ok
 */
static uint8_t FCUART_LongLongInt2Char(long long int i64Value, char *pOutStr, UART_PrintIntType eRadix, bool bHexUpper)
{
    uint8_t u8Retval;
    char aCharListUpper[] = "0123456789ABCDEF";
    char aCharListLower[] = "0123456789abcdef";
    char aNumList[]       = "0123456789";
    char *pCharList;
    uint64_t u64Temp;
    uint8_t u8Index = 0U;
    uint8_t u8ValueStart = 0U;
    char Temp = 0;
    uint32_t j;

    if (NULL == pOutStr)
    {
        u8Retval = 1U;
    }
    else
    {
        u8Retval = 0U;
        if ((UART_PRINT_RADIX_DEC == eRadix) && (i64Value < 0))
        {
            // Decimal and negative
            u64Temp = (uint64_t)(0 - i64Value);
            pOutStr[u8Index++] = '-';
            u8ValueStart = 1U;
            pCharList = aNumList;
        }
        else
        {
            if (true == bHexUpper)
            {
                pCharList = aCharListUpper;
            }
            else
            {
                pCharList = aCharListLower;
            }
            u64Temp = (uint64_t)i64Value;
        }

        // Data is converted to a string and stored in reverse order
        do
        {
            pOutStr[u8Index++] = pCharList[u64Temp % (uint8_t)eRadix];
            u64Temp /= (uint8_t)eRadix;
        } while (u64Temp);

        pOutStr[u8Index] = '\0';

        // Convert the string with reverse order to positive
        for (j = u8ValueStart; j < (uint32_t)((u8Index + u8ValueStart) / 2); j++)
        {
            Temp = pOutStr[j];
            pOutStr[j] = pOutStr[u8Index - j - 1U + u8ValueStart];
            pOutStr[u8Index - j - 1U + u8ValueStart] = Temp;
        }
    }
    return u8Retval;
}

/**
 * @brief  Convert float to char
 *
 * @param  Value
 * @param  pOutStr
 * @param  U32Eps
 * @return 0 is ok
 */
static uint8_t FCUART_Float2Char(double Value, char *pOutStr, uint32_t u32Eps)
{
    uint32_t u32Integer;
    double Decimal;
    char aCharList[] = "0123456789";
    uint8_t u8ValueStart = 0U;
    uint32_t u32TempCnt = 1U;
    char Temp = 0;
    double TempFactor = 0.1;
    uint8_t u8Index = 0U;
    uint32_t u32TempDecimal;
    uint8_t u8Retval;
    uint32_t j;

    if (NULL == pOutStr)
    {
        u8Retval = 1U;
    }
    else
    {
        u8Retval = 0U;
        // Extract integer and decimal from the input number
        if (Value < FLOAT_ZERO)
        {
            Decimal = (double)((int32_t)Value - Value);
            u32Integer = (uint32_t)(0.0 - Value);
            pOutStr[u8Index++] = '-';
            u8ValueStart = 1U;
        }
        else
        {
            u32Integer = (uint32_t)Value;
            Decimal = (double)(Value - u32Integer);
        }
        // The integer part of the data is converted into a string and stored in reverse order
        do
        {
            pOutStr[u8Index++] = aCharList[u32Integer % 10U];
            u32Integer /= 10U;
        } while (0U != u32Integer);

        pOutStr[u8Index] = '\0';

        // Convert the string with reverse order to positive
        for (j = u8ValueStart; j < (uint32_t)((u8Index + u8ValueStart) / 2); j++)
        {
            Temp = pOutStr[j];
            pOutStr[j] = pOutStr[u8Index - j - 1U + u8ValueStart];
            pOutStr[u8Index - j - 1U + u8ValueStart] = Temp;
        }

        // Accuracy problem, preventing input 1.2 and output 1.19
        for (j = 0U; j <= u32Eps; j++)
        {
            TempFactor *= 0.1;
        }
        Decimal += TempFactor;

        for (j = 0; j < u32Eps; j++)
        {
            Decimal *= (double)10.0;
            u32TempCnt *= 10U;
        }

        u32TempDecimal = (uint32_t)Decimal;
        pOutStr[u8Index++] = '.';
        for (j = 0; j < u32Eps; j++)
        {
            u32TempCnt /= 10U;
            if (0U != u32TempCnt)
            {
                pOutStr[u8Index++] = (char)((u32TempDecimal / u32TempCnt) + '0');
                u32TempDecimal %= u32TempCnt;
            }
        }
        pOutStr[u8Index] = '\0';
    }
    return u8Retval;
}

/**
 * @brief Get Stat Flag
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param eStatusType  stat type
 * @return FCUART STAT status flag
 */
uint32_t FCUART_GetStatus(FCUART_HandleType *pUartHandle, FCUART_StatType eStatusType)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_GET_SATTUS_ID, FCUART_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        FCUART_Type      *pUart;
        uint32_t         u32RetVal;

        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];
        u32RetVal = FCUART_HWA_GetStatus(pUart, eStatusType);

        return u32RetVal;
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to receive data when polling (not used when rx interrupt enabled)
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pRxMsg is data buffer address, and pDatas need to be initialed with external buffer
 * @return FCUART_ERROR_OK is ok, others are not ok
 */
FCUART_ErrorType FCUART_Receive_Polling(FCUART_HandleType *pUartHandle, FCUART_DataType *pRxMsg)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_RECEIVE_POLLING_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence != FCUART_SEQUENCE_START_RECEIVE)
    {
        FCUART_ReportDevError(FCUART_RECEIVE_POLLING_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else if(pRxMsg == NULL)
    {
        FCUART_ReportDevError(FCUART_RECEIVE_POLLING_ID, FCUART_E_PARAM_POINTER);
    }
    else if(pUartHandle->tStatus.u8FCUART_UartUsed != 1U)
    {
        FCUART_ReportDevError(FCUART_RECEIVE_POLLING_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        FCUART_ErrorType tRetVal;
        tRetVal = FCUART_LL_Receive(pUartHandle->eInstance, pRxMsg);

        return tRetVal;
#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to get error when polling (not used when error interrupt enabled)
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param pErrorValue is error value
 * @return void
 */
void FCUART_Error_Polling(FCUART_HandleType *pUartHandle, uint32_t *pErrorValue)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_ERROR_POLLING_ID, FCUART_E_PARAM_INSTANCE);
    }
    else if(pUartHandle->tStatus.eCurrentSequence < FCUART_SEQUENCE_NOTSTART_RECEIVE)
    {
        FCUART_ReportDevError(FCUART_ERROR_POLLING_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else if(pUartHandle->tStatus.u8FCUART_UartUsed != 1U)
    {
        FCUART_ReportDevError(FCUART_ERROR_POLLING_ID, FCUART_E_PARAM_ERROR_STATE);
    }
    else
    {
#endif
        /* check error */
        *pErrorValue = FCUART_LL_Error(pUartHandle->eInstance);

#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief This Function is used to enable fcuart loop mode
 *
 * @param pUartHandle The structure of the UART processing handle
 * @param bStatus  enable/disable status of loop mode
 * @return void
 *
 */
void FCUART_SetLoopMode(FCUART_HandleType *pUartHandle, bool bStatus)
{
#if FCUART_DEV_ERROR_REPORT == STD_ON
    if(pUartHandle->eInstance >= FCUART_INSTANCE_COUNT)
    {
        FCUART_ReportDevError(FCUART_SET_LOOPMODE_ID, FCUART_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        FCUART_Type *pUart;

        pUart = (FCUART_Type *)s_aFCUART_InstanceTable[pUartHandle->eInstance];

        if (true == bStatus)
        {
            FCUART_HWA_EnableLoopMode(pUart);
        }
        else
        {
            FCUART_HWA_DisableLoopMode(pUart);
        }

#if FCUART_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/* ################################################################################## */
/* ############################## Interrupt Services ################################ */

void FCUARTN_RxTx_IRQHandler(FCUART_HandleType *pUartHandle)
{
    FCUART_ErrorType tTempVal;
    FCUART_DataType *pRxMsgList;
    FCUART_DataType *pTxMsgList;
    uint32_t u32ErrorValue;
    uint32_t u32CtrlRegData;
    uint8_t u8UartIndex;

    u8UartIndex = pUartHandle->eInstance;
    /* Do not check instance because it should be checked before  */
    u32CtrlRegData = FCUART_HWA_GetCtrl((FCUART_Type *)s_aFCUART_InstanceTable[u8UartIndex]);

    /* Handle receive interrupt */
    if(((uint32_t)FCUART_INT_CTRL_RIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_RIE)))
    {
        /* get buffer point and it stored when called SetInterrupt */
        pRxMsgList = pUartHandle->tStatus.tFCUART_RxMsg;
        /* check pUart receive data */
        tTempVal = FCUART_LL_Receive(u8UartIndex, pRxMsgList);

        /* check buffer valid */
        if ( (tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (pRxMsgList != NULL))
        {
            if (pUartHandle->tStatus.pFCUART_RxNotify != NULL)
            {
                pUartHandle->tStatus.pFCUART_RxNotify(pUartHandle, pRxMsgList);
            }
        }
    }

    /* Handle transmit interrupt */
    if(((uint32_t)FCUART_INT_CTRL_TIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_TIE)))
    {
        /* get buffer point and it stored when called SetInterrupt */
        pTxMsgList = pUartHandle->tStatus.tFCUART_TxMsg;
        /* transfer data */
        tTempVal = FCUART_LL_Transmit_Empty(u8UartIndex, pTxMsgList);

        if((tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK)  && (pTxMsgList != NULL))
        {
            if (pUartHandle->tStatus.pFCUART_TxEmptyNotify != NULL)
            {
                pUartHandle->tStatus.pFCUART_TxEmptyNotify(pUartHandle, pTxMsgList);
            }
        }
    }

    /* Handle transmit complete interrupt */
    if(((uint32_t)FCUART_INT_CTRL_TCIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_TCIE)))
    {
        tTempVal = FCUART_LL_Transmit_Complete(u8UartIndex);

        if ((tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (pUartHandle->tStatus.pFCUART_TxCompleteNotify != NULL))
        {
            pUartHandle->tStatus.pFCUART_TxCompleteNotify(pUartHandle, NULL);
        }
    }

    /* Handle idle interrupt */
    if(((uint32_t)FCUART_INT_CTRL_IIE) == (u32CtrlRegData & ((uint32_t)FCUART_INT_CTRL_IIE)))
    {
        tTempVal = FCUART_LL_Transmit_Idle(u8UartIndex);
        if ((tTempVal == (FCUART_ErrorType)FCUART_ERROR_OK) && (pUartHandle->tStatus.pFCUART_IdleNotify != NULL))
        {
            pUartHandle->tStatus.pFCUART_IdleNotify(pUartHandle);
        }
    }

    /* Handle error interrupt */
    if(0U != (u32CtrlRegData & ((uint32_t)(FCUART_INT_CTRL_ORIE | FCUART_INT_CTRL_NEIE | FCUART_INT_CTRL_FEIE | FCUART_INT_CTRL_PEIE))))
    {
        /* check error */
        u32ErrorValue = FCUART_LL_Error(u8UartIndex);

        if ((u32ErrorValue != 0U) && (pUartHandle->tStatus.pFCUART_ErrorNotify != NULL))
        {
            pUartHandle->tStatus.pFCUART_ErrorNotify(pUartHandle, u32ErrorValue);
        }

        PROCESS_UNUSED_VAR(u32ErrorValue)
    }
}

#endif

