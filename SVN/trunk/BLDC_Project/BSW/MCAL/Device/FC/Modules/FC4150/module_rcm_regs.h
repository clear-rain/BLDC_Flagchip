#ifndef _MODULE_RCM_KJO_Ufdi20_REGS_H_
#define _MODULE_RCM_KJO_Ufdi20_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- RCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup RCM_Peripheral_Access_Layer RCM Peripheral Access Layer
 * @{
 */
/** RCM - Size of Registers Arrays */
/** RCM - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[8];
  __IO uint32_t SRS                           ; /* System Reset Status Register, offset: 0x8 */
  __IO uint32_t RSTFLT                        ; /* Reset Pin Filter Register, offset: 0xC */
       uint8_t  RESERVED_1[8];
  __IO uint32_t SSRS                          ; /* Sticky System Reset Status Register, offset: 0x18 */
  __IO uint32_t SRIE                          ; /* System Reset Interrupt Enable Register, offset: 0x1C */
} RCM_Type, *RCM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- RCM Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup RCM_Register_Masks RCM Register Masks
 * @{
 */
 
/* SRS Bit Fields */
#define RCM_SRS_SACKERR_MASK           0x2000u
#define RCM_SRS_SACKERR_SHIFT          13u
#define RCM_SRS_SACKERR_WIDTH          1u
#define RCM_SRS_SACKERR(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SRS_SACKERR_SHIFT))&RCM_SRS_SACKERR_MASK)
#define RCM_SRS_INTM_TOUT_MASK         0x1000u
#define RCM_SRS_INTM_TOUT_SHIFT        12u
#define RCM_SRS_INTM_TOUT_WIDTH        1u
#define RCM_SRS_INTM_TOUT(x)           (((uint32_t)(((uint32_t)(x))<<RCM_SRS_INTM_TOUT_SHIFT))&RCM_SRS_INTM_TOUT_MASK)
#define RCM_SRS_SYSAP_MASK             0x800u
#define RCM_SRS_SYSAP_SHIFT            11u
#define RCM_SRS_SYSAP_WIDTH            1u
#define RCM_SRS_SYSAP(x)               (((uint32_t)(((uint32_t)(x))<<RCM_SRS_SYSAP_SHIFT))&RCM_SRS_SYSAP_MASK)
#define RCM_SRS_SW_MASK                0x400u
#define RCM_SRS_SW_SHIFT               10u
#define RCM_SRS_SW_WIDTH               1u
#define RCM_SRS_SW(x)                  (((uint32_t)(((uint32_t)(x))<<RCM_SRS_SW_SHIFT))&RCM_SRS_SW_MASK)
#define RCM_SRS_CPULOC_MASK            0x200u
#define RCM_SRS_CPULOC_SHIFT           9u
#define RCM_SRS_CPULOC_WIDTH           1u
#define RCM_SRS_CPULOC(x)              (((uint32_t)(((uint32_t)(x))<<RCM_SRS_CPULOC_SHIFT))&RCM_SRS_CPULOC_MASK)
#define RCM_SRS_JTAG_MASK              0x100u
#define RCM_SRS_JTAG_SHIFT             8u
#define RCM_SRS_JTAG_WIDTH             1u
#define RCM_SRS_JTAG(x)                (((uint32_t)(((uint32_t)(x))<<RCM_SRS_JTAG_SHIFT))&RCM_SRS_JTAG_MASK)
#define RCM_SRS_POR_MASK               0x80u
#define RCM_SRS_POR_SHIFT              7u
#define RCM_SRS_POR_WIDTH              1u
#define RCM_SRS_POR(x)                 (((uint32_t)(((uint32_t)(x))<<RCM_SRS_POR_SHIFT))&RCM_SRS_POR_MASK)
#define RCM_SRS_PIN_MASK               0x40u
#define RCM_SRS_PIN_SHIFT              6u
#define RCM_SRS_PIN_WIDTH              1u
#define RCM_SRS_PIN(x)                 (((uint32_t)(((uint32_t)(x))<<RCM_SRS_PIN_SHIFT))&RCM_SRS_PIN_MASK)
#define RCM_SRS_WDG0_MASK              0x20u
#define RCM_SRS_WDG0_SHIFT             5u
#define RCM_SRS_WDG0_WIDTH             1u
#define RCM_SRS_WDG0(x)                (((uint32_t)(((uint32_t)(x))<<RCM_SRS_WDG0_SHIFT))&RCM_SRS_WDG0_MASK)
#define RCM_SRS_WDG1_MASK              0x10u
#define RCM_SRS_WDG1_SHIFT             4u
#define RCM_SRS_WDG1_WIDTH             1u
#define RCM_SRS_WDG1(x)                (((uint32_t)(((uint32_t)(x))<<RCM_SRS_WDG1_SHIFT))&RCM_SRS_WDG1_MASK)
#define RCM_SRS_CLKERR0_MASK           0x8u
#define RCM_SRS_CLKERR0_SHIFT          3u
#define RCM_SRS_CLKERR0_WIDTH          1u
#define RCM_SRS_CLKERR0(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SRS_CLKERR0_SHIFT))&RCM_SRS_CLKERR0_MASK)
#define RCM_SRS_CLKERR1_MASK           0x4u
#define RCM_SRS_CLKERR1_SHIFT          2u
#define RCM_SRS_CLKERR1_WIDTH          1u
#define RCM_SRS_CLKERR1(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SRS_CLKERR1_SHIFT))&RCM_SRS_CLKERR1_MASK)
#define RCM_SRS_LVD_MASK               0x2u
#define RCM_SRS_LVD_SHIFT              1u
#define RCM_SRS_LVD_WIDTH              1u
#define RCM_SRS_LVD(x)                 (((uint32_t)(((uint32_t)(x))<<RCM_SRS_LVD_SHIFT))&RCM_SRS_LVD_MASK)
#define RCM_SRS_WAKEUP_MASK            0x1u
#define RCM_SRS_WAKEUP_SHIFT           0u
#define RCM_SRS_WAKEUP_WIDTH           1u
#define RCM_SRS_WAKEUP(x)              (((uint32_t)(((uint32_t)(x))<<RCM_SRS_WAKEUP_SHIFT))&RCM_SRS_WAKEUP_MASK)
/* SRS Reg Mask */
#define RCM_SRS_MASK                   0x00003FFFu
/* RSTFLT Bit Fields */
#define RCM_RSTFLT_RSTFLT_BUSW_MASK    0x1F00u
#define RCM_RSTFLT_RSTFLT_BUSW_SHIFT   8u
#define RCM_RSTFLT_RSTFLT_BUSW_WIDTH   5u
#define RCM_RSTFLT_RSTFLT_BUSW(x)      (((uint32_t)(((uint32_t)(x))<<RCM_RSTFLT_RSTFLT_BUSW_SHIFT))&RCM_RSTFLT_RSTFLT_BUSW_MASK)
#define RCM_RSTFLT_RSTFLT_AON_LP_MASK  0x4u
#define RCM_RSTFLT_RSTFLT_AON_LP_SHIFT 2u
#define RCM_RSTFLT_RSTFLT_AON_LP_WIDTH 1u
#define RCM_RSTFLT_RSTFLT_AON_LP(x)    (((uint32_t)(((uint32_t)(x))<<RCM_RSTFLT_RSTFLT_AON_LP_SHIFT))&RCM_RSTFLT_RSTFLT_AON_LP_MASK)
#define RCM_RSTFLT_RSTFLT_AON_MASK     0x2u
#define RCM_RSTFLT_RSTFLT_AON_SHIFT    1u
#define RCM_RSTFLT_RSTFLT_AON_WIDTH    1u
#define RCM_RSTFLT_RSTFLT_AON(x)       (((uint32_t)(((uint32_t)(x))<<RCM_RSTFLT_RSTFLT_AON_SHIFT))&RCM_RSTFLT_RSTFLT_AON_MASK)
#define RCM_RSTFLT_RSTFLT_BUS_MASK     0x1u
#define RCM_RSTFLT_RSTFLT_BUS_SHIFT    0u
#define RCM_RSTFLT_RSTFLT_BUS_WIDTH    1u
#define RCM_RSTFLT_RSTFLT_BUS(x)       (((uint32_t)(((uint32_t)(x))<<RCM_RSTFLT_RSTFLT_BUS_SHIFT))&RCM_RSTFLT_RSTFLT_BUS_MASK)
/* RSTFLT Reg Mask */
#define RCM_RSTFLT_MASK                0x00001F07u
/* SSRS Bit Fields */
#define RCM_SSRS_SACKERR_ST_MASK       0x2000u
#define RCM_SSRS_SACKERR_ST_SHIFT      13u
#define RCM_SSRS_SACKERR_ST_WIDTH      1u
#define RCM_SSRS_SACKERR_ST(x)         (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_SACKERR_ST_SHIFT))&RCM_SSRS_SACKERR_ST_MASK)
#define RCM_SSRS_INTM_TOUT_ST_MASK     0x1000u
#define RCM_SSRS_INTM_TOUT_ST_SHIFT    12u
#define RCM_SSRS_INTM_TOUT_ST_WIDTH    1u
#define RCM_SSRS_INTM_TOUT_ST(x)       (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_INTM_TOUT_ST_SHIFT))&RCM_SSRS_INTM_TOUT_ST_MASK)
#define RCM_SSRS_SYSAP_ST_MASK         0x800u
#define RCM_SSRS_SYSAP_ST_SHIFT        11u
#define RCM_SSRS_SYSAP_ST_WIDTH        1u
#define RCM_SSRS_SYSAP_ST(x)           (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_SYSAP_ST_SHIFT))&RCM_SSRS_SYSAP_ST_MASK)
#define RCM_SSRS__SW_ST_MASK           0x400u
#define RCM_SSRS__SW_ST_SHIFT          10u
#define RCM_SSRS__SW_ST_WIDTH          1u
#define RCM_SSRS__SW_ST(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SSRS__SW_ST_SHIFT))&RCM_SSRS__SW_ST_MASK)
#define RCM_SSRS_CPULOC_ST_MASK        0x200u
#define RCM_SSRS_CPULOC_ST_SHIFT       9u
#define RCM_SSRS_CPULOC_ST_WIDTH       1u
#define RCM_SSRS_CPULOC_ST(x)          (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_CPULOC_ST_SHIFT))&RCM_SSRS_CPULOC_ST_MASK)
#define RCM_SSRS_JTAG_ST_MASK          0x100u
#define RCM_SSRS_JTAG_ST_SHIFT         8u
#define RCM_SSRS_JTAG_ST_WIDTH         1u
#define RCM_SSRS_JTAG_ST(x)            (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_JTAG_ST_SHIFT))&RCM_SSRS_JTAG_ST_MASK)
#define RCM_SSRS_POR_ST_MASK           0x80u
#define RCM_SSRS_POR_ST_SHIFT          7u
#define RCM_SSRS_POR_ST_WIDTH          1u
#define RCM_SSRS_POR_ST(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_POR_ST_SHIFT))&RCM_SSRS_POR_ST_MASK)
#define RCM_SSRS_PIN_ST_MASK           0x40u
#define RCM_SSRS_PIN_ST_SHIFT          6u
#define RCM_SSRS_PIN_ST_WIDTH          1u
#define RCM_SSRS_PIN_ST(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_PIN_ST_SHIFT))&RCM_SSRS_PIN_ST_MASK)
#define RCM_SSRS_WDG0_ST_MASK          0x20u
#define RCM_SSRS_WDG0_ST_SHIFT         5u
#define RCM_SSRS_WDG0_ST_WIDTH         1u
#define RCM_SSRS_WDG0_ST(x)            (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_WDG0_ST_SHIFT))&RCM_SSRS_WDG0_ST_MASK)
#define RCM_SSRS_WDG1_ST_MASK          0x10u
#define RCM_SSRS_WDG1_ST_SHIFT         4u
#define RCM_SSRS_WDG1_ST_WIDTH         1u
#define RCM_SSRS_WDG1_ST(x)            (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_WDG1_ST_SHIFT))&RCM_SSRS_WDG1_ST_MASK)
#define RCM_SSRS_CLKERR0_ST_MASK       0x8u
#define RCM_SSRS_CLKERR0_ST_SHIFT      3u
#define RCM_SSRS_CLKERR0_ST_WIDTH      1u
#define RCM_SSRS_CLKERR0_ST(x)         (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_CLKERR0_ST_SHIFT))&RCM_SSRS_CLKERR0_ST_MASK)
#define RCM_SSRS_CLKERR1_ST_MASK       0x4u
#define RCM_SSRS_CLKERR1_ST_SHIFT      2u
#define RCM_SSRS_CLKERR1_ST_WIDTH      1u
#define RCM_SSRS_CLKERR1_ST(x)         (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_CLKERR1_ST_SHIFT))&RCM_SSRS_CLKERR1_ST_MASK)
#define RCM_SSRS_LVD_ST_MASK           0x2u
#define RCM_SSRS_LVD_ST_SHIFT          1u
#define RCM_SSRS_LVD_ST_WIDTH          1u
#define RCM_SSRS_LVD_ST(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_LVD_ST_SHIFT))&RCM_SSRS_LVD_ST_MASK)
#define RCM_SSRS_WAKEUP_ST_MASK        0x1u
#define RCM_SSRS_WAKEUP_ST_SHIFT       0u
#define RCM_SSRS_WAKEUP_ST_WIDTH       1u
#define RCM_SSRS_WAKEUP_ST(x)          (((uint32_t)(((uint32_t)(x))<<RCM_SSRS_WAKEUP_ST_SHIFT))&RCM_SSRS_WAKEUP_ST_MASK)
/* SSRS Reg Mask */
#define RCM_SSRS_MASK                  0x00003FFFu
/* SRIE Bit Fields */
#define RCM_SRIE_SACKERR_RIE_MASK      0x2000u
#define RCM_SRIE_SACKERR_RIE_SHIFT     13u
#define RCM_SRIE_SACKERR_RIE_WIDTH     1u
#define RCM_SRIE_SACKERR_RIE(x)        (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_SACKERR_RIE_SHIFT))&RCM_SRIE_SACKERR_RIE_MASK)
#define RCM_SRIE_INTM_TOUT_RIE_MASK    0x1000u
#define RCM_SRIE_INTM_TOUT_RIE_SHIFT   12u
#define RCM_SRIE_INTM_TOUT_RIE_WIDTH   1u
#define RCM_SRIE_INTM_TOUT_RIE(x)      (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_INTM_TOUT_RIE_SHIFT))&RCM_SRIE_INTM_TOUT_RIE_MASK)
#define RCM_SRIE_SYSAP_RIE_MASK        0x800u
#define RCM_SRIE_SYSAP_RIE_SHIFT       11u
#define RCM_SRIE_SYSAP_RIE_WIDTH       1u
#define RCM_SRIE_SYSAP_RIE(x)          (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_SYSAP_RIE_SHIFT))&RCM_SRIE_SYSAP_RIE_MASK)
#define RCM_SRIE_SW_RIE_MASK           0x400u
#define RCM_SRIE_SW_RIE_SHIFT          10u
#define RCM_SRIE_SW_RIE_WIDTH          1u
#define RCM_SRIE_SW_RIE(x)             (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_SW_RIE_SHIFT))&RCM_SRIE_SW_RIE_MASK)
#define RCM_SRIE_CPULOC_RIE_MASK       0x200u
#define RCM_SRIE_CPULOC_RIE_SHIFT      9u
#define RCM_SRIE_CPULOC_RIE_WIDTH      1u
#define RCM_SRIE_CPULOC_RIE(x)         (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_CPULOC_RIE_SHIFT))&RCM_SRIE_CPULOC_RIE_MASK)
#define RCM_SRIE_JTAG_RIE_MASK         0x100u
#define RCM_SRIE_JTAG_RIE_SHIFT        8u
#define RCM_SRIE_JTAG_RIE_WIDTH        1u
#define RCM_SRIE_JTAG_RIE(x)           (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_JTAG_RIE_SHIFT))&RCM_SRIE_JTAG_RIE_MASK)
#define RCM_SRIE_GLOBAL_RIE_MASK       0x80u
#define RCM_SRIE_GLOBAL_RIE_SHIFT      7u
#define RCM_SRIE_GLOBAL_RIE_WIDTH      1u
#define RCM_SRIE_GLOBAL_RIE(x)         (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_GLOBAL_RIE_SHIFT))&RCM_SRIE_GLOBAL_RIE_MASK)
#define RCM_SRIE_PIN_RIE_MASK          0x40u
#define RCM_SRIE_PIN_RIE_SHIFT         6u
#define RCM_SRIE_PIN_RIE_WIDTH         1u
#define RCM_SRIE_PIN_RIE(x)            (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_PIN_RIE_SHIFT))&RCM_SRIE_PIN_RIE_MASK)
#define RCM_SRIE_WDG0_RIE_MASK         0x20u
#define RCM_SRIE_WDG0_RIE_SHIFT        5u
#define RCM_SRIE_WDG0_RIE_WIDTH        1u
#define RCM_SRIE_WDG0_RIE(x)           (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_WDG0_RIE_SHIFT))&RCM_SRIE_WDG0_RIE_MASK)
#define RCM_SRIE_WDG1_RIE_MASK         0x10u
#define RCM_SRIE_WDG1_RIE_SHIFT        4u
#define RCM_SRIE_WDG1_RIE_WIDTH        1u
#define RCM_SRIE_WDG1_RIE(x)           (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_WDG1_RIE_SHIFT))&RCM_SRIE_WDG1_RIE_MASK)
#define RCM_SRIE_CLKERR0_RIE_MASK      0x8u
#define RCM_SRIE_CLKERR0_RIE_SHIFT     3u
#define RCM_SRIE_CLKERR0_RIE_WIDTH     1u
#define RCM_SRIE_CLKERR0_RIE(x)        (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_CLKERR0_RIE_SHIFT))&RCM_SRIE_CLKERR0_RIE_MASK)
#define RCM_SRIE_CLKERR1_RIE_MASK      0x4u
#define RCM_SRIE_CLKERR1_RIE_SHIFT     2u
#define RCM_SRIE_CLKERR1_RIE_WIDTH     1u
#define RCM_SRIE_CLKERR1_RIE(x)        (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_CLKERR1_RIE_SHIFT))&RCM_SRIE_CLKERR1_RIE_MASK)
#define RCM_SRIE_DELAY_MASK            0x3u
#define RCM_SRIE_DELAY_SHIFT           0u
#define RCM_SRIE_DELAY_WIDTH           2u
#define RCM_SRIE_DELAY(x)              (((uint32_t)(((uint32_t)(x))<<RCM_SRIE_DELAY_SHIFT))&RCM_SRIE_DELAY_MASK)
/* SRIE Reg Mask */
#define RCM_SRIE_MASK                  0x00003FFFu
/**
 * @}
 */ /* end of group RCM_Register_Masks */
/**
 * @}
 */ /* end of group RCM_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
