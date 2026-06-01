/*
 * Math_Control_Lib.c
 *
 *  Created on: 2021��8��19��
 *      Author: ThinkPad
 */


/*
 * Math_Control_Lib.c
 *
 *  Created on: 2020.04.28
 *      Author: Bu Fan
 */
# include "stdint-gcc.h"
#include "Math_Control_Lib.h"
//#include "XL6600.h"


uint8_t Delay_On(uint8_t CondiTrue, uint32_t DelayCycles, uint16_t* Counter)
{
	if(CondiTrue)
	{
		(*Counter)++;
	}
	else
	{
		*Counter = 0;
	}

	if(*Counter > 0xFFFE)
	{
		*Counter = 0xFFFE;
	}

	if(*Counter > DelayCycles)
	{
		return 1u;
	}
	else
	{
		return 0u;
	}
}

uint8_t Filtered_Delay_On(uint8_t CondiTrue, uint16_t DelayCycles, uint16_t* DelayCounter, uint16_t FiltCycles, uint16_t* FiltCounter)
{
	if(CondiTrue)
	{
		(*DelayCounter)++;
		if(*FiltCounter > 0)
		{
			*FiltCounter = 0;
		}
	}
	else
	{
		if((*DelayCounter) > 0)
		{/*Already counting, begin to count the filter;
		   Condition true and then false for shorter
		    than threshold	 */
			(*FiltCounter)++;
			(*DelayCounter)++;
		}
		else
		{/*condition false, reset everything*/
			*FiltCounter = 0;
			*DelayCounter = 0;
		}

		if((*FiltCounter) > FiltCycles)
		{/*Already counting, filter counter exceeds the threshold;
		   Condition true and then false for longer than threshold,
		   reset everything*/
			*FiltCounter = 0;
			*DelayCounter = 0;
		}
		else
		{
			/*Do nothing*/
		}
	}

	if(*DelayCounter > DelayCycles)
	{
		return 1u;
	}
	else
	{
		return 0u;
	}
}

uint8_t Delay_Off(uint8_t CondiTrue, uint16_t DelayCycles, uint16_t* Counter)
{
	if(CondiTrue)
	{
		*Counter = 0u;
		return 1u;
	}
	else
	{
		(*Counter)++;
	}

	if(*Counter < DelayCycles)
	{
		return 1u;
	}
	else
	{
		return 0u;
	}
}

void Lib_Ramp(int16_t Input, int16_t *Output, int16_t UpStep, int16_t DownStep)
{
	if(*Output > Input + DownStep)
	{
		*Output = (int16_t)(*Output - DownStep);
	}
	else if(*Output < Input - UpStep)
	{
		*Output = (int16_t)(*Output + UpStep);
	}
	else
	{

	}

}

int16_t Lib_PI_Controller(int16_t Error, int16_t KpPermillage, int16_t KiPermillage, int16_t* Integral, int16_t UpperLimit, int16_t LowerLimit)
{
	int16_t Output = 0;

	(* Integral) += (int16_t)(Error*KiPermillage/1000);

	if(* Integral > UpperLimit)
	{
		* Integral = UpperLimit;
	}
	else if(* Integral < LowerLimit)
	{
		* Integral = LowerLimit;
	}
	else
	{
		/*Valid value, keep it*/
	}

	Output = (int16_t)((* Integral) + KpPermillage*Error/1000);

	if(Output > UpperLimit)
	{
		Output = UpperLimit;
	}
	else if(Output < LowerLimit)
	{
		Output = LowerLimit;
	}
	else
	{
		/*keep the value*/
	}


	if(UpperLimit < LowerLimit)/*Invalid parameter input, return 0*/
	{
		Output = 0;
	}

	return Output;
}

int16_t Lib_Linear_2P_Interpo(int16_t Input, int16_t x1, int16_t x2, int16_t y1, int16_t y2)
{
	int16_t Output = 0;

	if(x1 < x2)
	{
		if(Input <= x1)
		{
			Output = y1;
		}
		else if(Input >= x2)
		{
			Output = y2;
		}
		else
		{
			Output =(int16_t)( y1 + (Input - x1)*(y2 - y1)/(x2 - x1));
		}
	}
	else
	{
		Output = 0;
	}

	return Output;
}

