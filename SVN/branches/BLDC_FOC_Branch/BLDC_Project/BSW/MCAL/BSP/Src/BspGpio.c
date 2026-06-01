/**
 * @file BspGpio.c
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */
#include "main.h"
#include "BspGpio.h"

#include "FreeRTOS.h"
#include "IMU.h"
#ifndef ECU_ADDRESS_BLDC
#include "AsrNm.h"
#include "Hall.h"
#else
#include "CompatibleInfo.h"
#endif


PORT_HandleType g_tPORT_A = {.eInstance=PORT_A, .tSettings.PORT_PinInterruptCallBackType = NULL};
PORT_HandleType g_tPORT_B = {.eInstance=PORT_B, .tSettings.PORT_PinInterruptCallBackType = NULL};
PORT_HandleType g_tPORT_C = {.eInstance=PORT_C, .tSettings.PORT_PinInterruptCallBackType = NULL};
PORT_HandleType g_tPORT_D = {.eInstance=PORT_D, .tSettings.PORT_PinInterruptCallBackType = NULL};
PORT_HandleType g_tPORT_E = {.eInstance=PORT_E, .tSettings.PORT_PinInterruptCallBackType = NULL};

#ifndef ECU_ADDRESS_BLDC
/*************************Port Out Pin PinMode define start ***************************/
OutPinconfig OutPinconfigs[PORT_OUT_NUM] = {
		{.tPortOutBuff = EN_LDO_PORT        , .tPinOutBuff = EN_LDO_PIN        , .tLevelOutBuff = DIO_STD_LOW},
		{.tPortOutBuff = VBAT_HALL_CTRL_PORT, .tPinOutBuff = VBAT_HALL_CTRL_PIN, .tLevelOutBuff = DIO_STD_HIGH},
		{.tPortOutBuff = DRV_EN_PORT        , .tPinOutBuff = DRV_EN_PIN        , .tLevelOutBuff = DIO_STD_LOW }
};

PORT_InstanceType tPortOutBuff[PORT_OUT_NUM] =
{
		EN_LDO_PORT                  ,
		VBAT_HALL_CTRL_PORT          ,
		DRV_EN_PORT                  ,

};
uint32_t tPinOutBuff[PORT_OUT_NUM] =
{
		EN_LDO_PIN                  ,
		VBAT_HALL_CTRL_PIN          ,
		DRV_EN_PIN                  ,
};

/*************************Port Out Pin PinMode define end ***************************/ 

/*************************Port In Pin PinMode define start ***************************/
PORT_InstanceType tPortInBuff[PORT_IN_NUM] =
{
		IO_LHALLA_PORT             ,
		IO_LHALLB_PORT             ,
		KEYB_PORT                  ,
		KEYA_PORT                  ,
		INTN_PORT                  ,
		INT2_IAM_20680_PORT        ,
		INT_IAM_20680_PORT         ,
};
uint32_t tPinInBuff[PORT_IN_NUM] =
{
		IO_LHALLA_PIN             ,
		IO_LHALLB_PIN             ,
		KEYB_PIN                  ,
		KEYA_PIN                  ,
		INTN_PIN                  ,
		INT2_IAM_20680_PIN        ,
		INT_IAM_20680_PIN         ,
};
/*************************Port Out Pin PinMode define end ***************************/

/*************************ADC Port Pin PinMode define start ***************************/
const PORT_InstanceType e_AdcPortBuff[ADC_CHANNEL_NUM] =
{
	ADC_CSO1_PORT,
	ADC_Vbat_HALL_PORT,
	ADC_K30_PORT        ,
	ADC_TEMP_PORT        ,
	ADC_MOTOR_NEGATIVE_PORT,
	ADC_MOTOR_POSITIVE_PORT,
};
const uint32_t u32_AdcPinBuff[ADC_CHANNEL_NUM] =
{
	ADC_CSO1_PIN      	,
	ADC_Vbat_HALL_PIN  ,
	ADC_K30_PIN        ,
	ADC_TEMP_PIN       ,
	ADC_MOTOR_NEGATIVE_PIN,
	ADC_MOTOR_POSITIVE_PIN,
};
const uint32_t u32_AdcPinModeBuff[ADC_CHANNEL_NUM] =
{
	ADC_CSO1_PIN_MODE      	,
	ADC_Vbat_HALL_PIN_MODE  ,
	ADC_K30_PIN_MODE        ,
	ADC_TEMP_PIN_MODE       ,
	ADC_MOTOR_NEGATIVE_PIN_MODE,
	ADC_MOTOR_POSITIVE_PIN_MODE,
};
/*************************ADC Port Pin PinMode Define End ***************************/

