#ifndef _DEVICE_FEATURES_FC4150F2M_OSPI_COMMON_H_
#define _DEVICE_FEATURES_FC4150F2M_OSPI_COMMON_H_
/*********************** OSPI Features ****************************/
#define OSPI_MODULE_SUPPORT                      (1u)
#if OSPI_MODULE_SUPPORT
/** Number of instances of the OSPI module. */
#define OSPI_INSTANCE_COUNT                      (1u)
/* OSPI - Peripheral instance base addresses */
/** Peripheral OSPI base address */
#define OSPI_BASE                                (0x40076000u)
/** Peripheral OSPI base pointer */
#define OSPI                                     ((OSPI_Type *)OSPI_BASE)
/** Array initializer of OSPI peripheral base addresses */
#define OSPI_BASE_ADDRS                          {OSPI_BASE}
/** Array initializer of OSPI peripheral base pointers */
#define OSPI_BASE_PTRS                           {OSPI}
/** Number of interrupt vector arrays for the OSPI module. */
#define OSPI_IRQS_ARR_COUNT                      (1u)
/** Number of interrupt channels for the OSPI module. */
#define OSPI_IRQS_CH_COUNT                       (1u)
/** Interrupt vectors for the OSPI peripheral type */
#define OSPI_IRQS                                {QSPI_IRQn}
#endif

#endif
