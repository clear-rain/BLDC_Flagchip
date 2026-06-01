#ifndef _DEVICE_FEATURES_FC4150_PORT_COMMON_H_
#define _DEVICE_FEATURES_FC4150_PORT_COMMON_H_
/*********************** PORT Features ****************************/
/** Number of instances of the PORT module. */
#define PORT_INSTANCE_COUNT                      (5u)
/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40049000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_Type *)PORTA_BASE)
/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x4004A000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_Type *)PORTB_BASE)
/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)
/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004D000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_Type *)PORTE_BASE)
/** Array initializer of PORT peripheral base addresses */
#define PORT_BASE_ADDRS                          {PORTA_BASE, PORTB_BASE, PORTC_BASE, PORTD_BASE, PORTE_BASE}
/** Array initializer of PORT peripheral base pointers */
#define PORT_BASE_PTRS                           {PORTA, PORTB, PORTC, PORTD, PORTE}


/** @brief Port digital filter clock source */
typedef enum
{
    PORT_FILTER_BUS_CLK = 0U,
    PORT_FILTER_AON32K_CLK
} PORT_DigitalFilterClkSrcType;


#define PORT_FILTER_CLOCL_SRC   PORT_FILTER_AON32K_CLK

/** @brief Port Mode Type */
typedef uint32_t Port_PinModeType;

#endif