/*************************SPI Port Pin PinMode define start ***************************/
const PORT_InstanceType e_SPI_CsPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_CS_PORT, SPI1_CS_PORT, SPI2_CS_PORT, SPI3_CS_PORT};
const uint32_t u32_SPI_CsPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_CS_PIN, SPI1_CS_PIN, SPI2_CS_PIN, SPI3_CS_PIN};
const uint32_t u32_SPI_CsPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_CS_PIN_MODE, SPI1_CS_PIN_MODE, SPI2_CS_PIN_MODE,SPI3_CS_PIN_MODE};
const PORT_InstanceType e_SPI_SckPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_SCK_PORT, SPI1_SCK_PORT, SPI2_SCK_PORT, SPI3_SCK_PORT};
const uint32_t u32_SPI_SckPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_SCK_PIN, SPI1_SCK_PIN, SPI2_SCK_PIN, SPI3_SCK_PIN};
const uint32_t u32_SPI_SckPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_SCK_PIN_MODE, SPI1_SCK_PIN_MODE, SPI2_SCK_PIN_MODE,SPI3_SCK_PIN_MODE};
const PORT_InstanceType e_SPI_MisoPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MISO_PORT, SPI1_MISO_PORT, SPI2_MISO_PORT,SPI3_MISO_PORT};
const uint32_t u32_SPI_MisoPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MISO_PIN, SPI1_MISO_PIN, SPI2_MISO_PIN, SPI3_MISO_PIN};
const uint32_t u32_SPI_MisoPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MISO_PIN_MODE, SPI1_MISO_PIN_MODE, SPI2_MISO_PIN_MODE,SPI3_MISO_PIN_MODE};
const PORT_InstanceType e_SPI_MosiPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MOSI_PORT, SPI1_MOSI_PORT, SPI2_MOSI_PORT,SPI3_MOSI_PORT};
const uint32_t u32_SPI_MosiPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MOSI_PIN, SPI1_MOSI_PIN, SPI2_MOSI_PIN,SPI3_MOSI_PIN};
const uint32_t u32_SPI_MosiPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MOSI_PIN_MODE, SPI1_MOSI_PIN_MODE, SPI2_MOSI_PIN_MODE,SPI3_MOSI_PIN_MODE};
/*************************SPI Port Pin PinMode define end ***************************/ 

/*************************CAN Port Pin PinMode define start   ***************************/ 
const PORT_InstanceType e_CAN_RxPortBuff[FC_PROJECT_CAN_NUM] = {CAN1_RX_PORT };
const uint32_t u32_CAN_RxPinBuff[FC_PROJECT_CAN_NUM] = {CAN1_RX_PIN };
const uint32_t u32_CAN_RxPinModeBuff[FC_PROJECT_CAN_NUM] = {CAN1_RX_PIN_MODE};

const PORT_InstanceType e_CAN_TxPortBuff[FC_PROJECT_CAN_NUM] = {CAN1_TX_PORT,};
const uint32_t u32_CAN_TxPinBuff[FC_PROJECT_CAN_NUM] = {CAN1_TX_PIN};
const uint32_t u32_CAN_TxPinModeBuff[FC_PROJECT_CAN_NUM] = {CAN1_TX_PIN_MODE};
/*************************CAN Port Pin PinMode define end *******************************/ 

/*************************IIC Port Pin PinMode define start   ***************************/ 
const PORT_InstanceType e_IIC_SclPortBuff[FC_PROJECT_IIC_NUMBER] = {SCL1_IAM_20680_PORT, IIC1_SCL_PORT};
const uint32_t u32_IIC_SclPinBuff[FC_PROJECT_IIC_NUMBER]         = {SCL1_IAM_20680_PIN, IIC1_SCL_PIN};
const uint32_t u32_IIC_SclPinModeBuff[FC_PROJECT_IIC_NUMBER]     = {SCL1_IAM_20680_PIN_MODE, IIC1_SCL_PIN_MODE};

const PORT_InstanceType e_IIC_SdaPortBuff[FC_PROJECT_IIC_NUMBER] = {SDA1_IAM_20680_PORT, IIC1_SDA_PORT};
const uint32_t u32_IIC_SdaPinBuff[FC_PROJECT_IIC_NUMBER]         = {SDA1_IAM_20680_PIN, IIC1_SDA_PIN};
const uint32_t u32_IIC_SdaPinModeBuff[FC_PROJECT_IIC_NUMBER]     = {SDA1_IAM_20680_PIN_MODE, IIC1_SDA_PIN_MODE};
/*************************IIC Port Pin PinMode define end *******************************/ 

/*************************PWM Port Pin PinMode define start *******************************************/
const PORT_InstanceType e_PWM_PortBuff[PWM_CHANNEL_NUM_MAX] = {
		PWM1_PORT,
		PWM2_PORT,
		PWM3_PORT
};
const uint32_t u32_PWM_PinBuff[PWM_CHANNEL_NUM_MAX] = {
		PWM1_PIN,
		PWM2_PIN,
		PWM3_PIN
};
const uint32_t u32_PWM_PinModeBuff[PWM_CHANNEL_NUM_MAX] = {
		PWM1_PIN_MODE,
		PWM2_PIN_MODE,
		PWM3_PIN_MODE
};
/*************************PWM Port Pin PinMode define end ***************************/
/**
 * @brief 
 */
