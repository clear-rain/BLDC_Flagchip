#include "IMU_Cfg.h"
#include "IMU_Diag.h"
#include "IMU_Driver.h"
#include "math.h"
#include "tgmath.h"
#include "Can_Hw.h"

#define IMU_CALC_PI 3.1415f

extern int16_t g_ai16ImuDataBlock[];

volatile IMU_Acceleration_t g_tImuAccCalcVal;
volatile IMU_EulerAngles_t g_tImuAnglesVal;
IMU_ERR_STA_e g_eImuErrStatus = e_IMU_RUN_OK;
static IMU_MODE_SET_STA_e  s_eImuModeSetSta = e_IMU_ERROR_SET;
int16_t g_i16IsEcuStudy = 0;			// 0 - self study not finished; 1 - self study finished;
static IMU_RUNNING_MODE_e s_eImuRunMode = e_IMU_NORMAL_MODE;
static IMU_STUDY_STA_e s_eAccStuStu = e_IMU_STUDY_EXECUTING; // 瑜版挸澧犲锝呮躬閼奉亜顒熸稊鐘垫畱閻樿埖锟斤拷
static IMU_FCT_STA_e s_eAccFctStu = e_IMU_FCT_EXECUTING; // 瑜版挸澧犲锝呮躬閼奉亜顒熸稊鐘垫畱閻樿埖锟斤拷
static int16_t s_aui16ImuAccelData[3] = {0};
int16_t g_ai16ImuAccelStuData[3] = {0}; // 閼奉亜顒熸稊鐘垫畱閸旂娀锟界喎瀹抽崐锟�
uint8_t g_aui8ImuRxBuff[15] = {0};
uint16_t g_aui8ImuAccXbuff[100] = {0};
uint16_t g_aui8ImuAccYbuff[100] = {0};
uint16_t g_aui8ImuAccZbuff[100] = {0};

int16_t g_aui16ImuCalibrationData[3] = {0};
static uint8_t s_ui8AccDataIdx = 0u;
static uint8_t s_ui8StuAccDataReady = 0;	// 鐎涳缚绡勯崝鐘伙拷鐔峰閺佺増宓侀崙鍡楊槵婵傦拷
static uint8_t s_ui8FctAccDataReady = 0;	// 鐎涳缚绡勯崝鐘伙拷鐔峰閺佺増宓侀崙鍡楊槵婵傦拷
static uint8_t s_ui8NorAccDataReady = 0;	// 濮濓絽鐖堕崝鐘伙拷鐔峰閺佺増宓侀崙鍡楊槵婵傦拷


void IMU_AllRegsInitSync(void)
{
	uint8_t l_ui8Idx = 0;
	TickType_t l_ui32NextWakeTime;
	s_eImuModeSetSta = e_IMU_ERROR_SET;
	for (l_ui8Idx = 0; l_ui8Idx < 3U; l_ui8Idx++)
	{
		if (e_IMU_CHIPID_OK == IMU_CheckChipId())
		{
			break;
		}
	}
	if (3U <= l_ui8Idx)
	{
		s_eImuRunMode = e_IMU_ERROR_MODE;
		g_eImuErrStatus = e_IMU_I2C_ERR;
		return;
	}
	IMU_WriteReg(IMU_SENS_CONFIG1_ADDR, 0x80);
	l_ui32NextWakeTime = IMU_SysTickGet();
	IMU_DelayMs(l_ui32NextWakeTime, IMU_DELAY_1MS);
	IMU_WriteReg(IMU_SENS_CONFIG1_ADDR, 0x00);	// standby mode
	IMU_WriteReg(IMU_SENS_CONFIG2_ADDR, 0x40);  // WAKE_PM=High performance mode,SLEEP_PM= Low-power mode
    IMU_WriteReg(IMU_SENS_CONFIG3_ADDR, 0x58); 	// WAKE_ODR=100Hz,SLEEP_ODR=12.5Hz
	IMU_WriteReg(IMU_INT_EN_ADDR, 0x80); 		// Enable data ready interrupt
	IMU_WriteReg(IMU_INT_PIN_SEL_ADDR, 0x00); 	// All int event maps to INT1 pin
    IMU_WriteReg(IMU_SENS_CONFIG4_ADDR, 0x00); 	// int1 pin low level active
	IMU_WriteReg(IMU_SENS_CONFIG1_ADDR, 0x03); 	// +-4g,Active mode,1024 LSB/g
	s_eImuRunMode = e_IMU_NORMAL_MODE;
	s_eImuModeSetSta = e_IMU_NORMAL_SET_OK;
}

