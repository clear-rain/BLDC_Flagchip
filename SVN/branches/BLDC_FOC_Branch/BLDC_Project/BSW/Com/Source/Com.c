#include "com.h"
#ifndef ECU_ADDRESS_BLDC
#include "uds_Dem.h"
#endif
#include "IoHwAb_Dio.h"
extern Bsp_CanTxInit_t g_stBsp_CanTxInit[CANTX_NUM];
static boolean Com_lSendSignal(uint16 sigId);

extern void PduR_ComTransmit(uint32 PduIndex,uint8 *pduInfoPtr);

static const uint32 comBitMask[33] = {
    0x00,
    0x00000001, 0x00000003, 0x00000007, 0x0000000F,
    0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF,
    0x000001FF, 0x000003FF, 0x000007FF, 0x00000FFF,
    0x00001FFF, 0x00003FFF, 0x00007FFF, 0x0000FFFF,
    0x0001FFFF, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF,
    0x001FFFFF, 0x003FFFFF, 0x007FFFFF, 0x00FFFFFF,
    0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF,
    0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF
};

ComRunPduDatasType comRunPduDatasList[COM_PDUS_CNT];

void Com_MainFunction(void)
{
	static uint8_t FaultReportCNT = 0;
#ifndef ECU_ADDRESS_BLDC
	Analysis_Com_signal_Task();
	Com_lTxHdl();

	if(FaultReportCNT == 100)
	{

		Com_FaultReport500ms();

		FaultReportCNT = 0;
	}
	else
	{
		FaultReportCNT++;
	}

#else
	Analysis_Com_signal_Task();

	Com_Task_BLDCTest();
//	IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 0);
	Com_lTxHdl();
//	IoHwAb_Dio_WriteChannel(VBAT_ENCODER_CTRL_IDX, 1);

#endif
}

boolean txRdy[CANTX_NUM] = {FALSE};

uint32 Can_Tx_Timeoutcounter = 0;

void Com_lTxHdl(void)
{
	uint16 index = 0;
	uint16 i,com_signal_cnt;
//	static uint32 Can_Tx_Timeoutcounter = 0;

	com_signal_cnt = getCom_SIGNALS_CNT();
	Can_Tx_Timeoutcounter++;
//	for (index = 0; index < CANTX_NUM; index++)
	{
		if (g_stBsp_CanTxInit[index].ui16CanTxPeriod != 0)
		{
			if((Can_Tx_Timeoutcounter % g_stBsp_CanTxInit[index].ui16CanTxPeriod) == 0)
			{
				txRdy[index] = TRUE;
			}
		}
		/*Process event frames*/
		else
		{
			//如果是事件帧，则需要在其他地方操作txRdy[index] = TRUE;
		}

		if (txRdy[index] == TRUE)
		{
			/*通过确定的报文ID，找到信号并解析*/
//			for(i = 0;i < com_signal_cnt;i++)
//			{
//				if(comSigs[i].FrameId == g_stBsp_CanTxInit[index].ui32FrameId)
//				{
//					Com_lSendSignal(i);
//				}
//			}
//			/*通过确定的报文ID，找到信号并解析*/
			for(i = 56;i < 74;i++)
			{
					Com_lSendSignal(i);
			}

			PduR_ComTransmit(g_stBsp_CanTxInit[index].PDUIndex, g_stBsp_CanTxInit[index].pui8CanTxBuffer);
			txRdy[index] = FALSE;
		}
	}
    if(Can_Tx_Timeoutcounter >= 10000)
    {Can_Tx_Timeoutcounter = 0;}
}

void Com_TxNM(void)
{
	uint16 i,index,com_signal_cnt;

	com_signal_cnt = getCom_SIGNALS_CNT();
	for(index = 0; index < CANTX_NUM; index++)
	{
		if(COM_TX_PDUID_NM == g_stBsp_CanTxInit[index].ui32FrameId)
		{
			break;
		}
	}
	if(index >= CANTX_NUM)
	{
		return ;
	}
	for(i = 0;i < com_signal_cnt;i++)
	{
		if(comSigs[i].FrameId == COM_TX_PDUID_NM)
		{
			Com_lSendSignal(i);
		}
	}
	PduR_ComTransmit(g_stBsp_CanTxInit[index].PDUIndex,g_stBsp_CanTxInit[index].pui8CanTxBuffer);
}