void Bsp_GpioOutInit(void)
{
	uint8_t u8_idx = 0;
	PORT_InitType tInitStruct = {0};
	PORT_HandleType tPortDHandle;
	for(u8_idx = 0; u8_idx < PORT_OUT_NUM; u8_idx++)
	{
		tInitStruct.u32PortPins = OutPinconfigs[u8_idx].tPinOutBuff;
		tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
		tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
		tInitStruct.ePortGpioLevel = OutPinconfigs[u8_idx].tLevelOutBuff;
		tPortDHandle.eInstance = OutPinconfigs[u8_idx].tPortOutBuff;
		PORT_InitPins(&tPortDHandle, &tInitStruct);
	}
	tInitStruct.u32PortPins = OutPinconfigs[0].tPinOutBuff;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
	tInitStruct.ePortGpioLevel = DIO_STD_HIGH;
	tPortDHandle.eInstance = OutPinconfigs[0].tPortOutBuff;
	PORT_InitPins(&tPortDHandle, &tInitStruct);
}

void Bsp_GpioInInit(void)
{
	uint8_t u8_idx = 0;
	PORT_InitType tInitStruct = {0};
	PORT_HandleType tPortDHandle;
	for(u8_idx = 0; u8_idx < PORT_IN_NUM; u8_idx++)
	{
		tInitStruct.u32PortPins = tPinInBuff[u8_idx];
		tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
		tInitStruct.ePortGpioDir = PORT_GPIO_IN;
	    tInitStruct.bPullEn = false;
	    tInitStruct.ePullSel = PORT_PULL_UP;
		tPortDHandle.eInstance = tPortInBuff[u8_idx];
		PORT_InitPins(&tPortDHandle, &tInitStruct);
	}
}

/**
 * @brief
 * @return uint8_t
 */
uint8_t FCAdcGpioInit(void)
{
    uint8_t u8Index = 0;
    PORT_InitType tInitStruct = {0};
    PORT_HandleType tPortDHandle;

    for(u8Index = 0; u8Index < ADC_CHANNEL_NUM; u8Index++)
    {
        tInitStruct.u32PortPins = u32_AdcPinBuff[u8Index];
        tInitStruct.uPortPinMux.u32PortPinMode = u32_AdcPinModeBuff[u8Index];
        tPortDHandle.eInstance = e_AdcPortBuff[u8Index];
        PORT_InitPins(&tPortDHandle, &tInitStruct);
    }
    return 0;
}

uint8_t FCSpiGpioInit(uint8_t u8_spiIdx)
{
	PORT_HandleType tPortDHandle;
	PORT_InitType tPortCfg = {0};
	
	if (FCSPI_INSTANCE_COUNT <= u8_spiIdx)
    {
        return 1;
    }
    // MOSI
    tPortCfg.u32PortPins             = u32_SPI_MosiPinBuff[u8_spiIdx];
	tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_MosiPinModeBuff[u8_spiIdx];
    tPortCfg.ePortGpioDir            = PORT_GPIO_OUT;
    tPortCfg.bPullEn                 = false;
	tPortCfg.bPullEn                 = false;
    tPortCfg.ePullSel                = PORT_PULL_UP;
    tPortCfg.ePortGpioLevel          = PORT_GPIO_LOW;
	tPortDHandle.eInstance = e_SPI_MosiPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    // CS
    tPortCfg.u32PortPins = u32_SPI_CsPinBuff[u8_spiIdx];
   tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_CsPinModeBuff[u8_spiIdx];
	tPortDHandle.eInstance = e_SPI_CsPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    // CLK
    tPortCfg.u32PortPins               = u32_SPI_SckPinBuff[u8_spiIdx];
   tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_SckPinModeBuff[u8_spiIdx];
	tPortDHandle.eInstance = e_SPI_SckPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    // MISO
    tPortCfg.u32PortPins             = u32_SPI_MisoPinBuff[u8_spiIdx];
   tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_MisoPinModeBuff[u8_spiIdx];
    tPortCfg.ePortGpioDir            = PORT_GPIO_IN;
	tPortDHandle.eInstance = e_SPI_MisoPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    return 0;
}

void FCFtuPwmGpioInit(uint8_t u8_ChannelIdx)
{
	PORT_HandleType tPortDHandle;
    PORT_InitType tInitStruct = {0};
    if (PWM_CHANNEL_NUM_MAX <= u8_ChannelIdx)
    {
        return;
    }

	tInitStruct.u32PortPins = u32_PWM_PinBuff[u8_ChannelIdx];
	tInitStruct.uPortPinMux.u32PortPinMode = u32_PWM_PinModeBuff[u8_ChannelIdx];
    tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
    tInitStruct.ePortGpioLevel = PORT_GPIO_HIGH;
	tInitStruct.bPullEn = false;
	tInitStruct.ePullSel = PORT_PULL_UP;

	tPortDHandle.eInstance = e_PWM_PortBuff[u8_ChannelIdx];
	PORT_InitPins(&tPortDHandle, &tInitStruct);
}
void FCCanGpioInit(void)
{
	uint8 u8_idx;
	PORT_HandleType tPortDHandle;
	PORT_InitType tInitStruct = {0};
	for(u8_idx = 0; u8_idx < FC_PROJECT_CAN_NUM; u8_idx++)
	{
		tInitStruct.u32PortPins = u32_CAN_RxPinBuff[u8_idx];
		tInitStruct.uPortPinMux.u32PortPinMode = u32_CAN_RxPinModeBuff[u8_idx];
		tInitStruct.ePortGpioDir = PORT_GPIO_IN;
		tInitStruct.bPullEn = false;
		tInitStruct.ePullSel = PORT_PULL_UP;
		tPortDHandle.eInstance = e_CAN_RxPortBuff[u8_idx];
		PORT_InitPins(&tPortDHandle, &tInitStruct);

		/* Port B13: MUX = ALT4, CAN1_TX */
		tInitStruct.u32PortPins = u32_CAN_TxPinBuff[u8_idx];
		tInitStruct.uPortPinMux.u32PortPinMode = u32_CAN_TxPinModeBuff[u8_idx];
		tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
		tInitStruct.ePortGpioLevel = PORT_GPIO_HIGH;
		tPortDHandle.eInstance = e_CAN_TxPortBuff[u8_idx];
		PORT_InitPins(&tPortDHandle, &tInitStruct);
	}
}

