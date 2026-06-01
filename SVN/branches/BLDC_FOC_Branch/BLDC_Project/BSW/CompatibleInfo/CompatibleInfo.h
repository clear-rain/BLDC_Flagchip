/*
 *CompatibleInfo.h
 *
 *  Created on: 2025年7月23日
 *      Author: jiang
 */

#ifndef BSW_COMPATIBLEINFO_COMPATIBLEINFO_H_
#define BSW_COMPATIBLEINFO_COMPATIBLEINFO_H_

/****************** CAN NM******************************/
#ifdef ECU_ADDRESS_BLDC
typedef enum{
	Close = 0u,
	Open
}RTStatus;

RTStatus getCom_Rx_status(void);
RTStatus getCom_Tx_status(void);
RTStatus getNm_Rx_status(void);
RTStatus getNm_Tx_status(void);

/********************* UDS***************************************/
#define CAN_NORMAL                      0x00U

RTStatus getUDS_ComRx(void);
RTStatus getUDS_ComTx(void);
RTStatus getUDS_NmRx(void);
RTStatus getUDS_NmTx(void);



#endif

#endif /* BSW_COMPATIBLEINFO_COMPATIBLEINFO_H_ */
