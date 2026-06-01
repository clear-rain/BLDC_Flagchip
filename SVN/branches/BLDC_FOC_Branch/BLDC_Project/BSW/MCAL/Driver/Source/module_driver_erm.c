/**
 * @file module_driver_erm.c
 * @author Flagchip
 * @brief EIM driver source code
 * @version 2.0.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/**********************************************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip102   N/A          First version
*******************************************************************************************************/

#include "module_driver_erm.h"

#if ERM_INSTANCE_COUNT > 0U


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef ERM_DEV_ERROR_REPORT
#define ERM_DEV_ERROR_REPORT    STD_OFF
#endif

#if ERM_DEV_ERROR_REPORT == STD_ON
#define ERM_ReportDevError(func, error)     ReportDevError(ERM_MODULE_ID, func, error)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static uint32_t ERM_ReadAddress(ERM_HandleType *const pHandle, ERM_channelType eChannel);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static ERM_Type *const s_apErmBase[ERM_INSTANCE_COUNT] = ERM_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Populates the ERM configuration structure with default values
 *
 * This function initializes a given ERM configuration structure with default settings for
 * various error detection and correction configurations. If the provided pointer is `NULL`,
 * an error report will be generated when error reporting is enabled.
 *
 * @param pInitCfg Pointer to an ERM configuration structure to be populated with default values
 *
 * @note Error reporting is enabled when `ERM_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void ERM_GetDefaultConfig(ERM_CfgType *const pInitCfg)
{
#if ERM_DEV_ERROR_REPORT == STD_ON
    if (pInitCfg == NULL)
    {
        ERM_ReportDevError(ERM_GET_DEFAULT_CONFIG_ID, ERM_E_PARAM_NULLPTR);
    }
    else
#endif
    {
        pInitCfg->tCTCMCfg.bEnable = true;
        pInitCfg->tCTCMCfg.u8IntType = ERM_NON_CORRECTABLE_IRQ | ERM_SINGLE_CORRECTION_IRQ;

        pInitCfg->tDTCMCfg.bEnable = true;
        pInitCfg->tDTCMCfg.u8IntType = ERM_NON_CORRECTABLE_IRQ | ERM_SINGLE_CORRECTION_IRQ;

        pInitCfg->tPFLASHfg.bEnable = true;
        pInitCfg->tPFLASHfg.u8IntType = ERM_NON_CORRECTABLE_IRQ | ERM_SINGLE_CORRECTION_IRQ;

        pInitCfg->tDMACfg.bEnable = true;
        pInitCfg->tDMACfg.u8IntType = ERM_NON_CORRECTABLE_IRQ | ERM_SINGLE_CORRECTION_IRQ;

#if (ERM_DFLASH_SUPPORT == STD_ON)
        pInitCfg->tDFLASHCfg.bEnable = true;
        pInitCfg->tDFLASHCfg.u8IntType = ERM_NON_CORRECTABLE_IRQ | ERM_SINGLE_CORRECTION_IRQ;
#endif
    }
}

/**
 * @brief Initializes the Error Reporting Module (ERM) for the specified instance
 *
 * This function initializes the ERM module with the provided configuration structure.
 * It performs parameter validation, sets up the control register based on the configuration,
 * and clears the status. If an error occurs or the handle is invalid, an error report will
 * be generated, and the function will return a failure status.
 *
 * @param pHandle Pointer to an ERM handle structure containing the instance information
 * @param pInitCfg Pointer to an ERM configuration structure with desired settings
 *
 * @return Status of the initialization operation
 *         - ERM_STATUS_SUCCESS: Initialization successful
 *         - ERM_STATUS_FAIL: Initialization failed due to an error
 *
 * @note Error reporting is enabled when `ERM_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
