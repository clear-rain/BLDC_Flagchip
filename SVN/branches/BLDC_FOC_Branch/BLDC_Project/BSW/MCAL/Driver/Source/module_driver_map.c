/**
 * @file module_driver_map.c
 * @author Flagchip054
 * @brief MAP driver source code
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

#include "module_driver_map.h"

#if MAP_INSTANCE_COUNT > 0U

FCMAP_StatusType FCMAP_GetErrorInformation(FCMAP_ErrorInfoType *pInf)
{
    uint32_t         u32CSR  = 0U;
    uint32_t         u32FIR  = 0U;
    uint32_t         u32EC   = 0U;
    FCMAP_StatusType eStatus = FCMAP_STATUS_SUCCESS;

    if (NULL == pInf)
    {
        eStatus = FCMAP_STATUS_PARAM_ERROR;
    }
    else
    {
        u32CSR = MAP_HWA_Get_CSR();
        u32FIR = MAP_HWA_Get_FIR();
        u32EC  = u32FIR & MAP_FIR_EC_MASK;

        if ((0U == (u32CSR & MAP_CSR_GE_MASK)) || /* MAP is disabled. All accesses form all bus masters are allowed */
            (0U == (u32CSR & MAP_CSR_ERRP1_MASK))) /* no error occur */
        {
            eStatus = FCMAP_STATUS_SUCCESS;
        }
        else
        {
            pInf->eRdErrCond = FCMAP_EC_ERR_NONE;
            pInf->u32FaultAddress  = MAP_HWA_Get_FAR();
            if (0U == u32EC)
            {
                pInf->eRdErrCond  = FCMAP_EC_ERR_ADDRESS_NOT_CONFIGURED;
            }
            else if (0U == (u32EC & (u32EC - 1U)))
            {
                pInf->eRdErrCond  = FCMAP_EC_ERR_ONE_REGION_VIOLATION;
            }
            else
            {
                pInf->eRdErrCond  = FCMAP_EC_ERR_OVERLAPPED_REGION_VIOLATION;
            }

            pInf->eAddressFrom    = (FCMAP_MasterType)((uint32_t)((u32FIR & MAP_FIR_EMID_MASK) >> MAP_FIR_EMID_SHIFT));
            pInf->eErrorAttr      = (FCMAP_ErrAttrType)((uint32_t)((u32FIR & MAP_FIR_EATT_MASK) >> MAP_FIR_EATT_SHIFT));
            pInf->eErrorOperation = (FCMAP_ErrOperationType)((uint32_t)((u32FIR & MAP_FIR_ET_MASK) >> MAP_FIR_ET_SHIFT));

            MAP_HWA_Set_CSR(u32CSR | MAP_CSR_ERRP1(1)); /* clear error bit */

            eStatus = FCMAP_STATUS_ACCESS_DENIED;
        }
    }

    return eStatus;
}

boolean FCMAP_CheckEnable(void)
{
  return (0U != (MAP_HWA_Get_CSR() & MAP_CSR_GE_MASK)) ? TRUE : FALSE;
}

boolean FCMAP_CheckRegionEnable(FCMAP_RegionIdType eRegion)
{
    boolean bRet = TRUE;

    switch (eRegion)
    {
        case FCMAP_REGION_0:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(0U) & MAP_EN_RD0_EN_MASK)) ? TRUE : FALSE;
            break;

        case FCMAP_REGION_1:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(1U) & MAP_EN_RD_EN_MASK)) ? TRUE : FALSE;
            break;

        case FCMAP_REGION_2:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(2U) & MAP_EN_RD_EN_MASK)) ? TRUE : FALSE;
            break;

        case FCMAP_REGION_3:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(3U) & MAP_EN_RD_EN_MASK)) ? TRUE : FALSE;
            break;

        case FCMAP_REGION_4:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(4U) & MAP_EN_RD_EN_MASK)) ? TRUE : FALSE;
            break;

        case FCMAP_REGION_5:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(5U) & MAP_EN_RD_EN_MASK)) ? TRUE : FALSE;
            break;

        case FCMAP_REGION_6:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(6U) & MAP_EN_RD_EN_MASK)) ? TRUE : FALSE;
            break;

        case FCMAP_REGION_7:
            bRet = (0U != (MAP_HWA_Get_EN_RDn(7U) & MAP_EN_RD_EN_MASK)) ? TRUE : FALSE;
            break;

        default:
            bRet = FALSE;
            break;
    }

    return bRet;
}
void FCMAP_Enable(void)
{
    if (!FCMAP_CheckEnable())
    {
        MAP_HWA_Set_CSR(MAP_CSR_ERRP1(1) | MAP_CSR_GE(1));
    }
}