static boolean Com_lSendSignal(uint16 sigId)
{
    uint32 FrameId;
    uint8 row;
    uint8 column;
    uint8 remainLen;
    uint8 len;
    uint8 indx;
    uint32 raw;
    uint8 *temp_buff = NULL;
    uint16 com_signal_cnt;

    com_signal_cnt = getCom_SIGNALS_CNT();
    if (sigId >= com_signal_cnt)
    {
        return FALSE;
    }

    if (comSigs[sigId].integer == FALSE)
    {
        if (comSigs[sigId].unsign == TRUE)
        {
            raw = (uint32)((*(float32*)comSigs[sigId].pVal - comSigs[sigId].offset) / comSigs[sigId].factor);
        }
        else
        {
            raw = (uint32)(sint32)((*(float32*)comSigs[sigId].pVal - comSigs[sigId].offset) / comSigs[sigId].factor);
        }
    }
    else if (comSigs[sigId].len <= 8)
    {
        if (comSigs[sigId].unsign == TRUE)
        {
             raw = (uint32)(*(uint8*)comSigs[sigId].pVal);
        }
        else
        {
            raw = (uint32)(sint32)(*(sint8*)comSigs[sigId].pVal);
        }
    }
    else if (comSigs[sigId].len <= 16)
    {
        if (comSigs[sigId].unsign == TRUE)
        {
            raw = (uint32)(*(uint16*)comSigs[sigId].pVal);
        }
        else
        {
            raw = (uint32)(sint32)(*(sint16*)comSigs[sigId].pVal);
        }
    }
    else
    {
        if (comSigs[sigId].unsign == TRUE)
        {
            raw = (uint32)(*(uint32*)comSigs[sigId].pVal);
        }
        else
        {
            raw = (uint32)(sint32)(*(sint32*)comSigs[sigId].pVal);
        }
    }
    FrameId = comSigs[sigId].FrameId;
    row = (uint8)(comSigs[sigId].start >> 3);
    column = (uint8)(comSigs[sigId].start & 0x07);
    remainLen = comSigs[sigId].len;
    len = 0;
    indx = 0;
    for(uint8 i = 0;i < CANTX_NUM;i++)
    {
    	if(FrameId == g_stBsp_CanTxInit[i].ui32FrameId)
    	{
    		temp_buff = g_stBsp_CanTxInit[i].pui8CanTxBuffer;
    	}
    }
    if(temp_buff == NULL)
    {
    	return FALSE;
    }
    if (comSigs[sigId].format == COM_SIG_INTEL)
    {
        while (remainLen > 0)
        {
            len = ((remainLen > (8 - column)) ? (8 - column) : remainLen);
            temp_buff[row] &= ~(uint8)(comBitMask[len] << column);
            temp_buff[row] |= (uint8)(((raw >> indx) & comBitMask[len]) << column);
            row++;
            indx += len;
            column = 0;
            remainLen -= len;
        }
    }
    else
    {
        indx = 32 - comSigs[sigId].len;
        while (remainLen > 0)
        {
            len = ((remainLen > (column + 1)) ? (column + 1) : remainLen);
            temp_buff[row] &= ~(uint8)(comBitMask[len] << (column + 1 - len));
            temp_buff[row] |= (uint8)(((raw >> (32 - indx - len)) & comBitMask[len]) << (column + 1 - len));
            row++;
            indx += len;
            column = 7;
            remainLen -= len;
        }
    }
    return TRUE;
}

