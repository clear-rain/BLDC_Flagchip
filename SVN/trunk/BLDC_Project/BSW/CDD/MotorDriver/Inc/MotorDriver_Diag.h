/*
 * MotorDriver_Diag.h
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */

#ifndef BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_DIAG_H_
#define BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_DIAG_H_

#include "v_def.h"

typedef union {
    struct {
    	uint8_t no_error            : 1;
        uint8_t motorshort2gnd_error: 1;
        uint8_t motorshort2vcc_error: 1;
        uint8_t motoropenload_error : 1;
        uint8_t SH1_Pull_Up_unknown_error       : 1;
        uint8_t SH1_Pull_Down_unknown_error       : 1;
        uint8_t SH2_Pull_Up_unknown_error       : 1;
        uint8_t SH2_Pull_Down_unknown_error       : 1;
    }bits;
    uint8_t errors;
} MotorDriver_Offline_Diag_error;

typedef union {
    struct {
        uint8_t MotorOpenCircuitFailure : 1;
        uint8_t MotorShortCircuitFailure : 1;
        uint8_t MotorOverCurrentFailure : 1;
        uint8_t MotorDriverChipFailure : 1;
        uint8_t reserved : 4; // Reserved bits to make up 8 bits
    } bits;
    uint8_t byte;
} MotorErrorStatus_t;

typedef union {
    struct {
        uint8_t Charge_Pump_Undervoltage       : 1;
        uint8_t VS_Undervoltage      : 1;
        uint8_t VS_Overvoltage     : 1;
        uint8_t CSO1_Overcurrent : 1;
        uint8_t Thermal_Warning : 1;
        uint8_t Thermal_Shutdown : 1;
        uint8_t DrainSource_Overvoltage : 1;
        uint8_t reserved : 1; // Reserved bit to make up 8 bits
    }bits;
    uint8_t all_flags;
} TLE92104_FaultIndicator_t;


Std_ReturnType MotorDriver_Offline_diag(void);
Std_ReturnType MotorDriver_Online_diag(void);
void MotorDriver_Current_diag(void);
Std_ReturnType MotorDriver_MotorErrorSet(void);

#endif /* BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_DIAG_H_ */
