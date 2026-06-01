#include "com_cfg.h"

/*BD CAN RX/TX signal*/
uint8 comRxReqMessage_State = 0;
uint8 comRxActiveWakeup = 0;
/*TX AsrNM signal:0x538*/
const uint8 comTxNM_FrameIDInitVal = 0;
uint8 comTxNM_FrameID = 0;
const uint8 comTxRepMessage_StateInitVal = 0;
uint8 comTxRepMessage_State = 0;
const uint8 comTxActiveWakeupInitVal = 0;
uint8 comTxActiveWakeup = 0;
const uint8 comTxRepeatStateInitVal = 0;
uint8 comTxRepeatState = 0;

#ifdef ECU_ADDRESS_PDM_FL

/*new add*/
/*TX PDM_FL_Fault_0x5C3 : 5C3*/
uint8 Com_PDM_FL_TotalFaultNum = 0;
uint8 Com_PDM_FL_FrameIndex = 0;
uint8 Com_PDM_FL_SupplierNum = 0;
uint16 Com_PDM_FL_FaultNum1 = 0;
uint16 Com_PDM_FL_FaultNum2 = 0;
uint16 Com_PDM_FL_FaultNum3 = 0;
uint16 Com_PDM_FL_FaultNum4 = 0;


/*TX PDM_FL_IMUSt_0x3B6 : 3B6*/
float32 Com_PDM_FL_SlopeX = 0;
float32 Com_PDM_FL_SlopeY = 0;
uint8 	Com_PDM_FL_IMUSt = 0;

/*TX PDM_FL_St_0x3A6 : 3A6*/
uint8 Com_PDM_FL_Ag = 86	;
float32 Com_PDM_FL_DoorOpeningAgrSpd = 0;
uint8 Com_PDM_FL_AntiPlaySt = 0;
uint8 Com_PDM_FL_AntiPinchSt = 0;
uint8 Com_PDM_FL_NCODSt = 0;
uint8 Com_PDM_FL_FolwUpSt = 0;
uint8 Com_PDM_FL_MtnSt = 0;
uint8 Com_PDM_FL_LrnSt = 0;
uint8 Com_PDM_FL_SysFlt = 0;
uint8 Com_PDM_FL_SelfLrnMeclPosn = 0;
uint8 Com_PDM_FL_MaxPosnLrnSt = 0;
uint8 Com_PDM_FL_ZeroPosnLrnSt = 0;
uint8 Com_PDM_FL_InstallPosnLrnSt = 0;
uint8 Com_PDM_FL_OverTProtnSt = 0;
uint8 Com_PDM_FL_ModSetFb = 0;
uint8 Com_PDM_FL_OpenSpdSetFb = 0;
uint8 Com_PDM_FL_FullOpenDegSetFb = 0;
uint8 Com_PDM_FL_DRDDetnEna = 0;
uint8 Com_PDM_FL_FailReazon = 0;

/*NM_Autosar_PDM_FL_0x471 : 471*/
uint8 Com_PDM_FL_SourceNodeIdentifier = 0;
uint8 Com_PDM_FL_RepeatMessageRequestBit = 0;
uint8 Com_PDM_FL_ActiveWakeupBit = 0;
uint8 Com_PDM_FL_RepeatSts = 0;
uint8 Com_PDM_FL_NMReq_NM = 0;
uint8 Com_PDM_FL_NMReq_Diag = 0;
uint8 Com_PDM_FL_NMReq_Poweron = 0;
uint8 Com_PDM_FL_NMReq_GyroWakeup = 0;
uint8 Com_PDM_FL_FirstWakeupReason = 0;




/*RX DRD_FL_St : 150*/
uint8 Com_DRD_FL_DoorOpenAg = 0;
float32 Com_DRD_FL_ObstclXDst = 0;
float32 Com_DRD_FL_ObstclYDst = 0;
float32 Com_DRD_FL_ObstclZDst = 0;
float32 Com_DRD_FL_ObstclSpd = 0;
uint8 Com_DRD_FL_Err = 0;
uint8 Com_DRD_FL_St = 0;
uint8 Com_DRD_FL_InstallPosnLrnSt = 0;
uint8 Com_DRD_FL_Req = 0;

