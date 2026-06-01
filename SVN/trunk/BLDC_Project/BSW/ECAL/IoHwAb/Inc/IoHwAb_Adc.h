/*
 * IoHwAb_Adc.h
 *
 *  Created on: 2024年11月1日
 *      Author: 14013
 */

#ifndef BSW_ECAL_IOHWAB_INC_IOHWAB_ADC_H_
#define BSW_ECAL_IOHWAB_INC_IOHWAB_ADC_H_

#include "BspAdc.h"

#define Adc0Channel_23_MOTOR_POSITIVE            (0x0U)
#define Adc0Channel_10_K30                       (0x1U)

#define Adc1Channel_12_CSO1                      (0x0U)
#define Adc1Channel_13_Temp                      (0x1U)
#define Adc1Channel_15_Vbat_Hall                 (0x2U)
#define Adc1Channel_24_MOTOR_NEGATIVE            (0x3U)



extern uint32_t g_aui32Adc0ConvBuf[ADC0_CHN_NUM_EN];
extern uint32_t g_aui32Adc1ConvBuf[ADC1_CHN_NUM_EN];
extern uint32_t g_aui32Adc0VoltBuf[ADC0_CHN_NUM_EN];
extern uint32_t g_aui32Adc1VoltBuf[ADC1_CHN_NUM_EN];


extern void Adc_Init(void);
extern void Adc_StartGroupConversion(uint8_t u8_groupId);
extern void IoHwAb_Adc_MainFunction(void );


uint32 CDD_GetBatmVolt(void);
void IoHwAb_Adc_BatmVoltTask(void);
sint32 CDD_GetPCBATempC(void);
void IoHwAb_Adc_PCBATempCTask(void);
uint32 CDD_GetHallVolt(void);
void IoHwAb_Adc_HallVoltTask(void);

#endif /* BSW_ECAL_IOHWAB_INC_IOHWAB_ADC_H_ */
