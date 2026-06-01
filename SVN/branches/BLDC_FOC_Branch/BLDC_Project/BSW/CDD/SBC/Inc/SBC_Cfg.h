#ifndef _SBC_CFG_H_
#define _SBC_CFG_H_

#include "main.h"

// #include "Platform.h"

#define SBC_CHIP_TYPE (0x56U)    // 0x7A

#define SBC_FAM_PROD_STATE_ADDR  (0x7EU)
#define SBC_WDG_VALUE (0x55U) 	// 0x74 0x53 0xd4


#define SBC_SOFT_RESET_RST           (1U) 	// 0-杞浣嶄細鎷変綆MCU Reset Pin;  1-杞浣嶄笉浼氭媺浣嶮CU Reset Pin

/********** Control registers address *********/
#define SBC_CTRL_REG_NUM            (17U)

#define SBC_M_S_CTRL_ADDR            (0x01U)
#define SBC_HW_CTRL_0_ADDR           (0x02U)
#define SBC_WD_CTRL_ADDR             (0x03U)
#define SBC_BUS_CTRL_0_ADDR          (0x04U)
#define SBC_WK_CTRL_0_ADDR           (0x06U)
#define SBC_WK_CTRL_1_ADDR           (0x07U)
#define SBC_WK_PUPD_CTRL_ADDR        (0x08U)
#define SBC_BUS_CTRL_3_ADDR          (0x0BU)
#define SBC_TIMER_CTRL_ADDR          (0x0CU)
#define SBC_HW_CTRL_1_ADDR           (0x0EU)
#define SBC_HW_CTRL_2_ADDR           (0x0FU)
#define SBC_GPIO_CTRL_ADDR           (0x17U)
#define SBC_PWM_CTRL_ADDR            (0x18U)
#define SBC_PWM_FREQ_CTRL_ADDR       (0x1CU)
#define SBC_HW_CTRL_3_ADDR           (0x1DU)
#define SBC_SYS_STAT_CTRL_0_ADDR     (0x1EU)
#define SBC_SYS_STAT_CTRL_1_ADDR     (0x1FU)
/********** Control registers address end *********/


/********** Select wake registers address *********/
#define SBC_SWK_CTRL_REG_NUM    (21U)

#define SBC_SWK_CTRL_ADDR             (0x20U)
#define SBC_SWK_BTL0_CTRL_ADDR        (0x21U)
#define SBC_SWK_BTL1_CTRL_ADDR        (0x22U)
#define SBC_SWK_ID3_CTRL_ADDR         (0x23U)
#define SBC_SWK_ID2_CTRL_ADDR         (0x24U)
#define SBC_SWK_ID1_CTRL_ADDR         (0x25U)
#define SBC_SWK_ID0_CTRL_ADDR         (0x26U)
#define SBC_SWK_MASK_ID3_CTRL_ADDR    (0x27U)
#define SBC_SWK_MASK_ID2_CTRL_ADDR    (0x28U)
#define SBC_SWK_MASK_ID1_CTRL_ADDR    (0x29U)
#define SBC_SWK_MASK_ID0_CTRL_ADDR    (0x2AU)
#define SBC_SWK_DLC_CTRL_ADDR         (0x2BU)
#define SBC_SWK_DATA7_CTRL_ADDR       (0x2CU)
#define SBC_SWK_DATA6_CTRL_ADDR       (0x2DU)
#define SBC_SWK_DATA5_CTRL_ADDR       (0x2EU)
#define SBC_SWK_DATA4_CTRL_ADDR       (0x2FU)
#define SBC_SWK_DATA3_CTRL_ADDR       (0x30U)
#define SBC_SWK_DATA2_CTRL_ADDR       (0x31U)
#define SBC_SWK_DATA1_CTRL_ADDR       (0x32U)
#define SBC_SWK_DATA0_CTRL_ADDR       (0x33U)
#define SBC_SWK_CAN_FD_ADDR           (0x34U)
/********** Select wake registers address end *********/

/********** Select wake trim & configurations registers address *********/
#define SBC_SWK_TRIM_CTRL_REG_NUM    (8U)

#define SBC_SWK_OSC_TRIM_CTRL_ADDR          (0x38U)
#define SBC_SWK_OPT_CTRL_ADDR               (0x39U)
#define SBC_SWK_OSC_CAL_H_STAT_ADDR         (0x3AU)
#define SBC_SWK_OSC_CAL_L_STAT_ADDR         (0x3BU)
#define SBC_SWK_CDR_CTRL_1_ADDR             (0x3CU)
#define SBC_SWK_CDR_CTRL_2_ADDR             (0x3DU)
#define SBC_SWK_CDR_LIMIT_HIGH_CTRL_ADDR    (0x3EU)
#define SBC_SWK_CDR_LIMIT_LOW_CTRL_ADDR     (0x3FU)
/********** Select wake trim & configurations registers address end *********/

