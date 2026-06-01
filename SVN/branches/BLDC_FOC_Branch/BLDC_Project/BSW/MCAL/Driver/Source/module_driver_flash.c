/**
 * @file module_driver_flash.c
 * @author Flagchip
 * @brief FLASH driver source code
 * @version 2.0.0
 * @date 2024-02-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#include "module_driver_flash.h"

#if FMC_INSTANCE_COUNT > 0U

#ifndef FLASH_DEV_ERROR_REPORT
    #define FLASH_DEV_ERROR_REPORT  STD_OFF
#endif

#if FLASH_DEV_ERROR_REPORT == STD_ON
    #define FLASH_ReportDevError(func, error) ReportDevError(FLASH_MODULE_ID, func, error)
#endif

/* ################################################################################## */
/* ####################################### Macro #################################### */


/* ################################################################################## */
/* ################################### Type define ################################## */



/* ################################################################################## */
/* ################################### Const Variables ############################## */

/** flash driver header for finding function in special address */

static  FLASH_ROM_API_ENTRY_T * const s_pFlashDriver[FLASH_INSTANCE_COUNT] = FLASHDRV_BASE_ADDR;

/* ################################################################################## */
/* ################################ Local Variables ################################# */



/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */
void FLASHDRIVER_LL_Delay(void);
FLASH_StatusType FLASHDRIVER_SyncEraseCheck(FLASH_DRIVER_ParamType *pFlashParam);
FLASH_StatusType FLASHDRIVER_SyncWriteCheck(FLASH_DRIVER_ParamType *pFlashParam);
static FLASH_StatusType FLASHDRIVER_AsyncEraseCheck(FLASH_DRIVER_ParamType *pFlashParam);
static FLASH_StatusType FLASHDRIVER_AsyncWriteCheck(FLASH_DRIVER_ParamType *pFlashParam);
FLASH_StatusType FLASHDRIVER_LockSector(uint32_t u32Address, uint8_t bLock);
static FLASH_StatusType NVRDRIVER_EraseCheck(FLASH_DRIVER_ParamType *pFlashParam);
static FLASH_StatusType NVRDRIVER_WriteCheck(FLASH_DRIVER_ParamType *pFlashParam);
static FLASH_StatusType NVRDRIVER_LockSector(uint32_t u32Address, uint8_t bLock);
FLASH_StatusType FLASHDRIVER_GetFlashConfig(uint32_t u32Address, FLASH_DRV_ERASESECTOR_CFG_T *pFlash_api_cfg);
static void FLASHDRIVER_INTSingleErase(FLASH_HandleType *pFlashHandle);
static void FLASHDRIVER_INTSingleProgram(FLASH_HandleType *pFlashHandle);


/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */


/* ################################################################################## */
/* ################################ Local Functions ################################# */


/**
 * @brief Local Delay Function
 *
 */
void FLASHDRIVER_LL_Delay(void)
{
    uint32_t u32Tick;

    for (u32Tick = 0; u32Tick < 100; u32Tick++)
    {
        __asm("nop");
    }
}

static Fls_Status_t current_status = FLS_IDLE;

/**
 * @brief Flash Driver Function for Erasing Address Check
 *
 * @param pFlashParam flash driver erase parameter
 */
