#include "rte.h"
#include "Com_cfg.h"
#include "BspCan.h"
#ifndef ECU_ADDRESS_BLDC
#include "uds_srv.h"
#include "NvM.h"


uint32_t ProgrammingReqAdrr = 0x20017C00UL;

//volatile uint32_t ProgrammingReqAdrr __attribute__((section(".ram_exchange"))) ;

/* *****************************************************************************
 * @brief  Set programming request flag
 *
 * @param  None
 * @return None
 * @note
 ***************************************************************************** */

void Rte_SetProgrammingReq(uint8_t SuppressPosRsp)
{
	if(0 == SuppressPosRsp)
	{
		 *(uint32_t*)ProgrammingReqAdrr = 0x55555555UL;
	}
	else
	{
		 *(uint32_t*)ProgrammingReqAdrr = 0xAAAAAAAAUL;
	}
   // *(uint32_t*)ProgrammingReqAdrr = 0x55555555UL;
}



/* *****************************************************************************
 * @brief   OTA  mode initialization
 *
 * @param  None
 * @retval None
 * @note
***************************************************************************** */
//OTA
uint8_t  Rte_OTA_Mode  = FALSE;
static uint16_t  usermodecnt = 0x0,usermodecnt1 = 0x0,diag3Ecnt = 0x0;
static uint8_t   usermodecursts , usermoeprests,OTAModeflg = FALSE,OTAModeflg1 = FALSE;
extern uint8_t NVM_MirrorBlockDataId_OTAModestatus[8];
extern uint8 g_ui83ERequstFlag;

/* *****************************************************************************
 * @brief  Get OTA mode
 *
 * @param  None
 * @retval OTA mode
 * @note
***************************************************************************** */
uint8_t Rte_GetOTA_Mode(void)
{
  return Rte_OTA_Mode;
}


/* *****************************************************************************
 * @brief  Enter OTA mode
 *
 * @param  None
 * @retval None
 * @note
***************************************************************************** */
void Rte_EnterOTA_Mode(void)
{
  Rte_OTA_Mode = ENTER_OTA_MODE;
  NVM_MirrorBlockDataId_OTAModestatus[0] = ENTER_OTA_MODE;
  OTA_WriteOTAFlagToNvm();
}



void OTA_WriteOTAFlagToNvm(void)
{
	if(NVM_IDLE == NVM_GetStatus())
	{
		while(NVM_OK == NVM_WriteBlockData(OTAModestatus_NVM_BLOCK_ID))
		{
			return ;
		}
	}
}




/* *****************************************************************************
 * @brief  Exit OTA mode
 *
 * @param  None
 * @retval None
 * @note
***************************************************************************** */
void Rte_ExitOTA_Mode(void)
{
  Rte_OTA_Mode = EXIT_OTA_MODE;
  NVM_MirrorBlockDataId_OTAModestatus[0] = EXIT_OTA_MODE;
  OTA_WriteOTAFlagToNvm();
}

void Rte_OTAModeInit(void)
{

  if(NVM_MirrorBlockDataId_OTAModestatus[0] == 0x55)
  {
	  Rte_EnterOTA_Mode();
	  OTAModeflg = TRUE;
      usermodecnt = 0x0;
      diag3Ecnt = 0x0;
      usermodecnt1 = 0x0;
  }
  else
  {
	  Rte_ExitOTA_Mode();
	  OTAModeflg = FALSE;
	  usermodecnt = 0x0;
	  diag3Ecnt = 0x0;
	  usermodecnt1 = 0x0;
  }

}

/* *****************************************************************************
 * @brief  Update OTA  mode
 *
 * @param  None
 * @retval None
 * @note
***************************************************************************** */

