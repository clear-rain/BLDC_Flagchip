#ifndef _MODULE_MCM_KJO_Ufdi31_REGS_H_
#define _MODULE_MCM_KJO_Ufdi31_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- MCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup MCM_Peripheral_Access_Layer MCM Peripheral Access Layer
 * @{
 */
/** MCM - Size of Registers Arrays */
/** MCM - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[12];
  __IO uint32_t ACR                           ; /* Arbiter Control Register, offset: 0xC */
  __IO uint32_t FISCR                         ; /* FPU Interrupt Status and Control Register, offset: 0x10 */
       uint8_t  RESERVED_1[1132];
  __IO uint32_t CASPECR                       ; /* Cache and System Ram Parity and ECC Control Register, offset: 0x480 */
       uint8_t  RESERVED_2[4];
  __IO uint32_t CASPEIR                       ; /* Cache and System Ram Parity and ECC Interrupt Register, offset: 0x488 */
       uint8_t  RESERVED_3[4];
  __I  uint32_t CASFAR                        ; /* Cache and System Ram Fault Address Register, offset: 0x490 */
  __I  uint32_t CASFATR                       ; /* Cache and System Ram Fault Attribute Register, offset: 0x494 */
       uint8_t  RESERVED_4[12];
  __I  uint32_t CASFDR                        ; /* Cache and System Ram Fault Data Register, offset: 0x4A4 */
} MCM_Type, *MCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MCM Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup MCM_Register_Masks MCM Register Masks
 * @{
 */
 
/* ACR Bit Fields */
#define MCM_ACR_CTCMAP_MASK            0x30000000u
#define MCM_ACR_CTCMAP_SHIFT           28u
#define MCM_ACR_CTCMAP_WIDTH           2u
#define MCM_ACR_CTCMAP(x)              (((uint32_t)(((uint32_t)(x))<<MCM_ACR_CTCMAP_SHIFT))&MCM_ACR_CTCMAP_MASK)
#define MCM_ACR_DTCMAP_MASK            0x3000000u
#define MCM_ACR_DTCMAP_SHIFT           24u
#define MCM_ACR_DTCMAP_WIDTH           2u
#define MCM_ACR_DTCMAP(x)              (((uint32_t)(((uint32_t)(x))<<MCM_ACR_DTCMAP_SHIFT))&MCM_ACR_DTCMAP_MASK)
#define MCM_ACR_CBRR_MASK              0x200u
#define MCM_ACR_CBRR_SHIFT             9u
#define MCM_ACR_CBRR_WIDTH             1u
#define MCM_ACR_CBRR(x)                (((uint32_t)(((uint32_t)(x))<<MCM_ACR_CBRR_SHIFT))&MCM_ACR_CBRR_MASK)
/* ACR Reg Mask */
#define MCM_ACR_MASK                   0x33000200u
/* FISCR Bit Fields */
#define MCM_FISCR_FIDCE_MASK           0x80000000u
#define MCM_FISCR_FIDCE_SHIFT          31u
#define MCM_FISCR_FIDCE_WIDTH          1u
#define MCM_FISCR_FIDCE(x)             (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FIDCE_SHIFT))&MCM_FISCR_FIDCE_MASK)
#define MCM_FISCR_FIXCE_MASK           0x10000000u
#define MCM_FISCR_FIXCE_SHIFT          28u
#define MCM_FISCR_FIXCE_WIDTH          1u
#define MCM_FISCR_FIXCE(x)             (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FIXCE_SHIFT))&MCM_FISCR_FIXCE_MASK)
#define MCM_FISCR_FUFCE_MASK           0x8000000u
#define MCM_FISCR_FUFCE_SHIFT          27u
#define MCM_FISCR_FUFCE_WIDTH          1u
#define MCM_FISCR_FUFCE(x)             (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FUFCE_SHIFT))&MCM_FISCR_FUFCE_MASK)
#define MCM_FISCR_FOFCE_MASK           0x4000000u
#define MCM_FISCR_FOFCE_SHIFT          26u
#define MCM_FISCR_FOFCE_WIDTH          1u
#define MCM_FISCR_FOFCE(x)             (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FOFCE_SHIFT))&MCM_FISCR_FOFCE_MASK)
#define MCM_FISCR_FDZCE_MASK           0x2000000u
#define MCM_FISCR_FDZCE_SHIFT          25u
#define MCM_FISCR_FDZCE_WIDTH          1u
#define MCM_FISCR_FDZCE(x)             (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FDZCE_SHIFT))&MCM_FISCR_FDZCE_MASK)
#define MCM_FISCR_FIOCE_MASK           0x1000000u
#define MCM_FISCR_FIOCE_SHIFT          24u
#define MCM_FISCR_FIOCE_WIDTH          1u
#define MCM_FISCR_FIOCE(x)             (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FIOCE_SHIFT))&MCM_FISCR_FIOCE_MASK)
#define MCM_FISCR_FIDC_MASK            0x8000u
#define MCM_FISCR_FIDC_SHIFT           15u
#define MCM_FISCR_FIDC_WIDTH           1u
#define MCM_FISCR_FIDC(x)              (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FIDC_SHIFT))&MCM_FISCR_FIDC_MASK)
#define MCM_FISCR_FIXC_MASK            0x1000u
#define MCM_FISCR_FIXC_SHIFT           12u
#define MCM_FISCR_FIXC_WIDTH           1u
#define MCM_FISCR_FIXC(x)              (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FIXC_SHIFT))&MCM_FISCR_FIXC_MASK)
#define MCM_FISCR_FUFC_MASK            0x800u
#define MCM_FISCR_FUFC_SHIFT           11u
#define MCM_FISCR_FUFC_WIDTH           1u
#define MCM_FISCR_FUFC(x)              (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FUFC_SHIFT))&MCM_FISCR_FUFC_MASK)
#define MCM_FISCR_FOFC_MASK            0x400u
#define MCM_FISCR_FOFC_SHIFT           10u
#define MCM_FISCR_FOFC_WIDTH           1u
#define MCM_FISCR_FOFC(x)              (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FOFC_SHIFT))&MCM_FISCR_FOFC_MASK)
#define MCM_FISCR_FDZC_MASK            0x200u
#define MCM_FISCR_FDZC_SHIFT           9u
#define MCM_FISCR_FDZC_WIDTH           1u
#define MCM_FISCR_FDZC(x)              (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FDZC_SHIFT))&MCM_FISCR_FDZC_MASK)
#define MCM_FISCR_FIOC_MASK            0x100u
#define MCM_FISCR_FIOC_SHIFT           8u
#define MCM_FISCR_FIOC_WIDTH           1u
#define MCM_FISCR_FIOC(x)              (((uint32_t)(((uint32_t)(x))<<MCM_FISCR_FIOC_SHIFT))&MCM_FISCR_FIOC_MASK)
/* FISCR Reg Mask */
#define MCM_FISCR_MASK                 0x9F009F00u
/* CASPECR Bit Fields */
#define MCM_CASPECR_ECPR_MASK          0x100000u
#define MCM_CASPECR_ECPR_SHIFT         20u
#define MCM_CASPECR_ECPR_WIDTH         1u
#define MCM_CASPECR_ECPR(x)            (((uint32_t)(((uint32_t)(x))<<MCM_CASPECR_ECPR_SHIFT))&MCM_CASPECR_ECPR_MASK)
#define MCM_CASPECR_ER1BR_MASK         0x100u
#define MCM_CASPECR_ER1BR_SHIFT        8u
#define MCM_CASPECR_ER1BR_WIDTH        1u
#define MCM_CASPECR_ER1BR(x)           (((uint32_t)(((uint32_t)(x))<<MCM_CASPECR_ER1BR_SHIFT))&MCM_CASPECR_ER1BR_MASK)
#define MCM_CASPECR_ERNCR_MASK         0x1u
#define MCM_CASPECR_ERNCR_SHIFT        0u
#define MCM_CASPECR_ERNCR_WIDTH        1u
#define MCM_CASPECR_ERNCR(x)           (((uint32_t)(((uint32_t)(x))<<MCM_CASPECR_ERNCR_SHIFT))&MCM_CASPECR_ERNCR_MASK)
/* CASPECR Reg Mask */
#define MCM_CASPECR_MASK               0x00100101u
/* CASPEIR Bit Fields */
#define MCM_CASPEIR_PRESENT_MASK       0x80000000u
#define MCM_CASPEIR_PRESENT_SHIFT      31u
#define MCM_CASPEIR_PRESENT_WIDTH      1u
#define MCM_CASPEIR_PRESENT(x)         (((uint32_t)(((uint32_t)(x))<<MCM_CASPEIR_PRESENT_SHIFT))&MCM_CASPEIR_PRESENT_MASK)
#define MCM_CASPEIR_PEELOC_MASK        0x1F000000u
#define MCM_CASPEIR_PEELOC_SHIFT       24u
#define MCM_CASPEIR_PEELOC_WIDTH       5u
#define MCM_CASPEIR_PEELOC(x)          (((uint32_t)(((uint32_t)(x))<<MCM_CASPEIR_PEELOC_SHIFT))&MCM_CASPEIR_PEELOC_MASK)
#define MCM_CASPEIR_PE_MASK            0xFF0000u
#define MCM_CASPEIR_PE_SHIFT           16u
#define MCM_CASPEIR_PE_WIDTH           8u
#define MCM_CASPEIR_PE(x)              (((uint32_t)(((uint32_t)(x))<<MCM_CASPEIR_PE_SHIFT))&MCM_CASPEIR_PE_MASK)
#define MCM_CASPEIR_E1B_MASK           0xFF00u
#define MCM_CASPEIR_E1B_SHIFT          8u
#define MCM_CASPEIR_E1B_WIDTH          8u
#define MCM_CASPEIR_E1B(x)             (((uint32_t)(((uint32_t)(x))<<MCM_CASPEIR_E1B_SHIFT))&MCM_CASPEIR_E1B_MASK)
#define MCM_CASPEIR_ENC_MASK           0xFFu
#define MCM_CASPEIR_ENC_SHIFT          0u
#define MCM_CASPEIR_ENC_WIDTH          8u
#define MCM_CASPEIR_ENC(x)             (((uint32_t)(((uint32_t)(x))<<MCM_CASPEIR_ENC_SHIFT))&MCM_CASPEIR_ENC_MASK)
/* CASPEIR Reg Mask */
#define MCM_CASPEIR_MASK               0x9FFFFFFFu
/* CASFAR Bit Fields */
#define MCM_CASFAR_EFADD_MASK          0xFFFFFFFFu
#define MCM_CASFAR_EFADD_SHIFT         0u
#define MCM_CASFAR_EFADD_WIDTH         32u
#define MCM_CASFAR_EFADD(x)            (((uint32_t)(((uint32_t)(x))<<MCM_CASFAR_EFADD_SHIFT))&MCM_CASFAR_EFADD_MASK)
/* CASFAR Reg Mask */
#define MCM_CASFAR_MASK                0xFFFFFFFFu
/* CASFATR Bit Fields */
#define MCM_CASFATR_MULT_MASK          0x80000000u
#define MCM_CASFATR_MULT_SHIFT         31u
#define MCM_CASFATR_MULT_WIDTH         1u
#define MCM_CASFATR_MULT(x)            (((uint32_t)(((uint32_t)(x))<<MCM_CASFATR_MULT_SHIFT))&MCM_CASFATR_MULT_MASK)
#define MCM_CASFATR_PEMASTER_MASK      0xFF00u
#define MCM_CASFATR_PEMASTER_SHIFT     8u
#define MCM_CASFATR_PEMASTER_WIDTH     8u
#define MCM_CASFATR_PEMASTER(x)        (((uint32_t)(((uint32_t)(x))<<MCM_CASFATR_PEMASTER_SHIFT))&MCM_CASFATR_PEMASTER_MASK)
#define MCM_CASFATR_PWR_MASK           0x80u
#define MCM_CASFATR_PWR_SHIFT          7u
#define MCM_CASFATR_PWR_WIDTH          1u
#define MCM_CASFATR_PWR(x)             (((uint32_t)(((uint32_t)(x))<<MCM_CASFATR_PWR_SHIFT))&MCM_CASFATR_PWR_MASK)
#define MCM_CASFATR_PESIZE_MASK        0x30u
#define MCM_CASFATR_PESIZE_SHIFT       4u
#define MCM_CASFATR_PESIZE_WIDTH       2u
#define MCM_CASFATR_PESIZE(x)          (((uint32_t)(((uint32_t)(x))<<MCM_CASFATR_PESIZE_SHIFT))&MCM_CASFATR_PESIZE_MASK)
#define MCM_CASFATR_PEFPRT_MASK        0x3u
#define MCM_CASFATR_PEFPRT_SHIFT       0u
#define MCM_CASFATR_PEFPRT_WIDTH       2u
#define MCM_CASFATR_PEFPRT(x)          (((uint32_t)(((uint32_t)(x))<<MCM_CASFATR_PEFPRT_SHIFT))&MCM_CASFATR_PEFPRT_MASK)
/* CASFATR Reg Mask */
#define MCM_CASFATR_MASK               0x8000FFB3u
/* CASFDR Bit Fields */
#define MCM_CASFDR_PEFD_MASK           0xFFFFFFFFu
#define MCM_CASFDR_PEFD_SHIFT          0u
#define MCM_CASFDR_PEFD_WIDTH          32u
#define MCM_CASFDR_PEFD(x)             (((uint32_t)(((uint32_t)(x))<<MCM_CASFDR_PEFD_SHIFT))&MCM_CASFDR_PEFD_MASK)
/* CASFDR Reg Mask */
#define MCM_CASFDR_MASK                0xFFFFFFFFu
/**
 * @}
 */ /* end of group MCM_Register_Masks */
/**
 * @}
 */ /* end of group MCM_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
