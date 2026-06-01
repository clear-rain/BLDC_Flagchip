/**
 * @file BspGpio.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */

#ifndef INCLUDE_EVB_PORT_H_
#define INCLUDE_EVB_PORT_H_


#include "main.h"

typedef enum{
	 DIO_STD_LOW = 0,
	 DIO_STD_HIGH
}Dio_LevelType;


typedef struct{
	PORT_InstanceType tPortOutBuff;
	uint32_t tPinOutBuff;
	Dio_LevelType tLevelOutBuff;
}OutPinconfig;
/******************  Out port start  *******************/
#ifndef ECU_ADDRESS_BLDC
#define PORT_OUT_NUM	3

#define EN_LDO_PORT							PORT_E
#define EN_LDO_PIN							PORT_PIN_6

#define VBAT_HALL_CTRL_PORT					PORT_C
#define VBAT_HALL_CTRL_PIN					PORT_PIN_3

#define DRV_EN_PORT							PORT_E
#define DRV_EN_PIN							PORT_PIN_7

/******************  Out port end   *******************/


/******************  In port start  *******************/
#define PORT_IN_NUM	7

#define INTN_PORT                       	PORT_D
#define INTN_PIN                 			PORT_PIN_5

#define IO_LHALLA_PORT                  	PORT_C
#define IO_LHALLA_PIN            			PORT_PIN_5

#define IO_LHALLB_PORT                  	PORT_A
#define IO_LHALLB_PIN            			PORT_PIN_14

#define KEYA_PORT                          	PORT_E
#define KEYA_PIN                    		PORT_PIN_0

#define KEYB_PORT                          	PORT_A
#define KEYB_PIN                    		PORT_PIN_11

#define INT_IAM_20680_PORT             		PORT_A
#define INT_IAM_20680_PIN       			PORT_PIN_10

#define INT2_IAM_20680_PORT             	PORT_E
#define INT2_IAM_20680_PIN       			PORT_PIN_1


/******************  In port end   *******************/

/****************** ADC Pin define start ******************/
#define ADC_CHANNEL_NUM 6

#define ADC_CSO1_PORT				(PORT_B)
#define ADC_CSO1_PIN				(PORT_PIN_0)
#define ADC_CSO1_PIN_MODE			(PORTB_0_ADC1_SE12)

#define ADC_Vbat_HALL_PORT			(PORT_C)
#define ADC_Vbat_HALL_PIN           (PORT_PIN_13)
#define ADC_Vbat_HALL_PIN_MODE      (PORTC_13_ADC1_SE15)

#define ADC_K30_PORT				(PORT_D)
#define ADC_K30_PIN                 (PORT_PIN_16)
#define ADC_K30_PIN_MODE            (PORTD_16_ADC0_SE10)

#define ADC_TEMP_PORT				(PORT_B)
#define ADC_TEMP_PIN                (PORT_PIN_1)
#define ADC_TEMP_PIN_MODE           (PORTB_1_ADC1_SE13)

#define ADC_MOTOR_NEGATIVE_PORT		(PORT_C)
#define ADC_MOTOR_NEGATIVE_PIN      (PORT_PIN_7)
#define ADC_MOTOR_NEGATIVE_PIN_MODE (PORTC_7_ADC1_SE24)

#define ADC_MOTOR_POSITIVE_PORT		(PORT_C)
#define ADC_MOTOR_POSITIVE_PIN      (PORT_PIN_6)
#define ADC_MOTOR_POSITIVE_PIN_MODE (PORTC_6_ADC0_SE23)


/****************** ADC Pin define end ********************/

