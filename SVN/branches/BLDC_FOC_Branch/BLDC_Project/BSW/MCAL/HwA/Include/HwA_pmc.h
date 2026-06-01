/**
 * @file HwA_pmc.h
 * @author Flagchip
 * @brief PMC hardware access layer
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
  *   Revision History:
  *
  *   Version     Date          Initials          Descriptions
  *   ---------   ----------    ------------     ---------------
  *   2.0.0       2024-05-15    Flagchip055      Update file structures
  *********************************************************************************/

#ifndef HWA_INCLUDE_HWA_PMC_H_
#define HWA_INCLUDE_HWA_PMC_H_
#include "device_header.h"

#if PMC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_pmc HwA_pmc
 * @ingroup module_driver_pmc
 * @{
 */

#if PMC_LVD_SUPPORT
#define LVD_INTERRUPT  PMC_CONFIG_LVD_IE_MASK
#endif

#define HVD_INTERRUPT  PMC_CONFIG_HVD_IE_MASK


/**
 * @brief Disable High Voltage detect interrupt
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_DisableHvdInt(PMC_Type *pPMC)
{
	pPMC->CONFIG &=  ~ (uint32_t)PMC_CONFIG_HVD_IE_MASK;
}

/**
 * @brief Enable High Voltage detect interrupt
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_EnableHvdInt(PMC_Type *pPMC)
{
	pPMC->CONFIG |= PMC_CONFIG_HVD_IE_MASK;
}

/**
 * @brief Return HVD1P1V_FLAG value
 * @param pPMC  PMC instance
 * @return 0: HVD1P1V_STATUS has not changed; 1: HVD1P1V_STATUS has changed
 */
LOCAL_INLINE bool PMC_HWA_Hvd1p1vFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD1P1V_FLAG_MASK) >> PMC_LVSCR_HVD1P1V_FLAG_SHIFT);
}

/**
 * @brief Return POR_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No power on resent event; 1: Power on resent event
 */
LOCAL_INLINE bool PMC_HWA_PorFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_POR_FLAG_MASK) >> PMC_LVSCR_POR_FLAG_SHIFT);
}

/**
 * @brief Return LVR1P1V_RPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr1p1vRpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK) >> PMC_LVSCR_LVR1P1V_RPM_FLAG_SHIFT);
}

/**
 * @brief Return LVR1P1V_FPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr1p1vFpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK) >> PMC_LVSCR_LVR1P1V_FPM_FLAG_SHIFT);
}

/**
 * @brief Clear POR_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearPorFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_POR_FLAG_MASK)) | PMC_LVSCR_POR_FLAG_MASK);
}

/**
 * @brief Clear LVR1P1V_RPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr1p1vRpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK)) | PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK);
}

/**
 * @brief Clear LVR1P1V_FPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr1p1vFpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK)) | PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK);
}

/**
 * @brief Clear HVD1P1V_FLAG, w1c
 *
 */
LOCAL_INLINE void PMC_HWA_ClearHvd1p1vFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_HVD1P1V_FLAG_MASK)) | PMC_LVSCR_HVD1P1V_FLAG_MASK);
}

/**
 * @brief Return HVD1P1V_STATUS on V11 domain in FPM
 * @param pPMC  PMC instance
 * @return 0: Voltage on V11 is below high-voltage detect threshold; 1: Voltage on V11 is above high-voltage detect threshold
 */
LOCAL_INLINE bool PMC_HWA_Hvd1p1vStatus(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD1P1V_STATUS_MASK) >> PMC_LVSCR_HVD1P1V_STATUS_SHIFT);
}

/**
 * @brief Return High Voltage Detect Interrupt Enable Flag
 * @param pPMC  PMC instance
 * @return 0: High Voltage Detect Interrupt Disabled; 1: High Voltage Detect Interrupt Enabled
 */
LOCAL_INLINE bool PMC_ReadHVDInterruptFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->CONFIG & PMC_CONFIG_HVD_IE_MASK) >> PMC_CONFIG_HVD_IE_SHIFT);
}

