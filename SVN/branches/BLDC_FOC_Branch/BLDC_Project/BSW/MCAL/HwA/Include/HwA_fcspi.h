/**
 * @file HwA_fcspi.h
 * @author Flagchip032
 * @brief FCSPI hardware access layer
 * @version 2.0.0
 * @date 2024-04-21
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip103   N/A          First version
*********************************************************************************/

#ifndef _HWA_FCSPI_H_
#define _HWA_FCSPI_H_

#include "device_header.h"

#if FCSPI_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_fcspi HwA_fcspi
 * @ingroup module_driver_fcspi
 * @{
 */

/**
 * @brief Boolean false value definition for type FCSPI_AtomicBoolType used by FCSPI to ensure read/write atomic
 *
 */
#define         FCSPI_FALSE ((uint8_t)0)

/**
 * @brief Boolean true value definition for type FCSPI_AtomicBoolType used by FCSPI to ensure read/write atomic
 *
 */
#define         FCSPI_TRUE  ((uint8_t)1)

/********* Local typedef ************/
/**
 * @brief FCSPI Mode type, master or slave.
 */
typedef enum {
    FCSPI_MODE_SLAVE  = 0,
    FCSPI_MODE_MASTER = 1
} FCSPI_MasterSlaveModeType;

/**
 * @brief Boolean type for FCSpi
 */
typedef uint8_t FCSPI_AtomicBoolType; 

/********* Local inline function ************/

/**
 * @brief Read the FCSPI CTRL register value for all.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI CTRL regsiter value.
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetCtrlValue(FCSPI_Type *pFCSPI)
{
    return pFCSPI->CTRL;
}

/**
 * @brief Set FCSPI CTRL value, users should write the whole value to this register.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value  the value which will be written to the CTRL register.
 */
LOCAL_INLINE void FCSPI_HWA_SetCtrlValue(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->CTRL = u32Value;
}

/**
 * @brief Enable the feature of FCSPI hardware, only for starting the feature of SPI module.
 * 
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 */
LOCAL_INLINE void FCSPI_HWA_ModuleEnable(FCSPI_Type *pFCSPI)
{
    pFCSPI->CTRL |= FCSPI_CTRL_M_EN(1);
}

/**
 * @brief Disable the feature of FCSPI, and shutdown the FCSPI module.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 */
LOCAL_INLINE void FCSPI_HWA_ModuleDisable(FCSPI_Type *pFCSPI)
{
    pFCSPI->CTRL &= (~(FCSPI_CTRL_M_EN_MASK));
}

/**
 * @brief Getting the FCSPI transfer status by reading the STATUS register.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return the whole status of FCSPI transfer, which can be read in STATUS register.
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetStatus(FCSPI_Type *pFCSPI)
{
    return pFCSPI->STATUS;
}

/**
 * @brief Clear FCSPI STATUS register for certain function.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_ClearStatus(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->STATUS = u32Value;
}

/**
 * @brief Get FCSPI INT_EN register value for checking which interrupt is enabled.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI INT_EN regsiter value will be returned.
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetIntrruptEnableReg(FCSPI_Type *pFCSPI)
{
    return pFCSPI->INT_EN;
}

/**
 * @brief Set the FCSPI INT_EN register value for enable or disable some interrupts.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetInterruptEnableReg(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->INT_EN = u32Value;
}

/**
 * @brief Getting the DMA enabled status through the regsiter FCSPI DMA_EN value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI DMA_EN regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetDMAEnableReg(FCSPI_Type *pFCSPI)
{
    return pFCSPI->DMA_EN;
}

/**
 * @brief Enable or disable the DMA feature by setting the FCSPI DMA_EN register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetDMAEnableReg(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->DMA_EN = u32Value;
}

/**
 * @brief Get FCSPI CFG0 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI CFG0 regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetCFG0Reg(FCSPI_Type *pFCSPI)
{
    return pFCSPI->CFG0;
}

/**
 * @brief Set FCSPI CFG0 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetCFG0Reg(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->CFG0 = u32Value;
}

/**
 * @brief Get FCSPI CFG1 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI CFG1 regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetCFG1Reg(FCSPI_Type *pFCSPI)
{
    return pFCSPI->CFG1;
}

/**
 * @brief Set FCSPI CFG1 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetCFG1Reg(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->CFG1 = u32Value;
}

/**
 * @brief Set the FCSPI to master mode.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 */
LOCAL_INLINE void FCSPI_HWA_SetMasterMode(FCSPI_Type *pFCSPI)
{
    pFCSPI->CFG1 |= FCSPI_CFG1_MASTER(1);
}

/**
 * @brief Set FCSPI to slave mode.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 */
LOCAL_INLINE void FCSPI_HWA_SetSlaveMode(FCSPI_Type *pFCSPI)
{
    pFCSPI->CFG1 &= (~(FCSPI_CFG1_MASTER_MASK));
}

/**
 * @brief Check the current mode status, master or slave.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return the mode type of FCSPI, FCSPI_MODE_MASTER or FCSPI_MODE_SLAVE
 */
LOCAL_INLINE FCSPI_MasterSlaveModeType FCSPI_HWA_CheckMode(FCSPI_Type *pFCSPI)
{
    FCSPI_MasterSlaveModeType eRet = FCSPI_MODE_SLAVE;

    if ((pFCSPI->CFG1 & FCSPI_CFG1_MASTER_MASK) == FCSPI_CFG1_MASTER(1))
    {
        eRet = FCSPI_MODE_MASTER;
    }

    return eRet;
}

/**
 * @brief Get FCSPI MATCH0 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI MATCH0 regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetMatch0Value(FCSPI_Type *pFCSPI)
{
    return pFCSPI->DATA_MATCH0;
}

/**
 * @brief Set FCSPI MATCH0 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetMatch0Value(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->DATA_MATCH0 = u32Value;
}

/**
 * @brief Get FCSPI MATCH1 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI MATCH1 regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetMatch1Value(FCSPI_Type *pFCSPI)
{
    return pFCSPI->DATA_MATCH1;
}

/**
 * @brief Set FCSPI MATCH1 register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetMatch1Value(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->DATA_MATCH1 = u32Value;
}

/**
 * @brief Get FCSPI CLK_CFG register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI CLK_CFG regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetClockConfig(FCSPI_Type *pFCSPI)
{
    return pFCSPI->CLK_CFG;
}

/**
 * @brief Set FCSPI CLK_CFG register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetClockConfig(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->CLK_CFG = u32Value;
}

/**
 * @brief Get FCSPI FIFO_WTM register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI FIFO_WTM regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetFIFOWaterMark(FCSPI_Type *pFCSPI)
{
    return pFCSPI->FIFO_WTM;
}

/**
 * @brief Set FCSPI FIFO_WTM register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u8RxWatermark the rx water mark value.
 * @param u8TxWatermark the tx water mark value.
 */
LOCAL_INLINE void FCSPI_HWA_SetWatermark(FCSPI_Type *pFCSPI, uint8_t u8RxWatermark, uint8_t u8TxWatermark)
{
    uint32_t u32Flag = 0U;

    u32Flag |= ((uint32_t)u8RxWatermark << FCSPI_FIFO_WTM_RXWATER_SHIFT);
    u32Flag |= ((uint32_t)u8TxWatermark << FCSPI_FIFO_WTM_TXWATER_SHIFT);

    pFCSPI->FIFO_WTM = u32Flag;
}

/**
 * @brief Get FCSPI RX FIFO count.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return the real count value of rx fifo.
 */
LOCAL_INLINE uint8_t FCSPI_HWA_GetRxFifoStoredCount(FCSPI_Type *pFCSPI)
{
    return (uint8_t)(((pFCSPI->FIFO_STATUS) & FCSPI_FIFO_STATUS_RXCNT_MASK) >> FCSPI_FIFO_STATUS_RXCNT_SHIFT);
}

/**
 * @brief Get FCSPI TX FIFO count value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return the real count of tx fifo.
 */
LOCAL_INLINE uint8_t FCSPI_HWA_GetTxFifoStoredCount(FCSPI_Type *pFCSPI)
{
    return (uint8_t)(((pFCSPI->FIFO_STATUS) & FCSPI_FIFO_STATUS_TXCNT_MASK) >> FCSPI_FIFO_STATUS_TXCNT_SHIFT);
}

/**
 * @brief Get FCSPI TR_CTRL register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI TR_CTRL regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetTxRxControl(FCSPI_Type *pFCSPI)
{
    return pFCSPI->TR_CTRL;
}

/**
 * @brief Set FCSPI TR_CTRL register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetTxRxControl(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->TR_CTRL = u32Value;
}

/**
 * @brief Set RX enable status in register FCSPI TR_CTRL.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param eEnable FCSPI_TRUE for enabled, FCSPI_FALSE for disable.
 */
LOCAL_INLINE void FCSPI_HWA_SetRxEnableStatus(FCSPI_Type *pFCSPI, FCSPI_AtomicBoolType eEnable)
{
    if (FCSPI_FALSE == eEnable)
    {
        pFCSPI->TR_CTRL |= FCSPI_TR_CTRL_RX_MSK_MASK;
    }
    else
    {
        pFCSPI->TR_CTRL &= (~(FCSPI_TR_CTRL_RX_MSK_MASK));
    }
}

/**
 * @brief Set TX enable status in register FCSPI TR_CTRL.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param eEnable FCSPI_TRUE for enabled, FCSPI_FALSE for disable.
 */
LOCAL_INLINE void FCSPI_HWA_SetTxEnableStatus(FCSPI_Type *pFCSPI, FCSPI_AtomicBoolType eEnable)
{
    if (FCSPI_FALSE == eEnable)
    {
        pFCSPI->TR_CTRL |= FCSPI_TR_CTRL_TX_MSK_MASK;
    }
    else
    {
        pFCSPI->TR_CTRL &= (~(FCSPI_TR_CTRL_TX_MSK_MASK));
    }
}

/**
 * @brief Set FCSPI TX_DATA register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_WriteData(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->TX_DATA = u32Value;
}

/**
 * @brief Get the address of FCSPI TX_DATA register,return value is the pointer address of TX_DATA.
 *
 * @param pFCSPI  FCSPI instance，e.g. FCSPI0, FCSPI1.
 * @return FCSPI TX_DATA address.
 */
LOCAL_INLINE uint32_t volatile *FCSPI_HWA_GetTxDataAddr(FCSPI_Type *pFCSPI)
{
    return (uint32_t volatile *)&(pFCSPI->TX_DATA);
}

/**
 * @brief Read FCSPI RX_STATUS register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI RX_STATUS regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetRxStatus(FCSPI_Type *pFCSPI)
{
    return pFCSPI->RX_STATUS;
}

/**
 * @brief Read FCSPI RX_DATA register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI RX_DATA regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_ReadData(FCSPI_Type *pFCSPI)
{
    return pFCSPI->RX_DATA;
}

/**
 * @brief Get the address of FCSPI RX_DATA register,return value is the pointer address of RX_DATA.
 *
 * @param pFCSPI  FCSPI instance，e.g. FCSPI0, FCSPI1.
 * @return FCSPI RX_DATA address.
 */
LOCAL_INLINE uint32_t volatile const *FCSPI_HWA_GetRxDataAddr(FCSPI_Type *pFCSPI)
{
    return &(pFCSPI->RX_DATA);
}

/**
 * @brief Get FCSPI PARITY_CHK register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @return FCSPI PARITY_CHK regsiter value
 */
LOCAL_INLINE uint32_t FCSPI_HWA_GetParityCheck(FCSPI_Type *pFCSPI)
{
    return pFCSPI->PARITY_CHK;
}

/**
 * @brief Set FCSPI PARITY_CHK register value.
 *
 * @param pFCSPI  FCSPI instance, e.g. FCSPI0, FCSPI1.
 * @param u32Value the value write to the register.
 */
LOCAL_INLINE void FCSPI_HWA_SetParityCheck(FCSPI_Type *pFCSPI, uint32_t u32Value)
{
    pFCSPI->PARITY_CHK = u32Value;
}
/** @}*/
#endif

#endif /* #ifndef _HWA_FCPIT_H_ */
