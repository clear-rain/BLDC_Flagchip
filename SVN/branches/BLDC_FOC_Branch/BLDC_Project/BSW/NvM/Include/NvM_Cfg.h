/*
 * NvM_Cfg.h
 *
 *  Created on: 2024年7月10日
 *      Author: 22093
 */

#ifndef SOURCES_NVM_INCLUDE_NVM_CFG_H_
#define SOURCES_NVM_INCLUDE_NVM_CFG_H_

#include "typedef.h"
#include "v_def.h"
#include "Nvm_BlockID_Cfg.h"
#ifndef ECU_ADDRESS_BLDC
#include "uds_did.h"


#define NvM_BlockNumber        22u



#define DTC_BLOCK0 1
#define DCM27ERRORCNT 2
#define SEEDBLOCK  3
#define BlockLearningModeId 5
#define BlockSleepModeId 6
#define HallPosId 7
#define DID_F184_NVM_BLOCK_ID 27
#define OTAModestatus_NVM_BLOCK_ID  28
#define DID_F0FA_NVM_BLOCK_ID 29
#define DID_F190_NVM_BLOCK_ID 30
#define DID_F18C_NVM_BLOCK_ID 33
#define ProgrammingAtptNum_NVM_BLOCK_ID 31
#define ProgramDependencyCheck_NVM_BLOCK_ID 32


/*APP Store*/
typedef struct
{
	int16 NvRPODXXXZeroPosition;
	int16 NvRPODXXXHallPosn;
	uint8 NvRPODXXXHallPosnValid;
	uint8 NVRPODXXXCDC_ModSet;
	uint16 NVRRes16_2;
	uint32 NvRPODXXXLifeCycles;
	uint16 NVRRes16_3;
	uint8 NVRRes8_4;
	int16 NvR_IMUPitch;
	int16 NvR_IMURoll;
	uint32 NVRRes32_5;
	uint32 NVRRes32_6;
	uint32 NVRRes32_7;
	int8 NvRProtectionLastMotorTemperature;
	int8 NvRTempCompLastMotorTemperature;
	int8 NvRTempCompLastGearTemperature;
	uint8 NvRDoorHoldingStatus;
	uint8 NvRDoorNormingStatus;
	uint32 NVRRes32_8;
	uint32 NVRRes32_9;
	uint32 NVRRes32_10;
	uint32 NVRRes32_11;
	uint32 NVRRes32_12;
}EnterSleepMode_t;


typedef union
{
	uint8 Data[80];
	EnterSleepMode_t EnterSleepMode;

}EnterSleepModeUnion_t;


typedef struct
{
	uint8 NvRPODXXXImuSts;
	uint16 NvRSystemFrictionIndicatorClose;
	uint16 NvRSystemFrictionIndicatorOpen;
	uint8 NvRMotorBEMFLearned;
	uint8 NvRMotorKTLearned;
	uint16 NvRMotorResistanceLearned;
	uint16 NvRMaxHallcount;
	uint16 NvRLearnedBrakeFrictionClose;
	uint8 NvRLearnedMotorFrictionClose;
	uint8 NvRLearnedBrakeFrictionOpen;
	uint8 NvRLearnedMotorFrictionOpen;
	uint32 NvRLastValidEpochTimeStamp;
	int16 NvRServoAssistIdleHallcount;
	uint8 NvRLrnStatus;


}LearningMode_t;

typedef union
{
	uint8 Data[64];
	LearningMode_t LearningMode;

}LearningModeUnion_t;






typedef enum
{
	NVM_APP_COMMON,
	NVM_BOOT_SECURITY_KEYS,
    NVM_BOOT_INTEGRITY_CHECK,
    NVM_BOOT_SECURITY_LOG,
	NVM_DTC,
	NVM_BOOT_APP_EXCHANGE,
	NvM_RangeAddressNumber
}NvM_RangeAddressID_t;

