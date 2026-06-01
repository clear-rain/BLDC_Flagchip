/**
 * @file HwA_lu.h
 * @author Flagchip032
 * @brief LU hardware access layer
 * @version 2.0.0
 * @date 2024-11-10
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip032   N/A          First version
*********************************************************************************/

#ifndef _HWA_LU_H_
#define _HWA_LU_H_

#include "device_header.h"

#if LU_INSTANCE_COUNT > 0U



/**
 * @defgroup HwA_lu HwA_lu
 * @ingroup module_driver_lu
 * @{
 */

/**
 * @brief Enumerates the LG instances available in the LU module.
 */
typedef enum
{
    LU_LG_0 = 0U, /**< LG instance 0 */
    LU_LG_1,      /**< LG instance 1 */
    LU_LG_2,      /**< LG instance 2 */
    LU_LG_3       /**< LG instance 3 */
} LU_LgType;

/**
 * @brief Enumerates the AOI bypass modes available in the LU module.
 */
typedef enum
{
    LU_NO_BYPASS = 0U, /**< No bypass mode */
    LU_AOI0_BYPASS,    /**< AOI0 bypass mode */
    LU_AOI1_BYPASS,    /**< AOI1 bypass mode */
    LU_AOI0_AOI1_BYPASS /**< Both AOI0 and AOI1 bypass mode */
} LU_BypassModeType;

/**
 * @brief Enumerates the flip-flop modes available in the LU module.
 */
typedef enum
{
    LU_BYPASS_MODE0 = 0U, /**< Bypass mode 0 */
    LU_RS_MODE,            /**< RS mode */
    LU_TFF_MODE,           /**< T flip-flop mode */
    LU_DFF_MODE,           /**< D flip-flop mode */
    LU_JKFF_MODE,          /**< JK flip-flop mode */
    LU_LATCH_MODE          /**< Latch mode */
} LU_ConfigModeType;

/**
 * @brief Enumerates the input types available in the LU module.
 */
typedef enum
{
    LU_INPUT_N_A = 0U, /**< Input A */
    LU_INPUT_N_B,      /**< Input B */
    LU_INPUT_N_C,      /**< Input C */
    LU_INPUT_N_D       /**< Input D */
} LU_InputNType;


/**
 * @brief Configures the AOI0 register of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32RegValue The value to write to the AOI0 register.
 */
LOCAL_INLINE void LU_HWA_ConfigAOI0(LU_Type* const pLu,LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].AOI_0 = u32RegValue;
}

/**
 * @brief Configures the AOI1 register of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32RegValue The value to write to the AOI1 register.
 */
LOCAL_INLINE void LU_HWA_ConfigAOI1(LU_Type* const pLu,LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].AOI_1 = u32RegValue;
}

/**
 * @brief Configures the CTRL register of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32RegValue The value to write to the CTRL register.
 */LOCAL_INLINE void LU_HWA_ConfigCtrl(LU_Type* const pLu,LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].CTRL = u32RegValue;
}

/**
 * @brief Configures the FILT register of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32RegValue The value to write to the FILT register.
 */
LOCAL_INLINE void LU_HWA_ConfigFilter(LU_Type* const pLu,LU_LgType eLg, uint32_t u32RegValue)
{
    pLu->LG[eLg].FILT = u32RegValue;
}

/**
 * @brief Sets the bypass control mode for a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param eMode The bypass control mode to set.
 */
LOCAL_INLINE void LU_HWA_SetLgBypassControl(LU_Type* const pLu,LU_LgType eLg, LU_BypassModeType eMode)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_BYPASS_MASK) | LU_CTRL_BYPASS(eMode));
}

/**
 * @brief Sets the flip-flop mode for a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param eMode The flip-flop mode to set.
 */LOCAL_INLINE void LU_HWA_SetLgFlipFlopMode(LU_Type* const pLu,LU_LgType eLg, LU_ConfigModeType eMode)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_MOD_MASK) | LU_CTRL_MOD(eMode));
}


/**
 * @brief Sets the inputs synchronous control for a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32Value The value to set for the inputs synchronous control.
 */LOCAL_INLINE void LU_HWA_SetLgInputsSyncCtrl(LU_Type* const pLu,LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_SYNC_MASK) | LU_CTRL_SYNC(u32Value));
}

/**
 * @brief Sets the output feedback override control for a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param eInput The feedback input to set.
 */
LOCAL_INLINE void LU_HWA_SetLgFeedbackOverrideCtrl(LU_Type* const pLu,LU_LgType eLg, LU_InputNType eInput)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].CTRL;
    pLu->LG[eLg].CTRL = ((u32TempRegValue & ~(uint32_t)LU_CTRL_FB_OVRD_MASK) | LU_CTRL_FB_OVRD(eInput));
}

/**
 * @brief Configures the flip-flop output to "1" for a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 */

LOCAL_INLINE void LU_HWA_ConfigFlipFlopTo1(LU_Type* const pLu,LU_LgType eLg)
{
    pLu->LG[eLg].CTRL |= (uint32_t)LU_CTRL_FF_INIT_MASK;
}

/**
 * @brief Enables the control flip-flop initialization output for a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 */
LOCAL_INLINE void LU_HWA_EnableControlFlipFlopInitOutput(LU_Type* const pLu,LU_LgType eLg)
{
    pLu->LG[eLg].CTRL |= (uint32_t)LU_CTRL_INIT_EN_MASK;
}

/**
 * @brief Sets the input filter sample count for AOI0 of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32Value The sample count value to set.
 */
LOCAL_INLINE void LU_HWA_SetAOI0InputFilterSampleCount(LU_Type* const pLu,LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_CNT0_MASK) | LU_FILT_CNT0(u32Value));
}

/**
 * @brief Sets the input filter sample period for AOI0 of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32Value The sample period value to set.
 */
LOCAL_INLINE void LU_HWA_SetAOI0InputFilterSamplePeriod(LU_Type* const pLu,LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_PRE0_MASK) | LU_FILT_PRE0(u32Value));
}

/**
 * @brief Sets the input filter sample count for AOI1 of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32Value The sample count value to set.
 */
LOCAL_INLINE void LU_HWA_SetAOI1InputFilterSampleCount(LU_Type* const pLu,LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_CNT1_MASK) | LU_FILT_CNT1(u32Value));
}

/**
 * @brief Sets the input filter sample period for AOI1 of a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 * @param u32Value The sample period value to set.
 */
LOCAL_INLINE void LU_HWA_SetAOI1InputFilterSamplePeriod(LU_Type* const pLu,LU_LgType eLg, uint32_t u32Value)
{
    uint32_t u32TempRegValue = pLu->LG[eLg].FILT;
    pLu->LG[eLg].FILT = ((u32TempRegValue & ~(uint32_t)LU_FILT_PRE1_MASK) | LU_FILT_PRE1(u32Value));
}

/**
 * @brief Configures the flip-flop output to "0" for a specific LG instance.
 *
 * @param pLu Pointer to the LU module instance.
 * @param eLg The LG instance to configure.
 */
LOCAL_INLINE void LU_HWA_ConfigFlipFlopTo0(LU_Type* const pLu,LU_LgType eLg)
{
    pLu->LG[eLg].CTRL &= ~(uint32_t)LU_CTRL_FF_INIT_MASK;
}
/**
 * @}
 */

#endif


#endif /* #ifndef _HWA_LU_H_ */
