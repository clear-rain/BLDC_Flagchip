#ifndef RTE_RTE_H_
#define RTE_RTE_H_



#include <stdint.h>
#include "v_def.h"
#include <stdbool.h>

#ifndef ECU_ADDRESS_BLDC

void Rte_SetProgrammingReq(uint8_t SuppressPosRsp);
void Rte_OTAModeInit(void);
void Rte_UpdateOTAMode(void);
uint8_t Rte_GetOTA_Mode(void);

#define ENTER_OTA_MODE                  0x55U
#define EXIT_OTA_MODE                   0x00U


#ifdef ECU_ADDRESS_PDM_FL
/*TimeOut API*/
bool RTE_Read_CheckTimeOut_DRD_FL_St_0x150(void);
bool RTE_Read_CheckTimeOut_TBOX_TimeInfo_0x5E2(void);
bool RTE_Read_CheckTimeOut_TVIU_Info_Prof1A_0x1C2(void);
bool RTE_Read_CheckTimeOut_VIU0_0x2A0(void);
bool RTE_Read_CheckTimeOut_VIU0_0x3AE(void);
bool RTE_Read_CheckTimeOut_VIU0_0x3AF(void);
bool RTE_Read_CheckTimeOut_VIU0_CDC_0x3AA(void);
/*TimeOut API*/