void INTEL_EightSignalAnaly(uint8 index , uint8* BufferPtr)
{
    uint8 u8Temp;

    uint8 row;
    uint8 column;
    uint8 remainLen;

	u8Temp = 0;
	remainLen = comSigs[index].len;
	row = (uint8)(comSigs[index].start >> 3);
	column = (uint8)(comSigs[index].start & 0x07);
	if (remainLen <= (8 - column))
	{
	   u8Temp = (uint8)((BufferPtr[row] & (comBitMask[remainLen] << column)) >> column);
	}
	else
	{
		u8Temp = (uint8)((BufferPtr[row] & (comBitMask[8 - column] << column)) >> column);
		remainLen -= (8 - column);
		row += 1;
		column = 0;
		/* remainLen must < 8 */
		u8Temp += ((uint8)(BufferPtr[row] & comBitMask[remainLen]) << (comSigs[index].len - remainLen));
	}
	if (comSigs[index].unsign == FALSE)
	{
		if ((uint8)(u8Temp >> (comSigs[index].len - 1)) > 0)
		{
			/* signed number need append 1 at top bits */
			u8Temp |= (0xFFUL - comBitMask[comSigs[index].len]);
		}
	}
	if (comSigs[index].integer == FALSE)
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(float32*)comSigs[index].pVal = (float32)u8Temp * comSigs[index].factor + comSigs[index].offset;
		}
		else
		{
			*(float32*)comSigs[index].pVal = (float32)(sint8)u8Temp * comSigs[index].factor + comSigs[index].offset;
		}
	}
	else
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(uint8*)comSigs[index].pVal = (uint8)u8Temp;
		}
		else
		{
			*(sint8*)comSigs[index].pVal = (sint8)u8Temp;
		}
	}
}

void INTEL_SixteenSignalAnaly(uint8 index , uint8* BufferPtr)
{
    uint16 u16Temp;
    uint8 u8Temp;

    uint8 row;
    uint8 column;
    uint8 remainLen;
    uint8 indx;

	u16Temp = 0;
	indx = 0;
	remainLen = comSigs[index].len;
	row = (uint8)(comSigs[index].start >> 3);
	column = (uint8)(comSigs[index].start & 0x07);

	while (remainLen > 0)
	{
		if (remainLen <= (8 - column))
		{
			u8Temp = (uint8)((BufferPtr[row] & (comBitMask[remainLen] << column)) >> column);
			u16Temp += (uint16)((uint16)u8Temp << indx);
			indx += remainLen;
			remainLen = 0;
			row++;
			column = 0;
		}
		else
		{
			u8Temp = (uint8)((BufferPtr[row] & (comBitMask[8 - column] << column)) >> column);
			u16Temp += (uint16)((uint16)u8Temp << indx);
			remainLen -= (8 - column);
			indx += (8 - column);
			row++;
			column = 0;
		}
	}

	if (comSigs[index].unsign == FALSE)
	{
		if ((uint16)(u16Temp >> (comSigs[index].len - 1)) > 0)
		{
			/* signed number need append 1 at top bits */
			u16Temp |= (uint16)(0xFFFFUL - comBitMask[comSigs[index].len]);
		}
	}
	if (comSigs[index].integer == FALSE)
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(float32*)comSigs[index].pVal = (float32)u16Temp * comSigs[index].factor + comSigs[index].offset;
		}
		else
		{
			*(float32*)comSigs[index].pVal = (float32)(sint16)u16Temp * comSigs[index].factor + comSigs[index].offset;
		}
	}
	else
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(uint16*)comSigs[index].pVal = (uint16)u16Temp;
		}
		else
		{
			*(sint16*)comSigs[index].pVal = (sint16)u16Temp;
		}
	}


}

void INTEL_ThirtyTwoSignalAnaly(uint8 index , uint8* BufferPtr)
{
    uint8 u8Temp;
    uint32 u32Temp;

    uint8 row;
    uint8 column;
    uint8 remainLen;
    uint8 indx;

	u32Temp = 0;
	indx = 0;
	remainLen = comSigs[index].len;
	row = (uint8)(comSigs[index].start >> 3);
	column = (uint8)(comSigs[index].start & 0x07);

	while (remainLen > 0)
	{
		if (remainLen <= (8 - column))
		{
			u8Temp = (uint8)((BufferPtr[row] & (comBitMask[remainLen] << column)) >> column);
			u32Temp += (uint32)((uint32)u8Temp << indx);
			indx += remainLen;
			remainLen = 0;
			row++;
			column = 0;
		}
		else
		{
			u8Temp = (uint8)((BufferPtr[row] & (comBitMask[8 - column] << column)) >> column);
			u32Temp += (uint32)((uint32)u8Temp << indx);
			remainLen -= (8 - column);
			indx += (8 - column);
			row++;
			column = 0;
		}
	}

	if (comSigs[index].unsign == FALSE)
	{
		if ((uint32)(u32Temp >> (comSigs[index].len - 1)) > 0)
		{
			/* signed number need append 1 at top bits */
			u32Temp |= (uint32)(0xFFFFFFFFUL - comBitMask[comSigs[index].len]);
		}
	}
	if (comSigs[index].integer == FALSE)
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(float32*)comSigs[index].pVal = (float32)u32Temp * comSigs[index].factor + comSigs[index].offset;
		}
		else
		{
			*(float32*)comSigs[index].pVal = (float32)(sint32)u32Temp * comSigs[index].factor + comSigs[index].offset;
		}
	}
	else
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(uint32*)comSigs[index].pVal = (uint32)u32Temp;
		}
		else
		{
			*(sint32*)comSigs[index].pVal = (sint32)u32Temp;
		}
	}

}

