/**
 * @file module_driver_ospi.h
 * @author Flagchip
 * @brief OSPI driver type definition and API
 * @version 2.0.0
 * @date 2024-08-23
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-08-23    Flagchip122   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_OSPI_H_
#define _DRIVER_MODULE_DRIVER_OSPI_H_

#include "HwA_ospi.h"

#if OSPI_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_ospi
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif


/**
 * @name  Ospi API Service IDs
 * @brief These macros define the command IDs used for communication with the on-chip OSPI interface.
 *        Each ID corresponds to a specific operation that can be performed via the OSPI interface.
 *
* @{
 */
#define OSPI_INIT_ID                        ((uint8) 0x00u)             /**< Initialize OSPI interface */
#define OSPI_SET_FLASHCFG_ID                ((uint8) 0x01u)             /**< Set OSPI flash configuration */
#define OSPI_UPDATE_LUT_ID                  ((uint8) 0x02u)             /**< Update OSPI look-up table */
#define OSPI_WRITE_FIFO_ID                  ((uint8) 0x03u)             /**< Write data to OSPI FIFO */
#define OSPI_READ_FIFO_ID                   ((uint8) 0x04u)             /**< Read data from OSPI FIFO */
#define OSPI_WRITE_ID                       ((uint8) 0x05u)             /**< Write data to OSPI */
#define OSPI_READ_ID                        ((uint8) 0x06u)             /**< Read data from OSPI */
#define OSPI_WRITE_BYTES_ID                 ((uint8) 0x07u)             /**< Write bytes to OSPI */
#define OSPI_READ_BYTES_ID                  ((uint8) 0x08u)             /**< Read bytes from OSPI */
#define OSPI_WRITE_CONFIG_ID                ((uint8) 0x07u)             /**< Write OSPI configuration */
/** @}*/

/**
 * @name  Ospi Dev Error Code
 * @brief Error Code of calling OSPI apis
 * @{
 */
#define OSPI_E_PARAM_POINTER            ((uint8)0x01u)  /**< Invalid pointer */
#define OSPI_E_PARAM_INVALID            ((uint8)0x02u)  /**< Invalid parameter */

/** @}*/

/**
 * @name    IO configurations IO configurations for the OSPI interface
 * @brief   IO configurations for the OSPI interface
 * @{
 */
#define SINGLE_IO               0x00    /**< Single I/O */
#define DUAL_IO                 0x01    /**< Dual I/O */
#define QUAD_IO                 0x02    /**< Quad I/O */
#define OCTAL_IO                0x03    /**< Octal I/O */
/** @}*/

/**
 * @name    OSPI command_set OSPI command set definitions
 * @brief   OSPI command set definitions
 * @{
 */
#define OSPI_CMD_STOP         0x0   /**< Stop command */
#define OSPI_CFG_DRV          0x1   /**< Configure drive strength */
#define OSPI_CFG_ADDR         0x2   /**< Configure address */
#define OSPI_CMD_DUMMY        0x3   /**< Configure dummy cycles */
#define OSPI_CFG_MODE8        0x4   /**< Configure mode 8 */
#define OSPI_CFG_MODE2        0x5   /**< Configure mode 2 */
#define OSPI_CFG_MODE4        0x6   /**< Configure mode 4 */
#define OSPI_READ_DRV         0x7   /**< Configure read drive strength */
#define OSPI_WRITE_DRV        0x8   /**< Configure write drive strength */
#define OSPI_CMD_END          0x9   /**< End command */
#define OSPI_CFG_ADDR_DDR     0xA   /**< Configure address DDR */
#define OSPI_CFG_MODE8_DDR    0xB   /**< Configure mode 8 DDR */
#define OSPI_CFG_MODE2_DDR    0xC   /**< Configure mode 2 DDR */
#define OSPI_CFG_MODE4_DDR    0xD   /**< Configure mode 4 DDR */
#define OSPI_READ_DRV_DDR     0xE   /**< Configure read drive strength DDR */
#define OSPI_WRITE_DRV_DDR    0xF   /**< Configure write drive strength DDR */
#define OSPI_CFG_DRV_DDR      0x11  /**< Configure drive strength DDR */
#define OSPI_CFG_CADDR        0x12  /**< Configure CADDR */
#define OSPI_CFG_CADDR_DDR    0x13  /**< Configure CADDR DDR */
/*#define INSTR_CODE_DATA_LINEAR  0x10*/
/*#define INSTR_CODE_JMP_TO_SEQ   0x14*/
/** @}*/

