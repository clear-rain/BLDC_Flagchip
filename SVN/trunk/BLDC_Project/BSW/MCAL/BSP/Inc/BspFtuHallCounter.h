/*
 * BspFtuHallCounter.h
 *
 *  Created on: 2026年3月9日
 */

#ifndef BSW_MCAL_BSP_INC_BSPFTUHALLCOUNTER_H_
#define BSW_MCAL_BSP_INC_BSPFTUHALLCOUNTER_H_

#include "BspFtuCounter.h"

/* FTUx 在当前 PCC 属性下不支持模块级 DIV 分频，功能时钟直接取 FOSCDIVH。 */
#define BSP_FTU2_COUNTER_SOURCE_CLOCK_HZ ((uint32_t)16000000u)
#define BSP_FTU2_COUNTER_PRESCALER_DIV ((uint32_t)32u)
#define BSP_FTU2_COUNTER_TICK_HZ (BSP_FTU2_COUNTER_SOURCE_CLOCK_HZ / BSP_FTU2_COUNTER_PRESCALER_DIV)
#define BSP_FTU2_COUNTER_PERIOD_MS ((uint32_t)100u)
#define BSP_FTU2_COUNTER_PERIOD_TICKS ((uint32_t)((BSP_FTU2_COUNTER_TICK_HZ / 1000u) * BSP_FTU2_COUNTER_PERIOD_MS))

struct FtuCounterDriverIf_t * BSP_HallCounterGetDevice(char *name);
void Bsp_FtuHallCounter_DeInit(void);
uint8_t Bsp_Ftu2_GetOverflowFlag(void);
uint8_t Bsp_Ftu2_GetOverflowCount(void);
void Bsp_Ftu2_ClearOverflowFlag(void);

#endif /* BSW_MCAL_BSP_INC_BSPFTUHALLCOUNTER_H_ */