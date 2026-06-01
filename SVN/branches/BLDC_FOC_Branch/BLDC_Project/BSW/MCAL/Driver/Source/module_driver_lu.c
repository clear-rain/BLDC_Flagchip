/**
 * @file module_driver_lu.c
 * @author Flagchip032
 * @brief LU driver source code
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

#include "module_driver_lu.h"

#if LU_INSTANCE_COUNT > 0U

static LU_Type *const p_LUTables[LU_INSTANCE_COUNT] = LU_BASE_PTRS;

#ifndef LU_DEV_ERROR_REPORT
    #define LU_DEV_ERROR_REPORT    STD_OFF
#endif

#if LU_DEV_ERROR_REPORT == STD_ON
    #define LU_ReportDevError(func, error)     ReportDevError(LU_MODULE_ID, func, error)
#endif

/**
 * @brief Initialize Lu instance
 *
 * @param pInitStruct Lu initialization structure
 *
 * @return LU return type
 */
LU_StatusType LU_Init(LU_InstanceType eInstance,const LU_InitType *const pInitStruct)
{
    LU_StatusType eRet = LU_STATUS_SUCCESS;
#if LU_DEV_ERROR_REPORT == STD_ON

    if (eInstance >= LU_INSTANCE_COUNT)
    {
        LU_ReportDevError(LU_INIT_ID, LU_E_PARAM_INSTANCE);
    }
    else if (pInitStruct == NULL)
    {
        LU_ReportDevError(LU_INIT_ID, LU_E_PARAM_NULLPTR);
     }
    else
    {
    #endif
    LU_Type *const p_LU=p_LUTables[eInstance];
    uint32_t u32TempReg = 0U, u32TempCfg = 0U;
    if (NULL == pInitStruct)
    {
        eRet = LU_STATUS_PARAM_INVALID;
    }
    else
    {
        /* set AOI0 value */
        LU_HWA_ConfigAOI0(p_LU,pInitStruct->eLgNum, 0U);
        /* set AOI1 value */
        LU_HWA_ConfigAOI1(p_LU,pInitStruct->eLgNum, 0U);
        /* set CTRL value */
        LU_HWA_ConfigCtrl(p_LU,pInitStruct->eLgNum, 0U);
        /* set FILT value */
        LU_HWA_ConfigFilter(p_LU,pInitStruct->eLgNum, 0U);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn0Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn0Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn0Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn0Config.eInNDCfg);
        u32TempReg = (uint32_t)0U | LU_AOI_IN_N_CFG(LU_AOI_IN_0, u32TempCfg);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn1Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn1Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn1Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn1Config.eInNDCfg);
        u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_1, u32TempCfg);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn2Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn2Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn2Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn2Config.eInNDCfg);
        u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_2, u32TempCfg);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi0Config.tIn3Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi0Config.tIn3Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi0Config.tIn3Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi0Config.tIn3Config.eInNDCfg);
        u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_3, u32TempCfg);
        /* set AOI0 value */
        LU_HWA_ConfigAOI0(p_LU,pInitStruct->eLgNum, u32TempReg);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn0Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn0Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn0Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn0Config.eInNDCfg);
        u32TempReg = (uint32_t)0U | LU_AOI_IN_N_CFG(LU_AOI_IN_0, u32TempCfg);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn1Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn1Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn1Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn1Config.eInNDCfg);
        u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_1, u32TempCfg);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn2Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn2Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn2Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn2Config.eInNDCfg);
        u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_2, u32TempCfg);

        u32TempCfg = (uint32_t)0U |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_A, pInitStruct->tAoi1Config.tIn3Config.eInNACfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_B, pInitStruct->tAoi1Config.tIn3Config.eInNBCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_C, pInitStruct->tAoi1Config.tIn3Config.eInNCCfg) |
                     LU_AOI_IN_CFG(LU_AOI_IN_N_D, pInitStruct->tAoi1Config.tIn3Config.eInNDCfg);
        u32TempReg |= LU_AOI_IN_N_CFG(LU_AOI_IN_3, u32TempCfg);
        /* set AOI1 value */
        LU_HWA_ConfigAOI1(p_LU,pInitStruct->eLgNum, u32TempReg);

        /* force bypass mode */
        LU_HWA_SetLgBypassControl(p_LU,pInitStruct->eLgNum, pInitStruct->eAoiMode);
        /* set Flip-Flop mode configure */
        LU_HWA_SetLgFlipFlopMode(p_LU,pInitStruct->eLgNum, pInitStruct->eFFMode);
        u32TempCfg = 0U;
        if (pInitStruct->tSyncCtrl.bInputNA)
        {
            u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(LU_INPUT_N_A, 1U);
        }
        if (pInitStruct->tSyncCtrl.bInputNB)
        {
            u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(LU_INPUT_N_B, 1U);
        }
        if (pInitStruct->tSyncCtrl.bInputNC)
        {
            u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(LU_INPUT_N_C, 1U);
        }
        if (pInitStruct->tSyncCtrl.bInputND)
        {
            u32TempCfg |= LU_SYNC_CONTROL_INPUT_N(LU_INPUT_N_D, 1U);
        }
        /* set LG inputs synchronous control */
        LU_HWA_SetLgInputsSyncCtrl(p_LU,pInitStruct->eLgNum, u32TempCfg);

        if (LU_JKFF_MODE == pInitStruct->eFFMode)
        {
            /* set LG output feedback override control */
            LU_HWA_SetLgFeedbackOverrideCtrl(p_LU,pInitStruct->eLgNum, pInitStruct->eFbMode);
        }

        if (LU_OUTPUT_INIT_DISABLE > pInitStruct->eFFInitValue)
        {
            if (LU_OUTPUT_INIT_ONE == pInitStruct->eFFInitValue)
            {
                /* Configure the output of flip-flop as "1" */
                LU_HWA_ConfigFlipFlopTo1(p_LU,pInitStruct->eLgNum);
            }
            else
            {
                /* Configure the output of flip-flop as "0" */
                LU_HWA_ConfigFlipFlopTo0(p_LU,pInitStruct->eLgNum);
            }
            /* Flip-Flop initial output enable control */
            LU_HWA_EnableControlFlipFlopInitOutput(p_LU,pInitStruct->eLgNum);
        }

        /* set input filter sample count for AOI0 */
        LU_HWA_SetAOI0InputFilterSampleCount(p_LU,pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi0FiltCnt);
        /* set input filter sample period for AOI0 */
        LU_HWA_SetAOI0InputFilterSamplePeriod(p_LU,pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi0Period);
        /* set input filter sample count for AOI1 */
        LU_HWA_SetAOI1InputFilterSampleCount(p_LU,pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi1FiltCnt);
        /* set input filter sample period for AOI0 */
        LU_HWA_SetAOI1InputFilterSamplePeriod(p_LU,pInitStruct->eLgNum, (uint32_t)pInitStruct->u8Aoi1Period);
    }
