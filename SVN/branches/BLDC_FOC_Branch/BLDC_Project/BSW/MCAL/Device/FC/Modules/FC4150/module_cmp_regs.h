#ifndef _MODULE_CMP_KJO_Ufdi30_REGS_H_
#define _MODULE_CMP_KJO_Ufdi30_REGS_H_
#ifdef __cplusplus
extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- CMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup CMP_Peripheral_Access_Layer CMP Peripheral Access Layer
 * @{
 */
/** CMP - Size of Registers Arrays */
/** CMP - Register Layout Typedef */
typedef struct
{
    uint8_t  RESERVED_0[8];
    __IO uint32_t CCR0                          ; /* Comparator Control Register 0, offset: 0x8 */
    __IO uint32_t CCR1                          ; /* Comparator Control Register 1, offset: 0xC */
    __IO uint32_t CCR2                          ; /* Comparator Control Register 2, offset: 0x10 */
    uint8_t  RESERVED_1[4];
    __IO uint32_t DCR                           ; /* Comparator DAC Control Register, offset: 0x18 */
    __IO uint32_t IER                           ; /* Comparator Interrupt Enable Register, offset: 0x1C */
    __IO uint32_t CSR                           ; /* Comparator Status Register, offset: 0x20 */
    #ifdef CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE
    __IO uint32_t CSCR0                         ; /* Channel Scan Control Register 0, offset: 0x24 */
    __IO uint32_t CSCR1                         ; /* Channel Scan Control Register 1, offset: 0x28 */
    __IO uint32_t CSCSR                         ; /* Channel Scan Control and Status Register, offset: 0x2C */
    __IO uint32_t CSSR                          ; /* Channel Scan Status Register, offset: 0x30 */
    #endif
} CMP_Type, *CMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CMP Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup CMP_Register_Masks CMP Register Masks
 * @{
 */

/* CCR0 Bit Fields */
#define CMP_CCR0_DACEN_SEL_MASK        0x4u
#define CMP_CCR0_DACEN_SEL_SHIFT       2u
#define CMP_CCR0_DACEN_SEL_WIDTH       1u
#define CMP_CCR0_DACEN_SEL(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CCR0_DACEN_SEL_SHIFT))&CMP_CCR0_DACEN_SEL_MASK)
#define CMP_CCR0_LP_EN_MASK            0x2u
#define CMP_CCR0_LP_EN_SHIFT           1u
#define CMP_CCR0_LP_EN_WIDTH           1u
#define CMP_CCR0_LP_EN(x)              (((uint32_t)(((uint32_t)(x))<<CMP_CCR0_LP_EN_SHIFT))&CMP_CCR0_LP_EN_MASK)
#define CMP_CCR0_EN_MASK               0x1u
#define CMP_CCR0_EN_SHIFT              0u
#define CMP_CCR0_EN_WIDTH              1u
#define CMP_CCR0_EN(x)                 (((uint32_t)(((uint32_t)(x))<<CMP_CCR0_EN_SHIFT))&CMP_CCR0_EN_MASK)
/* CCR0 Reg Mask */
#define CMP_CCR0_MASK                  0x00000007u
/* CCR1 Bit Fields */
#define CMP_CCR1_FILT_PER_MASK         0xFF000000u
#define CMP_CCR1_FILT_PER_SHIFT        24u
#define CMP_CCR1_FILT_PER_WIDTH        8u
#define CMP_CCR1_FILT_PER(x)           (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_FILT_PER_SHIFT))&CMP_CCR1_FILT_PER_MASK)
#define CMP_CCR1_FILT_CNT_MASK         0x70000u
#define CMP_CCR1_FILT_CNT_SHIFT        16u
#define CMP_CCR1_FILT_CNT_WIDTH        3u
#define CMP_CCR1_FILT_CNT(x)           (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_FILT_CNT_SHIFT))&CMP_CCR1_FILT_CNT_MASK)
#define CMP_CCR1_EVT_SEL_MASK          0xC00u
#define CMP_CCR1_EVT_SEL_SHIFT         10u
#define CMP_CCR1_EVT_SEL_WIDTH         2u
#define CMP_CCR1_EVT_SEL(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_EVT_SEL_SHIFT))&CMP_CCR1_EVT_SEL_MASK)
#define CMP_CCR1_WIN_CLS_MASK          0x200u
#define CMP_CCR1_WIN_CLS_SHIFT         9u
#define CMP_CCR1_WIN_CLS_WIDTH         1u
#define CMP_CCR1_WIN_CLS(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_WIN_CLS_SHIFT))&CMP_CCR1_WIN_CLS_MASK)
#define CMP_CCR1_WIN_INV_MASK          0x100u
#define CMP_CCR1_WIN_INV_SHIFT         8u
#define CMP_CCR1_WIN_INV_WIDTH         1u
#define CMP_CCR1_WIN_INV(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_WIN_INV_SHIFT))&CMP_CCR1_WIN_INV_MASK)
#define CMP_CCR1_CMPOUT_WIN_OW_MASK    0x80u
#define CMP_CCR1_CMPOUT_WIN_OW_SHIFT   7u
#define CMP_CCR1_CMPOUT_WIN_OW_WIDTH   1u
#define CMP_CCR1_CMPOUT_WIN_OW(x)      (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_CMPOUT_WIN_OW_SHIFT))&CMP_CCR1_CMPOUT_WIN_OW_MASK)
#define CMP_CCR1_CMPOUT_WIN_OWEN_MASK  0x40u
#define CMP_CCR1_CMPOUT_WIN_OWEN_SHIFT 6u
#define CMP_CCR1_CMPOUT_WIN_OWEN_WIDTH 1u
#define CMP_CCR1_CMPOUT_WIN_OWEN(x)    (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_CMPOUT_WIN_OWEN_SHIFT))&CMP_CCR1_CMPOUT_WIN_OWEN_MASK)
#define CMP_CCR1_CMPOUT_PEN_MASK       0x20u
#define CMP_CCR1_CMPOUT_PEN_SHIFT      5u
#define CMP_CCR1_CMPOUT_PEN_WIDTH      1u
#define CMP_CCR1_CMPOUT_PEN(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_CMPOUT_PEN_SHIFT))&CMP_CCR1_CMPOUT_PEN_MASK)
#define CMP_CCR1_CMPOUT_SEL_MASK       0x10u
#define CMP_CCR1_CMPOUT_SEL_SHIFT      4u
#define CMP_CCR1_CMPOUT_SEL_WIDTH      1u
#define CMP_CCR1_CMPOUT_SEL(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_CMPOUT_SEL_SHIFT))&CMP_CCR1_CMPOUT_SEL_MASK)
#define CMP_CCR1_CMPOUT_INV_MASK       0x8u
#define CMP_CCR1_CMPOUT_INV_SHIFT      3u
#define CMP_CCR1_CMPOUT_INV_WIDTH      1u
#define CMP_CCR1_CMPOUT_INV(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_CMPOUT_INV_SHIFT))&CMP_CCR1_CMPOUT_INV_MASK)
#define CMP_CCR1_DMA_EN_MASK           0x4u
#define CMP_CCR1_DMA_EN_SHIFT          2u
#define CMP_CCR1_DMA_EN_WIDTH          1u
#define CMP_CCR1_DMA_EN(x)             (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_DMA_EN_SHIFT))&CMP_CCR1_DMA_EN_MASK)
#define CMP_CCR1_SAMPLE_EN_MASK        0x2u
#define CMP_CCR1_SAMPLE_EN_SHIFT       1u
#define CMP_CCR1_SAMPLE_EN_WIDTH       1u
#define CMP_CCR1_SAMPLE_EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_SAMPLE_EN_SHIFT))&CMP_CCR1_SAMPLE_EN_MASK)
#define CMP_CCR1_WIN_EN_MASK           0x1u
#define CMP_CCR1_WIN_EN_SHIFT          0u
#define CMP_CCR1_WIN_EN_WIDTH          1u
#define CMP_CCR1_WIN_EN(x)             (((uint32_t)(((uint32_t)(x))<<CMP_CCR1_WIN_EN_SHIFT))&CMP_CCR1_WIN_EN_MASK)
/* CCR1 Reg Mask */
#define CMP_CCR1_MASK                  0xFF070FFFu
/* CCR2 Bit Fields */
#define CMP_CCR2_INMSEL_MASK           0x30000000u
#define CMP_CCR2_INMSEL_SHIFT          28u
#define CMP_CCR2_INMSEL_WIDTH          2u
#define CMP_CCR2_INMSEL(x)             (((uint32_t)(((uint32_t)(x))<<CMP_CCR2_INMSEL_SHIFT))&CMP_CCR2_INMSEL_MASK)
#define CMP_CCR2_INPSEL_MASK           0x3000000u
#define CMP_CCR2_INPSEL_SHIFT          24u
#define CMP_CCR2_INPSEL_WIDTH          2u
#define CMP_CCR2_INPSEL(x)             (((uint32_t)(((uint32_t)(x))<<CMP_CCR2_INPSEL_SHIFT))&CMP_CCR2_INPSEL_MASK)
#define CMP_CCR2_MSEL_MASK             0x700000u
#define CMP_CCR2_MSEL_SHIFT            20u
#define CMP_CCR2_MSEL_WIDTH            3u
#define CMP_CCR2_MSEL(x)               (((uint32_t)(((uint32_t)(x))<<CMP_CCR2_MSEL_SHIFT))&CMP_CCR2_MSEL_MASK)
#define CMP_CCR2_PSEL_MASK             0x70000u
#define CMP_CCR2_PSEL_SHIFT            16u
#define CMP_CCR2_PSEL_WIDTH            3u
#define CMP_CCR2_PSEL(x)               (((uint32_t)(((uint32_t)(x))<<CMP_CCR2_PSEL_SHIFT))&CMP_CCR2_PSEL_MASK)
#define CMP_CCR2_HYSTCTR_MASK          0x30u
#define CMP_CCR2_HYSTCTR_SHIFT         4u
#define CMP_CCR2_HYSTCTR_WIDTH         2u
#define CMP_CCR2_HYSTCTR(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CCR2_HYSTCTR_SHIFT))&CMP_CCR2_HYSTCTR_MASK)
#define CMP_CCR2_HPMD_MASK             0x1u
#define CMP_CCR2_HPMD_SHIFT            0u
#define CMP_CCR2_HPMD_WIDTH            1u
#define CMP_CCR2_HPMD(x)               (((uint32_t)(((uint32_t)(x))<<CMP_CCR2_HPMD_SHIFT))&CMP_CCR2_HPMD_MASK)
/* CCR2 Reg Mask */
#define CMP_CCR2_MASK                  0x33770031u
/* DCR Bit Fields */
#define CMP_DCR_DAC_DATA_MASK          0xFF0000u
#define CMP_DCR_DAC_DATA_SHIFT         16u
#define CMP_DCR_DAC_DATA_WIDTH         8u
#define CMP_DCR_DAC_DATA(x)            (((uint32_t)(((uint32_t)(x))<<CMP_DCR_DAC_DATA_SHIFT))&CMP_DCR_DAC_DATA_MASK)
#define CMP_DCR_VRSEL_MASK             0x100u
#define CMP_DCR_VRSEL_SHIFT            8u
#define CMP_DCR_VRSEL_WIDTH            1u
#define CMP_DCR_VRSEL(x)               (((uint32_t)(((uint32_t)(x))<<CMP_DCR_VRSEL_SHIFT))&CMP_DCR_VRSEL_MASK)
#define CMP_DCR_DAC_EN_MASK            0x1u
#define CMP_DCR_DAC_EN_SHIFT           0u
#define CMP_DCR_DAC_EN_WIDTH           1u
#define CMP_DCR_DAC_EN(x)              (((uint32_t)(((uint32_t)(x))<<CMP_DCR_DAC_EN_SHIFT))&CMP_DCR_DAC_EN_MASK)
/* DCR Reg Mask */
#define CMP_DCR_MASK                   0x00FF0101u
/* IER Bit Fields */
#ifdef CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE
#define CMP_IER_CSF_IE_MASK            0x4u
#define CMP_IER_CSF_IE_SHIFT           2u
#define CMP_IER_CSF_IE_WIDTH           1u
#define CMP_IER_CSF_IE(x)              (((uint32_t)(((uint32_t)(x))<<CMP_IER_CSF_IE_SHIFT))&CMP_IER_CSF_IE_MASK)
#endif
#define CMP_IER_CFF_IE_MASK            0x2u
#define CMP_IER_CFF_IE_SHIFT           1u
#define CMP_IER_CFF_IE_WIDTH           1u
#define CMP_IER_CFF_IE(x)              (((uint32_t)(((uint32_t)(x))<<CMP_IER_CFF_IE_SHIFT))&CMP_IER_CFF_IE_MASK)
#define CMP_IER_CFR_IE_MASK            0x1u
#define CMP_IER_CFR_IE_SHIFT           0u
#define CMP_IER_CFR_IE_WIDTH           1u
#define CMP_IER_CFR_IE(x)              (((uint32_t)(((uint32_t)(x))<<CMP_IER_CFR_IE_SHIFT))&CMP_IER_CFR_IE_MASK)
/* IER Reg Mask */
#define CMP_IER_MASK                   0x00000003u
/* CSR Bit Fields */
#define CMP_CSR_CMPOUT_FILTER_MASK     0x100u
#define CMP_CSR_CMPOUT_FILTER_SHIFT    8u
#define CMP_CSR_CMPOUT_FILTER_WIDTH    1u
#define CMP_CSR_CMPOUT_FILTER(x)       (((uint32_t)(((uint32_t)(x))<<CMP_CSR_CMPOUT_FILTER_SHIFT))&CMP_CSR_CMPOUT_FILTER_MASK)
#ifdef  CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE
#define CMP_CSR_CSF_MASK               0x4u
#define CMP_CSR_CSF_SHIFT              2u
#define CMP_CSR_CSF_WIDTH              1u
#define CMP_CSR_CSF(x)                 (((uint32_t)(((uint32_t)(x))<<CMP_CSR_CSF_SHIFT))&CMP_CSR_CSF_MASK)
#endif
#define CMP_CSR_CFF_MASK               0x2u
#define CMP_CSR_CFF_SHIFT              1u
#define CMP_CSR_CFF_WIDTH              1u
#define CMP_CSR_CFF(x)                 (((uint32_t)(((uint32_t)(x))<<CMP_CSR_CFF_SHIFT))&CMP_CSR_CFF_MASK)
#define CMP_CSR_CFR_MASK               0x1u
#define CMP_CSR_CFR_SHIFT              0u
#define CMP_CSR_CFR_WIDTH              1u
#define CMP_CSR_CFR(x)                 (((uint32_t)(((uint32_t)(x))<<CMP_CSR_CFR_SHIFT))&CMP_CSR_CFR_MASK)
/* CSR Reg Mask */
#define CMP_CSR_MASK                   0x00000103u

#ifdef CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE

/* CSCR0 Bit Fields */
#define CMP_CSCR0_CS_INITMOD_MASK      0x3F0000u
#define CMP_CSCR0_CS_INITMOD_SHIFT     16u
#define CMP_CSCR0_CS_INITMOD_WIDTH     6u
#define CMP_CSCR0_CS_INITMOD(x)        (((uint32_t)(((uint32_t)(x))<<CMP_CSCR0_CS_INITMOD_SHIFT))&CMP_CSCR0_CS_INITMOD_MASK)
#define CMP_CSCR0_CS_NSAM_MASK         0x300u
#define CMP_CSCR0_CS_NSAM_SHIFT        8u
#define CMP_CSCR0_CS_NSAM_WIDTH        2u
#define CMP_CSCR0_CS_NSAM(x)           (((uint32_t)(((uint32_t)(x))<<CMP_CSCR0_CS_NSAM_SHIFT))&CMP_CSCR0_CS_NSAM_MASK)
#define CMP_CSCR0_CS_EN_MASK           0x1u
#define CMP_CSCR0_CS_EN_SHIFT          0u
#define CMP_CSCR0_CS_EN_WIDTH          1u
#define CMP_CSCR0_CS_EN(x)             (((uint32_t)(((uint32_t)(x))<<CMP_CSCR0_CS_EN_SHIFT))&CMP_CSCR0_CS_EN_MASK)
/* CSCR0 Reg Mask */
#define CMP_CSCR0_MASK                 0x003F0301u
/* CSCR1 Bit Fields */
#define CMP_CSCR1_FIXCH_MASK           0x700000u
#define CMP_CSCR1_FIXCH_SHIFT          20u
#define CMP_CSCR1_FIXCH_WIDTH          3u
#define CMP_CSCR1_FIXCH(x)             (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_FIXCH_SHIFT))&CMP_CSCR1_FIXCH_MASK)
#define CMP_CSCR1_FIXP_MASK            0x10000u
#define CMP_CSCR1_FIXP_SHIFT           16u
#define CMP_CSCR1_FIXP_WIDTH           1u
#define CMP_CSCR1_FIXP(x)              (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_FIXP_SHIFT))&CMP_CSCR1_FIXP_MASK)
#define CMP_CSCR1_CS_CH7EN_MASK        0x80u
#define CMP_CSCR1_CS_CH7EN_SHIFT       7u
#define CMP_CSCR1_CS_CH7EN_WIDTH       1u
#define CMP_CSCR1_CS_CH7EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH7EN_SHIFT))&CMP_CSCR1_CS_CH7EN_MASK)
#define CMP_CSCR1_CS_CH6EN_MASK        0x40u
#define CMP_CSCR1_CS_CH6EN_SHIFT       6u
#define CMP_CSCR1_CS_CH6EN_WIDTH       1u
#define CMP_CSCR1_CS_CH6EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH6EN_SHIFT))&CMP_CSCR1_CS_CH6EN_MASK)
#define CMP_CSCR1_CS_CH5EN_MASK        0x20u
#define CMP_CSCR1_CS_CH5EN_SHIFT       5u
#define CMP_CSCR1_CS_CH5EN_WIDTH       1u
#define CMP_CSCR1_CS_CH5EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH5EN_SHIFT))&CMP_CSCR1_CS_CH5EN_MASK)
#define CMP_CSCR1_CS_CH4EN_MASK        0x10u
#define CMP_CSCR1_CS_CH4EN_SHIFT       4u
#define CMP_CSCR1_CS_CH4EN_WIDTH       1u
#define CMP_CSCR1_CS_CH4EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH4EN_SHIFT))&CMP_CSCR1_CS_CH4EN_MASK)
#define CMP_CSCR1_CS_CH3EN_MASK        0x8u
#define CMP_CSCR1_CS_CH3EN_SHIFT       3u
#define CMP_CSCR1_CS_CH3EN_WIDTH       1u
#define CMP_CSCR1_CS_CH3EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH3EN_SHIFT))&CMP_CSCR1_CS_CH3EN_MASK)
#define CMP_CSCR1_CS_CH2EN_MASK        0x4u
#define CMP_CSCR1_CS_CH2EN_SHIFT       2u
#define CMP_CSCR1_CS_CH2EN_WIDTH       1u
#define CMP_CSCR1_CS_CH2EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH2EN_SHIFT))&CMP_CSCR1_CS_CH2EN_MASK)
#define CMP_CSCR1_CS_CH1EN_MASK        0x2u
#define CMP_CSCR1_CS_CH1EN_SHIFT       1u
#define CMP_CSCR1_CS_CH1EN_WIDTH       1u
#define CMP_CSCR1_CS_CH1EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH1EN_SHIFT))&CMP_CSCR1_CS_CH1EN_MASK)
#define CMP_CSCR1_CS_CH0EN_MASK        0x1u
#define CMP_CSCR1_CS_CH0EN_SHIFT       0u
#define CMP_CSCR1_CS_CH0EN_WIDTH       1u
#define CMP_CSCR1_CS_CH0EN(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCR1_CS_CH0EN_SHIFT))&CMP_CSCR1_CS_CH0EN_MASK)
/* CSCR1 Reg Mask */
#define CMP_CSCR1_MASK                 0x007100FFu
/* CSCSR Bit Fields */
#define CMP_CSCSR_CS_SWCLR_MASK        0x20000u
#define CMP_CSCSR_CS_SWCLR_SHIFT       17u
#define CMP_CSCSR_CS_SWCLR_WIDTH       1u
#define CMP_CSCSR_CS_SWCLR(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_SWCLR_SHIFT))&CMP_CSCSR_CS_SWCLR_MASK)
#define CMP_CSCSR_CS_ACLR_MASK         0x10000u
#define CMP_CSCSR_CS_ACLR_SHIFT        16u
#define CMP_CSCSR_CS_ACLR_WIDTH        1u
#define CMP_CSCSR_CS_ACLR(x)           (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_ACLR_SHIFT))&CMP_CSCSR_CS_ACLR_MASK)
#define CMP_CSCSR_CS_CH7OUT_MASK       0x80u
#define CMP_CSCSR_CS_CH7OUT_SHIFT      7u
#define CMP_CSCSR_CS_CH7OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH7OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH7OUT_SHIFT))&CMP_CSCSR_CS_CH7OUT_MASK)
#define CMP_CSCSR_CS_CH6OUT_MASK       0x40u
#define CMP_CSCSR_CS_CH6OUT_SHIFT      6u
#define CMP_CSCSR_CS_CH6OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH6OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH6OUT_SHIFT))&CMP_CSCSR_CS_CH6OUT_MASK)
#define CMP_CSCSR_CS_CH5OUT_MASK       0x20u
#define CMP_CSCSR_CS_CH5OUT_SHIFT      5u
#define CMP_CSCSR_CS_CH5OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH5OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH5OUT_SHIFT))&CMP_CSCSR_CS_CH5OUT_MASK)
#define CMP_CSCSR_CS_CH4OUT_MASK       0x10u
#define CMP_CSCSR_CS_CH4OUT_SHIFT      4u
#define CMP_CSCSR_CS_CH4OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH4OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH4OUT_SHIFT))&CMP_CSCSR_CS_CH4OUT_MASK)
#define CMP_CSCSR_CS_CH3OUT_MASK       0x8u
#define CMP_CSCSR_CS_CH3OUT_SHIFT      3u
#define CMP_CSCSR_CS_CH3OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH3OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH3OUT_SHIFT))&CMP_CSCSR_CS_CH3OUT_MASK)
#define CMP_CSCSR_CS_CH2OUT_MASK       0x4u
#define CMP_CSCSR_CS_CH2OUT_SHIFT      2u
#define CMP_CSCSR_CS_CH2OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH2OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH2OUT_SHIFT))&CMP_CSCSR_CS_CH2OUT_MASK)
#define CMP_CSCSR_CS_CH1OUT_MASK       0x2u
#define CMP_CSCSR_CS_CH1OUT_SHIFT      1u
#define CMP_CSCSR_CS_CH1OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH1OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH1OUT_SHIFT))&CMP_CSCSR_CS_CH1OUT_MASK)
#define CMP_CSCSR_CS_CH0OUT_MASK       0x1u
#define CMP_CSCSR_CS_CH0OUT_SHIFT      0u
#define CMP_CSCSR_CS_CH0OUT_WIDTH      1u
#define CMP_CSCSR_CS_CH0OUT(x)         (((uint32_t)(((uint32_t)(x))<<CMP_CSCSR_CS_CH0OUT_SHIFT))&CMP_CSCSR_CS_CH0OUT_MASK)
/* CSCSR Reg Mask */
#define CMP_CSCSR_MASK                 0x000300FFu
/* CSSR Bit Fields */
#define CMP_CSSR_CS_ACTIVE_MASK        0x10000u
#define CMP_CSSR_CS_ACTIVE_SHIFT       16u
#define CMP_CSSR_CS_ACTIVE_WIDTH       1u
#define CMP_CSSR_CS_ACTIVE(x)          (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_ACTIVE_SHIFT))&CMP_CSSR_CS_ACTIVE_MASK)
#define CMP_CSSR_CS_CH7F_MASK          0x80u
#define CMP_CSSR_CS_CH7F_SHIFT         7u
#define CMP_CSSR_CS_CH7F_WIDTH         1u
#define CMP_CSSR_CS_CH7F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH7F_SHIFT))&CMP_CSSR_CS_CH7F_MASK)
#define CMP_CSSR_CS_CH6F_MASK          0x40u
#define CMP_CSSR_CS_CH6F_SHIFT         6u
#define CMP_CSSR_CS_CH6F_WIDTH         1u
#define CMP_CSSR_CS_CH6F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH6F_SHIFT))&CMP_CSSR_CS_CH6F_MASK)
#define CMP_CSSR_CS_CH5F_MASK          0x20u
#define CMP_CSSR_CS_CH5F_SHIFT         5u
#define CMP_CSSR_CS_CH5F_WIDTH         1u
#define CMP_CSSR_CS_CH5F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH5F_SHIFT))&CMP_CSSR_CS_CH5F_MASK)
#define CMP_CSSR_CS_CH4F_MASK          0x10u
#define CMP_CSSR_CS_CH4F_SHIFT         4u
#define CMP_CSSR_CS_CH4F_WIDTH         1u
#define CMP_CSSR_CS_CH4F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH4F_SHIFT))&CMP_CSSR_CS_CH4F_MASK)
#define CMP_CSSR_CS_CH3F_MASK          0x8u
#define CMP_CSSR_CS_CH3F_SHIFT         3u
#define CMP_CSSR_CS_CH3F_WIDTH         1u
#define CMP_CSSR_CS_CH3F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH3F_SHIFT))&CMP_CSSR_CS_CH3F_MASK)
#define CMP_CSSR_CS_CH2F_MASK          0x4u
#define CMP_CSSR_CS_CH2F_SHIFT         2u
#define CMP_CSSR_CS_CH2F_WIDTH         1u
#define CMP_CSSR_CS_CH2F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH2F_SHIFT))&CMP_CSSR_CS_CH2F_MASK)
#define CMP_CSSR_CS_CH1F_MASK          0x2u
#define CMP_CSSR_CS_CH1F_SHIFT         1u
#define CMP_CSSR_CS_CH1F_WIDTH         1u
#define CMP_CSSR_CS_CH1F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH1F_SHIFT))&CMP_CSSR_CS_CH1F_MASK)
#define CMP_CSSR_CS_CH0F_MASK          0x1u
#define CMP_CSSR_CS_CH0F_SHIFT         0u
#define CMP_CSSR_CS_CH0F_WIDTH         1u
#define CMP_CSSR_CS_CH0F(x)            (((uint32_t)(((uint32_t)(x))<<CMP_CSSR_CS_CH0F_SHIFT))&CMP_CSSR_CS_CH0F_MASK)
/* CSSR Reg Mask */
#define CMP_CSSR_MASK                  0x000100FFu

#endif
/**
 * @}
 */ /* end of group CMP_Register_Masks */
/**
 * @}
 */ /* end of group CMP_Peripheral_Access_Layer */

#ifdef __cplusplus
}
#endif
#endif
