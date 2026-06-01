/**
 * @file module_driver_mpu.c
 * @author Flagchip054
 * @brief MPU driver source code
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

#include "module_driver_mpu.h"

void MPU_Disable(void)
{
	ARM_MPU_Disable();
}

void MPU_Enable(MPU_EnableOptionType eOption)
{
    uint32_t u32MpuCtr = 0U;

    switch (eOption)
    {
        case MPU_EN_HARDFAULT_NMI:
        	u32MpuCtr = MPU_CTRL_HFNMIENA_Msk;
            break;

        case MPU_EN_PRIVILEGED_DEFAULT:
        	u32MpuCtr = MPU_CTRL_PRIVDEFENA_Msk;
            break;

        case MPU_EN_HFNMI_PRIVDEF:
        	u32MpuCtr = (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk);
            break;

        case MPU_EN_HFNMI_PRIVDEF_NONE:
        	u32MpuCtr = 0U;
            break;

        default:
        	u32MpuCtr = 0U;
            break;
    }
    ARM_MPU_Enable(u32MpuCtr);
}

void MPU_RegionDisable(MPU_RegionNumberType eRegion)
{
	ARM_MPU_ClrRegion((uint32_t)eRegion);
}

MPU_StatusType MPU_RegionInit(const MPU_RegionInitType *pConfig)
{
    MPU_StatusType  eRet   = MPU_STATUS_SUCCESS;
    uint32_t        u32Srd = 0U;
    uint32_t        u32Asr = 0U;

    if (NULL == pConfig)
    {
        eRet = MPU_STATUS_ERROR;
    }
    else
    {
        /* use bit shift is surely safe */
        u32Srd =    (((((uint32_t)pConfig->eSubRegionDis_0) << 0) |
                      (((uint32_t)pConfig->eSubRegionDis_1) << 1) |
                      (((uint32_t)pConfig->eSubRegionDis_2) << 2) |
                      (((uint32_t)pConfig->eSubRegionDis_3) << 3) |
                      (((uint32_t)pConfig->eSubRegionDis_4) << 4) |
                      (((uint32_t)pConfig->eSubRegionDis_5) << 5) |
                      (((uint32_t)pConfig->eSubRegionDis_6) << 6) |
                      (((uint32_t)pConfig->eSubRegionDis_7) << 7)) & 0xFFU);

        u32Asr =    ARM_MPU_RASR(pConfig->eExecuteNever, pConfig->eAccessPermission, pConfig->eTypeExtLevel , pConfig->eShareable,
        		                 pConfig->eCacheable, pConfig->eBufferable, u32Srd, pConfig->eRegionSize );

        ARM_MPU_SetRegionEx((uint32_t)pConfig->eRegion, ARM_MPU_RBAR((uint8_t)pConfig->eRegion, pConfig->u32BaseAddr), u32Asr);
    }

    return eRet;
}
