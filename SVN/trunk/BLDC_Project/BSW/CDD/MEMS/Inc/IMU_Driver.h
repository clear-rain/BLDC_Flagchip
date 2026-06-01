#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

//#include "Platform.h"
#include "main.h"

#define IMU_FCT_DATA_BUFF_SIZE		30U
#define IMU_STUDY_DATA_BUFF_SIZE	100U
#define IMU_NORMAL_DATA_BUFF_SIZE	20U


extern void IMU_AllRegsInitSync(void);
extern void IMU_NormalRun(void);
extern void IMU_SleepRun(void);
extern void IMU_SelfStudyRun(void);
extern void IMU_ErrModeRun(void);
extern void IMU_FctRun(void);
void Cdd_ImuSpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);

#endif // IMU_DRIVER_H


