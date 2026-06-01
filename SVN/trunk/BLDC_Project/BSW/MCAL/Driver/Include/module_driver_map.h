/**
 * @file module_driver_map.h
 * @author Flagchip054
 * @brief MAP driver type definition and API
 * @version 2.0.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details The MAP only checks the non-CPU master access to CTCM and DTCM memory. When access denied, it will cause BusFault Interrupt.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_MAP_H_
#define _DRIVER_MODULE_DRIVER_MAP_H_

#include "HwA_map.h"

#if MAP_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup module_driver_map
 * @{
 */

/**
 * @brief Get Error Information when Access denied
 *
 * @param pInf The address stored the error information
 * @return FCMAP_StatusType FCMAP_STATUS_SUCCESS when no error occur, or return FCMAP_STATUS_ACCESS_DENIED.
 */
FCMAP_StatusType FCMAP_GetErrorInformation(FCMAP_ErrorInfoType *pInf);

/**
 * @brief Enable the MAP
 *
 * @note When the CPU start to work, default the MAP is enabled, and only Region 0 is enabled and all permission is allowed.
 */
void FCMAP_Enable(void);

/**
 * @brief Disable the MAP
 *
 * @note After disable the MAP, all access is allowed.
 */
void FCMAP_Disable(void);

/**
 * @brief Check the MAP has been enabled
 *
 * @return TRUE  MAP has been enabled
 * @return FALSE  MAP has not been enabled
 */
boolean FCMAP_CheckEnable(void);

/**
 * @brief Check the MAP region has been enabled, it not ensure the MAP is enabled
 *
 * @param eRegion The region ID
 * @return TRUE the region all enabled
 * @return FALSE the region is not enabled
 */
boolean FCMAP_CheckRegionEnable(FCMAP_RegionIdType eRegion);


/**
 * @brief enable the region with permission configuration
 *
 * @param pConf  Permission parameter
 * @return FCMAP_StatusType FCMAP_STATUS_SUCCESS when enable success, others fail
 * @note @verbatim
Before enabling the region, ensure MAP is enabled already.
Region 0 can't be enable, it only allow to update its permission configuration or disable it.
The other Regions can't be re-enabled, only allow to enable it after disabled.
 @endverbatim
 *
 */
FCMAP_StatusType FCMAP_RegionEnable(const FCMAP_RegionConfigurationType *pConf);

/**
 * @brief Get the configuration of region
 *
 * @param eRegion Region ID
 * @param pConf  Address to store the configuration
 * @return FCMAP_StatusType FCMAP_STATUS_SUCCESS when successfully, or some error occur.
 */
FCMAP_StatusType FCMAP_GetRegionConfiguration(FCMAP_RegionIdType eRegion, FCMAP_RegionConfigurationType *pConf);

/**
 * @brief Disable the region
 *
 * @param eRegion Region ID
 * @return FCMAP_StatusType FCMAP_STATUS_SUCCESS when successfully, or some error occur.
 */
FCMAP_StatusType FCMAP_RegionDisable(FCMAP_RegionIdType eRegion);


/* FCMAP_UpdateRegionPermission only work when MAP and REGION all enabled */
/**
 * @brief Update the permission of region(MAP and region Must enabled already)
 *
 * @param eRegion Region ID
 * @param eDmaPermission DMA Access Permission
 * @param eEnetPermission Enet Access Permission
 * @param eHsmPermission Hsm Access Permission
 * @return FCMAP_StatusType FCMAP_STATUS_SUCCESS when successfully, or some error occur.
 */
FCMAP_StatusType FCMAP_UpdateRegionPermission(FCMAP_RegionIdType eRegion,
    FCMAP_AccessPermissionType  eDmaPermission,
    FCMAP_AccessPermissionType  eEnetPermission,
    FCMAP_AccessPermissionType  eHsmPermission);


/** @} */ /* module_driver_map */
#if defined(__cplusplus)
}
#endif

#endif

#endif /* _DRIVER_MODULE_DRIVER_MAP_H_ */
