/**
 * @file arm_cortex_asm.h
 * @author Flagchip
 * @brief include all arm cortex m4 files
 * @version 0.2.1
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef _FC4150_CORE_CM4_H_
#define _FC4150_CORE_CM4_H_



#ifdef __cplusplus
extern "C" {
#endif

/** @brief  BKPT_ASM
 *
 *   Macro to be used to trigger an debug interrupt
 */
#define BKPT_ASM __asm("BKPT #0\n\t")


/** @brief  Enable FPU
 *
 *   ENABLE_FPU indicates whether SystemInit will enable the Floating point unit (FPU)
 */
#if defined (__GNUC__) || defined (__ARMCC_VERSION)
#if defined (__VFP_FP__) && !defined (__SOFTFP__)
#define ENABLE_FPU
#endif

#elif defined (__ICCARM__)
#if defined __ARMVFP__
#define ENABLE_FPU
#endif

#elif defined (__ghs__) || defined (__DCC__)
#if defined (__VFP__)
#define ENABLE_FPU
#endif
#endif /* if defined (__GNUC__) */

/** @brief  Enable interrupts
 */
#if defined (__GNUC__)
#define ENABLE_INTERRUPTS() __asm volatile ("cpsie i" : : : "memory");
#else
#define ENABLE_INTERRUPTS() __asm("cpsie i")
#endif


/** @brief  Disable interrupts
 */
#if defined (__GNUC__)
#define DISABLE_INTERRUPTS() __asm volatile ("cpsid i" : : : "memory");
#else
#define DISABLE_INTERRUPTS() __asm("cpsid i")
#endif


/** @brief  Enter low-power standby state
 *    WFI (Wait For Interrupt) makes the processor suspend execution (Clock is stopped) until an IRQ interrupts.
 */
#if defined (__GNUC__)
#define STANDBY() __asm volatile ("wfi")
#else
#define STANDBY() __asm("wfi")
#endif

/** @brief  No-op
 */
#define NOP() __asm volatile ("nop")

/** @brief  Reverse byte order in a word.
 */
#if defined (__GNUC__) || defined (__ICCARM__) || defined (__ghs__) || defined (__ARMCC_VERSION)
#define REV_BYTES_32(a, b) __asm volatile ("rev %0, %1" : "=r" (b) : "r" (a))
#else
#define REV_BYTES_32(a, b) (b = ((a & 0xFF000000U) >> 24U) | ((a & 0xFF0000U) >> 8U) \
                                | ((a & 0xFF00U) << 8U) | ((a & 0xFFU) << 24U))
#endif

/** @brief  Reverse byte order in each halfword independently.
 */
#if defined (__GNUC__) || defined (__ICCARM__) || defined (__ghs__) || defined (__ARMCC_VERSION)
#define REV_BYTES_16(a, b) __asm volatile ("rev16 %0, %1" : "=r" (b) : "r" (a))
#else
#define REV_BYTES_16(a, b) (b = ((a & 0xFF000000U) >> 8U) | ((a & 0xFF0000U) << 8U) \
                                | ((a & 0xFF00U) >> 8U) | ((a & 0xFFU) << 8U))
#endif

/** @brief  Places a function in RAM.
 */
#if defined ( __GNUC__ ) || defined (__ARMCC_VERSION)
    #define START_FUNCTION_DECLARATION_RAMSECTION
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));
#elif defined ( __ghs__ )
    #define START_FUNCTION_DECLARATION_RAMSECTION      _Pragma("ghs callmode=far")
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));\
                                                       _Pragma("ghs callmode=default")
#elif defined ( __ICCARM__ )
    #define START_FUNCTION_DECLARATION_RAMSECTION      __ramfunc
    #define END_FUNCTION_DECLARATION_RAMSECTION        ;
#elif defined ( __DCC__ )
    #define START_FUNCTION_DECLARATION_RAMSECTION      _Pragma("section CODE \".code_ram\"") \
                                                       _Pragma("use_section CODE")
    #define END_FUNCTION_DECLARATION_RAMSECTION        ; \
                                                       _Pragma("section CODE \".text\"")
#else
    /* Keep compatibility with software analysis tools */
    #define START_FUNCTION_DECLARATION_RAMSECTION
    #define END_FUNCTION_DECLARATION_RAMSECTION        ;
#endif

    /* For GCC, IAR, GHS, Diab and ARMC there is no need to specify the section when
    defining a function, it is enough to specify it at the declaration. This
    also enables compatibility with software analysis tools. */
    #define START_FUNCTION_DEFINITION_RAMSECTION
    #define END_FUNCTION_DEFINITION_RAMSECTION

#if defined (__ICCARM__)
    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL     _Pragma("diag_suppress=Ta022")
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL      _Pragma("diag_default=Ta022")
#else
    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
#endif

/** @brief  Get Core ID
 *
 *   GET_CORE_ID returns the processor identification number for cm4
 */
#define GET_CORE_ID()    0U

/** @brief  Data alignment.
 */
#if defined ( __GNUC__ ) || defined ( __ghs__ ) || defined ( __DCC__ ) || defined (__ARMCC_VERSION)
    #define ALIGNED(x)      __attribute__((aligned(x)))
#elif defined ( __ICCARM__ )
    #define stringify(s) tostring(s)
    #define tostring(s) #s
    #define ALIGNED(x)      _Pragma(stringify(data_alignment=(x)))
#else
    /* Keep compatibility with software analysis tools */
    #define ALIGNED(x)
#endif

/** @brief  Endianness.
 */
#define CORE_LITTLE_ENDIAN


/** @brief  DSB
 *
 *   The Data Synchronization Barrier (DSB) instruction ensures that outstanding memory transactions complete before subsequent instructions execute.
 */
#if defined (__GNUC__)
#define DSB() __asm volatile ("dsb" : : : "memory");
#else
#define DSB() __asm("dsb")
#endif

/** @brief  ISB
 *
 *   The Instruction Synchronization Barrier (ISB) ensures that the effect of all completed memory transactions is recognizable by subsequent instructions.
 */
#if defined (__GNUC__)
#define ISB() __asm volatile ("isb" : : : "memory");
#else
#define ISB() __asm("isb")
#endif

/** @brief  DMB
 *
 *   The Data Memory Barrier (DMB) instruction ensures that outstanding memory transactions complete before subsequent memory transactions
 */
#if defined (__GNUC__)
#define DMB() __asm volatile ("dmb" : : : "memory");
#else
#define DMB() __asm("dmb")
#endif


#ifdef __cplusplus
}
#endif

#endif
