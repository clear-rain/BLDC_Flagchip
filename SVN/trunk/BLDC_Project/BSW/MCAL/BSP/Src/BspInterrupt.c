#include "main.h"
#include "BspInterrupt.h"
#include "BspRtc.h"
#include "BspAontimer.h"
#include "SEGGER_SYSVIEW_FreeRTOS.h"

extern FCSPI_HandleType	g_tFcspi1Handle;
extern DMA_HandleType stFcSpiDmaHandleBuff[];
extern DMA_HandleType  g_tDmaRxHandle;
extern DMA_HandleType  g_tDmaTxHandle;
extern DMA_InstanceHandleType	g_tDmaInstanceHandle;
extern DMA_HandleType g_tAdcDmaHandle[2];

extern FLEXCAN_HandleType  g_tCan2;
extern FLEXCAN_HandleType  g_tCan1;

void FCSPI2_IRQHandler(void);
void DMA4_IRQHandler(void);
void DMA5_IRQHandler(void);
void DMA_Error_IRQHandler(void);

static const IRQn_Type  IRQnFcspiTable[] =
{
    FCSPI0_IRQn,
    FCSPI1_IRQn,
    FCSPI2_IRQn,
    FCSPI3_IRQn
};

extern FCIIC_MasterHandleType g_tFciicMasterHandle;


void FCIIC0_IRQHandler(void);
// void FCIIC1_IRQHandler(void);


static const IRQn_Type IRQnFciicTable[] = {
		FCIIC0_IRQn,
		FCIIC1_IRQn,
};
static const IRQn_Type IRQnDmaTable[] = {
		DMA0_IRQn,
		DMA1_IRQn,
		DMA2_IRQn,
		DMA3_IRQn,
		DMA4_IRQn,
		DMA5_IRQn,
		DMA6_IRQn,
		DMA7_IRQn,
		DMA8_IRQn,
		DMA9_IRQn,
		DMA10_IRQn,
		DMA11_IRQn,
		DMA12_IRQn,
		DMA13_IRQn,
		DMA14_IRQn,
		DMA15_IRQn,
		DMA_error_IRQn,
};

void PORTA_IRQHandler();
void PORTB_IRQHandler();
void PORTC_IRQHandler();
void PORTD_IRQHandler();
void PORTE_IRQHandler();

static const IRQn_Type IRQnPortTable[] = {
		PORTA_IRQn,
		PORTB_IRQn,
		PORTC_IRQn,
		PORTD_IRQn,
		PORTE_IRQn,
};
static const IRQn_Type IRQnCanTable[] = {
	    FlexCAN0_IRQn,
	    FlexCAN1_IRQn,
	    FlexCAN2_IRQn,
	    FlexCAN3_IRQn,
	    FlexCAN4_IRQn,
	    FlexCAN5_IRQn
};
extern PORT_HandleType g_tPORT_A;
extern PORT_HandleType g_tPORT_B;
extern PORT_HandleType g_tPORT_C;
extern PORT_HandleType g_tPORT_D;
extern PORT_HandleType g_tPORT_E;


static const IRQn_Type IRQnWdogTable[] = {
		WDOG0_IRQn,
		WDOG1_IRQn
};

static const IRQn_Type IRQnPtimerTable[] =
{
    PTIMER0_IRQn,
    PTIMER1_IRQn
};

extern WDOG_HandleType g_tWdogHandle;

extern FTU_HandleType	g_tFtuCounterHandle;
extern FTU_HandleType	g_tFtuHallCounterHandle;

void FTU1_IRQHandler();
void FTU2_IRQHandler();

extern FTU_HandleType	g_tFtuPwmHandle;
void FTU0_IRQHandler();

