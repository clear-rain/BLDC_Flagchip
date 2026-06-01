/*
 * BspFlash.c
 *
 *  Created on: 2024年11月11日
 *      Author: 22093
 */

#include "BspFlash.h"
//#include "modules/FC4150F1M_B_flash_common_feature.h"

//#include "interrupt_manager.h"

typedef struct
{
    uint32_t u32Addr;
    uint32_t u32Length;
    uint32_t u32DataAddr;
    uint32_t u32AlignLen;
    uint32_t u32TempLen;
    uint32_t u32AlignOffset;
    uint32_t u32Index;
    uint32_t u32Count;
    uFLS_Status_t progress;
    uFLS_Status_t uFLS_JOB_Status;
}uFLS_Data_t;

static uFLS_Status_t uFLS_Status = uFLS_IDLE;
static FLASH_DRIVER_ParamType User_pFlashParam;
static uFLS_Data_t uFLS_Data;
static uFLS_Status_t uFLS_Result = uFLS_OK;

static uFLS_Status_t uFLS_WriteHandler(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);
static uFLS_Status_t uFLS_WriteData(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);
static uFLS_Status_t uFLS_WriteCheckResult(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);
static uFLS_Status_t uFLS_Write(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);

static uFLS_Status_t uFLS_EraseHandler(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);
static uFLS_Status_t uFLS_EraseData(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);
static uFLS_Status_t uFLS_EraseCheckResult(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);
static uFLS_Status_t uFLS_Erase(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);

static uFLS_Status_t FLS_RepeaterExecute(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);
static void FLS_WorkerDoRepeat(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State);

FLASH_ROM_API_ENTRY_T * s_pFlashDriver_FuncHeader = FLASHDRV_BASE_ADDR;//s_pFlashDriver[0];
FLASH_HandleType g_tFlashHandle = {.eInstance = FLASH_INSTANCE_0};


static uFLS_Status_t uFLS_WriteHandler(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
    FLASH_StatusType tRetVal = FLASH_ERROR_FAILED;
    uFLS_Status_t ret = uFLS_OK;

    State->u32Addr = pFlashParam->u32Address;
    State->u32Length = pFlashParam->u32Length;
    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = FLASHDRIVER_SyncWriteCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        /* flash watchdog config */
        /* tFlash_wdg_cfg.time = 0x03UL; */
        /* tFlash_wdg_cfg.wen = 0x01UL; */
        /* tFlash_wdg_cfg.wint_en = FLASH_WDG_INT_DISABLE; */
        /* (s_pFlashDriver_FuncHeader)->FLASH_DRV_Wdog_Configure(&tFlash_wdg_cfg); */
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_ENABLE_HOLD_CFG(1);

        /* align address, write must align to FLASH_PROGRAM_PAGE_MAX_SIZE */
        State->u32AlignOffset = State->u32Addr & (FLASH_PROGRAM_PAGE_MAX_SIZE - 1U);
        State->u32AlignLen = State->u32Length + State->u32AlignOffset;
        State->u32Count = State->u32AlignLen & (FLASH_PROGRAM_PAGE_MAX_SIZE - 1U);
        State->u32Count = State->u32Count > 0U ? 1U : 0U;
        State->u32Count += State->u32AlignLen / FLASH_PROGRAM_PAGE_MAX_SIZE;
        State->u32DataAddr = (uint32_t)pFlashParam->pData;
        State->u32TempLen = State->u32AlignLen;
        State->u32Index = 0u;

        State->progress = uFLS_WRITING;
        ret = uFLS_LOOP;
    }
    else
    {
        ret = uFLS_NOT_OK;
    }

    return ret;
}

static uFLS_Status_t uFLS_WriteData(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
    FLASH_StatusType tRetVal = FLASH_ERROR_FAILED;
    uFLS_Status_t ret = uFLS_OK;
    uint32_t u32Temp = 0;
    FLASH_DRV_PRGM_CFG_T tFlash_api_cfg;

    State->u32TempLen = State->u32Length + State->u32AlignOffset;
    State->u32TempLen = State->u32TempLen >= FLASH_PROGRAM_PAGE_MAX_SIZE ? FLASH_PROGRAM_PAGE_MAX_SIZE : State->u32TempLen;
    State->u32TempLen -= State->u32AlignOffset;

    pFlashParam->u32Address = State->u32Addr;
    pFlashParam->u32Length = State->u32TempLen;

    if((DFLASH_ADDR_START > pFlashParam->u32Address) || (pFlashParam->u32Address > DFLASH_ADDR_END))
    {
        ret = uFLS_NOT_OK;
        return ret;
    }

    /* unlock sector */
    FLASHDRIVER_LockSector(pFlashParam->u32Address, 0U);
    tFlash_api_cfg.dest = pFlashParam->u32Address;
    tFlash_api_cfg.size = pFlashParam->u32Length / 4; /* one data is 4 bytes */
    tFlash_api_cfg.pData = (uint32_t *)State->u32DataAddr;
    tFlash_api_cfg.wdg_tune = WDG_TUNE_DISABLE;

    /* next address and length */
    State->u32Addr += State->u32TempLen;
    State->u32DataAddr += State->u32TempLen;
    State->u32Length -= State->u32TempLen;

    State->u32AlignOffset = 0U;

    /* start write */
    DISABLE_INTERRUPTS();
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program(&tFlash_api_cfg);
    ENABLE_INTERRUPTS();

    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

    /* check erase operation valid */
    if (tRetVal != FLASH_ERROR_OK)
    {
        /* write operation failed, exit */
        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        ret = uFLS_NOT_OK;
    }
    else
    {
        State->progress = uFLS_WRIT_CHECK;
        ret = uFLS_LOOP;
    }

    return ret;
}