/**
 * @brief Status returned by OSPI APIs
 *
 */
typedef enum {
    OSPI_STATUS_SUCCESS = 0,    /**< API execute successfully */
    OSPI_STATUS_PARAM_ERR,      /**< parameter error */
    OSPI_STATUS_TIMEOUT         /**< API execute timeout */
} OSPI_StatusType;

/**
 * @brief Defines the types of OSPI operations.
 * 
 * This enumeration defines the different types of operations that can be performed over an OSPI interface.
 * 
 */
typedef enum
{
    OSPI_OPERATION_COMMAND,         /**< OSPI operation: Only command, both TX and Rx buffer are ignored. */
    OSPI_OPERATION_CONFIG,          /**< OSPI operation: Configure device mode, the TX fifo size is fixed in LUT. */
    OSPI_OPERATION_READ,            /**< OSPI operation: Read, only Rx Buffer is effective. */
    OSPI_OPERATION_WRITE,           /**< OSPI operation: Read, only Tx Buffer is effective. */
} OSPI_OperationType;


/**
 * @brief Define the structure for OSPI device configuration.
 * 
 * This structure is used to configure the parameters of the OSPI (OctoSPI) interface.
 */
typedef struct
{
    uint32_t  u32FlashAddress;      /**< The base address of the flash. */
    uint32_t  u32FlashTopAddress;   /**< The top address of the flash. */
    uint8_t   u8FlashColAddressSpace;/**< The column address space of the flash. */
    uint8_t   u8WordAddressable;     /**< Indicates if the device is word addressable. */
    uint8_t   u8CsHoldTime;          /**< Chip select hold time. */
    uint8_t   u8CsSetupTime;         /**< Chip select setup time. */
    uint8_t   u8DelayLine;           /**< Delay line value. */
    uint8_t  _aligned[3];           /**< Alignment padding. */
} OSPI_DeviceConfigType;

/**
 * @brief Defines the OSPI configuration structure type, 
 *        used to configure various parameters of the OSPI (Octa-SPI) controller.
 *
 */
typedef struct
{
    OSPI_DeviceConfigType    tFlashConfig;   /**< OSPI device configuration. */
    OSPI_DqsSrcSelType       eDqsSrcSel;      /**< DQS source select. */
    OSPI_ClockDivideType     eClkDivider;     /**< Clock divider. */
    OSPI_ClockMuxType        eClkMux;         /**< Clock mux. */
    OSPI_EndianType          eEndian;         /**< Endianness. */
    bool                     bDdrEn;          /**< DDR enable. */
    uint8_t                 _aligned[3];      /**< Alignment padding. */
} OSPI_ConfigType;

/**
 * @brief FlexSPI Transfer structure definition.
 *
 * This structure defines the parameters required for a FlexSPI transfer operation.
 *
 *
 */
typedef struct _flexspi_transfer
{
    uint32_t              deviceAddress;           /**< Operation device address. */
    uint32_t             *data;                    /**< Data buffer. */
    size_t                dataSize;                /**< Data size in bytes. */
    OSPI_OperationType    cmdType;                 /**< Execution command type. */
    uint8_t               seqIndex;                /**< Sequence ID for command. */
    uint8_t               _aligned[2];
} OSPI_TransferType;