/*RX TBOX_TimeInfo_5E2 : 5E2*/
uint16 Com_TBOX_TimeYear = 2000;
uint8 Com_TBOX_TimeMonth = 1;
uint8 Com_TBOX_TimeDay = 1;
uint8 Com_TBOX_TimeHour = 0;
uint8 Com_TBOX_TimeMinute = 0;
uint8 Com_TBOX_TimeSecond = 0;
uint8 Com_TBOX_TimeZone = 0;
uint8 Com_TBOX_TimeZoneNum = 0;
uint8 Com_TBOX_TimeFlag = 0;

/*RX VIU_Info_Prof1A : 1C2*/
uint8 Com_VIU_Info_Prof1A_Checksum = 0;
uint8 Com_VIU_Info_Prof1A_Counter = 0;
uint8 Com_VIU_CarMode = 14;
uint8 Com_VIU_UsageMode = 1;
uint8 Com_VIU_PowerModeFltFlag = 0;
uint8 Com_VIU_PowerMode = 0;

/*RX VIU0_0x2A0 : 2A0*/
uint8 Com_VIU_RRDoorSt = 0;
uint8 Com_VIU_RLDoorSt = 0;
uint8 Com_VIU_PassDoorSt = 0;
uint8 Com_VIU_DrvrDoorSt = 0;
uint8 Com_VIU_DrvrDoorLockSt3 = 0;
uint8 Com_VIU_DrvrDoorLockSt2 = 0;
uint8 Com_VIU_TailgateSt = 0;
uint8 Com_VIU_FLWinOpenDeg = 0;
uint8 Com_VIU_FRWinOpenDeg = 0;
uint8 Com_VIU_RLWinOpenDeg = 0;
uint8 Com_VIU_RRWinOpenDeg = 0;
float32 Com_VDC_AmbT = 0;
uint8 Com_VIU_DrvrDoorLockStVld = 0;
uint8 Com_VIU_DrvrDoorLockSt = 0;

/*RX VIU0_0x3AE : 3AE*/
uint8 Com_IPB_VehicleSpeedValid = 0;
uint8 Com_VDC_brakePedalSts = 0;
float32 Com_IPB_VehicleSpeed = 0;
uint32 Com_VDC_TotalRang = 0;
uint8 Com_VDC_actualGear = 0;
uint8 Com_VDC_actualGearValid = 0;


/*RX VIU0_0x3AF : 3AF*/
float32 Com_ABM_IMU_LongAcceleration = 0;
float32 Com_ABM_IMU_LateralAcceleration = 0;
float32 Com_ABM_IMU_YawRate = 0;

/*RX VIU0_CDC_0x3AA : 3AA*/
uint8 Com_CDC_FullOpenDegSet = 0;
uint8 Com_CDC_ModSet = 0;
uint8 Com_CDC_PDMFL_Ctrl = 0;
uint8 Com_CDC_HndFeelSet = 0;
uint8 Com_CDC_OpenSpdSet = 0;

/*RX NM_Autosar_VIU1_0x43F : 43F*/
uint8 Com_VIU0_SourceNodeIdentifier = 0;
uint8 Com_VIU0_RepeatMessageRequestBit = 0;
uint8 Com_VIU0_ActiveWakeupBit = 0;
uint8 Com_VIU0_RepeatSts = 0;




/*new add*/

/*Invalid signal*/
const uint8_t u8InvalidSigInitVal = 0;
uint8_t u8InvalidSig = 0;

