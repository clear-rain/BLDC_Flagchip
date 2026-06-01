/*
 * BspWdg.h
 *
 *  Created on: 2024年11月21日
 *      Author: 14013
 */

#ifndef BSW_MCAL_BSP_INC_BSPWDG_H_
#define BSW_MCAL_BSP_INC_BSPWDG_H_

#include "main.h"


void Bsp_WDOG_Init(void);
void Bsp_WDOG_DeInit(void);
void Bsp_WDOG_Refresh(void);
extern uint8 Wdg_cnt;


#endif /* BSW_MCAL_BSP_INC_BSPWDG_H_ */
