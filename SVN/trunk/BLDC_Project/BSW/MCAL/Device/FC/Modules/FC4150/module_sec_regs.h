#ifndef _MODULE_SEC_KJO_Ufdi45_REGS_H_
#define _MODULE_SEC_KJO_Ufdi45_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- SEC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup SEC_Peripheral_Access_Layer SEC Peripheral Access Layer
 * @{
 */
/** SEC - Size of Registers Arrays */
/** SEC - Register Layout Typedef */
#define SEC_DEK_COUNT 4
#define SEC_BCK_COUNT 8
typedef struct {
  __IO uint32_t DEN                           ; /* Debug Enable Register, offset: 0x0 */
  __I  uint32_t FSEC0                         ; /* System Security_Control 0, offset: 0x4 */
  __I  uint32_t FSEC1                         ; /* System Security_Control 1, offset: 0x8 */
  __IO uint32_t DCWOR                         ; /* Debug Control Write Once Register, offset: 0xC */
  __O  uint32_t DEK[SEC_DEK_COUNT]            ; /* Debug Re-Enable Key, offset: 0x10 */
  __IO uint32_t TME                           ; /* Test Mode Enable, offset: 0x20 */
  __IO uint32_t TMEA                          ; /* Test Mode Re-Enable Allow, offset: 0x24 */
  __O  uint32_t TMEK                          ; /* Test Mode Re-Enable Key, offset: 0x28 */
       uint8_t  RESERVED_0[4];
  __IO uint32_t FCR0                          ; /* Flash Control Register0, offset: 0x30 */
       uint8_t  RESERVED_1[12];
  __O  uint32_t BCK[SEC_BCK_COUNT]            ; /* Block Cipher Key, offset: 0x40 */
  __I  uint32_t BC0                           ; /* Boot Config, offset: 0x60 */
} SEC_Type, *SEC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SEC Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup SEC_Register_Masks SEC Register Masks
 * @{
 */
 
/* DEN Bit Fields */
#define SEC_DEN_DEN_MASK               0xFu
#define SEC_DEN_DEN_SHIFT              0u
#define SEC_DEN_DEN_WIDTH              4u
#define SEC_DEN_DEN(x)                 (((uint32_t)(((uint32_t)(x))<<SEC_DEN_DEN_SHIFT))&SEC_DEN_DEN_MASK)
/* DEN Reg Mask */
#define SEC_DEN_MASK                   0x0000000Fu
/* FSEC0 Bit Fields */
#define SEC_FSEC0_SSC0_MASK            0xFFFFu
#define SEC_FSEC0_SSC0_SHIFT           0u
#define SEC_FSEC0_SSC0_WIDTH           16u
#define SEC_FSEC0_SSC0(x)              (((uint32_t)(((uint32_t)(x))<<SEC_FSEC0_SSC0_SHIFT))&SEC_FSEC0_SSC0_MASK)
/* FSEC0 Reg Mask */
#define SEC_FSEC0_MASK                 0x0000FFFFu
/* FSEC1 Bit Fields */
#define SEC_FSEC1_SSC1_MASK            0xFFFFu
#define SEC_FSEC1_SSC1_SHIFT           0u
#define SEC_FSEC1_SSC1_WIDTH           16u
#define SEC_FSEC1_SSC1(x)              (((uint32_t)(((uint32_t)(x))<<SEC_FSEC1_SSC1_SHIFT))&SEC_FSEC1_SSC1_MASK)
/* FSEC1 Reg Mask */
#define SEC_FSEC1_MASK                 0x0000FFFFu
/* DCWOR Bit Fields */
#define SEC_DCWOR_DEA_MASK             0xFu
#define SEC_DCWOR_DEA_SHIFT            0u
#define SEC_DCWOR_DEA_WIDTH            4u
#define SEC_DCWOR_DEA(x)               (((uint32_t)(((uint32_t)(x))<<SEC_DCWOR_DEA_SHIFT))&SEC_DCWOR_DEA_MASK)
#define SEC_DCWOR_RWL_MASK             0xF0u
#define SEC_DCWOR_RWL_SHIFT            4u
#define SEC_DCWOR_RWL_WIDTH            4u
#define SEC_DCWOR_RWL(x)               (((uint32_t)(((uint32_t)(x))<<SEC_DCWOR_RWL_SHIFT))&SEC_DCWOR_RWL_MASK)
/* DCWOR Reg Mask */
#define SEC_DCWOR_MASK                 0x000000FFu
/* DEK Bit Fields */
#define SEC_DEK_DEK_MASK               0xFFFFFFFFu
#define SEC_DEK_DEK_SHIFT              0u
#define SEC_DEK_DEK_WIDTH              32u
#define SEC_DEK_DEK(x)                 (((uint32_t)(((uint32_t)(x))<<SEC_DEK_DEK_SHIFT))&SEC_DEK_DEK_MASK)
/* DEK0 Reg Mask */
#define SEC_DEK_MASK                   0xFFFFFFFFu
/* TME Bit Fields */
#define SEC_TME_TME_MASK               0xFu
#define SEC_TME_TME_SHIFT              0u
#define SEC_TME_TME_WIDTH              4u
#define SEC_TME_TME(x)                 (((uint32_t)(((uint32_t)(x))<<SEC_TME_TME_SHIFT))&SEC_TME_TME_MASK)
/* TME Reg Mask */
#define SEC_TME_MASK                   0x0000000Fu
/* TMEA Bit Fields */
#define SEC_TMEA_TMEA_MASK             0xFu
#define SEC_TMEA_TMEA_SHIFT            0u
#define SEC_TMEA_TMEA_WIDTH            4u
#define SEC_TMEA_TMEA(x)               (((uint32_t)(((uint32_t)(x))<<SEC_TMEA_TMEA_SHIFT))&SEC_TMEA_TMEA_MASK)
/* TMEA Reg Mask */
#define SEC_TMEA_MASK                  0x0000000Fu
/* TMEK Bit Fields */
#define SEC_TMEK_TMEK_MASK             0xFFFFFFFFu
#define SEC_TMEK_TMEK_SHIFT            0u
#define SEC_TMEK_TMEK_WIDTH            32u
#define SEC_TMEK_TMEK(x)               (((uint32_t)(((uint32_t)(x))<<SEC_TMEK_TMEK_SHIFT))&SEC_TMEK_TMEK_MASK)
/* TMEK Reg Mask */
#define SEC_TMEK_MASK                  0xFFFFFFFFu
/* FCR0 Bit Fields */
#define SEC_FCR0_MED_MASK              0xFu
#define SEC_FCR0_MED_SHIFT             0u
#define SEC_FCR0_MED_WIDTH             4u
#define SEC_FCR0_MED(x)                (((uint32_t)(((uint32_t)(x))<<SEC_FCR0_MED_SHIFT))&SEC_FCR0_MED_MASK)
#define SEC_FCR0_NRP_MASK              0xF0u
#define SEC_FCR0_NRP_SHIFT             4u
#define SEC_FCR0_NRP_WIDTH             4u
#define SEC_FCR0_NRP(x)                (((uint32_t)(((uint32_t)(x))<<SEC_FCR0_NRP_SHIFT))&SEC_FCR0_NRP_MASK)
#define SEC_FCR0_NWP_MASK              0xF00u
#define SEC_FCR0_NWP_SHIFT             8u
#define SEC_FCR0_NWP_WIDTH             4u
#define SEC_FCR0_NWP(x)                (((uint32_t)(((uint32_t)(x))<<SEC_FCR0_NWP_SHIFT))&SEC_FCR0_NWP_MASK)
/* FCR0 Reg Mask */
#define SEC_FCR0_MASK                  0x00000FFFu
/* BCK Bit Fields */
#define SEC_BCK_BCK_MASK               0xFFFFFFFFu
#define SEC_BCK_BCK_SHIFT              0u
#define SEC_BCK_BCK_WIDTH              32u
#define SEC_BCK_BCK(x)                 (((uint32_t)(((uint32_t)(x))<<SEC_BCK_BCK_SHIFT))&SEC_BCK_BCK_MASK)
/* BCK0 Reg Mask */
#define SEC_BCK_MASK                   0xFFFFFFFFu
/* BC0 Bit Fields */
#define SEC_BC0_NMIDIS_MASK            0x2u
#define SEC_BC0_NMIDIS_SHIFT           1u
#define SEC_BC0_NMIDIS_WIDTH           1u
#define SEC_BC0_NMIDIS(x)              (((uint32_t)(((uint32_t)(x))<<SEC_BC0_NMIDIS_SHIFT))&SEC_BC0_NMIDIS_MASK)
#define SEC_BC0_RSTDIS_MASK            0x4u
#define SEC_BC0_RSTDIS_SHIFT           2u
#define SEC_BC0_RSTDIS_WIDTH           1u
#define SEC_BC0_RSTDIS(x)              (((uint32_t)(((uint32_t)(x))<<SEC_BC0_RSTDIS_SHIFT))&SEC_BC0_RSTDIS_MASK)
/* BC0 Reg Mask */
#define SEC_BC0_MASK                   0x00000006u
/**
 * @}
 */ /* end of group SEC_Register_Masks */
/**
 * @}
 */ /* end of group SEC_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
