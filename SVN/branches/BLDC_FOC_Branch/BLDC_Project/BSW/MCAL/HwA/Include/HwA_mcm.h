/**
 * @file HwA_mcm.h
 * @author Flagchip
 * @brief MCM hardware access layer
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
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#ifndef HWA_INCLUDE_HWA_MCM_H_
#define HWA_INCLUDE_HWA_MCM_H_
#include "device_header.h"

#if MCM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_mcm HwA_mcm
 * @ingroup module_driver_mcm
 * @{
 */

/**
 * @brief Get the value of MCM ACR.
 *
 * This function returns ACR value.
 *
 * @param pMcm MCM instance.
 * @return uint32_t the value of the ACR register.
 */
LOCAL_INLINE uint32_t MCM_HWA_GetAcr(MCM_Type *const pMcm)
{
    return pMcm->ACR;
}

/**
 * @brief Get the value of MCM FISCR.
 *
 * This function returns FISCR value.
 *
 * @param pMcm MCM instance.
 * @return uint32_t the value of the FISCR register.
 */
LOCAL_INLINE uint32_t MCM_HWA_GetFiscr(MCM_Type *const pMcm)
{
    return pMcm->FISCR;
}

/**
 * @brief Get the value of MCM CASPECR.
 *
 * This function returns CASPECR value.
 *
 * @param pMcm MCM instance.
 * @return uint32_t the value of the CASPECR register.
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCaspecr(MCM_Type *const pMcm)
{
    return pMcm->CASPECR;
}

/**
 * @brief Get the value of MCM CASPEIR.
 *
 * This function returns CASPEIR value.
 *
 * @param pMcm MCM instance.
 * @return uint32_t the value of the CASPEIR register.
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCaspeir(MCM_Type *const pMcm)
{
    return pMcm->CASPEIR;
}

/**
 * @brief Get the value of MCM CASFAR.
 *
 * This function returns CASFAR value. The register is read only.
 *
 * @param pMcm MCM instance.
 * @return uint32_t the value of the CASFAR register.
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCasfar(MCM_Type *const pMcm)
{
    return pMcm->CASFAR;
}

/**
 * @brief Get the value of MCM CASFATR.
 *
 * This function returns CASFATR value. The register is read only.
 *
 * @param pMcm MCM instance.
 * @return uint32_t the value of CASFATR register.
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCasfatr(MCM_Type *const pMcm)
{
    return pMcm->CASFATR;
}

/**
 * @brief Get the value of MCM CASFDR.
 *
 *  This function returns CASFDR value.
 *
 * @param pMcm MCM instance.
 * @return uint32_t the value of CASFDR register.
 */

LOCAL_INLINE uint32_t MCM_HWA_GetCasfdr(MCM_Type *const pMcm)
{
    return pMcm->CASFDR;
}

/**
 * @brief Return MCM_FISCR FIOC value
 *
 * @param pMcm MCM instance.
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool MCM_HWA_GetFpuFiocFlag(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->FISCR;
    u32TmpVal = (u32TmpVal & MCM_FISCR_FIOC_MASK) >> MCM_FISCR_FIOC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return MCM_FISCR FDZC value
 *
 * @param pMcm MCM instance.
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool MCM_HWA_GetFpuFdzcFlag(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->FISCR;
    u32TmpVal = (u32TmpVal & MCM_FISCR_FDZC_MASK) >> MCM_FISCR_FDZC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return MCM_FISCR FOFC value
 *
 * @param pMcm MCM instance.
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool MCM_HWA_GetFpuFofcFlag(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->FISCR;
    u32TmpVal = (u32TmpVal & MCM_FISCR_FOFC_MASK) >> MCM_FISCR_FOFC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return MCM_FISCR FUFC value
 *
 * @param pMcm MCM instance.
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool MCM_HWA_GetFpuFufcFlag(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->FISCR;
    u32TmpVal = (u32TmpVal & MCM_FISCR_FUFC_MASK) >> MCM_FISCR_FUFC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return MCM_FISCR FIXC value
 *
 * @param pMcm MCM instance.
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool MCM_HWA_GetFpuFixcFlag(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->FISCR;
    u32TmpVal = (u32TmpVal & MCM_FISCR_FIXC_MASK) >> MCM_FISCR_FIXC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return MCM_FISCR FIDC value
 *
 * @param pMcm MCM instance.
 * @return 0: No interrupt; 1: Interrupt occurred
 */