FLASH_StatusType FLASHDRIVER_SyncEraseCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length;
    FLASH_StatusType tRetVal;

    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;

    if ((u32Addr + u32Length) <= (PFLASH_ADDR_END + 1))
    {
        /* check address align */
        if (u32Addr & (PFLASH_ERASE_SECTOR_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = u32Addr;
        }
        else
        {
            /* check length align */
            if (u32Length & (PFLASH_ERASE_SECTOR_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = u32Addr;
            }
        }
    }
    #if (DFLASH_SUPPORT == STD_ON)
    else if ((DFLASH_ADDR_START <= u32Addr)  && ((u32Addr + u32Length) <= (DFLASH_ADDR_END + 1)))
    {
        /* check address align */
        if (u32Addr & (DFLASH_ERASE_SECTOR_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = u32Addr;
        }
        else
        {
            /* check length align */
            if (u32Length & (DFLASH_ERASE_SECTOR_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = u32Addr;
            }
        }
    }
    #endif
    else
    {
        tRetVal = FLASH_ERROR_INVALID_PARAM;
        pFlashParam->u32ErrorAddress = u32Addr;
    }

    return tRetVal;
}

/**
 * @brief Flash Driver Function for Writing address Check
 *
 * @param pFlashParam flash driver write parameter
 */
FLASH_StatusType FLASHDRIVER_SyncWriteCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length;
    FLASH_StatusType tRetVal;
    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;

    if ((u32Addr + u32Length) <= (PFLASH_ADDR_END + 1))
    {
        /* check address align */
        if (u32Addr & (PFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        }
        /* check length align */
        else
        {
            if (u32Length & (PFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            }
        }
    }
    #if (DFLASH_SUPPORT == STD_ON)
    else if ((DFLASH_ADDR_START <= u32Addr)  && ((u32Addr + u32Length) <= (DFLASH_ADDR_END + 1)))
    {
        /* check length align */
        if (u32Addr & (DFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        }
        else
        {
            if (u32Length & (DFLASH_PROGRAM_PAGE_MIN_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            }
        }
    }
    #endif
    else
    {
        tRetVal = FLASH_ERROR_INVALID_PARAM;
        pFlashParam->u32ErrorAddress = u32Addr;
    }
    return tRetVal;
}

/**
 * @brief Flash Driver Function for Erasing Address Check
 *
 * @param pFlashParam flash driver erase parameter
 */
static FLASH_StatusType FLASHDRIVER_AsyncEraseCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    FLASH_StatusType tRetVal;
    uint32_t u32Addr;
    u32Addr = pFlashParam->u32Address;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;

    if (u32Addr <= PFLASH_ADDR_END)
    {
        /* check address align */
        if (u32Addr & (PFLASH_ERASE_SECTOR_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = u32Addr;
        }
    }
    #if (DFLASH_SUPPORT == STD_ON)
    else if ((DFLASH_ADDR_START <= u32Addr)  && (u32Addr <= DFLASH_ADDR_END))
    {
        /* check address align */
        if (u32Addr & (DFLASH_ERASE_SECTOR_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = u32Addr;
        }
    }
    #endif
    else
    {
        tRetVal = FLASH_ERROR_INVALID_PARAM;
        pFlashParam->u32ErrorAddress = u32Addr;
    }

    return tRetVal;
}

/**
* @brief        Check whether u32TargetAddress is page start aligned
* @param[in]    u32TargetAddress Target address in flash memory
* @return       boolean
* @retval       TRUE u32TargetAddress is in range and aligned to start of the fixed size
* @retval       FALSE u32TargetAddress is not in range or aligned to start of fixed size
*/
static FLASH_StatusType FLASHDRIVER_AsyncWriteCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr;
    FLASH_StatusType tRetVal;
    u32Addr = pFlashParam->u32Address;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;

    if ((u32Addr + FLASH_PROGRAM_PAGE_MAX_SIZE) <= (PFLASH_ADDR_END + 1))
    {
        /* check address align */
        if (u32Addr & (FLASH_PROGRAM_PAGE_MAX_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        }
    }
    #if (DFLASH_SUPPORT == STD_ON)
    else if ((DFLASH_ADDR_START <= u32Addr)  && ((u32Addr + FLASH_PROGRAM_PAGE_MAX_SIZE) <= (DFLASH_ADDR_END + 1)))
    {
        /* check address align */
        if (u32Addr & (FLASH_PROGRAM_PAGE_MAX_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        }
    }
    #endif
    else
    {
        tRetVal = FLASH_ERROR_INVALID_PARAM;
        pFlashParam->u32ErrorAddress = u32Addr;
    }
    return tRetVal;
}

/**
 * @brief Flash Driver Function for lock/unlock sector
 *
 * @param u32Address sector address
 * @param bLock 0U-unlock, 1U-lock
 */
FLASH_StatusType FLASHDRIVER_LockSector(uint32_t u32Address, uint8_t bLock)
{
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;
    uint32 u32Index = 0;
    uint32 u32Length = 0;
    uint32 u32Temp = 0;

    /* 1 bank contains more than 256KB, used FB_CPELCK for first and last 256KB used FB_FPELCK */
    if (u32Address <= (PFLASH_ADDR_START + PFLASH_SIZE))
    {
        /* PFLASH bank index */
        u32Index = (u32Address - PFLASH_ADDR_START) / PFLASH_BANK_SIZE;
        u32Length = ((u32Address - PFLASH_ADDR_START) % PFLASH_BANK_SIZE) ;
        #if (PFLASH_FINE_SUPPORT == STD_ON)
        #if (PFLASH_BANK_SIZE - FLASH_256KB_SIZE) > 0U
        if (u32Length < (PFLASH_BANK_SIZE - FLASH_256KB_SIZE))
        {
            u32Temp = ((uint32)1UL << ((u32Address - PFLASH_ADDR_START - PFLASH_BANK_SIZE * u32Index) >> 16));
            u32Temp = bLock ? 0xFFFFFFFFUL : (0xFFFFFFFFUL ^ u32Temp);
            FMC->FB_CPELCK[u32Index] = u32Temp;
        }
        else /* last 256KB */
        #else
            PROCESS_UNUSED_VAR(u32Length);
        #endif
        {
            u32Temp = ((u32Address - PFLASH_ADDR_START - PFLASH_BANK_SIZE * u32Index - PFLASH_PHANTOM_OFFSET) >> 13);
            u32Temp = ((uint32)1UL << u32Temp);
            u32Temp = bLock ? 0xFFFFFFFFUL : (0xFFFFFFFFUL ^ u32Temp);
            FMC->FB_FPELCK[u32Index] = u32Temp;
        }
        #else
        if (u32Length < (PFLASH_BANK_SIZE))
        {
            u32Temp = ((uint32)1UL << ((u32Address - PFLASH_ADDR_START - PFLASH_BANK_SIZE * u32Index) >> 16));
            u32Temp = bLock ? 0xFFFFFFFFUL : (0xFFFFFFFFUL ^ u32Temp);
            FMC->FB_CPELCK[u32Index] = u32Temp;
        }
        #endif
    }
    #if (DFLASH_SUPPORT == STD_ON)
    else if ((u32Address >= DFLASH_ADDR_START) && (u32Address <= DFLASH_ADDR_END))
    {
        u32Temp = 0xFFFFFFFFUL ^ (1UL << ((u32Address - DFLASH_ADDR_START) >> 13));
        FMC->FB_FPELCK[DFLASH_INDEX] = bLock ? 0xFFFFFFFFUL : u32Temp ;
    }
    #endif
    else
    {
        tRetVal = FLASH_ERROR_INVALID_ADDR;
    }
    return tRetVal;
}

/**
 * @brief Flash Driver Function for Erasing NVR Address Check
 *
 * @param pFlashParam flash driver erase NVR parameter
 */
static FLASH_StatusType NVRDRIVER_EraseCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length;
    FLASH_StatusType tRetVal;
    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;
    tRetVal = FLASH_ERROR_OK;

#if(NVR_NUM == 3U)
    if ((NVR0_FLASH_ADDR_START <= u32Addr &&  (u32Addr + u32Length) <= (NVR0_FLASH_ADDR_END + 1)) \
            || (NVR1_FLASH_ADDR_START <= u32Addr &&  (u32Addr + u32Length) <= (NVR1_FLASH_ADDR_END + 1)) \
            || (NVR2_FLASH_ADDR_START <= u32Addr &&  (u32Addr + u32Length) <= (NVR2_FLASH_ADDR_END + 1))
       )
#elif(NVR_NUM == 1U)
   if (NVR_FLASH_ADDR_START <= u32Addr &&  (u32Addr + u32Length) <= (NVR_FLASH_ADDR_END + 1))
#endif
    {
        /* check address align */
        if (u32Addr & (NVR_ERASE_SECTOR_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = u32Addr;
        }
        else
        {
            /* check length align */
            if (u32Length & (NVR_ERASE_SECTOR_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = u32Addr;
            }
        }
    }
    else
    {
        tRetVal = FLASH_ERROR_INVALID_PARAM;
        pFlashParam->u32ErrorAddress = u32Addr;
    }
    return tRetVal;
}

/**
 * \brief Flash Driver Function for Writing NVR address Check
 *
 * \param pFlashParam flash driver write NVR parameter
 */
static FLASH_StatusType NVRDRIVER_WriteCheck(FLASH_DRIVER_ParamType *pFlashParam)
{
    uint32_t u32Addr, u32Length;
    FLASH_StatusType tRetVal;

    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;

    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;

#if(NVR_NUM == 3U)
    if ((NVR0_FLASH_ADDR_START <= u32Addr && u32Addr + u32Length  <= NVR0_FLASH_ADDR_END + 1) || \
            (NVR1_FLASH_ADDR_START <= u32Addr && u32Addr + u32Length  <= NVR1_FLASH_ADDR_END + 1) || \
            (NVR2_FLASH_ADDR_START <= u32Addr && u32Addr + u32Length  <= NVR2_FLASH_ADDR_END + 1))
#elif(NVR_NUM == 1U)
   if (NVR_FLASH_ADDR_START <= u32Addr &&  (u32Addr + u32Length) <= (NVR_FLASH_ADDR_END + 1))
#endif
    {
        /* check address align */
        if (u32Addr & (NVR_PROGRAM_PAGE_MIN_SIZE - 1U))
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
            pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
        }
        /* check length align */
        else
        {
            if (u32Length & (NVR_PROGRAM_PAGE_MIN_SIZE - 1U))
            {
                tRetVal = FLASH_ERROR_INVALID_SIZE;
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
            }
        }
    }
    else
    {
        tRetVal = FLASH_ERROR_INVALID_PARAM;
        pFlashParam->u32ErrorAddress = u32Addr;
    }
    return tRetVal;
}

/**
 * @brief Flash Driver Function for lock/unlock nvr sector
 *
 * @param u32Address sector address
 * @param bLock 0U-unlock, 1U-lock
 */
static FLASH_StatusType NVRDRIVER_LockSector(uint32_t u32Address, uint8_t bLock)
{
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;

    if (bLock)
    {
#if(NVR_NUM == 3U)
        if ((NVR0_FLASH_ADDR_START <= u32Address &&  u32Address <= NVR0_FLASH_ADDR_END) \
                || (NVR1_FLASH_ADDR_START <= u32Address &&  u32Address <= NVR1_FLASH_ADDR_END) \
                || (NVR2_FLASH_ADDR_START <= u32Address &&  u32Address <= NVR2_FLASH_ADDR_END)
           )
#elif(NVR_NUM == 1U)
        if (NVR_FLASH_ADDR_START <= u32Address &&  u32Address <= (NVR_FLASH_ADDR_END + 1))
#endif
        {
            FMC->FN_FPELCK = 0x01;
        }
        else
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
        }
    }
    else
    {
#if(NVR_NUM == 3U)
        if ((NVR0_FLASH_ADDR_START <= u32Address &&  u32Address <= NVR0_FLASH_ADDR_END) \
                || (NVR1_FLASH_ADDR_START <= u32Address &&  u32Address <= NVR1_FLASH_ADDR_END) \
                || (NVR2_FLASH_ADDR_START <= u32Address &&  u32Address <= NVR2_FLASH_ADDR_END)
           )
#elif(NVR_NUM == 1U)
        if (NVR_FLASH_ADDR_START <= u32Address &&  u32Address <= (NVR_FLASH_ADDR_END + 1))
#endif
        {
            FMC->FN_FPELCK = 0x00;
        }
        else
        {
            tRetVal = FLASH_ERROR_INVALID_ADDR;
        }
    }
    return tRetVal;
}

/**
 * @brief Get Flash Configuration
 *
 * @param u32Address the flash address
 * @param pFlash_api_cfg out flash parameter
 */
FLASH_StatusType FLASHDRIVER_GetFlashConfig(uint32_t u32Address, FLASH_DRV_ERASESECTOR_CFG_T *pFlash_api_cfg)
{
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;
    uint32 u32Index = 0;

    if (u32Address <= (PFLASH_ADDR_START + PFLASH_SIZE))
    {
        /* PFLASH bank index */
        u32Index = (u32Address - PFLASH_ADDR_START) / PFLASH_BANK_SIZE;
        pFlash_api_cfg->blk_sel = u32Index;
        pFlash_api_cfg->dest = u32Address;
    }
    #if (DFLASH_SUPPORT == STD_ON)
    else if ((u32Address >= DFLASH_ADDR_START) && (u32Address <= DFLASH_ADDR_END))
    {
        pFlash_api_cfg->blk_sel = 2UL;
        pFlash_api_cfg->dest = u32Address;
    }
    #endif
    else
    {
        tRetVal = FLASH_ERROR_INVALID_ADDR;
    }
    return tRetVal;
}

#if (FLASH_API_1MB_SUPPORT == STD_ON)
/**
* @brief        flash driver interrupt enable
* @param[in]    par
* @return       none
*/
static void FLASHDRIVER_IntEnable(FLASH_HandleType* pFlashHandle)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    FLASH_DRV_MCTL_CFG_T cfg;
    cfg.edcie = 0x02;
    cfg.ehv = 0x02;
    cfg.encie = 0x02;
    cfg.ers = 0x02;
    cfg.ess = 0x02;
    cfg.pecie = 0x01;
    cfg.pgm = 0x02;
    (s_pFlashDriver_FuncHeader)-> FLASH_DRV_Config_FUNC(&cfg);
}
#endif

/**
* @brief        flash driver single erase
* @param[in]    Flash instance
* @return       none
*/
static void FLASHDRIVER_INTSingleErase(FLASH_HandleType *pFlashHandle)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    FLASH_DRV_ERASESECTOR_CFG_T tFlash_api_cfg;

    #if (FLASH_API_1MB_SUPPORT == STD_ON)
    FLASHDRIVER_IntEnable(pFlashHandle);
    #endif
    (s_pFlashDriver_FuncHeader)->FLASH_DRV_ENABLE_HOLD_CFG(1);
    FLASHDRIVER_LockSector(pFlashHandle->tStatus.u32CurrentAddress, 0U);
    FLASHDRIVER_GetFlashConfig(pFlashHandle->tStatus.u32CurrentAddress, &tFlash_api_cfg);

    pFlashHandle->tStatus.u32CurrentAddress += pFlashHandle->tStatus.u32EraseSectorSize;

    __asm(" cpsid i");
    if (FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
    {
        #if (FLASH_TYPE_SUPPORT == STD_ON)
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector(&tFlash_api_cfg, FLASH_TYPE);
        #else
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector(&tFlash_api_cfg);
        #endif
    }
    __asm(" cpsie i");
}

/**
* @brief        flash driver single program
* @param[in]    Flash instance
* @return       none
*/
static void FLASHDRIVER_INTSingleProgram(FLASH_HandleType *pFlashHandle)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    FLASH_DRV_PRGM_CFG_T tFlash_api_cfg;
    uint32_t u32ProgramEndAddr, u32EndAddr;

    u32EndAddr = pFlashHandle->tStatus.u32Address + pFlashHandle->tStatus.u32Length;
    u32ProgramEndAddr = ((pFlashHandle->tStatus.u32CurrentAddress + FLASH_PROGRAM_PAGE_MAX_SIZE) & ~(FLASH_PROGRAM_PAGE_MAX_SIZE - 1U));
    u32ProgramEndAddr = ((u32ProgramEndAddr > u32EndAddr) ? u32EndAddr : u32ProgramEndAddr);
    pFlashHandle->tStatus.u32ProgramSize = u32ProgramEndAddr - pFlashHandle->tStatus.u32CurrentAddress;

    #if (FLASH_API_1MB_SUPPORT == STD_ON)
    FLASHDRIVER_IntEnable(pFlashHandle);
    #endif

    FLASHDRIVER_LockSector(pFlashHandle->tStatus.u32CurrentAddress, 0U);
    tFlash_api_cfg.dest = pFlashHandle->tStatus.u32CurrentAddress;
    tFlash_api_cfg.size = (uint32_t)(pFlashHandle->tStatus.u32ProgramSize) >> 2;  /* one data is 4 bytes  */
    tFlash_api_cfg.pData = (uint32_t *)(pFlashHandle->tStatus.pData);
    tFlash_api_cfg.wdg_tune = WDG_TUNE_DISABLE;

    pFlashHandle->tStatus.u32CurrentAddress += pFlashHandle->tStatus.u32ProgramSize;
    
    __asm(" cpsid i");
    if (FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
    {
        #if (FLASH_TYPE_SUPPORT == STD_ON)
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program(&tFlash_api_cfg, FLASH_TYPE);
        #else
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program(&tFlash_api_cfg);
        #endif
    }
    __asm(" cpsie i");
}

/* ################################################################################## */
/* ################################# Global Functions ############################### */

/**
 * @brief flash driver erase function
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash erase function parameter, address is align to sector, and length is align to sector
 * @return ErrorType
 */
FLASH_StatusType FLASHDRIVER_SyncErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(FLASH_SYNC_ERASE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    uint32_t u32Addr, u32Length;
    uint32_t u32TryCount;
    FLASH_DRV_ERASESECTOR_CFG_T tFlash_api_cfg;
    FLASH_StatusType tRetVal;
    uint32_t u32Temp;
    tRetVal = FLASH_ERROR_OK;

    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */
    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;
    tRetVal = FLASH_ERROR_OK;
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
        pFlashParam->u32Length = PFLASH_ERASE_SECTOR_SIZE;

        /* loop erase */
        for (pFlashParam->u32Address = u32Addr; pFlashParam->u32Address < u32Addr + u32Length;
             pFlashParam->u32Address += PFLASH_ERASE_SECTOR_SIZE)
        {

            FLASHDRIVER_LockSector(pFlashParam->u32Address, 0U);
            FLASHDRIVER_GetFlashConfig(pFlashParam->u32Address, &tFlash_api_cfg);
            /* start erase */
            __asm(" cpsid i");
            if (FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
            {
                #if (FLASH_TYPE_SUPPORT == STD_ON)
                u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector(&tFlash_api_cfg, FLASH_TYPE);
                #else
                u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector(&tFlash_api_cfg);
                #endif
                tRetVal = ((u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED);
            }
            else
            {
                tRetVal = FLASH_ERROR_FAILED;
            }            
            __asm(" cpsie i");
        
            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* erase operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                FLASHDRIVER_LL_Delay();
                /* check erasing still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
                while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 1000000))
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
                    break;
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
                        break;
                    }
                    else
                    {
                        /* trigger watchdog function */
                        if (pFlashParam->wdTriggerFct != ((void *)0))
                        {
                            pFlashParam->wdTriggerFct();
                        }
                    }
                }
            }
            FLASHDRIVER_LockSector(pFlashParam->u32Address, 1U);
        }
    }
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    else
    {
        FLASH_ReportDevError(FLASH_SYNC_ERASE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    return tRetVal;
}

/**
 * @brief flash driver write function
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to page, and length is align to page
 * @return ErrorType
 */
FLASH_StatusType FLASHDRIVER_SyncWrite(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(FLASH_SYNC_WRITE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    uint32_t u32Addr, u32Length, u32DataAddr, u32AlignLen, u32TempLen;
    /* uint8_t *pTempBuf; */
    uint32_t u32AlignOffset, u32Index, u32Count;
    uint32_t u32TryCount;

    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */
    FLASH_DRV_PRGM_CFG_T tFlash_api_cfg;
    FLASH_StatusType tRetVal;
    uint32_t u32Temp;
    tRetVal = FLASH_ERROR_OK;
    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;
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
        u32AlignOffset = u32Addr & (FLASH_PROGRAM_PAGE_MAX_SIZE - 1U);
        u32AlignLen = u32Length + u32AlignOffset;
        u32Count = ((u32AlignLen + (FLASH_PROGRAM_PAGE_MAX_SIZE - 1U)) & ~(FLASH_PROGRAM_PAGE_MAX_SIZE - 1U)) / FLASH_PROGRAM_PAGE_MAX_SIZE;
        u32DataAddr = (uint32_t)pFlashParam->pData;
        u32TempLen = u32AlignLen;

        for (u32Index = 0U; u32Index < u32Count; u32Index++)
        {
            /* real write length in this cycle */
            u32TempLen = u32Length + u32AlignOffset;
            u32TempLen = u32TempLen >= FLASH_PROGRAM_PAGE_MAX_SIZE ? FLASH_PROGRAM_PAGE_MAX_SIZE : u32TempLen;
            u32TempLen -= u32AlignOffset;

            pFlashParam->u32Address = u32Addr;
            pFlashParam->u32Length = u32TempLen;

            /* unlock sector */
            FLASHDRIVER_LockSector(pFlashParam->u32Address, 0U);
            tFlash_api_cfg.dest = pFlashParam->u32Address;
            tFlash_api_cfg.size = pFlashParam->u32Length / 4; /* one data is 4 bytes */
            tFlash_api_cfg.pData = (uint32_t *)u32DataAddr;
            tFlash_api_cfg.wdg_tune = WDG_TUNE_DISABLE;

            /* next address and length */
            u32Addr += u32TempLen;
            u32DataAddr += u32TempLen;
            u32Length -= u32TempLen;

            u32AlignOffset = 0U;

            /* start write */
            __asm(" cpsid i");
            if (FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
            {
                #if (FLASH_TYPE_SUPPORT == STD_ON)
                u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program(&tFlash_api_cfg, FLASH_TYPE);
                #else
                u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program(&tFlash_api_cfg);
                #endif
                tRetVal = ((u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED);
            }
            else
            {
                tRetVal = FLASH_ERROR_FAILED;
            }
            __asm(" cpsie i");

            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* write operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                FLASHDRIVER_LL_Delay();

                /* check write still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
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
                    break;
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
                        break;
                    }
                    else
                    {
                        /* trigger watchdog function */
                        if (pFlashParam->wdTriggerFct != ((void *)0))
                        {
                            pFlashParam->wdTriggerFct();
                        }
                    }
                }
            }
            FLASHDRIVER_LockSector(pFlashParam->u32Address, 1U);
        }
    }
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    else
    {
        FLASH_ReportDevError(FLASH_SYNC_WRITE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    return tRetVal;
}

/**
 * @brief NVR driver erase function
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *   .=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.       *
 *    |                     ______                     |      *
 *    |                  .-"      "-.                  |      *
 *    |                 /            \                 |      *
 *    |     _          |              |          _     |      *
 *    |    ( \         |,  .-.  .-.  ,|         / )    |      *
 *    |     > "=._     | )(__/  \__)( |     _.=" <     |      *
 *    |    (_/"=._"=._ |/     /\     \| _.="_.="\_)    |      *
 *    |           "=._"(_     ^^     _)"_.="           |      *
 *    |               "=\__|IIIIII|__/="               |      *
 *    |              _.="| \IIIIII/ |"=._              |      *
 *    |    _     _.="_.="\          /"=._"=._     _    |      *
 *    |   ( \_.="_.="     `--------`     "=._"=._/ )   |      *
 *    |    > _.="                            "=._ <    |      *
 *    |   (_/                                    \_)   |      *
 *    |                                                |      *
 *    '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-='      *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash erase function parameter, address is align to sector, and length is align to sector
 * @return ErrorType
 */
FLASH_StatusType NVRDRIVER_SyncErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(NVR_SYNC_ERASE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    uint32_t u32Addr, u32Length;
    uint32_t u32TryCount;
    FLASH_StatusType tRetVal;
    uint32_t u32Temp;
    tRetVal = FLASH_ERROR_OK;

    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */
    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = NVRDRIVER_EraseCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_ENABLE_HOLD_CFG(1);
        pFlashParam->u32Length = NVR_ERASE_SECTOR_SIZE;

        /* loop erase */
        for (pFlashParam->u32Address = u32Addr; pFlashParam->u32Address < u32Addr + u32Length;
             pFlashParam->u32Address += NVR_ERASE_SECTOR_SIZE)
        {
            NVRDRIVER_LockSector(pFlashParam->u32Address, 0U);
            /* start erase */
            __asm(" cpsid i");
            if (FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
            {
                #if (NVR_SECTOR_NUM > 1)
                u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseNvr(pFlashParam->u32Address);
                #else
                u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseNvr();
                #endif
                tRetVal = ((u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED);
            }
            else
            {
                tRetVal = FLASH_ERROR_FAILED;
            }
            __asm(" cpsie i");

            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* erase operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                FLASHDRIVER_LL_Delay();
                /* check erasing still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
                while ((tRetVal != FLASH_ERROR_OK) && (u32TryCount++ < 1000000))
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
                    break;
                }
                else
                {
                    FLASHDRIVER_LL_Delay();
                    /* check erasing result */
                    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseNvr_Clear();
                    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

                    if (tRetVal != FLASH_ERROR_OK)
                    {
                        /* erasing failed, exit */
                        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                        break;
                    }
                    else
                    {
                        /* trigger watchdog function */
                        if (pFlashParam->wdTriggerFct != ((void *)0))
                        {
                            pFlashParam->wdTriggerFct();
                        }

                    }
                }
            }
            NVRDRIVER_LockSector(pFlashParam->u32Address, 1U);
        }
    }
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    else
    {
        FLASH_ReportDevError(NVR_SYNC_ERASE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    return tRetVal;
}

/**
 * @brief NVR driver write function
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *    warning:Need to configure the NVR correctly, otherwise there is a risk that the chip will become bricked.
 *   .=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.       *
 *    |                     ______                     |      *
 *    |                  .-"      "-.                  |      *
 *    |                 /            \                 |      *
 *    |     _          |              |          _     |      *
 *    |    ( \         |,  .-.  .-.  ,|         / )    |      *
 *    |     > "=._     | )(__/  \__)( |     _.=" <     |      *
 *    |    (_/"=._"=._ |/     /\     \| _.="_.="\_)    |      *
 *    |           "=._"(_     ^^     _)"_.="           |      *
 *    |               "=\__|IIIIII|__/="               |      *
 *    |              _.="| \IIIIII/ |"=._              |      *
 *    |    _     _.="_.="\          /"=._"=._     _    |      *
 *    |   ( \_.="_.="     `--------`     "=._"=._/ )   |      *
 *    |    > _.="                            "=._ <    |      *
 *    |   (_/                                    \_)   |      *
 *    |                                                |      *
 *    '-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-='      *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to page, and length is align to page
 * @return ErrorType
 */
FLASH_StatusType NVRDRIVER_SyncWrite(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(NVR_SYNC_WRITE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    uint32_t u32Addr, u32Length, u32DataAddr, u32AlignLen, u32TempLen;
    /* uint8_t *pTempBuf; */
    uint32_t u32AlignOffset, u32Index, u32Count;
    uint32_t u32TryCount;

    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */
    FLASH_DRV_PRGM_CFG_T tFlash_api_cfg;
    FLASH_StatusType tRetVal;
    uint32_t u32Temp;
    tRetVal = FLASH_ERROR_OK;
    u32Addr = pFlashParam->u32Address;
    u32Length = pFlashParam->u32Length;
    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = NVRDRIVER_WriteCheck(pFlashParam);
    if (tRetVal == FLASH_ERROR_OK)
    {
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_ENABLE_HOLD_CFG(1);

        /* align address, write must align to NVRFLASH_PROGRAM_PAGE_MAX_SIZE */
        u32AlignOffset = u32Addr & (NVRFLASH_PROGRAM_PAGE_MAX_SIZE - 1U);
        u32AlignLen = u32Length + u32AlignOffset;
        u32Count = ((u32AlignLen + (NVRFLASH_PROGRAM_PAGE_MAX_SIZE - 1U)) & ~(NVRFLASH_PROGRAM_PAGE_MAX_SIZE - 1U)) / NVRFLASH_PROGRAM_PAGE_MAX_SIZE;
        u32DataAddr = (uint32_t)pFlashParam->pData;
        u32TempLen = u32AlignLen;

        for (u32Index = 0U; u32Index < u32Count; u32Index++)
        {
            /* real write length in this cycle */
            u32TempLen = u32Length + u32AlignOffset;
            u32TempLen = u32TempLen >= NVRFLASH_PROGRAM_PAGE_MAX_SIZE ? NVRFLASH_PROGRAM_PAGE_MAX_SIZE : u32TempLen;
            u32TempLen -= u32AlignOffset;

            pFlashParam->u32Address = u32Addr;
            pFlashParam->u32Length = u32TempLen;

            /* unlock sector */
            NVRDRIVER_LockSector(pFlashParam->u32Address, 0U);
            tFlash_api_cfg.dest = pFlashParam->u32Address;
            tFlash_api_cfg.size = pFlashParam->u32Length / 4; /* one data is 4 bytes */
            tFlash_api_cfg.pData = (uint32_t *)u32DataAddr;
            tFlash_api_cfg.wdg_tune = WDG_TUNE_DISABLE;

            /* next address and length */
            u32Addr += u32TempLen;
            u32DataAddr += u32TempLen;
            u32Length -= u32TempLen;
            u32AlignOffset = 0U;

            /* start write */
            __asm(" cpsid i");
            if (FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
            {
                u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program_Nvr(&tFlash_api_cfg);
                tRetVal = ((u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED);
            }
            else
            {
                tRetVal = FLASH_ERROR_FAILED;
            }
            __asm(" cpsie i");

            /* check erase operation valid */
            if (tRetVal != FLASH_ERROR_OK)
            {
                /* write operation failed, exit */
                pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                break;
            }
            else
            {
                FLASHDRIVER_LL_Delay();

                /* check write still in progress */
                tRetVal = FLASH_ERROR_FAILED;
                u32TryCount = 0;
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
                    break;
                }
                else
                {
                    FLASHDRIVER_LL_Delay();

                    /* check write result */
                    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program_Nvr_Clear();
                    tRetVal = (u32Temp == STATUS_SUCCESS) ? FLASH_ERROR_OK : FLASH_ERROR_FAILED;

                    if (tRetVal != FLASH_ERROR_OK)
                    {
                        /* write failed, exit */
                        pFlashParam->u32ErrorAddress = pFlashParam->u32Address;
                        break;
                    }
                    else
                    {
                        /* trigger watchdog function */
                        if (pFlashParam->wdTriggerFct != ((void *)0))
                        {
                            pFlashParam->wdTriggerFct();
                        }
                    }
                }
            }
            NVRDRIVER_LockSector(pFlashParam->u32Address, 1U);
        }
    }
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    else
    {
        FLASH_ReportDevError(NVR_SYNC_WRITE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    return tRetVal;
}

/**
 * @brief flash driver erase a sector
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to sector, and length is align to sector
 */
void FLASHDRIVER_AsyncErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(FLASH_ASYNC_ERASE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    FLASH_DRV_ERASESECTOR_CFG_T tFlash_api_cfg;
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;

    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = FLASHDRIVER_AsyncEraseCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        (s_pFlashDriver_FuncHeader)->FLASH_DRV_ENABLE_HOLD_CFG(1);
        FLASHDRIVER_LockSector(pFlashParam->u32Address, 0U);
        FLASHDRIVER_GetFlashConfig(pFlashParam->u32Address, &tFlash_api_cfg);
        /* check erase operation valid */
        __asm(" cpsid i");
        if(FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
        {
            #if (FLASH_TYPE_SUPPORT == STD_ON)
            if ((s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector(&tFlash_api_cfg, FLASH_TYPE) != STATUS_SUCCESS)
            #else
            if ((s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector(&tFlash_api_cfg) != STATUS_SUCCESS)
            #endif
            {
                current_status = FLS_ERASE_ERROR;
            }
            else
            {
                current_status = FLS_ERASING;
            }
        }
        else
        {
            current_status = FLS_ERASE_ERROR;
        }
        __asm(" cpsie i");
    }
    else
    {
        #if FLASH_DEV_ERROR_REPORT == STD_ON
        FLASH_ReportDevError(FLASH_ASYNC_ERASE_ID, FLASH_E_PARAM_POINTER);
        #endif
        current_status = FLS_PARA_ERROR;
    }
}

/**
 * @brief flash driver erase a sector
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam contains flash write function parameter, address is align to max size of program
 */
void FLASHDRIVER_AsyncWrite(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(FLASH_ASYNC_WRITE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    /* FLASH_DRV_WDG_CFG_T tFlash_wdg_cfg; */
    FLASH_DRV_PRGM_CFG_T tFlash_api_cfg;
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = FLASHDRIVER_AsyncWriteCheck(pFlashParam);
    if (tRetVal == FLASH_ERROR_OK)
    {
        FLASHDRIVER_LockSector(pFlashParam->u32Address, 0U);
        tFlash_api_cfg.dest = pFlashParam->u32Address;
        tFlash_api_cfg.size = (uint32_t)(FLASH_PROGRAM_PAGE_MAX_SIZE) >> 2;  /* one data is 4 bytes  */
        tFlash_api_cfg.pData = (uint32_t *)(pFlashParam->pData);
        tFlash_api_cfg.wdg_tune = WDG_TUNE_DISABLE;
        __asm(" cpsid i");
        if(FLASH_HARDWARE_STATUS_IDLE == (((*(volatile uint32 *)FLASH_HARDWARE_STATUS_ADDR) & FLASH_HARDWARE_STATUS_MASK) >> 16))
        {
            #if (FLASH_TYPE_SUPPORT == STD_ON)
            if ((s_pFlashDriver_FuncHeader)->FLASH_DRV_Program(&tFlash_api_cfg, FLASH_TYPE) != STATUS_SUCCESS)
            #else
            if ((s_pFlashDriver_FuncHeader)->FLASH_DRV_Program(&tFlash_api_cfg) != STATUS_SUCCESS)
            #endif
            {
                current_status = FLS_WRITE_ERROR;
            }
            else
            {
                current_status = FLS_WRITING;
            }
        }
        else
        {
            current_status = FLS_WRITE_ERROR;
        }
        __asm(" cpsie i");
    }
    else
    {
        #if FLASH_DEV_ERROR_REPORT == STD_ON
        FLASH_ReportDevError(FLASH_ASYNC_ERASE_ID, FLASH_E_PARAM_POINTER);
        #endif
        current_status = FLS_PARA_ERROR;
    }
}

/**
 * @brief flash driver check current status when erasing
 *
 * @param pFlashHandle the Flash instance to use
 * @return Fls_Return_t return the erase status
 */
Async_Return_t FLASHDRIVER_AsyncCheckEraseStatus(FLASH_HandleType *pFlashHandle)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    Async_Return_t async_ret = FLASH_ASYNC_ERR_NOT_OK;
    if (current_status == FLS_ERASING)
    {
        /* check if finished */
        if (STATUS_HVOP == (s_pFlashDriver_FuncHeader)->FLASH_DRV_HV_Status_Check())
        {
            async_ret = FLASH_ASYNC_ERR_BUSY;
        }
        else
        {
            if (FLASH_PES_CHECK == ((s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check(FLASH_PES_CHECK) & FLASH_PES_CHECK))
            {
                (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector_Clear();
                (s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check_Clear(FLASH_PES_CHECK);
                async_ret = FLASH_ASYNC_ERR_NOT_OK;
            }
            else
            {
                if (STATUS_SUCCESS == (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector_Clear())
                {
                    async_ret = FLASH_ASYNC_ERR_OK;
                }
                else
                {
                    async_ret = FLASH_ASYNC_ERR_NOT_OK;
                }
            }
            current_status = FLS_IDLE;
        }
    }
    else if (current_status == FLS_IDLE)
    {
        async_ret = FLASH_ASYNC_ERR_OK;
    }
    return async_ret;
}

/**
 * @brief flash driver check current status when writing
 *
 * @param pFlashHandle the Flash instance to use
 * @return Fls_Return_t return the write status
 */
Async_Return_t FLASHDRIVER_AsyncCheckWriteStatus(FLASH_HandleType *pFlashHandle)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    Async_Return_t async_ret = FLASH_ASYNC_ERR_NOT_OK;
    if (current_status == FLS_WRITING)
    {
        /* check if finished */
        if (STATUS_HVOP == (s_pFlashDriver_FuncHeader)->FLASH_DRV_HV_Status_Check())
        {
            async_ret = FLASH_ASYNC_ERR_BUSY;
        }
        else
        {
            if (FLASH_PES_CHECK == ((s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check(FLASH_PES_CHECK) & FLASH_PES_CHECK))
            {
                (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program_Clear();
                (s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check_Clear(FLASH_PES_CHECK);
                async_ret = FLASH_ASYNC_ERR_NOT_OK;
            }
            else
            {
                if (STATUS_SUCCESS == (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program_Clear())
                {
                    async_ret = FLASH_ASYNC_ERR_OK;
                }
                else
                {
                    async_ret = FLASH_ASYNC_ERR_NOT_OK;
                }
            }
            current_status = FLS_IDLE;
        }
    }
    else if (current_status == FLS_IDLE)
    {
        async_ret = FLASH_ASYNC_ERR_OK;
    }
    return async_ret;
}

/**
 * @brief flash driver interrupt erase
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam erase parameter
 */
void FLASHDRIVER_InterruptErase(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(FLASH_INTERRUPT_ERASE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = FLASHDRIVER_SyncEraseCheck(pFlashParam);

    if (tRetVal == FLASH_ERROR_OK)
    {
        pFlashHandle->tStatus.eFlsStatus = FLS_ERASING;
        pFlashHandle->tStatus.u32Address = pFlashParam->u32Address;
        pFlashHandle->tStatus.u32Length = pFlashParam->u32Length;
        pFlashHandle->tStatus.u32CurrentAddress = pFlashParam->u32Address;
        pFlashHandle->tStatus.u32EraseSectorSize = PFLASH_ERASE_SECTOR_SIZE;

        FLASHDRIVER_INTSingleErase(pFlashHandle);
    }
    else
    {
        #if FLASH_DEV_ERROR_REPORT == STD_ON
        FLASH_ReportDevError(FLASH_INTERRUPT_ERASE_ID, FLASH_E_PARAM_POINTER);
        #endif
        current_status = FLS_PARA_ERROR;
    }
}

/**
 * @brief flash driver interrupt write
 *
 * @param pFlashHandle the Flash instance to use
 * @param pFlashParam write parameter
 */
void FLASHDRIVER_InterruptProgram(FLASH_HandleType *pFlashHandle, FLASH_DRIVER_ParamType *pFlashParam)
{
    #if FLASH_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFlashParam)
    {
        FLASH_ReportDevError(FLASH_INTERRUPT_WRITE_ID, FLASH_E_PARAM_POINTER);
    }
    #endif
    FLASH_StatusType tRetVal;
    tRetVal = FLASH_ERROR_OK;
    pFlashParam->u32ErrorAddress = 0x0U;
    tRetVal = FLASHDRIVER_SyncWriteCheck(pFlashParam);
    if (tRetVal == FLASH_ERROR_OK)
    {
        pFlashHandle->tStatus.eFlsStatus = FLS_WRITING;
        pFlashHandle->tStatus.u32Address = pFlashParam->u32Address;
        pFlashHandle->tStatus.u32Length = pFlashParam->u32Length;
        pFlashHandle->tStatus.u32CurrentAddress = pFlashParam->u32Address;
        pFlashHandle->tStatus.pData = pFlashParam->pData;

        FLASHDRIVER_INTSingleProgram(pFlashHandle);
    }
    else
    {
        #if FLASH_DEV_ERROR_REPORT == STD_ON
        FLASH_ReportDevError(FLASH_INTERRUPT_WRITE_ID, FLASH_E_PARAM_POINTER);
        #endif
        current_status = FLS_PARA_ERROR;
    }
}

/**
 * @brief flash driver ecc type check
 *
 * @param pFlashHandle the Flash instance to use
 * @param pECCType ecc type input addr
 * @return return the ecc check status
 */
uint32_t FLASHDRIVER_ECCType_Check(FLASH_HandleType *pFlashHandle, ECC_StatusType *pECCType)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    uint32_t u32RetVal = false;
    if (STATUS_ECC_WARNING == (s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check((uint32_t)FLASH_SBC_CHECK))
    {
        *pECCType = FLASH_ECC_ERROR_SBC;
        if (STATUS_SUCCESS == (s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check_Clear((uint32_t)FLASH_SBC_CHECK))
        {
            u32RetVal = true;
        }
        else
        {
            u32RetVal = false;
        }
    }
    else if (STATUS_ECC_ERROR == (s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check((uint32_t)FLASH_ECC_CHECK))
    {
        *pECCType = FLASH_ECC_ERROR_DBC;
        if (STATUS_SUCCESS == (s_pFlashDriver_FuncHeader)->FLASH_DRV_Read_Status_Check_Clear((uint32_t)FLASH_ECC_CHECK))
        {
            u32RetVal = true;
        }
        else
        {
            u32RetVal = false;
        }
    }
    else
    {
        *pECCType = FLASH_ECC_ERROR_NONE;
        u32RetVal = true;
    }
    return u32RetVal;
}

/**
 * @brief Tests the ECC functionality of the flash.
 *
 * This function performs an ECC test on the flash by opening the test mode, checking the ECC,
 * and then closing the test mode. It returns a status indicating whether the ECC check was successful.
 *
 * @param pFlashHandle Pointer to the flash handle structure.
 * @param pECCParam Pointer to the ECC check configuration structure.
 * @param pECCType Pointer to store the type of ECC error detected.
 *
 * @return A `uint32_t` value indicating the success or failure of the ECC test:
 *         - `true` if the ECC test was successful.
 *         - `false` if the ECC test failed.
 */
uint32_t FLASHDRIVER_ECC_Test(FLASH_HandleType *pFlashHandle, FLASH_DRV_ECC_CHECK_CFG_T *pECCParam, ECC_StatusType *pECCType)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    volatile uint32_t u32Temp = 1;
    uint32_t u32RetVal = false;
    FMC->FAPC0 &= ~(FMC_FAPC0_CBBEN_MASK | FMC_FAPC0_DBBEN_MASK);
    #if (FC4150_512K_ECC_TEST == STD_ON)

    #if (FLASH_TYPE_SUPPORT == STD_ON)
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_ECC_Check(pECCParam, FLASH_TYPE);
    #else
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_ECC_Check(pECCParam);
    #endif


    #else
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Test_Mode_Open();

    #if (FLASH_TYPE_SUPPORT == STD_ON)
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_ECC_Check(pECCParam, FLASH_TYPE);
    #else
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_ECC_Check(pECCParam);
    #endif

    #endif
    if (u32Temp == STATUS_SUCCESS)
    {
        #if (FC4150_512K_ECC_TEST == STD_ON)
        *(uint32_t *)0x40020094 = *(uint32_t *)0x40020094 | (1 << 30);
        #endif
        u32Temp = *(uint32_t *)(pECCParam->dest);
        u32RetVal = FLASHDRIVER_ECCType_Check(pFlashHandle, pECCType);
        #if (FC4150_512K_ECC_TEST == STD_ON)
        *(uint32_t *)0x40020094 &= (uint32_t)( ~(1 << 12));
        #endif
    }
    else
    {
        u32RetVal = false;
    }
    (s_pFlashDriver_FuncHeader)->FLASH_DRV_Test_Mode_Close();
    FMC->FAPC0 |= (FMC_FAPC0_CBBEN_MASK | FMC_FAPC0_DBBEN_MASK);
    return u32RetVal;
}

/**
 * @brief flash driver misr test
 *
 * @param pFlashHandle the Flash instance to use
 * @param pMisrParam misr test input para addr
 * @param tMisrOutput misr test output para addr
 * @return return misr test status
 */
uint32_t FLASHDRIVER_Integrity_Test(FLASH_HandleType *pFlashHandle, FLASH_DRV_TEST_CHECK_CFG_T *pMisrParam, FLASH_DRV_TEST_CHECK_DATA_CFG_T *tMisrOutput)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    uint32_t u32Temp;
    #if (FC4150_512K_ECC_TEST == STD_ON)
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Array_Integrity_Check(pMisrParam);
    #else
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Test_Mode_Open();
    u32Temp = (s_pFlashDriver_FuncHeader)->FLASH_DRV_Array_Integrity_Check(pMisrParam);
    #endif
    if (u32Temp != STATUS_SUCCESS)
    {
        return false;
    }
    while ((s_pFlashDriver_FuncHeader)->FLASH_DRV_Test_Status_Check(tMisrOutput) != 0);
    #if (FC4150_512K_ECC_TEST == STD_ON)
    *(uint32_t *)0x40020094 &= (uint32)(~(1 << 5));
    #endif
    (s_pFlashDriver_FuncHeader)->FLASH_DRV_Test_Mode_Close();
    return true;
}

/**
 * @brief flash driver test close
 *
 * @param pFlashHandle the Flash instance to use
 */
void FLASHDRIVER_Test_Close(FLASH_HandleType *pFlashHandle)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    (s_pFlashDriver_FuncHeader)->FLASH_DRV_Test_Mode_Close();
}

/**
* @brief        flash driver init
*/
void FLASHDRIVER_Init(void)
{
    #if SMISC_ROM_CLOCK_GATING_SUPPORT
    SMISC->SYSCGC |= SMISC_SYSCGC_CGCROM(1);
    #endif
}

Fls_ReturnType Fls_CommonProcessInterrupt(FLASH_HandleType *pFlashHandle)
{
    FLASH_ROM_API_ENTRY_T *const s_pFlashDriver_FuncHeader = s_pFlashDriver[pFlashHandle->eInstance];
    Fls_ReturnType interrupt_ret = FLASH_INTERRUPT_ERR_NOT_OK;
    if (pFlashHandle->tStatus.eFlsStatus == FLS_WRITING)
    {
        /* check if finished */
        if (STATUS_SUCCESS == (s_pFlashDriver_FuncHeader)->FLASH_DRV_Program_Clear())
        {
            interrupt_ret = FLASH_INTERRUPT_ERR_OK;
            if (pFlashHandle->tStatus.u32CurrentAddress < (pFlashHandle->tStatus.u32Address + pFlashHandle->tStatus.u32Length))
            {
                pFlashHandle->tStatus.pData += pFlashHandle->tStatus.u32ProgramSize;
                FLASHDRIVER_INTSingleProgram(pFlashHandle);
            }
            else
            {
                pFlashHandle->tStatus.eFlsStatus = FLS_IDLE;
            }
        }
        else
        {
            interrupt_ret = FLASH_INTERRUPT_ERR_NOT_OK;
        }

    }
    else if (pFlashHandle->tStatus.eFlsStatus == FLS_ERASING)
    {

        if (STATUS_SUCCESS == (s_pFlashDriver_FuncHeader)->FLASH_DRV_EraseSector_Clear())
        {
            interrupt_ret = FLASH_INTERRUPT_ERR_OK;
            if (pFlashHandle->tStatus.u32CurrentAddress < (pFlashHandle->tStatus.u32Address + pFlashHandle->tStatus.u32Length))
            {
                FLASHDRIVER_INTSingleErase(pFlashHandle);
            }
            else
            {
                pFlashHandle->tStatus.eFlsStatus = FLS_IDLE;
            }
        }
        else
        {
            interrupt_ret = FLASH_INTERRUPT_ERR_NOT_OK;
        }

    }
    else
    {

    }
    return interrupt_ret;
}

#endif
