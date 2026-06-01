/**
 * @file motor_current.c
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

#include "motor_current.h"

void Motor_InitCurrentOffset(MotorCurrentOffset *current_offset, uint16_t max_offset_cnt)
{
    current_offset->ia_offset_raw = 0;
    current_offset->ib_offset_raw = 0;
    current_offset->ic_offset_raw = 0;
    current_offset->ia_offset_sum = 0;
    current_offset->ib_offset_sum = 0;
    current_offset->ic_offset_sum = 0;

    current_offset->offset_cnt = 0;
    current_offset->offset_cnt_max = max_offset_cnt;

    current_offset->offset_done = 0;
}

void Motor_CalCurrentOffset(MotorCurrentOffset *current_offset, MotorCurrent *current_mea)
{
    current_offset->ia_offset_sum += current_mea->ia;
    current_offset->ib_offset_sum += current_mea->ib;
    current_offset->ic_offset_sum += current_mea->ic;

    current_offset->offset_cnt += 1;

    if (current_offset->offset_cnt >= current_offset->offset_cnt_max)
    {
        current_offset->ia_offset_raw = current_offset->ia_offset_sum / current_offset->offset_cnt;
        current_offset->ib_offset_raw = current_offset->ib_offset_sum / current_offset->offset_cnt;
        current_offset->ic_offset_raw = current_offset->ic_offset_sum / current_offset->offset_cnt;

        current_offset->offset_done = 1;
    }
}

uint8_t Motor_IsDoneCalCurrentOffset(MotorCurrentOffset current_offset) { return current_offset.offset_done; }
