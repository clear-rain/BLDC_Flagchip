#ifndef _DEVICE_FEATURES_FC4150F1M__B_PORT_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_PORT_COMMON_H_

/*********************** PORT Features ****************************/
/** @brief PORTA0 Mode enumeration */
typedef enum
{
PORTA_0_ADC1_SE26 = 0U,
PORTA_0_GPIO = 1U,
PORTA_0_FTU2_CH1 = 2U,
PORTA_0_FTU2_QD_PHA = 5U,
PORTA_0_FCUART0_CTS = 6U,
PORTA_0_TRGSEL_OUT3 = 7U,
} PORT_A0MuxType;

/** @brief PORTA1 Mode enumeration */
typedef enum
{
PORTA_1_ADC0_SE28_ADC1_SE28 = 0U,
PORTA_1_GPIO = 1U,
PORTA_1_FTU1_CH1 = 2U,
PORTA_1_FTU1_QD_PHA = 5U,
PORTA_1_FCUART0_RTS = 6U,
PORTA_1_TRGSEL_OUT0 = 7U,
} PORT_A1MuxType;

/** @brief PORTA10 Mode enumeration */
typedef enum
{
PORTA_10_GPIO = 1U,
PORTA_10_FTU1_CH4 = 2U,
PORTA_10_AONTIMER0_CLK1 = 3U,
PORTA_10_FCIIC0_SCL = 5U,
PORTA_10_JTAG_TDO_TRACE_SWO = 7U,
} PORT_A10MuxType;

/** @brief PORTA11 Mode enumeration */
typedef enum
{
PORTA_11_GPIO = 1U,
PORTA_11_FTU1_CH5 = 2U,
PORTA_11_FCSPI0_PCS0 = 5U,
PORTA_11_NMI_b = 7U,
} PORT_A11MuxType;

/** @brief PORTA12 Mode enumeration */
typedef enum
{
PORTA_12_GPIO = 1U,
PORTA_12_FTU1_CH6 = 2U,
PORTA_12_FLEXCAN1_RX = 3U,
PORTA_12_FCSPI0_SOUT = 5U,
PORTA_12_FTU2_QD_PHB = 6U,
} PORT_A12MuxType;

/** @brief PORTA13 Mode enumeration */
typedef enum
{
PORTA_13_GPIO = 1U,
PORTA_13_FTU1_CH7 = 2U,
PORTA_13_FLEXCAN1_TX = 3U,
PORTA_13_FCUART0_RX = 5U,
PORTA_13_FTU2_QD_PHA = 6U,
} PORT_A13MuxType;

/** @brief PORTA14 Mode enumeration */
typedef enum
{
PORTA_14_GPIO = 1U,
PORTA_14_FTU_FLT17 = 2U,
PORTA_14_AONTIMER0_CLK2 = 3U,
PORTA_14_FWM_IN = 4U,
PORTA_14_FCUART0_TX = 5U,
} PORT_A14MuxType;

/** @brief PORTA15 Mode enumeration */
typedef enum
{
PORTA_15_ADC0_SE21 = 0U,
PORTA_15_GPIO = 1U,
PORTA_15_FTU1_CH2 = 2U,
PORTA_15_FCSPI2_PCS3 = 4U,
PORTA_15_TRGSEL_OUT0 = 5U,
} PORT_A15MuxType;

/** @brief PORTA16 Mode enumeration */
typedef enum
{
PORTA_16_ADC0_SE22 = 0U,
PORTA_16_GPIO = 1U,
PORTA_16_FTU1_CH3 = 2U,
PORTA_16_FCSPI1_PCS2 = 3U,
} PORT_A16MuxType;

/** @brief PORTA17 Mode enumeration */
typedef enum
{
PORTA_17_GPIO = 1U,
PORTA_17_FTU0_CH6 = 2U,
PORTA_17_FWM_OUT_b = 4U,
PORTA_17_FTU_FLT15 = 5U,
} PORT_A17MuxType;

/** @brief PORTA2 Mode enumeration */
typedef enum
{
PORTA_2_ADC0_SE27 = 0U,
PORTA_2_GPIO = 1U,
PORTA_2_FTU3_CH0 = 2U,
PORTA_2_FCIIC0_SDA = 3U,
PORTA_2_FWM_OUT_b = 4U,
PORTA_2_FCUART0_RX = 6U,
} PORT_A2MuxType;

/** @brief PORTA25 Mode enumeration */
typedef enum
{
PORTA_25_ADC0_SE0 = 0U,
PORTA_25_GPIO = 1U,
PORTA_25_FTU5_CH0 = 2U,
PORTA_25_FCSPI2_SOUT = 3U,
} PORT_A25MuxType;

/** @brief PORTA26 Mode enumeration */
typedef enum
{
PORTA_26_CMP0_IN0 = 0U,
PORTA_26_GPIO = 1U,
PORTA_26_FTU5_CH1 = 2U,
PORTA_26_FCSPI1_PCS0 = 3U,
} PORT_A26MuxType;

/** @brief PORTA27 Mode enumeration */
typedef enum
{
PORTA_27_ADC0_SE2 = 0U,
PORTA_27_GPIO = 1U,
PORTA_27_FTU5_CH2 = 2U,
PORTA_27_FCSPI1_SOUT = 3U,
PORTA_27_FCUART0_TX = 4U,
PORTA_27_FLEXCAN0_TX = 5U,
} PORT_A27MuxType;

