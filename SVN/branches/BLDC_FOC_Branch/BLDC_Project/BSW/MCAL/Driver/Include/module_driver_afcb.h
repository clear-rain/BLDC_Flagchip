/**
 * @file module_driver_afcb.h
 * @author Flagchip095
 * @brief FACB driver type definition and API
 * @version 2.0.0
 * @date 2024-03-09
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_AFCB_H_
#define _DRIVER_MODULE_DRIVER_AFCB_H_

#include "HwA_afcb.h"

#if AFCB_INSTANCE_COUNT > 0U

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup module_driver_afcb
 * @{
 */

/**
 * @name  AFCB API Service IDs
 *
 * @{
 */
#define AFCB_MASTER_TR_ID                0U
#define AFCB_MASTER_TW_ID                1U
#define AFCB_MASTER_PL_ID                2U
#define AFCB_MASTER_ACCESS_ID            3U
#define AFCB_MASTER_CONFIG_ID            4U
#define AFCB_SLAVE_SP_ID                 5U
#define AFCB_SLAVE_WP_ID                 6U
#define AFCB_SLAVE_TP_ID                 7U
#define AFCB_SLAVE_PROTECT_ID            8U
#define AFCB_SLAVE_CONFIG_ID             9U
/** @}*/

/**
 * @name  AFCB Dev Error Code
 * @brief Error Code of calling AFCB apis
 *
 * @{
 */
#define AFCB_E_PARAM_MASTER		   		0x01U
#define AFCB_E_PARAM_SLAVE   			0x02U
/** @}*/

/**
 * @brief Master Mapping Table
 *
 */
typedef enum
{
	M_CPU   = 0U,
	M_DEBUG = 1U,
	M_DMA   = 2U,
	M_ENET  = 3U,
	M_HSM   = 4U,
	MAST_MAX,
}Afcb_Master_Type;

/**
 * @brief Slave Mapping Table
 *
 */
