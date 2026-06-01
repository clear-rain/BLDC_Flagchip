#ifndef _MODULE_AONTIMER_KJO_Ufdi2_REGS_H_
#define _MODULE_AONTIMER_KJO_Ufdi2_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------
   -- AONTIMER Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup AONTIMER_Peripheral_Access_Layer AONTIMER Peripheral Access Layer
 * @{
 */
/** AONTIMER - Size of Registers Arrays */
/** AONTIMER - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSR                           ; /* Always On Timer Control Status Register, offset: 0x0 */
  __IO uint32_t PSR                           ; /* Always On Timer Prescale Register, offset: 0x4 */
  __IO uint32_t CMR                           ; /* Always On Timer Compare Register, offset: 0x8 */
  __IO uint32_t CNR                           ; /* Always On Timer Counter Register, offset: 0xC */
} AONTIMER_Type, *AONTIMER_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- AONTIMER Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup AONTIMER_Register_Masks AONTIMER Register Masks
 * @{
 */
 
/* CSR Bit Fields */
#define AONTIMER_CSR_DBGEN_MASK        0x200u
#define AONTIMER_CSR_DBGEN_SHIFT       9u
#define AONTIMER_CSR_DBGEN_WIDTH       1u
#define AONTIMER_CSR_DBGEN(x)          (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_DBGEN_SHIFT))&AONTIMER_CSR_DBGEN_MASK)
#define AONTIMER_CSR_TDRE_MASK         0x100u
#define AONTIMER_CSR_TDRE_SHIFT        8u
#define AONTIMER_CSR_TDRE_WIDTH        1u
#define AONTIMER_CSR_TDRE(x)           (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TDRE_SHIFT))&AONTIMER_CSR_TDRE_MASK)
#define AONTIMER_CSR_TCF_MASK          0x80u
#define AONTIMER_CSR_TCF_SHIFT         7u
#define AONTIMER_CSR_TCF_WIDTH         1u
#define AONTIMER_CSR_TCF(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TCF_SHIFT))&AONTIMER_CSR_TCF_MASK)
#define AONTIMER_CSR_TIE_MASK          0x40u
#define AONTIMER_CSR_TIE_SHIFT         6u
#define AONTIMER_CSR_TIE_WIDTH         1u
#define AONTIMER_CSR_TIE(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TIE_SHIFT))&AONTIMER_CSR_TIE_MASK)
#define AONTIMER_CSR_TPS_MASK          0x30u
#define AONTIMER_CSR_TPS_SHIFT         4u
#define AONTIMER_CSR_TPS_WIDTH         2u
#define AONTIMER_CSR_TPS(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TPS_SHIFT))&AONTIMER_CSR_TPS_MASK)
#define AONTIMER_CSR_TPP_MASK          0x8u
#define AONTIMER_CSR_TPP_SHIFT         3u
#define AONTIMER_CSR_TPP_WIDTH         1u
#define AONTIMER_CSR_TPP(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TPP_SHIFT))&AONTIMER_CSR_TPP_MASK)
#define AONTIMER_CSR_TFC_MASK          0x4u
#define AONTIMER_CSR_TFC_SHIFT         2u
#define AONTIMER_CSR_TFC_WIDTH         1u
#define AONTIMER_CSR_TFC(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TFC_SHIFT))&AONTIMER_CSR_TFC_MASK)
#define AONTIMER_CSR_TMS_MASK          0x2u
#define AONTIMER_CSR_TMS_SHIFT         1u
#define AONTIMER_CSR_TMS_WIDTH         1u
#define AONTIMER_CSR_TMS(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TMS_SHIFT))&AONTIMER_CSR_TMS_MASK)
#define AONTIMER_CSR_TEN_MASK          0x1u
#define AONTIMER_CSR_TEN_SHIFT         0u
#define AONTIMER_CSR_TEN_WIDTH         1u
#define AONTIMER_CSR_TEN(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_CSR_TEN_SHIFT))&AONTIMER_CSR_TEN_MASK)
/* CSR Reg Mask */
#define AONTIMER_CSR_MASK              0x000003FFu
/* PSR Bit Fields */
#define AONTIMER_PSR_PRESCALE_MASK     0x78u
#define AONTIMER_PSR_PRESCALE_SHIFT    3u
#define AONTIMER_PSR_PRESCALE_WIDTH    4u
#define AONTIMER_PSR_PRESCALE(x)       (((uint32_t)(((uint32_t)(x))<<AONTIMER_PSR_PRESCALE_SHIFT))&AONTIMER_PSR_PRESCALE_MASK)
#define AONTIMER_PSR_PBYP_MASK         0x4u
#define AONTIMER_PSR_PBYP_SHIFT        2u
#define AONTIMER_PSR_PBYP_WIDTH        1u
#define AONTIMER_PSR_PBYP(x)           (((uint32_t)(((uint32_t)(x))<<AONTIMER_PSR_PBYP_SHIFT))&AONTIMER_PSR_PBYP_MASK)
#define AONTIMER_PSR_PCS_MASK          0x3u
#define AONTIMER_PSR_PCS_SHIFT         0u
#define AONTIMER_PSR_PCS_WIDTH         2u
#define AONTIMER_PSR_PCS(x)            (((uint32_t)(((uint32_t)(x))<<AONTIMER_PSR_PCS_SHIFT))&AONTIMER_PSR_PCS_MASK)
/* PSR Reg Mask */
#define AONTIMER_PSR_MASK              0x0000007Fu
/* CMR Bit Fields */
#define AONTIMER_CMR_COMPARE_MASK      0xFFFFu
#define AONTIMER_CMR_COMPARE_SHIFT     0u
#define AONTIMER_CMR_COMPARE_WIDTH     16u
#define AONTIMER_CMR_COMPARE(x)        (((uint32_t)(((uint32_t)(x))<<AONTIMER_CMR_COMPARE_SHIFT))&AONTIMER_CMR_COMPARE_MASK)
/* CMR Reg Mask */
#define AONTIMER_CMR_MASK              0x0000FFFFu
/* CNR Bit Fields */
#define AONTIMER_CNR_COUNTER_MASK      0xFFFFu
#define AONTIMER_CNR_COUNTER_SHIFT     0u
#define AONTIMER_CNR_COUNTER_WIDTH     16u
#define AONTIMER_CNR_COUNTER(x)        (((uint32_t)(((uint32_t)(x))<<AONTIMER_CNR_COUNTER_SHIFT))&AONTIMER_CNR_COUNTER_MASK)
/* CNR Reg Mask */
#define AONTIMER_CNR_MASK              0x0000FFFFu
/**
 * @}
 */ /* end of group AONTIMER_Register_Masks */
/**
 * @}
 */ /* end of group AONTIMER_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif


#endif
