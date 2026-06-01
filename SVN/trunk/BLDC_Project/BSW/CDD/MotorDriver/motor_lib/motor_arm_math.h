/**
 * @file motor_arm_math.h
 * @author Flagchip127
 * @brief FC4xxx motor_arm_math
 * @version 1.0.0
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   1.0.0       2024-05-20    Flagchip127   N/A          First version for FC4150
 ******************************************************************************** */

#ifndef _MOTOR_LIB_MOTOR_ARM_MATH_H_
#define _MOTOR_LIB_MOTOR_ARM_MATH_H_

#include "compiler.h"
#include "stdint.h"

#define FAST_MATH_TABLE_SIZE 512
extern const float sin_table_f32_[FAST_MATH_TABLE_SIZE + 1];

#ifndef M_PI
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#endif

LOCAL_INLINE
float arm_cos_f32(float x)
{
    float cosVal, fract, in;
    uint16_t index;
    float a, b;
    int32_t n;
    float findex;
    in = x * 0.159154943092f + 0.25f;
    n = (int32_t)in;
    if (in < 0.0f)
    {
        n--;
    }
    in = in - (float)n;
    findex = (float)FAST_MATH_TABLE_SIZE * in;
    index = ((uint16_t)findex) & 0x1ff;
    fract = findex - (float)index;
    a = sin_table_f32_[index];
    b = sin_table_f32_[index + 1];
    cosVal = (1.0f - fract) * a + fract * b;
    return (cosVal);
}

LOCAL_INLINE
float arm_sin_f32(float x)
{
    float sinVal, fract, in;
    uint16_t index;
    float a, b;
    int32_t n;
    float findex;
    in = x * 0.159154943092f;
    n = (int32_t)in;
    if (x < 0.0f)
    {
        n--;
    }
    in = in - (float)n;
    findex = (float)FAST_MATH_TABLE_SIZE * in;
    index = ((uint16_t)findex) & 0x1ff;
    fract = findex - (float)index;
    a = sin_table_f32_[index];
    b = sin_table_f32_[index + 1];
    sinVal = (1.0f - fract) * a + fract * b;
    return (sinVal);
}

LOCAL_INLINE
void Mat_SinCosLookup(float f, float *sin, float *cos)
{
    *cos = arm_cos_f32(f);
    *sin = arm_sin_f32(f);
}

LOCAL_INLINE
void Mat_FastArctan(float y, float x, float *angle)
{
    float theta, abs_y;

    if (y > 0)
    {
        abs_y = y;
    }
    else if (y < 0)
    {
        abs_y = -y;
    }
    else
    {
        abs_y = 1e-20f;
    } // kludge to prevent 0/0 condition

    if (x >= 0)
    {
        float r = (x - abs_y) / (x + abs_y);
        float rsq = r * r;
        theta = ((0.1963f * rsq) - 0.9817f) * r + ((float)M_PI / 4.0f);
    }
    else
    {
        float r = (x + abs_y) / (abs_y - x);
        float rsq = r * r;
        theta = ((0.1963f * rsq) - 0.9817f) * r + (3.0f * (float)M_PI / 4.0f);
    }

    if (y < 0)
    {
        *angle = -theta;
    }
    else
    {
        *angle = theta;
    }
}

#endif /* _MOTOR_LIB_MOTOR_ARM_MATH_H_ */