void Motorola_EightSignalAnaly(uint8 index , uint8* BufferPtr)
{
    uint8 u8Temp;

    uint8 row;
    uint8 column;
    uint8 remainLen;
	u8Temp = 0;
	remainLen = comSigs[index].len;
	row = (uint8)(comSigs[index].start >> 3);
	column = (uint8)(comSigs[index].start & 0x07);
	if (remainLen <= (column + 1))
	{
	   u8Temp = (uint8)((BufferPtr[row] & (comBitMask[remainLen] << (column + 1 - remainLen))) >> (column + 1 - remainLen));
	}
	else
	{
		u8Temp = (uint8)(BufferPtr[row] & comBitMask[column + 1]);
		remainLen -= (column + 1);
		row += 1;
		u8Temp <<= remainLen;
		column = 7;
		/* remainLen must < 8 */
		u8Temp += (uint8)((BufferPtr[row] & (comBitMask[remainLen] << (8 - remainLen))) >> (8 - remainLen));
	}
	if (comSigs[index].unsign == FALSE)
	{
		if ((uint8)(u8Temp >> (comSigs[index].len - 1)) > 0)
		{
			/* signed number need append 1 at top bits */
			u8Temp |= (0xFFUL - comBitMask[comSigs[index].len]);
		}
	}
	if (comSigs[index].integer == FALSE)
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(float32*)comSigs[index].pVal = (float32)u8Temp * comSigs[index].factor + comSigs[index].offset;
		}
		else
		{
			*(float32*)comSigs[index].pVal = (float32)(sint8)u8Temp * comSigs[index].factor + comSigs[index].offset;
		}
	}
	else
	{
		if (comSigs[index].unsign == TRUE)
		{
			int16_t i16Result = u8Temp + (int16_t)comSigs[index].offset;

			if (i16Result > 255)
			{
				*(uint16*)comSigs[index].pVal = (uint16)i16Result;
			} else if (i16Result < 0 || comSigs[index].offset < 0)
			{
				*(int16_t*)comSigs[index].pVal = (int16_t)i16Result;
			} else
			{
				*(uint8*)comSigs[index].pVal = (uint8)i16Result;
			}
		}
		else
		{
			*(sint8*)comSigs[index].pVal = (sint8)u8Temp * comSigs[index].factor + comSigs[index].offset;
		}
	}

}

void Motorola_SixteenSignalAnaly(uint8 index , uint8* BufferPtr)
{
    uint16 u16Temp;
    uint8 u8Temp;

    uint8 row;
    uint8 column;
    uint8 remainLen;
    uint8 len;

	u8Temp = 0;
	u16Temp = 0;
	remainLen = comSigs[index].len;
	row = (uint8)(comSigs[index].start >> 3);
	column = (uint8)(comSigs[index].start & 0x07);

	while (remainLen > 0)
	{
		if (remainLen > (column + 1))
		{
			len = (column + 1);
		}
		else
		{
			len = remainLen;
		}
		u16Temp <<= len;
		u16Temp += (uint8)((BufferPtr[row] & (comBitMask[len] << (column + 1 - len))) >> (column + 1 - len));
		remainLen -= len;
		column = 7;
		row++;
	}

	if (comSigs[index].unsign == FALSE)
	{
		if ((uint16)(u16Temp >> (comSigs[index].len - 1)) > 0)
		{
			/* signed number need append 1 at top bits */
			u16Temp |= (0xFFFFUL - comBitMask[comSigs[index].len]);
		}
	}
	if (comSigs[index].integer == FALSE)
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(float32*)comSigs[index].pVal = (float32)u16Temp * comSigs[index].factor + comSigs[index].offset;
		}
		else
		{
			*(float32*)comSigs[index].pVal = (float32)(sint16)u16Temp * comSigs[index].factor + comSigs[index].offset;
		}
	}
	else
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(uint16*)comSigs[index].pVal = (uint16)u16Temp;
		}
		else
		{
			*(sint16*)comSigs[index].pVal = (sint16)u16Temp;
		}
	}

}

