#include "Pdu.h"
#ifndef ECU_ADDRESS_BLDC
#include "uds_srv.h"
#else
#include "CompatibleInfo.h"
#include "BspGpio.h"
#endif
#define E_OK     0
#define E_NOT_OK 1

uint32 NMReq_Diag_Cnt=0xffffff;
/**
 * PduR_CanIfRxIndication
 *
 * @param[in]  pduId:ID of the operation
 * @param[in]  pduInfoPtr:The corresponding block
 * @return     none
 * @brief      The PDUR receives commands
 */
void PduR_CanIfRxIndication(Bsp_CanRxInit_t * pduInfoPtr)
{
	uint16 index;

	index = pduInfoPtr->PDUIndex;
#ifndef ECU_ADDRESS_BLDC
    if ((PduRCfgTable[index].dir == PDUR_PDU_RX))
    {
        if((PduRCfgTable[index].dest == PDUR_COM)&&(Open == getCom_Rx_status())&&(Open == getUDS_ComRx()))
        {
        	/* If com data receiving conditions are met, use COM to receive data */
        	pduInfoPtr->ui8CanRx_Flag = 1;
        }
        else if ((PduRCfgTable[index].dest == PDUR_NM)&&(Open == getNm_Rx_status())&&(Open == getUDS_NmRx()))
        {
            /* let the com layer to parse the nm signals */
//        	AsrNm_PduRxIndication(pduInfoPtr);
        }
        else if(Open == getCom_Rx_status())
        {
        	NMReq_Diag_Cnt=0;

#ifdef ECU_ADDRESS_PDM_FL
        	(void)RTE_Write_Com_PDM_FL_NMReq_Diag(1);
#endif
#ifdef ECU_ADDRESS_PDM_FR
        	(void)RTE_Write_Com_PDM_FR_NMReq_Diag(1);
#endif
            /*handle diagnostic frame*/
        	CanTp_PushL_Fifo(CAN_NORMAL,pduInfoPtr->ui8Dlc,pduInfoPtr->stFLEXCAN_RxFilter.u32RxCanId,pduInfoPtr->pui8CanRxBuffer);
        }
    }
#else
    if ((PduRCfgTable[index].dir == PDUR_PDU_RX))
	{
    	if((PduRCfgTable[index].dest == PDUR_COM)&&(Open == getCom_Rx_status())&&(Open == getUDS_ComRx()))
		{
			/* If com data receiving conditions are met, use COM to receive data */
			pduInfoPtr->ui8CanRx_Flag = 1;
		}
	}
#endif
}

/**
 * PduR_ComTransmit
 *
 * @param[in]  pduId:ID of the operation
 * @param[in]  pduInfoPtr:The corresponding block
 * @return     none
 * @brief      The PDUR sends data
 */
void PduR_ComTransmit(uint32 PduIndex,uint8 *pduInfoPtr)
{
#ifndef ECU_ADDRESS_BLDC
	if((PDUR_COM == PduRCfgTable[PduIndex].src)&&(PDUR_PDU_TX == PduRCfgTable[PduIndex].dir))
	{
		if(Open == getCom_Tx_status()&&(Open == getUDS_ComTx()))
		{
			BSP_CAN_Transmit(PduRCfgTable[PduIndex].PduId, pduInfoPtr,g_tCan1);
		}
	}
	else if((PDUR_NM == PduRCfgTable[PduIndex].src)&&(PDUR_PDU_TX == PduRCfgTable[PduIndex].dir))
	{
		if(Open == getNm_Tx_status()&&(Open == getUDS_NmTx()))
		{
			BSP_CAN_Transmit(PduRCfgTable[PduIndex].PduId, pduInfoPtr,g_tCan1);
		}
	}
#else
	if((PDUR_COM == PduRCfgTable[PduIndex].src)&&(PDUR_PDU_TX == PduRCfgTable[PduIndex].dir))
	{
		if(Open == getCom_Tx_status()&&(Open == getUDS_ComTx()))
		{
#if FLEXCAN_USED_INSTANCE1 == STD_ON
//			BSP_CAN_Transmit(PduRCfgTable[PduIndex].PduId, pduInfoPtr,g_tCan1);
#endif
#if FLEXCAN_USED_INSTANCE2 == STD_ON
			BSP_CAN_Transmit(PduRCfgTable[PduIndex].PduId, pduInfoPtr,g_tCan2);
#endif
		}
	}
#endif
}