void FCIicGpioInit(uint8_t u8_IicIdx)
{
	PORT_HandleType tPortHandle;
	PORT_InitType tInitStruct = {0};
	if(FCIIC_INSTANCE_COUNT <= u8_IicIdx)
	{
		return;
	}
	/* SCL */
	tInitStruct.u32PortPins = u32_IIC_SclPinBuff[u8_IicIdx];
	tInitStruct.uPortPinMux.u32PortPinMode = u32_IIC_SclPinModeBuff[u8_IicIdx];
	tInitStruct.bPullEn = false;
	tInitStruct.ePortGpioLevel = PORT_GPIO_HIGH;
	tPortHandle.eInstance=e_IIC_SclPortBuff[u8_IicIdx];
	PORT_InitPins(&tPortHandle, &tInitStruct);

	/* SDA */
	tInitStruct.u32PortPins = u32_IIC_SdaPinBuff[u8_IicIdx];
	tInitStruct.uPortPinMux.u32PortPinMode = u32_IIC_SdaPinModeBuff[u8_IicIdx];
	tInitStruct.bPullEn = false;
	tInitStruct.ePortGpioLevel = PORT_GPIO_HIGH;
	tPortHandle.eInstance=e_IIC_SdaPortBuff[u8_IicIdx];
	PORT_InitPins(&tPortHandle, &tInitStruct);
	
}

void IRQ_PORTD_INT_Callback(PORT_HandleType *pHandle, uint32_t u32pins);
void IRQ_PORTA_INT_Callback(PORT_HandleType *pHandle, uint32_t u32pins);

void ExternalInterruptPortPinInit(void)
{
	PORT_InitType tInitStruct = {0};

	tInitStruct.u32PortPins = INTN_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_FALLING;
    g_tPORT_D.eInstance = INTN_PORT;
    g_tPORT_D.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTD_INT_Callback;
	PORT_InitPins(&g_tPORT_D, &tInitStruct);

	tInitStruct.u32PortPins = IO_LHALLB_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
    g_tPORT_A.eInstance = IO_LHALLB_PORT;
    g_tPORT_A.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTA_INT_Callback;
	PORT_InitPins(&g_tPORT_A, &tInitStruct);

	tInitStruct.u32PortPins = IO_LHALLA_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
    g_tPORT_C.eInstance = IO_LHALLA_PORT;
#ifndef ECU_ADDRESS_BLDC
    g_tPORT_C.tSettings.PORT_PinInterruptCallBackType = IRQ_HALLA_Callback;
#endif
	PORT_InitPins(&g_tPORT_C, &tInitStruct);

	tInitStruct.u32PortPins = INT_IAM_20680_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_FALLING;
    g_tPORT_A.eInstance = INT_IAM_20680_PORT;
    // g_tPORT_A.tSettings.PORT_PinInterruptCallBackType = IRQ_IMU_INT_Callback;
	PORT_InitPins(&g_tPORT_A, &tInitStruct);

	tInitStruct.u32PortPins = INT2_IAM_20680_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_FALLING;
    g_tPORT_E.eInstance = INT2_IAM_20680_PORT;
#ifndef ECU_ADDRESS_BLDC
    g_tPORT_E.tSettings.PORT_PinInterruptCallBackType = IRQ_IMU_INT2_Callback;
#endif
	PORT_InitPins(&g_tPORT_E, &tInitStruct);
}

void IRQ_PORTA_INT_Callback(PORT_HandleType *pHandle, uint32_t u32pins)
{
#ifndef ECU_ADDRESS_BLDC
	if(u32pins & INT_IAM_20680_PIN)
	{
		IRQ_IMU_INT_Callback(pHandle, u32pins);
	}
	if(u32pins & IO_LHALLB_PIN)
	{
		IRQ_HALLB_Callback(pHandle, u32pins);
	}
#endif
}

uint8 reseted = 0;
void IRQ_PORTD_INT_Callback(PORT_HandleType *pHandle, uint32_t u32pins)
{
#ifndef ECU_ADDRESS_BLDC
	reseted = 1;
	if(u32pins & INTN_PIN)
	{
		if(FALSE == AsrNm_GetNetWorkReleaseState())
		{
			RCM_GenerateSwReset();
		}
	}
#endif
}

void OutPut_Deinit(void)
{
	//PORT_Deinit(&g_tPORT_E, VCP_CTRL_PIN);
//	PORT_Deinit(&g_tPORT_D, VBAT_SW_CTRL_PIN);
//	PORT_Deinit(&g_tPORT_B, VBAT_HALL_CTRL_PIN);
}

