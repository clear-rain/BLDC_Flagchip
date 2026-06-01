/**
 * @file module_driver_fcspi.h
 * @author Flagchip051
 * @brief FCSPI driver type definition and API
 * @version 2.0.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip051   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_FCSPI_H_
#define _DRIVER_MODULE_DRIVER_FCSPI_H_

#include "HwA_fcspi.h"

#if FCSPI_INSTANCE_COUNT > 0U
/**
 * @addtogroup module_driver_fcspi
 *
 * @{
 */

#include "module_driver_dma.h"
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  FCSPI API Service IDs
 * @brief Service for det error report
 *
 * @{
 */
#define FCSPI_MASTER_INIT_ID   			             0U
#define FCSPI_MASTER_SET_SCKPCS_HOLD_TIME_ID         1U
#define FCSPI_MASTER_SET_SCKPCS_HOLD_SCK_PERCENT_ID  2U
#define FCSPI_MASTER_SELECT_PCS_ID                   3U
#define FCSPI_SLAVE_INIT_ID                          4U
#define FCSPI_ASYNC_TRANSFER_ID                      5U
#define FCSPI_SYNC_TRANSFER_ID                       6U
#define FCSPI_GET_LATEST_TRANSFER_STATUS_ID          7U
#define FCSPI_ABORT_TRANSFER_ID                      8U
#define FCSPI_DEINIT_ID   			                 9U
/** @}*/

/**
 * @name  FCSPI Dev Error Code
 * @brief Error Code of calling FCSPI apis
 *
 * @{
 */
#define FCSPI_E_PARAM_NULL_CONFIGURATION  		    0x01U
/** @}*/

#define FCSPI_DRV_STATUS_REG_W1C_U32  ((uint32_t)(  FCSPI_STATUS_DMF(1)    | \
                                                    FCSPI_STATUS_RX_FO(1)  | \
                                                    FCSPI_STATUS_TX_FU(1)  | \
                                                    FCSPI_STATUS_TCF(1)    | \
                                                    FCSPI_STATUS_FEF(1)    | \
                                                    FCSPI_STATUS_RX_WF(1)))

#define FCSPI_DRV_STATUS_REG_W1C_MASK_U32 ((uint32_t)(FCSPI_STATUS_DMF_MASK   | \
                                                      FCSPI_STATUS_RX_FO_MASK | \
                                                      FCSPI_STATUS_TX_FU_MASK | \
                                                      FCSPI_STATUS_TCF_MASK   | \
                                                      FCSPI_STATUS_FEF_MASK   | \
                                                      FCSPI_STATUS_RX_WF_MASK))

#define FCSPI_DRV_INT_EN_REG_ALL_U32   ((uint32_t)(FCSPI_INT_EN_DMIE(1)     | \
                                                   FCSPI_INT_EN_RFOIE(1)   | \
                                                   FCSPI_INT_EN_TFUIE(1)   | \
                                                   FCSPI_INT_EN_TCIE(1)    | \
                                                   FCSPI_INT_EN_FEIE(1)    | \
                                                   FCSPI_INT_EN_RWIE(1)    | \
                                                   FCSPI_INT_EN_RX_PEIE(1) | \
                                                   FCSPI_INT_EN_TX_PEIE(1) | \
                                                   FCSPI_INT_EN_RFIE(1)    | \
                                                   FCSPI_INT_EN_TFIE(1)))

#define FCSPI_DRV_RX_FIFO_WORD_CNT (8)
#define FCSPI_DRV_TX_FIFO_WORD_CNT (8)

#define FCSPI_CFGR1_PCS23_PCS_MODE_U32                  FCSPI_CFG1_PCS_CFG(0) /* PCS[3:2] as PCS feature */
#define FCSPI_CFGR1_PCS23_DATABUS_IN_4BIT_MODE_U32      FCSPI_CFG1_PCS_CFG(1) /* PCS[3:2] as data bus in 4-bit mode */

#define FCSPI_CFGR1_OUTCFG_RETAIN_LAST_WHEN_NEGATE_U32  FCSPI_CFG1_OUT_CFG(0)
#define FCSPI_CFGR1_OUTCFG_TRISTATE_WHEN_NEGATE_U32     FCSPI_CFG1_OUT_CFG(1)

#define FCSPI_CFGR1_PINCFG_SIN_INPUT_SOUT_OUTPUT_U32    FCSPI_CFG1_PIN_CFG(0) /* SIN is used for input data and SOUT for output data */
#define FCSPI_CFGR1_PINCFG_SIN_INPUT_OUTPUT_U32         FCSPI_CFG1_PIN_CFG(1) /* SIN is used for both input and output data */
#define FCSPI_CFGR1_PINCFG_SOUT_INPUT_OUTPUT_U32        FCSPI_CFG1_PIN_CFG(2) /* SOUT is used for both input and output data */
#define FCSPI_CFGR1_PINCFG_SOUT_INPUT_SIN_OUTPUT_U32    FCSPI_CFG1_PIN_CFG(3) /* SOUT is used for input data and SIN for output data */

#define FCSPI_CFGR1_PCS0_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(1) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS0_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(1)
#define FCSPI_CFGR1_PCS1_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(2) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS1_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(2)
#define FCSPI_CFGR1_PCS2_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(4) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS2_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(4)
#define FCSPI_CFGR1_PCS3_ACTIVE_HIGH_U32                FCSPI_CFG1_PCS_POL(8) /* Peripheral Chip Select Polarity - Active High */
#define FCSPI_CFGR1_PCS3_POL_MASK_U32                   FCSPI_CFG1_PCS_POL(8)

#define FCSPI_TRCR_SCKPOL_ACTIVE_HIGH_U32               FCSPI_TR_CTRL_SCK_POL(0) /* When inactive, SCK is low */
#define FCSPI_TRCR_SCKPOL_ACTIVE_LOW_U32                FCSPI_TR_CTRL_SCK_POL(1) /* When inactive, SCK is high */

#define FCSPI_TRCR_SCKPHA_CAP_LEADING_U32               FCSPI_TR_CTRL_SCK_PHA(0) /* Data is changed on the leading edge of SCK and captured on the following edge */
#define FCSPI_TRCR_SCKPHA_CAP_TRAILING_U32              FCSPI_TR_CTRL_SCK_PHA(1) /* Data is captured on the leading edge of SCK and changed on the following edge */

