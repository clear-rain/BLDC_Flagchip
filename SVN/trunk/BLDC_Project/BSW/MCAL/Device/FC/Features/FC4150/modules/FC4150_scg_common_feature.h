#ifndef _DEVICE_FEATURES_FC4150_SCG_COMMON_H_
#define _DEVICE_FEATURES_FC4150_SCG_COMMON_H_
/*********************** SCG Features ****************************/
/** Number of instances of the SCG module. */
#define SCG_INSTANCE_COUNT                       (1u)
/* SCG - Peripheral instance base addresses */
/** Peripheral SCG base address */
#define SCG_BASE                                 (0x40064000u)
/** Peripheral SCG base pointer */
#define SCG                                      ((SCG_Type *)SCG_BASE)
/** Array initializer of SCG peripheral base addresses */
#define SCG_BASE_ADDRS                           {SCG_BASE}
/** Array initializer of SCG peripheral base pointers */
#define SCG_BASE_PTRS                            {SCG}
// need fill by yourself
///** Number of interrupt vector arrays for the SCG module. */
//#define SCG_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the SCG module. */
//#define SCG_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the SCG peripheral type */
//#define SCG_IRQS                                 {SCG_IRQn}


#define SIRC_CLOCK       12000000U
#define SIRC32K_CLOCK    32000U
#define FIRC_CLOCK       96000000U
#define FOSC_STABILIZATION_TIMEOUT       1200000U
#define FIRC_STABILIZATION_TIMEOUT       100000U
#define SIRC_STABILIZATION_TIMEOUT       100000U
#define SOSC_STABILIZATION_TIMEOUT       75000000U
#define PLL0_STABILIZATION_TIMEOUT       320500U
#define SCG_CLKSRC_STABILIZATION_TIMEOUT 100000U
#define CLOCK_OFF_STABILIZATION_TIMEOUT  100000U 
#define CLOCK_DIV_STABILIZATION_TIMEOUT  100000U
#define SYS_CORE_CLK_MAX       150000000U
#define SYS_BUS_CLK_MAX        75000000U
#define SYS_SLOW_CLK_MAX       37500000U

#define FOSC_DIVH_MAX_CLOCK 48000000U
#define FOSC_DIVM_MAX_CLOCK 48000000U
#define FOSC_DIVL_MAX_CLOCK 24000000U
#define FIRC_DIVH_MAX_CLOCK 96000000U
#define FIRC_DIVM_MAX_CLOCK 48000000U
#define FIRC_DIVL_MAX_CLOCK 24000000U
#define PLL0_DIVH_MAX_CLOCK 150000000U
#define PLL0_DIVM_MAX_CLOCK 75000000U
#define PLL0_DIVL_MAX_CLOCK 37500000U

#define UNKNOWN_CLOCK    0xFFFFFFFFU



#endif
