/*
 * BspSmc.h
 *
 *  Created on: 2024年12月6日
 *      Author: 14013
 */

#ifndef BSW_MCAL_BSP_INC_BSPSMC_H_
#define BSW_MCAL_BSP_INC_BSPSMC_H_

#include "main.h"


void Bsp_SmcEnterStop(void);
void Bsp_SmcEnterWait(void);
void Bsp_SmcEnterStandby0(void);
void Bsp_SmcEnterStandby1(void);
void Bsp_SmcEnterStandby2(void);
void Bsp_SmcEnterStandby3(void);
void Bsp_SetWakeupSource(void);



#endif /* BSW_MCAL_BSP_INC_BSPSMC_H_ */