const ComSigType comSigs[] =
{
		/*BCM*/
		/*Rx*/
		/*0x150 0*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_150,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FL_DoorOpenAg        		},
		{.start = 15,  .len =  8,  .FrameId = COM_RX_PDUID_150,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05,    .offset =   0       , .pVal = &Com_DRD_FL_ObstclXDst        		},
		{.start = 23,  .len =  8,  .FrameId = COM_RX_PDUID_150,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05,    .offset =   0       , .pVal = &Com_DRD_FL_ObstclYDst        		},
		{.start = 31,  .len =  8,  .FrameId = COM_RX_PDUID_150,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05,    .offset =   0       , .pVal = &Com_DRD_FL_ObstclZDst        		},
		{.start = 39,  .len =  8,  .FrameId = COM_RX_PDUID_150,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.03,    .offset =   0       , .pVal = &Com_DRD_FL_ObstclSpd        			},
		{.start = 43,  .len =  4,  .FrameId = COM_RX_PDUID_150,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FL_Err        				},
		{.start = 47,  .len =  4,  .FrameId = COM_RX_PDUID_150,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FL_St        				},
		{.start = 54,  .len =  2,  .FrameId = COM_RX_PDUID_150,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FL_InstallPosnLrnSt        	},
		{.start = 55,  .len =  1,  .FrameId = COM_RX_PDUID_150,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FL_Req        				},

		/*0x5E2 9*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset = 2000       , .pVal = &Com_TBOX_TimeYear        		},
		{.start = 11,  .len =  4,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeMonth        		},
		{.start = 20,  .len =  5,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeDay        		},
		{.start = 28,  .len =  5,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeHour        		},
		{.start = 37,  .len =  6,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeMinute        		},
		{.start = 45,  .len =  6,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeSecond        		},
		{.start = 49,  .len =  2,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeZone        		},
		{.start = 54,  .len =  5,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeZoneNum        		},
		{.start = 57,  .len =  2,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeFlag        		},
		/*0x1C2 18*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_1C2, .integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_Info_Prof1A_Checksum     	},
		{.start = 11,  .len =  4,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_Info_Prof1A_Counter        	},
		{.start = 27,  .len =  4,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_CarMode        				},
		{.start = 31,  .len =  4,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_UsageMode        			},
		{.start = 37,  .len =  2,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PowerModeFltFlag    	    	},
		{.start = 39,  .len =  2,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PowerMode        			},
		/*0x2A0 24*/
		{.start =  1,  .len =  2,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RRDoorSt        				},
		{.start =  3,  .len =  2,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RLDoorSt        				},
		{.start =  5,  .len =  2,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PassDoorSt        			},
		{.start =  7,  .len =  2,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_DrvrDoorSt        			},
		{.start =  9,  .len =  1,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_DrvrDoorLockSt3        		},
		{.start = 11,  .len =  2,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_DrvrDoorLockSt2        		},
		{.start = 15,  .len =  4,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_TailgateSt        			},
		{.start = 22,  .len =  7,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_FLWinOpenDeg        			},
		{.start = 30,  .len =  7,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_FRWinOpenDeg        			},
		{.start = 38,  .len =  7,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RLWinOpenDeg        			},
		{.start = 46,  .len =  7,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RRWinOpenDeg        			},
		{.start = 55,  .len =  8,  .FrameId = COM_RX_PDUID_2A0,	.integer =   FALSE, .unsign = TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.5,     .offset = -40       , .pVal = &Com_VDC_AmbT        					},
		{.start = 61,  .len =  1,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_DrvrDoorLockStVld        	},
		{.start = 63,  .len =  2,  .FrameId = COM_RX_PDUID_2A0,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_DrvrDoorLockSt        	},

		/*0x3AE 38*/
		{.start =  6,  .len = 13,  .FrameId = COM_RX_PDUID_3AE,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05625, .offset =   0       , .pVal = &Com_IPB_VehicleSpeed        			},
		{.start =  7,  .len =  1,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_IPB_VehicleSpeedValid        	},
		{.start =  9,  .len =  1,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_brakePedalSts        		},
		{.start = 35,  .len =  2,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_actualGear        			},
		{.start = 23,  .len = 20,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_TotalRang        			},
		{.start = 48,  .len =  1,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_actualGearValid        		},

		/*0x3AF 42*/
		{.start =  7,  .len = 14,  .FrameId = COM_RX_PDUID_3AF,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.01,    .offset =  -49.05    , .pVal = &Com_ABM_IMU_LongAcceleration        	},
		{.start =  9,  .len = 14,  .FrameId = COM_RX_PDUID_3AF,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.01,    .offset =  -49.05    , .pVal = &Com_ABM_IMU_LateralAcceleration      },
		{.start = 27,  .len = 16,  .FrameId = COM_RX_PDUID_3AF,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.01,    .offset =  -300     , .pVal = &Com_ABM_IMU_YawRate        			},
		/*0x3AA 45*/
		{.start =  1,  .len =  3,  .FrameId = COM_RX_PDUID_3AA,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_OpenSpdSet        			},
		{.start =  4,  .len =  3,  .FrameId = COM_RX_PDUID_3AA,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_FullOpenDegSet        		},
		{.start =  7,  .len =  3,  .FrameId = COM_RX_PDUID_3AA,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_ModSet        				},
		{.start = 11,  .len =  4,  .FrameId = COM_RX_PDUID_3AA,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_PDMFL_Ctrl        			},
		{.start = 14,  .len =  3,  .FrameId = COM_RX_PDUID_3AA,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_HndFeelSet        			},
		/*0x43F 50*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU0_SourceNodeIdentifier        			},
		{.start =  8,  .len =  1,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU0_RepeatMessageRequestBit        			},
		{.start = 12,  .len =  1,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU0_ActiveWakeupBit        			},
		{.start = 16,  .len =  1,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU0_RepeatSts        			},


		/*Tx*/
		/*0x5C3*/
		{.start =  7,  .len = 8,  .FrameId = COM_TX_PDUID_5C3, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FL_TotalFaultNum          			},
		{.start = 12,  .len = 5,  .FrameId = COM_TX_PDUID_5C3, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FL_FrameIndex          			},
		{.start = 15,  .len = 3,  .FrameId = COM_TX_PDUID_5C3, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FL_SupplierNum          			},
		{.start = 23,  .len =12,  .FrameId = COM_TX_PDUID_5C3, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FL_FaultNum1          			},
		{.start = 27,  .len =12,  .FrameId = COM_TX_PDUID_5C3, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FL_FaultNum2          			},
		{.start = 47,  .len =12,  .FrameId = COM_TX_PDUID_5C3, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FL_FaultNum3          			},
		{.start = 51,  .len =12,  .FrameId = COM_TX_PDUID_5C3, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FL_FaultNum4          			},
		/*0x3B6*/
		{.start =  7,  .len = 12,  .FrameId = COM_TX_PDUID_3B6, .integer = FALSE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor =0.1,       .offset = -100      , .pVal = &Com_PDM_FL_SlopeX          			},
		{.start = 11,  .len = 12,  .FrameId = COM_TX_PDUID_3B6, .integer = FALSE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor =0.1,       .offset = -100      , .pVal = &Com_PDM_FL_SlopeY          			},
		{.start = 35,  .len =  2,  .FrameId = COM_TX_PDUID_3B6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_IMUSt          			},
		/*0x3A6*/
		{.start =  7,  .len =  8,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_Ag          				},
		{.start = 15,  .len =  8,  .FrameId = COM_TX_PDUID_3A6, .integer =  FALSE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	-128    , .pVal = &Com_PDM_FL_DoorOpeningAgrSpd         },
		{.start = 16,  .len =  1,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_AntiPlaySt          		},
		{.start = 17,  .len =  1,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_AntiPinchSt          		},
		{.start = 18,  .len =  1,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_NCODSt          			},
		{.start = 20,  .len =  2,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_FolwUpSt          		},
		{.start = 23,  .len =  3,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_MtnSt          			},
		{.start = 25,  .len =  2,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_LrnSt          			},
		{.start = 31,  .len =  2,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_SysFlt          			},
		{.start = 39,  .len =  8,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_SelfLrnMeclPosn          	},
		{.start = 41,  .len =  3,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_FullOpenDegSetFb          },
		{.start = 43,  .len =  2,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_MaxPosnLrnSt          	},
		{.start = 45,  .len =  2,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_ZeroPosnLrnSt          	},
		{.start = 47,  .len =  2,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_InstallPosnLrnSt          },
		{.start = 48,  .len =  1,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_OverTProtnSt          	},
		{.start = 51,  .len =  3,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_ModSetFb          		},
		{.start = 54,  .len =  3,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_OpenSpdSetFb          	},
		{.start = 58,  .len =  2,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_DRDDetnEna          		},
		{.start = 63,  .len =  5,  .FrameId = COM_TX_PDUID_3A6, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_FailReazon          		},

		/*0x471*/
		{.start =  7,  .len =  8,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_SourceNodeIdentifier          				},
		{.start =  8,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_RepeatMessageRequestBit          				},
		{.start = 12,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_ActiveWakeupBit          				},
		{.start = 16,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_RepeatSts          				},
		{.start = 21,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_NMReq_NM          				},
		{.start = 22,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_NMReq_Diag          				},
		{.start = 23,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_NMReq_Poweron          				},
		{.start = 29,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_NMReq_GyroWakeup          				},
		{.start = 53,  .len =  6,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FL_FirstWakeupReason          				},

		/*Invalid signal*/
		{.start = 0 , .len = 0 , .FrameId = Invalid_PDUID   , .integer = TRUE , .unsign = TRUE, .format = COM_SIG_INTEL,    .factor = 1,       .offset = 0              , .pVal = &u8InvalidSig                         },

};