#if LU_DEV_ERROR_REPORT == STD_ON
}
#endif
    return eRet;
}

/**
 * @brief De-initialize Lu instance
 * @param pInitStruct Lu initialization structure
 *
 */
void LU_Deinit(LU_InstanceType eInstance)
{
#if LU_DEV_ERROR_REPORT == STD_ON
    if (eInstance >= LU_INSTANCE_COUNT)
    {
        LU_ReportDevError(LU_DEINIT_ID, LU_E_PARAM_INSTANCE);
    }
    else
    {
#endif
    LU_Type *const p_LU=p_LUTables[eInstance] ;
    uint8_t u8Index = 0U;
    for (u8Index = 0U; u8Index < (uint8_t)LG_CNT; u8Index++)
    {
        /* set AOI0 value */
        LU_HWA_ConfigAOI0(p_LU,(LU_LgType)u8Index, 0U);
        /* set AOI1 value */
        LU_HWA_ConfigAOI1(p_LU,(LU_LgType)u8Index, 0U);
        /* set CTRL value */
        LU_HWA_ConfigCtrl(p_LU,(LU_LgType)u8Index, 0U);
        /* set FILT value */
        LU_HWA_ConfigFilter(p_LU,(LU_LgType)u8Index, 0U);
    }
#if LU_DEV_ERROR_REPORT == STD_ON
}
    #endif
}
#endif
