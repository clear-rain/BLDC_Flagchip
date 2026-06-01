/*
 * MotorDriver_Cfg.c
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */

#include "MotorDriver_Cfg.h"

//
//typedef union{
//	uint16_t RegData;
//	struct{
//		uint16_t Address:3;
//		uint16_t ReadWrite:1;
//		uint16_t data:12;
//	}bit;
//}MotorDriver_SPI_Reg_T;

MotorDriver_SPI_RegTXD_T MotorDriver_SPI_RegTXD[MOTORDRIVER_SPIREG_NUM]=
{
	{.bit.address=000, .bit.readORwrite=SPI_REG_WRITE, .bit.data = 0x000},
	{.bit.address=001, .bit.readORwrite=SPI_REG_WRITE, .bit.data = 0x46F},
	{.bit.address=002, .bit.readORwrite=SPI_REG_WRITE, .bit.data = 0x46F},
	{.bit.address=003, .bit.readORwrite=SPI_REG_WRITE, .bit.data = 0x46F},
	{.bit.address=004, .bit.readORwrite=SPI_REG_WRITE, .bit.data = 0x923},
};

MotorDriver_SPI_RegTXD_T MotorDriver_SPI_RegTXD_Read[MOTORDRIVER_SPIREG_NUM]=
{
	{.bit.address=000, .bit.readORwrite=SPI_REG_READ, .bit.data = 0x0000},
	{.bit.address=001, .bit.readORwrite=SPI_REG_READ, .bit.data = 0x0000},
	{.bit.address=002, .bit.readORwrite=SPI_REG_READ, .bit.data = 0x0000},
	{.bit.address=003, .bit.readORwrite=SPI_REG_READ, .bit.data = 0x0000},
	{.bit.address=004, .bit.readORwrite=SPI_REG_READ, .bit.data = 0x0000},
};

MotorDriver_SPI_RegRXD_T MotorDriver_SPI_RegRXD[MOTORDRIVER_SPIREG_NUM];

//
//TLE9210X_SPI_Frame TLE92104_All_CTRL_REG_SPI_Frame_Table[TLE92104_All_CTRL_REG_COUNT] = {
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, GENCTRL1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, GENCTRL2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, VDS1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, CCP_BLK1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, CCP_BLK2_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, CCP_BLK2_FW_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, HBMODE_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWMSET_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, TPRECHG_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, HBIDIAG_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, ST_ICHG_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWM_PCHG_INIT_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWM_ICHG_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWM_ICHG_FW_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWM_IDCHG_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWM_PDCHG_INIT_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWM_ICHGMAX_CCP_BLK3_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, PWM_ICHGMAX_CCP_BLK3_FW_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, TDON_OFF1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, TDON_OFF2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, TDON_OFF3_ADDR, LABT_Bit, MSB_Bit),
//};
//
//TLE9210X_SPI_Frame TLE92104_BANK0_CTRL_REG_SPI_Frame_Table[TLE92104_BANK0_CTRL_Registers_Send_Count] = {
//    INIT_SPI_MESSAGE(0x35a7, OP_Read_And_WriteOrClear_Bit, GENCTRL1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x03b7, OP_Read_And_WriteOrClear_Bit, GENCTRL2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0b6d, OP_Read_And_WriteOrClear_Bit, VDS1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, CCP_BLK1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x4936, OP_Read_And_WriteOrClear_Bit, CCP_BLK2_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, HBMODE_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0643, OP_Read_And_WriteOrClear_Bit, PWMSET_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, TPRECHG_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0xd400, OP_Read_And_WriteOrClear_Bit, HBIDIAG_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, ST_ICHG_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x294A, OP_Read_And_WriteOrClear_Bit, PWM_ICHG_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x2D6B, OP_Read_And_WriteOrClear_Bit, PWM_IDCHG_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x4900, OP_Read_And_WriteOrClear_Bit, PWM_ICHGMAX_CCP_BLK3_ACT_REG_BANK_0_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0a0a, OP_Read_And_WriteOrClear_Bit, TDON_OFF1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0a0a, OP_Read_And_WriteOrClear_Bit, TDON_OFF2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0a0a, OP_Read_And_WriteOrClear_Bit, TDON_OFF3_ADDR, LABT_Bit, MSB_Bit),
//};
//
//TLE9210X_SPI_Frame TLE92104_BANK1_CTRL_REG_SPI_Frame_Table[TLE92104_BANK1_CTRL_Registers_Send_Count] = {
////    INIT_SPI_MESSAGE(0x37a7, OP_Read_And_WriteOrClear_Bit, GENCTRL1_ADDR, LABT_Bit, MSB_Bit),
//	INIT_SPI_MESSAGE(0x3da7, OP_Read_And_WriteOrClear_Bit, GENCTRL1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x03b7, OP_Read_And_WriteOrClear_Bit, GENCTRL2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0b6d, OP_Read_And_WriteOrClear_Bit, VDS1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, CCP_BLK1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x4936, OP_Read_And_WriteOrClear_Bit, CCP_BLK2_FW_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, HBMODE_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, TPRECHG_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0xd400, OP_Read_And_WriteOrClear_Bit, HBIDIAG_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x18c6, OP_Read_And_WriteOrClear_Bit, PWM_PCHG_INIT_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x294A, OP_Read_And_WriteOrClear_Bit, PWM_ICHG_FW_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x2D6B, OP_Read_And_WriteOrClear_Bit, PWM_PDCHG_INIT_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x4900, OP_Read_And_WriteOrClear_Bit, PWM_ICHGMAX_CCP_BLK3_FW_REG_BANK_1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0a0a, OP_Read_And_WriteOrClear_Bit, TDON_OFF1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0a0a, OP_Read_And_WriteOrClear_Bit, TDON_OFF2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0a0a, OP_Read_And_WriteOrClear_Bit, TDON_OFF3_ADDR, LABT_Bit, MSB_Bit),
//};
//
//
//TLE9210X_SPI_Frame TLE92104_All_STAT_REG_SPI_Frame_Table[TLE92104_All_STAT_REG_COUNT] = {
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, GENSTAT_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, DSOV_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, HBVOUT_PWMERR_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, EFF_TDON_OFF1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, EFF_TDON_OFF2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, EFF_TDON_OFF3_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, TRISE_FALL1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, TRISE_FALL2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, TRISE_FALL3_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, DEVID_ADDR, LABT_Bit, MSB_Bit),
//};
//
//TLE9210X_SPI_Frame TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[TLE92104_Usual_Use_CTRL_Registers_Count] ={
//    INIT_SPI_MESSAGE(0x35a7, OP_Read_And_WriteOrClear_Bit, GENCTRL1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x03b7, OP_Read_And_WriteOrClear_Bit, GENCTRL2_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0b6d, OP_Read_And_WriteOrClear_Bit, VDS1_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_And_WriteOrClear_Bit, HBMODE_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0xd400, OP_Read_And_WriteOrClear_Bit, HBIDIAG_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, GENSTAT_ADDR, LABT_Bit, MSB_Bit),
//    INIT_SPI_MESSAGE(0x0000, OP_Read_Only_Bit, DSOV_ADDR, LABT_Bit, MSB_Bit),
//};