typedef enum
{
	S0_AFCB0       = 0U,
	S0_DMA         = 8U,
	S0_DMACFG      = 9U,
	S0_MAP         = 13U,
	S0_SEC         = 20U,
	S0_ERM         = 24U,
	S0_EIM         = 25U,
	S0_INTM        = 26U,
	S0_ISM0        = 27U,
	S0_FMC         = 30U,
	S1_FC          = 32U + 0U,
	S1_DMAMUX      = 32U + 1U,
	S1_FTU3        = 32U + 6U,
	S1_ADC1        = 32U + 7U,
	S1_FCSPI0      = 32U + 12U,
	S1_FCSPI1      = 32U + 13U,
	S1_FCSPI2      = 32U + 14U,
	S1_FCSPI3      = 32U + 15U,
	S1_PTIMER1     = 32U + 17U,
	S1_CRC         = 32U + 18U,
	S1_PTIMER0     = 32U + 22U,
	S1_FCPIT0      = 32U + 23U,
	S1_FTU0        = 32U + 24U,
	S1_FTU1        = 32U + 25U,
	S1_FTU2        = 32U + 26U,
	S1_ADC0        = 32U + 27U,
	S1_RTC         = 32U + 29U,
	S1_CMU0        = 32U + 30U,
	S1_CMU1        = 32U + 31U,
	S1_AONTIMER0   = 32U + 32U,
	S1_CMU2        = 32U + 35U,
	S1_CMU3        = 32U + 36U,
	S1_SMISC       = 32U + 40U,
	S1_PoreA       = 32U + 41U,
	S1_PortB       = 32U + 42U,
	S1_PortC       = 32U + 43U,
	S1_PortD       = 32U + 44U,
	S1_PortE       = 32U + 45U,
	S1_WKU0        = 32U + 47U,
	S1_WDOG0       = 32U + 50U,
	S1_WDOG1       = 32U + 51U,
	S1_I2S0        = 32U + 52U,
	S1_I2S1        = 32U + 53U,
	S1_FTU6        = 32U + 54U,
	S1_FTU7        = 32U + 55U,
	S1_FCUART3     = 32U + 59U,
	S1_FCUART4     = 32U + 60U,
	S1_FCUART5     = 32U + 61U,
	S1_FWM         = 32U + 65U,
	S1_TRGSEL0     = 32U + 66U,
	S1_TRGSEL1     = 32U + 67U,
	S1_SCG         = 32U + 68U,
	S1_PCC         = 32U + 69U,
	S1_FCIIC0      = 32U + 70U,
	S1_FCIIC1      = 32U + 71U,
	S1_FCUART0     = 32U + 74U,
	S1_FCUART1     = 32U + 75U,
	S1_FCUART2     = 32U + 76U,
	S1_FTU4        = 32U + 78U,
	S1_FTU5        = 32U + 79U,
	S1_LU0         = 32U + 80U,
	S1_TRGSEL2     = 32U + 81U,
	S1_TRGSEL3     = 32U + 82U,
	S1_CMP0        = 32U + 83U,
	S1_CMP1        = 32U + 84U,
	S1_CMP2        = 32U + 85U,
	S1_OSPI        = 32U + 86U,
	S1_ENET        = 32U + 88U,
	S1_ENET_1      = 32U + 89U,
	S1_TSTMP1      = 32U + 92U,
	S1_PMC         = 32U + 93U,
	S1_SMC         = 32U + 94U,
	S1_RCM         = 32U + 95U,
	S1_FLEXCAN0    = 32U + 96U,
	S1_FLEXCAN0_1  = 32U + 97U,
	S1_FLEXCAN0_2  = 32U + 98U,
	S1_FLEXCAN0_3  = 32U + 99U,
	S1_FLEXCAN1    = 32U + 100U,
	S1_FLEXCAN1_1  = 32U + 101U,
	S1_FLEXCAN1_2  = 32U + 102U,
	S1_FLEXCAN1_3  = 32U + 103U,
	S1_FLEXCAN2    = 32U + 104U,
	S1_FLEXCAN2_1  = 32U + 105U,
	S1_FLEXCAN2_2  = 32U + 106U,
	S1_FLEXCAN2_3  = 32U + 107U,
	S1_FLEXCAN3_4  = 32U + 108U,
	S1_FLEXCAN4    = 32U + 112U,
	S1_FLEXCAN4_1  = 32U + 113U,
	S1_FLEXCAN4_2  = 32U + 114U,
	S1_FLEXCAN4_3  = 32U + 115U,
	S1_FLEXCAN5    = 32U + 116U,
	S1_FLEXCAN5_1  = 32U + 117U,
	S1_FLEXCAN5_2  = 32U + 118U,
	S1_FLEXCAN5_3  = 32U + 119U,
	S1_HSM         = 32U + 120U,
	S1_HSM_1       = 32U + 121U,
	S1_HSM_2       = 32U + 122U,
	S1_HSM_3       = 32U + 123U,
	SLAVE_MAX      = 32U + 128U,
}Afcb_SlaveSlot_Type;

/**
 * @brief  Trusted For Read Status
 *
 */
typedef enum
{
	NOTTRUSTED_FOR_READ = 0U,
	TRUSTED_FOR_READ    = 1U,
}Master_TR_Status;

/**
 * @brief  Trusted For Write Status
 *
 */
typedef enum
{
	NOTTRUSTED_FOR_WRITE = 0U,
	TRUSTED_FOR_WRITE    = 1U,
}Master_WR_Status;

/**
 * @brief  Privilege Level Status
 *
 */
typedef enum
{
	USER_MODE    = 0U,
	KEEP_ORI_PRI = 1U,
}Master_Pri_Level;

/**
 * @brief  Supervisor Protect Status
 *
 */
typedef enum
{
	NOT_SUPER_PROTECT = 0U,
	SUPER_PROTECT     = 1U,
}Slave_SP_Status;