#define FCSPI_TRCR_PRESCALE_1_U32                       FCSPI_TR_CTRL_PRESCALE(0) /* Divide by 1 */
#define FCSPI_TRCR_PRESCALE_2_U32                       FCSPI_TR_CTRL_PRESCALE(1) /* Divide by 2 */
#define FCSPI_TRCR_PRESCALE_4_U32                       FCSPI_TR_CTRL_PRESCALE(2) /* Divide by 4 */
#define FCSPI_TRCR_PRESCALE_8_U32                       FCSPI_TR_CTRL_PRESCALE(3) /* Divide by 8 */
#define FCSPI_TRCR_PRESCALE_16_U32                      FCSPI_TR_CTRL_PRESCALE(4) /* Divide by 16 */
#define FCSPI_TRCR_PRESCALE_32_U32                      FCSPI_TR_CTRL_PRESCALE(5) /* Divide by 32 */
#define FCSPI_TRCR_PRESCALE_64_U32                      FCSPI_TR_CTRL_PRESCALE(6) /* Divide by 64 */
#define FCSPI_TRCR_PRESCALE_128_U32                     FCSPI_TR_CTRL_PRESCALE(7) /* Divide by 128 */

#define FCSPI_TRCR_PCS0_EN_U32                          FCSPI_TR_CTRL_PCS(0) /* Transfer using FCSPI_PCS[0] */
#define FCSPI_TRCR_PCS1_EN_U32                          FCSPI_TR_CTRL_PCS(1) /* Transfer using FCSPI_PCS[1] */
#define FCSPI_TRCR_PCS2_EN_U32                          FCSPI_TR_CTRL_PCS(2) /* Transfer using FCSPI_PCS[2] */
#define FCSPI_TRCR_PCS3_EN_U32                          FCSPI_TR_CTRL_PCS(3) /* Transfer using FCSPI_PCS[3] */

#define FCSPI_TRCR_MSB_U32                              FCSPI_TR_CTRL_LSBF(0) /* Data is transferred MSB first */
#define FCSPI_TRCR_LSB_U32                              FCSPI_TR_CTRL_LSBF(1) /* Data is transferred LSB first */

#define FCSPI_TRCR_BYSW_EN_U32                          FCSPI_TR_CTRL_BYSW(1) /* Byte swap enabled */
#define FCSPI_TRCR_BYSW_DIS_U32                         FCSPI_TR_CTRL_BYSW(0) /* Byte swap disable */

#define FCSPI_TRCR_CONT_EN_U32                          FCSPI_TR_CTRL_CT_EN(1) /* Continuous transfer enabled */
#define FCSPI_TRCR_CONT_DIS_U32                         FCSPI_TR_CTRL_CT_EN(0) /* Continuous transfer disabled */

#define FCSPI_TRCR_CONTC_EN_U32                         FCSPI_TR_CTRL_CT_GO(1) /* Command word for continuing transfer */

#define FCSPI_TRCR_WIDTH_1_U32                          FCSPI_TR_CTRL_WIDTH(0) /* Single bit transfer */
#define FCSPI_TRCR_WIDTH_2_U32                          FCSPI_TR_CTRL_WIDTH(1) /* Two bita transfer */
#define FCSPI_TRCR_WIDTH_4_U32                          FCSPI_TR_CTRL_WIDTH(2) /* Four bits transfer */

/* get status value and check using macro */
#define   FCSpi_Hw_ChkBusy(status)                   (((status) & FCSPI_STATUS_BF_MASK) != 0U)
#define   FCSpi_Hw_ChkDataMatch(status)              (((status) & FCSPI_STATUS_DMF_MASK) != 0U)
#define   FCSpi_Hw_ChkRxFifoOverflow(status)         (((status) & FCSPI_STATUS_RX_FO_MASK) != 0U)
#define   FCSpi_Hw_ChkTxFifoUnderrun(status)         (((status) & FCSPI_STATUS_TX_FU_MASK) != 0U)
#define   FCSpi_Hw_ChkTransferComplete(status)       (((status) & FCSPI_STATUS_TCF_MASK) != 0U)
#define   FCSpi_Hw_ChkFrameEndDetected(status)       (((status) & FCSPI_STATUS_FEF_MASK) != 0U)
#define   FCSpi_Hw_ChkReceiveWordComplete(status)    (((status) & FCSPI_STATUS_RX_WF_MASK) != 0U)
#define   FCSpi_Hw_ChkRxGreaterThanWater(status)     (((status) & FCSPI_STATUS_RX_FF_MASK) != 0U)
#define   FCSpi_Hw_ChkTxEqualOrLessThanWater(status) (((status) & FCSPI_STATUS_TX_FF_MASK) != 0U)
#define   FCSpi_Hw_EnableTransmitDataInterrupt(eInst)      FCSpi_Hw_EnableMoreInterrupts((eInst),  FCSPI_INT_EN_TFIE_MASK)
#define   FCSpi_Hw_DisableTransmitDataInterrupt(eInst)     FCSpi_Hw_DisableSomeInterrupts((eInst), FCSPI_INT_EN_TFIE_MASK)
#define   FCSpi_Hw_EnableReceiveDataInterrupt(eInst)       FCSpi_Hw_EnableMoreInterrupts((eInst),  FCSPI_INT_EN_RFIE_MASK)
#define   FCSpi_Hw_DisableReceiveDataInterrupt(eInst)      FCSpi_Hw_DisableSomeInterrupts((eInst), FCSPI_INT_EN_RFIE_MASK)
#define   FCSpi_Hw_EnableTransmitCompleteInterrupt(eInst)  FCSpi_Hw_EnableMoreInterrupts((eInst),  FCSPI_INT_EN_TCIE_MASK)
#define   FCSpi_Hw_DisableTransmitCompleteInterrupt(eInst) FCSpi_Hw_DisableSomeInterrupts((eInst), FCSPI_INT_EN_TCIE_MASK)

#define   FCSpi_Hw_PrescalerRegToActualVal(eVal)  (((uint32_t)1) << ((uint8_t)(eVal)))