LOCAL_INLINE bool MCM_HWA_GetFpuFidcFlag(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->FISCR;
    u32TmpVal = (u32TmpVal & MCM_FISCR_FIDC_MASK) >> MCM_FISCR_FIDC_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Set FIOCE interrupt
 *
 * @param pMcm MCM instance.
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void MCM_HWA_SetFioceInt(MCM_Type *const pMcm, bool bEnable)
{
    pMcm->FISCR = ((pMcm->FISCR & (~(uint32_t)MCM_FISCR_FIOCE_MASK)) | (uint32_t)((bEnable?1U:0U) << MCM_FISCR_FIOCE_SHIFT));
}

/**
 * @brief Set FDZCE interrupt
 *
 * @param pMcm MCM instance.
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void MCM_HWA_SetFdzceInt(MCM_Type *const pMcm, bool bEnable)
{
    pMcm->FISCR = ((pMcm->FISCR & (~(uint32_t)MCM_FISCR_FDZCE_MASK)) | (uint32_t)((bEnable?1U:0U) << MCM_FISCR_FDZCE_SHIFT));
}

/**
 * @brief Set FOFCE interrupt
 *
 * @param pMcm MCM instance.
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void MCM_HWA_SetFofceInt(MCM_Type *const pMcm, bool bEnable)
{
    pMcm->FISCR = ((pMcm->FISCR & (~(uint32_t)MCM_FISCR_FOFCE_MASK)) | (uint32_t)((bEnable?1U:0U) << MCM_FISCR_FOFCE_SHIFT));
}

/**
 * @brief Set FUFCE interrupt
 *
 * @param pMcm MCM instance.
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void MCM_HWA_SetFufceInt(MCM_Type *const pMcm, bool bEnable)
{
    pMcm->FISCR = ((pMcm->FISCR & (~(uint32_t)MCM_FISCR_FUFCE_MASK)) | (uint32_t)((bEnable?1U:0U) << MCM_FISCR_FUFCE_SHIFT));
}

/**
 * @brief Set FIXCE interrupt
 *
 * @param pMcm MCM instance.
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void MCM_HWA_SetFixceInt(MCM_Type *const pMcm, bool bEnable)
{
    pMcm->FISCR = ((pMcm->FISCR & (~(uint32_t)MCM_FISCR_FIXCE_MASK)) | (uint32_t)((bEnable?1U:0U) << MCM_FISCR_FIXCE_SHIFT));
}

/**
 * @brief Set FIDCE interrupt
 *
 * @param pMcm MCM instance.
 * @param bEnable 1: enable interrupt 0: disable interrupt
 */
LOCAL_INLINE void MCM_HWA_SetFidceInt(MCM_Type *const pMcm, bool bEnable)
{
    pMcm->FISCR = ((pMcm->FISCR & (~(uint32_t)MCM_FISCR_FIDCE_MASK)) | (uint32_t)((bEnable?1U:0U) << MCM_FISCR_FIDCE_SHIFT));
}
/**
 * @brief Return MCM_CASPECR ECPR value
 *
 * @param pMcm MCM instance.
 * @return 0: Cache Parity Reporting disable; 1: Cache Parity Reporting enable
 */
LOCAL_INLINE bool MCM_HWA_GetCaspecrEcpr(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->CASPECR;
    u32TmpVal = (u32TmpVal & MCM_CASPECR_ECPR_MASK) >> MCM_CASPECR_ECPR_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable Cache Parity Reporting
 *
 * @param pMcm MCM instance.
 */
LOCAL_INLINE void MCM_HWA_EnableCacheParityReport(MCM_Type *const pMcm)
{
    pMcm->CASPECR |= MCM_CASPECR_ECPR_MASK;
}

/**
 * @brief Disable Cache Parity Reporting
 *
 * @param pMcm MCM instance.
 */
LOCAL_INLINE void MCM_HWA_DisableCacheParityReport(MCM_Type *const pMcm)
{
    pMcm->CASPECR &= ~(uint32_t)MCM_CASPECR_ECPR_MASK;
}

/**
 * @brief Disable Cache & ECC Reporting
 *
 * @param pMcm MCM instance.
 */
LOCAL_INLINE void MCM_HWA_DisableCacheEccReport(MCM_Type *const pMcm)
{
    pMcm->CASPECR = 0x0U;
}

/**
 * @brief Set CASPECR Register
 *
 * @param pMcm MCM instance.
 * @param u32Val The 32-bit value to be written into the CASPECR register for configuration or operation.
 */
LOCAL_INLINE void MCM_HWA_SetCASPECR(MCM_Type *const pMcm, uint32_t u32Val)
{
    pMcm->CASPECR = u32Val;
}
/**
 * @brief Return MCM_CASPECR ER1BR value
 *
 * @param pMcm MCM instance.
 * @return 0: RAM ECC 1 Bit Reporting disable; 1: RAM ECC 1 Bit Reporting enable
 */
LOCAL_INLINE bool MCM_HWA_GetCaspecrEr1br(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->CASPECR;
    u32TmpVal = (u32TmpVal & MCM_CASPECR_ER1BR_MASK) >> MCM_CASPECR_ER1BR_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Enable RAM ECC 1 Bit Reporting
 *
 * @param pMcm MCM instance.
 */
LOCAL_INLINE void MCM_HWA_EnableRamEcc1BitReport(MCM_Type *const pMcm)
{
    pMcm->CASPECR |= MCM_CASPECR_ER1BR_MASK;
}

/**
 * @brief Disable RAM ECC 1 Bit Reporting
 *
 * @param pMcm MCM instance.
 */
LOCAL_INLINE void MCM_HWA_DisableRamEcc1BitReport(MCM_Type *const pMcm)
{
    pMcm->CASPECR &= ~(uint32_t)MCM_CASPECR_ER1BR_MASK;
}

/**
 * @brief Return MCM_CASPECR ERNCR value
 *
 * @param pMcm MCM instance.
 * @return 0: RAM ECC Noncorrectable reporting disable; 1: RAM ECC Noncorrectable reporting enable
 */
LOCAL_INLINE bool MCM_HWA_GetCaspecrErncr(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->CASPECR;
    u32TmpVal = u32TmpVal & MCM_CASPECR_ERNCR_MASK;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Disable RAM ECC Ncr Reporting
 *
 * @param pMcm MCM instance.
 */
LOCAL_INLINE void MCM_HWA_DisableRamEccNcrReport(MCM_Type *const pMcm)
{
    pMcm->CASPECR &= ~(uint32_t)MCM_CASPECR_ERNCR_MASK;
}

/**
 * @brief Return MCM_CASPEIR PRESENT value
 *
 * @param pMcm MCM instance.
 * @return Valid bit
 */
LOCAL_INLINE bool MCM_HWA_GetCaspeirPresent(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->CASPEIR;
    u32TmpVal = (u32TmpVal & MCM_CASPEIR_PRESENT_MASK) >> MCM_CASPEIR_PRESENT_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return MCM_CASPEIR PEELOC value
 *
 * @param pMcm MCM instance.
 * @return PEELOC value
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCaspeirPeeloc(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->CASPEIR;
    u32TmpVal = (u32TmpVal & MCM_CASPEIR_PEELOC_MASK) >> MCM_CASPEIR_PEELOC_SHIFT;
    return u32TmpVal;
}

/**
 * @brief Return MCM_CASPEIR PE value
 *
 * @param pMcm MCM instance.
 * @return PE value
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCaspeirPe(MCM_Type *const pMcm)
{
    return ((pMcm->CASPEIR & MCM_CASPEIR_PE_MASK) >> MCM_CASPEIR_PE_SHIFT);
}

/**
 * @brief Return MCM_CASPEIR E1B value
 *
 * @param pMcm MCM instance.
 * @return E1B value
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCaspeirE1b(MCM_Type *const pMcm)
{
    return ((pMcm->CASPEIR & MCM_CASPEIR_E1B_MASK) >> MCM_CASPEIR_E1B_SHIFT);
}

/**
 * @brief Return MCM_CASPEIR ENC value
 *
 * @param pMcm MCM instance.
 * @return ENC value
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCaspeirEnc(MCM_Type *const pMcm)
{
    return (pMcm->CASPEIR & MCM_CASPEIR_ENC_MASK);
}

/**
 * @brief Return MCM_CASFATR MULT value
 *
 * @param pMcm MCM instance.
 * @return MULT value
 */
LOCAL_INLINE bool MCM_HWA_GetCasfatrMult(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->CASFATR;
    u32TmpVal = (u32TmpVal & MCM_CASFATR_MULT_MASK) >> MCM_CASFATR_MULT_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/**
 * @brief Return MCM_CASFATR PEMASTER value
 *
 * @param pMcm MCM instance.
 * @return PEMASTER value
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCasfatrPemaster(MCM_Type *const pMcm)
{
    return ((pMcm->CASFATR & MCM_CASFATR_PEMASTER_MASK) >> MCM_CASFATR_PEMASTER_SHIFT);
}

/**
 * @brief Return MCM_CASFATR PWR value
 *
 * @param pMcm MCM instance.
 * @return PWR value
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCasfatrPwr(MCM_Type *const pMcm)
{
    return ((pMcm->CASFATR & MCM_CASFATR_PWR_MASK) >> MCM_CASFATR_PWR_SHIFT);
}

/**
 * @brief Return MCM_CASFATR PESIZE value
 *
 * @param pMcm MCM instance.
 * @return PESIZE value
 */
LOCAL_INLINE uint32_t MCM_HWA_GetCasfatrPesize(MCM_Type *const pMcm)
{
    return ((pMcm->CASFATR & MCM_CASFATR_PESIZE_MASK) >> MCM_CASFATR_PESIZE_SHIFT);
}

/**
 * @brief Return MCM_CASFATR PEFPRT value
 *
 * @param pMcm MCM instance.
 * @return PEFPRT value
 */
LOCAL_INLINE bool MCM_HWA_GetCasfatrPefprt(MCM_Type *const pMcm)
{
    uint32_t u32TmpVal = pMcm->CASFATR;
    u32TmpVal = (u32TmpVal & MCM_CASFATR_PEFPRT_MASK) >> MCM_CASFATR_PEFPRT_SHIFT;
    return (bool)((u32TmpVal != 0U) ? true : false);
}

/** @}*/

#endif

#endif /* HWA_INCLUDE_HWA_MCM_H_ */