static uFLS_Status_t uFLS_WriteCheckResult(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
    uint32_t u32Temp = 0;
    uFLS_Status_t ret = uFLS_OK;
    FLASH_StatusType tRetVal = FLASH_ERROR_FAILED;
     uint32_t u32TryCount = 0;

    FLASHDRIVER_LL_Delay();

    /* check write still in progress */
    while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 10000))
    {
        u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_HV_Status_Check();
        /* check if finished */
        if (u32Temp == STATUS_HVOP)
        {
            tRetVal = FLASH_ERROR_FAILED;
        }
        else
        {
            tRetVal = FLASH_ERROR_OK;
        }
    }

    if (tRetVal != FLASH_ERROR_OK)
    {
        /* erasing timeout, exit */
        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        ret = uFLS_NOT_OK;
    }
    else
    {
        FLASHDRIVER_LL_Delay();
        /* check write result */
        u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program_Clear();
        tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;
        if (tRetVal != FLASH_ERROR_OK)
        {
            /* write failed, exit */
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            ret = uFLS_NOT_OK;
        }
        else
        {
            /* trigger watchdog function */
            if (pFlashParam->wdTriggerFct != ((void *)0))
            {
                pFlashParam->wdTriggerFct();
            }

            State->u32Index++;
            if(State->u32Index < State->u32Count)
            {
                State->progress = uFLS_WRITING;
                ret = uFLS_PENDING;
            }
            else
            {
                ret = uFLS_OK;
            }
        }
    }

    return ret;
}

static uFLS_Status_t uFLS_Write(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{

    uFLS_Status_t ret = uFLS_OK;

     switch (State->progress)
     {
            case uFLS_WRITE_INITIAL:
                ret = uFLS_WriteHandler(pFlashParam, State);
                break;

            case uFLS_WRITING:
                ret = uFLS_WriteData(pFlashParam, State);
                break;

            case uFLS_WRIT_CHECK:
                ret = uFLS_WriteCheckResult(pFlashParam, State);
                break;

            default:
                ret = uFLS_NOT_OK;
                break;
     }

     return ret;
}

static uFLS_Status_t uFLS_EraseHandler(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
    FLASH_StatusType tRetVal = FLASH_ERROR_FAILED;
    uFLS_Status_t ret = uFLS_NOT_OK;

    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */
    State->u32Addr = pFlashParam->u32Address;
    State->u32Length = pFlashParam->u32Length;

    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = FLASHDRIVER_SyncEraseCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        /* flash watchdog config */
        /* tFlash_wdg_cfg.time = FLASH_WDG_TIMEOUT_SELECT3; */
        /* tFlash_wdg_cfg.wen = FLASH_WDG_ENABLE; */
        /* tFlash_wdg_cfg.wint_en = FLASH_WDG_INT_DISABLE; */
        /* (s_pFlashDriver_FuncHeader)->FLASH_DRV_Wdog_Configure(&tFlash_wdg_cfg); */
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_ENABLE_HOLD_CFG(1);
        pFlashParam->u32Length = DFLASH_ERASE_SECTOR_SIZE;

        State->progress = uFLS_ERASEING;
        ret = uFLS_LOOP;
    }
    else
    {
        ret = uFLS_NOT_OK;
    }
    return ret;
}

static uFLS_Status_t uFLS_EraseData(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
    FLASH_StatusType tRetVal = FLASH_ERROR_FAILED;
    uFLS_Status_t ret = uFLS_NOT_OK;
    uint32_t u32Temp = 0;
    FLASH_DRV_ERASESECTOR_CFG_T tFlash_api_cfg;

    if((DFLASH_ADDR_START > pFlashParam->u32Address) || (pFlashParam->u32Address > DFLASH_ADDR_END))
    {
        ret = uFLS_NOT_OK;
        return ret;
    }

    FLASHDRIVER_LockSector(pFlashParam->u32Address, 0U);
    FLASHDRIVER_GetFlashConfig(pFlashParam->u32Address, &tFlash_api_cfg);
    /* start erase */
    DISABLE_INTERRUPTS();
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector(&tFlash_api_cfg);
    ENABLE_INTERRUPTS();

    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;


    /* check erase operation valid */
    if (tRetVal != FLASH_ERROR_OK)
    {
        /* erase operation failed, exit */
        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        ret = uFLS_NOT_OK;
    }
    else
    {
        /* check erasing still in progress */
        State->progress = uFLS_ERASE_CHECK;
        ret = uFLS_LOOP;
    }
    return ret;
}