/**
 * @name FCSPI_StatusType
 * @brief Status returned by FCSpi APIs
 *
 * @{
 */
typedef enum
{
    FCSPI_STATUS_SUCCESS = 0,    /**< API execute successfully */
    FCSPI_STATUS_INSTANCE_ERROR, /**< FCSpi instance index parameter error */
    FCSPI_STATUS_PARAM_ERR,      /**< parameter error */
    FCSPI_STATUS_ERROR,          /**< some error occur in API */
    FCSPI_STATUS_NO_DATA,        /**< user want to transfer nothing */
    FCSPI_STATUS_BUSY,           /**< FCSpi hardware is busy, not available */
    FCSPI_STATUS_SYNC_TIMEOUT,   /**< FCSpi synchronous transfer timeout */
    FCSPI_STATUS_TRANSFER_FAIL,  /**< FCSpi transfer fail */

    FCSPI_STATUS_TRIGGER_OK,            /**< FCSpi user trigger successfully */
    FCSPI_STATUS_TRIGGER_ABORT_TX_FAIL, /**< FCSpi user trigger fail due to send underrun */
    FCSPI_STATUS_TRIGGER_ABORT_RX_FAIL, /**< FCSpi user trigger fail due to receive overflow */
    FCSPI_STATUS_TRIGGER_FINISH         /**< FCSpi user trigger finish, all data already send */
} FCSPI_StatusType;
/** @}*/

/**
 * @name FCSPI_InstanceType
 * @brief FCSpi hardware instances
 *
 * FCSpi consist of multiple hardware instances, for example, FCSPI0, FCSPI1...
 * Just as the enumeration type "FCSPI_InstanceType" definition shows.
 * We use variables of this type to indicate which hardware instance to use.
 * @{
 */
typedef enum
{
    FCSPI_0   = 0, /**< Select FCSPI0 */
    FCSPI_1   = 1, /**< Select FCSPI1 */
    FCSPI_2   = 2, /**< Select FCSPI2 */
    FCSPI_3   = 3  /**< Select FCSPI3 */
} FCSPI_InstanceType;
/** @}*/

/**
 * @name FCSPI_PCSType
 * @brief PCS(Peripheral Chip Select) pin select
 *
 * FCSPI has four PCS lines, in our driver code,
 * we use FCSPI_PCS_0/FCSPI_PCS_1/FCSPI_PCS_2/FCSPI_PCS_3 to present them.
 * Like the above, we use enumeration type "FCSPI_PCSType" to indicate
 * which PCS to connect to the external device,
 * "PCS" is short for Peripheral Chip Select,
 * which usually use low level voltage to select the external chip to communicate.
 * @{
 */
typedef enum
{
    FCSPI_PCS_0 = 0U, /**< Transfer using pcs_0 */
    FCSPI_PCS_1 = 1U, /**< Transfer using pcs_1 */
    FCSPI_PCS_2 = 2U, /**< Transfer using pcs_2 */
    FCSPI_PCS_3 = 3U  /**< Transfer using pcs_3 */
} FCSPI_PCSType;
/** @}*/

/**
 * @name FCSPI_PcsPolarityType
 * @brief Valid PCS pin voltage polarity
 *
 * The external device determines the voltage polarity (low or high) of PCS to enable it.
 * So, FCSpi use enumeration type "FCSPI_PcsPolarityType" to indicate
 * the polarity the PCS output when select the external device
 * @{
 */
typedef enum
{
    FCSPI_PCS_POL_ACTIVE_HIGH = 1, /**< pcs use high level to select external device */
    FCSPI_PCS_POL_ACTIVE_LOW  = 0  /**< pcs use low level to select external device */
} FCSPI_PcsPolarityType;
/** @}*/

/**
 * @name FCSPI_SckPolarityType
 * @brief SCK(serial clock) active phase
 *
 * Just as the SPI bus specification says, clock polarity (CPOL) and clock phase (CPHA) determine the sample point.
 * FCSpi use enumeration type "FCSPI_SckPolarityType" to present CPOL configuration.
 * @{
 */
typedef enum
{
    FCSPI_SCK_ACTIVE_HIGH = 0, /**< sck is high level when active (idles low). */
    FCSPI_SCK_ACTIVE_LOW  = 1  /**< sck is low level when active (idles high). */
} FCSPI_SckPolarityType;
/** @}*/

/**
 * @name FCSPI_SckSamplePhaseType
 * @brief SCK(serial clock) sample edge
 *
 * Just as the SPI bus specification says,
 * clock polarity (CPOL) and clock phase (CPHA) determine the sample point.
 * FCSpi use enumeration type "FCSPI_SckSamplePhaseType" to present CPHA configuration.
 * @{
 */
typedef enum
{
    FCSPI_SCK_SAMPLE_FIRST_EDGE  = 0, /**< sample on first edge of sck active polarity, change on second */
    FCSPI_SCK_SAMPLE_SECOND_EDGE = 1  /**< changed on first edge of sck active polarity, sample on second */
} FCSPI_SckSamplePhaseType;
/** @}*/

/**
 * @name FCSPI_BitFirstOrderType
 * @brief The order of rx/tx handles bit
 *
 * When send or receive data, the MOSI and MISO handle only one bit at a time,
 * FCSpi map the bit data order according to the specific configuration.
 * FCSpi driver provides the enumeration type "FCSPI_BitFirstOrderType" to indicate the order.
 * @{
 */
typedef enum
{
    FCSPI_MSB_FIRST = 0, /**< most significant bit first handle, from msb to lsb */
    FCSPI_LSB_FIRST = 1  /**< least significant bit first handle, from lsb to msb */
} FCSPI_BitFirstOrderType;
/** @}*/

/**
 * @name FCSPI_BaudrateCalculatePriorityType
 * @brief The priority when calculating baudrate
 * @{
 */
typedef enum {
    FCSPI_BAUDRATE_CALCULATE_MINIUM_ERROR_FIRST = 0, /**< Calculate the nearest baudrate*/
    FCSPI_BAUDRATE_CALCULATE_DUTY_CYCLE_FIRST = 1  /**< Calculate the nearest baudrate clock when duty cycle is 50%(SCKDIV must be even)*/
} FCSPI_BaudrateCalculatePriorityType;
/** @}*/

