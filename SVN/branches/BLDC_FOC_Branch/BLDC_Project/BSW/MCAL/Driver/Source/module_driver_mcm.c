 /* @file module_driver_mcm.c
 * @author Flagchip
 * @brief MCM driver source code
 * @version 2.0.0
 * @date 2024-02-21
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

 /*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#include "module_driver_mcm.h"

#if MCM_INSTANCE_COUNT > 0U


#include "module_driver_fcuart.h"

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */

/********* Local variable ************/
static MCM_Type * const s_pMcmBasePtrs[MCM_INSTANCE_COUNT] = MCM_BASE_PTRS;

/* ################################################################################## */
/* ################################ Global Functions ################################ */
/**
 * @brief Configures the FPU interrupt mode.
 *
 * This function configures the specified interrupt source of the FPU according to the enable state.
 * Depending on the interrupt source, it calls the corresponding hardware abstraction layer functions
 * to enable or disable the interrupts.
 *
 * @param pMcmHandle The handle to the FPU module, which identifies the specific FPU instance and stores related states.
 * @param eIntSrc The interrupt source that specifies the particular type of interrupt to configure.
 * @param bEnable The enable state; true to enable the interrupt, false to disable it.
 */
void MCM_FpuIntMode(MCM_HandleType* pMcmHandle, FPU_IntType eIntSrc, bool bEnable)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    switch (eIntSrc)
    {
        case MCM_FPU_FIO:
            MCM_HWA_SetFioceInt(pMcm, bEnable);
            break;
        case MCM_FPU_FDZ:
            MCM_HWA_SetFdzceInt(pMcm, bEnable);
            break;
        case MCM_FPU_FOF:
            MCM_HWA_SetFofceInt(pMcm, bEnable);
            break;
        case MCM_FPU_FUF:
            MCM_HWA_SetFufceInt(pMcm, bEnable);
            break;
        case MCM_FPU_FIX:
            MCM_HWA_SetFixceInt(pMcm, bEnable);
            break;
        case MCM_FPU_FID:
            MCM_HWA_SetFixceInt(pMcm, bEnable);
            break;
        default :
            /* Invalid parameter: return */
            break;
    }
}


/**
 * @brief Gets the status of a specified FPU interrupt source.
 *
 * This function queries the status of a specific FPU interrupt source and returns whether an interrupt has occurred.
 *
 * @param pMcmHandle A handle to the module control management, identifying the specific FPU instance.
 * @param eIntSrc The type of interrupt source to query.
 * @return bool True if an interrupt has occurred, false otherwise.
 */
bool MCM_GetFpuIntStatus(MCM_HandleType* pMcmHandle, FPU_IntType eIntSrc)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    bool bRetVal = false;
    switch(eIntSrc){
    case MCM_FPU_FIO:
        bRetVal = MCM_HWA_GetFpuFiocFlag(pMcm);
        break;
    case MCM_FPU_FDZ:
        bRetVal = MCM_HWA_GetFpuFdzcFlag(pMcm);
        break;
    case MCM_FPU_FOF:
        bRetVal = MCM_HWA_GetFpuFofcFlag(pMcm);
        break;
    case MCM_FPU_FUF:
        bRetVal = MCM_HWA_GetFpuFufcFlag(pMcm);
        break;
    case MCM_FPU_FIX:
        bRetVal = MCM_HWA_GetFpuFixcFlag(pMcm);
        break;
    case MCM_FPU_FID:
        bRetVal = MCM_HWA_GetFpuFidcFlag(pMcm);
        break;
    default:
        break;

    }
    return bRetVal;
}


/**
 * @brief Get the reset status of the MCM module.
 * 
 * This function retrieves the reset status for a specific source within the MCM module.
 * 
 * @param pMcmHandle Pointer to the MCM handle structure containing instance information.
 * @param eIntSrc The type of reset status to retrieve.
 * 
 * @return bool Indicates whether the specified reset status is active (true) or inactive (false).
 */
bool MCM_GetRepStatus(MCM_HandleType* pMcmHandle, MCM_RepType eIntSrc)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    bool bRetVal = false;
    switch(eIntSrc){
    case MCM_CASPECR_ECPR:
        bRetVal = MCM_HWA_GetCaspecrEcpr(pMcm);
        break;
    case MCM_CASPECR_ER1BR:
        bRetVal = MCM_HWA_GetCaspecrEr1br(pMcm);
        break;
    case MCM_CASPECR_ERNCR:
        bRetVal = MCM_HWA_GetCaspecrErncr(pMcm);
        break;
    default:
        break;
    }
    return bRetVal;
}

