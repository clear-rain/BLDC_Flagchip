#ifndef _MODULE_FCSPI_KJO_Ufdi16_REGS_H_
#define _MODULE_FCSPI_KJO_Ufdi16_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif

#include "typedef.h"
/* ----------------------------------------------------------------------------
   -- FCSPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCSPI_Peripheral_Access_Layer FCSPI Peripheral Access Layer
 * @{
 */
/** FCSPI - Size of Registers Arrays */
/** FCSPI - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[16];
  __IO uint32_t CTRL                          ; /* Control, offset: 0x10 */
  __IO uint32_t STATUS                        ; /* Status, offset: 0x14 */
  __IO uint32_t INT_EN                        ; /* Interrupt Enable, offset: 0x18 */
  __IO uint32_t DMA_EN                        ; /* DMA Enable, offset: 0x1C */
  __IO uint32_t CFG0                          ; /* Configuration 0, offset: 0x20 */
  __IO uint32_t CFG1                          ; /* Configuration 1, offset: 0x24 */
       uint8_t  RESERVED_1[8];
  __IO uint32_t DATA_MATCH0                   ; /* Data Match 0, offset: 0x30 */
  __IO uint32_t DATA_MATCH1                   ; /* Data Match 1, offset: 0x34 */
       uint8_t  RESERVED_2[8];
  __IO uint32_t CLK_CFG                       ; /* Clock Configure, offset: 0x40 */
       uint8_t  RESERVED_3[20];
  __IO uint32_t FIFO_WTM                      ; /* FIFO Water Mark, offset: 0x58 */
  __I  uint32_t FIFO_STATUS                   ; /* FIFO Status, offset: 0x5C */
  __IO uint32_t TR_CTRL                       ; /* Transmit and Receive Control, offset: 0x60 */
  __O  uint32_t TX_DATA                       ; /* Transmit Data, offset: 0x64 */
       uint8_t  RESERVED_4[8];
  __I  uint32_t RX_STATUS                     ; /* Receive Status, offset: 0x70 */
  __I  uint32_t RX_DATA                       ; /* Receive Data, offset: 0x74 */
       uint8_t  RESERVED_5[8];
  __IO uint32_t PARITY_CHK                    ; /* Parity Check, offset: 0x80 */
} FCSPI_Type, *FCSPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FCSPI Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCSPI_Register_Masks FCSPI Register Masks
 * @{
 */
 
/* CTRL Bit Fields */
#define FCSPI_CTRL_RST_RF_MASK         0x200u
#define FCSPI_CTRL_RST_RF_SHIFT        9u
#define FCSPI_CTRL_RST_RF_WIDTH        1u
#define FCSPI_CTRL_RST_RF(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_CTRL_RST_RF_SHIFT))&FCSPI_CTRL_RST_RF_MASK)
#define FCSPI_CTRL_RST_TF_MASK         0x100u
#define FCSPI_CTRL_RST_TF_SHIFT        8u
#define FCSPI_CTRL_RST_TF_WIDTH        1u
#define FCSPI_CTRL_RST_TF(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_CTRL_RST_TF_SHIFT))&FCSPI_CTRL_RST_TF_MASK)
#define FCSPI_CTRL_DBG_EN_MASK         0x8u
#define FCSPI_CTRL_DBG_EN_SHIFT        3u
#define FCSPI_CTRL_DBG_EN_WIDTH        1u
#define FCSPI_CTRL_DBG_EN(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_CTRL_DBG_EN_SHIFT))&FCSPI_CTRL_DBG_EN_MASK)
#define FCSPI_CTRL_WAIT_DIS_MASK       0x4u
#define FCSPI_CTRL_WAIT_DIS_SHIFT      2u
#define FCSPI_CTRL_WAIT_DIS_WIDTH      1u
#define FCSPI_CTRL_WAIT_DIS(x)         (((uint32_t)(((uint32_t)(x))<<FCSPI_CTRL_WAIT_DIS_SHIFT))&FCSPI_CTRL_WAIT_DIS_MASK)
#define FCSPI_CTRL_SW_RST_MASK         0x2u
#define FCSPI_CTRL_SW_RST_SHIFT        1u
#define FCSPI_CTRL_SW_RST_WIDTH        1u
#define FCSPI_CTRL_SW_RST(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_CTRL_SW_RST_SHIFT))&FCSPI_CTRL_SW_RST_MASK)
#define FCSPI_CTRL_M_EN_MASK           0x1u
#define FCSPI_CTRL_M_EN_SHIFT          0u
#define FCSPI_CTRL_M_EN_WIDTH          1u
#define FCSPI_CTRL_M_EN(x)             (((uint32_t)(((uint32_t)(x))<<FCSPI_CTRL_M_EN_SHIFT))&FCSPI_CTRL_M_EN_MASK)
/* CTRL Reg Mask */
#define FCSPI_CTRL_MASK                0x0000030Fu
/* STATUS Bit Fields */
#define FCSPI_STATUS_BF_MASK           0x1000000u
#define FCSPI_STATUS_BF_SHIFT          24u
#define FCSPI_STATUS_BF_WIDTH          1u
#define FCSPI_STATUS_BF(x)             (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_BF_SHIFT))&FCSPI_STATUS_BF_MASK)
#define FCSPI_STATUS_DMF_MASK          0x2000u
#define FCSPI_STATUS_DMF_SHIFT         13u
#define FCSPI_STATUS_DMF_WIDTH         1u
#define FCSPI_STATUS_DMF(x)            (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_DMF_SHIFT))&FCSPI_STATUS_DMF_MASK)
#define FCSPI_STATUS_RX_FO_MASK        0x1000u
#define FCSPI_STATUS_RX_FO_SHIFT       12u
#define FCSPI_STATUS_RX_FO_WIDTH       1u
#define FCSPI_STATUS_RX_FO(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_RX_FO_SHIFT))&FCSPI_STATUS_RX_FO_MASK)
#define FCSPI_STATUS_TX_FU_MASK        0x800u
#define FCSPI_STATUS_TX_FU_SHIFT       11u
#define FCSPI_STATUS_TX_FU_WIDTH       1u
#define FCSPI_STATUS_TX_FU(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_TX_FU_SHIFT))&FCSPI_STATUS_TX_FU_MASK)
#define FCSPI_STATUS_TCF_MASK          0x400u
#define FCSPI_STATUS_TCF_SHIFT         10u
#define FCSPI_STATUS_TCF_WIDTH         1u
#define FCSPI_STATUS_TCF(x)            (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_TCF_SHIFT))&FCSPI_STATUS_TCF_MASK)
#define FCSPI_STATUS_FEF_MASK          0x200u
#define FCSPI_STATUS_FEF_SHIFT         9u
#define FCSPI_STATUS_FEF_WIDTH         1u
#define FCSPI_STATUS_FEF(x)            (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_FEF_SHIFT))&FCSPI_STATUS_FEF_MASK)
#define FCSPI_STATUS_RX_WF_MASK        0x100u
#define FCSPI_STATUS_RX_WF_SHIFT       8u
#define FCSPI_STATUS_RX_WF_WIDTH       1u
#define FCSPI_STATUS_RX_WF(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_RX_WF_SHIFT))&FCSPI_STATUS_RX_WF_MASK)
#define FCSPI_STATUS_RPEF_MASK         0x8u
#define FCSPI_STATUS_RPEF_SHIFT        3u
#define FCSPI_STATUS_RPEF_WIDTH        1u
#define FCSPI_STATUS_RPEF(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_RPEF_SHIFT))&FCSPI_STATUS_RPEF_MASK)
#define FCSPI_STATUS_TPEF_MASK         0x4u
#define FCSPI_STATUS_TPEF_SHIFT        2u
#define FCSPI_STATUS_TPEF_WIDTH        1u
#define FCSPI_STATUS_TPEF(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_TPEF_SHIFT))&FCSPI_STATUS_TPEF_MASK)
#define FCSPI_STATUS_RX_FF_MASK        0x2u
#define FCSPI_STATUS_RX_FF_SHIFT       1u
#define FCSPI_STATUS_RX_FF_WIDTH       1u
#define FCSPI_STATUS_RX_FF(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_RX_FF_SHIFT))&FCSPI_STATUS_RX_FF_MASK)
#define FCSPI_STATUS_TX_FF_MASK        0x1u
#define FCSPI_STATUS_TX_FF_SHIFT       0u
#define FCSPI_STATUS_TX_FF_WIDTH       1u
#define FCSPI_STATUS_TX_FF(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_STATUS_TX_FF_SHIFT))&FCSPI_STATUS_TX_FF_MASK)
/* STATUS Reg Mask */
#define FCSPI_STATUS_MASK              0x01003F0Fu
/* INT_EN Bit Fields */
#define FCSPI_INT_EN_DMIE_MASK         0x2000u
#define FCSPI_INT_EN_DMIE_SHIFT        13u
#define FCSPI_INT_EN_DMIE_WIDTH        1u
#define FCSPI_INT_EN_DMIE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_DMIE_SHIFT))&FCSPI_INT_EN_DMIE_MASK)
#define FCSPI_INT_EN_RFOIE_MASK        0x1000u
#define FCSPI_INT_EN_RFOIE_SHIFT       12u
#define FCSPI_INT_EN_RFOIE_WIDTH       1u
#define FCSPI_INT_EN_RFOIE(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_RFOIE_SHIFT))&FCSPI_INT_EN_RFOIE_MASK)
#define FCSPI_INT_EN_TFUIE_MASK        0x800u
#define FCSPI_INT_EN_TFUIE_SHIFT       11u
#define FCSPI_INT_EN_TFUIE_WIDTH       1u
#define FCSPI_INT_EN_TFUIE(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_TFUIE_SHIFT))&FCSPI_INT_EN_TFUIE_MASK)
#define FCSPI_INT_EN_TCIE_MASK         0x400u
#define FCSPI_INT_EN_TCIE_SHIFT        10u
#define FCSPI_INT_EN_TCIE_WIDTH        1u
#define FCSPI_INT_EN_TCIE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_TCIE_SHIFT))&FCSPI_INT_EN_TCIE_MASK)
#define FCSPI_INT_EN_FEIE_MASK         0x200u
#define FCSPI_INT_EN_FEIE_SHIFT        9u
#define FCSPI_INT_EN_FEIE_WIDTH        1u
#define FCSPI_INT_EN_FEIE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_FEIE_SHIFT))&FCSPI_INT_EN_FEIE_MASK)
#define FCSPI_INT_EN_RWIE_MASK         0x100u
#define FCSPI_INT_EN_RWIE_SHIFT        8u
#define FCSPI_INT_EN_RWIE_WIDTH        1u
#define FCSPI_INT_EN_RWIE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_RWIE_SHIFT))&FCSPI_INT_EN_RWIE_MASK)
#define FCSPI_INT_EN_RX_PEIE_MASK      0x8u
#define FCSPI_INT_EN_RX_PEIE_SHIFT     3u
#define FCSPI_INT_EN_RX_PEIE_WIDTH     1u
#define FCSPI_INT_EN_RX_PEIE(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_RX_PEIE_SHIFT))&FCSPI_INT_EN_RX_PEIE_MASK)
#define FCSPI_INT_EN_TX_PEIE_MASK      0x4u
#define FCSPI_INT_EN_TX_PEIE_SHIFT     2u
#define FCSPI_INT_EN_TX_PEIE_WIDTH     1u
#define FCSPI_INT_EN_TX_PEIE(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_TX_PEIE_SHIFT))&FCSPI_INT_EN_TX_PEIE_MASK)
#define FCSPI_INT_EN_RFIE_MASK         0x2u
#define FCSPI_INT_EN_RFIE_SHIFT        1u
#define FCSPI_INT_EN_RFIE_WIDTH        1u
#define FCSPI_INT_EN_RFIE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_RFIE_SHIFT))&FCSPI_INT_EN_RFIE_MASK)
#define FCSPI_INT_EN_TFIE_MASK         0x1u
#define FCSPI_INT_EN_TFIE_SHIFT        0u
#define FCSPI_INT_EN_TFIE_WIDTH        1u
#define FCSPI_INT_EN_TFIE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_INT_EN_TFIE_SHIFT))&FCSPI_INT_EN_TFIE_MASK)
/* INT_EN Reg Mask */
#define FCSPI_INT_EN_MASK              0x00003F0Fu
/* DMA_EN Bit Fields */
#define FCSPI_DMA_EN_RFDE_MASK         0x2u
#define FCSPI_DMA_EN_RFDE_SHIFT        1u
#define FCSPI_DMA_EN_RFDE_WIDTH        1u
#define FCSPI_DMA_EN_RFDE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_DMA_EN_RFDE_SHIFT))&FCSPI_DMA_EN_RFDE_MASK)
#define FCSPI_DMA_EN_TFDE_MASK         0x1u
#define FCSPI_DMA_EN_TFDE_SHIFT        0u
#define FCSPI_DMA_EN_TFDE_WIDTH        1u
#define FCSPI_DMA_EN_TFDE(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_DMA_EN_TFDE_SHIFT))&FCSPI_DMA_EN_TFDE_MASK)
/* DMA_EN Reg Mask */
#define FCSPI_DMA_EN_MASK              0x00000003u
/* CFG0 Bit Fields */
#define FCSPI_CFG0_RDMO_MASK           0x200u
#define FCSPI_CFG0_RDMO_SHIFT          9u
#define FCSPI_CFG0_RDMO_WIDTH          1u
#define FCSPI_CFG0_RDMO(x)             (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG0_RDMO_SHIFT))&FCSPI_CFG0_RDMO_MASK)
#define FCSPI_CFG0_TRGEN_MASK          0x1u
#define FCSPI_CFG0_TRGEN_SHIFT         0u
#define FCSPI_CFG0_TRGEN_WIDTH         1u
#define FCSPI_CFG0_TRGEN(x)            (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG0_TRGEN_SHIFT))&FCSPI_CFG0_TRGEN_MASK)
/* CFG0 Reg Mask */
#define FCSPI_CFG0_MASK                0x00000201u
/* CFG1 Bit Fields */
#define FCSPI_CFG1_PCS_CFG_MASK        0x8000000u
#define FCSPI_CFG1_PCS_CFG_SHIFT       27u
#define FCSPI_CFG1_PCS_CFG_WIDTH       1u
#define FCSPI_CFG1_PCS_CFG(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_PCS_CFG_SHIFT))&FCSPI_CFG1_PCS_CFG_MASK)
#define FCSPI_CFG1_OUT_CFG_MASK        0x4000000u
#define FCSPI_CFG1_OUT_CFG_SHIFT       26u
#define FCSPI_CFG1_OUT_CFG_WIDTH       1u
#define FCSPI_CFG1_OUT_CFG(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_OUT_CFG_SHIFT))&FCSPI_CFG1_OUT_CFG_MASK)
#define FCSPI_CFG1_PIN_CFG_MASK        0x3000000u
#define FCSPI_CFG1_PIN_CFG_SHIFT       24u
#define FCSPI_CFG1_PIN_CFG_WIDTH       2u
#define FCSPI_CFG1_PIN_CFG(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_PIN_CFG_SHIFT))&FCSPI_CFG1_PIN_CFG_MASK)
#define FCSPI_CFG1_MAT_CFG_MASK        0x70000u
#define FCSPI_CFG1_MAT_CFG_SHIFT       16u
#define FCSPI_CFG1_MAT_CFG_WIDTH       3u
#define FCSPI_CFG1_MAT_CFG(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_MAT_CFG_SHIFT))&FCSPI_CFG1_MAT_CFG_MASK)
#define FCSPI_CFG1_PCS_POL_MASK        0xF00u
#define FCSPI_CFG1_PCS_POL_SHIFT       8u
#define FCSPI_CFG1_PCS_POL_WIDTH       4u
#define FCSPI_CFG1_PCS_POL(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_PCS_POL_SHIFT))&FCSPI_CFG1_PCS_POL_MASK)
#define FCSPI_CFG1_INT_PCS_MASK        0x4u
#define FCSPI_CFG1_INT_PCS_SHIFT       2u
#define FCSPI_CFG1_INT_PCS_WIDTH       1u
#define FCSPI_CFG1_INT_PCS(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_INT_PCS_SHIFT))&FCSPI_CFG1_INT_PCS_MASK)
#define FCSPI_CFG1_SCK_LB_MASK         0x2u
#define FCSPI_CFG1_SCK_LB_SHIFT        1u
#define FCSPI_CFG1_SCK_LB_WIDTH        1u
#define FCSPI_CFG1_SCK_LB(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_SCK_LB_SHIFT))&FCSPI_CFG1_SCK_LB_MASK)
#define FCSPI_CFG1_MASTER_MASK         0x1u
#define FCSPI_CFG1_MASTER_SHIFT        0u
#define FCSPI_CFG1_MASTER_WIDTH        1u
#define FCSPI_CFG1_MASTER(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_CFG1_MASTER_SHIFT))&FCSPI_CFG1_MASTER_MASK)
/* CFG1 Reg Mask */
#define FCSPI_CFG1_MASK                0x0F070F07u
/* DATA_MATCH0 Bit Fields */
#define FCSPI_DATA_MATCH0_DATA0_MASK   0xFFFFFFFFu
#define FCSPI_DATA_MATCH0_DATA0_SHIFT  0u
#define FCSPI_DATA_MATCH0_DATA0_WIDTH  32u
#define FCSPI_DATA_MATCH0_DATA0(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_DATA_MATCH0_DATA0_SHIFT))&FCSPI_DATA_MATCH0_DATA0_MASK)
/* DATA_MATCH0 Reg Mask */
#define FCSPI_DATA_MATCH0_MASK         0xFFFFFFFFu
/* DATA_MATCH1 Bit Fields */
#define FCSPI_DATA_MATCH1_DATA1_MASK   0xFFFFFFFFu
#define FCSPI_DATA_MATCH1_DATA1_SHIFT  0u
#define FCSPI_DATA_MATCH1_DATA1_WIDTH  32u
#define FCSPI_DATA_MATCH1_DATA1(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_DATA_MATCH1_DATA1_SHIFT))&FCSPI_DATA_MATCH1_DATA1_MASK)
/* DATA_MATCH1 Reg Mask */
#define FCSPI_DATA_MATCH1_MASK         0xFFFFFFFFu
/* CLK_CFG Bit Fields */
#define FCSPI_CLK_CFG_SCKPCS_MASK      0xFF000000u
#define FCSPI_CLK_CFG_SCKPCS_SHIFT     24u
#define FCSPI_CLK_CFG_SCKPCS_WIDTH     8u
#define FCSPI_CLK_CFG_SCKPCS(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_CLK_CFG_SCKPCS_SHIFT))&FCSPI_CLK_CFG_SCKPCS_MASK)
#define FCSPI_CLK_CFG_PCSSCK_MASK      0xFF0000u
#define FCSPI_CLK_CFG_PCSSCK_SHIFT     16u
#define FCSPI_CLK_CFG_PCSSCK_WIDTH     8u
#define FCSPI_CLK_CFG_PCSSCK(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_CLK_CFG_PCSSCK_SHIFT))&FCSPI_CLK_CFG_PCSSCK_MASK)
#define FCSPI_CLK_CFG_PCSPCS_MASK      0xFF00u
#define FCSPI_CLK_CFG_PCSPCS_SHIFT     8u
#define FCSPI_CLK_CFG_PCSPCS_WIDTH     8u
#define FCSPI_CLK_CFG_PCSPCS(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_CLK_CFG_PCSPCS_SHIFT))&FCSPI_CLK_CFG_PCSPCS_MASK)
#define FCSPI_CLK_CFG_SCKDIV_MASK      0xFFu
#define FCSPI_CLK_CFG_SCKDIV_SHIFT     0u
#define FCSPI_CLK_CFG_SCKDIV_WIDTH     8u
#define FCSPI_CLK_CFG_SCKDIV(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_CLK_CFG_SCKDIV_SHIFT))&FCSPI_CLK_CFG_SCKDIV_MASK)
/* CLK_CFG Reg Mask */
#define FCSPI_CLK_CFG_MASK             0xFFFFFFFFu
/* FIFO_WTM Bit Fields */
#define FCSPI_FIFO_WTM_RXWATER_MASK    0x70000u
#define FCSPI_FIFO_WTM_RXWATER_SHIFT   16u
#define FCSPI_FIFO_WTM_RXWATER_WIDTH   3u
#define FCSPI_FIFO_WTM_RXWATER(x)      (((uint32_t)(((uint32_t)(x))<<FCSPI_FIFO_WTM_RXWATER_SHIFT))&FCSPI_FIFO_WTM_RXWATER_MASK)
#define FCSPI_FIFO_WTM_TXWATER_MASK    0x7u
#define FCSPI_FIFO_WTM_TXWATER_SHIFT   0u
#define FCSPI_FIFO_WTM_TXWATER_WIDTH   3u
#define FCSPI_FIFO_WTM_TXWATER(x)      (((uint32_t)(((uint32_t)(x))<<FCSPI_FIFO_WTM_TXWATER_SHIFT))&FCSPI_FIFO_WTM_TXWATER_MASK)
/* FIFO_WTM Reg Mask */
#define FCSPI_FIFO_WTM_MASK            0x00070007u
/* FIFO_STATUS Bit Fields */
#define FCSPI_FIFO_STATUS_RXCNT_MASK   0xF0000u
#define FCSPI_FIFO_STATUS_RXCNT_SHIFT  16u
#define FCSPI_FIFO_STATUS_RXCNT_WIDTH  4u
#define FCSPI_FIFO_STATUS_RXCNT(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_FIFO_STATUS_RXCNT_SHIFT))&FCSPI_FIFO_STATUS_RXCNT_MASK)
#define FCSPI_FIFO_STATUS_TXCNT_MASK   0xFu
#define FCSPI_FIFO_STATUS_TXCNT_SHIFT  0u
#define FCSPI_FIFO_STATUS_TXCNT_WIDTH  4u
#define FCSPI_FIFO_STATUS_TXCNT(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_FIFO_STATUS_TXCNT_SHIFT))&FCSPI_FIFO_STATUS_TXCNT_MASK)
/* FIFO_STATUS Reg Mask */
#define FCSPI_FIFO_STATUS_MASK         0x000F000Fu
/* TR_CTRL Bit Fields */
#define FCSPI_TR_CTRL_SCK_POL_MASK     0x80000000u
#define FCSPI_TR_CTRL_SCK_POL_SHIFT    31u
#define FCSPI_TR_CTRL_SCK_POL_WIDTH    1u
#define FCSPI_TR_CTRL_SCK_POL(x)       (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_SCK_POL_SHIFT))&FCSPI_TR_CTRL_SCK_POL_MASK)
#define FCSPI_TR_CTRL_SCK_PHA_MASK     0x40000000u
#define FCSPI_TR_CTRL_SCK_PHA_SHIFT    30u
#define FCSPI_TR_CTRL_SCK_PHA_WIDTH    1u
#define FCSPI_TR_CTRL_SCK_PHA(x)       (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_SCK_PHA_SHIFT))&FCSPI_TR_CTRL_SCK_PHA_MASK)
#define FCSPI_TR_CTRL_PRESCALE_MASK    0x38000000u
#define FCSPI_TR_CTRL_PRESCALE_SHIFT   27u
#define FCSPI_TR_CTRL_PRESCALE_WIDTH   3u
#define FCSPI_TR_CTRL_PRESCALE(x)      (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_PRESCALE_SHIFT))&FCSPI_TR_CTRL_PRESCALE_MASK)
#define FCSPI_TR_CTRL_PCS_MASK         0x3000000u
#define FCSPI_TR_CTRL_PCS_SHIFT        24u
#define FCSPI_TR_CTRL_PCS_WIDTH        2u
#define FCSPI_TR_CTRL_PCS(x)           (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_PCS_SHIFT))&FCSPI_TR_CTRL_PCS_MASK)
#define FCSPI_TR_CTRL_LSBF_MASK        0x800000u
#define FCSPI_TR_CTRL_LSBF_SHIFT       23u
#define FCSPI_TR_CTRL_LSBF_WIDTH       1u
#define FCSPI_TR_CTRL_LSBF(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_LSBF_SHIFT))&FCSPI_TR_CTRL_LSBF_MASK)
#define FCSPI_TR_CTRL_BYSW_MASK        0x400000u
#define FCSPI_TR_CTRL_BYSW_SHIFT       22u
#define FCSPI_TR_CTRL_BYSW_WIDTH       1u
#define FCSPI_TR_CTRL_BYSW(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_BYSW_SHIFT))&FCSPI_TR_CTRL_BYSW_MASK)
#define FCSPI_TR_CTRL_CT_EN_MASK       0x200000u
#define FCSPI_TR_CTRL_CT_EN_SHIFT      21u
#define FCSPI_TR_CTRL_CT_EN_WIDTH      1u
#define FCSPI_TR_CTRL_CT_EN(x)         (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_CT_EN_SHIFT))&FCSPI_TR_CTRL_CT_EN_MASK)
#define FCSPI_TR_CTRL_CT_GO_MASK       0x100000u
#define FCSPI_TR_CTRL_CT_GO_SHIFT      20u
#define FCSPI_TR_CTRL_CT_GO_WIDTH      1u
#define FCSPI_TR_CTRL_CT_GO(x)         (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_CT_GO_SHIFT))&FCSPI_TR_CTRL_CT_GO_MASK)
#define FCSPI_TR_CTRL_RX_MSK_MASK      0x80000u
#define FCSPI_TR_CTRL_RX_MSK_SHIFT     19u
#define FCSPI_TR_CTRL_RX_MSK_WIDTH     1u
#define FCSPI_TR_CTRL_RX_MSK(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_RX_MSK_SHIFT))&FCSPI_TR_CTRL_RX_MSK_MASK)
#define FCSPI_TR_CTRL_TX_MSK_MASK      0x40000u
#define FCSPI_TR_CTRL_TX_MSK_SHIFT     18u
#define FCSPI_TR_CTRL_TX_MSK_WIDTH     1u
#define FCSPI_TR_CTRL_TX_MSK(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_TX_MSK_SHIFT))&FCSPI_TR_CTRL_TX_MSK_MASK)
#define FCSPI_TR_CTRL_WIDTH_MASK       0x30000u
#define FCSPI_TR_CTRL_WIDTH_SHIFT      16u
#define FCSPI_TR_CTRL_WIDTH_WIDTH      2u
#define FCSPI_TR_CTRL_WIDTH(x)         (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_WIDTH_SHIFT))&FCSPI_TR_CTRL_WIDTH_MASK)
#define FCSPI_TR_CTRL_FRM_SZ_MASK      0xFFFu
#define FCSPI_TR_CTRL_FRM_SZ_SHIFT     0u
#define FCSPI_TR_CTRL_FRM_SZ_WIDTH     12u
#define FCSPI_TR_CTRL_FRM_SZ(x)        (((uint32_t)(((uint32_t)(x))<<FCSPI_TR_CTRL_FRM_SZ_SHIFT))&FCSPI_TR_CTRL_FRM_SZ_MASK)
/* TR_CTRL Reg Mask */
#define FCSPI_TR_CTRL_MASK             0xFBFF0FFFu
/* TX_DATA Bit Fields */
#define FCSPI_TX_DATA_DATA_MASK        0xFFFFFFFFu
#define FCSPI_TX_DATA_DATA_SHIFT       0u
#define FCSPI_TX_DATA_DATA_WIDTH       32u
#define FCSPI_TX_DATA_DATA(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_TX_DATA_DATA_SHIFT))&FCSPI_TX_DATA_DATA_MASK)
/* TX_DATA Reg Mask */
#define FCSPI_TX_DATA_MASK             0xFFFFFFFFu
/* RX_STATUS Bit Fields */
#define FCSPI_RX_STATUS_RX_EMPTY_MASK  0x2u
#define FCSPI_RX_STATUS_RX_EMPTY_SHIFT 1u
#define FCSPI_RX_STATUS_RX_EMPTY_WIDTH 1u
#define FCSPI_RX_STATUS_RX_EMPTY(x)    (((uint32_t)(((uint32_t)(x))<<FCSPI_RX_STATUS_RX_EMPTY_SHIFT))&FCSPI_RX_STATUS_RX_EMPTY_MASK)
#define FCSPI_RX_STATUS_FD_MASK        0x1u
#define FCSPI_RX_STATUS_FD_SHIFT       0u
#define FCSPI_RX_STATUS_FD_WIDTH       1u
#define FCSPI_RX_STATUS_FD(x)          (((uint32_t)(((uint32_t)(x))<<FCSPI_RX_STATUS_FD_SHIFT))&FCSPI_RX_STATUS_FD_MASK)
/* RX_STATUS Reg Mask */
#define FCSPI_RX_STATUS_MASK           0x00000003u
/* RX_DATA Bit Fields */
#define FCSPI_RX_DATA_RX_DATA_MASK     0xFFFFFFFFu
#define FCSPI_RX_DATA_RX_DATA_SHIFT    0u
#define FCSPI_RX_DATA_RX_DATA_WIDTH    32u
#define FCSPI_RX_DATA_RX_DATA(x)       (((uint32_t)(((uint32_t)(x))<<FCSPI_RX_DATA_RX_DATA_SHIFT))&FCSPI_RX_DATA_RX_DATA_MASK)
/* RX_DATA Reg Mask */
#define FCSPI_RX_DATA_MASK             0xFFFFFFFFu
/* PARITY_CHK Bit Fields */
#define FCSPI_PARITY_CHK_REIB_MASK     0xFC00u
#define FCSPI_PARITY_CHK_REIB_SHIFT    10u
#define FCSPI_PARITY_CHK_REIB_WIDTH    6u
#define FCSPI_PARITY_CHK_REIB(x)       (((uint32_t)(((uint32_t)(x))<<FCSPI_PARITY_CHK_REIB_SHIFT))&FCSPI_PARITY_CHK_REIB_MASK)
#define FCSPI_PARITY_CHK_REI_EN_MASK   0x200u
#define FCSPI_PARITY_CHK_REI_EN_SHIFT  9u
#define FCSPI_PARITY_CHK_REI_EN_WIDTH  1u
#define FCSPI_PARITY_CHK_REI_EN(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_PARITY_CHK_REI_EN_SHIFT))&FCSPI_PARITY_CHK_REI_EN_MASK)
#define FCSPI_PARITY_CHK_RPC_EN_MASK   0x100u
#define FCSPI_PARITY_CHK_RPC_EN_SHIFT  8u
#define FCSPI_PARITY_CHK_RPC_EN_WIDTH  1u
#define FCSPI_PARITY_CHK_RPC_EN(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_PARITY_CHK_RPC_EN_SHIFT))&FCSPI_PARITY_CHK_RPC_EN_MASK)
#define FCSPI_PARITY_CHK_TEIB_MASK     0xFCu
#define FCSPI_PARITY_CHK_TEIB_SHIFT    2u
#define FCSPI_PARITY_CHK_TEIB_WIDTH    6u
#define FCSPI_PARITY_CHK_TEIB(x)       (((uint32_t)(((uint32_t)(x))<<FCSPI_PARITY_CHK_TEIB_SHIFT))&FCSPI_PARITY_CHK_TEIB_MASK)
#define FCSPI_PARITY_CHK_TEI_EN_MASK   0x2u
#define FCSPI_PARITY_CHK_TEI_EN_SHIFT  1u
#define FCSPI_PARITY_CHK_TEI_EN_WIDTH  1u
#define FCSPI_PARITY_CHK_TEI_EN(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_PARITY_CHK_TEI_EN_SHIFT))&FCSPI_PARITY_CHK_TEI_EN_MASK)
#define FCSPI_PARITY_CHK_TPC_EN_MASK   0x1u
#define FCSPI_PARITY_CHK_TPC_EN_SHIFT  0u
#define FCSPI_PARITY_CHK_TPC_EN_WIDTH  1u
#define FCSPI_PARITY_CHK_TPC_EN(x)     (((uint32_t)(((uint32_t)(x))<<FCSPI_PARITY_CHK_TPC_EN_SHIFT))&FCSPI_PARITY_CHK_TPC_EN_MASK)
/* PARITY_CHK Reg Mask */
#define FCSPI_PARITY_CHK_MASK          0x0000FFFFu
/**
 * @}
 */ /* end of group FCSPI_Register_Masks */
/**
 * @}
 */ /* end of group FCSPI_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif

#endif