/**
 * @brief get PMC LVSCR register
 * @param pPMC  PMC instance
 * @return uint32_t LVSCR register value
 */
LOCAL_INLINE uint32_t PMC_HWA_GetLVSCRRegister(const PMC_Type *pPMC)
{
    return (uint32)(pPMC -> LVSCR);
}

/**
 * @brief set PMC LVSCR register.
 * @param pPMC  PMC instance
 * This function configures the PMC LVSCR registe.
 *
 * @param u32LVSCRValue Set PMC LVSCR register value.
 */
LOCAL_INLINE void PMC_HWA_SetLVSCRRegister(PMC_Type *pPMC,uint32_t u32LVSCRValue)
{
	pPMC -> LVSCR = u32LVSCRValue;
}

/**
 * @brief get PMC CONFIG register
 * @param pPMC  PMC instance
 * @return uint32_t CONFIG register value
 */
LOCAL_INLINE uint32_t PMC_HWA_GetCONFIGRegister(const PMC_Type *pPMC)
{
    return (uint32)(pPMC -> CONFIG);
}

/**
 * @brief set PMC CONFIG register.
 * @param pPMC  PMC instance
 * This function configures the PMC CONFIG registe.
 *
 * @param u32LVSCRValue Set PMC CONFIG register value.
 */
LOCAL_INLINE void PMC_HWA_SetCONFIGRegister(PMC_Type *pPMC,uint32_t u32LVSCRValue)
{
	pPMC -> CONFIG = u32LVSCRValue;
}

/**
 * @brief HWA Disable PMC interrupt
 * @param pPMC  PMC instance
 * @param u32Val the parameter of interrupt flag
 */
LOCAL_INLINE void PMC_HWA_DisableInterrupt(PMC_Type *pPMC,uint32 u32Val)
{
	pPMC -> CONFIG &= (~u32Val);
}
/**
 * @brief HWA Enable PMC interrupt
 * @param pPMC  PMC instance
 * @param u32Val the parameter of interrupt flag
 */
LOCAL_INLINE void Pmc_HWA_EnableInterrupt(PMC_Type *pPMC,uint32 u32Val)
{
	pPMC -> CONFIG |= u32Val;
}

#if PMC_LVD_SUPPORT
/**
 * @brief Enable low Voltage detect interrupt
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_EnableLvdInt(PMC_Type *pPMC)
{
	pPMC->CONFIG |= PMC_CONFIG_LVD_IE_MASK;
}

/**
 * @brief Disable low Voltage detect interrupt
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_DisableLvdInt(PMC_Type *pPMC)
{
	pPMC->CONFIG &=  ~ (uint32_t)PMC_CONFIG_LVD_IE_MASK;
}

/**
 * @brief Return Low Voltage Detect Interrupt Enable Flag
 * @param pPMC  PMC instance
 * @return 0: Low Voltage Detect Interrupt Disabled; 1: Low Voltage Detect Interrupt Enabled
 */
LOCAL_INLINE bool PMC_ReadLVDInterruptFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->CONFIG & PMC_CONFIG_LVD_IE_MASK) >> PMC_CONFIG_LVD_IE_SHIFT);
}

#endif

#if PMC_V5_SUPPORT
/**
 * @brief Return LVD5V_FLAG value
 * @param pPMC  PMC instance
 * @return 0: LVD5V_STATUS has not changed; 1: LVD5V_STATUS has changed
 */
LOCAL_INLINE bool PMC_HWA_Lvd5vFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVD5V_FLAG_MASK) >> PMC_LVSCR_LVD5V_FLAG_SHIFT);
}

/**
 * @brief Return HVD5V_FLAG value
 * @param pPMC  PMC instance
 * @return 0: HVD5V_STATUS has not changed; 1: HVD5V_STATUS has changed
 */
