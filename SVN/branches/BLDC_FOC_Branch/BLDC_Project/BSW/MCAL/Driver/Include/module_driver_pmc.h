/**
 * @file module_driver_pmc.h
 * @author Flagchip
 * @brief PMC driver type definition and API
 * @version 2.0.0
 * @date 2024-11-10
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
#ifndef _DRIVER_MODULE_DRIVER_PMC_H_
#define _DRIVER_MODULE_DRIVER_PMC_H_

#include "HwA_pmc.h"

#if PMC_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif
/* ################################################################################## */
/* ####################################### Macro #################################### */
/**
 * @addtogroup module_driver_pmc
 * @{
 */

/**
 * @name  PMC API Service IDs
 *
 * @{
 */
#define PMC_INIT_ID     0x00U
/** @}*/

/**
 * @name  PMC Dev Error Code
 * @brief Error Code of calling PCC apis
 *
 * @{
 */
#define PMC_E_PARAM_INSTANCE   			0x01U
#define PMC_E_PARAM_POINTER   			0x02U
/** @}*/

/**
 * @name  PMC register default value
 *
 * @{
 */
#if PMC_BUFVREF10_SUPPORT
#define LVSCR_DEFAULT_VAL   0x83C30000U
#else
#define LVSCR_DEFAULT_VAL   0x83F30010U
#endif /* PMC_BUFVREF10_SUPPORT */

#define CONFIG_DEFAULT_VAL  0x0U
/** @} */

/**
 * @brief PMC fault type.
 * This provides constants for the PMC fault type for use in the PMC interrupt callback functions.
 */
typedef enum
{
    PMC_NONE = 0,       /**< PMC no fault */
#if PMC_LVD_SUPPORT
    PMC_LVD5V,          /**< PMC LVD5V fault */
#endif
#if PMC_V5_SUPPORT
    PMC_HVD5V,          /**< PMC HVD5V fault */
#endif
#if PMC_V3_SUPPORT
    PMC_HVD3V,          /**< PMC HVD3V fault */
#endif
#if PMC_V25_SUPPORT
    PMC_HVD2P5V,        /**< PMC HVD2P5V fault */
#endif
    PMC_HVD1P1V         /**< PMC HVD1P1V fault */
} PMC_Fault_Type;

/**
 * @brief PMC flags.
 * This provides constants for the PMC LVSCR flags for use in the PMC functions.
 */
typedef enum
{
    PMC_POR_FLAG             = PMC_LVSCR_POR_FLAG_SHIFT,             /**< PMC POR flag */
    PMC_LVR1P1V_RPM_FLAG     = PMC_LVSCR_LVR1P1V_RPM_FLAG_SHIFT,     /**< PMC Low voltage reset flag of V11 domain in RPM */
    PMC_LVR1P1V_FPM_FLAG     = PMC_LVSCR_LVR1P1V_FPM_FLAG_SHIFT,     /**< PMC Low voltage reset flag of V11 domain in FPM */
#if PMC_V25_SUPPORT
    PMC_LVR2P5V_RPM_FLAG     = PMC_LVSCR_LVR2P5V_RPM_FLAG_SHIFT,     /**< PMC Low voltage reset flag of V25 domain in RPM */
    PMC_LVR2P5V_FPM_FLAG     = PMC_LVSCR_LVR2P5V_FPM_FLAG_SHIFT,     /**< PMC Low voltage reset flag of V25 domain in FPM */
#endif
#if PMC_V3_SUPPORT
    PMC_LVR3V_RPM_FLAG       = PMC_LVSCR_LVR3V_RPM_FLAG_SHIFT,       /**< PMC Low voltage reset flag of V3 domain in RPM */
    PMC_LVR3V_FPM_FLAG       = PMC_LVSCR_LVR3V_FPM_FLAG_SHIFT,       /**< PMC Low voltage reset flag of V3 domain in FPM */
#endif
#if PMC_V5_SUPPORT
    PMC_LVR5V_RPM_FLAG       = PMC_LVSCR_LVR5V_RPM_FLAG_SHIFT,       /**< PMC Low voltage reset flag of V5 domain in RPM */
    PMC_LVR5V_FPM_FLAG       = PMC_LVSCR_LVR5V_FPM_FLAG_SHIFT,       /**< PMC Low voltage reset flag of V5 domain in FPM */
    PMC_LVD5V_FLAG           = PMC_LVSCR_LVD5V_FLAG_SHIFT,           /**< PMC LVD5V flag on V5 domain in FPM  */
#endif
    PMC_HVD1P1V_FLAG         = PMC_LVSCR_HVD1P1V_FLAG_SHIFT,         /**< PMC HVD1P1V flag on V11 domain in FPM */
#if PMC_V25_SUPPORT
    PMC_HVD2P5V_FLAG         = PMC_LVSCR_HVD2P5V_FLAG_SHIFT,         /**< PMC HVD2P5V flag on V25 domain in FPM */
#endif
#if PMC_V5_SUPPORT
    PMC_HVD5V_FLAG           = PMC_LVSCR_HVD5V_FLAG_SHIFT            /**< PMC HVD5V flag on V5 domain in FPM */
#endif
#if PMC_V3_SUPPORT
	PMC_HVD3V_FLAG           = PMC_LVSCR_HVD3V_FLAG_SHIFT            /**< PMC HVD3V flag on V3 domain in FPM */
#endif
} PMC_FlagType;


