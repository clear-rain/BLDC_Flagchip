/**
 * @file HwA_smisc.h
 * @author Flagchip
 * @brief SMISC hardware access layer
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

#ifndef _HWA_SMISC_H_
#define _HWA_SMISC_H_

#include "device_header.h"

#if SMISC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_smisc HwA_smisc
 * @ingroup module_driver_smisc
 * @{
 */

/********* Local define ************/
/**
 * @name  PLL related macros
 *
 * @{
 */
#define SMISC_FTUOPT0FTU0123_CLKSEL(clk, instance) (uint32_t)((uint32_t)(clk) << (((uint32_t)(instance) << 1U) + 24U))
#define SMISC_FTUOPT0FTU0123_CLKSEL_MASK(instance) (uint32_t)((uint32_t)3U << (((uint32_t)(instance) << 1U) + 24U))

#define SMISC_FTUOPT0FTU4567_CLKSEL(clk, instance) (uint32_t)((uint32_t)(clk) << ((((uint32_t)(instance) - 4U) << 1U) + 16U))
#define SMISC_FTUOPT0FTU4567_CLKSEL_MASK(instance) (uint32_t)((uint32_t)3U << ((((uint32_t)(instance) - 4U) << 1U) + 16U))
/** @}*/ 

/********* Local typedef ************/
/**
 * @brief external clock enumeration
 *
 */
typedef enum
{
    FTU_TCLK0_USED 	= 0U,		/**< FTU_TCLK0 pin as FTU external clock */
    FTU_TCLK1_USED 	= 1U,		/**< FTU_TCLK1 pin as FTU external clock */
    FTU_TCLK2_USED 	= 2U,		/**< FTU_TCLK2 pin as FTU external clock */
    FTU_NO_CLK_USED = 3U,		/**< No clock input */
} FTU_TclkSelType;

/** @brief Ftu Trig1 sync event type */
typedef enum
{
    SMISC_FTU_TRIG1_FTU0SYNC = 0x01U,  /**< SMSIC FTU0SYNC related */
    SMISC_FTU_TRIG1_FTU1SYNC = 0x02U,  /**< SMSIC FTU1SYNC related */
    SMISC_FTU_TRIG1_FTU2SYNC = 0x04U,  /**< SMSIC FTU2SYNC related */
    SMISC_FTU_TRIG1_FTU3SYNC = 0x08U,  /**< SMSIC FTU3SYNC related */
    SMISC_FTU_TRIG1_FTU4SYNC = 0x800U, /**< SMSIC FTU4SYNC related */
    SMISC_FTU_TRIG1_FTU5SYNC = 0x1000U, /**< SMSIC FTU5SYNC related */
#if (FTU_INSTANCE_COUNT == 8u)
    SMISC_FTU_TRIG1_FTU6SYNC = 0x2000U, /**< SMSIC FTU6SYNC related */
    SMISC_FTU_TRIG1_FTU7SYNC = 0x4000U, /**< SMSIC FTU7SYNC related */
#endif
} SMISC_TRIG1SyncGenType;

/********* Local inline function ************/
/**
 * @brief Set FTU(n) external clock source
 *
 * @param u32FtuInstance FTU instance number, range is 0-7
 * @param eClk FTU clock select enumeration
 */
LOCAL_INLINE void SMISC_HWA_SetFtuExternalClkSrc(uint32_t u32FtuInstance, FTU_TclkSelType eClk)
{
    uint32_t u32RegValue = SMISC->FTUOPTR0;
    if (u32FtuInstance >= (uint32_t)4U)
    {
        SMISC->FTUOPTR0 = (u32RegValue & ~SMISC_FTUOPT0FTU4567_CLKSEL_MASK(u32FtuInstance)) | SMISC_FTUOPT0FTU4567_CLKSEL(eClk,
                          u32FtuInstance);
    }
    else
    {
        SMISC->FTUOPTR0 = (u32RegValue & ~SMISC_FTUOPT0FTU0123_CLKSEL_MASK(u32FtuInstance)) | SMISC_FTUOPT0FTU0123_CLKSEL(eClk,
                          u32FtuInstance);
    }
}

/**
 * @brief Generate FTU TRIG1 trigger
 *
 * @param eTrigGen TRIG1 trigger type
 */
LOCAL_INLINE void SMISC_HWA_GenerateFtuTrig1Trigger(SMISC_TRIG1SyncGenType eTrigGen)
{
    SMISC->FTUOPTR1 |= (uint32_t)eTrigGen;
    SMISC->FTUOPTR1 &= ~(uint32_t)eTrigGen;
}

/**
 * @brief Generate trigger signal for the selected software trigger source channel
 * @param u8Channal the software trigger channel, range 0~7
 */
LOCAL_INLINE void SMISC_HWA_GenerateSwTrigger(uint8_t u8Channal)
{
    SMISC->SOFTCTRL |= (SMISC_SOFTCTRL_SWTRG0_MASK << u8Channal);
    SMISC->SOFTCTRL &= ~(SMISC_SOFTCTRL_SWTRG0_MASK << u8Channal);
}

