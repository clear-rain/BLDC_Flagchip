#ifndef _DEVICE_FEATURES_FC4150_TRGSEL_COMMON_H_
#define _DEVICE_FEATURES_FC4150_TRGSEL_COMMON_H_
/*********************** TRGSEL Features ****************************/
/* TRGSEL - Peripheral instance base addresses */
/** Peripheral TRGSEL0 base address */
#define TRGSEL0_BASE                             (0x40062000u)
/** Peripheral TRGSEL0 base pointer */
#define TRGSEL0                                  ((TRGSEL_Type *)TRGSEL0_BASE)
/** Peripheral TRGSEL1 base address */
#define TRGSEL1_BASE                             (0x40063000u)
/** Peripheral TRGSEL1 base pointer */
#define TRGSEL1                                  ((TRGSEL_Type *)TRGSEL1_BASE)
/** Peripheral TRGSEL2 base address */
#define TRGSEL2_BASE                             (0x40071000u)
/** Peripheral TRGSEL2 base pointer */
#define TRGSEL2                                  ((TRGSEL_Type *)TRGSEL2_BASE)
// need fill by yourself
///** Number of interrupt vector arrays for the TRGSEL module. */
//#define TRGSEL_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the TRGSEL module. */
//#define TRGSEL_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the TRGSEL peripheral type */
//#define TRGSEL_IRQS                              {TRGSEL0_IRQn, TRGSEL1_IRQn, TRGSEL2_IRQn, TRGSEL3_IRQn}
/**
 * @brief Number of target outputs of TrgSel 0
 *
 */
#define TRGSEL0_NUM_OUTPUTS            54U

/**
 * @brief Number of target outputs of TrgSel 1
 *
 */
#define TRGSEL1_NUM_OUTPUTS            25U

/**
 * @brief Number of target outputs of TrgSel 2
 *
 */
#define TRGSEL2_NUM_OUTPUTS            40U

/**
 * @brief Number of target outputs of TrgSel 3
 *
 */
#define TRGSEL3_NUM_OUTPUTS            16U

/**
 * @brief Number of input sources of TrgSel 0
 *
 */
#define TRGSEL0_NUM_SOURCES            105U

/**
 * @brief Number of input sources of TrgSel 1
 *
 */
#define TRGSEL1_NUM_SOURCES            115U

/**
 * @brief Number of input sources of TrgSel 2
 *
 */
#define TRGSEL2_NUM_SOURCES            32U


/**
 * @brief Number of input sources of TrgSel 3
 *
 */
#define TRGSEL3_NUM_SOURCES            64U
#endif