/**
 * @brief PMC status.
 * 
 * This provides PMC status in the PMC functions.
 */
typedef enum
{
#if PMC_V5_SUPPORT
	PMC_LVD5V_STATUS         = PMC_LVSCR_LVD5V_STATUS_SHIFT,        /**< PMCLVD5V status on V5 domain in FPM */
#endif
    PMC_HVD1P1V_STATUS       = PMC_LVSCR_HVD1P1V_STATUS_SHIFT,      /**< HVD11 status on V11 domain in FPM */
#if PMC_V25_SUPPORT
    PMC_HVD2P5V_STATUS       = PMC_LVSCR_HVD2P5V_STATUS_SHIFT,      /**< HVD25 status on V25 domain in FPM */
#endif
#if PMC_V5_SUPPORT
    PMC_HVD5V_STATUS         = PMC_LVSCR_HVD5V_STATUS_SHIFT         /**< HVD5V status on V5 domain in FPM */
#endif
#if PMC_V3_SUPPORT
	PMC_HVD3V_STATUS         = PMC_LVSCR_HVD3V_STATUS_SHIFT         /**< HVD3V status on V3 domain in FPM */
#endif
} PMC_StatusType;

/**
 * @brief PMC return type.
 *
 * This provides PMC return status. 0: successful, 1: invalid parameter
 */
typedef enum
{
    PMC_STATUS_SUCCESS = 0U,          /**< PMC status success */
    PMC_STATUS_PARAM_INVALID = 1U     /**< PMC status parameter invalid */

}PMC_RetType;

/**
 * @brief The interrupt enable/disable mask of PMC
 *
 */
typedef enum
{
	PMC_INTR_MASK_HVD		= 1U,			/**< interrupt mask of HVD */
#if PMC_LVD_SUPPORT
	PMC_INTR_MASK_LVD		= (1U << 1) 	/**< interrupt mask of LVD */
#endif
} PMC_IntrMaskType;

/**
 * @brief The structure of the SCG processing handle
 *
 */
typedef struct _PMC_HandleType
{
    void (*pPmcFaultNotify)(struct _PMC_HandleType *pHandle, PMC_Fault_Type eFault);	/**< PMC interrupt callback */
} PMC_HandleType;

/**
 * @brief The configuration option for the SCG interrupt
 *
 */
typedef struct
{
#if PMC_BUFVREF10_SUPPORT
	bool bBufVref10En;          /**< Buffer Vref10 enable */
#else
	bool bV25RpmEn;             /**< V25Rpm enable */
#endif
	uint32_t u32InterruptMask;	/**< interrupt enable mask */
    void (*pPmcFaultNotify)(PMC_HandleType *pHandle, PMC_Fault_Type eFault);	/**< FOSC clock error interrupt callback */
} PMC_ConfigType;


/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief PMC get status flag
 * 
 * This function returns the state of a status flag.
 * 
 * @param eFlag PMC flag type
 * @return true the flag bit is 1
 *         false the flag bit is 0
 */
bool PMC_GetFlag(PMC_FlagType eFlag);

/**
 * @brief PMC clears an individual status flag.
 * 
 * This function clears an individual status flag (see pmc_status_flag_t for list of status bits).
 * 
 * @param eFlag PMC flag type
 * @return PMC status successful or operation an invalid parameter
 */
PMC_RetType PMC_ClearFlag(PMC_FlagType eFlag);

/**
 * @brief PMC clears all exist flag bit.
 *
 * This function clears all exist flag bit (see PMC_FlagType for list of flag bits).
 */
void Pmc_ClearAllFlag(void);

/**
 * @brief PMC get status
 * 
 * @param eStatus the status type
 * @return true the status bit return 1
 *         false the status bit return 0
 */
bool PMC_GetStatus(PMC_StatusType eStatus);

/**
 * @brief set PMC LVSCR register.
 * 
 * This function configures the PMC LVSCR registe.
 * 
 * @param u32LVSCRValue Set PMC LVSCR register value.
 */
void PMC_SetLVSCRRegister(uint32_t u32LVSCRValue);

/**
 * @brief PMC_UserIRQHandler function
 * The function just demonstrates how to clear the flag.
 * Customer needs write this function according by customer requirement.
 *
 * @param pPmcHandle Pmc handle
 *
 */
void PMC_UserIRQHandler(PMC_HandleType* pPmcHandle);

/**
 * @brief Enable PMC interrupt
 * @param u32Val the parameter of interrupt flag
 */
void Pmc_EnableInterrupt(uint32 u32Val);

/**
 * @brief Disable PMC interrupt
 * @param u32Val the parameter of interrupt flag
 */
void Pmc_DisableInterrupt(uint32 u32Val);

/**
 * @brief Init PMC interrupt
 *
 * @param pPmcHandle Pmc handle
 * @param pIntCfg interrupt configuration
 */
void Pmc_Init(PMC_HandleType* pPmcHandle, PMC_ConfigType *pIntCfg);

/**
 * @brief PMC DeInit
 *
 * @param pPmcHandle Pmc handle
 */
void Pmc_DeInit(PMC_HandleType* pPmcHandle);

#if defined(__cplusplus)
}
#endif
/** @}*/  /* module_driver_pmc */

#endif

#endif
