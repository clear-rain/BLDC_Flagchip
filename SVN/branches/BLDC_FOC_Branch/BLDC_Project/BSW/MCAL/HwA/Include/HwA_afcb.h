/**
 * @file HwA_afcb.h
 * @author Flagchip095
 * @brief AFCB hardware access layer
 * @version 2.0.0
 * @date 2024-03-09
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
#ifndef __HWA_AFCB_H_
#define __HWA_AFCB_H_

#include "device_header.h"

#if AFCB_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_afcb HwA_afcb
 * @ingroup module_driver_afcb
 * @{
 */

/**
 * @brief Set a bit in MAAR0 according the shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param mbit_shift  the shift of bit in the register MAAR0.
 */
LOCAL_INLINE void AFCB_HWA_SetMarrBit(AFCB_Type *const pAfcb,uint8_t mbit_shift)
{
	pAfcb->MAAR0 |= (uint32_t)(1<<mbit_shift);
}

/**
 * @brief Clear a bit in MAAR0 according the shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param mbit_shift  the shift of bit in the register MAAR0.
 */
LOCAL_INLINE void AFCB_HWA_ClearMarrBit(AFCB_Type *const pAfcb,uint8_t mbit_shift)
{
	pAfcb->MAAR0 &= (uint32_t)~(1<<mbit_shift);
}

/**
 * @brief Set a bit in SEG0PAP[x]  according the index and bit shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param index the index of register in Array SEG0PAP
 * @param sbit_shift the bit shift
 */
LOCAL_INLINE void AFCB_HWA_SetSEG0PAPBit(AFCB_Type *const pAfcb, uint8_t index,uint8_t sbit_shift)
{
	(pAfcb->SEG0PAP)[index] |= (uint32_t)(1<<sbit_shift);
}


/**
 * @brief Clear a bit in SEG0PAP[x]  according the index and bit shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param index the index of register in Array SEG0PAP
 * @param sbit_shift the bit shift
 */
LOCAL_INLINE void AFCB_HWA_ClearSEG0PAPBit(AFCB_Type *const pAfcb, uint8_t index,uint8_t sbit_shift)
{
	(pAfcb->SEG0PAP)[index] &= (uint32_t)~(1<<sbit_shift);
}

/**
 * @brief Get bit value in SEG0PAP[x]  according the index and bit shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param index the index of register in Array SEG0PAP
 * @param sbit_shift the bit shift
 */
LOCAL_INLINE uint32_t AFCB_HWA_GetSEG0PAPBit(AFCB_Type *const pAfcb, uint8_t index,uint8_t sbit_shift)
{
	return ((pAfcb->SEG0PAP[index])&(uint32_t)(1<<sbit_shift))>>sbit_shift;
}

/**
 * @brief Set a bit in SEG1PAP[x]  according the index and bit shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param index the index of register in Array SEG1PAP
 * @param sbit_shift the bit shift
 */
LOCAL_INLINE void AFCB_HWA_SetSEG1PAPBit(AFCB_Type *const pAfcb, uint8_t index,uint8_t sbit_shift)
{
	(pAfcb->SEG1PAP)[index] |= (uint32_t)(1<<sbit_shift);
}

/**
 * @brief Clear a bit in SEG1PAP[x]  according the index and bit shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param index the index of register in Array SEG1PAP
 * @param sbit_shift the bit shift
 */
LOCAL_INLINE void AFCB_HWA_ClearSEG1PAPBit(AFCB_Type *const pAfcb, uint8_t index,uint8_t sbit_shift)
{
	(pAfcb->SEG1PAP)[index] &= (uint32_t)~(1<<sbit_shift);
}

/**
 * @brief Get bit value in SEG1PAP[x]  according the index and bit shift.
 *
 * @param pAfcb the base address of the pAfcb instance.
 * @param index the index of register in Array SEG1PAP
 * @param sbit_shift the bit shift
 */
LOCAL_INLINE uint32_t AFCB_HWA_GetSEG1PAPBit(AFCB_Type *const pAfcb, uint8_t index,uint8_t sbit_shift)
{
	return ((pAfcb->SEG1PAP[index])&(uint32_t)(1<<sbit_shift))>>sbit_shift;
}

/**
 * @brief Get Register Value Of MAAR0
 *
 *@param pAfcb the base address of the pAfcb instance.
 */
LOCAL_INLINE uint32_t AFCB_HWA_GetMARR0(AFCB_Type *const pAfcb)
{
	return pAfcb->MAAR0;
}

/**
 * @brief Set Register Value Of MAAR0
 *
 *@param pAfcb the base address of the pAfcb instance.
 *@param config_Value the value to write the MAAR0 Register
 */
LOCAL_INLINE void AFCB_HWA_SetMARR0(AFCB_Type *const pAfcb, uint32_t config_Value)
{
	pAfcb->MAAR0 = config_Value;
}

/**
 * @brief Set Register Value Of SEG0PAP[x]
 *
 *@param pAfcb the base address of the pAfcb instance.
 *@param index the index of register in Array SEG0PAP
 *@param config_Value the value to write the SEG0PAP[x] Register
 */
LOCAL_INLINE void AFCB_HWA_SetSEG0PAP(AFCB_Type *const pAfcb, uint8_t index,uint32_t config_Value)
{
	(pAfcb->SEG0PAP)[index] = config_Value;
}

/**
 * @brief Get Register Value Of SEG0PAP[x]
 *
 *@param pAfcb the base address of the pAfcb instance.
 *@param index the index of register in Array SEG0PAP
 *
 *@return Returns the 32-bit register value at the specified index position.
 */
LOCAL_INLINE uint32_t AFCB_HWA_ReadSEG0PAP(AFCB_Type *const pAfcb, uint8_t index)
{
	return (pAfcb->SEG0PAP)[index];
}

/**
 * @brief Set Register Value Of SEG1PAP[x]
 *
 *@param pAfcb the base address of the pAfcb instance.
 *@param index the index of register in Array SEG1PAP
 *@param config_Value the value to write the SEG1PAP[x] Register
 *@return Returns the 32-bit register value at the specified index position.
 */
LOCAL_INLINE void AFCB_HWA_SetSEG1PAP(AFCB_Type *const pAfcb, uint8_t index, uint32_t config_Value)
{
	(pAfcb->SEG1PAP)[index] = config_Value;
}

/**
 * @brief Get Register Value Of SEG1PAP[x]
 *
 *@param pAfcb the base address of the pAfcb instance.
 *@param index the index of register in Array SEG1PAP
 *@return Returns the 32-bit register value at the specified index position.
 */
LOCAL_INLINE uint32_t AFCB_HWA_ReadSEG1PAP(AFCB_Type *const pAfcb, uint8_t index)
{
	return (pAfcb->SEG1PAP)[index];
}

/** @}*/

#endif


#endif