/****************** SPI Pin define start ********************/
#define SPI0_CS_PORT  (PORT_E)
#define SPI0_CS_PIN  (PORT_PIN_9)
#define SPI0_CS_PIN_MODE (PORTE_9_FCSPI0_PCS0)
#define SPI0_CS_WHICH_PIN (FCSPI_PCS_0)
#define SPI1_CS_PORT  (PORT_A)
#define SPI1_CS_PIN  (PORT_PIN_6)
#define SPI1_CS_PIN_MODE (PORTA_6_FCSPI1_PCS1)
#define SPI1_CS_WHICH_PIN (FCSPI_PCS_1)
#define SPI2_CS_PORT  0//(PORT_C)
#define SPI2_CS_PIN  0//(PORT_PIN_14)
#define SPI2_CS_PIN_MODE 0//(PORTC_14_FCSPI2_PCS0)
#define SPI2_CS_WHICH_PIN 0//(FCSPI_PCS_0)
#define SPI3_CS_PORT  0//(PORT_D)
#define SPI3_CS_PIN  0//(PORT_PIN_11)
#define SPI3_CS_PIN_MODE 0//(PORTD_11_FCSPI3_PCS0)
#define SPI3_CS_WHICH_PIN 0//(FCSPI_PCS_0)

#define SPI0_SCK_PORT  (PORT_D)
#define SPI0_SCK_PIN  (PORT_PIN_15)
#define SPI0_SCK_PIN_MODE  (PORTD_15_FCSPI0_SCK)
#define SPI1_SCK_PORT  (PORT_A)
#define SPI1_SCK_PIN  (PORT_PIN_7)
#define SPI1_SCK_PIN_MODE  (PORTA_7_FCSPI1_SCK)
#define SPI2_SCK_PORT  0//(PORT_C)
#define SPI2_SCK_PIN  0//(PORT_PIN_15)
#define SPI2_SCK_PIN_MODE  0//(PORTC_15_FCSPI2_SCK)
#define SPI3_SCK_PORT  0//(PORT_D)
#define SPI3_SCK_PIN  0//(PORT_PIN_6)
#define SPI3_SCK_PIN_MODE  0//(PORTD_6_FCSPI3_SCK)

#define SPI0_MOSI_PORT  (PORT_B)
#define SPI0_MOSI_PIN  (PORT_PIN_4)
#define SPI0_MOSI_PIN_MODE  (PORTB_4_FCSPI0_SOUT)
#define SPI1_MOSI_PORT  (PORT_C)
#define SPI1_MOSI_PIN  (PORT_PIN_9)
#define SPI1_MOSI_PIN_MODE  (PORTC_9_FCSPI1_SOUT)
#define SPI2_MOSI_PORT  0//(PORT_C)
#define SPI2_MOSI_PIN  0//(PORT_PIN_1)
#define SPI2_MOSI_PIN_MODE  0//(PORTC_1_FCSPI2_SOUT)
#define SPI3_MOSI_PORT  0//(PORT_D)
#define SPI3_MOSI_PIN  0//(PORT_PIN_12)
#define SPI3_MOSI_PIN_MODE  0//(PORTD_12_FCSPI3_SOUT)

#define SPI0_MISO_PORT  (PORT_D)
#define SPI0_MISO_PIN  (PORT_PIN_7)
#define SPI0_MISO_PIN_MODE  (PORTD_7_FCSPI0_SIN)
#define SPI1_MISO_PORT  (PORT_C)
#define SPI1_MISO_PIN  (PORT_PIN_8)
#define SPI1_MISO_PIN_MODE  (PORTC_8_FCSPI1_SIN)
#define SPI2_MISO_PORT  0//(PORT_C)
#define SPI2_MISO_PIN  0//(PORT_PIN_16)
#define SPI2_MISO_PIN_MODE  0//(PORTC_16_FCSPI2_SIN)
#define SPI3_MISO_PORT  0//(PORT_D)
#define SPI3_MISO_PIN  0//(PORT_PIN_5)
#define SPI3_MISO_PIN_MODE  0//(PORTD_5_FCSPI3_SIN)
/****************** SPI Pin define end ********************/

