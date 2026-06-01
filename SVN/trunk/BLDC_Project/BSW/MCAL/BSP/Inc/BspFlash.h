/*
 * BspFlash.h
 *
 *  Created on: 2024年11月11日
 *      Author: 22093
 */

#ifndef BSW_MCAL_BSP_INC_BSPFLASH_H_
#define BSW_MCAL_BSP_INC_BSPFLASH_H_

#include "module_driver_flash.h"

typedef enum
{
    uFLS_IDLE,
    uFLS_BUSY,

    uFLS_OK,
    uFLS_NOT_OK,
    uFLS_LOOP,
    uFLS_PENDING,

    uFLS_WRITE_INITIAL,
    uFLS_WRITING,
    uFLS_WRIT_CHECK,

    uFLS_ERASE_INITIAL,
    uFLS_ERASEING,
    uFLS_ERASE_CHECK,

    uFLS_JOB_NO_ERASE_NO_WRITE,
    uFLS_JOB_ERASE,
    uFLS_JOB_WRITE,
} uFLS_Status_t;

void FLS_SetEraseParameter(uint32_t address, uint32_t len);
void FLS_SetWriteParameter(uint32_t address, uint32_t len, uint8_t *Data);
void FLS_SetStatusBusy(void);
void FLS_SetStatusIdle(void);
uFLS_Status_t FLS_GetStatus(void);
uFLS_Status_t FLS_GetResult(void);
void FLS_MainFunction(void);

extern FLASH_HandleType g_tFlashHandle;

#endif /* BSW_MCAL_BSP_INC_BSPFLASH_H_ */
