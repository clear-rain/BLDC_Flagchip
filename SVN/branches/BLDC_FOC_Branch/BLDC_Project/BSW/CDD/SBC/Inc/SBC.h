/**
 * @file SBC.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-02 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */
#ifndef _SBC_H_ 
#define _SBC_H_
#include "main.h"
// #include "Platform.h"
#include "SBC_Types.h"

extern E_CDD_SBC_ERR_STATUS Cdd_SbcModeSet(E_CDD_SBC_MODE e_mode);
extern uint8_t Cdd_SbcResetReasonGet(void);
extern uint8_t Cdd_SbcWkStat0Get(void);
extern uint8_t Cdd_SbcWkStat1Get(void);
extern void Cdd_SbcWdg_SetTriggerCondition(uint16_t timeout);

extern void Cdd_SbcTurnOnVcc2(void);
extern void Cdd_SbcInit(void);
extern void Cdd_SbcMainFunction(void);
#endif /* _SBC_H_ */