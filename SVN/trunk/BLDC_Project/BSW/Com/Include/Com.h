#ifndef COM_H_
#define COM_H_

#include "BspCan.h"
#include "com_cfg.h"
#include "v_def.h"
#include <string.h>


#define COM_SIG_INTEL     1
#define COM_SIG_MOTOROLA  0 /* Motorola Msb */
#define COM_PDU_RECEIVE   0
#define COM_PDU_TRANSMIT  1

typedef struct{
	uint16_t Angle;
	uint8_t Angle_CRC;
	uint8_t RollingCounter:4;
	uint8_t AngleValid:1;
	uint8_t Fault1:1;
	uint8_t Fault2:1;
	uint8_t Fault3:1;
}Recv_DataBuf_T;


void Com_Init(void);
boolean Com_InvalidPduSignals(uint16 pduId);
void Com_MainFunction(void);
void Com_RxIndication(uint16 pduId,uint8 *PduInfoPtr, uint8 immediate);
void Com_lRxHdl(void);
void Com_lTxHdl(void);
void Com_TxNM(void);
void Com_lProcessReceiveSignals(uint8 pduId);
void AnalysisReceiveSignals(uint32 FrameId , uint8 index , uint8* BufferPtr);

uint16_t Com_GetMTEncoderAngleData(void);

#ifdef ECU_ADDRESS_BLDC
void Com_Task_BLDCTest(void);

#endif /*ECU_ADDRESS_BLDC*/

//extern boolean txRdy[CANTX_NUM];
#endif
