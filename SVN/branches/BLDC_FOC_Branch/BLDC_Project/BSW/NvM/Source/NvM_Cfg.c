/*
 * NvM_Cfg.c
 *
 *  Created on: 2024年7月10日
 *      Author: 22093
 */



#include "NvM_Cfg.h"
#include "IMU.h"
#ifndef ECU_ADDRESS_BLDC
#include "uds_Dem.h"
#include "security_storage.h"
#include "security_integrityCheck.h"
#include "security_log.h"



/*****************************************************************************************************************************8*/

#define COMMON_SECTOR_SIZE					(2u)
#define SECURE_KEY_SECTOR_SIZE         		(2U)
#define INTEGRITY_CHECK_SECTOR_SIZE         (2U)
#define SECURE_LOG_SECTOR_SIZE         		(2U)
#define DTC_SECTOR_SIZE						(2U)
#define BOOT_APP_EXCHANGE_SECTOR_SIZE		(2U)


const NvM_SectorAddr_t SectorAddr_COMMMON[COMMON_SECTOR_SIZE] = 
{
	{0x01100000, 0x01101000, 0x1000},  //Sector0 4K
	{0x01101000, 0x01102000, 0x1000},  //Sector1 4K
};

const NvM_SectorAddr_t SectorAddr_Security_Keys[SECURE_KEY_SECTOR_SIZE] =
{
	{0x01102000, 0x01103000, 0x1000},  //Sector0 4K
	{0x01103000, 0x01104000, 0x1000},  //Sector1 4K
};

const NvM_SectorAddr_t SectorAddr_Integrity_Check[INTEGRITY_CHECK_SECTOR_SIZE] =
{
	{0x01104000, 0x01105000, 0x1000},  //Sector0 4K
	{0x01105000, 0x01106000, 0x1000},  //Sector1 4K
};

const NvM_SectorAddr_t SectorAddr_Security_Log[SECURE_LOG_SECTOR_SIZE] =
{
	{0x01106000, 0x01108000, 0x2000},  //Sector0 8K
	{0x01108000, 0x0110A000, 0x2000},  //Sector1 8K
};

const NvM_SectorAddr_t SectorAddr_DTC[DTC_SECTOR_SIZE] =
{
	{0x0110A000, 0x0110C000, 0x2000},  //Sector0 8K
	{0x0110C000, 0x0110E000, 0x2000},  //Sector0 8K
};
const NvM_SectorAddr_t SectorAddr_Boot_App_Exchange[BOOT_APP_EXCHANGE_SECTOR_SIZE] =
{
	{0x0110E000, 0x0110E800, 0x800},  //Sector0 2K
	{0x0110E800, 0x0110F000, 0x800},  //Sector0 2K
};
static NvM_LogicalSector_t LogicalSectorState[NvM_RangeAddressNumber] = {0};

 NvM_RangeAddress_t NvM_RangeAddress[NvM_RangeAddressNumber] =
{
	{SectorAddr_COMMMON, COMMON_SECTOR_SIZE, &LogicalSectorState[NVM_APP_COMMON]},
	{SectorAddr_Security_Keys, SECURE_KEY_SECTOR_SIZE, &LogicalSectorState[NVM_BOOT_SECURITY_KEYS]},
	{SectorAddr_Integrity_Check, INTEGRITY_CHECK_SECTOR_SIZE, &LogicalSectorState[NVM_BOOT_INTEGRITY_CHECK]},
	{SectorAddr_Security_Log, SECURE_LOG_SECTOR_SIZE, &LogicalSectorState[NVM_BOOT_SECURITY_LOG]},
	{SectorAddr_DTC, DTC_SECTOR_SIZE, &LogicalSectorState[NVM_DTC]},
	{SectorAddr_Boot_App_Exchange, BOOT_APP_EXCHANGE_SECTOR_SIZE, &LogicalSectorState[NVM_BOOT_APP_EXCHANGE]}
};

uint32_t test_arr[64] = {0};
uint8  Diag27eroor[8] = {0};
int16_t g_ai16ImuDataBlock[16] = {0};
sint32 NvmHallPosn[2] = {0};
uint8 RandomSeedArray[8];
uint8_t NVM_MirrorBlockDataId_OTAModestatus[8] = {0};
#define SEEDADDRESS RandomSeedArray

