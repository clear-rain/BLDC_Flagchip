/**
 * @file HwA_eim.h
 * @author Flagchip100
 * @brief EIM hardware access layer
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
*   2.0.0       2024-04-20    Flagchip100   N/A          First version
*********************************************************************************/

#ifndef HWA_INCLUDE_HWA_EIM_H_
#define HWA_INCLUDE_HWA_EIM_H_

#include "device_header.h"

#if EIM_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_eim HwA_eim
 * @ingroup module_driver_eim
 * @{
 */

/**
 * @brief Select the EIM channel
 *
 */
typedef enum
{
    EIM_CHR0 = 0U,   /**< EIM_CHR0 is selected */
    EIM_CHR1 = 1U,   /**< EIM_CHR1 is selected */
    EIM_CHR2 = 2U,   /**< EIM_CHR2 is selected */
    EIM_CHR3 = 3U,   /**< EIM_CHR3 is selected */
#if (EIM_MAXCHANNEL == 7u)
    EIM_CHR4 = 4U,   /**< EIM_CHR4 is selected, 512K not support */
    EIM_CHR5 = 5U,   /**< EIM_CHR5 is selected, 512K not support */
    EIM_CHR6 = 6U,   /**< EIM_CHR6 is selected, 512K not support */
    EIM_CHR7 = 7U    /**< EIM_CHR7 is selected, 512K not support */
#endif
} EIM_CHRnType;

/**
 * @brief Select the EIM WORD0 channel
 *
 */
typedef enum
{
    EIM_WORD0_CHR0 = 0U,   /**< EIM_WORD0_CHR0 is selected */
    EIM_WORD0_CHR1 = 1U,   /**< EIM_WORD0_CHR1 is selected */
    EIM_WORD0_CHR2 = 2U,   /**< EIM_WORD0_CHR2 is selected */
    EIM_WORD0_CHR3 = 3U,   /**< EIM_WORD0_CHR3 is selected */
#if (EIM_MAXCHANNEL == 7u)
    EIM_WORD0_CHR4 = 4U,   /**< EIM_WORD0_CHR4 is selected, 512K not support */
    EIM_WORD0_CHR5 = 5U,   /**< EIM_WORD0_CHR5 is selected, 512K not support */
    EIM_WORD0_CHR6 = 6U,   /**< EIM_WORD0_CHR6 is selected, 512K not support */
    EIM_WORD0_CHR7 = 7U    /**< EIM_WORD0_CHR7 is selected, 512K not support */
#endif
} EIM_WORD0CHRnType;

/**
 * @brief The Channel index of EIM word1
 *
 */
typedef enum
{
    EIM_WORD1_CHR0 = 0U,   /**< EIM_WORD1_CHR0 is selected */
    EIM_WORD1_CHR1 = 1U,   /**< EIM_WORD1_CHR1 is selected */
    EIM_WORD1_CHR2 = 2U,   /**< EIM_WORD1_CHR2 is selected */
    EIM_WORD1_CHR3 = 3U    /**< EIM_WORD1_CHR3 is selected */

} EIM_WORD1CHRnType;

/**
 * @brief Enable EIM Global Error Injection
 *
 * @param pEim EIM Instance
 */
LOCAL_INLINE void EIM_HWA_EnableGlobalErrorInjection(EIM_Type *const pEim)
{
    pEim->CR |= EIM_CR_GEIEN_MASK;
}

/**
 * @brief Disable EIM Global Error Injection
 *
 * @param pEim EIM Instance
 */
LOCAL_INLINE void EIM_HWA_DisableGlobalErrorInjection(EIM_Type *const pEim)
{
    pEim->CR &= ~(uint32_t) EIM_CR_GEIEN_MASK;
}

/**
 * @brief Set word0 value
 *
 * @param pEim EIM Instance
 * @param eChannel The select channel of EIM WORD0
 * @param u32Val The value the EIM WORD0_CHRn
 */
LOCAL_INLINE void EIM_HWA_SetWORD0_Channel(EIM_Type *const pEim, EIM_WORD0CHRnType eChannel, uint32_t u32Val)
{
    switch (eChannel)
    {
        case EIM_WORD0_CHR0:
            pEim->WORD0_CHR0 = u32Val;
            break;
        case EIM_WORD0_CHR1:
            pEim->WORD0_CHR1 = u32Val;
            break;
        case EIM_WORD0_CHR2:
            pEim->WORD0_CHR2 = u32Val;
            break;
        case EIM_WORD0_CHR3:
            pEim->WORD0_CHR3 = u32Val;
            break;
#if (EIM_MAXCHANNEL == 7u)
        case EIM_WORD0_CHR4:
            pEim->WORD0_CHR4 = u32Val;
            break;
        case EIM_WORD0_CHR5:
            pEim->WORD0_CHR5 = u32Val;
            break;
        case EIM_WORD0_CHR6:
            pEim->WORD0_CHR6 = u32Val;
            break;
        case EIM_WORD0_CHR7:
            pEim->WORD0_CHR7 = u32Val;
            break;
#endif
        default:
            break;
    }
}

/**
 * @brief Set word1 value
 *
 * @param pEim EIM Instance
 * @param eChannel The select channel of EIM WORD1
 * @param u32Val The value the EIM WORD1_CHRn
 */
LOCAL_INLINE void EIM_HWA_SetWORD1_Channel(EIM_Type *const pEim, EIM_WORD1CHRnType eChannel, uint32_t u32Val)
{
    switch (eChannel)
    {
        case EIM_WORD1_CHR0:
            pEim->WORD1_CHR0 = u32Val;
            break;
        case EIM_WORD1_CHR1:
            pEim->WORD1_CHR1 = u32Val;
            break;
        case EIM_WORD1_CHR2:
            pEim->WORD1_CHR2 = u32Val;
            break;
        case EIM_WORD1_CHR3:
            pEim->WORD1_CHR3 = u32Val;
            break;
        default:
            break;
    }
}

/**
 * @brief Set EIM channel Enable register
 *
 * @param pEim EIM Instance
 * @param u32Val the value of the register
 */
LOCAL_INLINE void EIM_HWA_SetChnReg(EIM_Type *const pEim, uint32_t u32Val)
{
    pEim->CHENR = u32Val;
}

/**
 * @brief Read EIM channel Enable register
 *
 * @param pEim EIM Instance
 * @return the value of EIM_CHENR register
 */
LOCAL_INLINE uint32_t EIM_HWA_GetChenr(EIM_Type *const pEim)
{
    return pEim->CHENR;
}

/**
 * @brief Clear all EIM WORD0 channels
 *
 * @param pEim EIM Instance
 * @return the value of EIM_CHENR register
 */
LOCAL_INLINE void EIM_HWA_ClearWORD0_Channels(EIM_Type *const pEim)
{
    pEim->WORD0_CHR0 = 0x0U;
    pEim->WORD0_CHR1 = 0x0U;
    pEim->WORD0_CHR2 = 0x0U;
    pEim->WORD0_CHR3 = 0x0U;
#if (EIM_MAXCHANNEL == 7u)
    pEim->WORD0_CHR4 = 0x0U;
    pEim->WORD0_CHR5 = 0x0U;
    pEim->WORD0_CHR6 = 0x0U;
    pEim->WORD0_CHR7 = 0x0U;
#endif
}

/**
 * @brief Clear all EIM WORD1 channels
 *
 * @param pEim EIM Instance
 * @return the value of EIM_CHENR register
 */
LOCAL_INLINE void EIM_HWA_ClearWORD1_Channels(EIM_Type *const pEim)
{
    pEim->WORD1_CHR0 = 0x0U;
    pEim->WORD1_CHR1 = 0x0U;
    pEim->WORD1_CHR2 = 0x0U;
    pEim->WORD1_CHR3 = 0x0U;
}

/** @}*/

#endif

#endif /* HWA_INCLUDE_HWA_EIM_H_ */