void Motorola_ThirtyTwoSignalAnaly(uint8 index , uint8* BufferPtr)
{
    uint32 u32Temp;
    uint8 u8Temp;


    uint8 row;
    uint8 column;
    uint8 remainLen;
    uint8 len;

	/* comSigs[index].len must be <= 32 */
	u8Temp = 0;
	u32Temp = 0;
	remainLen = comSigs[index].len;
	row = (uint8)(comSigs[index].start >> 3);
	column = (uint8)(comSigs[index].start & 0x07);

	while (remainLen > 0)
	{
		if (remainLen > (column + 1))
		{
			len = (column + 1);
		}
		else
		{
			len = remainLen;
		}
		u32Temp <<= len;
		u32Temp += (uint8)((BufferPtr[row] & (comBitMask[len] << (column + 1 - len))) >> (column + 1 - len));
		remainLen -= len;
		column = 7;
		row++;
	}

	if (comSigs[index].unsign == FALSE)
	{
		if ((uint32)(u32Temp >> (comSigs[index].len - 1)) > 0)
		{
			/* signed number need append 1 at top bits */
			u32Temp |= (0xFFFFFFFFUL - comBitMask[comSigs[index].len]);
		}
	}
	if (comSigs[index].integer == FALSE)
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(float32*)comSigs[index].pVal = (float32)u32Temp * comSigs[index].factor + comSigs[index].offset;
		}
		else
		{
			*(float32*)comSigs[index].pVal = (float32)(sint32)u32Temp * comSigs[index].factor + comSigs[index].offset;
		}
	}
	else
	{
		if (comSigs[index].unsign == TRUE)
		{
			*(uint32*)comSigs[index].pVal = (uint32)u32Temp;
		}
		else
		{
			*(sint32*)comSigs[index].pVal = (sint32)u32Temp;
		}
	}

}


void AnalysisReceiveSignals(uint32 FrameId , uint8 index , uint8* BufferPtr)
{

	while(FrameId == comSigs[index].FrameId)
	{
		if ((comSigs[index].len == 0) || (comSigs[index].len > 32))
		{
			index++;
			continue;
		}
		if (comSigs[index].format == COM_SIG_INTEL)
		{
#if 0

			if (comSigs[index].len <= 8)
			{
				INTEL_EightSignalAnaly(index,BufferPtr);
			}
			else if (comSigs[index].len <= 16)
			{
				INTEL_SixteenSignalAnaly(index,BufferPtr);
			}
			else if (comSigs[index].len <= 32)
			{
				INTEL_ThirtyTwoSignalAnaly(index,BufferPtr);
			}
			else
			{
				/* bit length is not corrent, nothing to do */
			}
#endif
		}
		else
		{
			/* Motorola MSB */
			if (comSigs[index].len <= 8)
			{
				Motorola_EightSignalAnaly(index,BufferPtr);
			}
			else if (comSigs[index].len <= 16)
			{
				Motorola_SixteenSignalAnaly(index,BufferPtr);
			}
			else
			{
				Motorola_ThirtyTwoSignalAnaly(index,BufferPtr);
			}
		}
		index++;
    }
}

#ifndef ECU_ADDRESS_BLDC
static bool FaultReportFlag = false;

