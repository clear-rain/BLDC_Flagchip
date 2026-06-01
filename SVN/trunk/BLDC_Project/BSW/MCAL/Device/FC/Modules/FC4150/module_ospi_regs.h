#ifndef _MODULE_OSPI_KJO_Ufdi18_REGS_H_
#define _MODULE_OSPI_KJO_Ufdi18_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- OSPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup OSPI_Peripheral_Access_Layer OSPI Peripheral Access Layer
 * @{
 */
/** OSPI - Size of Registers Arrays */
/** OSPI - Register Layout Typedef */
#define OSPI_RFDR_COUNT 32
#define OSPI_LUT_COUNT 16
typedef struct {
  __IO uint32_t CTRL                          ; /* Control Register, offset: 0x0 */
       uint8_t  RESERVED_0[4];
  __IO uint32_t CMDC                          ; /* Command Control Register, offset: 0x8 */
  __IO uint32_t FLS_CFG                       ; /* Flash Configuration Register, offset: 0xC */
       uint8_t  RESERVED_1[20];
  __IO uint32_t SOC_CFG                       ; /* SOC Configuration Register, offset: 0x24 */
       uint8_t  RESERVED_2[216];
  __IO uint32_t FLS_AR                        ; /* Flash Address Register, offset: 0x100 */
  __IO uint32_t FLS_CAR                       ; /* Flash Column Address Register, offset: 0x104 */
  __IO uint32_t SAMP_CTRL                     ; /* Sampling Control Register, offset: 0x108 */
  __IO uint32_t RFSR                          ; /* Receive FIFO Status Register, offset: 0x10C */
  __IO uint32_t RF_CFG                        ; /* Receive FIFO Configuration Register, offset: 0x110 */
       uint8_t  RESERVED_3[12];
  __IO uint32_t RFD2R                         ; /* Receive FIFO Data Secondary Register, offset: 0x120 */
       uint8_t  RESERVED_4[44];
  __IO uint32_t TFSR                          ; /* Transmit FIFO Status Register, offset: 0x150 */
  __IO uint32_t TFDR                          ; /* Transmit FIFO Data Register, offset: 0x154 */
  __IO uint32_t TF_CFG                        ; /* Transmit FIFO Configuration Register, offset: 0x158 */
  __IO uint32_t STATUS                        ; /* Status Register, offset: 0x15C */
  __IO uint32_t FLAG                          ; /* Flag Register, offset: 0x160 */
  __IO uint32_t IND_EN                        ; /* Interrupt and DMA Enable Register, offset: 0x164 */
       uint8_t  RESERVED_5[24];
  __IO uint32_t FLS_TAR                       ; /* Flash Top Address Register, offset: 0x180 */
       uint8_t  RESERVED_6[124];
  __IO uint32_t RFDR[OSPI_RFDR_COUNT]         ; /* Receive FIFO Data Register, offset: 0x200 */
       uint8_t  RESERVED_7[128];
  __IO uint32_t LUT_KEY                       ; /* Lookup Table Key Register, offset: 0x300 */
  __IO uint32_t LUT_CFG                       ; /* Lookup Table Configuration Register, offset: 0x304 */
       uint8_t  RESERVED_8[8];
  __IO uint32_t LUT[OSPI_LUT_COUNT]           ; /* Lookup Table Register, offset: 0x310 */
} OSPI_Type, *OSPI_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- OSPI Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup OSPI_Register_Masks OSPI Register Masks
 * @{
 */
/* CTRL Bit Fields */
#define OSPI_CTRL_DSDIO3_MASK          0x20000u
#define OSPI_CTRL_DSDIO3_SHIFT         17u
#define OSPI_CTRL_DSDIO3_WIDTH         1u
#define OSPI_CTRL_DSDIO3(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_DSDIO3_SHIFT))&OSPI_CTRL_DSDIO3_MASK)
#define OSPI_CTRL_DSDIO2_MASK          0x10000u
#define OSPI_CTRL_DSDIO2_SHIFT         16u
#define OSPI_CTRL_DSDIO2_WIDTH         1u
#define OSPI_CTRL_DSDIO2(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_DSDIO2_SHIFT))&OSPI_CTRL_DSDIO2_MASK)
#define OSPI_CTRL_WAIT_MASK            0x8000u
#define OSPI_CTRL_WAIT_SHIFT           15u
#define OSPI_CTRL_WAIT_WIDTH           1u
#define OSPI_CTRL_WAIT(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_WAIT_SHIFT))&OSPI_CTRL_WAIT_MASK)
#define OSPI_CTRL_MDIS_MASK            0x4000u
#define OSPI_CTRL_MDIS_SHIFT           14u
#define OSPI_CTRL_MDIS_WIDTH           1u
#define OSPI_CTRL_MDIS(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_MDIS_SHIFT))&OSPI_CTRL_MDIS_MASK)
#define OSPI_CTRL_XFRWT_CFG_MASK       0x3000u
#define OSPI_CTRL_XFRWT_CFG_SHIFT      12u
#define OSPI_CTRL_XFRWT_CFG_WIDTH      2u
#define OSPI_CTRL_XFRWT_CFG(x)         (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_XFRWT_CFG_SHIFT))&OSPI_CTRL_XFRWT_CFG_MASK)
#define OSPI_CTRL_CLR_TF_MASK          0x800u
#define OSPI_CTRL_CLR_TF_SHIFT         11u
#define OSPI_CTRL_CLR_TF_WIDTH         1u
#define OSPI_CTRL_CLR_TF(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_CLR_TF_SHIFT))&OSPI_CTRL_CLR_TF_MASK)
#define OSPI_CTRL_CLR_RF_MASK          0x400u
#define OSPI_CTRL_CLR_RF_SHIFT         10u
#define OSPI_CTRL_CLR_RF_WIDTH         1u
#define OSPI_CTRL_CLR_RF(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_CLR_RF_SHIFT))&OSPI_CTRL_CLR_RF_MASK)
#define OSPI_CTRL_LAT_CFG_MASK         0x100u
#define OSPI_CTRL_LAT_CFG_SHIFT        8u
#define OSPI_CTRL_LAT_CFG_WIDTH        1u
#define OSPI_CTRL_LAT_CFG(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_LAT_CFG_SHIFT))&OSPI_CTRL_LAT_CFG_MASK)
#define OSPI_CTRL_DDR_EN_MASK          0x80u
#define OSPI_CTRL_DDR_EN_SHIFT         7u
#define OSPI_CTRL_DDR_EN_WIDTH         1u
#define OSPI_CTRL_DDR_EN(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_DDR_EN_SHIFT))&OSPI_CTRL_DDR_EN_MASK)
#define OSPI_CTRL_DQS_EN_MASK          0x40u
#define OSPI_CTRL_DQS_EN_SHIFT         6u
#define OSPI_CTRL_DQS_EN_WIDTH         1u
#define OSPI_CTRL_DQS_EN(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_DQS_EN_SHIFT))&OSPI_CTRL_DQS_EN_MASK)
#define OSPI_CTRL_DQS_LAT_MASK         0x20u
#define OSPI_CTRL_DQS_LAT_SHIFT        5u
#define OSPI_CTRL_DQS_LAT_WIDTH        1u
#define OSPI_CTRL_DQS_LAT(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_DQS_LAT_SHIFT))&OSPI_CTRL_DQS_LAT_MASK)
#define OSPI_CTRL_DQS_OUT_MASK         0x10u
#define OSPI_CTRL_DQS_OUT_SHIFT        4u
#define OSPI_CTRL_DQS_OUT_WIDTH        1u
#define OSPI_CTRL_DQS_OUT(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_DQS_OUT_SHIFT))&OSPI_CTRL_DQS_OUT_MASK)
#define OSPI_CTRL_ENDIAN_MASK          0x4u
#define OSPI_CTRL_ENDIAN_SHIFT         2u
#define OSPI_CTRL_ENDIAN_WIDTH         1u
#define OSPI_CTRL_ENDIAN(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_ENDIAN_SHIFT))&OSPI_CTRL_ENDIAN_MASK)
#define OSPI_CTRL_SWRST_MASK           0x1u
#define OSPI_CTRL_SWRST_SHIFT          0u
#define OSPI_CTRL_SWRST_WIDTH          1u
#define OSPI_CTRL_SWRST(x)             (((uint32_t)(((uint32_t)(x))<<OSPI_CTRL_SWRST_SHIFT))&OSPI_CTRL_SWRST_MASK)
/* CTRL Reg Mask */
#define OSPI_CTRL_MASK                 0x0003FDF5u
/* CMDC Bit Fields */
#define OSPI_CMDC_CMD_ID_MASK          0xF000000u
#define OSPI_CMDC_CMD_ID_SHIFT         24u
#define OSPI_CMDC_CMD_ID_WIDTH         4u
#define OSPI_CMDC_CMD_ID(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_CMDC_CMD_ID_SHIFT))&OSPI_CMDC_CMD_ID_MASK)
#define OSPI_CMDC_CMD_SIZE_MASK        0xFFFFu
#define OSPI_CMDC_CMD_SIZE_SHIFT       0u
#define OSPI_CMDC_CMD_SIZE_WIDTH       16u
#define OSPI_CMDC_CMD_SIZE(x)          (((uint32_t)(((uint32_t)(x))<<OSPI_CMDC_CMD_SIZE_SHIFT))&OSPI_CMDC_CMD_SIZE_MASK)
/* CMDC Reg Mask */
#define OSPI_CMDC_MASK                 0x0F00FFFFu
/* FLS_CFG Bit Fields */
#define OSPI_FLS_CFG_TDH_MASK          0x30000u
#define OSPI_FLS_CFG_TDH_SHIFT         16u
#define OSPI_FLS_CFG_TDH_WIDTH         2u
#define OSPI_FLS_CFG_TDH(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_FLS_CFG_TDH_SHIFT))&OSPI_FLS_CFG_TDH_MASK)
#define OSPI_FLS_CFG_TCSH_MASK         0xF00u
#define OSPI_FLS_CFG_TCSH_SHIFT        8u
#define OSPI_FLS_CFG_TCSH_WIDTH        4u
#define OSPI_FLS_CFG_TCSH(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_FLS_CFG_TCSH_SHIFT))&OSPI_FLS_CFG_TCSH_MASK)
#define OSPI_FLS_CFG_TCSS_MASK         0x0Fu
#define OSPI_FLS_CFG_TCSS_SHIFT        0u
#define OSPI_FLS_CFG_TCSS_WIDTH        4u
#define OSPI_FLS_CFG_TCSS(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_FLS_CFG_TCSS_SHIFT))&OSPI_FLS_CFG_TCSS_MASK)
/* FLS_CFG Reg Mask */
#define OSPI_FLS_CFG_MASK              0x00030F0Fu
/* SOC_CFG Bit Fields */
#define OSPI_SOC_CFG_CLK_EN_MASK       0x80000000u
#define OSPI_SOC_CFG_CLK_EN_SHIFT      31u
#define OSPI_SOC_CFG_CLK_EN_WIDTH      1u
#define OSPI_SOC_CFG_CLK_EN(x)         (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_CLK_EN_SHIFT))&OSPI_SOC_CFG_CLK_EN_MASK)
#define OSPI_SOC_CFG_CLK_DIV_MASK      0x70000000u
#define OSPI_SOC_CFG_CLK_DIV_SHIFT     28u
#define OSPI_SOC_CFG_CLK_DIV_WIDTH     3u
#define OSPI_SOC_CFG_CLK_DIV(x)        (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_CLK_DIV_SHIFT))&OSPI_SOC_CFG_CLK_DIV_MASK)
#define OSPI_SOC_CFG_IBE_EN_MASK       0x8000000u
#define OSPI_SOC_CFG_IBE_EN_SHIFT      27u
#define OSPI_SOC_CFG_IBE_EN_WIDTH      1u
#define OSPI_SOC_CFG_IBE_EN(x)         (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_IBE_EN_SHIFT))&OSPI_SOC_CFG_IBE_EN_MASK)
#define OSPI_SOC_CFG_CLK_MUX_MASK      0x6000000u
#define OSPI_SOC_CFG_CLK_MUX_SHIFT     25u
#define OSPI_SOC_CFG_CLK_MUX_WIDTH     2u
#define OSPI_SOC_CFG_CLK_MUX(x)        (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_CLK_MUX_SHIFT))&OSPI_SOC_CFG_CLK_MUX_MASK)
#define OSPI_SOC_CFG_DQS_INV_MASK      0x1000000u
#define OSPI_SOC_CFG_DQS_INV_SHIFT     24u
#define OSPI_SOC_CFG_DQS_INV_WIDTH     1u
#define OSPI_SOC_CFG_DQS_INV(x)        (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_DQS_INV_SHIFT))&OSPI_SOC_CFG_DQS_INV_MASK)
#define OSPI_SOC_CFG_DQS_MUX_MASK      0xC00000u
#define OSPI_SOC_CFG_DQS_MUX_SHIFT     22u
#define OSPI_SOC_CFG_DQS_MUX_WIDTH     2u
#define OSPI_SOC_CFG_DQS_MUX(x)        (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_DQS_MUX_SHIFT))&OSPI_SOC_CFG_DQS_MUX_MASK)
#define OSPI_SOC_CFG_OBE_RELAX_MASK    0x100000u
#define OSPI_SOC_CFG_OBE_RELAX_SHIFT   20u
#define OSPI_SOC_CFG_OBE_RELAX_WIDTH   1u
#define OSPI_SOC_CFG_OBE_RELAX(x)      (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_OBE_RELAX_SHIFT))&OSPI_SOC_CFG_OBE_RELAX_MASK)
#define OSPI_SOC_CFG_DDR_EN_MASK       0x80000u
#define OSPI_SOC_CFG_DDR_EN_SHIFT      19u
#define OSPI_SOC_CFG_DDR_EN_WIDTH      1u
#define OSPI_SOC_CFG_DDR_EN(x)         (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_DDR_EN_SHIFT))&OSPI_SOC_CFG_DDR_EN_MASK)
#define OSPI_SOC_CFG_DLLINE_CFG_MASK   0xFFu
#define OSPI_SOC_CFG_DLLINE_CFG_SHIFT  0u
#define OSPI_SOC_CFG_DLLINE_CFG_WIDTH  8u
#define OSPI_SOC_CFG_DLLINE_CFG(x)     (((uint32_t)(((uint32_t)(x))<<OSPI_SOC_CFG_DLLINE_CFG_SHIFT))&OSPI_SOC_CFG_DLLINE_CFG_MASK)
/* SOC_CFG Reg Mask */
#define OSPI_SOC_CFG_MASK              0xFFD800FFu
/* FLS_AR Bit Fields */
#define OSPI_FLS_AR_FLASH_ADDR_MASK    0xFFFFFFFFu
#define OSPI_FLS_AR_FLASH_ADDR_SHIFT   0u
#define OSPI_FLS_AR_FLASH_ADDR_WIDTH   32u
#define OSPI_FLS_AR_FLASH_ADDR(x)      (((uint32_t)(((uint32_t)(x))<<OSPI_FLS_AR_FLASH_ADDR_SHIFT))&OSPI_FLS_AR_FLASH_ADDR_MASK)
/* FLS_AR Reg Mask */
#define OSPI_FLS_AR_MASK               0xFFFFFFFFu
/* FLS_CAR Bit Fields */
#define OSPI_FLS_CAR_WA_MASK           0x10000u
#define OSPI_FLS_CAR_WA_SHIFT          16u
#define OSPI_FLS_CAR_WA_WIDTH          1u
#define OSPI_FLS_CAR_WA(x)             (((uint32_t)(((uint32_t)(x))<<OSPI_FLS_CAR_WA_SHIFT))&OSPI_FLS_CAR_WA_MASK)
#define OSPI_FLS_CAR_CAS_MASK          0xFu
#define OSPI_FLS_CAR_CAS_SHIFT         0u
#define OSPI_FLS_CAR_CAS_WIDTH         4u
#define OSPI_FLS_CAR_CAS(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_FLS_CAR_CAS_SHIFT))&OSPI_FLS_CAR_CAS_MASK)
/* FLS_CAR Reg Mask */
#define OSPI_FLS_CAR_MASK              0x0001000Fu
/* SAMP_CTRL Bit Fields */
#define OSPI_SAMP_CTRL_DLY_MASK        0x40u
#define OSPI_SAMP_CTRL_DLY_SHIFT       6u
#define OSPI_SAMP_CTRL_DLY_WIDTH       1u
#define OSPI_SAMP_CTRL_DLY(x)          (((uint32_t)(((uint32_t)(x))<<OSPI_SAMP_CTRL_DLY_SHIFT))&OSPI_SAMP_CTRL_DLY_MASK)
#define OSPI_SAMP_CTRL_PHS_MASK        0x20u
#define OSPI_SAMP_CTRL_PHS_SHIFT       5u
#define OSPI_SAMP_CTRL_PHS_WIDTH       1u
#define OSPI_SAMP_CTRL_PHS(x)          (((uint32_t)(((uint32_t)(x))<<OSPI_SAMP_CTRL_PHS_SHIFT))&OSPI_SAMP_CTRL_PHS_MASK)
/* SAMP_CTRL Reg Mask */
#define OSPI_SAMP_CTRL_MASK            0x00000060u
/* RFSR Bit Fields */
#define OSPI_RFSR_RFCTR_MASK           0xFFFF0000u
#define OSPI_RFSR_RFCTR_SHIFT          16u
#define OSPI_RFSR_RFCTR_WIDTH          16u
#define OSPI_RFSR_RFCTR(x)             (((uint32_t)(((uint32_t)(x))<<OSPI_RFSR_RFCTR_SHIFT))&OSPI_RFSR_RFCTR_MASK)
#define OSPI_RFSR_RFFL_MASK            0x3F00u
#define OSPI_RFSR_RFFL_SHIFT           8u
#define OSPI_RFSR_RFFL_WIDTH           6u
#define OSPI_RFSR_RFFL(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_RFSR_RFFL_SHIFT))&OSPI_RFSR_RFFL_MASK)
/* RFSR Reg Mask */
#define OSPI_RFSR_MASK                 0xFFFF3F00u
/* RF_CFG Bit Fields */
#define OSPI_RF_CFG_WMRK_MASK          0x1Fu
#define OSPI_RF_CFG_WMRK_SHIFT         0u
#define OSPI_RF_CFG_WMRK_WIDTH         5u
#define OSPI_RF_CFG_WMRK(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_RF_CFG_WMRK_SHIFT))&OSPI_RF_CFG_WMRK_MASK)
/* RF_CFG Reg Mask */
#define OSPI_RF_CFG_MASK               0x0000001Fu
/* TFSR Bit Fields */
#define OSPI_TFSR_TFCTR_MASK           0xFFFF0000u
#define OSPI_TFSR_TFCTR_SHIFT          16u
#define OSPI_TFSR_TFCTR_WIDTH          16u
#define OSPI_TFSR_TFCTR(x)             (((uint32_t)(((uint32_t)(x))<<OSPI_TFSR_TFCTR_SHIFT))&OSPI_TFSR_TFCTR_MASK)
#define OSPI_TFSR_TFFL_MASK            0x3F00u
#define OSPI_TFSR_TFFL_SHIFT           8u
#define OSPI_TFSR_TFFL_WIDTH           6u
#define OSPI_TFSR_TFFL(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_TFSR_TFFL_SHIFT))&OSPI_TFSR_TFFL_MASK)
/* TFSR Reg Mask */
#define OSPI_TFSR_MASK                 0xFFFF3F00u
/* TFDR Bit Fields */
#define OSPI_TFDR_TXDATA_MASK          0xFFFFFFFFu
#define OSPI_TFDR_TXDATA_SHIFT         0u
#define OSPI_TFDR_TXDATA_WIDTH         32u
#define OSPI_TFDR_TXDATA(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_TFDR_TXDATA_SHIFT))&OSPI_TFDR_TXDATA_MASK)
/* TFDR Reg Mask */
#define OSPI_TFDR_MASK                 0xFFFFFFFFu
/* TF_CFG Bit Fields */
#define OSPI_TF_CFG_WMRK_MASK          0x1Fu
#define OSPI_TF_CFG_WMRK_SHIFT         0u
#define OSPI_TF_CFG_WMRK_WIDTH         5u
#define OSPI_TF_CFG_WMRK(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_TF_CFG_WMRK_SHIFT))&OSPI_TF_CFG_WMRK_MASK)
/* TF_CFG Reg Mask */
#define OSPI_TF_CFG_MASK               0x0000001Fu
/* STATUS Bit Fields */
#define OSPI_STATUS_TFFULL_MASK        0x8000000u
#define OSPI_STATUS_TFFULL_SHIFT       27u
#define OSPI_STATUS_TFFULL_WIDTH       1u
#define OSPI_STATUS_TFFULL(x)          (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_TFFULL_SHIFT))&OSPI_STATUS_TFFULL_MASK)
#define OSPI_STATUS_TFDMA_MASK         0x4000000u
#define OSPI_STATUS_TFDMA_SHIFT        26u
#define OSPI_STATUS_TFDMA_WIDTH        1u
#define OSPI_STATUS_TFDMA(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_TFDMA_SHIFT))&OSPI_STATUS_TFDMA_MASK)
#define OSPI_STATUS_TFWDA_MASK         0x2000000u
#define OSPI_STATUS_TFWDA_SHIFT        25u
#define OSPI_STATUS_TFWDA_WIDTH        1u
#define OSPI_STATUS_TFWDA(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_TFWDA_SHIFT))&OSPI_STATUS_TFWDA_MASK)
#define OSPI_STATUS_TFEDA_MASK         0x1000000u
#define OSPI_STATUS_TFEDA_SHIFT        24u
#define OSPI_STATUS_TFEDA_WIDTH        1u
#define OSPI_STATUS_TFEDA(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_TFEDA_SHIFT))&OSPI_STATUS_TFEDA_MASK)
#define OSPI_STATUS_RFDMA_MASK         0x800000u
#define OSPI_STATUS_RFDMA_SHIFT        23u
#define OSPI_STATUS_RFDMA_WIDTH        1u
#define OSPI_STATUS_RFDMA(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_RFDMA_SHIFT))&OSPI_STATUS_RFDMA_MASK)
#define OSPI_STATUS_RFFULL_MASK        0x80000u
#define OSPI_STATUS_RFFULL_SHIFT       19u
#define OSPI_STATUS_RFFULL_WIDTH       1u
#define OSPI_STATUS_RFFULL(x)          (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_RFFULL_SHIFT))&OSPI_STATUS_RFFULL_MASK)
#define OSPI_STATUS_RFWDA_MASK         0x10000u
#define OSPI_STATUS_RFWDA_SHIFT        16u
#define OSPI_STATUS_RFWDA_WIDTH        1u
#define OSPI_STATUS_RFWDA(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_RFWDA_SHIFT))&OSPI_STATUS_RFWDA_MASK)
#define OSPI_STATUS_BUS_ACC_MASK       0x2u
#define OSPI_STATUS_BUS_ACC_SHIFT      1u
#define OSPI_STATUS_BUS_ACC_WIDTH      1u
#define OSPI_STATUS_BUS_ACC(x)         (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_BUS_ACC_SHIFT))&OSPI_STATUS_BUS_ACC_MASK)
#define OSPI_STATUS_BUSY_MASK       0x1u
#define OSPI_STATUS_BUSY_SHIFT      0u
#define OSPI_STATUS_BUSY_WIDTH      1u
#define OSPI_STATUS_BUSY(x)         (((uint32_t)(((uint32_t)(x))<<OSPI_STATUS_BUSY_SHIFT))&OSPI_STATUS_BUSY_MASK)
/* STATUS Reg Mask */
#define OSPI_STATUS_MASK               0x0F890003u
/* FLAG Bit Fields */
#define OSPI_FLAG_TFFF_MASK            0x8000000u
#define OSPI_FLAG_TFFF_SHIFT           27u
#define OSPI_FLAG_TFFF_WIDTH           1u
#define OSPI_FLAG_TFFF(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_FLAG_TFFF_SHIFT))&OSPI_FLAG_TFFF_MASK)
#define OSPI_FLAG_TFUF_MASK            0x4000000u
#define OSPI_FLAG_TFUF_SHIFT           26u
#define OSPI_FLAG_TFUF_WIDTH           1u
#define OSPI_FLAG_TFUF(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_FLAG_TFUF_SHIFT))&OSPI_FLAG_TFUF_MASK)
#define OSPI_FLAG_ECF_MASK             0x800000u
#define OSPI_FLAG_ECF_SHIFT            23u
#define OSPI_FLAG_ECF_WIDTH            1u
#define OSPI_FLAG_ECF(x)               (((uint32_t)(((uint32_t)(x))<<OSPI_FLAG_ECF_SHIFT))&OSPI_FLAG_ECF_MASK)
#define OSPI_FLAG_RFOF_MASK            0x20000u
#define OSPI_FLAG_RFOF_SHIFT           17u
#define OSPI_FLAG_RFOF_WIDTH           1u
#define OSPI_FLAG_RFOF(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_FLAG_RFOF_SHIFT))&OSPI_FLAG_RFOF_MASK)
#define OSPI_FLAG_RFDF_MASK            0x10000u
#define OSPI_FLAG_RFDF_SHIFT           16u
#define OSPI_FLAG_RFDF_WIDTH           1u
#define OSPI_FLAG_RFDF(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_FLAG_RFDF_SHIFT))&OSPI_FLAG_RFDF_MASK)
#define OSPI_FLAG_BUSEF_MASK           0x40u
#define OSPI_FLAG_BUSEF_SHIFT          6u
#define OSPI_FLAG_BUSEF_WIDTH          1u
#define OSPI_FLAG_BUSEF(x)             (((uint32_t)(((uint32_t)(x))<<OSPI_FLAG_BUSEF_SHIFT))&OSPI_FLAG_BUSEF_MASK)
#define OSPI_FLAG_BUSDF_MASK           0x1u
#define OSPI_FLAG_BUSDF_SHIFT          0u
#define OSPI_FLAG_BUSDF_WIDTH          1u
#define OSPI_FLAG_BUSDF(x)             (((uint32_t)(((uint32_t)(x))<<OSPI_FLAG_BUSDF_SHIFT))&OSPI_FLAG_BUSDF_MASK)
/* FLAG Reg Mask */
#define OSPI_FLAG_MASK                 0x0C830041u
/* IND_EN Bit Fields */
#define OSPI_IND_EN_TFFIE_MASK         0x8000000u
#define OSPI_IND_EN_TFFIE_SHIFT        27u
#define OSPI_IND_EN_TFFIE_WIDTH        1u
#define OSPI_IND_EN_TFFIE(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_TFFIE_SHIFT))&OSPI_IND_EN_TFFIE_MASK)
#define OSPI_IND_EN_TFUIE_MASK         0x4000000u
#define OSPI_IND_EN_TFUIE_SHIFT        26u
#define OSPI_IND_EN_TFUIE_WIDTH        1u
#define OSPI_IND_EN_TFUIE(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_TFUIE_SHIFT))&OSPI_IND_EN_TFUIE_MASK)
#define OSPI_IND_EN_TFFDRE_MASK        0x2000000u
#define OSPI_IND_EN_TFFDRE_SHIFT       25u
#define OSPI_IND_EN_TFFDRE_WIDTH       1u
#define OSPI_IND_EN_TFFDRE(x)          (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_TFFDRE_SHIFT))&OSPI_IND_EN_TFFDRE_MASK)
#define OSPI_IND_EN_ECIE_MASK          0x800000u
#define OSPI_IND_EN_ECIE_SHIFT         23u
#define OSPI_IND_EN_ECIE_WIDTH         1u
#define OSPI_IND_EN_ECIE(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_ECIE_SHIFT))&OSPI_IND_EN_ECIE_MASK)
#define OSPI_IND_EN_RFDDRE_MASK        0x200000u
#define OSPI_IND_EN_RFDDRE_SHIFT       21u
#define OSPI_IND_EN_RFDDRE_WIDTH       1u
#define OSPI_IND_EN_RFDDRE(x)          (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_RFDDRE_SHIFT))&OSPI_IND_EN_RFDDRE_MASK)
#define OSPI_IND_EN_RFOIE_MASK         0x20000u
#define OSPI_IND_EN_RFOIE_SHIFT        17u
#define OSPI_IND_EN_RFOIE_WIDTH        1u
#define OSPI_IND_EN_RFOIE(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_RFOIE_SHIFT))&OSPI_IND_EN_RFOIE_MASK)
#define OSPI_IND_EN_RFDIE_MASK         0x10000u
#define OSPI_IND_EN_RFDIE_SHIFT        16u
#define OSPI_IND_EN_RFDIE_WIDTH        1u
#define OSPI_IND_EN_RFDIE(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_RFDIE_SHIFT))&OSPI_IND_EN_RFDIE_MASK)
#define OSPI_IND_EN_BUSEE_MASK         0x40u
#define OSPI_IND_EN_BUSEE_SHIFT        6u
#define OSPI_IND_EN_BUSEE_WIDTH        1u
#define OSPI_IND_EN_BUSEE(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_BUSEE_SHIFT))&OSPI_IND_EN_BUSEE_MASK)
#define OSPI_IND_EN_TDIE_MASK          0x1u
#define OSPI_IND_EN_TDIE_SHIFT         0u
#define OSPI_IND_EN_TDIE_WIDTH         1u
#define OSPI_IND_EN_TDIE(x)            (((uint32_t)(((uint32_t)(x))<<OSPI_IND_EN_TDIE_SHIFT))&OSPI_IND_EN_TDIE_MASK)
/* IND_EN Reg Mask */
#define OSPI_IND_EN_MASK               0x0EA30041u
/* FLS_TAR Bit Fields */
#define OSPI_FLS_TAR_TOP_ADDR_MASK     0xFFFFFC00u
#define OSPI_FLS_TAR_TOP_ADDR_SHIFT    10u
#define OSPI_FLS_TAR_TOP_ADDR_WIDTH    22u
#define OSPI_FLS_TAR_TOP_ADDR(x)       (((uint32_t)(((uint32_t)(x))<<OSPI_FLS_TAR_TOP_ADDR_SHIFT))&OSPI_FLS_TAR_TOP_ADDR_MASK)
/* FLS_TAR Reg Mask */
#define OSPI_FLS_TAR_MASK              0xFFFFFC00u
/* RFDR Bit Fields */
#define OSPI_RFDR_DATA_MASK            0xFFFFFFFFu
#define OSPI_RFDR_DATA_SHIFT           0u
#define OSPI_RFDR_DATA_WIDTH           32u
#define OSPI_RFDR_DATA(x)              (((uint32_t)(((uint32_t)(x))<<OSPI_RFDR_DATA_SHIFT))&OSPI_RFDR_DATA_MASK)
/* RFDR0 Reg Mask */
#define OSPI_RFDR_MASK                 0xFFFFFFFFu
/* RFD2R Bit Fields */
#define OSPI_RFD2R_DATA_MASK           0xFFFFFFFFu
#define OSPI_RFD2R_DATA_SHIFT          0u
#define OSPI_RFD2R_DATA_WIDTH          32u
#define OSPI_RFD2R_DATA(x)             (((uint32_t)(((uint32_t)(x))<<OSPI_RFD2R_DATA_SHIFT))&OSPI_RFD2R_DATA_MASK)
/* RFD2R Reg Mask */
#define OSPI_RFD2R_MASK                0xFFFFFFFFu
/* LUT_KEY Bit Fields */
#define OSPI_LUT_KEY_LUT_KEY_MASK      0xFFFFFFFFu
#define OSPI_LUT_KEY_LUT_KEY_SHIFT     0u
#define OSPI_LUT_KEY_LUT_KEY_WIDTH     32u
#define OSPI_LUT_KEY_LUT_KEY(x)        (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_KEY_LUT_KEY_SHIFT))&OSPI_LUT_KEY_LUT_KEY_MASK)
/* LUT_KEY Reg Mask */
#define OSPI_LUT_KEY_MASK              0xFFFFFFFFu
/* LUT_CFG Bit Fields */
#define OSPI_LUT_CFG_UNLOCK_MASK       0x2u
#define OSPI_LUT_CFG_UNLOCK_SHIFT      1u
#define OSPI_LUT_CFG_UNLOCK_WIDTH      1u
#define OSPI_LUT_CFG_UNLOCK(x)         (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_CFG_UNLOCK_SHIFT))&OSPI_LUT_CFG_UNLOCK_MASK)
#define OSPI_LUT_CFG_LOCK_MASK         0x1u
#define OSPI_LUT_CFG_LOCK_SHIFT        0u
#define OSPI_LUT_CFG_LOCK_WIDTH        1u
#define OSPI_LUT_CFG_LOCK(x)           (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_CFG_LOCK_SHIFT))&OSPI_LUT_CFG_LOCK_MASK)
/* LUT_CFG Reg Mask */
#define OSPI_LUT_CFG_MASK              0x00000003u
/* LUT Bit Fields */
#define OSPI_LUT_INSTR1_CMD_NAME_MASK  0xFC000000u
#define OSPI_LUT_INSTR1_CMD_NAME_SHIFT 26u
#define OSPI_LUT_INSTR1_CMD_NAME_WIDTH 6u
#define OSPI_LUT_INSTR1_CMD_NAME(x)    (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_INSTR1_CMD_NAME_SHIFT))&OSPI_LUT_INSTR1_CMD_NAME_MASK)
#define OSPI_LUT_INSTR1_PAD_NUM_MASK   0x3000000u
#define OSPI_LUT_INSTR1_PAD_NUM_SHIFT  24u
#define OSPI_LUT_INSTR1_PAD_NUM_WIDTH  2u
#define OSPI_LUT_INSTR1_PAD_NUM(x)     (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_INSTR1_PAD_NUM_SHIFT))&OSPI_LUT_INSTR1_PAD_NUM_MASK)
#define OSPI_LUT_INSTR1_DRV_CMD_MASK   0xFF0000u
#define OSPI_LUT_INSTR1_DRV_CMD_SHIFT  16u
#define OSPI_LUT_INSTR1_DRV_CMD_WIDTH  8u
#define OSPI_LUT_INSTR1_DRV_CMD(x)     (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_INSTR1_DRV_CMD_SHIFT))&OSPI_LUT_INSTR1_DRV_CMD_MASK)
#define OSPI_LUT_INSTR0_CMD_NAME_MASK  0xFC00u
#define OSPI_LUT_INSTR0_CMD_NAME_SHIFT 10u
#define OSPI_LUT_INSTR0_CMD_NAME_WIDTH 6u
#define OSPI_LUT_INSTR0_CMD_NAME(x)    (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_INSTR0_CMD_NAME_SHIFT))&OSPI_LUT_INSTR0_CMD_NAME_MASK)
#define OSPI_LUT_INSTR0_PAD_NUM_MASK   0x300u
#define OSPI_LUT_INSTR0_PAD_NUM_SHIFT  8u
#define OSPI_LUT_INSTR0_PAD_NUM_WIDTH  2u
#define OSPI_LUT_INSTR0_PAD_NUM(x)     (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_INSTR0_PAD_NUM_SHIFT))&OSPI_LUT_INSTR0_PAD_NUM_MASK)
#define OSPI_LUT_INSTR0_DRV_CMD_MASK   0xFFu
#define OSPI_LUT_INSTR0_DRV_CMD_SHIFT  0u
#define OSPI_LUT_INSTR0_DRV_CMD_WIDTH  8u
#define OSPI_LUT_INSTR0_DRV_CMD(x)     (((uint32_t)(((uint32_t)(x))<<OSPI_LUT_INSTR0_DRV_CMD_SHIFT))&OSPI_LUT_INSTR0_DRV_CMD_MASK)
/* LUT0 Reg Mask */
#define OSPI_LUT_MASK                  0xFFFFFFFFu
/**
 * @}
 */ /* end of group OSPI_Register_Masks */
/**
 * @}
 */ /* end of group OSPI_Peripheral_Access_Layer */
#ifdef __cplusplus
}
#endif
#endif
