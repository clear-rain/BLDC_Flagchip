/**
 * @file module_driver_farc.c
 * @author Flagchip054
 * @brief FARC driver source code
 * @version 2.0.0
 * @date 2024-09-11
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

#include "module_driver_farc.h"

#if FARC_INSTANCE_COUNT > 0u

/**
 * @brief config the frac hardware
 * @param BaseAddr the physic address for frac config
 * @param Size the size for frac config
 */
void FCFARC_Config(uint32_t BaseAddr, uint32_t Size)
{
    FARC_HWA_SetLRS(Size);
    FARC_HWA_SetPRBA(BaseAddr);
}

/**
 * @brief Read data according to input offset
 * @param Offset the offset address of the data to read
 */
uint8_t FCFARC_Read_Data(uint32_t Offset)
{
    return *(uint8_t *)(FARC_HWA_GetLRBA() + Offset);
}

/**
 * @brief Get the logic addr according to input offset
 * @param Offset the offset address to the logic start address
 * @return return the logic address
 */
uint32_t FCFARC_Read_Addr(uint32_t Offset)
{
    return (FARC_HWA_GetLRBA() + Offset);
}
#endif