#endif


#ifdef ECU_ADDRESS_PDM_FR

/*RX DRD_FR_St : 151*/
uint8 Com_DRD_FR_DoorOpenAg = 0;
float32 Com_DRD_FR_ObstclXDst = 0;
float32 Com_DRD_FR_ObstclYDst = 0;
float32 Com_DRD_FR_ObstclZDst = 0;
float32 Com_DRD_FR_ObstclSpd = 0;
uint8 Com_DRD_FR_Err = 0;
uint8 Com_DRD_FR_St = 0;
uint8 Com_DRD_FR_InstallPosnLrnSt = 0;
uint8 Com_DRD_FR_Req = 0;

/*RX TBOX_TimeInfo_5E2 : 5E2*/
uint16 Com_TBOX_TimeYear = 2000;
uint8 Com_TBOX_TimeMonth = 1;
uint8 Com_TBOX_TimeDay = 1;
uint8 Com_TBOX_TimeHour = 0;
uint8 Com_TBOX_TimeMinute = 0;
uint8 Com_TBOX_TimeSecond = 0;
uint8 Com_TBOX_TimeZone = 0;
uint8 Com_TBOX_TimeZoneNum = 0;
uint8 Com_TBOX_TimeFlag = 0;

/*RX VIU_Info_Prof1A : 1C2*/
uint8 Com_VIU_Info_Prof1A_Checksum = 0;
uint8 Com_VIU_Info_Prof1A_Counter = 0;
uint8 Com_VIU_CarMode = 14;
uint8 Com_VIU_UsageMode = 1;
uint8 Com_VIU_PowerModeFltFlag = 0;
uint8 Com_VIU_PowerMode = 0;

