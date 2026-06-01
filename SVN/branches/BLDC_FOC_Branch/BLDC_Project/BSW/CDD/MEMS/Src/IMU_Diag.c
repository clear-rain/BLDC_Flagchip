#include "IMU_Diag.h"
#include "IMU_Cfg.h"
// #include "Dio.h"
// #include "Port.h"
#include "BspIic.h"

extern volatile IMU_Acceleration_t g_tImuAccCalcVal;
extern volatile IMU_EulerAngles_t g_tImuAnglesVal;
extern IMU_ERR_STA_e g_eImuErrStatus;
extern int8_t g_i8AccChipTemp;
extern int16_t g_i16IsEcuStudy; 			// 0-not study, 1-study
extern int16_t  g_ai16ImuAccelStuData[]; 	// study data
//extern int16_t g_ai16ImuDataBlock[];
extern int16_t g_aui16ImuCalibrationData[];
int16_t g_ai16ImuDataBlock[16] = {0};

void IMU_DiagInit(void)
{

	if (E_OK == Imu_StudyDataReadNvm())
	{
		// todo: if NvM data error, set all data to zero.
		g_i16IsEcuStudy = g_ai16ImuDataBlock[0];
		g_ai16ImuAccelStuData[0] = g_ai16ImuDataBlock[1];
		g_ai16ImuAccelStuData[1] = g_ai16ImuDataBlock[2];
		g_ai16ImuAccelStuData[2] = g_ai16ImuDataBlock[3];
		g_aui16ImuCalibrationData[0] = g_ai16ImuDataBlock[4];
		g_aui16ImuCalibrationData[1] = g_ai16ImuDataBlock[5];
		g_aui16ImuCalibrationData[2] = g_ai16ImuDataBlock[6];
	}
}

static uint8_t IMU_Delay_us()
{
	volatile uint32_t i = 0;
	for(i = 0; i < 6; i++)
	{
		__asm("nop");
	}
	return 0;
}
IMU_CHIPID_STA_e IMU_CheckChipId(void)
{
	uint8_t l_ui8Idx = 0;
	uint8_t ui8_chipId = 0;
	IMU_ReadRegSync(IMU_WHOAMI_ADDR, &ui8_chipId, 1);
	if(IMU_WHOAMI_VAL == ui8_chipId)
	{
		return e_IMU_CHIPID_OK;
	}
//	I2c_DeInit();
//	Port_SetPinMode(PortConf_PortPin_PTC15_SCL_IAM,SIUL2_0_PORT79_GPIO);
//	Port_SetPinDirection(PortConf_PortPin_PTC15_SCL_IAM,PORT_PIN_OUT);
////	// Siul2_Port_Ip_GetPinConfiguration(PORTC_L_HALF,Test_pinRead,15);
//	for (l_ui8Idx = 0; l_ui8Idx < 64U; l_ui8Idx++)
//	{
//		Dio_WriteChannel(DioConf_DioChannel_IMU_SCL, 1);
//		IMU_Delay_us();
//		Dio_WriteChannel(DioConf_DioChannel_IMU_SCL, 0);
//		IMU_Delay_us();
//	}
//	Dio_WriteChannel(DioConf_DioChannel_IMU_SCL, 1);
//	(void)Platform_SetIrq(LPI2C1_IRQn, FALSE);
//	I2c_DeInit();
//	// restart I2C
//	Port_SetPinMode(PortConf_PortPin_PTC15_SCL_IAM,SIUL2_0_PORT79_LPI2C1_LPI2C1_SCL_INOUT);
//	Port_SetPinDirection(PortConf_PortPin_PTC15_SCL_IAM,PORT_PIN_OUT);
//	(void)Platform_SetIrq(LPI2C1_IRQn, TRUE);
//	I2c_Init(&I2c_Config);
	return e_IMU_CHIPID_ERR;
}


uint8 IMU_GetErrorStatus(void)
{
	uint8_t e_imuErrStatus;
	if(1 == g_i16IsEcuStudy)
	{
		e_imuErrStatus = 0;
	}
	else
	{
		e_imuErrStatus = 1;
	}	
	if(e_IMU_RUN_OK != g_eImuErrStatus)
	{
		e_imuErrStatus |= 0x02;
	}
	return e_imuErrStatus;
}

Std_ReturnType  IMU_ReadTempC(int8_t* sTemp)
{
	*sTemp = g_i8AccChipTemp + 25;
	return E_OK;
}


Std_ReturnType IMU_ReadIMUPitch(int16_t *IMUPitch)
{
	*IMUPitch = (int16_t)(g_tImuAnglesVal.pitch * 100.0f);
	return E_OK;
}

Std_ReturnType IMU_ReadIMURoll(int16_t *IMURoll)
{
	*IMURoll = (int16_t)(g_tImuAnglesVal.roll * 100.0f);
	return E_OK;
}