/**
 * @name FCSPI_PCS2_3ModeType
 * @brief The PCS2 3 mode select
 *
 * When use qspi mode, must select PCS2_3_DATA_BUS_IN_4BIT_MODE.
 * @{
 */
typedef enum
{
    PCS2_3_PCS                   = 0, /**< PCS[3:2] are configured as PCS feature */
    PCS2_3_DATA_BUS_IN_4BIT_MODE = 1  /**< PCS[3:2] are configured as data bus in 4-bit mode */
} FCSPI_PCS2_3ModeType;
/** @}*/

/**
 * @name FCSPI_TransferWidthType
 * @brief TransferWidth ,can be 1/2/4 bits
 * @{
 */
typedef enum
{
    FCSPI_TRANSFER_1_BIT = 0, /**< 1-bit shift at a time, data out on SDO, in on SDI (normal mode) */
    FCSPI_TRANSFER_2_BIT = 1, /**< 2-bits shift out on SDO/SDI and in on SDO/SDI */
    FCSPI_TRANSFER_4_BIT = 2  /**< 4-bits shift out on SDO/SDI/PCS[3:2] and in on SDO/SDI/PCS[3:2] */
} FCSPI_TransferWidthType;
/** @}*/

/**
 * @name FCSPI_NegatedPinOutStatType
 * @brief Output data level when PCS is negated
 * @{
 */
typedef enum
{
    PINOUT_RETAIN_LAST = 0, /**< Output data retains last value when PCS is negated */
    PINOUT_TRISTATE    = 1  /**< Output data is tristated when PCS is negated. This bit must be set if perform a half duplex transfer. */
} FCSPI_NegatedPinOutStatType;
/** @}*/

/**
 * @name FCSPI_PinModeType
 * @brief SIN/SOUT Pin mode select
 * @{
 */
typedef enum
{
    SIN_INPUT_SOUT_OUTPUT = 0, /**< SIN is configured as input pin and SOUT is configured as output pin */ 
    SIN_INPUT_OUTPUT      = 1, /**< SIN is configured as input and output pin */ 
    SOUT_INPUT_OUTPUT     = 2, /**< SOUT is configured as input and output pin */ 
    SOUT_INPUT_SIN_OUTPUT = 3  /**< SOUT is configured as input pin and SIN is configured as output pin */ 
} FCSPI_PinModeType;
/** @}*/

/**
 * @name FCSPI_PrescaleValueType
 * @brief Prescale
 * @{
 */
typedef enum
{
    FCSPI_PRESCALE_1   = 0, /**< Divide by 1 */ 
    FCSPI_PRESCALE_2   = 1, /**< Divide by 2 */ 
    FCSPI_PRESCALE_4   = 2, /**< Divide by 4 */ 
    FCSPI_PRESCALE_8   = 3, /**< Divide by 8 */ 
    FCSPI_PRESCALE_16  = 4, /**< Divide by 16 */ 
    FCSPI_PRESCALE_32  = 5, /**< Divide by 32 */ 
    FCSPI_PRESCALE_64  = 6, /**< Divide by 64 */ 
    FCSPI_PRESCALE_128 = 7, /**< Divide by 128 */ 
    FCSPI_PRESCALE_MAX = 8  
} FCSPI_PrescaleValueType;
/**@}*/

/**
 * @name FCSPI_TxRxCtrlType
 * @brief Configurations for TR_CTRL
 * @{
 */
typedef struct
{
    FCSPI_SckPolarityType    eSckPolarity;
    FCSPI_SckSamplePhaseType eSckPhase;
    FCSPI_PrescaleValueType  ePrescalerValue;
    FCSPI_PCSType            ePCSSelect;
    FCSPI_BitFirstOrderType  eBitFirstOrder;
    FCSPI_AtomicBoolType     eByteSwap;
    FCSPI_AtomicBoolType     eContTransEnable;
    FCSPI_AtomicBoolType     eContCmdEnable;
    FCSPI_AtomicBoolType     eRxDisable;
    FCSPI_AtomicBoolType     eTxDisable;
    FCSPI_TransferWidthType  eTransferWidth;
    uint8_t                  u8Reserved0;
    uint16_t                 u16FrameBitCnt;
} FCSPI_TxRxCtrlType;
/**@}*/

/**
 * @name FCSPI_TriggerSrcType
 * @brief Transfer method between memory and FCSpi's registers
 *
 * FCSpi support transferring data by ISR, DMA, or user poll.
 *
 * If use ISR method, in interrupt handler function,
 * the driver will write data to register "FCSPI_TX_DATA" to push it into Tx FIFO
 * and read the register "FCSPI_RX_DATA" to pop data from Rx FIFO.
 * When finish, the hardware will create an interrupt to notify the end.
 *
 * If use DMA, the DMA channel and priority should also be configured.
 * After configuring these, driver user doesn't need to take care of the detail of transferring.
 * Just send data or send & receive at same time. When finish, the hardware will create an interrupt to notify the end.
 *
 * If use User Poll mode, driver user should call
 * "FCSPI_SyncTransfer" API to move the data until it return error or finished.
 * In this mode, the interrupt in driver is disabled.
 * @{
 */
typedef enum
{
    FCSPI_TRANSFER_TRIGGER_SRC_ISR = 0,  /**< software(interrupt function) move data between register and memory, when finish, notified by interrupt */
    FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR,  /**< hardware(DMA) move data between register and memory, when finish, notified by interrupt */
    FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL /**< NOT use ISR and DMA!!! driver user use API to move data between register and memory, notified by return value when finish */
} FCSPI_TriggerSrcType;
/**@}*/

/**
 * @name FCSPI_SemaphoreStatType
 * @brief Type return by semaphore callback function
 *
 * If want to use synchronous tranfer API, driver user need to provide semaphore callback,
 * these callback function should return value of this enumeration defined.
 * @{
 */
typedef enum
{
    FCSPI_SEMAPHORE_SUCCESS = 0,  /**< semaphore function execute successfully */
    FCSPI_SEMAPHORE_FAIL    = 1,  /**< semaphore function execute fail */
    FCSPI_SEMAPHORE_TIMEOUT = 2   /**< wait to get semaphore until reaching deadline */
} FCSPI_SemaphoreStatType;
/**@}*/

