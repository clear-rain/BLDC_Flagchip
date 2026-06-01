/*
 * IoHwAb_Pwm.h
 *
 *  Created on: 2024年11月4日
 *      Author: 14013
 */

#ifndef BSW_ECAL_IOHWAB_INC_IOHWAB_PWM_H_
#define BSW_ECAL_IOHWAB_INC_IOHWAB_PWM_H_

#include "BspFtuPwm.h"

#include "typedef.h"

typedef enum{
	e_PWM_INA_IDX = 0u,
	e_PWM_INB_IDX,
	e_PWM_INC_IDX,
	e_PWM_NUM_MAX
}Pwm_ChannelType;


extern void Bsp_PWM_Init(void);
void Bsp_PWM_DutySet(uint8_t channel, uint16 duty);

#endif /* BSW_ECAL_IOHWAB_INC_IOHWAB_PWM_H_ */
