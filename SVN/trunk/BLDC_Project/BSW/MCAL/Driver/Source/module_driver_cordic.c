/**
 * @file module_driver_cordic.c
 * @author Flagchip
 * @brief CORDIC driver source code
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
#include "module_driver_cordic.h"

#if CORDIC_INSTANCE_COUNT > 0U

#ifndef CORDIC_DEV_ERROR_REPORT
    #define CORDIC_DEV_ERROR_REPORT    STD_OFF
#endif

#if CORDIC_DEV_ERROR_REPORT == STD_ON
    #define CORDIC_ReportDevError(func, error)     ReportDevError(CORDIC_MODULE_ID, func, error)
#endif


/**
 * @brief Sign bit for the CORDIC algorithm.
 *
 * Represents the sign bit in a single-precision floating-point number.
 */
#define CORDIC_SIGN_BIT               0x80000000UL

/**
 * @brief Exponent bit for the CORDIC algorithm.
 *
 * Represents the exponent bits in a single-precision floating-point number.
 */
#define CORDIC_EXP_BIT                0x7F800000UL

/**
 * @brief Tail bit for the CORDIC algorithm.
 *
 * Represents the mantissa bits in a single-precision floating-point number.
 */
#define CORDIC_TAIL_BIT               0x007FFFFFUL

/**
 * @brief Scaling factor K for the CORDIC algorithm.
 *
 * Represents the scaling factor used in the CORDIC algorithm.
 */
#define SCALEING_FACTOR_K             (float)1.64676f

/**
 * @brief Adjusted scaling factor KA for the CORDIC algorithm.
 *
 * Represents the adjusted scaling factor used in the CORDIC algorithm.
 */
#define SCALEING_FACTOR_KA            (float)0.828159f

/**
 * @brief Reverse scaling factor K for the CORDIC algorithm.
 *
 * Represents the reverse scaling factor used in the CORDIC algorithm.
 */
#define REVERSE_SCALEING_FACTOR_K     (float)(1.f/SCALEING_FACTOR_K)

/**
 * @brief Reverse adjusted scaling factor KA for the CORDIC algorithm.
 *
 * Represents the reverse adjusted scaling factor used in the CORDIC algorithm.
 */
#define REVERSE_SCALEING_FACTOR_KA    (float)(1.f/SCALEING_FACTOR_KA)


/*******************************************************************************
 * Variables
 ******************************************************************************/


/**
 * @brief Array of pointers to CORDIC module bases.
 *
 * This array contains pointers to the base addresses of all CORDIC modules.
 */
static CORDIC_Type  *const s_apCordicBase[CORDIC_INSTANCE_COUNT] = CORDIC_BASE_PTRS ;

/**
 * @brief Floating-point conversion to 24 bit fixed-point
 *
 * @param nFloat Input value
 */
static uint32_t Float2Fix_convert(const float *nFloat);

/**
 * @brief Converts a floating-point number to a fixed-point representation.
 *
 * This function converts a floating-point number into a fixed-point
 * representation suitable for use in the CORDIC algorithm.
 *
 * @param nFloat Pointer to the floating-point number to convert.
 * @return The converted fixed-point representation.
 */
