#ifndef _DEVICE_FEATURES_FC4150_FCUART_COMMON_H_
#define _DEVICE_FEATURES_FC4150_FCUART_COMMON_H_
/*********************** FCUART Features ****************************/
/** Number of instances of the FCUART module. */
#define FCUART_INSTANCE_COUNT                    (6u)
/* FCUART - Peripheral instance base addresses */
/** Peripheral FCUART0 base address */
#define FCUART0_BASE                             (0x4006A000u)
/** Peripheral FCUART0 base pointer */
#define FCUART0                                  ((FCUART_Type *)FCUART0_BASE)
/** Peripheral FCUART1 base address */
#define FCUART1_BASE                             (0x4006B000u)
/** Peripheral FCUART1 base pointer */
#define FCUART1                                  ((FCUART_Type *)FCUART1_BASE)
/** Peripheral FCUART2 base address */
#define FCUART2_BASE                             (0x4006C000u)
/** Peripheral FCUART2 base pointer */
#define FCUART2                                  ((FCUART_Type *)FCUART2_BASE)
/** Peripheral FCUART3 base address */
#define FCUART3_BASE                             (0x4005B000u)
/** Peripheral FCUART3 base pointer */
#define FCUART3                                  ((FCUART_Type *)FCUART3_BASE)
/** Peripheral FCUART4 base address */
#define FCUART4_BASE                             (0x4005C000u)
/** Peripheral FCUART4 base pointer */
#define FCUART4                                  ((FCUART_Type *)FCUART4_BASE)
/** Peripheral FCUART5 base address */
#define FCUART5_BASE                             (0x4005D000u)
/** Peripheral FCUART5 base pointer */
#define FCUART5                                  ((FCUART_Type *)FCUART5_BASE)
/** Array initializer of FCUART peripheral base addresses */
#define FCUART_BASE_ADDRS                        {FCUART0_BASE, FCUART1_BASE, FCUART2_BASE, FCUART3_BASE, FCUART4_BASE, FCUART5_BASE}
/** Array initializer of FCUART peripheral base pointers */
#define FCUART_BASE_PTRS                         {FCUART0, FCUART1, FCUART2, FCUART3, FCUART4, FCUART5}
/** Number of interrupt vector arrays for the FCUART module. */
#define FCUART_IRQS_ARR_COUNT                       (1u)
/** Number of interrupt channels for the FCUART module. */
#define FCUART_IRQS_CH_COUNT                        (1u)
/** Interrupt vectors for the FCUART peripheral type */
#define FCUART_IRQS                              {FCUART0_IRQn, FCUART1_IRQn, FCUART2_IRQn, FCUART3_IRQn, FCUART4_IRQn, FCUART5_IRQn}
#endif