Std_ReturnType RTE_Read_Com_DRD_FL_DoorOpenAg(uint8 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclXDst(float32 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclYDst(float32 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclZDst(float32 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclSpd(float32 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_St(uint8 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_Err(uint8 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_Req(uint8 * pData);//0x150
Std_ReturnType RTE_Read_Com_DRD_FL_InstallPosnLrnSt(uint8 * pData);//0x150

Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Checksum(uint8 * pData);//0x1C2
Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Counter(uint8 * pData);//0x1C2
Std_ReturnType RTE_Read_Com_VIU_UsageMode(uint8 * pData);//0x1C2
Std_ReturnType RTE_Read_Com_VIU_CarMode(uint8 * pData);//0x1C2
Std_ReturnType RTE_Read_Com_VIU_PowerMode(uint8 * pData);//0x1C2
Std_ReturnType RTE_Read_Com_VIU_PowerModeFltFlag(uint8 * pData);//0x1C2

Std_ReturnType RTE_Read_Com_VIU_DrvrDoorSt(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_PassDoorSt(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_RLDoorSt(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_RRDoorSt(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_TailgateSt(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockSt2(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockSt3(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_FLWinOpenDeg(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_FRWinOpenDeg(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_RLWinOpenDeg(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_RRWinOpenDeg(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VDC_AmbT(float32 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockSt(uint8 * pData);//0x2A0
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockStVld(uint8 * pData);//0x2A0

Std_ReturnType RTE_Read_Com_IPB_VehicleSpeedValid(uint8 * pData);//0x3AE
Std_ReturnType RTE_Read_Com_VDC_brakePedalSts(uint8 * pData);//0x3AE
Std_ReturnType RTE_Read_Com_IPB_VehicleSpeed(float32 * pData);//0x3AE
Std_ReturnType RTE_Read_Com_VDC_TotalRang(uint32 * pData);//0x3AE
Std_ReturnType RTE_Read_Com_VDC_actualGear(uint8 * pData);
Std_ReturnType RTE_Read_Com_VDC_actualGearValid(uint8 * pData);//0x3AE

Std_ReturnType RTE_Read_Com_ABM_IMU_LongAcceleration(float32 * pData);//0x3AF
Std_ReturnType RTE_Read_Com_ABM_IMU_LateralAcceleration(float32 * pData);//0x3AF
Std_ReturnType RTE_Read_Com_ABM_IMU_YawRate(float32 * pData);//0x3AF

Std_ReturnType RTE_Read_Com_CDC_ModSet(uint8 * pData);//0x3AA
Std_ReturnType RTE_Read_Com_CDC_FullOpenDegSet(uint8 * pData);//0x3AA
Std_ReturnType RTE_Read_Com_CDC_OpenSpdSet(uint8 * pData);//0x3AA
Std_ReturnType RTE_Read_Com_CDC_HndFeelSet(uint8 * pData);//0x3AA
Std_ReturnType RTE_Read_Com_CDC_PDMFL_Ctrl(uint8 * pData);//0x3AA
Std_ReturnType RTE_Read_Com_VIU0_SourceNodeIdentifier(uint8 * pData); //0x43F
Std_ReturnType RTE_Read_Com_VIU0_RepeatMessageRequestBit(uint8 * pData); //0x43F
Std_ReturnType RTE_Read_Com_VIU0_ActiveWakeupBit(uint8 * pData); //0x43F
Std_ReturnType RTE_Read_Com_VIU0_RepeatSts(uint8 * pData); //0x43F

Std_ReturnType RTE_Read_Com_TBOX_TimeYear(uint16 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeMonth(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeDay(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeHour(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeMinute(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeSecond(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeZone(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeZoneNum(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeFlag(uint8 * pData); //0x5E2



Std_ReturnType RTE_Write_Com_PDM_FL_IMUSt(uint8 data);//0x3B6
Std_ReturnType RTE_Write_Com_PDM_FL_SlopeX (float32 data);//0x3B6
Std_ReturnType RTE_Write_Com_PDM_FL_SlopeY (float32 data);//0x3B6

Std_ReturnType RTE_Write_Com_PDM_FL_Ag (uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_AntiPinchSt (uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_AntiPlaySt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_DoorOpeningAgrSpd(float32 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_DRDDetnEna(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_FailReazon(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_FolwUpSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_FullOpenDegSetFb(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_InstallPosnLrnSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_LrnSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_MaxPosnLrnSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_ModSetFb(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_MtnSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_NCODSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_PDM_FL_OpenSpdSetFb(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_OverTProtnSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_PDM_FL_SelfLrnMeclPosn(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_SysFlt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_ZeroPosnLrnSt(uint8 data);//0x3A6
Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum1(uint16 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum2(uint16 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum3(uint16 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum4(uint16 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_FrameIndex(uint8 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_TotalFaultNum(uint8 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_SupplierNum(uint8 data);//0x5C3
Std_ReturnType RTE_Write_comTxNM_FrameID(uint8 data);//0x471
Std_ReturnType RTE_Write_comTxRepMessage_State(uint8 data);//0x471
Std_ReturnType RTE_Write_comTxActiveWakeup(uint8 data);//0x471
Std_ReturnType RTE_Write_comTxRepeatState(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_NM(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_Diag(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_Poweron(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_GyroWakeup(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FL_FirstWakeupReason(uint8 data);//0x471

#endif

#ifdef ECU_ADDRESS_PDM_FR
/*TimeOut API*/
bool RTE_Read_CheckTimeOut_DRD_FR_St_0x151(void);
bool RTE_Read_CheckTimeOut_TBOX_TimeInfo_0x5E2(void);
bool RTE_Read_CheckTimeOut_VIU_Info_Prof1A_0x1C2(void);
bool RTE_Read_CheckTimeOut_TBOX_VIU_0x2A1(void);
bool RTE_Read_CheckTimeOut_VIU1_0x3AE(void);
bool RTE_Read_CheckTimeOut_VIU1_0x3AF(void);
bool RTE_Read_CheckTimeOut_VIU1_CDC_0x3AB(void);
/*TimeOut API*/
Std_ReturnType RTE_Read_Com_DRD_FR_DoorOpenAg(uint8 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclXDst(float32 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclYDst(float32 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclZDst(float32 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclSpd(float32 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_St(uint8 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_Err(uint8 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_Req(uint8 * pData);
Std_ReturnType RTE_Read_Com_DRD_FR_InstallPosnLrnSt(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Checksum(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Counter(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_UsageMode(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_CarMode(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_PowerMode(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_PowerModeFltFlag(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorSt(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_PassDoorSt(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_RLDoorSt(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_RRDoorSt(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_TailgateSt(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_PassDoorLockSt2(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_PassDoorLockSt3(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_FLWinOpenDeg(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_FRWinOpenDeg(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_RLWinOpenDeg(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU_RRWinOpenDeg(uint8 * pData);
Std_ReturnType RTE_Read_Com_VDC_AmbT(float32 * pData);
Std_ReturnType RTE_Read_Com_VIU_PassDoorLockSt(uint8 * pData);
Std_ReturnType RTE_Read_Com_IPB_VehicleSpeedValid(uint8 * pData);
Std_ReturnType RTE_Read_Com_VDC_brakePedalSts(uint8 * pData);
Std_ReturnType RTE_Read_Com_IPB_VehicleSpeed(float32 * pData);
Std_ReturnType RTE_Read_Com_VDC_TotalRang(uint32 * pData);
Std_ReturnType RTE_Read_Com_VDC_actualGear(uint8 * pData);
Std_ReturnType RTE_Read_Com_VDC_actualGearValid(uint8 * pData);//0x3AE
Std_ReturnType RTE_Read_Com_ABM_IMU_LongAcceleration(float32 * pData);
Std_ReturnType RTE_Read_Com_ABM_IMU_LateralAcceleration(float32 * pData);
Std_ReturnType RTE_Read_Com_ABM_IMU_YawRate(float32 * pData);
Std_ReturnType RTE_Read_Com_CDC_ModSet(uint8 * pData);
Std_ReturnType RTE_Read_Com_CDC_FullOpenDegSet(uint8 * pData);
Std_ReturnType RTE_Read_Com_CDC_OpenSpdSet(uint8 * pData);
Std_ReturnType RTE_Read_Com_CDC_HndFeelSet(uint8 * pData);
Std_ReturnType RTE_Read_Com_CDC_PDMFR_Ctrl(uint8 * pData);
Std_ReturnType RTE_Read_Com_VIU1_SourceNodeIdentifier(uint8 * pData); //0x449
Std_ReturnType RTE_Read_Com_VIU1_RepeatMessageRequestBit(uint8 * pData); //0x449
Std_ReturnType RTE_Read_Com_VIU1_ActiveWakeupBit(uint8 * pData); //0x449
Std_ReturnType RTE_Read_Com_VIU1_RepeatSts(uint8 * pData); //0x449
Std_ReturnType RTE_Read_Com_TBOX_TimeYear(uint16 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeMonth(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeDay(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeHour(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeMinute(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeSecond(uint8 * pData); //0x5E2
//Std_ReturnType RTE_Read_Com_TBOX_TimeSecond(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeZone(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeZoneNum(uint8 * pData); //0x5E2
Std_ReturnType RTE_Read_Com_TBOX_TimeFlag(uint8 * pData); //0x5E2

Std_ReturnType RTE_Write_Com_PDM_FR_IMUSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_SlopeX (float32 data);
Std_ReturnType RTE_Write_Com_PDM_FR_SlopeY (float32 data);
Std_ReturnType RTE_Write_Com_PDM_FR_Ag (uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_AntiPinchSt (uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_AntiPlaySt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_DoorOpeningAgrSpd(float32 data);
Std_ReturnType RTE_Write_Com_PDM_FR_DRDDetnEna(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_FailReazon(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_FolwUpSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_FullOpenDegSetFb(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_InstallPosnLrnSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_LrnSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_MaxPosnLrnSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_ModSetFb(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_MtnSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_NCODSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_PDM_FR_OpenSpdSetFb(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_OverTProtnSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_PDM_FR_SelfLrnMeclPosn(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_SysFlt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_ZeroPosnLrnSt(uint8 data);
Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum1(uint16 data);//0x5CB
Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum2(uint16 data);//0x5CB
Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum3(uint16 data);//0x5CB
Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum4(uint16 data);//0x5CB
Std_ReturnType RTE_Write_Com_PDM_FR_FrameIndex(uint8 data);//0x5CB
Std_ReturnType RTE_Write_Com_PDM_FR_TotalFaultNum(uint8 data);//0x5CB
Std_ReturnType RTE_Write_Com_PDM_FR_SupplierNum(uint8 data);//0x5CB
Std_ReturnType RTE_Write_comTxNM_FrameID(uint8 data);
Std_ReturnType RTE_Write_comTxRepMessage_State(uint8 data);//0x471
Std_ReturnType RTE_Write_comTxActiveWakeup(uint8 data);//0x471
Std_ReturnType RTE_Write_comTxRepeatState(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_NM(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_Diag(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_Poweron(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_GyroWakeup(uint8 data);//0x471
Std_ReturnType RTE_Write_Com_PDM_FR_FirstWakeupReason(uint8 data);//0x471

#endif
Std_ReturnType RTE_Read_Time(uint32 * pData);

#else
Std_ReturnType RTE_Read_Com_DRD_FL_DoorOpenAg(uint8 * pData);//0x150


Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum1(uint16 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum2(uint16 data);//0x5C3
Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum3(uint16 data);//0x5C3
#endif  /*ECU_ADDRESS_BLDC*/

#endif /* RTE_RTE_H_ */



