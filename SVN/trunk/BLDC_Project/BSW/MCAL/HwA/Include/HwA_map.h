/**
 * @file HwA_map.h
 * @author Flagchip054
 * @brief  MAP hardware access layer
 * @version 2.0.0
 * @date 2024-04-13
 * 
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 * 
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/

#ifndef _HWA_MAP_H_
#define _HWA_MAP_H_
#include "device_header.h"

#if MAP_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_map HwA_map
 * @ingroup module_driver_map
 * @{
 */

/********* Local typedef ************/
#define FCMAP_DRV_RD0_HSM_PERMISSION(regVal)  (MAP_MAC_RD0_BM4AE((uint32_t)(regVal)))
#define FCMAP_DRV_RD0_ENET_PERMISSION(regVal) (MAP_MAC_RD0_BM3AE(((uint32_t)0xC) | ((uint32_t)(regVal))))
#define FCMAP_DRV_RD0_DMA_PERMISSION(regVal)  (MAP_MAC_RD0_BM2AE(((uint32_t)0xC) | ((uint32_t)(regVal))))

#define FCMAP_DRV_RD_HSM_PERMISSION(regVal)   (MAP_MAC_RD_BM4AE((uint32_t)(regVal)))
#define FCMAP_DRV_RD_ENET_PERMISSION(regVal)  (MAP_MAC_RD_BM3AE(((uint32_t)0xC) | ((uint32_t)(regVal))))
#define FCMAP_DRV_RD_DMA_PERMISSION(regVal)   (MAP_MAC_RD_BM2AE(((uint32_t)0xC) | ((uint32_t)(regVal))))

#define FCMAP_DRV_RD0_GET_HSM_PERMISSION(regVal)   \
    ((FCMAP_AccessPermissionType)((uint32_t)((((uint32_t)(regVal)) & MAP_MAC_RD0_BM4AE_MASK) >> MAP_MAC_RD0_BM4AE_SHIFT)))

#define FCMAP_DRV_RD0_GET_ENET_PERMISSION(regVal)  \
    ((FCMAP_AccessPermissionType)((uint32_t)(((((uint32_t)(regVal)) & MAP_MAC_RD0_BM3AE_MASK) >> MAP_MAC_RD0_BM3AE_SHIFT) & ((uint32_t)0x3))))

#define FCMAP_DRV_RD0_GET_DMA_PERMISSION(regVal)   \
    ((FCMAP_AccessPermissionType)((uint32_t)(((((uint32_t)(regVal)) & MAP_MAC_RD0_BM2AE_MASK) >> MAP_MAC_RD0_BM2AE_SHIFT) & ((uint32_t)0x3))))

#define FCMAP_DRV_RD_GET_HSM_PERMISSION(regVal)    \
    ((FCMAP_AccessPermissionType)((uint32_t)((((uint32_t)(regVal)) & MAP_MAC_RD_BM4AE_MASK) >> MAP_MAC_RD_BM4AE_SHIFT)))

#define FCMAP_DRV_RD_GET_ENET_PERMISSION(regVal)   \
    ((FCMAP_AccessPermissionType)((uint32_t)(((((uint32_t)(regVal)) & MAP_MAC_RD_BM3AE_MASK) >> MAP_MAC_RD_BM3AE_SHIFT) & ((uint32_t)0x3))))

#define FCMAP_DRV_RD_GET_DMA_PERMISSION(regVal)    \
    ((FCMAP_AccessPermissionType)((uint32_t)(((((uint32_t)(regVal)) & MAP_MAC_RD_BM2AE_MASK) >> MAP_MAC_RD_BM2AE_SHIFT) & ((uint32_t)0x3))))