/**
 * @brief  Write Protect Status
 *
 */
typedef enum
{
	NOT_WRITE_PROTECT = 0U,
	WRITE_PROTECT     = 1U,
}Slave_WP_Status;

/**
 * @brief  Trusted Protect Status
 *
 */
typedef enum
{
	ALLOWACCESS_FROM_UNTRUSTED_MASTER     = 0U,
	NOT_ALLOWACCESS_FROM_UNTRUSTED_MASTER = 1U,
}Slave_TP_Status;


/**
 * @brief Config Master Access Attribute
 *
 * @param mstSrc Master type according map table
 * @param trStatus the status of Trusted For Read.
 * @param wrStatus the status of Trusted For Write.
 * @param priLevel the Privilege Level of Master.
 */
void AFCB_ConfigMasterAccessAttribute(const Afcb_Master_Type mstSrc, const Master_TR_Status trStatus, const Master_WR_Status wrStatus, const Master_Pri_Level priLevel);

/**
 * @brief Get Config Info of Master Access Attribute
 *
 * @param mstSrc Master type according map table
 * @return the config value of mstSrc
 */
uint32_t AFCB_GetMasterConfig(const Afcb_Master_Type mstSrc);

/**
 * @brief Config Peripheral Access Protection
 *
 * @param slaSrc Slave type according map table
 * @param spStatus the status of Supervisor Protect.
 * @param wpStatus the status of Write Protect.
 * @param tpStatus the status of Trusted Protect..
 */
void AFCB_ConfigSlaveAccessProtection(const Afcb_SlaveSlot_Type slaSrc, const Slave_SP_Status spStatus, const Slave_WP_Status wpStatus, const Slave_TP_Status tpStatus);

/**
 * @brief Get Config Info of Peripheral Access Protection
 *
 * @param slaSrc Slave type according map table
 * @return config value of slaSrc
 */
uint32_t AFCB_GetSlaveConfig(const Afcb_SlaveSlot_Type slaSrc);

/**
 * @brief Config  Trusted Protect Of Slave
 *
 * @param slaSrc Slave type according map table
 * @param tpStatus the status of Trusted Protect.
 */
void AFCB_ConfigSlaveTP(const Afcb_SlaveSlot_Type slaSrc, const Slave_TP_Status tpStatus);

/**
 * @brief Config  Write Protect Of Slave
 *
 * @param slaSrc Slave type according map table
 * @param wpStatus the status of  Write Protect.
 */
void AFCB_ConfigSlaveWP(const Afcb_SlaveSlot_Type slaSrc, const Slave_WP_Status wpStatus);

/**
 * @brief Config Supervisor Protect Of Slave
 *
 * @param slaSrc Slave type according map table
 * @param spStatus the status of Supervisor Protect.
 */
void AFCB_ConfigSlaveSP(const Afcb_SlaveSlot_Type slaSrc, const Slave_SP_Status spStatus);

/**
 * @brief Config Master Privilege Level
 *
 * @param mstSrc Master type according map table
 * @param pl the Privilege Level of Master.
 */
void AFCB_ConfigMasterPL(const Afcb_Master_Type mstSrc, const Master_Pri_Level pl);

/**
 * @brief Config Master Trusted For Write Attribute
 *
 * @param mstSrc Master type according map table
 * @param wrStatus the status of Trusted For Write.
 */
void AFCB_ConfigMasterTW(const Afcb_Master_Type mstSrc, const Master_WR_Status wrStatus);

/**
 * @brief Config Master Trusted For Read Attribute
 *
 * @param mstSrc Master type according map table
 * @param trStatus the status of Trusted For Read.
 */
void AFCB_ConfigMasterTR(const Afcb_Master_Type mstSrc, const Master_TR_Status trStatus);

#if defined(__cplusplus)
}

#endif

/** @}*/

#endif

#endif
