/**
 * @file HwA_rcm.h
 * @author Flagchip
 * @brief RCM hardware access layer
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/

#ifndef _HWA_RCM_H_
#define _HWA_RCM_H_

#include "device_header.h"

#if RCM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_rcm HwA_rcm
 * @ingroup module_driver_rcm
 * @{
 */

/********* Local typedef ************/
/** @brief Rcm reset event */
typedef enum
{
    RCM_WAKEUP      = 0x0001U,  /**< Wakeup reset */
    RCM_LVR         = 0x0002U,  /**< LVR reset */
    RCM_CLKERR1     = 0x0004U,  /**< Clock error 1 reset */
    RCM_CLKERR0     = 0x0008U,  /**< Clock error 0 reset */
    RCM_WDG1        = 0x0010U,  /**< WDG1 reset */
    RCM_WDG0        = 0x0020U,  /**< WDG0 reset */
    RCM_PIN         = 0x0040U,  /**< Pin reset */
    RCM_POR         = 0x0080U,  /**< POR reset */
    RCM_JTAG        = 0x0100U,  /**< JTAG reset */
    RCM_CPULOC      = 0x0200U,  /**< CPU lockup reset */
    RCM_SW          = 0x0400U,  /**< Software reset */
    RCM_SYSAP       = 0x0800U,  /**< SYSAP reset */
    RCM_INTM_TOUT   = 0x1000U,  /**< Interrupt timeout reset */
    RCM_SACKERR     = 0x2000U,  /**< SACKERR reset */
#if RCM_RESET_REQ_TOUT_SUPPORT  
	RCM_PINRST_TOUT = 0x40000000U,  /* Pin reset timeout reset */
	RCM_SYSRST_TOUT = 0x80000000U  /* System reset request timeout reset */
#endif
} RCM_ResetEventType;

/** @brief Rcm reset interrupt delay cycles type. */
typedef enum
{
    RCM_8_CLOCK_CYCLES   = 0x0U,  /**< RCM reset delay 8 clock cycles */
    RCM_32_CLOCK_CYCLES  = 0x1U,  /**< RCM reset delay 32 clock cycles */
    RCM_128_CLOCK_CYCLES = 0x2U,  /**< RCM reset delay 128 clock cycles */
    RCM_512_CLOCK_CYCLES = 0x3U   /**< RCM reset delay 512 clock cycles */
} RCM_ResetDelayType;

/** @brief Rcm reset interrupt event manger */
typedef enum
{
    RCM_INT_CLKERR1   = 0x0004U,  /**< RCM interrupt when Clock error 1 reset */
    RCM_INT_CLKERR0   = 0x0008U,  /**< RCM interrupt when Clock error 0 reset */
    RCM_INT_WDG1      = 0x0010U,  /**< RCM interrupt when WDG1 reset */
    RCM_INT_WDG0      = 0x0020U,  /**< RCM interrupt when WDG0 reset */
    RCM_INT_PIN       = 0x0040U,  /**< RCM interrupt when Pin reset */
    RCM_INT_JTAG      = 0x0100U,  /**< RCM interrupt when JTAG reset */
    RCM_INT_CPULOC    = 0x0200U,  /**< RCM interrupt when CPU lockup reset */
    RCM_INT_SW        = 0x0400U,  /**< RCM interrupt when Software reset */
    RCM_INT_SYSAP     = 0x0800U,  /**< RCM interrupt when SYSAP reset */
    RCM_INT_INTM_TOUT = 0x1000U,  /**< RCM interrupt when Interrupt timeout reset */
    RCM_INT_SACKERR   = 0x2000U,  /**< RCM interrupt when SACKERR reset */
	RCM_INT_ALL_MASK  = 0x3F7CU   /**< RCM interrupt all mask */
} RCM_ResetIntMangerType;
/********* Local inline function ************/
/**
 * @brief Read last reset flag
 *
 * @return Last reset flag
 */
LOCAL_INLINE uint32_t RCM_HWA_ReadLastResetFlag(void)
{
    return (uint32_t)RCM->SRS;
}

/**
 * @brief Read all reset flag before POR,SSRS register is reset on POR only
 *
 * @return All reset flag before POR
 */
LOCAL_INLINE uint32_t RCM_HWA_ReadAllResetFlagBeforePOR(void)
{
    return (uint32_t)RCM->SSRS;
}

/**
 * @brief Read reset pin filter register
 *
 * @return Reset pin filter register
 */
LOCAL_INLINE uint32_t RCM_HWA_ReadResetPinFilterEnable(void)
{
    return (uint32_t)RCM->RSTFLT;
}

/**
 * @brief This api can clear reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 * @param eReset Reset flag
 */
LOCAL_INLINE void RCM_HWA_ClearResetFlagAfterPOR(RCM_ResetEventType eReset)
{
    RCM->SSRS = (uint32_t)(eReset);
}

/**
 * @brief This api can clear all reset flag of SSRS register which indicate all reset sources since the last POR or LVD that have not been cleared by software.
 *
 */
LOCAL_INLINE void RCM_HWA_ClearAllResetFlagAfterPOR(void)
{
    RCM->SSRS = (uint32_t)0x3FFFU;
}