#define FCMAP_DRV_ACUR0_HSM_PERMISSION(regVal)  (MAP_ACUR0_BM4AE((uint32_t)(regVal)))
#define FCMAP_DRV_ACUR0_ENET_PERMISSION(regVal) (MAP_ACUR0_BM3AE(((uint32_t)0xC) | ((uint32_t)(regVal))))
#define FCMAP_DRV_ACUR0_DMA_PERMISSION(regVal)  (MAP_ACUR0_BM2AE(((uint32_t)0xC) | ((uint32_t)(regVal))))

#define FCMAP_DRV_ACUR_HSM_PERMISSION(regVal)   (MAP_ACUR_BM4AE((uint32_t)(regVal)))
#define FCMAP_DRV_ACUR_ENET_PERMISSION(regVal)  (MAP_ACUR_BM3AE(((uint32_t)0xC) | ((uint32_t)(regVal))))
#define FCMAP_DRV_ACUR_DMA_PERMISSION(regVal)   (MAP_ACUR_BM2AE(((uint32_t)0xC) | ((uint32_t)(regVal))))


/**
 * @brief Status enumeration used by Flagchip MAP Driver
 *
 */
typedef enum {
    FCMAP_STATUS_SUCCESS       = 0, /**< FCMap API execute successfully */
    FCMAP_STATUS_ACCESS_DENIED = 1, /**< When the non-CPU master(DMA/ENET/HSM) access fail, get error information, will return this value */
    FCMAP_STATUS_PARAM_ERROR   = 2, /**< FCMap API param error */
    FCMAP_STATUS_ERROR         = 3, /**< Some error occur in FCMap API */
    FCMAP_STATUS_REENABLED     = 4, /**< The region is re-enabled */
} FCMAP_StatusType;

/**
 * @brief Region ID
 *
 */
typedef enum {
    FCMAP_REGION_0 = 0, /**< Region 0 is enabled when MAP start to work, address range fixed to 0-0xffffffff, no protection. Once it closed, can't be re-enable */
    FCMAP_REGION_1 = 1, /**< Region 1, driver user can configure range, permission, disable and enable. But be careful of the region 0 */
    FCMAP_REGION_2 = 2, /**< Region 2, driver user can configure range, permission, disable and enable. But be careful of the region 0 */
    FCMAP_REGION_3 = 3, /**< Region 3, driver user can configure range, permission, disable and enable. But be careful of the region 0 */
    FCMAP_REGION_4 = 4, /**< Region 4, driver user can configure range, permission, disable and enable. But be careful of the region 0 */
    FCMAP_REGION_5 = 5, /**< Region 5, driver user can configure range, permission, disable and enable. But be careful of the region 0 */
    FCMAP_REGION_6 = 6, /**< Region 6, driver user can configure range, permission, disable and enable. But be careful of the region 0 */
    FCMAP_REGION_7 = 7  /**< Region 7, driver user can configure range, permission, disable and enable. But be careful of the region 0 */
} FCMAP_RegionIdType;

/**
 * @brief Error condition
 *
 */
typedef enum {
    FCMAP_EC_ERR_NONE                        = 0, /**< no region access error */
    FCMAP_EC_ERR_ADDRESS_NOT_CONFIGURED      = 1, /**< an access did not hit in any region */
    FCMAP_EC_ERR_ONE_REGION_VIOLATION        = 2, /**< the error is caused by one of regions */
    FCMAP_EC_ERR_OVERLAPPED_REGION_VIOLATION = 3, /**<  the error is caused by an overlapping set of region descriptors */
} FCMAP_ErrorConditionType;


/**
 * @brief  The non-CPU master accessing to CTCM/DTCM memory
 *
 */
typedef enum {
    /*
     * FCMAP_MASTER_NONE = 0,
     * FCMAP_MASTER_CM4  = 1,
     * not use by map, MPU instead
     */
    FCMAP_EMID_DMA  = 2, /**< DMA access the memory */
    FCMAP_EMID_ENET = 3, /**< ENET access the memory */
    FCMAP_EMID_HSM  = 4, /**< HSM access the memory */
} FCMAP_MasterType;

