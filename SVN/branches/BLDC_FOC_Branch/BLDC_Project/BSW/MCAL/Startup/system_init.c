/**
 * @file system_init.c
 * @author Flagchip
 * @brief interrupt configuration
 * @version 2.00.0
 * @date 2024-07-14
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */
 #include "device_header.h"

#define SCB_CPACR     0xE000ED88
/* #define DATA_IN_DTCM */

#if defined(__GNUC__) || defined(__ghs__)
    extern uint32 __data_start__[];
    extern uint32 __data_end__[];
    extern uint32 __data_init_start__[];
    extern uint32 __bss_start__[];
    extern uint32 __bss_end__[];
#elif defined(__ICCARM__)
    #pragma section = ".data"
    #pragma section = ".data_init"
    #pragma section = ".bss"

    uint32 *const __data_start__             = (uint32 *)(__section_begin(".data"));
    uint32 *const __data_end__               = (uint32 *)(__section_end(".data"));
    uint32 *const __data_init_start__        = (uint32 *)(__section_begin(".data_init"));
    uint32 *const __bss_start__                = (uint32 *)(__section_begin(".bss"));
    uint32 *const __bss_end__                   = (uint32 *)(__section_end(".bss"));
#endif

extern void data_init(void);
extern void system_init(void);

static void data_clear(uint32 *pHead, uint32 *pTail)
{
    while (pHead < pTail)
    {
        *pHead = 0U;
        pHead++;
    }
}

static void data_copy(uint32 *pHead, uint32 *pTail, uint32 *pSrc)
{
    while (pHead < pTail)
    {
        *pHead = *pSrc;
        pHead++;
        pSrc++;
    }
}

void data_init(void)
{

    /* bss */
    data_clear(__bss_start__, __bss_end__);
    /* data */
    data_copy(__data_start__, __data_end__, __data_init_start__);

}

void system_init(void)
{
    
    /* disable wdog 0 */
    *(volatile uint32 *)0x40052004 = 0x08181982;
    while (0U == (0x800u & *(volatile uint32 *)0x40052000));
    *(volatile uint32 *)0x40052000 = 0x2920;
    *(volatile uint32 *)0x40052008 = 0xF000;
    while (0U == (0x400u & *(volatile uint32 *)0x40052000));
   

    /* disable wdog 1 */
    *(volatile uint32 *)0x40053004 = 0x08181982;

    while (0U == (0x800u & *(volatile uint32 *)0x40053000));
    *(volatile uint32 *)0x40053000 = 0x2920;
    *(volatile uint32 *)0x40053008 = 0xF000;
    while (0U == (0x400u & *(volatile uint32 *)0x40053000));

    /* clear RTC interrupt */
    *(volatile uint32*)(0x400650f4) = 0x40000000;
    RTC->SR = 0xFFFFFFFFU;
    *(volatile uint32*)(0x400650f4) = 0x00000000;

    /* FPU enable: 设置 CP10/CP11 为 Full Access，并执行 DSB/ISB，
     * 行为与 Tmotor 工程中的 fpu_enable 保持一致，避免依赖 __FPU_USED 编译宏 */
#if defined(__FPU_PRESENT) && (__FPU_PRESENT == 1)
    SCB->CPACR |= (0xFu << 20);
    __DSB();
    __ISB();
#endif

    asm volatile("mov pc, lr");
}
