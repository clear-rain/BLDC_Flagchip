#ifndef _DEVICE_FEATURES_FC4150F512BS1P64T1A_H_
#define _DEVICE_FEATURES_FC4150F512BS1P64T1A_H_

#include "FC4150F512_Common_feature.h"

/*********************** PORT Features ****************************/
/** @brief Port Pin Mux structure */
typedef union
{
PORT_A2MuxType       ePortA2Mode;
PORT_A3MuxType       ePortA3Mode;
PORT_A4MuxType       ePortA4Mode;
PORT_A5MuxType       ePortA5Mode;
PORT_A7MuxType       ePortA7Mode;
PORT_A8MuxType       ePortA8Mode;
PORT_A10MuxType      ePortA10Mode;
PORT_A11MuxType      ePortA11Mode;
PORT_A15MuxType      ePortA15Mode;
PORT_A16MuxType      ePortA16Mode;
PORT_A26MuxType      ePortA26Mode;
PORT_A29MuxType      ePortA29Mode;
PORT_A30MuxType      ePortA30Mode;
PORT_B3MuxType       ePortB3Mode;
PORT_B4MuxType       ePortB4Mode;
PORT_B5MuxType       ePortB5Mode;
PORT_B6MuxType       ePortB6Mode;
PORT_B14MuxType      ePortB14Mode;
PORT_B15MuxType      ePortB15Mode;
PORT_B16MuxType      ePortB16Mode;
PORT_B25MuxType      ePortB25Mode;
PORT_B27MuxType      ePortB27Mode;
PORT_B28MuxType      ePortB28Mode;
PORT_B29MuxType      ePortB29Mode;
PORT_C5MuxType       ePortC5Mode;
PORT_C11MuxType      ePortC11Mode;
PORT_C13MuxType      ePortC13Mode;
PORT_C15MuxType      ePortC15Mode;
PORT_C16MuxType      ePortC16Mode;
PORT_C19MuxType      ePortC19Mode;
PORT_C23MuxType      ePortC23Mode;
PORT_C28MuxType      ePortC28Mode;
PORT_D2MuxType       ePortD2Mode;
PORT_D7MuxType       ePortD7Mode;
PORT_D8MuxType       ePortD8Mode;
PORT_D10MuxType      ePortD10Mode;
PORT_D11MuxType      ePortD11Mode;
PORT_D15MuxType      ePortD15Mode;
PORT_D16MuxType      ePortD16Mode;
PORT_D18MuxType      ePortD18Mode;
PORT_D23MuxType      ePortD23Mode;
PORT_D28MuxType      ePortD28Mode;
PORT_D29MuxType      ePortD29Mode;
PORT_E1MuxType       ePortE1Mode;
PORT_E2MuxType       ePortE2Mode;
PORT_E3MuxType       ePortE3Mode;
PORT_E6MuxType       ePortE6Mode;
PORT_E10MuxType      ePortE10Mode;
PORT_E12MuxType      ePortE12Mode;
PORT_E13MuxType      ePortE13Mode;
PORT_E15MuxType      ePortE15Mode;
PORT_E21MuxType      ePortE21Mode;
PORT_E25MuxType      ePortE25Mode;
Port_PinModeType     u32PortPinMode;
} Port_PinMuxType;

/*********************** GPIO Features ****************************/
/** @brief PortA Pin MASK structure */
#define PORTA_PIN_MASK     (uint32_t)(0x64018dbcu)
/** @brief PortB Pin MASK structure */
#define PORTB_PIN_MASK     (uint32_t)(0x3a01c078u)
/** @brief PortC Pin MASK structure */
#define PORTC_PIN_MASK     (uint32_t)(0x1089a820u)
/** @brief PortD Pin MASK structure */
#define PORTD_PIN_MASK     (uint32_t)(0x30858d84u)
/** @brief PortE Pin MASK structure */
#define PORTE_PIN_MASK     (uint32_t)(0x220b44eu)

/** @brief Port Pin MASK structure */
#define PIN_MASK_BASE      {PORTA_PIN_MASK, PORTB_PIN_MASK, PORTC_PIN_MASK, PORTD_PIN_MASK, PORTE_PIN_MASK}


#endif /* _DEVICE_FEATURES_FC4150F512BS1P64T1A_H_ */
