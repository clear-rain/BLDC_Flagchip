/**
 * @file module_driver_crc.c
 * @author Flagchip119
 * @brief CRC driver source code
 * @version 2.0.0
 * @date 22024-07-31
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip119   N/A          First version
*********************************************************************************/

#include "module_driver_crc.h"

#if CRC_INSTANCE_COUNT > 0U


#ifndef CRC_DEV_ERROR_REPORT
#define CRC_DEV_ERROR_REPORT    STD_OFF
#endif

#if CRC_DEV_ERROR_REPORT == STD_ON
#define CRC_ReportDevError(func, error) ReportDevError(CRC_MODULE_ID, func, error)
#endif

/********* Local Variables ************/
static CRC_Type *const s_apCrcBase[CRC_INSTANCE_COUNT] = CRC_BASE_PTRS;


/********* Local Functions ************/
/**
 * @brief set CRC module initialization
 *
 * @param pInitCfg the CRC_InitType type
 */
void CRC_Init(const CRC_InitType *const pInitCfg)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        CRC_ReportDevError(CRC_INIT_ID, CRC_E_PARAM_POINTER);
    }
    else if ((pInitCfg->u8CrcIndex) >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_INIT_ID, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        CRC_Type *const pCrc = s_apCrcBase[pInitCfg->u8CrcIndex];

        if (pInitCfg->eBitWidth == CRC_BIT_8)
        {
            CRC_HWA_SetBitWidth(pCrc, (CRC_BitWidthType)(0));
#if (CRC_8_BIT_HARDWARE_SUPPORT == 1)
            CRC_HWA_Set_8Bit_Width(pCrc, (CRC_BitWidthType)1);
#endif
        }
        else
        {
            /* set CRC bit width(16-bit or 32-bit) */
#if (CRC_8_BIT_HARDWARE_SUPPORT == 1)
            CRC_HWA_Set_8Bit_Width(pCrc, (CRC_BitWidthType)0);
#endif
            CRC_HWA_SetBitWidth(pCrc, pInitCfg->eBitWidth);
        }

        /* set CRC write/read swap and FXOR */
        CRC_HWA_SetWriteDataSwap(pCrc, pInitCfg->eWriteDataSwap);
        CRC_HWA_SetReadDataSwap(pCrc, pInitCfg->eReadDataSwap);
        CRC_HWA_SetReadDataFXOR(pCrc, pInitCfg->eReadDataFXOR);

        /* set CRC polynomial value */
        CRC_HWA_SetPolyVal(pCrc, pInitCfg->u32Polynomial);

        /* set CRC seed value */
        CRC_SetSeed(pInitCfg->u8CrcIndex, pInitCfg->u32SeedValue);
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief CRC default Init
 *
 * @param u8Instance the CRC instance to use
 * @note initialization CRC module with default value
 *       CRC-32, initial value(seed value) = 0,
 *       polynomial value = 0x1021,
 *       none swap and FXOR
 */
void CRC_DeInit(uint8_t u8Instance)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (u8Instance >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_DEINIT_ID, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        CRC_Type *const pCrc = s_apCrcBase[u8Instance];

        /* set CRC bit width(32-bit) */
        CRC_HWA_SetBitWidth(pCrc, CRC_BIT_32);

        /* set CRC write/read swap and FXOR */
        CRC_HWA_SetWriteDataSwap(pCrc, WRITE_DATASWAP_NONE);
        CRC_HWA_SetReadDataSwap(pCrc, READ_DATASWAP_NONE);
        CRC_HWA_SetReadDataFXOR(pCrc, READ_DATA_NORMAL);

        /* set CRC polynomial value */
        CRC_HWA_SetPolyVal(pCrc, CRC_DEFAULT_POLY);

        /* set CRC seed value */
        CRC_SetSeed(u8Instance, CRC_DEFAULT_INTVAL);
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief get CRC result
 *
 * @param u8Instance the CRC instance to use
 */
uint32_t CRC_GetCrcResult(uint8_t u8Instance)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (u8Instance >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_GET_CRC_RESULT_ID, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        CRC_Type *const pCrc = s_apCrcBase[u8Instance];
        CRC_ReadDataSwapType eTempVal = READ_DATASWAP_NONE;
        uint32_t u32Ret = 0U;

        u32Ret = CRC_HWA_GetData_U32(pCrc);

        eTempVal = CRC_HWA_GetReadDataSwap(pCrc);

#if (CRC_8_BIT_HARDWARE_SUPPORT == 1)
        if (CRC_BIT_8 == CRC_HWA_Get8BitWidth(pCrc))
        {
            /* Returns upper 8 bits of CRC because of swap in 8 bits mode */
            if ((eTempVal == READ_DATASWAP_BIT_BYTE) || (eTempVal == READ_DATASWAP_BYTE))
            {
                u32Ret = (u32Ret & 0xFF00) >> 8;
            }
            else
            {
                u32Ret = (uint8_t)u32Ret;
            }
        }
        else if (CRC_BIT_16 == CRC_HWA_GetBitWidth(pCrc))
#else
        if (CRC_BIT_16 == CRC_HWA_GetBitWidth(pCrc))
#endif
        {
            /* Returns upper 16 bits of CRC because of swap in 16 bits mode */
            if ((eTempVal == READ_DATASWAP_BIT_BYTE) || (eTempVal == READ_DATASWAP_BYTE))
            {
                u32Ret = u32Ret >> 16U;
            }
            else
            {
                u32Ret = (uint16_t)u32Ret;
            }
        }
        else
        {
            /* do nothing */
        }
    return u32Ret;
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief set CRC DATA register 8bits
 *
 * @param u8Instance the CRC instance to use
 * @param u8Data the data to be set
 */
void CRC_SetCalcData_U8(uint8_t u8Instance, uint8_t u8Data)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (u8Instance >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_SET_CALC_DATA_U8, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        CRC_Type *const pCrc = s_apCrcBase[u8Instance];

        CRC_HWA_SetData_U8(pCrc, u8Data);
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief set CRC DATA register 16bits
 *
 * @param u8Instance the CRC instance to use
 * @param u16Data the data to be set
 */
void CRC_SetCalcData_U16(uint8_t u8Instance, uint16_t u16Data)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (u8Instance >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_SET_CALC_DATA_U16, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        CRC_Type *const pCrc = s_apCrcBase[u8Instance];

        CRC_HWA_SetData_U16(pCrc, u16Data);
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief set CRC low lower register
 *
 * @param u8Instance the CRC instance to use
 * @param u32Data the data to be set
 */
void CRC_SetCalcData_U32(uint8_t u8Instance, uint32_t u32Data)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (u8Instance >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_SET_CALC_DATA_U32, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        CRC_Type *const pCrc = s_apCrcBase[u8Instance];

        CRC_HWA_SetData_U32(pCrc, u32Data);
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief set CRC seed value
 *
 * @param u8Instance the CRC instance to use
 * @param u32SeedVal seed value
 */
void CRC_SetSeed(uint8_t u8Instance, uint32_t u32SeedVal)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (u8Instance >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_SET_SEED, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        CRC_Type *const pCrc = s_apCrcBase[u8Instance];

        CRC_HWA_SetDataOrSeed(pCrc, WRITE_COMMAND_SEED);
        CRC_HWA_SetData_U32(pCrc, u32SeedVal);
        CRC_HWA_SetDataOrSeed(pCrc, WRITE_COMMAND_DATA);
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief set CRC input data
 *
 * @param u8Instance the CRC instance to use
 * @param pData data pointer
 * @param u32DataSize input data size
 */
void CRC_SetInputData(uint8_t u8Instance, const uint8_t pData[], uint32_t u32DataSize)
{
#if CRC_DEV_ERROR_REPORT == STD_ON
    if (u8Instance >= CRC_INSTANCE_COUNT)
    {
        CRC_ReportDevError(CRC_SET_INPUT_DATA, CRC_E_PARAM_INSTANCE);
    }
    else
    {
#endif
        uint32_t  u32TempLength = u32DataSize / 4;
        uint32_t *p32Data       = (uint32_t *)pData;
        CRC_Type *const pCrc    = s_apCrcBase[u8Instance];
        CRC_WriteDataSwapType WriteDataSwap;
        uint32_t              u32Index;

        WriteDataSwap = CRC_HWA_GetWriteDataSwap(pCrc);
        CRC_HWA_SetWriteDataSwap(pCrc, (CRC_WriteDataSwapType)(WRITE_DATASWAP_BYTE - WriteDataSwap));
        for (u32Index = 0; u32Index < u32TempLength; u32Index++)
        {
            CRC_SetCalcData_U32(u8Instance, *p32Data++);
        }

        u32TempLength   = u32DataSize % 4;
        uint8_t *p8Data = (uint8_t *)p32Data;
        CRC_HWA_SetWriteDataSwap(pCrc, WriteDataSwap);
        for (u32Index = 0; u32Index < u32TempLength; u32Index++)
        {
            CRC_SetCalcData_U8(u8Instance, *p8Data++);
        }
#if CRC_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

#endif

