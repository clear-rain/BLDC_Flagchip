#ifndef _MODULE_CRC_KJO_Ufdi21_REGS_H_
#define _MODULE_CRC_KJO_Ufdi21_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
#include "typedef.h"
/* ----------------------------------------------------------------------------
   -- CRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup CRC_Peripheral_Access_Layer CRC Peripheral Access Layer
 * @{
 */
/** CRC - Size of Registers Arrays */
/** CRC - Register Layout Typedef */
typedef struct {
  union {
    __IO uint32_t uDATA;                          /** CRC Data union */
    struct {
      __IO uint16_t L;                            /** CRC_DATAL register., offset: 0x0 */
      __IO uint16_t H;                            /** CRC_DATAH register., offset: 0x2 */
    } tDATA_16;
    struct {
      __IO uint8_t LL;                            /** CRC_DATALL register., offset: 0x0 */
      __IO uint8_t LU1;                            /** CRC_DATALU register., offset: 0x1 */
      __IO uint8_t HL;                            /** CRC_DATAHL register., offset: 0x2 */
      __IO uint8_t HU;                            /** CRC_DATAHU register., offset: 0x3 */
    } tDATA_8;
  } DATA;                                         /** CRC Data Register, offset: 0x0 */
  __IO uint32_t POLY;                             /** CRC Polynomial register, offset: 0x4 */
  __IO uint32_t CR	;                             /** CRC Control Register, offset: 0x8 */
#if DEVICE_NAME <= FC4150F1MBS2P144T1A
  __IO uint32_t SDAT;                             /** CRC Control Register, offset: 0xc */
#endif
} CRC_Type, *CRC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CRC Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup CRC_Register_Masks CRC Register Masks
 * @{
 */
 
/* DATA Bit Fields */
#define CRC_DATA_HU_MASK               0xFF000000u
#define CRC_DATA_HU_SHIFT              24u
#define CRC_DATA_HU_WIDTH              8u
#define CRC_DATA_HU(x)                 (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HU_SHIFT))&CRC_DATA_HU_MASK)
#define CRC_DATA_HL_MASK               0xFF0000u
#define CRC_DATA_HL_SHIFT              16u
#define CRC_DATA_HL_WIDTH              8u
#define CRC_DATA_HL(x)                 (((uint32_t)(((uint32_t)(x))<<CRC_DATA_HL_SHIFT))&CRC_DATA_HL_MASK)
#define CRC_DATA_LU_MASK               0xFF00u
#define CRC_DATA_LU_SHIFT              8u
#define CRC_DATA_LU_WIDTH              8u
#define CRC_DATA_LU(x)                 (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LU_SHIFT))&CRC_DATA_LU_MASK)
#define CRC_DATA_LL_MASK               0xFFu
#define CRC_DATA_LL_SHIFT              0u
#define CRC_DATA_LL_WIDTH              8u
#define CRC_DATA_LL(x)                 (((uint32_t)(((uint32_t)(x))<<CRC_DATA_LL_SHIFT))&CRC_DATA_LL_MASK)
/* DATA Reg Mask */
#define CRC_DATA_MASK                  0xFFFFFFFFu
/* POLY Bit Fields */
#define CRC_POLY_HIGH_MASK             0xFFFF0000u
#define CRC_POLY_HIGH_SHIFT            16u
#define CRC_POLY_HIGH_WIDTH            16u
#define CRC_POLY_HIGH(x)               (((uint32_t)(((uint32_t)(x))<<CRC_POLY_HIGH_SHIFT))&CRC_POLY_HIGH_MASK)
#define CRC_POLY_LOW_MASK              0xFFFFu
#define CRC_POLY_LOW_SHIFT             0u
#define CRC_POLY_LOW_WIDTH             16u
#define CRC_POLY_LOW(x)                (((uint32_t)(((uint32_t)(x))<<CRC_POLY_LOW_SHIFT))&CRC_POLY_LOW_MASK)
/* POLY Reg Mask */
#define CRC_POLY_MASK                  0xFFFFFFFFu
/* CR Bit Fields */
#define CRC_CR_DSW_MASK                0xC0000000u
#define CRC_CR_DSW_SHIFT               30u
#define CRC_CR_DSW_WIDTH               2u
#define CRC_CR_DSW(x)                  (((uint32_t)(((uint32_t)(x))<<CRC_CR_DSW_SHIFT))&CRC_CR_DSW_MASK)
#define CRC_CR_DSR_MASK                0x30000000u
#define CRC_CR_DSR_SHIFT               28u
#define CRC_CR_DSR_WIDTH               2u
#define CRC_CR_DSR(x)                  (((uint32_t)(((uint32_t)(x))<<CRC_CR_DSR_SHIFT))&CRC_CR_DSR_MASK)
#if DEVICE_NAME <= FC4150F1MBS2P144T1A
#define CRC_CR_TCRC8_MASK              0x8000000u
#define CRC_CR_TCRC8_SHIFT             27u
#define CRC_CR_TCRC8_WIDTH             1u
#define CRC_CR_TCRC8(x)                (((uint32_t)(((uint32_t)(x))<<CRC_CR_TCRC8_SHIFT))&CRC_CR_TCRC8_MASK)
#endif
#define CRC_CR_FXOR_MASK               0x4000000u
#define CRC_CR_FXOR_SHIFT              26u
#define CRC_CR_FXOR_WIDTH              1u
#define CRC_CR_FXOR(x)                 (((uint32_t)(((uint32_t)(x))<<CRC_CR_FXOR_SHIFT))&CRC_CR_FXOR_MASK)
#define CRC_CR_WAS_MASK                0x2000000u
#define CRC_CR_WAS_SHIFT               25u
#define CRC_CR_WAS_WIDTH               1u
#define CRC_CR_WAS(x)                  (((uint32_t)(((uint32_t)(x))<<CRC_CR_WAS_SHIFT))&CRC_CR_WAS_MASK)
#define CRC_CR_TCRC_MASK               0x1000000u
#define CRC_CR_TCRC_SHIFT              24u
#define CRC_CR_TCRC_WIDTH              1u
#define CRC_CR_TCRC(x)                 (((uint32_t)(((uint32_t)(x))<<CRC_CR_TCRC_SHIFT))&CRC_CR_TCRC_MASK)
/* CR Reg Mask */
#define CRC_CR_MASK                    0xF7000000u
#if DEVICE_NAME <= FC4150F1MBS2P144T1A
/* SDAT Bit Fields */
#define CRC_SDAT_HIGH_MASK             0xFFFF0000u
#define CRC_SDAT_HIGH_SHIFT            16u
#define CRC_SDAT_HIGH_WIDTH            16u
#define CRC_SDAT_HIGH(x)               (((uint32_t)(((uint32_t)(x))<<CRC_SDAT_HIGH_SHIFT))&CRC_SDAT_HIGH_MASK)
#define CRC_SDAT_LOW_MASK              0xFFFFu
#define CRC_SDAT_LOW_SHIFT             0u
#define CRC_SDAT_LOW_WIDTH             16u
#define CRC_SDAT_LOW(x)                (((uint32_t)(((uint32_t)(x))<<CRC_SDAT_LOW_SHIFT))&CRC_SDAT_LOW_MASK)
/* SDAT Reg Mask */
#define CRC_SDAT_MASK                  0xFFFFFFFFu
#endif
/**
 * @}
 */ /* end of group CRC_Register_Masks */
/**
 * @}
 */ /* end of group CRC_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
