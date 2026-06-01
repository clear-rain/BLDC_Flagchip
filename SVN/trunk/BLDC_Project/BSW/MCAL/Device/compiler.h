/**
 * @file compiler.h
 * @author Flagchip
 * @brief compiler define
 * @version 2.0.0
 * @date 2023-09-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef DEVICE_COMPILER_H_
#define DEVICE_COMPILER_H_


#ifndef __IO
#ifdef __cplusplus
  #define   __I     volatile             /**< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /**< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /**< Defines 'write only' permissions                */
#define     __IO    volatile             /**< Defines 'read / write' permissions              */
#endif


#if defined (__GNUC__)
#ifndef INLINE
#define INLINE           __attribute__((always_inline)) inline
#endif
#ifndef LOCAL_INLINE
#define LOCAL_INLINE     __attribute__((always_inline)) static inline
#endif
#define ALIGN(n)         __attribute__((aligned(n)))
#define PCAKED           __attribute__((packed))

#else
#ifndef INLINE
#define INLINE           inline
#endif
#ifndef LOCAL_INLINE
#define LOCAL_INLINE     static inline
#endif

#if (defined(__ICCARM__))
#define STRINGIZE(x)     #x
#define ALIGN(n)         _Pragma(STRINGIZE(data_alignment=(n)))
#define PACKED           __packed
#endif

#if (defined(__CC_ARM))
#define ALIGN(n)         __align(n)
#define PACKED           __packed
#endif

#endif




#if (defined(__ICCARM__))

#define PROCESS_UNUSED_VAR(var)        (var) = (var);

#elif defined __GNUC__ || defined __ghs__
#define PROCESS_UNUSED_VAR(var)        (void)(var);

#else

#define PROCESS_UNUSED_VAR(var)

#endif



#endif /* DEVICE_COMPILER_H_ */
