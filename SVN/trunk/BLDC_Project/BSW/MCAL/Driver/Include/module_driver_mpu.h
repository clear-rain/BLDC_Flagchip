/**
 * @file module_driver_mpu.h
 * @author Flagchip054
 * @brief MPU driver type definition and API
 * @version 2.0.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details The MPU only checks the CPU master access to CTCM and DTCM memory. When access denied, it will cause MemManage Interrupt.
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_MPU_H_
#define _DRIVER_MODULE_DRIVER_MPU_H_

#include "device_header.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup module_driver_mpu
 * @{
 */

/**
 * @brief Status enumeration used by Flagchip MPU Driver
 *
 */
typedef enum {
    MPU_STATUS_SUCCESS = 0, /**< MPU API execute successfully */
    MPU_STATUS_ERROR, /**< Some error occur in MPU API */
} MPU_StatusType;

/**
 * @brief Enable option enumeration for MPU
 *
 */
typedef enum {
    MPU_EN_HFNMI_PRIVDEF_NONE = 0U, /**< disables use of the default memory map. Any memory access to a location not covered by any enabled region causes a fault,
                                         MPU is disabled during hard fault, NMI, and FAULTMASK handlers */
    MPU_EN_HARDFAULT_NMI      = 1, /**< Enables the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
    MPU_EN_PRIVILEGED_DEFAULT = 2, /**< enables use of the default memory map as a background region for privileged software accesses.
                                        When enabled, the background region acts as if it is region number -1.
                                        Any region that is defined and enabled has priority over this default map. */
    MPU_EN_HFNMI_PRIVDEF      = 3, /**< same with MPU_EN_HARDFAULT_NMI | MPU_EN_PRIVILEGED_DEFAULT */
} MPU_EnableOptionType;

/**
 * @brief Enable Status for Sub-region configuration
 *
 */
typedef enum {
    MPU_REGION_SRD_ENABLE_SUBREGION  = 0, /**< sub-region is enabled */
    MPU_REGION_SRD_DISABLE_SUBREGION = 1, /**< sub-region is not enabled */
} MPU_RegionSubDisableType;

/**
 * @brief Configure the code in the region whether can be execute
 *
 */
typedef enum {
    MPU_REGION_XN_EXECUTE_ENABLE  = 0x0,
    MPU_REGION_XN_EXECUTE_DISABLE = 0x1
} MPU_RegionExecuteNeverType;

/**
 * @brief region Shareable configuration
 *
 */
typedef enum {
    MPU_REGION_S_DISABLE = 0,
    MPU_REGION_S_ENABLE  = 1
} MPU_RegionShareableType;

/**
 * @brief Region Cacheable configuration
 *
 */
typedef enum {
    MPU_REGION_C_DISABLE = 0,
    MPU_REGION_C_ENABLE  = 1
} MPU_RegionCacheableType;

/**
 * @brief Region Bufferable configuration
 *
 */
typedef enum {
    MPU_REGION_B_DISABLE = 0,
    MPU_REGION_B_ENABLE  = 1
} MPU_RegionBufferableType;

/**
 * @brief Region Type Extend Level configuration
 *
 */
typedef enum {
    MPU_REGION_TEX_LEVEL_0 = 0,
    MPU_REGION_TEX_LEVEL_1 = 1,
    MPU_REGION_TEX_LEVEL_2 = 2
} MPU_RegionTypeExtLevelType;

/**
 * @brief Region size enumeration for enabling MPU region
 *
 */
typedef enum {
    MPU_REGION_SIZE_32B      = 0x04,
    MPU_REGION_SIZE_64B      = 0x05,
    MPU_REGION_SIZE_128B     = 0x06,
    MPU_REGION_SIZE_256B     = 0x07,
    MPU_REGION_SIZE_512B     = 0x08,
    MPU_REGION_SIZE_1KB      = 0x09,
    MPU_REGION_SIZE_2KB      = 0x0A,
    MPU_REGION_SIZE_4KB      = 0x0B,
    MPU_REGION_SIZE_8KB      = 0x0C,
    MPU_REGION_SIZE_16KB     = 0x0D,
    MPU_REGION_SIZE_32KB     = 0x0E,
    MPU_REGION_SIZE_64KB     = 0x0F,
    MPU_REGION_SIZE_128KB    = 0x10,
    MPU_REGION_SIZE_256KB    = 0x11,
    MPU_REGION_SIZE_512KB    = 0x12,
    MPU_REGION_SIZE_1MB      = 0x13,
    MPU_REGION_SIZE_2MB      = 0x14,
    MPU_REGION_SIZE_4MB      = 0x15,
    MPU_REGION_SIZE_8MB      = 0x16,
    MPU_REGION_SIZE_16MB     = 0x17,
    MPU_REGION_SIZE_32MB     = 0x18,
    MPU_REGION_SIZE_64MB     = 0x19,
    MPU_REGION_SIZE_128MB    = 0x1A,
    MPU_REGION_SIZE_256MB    = 0x1B,
    MPU_REGION_SIZE_512MB    = 0x1C,
    MPU_REGION_SIZE_1GB      = 0x1D,
    MPU_REGION_SIZE_2GB      = 0x1E,
    MPU_REGION_SIZE_4GB      = 0x1F
} MPU_RegionSizeType;