Std_ReturnType IMU_SetPowerMode(uint8_t u8_mode)
{
	TickType_t l_ui32NextWakeTime;
	if(((uint8_t)e_IMU_ERROR_MODE <= u8_mode)|| (e_IMU_ERROR_MODE == s_eImuRunMode))
	{
		return E_NOT_OK;
	}
	// s_eImuModeSetSta = e_IMU_ERROR_SET;
	l_ui32NextWakeTime = IMU_SysTickGet();
	if(e_IMU_SLEEP_MODE == (IMU_RUNNING_MODE_e)u8_mode)
	{
		s_eImuModeSetSta = e_IMU_ERROR_SET;
		IMU_DelayMs(l_ui32NextWakeTime, IMU_DELAY_1MS);
		IMU_DelayMs(l_ui32NextWakeTime, IMU_DELAY_1MS);
		IMU_WriteReg(IMU_SENS_CONFIG1_ADDR, 0x80); 		// reset chip
		IMU_DelayMs(l_ui32NextWakeTime, IMU_DELAY_1MS);
		IMU_WriteReg(IMU_SENS_CONFIG1_ADDR, 0x00); 		// standby mode
		IMU_WriteReg(IMU_SENS_CONFIG3_ADDR, 0x39); 		// WAKE_ODR=100Hz,SLEEP_ODR=12.5Hz
		IMU_WriteReg(IMU_SDCD_CONFIG1_ADDR, 0x38); 		// 
		IMU_WriteReg(IMU_SDCD_CONFIG2_ADDR, 0xC0); 		// 
		/* Set the SDCD_OT debounce count to 0 */
		IMU_WriteReg(IMU_SDCD_OT_DBCNT_ADDR, 0x00); 	//
		/* Set the SDCD lower and upper thresholds to 100mg*/
		// IMU_WriteReg(IMU_SDCD_LTHS_LSB_ADDR, 0x00); 	// 
		// IMU_WriteReg(IMU_SDCD_LTHS_MSB_ADDR, 0xFD); 	// 
		// IMU_WriteReg(IMU_SDCD_UTHS_LSB_ADDR, 0x00); 	// 
		// IMU_WriteReg(IMU_SDCD_UTHS_MSB_ADDR, 0x02); 	// 

		IMU_WriteReg(IMU_SDCD_LTHS_LSB_ADDR, 0xE0); 	// 
		IMU_WriteReg(IMU_SDCD_LTHS_MSB_ADDR, 0xFF); 	// 
		IMU_WriteReg(IMU_SDCD_UTHS_LSB_ADDR, 0x10); 	// 
		IMU_WriteReg(IMU_SDCD_UTHS_MSB_ADDR, 0x00); 	// 

		/* Enable SDCD outside of thresholds event Auto-WAKE/SLEEP transition source enable. */
		IMU_WriteReg(IMU_SENS_CONFIG4_ADDR, 0x21); 		// open SDCD and ORIENT interrupt
		/* Set the ASLP count to 5sec */
		IMU_WriteReg(IMU_ASLP_COUNT_LSB_ADDR, 0x2); 	// 
		IMU_WriteReg(IMU_ASLP_COUNT_MSB_ADDR, 0x00); 	// 
		/* Enable Interrupts for WAKE mode. */
		IMU_WriteReg(IMU_INT_EN_ADDR, 0x1); 			//
		IMU_WriteReg(IMU_INT_PIN_SEL_ADDR, 0x00); 		// All int event maps to INT1 pin
		IMU_WriteReg(IMU_SENS_CONFIG1_ADDR, 0x03); 		// Active mode 鍗�4g,512 LSB/g
		s_eImuModeSetSta = e_IMU_SLEEP_SET_OK;
	}
	else //if ((e_IMU_NORMAL_MODE == u8_mode) || (e_IMU_SELFSTUDY_MODE == u8_mode))
	{
		s_ui8AccDataIdx = 0u;
		s_ui8StuAccDataReady = 0;
		s_ui8NorAccDataReady = 0u;

		if (e_IMU_NORMAL_MODE == (IMU_RUNNING_MODE_e)u8_mode)
		{
			s_eImuModeSetSta = e_IMU_NORMAL_SET_OK;
		}
		else if (e_IMU_SELFSTUDY_MODE == (IMU_RUNNING_MODE_e)u8_mode)
		{
			s_eImuModeSetSta = e_IMU_SELFSTUDY_SET_OK;
		}
		else
		{
			s_eImuModeSetSta = e_IMU_FCT_SET_OK;
		}
	}

	s_eImuRunMode = (IMU_RUNNING_MODE_e)u8_mode;
	return E_OK;
}	
void IMU_AccDataCalc(int8_t calcNum)
{
	uint8_t l_ui8Idx = 0;
	int32_t l_i32AccXSum = 0;
	int32_t l_i32AccYSum = 0;
	int32_t l_i32AccZSum = 0;
	for(l_ui8Idx = 0; l_ui8Idx < calcNum; l_ui8Idx++)
	{
		l_i32AccXSum = g_aui8ImuAccXbuff[l_ui8Idx] > 2047 ? (l_i32AccXSum - (int32_t)(4096 - g_aui8ImuAccXbuff[l_ui8Idx])) :\
												 (l_i32AccXSum + g_aui8ImuAccXbuff[l_ui8Idx]);
		l_i32AccYSum = g_aui8ImuAccYbuff[l_ui8Idx] > 2047 ? (l_i32AccYSum - (int32_t)(4096 - g_aui8ImuAccYbuff[l_ui8Idx])) :\
												 (l_i32AccYSum + g_aui8ImuAccYbuff[l_ui8Idx]);
		l_i32AccZSum = g_aui8ImuAccZbuff[l_ui8Idx] > 2047 ? (l_i32AccZSum - (int32_t)(4096 - g_aui8ImuAccZbuff[l_ui8Idx])) :\
												 (l_i32AccZSum + g_aui8ImuAccZbuff[l_ui8Idx]);
	}

	l_i32AccXSum = 0 - l_i32AccXSum;
	if(e_IMU_FCT_MODE != s_eImuRunMode)
	{
		s_aui16ImuAccelData[0] = (int16_t)(l_i32AccXSum / calcNum) - g_aui16ImuCalibrationData[0];
		s_aui16ImuAccelData[1] = (int16_t)(l_i32AccYSum / calcNum) - g_aui16ImuCalibrationData[1];
		s_aui16ImuAccelData[2] = (int16_t)(l_i32AccZSum / calcNum) - g_aui16ImuCalibrationData[2];
	}
	else
	{
		s_aui16ImuAccelData[0] = (int16_t)(l_i32AccXSum / calcNum);
		s_aui16ImuAccelData[1] = (int16_t)(l_i32AccYSum / calcNum);
		s_aui16ImuAccelData[2] = (int16_t)(l_i32AccZSum / calcNum);
	}

	if(e_IMU_SELFSTUDY_MODE == s_eImuRunMode)
	{
		g_ai16ImuAccelStuData[0] = s_aui16ImuAccelData[0];
		g_ai16ImuAccelStuData[1] = s_aui16ImuAccelData[1];
		g_ai16ImuAccelStuData[2] = s_aui16ImuAccelData[2];
	}

	// self study finished 
	if(0 != g_i16IsEcuStudy)//Use the self-learned data to perform another calibration, and at the same time, carry out a three-axis conversion.
	{
		g_tImuAccCalcVal.x = (float)((float)(s_aui16ImuAccelData[2] - g_ai16ImuAccelStuData[2])/ 512.0f);
		g_tImuAccCalcVal.y = (float)((float)(s_aui16ImuAccelData[0] - g_ai16ImuAccelStuData[0]) / 512.0f);
		g_tImuAccCalcVal.z = (float)((float)(s_aui16ImuAccelData[1] - g_ai16ImuAccelStuData[1] + 512) / 512.0f);
	}
	else	// self study not finished
	{
		g_tImuAccCalcVal.x = (float)((float)s_aui16ImuAccelData[0] / 512.0f);
		g_tImuAccCalcVal.y = (float)((float)s_aui16ImuAccelData[1] / 512.0f);
		g_tImuAccCalcVal.z = (float)((float)s_aui16ImuAccelData[2] / 512.0f);
	}

	g_tImuAnglesVal.pitch = atan2f(g_tImuAccCalcVal.y, sqrtf(g_tImuAccCalcVal.x * g_tImuAccCalcVal.x + g_tImuAccCalcVal.z * g_tImuAccCalcVal.z)) * 180.0f / IMU_CALC_PI;
	g_tImuAnglesVal.roll = atan2f(-g_tImuAccCalcVal.x, g_tImuAccCalcVal.z) * 180.0f / IMU_CALC_PI;
}