/****************** CAN Pin define start ********************/
#define FC_PROJECT_CAN_NUM  1U

#define CAN1_RX_PORT  (PORT_A)
#define CAN1_RX_PIN  (PORT_PIN_12)
#define CAN1_RX_PIN_MODE  (PORTA_12_FLEXCAN1_RX)
#define CAN1_TX_PORT  (PORT_A)
#define CAN1_TX_PIN  (PORT_PIN_13)
#define CAN1_TX_PIN_MODE  (PORTA_13_FLEXCAN1_TX)



/****************** SPI Pin define end 	 ********************/

/****************** IIC Pin define Start ********************/
#define FC_PROJECT_IIC_NUMBER FCIIC_INSTANCE_COUNT

#define SDA1_IAM_20680_PORT		PORT_A
#define SDA1_IAM_20680_PIN		PORT_PIN_2
#define SDA1_IAM_20680_PIN_MODE (PORTA_2_FCIIC0_SDA)

#define SCL1_IAM_20680_PORT		PORT_A
#define SCL1_IAM_20680_PIN		PORT_PIN_3
#define SCL1_IAM_20680_PIN_MODE (PORTA_3_FCIIC0_SCL)

#define IIC1_SDA_PORT		0//PORT_B
#define IIC1_SDA_PIN		0//PORT_PIN_4
#define IIC1_SDA_PIN_MODE  0//(PORTB_4_FCIIC1_SDA)

#define IIC1_SCL_PORT		0//PORT_B
#define IIC1_SCL_PIN		0//PORT_PIN_5
#define IIC1_SCL_PIN_MODE  0//(PORTB_5_FCIIC1_SCL)

/****************** IIC Pin define end 	 ********************/

/****************** FTU PWM Pin Define Start *************/
#define PWM_CHANNEL_NUM_MAX	3U

#define PWM1_PORT		PORT_B
#define PWM1_PIN		PORT_PIN_12
#define PWM1_PIN_MODE	PORTB_12_FTU0_CH0

#define PWM2_PORT		PORT_B
#define PWM2_PIN		PORT_PIN_13
#define PWM2_PIN_MODE	PORTB_13_FTU0_CH1

#define PWM3_PORT		PORT_B
#define PWM3_PIN		PORT_PIN_10
#define PWM3_PIN_MODE	PORTB_10_FTU3_CH2

/****************** FTU PWM Pin Define End ***************/

/* CAN */
#define FLEXCAN_USED_INSTANCE0      STD_OFF
#define FLEXCAN_USED_INSTANCE1      STD_ON
#define FLEXCAN_USED_INSTANCE2      STD_OFF
#define FLEXCAN_USED_INSTANCE4      STD_OFF
#define FLEXCAN_USED_INSTANCE5      STD_OFF
#define FLEXCAN_USED_INSTANCE6      STD_OFF

extern void Bsp_GpioOutInit(void);

extern void Bsp_GpioInInit(void);

extern uint8_t FCSpiGpioInit(uint8_t u8_spiIdx);

extern uint8_t FCAdcGpioInit(void);

extern void FCFtuPwmGpioInit(uint8_t u8_ChannelIdx);

extern void FCCanGpioInit(void);

extern void FCIicGpioInit(uint8_t u8_IicIdx);

void ExternalInterruptPortPinInit(void);
void Wakeup_gpio_external_interrupt_Config(void);

#else
#define PORT_OUT_NUM	10

#define ENC_PDRV_PORT						PORT_E
#define ENC_PDRV_PIN						PORT_PIN_9

#define ENB_PDRV_PORT						PORT_B
#define ENB_PDRV_PIN						PORT_PIN_5

#define ENA_PDRV_PORT						PORT_C
#define ENA_PDRV_PIN						PORT_PIN_3

#define VBAT_HALL_CTRL_PORT					PORT_D
#define VBAT_HALL_CTRL_PIN					PORT_PIN_7