/**
 * @brief Gets the FIU control and status register value.
 *
 * @param pMcmHandle Pointer to the MCM_HandleType structure containing instance information.
 *
 * @return The value of the FIU control and status register.
 */
uint32_t MCM_GetFiscr(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    return MCM_HWA_GetFiscr(pMcm);
}

/**
 * @brief Gets the value of the CASPEIR register.
 *
 * This function retrieves the corresponding MCM instance through the provided MCM handle,
 * and calls a hardware access function to get the value of the CASPEIR register.
 *
 * @param pMcmHandle A pointer to an MCM handle, used to identify the specific MCM instance.
 * @return The value of the CASPEIR register, returned as a uint32_t.
 */
uint32_t MCM_GetCaspeir(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    return MCM_HWA_GetCaspeir(pMcm);
}

/**
 * @brief Gets the CASPEIR E1b value.
 *
 * This function retrieves the CASPEIR E1b value by using the provided MCM handle to identify the specific MCM instance and then calls a hardware access function.
 *
 * @param pMcmHandle Pointer to an MCM handle type, used to identify a specific MCM instance.
 *
 * @return Returns the CASPEIR E1b value as an unsigned 32-bit integer.
 */
uint32_t MCM_GetCaspeirE1b(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    return MCM_HWA_GetCaspeirE1b(pMcm);
}

/**
 * @brief Gets the Caspeir encoding value.
 * 
 * This function retrieves the Caspeir encoding value through the specified MCM instance handle.
 * The encoding value reflects the current state or setting of Caspeir in the MCM module.
 * 
 * @param pMcmHandle A pointer to the MCM instance handle. This handle identifies which MCM instance will be used.
 * @return uint32_t The Caspeir encoding value.
 */
uint32_t MCM_GetCaspeirEnc(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    return MCM_HWA_GetCaspeirEnc(pMcm);
}

/**
 * @brief Gets the CASFAR value for a given MCM instance.
 *
 * This function retrieves the CASFAR value using the provided MCM handle.
 *
 * @param pMcmHandle Pointer to the MCM handle structure that identifies the MCM instance.
 * @return The retrieved CASFAR value, reflecting a specific configuration or status parameter.
 */
uint32_t MCM_GetCasfar(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    return MCM_HWA_GetCasfar(pMcm);
}

/**
 * @brief Enables the RAM ECC single-bit error reporting.
 * 
 * This function enables the reporting of single-bit errors detected by the ECC on the RAM.
 * By calling a hardware-specific API, it configures the system to report these errors,
 * which can be useful for monitoring and analysis.
 * 
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_EnableRamEcc1BitReport(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    MCM_HWA_EnableRamEcc1BitReport(pMcm);
}

/**
 * @brief Disable Ram Ecc1 Bit Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_DisableRamEcc1BitReport(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    MCM_HWA_DisableRamEcc1BitReport(pMcm);
}

/**
 * @brief Disable Ram Ecc Ncr Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_DisableRamEccNcrReport(MCM_HandleType* pMcmHandle)
{
    MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    MCM_HWA_DisableRamEccNcrReport(pMcm);
}

/**
 * @brief Enable Cache Parity Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_EnableCacheParityReport(MCM_HandleType* pMcmHandle)
{
    MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    MCM_HWA_EnableCacheParityReport(pMcm);
}

/**
 * @brief Disable Cache Ecc Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_DisableCacheEccReport(MCM_HandleType* pMcmHandle)
{
	MCM_Type * const pMcm = s_pMcmBasePtrs[pMcmHandle->eInstance];
    MCM_HWA_DisableCacheEccReport(pMcm);
}

#ifdef FPU_USED
/**
 * @brief MCM_Read_FPSCR
 * Return the current value of FPSCR
 * @return u32RetVal 
 */
uint32_t MCM_Read_FPSCR(void)
{
    uint32_t u32RetVal = 0U;
    __asm(
            "vmrs %0, fpscr" : "=r" (u32RetVal)
    );
    return u32RetVal;
}

/**
 * @brief MCM_Write_FPSCR
 * 
 * @param u32SetVal set the value for FPSCR 
 */
void MCM_Write_FPSCR(uint32_t u32SetVal)
{
        __asm(
                "vmsr fpscr, %0" : : "r" (u32SetVal)
        );
}
#endif

/**
 * @brief MCM common interrupt function
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void Mcm_CommonProcessInterrupt(MCM_HandleType* pMcmHandle)
{
    if (NULL != pMcmHandle->tSettings.pMcmCallback)
    {
        pMcmHandle->tSettings.pMcmCallback(pMcmHandle);
    }
}

#endif