void IMU_NormalRun(void )		// 
{
	static uint8_t s_ui8AccDataIdxPre = 0;
	static uint8_t s_ui8stuCnt = 0;
	if(e_IMU_NORMAL_MODE != s_eImuRunMode)
	{
		return;
	}
	if((0 == s_ui8NorAccDataReady) || (s_ui8AccDataIdxPre == s_ui8AccDataIdx))
	{
		s_ui8stuCnt ++;
		if(150U <= s_ui8stuCnt)
		{
			s_ui8stuCnt = 0u;
			g_eImuErrStatus = e_IMU_I2C_ERR;
			s_eImuModeSetSta = e_IMU_ERROR_SET;
			s_eImuRunMode = e_IMU_ERROR_MODE;
		}
		return;
	}
	s_ui8stuCnt = 0;
	s_ui8AccDataIdxPre = s_ui8AccDataIdx;
	g_eImuErrStatus = e_IMU_RUN_OK;
	IMU_AccDataCalc(IMU_NORMAL_DATA_BUFF_SIZE);
}


void IMU_SleepRun(void)	//
{
	if ((e_IMU_SLEEP_MODE != s_eImuRunMode) || (e_IMU_SLEEP_SET_OK != s_eImuModeSetSta))
	{
		return;
	}
	IMU_ReadRegSync(IMU_SYS_MODE_ADDR, g_aui8ImuRxBuff, 1);	// read the system mode register
}
#include "RTE.h"
#include "com_cfg.h"
Std_ReturnType IMU_LearnProcessTrigger(void)
{
	Std_ReturnType ret = E_NOT_OK;
//	float32 VehSpd = Com_VehSpd;
//	uint8 VehSpdVld = Com_VehSpdVld;
//	float32 VCULatSlopForDisp = Com_VCULatSlopForDisp;
//	float32 VCULgtSlopForDisp = Com_VCULgtSlopForDisp;
//	uint8 l_ui8VcSts = 0;
//	(void)RTE_Read_Com_VehSpdVld(&VehSpdVld);
//	(void)RTE_Read_Com_VehSpd(&VehSpd);
//	(void)RTE_Read_Com_VCULatSlopForDisp(&VCULatSlopForDisp);
//	(void)RTE_Read_Com_VCULgtSlopForDisp(&VCULgtSlopForDisp);
//	#ifdef ECU_ADDRESS_DPOD
//	(void)RTE_Read_Com_DoorDrvrVcSts(&l_ui8VcSts);
//	#endif
//	#ifdef ECU_ADDRESS_LPOD
//	(void)RTE_Read_Com_DoorLeReVcSts(&l_ui8VcSts);
//	#endif
//	#ifdef ECU_ADDRESS_PPOD
//	(void)RTE_Read_Com_DoorPassVcSts(&l_ui8VcSts);
//	#endif
//	#ifdef ECU_ADDRESS_RPOD
//	(void)RTE_Read_Com_DoorRiReVcSts(&l_ui8VcSts);
//	#endif
//
//	if((CDD_GetBatmVolt() < 9000)||(CDD_GetBatmVolt() > 18000))
//	{
//		s_eAccStuStu = e_IMU_STUDY_ABORTED;
//		ret = E_NOT_OK;
//	}
//	else if(((VehSpd >= 5)&&(1 == VehSpdVld))||(VCULatSlopForDisp > 1)||(VCULatSlopForDisp < -1)
//			||(VCULgtSlopForDisp > 1)||(VCULgtSlopForDisp < -1)
//			||(l_ui8VcSts != 1))
//	{
//		s_eAccStuStu = e_IMU_STUDY_ABORTED;
//		ret = E_NOT_OK;
//	}
//	else
//	{
//		s_ui8AccDataIdx = 0u;
//		s_ui8StuAccDataReady = 0u;
//		s_ui8FctAccDataReady = 0u;
//		s_ui8NorAccDataReady = 0u;
//		s_eAccStuStu = e_IMU_STUDY_EXECUTING;
//		(void)IMU_SetPowerMode(e_IMU_SELFSTUDY_MODE);
//		ret = E_OK;
//	}
	ret = E_OK;
	return ret;
}
Std_ReturnType IMU_LearnProcessGetResult(uint8_t *result)
{
	*result = (uint8_t)s_eAccStuStu;
	return E_OK;
}

