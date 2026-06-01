#ifndef _MODULE_TSTMP_KJO_Ufdi10_REGS_H_
#define _MODULE_TSTMP_KJO_Ufdi10_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- TSTMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup TSTMP_Peripheral_Access_Layer TSTMP Peripheral Access Layer
 * @{
 */
/** TSTMP - Size of Registers Arrays */
/** TSTMP - Register Layout Typedef */
typedef struct {
  __I  uint32_t VALL                          ; /* Low Value, offset: 0x0 */
  __I  uint32_t VALH                          ; /* High Value, offset: 0x4 */
  __IO uint32_t MOD_INTEN                     ; /* Modulate Interrupt Enable, offset: 0x8 */
  __IO uint32_t MOD_STATUS                    ; /* Modulate Status, offset: 0xC */
  __IO uint32_t MOD0_SETVAL                   ; /* Modulate0 Set Value, offset: 0x10 */
  __IO uint32_t MOD1_SETVAL                   ; /* Modulate1 Set Value, offset: 0x14 */
  __IO uint32_t MOD2_SETVAL                   ; /* Modulate2 Set Value, offset: 0x18 */
  __IO uint32_t MOD3_SETVAL                   ; /* Modulate3 Set Value, offset: 0x1C */
} TSTMP_Type, *TSTMP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TSTMP Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup TSTMP_Register_Masks TSTMP Register Masks
 * @{
 */
 
/* VALL Bit Fields */
#define TSTMP_VALL_TVALL_MASK          0xFFFFFFFFu
#define TSTMP_VALL_TVALL_SHIFT         0u
#define TSTMP_VALL_TVALL_WIDTH         32u
#define TSTMP_VALL_TVALL(x)            (((uint32_t)(((uint32_t)(x))<<TSTMP_VALL_TVALL_SHIFT))&TSTMP_VALL_TVALL_MASK)
/* VALL Reg Mask */
#define TSTMP_VALL_MASK                0xFFFFFFFFu
/* VALH Bit Fields */
#define TSTMP_VALH_TVALH_MASK          0xFFFFFFu
#define TSTMP_VALH_TVALH_SHIFT         0u
#define TSTMP_VALH_TVALH_WIDTH         24u
#define TSTMP_VALH_TVALH(x)            (((uint32_t)(((uint32_t)(x))<<TSTMP_VALH_TVALH_SHIFT))&TSTMP_VALH_TVALH_MASK)
/* VALH Reg Mask */
#define TSTMP_VALH_MASK                0x00FFFFFFu
/* MOD_INTEN Bit Fields */
#define TSTMP_MOD_INTEN_MOD3_INTEN_MASK 0x8u
#define TSTMP_MOD_INTEN_MOD3_INTEN_SHIFT 3u
#define TSTMP_MOD_INTEN_MOD3_INTEN_WIDTH 1u
#define TSTMP_MOD_INTEN_MOD3_INTEN(x)  (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_INTEN_MOD3_INTEN_SHIFT))&TSTMP_MOD_INTEN_MOD3_INTEN_MASK)
#define TSTMP_MOD_INTEN_MOD2_INTEN_MASK 0x4u
#define TSTMP_MOD_INTEN_MOD2_INTEN_SHIFT 2u
#define TSTMP_MOD_INTEN_MOD2_INTEN_WIDTH 1u
#define TSTMP_MOD_INTEN_MOD2_INTEN(x)  (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_INTEN_MOD2_INTEN_SHIFT))&TSTMP_MOD_INTEN_MOD2_INTEN_MASK)
#define TSTMP_MOD_INTEN_MOD1_INTEN_MASK 0x2u
#define TSTMP_MOD_INTEN_MOD1_INTEN_SHIFT 1u
#define TSTMP_MOD_INTEN_MOD1_INTEN_WIDTH 1u
#define TSTMP_MOD_INTEN_MOD1_INTEN(x)  (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_INTEN_MOD1_INTEN_SHIFT))&TSTMP_MOD_INTEN_MOD1_INTEN_MASK)
#define TSTMP_MOD_INTEN_MOD0_INTEN_MASK 0x1u
#define TSTMP_MOD_INTEN_MOD0_INTEN_SHIFT 0u
#define TSTMP_MOD_INTEN_MOD0_INTEN_WIDTH 1u
#define TSTMP_MOD_INTEN_MOD0_INTEN(x)  (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_INTEN_MOD0_INTEN_SHIFT))&TSTMP_MOD_INTEN_MOD0_INTEN_MASK)
/* MOD_INTEN Reg Mask */
#define TSTMP_MOD_INTEN_MASK           0x0000000Fu
/* MOD_STATUS Bit Fields */
#define TSTMP_MOD_STATUS_MOD3_MATCH_MASK 0x8u
#define TSTMP_MOD_STATUS_MOD3_MATCH_SHIFT 3u
#define TSTMP_MOD_STATUS_MOD3_MATCH_WIDTH 1u
#define TSTMP_MOD_STATUS_MOD3_MATCH(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_STATUS_MOD3_MATCH_SHIFT))&TSTMP_MOD_STATUS_MOD3_MATCH_MASK)
#define TSTMP_MOD_STATUS_MOD2_MATCH_MASK 0x4u
#define TSTMP_MOD_STATUS_MOD2_MATCH_SHIFT 2u
#define TSTMP_MOD_STATUS_MOD2_MATCH_WIDTH 1u
#define TSTMP_MOD_STATUS_MOD2_MATCH(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_STATUS_MOD2_MATCH_SHIFT))&TSTMP_MOD_STATUS_MOD2_MATCH_MASK)
#define TSTMP_MOD_STATUS_MOD1_MATCH_MASK 0x2u
#define TSTMP_MOD_STATUS_MOD1_MATCH_SHIFT 1u
#define TSTMP_MOD_STATUS_MOD1_MATCH_WIDTH 1u
#define TSTMP_MOD_STATUS_MOD1_MATCH(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_STATUS_MOD1_MATCH_SHIFT))&TSTMP_MOD_STATUS_MOD1_MATCH_MASK)
#define TSTMP_MOD_STATUS_MOD0_MATCH_MASK 0x1u
#define TSTMP_MOD_STATUS_MOD0_MATCH_SHIFT 0u
#define TSTMP_MOD_STATUS_MOD0_MATCH_WIDTH 1u
#define TSTMP_MOD_STATUS_MOD0_MATCH(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD_STATUS_MOD0_MATCH_SHIFT))&TSTMP_MOD_STATUS_MOD0_MATCH_MASK)
/* MOD_STATUS Reg Mask */
#define TSTMP_MOD_STATUS_MASK          0x0000000Fu
/* MOD0_SETVAL Bit Fields */
#define TSTMP_MOD0_SETVAL_MOD0_SETVAL_MASK 0xFFFFFFFFu
#define TSTMP_MOD0_SETVAL_MOD0_SETVAL_SHIFT 0u
#define TSTMP_MOD0_SETVAL_MOD0_SETVAL_WIDTH 32u
#define TSTMP_MOD0_SETVAL_MOD0_SETVAL(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD0_SETVAL_MOD0_SETVAL_SHIFT))&TSTMP_MOD0_SETVAL_MOD0_SETVAL_MASK)
/* MOD0_SETVAL Reg Mask */
#define TSTMP_MOD0_SETVAL_MASK         0xFFFFFFFFu
/* MOD1_SETVAL Bit Fields */
#define TSTMP_MOD1_SETVAL_MOD1_SETVAL_MASK 0xFFFFFFFFu
#define TSTMP_MOD1_SETVAL_MOD1_SETVAL_SHIFT 0u
#define TSTMP_MOD1_SETVAL_MOD1_SETVAL_WIDTH 32u
#define TSTMP_MOD1_SETVAL_MOD1_SETVAL(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD1_SETVAL_MOD1_SETVAL_SHIFT))&TSTMP_MOD1_SETVAL_MOD1_SETVAL_MASK)
/* MOD1_SETVAL Reg Mask */
#define TSTMP_MOD1_SETVAL_MASK         0xFFFFFFFFu
/* MOD2_SETVAL Bit Fields */
#define TSTMP_MOD2_SETVAL_MOD2_SETVAL_MASK 0xFFFFFFFFu
#define TSTMP_MOD2_SETVAL_MOD2_SETVAL_SHIFT 0u
#define TSTMP_MOD2_SETVAL_MOD2_SETVAL_WIDTH 32u
#define TSTMP_MOD2_SETVAL_MOD2_SETVAL(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD2_SETVAL_MOD2_SETVAL_SHIFT))&TSTMP_MOD2_SETVAL_MOD2_SETVAL_MASK)
/* MOD2_SETVAL Reg Mask */
#define TSTMP_MOD2_SETVAL_MASK         0xFFFFFFFFu
/* MOD3_SETVAL Bit Fields */
#define TSTMP_MOD3_SETVAL_MOD3_SETVAL_MASK 0xFFFFFFFFu
#define TSTMP_MOD3_SETVAL_MOD3_SETVAL_SHIFT 0u
#define TSTMP_MOD3_SETVAL_MOD3_SETVAL_WIDTH 32u
#define TSTMP_MOD3_SETVAL_MOD3_SETVAL(x) (((uint32_t)(((uint32_t)(x))<<TSTMP_MOD3_SETVAL_MOD3_SETVAL_SHIFT))&TSTMP_MOD3_SETVAL_MOD3_SETVAL_MASK)
/* MOD3_SETVAL Reg Mask */
#define TSTMP_MOD3_SETVAL_MASK         0xFFFFFFFFu
/**
 * @}
 */ /* end of group TSTMP_Register_Masks */
/**
 * @}
 */ /* end of group TSTMP_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