LOCAL_INLINE bool PMC_HWA_Hvd5vFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD5V_FLAG_MASK) >> PMC_LVSCR_HVD5V_FLAG_SHIFT);
}

/**
 * @brief Return LVR5V_RPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr5vRpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR5V_RPM_FLAG_MASK) >> PMC_LVSCR_LVR5V_RPM_FLAG_SHIFT);
}


/**
 * @brief Return LVR5V_FPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr5vFpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR5V_FPM_FLAG_MASK) >> PMC_LVSCR_LVR5V_FPM_FLAG_SHIFT);
}

/**
 * @brief Clear LVR5V_RPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr5vRpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR5V_RPM_FLAG_MASK)) | PMC_LVSCR_LVR5V_RPM_FLAG_MASK);
}

/**
 * @brief Clear LVR5V_FPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr5vFpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR5V_FPM_FLAG_MASK)) | PMC_LVSCR_LVR5V_FPM_FLAG_MASK);
}

/**
 * @brief Clear LVR5V_FLAG, w1c
 *
 */
LOCAL_INLINE void PMC_HWA_ClearLvd5vFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVD5V_FLAG_MASK)) | PMC_LVSCR_LVD5V_FLAG_MASK);
}

/**
 * @brief Clear HVD5V_FLAG, w1c
 *
 */
LOCAL_INLINE void PMC_HWA_ClearHvd5vFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_HVD5V_FLAG_MASK)) | PMC_LVSCR_HVD5V_FLAG_MASK);
}

/**
 * @brief Return LVD5V_STATUS on V5 domain in FPM
 * @param pPMC  PMC instance
 * @return 0: Voltage on V5 is above low-voltage detect threshold; 1: Voltage on V5 is below low-voltage detect threshold
 */
LOCAL_INLINE bool PMC_HWA_Lvd5vStatus(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVD5V_STATUS_MASK) >> PMC_LVSCR_LVD5V_STATUS_SHIFT);
}

/**
 * @brief Return HVD5V_STATUS on V5 domain in FPM
 * @param pPMC  PMC instance
 * @return 0: Voltage on V5 is below high-voltage detect threshold; 1: Voltage on V5 is above high-voltage detect threshold
 */
LOCAL_INLINE bool PMC_HWA_Hvd5vStatus(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD5V_STATUS_MASK) >> PMC_LVSCR_HVD5V_STATUS_SHIFT);
}

#endif

#if PMC_V25_SUPPORT
/**
 * @brief Return HVD2P5V_FLAG value
 * @param pPMC  PMC instance
 * @return 0: HVD2P5V_STATUS has not changed; 1: HVD2P5V_STATUS has changed
 */
LOCAL_INLINE bool PMC_HWA_Hvd2p5vFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD2P5V_FLAG_MASK) >> PMC_LVSCR_HVD2P5V_FLAG_SHIFT);
}

/**
 * @brief Return LVR2P5V_RPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr2p5vRpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK) >> PMC_LVSCR_LVR2P5V_RPM_FLAG_SHIFT);
}

/**
 * @brief Return LVR2P5V_FPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr2p5vFpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK) >> PMC_LVSCR_LVR2P5V_FPM_FLAG_SHIFT);
}

/**
 * @brief Clear LVR2P5V_RPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr2p5vRpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK)) | PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK);
}

/**
 * @brief Clear LVR2P5V_FPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr2p5vFpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK)) | PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK);
}

/**
 * @brief Clear HVD2P5V_FLAG, w1c
 *
 */
LOCAL_INLINE void PMC_HWA_ClearHvd2p5vFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_HVD2P5V_FLAG_MASK)) | PMC_LVSCR_HVD2P5V_FLAG_MASK);
}

/**
 * @brief Return HVD2P5V_STATUS on V25 domain in FPM
 * @param pPMC  PMC instance
 * @return 0: Voltage on V25 is below high-voltage detect threshold; 1: Voltage on V25 is above high-voltage detect threshold
 */