/** @brief PORTA28 Mode enumeration */
typedef enum
{
PORTA_28_ADC0_SE3 = 0U,
PORTA_28_GPIO = 1U,
PORTA_28_FTU5_CH3 = 2U,
PORTA_28_FCSPI1_SCK = 3U,
PORTA_28_FCUART0_RX = 4U,
PORTA_28_FLEXCAN0_RX = 5U,
} PORT_A28MuxType;

/** @brief PORTA29 Mode enumeration */
typedef enum
{
PORTA_29_ADC0_SE8 = 0U,
PORTA_29_GPIO = 1U,
PORTA_29_FTU5_CH4 = 2U,
PORTA_29_FCUART2_TX = 4U,
PORTA_29_FCSPI1_SIN = 5U,
} PORT_A29MuxType;

/** @brief PORTA3 Mode enumeration */
typedef enum
{
PORTA_3_ADC0_SE26 = 0U,
PORTA_3_GPIO = 1U,
PORTA_3_FTU3_CH1 = 2U,
PORTA_3_FCIIC0_SCL = 3U,
PORTA_3_FWM_IN = 4U,
PORTA_3_FCUART0_TX = 6U,
} PORT_A3MuxType;

/** @brief PORTA30 Mode enumeration */
typedef enum
{
PORTA_30_ADC0_SE9 = 0U,
PORTA_30_GPIO = 1U,
PORTA_30_FTU5_CH5 = 2U,
PORTA_30_FCUART2_RX = 3U,
PORTA_30_FCSPI0_SOUT = 4U,
} PORT_A30MuxType;

/** @brief PORTA31 Mode enumeration */
typedef enum
{
PORTA_31_ADC0_SE13_CMP0_IN3 = 0U,
PORTA_31_GPIO = 1U,
PORTA_31_FTU5_CH6 = 2U,
PORTA_31_FCSPI0_PCS1 = 4U,
} PORT_A31MuxType;

/** @brief PORTA4 Mode enumeration */
typedef enum
{
PORTA_4_GPIO = 1U,
PORTA_4_TRGSEL_OUT7 = 3U,
PORTA_4_CMP0_OUT = 4U,
PORTA_4_FWM_OUT_b = 5U,
PORTA_4_JTAG_TMS_SWD_DIO = 7U,
} PORT_A4MuxType;

/** @brief PORTA5 Mode enumeration */
typedef enum
{
PORTA_5_GPIO = 1U,
PORTA_5_RESET_b = 7U,
} PORT_A5MuxType;

/** @brief PORTA6 Mode enumeration */
typedef enum
{
PORTA_6_ADC1_SE10 = 0U,
PORTA_6_GPIO = 1U,
PORTA_6_FTU_FLT13 = 2U,
PORTA_6_FCSPI1_PCS1 = 3U,
PORTA_6_FTU5_CH5 = 4U,
PORTA_6_TRGSEL_OUT4 = 5U,
PORTA_6_FCUART1_CTS = 6U,
} PORT_A6MuxType;

/** @brief PORTA7 Mode enumeration */
typedef enum
{
PORTA_7_GPIO = 1U,
PORTA_7_FTU_FLT12 = 2U,
PORTA_7_FTU5_CH3 = 3U,
PORTA_7_FCSPI1_SCK = 5U,
PORTA_7_FCUART1_RTS = 6U,
} PORT_A7MuxType;

/** @brief PORTA8 Mode enumeration */
typedef enum
{
PORTA_8_ADC1_SE3 = 0U,
PORTA_8_GPIO = 1U,
PORTA_8_FCUART2_RX = 2U,
PORTA_8_FTU_FLT21 = 5U,
PORTA_8_FCUART0_RX = 6U,
} PORT_A8MuxType;

/** @brief PORTA9 Mode enumeration */
typedef enum
{
PORTA_9_ADC1_SE7 = 0U,
PORTA_9_GPIO = 1U,
PORTA_9_FCUART2_TX = 2U,
PORTA_9_FTU_FLT20 = 5U,
PORTA_9_FCUART0_TX = 6U,
} PORT_A9MuxType;

/** @brief PORTB0 Mode enumeration */
typedef enum
{
PORTB_0_ADC1_SE12 = 0U,
PORTB_0_GPIO = 1U,
PORTB_0_FCUART0_RX = 2U,
PORTB_0_FCSPI0_PCS0 = 3U,
PORTB_0_AONTIMER0_CLK3 = 4U,
PORTB_0_FLEXCAN0_RX = 5U,
PORTB_0_FTU4_CH6 = 6U,
} PORT_B0MuxType;

/** @brief PORTB1 Mode enumeration */
typedef enum
{
PORTB_1_ADC1_SE13 = 0U,
PORTB_1_GPIO = 1U,
PORTB_1_FCUART0_TX = 2U,
PORTB_1_FCSPI0_SOUT = 3U,
PORTB_1_FTU_TCK0 = 4U,
PORTB_1_FLEXCAN0_TX = 5U,
PORTB_1_FTU4_CH5 = 6U,
} PORT_B1MuxType;

/** @brief PORTB10 Mode enumeration */
typedef enum
{
PORTB_10_GPIO = 1U,
PORTB_10_FTU3_CH2 = 2U,
PORTB_10_FLEXCAN0_TX = 3U,
PORTB_10_TRGSEL_OUT2 = 5U,
PORTB_10_FTU2_QD_PHA = 6U,
} PORT_B10MuxType;

