/**
 * @file module_driver_eim.c
 * @author Flagchip052
 * @brief EIM driver source code
 * @version 2.0.0
 * @date 2024-10-24
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip052   N/A          First version
*********************************************************************************/
#include "module_driver_eim.h"

#if EIM_INSTANCE_COUNT > 0U

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef EIM_DEV_ERROR_REPORT
#define EIM_DEV_ERROR_REPORT    STD_OFF
#endif

#if EIM_DEV_ERROR_REPORT == STD_ON
#define EIM_ReportDevError(func, error)     ReportDevError(EIM_MODULE_ID, func, error)
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void EIM_SetChannel(EIM_HandleType *const pHandle, const EIM_CHRnType eEimChannel, uint8_t u8Val);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static EIM_Type *const s_apEimBase[EIM_INSTANCE_COUNT] = EIM_BASE_PTRS;

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Sets the state of a specified channel in the Error Injection Module(EIM).
 *
 * This function modifies the channel enable register (CHENR) of the EIM to either enable or disable
 * a particular channel based on the input value `u8Val`. The channel is identified by the `eEimChannel` parameter,
 * which is an enumerated type specifying the channel number.
 *
 * @param pHandle A pointer to the EIM handle structure, containing information about the EIM instance.
 * @param eEimChannel The channel number to be set, defined by the EIM_CHRnType enumeration.
 * @param u8Val A flag indicating the operation to perform: \n
 *        - If `TRUE` (or non-zero), the specified channel will be enabled. \n
 *        - If `FALSE` (or zero), the channel will be disabled.
 *
 * @note Ensure that the EIM peripheral is properly initialized before calling this function.
 */
static void EIM_SetChannel(EIM_HandleType *const pHandle, const EIM_CHRnType eEimChannel, uint8_t u8Val)
{
    uint32_t u32Val = 0U;
    EIM_Type *const pEim = s_apEimBase[pHandle->eInstance];

    u32Val = EIM_HWA_GetChenr(pEim);
    if (u8Val == TRUE)
    {
        u32Val |= (1U << (0x1FU - eEimChannel));
    }
    else
    {
        u32Val &= (~(1U << (0x1FU - eEimChannel)));
    }

    EIM_HWA_SetChnReg(pEim, u32Val);
}

/**
 * @brief Initializes the Error Injection Module(EIM) with provided configuration settings.
 *
 * This function sets up the EIM module according to the configuration specified in `pInitCfg`.
 * It configures the word channels (WORD0 and WORD1), enables the selected EIM channel, and activates
 * global error injection if supported. Error checking is performed to ensure valid pointers and EIM instance.
 *
 * @param pHandle A pointer to the EIM handle structure which identifies the EIM instance to initialize.
 * @param pInitCfg A pointer to the initialization configuration structure (`EIM_ChCfgType`) defining setup parameters for the EIM module.
 *
 * @return `EIM_STATUS_SUCCESS` if the initialization was successful, otherwise `EIM_STATUS_FAIL`.
 *
 * @note The error reporting macros are conditionally compiled based on `EIM_DEV_ERROR_REPORT` definition.
 */
EIM_StatusType EIM_Init(EIM_HandleType *const pHandle, const EIM_ChCfgType *const pInitCfg)
{
    EIM_StatusType eStatus = EIM_STATUS_SUCCESS;

#if EIM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        EIM_ReportDevError(EIM_INIT_ID, EIM_E_PARAM_NULLPTR);
        eStatus = EIM_STATUS_FAIL;
    }
    else if (pInitCfg == NULL)
    {
        EIM_ReportDevError(EIM_INIT_ID, EIM_E_PARAM_NULLPTR);
        eStatus = EIM_STATUS_FAIL;
    }
    else if (pHandle->eInstance >= EIM_INSTANCE_COUNT)
    {
        EIM_ReportDevError(EIM_INIT_ID, EIM_E_PARAM_INSTANCE);
        eStatus = EIM_STATUS_FAIL;
    }
    else
#endif
    {
        EIM_Type *const pEim = s_apEimBase[pHandle->eInstance];

        EIM_HWA_SetWORD0_Channel(pEim, pInitCfg->eWord0Ch, pInitCfg->u32_Word0ChkVal);
        EIM_HWA_SetWORD1_Channel(pEim, pInitCfg->eWord1Ch, pInitCfg->u32_Word1DataVal);
        EIM_SetChannel(pHandle, pInitCfg->eEimChannel, TRUE);

        /* Enable Global Error injection*/
        EIM_HWA_EnableGlobalErrorInjection(pEim);
    }

    return eStatus;
}

/**
 * @brief Deinitializes the Error Injection Module(EIM).
 *
 * This function disables the EIM module by clearing all channel configurations, disabling global error injection,
 * and resetting the word channel registers to their default state. Error checking is performed to ensure a valid EIM instance.
 *
 * @param pHandle A pointer to the EIM handle structure identifying the EIM instance to deinitialize.
 *
 * @note The error reporting macros are conditionally compiled based on `EIM_DEV_ERROR_REPORT` definition.
 */
void EIM_Deinit(EIM_HandleType *const pHandle)
{
#if EIM_DEV_ERROR_REPORT == STD_ON
    if (pHandle == NULL)
    {
        EIM_ReportDevError(EIM_DEINIT_ID, EIM_E_PARAM_NULLPTR);
    }
    else if (pHandle->eInstance >= EIM_INSTANCE_COUNT)
    {
        EIM_ReportDevError(EIM_DEINIT_ID, EIM_E_PARAM_INSTANCE);
    }
    else
#endif
    {
        EIM_Type *const pEim = s_apEimBase[pHandle->eInstance];

        EIM_HWA_DisableGlobalErrorInjection(pEim);
        EIM_HWA_SetChnReg(pEim, 0x0U);
        EIM_HWA_ClearWORD0_Channels(pEim);
        EIM_HWA_ClearWORD1_Channels(pEim);
    }
}

#endif

