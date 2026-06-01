/**
 * @file module_driver_fciic.c
 * @author Flagchip
 * @brief FCIIC driver type definition and API
 * @version 2.0.0
 * @date 2023-09-18
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/* ********************************************************************************
   *   Revision History:
   *
   *   Version     Date          Initials      CR#          Descriptions
   *   ---------   ----------    ------------  ----------   ---------------
   *   0.1.0       2022/12/31    qxw0052      N/A          First version for FC7300
   *   0.2.0       2023/02/14    qxw0052      N/A          Fix MISRA issues
   *   0.2.1       2023/09/18    qxw0100      N/A          modify clock duty to 1:2
   *   x.x.x       2024/xx/xx    qxw0100      N/A          Refactor driver
   ******************************************************************************** */

#include "module_driver_fciic.h"

#if FCIIC_INSTANCE_COUNT > 0U

#include "module_driver_dma.h"

#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


#ifndef FCIIC_DEV_ERROR_REPORT
    #define FCIIC_DEV_ERROR_REPORT    STD_OFF
#endif

#if FCIIC_DEV_ERROR_REPORT == STD_ON
    #define FCIIC_ReportDevError(func, error)     ReportDevError(FCIIC_MODULE_ID, func, error)
#endif

/********* Local variable ************/
static  FCIIC_Type *const s_aFCIIC_InstanceTable[FCIIC_INSTANCE_COUNT] = FCIIC_BASE_PTRS;

/* ################################################################################## */
/* ################################ Global Functions ################################ */

/**
 * @brief Checks if the I2C bus is busy for the master.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC Master handle.
 *
 * @return FCIIC_StatusType Indicates whether the bus is busy or not.
 * @retval FCIIC_SUCCESS Bus is not busy.
 * @retval FCIIC_BUSY Bus is busy.
 */
FCIIC_StatusType FCIIC_MasterCheckForBusyBus(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    FCIIC_StatusType ret = FCIIC_SUCCESS;
    FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];

    uint32_t status = FCIIC_HWA_MasterGetStatusFlags(pFciic);

    if (0U != (status & (uint32_t)FCIIC_MSR_BBF))
    {
        ret = FCIIC_BUSY;
    }
    return ret;
}

/**
 * @brief Initializes a default configuration for the I2C master.
 *
 * This function sets up the default configuration parameters for the I2C master.
 *
 * @param[out] pMasterConfig Pointer to the structure where the default configuration will be stored.
 *
 * The following configurations are set:
 * - bEnableMaster: Enables the master functionality.
 * - bDebugEnable: Disables debug mode by default.
 * - ePinConfig: Sets the pin configuration to open-drain.
 * - u32BaudRate: Sets the baud rate to 100 kHz.
 * - u32BusIdleTimeout: Disables the bus idle timeout.
 * - u32PinLowTimeout: Disables the pin low timeout.
 * - u8SdaGlitchFilterWidth: Disables the SDA glitch filter.
 * - u8SclGlitchFilterWidth: Disables the SCL glitch filter.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
void FCIIC_MasterGetDefaultConfig(FCIIC_MasterConfigType *const pMasterConfig)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pMasterConfig == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERGETDEFAULTCONFIG_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        pMasterConfig->bEnableMaster          = true;
        pMasterConfig->bDebugEnable           = false;
        pMasterConfig->ePinConfig             = FCIIC_OPENDRAIN;
        pMasterConfig->u32BaudRate            = 100000U;
        pMasterConfig->u32BusIdleTimeout      = 0U; /* Set to 0 to disable the function */
        pMasterConfig->u32PinLowTimeout       = 0U; /* Set to 0 to disable the function */
        pMasterConfig->u8SdaGlitchFilterWidth = 0U; /* Set to 0 to disable the function */
        pMasterConfig->u8SclGlitchFilterWidth = 0U; /* Set to 0 to disable the function */
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Sets the baud rate for the I2C master.
 *
 * This function calculates and sets the baud rate for the I2C master based on the given source clock frequency and desired baud rate.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] sourceClock_Hz The source clock frequency in Hz.
 * @param[in] baudRate_Hz The desired baud rate in Hz.
 *
 * The function performs the following steps:
 * - Calculates the optimal values for CLKHI, CLKLO, and PRESCALE to achieve the closest possible baud rate to the desired one.
 * - Configures the MCCR and MCFGR1 registers with the calculated values.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterSetBaudRate(FCIIC_MasterHandleType *const pFciicMasterHandle, uint32_t sourceClock_Hz, uint32_t baudRate_Hz)
{

    /* SCL_LATENCY is defined as ROUNDDOWN ((2 + FILTSCL + SCL_RISETIME) / (2 ^ PRESCALE)) */
    /* CLKLO: Minimum value is 0x3 */
    /* CLKHI: Minimum value is 0x1 */
    /* SCL clock period: (CLKHI + CLKLO + 2 + SCL_LATENCY) / (2 ^ PRESCALE) / function clock period */
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERSETBAUDRATE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MODULE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        uint32_t u32TempMcfgr1, u32TempMccr, u32CLKHI, u32CLKHITemp;
        uint32_t u32Prescale;
        uint32_t u32BandrateDeltaCur, u32BandrateDeltaBest;
        uint32_t u32FreqDesired, u32FreqCur;
        uint32_t u32ClkSrcHz;
        uint8_t u8PrescaleTemp;

        u32ClkSrcHz = sourceClock_Hz;
        u32FreqDesired = baudRate_Hz;
        u32BandrateDeltaBest = baudRate_Hz;


        for (u8PrescaleTemp = 0U; u8PrescaleTemp <= 8U; u8PrescaleTemp++)
        {
            if (u32BandrateDeltaBest == 0U)
            {
                break;
            }

            for (u32CLKHITemp = 1U; u32CLKHITemp < 32U; u32CLKHITemp++)
            {
                if (u32CLKHITemp == 1U)
                {
                    u32FreqCur = u32ClkSrcHz / Fc_Power(2U, u8PrescaleTemp) / (1U + 3U + 2U + 2U);
                }
                else
                {
                    u32FreqCur = u32ClkSrcHz / Fc_Power(2U, u8PrescaleTemp) / (3U * u32CLKHITemp + 2U + 2U);
                }

                u32BandrateDeltaCur = u32FreqDesired > u32FreqCur ? u32FreqDesired - u32FreqCur : u32FreqCur - u32FreqDesired;

                if (u32BandrateDeltaCur < u32BandrateDeltaBest)
                {
                    u32Prescale          = u8PrescaleTemp;
                    u32CLKHI             = u32CLKHITemp;
                    u32BandrateDeltaBest = u32BandrateDeltaCur;

                    /* If the error is 0, then we can stop searching because we won't find a better match. */
                    if (u32BandrateDeltaBest == 0U)
                    {
                        break;
                    }
                }
            }
        }   

        if (u32CLKHI == 1)
        {
            u32TempMccr = FCIIC_MCCR_DATAVD(1) |
                          FCIIC_MCCR_SETHOLD(2)   |
                          FCIIC_MCCR_CLKHI(u32CLKHI) |
                          FCIIC_MCCR_CLKLO(3);
        }
        else
        {
            u32TempMccr = FCIIC_MCCR_DATAVD(u32CLKHI / 2) |
                          FCIIC_MCCR_SETHOLD(u32CLKHI)   |
                          FCIIC_MCCR_CLKHI(u32CLKHI) |
                          FCIIC_MCCR_CLKLO(2 * u32CLKHI);
        }

        u32TempMcfgr1 = FCIIC_HWA_GetMCFGR1(pFciic);
        u32TempMcfgr1 &= ~FCIIC_MCFGR1_PRESCALE_MASK;
        u32TempMcfgr1 |= FCIIC_MCFGR1_PRESCALE(u32Prescale);

        FCIIC_HWA_SetMCCR(pFciic, u32TempMccr);
        FCIIC_HWA_SetMCFGR1(pFciic, u32TempMcfgr1);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Initializes the I2C master with the specified configuration.
 *
 * This function initializes the I2C master with the provided configuration and sets up the baud rate.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] pMasterConfig Pointer to the master configuration structure.
 * @param[in] sourceClock_Hz The source clock frequency in Hz.
 *
 * The function performs the following steps:
 * - Resets the I2C hardware.
 * - Sets the baud rate using the `FCIIC_MasterSetBaudRate` function.
 * - Configures the master control register (MCR) for debug enablement.
 * - Configures the master configuration registers (MCFGR1, MCFGR2, MCFGR3) for pin configuration, glitch filters, and timeouts.
 * - Enables the master operation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointers are null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterInit(FCIIC_MasterHandleType *const pFciicMasterHandle, const FCIIC_MasterConfigType *const pMasterConfig, uint32_t sourceClock_Hz)
{

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL || pMasterConfig == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERINIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERINIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        uint32_t u32TempMcfgr1, u32TempMcfgr2, u32TempMcfgr3;

        FCIIC_HwA_MasterReset(pFciic);

        FCIIC_MasterSetBaudRate(pFciicMasterHandle, sourceClock_Hz, pMasterConfig->u32BaudRate);

        FCIIC_HWA_SetMcr(pFciic, FCIIC_MCR_DBGEN(pMasterConfig->bDebugEnable));

        /* pin config and ignore ack */
        u32TempMcfgr1 = FCIIC_HWA_GetMCFGR1(pFciic);
        u32TempMcfgr1 &= ~(FCIIC_MCFGR1_PINCFG_MASK | FCIIC_MCFGR1_IGNACK_MASK);
        u32TempMcfgr1 |= FCIIC_MCFGR1_PINCFG(pMasterConfig->ePinConfig);
        FCIIC_HWA_SetMCFGR1(pFciic, u32TempMcfgr1);

        /* Configure glitch filters. */
        u32TempMcfgr2 = FCIIC_MCFGR2_FILTSDA(pMasterConfig->u8SdaGlitchFilterWidth) |
                        FCIIC_MCFGR2_FILTSCL(pMasterConfig->u8SclGlitchFilterWidth) |
                        FCIIC_MCFGR2_BUSIDLE(pMasterConfig->u32BusIdleTimeout);
        FCIIC_HWA_SetMCFGR2(pFciic, u32TempMcfgr2);

        u32TempMcfgr3 = FCIIC_MCFGR3_PINLOW(pMasterConfig->u32PinLowTimeout);
        FCIIC_HWA_SetMCFGR3(pFciic, u32TempMcfgr3);

        FCIIC_HwA_MasterEnable(pFciic, pMasterConfig->bEnableMaster);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


/**
 * @brief Deinitializes the I2C master.
 *
 * This function deinitializes the I2C master by resetting it and clearing its configuration.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Resets the master control register (MCR) to disable the master, reset, and clear DMA and buffer flags.
 * - Disables DMA operations by setting the master DMA enable register (MDER).
 * - Clears the pin configuration and glitch filter settings in the master configuration registers (MCFGR1, MCFGR2, MCFGR3).
 * - Resets the I2C hardware.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
void FCIIC_MasterDeinit(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    uint32 u32PccCgcMask = 0x40000000U;
    uint32 u32PccSelMask = 0x7000000U;
    uint32 u32PccBase = 0x40065000U;
    uint32 u32IICPccRegOffset[2] = {0x198U, 0x19CU};
    FCIIC_Type *const pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
    uint32 u32TempMcr, u32TempMder, u32TempPcc;

    u32TempMcr = FCIIC_MCR_RRF(0U)      |
    FCIIC_MCR_RTF(0U)      |
    FCIIC_MCR_DBGEN(0U)    |
    FCIIC_MCR_RST(0U)      |
    FCIIC_MCR_MEN(0U);         /* master disable */

    u32TempMder = FCIIC_MDER_RDDE(0U) |   /* disable receive dma */
    FCIIC_MDER_TDDE(0U);          /* disable transmit dma */

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDEINIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif

        FCIIC_HWA_MasterDisableInterrupts(pFciic, FCIIC_MIER_MASK);
        FCIIC_HWA_SetMder(pFciic, u32TempMder);

        /* PRQA S 0306 ++ #Misra-C:2012 Rule-11.4 A conversion should not be performed between a pointer to object and an integer type
        * Reason: Pointer to register addressing map operation could not be avoid */
        u32TempPcc = *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicMasterHandle->eInstance]));
        /*   Disable PCC gate    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicMasterHandle->eInstance])) = (uint32)(u32TempPcc & (~u32PccCgcMask));
        /*   Disable function clock    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicMasterHandle->eInstance])) = (uint32)(u32TempPcc & (~u32PccSelMask));

        FCIIC_HWA_SetMcr(pFciic, FCIIC_MCR_RST(1U));
        FCIIC_HWA_SetMcr(pFciic, u32TempMcr);

        /*   Disable PCC gate    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicMasterHandle->eInstance])) = (uint32)(u32TempPcc & (~u32PccCgcMask));
        /*   Recover function clock    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicMasterHandle->eInstance])) = u32TempPcc;
        /* PRQA S 0306 -- */
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