ERM_StatusType ERM_Init(ERM_HandleType *const pHandle, const ERM_CfgType *const pInitCfg)
{
    ERM_StatusType eStatus = ERM_STATUS_SUCCESS;
#if ERM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        ERM_ReportDevError(ERM_INIT_ID, ERM_E_PARAM_NULLPTR);
        eStatus = ERM_STATUS_FAIL;
    }
    else if (pInitCfg == NULL)
    {
        ERM_ReportDevError(ERM_INIT_ID, ERM_E_PARAM_NULLPTR);
        eStatus = ERM_STATUS_FAIL;
    }
    else if (pHandle->eInstance >= ERM_INSTANCE_COUNT)
    {
        ERM_ReportDevError(ERM_INIT_ID, ERM_E_PARAM_INSTANCE);
        eStatus = ERM_STATUS_FAIL;
    }
    else
#endif
    {
        uint32_t u32ErmCr0Val = 0x0U;
        ERM_Type *const pErm = s_apErmBase[pHandle->eInstance];

        if (pInitCfg->tCTCMCfg.bEnable == TRUE)
        {
            u32ErmCr0Val |= ((uint32_t)(pInitCfg->tCTCMCfg.u8IntType) << ERM_SR0_NCE0_SHIFT);
        }

        if (pInitCfg->tDTCMCfg.bEnable == TRUE)
        {
            u32ErmCr0Val |= ((uint32_t)(pInitCfg->tDTCMCfg.u8IntType) << ERM_SR0_NCE1_SHIFT);
        }

        if (pInitCfg->tPFLASHfg.bEnable == TRUE)
        {
            u32ErmCr0Val |= ((uint32_t)(pInitCfg->tPFLASHfg.u8IntType) << ERM_SR0_NCE2_SHIFT);
        }

#if (ERM_DFLASH_SUPPORT == STD_ON)
        if (pInitCfg->tDFLASHCfg.bEnable == TRUE)
        {
            u32ErmCr0Val |= ((uint32_t)(pInitCfg->tDFLASHCfg.u8IntType) << ERM_SR0_NCE3_SHIFT);
        }
#endif
        if (pInitCfg->tDMACfg.bEnable == TRUE)
        {
            u32ErmCr0Val |= ((uint32_t)(pInitCfg->tDMACfg.u8IntType) << ERM_SR0_NCE4_SHIFT);
        }

        ERM_ClearStatus(pHandle);
        ERM_HWA_SetCR0Register(pErm, u32ErmCr0Val);
    }

    return eStatus;
}

/**
 * @brief Clears the Error Reporting Module (ERM) status flags
 *
 * This function clears all status flags in the ERM module associated with the given handle's
 * instance. If an error occurs or the handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to an ERM handle structure containing the instance information
 *
 * @note Error reporting is enabled when `ERM_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
void ERM_ClearStatus(ERM_HandleType *const pHandle)
{
    ERM_Type *const pErm = s_apErmBase[pHandle->eInstance];

    ERM_HWA_SetSR0(pErm, ERM_SR0_ALLFLAG_MASK);
}

/**
 * @brief Reads the error address from the specified Error Reporting Module (ERM) channel
 *
 * This function retrieves the error address associated with the given ERM channel.
 * If an error occurs or the handle is invalid, an error report will be generated.
 *
 * @param pHandle Pointer to an ERM handle structure containing the instance information
 * @param eChannel Enumerated type specifying the ERM channel to read the address from
 *
 * @return Error address from the specified ERM channel
 *
 * @note Error reporting is enabled when `ERM_DEV_ERROR_REPORT` is set to `STD_ON`.
 */
static uint32_t ERM_ReadAddress(ERM_HandleType *const pHandle, ERM_channelType eChannel)
{
    uint32_t u32Address = 0U;
    ERM_Type *const pErm = s_apErmBase[pHandle->eInstance];

    u32Address = ERM_HWA_GetEARn(pErm, eChannel);

   	return u32Address;
}

