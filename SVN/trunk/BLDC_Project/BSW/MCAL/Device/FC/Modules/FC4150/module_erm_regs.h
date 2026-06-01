#ifndef _MODULE_ERM_KJO_Ufdi25_REGS_H_
#define _MODULE_ERM_KJO_Ufdi25_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- ERM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup ERM_Peripheral_Access_Layer ERM Peripheral Access Layer
 * @{
 */
/** ERM - Size of Registers Arrays */
/** ERM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR0                           ; /* ERM Configuration Register 0, offset: 0x0 */
       uint8_t  RESERVED_0[12];
  __IO uint32_t SR0                           ; /* ERM Status Register 0, offset: 0x10 */
       uint8_t  RESERVED_1[236];
  __I  uint32_t EAR0                          ; /* ERM Error Address Register, offset: 0x100 */
       uint8_t  RESERVED_2[12];
  __I  uint32_t EAR1                          ; /* ERM Error Address Register, offset: 0x110 */
       uint8_t  RESERVED_3[12];
  __I  uint32_t EAR2                          ; /* ERM Error Address Register, offset: 0x120 */
       uint8_t  RESERVED_4[12];
  __I  uint32_t EAR3                          ; /* ERM Error Address Register, offset: 0x130 */
       uint8_t  RESERVED_5[12];
  __I  uint32_t EAR4                          ; /* ERM Error Address Register, offset: 0x140 */
} ERM_Type, *ERM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ERM Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup ERM_Register_Masks ERM Register Masks
 * @{
 */
 
/* CR0 Bit Fields */
#define ERM_CR0_ESCIE0_MASK            0x80000000u
#define ERM_CR0_ESCIE0_SHIFT           31u
#define ERM_CR0_ESCIE0_WIDTH           1u
#define ERM_CR0_ESCIE0(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE0_SHIFT))&ERM_CR0_ESCIE0_MASK)
#define ERM_CR0_ENCIE0_MASK            0x40000000u
#define ERM_CR0_ENCIE0_SHIFT           30u
#define ERM_CR0_ENCIE0_WIDTH           1u
#define ERM_CR0_ENCIE0(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE0_SHIFT))&ERM_CR0_ENCIE0_MASK)
#define ERM_CR0_ESCIE1_MASK            0x8000000u
#define ERM_CR0_ESCIE1_SHIFT           27u
#define ERM_CR0_ESCIE1_WIDTH           1u
#define ERM_CR0_ESCIE1(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE1_SHIFT))&ERM_CR0_ESCIE1_MASK)
#define ERM_CR0_ENCIE1_MASK            0x4000000u
#define ERM_CR0_ENCIE1_SHIFT           26u
#define ERM_CR0_ENCIE1_WIDTH           1u
#define ERM_CR0_ENCIE1(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE1_SHIFT))&ERM_CR0_ENCIE1_MASK)
#define ERM_CR0_ESCIE2_MASK            0x800000u
#define ERM_CR0_ESCIE2_SHIFT           23u
#define ERM_CR0_ESCIE2_WIDTH           1u
#define ERM_CR0_ESCIE2(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE2_SHIFT))&ERM_CR0_ESCIE2_MASK)
#define ERM_CR0_ENCIE2_MASK            0x400000u
#define ERM_CR0_ENCIE2_SHIFT           22u
#define ERM_CR0_ENCIE2_WIDTH           1u
#define ERM_CR0_ENCIE2(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE2_SHIFT))&ERM_CR0_ENCIE2_MASK)
#define ERM_CR0_ESCIE3_MASK            0x80000u
#define ERM_CR0_ESCIE3_SHIFT           19u
#define ERM_CR0_ESCIE3_WIDTH           1u
#define ERM_CR0_ESCIE3(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE3_SHIFT))&ERM_CR0_ESCIE3_MASK)
#define ERM_CR0_ENCIE3_MASK            0x40000u
#define ERM_CR0_ENCIE3_SHIFT           18u
#define ERM_CR0_ENCIE3_WIDTH           1u
#define ERM_CR0_ENCIE3(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE3_SHIFT))&ERM_CR0_ENCIE3_MASK)
#define ERM_CR0_ESCIE4_MASK            0x8000u
#define ERM_CR0_ESCIE4_SHIFT           15u
#define ERM_CR0_ESCIE4_WIDTH           1u
#define ERM_CR0_ESCIE4(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ESCIE4_SHIFT))&ERM_CR0_ESCIE4_MASK)
#define ERM_CR0_ENCIE4_MASK            0x4000u
#define ERM_CR0_ENCIE4_SHIFT           14u
#define ERM_CR0_ENCIE4_WIDTH           1u
#define ERM_CR0_ENCIE4(x)              (((uint32_t)(((uint32_t)(x))<<ERM_CR0_ENCIE4_SHIFT))&ERM_CR0_ENCIE4_MASK)
/* CR0 Reg Mask */
#define ERM_CR0_MASK                   0xCCCCC000u

/* SR0 Bit Fields */
#define ERM_SR0_SBC0_MASK              0x80000000u
#define ERM_SR0_SBC0_SHIFT             31u
#define ERM_SR0_SBC0_WIDTH             1u
#define ERM_SR0_SBC0(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC0_SHIFT))&ERM_SR0_SBC0_MASK)
#define ERM_SR0_NCE0_MASK              0x40000000u
#define ERM_SR0_NCE0_SHIFT             30u
#define ERM_SR0_NCE0_WIDTH             1u
#define ERM_SR0_NCE0(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE0_SHIFT))&ERM_SR0_NCE0_MASK)
#define ERM_SR0_SBC1_MASK              0x8000000u
#define ERM_SR0_SBC1_SHIFT             27u
#define ERM_SR0_SBC1_WIDTH             1u
#define ERM_SR0_SBC1(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC1_SHIFT))&ERM_SR0_SBC1_MASK)
#define ERM_SR0_NCE1_MASK              0x4000000u
#define ERM_SR0_NCE1_SHIFT             26u
#define ERM_SR0_NCE1_WIDTH             1u
#define ERM_SR0_NCE1(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE1_SHIFT))&ERM_SR0_NCE1_MASK)
#define ERM_SR0_SBC2_MASK              0x800000u
#define ERM_SR0_SBC2_SHIFT             23u
#define ERM_SR0_SBC2_WIDTH             1u
#define ERM_SR0_SBC2(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC2_SHIFT))&ERM_SR0_SBC2_MASK)
#define ERM_SR0_NCE2_MASK              0x400000u
#define ERM_SR0_NCE2_SHIFT             22u
#define ERM_SR0_NCE2_WIDTH             1u
#define ERM_SR0_NCE2(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE2_SHIFT))&ERM_SR0_NCE2_MASK)
#define ERM_SR0_SBC3_MASK              0x80000u
#define ERM_SR0_SBC3_SHIFT             19u
#define ERM_SR0_SBC3_WIDTH             1u
#define ERM_SR0_SBC3(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC3_SHIFT))&ERM_SR0_SBC3_MASK)
#define ERM_SR0_NCE3_MASK              0x40000u
#define ERM_SR0_NCE3_SHIFT             18u
#define ERM_SR0_NCE3_WIDTH             1u
#define ERM_SR0_NCE3(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE3_SHIFT))&ERM_SR0_NCE3_MASK)
#define ERM_SR0_SBC4_MASK              0x8000u
#define ERM_SR0_SBC4_SHIFT             15u
#define ERM_SR0_SBC4_WIDTH             1u
#define ERM_SR0_SBC4(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_SBC4_SHIFT))&ERM_SR0_SBC4_MASK)
#define ERM_SR0_NCE4_MASK              0x4000u
#define ERM_SR0_NCE4_SHIFT             14u
#define ERM_SR0_NCE4_WIDTH             1u
#define ERM_SR0_NCE4(x)                (((uint32_t)(((uint32_t)(x))<<ERM_SR0_NCE4_SHIFT))&ERM_SR0_NCE4_MASK)
/* SR0 Reg Mask */
#define ERM_SR0_MASK                   0xCCCCC000u

/* EAR Bit Fields */
#define ERM_EAR_EAR_MASK               0xFFFFFFFFu
#define ERM_EAR_EAR_SHIFT              0u
#define ERM_EAR_EAR_WIDTH              32u
#define ERM_EAR_EAR(x)                 (((uint32_t)(((uint32_t)(x))<<ERM_EAR_EAR_SHIFT))&ERM_EAR_EAR_MASK)
/* EAR0 Reg Mask */
#define ERM_EAR_MASK                   0xFFFFFFFFu

/**
 * @}
 */ /* end of group ERM_Register_Masks */
/**
 * @}
 */ /* end of group ERM_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