void IMU_SelfStudyRun(void)	//
{
	static uint8_t s_ui8stuCnt = 0;
	if(e_IMU_SELFSTUDY_MODE != s_eImuRunMode)
	{
		return;
	}
	if(0 == s_ui8StuAccDataReady)
	{
		s_ui8stuCnt++;
		if (150U <= s_ui8stuCnt)
		{
			s_ui8stuCnt = 0u;
			s_eAccStuStu = e_IMU_STUDY_I2C_ERR;
			g_i16IsEcuStudy = g_ai16ImuDataBlock[0];
			g_eImuErrStatus = e_IMU_I2C_ERR;
			s_eImuModeSetSta = e_IMU_ERROR_SET;
			s_eImuRunMode = e_IMU_ERROR_MODE;
		}
		return;
	}
	s_ui8stuCnt = 0;
	g_eImuErrStatus = e_IMU_RUN_OK;
	IMU_AccDataCalc(IMU_STUDY_DATA_BUFF_SIZE);
	g_ai16ImuDataBlock[0] = 1;	// self study finished
	g_ai16ImuDataBlock[1] = g_ai16ImuAccelStuData[0];
	g_ai16ImuDataBlock[2] = g_ai16ImuAccelStuData[1];
	g_ai16ImuDataBlock[3] = g_ai16ImuAccelStuData[2];
	if(E_OK != Imu_StudyDataWirteNvm())	// NvM 
	{
		s_eAccStuStu = e_IMU_STUDY_NVM_ERR;
		g_i16IsEcuStudy = 0;
		(void)IMU_SetPowerMode(e_IMU_NORMAL_MODE);
		return;
	}
	s_eAccStuStu = e_IMU_STUDY_COMPLETED;
	g_i16IsEcuStudy = 1;
	s_ui8NorAccDataReady = 0u;
	s_ui8AccDataIdx = 0u;
	(void)IMU_SetPowerMode(e_IMU_NORMAL_MODE);
}
void IMU_ErrModeRun(void)
{
	static uint8_t s_ui8stuCnt = 0;
	if(e_IMU_ERROR_MODE != s_eImuRunMode)
	{
		return;
	}
	s_ui8stuCnt++;
	if (s_ui8stuCnt % 10U == 0)
	{
		s_ui8stuCnt = 0;
		IMU_AllRegsInitSync();
	}
}
#define IMU_OUT_X_INDEX_L 	0x00
#define IMU_OUT_X_INDEX_H  (IMU_OUT_X_INDEX_L + 1)
#define IMU_OUT_Y_INDEX_L  (IMU_OUT_X_INDEX_L + 2)
#define IMU_OUT_Y_INDEX_H  (IMU_OUT_X_INDEX_L + 3)
#define IMU_OUT_Z_INDEX_L  (IMU_OUT_X_INDEX_L + 4)
#define IMU_OUT_Z_INDEX_H  (IMU_OUT_X_INDEX_L + 5)

