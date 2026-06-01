/**
 * @file HwA_fcpit.h
 * @author Flagchip032
 * @brief FCPIT hardware access layer
 * @version 2.0.0
 * @date 2024-03-22
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/

#ifndef _HWA_FCPIT_H_
#define _HWA_FCPIT_H_

#include "device_header.h"

#if FCPIT_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_fcpit HwA_fcpit
 * @ingroup module_driver_fcpit
 * @{
 */

/********* Local typedef ************/
/** @brief Fcpit counter mode, the default mode is 32bit periodic count mode */
typedef enum
{
    FCPIT_32PERIODIC_COUNTER = 0,               /**< 32-bit Periodic Counter*/
    FCPIT_DUAL_16PERIODIC_COUNTER,              /**< Dual 16-bit Periodic Counter*/
    FCPIT_ACCUMULATOR,                          /**< 32-bit Trigger Accumulator*/
    FCPIT_INPUT_CAPTURE,                        /**< 32-bit Trigger Input Capture*/
	FCPIT_CHANNEL_NOMODE                        /**< No mode*/
} FCPIT_TimerModeType;

/** @brief Fcpit channel number */
typedef enum
{
    FCPIT_CHANNEL_0 = 0U,                        /**< FCPIT channel 0*/
    FCPIT_CHANNEL_1,                            /**< FCPIT channel 1*/
    FCPIT_CHANNEL_2,                            /**< FCPIT channel 2*/
    FCPIT_CHANNEL_3,                            /**< FCPIT channel 3*/
	FCPIT_CHANNEL_MAX
} FCPIT_ChannelType;
/********* Local inline function ************/
/**
 * @brief Set FCPIT channel value
 *
 * @param eChannel FCPIT channel number
 * @param u32RegValue Timer value
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelValue(FCPIT_ChannelType eChannel, uint32_t u32RegValue)
{
    FCPIT->CONTROLS[eChannel].TVAL = u32RegValue;
}

/**
 * @brief Configure FCPIT channel
 *
 * @param eChannel FCPIT channel number
 * @param u32RegValue TCTRL register value
 */
LOCAL_INLINE void FCPIT_HWA_ConfigChannel(FCPIT_ChannelType eChannel, uint32_t u32RegValue)
{
    FCPIT->CONTROLS[eChannel].TCTRL = u32RegValue;
}

/**
 * @brief Configure FCPIT module
 *
 * @param u32RegValue MCR register value
 */
LOCAL_INLINE void FCPIT_HWA_ConfigModule(uint32_t u32RegValue)
{
    FCPIT->MCR = u32RegValue;
}


/**
 * @brief Read FCPIT module enable
 *
 * @return MCR register with FCPIT_MCR_M_CEN_MASK
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadModuleEnable(void)
{
    return (uint32_t)(FCPIT->MCR & FCPIT_MCR_M_CEN_MASK);
}

/**
 * @brief Read FCPIT channel
 *
 * @param eChannel Channel number
 * @return TCTRL register with FCPIT_TCTRL_T_EN_MASK
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadChannelEnable(FCPIT_ChannelType eChannel)
{
    return (uint32_t)(FCPIT->CONTROLS[eChannel].TCTRL & FCPIT_TCTRL_T_EN_MASK);
}

/**
 * @brief Read FCPIT active interrupt flag
 *
 * @return FCPIT active interrupt flag
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadInterruptFlag(void)
{
    return (FCPIT->MSR);
}

/**
 * @brief Read FCPIT enable interrupt flag
 *
 * @return FCPIT enable interrupt flag
 */
LOCAL_INLINE uint32_t FCPIT_HWA_ReadEnableInterruptFlag(void)
{
    return (FCPIT->MIER);
}

/**
 * @brief Set FCPIT channel running on debug mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelRunOnDebug(void)
{
    FCPIT->MCR |= FCPIT_MCR_DBG_EN_MASK;
}

/**
 * @brief Set FCPIT channel running on low power mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelRunOnLpm(void)
{
    FCPIT->MCR |= FCPIT_MCR_LPM_EN_MASK;
}

/**
 * @brief Enable FCPIT module
 *
 */
LOCAL_INLINE void FCPIT_HWA_EnableModule(void)
{
    FCPIT->MCR |= FCPIT_MCR_M_CEN_MASK;
}

/**
 * @brief Enable FCPIT channel(n) interrupt
 *
 * @param u32RegValue u32RegValue 0-3 bit indicate TIE0-TIE3
 */
LOCAL_INLINE void FCPIT_HWA_EnableChannelsInterrupt(uint32_t u32RegValue)
{
    FCPIT->MIER |= u32RegValue;
}

