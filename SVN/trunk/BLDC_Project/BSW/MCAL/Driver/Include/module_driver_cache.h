/**
 * @file module_driver_cache.h
 * @author Flagchip051
 * @brief CACHE driver type definition and API
 * @version 2.0.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_CACHE_H_
#define _DRIVER_MODULE_DRIVER_CACHE_H_

#include "HwA_cache.h"

#if CCU_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_cache
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

#define CACHE_TIMEOUT_VALUE   10000U
#define CACHE_LINE_SIZE       16
#define CACHE_CODE_SIZE       8192



/**
 * @brief Clear the cache.
 *
 */
FCCACHE_StatusType CCACHE_Driver_Clear(void);

/**
 * @brief Disable the cache.
 *
 */
void FCCACHE_Driver_Disable(void);

/**
 * @brief Only clear the cache no matter whether the cache is enabled
 *
 * @return FCCACHE_StatusType return FCCACHE_STATUS_SUCCESS when clear successfully, others, fail
 */
FCCACHE_StatusType FCCACHE_Driver_Enable(void);

/**
 * @brief Clear partly cache.
 *
 */
FCCACHE_StatusType FCCACHE_Driver_Clear_MultiLines(uint32 u32PhyAddr, uint32 u32Length);


#if defined(__cplusplus)
}
#endif

/** @} */ /* module_driver_cache */

#endif

#endif /* _DRIVER_MODULE_DRIVER_CACHE_H_ */