void FCMAP_Disable(void)
{
    MAP_HWA_Set_CSR(0U);
}

/* when MAP and REGION all enabled, the region can't be re-enabled */
FCMAP_StatusType FCMAP_RegionEnable(const FCMAP_RegionConfigurationType *pConf)
{
    FCMAP_StatusType eRet = FCMAP_STATUS_SUCCESS;
    uint32_t u32Temp = 0;

    if (NULL == pConf)    {
        eRet = FCMAP_STATUS_PARAM_ERROR;
    }
    else if (!FCMAP_CheckEnable())
    {
        eRet = FCMAP_STATUS_ERROR;
    }
    else if (FCMAP_CheckRegionEnable(pConf->eRegion))
    {
        eRet = FCMAP_STATUS_REENABLED;
    }
    else
    {
        switch (pConf->eRegion)
        {
            case FCMAP_REGION_0:
                eRet = FCMAP_STATUS_ERROR; /* not allow enable, once rd0 is closed, it can not be enabled again */
                break;

            case FCMAP_REGION_1:
            case FCMAP_REGION_2:
            case FCMAP_REGION_3:
            case FCMAP_REGION_4:
            case FCMAP_REGION_5:
            case FCMAP_REGION_6:
            case FCMAP_REGION_7:
                MAP_HWA_Set_STA_RDn((uint8_t)(pConf->eRegion), pConf->u32AddrStart);
                MAP_HWA_Set_ENA_RDn((uint8_t)(pConf->eRegion), pConf->u32AddrEnd);
                u32Temp = (FCMAP_DRV_RD_HSM_PERMISSION(pConf->eHsmPermission)   |
                #if (FCMAP_EMID_ENET_SUPPORT == STD_ON)
                  FCMAP_DRV_RD_ENET_PERMISSION(pConf->eEnetPermission) | FCMAP_DRV_RD_DMA_PERMISSION(pConf->eDmaPermission));
                #else
                  FCMAP_DRV_RD_DMA_PERMISSION(pConf->eDmaPermission));
                #endif
                MAP_HWA_Set_MAC_RDn((uint8_t)(pConf->eRegion), u32Temp);
                MAP_HWA_Set_EN_RDn((uint8_t)(pConf->eRegion),  MAP_EN_RD_EN(1));
                break;

            default:
                eRet = FCMAP_STATUS_PARAM_ERROR;
                break;
        }
    }


    return eRet;
}

