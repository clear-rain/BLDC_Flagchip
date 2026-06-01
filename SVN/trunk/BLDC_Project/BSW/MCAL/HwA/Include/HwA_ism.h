/**
 * @file HwA_ism.h
 * @author Flagchip084
 * @brief ISM hardware access layer
 * @version 2.0.0
 * @date 2024-02-13
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip084   N/A          First version
*********************************************************************************/
#ifndef _HWA_ISM_H_
#define _HWA_ISM_H_

#include "device_header.h"

#if ISM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_ism HwA_ism
 * @ingroup module_driver_ism
 * @{
 */

/********* macros ************/

/********* Local typedef ************/


/**
 * @brief Define the structure type for the FPC module
 *
 */
typedef struct
{
    __IO uint32_t FPC_STATUS;               /**<  FPC status register*/
    __IO uint32_t FPC_CTRL;                 /**<  FPC control register*/
    __IO uint32_t FPC_CONFIG;               /**<  FPC configuration register*/
    __IO uint32_t FPC_TIMER;                /**<  FPC timer register*/
} FPC_Type, *FPC_MemMapPtr;                 /**<  FPC_Type is the struct type name, and FPC_MemMapPtr is the pointer type to this struct*/

/**
 * @brief Define the structure type for the LAM module
 *
 */
typedef struct
{
    __IO uint32_t LAM_STATUS;               /**<  LAM status register*/
    __IO uint32_t LAM_CTRL;                 /**<  LAM control register*/
    __IO uint32_t LAM_CONFIG;               /**<  LAM configuration register*/
    __IO uint32_t LAM_COUNTER;              /**<  LAM counter register*/
} LAM_Type, *LAM_MemMapPtr;                 /**<  LAM_Type is the struct type name, and LAM_MemMapPtr is the pointer type to this struct*/

typedef enum
{
    ISM_FPC_DETECT_NO_FILTER        = 0U,   /**<  No filter mode. Copy input to SOUT directly, which is LAM input.*/
    ISM_FPC_DETECT_IMMI_FILTER      = 1U,   /**<  Immediate filter mode.*/
    ISM_FPC_DETECT_DELAY_MODE       = 2U,   /**<  Delay mode.*/
    ISM_FPC_DETECT_PRESCALER_MODE   = 3U    /**<  Prcaler mode.*/
} ISM_FPC_EdgeDetectModeType;

typedef enum
{
    ISM_FPC_DELAY_FIXED0        = 0U,   /**<Fixed delay mode.*/
    ISM_FPC_DELAY_FIXED1        = 1U,   /**<Fixed delay mode.*/
    ISM_FPC_DELAY_SMART_DELAY0  = 2U,   /**<Smart delay mode. The counter is decremented when a glitch happens.*/
    ISM_FPC_DELAY_SMART_DELAY1  = 3U    /**<Smart delay mode. The counter is reset when a glitch happens.*/
} ISM_FPC_EdgeDelayModeType;


typedef enum
{
    ISM_LAM_EVT_WIN_NON_INVERT  = 0U,   /**<Event window non-inverted.*/
    ISM_LAM_EVT_WIN_INVERT      = 1U    /**<Event window inverted.*/
} ISM_LAM_InvertEventWindowType;

typedef enum
{
    ISM_LAM_NTR_CLEAR_NTR_GATE  = 0U,   /**< Neither edge used to clear the event window counter. Neither edge used to gate event generation.*/
    ISM_LAM_POS_CLEAR_NTR_GATE  = 1U,   /**< Positive edge used to clear the event window counter. Neither edge used to gate event generation.*/
    ISM_LAM_NEG_CLEAR_NTR_GATE  = 2U,   /**< Negative edge used to clear the event window counter. Neither edge used to gate event generation.*/
    ISM_LAM_ETR_CLEAR_NTR_GATE  = 3U,   /**< Either edge used to clear the event window counter. Neither edge used to gate event generation.*/
    ISM_LAM_NTR_CLEAR_POS_GATE  = 4U,   /**< Neither edge used to clear the event window counter. Positive edge used to gate event generation.*/
    ISM_LAM_POS_CLEAR_POS_GATE  = 5U,   /**< Positive edge used to clear the event window counter. Positive edge used to gate event generation.*/
    ISM_LAM_NEG_CLEAR_POS_GATE  = 6U,   /**< Negative edge used to clear the event window counter. Positive edge used to gate event generation.*/
    ISM_LAM_ETR_CLEAR_POS_GATE  = 7U,   /**< Either edge used to clear the event window counter. Positive edge used to gate event generation.*/
    ISM_LAM_NTR_CLEAR_NEG_GATE  = 8U,   /**< Neither edge used to clear the event window counter. Negative edge used to gate event generation.*/
    ISM_LAM_POS_CLEAR_NEG_GATE  = 9U,   /**< Positive edge used to clear the event window counter. Negative edge used to gate event generation.*/
    ISM_LAM_NEG_CLEAR_NEG_GATE  = 10U,  /**< Negative edge used to clear the event window counter. Negative edge used to gate event generation.*/
    ISM_LAM_ETR_CLEAR_NEG_GATE  = 11U,  /**< Either edge used to clear the event window counter. Negative edge used to gate event generation.*/
    ISM_LAM_NTR_CLEAR_ETR_GATE  = 12U,  /**< Neither edge used to clear the event window counter. Either edge used to gate event generation.*/
    ISM_LAM_POS_CLEAR_ETR_GATE  = 13U,  /**< Positive edge used to clear the event window counter. Either edge used to gate event generation.*/
    ISM_LAM_NEG_CLEAR_ETR_GATE  = 14U,  /**< Negative edge used to clear the event window counter. Either edge used to gate event generation.*/
    ISM_LAM_ETR_CLEAR_ETR_GATE  = 15U   /**< Either edge used to clear the event window counter. Either edge used to gate event generation.*/
} ISM_LAM_EventWindowEdgeType;

typedef enum
{
    ISM_LAM_EVT_WIN_SEL_REF = 0U,   /**< Event window generation is determined from the reference signal.*/
    ISM_LAM_EVT_WIN_SEL_MON = 1U    /**< Event window generation is determined from the monitor signal.*/
} ISM_LAM_EventWindowSelectType;

typedef enum
{
    ISM_LAM_RUN_FREE    = 0U,   /**< Event window generation is free-running.*/
    ISM_LAM_RUN_GATED   = 1U    /**< Event window generation is gated with the monitor or reference signal.*/
} ISM_LAM_RunModeSelectType;


typedef enum
{
    ISM_LAM_SRC_FPC_MON         = 0U,   /**< Monitor signal is sourced directly from FPC monitor channel.*/
    ISM_LAM_SRC_EXORD_FPC_REF   = 1U    /**< Monitor signal is EXOR'd with FPC reference channel.*/
} ISM_LAM_MonitorSourceType;

typedef enum
{
    ISM_LAM_FPC_MON_NON_INVERT  = 0U,   /**< Do not invert the monitor signal from FPC.*/
    ISM_LAM_FPC_MON_INVERT      = 1U    /**< Invert the monitor signal from FPC.*/
} ISM_LAM_InvertMonitorType;

typedef enum
{
    ISM_LAM_FPC_REF_NON_INVERT  = 0U,   /**< Do not invert the reference signal from FPC.*/
    ISM_LAM_FPC_REF_INVERT      = 1U    /**< Invert the reference signal from FPC.*/
} ISM_LAM_InvertReferenceType;

/********* Local inline function   ************/

/*********  ISM Register interface ************/

/**
 * @brief Get ISM ECM count
 *
 * @param pIsm ISM Instance
 * @return ECM count
 */
LOCAL_INLINE uint8_t ISM_HWA_PARAM_ECMC(ISM_Type *const pIsm)
{
    return (uint8_t)((pIsm->PARAM & ISM_PARAM_ECMC_MASK) >> ISM_PARAM_ECMC_SHIFT);
}

/**
 * @brief Get ISM FPC count
 *
 * @param pIsm ISM Instance
 * @return FPC count
 */
LOCAL_INLINE uint8_t ISM_HWA_PARAM_FPC(ISM_Type *const pIsm)
{
    return (uint8_t)((pIsm->PARAM & ISM_PARAM_FPC_MASK) >> ISM_PARAM_FPC_SHIFT);
}

/**
 * @brief Get ISM LAM count
 *
 * @param pIsm ISM Instance
 * @return LAM count
 */
LOCAL_INLINE uint8_t ISM_HWA_PARAM_LAM(ISM_Type *const pIsm)
{
    return (uint8_t)((pIsm->PARAM & ISM_PARAM_LAM_MASK) >> ISM_PARAM_LAM_SHIFT);
}

/**
 * @brief Enable ISM
 *
 * @param pIsm ISM Instance
 * @param bEnable EN value
 */
LOCAL_INLINE void ISM_HWA_Enable(ISM_Type *const pIsm, bool bEnable)
{
    pIsm->CTRL = (pIsm->CTRL & ~ISM_CTRL_EN_MASK) | ISM_CTRL_EN(bEnable);
}

/**
 * @brief Enable ISM Interrupt
 *
 * @param pIsm ISM Instance
 * @param bEnable IEN value
 */
LOCAL_INLINE void ISM_HWA_InterruptEnable(ISM_Type *const pIsm, bool bEnable)
{
    pIsm->CTRL = (pIsm->CTRL & ~ISM_CTRL_IEN_MASK) | ISM_CTRL_IEN(bEnable);
}

/**
 * @brief Get ECS of ISM_E_STATUS register
 *
 * @param pIsm ISM Instance
 * @return ECS value
 */
LOCAL_INLINE uint8_t ISM_HWA_GetEcs(ISM_Type *const pIsm)
{
    return (uint8_t)((pIsm->E_STATUS & ISM_E_STATUS_ECS_MASK) >> ISM_E_STATUS_ECS_SHIFT);
}

/**
 * @brief Clear ECS of ISM_E_STATUS register
 *
 * @param pIsm ISM Instance
 * @param u32Channels ECM channels
 */
LOCAL_INLINE void ISM_HWA_ClearEcs(ISM_Type *const pIsm, uint32_t u32Channels)
{
    pIsm->E_STATUS = (u32Channels << ISM_E_STATUS_ECS_SHIFT) & ISM_E_STATUS_ECS_MASK;
}

/**
 * @brief Get ES of ISM_E_STATUS register
 *
 * @param pIsm ISM Instance
 * @return ES value
 */
LOCAL_INLINE uint16_t ISM_HWA_GetEs(ISM_Type *const pIsm)
{
    return (uint16_t)((pIsm->E_STATUS & ISM_E_STATUS_ES_MASK) >> ISM_E_STATUS_ES_SHIFT);
}

/**
 * @brief Clear ES of ISM_E_STATUS register
 *
 * @param pIsm ISM Instance
 * @param u32Channels ECM channels
 */
LOCAL_INLINE void ISM_HWA_ClearEs(ISM_Type *const pIsm, uint32_t u32Channels)
{
    pIsm->E_STATUS = (u32Channels << ISM_E_STATUS_ES_SHIFT) & ISM_E_STATUS_ES_MASK;
}

/**
 * @brief Enable ISM ECM channels system event
 *
 * @param pIsm ISM Instance
 * @param u32Channels ECM Channels
 * @param bEnable enable value
 */
LOCAL_INLINE void ISM_HWA_EnableEcmSystemEvent(ISM_Type *const pIsm, uint32_t u32Channels, bool bEnable)
{
    if (bEnable)
    {
        pIsm->E_CTRL = pIsm->E_CTRL | (u32Channels << ISM_E_CTRL_ECE_SHIFT);
    }
    else
    {
        pIsm->E_CTRL = pIsm->E_CTRL & ~(u32Channels << ISM_E_CTRL_ECE_SHIFT);
    }
}

/**
 * @brief Get Enabled ISM ECM channels system event
 *
 * @param pIsm ISM Instance
 * @return Enabled ECM event
 */
LOCAL_INLINE uint8_t ISM_HWA_GetEnabledEcmSystemEvent(ISM_Type *const pIsm)
{
    return (uint8_t)((pIsm->E_CTRL & ISM_E_CTRL_ECE_MASK) >> ISM_E_CTRL_ECE_SHIFT);
}

/**
 * @brief Enable ISM LAM channels system event
 *
 * @param pIsm ISM Instance
 * @param u32Channels LAM Channels
 * @param bEnable enable value
 */
LOCAL_INLINE void ISM_HWA_EnableLamSystemEvent(ISM_Type *const pIsm, uint32_t u32Channels, bool bEnable)
{
    if (bEnable)
    {
        pIsm->E_CTRL = pIsm->E_CTRL | (u32Channels << ISM_E_CTRL_EE_SHIFT);
    }
    else
    {
        pIsm->E_CTRL = pIsm->E_CTRL & ~(u32Channels << ISM_E_CTRL_EE_SHIFT);
    }
}

/**
 * @brief Get Enabled ISM LAM channels system event
 *
 * @param pIsm ISM Instance
 * @return Enabled LAM event
 */
LOCAL_INLINE uint16_t ISM_HWA_GetEnabledLamSystemEvent(ISM_Type *const pIsm)
{
    return (uint16_t)((pIsm->E_CTRL & ISM_E_CTRL_EE_MASK) >> ISM_E_CTRL_EE_SHIFT);
}

/**
 * @brief Set the EC_CTRL register
 *
 * @param pIsm ISM Instance
 * @param u32Value register Value
 */
LOCAL_INLINE void ISM_HWA_SetEcCtrl(ISM_Type *const pIsm, uint32_t u32Value)
{
    pIsm->EC_CTRL = u32Value;
}

/**
 * @brief Set THRL and LAM channel of ECM0
 *
 * @param pIsm ISM Instance
 * @param u32Value THRL value
 * @param u32LamChannel Lam channel
 */
LOCAL_INLINE void ISM_HWA_SetEcm0EcCtrl(ISM_Type *const pIsm, uint32_t u32Value, uint32_t u32LamChannel)
{
    uint32_t u32TempValue = pIsm->EC_CTRL;

    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_SEL_0_MASK) | ISM_EC_CTRL_SEL_0(u32LamChannel);
    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_THRL_0_MASK) | ISM_EC_CTRL_THRL_0(u32Value);
    pIsm->EC_CTRL = u32TempValue;
}

