/*
 * E2E.c
 *
 *  Created on: 2025年4月16日
 *      Author: 22093
 */


#include "E2E.h"
//#include "BspCan.h"
#include <stdio.h>
//#include "com_cfg.h"
//#include "BspCan.h"


//#define uint8_t unsigned char

E2E_CheckStatusType E2E_Process(uint8 *DataPtr,uint8 E2E_Counter,uint8 E2E_CRC,uint8 E2E_len);


// CRC8_SAEJ1850 table
static const uint8_t crc8_table[256] =
    {
        0x00, 0x1D, 0x3A, 0x27, 0x74, 0x69, 0x4E, 0x53,
        0xE8, 0xF5, 0xD2, 0xCF, 0x9C, 0x81, 0xA6, 0xBB,
        0xCD, 0xD0, 0xF7, 0xEA, 0xB9, 0xA4, 0x83, 0x9E,
        0x25, 0x38, 0x1F, 0x02, 0x51, 0x4C, 0x6B, 0x76,
        0x87, 0x9A, 0xBD, 0xA0, 0xF3, 0xEE, 0xC9, 0xD4,
        0x6F, 0x72, 0x55, 0x48, 0x1B, 0x06, 0x21, 0x3C,
        0x4A, 0x57, 0x70, 0x6D, 0x3E, 0x23, 0x04, 0x19,
        0xA2, 0xBF, 0x98, 0x85, 0xD6, 0xCB, 0xEC, 0xF1,
        0x13, 0x0E, 0x29, 0x34, 0x67, 0x7A, 0x5D, 0x40,
        0xFB, 0xE6, 0xC1, 0xDC, 0x8F, 0x92, 0xB5, 0xA8,
        0xDE, 0xC3, 0xE4, 0xF9, 0xAA, 0xB7, 0x90, 0x8D,
        0x36, 0x2B, 0x0C, 0x11, 0x42, 0x5F, 0x78, 0x65,
        0x94, 0x89, 0xAE, 0xB3, 0xE0, 0xFD, 0xDA, 0xC7,
        0x7C, 0x61, 0x46, 0x5B, 0x08, 0x15, 0x32, 0x2F,
        0x59, 0x44, 0x63, 0x7E, 0x2D, 0x30, 0x17, 0x0A,
        0xB1, 0xAC, 0x8B, 0x96, 0xC5, 0xD8, 0xFF, 0xE2,
        0x26, 0x3B, 0x1C, 0x01, 0x52, 0x4F, 0x68, 0x75,
        0xCE, 0xD3, 0xF4, 0xE9, 0xBA, 0xA7, 0x80, 0x9D,
        0xEB, 0xF6, 0xD1, 0xCC, 0x9F, 0x82, 0xA5, 0xB8,
        0x03, 0x1E, 0x39, 0x24, 0x77, 0x6A, 0x4D, 0x50,
        0xA1, 0xBC, 0x9B, 0x86, 0xD5, 0xC8, 0xEF, 0xF2,
        0x49, 0x54, 0x73, 0x6E, 0x3D, 0x20, 0x07, 0x1A,
        0x6C, 0x71, 0x56, 0x4B, 0x18, 0x05, 0x22, 0x3F,
        0x84, 0x99, 0xBE, 0xA3, 0xF0, 0xED, 0xCA, 0xD7,
        0x35, 0x28, 0x0F, 0x12, 0x41, 0x5C, 0x7B, 0x66,
        0xDD, 0xC0, 0xE7, 0xFA, 0xA9, 0xB4, 0x93, 0x8E,
        0xF8, 0xE5, 0xC2, 0xDF, 0x8C, 0x91, 0xB6, 0xAB,
        0x10, 0x0D, 0x2A, 0x37, 0x64, 0x79, 0x5E, 0x43,
        0xB2, 0xAF, 0x88, 0x95, 0xC6, 0xDB, 0xFC, 0xE1,
        0x5A, 0x47, 0x60, 0x7D, 0x2E, 0x33, 0x14, 0x09,
        0x7F, 0x62, 0x45, 0x58, 0x0B, 0x16, 0x31, 0x2C,
        0x97, 0x8A, 0xAD, 0xB0, 0xE3, 0xFE, 0xD9, 0xC4
        };


