/**
 * @file HwA_erm.h
 * @author Flagchip100
 * @brief ERM hardware access layer
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
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#ifndef HWA_INCLUDE_HWA_ERM_H_
#define HWA_INCLUDE_HWA_ERM_H_

#include "device_header.h"

#if ERM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_erm HwA_erm
 * @ingroup module_driver_erm
 * @{
 */

/**
 * @brief Define a mask for all flags in the ERM_SR0 register.
 *        This constant specifies the mask for all flags in the ERM_SR0 status register.
 */
#define ERM_SR0_ALLFLAG_MASK 0xCCCCC000U

/**
 * @brief Select the ERM channel
 *
 */
typedef enum
{
    ERM_CTCM       = 0U,                /**< CTCM channel */
    ERM_DTCM       = 1U,                /**< DTCM channel */
    ERM_PFLASH     = 2U,                /**< PFLASH channel */
#if (ERM_DFLASH_SUPPORT == STD_ON)
    ERM_DFLASH     = 3U,                /**< DFLASH channel */
#endif
    ERM_DMA        = 4U                 /**< DMA channel */
} ERM_channelType;

/**
 * @brief set ERM CR0 register.
 *
 * This function configures the ERM CR0 registe.
 *
 * @param pErm ERM Instance
 * @param u32ErmCr0Val Set ERM CR0 register value.
 */
LOCAL_INLINE void ERM_HWA_SetCR0Register(ERM_Type *const pErm, uint32_t u32ErmCr0Val)
{
    pErm->CR0 = u32ErmCr0Val;
}

/**
 * @brief Read ERM SR0 register
 *
 * @param pErm ERM Instance
 * @return the value of ERM_SR0 register
 */
LOCAL_INLINE uint32_t ERM_HWA_GetSr0(ERM_Type *const pErm)
{
    return pErm->SR0;
}

/**
 * @brief Set ERM SR0 register
 *
 * @param pErm ERM Instance
 * @param u32Val the value of the register
 */
LOCAL_INLINE void ERM_HWA_SetSR0(ERM_Type *const pErm, uint32_t u32Val)
{
    pErm->SR0 = u32Val;
}

/**
 * @brief ERM Read EARn address.
 *
 * @param pErm ERM Instance
 * @param eChannel The channel type
 * @return u32Address The error address
 */
LOCAL_INLINE uint32_t ERM_HWA_GetEARn(ERM_Type *const pErm, ERM_channelType eChannel)
{
    uint32_t u32Address = 0U;
    switch (eChannel)
    {
        case ERM_CTCM:
        	u32Address = pErm->EAR0;
            break;
        case ERM_DTCM:
        	u32Address = pErm->EAR1;
            break;
        case ERM_PFLASH:
            u32Address = pErm->EAR2;
            break;
#if (ERM_DFLASH_SUPPORT == STD_ON)
        case ERM_DFLASH:
            u32Address = pErm->EAR3;
            break;
#endif
        case ERM_DMA:
            u32Address = pErm->EAR4;
            break;
        default:
            break;

    }
   	return u32Address;
}

/** @}*/

#endif

#endif /* HWA_INCLUDE_HWA_ERM_H_ */