/**
 * @brief Set THRL and LAM channel of ECM1
 *
 * @param pIsm ISM Instance
 * @param u32Value THRL value
 * @param u32LamChannel Lam channel
 */
LOCAL_INLINE void ISM_HWA_SetEcm1EcCtrl(ISM_Type *const pIsm, uint32_t u32Value, uint32_t u32LamChannel)
{
    uint32_t u32TempValue = pIsm->EC_CTRL;

    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_SEL_1_MASK) | ISM_EC_CTRL_SEL_1(u32LamChannel);
    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_THRL_1_MASK) | ISM_EC_CTRL_THRL_1(u32Value);
    pIsm->EC_CTRL = u32TempValue;
}

/**
 * @brief Set THRL and LAM channel of ECM2
 *
 * @param pIsm ISM Instance
 * @param u32Value THRL value
 * @param u32LamChannel Lam channel
 */
LOCAL_INLINE void ISM_HWA_SetEcm2EcCtrl(ISM_Type *const pIsm, uint32_t u32Value, uint32_t u32LamChannel)
{
    uint32_t u32TempValue = pIsm->EC_CTRL;

    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_SEL_2_MASK) | ISM_EC_CTRL_SEL_2(u32LamChannel);
    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_THRL_2_MASK) | ISM_EC_CTRL_THRL_2(u32Value);
    pIsm->EC_CTRL = u32TempValue;
}