void Com_FaultReport500ms()
{
    static uint8_t AllFaultNum = 0;
    static uint16_t FaultNumArr[DTC_NUM + 3] = {0};
	static uint8_t LastFaultNum = 0;
	static uint8_t FaultIndex = 0;

#ifdef ECU_ADDRESS_PDM_FL
	RTE_Write_Com_PDM_FL_SupplierNum(1);
	if(FaultReportFlag == 0)
		{
			//if there are no fault num to report, then get new fault;
			//todo : 通过DEM接口返回需要的错误记录个数
		 	 if ((Dem_GetFaultNum(FaultNumArr, &AllFaultNum)) != 0)
			{
				memset(FaultNumArr, 0, sizeof(FaultNumArr));
				AllFaultNum = 0;
			}
			if(AllFaultNum == 0)
			{
				//there are no fault num
				RTE_Write_Com_PDM_FL_TotalFaultNum(0);

				RTE_Write_Com_PDM_FL_FrameIndex(0);
				RTE_Write_Com_PDM_FL_FaultNum1(0);
				RTE_Write_Com_PDM_FL_FaultNum2(0);
				RTE_Write_Com_PDM_FL_FaultNum3(0);
				RTE_Write_Com_PDM_FL_FaultNum4(0);
			}
			else if(AllFaultNum <= 4)
			{
				RTE_Write_Com_PDM_FL_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FL_FrameIndex(1+FaultIndex);
				RTE_Write_Com_PDM_FL_FaultNum1(FaultNumArr[FaultIndex]);
				RTE_Write_Com_PDM_FL_FaultNum2(FaultNumArr[FaultIndex+1]);
				RTE_Write_Com_PDM_FL_FaultNum3(FaultNumArr[FaultIndex+2]);
				RTE_Write_Com_PDM_FL_FaultNum4(FaultNumArr[FaultIndex+3]);
			}
			else
			{
				//AllFaultNum  > 4
				FaultReportFlag = 1;
				LastFaultNum = AllFaultNum - 4;
				RTE_Write_Com_PDM_FL_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FL_FrameIndex(1);
				RTE_Write_Com_PDM_FL_FaultNum1(FaultNumArr[0]);
				RTE_Write_Com_PDM_FL_FaultNum2(FaultNumArr[1]);
				RTE_Write_Com_PDM_FL_FaultNum3(FaultNumArr[2]);
				RTE_Write_Com_PDM_FL_FaultNum4(FaultNumArr[3]);
			}

			//endif(FaultReportFlag == 0)
		}
		else
		{

			if(LastFaultNum <= 4)
			{
				FaultIndex += 1;
				RTE_Write_Com_PDM_FL_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FL_FrameIndex(1+FaultIndex);
				RTE_Write_Com_PDM_FL_FaultNum1(FaultNumArr[4 * FaultIndex]);
				RTE_Write_Com_PDM_FL_FaultNum2(FaultNumArr[4 * FaultIndex + 1]);
				RTE_Write_Com_PDM_FL_FaultNum3(FaultNumArr[4 * FaultIndex + 2]);
				RTE_Write_Com_PDM_FL_FaultNum4(FaultNumArr[4 * FaultIndex + 3]);
				FaultIndex = 0;
				FaultReportFlag = 0;
				LastFaultNum = 0;
				AllFaultNum = 0;
			}
			else
			{
				LastFaultNum -= 4;
				FaultIndex += 1;
				RTE_Write_Com_PDM_FL_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FL_FrameIndex(1+FaultIndex);
				RTE_Write_Com_PDM_FL_FaultNum1(FaultNumArr[4 * FaultIndex]);
				RTE_Write_Com_PDM_FL_FaultNum2(FaultNumArr[4 * FaultIndex + 1]);
				RTE_Write_Com_PDM_FL_FaultNum3(FaultNumArr[4 * FaultIndex + 2]);
				RTE_Write_Com_PDM_FL_FaultNum4(FaultNumArr[4 * FaultIndex + 3]);
			}
		}
#endif

#ifdef ECU_ADDRESS_PDM_FR
	RTE_Write_Com_PDM_FR_SupplierNum(1);
	if(FaultReportFlag == 0)
		{
			//if there are no fault num to report, then get new fault;
				//todo : 通过DEM接口返回需要的错误记录个数
			 if ((Dem_GetFaultNum(FaultNumArr, &AllFaultNum)) != 0)
			{
				memset(FaultNumArr, 0, sizeof(FaultNumArr));
				AllFaultNum = 0;
			}
			if(AllFaultNum == 0)
			{
				//there are no fault num
				RTE_Write_Com_PDM_FR_TotalFaultNum(0);
				RTE_Write_Com_PDM_FR_FrameIndex(0);
				RTE_Write_Com_PDM_FR_FaultNum1(0);
				RTE_Write_Com_PDM_FR_FaultNum2(0);
				RTE_Write_Com_PDM_FR_FaultNum3(0);
				RTE_Write_Com_PDM_FR_FaultNum4(0);
			}
			else if(AllFaultNum <= 4)
			{
				RTE_Write_Com_PDM_FR_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FR_FrameIndex(1+FaultIndex);
				RTE_Write_Com_PDM_FR_FaultNum1(FaultNumArr[FaultIndex]);
				RTE_Write_Com_PDM_FR_FaultNum2(FaultNumArr[FaultIndex+1]);
				RTE_Write_Com_PDM_FR_FaultNum3(FaultNumArr[FaultIndex+2]);
				RTE_Write_Com_PDM_FR_FaultNum4(FaultNumArr[FaultIndex+3]);
			}
			else
			{
				//AllFaultNum  > 4
				FaultReportFlag = 1;
				LastFaultNum = AllFaultNum - 4;
				RTE_Write_Com_PDM_FR_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FR_FrameIndex(1);
				RTE_Write_Com_PDM_FR_FaultNum1(FaultNumArr[0]);
				RTE_Write_Com_PDM_FR_FaultNum2(FaultNumArr[1]);
				RTE_Write_Com_PDM_FR_FaultNum3(FaultNumArr[2]);
				RTE_Write_Com_PDM_FR_FaultNum4(FaultNumArr[3]);
			}

			//endif(FaultReportFlag == 0)
		}
		else
		{

			if(LastFaultNum <= 4)
			{
				FaultIndex += 1;
				RTE_Write_Com_PDM_FR_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FR_FrameIndex(1+FaultIndex);
				RTE_Write_Com_PDM_FR_FaultNum1(FaultNumArr[4 * FaultIndex]);
				RTE_Write_Com_PDM_FR_FaultNum2(FaultNumArr[4 * FaultIndex + 1]);
				RTE_Write_Com_PDM_FR_FaultNum3(FaultNumArr[4 * FaultIndex + 2]);
				RTE_Write_Com_PDM_FR_FaultNum4(FaultNumArr[4 * FaultIndex + 3]);
				FaultIndex = 0;
				FaultReportFlag = 0;
				LastFaultNum = 0;
				AllFaultNum = 0;
			}
			else
			{
				LastFaultNum -= 4;
				FaultIndex += 1;
				RTE_Write_Com_PDM_FR_TotalFaultNum(AllFaultNum);
				RTE_Write_Com_PDM_FR_FrameIndex(1+FaultIndex);

				RTE_Write_Com_PDM_FR_FaultNum1(FaultNumArr[4 * FaultIndex]);
				RTE_Write_Com_PDM_FR_FaultNum2(FaultNumArr[4 * FaultIndex + 1]);
				RTE_Write_Com_PDM_FR_FaultNum3(FaultNumArr[4 * FaultIndex + 2]);
				RTE_Write_Com_PDM_FR_FaultNum4(FaultNumArr[4 * FaultIndex + 3]);
			}
		}
#endif
}

#endif

#ifdef ECU_ADDRESS_BLDC
#include "rte.h"
#include "IoHwAb_Adc.h"

uint8_t bldc_RxOpenSignal = 0;
void Com_RxSignal_BLDCTest(void)
{
	RTE_Read_Com_DRD_FL_DoorOpenAg(&bldc_RxOpenSignal);
}

void Com_TxSignal_BLDCTest(void)
{
	RTE_Write_Com_PDM_FL_FaultNum1((uint16_t)g_aui32Adc1ConvBuf[0]);
	RTE_Write_Com_PDM_FL_FaultNum2((uint16_t)g_aui32Adc1ConvBuf[1]);
	RTE_Write_Com_PDM_FL_FaultNum3(0x00);
}

void Com_Task_BLDCTest(void)
{
	Com_RxSignal_BLDCTest();
	Com_TxSignal_BLDCTest();
}

Recv_DataBuf_T Recv_DataBuf;

uint16_t Com_GetMTEncoderAngleData(void)
{
	return Recv_DataBuf.Angle;
}



#endif /*ECU_ADDRESS_BLDC*/


