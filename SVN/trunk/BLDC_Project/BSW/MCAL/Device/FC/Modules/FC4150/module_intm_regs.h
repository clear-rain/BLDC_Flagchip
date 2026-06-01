#ifndef _MODULE_INTM_KJO_Ufdi19_REGS_H_
#define _MODULE_INTM_KJO_Ufdi19_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- INTM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup INTM_Peripheral_Access_Layer INTM Peripheral Access Layer
 * @{
 */
/** INTM - Size of Registers Arrays */
/** INTM - Register Layout Typedef */
typedef struct {
  __IO uint32_t ER                            ; /* INTM Enable Register, offset: 0x0 */
  __IO uint32_t IACKR                         ; /* INTM Interrupt Acknowledge Register, offset: 0x4 */
  __IO uint32_t IRQSELR0                      ; /* INTM Interrupt Request Select Register, offset: 0x8 */
  __IO uint32_t LATR0                         ; /* INTM Latency Register, offset: 0xc */
  __IO uint32_t TMR0                          ; /* INTM Timer Register, offset: 0x10 */
  __I  uint32_t SR0                           ; /* INTM Status Register, offset: 0x14 */
  __IO uint32_t IRQSELR1                      ; /* INTM Interrupt Request Select Register, offset: 0x18 */
  __IO uint32_t LATR1                         ; /* INTM Latency Register, offset: 0x1c */
  __IO uint32_t TMR1                          ; /* INTM Timer Register, offset: 0x20 */
  __I  uint32_t SR1                           ; /* INTM Status Register, offset: 0x24 */
} INTM_Type, *INTM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- INTM Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup INTM_Register_Masks INTM Register Masks
 * @{
 */
 
/* ER Bit Fields */
#define INTM_ER_EN_MASK                0x1u
#define INTM_ER_EN_SHIFT               0u
#define INTM_ER_EN_WIDTH               1u
#define INTM_ER_EN(x)                  (((uint32_t)(((uint32_t)(x))<<INTM_ER_EN_SHIFT))&INTM_ER_EN_MASK)
/* ER Reg Mask */
#define INTM_ER_MASK                   0x00000001u
/* IACKR Bit Fields */
#define INTM_IACKR_IRQ_MASK            0x3FFu
#define INTM_IACKR_IRQ_SHIFT           0u
#define INTM_IACKR_IRQ_WIDTH           10u
#define INTM_IACKR_IRQ(x)              (((uint32_t)(((uint32_t)(x))<<INTM_IACKR_IRQ_SHIFT))&INTM_IACKR_IRQ_MASK)
/* IACKR Reg Mask */
#define INTM_IACKR_MASK                0x000003FFu
/* IRQSELR Bit Fields */
#define INTM_IRQSELR_RSTE_MASK         0x80000000u
#define INTM_IRQSELR_RSTE_SHIFT        31u
#define INTM_IRQSELR_RSTE_WIDTH        1u
#define INTM_IRQSELR_RSTE(x)           (((uint32_t)(((uint32_t)(x))<<INTM_IRQSELR_RSTE_SHIFT))&INTM_IRQSELR_RSTE_MASK)
#define INTM_IRQSELR_INTE_MASK         0x40000000u
#define INTM_IRQSELR_INTE_SHIFT        30u
#define INTM_IRQSELR_INTE_WIDTH        1u
#define INTM_IRQSELR_INTE(x)           (((uint32_t)(((uint32_t)(x))<<INTM_IRQSELR_INTE_SHIFT))&INTM_IRQSELR_INTE_MASK)
#define INTM_IRQSELR_IACTE_MASK        0x20000000u
#define INTM_IRQSELR_IACTE_SHIFT       29u
#define INTM_IRQSELR_IACTE_WIDTH       1u
#define INTM_IRQSELR_IACTE(x)          (((uint32_t)(((uint32_t)(x))<<INTM_IRQSELR_IACTE_SHIFT))&INTM_IRQSELR_IACTE_MASK)
#define INTM_IRQSELR_IACTST_MASK       0x10000u
#define INTM_IRQSELR_IACTST_SHIFT      16u
#define INTM_IRQSELR_IACTST_WIDTH      1u
#define INTM_IRQSELR_IACTST(x)         (((uint32_t)(((uint32_t)(x))<<INTM_IRQSELR_IACTST_SHIFT))&INTM_IRQSELR_IACTST_MASK)
#define INTM_IRQSELR_IRQ_MASK          0x3FFu
#define INTM_IRQSELR_IRQ_SHIFT         0u
#define INTM_IRQSELR_IRQ_WIDTH         10u
#define INTM_IRQSELR_IRQ(x)            (((uint32_t)(((uint32_t)(x))<<INTM_IRQSELR_IRQ_SHIFT))&INTM_IRQSELR_IRQ_MASK)
/* IRQSELR0 Reg Mask */
#define INTM_IRQSELR_MASK              0xE00103FFu
/* LATR Bit Fields */
#define INTM_LATR_LAT_MASK             0xFFFFFFu
#define INTM_LATR_LAT_SHIFT            0u
#define INTM_LATR_LAT_WIDTH            24u
#define INTM_LATR_LAT(x)               (((uint32_t)(((uint32_t)(x))<<INTM_LATR_LAT_SHIFT))&INTM_LATR_LAT_MASK)
/* LATR0 Reg Mask */
#define INTM_LATR_MASK                 0x00FFFFFFu
/* TMR Bit Fields */
#define INTM_TMR_TIMER_MASK            0xFFFFFFu
#define INTM_TMR_TIMER_SHIFT           0u
#define INTM_TMR_TIMER_WIDTH           24u
#define INTM_TMR_TIMER(x)              (((uint32_t)(((uint32_t)(x))<<INTM_TMR_TIMER_SHIFT))&INTM_TMR_TIMER_MASK)
/* TMR0 Reg Mask */
#define INTM_TMR_MASK                  0x00FFFFFFu
/* SR Bit Fields */
#define INTM_SR_STATUS_MASK            0x1u
#define INTM_SR_STATUS_SHIFT           0u
#define INTM_SR_STATUS_WIDTH           1u
#define INTM_SR_STATUS(x)              (((uint32_t)(((uint32_t)(x))<<INTM_SR_STATUS_SHIFT))&INTM_SR_STATUS_MASK)
/* SR0 Reg Mask */
#define INTM_SR_MASK                   0x00000001u
/**
 * @}
 */ /* end of group INTM_Register_Masks */
/**
 * @}
 */ /* end of group INTM_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