/**
 * @brief Set THRL and LAM channel of ECM3
 *
 * @param pIsm ISM Instance
 * @param u32Value THRL value
 * @param u32LamChannel Lam channel
 */
LOCAL_INLINE void ISM_HWA_SetEcm3EcCtrl(ISM_Type *const pIsm, uint32_t u32Value, uint32_t u32LamChannel)
{
    uint32_t u32TempValue = pIsm->EC_CTRL;

    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_SEL_3_MASK) | ISM_EC_CTRL_SEL_3(u32LamChannel);
    u32TempValue  = (u32TempValue & ~ISM_EC_CTRL_THRL_3_MASK) | ISM_EC_CTRL_THRL_3(u32Value);
    pIsm->EC_CTRL = u32TempValue;
}

/**
 * @brief Get the RGD value of FPC_STATUS
 *
 * @param pFpc FPC Instance
 * @return RGD value
 */
LOCAL_INLINE bool ISM_HWA_GetFpcRgd(FPC_Type *const pFpc)
{
    return (pFpc->FPC_STATUS & ISM_FPC_STATUS_RGD_MASK) == ISM_FPC_STATUS_RGD_MASK ? true : false;
}

/**
 * @brief Clear the RGD value of FPC_STATUS
 *
 * @param pFpc FPC Instance
 */
