#ifndef _DEVICE_FEATURES_FC4150_ADC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_ADC_COMMON_H_
/*********************** ADC Features ****************************/
#define ADC_SC_COUNT 32
#define ADC_RESULT_COUNT 32

/** Number of instances of the ADC module. */
#define ADC_INSTANCE_COUNT                       (2u)
/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x4003B000u)

/** Peripheral ADC1 base address */
#define ADC1_BASE                                (0x40027000u)

/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)

/** Peripheral ADC1 base pointer */
#define ADC1                                     ((ADC_Type *)ADC1_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           {ADC0_BASE, ADC1_BASE}
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            {ADC0, ADC1}
// need fill by yourself
///** Number of interrupt vector arrays for the ADC module. */
//#define ADC_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the ADC module. */
//#define ADC_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the ADC peripheral type */
//#define ADC_IRQS                                 {ADC0_IRQn, ADC1_IRQn}

#endif /* _DEVICE_FEATURES_FC4150_ADC_COMMON_H_ */