/** @brief PORTB12 Mode enumeration */
typedef enum
{
PORTB_12_ADC1_SE20 = 0U,
PORTB_12_GPIO = 1U,
PORTB_12_FTU0_CH0 = 2U,
PORTB_12_FLEXCAN2_RX = 4U,
} PORT_B12MuxType;

/** @brief PORTB13 Mode enumeration */
typedef enum
{
PORTB_13_ADC1_SE19 = 0U,
PORTB_13_GPIO = 1U,
PORTB_13_FTU0_CH1 = 2U,
PORTB_13_FLEXCAN2_TX = 4U,
} PORT_B13MuxType;

/** @brief PORTB14 Mode enumeration */
typedef enum
{
PORTB_14_ADC1_SE18 = 0U,
PORTB_14_GPIO = 1U,
PORTB_14_FTU0_CH2 = 2U,
PORTB_14_FCSPI1_SCK = 3U,
} PORT_B14MuxType;

/** @brief PORTB15 Mode enumeration */
typedef enum
{
PORTB_15_ADC1_SE17 = 0U,
PORTB_15_GPIO = 1U,
PORTB_15_FTU0_CH3 = 2U,
PORTB_15_FCSPI1_SIN = 3U,
} PORT_B15MuxType;

/** @brief PORTB16 Mode enumeration */
typedef enum
{
PORTB_16_ADC1_SE16 = 0U,
PORTB_16_GPIO = 1U,
PORTB_16_FTU0_CH4 = 2U,
PORTB_16_FCSPI1_SOUT = 3U,
} PORT_B16MuxType;

/** @brief PORTB17 Mode enumeration */
typedef enum
{
PORTB_17_GPIO = 1U,
PORTB_17_FTU0_CH5 = 2U,
PORTB_17_FCSPI1_PCS3 = 3U,
PORTB_17_TRGSEL_OUT3 = 5U,
} PORT_B17MuxType;

/** @brief PORTB18 Mode enumeration */
typedef enum
{
PORTB_18_CMP0_IN4 = 0U,
PORTB_18_GPIO = 1U,
PORTB_18_FTU5_CH7 = 2U,
PORTB_18_FCSPI1_PCS1 = 4U,
} PORT_B18MuxType;

/** @brief PORTB20 Mode enumeration */
typedef enum
{
PORTB_20_ADC0_SE14 = 0U,
PORTB_20_GPIO = 1U,
PORTB_20_FTU2_CH5 = 2U,
PORTB_20_FCUART1_TX = 3U,
PORTB_20_SCG_CLKOUT = 7U,
} PORT_B20MuxType;

/** @brief PORTB21 Mode enumeration */
typedef enum
{
PORTB_21_ADC0_SE15 = 0U,
PORTB_21_GPIO = 1U,
PORTB_21_FTU2_CH4 = 2U,
PORTB_21_FCUART1_RX = 3U,
PORTB_21_RTC_CLKOUT = 7U,
} PORT_B21MuxType;

/** @brief PORTB22 Mode enumeration */
typedef enum
{
PORTB_22_GPIO = 1U,
PORTB_22_FTU_FLT8 = 2U,
PORTB_22_FCUART1_TX = 5U,
PORTB_22_OSPI_A_IO2 = 6U,
PORTB_22_FCSPI3_PCS3 = 7U,
} PORT_B22MuxType;

/** @brief PORTB23 Mode enumeration */
typedef enum
{
PORTB_23_GPIO = 1U,
PORTB_23_FTU_FLT9 = 2U,
PORTB_23_FCUART1_RX = 3U,
PORTB_23_OSPI_A_IO4  = 6U,
} PORT_B23MuxType;

/** @brief PORTB25 Mode enumeration */
typedef enum
{
PORTB_25_GPIO = 1U,
PORTB_25_FTU1_CH2 = 2U,
PORTB_25_FCSPI2_PCS0 = 5U,
} PORT_B25MuxType;

/** @brief PORTB27 Mode enumeration */
typedef enum
{
PORTB_27_GPIO = 1U,
PORTB_27_FCSPI2_SOUT = 5U,
} PORT_B27MuxType;

/** @brief PORTB28 Mode enumeration */
typedef enum
{
PORTB_28_GPIO = 1U,
PORTB_28_FCSPI2_SIN = 5U,
} PORT_B28MuxType;

/** @brief PORTB29 Mode enumeration */
typedef enum
{
PORTB_29_GPIO = 1U,
PORTB_29_FTU1_CH0 = 2U,
PORTB_29_FTU1_QD_PHB = 4U,
PORTB_29_FCSPI2_SCK = 5U,
} PORT_B29MuxType;

/** @brief PORTB3 Mode enumeration */
typedef enum
{
PORTB_3_GPIO = 1U,
PORTB_3_FTU1_CH1 = 2U,
PORTB_3_FCSPI0_SIN = 3U,
PORTB_3_FTU1_QD_PHA = 4U,
} PORT_B3MuxType;

/** @brief PORTB4 Mode enumeration */
typedef enum
{
PORTB_4_GPIO = 1U,
PORTB_4_FTU0_CH4 = 2U,
PORTB_4_FCSPI0_SOUT = 3U,
PORTB_4_FCIIC1_SDA = 4U,
} PORT_B4MuxType;