void Interrupt_Init(void)
{
	uint8_t u8FcspiIndex;
	uint8_t u8DmaChannel;
	uint8_t u8PortIndex;
	uint8_t u8WdogIndex;
	uint8_t u8I2cIndex;

    /* enable global interrupt for fciic */
//	u8I2cIndex = 0U;
//    __NVIC_EnableIRQ(IRQnFciicTable[u8I2cIndex]);
	u8FcspiIndex = 0U;
	__NVIC_EnableIRQ(IRQnFcspiTable[u8FcspiIndex]);
	u8FcspiIndex = 1U;
	__NVIC_EnableIRQ(IRQnFcspiTable[u8FcspiIndex]);
	u8FcspiIndex = 2U;
	__NVIC_EnableIRQ(IRQnFcspiTable[u8FcspiIndex]);


	// Spi and I2C's DMA channels IRQ enable
	for(u8DmaChannel = 0U; u8DmaChannel < 8U; u8DmaChannel++)
	{
		__NVIC_EnableIRQ(IRQnDmaTable[u8DmaChannel]);
	}
	__NVIC_EnableIRQ(FTU0_IRQn);

	/* The interrupt at port A is enabled for the acquisition of HallB and IMU INT */
	u8PortIndex = 0U;
    __NVIC_EnableIRQ(IRQnPortTable[u8PortIndex]);

	/* The interrupt at port B is enabled for the acquisition of HALL_U (BLDC) */
	u8PortIndex = 1U;
	__NVIC_EnableIRQ(IRQnPortTable[u8PortIndex]);

    /* The interrupt at port C is enabled for the acquisition of HallA */
	u8PortIndex = 2U;
    __NVIC_EnableIRQ(IRQnPortTable[u8PortIndex]);

    /* The interrupt at port D is enabled for the acquisition of INTN */
	u8PortIndex = 3U;
    __NVIC_EnableIRQ(IRQnPortTable[u8PortIndex]);

    /* The interrupt at port E is enabled for the acquisition of IMU INT2 */
	u8PortIndex = 4U;
    __NVIC_EnableIRQ(IRQnPortTable[u8PortIndex]);

    /* enable global interrupt for ftu1 */
    __NVIC_EnableIRQ(FTU1_IRQn);

	/* enable global interrupt for ftu2 */
	__NVIC_EnableIRQ(FTU2_IRQn);

    u8WdogIndex = 0U;

    /* enable global interrupt for wdog0 */
//    __NVIC_EnableIRQ(IRQnWdogTable[u8WdogIndex]);

    __NVIC_EnableIRQ(PTIMER1_IRQn);

//    __NVIC_EnableIRQ(AONTMR_IRQn);

    __NVIC_EnableIRQ(ADC0_IRQn);
    __NVIC_EnableIRQ(ADC1_IRQn);
#if FLEXCAN_USED_INSTANCE0 == STD_ON
    /* enable global interrupt for pCan */
    __NVIC_EnableIRQ(IRQnCanTable[g_tCan0.eInstance]);
#endif /* end for #if FLEXCAN_USED_INSTANCE0 == STD_ON */

#if FLEXCAN_USED_INSTANCE1 == STD_ON
    /* enable global interrupt for pCan */
    __NVIC_EnableIRQ(IRQnCanTable[g_tCan1.eInstance]);
#endif /* end for #if FLEXCAN_USED_INSTANCE1 == STD_ON */

#if FLEXCAN_USED_INSTANCE2 == STD_ON
    /* enable global interrupt for pCan */
    __NVIC_EnableIRQ(IRQnCanTable[g_tCan2.eInstance]);
#endif /* end for #if FLEXCAN_USED_INSTANCE2 == STD_ON */
    
}
void DMA0_IRQHandler(void);
void DMA1_IRQHandler(void);

void DMA0_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&g_tAdcDmaHandle[0]);
}

void DMA1_IRQHandler(void)
{
    DMA_Transfer_Complete_IRQHandler(&g_tAdcDmaHandle[1]);
}

void CAN1_IRQHandler(void)
{
	FLEXCAN_InterruptProcess(&g_tCan1);
}

void CAN2_IRQHandler(void)
{
	FLEXCAN_InterruptProcess(&g_tCan2);
}

void PORTA_IRQHandler()
{
	PORT_IRQHandler(&g_tPORT_A);
}

void PORTB_IRQHandler()
{
	PORT_IRQHandler(&g_tPORT_B);
}

void PORTC_IRQHandler()
{
	PORT_IRQHandler(&g_tPORT_C);
}

void PORTD_IRQHandler()
{
	PORT_IRQHandler(&g_tPORT_D);
}

void PORTE_IRQHandler()
{
	PORT_IRQHandler(&g_tPORT_E);
}

void FTU1_IRQHandler()
{
	FTUn_IRQHandler(&g_tFtuCounterHandle);
}

void FTU2_IRQHandler()
{
	FTUn_IRQHandler(&g_tFtuHallCounterHandle);
}

void FTU0_IRQHandler()
{
	FTUn_IRQHandler(&g_tFtuPwmHandle);
}


void WDOG0_IRQHandler(void);
void WDOG1_IRQHandler(void);

void WDOG0_IRQHandler(void)
{
    WDOG_IRQHandler(&g_tWdogHandle);
}

void WDOG1_IRQHandler(void)
{
    WDOG_IRQHandler(&g_tWdogHandle);
}

//void FCIIC0_IRQHandler(void)
//{
//    if (FCIIC_INSTANCE_0 == g_tFciicMasterHandle.eInstance)
//    {
//        FCIIC_LL_MasterIRQnHandler(&g_tFciicMasterHandle);
//    }
//    else
//    {
//
//    }
//}

void RTC_IRQHandler(void)
{
	RTC_Alarm_Overflow_IRQHandler(&g_tRtcHandle);
}

extern AONTIMER_HandleType g_tAontimerHandle;
void AONTIMER_IRQHandler(void)
{
    Aontimer_CommonProcessInterrupt(&g_tAontimerHandle);
}

extern PTIMER_HandleType g_tPtimerHandle;


void PTIMER0_IRQHandler(void);
void PTIMER1_IRQHandler(void);

void PTIMER0_IRQHandler(void)
{
    PTIMERn_IRQHandler(&g_tPtimerHandle);
}

void PTIMER1_IRQHandler(void)
{
    PTIMERn_IRQHandler(&g_tPtimerHandle);
}


void Wakeup_GPIO_Interrupt_Enable(void)
{
//	__NVIC_DisableIRQ(PORTE_IRQn);
//	__NVIC_DisableIRQ(IRQnCanTable[g_tCan1.eInstance]);
//	__NVIC_DisableIRQ(IRQnCanTable[g_tCan2.eInstance]);
//	__NVIC_EnableIRQ(PORTA_IRQn);
//	__NVIC_EnableIRQ(PORTE_IRQn);
//	__NVIC_EnableIRQ(PORTB_IRQn);
//	__NVIC_EnableIRQ(PORTD_IRQn);
}
