/**
 * @file module_driver_cache.c
 * @author Flagchip051
 * @brief CACHE driver source code
 * @version 2.0.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/

#include "module_driver_cache.h"

static FCCACHE_StatusType FCCACHE_Driver_Clear_Line(uint32_t u32Addr)
{
	uint32_t  u32TryCnt = 0U;
	FCCACHE_StatusType eRet = FCCACHE_STATUS_SUCCESS;
	CACHE_HWA_Line_Clear();
	CACHE_HWA_Set_Addr(u32Addr);            // physical address of SOC
	CACHE_HWA_Line_Clear_Start();            // start cache line clear
	while(!CACHE_HWA_Line_Clear_Is_Done())
	{
        u32TryCnt++;
        if (u32TryCnt > CACHE_TIMEOUT_VALUE) /* clear cache need about 250 sys_clkcycle, this should large enough  */
        {
            eRet = FCCACHE_STATUS_FAIL;
            break;
        }
	}
	return eRet;
}

FCCACHE_StatusType CCACHE_Driver_Clear(void)
{
    uint32_t    u32TryCnt = 0U;
    FCCACHE_StatusType eRet      = FCCACHE_STATUS_SUCCESS;

    CACHE_HWA_Clear(); /* clear the cache */
    
    while (0U != (CACHE_HWA_Get_CTRL() & CCU_CTRL_CC(0x80))) /* clear not finish */
    {
        u32TryCnt++;
        if (u32TryCnt > 10000U) /* clear cache need about 250 sys_clkcycle, this should large enough  */
        {
            eRet = FCCACHE_STATUS_FAIL;
            break;
        }
    }

    return eRet;
}

/*
 * disable the cache hardware
 */
void FCCACHE_Driver_Disable(void)
{
    CACHE_HWA_Disable();
}

/* clear the cache and enable */
FCCACHE_StatusType FCCACHE_Driver_Enable(void)
{
    FCCACHE_StatusType eRet = FCCACHE_STATUS_SUCCESS;

    CACHE_HWA_Disable(); /* disable cache */

    if (FCCACHE_STATUS_SUCCESS != CCACHE_Driver_Clear())
    {
        eRet = FCCACHE_STATUS_FAIL;
    }
    else
    {
        CACHE_HWA_Enable(); /* enable cache */
    }

    return eRet;
}

/**
 * @brief Clear partly cache.
 *
 */
FCCACHE_StatusType FCCACHE_Driver_Clear_MultiLines(uint32 u32PhyAddr, uint32 u32Length)
{
	FCCACHE_StatusType eRet = FCCACHE_STATUS_SUCCESS;
    uint32_t u32EndAddr = u32PhyAddr + u32Length;

    /* Align physical address to the cache line size. */
    u32PhyAddr = u32PhyAddr & ~(CACHE_LINE_SIZE - 1U);

    /* Flush entire cache if length is greater than half the size of the cache. */
    if (u32Length >= (CACHE_CODE_SIZE/2))
    {
    	eRet = CCACHE_Driver_Clear();
    }
    else /* Else, invalidate by line. */
    {
        while((u32PhyAddr < u32EndAddr) && (eRet == FCCACHE_STATUS_SUCCESS))
        {
        	eRet = FCCACHE_Driver_Clear_Line(u32PhyAddr);
            u32PhyAddr = u32PhyAddr + CACHE_LINE_SIZE;
        }
    }

    return eRet;
}