/** @brief PORTB5 Mode enumeration */
typedef enum
{
PORTB_5_GPIO = 1U,
PORTB_5_FTU0_CH5 = 2U,
PORTB_5_FCIIC1_SCL = 3U,
PORTB_5_FCSPI0_PCS0 = 4U,
PORTB_5_SCG_CLKOUT = 5U,
} PORT_B5MuxType;

/** @brief PORTB6 Mode enumeration */
typedef enum
{
PORTB_6_XTAL = 0U,
PORTB_6_GPIO = 1U,
PORTB_6_FCIIC0_SDA = 2U,
} PORT_B6MuxType;

/** @brief PORTB7 Mode enumeration */
typedef enum
{
PORTB_7_EXTAL = 0U,
PORTB_7_GPIO = 1U,
PORTB_7_FCIIC0_SCL = 2U,
} PORT_B7MuxType;

/** @brief PORTB8 Mode enumeration */
typedef enum
{
PORTB_8_ADC0_SE29_ADC1_SE29 = 0U,
PORTB_8_GPIO = 1U,
PORTB_8_FTU3_CH0 = 2U,
PORTB_8_FLEXCAN0_RX = 3U,
PORTB_8_FCUART1_CTS = 6U,
} PORT_B8MuxType;

/** @brief PORTB9 Mode enumeration */
typedef enum
{
PORTB_9_ADC0_SE30_ADC1_SE30 = 0U,
PORTB_9_GPIO = 1U,
PORTB_9_FTU3_CH1 = 2U,
PORTB_9_TRGSEL_OUT1 = 5U,
} PORT_B9MuxType;

/** @brief PORTC0 Mode enumeration */
typedef enum
{
PORTC_0_GPIO = 1U,
PORTC_0_FTU0_CH0 = 2U,
PORTC_0_OSPI_A_IO6  = 4U,
PORTC_0_FTU1_CH6 = 6U,
PORTC_0_FCSPI3_PCS2 = 7U,
} PORT_C0MuxType;

/** @brief PORTC1 Mode enumeration */
typedef enum
{
PORTC_1_GPIO = 1U,
PORTC_1_FTU0_CH1 = 2U,
PORTC_1_FCSPI2_SOUT = 3U,
PORTC_1_OSPI_A_IO5  = 4U,
PORTC_1_FTU1_CH7 = 6U,
PORTC_1_FCUART3_TX = 7U,
} PORT_C1MuxType;

/** @brief PORTC10 Mode enumeration */
typedef enum
{
PORTC_10_ADC1_SE14 = 0U,
PORTC_10_GPIO = 1U,
PORTC_10_FTU3_CH4 = 2U,
} PORT_C10MuxType;

/** @brief PORTC11 Mode enumeration */
typedef enum
{
PORTC_11_GPIO = 1U,
PORTC_11_FTU3_CH5 = 2U,
PORTC_11_FTU4_CH2 = 3U,
PORTC_11_FCSPI1_PCS0 = 5U,
} PORT_C11MuxType;

/** @brief PORTC12 Mode enumeration */
typedef enum
{
PORTC_12_GPIO = 1U,
PORTC_12_FTU3_CH6 = 2U,
PORTC_12_FTU2_CH6 = 3U,
PORTC_12_FCUART2_CTS = 4U,
PORTC_12_TRGSEL_OUT5 = 5U,
} PORT_C12MuxType;

/** @brief PORTC13 Mode enumeration */
typedef enum
{
PORTC_13_ADC1_SE15 = 0U,
PORTC_13_GPIO = 1U,
PORTC_13_FTU3_CH7 = 2U,
PORTC_13_FTU2_CH7 = 3U,
PORTC_13_FCUART2_RTS = 4U,
PORTC_13_TRGSEL_OUT6 = 5U,
} PORT_C13MuxType;

/** @brief PORTC14 Mode enumeration */
typedef enum
{
PORTC_14_GPIO = 1U,
PORTC_14_FTU1_CH2 = 2U,
PORTC_14_FCSPI2_PCS0 = 3U,
PORTC_14_OSPI_A_CS  = 6U,
} PORT_C14MuxType;

/** @brief PORTC15 Mode enumeration */
typedef enum
{
PORTC_15_GPIO = 1U,
PORTC_15_FTU1_CH3 = 2U,
PORTC_15_FCSPI2_SCK = 3U,
PORTC_15_OSPI_A_IO3  = 6U,
PORTC_15_FCUART5_TX = 7U,
} PORT_C15MuxType;

/** @brief PORTC16 Mode enumeration */
typedef enum
{
PORTC_16_GPIO = 1U,
PORTC_16_FTU_FLT7 = 2U,
PORTC_16_FLEXCAN2_RX = 3U,
PORTC_16_FCSPI2_SIN = 4U,
PORTC_16_FCUART5_RX = 7U,
} PORT_C16MuxType;

/** @brief PORTC17 Mode enumeration */
typedef enum
{
PORTC_17_GPIO = 1U,
PORTC_17_FTU_FLT6 = 2U,
PORTC_17_FLEXCAN2_TX = 3U,
PORTC_17_FCSPI2_PCS3 = 4U,
PORTC_17_FCUART4_TX = 7U,
} PORT_C17MuxType;

/** @brief PORTC19 Mode enumeration */
typedef enum
{
PORTC_19_GPIO = 1U,
PORTC_19_FCSPI2_PCS1 = 5U,
} PORT_C19MuxType;

