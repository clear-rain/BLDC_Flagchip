#ifndef COM_CFG_H_
#define COM_CFG_H_

#include "v_def.h"
#include "BspCan.h"
#include "com.h"

#define COM_MAIN_PERIOD 5

#ifdef COM_SIG_INTEL
#define COM_SIG_INTEL     1
#endif
#define COM_SIG_MOTOROLA  0
#define COM_PDU_RECEIVE   0
#define COM_PDU_TRANSMIT  1


#ifdef ECU_ADDRESS_PDM_FL

/*BD CAN RX Frame*/
#define COM_RX_PDUID_150   0x150
#define COM_RX_PDUID_5E2   0x5E2
#define COM_RX_PDUID_1C2   0x1C2
#define COM_RX_PDUID_2A0   0x2A0
#define COM_RX_PDUID_3AE   0x3AE
#define COM_RX_PDUID_3AF   0x3AF
#define COM_RX_PDUID_3AA   0x3AA

/*BD CAN TX Frame*/

#define COM_TX_PDUID_5C3   0x5C3
#define COM_TX_PDUID_3B6   0x3B6
#define COM_TX_PDUID_3A6   0x3A6

/*AsrNM Frame*/
#define COM_RX_PDUID_NM   0x43F
#define COM_TX_PDUID_NM   0x471

/*Diag Frame*/
#define COM_RX_PHY_Diag   0x771
#define COM_RX_FUN_Diag   0x7DF
#define COM_TX_Diag       0x779

/*XCP Frame*/
#define XCP_RX_PDUID   0x6C0
#define XCP_TX_PDUID   0x6C1

/*Invalid Frame*/
#define Invalid_PDUID  0xFFFF

#define COM_PDUS_CNT   PDU_NUM

/*TX AsrNM signal:0x538*/
extern uint8 comTxNM_FrameID;
extern uint8 comTxRepMessage_State;
extern uint8 comTxActiveWakeup;
extern uint8 comTxRepeatState;


/*new add*/
/*TX PDM_FL_Fault_0x5C3 : 5C3*/
extern uint8 Com_PDM_FL_TotalFaultNum;
extern uint8 Com_PDM_FL_FrameIndex;
extern uint8 Com_PDM_FL_SupplierNum;
extern uint16 Com_PDM_FL_FaultNum1;
extern uint16 Com_PDM_FL_FaultNum2;
extern uint16 Com_PDM_FL_FaultNum3;
extern uint16 Com_PDM_FL_FaultNum4;

/*TX PDM_FL_IMUSt_0x3B6 : 3B6*/
extern float32 Com_PDM_FL_SlopeX;
extern float32 Com_PDM_FL_SlopeY;
extern uint8 	Com_PDM_FL_IMUSt;

/*TX PDM_FL_St_0x3A6 : 3A6*/
extern uint8 Com_PDM_FL_Ag;
extern float32 Com_PDM_FL_DoorOpeningAgrSpd;
extern uint8 Com_PDM_FL_AntiPlaySt;
extern uint8 Com_PDM_FL_AntiPinchSt;
extern uint8 Com_PDM_FL_NCODSt;
extern uint8 Com_PDM_FL_FolwUpSt;
extern uint8 Com_PDM_FL_MtnSt;
extern uint8 Com_PDM_FL_LrnSt;
extern uint8 Com_PDM_FL_SysFlt;
extern uint8 Com_PDM_FL_SelfLrnMeclPosn;
extern uint8 Com_PDM_FL_MaxPosnLrnSt;
extern uint8 Com_PDM_FL_ZeroPosnLrnSt;
extern uint8 Com_PDM_FL_InstallPosnLrnSt;
extern uint8 Com_PDM_FL_OverTProtnSt;
extern uint8 Com_PDM_FL_ModSetFb;
extern uint8 Com_PDM_FL_OpenSpdSetFb;
extern uint8 Com_PDM_FL_FullOpenDegSetFb;
extern uint8 Com_PDM_FL_DRDDetnEna;
extern uint8 Com_PDM_FL_FailReazon;

