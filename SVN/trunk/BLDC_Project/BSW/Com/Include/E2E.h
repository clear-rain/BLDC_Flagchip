/*
 * E2E.h
 *
 *  Created on: 2024骞�12鏈�31鏃�
 *      Author: 22093
 */

#ifndef BSW_COM_INCLUDE_E2E_H_
#define BSW_COM_INCLUDE_E2E_H_

//#include "Platform_Types.h"
//#include "BspInclude.h"

#include "BspCan.h"

#define ADSFCTSTSSIGGRP_ID 1
#define PODRiREOBSTCGRP_ID 2
#define WHLSTSSIGGRP_ID 3
#define BATTSOCRAWSIGGRP_ID 4
#define BATTURAWSIGGRP_ID 5
#define SPCLROADSURFTYPSIGGRP_ID 6
#define PWRMODSIGGRP_ID 7
#define VCUACTGEARSIGGRP_ID 8

typedef enum {
        E2E_STATUS_OK = 0x00,
        E2E_STATUS_NONEWDATA = 0x1,
        E2E_STATUS_WRONGCRC = 0x2,
        E2E_STATUS_SYNC = 0x03,
        E2E_STATUS_INITIAL = 0x4,
        E2E_STATUS_REPEATED = 0x8,
        E2E_STATUS_OKSOMELOST = 0x20,
        E2E_STATUS_WRONGSEQUENCE = 0x40
} E2E_CheckStatusType;


typedef enum
{
    INVALIDGRP = 0,
    ADSFCTSTSSIGGRP ,
    PODDRVROBSTCGRP,
    PODLEREOBSTCGRP,
    PODPASSOBSTCGRP,
    PODRIREOBSTCGRP,
    WHLSTSSIGGRP,
    BATTURAWSIGGRP,
    BATTSOCRAWSIGGRP,
    SPCLROADSURFTYPSIGGRP,
    PWRMODSIGGRP,
    VCUACTGEARSIGGRP,
	PODDRVRRELSBTN,
	PODLERERELSBTN,
	PODRiRERELSBTN
}E2E_Grp;




#define MaxDeltaCounter 3
#define SyncCounterMax 1
#define MaxNoNewOrRepeatedData 3

extern E2E_CheckStatusType  __attribute__((section(".dtcm_data")))RxGroupID_Sts;

void E2E_TimeoutCheck_1ms(void);
void E2E_WaitForFirstData(uint32 CanId);
E2E_CheckStatusType E2E_CheckResult(void);
uint8_t CRC8_SAEJ1850_LOOKUP(uint8_t* buf, uint8_t len);

void E2E_MainFunction(uint32_t FrameID , Bsp_CanRxInit_t* pduInfoPtr);




#endif /* BSW_COM_INCLUDE_E2E_H_ */