static uint32_t Float2Fix_convert(const float *nFloat)
{
    uint32_t nFix ;
    uint32_t temp ;
    int32_t exp ;
    uint32_t tail ;
    /* Step1: get the sign bit */
    temp = *((uint32_t *)(uint32_t)nFloat);
    nFix = temp & CORDIC_SIGN_BIT;
    /* Step2: get the integer bits */
    exp = (int32_t)(((temp & CORDIC_EXP_BIT) >> 23) - 127U);
    tail = (temp & CORDIC_TAIL_BIT) | 0x00800000U;
    nFix = nFix | ((tail >> (23 - exp)) << 27);
    /* Step3: get the fractional bits */
    if ((4 + exp) < 0)
    {
        nFix = nFix | (tail & (~(0xFFFFFFFFU << (23 - exp)))) >> (-4 - exp);
    }
    else
    {
        nFix = nFix | (tail & (~(0xFFFFFFFFU << (23 - exp)))) << (4 + exp);
    }
    if (nFix & CORDIC_SIGN_BIT)
    {
        nFix = ((nFix ^ 0x7FFFFFFFU) + 1) | CORDIC_SIGN_BIT;
    }
    return nFix;
}

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
CORDIC_SinCos_Type Cordic_Circular_Sin_Cos(CORDIC_InstanceType eInstance, const float radian)
{
    /* angles are expressed in radian, multiplied by a constant number. 𝜃/180 * 𝜋c (where 𝜋c is 13.42177) */
    #if CORDIC_DEV_ERROR_REPORT == STD_ON
    if (eInstance >= CORDIC_INSTANCE_COUNT)
    {
        CORDIC_ReportDevError(CORDIC_CIRCULAR_SIN_COS_ID, CORDIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        CORDIC_SinCos_Type tRetVal;
        CORDIC_Type *const pCORDIC = s_apCordicBase[eInstance];

        float tmp = REVERSE_SCALEING_FACTOR_K;

        uint32_t fix_radian = Float2Fix_convert(&radian);
        uint32_t x_input = Float2Fix_convert(&tmp);
        Cordic_HWA_Set_XInput(pCORDIC, x_input);
        Cordic_HWA_Set_YInput(pCORDIC, 0);
        Cordic_HWA_Set_ZInput(pCORDIC, fix_radian);
        /* Disable interrupt + Iteration Number16 + Trigonometric system + Rotate mode */
        Cordic_HWA_SetCtrl(pCORDIC, CORDIC_CTR_VAL(false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Rotate));
        while (!Cordic_HWA_Get_Stat(pCORDIC)) {}
        tmp = (float)(Cordic_HWA_Get_YOutput(pCORDIC)) / 134217728.f;
        tRetVal.sinx = tmp;
        tmp = (float)(Cordic_HWA_Get_XOutput(pCORDIC)) / 134217728.f;
        tRetVal.cosx = tmp;
        return tRetVal;
        #if CORDIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
}

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
CORDIC_Radical_Type Cordic_Circular_Radical_Add(CORDIC_InstanceType eInstance, const float x, const float y)
{
    CORDIC_Radical_Type tRetVal;
    #if CORDIC_DEV_ERROR_REPORT == STD_ON

    if (eInstance >= CORDIC_INSTANCE_COUNT)
    {
        CORDIC_ReportDevError(CORDIC_CIRCULAR_RADICAL_ADD_ID, CORDIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        CORDIC_Type *const pCORDIC = s_apCordicBase[eInstance];

        float x_input = REVERSE_SCALEING_FACTOR_K * x;
        float y_input = REVERSE_SCALEING_FACTOR_K * y;
        Cordic_HWA_Set_XInput(pCORDIC, Float2Fix_convert(&x_input));
        Cordic_HWA_Set_YInput(pCORDIC, Float2Fix_convert(&y_input));
        Cordic_HWA_Set_ZInput(pCORDIC, 0);
        /* Disable interrupt + Iteration Number16 + Trigonometric system + Vector mode */
        Cordic_HWA_SetCtrl(pCORDIC, CORDIC_CTR_VAL(false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Vector));
        while (!Cordic_HWA_Get_Stat(pCORDIC)) {}
        tRetVal = (CORDIC_Radical_Type)(Cordic_HWA_Get_XOutput(pCORDIC)) / 134217728.f;
        #if CORDIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return tRetVal;
}

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
CORDIC_Arctan_Type Cordic_Circular_Arctan_F(CORDIC_InstanceType eInstance, const float y)
{
    CORDIC_Arctan_Type tRetVal;
    #if CORDIC_DEV_ERROR_REPORT == STD_ON

    if (eInstance >= CORDIC_INSTANCE_COUNT)
    {
        CORDIC_ReportDevError(CORDIC_CIRCULAR_ARCTAN_F_ID, CORDIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        CORDIC_Type *const pCORDIC = s_apCordicBase[eInstance];

        if ((y > 96.6) || (y < -96.6))
        {
            tRetVal = (CORDIC_Arctan_Type)89.4069;
        }
        else
        {
            float x_input = 0.1f;
            float y_input = y * 0.1f;
            Cordic_HWA_Set_XInput(pCORDIC, Float2Fix_convert(&x_input));
            Cordic_HWA_Set_YInput(pCORDIC, Float2Fix_convert(&y_input));
            Cordic_HWA_Set_ZInput(pCORDIC, 0);
            /* Disable interrupt + Iteration Number16 + Trigonometric system + Vector mode */
            Cordic_HWA_SetCtrl(pCORDIC, CORDIC_CTR_VAL(false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Vector));
            while (!Cordic_HWA_Get_Stat(pCORDIC)) {}
            /* 10007997.084103 = 134217728.f * 13.42177 / 180 */;
            tRetVal = (CORDIC_Arctan_Type)(Cordic_HWA_Get_ZOutput(pCORDIC)) / 10007997.084103f;
        }
        #if CORDIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return tRetVal;
}


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
CORDIC_Arctan_Type Cordic_Circular_Arctan(CORDIC_InstanceType eInstance, const int32_t x, const int32_t y)
{
    CORDIC_Arctan_Type tRetVal;

    #if CORDIC_DEV_ERROR_REPORT == STD_ON

    if (eInstance >= CORDIC_INSTANCE_COUNT)
    {
        CORDIC_ReportDevError(CORDIC_CIRCULAR_ARCTAN_ID, CORDIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        CORDIC_Type *const pCORDIC = s_apCordicBase[eInstance];

        Cordic_HWA_Set_XInput(pCORDIC, (uint32_t)x);
        Cordic_HWA_Set_YInput(pCORDIC, (uint32_t)y);
        Cordic_HWA_Set_ZInput(pCORDIC, 0);
        /* Disable interrupt + Iteration Number16 + Trigonometric system + Vector mode */
        Cordic_HWA_SetCtrl(pCORDIC, CORDIC_CTR_VAL(false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Trigonometric, (uint32_t)CORDIC_Vector));
        while (!Cordic_HWA_Get_Stat(pCORDIC)) {}
        /* 10007997.084103 = 134217728.f * 13.42177 / 180 */;
        tRetVal = (CORDIC_Arctan_Type)(Cordic_HWA_Get_ZOutput(pCORDIC)) / 10007997.084103f;
        #if CORDIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return tRetVal;
}

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
CORDIC_SinhCosh_Type Cordic_Circular_Sinh_Cosh(CORDIC_InstanceType eInstance, const float z)
{
    CORDIC_SinhCosh_Type tRetVal;
    #if CORDIC_DEV_ERROR_REPORT == STD_ON

    if (eInstance >= CORDIC_INSTANCE_COUNT)
    {
        CORDIC_ReportDevError(CORDIC_CIRCULAR_SINH_COSH_ID, CORDIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        CORDIC_Type *const pCORDIC = s_apCordicBase[eInstance];
        float tmp = REVERSE_SCALEING_FACTOR_KA;
        uint32_t z_input = Float2Fix_convert(&z);
        uint32_t x_input = Float2Fix_convert(&tmp);
        Cordic_HWA_Set_XInput(pCORDIC, x_input);
        Cordic_HWA_Set_YInput(pCORDIC, 0);
        Cordic_HWA_Set_ZInput(pCORDIC, z_input);
        /* Disable interrupt + Iteration Number16 + Hyperbolic system + Rotate mode */
        Cordic_HWA_SetCtrl(pCORDIC, CORDIC_CTR_VAL(false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Rotate));
        while (!Cordic_HWA_Get_Stat(pCORDIC)) {}
        tmp = (float)(Cordic_HWA_Get_YOutput(pCORDIC)) / 134217728.f;
        tRetVal.sinxh = tmp;
        tmp = (float)(Cordic_HWA_Get_XOutput(pCORDIC)) / 134217728.f;
        tRetVal.cosxh = tmp;
        #if CORDIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return tRetVal;
}

/**
 * @brief Computes the circular radical subtraction using the CORDIC algorithm.
 *
 * This function computes the circular radical subtraction of two input values `x` and `y`.
 * It uses the CORDIC hardware abstraction layer (HAL) functions to perform the calculations.
 *
 * @param eInstance The CORDIC instance identifier.
 * @param x The first input value.
 * @param y The second input value.
 *
 * @return CORDIC_Radical_Type The result of the circular radical subtraction.
 */
CORDIC_Radical_Type Cordic_Circular_Radical_Sub(CORDIC_InstanceType eInstance, const float x, const float y)
{
    CORDIC_Radical_Type tRetVal;
    #if CORDIC_DEV_ERROR_REPORT == STD_ON

    if (eInstance >= CORDIC_INSTANCE_COUNT)
    {
        CORDIC_ReportDevError(CORDIC_CIRCULAR_RADICAL_SUB_ID, CORDIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        CORDIC_Type *const pCORDIC = s_apCordicBase[eInstance];

        float x_input = REVERSE_SCALEING_FACTOR_KA * x;
        float y_input = REVERSE_SCALEING_FACTOR_KA * y;

        Cordic_HWA_Set_XInput(pCORDIC, Float2Fix_convert(&x_input));
        Cordic_HWA_Set_YInput(pCORDIC, Float2Fix_convert(&y_input));
        Cordic_HWA_Set_ZInput(pCORDIC, 0);
        /* Disable interrupt + Iteration Number16 + Hyperbolic system + Vector mode */
        Cordic_HWA_SetCtrl(pCORDIC, CORDIC_CTR_VAL(false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Vector));
        while (!Cordic_HWA_Get_Stat(pCORDIC)) {}
        tRetVal =(CORDIC_Radical_Type)(Cordic_HWA_Get_XOutput(pCORDIC)) / 134217728.f;
        #if CORDIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return tRetVal;
}

/**
 * @brief Computes the hyperbolic arctangent using the CORDIC algorithm.
 *
 * This function calculates the hyperbolic arctangent of a given input value `y`.
 * It uses the CORDIC hardware abstraction layer (HAL) functions to perform the calculations.
 *
 * @param eInstance The CORDIC instance identifier.
 * @param y The input value for which to compute the hyperbolic arctangent.
 *
 * @return CORDIC_Arctanh_Type The computed hyperbolic arctangent value.
 */
CORDIC_Arctanh_Type Cordic_Circular_Arctanh(CORDIC_InstanceType eInstance, const float y)
{
    CORDIC_Arctanh_Type tRetVal;
    #if CORDIC_DEV_ERROR_REPORT == STD_ON

    if (eInstance >= CORDIC_INSTANCE_COUNT)
    {
        CORDIC_ReportDevError(CORDIC_CIRCULAR_ARCTANH_ID, CORDIC_E_PARAM_INSTANCE);
    }
    else
    {
    #endif
        CORDIC_Type *const pCORDIC = s_apCordicBase[eInstance];

        float x_input = 1.f;
        float y_input = y;

        Cordic_HWA_Set_XInput(pCORDIC, Float2Fix_convert(&x_input));
        Cordic_HWA_Set_YInput(pCORDIC, Float2Fix_convert(&y_input));
        Cordic_HWA_Set_ZInput(pCORDIC, 0);
        /* Disable interrupt + Iteration Number16 + Hyperbolic system + Vector mode */
        Cordic_HWA_SetCtrl(pCORDIC, CORDIC_CTR_VAL(false, (uint32_t)CORDIC_Iteration_16, (uint32_t)CORDIC_Hyperbolic, (uint32_t)CORDIC_Vector));
        while (!Cordic_HWA_Get_Stat(pCORDIC)) {}
        /* 10007997.084103 = 134217728.f * 13.42177 / 180 */;
        tRetVal = (CORDIC_Arctanh_Type)(Cordic_HWA_Get_ZOutput(pCORDIC)) / 134217728.f;
        #if CORDIC_DEV_ERROR_REPORT == STD_ON
    }
        #endif
    return tRetVal;
}
/**
 * @}
 */

#endif

