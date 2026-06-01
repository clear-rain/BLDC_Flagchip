/**
 * @file module_driver_farc.h
 * @author Flagchip054
 * @brief FARC driver type definition and API
 * @version 2.0.0
 * @date 2024-09-11
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip054   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_FARC_H_
#define _DRIVER_MODULE_DRIVER_FARC_H_

#include "HwA_farc.h"

#if FARC_INSTANCE_COUNT > 0u
/**
 * @addtogroup module_driver_farc
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif


/**
 * @brief config the frac hardware
 *
 * @param BaseAddr the physic address for frac config
 * @param Size the size for frac config
 */
void FCFARC_Config(uint32_t BaseAddr, uint32_t Size);

/**
 * @brief Read data according to input offset
 *
 * @param Offset the offset address of the data to read
 * @return return the data
 */
uint8_t FCFARC_Read_Data(uint32_t Offset);

/**
 * @brief Get the logic addr according to input offset
 *
 * @param Offset the offset address to the logic start address
 * @return return the logic address
 */
uint32_t FCFARC_Read_Addr(uint32_t Offset);


#if defined(__cplusplus)
}
#endif

/** @} */

#endif
#endif /* _DRIVER_FC4XXX_DRIVER_FARC_H_ */
