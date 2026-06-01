/**
 * @file module_driver_mcm.h
 * @author Flagchip
 * @brief MCM driver type definition and API
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
#ifndef _DRIVER_MODULE_DRIVER_MCM_H_
#define _DRIVER_MODULE_DRIVER_MCM_H_

#include "HwA_mcm.h"

#if MCM_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif

/* ################################################################################## */
/* ####################################### Macro #################################### */

/* FPSCR Bit Fields */
#define FPSCR_IOC_MASK            0x00000001U
#define FPSCR_DZC_MASK            0x00000002U
#define FPSCR_OFC_MASK            0x00000004U
#define FPSCR_UFC_MASK            0x00000008U
#define FPSCR_IXC_MASK            0x00000010U
#define FPSCR_IDC_MASK            0x00000080U
#define MCM_FPU_INTFLAGMASK       0x00009F00U

#define CASPEIR_E1B_CTCM          0x00000001U
#define CASPEIR_E1B_DTCM          0x00000002U

#define CASPEIR_ENB_CTCM          0x00000001U
#define CASPEIR_ENB_DTCM          0x00000002U

/**
 * @addtogroup module_driver_mcm
 * @{
 */
/**
 * @brief FPU INTERRUPT type.
 *
 * This provides constants for FPU interrupt type for use in the FPU functions.
 * Please refer to Reference Manual chapter 14 MCM, it introduce register FISCR for details.
 * 
 */
typedef enum {
    MCM_FPU_FIO = 0U,    /**< in function MCM_FpuIntMode, set MCM_FISCR FIOCE bit; in function MCM_GetFpuIntStatus, get MCM_FISCR FIOC Status*/
    MCM_FPU_FDZ,         /**< in function MCM_FpuIntMode, set MCM_FISCR FDZCE bit; in function MCM_GetFpuIntStatus, get MCM_FISCR FDZC Status*/
    MCM_FPU_FOF,         /**< in function MCM_FpuIntMode, set MCM_FISCR FOFCE bit; in function MCM_GetFpuIntStatus, get MCM_FISCR FOFC Status*/
    MCM_FPU_FUF,         /**< in function MCM_FpuIntMode, set MCM_FISCR FUFCE bit; in function MCM_GetFpuIntStatus, get MCM_FISCR FUFC Status*/
    MCM_FPU_FIX,         /**< in function MCM_FpuIntMode, set MCM_FISCR FIXCE bit; in function MCM_GetFpuIntStatus, get MCM_FISCR FIXC Status*/
    MCM_FPU_FID          /**< in function MCM_FpuIntMode, set MCM_FISCR FIDCE bit; in function MCM_GetFpuIntStatus, get MCM_FISCR FIDC Status*/
} FPU_IntType;

/**
 * @brief MCM Error type.
 *
 * This provides constants the error type.
 * Please refer to Reference Manual chapter 14 MCM, it introduce register CASPECR for details.
 */
typedef enum {
    CACHE_PARITY_ERROR = 0,  /**< MCM CACHE parity error  */
    ECC1BIT_DTCM_ERROR,      /**< MCM ECC 1 Bit DTCM error */
    ECC1BIT_CTCM_ERROR,      /**< MCM ECC 1 Bit CTCM error */
    ECCNBIT_DTCM_ERROR,      /**< MCM ECC n Bit DTCM error */
    ECCNBIT_CTCM_ERROR       /**< MCM ECC n Bit CTCM error */
} MCM_ErrorType;

/**
 * @brief CASPECR Report type.
 *
 * This provides constants the report type.
 * Please refer to Reference Manual chapter 14 MCM, it introduce register CASPECR for details.
 */
typedef enum {
    MCM_CASPECR_ECPR = 0U,      /**< MCM_CASPEIR ECPR  */
    MCM_CASPECR_ER1BR,          /**< MCM_CASPECR ER1BR */
    MCM_CASPECR_ERNCR           /**< MCM_CASPECR ERNCR */
} MCM_RepType;

/**
 * @brief CASPEIR Report type.
 * 
 * Please refer to Reference Manual chapter 14 MCM, it introduce register CASPEIR for details.
 */
typedef enum {
    MCM_CASPEIR_PRESENT = 0U,    /**< MCM CASPEIR PRESENT, Valid bit  */
    MCM_CASPEIR_PEELOC,          /**< MCM CASPEIR PEELOC, Parity or ECC Error Location */
    MCM_CASPEIR_PE,              /**< MCM CASPEIR PE, Cache Parity Error */
    MCM_CASPEIR_E1B,             /**< MCM CASPEIR E1B, ECC 1-bit Error n */
    MCM_CASPEIR_ENC              /**< MCM CASPEIR ENC, ECC Noncorrectable Error n */
} MCM_CaspeirType;

/**
 * @brief ACR register type.
 *
 * Please refer to Reference Manual chapter 14 MCM, it introduce register ACR for details.
 */
typedef enum {
    MCM_ACR_CTCMAP,     /**< MCM ACR CTCMAP, CTCM Arbitration Priority */
    MCM_ACR_DTCMAP,     /**< MCM ACR DTCMAP, ECC Noncorrectable Error n */
    MCM_ACR_CBRR        /**< MCM ACR CRBB, ECC Noncorrectable Error n */
}MCM_AcrType;