void IRQ_PORTA_WAKEUP_Callback(PORT_HandleType *pHandle, uint32_t u32pins)
{
	(void)pHandle;
	(void)u32pins;
//	__NVIC_DisableIRQ(PORTA_IRQn);
#ifndef ECU_ADDRESS_BLDC
	RCM_GenerateSwReset();
#endif
}

void IRQ_PORTC_WAKEUP_Callback(PORT_HandleType *pHandle, uint32_t u32pins)
{
	(void)pHandle;
	(void)u32pins;
//	__NVIC_DisableIRQ(PORTC_IRQn);
#ifndef ECU_ADDRESS_BLDC
	RCM_GenerateSwReset();
#endif
}

void IRQ_PORTD_WAKEUP_Callback(PORT_HandleType *pHandle, uint32_t u32pins)
{
	(void)pHandle;
	(void)u32pins;
//	__NVIC_DisableIRQ(PORTE_IRQn);
#ifndef ECU_ADDRESS_BLDC
	RCM_GenerateSwReset();
#endif
}

void IRQ_PORTE_WAKEUP_Callback(PORT_HandleType *pHandle, uint32_t u32pins)
{
	(void)pHandle;
	(void)u32pins;
//	__NVIC_DisableIRQ(PORTD_IRQn);
#ifndef ECU_ADDRESS_BLDC
	RCM_GenerateSwReset();
#endif
}

void Wakeup_gpio_external_interrupt_Config(void)
{
	PORT_InitType tInitStruct = {0};

//	tInitStruct.u32PortPins = CAN1_RX_PIN;
//	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
//	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
//    tInitStruct.bPullEn = false;
//    tInitStruct.ePullSel = PORT_PULL_UP;
//    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
//    g_tPORT_A.eInstance = CAN1_RX_PORT;
//    g_tPORT_A.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTA_WAKEUP_Callback;
//	PORT_InitPins(&g_tPORT_A, &tInitStruct);


	tInitStruct.u32PortPins = IO_LHALLA_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
    g_tPORT_C.eInstance = PORT_C;
    g_tPORT_C.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTC_WAKEUP_Callback;
	PORT_InitPins(&g_tPORT_C, &tInitStruct);

	tInitStruct.u32PortPins = IO_LHALLB_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
    g_tPORT_A.eInstance = PORT_A;
    g_tPORT_A.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTA_WAKEUP_Callback;
	PORT_InitPins(&g_tPORT_A, &tInitStruct);

	tInitStruct.u32PortPins = CAN1_RX_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
    g_tPORT_A.eInstance = PORT_A;
//    g_tPORT_A.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTA_WAKEUP_Callback;
	PORT_InitPins(&g_tPORT_A, &tInitStruct);


	tInitStruct.u32PortPins = INT2_IAM_20680_PIN;
	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
    tInitStruct.bPullEn = false;
    tInitStruct.ePullSel = PORT_PULL_UP;
    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
    g_tPORT_E.eInstance = PORT_E;
    g_tPORT_A.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTE_WAKEUP_Callback;
	PORT_InitPins(&g_tPORT_E, &tInitStruct);

//	tInitStruct.u32PortPins = INTN_PIN;
//	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
//	tInitStruct.ePortGpioDir = PORT_GPIO_IN;
//    tInitStruct.bPullEn = false;
//    tInitStruct.ePullSel = PORT_PULL_UP;
//    tInitStruct.tInterruptCfg.ePortIsrMode = PORT_IRQ_BOTH_EDGE;
//    g_tPORT_D.eInstance = PORT_D;
//    g_tPORT_D.tSettings.PORT_PinInterruptCallBackType = IRQ_PORTD_WAKEUP_Callback;
//	PORT_InitPins(&g_tPORT_D, &tInitStruct);

}

#else
/*************************Port Out Pin PinMode define start ***************************/
OutPinconfig OutPinconfigs[PORT_OUT_NUM] = {
		{.tPortOutBuff = ENC_PDRV_PORT, .tPinOutBuff = ENC_PDRV_PIN, .tLevelOutBuff = DIO_STD_HIGH},
		{.tPortOutBuff = ENB_PDRV_PORT, .tPinOutBuff = ENB_PDRV_PIN, .tLevelOutBuff = DIO_STD_HIGH},
		{.tPortOutBuff = ENA_PDRV_PORT, .tPinOutBuff = ENA_PDRV_PIN, .tLevelOutBuff = DIO_STD_HIGH },
		{.tPortOutBuff = VBAT_HALL_CTRL_PORT, .tPinOutBuff = VBAT_HALL_CTRL_PIN, .tLevelOutBuff = DIO_STD_HIGH},
		{.tPortOutBuff = HSD_DIAG_EN_PORT, .tPinOutBuff = HSD_DIAG_EN_PIN, .tLevelOutBuff = DIO_STD_LOW},
		{.tPortOutBuff = HSD_2CH_DSEL_PORT, .tPinOutBuff = HSD_2CH_DSEL_PIN, .tLevelOutBuff = DIO_STD_LOW},
		{.tPortOutBuff = NSLEEP_PDRV_PORT, .tPinOutBuff = NSLEEP_PDRV_PIN, .tLevelOutBuff = DIO_STD_HIGH},
		{.tPortOutBuff = VBAT_ENCODER_CTRL_PORT, .tPinOutBuff = VBAT_ENCODER_CTRL_PIN, .tLevelOutBuff = DIO_STD_HIGH },
		{.tPortOutBuff = EN_LDO_PORT, .tPinOutBuff = EN_LDO_PIN, .tLevelOutBuff = DIO_STD_HIGH},
		{.tPortOutBuff = CAN2_STB_PORT, .tPinOutBuff = CAN2_STB_PIN, .tLevelOutBuff = DIO_STD_LOW},
};

