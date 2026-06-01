/**
 * @file BspAdc.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */

#ifndef INC_BSPADC_H_
#define INC_BSPADC_H_

#include "main.h"

#ifndef ECU_ADDRESS_BLDC
#define SYS_ADC_GROUP_NUM	2U

#define ADC0_CHN_NUM_EN  2U
#define ADC1_CHN_NUM_EN  4U
#else
#define SYS_ADC_GROUP_NUM	2U

#define ADC0_CHN_NUM_EN  5U
#define ADC1_CHN_NUM_EN  5U
#endif /*ECU_ADDRESS_BLDC*/

struct AdcGroupCfg_t {
	char *name;
	PCC_ClkSrcType eAdcClkName;
	ADC_InitType *pAdcInitCfg;
	ADC_HandleType *g_tAdcHandle;
	DMA_HandleType *ptDmaHandle;
	ADC_DmaType *pAdcDmaCfg;
	const ADC_ChannelCfgType *pAdcChnl;
	void (*pf_AdcInit)(struct AdcGroupCfg_t *pDev);
	void (*pf_AdcStart)(struct AdcGroupCfg_t *pDev);
};

struct AdcGroupCfg_t * BSP_AdcGetDevice(char *name);
void Bsp_ADC_DeInit(void);
#endif /* INC_BSPADC_H_ */
