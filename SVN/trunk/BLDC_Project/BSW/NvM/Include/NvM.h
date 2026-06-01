/*
 * NvM.h
 *
 *  Created on: 2024年7月10日
 *      Author: 22093
 */

#ifndef BSW_INCLUDE_NVM_H_
#define BSW_INCLUDE_NVM_H_

#include "NvM_Cfg.h"
#include "BspFlash.h"
#include "module_driver_flash.h"


typedef enum
{
	NVM_UNINIT = 0U,
    NVM_IDLE,
    NVM_BUSY,

	NVM_OK,
	NVM_NOT_OK,
	NVM_LOOP,
	NVM_PENDING,

	NVM_JOB_NO_OPERATION,
	NVM_JOB_READ,
	NVM_JOB_WRITE,
	NVM_JOB_ERASE,

	NVM_JOB_READ_INITIAL,
	NVM_JOB_READ_ING,

	NVM_JOB_ERASE_INITIAL,
	NVM_JOB_ERASE_ING,

	NVM_JOB_WRITE_INITIAL,
	NVM_JOB_WRITE_DATA,
	NVM_JOB_WRITE_DATAING,
	NVM_JOB_WRITE_VALIDBLOCK,
	NVM_JOB_WRITEALL,
}NVM_Status_t;





void NVM_Init(void);
NVM_Status_t NVM_WriteBlockData(uint16_t BlockId);
NVM_Status_t NVM_ReadBlockData(uint16_t BlockId);
void NVM_MainFunction(void);
NVM_Status_t NVM_GetStatus(void);

NvM_ErrorStatus_t NVM_GetBlockErrorStatus(uint16_t BlockId);
boolean NVM_GetIsReachAge(void);

NVM_Status_t NVM_WriteAll(void);
NVM_Status_t NVM_SetBlockWriteFlag(uint16_t BlockId);




#endif /* BSW_INCLUDE_NVM_H_ */
