#ifndef IMU_H
#define IMU_H

// #include "Platform.h"
#include "IMU_Types.h"
#include "v_def.h"
#include "Can_Hw.h"

#define CDD_IMU_NVM_NUM 5U

extern void IMU_IicInit(void);
extern void Cdd_ImuInit(void);
extern void Cdd_ImuMainFunction(void);


// extern Std_ReturnType IMU_Init(void);
// extern Std_ReturnType IMU_Enable(uint8_t bEnable);
extern uint8 IMU_GetErrorStatus(void);
extern Std_ReturnType IMU_ReadAccData(int16_t *ax, int16_t *ay, int16_t *az);
extern Std_ReturnType IMU_ReadAccDataOffset(int16_t *axo, int16_t *ayo, int16_t *azo);// read calibration offset data
// extern Std_ReturnType IMU_SetAccScaleRange(uint8_t sRange);
// extern Std_ReturnType IMU_SetAccSampleRate(uint8_t sRate);
extern Std_ReturnType IMU_ReadIMUPitch(int16_t *IMUPitch);
extern Std_ReturnType IMU_ReadIMURoll(int16_t *IMURoll);
extern Std_ReturnType IMU_LearnProcessTrigger(void);
extern Std_ReturnType IMU_LearnProcessGetResult(uint8_t *result);
extern Std_ReturnType IMU_SetPowerMode(uint8_t mode);
extern Std_ReturnType IMU_ReadTempC(int8_t* sTemp);			// get chip temperature
extern IMU_FCT_STA_e Cdd_ImuCalibrationAccResultGet(void);
extern void Cdd_ImuCalibrationAccTriggerStart(void);

#endif // IMU_H