#define HSD_DIAG_EN_PORT					PORT_D
#define HSD_DIAG_EN_PIN				    	PORT_PIN_6

#define HSD_2CH_DSEL_PORT					PORT_D
#define HSD_2CH_DSEL_PIN				    PORT_PIN_5

#define NSLEEP_PDRV_PORT					PORT_D
#define NSLEEP_PDRV_PIN				    	PORT_PIN_9

#define VBAT_ENCODER_CTRL_PORT				PORT_C
#define VBAT_ENCODER_CTRL_PIN				PORT_PIN_17

#define EN_LDO_PORT							PORT_A
#define EN_LDO_PIN							PORT_PIN_1

#define CAN2_STB_PORT						PORT_C
#define CAN2_STB_PIN						PORT_PIN_6



/******************  In port start  *******************/
#define PORT_IN_NUM	10

#define NFAULT_PDRV_PORT                    PORT_E
#define NFAULT_PDRV_PIN                 	PORT_PIN_3

#define IO_HALL_V_PORT                  	PORT_D
#define IO_HALL_V_PIN            			PORT_PIN_3

#define IO_HALL_U_PORT                  	PORT_B
#define IO_HALL_U_PIN            			PORT_PIN_10

#define IO_HALL_W_PORT                      PORT_E
#define IO_HALL_W_PIN                       PORT_PIN_6

#define INTN_WPS_PORT                       PORT_A
#define INTN_WPS_PIN                    	PORT_PIN_14

#define IO_KEY_B_WPS_PORT             		PORT_A
#define IO_KEY_B_WPS_PIN       				PORT_PIN_11

#define INT1_IAM_8961_WPS_PORT             	PORT_A
#define INT1_IAM_8961_WPS_PIN       		PORT_PIN_10

#define IO_HALL_WPS_PORT                    PORT_E
#define IO_HALL_WPS_PIN                    	PORT_PIN_1

#define IO_KEY_A_WPS_PORT             		PORT_E
#define IO_KEY_A_WPS_PIN       				PORT_PIN_0

#define IO_KEY_C_WPS_PORT             		PORT_C
#define IO_KEY_C_WPS_PIN       				PORT_PIN_5

/******************  In port end   *******************/

/****************** ADC Pin define start ******************/
#define ADC_CHANNEL_NUM 10

#define ADC_CS_V_PORT				(PORT_D)
#define ADC_CS_V_PIN				(PORT_PIN_1)
#define ADC_CS_V_PIN_MODE			(PORTD_1_ADC1_SE5)

#define ADC_CS_U_PORT				(PORT_D)
#define ADC_CS_U_PIN           		(PORT_PIN_0)
#define ADC_CS_U_PIN_MODE      		(PORTD_0_ADC1_SE1)

#define ADC_DIAG_W_PORT				(PORT_E)
#define ADC_DIAG_W_PIN              (PORT_PIN_5)
#define ADC_DIAG_W_PIN_MODE         (PORTE_5_ADC0_SE1)

#define ADC_DIAG_V_PORT				(PORT_E)
#define ADC_DIAG_V_PIN              (PORT_PIN_4)
#define ADC_DIAG_V_PIN_MODE         (PORTE_4_ADC0_SE4)

#define ADC_CSO_PORT				(PORT_D)
#define ADC_CSO_PIN      			(PORT_PIN_16)
#define ADC_CSO_PIN_MODE 			(PORTD_16_ADC0_SE10)

#define ADC_K30_PORT				(PORT_C)
#define ADC_K30_PIN      			(PORT_PIN_13)
#define ADC_K30_PIN_MODE 			(PORTC_13_ADC1_SE15)

#define ENCODER_CURRENT_PORT		(PORT_E)
#define ENCODER_CURRENT_PIN         (PORT_PIN_7)
#define ENCODER_CURRENT_PIN_MODE    (PORTE_7_ADC1_SE9)