/**
 * @brief Access Error Attribute-User/Supervisor Data/Instrunction Access
 *
 */
typedef enum {
    FCMAP_EATT_USER_CODE       = 0, /**< user mode, instruction access */
    FCMAP_EATT_USER_DATA       = 1, /**< user mode, data access */
    FCMAP_EATT_SUPERVISOR_CODE = 2, /**< supervisor mode, instruction access */
    FCMAP_EATT_SUPERVISOR_DATA = 3, /**< supervisor mode, data access */
} FCMAP_ErrAttrType;

/**
 * @brief Error operation
 *
 */
typedef enum {
    FCMAP_ET_READ  = 0, /**< read operation cause the error */
    FCMAP_ET_WRITE = 1, /**< write operation cause the error */
} FCMAP_ErrOperationType;

/**
 * @brief All Access Error Information
 *
 */
typedef struct {
    uint32_t                  u32FaultAddress;  /**< indicates the address value on slave port1 of AXBS that an error response is generated */
    FCMAP_ErrorConditionType  eRdErrCond;      /**< error condition */
    FCMAP_MasterType          eAddressFrom;    /**< error master identifier */
    FCMAP_ErrAttrType         eErrorAttr;      /**< error attributes */
    FCMAP_ErrOperationType    eErrorOperation; /**< error type */
} FCMAP_ErrorInfoType;

/**
 * @brief Permission enumeration used to configure
 *
 */
typedef enum {
    FCMAP_PERMISSION_RW_FORBIDDEN = 0, /**< read and write forbidden */
    FCMAP_PERMISSION_WRITE_ONLY   = 1, /**< write only, read forbidden */
    FCMAP_PERMISSION_READ_ONLY    = 2, /**< read only, write forbidden */
    FCMAP_PERMISSION_READ_WRITE   = 3, /**< read and write all allowed */
} FCMAP_AccessPermissionType;

/**
 * @brief Structure to configure the address and permission
 *
 */
typedef struct {
    uint32_t                     u32AddrStart; /**< the start address to configure */
    uint32_t                     u32AddrEnd;   /**< the end address to configure */
    FCMAP_RegionIdType           eRegion;
    FCMAP_AccessPermissionType   eDmaPermission; /**< the DMA permission to configure */
    FCMAP_AccessPermissionType   eEnetPermission; /**< the Enet permission to configure */
    FCMAP_AccessPermissionType   eHsmPermission; /**< the Hsm permission to configure */
} FCMAP_RegionConfigurationType;


/**
 * @brief get mpu control and status register
 * 
 * @return csr value
 */
LOCAL_INLINE uint32_t  MAP_HWA_Get_CSR(void)
{
   return MAP->CSR;
}

/**
 * @brief get mpu fault address  register
 * 
 * @return far value 
 */
LOCAL_INLINE uint32_t  MAP_HWA_Get_FAR(void)
{
   return MAP->FAR;
}

/**
 * @brief get mpu fault information register
 * 
 * @return fir value 
 */
LOCAL_INLINE uint32_t  MAP_HWA_Get_FIR(void)
{
   return MAP->FIR;
}


/**
 * @brief set mpu control and status register
 * 
 * @param u32RegValue  value write to csr
 */
LOCAL_INLINE void  MAP_HWA_Set_CSR(uint32_t u32RegValue)
{
   MAP->CSR = u32RegValue;
}

/**
 * @brief set mpu fault information register
 * 
 * @param u32RegValue  value write to fir
 */
LOCAL_INLINE void  MAP_HWA_Set_FIR(uint32_t u32RegValue)
{
   MAP->FIR = u32RegValue;
}

/**
 * @brief set mpu enable register 1~7
 * 
 * @param idx   index (1~7)
 * @param u32RegValue  enable value
 */
LOCAL_INLINE void MAP_HWA_Set_EN_RDn(uint8_t idx, uint32_t u32RegValue)
{
   *((volatile uint32_t*)(&(MAP->EN_RD1) + (int32_t)idx*4 - 4)) |= u32RegValue;
}