/*NM_Autosar_PDM_FL_0x471 : 471*/
extern uint8 Com_PDM_FL_SourceNodeIdentifier;
extern uint8 Com_PDM_FL_RepeatMessageRequestBit;
extern uint8 Com_PDM_FL_ActiveWakeupBit;
extern uint8 Com_PDM_FL_RepeatSts;
extern uint8 Com_PDM_FL_NMReq_NM;
extern uint8 Com_PDM_FL_NMReq_Diag;
extern uint8 Com_PDM_FL_NMReq_Poweron;
extern uint8 Com_PDM_FL_NMReq_GyroWakeup;
extern uint8 Com_PDM_FL_FirstWakeupReason;

/*RX DRD_FL_St : 150*/
extern uint8 Com_DRD_FL_DoorOpenAg;
extern float32 Com_DRD_FL_ObstclXDst;
extern float32 Com_DRD_FL_ObstclYDst;
extern float32 Com_DRD_FL_ObstclZDst;
extern float32 Com_DRD_FL_ObstclSpd;
extern uint8 Com_DRD_FL_Err;
extern uint8 Com_DRD_FL_St;
extern uint8 Com_DRD_FL_InstallPosnLrnSt;
extern uint8 Com_DRD_FL_Req;

/*RX TBOX_TimeInfo_5E2 : 5E2*/
extern uint16 Com_TBOX_TimeYear;
extern uint8 Com_TBOX_TimeMonth;
extern uint8 Com_TBOX_TimeDay;
extern uint8 Com_TBOX_TimeHour;
extern uint8 Com_TBOX_TimeMinute;
extern uint8 Com_TBOX_TimeSecond;
extern uint8 Com_TBOX_TimeZone;
extern uint8 Com_TBOX_TimeZoneNum;
extern uint8 Com_TBOX_TimeFlag;

 /*RX VIU_Info_Prof1A : 1C2*/
extern uint8 Com_VIU_Info_Prof1A_Checksum;
extern uint8 Com_VIU_Info_Prof1A_Counter;
extern uint8 Com_VIU_CarMode;
extern uint8 Com_VIU_UsageMode;
extern uint8 Com_VIU_PowerModeFltFlag;
extern uint8 Com_VIU_PowerMode;

/*RX VIU0_0x2A0 : 2A0*/
extern uint8 Com_VIU_RRDoorSt;
extern uint8 Com_VIU_RLDoorSt;
extern uint8 Com_VIU_PassDoorSt;
extern uint8 Com_VIU_DrvrDoorSt;
extern uint8 Com_VIU_DrvrDoorLockSt3;
extern uint8 Com_VIU_DrvrDoorLockSt2;
extern uint8 Com_VIU_TailgateSt;
extern uint8 Com_VIU_FLWinOpenDeg;
extern uint8 Com_VIU_FRWinOpenDeg;
extern uint8 Com_VIU_RLWinOpenDeg;
extern uint8 Com_VIU_RRWinOpenDeg;
extern float32 Com_VDC_AmbT;
extern uint8 Com_VIU_DrvrDoorLockStVld;
extern uint8 Com_VIU_DrvrDoorLockSt;

/*RX VIU0_0x3AE : 3AE*/
extern uint8 Com_IPB_VehicleSpeedValid;
extern uint8 Com_VDC_brakePedalSts;
extern float32 Com_IPB_VehicleSpeed;
extern uint32 Com_VDC_TotalRang;
extern uint8 Com_VDC_actualGear;
extern uint8 Com_VDC_actualGearValid;

/*RX VIU0_0x3AF : 3AF*/
extern float32 Com_ABM_IMU_LongAcceleration;
extern float32 Com_ABM_IMU_LateralAcceleration;
extern float32 Com_ABM_IMU_YawRate;

/*RX VIU0_CDC_0x3AA : 3AA*/
extern uint8 Com_CDC_FullOpenDegSet;
extern uint8 Com_CDC_ModSet;
extern uint8 Com_CDC_PDMFL_Ctrl;
extern uint8 Com_CDC_HndFeelSet;
extern uint8 Com_CDC_OpenSpdSet;

/*RX NM_Autosar_VIU1_0x43F : 43F*/
extern uint8 Com_VIU0_SourceNodeIdentifier;
extern uint8 Com_VIU0_RepeatMessageRequestBit;
extern uint8 Com_VIU0_ActiveWakeupBit;
extern uint8 Com_VIU0_RepeatSts;


#endif

