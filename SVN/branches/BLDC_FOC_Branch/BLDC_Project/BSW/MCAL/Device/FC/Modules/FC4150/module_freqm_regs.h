#ifndef _MODULE_FREQM_KJO_Ufdi38_REGS_H_
#define _MODULE_FREQM_KJO_Ufdi38_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* ----------------------------------------------------------------------------
   -- FREQM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FREQM_Peripheral_Access_Layer FREQM Peripheral Access Layer
 * @{
 */

/** FREQM - Size of Registers Arrays */

/** FREQM - Register Layout Typedef */

typedef struct {

  __IO uint32_t CTRL                          ; /* CTRL, offset: 0x0 */
  __IO uint32_t MES_CNT                       ; /* MES_CNT, offset: 0x4 */
  __O  uint32_t REF_CNT                       ; /* REF_CNT, offset: 0x8 */
  __IO uint32_t MES_LENGTH                    ; /* MES_LENGTH, offset: 0xC */
  __IO uint32_t REF_TIMEOUT                   ; /* REF_TIMEOUT, offset: 0x10 */
  __IO uint32_t CNT_STATUS                    ; /* CNT_STATUS, offset: 0x14 */
       uint32_t RESERVED_0;
  __I  uint32_t REF_CNT_SAVE                  ; /* REF_CNT_SAVE, offset: 0x1C */

} FREQM_Type, *FREQM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FREQM Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup FREQM_Register_Masks FREQM Register Masks
 * @{
 */

/* CTRL Bit Fields */
#define FREQM_CTRL_CNT_EVENT_IE_MASK   0x4000u
#define FREQM_CTRL_CNT_EVENT_IE_SHIFT  14u
#define FREQM_CTRL_CNT_EVENT_IE_WIDTH  1u
#define FREQM_CTRL_CNT_EVENT_IE(x)     (((uint32_t)(((uint32_t)(x))<<FREQM_CTRL_CNT_EVENT_IE_SHIFT))&FREQM_CTRL_CNT_EVENT_IE_MASK)
#define FREQM_CTRL_MES_CLK_SEL_MASK    0x3F00u
#define FREQM_CTRL_MES_CLK_SEL_SHIFT   8u
#define FREQM_CTRL_MES_CLK_SEL_WIDTH   6u
#define FREQM_CTRL_MES_CLK_SEL(x)      (((uint32_t)(((uint32_t)(x))<<FREQM_CTRL_MES_CLK_SEL_SHIFT))&FREQM_CTRL_MES_CLK_SEL_MASK)
#define FREQM_CTRL_MES_CLK_PREDIV_MASK 0xFFu
#define FREQM_CTRL_MES_CLK_PREDIV_SHIFT 0u
#define FREQM_CTRL_MES_CLK_PREDIV_WIDTH 8u
#define FREQM_CTRL_MES_CLK_PREDIV(x)   (((uint32_t)(((uint32_t)(x))<<FREQM_CTRL_MES_CLK_PREDIV_SHIFT))&FREQM_CTRL_MES_CLK_PREDIV_MASK)
/* CTRL Reg Mask */
#define FREQM_CTRL_MASK                0x00007FFFu

/* MES_CNT Bit Fields */
#define FREQM_MES_CNT_MES_CNT_MASK     0xFFFFFFFFu
#define FREQM_MES_CNT_MES_CNT_SHIFT    0u
#define FREQM_MES_CNT_MES_CNT_WIDTH    32u
#define FREQM_MES_CNT_MES_CNT(x)       (((uint32_t)(((uint32_t)(x))<<FREQM_MES_CNT_MES_CNT_SHIFT))&FREQM_MES_CNT_MES_CNT_MASK)
/* MES_CNT Reg Mask */
#define FREQM_MES_CNT_MASK             0xFFFFFFFFu

/* REF_CNT Bit Fields */
#define FREQM_REF_CNT_REF_CNT_MASK     0xFFFFFFFFu
#define FREQM_REF_CNT_REF_CNT_SHIFT    0u
#define FREQM_REF_CNT_REF_CNT_WIDTH    32u
#define FREQM_REF_CNT_REF_CNT(x)       (((uint32_t)(((uint32_t)(x))<<FREQM_REF_CNT_REF_CNT_SHIFT))&FREQM_REF_CNT_REF_CNT_MASK)
/* REF_CNT Reg Mask */
#define FREQM_REF_CNT_MASK             0xFFFFFFFFu

/* MES_LENGTH Bit Fields */
#define FREQM_MES_LENGTH_MES_LENGTH_MASK 0xFFFFFFFFu
#define FREQM_MES_LENGTH_MES_LENGTH_SHIFT 0u
#define FREQM_MES_LENGTH_MES_LENGTH_WIDTH 32u
#define FREQM_MES_LENGTH_MES_LENGTH(x) (((uint32_t)(((uint32_t)(x))<<FREQM_MES_LENGTH_MES_LENGTH_SHIFT))&FREQM_MES_LENGTH_MES_LENGTH_MASK)
/* MES_LENGTH Reg Mask */
#define FREQM_MES_LENGTH_MASK          0xFFFFFFFFu

/* REF_TIMEOUT Bit Fields */
#define FREQM_REF_TIMEOUT_REF_TIMEOUT_MASK 0xFFFFFFFFu
#define FREQM_REF_TIMEOUT_REF_TIMEOUT_SHIFT 0u
#define FREQM_REF_TIMEOUT_REF_TIMEOUT_WIDTH 32u
#define FREQM_REF_TIMEOUT_REF_TIMEOUT(x) (((uint32_t)(((uint32_t)(x))<<FREQM_REF_TIMEOUT_REF_TIMEOUT_SHIFT))&FREQM_REF_TIMEOUT_REF_TIMEOUT_MASK)
/* REF_TIMEOUT Reg Mask */
#define FREQM_REF_TIMEOUT_MASK         0xFFFFFFFFu

/* CNT_STATUS Bit Fields */
#define FREQM_CNT_STATUS_CNT_EVENT_MASK 0x80u
#define FREQM_CNT_STATUS_CNT_EVENT_SHIFT 7u
#define FREQM_CNT_STATUS_CNT_EVENT_WIDTH 1u
#define FREQM_CNT_STATUS_CNT_EVENT(x)  (((uint32_t)(((uint32_t)(x))<<FREQM_CNT_STATUS_CNT_EVENT_SHIFT))&FREQM_CNT_STATUS_CNT_EVENT_MASK)
#define FREQM_CNT_STATUS_MES_CNT_START_MASK 0x4u
#define FREQM_CNT_STATUS_MES_CNT_START_SHIFT 2u
#define FREQM_CNT_STATUS_MES_CNT_START_WIDTH 1u
#define FREQM_CNT_STATUS_MES_CNT_START(x) (((uint32_t)(((uint32_t)(x))<<FREQM_CNT_STATUS_MES_CNT_START_SHIFT))&FREQM_CNT_STATUS_MES_CNT_START_MASK)
#define FREQM_CNT_STATUS_MES_CNT_STOP_MASK 0x2u
#define FREQM_CNT_STATUS_MES_CNT_STOP_SHIFT 1u
#define FREQM_CNT_STATUS_MES_CNT_STOP_WIDTH 1u
#define FREQM_CNT_STATUS_MES_CNT_STOP(x) (((uint32_t)(((uint32_t)(x))<<FREQM_CNT_STATUS_MES_CNT_STOP_SHIFT))&FREQM_CNT_STATUS_MES_CNT_STOP_MASK)
#define FREQM_CNT_STATUS_REF_CNT_STOP_MASK 0x1u
#define FREQM_CNT_STATUS_REF_CNT_STOP_SHIFT 0u
#define FREQM_CNT_STATUS_REF_CNT_STOP_WIDTH 1u
#define FREQM_CNT_STATUS_REF_CNT_STOP(x) (((uint32_t)(((uint32_t)(x))<<FREQM_CNT_STATUS_REF_CNT_STOP_SHIFT))&FREQM_CNT_STATUS_REF_CNT_STOP_MASK)
/* CNT_STATUS Reg Mask */
#define FREQM_CNT_STATUS_MASK          0x00000087u

/* REF_CNT_SAVE Bit Fields */
#define FREQM_REF_CNT_SAVE_REF_CNT_SAVE_MASK 0xFFFFFFFFu
#define FREQM_REF_CNT_SAVE_REF_CNT_SAVE_SHIFT 0u
#define FREQM_REF_CNT_SAVE_REF_CNT_SAVE_WIDTH 32u
#define FREQM_REF_CNT_SAVE_REF_CNT_SAVE(x) (((uint32_t)(((uint32_t)(x))<<FREQM_REF_CNT_SAVE_REF_CNT_SAVE_SHIFT))&FREQM_REF_CNT_SAVE_REF_CNT_SAVE_MASK)
/* REF_CNT_SAVE Reg Mask */
#define FREQM_REF_CNT_SAVE_MASK        0xFFFFFFFFu


/**
 * @}
 */ /* end of group FREQM_Register_Masks */

/**
 * @}
 */ /* end of group FREQM_Peripheral_Access_Layer */

#ifdef __cplusplus
}
#endif

#endif /* _MODULE_FREQM_KJO_Ufdi38_REGS_H_ */