PORT_InstanceType tPortOutBuff[PORT_OUT_NUM] =
{
		ENC_PDRV_PORT,
		ENB_PDRV_PORT,
		ENA_PDRV_PORT,
		VBAT_HALL_CTRL_PORT,
		HSD_DIAG_EN_PORT,
		HSD_2CH_DSEL_PORT,
		NSLEEP_PDRV_PORT,
		VBAT_ENCODER_CTRL_PORT,
		EN_LDO_PORT,
		CAN2_STB_PORT
};
uint32_t tPinOutBuff[PORT_OUT_NUM] =
{
		ENC_PDRV_PIN,
		ENB_PDRV_PIN,
		ENA_PDRV_PIN,
		VBAT_HALL_CTRL_PIN,
		HSD_DIAG_EN_PIN,
		HSD_2CH_DSEL_PIN,
		NSLEEP_PDRV_PIN,
		VBAT_ENCODER_CTRL_PIN,
		EN_LDO_PIN,
		CAN2_STB_PIN
};
/*************************PWM Port Pin PinMode define end ***************************/

/*************************Port In Pin PinMode define start ***************************/
PORT_InstanceType tPortInBuff[PORT_IN_NUM] =
{
		NFAULT_PDRV_PORT,
		IO_HALL_V_PORT,
		IO_HALL_U_PORT,
		IO_HALL_W_PORT,
		INTN_WPS_PORT,
		IO_KEY_B_WPS_PORT,
		INT1_IAM_8961_WPS_PORT,
		IO_HALL_WPS_PORT,
		IO_KEY_A_WPS_PORT,
		IO_KEY_C_WPS_PORT
};
uint32_t tPinInBuff[PORT_IN_NUM] =
{
		NFAULT_PDRV_PIN,
		IO_HALL_V_PIN,
		IO_HALL_U_PIN,
		IO_HALL_W_PIN,
		INTN_WPS_PIN,
		IO_KEY_B_WPS_PIN,
		INT1_IAM_8961_WPS_PIN,
		IO_HALL_WPS_PIN,
		IO_KEY_A_WPS_PIN,
		IO_KEY_C_WPS_PIN
};
/*************************Port Out Pin PinMode define end ***************************/

/*************************ADC Port Pin PinMode define start ***************************/
const PORT_InstanceType e_AdcPortBuff[ADC_CHANNEL_NUM] =
{
	ADC_CS_V_PORT,
	ADC_CS_U_PORT,
	ADC_DIAG_W_PORT,
	ADC_DIAG_V_PORT,
	ADC_CSO_PORT,
	ADC_K30_PORT,
	ENCODER_CURRENT_PORT,
	ADC_TEMP_PORT,
	ADC_KEY_A_DIAG_PORT,
	ADC_KEY_B_DIAG_PORT
};
const uint32_t u32_AdcPinBuff[ADC_CHANNEL_NUM] =
{
	ADC_CS_V_PIN,
	ADC_CS_U_PIN,
	ADC_DIAG_W_PIN,
	ADC_DIAG_V_PIN,
	ADC_CSO_PIN,
	ADC_K30_PIN,
	ENCODER_CURRENT_PIN,
	ADC_TEMP_PIN,
	ADC_KEY_A_DIAG_PIN,
	ADC_KEY_B_DIAG_PIN
};
const uint32_t u32_AdcPinModeBuff[ADC_CHANNEL_NUM] =
{
	ADC_CS_V_PIN_MODE,
	ADC_CS_U_PIN_MODE,
	ADC_DIAG_W_PIN_MODE,
	ADC_DIAG_V_PIN_MODE,
	ADC_CSO_PIN_MODE,
	ADC_K30_PIN_MODE,
	ENCODER_CURRENT_PIN_MODE,
	ADC_TEMP_PIN_MODE,
	ADC_KEY_A_DIAG_PIN_MODE,
	ADC_KEY_B_DIAG_PIN_MODE
};
/*************************ADC Port Pin PinMode Define End ***************************/

/*************************SPI Port Pin PinMode define start ***************************/
const PORT_InstanceType e_SPI_CsPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_CS_PORT, SPI1_CS_PORT, SPI2_CS_PORT, SPI3_CS_PORT};
const uint32_t u32_SPI_CsPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_CS_PIN, SPI1_CS_PIN, SPI2_CS_PIN, SPI3_CS_PIN};
const uint32_t u32_SPI_CsPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_CS_PIN_MODE, SPI1_CS_PIN_MODE, SPI2_CS_PIN_MODE,SPI3_CS_PIN_MODE};