/**
 * @brief Get whether Ptimer inter instance back to back trigger is enabled
 * 
 * @return true Ptimer inter instance back to back trigger is enabled
 * @return false Ptimer inter instance back to back trigger is disabled
 */
LOCAL_INLINE bool SMISC_HWA_GetPtimerInstanceBackToBackEnableFlag(void)
{
    uint32_t u32TmpVal = (SMISC->CHIPCTLR & SMISC_CHIPCTLR_PTIMER_BTB_SEL_MASK) >> SMISC_CHIPCTLR_PTIMER_BTB_SEL_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set whether to enable Ptimer inter instance back to back trigger
 * 
 * @param bEnable whether to enable Ptimer inter instance back to back trigger
 */
LOCAL_INLINE void SMISC_HWA_SetPtimerInstanceBackToBackEnableFlag(bool bEnable)
{
    SMISC->CHIPCTLR = (SMISC->CHIPCTLR & ~SMISC_CHIPCTLR_PTIMER_BTB_SEL_MASK) | SMISC_CHIPCTLR_PTIMER_BTB_SEL(bEnable);
}

/**
 * @brief Set CHIPCTLR value. used to set SMISC clock out configuration.
 *
 * @param u32ChipCtrl value for this register configuration.
 */
LOCAL_INLINE void SMISC_HWA_SetChipCtrl(uint32_t u32ChipCtrl)
{
    SMISC->CHIPCTLR = u32ChipCtrl;
}

/**
 * @brief Set SYSCGC value. for the extra clock gate define in SMISC.
 *
 * @param u32SysCgc value for SYSCGC register configuration.
 */
LOCAL_INLINE void SMISC_HWA_SetSysCgc(uint32_t u32SysCgc)
{
    SMISC->SYSCGC = (uint32_t)u32SysCgc;
}

/**
 * @brief Disable Trace clock Divider.
 *
 */
LOCAL_INLINE void SMISC_HWA_DisableTraceClkDiv(void)
{
    SMISC->TRACECLKDIV &= ~SMISC_TRACECLKDIV_TRACEDIVEN_MASK;
}

/**
 * @brief Set Trace clock Divider value.
 * 
 * @param u32TraceClkDiv Trace clock Divider value.
 */
LOCAL_INLINE void SMISC_HWA_SetTraceClkDiv(uint32_t u32TraceClkDiv)
{
    SMISC->TRACECLKDIV = u32TraceClkDiv;
}

/**
 * @brief Set Always on clock source.
 *
 * @param u32AonClkSr value for AONCLKSR register configuration.
 */
LOCAL_INLINE void SMISC_HWA_SetAonClkSr(uint32_t u32AonClkSr)
{
    SMISC->AONCLKSR = u32AonClkSr;
}

/**
 * @brief Get Always on clock source.
 *
 * @return AONCLKSR register value.
 */
LOCAL_INLINE uint32_t SMISC_HWA_GetAonClkSr(void)
{
    return SMISC->AONCLKSR;
}

/**
 * @brief Enable extra clock gate by specific clock.
 *
 * @param u32Val the value of this register
 */
LOCAL_INLINE void SMISC_HWA_SetSysClock(uint32_t u32Val)
{
    SMISC->SYSCGC |= u32Val;
}

/**
 * @brief Get bit[31:0] of Unique Identification from register UID0
 *
 * @return UID0 the value of this register
 */
LOCAL_INLINE uint32_t SMISC_HWA_GetUID0(void)
{
    return SMISC -> UID0;
}

/**
 * @brief Get bit[63:32] of Unique Identification from register UID1
 *
 * @return UID1 the value of this register
 */
LOCAL_INLINE uint32_t SMISC_HWA_GetUID1(void)
{
    return SMISC -> UID1;
}

/**
 * @brief Get bit[95:64] of Unique Identification from register UID2
 *
 * @return UID2 the value of this register
 */
LOCAL_INLINE uint32_t SMISC_HWA_GetUID2(void)
{
    return SMISC -> UID2;
}

/**
 * @brief Get bit[127:96] of Unique Identification from register UID3
 *
 * @return UID3 the value of this register
 */
LOCAL_INLINE uint32_t SMISC_HWA_GetUID3(void)
{
    return SMISC -> UID3;
}

/**
 * @brief Enable FTU Global Time Base.
 *
 */
LOCAL_INLINE void SMISC_HWA_EnabeFtuGTB(void)
{
	SMISC->PERICTLR |= SMISC_PERICTLR_FTU_GTBCTRL_MASK;
}
/**
 * @brief Disable FTU Global Time Base.
 *
 */
LOCAL_INLINE void SMISC_HWA_DisabeFtuGTB(void)
{
	SMISC->PERICTLR  &= (~SMISC_PERICTLR_FTU_GTBCTRL_MASK);
}

/** @}*/

#endif


#endif /* #ifndef _HWA_SMISC_H_ */