#ifdef ECU_ADDRESS_PDM_FR
/*BD CAN RX Frame*/
#define COM_RX_PDUID_151   0x151
#define COM_RX_PDUID_5E2   0x5E2
#define COM_RX_PDUID_1C2   0x1C2
#define COM_RX_PDUID_2A1   0x2A1
#define COM_RX_PDUID_3AE   0x3AE
#define COM_RX_PDUID_3AF   0x3AF
#define COM_RX_PDUID_3AB   0x3AB

/*BD CAN TX Frame*/

#define COM_TX_PDUID_5CB   0x5CB
#define COM_TX_PDUID_3B7   0x3B7
#define COM_TX_PDUID_3A7   0x3A7

/*AsrNM Frame*/
#define COM_RX_PDUID_NM   0x449
#define COM_TX_PDUID_NM   0x472

/*Diag Frame*/
#define COM_RX_PHY_Diag   0x770
#define COM_RX_FUN_Diag   0x7DF
#define COM_TX_Diag       0x778

/*XCP Frame*/
#define XCP_RX_PDUID   0x6C2
#define XCP_TX_PDUID   0x6C3

/*Invalid Frame*/
#define Invalid_PDUID  0xFFFF

#define COM_PDUS_CNT   PDU_NUM



/*RX DRD_FR_St : 150*/
extern uint8 Com_DRD_FR_DoorOpenAg;
extern float32 Com_DRD_FR_ObstclXDst;
extern float32 Com_DRD_FR_ObstclYDst;
extern float32 Com_DRD_FR_ObstclZDst;
extern float32 Com_DRD_FR_ObstclSpd;
extern uint8 Com_DRD_FR_Err;
extern uint8 Com_DRD_FR_St;
extern uint8 Com_DRD_FR_InstallPosnLrnSt;
extern uint8 Com_DRD_FR_Req;

/*RX TBOX_TimeInfo_5E2 : 5E2*/
extern uint16 Com_TBOX_TimeYear;
extern uint8 Com_TBOX_TimeMonth;
extern uint8 Com_TBOX_TimeDay;
extern uint8 Com_TBOX_TimeHour;
extern uint8 Com_TBOX_TimeMinute;
extern uint8 Com_TBOX_TimeSecond;
extern uint8 Com_TBOX_TimeZone;
extern uint8 Com_TBOX_TimeZoneNum;
extern uint8 Com_TBOX_TimeFlag;

/*RX VIU_Info_Prof1A : 1C2*/
extern uint8 Com_VIU_Info_Prof1A_Checksum;
extern uint8 Com_VIU_Info_Prof1A_Counter;
extern uint8 Com_VIU_CarMode;
extern uint8 Com_VIU_UsageMode;
extern uint8 Com_VIU_PowerModeFltFlag;
extern uint8 Com_VIU_PowerMode;

/*RX VIU1_0x2A1 : 2A1*/
extern uint8 Com_VIU_RRDoorSt;
extern uint8 Com_VIU_RLDoorSt;
extern uint8 Com_VIU_PassDoorSt;
extern uint8 Com_VIU_DrvrDoorSt;
extern uint8 Com_VIU_PassDoorLockSt3;
extern uint8 Com_VIU_PassDoorLockSt2;
extern uint8 Com_VIU_TailgateSt;
extern uint8 Com_VIU_FLWinOpenDeg;
extern uint8 Com_VIU_FRWinOpenDeg;
extern uint8 Com_VIU_RLWinOpenDeg;
extern uint8 Com_VIU_RRWinOpenDeg;
extern float32 Com_VDC_AmbT;
extern uint8 Com_VIU_PassDoorLockSt;

/*RX VIU1_0x3AE : 3AE*/
extern uint8 Com_IPB_VehicleSpeedValid;
extern uint8 Com_VDC_brakePedalSts;
extern float32 Com_IPB_VehicleSpeed;
extern uint32 Com_VDC_TotalRang;
extern uint8 Com_VDC_actualGear;
extern uint8 Com_VDC_actualGearValid;

/*RX VIU1_0x3AF : 3AF*/
extern float32 Com_ABM_IMU_LongAcceleration;
extern float32 Com_ABM_IMU_LateralAcceleration;
extern float32 Com_ABM_IMU_YawRate;

/*RX VIU1_CDC_0x3AB : 3AB*/
extern uint8 Com_CDC_OpenSpdSet;
extern uint8 Com_CDC_FullOpenDegSet;
extern uint8 Com_CDC_ModSet;
extern uint8 Com_CDC_PDMFR_Ctrl;
extern uint8 Com_CDC_HndFeelSet;
extern uint8 Com_VIU_PassSeatOccptSt;

