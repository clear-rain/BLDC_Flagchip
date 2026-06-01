/**
 * @file module_driver_flash.h
 * @author Flagchip
 * @brief FLASH driver type definition and API
 * @version 2.0.0
 * @date 2024-02-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/** ********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-07-31    Flagchip120  N/A          Release version for FC4150
********************************************************************************
*/
#ifndef _DRIVER_MODULE_DRIVER_FLASH_H_
#define _DRIVER_MODULE_DRIVER_FLASH_H_

#include "device_header.h"

#if FMC_INSTANCE_COUNT > 0U


/**
 * @addtogroup module_driver_flash
 * @{
 */


/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

/**
 * @name  FLASH API Service IDs
 *
 * @{
 */
#define FLASH_SYNC_ERASE_ID                  0U
#define FLASH_SYNC_WRITE_ID                  1U
#define FLASH_ASYNC_ERASE_ID                 2U
#define FLASH_ASYNC_WRITE_ID                 3U
#define FLASH_INTERRUPT_ERASE_ID             4U
#define FLASH_INTERRUPT_WRITE_ID             5U
#define NVR_SYNC_ERASE_ID                    6U
#define NVR_SYNC_WRITE_ID                    7U
/** @}*/

/** NVR start address */
#define NVR_FLASH_ADDR_START                      0x01000000U
/** NVR0 end address */
#define NVR_FLASH_ADDR_END                        0x010003FFU
/** Program minimum size */
#define NVR_PROGRAM_PAGE_MIN_SIZE                  0x08U
/** NVR erase sector size */
#define NVR_ERASE_SECTOR_SIZE                      0x400U /* 1024 bytes */
/** NVR program maximum */
#define NVRFLASH_PROGRAM_PAGE_MAX_SIZE             0x80U  /* 128 bytes */
/** NVR num */
#define NVR_NUM                                    1U
/** NVR Sector num */
#define NVR_SECTOR_NUM                             1U

#define FLASH_HARDWARE_STATUS_ADDR       (0x40020000U)
#define FLASH_HARDWARE_STATUS_MASK       (0x00FF0000U)
#define FLASH_HARDWARE_STATUS_IDLE       (0xFFU)




/**
 * @name  FLASH Dev Error Code
 * @brief Error Code of calling FLASH apis
 *
 * @{
 */
#define FLASH_E_PARAM_POINTER   		0x01U
/** @}*/

/**
 * @brief FLASH API error status
 *
 */
typedef enum
{
    FLASH_ERROR_OK                  =  0x00U,/**< FLASH_ERROR_OK means no error */

    FLASH_ERROR_INVALID_VERSION,             /**< FLASH_ERROR_INVALID_VERSION means rom code api version is not same */
    FLASH_ERROR_FAILED,                      /**< FLASH_ERROR_FAILED means operation is failed */
    FLASH_ERROR_INVALID_PARAM,               /**< FLASH_ERROR_INVALID_PARAM means parameters are invalid */
    FLASH_ERROR_INVALID_ADDR,                /**< FLASH_ERROR_INVALID_ADDR means address is invalid */
    FLASH_ERROR_INVALID_SIZE,                /**< FLASH_ERROR_INVALID_SIZE means size is invalid */
    FLASH_ERROR_INVALID_SEQUENCE,            /**< FLASH_ERROR_INVALID_SEQUENCE means sequence is error */
    FLASH_ERROR_TIMEOUT                      /**< FLASH_ERROR_TIMEOUT means operation is timeout */
} FLASH_StatusType;

/**
 * @brief FLASH ECC error status
 *
 */
typedef enum
{
    FLASH_ECC_ERROR_NONE,
    FLASH_ECC_ERROR_SBC,
    FLASH_ECC_ERROR_DBC
} ECC_StatusType;

/**
 * @brief FLASH async prog/erase status
 *
 */
typedef enum Async_Return
{
    FLASH_ASYNC_ERR_OK = 0,     /**< Indicate that a function was successfully processed.*/
    FLASH_ASYNC_ERR_NOT_OK = 1, /**< Indicate that a function was NOT successfully processed.*/
    FLASH_ASYNC_ERR_BUSY = 2,   /**< Indicate that a function was busy .*/
} Async_Return_t; /**< Some values from a called function.*/

