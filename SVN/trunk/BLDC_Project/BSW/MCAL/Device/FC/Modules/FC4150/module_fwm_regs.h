#ifndef _MODULE_FWM_KJO_Ufdi37_REGS_H_
#define _MODULE_FWM_KJO_Ufdi37_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- FWM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FWM_Peripheral_Access_Layer FWM Peripheral Access Layer
 * @{
 */
/** FWM - Size of Registers Arrays */
/** FWM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL                          ; /* Control Register, offset: 0x0 */
  __O  uint32_t SERV                          ; /* Service Register, offset: 0x4 */
  __IO uint32_t CMPL                          ; /* Compare Low Register, offset: 0x8 */
  __IO uint32_t CMPH                          ; /* Compare High Register, offset: 0x0C */
       uint8_t  RESERVED_0[4];
  __IO uint32_t CLKPRESCALER                  ; /* Clock Prescaler Register, offset: 0x14 */
} FWM_Type, *FWM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FWM Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FWM_Register_Masks FWM Register Masks
 * @{
 */
 
/* CTRL Bit Fields */
#define FWM_CTRL_INTEN_MASK            0x8u
#define FWM_CTRL_INTEN_SHIFT           3u
#define FWM_CTRL_INTEN_WIDTH           1u
#define FWM_CTRL_INTEN(x)              (((uint32_t)(((uint32_t)(x))<<FWM_CTRL_INTEN_SHIFT))&FWM_CTRL_INTEN_MASK)
#define FWM_CTRL_INEN_MASK             0x4u
#define FWM_CTRL_INEN_SHIFT            2u
#define FWM_CTRL_INEN_WIDTH            1u
#define FWM_CTRL_INEN(x)               (((uint32_t)(((uint32_t)(x))<<FWM_CTRL_INEN_SHIFT))&FWM_CTRL_INEN_MASK)
#define FWM_CTRL_INASTSEL_MASK         0x2u
#define FWM_CTRL_INASTSEL_SHIFT        1u
#define FWM_CTRL_INASTSEL_WIDTH        1u
#define FWM_CTRL_INASTSEL(x)           (((uint32_t)(((uint32_t)(x))<<FWM_CTRL_INASTSEL_SHIFT))&FWM_CTRL_INASTSEL_MASK)
#define FWM_CTRL_FWMEN_MASK            0x1u
#define FWM_CTRL_FWMEN_SHIFT           0u
#define FWM_CTRL_FWMEN_WIDTH           1u
#define FWM_CTRL_FWMEN(x)              (((uint32_t)(((uint32_t)(x))<<FWM_CTRL_FWMEN_SHIFT))&FWM_CTRL_FWMEN_MASK)
/* CTRL Reg Mask */
#define FWM_CTRL_MASK                  0x0000000Fu
/* SERV Bit Fields */
#define FWM_SERV_SERVICE_MASK          0xFFFFFFFFu
#define FWM_SERV_SERVICE_SHIFT         0u
#define FWM_SERV_SERVICE_WIDTH         32u
#define FWM_SERV_SERVICE(x)            (((uint32_t)(((uint32_t)(x))<<FWM_SERV_SERVICE_SHIFT))&FWM_SERV_SERVICE_MASK)
/* SERV Reg Mask */
#define FWM_SERV_MASK                  0xFFFFFFFFu
/* CMPL Bit Fields */
#define FWM_CMPL_COMPAREL_MASK         0xFFu
#define FWM_CMPL_COMPAREL_SHIFT        0u
#define FWM_CMPL_COMPAREL_WIDTH        8u
#define FWM_CMPL_COMPAREL(x)           (((uint32_t)(((uint32_t)(x))<<FWM_CMPL_COMPAREL_SHIFT))&FWM_CMPL_COMPAREL_MASK)
/* CMPL Reg Mask */
#define FWM_CMPL_MASK                  0x000000FFu
/* CMPH Bit Fields */
#define FWM_CMPH_COMPAREH_MASK         0xFFu
#define FWM_CMPH_COMPAREH_SHIFT        0u
#define FWM_CMPH_COMPAREH_WIDTH        8u
#define FWM_CMPH_COMPAREH(x)           (((uint32_t)(((uint32_t)(x))<<FWM_CMPH_COMPAREH_SHIFT))&FWM_CMPH_COMPAREH_MASK)
/* CMPH Reg Mask */
#define FWM_CMPH_MASK                  0x000000FFu
/* CLKPRESCALER Bit Fields */
#define FWM_CLKPRESCALER_CLK_DIV_MASK  0xFFu
#define FWM_CLKPRESCALER_CLK_DIV_SHIFT 0u
#define FWM_CLKPRESCALER_CLK_DIV_WIDTH 8u
#define FWM_CLKPRESCALER_CLK_DIV(x)    (((uint32_t)(((uint32_t)(x))<<FWM_CLKPRESCALER_CLK_DIV_SHIFT))&FWM_CLKPRESCALER_CLK_DIV_MASK)
/* CLKPRESCALER Reg Mask */
#define FWM_CLKPRESCALER_MASK          0x000000FFu
/**
 * @}
 */ /* end of group FWM_Register_Masks */
/**
 * @}
 */ /* end of group FWM_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
