/**
 * @file IoHwAb_Dio.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */
#ifndef BSW_ECAL_IOHWAB_INC_IOHWAB_DIO_H_
#define BSW_ECAL_IOHWAB_INC_IOHWAB_DIO_H_

#include "BspGpio.h"

typedef enum{
	ENC_PDRV_IDX,
	ENB_PDRV_IDX,
	ENA_PDRV_IDX,
	VBAT_HALL_CTRL_IDX,
	HSD_DIAG_EN_IDX,
	HSD_2CH_DSEL_IDX,
	NSLEEP_PDRV_IDX,
	VBAT_ENCODER_CTRL_IDX,
	EN_LDO_IDX,
	CAN2_STB_IDX,
	e_IO_OUT_NUM_MAX
}Dio_ChannelOutputType;


typedef enum{
	NFAULT_PDRV_IDX,
	IO_HALL_V_IDX,
	IO_HALL_U_IDX,
	IO_HALL_W_IDX,
	INTN_WPS_IDX,
	IO_KEY_B_WPS_IDX,
	INT1_IAM_8961_WPS_IDX,
	IO_HALL_WPS_IDX,
	IO_KEY_A_WPS_IDX,
	IO_KEY_C_WPS_IDX,
	e_IO_INPUT_NUM_MAX
}Dio_ChannelInputType;

extern Dio_LevelType IoHwAb_Dio_ReadChannel(Dio_ChannelInputType ChannelId);
extern void IoHwAb_Dio_FlipChannel(Dio_ChannelOutputType ChannelId);
extern void IoHwAb_Dio_WriteChannel( Dio_ChannelOutputType ChannelId, Dio_LevelType Level);
extern void Dio_InitWriteChannel(void);

#endif /* BSW_ECAL_IOHWAB_INC_IOHWAB_DIO_H_ */