/**
 * @brief FLASH interrupt prog/erase status
 *
 */
typedef enum Interrupt_Return
{
    FLASH_INTERRUPT_ERR_OK = 0,      /**< Indicate that a function was successfully processed.*/
    FLASH_INTERRUPT_ERR_NOT_OK = 1,  /**< Indicate that a function was NOT successfully processed.*/
    FLASH_INTERRUPT_ERR_BUSY = 2,    /**< Indicate that a function was busy */
} Fls_ReturnType;

/**
 * @brief FLASH instance
 *
 */
typedef enum
{
    FLASH_INSTANCE_0 = 0U,
} FLASH_InstanceType;

/**
 * @brief FLASH status
 *
 */
typedef enum fls_Ret
{
    FLS_IDLE = 0,         /**< Indicate that a function was successfully processed.*/
    FLS_ERASING = 1,      /**< Indicate that a function was NOT successfully processed.*/
    FLS_WRITING = 2,      /**< Indicate that a function was waiting .*/
    FLS_READING = 3,      /**< Indicate that a function was reading */
    FLS_ERASE_ERROR = 4,  /**< Indicate that a function was in erasing error */
    FLS_WRITE_ERROR = 5,  /**< Indicate that a function was in waiting error */
    FLS_PARA_ERROR = 6,   /**< Indicate that a function contains parameter error */
} Fls_Status_t;



/** ########################################## Type define ################################################ */

/**
 * @brief The structure of the FLASH processing handle
 * 
 **/
typedef struct _FLASH_HandleType
{
    FLASH_InstanceType eInstance;       /**< Flash instance*/
    char _aligned[3];
    /**
     * @brief Flash handle status
     *
     */
    struct
    {
        uint32_t                    u32Address;          /**< Flash address  */
        uint32_t                    u32Length;           /**< Flash Length   */
        uint32_t                    u32CurrentAddress;   /**< Current address */
        uint32_t                    u32ProgramSize;      /**< Program segment size */
        uint32_t                    u32EraseSectorSize;  /**< Erase sector size    */
        uint32_t                    u32ErrorAdress;      /**< Error address        */
        uint8_t                     *pData;              /**< Data buffer          */
        Fls_Status_t                eFlsStatus;          /**< Flash operation status */
        char _aligned1[3];
    } tStatus;
} FLASH_HandleType;

/**
 * @brief Flash driver parameter define
 *
 */
typedef struct
{
    uint32_t      u32Address;            /**< Logical target address                  */
    uint32_t      u32Length;             /**< Length in logical sectors or bytes      */
    uint8_t       *pData;                /**< Pointer to data buffer (read only)      */
    uint8_t      (* wdTriggerFct)(void); /**< Pointer to watchdog handling function   */
    uint32_t     u32ErrorAddress;        /**< Error address                           */

} FLASH_DRIVER_ParamType;

/**
 * @brief flash init function
 *
 */
void FLASHDRIVER_Init(void);

/**
 * @brief flash driver erase function
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash erase function parameter, address is align to sector, and length is align to sector
 * @return ErrorType
 */
FLASH_StatusType FLASHDRIVER_SyncErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief flash driver write function
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to page, and length is align to page
 * @return ErrorType
 */