#define OSPI_LUT_SEQ(cmd0, pad0, op0, cmd1, pad1, op1)                                                              \
    (OSPI_LUT_INSTR0_CMD_NAME(cmd0) | OSPI_LUT_INSTR0_PAD_NUM(pad0) | OSPI_LUT_INSTR0_DRV_CMD(op0) | \
     OSPI_LUT_INSTR1_CMD_NAME(cmd1) | OSPI_LUT_INSTR1_PAD_NUM(pad1) | OSPI_LUT_INSTR1_DRV_CMD(op1))

/********* Global Functions ************/
/**
 * @brief Initialize OSPI configuration
 *
 * @param pConfig the basic configurations of the OSPI
 */
void OSPI_Init(const OSPI_ConfigType *const pConfig);

/**
 * @brief Get OSPI configuration
 *
 * @param config the basic configurations of the OSPI
 */
void OSPI_GetDefaultConfig(OSPI_ConfigType *config);

/**
 * @brief De-initialize the OSPI 
 *
 * @param base OSPI peripheral base address
 */
void OSPI_Deinit(OSPI_Type *base);

/**
 * @brief OSPI Config Flash Parameter
 *
 * @param base OSPI peripheral base address
 * @param pConfig the basic configurations of the device
 */
void OSPI_SetFlashConfig(OSPI_Type *base, const OSPI_DeviceConfigType *pConfig);

/**
 * @brief OSPI Config LUT
 *
 * @param base OSPI peripheral base address
 * @param index index to be written
 * @param cmd Command sequence array
 * @param count Number of sequences
 *
 */
void OSPI_UpdateLUT(OSPI_Type *base, uint32_t index, const uint32_t *cmd, uint32_t count);

/**
 * @brief OSPI Wait bus command transaction done
 *
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Wait_Cmd_Done(void);

/**
 * @brief OSPI Wait Tx FIFO transfer complete
 *
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Wait_Tx_Fifo_Empty(void);

/**
 * @brief OSPI Wait bus command transaction done
 *
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Wait_Bus_Idle(void);

/**
 * @brief OSPI write fifo，fifo size is 16words.
 *
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the write buffer start address.
 * @param u8Size fifo size to be written.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Write_Fifo(uint8_t u8SeqId,uint32_t *pBuf,uint8_t u8Size);

/**
 * @brief OSPI read fifo，fifo size is 16words.
 *
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the read buffer start address.
 * @param u8Size fifo size to be read.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Read_Fifo(uint8_t u8SeqId,uint32_t *pBuf,uint8_t u8Size);

/**
 * @brief OSPI write sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the write buffer start address.
 * @param u32Size data size to be written.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Write(uint32_t u32Addr,uint8_t u8SeqId,uint32_t *pBuf,uint32_t u32Size);

/**
 * @brief OSPI write bytes sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the write buffer start address.
 * @param u16Size data size to be written.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_WriteBytes(uint32_t u32Addr, uint8_t u8SeqId, uint32_t *pBuf, uint16_t u16Size);

/**
 * @brief OSPI write command sequence.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_WriteConfig(uint32_t u32Addr,uint8_t u8SeqId);

/**
 * @brief OSPI read sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the read buffer start address.
 * @param u32Size data size to be read.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_Read(uint32_t u32Addr,uint8_t u8SeqId,uint32_t *pBuf,uint32_t u32Size);

/**
 * @brief OSPI read bytes sequence data.
 *
 * @param u32Addr the flash map address.
 * @param u8SeqId the cmd id location in lut.
 * @param pBuf the read buffer start address.
 * @param u16Size data size to be read.
 * @return OSPI_StatusType whether the operation is successfully
 */
OSPI_StatusType OSPI_ReadBytes(uint32_t u32Addr, uint8_t u8SeqId, uint32_t *pBuf, uint16_t u16Size);



#if defined(__cplusplus)
}

#endif

/** @} */

#endif
#endif /* _DRIVER_MODULE_DRIVER_OSPI_H_ */
