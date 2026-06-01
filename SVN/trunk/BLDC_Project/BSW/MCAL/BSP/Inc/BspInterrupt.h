/**
 * @file BspInterrupt.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */

#ifndef INC_BSPINTERRUPT_H_
#define INC_BSPINTERRUPT_H_

#include "main.h"
#include "BspGpio.h"

void CAN1_IRQHandler(void);
void CAN2_IRQHandler(void);

extern void Interrupt_Init(void);
void Wakeup_GPIO_Interrupt_Enable(void);
void RTC_IRQHandler(void);
void RTC_Seconds_IRQHandler(void);
void AONTIMER_IRQHandler(void);
void PTIMER0_IRQHandler(void);
void PTIMER1_IRQHandler(void);

#endif /* INC_BSPINTERRUPT_H_ */