LOCAL_INLINE void ISM_HWA_ClearFpcRgd(FPC_Type *const pFpc)
{
    pFpc->FPC_STATUS = ISM_FPC_STATUS_RGD_MASK;
}

/**
 * @brief Get the FGD value of FPC_STATUS
 *
 * @param pFpc FPC Instance
 * @return FGD value
 */
LOCAL_INLINE bool ISM_HWA_GetFpcFgd(FPC_Type *const pFpc)
{
    return (pFpc->FPC_STATUS & ISM_FPC_STATUS_FGD_MASK) == ISM_FPC_STATUS_FGD_MASK ? true : false;
}

/**
 * @brief Clear the FGD value of FPC_STATUS
 *
 * @param pFpc FPC Instance
 */
LOCAL_INLINE void ISM_HWA_ClearFpcFgd(FPC_Type *const pFpc)
{
    pFpc->FPC_STATUS = ISM_FPC_STATUS_FGD_MASK;
}

/**
 * @brief Set the EN of FPC_CTRL
 *
 * @param pFpc FPC Instance
 * @param bEnable EN value
 */
LOCAL_INLINE void ISM_HWA_SetFpcCtrlEn(FPC_Type *const pFpc, bool bEnable)
{
    pFpc->FPC_CTRL = (pFpc->FPC_CTRL & ~ISM_FPC_CTRL_EN_MASK) | ISM_FPC_CTRL_EN(bEnable);
}