/**
 * @name FCSPI_AsyncDataInfType
 * @brief Asynchronous Transfer data buffer information
 *
 * @note  @verbatim
if init frame bit count need N bytes to store, for example, 7bits need N=1 byte, 9bits need N=2bytes, 23bits need N=3bytes.
N = 1,  one frame data stored in pSendBuffer using uint8_t, driver read data using step 1byte.
N = 2,  one frame data stored in pSendBuffer using uint16_t, driver read data using step 2byte.
N = 3,  one frame data stored in pSendBuffer using uint32_t, driver read data using step 4byte.The highest byte is dropped.
N > 3,  byte count of frame data stored in the parameter pointer pSendBuffer aligned with 4bytes,
        for example, one frame uses 5bytes, it will need two uint32_t, the highest 3bytes are dropped,
        driver API user need declare as "uint32_t data[N]"; it use index 0 to 1, the next frame is 2 to 3.
 @endverbatim
 * @{
 */
typedef struct
{
    uint16_t       u16FrameCount;  /**< The frame count to be sent, the data stored in pSendBuffer is divided into many frames. */
    uint16_t       u16Reserved0;
    const uint8_t *pSendBuffer;    /**< The buffer containing data to be send, must keep valid before sending is terminated or finished, can be NULL */
    uint8_t       *pReceiveBuffer; /**< Optional, can be NULL. Buffer to store the data received.The data received is 1byte aligned, no dummy data insert. */
} FCSPI_AsyncDataInfType;
/**@}*/

/**
 * @name FCSPI_SyncDataInfType
 * @brief Synchronous Transfer data buffer information
 *
 * @note  @verbatim
if init frame bit count need N bytes to store, for example, 7bits need N=1 byte, 9bits need N=2bytes, 23bits need N=3bytes.
N = 1,  one frame data stored in pSendBuffer using uint8_t, driver read data using step 1byte.
N = 2,  one frame data stored in pSendBuffer using uint16_t, driver read data using step 2byte.
N = 3,  one frame data stored in pSendBuffer using uint32_t, driver read data using step 4byte.The highest byte is dropped.
N > 3,  byte count of frame data stored in the parameter pointer pSendBuffer aligned with 4bytes,
        for example, one frame uses 5bytes, it will need two uint32_t, the highest 3bytes are dropped,
        driver API user need declare as "uint32_t data[N]"; it use index 0 to 1, the next frame is 2 to 3.
 @endverbatim
 * @{
 */
typedef struct
{
    uint16_t       u16FrameCount;   /**< The frame count to be sent, the data stored in pSendBuffer is divided into many frames. */
    uint16_t       u16Reserved0;
    const uint8_t *pSendBuffer;     /**< The buffer containing data to be send, must keep valid before sending is terminated or finished, can be NULL */
    uint8_t       *pReceiveBuffer;  /**< Optional, can be NULL. Buffer to store the data received.The data received is 1byte aligned, no dummy data insert. */
    uint32_t       u32Timeout;      /**< The timeout value, it will only be passed to the semaphore callback API configured by driver user */
} FCSPI_SyncDataInfType;
/**@}*/

/**
 * @name FCSPI_TransferRemainInfType
 * @brief tx/rx remain information
 * @{
 */
typedef struct
{
    uint32_t u32ByteCountSendRemained; /**< byte count remains to be sent */
    uint32_t u32ByteCountReceiveRemained;  /**< byte count remains to be get */
} FCSPI_TransferRemainInfType;
/**@}*/

/**
 * @name FCSPI_TriggerDmaInfType
 * @brief configuration when use DMA
 *
 * @{
 */
typedef struct
{
    uint8_t u8RxDMAChannelPriority; /**< DMA channel priority for Rx, should differ from others in project scope */
    uint8_t u8TxDMAChannelPriority; /**< DMA channel priority for Tx, should differ from others in project scope */
    uint8_t u8RESERVED0[2];
    DMA_HandleType               *pDmaTxInstanceHandle;    /**< DMA channel number for Tx, if DMA not used, this ignored */
    DMA_HandleType               *pDmaRxInstanceHandle;    /**< DMA channel number for Rx, if DMA not used, this ignored */
} FCSPI_TriggerDmaInfType;
/**@}*/

/**
 * @name FCSPI_TransferStatusType
 * @brief driver status
 *
 * @{
 */
typedef enum
{
    FCSPI_TRANSFER_OK = 0U,    /**< Transfer OK */
    FCSPI_TRANSFER_TX_FAIL,    /**< Error during transmission */
    FCSPI_TRANSFER_RX_FAIL,    /**< Error during reception */
    FCSPI_TRANSFER_ABORT,      /**< Transfer is aborted */
} FCSPI_TransferStatusType;
/**@}*/

/**
 *
 * @brief The structure of the FCSPI processing handle
 */