/*RX VIU1_0x2A1 : 2A1*/
uint8 Com_VIU_RRDoorSt = 0;
uint8 Com_VIU_RLDoorSt = 0;
uint8 Com_VIU_PassDoorSt = 0;
uint8 Com_VIU_DrvrDoorSt = 0;
uint8 Com_VIU_PassDoorLockSt3 = 0;
uint8 Com_VIU_PassDoorLockSt2 = 0;
uint8 Com_VIU_TailgateSt = 0;
uint8 Com_VIU_FLWinOpenDeg = 0;
uint8 Com_VIU_FRWinOpenDeg = 0;
uint8 Com_VIU_RLWinOpenDeg = 0;
uint8 Com_VIU_RRWinOpenDeg = 0;
float32 Com_VDC_AmbT = 0;
uint8 Com_VIU_PassDoorLockSt = 0;

/*RX VIU1_0x3AE : 3AE*/
uint8 Com_IPB_VehicleSpeedValid = 0;
uint8 Com_VDC_brakePedalSts = 0;
float32 Com_IPB_VehicleSpeed = 0;
uint32 Com_VDC_TotalRang = 0;
uint8 Com_VDC_actualGear = 0;
uint8 Com_VDC_actualGearValid = 0;

/*RX VIU1_0x3AF : 3AF*/
float32 Com_ABM_IMU_LongAcceleration = 0;
float32 Com_ABM_IMU_LateralAcceleration = 0;
float32 Com_ABM_IMU_YawRate = 0;

/*RX VIU1_CDC_0x3AB : 3AB*/
uint8 Com_CDC_OpenSpdSet = 0;
uint8 Com_CDC_FullOpenDegSet = 0;
uint8 Com_CDC_ModSet = 0;
uint8 Com_CDC_PDMFR_Ctrl = 0;
uint8 Com_CDC_HndFeelSet = 0;
uint8 Com_VIU_PassSeatOccptSt = 0;

/*RX NM_Autosar_VIU1_0x449 : 449*/
uint8 Com_VIU1_SourceNodeIdentifier = 0;
uint8 Com_VIU1_RepeatMessageRequestBit = 0;
uint8 Com_VIU1_ActiveWakeupBit = 0;
uint8 Com_VIU1_RepeatSts = 0;

/*TX PDM_FR_Fault_0x5CB : 5CB*/
uint8 Com_PDM_FR_TotalFaultNum = 0;
uint8 Com_PDM_FR_FrameIndex = 0;
uint8 Com_PDM_FR_SupplierNum = 0;
uint16 Com_PDM_FR_FaultNum1 = 0;
uint16 Com_PDM_FR_FaultNum2 = 0;
uint16 Com_PDM_FR_FaultNum3 = 0;
uint16 Com_PDM_FR_FaultNum4 = 0;

/*TX PDM_FR_IMUSt_0x3B7 : 3B7*/
float32 Com_PDM_FR_SlopeX = 0;
float32 Com_PDM_FR_SlopeY = 0;
uint8 	Com_PDM_FR_IMUSt = 0;

