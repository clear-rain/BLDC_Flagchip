/**
 * @file HwA_sec.h
 * @author Flagchip075
 * @brief SEC hardware access layer
 * @version 2.0.0
 * @date 2024-11-16
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#ifndef _HWA_SEC_H_
#define _HWA_SEC_H_

#include "device_header.h"

#if SEC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_sec HwA_sec
 * @ingroup module_driver_sec
 * @{
 */

/* DEN Bit Fields */
/**
 *@brief Enable the debug module
 **/
LOCAL_INLINE void SEC_HWA_EnDebug(SEC_Type *const pSec)
{
	pSec->DEN = SEC_DEN_DEN(0X5) ;
}

/* FSEC0 Bit Fields */
/**
 * @brief Get the system security KEY0
 **/
LOCAL_INLINE uint16_t SEC_HWA_GetSScontrol0(SEC_Type *const pSec)
{
    return (uint16_t)((pSec->FSEC0) & (SEC_FSEC0_SSC0_MASK));
}

/* FSEC1 Bit Fields */
/**
 * @brief Get the system security KEY1
 **/
LOCAL_INLINE uint16_t SEC_HWA_GetSScontrol1(SEC_Type *const pSec)
{
    return (uint16_t)((pSec->FSEC1) & (SEC_FSEC1_SSC1_MASK));
}

/* DCWOR Bit Fields */
/**
 * @brief Re-enable the Debug mode.
 * @note  This register can only be write once. startup_fc4150.s has lock the register.
 **/
LOCAL_INLINE void SEC_HWA_ReEnDebug(SEC_Type *const pSec)
{
	pSec->DCWOR = ((pSec->DCWOR & (~SEC_DCWOR_DEA_MASK)) | SEC_DCWOR_DEA(0X5));
}


/**
 * @brief Get the Re-enable Debug permission.
 **/
LOCAL_INLINE bool SEC_HWA_GetReEnDebug(SEC_Type *const pSec)
{
    bool ret = false;
    uint8_t  dea = (uint8_t)((pSec->DCWOR & (SEC_DCWOR_DEA_MASK)) >> SEC_DCWOR_DEA_SHIFT);
    if (dea == 0x5U)
    {
        ret = true;
    }
    return ret;
}


/**
 * @brief Enable the write operation for SEC register.
 * @note  This register can only be write once. startup_fc4150.s has lock the register.
 **/
LOCAL_INLINE void SEC_HWA_WriteUnlock(SEC_Type *const pSec)
{
	pSec->DCWOR = ((pSec->DCWOR & (~SEC_DCWOR_RWL_MASK)) | SEC_DCWOR_RWL(0X5));
}


/**
 * @brief Get the sec write permission
 * @return true means allow write. false means  forbid write.
*/
LOCAL_INLINE bool SEC_HWA_GetWritePer(SEC_Type *const pSec)
{
    bool ret = false;
    uint8_t rwl = (uint8_t)((pSec->DCWOR & (SEC_DCWOR_RWL_MASK)) >> SEC_DCWOR_RWL_SHIFT);
    if ((rwl == 0x5U) || (rwl == 0xFU))
    {
        ret = true;
    }
    return ret;
}


/* DEK Bit Fields */
/**
 * @brief Enable the write operation for SEC register.
 **/
LOCAL_INLINE void SEC_HWA_WriteReEnKeyn(SEC_Type *const pSec, uint8_t count, uint32_t key)
{
    if (count < 4u)
    {
    	pSec->DEN = key;
    }
}

/* TME Bit Fields */
/**
 *@brief Enable the Test module
 **/
LOCAL_INLINE void SEC_HWA_EnTest(SEC_Type *const pSec)
{
	pSec->TME = SEC_TME_TME(0X5) ;
}

/* TMEA Bit Fields */
/**
 * @brief Re-Enable Test mode
 **/
LOCAL_INLINE void SEC_HWA_ReEnTest(SEC_Type *const pSec)
{
	pSec->TMEA = SEC_TMEA_TMEA(0X5) ;
}


/**
 * @brief Get the Re-enable Test permission.
 **/
LOCAL_INLINE bool SEC_HWA_GetReEnTest(SEC_Type *const pSec)
{
    bool ret = false;
    uint8_t  tmea = (uint8_t)((pSec->TMEA & (SEC_TMEA_TMEA_MASK)) >> SEC_TMEA_TMEA_SHIFT);
    if ((tmea == 0x5U) || (tmea == 0xFU))
    {
        ret = true;
    }
    return ret;
}



/* TMEK Bit Fields */
/**
 *@brief write Test re-enable mode key
 *
 */
LOCAL_INLINE void SEC_HWA_ReEnTestKey(SEC_Type *const pSec, uint32_t testkey)
{
	pSec->TMEK = SEC_TMEK_TMEK(testkey) ;
}


/* FCR0 Bit Fields */
/**
 * @brief Enable the Mass Erase
 */
LOCAL_INLINE void SEC_HWA_EnME(SEC_Type *const pSec)
{
	pSec->FCR0 = ((pSec->FCR0 & (~SEC_FCR0_MED_MASK)) | SEC_FCR0_MED(0x5));
}


/**
 * @brief Enable the Block 0 NVR read .
 */
LOCAL_INLINE void SEC_HWA_EnReadB0NVR(SEC_Type *const pSec)
{
	pSec->FCR0 = ((pSec->FCR0 & (~SEC_FCR0_NRP_MASK)) | SEC_FCR0_NRP(0x5)) ;
}


/**
 * @brief Disable the Block 0 NVR read .
 */
LOCAL_INLINE void SEC_HWA_DisReadB0NVR(SEC_Type *const pSec)
{
	pSec->FCR0 = ((pSec->FCR0 & (~SEC_FCR0_NRP_MASK)) | SEC_FCR0_NRP(0xA)) ;
}


/**
 * @brief Enable the Block 0 NVR write .
 */
LOCAL_INLINE void SEC_HWA_EnWriteB0NVR(SEC_Type *const pSec)
{
	pSec->FCR0 = ((pSec->FCR0 & (~SEC_FCR0_NWP_MASK)) | SEC_FCR0_NWP(0x5)) ;
}


/**
 * @brief Disable the Block 0 NVR write .
 */
LOCAL_INLINE void SEC_HWA_DisWriteB0NVR(SEC_Type *const pSec)
{
	pSec->FCR0 = ((pSec->FCR0 & (~SEC_FCR0_NWP_MASK)) | SEC_FCR0_NWP(0xA)) ;
}


/* BCKn Fields */
/**
 * @brief Write the Block cipher key
 **/
LOCAL_INLINE void SEC_HWA_WriteCipKey(SEC_Type *const pSec, uint8_t count, uint32_t key)
{
    if (count < 8u)
    {
    	pSec->BCK[count] = SEC_BCK_BCK(key);
    }
}

/* BC0 Bit Fields */
/**
 * @brief Get NMI Pin mode.
 * @return  true means NMI Pin enable, false means NMI Pin disable.
 **/
LOCAL_INLINE bool SEC_HWA_GetNmiPin(SEC_Type *const pSec)
{

    return (bool)(pSec->BC0 & SEC_BC0_NMIDIS_MASK);
}


/**
 * @brief Get Reset Pin mode.
 *  @return  true means Reset Pin enable, false means Reset Pin disable.
 **/
LOCAL_INLINE bool SEC_HWA_GetResetPin(SEC_Type *const pSec)
{
    return (bool)(pSec->BC0 & SEC_BC0_RSTDIS_MASK);
}

/** @}*/

#endif

#endif /* _HWA_SEC_H_ */