Std_ReturnType IMU_ReadAccData(int16_t *ax, int16_t *ay, int16_t *az)
{
	*ax = s_aui16ImuAccelData[0];
	*ay = s_aui16ImuAccelData[1];
	*az = s_aui16ImuAccelData[2];
	return E_OK;
}

Std_ReturnType IMU_ReadAccDataOffset(int16_t *axo, int16_t *ayo, int16_t *azo)
{
	*axo = g_ai16ImuAccelStuData[0];
	*ayo = g_ai16ImuAccelStuData[1];
	*azo = g_ai16ImuAccelStuData[2];
	return E_OK;
}
void FXLS8961_INT1_CallBack()
{
	if ((e_IMU_NORMAL_SET_OK == s_eImuModeSetSta) ||
		(e_IMU_SELFSTUDY_SET_OK == s_eImuModeSetSta) ||
		(e_IMU_FCT_SET_OK == s_eImuModeSetSta))
	{
		if(s_eImuRunMode == e_IMU_NORMAL_MODE)
		{
			if(s_ui8AccDataIdx == IMU_NORMAL_DATA_BUFF_SIZE)		// 
			{
				s_ui8NorAccDataReady = 1u;
			}
			s_ui8AccDataIdx = (s_ui8AccDataIdx % IMU_NORMAL_DATA_BUFF_SIZE);
		}
		else if(s_eImuRunMode == e_IMU_SELFSTUDY_MODE)
		{	
			if(s_ui8AccDataIdx == IMU_STUDY_DATA_BUFF_SIZE)		// 
			{
				s_ui8StuAccDataReady = 1u;
			}
			s_ui8AccDataIdx = (s_ui8AccDataIdx % IMU_STUDY_DATA_BUFF_SIZE);
		}
		else
		{
			if(s_ui8AccDataIdx == IMU_FCT_DATA_BUFF_SIZE)		// 
			{
				s_ui8FctAccDataReady = 1u;
			}
			s_ui8AccDataIdx = (s_ui8AccDataIdx % IMU_FCT_DATA_BUFF_SIZE);
		}

		g_aui8ImuAccXbuff[s_ui8AccDataIdx] = (((uint16_t)g_aui8ImuRxBuff[IMU_OUT_X_INDEX_H] << 8U) & 0x0F00U) +\
									 ((uint16_t)g_aui8ImuRxBuff[IMU_OUT_X_INDEX_L] & 0x00FFU);
		g_aui8ImuAccYbuff[s_ui8AccDataIdx] = (((uint16_t)g_aui8ImuRxBuff[IMU_OUT_Y_INDEX_H] << 8U) & 0x0F00U) +\
									 ((uint16_t)g_aui8ImuRxBuff[IMU_OUT_Y_INDEX_L] & 0x00FFU);
		g_aui8ImuAccZbuff[s_ui8AccDataIdx] = (((uint16_t)g_aui8ImuRxBuff[IMU_OUT_Z_INDEX_H] << 8U) & 0x0F00U) +\
									 ((uint16_t)g_aui8ImuRxBuff[IMU_OUT_Z_INDEX_L] & 0x00FFU);

		s_ui8AccDataIdx++;

		IMU_ReadData(IMU_OUT_X_LSB_ADDR, g_aui8ImuRxBuff, 6);
	}
}

