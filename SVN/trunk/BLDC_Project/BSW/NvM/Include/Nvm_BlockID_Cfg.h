/*
 * Nvm_BlockID_Cfg.h
 *
 *  Created on: 2024年7月2日
 *      Author: jiang
 */

#ifndef SOURCES_NVM_INCLUDE_NVM_BLOCKID_CFG_H_
#define SOURCES_NVM_INCLUDE_NVM_BLOCKID_CFG_H_

//#define BOOT_NVM_Cfg
#define APP_NVM_CFG

/*common blocks used by boot and app */
#define DID_D01C_NVM_BLOCK_ID           25
#define DID_F109_NVM_BLOCK_ID           26
#define DID_F18A_NVM_BLOCK_ID           43
#define DID_F18C_NVM_BLOCK_ID           34
#define DID_F1AB_NVM_BLOCK_ID           41
#define SecuritySeedCount_NVM_BLOCK_ID  100

#define	SECURITY_NVM_BLOCK_ID_BASE	    (66u)
#define	SECURITY_KEY_NVM_BLOCK_ID	    (SECURITY_NVM_BLOCK_ID_BASE + 0u)
//#define ITGCHK_NVM_BLOCK_ID_0           (SECURITY_NVM_BLOCK_ID_BASE + 1u)
//#define ITGCHK_NVM_BLOCK_ID_1           (SECURITY_NVM_BLOCK_ID_BASE + 2u)
//#define ITGCHK_NVM_BLOCK_ID_2           (SECURITY_NVM_BLOCK_ID_BASE + 3u)
#define	SECURITY_LOG_MAC_NVM_BLOCK_ID	(SECURITY_NVM_BLOCK_ID_BASE + 4u)
#define	SECURITY_LOG_NVM_BLOCK0_ID		(SECURITY_NVM_BLOCK_ID_BASE + 5u)
#define	SECURITY_LOG_NVM_BLOCK1_ID		(SECURITY_NVM_BLOCK_ID_BASE + 6u)
#define	SECURITY_LOG_NVM_BLOCK2_ID		(SECURITY_NVM_BLOCK_ID_BASE + 7u)
#define	SECURITY_LOG_NVM_BLOCK3_ID		(SECURITY_NVM_BLOCK_ID_BASE + 8u)
#define	SECURITY_LOG_NVM_BLOCK4_ID		(SECURITY_NVM_BLOCK_ID_BASE + 9u)
#define	SECURITY_LOG_NVM_BLOCK5_ID		(SECURITY_NVM_BLOCK_ID_BASE + 10u)
#define EVENT_RECORD_MAC_NVM_ID         SECURITY_LOG_MAC_NVM_BLOCK_ID


/*NVM blocks used by boot*/
#ifdef BOOT_NVM_Cfg
#define NvM_BlockNumber        17u


#endif //#define BOOT_NVM_Cfg

/*NVM blocks used by APP*/
#ifdef APP_NVM_CFG


#define BLOCK0_ID_NVM_HALLCOUNT		1u


#define DTC_Controller_DATA_0_BLOCK_ID     0
#define DTC_Controller_DATA_0_BLOCK_SIZE   392

#define DTC_Controller_DATA_1_BLOCK_ID     1
#define DTC_Controller_DATA_1_BLOCK_SIZE   392

#define DTC_Controller_DATA_2_BLOCK_ID     2
#define DTC_Controller_DATA_2_BLOCK_SIZE   392

#define DTC_Controller_DATA_3_BLOCK_ID     3
#define DTC_Controller_DATA_3_BLOCK_SIZE   392

#define DTC_Controller_DATA_4_BLOCK_ID     4
#define DTC_Controller_DATA_4_BLOCK_SIZE   392

#define DTC_Controller_DATA_5_BLOCK_ID     5
#define DTC_Controller_DATA_5_BLOCK_SIZE   392

#define DTC_Controller_DATA_6_BLOCK_ID     6
#define DTC_Controller_DATA_6_BLOCK_SIZE   392

#define DTC_Controller_DATA_7_BLOCK_ID     7
#define DTC_Controller_DATA_7_BLOCK_SIZE   392

#define DTC_Controller_DATA_8_BLOCK_ID     8
#define DTC_Controller_DATA_8_BLOCK_SIZE   392

#define DTC_Controller_DATA_9_BLOCK_ID     9
#define DTC_Controller_DATA_9_BLOCK_SIZE   392

#define DTC_Controller_DATA_10_BLOCK_ID    10
#define DTC_Controller_DATA_10_BLOCK_SIZE  392

