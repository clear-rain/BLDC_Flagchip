/**
 * @file IoHwAb_Dio.c
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */


#include <IoHwAb_Dio.h>
extern PORT_InstanceType tPortOutBuff[];
extern uint32_t tPinOutBuff[];

extern PORT_InstanceType tPortInBuff[];
extern uint32_t tPinInBuff[];

/**
 * @brief 
 * @param  ChannelId        My Param doc
 * @param  Level            My Param doc
 */
void IoHwAb_Dio_WriteChannel(Dio_ChannelOutputType ChannelId, Dio_LevelType Level)
{
	if (e_IO_OUT_NUM_MAX <= ChannelId)
	{
		return;
	}
	GPIO_WritePins(tPortOutBuff[ChannelId], tPinOutBuff[ChannelId], Level);
}

/**
 * @brief 
 * @param  ChannelId        My Param doc
 * @return Dio_LevelType 
 */
Dio_LevelType IoHwAb_Dio_ReadChannel(Dio_ChannelInputType ChannelId)
{
	if (e_IO_INPUT_NUM_MAX <= ChannelId)
	{
		return DIO_STD_LOW;
	}
	if(GPIO_ReadPins(tPortInBuff[ChannelId], tPinInBuff[ChannelId]))
	{
		return DIO_STD_HIGH;
	}
	return DIO_STD_LOW;
}

/**
 * @brief 
 * @param  ChannelId        My Param doc
 * @return Dio_LevelType 
 */
void IoHwAb_Dio_FlipChannel(Dio_ChannelOutputType ChannelId)
{
	if (e_IO_OUT_NUM_MAX <= ChannelId)
	{
		return ;
	}
	GPIO_Toggle(tPortOutBuff[ChannelId], tPinOutBuff[ChannelId]);
}