/**
 * @brief get mpu enable register 
 * 
 * @param idx   index (0~7) 
 * @return  enable register 0~7 value
 */
LOCAL_INLINE uint32_t MAP_HWA_Get_EN_RDn(uint8_t idx)
{
   uint32_t u32RegValue;
   if(idx == 0U)
   {
      u32RegValue = (MAP->EN_RD0);
   }
   else
   {
      u32RegValue = *((volatile uint32_t*)(&(MAP->EN_RD1) + (int32_t)idx*4 - 4));
   }
   return u32RegValue;
}

/**
 * @brief  set mpu start address register 1~7
 * 
 * @param idx   index (1~7)
 * @param u32RegValue  start address value 
 */
LOCAL_INLINE void MAP_HWA_Set_STA_RDn(uint8_t idx, uint32_t u32RegValue)
{
    *((volatile uint32_t*)(&(MAP->STA_RD1) + (int32_t)idx*4 - 4)) = u32RegValue;
}

/**
 * @brief get mpu start address register 0~7
 * 
 * @param idx  index (0~7)
 * @return start address value 
 */
LOCAL_INLINE uint32_t MAP_HWA_Get_STA_RDn(uint8_t idx)
{
   uint32_t u32RegValue;
   if(idx == 0U)
   {
      u32RegValue = (MAP->STA_RD0);
   }
   else
   {
      u32RegValue = *((volatile uint32_t*)(&(MAP->STA_RD1) + (int32_t)idx*4 - 4));
   }
   return u32RegValue;
}

/**
 * @brief  set mpu end address register 1~7
 * 
 * @param idx  index (1~7)
 * @param u32RegValue  end address value 
 */
LOCAL_INLINE void MAP_HWA_Set_ENA_RDn(uint8_t idx, uint32_t u32RegValue)
{
    *((volatile uint32_t*)(&(MAP->ENA_RD1) + (int32_t)idx*4 - 4)) = u32RegValue;
}

/**
 * @brief  get mpu end address register 0~7
 * 
 * @return  end address value 
 */
LOCAL_INLINE uint32_t MAP_HWA_Get_ENA_RDn(uint8_t idx)
{
   uint32_t u32RegValue;
   if(idx == 0U)
   {
      u32RegValue = (MAP->ENA_RD0);
   }
   else
   {
      u32RegValue = *((volatile uint32_t*)(&(MAP->ENA_RD1) + (int32_t)idx*4 - 4));
   }
   return u32RegValue;
}

/**
 * @brief  set mpu access control register
 * 
 * @param idx  index (0~7)
 * @param u32RegValue  access control value
 */
LOCAL_INLINE void MAP_HWA_Set_MAC_RDn(uint8_t idx, uint32_t u32RegValue)
{
    *((volatile uint32_t*)(&(MAP->MAC_RD0) + (int32_t)idx*4)) = u32RegValue;
}

/**
 * @brief  get mpu access control register
 * 
 * @param idx   index (0~7)
 * @return  access control value 
 */
LOCAL_INLINE uint32_t MAP_HWA_Get_MAC_RDn(uint8_t idx)
{
	return *((volatile uint32_t*)(&(MAP->MAC_RD0) + (int32_t)idx*4));
}

/**
 * @brief  set mpu access control update register
 * 
 * @param idx  index (0~7)
 * @param u32RegValue  access control update value
 */
LOCAL_INLINE void MAP_HWA_Set_ACU_RDn(uint8_t idx, uint32_t u32RegValue)
{
	if(idx == 0U)
	{
		MAP->ACUR0 = u32RegValue;
	}
	else
	{
		MAP->ACUR[idx-1U] = u32RegValue;
	}
}

/** @}*/

#endif

#endif /* HWA_INCLUDE_HWA_MAP_H_ */