/*TX PDM_FR_St_0x3A7 : 3A7*/
uint8 Com_PDM_FR_Ag = 86;
float32 Com_PDM_FR_DoorOpeningAgrSpd = 0;
uint8 Com_PDM_FR_AntiPlaySt = 0;
uint8 Com_PDM_FR_AntiPinchSt = 0;
uint8 Com_PDM_FR_NCODSt = 0;
uint8 Com_PDM_FR_FolwUpSt = 0;
uint8 Com_PDM_FR_MtnSt = 0;
uint8 Com_PDM_FR_LrnSt = 0;
uint8 Com_PDM_FR_SysFlt = 0;
uint8 Com_PDM_FR_SelfLrnMeclPosn = 0;
uint8 Com_PDM_FR_MaxPosnLrnSt = 0;
uint8 Com_PDM_FR_ZeroPosnLrnSt = 0;
uint8 Com_PDM_FR_InstallPosnLrnSt = 0;
uint8 Com_PDM_FR_OverTProtnSt = 0;
uint8 Com_PDM_FR_ModSetFb = 0;
uint8 Com_PDM_FR_OpenSpdSetFb = 0;
uint8 Com_PDM_FR_FullOpenDegSetFb = 0;
uint8 Com_PDM_FR_DRDDetnEna = 0;
uint8 Com_PDM_FR_FailReazon = 0;

/*NM_Autosar_VIU1_0x472: 0x472*/
uint8 Com_PDM_FR_SourceNodeIdentifier = 0;
uint8 Com_PDM_FR_RepeatMessageRequestBit = 0;
uint8 Com_PDM_FR_ActiveWakeupBit = 0;
uint8 Com_PDM_FR_RepeatSts = 0;
uint8 Com_PDM_FR_NMReq_NM = 0;
uint8 Com_PDM_FR_NMReq_Diag = 0;
uint8 Com_PDM_FR_NMReq_Poweron = 0;
uint8 Com_PDM_FR_NMReq_GyroWakeup = 0;
uint8 Com_PDM_FR_FirstWakeupReason = 0;



/*Invalid signal*/
const uint8_t u8InvalidSigInitVal = 0;
uint8_t u8InvalidSig = 0;

