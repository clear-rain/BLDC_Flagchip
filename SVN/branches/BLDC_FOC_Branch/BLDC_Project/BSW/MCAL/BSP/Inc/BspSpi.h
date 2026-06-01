/**
 * @file BspSpi.h
 * @brief 
 * @author  BSW ENGINEER (Jin-Tech)
 * @copyright Jin-Tech Technologies 
 * @par Modified Log:
 * <table>
 * <tr><th>Date       <th>Version         <th>Author           <th>Description
 * <tr><td>2024-09-18 <td>m00.a00.b01     <td>HongChunfeng     <td>1.Initialization Version
 * </table>
 */


#ifndef INC_BSPSPI_H_
#define INC_BSPSPI_H_

#include "main.h"


typedef struct 
{
	FCSPI_InstanceType eInstance;
	uint32_t u32BitCntPerSecond;
	FCSPI_PCSType ePcs;
	FCSPI_PcsPolarityType ePcsPolarity;
	FCSPI_AtomicBoolType eIsPcsContinuous;
	uint16_t u16BitCountPerFrame;
	FCSPI_SckSamplePhaseType eSckSamplePhase;
	FCSPI_SckPolarityType eSckPolarity;
	FCSPI_BitFirstOrderType eBitFirstOrder;
	FCSPI_TriggerSrcType eTransferTriggerSrc;
	void (*pStopNotifyCb)(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);
	FCSPI_PCS2_3ModeType ePCS23Mode;
	FCSPI_TransferWidthType eTransferWidthType;
	FCSPI_NegatedPinOutStatType ePinOutStatType;
	DMA_HandleType *pDmaRxInstanceHandle ;
	DMA_HandleType *pDmaTxInstanceHandle ;
	uint32_t u32PCStoPCSHoldUs; /*!< Configures the delay cycles from the PCS negation to the next PCS assertion, in microsecond(us) */
    uint32_t u32SCKtoPCSHoldUs; /*!< Configure the delay cycles from the last SCK edge to the PCS negation, in microsecond(us) */
    uint32_t u32PCStoSCKHoldUs; /*!< Configure the delay cycles from the PCS assertion to the first SCK edge, in microsecond(us) */
	uint32_t u32Sckdiv;
}SpiPrivateData_t;

struct SpiDriverIf_t
{
	char *name;
	SpiPrivateData_t *spiPriData;
	uint8_t (*GPIO_Init)(uint8_t u8_spiIdx);
	void (*SpiInit)(struct SpiDriverIf_t *pDev);
	FCSPI_StatusType (*TransmitSync)(struct SpiDriverIf_t *pDev, const uint8_t *TxBuffer, uint8_t *RxBuffer, uint16_t len, uint32_t timeout);
	FCSPI_StatusType (*TransmitAsync)(struct SpiDriverIf_t *pDev, const uint8_t *TxBuffer, uint8_t *RxBuffer, uint16_t len);
};

extern struct SpiDriverIf_t *Bsp_FCSpi_GetDevice(char *name);
extern bool Bsp_FCSpi_CheckSendFinish(struct SpiDriverIf_t *pDev);
void Bsp_FCSpi_DeInit(void);

#endif /* INC_BSPSPI_H_ */