/**
 * @brief Set the IEN of FPC_CTRL
 *
 * @param pFpc FPC Instance
 * @param bEnable IEN value
 */
LOCAL_INLINE void ISM_HWA_SetFpcCtrlIen(FPC_Type *const pFpc, bool bEnable)
{
    pFpc->FPC_CTRL = (pFpc->FPC_CTRL & ~ISM_FPC_CTRL_IEN_MASK) | ISM_FPC_CTRL_IEN(bEnable);
}

/**
 * @brief Get the IEN of FPC_CTRL
 *
 * @param pFpc FPC Instance
 * @return Interrupt enable bit
 */
LOCAL_INLINE bool ISM_HWA_GetFpcCtrlIen(FPC_Type *const pFpc)
{
    return (pFpc->FPC_CTRL & ISM_FPC_CTRL_IEN_MASK) == ISM_FPC_CTRL_IEN_MASK ? true : false;
}

/**
 * @brief Set the FEG of FPC_CONFIG
 *
 * @param pFpc FPC Instance
 * @param eMode FEG mode
 */
LOCAL_INLINE void ISM_HWA_SetFpcFallingDetectMode(FPC_Type *const pFpc, ISM_FPC_EdgeDetectModeType eMode)
{
    pFpc->FPC_CONFIG = (pFpc->FPC_CONFIG & ~ISM_FPC_CONFIG_FEG_MASK) | ISM_FPC_CONFIG_FEG(eMode);
}