uint8_t GetUsageMode(void)
{
   uint8_t  temp;

   temp = Com_VIU_UsageMode;

   return  temp;
}
void Rte_UpdateOTAMode(void)   //5ms
{
   uint8 l_ui8ProNo3E = 0;
   usermodecursts = GetUsageMode();
   if(usermodecursts != usermoeprests)
   {
	   usermoeprests = usermodecursts;
       if(usermoeprests == 0x4)    //ֻ�дӷ�OTA���OTAʱ���ŻὫOTAģʽ�ı�־λ��λ
       {
    	   Rte_EnterOTA_Mode();
    	   OTAModeflg = TRUE;
    	   usermodecnt = 0x0;
    	   diag3Ecnt = 0x0;
    	   usermodecnt1 = 0x0;
       }
   }
   if(OTAModeflg == TRUE)  //Ϊ�治�����յ����ź�ΪOTA
   {

	  if( Dcm_Srv_GetPresentSession() == 0x03U)
	  {
		  if(diag3Ecnt < 400)//�������յ�3E�Ļ�����ʼ�����Ӽ�ʱ|���������û�н��յ�3E,�������������ӳ�ʱ�߼�����OTA�����Ƿ���յ�3E
		  {
			  diag3Ecnt++;
			  if(g_ui83ERequstFlag)
			  {
				  OTAModeflg1 = TRUE;
				  g_ui83ERequstFlag = 0;
			  }

		  }
		  else   //���2s��û�н��յ�3E����ͬĬ�ϻỰ����ʱ������
		  {
			  l_ui8ProNo3E = 1;
			  usermodecnt1 = 400;
		  }
		  if((OTAModeflg1 == TRUE)||(1 == l_ui8ProNo3E))//�������ڽ��յ�3E���ִ�������߼�
		  {
			  if(usermodecnt1 < 24000)  //��ѯ�������ڽ������
			  {
				  usermodecnt1++;
				  if(((!g_ui83ERequstFlag)&&(usermodecnt1!=1))||(1 == l_ui8ProNo3E))
				  {
					  if(GetUsageMode() == 0x4)
					  {
						  usermodecnt1 = 0;
						  g_ui83ERequstFlag = 0;
					  }
					  else if(GetUsageMode()!=0xF)
					  {
						  Rte_ExitOTA_Mode();
						  OTAModeflg = FALSE;
						  OTAModeflg1 = FALSE;
						  usermodecnt1 = 0x0;
						  return;
					  }
				  }
				  else   //������ֽ��յ���3E����������û�н��յ�3E
				  {
					  usermodecnt1 = 0;
					  g_ui83ERequstFlag = 0;
				  }
			  }
			  else
			  {
				  Rte_ExitOTA_Mode();
				  OTAModeflg = FALSE;
				  OTAModeflg1 = FALSE;
				  usermodecnt1 = 0x0;
				  return;
			  }
//			   if(usermodecnt1 >= 120)
//			   {
//
//				   if((GetUsageMode() != 0x4)||(Apdu.ReqData[0] != 0x3E))
//				   {
//					   Rte_ExitOTA_Mode();
//					   OTAModeflg = FALSE;
//					   OTAModeflg1 = FALSE;
//					   usermodecnt1 = 0x0;
//				   }
//
//			   }
//			   else
//			   {
//				   usermodecnt1++;
//			   }

		  }

	  }
	  else
	  {
		  if(usermodecnt < 24000)
		  {
			  usermodecnt++;
			  if(GetUsageMode() == 0x4)
			  {
				  usermodecnt = 0;
			  }
			  else if(GetUsageMode() != 0xF)
			  {
				  Rte_ExitOTA_Mode();
			      OTAModeflg = FALSE;
			      usermodecnt = 0x0;
			  }
		  }
		  else
		  {
			   Rte_ExitOTA_Mode();
			   OTAModeflg = FALSE;
			   usermodecnt = 0x0;
		  }
//		   if(usermodecnt >= 120)
//		   {
//			   if(GetUsageMode() != 0x4)//||(NoREC0x12Cmsgflg == TRUE))
//			   {
//
//				   Rte_ExitOTA_Mode();
//				   OTAModeflg = FALSE;
//				   usermodecnt = 0x0;
//			   }
//		   }
//		   else
//		   {
//			   usermodecnt++;
//		   }
	  }

   }

}





#ifdef ECU_ADDRESS_PDM_FL
/*TimeOut API*/