#define DTC_Controller_DATA_11_BLOCK_ID    11
#define DTC_Controller_DATA_11_BLOCK_SIZE  392

#define dataSnapShot2003_BLOCK_ID          12
#define dataSnapShot2003_BLOCK_SIZE        80

#define dataSnapShot2004_BLOCK_ID          13
#define dataSnapShot2004_BLOCK_SIZE        120

#define dataSnapShot2005_BLOCK_ID          14
#define dataSnapShot2005_BLOCK_SIZE        72

#define dataSnapShot2006_BLOCK_ID          15
#define dataSnapShot2006_BLOCK_SIZE        104

#define dataSnapShot2007_BLOCK_ID          16
#define dataSnapShot2007_BLOCK_SIZE        72

#define dataSnapShot2008_BLOCK_ID          17
#define dataSnapShot2008_BLOCK_SIZE        72

#define dataSnapShot2009_BLOCK_ID          18
#define dataSnapShot2009_BLOCK_SIZE        120

#define securityErrorCounter_BLOCK_ID      19
#define securityErrorCounter_BLOCK_SIZE    8


#define NVM_DTC_Reserved11_BLOCK_ID        20
#define NVM_DTC_Reserved11_BLOCK_SIZE      96

#define NVM_DTC_Reserved12_BLOCK_ID        21
#define NVM_DTC_Reserved12_BLOCK_SIZE      96

#define NVM_DTC_Reserved13_BLOCK_ID        22
#define NVM_DTC_Reserved13_BLOCK_SIZE      96

#define NVM_DTC_Reserved14_BLOCK_ID        23
#define NVM_DTC_Reserved14_BLOCK_SIZE      96

#define NVM_DTC_Reserved15_BLOCK_ID        24
#define NVM_DTC_Reserved15_BLOCK_SIZE      96


#define DID_F120_block                     27
#define DID_F120_block_SIZE                16

#define DID_F121_block                     28
#define DID_F121_block_SIZE                16

#define DID_F124_block                     29
#define DID_F124_block_SIZE                16

#define DID_F125_block                     30
#define DID_F125_block_SIZE                16

#define DID_F12A_block                     31
#define DID_F12A_block_SIZE                16

#define DID_F12B_block                     32
#define DID_F12B_block_SIZE                16

#define DID_F12E_block                     33
#define DID_F12E_block_SIZE                16

#define DID_F190_block                     35
#define DID_F190_block_SIZE                24

#define DID_F1A0_block                     36
#define DID_F1A0_block_SIZE                16

#define DID_F1A1_block                     37
#define DID_F1A1_block_SIZE                16

#define DID_F1A2_block                     38
#define DID_F1A2_block_SIZE                16

#define DID_F1A5_block                     39
#define DID_F1A5_block_SIZE                16

#define DID_F1AA_block                     40
#define DID_F1AA_block_SIZE                16

#define DID_F1AE_block                     42
#define DID_F1AE_block_SIZE                24

#define DID_F18A_block                     43
#define DID_F18A_block_SIZE                sizeof(DID_Address_19)

#define NVM_AppSwcData_BLOCK_ID            45
#define NVM_AppSwcData_BLOCK_SIZE          sizeof(NVM_AppSwcData)

#define DID_F1F0_block                     57
#define DID_F1F0_block_SIZE                8

#define DTC_Controller_DATA_12_BLOCK_ID    58
#define DTC_Controller_DATA_12_BLOCK_SIZE  392

#define DTC_Controller_DATA_13_BLOCK_ID    59
#define DTC_Controller_DATA_13_BLOCK_SIZE  392

#define DTC_Controller_DATA_14_BLOCK_ID    60
#define DTC_Controller_DATA_14_BLOCK_SIZE  392

#define DTC_Controller_DATA_15_BLOCK_ID    61
#define DTC_Controller_DATA_15_BLOCK_SIZE  392

#define dataSnapShot2001_BLOCK_ID          62
#define dataSnapShot2001_BLOCK_SIZE        72

#define dataSnapShot2002_BLOCK_ID          63
#define dataSnapShot2002_BLOCK_SIZE        120

#define DTC_Controller_DATA_16_BLOCK_ID    64
#define DTC_Controller_DATA_16_BLOCK_SIZE  392

#define DTC_Controller_DATA_17_BLOCK_ID    65
#define DTC_Controller_DATA_17_BLOCK_SIZE  392

#define NVM_AppResetData_ID                88

#endif //#ifdef APP_NVM_CFG







#endif /* SOURCES_NVM_INCLUDE_NVM_BLOCKID_CFG_H_ */
