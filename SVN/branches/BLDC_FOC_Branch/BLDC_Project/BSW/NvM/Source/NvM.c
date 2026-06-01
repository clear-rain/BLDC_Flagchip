/*
 * NvM.c
 *
 *  Created on: 2024年7月10日
 *      Author: 22093
 */
#include "NvM.h"
#include "string.h"
#include "arm_cortex_asm.h"

#define ECC_DISENABLE 	 (*(uint32_t *)(0x4001E010U)) |= 0x00000080U
#define ECC_ENABLE		 (*(uint32_t *)(0x4001E010U)) = 0x00000000U

 /*undetermined*/
#define NVM_BLOCK_MIN_SIZE 		8u
#define NVM_BLOCK_MAX_SIZE 		1024u
 /*undetermined*/

#define LOGICAL_SECTOR_HEAD_LENGTH  16
#define Sector_HEAD_FIRST_MARK  	0x01234567
#define Sector_HEAD_SECOND_MARK 	0x89ABCDEF
#define Sector_HEAD_THIRD_MARK  	0x456789AB

#define NVM_BLOCK_HEAD_MARK 	0x1234u
#define NVM_BLOCK_HEAD_OFFSET 	8u

#define NVM_AGE_CYCLE    		100000u
#define NVM_ERASE_FAIL_CYCLE    10u

typedef struct
{
	uint32_t ageCycle;
	uint32_t markFirst;
	uint32_t markSecond;
	uint32_t markThird;
}SectorHead_t;

typedef struct
{
	uint16_t blockId;
	uint16_t dataLen;
	uint16_t crc;
	uint16_t mask;
/*block的前8个字节信息*/
}NvM_BlockHead_t;  // NvM_BlockHead_t 的字节 长度必须和 NVM_BLOCK_HEAD_OFFSET 相等

typedef struct
{
	boolean  isFound;
	boolean  valid;
	boolean  requestWrite;
	boolean  writeAllFlag;
	uint16_t crc;
	uint16_t tempCrc;
	uint32_t address;
	uint32_t tempAddr;
	uint32_t backUpAddr;
	NvM_ErrorStatus_t errorStatus;
} NvM_BlockState_t;

static uint8_t tempData[NVM_BLOCK_HEAD_OFFSET+NVM_BLOCK_MAX_SIZE] = {0};

static NvM_BlockState_t NvM_BlockState[NvM_BlockNumber] = {0};

const uint16_t crctab[256] =
{
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
	0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
	0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
	0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
	0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
	0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
	0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
	0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
	0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
	0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
	0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
	0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
	0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
	0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
	0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
	0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
	0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
	0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
	0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
	0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
	0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
	0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
	0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};



static NVM_Status_t NVM_Status = NVM_UNINIT;
static NVM_Status_t NVM_JobStatus = NVM_JOB_NO_OPERATION;

static uint32_t NVM_timeOut = 0u;

static uint16_t SectorProcessBlockIndex = 0u;

static NVM_Status_t NVM_JobProgress;
static uint16_t NvM_BlockIndex = 0;
static NvM_RangeAddressID_t NvM_RangeAddressId;

static volatile boolean NvM_EccFlag = false;

static boolean NvM_ReachAge = false;

static uint16_t NvM_DataCrc(uint32_t *ptr, uint16_t size);
static uint16_t NVM_FindBlockIndex(uint16_t BlockId);
static void NVM_ReadRangeAddressData(NvM_RangeAddressID_t RangeAddressId);
static void NVM_CheckBlockIsValid(void);
static void NVM_ReadAllBlock(void);

