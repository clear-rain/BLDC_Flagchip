#ifndef _MODULE_TRGSEL_KJO_Ufdi36_REGS_H_
#define _MODULE_TRGSEL_KJO_Ufdi36_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- TRGSEL Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup TRGSEL_Peripheral_Access_Layer TRGSEL Peripheral Access Layer
 * @{
 */
/** TRGSEL - Size of Registers Arrays */
/** TRGSEL - Register Layout Typedef */
#define TRGSEL_OUT_SEL_COUNT 16
typedef struct {
  __IO uint32_t OUT_SEL[TRGSEL_OUT_SEL_COUNT] ; /* OUT SEL for N, offset: 0x0 */
} TRGSEL_Type, *TRGSEL_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- TRGSEL Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup TRGSEL_Register_Masks TRGSEL Register Masks
 * @{
 */
 
/* OUT_SEL Bit Fields */
#define TRGSEL_OUT_SEL_LOCK_MASK       0x80000000u
#define TRGSEL_OUT_SEL_LOCK_SHIFT      31u
#define TRGSEL_OUT_SEL_LOCK_WIDTH      1u
#define TRGSEL_OUT_SEL_LOCK(x)         (((uint32_t)(((uint32_t)(x))<<TRGSEL_OUT_SEL_LOCK_SHIFT))&TRGSEL_OUT_SEL_LOCK_MASK)
#define TRGSEL_OUT_SEL_SEL_3_MASK      0x7F000000u
#define TRGSEL_OUT_SEL_SEL_3_SHIFT     24u
#define TRGSEL_OUT_SEL_SEL_3_WIDTH     7u
#define TRGSEL_OUT_SEL_SEL_3(x)        (((uint32_t)(((uint32_t)(x))<<TRGSEL_OUT_SEL_SEL_3_SHIFT))&TRGSEL_OUT_SEL_SEL_3_MASK)
#define TRGSEL_OUT_SEL_SEL_2_MASK      0xFF0000u
#define TRGSEL_OUT_SEL_SEL_2_SHIFT     16u
#define TRGSEL_OUT_SEL_SEL_2_WIDTH     8u
#define TRGSEL_OUT_SEL_SEL_2(x)        (((uint32_t)(((uint32_t)(x))<<TRGSEL_OUT_SEL_SEL_2_SHIFT))&TRGSEL_OUT_SEL_SEL_2_MASK)
#define TRGSEL_OUT_SEL_SEL_1_MASK      0xFF00u
#define TRGSEL_OUT_SEL_SEL_1_SHIFT     8u
#define TRGSEL_OUT_SEL_SEL_1_WIDTH     8u
#define TRGSEL_OUT_SEL_SEL_1(x)        (((uint32_t)(((uint32_t)(x))<<TRGSEL_OUT_SEL_SEL_1_SHIFT))&TRGSEL_OUT_SEL_SEL_1_MASK)
#define TRGSEL_OUT_SEL_SEL_0_MASK      0xFFu
#define TRGSEL_OUT_SEL_SEL_0_SHIFT     0u
#define TRGSEL_OUT_SEL_SEL_0_WIDTH     8u
#define TRGSEL_OUT_SEL_SEL_0(x)        (((uint32_t)(((uint32_t)(x))<<TRGSEL_OUT_SEL_SEL_0_SHIFT))&TRGSEL_OUT_SEL_SEL_0_MASK)
/**
 * @}
 */ /* end of group TRGSEL_Register_Masks */
/**
 * @}
 */ /* end of group TRGSEL_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
