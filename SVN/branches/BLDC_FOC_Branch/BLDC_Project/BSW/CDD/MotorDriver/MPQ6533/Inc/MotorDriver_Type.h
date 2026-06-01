/*
 * MotorDriver_Type.h
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */

#ifndef BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_TYPE_H_
#define BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_TYPE_H_


#include "main.h"
#include "BspSpi.h"

#define MSB_Bit                                 0x01
#define LABT_Bit                                0x01
#define OP_Read_And_WriteOrClear_Bit            0x01
#define OP_Read_Only_Bit                        0x00
#define E_NOK                                   0x01U


typedef struct {
    uint16 data    : 16; // Bits 0-15: Data
    uint8 OP  : 1;  // Bit 16: Control bit
    uint8 address  : 5;  // Bits 17-21: Address
    uint8 labt     : 1;  // Bit 22: LABT
    uint8 msb      : 1;  // Bit 23: MSB
} TLE9210X_SPI_Frame;

#endif /* BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_TYPE_H_ */
