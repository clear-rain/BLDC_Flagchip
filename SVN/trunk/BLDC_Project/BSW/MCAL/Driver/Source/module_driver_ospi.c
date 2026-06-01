/**
 * @file module_driver_ospi.c
 * @author Flagchip
 * @brief OSPI driver source code
 * @version 2.0.0
 * @date 2024-08-23
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-08-23    Flagchip122   N/A          First version
*********************************************************************************/

#include "module_driver_ospi.h"

#if OSPI_INSTANCE_COUNT > 0U

#if OSPI_MODULE_SUPPORT

#ifndef OSPI_DEV_ERROR_REPORT
#define OSPI_DEV_ERROR_REPORT    STD_OFF
#endif

#if OSPI_DEV_ERROR_REPORT == STD_ON
#define OSPI_ReportDevError(func, error) ReportDevError(OSPI_MODULE_ID, func, error)
#endif

/********* Local variable ************/
#define OSPI_LUT_KEY_VAL (0xFC03FC03UL)

static OSPI_Type * const pOspiPtrs = OSPI;

/********* Global Functions ************/
/**
 * @brief Initialize OSPI configuration
 *
 * @param base OSPI peripheral base address
 * @param config the basic configurations of the OSPI
 */
void OSPI_Init(const OSPI_ConfigType *const pConfig)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pConfig == NULL_PTR )
    {
        OSPI_ReportDevError(OSPI_INIT_ID, OSPI_E_PARAM_POINTER);
    }
    else if((pConfig->bDdrEn == true) && (pConfig->eDqsSrcSel != DQS_EXTERNAL_PADINPUT))
    {
        OSPI_ReportDevError(OSPI_INIT_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_Type* base = pOspiPtrs;
        /* Set register to reset value */
        OSPI_HWA_SetCtrlValue(base, CTRL_RST_VALUE);
        OSPI_HWA_SetSocCfgValue(base, 0U);
        OSPI_HWA_ModuleDisable(base);

        OSPI_HWA_InternalRefclkDiv(base, pConfig->eClkDivider);
        OSPI_HWA_InternalRefclkSource(base, pConfig->eClkMux);
        OSPI_HWA_EndianSelect(base, pConfig->eEndian);

        OSPI_HWA_PadIbeEnable(base);
        OSPI_HWA_InternalRefclkEnable(base);

        OSPI_HWA_DqsInvertedEnable(base);
        OSPI_HWA_DqsSource(base, pConfig->eDqsSrcSel);
        OSPI_HWA_DqsModeEnable(base);

        if(pConfig->eDqsSrcSel == DQS_EXTERNAL_PADINPUT)
        {
            if(pConfig->bDdrEn)
            {
                OSPI_HWA_DdrClkEnable(base);
                OSPI_HWA_DdrModeEnable(base);
            }
            OSPI_HWA_ObeTimRelaxEnable(base);

            OSPI_HWA_DqsOutEnable(base);
            OSPI_HWA_DqsLatEnable(base);

            OSPI_HWA_Dio3DefLow(base);
            OSPI_HWA_Dio2DefLow(base);

            OSPI_HWA_SetDataHoldTime(base, 1);
        }
        else if (pConfig->eDqsSrcSel == DQS_PAD_LOOPBACK)
        {
            OSPI_HWA_SetSampleDlyClkCycle(base, 0);
            OSPI_HWA_SelectRefClkEdge(base, 0);
            OSPI_HWA_DqsModeDisable(base);
            OSPI_HWA_SetDataHoldTime(base, 1);
        }
        else
        {
            OSPI_HWA_DqsModeDisable(base);
            OSPI_HWA_SetSampleDlyClkCycle(base, 0);
            OSPI_HWA_SelectRefClkEdge(base, 0);
            OSPI_HWA_SetDataHoldTime(base, 1);
        }

        OSPI_HWA_ModuleEnable(base);
        OSPI_HWA_ClearTxFifo(base);
        OSPI_SetFlashConfig(base, &(pConfig->tFlashConfig));
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief Get OSPI configuration
 *
 * @param config the basic configurations of the OSPI
 */
void OSPI_GetDefaultConfig(OSPI_ConfigType *config)
{
    config->bDdrEn      = true;
    config->eDqsSrcSel  = DQS_EXTERNAL_PADINPUT;
    config->eClkDivider = OSPI_CLOCK_DIV_2;
    config->eClkMux     = OSPI_CLK_MUX_PLL0;
    config->eEndian     = OSPI_LITTLE_ENDIAN;
}

/**
 * @brief De-initialize the OSPI 
 *
 * @param base OSPI peripheral base address
 */
void OSPI_Deinit(OSPI_Type *base)
{
    /* Set register to reset value */    
    OSPI_HWA_SetCtrlValue(base, CTRL_RST_VALUE);
    OSPI_HWA_SetSocCfgValue(base, 0);
    OSPI_HWA_ModuleDisable(base);
}

/**
 * @brief OSPI Config Flash Parameter
 *
 * @param base OSPI peripheral base address
 * @param pConfig the basic configurations of the device
 */
void OSPI_SetFlashConfig(OSPI_Type *base, const OSPI_DeviceConfigType *pConfig)
{   
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pConfig == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_SET_FLASHCFG_ID, OSPI_E_PARAM_POINTER);
    }
    else if( (pConfig->u8CsHoldTime > (uint8_t)16) ||
        (pConfig->u8CsSetupTime > (uint8_t)16) ||
        (pConfig->u8FlashColAddressSpace > (uint8_t)16) )
    {
        OSPI_ReportDevError(OSPI_SET_FLASHCFG_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_HWA_SetCsHoldTime(base, pConfig->u8CsHoldTime);
        OSPI_HWA_SetCsSetupTime(base, pConfig->u8CsSetupTime);
        OSPI_HWA_CfgDelayLine(base, pConfig->u8DelayLine);

        OSPI_HWA_SetFlashAddr(base, pConfig->u32FlashAddress);
        OSPI_HWA_SetFlashTopAddr(base, pConfig->u32FlashTopAddress);
        OSPI_HWA_SetFlashAddrMode(base, pConfig->u8WordAddressable);
        OSPI_HWA_SetColAddrSpace(base, pConfig->u8FlashColAddressSpace);
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI Config LUT
 *
 * @param base OSPI peripheral base address
 * @param index index to be written
 * @param cmd Command sequence array
 * @param count Number of sequences
 *
 */
void OSPI_UpdateLUT(OSPI_Type *base, uint32_t index, const uint32_t *cmd, uint32_t count)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(cmd == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_UPDATE_LUT_ID, OSPI_E_PARAM_POINTER);
    }
    else if((count > 16U) || (index >3U))
    {
        OSPI_ReportDevError(OSPI_UPDATE_LUT_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif

        uint8_t i = 0;
        volatile uint32_t *lutBase;

        /* Wait for bus idle before change flash configuration. */
        if (OSPI_Wait_Bus_Idle() != OSPI_STATUS_SUCCESS)
        {
            return;
        }

        /* Unlock LUT for update. */
        base->LUT_KEY = OSPI_LUT_KEY_VAL;
        base->LUT_CFG  = 0x02;

        lutBase = &base->LUT[index*4];
        for (i = 0; i < count; i++)
        {
            *lutBase++ = *cmd++;
        }

        /* Lock LUT. */
        base->LUT_KEY = OSPI_LUT_KEY_VAL;
        base->LUT_CFG  = 0x01;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI Wait bus command transaction done
 *
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Wait_Cmd_Done(void)
{
    OSPI_StatusType eRet = OSPI_STATUS_TIMEOUT;
    uint32_t timeout = 0xfffff;
    do
    {
        if( (OSPI_HWA_GetFlag(pOspiPtrs)&OSPI_FLAG_BUSDF_MASK ) != (uint32_t)0)
        {
            OSPI_HWA_ClearFlag(pOspiPtrs,OSPI_FLAG_BUSDF_MASK);
            eRet = OSPI_STATUS_SUCCESS;
            break;
        }
        timeout--;
    }while(timeout);
    return eRet;
}

/**
 * @brief OSPI Wait bus command transaction done
 *
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Wait_Bus_Idle(void)
{
    OSPI_StatusType eRet = OSPI_STATUS_TIMEOUT;
    uint32_t timeout = 0xfffff;
    do
    {
        if((OSPI_HWA_GetStatus(pOspiPtrs)&OSPI_STATUS_BUSY_MASK) == (uint32_t)0)
        {
            eRet = OSPI_STATUS_SUCCESS;
            break;
        }
        timeout--;
    }while(timeout);
    return eRet;
}

/**
 * @brief OSPI write fifo，fifo size is 16words.
 *
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the write buffer start address.
 * @param u8Size fifo size to be written.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Write_Fifo(uint8_t u8SeqId, uint32_t *pBuf, uint8_t u8Size)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pBuf == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_WRITE_FIFO_ID, OSPI_E_PARAM_POINTER);
    }
    else if(u8SeqId > 3U)
    {
        OSPI_ReportDevError(OSPI_WRITE_FIFO_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_StatusType eRet = OSPI_STATUS_SUCCESS;

        for(uint16_t i=0;i<u8Size;i++)
        {
            OSPI_HWA_WriteTxData(pOspiPtrs,pBuf[i]);
        }

        OSPI_HWA_SetCmdIdSize(pOspiPtrs,u8SeqId, (uint16_t)((uint16_t)u8Size*(uint8_t)4));

        eRet = OSPI_Wait_Cmd_Done();
        if(eRet == OSPI_STATUS_SUCCESS)
        {
            eRet = OSPI_Wait_Bus_Idle();
        }
        OSPI_HWA_ClearTxFifo(pOspiPtrs);
        return eRet;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI read fifo，fifo size is 16words.
 *
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the read buffer start address.
 * @param u16Size fifo size to be read.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Read_Fifo(uint8_t u8SeqId, uint32_t *pBuf, uint8_t u8Size)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pBuf == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_READ_FIFO_ID, OSPI_E_PARAM_POINTER);
    }
    else if(u8SeqId > 3U)
    {
        OSPI_ReportDevError(OSPI_READ_FIFO_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_StatusType eRet = OSPI_STATUS_SUCCESS;

        OSPI_HWA_SetCmdIdSize(pOspiPtrs,u8SeqId, (uint16_t)((uint16_t)u8Size*(uint8_t)4));

        eRet = OSPI_Wait_Cmd_Done();

        if(eRet == OSPI_STATUS_SUCCESS)
        {
            for(uint8_t i=0;i<u8Size;i++)
            {
                pBuf[i] = OSPI_HWA_ReadSecondaryRcvFifoReg(pOspiPtrs);
            }
        }
        OSPI_HWA_ClearRxFifo(pOspiPtrs);
        return eRet;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI write sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the write buffer start address.
 * @param u32Size data size to be written.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Write(uint32_t u32Addr, uint8_t u8SeqId, uint32_t *pBuf, uint32_t u32Size)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pBuf == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_WRITE_ID, OSPI_E_PARAM_POINTER);
    }
    else if(u8SeqId > 3U)
    {
        OSPI_ReportDevError(OSPI_WRITE_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_StatusType eRet = OSPI_STATUS_SUCCESS;
        uint32_t u32Loop = u32Size/(uint32_t)16;
        uint8_t u8Remind = (uint8_t)(u32Size%(uint32_t)16);

        if(u32Loop!=(uint32_t)0)
        {
            for(uint32_t i=0;i<u32Loop;i++)
            {
                if(eRet == OSPI_STATUS_SUCCESS)
                {
                    OSPI_HWA_SetFlashAddr(pOspiPtrs,u32Addr+i*(uint32_t)64);
                    eRet = OSPI_Write_Fifo(u8SeqId,pBuf+(uint32_t)16*i,(uint8_t)16);
                }
            }
        }
        if(u8Remind!=(uint8_t)0)
        {
            if(eRet == OSPI_STATUS_SUCCESS)
            {
                OSPI_HWA_SetFlashAddr(pOspiPtrs,u32Addr+u32Loop*(uint32_t)64);
                eRet = OSPI_Write_Fifo(u8SeqId,pBuf+(uint32_t)16*u32Loop,u8Remind);
            }
        }
        return eRet;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI write bytes sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the write buffer start address.
 * @param u16Size data size to be written.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_WriteBytes(uint32_t u32Addr, uint8_t u8SeqId, uint32_t *pBuf, uint16_t u16Size)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pBuf == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_WRITE_BYTES_ID, OSPI_E_PARAM_POINTER);
    }
    else if(u8SeqId > 3U)
    {
        OSPI_ReportDevError(OSPI_WRITE_BYTES_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_StatusType eRet = OSPI_STATUS_SUCCESS;
        uint16_t u16LoopI, u16LoopMax;

        OSPI_HWA_SetFlashAddr(pOspiPtrs, u32Addr);

        u16LoopMax = u16Size >> 2;
        for (u16LoopI = 0; u16LoopI < u16LoopMax; u16LoopI++)
        {
            OSPI_HWA_WriteTxData(pOspiPtrs, pBuf[u16LoopI]);
        }

        if (u16Size & 0x3)
        {
            OSPI_HWA_WriteTxData(pOspiPtrs, pBuf[u16LoopI]);
            u16LoopI++;
        }
        for (; u16LoopI < 4; u16LoopI++)
        {
            OSPI_HWA_WriteTxData(pOspiPtrs, 0x00000000);
        }

        OSPI_HWA_SetCmdIdSize(pOspiPtrs, u8SeqId, u16Size);

        eRet = OSPI_Wait_Cmd_Done();
        if(eRet == OSPI_STATUS_SUCCESS)
        {
            eRet = OSPI_Wait_Bus_Idle();
        }
        OSPI_HWA_ClearTxFifo(pOspiPtrs);

        return eRet;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI write command sequence.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_WriteConfig(uint32_t u32Addr,uint8_t u8SeqId)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(u8SeqId > 3U)
    {
        OSPI_ReportDevError(OSPI_WRITE_CONFIG_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_StatusType eRet = OSPI_STATUS_SUCCESS;

        OSPI_HWA_SetFlashAddr(pOspiPtrs,u32Addr);
        OSPI_HWA_SetCmdIdSize(pOspiPtrs,u8SeqId, 0);

        eRet = OSPI_Wait_Cmd_Done();
        if(eRet == OSPI_STATUS_SUCCESS)
        {
            eRet = OSPI_Wait_Bus_Idle();
        }

        OSPI_HWA_ClearTxFifo(pOspiPtrs);

        return eRet;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI read sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the read buffer start address.
 * @param u32Size data size to be read.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Read(uint32_t u32Addr,uint8_t u8SeqId,uint32_t *pBuf,uint32_t u32Size)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pBuf == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_WRITE_ID, OSPI_E_PARAM_POINTER);
    }
    else if(u8SeqId > 3U)
    {
        OSPI_ReportDevError(OSPI_WRITE_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_StatusType eRet = OSPI_STATUS_SUCCESS;
        uint32_t u32Loop = u32Size/(uint32_t)16;
        uint8_t u8Remind = (uint8_t) (u32Size%(uint32_t)16);
        if(u32Loop!=(uint32_t)0)
        {
            for(uint32_t i=0;i<u32Loop;i++)
            {
                if(eRet == OSPI_STATUS_SUCCESS)
                {
                    OSPI_HWA_SetFlashAddr(pOspiPtrs,u32Addr+i*(uint32_t)64);
                    eRet = OSPI_Read_Fifo(u8SeqId,pBuf+(uint32_t)16*i,(uint8_t)16);
                }
            }
        }
        if(u8Remind!=(uint8_t)0)
        {
            if(eRet == OSPI_STATUS_SUCCESS)
            {
                OSPI_HWA_SetFlashAddr(pOspiPtrs,u32Addr+u32Loop*(uint32_t)64);
                eRet = OSPI_Read_Fifo(u8SeqId,pBuf+(uint32_t)16*u32Loop,u8Remind);
            }
        }
        return eRet;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief OSPI read bytes sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the read buffer start address.
 * @param u16Size data size to be read.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_ReadBytes(uint32_t u32Addr, uint8_t u8SeqId, uint32_t *pBuf, uint16_t u16Size)
{
#if OSPI_DEV_ERROR_REPORT == STD_ON
    if(pBuf == NULL_PTR)
    {
        OSPI_ReportDevError(OSPI_READ_BYTES_ID, OSPI_E_PARAM_POINTER);
    }
    else if(u8SeqId > 3U)
    {
        OSPI_ReportDevError(OSPI_READ_BYTES_ID, OSPI_E_PARAM_INVALID);
    }
    else
    {
#endif
        OSPI_StatusType eRet = OSPI_STATUS_SUCCESS;
        uint8_t u8LoopI, u8LoopMax;

        OSPI_HWA_SetFlashAddr(pOspiPtrs, u32Addr);
        OSPI_HWA_SetCmdIdSize(pOspiPtrs, u8SeqId, u16Size);

        eRet = OSPI_Wait_Cmd_Done();
        if(eRet == OSPI_STATUS_SUCCESS)
        {
            u8LoopMax = OSPI_HWA_GetRxFifoFillLevel(pOspiPtrs);
            for (u8LoopI = 0; u8LoopI < u8LoopMax; u8LoopI++)
            {
                pBuf[u8LoopI] = OSPI_HWA_ReadSecondaryRcvFifoReg(pOspiPtrs);
            }
        }
        OSPI_HWA_ClearRxFifo(pOspiPtrs);

        return eRet;
#if OSPI_DEV_ERROR_REPORT == STD_ON
    }
#endif
}



#endif /* OSPI_MODULE_SUPPORT */

#endif
