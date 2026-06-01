/**
 * @file HwA_intm.h
 * @author Flagchip084
 * @brief INTM hardware access layer
 * @version 2.0.0
 * @date 2024-02-13
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#ifndef _HWA_INTM_H_
#define _HWA_INTM_H_

#include "device_header.h"

#if INTM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_intm HwA_intm
 * @ingroup module_driver_intm
 * @{
 */

/**
 * @brief Represents the memory-mapped registers for the interrupt monitoring module.
 *
 * This structure contains the memory-mapped registers for controlling and monitoring interrupts.
 *
 * @note The registers are accessed directly through memory addresses.
 */
typedef struct
{
    __IO uint32_t IRQSELR;  /**< INTM Interrupt Request Select Register*/
    __IO uint32_t LATR;     /**< INTM Latency Register */
    __IO uint32_t TMR;      /**< INTM Timer Register */
    __I  uint32_t SR;       /**< INTM Status Register */
} INTM_MonitorType, *INTM_MonitorMemMapPtr;

/**
 * @brief Enable the INTM.
 * @param pIntm INTM instance. INTM instance.
 * @param bEnable Enable the ITNM.
 */
LOCAL_INLINE void INTM_HWA_Enable(INTM_Type *const pIntm, bool bEnable)
{
    if (bEnable)
    {
        pIntm->ER = INTM_ER_EN_MASK;
    }
    else
    {
        pIntm->ER = 0U;
    }
}

/**
 * @brief Get the instance of interrupt monitor.
 * @param pIntm INTM instance.
 * @param u8IrqMonitorIndex Interrupt monitor index.
 * @return Monitor Instance.
 */
LOCAL_INLINE INTM_MonitorType *INTM_HWA_GetIrqMonitor(INTM_Type *const pIntm, uint8_t u8IrqMonitorIndex)
{
    return (INTM_MonitorType *)((uint32_t) & (pIntm->IRQSELR0) + (uint32_t)u8IrqMonitorIndex * 0x10U);
}

/**
 * @brief Set the interrupt acknowledge.
 * @param pIntm INTM instance.
 * @param u16IrqNum Interrupt number to be monitored.
 */
LOCAL_INLINE void INTM_HWA_SetIACKR(INTM_Type *const pIntm, uint16_t u16IrqNum)
{
    pIntm->IACKR = u16IrqNum;
}

/**
 * @brief Sets the IRQ request number in the INTM monitor.
 * 
 * This function configures the IRQ request number in the INTM monitor by writing the provided
 * IRQ number to the IRQSELR register. This is used to specify which IRQ is being monitored or requested.
 * 
 * @param pIrqMon Pointer to the INTM monitor structure.
 * @param u16IrqNum The IRQ number to set.
 */
LOCAL_INLINE void INTM_HWA_SetIRQReqNum(INTM_MonitorType *const pIrqMon, uint16_t u16IrqNum)
{
    pIrqMon->IRQSELR = u16IrqNum;
}

/**
 * @brief Enable reset when interrupt delays overtime.
 * @param pIrqMon Interrupt monitor instance.
 * @param bEnable Enable reset.
 */
LOCAL_INLINE void INTM_HWA_EnableReset(INTM_MonitorType *const pIrqMon, bool bEnable)
{
    pIrqMon->IRQSELR = (pIrqMon->IRQSELR & ~INTM_IRQSELR_RSTE_MASK) | INTM_IRQSELR_RSTE(bEnable);
}

/**
 * @brief Enable interrupt when monitored interrupt delays overtime.
 * @param pIrqMon Interrupt monitor instance.
 * @param bEnable Enabel the interrupt.
 */
LOCAL_INLINE void INTM_HWA_EnableInterrupt(INTM_MonitorType *const pIrqMon, bool bEnable)
{
    pIrqMon->IRQSELR = (pIrqMon->IRQSELR & ~INTM_IRQSELR_INTE_MASK) | INTM_IRQSELR_INTE(bEnable);
}

/**
 * @brief Enable inactive mode.
 * @param pIrqMon Interrupt monitor instance.
 * @param bEnable Enable inactive mode.
 */
LOCAL_INLINE void INTM_HWA_EnableInactiveMode(INTM_MonitorType *const pIrqMon, bool bEnable)
{
    pIrqMon->IRQSELR = (pIrqMon->IRQSELR & ~INTM_IRQSELR_IACTE_MASK) | INTM_IRQSELR_IACTE(bEnable);
    __asm volatile(
        "dmb                            \n"
        "ldr r8, [%[IRQSELR]]			\n"/* Must Read IRQSELR after set. */
        : : [IRQSELR] "r"(&pIrqMon->IRQSELR) : "r8", "memory"
    );
}

/**
 * @brief Start the inactive mode.
 * @param pIrqMon Interrupt monitor instance.
 */
LOCAL_INLINE void INTM_HWA_StartInactiveMode(INTM_MonitorType *const pIrqMon)
{
    pIrqMon->IRQSELR |= INTM_IRQSELR_IACTST_MASK;
    __asm volatile(
        "dmb                            \n"
        "ldr r8, [%[IRQSELR]]			\n"/* Must Read IRQSELR after set. */
        : : [IRQSELR] "r"(&pIrqMon->IRQSELR) : "r8", "memory"
    );
}

/**
 * @brief Stops the inactive mode monitoring in the INTM monitor.
 * 
 * This function clears the inactive mode bit in the IRQSELR register of the INTM monitor.
 * This action stops the monitoring of the inactive mode status.
 * 
 * @param pIrqMon Pointer to the INTM monitor structure.
 */
LOCAL_INLINE void INTM_HWA_StopInactiveMode(INTM_MonitorType *const pIrqMon)
{
    pIrqMon->IRQSELR &= ~INTM_IRQSELR_IACTST_MASK;
}

/**
 * @brief Set the timeout value of interrupt.
 * @param pIrqMon Interrupt monitor instance.
 * @param u32Latency the timeout value of interrupt monitor.
 */
LOCAL_INLINE void INTM_HWA_SetLatency(INTM_MonitorType *const pIrqMon, uint32_t u32Latency)
{
    pIrqMon->LATR = u32Latency;
}

/**
 * @brief Get the value of timer.
 * @param pIrqMon Interrupt monitor instance.
 * @return Timer value
 */
LOCAL_INLINE uint32_t INTM_HWA_GetTimerCounter(INTM_MonitorType *const pIrqMon)
{
    return pIrqMon->TMR;
}

/**
 * @brief Set the value of timer.
 * @param pIrqMon Interrupt monitor instance.
 * @param u32Value The value to be set.
 */
LOCAL_INLINE void INTM_HWA_SetTimerCounter(INTM_MonitorType *const pIrqMon, uint32_t u32Value)
{
    pIrqMon->TMR = u32Value;
}

/**
 * @brief Read interrupt status.
 * @param pIrqMon Interrupt monitor instance.
 * @return Interrupt status.
 */
LOCAL_INLINE bool INTM_HWA_ReadStatus(INTM_MonitorType *const pIrqMon)
{
    return (pIrqMon->SR & INTM_SR_MASK) == INTM_SR_MASK ? true : false;
}

/** @}*/

#endif

#endif  /*#ifndef _HWA_INTM_H_*/
