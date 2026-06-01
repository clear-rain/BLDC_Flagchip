#ifndef _MODULE_CCU_KJO_Ufdi41_REGS_H_
#define _MODULE_CCU_KJO_Ufdi41_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- CCU Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup CCU_Peripheral_Access_Layer CCU Peripheral Access Layer
 * @{
 */
/** CCU - Size of Registers Arrays */
/** CCU - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL                          ; /* Cache Control Register, offset: 0x0 */
  __IO uint32_t CLCR                          ;
  __IO uint32_t CSAR                          ;

} CCU_Type, *CCU_MemMapPtr;


/* ----------------------------------------------------------------------------
   -- CCU Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup CCU_Register_Masks CCU Register Masks
 * @{
 */
 
/* CTRL Bit Fields */
#define CCU_CTRL_CC_MASK               0xFF000000u
#define CCU_CTRL_CC_SHIFT              24u
#define CCU_CTRL_CC_WIDTH              8u
#define CCU_CTRL_CC(x)                 (((uint32_t)(((uint32_t)(x))<<CCU_CTRL_CC_SHIFT))&CCU_CTRL_CC_MASK)
#define CCU_CTRL_CE_MASK               0x1u
#define CCU_CTRL_CE_SHIFT              0u
#define CCU_CTRL_CE_WIDTH              1u
#define CCU_CTRL_CE(x)                 (((uint32_t)(((uint32_t)(x))<<CCU_CTRL_CE_SHIFT))&CCU_CTRL_CE_MASK)
/* CTRL Reg Mask */
#define CCU_CTRL_MASK                  0xFF000001u

#define CSAR_PHYADDR_MASK_U32          0xFFFFFFFCu

#define CSAR_LGO_MASK_U32              0x00000001u
/**
 * @}
 */ /* end of group CCU_Register_Masks */
/**
 * @}
 */ /* end of group CCU_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
