#ifndef _MODULE_WKU_KJO_Ufdi6_REGS_H_
#define _MODULE_WKU_KJO_Ufdi6_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- WKU Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup WKU_Peripheral_Access_Layer WKU Peripheral Access Layer
 * @{
 */
/** WKU - Size of Registers Arrays */
/** WKU - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[8];
  __IO uint32_t MWER0                         ; /* Module Wakeup Enable Register, offset: 0x08 */
  __IO uint32_t MWER1                         ; /* Module Wakeup Enable Register, offset: 0x0C */
  __IO uint32_t MWER2                         ; /* Module Wakeup Enable Register, offset: 0x10 */
} WKU_Type, *WKU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- WKU Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup WKU_Register_Masks WKU Register Masks
 * @{
 */
 
/* MWER0 Bit Fields */
#define WKU_MWER0_MWE7_MASK            0x80u
#define WKU_MWER0_MWE7_SHIFT           7u
#define WKU_MWER0_MWE7_WIDTH           1u
#define WKU_MWER0_MWE7(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE7_SHIFT))&WKU_MWER0_MWE7_MASK)
#define WKU_MWER0_MWE6_MASK            0x40u
#define WKU_MWER0_MWE6_SHIFT           6u
#define WKU_MWER0_MWE6_WIDTH           1u
#define WKU_MWER0_MWE6(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE6_SHIFT))&WKU_MWER0_MWE6_MASK)
#define WKU_MWER0_MWE5_MASK            0x20u
#define WKU_MWER0_MWE5_SHIFT           5u
#define WKU_MWER0_MWE5_WIDTH           1u
#define WKU_MWER0_MWE5(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE5_SHIFT))&WKU_MWER0_MWE5_MASK)
#define WKU_MWER0_MWE4_MASK            0x10u
#define WKU_MWER0_MWE4_SHIFT           4u
#define WKU_MWER0_MWE4_WIDTH           1u
#define WKU_MWER0_MWE4(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE4_SHIFT))&WKU_MWER0_MWE4_MASK)
#define WKU_MWER0_MWE3_MASK            0x8u
#define WKU_MWER0_MWE3_SHIFT           3u
#define WKU_MWER0_MWE3_WIDTH           1u
#define WKU_MWER0_MWE3(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE3_SHIFT))&WKU_MWER0_MWE3_MASK)
#define WKU_MWER0_MWE2_MASK            0x4u
#define WKU_MWER0_MWE2_SHIFT           2u
#define WKU_MWER0_MWE2_WIDTH           1u
#define WKU_MWER0_MWE2(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE2_SHIFT))&WKU_MWER0_MWE2_MASK)
#define WKU_MWER0_MWE1_MASK            0x2u
#define WKU_MWER0_MWE1_SHIFT           1u
#define WKU_MWER0_MWE1_WIDTH           1u
#define WKU_MWER0_MWE1(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE1_SHIFT))&WKU_MWER0_MWE1_MASK)
#define WKU_MWER0_MWE0_MASK            0x1u
#define WKU_MWER0_MWE0_SHIFT           0u
#define WKU_MWER0_MWE0_WIDTH           1u
#define WKU_MWER0_MWE0(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER0_MWE0_SHIFT))&WKU_MWER0_MWE0_MASK)
/* MWER0 Reg Mask */
#define WKU_MWER0_MASK                 0x000000FFu
/* MWER1 Bit Fields */
#define WKU_MWER1_MWE15_MASK           0x80u
#define WKU_MWER1_MWE15_SHIFT          7u
#define WKU_MWER1_MWE15_WIDTH          1u
#define WKU_MWER1_MWE15(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE15_SHIFT))&WKU_MWER1_MWE15_MASK)
#define WKU_MWER1_MWE14_MASK           0x40u
#define WKU_MWER1_MWE14_SHIFT          6u
#define WKU_MWER1_MWE14_WIDTH          1u
#define WKU_MWER1_MWE14(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE14_SHIFT))&WKU_MWER1_MWE14_MASK)
#define WKU_MWER1_MWE13_MASK           0x20u
#define WKU_MWER1_MWE13_SHIFT          5u
#define WKU_MWER1_MWE13_WIDTH          1u
#define WKU_MWER1_MWE13(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE13_SHIFT))&WKU_MWER1_MWE13_MASK)
#define WKU_MWER1_MWE12_MASK           0x10u
#define WKU_MWER1_MWE12_SHIFT          4u
#define WKU_MWER1_MWE12_WIDTH          1u
#define WKU_MWER1_MWE12(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE12_SHIFT))&WKU_MWER1_MWE12_MASK)
#define WKU_MWER1_MWE11_MASK           0x8u
#define WKU_MWER1_MWE11_SHIFT          3u
#define WKU_MWER1_MWE11_WIDTH          1u
#define WKU_MWER1_MWE11(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE11_SHIFT))&WKU_MWER1_MWE11_MASK)
#define WKU_MWER1_MWE10_MASK           0x4u
#define WKU_MWER1_MWE10_SHIFT          2u
#define WKU_MWER1_MWE10_WIDTH          1u
#define WKU_MWER1_MWE10(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE10_SHIFT))&WKU_MWER1_MWE10_MASK)
#define WKU_MWER1_MWE9_MASK            0x2u
#define WKU_MWER1_MWE9_SHIFT           1u
#define WKU_MWER1_MWE9_WIDTH           1u
#define WKU_MWER1_MWE9(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE9_SHIFT))&WKU_MWER1_MWE9_MASK)
#define WKU_MWER1_MWE8_MASK            0x1u
#define WKU_MWER1_MWE8_SHIFT           0u
#define WKU_MWER1_MWE8_WIDTH           1u
#define WKU_MWER1_MWE8(x)              (((uint32_t)(((uint32_t)(x))<<WKU_MWER1_MWE8_SHIFT))&WKU_MWER1_MWE8_MASK)
/* MWER1 Reg Mask */
#define WKU_MWER1_MASK                 0x000000FFu
/* MWER2 Bit Fields */
#define WKU_MWER2_MWE23_MASK           0x80u
#define WKU_MWER2_MWE23_SHIFT          7u
#define WKU_MWER2_MWE23_WIDTH          1u
#define WKU_MWER2_MWE23(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE23_SHIFT))&WKU_MWER2_MWE23_MASK)
#define WKU_MWER2_MWE22_MASK           0x40u
#define WKU_MWER2_MWE22_SHIFT          6u
#define WKU_MWER2_MWE22_WIDTH          1u
#define WKU_MWER2_MWE22(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE22_SHIFT))&WKU_MWER2_MWE22_MASK)
#define WKU_MWER2_MWE21_MASK           0x20u
#define WKU_MWER2_MWE21_SHIFT          5u
#define WKU_MWER2_MWE21_WIDTH          1u
#define WKU_MWER2_MWE21(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE21_SHIFT))&WKU_MWER2_MWE21_MASK)
#define WKU_MWER2_MWE20_MASK           0x10u
#define WKU_MWER2_MWE20_SHIFT          4u
#define WKU_MWER2_MWE20_WIDTH          1u
#define WKU_MWER2_MWE20(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE20_SHIFT))&WKU_MWER2_MWE20_MASK)
#define WKU_MWER2_MWE19_MASK           0x8u
#define WKU_MWER2_MWE19_SHIFT          3u
#define WKU_MWER2_MWE19_WIDTH          1u
#define WKU_MWER2_MWE19(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE19_SHIFT))&WKU_MWER2_MWE19_MASK)
#define WKU_MWER2_MWE18_MASK           0x4u
#define WKU_MWER2_MWE18_SHIFT          2u
#define WKU_MWER2_MWE18_WIDTH          1u
#define WKU_MWER2_MWE18(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE18_SHIFT))&WKU_MWER2_MWE18_MASK)
#define WKU_MWER2_MWE17_MASK           0x2u
#define WKU_MWER2_MWE17_SHIFT          1u
#define WKU_MWER2_MWE17_WIDTH          1u
#define WKU_MWER2_MWE17(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE17_SHIFT))&WKU_MWER2_MWE17_MASK)
#define WKU_MWER2_MWE16_MASK           0x1u
#define WKU_MWER2_MWE16_SHIFT          0u
#define WKU_MWER2_MWE16_WIDTH          1u
#define WKU_MWER2_MWE16(x)             (((uint32_t)(((uint32_t)(x))<<WKU_MWER2_MWE16_SHIFT))&WKU_MWER2_MWE16_MASK)
/* MWER2 Reg Mask */
#define WKU_MWER2_MASK                 0x000000FFu
/**
 * @}
 */ /* end of group WKU_Register_Masks */
/**
 * @}
 */ /* end of group WKU_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
