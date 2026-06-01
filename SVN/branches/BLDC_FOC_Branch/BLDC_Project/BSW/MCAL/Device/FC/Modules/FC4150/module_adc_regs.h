#ifndef _MODULE_ADC_KJO_Ufdi14_REGS_H_
#define _MODULE_ADC_KJO_Ufdi14_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* ----------------------------------------------------------------------------
   -- ADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */
/** ADC - Size of Registers Arrays */
/** ADC - Register Layout Typedef */

typedef struct {
  __IO uint32_t INT_STATUS                    ; /* Interrupt Status Register, offset: 0x0 */
  __IO uint32_t INT_ENABLE                    ; /* Interrupt Enable Register, offset: 0x4 */
  __IO uint32_t CONTROL                       ; /* Control Register, offset: 0x8 */
  __IO uint32_t CFG1                          ; /* Configuration1 Register, offset: 0xC */
  __IO uint32_t CFG2                          ; /* Configuration2 Register, offset: 0x10 */
  __IO uint32_t SMPR                          ; /* Sampling Rate Register, offset: 0x14 */
  __IO uint32_t CMP_CTRL                      ; /* Compare Control Register, offset: 0x18 */
  __IO uint32_t CMP_TR                        ; /* Compare Threshold Register, offset: 0x1C */
       uint8_t  RESERVED_0[44];
  __IO uint32_t FIFO_DATA                     ; /* FIFO Data Register, offset: 0x4C */
  __IO uint32_t SC[ADC_SC_COUNT]              ; /* Sequence Configuration Register, offset: 0x50 */
  __IO uint32_t RESULT[ADC_RESULT_COUNT]      ; /* Result Register, offset: 0xd0 */
} ADC_Type, *ADC_MemMapPtr;


/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */
 