/** @brief PORTC2 Mode enumeration */
typedef enum
{
PORTC_2_GPIO = 1U,
PORTC_2_FTU0_CH2 = 2U,
PORTC_2_FLEXCAN0_RX = 3U,
PORTC_2_FCUART0_RX = 4U,
PORTC_2_ETM_TRACE_CLKOUT = 6U,
} PORT_C2MuxType;

/** @brief PORTC23 Mode enumeration */
typedef enum
{
PORTC_23_GPIO = 1U,
PORTC_23_FCSPI0_SCK = 2U,
} PORT_C23MuxType;

/** @brief PORTC27 Mode enumeration */
typedef enum
{
PORTC_27_GPIO = 1U,
PORTC_27_FTU4_CH4 = 2U,
} PORT_C27MuxType;

/** @brief PORTC28 Mode enumeration */
typedef enum
{
PORTC_28_GPIO = 1U,
PORTC_28_FTU4_CH7 = 2U,
} PORT_C28MuxType;

/** @brief PORTC29 Mode enumeration */
typedef enum
{
PORTC_29_GPIO = 1U,
PORTC_29_FTU5_CH2 = 2U,
} PORT_C29MuxType;

/** @brief PORTC3 Mode enumeration */
typedef enum
{
PORTC_3_GPIO = 1U,
PORTC_3_FTU0_CH3 = 2U,
PORTC_3_FLEXCAN0_TX = 3U,
PORTC_3_FCUART0_TX = 4U,
} PORT_C3MuxType;

/** @brief PORTC30 Mode enumeration */
typedef enum
{
PORTC_30_ADC1_SE11 = 0U,
PORTC_30_GPIO = 1U,
PORTC_30_FTU5_CH4 = 2U,
} PORT_C30MuxType;

/** @brief PORTC31 Mode enumeration */
typedef enum
{
PORTC_31_GPIO = 1U,
PORTC_31_FTU5_CH6 = 2U,
PORTC_31_FCIIC1_SDA = 4U,
} PORT_C31MuxType;

/** @brief PORTC4 Mode enumeration */
typedef enum
{
PORTC_4_GPIO = 1U,
PORTC_4_FTU1_CH0 = 2U,
PORTC_4_RTC_CLKOUT = 3U,
PORTC_4_FWM_IN = 5U,
PORTC_4_FTU1_QD_PHB = 6U,
PORTC_4_JTAG_TCLK_SWD_CLK = 7U,
} PORT_C4MuxType;

/** @brief PORTC5 Mode enumeration */
typedef enum
{
PORTC_5_GPIO = 1U,
PORTC_5_FTU2_CH0 = 2U,
PORTC_5_RTC_CLKOUT = 3U,
PORTC_5_FCIIC0_SDA = 5U,
PORTC_5_FTU2_QD_PHB = 6U,
PORTC_5_JTAG_TDI = 7U,
} PORT_C5MuxType;

/** @brief PORTC6 Mode enumeration */
typedef enum
{
PORTC_6_ADC0_SE23 = 0U,
PORTC_6_GPIO = 1U,
PORTC_6_FCUART1_RX = 2U,
PORTC_6_FLEXCAN1_RX = 3U,
PORTC_6_FTU3_CH2 = 4U,
PORTC_6_FTU1_QD_PHB = 6U,
} PORT_C6MuxType;

/** @brief PORTC7 Mode enumeration */
typedef enum
{
PORTC_7_ADC1_SE24 = 0U,
PORTC_7_GPIO = 1U,
PORTC_7_FCUART1_TX = 2U,
PORTC_7_FLEXCAN1_TX = 3U,
PORTC_7_FTU3_CH3 = 4U,
PORTC_7_FTU1_QD_PHA = 6U,
} PORT_C7MuxType;

/** @brief PORTC8 Mode enumeration */
typedef enum
{
PORTC_8_GPIO = 1U,
PORTC_8_FCUART1_RX = 2U,
PORTC_8_FTU_FLT11 = 3U,
PORTC_8_FTU5_CH1 = 4U,
PORTC_8_FCSPI1_SIN = 5U,
PORTC_8_FCUART0_CTS = 6U,
} PORT_C8MuxType;

/** @brief PORTC9 Mode enumeration */
typedef enum
{
PORTC_9_GPIO = 1U,
PORTC_9_FCUART1_TX = 2U,
PORTC_9_FTU_FLT10 = 3U,
PORTC_9_FTU5_CH0 = 4U,
PORTC_9_FCSPI1_SOUT = 5U,
PORTC_9_FCUART0_RTS = 6U,
} PORT_C9MuxType;

/** @brief PORTD0 Mode enumeration */
typedef enum
{
PORTD_0_ADC1_SE1 = 0U,
PORTD_0_GPIO = 1U,
PORTD_0_FTU0_CH2 = 2U,
PORTD_0_FCSPI1_SCK = 3U,
PORTD_0_FTU2_CH0 = 4U,
PORTD_0_ETM_TRACE_D0 = 5U,
PORTD_0_TRGSEL_OUT1 = 7U,
} PORT_D0MuxType;

/** @brief PORTD1 Mode enumeration */
typedef enum
{
PORTD_1_ADC1_SE5 = 0U,
PORTD_1_GPIO = 1U,
PORTD_1_FTU0_CH3 = 2U,
PORTD_1_FCSPI1_SIN = 3U,
PORTD_1_FTU2_CH1 = 4U,
PORTD_1_TRGSEL_OUT2 = 7U,
} PORT_D1MuxType;

