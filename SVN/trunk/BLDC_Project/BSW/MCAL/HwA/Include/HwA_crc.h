/**
 * @file HwA_crc.h
 * @author Flagchip119
 * @brief CRC hardware access layer
 * @version 2.0.0
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip119   N/A          First version
*********************************************************************************/


#ifndef _HWA_CRC_H_
#define _HWA_CRC_H_

#include "device_header.h"

#if CRC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_crc HwA_crc
 * @ingroup module_driver_crc
 * @{
 */

/********* Local typedef ************/

/**
 * @brief The data swap for write  
 */
typedef enum{
    WRITE_DATASWAP_NONE = 0U,         /**< none data swap for write */
    WRITE_DATASWAP_BIT = 1U,          /**< only bits data swap for write */
    WRITE_DATASWAP_BIT_BYTE = 2U,     /**< both bits and bytes data swap for write */
    WRITE_DATASWAP_BYTE = 3U          /**< only bytes data swap for write */
} CRC_WriteDataSwapType;

/**
 * @brief The data swap for read 
 */
typedef enum{
    READ_DATASWAP_NONE = 0U,         /**< none data swap for read */
    READ_DATASWAP_BIT = 1U,          /**< only bits data swap for read */
    READ_DATASWAP_BIT_BYTE = 2U,     /**< both bits and bytes data swap for read */
    READ_DATASWAP_BYTE = 3U          /**< only bytes data swap for read */
} CRC_ReadDataSwapType;

/**
 * @brief The complement of reading crc data
 */
typedef enum{
    READ_DATA_NORMAL = 0U,      /**< none complement of reading crc data */
    READ_DATA_FXOR = 1U         /**< Invert or complement with 0xFFFFFFFF or 0xFFFF of crc data */
} CRC_ReadDataFXORType;

/**
 * @brief The command type of write crc data or seed value
 */
typedef enum{
    WRITE_COMMAND_DATA = 0U,     /**< write crc data */
    WRITE_COMMAND_SEED = 1U      /**< write seed value(used to initialization crc calculation) */
} CRC_WriteCommondType;

/**
 * @brief The crc mode select 
 */
typedef enum{
    CRC_BIT_16 = 0U,        /**< crc 16 bit is selected */
    CRC_BIT_32 = 1U,        /**< crc 32 bit is selected */
    CRC_BIT_8  = 2U,        /**< crc 8 bit is selected */
    CRC_BIT_INVALID = 3U    /**< the selected crc width is not support */
} CRC_BitWidthType;


/********* Local inline function ************/

/**
 * @brief set CRC CR register for writing data or seed 
 *
 * @param pCrc the base address of the CRC instance
 * @param u32Mod WAS mode
 */
LOCAL_INLINE void CRC_HWA_SetDataOrSeed(CRC_Type *const pCrc, CRC_WriteCommondType u32Mod)
{
    uint32_t u32RegVal = pCrc->CR;
    pCrc->CR = ((u32RegVal & (~(uint32_t)CRC_CR_WAS_MASK)) | CRC_CR_WAS(u32Mod));
}

/**
 * @brief set polynomial value 
 *
 * @param pCrc the base address of the CRC instance
 * @param u32Poly the polynomial value
 */
LOCAL_INLINE void CRC_HWA_SetPolyVal(CRC_Type *const pCrc, uint32_t u32Poly)
{
    pCrc->POLY = u32Poly;
}

/**
 * @brief set data register(32 bits)
 *
 * @param pCrc the base address of the CRC instance
 * @param u32Data data to be set
 */
LOCAL_INLINE void CRC_HWA_SetData_U32(CRC_Type *const pCrc, uint32_t u32Data)
{
    pCrc->DATA.uDATA = u32Data;
}

/**
 * @brief set data register(16 bits)
 *
 * @param pCrc the base address of the CRC instance
 * @param u16Data data to be set
 */
LOCAL_INLINE void CRC_HWA_SetData_U16(CRC_Type *const pCrc, uint16_t u16Data)
{
    pCrc->DATA.tDATA_16.L = u16Data;
}

/**
 * @brief set data register(low 8 bits)
 *
 * @param pCrc the base address of the CRC instance
 * @param u8Data data to be set
 */
LOCAL_INLINE void CRC_HWA_SetData_U8(CRC_Type *const pCrc, uint8_t u8Data)
{
    pCrc->DATA.tDATA_8.LL = u8Data;
}

/**
 * @brief get data register(32 bits)
 *
 * @param pCrc the base address of the CRC instance
 * 
 * @return 32-bit value
 */
LOCAL_INLINE uint32_t CRC_HWA_GetData_U32(CRC_Type *const pCrc)
{
    return (pCrc->DATA.uDATA);
}

/**
 * @brief get data register(high 16 bits)
 *
 * @param pCrc the base address of the CRC instance
 * 
 * @return high 16-bit value
 */
LOCAL_INLINE uint16_t CRC_HWA_GetData_U16_H(CRC_Type *const pCrc)
{
    return (pCrc->DATA.tDATA_16.H);
}

/**
 * @brief get data register(low 16 bits)
 *
 * @param pCrc the base address of the CRC instance
 * 
 * @return low 16-bit value
 */
LOCAL_INLINE uint16_t CRC_HWA_GetData_U16_L(CRC_Type *const pCrc)
{
    return (pCrc->DATA.tDATA_16.L);
}

/**
 * @brief set data swap for writes
 *
 * @param pCrc the base address of the CRC instance
 * @param eWrDataSwap the CRC_WriteDataSwapType type
 */
LOCAL_INLINE void CRC_HWA_SetWriteDataSwap(CRC_Type *const pCrc, CRC_WriteDataSwapType eWrDataSwap)
{
    uint32_t u32RegVal = pCrc->CR;
    pCrc->CR = ((u32RegVal & (~(uint32_t)CRC_CR_DSW_MASK)) | CRC_CR_DSW(eWrDataSwap));
}

/**
 * @brief set data swap for read
 *
 * @param pCrc the base address of the CRC instance
 * @param eRdDataSwap the eRdDataSwap type
 */
LOCAL_INLINE void CRC_HWA_SetReadDataSwap(CRC_Type *const pCrc, CRC_ReadDataSwapType eRdDataSwap)
{
    uint32_t u32RegVal = pCrc->CR;
    pCrc->CR = ((u32RegVal & (~(uint32_t)CRC_CR_DSR_MASK)) | CRC_CR_DSR(eRdDataSwap));
}

/**
 * @brief set complement read Of CRC data 
 *
 * @param pCrc the base address of the CRC instance
 * @param eRdDataFXOR the CRC_ReadDataFXORType type
 */
LOCAL_INLINE void CRC_HWA_SetReadDataFXOR(CRC_Type *const pCrc, CRC_ReadDataFXORType eRdDataFXOR)
{
    uint32_t u32RegVal = pCrc->CR;
    pCrc->CR = ((u32RegVal & (~(uint32_t)CRC_CR_FXOR_MASK)) | CRC_CR_FXOR(eRdDataFXOR));
}

/**
 * @brief set width of CRC protocol 
 *
 * @param pCrc the base address of the CRC instance
 * @param eWidth the CRC_BitWidthType type
 */
LOCAL_INLINE void CRC_HWA_SetBitWidth(CRC_Type *const pCrc, CRC_BitWidthType eWidth)
{
    uint32_t u32RegVal = pCrc->CR;
    pCrc->CR = ((u32RegVal & (~(uint32_t)CRC_CR_TCRC_MASK)) | CRC_CR_TCRC(eWidth));
}

#if (CRC_8_BIT_HARDWARE_SUPPORT == 1)
/**
 * @brief set 8bit width of CRC protocol 
 *
 * @param pCrc the base address of the CRC instance
 * @param eWidth the CRC_BitWidthType type
 */
LOCAL_INLINE void CRC_HWA_Set_8Bit_Width(CRC_Type *const pCrc, CRC_BitWidthType eWidth)
{
    uint32_t u32RegVal = pCrc->CR;
    pCrc->CR = ((u32RegVal & (~(uint32_t)CRC_CR_TCRC8_MASK)) | CRC_CR_TCRC8(eWidth));
}

/**
 * @brief get 8-bit width of CRC protocol 
 *
 * @param pCrc the base address of the CRC instance
 * 
 * @return crc bit width
 */
LOCAL_INLINE CRC_BitWidthType CRC_HWA_Get8BitWidth(CRC_Type *const pCrc)
{
    uint32_t u32TempVal = (pCrc->CR & ((uint32_t)CRC_CR_TCRC8_MASK)) >> CRC_CR_TCRC8_SHIFT;
    return ((u32TempVal == 1U)?CRC_BIT_8:CRC_BIT_INVALID);
}
#endif

/**
 * @brief get width of CRC protocol 
 *
 * @param pCrc the base address of the CRC instance
 * 
 * @return crc bit width
 */
LOCAL_INLINE CRC_BitWidthType CRC_HWA_GetBitWidth(CRC_Type *const pCrc)
{
    uint32_t u32TempVal = (pCrc->CR & ((uint32_t)CRC_CR_TCRC_MASK)) >> CRC_CR_TCRC_SHIFT;
    return ((u32TempVal == 0U)?CRC_BIT_16:CRC_BIT_32);
}

/**
 * @brief get data swap type for read
 *
 * @param pCrc the base address of the CRC instance
 * 
 * @return crc read data swap type
 */
LOCAL_INLINE CRC_ReadDataSwapType CRC_HWA_GetReadDataSwap(CRC_Type *const pCrc)
{
    CRC_ReadDataSwapType eRet = READ_DATASWAP_NONE;
    uint32_t u32TempVal = 0U;

    u32TempVal = (pCrc->CR & ((uint32_t)CRC_CR_DSR_MASK))>>CRC_CR_DSR_SHIFT;
    if (u32TempVal == 0U)
    {
        eRet = READ_DATASWAP_NONE;
    }
    else if (u32TempVal == 1U)
    {
        eRet = READ_DATASWAP_BIT;
    }
    else if (u32TempVal == 2U)
    {
        eRet = READ_DATASWAP_BIT_BYTE;
    }
    else if (u32TempVal == 3U)
    {
        eRet = READ_DATASWAP_BYTE;
    }
    else
    {
        /*Noting to do*/
    }
    return eRet;
}

/**
 * @brief get data swap type for write
 *
 * @param pCrc the base address of the CRC instance
 * 
 * @return crc write data swap type
 */
LOCAL_INLINE CRC_WriteDataSwapType CRC_HWA_GetWriteDataSwap(CRC_Type *const pCrc)
{
    CRC_WriteDataSwapType eRet;
    eRet = (CRC_WriteDataSwapType)((pCrc->CR & ((uint32_t)CRC_CR_DSW_MASK))>>CRC_CR_DSW_SHIFT);

    return eRet;
}

/** @}*/

#endif


#endif /* #ifndef _HWA_CRC_H_ */
