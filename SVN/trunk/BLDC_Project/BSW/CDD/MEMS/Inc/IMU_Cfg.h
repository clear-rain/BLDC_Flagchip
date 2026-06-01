#ifndef IMU_CFG_H
#define IMU_CFG_H

//#include "Platform.h"
#include "FreeRTOS.h"	
#include "task.h"
#include "Can_Hw.h"
#include "BspSpi.h"


#define IMU_I2C_ADDR 			0x18


#define IMU_PROD_REV_VAL 		0x14U
#define IMU_WHOAMI_VAL			0x81U
/****************       FXLS8961 All register addr define start     ************************* */
#define IMU_INT_STATUS_ADDR 	0x00U
#define IMU_TEMP_OUT_ADDR		0x01U
#define IMU_VECM_LSB_ADDR		0x02U
#define IMU_VECM_MSB_ADDR		0x03U
#define IMU_OUT_X_LSB_ADDR		0x04U
#define IMU_OUT_X_MSB_ADDR		0x05U
#define IMU_OUT_Y_LSB_ADDR		0x06U
#define IMU_OUT_Y_MSB_ADDR		0x07U
#define IMU_OUT_Z_LSB_ADDR		0x08U
#define IMU_OUT_Z_MSB_ADDR		0x09U

//Output Buffer Configuration and Status
#define IMU_BUF_STATUS_ADDR 	0x0BU
#define IMU_BUF_X_LSB_ADDR 		0x0CU
#define IMU_BUF_X_MSB_ADDR 		0x0DU
#define IMU_BUF_Y_LSB_ADDR 		0x0EU
#define IMU_BUF_Y_MSB_ADDR 		0x0FU
#define IMU_BUF_Z_LSB_ADDR 		0x10U
#define IMU_BUF_Z_MSB_ADDR 		0x11U
//Device identification
#define IMU_RPOD_REV_ADDR 		0x12U
#define IMU_WHOAMI_ADDR 		0x13U
//System status register
#define IMU_SYS_MODE_ADDR 		0x14U
//Device configuration and control registers
#define IMU_SENS_CONFIG1_ADDR 	0x15U
#define IMU_SENS_CONFIG2_ADDR 	0x16U
#define IMU_SENS_CONFIG3_ADDR 	0x17U
#define IMU_SENS_CONFIG4_ADDR 	0x18U
#define IMU_SENS_CONFIG5_ADDR 	0x19U

#define IMU_WAKE_IDLE_LSB_ADDR 	0x1AU
#define IMU_WAKE_IDLE_MSB_ADDR 	0x1BU
#define IMU_SLEEP_IDLE_LSB_ADDR 	0x1CU
#define IMU_SLEEP_IDLE_MSB_ADDR 	0x1DU

#define IMU_ASLP_COUNT_LSB_ADDR 	0x1EU
#define IMU_ASLP_COUNT_MSB_ADDR 	0x1FU

#define IMU_INT_EN_ADDR 			0x20
#define IMU_INT_PIN_SEL_ADDR 		0x21
//Zero-g offset compensation registers
#define IMU_OFF_X_ADDR 			0x22U
#define IMU_OFF_Y_ADDR 			0x23U
#define IMU_OFF_Z_ADDR 			0x24U
//Output Buffer Configuration
#define IMU_BUF_CONFIG1_ADDR 		0x26U
#define IMU_BUF_CONFIG2_ADDR 		0x27U
//Orientation detection function configuration and status
#define IMU_ORIENT_STATUS_ADDR 	0x28U
#define IMU_ORIENT_CONFIG_ADDR 	0x29U
#define IMU_ORIENT_DBCOUNT_ADDR 	0x2AU
#define IMU_ORIENT_BF_ZCOMP_ADDR 	0x2BU
#define IMU_ORIENT_THS_REG_ADDR 	0x2CU
//Sensor data change detection function configuration and status
#define IMU_SDCD_INT_SRC1_ADDR 	0x2DU
#define IMU_SDCD_INT_SRC2_ADDR 	0x2EU
#define IMU_SDCD_CONFIG1_ADDR 		0x2FU
#define IMU_SDCD_CONFIG2_ADDR 		0x30U
#define IMU_SDCD_OT_DBCNT_ADDR 	0x31U
#define IMU_SDCD_WT_DBCNT_ADDR		0x32U
#define IMU_SDCD_LTHS_LSB_ADDR 	0x33U
#define IMU_SDCD_LTHS_MSB_ADDR 	0x34U
#define IMU_SDCD_UTHS_LSB_ADDR 	0x35U
#define IMU_SDCD_UTHS_MSB_ADDR 	0x36U
#define IMU_SELF_TEST_CONFIG1_ADDR 0x37U
#define IMU_SELF_TEST_CONFIG2_ADDR 0x38U
/****************       FXLS8961 All register addr define end        ************************* */

#define IMU_DELAY_1MS (1UL / portTICK_PERIOD_MS)
#define IMU_DELAY_2MS (2UL / portTICK_PERIOD_MS)
#define IMU_DELAY_5MS (5UL / portTICK_PERIOD_MS)
#define IMU_DELAY_10MS (10UL / portTICK_PERIOD_MS)
#define IMU_DELAY_100MS (100UL / portTICK_PERIOD_MS)
#define IMU_DelayMs(x,y) vTaskDelayUntil(&(x),y)
#define IMU_SysTickGet() xTaskGetTickCount()

extern void IMU_SpiInit(void);

extern void IMU_WriteReg(uint8 addr, uint8 val);
extern void IMU_ReadData(uint8 addr, uint8 *val, uint8 len);
extern void IMU_ReadRegSync(uint8 addr, uint8 *pData, uint8 ui8_readCnt);

extern Std_ReturnType Imu_StudyDataWirteNvm(void);
extern Std_ReturnType Imu_StudyDataReadNvm(void);
#endif // IMU_CFG_H
