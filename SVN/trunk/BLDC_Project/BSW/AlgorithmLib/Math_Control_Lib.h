/*
 * Math_Control_Lib.h
 *
 *  Created on: 2021��8��19��
 *      Author: ThinkPad
 */

#ifndef APPLICATION_SOURCE_MATH_CONTROL_LIB_H_
#define APPLICATION_SOURCE_MATH_CONTROL_LIB_H_

# include "stdint-gcc.h"
#include "typedef.h"

uint8_t Delay_On(uint8_t CondiTrue, uint32_t DelayCycles, uint16_t* Counter);

uint8_t Delay_Off(uint8_t CondiTrue, uint16_t DelayCycles, uint16_t* Counter);

void Lib_Ramp(int16_t Input, int16_t *Output, int16_t UpStep, int16_t DownStep);

int16_t Lib_PI_Controller(int16_t Error, int16_t Kp, int16_t Ki, int16_t* int16_tegral, int16_t UpperLimit, int16_t LowerLimit);

int16_t Lib_Linear_2P_Interpo(int16_t Input, int16_t x1, int16_t x2, int16_t y1, int16_t y2);

int16_t Lib_Linear_3P_Interpo(int16_t Input, int16_t x1, int16_t x2, int16_t y1, int16_t y2, int16_t x3, int16_t y3);

int16_t Lib_Linear_4P_Interpo(int16_t Input, int16_t x1, int16_t x2, int16_t y1, int16_t y2, int16_t x3, int16_t y3, int16_t x4, int16_t y4);
// uint32 Lib_Linear_4P_Interpo(uint32 Input, uint32 x1, uint32 x2, uint32 x3, uint32 x4, uint32 y1, uint32 y2,  uint32 y3,  uint32 y4);

int32_t Lib_Linear_6P_Interpo(int32_t Input, int32_t x1, int32_t x2, int32_t x3, int32_t x4,  int32_t x5, int32_t x6, int32_t y1, int32_t y2,  int32_t y3,  int32_t y4,  int32_t y5,  int32_t y6);


void Lib_ResetValueInCycle(uint8_t *Value, uint16_t * Counter, uint16_t CycleThreshold);

uint8_t Filtered_Delay_On(uint8_t CondiTrue, uint16_t DelayCycles, uint16_t* DelayCounter, uint16_t FiltCycles, uint16_t* FiltCounter);

#define MACRO_MIN(a,b) ((a)<(b)?(a):(b))

#define MACRO_MAX(a,b) ((a)>(b)?(a):(b))

#define MACRO_ABS(a) ((a) > 0? (a):(-a))

#endif /* APPLICATION_SOURCE_MATH_CONTROL_LIB_H_ */
