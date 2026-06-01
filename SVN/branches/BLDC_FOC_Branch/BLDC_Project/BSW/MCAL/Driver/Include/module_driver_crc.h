/**
 * @file module_driver_crc.h
 * @author Flagchip119
 * @brief CRC driver type definition and API
 * @version 2.0.0
 * @date 2024-07-31
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
#ifndef _DRIVER_MODULE_DRIVER_CRC_H_
#define _DRIVER_MODULE_DRIVER_CRC_H_

#include "HwA_crc.h"

#if CRC_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup module_driver_crc
 * @{
 */

/**
 * @name  CRC default init value
 *
 * @{
 */
#define CRC_DEFAULT_POLY        (0x1021U)
#define CRC_DEFAULT_INTVAL      (0U)
/** @}*/

/**
 * @name  CRC API Service IDs
 *
 * @{
 */
#define CRC_INIT_ID             0U
#define CRC_DEINIT_ID           1U
#define CRC_GET_CRC_RESULT_ID   2U
#define CRC_SET_CALC_DATA_U8    3U
#define CRC_SET_CALC_DATA_U16   4U
#define CRC_SET_CALC_DATA_U32   5U
#define CRC_SET_SEED            6U
#define CRC_SET_INPUT_DATA      7U
/** @}*/

/**
 * @name  CRC Dev Error Code
 * @brief Error Code of calling CRC apis
 *
 * @{
 */
#define CRC_E_PARAM_INSTANCE    0x01U
#define CRC_E_PARAM_POINTER     0x02U
#define CRC_E_PARAM_INVALID     0x03U
/** @}*/

typedef enum
{
    CRC_NONE            = 0,    /**< No CRC selected */
    CRC_16_CCITT        = 1,    /**< 16-bit CRC CCITT type */
    CRC_16_CCITT_FALSE  = 2,    /**< 16-bit CRC CCITT FALSE type */
    CRC_16_MODBUS       = 3,    /**< 16-bit CRC MODBUS type */
    CRC_16_USB          = 4,    /**< 16-bit CRC USB type */
    CRC_32_USER         = 5     /**< 32-bit CRC USER type */
#if CRC_8_BIT_HARDWARE_SUPPORT
    ,
    CRC_8_ROHC          = 6     /**< 8-bit CRC ROHC type */
#endif
} eCrctype;

/********* Local typedef ************/

/**
 * @brief Defines the crc configuration
 *
 * This structure is used to configure the crc
 *
 * Implements : CRC_InitType
 */
typedef struct
{
    uint8_t  u8CrcIndex;                    /**< the index of crc instance */
    CRC_WriteDataSwapType eWriteDataSwap;   /**< the data swap for write(none,bits,bytes or both) */
    CRC_ReadDataSwapType eReadDataSwap;     /**< the data swap for read(none,bits,bytes or both) */
    CRC_ReadDataFXORType eReadDataFXOR;     /**< complement of reading crc data(none or FXOR) */
    CRC_BitWidthType eBitWidth;             /**< the bit width of the CRC */
    eCrctype eType;                         /**< the CRC type */
    uint8_t _aligned[2];
    uint32_t u32SeedValue;                  /**< the seed value of crc */
    uint32_t u32CrcResult;                  /**< the crc result */
    uint32_t u32Polynomial;                 /**< the polynomial value of crc */
} CRC_InitType;


/******* Function Prototype *********/
/**
 * @brief set CRC module initialization
 *
 * @param pInitCfg the CRC_InitType type
 */
void CRC_Init(const CRC_InitType *const pInitCfg);

/**
 * @brief CRC default Init
 *
 * @param u8Instance the CRC instance to use
 * @note initialization CRC module with default value
 *       CRC-32, initial value(seed value) = 0,
 *       polynomial value = 0x1021,
 *       none swap and FXOR
 */
void CRC_DeInit(uint8_t u8Instance);

/**
 * @brief get CRC result
 *
 * @param u8Instance the CRC instance to use
 */
uint32_t CRC_GetCrcResult(uint8_t u8Instance);

/**
 * @brief set CRC DATA register 8bits
 *
 * @param u8Instance the CRC instance to use
 * @param u8Data the data to be set
 */
void CRC_SetCalcData_U8(uint8_t u8Instance, uint8_t u8Data);

/**
 * @brief set CRC DATA register 16bits
 *
 * @param u8Instance the CRC instance to use
 * @param u16Data the data to be set
 */
void CRC_SetCalcData_U16(uint8_t u8Instance, uint16_t u16Data);

/**
 * @brief set CRC low lower register
 *
 * @param u8Instance the CRC instance to use
 * @param u32Data the data to be set
 */
void CRC_SetCalcData_U32(uint8_t u8Instance, uint32_t u32Data);

/**
 * @brief set CRC seed value
 *
 * @param u8Instance the CRC instance to use
 * @param u32SeedVal seed value
 */
void CRC_SetSeed(uint8_t u8Instance, uint32_t u32SeedVal);

/**
 * @brief set CRC input data
 *
 * @param u8Instance the CRC instance to use
 * @param pData data pointer
 * @param u32DataSize input data size
 */
void CRC_SetInputData(uint8_t u8Instance, const uint8_t * pData, uint32_t u32DataSize);


/** @}*/ /* module_driver_crc */
#if defined(__cplusplus)
}
#endif

#endif

#endif  /* _DRIVER_MODULE_DRIVER_CRC_H_ */