FCMAP_StatusType FCMAP_GetRegionConfiguration(FCMAP_RegionIdType eRegion, FCMAP_RegionConfigurationType *pConf)
{
    uint32_t         u32RegVal = 0U;
    FCMAP_StatusType eRet      = FCMAP_STATUS_SUCCESS;

    if (NULL == pConf)
    {
        eRet = FCMAP_STATUS_PARAM_ERROR;
    }
    else if(eRegion <= FCMAP_REGION_7)
    {
    	pConf->eRegion         = eRegion;
        pConf->u32AddrStart    = MAP_HWA_Get_STA_RDn((uint8_t)eRegion);
        pConf->u32AddrEnd      = MAP_HWA_Get_ENA_RDn((uint8_t)eRegion);
        u32RegVal              = MAP_HWA_Get_MAC_RDn((uint8_t)eRegion);
        if(eRegion == FCMAP_REGION_0)
        {
            pConf->eHsmPermission  = FCMAP_DRV_RD0_GET_HSM_PERMISSION(u32RegVal);
            pConf->eEnetPermission = FCMAP_DRV_RD0_GET_ENET_PERMISSION(u32RegVal);
            pConf->eDmaPermission  = FCMAP_DRV_RD0_GET_DMA_PERMISSION(u32RegVal);
        }
        else
        {
            pConf->eHsmPermission  = FCMAP_DRV_RD_GET_HSM_PERMISSION(u32RegVal);
            pConf->eEnetPermission = FCMAP_DRV_RD_GET_ENET_PERMISSION(u32RegVal);
            pConf->eDmaPermission  = FCMAP_DRV_RD_GET_DMA_PERMISSION(u32RegVal);
        }
    }
    else
    {
        eRet = FCMAP_STATUS_PARAM_ERROR;
    }
    return eRet;
}

FCMAP_StatusType FCMAP_RegionDisable(FCMAP_RegionIdType eRegion)
{
    FCMAP_StatusType eRet = FCMAP_STATUS_SUCCESS;

    switch (eRegion)
    {
        case FCMAP_REGION_0:
            MAP->MAC_RD0 = MAP_MAC_RD0_BM4AE(3)   |
                           MAP_MAC_RD0_BM3AE(0xf) |
                           MAP_MAC_RD0_BM2AE(0xf);
            /* can't disable directly, write MAC reg will disable it, and RD0 can't be enable */
            break;
        case FCMAP_REGION_1:
        case FCMAP_REGION_2:
        case FCMAP_REGION_3:
        case FCMAP_REGION_4:
        case FCMAP_REGION_5:
        case FCMAP_REGION_6:
        case FCMAP_REGION_7:
            MAP_HWA_Set_EN_RDn((uint8_t)eRegion, MAP_EN_RD_EN(0));
            break;
        default:
            eRet = FCMAP_STATUS_PARAM_ERROR;
            break;
    }

    return eRet;
}

/* FCMAP_UpdateRegionPermission only work when MAP and REGION all enabled */
FCMAP_StatusType FCMAP_UpdateRegionPermission(FCMAP_RegionIdType eRegion,
    FCMAP_AccessPermissionType  eDmaPermission,
    FCMAP_AccessPermissionType  eEnetPermission,
    FCMAP_AccessPermissionType  eHsmPermission)
{
    FCMAP_StatusType eRet = FCMAP_STATUS_SUCCESS;

    if (!FCMAP_CheckEnable())
    {
        eRet = FCMAP_STATUS_ERROR;
    }
    else if (!FCMAP_CheckRegionEnable(eRegion))
    {
        eRet = FCMAP_STATUS_ERROR;
    }
    else
    {
        switch (eRegion)
        {
            case FCMAP_REGION_0:
                MAP_HWA_Set_ACU_RDn(0U,  FCMAP_DRV_ACUR0_HSM_PERMISSION(eHsmPermission)  |
                                        FCMAP_DRV_ACUR0_ENET_PERMISSION(eEnetPermission)|
                                        FCMAP_DRV_ACUR0_DMA_PERMISSION(eDmaPermission));
                break;
            case FCMAP_REGION_1:
            case FCMAP_REGION_2:
            case FCMAP_REGION_3:
            case FCMAP_REGION_4:
            case FCMAP_REGION_5:
            case FCMAP_REGION_6:
            case FCMAP_REGION_7:
                MAP_HWA_Set_ACU_RDn((uint8_t)eRegion,  FCMAP_DRV_ACUR_HSM_PERMISSION(eHsmPermission)   |
                                                       FCMAP_DRV_ACUR_ENET_PERMISSION(eEnetPermission) |
                                                       FCMAP_DRV_ACUR_DMA_PERMISSION(eDmaPermission));
                break;

            default:
                eRet = FCMAP_STATUS_PARAM_ERROR;
                break;
        }
    }

    return eRet;
}

#endif