/**
 * @brief Handles common Error Reporting Module (ERM) interrupts and invokes error callbacks
 *
 * This function serves as the common interrupt handler for the ERM, checking for errors in various channels
 * (CTCM, DTCM, PFLASH, optionally DFLASH, and DMA) and invoking the error callback function when an error
 * is detected. It also clears the status flags after processing the interrupts.
 *
 * @param pHandle Pointer to an ERM handle structure containing the instance information and error callback
 *
 * @note This function is designed to be used within an interrupt context.
 * @note Support for DFLASH depends on the compile-time configuration `ERM_DFLASH_SUPPORT`.
 */
void ERM_CommonIRQHandler(ERM_HandleType *const pHandle)
{
    ERM_channelType eChannel = ERM_CTCM;
    uint8_t u8ErrorType = 0;

    if (0U != (ERM->SR0 & (ERM_SR0_SBC0_MASK | ERM_SR0_NCE0_MASK)))
    {
        eChannel = ERM_CTCM;
        u8ErrorType = (uint8_t)((ERM->SR0 & (ERM_SR0_SBC0_MASK | ERM_SR0_NCE0_MASK)) >> ERM_SR0_NCE0_SHIFT);
        if (NULL != pHandle->tSettings.pErrorCallback)
        {
            pHandle->tSettings.pErrorCallback(pHandle, eChannel, u8ErrorType, ERM_ReadAddress(pHandle, eChannel));
        }
    }

    if (0U != (ERM->SR0 & (ERM_SR0_SBC1_MASK | ERM_SR0_NCE1_MASK)))
    {
        eChannel = ERM_DTCM;
        u8ErrorType = (uint8_t)((ERM->SR0 & (ERM_SR0_SBC1_MASK | ERM_SR0_NCE1_MASK)) >> ERM_SR0_NCE1_SHIFT);
        if (NULL != pHandle->tSettings.pErrorCallback)
        {
            pHandle->tSettings.pErrorCallback(pHandle, eChannel, u8ErrorType, ERM_ReadAddress(pHandle, eChannel));
        }
    }

    if (0U != (ERM->SR0 & (ERM_SR0_SBC2_MASK | ERM_SR0_NCE2_MASK)))
    {
        eChannel = ERM_PFLASH;
        u8ErrorType = (uint8_t)((ERM->SR0 & (ERM_SR0_SBC2_MASK | ERM_SR0_NCE2_MASK)) >> ERM_SR0_NCE2_SHIFT);
        if (NULL != pHandle->tSettings.pErrorCallback)
        {
            pHandle->tSettings.pErrorCallback(pHandle, eChannel, u8ErrorType, ERM_ReadAddress(pHandle, eChannel));
        }
    }

#if (ERM_DFLASH_SUPPORT == STD_ON)
    if (0U != (ERM->SR0 & (ERM_SR0_SBC3_MASK | ERM_SR0_NCE3_MASK)))
    {
        eChannel = ERM_DFLASH;
        u8ErrorType = (uint8_t)((ERM->SR0 & (ERM_SR0_SBC3_MASK | ERM_SR0_NCE3_MASK)) >> ERM_SR0_NCE3_SHIFT);
        if (NULL != pHandle->tSettings.pErrorCallback)
        {
            pHandle->tSettings.pErrorCallback(pHandle, eChannel, u8ErrorType, ERM_ReadAddress(pHandle, eChannel));
        }
    }
#endif

    if (0U != (ERM->SR0 & (ERM_SR0_SBC4_MASK | ERM_SR0_NCE4_MASK)))
    {
        eChannel = ERM_DMA;
        u8ErrorType = (uint8_t)((ERM->SR0 & (ERM_SR0_SBC4_MASK | ERM_SR0_NCE4_MASK)) >> ERM_SR0_NCE4_SHIFT);
        if (NULL != pHandle->tSettings.pErrorCallback)
        {
            pHandle->tSettings.pErrorCallback(pHandle, eChannel, u8ErrorType, ERM_ReadAddress(pHandle, eChannel));
        }
    }

    ERM_ClearStatus(pHandle);
}

#endif