int16_t Lib_Linear_3P_Interpo(int16_t Input, int16_t x1, int16_t x2, int16_t x3, int16_t y1, int16_t y2, int16_t y3)
{
	int16_t Output = 0;

	if((x1 < x2)&&(x2 < x3))
	{
		if(Input <= x1)
		{
			Output = y1;
		}
		else if((Input > x1)&&(Input <= x2))
		{
			Output = (int16_t)(y1 + (Input - x1)*(y2 - y1)/(x2 - x1));
		}
		else if((Input > x2)&&(Input <= x3))
		{
			Output = (int16_t)(y2 + (Input - x2)*(y3 - y2)/(x3 - x2));
		}
		else
		{
			Output = y3;
		}
	}
	else
	{
		Output = 0;
	}

	return Output;
}


int16_t Lib_Linear_4P_Interpo(int16_t Input, int16_t x1, int16_t x2, int16_t x3, int16_t x4, int16_t y1, int16_t y2,  int16_t y3,  int16_t y4)
{
	int16_t Output = 0;

	if((x1 < x2)&&(x2 < x3)&&(x3 < x4))
	{
		if(Input <= x1)
		{
			Output = y1;
		}
		else if((Input > x1)&&(Input <= x2))
		{
			Output = y1 + (Input - x1)*(y2 - y1)/(x2 - x1);
		}
		else if((Input > x2)&&(Input <= x3))
		{
			Output = y2 + (Input - x2)*(y3 - y2)/(x3 - x2);
		}
		else if((Input > x3)&&(Input <= x4))
		{
			Output = y3 + (Input - x3)*(y4 - y3)/(x4 - x3);
		}
		else
		{
			Output = y4;
		}
	}
	else
	{
		Output = 0;/*Invalid parameter input*/
	}

	return Output;
}

// uint32 Lib_Linear_4P_Interpo(uint32 Input, uint32 x1, uint32 x2, uint32 x3, uint32 x4, uint32 y1, uint32 y2,  uint32 y3,  uint32 y4)
// {
// 	uint32 Output = 0;

// 	if((x1 < x2)&&(x2 < x3)&&(x3 < x4))
// 	{
// 		if(Input <= x1)
// 		{
// 			Output = y1;
// 		}
// 		else if((Input > x1)&&(Input <= x2))
// 		{
// 			Output = y1 + (Input - x1)*(y2 - y1)/(x2 - x1);
// 		}
// 		else if((Input > x2)&&(Input <= x3))
// 		{
// 			Output = y2 + (Input - x2)*(y3 - y2)/(x3 - x2);
// 		}
// 		else if((Input > x3)&&(Input <= x4))
// 		{
// 			Output = y3 + (Input - x3)*(y4 - y3)/(x4 - x3);
// 		}
// 		else
// 		{
// 			Output = y4;
// 		}
// 	}
// 	else
// 	{
// 		Output = 0;/*Invalid parameter input*/
// 	}

// 	return Output;
// }


int32_t Lib_Linear_6P_Interpo(int32_t Input, int32_t x1, int32_t x2, int32_t x3, int32_t x4,  int32_t x5, int32_t x6, int32_t y1, int32_t y2,  int32_t y3,  int32_t y4,  int32_t y5,  int32_t y6)
{
	int32_t Output = 0;

	if((x1 < x2)&&(x2 < x3)&&(x3 < x4)&&(x4 < x5)&&(x5 < x6))
	{
		if(Input <= x1)
		{
			Output = y1;
		}
		else if((Input > x1)&&(Input <= x2))
		{
			Output = y1 + (Input - x1)*(y2 - y1)/(x2 - x1);
		}
		else if((Input > x2)&&(Input <= x3))
		{
			Output = y2 + (Input - x2)*(y3 - y2)/(x3 - x2);
		}
		else if((Input > x3)&&(Input <= x4))
		{
			Output = y3 + (Input - x3)*(y4 - y3)/(x4 - x3);
		}
		else if((Input > x4)&&(Input <= x5))
		{
			Output = y4 + (Input - x4)*(y5 - y4)/(x5 - x4);
		}
		else if((Input > x5)&&(Input <= x6))
		{
			Output = y5 + (Input - x5)*(y6 - y5)/(x6 - x5);
		}
		else
		{
			Output = y6;
		}
	}
	else
	{
		Output = 0;/*Invalid parameter input*/
	}

	return Output;
}

void Lib_ResetValueInCycle(uint8_t *Value, uint16_t * Counter, uint16_t CycleThreshold)
{
	if(*Value)
	{
		(*Counter)++;
	}
	else
	{
		*Counter = 0u;
	}

	if(*Counter > CycleThreshold)
	{
		*Value = 0u;
		*Counter = 0u;
	}
}
