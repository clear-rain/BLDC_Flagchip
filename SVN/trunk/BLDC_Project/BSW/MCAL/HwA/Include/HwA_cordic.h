/**
 * @file HwA_cordic.h
 * @author Flagchip
 * @brief CORDIC hardware access layer
 * @version 2.0.0
 * @date 2024-02-08
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/
#ifndef _HWA_CORDIC_H_
#define _HWA_CORDIC_H_
#include "device_header.h"

#if CORDIC_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_cordic HwA_cordic
 * @ingroup module_driver_cordic
 * @{
 */

/**
 * @brief CORDIC Iteration Type
 *
 * Defines the number of iterations for the CORDIC algorithm.
 */
typedef enum
{
    CORDIC_Iteration_8 = 0,
    CORDIC_Iteration_16,
    CORDIC_Iteration_24
} CORDIC_IterationType;

/**
 * @brief CORDIC System Type
 *
 * Specifies the system type for the CORDIC algorithm.
 */
typedef enum
{
    CORDIC_Trigonometric = 0,
    CORDIC_Hyperbolic,
    CORDIC_Linear
} CORDIC_SystemType;

/**
 * @brief CORDIC Mode Type
 *
 * Specifies the operation mode for the CORDIC algorithm.
 */
typedef enum
{
    CORDIC_Rotate = 0,
    CORDIC_Vector
} CORDIC_ModeType;

#define CORDIC_CTR_VAL(a,b,c,d)  (CORDIC_CTRL_IE(a) | CORDIC_CTRL_ITER(b) | CORDIC_CTRL_OS(c) |  CORDIC_CTRL_MODE(d))

/**
 * @brief Set CORDIC module Control register
 *
 * Sets the control register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @param u32Value Control register value to set.
 */
LOCAL_INLINE void Cordic_HWA_SetCtrl(CORDIC_Type* const pCordic, uint32_t u32Value)
{
    pCordic->CTRL = u32Value;
}

/**
 * @brief Read CORDIC module Control register
 *
 * Reads the control register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @return Control register value.
 */
LOCAL_INLINE uint32_t Cordic_HWA_GetCtrl(CORDIC_Type* const pCordic)
{
    return (uint32_t)(pCordic->CTRL);
}

/**
 * @brief Set CORDIC module X Input register
 *
 * Sets the X input register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @param u32Value X input register value to set.
 */
LOCAL_INLINE void Cordic_HWA_Set_XInput(CORDIC_Type* const pCordic, uint32_t u32Value)
{
    pCordic->X_INPUT = u32Value;
}

/**
 * @brief Set CORDIC module Y Input register
 *
 * Sets the Y input register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @param u32Value Y input register value to set.
 */
LOCAL_INLINE void Cordic_HWA_Set_YInput(CORDIC_Type* const pCordic, uint32_t u32Value)
{
    pCordic->Y_INPUT = u32Value;
}

/**
 * @brief Set CORDIC module Z Input register
 *
 * Sets the Z input register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @param u32Value Z input register value to set.
 */
LOCAL_INLINE void Cordic_HWA_Set_ZInput(CORDIC_Type* const pCordic, uint32_t u32Value)
{
    pCordic->Z_INPUT = u32Value;
}

/**
 * @brief Read CORDIC module X Output register
 *
 * Reads the X output register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @return X output register value.
 */
LOCAL_INLINE uint32_t Cordic_HWA_Get_XOutput(CORDIC_Type* const pCordic)
{
    return (uint32_t)(pCordic->X_OUTPUT);
}

/**
 * @brief Read CORDIC module Y Output register
 *
 * Reads the Y output register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @return Y output register value.
 */
LOCAL_INLINE uint32_t Cordic_HWA_Get_YOutput(CORDIC_Type* const pCordic)
{
    return (uint32_t)(pCordic->Y_OUTPUT);
}

/**
 * @brief Read CORDIC module Z Output register
 *
 * Reads the Z output register value of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @return Z output register value.
 */
LOCAL_INLINE uint32_t Cordic_HWA_Get_ZOutput(CORDIC_Type* const pCordic)
{
    return (uint32_t)(pCordic->Z_OUTPUT);
}

/**
 * @brief Read CORDIC module State
 *
 * Reads the current state of the CORDIC module.
 *
 * @param pCordic Pointer to the CORDIC module.
 * @return Current state of the CORDIC module.
 */
LOCAL_INLINE bool Cordic_HWA_Get_Stat(CORDIC_Type* const pCordic)
{
    return (bool)(pCordic->STAT & CORDIC_STAT_DONE_MASK);
}

/**
 * @}
 */

#endif

#endif
