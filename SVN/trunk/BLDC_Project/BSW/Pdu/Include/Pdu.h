#ifndef Pdu_H_
#define Pdu_H_

#include "Pdu_cfg.h"
#include "BspCan.h"
#include "v_def.h"
#include "com_cfg.h"
#ifndef ECU_ADDRESS_BLDC
#include "AsrNm.h"
#include "uds_tpl.h"
#endif


void PduR_CanIfRxIndication(Bsp_CanRxInit_t * pduInfoPtr);
void PduR_ComTransmit(uint32 PduIndex, uint8 *pduInfoPtr);
#endif
