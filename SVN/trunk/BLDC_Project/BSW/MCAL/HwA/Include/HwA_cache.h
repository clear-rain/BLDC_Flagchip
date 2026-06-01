/**
 * @file HwA_cache.h
 * @author Flagchip054
 * @brief  CACHE hardware access layer
 * @version 2.0.0
 * @date 2024-04-13
 * 
 * @copyright Copyright (c) 2020-2024
 * 
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/

#ifndef HWA_CACHE_H_
#define HWA_CACHE_H_

#include "device_header.h"

#if CCU_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_cache HwA_cache
 * @ingroup module_driver_cache
 * @{
 */

/**
 * @brief Status returned by FCCache APIs
 *
 */
typedef enum {
    FCCACHE_STATUS_SUCCESS = 0, /**< API execute successfully */
    FCCACHE_STATUS_FAIL,        /**< API execute fail, some error occur */
} FCCACHE_StatusType;


/**
 * @brief enable cache
 *
 */
LOCAL_INLINE void CACHE_HWA_Enable(void)
{
	CCU->CTRL = CCU_CTRL_CE(1);
}

/**
 * @brief disable cache
 *
 */
LOCAL_INLINE void CACHE_HWA_Disable(void)
{
	CCU->CTRL = 0x00000000U;
}

/**
 * @brief clear the cache data
 *
 */
LOCAL_INLINE void CACHE_HWA_Clear(void)
{
	CCU->CTRL |= CCU_CTRL_CC(0x85);
}

/**
 * @brief get ctrl register
 *
 */
LOCAL_INLINE uint32_t CACHE_HWA_Clear_Is_Done(void)
{
	return ((CCU->CTRL >> CCU_CTRL_CC_SHIFT) == 0);
}


/**
 * @brief get ctrl register
 *
 */
LOCAL_INLINE uint32_t CACHE_HWA_Get_CTRL(void)
{
	return CCU->CTRL;
}

/**
 * @brief write clear cache line command
 *
 */
LOCAL_INLINE void CACHE_HWA_Line_Clear(void)
{
	CCU->CLCR = 0x05000000;
}

/**
 * @brief start clear cache line
 *
 */
LOCAL_INLINE void CACHE_HWA_Line_Clear_Start(void)
{
	CCU->CLCR |= 0x01;
}

/**
 * @brief start clear cache line
 *
 */
LOCAL_INLINE uint32_t CACHE_HWA_Line_Clear_Is_Done(void)
{
	return ((CCU->CSAR & 0x01) == 0);
}

/**
 * @brief clear the cache line
 *
 */
LOCAL_INLINE void CACHE_HWA_Set_Addr(uint32_t u32PhyAddr)
{
	CCU->CSAR = CSAR_PHYADDR_MASK_U32 & u32PhyAddr;
}

/** @}*/

#endif

#endif /* HWA_INCLUDE_HWA_CACHE_H_ */
