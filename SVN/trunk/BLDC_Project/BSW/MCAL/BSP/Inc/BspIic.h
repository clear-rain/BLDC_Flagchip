/**
 * @file BspIic.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */

#ifndef __BSP_IIC_H__
#define __BSP_IIC_H__

#include "main.h"

typedef struct 
{
	FCIIC_InstanceType eInstance;
	
	uint8_t u8_slaveAddr;

	uint8_t *pau8_txDatabuf;

	uint8_t *pau8_rxDatabuf;

	FCIIC_MasterHandleType *ptFciicMasterHandle;

	FCIIC_DmaConfigType *ptFciicTxDmaConfig;

	FCIIC_DmaConfigType *ptFciicRxDmaConfig;

	DMA_HandleType *pDmaTxHandle;

	DMA_HandleType *pDmaRxHandle;

}IicPrivateData_t;


struct IicDrvHandle_t
{
	char *name;
 
	IicPrivateData_t *pIicPrivateData;

	void (*IicGpio_Init)(uint8_t u8_iicIdx);

	void (*pIicInit)(struct IicDrvHandle_t *pIicDriverIf);

	void (*pFCIIC_WriteAndRead)(struct IicDrvHandle_t * pIicHandle, uint32_t subAddr, uint8_t subAddrLen, uint8_t u8RxDataLen);

	void (*pFCIIC_Write)(struct IicDrvHandle_t * pIicHandle,  uint32_t subAddr, uint8_t subAddrLen, uint8_t u8DataLen);

};
extern struct IicDrvHandle_t *BspIic_GetHandle(char *name);
void BSP_FCIIC_DEInit(void);
#endif /* __BSP_IIC_H__ */