/*Function Name閿涙RC8_SAEJ1850_LOOKUP;
        CRC8_SAEJ1850 lookup table
        parameter: uint8_t[] buf;
                   uint8_t len;
        return:    uint8_t
*/
uint8_t CRC8_SAEJ1850_LOOKUP(uint8_t* buf, uint8_t len)
{
    uint8_t i;
    uint8_t u8_crc8;
    u8_crc8 = 0x00;

    for (i = 0; i < len; i++)
    {
        u8_crc8 ^= buf[i];
        u8_crc8 = crc8_table[u8_crc8];
    }
    u8_crc8 ^= (uint8_t)0x00;
    return u8_crc8;
}

uint8  receive_arr[64];
uint8 row_start = 0;
uint8 row_end = 0;
uint8 ReceiveCounter = 0;
uint8  Last_ReceiveCounter = 0;
E2E_CheckStatusType  RxGroupID_Sts = 0;
uint8  LastValidCounter = 0;
uint8  WaitForFirstData = 0;
uint8  CalledFlag = 0;
uint16  NonewCounter = 0;
uint8  RepeartCounter = 0;
uint8 E2E_WrongSeqFlag = 0;
uint8 E2E_Repeat_Flag = 0;
uint8 SyncCounter = 0;
volatile uint16 E2E_TimeoutTimer = 0;
const uint16 E2E_TimeoutMax = 22;

E2E_CheckStatusType E2E_Process(uint8 *DataPtr,uint8 E2E_Counter,uint8 E2E_CRC,uint8 E2E_len)
{
	E2E_CheckStatusType status = 0;

	NonewCounter = 0;
	if(15 == E2E_Counter)
	{
		E2E_WrongSeqFlag = 1;
		return E2E_STATUS_WRONGSEQUENCE;
	}

	if(E2E_CRC == CRC8_SAEJ1850_LOOKUP(DataPtr,E2E_len + 2))
	{
	   if(1 == WaitForFirstData)
	   {
		   status = E2E_STATUS_INITIAL;
	   }
	   else
	   {
		   if((E2E_Counter - Last_ReceiveCounter) < 0)
		   {
			   if((14 + E2E_Counter) - Last_ReceiveCounter == 0)
			   {
				  LastValidCounter = E2E_Counter;
				  status = E2E_STATUS_OK;
			   }
			   else if(((14 + E2E_Counter) - Last_ReceiveCounter) <= 3)
			   {
				   LastValidCounter = E2E_Counter;
				   status = E2E_STATUS_OKSOMELOST;
			   }
			   else if((E2E_STATUS_WRONGSEQUENCE == RxGroupID_Sts) && (E2E_TimeoutTimer > E2E_TimeoutMax))
			   {
				   SyncCounter += 1;
				   status = E2E_STATUS_SYNC;
			   }
			   else
			   {
				   E2E_WrongSeqFlag = 1;
				   SyncCounter = 0;
				   status = E2E_STATUS_WRONGSEQUENCE;
			   }
			   E2E_Repeat_Flag = 0;
		   }
		   else
		   {
			   if(E2E_Counter - Last_ReceiveCounter == 0)
				 {
					RepeartCounter++;
					E2E_Repeat_Flag = 1;
					status = E2E_STATUS_REPEATED;
					if(RepeartCounter > MaxNoNewOrRepeatedData)
					{
						E2E_WrongSeqFlag = 1;
						SyncCounter = 0;
						return E2E_STATUS_WRONGSEQUENCE;
					}
				 }
				 else if(E2E_Counter - Last_ReceiveCounter == 1)
				 {
					LastValidCounter = E2E_Counter;
					E2E_Repeat_Flag = 0;
					status = E2E_STATUS_OK;

				 }
				 else if(E2E_Counter - Last_ReceiveCounter <= MaxDeltaCounter)
				 {
					 LastValidCounter = E2E_Counter;
					 E2E_Repeat_Flag = 0;
					 status = E2E_STATUS_OKSOMELOST;

				 }
				 else if((E2E_STATUS_WRONGSEQUENCE == RxGroupID_Sts) && (E2E_TimeoutTimer > E2E_TimeoutMax))
				 {
					 /*receive valid message but counter over MaxDeltaCounter*/
					 /*so recognize this message`s status as sync*/
					 SyncCounter += 1;
					 E2E_Repeat_Flag = 0;
					 status = E2E_STATUS_SYNC;
				 }
				 else
				 {
					   E2E_WrongSeqFlag = 1;
					   E2E_Repeat_Flag = 0;
					   SyncCounter = 0;
					   status = E2E_STATUS_WRONGSEQUENCE;
				 }
		   }

	   }

	}
	else
	{
		E2E_WrongSeqFlag = 1;
		status = E2E_STATUS_WRONGCRC;
	}

	if(E2E_Repeat_Flag == 0)//E2E_STATUS_REPEATED == RxGroupID_Sts && E2E_STATUS_REPEATED != status ||
	{
	   RepeartCounter = 0;
	}

	if((E2E_STATUS_OKSOMELOST == status || E2E_STATUS_OK == status) && ((0 != SyncCounter) || (1 == E2E_WrongSeqFlag)))
	{
		if(SyncCounter <= SyncCounterMax)
		{
			SyncCounter += 1;
			status = E2E_STATUS_SYNC;
			E2E_WrongSeqFlag = 0;
		}
		else
		{
			SyncCounter = 0;
		}

	}
	return status;
}



