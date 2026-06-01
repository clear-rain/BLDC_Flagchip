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

void MotorDriver_SpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);
void MotorDriver_SpiInit(void);
FCSPI_StatusType TLE92108_SpiSendSync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len);
FCSPI_StatusType MotorDriver_SpiSendAsync(uint8_t *pTxData,uint8_t *pRxData,uint16_t u16Len);
FCSPI_StatusType MotorDriver_RegInitSync(void);
FCSPI_StatusType MotorDriver_RegSendAsyncTask(void);

#endif /* BSW_CDD_MOTORDRIVER_INC_MOTORDRIVER_DRIVER_H_ */
