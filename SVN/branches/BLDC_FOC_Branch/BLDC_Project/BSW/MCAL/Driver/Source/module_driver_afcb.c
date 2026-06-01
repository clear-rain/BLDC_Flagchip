/**
 * @file module_driver_afcb.c
 * @author Flagchip095
 * @brief AFCB driver source code
 * @version 2.0.0
 * @date 2024-03-09
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#include "module_driver_afcb.h"

#if AFCB_INSTANCE_COUNT > 0U

#ifndef AFCB_DEV_ERROR_REPORT
#define AFCB_DEV_ERROR_REPORT	STD_OFF
#endif

#if AFCB_DEV_ERROR_REPORT == STD_ON
#define AFCB_ReportDevError(func, error) ReportDevError(AFCB_MODULE_ID, func, error)
#endif

/********* Local Variables ************/
static AFCB_Type *const s_pAFCB_Instance = AFCB;

/**
 * @brief Config Master Trusted For Read Attribute
 *
 * @param mstSrc Master type according map table
 * @param trStatus the status of Trusted For Read.
 */
void AFCB_ConfigMasterTR(const Afcb_Master_Type mstSrc, const Master_TR_Status trStatus)
{
#if AFCB_DEV_ERROR_REPORT == STD_ON
    if (mstSrc >= MAST_MAX)
    {
        AFCB_ReportDevError(AFCB_MASTER_TR_ID, AFCB_E_PARAM_MASTER);
    }
    else
    {
#endif
		uint8_t bit_shift = (uint8_t)(4*(7-(uint32_t)mstSrc) + 2);
		if(trStatus == TRUSTED_FOR_READ)
		{
			AFCB_HWA_SetMarrBit(s_pAFCB_Instance,bit_shift);
		}
		else
		{
			AFCB_HWA_ClearMarrBit(s_pAFCB_Instance,bit_shift);
		}
#if AFCB_DEV_ERROR_REPORT == STD_ON        
    }
#endif
}

/**
 * @brief Config Master Trusted For Write Attribute
 *
 * @param mstSrc Master type according map table
 * @param wrStatus the status of Trusted For Write.
 */
void AFCB_ConfigMasterTW(const Afcb_Master_Type mstSrc, const Master_WR_Status wrStatus)
{
	uint8_t bit_shift = (uint8_t)(4*(7-(uint32_t)mstSrc) + 1);
	if(wrStatus == TRUSTED_FOR_WRITE)
	{
		AFCB_HWA_SetMarrBit(s_pAFCB_Instance,bit_shift);
	}
	else
	{
		AFCB_HWA_ClearMarrBit(s_pAFCB_Instance,bit_shift);
	}
}

/**
 * @brief Config Master Privilege Level
 *
 * @param mstSrc Master type according map table
 * @param pl the Privilege Level of Master.
 */
void AFCB_ConfigMasterPL(const Afcb_Master_Type mstSrc, const Master_Pri_Level pl)
{
	uint8_t bit_shift = (uint8_t)(4*(7-(uint32_t)mstSrc));
	if(pl == KEEP_ORI_PRI)
	{
		AFCB_HWA_SetMarrBit(s_pAFCB_Instance,bit_shift);
	}
	else
	{
		AFCB_HWA_ClearMarrBit(s_pAFCB_Instance,bit_shift);
	}
}

/**
 * @brief Config Master Access Attribute
 *
 * @param mstSrc Master type according map table
 * @param trStatus the status of Trusted For Read.
 * @param wrStatus the status of Trusted For Write.
 * @param priLevel the Privilege Level of Master.
 */
void AFCB_ConfigMasterAccessAttribute(const Afcb_Master_Type mstSrc, const Master_TR_Status trStatus, const Master_WR_Status wrStatus, const Master_Pri_Level priLevel)
{
	AFCB_ConfigMasterTR(mstSrc,trStatus);
	AFCB_ConfigMasterPL(mstSrc,priLevel);
	AFCB_ConfigMasterTW(mstSrc,wrStatus);
}

/**
 * @brief Get Config Info of Master Access Attribute
 *
 * @param mstSrc Master type according map table
 * @return the config value of mstSrc
 */
uint32_t AFCB_GetMasterConfig(const Afcb_Master_Type mstSrc)
{
	uint32_t config_data = 0;
	uint8_t bit_shift = (uint8_t)(4*(7-(uint32_t)mstSrc));
	config_data = AFCB_HWA_GetMARR0(s_pAFCB_Instance);
	config_data = ((config_data & (uint32_t)(7<<bit_shift))>>bit_shift);
	return config_data;
}

/**
 * @brief Config Supervisor Protect Of Slave
 *
 * @param slaSrc Slave type according map table
 * @param spStatus the status of Supervisor Protect.
 */
void AFCB_ConfigSlaveSP(const Afcb_SlaveSlot_Type slaSrc, const Slave_SP_Status spStatus)
{
	uint8_t slv_register_index = slaSrc/8;
	uint8_t slv_bit_shift = (uint8_t)((7-slaSrc%8)*4 + 2);
	if(slaSrc < S1_FC)
	{
		if(spStatus==SUPER_PROTECT)
		{
			AFCB_HWA_SetSEG0PAPBit(s_pAFCB_Instance, slv_register_index,slv_bit_shift);
		}
		else
		{
			AFCB_HWA_ClearSEG0PAPBit(s_pAFCB_Instance,slv_register_index,slv_bit_shift);
		}
	}
	else
	{
		if(spStatus==SUPER_PROTECT)
		{
			AFCB_HWA_SetSEG1PAPBit(s_pAFCB_Instance, (uint8_t)(slv_register_index-4),slv_bit_shift);
		}
		else
		{
			AFCB_HWA_ClearSEG1PAPBit(s_pAFCB_Instance, (uint8_t)(slv_register_index-4),slv_bit_shift);
		}
	}
}

