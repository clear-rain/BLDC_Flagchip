/**
 * @file BspClock.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */
#ifndef BSP_CLOCK_H_
#define BSP_CLOCK_H_

#include "main.h"



extern SCG_HandleType g_tScgHandle;
extern void Bsp_ClockInit(void);
extern void Bsp_SCG_Init(void);
extern void Bsp_PCC_Init(void);


#endif	//BSP_CLOCK_H_