/**
 * @brief Set reset pin filter bus clock filter width
 *
 * @param u8Value Bus clock filter width value
 */
LOCAL_INLINE void RCM_HWA_SetBusClockFilterWidth(uint8_t u8Value)
{
    uint32_t u32RegValue = RCM->RSTFLT;
    RCM->RSTFLT = (u32RegValue & ~(uint32_t)RCM_RSTFLT_RSTFLT_BUSW_MASK) | RCM_RSTFLT_RSTFLT_BUSW(u8Value);
}

/**
 * @brief Set reset pin filter register
 *
 */
LOCAL_INLINE void RCM_HWA_SetRstfltReg(uint32_t u32Val)
{
    RCM->RSTFLT = u32Val;
}

/**
 * @brief Enable reset pin filter bus clock
 *
 */
LOCAL_INLINE void RCM_HWA_EnableBusClockFilter(void)
{
    RCM->RSTFLT |= (uint32_t)RCM_RSTFLT_RSTFLT_BUS_MASK;
}

/**
 * @brief Enable reset pin filter AON32K clock
 *
 */
LOCAL_INLINE void RCM_HWA_EnableAon32kClockFilter(void)
{
    RCM->RSTFLT |= (uint32_t)RCM_RSTFLT_RSTFLT_AON_MASK;
}

/**
 * @brief Enable reset pin filter AON32K low power clock
 *
 */
LOCAL_INLINE void RCM_HWA_EnableAon32kLPClockFilter(void)
{
    RCM->RSTFLT |= (uint32_t)RCM_RSTFLT_RSTFLT_AON_LP_MASK;
}

/**
 * @brief Set system reset interrupt register
 *
 */
LOCAL_INLINE void RCM_HWA_SetSrieReg(uint32_t u32Val)
{
    RCM->SRIE = u32Val;
}

/**
 * @brief Enable global reset interrupt
 *
 */
LOCAL_INLINE void RCM_HWA_EnableGlobalResetInterrupt(void)
{
    RCM->SRIE |= (uint32_t)RCM_SRIE_GLOBAL_RIE_MASK;
}

/**
 * @brief Set Reset delay
 *
 * @param eDelay Reset delay type
 */
LOCAL_INLINE void RCM_HWA_SetResetDelay(RCM_ResetDelayType eDelay)
{
    uint32_t u32RegValue = RCM->SRIE;
    RCM->SRIE = (u32RegValue & ~(uint32_t)RCM_SRIE_DELAY_MASK) | RCM_SRIE_DELAY(eDelay);
}

/**
 * @brief Clear Reset delay
 */
LOCAL_INLINE void RCM_HWA_ClearResetDelay(void)
{
    RCM->SRIE &= ~(uint32_t)RCM_SRIE_DELAY_MASK;
}

/**
 * @brief Enable reset interrupt
 *
 * @param u16Int Reset interrupt type
 */
LOCAL_INLINE void RCM_HWA_EnableResetInterrupt(uint16_t u16Int)
{
    RCM->SRIE |= (uint32_t)(u16Int & RCM_INT_ALL_MASK);
}

/**
 * @brief Disable reset interrupt
 *
 * @param u16Int Reset interrupt type
 */
LOCAL_INLINE void RCM_HWA_DisableResetInterrupt(uint16_t u16Int)
{
    RCM->SRIE &= ~(uint32_t)(u16Int & RCM_INT_ALL_MASK);
}

/**
 * @brief Clear reset pin filter bus clock filter width
 *
 */
LOCAL_INLINE void RCM_HWA_ClearBusClockFilterWidth(void)
{
    RCM->RSTFLT &= ~(uint32_t)RCM_RSTFLT_RSTFLT_BUSW_MASK;
}
/**
 * @brief Disable reset pin filter bus clock
 *
 */
LOCAL_INLINE void RCM_HWA_DisableBusClockFilter(void)
{
    RCM->RSTFLT &= ~(uint32_t)RCM_RSTFLT_RSTFLT_BUS_MASK;
}

/**
 * @brief Disable reset pin filter AON32K clock
 *
 */
LOCAL_INLINE void RCM_HWA_DisableAon32kClockFilter(void)
{
    RCM->RSTFLT &= ~(uint32_t)RCM_RSTFLT_RSTFLT_AON_MASK;
}

/**
 * @brief Disable reset pin filter AON32K low power clock
 *
 */
LOCAL_INLINE void RCM_HWA_DisableAon32kLPClockFilter(void)
{
    RCM->RSTFLT &= ~(uint32_t)RCM_RSTFLT_RSTFLT_AON_LP_MASK;
}


/**
 * @brief Perform system reset.
 *
 */
LOCAL_INLINE void CM4_HWA_SystemReset(void)
{
    uint32 u32Temp;
    u32Temp = SCB->AIRCR;
    u32Temp &= ~(uint32)(SCB_AIRCR_VECTKEY_Msk);
    u32Temp |= (uint32)(SCB_AIRCR_VECTKEY(0x5FAU) | SCB_AIRCR_SYSRESETREQ_Msk | SCB_AIRCR_PRIGROUP_Msk);
    SCB->AIRCR = u32Temp;
}

/** @}*/

#endif


#endif /* #ifndef _HWA_RCM_H_ */
