/*
 * BspFtuPwm.h
 *
 *  Created on: 2024年11月4日
 *      Author: 14013
 */

#ifndef BSW_MCAL_BSP_INC_BSPFTUPWM_H_
#define BSW_MCAL_BSP_INC_BSPFTUPWM_H_

#include "main.h"
#pragma pack(1)

#ifndef ECU_ADDRESS_BLDC


#define FTU3_ChannelCount 1
#define FTU0_ChannelCount 2


#define PWM_INSTANCE_NUM 2

uint64_t period_us_plus_1k;

typedef struct
{
	FTU_InstanceType    eInstance;
	FTU_PrescalerType 	ePrescaler;            	/*!< Ftu prescaler */

	uint32_t u32PwmPeriod;                /*!< pwm period (timer ticks) */
	FTU_PwmAlignedType	eAlignedMode;
	uint32_t u32ChannelCount;			  	/**< channel count of the Ftu instance */
	FTU_PwmUpdateModeType	eUpdateMode;	/**< pwm Update Mode of Period and duty*/


//	uint8_t u8Channel;								/*!< selected FTU channel */
//	FTU_PwmPinModeType ePinMode;          /**< pwm mode */
//    uint32_t u32PwmDuty;                  /*!< pwm duty (timer ticks) */
//    uint32_t u32ChannelDeadtime;          /*!< pwm deadtime (source clock ticks) */
//    bool bDeadtimeEnable;				  /**< Deadtime Enable */
//    bool bLinkMode;                       /*!< pwm channel link mode enable, channel num must be even,and the linked channel is current_channel+1*/
//    bool bLinkChannelComplement;          /*!< pwm link channel output complement*/
//    uint32_t u32PhaseShift;				  /**< pwm phase shift (timer ticks)*/

	FTU_PwmChannelType			aPwmChannel[FTU0_ChannelCount];
}FtuPwmPrivateData_t;

struct FtuPwmDriverIf_t
{
	char *name;
	FtuPwmPrivateData_t *ftuPriData;
	void (*GPIO_Init)(uint8_t u8_ChannelIdx);
	void (*FtuPwmInit)(struct FtuPwmDriverIf_t *pDev);
	void (*FtuPwmTimerStart)(void);
	void (*FtuPwmTimerStop)(void);
	void (*FtuPwmDutySet)(struct FtuPwmDriverIf_t *pDev,uint8_t channelCnt,uint16_t u16_dutyVal);
	void (*FtuPwmPeriodSet)(struct FtuPwmDriverIf_t *pDev, uint32 PeriodCnt);
};

#pragma pack()

extern struct FtuPwmDriverIf_t *BSP_PwmGetDevice(char *name);
void Bsp_FtuPWM_DeInit(void);
#else
#define FTU0_ChannelCount 3


#define PWM_INSTANCE_NUM 1

uint64_t period_us_plus_1k;

typedef struct
{
	FTU_InstanceType    eInstance;
	FTU_PrescalerType 	ePrescaler;            	/*!< Ftu prescaler */

	uint32_t u32PwmPeriod;                /*!< pwm period (timer ticks) */
	FTU_PwmAlignedType	eAlignedMode;
	uint32_t u32ChannelCount;			  	/**< channel count of the Ftu instance */
	FTU_PwmUpdateModeType	eUpdateMode;	/**< pwm Update Mode of Period and duty*/


//	uint8_t u8Channel;								/*!< selected FTU channel */
//	FTU_PwmPinModeType ePinMode;          /**< pwm mode */
//    uint32_t u32PwmDuty;                  /*!< pwm duty (timer ticks) */
//    uint32_t u32ChannelDeadtime;          /*!< pwm deadtime (source clock ticks) */
//    bool bDeadtimeEnable;				  /**< Deadtime Enable */
//    bool bLinkMode;                       /*!< pwm channel link mode enable, channel num must be even,and the linked channel is current_channel+1*/
//    bool bLinkChannelComplement;          /*!< pwm link channel output complement*/
//    uint32_t u32PhaseShift;				  /**< pwm phase shift (timer ticks)*/

	FTU_PwmChannelType			aPwmChannel[FTU0_ChannelCount];
}FtuPwmPrivateData_t;

struct FtuPwmDriverIf_t
{
	char *name;
	FtuPwmPrivateData_t *ftuPriData;
	void (*GPIO_Init)(uint8_t u8_ChannelIdx);
	void (*FtuPwmInit)(struct FtuPwmDriverIf_t *pDev);
	void (*FtuPwmTimerStart)(void);
	void (*FtuPwmTimerStop)(void);
	void (*FtuPwmDutySet)(struct FtuPwmDriverIf_t *pDev,uint8_t channelCnt,uint16_t u16_dutyVal);
	void (*FtuPwmPeriodSet)(struct FtuPwmDriverIf_t *pDev, uint32 PeriodCnt);
};

#pragma pack()

extern struct FtuPwmDriverIf_t *BSP_PwmGetDevice(char *name);
void Bsp_FtuPWM_DeInit(void);
void Bsp_Ftu_SetDuty(uint8_t channelCnt, uint16_t duty);

#endif /*ECU_ADDRESS_BLDC*/
#endif /* BSW_MCAL_BSP_INC_BSPFTUPWM_H_ */