FLASH_StatusType FLASHDRIVER_SyncWrite(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief flash driver erase a sector
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to sector, and length is align to sector
 */
void FLASHDRIVER_AsyncErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief flash driver erase a sector
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to max size of program
 */
void FLASHDRIVER_AsyncWrite(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief flash driver check current status when erasing
 *
 * @param pFlashHandle the Flash instance to use
 * @return Fls_Return_t return the erase status
 */
Async_Return_t FLASHDRIVER_AsyncCheckEraseStatus(FLASH_HandleType *pFlashHandle);

/**
 * @brief flash driver check current status when writing
 *
 * @param pFlashHandle the Flash instance to use
 * @return Fls_Return_t return the write status
 */
Async_Return_t FLASHDRIVER_AsyncCheckWriteStatus(FLASH_HandleType *pFlashHandle);

/**
 * @brief NVR driver write function
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *   .=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.       *
 *    |                     ______                     |      *
 *    |                  .-"      "-.                  |      *
 *    |                 /            \                 |      *
 *    |     _          |              |          _     |      *
 *    |    ( \         |,  .-.  .-.  ,|         / )    |      *
 *    |     > "=._     | )(__/  \__)( |     _.=" <     |      *
 *    |    (_/"=._"=._ |/     /\     \| _.="_.="\_)    |      *
 *    |           "=._"(_     ^^     _)"_.="           |      *
 *    |               "=\__|IIIIII|__/="               |      *
 *    |              _.="| \IIIIII/ |"=._              |      *
 *    |    _     _.="_.="\          /"=._"=._     _    |      *
 *    |   ( \_.="_.="     `--------`     "=._"=._/ )   |      *
 *    |    > _.="                            "=._ <    |      *
 *    |   (_/                                    \_)   |      *
 *    |                                                |      *
 *    '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-='      *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to page, and length is align to page
 * @return ErrorType
 */
FLASH_StatusType NVRDRIVER_SyncWrite(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief NVR driver erase function
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *   .=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.       *
 *    |                     ______                     |      *
 *    |                  .-"      "-.                  |      *
 *    |                 /            \                 |      *
 *    |     _          |              |          _     |      *
 *    |    ( \         |,  .-.  .-.  ,|         / )    |      *
 *    |     > "=._     | )(__/  \__)( |     _.=" <     |      *
 *    |    (_/"=._"=._ |/     /\     \| _.="_.="\_)    |      *
 *    |           "=._"(_     ^^     _)"_.="           |      *
 *    |               "=\__|IIIIII|__/="               |      *
 *    |              _.="| \IIIIII/ |"=._              |      *
 *    |    _     _.="_.="\          /"=._"=._     _    |      *
 *    |   ( \_.="_.="     `--------`     "=._"=._/ )   |      *
 *    |    > _.="                            "=._ <    |      *
 *    |   (_/                                    \_)   |      *
 *    |                                                |      *
 *    '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-='      *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash erase function parameter, address is align to sector, and length is align to sector
 * @return ErrorType
 */
FLASH_StatusType NVRDRIVER_SyncErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief flash driver interrupt erase
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam erase parameter
 */
void FLASHDRIVER_InterruptErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief flash driver interrupt write
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam write parameter
 */
void FLASHDRIVER_InterruptProgram(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam);

/**
 * @brief flash driver ecc type check
 *
 * @param pFlashHandle the Flash instance to use
 * @param pECCType ecc type input addr
 * @return return the ecc check status
 */
uint32_t FLASHDRIVER_ECCType_Check(FLASH_HandleType *pFlashHandle, ECC_StatusType *pECCType);

/**
 * @brief flash driver ecc correct
 *
 * @param pFlashHandle the Flash instance to use
 * @param pECCParam ecc correct input para addr
 * @param pECCType Pointer to store the type of ECC error detected.
 * @return rreturn the ecc correct status
 */
uint32_t FLASHDRIVER_ECC_Test(FLASH_HandleType *pFlashHandle, FLASH_DRV_ECC_CHECK_CFG_T *pECCParam, ECC_StatusType *pECCType);

/**
 * @brief flash driver misr test
 *
 * @param pFlashHandle the Flash instance to use
 * @param pMisrParam misr test input para addr
 * @param tMisrOutput misr test output para addr
 * @return return misr test status
 */
uint32_t FLASHDRIVER_Integrity_Test(FLASH_HandleType *pFlashHandle, FLASH_DRV_TEST_CHECK_CFG_T *pMisrParam, FLASH_DRV_TEST_CHECK_DATA_CFG_T *tMisrOutput);

/**
 * @brief flash driver test close
 *
 * @param pFlashHandle the Flash instance to use
 */
void FLASHDRIVER_Test_Close(FLASH_HandleType *pFlashHandle);

/**
 * @brief Process Flash interrupt
 *
 * @param pFlashHandle flash handle point
 * @return process result
 */
Fls_ReturnType Fls_CommonProcessInterrupt(FLASH_HandleType *pFlashHandle);

/** @}*/

#endif

#endif /* FLASHDRV_H_ */
