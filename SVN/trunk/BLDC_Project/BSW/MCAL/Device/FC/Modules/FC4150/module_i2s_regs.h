#ifndef _MODULE_I2S_KJO_Ufdi13_REGS_H_
#define _MODULE_I2S_KJO_Ufdi13_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- I2S Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup I2S_Peripheral_Access_Layer I2S Peripheral Access Layer
 * @{
 */
/** I2S - Size of Registers Arrays */
/** I2S - Register Layout Typedef */
#define I2S_TX_DATA_COUNT 4
#define I2S_TX_FIFO_STATUS_COUNT 4
#define I2S_RX_DATA_COUNT 4
#define I2S_RX_FIFO_STATUS_COUNT 4
typedef struct {
       uint8_t  RESERVED_0[8];
  __IO uint32_t TX_IDF                        ; /* Transmitter Interrupt DMA and Flag, offset: 0x8 */
  __IO uint32_t TX_FIFO_CFG                   ; /* Transmitter FIFO Configure, offset: 0xC */
  __IO uint32_t TX_CLK_CFG                    ; /* Transmitter Clock Configure, offset: 0x10 */
  __IO uint32_t TX_CHAN_CFG                   ; /* Transmitter Channel Configure, offset: 0x14 */
  __IO uint32_t TX_FRAME_CFG0                 ; /* Transmitter Frame Configure 0, offset: 0x18 */
  __IO uint32_t TX_FRAME_CFG1                 ; /* Transmitter Frame Configure 1, offset: 0x1C */
  __O  uint32_t TX_DATA[I2S_TX_DATA_COUNT]    ; /* Transmitter Data, offset: 0x20 */
       uint8_t  RESERVED_1[16];
  __I  uint32_t TX_FIFO_STATUS[I2S_TX_FIFO_STATUS_COUNT]; /* Transmitter FIFO Status, offset: 0x40 */
       uint8_t  RESERVED_2[16];
  __IO uint32_t TX_DATA_MASK                  ; /* Transmitter Data Mask, offset: 0x60 */
       uint8_t  RESERVED_3[36];
  __IO uint32_t RX_IDF                        ; /* Receiver Interrupt DMA and Flag, offset: 0x88 */
  __IO uint32_t RX_FIFO_CFG                   ; /* Receiver FIFO Configure, offset: 0x8C */
  __IO uint32_t RX_CLK_CFG                    ; /* Receiver Clock Configure, offset: 0x90 */
  __IO uint32_t RX_CHAN_CFG                   ; /* Receiver Channel Configure, offset: 0x94 */
  __IO uint32_t RX_FRAME_CFG0                 ; /* Receiver Frame Configure 0, offset: 0x98 */
  __IO uint32_t RX_FRAME_CFG1                 ; /* Receiver Frame Configure 1, offset: 0x9C */
  __I  uint32_t RX_DATA[I2S_RX_DATA_COUNT]    ; /* Receiver Data, offset: 0xa0 */
       uint8_t  RESERVED_4[16];
  __I  uint32_t RX_FIFO_STATUS[I2S_RX_FIFO_STATUS_COUNT]; /* Receiver FIFO Status, offset: 0xc0 */
       uint8_t  RESERVED_5[16];
  __IO uint32_t RX_DATA_MASK                  ; /* Receiver Data Mask, offset: 0xE0 */
} I2S_Type, *I2S_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- I2S Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup I2S_Register_Masks I2S Register Masks
 * @{
 */
 
/* TX_IDF Bit Fields */
#define I2S_TX_IDF_TXEN_MASK           0x80000000u
#define I2S_TX_IDF_TXEN_SHIFT          31u
#define I2S_TX_IDF_TXEN_WIDTH          1u
#define I2S_TX_IDF_TXEN(x)             (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_TXEN_SHIFT))&I2S_TX_IDF_TXEN_MASK)
#define I2S_TX_IDF_STOPEN_MASK         0x40000000u
#define I2S_TX_IDF_STOPEN_SHIFT        30u
#define I2S_TX_IDF_STOPEN_WIDTH        1u
#define I2S_TX_IDF_STOPEN(x)           (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_STOPEN_SHIFT))&I2S_TX_IDF_STOPEN_MASK)
#define I2S_TX_IDF_DBGEN_MASK          0x20000000u
#define I2S_TX_IDF_DBGEN_SHIFT         29u
#define I2S_TX_IDF_DBGEN_WIDTH         1u
#define I2S_TX_IDF_DBGEN(x)            (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_DBGEN_SHIFT))&I2S_TX_IDF_DBGEN_MASK)
#define I2S_TX_IDF_BCKEN_MASK          0x10000000u
#define I2S_TX_IDF_BCKEN_SHIFT         28u
#define I2S_TX_IDF_BCKEN_WIDTH         1u
#define I2S_TX_IDF_BCKEN(x)            (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_BCKEN_SHIFT))&I2S_TX_IDF_BCKEN_MASK)
#define I2S_TX_IDF_FIFORST_MASK        0x2000000u
#define I2S_TX_IDF_FIFORST_SHIFT       25u
#define I2S_TX_IDF_FIFORST_WIDTH       1u
#define I2S_TX_IDF_FIFORST(x)          (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFORST_SHIFT))&I2S_TX_IDF_FIFORST_MASK)
#define I2S_TX_IDF_SWRST_MASK          0x1000000u
#define I2S_TX_IDF_SWRST_SHIFT         24u
#define I2S_TX_IDF_SWRST_WIDTH         1u
#define I2S_TX_IDF_SWRST(x)            (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_SWRST_SHIFT))&I2S_TX_IDF_SWRST_MASK)
#define I2S_TX_IDF_DATA_SF_MASK        0x100000u
#define I2S_TX_IDF_DATA_SF_SHIFT       20u
#define I2S_TX_IDF_DATA_SF_WIDTH       1u
#define I2S_TX_IDF_DATA_SF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_DATA_SF_SHIFT))&I2S_TX_IDF_DATA_SF_MASK)
#define I2S_TX_IDF_SYNC_EF_MASK        0x80000u
#define I2S_TX_IDF_SYNC_EF_SHIFT       19u
#define I2S_TX_IDF_SYNC_EF_WIDTH       1u
#define I2S_TX_IDF_SYNC_EF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_SYNC_EF_SHIFT))&I2S_TX_IDF_SYNC_EF_MASK)
#define I2S_TX_IDF_FIFO_UF_MASK        0x40000u
#define I2S_TX_IDF_FIFO_UF_SHIFT       18u
#define I2S_TX_IDF_FIFO_UF_WIDTH       1u
#define I2S_TX_IDF_FIFO_UF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_UF_SHIFT))&I2S_TX_IDF_FIFO_UF_MASK)
#define I2S_TX_IDF_FIFO_EF_MASK        0x20000u
#define I2S_TX_IDF_FIFO_EF_SHIFT       17u
#define I2S_TX_IDF_FIFO_EF_WIDTH       1u
#define I2S_TX_IDF_FIFO_EF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_EF_SHIFT))&I2S_TX_IDF_FIFO_EF_MASK)
#define I2S_TX_IDF_FIFO_RF_MASK        0x10000u
#define I2S_TX_IDF_FIFO_RF_SHIFT       16u
#define I2S_TX_IDF_FIFO_RF_WIDTH       1u
#define I2S_TX_IDF_FIFO_RF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_RF_SHIFT))&I2S_TX_IDF_FIFO_RF_MASK)
#define I2S_TX_IDF_DATA_SIE_MASK       0x1000u
#define I2S_TX_IDF_DATA_SIE_SHIFT      12u
#define I2S_TX_IDF_DATA_SIE_WIDTH      1u
#define I2S_TX_IDF_DATA_SIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_DATA_SIE_SHIFT))&I2S_TX_IDF_DATA_SIE_MASK)
#define I2S_TX_IDF_SYNC_EIE_MASK       0x800u
#define I2S_TX_IDF_SYNC_EIE_SHIFT      11u
#define I2S_TX_IDF_SYNC_EIE_WIDTH      1u
#define I2S_TX_IDF_SYNC_EIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_SYNC_EIE_SHIFT))&I2S_TX_IDF_SYNC_EIE_MASK)
#define I2S_TX_IDF_FIFO_UIE_MASK       0x400u
#define I2S_TX_IDF_FIFO_UIE_SHIFT      10u
#define I2S_TX_IDF_FIFO_UIE_WIDTH      1u
#define I2S_TX_IDF_FIFO_UIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_UIE_SHIFT))&I2S_TX_IDF_FIFO_UIE_MASK)
#define I2S_TX_IDF_FIFO_EIE_MASK       0x200u
#define I2S_TX_IDF_FIFO_EIE_SHIFT      9u
#define I2S_TX_IDF_FIFO_EIE_WIDTH      1u
#define I2S_TX_IDF_FIFO_EIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_EIE_SHIFT))&I2S_TX_IDF_FIFO_EIE_MASK)
#define I2S_TX_IDF_FIFO_RIE_MASK       0x100u
#define I2S_TX_IDF_FIFO_RIE_SHIFT      8u
#define I2S_TX_IDF_FIFO_RIE_WIDTH      1u
#define I2S_TX_IDF_FIFO_RIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_RIE_SHIFT))&I2S_TX_IDF_FIFO_RIE_MASK)
#define I2S_TX_IDF_FIFO_EDE_MASK       0x2u
#define I2S_TX_IDF_FIFO_EDE_SHIFT      1u
#define I2S_TX_IDF_FIFO_EDE_WIDTH      1u
#define I2S_TX_IDF_FIFO_EDE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_EDE_SHIFT))&I2S_TX_IDF_FIFO_EDE_MASK)
#define I2S_TX_IDF_FIFO_RDE_MASK       0x1u
#define I2S_TX_IDF_FIFO_RDE_SHIFT      0u
#define I2S_TX_IDF_FIFO_RDE_WIDTH      1u
#define I2S_TX_IDF_FIFO_RDE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_IDF_FIFO_RDE_SHIFT))&I2S_TX_IDF_FIFO_RDE_MASK)
/* TX_IDF Reg Mask */
#define I2S_TX_IDF_MASK                0xF31F1F03u
/* TX_FIFO_CFG Bit Fields */
#define I2S_TX_FIFO_CFG_FWM_MASK       0x7u
#define I2S_TX_FIFO_CFG_FWM_SHIFT      0u
#define I2S_TX_FIFO_CFG_FWM_WIDTH      3u
#define I2S_TX_FIFO_CFG_FWM(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_FIFO_CFG_FWM_SHIFT))&I2S_TX_FIFO_CFG_FWM_MASK)
/* TX_FIFO_CFG Reg Mask */
#define I2S_TX_FIFO_CFG_MASK           0x00000007u
/* TX_CLK_CFG Bit Fields */
#define I2S_TX_CLK_CFG_SYNC_MASK       0x40000000u
#define I2S_TX_CLK_CFG_SYNC_SHIFT      30u
#define I2S_TX_CLK_CFG_SYNC_WIDTH      1u
#define I2S_TX_CLK_CFG_SYNC(x)         (((uint32_t)(((uint32_t)(x))<<I2S_TX_CLK_CFG_SYNC_SHIFT))&I2S_TX_CLK_CFG_SYNC_MASK)
#define I2S_TX_CLK_CFG_BCLK_LB_MASK    0x10000000u
#define I2S_TX_CLK_CFG_BCLK_LB_SHIFT   28u
#define I2S_TX_CLK_CFG_BCLK_LB_WIDTH   1u
#define I2S_TX_CLK_CFG_BCLK_LB(x)      (((uint32_t)(((uint32_t)(x))<<I2S_TX_CLK_CFG_BCLK_LB_SHIFT))&I2S_TX_CLK_CFG_BCLK_LB_MASK)
#define I2S_TX_CLK_CFG_MCLK_SEL_MASK   0xC000000u
#define I2S_TX_CLK_CFG_MCLK_SEL_SHIFT  26u
#define I2S_TX_CLK_CFG_MCLK_SEL_WIDTH  2u
#define I2S_TX_CLK_CFG_MCLK_SEL(x)     (((uint32_t)(((uint32_t)(x))<<I2S_TX_CLK_CFG_MCLK_SEL_SHIFT))&I2S_TX_CLK_CFG_MCLK_SEL_MASK)
#define I2S_TX_CLK_CFG_BCLK_POL_MASK   0x2000000u
#define I2S_TX_CLK_CFG_BCLK_POL_SHIFT  25u
#define I2S_TX_CLK_CFG_BCLK_POL_WIDTH  1u
#define I2S_TX_CLK_CFG_BCLK_POL(x)     (((uint32_t)(((uint32_t)(x))<<I2S_TX_CLK_CFG_BCLK_POL_SHIFT))&I2S_TX_CLK_CFG_BCLK_POL_MASK)
#define I2S_TX_CLK_CFG_BCLK_DIR_MASK   0x1000000u
#define I2S_TX_CLK_CFG_BCLK_DIR_SHIFT  24u
#define I2S_TX_CLK_CFG_BCLK_DIR_WIDTH  1u
#define I2S_TX_CLK_CFG_BCLK_DIR(x)     (((uint32_t)(((uint32_t)(x))<<I2S_TX_CLK_CFG_BCLK_DIR_SHIFT))&I2S_TX_CLK_CFG_BCLK_DIR_MASK)
#define I2S_TX_CLK_CFG_BCLK_DIV_MASK   0xFFu
#define I2S_TX_CLK_CFG_BCLK_DIV_SHIFT  0u
#define I2S_TX_CLK_CFG_BCLK_DIV_WIDTH  8u
#define I2S_TX_CLK_CFG_BCLK_DIV(x)     (((uint32_t)(((uint32_t)(x))<<I2S_TX_CLK_CFG_BCLK_DIV_SHIFT))&I2S_TX_CLK_CFG_BCLK_DIV_MASK)
/* TX_CLK_CFG Reg Mask */
#define I2S_TX_CLK_CFG_MASK            0x5F0000FFu
/* TX_CHAN_CFG Bit Fields */
#define I2S_TX_CHAN_CFG_FIFO_RST_MASK  0xF000000u
#define I2S_TX_CHAN_CFG_FIFO_RST_SHIFT 24u
#define I2S_TX_CHAN_CFG_FIFO_RST_WIDTH 4u
#define I2S_TX_CHAN_CFG_FIFO_RST(x)    (((uint32_t)(((uint32_t)(x))<<I2S_TX_CHAN_CFG_FIFO_RST_SHIFT))&I2S_TX_CHAN_CFG_FIFO_RST_MASK)
#define I2S_TX_CHAN_CFG_CHAN_EN_MASK   0xF0000u
#define I2S_TX_CHAN_CFG_CHAN_EN_SHIFT  16u
#define I2S_TX_CHAN_CFG_CHAN_EN_WIDTH  4u
#define I2S_TX_CHAN_CFG_CHAN_EN(x)     (((uint32_t)(((uint32_t)(x))<<I2S_TX_CHAN_CFG_CHAN_EN_SHIFT))&I2S_TX_CHAN_CFG_CHAN_EN_MASK)
#define I2S_TX_CHAN_CFG_DSF_CFG_MASK   0xFu
#define I2S_TX_CHAN_CFG_DSF_CFG_SHIFT  0u
#define I2S_TX_CHAN_CFG_DSF_CFG_WIDTH  4u
#define I2S_TX_CHAN_CFG_DSF_CFG(x)     (((uint32_t)(((uint32_t)(x))<<I2S_TX_CHAN_CFG_DSF_CFG_SHIFT))&I2S_TX_CHAN_CFG_DSF_CFG_MASK)
/* TX_CHAN_CFG Reg Mask */
#define I2S_TX_CHAN_CFG_MASK           0x0F0F000Fu
/* TX_FRAME_CFG0 Bit Fields */
#define I2S_TX_FRAME_CFG0_RESTART_MASK 0x10000000u
#define I2S_TX_FRAME_CFG0_RESTART_SHIFT 28u
#define I2S_TX_FRAME_CFG0_RESTART_WIDTH 1u
#define I2S_TX_FRAME_CFG0_RESTART(x)   (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_RESTART_SHIFT))&I2S_TX_FRAME_CFG0_RESTART_MASK)
#define I2S_TX_FRAME_CFG0_FIFO_PACK_MASK 0x3000000u
#define I2S_TX_FRAME_CFG0_FIFO_PACK_SHIFT 24u
#define I2S_TX_FRAME_CFG0_FIFO_PACK_WIDTH 2u
#define I2S_TX_FRAME_CFG0_FIFO_PACK(x) (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_FIFO_PACK_SHIFT))&I2S_TX_FRAME_CFG0_FIFO_PACK_MASK)
#define I2S_TX_FRAME_CFG0_FRM_SZ_MASK  0xF0000u
#define I2S_TX_FRAME_CFG0_FRM_SZ_SHIFT 16u
#define I2S_TX_FRAME_CFG0_FRM_SZ_WIDTH 4u
#define I2S_TX_FRAME_CFG0_FRM_SZ(x)    (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_FRM_SZ_SHIFT))&I2S_TX_FRAME_CFG0_FRM_SZ_MASK)
#define I2S_TX_FRAME_CFG0_SYNC_WID_MASK 0x1F00u
#define I2S_TX_FRAME_CFG0_SYNC_WID_SHIFT 8u
#define I2S_TX_FRAME_CFG0_SYNC_WID_WIDTH 5u
#define I2S_TX_FRAME_CFG0_SYNC_WID(x)  (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_SYNC_WID_SHIFT))&I2S_TX_FRAME_CFG0_SYNC_WID_MASK)
#define I2S_TX_FRAME_CFG0_PIN_CFG_MASK 0x20u
#define I2S_TX_FRAME_CFG0_PIN_CFG_SHIFT 5u
#define I2S_TX_FRAME_CFG0_PIN_CFG_WIDTH 1u
#define I2S_TX_FRAME_CFG0_PIN_CFG(x)   (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_PIN_CFG_SHIFT))&I2S_TX_FRAME_CFG0_PIN_CFG_MASK)
#define I2S_TX_FRAME_CFG0_MSBF_MASK    0x10u
#define I2S_TX_FRAME_CFG0_MSBF_SHIFT   4u
#define I2S_TX_FRAME_CFG0_MSBF_WIDTH   1u
#define I2S_TX_FRAME_CFG0_MSBF(x)      (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_MSBF_SHIFT))&I2S_TX_FRAME_CFG0_MSBF_MASK)
#define I2S_TX_FRAME_CFG0_FSE_MASK     0x8u
#define I2S_TX_FRAME_CFG0_FSE_SHIFT    3u
#define I2S_TX_FRAME_CFG0_FSE_WIDTH    1u
#define I2S_TX_FRAME_CFG0_FSE(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_FSE_SHIFT))&I2S_TX_FRAME_CFG0_FSE_MASK)
#define I2S_TX_FRAME_CFG0_FSM_MASK     0x4u
#define I2S_TX_FRAME_CFG0_FSM_SHIFT    2u
#define I2S_TX_FRAME_CFG0_FSM_WIDTH    1u
#define I2S_TX_FRAME_CFG0_FSM(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_FSM_SHIFT))&I2S_TX_FRAME_CFG0_FSM_MASK)
#define I2S_TX_FRAME_CFG0_FSP_MASK     0x2u
#define I2S_TX_FRAME_CFG0_FSP_SHIFT    1u
#define I2S_TX_FRAME_CFG0_FSP_WIDTH    1u
#define I2S_TX_FRAME_CFG0_FSP(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_FSP_SHIFT))&I2S_TX_FRAME_CFG0_FSP_MASK)
#define I2S_TX_FRAME_CFG0_FSD_MASK     0x1u
#define I2S_TX_FRAME_CFG0_FSD_SHIFT    0u
#define I2S_TX_FRAME_CFG0_FSD_WIDTH    1u
#define I2S_TX_FRAME_CFG0_FSD(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG0_FSD_SHIFT))&I2S_TX_FRAME_CFG0_FSD_MASK)
/* TX_FRAME_CFG0 Reg Mask */
#define I2S_TX_FRAME_CFG0_MASK         0x130F1F3Fu
/* TX_FRAME_CFG1 Bit Fields */
#define I2S_TX_FRAME_CFG1_RDW_MASK     0x1F000000u
#define I2S_TX_FRAME_CFG1_RDW_SHIFT    24u
#define I2S_TX_FRAME_CFG1_RDW_WIDTH    5u
#define I2S_TX_FRAME_CFG1_RDW(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG1_RDW_SHIFT))&I2S_TX_FRAME_CFG1_RDW_MASK)
#define I2S_TX_FRAME_CFG1_FDW_MASK     0x1F0000u
#define I2S_TX_FRAME_CFG1_FDW_SHIFT    16u
#define I2S_TX_FRAME_CFG1_FDW_WIDTH    5u
#define I2S_TX_FRAME_CFG1_FDW(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG1_FDW_SHIFT))&I2S_TX_FRAME_CFG1_FDW_MASK)
#define I2S_TX_FRAME_CFG1_FBS_MASK     0x1F00u
#define I2S_TX_FRAME_CFG1_FBS_SHIFT    8u
#define I2S_TX_FRAME_CFG1_FBS_WIDTH    5u
#define I2S_TX_FRAME_CFG1_FBS(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_FRAME_CFG1_FBS_SHIFT))&I2S_TX_FRAME_CFG1_FBS_MASK)
/* TX_FRAME_CFG1 Reg Mask */
#define I2S_TX_FRAME_CFG1_MASK         0x1F1F1F00u
/* TX_DATA Bit Fields */
#define I2S_TX_DATA_FIFO_DATA_MASK     0xFFFFFFFFu
#define I2S_TX_DATA_FIFO_DATA_SHIFT    0u
#define I2S_TX_DATA_FIFO_DATA_WIDTH    32u
#define I2S_TX_DATA_FIFO_DATA(x)       (((uint32_t)(((uint32_t)(x))<<I2S_TX_DATA_FIFO_DATA_SHIFT))&I2S_TX_DATA_FIFO_DATA_MASK)
/* TX_DATA0 Reg Mask */
#define I2S_TX_DATA_MASK               0xFFFFFFFFu
/* TX_FIFO_STATUS Bit Fields */
#define I2S_TX_FIFO_STATUS_FIFO_WADDR_MASK 0xF0000u
#define I2S_TX_FIFO_STATUS_FIFO_WADDR_SHIFT 16u
#define I2S_TX_FIFO_STATUS_FIFO_WADDR_WIDTH 4u
#define I2S_TX_FIFO_STATUS_FIFO_WADDR(x) (((uint32_t)(((uint32_t)(x))<<I2S_TX_FIFO_STATUS_FIFO_WADDR_SHIFT))&I2S_TX_FIFO_STATUS_FIFO_WADDR_MASK)
#define I2S_TX_FIFO_STATUS_FIFO_RADDR_MASK 0xFu
#define I2S_TX_FIFO_STATUS_FIFO_RADDR_SHIFT 0u
#define I2S_TX_FIFO_STATUS_FIFO_RADDR_WIDTH 4u
#define I2S_TX_FIFO_STATUS_FIFO_RADDR(x) (((uint32_t)(((uint32_t)(x))<<I2S_TX_FIFO_STATUS_FIFO_RADDR_SHIFT))&I2S_TX_FIFO_STATUS_FIFO_RADDR_MASK)
/* TX_FIFO_STATUS0 Reg Mask */
#define I2S_TX_FIFO_STATUS_MASK        0x000F000Fu
/* TX_DATA_MASK Bit Fields */
#define I2S_TX_DATA_MASK_TDM_MASK      0xFFFFu
#define I2S_TX_DATA_MASK_TDM_SHIFT     0u
#define I2S_TX_DATA_MASK_TDM_WIDTH     16u
#define I2S_TX_DATA_MASK_TDM(x)        (((uint32_t)(((uint32_t)(x))<<I2S_TX_DATA_MASK_TDM_SHIFT))&I2S_TX_DATA_MASK_TDM_MASK)
/* TX_DATA_MASK Reg Mask */
#define I2S_TX_DATA_MASK_MASK          0x0000FFFFu
/* RX_IDF Bit Fields */
#define I2S_RX_IDF_RXEN_MASK           0x80000000u
#define I2S_RX_IDF_RXEN_SHIFT          31u
#define I2S_RX_IDF_RXEN_WIDTH          1u
#define I2S_RX_IDF_RXEN(x)             (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_RXEN_SHIFT))&I2S_RX_IDF_RXEN_MASK)
#define I2S_RX_IDF_STOPEN_MASK         0x40000000u
#define I2S_RX_IDF_STOPEN_SHIFT        30u
#define I2S_RX_IDF_STOPEN_WIDTH        1u
#define I2S_RX_IDF_STOPEN(x)           (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_STOPEN_SHIFT))&I2S_RX_IDF_STOPEN_MASK)
#define I2S_RX_IDF_DBGEN_MASK          0x20000000u
#define I2S_RX_IDF_DBGEN_SHIFT         29u
#define I2S_RX_IDF_DBGEN_WIDTH         1u
#define I2S_RX_IDF_DBGEN(x)            (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_DBGEN_SHIFT))&I2S_RX_IDF_DBGEN_MASK)
#define I2S_RX_IDF_BCKEN_MASK          0x10000000u
#define I2S_RX_IDF_BCKEN_SHIFT         28u
#define I2S_RX_IDF_BCKEN_WIDTH         1u
#define I2S_RX_IDF_BCKEN(x)            (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_BCKEN_SHIFT))&I2S_RX_IDF_BCKEN_MASK)
#define I2S_RX_IDF_FIFORST_MASK        0x2000000u
#define I2S_RX_IDF_FIFORST_SHIFT       25u
#define I2S_RX_IDF_FIFORST_WIDTH       1u
#define I2S_RX_IDF_FIFORST(x)          (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFORST_SHIFT))&I2S_RX_IDF_FIFORST_MASK)
#define I2S_RX_IDF_SWRST_MASK          0x1000000u
#define I2S_RX_IDF_SWRST_SHIFT         24u
#define I2S_RX_IDF_SWRST_WIDTH         1u
#define I2S_RX_IDF_SWRST(x)            (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_SWRST_SHIFT))&I2S_RX_IDF_SWRST_MASK)
#define I2S_RX_IDF_DATA_SF_MASK        0x100000u
#define I2S_RX_IDF_DATA_SF_SHIFT       20u
#define I2S_RX_IDF_DATA_SF_WIDTH       1u
#define I2S_RX_IDF_DATA_SF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_DATA_SF_SHIFT))&I2S_RX_IDF_DATA_SF_MASK)
#define I2S_RX_IDF_SYNC_EF_MASK        0x80000u
#define I2S_RX_IDF_SYNC_EF_SHIFT       19u
#define I2S_RX_IDF_SYNC_EF_WIDTH       1u
#define I2S_RX_IDF_SYNC_EF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_SYNC_EF_SHIFT))&I2S_RX_IDF_SYNC_EF_MASK)
#define I2S_RX_IDF_FIFO_OF_MASK        0x40000u
#define I2S_RX_IDF_FIFO_OF_SHIFT       18u
#define I2S_RX_IDF_FIFO_OF_WIDTH       1u
#define I2S_RX_IDF_FIFO_OF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_OF_SHIFT))&I2S_RX_IDF_FIFO_OF_MASK)
#define I2S_RX_IDF_FIFO_FF_MASK        0x20000u
#define I2S_RX_IDF_FIFO_FF_SHIFT       17u
#define I2S_RX_IDF_FIFO_FF_WIDTH       1u
#define I2S_RX_IDF_FIFO_FF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_FF_SHIFT))&I2S_RX_IDF_FIFO_FF_MASK)
#define I2S_RX_IDF_FIFO_RF_MASK        0x10000u
#define I2S_RX_IDF_FIFO_RF_SHIFT       16u
#define I2S_RX_IDF_FIFO_RF_WIDTH       1u
#define I2S_RX_IDF_FIFO_RF(x)          (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_RF_SHIFT))&I2S_RX_IDF_FIFO_RF_MASK)
#define I2S_RX_IDF_DATA_SIE_MASK       0x1000u
#define I2S_RX_IDF_DATA_SIE_SHIFT      12u
#define I2S_RX_IDF_DATA_SIE_WIDTH      1u
#define I2S_RX_IDF_DATA_SIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_DATA_SIE_SHIFT))&I2S_RX_IDF_DATA_SIE_MASK)
#define I2S_RX_IDF_SYNC_EIE_MASK       0x800u
#define I2S_RX_IDF_SYNC_EIE_SHIFT      11u
#define I2S_RX_IDF_SYNC_EIE_WIDTH      1u
#define I2S_RX_IDF_SYNC_EIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_SYNC_EIE_SHIFT))&I2S_RX_IDF_SYNC_EIE_MASK)
#define I2S_RX_IDF_FIFO_OIE_MASK       0x400u
#define I2S_RX_IDF_FIFO_OIE_SHIFT      10u
#define I2S_RX_IDF_FIFO_OIE_WIDTH      1u
#define I2S_RX_IDF_FIFO_OIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_OIE_SHIFT))&I2S_RX_IDF_FIFO_OIE_MASK)
#define I2S_RX_IDF_FIFO_FIE_MASK       0x200u
#define I2S_RX_IDF_FIFO_FIE_SHIFT      9u
#define I2S_RX_IDF_FIFO_FIE_WIDTH      1u
#define I2S_RX_IDF_FIFO_FIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_FIE_SHIFT))&I2S_RX_IDF_FIFO_FIE_MASK)
#define I2S_RX_IDF_FIFO_RIE_MASK       0x100u
#define I2S_RX_IDF_FIFO_RIE_SHIFT      8u
#define I2S_RX_IDF_FIFO_RIE_WIDTH      1u
#define I2S_RX_IDF_FIFO_RIE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_RIE_SHIFT))&I2S_RX_IDF_FIFO_RIE_MASK)
#define I2S_RX_IDF_FIFO_FDE_MASK       0x2u
#define I2S_RX_IDF_FIFO_FDE_SHIFT      1u
#define I2S_RX_IDF_FIFO_FDE_WIDTH      1u
#define I2S_RX_IDF_FIFO_FDE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_FDE_SHIFT))&I2S_RX_IDF_FIFO_FDE_MASK)
#define I2S_RX_IDF_FIFO_RDE_MASK       0x1u
#define I2S_RX_IDF_FIFO_RDE_SHIFT      0u
#define I2S_RX_IDF_FIFO_RDE_WIDTH      1u
#define I2S_RX_IDF_FIFO_RDE(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_IDF_FIFO_RDE_SHIFT))&I2S_RX_IDF_FIFO_RDE_MASK)
/* RX_IDF Reg Mask */
#define I2S_RX_IDF_MASK                0xF31F1F03u
/* RX_FIFO_CFG Bit Fields */
#define I2S_RX_FIFO_CFG_FWM_MASK       0x7u
#define I2S_RX_FIFO_CFG_FWM_SHIFT      0u
#define I2S_RX_FIFO_CFG_FWM_WIDTH      3u
#define I2S_RX_FIFO_CFG_FWM(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_FIFO_CFG_FWM_SHIFT))&I2S_RX_FIFO_CFG_FWM_MASK)
/* RX_FIFO_CFG Reg Mask */
#define I2S_RX_FIFO_CFG_MASK           0x00000007u
/* RX_CLK_CFG Bit Fields */
#define I2S_RX_CLK_CFG_SYNC_MASK       0x40000000u
#define I2S_RX_CLK_CFG_SYNC_SHIFT      30u
#define I2S_RX_CLK_CFG_SYNC_WIDTH      1u
#define I2S_RX_CLK_CFG_SYNC(x)         (((uint32_t)(((uint32_t)(x))<<I2S_RX_CLK_CFG_SYNC_SHIFT))&I2S_RX_CLK_CFG_SYNC_MASK)
#define I2S_RX_CLK_CFG_BCLK_LB_MASK    0x10000000u
#define I2S_RX_CLK_CFG_BCLK_LB_SHIFT   28u
#define I2S_RX_CLK_CFG_BCLK_LB_WIDTH   1u
#define I2S_RX_CLK_CFG_BCLK_LB(x)      (((uint32_t)(((uint32_t)(x))<<I2S_RX_CLK_CFG_BCLK_LB_SHIFT))&I2S_RX_CLK_CFG_BCLK_LB_MASK)
#define I2S_RX_CLK_CFG_MCLK_SEL_MASK   0xC000000u
#define I2S_RX_CLK_CFG_MCLK_SEL_SHIFT  26u
#define I2S_RX_CLK_CFG_MCLK_SEL_WIDTH  2u
#define I2S_RX_CLK_CFG_MCLK_SEL(x)     (((uint32_t)(((uint32_t)(x))<<I2S_RX_CLK_CFG_MCLK_SEL_SHIFT))&I2S_RX_CLK_CFG_MCLK_SEL_MASK)
#define I2S_RX_CLK_CFG_BCLK_POL_MASK   0x2000000u
#define I2S_RX_CLK_CFG_BCLK_POL_SHIFT  25u
#define I2S_RX_CLK_CFG_BCLK_POL_WIDTH  1u
#define I2S_RX_CLK_CFG_BCLK_POL(x)     (((uint32_t)(((uint32_t)(x))<<I2S_RX_CLK_CFG_BCLK_POL_SHIFT))&I2S_RX_CLK_CFG_BCLK_POL_MASK)
#define I2S_RX_CLK_CFG_BCLK_DIR_MASK   0x1000000u
#define I2S_RX_CLK_CFG_BCLK_DIR_SHIFT  24u
#define I2S_RX_CLK_CFG_BCLK_DIR_WIDTH  1u
#define I2S_RX_CLK_CFG_BCLK_DIR(x)     (((uint32_t)(((uint32_t)(x))<<I2S_RX_CLK_CFG_BCLK_DIR_SHIFT))&I2S_RX_CLK_CFG_BCLK_DIR_MASK)
#define I2S_RX_CLK_CFG_BCLK_DIV_MASK   0xFFu
#define I2S_RX_CLK_CFG_BCLK_DIV_SHIFT  0u
#define I2S_RX_CLK_CFG_BCLK_DIV_WIDTH  8u
#define I2S_RX_CLK_CFG_BCLK_DIV(x)     (((uint32_t)(((uint32_t)(x))<<I2S_RX_CLK_CFG_BCLK_DIV_SHIFT))&I2S_RX_CLK_CFG_BCLK_DIV_MASK)
/* RX_CLK_CFG Reg Mask */
#define I2S_RX_CLK_CFG_MASK            0x5F0000FFu
/* RX_CHAN_CFG Bit Fields */
#define I2S_RX_CHAN_CFG_FIFO_RST_MASK  0xF000000u
#define I2S_RX_CHAN_CFG_FIFO_RST_SHIFT 24u
#define I2S_RX_CHAN_CFG_FIFO_RST_WIDTH 4u
#define I2S_RX_CHAN_CFG_FIFO_RST(x)    (((uint32_t)(((uint32_t)(x))<<I2S_RX_CHAN_CFG_FIFO_RST_SHIFT))&I2S_RX_CHAN_CFG_FIFO_RST_MASK)
#define I2S_RX_CHAN_CFG_CHAN_EN_MASK   0xF0000u
#define I2S_RX_CHAN_CFG_CHAN_EN_SHIFT  16u
#define I2S_RX_CHAN_CFG_CHAN_EN_WIDTH  4u
#define I2S_RX_CHAN_CFG_CHAN_EN(x)     (((uint32_t)(((uint32_t)(x))<<I2S_RX_CHAN_CFG_CHAN_EN_SHIFT))&I2S_RX_CHAN_CFG_CHAN_EN_MASK)
#define I2S_RX_CHAN_CFG_DSF_CFG_MASK   0xFu
#define I2S_RX_CHAN_CFG_DSF_CFG_SHIFT  0u
#define I2S_RX_CHAN_CFG_DSF_CFG_WIDTH  4u
#define I2S_RX_CHAN_CFG_DSF_CFG(x)     (((uint32_t)(((uint32_t)(x))<<I2S_RX_CHAN_CFG_DSF_CFG_SHIFT))&I2S_RX_CHAN_CFG_DSF_CFG_MASK)
/* RX_CHAN_CFG Reg Mask */
#define I2S_RX_CHAN_CFG_MASK           0x0F0F000Fu
/* RX_FRAME_CFG0 Bit Fields */
#define I2S_RX_FRAME_CFG0_RESTART_MASK 0x10000000u
#define I2S_RX_FRAME_CFG0_RESTART_SHIFT 28u
#define I2S_RX_FRAME_CFG0_RESTART_WIDTH 1u
#define I2S_RX_FRAME_CFG0_RESTART(x)   (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_RESTART_SHIFT))&I2S_RX_FRAME_CFG0_RESTART_MASK)
#define I2S_RX_FRAME_CFG0_FIFO_PACK_MASK 0x3000000u
#define I2S_RX_FRAME_CFG0_FIFO_PACK_SHIFT 24u
#define I2S_RX_FRAME_CFG0_FIFO_PACK_WIDTH 2u
#define I2S_RX_FRAME_CFG0_FIFO_PACK(x) (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_FIFO_PACK_SHIFT))&I2S_RX_FRAME_CFG0_FIFO_PACK_MASK)
#define I2S_RX_FRAME_CFG0_FRM_SZ_MASK  0xF0000u
#define I2S_RX_FRAME_CFG0_FRM_SZ_SHIFT 16u
#define I2S_RX_FRAME_CFG0_FRM_SZ_WIDTH 4u
#define I2S_RX_FRAME_CFG0_FRM_SZ(x)    (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_FRM_SZ_SHIFT))&I2S_RX_FRAME_CFG0_FRM_SZ_MASK)
#define I2S_RX_FRAME_CFG0_SYNC_WID_MASK 0x1F00u
#define I2S_RX_FRAME_CFG0_SYNC_WID_SHIFT 8u
#define I2S_RX_FRAME_CFG0_SYNC_WID_WIDTH 5u
#define I2S_RX_FRAME_CFG0_SYNC_WID(x)  (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_SYNC_WID_SHIFT))&I2S_RX_FRAME_CFG0_SYNC_WID_MASK)
#define I2S_RX_FRAME_CFG0_MSBF_MASK    0x10u
#define I2S_RX_FRAME_CFG0_MSBF_SHIFT   4u
#define I2S_RX_FRAME_CFG0_MSBF_WIDTH   1u
#define I2S_RX_FRAME_CFG0_MSBF(x)      (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_MSBF_SHIFT))&I2S_RX_FRAME_CFG0_MSBF_MASK)
#define I2S_RX_FRAME_CFG0_FSE_MASK     0x8u
#define I2S_RX_FRAME_CFG0_FSE_SHIFT    3u
#define I2S_RX_FRAME_CFG0_FSE_WIDTH    1u
#define I2S_RX_FRAME_CFG0_FSE(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_FSE_SHIFT))&I2S_RX_FRAME_CFG0_FSE_MASK)
#define I2S_RX_FRAME_CFG0_FSM_MASK     0x4u
#define I2S_RX_FRAME_CFG0_FSM_SHIFT    2u
#define I2S_RX_FRAME_CFG0_FSM_WIDTH    1u
#define I2S_RX_FRAME_CFG0_FSM(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_FSM_SHIFT))&I2S_RX_FRAME_CFG0_FSM_MASK)
#define I2S_RX_FRAME_CFG0_FSP_MASK     0x2u
#define I2S_RX_FRAME_CFG0_FSP_SHIFT    1u
#define I2S_RX_FRAME_CFG0_FSP_WIDTH    1u
#define I2S_RX_FRAME_CFG0_FSP(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_FSP_SHIFT))&I2S_RX_FRAME_CFG0_FSP_MASK)
#define I2S_RX_FRAME_CFG0_FSD_MASK     0x1u
#define I2S_RX_FRAME_CFG0_FSD_SHIFT    0u
#define I2S_RX_FRAME_CFG0_FSD_WIDTH    1u
#define I2S_RX_FRAME_CFG0_FSD(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG0_FSD_SHIFT))&I2S_RX_FRAME_CFG0_FSD_MASK)
/* RX_FRAME_CFG0 Reg Mask */
#define I2S_RX_FRAME_CFG0_MASK         0x130F1F1Fu
/* RX_FRAME_CFG1 Bit Fields */
#define I2S_RX_FRAME_CFG1_RDW_MASK     0x1F000000u
#define I2S_RX_FRAME_CFG1_RDW_SHIFT    24u
#define I2S_RX_FRAME_CFG1_RDW_WIDTH    5u
#define I2S_RX_FRAME_CFG1_RDW(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG1_RDW_SHIFT))&I2S_RX_FRAME_CFG1_RDW_MASK)
#define I2S_RX_FRAME_CFG1_FDW_MASK     0x1F0000u
#define I2S_RX_FRAME_CFG1_FDW_SHIFT    16u
#define I2S_RX_FRAME_CFG1_FDW_WIDTH    5u
#define I2S_RX_FRAME_CFG1_FDW(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG1_FDW_SHIFT))&I2S_RX_FRAME_CFG1_FDW_MASK)
#define I2S_RX_FRAME_CFG1_FBS_MASK     0x1F00u
#define I2S_RX_FRAME_CFG1_FBS_SHIFT    8u
#define I2S_RX_FRAME_CFG1_FBS_WIDTH    5u
#define I2S_RX_FRAME_CFG1_FBS(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_FRAME_CFG1_FBS_SHIFT))&I2S_RX_FRAME_CFG1_FBS_MASK)
/* RX_FRAME_CFG1 Reg Mask */
#define I2S_RX_FRAME_CFG1_MASK         0x1F1F1F00u
/* RX_DATA Bit Fields */
#define I2S_RX_DATA_FIFO_DATA_MASK     0xFFFFFFFFu
#define I2S_RX_DATA_FIFO_DATA_SHIFT    0u
#define I2S_RX_DATA_FIFO_DATA_WIDTH    32u
#define I2S_RX_DATA_FIFO_DATA(x)       (((uint32_t)(((uint32_t)(x))<<I2S_RX_DATA_FIFO_DATA_SHIFT))&I2S_RX_DATA_FIFO_DATA_MASK)
/* RX_DATA0 Reg Mask */
#define I2S_RX_DATA_MASK               0xFFFFFFFFu
/* RX_FIFO_STATUS Bit Fields */
#define I2S_RX_FIFO_STATUS_FIFO_WADDR_MASK 0xF0000u
#define I2S_RX_FIFO_STATUS_FIFO_WADDR_SHIFT 16u
#define I2S_RX_FIFO_STATUS_FIFO_WADDR_WIDTH 4u
#define I2S_RX_FIFO_STATUS_FIFO_WADDR(x) (((uint32_t)(((uint32_t)(x))<<I2S_RX_FIFO_STATUS_FIFO_WADDR_SHIFT))&I2S_RX_FIFO_STATUS_FIFO_WADDR_MASK)
#define I2S_RX_FIFO_STATUS_FIFO_RADDR_MASK 0xFu
#define I2S_RX_FIFO_STATUS_FIFO_RADDR_SHIFT 0u
#define I2S_RX_FIFO_STATUS_FIFO_RADDR_WIDTH 4u
#define I2S_RX_FIFO_STATUS_FIFO_RADDR(x) (((uint32_t)(((uint32_t)(x))<<I2S_RX_FIFO_STATUS_FIFO_RADDR_SHIFT))&I2S_RX_FIFO_STATUS_FIFO_RADDR_MASK)
/* RX_FIFO_STATUS0 Reg Mask */
#define I2S_RX_FIFO_STATUS_MASK        0x000F000Fu
/* RX_DATA_MASK Bit Fields */
#define I2S_RX_DATA_MASK_RDM_MASK      0xFFFFu
#define I2S_RX_DATA_MASK_RDM_SHIFT     0u
#define I2S_RX_DATA_MASK_RDM_WIDTH     16u
#define I2S_RX_DATA_MASK_RDM(x)        (((uint32_t)(((uint32_t)(x))<<I2S_RX_DATA_MASK_RDM_SHIFT))&I2S_RX_DATA_MASK_RDM_MASK)
/* RX_DATA_MASK Reg Mask */
#define I2S_RX_DATA_MASK_MASK          0x0000FFFFu
/**
 * @}
 */ /* end of group I2S_Register_Masks */
/**
 * @}
 */ /* end of group I2S_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
