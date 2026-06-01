/*
 * BspRtc.h
 *
 *  Created on: 2025年3月17日
 *      Author: 14013
 */

#ifndef BSW_MCAL_BSP_INC_BSPRTC_H_
#define BSW_MCAL_BSP_INC_BSPRTC_H_

#include "main.h"

extern RTC_HandleType g_tRtcHandle;
void Bsp_Rtc_Init(void);
void Bsp_RtcStart(void);

#endif /* BSW_MCAL_BSP_INC_BSPRTC_H_ */
