/*
 * IoHwAb_HallCounter.h
 *
 *  Created on: 2026年3月9日
 */

#ifndef BSW_ECAL_IOHWAB_INC_IOHWAB_HALLCOUNTER_H_
#define BSW_ECAL_IOHWAB_INC_IOHWAB_HALLCOUNTER_H_

#include "BspFtuHallCounter.h"
#include "typedef.h"

#define HALL_COUNTER_SECONDS_PER_TICK (float)(1.0f / (float)BSP_FTU2_COUNTER_TICK_HZ)

extern void IoHwAb_HallCounter_Init(void);
extern void IoHwAb_HallCounter_Start(void);
extern void IoHwAb_HallCounter_Stop(void);
extern uint32_t IoHwAb_HallCounter_GetCnt(void);
extern void IoHwAb_HallCounter_Clear(void);
extern uint8_t IoHwAb_HallCounter_GetOverflowFlag(void);
extern uint8_t IoHwAb_HallCounter_GetOverflowCount(void);
extern void IoHwAb_HallCounter_ClearOverflowFlag(void);

#endif /* BSW_ECAL_IOHWAB_INC_IOHWAB_HALLCOUNTER_H_ */