/**
 * @brief Config  Write Protect Of Slave
 *
 * @param slaSrc Slave type according map table
 * @param wpStatus the status of  Write Protect.
 */
void AFCB_ConfigSlaveWP(const Afcb_SlaveSlot_Type slaSrc, const Slave_WP_Status wpStatus)
{
	uint8_t slv_register_index = slaSrc/8;
	uint8_t slv_bit_shift = (uint8_t)((7-slaSrc%8)*4 + 1);
	if(slaSrc < S1_FC)
	{
		if(wpStatus==WRITE_PROTECT)
		{
			AFCB_HWA_SetSEG0PAPBit(s_pAFCB_Instance, slv_register_index,slv_bit_shift);
		}
		else
		{
			AFCB_HWA_ClearSEG0PAPBit(s_pAFCB_Instance,slv_register_index,slv_bit_shift);
		}
	}
	else
	{
		if(wpStatus==WRITE_PROTECT)
		{
			AFCB_HWA_SetSEG1PAPBit(s_pAFCB_Instance, (uint8_t)(slv_register_index-4),slv_bit_shift);
		}
		else
		{
			AFCB_HWA_ClearSEG1PAPBit(s_pAFCB_Instance, (uint8_t)(slv_register_index-4),slv_bit_shift);
		}
	}
}

/**
 * @brief Config  Trusted Protect Of Slave
 *
 * @param slaSrc Slave type according map table
 * @param tpStatus the status of Trusted Protect.
 */
void AFCB_ConfigSlaveTP(const Afcb_SlaveSlot_Type slaSrc,const Slave_TP_Status tpStatus)
{
	uint8_t slv_register_index = slaSrc/8;
	uint8_t slv_bit_shift = (uint8_t)((7-slaSrc%8)*4);
	if(slaSrc < S1_FC)
	{
		if(tpStatus==NOT_ALLOWACCESS_FROM_UNTRUSTED_MASTER)
		{
			AFCB_HWA_SetSEG0PAPBit(s_pAFCB_Instance, slv_register_index,slv_bit_shift);
		}
		else
		{
			AFCB_HWA_ClearSEG0PAPBit(s_pAFCB_Instance,slv_register_index,slv_bit_shift);
		}
	}
	else
	{
		if(tpStatus==NOT_ALLOWACCESS_FROM_UNTRUSTED_MASTER)
		{
			AFCB_HWA_SetSEG1PAPBit(s_pAFCB_Instance, (uint8_t)(slv_register_index-4),slv_bit_shift);
		}
		else
		{
			AFCB_HWA_ClearSEG1PAPBit(s_pAFCB_Instance, (uint8_t)(slv_register_index-4),slv_bit_shift);
		}
	}
}


/**
 * @brief Config Peripheral Access Protection
 *
 * @param slaSrc Slave type according map table
 * @param spStatus the status of Supervisor Protect.
 * @param wpStatus the status of Write Protect.
 * @param tpStatus the status of Trusted Protect..
 */
void AFCB_ConfigSlaveAccessProtection(const Afcb_SlaveSlot_Type slaSrc,const Slave_SP_Status spStatus,const Slave_WP_Status wpStatus,const Slave_TP_Status tpStatus)
{
	uint32_t set_value = 0U;
	uint32_t reg_val = 0U;
	uint8_t slv_register_index = slaSrc/8;
	uint8_t slv_bit_shift = (uint8_t)((7-slaSrc%8)*4);
	set_value = (((uint32_t)spStatus) | (((uint32_t)wpStatus)<<1) | (((uint32_t)tpStatus)<<2))<<slv_bit_shift;
	if(slaSrc < S1_FC)
	{
		reg_val = AFCB_HWA_ReadSEG0PAP(s_pAFCB_Instance, slv_register_index);
		set_value = (reg_val & (uint32_t)(~(7<<slv_bit_shift)))|set_value;
		AFCB_HWA_SetSEG0PAP(s_pAFCB_Instance,slv_register_index,set_value);
	}
	else
	{
		reg_val = AFCB_HWA_ReadSEG1PAP(s_pAFCB_Instance, (uint8_t)(slv_register_index-4));
		set_value = (reg_val & (uint32_t)(~(7<<slv_bit_shift)))|set_value;
		AFCB_HWA_SetSEG1PAP(s_pAFCB_Instance,(uint8_t)(slv_register_index-4),set_value);
	}
}

/**
 * @brief Get Config Info of Peripheral Access Protection
 *
 * @param slaSrc Slave type according map table
 * @return config value of slaSrc
 */
uint32_t AFCB_GetSlaveConfig(const Afcb_SlaveSlot_Type slaSrc)
{
	uint32_t config_data = 0;
	uint8_t slv_register_index = slaSrc/8;
	uint8_t slv_bit_shift = (uint8_t)((7-slaSrc%8)*4);
	if(slaSrc < S1_FC)
	{
		config_data = AFCB_HWA_ReadSEG0PAP(s_pAFCB_Instance,slv_register_index);
		config_data = (config_data &(uint32_t)(7<<slv_bit_shift))>>slv_bit_shift;
	}
	else
	{
		config_data = AFCB_HWA_ReadSEG1PAP(s_pAFCB_Instance,(uint8_t)(slv_register_index-4));
		config_data = (config_data &(uint32_t)(7<<slv_bit_shift))>>slv_bit_shift;
	}
	return config_data;
}

#endif
