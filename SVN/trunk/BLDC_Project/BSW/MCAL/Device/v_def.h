/**
 * @file v_def.h
 * @author Flagchip
 * @brief variables type define
 * @version 0.2.1
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef DEVICE_V_DEF_H_
#define DEVICE_V_DEF_H_

#ifndef TRUE
#define TRUE   1U
#endif

#ifndef FALSE
#define FALSE  0U
#endif

#ifndef NULL_PTR
#define NULL_PTR  ((void*)0)
#endif

#ifndef int8
typedef signed char int8;
#endif

#ifndef int16
typedef signed short int16;
#endif

#ifndef int32
typedef signed int int32;
#endif

#ifndef uint8
typedef unsigned char uint8;
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

#ifndef uint16
typedef unsigned short uint16;
#endif

#ifndef uint32
typedef unsigned int uint32;
#endif

#ifndef uint64
typedef unsigned long long  uint64;
#endif

#ifndef boolean
typedef unsigned char boolean;
#endif

#ifndef Boolean
typedef unsigned char Boolean;
#endif

#ifndef float32
typedef float float32;
#endif

#ifndef float64
typedef double float64;
#endif

#ifndef sint8
typedef signed char sint8;
#endif

#ifndef sint16
typedef signed short sint16;
#endif

#ifndef sint32
typedef signed long sint32;
#endif

#ifndef sint64
typedef signed long long sint64;
#endif

typedef void *void_functype(void);

typedef enum{
	E_OK,
	E_NOK
}Std_ReturnType;
typedef void *void_functype(void);

#ifdef __GUNC__

#endif

#endif /* DEVICE_V_DEF_H_ */