/**
 * @brief Enable FCPIT channel
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_EnableChannel(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_T_EN_MASK;
}

/**
 * @brief Enable FCPIT channel(n) chain mode
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_EnableChannelChainMode(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_CHAIN_MASK;
}

/**
 * @brief Configure FCPIT channel operation mode
 *
 * @param eChannel FCPIT channel number
 * @param eMode FCPIT operation mode
 */
LOCAL_INLINE void FCPIT_HWA_ConfigChannelMode(FCPIT_ChannelType eChannel, FCPIT_TimerModeType eMode)
{
    uint32_t u32RegValue = FCPIT->CONTROLS[eChannel].TCTRL;
    FCPIT->CONTROLS[eChannel].TCTRL = (u32RegValue & ~(uint32_t)FCPIT_TCTRL_MODE_MASK) | FCPIT_TCTRL_MODE(eMode);
}

/**
 * @brief Set FCPIT channel start on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStartOnTrig(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TSOT_MASK;
}

/**
 * @brief Set FCPIT channel stop on interrupt
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStopOnInterrupt(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TSOI_MASK;
}

/**
 * @brief Set FCPIT channel reload on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelReloadOnTrig(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TROT_MASK;
}

/**
 * @brief Set FCPIT channel trigger source
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelTriggerSrc(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL |= FCPIT_TCTRL_TRG_SRC_MASK;
}

/**
 * @brief Select FCPIT channel trigger
 *
 * @param eChannel FCPIT channel number
 * @param u8SelChannel Select channel, range is 0-3
 */
LOCAL_INLINE void FCPIT_HWA_SelectChannelTrigger(FCPIT_ChannelType eChannel, uint8_t u8SelChannel)
{
    uint32_t u32RegValue = FCPIT->CONTROLS[eChannel].TCTRL;
    FCPIT->CONTROLS[eChannel].TCTRL = (u32RegValue & ~(uint32_t)FCPIT_TCTRL_TRG_SEL_MASK) | FCPIT_TCTRL_TRG_SEL(
                                          u8SelChannel);
}

/**
 * @brief Set FCPIT channel stop on debug mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStopOnDebug(void)
{
    FCPIT->MCR &= ~(uint32_t)FCPIT_MCR_DBG_EN_MASK;
}

/**
 * @brief Set FCPIT channel stop on low power mode
 *
 */
LOCAL_INLINE void FCPIT_HWA_SetChannelStopOnLpm(void)
{
    FCPIT->MCR &= ~(uint32_t)FCPIT_MCR_LPM_EN_MASK;
}

/**
 * @brief Disable FCPIT module
 *
 */
LOCAL_INLINE void FCPIT_HWA_DisableModule(void)
{
    FCPIT->MCR &= ~(uint32_t)FCPIT_MCR_M_CEN_MASK;
}

/**
 * @brief Clear FCPIT channel(n) interrupt flag
 *
 * @param u32RegValue 0-3 bit indicate TIF0-TIF3
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelsInterruptFlag(uint32_t u32RegValue)
{
    FCPIT->MSR = u32RegValue;
}

/**
 * @brief Disable FCPIT channel(n) interrupt
 *
 * @param u32RegValue u32RegValue 0-3 bit indicate TIE0-TIE3
 */
LOCAL_INLINE void FCPIT_HWA_DisableChannelsInterrupt(uint32_t u32RegValue)
{
    FCPIT->MIER &= ~u32RegValue;
}

/**
 * @brief Disable FCPIT channel
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_DisableChannel(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_T_EN_MASK;
}

/**
 * @brief Disable FCPIT channel chain mode
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_DisableChannelChainMode(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_CHAIN_MASK;
}

/**
 * @brief Clear FCPIT channel operation mode
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelMode(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_MODE_MASK;
}

/**
 * @brief Clear FCPIT channel start on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelStartOnTrig(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TSOT_MASK;
}

/**
 * @brief Clear FCPIT channel stop on interrupt
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelStopOnInterrupt(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TSOI_MASK;
}

/**
 * @brief Clear FCPIT channel reload on trigger
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelReloadOnTrig(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TROT_MASK;
}

/**
 * @brief Clear FCPIT channel trigger source
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelTriggerSrc(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TRG_SRC_MASK;
}

/**
 * @brief Clear FCPIT channel trigger select
 *
 * @param eChannel FCPIT channel number
 */
LOCAL_INLINE void FCPIT_HWA_ClearChannelTriggerSelect(FCPIT_ChannelType eChannel)
{
    FCPIT->CONTROLS[eChannel].TCTRL &= ~(uint32_t)FCPIT_TCTRL_TRG_SEL_MASK;
}

/** @}*/

#endif

#endif /* #ifndef _HWA_FCPIT_H_ */