#define ADC_TEMP_PORT				(PORT_D)
#define ADC_TEMP_PIN              	(PORT_PIN_2)
#define ADC_TEMP_PIN_MODE         	(PORTD_2_ADC0_SE24)

#define ADC_KEY_A_DIAG_PORT			(PORT_B)
#define ADC_KEY_A_DIAG_PIN      	(PORT_PIN_8)
#define ADC_KEY_A_DIAG_PIN_MODE 	(PORTB_8_ADC0_SE29_ADC1_SE29)

#define ADC_KEY_B_DIAG_PORT			(PORT_C)
#define ADC_KEY_B_DIAG_PIN      	(PORT_PIN_7)
#define ADC_KEY_B_DIAG_PIN_MODE 	(PORTC_7_ADC1_SE24)

/****************** ADC Pin define end ********************/

/****************** SPI Pin define start ********************/
#define SPI0_CS_PORT  (PORT_B)
#define SPI0_CS_PIN  (PORT_PIN_0)
#define SPI0_CS_PIN_MODE (PORTB_0_FCSPI0_PCS0)
#define SPI0_CS_WHICH_PIN (FCSPI_PCS_0)
#define SPI1_CS_PORT  (PORT_A)
#define SPI1_CS_PIN  (PORT_PIN_6)
#define SPI1_CS_PIN_MODE (PORTA_6_FCSPI1_PCS1)
#define SPI1_CS_WHICH_PIN (FCSPI_PCS_1)
#define SPI2_CS_PORT  (PORT_C)
#define SPI2_CS_PIN  (PORT_PIN_14)
#define SPI2_CS_PIN_MODE (PORTC_14_FCSPI2_PCS0)
#define SPI2_CS_WHICH_PIN (FCSPI_PCS_0)
#define SPI3_CS_PORT  0//(PORT_D)
#define SPI3_CS_PIN  0//(PORT_PIN_11)
#define SPI3_CS_PIN_MODE 0//(PORTD_11_FCSPI3_PCS0)
#define SPI3_CS_WHICH_PIN 0//(FCSPI_PCS_0)

#define SPI0_SCK_PORT  (PORT_D)
#define SPI0_SCK_PIN  (PORT_PIN_15)
#define SPI0_SCK_PIN_MODE  (PORTD_15_FCSPI0_SCK)
#define SPI1_SCK_PORT  (PORT_A)
#define SPI1_SCK_PIN  (PORT_PIN_7)
#define SPI1_SCK_PIN_MODE  (PORTA_7_FCSPI1_SCK)
#define SPI2_SCK_PORT  (PORT_C)
#define SPI2_SCK_PIN  (PORT_PIN_15)
#define SPI2_SCK_PIN_MODE  (PORTC_15_FCSPI2_SCK)
#define SPI3_SCK_PORT  0//(PORT_D)
#define SPI3_SCK_PIN  0//(PORT_PIN_6)
#define SPI3_SCK_PIN_MODE  0//(PORTD_6_FCSPI3_SCK)

#define SPI0_MOSI_PORT  (PORT_B)
#define SPI0_MOSI_PIN  (PORT_PIN_1)
#define SPI0_MOSI_PIN_MODE  (PORTB_1_FCSPI0_SOUT)
#define SPI1_MOSI_PORT  (PORT_C)
#define SPI1_MOSI_PIN  (PORT_PIN_9)
#define SPI1_MOSI_PIN_MODE  (PORTC_9_FCSPI1_SOUT)
#define SPI2_MOSI_PORT  (PORT_C)
#define SPI2_MOSI_PIN  (PORT_PIN_1)
#define SPI2_MOSI_PIN_MODE  (PORTC_1_FCSPI2_SOUT)
#define SPI3_MOSI_PORT  0//(PORT_D)
#define SPI3_MOSI_PIN  0//(PORT_PIN_12)
#define SPI3_MOSI_PIN_MODE  0//(PORTD_12_FCSPI3_SOUT)