typedef struct _FCSPI_HandleType
{
	FCSPI_InstanceType eInstance;  /**< FCSPI instance*/

//	uint8_t u8Reserved0[543];
	struct
	{
		uint8_t                         u8TxFifoSize;             /**< Tx fifo size */
		uint8_t                         u8RxFifoSize;             /**< Rx fifo size */
		volatile uint8_t                u8WaitSemaphore;
		FCSPI_BitFirstOrderType         eBitFirstOrder;       /**< MSB/LSB first to send/receive */
		FCSPI_TriggerSrcType            eTransferTriggerSrc;  /**< Type of transfer */
		FCSPI_SckSamplePhaseType        eSckSamplePhase;      /**< select which edge of active sck clock to capture data */
		FCSPI_SckPolarityType           eSckPolarity;         /**< select output sclk clock polarity */
		FCSPI_PCSType                   ePcs;                 /**< chip select pin */
		FCSPI_PcsPolarityType           ePcsPolarity;         /**< chip select pin polarity */
		FCSPI_AtomicBoolType            eIsPcsContinuous;     /**< Option to keep chip select asserted until transfer complete; needed for TCR programming */
		volatile FCSPI_TransferStatusType  eTransferStat;     /**< The status of the current */
		volatile FCSPI_AtomicBoolType      eIsInTransfer;     /**< True if there is an active transfer */
		uint16_t                        u16BitsPerFrame;          /**< count of bits per frame: 8-4096bits */
		uint16_t                        u16BytesCntFrameNeed;     /**< count of bytes per frame: 1-512bytes for external buffer passed into driver */
		volatile uint16_t               u16TxIndex;
		volatile uint16_t               u16RxIndex;
		volatile uint16_t               u16TxByteCntRemainToSend;    /**< Number of bytes remaining to send  */
		volatile uint16_t               u16RxByteCntRemainToGet;     /**< Number of bytes remaining to receive */
		volatile uint16_t               u16TxSendByteCntOfCurFrame;  /**< Number of bytes from current frame which were already sent */
		volatile uint16_t               u16RxGetByteCntOfCurFrame;   /**< Number of bytes from current frame which were already received */
		uint32_t                        u32DmaDummyData;      /**< DMA mode, TX is NULL, just send this data, RX is NULL, just store in this var */
		uint32_t                        u32FCSpiSrcClk;       /**< Module source clock */
		uint32_t                        u32Baundrate;         /**< the bit per second of current transmission */
	    /**< if to be notified when transmittion successfully or aborted, need set these following fields */
		void                   (*pStopNotifyCb)(struct _FCSPI_HandleType * pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr); /**< callback to transfer stop, transfer successfully or aborted */
	    /**< if want to use semaphore to synchronous transfer, the following need to be set */
		FCSPI_SemaphoreStatType(*pSemaResetCb)(struct _FCSPI_HandleType * pFcspiHandle); /**< synchronous send need, reset the semaphore */
		FCSPI_SemaphoreStatType(*pSemaTakeCb)(struct _FCSPI_HandleType * pFcspiHandle, uint32_t u32Timeout); /**< synchronous send need, acquire the semaphore */
		FCSPI_SemaphoreStatType(*pSemaPostCb)(struct _FCSPI_HandleType * pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);/**< synchronous send need, release the semaphore outside of the interrupt */
		const uint8_t*                  pbyTxBuff;            /**< The buffer from which transmitted bytes are taken */
		uint8_t*                        pbyRxBuff;            /**< The buffer into which received bytes are placed */
		FCSPI_TriggerDmaInfType         tTriggerDmaInf;
#if (!SPI_SUPPORT_CONTINUOUS_MODE_WHEN_SAMPLING_ON_SECOND_EDGE)
		FCSPI_AtomicBoolType               eIsWorkAroundNeeded;         /**<Automaticly set to true if  CPHA = 1 and CONT = 1 for 512K, 2M and 1M-A,the maximum bytes to be transferred during one pcs selection is 512bytes*/
		uint16_t                           u16BytesCntWorkAroundFrameNeed;     /**< count of bytes per frame: 1-512bytes for external buffer passed into driver */
#endif
		volatile uint32_t                  u32CurrentTrCtrl;
	}tStatus;
} FCSPI_HandleType;

/**
 * @name FCSPI_Semaphore typedefs
 * @brief Callback function to reset semaphore
 *
 * After calling this function, the semaphore variable has a zero semaphore count.
 * Then if try to take the semaphore, the take API will blocks.
 *
 * If the RTOS is FreeRTOS, the reference code as following.
 *
 * @code
 * FCSPI_SemaphoreStatType SpiSemaphoreReset(FCSPI_InstanceType eInst)
 * {
 *     while ( xSemaphoreTake( xSemaphore, ( TickType_t ) 0 ) == pdTRUE );
 *     return FCSPI_SEMAPHORE_SUCCESS;
 * }
 * @endcode
 * @{
 */
typedef FCSPI_SemaphoreStatType(*FCSPI_SemaphoreResetCbType)(FCSPI_InstanceType eInst);

/**
 * @brief Callback function to obtain semaphore
 *
 * This function will only try to obtain the semaphore before the time expires.
 *
 * If the RTOS is FreeRTOS, the reference code as following.
 *
 * @code
 * FCSPI_SemaphoreStatType SpiSemaphoreTake(FCSPI_InstanceType eInst, uint32_t u32Timeout)
 * {
 *     if ( xSemaphoreTake( xSemaphore, ( TickType_t ) u32Timeout ) == pdTRUE )
 *         return FCSPI_SEMAPHORE_SUCCESS;
 *     else
 *         return FCSPI_SEMAPHORE_TIMEOUT;
 * }
 * @endcode
 */
typedef FCSPI_SemaphoreStatType(*FCSPI_SemaphoreTakeCbType)(FCSPI_InstanceType eInst, uint32_t u32Timeout);


/**
 * @brief Callback function to release semaphore
 *
 * This function will only release semaphore.
 *
 * If the RTOS is FreeRTOS, the reference code as following.
 *
 * @code
 * static FCSPI_SemaphoreStatType SpiSemaphorePost(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr)
 * {
 *     FCSPI_SemaphoreStatType eRet = FCSPI_SEMAPHORE_SUCCESS;
 *
 *     (void)eInst;
 *     if (FCSPI_TRUE == bIsInIsr)
 *     {
 *         BaseType_t tBase = pdFALSE;
 *
 *         if ( xSemaphoreGiveFromISR( xSemaphore, &tBase ) == pdPASS )
 *         {
 *             portYIELD_FROM_ISR(tBase);
 *             eRet = FCSPI_SEMAPHORE_SUCCESS;
 *         }
 *         else
 *         {
 *             eRet = FCSPI_SEMAPHORE_FAIL;
 *         }
 *     }
 *     else
 *     {
 *         if ( xSemaphoreGive( xSemaphore ) == pdPASS )
 *             eRet = FCSPI_SEMAPHORE_SUCCESS;
 *         else
 *             eRet = FCSPI_SEMAPHORE_FAIL;
 *     }
 *
 *     return eRet;
 * }
 * @endcode
 */
typedef FCSPI_SemaphoreStatType(*FCSPI_SemaphorePostCbType)(FCSPI_InstanceType eInst, FCSPI_AtomicBoolType bIsInIsr);
/**@}*/