/**
 * @brief Set the FED of FPC_CONFIG
 *
 * @param pFpc FPC Instance
 * @param eMode FED mode
 */
LOCAL_INLINE void ISM_HWA_SetFpcFallingDelayMode(FPC_Type *const pFpc, ISM_FPC_EdgeDelayModeType eMode)
{
    pFpc->FPC_CONFIG = (pFpc->FPC_CONFIG & ~ISM_FPC_CONFIG_FED_MASK) | ISM_FPC_CONFIG_FED(eMode);
}

/**
 * @brief Set the REG of FPC_CONFIG
 *
 * @param pFpc FPC Instance
 * @param eMode REG mode
 */
LOCAL_INLINE void ISM_HWA_SetFpcRisingDetectMode(FPC_Type *const pFpc, ISM_FPC_EdgeDetectModeType eMode)
{
    pFpc->FPC_CONFIG = (pFpc->FPC_CONFIG & ~ISM_FPC_CONFIG_REG_MASK) | ISM_FPC_CONFIG_REG(eMode);
}

/**
 * @brief Set the RED of FPC_CONFIG
 *
 * @param pFpc FPC Instance
 * @param eMode RED mode
 */
LOCAL_INLINE void ISM_HWA_SetFpcRisingDelayMode(FPC_Type *const pFpc, ISM_FPC_EdgeDelayModeType eMode)
{
    pFpc->FPC_CONFIG = (pFpc->FPC_CONFIG & ~ISM_FPC_CONFIG_RED_MASK) | ISM_FPC_CONFIG_RED(eMode);
}

/**
 * @brief Set the CMP of FPC_CONFIG
 *
 * @param pFpc FPC Instance
 * @param u32Value FPC threshold value that is compared with the 16-bit timer.
 */
LOCAL_INLINE void ISM_HWA_SetFpcConfigCmp(FPC_Type *const pFpc, uint32_t u32Value)
{
    pFpc->FPC_CONFIG = (pFpc->FPC_CONFIG & ~ISM_FPC_CONFIG_CMP_MASK) | ISM_FPC_CONFIG_CMP(u32Value);
}

/**
 * @brief Set the value of FPC_CONFIG
 *
 * @param pFpc FPC Instance
 * @param u32Value Register value
 */
LOCAL_INLINE void ISM_HWA_SetFpcConfig(FPC_Type *const pFpc, uint32_t u32Value)
{
    pFpc->FPC_CONFIG = u32Value;
}

/**
 * @brief Get the TIM of FPC_TIMER
 *
 * @param pFpc FPC Instance
 * @return TIM value
 */
LOCAL_INLINE uint16_t ISM_HWA_GetFpcTimer(FPC_Type *const pFpc)
{
    return (uint16_t)((pFpc->FPC_TIMER & ISM_FPC_TIMER_TIM_MASK) >> ISM_FPC_TIMER_TIM_SHIFT);
}

/**
 * @brief Clear the TIM of FPC_TIMER
 *
 * @param pFpc FPC Instance
 */
LOCAL_INLINE void ISM_HWA_ClearFpcTimer(FPC_Type *const pFpc)
{
    pFpc->FPC_TIMER = ISM_FPC_TIMER_TIM_MASK;
}

/**
 * @brief Get the COUNT of LAM_STATUS
 *
 * @param pLam LAM Instance
 * @return COUNT value
 */
LOCAL_INLINE uint32_t ISM_HWA_GetLamStatusCounter(LAM_Type *const pLam)
{
    return (pLam->LAM_STATUS & ISM_LAM_STATUS_COUNT_MASK) >> ISM_LAM_STATUS_COUNT_SHIFT;
}

/**
 * @brief Clear the COUNT of LAM_STATUS
 *
 * @param pLam LAM Instance
 */
LOCAL_INLINE void ISM_HWA_ClearLamStatusCounter(LAM_Type *const pLam)
{
    pLam->LAM_STATUS = ISM_LAM_STATUS_COUNT_MASK;
}

