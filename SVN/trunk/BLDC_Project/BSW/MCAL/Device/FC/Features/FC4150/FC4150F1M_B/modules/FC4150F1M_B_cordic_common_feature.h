#ifndef _DEVICE_FEATURES_FC4150F1M__B_CORDIC_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_CORDIC_COMMON_H_

/************ CORDIC Features **************/
/** Number of instances of the CORDIC module. */
#define CORDIC_INSTANCE_COUNT                    (1u)

/* CORDIC - Peripheral instance base addresses */
/** Peripheral CORDIC base address */
#define CORDIC_BASE                              (0x40045000u)
/** Peripheral CORDIC base pointer */
#define CORDIC                                   ((CORDIC_Type *)CORDIC_BASE)
/** Array initializer of CORDIC peripheral base addresses */
#define CORDIC_BASE_ADDRS                        {CORDIC_BASE}
/** Array initializer of CORDIC peripheral base pointers */
#define CORDIC_BASE_PTRS                         {CORDIC}
// need fill by yourself
///** Number of interrupt vector arrays for the CORDIC module. */
//#define CORDIC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the CORDIC module. */
//#define CORDIC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the CORDIC peripheral type */
//#define CORDIC_IRQS                              {CORDIC_IRQn}


#endif
