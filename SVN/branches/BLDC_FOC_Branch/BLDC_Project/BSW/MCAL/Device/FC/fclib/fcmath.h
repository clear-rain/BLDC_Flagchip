/**
 * @file module_fclib.h
 * @author Flagchip
 * @brief include fclib file
 * @version 0.2.1
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef _DEVICE_FCLIB_FCMATH_H_
#define _DEVICE_FCLIB_FCMATH_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "typedef.h"

uint32_t Fc_Power(uint32_t num, uint32_t u8Power);

uint32_t Fc_Max(uint32_t u32Val1, uint32_t u32Val2);

uint32_t Fc_Min(uint32_t u32Val1, uint32_t u32Val2);


#ifdef __cplusplus
}
#endif


#endif