IMU_FCT_STA_e Cdd_ImuCalibrationAccResultGet(void)
{
	return s_eAccFctStu;
}

void Cdd_ImuCalibrationAccTriggerStart(void)
{
	s_ui8AccDataIdx = 0u;
	s_ui8StuAccDataReady = 0u;
	s_ui8FctAccDataReady = 0u;
	s_ui8NorAccDataReady = 0u;
	s_eAccFctStu = e_IMU_FCT_EXECUTING;
	(void)IMU_SetPowerMode(e_IMU_FCT_MODE);
}
void IMU_FctRun(void)
{
	static uint8_t l_ui8FctCnt = 0;
	if(e_IMU_FCT_MODE != s_eImuRunMode)
	{
		return;
	}
	if(0 == s_ui8FctAccDataReady)
	{
		l_ui8FctCnt ++;
		if(50U <= l_ui8FctCnt)
		{
			l_ui8FctCnt = 0u;
			g_eImuErrStatus = e_IMU_I2C_ERR;
			s_eImuModeSetSta = e_IMU_ERROR_SET;
			s_eImuRunMode = e_IMU_ERROR_MODE;
		}
		return;
	}
	l_ui8FctCnt = 0;
	g_eImuErrStatus = e_IMU_RUN_OK;
	IMU_AccDataCalc(IMU_FCT_DATA_BUFF_SIZE);
	g_aui16ImuCalibrationData[0] = s_aui16ImuAccelData[0];
	g_aui16ImuCalibrationData[1] = s_aui16ImuAccelData[1];
	g_aui16ImuCalibrationData[2] = s_aui16ImuAccelData[2] - 512;	//

	g_ai16ImuDataBlock[4] = g_aui16ImuCalibrationData[0]; 	//
	g_ai16ImuDataBlock[5] = g_aui16ImuCalibrationData[1];
	g_ai16ImuDataBlock[6] = g_aui16ImuCalibrationData[2];
	if(E_OK != Imu_StudyDataWirteNvm())	// NvM 
	{
		s_eAccFctStu = e_IMU_FCT_NVM_ERR;
		(void)IMU_SetPowerMode(e_IMU_NORMAL_MODE);
		return;
	}
	s_eAccFctStu = e_IMU_FCT_COMPLETED;
	s_ui8AccDataIdx = 0u;
	s_ui8NorAccDataReady = 0u;
	(void)IMU_SetPowerMode(e_IMU_NORMAL_MODE);
}

void Cdd_ImuSpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr)
{
//    pFcspiHandle = pFcspiHandle;
//    bIsInIsr = bIsInIsr;
}