const ComSigType comSigs[] =
{
		/*Rx*/
		/*0x151 0*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_151,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FR_DoorOpenAg        		},
		{.start = 15,  .len =  8,  .FrameId = COM_RX_PDUID_151,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05,    .offset =   0       , .pVal = &Com_DRD_FR_ObstclXDst        		},
		{.start = 23,  .len =  8,  .FrameId = COM_RX_PDUID_151,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05,    .offset =   0       , .pVal = &Com_DRD_FR_ObstclYDst        		},
		{.start = 31,  .len =  8,  .FrameId = COM_RX_PDUID_151,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05,    .offset =   0       , .pVal = &Com_DRD_FR_ObstclZDst        		},
		{.start = 39,  .len =  8,  .FrameId = COM_RX_PDUID_151,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.03,    .offset =   0       , .pVal = &Com_DRD_FR_ObstclSpd        			},
		{.start = 43,  .len =  4,  .FrameId = COM_RX_PDUID_151,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FR_Err        				},
		{.start = 47,  .len =  4,  .FrameId = COM_RX_PDUID_151,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FR_St        				},
		{.start = 54,  .len =  2,  .FrameId = COM_RX_PDUID_151,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FR_InstallPosnLrnSt        	},
		{.start = 55,  .len =  1,  .FrameId = COM_RX_PDUID_151,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_DRD_FR_Req        				},
		/*0x5E2 9*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset = 2000       , .pVal = &Com_TBOX_TimeYear        		},
		{.start = 11,  .len =  4,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeMonth        		},
		{.start = 20,  .len =  5,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeDay        		},
		{.start = 28,  .len =  5,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeHour        		},
		{.start = 37,  .len =  6,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeMinute        		},
		{.start = 45,  .len =  6,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeSecond        		},
		{.start = 49,  .len =  2,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeZone        		},
		{.start = 54,  .len =  5,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeZoneNum        		},
		{.start = 57,  .len =  2,  .FrameId = COM_RX_PDUID_5E2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_TBOX_TimeFlag        		},
		/*0x1C2 18*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_1C2, .integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_Info_Prof1A_Checksum     	},
		{.start = 11,  .len =  4,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_Info_Prof1A_Counter        	},
		{.start = 27,  .len =  4,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_CarMode        				},
		{.start = 31,  .len =  4,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_UsageMode        			},
		{.start = 37,  .len =  2,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PowerModeFltFlag    	    	},
		{.start = 39,  .len =  2,  .FrameId = COM_RX_PDUID_1C2,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PowerMode        			},
		/*0x2A0 24*/
		{.start =  1,  .len =  2,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RRDoorSt        				},
		{.start =  3,  .len =  2,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RLDoorSt        				},
		{.start =  5,  .len =  2,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PassDoorSt        			},
		{.start =  7,  .len =  2,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_DrvrDoorSt        			},
		{.start =  9,  .len =  1,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PassDoorLockSt3        		},
		{.start = 11,  .len =  2,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PassDoorLockSt2        		},
		{.start = 15,  .len =  4,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_TailgateSt        			},
		{.start = 22,  .len =  7,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_FLWinOpenDeg        			},
		{.start = 30,  .len =  7,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_FRWinOpenDeg        			},
		{.start = 38,  .len =  7,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RLWinOpenDeg        			},
		{.start = 46,  .len =  7,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_RRWinOpenDeg        			},
		{.start = 55,  .len =  8,  .FrameId = COM_RX_PDUID_2A1,	.integer =   FALSE, .unsign = TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.5,     .offset = -40       , .pVal = &Com_VDC_AmbT        					},
		{.start = 63,  .len =  2,  .FrameId = COM_RX_PDUID_2A1,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PassDoorLockSt        	},
		/*0x3AE 37*/
		{.start =  6,  .len = 13,  .FrameId = COM_RX_PDUID_3AE,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.05625, .offset =   0       , .pVal = &Com_IPB_VehicleSpeed        			},
		{.start =  7,  .len =  1,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_IPB_VehicleSpeedValid        	},
		{.start =  9,  .len =  1,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_brakePedalSts        		},
		{.start = 35,  .len =  2,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_actualGear        			},
		{.start = 23,  .len = 20,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_TotalRang        			},
		{.start = 48,  .len =  1,  .FrameId = COM_RX_PDUID_3AE,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VDC_actualGearValid        			},
		/*0x3AF 41*/
		{.start = 7,  .len = 14,  .FrameId = COM_RX_PDUID_3AF,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.01,    .offset =  -49.05    , .pVal = &Com_ABM_IMU_LongAcceleration        	},
		{.start = 9,  .len = 14,  .FrameId = COM_RX_PDUID_3AF,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.01,    .offset =  -49.05    , .pVal = &Com_ABM_IMU_LateralAcceleration      },
		{.start = 27,  .len = 16,  .FrameId = COM_RX_PDUID_3AF,	.integer =   FALSE,.unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  0.01,    .offset =  -300     , .pVal = &Com_ABM_IMU_YawRate        			},
		/*0x3AB 44*/
		{.start =  1,  .len =  3,  .FrameId = COM_RX_PDUID_3AB,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_OpenSpdSet       			},
		{.start =  4,  .len =  3,  .FrameId = COM_RX_PDUID_3AB,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_FullOpenDegSet      		},
		{.start =  7,  .len =  3,  .FrameId = COM_RX_PDUID_3AB,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_ModSet 				},
		{.start = 11,  .len =  4,  .FrameId = COM_RX_PDUID_3AB,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_PDMFR_Ctrl    			},
		{.start = 14,  .len =  3,  .FrameId = COM_RX_PDUID_3AB,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_CDC_HndFeelSet 			},
		{.start = 17,  .len =  2,  .FrameId = COM_RX_PDUID_3AB,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU_PassSeatOccptSt        		},

		/*0x449 50*/
		{.start =  7,  .len =  8,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU1_SourceNodeIdentifier        			},
		{.start =  8,  .len =  1,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU1_RepeatMessageRequestBit        			},
		{.start = 12,  .len =  1,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU1_ActiveWakeupBit        			},
		{.start = 16,  .len =  1,  .FrameId = COM_RX_PDUID_NM,	.integer =   TRUE, .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =   0       , .pVal = &Com_VIU1_RepeatSts        			},

		/*Tx*/
		/*0x5CB*/
		{.start =  7,  .len = 8,  .FrameId = COM_TX_PDUID_5CB, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FR_TotalFaultNum          		},
		{.start = 12,  .len = 5,  .FrameId = COM_TX_PDUID_5CB, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FR_FrameIndex          			},
		{.start = 15,  .len = 3,  .FrameId = COM_TX_PDUID_5CB, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FR_SupplierNum          			},
		{.start = 23,  .len =12,  .FrameId = COM_TX_PDUID_5CB, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FR_FaultNum1          			},
		{.start = 27,  .len =12,  .FrameId = COM_TX_PDUID_5CB, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FR_FaultNum2          			},
		{.start = 47,  .len =12,  .FrameId = COM_TX_PDUID_5CB, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FR_FaultNum3          			},
		{.start = 51,  .len =12,  .FrameId = COM_TX_PDUID_5CB, .integer = TRUE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor = 1,       .offset = 0      , .pVal = &Com_PDM_FR_FaultNum4          			},

		/*0x3B7*/
		{.start =  7,  .len = 12,  .FrameId = COM_TX_PDUID_3B7, .integer = FALSE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor =0.1,       .offset = -100      , .pVal = &Com_PDM_FR_SlopeX          			},
		{.start = 11,  .len = 12,  .FrameId = COM_TX_PDUID_3B7, .integer = FALSE , .unsign = TRUE,  .format = COM_SIG_MOTOROLA,	.factor =0.1,       .offset = -100      , .pVal = &Com_PDM_FR_SlopeY          			},
		{.start = 35,  .len =  2,  .FrameId = COM_TX_PDUID_3B7, .integer =  TRUE , .unsign = TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_IMUSt          			},

		/*0x3A6*/
		{.start =  7,  .len =  8,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_Ag          				},
		{.start = 15,  .len =  8,  .FrameId = COM_TX_PDUID_3A7, .integer =  FALSE , .unsign = TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	-128    , .pVal = &Com_PDM_FR_DoorOpeningAgrSpd         },
		{.start = 16,  .len =  1,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_AntiPlaySt          		},
		{.start = 17,  .len =  1,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_AntiPinchSt          		},
		{.start = 18,  .len =  1,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_NCODSt          			},
		{.start = 20,  .len =  2,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_FolwUpSt          		},
		{.start = 23,  .len =  3,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_MtnSt          			},
		{.start = 25,  .len =  2,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_LrnSt          			},
		{.start = 31,  .len =  2,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_SysFlt          			},
		{.start = 39,  .len =  8,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_SelfLrnMeclPosn          	},
		{.start = 41,  .len =  3,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_FullOpenDegSetFb          },
		{.start = 43,  .len =  2,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_MaxPosnLrnSt          	},
		{.start = 45,  .len =  2,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_ZeroPosnLrnSt          	},
		{.start = 47,  .len =  2,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_InstallPosnLrnSt          },
		{.start = 48,  .len =  1,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_OverTProtnSt          	},
		{.start = 51,  .len =  3,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_ModSetFb          		},
		{.start = 54,  .len =  3,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_OpenSpdSetFb          	},
		{.start = 58,  .len =  2,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_DRDDetnEna          		},
		{.start = 63,  .len =  5,  .FrameId = COM_TX_PDUID_3A7, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_FailReazon          		},

		/*0x472*/
		{.start =  7,  .len =  8,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_SourceNodeIdentifier          				},
		{.start =  8,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_RepeatMessageRequestBit          				},
		{.start = 12,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_ActiveWakeupBit          				},
		{.start = 16,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_RepeatSts          				},
		{.start = 21,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_NMReq_NM          				},
		{.start = 22,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_NMReq_Diag          				},
		{.start = 23,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_NMReq_Poweron          				},
		{.start = 29,  .len =  1,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_NMReq_GyroWakeup          				},
		{.start = 53,  .len =  6,  .FrameId = COM_TX_PDUID_NM, .integer =  TRUE , .unsign =  TRUE, .format = COM_SIG_MOTOROLA,	.factor =  1,       .offset =	0       , .pVal = &Com_PDM_FR_FirstWakeupReason          				},

		/*Invalid signal*/
		{.start = 0 , .len = 0 , .FrameId = Invalid_PDUID   , .integer = TRUE , .unsign = TRUE, .format = COM_SIG_INTEL,    .factor = 1,       .offset = 0              , .pVal = &u8InvalidSig                         },

};



#endif





#define COM_SIGNALS_CNT (sizeof(comSigs)/sizeof(comSigs[0]))

uint16 getCom_SIGNALS_CNT(void)
{
	return COM_SIGNALS_CNT;
}