/**
 * @brief MPU Permission Enumeration
 *
 */
typedef enum {
    MPU_REGION_AP_NO_ACCESS     = 0x00,  /**< Any access generates a permission fault */
    MPU_REGION_AP_PRIV_RW       = 0x01,  /**< Privileged access only, unprivileged no access */
    MPU_REGION_AP_PRIV_RW_URO   = 0x02,  /**< Any unprivileged write generates a permission fault */
    MPU_REGION_AP_FULL_ACCESS   = 0x03,  /**< Full access */
    MPU_REGION_AP_PRIV_RO       = 0x05,  /**< Privileged read-only, unprivileged no access */
    MPU_REGION_AP_PRIV_RO_URO   = 0x06   /**< Privileged and unprivileged read-only */
} MPU_RegionAccessPermissionType;

/**
 * @brief MPU Region Enumeration
 *
 */
typedef enum {
    MPU_REGION_NUMBER_0 = 0x0,   /**<  lowest priority */
    MPU_REGION_NUMBER_1 = 0x1,
    MPU_REGION_NUMBER_2 = 0x2,
    MPU_REGION_NUMBER_3 = 0x3,
    MPU_REGION_NUMBER_4 = 0x4,
    MPU_REGION_NUMBER_5 = 0x5,
    MPU_REGION_NUMBER_6 = 0x6,
    MPU_REGION_NUMBER_7 = 0x7    /**< highest priority */
} MPU_RegionNumberType;

/**
 * @brief MPU Region Configuration structure
 *
 */
typedef struct {
    uint32_t                       u32BaseAddr; /**< the start address of region,  the least significant 5 bits should be 0 */
	MPU_RegionNumberType           eRegion; /**< region num */
    MPU_RegionSizeType             eRegionSize; /**< region size */
    MPU_RegionAccessPermissionType eAccessPermission; /**< region access permission */
    MPU_RegionExecuteNeverType     eExecuteNever; /**< region data can be execute or not */
    MPU_RegionTypeExtLevelType     eTypeExtLevel; /**< region type extend level */
    MPU_RegionShareableType        eShareable; /**< region shareable */
    MPU_RegionCacheableType        eCacheable; /**< region cacheable */
    MPU_RegionBufferableType       eBufferable; /**< region bufferable */
    MPU_RegionSubDisableType       eSubRegionDis_0; /**< sub-region 0 disable or not */
    MPU_RegionSubDisableType       eSubRegionDis_1; /**< sub-region 1 disable or not */
    MPU_RegionSubDisableType       eSubRegionDis_2; /**< sub-region 2 disable or not */
    MPU_RegionSubDisableType       eSubRegionDis_3; /**< sub-region 3 disable or not */
    MPU_RegionSubDisableType       eSubRegionDis_4; /**< sub-region 4 disable or not */
    MPU_RegionSubDisableType       eSubRegionDis_5; /**< sub-region 5 disable or not */
    MPU_RegionSubDisableType       eSubRegionDis_6; /**< sub-region 6 disable or not */
    MPU_RegionSubDisableType       eSubRegionDis_7; /**< sub-region 7 disable or not */
} MPU_RegionInitType;

/**
 * @brief Enable the MPU
 *
 * @param eOption Enable Options
 */
void MPU_Enable(MPU_EnableOptionType eOption);

/**
 * @brief Disable MPU
 *
 */
void MPU_Disable(void);

/**
 * @brief Disable region
 *
 * @param eRegion Region index
 * @return MPU_StatusType MPU_STATUS_SUCCESS when disable successfully, others fail
 */
void  MPU_RegionDisable(MPU_RegionNumberType eRegion);

/**
 * @brief Enable region
 *
 * @param pConfig Region Configuration Parameter
 * @return MPU_StatusType MPU_STATUS_SUCCESS when disable successfully, others fail
 */
MPU_StatusType MPU_RegionInit(const MPU_RegionInitType *pConfig);


/** @} */ /* module_driver_mpu */
#if defined(__cplusplus)
}
#endif
#endif /* _DRIVER_MODULE_DRIVER_MPU_H_ */
