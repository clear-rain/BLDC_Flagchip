/**
 * @file motor_current.h
 * @author Flagchip127
 * @brief FC4xxx motor_current
 * @version 1.0.0
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2022 Flagchip Semiconductors Co., Ltd.
 *
 */
/* ********************************************************************************
 *   Revision History:
 *
 *   Version     Date          Initials      CR#          Descriptions
 *   ---------   ----------    ------------  ----------   ---------------
 *   1.0.0       2024-05-20    Flagchip127   N/A          First version for FC4150
 ******************************************************************************** */

#ifndef _MOTOR_MOTOR_LIB_MOTOR_CURRENT_H_
#define _MOTOR_MOTOR_LIB_MOTOR_CURRENT_H_

#include "motor_misc.h"

typedef struct
{
    float ia_offset_raw;
    float ib_offset_raw;
    float ic_offset_raw;
    uint32_t ia_offset_sum;
    uint32_t ib_offset_sum;
    uint32_t ic_offset_sum;
    uint16_t offset_cnt;
    uint16_t offset_cnt_max;
    uint8_t offset_done;
} MotorCurrentOffset;

void Motor_InitCurrentOffset(MotorCurrentOffset *current_offset, uint16_t max_offset_cnt);
void Motor_CalCurrentOffset(MotorCurrentOffset *current_offset, MotorCurrent *current_mea);
uint8_t Motor_IsDoneCalCurrentOffset(MotorCurrentOffset current_offset);

#endif /* _MOTOR_MOTOR_LIB_MOTOR_CURRENT_H_ */
