#ifndef _DEVICE_FEATURES_FC4150_DMAMUX_COMMON_H_
#define _DEVICE_FEATURES_FC4150_DMAMUX_COMMON_H_
/*********************** DMAMUX Features ****************************/
/** Number of instances of the DMAMUX module. */
#define DMAMUX_INSTANCE_COUNT                    (1u)
/* DMAMUX - Peripheral instance base addresses */
/** Peripheral DMAMUX base address */
#define DMAMUX_BASE                              (0x40021000u)
/** Peripheral DMAMUX base pointer */
#define DMAMUX                                   ((DMAMUX_Type *)DMAMUX_BASE)
/** Array initializer of DMAMUX peripheral base addresses */
#define DMAMUX_BASE_ADDRS                        {DMAMUX_BASE}
/** Array initializer of DMAMUX peripheral base pointers */
#define DMAMUX_BASE_PTRS                         {DMAMUX}
// need fill by yourself
///** Number of interrupt vector arrays for the DMAMUX module. */
//#define DMAMUX_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the DMAMUX module. */
//#define DMAMUX_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the DMAMUX peripheral type */
//#define DMAMUX_IRQS                              {DMAMUX_IRQn}
#endif