/**
 * @brief MCM instance type.
 *
 * This provides constants the MCM instance type.
 */
typedef enum
{
	MCM_INSTANCE_0 = 0U
} MCM_InstanceType;

/**
 * @brief The structure of the MCM processing handle
 *
 */
typedef struct _MCM_HandleType
{
	MCM_InstanceType eInstance;		/**< MCM instance*/
	char aligned[3];
	struct
	{
		void (*pMcmCallback)(struct _MCM_HandleType *pHandle);		/**< MCM interrupt callback */
	} tSettings;
} MCM_HandleType;

#ifdef FPU_USED
/**
 * @brief MCM_Read_FPSCR
 * Return the current value of FPSCR
 * @return u32RetVal 
 */
uint32_t MCM_Read_FPSCR(void);

/**
 * @brief MCM_Write_FPSCR
 * 
 * @param u32SetVal set the value for FPSCR 
 */
void MCM_Write_FPSCR(uint32_t u32SetVal);

#endif

/* ----------------------------------------------------------------------------
   --   Global Api
   ---------------------------------------------------------------------------- */
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
void MCM_FpuIntMode(MCM_HandleType* pMcmHandle, FPU_IntType eIntSrc, bool bEnable);

/**
 * @brief Gets the status of a specified FPU interrupt source.
 *
 * This function queries the status of a specific FPU interrupt source and returns whether an interrupt has occurred.
 *
 * @param pMcmHandle A handle to the module control management, identifying the specific FPU instance.
 * @param eIntSrc The type of interrupt source to query.
 * @return bool True if an interrupt has occurred, false otherwise.
 */
bool MCM_GetFpuIntStatus(MCM_HandleType* pMcmHandle, FPU_IntType eIntSrc);

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
bool MCM_GetRepStatus(MCM_HandleType* pMcmHandle, MCM_RepType eIntSrc);

/**
 * @brief Gets the FIU control and status register value.
 *
 * @param pMcmHandle Pointer to the MCM_HandleType structure containing instance information.
 *
 * @return The value of the FIU control and status register.
 */
uint32_t MCM_GetFiscr(MCM_HandleType* pMcmHandle);

/**
 * @brief Gets the value of the CASPEIR register.
 *
 * This function retrieves the corresponding MCM instance through the provided MCM handle,
 * and calls a hardware access function to get the value of the CASPEIR register.
 *
 * @param pMcmHandle A pointer to an MCM handle, used to identify the specific MCM instance.
 * @return The value of the CASPEIR register, returned as a uint32_t.
 */
uint32_t MCM_GetCaspeir(MCM_HandleType* pMcmHandle);

/**
 * @brief Gets the CASPEIR E1b value.
 *
 * This function retrieves the CASPEIR E1b value by using the provided MCM handle to identify the specific MCM instance and then calls a hardware access function.
 *
 * @param pMcmHandle Pointer to an MCM handle type, used to identify a specific MCM instance.
 *
 * @return Returns the CASPEIR E1b value as an unsigned 32-bit integer.
 */
uint32_t MCM_GetCaspeirE1b(MCM_HandleType* pMcmHandle);

/**
 * @brief Gets the Caspeir encoding value.
 * 
 * This function retrieves the Caspeir encoding value through the specified MCM instance handle.
 * The encoding value reflects the current state or setting of Caspeir in the MCM module.
 * 
 * @param pMcmHandle A pointer to the MCM instance handle. This handle identifies which MCM instance will be used.
 * @return uint32_t The Caspeir encoding value.
 */
uint32_t MCM_GetCaspeirEnc(MCM_HandleType* pMcmHandle);

/**
 * @brief Gets the CASFAR value for a given MCM instance.
 *
 * This function retrieves the CASFAR value using the provided MCM handle.
 *
 * @param pMcmHandle Pointer to the MCM handle structure that identifies the MCM instance.
 * @return The retrieved CASFAR value, reflecting a specific configuration or status parameter.
 */
uint32_t MCM_GetCasfar(MCM_HandleType* pMcmHandle);

/**
 * @brief Enables the RAM ECC single-bit error reporting.
 * 
 * This function enables the reporting of single-bit errors detected by the ECC on the RAM.
 * By calling a hardware-specific API, it configures the system to report these errors,
 * which can be useful for monitoring and analysis.
 * 
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_EnableRamEcc1BitReport(MCM_HandleType* pMcmHandle);

/**
 * @brief Disable Ram Ecc1 Bit Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_DisableRamEcc1BitReport(MCM_HandleType* pMcmHandle);

/**
 * @brief Disable Ram Ecc Ncr Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_DisableRamEccNcrReport(MCM_HandleType* pMcmHandle);

/**
 * @brief Enable Cache Parity Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_EnableCacheParityReport(MCM_HandleType* pMcmHandle);

/**
 * @brief Disable Cache Ecc Report
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void MCM_DisableCacheEccReport(MCM_HandleType* pMcmHandle);

/**
 * @brief MCM common interrupt function
 *
 * @param pMcmHandle A pointer to the MCM handle, identifying the specific MCM instance and its configuration.
 */
void Mcm_CommonProcessInterrupt(MCM_HandleType* pMcmHandle);

#if defined(__cplusplus)
}
#endif

/** @}*/ /* module_driver_mcm */

#endif

#endif