/** @brief PORTD10 Mode enumeration */
typedef enum
{
PORTD_10_GPIO = 1U,
PORTD_10_FTU2_CH0 = 2U,
PORTD_10_FTU2_QD_PHB = 3U,
PORTD_10_ETM_TRACE_D3 = 4U,
PORTD_10_SCG_CLKOUT = 6U,
PORTD_10_FCSPI3_PCS1 = 7U,
} PORT_D10MuxType;

/** @brief PORTD11 Mode enumeration */
typedef enum
{
PORTD_11_GPIO = 1U,
PORTD_11_FTU2_CH1 = 2U,
PORTD_11_FTU2_QD_PHA = 3U,
PORTD_11_ETM_TRACE_D2 = 4U,
PORTD_11_FCUART2_CTS = 6U,
PORTD_11_FCSPI3_PCS0 = 7U,
} PORT_D11MuxType;

/** @brief PORTD12 Mode enumeration */
typedef enum
{
PORTD_12_GPIO = 1U,
PORTD_12_FTU2_CH2 = 2U,
PORTD_12_OSPI_A_IO7  = 3U,
PORTD_12_ETM_TRACE_D1 = 4U,
PORTD_12_FCUART2_RTS = 6U,
PORTD_12_FCSPI3_SOUT = 7U,
} PORT_D12MuxType;

/** @brief PORTD15 Mode enumeration */
typedef enum
{
PORTD_15_ADC0_SE11_CMP0_IN1 = 0U,
PORTD_15_GPIO = 1U,
PORTD_15_FTU0_CH0 = 2U,
PORTD_15_ETM_TRACE_D3 = 3U,
PORTD_15_FCSPI0_SCK = 4U,
PORTD_15_FCUART2_RTS = 6U,
} PORT_D15MuxType;

/** @brief PORTD16 Mode enumeration */
typedef enum
{
PORTD_16_ADC0_SE10 = 0U,
PORTD_16_GPIO = 1U,
PORTD_16_FTU0_CH1 = 2U,
PORTD_16_ETM_TRACE_D2 = 3U,
PORTD_16_FCSPI0_SIN = 4U,
} PORT_D16MuxType;

/** @brief PORTD17 Mode enumeration */
typedef enum
{
PORTD_17_ADC0_SE7 = 0U,
PORTD_17_GPIO = 1U,
PORTD_17_FCUART2_RX = 3U,
PORTD_17_FTU_FLT3 = 4U,
} PORT_D17MuxType;

/** @brief PORTD18 Mode enumeration */
typedef enum
{
PORTD_18_ADC1_SE8 = 0U,
PORTD_18_GPIO = 1U,
PORTD_18_FTU5_CH7 = 2U,
} PORT_D18MuxType;

/** @brief PORTD19 Mode enumeration */
typedef enum
{
PORTD_19_GPIO = 1U,
PORTD_19_FWM_OUT_b = 2U,
PORTD_19_FCIIC1_SCL = 4U,
} PORT_D19MuxType;

/** @brief PORTD2 Mode enumeration */
typedef enum
{
PORTD_2_ADC0_SE24 = 0U,
PORTD_2_GPIO = 1U,
PORTD_2_FTU3_CH4 = 2U,
PORTD_2_ISP_EN_B = 7U,
} PORT_D2MuxType;

/** @brief PORTD22 Mode enumeration */
typedef enum
{
PORTD_22_ADC1_SE21 = 0U,
PORTD_22_GPIO = 1U,
} PORT_D22MuxType;

/** @brief PORTD23 Mode enumeration */
typedef enum
{
PORTD_23_ADC0_SE25 = 0U,
PORTD_23_GPIO = 1U,
} PORT_D23MuxType;

/** @brief PORTD24 Mode enumeration */
typedef enum
{
PORTD_24_ADC0_SE31_ADC1_SE31 = 0U,
PORTD_24_GPIO = 1U,
PORTD_24_FTU3_CH3 = 2U,
} PORT_D24MuxType;

/** @brief PORTD27 Mode enumeration */
typedef enum
{
PORTD_27_GPIO = 1U,
} PORT_D27MuxType;

/** @brief PORTD28 Mode enumeration */
typedef enum
{
PORTD_28_GPIO = 1U,
} PORT_D28MuxType;

/** @brief PORTD29 Mode enumeration */
typedef enum
{
PORTD_29_ADC1_SE27 = 0U,
PORTD_29_GPIO = 1U,
} PORT_D29MuxType;

/** @brief PORTD3 Mode enumeration */
typedef enum
{
PORTD_3_ADC1_SE23 = 0U,
PORTD_3_GPIO = 1U,
PORTD_3_FTU3_CH5 = 2U,
PORTD_3_FCSPI1_PCS0 = 3U,
} PORT_D3MuxType;

/** @brief PORTD30 Mode enumeration */
typedef enum
{
PORTD_30_ADC1_SE25 = 0U,
PORTD_30_GPIO = 1U,
} PORT_D30MuxType;

/** @brief PORTD4 Mode enumeration */
typedef enum
{
PORTD_4_ADC1_SE22 = 0U,
PORTD_4_GPIO = 1U,
PORTD_4_FTU_FLT16 = 2U,
} PORT_D4MuxType;

/** @brief PORTD5 Mode enumeration */
typedef enum
{
PORTD_5_GPIO = 1U,
PORTD_5_FTU2_CH3 = 2U,
PORTD_5_AONTIMER0_CLK2 = 3U,
PORTD_5_FTU_FLT5 = 4U,
PORTD_5_OSPI_A_IO1  = 6U,
PORTD_5_FCSPI3_SIN = 7U,
} PORT_D5MuxType;

