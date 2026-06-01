#ifndef _MODULE_FCUART_KJO_Ufdi22_REGS_H_
#define _MODULE_FCUART_KJO_Ufdi22_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- FCUART Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCUART_Peripheral_Access_Layer FCUART Peripheral Access Layer
 * @{
 */
/** FCUART - Size of Registers Arrays */
/** FCUART - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[8];
  __IO uint32_t RST                           ; /* Software Reset Register, offset: 0x8 */
  __IO uint32_t PIN_CFG                       ; /* Pin Configuration Register, offset: 0xC */
  __IO uint32_t BAUD                          ; /* Baud Rate Register, offset: 0x10 */
  __IO uint32_t STAT                          ; /* Status Register, offset: 0x14 */
  __IO uint32_t CTRL                          ; /* Control Register, offset: 0x18 */
  __IO uint32_t DATA                          ; /* Data Register, offset: 0x1C */
  __IO uint32_t MATCH                         ; /* Match Address Register, offset: 0x20 */
  __IO uint32_t MODIR                         ; /* Modem IrDA Register, offset: 0x24 */
  __IO uint32_t FIFO                          ; /* FIFO Register, offset: 0x28 */
  __IO uint32_t WATERMARK                     ; /* Watermark Register, offset: 0x2C */
  __IO uint32_t PARITY_CFG                    ; /* Parity Configuration Register, offset: 0x30 */
} FCUART_Type, *FCUART_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FCUART Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCUART_Register_Masks FCUART Register Masks
 * @{
 */
 
/* RST Bit Fields */
#define FCUART_RST_RST_MASK            0x2u
#define FCUART_RST_RST_SHIFT           1u
#define FCUART_RST_RST_WIDTH           1u
#define FCUART_RST_RST(x)              (((uint32_t)(((uint32_t)(x))<<FCUART_RST_RST_SHIFT))&FCUART_RST_RST_MASK)
/* RST Reg Mask */
#define FCUART_RST_MASK                0x00000002u
/* PIN_CFG Bit Fields */
#define FCUART_PIN_CFG_TRGSEL_MASK     0x3u
#define FCUART_PIN_CFG_TRGSEL_SHIFT    0u
#define FCUART_PIN_CFG_TRGSEL_WIDTH    2u
#define FCUART_PIN_CFG_TRGSEL(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_PIN_CFG_TRGSEL_SHIFT))&FCUART_PIN_CFG_TRGSEL_MASK)
/* PIN_CFG Reg Mask */
#define FCUART_PIN_CFG_MASK            0x00000003u
/* BAUD Bit Fields */
#define FCUART_BAUD_MAEN0_MASK         0x80000000u
#define FCUART_BAUD_MAEN0_SHIFT        31u
#define FCUART_BAUD_MAEN0_WIDTH        1u
#define FCUART_BAUD_MAEN0(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_MAEN0_SHIFT))&FCUART_BAUD_MAEN0_MASK)
#define FCUART_BAUD_MAEN1_MASK         0x40000000u
#define FCUART_BAUD_MAEN1_SHIFT        30u
#define FCUART_BAUD_MAEN1_WIDTH        1u
#define FCUART_BAUD_MAEN1(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_MAEN1_SHIFT))&FCUART_BAUD_MAEN1_MASK)
#define FCUART_BAUD_10BIT_MODE_MASK    0x20000000u
#define FCUART_BAUD_10BIT_MODE_SHIFT   29u
#define FCUART_BAUD_10BIT_MODE_WIDTH   1u
#define FCUART_BAUD_10BIT_MODE(x)      (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_10BIT_MODE_SHIFT))&FCUART_BAUD_10BIT_MODE_MASK)
#define FCUART_BAUD_OVR_SAMP_MASK      0x1F000000u
#define FCUART_BAUD_OVR_SAMP_SHIFT     24u
#define FCUART_BAUD_OVR_SAMP_WIDTH     5u
#define FCUART_BAUD_OVR_SAMP(x)        (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_OVR_SAMP_SHIFT))&FCUART_BAUD_OVR_SAMP_MASK)
#define FCUART_BAUD_TDMAEN_MASK        0x800000u
#define FCUART_BAUD_TDMAEN_SHIFT       23u
#define FCUART_BAUD_TDMAEN_WIDTH       1u
#define FCUART_BAUD_TDMAEN(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_TDMAEN_SHIFT))&FCUART_BAUD_TDMAEN_MASK)
#define FCUART_BAUD_RDMAEN_MASK        0x200000u
#define FCUART_BAUD_RDMAEN_SHIFT       21u
#define FCUART_BAUD_RDMAEN_WIDTH       1u
#define FCUART_BAUD_RDMAEN(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_RDMAEN_SHIFT))&FCUART_BAUD_RDMAEN_MASK)
#define FCUART_BAUD_RIDMAEN_MASK       0x100000u
#define FCUART_BAUD_RIDMAEN_SHIFT      20u
#define FCUART_BAUD_RIDMAEN_WIDTH      1u
#define FCUART_BAUD_RIDMAEN(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_RIDMAEN_SHIFT))&FCUART_BAUD_RIDMAEN_MASK)
#define FCUART_BAUD_MATCH_CFG_MASK     0xC0000u
#define FCUART_BAUD_MATCH_CFG_SHIFT    18u
#define FCUART_BAUD_MATCH_CFG_WIDTH    2u
#define FCUART_BAUD_MATCH_CFG(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_MATCH_CFG_SHIFT))&FCUART_BAUD_MATCH_CFG_MASK)
#define FCUART_BAUD_BEDGE_SAMP_MASK    0x20000u
#define FCUART_BAUD_BEDGE_SAMP_SHIFT   17u
#define FCUART_BAUD_BEDGE_SAMP_WIDTH   1u
#define FCUART_BAUD_BEDGE_SAMP(x)      (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_BEDGE_SAMP_SHIFT))&FCUART_BAUD_BEDGE_SAMP_MASK)
#define FCUART_BAUD_RESYNC_DIS_MASK    0x10000u
#define FCUART_BAUD_RESYNC_DIS_SHIFT   16u
#define FCUART_BAUD_RESYNC_DIS_WIDTH   1u
#define FCUART_BAUD_RESYNC_DIS(x)      (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_RESYNC_DIS_SHIFT))&FCUART_BAUD_RESYNC_DIS_MASK)
#define FCUART_BAUD_LBKDIE_MASK        0x8000u
#define FCUART_BAUD_LBKDIE_SHIFT       15u
#define FCUART_BAUD_LBKDIE_WIDTH       1u
#define FCUART_BAUD_LBKDIE(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_LBKDIE_SHIFT))&FCUART_BAUD_LBKDIE_MASK)
#define FCUART_BAUD_RIAEIE_MASK        0x4000u
#define FCUART_BAUD_RIAEIE_SHIFT       14u
#define FCUART_BAUD_RIAEIE_WIDTH       1u
#define FCUART_BAUD_RIAEIE(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_RIAEIE_SHIFT))&FCUART_BAUD_RIAEIE_MASK)
#define FCUART_BAUD_SBNS_MASK          0x2000u
#define FCUART_BAUD_SBNS_SHIFT         13u
#define FCUART_BAUD_SBNS_WIDTH         1u
#define FCUART_BAUD_SBNS(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_SBNS_SHIFT))&FCUART_BAUD_SBNS_MASK)
#define FCUART_BAUD_SBR_MASK           0x1FFFu
#define FCUART_BAUD_SBR_SHIFT          0u
#define FCUART_BAUD_SBR_WIDTH          13u
#define FCUART_BAUD_SBR(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_BAUD_SBR_SHIFT))&FCUART_BAUD_SBR_MASK)
/* BAUD Reg Mask */
#define FCUART_BAUD_MASK               0xFFBFFFFFu
/* STAT Bit Fields */
#define FCUART_STAT_LBKDIF_MASK        0x80000000u
#define FCUART_STAT_LBKDIF_SHIFT       31u
#define FCUART_STAT_LBKDIF_WIDTH       1u
#define FCUART_STAT_LBKDIF(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_LBKDIF_SHIFT))&FCUART_STAT_LBKDIF_MASK)
#define FCUART_STAT_RPAEIF_MASK        0x40000000u
#define FCUART_STAT_RPAEIF_SHIFT       30u
#define FCUART_STAT_RPAEIF_WIDTH       1u
#define FCUART_STAT_RPAEIF(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_RPAEIF_SHIFT))&FCUART_STAT_RPAEIF_MASK)
#define FCUART_STAT_MSBF_MASK          0x20000000u
#define FCUART_STAT_MSBF_SHIFT         29u
#define FCUART_STAT_MSBF_WIDTH         1u
#define FCUART_STAT_MSBF(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_MSBF_SHIFT))&FCUART_STAT_MSBF_MASK)
#define FCUART_STAT_RXINV_MASK         0x10000000u
#define FCUART_STAT_RXINV_SHIFT        28u
#define FCUART_STAT_RXINV_WIDTH        1u
#define FCUART_STAT_RXINV(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_RXINV_SHIFT))&FCUART_STAT_RXINV_MASK)
#define FCUART_STAT_RWUID_MASK         0x8000000u
#define FCUART_STAT_RWUID_SHIFT        27u
#define FCUART_STAT_RWUID_WIDTH        1u
#define FCUART_STAT_RWUID(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_RWUID_SHIFT))&FCUART_STAT_RWUID_MASK)
#define FCUART_STAT_BCGL_MASK          0x4000000u
#define FCUART_STAT_BCGL_SHIFT         26u
#define FCUART_STAT_BCGL_WIDTH         1u
#define FCUART_STAT_BCGL(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_BCGL_SHIFT))&FCUART_STAT_BCGL_MASK)
#define FCUART_STAT_LBKDE_MASK         0x2000000u
#define FCUART_STAT_LBKDE_SHIFT        25u
#define FCUART_STAT_LBKDE_WIDTH        1u
#define FCUART_STAT_LBKDE(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_LBKDE_SHIFT))&FCUART_STAT_LBKDE_MASK)
#define FCUART_STAT_RAF_MASK           0x1000000u
#define FCUART_STAT_RAF_SHIFT          24u
#define FCUART_STAT_RAF_WIDTH          1u
#define FCUART_STAT_RAF(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_RAF_SHIFT))&FCUART_STAT_RAF_MASK)
#define FCUART_STAT_TDREF_MASK         0x800000u
#define FCUART_STAT_TDREF_SHIFT        23u
#define FCUART_STAT_TDREF_WIDTH        1u
#define FCUART_STAT_TDREF(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_TDREF_SHIFT))&FCUART_STAT_TDREF_MASK)
#define FCUART_STAT_TCF_MASK           0x400000u
#define FCUART_STAT_TCF_SHIFT          22u
#define FCUART_STAT_TCF_WIDTH          1u
#define FCUART_STAT_TCF(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_TCF_SHIFT))&FCUART_STAT_TCF_MASK)
#define FCUART_STAT_RDRFF_MASK         0x200000u
#define FCUART_STAT_RDRFF_SHIFT        21u
#define FCUART_STAT_RDRFF_WIDTH        1u
#define FCUART_STAT_RDRFF(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_RDRFF_SHIFT))&FCUART_STAT_RDRFF_MASK)
#define FCUART_STAT_IDLEF_MASK         0x100000u
#define FCUART_STAT_IDLEF_SHIFT        20u
#define FCUART_STAT_IDLEF_WIDTH        1u
#define FCUART_STAT_IDLEF(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_IDLEF_SHIFT))&FCUART_STAT_IDLEF_MASK)
#define FCUART_STAT_RORF_MASK          0x80000u
#define FCUART_STAT_RORF_SHIFT         19u
#define FCUART_STAT_RORF_WIDTH         1u
#define FCUART_STAT_RORF(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_RORF_SHIFT))&FCUART_STAT_RORF_MASK)
#define FCUART_STAT_NF_MASK            0x40000u
#define FCUART_STAT_NF_SHIFT           18u
#define FCUART_STAT_NF_WIDTH           1u
#define FCUART_STAT_NF(x)              (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_NF_SHIFT))&FCUART_STAT_NF_MASK)
#define FCUART_STAT_FEF_MASK           0x20000u
#define FCUART_STAT_FEF_SHIFT          17u
#define FCUART_STAT_FEF_WIDTH          1u
#define FCUART_STAT_FEF(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_FEF_SHIFT))&FCUART_STAT_FEF_MASK)
#define FCUART_STAT_PEF_MASK           0x10000u
#define FCUART_STAT_PEF_SHIFT          16u
#define FCUART_STAT_PEF_WIDTH          1u
#define FCUART_STAT_PEF(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_PEF_SHIFT))&FCUART_STAT_PEF_MASK)
#define FCUART_STAT_M0F_MASK           0x8000u
#define FCUART_STAT_M0F_SHIFT          15u
#define FCUART_STAT_M0F_WIDTH          1u
#define FCUART_STAT_M0F(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_M0F_SHIFT))&FCUART_STAT_M0F_MASK)
#define FCUART_STAT_M1F_MASK           0x4000u
#define FCUART_STAT_M1F_SHIFT          14u
#define FCUART_STAT_M1F_WIDTH          1u
#define FCUART_STAT_M1F(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_M1F_SHIFT))&FCUART_STAT_M1F_MASK)
#define FCUART_STAT_RPEF_MASK          0x8u
#define FCUART_STAT_RPEF_SHIFT         3u
#define FCUART_STAT_RPEF_WIDTH         1u
#define FCUART_STAT_RPEF(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_RPEF_SHIFT))&FCUART_STAT_RPEF_MASK)
#define FCUART_STAT_TPEF_MASK          0x4u
#define FCUART_STAT_TPEF_SHIFT         2u
#define FCUART_STAT_TPEF_WIDTH         1u
#define FCUART_STAT_TPEF(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_STAT_TPEF_SHIFT))&FCUART_STAT_TPEF_MASK)
/* STAT Reg Mask */
#define FCUART_STAT_MASK               0xFFFFC00Cu
/* CTRL Bit Fields */
#define FCUART_CTRL_R8T9_MASK          0x80000000u
#define FCUART_CTRL_R8T9_SHIFT         31u
#define FCUART_CTRL_R8T9_WIDTH         1u
#define FCUART_CTRL_R8T9(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_R8T9_SHIFT))&FCUART_CTRL_R8T9_MASK)
#define FCUART_CTRL_R9T8_MASK          0x40000000u
#define FCUART_CTRL_R9T8_SHIFT         30u
#define FCUART_CTRL_R9T8_WIDTH         1u
#define FCUART_CTRL_R9T8(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_R9T8_SHIFT))&FCUART_CTRL_R9T8_MASK)
#define FCUART_CTRL_TXDIR_MASK         0x20000000u
#define FCUART_CTRL_TXDIR_SHIFT        29u
#define FCUART_CTRL_TXDIR_WIDTH        1u
#define FCUART_CTRL_TXDIR(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_TXDIR_SHIFT))&FCUART_CTRL_TXDIR_MASK)
#define FCUART_CTRL_TXINV_MASK         0x10000000u
#define FCUART_CTRL_TXINV_SHIFT        28u
#define FCUART_CTRL_TXINV_WIDTH        1u
#define FCUART_CTRL_TXINV(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_TXINV_SHIFT))&FCUART_CTRL_TXINV_MASK)
#define FCUART_CTRL_ORIE_MASK          0x8000000u
#define FCUART_CTRL_ORIE_SHIFT         27u
#define FCUART_CTRL_ORIE_WIDTH         1u
#define FCUART_CTRL_ORIE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_ORIE_SHIFT))&FCUART_CTRL_ORIE_MASK)
#define FCUART_CTRL_NEIE_MASK          0x4000000u
#define FCUART_CTRL_NEIE_SHIFT         26u
#define FCUART_CTRL_NEIE_WIDTH         1u
#define FCUART_CTRL_NEIE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_NEIE_SHIFT))&FCUART_CTRL_NEIE_MASK)
#define FCUART_CTRL_FEIE_MASK          0x2000000u
#define FCUART_CTRL_FEIE_SHIFT         25u
#define FCUART_CTRL_FEIE_WIDTH         1u
#define FCUART_CTRL_FEIE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_FEIE_SHIFT))&FCUART_CTRL_FEIE_MASK)
#define FCUART_CTRL_PEIE_MASK          0x1000000u
#define FCUART_CTRL_PEIE_SHIFT         24u
#define FCUART_CTRL_PEIE_WIDTH         1u
#define FCUART_CTRL_PEIE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_PEIE_SHIFT))&FCUART_CTRL_PEIE_MASK)
#define FCUART_CTRL_TIE_MASK           0x800000u
#define FCUART_CTRL_TIE_SHIFT          23u
#define FCUART_CTRL_TIE_WIDTH          1u
#define FCUART_CTRL_TIE(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_TIE_SHIFT))&FCUART_CTRL_TIE_MASK)
#define FCUART_CTRL_TCIE_MASK          0x400000u
#define FCUART_CTRL_TCIE_SHIFT         22u
#define FCUART_CTRL_TCIE_WIDTH         1u
#define FCUART_CTRL_TCIE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_TCIE_SHIFT))&FCUART_CTRL_TCIE_MASK)
#define FCUART_CTRL_RIE_MASK           0x200000u
#define FCUART_CTRL_RIE_SHIFT          21u
#define FCUART_CTRL_RIE_WIDTH          1u
#define FCUART_CTRL_RIE(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_RIE_SHIFT))&FCUART_CTRL_RIE_MASK)
#define FCUART_CTRL_IIE_MASK           0x100000u
#define FCUART_CTRL_IIE_SHIFT          20u
#define FCUART_CTRL_IIE_WIDTH          1u
#define FCUART_CTRL_IIE(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_IIE_SHIFT))&FCUART_CTRL_IIE_MASK)
#define FCUART_CTRL_TE_MASK            0x80000u
#define FCUART_CTRL_TE_SHIFT           19u
#define FCUART_CTRL_TE_WIDTH           1u
#define FCUART_CTRL_TE(x)              (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_TE_SHIFT))&FCUART_CTRL_TE_MASK)
#define FCUART_CTRL_RE_MASK            0x40000u
#define FCUART_CTRL_RE_SHIFT           18u
#define FCUART_CTRL_RE_WIDTH           1u
#define FCUART_CTRL_RE(x)              (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_RE_SHIFT))&FCUART_CTRL_RE_MASK)
#define FCUART_CTRL_RWC_MASK           0x20000u
#define FCUART_CTRL_RWC_SHIFT          17u
#define FCUART_CTRL_RWC_WIDTH          1u
#define FCUART_CTRL_RWC(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_RWC_SHIFT))&FCUART_CTRL_RWC_MASK)
#define FCUART_CTRL_SBK_MASK           0x10000u
#define FCUART_CTRL_SBK_SHIFT          16u
#define FCUART_CTRL_SBK_WIDTH          1u
#define FCUART_CTRL_SBK(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_SBK_SHIFT))&FCUART_CTRL_SBK_MASK)
#define FCUART_CTRL_M0IE_MASK          0x8000u
#define FCUART_CTRL_M0IE_SHIFT         15u
#define FCUART_CTRL_M0IE_WIDTH         1u
#define FCUART_CTRL_M0IE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_M0IE_SHIFT))&FCUART_CTRL_M0IE_MASK)
#define FCUART_CTRL_M1IE_MASK          0x4000u
#define FCUART_CTRL_M1IE_SHIFT         14u
#define FCUART_CTRL_M1IE_WIDTH         1u
#define FCUART_CTRL_M1IE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_M1IE_SHIFT))&FCUART_CTRL_M1IE_MASK)
#define FCUART_CTRL_7BMS_MASK          0x800u
#define FCUART_CTRL_7BMS_SHIFT         11u
#define FCUART_CTRL_7BMS_WIDTH         1u
#define FCUART_CTRL_7BMS(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_7BMS_SHIFT))&FCUART_CTRL_7BMS_MASK)
#define FCUART_CTRL_IDLECFG_MASK       0x700u
#define FCUART_CTRL_IDLECFG_SHIFT      8u
#define FCUART_CTRL_IDLECFG_WIDTH      3u
#define FCUART_CTRL_IDLECFG(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_IDLECFG_SHIFT))&FCUART_CTRL_IDLECFG_MASK)
#define FCUART_CTRL_LOOPMS_MASK        0x80u
#define FCUART_CTRL_LOOPMS_SHIFT       7u
#define FCUART_CTRL_LOOPMS_WIDTH       1u
#define FCUART_CTRL_LOOPMS(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_LOOPMS_SHIFT))&FCUART_CTRL_LOOPMS_MASK)
#define FCUART_CTRL_WAITEN_MASK        0x40u
#define FCUART_CTRL_WAITEN_SHIFT       6u
#define FCUART_CTRL_WAITEN_WIDTH       1u
#define FCUART_CTRL_WAITEN(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_WAITEN_SHIFT))&FCUART_CTRL_WAITEN_MASK)
#define FCUART_CTRL_RXSRC_MASK         0x20u
#define FCUART_CTRL_RXSRC_SHIFT        5u
#define FCUART_CTRL_RXSRC_WIDTH        1u
#define FCUART_CTRL_RXSRC(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_RXSRC_SHIFT))&FCUART_CTRL_RXSRC_MASK)
#define FCUART_CTRL_BMSEL_MASK         0x10u
#define FCUART_CTRL_BMSEL_SHIFT        4u
#define FCUART_CTRL_BMSEL_WIDTH        1u
#define FCUART_CTRL_BMSEL(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_BMSEL_SHIFT))&FCUART_CTRL_BMSEL_MASK)
#define FCUART_CTRL_RSWMS_MASK         0x8u
#define FCUART_CTRL_RSWMS_SHIFT        3u
#define FCUART_CTRL_RSWMS_WIDTH        1u
#define FCUART_CTRL_RSWMS(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_RSWMS_SHIFT))&FCUART_CTRL_RSWMS_MASK)
#define FCUART_CTRL_ITS_MASK           0x4u
#define FCUART_CTRL_ITS_SHIFT          2u
#define FCUART_CTRL_ITS_WIDTH          1u
#define FCUART_CTRL_ITS(x)             (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_ITS_SHIFT))&FCUART_CTRL_ITS_MASK)
#define FCUART_CTRL_PE_MASK            0x2u
#define FCUART_CTRL_PE_SHIFT           1u
#define FCUART_CTRL_PE_WIDTH           1u
#define FCUART_CTRL_PE(x)              (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_PE_SHIFT))&FCUART_CTRL_PE_MASK)
#define FCUART_CTRL_PT_MASK            0x1u
#define FCUART_CTRL_PT_SHIFT           0u
#define FCUART_CTRL_PT_WIDTH           1u
#define FCUART_CTRL_PT(x)              (((uint32_t)(((uint32_t)(x))<<FCUART_CTRL_PT_SHIFT))&FCUART_CTRL_PT_MASK)
/* CTRL Reg Mask */
#define FCUART_CTRL_MASK               0xFFFFCFFFu
/* DATA Bit Fields */
#define FCUART_DATA_NOISY_MASK         0x8000u
#define FCUART_DATA_NOISY_SHIFT        15u
#define FCUART_DATA_NOISY_WIDTH        1u
#define FCUART_DATA_NOISY(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_DATA_NOISY_SHIFT))&FCUART_DATA_NOISY_MASK)
#define FCUART_DATA_PARITYE_MASK       0x4000u
#define FCUART_DATA_PARITYE_SHIFT      14u
#define FCUART_DATA_PARITYE_WIDTH      1u
#define FCUART_DATA_PARITYE(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_DATA_PARITYE_SHIFT))&FCUART_DATA_PARITYE_MASK)
#define FCUART_DATA_FETSC_MASK         0x2000u
#define FCUART_DATA_FETSC_SHIFT        13u
#define FCUART_DATA_FETSC_WIDTH        1u
#define FCUART_DATA_FETSC(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_DATA_FETSC_SHIFT))&FCUART_DATA_FETSC_MASK)
#define FCUART_DATA_RXEMPT_MASK        0x1000u
#define FCUART_DATA_RXEMPT_SHIFT       12u
#define FCUART_DATA_RXEMPT_WIDTH       1u
#define FCUART_DATA_RXEMPT(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_DATA_RXEMPT_SHIFT))&FCUART_DATA_RXEMPT_MASK)
#define FCUART_DATA_IDLE_MASK          0x800u
#define FCUART_DATA_IDLE_SHIFT         11u
#define FCUART_DATA_IDLE_WIDTH         1u
#define FCUART_DATA_IDLE(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_DATA_IDLE_SHIFT))&FCUART_DATA_IDLE_MASK)
#define FCUART_DATA_RXTXDATA_MASK      0x3FFu
#define FCUART_DATA_RXTXDATA_SHIFT     0u
#define FCUART_DATA_RXTXDATA_WIDTH     10u
#define FCUART_DATA_RXTXDATA(x)        (((uint32_t)(((uint32_t)(x))<<FCUART_DATA_RXTXDATA_SHIFT))&FCUART_DATA_RXTXDATA_MASK)
/* DATA Reg Mask */
#define FCUART_DATA_MASK               0x0000FBFFu
/* MATCH Bit Fields */
#define FCUART_MATCH_MATCH1_MASK       0x3FF0000u
#define FCUART_MATCH_MATCH1_SHIFT      16u
#define FCUART_MATCH_MATCH1_WIDTH      10u
#define FCUART_MATCH_MATCH1(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_MATCH_MATCH1_SHIFT))&FCUART_MATCH_MATCH1_MASK)
#define FCUART_MATCH_MATCH0_MASK       0x3FFu
#define FCUART_MATCH_MATCH0_SHIFT      0u
#define FCUART_MATCH_MATCH0_WIDTH      10u
#define FCUART_MATCH_MATCH0(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_MATCH_MATCH0_SHIFT))&FCUART_MATCH_MATCH0_MASK)
/* MATCH Reg Mask */
#define FCUART_MATCH_MASK              0x03FF03FFu
/* MODIR Bit Fields */
#define FCUART_MODIR_RXRTSCFG_MASK     0x300u
#define FCUART_MODIR_RXRTSCFG_SHIFT    8u
#define FCUART_MODIR_RXRTSCFG_WIDTH    2u
#define FCUART_MODIR_RXRTSCFG(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_MODIR_RXRTSCFG_SHIFT))&FCUART_MODIR_RXRTSCFG_MASK)
#define FCUART_MODIR_TXCTSSRC_MASK     0x20u
#define FCUART_MODIR_TXCTSSRC_SHIFT    5u
#define FCUART_MODIR_TXCTSSRC_WIDTH    1u
#define FCUART_MODIR_TXCTSSRC(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_MODIR_TXCTSSRC_SHIFT))&FCUART_MODIR_TXCTSSRC_MASK)
#define FCUART_MODIR_TXCTSCFG_MASK     0x10u
#define FCUART_MODIR_TXCTSCFG_SHIFT    4u
#define FCUART_MODIR_TXCTSCFG_WIDTH    1u
#define FCUART_MODIR_TXCTSCFG(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_MODIR_TXCTSCFG_SHIFT))&FCUART_MODIR_TXCTSCFG_MASK)
#define FCUART_MODIR_RXRTSEN_MASK      0x8u
#define FCUART_MODIR_RXRTSEN_SHIFT     3u
#define FCUART_MODIR_RXRTSEN_WIDTH     1u
#define FCUART_MODIR_RXRTSEN(x)        (((uint32_t)(((uint32_t)(x))<<FCUART_MODIR_RXRTSEN_SHIFT))&FCUART_MODIR_RXRTSEN_MASK)
#define FCUART_MODIR_TXRTSPOL_MASK     0x4u
#define FCUART_MODIR_TXRTSPOL_SHIFT    2u
#define FCUART_MODIR_TXRTSPOL_WIDTH    1u
#define FCUART_MODIR_TXRTSPOL(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_MODIR_TXRTSPOL_SHIFT))&FCUART_MODIR_TXRTSPOL_MASK)
#define FCUART_MODIR_TXRTSEN_MASK      0x2u
#define FCUART_MODIR_TXRTSEN_SHIFT     1u
#define FCUART_MODIR_TXRTSEN_WIDTH     1u
#define FCUART_MODIR_TXRTSEN(x)        (((uint32_t)(((uint32_t)(x))<<FCUART_MODIR_TXRTSEN_SHIFT))&FCUART_MODIR_TXRTSEN_MASK)
#define FCUART_MODIR_TXCTSEN_MASK      0x1u
#define FCUART_MODIR_TXCTSEN_SHIFT     0u
#define FCUART_MODIR_TXCTSEN_WIDTH     1u
#define FCUART_MODIR_TXCTSEN(x)        (((uint32_t)(((uint32_t)(x))<<FCUART_MODIR_TXCTSEN_SHIFT))&FCUART_MODIR_TXCTSEN_MASK)
/* MODIR Reg Mask */
#define FCUART_MODIR_MASK              0x0000033Fu
/* FIFO Bit Fields */
#define FCUART_FIFO_TXEMPTY_MASK       0x800000u
#define FCUART_FIFO_TXEMPTY_SHIFT      23u
#define FCUART_FIFO_TXEMPTY_WIDTH      1u
#define FCUART_FIFO_TXEMPTY(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_TXEMPTY_SHIFT))&FCUART_FIFO_TXEMPTY_MASK)
#define FCUART_FIFO_RXEMPTY_MASK       0x400000u
#define FCUART_FIFO_RXEMPTY_SHIFT      22u
#define FCUART_FIFO_RXEMPTY_WIDTH      1u
#define FCUART_FIFO_RXEMPTY(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_RXEMPTY_SHIFT))&FCUART_FIFO_RXEMPTY_MASK)
#define FCUART_FIFO_TXOF_MASK          0x20000u
#define FCUART_FIFO_TXOF_SHIFT         17u
#define FCUART_FIFO_TXOF_WIDTH         1u
#define FCUART_FIFO_TXOF(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_TXOF_SHIFT))&FCUART_FIFO_TXOF_MASK)
#define FCUART_FIFO_RXUF_MASK          0x10000u
#define FCUART_FIFO_RXUF_SHIFT         16u
#define FCUART_FIFO_RXUF_WIDTH         1u
#define FCUART_FIFO_RXUF(x)            (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_RXUF_SHIFT))&FCUART_FIFO_RXUF_MASK)
#define FCUART_FIFO_TXFLUSH_MASK       0x8000u
#define FCUART_FIFO_TXFLUSH_SHIFT      15u
#define FCUART_FIFO_TXFLUSH_WIDTH      1u
#define FCUART_FIFO_TXFLUSH(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_TXFLUSH_SHIFT))&FCUART_FIFO_TXFLUSH_MASK)
#define FCUART_FIFO_RXFLUSH_MASK       0x4000u
#define FCUART_FIFO_RXFLUSH_SHIFT      14u
#define FCUART_FIFO_RXFLUSH_WIDTH      1u
#define FCUART_FIFO_RXFLUSH(x)         (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_RXFLUSH_SHIFT))&FCUART_FIFO_RXFLUSH_MASK)
#define FCUART_FIFO_RXIDEN_MASK        0x1C00u
#define FCUART_FIFO_RXIDEN_SHIFT       10u
#define FCUART_FIFO_RXIDEN_WIDTH       3u
#define FCUART_FIFO_RXIDEN(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_RXIDEN_SHIFT))&FCUART_FIFO_RXIDEN_MASK)
#define FCUART_FIFO_TXOFIE_MASK        0x200u
#define FCUART_FIFO_TXOFIE_SHIFT       9u
#define FCUART_FIFO_TXOFIE_WIDTH       1u
#define FCUART_FIFO_TXOFIE(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_TXOFIE_SHIFT))&FCUART_FIFO_TXOFIE_MASK)
#define FCUART_FIFO_RXUFIE_MASK        0x100u
#define FCUART_FIFO_RXUFIE_SHIFT       8u
#define FCUART_FIFO_RXUFIE_WIDTH       1u
#define FCUART_FIFO_RXUFIE(x)          (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_RXUFIE_SHIFT))&FCUART_FIFO_RXUFIE_MASK)
#define FCUART_FIFO_TXFEN_MASK         0x80u
#define FCUART_FIFO_TXFEN_SHIFT        7u
#define FCUART_FIFO_TXFEN_WIDTH        1u
#define FCUART_FIFO_TXFEN(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_TXFEN_SHIFT))&FCUART_FIFO_TXFEN_MASK)
#define FCUART_FIFO_TXFIFODEP_MASK     0x70u
#define FCUART_FIFO_TXFIFODEP_SHIFT    4u
#define FCUART_FIFO_TXFIFODEP_WIDTH    3u
#define FCUART_FIFO_TXFIFODEP(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_TXFIFODEP_SHIFT))&FCUART_FIFO_TXFIFODEP_MASK)
#define FCUART_FIFO_RXFEN_MASK         0x8u
#define FCUART_FIFO_RXFEN_SHIFT        3u
#define FCUART_FIFO_RXFEN_WIDTH        1u
#define FCUART_FIFO_RXFEN(x)           (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_RXFEN_SHIFT))&FCUART_FIFO_RXFEN_MASK)
#define FCUART_FIFO_RXFIFODEP_MASK     0x7u
#define FCUART_FIFO_RXFIFODEP_SHIFT    0u
#define FCUART_FIFO_RXFIFODEP_WIDTH    3u
#define FCUART_FIFO_RXFIFODEP(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_FIFO_RXFIFODEP_SHIFT))&FCUART_FIFO_RXFIFODEP_MASK)
/* FIFO Reg Mask */
#define FCUART_FIFO_MASK               0x00C3DFFFu
/* WATERMARK Bit Fields */
#define FCUART_WATERMARK_RXCOUNT_MASK  0x7000000u
#define FCUART_WATERMARK_RXCOUNT_SHIFT 24u
#define FCUART_WATERMARK_RXCOUNT_WIDTH 3u
#define FCUART_WATERMARK_RXCOUNT(x)    (((uint32_t)(((uint32_t)(x))<<FCUART_WATERMARK_RXCOUNT_SHIFT))&FCUART_WATERMARK_RXCOUNT_MASK)
#define FCUART_WATERMARK_RXWATER_MASK  0x30000u
#define FCUART_WATERMARK_RXWATER_SHIFT 16u
#define FCUART_WATERMARK_RXWATER_WIDTH 2u
#define FCUART_WATERMARK_RXWATER(x)    (((uint32_t)(((uint32_t)(x))<<FCUART_WATERMARK_RXWATER_SHIFT))&FCUART_WATERMARK_RXWATER_MASK)
#define FCUART_WATERMARK_TXCOUNT_MASK  0x700u
#define FCUART_WATERMARK_TXCOUNT_SHIFT 8u
#define FCUART_WATERMARK_TXCOUNT_WIDTH 3u
#define FCUART_WATERMARK_TXCOUNT(x)    (((uint32_t)(((uint32_t)(x))<<FCUART_WATERMARK_TXCOUNT_SHIFT))&FCUART_WATERMARK_TXCOUNT_MASK)
#define FCUART_WATERMARK_TXWATER_MASK  0x3u
#define FCUART_WATERMARK_TXWATER_SHIFT 0u
#define FCUART_WATERMARK_TXWATER_WIDTH 2u
#define FCUART_WATERMARK_TXWATER(x)    (((uint32_t)(((uint32_t)(x))<<FCUART_WATERMARK_TXWATER_SHIFT))&FCUART_WATERMARK_TXWATER_MASK)
/* WATERMARK Reg Mask */
#define FCUART_WATERMARK_MASK          0x07030703u
/* PARITY_CFG Bit Fields */
#define FCUART_PARITY_CFG_REIB_MASK    0xF000u
#define FCUART_PARITY_CFG_REIB_SHIFT   12u
#define FCUART_PARITY_CFG_REIB_WIDTH   4u
#define FCUART_PARITY_CFG_REIB(x)      (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_REIB_SHIFT))&FCUART_PARITY_CFG_REIB_MASK)
#define FCUART_PARITY_CFG_RPEIE_MASK   0x400u
#define FCUART_PARITY_CFG_RPEIE_SHIFT  10u
#define FCUART_PARITY_CFG_RPEIE_WIDTH  1u
#define FCUART_PARITY_CFG_RPEIE(x)     (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_RPEIE_SHIFT))&FCUART_PARITY_CFG_RPEIE_MASK)
#define FCUART_PARITY_CFG_REIE_MASK    0x200u
#define FCUART_PARITY_CFG_REIE_SHIFT   9u
#define FCUART_PARITY_CFG_REIE_WIDTH   1u
#define FCUART_PARITY_CFG_REIE(x)      (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_REIE_SHIFT))&FCUART_PARITY_CFG_REIE_MASK)
#define FCUART_PARITY_CFG_RPE_MASK     0x100u
#define FCUART_PARITY_CFG_RPE_SHIFT    8u
#define FCUART_PARITY_CFG_RPE_WIDTH    1u
#define FCUART_PARITY_CFG_RPE(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_RPE_SHIFT))&FCUART_PARITY_CFG_RPE_MASK)
#define FCUART_PARITY_CFG_TEIB_MASK    0xF0u
#define FCUART_PARITY_CFG_TEIB_SHIFT   4u
#define FCUART_PARITY_CFG_TEIB_WIDTH   4u
#define FCUART_PARITY_CFG_TEIB(x)      (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_TEIB_SHIFT))&FCUART_PARITY_CFG_TEIB_MASK)
#define FCUART_PARITY_CFG_TPEIE_MASK   0x4u
#define FCUART_PARITY_CFG_TPEIE_SHIFT  2u
#define FCUART_PARITY_CFG_TPEIE_WIDTH  1u
#define FCUART_PARITY_CFG_TPEIE(x)     (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_TPEIE_SHIFT))&FCUART_PARITY_CFG_TPEIE_MASK)
#define FCUART_PARITY_CFG_TEIE_MASK    0x2u
#define FCUART_PARITY_CFG_TEIE_SHIFT   1u
#define FCUART_PARITY_CFG_TEIE_WIDTH   1u
#define FCUART_PARITY_CFG_TEIE(x)      (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_TEIE_SHIFT))&FCUART_PARITY_CFG_TEIE_MASK)
#define FCUART_PARITY_CFG_TPE_MASK     0x1u
#define FCUART_PARITY_CFG_TPE_SHIFT    0u
#define FCUART_PARITY_CFG_TPE_WIDTH    1u
#define FCUART_PARITY_CFG_TPE(x)       (((uint32_t)(((uint32_t)(x))<<FCUART_PARITY_CFG_TPE_SHIFT))&FCUART_PARITY_CFG_TPE_MASK)
/* PARITY_CFG Reg Mask */
#define FCUART_PARITY_CFG_MASK         0x0000F7F7u
/**
 * @}
 */ /* end of group FCUART_Register_Masks */
/**
 * @}
 */ /* end of group FCUART_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