static NVM_Status_t NVM_JobEraseHandle(NvM_RangeAddressID_t *RangeAddressId, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobEraseWait(NvM_RangeAddressID_t *RangeAddressId, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobErase(NvM_RangeAddressID_t *RangeAddressId, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobEraseExecute(NvM_RangeAddressID_t *RangeAddressId, NVM_Status_t *JobState);

static NVM_Status_t NVM_JobWriteCheckSectorAct(uint16_t *BlockIndex, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobWriteDataHandle(uint16_t *BlockIndex, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobWriteDataWait(uint16_t *BlockIndex, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobWriteValidBlock(uint16_t *BlockIndex, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobWrite(uint16_t *BlockIndex, NVM_Status_t *JobState);
static NVM_Status_t NVM_JobWriteExecute(uint16_t *BlockIndex, NVM_Status_t *JobState);


static uint16_t NVM_WriteAllBlockIndex = 0;
static boolean NVM_WriteAllFlag = 0;
static NVM_Status_t NVM_JobWriteAllBlock(uint16_t *BlockIndex, NVM_Status_t *JobState);

static uint16_t NvM_DataCrc(uint32_t *ptr, uint16_t size)
{
	uint16_t crc = 0xffff; /* initial value */
	uint32_t tmp;
	uint16_t i;
	uint32_t addrData;
	uint8_t data;

	for(i=0;i<size;i++)
	{
		addrData = ptr[i];

		data = addrData;
		tmp  = (crc>>8)^data;
		crc  = (crc<<8)^crctab[tmp];

		data = addrData>>8;
		tmp  = (crc>>8)^data;
		crc  = (crc<<8)^crctab[tmp];

		data = addrData>>16;
		tmp  = (crc>>8)^data;
		crc  = (crc<<8)^crctab[tmp];

		data = addrData>>24;
		tmp  = (crc>>8)^data;
		crc  = (crc<<8)^crctab[tmp];
	}
	return crc;
}

static uint16_t NVM_FindBlockIndex(uint16_t BlockId)
{
	uint16_t index = 0;
	for(index = 0;index <NvM_BlockNumber;index++)
	{
		if(NvM_BlockCfg[index].blockId == BlockId)
		{
			break;
		}
	}
	return index;
}

void NVM_Init(void)
{
	FLASHDRIVER_Init();

	uint32_t i = 0;
	for(i = 0;i < NvM_RangeAddressNumber;i++)
	{
		NVM_ReadRangeAddressData(i);
	}

	NVM_CheckBlockIsValid();
	NVM_ReadAllBlock();

	NVM_Status = NVM_IDLE;
}

NVM_Status_t NVM_WriteBlockData(uint16_t BlockId)
{
	NVM_Status_t ret = NVM_NOT_OK;
	uint16_t index;

	if((NVM_IDLE == NVM_Status)&&(uFLS_IDLE == FLS_GetStatus()))
	{
		index = NVM_FindBlockIndex(BlockId);
		if(index <NvM_BlockNumber)
		{
			if(false == NvM_BlockCfg[index].rangeAddress->SectorState->reachAge)
			{
				NvM_BlockIndex = index;
				NvM_BlockState[index].requestWrite = true;

				NVM_Status = NVM_BUSY;
				NVM_JobStatus = NVM_JOB_WRITE;
				NVM_JobProgress = NVM_JOB_WRITE_INITIAL;

				ret = NVM_OK;
			}
		}
	}

	return ret;
}


NVM_Status_t NVM_ReadBlockData(uint16_t BlockId)
{
	NVM_Status_t ret = NVM_NOT_OK;

	uint16_t index;
	const NvM_BlockConfig_t *Block;

	uint32_t *Addr;
	uint16_t expectCrc;
	uint16_t actualCrc;
	uint16_t len;
	uint32_t *tbackUpAddr;


	if((NVM_IDLE == NVM_Status)&&(uFLS_IDLE == FLS_GetStatus()))
	{
		index = NVM_FindBlockIndex(BlockId);
		if(index <NvM_BlockNumber)
		{
			Block = &NvM_BlockCfg[index];

			len = Block->dataLen >>2;

			NVM_Status = NVM_BUSY;

			if(true == NvM_BlockState[index].valid)
			{
				NvM_EccFlag = false;
				Addr = (uint32_t *)NvM_BlockState[index].address;
				expectCrc = *(Addr+1);
				Addr += 2;
				actualCrc = NvM_DataCrc(Addr, len);
				asm("nop");

				if(true == NvM_EccFlag)
				{
					NvM_BlockState[index].valid = false;
					NvM_BlockState[index].errorStatus = NVM_ECC;
					Block->rangeAddress->SectorState->sectorAction = NVM_SECTOR_START;
					/*Block->data is default value，are all 0xFF*/
					for(uint16_t size = 0;size <Block->dataLen;size++)
					{
						Block->data[size] = 0xFF;
					}
				}
				else
				{
					if(actualCrc == expectCrc)
					{
						for(uint16_t size = 0;size <len;size++)
						{
							((uint32_t *)Block->data)[size] = *Addr;
							Addr++;
						}
						NvM_BlockState[index].valid = true;
						NvM_BlockState[index].errorStatus = NVM_NO_ERROR;
					}
					else
					{
						tbackUpAddr = (uint32_t *)NvM_BlockState[index].backUpAddr;
						expectCrc = *(tbackUpAddr+1);
						tbackUpAddr += 2;
						actualCrc = NvM_DataCrc(tbackUpAddr, len);
						asm("nop");
						if(actualCrc == expectCrc)
						{
							/*Block->data is default value，read backup data*/
							for(uint16_t size = 0;size <len;size++)
							{
								((uint32_t *)Block->data)[size] = *tbackUpAddr;
								tbackUpAddr++;
							}
						}
						else
						{
							for(uint16_t size = 0;size <Block->dataLen;size++)
							{
								Block->data[size] = 0xFF;
							}
						}
						/*crc checking result not equal,perform a paging operation*/
						NvM_BlockState[index].valid = false;
						NvM_BlockState[index].errorStatus = NVM_CRC_FAIL;
						Block->rangeAddress->SectorState->sectorAction = NVM_SECTOR_START;
					}
				}

			}
			else
			{
				for(uint16_t size = 0;size <Block->dataLen;size++)
				{
					Block->data[size] = 0xFF;
				}
			}
			NVM_Status = NVM_IDLE;
			ret = NVM_OK;
		}
	}
	return ret;
}

void NVM_MainFunction(void)
{
	NVM_Status_t ret = NVM_OK;

    if(NVM_Status == NVM_BUSY)
    {
        switch(NVM_JobStatus)
        {
            case NVM_JOB_ERASE:
				ret = NVM_JobEraseExecute(&NvM_RangeAddressId, &NVM_JobProgress);
                break;

            case NVM_JOB_WRITE:
				ret = NVM_JobWriteExecute(&NvM_BlockIndex, &NVM_JobProgress);
                break;

            default:
				ret = NVM_OK;
                break;
        }

		if((NVM_NOT_OK == ret)|| (NVM_OK == ret))
		{
			NVM_Status = NVM_IDLE;
			NVM_timeOut = 0;

			FLS_SetStatusIdle();
		}
    }

	if(NVM_timeOut > 0)
	{
		NVM_timeOut--;
		if(0u == NVM_timeOut)
		{
			NVM_Status = NVM_IDLE;
			FLS_SetStatusIdle();
		}
	}
}

NVM_Status_t NVM_GetStatus(void)
{
	return NVM_Status;
}

static NVM_Status_t NVM_JobEraseHandle(NvM_RangeAddressID_t *RangeAddressId ,NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

	uint8_t eraseSector = 0;
	uint32_t startAddr;
	uint32_t len;

	eraseSector = NvM_RangeAddress[*RangeAddressId].SectorState->eraseSector;

	startAddr = NvM_RangeAddress[*RangeAddressId].SectorAddrr[eraseSector].startAddr;
	len =  NvM_RangeAddress[*RangeAddressId].SectorAddrr[eraseSector].len;

	FLS_SetEraseParameter(startAddr, len);
	FLS_SetStatusBusy();
	*JobState = NVM_JOB_ERASE_ING;
	ret = NVM_LOOP;

	return ret;
}

static NVM_Status_t NVM_JobEraseWait(NvM_RangeAddressID_t *RangeAddressId, NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

	FLS_MainFunction();
	if(FLS_GetStatus() == uFLS_BUSY)
	{
		*JobState = NVM_JOB_ERASE_ING;
		ret = NVM_PENDING;

	}
	else if(FLS_GetStatus() == uFLS_IDLE)
	{
		if(FLS_GetResult() == uFLS_OK)
		{
			if(NVM_SECTOR_START == NvM_RangeAddress[*RangeAddressId].SectorState->sectorAction)
			{
				NVM_JobStatus = NVM_JOB_WRITE;
				*JobState = NVM_JOB_WRITE_VALIDBLOCK;
				ret = NVM_PENDING;
			}
			else
			{
				ret = NVM_OK;
			}
			NvM_RangeAddress[*RangeAddressId].SectorState->eraseFailCycle = 0;
		}
		else if(FLS_GetResult() == uFLS_NOT_OK)
		{

			if(NVM_SECTOR_START == NvM_RangeAddress[*RangeAddressId].SectorState->sectorAction)
			{
				NVM_JobStatus = NVM_JOB_WRITE;
				*JobState = NVM_JOB_WRITE_VALIDBLOCK;
				ret = NVM_PENDING;
			}
			else
			{
				ret = NVM_NOT_OK;
			}

			if(NvM_RangeAddress[*RangeAddressId].SectorState->eraseFailCycle <NVM_ERASE_FAIL_CYCLE)
			{
				NvM_RangeAddress[*RangeAddressId].SectorState->eraseFailCycle++;
			}
			else
			{
				NvM_RangeAddress[*RangeAddressId].SectorState->reachAge = true;
				NvM_ReachAge = true;
				ret = NVM_NOT_OK;
			}
		}
		else
		{
			ret = NVM_NOT_OK;
		}

	}

	return ret;
}

static NVM_Status_t NVM_JobErase(NvM_RangeAddressID_t *RangeAddressId , NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

    switch(*JobState)
	{
		case NVM_JOB_ERASE_INITIAL:
			ret = NVM_JobEraseHandle(RangeAddressId, JobState);
			break;
		case NVM_JOB_ERASE_ING:
			ret = NVM_JobEraseWait(RangeAddressId,JobState);
			break;
		default:
			ret = NVM_NOT_OK;
			break;
	}

	return ret;
}

static NVM_Status_t NVM_JobEraseExecute(NvM_RangeAddressID_t *RangeAddressId, NVM_Status_t *JobState)
{
	NVM_Status_t result = NVM_OK;

	for(;;)
	{
        result = NVM_JobErase(RangeAddressId, JobState);

		if(result != NVM_LOOP)
		{
			break;
		}
	}

	return result;
}


static NVM_Status_t NVM_JobWriteCheckSectorAct(uint16_t *BlockIndex,NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

	uint32_t currentAddr;
	uint32_t endAddr;
	uint16_t len;

	uint8_t currentSector;
	NvM_RangeAddress_t *rangAddr = NvM_BlockCfg[*BlockIndex].rangeAddress;
	currentSector = rangAddr->SectorState->currentSector;

	if(NVM_SECTOR_NO_ACTION == rangAddr->SectorState->sectorAction)
	{
		len  = NvM_BlockCfg[*BlockIndex].dataLen;
		endAddr     = rangAddr->SectorAddrr[currentSector].endAddr;
		currentAddr = rangAddr->SectorState->currentAddr;

		if((currentAddr +len +NVM_BLOCK_HEAD_OFFSET) > endAddr)
		{
			rangAddr->SectorState->sectorAction = NVM_SECTOR_START;
		}

	}

	if(NVM_SECTOR_START == rangAddr->SectorState->sectorAction)
	{

		if((false == rangAddr->SectorState->reachAge) && (rangAddr->SectorState->ageCycle < (NVM_AGE_CYCLE * rangAddr->SectorSize)))
		{
			rangAddr->SectorState->ageCycle++;
		}
		else
		{
			rangAddr->SectorState->reachAge = true;
			NvM_ReachAge = true;

			if(true == NVM_WriteAllFlag)
			{
				*JobState = NVM_JOB_WRITEALL;
				ret = NVM_LOOP;
			}
			else
			{
				ret = NVM_NOT_OK;
			}
			return ret;
		}

		do{
			rangAddr->SectorState->tempSector++;
			if(rangAddr->SectorState->tempSector >= rangAddr->SectorSize)
			{
				rangAddr->SectorState->tempSector = 0;
			}
		}while(rangAddr->SectorState->tempSector == currentSector);

		rangAddr->SectorState->eraseSector = rangAddr->SectorState->tempSector;
		rangAddr->SectorState->currentAddr = rangAddr->SectorAddrr[rangAddr->SectorState->tempSector].startAddr + LOGICAL_SECTOR_HEAD_LENGTH;

		SectorProcessBlockIndex = 0u;

		for(NvM_RangeAddressID_t Id = 0;Id<NvM_RangeAddressNumber;Id++)
		{
			if( NvM_BlockCfg[*BlockIndex].rangeAddress == &NvM_RangeAddress[Id])
			{
				NvM_RangeAddressId = Id;
				break;
			}
		}

		NVM_JobStatus = NVM_JOB_ERASE;
		*JobState = NVM_JOB_ERASE_INITIAL;
		ret = NVM_PENDING;
	}
	else
	{
		*JobState = NVM_JOB_WRITE_DATA;
		ret = NVM_LOOP;
	}

	return ret;
}

static NVM_Status_t NVM_JobWriteDataHandle(uint16_t *BlockIndex,NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;


	NvM_BlockHead_t NvM_BlockHead;
	SectorHead_t SectorHead;
	uint8_t tempSector;

	uint32_t currentAddr;
	uint16_t len;
	uint8_t *data;

	uint32_t addrData;
	NvM_RangeAddress_t *rangAddr = NvM_BlockCfg[*BlockIndex].rangeAddress;

	currentAddr = rangAddr->SectorState->currentAddr;
	len = NvM_BlockCfg[*BlockIndex].dataLen;
	data = NvM_BlockCfg[*BlockIndex].data;

	NvM_BlockHead.blockId = NvM_BlockCfg[*BlockIndex].blockId;
	NvM_BlockHead.dataLen = len;
	NvM_BlockHead.mask    = NVM_BLOCK_HEAD_MARK;

	if(NVM_SECTOR_NO_ACTION == rangAddr->SectorState->sectorAction)
	{
		for(uint16_t i=0;i<len;i++)
		{
			tempData[NVM_BLOCK_HEAD_OFFSET+i] = data[i];
		}
		NvM_BlockHead.crc = NvM_DataCrc((uint32_t *)(&tempData[NVM_BLOCK_HEAD_OFFSET]), (len>>2));

		for(uint16_t i=0;i<NVM_BLOCK_HEAD_OFFSET;i++)
		{
			tempData[i] = ((uint8_t*)&NvM_BlockHead)[i];  // NvM_BlockHead 的字节 长度必须和 NVM_BLOCK_HEAD_OFFSET 相等
		}

		NvM_BlockState[*BlockIndex].tempCrc = NvM_BlockHead.crc;
		NvM_BlockState[*BlockIndex].tempAddr = currentAddr;
		len += NVM_BLOCK_HEAD_OFFSET;
		rangAddr->SectorState->currentAddr += len;

		FLS_SetWriteParameter(currentAddr, len, tempData);
		FLS_SetStatusBusy();
		ret = NVM_LOOP;
		*JobState = NVM_JOB_WRITE_DATAING;
	}
	else if(NVM_SECTOR_START == rangAddr->SectorState->sectorAction)
	{
		if(true == NvM_BlockState[*BlockIndex].requestWrite)
		{
			for(uint16_t i=0;i<len;i++)
			{
				tempData[NVM_BLOCK_HEAD_OFFSET+i] = data[i];
			}
			NvM_BlockHead.crc = NvM_DataCrc((uint32_t *)(&tempData[NVM_BLOCK_HEAD_OFFSET]), (len>>2));

			for(uint16_t i=0;i<NVM_BLOCK_HEAD_OFFSET;i++)
			{
				tempData[i] = ((uint8_t*)&NvM_BlockHead)[i];  // NvM_BlockHead 的字节 长度必须和 NVM_BLOCK_HEAD_OFFSET 相等
			}

			NvM_BlockState[*BlockIndex].tempCrc = NvM_BlockHead.crc;
		}
		else
		{
			NvM_BlockHead.crc = NvM_BlockState[*BlockIndex].crc;

			for(uint16_t i=0;i<NVM_BLOCK_HEAD_OFFSET;i++)
			{
				tempData[i] = ((uint8_t*)&NvM_BlockHead)[i];  // NvM_BlockHead 的字节 长度必须和 NVM_BLOCK_HEAD_OFFSET 相等
			}

			for(uint16_t i=0;i<len;i=i+4)
			{
				addrData = *(uint32_t *)(NvM_BlockState[*BlockIndex].address+NVM_BLOCK_HEAD_OFFSET+i);

				tempData[NVM_BLOCK_HEAD_OFFSET+i]   = addrData;
				tempData[NVM_BLOCK_HEAD_OFFSET+i+1] = addrData>>8;
				tempData[NVM_BLOCK_HEAD_OFFSET+i+2] = addrData>>16;
				tempData[NVM_BLOCK_HEAD_OFFSET+i+3] = addrData>>24;
			}
		}

		NvM_BlockState[*BlockIndex].tempAddr = currentAddr;
		len += NVM_BLOCK_HEAD_OFFSET;
		rangAddr->SectorState->currentAddr += len;

		FLS_SetWriteParameter(currentAddr, len, tempData);
		FLS_SetStatusBusy();
		ret = NVM_LOOP;
		*JobState = NVM_JOB_WRITE_DATAING;
	}
	else if(NVM_SECTOR_FINISH == rangAddr->SectorState->sectorAction)
	{
		SectorHead.ageCycle   = rangAddr->SectorState->ageCycle;
		SectorHead.markFirst  = Sector_HEAD_FIRST_MARK;
		SectorHead.markSecond = Sector_HEAD_SECOND_MARK;
		SectorHead.markThird  = Sector_HEAD_THIRD_MARK;

		for(uint16_t i=0;i<LOGICAL_SECTOR_HEAD_LENGTH;i++)
		{
			tempData[i] = ((uint8_t*)&SectorHead)[i];
		}

		tempSector = rangAddr->SectorState->tempSector;
		currentAddr = rangAddr->SectorAddrr[tempSector].startAddr;
		len = LOGICAL_SECTOR_HEAD_LENGTH;

		FLS_SetWriteParameter(currentAddr, len, tempData);
		FLS_SetStatusBusy();
		ret = NVM_LOOP;
		*JobState = NVM_JOB_WRITE_DATAING;
	}
	else
	{
		rangAddr->SectorState->sectorAction = NVM_SECTOR_NO_ACTION;
		ret = NVM_NOT_OK;
	}

	return ret;
}

static NVM_Status_t NVM_JobWriteDataWait(uint16_t *BlockIndex, NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

	NvM_RangeAddress_t *rangAddr = NvM_BlockCfg[*BlockIndex].rangeAddress;

	FLS_MainFunction();
	if(FLS_GetStatus() == uFLS_BUSY)
	{
		*JobState = NVM_JOB_WRITE_DATAING;
		ret = NVM_PENDING;
	}
	else if(FLS_GetStatus() == uFLS_IDLE)
	{
		if(FLS_GetResult() == uFLS_OK)
		{
			if(NVM_SECTOR_NO_ACTION == rangAddr->SectorState->sectorAction)
			{
				NvM_BlockState[*BlockIndex].crc          = NvM_BlockState[*BlockIndex].tempCrc;
				NvM_BlockState[*BlockIndex].requestWrite = false;
				NvM_BlockState[*BlockIndex].valid        = true;
				NvM_BlockState[*BlockIndex].backUpAddr   = NvM_BlockState[*BlockIndex].address;
				NvM_BlockState[*BlockIndex].address      = NvM_BlockState[*BlockIndex].tempAddr;
				NvM_BlockState[*BlockIndex].errorStatus  = NVM_NO_ERROR;

				if(true == NVM_WriteAllFlag)
				{
					*JobState = NVM_JOB_WRITEALL;
					ret = NVM_PENDING;
				}
				else
				{
					ret = NVM_OK;
				}
			}
			else if(NVM_SECTOR_START == rangAddr->SectorState->sectorAction)
			{
				*JobState = NVM_JOB_WRITE_VALIDBLOCK;
				ret = NVM_PENDING;
			}
			else if(NVM_SECTOR_FINISH == rangAddr->SectorState->sectorAction)
			{
				for(uint16_t i=0;i<NvM_BlockNumber;i++)
				{
					if((NvM_BlockCfg[i].rangeAddress == rangAddr) && ((true == NvM_BlockState[i].valid) || (true == NvM_BlockState[i].requestWrite)))
					{
						if(true == NvM_BlockState[i].requestWrite)
						{
							NvM_BlockState[i].crc          = NvM_BlockState[i].tempCrc;
							NvM_BlockState[i].errorStatus  = NVM_NO_ERROR;
						}
						NvM_BlockState[i].requestWrite = false;
						NvM_BlockState[i].valid        = true;
						NvM_BlockState[i].backUpAddr   = NvM_BlockState[i].address;
						NvM_BlockState[i].address      = NvM_BlockState[i].tempAddr;
					}
				}
				rangAddr->SectorState->sectorAction = NVM_SECTOR_NO_ACTION;
				rangAddr->SectorState->currentSector = rangAddr->SectorState->tempSector;

				if(true == NVM_WriteAllFlag)
				{
					*JobState = NVM_JOB_WRITEALL;
					ret = NVM_PENDING;
				}
				else
				{
					ret = NVM_OK;
				}
			}
			else
			{
				ret = NVM_NOT_OK;
			}
		}
		else if(FLS_GetResult() == uFLS_NOT_OK)
		{
			rangAddr->SectorState->sectorAction = NVM_SECTOR_START;
			*JobState = NVM_JOB_WRITE_INITIAL;
			ret = NVM_PENDING;
		}
		else
		{
			ret = NVM_NOT_OK;
		}
	}

	return ret;
}

static NVM_Status_t NVM_JobWriteValidBlock(uint16_t *BlockIndex, NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

	while(SectorProcessBlockIndex < NvM_BlockNumber)
	{
		if(NvM_BlockCfg[*BlockIndex].rangeAddress == NvM_BlockCfg[SectorProcessBlockIndex].rangeAddress)
		{
			if((true == NVM_WriteAllFlag) && (true == NvM_BlockState[SectorProcessBlockIndex].writeAllFlag))
			{
				NvM_BlockState[SectorProcessBlockIndex].requestWrite = true;
				NvM_BlockState[SectorProcessBlockIndex].writeAllFlag = false;
			}

			if((true == NvM_BlockState[SectorProcessBlockIndex].valid) || (true == NvM_BlockState[SectorProcessBlockIndex].requestWrite))
			{
				*BlockIndex = SectorProcessBlockIndex;
				SectorProcessBlockIndex++;
				*JobState = NVM_JOB_WRITE_DATA;
				ret = NVM_LOOP;
				return ret;
			}
		}

		SectorProcessBlockIndex++;
	}

	NvM_BlockCfg[*BlockIndex].rangeAddress->SectorState->sectorAction = NVM_SECTOR_FINISH;
	*JobState = NVM_JOB_WRITE_DATA;
	ret = NVM_LOOP;

	return ret;
}

static NVM_Status_t NVM_JobWrite(uint16_t *BlockIndex, NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

    switch(*JobState)
	{
		case NVM_JOB_WRITE_INITIAL:
			ret = NVM_JobWriteCheckSectorAct(BlockIndex, JobState);
			break;

		case NVM_JOB_WRITE_DATA:
			ret = NVM_JobWriteDataHandle(BlockIndex, JobState);
			break;

		case NVM_JOB_WRITE_DATAING:
			ret = NVM_JobWriteDataWait(BlockIndex, JobState);
			break;

		case NVM_JOB_WRITE_VALIDBLOCK:
			ret = NVM_JobWriteValidBlock(BlockIndex, JobState);
			break;

		case NVM_JOB_WRITEALL:
			ret = NVM_JobWriteAllBlock(BlockIndex, JobState);
			break;

		default:
			ret = NVM_NOT_OK;
			break;
	}

	return ret;
}

static NVM_Status_t NVM_JobWriteExecute(uint16_t *BlockIndex, NVM_Status_t *JobState)
{
	NVM_Status_t result = NVM_OK;

	for(;;)
	{
        result = NVM_JobWrite(BlockIndex, JobState);

		if(result != NVM_LOOP)
		{
			break;
		}
	}

	return result;
}

static void NVM_ReadRangeAddressData(NvM_RangeAddressID_t RangeAddressId)
{
	SectorHead_t SectorHead;
	uint32_t startAddr    = 0;
	uint32_t ageCycle     = 0;
	uint8_t currentSector = 0;
	uint16_t index        = 0;

	uint32_t endAddr      = 0;
	uint32_t currentAddr  = 0;

	uint32_t first4Data   = 0;
	uint32_t second4Data  = 0;
	NvM_BlockHead_t NvM_BlockHead;

	uint16_t len;


	NvM_RangeAddress[RangeAddressId].SectorState->currentSector = 0;
	NvM_RangeAddress[RangeAddressId].SectorState->eraseSector   = 0;
	NvM_RangeAddress[RangeAddressId].SectorState->sectorAction  = NVM_SECTOR_NO_ACTION;
	NvM_RangeAddress[RangeAddressId].SectorState->currentSector = 0;
	NvM_RangeAddress[RangeAddressId].SectorState->ageCycle      = 0;

	for(uint8_t i = 0; i<NvM_RangeAddress[RangeAddressId].SectorSize;i++)
	{
		startAddr =  NvM_RangeAddress[RangeAddressId].SectorAddrr[i].startAddr;

		NvM_EccFlag = false;
		ECC_ENABLE;
		SectorHead.ageCycle   = *(uint32_t*)startAddr;
		SectorHead.markFirst  = *(uint32_t*)(startAddr + 4);
		SectorHead.markSecond = *(uint32_t*)(startAddr + 8);
		SectorHead.markThird  = *(uint32_t*)(startAddr + 12);
		asm("nop");
		ECC_ENABLE;
		if(true == NvM_EccFlag)
		{
			SectorHead.ageCycle = 0;
		}
		else
		{
			if((Sector_HEAD_FIRST_MARK != SectorHead.markFirst) || (Sector_HEAD_SECOND_MARK != SectorHead.markSecond) || (Sector_HEAD_THIRD_MARK != SectorHead.markThird))
			{
				SectorHead.ageCycle = 0;
			}
		}

		if(SectorHead.ageCycle>ageCycle)
		{
			currentSector = i;
			ageCycle = SectorHead.ageCycle;
		}
	}

	if(0u == ageCycle)
	{
		/*判断是否有可用的block*/
		for(index=0;index<NvM_BlockNumber;index++)
		{
			if(NvM_BlockCfg[index].rangeAddress == &NvM_RangeAddress[RangeAddressId])
			{
				break;
			}
		}

		if(index >=NvM_BlockNumber)
		{
			return;
		}

		/*擦除*/
		NvM_RangeAddressId = RangeAddressId;
		NvM_RangeAddress[RangeAddressId].SectorState->sectorAction = NVM_SECTOR_NO_ACTION;
		NvM_RangeAddress[RangeAddressId].SectorState->eraseSector  = 0;

		NVM_JobStatus   = NVM_JOB_ERASE;
		NVM_JobProgress = NVM_JOB_ERASE_INITIAL;
		NVM_Status      = NVM_BUSY;

		while(NVM_GetStatus() == NVM_BUSY)
		{
			NVM_MainFunction();
		}

		/*写入寿命*/
		NvM_RangeAddress[RangeAddressId].SectorState->tempSector    = 0;
		NvM_RangeAddress[RangeAddressId].SectorState->currentSector = 0;
		NvM_RangeAddress[RangeAddressId].SectorState->ageCycle      = 1;
		NvM_RangeAddress[RangeAddressId].SectorState->sectorAction  = NVM_SECTOR_FINISH;
		NvM_BlockIndex  = index;
		NVM_JobStatus   = NVM_JOB_WRITE;
		NVM_JobProgress = NVM_JOB_WRITE_DATA;
		NVM_Status      = NVM_BUSY;

		while(NVM_GetStatus() == NVM_BUSY)
		{
			NVM_MainFunction();
		}

		currentSector = NvM_RangeAddress[RangeAddressId].SectorState->currentSector;
		NvM_RangeAddress[RangeAddressId].SectorState->currentAddr = NvM_RangeAddress[RangeAddressId].SectorAddrr[currentSector].startAddr + LOGICAL_SECTOR_HEAD_LENGTH;

		return;
	}
	else
	{
		NvM_RangeAddress[RangeAddressId].SectorState->currentSector = currentSector;
		NvM_RangeAddress[RangeAddressId].SectorState->tempSector    = currentSector;
		NvM_RangeAddress[RangeAddressId].SectorState->ageCycle      = ageCycle;
		startAddr   = NvM_RangeAddress[RangeAddressId].SectorAddrr[currentSector].startAddr;
		endAddr     =  NvM_RangeAddress[RangeAddressId].SectorAddrr[currentSector].endAddr;
		currentAddr = startAddr + LOGICAL_SECTOR_HEAD_LENGTH;

		if(ageCycle >= (NVM_AGE_CYCLE * NvM_RangeAddress[RangeAddressId].SectorSize))
		{
			NvM_RangeAddress[RangeAddressId].SectorState->reachAge = true;
			NvM_ReachAge = true;
		}
	}


	/*查找Block存储的最近两次位置*/
	while(currentAddr < endAddr)
	{
		NvM_EccFlag = false;
		ECC_ENABLE;
		first4Data  = *(uint32_t *)currentAddr;
		second4Data = *(uint32_t *)(currentAddr+4);
		asm("nop");
		ECC_ENABLE;

		if(true == NvM_EccFlag)
		{
			NvM_RangeAddress[RangeAddressId].SectorState->sectorAction  = NVM_SECTOR_START;
			break;
		}

		NvM_BlockHead.blockId = first4Data;
		NvM_BlockHead.dataLen = first4Data >>16;
		NvM_BlockHead.crc     = second4Data;
		NvM_BlockHead.mask    = second4Data>>16;

		len = 0u;

		if((0xFFFFFFFF == first4Data) && (0xFFFFFFFF== second4Data) )
		{
			break;
		}
		else
		{
			if((NVM_BLOCK_HEAD_MARK == NvM_BlockHead.mask) && (!(NvM_BlockHead.dataLen &(NVM_BLOCK_MIN_SIZE-1u))) )
			{
				if((NVM_BLOCK_MIN_SIZE <=NvM_BlockHead.dataLen) && (NVM_BLOCK_MAX_SIZE >=NvM_BlockHead.dataLen) && ((currentAddr +NVM_BLOCK_HEAD_OFFSET +NvM_BlockHead.dataLen) <= endAddr))
				{
					index = NVM_FindBlockIndex(NvM_BlockHead.blockId);
					if(index <NvM_BlockNumber)
					{
						if((NvM_BlockCfg[index].rangeAddress == &NvM_RangeAddress[RangeAddressId]) && (NvM_BlockHead.dataLen == NvM_BlockCfg[index].dataLen))
						{
							NvM_BlockState[index].isFound = true;
							NvM_BlockState[index].backUpAddr = NvM_BlockState[index].address;
							NvM_BlockState[index].address = currentAddr;
						}
						else
						{
							NvM_RangeAddress[RangeAddressId].SectorState->sectorAction = NVM_SECTOR_START;
						}
					}
					else
					{
						NvM_RangeAddress[RangeAddressId].SectorState->sectorAction = NVM_SECTOR_START;
					}

					len =  NvM_BlockHead.dataLen;
				}
				else
				{
					NvM_RangeAddress[RangeAddressId].SectorState->sectorAction = NVM_SECTOR_START;
					break;
				}

			}
			else
			{
				NvM_RangeAddress[RangeAddressId].SectorState->sectorAction = NVM_SECTOR_START;
				break;
			}

		}
		currentAddr += len + NVM_BLOCK_HEAD_OFFSET;
	}

	NvM_RangeAddress[RangeAddressId].SectorState->currentAddr = currentAddr;
}

static void NVM_CheckBlockIsValid(void)
{
	const NvM_BlockConfig_t *Block;
	uint32_t *Addr;
	uint16_t expectCrc;
	uint16_t actualCrc;
	uint16_t len;


	uint16 index = 0;

	while(index <NvM_BlockNumber)
	{
		NvM_BlockState[index].valid = false;
		NvM_BlockState[index].requestWrite = false;
		NvM_BlockState[index].crc = 0;
		NvM_BlockState[index].tempCrc = 0;
		NvM_BlockState[index].tempAddr = 0;
		NvM_BlockState[index].errorStatus = NVM_NO_ERROR;

		Block = &NvM_BlockCfg[index];
		len = Block->dataLen >>2;

		if(true == NvM_BlockState[index].isFound)
		{
			NvM_EccFlag = false;
			ECC_ENABLE;
			Addr = (uint32_t *)NvM_BlockState[index].address;
			expectCrc = *(Addr+1);
			Addr += 2;
			actualCrc = NvM_DataCrc(Addr, len);
			asm("nop");
			ECC_ENABLE;

			if(true == NvM_EccFlag)
			{
				NvM_BlockState[index].errorStatus = NVM_ECC;
				Block->rangeAddress->SectorState->sectorAction = NVM_SECTOR_START;
			}
			else
			{
				if(actualCrc == expectCrc)
				{
					NvM_BlockState[index].valid = true;
					NvM_BlockState[index].crc   = expectCrc;
					NvM_BlockState[index].errorStatus = NVM_NO_ERROR;
				}
				else
				{
					/*crc checking result not equal,the data is invlaid*/
					NvM_BlockState[index].errorStatus = NVM_CRC_FAIL;
					Block->rangeAddress->SectorState->sectorAction = NVM_SECTOR_START;

				}
			}

			if((NVM_ECC == NvM_BlockState[index].errorStatus) || (NVM_CRC_FAIL == NvM_BlockState[index].errorStatus))
			{
				if(NvM_BlockState[index].backUpAddr != 0)
				{
					NvM_BlockState[index].address = NvM_BlockState[index].backUpAddr;
					NvM_BlockState[index].backUpAddr = 0;
					continue;
				}
			}

		}
		else
		{
			NvM_BlockState[index].address    = 0;
			NvM_BlockState[index].backUpAddr = 0;

			NvM_BlockState[index].errorStatus = NVM_NO_STORE;
		}

		index++;
	}

}


void NVM_ReadAllBlock(void)
{
	uint16 index = 0;
	uint32_t *Addr;
	uint16_t len;

	while(index <NvM_BlockNumber)
	{
		len = NvM_BlockCfg[index].dataLen;
		if(true == NvM_BlockState[index].valid)
		{
			Addr = (uint32_t *)(NvM_BlockState[index].address + NVM_BLOCK_HEAD_OFFSET);
			len  = len>>2;

			ECC_ENABLE;
			for(uint16_t size = 0;size <len;size++)
			{
				((uint32_t *)NvM_BlockCfg[index].data)[size] = *Addr;
				Addr++;
			}
			ECC_ENABLE;
		}
		else
		{
			for(uint16_t size = 0;size <len;size++)
			{
				NvM_BlockCfg[index].data[size] = 0xFF;
			}
		}
		index++;
	}
}
/************************************************************/

static NVM_Status_t NVM_JobWriteAllBlock(uint16_t *BlockIndex, NVM_Status_t *JobState)
{
	NVM_Status_t ret = NVM_OK;

    while(NVM_WriteAllBlockIndex < NvM_BlockNumber)
	{
		if(true == NvM_BlockState[NVM_WriteAllBlockIndex].writeAllFlag)
		{
			NvM_BlockState[NVM_WriteAllBlockIndex].requestWrite = true;
			NvM_BlockState[NVM_WriteAllBlockIndex].writeAllFlag = false;
			*BlockIndex = NVM_WriteAllBlockIndex;
			NVM_WriteAllBlockIndex++;

			*JobState = NVM_JOB_WRITE_INITIAL;
			ret = NVM_LOOP;
			return ret;
		}

		NVM_WriteAllBlockIndex++;
	}

	NVM_WriteAllFlag = false;
	ret = NVM_OK;

	return ret;
}


NVM_Status_t NVM_WriteAll(void)
{
	NVM_Status_t ret = NVM_OK;

	if((NVM_IDLE == NVM_Status) && (NVM_GetIsReachAge() == false))
	{
		NVM_WriteAllBlockIndex = 0;
		NvM_BlockIndex = NVM_WriteAllBlockIndex;
		NVM_WriteAllFlag = true;
		NVM_Status = NVM_BUSY;
		NVM_JobStatus = NVM_JOB_WRITE;
		NVM_JobProgress = NVM_JOB_WRITEALL;
	}
	else
	{
		ret = NVM_NOT_OK;
	}

	return ret;
}


NVM_Status_t NVM_SetBlockWriteFlag(uint16_t BlockId)
{
	NVM_Status_t ret = NVM_NOT_OK;
	uint16_t index;

	if(NVM_IDLE == NVM_Status)
	{
		index = NVM_FindBlockIndex(BlockId);
		if(index <NvM_BlockNumber)
		{
			if(false == NvM_BlockCfg[index].rangeAddress->SectorState->reachAge)
			{
				NvM_BlockState[index].writeAllFlag = true;
				ret = NVM_OK;
			}
		}
	}

	return ret;
}



void NVM_EccCheck(void)
{
	ECC_StatusType tEccType;
    uint32_t tEccStatus = 0;
    uint32_t u32ErrorAddr = 0;
	tEccStatus =  FLASHDRIVER_ECCType_Check(&g_tFlashHandle,&tEccType);
    if(tEccStatus && (tEccType == FLASH_ECC_ERROR_DBC))
    {
        u32ErrorAddr = SCB->BFAR;
		for(uint8_t index=0;index<NvM_RangeAddressNumber;index++)
		{
			for(uint8_t i=0;i<NvM_RangeAddress[index].SectorSize;i++)
			{
				if((NvM_RangeAddress[index].SectorAddrr[i].startAddr <=u32ErrorAddr) && (NvM_RangeAddress[index].SectorAddrr[i].endAddr >u32ErrorAddr))
				{
					NvM_EccFlag = true;
					ECC_DISENABLE;
					return;
				}
			}
		}
	}
}

void HardFault_Handler(void)
{
	NVM_EccCheck();
}

NvM_ErrorStatus_t NVM_GetBlockErrorStatus(uint16_t BlockId)
{
	uint16_t index;

	index = NVM_FindBlockIndex(BlockId);

	if(index<NvM_BlockNumber)
	{
		if(false == NvM_BlockCfg[index].rangeAddress->SectorState->reachAge)
		{
			return NvM_BlockState[index].errorStatus;
		}
		else
		{
			return NVM_REACH_AGE;
		}
	}

	return NVM_NO_SUPPORT;
}

boolean NVM_GetIsReachAge(void)
{
	return NvM_ReachAge;
}



