#include "Can_Hw.h"

extern FLEXCAN_HandleType  g_tCan1;
void ResetBusoff(FLEXCAN_HandleType *pCanHandle);
Can_ControllerStateType CurrentControlMode = CAN_CS_STARTED;

/* CAN Instance */
static FLEXCAN_Type *const  s_aFlexCan_InstanceTable[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_BASE_PTRS;

uint8 Can_Hw_ChkBusOffStatus(uint8 u8CanIndex)
{
	FLEXCAN_Type *pCan;

	pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];

	if(pCan->ESR1 & FLEXCAN_ESR_BOFFINT_U32)
	{
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}

void Can_FlexCan_BusOff(uint8 u8CanIndex)
{
    uint32 can_status = 0U;
    uint32 can_mask = 0U;
    FLEXCAN_Type *pCan;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[u8CanIndex];
    can_mask = ((pCan->CTRL1 & FLEXCAN_CTRL_BOFFMSK_U32)>>FLEXCAN_CTRL_BOFFMSK_SHIFT_U32);
    can_status = ((pCan->ESR1 & FLEXCAN_ESR_BOFFINT_U32)>>FLEXCAN_ESR_BOFFINT_SHIFT_U32);
    if(0u != can_status)
    {
    	if(0u != can_mask)
    	{
    		if(E_OK == Can_SetControlMode(CAN_CS_STOPPED))
    		{
        		/* Clear the ESR[BOFF_INT] bus off interrupt flag */
        		pCan->ESR1 = (FLEXCAN_ESR_BOFFINT_U32 & FLEXCAN_ESR_CONFIG_MASK_U32);
        		/*Set Busoff*/
        		CanSM_SetBusOff();
    		}
    	}
    	else
    	{
    		/* Clear the ESR[BOFF_INT] bus off interrupt flag */
    		pCan->ESR1 = (FLEXCAN_ESR_BOFFINT_U32 & FLEXCAN_ESR_CONFIG_MASK_U32);
    	}
    }
}

uint8 Can_SetControlMode(Can_ControllerStateType Transition)
{
	uint8 ReturnValue = E_NOT_OK;

	switch(Transition)
	{
		case CAN_CS_STARTED:
			ReturnValue = CanSetControlToStartMode();
			break;
		case CAN_CS_STOPPED:
			ReturnValue = CanSetControlToStopMode();
			break;
		case CAN_CS_SLEEP:
			break;
		default:
			break;
	}
	return ReturnValue;
}

uint8 CanSetControlToStopMode(void)
{
	uint8 ReturnValue = E_NOT_OK;

	if(CAN_CS_STARTED == CurrentControlMode)
	{
		ReturnValue = E_OK;
		CurrentControlMode = CAN_CS_STOPPED;
	}
	else
	{
		/**/
	}

	return ReturnValue;
}

void ResetBusoff(FLEXCAN_HandleType *pCanHandle)
{
	FLEXCAN_Type  *pCan;

	pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
	pCan->CTRL1 &= (~FLEXCAN_CTRL1_BOFFREC(1));
}

//uint8 CanSetControlToStartMode(void)
//{
//	uint8 ReturnValue = E_NOT_OK;
//
//		/*Can init*/
//	ResetBusoff(&g_tCan1);
//	CurrentControlMode = CAN_CS_STARTED;
//
//
//	return ReturnValue;
//}

extern void BSP_CAN_Init(void);
extern FLEXCAN_HandleType g_tCan1;
extern uint32 Can_Tx_Timeoutcounter;
uint8 CanSetControlToStartMode(void)
{
	uint8 ReturnValue = E_NOT_OK;

		/*Can init*/
	FLEXCAN_DeInit(&g_tCan1);
	BSP_CAN_Init();
	Can_Tx_Timeoutcounter = 18;
	CurrentControlMode = CAN_CS_STARTED;


	return ReturnValue;
}

