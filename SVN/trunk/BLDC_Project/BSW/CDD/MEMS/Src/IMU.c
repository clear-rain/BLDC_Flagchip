/**
 * *********************************************************************************************************************
 * Copyright  (c)  2023-2025  Jin-Tech TECHNOLOGY CO.,LTD.
 * All Rights Reserved
 * Filename     : IMU.c
 * Description  :
 * Project      :
 * Note(s)      :
 * Update Record:
 * Version    Date           Modified by       DescriptionWhy & What is modified
 * V1.0       2025-01-23     Chunfeng.hong     Initial Version
 * AA.BB      YYYY.MM.DD     author            ****
 * *********************************************************************************************************************
 */
#include "IMU.h"
#include "IMU_Driver.h"
#include "IMU_Cfg.h"
#include "IMU_Diag.h"



//void IMU_IicInit(void)
//{
////WJF V2	FCIicGpioInit(0);
////WJF V2	BSP_FCIIC_Init();
//}




void Cdd_ImuInit(void)
{
//	IMU_DiagInit();
	IMU_SpiInit();
	IMU_AllRegsInitSync();
}

// volatile int8_t temptest = 0;
// volatile int16_t Pitchtest = 0;
// volatile int16_t Rolltest = 0;

void Cdd_ImuMainFunction(void)
{
//WJF V2	IMU_AllRegsInitSync();
//WJF V2	IMU_NormalRun();	// Normal mode

//wjf	IMU_SleepRun();		// Low-power sleep mode

//wjf	IMU_SelfStudyRun();	// Self-learning mode

//wjf	IMU_ErrModeRun(); 	// I2C error deal

//wjf	IMU_FctRun();		// FCT mode to calibrate the IMU

	// IMU_ReadTempC(&temptest);
	// IMU_ReadIMUPitch(&Pitchtest);
	// IMU_ReadIMURoll(&Rolltest);
}