/** @brief PORTD6 Mode enumeration */
typedef enum
{
PORTD_6_GPIO = 1U,
PORTD_6_FCUART2_RX = 2U,
PORTD_6_FTU_FLT4 = 4U,
PORTD_6_OSPI_A_IO0 = 6U,
PORTD_6_FCSPI3_SCK = 7U,
} PORT_D6MuxType;

/** @brief PORTD7 Mode enumeration */
typedef enum
{
PORTD_7_GPIO = 1U,
PORTD_7_FCUART2_TX = 2U,
PORTD_7_FCSPI0_SIN = 4U,
PORTD_7_ETM_TRACE_D0 = 6U,
} PORT_D7MuxType;

/** @brief PORTD8 Mode enumeration */
typedef enum
{
PORTD_8_GPIO = 1U,
PORTD_8_FCIIC1_SDA = 2U,
PORTD_8_FCSPI2_PCS2 = 4U,
PORTD_8_OSPI_DQS_RWDS  = 5U,
PORTD_8_FTU1_CH4 = 6U,
PORTD_8_FCUART4_RX = 7U,
} PORT_D8MuxType;

/** @brief PORTD9 Mode enumeration */
typedef enum
{
PORTD_9_GPIO = 1U,
PORTD_9_FCIIC1_SCL = 2U,
PORTD_9_OSPI_A_SCK  = 3U,
PORTD_9_FCSPI2_PCS1 = 4U,
PORTD_9_FTU1_CH5 = 6U,
PORTD_9_FCUART3_RX = 7U,
} PORT_D9MuxType;

/** @brief PORTE0 Mode enumeration */
typedef enum
{
PORTE_0_GPIO = 1U,
PORTE_0_FCSPI0_SCK = 2U,
PORTE_0_FTU_TCK1 = 3U,
PORTE_0_FCIIC1_SDA = 4U,
PORTE_0_FCUART0_CTS = 5U,
PORTE_0_FTU_FLT19 = 6U,
} PORT_E0MuxType;

/** @brief PORTE1 Mode enumeration */
typedef enum
{
PORTE_1_GPIO = 1U,
PORTE_1_FCSPI0_SIN = 2U,
PORTE_1_FCIIC1_SCL = 4U,
PORTE_1_FCUART0_RTS = 5U,
PORTE_1_FTU_FLT18 = 6U,
} PORT_E1MuxType;

/** @brief PORTE10 Mode enumeration */
typedef enum
{
PORTE_10_ADC1_SE0 = 0U,
PORTE_10_GPIO = 1U,
PORTE_10_SCG_CLKOUT = 2U,
PORTE_10_FCSPI2_PCS1 = 3U,
PORTE_10_FTU2_CH4 = 4U,
PORTE_10_TRGSEL_OUT4 = 7U,
} PORT_E10MuxType;

/** @brief PORTE11 Mode enumeration */
typedef enum
{
PORTE_11_ADC1_SE4 = 0U,
PORTE_11_GPIO = 1U,
PORTE_11_FCSPI2_PCS0 = 2U,
PORTE_11_AONTIMER0_CLK1 = 3U,
PORTE_11_FTU2_CH5 = 4U,
PORTE_11_TRGSEL_OUT5 = 7U,
} PORT_E11MuxType;

/** @brief PORTE12 Mode enumeration */
typedef enum
{
PORTE_12_ADC0_SE6 = 0U,
PORTE_12_GPIO = 1U,
PORTE_12_FCUART2_TX = 3U,
PORTE_12_FTU_FLT2 = 4U,
PORTE_12_CMP0_OUT = 7U,
} PORT_E12MuxType;

/** @brief PORTE13 Mode enumeration */
typedef enum
{
PORTE_13_ADC0_SE5 = 0U,
PORTE_13_GPIO = 1U,
PORTE_13_FTU4_CH5 = 2U,
PORTE_13_FCSPI2_PCS2 = 3U,
} PORT_E13MuxType;

/** @brief PORTE14 Mode enumeration */
typedef enum
{
PORTE_14_OSC32K_XTAL = 0U,
PORTE_14_GPIO = 1U,
PORTE_14_FTU2_CH7 = 2U,
PORTE_14_FTU_FLT0 = 4U,
PORTE_14_FLEXCAN0_RX = 5U,
PORTE_14_AONTIMER0_CLK1 = 6U,
} PORT_E14MuxType;

/** @brief PORTE15 Mode enumeration */
typedef enum
{
PORTE_15_ADC1_SE2 = 0U,
PORTE_15_GPIO = 1U,
PORTE_15_FCUART1_CTS = 2U,
PORTE_15_FCSPI2_SCK = 3U,
PORTE_15_FTU2_CH6 = 4U,
PORTE_15_TRGSEL_OUT6 = 7U,
} PORT_E15MuxType;

/** @brief PORTE16 Mode enumeration */
typedef enum
{
PORTE_16_ADC1_SE6 = 0U,
PORTE_16_GPIO = 1U,
PORTE_16_FCUART1_RTS = 2U,
PORTE_16_FCSPI2_SIN = 3U,
PORTE_16_FTU2_CH7 = 4U,
PORTE_16_TRGSEL_OUT7 = 7U,
} PORT_E16MuxType;

