/*
 * CompatibleInfo.c
 *
 *  Created on: 2025年7月23日
 *      Author: jiang
 */
#include "CompatibleInfo.h"
#ifdef ECU_ADDRESS_BLDC

RTStatus Com_Rx_status = Open;
RTStatus Com_Tx_status = Open;
RTStatus Nm_Rx_status  = Open;
RTStatus Nm_Tx_status  = Open;

RTStatus getCom_Rx_status(void)
{
	return Com_Rx_status;
}

RTStatus getCom_Tx_status(void)
{
	return Com_Tx_status;
}

RTStatus getNm_Rx_status(void)
{
	return Nm_Rx_status;
}

RTStatus getNm_Tx_status(void)
{
	return Nm_Tx_status;
}


/********************** UDS ***************************/
RTStatus UDS_ComRx = Open;
RTStatus UDS_ComTx = Open;
RTStatus UDS_NmRx  = Open;
RTStatus UDS_NmTx  = Open;

RTStatus getUDS_ComRx(void)
{
	return UDS_ComRx;
}

RTStatus getUDS_ComTx(void)
{
	return UDS_ComTx;
}

RTStatus getUDS_NmRx(void)
{
	return UDS_NmRx;
}

RTStatus getUDS_NmTx(void)
{
	return UDS_NmTx;
}

#endif