/*APP Store*/
EnterSleepModeUnion_t EnterSleepModeUnion;
LearningModeUnion_t  LearningModeUnion;
/*APP Store*/


 NvM_BlockConfig_t NvM_BlockCfg[NvM_BlockNumber] =
{
	/*blockId,                 dataLen,       			data,                            rangeAddress                          */
	{DTC_BLOCK0,      		   600,      		        &(DTC_Controller.data[0]), 		 &NvM_RangeAddress[NVM_DTC]},
	{DCM27ERRORCNT,      		 8,      				Diag27eroor, 					 &NvM_RangeAddress[NVM_APP_COMMON]},
	{SEEDBLOCK,      	         8,      				SEEDADDRESS, 		             &NvM_RangeAddress[NVM_APP_COMMON]},
	{CDD_IMU_NVM_NUM,      		16,      				(uint8*)g_ai16ImuDataBlock, 	 &NvM_RangeAddress[NVM_APP_COMMON]},
	{BlockLearningModeId,      	64,      				LearningModeUnion.Data, 		 &NvM_RangeAddress[NVM_APP_COMMON]},
	{BlockSleepModeId,      	80,      				EnterSleepModeUnion.Data, 		 &NvM_RangeAddress[NVM_APP_COMMON]},
	{DID_F184_NVM_BLOCK_ID, sizeof(NVM_MirrorBlockDataId_DID_F184), NVM_MirrorBlockDataId_DID_F184,  &NvM_RangeAddress[NVM_BOOT_APP_EXCHANGE]},
	{OTAModestatus_NVM_BLOCK_ID, sizeof(NVM_MirrorBlockDataId_OTAModestatus),NVM_MirrorBlockDataId_OTAModestatus,  &NvM_RangeAddress[NVM_BOOT_APP_EXCHANGE]},
	{DID_F0FA_NVM_BLOCK_ID, sizeof(NVM_MirrorBlockDataId_DID_F0FA),NVM_MirrorBlockDataId_DID_F0FA,  &NvM_RangeAddress[NVM_BOOT_APP_EXCHANGE]},
	{DID_F190_NVM_BLOCK_ID, sizeof(NVM_MirrorBlockDataId_DID_F190),NVM_MirrorBlockDataId_DID_F190,  &NvM_RangeAddress[NVM_BOOT_APP_EXCHANGE]},
	{ProgrammingAtptNum_NVM_BLOCK_ID, sizeof(NVM_MirrorBlockDataId_ProgrammingAtptNum),NVM_MirrorBlockDataId_ProgrammingAtptNum,  &NvM_RangeAddress[NVM_APP_COMMON]},
	{ProgramDependencyCheck_NVM_BLOCK_ID, sizeof(NVM_MirrorBlockDataId_ProgramDependencyCheck),NVM_MirrorBlockDataId_ProgramDependencyCheck,  &NvM_RangeAddress[NVM_APP_COMMON]},
	{HallPosId,      					 8,      				(uint8*)NvmHallPosn, 					 &NvM_RangeAddress[NVM_APP_COMMON]},
	{DID_F18C_NVM_BLOCK_ID, sizeof(NVM_MirrorBlockDataId_DID_F18C),NVM_MirrorBlockDataId_DID_F18C,  &NvM_RangeAddress[NVM_BOOT_APP_EXCHANGE]},

	/*security related start*/
	{SECURITY_KEY_NVM_BLOCK_ID, sizeof(tSecKeyStorage), (uint8 *)&NVM_MirrorSecKeyStorage, (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_KEYS]},
//	{ITGCHK_NVM_BLOCK_ID_0, sizeof(tBlockContext), (uint8 *)&blockContext[0], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_INTEGRITY_CHECK]},
//	{ITGCHK_NVM_BLOCK_ID_1, sizeof(tBlockContext), (uint8 *)&blockContext[1], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_INTEGRITY_CHECK]},
//	{ITGCHK_NVM_BLOCK_ID_2, sizeof(tBlockContext), (uint8 *)&blockContext[2], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_INTEGRITY_CHECK]},
	{SECURITY_LOG_MAC_NVM_BLOCK_ID, sizeof(EvtRecordsMac), (uint8 *)&EvtRecordsMac, (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_LOG]},
	{SECURITY_LOG_NVM_BLOCK0_ID, sizeof(EvtRecords[0]), (uint8 *)&EvtRecords[0], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_LOG]},
	{SECURITY_LOG_NVM_BLOCK1_ID, sizeof(EvtRecords[1]), (uint8 *)&EvtRecords[1], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_LOG]},
//	{SECURITY_LOG_NVM_BLOCK2_ID, sizeof(EvtRecords[2]), (uint8 *)&EvtRecords[2], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_LOG]},
//	{SECURITY_LOG_NVM_BLOCK3_ID, sizeof(EvtRecords[3]), (uint8 *)&EvtRecords[3], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_LOG]},
//	{SECURITY_LOG_NVM_BLOCK4_ID, sizeof(EvtRecords[4]), (uint8 *)&EvtRecords[4], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_LOG]},
//	{SECURITY_LOG_NVM_BLOCK5_ID, sizeof(EvtRecords[5]), (uint8 *)&EvtRecords[5], (NvM_RangeAddress_t *)&NvM_RangeAddress[NVM_BOOT_SECURITY_LOG]},
	/*security related stop*/
};
#else

#define COMMON_SECTOR_SIZE					(2u)

const NvM_SectorAddr_t SectorAddr_COMMMON[COMMON_SECTOR_SIZE] =
{
	{0x01100000, 0x01101000, 0x1000},  //Sector0 4K
	{0x01101000, 0x01102000, 0x1000},  //Sector1 4K
};

static NvM_LogicalSector_t LogicalSectorState[NvM_RangeAddressNumber] = {0};

 NvM_RangeAddress_t NvM_RangeAddress[NvM_RangeAddressNumber] =
{
	{SectorAddr_COMMMON, COMMON_SECTOR_SIZE, &LogicalSectorState[NVM_APP_COMMON]},
};

sint32 NvMEncoderStroke[2] = {0};
float NvMEncoderOffset[2] = {0.0f, 0.0f};


 NvM_BlockConfig_t NvM_BlockCfg[NvM_BlockNumber] =
{
	/*blockId,                 dataLen,        			data,                            rangeAddress                          */
	{EncoderStrokeId,      	8,      				(uint8*)NvMEncoderStroke, 	&NvM_RangeAddress[NVM_APP_COMMON]},
	{EncoderOffsetId,       	8,      				(uint8*)NvMEncoderOffset, 	&NvM_RangeAddress[NVM_APP_COMMON]},

};
#endif