/**
 * @brief Initializes the I2C master handle.
 *
 * This function initializes the I2C master handle with the specified instance and clears its status and settings.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] eInstance The instance of the I2C master to initialize.
 *
 * The function performs the following steps:
 * - Sets the instance of the handle.
 * - Clears the status fields including command data, direction, channel status, and offsets.
 * - Sets callback functions and user data pointers to null.
 * - Initializes DMA-related settings to null or zero.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterInitHandle(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_InstanceType eInstance)
{
    uint8_t i = 0;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERINITHANDLE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if (eInstance >= FCIIC_INSTANCE_COUNT)
    {
        FCIIC_ReportDevError(FCIIC_MASTERINITHANDLE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciicMasterHandle->eInstance = eInstance;
        pFciicMasterHandle->tStatus.bUsed = false;
        pFciicMasterHandle->tStatus.eDirection = FCIIC_DIRNOCONFIG;
        for (i = 0; i < FCIIC_MASTER_CMD_SIZE; i++)
        {
            pFciicMasterHandle->tStatus.u8Cmd[i] = FCIIC_TX_CMD_STOP;
            pFciicMasterHandle->tStatus.u16DmaCmdData[i] = 0;
            pFciicMasterHandle->tStatus.u8CmdData[i] = 0;
        }
        pFciicMasterHandle->tStatus.u8CmdSize = 0;
        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
        pFciicMasterHandle->tStatus.u8CmdOffset = 0;
        pFciicMasterHandle->tStatus.u16DataSize = 0;
        pFciicMasterHandle->tStatus.u16DataOffset = 0;
        pFciicMasterHandle->tSettings.pCallback = NULL;
        pFciicMasterHandle->tSettings.pErrorCallback = NULL;
        pFciicMasterHandle->tSettings.pUserData = NULL;
        pFciicMasterHandle->tSettings.pData = NULL;
        pFciicMasterHandle->tStatus.u8DmaCmdSize = 0;
        pFciicMasterHandle->tStatus.u8DmaCmdOffset = 0;
        pFciicMasterHandle->tSettings.pFciicTxDmaConfig = NULL;
        pFciicMasterHandle->tSettings.pFciicRxDmaConfig = NULL;

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Enables interrupt handling for the I2C master.
 *
 * This function sets the callback functions and user data for interrupt handling in the I2C master.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] pCallback Pointer to the transfer callback function.
 * @param[in] pErrorCallback Pointer to the error callback function.
 * @param[in] pUserData User-defined data to be passed to the callback functions.
 *
 * The function performs the following steps:
 * - Sets the transfer callback, error callback, and user data pointers in the handle's settings.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
void FCIIC_MasterEnableInterrupt(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransfer_CallbackType pCallback, FCIIC_MasterError_CallBackType pErrorCallback,
                                 void *pUserData)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERENABLEINTERRUPT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        pFciicMasterHandle->tSettings.pCallback       = pCallback;
        pFciicMasterHandle->tSettings.pErrorCallback  = pErrorCallback;
        pFciicMasterHandle->tSettings.pUserData       = pUserData;

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Checks and clears errors in the I2C master.
 *
 * This function checks for specific error conditions in the I2C master and clears them if present.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] status The status flags to check and clear.
 *
 * @return FCIIC_StatusType The error status or FCIIC_SUCCESS if no errors were detected.
 *
 * The function performs the following steps:
 * - Checks the status flags against known error conditions.
 * - Selects the appropriate error code based on the severity and type of error.
 * - Clears the error flags in the I2C hardware.
 * - Resets the FIFOs if necessary.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterCheckAndClearError(FCIIC_MasterHandleType *const pFciicMasterHandle, uint32_t status)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERCHECKANDCLEARERROR_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERCHECKANDCLEARERROR_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        status &= (uint32_t)FCIIC_MasterErrorFlags;
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        if (0U != status)
        {
            /* Select the correct error code. Ordered by severity, with bus issues first. */
            if (0U != (status & (uint32_t)FCIIC_MSR_PLTF))
            {
                result = FCIIC_PINLOWTIMEOUT;
            }
            else if (0U != (status & (uint32_t)FCIIC_MSR_ALF))
            {
                result = FCIIC_ARBITRATIONLOST;
            }
            else if (0U != (status & (uint32_t)FCIIC_MSR_NDF))
            {
                result = FCIIC_NAK;
            }
            else if (0U != (status & (uint32_t)FCIIC_MSR_FEF))
            {
                result = FCIIC_FIFOERROR;
            }
            else
            {

            }

            /* Clear the flags. */
            FCIIC_HWA_MasterClearStatusFlags(pFciic, status);

            /* Reset fifos. These flags clear automatically. */
            FCIIC_HWA_MasterResetFIFO(pFciic);
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Waits for a specific flag to be set in the I2C master.
 *
 * This function waits for a given flag to be set in the I2C master status and returns the result.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] u32Flag The flag to wait for.
 *
 * @return FCIIC_StatusType The status indicating success or timeout.
 *
 * The function performs the following steps:
 * - Waits for the specified flag to be set within a certain number of attempts.
 * - Returns FCIIC_SUCCESS if the flag is set, or FCIIC_TIMEOUT if the flag is not set within the timeout period.
 * - Checks and clears any errors that may have occurred during the wait.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterWaitFlag(FCIIC_MasterHandleType *const pFciicMasterHandle, uint32_t u32Flag)
{
    FCIIC_StatusType result = FCIIC_TIMEOUT;
    FCIIC_Type *pFciic;
    uint32_t u32TryCount, u32TryTick;
    uint32_t status;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERWAITFLAG_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERWAITFLAG_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        u32TryCount = 0U;
        while (u32TryCount < 100U)
        {
            u32TryTick = 0U;
            while (u32TryTick++ < 100U)
            {
                __asm("nop");
            }

            status = FCIIC_HWA_MasterGetStatusFlags(pFciic);
            if (0U != (status & u32Flag))
            {
                result = FCIIC_SUCCESS;
                break;
            }

            u32TryCount++;
        }
        if (result != FCIIC_TIMEOUT)
        {
            result = FCIIC_MasterCheckAndClearError(pFciicMasterHandle, status);
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Initiates an I2C start condition.
 *
 * This function initiates an I2C start condition and sends the device address along with the read/write direction.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] address The 7-bit I2C address of the target device.
 * @param[in] dir The direction of the communication (read or write).
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Checks if the bus is busy before starting.
 * - Clears all relevant flags in the I2C hardware.
 * - Sends a start condition followed by the address and direction.
 * - Waits for the transmission done flag to be set.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterStart(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8_t address, FCIIC_DirectionType dir)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERSTART_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERSTART_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        result = FCIIC_MasterCheckForBusyBus(pFciicMasterHandle);
        if (result == FCIIC_SUCCESS)
        {
            /* Clear all flags. */
            FCIIC_HWA_MasterClearStatusFlags(pFciic, FCIIC_MasterClearFlags);

            FCIIC_Master_HWA_Transmit(pFciic, FCIIC_TX_CMD_STARTANDTRANSMIT, (uint8_t)((address << 1U) | dir));
        }

        result = FCIIC_MasterWaitFlag(pFciicMasterHandle, FCIIC_MSR_TDF);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Initiates an I2C repeated start condition.
 *
 * This function initiates an I2C repeated start condition and sends the device address along with the read/write direction.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] address The 7-bit I2C address of the target device.
 * @param[in] dir The direction of the communication (read or write).
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Sends a repeated start condition followed by the address and direction.
 * - Waits for the transmission done flag to be set.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterRepeatedStart(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8_t address, FCIIC_DirectionType dir)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERREPEATEDSTART_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERREPEATEDSTART_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        FCIIC_Master_HWA_Transmit(pFciic, FCIIC_TX_CMD_STARTANDTRANSMIT, (uint8_t)((address << 1U) | dir));
        result = FCIIC_MasterWaitFlag(pFciicMasterHandle, FCIIC_MSR_TDF);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Sends a sequence of commands in the I2C master.
 *
 * This function sends a sequence of commands and data to the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Iterates through each command in the command buffer.
 * - Sends the command and corresponding data.
 * - Waits for the transmission done flag to be set for each command.
 * - Increments the command offset after each successful transmission.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterSendStartCommand(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;
    uint8 i;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERSEND_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERSEND_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        for (i = 0; i < pFciicMasterHandle->tStatus.u8CmdSize; ++i)
        {
            FCIIC_Master_HWA_Transmit(pFciic,  pFciicMasterHandle->tStatus.u8Cmd[i], pFciicMasterHandle->tStatus.u8CmdData[i]);
            result = FCIIC_MasterWaitFlag(pFciicMasterHandle, FCIIC_MSR_TDF);
            if (result != FCIIC_SUCCESS)
            {
                break;
            }
            pFciicMasterHandle->tStatus.u8CmdOffset++;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Sends data over the I2C bus.
 *
 * This function sends a block of data over the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] txBuff Pointer to the transmit buffer containing the data to send.
 * @param[in] txSize The size of the data to send in bytes.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Iterates through each byte in the transmit buffer.
 * - Sends the byte over the I2C bus.
 * - Waits for the transmission done flag to be set for each byte.
 * - Increments the data offset after each successful transmission.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterSend(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8 *txBuff, uint16 txSize)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;
    uint16 i;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERSEND_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERSEND_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        for (i = 0; i < txSize; ++i)
        {
            FCIIC_Master_HWA_Transmit(pFciic, FCIIC_TX_CMD_TRANSMIT, txBuff[i]);
            result = FCIIC_MasterWaitFlag(pFciicMasterHandle, FCIIC_MSR_TDF);
            if (result != FCIIC_SUCCESS)
            {
                break;
            }
            pFciicMasterHandle->tStatus.u16DataOffset++;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Receives data over the I2C bus.
 *
 * This function receives a block of data over the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Iterates through each byte of the receive buffer.
 * - Waits for the receive data flag to be set.
 * - Reads the received byte from the I2C bus.
 * - Stores the received byte in the receive buffer.
 * - Increments the data offset after each successful reception.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterReceive(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;
    uint8_t i;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERRECEIVE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERRECEIVE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        for (i = 0; i < pFciicMasterHandle->tStatus.u16DataSize; ++i)
        {
            result = FCIIC_MasterWaitFlag(pFciicMasterHandle, FCIIC_MSR_RDF);
            if (result != FCIIC_SUCCESS)
            {
                break;
            }
            pFciicMasterHandle->tSettings.pData[i] = FCIIC_Master_HWA_Receive(pFciic);
            pFciicMasterHandle->tStatus.u16DataOffset++;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Sends a stop condition over the I2C bus.
 *
 * This function sends a stop condition over the I2C bus.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * @return FCIIC_StatusType The status indicating success or failure.
 *
 * The function performs the following steps:
 * - Sends a stop condition over the I2C bus.
 * - Waits for the transmission done flag to be set.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
FCIIC_StatusType FCIIC_MasterStop(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERSTOP_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERSTOP_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        FCIIC_Master_HWA_Transmit(pFciic, FCIIC_TX_CMD_STOP, 0U);
        result = FCIIC_MasterWaitFlag(pFciicMasterHandle, FCIIC_MSR_TDF);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Aborts an ongoing I2C transfer.
 *
 * This function aborts an ongoing I2C transfer by disabling interrupts, resetting the FIFO, and marking the handle as unused.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Disables interrupts for the I2C master.
 * - Resets the FIFO.
 * - Marks the handle as unused.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterTransferAbort(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    FCIIC_Type *pFciic;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_MASTERTRANSFERABORT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERTRANSFERABORT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        FCIIC_HWA_MasterDisableInterrupts(pFciic, (uint32_t)FCIIC_MasterIrqFlags);
        FCIIC_HWA_MasterResetFIFO(pFciic);
        pFciicMasterHandle->tStatus.bUsed = false;
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Sets the receive length for an ongoing I2C transfer.
 *
 * This function sets the number of bytes to receive during an ongoing I2C transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] u8Len The number of bytes to receive.
 *
 * @return uint8_t Returns 1 if the receive length was successfully set, otherwise 0.
 *
 * The function performs the following steps:
 * - Checks if the transmit count is less than 8.
 * - If the condition is met, sends a receive command with the specified length minus one.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly.
 */
uint8_t FCIIC_MasterSetReceiveLen(FCIIC_MasterHandleType *const pFciicMasterHandle, uint8 u8Len)
{
    uint8_t eRetType = 0;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERSETRECEIVELEN_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        uint8_t count = (uint8_t)FCIIC_Master_HWA_GetTxCount(pFciic);
        if (8u > count)
        {
            FCIIC_Master_HWA_Transmit(pFciic, FCIIC_TX_CMD_RECEIVE, (uint8_t)(u8Len - (uint8)1u));
            eRetType = 1;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return eRetType;
}

/**
 * @brief Transmits data over the I2C bus.
 *
 * This function transmits data over the I2C bus if the transmission data flag is set.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] pTxData Pointer to the transmit data structure containing the command and data to send.
 *
 * @return uint8_t Returns 1 if the transmission was initiated, otherwise 0.
 *
 * The function performs the following steps:
 * - Clears any error flags.
 * - Checks the transmission data flag.
 * - If the flag is set, sends the command and data.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointers are null and report an error accordingly. It also checks if the instance is valid.
 */
uint8_t FCIIC_MasterTransmit(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_TxDataType *pTxData)
{
    uint8_t    u8RetVal;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle || NULL == pTxData)
    {
        FCIIC_ReportDevError(FCIIC_MASTERTRANSMIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERTRANSMIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];

        /* clear error flag */
        /* CheckAndClear(pFciic); */

        /* check tx data flag */
        u8RetVal = FCIIC_Master_HWA_GetStatus(pFciic, FCIIC_MSR_TDF_STATUS);

        /* pFciic->MSR |= FCIIC_MSR_FEF_MASK; */ /* clear fifo error error */
        if (u8RetVal == 1U)
        {
            FCIIC_Master_HWA_Transmit(pFciic, pTxData->eCmd, pTxData->u8Data);
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return (uint8_t)(1U >> u8RetVal);
}

/**
 * @brief Gets the status of the I2C master.
 *
 * This function retrieves the status of the I2C master based on the specified status type.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] eStatus The status type to retrieve.
 *
 * @return uint8_t Returns the status value as a bit mask.
 *
 * The function performs the following steps:
 * - Retrieves the status based on the specified status type.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
uint8_t FCIIC_MasterGetStatus(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterStatusType eStatus)
{
    uint8_t u8Status;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERGETSTATUS_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERGETSTATUS_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        FCIIC_Type *pFciic  = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        u8Status = (uint8_t)(1U >> FCIIC_Master_HWA_GetStatus(pFciic, eStatus));

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return u8Status;
}

/**
 * @brief Clears the status flags of the I2C master.
 *
 * This function clears specific status flags of the I2C master.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Clears the data match flag, protocol error flag, FIFO error flag, address lost flag,
 *   not data flag, start detection flag, and end packet flag.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterClrStatus(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERCLRSTATUS_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERCLRSTATUS_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic  = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];

        FCIIC_Master_HWA_ClrStatus(pFciic, FCIIC_MSR_DMF_MASK | FCIIC_MSR_PLTF_MASK |
                                   FCIIC_MSR_FEF_MASK | FCIIC_MSR_ALF_MASK |
                                   FCIIC_MSR_NDF_MASK | FCIIC_MSR_SDF_MASK |
                                   FCIIC_MSR_EPF_MASK);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


/**
 * @brief Performs a blocking I2C transfer.
 *
 * This function performs a blocking I2C transfer, which includes sending commands and data, and handling the transfer completion or errors.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] transfer Pointer to the I2C transfer parameters.
 *
 * @return FCIIC_StatusType Returns the status of the transfer operation.
 *
 * The function performs the following steps:
 * - Checks if the bus is busy or the handle is already in use.
 * - Clears the status flags.
 * - Initializes the handle's status fields.
 * - Generates and sends the start command.
 * - Sends or receives data based on the direction.
 * - Sends a stop signal after the data transfer.
 * - Calls the callback function upon successful transfer completion.
 * - Calls the error callback function if an error occurs during the transfer.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointers are null and report an error accordingly.
 */
FCIIC_StatusType FCIIC_MasterTransferBlocking(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    uint32_t u8CurChSts;
    FCIIC_DirectionType eDirection;
    FCIIC_Type *pFciic;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if ((NULL == pFciicMasterHandle) || (NULL == transfer))
    {
        FCIIC_ReportDevError(FCIIC_MASTERTRANSFERBLOCKING_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        if ((NULL != pFciicMasterHandle) && (NULL != transfer) && (pFciicMasterHandle->eInstance < FCIIC_INSTANCE_COUNT))
        {
            pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
            result = FCIIC_MasterCheckForBusyBus(pFciicMasterHandle);

            if ((result == FCIIC_BUSY) || (pFciicMasterHandle->tStatus.bUsed == true) || (FCIIC_CH_IDLE != pFciicMasterHandle->tStatus.eChannelStatus))
            {
                return FCIIC_BUSY;
            }
            FCIIC_MasterClrStatus(pFciicMasterHandle);

            pFciicMasterHandle->tStatus.bUsed = true;
            pFciicMasterHandle->tStatus.eDirection = transfer->eDirection;
            pFciicMasterHandle->tSettings.pData = transfer->pData;
            pFciicMasterHandle->tStatus.u16DataSize = transfer->u16DataSize;
            pFciicMasterHandle->tStatus.u16DataOffset = 0;
            pFciicMasterHandle->tStatus.u8CmdSize = 0;
            pFciicMasterHandle->tStatus.u8CmdOffset = 0;
            eDirection = pFciicMasterHandle->tStatus.eDirection;

            FCIIC_MasterGenerateStartCommand(pFciicMasterHandle, transfer);

            /*master send command data stage*/
            result = FCIIC_MasterSendStartCommand(pFciicMasterHandle);

            if ((FCIIC_SUCCESS == result) && (pFciicMasterHandle->tStatus.u8CmdOffset == pFciicMasterHandle->tStatus.u8CmdSize))
            {
                pFciicMasterHandle->tStatus.eChannelStatus = eDirection == FCIIC_WRITE ? FCIIC_CH_START_WRITE : FCIIC_CH_START_READ;
            }
            else
            {
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            }
            /*master transmit or receive data stage*/
            if ((FCIIC_WRITE == eDirection) && (FCIIC_CH_START_WRITE == pFciicMasterHandle->tStatus.eChannelStatus))
            {
                result = FCIIC_MasterSend(pFciicMasterHandle, pFciicMasterHandle->tSettings.pData, pFciicMasterHandle->tStatus.u16DataSize);
            }
            else if ((FCIIC_READ == eDirection) && (FCIIC_CH_START_READ == pFciicMasterHandle->tStatus.eChannelStatus))
            {
                result = FCIIC_MasterReceive(pFciicMasterHandle);
            }
            else
            {
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                result = FCIIC_TRAMSMITORRECEIVEERROR;
            }

            /*master send stop signal stage*/
            if ((FCIIC_SUCCESS == result) && (pFciicMasterHandle->tStatus.u16DataOffset == pFciicMasterHandle->tStatus.u16DataSize))
            {
                result = FCIIC_MasterStop(pFciicMasterHandle);
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
            }
            else
            {
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                result |= FCIIC_TRAMSMITORRECEIVEERROR;
            }
            /*master callback function*/
            if ((FCIIC_SUCCESS == result) && (pFciicMasterHandle->tStatus.eChannelStatus == FCIIC_CH_TRANSFER_FINISHED))
            {
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
                pFciicMasterHandle->tStatus.bUsed = false;
                if (NULL != pFciicMasterHandle->tSettings.pCallback)
                {
                    pFciicMasterHandle->tSettings.pCallback(pFciicMasterHandle, FCIIC_SUCCESS);
                }
            }
            /*master callback error function*/
            if (FCIIC_CH_ERROR_PRESENT == pFciicMasterHandle->tStatus.eChannelStatus)
            {
                u8CurChSts = FCIIC_HWA_GetMSR(pFciic);
                result |= FCIIC_MasterCheckAndClearError(pFciicMasterHandle, u8CurChSts);
                FCIIC_MasterTransferAbort(pFciicMasterHandle);
                if (NULL != pFciicMasterHandle->tSettings.pErrorCallback)
                {
                    pFciicMasterHandle->tSettings.pErrorCallback(pFciicMasterHandle, result);
                }
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
                pFciicMasterHandle->tStatus.bUsed = false;
            }
        }
        else
        {
            result = FCIIC_FAIL;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}
/**
 * @brief Prepares the DMA channel for I2C master transfer.
 *
 * This function prepares the DMA channel for data transfer by configuring the DMA attributes and starting the DMA transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Configures the DMA channel attributes based on the transfer direction (read/write).
 * - Sets up the DMA source and destination buffers, block size, and other settings.
 * - Starts the DMA transfer.
 * - Updates the channel status based on the transfer direction.
 * - Calls the error callback function if an error occurs during preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterDmaPrepare(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMAPREPARE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((NULL != pFciicMasterHandle) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMAPREPARE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        DMA_HandleType *pDmaHandle = NULL;
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        DMA_ChannelCfgType FCIIC_DmaChannelAttr = {0};

        if (FCIIC_DMA_NEXT_STAGE_DATA == pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage ||
            FCIIC_DMA_NEXT_STAGE_DATA == pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage)
        {
            FCIIC_DmaChannelAttr.eSrcDataSize          = DMA_TRANSFER_SIZE_1B;
            FCIIC_DmaChannelAttr.eDestDataSize         = DMA_TRANSFER_SIZE_1B;
            FCIIC_DmaChannelAttr.u32BlockSize          = 1;
            FCIIC_DmaChannelAttr.u16BlockCount         = pFciicMasterHandle->tStatus.u16DataSize;
            if (FCIIC_WRITE == pFciicMasterHandle->tStatus.eDirection)
            {
                FCIIC_DmaChannelAttr.pSrcBuffer            = &(pFciicMasterHandle->tSettings.pData[0]);
                FCIIC_DmaChannelAttr.pDestBuffer           = &(pFciic->MTDR);
                FCIIC_DmaChannelAttr.eSrcIncMode           = DMA_INCREMENT_DATA_SIZE ;
                FCIIC_DmaChannelAttr.eDestIncMode          = DMA_INCREMENT_DISABLE;
                pDmaHandle                                 = pFciicMasterHandle->tSettings.pFciicTxDmaConfig->pDmaHandle;
                if (FCIIC_INSTANCE_0 == pFciicMasterHandle->eInstance)
                {
                    FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC0_TX;
                }
                else
                {
                    FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC1_TX;
                }
            }
            else if (FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
            {
                FCIIC_DmaChannelAttr.pSrcBuffer            = &(pFciic->MRDR);
                FCIIC_DmaChannelAttr.pDestBuffer           = &(pFciicMasterHandle->tSettings.pData[0]);
                FCIIC_DmaChannelAttr.eSrcIncMode           = DMA_INCREMENT_DISABLE ;
                FCIIC_DmaChannelAttr.eDestIncMode          = DMA_INCREMENT_DATA_SIZE;
                pDmaHandle                                 = pFciicMasterHandle->tSettings.pFciicRxDmaConfig->pDmaHandle;
                if (FCIIC_INSTANCE_0 == pFciicMasterHandle->eInstance)
                {
                    FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC0_RX;
                }
                else
                {
                    FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC1_RX;
                }
            }
            else
            {
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            }
        }
        else
        {
            FCIIC_DmaChannelAttr.pSrcBuffer            = &(pFciicMasterHandle->tStatus.u16DmaCmdData[0]);
            FCIIC_DmaChannelAttr.pDestBuffer           = &(pFciic->MTDR);
            FCIIC_DmaChannelAttr.eSrcDataSize          = DMA_TRANSFER_SIZE_2B;
            FCIIC_DmaChannelAttr.eDestDataSize         = DMA_TRANSFER_SIZE_2B;
            FCIIC_DmaChannelAttr.u32BlockSize          = 2;
            FCIIC_DmaChannelAttr.u16BlockCount         = pFciicMasterHandle->tStatus.u8DmaCmdSize;
            FCIIC_DmaChannelAttr.eSrcIncMode           = DMA_INCREMENT_DATA_SIZE ;
            FCIIC_DmaChannelAttr.eDestIncMode          = DMA_INCREMENT_DISABLE;
            pDmaHandle                                 = pFciicMasterHandle->tSettings.pFciicTxDmaConfig->pDmaHandle;
            if (FCIIC_INSTANCE_0 == pFciicMasterHandle->eInstance)
            {
                FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC0_TX;
            }
            else
            {
                FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC1_TX;
            }
        }

        FCIIC_DmaChannelAttr.u8ChannelPriority     = pDmaHandle->tSettings.u8Channel;
        FCIIC_DmaChannelAttr.bSrcBlockOffsetEn     = false;
        FCIIC_DmaChannelAttr.bDestBlockOffsetEn    = false;
        FCIIC_DmaChannelAttr.s32BlockOffset        = 0;
        FCIIC_DmaChannelAttr.bSrcAddrLoopbackEn    = false;
        FCIIC_DmaChannelAttr.bDestAddrLoopbackEn   = false;
        FCIIC_DmaChannelAttr.bAutoStop             = true;
        FCIIC_DmaChannelAttr.bSrcCircularBufferEn  = false;
        FCIIC_DmaChannelAttr.u32SrcCircBufferSize  = 0;
        FCIIC_DmaChannelAttr.bDestCircularBufferEn = false;
        FCIIC_DmaChannelAttr.u32DestCircBufferSize = 0;


        FCIIC_DmaChannelAttr.bTransferCompleteIntEn  = true;
        FCIIC_DmaChannelAttr.pTransferCompleteNotify = pDmaHandle->tSettings.callback.pTransferCompleteCallback;
        FCIIC_DmaChannelAttr.bTransferErrorIntEn     = false;
        FCIIC_DmaChannelAttr.pTransferErrorNotify    = NULL;
        FCIIC_DmaChannelAttr.completedata            = NULL;
        FCIIC_DmaChannelAttr.errdata                 = NULL;


        if(FCIIC_CH_IDLE == pFciicMasterHandle->tStatus.eChannelStatus)
        {
            if ((FCIIC_READ == pFciicMasterHandle->tStatus.eDirection) && (FCIIC_DMA_NEXT_STAGE_IDLE == pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage))
            {
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_START_READ;
                pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_DATA;
            }
            else if ((FCIIC_WRITE == pFciicMasterHandle->tStatus.eDirection) && (FCIIC_DMA_NEXT_STAGE_IDLE == pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage))
            {
                pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_DATA;
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_START_WRITE;
            }
            else
            {
                if (NULL != pFciicMasterHandle->tSettings.pErrorCallback)
                {
                    pFciicMasterHandle->tSettings.pErrorCallback(pFciicMasterHandle, FCIIC_DMAREQUESTFAIL);
                }
            }
        }

        DMA_InitChannel(pDmaHandle, &FCIIC_DmaChannelAttr);
        DMA_StartChannel(pDmaHandle);

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Stops the DMA transfer for the I2C master.
 *
 * This function stops the DMA transfer by preparing a stop command and updating the DMA configuration.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Sets up the stop command in the DMA command buffer.
 * - Prepares the DMA for the stop command.
 * - Updates the channel status to indicate the transfer has been stopped.
 * - Adjusts the next DMA stage based on the transfer direction.
 * - Calls the error callback function if an error occurs during the preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void FCIIC_MasterDmaStop(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMASTOP_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMASTOP_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        pFciicMasterHandle->tStatus.u16DmaCmdData[0] = (uint16)FCIIC_MTDR_CMD(FCIIC_TX_CMD_STOP);
        pFciicMasterHandle->tStatus.u8DmaCmdSize = 1;
        pFciicMasterHandle->tStatus.u8DmaCmdOffset = 0;
        FCIIC_MasterDmaPrepare(pFciicMasterHandle);

        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_CLOSED;

        if ((FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
            && (FCIIC_DMA_NEXT_STAGE_STOP == pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage))
        {
            pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_NOTIFICATION;
        }
        else if ((FCIIC_WRITE == pFciicMasterHandle->tStatus.eDirection)
                 && (FCIIC_DMA_NEXT_STAGE_STOP == pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage))
        {
            pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_NOTIFICATION;
        }
        else
        {
            pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Initiates a DMA transmit operation for the I2C master.
 *
 * This function initiates the DMA transmit operation by preparing the DMA for transmission and setting the next DMA stage to stop.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Prepares the DMA for the transmit operation.
 * - Sets the next DMA stage to stop after the transmission.
 * - Calls the error callback function if an error occurs during preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void  FCIIC_MasterDmaTransmit(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMATRANSMIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((NULL != pFciicMasterHandle) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMATRANSMIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        FCIIC_MasterDmaPrepare(pFciicMasterHandle);
        pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_STOP;
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Initiates a DMA receive operation for the I2C master.
 *
 * This function initiates the DMA receive operation by preparing the DMA for reception and setting the next DMA stage to stop.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 *
 * The function performs the following steps:
 * - Prepares the DMA for the receive operation.
 * - Sets the next DMA stage to stop after the reception.
 * - Calls the error callback function if an error occurs during preparation.
 *
 * @note If FCIIC_DEV_ERROR_REPORT is defined as STD_ON, this function will check if the provided pointer is null and report an error accordingly. It also checks if the instance is valid.
 */
void  FCIIC_MasterDmaReceive(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMARECEIVE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((NULL == pFciicMasterHandle) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMARECEIVE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        FCIIC_MasterDmaPrepare(pFciicMasterHandle);
        pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_STOP;

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Starts the DMA transfer for the FCIIC master.
 *
 * This function initializes the DMA command sequence based on the given transfer parameters.
 * It checks for valid input parameters and then prepares the DMA commands to be sent.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle structure.
 * @param[in] transfer Pointer to the FCIIC master transfer structure containing transfer details.
 */
void  FCIIC_MasterDmaStart(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMASTART_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMASTART_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        uint8_t *pSubAddr = (uint8_t *)&transfer->subaddress;
        uint32 i;
        pFciicMasterHandle->tStatus.u8DmaCmdSize = 0;

        if (0U != transfer->subaddressSize)
        {

            pFciicMasterHandle->tStatus.u16DmaCmdData[pFciicMasterHandle->tStatus.u8DmaCmdSize] = (uint16)(FCIIC_MTDR_CMD(FCIIC_TX_CMD_STARTANDTRANSMIT) | FCIIC_MTDR_DATA((uint8)(
                                transfer->u8SlaveAddress << 1) | FCIIC_WRITE));
            pFciicMasterHandle->tStatus.u8DmaCmdSize++;

            for (i = transfer->subaddressSize; i > 0 ; --i)
            {
                pFciicMasterHandle->tStatus.u16DmaCmdData[pFciicMasterHandle->tStatus.u8DmaCmdSize] = (uint16)(FCIIC_MTDR_CMD(FCIIC_TX_CMD_TRANSMIT) | FCIIC_MTDR_DATA(pSubAddr[i - 1]));
                pFciicMasterHandle->tStatus.u8DmaCmdSize++;
            }

            if (FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
            {
                pFciicMasterHandle->tStatus.u16DmaCmdData[pFciicMasterHandle->tStatus.u8DmaCmdSize] = (uint16)(FCIIC_MTDR_CMD(FCIIC_TX_CMD_STARTANDTRANSMIT) | FCIIC_MTDR_DATA((
                                    transfer->u8SlaveAddress << 1) | FCIIC_READ));
                pFciicMasterHandle->tStatus.u8DmaCmdSize++;

                pFciicMasterHandle->tStatus.u16DmaCmdData[pFciicMasterHandle->tStatus.u8DmaCmdSize] = (uint16)(FCIIC_MTDR_CMD(FCIIC_TX_CMD_RECEIVE) | FCIIC_MTDR_DATA((transfer->u16DataSize - 1)));
                pFciicMasterHandle->tStatus.u8DmaCmdSize++;
            }
        }
        else
        {
            pFciicMasterHandle->tStatus.u16DmaCmdData[pFciicMasterHandle->tStatus.u8DmaCmdSize] = (uint16)((uint16)FCIIC_MTDR_CMD(FCIIC_TX_CMD_STARTANDTRANSMIT) | ((
                                transfer->u8SlaveAddress << 1) | transfer->eDirection));
            pFciicMasterHandle->tStatus.u8DmaCmdSize++;
            if (FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
            {
                pFciicMasterHandle->tStatus.u16DmaCmdData[pFciicMasterHandle->tStatus.u8DmaCmdSize] = (uint16)(FCIIC_MTDR_CMD(FCIIC_TX_CMD_RECEIVE) | (uint8_t)(transfer->u16DataSize - 1));
                pFciicMasterHandle->tStatus.u8DmaCmdSize++;
            }
        }

        FCIIC_MasterDmaPrepare(pFciicMasterHandle);

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Handles the notification stage after a DMA transmission.
 *
 * This function updates the channel status and triggers a callback if one is registered.
 * It also manages the next stage of DMA operations based on the direction of the transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterDmaStageNotification(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMASTAGENOTIFICATION_ID, FCIIC_E_PARAM_NULLPTR);
    }
    #endif

    pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
    if ((FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
        && (FCIIC_DMA_NEXT_STAGE_NOTIFICATION == pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage))
    {
        pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_IDLE;
    }
    else if ((FCIIC_WRITE == pFciicMasterHandle->tStatus.eDirection)
             && (FCIIC_DMA_NEXT_STAGE_NOTIFICATION == pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage))
    {
        pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_IDLE;
    }
    else
    {
        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
    }

    if (NULL != pFciicMasterHandle->tSettings.pCallback)
    {
        pFciicMasterHandle->tSettings.pCallback(pFciicMasterHandle, FCIIC_SUCCESS);
    }
    pFciicMasterHandle->tStatus.bUsed = false;
}

/**
 * @brief Handles the data stage of a DMA transmission.
 *
 * This function updates the channel status and triggers the data transfer phase
 * based on the current state and direction of the transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterDmaStageData(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMASTAGEDATA_ID, FCIIC_E_PARAM_NULLPTR);
    }
    #endif
    FCIIC_ChannelStatusType eChannelStatus;

    eChannelStatus = pFciicMasterHandle->tStatus.eChannelStatus;

    if ((FCIIC_WRITE == pFciicMasterHandle->tStatus.eDirection) && (FCIIC_CH_START_WRITE == eChannelStatus)
        && (FCIIC_DMA_NEXT_STAGE_DATA == pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage))
    {
        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
        FCIIC_MasterDmaTransmit(pFciicMasterHandle);
    }
    else if ((FCIIC_READ == pFciicMasterHandle->tStatus.eDirection) && (FCIIC_CH_START_READ == eChannelStatus)
             && (FCIIC_DMA_NEXT_STAGE_DATA == pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage))
    {
        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
        FCIIC_MasterDmaReceive(pFciicMasterHandle);
    }
    else
    {
        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
    }
}

/**
 * @brief DMA interrupt handler for the FCIIC master.
 *
 * This function handles DMA interrupts by determining the next stage of the DMA operation,
 * updating the channel status, and managing error conditions.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_LL_MasterDmaIRQnHandler(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_LL_MASTERDMAIRQNHANDLER_ID, FCIIC_E_PARAM_NULLPTR);
    }
    #endif
    FCIIC_DmaStatusType eDmaNextStage;
    uint32_t         u8CurChSts;
    FCIIC_ChannelStatusType eChannelStatus = pFciicMasterHandle->tStatus.eChannelStatus;
    FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
    FCIIC_StatusType eResult;

    eDmaNextStage = FCIIC_WRITE == pFciicMasterHandle->tStatus.eDirection ?
                    pFciicMasterHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage : pFciicMasterHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage;

    eChannelStatus = pFciicMasterHandle->tStatus.eChannelStatus;

    if ((FCIIC_DMA_NEXT_STAGE_DATA == eDmaNextStage) && ((FCIIC_CH_START_READ == eChannelStatus) || (FCIIC_CH_START_WRITE == eChannelStatus)))
    {
        pFciicMasterHandle->tStatus.u8DmaCmdOffset = pFciicMasterHandle->tStatus.u8DmaCmdSize;
        FCIIC_MasterDmaStageData(pFciicMasterHandle);
    }
    else if ((FCIIC_DMA_NEXT_STAGE_STOP == eDmaNextStage) && (FCIIC_CH_TRANSFER_FINISHED == eChannelStatus))
    {
        pFciicMasterHandle->tStatus.u16DataOffset = pFciicMasterHandle->tStatus.u16DataSize;
        FCIIC_MasterDmaStop(pFciicMasterHandle);
    }
    else  if ((FCIIC_DMA_NEXT_STAGE_NOTIFICATION == eDmaNextStage) && (FCIIC_CH_CLOSED == eChannelStatus))
    {
        pFciicMasterHandle->tStatus.u8DmaCmdOffset = pFciicMasterHandle->tStatus.u8DmaCmdSize ;
        FCIIC_MasterDmaStageNotification(pFciicMasterHandle);
    }
    else
    {
        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
    }

    if (FCIIC_CH_ERROR_PRESENT == pFciicMasterHandle->tStatus.eChannelStatus)
    {
        u8CurChSts = FCIIC_HWA_GetMSR(pFciic);
        eResult = FCIIC_MasterCheckAndClearError(pFciicMasterHandle, u8CurChSts);
        FCIIC_MasterTransferAbort(pFciicMasterHandle);
        if (NULL != pFciicMasterHandle->tSettings.pErrorCallback)
        {
            pFciicMasterHandle->tSettings.pErrorCallback(pFciicMasterHandle, eResult);
        }
    }
}

/**
 * @brief Initiates a DMA transfer for the FCIIC master.
 *
 * This function starts a DMA transfer by configuring the DMA settings and initiating the transfer process.
 * It checks for valid parameters, ensures the bus is not busy, and configures the DMA accordingly.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 * @param[in] transfer Pointer to the FCIIC master transfer structure containing transfer details.
 *
 * @return FCIIC_StatusType The status of the DMA transfer initiation.
 */
FCIIC_StatusType FCIIC_MasterDmaTransfer(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle || NULL == transfer)
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMATRANSFER_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle != NULL) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERDMATRANSFER_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        if ((NULL != pFciicMasterHandle) && (NULL != transfer) && (pFciicMasterHandle->eInstance < FCIIC_INSTANCE_COUNT))
        {
            pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
            result = FCIIC_MasterCheckForBusyBus(pFciicMasterHandle);
            if ((result == FCIIC_BUSY) || (pFciicMasterHandle->tStatus.bUsed == true) || (FCIIC_CH_IDLE != pFciicMasterHandle->tStatus.eChannelStatus))
            {
                return FCIIC_BUSY;
            }

            if ((NULL != pFciicMasterHandle->tSettings.pFciicRxDmaConfig) && (NULL != pFciicMasterHandle->tSettings.pFciicTxDmaConfig))
            {
                FCIIC_HWA_MasterClearStatusFlags(pFciic, FCIIC_MasterClearFlags);
                FCIIC_HWA_MasterEnableDMA(pFciic, false, false);

                pFciicMasterHandle->tSettings.pData = transfer->pData;
                pFciicMasterHandle->tStatus.u16DataSize = transfer->u16DataSize;
                pFciicMasterHandle->tStatus.eDirection = transfer->eDirection;
                pFciicMasterHandle->tStatus.u16DataOffset = 0;
                pFciicMasterHandle->tStatus.u8DmaCmdSize = 0;
                pFciicMasterHandle->tStatus.u8DmaCmdOffset = 0;
                pFciicMasterHandle->tStatus.bUsed = true;

                FCIIC_MasterDmaStart(pFciicMasterHandle, transfer);
                FCIIC_HWA_MasterEnableDMA(pFciic, true, true);

            }
            else
            {
                result = FCIIC_DMAREQUESTFAIL;
                if (NULL != pFciicMasterHandle->tSettings.pErrorCallback)
                {
                    pFciicMasterHandle->tSettings.pErrorCallback(pFciicMasterHandle, FCIIC_DMAREQUESTFAIL);
                }
            }
        }
        else
        {
            result = FCIIC_FAIL;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}


/**
 * @brief Stops the interrupt process for the FCIIC master.
 *
 * This function disables all interrupts, updates the channel status, and triggers a callback if the data transfer is complete.
 * It also handles error conditions if the data offset does not match the expected size.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessStop(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSSTOP_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle != NULL) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSSTOP_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        /* Disable All interrupts */
        FCIIC_HWA_MasterDisableInterrupts(pFciic, (uint32_t)FCIIC_MasterIrqFlags);

        /* Update channel status */
        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
        pFciicMasterHandle->tStatus.bUsed = false;

        if (pFciicMasterHandle->tStatus.u16DataOffset == pFciicMasterHandle->tStatus.u16DataSize)
        {
            if (NULL != pFciicMasterHandle->tSettings.pCallback)
            {
                pFciicMasterHandle->tSettings.pCallback(pFciicMasterHandle, FCIIC_SUCCESS);
            }
        }
        else
        {
            pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Processes the transmit phase in interrupt mode for the FCIIC master.
 *
 * This function transmits data and updates the data offset. It stops the transfer and updates the channel status when the data transfer is complete.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessTransmit(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSTRANSMIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle != NULL) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSTRANSMIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        uint16 u16CurIdx;
        uint8 u8Data;

        u16CurIdx = pFciicMasterHandle->tStatus.u16DataOffset;

        if (u16CurIdx != pFciicMasterHandle->tStatus.u16DataSize)
        {
            u8Data = pFciicMasterHandle->tSettings.pData[u16CurIdx];
            FCIIC_Master_HWA_Transmit(pFciic, FCIIC_TX_CMD_TRANSMIT, u8Data);
            pFciicMasterHandle->tStatus.u16DataOffset++;

            if (pFciicMasterHandle->tStatus.u16DataOffset == pFciicMasterHandle->tStatus.u16DataSize)
            {
                (void)FCIIC_MasterStop(pFciicMasterHandle);
                /* Update channel status */
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Processes the receive phase in interrupt mode for the FCIIC master.
 *
 * This function receives data and updates the data offset. It stops the transfer and updates the channel status when the data reception is complete.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessReceive(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSRECEIVE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle != NULL) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSRECEIVE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        uint16      u16CurIdx   = pFciicMasterHandle->tStatus.u16DataOffset;

        if (u16CurIdx != pFciicMasterHandle->tStatus.u16DataSize)
        {
            pFciicMasterHandle->tSettings.pData[u16CurIdx] = FCIIC_Master_HWA_Receive(pFciic);
            pFciicMasterHandle->tStatus.u16DataOffset++;

            if (pFciicMasterHandle->tStatus.u16DataOffset == pFciicMasterHandle->tStatus.u16DataSize)
            {
                (void)FCIIC_MasterStop(pFciicMasterHandle);
                pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Processes the start phase in interrupt mode for the FCIIC master.
 *
 * This function manages the command transmission and updates the command offset. It transitions the channel status based on the current phase of the transfer.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_MasterInterruptProcessStart(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicMasterHandle)
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSSTART_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle != NULL) && (pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERINTERRUPTPROCESSSTART_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        FCIIC_ChannelStatusType eChannelStatus = pFciicMasterHandle->tStatus.eChannelStatus;
        uint8 u16CurIdx = pFciicMasterHandle->tStatus.u8CmdOffset;

        if (u16CurIdx != pFciicMasterHandle->tStatus.u8CmdSize)
        {
            FCIIC_Master_HWA_Transmit(pFciic,
                                      pFciicMasterHandle->tStatus.u8Cmd[u16CurIdx],
                                      pFciicMasterHandle->tStatus.u8CmdData[u16CurIdx]);
            pFciicMasterHandle->tStatus.u8CmdOffset++;

            if (pFciicMasterHandle->tStatus.u8CmdOffset == pFciicMasterHandle->tStatus.u8CmdSize)
            {
                if (eChannelStatus == FCIIC_CH_START_WRITE)
                {
                    pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_SENDING;
                }
                else if (eChannelStatus == FCIIC_CH_START_READ)
                {
                    pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_RECEIVING;
                    FCIIC_HWA_MasterDisableInterrupts(pFciic, FCIIC_MIER_TDIE);
                }
                else
                {
                    pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                }
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}
/**
 * @brief Handles the interrupt for the FCIIC master.
 *
 * This function processes various interrupt sources and updates the state of the transfer based on the current channel status.
 * It also handles errors and calls appropriate callbacks.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC master handle.
 */
void FCIIC_LL_MasterIRQnHandler(FCIIC_MasterHandleType *const pFciicMasterHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicMasterHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_LL_MASTERIRQNHANDLER_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_LL_MASTERIRQNHANDLER_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
        uint32_t         u8CurChSts;
        FCIIC_StatusType eResult = FCIIC_SUCCESS;

        FCIIC_ChannelStatusType eChannelStatus = pFciicMasterHandle->tStatus.eChannelStatus;

        u8CurChSts = FCIIC_HWA_GetMSR(pFciic);
        u8CurChSts &= FCIIC_HWA_GetMIER(pFciic);

        if ((0 != (u8CurChSts & FCIIC_MasterErrorFlags)))
        {
            eResult = FCIIC_MasterCheckAndClearError(pFciicMasterHandle, u8CurChSts);
            /* Update channel status */
            pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }
        else if ((0 != (u8CurChSts & FCIIC_MSR_TDF)) && ((eChannelStatus == FCIIC_CH_START_WRITE) || (eChannelStatus == FCIIC_CH_START_READ)))
        {
            FCIIC_MasterInterruptProcessStart(pFciicMasterHandle);
        }
        else if ((0 != (u8CurChSts & FCIIC_MSR_TDF)) && (eChannelStatus == FCIIC_CH_SENDING))
        {
            FCIIC_MasterInterruptProcessTransmit(pFciicMasterHandle);
        }
        else if ((0 != (u8CurChSts & FCIIC_MSR_RDF)) && (eChannelStatus == FCIIC_CH_RECEIVING))
        {
            FCIIC_MasterInterruptProcessReceive(pFciicMasterHandle);
        }
        else if ((0 != (u8CurChSts & FCIIC_MSR_SDF)) && (eChannelStatus == FCIIC_CH_TRANSFER_FINISHED))
        {
            FCIIC_MasterInterruptProcessStop(pFciicMasterHandle);
        }
        else
        {
            FCIIC_Master_HWA_Transmit(pFciic, FCIIC_TX_CMD_STOP, 0U);
            eResult = FCIIC_TRAMSMITORRECEIVEERROR;
            pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }

        if (FCIIC_CH_ERROR_PRESENT == pFciicMasterHandle->tStatus.eChannelStatus)
        {
            FCIIC_MasterTransferAbort(pFciicMasterHandle);
            if (NULL != pFciicMasterHandle->tSettings.pErrorCallback)
            {
                pFciicMasterHandle->tSettings.pErrorCallback(pFciicMasterHandle, eResult);
            }
            pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
            pFciicMasterHandle->tStatus.bUsed = false;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Generates a start command for the FCIIC Master.
 *
 * This function initializes the master for transmission by generating the necessary commands for the start of a transfer.
 *
 * @param[in] pFciicMasterHandle The FCIIC Master Handle.
 * @param[in] transfer Pointer to the `FCIIC_MasterTransferType` structure containing the transfer details.
 * @return void
 */
void FCIIC_MasterGenerateStartCommand(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer)
{
    uint8_t *pSubAddr = (uint8_t *)&transfer->subaddress;
    uint32_t i;

    if (0U != transfer->subaddressSize)
    {
        pFciicMasterHandle->tStatus.u8Cmd[pFciicMasterHandle->tStatus.u8CmdSize] = FCIIC_TX_CMD_STARTANDTRANSMIT;
        pFciicMasterHandle->tStatus.u8CmdData[pFciicMasterHandle->tStatus.u8CmdSize] = (uint8_t)((transfer->u8SlaveAddress << 1) | FCIIC_WRITE);
        pFciicMasterHandle->tStatus.u8CmdSize++;

        for (i = transfer->subaddressSize; i > 0 ; --i)
        {
            pFciicMasterHandle->tStatus.u8Cmd[pFciicMasterHandle->tStatus.u8CmdSize] = FCIIC_TX_CMD_TRANSMIT;
            pFciicMasterHandle->tStatus.u8CmdData[pFciicMasterHandle->tStatus.u8CmdSize] = pSubAddr[i - 1];
            pFciicMasterHandle->tStatus.u8CmdSize++;
        }

        if (FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
        {
            pFciicMasterHandle->tStatus.u8Cmd[pFciicMasterHandle->tStatus.u8CmdSize] = FCIIC_TX_CMD_STARTANDTRANSMIT;
            pFciicMasterHandle->tStatus.u8CmdData[pFciicMasterHandle->tStatus.u8CmdSize] = (uint8_t)((transfer->u8SlaveAddress << 1) | FCIIC_READ);
            pFciicMasterHandle->tStatus.u8CmdSize++;

            pFciicMasterHandle->tStatus.u8Cmd[pFciicMasterHandle->tStatus.u8CmdSize] = FCIIC_TX_CMD_RECEIVE;
            pFciicMasterHandle->tStatus.u8CmdData[pFciicMasterHandle->tStatus.u8CmdSize] = (uint8_t)(transfer->u16DataSize - 1);
            pFciicMasterHandle->tStatus.u8CmdSize++;
        }
    }
    else
    {
        pFciicMasterHandle->tStatus.u8Cmd[pFciicMasterHandle->tStatus.u8CmdSize] = FCIIC_TX_CMD_STARTANDTRANSMIT;
        pFciicMasterHandle->tStatus.u8CmdData[pFciicMasterHandle->tStatus.u8CmdSize] = (uint8_t)((transfer->u8SlaveAddress << 1) | pFciicMasterHandle->tStatus.eDirection);
        pFciicMasterHandle->tStatus.u8CmdSize++;

        if (FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
        {
            pFciicMasterHandle->tStatus.u8Cmd[pFciicMasterHandle->tStatus.u8CmdSize] = FCIIC_TX_CMD_RECEIVE;
            pFciicMasterHandle->tStatus.u8CmdData[pFciicMasterHandle->tStatus.u8CmdSize] = (uint8_t)(transfer->u16DataSize - 1);
            pFciicMasterHandle->tStatus.u8CmdSize++;
        }
    }
}

/**
 * @brief Initiates a non-blocking I2C Master transfer.
 *
 * Sets up and initiates a non-blocking I2C Master transfer, including handling of START, addressing, subaddress (if provided),
 * data transfer, and STOP conditions. Returns immediately after starting the transfer, and the transfer is managed asynchronously
 * using interrupts.
 *
 * @param[in] pFciicMasterHandle Pointer to the FCIIC Master Handle.
 * @param[in] transfer Pointer to the `FCIIC_MasterTransferType` structure containing the transfer details.
 * @return A status code indicating the outcome of the initiation process:
 *         - FCIIC_SUCCESS: The transfer was initiated successfully.
 *         - FCIIC_BSY: Another non-blocking transfer is already in progress.
 *         - Other error codes: Errors encountered during the transfer setup, such as a busy bus.
 */
FCIIC_StatusType FCIIC_MasterTransferNonBlocking(FCIIC_MasterHandleType *const pFciicMasterHandle, FCIIC_MasterTransferType *const transfer)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type *pFciic ;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if ((NULL == pFciicMasterHandle) || (NULL == transfer))
    {
        FCIIC_ReportDevError(FCIIC_MASTERTRANSFERNONBLOCKING_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicMasterHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_MASTERTRANSFERNONBLOCKING_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        if ((NULL != pFciicMasterHandle) && (NULL != transfer) && (pFciicMasterHandle->eInstance < FCIIC_INSTANCE_COUNT))
        {
            pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicMasterHandle->eInstance];
            /* Clear all flags. */
            FCIIC_HWA_MasterClearStatusFlags(pFciic, FCIIC_MasterClearFlags);
            if (pFciicMasterHandle->tStatus.bUsed == true)
            {
                result = FCIIC_BUSY;
            }
            else
            {
                result = FCIIC_MasterCheckForBusyBus(pFciicMasterHandle);
                if ((result == FCIIC_SUCCESS) && (FCIIC_CH_IDLE == pFciicMasterHandle->tStatus.eChannelStatus))
                {
                    /* Clear all flags. */
                    FCIIC_HWA_MasterClearStatusFlags(pFciic, FCIIC_MasterClearFlags);

                    pFciicMasterHandle->tStatus.bUsed = true;
                    pFciicMasterHandle->tStatus.eDirection = transfer->eDirection;
                    pFciicMasterHandle->tSettings.pData = transfer->pData;
                    pFciicMasterHandle->tStatus.u16DataSize = transfer->u16DataSize;
                    pFciicMasterHandle->tStatus.u16DataOffset = 0;
                    pFciicMasterHandle->tStatus.u8CmdSize = 0;
                    pFciicMasterHandle->tStatus.u8CmdOffset = 0;

                    FCIIC_MasterGenerateStartCommand(pFciicMasterHandle, transfer);
                    if (FCIIC_READ == pFciicMasterHandle->tStatus.eDirection)
                    {
                        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_START_READ;
                    }
                    else
                    {
                        pFciicMasterHandle->tStatus.eChannelStatus = FCIIC_CH_START_WRITE;
                    }
                    FCIIC_HWA_MasterEnableInterrupts(pFciic, FCIIC_MasterIrqFlags);
                }
            }
        }
        else
        {
            result = FCIIC_FAIL;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}
/**
 * @brief Initializes the I2C Slave mode.
 *
 * Configures the I2C interface for slave mode operation according to the parameters provided.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave Handle.
 * @param[in] pInitReg Pointer to the `FCIIC_SlaveConfigType` structure containing the initialization settings.
 * @return void
 */
void FCIIC_SlaveInit(FCIIC_SlaveHandleType *const pFciicSlaveHandle,  const FCIIC_SlaveConfigType *pInitReg)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle || NULL == pInitReg)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        uint32 u32TempScr, u32TempScfgr1, u32TempScfgr2, u32TempSamr, u32TempSder;
        FCIIC_Type *pFciic  = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];


        u32TempScr = FCIIC_SCR_SEN(pInitReg->bEnableSlave) |
                     FCIIC_SCR_RST(0U)    |
                     FCIIC_SCR_FILTEN(pInitReg->bI2cSlaveFilterEnable);

        u32TempSder =  FCIIC_SDER_TDDE(pInitReg->bUsedDMA) |
                       FCIIC_SDER_RDDE(pInitReg->bUsedDMA) |
                       FCIIC_SDER_AVDE(0U);

        u32TempSamr = FCIIC_SAMR_ADDR1(0U) |
                      FCIIC_SAMR_ADDR0(pInitReg->slaveAddress);

        u32TempScfgr1 = FCIIC_SCFGR1_ADDRCFG(pInitReg->u8AddrCfg) |
                        FCIIC_SCFGR1_HSMEN(0U)    |
                        FCIIC_SCFGR1_IGNACK(0U)   |
                        FCIIC_SCFGR1_RXCFG(0U)    |
                        FCIIC_SCFGR1_TXCFG(0U)    |
                        FCIIC_SCFGR1_SAEN(0U)     |
                        FCIIC_SCFGR1_GCEN(0U)     |
                        FCIIC_SCFGR1_ACKSTALL(pInitReg->bI2cSlaveAckStall) |
                        FCIIC_SCFGR1_TXDSTALL(pInitReg->bI2cSlaveTxStall) |
                        FCIIC_SCFGR1_RXSTALL(pInitReg->bI2cSlaveRxStall) |
                        FCIIC_SCFGR1_ADRSTALL(pInitReg->bI2cSlaveAdrStall);


        u32TempScfgr2 = FCIIC_SCFGR2_FILTSDA(pInitReg->u8SdaGlitchFilterWidth) |
                        FCIIC_SCFGR2_FILTSCL(pInitReg->u8SclGlitchFilterWidth) |
                        FCIIC_SCFGR2_DATAVD(pInitReg->u32PinLowTimeout) |
                        FCIIC_SCFGR2_CLKHOLD(pInitReg->u32BusIdleTimeout);

        FCIIC_HWA_SetSCR(pFciic, u32TempScr);
        FCIIC_HWA_SetSDER(pFciic, u32TempSder);
        FCIIC_HWA_SetSCFGR1(pFciic, u32TempScfgr1);
        FCIIC_HWA_SetSCFGR2(pFciic, u32TempScfgr2);
        FCIIC_HWA_SetSAMR(pFciic, u32TempSamr);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief De-initializes the IIC Slave mode.
 *
 * This function de-initializes the IIC Slave mode by resetting the handle and disabling the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the slave handle structure.
 * @param[in] transfer Pointer to the I2C transfer parameters.
 *
 * @return FCIIC_StatusType indicating the status of the operation.
 */
FCIIC_StatusType FCIIC_Slavelistening(FCIIC_SlaveHandleType *const pFciicSlaveHandle, FCIIC_SlaveTransferType *const transfer)
{
    FCIIC_StatusType eRetType;
    uint32 u32I2cSlaveDmaStatus, u8CurChSts;
    FCIIC_Type *pFciic;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle || NULL == transfer)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        if ((NULL != pFciicSlaveHandle) && (NULL != transfer))
        {
            pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
            u8CurChSts = FCIIC_HWA_GetSSR(pFciic);
            eRetType = FCIIC_SlaveCheckForBusyBus(pFciicSlaveHandle);
            eRetType |= FCIIC_SlaveCheckAndClearError(pFciicSlaveHandle, u8CurChSts);

            if ((FCIIC_SUCCESS == eRetType) && (FCIIC_CH_IDLE == pFciicSlaveHandle->tStatus.eChannelStatus))
            {
                pFciicSlaveHandle->tStatus.u16DataSize = transfer->u16DataSize;
                pFciicSlaveHandle->tSettings.pData = transfer->pData;
                pFciicSlaveHandle->tStatus.u16DataOffset = 0;
                pFciicSlaveHandle->tStatus.curSubaddressSize = 0;
                pFciicSlaveHandle->tStatus.subaddressSize = transfer->subaddressSize;
                FCIIC_Slave_HWA_EnableInterrupt(pFciic, FCIIC_SIER_TREIE | FCIIC_SIER_BEIE);

                u32I2cSlaveDmaStatus = FCIIC_HWA_GetSDER(pFciic);
                /* DMA Priority*/
                if ((u32I2cSlaveDmaStatus == (uint32)0x0u) && ((NULL == pFciicSlaveHandle->tSettings.pFciicTxDmaConfig) && (NULL == pFciicSlaveHandle->tSettings.pFciicRxDmaConfig)))
                {
                    eRetType = FCIIC_SlaveTransferNonBlocking(pFciicSlaveHandle);
                }
                else if ((u32I2cSlaveDmaStatus == (uint32)0x3u) && ((NULL != pFciicSlaveHandle->tSettings.pFciicTxDmaConfig) && (NULL != pFciicSlaveHandle->tSettings.pFciicRxDmaConfig)))
                {
                    eRetType = FCIIC_SlaveTransferDMA(pFciicSlaveHandle);
                }
                else
                {
                    eRetType = FCIIC_FAIL;
                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                }
            }
            else
            {
                if (NULL != pFciicSlaveHandle->tSettings.pErrorCallback)
                {
                    pFciicSlaveHandle->tSettings.pErrorCallback(pFciicSlaveHandle);
                }
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
            }
        }
        else
        {
            eRetType = FCIIC_FAIL;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return eRetType;
}

/**
 * @brief Deinitializes the FCIIC slave configuration.
 *
 * This function resets the FCIIC slave peripheral to its default state.
 * It disables the FCIIC slave, clears all registers, and disables interrupts.
 *
 * @param pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveDeInit(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    uint32 u32PccCgcMask = 0x40000000U;
    uint32 u32PccSelMask = 0x7000000U;
    uint32 u32PccBase = 0x40065000U;
    uint32 u32IICPccRegOffset[2] = {0x198U, 0x19CU};
    FCIIC_Type *const pFciic = s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
    uint32 u32TempScr, u32TempSder, u32TempPcc;

    u32TempScr = FCIIC_SCR_FILTEN(0U)    |
                 FCIIC_SCR_RST(0U)      |
                 FCIIC_SCR_SEN(0U);         /* slave enable */

    u32TempSder = FCIIC_SDER_AVDE(0U) |
                 FCIIC_SDER_RDDE(0U) |
                 FCIIC_SDER_TDDE(0U);

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEDEINIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEDEINIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif

        FCIIC_Slave_HWA_DisableInterrupt(pFciic, FCIIC_SIER_MASK);
        FCIIC_HWA_SetSDER(pFciic, u32TempSder);
        
        /* PRQA S 0306 ++ #Misra-C:2012 Rule-11.4 A conversion should not be performed between a pointer to object and an integer type
        * Reason: Pointer to register addressing map operation could not be avoid */
        u32TempPcc = *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicSlaveHandle->eInstance]));
        /*   Disable PCC gate    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicSlaveHandle->eInstance])) = (uint32)(u32TempPcc & (~u32PccCgcMask));
        /*   Disable function clock    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicSlaveHandle->eInstance])) = (uint32)(u32TempPcc & (~u32PccSelMask));

        FCIIC_HWA_SetSCR(pFciic, FCIIC_SCR_RST(1U));
        FCIIC_HWA_SetSCR(pFciic, u32TempScr);

        /*   Disable PCC gate    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicSlaveHandle->eInstance])) = (uint32)(u32TempPcc & (~u32PccCgcMask));
        /*   Recover function clock    */
        *((volatile uint32 *)(u32PccBase + u32IICPccRegOffset[pFciicSlaveHandle->eInstance])) = u32TempPcc;
        /* PRQA S 0306 -- */
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Deinitializes the FCIIC slave handle.
 *
 * This function resets the FCIIC slave handle to its default state.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveDeinitHandle(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEDEINITHANDLE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        pFciicSlaveHandle->tStatus.u16DataSize = 0;
        pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
        pFciicSlaveHandle->tSettings.pData = NULL;
        pFciicSlaveHandle->tStatus.u16DataOffset = 0;
        pFciicSlaveHandle->tStatus.bUsed     = false;
        pFciicSlaveHandle->tStatus.eRunStatus = FCIIC_SUCCESS;
        pFciicSlaveHandle->tStatus.subaddressSize = 0;
        pFciicSlaveHandle->tStatus.u32CurSubaddress = 0;
        pFciicSlaveHandle->tStatus.u32Subaddress = 0;
        pFciicSlaveHandle->tSettings.pCallback = NULL;
        pFciicSlaveHandle->tSettings.pUserData = NULL;
        pFciicSlaveHandle->tSettings.pErrorCallback = NULL;
        pFciicSlaveHandle->tSettings.pFciicTxDmaConfig = NULL;
        pFciicSlaveHandle->tSettings.pFciicRxDmaConfig = NULL;
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Sends an ACK/NACK signal in IIC Slave mode.
 *
 * This function sends an ACK or NACK signal based on the input parameter.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] bAck Boolean flag to indicate whether to send ACK (true) or NACK (false).
 */
void  FCIIC_SlaveAck(FCIIC_SlaveHandleType *const pFciicSlaveHandle, boolean bAck)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEACK_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        if ((boolean)TRUE == bAck)
        {
            FCIIC_Slave_HWA_NACK(pFciic, FCIIC_STAR_TXNACK(0U));
        }
        else
        {
            FCIIC_Slave_HWA_NACK(pFciic, FCIIC_STAR_TXNACK(1U));
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Clears the I2C master status flag state.
 *
 * This function clears the status flags of the I2C master.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveClrStatus(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVECLRSTATUS_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic  = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];

        FCIIC_Slave_HWA_ClrStatus(pFciic, FCIIC_SSR_MASK);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Gets the slave SSR status.
 *
 * This function retrieves the current status of the slave SSR register.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return The current SSR status as a 32-bit unsigned integer.
 */
uint32_t FCIIC_SlaveGetStatus(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    uint32_t u32Status;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEGETSTATUS_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic  = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        u32Status = FCIIC_HWA_GetSSR(pFciic);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return u32Status;
}


/**
 * @brief Enables the interrupt for the specified FCIIC Slave instance.
 *
 * This function configures the interrupt system to handle non-blocking transfers for the given FCIIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] pCallback Pointer to a callback function that will be invoked when a non-blocking transfer completes.
 * @param[in] pErrorCallBack Pointer to a callback function that will be invoked when an error occurs.
 * @param[in] pUserData Pointer to user-defined data that will be passed back to the callback function when it is called.
 */
void FCIIC_SlaveEnableInterrupt(FCIIC_SlaveHandleType *const pFciicSlaveHandle,
                                FCIIC_SlaveTransfer_CallbackType pCallback, FCIIC_SlaveError_CallBackType pErrorCallBack, void *pUserData)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEENABLEINTERRUPT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        pFciicSlaveHandle->tSettings.pCallback = pCallback;
        pFciicSlaveHandle->tSettings.pUserData = pUserData;
        pFciicSlaveHandle->tSettings.pErrorCallback = pErrorCallBack;
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Checks if the FCIIC bus is busy.
 *
 * This function determines if the FCIIC bus is currently busy.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return FCIIC_StatusType indicating the bus status.
 */
FCIIC_StatusType FCIIC_SlaveCheckForBusyBus(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    FCIIC_StatusType ret = FCIIC_SUCCESS;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEGETSTATUS_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];

        uint32_t status = FCIIC_HWA_GetSSR(pFciic);

        if (0U != (status & (uint32_t)FCIIC_SSR_BBF))
        {
            ret = FCIIC_BUSY;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return ret;
}

/**
 * @brief Checks for and clears I2C Slave errors.
 *
 * This function checks the provided status register for any I2C Slave errors and clears them.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] status The current status register value.
 *
 * @return FCIIC_StatusType indicating the encountered error or FCIIC_SUCCESS if no error is found.
 */
FCIIC_StatusType FCIIC_SlaveCheckAndClearError(FCIIC_SlaveHandleType *const pFciicSlaveHandle, uint32_t status)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;

    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVECHECKANDCLEARERROR_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];

        status &= (uint32_t)FCIIC_SlaveErrorFlags;
        if (0U != status)
        {
            /* Select the correct error code. Ordered by severity, with bus issues first. */
            if (0U != (status & (uint32_t)FCIIC_SSR_TREF))
            {
                result = FCIIC_TRAMSMITORRECEIVEERROR;
            }
            else if (0U != (status & (uint32_t)FCIIC_SSR_BEF))
            {
                result = FCIIC_BITERROR;
            }
            else
            {

            }
        }
        /* Clear the flags. */
        FCIIC_Slave_HWA_ClrStatus(pFciic, status);

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Sets the default configuration for the I2C Slave.
 *
 * This function sets the default configuration parameters for the I2C Slave.
 *
 * @param[in] slaveConfig Pointer to the configuration structure.
 * @param[in] bUsedDMA Boolean flag indicating whether DMA is used.
 */
void FCIIC_SlaveGetDefaultConfig(FCIIC_SlaveConfigType *const slaveConfig, boolean bUsedDMA)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == slaveConfig)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEGETDEFAULTCONFIG_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else
    {
    #endif
        slaveConfig->bEnableSlave = true;                 /*!< Enables Slave mode if set to true. */
        slaveConfig->bI2cSlaveFilterEnable = false;         /*!< Enables Slave mode if set to true. */
        slaveConfig->bUsedDMA = bUsedDMA;
        slaveConfig->u8AddrCfg = 0;
        slaveConfig->bI2cSlaveAdrStall = false;
        slaveConfig->bI2cSlaveAckStall = false;
        slaveConfig->bI2cSlaveTxStall = false;
        slaveConfig->bI2cSlaveRxStall = false;
        slaveConfig->u32BusIdleTimeout = 0U;        /*!< Bus idle timeout in nanoseconds. Set to 0 to disable timeout. */
        slaveConfig->u32PinLowTimeout = 0;         /*!< Pin low timeout in nanoseconds. Set to 0 to disable timeout. */
        slaveConfig->u8SdaGlitchFilterWidth = 0;   /*!< Width of the SDA glitch filter in nanoseconds. Set to 0 to disable. */
        slaveConfig->u8SclGlitchFilterWidth = 0;

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Receives data in IIC Slave mode.
 *
 * This function receives data when polling (not used when RX interrupt is enabled) in Slave mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[out] pData Pointer to the data buffer where the received data will be stored.
 *
 * @return 0 if successful, non-zero otherwise.
 */
uint8_t FCIIC_SlaveReceive(FCIIC_SlaveHandleType *const pFciicSlaveHandle, uint8_t *pData)
{
    uint8_t     u8RetVal;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVERECEIVE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVERECEIVE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type  *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];

        /* check slave receive flag */
        u8RetVal = FCIIC_Slave_HWA_GetStatus(pFciic, FCIIC_SSR_RDF_STATUS);

        /* u8RetVal = (pFciic->MRDR & FCIIC_MRDR_RXEMPTY_MASK)>>FCIIC_MRDR_RXEMPTY_SHIFT; */

        if (u8RetVal != 0U)
        {
            /* get received data */
            (*pData) = FCIIC_Slave_HWA_Receive(pFciic);
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return (uint8_t)(1U >> u8RetVal);
}

/**
 * @brief Gets the slave error value.
 *
 * This function retrieves the current error value of the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return The current error value as a 32-bit unsigned integer.
 */
uint32_t FCIIC_SlaveGetError(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    uint32_t     u32RetVal;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEGETERROR_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEGETERROR_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type  *pFciic;

        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];

        /* check receive flag */
        u32RetVal = FCIIC_Slave_HWA_GetErrorFlag(pFciic);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return u32RetVal;
}

/**
 * @brief Clears the slave error value.
 *
 * This function clears the error value of the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 */
void FCIIC_SlaveClrError(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVECLRERROR_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVECLRERROR_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type  *pFciic;

        pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];

        /* clear receive flag */
        FCIIC_Slave_HWA_ClrErrorFlag(pFciic);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Gets the current direction of the slave.
 *
 * This function retrieves the current direction (read/write) of the slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 *
 * @return The current direction as an FCIIC_DirectionType enum value.
 */
FCIIC_DirectionType FCIIC_SlaveGetDir(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    FCIIC_DirectionType direction;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEGETDIR_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEGETDIR_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        direction = (FCIIC_DirectionType)(FCIIC_HWA_GetSASR(pFciic) & 0x1);
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return direction;
}



/**
 * @brief Processes the IIC Slave AM0F interrupt.
 *
 * This function processes the Address Match 0 Flag interrupt for the IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] u32IsrStatus The status of the SSR flags.
 */
void FCIIC_SlaveInterruptProcessAddressMatch(FCIIC_SlaveHandleType *const pFciicSlaveHandle, uint32 u32IsrStatus)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSADDRESSMATCH_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSADDRESSMATCH_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type  *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        FCIIC_ChannelStatusType u8CurChSts;
        uint32 u32I2cSlaveDmaStatus = FCIIC_HWA_GetSDER(pFciic);
        uint32 u32Raddr = FCIIC_HWA_GetSASR(pFciic);
        u8CurChSts = pFciicSlaveHandle->tStatus.eChannelStatus;

        /*subAddressSize !=0x00u,only support Interrupt*/
        if (((uint8)0X0U != pFciicSlaveHandle->tStatus.subaddressSize) && ((uint32)0x0U == u32I2cSlaveDmaStatus))
        {
            if ((0 != (u32IsrStatus & FCIIC_SSR_AM0F_MASK)))
            {
                /*firstly match device address when the master want to read and */
                if ((FCIIC_CH_LISTENING == u8CurChSts || FCIIC_CH_IDLE == u8CurChSts) && (pFciicSlaveHandle->tStatus.curSubaddressSize != pFciicSlaveHandle->tStatus.subaddressSize))
                {
                    if ((FCIIC_WRITE == (u32Raddr & FCIIC_DIR_MASK)))
                    {
                        FCIIC_Slave_HWA_EnableInterrupt(pFciic,  FCIIC_SIER_RDIE_MASK);
                        FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
                        pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_LISTENING_READ;
                    }
                    else
                    {
                        FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)FALSE);
                        pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_DIRECTIONERROR;
                        pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                    }
                }
                /*secondly match adddress when the master read and subAddressSize more than 0*/
                else  if ((FCIIC_CH_LISTENING_READ == u8CurChSts) && (pFciicSlaveHandle->tStatus.curSubaddressSize == pFciicSlaveHandle->tStatus.subaddressSize))
                {
                    if ((FCIIC_READ == (u32Raddr & FCIIC_DIR_MASK)) && ((boolean)TRUE == pFciicSlaveHandle->tStatus.bIsGenRsf))
                    {
                        FCIIC_Slave_HWA_Transmit(pFciic,  pFciicSlaveHandle->tSettings.pData[pFciicSlaveHandle->tStatus.u16DataOffset]);
                        pFciicSlaveHandle->tStatus.u16DataOffset++;
                        FCIIC_Slave_HWA_EnableInterrupt(pFciic,  FCIIC_SIER_TDIE);
                        pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_SENDING;
                    }
                    else
                    {
                        if (FCIIC_READ != (u32Raddr & FCIIC_DIR_MASK))
                        {
                            pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_DIRECTIONERROR;
                        }
                        if (((boolean)TRUE != pFciicSlaveHandle->tStatus.bIsGenRsf))
                        {
                            pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_REPEATEDSTARTERROR;
                        }
                        pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                    }
                }
                else
                {
                    pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_STATEMACHINEERROR;
                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                }
            }
            /*secondly detect start signal when the master read and subAddressSize more than 0*/
            else if ((0U != (u32IsrStatus & FCIIC_SSR_RSF)))
            {
                FCIIC_Slave_HWA_ClearStatus(pFciic, FCIIC_SSR_RSF_STATUS);
                if (((boolean)FALSE == pFciicSlaveHandle->tStatus.bIsGenRsf) && (FCIIC_CH_LISTENING_READ == u8CurChSts) &&
                    (pFciicSlaveHandle->tStatus.curSubaddressSize == pFciicSlaveHandle->tStatus.subaddressSize))
                {
                    pFciicSlaveHandle->tStatus.u16DataOffset = (uint16)(pFciicSlaveHandle->tStatus.u32CurSubaddress);
                    /*if SCFGR1_TXCFG=1 , firstly transmit one byte. */
                    if ((uint32)0x0u != (FCIIC_HWA_GetSCFGR1(pFciic)&FCIIC_SCFGR1_TXCFG_MASK))
                    {
                        FCIIC_Slave_HWA_Transmit(pFciic,  pFciicSlaveHandle->tSettings.pData[0]);
                        pFciicSlaveHandle->tStatus.u16DataOffset++;
                    }
                    pFciicSlaveHandle->tStatus.bIsGenRsf = (boolean)TRUE;
                }
                else
                {
                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                }
            }
            else
            {
                pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_STATEMACHINEERROR;
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            }
        }
        /*subAddressSize ==0x00u,for support Interrupt*/
        else if (((uint32)0x0U == u32I2cSlaveDmaStatus) && ((uint8)0X0U == pFciicSlaveHandle->tStatus.subaddressSize))
        {
            /*slave interrupt and subAddressSize=0 */
            if ((FCIIC_CH_LISTENING == u8CurChSts || FCIIC_CH_IDLE == u8CurChSts))
            {
                FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
                if ((FCIIC_READ == (u32Raddr & FCIIC_DIR_MASK)))
                {
                    FCIIC_Slave_HWA_Transmit(pFciic,  pFciicSlaveHandle->tSettings.pData[pFciicSlaveHandle->tStatus.u16DataOffset]);
                	pFciicSlaveHandle->tStatus.u16DataOffset++;
                    pFciicSlaveHandle->tStatus.eChannelStatus  = FCIIC_CH_SENDING;
                    FCIIC_Slave_HWA_EnableInterrupt(pFciic,  FCIIC_SIER_TDIE_MASK);
                }
                else if ((FCIIC_WRITE == (u32Raddr & FCIIC_DIR_MASK)))
                {
                    pFciicSlaveHandle->tStatus.eChannelStatus  = FCIIC_CH_RECEIVING;
                    FCIIC_Slave_HWA_EnableInterrupt(pFciic,  FCIIC_SIER_RDIE_MASK);
                }
                else
                {
                    pFciicSlaveHandle->tStatus.eChannelStatus  = FCIIC_CH_ERROR_PRESENT;
                }
            }
            else
            {
                pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_STATEMACHINEERROR;
                pFciicSlaveHandle->tStatus.eChannelStatus  = FCIIC_CH_ERROR_PRESENT;
                FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)FALSE);
            }
        }
        /*subAddressSize ==0x00u DMA tx rx ENABLE,for DMA Interrupt*/
        //        else if (((uint8)0X0U == pFciicSlaveHandle->tStatus.subaddressSize) && ((uint32)0x3U == u32I2cSlaveDmaStatus))
        //        {
        //            FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
        //            if ((FCIIC_CH_LISTENING == u8CurChSts || FCIIC_CH_IDLE == u8CurChSts) && ((uint32)0X0U != u32I2cSlaveDmaStatus))
        //            {
        //                if ((FCIIC_WRITE == (u32Raddr & FCIIC_DIR_MASK)) && (0U != (FCIIC_SDER_RDDE_MASK & u32I2cSlaveDmaStatus)))
        //                {
        //                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_RECEIVING;
        //                    pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_DATA;
        //                    DMA_StartChannel(pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->pDmaHandle);
        //                }
        //                else if ((FCIIC_READ == (u32Raddr & FCIIC_DIR_MASK)) && (0U != (FCIIC_SDER_TDDE_MASK & u32I2cSlaveDmaStatus)))
        //                {
        //                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_SENDING;
        //                    pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_DATA;
        //                    DMA_StartChannel(pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->pDmaHandle);
        //                }
        //                else
        //                {
        //                    pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_STATEMACHINEERROR;
        //                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        //                }
        //            }
        //        }
        /*unknown error */
        else
        {
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Processes the IIC Slave RDF interrupt.
 *
 * This function processes the Receive Data Flag interrupt for the IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC slave handle structure.
 * @param[in] u8CurChSts The status of the SSR flags.
 */
void FCIIC_SlaveInterruptProcessReceive(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSRECEIVE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSRECEIVE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        uint16 u16CurIdx;
        uint8 u8SubAddrTotalLen;
        uint8 u8SubAddrCurIdx;
        uint8 u8ShiftWidth;
        uint8 u8Data;

        u8SubAddrTotalLen = pFciicSlaveHandle->tStatus.subaddressSize;
        u8SubAddrCurIdx   = pFciicSlaveHandle->tStatus.curSubaddressSize;
        u16CurIdx = pFciicSlaveHandle->tStatus.u16DataOffset;

        if (0x0U != pFciicSlaveHandle->tStatus.subaddressSize)
        {
            /*If the subaddress is fully received, change the state machine to FCIIC_CH_RECEIVING to prepare to send data */
            if ((FCIIC_CH_LISTENING_READ == pFciicSlaveHandle->tStatus.eChannelStatus) && (pFciicSlaveHandle->tStatus.curSubaddressSize == pFciicSlaveHandle->tStatus.subaddressSize))
            {
                pFciicSlaveHandle->tStatus.u16DataOffset = (uint16)(pFciicSlaveHandle->tStatus.u32CurSubaddress);
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_RECEIVING;
            }
            /*receive subAddress data*/
            if ((FCIIC_CH_LISTENING_READ == pFciicSlaveHandle->tStatus.eChannelStatus) && (u8SubAddrCurIdx < u8SubAddrTotalLen))
            {
                u8ShiftWidth = (uint8)((u8SubAddrTotalLen - u8SubAddrCurIdx - (uint8) 0X1U) << 0x3U);
                u8Data = FCIIC_Slave_HWA_Receive(pFciic);
                pFciicSlaveHandle->tStatus.u32CurSubaddress |= (uint32)(u8Data << u8ShiftWidth);
                pFciicSlaveHandle->tStatus.curSubaddressSize = (uint8)(pFciicSlaveHandle->tStatus.curSubaddressSize + 1u);
                if ((pFciicSlaveHandle->tStatus.curSubaddressSize == pFciicSlaveHandle->tStatus.subaddressSize))
                {
                    FCIIC_Slave_HWA_EnableInterrupt(pFciic, FCIIC_SIER_RSIE_MASK);
                }
                FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
            }
            /*receive data */
            else if ((FCIIC_CH_RECEIVING == pFciicSlaveHandle->tStatus.eChannelStatus) && (u8SubAddrCurIdx == u8SubAddrTotalLen))
            {
            	u16CurIdx = pFciicSlaveHandle->tStatus.u16DataOffset;
                FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
                if (u16CurIdx < pFciicSlaveHandle->tStatus.u16DataSize)
                {
                    pFciicSlaveHandle->tSettings.pData[u16CurIdx] =  FCIIC_Slave_HWA_Receive(pFciic);
                    pFciicSlaveHandle->tStatus.u16DataOffset = (uint16)(u16CurIdx + 1u);
                }
                else
                {
                    pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_OVERFLOWERROR;
                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                }
            }
            else
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                (void)FCIIC_Slave_HWA_Receive(pFciic);
                FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)FALSE);
            }
        }
        else
        {
            if ((FCIIC_CH_RECEIVING == pFciicSlaveHandle->tStatus.eChannelStatus))
            {
                FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
                if (u16CurIdx < pFciicSlaveHandle->tStatus.u16DataSize)
                {
                    pFciicSlaveHandle->tSettings.pData[u16CurIdx] = FCIIC_Slave_HWA_Receive(pFciic);
                    pFciicSlaveHandle->tStatus.u16DataOffset = (uint16)(u16CurIdx + 1u);
                }
                else
                {
                    pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_OVERFLOWERROR;
                    pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                }
            }
            else
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                (void)FCIIC_Slave_HWA_Receive(pFciic);
                FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)FALSE);
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Processes IIC Slave TDF interrupt.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveInterruptProcessTransmit(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSTRANSMIT_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSTRANSMIT_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        uint16 u16CurIdx = pFciicSlaveHandle->tStatus.u16DataOffset;

        if ((FCIIC_CH_SENDING == pFciicSlaveHandle->tStatus.eChannelStatus))
        {
            if (u16CurIdx <= pFciicSlaveHandle->tStatus.u16DataSize)
            {
                FCIIC_Slave_HWA_Transmit(pFciic,  pFciicSlaveHandle->tSettings.pData[u16CurIdx]);
                pFciicSlaveHandle->tStatus.u16DataOffset = (uint16)(u16CurIdx + 1u);
            }
            else
            {
                pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_OVERFLOWERROR;
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            }
        }
        else
        {
            FCIIC_Slave_HWA_Transmit(pFciic, 0x00);
            pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_STATEMACHINEERROR;
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }

        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Processes IIC Slave SDF interrupt.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveInterruptProcessStop(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSSTOP_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEINTERRUPTPROCESSSTOP_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        FCIIC_ChannelStatusType eChannelStatus = pFciicSlaveHandle->tStatus.eChannelStatus;

        FCIIC_Slave_HWA_ClrStatus(pFciic, FCIIC_SSR_SDF_STATUS);
        if (eChannelStatus == FCIIC_CH_SENDING || eChannelStatus == FCIIC_CH_RECEIVING)
        {
            /*Interrupt receive Successfully*/
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
        }
        else
        {
            pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_STATEMACHINEERROR;
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }

        if ((FCIIC_CH_TRANSFER_FINISHED == pFciicSlaveHandle->tStatus.eChannelStatus))
        {
            if (NULL != pFciicSlaveHandle->tSettings.pCallback)
            {
                pFciicSlaveHandle->tSettings.pCallback(pFciicSlaveHandle);
            }
            if (0 != pFciicSlaveHandle->tStatus.subaddressSize)
            {
                pFciicSlaveHandle->tSettings.pData = NULL;
                pFciicSlaveHandle->tStatus.u32CurSubaddress = 0;
                pFciicSlaveHandle->tStatus.bIsGenRsf = false;
                pFciicSlaveHandle->tStatus.curSubaddressSize = 0;
            }
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
            pFciicSlaveHandle->tStatus.u16DataOffset = 0;
            pFciicSlaveHandle->tStatus.eRunStatus = FCIIC_SUCCESS;
            FCIIC_Slave_HWA_DisableInterrupt(pFciic, FCIIC_SIER_RDIE | FCIIC_SIER_TDIE);
        }
        else
        {
            if (NULL != pFciicSlaveHandle->tSettings.pErrorCallback)
            {
                pFciicSlaveHandle->tSettings.pErrorCallback(pFciicSlaveHandle);
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}


/**
 * @brief I2C Slave Interrupt Service Routine (ISR).
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_LL_SlaveIRQnHandler(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (pFciicSlaveHandle == NULL)
    {
        FCIIC_ReportDevError(FCIIC_LL_SLAVEIRQNHANDLER_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_LL_SLAVEIRQNHANDLER_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        uint32_t         u8CurChSts,  u32I2cSlaveDmaStatus;
        FCIIC_Type       *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        uint32_t u32ErrorValue;
        u8CurChSts = FCIIC_HWA_GetSSR(pFciic);
        u8CurChSts &= FCIIC_HWA_GetSIER(pFciic);
        u32I2cSlaveDmaStatus = FCIIC_HWA_GetSDER(pFciic);
        if (0 != (u8CurChSts & FCIIC_SlaveErrorFlags))
        {
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }
        else if (((uint32_t)0x03 != u32I2cSlaveDmaStatus))
        {
            if (0 != (u8CurChSts & FCIIC_SSR_AM0F) || (0 != (u8CurChSts & FCIIC_SSR_RSF)))
            {
                FCIIC_SlaveInterruptProcessAddressMatch(pFciicSlaveHandle, u8CurChSts);
            }
            else if ((0 != (u8CurChSts & FCIIC_SSR_RDF)))
            {
                FCIIC_SlaveInterruptProcessReceive(pFciicSlaveHandle);
            }
            else if ((0 != (u8CurChSts & FCIIC_SSR_TDF)))
            {
                FCIIC_SlaveInterruptProcessTransmit(pFciicSlaveHandle);
            }
            else if ((0 != (u8CurChSts & FCIIC_SSR_SDF)))
            {
                FCIIC_SlaveInterruptProcessStop(pFciicSlaveHandle);
            }
            else
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            }
        }
        else if ((u32I2cSlaveDmaStatus==0x03)&&((NULL != pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->pDmaHandle)) && (NULL != pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->pDmaHandle))
        {
            if (0 != (u8CurChSts & FCIIC_SSR_AM0F))
            {
                FCIIC_SlaveStartDMA(pFciicSlaveHandle);
            }
            else if (0 != (u8CurChSts & FCIIC_SSR_SDF))
            {
                FCIIC_SlaveDMAStageNotification(pFciicSlaveHandle);
            }
            else
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            }
        }
        else
        {
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }

        if (FCIIC_CH_ERROR_PRESENT == pFciicSlaveHandle->tStatus.eChannelStatus)
        {
            u32ErrorValue = FCIIC_SlaveGetError(pFciicSlaveHandle);
            if ((u32ErrorValue != 0U))
            {
                FCIIC_SlaveClrError(pFciicSlaveHandle);
            }
            if ((NULL != pFciicSlaveHandle->tSettings.pErrorCallback))
            {
                pFciicSlaveHandle->tSettings.pErrorCallback(pFciicSlaveHandle);
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Starts accepting slave transfers in non-blocking mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 *
 * @return FCIIC_StatusType Status indicating whether the start was successful.
 */
FCIIC_StatusType FCIIC_SlaveTransferNonBlocking(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    FCIIC_StatusType result = FCIIC_SUCCESS;
    FCIIC_Type  *pFciic;
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVETRANSFERNONBLOCKING_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVETRANSFERNONBLOCKING_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        if ((NULL != pFciicSlaveHandle) && (pFciicSlaveHandle->eInstance < FCIIC_INSTANCE_COUNT))
        {
            pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
            if (true == pFciicSlaveHandle->tStatus.bUsed) /* Check if the I2C bus is idle - if not return busy status. */
            {
                result = FCIIC_BUSY;
            }
            else
            {
                pFciicSlaveHandle->tStatus.bUsed = true;
                FCIIC_Slave_HWA_DisableInterrupt(pFciic, FCIIC_SlaveIrqFlags);
                FCIIC_Slave_HWA_ClrStatus(pFciic, FCIIC_SlaveClearFlags);
                FCIIC_Slave_HWA_EnableInterrupt(pFciic, FCIIC_SIER_AM0IE | FCIIC_SIER_SDIE); /* Enable I2C internal IRQ sources */
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_LISTENING;
            }
        }
        else
        {
            result = FCIIC_FAIL;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return result;
}

/**
 * @brief Prepares DMA configuration for IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */

void FCIIC_SlaveDmaPrepare(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEDMAPREPARE_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((NULL != pFciicSlaveHandle) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEDMAPREPARE_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        DMA_HandleType *pDmaHandle = NULL;
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        DMA_ChannelCfgType FCIIC_DmaChannelAttr = {0};

        FCIIC_DmaChannelAttr.eSrcDataSize          = DMA_TRANSFER_SIZE_1B;
        FCIIC_DmaChannelAttr.eDestDataSize         = DMA_TRANSFER_SIZE_1B;
        FCIIC_DmaChannelAttr.u32BlockSize          = 1;
        FCIIC_DmaChannelAttr.u16BlockCount         = pFciicSlaveHandle->tStatus.u16DataSize;

        FCIIC_DmaChannelAttr.bSrcBlockOffsetEn     = false;
        FCIIC_DmaChannelAttr.bDestBlockOffsetEn    = false;
        FCIIC_DmaChannelAttr.s32BlockOffset        = 0;
        FCIIC_DmaChannelAttr.bSrcAddrLoopbackEn    = true;
        FCIIC_DmaChannelAttr.bDestAddrLoopbackEn   = false;
        FCIIC_DmaChannelAttr.bAutoStop             = true;
        FCIIC_DmaChannelAttr.bSrcCircularBufferEn  = false;
        FCIIC_DmaChannelAttr.u32SrcCircBufferSize  = 0;
        FCIIC_DmaChannelAttr.bDestCircularBufferEn = false;
        FCIIC_DmaChannelAttr.u32DestCircBufferSize = 0;

        FCIIC_DmaChannelAttr.bTransferCompleteIntEn  = true;
        FCIIC_DmaChannelAttr.bTransferErrorIntEn     = false;
        FCIIC_DmaChannelAttr.pTransferErrorNotify    = NULL;
        FCIIC_DmaChannelAttr.completedata            = NULL;
        FCIIC_DmaChannelAttr.errdata                 = NULL;

        if (NULL != pFciicSlaveHandle->tSettings.pFciicTxDmaConfig)
        {
            FCIIC_DmaChannelAttr.pSrcBuffer            = &(pFciicSlaveHandle->tSettings.pData[0]);
            FCIIC_DmaChannelAttr.pDestBuffer           = &(pFciic->STDR);
            FCIIC_DmaChannelAttr.eSrcIncMode           = DMA_INCREMENT_DATA_SIZE ;
            FCIIC_DmaChannelAttr.eDestIncMode          = DMA_INCREMENT_DISABLE;
            pDmaHandle                                 = pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->pDmaHandle;
            FCIIC_DmaChannelAttr.u8ChannelPriority     = pDmaHandle->tSettings.u8Channel;
            FCIIC_DmaChannelAttr.pTransferCompleteNotify = pDmaHandle->tSettings.callback.pTransferCompleteCallback;

            if (FCIIC_INSTANCE_0 == pFciicSlaveHandle->eInstance)
            {
                FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC0_TX;
            }
            else
            {
                FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC1_TX;
            }
            DMA_InitChannel(pDmaHandle, &FCIIC_DmaChannelAttr);
            pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage=FCIIC_DMA_NEXT_STAGE_IDLE;
        }

        if (NULL != pFciicSlaveHandle->tSettings.pFciicRxDmaConfig)
        {
            FCIIC_DmaChannelAttr.pSrcBuffer            = &(pFciic->SRDR);
            FCIIC_DmaChannelAttr.pDestBuffer           = &(pFciicSlaveHandle->tSettings.pData[0]);
            FCIIC_DmaChannelAttr.eSrcIncMode           = DMA_INCREMENT_DISABLE ;
            FCIIC_DmaChannelAttr.eDestIncMode          = DMA_INCREMENT_DATA_SIZE;
            pDmaHandle                                 = pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->pDmaHandle;
            FCIIC_DmaChannelAttr.u8ChannelPriority     = pDmaHandle->tSettings.u8Channel;
            FCIIC_DmaChannelAttr.pTransferCompleteNotify = pDmaHandle->tSettings.callback.pTransferCompleteCallback;
            if (FCIIC_INSTANCE_0 == pFciicSlaveHandle->eInstance)
            {
                FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC0_RX;
            }
            else
            {
                FCIIC_DmaChannelAttr.eTriggerSrc           = DMA_REQ_FCIIC1_RX;
            }
            DMA_InitChannel(pDmaHandle, &FCIIC_DmaChannelAttr);
            pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage=FCIIC_DMA_NEXT_STAGE_IDLE;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}



/**
 * @brief Initiates an IIC Slave Asynchronous DMA transfer.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 *
 * @return FCIIC_StatusType Status indicating whether the DMA transfer was successful.
 */
FCIIC_StatusType FCIIC_SlaveTransferDMA(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVETRANSFERDMA_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVETRANSFERDMA_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_Type  *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];

        if (true == pFciicSlaveHandle->tStatus.bUsed) /* Check if the I2C bus is idle - if not return busy status. */
        {
            return FCIIC_BUSY;
        }
        else
        {
            pFciicSlaveHandle->tStatus.bUsed = true;
            FCIIC_Slave_HWA_DisableInterrupt(pFciic, FCIIC_SlaveIrqFlags);
            FCIIC_Slave_HWA_ClrStatus(pFciic, FCIIC_SlaveClearFlags);
            FCIIC_SlaveDmaPrepare(pFciicSlaveHandle);
            /*When using DMA, the AM0IE interrupt is used to match the address and open the corresponding DMA request,
             * and then the SDIE interrupt is used to process the logic after the DMA handling is completed.*/
            FCIIC_Slave_HWA_EnableInterrupt(pFciic, FCIIC_SIER_AM0IE | FCIIC_SIER_SDIE);
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_LISTENING;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return FCIIC_SUCCESS;
}


/**
 * @brief Starts DMA for IIC Slave in asynchronous mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveDMAStageNotification(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVEDMASTAGENOTIFICATION_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVEDMASTAGENOTIFICATION_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        DMA_StatusType ret = DMA_STATUS_BUSY;
        FCIIC_Type *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        FCIIC_ChannelStatusType eChannelStatus = pFciicSlaveHandle->tStatus.eChannelStatus;
        FCIIC_DmaConfigType *pFciicRxDmaConfig = pFciicSlaveHandle->tSettings.pFciicRxDmaConfig;
        FCIIC_DmaConfigType *pFciicTxDmaConfig = pFciicSlaveHandle->tSettings.pFciicTxDmaConfig;
        DMA_Type *aDma[] = DMA_BASE_PTRS;
        DMA_Type *const pDma = aDma[pFciicTxDmaConfig->pDmaHandle->tSettings.pInstance->tSettings.u8Instance];

        uint32_t u32FciicTxSrcAddr = DMA_HWA_GetSrcAddr(pDma, pFciicTxDmaConfig->pDmaHandle->tSettings.u8Channel);
        uint32_t u32FciicRxDstAddr = DMA_HWA_GetDestAddr(pDma, pFciicRxDmaConfig->pDmaHandle->tSettings.u8Channel);

        FCIIC_Slave_HWA_ClrStatus(pFciic, FCIIC_SSR_SDF_STATUS);
        if ((eChannelStatus == FCIIC_CH_SENDING) && (FCIIC_DMA_NEXT_STAGE_DATA == pFciicTxDmaConfig->u8I2cDmaNextStage))
        {
            /*DMA less send,But more bytes are required to transfer,*/
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            FCIIC_Slave_HWA_ClearStatus(pFciic, FCIIC_SSR_TREF_STATUS);
            ret = DMA_ModifyAddress(pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->pDmaHandle, (const volatile void *)pFciicSlaveHandle->tSettings.pData,
                                    (const volatile void *)(pFciic->STDR));
            pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_SLAVEDMANUMBERERROR;
        }
        /*DMA less receive,But not all bytes are transferred completely*/
        else if ((eChannelStatus == FCIIC_CH_RECEIVING) && (FCIIC_DMA_NEXT_STAGE_DATA == pFciicRxDmaConfig->u8I2cDmaNextStage))
        {
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
            FCIIC_Slave_HWA_ClearStatus(pFciic, FCIIC_SSR_TREF_STATUS);
            ret = DMA_ModifyAddress(pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->pDmaHandle, (const volatile void *)(pFciic->SRDR),
                                    (const volatile void *)pFciicSlaveHandle->tSettings.pData);
            pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_SLAVEDMANUMBERERROR;
        }
        /*DMA more send error*/
        else if ((eChannelStatus == FCIIC_CH_TRANSFER_FINISHED) && (pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage == FCIIC_DMA_NEXT_STAGE_STOP))
        {
            if ((u32FciicTxSrcAddr == ((uint32)pFciicSlaveHandle->tSettings.pData)))
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
                pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_NOTIFICATION;
            }
            else
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                FCIIC_Slave_HWA_ClearStatus(pFciic, FCIIC_SSR_TREF_STATUS);
                ret = DMA_ModifyAddress(pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->pDmaHandle, pFciicSlaveHandle->tSettings.pData, (const volatile void *)(pFciic->STDR));
                pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_SLAVEDMANUMBERERROR;
            }
        }
        /*DMA more receive error*/
        else if ((eChannelStatus == FCIIC_CH_TRANSFER_FINISHED) && (pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage == FCIIC_DMA_NEXT_STAGE_STOP))
        {
            if ((u32FciicRxDstAddr == ((uint32)pFciicSlaveHandle->tSettings.pData)))
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_IDLE;
                pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_NOTIFICATION;
            }
            else
            {
                pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
                FCIIC_Slave_HWA_ClearStatus(pFciic, FCIIC_SSR_TREF_STATUS);
                pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_SLAVEDMANUMBERERROR;
                ret = DMA_ModifyAddress(pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->pDmaHandle, (const volatile void *)(pFciic->SRDR), pFciicSlaveHandle->tSettings.pData);
            }
        }
        else
        {
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }

        if ((ret == DMA_STATUS_BUSY))
        {
            pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_DMAREQUESTFAIL;
        }

        if ((FCIIC_CH_IDLE == pFciicSlaveHandle->tStatus.eChannelStatus))
        {
            pFciicSlaveHandle->tStatus.u16DataOffset=(uint16)DMA_HWA_GetSrcOffset(pDma, pFciicTxDmaConfig->pDmaHandle->tSettings.u8Channel);
            if (NULL != pFciicSlaveHandle->tSettings.pCallback)
            {
                pFciicSlaveHandle->tSettings.pCallback(pFciicSlaveHandle);
            }
            if(pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage == FCIIC_DMA_NEXT_STAGE_NOTIFICATION)
            {
                pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_IDLE;
            }
            if(pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage == FCIIC_DMA_NEXT_STAGE_NOTIFICATION)
            {
                pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_IDLE;
            }
            pFciicSlaveHandle->tStatus.u16DataOffset = 0;
            pFciicSlaveHandle->tStatus.eRunStatus = FCIIC_SUCCESS;
            pFciicSlaveHandle->tStatus.eChannelStatus=FCIIC_CH_LISTENING;
        }
        else
        {
            if (NULL != pFciicSlaveHandle->tSettings.pErrorCallback)
            {
                pFciicSlaveHandle->tSettings.pErrorCallback(pFciicSlaveHandle);
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief Starts DMA for IIC Slave in asynchronous mode.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_SlaveStartDMA(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_SLAVESTARTDMA_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_SLAVESTARTDMA_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        FCIIC_DmaStatusType eDmaNextStage;
        FCIIC_Type       *pFciic = (FCIIC_Type *)s_aFCIIC_InstanceTable[pFciicSlaveHandle->eInstance];
        FCIIC_ChannelStatusType eChannelStatus;
        FCIIC_DirectionType eDirection = (FCIIC_DirectionType)(FCIIC_HWA_GetSASR(pFciic)& FCIIC_DIR_MASK);

        pFciicSlaveHandle->tStatus.eChannelStatus = eDirection == FCIIC_READ ? FCIIC_CH_LISTENING : FCIIC_CH_LISTENING_READ;

        eDmaNextStage = FCIIC_READ == eDirection ?
                        pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage : pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage;

        eChannelStatus = pFciicSlaveHandle->tStatus.eChannelStatus;

        if ((FCIIC_WRITE == eDirection) && (FCIIC_CH_LISTENING_READ == eChannelStatus) && (eDmaNextStage == FCIIC_DMA_NEXT_STAGE_IDLE))
        {
            FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_RECEIVING;
            pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_DATA;
            DMA_StartChannel(pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->pDmaHandle);
        }
        else  if ((FCIIC_READ == eDirection) && (FCIIC_CH_LISTENING == eChannelStatus) && (eDmaNextStage == FCIIC_DMA_NEXT_STAGE_IDLE))
        {
            FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)TRUE);
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_SENDING;
            pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_DATA;
            DMA_StartChannel(pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->pDmaHandle);
        }
        else
        {
            FCIIC_SlaveAck(pFciicSlaveHandle, (boolean)FALSE);
            if(eDmaNextStage != FCIIC_DMA_NEXT_STAGE_IDLE)
            {
                pFciicSlaveHandle->tStatus.eRunStatus |= FCIIC_STATEMACHINEERROR;
            }
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

/**
 * @brief DMA handler for IIC Slave.
 *
 * @param[in] pFciicSlaveHandle Pointer to the FCIIC Slave handle.
 */
void FCIIC_LL_SlaveDmaIRQnHandler(FCIIC_SlaveHandleType *const pFciicSlaveHandle)
{
    #if FCIIC_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFciicSlaveHandle)
    {
        FCIIC_ReportDevError(FCIIC_LL_SLAVEDMAIRQNHANDLER_ID, FCIIC_E_PARAM_NULLPTR);
    }
    else if ((pFciicSlaveHandle != NULL) && (pFciicSlaveHandle->eInstance >= FCIIC_INSTANCE_COUNT))
    {
        FCIIC_ReportDevError(FCIIC_LL_SLAVEDMAIRQNHANDLER_ID, FCIIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        if ((FCIIC_DMA_NEXT_STAGE_DATA == pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage) && (FCIIC_CH_RECEIVING == pFciicSlaveHandle->tStatus.eChannelStatus))
        {
            pFciicSlaveHandle->tSettings.pFciicRxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_STOP;
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
        }
        else if ((FCIIC_DMA_NEXT_STAGE_DATA == pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage) && (FCIIC_CH_SENDING == pFciicSlaveHandle->tStatus.eChannelStatus))
        {
            pFciicSlaveHandle->tSettings.pFciicTxDmaConfig->u8I2cDmaNextStage = FCIIC_DMA_NEXT_STAGE_STOP;
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_TRANSFER_FINISHED;
        }
        else
        {
            pFciicSlaveHandle->tStatus.eRunStatus |=FCIIC_STATEMACHINEERROR;
            pFciicSlaveHandle->tStatus.eChannelStatus = FCIIC_CH_ERROR_PRESENT;
        }

        if (pFciicSlaveHandle->tStatus.eChannelStatus == FCIIC_CH_ERROR_PRESENT)
        {
            pFciicSlaveHandle->tStatus.eRunStatus |= (FCIIC_StatusType)FCIIC_SlaveGetError(pFciicSlaveHandle);
            if ((NULL != pFciicSlaveHandle->tSettings.pErrorCallback))
            {
                FCIIC_SlaveClrError(pFciicSlaveHandle);
                pFciicSlaveHandle->tSettings.pErrorCallback(pFciicSlaveHandle);
            }
        }
        #if FCIIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

#endif
