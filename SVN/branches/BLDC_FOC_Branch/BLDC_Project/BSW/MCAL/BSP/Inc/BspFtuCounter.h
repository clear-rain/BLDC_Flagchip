/*
 * BspFtuCounter.h
 *
 *  Created on: 2024年11月20日
 *      Author: 14013
 */

#ifndef BSW_MCAL_BSP_INC_BSPFTUCOUNTER_H_
#define BSW_MCAL_BSP_INC_BSPFTUCOUNTER_H_

#include "main.h"

typedef struct
{
	//g_tFtuHandle.eInstance
	FTU_InstanceType    eInstance;

	//FTU_CommonType 			tInitConfig
	FTU_ClkSrcType 		eClkSrc;                /**< Ftu clock source */
	FTU_PrescalerType 	ePrescaler;            	/*!< Ftu prescaler */
	uint32_t 			u32InterruptMask;		/**< interrupt enable mask */
	void 				(*pOverflowCallback)(FTU_HandleType *pHandle);

	//FTU_CounterModeType 		tCounterConfig
    uint32_t u32CounterValue;                       /**< counter overflow value (timer ticks) */
    uint32_t u32InitialValue;						/**< counter initial value (timer ticks) */


}FtuCounterPrivateData_t;

struct FtuCounterDriverIf_t
{
	char *name;
	FtuCounterPrivateData_t *ftuPriData;
	void (*GPIO_Init)(uint8_t u8_ChannelIdx);
	void (*FtuCounterInit)(struct FtuCounterDriverIf_t *pDev);
	void (*FtuCounterTimerStart)(void);
	void (*FtuCounterTimerStop)(void);
	uint32_t (*FtuCounterGetCnt)(void);
	void (*FtuCounterClearCnt)(void);
};

struct FtuCounterDriverIf_t * BSP_CounterGetDevice(char *name);
void Bsp_FtuCounter_DeInit(void);
#endif /* BSW_MCAL_BSP_INC_BSPFTUCOUNTER_H_ */