/**
 * @name FCSPI_MasterCfgType
 * @brief FCSpi Master mode configuration
 *
 * When One FCSpi instance used as master side, API "FCSPI_Master_Init" need this parameter to configure the driver.
 * @{
 */
typedef struct
{
    uint16_t                      u16BitCountPerFrame;   /**< bit count of one frame, should >= 8, we call the data after pcs select, before pcs become invalid, as a frame, */
    uint16_t                      u16Reserved0;
    uint32_t                      u32FCSpiSrcClk;        /**< fcspi hardware module source clock */
    uint32_t                      u32Sckdiv;             /**< should less than 0x100,otherwise will calculate baudrate automatically by the method selected by eBaudCalcPriority*/
    uint32_t                      u32BitCntPerSecond;    /**< baud rate in bits per second, actual baudrate is calculated in driver, it's the nearest value to this parameter */
    /* peripheral chip select configuration */
    FCSPI_PCSType                 ePcs;                  /**< chip select pin */
    FCSPI_PcsPolarityType         ePcsPolarity;          /**< chip select pin polarity */
    FCSPI_AtomicBoolType          eIsPcsContinuous;      /**< keep PCS select enable until transfer finish */

    /* about sample point, sample bit order */
    FCSPI_SckSamplePhaseType      eSckSamplePhase;       /**< select which edge of active sck clock to capture data */
    FCSPI_SckPolarityType         eSckPolarity;          /**< select output sclk clock polarity */
    FCSPI_BitFirstOrderType       eBitFirstOrder;        /**< transmit LSB/MSB first */
    FCSPI_TriggerSrcType          eTransferTriggerSrc;    /**< type of transfer data between memory and data register of FCSPI */

    FCSPI_PCS2_3ModeType          ePCS23Mode;           /**< PCS2 and PCS3 mode select */
    FCSPI_TransferWidthType       eTransferWidthType;   /**< spi transfer width select */
    FCSPI_NegatedPinOutStatType   ePinOutStatType;      /**< spi pin out stat select */
    FCSPI_BaudrateCalculatePriorityType eBaudCalcPriority; /**< baudrate calculate priority */
    FCSPI_PrescaleValueType        ePrescalerValue;    /**< prescale value */

    /* if to be notified when transmittion successfully or aborted, need set these following fields */
	void                   (*pStopNotifyCb)(struct _FCSPI_HandleType * pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr); /* callback to transfer stop, transfer successfully or aborted */
    /* if want to use semaphore to synchronous transfer, the following need to be set */
	FCSPI_SemaphoreStatType(*pSemaResetCb)(struct _FCSPI_HandleType * pFcspiHandle); /* synchronous send need, reset the semaphore */
	FCSPI_SemaphoreStatType(*pSemaTakeCb)(struct _FCSPI_HandleType * pFcspiHandle, uint32_t u32Timeout); /* synchronous send need, acquire the semaphore */
	FCSPI_SemaphoreStatType(*pSemaPostCb)(struct _FCSPI_HandleType * pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);/* synchronous send need, release the semaphore outside of the interrupt */
    /* if eTransferTriggerSrc is "FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR", these following fields should be set, or ingore */
    FCSPI_TriggerDmaInfType       tTriggerDmaInf; /**< if trigger src is DMA, this MUST configure */
} FCSPI_MasterCfgType;
/**@}*/

/**
 * @name FCSPI_MasterSckPcsHoldTimeType
 * @brief parameters about the holding time (in us) between PCS and SCK
 *
 * Configure the duration (in us) of the clock voltage between PCS and SCK
 * @{
 */
typedef struct
{
    uint32_t u32PCStoPCSHoldUs; /**< Configures the delay cycles from the PCS negation to the next PCS assertion, in microsecond(us) */
    uint32_t u32SCKtoPCSHoldUs; /**< Configure the delay cycles from the last SCK edge to the PCS negation, in microsecond(us) */
    uint32_t u32PCStoSCKHoldUs; /**< Configure the delay cycles from the PCS assertion to the first SCK edge, in microsecond(us) */
} FCSPI_MasterSckPcsHoldTimeType;
/**@}*/

/**
 * @name FCSPI_MasterSckPcsHoldSckCycleType
 * @brief parameters about the holding time (in PCS/100) between PCS and SCK
 *
 * Configure the duration (in PCS/100) of the clock voltage between PCS and SCK
 * @{
 */
typedef struct
{
    uint32_t u32PCStoPCSHoldPercentage; /**< Configure the delay cycles from the PCS negation to the next PCS assertion, in PCS/100 */
    uint32_t u32SCKtoPCSHoldPercentage; /**< Configure the delay cycles from the last SCK edge to the PCS negation, in PCS/100 */
    uint32_t u32PCStoSCKHoldPercentage; /**< Configure the delay cycles from the PCS assertion to the first SCK edge, in PCS/100 */
} FCSPI_MasterSckPcsHoldSckCycleType;
/**@}*/

/**
 * @name FCSPI_MasterPcsConfType
 * @brief parameters about the PCS and its Polarity
 *
 * Configure the specific PCS to be used and its active polarity when FCSPI running as master side
 * @{
 */
typedef struct
{
    FCSPI_PCSType         ePcs; /**< Which PCS pin to configure */
    FCSPI_PcsPolarityType ePolarity;  /**< Pin's active polarity */
} FCSPI_MasterPcsConfType;
/**@}*/

/**
 * name FCSPI_SlaveCfgType
 * @brief FCSpi Slave mode configuration
 *
 * When One FCSpi instance used as slave side, API "FCSPI_Slave_Init" need this parameter to configure the driver.
 * @{
 */
