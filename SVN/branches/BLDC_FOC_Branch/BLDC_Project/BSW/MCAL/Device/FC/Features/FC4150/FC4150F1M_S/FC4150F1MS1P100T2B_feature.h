#ifndef _DEVICE_FEATURES_FC4150F1MS1P100T2B_H_
#define _DEVICE_FEATURES_FC4150F1MS1P100T2B_H_

#include "FC4150F1M_S_Common_feature.h"

/*********************** PORT Features ****************************/
/** @brief Port Pin Mux structure */
typedef union
{
PORT_A0MuxType       ePortA0Mode;
PORT_A1MuxType       ePortA1Mode;
PORT_A2MuxType       ePortA2Mode;
PORT_A3MuxType       ePortA3Mode;
PORT_A4MuxType       ePortA4Mode;
PORT_A5MuxType       ePortA5Mode;
PORT_A6MuxType       ePortA6Mode;
PORT_A7MuxType       ePortA7Mode;
PORT_A8MuxType       ePortA8Mode;
PORT_A9MuxType       ePortA9Mode;
PORT_A10MuxType      ePortA10Mode;
PORT_A11MuxType      ePortA11Mode;
PORT_A12MuxType      ePortA12Mode;
PORT_A13MuxType      ePortA13Mode;
PORT_A14MuxType      ePortA14Mode;
PORT_A15MuxType      ePortA15Mode;
PORT_A16MuxType      ePortA16Mode;
PORT_A17MuxType      ePortA17Mode;
PORT_A24MuxType      ePortA24Mode;
PORT_B0MuxType       ePortB0Mode;
PORT_B1MuxType       ePortB1Mode;
PORT_B3MuxType       ePortB3Mode;
PORT_B4MuxType       ePortB4Mode;
PORT_B5MuxType       ePortB5Mode;
PORT_B6MuxType       ePortB6Mode;
PORT_B7MuxType       ePortB7Mode;
PORT_B8MuxType       ePortB8Mode;
PORT_B9MuxType       ePortB9Mode;
PORT_B10MuxType      ePortB10Mode;
PORT_B12MuxType      ePortB12Mode;
PORT_B13MuxType      ePortB13Mode;
PORT_B14MuxType      ePortB14Mode;
PORT_B15MuxType      ePortB15Mode;
PORT_B16MuxType      ePortB16Mode;
PORT_B17MuxType      ePortB17Mode;
PORT_C0MuxType       ePortC0Mode;
PORT_C1MuxType       ePortC1Mode;
PORT_C2MuxType       ePortC2Mode;
PORT_C3MuxType       ePortC3Mode;
PORT_C4MuxType       ePortC4Mode;
PORT_C5MuxType       ePortC5Mode;
PORT_C6MuxType       ePortC6Mode;
PORT_C7MuxType       ePortC7Mode;
PORT_C8MuxType       ePortC8Mode;
PORT_C9MuxType       ePortC9Mode;
PORT_C10MuxType      ePortC10Mode;
PORT_C11MuxType      ePortC11Mode;
PORT_C12MuxType      ePortC12Mode;
PORT_C13MuxType      ePortC13Mode;
PORT_C14MuxType      ePortC14Mode;
PORT_C15MuxType      ePortC15Mode;
PORT_C16MuxType      ePortC16Mode;
PORT_C17MuxType      ePortC17Mode;
PORT_D0MuxType       ePortD0Mode;
PORT_D1MuxType       ePortD1Mode;
PORT_D2MuxType       ePortD2Mode;
PORT_D3MuxType       ePortD3Mode;
PORT_D4MuxType       ePortD4Mode;
PORT_D5MuxType       ePortD5Mode;
PORT_D6MuxType       ePortD6Mode;
PORT_D7MuxType       ePortD7Mode;
PORT_D8MuxType       ePortD8Mode;
PORT_D9MuxType       ePortD9Mode;
PORT_D10MuxType      ePortD10Mode;
PORT_D11MuxType      ePortD11Mode;
PORT_D12MuxType      ePortD12Mode;
PORT_D15MuxType      ePortD15Mode;
PORT_D16MuxType      ePortD16Mode;
PORT_D17MuxType      ePortD17Mode;
PORT_E0MuxType       ePortE0Mode;
PORT_E1MuxType       ePortE1Mode;
PORT_E2MuxType       ePortE2Mode;
PORT_E3MuxType       ePortE3Mode;
PORT_E4MuxType       ePortE4Mode;
PORT_E5MuxType       ePortE5Mode;
PORT_E6MuxType       ePortE6Mode;
PORT_E7MuxType       ePortE7Mode;
PORT_E8MuxType       ePortE8Mode;
PORT_E9MuxType       ePortE9Mode;
PORT_E10MuxType      ePortE10Mode;
PORT_E11MuxType      ePortE11Mode;
PORT_E12MuxType      ePortE12Mode;
PORT_E13MuxType      ePortE13Mode;
PORT_E14MuxType      ePortE14Mode;
PORT_E15MuxType      ePortE15Mode;
PORT_E16MuxType      ePortE16Mode;
Port_PinModeType     u32PortPinMode;
} Port_PinMuxType;

/*********************** GPIO Features ****************************/
/** @brief PortA Pin MASK structure */
#define PORTA_PIN_MASK     (uint32_t)(0x103ffffu)
/** @brief PortB Pin MASK structure */
#define PORTB_PIN_MASK     (uint32_t)(0x3f7fbu)
/** @brief PortC Pin MASK structure */
#define PORTC_PIN_MASK     (uint32_t)(0x3ffffu)
/** @brief PortD Pin MASK structure */
#define PORTD_PIN_MASK     (uint32_t)(0x39fffu)
/** @brief PortE Pin MASK structure */
#define PORTE_PIN_MASK     (uint32_t)(0x1ffffu)

/** @brief Port Pin MASK structure */
#define PIN_MASK_BASE      {PORTA_PIN_MASK, PORTB_PIN_MASK, PORTC_PIN_MASK, PORTD_PIN_MASK, PORTE_PIN_MASK}

#endif /* _DEVICE_FEATURES_FC4150F1MS1P100T2B_H_ */