const PORT_InstanceType e_SPI_SckPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_SCK_PORT, SPI1_SCK_PORT, SPI2_SCK_PORT, SPI3_SCK_PORT};
const uint32_t u32_SPI_SckPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_SCK_PIN, SPI1_SCK_PIN, SPI2_SCK_PIN, SPI3_SCK_PIN};
const uint32_t u32_SPI_SckPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_SCK_PIN_MODE, SPI1_SCK_PIN_MODE, SPI2_SCK_PIN_MODE,SPI3_SCK_PIN_MODE};

const PORT_InstanceType e_SPI_MisoPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MISO_PORT, SPI1_MISO_PORT, SPI2_MISO_PORT,SPI3_MISO_PORT};
const uint32_t u32_SPI_MisoPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MISO_PIN, SPI1_MISO_PIN, SPI2_MISO_PIN, SPI3_MISO_PIN};
const uint32_t u32_SPI_MisoPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MISO_PIN_MODE, SPI1_MISO_PIN_MODE, SPI2_MISO_PIN_MODE,SPI3_MISO_PIN_MODE};

const PORT_InstanceType e_SPI_MosiPortBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MOSI_PORT, SPI1_MOSI_PORT, SPI2_MOSI_PORT,SPI3_MOSI_PORT};
const uint32_t u32_SPI_MosiPinBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MOSI_PIN, SPI1_MOSI_PIN, SPI2_MOSI_PIN,SPI3_MOSI_PIN};
const uint32_t u32_SPI_MosiPinModeBuff[FCSPI_INSTANCE_COUNT] = {SPI0_MOSI_PIN_MODE, SPI1_MOSI_PIN_MODE, SPI2_MOSI_PIN_MODE,SPI3_MOSI_PIN_MODE};
/*************************SPI Port Pin PinMode define end ***************************/

/*************************CAN Port Pin PinMode define start   ***************************/
const PORT_InstanceType e_CAN_RxPortBuff[FC_PROJECT_CAN_NUM] = {CAN1_RX_PORT, CAN2_RX_PORT};
const uint32_t u32_CAN_RxPinBuff[FC_PROJECT_CAN_NUM] = {CAN1_RX_PIN, CAN2_RX_PIN };
const uint32_t u32_CAN_RxPinModeBuff[FC_PROJECT_CAN_NUM] = {CAN1_RX_PIN_MODE, CAN2_RX_PIN_MODE};

const PORT_InstanceType e_CAN_TxPortBuff[FC_PROJECT_CAN_NUM] = {CAN1_TX_PORT, CAN2_TX_PORT};
const uint32_t u32_CAN_TxPinBuff[FC_PROJECT_CAN_NUM] = {CAN1_TX_PIN, CAN2_TX_PIN};
const uint32_t u32_CAN_TxPinModeBuff[FC_PROJECT_CAN_NUM] = {CAN1_TX_PIN_MODE, CAN2_TX_PIN_MODE};
/*************************CAN Port Pin PinMode define end *******************************/

/*************************PWM Port Pin PinMode define start *******************************************/
const PORT_InstanceType e_PWM_PortBuff[PWM_CHANNEL_NUM_MAX] = {
		PWM_INA_PORT,
		PWM_INB_PORT,
		PWM_INC_PORT
};
const uint32_t u32_PWM_PinBuff[PWM_CHANNEL_NUM_MAX] = {
		PWM_INA_PIN,
		PWM_INB_PIN,
		PWM_INC_PIN
};
const uint32_t u32_PWM_PinModeBuff[PWM_CHANNEL_NUM_MAX] = {
		PWM_INA_PIN_MODE,
		PWM_INB_PIN_MODE,
		PWM_INC_PIN_MODE
};
/*************************PWM Port Pin PinMode define end ***************************/

/**
 * @brief
 */
void Bsp_GpioOutInit(void)
{
	uint8_t u8_idx = 0;
	PORT_InitType tInitStruct = {0};
	PORT_HandleType tPortDHandle;
	for(u8_idx = 0; u8_idx < PORT_OUT_NUM; u8_idx++)
	{
		tInitStruct.u32PortPins = OutPinconfigs[u8_idx].tPinOutBuff;
		tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
		tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
		tInitStruct.ePortGpioLevel = OutPinconfigs[u8_idx].tLevelOutBuff;
		tPortDHandle.eInstance = OutPinconfigs[u8_idx].tPortOutBuff;
		PORT_InitPins(&tPortDHandle, &tInitStruct);
	}
//	tInitStruct.u32PortPins = OutPinconfigs[0].tPinOutBuff;
//	tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
//	tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
//	tInitStruct.ePortGpioLevel = DIO_STD_HIGH;
//	tPortDHandle.eInstance = OutPinconfigs[0].tPortOutBuff;
//	PORT_InitPins(&tPortDHandle, &tInitStruct);
}

void Bsp_GpioInInit(void)
{
	uint8_t u8_idx = 0;
	PORT_InitType tInitStruct = {0};
	PORT_HandleType tPortDHandle;
	for(u8_idx = 0; u8_idx < PORT_IN_NUM; u8_idx++)
	{
		tInitStruct.u32PortPins = tPinInBuff[u8_idx];
		tInitStruct.uPortPinMux.u32PortPinMode = PORT_GPIO_MODE;
		tInitStruct.ePortGpioDir = PORT_GPIO_IN;
	    tInitStruct.bPullEn = false;
	    tInitStruct.ePullSel = PORT_PULL_UP;
		tPortDHandle.eInstance = tPortInBuff[u8_idx];
		PORT_InitPins(&tPortDHandle, &tInitStruct);
	}
}

