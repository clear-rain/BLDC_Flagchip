#ifndef IMU_TYPES_H
#define IMU_TYPES_H

//#include "Platform.h"

typedef enum
{
	e_IMU_CHIPID_OK = 0,
	e_IMU_CHIPID_ERR,
}IMU_CHIPID_STA_e;

typedef enum
{
	e_IMU_RUN_OK= 0,
	e_IMU_RUN_NOT_LEARN,
	e_IMU_I2C_ERR,
	e_IMU_TWO_ERR
} IMU_ERR_STA_e;

typedef enum
{
	e_IMU_STUDY_COMPLETED = 0,
	e_IMU_STUDY_ABORTED,
	e_IMU_STUDY_EXECUTING,
	e_IMU_STUDY_NVM_ERR,
	e_IMU_STUDY_I2C_ERR,
	e_IMU_STUDY_ERROR
} IMU_STUDY_STA_e;

typedef enum
{
	e_IMU_FCT_COMPLETED = 0,
	e_IMU_FCT_ABORTED,
	e_IMU_FCT_EXECUTING,
	e_IMU_FCT_NVM_ERR,
	e_IMU_FCT_I2C_ERR,
	e_IMU_FCT_ERROR
} IMU_FCT_STA_e;

typedef enum
{
	e_IMU_NORMAL_SET_OK = 0,
	e_IMU_SLEEP_SET_OK,
	e_IMU_STANDBY_SET_OK,
	e_IMU_SELFSTUDY_SET_OK,
	e_IMU_FCT_SET_OK,
	e_IMU_ERROR_SET
}IMU_MODE_SET_STA_e;

typedef enum
{
	e_IMU_NORMAL_MODE = 0,
	e_IMU_SLEEP_MODE,
	e_IMU_SELFSTUDY_MODE,
	e_IMU_FCT_MODE,
	e_IMU_ERROR_MODE
}IMU_RUNNING_MODE_e;

typedef struct {
    float x;
    float y;
    float z;
} IMU_Acceleration_t;

typedef struct {
    float pitch;
    float roll;
} IMU_EulerAngles_t;

#endif // IMU_TYPES_H