bool RTE_Read_CheckTimeOut_DRD_FL_St_0x150(void)
{
	if(E_OK == Can_CheckTimeOut_DRD_FL_St_0x150())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_TBOX_TimeInfo_0x5E2(void)
{
	if(E_OK == Can_CheckTimeOut_TBOX_TimeInfo_0x5E2())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_TVIU_Info_Prof1A_0x1C2(void)
{
	if(E_OK == Can_CheckTimeOut_TVIU_Info_Prof1A_0x1C2())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU0_0x2A0(void)
{
	if(E_OK == Can_CheckTimeOut_VIU0_0x2A0())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU0_0x3AE(void)
{
	if(E_OK == Can_CheckTimeOut_VIU0_0x3AE())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU0_0x3AF(void)
{
	if(E_OK == Can_CheckTimeOut_VIU0_0x3AF())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU0_CDC_0x3AA(void)
{
	if(E_OK == Can_CheckTimeOut_VIU0_CDC_0x3AA())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/*TimeOut API*/


/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_DoorOpenAg(uint8 * pData)//0x150
{
	if(Com_DRD_FL_DoorOpenAg <= 100)
	{
		*pData = Com_DRD_FL_DoorOpenAg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclXDst(float32 * pData)//0x150
{
	if(Com_DRD_FL_ObstclXDst <= 12.75)
	{
		*pData = Com_DRD_FL_ObstclXDst;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclYDst(float32 * pData)//0x150
{
	if(Com_DRD_FL_ObstclYDst <= 12.75)
	{
		*pData = Com_DRD_FL_ObstclYDst;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclZDst(float32 * pData)//0x150
{
	if(Com_DRD_FL_ObstclZDst <= 12.75)
	{
		*pData = Com_DRD_FL_ObstclZDst;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_ObstclSpd(float32 * pData)//0x150
{
	if(Com_DRD_FL_ObstclSpd <= 7.65)
	{
		*pData = Com_DRD_FL_ObstclSpd;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_St(uint8 * pData)//0x150
{
	if(Com_DRD_FL_St <= 15)
	{
		*pData = Com_DRD_FL_St;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_Err(uint8 * pData)//0x150
{
	if(Com_DRD_FL_Err <= 15)
	{
		*pData = Com_DRD_FL_Err;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_Req(uint8 * pData)//0x150
{
	if(Com_DRD_FL_Req <= 1)
	{
		*pData = Com_DRD_FL_Req;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FL_InstallPosnLrnSt(uint8 * pData)//0x150
{
	if(Com_DRD_FL_InstallPosnLrnSt <= 3)
	{
		*pData = Com_DRD_FL_InstallPosnLrnSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Checksum(uint8 * pData)//0x1C2
{
	*pData = Com_VIU_Info_Prof1A_Checksum;
	return E_OK;
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Counter(uint8 * pData)//0x1C2
{
	if(Com_VIU_Info_Prof1A_Counter <= 14)
	{
		*pData = Com_VIU_Info_Prof1A_Counter;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_UsageMode(uint8 * pData)//0x1C2
{
	if(Com_VIU_UsageMode <= 15)
	{
		*pData = Com_VIU_UsageMode;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_CarMode(uint8 * pData)//0x1C2
{
	if(Com_VIU_CarMode <= 15)
	{
		*pData = Com_VIU_CarMode;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PowerMode(uint8 * pData)//0x1C2
{
	if(Com_VIU_PowerMode <= 3)
	{
		*pData = Com_VIU_PowerMode;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PowerModeFltFlag(uint8 * pData)//0x1C2
{
	if(Com_VIU_PowerModeFltFlag <= 3)
	{
		*pData = Com_VIU_PowerModeFltFlag;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_DrvrDoorSt <= 3)
	{
		*pData = Com_VIU_DrvrDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PassDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_PassDoorSt <= 3)
	{
		*pData = Com_VIU_PassDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RLDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_RLDoorSt <= 3)
	{
		*pData = Com_VIU_RLDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RRDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_RRDoorSt <= 3)
	{
		*pData = Com_VIU_RRDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_TailgateSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_TailgateSt <= 15)
	{
		*pData = Com_VIU_TailgateSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockSt2(uint8 * pData) //0x2A0
{
	if(Com_VIU_DrvrDoorLockSt2 <= 3)
	{
		*pData = Com_VIU_DrvrDoorLockSt2;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockSt3(uint8 * pData) //0x2A0
{
	if(Com_VIU_DrvrDoorLockSt3 <= 1)
	{
		*pData = Com_VIU_DrvrDoorLockSt3;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_FLWinOpenDeg(uint8 * pData)//0x2A0
{
	if(Com_VIU_FLWinOpenDeg <= 127)
	{
		*pData = Com_VIU_FLWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_FRWinOpenDeg(uint8 * pData)//0x2A0
{
	if(Com_VIU_FRWinOpenDeg <= 127)
	{
		*pData = Com_VIU_FRWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RLWinOpenDeg(uint8 * pData)//0x2A0
{
	if(Com_VIU_RLWinOpenDeg <= 127)
	{
		*pData = Com_VIU_RLWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RRWinOpenDeg(uint8 * pData)//0x2A0
{
	if(Com_VIU_RRWinOpenDeg <= 127)
	{
		*pData = Com_VIU_RRWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_AmbT(float32 * pData)//0x2A0
{
	if((Com_VDC_AmbT <= 87)&&(Com_VDC_AmbT >= -40))
	{
		*pData = Com_VDC_AmbT;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockSt(uint8_t * pData)//0x2A0
{
	if(Com_VIU_DrvrDoorLockSt <= 3)
	{
		*pData = Com_VIU_DrvrDoorLockSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockStVld(uint8 * pData)//0x2A0
{
	if(Com_VIU_DrvrDoorLockStVld <= 1)
	{
		*pData = Com_VIU_DrvrDoorLockStVld;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_IPB_VehicleSpeedValid(uint8 * pData) //0x3AE
{
	if(Com_IPB_VehicleSpeedValid <= 1)
	{
		*pData = Com_IPB_VehicleSpeedValid;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_brakePedalSts(uint8 * pData)//0x3AE
{
	if(Com_VDC_brakePedalSts <= 1)
	{
		*pData = Com_VDC_brakePedalSts;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_IPB_VehicleSpeed(float32 * pData)//0x3AE
{
	if(Com_IPB_VehicleSpeed < 460.74375)
	{
		*pData = Com_IPB_VehicleSpeed;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_TotalRang(uint32 * pData)//0x3AE
{
	if(Com_VDC_TotalRang <= 1048575)
	{
		*pData = Com_VDC_TotalRang;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_VDC_actualGear
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_actualGear(uint8 * pData)//0x3AE
{
	if(Com_VDC_TotalRang <= 3)
	{
		*pData = Com_VDC_actualGear;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_VDC_actualGearValid
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_actualGearValid(uint8 * pData)//0x3AE
{
	if(Com_VDC_TotalRang <= 1)
	{
		*pData = Com_VDC_actualGearValid;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_ABM_IMU_LongAcceleration(float32 * pData) //0x3AF
{
	if((Com_ABM_IMU_LongAcceleration <= 114.78)&&(Com_ABM_IMU_LongAcceleration >= -49.05))
	{
		*pData = Com_ABM_IMU_LongAcceleration;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_ABM_IMU_LateralAcceleration(float32 * pData)//0x3AF
{
	if((Com_ABM_IMU_LateralAcceleration <= 114.78)&&(Com_ABM_IMU_LateralAcceleration >= -49.05))
	{
		*pData = Com_ABM_IMU_LateralAcceleration;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_ABM_IMU_YawRate(float32 * pData)//0x3AF
{
	if((Com_ABM_IMU_YawRate <= 355.35)&&(Com_ABM_IMU_YawRate >= -300))
	{
		*pData = Com_ABM_IMU_YawRate;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_ModSet(uint8 * pData) //0x3AA
{
	if(Com_CDC_ModSet <= 7)
	{
		*pData = Com_CDC_ModSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_FullOpenDegSet(uint8 * pData) //0x3AA
{
	if(Com_CDC_FullOpenDegSet <= 7)
	{
		*pData = Com_CDC_FullOpenDegSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_OpenSpdSet(uint8 * pData) //0x3AA
{
	if(Com_CDC_OpenSpdSet <= 7)
	{
		*pData = Com_CDC_OpenSpdSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_HndFeelSet(uint8 * pData) //0x3AA
{
	if(Com_CDC_HndFeelSet <= 7)
	{
		*pData = Com_CDC_HndFeelSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_PDMFL_Ctrl(uint8 * pData) //0x3AA
{
	if(Com_CDC_PDMFL_Ctrl <= 15)
	{
		*pData = Com_CDC_PDMFL_Ctrl;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_VIU0_SourceNodeIdentifier(uint8 * pData) //0x43F
{
	*pData = Com_VIU0_SourceNodeIdentifier;
	return E_OK;
}

Std_ReturnType RTE_Read_Com_VIU0_RepeatMessageRequestBit(uint8 * pData) //0x43F
{
	if(Com_VIU0_RepeatMessageRequestBit <= 1)
	{
		*pData = Com_VIU0_RepeatMessageRequestBit;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_VIU0_ActiveWakeupBit(uint8 * pData) //0x43F
{
	if(Com_VIU0_ActiveWakeupBit <= 1)
	{
		*pData = Com_VIU0_ActiveWakeupBit;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_VIU0_RepeatSts(uint8 * pData) //0x43F
{
	if(Com_VIU0_RepeatSts <= 1)
	{
		*pData = Com_VIU0_RepeatSts;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeYear(uint16 * pData) //0x5E2
{
	if((Com_TBOX_TimeYear <= 2255)&&(Com_TBOX_TimeYear >= 2000))
	{
		*pData = Com_TBOX_TimeYear;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeMonth(uint8 * pData) //0x5E2
{
	if((Com_TBOX_TimeMonth <= 12)&&(Com_TBOX_TimeMonth >= 1))
	{
		*pData = Com_TBOX_TimeMonth;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeDay(uint8 * pData) //0x5E2
{
	if((Com_TBOX_TimeDay <= 31)&&(Com_TBOX_TimeDay >= 1))
	{
		*pData = Com_TBOX_TimeDay;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeHour(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeHour <= 23)
	{
		*pData = Com_TBOX_TimeHour;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeMinute(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeMinute <= 59)
	{
		*pData = Com_TBOX_TimeMinute;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeSecond(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeSecond <= 59)
	{
		*pData = Com_TBOX_TimeSecond;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

//Std_ReturnType RTE_Read_Com_TBOX_TimeSecond(uint8 * pData) //0x5E2
//{
//	if(Com_TBOX_TimeSecond <= 59)
//	{
//		*pData = Com_TBOX_TimeSecond;
//		return E_OK;
//	}
//	else
//	{
//		return E_NOK;
//	}
//}

Std_ReturnType RTE_Read_Com_TBOX_TimeZone(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeZone <= 3)
	{
		*pData = Com_TBOX_TimeZone;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeZoneNum(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeZoneNum <= 31)
	{
		*pData = Com_TBOX_TimeZoneNum;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeFlag(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeFlag <= 3)
	{
		*pData = Com_TBOX_TimeFlag;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}




/*Tx*/
Std_ReturnType RTE_Write_Com_PDM_FL_IMUSt(uint8 data)//0x3B6
{
	if(data <= 3)
	{
		Com_PDM_FL_IMUSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrDoorMovingStatus
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_SlopeX (float32 data)//0x3B6
{
	if((data <= 100)&&(data >= -100))
	{
		Com_PDM_FL_SlopeX = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrPrimaryMotorPower
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_SlopeY (float32 data)//0x3B6
{
	if((data <= 100)&&(data >= -100))
	{
		Com_PDM_FL_SlopeY = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrPrimaryMotorDirection
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_Ag (uint8 data)//0x3A6
{
	Com_PDM_FL_Ag = data;
	return E_OK;
}


/**
 * @name :RTE_Write_Com_ISrPushDetected
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_AntiPinchSt (uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FL_AntiPinchSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_AntiPlaySt(uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FL_AntiPlaySt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrSlipDeviceActivState
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_DoorOpeningAgrSpd(float32 data)//0x3A6
{
	if((data <= 127)&&(data >= -128))
	{
		Com_PDM_FL_DoorOpeningAgrSpd = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Write_Com_ISrStatusDriveControl
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_DRDDetnEna(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FL_DRDDetnEna = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrStatusPositionAngle
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_FailReazon(uint8 data)//0x3A6
{
	if(data <= 31)
	{
		Com_PDM_FL_FailReazon = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_comTxNM_FrameID
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FL_FolwUpSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FL_FolwUpSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_FullOpenDegSetFb(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FL_FullOpenDegSetFb = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_InstallPosnLrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FL_InstallPosnLrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_LrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FL_LrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_MaxPosnLrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FL_MaxPosnLrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_ModSetFb(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FL_ModSetFb = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_MtnSt(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FL_MtnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_NCODSt(uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FL_NCODSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_PDM_FL_OpenSpdSetFb(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FL_OpenSpdSetFb = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_OverTProtnSt(uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FL_OverTProtnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_PDM_FL_SelfLrnMeclPosn(uint8 data)//0x3A6
{
	Com_PDM_FL_SelfLrnMeclPosn = data;
	return E_OK;
}

Std_ReturnType RTE_Write_Com_PDM_FL_SysFlt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FL_SysFlt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_ZeroPosnLrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FL_ZeroPosnLrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum1(uint16 data)//0x5C3
{
	if(data <= 4095)
	{
		Com_PDM_FL_FaultNum1 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}

}

Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum2(uint16 data)//0x5C3
{
	if(data <= 4095)
	{
		Com_PDM_FL_FaultNum2 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum3(uint16 data)//0x5C3
{
	if(data <= 4095)
	{
		Com_PDM_FL_FaultNum3 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum4(uint16 data)//0x5C3
{
	if(data <= 4095)
	{
		Com_PDM_FL_FaultNum4 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_FrameIndex(uint8 data)//0x5C3
{
	if(data <= 31)
	{
		Com_PDM_FL_FrameIndex = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_TotalFaultNum(uint8 data)//0x5C3
{
	Com_PDM_FL_TotalFaultNum = data;
	return E_OK;
}

Std_ReturnType RTE_Write_Com_PDM_FL_SupplierNum(uint8 data)//0x5C3
{
	if(data <= 7)
	{
		Com_PDM_FL_SupplierNum = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}

}


//Std_ReturnType RTE_Write_Com_PDM_FL_SourceNodeIdentifier(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxNM_FrameID(uint8 data)//0x471
{
	Com_PDM_FL_SourceNodeIdentifier = data;
	return E_OK;
}

//Std_ReturnType RTE_Write_Com_PDM_FL_RepeatMessageRequestBit(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxRepMessage_State(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FL_RepeatMessageRequestBit = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

//Std_ReturnType RTE_Write_Com_PDM_FL_ActiveWakeupBit(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxActiveWakeup(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FL_ActiveWakeupBit = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

//Std_ReturnType RTE_Write_Com_PDM_FL_RepeatSts(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxRepeatState(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FL_RepeatSts = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_NM(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FL_NMReq_NM = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_Diag(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FL_NMReq_Diag = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_Poweron(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FL_NMReq_Poweron = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_NMReq_GyroWakeup(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FL_NMReq_GyroWakeup = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_FirstWakeupReason(uint8 data)//0x471
{
	if(data <= 63)
	{
		Com_PDM_FL_FirstWakeupReason = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

#endif


#ifdef ECU_ADDRESS_PDM_FR

/*TimeOut API*/

bool RTE_Read_CheckTimeOut_DRD_FR_St_0x151(void)
{
	if(E_OK == Can_CheckTimeOut_DRD_FR_St_0x151())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_TBOX_TimeInfo_0x5E2(void)
{
	if(E_OK == Can_CheckTimeOut_TBOX_TimeInfo_0x5E2())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU_Info_Prof1A_0x1C2(void)
{
	if(E_OK == Can_CheckTimeOut_VIU_Info_Prof1A_0x1C2())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_TBOX_VIU_0x2A1(void)
{
	if(E_OK == Can_CheckTimeOut_VIU_0x2A1())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU1_0x3AE(void)
{
	if(E_OK == Can_CheckTimeOut_VIU1_0x3AE())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU1_0x3AF(void)
{
	if(E_OK == Can_CheckTimeOut_VIU1_0x3AF())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool RTE_Read_CheckTimeOut_VIU1_CDC_0x3AB(void)
{
	if(E_OK == Can_CheckTimeOut_VIU1_CDC_0x3AB())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/*TimeOut API*/




/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_DoorOpenAg(uint8 * pData)//0x151
{
	if(Com_DRD_FR_DoorOpenAg <= 100)
	{
		*pData = Com_DRD_FR_DoorOpenAg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclXDst(float32 * pData)//0x151
{
	if(Com_DRD_FR_ObstclXDst <= 12.75)
	{
		*pData = Com_DRD_FR_ObstclXDst;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclYDst(float32 * pData)//0x151
{
	if(Com_DRD_FR_ObstclYDst <= 12.75)
	{
		*pData = Com_DRD_FR_ObstclYDst;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclZDst(float32 * pData)//0x151
{
	if(Com_DRD_FR_ObstclZDst <= 12.75)
	{
		*pData = Com_DRD_FR_ObstclZDst;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_ObstclSpd(float32 * pData)//0x151
{
	if(Com_DRD_FR_ObstclSpd <= 7.65)
	{
		*pData = Com_DRD_FR_ObstclSpd;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_St(uint8 * pData)//0x151
{
	if(Com_DRD_FR_St <= 15)
	{
		*pData = Com_DRD_FR_St;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_Err(uint8 * pData)//0x151
{
	if(Com_DRD_FR_Err <= 15)
	{
		*pData = Com_DRD_FR_Err;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_Req(uint8 * pData)//0x151
{
	if(Com_DRD_FR_Req <= 1)
	{
		*pData = Com_DRD_FR_Req;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_DRD_FR_InstallPosnLrnSt(uint8 * pData)//0x151
{
	if(Com_DRD_FR_InstallPosnLrnSt <= 3)
	{
		*pData = Com_DRD_FR_InstallPosnLrnSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Checksum(uint8 * pData)//0x1C2
{
	*pData = Com_VIU_Info_Prof1A_Checksum;
	return E_OK;
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_Info_Prof1A_Counter(uint8 * pData)//0x1C2
{
	if(Com_VIU_Info_Prof1A_Counter <= 14)
	{
		*pData = Com_VIU_Info_Prof1A_Counter;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_UsageMode(uint8 * pData)//0x1C2
{
	if(Com_VIU_UsageMode <= 15)
	{
		*pData = Com_VIU_UsageMode;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_CarMode(uint8 * pData)//0x1C2
{
	if(Com_VIU_CarMode <= 15)
	{
		*pData = Com_VIU_CarMode;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PowerMode(uint8 * pData)//0x1C2
{
	if(Com_VIU_PowerMode <= 3)
	{
		*pData = Com_VIU_PowerMode;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PowerModeFltFlag(uint8 * pData)//0x1C2
{
	if(Com_VIU_PowerModeFltFlag <= 3)
	{
		*pData = Com_VIU_PowerModeFltFlag;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_DrvrDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_DrvrDoorSt <= 3)
	{
		*pData = Com_VIU_DrvrDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PassDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_PassDoorSt <= 3)
	{
		*pData = Com_VIU_PassDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RLDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_RLDoorSt <= 3)
	{
		*pData = Com_VIU_RLDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RRDoorSt(uint8 * pData) //0x2A0
{
	if(Com_VIU_RRDoorSt <= 3)
	{
		*pData = Com_VIU_RRDoorSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_TailgateSt(uint8 * pData) //0x2A1
{
	if(Com_VIU_TailgateSt <= 15)
	{
		*pData = Com_VIU_TailgateSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PassDoorLockSt2(uint8 * pData) //0x2A1
{
	if(Com_VIU_PassDoorLockSt2 <= 3)
	{
		*pData = Com_VIU_PassDoorLockSt2;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PassDoorLockSt3(uint8 * pData) //0x2A1
{
	if(Com_VIU_PassDoorLockSt3 <= 1)
	{
		*pData = Com_VIU_PassDoorLockSt3;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_FRWinOpenDeg(uint8 * pData)//0x2A1
{
	if(Com_VIU_FRWinOpenDeg <= 127)
	{
		*pData = Com_VIU_FRWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_VIU_FLWinOpenDeg(uint8 * pData)//0x2A1
{
	if(Com_VIU_FLWinOpenDeg <= 127)
	{
		*pData = Com_VIU_FLWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RLWinOpenDeg(uint8 * pData)//0x2A1
{
	if(Com_VIU_RLWinOpenDeg <= 127)
	{
		*pData = Com_VIU_RLWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_RRWinOpenDeg(uint8 * pData)//0x2A1
{
	if(Com_VIU_RRWinOpenDeg <= 127)
	{
		*pData = Com_VIU_RRWinOpenDeg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_AmbT(float32 * pData)//0x2A1
{
	if((Com_VDC_AmbT <= 87)&&(Com_VDC_AmbT >= -40))
	{
		*pData = Com_VDC_AmbT;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VIU_PassDoorLockSt(uint8_t * pData)//0x2A1
{
	if(Com_VIU_PassDoorLockSt <= 3)
	{
		*pData = Com_VIU_PassDoorLockSt;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
//Std_ReturnType RTE_Read_Com_VIU_DrvrDoorLockStVld(uint8 * pData)//0x2A1
//{
//	if(Com_VIU_DrvrDoorLockStVld <= 1)
//	{
//		*pData = Com_VIU_DrvrDoorLockStVld;
//		return E_OK;
//	}
//	else
//	{
//		return E_NOK;
//	}
//}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_IPB_VehicleSpeedValid(uint8 * pData) //0x3AE
{
	if(Com_IPB_VehicleSpeedValid <= 1)
	{
		*pData = Com_IPB_VehicleSpeedValid;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_brakePedalSts(uint8 * pData)//0x3AE
{
	if(Com_VDC_brakePedalSts <= 1)
	{
		*pData = Com_VDC_brakePedalSts;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_IPB_VehicleSpeed(float32 * pData)//0x3AE
{
	if(Com_IPB_VehicleSpeed < 460.74375)
	{
		*pData = Com_IPB_VehicleSpeed;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_TotalRang(uint32 * pData)//0x3AE
{
	if(Com_VDC_TotalRang <= 1048575)
	{
		*pData = Com_VDC_TotalRang;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_VDC_actualGear
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_actualGear(uint8 * pData)//0x3AE
{
	if(Com_VDC_TotalRang <= 3)
	{
		*pData = Com_VDC_actualGear;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_VDC_actualGearValid
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_VDC_actualGearValid(uint8 * pData)//0x3AE
{
	if(Com_VDC_TotalRang <= 1)
	{
		*pData = Com_VDC_actualGearValid;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_ABM_IMU_LongAcceleration(float32 * pData) //0x3AF
{
	if((Com_ABM_IMU_LongAcceleration <= 114.78)&&(Com_ABM_IMU_LongAcceleration >= -49.05))
	{
		*pData = Com_ABM_IMU_LongAcceleration;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_ABM_IMU_LateralAcceleration(float32 * pData)//0x3AF
{
	if((Com_ABM_IMU_LateralAcceleration <= 114.78)&&(Com_ABM_IMU_LateralAcceleration >= -49.05))
	{
		*pData = Com_ABM_IMU_LateralAcceleration;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_ABM_IMU_YawRate(float32 * pData)//0x3AF
{
	if((Com_ABM_IMU_YawRate <= 355.35)&&(Com_ABM_IMU_YawRate >= -300))
	{
		*pData = Com_ABM_IMU_YawRate;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_ModSet(uint8 * pData) //0x3AB
{
	if(Com_CDC_ModSet <= 7)
	{
		*pData = Com_CDC_ModSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_FullOpenDegSet(uint8 * pData) //0x3AB
{
	if(Com_CDC_FullOpenDegSet <= 7)
	{
		*pData = Com_CDC_FullOpenDegSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_OpenSpdSet(uint8 * pData) //0x3AB
{
	if(Com_CDC_OpenSpdSet <= 7)
	{
		*pData = Com_CDC_OpenSpdSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_HndFeelSet(uint8 * pData) //0x3AB
{
	if(Com_CDC_HndFeelSet <= 7)
	{
		*pData = Com_CDC_HndFeelSet;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Read_Com_ISrDoorContact
 * @brief:Read Signal from CAN.
 * */
Std_ReturnType RTE_Read_Com_CDC_PDMFR_Ctrl(uint8 * pData) //0x3AB
{
	if(Com_CDC_PDMFR_Ctrl <= 15)
	{
		*pData = Com_CDC_PDMFR_Ctrl;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_VIU1_SourceNodeIdentifier(uint8 * pData) //0x449
{
	*pData = Com_VIU1_SourceNodeIdentifier;
	return E_OK;
}

Std_ReturnType RTE_Read_Com_VIU1_RepeatMessageRequestBit(uint8 * pData) //0x449
{
	if(Com_VIU1_RepeatMessageRequestBit <= 1)
	{
		*pData = Com_VIU1_RepeatMessageRequestBit;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_VIU1_ActiveWakeupBit(uint8 * pData) //0x449
{
	if(Com_VIU1_ActiveWakeupBit <= 1)
	{
		*pData = Com_VIU1_ActiveWakeupBit;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_VIU1_RepeatSts(uint8 * pData) //0x449
{
	if(Com_VIU1_RepeatSts <= 1)
	{
		*pData = Com_VIU1_RepeatSts;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeYear(uint16 * pData) //0x5E2
{
	if((Com_TBOX_TimeYear <= 2255)&&(Com_TBOX_TimeYear >= 2000))
	{
		*pData = Com_TBOX_TimeYear;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeMonth(uint8 * pData) //0x5E2
{
	if((Com_TBOX_TimeMonth <= 12)&&(Com_TBOX_TimeMonth >= 1))
	{
		*pData = Com_TBOX_TimeMonth;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeDay(uint8 * pData) //0x5E2
{
	if((Com_TBOX_TimeDay <= 31)&&(Com_TBOX_TimeDay >= 1))
	{
		*pData = Com_TBOX_TimeDay;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeHour(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeHour <= 23)
	{
		*pData = Com_TBOX_TimeHour;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeMinute(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeMinute <= 59)
	{
		*pData = Com_TBOX_TimeMinute;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeSecond(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeSecond <= 59)
	{
		*pData = Com_TBOX_TimeSecond;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

//Std_ReturnType RTE_Read_Com_TBOX_TimeSecond(uint8 * pData) //0x5E2
//{
//	if(Com_TBOX_TimeSecond <= 59)
//	{
//		*pData = Com_TBOX_TimeSecond;
//		return E_OK;
//	}
//	else
//	{
//		return E_NOK;
//	}
//}

Std_ReturnType RTE_Read_Com_TBOX_TimeZone(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeZone <= 3)
	{
		*pData = Com_TBOX_TimeZone;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeZoneNum(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeZoneNum <= 31)
	{
		*pData = Com_TBOX_TimeZoneNum;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Read_Com_TBOX_TimeFlag(uint8 * pData) //0x5E2
{
	if(Com_TBOX_TimeFlag <= 3)
	{
		*pData = Com_TBOX_TimeFlag;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}



/*Tx*/
Std_ReturnType RTE_Write_Com_PDM_FR_IMUSt(uint8 data)//0x3B7
{
	if(data <= 3)
	{
		Com_PDM_FR_IMUSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrDoorMovingStatus
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_SlopeX (float32 data)//0x3B7
{
	if((data <= 100)&&(data >= -100))
	{
		Com_PDM_FR_SlopeX = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrPrimaryMotorPower
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_SlopeY (float32 data)//0x3B7
{
	if((data <= 100)&&(data >= -100))
	{
		Com_PDM_FR_SlopeY = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrPrimaryMotorDirection
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_Ag (uint8 data)//0x3A6
{
	Com_PDM_FR_Ag = data;
	return E_OK;
}


/**
 * @name :RTE_Write_Com_ISrPushDetected
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_AntiPinchSt (uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FR_AntiPinchSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_AntiPlaySt(uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FR_AntiPlaySt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrSlipDeviceActivState
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_DoorOpeningAgrSpd(float32 data)//0x3A6
{
	if((data <= 127)&&(data >= -128))
	{
		Com_PDM_FR_DoorOpeningAgrSpd = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
/**
 * @name :RTE_Write_Com_ISrStatusDriveControl
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_DRDDetnEna(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FR_DRDDetnEna = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_Com_ISrStatusPositionAngle
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_FailReazon(uint8 data)//0x3A6
{
	if(data <= 31)
	{
		Com_PDM_FR_FailReazon = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * @name :RTE_Write_comTxNM_FrameID
 * @brief:Write Signal to CAN.
 * */
Std_ReturnType RTE_Write_Com_PDM_FR_FolwUpSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FR_FolwUpSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_FullOpenDegSetFb(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FR_FullOpenDegSetFb = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_InstallPosnLrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FR_InstallPosnLrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_LrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FR_LrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_MaxPosnLrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FR_MaxPosnLrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_ModSetFb(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FR_ModSetFb = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_MtnSt(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FR_MtnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_NCODSt(uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FR_NCODSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_PDM_FR_OpenSpdSetFb(uint8 data)//0x3A6
{
	if(data <= 7)
	{
		Com_PDM_FR_OpenSpdSetFb = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_OverTProtnSt(uint8 data)//0x3A6
{
	if(data <= 1)
	{
		Com_PDM_FR_OverTProtnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_PDM_FR_SelfLrnMeclPosn(uint8 data)//0x3A6
{
	Com_PDM_FR_SelfLrnMeclPosn = data;
	return E_OK;
}

Std_ReturnType RTE_Write_Com_PDM_FR_SysFlt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FR_SysFlt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_ZeroPosnLrnSt(uint8 data)//0x3A6
{
	if(data <= 3)
	{
		Com_PDM_FR_ZeroPosnLrnSt = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum1(uint16 data)//0x5CB
{
	if(data <= 4095)
	{
		Com_PDM_FR_FaultNum1 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}

}

Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum2(uint16 data)//0x5CB
{
	if(data <= 4095)
	{
		Com_PDM_FR_FaultNum2 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum3(uint16 data)//0x5CB
{
	if(data <= 4095)
	{
		Com_PDM_FR_FaultNum3 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_FaultNum4(uint16 data)//0x5CB
{
	if(data <= 4095)
	{
		Com_PDM_FR_FaultNum4 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_FrameIndex(uint8 data)//0x5CB
{
	if(data <= 31)
	{
		Com_PDM_FR_FrameIndex = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_TotalFaultNum(uint8 data)//0x5CB
{
	Com_PDM_FR_TotalFaultNum = data;
	return E_OK;
}

Std_ReturnType RTE_Write_Com_PDM_FR_SupplierNum(uint8 data)//0x5CB
{
	if(data <= 7)
	{
		Com_PDM_FR_SupplierNum = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}

}


//Std_ReturnType RTE_Write_Com_PDM_FR_SourceNodeIdentifier(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxNM_FrameID(uint8 data)
{
	Com_PDM_FR_SourceNodeIdentifier = data;
	return E_OK;
}

//Std_ReturnType RTE_Write_Com_PDM_FR_RepeatMessageRequestBit(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxRepMessage_State(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FR_RepeatMessageRequestBit = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

//Std_ReturnType RTE_Write_Com_PDM_FR_ActiveWakeupBit(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxActiveWakeup(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FR_ActiveWakeupBit = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

//Std_ReturnType RTE_Write_Com_PDM_FR_RepeatSts(uint8 data)//0x471
Std_ReturnType RTE_Write_comTxRepeatState(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FR_RepeatSts = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_NM(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FR_NMReq_NM = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_Diag(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FR_NMReq_Diag = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_Poweron(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FR_NMReq_Poweron = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_NMReq_GyroWakeup(uint8 data)//0x471
{
	if(data <= 1)
	{
		Com_PDM_FR_NMReq_GyroWakeup = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FR_FirstWakeupReason(uint8 data)//0x471
{
	if(data <= 63)
	{
		Com_PDM_FR_FirstWakeupReason = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}


#endif


Std_ReturnType RTE_Read_Time(uint32 * pData)
{
	Std_ReturnType ret  = E_OK;
	uint32_t temp = 0;
	uint8_t temp_valid = 0;
	ret = RTE_Read_Com_TBOX_TimeFlag(&temp_valid);
	if(temp_valid == 0)
	{
		temp = 0xFFFFFFFF;
		*pData = temp;
		return ret;
	}
	else
	{
		uint16_t temp_year = 0;
		ret = RTE_Read_Com_TBOX_TimeYear(&temp_year);
		uint8_t temp_month = 0;
		ret = RTE_Read_Com_TBOX_TimeMonth(&temp_month);
		uint8_t temp_day = 0;
		ret = RTE_Read_Com_TBOX_TimeDay(&temp_day);
		uint8_t temp_hour = 0;
		ret = RTE_Read_Com_TBOX_TimeHour(&temp_hour);
		uint8_t temp_minute = 0;
		ret = RTE_Read_Com_TBOX_TimeMinute(&temp_minute);
		uint8_t temp_second = 0;
		ret = RTE_Read_Com_TBOX_TimeSecond(&temp_second);
		temp = (temp_year & 0x3F);
		temp = temp<<4;
		temp |= temp_month;
		temp = temp << 5;
		temp |= temp_day;
		temp = temp << 5;
		temp |= temp_hour;
		temp = temp << 6;
		temp |= temp_minute;
		temp = temp << 6;
		temp |= temp_second;
		*pData = temp;
	}
	return ret;
}

#else

Std_ReturnType RTE_Read_Com_DRD_FL_DoorOpenAg(uint8 * pData)//0x150
{
	if(Com_DRD_FL_DoorOpenAg <= 100)
	{
		*pData = Com_DRD_FL_DoorOpenAg;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}


Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum1(uint16 data)//0x5C3
{
	if(data <= 4095)
	{
		Com_PDM_FL_FaultNum1 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}

}

Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum2(uint16 data)//0x5C3
{
	if(data <= 4095)
	{
		Com_PDM_FL_FaultNum2 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType RTE_Write_Com_PDM_FL_FaultNum3(uint16 data)//0x5C3
{
	if(data <= 4095)
	{
		Com_PDM_FL_FaultNum3 = data;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

#endif


