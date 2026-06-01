/**
 * @file BspCan.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */


#ifndef INC_BSPCAN_H_
#define INC_BSPCAN_H_

#include "main.h"
#include "module_driver_flexcan.h"
#include "XcpBasic.h"
#include "Com_cfg.h"
#include "Pdu_cfg.h"
#include "string.h"
#include "com.h"

typedef struct
{
	uint8                	ui8Index;
	FLEXCAN_MbSettingType 	stFLEXCAN_RxFilter;
	uint16					ui16CanRxTimeoutThreshold;
	uint8					ui8Dlc;
	uint8 *					pui8CanRxBuffer;
	uint16 *				pui16CanRxTimeoutCnt;
	uint8					ui8CanRx_Flag;
	uint8					ui8StartBit_Index;
	uint8					ui8TimeOut_Flag;
	uint16                  PDUIndex;
}Bsp_CanRxInit_t;

#include "Pdu.h"

#define     CAN_NM_ID			COM_RX_PDUID_NM
#define     CAN_DIAG_PHY_ID		0x731
#define     CAN_DIAG_FUNC_ID	0x7DF

#ifdef ECU_ADDRESS_PDM_FL

#define		CANTX_NUM		(6u)
#define		CANRX_NUM		(11u)

#define TXMAILBOX_5C3_INDEX  0
#define TXMAILBOX_3B6_INDEX  1
#define TXMAILBOX_3A6_INDEX  2
#define TXMAILBOX_6C1_INDEX  3
#define TXMAILBOX_471_INDEX  4
#define TXMAILBOX_779_INDEX  5

Std_ReturnType Can_CheckTimeOut_DRD_FL_St_0x150(void);
Std_ReturnType Can_CheckTimeOut_TBOX_TimeInfo_0x5E2(void);
Std_ReturnType Can_CheckTimeOut_TVIU_Info_Prof1A_0x1C2(void);
Std_ReturnType Can_CheckTimeOut_VIU0_0x2A0(void);
Std_ReturnType Can_CheckTimeOut_VIU0_0x3AE(void);
Std_ReturnType Can_CheckTimeOut_VIU0_0x3AF(void);
Std_ReturnType Can_CheckTimeOut_VIU0_CDC_0x3AA(void);

#endif

#ifdef ECU_ADDRESS_PDM_FR
#define		CANTX_NUM		(6u)
#define		CANRX_NUM		(11u)

#define TXMAILBOX_5CB_INDEX  0
#define TXMAILBOX_3B7_INDEX  1
#define TXMAILBOX_3A7_INDEX  2
#define TXMAILBOX_6C3_INDEX  3
#define TXMAILBOX_472_INDEX  4
#define TXMAILBOX_778_INDEX  5


Std_ReturnType Can_CheckTimeOut_DRD_FR_St_0x151(void);
Std_ReturnType Can_CheckTimeOut_TBOX_TimeInfo_0x5E2(void);
Std_ReturnType Can_CheckTimeOut_VIU_Info_Prof1A_0x1C2(void);
Std_ReturnType Can_CheckTimeOut_VIU_0x2A1(void);
Std_ReturnType Can_CheckTimeOut_VIU1_0x3AE(void);
Std_ReturnType Can_CheckTimeOut_VIU1_0x3AF(void);
Std_ReturnType Can_CheckTimeOut_VIU1_CDC_0x3AB(void);

#endif


#define PDU_NUM (CANRX_NUM+CANTX_NUM)

extern FLEXCAN_HandleType  g_tCan1;
extern FLEXCAN_HandleType  g_tCan2;


typedef struct
{
	uint8                	ui8Index;
	uint32					ui32FrameId;
	uint8					ui8MBindex;
	uint16 				 	ui16CanTxPeriod;
	uint8					ui8Delay;
	uint8					ui8Dlc;
	uint8 *					pui8CanTxBuffer;
	uint16                  PDUIndex;
}Bsp_CanTxInit_t;

typedef enum
{
	TimeOut_False = 0,
	TimeOut_True,
	TimeOut_NotSupport
}CheckResult_t;

extern Bsp_CanRxInit_t g_stBsp_CanRxInit[CANRX_NUM];

void BSP_CAN_Init(void);

void BSP_CAN_TransmitData(void);

void GetCanRxTimeOutResult_100ms(void);

void CanRxTimeOutCheckOut_1ms(void);

void Analysis_Com_signal_Task(void);

void XcpFifoStructInit(void);
void XcpEventTransmit_1ms(void);
void ApplXcpSend( uint8_t len,const uint8_t* msg );
FLEXCAN_ErrorType BSP_XCP_Transmit(uint8_t len,const uint8_t* msg,uint32 ID);
void BSP_CAN_Init(void);
void BSP_CAN_Transmit(uint32 FrameId,uint8 *pduInfoPtr,FLEXCAN_HandleType g_tCan);
void Bsp_CAN_DeInit(void);
#endif /* INC_BSPCAN_H_ */
