#ifndef _MODULE_EIM_KJO_Ufdi11_REGS_H_
#define _MODULE_EIM_KJO_Ufdi11_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- EIM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup EIM_Peripheral_Access_Layer EIM Peripheral Access Layer
 * @{
 */
/** EIM - Size of Registers Arrays */
/** EIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR                            ; /* EIM Configuration Register, offset: 0x0 */
  __IO uint32_t CHENR                         ; /* EIM Channel Enable Register, offset: 0x4 */
       uint8_t  RESERVED_0[248];
  __IO uint32_t WORD0_CHR0                    ; /* EIM Channel 0 Word0 inject Register, offset: 0x100 */
  __IO uint32_t WORD1_CHR0                    ; /* EIM Channel 0 Word1 inject Register, offset: 0x104 */
       uint8_t  RESERVED_1[248];
  __IO uint32_t WORD0_CHR1                    ; /* EIM Channel 1 Word0 inject Register, offset: 0x200 */
  __IO uint32_t WORD1_CHR1                    ; /* EIM Channel 1 Word1 inject Register, offset: 0x204 */
       uint8_t  RESERVED_2[248];
  __IO uint32_t WORD0_CHR2                    ; /* EIM Channel 2 Word0 inject Register, offset: 0x300 */
  __IO uint32_t WORD1_CHR2                    ; /* EIM Channel 2 Word1 inject Register, offset: 0x304 */
       uint8_t  RESERVED_3[248];
  __IO uint32_t WORD0_CHR3                    ; /* EIM Channel 3 Word0 inject Register, offset: 0x400 */
  __IO uint32_t WORD1_CHR3                    ; /* EIM Channel 3 Word1 inject Register, offset: 0x404 */
#if (EIM_MAXCHANNEL == 7u)
       uint8_t  RESERVED_4[248];
  __IO uint32_t WORD0_CHR4                    ; /* EIM Channel 4 Word0 inject Register, offset: 0x500 */
       uint8_t  RESERVED_5[252];
  __IO uint32_t WORD0_CHR5                    ; /* EIM Channel 5 Word0 inject Register, offset: 0x600 */
       uint8_t  RESERVED_6[252];
  __IO uint32_t WORD0_CHR6                    ; /* EIM Channel 6 Word0 inject Register, offset: 0x700 */
       uint8_t  RESERVED_7[252];
  __IO uint32_t WORD0_CHR7                    ; /* EIM Channel 7 Word0 inject Register, offset: 0x800 */
#endif
} EIM_Type, *EIM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- EIM Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup EIM_Register_Masks EIM Register Masks
 * @{
 */
 
/* CR Bit Fields */
#define EIM_CR_GEIEN_MASK              0x1u
#define EIM_CR_GEIEN_SHIFT             0u
#define EIM_CR_GEIEN_WIDTH             1u
#define EIM_CR_GEIEN(x)                (((uint32_t)(((uint32_t)(x))<<EIM_CR_GEIEN_SHIFT))&EIM_CR_GEIEN_MASK)
/* CR Reg Mask */
#define EIM_CR_MASK                    0x00000001u

/* CHENR Bit Fields */
#define EIM_CHENR_CH0EN_MASK           0x80000000u
#define EIM_CHENR_CH0EN_SHIFT          31u
#define EIM_CHENR_CH0EN_WIDTH          1u
#define EIM_CHENR_CH0EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH0EN_SHIFT))&EIM_CHENR_CH0EN_MASK)
#define EIM_CHENR_CH1EN_MASK           0x40000000u
#define EIM_CHENR_CH1EN_SHIFT          30u
#define EIM_CHENR_CH1EN_WIDTH          1u
#define EIM_CHENR_CH1EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH1EN_SHIFT))&EIM_CHENR_CH1EN_MASK)
#define EIM_CHENR_CH2EN_MASK           0x20000000u
#define EIM_CHENR_CH2EN_SHIFT          29u
#define EIM_CHENR_CH2EN_WIDTH          1u
#define EIM_CHENR_CH2EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH2EN_SHIFT))&EIM_CHENR_CH2EN_MASK)
#define EIM_CHENR_CH3EN_MASK           0x10000000u
#define EIM_CHENR_CH3EN_SHIFT          28u
#define EIM_CHENR_CH3EN_WIDTH          1u
#define EIM_CHENR_CH3EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH3EN_SHIFT))&EIM_CHENR_CH3EN_MASK)
#define EIM_CHENR_CH4EN_MASK           0x8000000u
#define EIM_CHENR_CH4EN_SHIFT          27u
#define EIM_CHENR_CH4EN_WIDTH          1u
#define EIM_CHENR_CH4EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH4EN_SHIFT))&EIM_CHENR_CH4EN_MASK)
#define EIM_CHENR_CH5EN_MASK           0x4000000u
#define EIM_CHENR_CH5EN_SHIFT          26u
#define EIM_CHENR_CH5EN_WIDTH          1u
#define EIM_CHENR_CH5EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH5EN_SHIFT))&EIM_CHENR_CH5EN_MASK)
#define EIM_CHENR_CH6EN_MASK           0x2000000u
#define EIM_CHENR_CH6EN_SHIFT          25u
#define EIM_CHENR_CH6EN_WIDTH          1u
#define EIM_CHENR_CH6EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH6EN_SHIFT))&EIM_CHENR_CH6EN_MASK)
#define EIM_CHENR_CH7EN_MASK           0x1000000u
#define EIM_CHENR_CH7EN_SHIFT          24u
#define EIM_CHENR_CH7EN_WIDTH          1u
#define EIM_CHENR_CH7EN(x)             (((uint32_t)(((uint32_t)(x))<<EIM_CHENR_CH7EN_SHIFT))&EIM_CHENR_CH7EN_MASK)
/* CHENR Reg Mask */
#define EIM_CHENR_MASK                 0xFF000000u

/* WORD0_CHR Bit Fields */
#define EIM_WORD0_CHR_CHKBIT_MASK_MASK 0xFFFFF000u
#define EIM_WORD0_CHR_CHKBIT_MASK_SHIFT 12u
#define EIM_WORD0_CHR_CHKBIT_MASK_WIDTH 20u
#define EIM_WORD0_CHR_CHKBIT_MASK(x)   (((uint32_t)(((uint32_t)(x))<<EIM_WORD0_CHR_CHKBIT_MASK_SHIFT))&EIM_WORD0_CHR_CHKBIT_MASK_MASK)
/* WORD0_CHR0 Reg Mask */
#define EIM_WORD0_CHR_MASK             0xFFFFF000u

/* WORD1_CHR Bit Fields */
#define EIM_WORD1_CHR_B0_3DATA_MASK_MASK 0xFFFFFFFFu
#define EIM_WORD1_CHR_B0_3DATA_MASK_SHIFT 0u
#define EIM_WORD1_CHR_B0_3DATA_MASK_WIDTH 32u
#define EIM_WORD1_CHR_B0_3DATA_MASK(x) (((uint32_t)(((uint32_t)(x))<<EIM_WORD1_CHR_B0_3DATA_MASK_SHIFT))&EIM_WORD1_CHR_B0_3DATA_MASK_MASK)
/* WORD1_CHR0 Reg Mask */
#define EIM_WORD1_CHR_MASK             0xFFFFFFFFu

/**
 * @}
 */ /* end of group EIM_Register_Masks */
/**
 * @}
 */ /* end of group EIM_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