/* INT_STATUS Bit Fields */
#define ADC_INT_STATUS_TRGERR_MASK     0xF000000u
#define ADC_INT_STATUS_TRGERR_SHIFT    24u
#define ADC_INT_STATUS_TRGERR_WIDTH    4u
#define ADC_INT_STATUS_TRGERR(x)       (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_TRGERR_SHIFT))&ADC_INT_STATUS_TRGERR_MASK)
#define ADC_INT_STATUS_TRG_STATUS_MASK 0xF0000u
#define ADC_INT_STATUS_TRG_STATUS_SHIFT 16u
#define ADC_INT_STATUS_TRG_STATUS_WIDTH 4u
#define ADC_INT_STATUS_TRG_STATUS(x)   (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_TRG_STATUS_SHIFT))&ADC_INT_STATUS_TRG_STATUS_MASK)
#define ADC_INT_STATUS_TRG_PRO_NUM_MASK 0x6000u
#define ADC_INT_STATUS_TRG_PRO_NUM_SHIFT 13u
#define ADC_INT_STATUS_TRG_PRO_NUM_WIDTH 2u
#define ADC_INT_STATUS_TRG_PRO_NUM(x)  (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_TRG_PRO_NUM_SHIFT))&ADC_INT_STATUS_TRG_PRO_NUM_MASK)
#define ADC_INT_STATUS_FIFO_RDY_MASK   0x100u
#define ADC_INT_STATUS_FIFO_RDY_SHIFT  8u
#define ADC_INT_STATUS_FIFO_RDY_WIDTH  1u
#define ADC_INT_STATUS_FIFO_RDY(x)     (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_FIFO_RDY_SHIFT))&ADC_INT_STATUS_FIFO_RDY_MASK)
#define ADC_INT_STATUS_ACMP_MASK       0x80u
#define ADC_INT_STATUS_ACMP_SHIFT      7u
#define ADC_INT_STATUS_ACMP_WIDTH      1u
#define ADC_INT_STATUS_ACMP(x)         (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_ACMP_SHIFT))&ADC_INT_STATUS_ACMP_MASK)
#define ADC_INT_STATUS_EMPTY_MASK      0x40u
#define ADC_INT_STATUS_EMPTY_SHIFT     6u
#define ADC_INT_STATUS_EMPTY_WIDTH     1u
#define ADC_INT_STATUS_EMPTY(x)        (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_EMPTY_SHIFT))&ADC_INT_STATUS_EMPTY_MASK)
#define ADC_INT_STATUS_FULL_MASK       0x20u
#define ADC_INT_STATUS_FULL_SHIFT      5u
#define ADC_INT_STATUS_FULL_WIDTH      1u
#define ADC_INT_STATUS_FULL(x)         (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_FULL_SHIFT))&ADC_INT_STATUS_FULL_MASK)
#define ADC_INT_STATUS_OVR_MASK        0x10u
#define ADC_INT_STATUS_OVR_SHIFT       4u
#define ADC_INT_STATUS_OVR_WIDTH       1u
#define ADC_INT_STATUS_OVR(x)          (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_OVR_SHIFT))&ADC_INT_STATUS_OVR_MASK)
#define ADC_INT_STATUS_EOSEQ_MASK      0x8u
#define ADC_INT_STATUS_EOSEQ_SHIFT     3u
#define ADC_INT_STATUS_EOSEQ_WIDTH     1u
#define ADC_INT_STATUS_EOSEQ(x)        (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_EOSEQ_SHIFT))&ADC_INT_STATUS_EOSEQ_MASK)
#define ADC_INT_STATUS_EOC_MASK        0x4u
#define ADC_INT_STATUS_EOC_SHIFT       2u
#define ADC_INT_STATUS_EOC_WIDTH       1u
#define ADC_INT_STATUS_EOC(x)          (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_EOC_SHIFT))&ADC_INT_STATUS_EOC_MASK)
#define ADC_INT_STATUS_EOSMP_MASK      0x2u
#define ADC_INT_STATUS_EOSMP_SHIFT     1u
#define ADC_INT_STATUS_EOSMP_WIDTH     1u
#define ADC_INT_STATUS_EOSMP(x)        (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_EOSMP_SHIFT))&ADC_INT_STATUS_EOSMP_MASK)
#define ADC_INT_STATUS_ADRDY_MASK      0x1u
#define ADC_INT_STATUS_ADRDY_SHIFT     0u
#define ADC_INT_STATUS_ADRDY_WIDTH     1u
#define ADC_INT_STATUS_ADRDY(x)        (((uint32_t)(((uint32_t)(x))<<ADC_INT_STATUS_ADRDY_SHIFT))&ADC_INT_STATUS_ADRDY_MASK)
/* INT_STATUS Reg Mask */
#define ADC_INT_STATUS_MASK            0x0F0F61FFu
/* INT_ENABLE Bit Fields */
#define ADC_INT_ENABLE_FIFO_RDY_IE_MASK 0x100u
#define ADC_INT_ENABLE_FIFO_RDY_IE_SHIFT 8u
#define ADC_INT_ENABLE_FIFO_RDY_IE_WIDTH 1u
#define ADC_INT_ENABLE_FIFO_RDY_IE(x)  (((uint32_t)(((uint32_t)(x))<<ADC_INT_ENABLE_FIFO_RDY_IE_SHIFT))&ADC_INT_ENABLE_FIFO_RDY_IE_MASK)
#define ADC_INT_ENABLE_ACMP_IE_MASK    0x80u
#define ADC_INT_ENABLE_ACMP_IE_SHIFT   7u
#define ADC_INT_ENABLE_ACMP_IE_WIDTH   1u
#define ADC_INT_ENABLE_ACMP_IE(x)      (((uint32_t)(((uint32_t)(x))<<ADC_INT_ENABLE_ACMP_IE_SHIFT))&ADC_INT_ENABLE_ACMP_IE_MASK)
#define ADC_INT_ENABLE_OVRIE_MASK      0x10u
#define ADC_INT_ENABLE_OVRIE_SHIFT     4u
#define ADC_INT_ENABLE_OVRIE_WIDTH     1u
#define ADC_INT_ENABLE_OVRIE(x)        (((uint32_t)(((uint32_t)(x))<<ADC_INT_ENABLE_OVRIE_SHIFT))&ADC_INT_ENABLE_OVRIE_MASK)
#define ADC_INT_ENABLE_EOSEQIE_MASK    0x8u
#define ADC_INT_ENABLE_EOSEQIE_SHIFT   3u
#define ADC_INT_ENABLE_EOSEQIE_WIDTH   1u
#define ADC_INT_ENABLE_EOSEQIE(x)      (((uint32_t)(((uint32_t)(x))<<ADC_INT_ENABLE_EOSEQIE_SHIFT))&ADC_INT_ENABLE_EOSEQIE_MASK)
#define ADC_INT_ENABLE_EOCIE_MASK      0x4u
#define ADC_INT_ENABLE_EOCIE_SHIFT     2u
#define ADC_INT_ENABLE_EOCIE_WIDTH     1u
#define ADC_INT_ENABLE_EOCIE(x)        (((uint32_t)(((uint32_t)(x))<<ADC_INT_ENABLE_EOCIE_SHIFT))&ADC_INT_ENABLE_EOCIE_MASK)
#define ADC_INT_ENABLE_EOSMPIE_MASK    0x2u
#define ADC_INT_ENABLE_EOSMPIE_SHIFT   1u
#define ADC_INT_ENABLE_EOSMPIE_WIDTH   1u
#define ADC_INT_ENABLE_EOSMPIE(x)      (((uint32_t)(((uint32_t)(x))<<ADC_INT_ENABLE_EOSMPIE_SHIFT))&ADC_INT_ENABLE_EOSMPIE_MASK)
#define ADC_INT_ENABLE_ADRDYIE_MASK    0x1u
#define ADC_INT_ENABLE_ADRDYIE_SHIFT   0u
#define ADC_INT_ENABLE_ADRDYIE_WIDTH   1u
#define ADC_INT_ENABLE_ADRDYIE(x)      (((uint32_t)(((uint32_t)(x))<<ADC_INT_ENABLE_ADRDYIE_SHIFT))&ADC_INT_ENABLE_ADRDYIE_MASK)
/* INT_ENABLE Reg Mask */
#define ADC_INT_ENABLE_MASK            0x0000019Fu
/* CONTROL Bit Fields */
#define ADC_CONTROL_ADRST_MASK         0x10u
#define ADC_CONTROL_ADRST_SHIFT        4u
#define ADC_CONTROL_ADRST_WIDTH        1u
#define ADC_CONTROL_ADRST(x)           (((uint32_t)(((uint32_t)(x))<<ADC_CONTROL_ADRST_SHIFT))&ADC_CONTROL_ADRST_MASK)
#define ADC_CONTROL_ADSTP_MASK         0x8u
#define ADC_CONTROL_ADSTP_SHIFT        3u
#define ADC_CONTROL_ADSTP_WIDTH        1u
#define ADC_CONTROL_ADSTP(x)           (((uint32_t)(((uint32_t)(x))<<ADC_CONTROL_ADSTP_SHIFT))&ADC_CONTROL_ADSTP_MASK)
#define ADC_CONTROL_ADSTART_MASK       0x4u
#define ADC_CONTROL_ADSTART_SHIFT      2u
#define ADC_CONTROL_ADSTART_WIDTH      1u
#define ADC_CONTROL_ADSTART(x)         (((uint32_t)(((uint32_t)(x))<<ADC_CONTROL_ADSTART_SHIFT))&ADC_CONTROL_ADSTART_MASK)
#define ADC_CONTROL_ADDIS_MASK         0x2u
#define ADC_CONTROL_ADDIS_SHIFT        1u
#define ADC_CONTROL_ADDIS_WIDTH        1u
#define ADC_CONTROL_ADDIS(x)           (((uint32_t)(((uint32_t)(x))<<ADC_CONTROL_ADDIS_SHIFT))&ADC_CONTROL_ADDIS_MASK)
#define ADC_CONTROL_ADEN_MASK          0x1u
#define ADC_CONTROL_ADEN_SHIFT         0u
#define ADC_CONTROL_ADEN_WIDTH         1u
#define ADC_CONTROL_ADEN(x)            (((uint32_t)(((uint32_t)(x))<<ADC_CONTROL_ADEN_SHIFT))&ADC_CONTROL_ADEN_MASK)
/* CONTROL Reg Mask */
#define ADC_CONTROL_MASK               0x0000001Fu
/* CFG1 Bit Fields */
#define ADC_CFG1_DIFF_MASK             0x80000000u
#define ADC_CFG1_DIFF_SHIFT            31u
#define ADC_CFG1_DIFF_WIDTH            1u
#define ADC_CFG1_DIFF(x)               (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_DIFF_SHIFT))&ADC_CFG1_DIFF_MASK)
#define ADC_CFG1_OVRMOD_MASK           0x40000000u
#define ADC_CFG1_OVRMOD_SHIFT          30u
#define ADC_CFG1_OVRMOD_WIDTH          1u
#define ADC_CFG1_OVRMOD(x)             (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_OVRMOD_SHIFT))&ADC_CFG1_OVRMOD_MASK)
#define ADC_CFG1_SEQ_LEN_MASK          0x1F000000u
#define ADC_CFG1_SEQ_LEN_SHIFT         24u
#define ADC_CFG1_SEQ_LEN_WIDTH         5u
#define ADC_CFG1_SEQ_LEN(x)            (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_SEQ_LEN_SHIFT))&ADC_CFG1_SEQ_LEN_MASK)
#define ADC_CFG1_SEQ_MOD_MASK          0xC00000u
#define ADC_CFG1_SEQ_MOD_SHIFT         22u
#define ADC_CFG1_SEQ_MOD_WIDTH         2u
#define ADC_CFG1_SEQ_MOD(x)            (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_SEQ_MOD_SHIFT))&ADC_CFG1_SEQ_MOD_MASK)
#define ADC_CFG1_AUTO_DIS_MASK         0x200000u
#define ADC_CFG1_AUTO_DIS_SHIFT        21u
#define ADC_CFG1_AUTO_DIS_WIDTH        1u
#define ADC_CFG1_AUTO_DIS(x)           (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_AUTO_DIS_SHIFT))&ADC_CFG1_AUTO_DIS_MASK)
#define ADC_CFG1_WAIT_MASK             0x100000u
#define ADC_CFG1_WAIT_SHIFT            20u
#define ADC_CFG1_WAIT_WIDTH            1u
#define ADC_CFG1_WAIT(x)               (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_WAIT_SHIFT))&ADC_CFG1_WAIT_MASK)
#define ADC_CFG1_TRIGSRC_MASK          0x70000u
#define ADC_CFG1_TRIGSRC_SHIFT         16u
#define ADC_CFG1_TRIGSRC_WIDTH         3u
#define ADC_CFG1_TRIGSRC(x)            (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_TRIGSRC_SHIFT))&ADC_CFG1_TRIGSRC_MASK)
#define ADC_CFG1_TRIGMODE_MASK         0x3800u
#define ADC_CFG1_TRIGMODE_SHIFT        11u
#define ADC_CFG1_TRIGMODE_WIDTH        3u
#define ADC_CFG1_TRIGMODE(x)           (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_TRIGMODE_SHIFT))&ADC_CFG1_TRIGMODE_MASK)
#define ADC_CFG1_ALIGN_MASK            0x400u
#define ADC_CFG1_ALIGN_SHIFT           10u
#define ADC_CFG1_ALIGN_WIDTH           1u
#define ADC_CFG1_ALIGN(x)              (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_ALIGN_SHIFT))&ADC_CFG1_ALIGN_MASK)
#define ADC_CFG1_RES_MASK              0x300u
#define ADC_CFG1_RES_SHIFT             8u
#define ADC_CFG1_RES_WIDTH             2u
#define ADC_CFG1_RES(x)                (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_RES_SHIFT))&ADC_CFG1_RES_MASK)
#define ADC_CFG1_DMAEN_MASK            0x1u
#define ADC_CFG1_DMAEN_SHIFT           0u
#define ADC_CFG1_DMAEN_WIDTH           1u
#define ADC_CFG1_DMAEN(x)              (((uint32_t)(((uint32_t)(x))<<ADC_CFG1_DMAEN_SHIFT))&ADC_CFG1_DMAEN_MASK)
/* CFG1 Reg Mask */
#define ADC_CFG1_MASK                  0xDFF73F01u
/* CFG2 Bit Fields */
#define ADC_CFG2_FWMARK_MASK           0x1F000000u
#define ADC_CFG2_FWMARK_SHIFT          24u
#define ADC_CFG2_FWMARK_WIDTH          5u
#define ADC_CFG2_FWMARK(x)             (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_FWMARK_SHIFT))&ADC_CFG2_FWMARK_MASK)
#define ADC_CFG2_TRG_CLR_MASK          0x80000u
#define ADC_CFG2_TRG_CLR_SHIFT         19u
#define ADC_CFG2_TRG_CLR_WIDTH         1u
#define ADC_CFG2_TRG_CLR(x)            (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_TRG_CLR_SHIFT))&ADC_CFG2_TRG_CLR_MASK)
#define ADC_CFG2_AVG_EN_MASK           0x40000u
#define ADC_CFG2_AVG_EN_SHIFT          18u
#define ADC_CFG2_AVG_EN_WIDTH          1u
#define ADC_CFG2_AVG_EN(x)             (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_AVG_EN_SHIFT))&ADC_CFG2_AVG_EN_MASK)
#define ADC_CFG2_AVG_LEN_MASK          0x30000u
#define ADC_CFG2_AVG_LEN_SHIFT         16u
#define ADC_CFG2_AVG_LEN_WIDTH         2u
#define ADC_CFG2_AVG_LEN(x)            (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_AVG_LEN_SHIFT))&ADC_CFG2_AVG_LEN_MASK)
#define ADC_CFG2_CG_ACK_MASK           0x4000u
#define ADC_CFG2_CG_ACK_SHIFT          14u
#define ADC_CFG2_CG_ACK_WIDTH          1u
#define ADC_CFG2_CG_ACK(x)             (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_CG_ACK_SHIFT))&ADC_CFG2_CG_ACK_MASK)
#define ADC_CFG2_CG_MASK               0x2000u
#define ADC_CFG2_CG_SHIFT              13u
#define ADC_CFG2_CG_WIDTH              1u
#define ADC_CFG2_CG(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_CG_SHIFT))&ADC_CFG2_CG_MASK)
#define ADC_CFG2_REF_EXT_MASK          0x1000u
#define ADC_CFG2_REF_EXT_SHIFT         12u
#define ADC_CFG2_REF_EXT_WIDTH         1u
#define ADC_CFG2_REF_EXT(x)            (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_REF_EXT_SHIFT))&ADC_CFG2_REF_EXT_MASK)
#define ADC_CFG2_DIV_MASK              0x300u
#define ADC_CFG2_DIV_SHIFT             8u
#define ADC_CFG2_DIV_WIDTH             2u
#define ADC_CFG2_DIV(x)                (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_DIV_SHIFT))&ADC_CFG2_DIV_MASK)
#define ADC_CFG2_STCNT_MASK            0xFFu
#define ADC_CFG2_STCNT_SHIFT           0u
#define ADC_CFG2_STCNT_WIDTH           8u
#define ADC_CFG2_STCNT(x)              (((uint32_t)(((uint32_t)(x))<<ADC_CFG2_STCNT_SHIFT))&ADC_CFG2_STCNT_MASK)
/* CFG2 Reg Mask */
#define ADC_CFG2_MASK                  0x1F0F73FFu
/* SMPR Bit Fields */
#define ADC_SMPR_SMP_OPT3_MASK         0xFF000000u
#define ADC_SMPR_SMP_OPT3_SHIFT        24u
#define ADC_SMPR_SMP_OPT3_WIDTH        8u
#define ADC_SMPR_SMP_OPT3(x)           (((uint32_t)(((uint32_t)(x))<<ADC_SMPR_SMP_OPT3_SHIFT))&ADC_SMPR_SMP_OPT3_MASK)
#define ADC_SMPR_SMP_OPT2_MASK         0xFF0000u
#define ADC_SMPR_SMP_OPT2_SHIFT        16u
#define ADC_SMPR_SMP_OPT2_WIDTH        8u
#define ADC_SMPR_SMP_OPT2(x)           (((uint32_t)(((uint32_t)(x))<<ADC_SMPR_SMP_OPT2_SHIFT))&ADC_SMPR_SMP_OPT2_MASK)
#define ADC_SMPR_SMP_OPT1_MASK         0xFF00u
#define ADC_SMPR_SMP_OPT1_SHIFT        8u
#define ADC_SMPR_SMP_OPT1_WIDTH        8u
#define ADC_SMPR_SMP_OPT1(x)           (((uint32_t)(((uint32_t)(x))<<ADC_SMPR_SMP_OPT1_SHIFT))&ADC_SMPR_SMP_OPT1_MASK)
#define ADC_SMPR_SMP_OPT0_MASK         0xFFu
#define ADC_SMPR_SMP_OPT0_SHIFT        0u
#define ADC_SMPR_SMP_OPT0_WIDTH        8u
#define ADC_SMPR_SMP_OPT0(x)           (((uint32_t)(((uint32_t)(x))<<ADC_SMPR_SMP_OPT0_SHIFT))&ADC_SMPR_SMP_OPT0_MASK)
/* SMPR Reg Mask */
#define ADC_SMPR_MASK                  0xFFFFFFFFu
/* CMP_CTRL Bit Fields */
#define ADC_CMP_CTRL_ACMPEN_MASK       0x80u
#define ADC_CMP_CTRL_ACMPEN_SHIFT      7u
#define ADC_CMP_CTRL_ACMPEN_WIDTH      1u
#define ADC_CMP_CTRL_ACMPEN(x)         (((uint32_t)(((uint32_t)(x))<<ADC_CMP_CTRL_ACMPEN_SHIFT))&ADC_CMP_CTRL_ACMPEN_MASK)
#define ADC_CMP_CTRL_ACMPSGL_MASK      0x40u
#define ADC_CMP_CTRL_ACMPSGL_SHIFT     6u
#define ADC_CMP_CTRL_ACMPSGL_WIDTH     1u
#define ADC_CMP_CTRL_ACMPSGL(x)        (((uint32_t)(((uint32_t)(x))<<ADC_CMP_CTRL_ACMPSGL_SHIFT))&ADC_CMP_CTRL_ACMPSGL_MASK)
#define ADC_CMP_CTRL_ACMPCH_MASK       0x3Fu
#define ADC_CMP_CTRL_ACMPCH_SHIFT      0u
#define ADC_CMP_CTRL_ACMPCH_WIDTH      6u
#define ADC_CMP_CTRL_ACMPCH(x)         (((uint32_t)(((uint32_t)(x))<<ADC_CMP_CTRL_ACMPCH_SHIFT))&ADC_CMP_CTRL_ACMPCH_MASK)
/* CMP_CTRL Reg Mask */
#define ADC_CMP_CTRL_MASK              0x000000FFu
/* CMP_TR Bit Fields */
#define ADC_CMP_TR_HT_MASK             0xFFF0000u
#define ADC_CMP_TR_HT_SHIFT            16u
#define ADC_CMP_TR_HT_WIDTH            12u
#define ADC_CMP_TR_HT(x)               (((uint32_t)(((uint32_t)(x))<<ADC_CMP_TR_HT_SHIFT))&ADC_CMP_TR_HT_MASK)
#define ADC_CMP_TR_LT_MASK             0xFFFu
#define ADC_CMP_TR_LT_SHIFT            0u
#define ADC_CMP_TR_LT_WIDTH            12u
#define ADC_CMP_TR_LT(x)               (((uint32_t)(((uint32_t)(x))<<ADC_CMP_TR_LT_SHIFT))&ADC_CMP_TR_LT_MASK)
/* CMP_TR Reg Mask */
#define ADC_CMP_TR_MASK                0x0FFF0FFFu
/* FIFO_DATA Bit Fields */
#define ADC_FIFO_DATA_FIFO_DATA_MASK   0xFFFFu
#define ADC_FIFO_DATA_FIFO_DATA_SHIFT  0u
#define ADC_FIFO_DATA_FIFO_DATA_WIDTH  16u
#define ADC_FIFO_DATA_FIFO_DATA(x)     (((uint32_t)(((uint32_t)(x))<<ADC_FIFO_DATA_FIFO_DATA_SHIFT))&ADC_FIFO_DATA_FIFO_DATA_MASK)
/* FIFO_DATA Reg Mask */
#define ADC_FIFO_DATA_MASK             0x0000FFFFu
/* SC Bit Fields */
#define ADC_SC_SMPSEL_MASK             0x300u
#define ADC_SC_SMPSEL_SHIFT            8u
#define ADC_SC_SMPSEL_WIDTH            2u
#define ADC_SC_SMPSEL(x)               (((uint32_t)(((uint32_t)(x))<<ADC_SC_SMPSEL_SHIFT))&ADC_SC_SMPSEL_MASK)
#define ADC_SC_COCO_MASK               0x80u
#define ADC_SC_COCO_SHIFT              7u
#define ADC_SC_COCO_WIDTH              1u
#define ADC_SC_COCO(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_SC_COCO_SHIFT))&ADC_SC_COCO_MASK)
#define ADC_SC_AIEN_MASK               0x40u
#define ADC_SC_AIEN_SHIFT              6u
#define ADC_SC_AIEN_WIDTH              1u
#define ADC_SC_AIEN(x)                 (((uint32_t)(((uint32_t)(x))<<ADC_SC_AIEN_SHIFT))&ADC_SC_AIEN_MASK)
#define ADC_SC_CHS_MASK                0x3Fu
#define ADC_SC_CHS_SHIFT               0u
#define ADC_SC_CHS_WIDTH               6u
#define ADC_SC_CHS(x)                  (((uint32_t)(((uint32_t)(x))<<ADC_SC_CHS_SHIFT))&ADC_SC_CHS_MASK)
/* SC0 Reg Mask */
#define ADC_SC_MASK                    0x000003FFu
/* RESULT Bit Fields */
#define ADC_RESULT_RESULT_MASK         0xFFFFu
#define ADC_RESULT_RESULT_SHIFT        0u
#define ADC_RESULT_RESULT_WIDTH        16u
#define ADC_RESULT_RESULT(x)           (((uint32_t)(((uint32_t)(x))<<ADC_RESULT_RESULT_SHIFT))&ADC_RESULT_RESULT_MASK)
/* RESULT0 Reg Mask */
#define ADC_RESULT_MASK                0x0000FFFFu
/**
 * @}
 */ /* end of group ADC_Register_Masks */
/**
 * @}
 */ /* end of group ADC_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif

#endif