static uFLS_Status_t uFLS_EraseCheckResult(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
    uint32_t u32Temp = 0;
    uFLS_Status_t ret = uFLS_NOT_OK;
    FLASH_StatusType tRetVal = FLASH_ERROR_FAILED;
    uint32_t u32TryCount = 0;

    FLASHDRIVER_LL_Delay();
    /* check erasing still in progress */
    tRetVal = FLASH_ERROR_FAILED;

    while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 100000))
    {
        u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_HV_Status_Check();
        /* check if finished */
        if (u32Temp == STATUS_HVOP)
        {
            tRetVal = FLASH_ERROR_FAILED;
        }
        else
        {
            tRetVal = FLASH_ERROR_OK;
        }
    }

    if (tRetVal != FLASH_ERROR_OK)
    {
        /* erasing timeout, exit */
        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        ret = uFLS_NOT_OK;
    }
    else
    {
        FLASHDRIVER_LL_Delay();
        /* check erasing result */
        u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector_Clear();
        tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

        if (tRetVal != FLASH_ERROR_OK)
        {
            /* erasing failed, exit */
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            ret = uFLS_NOT_OK;
        }
        else
        {
            /* trigger watchdog function */
            if (pFlashParam->wdTriggerFct != ((void *)0))
            {
                pFlashParam->wdTriggerFct();
            }

            pFlashParam->u32Address += DFLASH_ERASE_SECTOR_SIZE;
            if(pFlashParam->u32Address < (State->u32Addr + State->u32Length))
            {
                State->progress = uFLS_ERASEING;
                ret = uFLS_PENDING;
            }
            else
            {
                ret = uFLS_OK;
            }
        }
    }

    return ret;
}

static uFLS_Status_t uFLS_Erase(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{

    uFLS_Status_t ret = uFLS_OK;

     switch (State->progress)
     {
            case uFLS_ERASE_INITIAL:
                ret = uFLS_EraseHandler(pFlashParam, State);
                break;

            case uFLS_ERASEING:
                ret = uFLS_EraseData(pFlashParam, State);
                break;

            case uFLS_ERASE_CHECK:
                ret = uFLS_EraseCheckResult(pFlashParam, State);
                break;

            default:
                ret = uFLS_NOT_OK;
                break;
     }

     return ret;
}

static uFLS_Status_t FLS_RepeaterExecute(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
	uFLS_Status_t result = uFLS_OK;
    uFLS_Status_t status = State->uFLS_JOB_Status;

	for(;;)
	{
        if(uFLS_JOB_ERASE == status)
        {
            result = uFLS_Erase(pFlashParam, State);
        }
        else if(uFLS_JOB_WRITE == status)
        {
            result = uFLS_Write(pFlashParam, State);
        }
        else
        {
            result = uFLS_NOT_OK;
            break;
        }

		if(result != uFLS_LOOP)
		{
			break;
		}
	}


	return result;
}

static void FLS_WorkerDoRepeat(FLASH_DRIVER_ParamType *pFlashParam, uFLS_Data_t *State)
{
	uFLS_Result  = FLS_RepeaterExecute(pFlashParam, State);

	switch(uFLS_Result)
	{
		case uFLS_OK:
            uFLS_Status = uFLS_IDLE;
			break;

		case uFLS_NOT_OK:
            uFLS_Status = uFLS_IDLE;
			break;

		case uFLS_PENDING:
			uFLS_Status = uFLS_BUSY;
			break;

        default:
            uFLS_Status = uFLS_IDLE;
            break;
	}
}


void FLS_MainFunction(void)
{
	if(uFLS_Status == uFLS_BUSY)
	{
		FLS_WorkerDoRepeat(&User_pFlashParam, &uFLS_Data);
	}
}


void FLS_SetEraseParameter(uint32_t address, uint32_t len)
{
    if(uFLS_IDLE == uFLS_Status)
    {
        User_pFlashParam.u32Address = address;
        User_pFlashParam.u32Length = len;
        User_pFlashParam.wdTriggerFct = (void *)0;

        uFLS_Data.progress = uFLS_ERASE_INITIAL;
        uFLS_Data.uFLS_JOB_Status = uFLS_JOB_ERASE;
    }
}

void FLS_SetWriteParameter(uint32_t address, uint32_t len, uint8_t *Data)
{
    if(uFLS_IDLE == uFLS_Status)
    {
        User_pFlashParam.u32Address = address;
        User_pFlashParam.u32Length = len;
        User_pFlashParam.pData = Data;
        User_pFlashParam.wdTriggerFct = (void *)0;

        uFLS_Data.progress = uFLS_WRITE_INITIAL;
        uFLS_Data.uFLS_JOB_Status = uFLS_JOB_WRITE;
    }
}

uFLS_Status_t FLS_GetStatus(void)
{
    return uFLS_Status;
}

void FLS_SetStatusBusy(void)
{
    uFLS_Status = uFLS_BUSY ;
}

void FLS_SetStatusIdle(void)
{
    uFLS_Status = uFLS_IDLE;
}

uFLS_Status_t FLS_GetResult(void)
{
    return uFLS_Result;
}




