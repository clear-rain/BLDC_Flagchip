#ifndef Pdu_cfg_H_
#define Pdu_cfg_H_

#include "com_cfg.h"

#define PDUR_PDU_RX 0
#define PDUR_PDU_TX 1

#define PDUR_COM   0
#define PDUR_NM    1
#define PDUR_CANIF 2
#define PDUR_DCM   3
#ifdef ECU_ADDRESS_PDM_FL
//RX
#define PDU_Index_150    0
#define PDU_Index_5E2    1
#define PDU_Index_1C2    2
#define PDU_Index_2A0    3
#define PDU_Index_3AE    4
#define PDU_Index_3AF    5
#define PDU_Index_3AA    6
#define PDU_Index_RxXcp  7
#define PDU_Index_RxNM   8
#define PDU_Index_7DF    9
#define PDU_Index_771    10
//TX
#define PDU_Index_5C3    11
#define PDU_Index_3B6    12
#define PDU_Index_3A6    13
#define PDU_Index_TxXcp  14
#define PDU_Index_TxNM   15
#define PDU_Index_779    14

#endif



#ifdef ECU_ADDRESS_PDM_FR

//RX
#define PDU_Index_151    0
#define PDU_Index_5E2    1
#define PDU_Index_1C2    2
#define PDU_Index_2A1    3
#define PDU_Index_3AE    4
#define PDU_Index_3AF    5
#define PDU_Index_3AB    6
#define PDU_Index_RxXcp  7
#define PDU_Index_RxNM   8
#define PDU_Index_7DF    9
#define PDU_Index_770    10
//TX
#define PDU_Index_5CB    11
#define PDU_Index_3B7    12
#define PDU_Index_3A7    13
#define PDU_Index_TxXcp  14
#define PDU_Index_TxNM   15
#define PDU_Index_778    14
#endif


typedef struct {
    uint8 src;
    uint8 dest;
    uint8 dir;
    uint16 PduId;
} PduRPduType;

extern const PduRPduType PduRCfgTable[];
#endif
