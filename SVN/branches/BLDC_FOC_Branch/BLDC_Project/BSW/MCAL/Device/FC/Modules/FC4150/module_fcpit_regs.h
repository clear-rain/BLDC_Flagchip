#ifndef _MODULE_FCPIT_KJO_Ufdi23_REGS_H_
#define _MODULE_FCPIT_KJO_Ufdi23_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- FCPIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCPIT_Peripheral_Access_Layer FCPIT Peripheral Access Layer
 * @{
 */
/** FCPIT - Size of Registers Arrays */
/** @brief Fcpit max channel number */
#define MAX_FCPIT_CHANNEL_NUM 4U
/** FCPIT - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[8];
  __IO uint32_t MCR                           ; /* Module Control Register, offset: 0x8 */
  __IO uint32_t MSR                           ; /* Module Status Register, offset: 0xC */
  __IO uint32_t MIER                          ; /* Module Interrupt Enable Register, offset: 0x10 */
  __IO uint32_t SETTEN                        ; /* Set Timer Enable Register, offset: 0x14 */
  __O  uint32_t CLRTEN                        ; /* Clear Timer Enable Register, offset: 0x18 */
  struct
  {
		   uint8_t  RESERVED_1[4];
	  __IO uint32_t TVAL                      ; /* Timer Value Register, offset: 0x20 0x30 0x40 0x50*/
	  __IO uint32_t CVAL 					;	/* Current Timer Value Register, offset: 0x24 0x34 0x44 0x54,This register only available on FC4150F1M_B*/
	  __IO uint32_t TCTRL                     ; /* Timer Control Register, offset: 0x28 0x38 0x48 0x58*/
  }CONTROLS[MAX_FCPIT_CHANNEL_NUM];
} FCPIT_Type, *FCPIT_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FCPIT Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCPIT_Register_Masks FCPIT Register Masks
 * @{
 */
 
/* MCR Bit Fields */
#define FCPIT_MCR_DBG_EN_MASK          0x8u
#define FCPIT_MCR_DBG_EN_SHIFT         3u
#define FCPIT_MCR_DBG_EN_WIDTH         1u
#define FCPIT_MCR_DBG_EN(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_MCR_DBG_EN_SHIFT))&FCPIT_MCR_DBG_EN_MASK)
#define FCPIT_MCR_LPM_EN_MASK          0x4u
#define FCPIT_MCR_LPM_EN_SHIFT         2u
#define FCPIT_MCR_LPM_EN_WIDTH         1u
#define FCPIT_MCR_LPM_EN(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_MCR_LPM_EN_SHIFT))&FCPIT_MCR_LPM_EN_MASK)
#define FCPIT_MCR_SW_RST_MASK          0x2u
#define FCPIT_MCR_SW_RST_SHIFT         1u
#define FCPIT_MCR_SW_RST_WIDTH         1u
#define FCPIT_MCR_SW_RST(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_MCR_SW_RST_SHIFT))&FCPIT_MCR_SW_RST_MASK)
#define FCPIT_MCR_M_CEN_MASK           0x1u
#define FCPIT_MCR_M_CEN_SHIFT          0u
#define FCPIT_MCR_M_CEN_WIDTH          1u
#define FCPIT_MCR_M_CEN(x)             (((uint32_t)(((uint32_t)(x))<<FCPIT_MCR_M_CEN_SHIFT))&FCPIT_MCR_M_CEN_MASK)
/* MCR Reg Mask */
#define FCPIT_MCR_MASK                 0x0000000Fu

/* MSR Bit Fields */
#define FCPIT_MSR_TIF3_MASK            0x8u
#define FCPIT_MSR_TIF3_SHIFT           3u
#define FCPIT_MSR_TIF3_WIDTH           1u
#define FCPIT_MSR_TIF3(x)              (((uint32_t)(((uint32_t)(x))<<FCPIT_MSR_TIF3_SHIFT))&FCPIT_MSR_TIF3_MASK)
#define FCPIT_MSR_TIF2_MASK            0x4u
#define FCPIT_MSR_TIF2_SHIFT           2u
#define FCPIT_MSR_TIF2_WIDTH           1u
#define FCPIT_MSR_TIF2(x)              (((uint32_t)(((uint32_t)(x))<<FCPIT_MSR_TIF2_SHIFT))&FCPIT_MSR_TIF2_MASK)
#define FCPIT_MSR_TIF1_MASK            0x2u
#define FCPIT_MSR_TIF1_SHIFT           1u
#define FCPIT_MSR_TIF1_WIDTH           1u
#define FCPIT_MSR_TIF1(x)              (((uint32_t)(((uint32_t)(x))<<FCPIT_MSR_TIF1_SHIFT))&FCPIT_MSR_TIF1_MASK)
#define FCPIT_MSR_TIF0_MASK            0x1u
#define FCPIT_MSR_TIF0_SHIFT           0u
#define FCPIT_MSR_TIF0_WIDTH           1u
#define FCPIT_MSR_TIF0(x)              (((uint32_t)(((uint32_t)(x))<<FCPIT_MSR_TIF0_SHIFT))&FCPIT_MSR_TIF0_MASK)
/* MSR Reg Mask */
#define FCPIT_MSR_MASK                 0x0000000Fu

/* MIER Bit Fields */
#define FCPIT_MIER_TIE3_MASK           0x8u
#define FCPIT_MIER_TIE3_SHIFT          3u
#define FCPIT_MIER_TIE3_WIDTH          1u
#define FCPIT_MIER_TIE3(x)             (((uint32_t)(((uint32_t)(x))<<FCPIT_MIER_TIE3_SHIFT))&FCPIT_MIER_TIE3_MASK)
#define FCPIT_MIER_TIE2_MASK           0x4u
#define FCPIT_MIER_TIE2_SHIFT          2u
#define FCPIT_MIER_TIE2_WIDTH          1u
#define FCPIT_MIER_TIE2(x)             (((uint32_t)(((uint32_t)(x))<<FCPIT_MIER_TIE2_SHIFT))&FCPIT_MIER_TIE2_MASK)
#define FCPIT_MIER_TIE1_MASK           0x2u
#define FCPIT_MIER_TIE1_SHIFT          1u
#define FCPIT_MIER_TIE1_WIDTH          1u
#define FCPIT_MIER_TIE1(x)             (((uint32_t)(((uint32_t)(x))<<FCPIT_MIER_TIE1_SHIFT))&FCPIT_MIER_TIE1_MASK)
#define FCPIT_MIER_TIE0_MASK           0x1u
#define FCPIT_MIER_TIE0_SHIFT          0u
#define FCPIT_MIER_TIE0_WIDTH          1u
#define FCPIT_MIER_TIE0(x)             (((uint32_t)(((uint32_t)(x))<<FCPIT_MIER_TIE0_SHIFT))&FCPIT_MIER_TIE0_MASK)
/* MIER Reg Mask */
#define FCPIT_MIER_MASK                0x0000000Fu

/* SETTEN Bit Fields */
#define FCPIT_SETTEN_SET_T_EN_3_MASK   0x8u
#define FCPIT_SETTEN_SET_T_EN_3_SHIFT  3u
#define FCPIT_SETTEN_SET_T_EN_3_WIDTH  1u
#define FCPIT_SETTEN_SET_T_EN_3(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_SETTEN_SET_T_EN_3_SHIFT))&FCPIT_SETTEN_SET_T_EN_3_MASK)
#define FCPIT_SETTEN_SET_T_EN_2_MASK   0x4u
#define FCPIT_SETTEN_SET_T_EN_2_SHIFT  2u
#define FCPIT_SETTEN_SET_T_EN_2_WIDTH  1u
#define FCPIT_SETTEN_SET_T_EN_2(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_SETTEN_SET_T_EN_2_SHIFT))&FCPIT_SETTEN_SET_T_EN_2_MASK)
#define FCPIT_SETTEN_SET_T_EN_1_MASK   0x2u
#define FCPIT_SETTEN_SET_T_EN_1_SHIFT  1u
#define FCPIT_SETTEN_SET_T_EN_1_WIDTH  1u
#define FCPIT_SETTEN_SET_T_EN_1(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_SETTEN_SET_T_EN_1_SHIFT))&FCPIT_SETTEN_SET_T_EN_1_MASK)
#define FCPIT_SETTEN_SET_T_EN_0_MASK   0x1u
#define FCPIT_SETTEN_SET_T_EN_0_SHIFT  0u
#define FCPIT_SETTEN_SET_T_EN_0_WIDTH  1u
#define FCPIT_SETTEN_SET_T_EN_0(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_SETTEN_SET_T_EN_0_SHIFT))&FCPIT_SETTEN_SET_T_EN_0_MASK)
/* SETTEN Reg Mask */
#define FCPIT_SETTEN_MASK              0x0000000Fu

/* CLRTEN Bit Fields */
#define FCPIT_CLRTEN_CLR_T_EN_3_MASK   0x8u
#define FCPIT_CLRTEN_CLR_T_EN_3_SHIFT  3u
#define FCPIT_CLRTEN_CLR_T_EN_3_WIDTH  1u
#define FCPIT_CLRTEN_CLR_T_EN_3(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_CLRTEN_CLR_T_EN_3_SHIFT))&FCPIT_CLRTEN_CLR_T_EN_3_MASK)
#define FCPIT_CLRTEN_CLR_T_EN_2_MASK   0x4u
#define FCPIT_CLRTEN_CLR_T_EN_2_SHIFT  2u
#define FCPIT_CLRTEN_CLR_T_EN_2_WIDTH  1u
#define FCPIT_CLRTEN_CLR_T_EN_2(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_CLRTEN_CLR_T_EN_2_SHIFT))&FCPIT_CLRTEN_CLR_T_EN_2_MASK)
#define FCPIT_CLRTEN_CLR_T_EN_1_MASK   0x2u
#define FCPIT_CLRTEN_CLR_T_EN_1_SHIFT  1u
#define FCPIT_CLRTEN_CLR_T_EN_1_WIDTH  1u
#define FCPIT_CLRTEN_CLR_T_EN_1(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_CLRTEN_CLR_T_EN_1_SHIFT))&FCPIT_CLRTEN_CLR_T_EN_1_MASK)
#define FCPIT_CLRTEN_CLR_T_EN_0_MASK   0x1u
#define FCPIT_CLRTEN_CLR_T_EN_0_SHIFT  0u
#define FCPIT_CLRTEN_CLR_T_EN_0_WIDTH  1u
#define FCPIT_CLRTEN_CLR_T_EN_0(x)     (((uint32_t)(((uint32_t)(x))<<FCPIT_CLRTEN_CLR_T_EN_0_SHIFT))&FCPIT_CLRTEN_CLR_T_EN_0_MASK)
/* CLRTEN Reg Mask */
#define FCPIT_CLRTEN_MASK              0x0000000Fu

/* TVAL Bit Fields */
#define FCPIT_TVAL_TMR_VAL_MASK        0xFFFFFFFFu
#define FCPIT_TVAL_TMR_VAL_SHIFT       0u
#define FCPIT_TVAL_TMR_VAL_WIDTH       32u
#define FCPIT_TVAL_TMR_VAL(x)          (((uint32_t)(((uint32_t)(x))<<FCPIT_TVAL_TMR_VAL_SHIFT))&FCPIT_TVAL_TMR_VAL_MASK)
/* TVAL0 Reg Mask */
#define FCPIT_TVAL_MASK                0xFFFFFFFFu

/* CVAL Bit Fields  This register only available on FC4150F1M_B*/
#define FCPIT_CVAL_TMR_VAL_MASK        0xFFFFFFFFu
#define FCPIT_CVAL_TMR_VAL_SHIFT       0u
#define FCPIT_CVAL_TMR_VAL_WIDTH       32u
#define FCPIT_CVAL_TMR_VAL(x)          (((uint32_t)(((uint32_t)(x))<<FCPIT_CVAL_TMR_VAL_SHIFT))&FCPIT_CVAL_TMR_VAL_MASK)
/* TVAL0 Reg Mask */
#define FCPIT_CVAL_MASK                0xFFFFFFFFu

/* TCTRL Bit Fields */
#define FCPIT_TCTRL_TRG_SEL_MASK       0xF000000u
#define FCPIT_TCTRL_TRG_SEL_SHIFT      24u
#define FCPIT_TCTRL_TRG_SEL_WIDTH      4u
#define FCPIT_TCTRL_TRG_SEL(x)         (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_TRG_SEL_SHIFT))&FCPIT_TCTRL_TRG_SEL_MASK)
#define FCPIT_TCTRL_TRG_SRC_MASK       0x800000u
#define FCPIT_TCTRL_TRG_SRC_SHIFT      23u
#define FCPIT_TCTRL_TRG_SRC_WIDTH      1u
#define FCPIT_TCTRL_TRG_SRC(x)         (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_TRG_SRC_SHIFT))&FCPIT_TCTRL_TRG_SRC_MASK)
#define FCPIT_TCTRL_TROT_MASK          0x40000u
#define FCPIT_TCTRL_TROT_SHIFT         18u
#define FCPIT_TCTRL_TROT_WIDTH         1u
#define FCPIT_TCTRL_TROT(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_TROT_SHIFT))&FCPIT_TCTRL_TROT_MASK)
#define FCPIT_TCTRL_TSOI_MASK          0x20000u
#define FCPIT_TCTRL_TSOI_SHIFT         17u
#define FCPIT_TCTRL_TSOI_WIDTH         1u
#define FCPIT_TCTRL_TSOI(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_TSOI_SHIFT))&FCPIT_TCTRL_TSOI_MASK)
#define FCPIT_TCTRL_TSOT_MASK          0x10000u
#define FCPIT_TCTRL_TSOT_SHIFT         16u
#define FCPIT_TCTRL_TSOT_WIDTH         1u
#define FCPIT_TCTRL_TSOT(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_TSOT_SHIFT))&FCPIT_TCTRL_TSOT_MASK)
#define FCPIT_TCTRL_MODE_MASK          0xCu
#define FCPIT_TCTRL_MODE_SHIFT         2u
#define FCPIT_TCTRL_MODE_WIDTH         2u
#define FCPIT_TCTRL_MODE(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_MODE_SHIFT))&FCPIT_TCTRL_MODE_MASK)
#define FCPIT_TCTRL_CHAIN_MASK         0x2u
#define FCPIT_TCTRL_CHAIN_SHIFT        1u
#define FCPIT_TCTRL_CHAIN_WIDTH        1u
#define FCPIT_TCTRL_CHAIN(x)           (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_CHAIN_SHIFT))&FCPIT_TCTRL_CHAIN_MASK)
#define FCPIT_TCTRL_T_EN_MASK          0x1u
#define FCPIT_TCTRL_T_EN_SHIFT         0u
#define FCPIT_TCTRL_T_EN_WIDTH         1u
#define FCPIT_TCTRL_T_EN(x)            (((uint32_t)(((uint32_t)(x))<<FCPIT_TCTRL_T_EN_SHIFT))&FCPIT_TCTRL_T_EN_MASK)
/* TCTRL0 Reg Mask */
#define FCPIT_TCTRL_MASK               0x0F87000Fu
/**
 * @}
 */ /* end of group FCPIT_Register_Masks */
/**
 * @}
 */ /* end of group FCPIT_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