/**
 * @brief
 * @return uint8_t
 */
uint8_t FCAdcGpioInit(void)
{
    uint8_t u8Index = 0;
    PORT_InitType tInitStruct = {0};
    PORT_HandleType tPortDHandle;

    for(u8Index = 0; u8Index < ADC_CHANNEL_NUM; u8Index++)
    {
        tInitStruct.u32PortPins = u32_AdcPinBuff[u8Index];
        tInitStruct.uPortPinMux.u32PortPinMode = u32_AdcPinModeBuff[u8Index];
        tPortDHandle.eInstance = e_AdcPortBuff[u8Index];
        PORT_InitPins(&tPortDHandle, &tInitStruct);
    }
    return 0;
}


uint8_t FCSpiGpioInit(uint8_t u8_spiIdx)
{
	PORT_HandleType tPortDHandle;
	PORT_InitType tPortCfg = {0};

	if (FCSPI_INSTANCE_COUNT <= u8_spiIdx)
    {
        return 1;
    }
    // MOSI
    tPortCfg.u32PortPins             = u32_SPI_MosiPinBuff[u8_spiIdx];
	tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_MosiPinModeBuff[u8_spiIdx];
    tPortCfg.ePortGpioDir            = PORT_GPIO_OUT;
    tPortCfg.bPullEn                 = false;
	tPortCfg.bPullEn                 = false;
    tPortCfg.ePullSel                = PORT_PULL_UP;
    tPortCfg.ePortGpioLevel          = PORT_GPIO_LOW;
	tPortDHandle.eInstance = e_SPI_MosiPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    // CS
    tPortCfg.u32PortPins = u32_SPI_CsPinBuff[u8_spiIdx];
   tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_CsPinModeBuff[u8_spiIdx];
	tPortDHandle.eInstance = e_SPI_CsPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    // CLK
    tPortCfg.u32PortPins               = u32_SPI_SckPinBuff[u8_spiIdx];
   tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_SckPinModeBuff[u8_spiIdx];
	tPortDHandle.eInstance = e_SPI_SckPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    // MISO
    tPortCfg.u32PortPins             = u32_SPI_MisoPinBuff[u8_spiIdx];
   tPortCfg.uPortPinMux.u32PortPinMode = u32_SPI_MisoPinModeBuff[u8_spiIdx];
    tPortCfg.ePortGpioDir            = PORT_GPIO_IN;
    tPortCfg.bPullEn 				= true;
    tPortCfg.ePullSel                = PORT_PULL_UP;
	tPortDHandle.eInstance = e_SPI_MisoPortBuff[u8_spiIdx];
	PORT_InitPins(&tPortDHandle, &tPortCfg);
    return 0;
}

void FCFtuPwmGpioInit(uint8_t u8_ChannelIdx)
{
	PORT_HandleType tPortDHandle;
    PORT_InitType tInitStruct = {0};
    if (PWM_CHANNEL_NUM_MAX <= u8_ChannelIdx)
    {
        return;
    }

	tInitStruct.u32PortPins = u32_PWM_PinBuff[u8_ChannelIdx];
	tInitStruct.uPortPinMux.u32PortPinMode = u32_PWM_PinModeBuff[u8_ChannelIdx];
    tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
    tInitStruct.ePortGpioLevel = PORT_GPIO_HIGH;
	tInitStruct.bPullEn = false;
	tInitStruct.ePullSel = PORT_PULL_UP;

	tPortDHandle.eInstance = e_PWM_PortBuff[u8_ChannelIdx];
	PORT_InitPins(&tPortDHandle, &tInitStruct);
}

void FCCanGpioInit(void)
{
	uint8 u8_idx;
	PORT_HandleType tPortDHandle;
	PORT_InitType tInitStruct = {0};
	for(u8_idx = 0; u8_idx < FC_PROJECT_CAN_NUM; u8_idx++)
	{
		tInitStruct.u32PortPins = u32_CAN_RxPinBuff[u8_idx];
		tInitStruct.uPortPinMux.u32PortPinMode = u32_CAN_RxPinModeBuff[u8_idx];
		tInitStruct.ePortGpioDir = PORT_GPIO_IN;
		tInitStruct.bPullEn = false;
		tInitStruct.ePullSel = PORT_PULL_UP;
		tPortDHandle.eInstance = e_CAN_RxPortBuff[u8_idx];
		PORT_InitPins(&tPortDHandle, &tInitStruct);

		/* Port B13: MUX = ALT4, CAN1_TX */
		tInitStruct.u32PortPins = u32_CAN_TxPinBuff[u8_idx];
		tInitStruct.uPortPinMux.u32PortPinMode = u32_CAN_TxPinModeBuff[u8_idx];
		tInitStruct.ePortGpioDir = PORT_GPIO_OUT;
		tInitStruct.ePortGpioLevel = PORT_GPIO_HIGH;
		tPortDHandle.eInstance = e_CAN_TxPortBuff[u8_idx];
		PORT_InitPins(&tPortDHandle, &tInitStruct);
	}
}

#endif
