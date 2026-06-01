#ifndef _DEVICE_FEATURES_FC4150_FCSPI_COMMON_H_
#define _DEVICE_FEATURES_FC4150_FCSPI_COMMON_H_
/*********************** FCSPI Features ****************************/
/** Number of instances of the FCSPI module. */
#define FCSPI_INSTANCE_COUNT                     (4u)
/* FCSPI - Peripheral instance base addresses */
/** Peripheral FCSPI0 base address */
#define FCSPI0_BASE                              (0x4002C000u)
/** Peripheral FCSPI0 base pointer */
#define FCSPI0                                   ((FCSPI_Type *)FCSPI0_BASE)
/** Peripheral FCSPI1 base address */
#define FCSPI1_BASE                              (0x4002D000u)
/** Peripheral FCSPI1 base pointer */
#define FCSPI1                                   ((FCSPI_Type *)FCSPI1_BASE)
/** Peripheral FCSPI2 base address */
#define FCSPI2_BASE                              (0x4002E000u)
/** Peripheral FCSPI2 base pointer */
#define FCSPI2                                   ((FCSPI_Type *)FCSPI2_BASE)
/** Peripheral FCSPI3 base address */
#define FCSPI3_BASE                              (0x4002F000u)
/** Peripheral FCSPI3 base pointer */
#define FCSPI3                                   ((FCSPI_Type *)FCSPI3_BASE)
/** Array initializer of FCSPI peripheral base addresses */
#define FCSPI_BASE_ADDRS                         {FCSPI0_BASE, FCSPI1_BASE, FCSPI2_BASE, FCSPI3_BASE}
/** Array initializer of FCSPI peripheral base pointers */
#define FCSPI_BASE_PTRS                          {FCSPI0, FCSPI1, FCSPI2, FCSPI3}
#endif