LOCAL_INLINE bool PMC_HWA_Hvd2p5vStatus(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD2P5V_STATUS_MASK) >> PMC_LVSCR_HVD2P5V_STATUS_SHIFT);
}
#endif

#if PMC_V3_SUPPORT
/**
 * @brief Return LVR3V_RPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr3vRpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR3V_RPM_FLAG_MASK) >> PMC_LVSCR_LVR3V_RPM_FLAG_SHIFT);
}

/**
 * @brief Return LVR3V_FPM_FLAG value
 * @param pPMC  PMC instance
 * @return 0: No low-voltage reset event has occurred; 1: Low-voltage reset event has occurred
 */
LOCAL_INLINE bool PMC_HWA_Lvr3vFpmFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_LVR3V_FPM_FLAG_MASK) >> PMC_LVSCR_LVR3V_FPM_FLAG_SHIFT);
}

/**
 * @brief Return HVD3V_FLAG value
 * @param pPMC  PMC instance
 * @return 0: HVD3V_STATUS has not changed; 1: HVD3V_STATUS has changed
 */
LOCAL_INLINE bool PMC_HWA_Hvd3vFlag(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD3V_FLAG_MASK) >> PMC_LVSCR_HVD3V_FLAG_SHIFT);
}

/**
 * @brief Clear LVR3V_RPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr3vRpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR3V_RPM_FLAG_MASK)) | PMC_LVSCR_LVR3V_RPM_FLAG_MASK);
}

/**
 * @brief Clear LVR3V_FPM_FLAG, w1c
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void PMC_HWA_ClearLvr3vFpmFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_LVR3V_FPM_FLAG_MASK)) | PMC_LVSCR_LVR3V_FPM_FLAG_MASK);
}

/**
 * @brief Clear HVD3V_FLAG, w1c
 *
 */
LOCAL_INLINE void PMC_HWA_ClearHvd3vFlag(PMC_Type *pPMC)
{
	pPMC->LVSCR = ((pPMC->LVSCR & (~PMC_LVSCR_HVD3V_FLAG_MASK)) | PMC_LVSCR_HVD3V_FLAG_MASK);
}

/**
 * @brief Return HVD5V_STATUS on V3 domain in FPM
 * @param pPMC  PMC instance
 * @return 0: Voltage on V3 is below high-voltage detect threshold; 1: Voltage on V3 is above high-voltage detect threshold
 */
LOCAL_INLINE bool PMC_HWA_Hvd3vStatus(const PMC_Type *pPMC)
{
    return (bool) ((pPMC->LVSCR & PMC_LVSCR_HVD3V_STATUS_MASK) >> PMC_LVSCR_HVD3V_STATUS_SHIFT);
}
#endif

#if PMC_BUFVREF10_SUPPORT
/**
 * @brief HWA Enable Buffered Vref10 in FPM
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void Pmc_HWA_EnableBufVref10Fpm(PMC_Type *pPMC)
{
	pPMC -> CONFIG |= PMC_CONFIG_BUF10_EN_MASK;
}

/**
 * @brief HWA Disable Buffered Vref10  in FPM
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void Pmc_HWA_DisableBufVref10Fpm(PMC_Type *pPMC)
{
	pPMC -> CONFIG &= (~PMC_CONFIG_BUF10_EN_MASK);
}
#else
/**
 * @brief HWA Enable v25 domain in RPM
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void Pmc_HWA_EnableV25Rpm(PMC_Type *pPMC)
{
	pPMC -> CONFIG |= PMC_CONFIG_RPM_VDD2P5_EN_MASK;
}

/**
 * @brief HWA Disable v25 domain in RPM
 * @param pPMC  PMC instance
 */
LOCAL_INLINE void Pmc_HWA_DisableV25Rpm(PMC_Type *pPMC)
{
	pPMC -> CONFIG &= (~PMC_CONFIG_RPM_VDD2P5_EN_MASK);
}
#endif



/** @}*/

#endif

#endif /* HWA_INCLUDE_HWA_PMC_H_ */