void E2E_MainFunction(uint32_t FrameID , Bsp_CanRxInit_t* pduInfoPtr)
{
   uint16 index = 0;
   uint16 DataID = 0;
   uint8_t receive_len,receive_crc;
   if(0x1C2 != FrameID)
   {
	   return;
   }
   for(uint8 i = 0 ; i < CANRX_NUM ; i++)
   {
        if(FrameID == g_stBsp_CanRxInit[i].stFLEXCAN_RxFilter.u32RxCanId)
        {
            index = g_stBsp_CanRxInit[i].ui8StartBit_Index;
            break;
        }
   }
   while(FrameID == comSigs[index].FrameId)
   {
       if(comSigs[index].FrameId == 0x1C2 )
       {

           row_start = comSigs[index].start>>3;
           DataID = 0x00C2;
           while (comSigs[index].FrameId == 0x1C2)
           {
               index++;
           }
           uint8 Remainder = (comSigs[--index].start)%8 + 1;
           uint8 LastSigLen = 0;
           if(comSigs[index].len <= Remainder)
           {
               row_end = (comSigs[index].start )>>3;
           }
           else
           {
				LastSigLen = comSigs[index].len - Remainder;
				if(LastSigLen <= 8)
				{
					row_end = ((comSigs[index].start )>>3) + 1;
				}
				else
				{
					row_end = ((comSigs[index].start )>>3) + (LastSigLen/8) + 1;
				}
           }
//           row_end = (comSigs[--index].start + comSigs[--index].len)>>3;
           receive_len = row_end - row_start;
           receive_crc = pduInfoPtr->pui8CanRxBuffer[row_start];
           ReceiveCounter = pduInfoPtr->pui8CanRxBuffer[row_start + 1] & 0x0F;
           receive_arr[0] = DataID & 0x00FF;
           receive_arr[1] = (DataID & 0xFF00)>>8;
           for(uint8_t i = 0; i < receive_len; i++)
           {
               receive_arr[i+2] = pduInfoPtr->pui8CanRxBuffer[++row_start];
           }
           RxGroupID_Sts = E2E_Process(receive_arr,ReceiveCounter,receive_crc,receive_len);
           Last_ReceiveCounter = ReceiveCounter;
       }
       index++;
   }
}


E2E_CheckStatusType E2E_CheckResult(void)
{

	return RxGroupID_Sts;

}


void E2E_WaitForFirstData(uint32 CanId)
{
    if(0x1C2 == CanId)
    {
    	if(0 == WaitForFirstData)
    	{
    		WaitForFirstData = 1;
    	}
    	else
    	{
    		WaitForFirstData = 2;
    	}
    	E2E_TimeoutTimer = 0;

    }
    else
    {}
}



void E2E_TimeoutCheck_1ms(void)
{
	// E2E_TimeoutTimer++;
	if((++E2E_TimeoutTimer)>60000)
	{
		E2E_TimeoutTimer = 60000;
	}
	if(E2E_TimeoutTimer > E2E_TimeoutMax)
	{
		NonewCounter = E2E_TimeoutTimer/E2E_TimeoutMax;
		if(NonewCounter > MaxNoNewOrRepeatedData)
		{
			E2E_WrongSeqFlag = 1;
			SyncCounter = 0;
			RxGroupID_Sts = E2E_STATUS_WRONGSEQUENCE;//超过3帧未更新或重复大于3次
		}
		else
		{
			RxGroupID_Sts = E2E_STATUS_NONEWDATA;
		}
	}

}







