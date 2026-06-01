/*
 * MotorDriver_Driver.h
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */

#ifndef BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_DRIVER_H_
#define BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_DRIVER_H_

#include "MotorDriver_Type.h"
#include "MotorDriver_Cfg.h"


#define SET_TLE9210X_SPI_FRAME(message, data_val, OP_val, addr_val, labt_val, msb_val) \
    message.data = data_val; \
    message.OP = OP_val; \
    message.address = addr_val; \
    message.labt = labt_val; \
    message.msb = msb_val;

FCSPI_StatusType TLE9210x_RegInitSync(void);
FCSPI_StatusType TLE9210x_RegSendAsyncTask(void);

extern uint32 g_au32MotorDriverSpiSendTaskTxData[TLE92104_Usual_Use_CTRL_Registers_Count];
extern uint32 g_au32MotorDriverSpiSendTaskRxData[TLE92104_Usual_Use_CTRL_Registers_Count];

uint8_t get_bit_from_rx_data(uint8_t m, uint8_t n);
uint32 TLE9210X_SPI_Frame_To_Uint32(TLE9210X_SPI_Frame frame);
FCSPI_StatusType TLE9210x_RegInitSync(void);
FCSPI_StatusType TLE9210x_RegSendAsyncTask(void);

#endif /* BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_DRIVER_H_ */