/** @brief PORTE19 Mode enumeration */
typedef enum
{
PORTE_19_ADC0_SE18 = 0U,
PORTE_19_GPIO = 1U,
PORTE_19_SCG_CLKOUT = 2U,
PORTE_19_FCIIC0_SCL = 3U,
} PORT_E19MuxType;

/** @brief PORTE2 Mode enumeration */
typedef enum
{
PORTE_2_ADC0_SE19 = 0U,
PORTE_2_GPIO = 1U,
PORTE_2_AONTIMER0_CLK3 = 3U,
PORTE_2_FTU3_CH6 = 4U,
PORTE_2_FCUART1_CTS = 6U,
} PORT_E2MuxType;

/** @brief PORTE20 Mode enumeration */
typedef enum
{
PORTE_20_ADC0_SE17 = 0U,
PORTE_20_GPIO = 1U,
PORTE_20_FTU4_CH0 = 2U,
PORTE_20_FCIIC0_SDA = 3U,
} PORT_E20MuxType;

/** @brief PORTE21 Mode enumeration */
typedef enum
{
PORTE_21_ADC0_SE16 = 0U,
PORTE_21_GPIO = 1U,
PORTE_21_FTU4_CH1 = 2U,
PORTE_21_AONTIMER0_CLK3 = 3U,
PORTE_21_FLEXCAN0_TX = 4U,
PORTE_21_FCUART0_RTS = 5U,
} PORT_E21MuxType;

/** @brief PORTE22 Mode enumeration */
typedef enum
{
PORTE_22_GPIO = 1U,
PORTE_22_FTU4_CH2 = 2U,
PORTE_22_FLEXCAN0_RX = 4U,
PORTE_22_FCUART0_CTS = 5U,
} PORT_E22MuxType;

/** @brief PORTE23 Mode enumeration */
typedef enum
{
PORTE_23_GPIO = 1U,
PORTE_23_FTU4_CH3 = 2U,
PORTE_23_FCSPI0_PCS3 = 5U,
} PORT_E23MuxType;

/** @brief PORTE24 Mode enumeration */
typedef enum
{
PORTE_24_GPIO = 1U,
PORTE_24_FTU4_CH4 = 2U,
PORTE_24_FLEXCAN2_TX = 3U,
PORTE_24_FCSPI0_PCS2 = 5U,
} PORT_E24MuxType;

/** @brief PORTE25 Mode enumeration */
typedef enum
{
PORTE_25_GPIO = 1U,
PORTE_25_FTU4_CH5 = 2U,
PORTE_25_FLEXCAN2_RX = 3U,
PORTE_25_FCSPI0_PCS1 = 5U,
} PORT_E25MuxType;

/** @brief PORTE3 Mode enumeration */
typedef enum
{
PORTE_3_OSC32K_EXTAL = 0U,
PORTE_3_GPIO = 1U,
PORTE_3_FTU2_CH6 = 2U,
PORTE_3_FCUART2_RX = 3U,
PORTE_3_FTU_FLT1 = 4U,
PORTE_3_FTU_TCK0 = 6U,
PORTE_3_FWM_IN = 7U,
} PORT_E3MuxType;

/** @brief PORTE4 Mode enumeration */
typedef enum
{
PORTE_4_ADC0_SE4 = 0U,
PORTE_4_GPIO = 1U,
PORTE_4_ETM_TRACE_D1 = 2U,
PORTE_4_FTU2_QD_PHB = 3U,
PORTE_4_FTU2_CH2 = 4U,
PORTE_4_FCSPI1_PCS0 = 5U,
PORTE_4_FWM_OUT_b = 7U,
} PORT_E4MuxType;

/** @brief PORTE5 Mode enumeration */
typedef enum
{
PORTE_5_ADC0_SE1 = 0U,
PORTE_5_GPIO = 1U,
PORTE_5_FTU_TCK2 = 2U,
PORTE_5_FTU2_QD_PHA = 3U,
PORTE_5_FTU2_CH3 = 4U,
PORTE_5_FCSPI1_SOUT = 5U,
PORTE_5_FWM_IN = 7U,
} PORT_E5MuxType;

/** @brief PORTE6 Mode enumeration */
typedef enum
{
PORTE_6_ADC0_SE20 = 0U,
PORTE_6_GPIO = 1U,
PORTE_6_FTU3_CH7 = 4U,
PORTE_6_FCUART1_RTS = 6U,
} PORT_E6MuxType;

/** @brief PORTE7 Mode enumeration */
typedef enum
{
PORTE_7_ADC1_SE9 = 0U,
PORTE_7_GPIO = 1U,
PORTE_7_FTU0_CH7 = 2U,
PORTE_7_FTU_FLT14 = 3U,
PORTE_7_TRGSEL_OUT3 = 5U,
} PORT_E7MuxType;

/** @brief PORTE8 Mode enumeration */
typedef enum
{
PORTE_8_GPIO = 1U,
PORTE_8_FTU0_CH6 = 2U,
PORTE_8_FCSPI0_SCK = 3U,
} PORT_E8MuxType;

/** @brief PORTE9 Mode enumeration */
typedef enum
{
PORTE_9_ADC0_SE12_CMP0_IN2 = 0U,
PORTE_9_GPIO = 1U,
PORTE_9_FTU0_CH7 = 2U,
PORTE_9_FCUART2_CTS = 3U,
PORTE_9_FCSPI0_PCS0 = 4U,
PORTE_9_ETM_TRACE_CLKOUT = 7U,
} PORT_E9MuxType;

#endif