/**
 * @brief Get the OVFL of LAM_STATUS
 *
 * @param pLam LAM Instance
 * @return OVFL value
 */
LOCAL_INLINE bool ISM_HWA_GetLamStatusOvfl(LAM_Type *const pLam)
{
    return (pLam->LAM_STATUS & ISM_LAM_STATUS_OVFL_MASK) == ISM_LAM_STATUS_OVFL_MASK ? true : false;
}

/**
 * @brief Clear the OVFL of LAM_STATUS
 *
 * @param pLam LAM Instance
 */
LOCAL_INLINE void ISM_HWA_ClearLamStatusOvfl(LAM_Type *const pLam)
{
    pLam->LAM_STATUS = ISM_LAM_STATUS_OVFL_MASK;
}

/**
 * @brief Set the IEN of LAM_CTRL
 *
 * @param pLam LAM Instance
 * @param bEnable IEN value, LAM Channel Overflow Interrupt Enable
 */
LOCAL_INLINE void ISM_HWA_SetLamCtrIen(LAM_Type *const pLam, bool bEnable)
{
    pLam->LAM_CTRL = (pLam->LAM_CTRL & ~ISM_LAM_CTRL_IEN_MASK) | ISM_LAM_CTRL_IEN(bEnable);
}

/**
 * @brief Get the IEN of LAM_CTRL
 *
 * @param pLam LAM Instance
 * @return LAM Channel Overflow Interrupt Enable bit
 */
LOCAL_INLINE bool ISM_HWA_GetLamCtrIen(LAM_Type *const pLam)
{
    return (pLam->LAM_CTRL & ISM_LAM_CTRL_IEN_MASK) == ISM_LAM_CTRL_IEN_MASK ? true : false;
}

/**
 * @brief Set the EN of LAM_CTRL
 *
 * @param pLam LAM Instance
 * @param bEnable EN value, LAM Channel Enable
 */
LOCAL_INLINE void ISM_HWA_SetLamCtrEn(LAM_Type *const pLam, bool bEnable)
{
    pLam->LAM_CTRL = (pLam->LAM_CTRL & ~ISM_LAM_CTRL_EN_MASK) | ISM_LAM_CTRL_EN(bEnable);
}

/**
 * @brief Set the value of LAM_CONFIG
 *
 * @param pLam LAM Instance
 * @param u32Value Reigster value
 */
LOCAL_INLINE void ISM_HWA_SetLamConfig(LAM_Type *const pLam, uint32_t u32Value)
{
    pLam->LAM_CONFIG = u32Value;
}

/**
 * @brief Set the value of LAM_COUNTER
 *
 * @param pLam LAM Instance
 * @param u32Value Reigster value
 */
LOCAL_INLINE void ISM_HWA_SetLamCounter(LAM_Type *const pLam, uint32_t u32Value)
{
    pLam->LAM_COUNTER = u32Value;
}

/**
 * @brief Get the FPC instance.
 * @param pIsm ISM Instance
 * @param u8FpcIndex FPC index
 * @return FPC Instance
 */
LOCAL_INLINE FPC_Type *ISM_HWA_GetFpc(ISM_Type *const pIsm, uint8_t u8FpcIndex)
{
    return (FPC_Type *)((uint32_t) & (pIsm->FPC_STATUS0) + (uint32_t)u8FpcIndex * 0x10U);
}

/**
 * @brief Get the LAM instance.
 * @param pIsm ISM Instance
 * @param u8LamIndex LAM index
 * @return LAM Instance
 */
LOCAL_INLINE LAM_Type *ISM_HWA_GetLam(ISM_Type *const pIsm, uint8_t u8LamIndex)
{
    return (LAM_Type *)((uint32_t) & (pIsm->LAM_STATUS0) + (uint32_t)u8LamIndex * 0x10U);
}

/** @}*/ /* HwA_ism */

#endif

#endif /* #ifndef _HWA_ISM_H_ */
