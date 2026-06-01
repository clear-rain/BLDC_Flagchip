#ifndef _MODULE_DMAMUX_KJO_Ufdi17_REGS_H_
#define _MODULE_DMAMUX_KJO_Ufdi17_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- DMAMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup DMAMUX_Peripheral_Access_Layer DMAMUX Peripheral Access Layer
 * @{
 */
/** DMAMUX - Size of Registers Arrays */
/** DMAMUX - Register Layout Typedef */
#define DMAMUX_CHCFG_COUNT 16
typedef struct {
  __IO uint8_t  CHCFG[DMAMUX_CHCFG_COUNT]     ; /* Channel Configuration register, offset: 0x0 */
} DMAMUX_Type, *DMAMUX_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- DMAMUX Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup DMAMUX_Register_Masks DMAMUX Register Masks
 * @{
 */
 
/* CHCFG Bit Fields */
#define DMAMUX_CHCFG_ENBL_MASK         0x80u
#define DMAMUX_CHCFG_ENBL_SHIFT        7u
#define DMAMUX_CHCFG_ENBL_WIDTH        1u
#define DMAMUX_CHCFG_ENBL(x)           (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_ENBL_SHIFT))&DMAMUX_CHCFG_ENBL_MASK)
#define DMAMUX_CHCFG_TRIG_MASK         0x40u
#define DMAMUX_CHCFG_TRIG_SHIFT        6u
#define DMAMUX_CHCFG_TRIG_WIDTH        1u
#define DMAMUX_CHCFG_TRIG(x)           (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_TRIG_SHIFT))&DMAMUX_CHCFG_TRIG_MASK)
#define DMAMUX_CHCFG_SOURCE_MASK       0x3Fu
#define DMAMUX_CHCFG_SOURCE_SHIFT      0u
#define DMAMUX_CHCFG_SOURCE_WIDTH      6u
#define DMAMUX_CHCFG_SOURCE(x)         (((uint8_t)(((uint8_t)(x))<<DMAMUX_CHCFG_SOURCE_SHIFT))&DMAMUX_CHCFG_SOURCE_MASK)
/* CHCFG0 Reg Mask */
#define DMAMUX_CHCFG_MASK              0xFFu
/**
 * @}
 */ /* end of group DMAMUX_Register_Masks */
/**
 * @}
 */ /* end of group DMAMUX_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
