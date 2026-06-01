/**
 * @file module_driver_cordic.h
 * @author Flagchip
 * @brief CORDIC driver type definition and API
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
#ifndef _DRIVER_MODULE_DRIVER_CORDIC_H_
#define _DRIVER_MODULE_DRIVER_CORDIC_H_

#include "HwA_cordic.h"

#if CORDIC_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_cordic
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @name  CORDIC API Service IDs
 * @{
 */
#define CORDIC_CIRCULAR_SIN_COS_ID                        0x00
#define CORDIC_CIRCULAR_RADICAL_ADD_ID                    0x01
#define CORDIC_CIRCULAR_ARCTAN_F_ID                       0x02
#define CORDIC_CIRCULAR_ARCTAN_ID                         0x03
#define CORDIC_CIRCULAR_SINH_COSH_ID                      0x04
#define CORDIC_CIRCULAR_RADICAL_SUB_ID                    0x05
#define CORDIC_CIRCULAR_ARCTANH_ID                        0x06
/**
 * @}
 */



/**
 * @name  CORDIC Error Codes
 * @{
 */
#define CORDIC_E_PARAM_INSTANCE     0x01U
/**
 * @}
 */


/**
 * @brief CORDIC instance type.
 */
typedef enum
{
    CORDIC_INSTANCE_0  = 0U,  /**< CORDIC instance 0 is selected. */
} CORDIC_InstanceType;




/**
 * @brief Circular sine and cosine type.
 */
typedef struct
{
    float sinx;   /**< Sine value. */
    float cosx;   /**< Cosine value. */
} CORDIC_SinCos_Type;

/**
 * @brief Circular hyperbolic sine and cosine type.
 */
typedef struct
{
    float sinxh;  /**< Hyperbolic sine value. */
    float cosxh;  /**< Hyperbolic cosine value. */
} CORDIC_SinhCosh_Type;

/**
 * @brief Circular radical type.
 */
typedef float CORDIC_Radical_Type;

/**
 * @brief Circular arctangent type.
 */
typedef float CORDIC_Arctan_Type;

/**
 * @brief Circular hyperbolic arctangent type.
 */
typedef float CORDIC_Arctanh_Type;



/**
 * @brief Computes sine and cosine values using the circular CORDIC algorithm.
 *
 * This function computes the sine and cosine of an angle specified in radians.
 * It uses the circular CORDIC algorithm to perform the computation.
 *
 * @param eInstance The instance of the CORDIC module to use.
 * @param radian The angle in radians for which to compute the sine and cosine.
 * @return A CORDIC_SinCos_Type structure containing the computed sine and cosine values.
 */
CORDIC_SinCos_Type Cordic_Circular_Sin_Cos(CORDIC_InstanceType eInstance, const float radian);

/**
 * @brief Computes the angle given the x and y components using the circular CORDIC algorithm.
 *
 * This function computes the angle given the x and y components using the circular
 * CORDIC algorithm in vector mode.
 *
 * @param eInstance The instance of the CORDIC module to use.
 * @param x The x component.
 * @param y The y component.
 * @return A CORDIC_Radical_Type representing the computed angle.
 */
CORDIC_Radical_Type Cordic_Circular_Radical_Add(CORDIC_InstanceType eInstance, const float x, const float y);

/**
 * @brief Computes the arctangent of a value using the circular CORDIC algorithm.
 *
 * This function computes the arctangent of a value using the circular CORDIC
 * algorithm in vector mode. It handles special cases for large input values.
 *
 * @param eInstance The instance of the CORDIC module to use.
 * @param y The value for which to compute the arctangent.
 * @return A CORDIC_Arctan_Type representing the computed arctangent value.
 */
CORDIC_Arctan_Type Cordic_Circular_Arctan_F(CORDIC_InstanceType eInstance, const float y);

/**
 * @brief Computes the arctangent of a point given its x and y coordinates using the circular CORDIC algorithm.
 *
 * This function computes the arctangent of a point defined by its x and y
 * coordinates using the circular CORDIC algorithm in vector mode.
 *
 * @param eInstance The instance of the CORDIC module to use.
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return A CORDIC_Arctan_Type representing the computed arctangent value.
 */
CORDIC_Arctan_Type Cordic_Circular_Arctan(CORDIC_InstanceType eInstance, const int32_t x, const int32_t y);

/**
 * @brief Computes the hyperbolic sine and cosine of a value using the circular CORDIC algorithm.
 *
 * This function computes the hyperbolic sine and cosine of a value using the
 * circular CORDIC algorithm in rotate mode.
 *
 * @param eInstance The instance of the CORDIC module to use.
 * @param z The value for which to compute the hyperbolic sine and cosine.
 * @return A CORDIC_SinhCosh_Type structure containing the computed hyperbolic sine and cosine values.
 */
CORDIC_SinhCosh_Type Cordic_Circular_Sinh_Cosh(CORDIC_InstanceType eInstance, const float z);

/**
 * @brief Computes the circular radical subtraction using the CORDIC algorithm.
 *
 * This function computes the circular radical subtraction of two input values `x` and `y`.
 * It uses the CORDIC hardware abstraction layer (HAL) functions to perform the calculations.
 *
 * @param eInstance The CORDIC instance identifier.
 * @param x The first input value.
 * @param y The second input value.
 * @return CORDIC_Radical_Type The result of the circular radical subtraction.
 */
CORDIC_Radical_Type Cordic_Circular_Radical_Sub(CORDIC_InstanceType eInstance, const float x, const float y);

/**
 * @brief Computes the hyperbolic arctangent using the CORDIC algorithm.
 *
 * This function calculates the hyperbolic arctangent of a given input value `y`.
 * It uses the CORDIC hardware abstraction layer (HAL) functions to perform the calculations.
 *
 * @param eInstance The CORDIC instance identifier.
 * @param y The input value for which to compute the hyperbolic arctangent.
 * @return CORDIC_Arctanh_Type The computed hyperbolic arctangent value.
 */
CORDIC_Arctanh_Type Cordic_Circular_Arctanh(CORDIC_InstanceType eInstance, const float y);


#if defined(__cplusplus)
}
#endif
/**
 * @}
 */
#endif

#endif