/*RX NM_Autosar_VIU1_0x449 : 449*/
extern uint8 Com_VIU1_SourceNodeIdentifier;
extern uint8 Com_VIU1_RepeatMessageRequestBit;
extern uint8 Com_VIU1_ActiveWakeupBit;
extern uint8 Com_VIU1_RepeatSts;

/*TX PDM_FR_Fault_0x5CB : 5CB*/
extern uint8 Com_PDM_FR_TotalFaultNum;
extern uint8 Com_PDM_FR_FrameIndex;
extern uint8 Com_PDM_FR_SupplierNum;
extern uint16 Com_PDM_FR_FaultNum1;
extern uint16 Com_PDM_FR_FaultNum2;
extern uint16 Com_PDM_FR_FaultNum3;
extern uint16 Com_PDM_FR_FaultNum4;

/*TX PDM_FR_IMUSt_0x3B7 : 3B7*/
extern float32 Com_PDM_FR_SlopeX;
extern float32 Com_PDM_FR_SlopeY;
extern uint8 	Com_PDM_FR_IMUSt;

/*TX PDM_FR_St_0x3A7 : 3A7*/
extern uint8 Com_PDM_FR_Ag;
extern float32 Com_PDM_FR_DoorOpeningAgrSpd;
extern uint8 Com_PDM_FR_AntiPlaySt;
extern uint8 Com_PDM_FR_AntiPinchSt;
extern uint8 Com_PDM_FR_NCODSt;
extern uint8 Com_PDM_FR_FolwUpSt;
extern uint8 Com_PDM_FR_MtnSt;
extern uint8 Com_PDM_FR_LrnSt;
extern uint8 Com_PDM_FR_SysFlt;
extern uint8 Com_PDM_FR_SelfLrnMeclPosn;
extern uint8 Com_PDM_FR_MaxPosnLrnSt;
extern uint8 Com_PDM_FR_ZeroPosnLrnSt;
extern uint8 Com_PDM_FR_InstallPosnLrnSt;
extern uint8 Com_PDM_FR_OverTProtnSt;
extern uint8 Com_PDM_FR_ModSetFb;
extern uint8 Com_PDM_FR_OpenSpdSetFb;
extern uint8 Com_PDM_FR_FullOpenDegSetFb;
extern uint8 Com_PDM_FR_DRDDetnEna;
extern uint8 Com_PDM_FR_FailReazon;

/*NM_Autosar_VIU1_0x472: 0x472*/
extern uint8 Com_PDM_FR_SourceNodeIdentifier;
extern uint8 Com_PDM_FR_RepeatMessageRequestBit;
extern uint8 Com_PDM_FR_ActiveWakeupBit;
extern uint8 Com_PDM_FR_RepeatSts;
extern uint8 Com_PDM_FR_NMReq_NM;
extern uint8 Com_PDM_FR_NMReq_Diag;
extern uint8 Com_PDM_FR_NMReq_Poweron;
extern uint8 Com_PDM_FR_NMReq_GyroWakeup;
extern uint8 Com_PDM_FR_FirstWakeupReason;



#endif


typedef struct {
    uint8       start; /*format= intel,start:signal start bit ;format = matorola, start: signal end bit*/
    uint8       len;
    uint16      FrameId;
    boolean     integer;
    boolean     unsign;
    uint8       format;
    float32     factor;
    float32     offset;
    void        *pVal;
} ComSigType;

typedef enum{
	Cycle = 0,
	CE,
	Event
} MsgSendType;

typedef struct {
    uint8       busController;
    uint16      pdurPduId;
    uint8       dir;
    uint16      period; /* 0 : means event message */
    MsgSendType msgtype;
    uint16      sigStart;
    uint16      sigEnd;
} ComPduType;

typedef enum{
	SigInvalid = 0,
	SigValid,
	SigReserved,

}Sig_ReturnType;

typedef struct {
    boolean active;
    boolean ready;
    uint8 buf[8];
    uint16 tick;
    uint8 CE;//change event
    uint8 dir;
    MsgSendType msgtype;
} ComRunPduDatasType;

extern const ComSigType comSigs[];

extern ComRunPduDatasType comRunPduDatasList[];

uint16 getCom_SIGNALS_CNT(void);
#endif
