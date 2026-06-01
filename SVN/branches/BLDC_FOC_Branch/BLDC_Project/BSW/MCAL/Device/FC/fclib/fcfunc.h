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
#ifndef _DEVICE_FCLIB_FCFUNC_H_
#define _DEVICE_FCLIB_FCFUNC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "typedef.h"
#include "v_def.h"

void* FCFUNC_FcOwnMemcpy(uint8_t *pDest, const uint8_t *pSource, uint32_t u32Count,  void_functype wdogTriggerFunc );

void* FC_OwnMemcpy(void *pDest, const void *pSource, uint32_t u32Count);

void* FC_OwnMemcpyWithWdg(void *pDest, const void *pSource, uint32_t u32Count,  void_functype wdogTriggerFunc, uint32_t u32CallBackCnt );

#ifdef __cplusplus
}
#endif


#endif