typedef enum
{
	NVM_NO_ERROR = 0u,
	NVM_NO_SUPPORT,
	NVM_NO_STORE,
	NVM_ECC,
	NVM_CRC_FAIL,
	NVM_REACH_AGE,
}NvM_ErrorStatus_t;

typedef enum
{
	NVM_SECTOR_NO_ACTION = 0u,
	NVM_SECTOR_START,
	NVM_SECTOR_FINISH
}NvM_SectorAction_t;

typedef struct
{
	uint8_t  currentSector;
	uint8_t  tempSector;
	uint8_t	 eraseSector;
	boolean  reachAge;
	NvM_SectorAction_t  sectorAction;
	uint32_t currentAddr;
	uint32_t ageCycle;
	uint32_t eraseFailCycle;
} NvM_LogicalSector_t;


typedef struct
{
	uint32_t startAddr;
	uint32_t endAddr;
	uint16_t len;  //最小长度是8K，且必须是8K的整数倍
}NvM_SectorAddr_t;

typedef struct
{
	const NvM_SectorAddr_t  *SectorAddrr;
	uint8_t  SectorSize;  //大于等于2
	NvM_LogicalSector_t *SectorState;
} NvM_RangeAddress_t;

typedef struct
{
	uint16_t blockId;
	uint16_t dataLen; //8的倍数
	uint8_t *data;
	NvM_RangeAddress_t *rangeAddress;
} NvM_BlockConfig_t;

extern  NvM_RangeAddress_t NvM_RangeAddress[NvM_RangeAddressNumber];
extern  NvM_BlockConfig_t NvM_BlockCfg[NvM_BlockNumber];
extern uint32_t test_arr[64];
extern uint8 Diag27eroor[8];
extern sint32 NvmHallPosn[2];
extern EnterSleepModeUnion_t EnterSleepModeUnion;
extern LearningModeUnion_t LearningModeUnion;

#else

#define NvM_BlockNumber        2u

#define EncoderStrokeId 1
/* BLDC 版本同样增加编码器偏置 Block */
#define EncoderOffsetId 2

typedef enum
{
	NVM_APP_COMMON,
	NvM_RangeAddressNumber
}NvM_RangeAddressID_t;

typedef enum
{
	NVM_NO_ERROR = 0u,
	NVM_NO_SUPPORT,
	NVM_NO_STORE,
	NVM_ECC,
	NVM_CRC_FAIL,
	NVM_REACH_AGE,
}NvM_ErrorStatus_t;

typedef enum
{
	NVM_SECTOR_NO_ACTION = 0u,
	NVM_SECTOR_START,
	NVM_SECTOR_FINISH
}NvM_SectorAction_t;

typedef struct
{
	uint8_t  currentSector;
	uint8_t  tempSector;
	uint8_t	 eraseSector;
	boolean  reachAge;
	NvM_SectorAction_t  sectorAction;
	uint32_t currentAddr;
	uint32_t ageCycle;
	uint32_t eraseFailCycle;
} NvM_LogicalSector_t;


typedef struct
{
	uint32_t startAddr;
	uint32_t endAddr;
	uint16_t len;  //最小长度是8K，且必须是8K的整数倍
}NvM_SectorAddr_t;

typedef struct
{
	const NvM_SectorAddr_t  *SectorAddrr;
	uint8_t  SectorSize;  //大于等于2
	NvM_LogicalSector_t *SectorState;
} NvM_RangeAddress_t;

typedef struct
{
	uint16_t blockId;
	uint16_t dataLen; //8的倍数
	uint8_t *data;
	NvM_RangeAddress_t *rangeAddress;
} NvM_BlockConfig_t;

extern  NvM_RangeAddress_t NvM_RangeAddress[NvM_RangeAddressNumber];
extern  NvM_BlockConfig_t NvM_BlockCfg[NvM_BlockNumber];

extern sint32 NvMEncoderStroke[2];
extern float NvMEncoderOffset[2];


#endif

#endif /* SOURCES_NVM_INCLUDE_NVM_CFG_H_ */
