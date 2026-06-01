/**
 * @file module_driver_trgsel.c
 * @author Flagchip103
 * @brief TRGSEL driver source code
 * @version 2.0.0
 * @date 2024-07-26
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip103   N/A          First version
*********************************************************************************/

#include "module_driver_trgsel.h"

#if TRGSEL_INSTANCE_COUNT > 0U

#if TRGSEL_DEV_ERROR_REPORT == STD_ON
#define TRGSEL_ReportDevError(func, error) ReportDevError(TRGSEL_MODULE_ID, func, error)
#endif

#include "HwA_trgsel.h"
#include "HwA_smisc.h"

#define TRGSEL_NUM_SW_TRG_CHANNELS     8U

static TRGSEL_Type *const s_trgselBase[TRGSEL_INSTANCE_COUNT] = TRGSEL_BASE_PTRS;

#ifndef NDEBUG
#if TRGSEL_DEV_ERROR_REPORT == STD_ON
/**
 * @brief Check whether the TRGSEL target is valid for the TRGSEL instance
 *
 * @param eInstance the selected TRGSEL instance
 * @param eTarget the target value to check
 * @return true the TRGSEL target is valid
 * @return false the TRGSEL target is invalid
 */
static inline bool TRGSEL_IsValidTarget(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget);

/**
 * @brief Check whether the TRGSEL source is valid for the TRGSEL instance
 *
 * @param eInstance the selected TRGSEL instance
 * @param eSource the source value to check
 * @return true the TRGSEL source is valid
 * @return false the TRGSEL source is invalid
 */
static inline bool TRGSEL_IsValidSource(const TRGSEL_InstanceType eInstance, const TRGSEL_SourceType eSource);

static inline bool TRGSEL_IsValidTarget(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
    bool bRet = false;
    switch (eInstance)
    {
        case TRGSEL_INSTANCE_0:
        {
            bRet = (bool)((eTarget < TRGSEL0_NUM_OUTPUTS) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_1:
        {
            bRet = (bool)((eTarget < TRGSEL1_NUM_OUTPUTS) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_2:
        {
            bRet = (bool)((eTarget < TRGSEL2_NUM_OUTPUTS) ? true : false);
            break;
        }
    
        case TRGSEL_INSTANCE_3:
        {
            bRet = (bool)((eTarget < TRGSEL3_NUM_OUTPUTS) ? true : false);
            break;
        }

        default:
            break;
    }
    return bRet;
}

static inline bool TRGSEL_IsValidSource(const TRGSEL_InstanceType eInstance, const TRGSEL_SourceType eSource)
{
    bool bRet = false;
    switch (eInstance)
    {
        case TRGSEL_INSTANCE_0:
        {
            bRet = (bool)((eSource < TRGSEL0_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_1:
        {
            bRet = (bool)((eSource < TRGSEL1_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_2:
        {
            bRet = (bool)((eSource < TRGSEL2_NUM_SOURCES) ? true : false);
            break;
        }

        case TRGSEL_INSTANCE_3:
        {
            bRet = (bool)((eSource < TRGSEL3_NUM_SOURCES) ? true : false);
            break;
        }

        default:
            break;
    }
    return bRet;
}
#endif
#endif

TRGSEL_SourceType TRGSEL_GetTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
#if TRGSEL_DEV_ERROR_REPORT == STD_ON
	if(eInstance >= TRGSEL_INSTANCE_COUNT)
	{
		TRGSEL_ReportDevError(TRGSEL_GET_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_PARAM_INSTANCE_NUMBER);
	}
	else if(false == TRGSEL_IsValidTarget(eInstance, eTarget))
	{
		TRGSEL_ReportDevError(TRGSEL_GET_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_INVALID_TARGET);
	}
#endif
    const TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    uint32_t u32Tmp = TRGSEL_HWA_GetTargetTriggerSource(pTrgsel, eTarget);

    return (TRGSEL_SourceType)u32Tmp;
}

void TRGSEL_SetTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget,
                                   const TRGSEL_SourceType eSource)
{
#if TRGSEL_DEV_ERROR_REPORT == STD_ON
	if(eInstance >= TRGSEL_INSTANCE_COUNT)
	{
		TRGSEL_ReportDevError(TRGSEL_SET_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_PARAM_INSTANCE_NUMBER);
	}
	else if(false == TRGSEL_IsValidTarget(eInstance, eTarget))
	{
		TRGSEL_ReportDevError(TRGSEL_SET_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_INVALID_TARGET);
	}
	else if(false == TRGSEL_IsValidSource(eInstance, eSource))
	{
		TRGSEL_ReportDevError(TRGSEL_SET_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_INVALID_SOURCE);
	}
	else if(true == TRGSEL_GetTargetLockStatus(eInstance, eTarget))
	{
		TRGSEL_ReportDevError(TRGSEL_SET_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_TARGET_LOCKED);
	}
#endif
    TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    TRGSEL_HWA_SetTargetTriggerSource(pTrgsel, eTarget, eSource);
}

bool TRGSEL_GetTargetLockStatus(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
#if TRGSEL_DEV_ERROR_REPORT == STD_ON
	if(eInstance >= TRGSEL_INSTANCE_COUNT)
	{
		TRGSEL_ReportDevError(TRGSEL_GET_TARGET_LOCK_STATUS_ID,TRGSEL_E_PARAM_INSTANCE_NUMBER);
	}
	else if(false == TRGSEL_IsValidTarget(eInstance, eTarget))
	{
		TRGSEL_ReportDevError(TRGSEL_GET_TARGET_LOCK_STATUS_ID,TRGSEL_E_INVALID_TARGET);
	}
#endif
    const TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    return TRGSEL_HWA_GetTargetLockStatus(pTrgsel, eTarget);
}

void TRGSEL_LockTargetTriggerSource(const TRGSEL_InstanceType eInstance, const TRGSEL_TargetType eTarget)
{
#if TRGSEL_DEV_ERROR_REPORT == STD_ON
	if(eInstance >= TRGSEL_INSTANCE_COUNT)
	{
		TRGSEL_ReportDevError(TRGSEL_LOCK_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_PARAM_INSTANCE_NUMBER);
	}
	else if(false == TRGSEL_IsValidTarget(eInstance, eTarget))
	{
		TRGSEL_ReportDevError(TRGSEL_LOCK_TARGET_TRIGGER_SOURCE_ID,TRGSEL_E_INVALID_TARGET);
	}
#endif
    TRGSEL_Type *const pTrgsel = s_trgselBase[eInstance];

    if (TRGSEL_GetTargetLockStatus(eInstance, eTarget) != true)
    {
        TRGSEL_HWA_LockTargetTriggerSource(pTrgsel, eTarget);
    }
}

void TRGSEL_GenerateSwTrigger(const TRGSEL_SwTriggerChannelType eChannel)
{
#if TRGSEL_DEV_ERROR_REPORT == STD_ON
	if(eChannel >= TRGSEL_NUM_SW_TRG_CHANNELS)
	{
		TRGSEL_ReportDevError(TRGSEL_GENERATE_SW_TRIGGER_ID,TRGSEL_E_INVALID_SW_TRIGGIER);
	}
#endif
    SMISC_HWA_GenerateSwTrigger(eChannel);
}

#endif
