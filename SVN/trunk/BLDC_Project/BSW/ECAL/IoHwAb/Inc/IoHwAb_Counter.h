/*
 * IoHwAb_Counter.h
 *
 *  Created on: 2024年11月20日
 *      Author: 14013
 */

#ifndef BSW_ECAL_IOHWAB_INC_IOHWAB_COUNTER_H_
#define BSW_ECAL_IOHWAB_INC_IOHWAB_COUNTER_H_

#include "BspFtuCounter.h"

#include "typedef.h"

extern void IoHwAb_Counter_Init(void);
extern void IoHwAb_Counter_Start(void);
extern void IoHwAb_Counter_Stop(void);
extern uint32_t IoHwAb_Counter_GetCnt(void);
extern void IoHwAb_Counter_Clear(void);


#endif /* BSW_ECAL_IOHWAB_INC_IOHWAB_COUNTER_H_ */