#define SPI0_MISO_PORT  (PORT_B)
#define SPI0_MISO_PIN  (PORT_PIN_3)
#define SPI0_MISO_PIN_MODE  (PORTB_3_FCSPI0_SIN)
#define SPI1_MISO_PORT  (PORT_C)
#define SPI1_MISO_PIN  (PORT_PIN_8)
#define SPI1_MISO_PIN_MODE  (PORTC_8_FCSPI1_SIN)
#define SPI2_MISO_PORT  (PORT_C)
#define SPI2_MISO_PIN  (PORT_PIN_16)
#define SPI2_MISO_PIN_MODE  (PORTC_16_FCSPI2_SIN)
#define SPI3_MISO_PORT  0//(PORT_D)
#define SPI3_MISO_PIN  0//(PORT_PIN_5)
#define SPI3_MISO_PIN_MODE  0//(PORTD_5_FCSPI3_SIN)
/****************** SPI Pin define end ********************/

/****************** CAN Pin define start ********************/
#define FC_PROJECT_CAN_NUM  2U

#define CAN1_RX_PORT  (PORT_B)
#define CAN1_RX_PIN  (PORT_PIN_12)
#define CAN1_RX_PIN_MODE  (PORTB_12_FLEXCAN2_RX)
#define CAN1_TX_PORT  (PORT_B)
#define CAN1_TX_PIN  (PORT_PIN_13)
#define CAN1_TX_PIN_MODE  (PORTB_13_FLEXCAN2_TX)

#define CAN2_RX_PORT  (PORT_A)
#define CAN2_RX_PIN  (PORT_PIN_12)
#define CAN2_RX_PIN_MODE  (PORTA_12_FLEXCAN1_RX)
#define CAN2_TX_PORT  (PORT_A)
#define CAN2_TX_PIN  (PORT_PIN_13)
#define CAN2_TX_PIN_MODE  (PORTA_13_FLEXCAN1_TX)
/****************** CAN Pin define END ********************/

/****************** FTU PWM Pin Define Start *************/
#define PWM_CHANNEL_NUM_MAX	3U

#define PWM_INA_PORT		PORT_C
#define PWM_INA_PIN			PORT_PIN_2
#define PWM_INA_PIN_MODE	PORTC_2_FTU0_CH2

#define PWM_INB_PORT		PORT_B
#define PWM_INB_PIN			PORT_PIN_4
#define PWM_INB_PIN_MODE	PORTB_4_FTU0_CH4

#define PWM_INC_PORT		PORT_E
#define PWM_INC_PIN			PORT_PIN_8
#define PWM_INC_PIN_MODE	PORTE_8_FTU0_CH6

/****************** FTU PWM Pin Define End ***************/

/* CAN */
#define FLEXCAN_USED_INSTANCE0      STD_OFF
#define FLEXCAN_USED_INSTANCE1      STD_ON
#define FLEXCAN_USED_INSTANCE2      STD_ON
#define FLEXCAN_USED_INSTANCE4      STD_OFF
#define FLEXCAN_USED_INSTANCE5      STD_OFF
#define FLEXCAN_USED_INSTANCE6      STD_OFF


extern void Bsp_GpioOutInit(void);

extern void Bsp_GpioInInit(void);

extern uint8_t FCSpiGpioInit(uint8_t u8_spiIdx);

extern uint8_t FCAdcGpioInit(void);

extern void FCFtuPwmGpioInit(uint8_t u8_ChannelIdx);

extern void FCCanGpioInit(void);

//extern void FCIicGpioInit(uint8_t u8_IicIdx);

//void ExternalInterruptPortPinInit(void);
//void Wakeup_gpio_external_interrupt_Config(void);
#endif /*ECU_ADDRESS_BLDC*/

#endif /* INCLUDE_EVB_PORT_H_ */