typedef struct
{
    FCSPI_BitFirstOrderType       eBitFirstOrder;     /**< transmit LSB/MSB first */
    FCSPI_PcsPolarityType         ePcsPolarity;       /**< pcs polarity */
    FCSPI_PCSType                 ePcs;               /**< chip select pin */
    FCSPI_SckSamplePhaseType      eSckSamplePhase;          /**< select which edge of active sck clock to capture data */
    FCSPI_SckPolarityType         eSckPolarity;       /**< selects clock polarity */
    FCSPI_TriggerSrcType          eTransferTriggerSrc; /**< type of transfer data between memory and data register of FCSPI */
    FCSPI_PCS2_3ModeType          ePCS23Mode;           /**< PCS2 and PCS3 mode select */
    FCSPI_TransferWidthType       eTransferWidthType;   /**< spi transfer width select */
    FCSPI_NegatedPinOutStatType   ePinOutStatType;      /**< spi pin out stat select */

    uint8_t                       u8Reserved0;
    uint16_t                      u16BitCountPerFrame;  /**< bit count of one frame, should >= 8 */

    /* if eTransferTriggerSrc is "FCSPI_TRANSFER_TRIGGER_SRC_DMA_ISR", these following fields should be set, or ingore */
    FCSPI_TriggerDmaInfType       tTriggerDmaInf; /**< if trigger src is DMA, this MUST configure */

    /* if to be notified when transmittion successfully or aborted, need set these following fields */
	void                   (*pStopNotifyCb)(struct _FCSPI_HandleType * pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr); /* callback to transfer stop, transfer successfully or aborted */
    /* if want to use semaphore to synchronous transfer, the following need to be set */
	FCSPI_SemaphoreStatType(*pSemaResetCb)(struct _FCSPI_HandleType * pFcspiHandle); /* synchronous send need, reset the semaphore */
	FCSPI_SemaphoreStatType(*pSemaTakeCb)(struct _FCSPI_HandleType * pFcspiHandle, uint32_t u32Timeout); /* synchronous send need, acquire the semaphore */
	FCSPI_SemaphoreStatType(*pSemaPostCb)(struct _FCSPI_HandleType * pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);/* synchronous send need, release the semaphore outside of the interrupt */
} FCSPI_SlaveCfgType;
/**@}*/

/**
 * @name Fcspi APIs
 * @brief Init the FCSpi instance as spi master side
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg Configuration of the FCSpi, MUST NOT NULL
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 * @{
 */
FCSPI_StatusType FCSPI_Master_Init(FCSPI_HandleType *pFcspiHandle, const FCSPI_MasterCfgType *pCfg);

/**
 * @brief Configure the holding time (in us) between PCS and SCK
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldTime(FCSPI_HandleType *pFcspiHandle, const FCSPI_MasterSckPcsHoldTimeType *pCfg);

/**
 * @brief Configure the holding time (in SCK/100) between PCS and SCK
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg Configure the delay parameters between PCS and SCK, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SetSckPcsHoldSckPercentage(FCSPI_HandleType *pFcspiHandle, const FCSPI_MasterSckPcsHoldSckCycleType *pCfg);
/**
 * @brief Select the PCS to use and configure
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg Parameters about PCS configuration, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Master_SelectPcs(FCSPI_HandleType *pFcspiHandle, const FCSPI_MasterPcsConfType *pCfg);

/**
 * @brief Set Spi Operation Mode
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param SckPorality FCSPI_SCK_ACTIVE_HIGH or FCSPI_SCK_ACTIVE_LOW
 * @param SckPhase FCSPI_SCK_SAMPLE_FIRST_EDGE or FCSPI_SCK_SAMPLE_SECOND_EDGE
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when successfully. Others, error.
 */
FCSPI_StatusType FCSPI_SetClockPolarityClockPhase(FCSPI_HandleType *pFcspiHandle, FCSPI_SckPolarityType SckPorality, FCSPI_SckSamplePhaseType SckPhase);


/**
 * @brief Init the FCSpi instance as spi slave side
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg Configuration of the FCSpi
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when configure successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_Slave_Init(FCSPI_HandleType *pFcspiHandle, const FCSPI_SlaveCfgType *pCfg);

/**
 * @brief Send and receive asynchronously
 * 1) If the trigger source is driver user poll, this api not support this mode.
 * 2) If the trigger source is interrupt or DMA, this api will start the transmission, then return immediately.
 *    After transmission stop, it will trigger an interrupt.
 *    During the transmission, the send data buffer and receive data buffer
 *    should keep valid until the transmission stop.
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when start transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_AsyncTransfer(FCSPI_HandleType *pFcspiHandle, const FCSPI_AsyncDataInfType *pCfg);

/**
 * @brief Send and receive synchronously
 * 1) If the semaphore callbacks are configured,
 *    and the driver is configured transmitting triggered by interrupt, or by DMA,
 *    the driver will use semaphore to wait the transmission stopped.
 *    In this case, the timeout value is passed to semaphore callback directly.
 * 2) If the semaphore callbacks are not configured,
 *    this api will poll the status when triggered by interrupt or DMA,
 *    or poll to trigger the transmission when the mode is "FCSPI_TRANSFER_TRIGGER_SRC_USER_POLL".
 *    In this case, the timeout value has different meaning for different trigger mode.
 *    Read the source code for detail.
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg the data information, MUST NOT null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when transfer successfully. Others, some error occur.
 */
FCSPI_StatusType FCSPI_SyncTransfer(FCSPI_HandleType *pFcspiHandle, const FCSPI_SyncDataInfType *pCfg);

/**
 * @brief If it's in transfer, get its stat, or get the last transfer's stat.
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @param pCfg the transfer information, can be null
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when the last transfer is finish successfully. Others, busy or error occur.
 */
FCSPI_StatusType FCSPI_GetLatestTransferStat(FCSPI_HandleType *pFcspiHandle, FCSPI_TransferRemainInfType *pCfg);

/**
 * @brief Abort current transfer if exist, or just recovery the hardware.
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 */
void FCSPI_AbortTransfer(FCSPI_HandleType *pFcspiHandle);

/**
 * @brief Deinit the FCSpi
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 * @return FCSPI_StatusType FCSPI_STATUS_SUCCESS when deinit the FCSpi successfully. Others, the hardware is busy now.
 */
FCSPI_StatusType FCSPI_Deinit(FCSPI_HandleType *pFcspiHandle);

/**
 * @brief FCSpi interrupt handler
 *
 * @param pFcspiHandle FCSpi handler with status and settings information
 */
void fcspi_irq_handler(FCSPI_HandleType *pFcspiHandle);
/**@}*/

#if defined(__cplusplus)
}
#endif

/** @}*/
#endif
#endif /* _DRIVER_MODULE_DRIVER_FCSPI_H_ */
