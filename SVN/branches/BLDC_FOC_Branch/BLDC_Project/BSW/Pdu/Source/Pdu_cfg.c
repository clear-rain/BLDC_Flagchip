#include "Pdu_cfg.h"

#ifdef ECU_ADDRESS_PDM_FL
const PduRPduType PduRCfgTable[] =
{
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_150,
	}, /* 0 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_5E2,
	}, /* 1 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_1C2,
	}, /* 2 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_2A0,
	}, /* 3 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_3AE,
	}, /* 4 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_3AF,
	}, /* 5 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_3AA,
	}, /* 6 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = XCP_RX_PDUID,
	}, /* 7 */

	{
			.src = PDUR_CANIF,
			.dest = PDUR_NM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_NM,
	}, /* 8 */
	{
    		.src = PDUR_CANIF,
			.dest = PDUR_DCM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_FUN_Diag,
	}, /* 9 */
	{
    		.src = PDUR_CANIF,
			.dest = PDUR_DCM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PHY_Diag,
	}, /* 10 */
	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_5C3,
	}, /* 11 */
	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_3B6,
	}, /* 12 */	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_3A6,
	}, /* 13 */
	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = XCP_TX_PDUID,
	}, /* 14 */
    {
    		.src = PDUR_NM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_NM,
    }, /* 15 */
	{
    		.src = PDUR_DCM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_Diag,
	}, /* 16 */

};

#endif


#ifdef ECU_ADDRESS_PDM_FR
const PduRPduType PduRCfgTable[] =
{
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_151,
	}, /* 0 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_5E2,
	}, /* 1 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_1C2,
	}, /* 2 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_2A1,
	}, /* 3 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_3AE,
	}, /* 4 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_3AF,
	}, /* 5 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_3AB,
	}, /* 6 */
	{
			.src = PDUR_CANIF,
			.dest = PDUR_COM,
			.dir = PDUR_PDU_RX,
			.PduId = XCP_RX_PDUID,
	}, /* 7 */

	{
			.src = PDUR_CANIF,
			.dest = PDUR_NM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PDUID_NM,
	}, /* 8 */
	{
    		.src = PDUR_CANIF,
			.dest = PDUR_DCM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_FUN_Diag,
	}, /* 9 */
	{
    		.src = PDUR_CANIF,
			.dest = PDUR_DCM,
			.dir = PDUR_PDU_RX,
			.PduId = COM_RX_PHY_Diag,
	}, /* 10 */
	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_5CB,
	}, /* 11 */
	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_3B7,
	}, /* 12 */	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_3A7,
	}, /* 13 */
	{
			.src = PDUR_COM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = XCP_TX_PDUID,
	}, /* 14 */
    {
    		.src = PDUR_NM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_PDUID_NM,
    }, /* 15 */
	{
    		.src = PDUR_DCM,
			.dest = PDUR_CANIF,
			.dir = PDUR_PDU_TX,
			.PduId = COM_TX_Diag,
	}, /* 16 */

};

#endif