/********** Status registers address *******************/
#define SBC_STAT_REG_NUM    (10U)

#define SBC_SUP_STAT_1_ADDR    (0x40U)
#define SBC_SUP_STAT_0_ADDR    (0x41U)
#define SBC_TRIM_STAT_ADDR     (0x42U)
#define SBC_DEV_STAT_ADDR      (0x43U)
#define SBC_BUS_STAT_ADDR      (0x44U)
#define SBC_WK_STAT_0_ADDR     (0x46U)
#define SBC_WK_STAT_1_ADDR     (0x47U)
#define SBC_WK_LVL_STAT_ADDR   (0x48U)
#define SBC_GPIO_OC_STAT_ADDR  (0x54U)
#define SBC_GPIO_OL_STAT_ADDR  (0x55U)
/********** Status registers address end *******************/

/********** Select wake status registers address *********/
#define SBC_SWK_WAKE_STAT_REG_NUM    (4U)

#define SBC_SWK_STAT_ADDR                         (0x70U)
#define SBC_SWK_ECNT_STAT_ADDR                    (0x71U)
#define SBC_SWK_CDR_STAT1_ADDR                    (0x72U)
#define SBC_SWK_CDR_STAT2_ADDR                    (0x73U)
/********** Select wake status registers address end *********/

// #define SBC_ALL_REG_NUM  (1U + SBC_CTRL_REG_NUM + SBC_SWK_CTRL_REG_NUM +
// 							SBC_SWK_TRIM_CTRL_REG_NUM + SBC_STAT_REG_NUM + SBC_SWK_WAKE_STAT_REG_NUM)

#define SBC_ALL_REG_NUM  (1U + SBC_CTRL_REG_NUM +  SBC_STAT_REG_NUM )

#define SBC_STAT_REG_IDX (SBC_CTRL_REG_NUM )
							
/*******************************      SBC CAN wake frame define start      ***************************** */
#ifdef ECU_ADDRESS_PDM_FR		// right front
#define SBC_SWK_CAN_ID0 		0x00U
#define SBC_SWK_CAN_ID1 		0x00U
#define SBC_SWK_CAN_ID2 		0x00U
#define SBC_SWK_CAN_ID3 		0x80U
#define SBC_SWK_CAN_ID_MASK0 	0x00U
#define SBC_SWK_CAN_ID_MASK1 	0x00U
#define SBC_SWK_CAN_ID_MASK2 	0x00U
#define SBC_SWK_CAN_ID_MASK3 	0xF0U
#define SBC_SWK_CAN_DLC			0x08U
#define SBC_SWK_CAN_DATA0		0xFFU
#define SBC_SWK_CAN_DATA1		0xFFU
#define SBC_SWK_CAN_DATA2		0xFFU
#define SBC_SWK_CAN_DATA3		0xFFU
#define SBC_SWK_CAN_DATA4		0xFFU
#define SBC_SWK_CAN_DATA5		0xFFU
#define SBC_SWK_CAN_DATA6		0xFFU
#define SBC_SWK_CAN_DATA7		0xFFU
#endif

#ifdef ECU_ADDRESS_PDM_FL		// left door
#define SBC_SWK_CAN_ID0 		0x00U
#define SBC_SWK_CAN_ID1 		0x00U
#define SBC_SWK_CAN_ID2 		0x00U
#define SBC_SWK_CAN_ID3 		0x80U
#define SBC_SWK_CAN_ID_MASK0 	0x00U
#define SBC_SWK_CAN_ID_MASK1 	0x00U
#define SBC_SWK_CAN_ID_MASK2 	0x00U
#define SBC_SWK_CAN_ID_MASK3 	0xF0U
#define SBC_SWK_CAN_DLC			0x08U
#define SBC_SWK_CAN_DATA0		0xFFU
#define SBC_SWK_CAN_DATA1		0xFFU
#define SBC_SWK_CAN_DATA2		0xFFU
#define SBC_SWK_CAN_DATA3		0xFFU
#define SBC_SWK_CAN_DATA4		0xFFU
#define SBC_SWK_CAN_DATA5		0xFFU
#define SBC_SWK_CAN_DATA6		0xFFU
#define SBC_SWK_CAN_DATA7		0xFFU
#endif
 

/*******************************      SBC CAN wake frame defien end        ***************************** */

extern void SBC_SpiInit(void);
extern void SBC_SpiSendSync(uint8_t *pTxData, uint8_t *pRxData, uint16_t u16Len);

extern void SBC_WriteRegSync(uint8_t u8Addr, uint8_t u8Data);
extern void SBC_ReadRegSync(uint8_t u8Addr, uint8_t *pu8Data);
extern void SBC_SpiSendDataSetEB(uint8_t *pTxData, uint8_t *pRxData, uint16_t u16Len);
extern void SBC_SpiSendDataSeqAsync(void);

#endif /* _SBC_CFG_H_ */
