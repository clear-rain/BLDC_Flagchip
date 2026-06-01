#ifndef _MODULE_SCG_KJO_Ufdi43_REGS_H_
#define _MODULE_SCG_KJO_Ufdi43_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- SCG Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup SCG_Peripheral_Access_Layer SCG Peripheral Access Layer
 * @{
 */
/** SCG - Size of Registers Arrays */
/** SCG - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[16];
  __I  uint32_t CSR                           ; /* Clock Status Register, offset: 0x10 */
  __IO uint32_t CCR                           ; /* Clock Control Register, offset: 0x14 */
       uint8_t  RESERVED_1[8];
  __IO uint32_t CLKOUTCFG                     ; /* CLKOUT Configuration Register, offset: 0x20 */
#if SCG_LPWDG_SUPPORT
  __IO uint32_t SLPWDG                        ; /* Low Power Sleep WDOG Register, offset: 0x24 */
  __IO uint32_t WKPWDG                        ; /* Low Power Wakeup WDOG Register, offset: 0x28 */
  uint8_t  RESERVED_2[212];
#else
  uint8_t  RESERVED_2[220];
#endif
  __IO uint32_t FOSCCSR                       ; /* Fast OSC Control Status Register, offset: 0x100 */
  __IO uint32_t FOSCDIV                       ; /* Fast OSC Divide Register, offset: 0x104 */
  __IO uint32_t FOSCCFG                       ; /* Fast OSC Configuration Register, offset: 0x108 */
       uint8_t  RESERVED_3[244];
  __IO uint32_t SIRCCSR                       ; /* Slow IRC Control Status Register, offset: 0x200 */
  __IO uint32_t SIRCDIV                       ; /* Slow IRC Divide Register, offset: 0x204 */
       uint8_t  RESERVED_4[4];
  __IO uint32_t SIRCTCFG                      ; /* Slow IRC Auto Trim Configuration Register, offset: 0x20C */
       uint8_t  RESERVED_5[8];
  __IO uint32_t SIRCSTAT                      ; /* Slow IRC Software Trim Status Register, offset: 0x218 */
       uint8_t  RESERVED_6[228];
  __IO uint32_t FIRCCSR                       ; /* Fast IRC Control Status Register, offset: 0x300 */
  __IO uint32_t FIRCDIV                       ; /* Fast IRC Divide Register, offset: 0x304 */
  __IO uint32_t FIRCCFG                       ; /* Fast IRC Configuration Register, offset: 0x308 */
  __IO uint32_t FIRCTCFG                      ; /* Fast IRC Auto Trim Configuration Register, offset: 0x30C */
       uint8_t  RESERVED_7[8];
  __IO uint32_t FIRCSTAT                      ; /* Fast IRC Software Trim Status Register, offset: 0x318 */
       uint8_t  RESERVED_8[228];
  __IO uint32_t SOSCCSR                       ; /* Slow OSC Control Status Register, offset: 0x400 */
  __IO uint32_t SOSCCFG                       ; /* Slow OSC Configuration Register, offset: 0x404 */
       uint8_t  RESERVED_9[504];
  __IO uint32_t PLL0CSR                       ; /* PLL0 Control Status Register, offset: 0x600 */
  __IO uint32_t PLL0DIV                       ; /* PLL0 Divide Register, offset: 0x604 */
  __IO uint32_t PLL0CFG                       ; /* PLL0 Configuration Register, offset: 0x608 */
       uint8_t  RESERVED_10[244];
  __IO uint32_t SIRC32KCSR                    ; /* 32K Slow IRC Control Status Register, offset: 0x700 */
} SCG_Type, *SCG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- SCG Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup SCG_Register_Masks SCG Register Masks
 * @{
 */
 
/* CSR Bit Fields */
#define SCG_CSR_CCR_UPRD_MASK          0x80000000u
#define SCG_CSR_CCR_UPRD_SHIFT         31u
#define SCG_CSR_CCR_UPRD_WIDTH         1u
#define SCG_CSR_CCR_UPRD(x)            (((uint32_t)(((uint32_t)(x))<<SCG_CSR_CCR_UPRD_SHIFT))&SCG_CSR_CCR_UPRD_MASK)
#define SCG_CSR_SCS_MASK               0xF000000u
#define SCG_CSR_SCS_SHIFT              24u
#define SCG_CSR_SCS_WIDTH              4u
#define SCG_CSR_SCS(x)                 (((uint32_t)(((uint32_t)(x))<<SCG_CSR_SCS_SHIFT))&SCG_CSR_SCS_MASK)
#define SCG_CSR_DIVCORE_MASK           0xF0000u
#define SCG_CSR_DIVCORE_SHIFT          16u
#define SCG_CSR_DIVCORE_WIDTH          4u
#define SCG_CSR_DIVCORE(x)             (((uint32_t)(((uint32_t)(x))<<SCG_CSR_DIVCORE_SHIFT))&SCG_CSR_DIVCORE_MASK)
#define SCG_CSR_DIVBUS_MASK            0xF0u
#define SCG_CSR_DIVBUS_SHIFT           4u
#define SCG_CSR_DIVBUS_WIDTH           4u
#define SCG_CSR_DIVBUS(x)              (((uint32_t)(((uint32_t)(x))<<SCG_CSR_DIVBUS_SHIFT))&SCG_CSR_DIVBUS_MASK)
#define SCG_CSR_DIVSLOW_MASK           0xFu
#define SCG_CSR_DIVSLOW_SHIFT          0u
#define SCG_CSR_DIVSLOW_WIDTH          4u
#define SCG_CSR_DIVSLOW(x)             (((uint32_t)(((uint32_t)(x))<<SCG_CSR_DIVSLOW_SHIFT))&SCG_CSR_DIVSLOW_MASK)
/* CSR Reg Mask */
#define SCG_CSR_MASK                   0x8F0F00FFu
/* CCR Bit Fields */
#define SCG_CCR_SYSCLK_CME_MASK        0x80000000u
#define SCG_CCR_SYSCLK_CME_SHIFT       31u
#define SCG_CCR_SYSCLK_CME_WIDTH       1u
#define SCG_CCR_SYSCLK_CME(x)          (((uint32_t)(((uint32_t)(x))<<SCG_CCR_SYSCLK_CME_SHIFT))&SCG_CCR_SYSCLK_CME_MASK)
#define SCG_CCR_SCS_MASK               0xF000000u
#define SCG_CCR_SCS_SHIFT              24u
#define SCG_CCR_SCS_WIDTH              4u
#define SCG_CCR_SCS(x)                 (((uint32_t)(((uint32_t)(x))<<SCG_CCR_SCS_SHIFT))&SCG_CCR_SCS_MASK)
#define SCG_CCR_DIVCORE_MASK           0xF0000u
#define SCG_CCR_DIVCORE_SHIFT          16u
#define SCG_CCR_DIVCORE_WIDTH          4u
#define SCG_CCR_DIVCORE(x)             (((uint32_t)(((uint32_t)(x))<<SCG_CCR_DIVCORE_SHIFT))&SCG_CCR_DIVCORE_MASK)
#define SCG_CCR_DIVBUS_MASK            0xF0u
#define SCG_CCR_DIVBUS_SHIFT           4u
#define SCG_CCR_DIVBUS_WIDTH           4u
#define SCG_CCR_DIVBUS(x)              (((uint32_t)(((uint32_t)(x))<<SCG_CCR_DIVBUS_SHIFT))&SCG_CCR_DIVBUS_MASK)
#define SCG_CCR_DIVSLOW_MASK           0xFu
#define SCG_CCR_DIVSLOW_SHIFT          0u
#define SCG_CCR_DIVSLOW_WIDTH          4u
#define SCG_CCR_DIVSLOW(x)             (((uint32_t)(((uint32_t)(x))<<SCG_CCR_DIVSLOW_SHIFT))&SCG_CCR_DIVSLOW_MASK)
/* CCR Reg Mask */
#define SCG_CCR_MASK                   0x8F0F00FFu
/* CLKOUTCFG Bit Fields */
#define SCG_CLKOUTCFG_NVMCLK_FIRC_MASK 0x80000000u
#define SCG_CLKOUTCFG_NVMCLK_FIRC_SHIFT 31u
#define SCG_CLKOUTCFG_NVMCLK_FIRC_WIDTH 1u
#define SCG_CLKOUTCFG_NVMCLK_FIRC(x)   (((uint32_t)(((uint32_t)(x))<<SCG_CLKOUTCFG_NVMCLK_FIRC_SHIFT))&SCG_CLKOUTCFG_NVMCLK_FIRC_MASK)
#define SCG_CLKOUTCFG_NVMCLK_SIRC_MASK 0x40000000u
#define SCG_CLKOUTCFG_NVMCLK_SIRC_SHIFT 30u
#define SCG_CLKOUTCFG_NVMCLK_SIRC_WIDTH 1u
#define SCG_CLKOUTCFG_NVMCLK_SIRC(x)   (((uint32_t)(((uint32_t)(x))<<SCG_CLKOUTCFG_NVMCLK_SIRC_SHIFT))&SCG_CLKOUTCFG_NVMCLK_SIRC_MASK)
#define SCG_CLKOUTCFG_CLKOUTSEL_MASK   0xF000000u
#define SCG_CLKOUTCFG_CLKOUTSEL_SHIFT  24u
#define SCG_CLKOUTCFG_CLKOUTSEL_WIDTH  4u
#define SCG_CLKOUTCFG_CLKOUTSEL(x)     (((uint32_t)(((uint32_t)(x))<<SCG_CLKOUTCFG_CLKOUTSEL_SHIFT))&SCG_CLKOUTCFG_CLKOUTSEL_MASK)
/* CLKOUTCFG Reg Mask */
#define SCG_CLKOUTCFG_MASK             0xCF000000u

#if SCG_LPWDG_SUPPORT

/* SLPWDG Bit Fields */
#define SCG_SLPWDG_EN_MASK             0x80000000u
#define SCG_SLPWDG_EN_SHIFT            31u
#define SCG_SLPWDG_EN_WIDTH            1u
#define SCG_SLPWDG_EN(x)               (((uint32_t)(((uint32_t)(x))<<SCG_SLPWDG_EN_SHIFT))&SCG_SLPWDG_EN_MASK)
#define SCG_SLPWDG_MSB_MASK            0xFF0000u
#define SCG_SLPWDG_MSB_SHIFT           16u
#define SCG_SLPWDG_MSB_WIDTH           8u
#define SCG_SLPWDG_MSB(x)              (((uint32_t)(((uint32_t)(x))<<SCG_SLPWDG_MSB_SHIFT))&SCG_SLPWDG_MSB_MASK)
/* SLPWDG Reg Mask */
#define SCG_SLPWDG_MASK                0x80FF0000u
/* WKPWDG Bit Fields */
#define SCG_WKPWDG_EN_MASK             0x80000000u
#define SCG_WKPWDG_EN_SHIFT            31u
#define SCG_WKPWDG_EN_WIDTH            1u
#define SCG_WKPWDG_EN(x)               (((uint32_t)(((uint32_t)(x))<<SCG_WKPWDG_EN_SHIFT))&SCG_WKPWDG_EN_MASK)
#define SCG_WKPWDG_MSB_MASK            0xFF0000u
#define SCG_WKPWDG_MSB_SHIFT           16u
#define SCG_WKPWDG_MSB_WIDTH           8u
#define SCG_WKPWDG_MSB(x)              (((uint32_t)(((uint32_t)(x))<<SCG_WKPWDG_MSB_SHIFT))&SCG_WKPWDG_MSB_MASK)
/* WKPWDG Reg Mask */
#define SCG_WKPWDG_MASK                0x80FF0000u

#endif

/* FOSCCSR Bit Fields */
#define SCG_FOSCCSR_ERR_MASK           0x4000000u
#define SCG_FOSCCSR_ERR_SHIFT          26u
#define SCG_FOSCCSR_ERR_WIDTH          1u
#define SCG_FOSCCSR_ERR(x)             (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_ERR_SHIFT))&SCG_FOSCCSR_ERR_MASK)
#define SCG_FOSCCSR_SEL_MASK           0x2000000u
#define SCG_FOSCCSR_SEL_SHIFT          25u
#define SCG_FOSCCSR_SEL_WIDTH          1u
#define SCG_FOSCCSR_SEL(x)             (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_SEL_SHIFT))&SCG_FOSCCSR_SEL_MASK)
#define SCG_FOSCCSR_VLD_MASK           0x1000000u
#define SCG_FOSCCSR_VLD_SHIFT          24u
#define SCG_FOSCCSR_VLD_WIDTH          1u
#define SCG_FOSCCSR_VLD(x)             (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_VLD_SHIFT))&SCG_FOSCCSR_VLD_MASK)
#define SCG_FOSCCSR_LK_MASK            0x800000u
#define SCG_FOSCCSR_LK_SHIFT           23u
#define SCG_FOSCCSR_LK_WIDTH           1u
#define SCG_FOSCCSR_LK(x)              (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_LK_SHIFT))&SCG_FOSCCSR_LK_MASK)
#define SCG_FOSCCSR_CMRE_MASK          0x20000u
#define SCG_FOSCCSR_CMRE_SHIFT         17u
#define SCG_FOSCCSR_CMRE_WIDTH         1u
#define SCG_FOSCCSR_CMRE(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_CMRE_SHIFT))&SCG_FOSCCSR_CMRE_MASK)
#define SCG_FOSCCSR_CM_MASK            0x10000u
#define SCG_FOSCCSR_CM_SHIFT           16u
#define SCG_FOSCCSR_CM_WIDTH           1u
#define SCG_FOSCCSR_CM(x)              (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_CM_SHIFT))&SCG_FOSCCSR_CM_MASK)
#define SCG_FOSCCSR_STEN_MASK          0x2u
#define SCG_FOSCCSR_STEN_SHIFT         1u
#define SCG_FOSCCSR_STEN_WIDTH         1u
#define SCG_FOSCCSR_STEN(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_STEN_SHIFT))&SCG_FOSCCSR_STEN_MASK)
#define SCG_FOSCCSR_EN_MASK            0x1u
#define SCG_FOSCCSR_EN_SHIFT           0u
#define SCG_FOSCCSR_EN_WIDTH           1u
#define SCG_FOSCCSR_EN(x)              (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCSR_EN_SHIFT))&SCG_FOSCCSR_EN_MASK)
/* FOSCCSR Reg Mask */
#define SCG_FOSCCSR_MASK               0x07830003u
/* FOSCDIV Bit Fields */
#define SCG_FOSCDIV_DIVL_ACK_MASK      0x40000000u
#define SCG_FOSCDIV_DIVL_ACK_SHIFT     30u
#define SCG_FOSCDIV_DIVL_ACK_WIDTH     1u
#define SCG_FOSCDIV_DIVL_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVL_ACK_SHIFT))&SCG_FOSCDIV_DIVL_ACK_MASK)
#define SCG_FOSCDIV_DIVM_ACK_MASK      0x20000000u
#define SCG_FOSCDIV_DIVM_ACK_SHIFT     29u
#define SCG_FOSCDIV_DIVM_ACK_WIDTH     1u
#define SCG_FOSCDIV_DIVM_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVM_ACK_SHIFT))&SCG_FOSCDIV_DIVM_ACK_MASK)
#define SCG_FOSCDIV_DIVH_ACK_MASK      0x10000000u
#define SCG_FOSCDIV_DIVH_ACK_SHIFT     28u
#define SCG_FOSCDIV_DIVH_ACK_WIDTH     1u
#define SCG_FOSCDIV_DIVH_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVH_ACK_SHIFT))&SCG_FOSCDIV_DIVH_ACK_MASK)
#define SCG_FOSCDIV_DIVL_EN_MASK       0x4000000u
#define SCG_FOSCDIV_DIVL_EN_SHIFT      26u
#define SCG_FOSCDIV_DIVL_EN_WIDTH      1u
#define SCG_FOSCDIV_DIVL_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVL_EN_SHIFT))&SCG_FOSCDIV_DIVL_EN_MASK)
#define SCG_FOSCDIV_DIVM_EN_MASK       0x2000000u
#define SCG_FOSCDIV_DIVM_EN_SHIFT      25u
#define SCG_FOSCDIV_DIVM_EN_WIDTH      1u
#define SCG_FOSCDIV_DIVM_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVM_EN_SHIFT))&SCG_FOSCDIV_DIVM_EN_MASK)
#define SCG_FOSCDIV_DIVH_EN_MASK       0x1000000u
#define SCG_FOSCDIV_DIVH_EN_SHIFT      24u
#define SCG_FOSCDIV_DIVH_EN_WIDTH      1u
#define SCG_FOSCDIV_DIVH_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVH_EN_SHIFT))&SCG_FOSCDIV_DIVH_EN_MASK)
#define SCG_FOSCDIV_DIVL_MASK          0x70000u
#define SCG_FOSCDIV_DIVL_SHIFT         16u
#define SCG_FOSCDIV_DIVL_WIDTH         3u
#define SCG_FOSCDIV_DIVL(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVL_SHIFT))&SCG_FOSCDIV_DIVL_MASK)
#define SCG_FOSCDIV_DIVM_MASK          0x700u
#define SCG_FOSCDIV_DIVM_SHIFT         8u
#define SCG_FOSCDIV_DIVM_WIDTH         3u
#define SCG_FOSCDIV_DIVM(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVM_SHIFT))&SCG_FOSCDIV_DIVM_MASK)
#define SCG_FOSCDIV_DIVH_MASK          0x7u
#define SCG_FOSCDIV_DIVH_SHIFT         0u
#define SCG_FOSCDIV_DIVH_WIDTH         3u
#define SCG_FOSCDIV_DIVH(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FOSCDIV_DIVH_SHIFT))&SCG_FOSCDIV_DIVH_MASK)
/* FOSCDIV Reg Mask */
#define SCG_FOSCDIV_MASK               0x77070707u
/* FOSCCFG Bit Fields */
#define SCG_FOSCCFG_BYPASS_MASK        0x80000000u
#define SCG_FOSCCFG_BYPASS_SHIFT       31u
#define SCG_FOSCCFG_BYPASS_WIDTH       1u
#define SCG_FOSCCFG_BYPASS(x)          (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCFG_BYPASS_SHIFT))&SCG_FOSCCFG_BYPASS_MASK)
#define SCG_FOSCCFG_COMP_EN_MASK       0x1000000u
#define SCG_FOSCCFG_COMP_EN_SHIFT      24u
#define SCG_FOSCCFG_COMP_EN_WIDTH      1u
#define SCG_FOSCCFG_COMP_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCFG_COMP_EN_SHIFT))&SCG_FOSCCFG_COMP_EN_MASK)
#define SCG_FOSCCFG_EOCV_MASK          0xFF0000u
#define SCG_FOSCCFG_EOCV_SHIFT         16u
#define SCG_FOSCCFG_EOCV_WIDTH         8u
#define SCG_FOSCCFG_EOCV(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCFG_EOCV_SHIFT))&SCG_FOSCCFG_EOCV_MASK)
#define SCG_FOSCCFG_GM_SEL_MASK        0xF000u
#define SCG_FOSCCFG_GM_SEL_SHIFT       12u
#define SCG_FOSCCFG_GM_SEL_WIDTH       4u
#define SCG_FOSCCFG_GM_SEL(x)          (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCFG_GM_SEL_SHIFT))&SCG_FOSCCFG_GM_SEL_MASK)
#define SCG_FOSCCFG_ALC_D_MASK         0x800u
#define SCG_FOSCCFG_ALC_D_SHIFT        11u
#define SCG_FOSCCFG_ALC_D_WIDTH        1u
#define SCG_FOSCCFG_ALC_D(x)           (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCFG_ALC_D_SHIFT))&SCG_FOSCCFG_ALC_D_MASK)
#define SCG_FOSCCFG_HYST_D_MASK        0x400u
#define SCG_FOSCCFG_HYST_D_SHIFT       10u
#define SCG_FOSCCFG_HYST_D_WIDTH       1u
#define SCG_FOSCCFG_HYST_D(x)          (((uint32_t)(((uint32_t)(x))<<SCG_FOSCCFG_HYST_D_SHIFT))&SCG_FOSCCFG_HYST_D_MASK)
/* FOSCCFG Reg Mask */
#define SCG_FOSCCFG_MASK               0x81FFFC00u
/* SIRCCSR Bit Fields */
#define SCG_SIRCCSR_ERR_MASK           0x4000000u
#define SCG_SIRCCSR_ERR_SHIFT          26u
#define SCG_SIRCCSR_ERR_WIDTH          1u
#define SCG_SIRCCSR_ERR(x)             (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_ERR_SHIFT))&SCG_SIRCCSR_ERR_MASK)
#define SCG_SIRCCSR_VLD_MASK           0x1000000u
#define SCG_SIRCCSR_VLD_SHIFT          24u
#define SCG_SIRCCSR_VLD_WIDTH          1u
#define SCG_SIRCCSR_VLD(x)             (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_VLD_SHIFT))&SCG_SIRCCSR_VLD_MASK)
#define SCG_SIRCCSR_LK_MASK            0x800000u
#define SCG_SIRCCSR_LK_SHIFT           23u
#define SCG_SIRCCSR_LK_WIDTH           1u
#define SCG_SIRCCSR_LK(x)              (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_LK_SHIFT))&SCG_SIRCCSR_LK_MASK)
#define SCG_SIRCCSR_CM_MASK            0x10000u
#define SCG_SIRCCSR_CM_SHIFT           16u
#define SCG_SIRCCSR_CM_WIDTH           1u
#define SCG_SIRCCSR_CM(x)              (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_CM_SHIFT))&SCG_SIRCCSR_CM_MASK)
#define SCG_SIRCCSR_TRLK_MASK          0x400u
#define SCG_SIRCCSR_TRLK_SHIFT         10u
#define SCG_SIRCCSR_TRLK_WIDTH         1u
#define SCG_SIRCCSR_TRLK(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_TRLK_SHIFT))&SCG_SIRCCSR_TRLK_MASK)
#define SCG_SIRCCSR_TRUP_MASK          0x200u
#define SCG_SIRCCSR_TRUP_SHIFT         9u
#define SCG_SIRCCSR_TRUP_WIDTH         1u
#define SCG_SIRCCSR_TRUP(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_TRUP_SHIFT))&SCG_SIRCCSR_TRUP_MASK)
#define SCG_SIRCCSR_TREN_MASK          0x100u
#define SCG_SIRCCSR_TREN_SHIFT         8u
#define SCG_SIRCCSR_TREN_WIDTH         1u
#define SCG_SIRCCSR_TREN(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_TREN_SHIFT))&SCG_SIRCCSR_TREN_MASK)
#define SCG_SIRCCSR_LPEN_MASK          0x4u
#define SCG_SIRCCSR_LPEN_SHIFT         2u
#define SCG_SIRCCSR_LPEN_WIDTH         1u
#define SCG_SIRCCSR_LPEN(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_LPEN_SHIFT))&SCG_SIRCCSR_LPEN_MASK)
#define SCG_SIRCCSR_STEN_MASK          0x2u
#define SCG_SIRCCSR_STEN_SHIFT         1u
#define SCG_SIRCCSR_STEN_WIDTH         1u
#define SCG_SIRCCSR_STEN(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCCSR_STEN_SHIFT))&SCG_SIRCCSR_STEN_MASK)
/* SIRCCSR Reg Mask */
#define SCG_SIRCCSR_MASK               0x05810706u
/* SIRCDIV Bit Fields */
#define SCG_SIRCDIV_DIVL_ACK_MASK      0x40000000u
#define SCG_SIRCDIV_DIVL_ACK_SHIFT     30u
#define SCG_SIRCDIV_DIVL_ACK_WIDTH     1u
#define SCG_SIRCDIV_DIVL_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVL_ACK_SHIFT))&SCG_SIRCDIV_DIVL_ACK_MASK)
#define SCG_SIRCDIV_DIVM_ACK_MASK      0x20000000u
#define SCG_SIRCDIV_DIVM_ACK_SHIFT     29u
#define SCG_SIRCDIV_DIVM_ACK_WIDTH     1u
#define SCG_SIRCDIV_DIVM_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVM_ACK_SHIFT))&SCG_SIRCDIV_DIVM_ACK_MASK)
#define SCG_SIRCDIV_DIVH_ACK_MASK      0x10000000u
#define SCG_SIRCDIV_DIVH_ACK_SHIFT     28u
#define SCG_SIRCDIV_DIVH_ACK_WIDTH     1u
#define SCG_SIRCDIV_DIVH_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVH_ACK_SHIFT))&SCG_SIRCDIV_DIVH_ACK_MASK)
#define SCG_SIRCDIV_DIVL_EN_MASK       0x4000000u
#define SCG_SIRCDIV_DIVL_EN_SHIFT      26u
#define SCG_SIRCDIV_DIVL_EN_WIDTH      1u
#define SCG_SIRCDIV_DIVL_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVL_EN_SHIFT))&SCG_SIRCDIV_DIVL_EN_MASK)
#define SCG_SIRCDIV_DIVM_EN_MASK       0x2000000u
#define SCG_SIRCDIV_DIVM_EN_SHIFT      25u
#define SCG_SIRCDIV_DIVM_EN_WIDTH      1u
#define SCG_SIRCDIV_DIVM_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVM_EN_SHIFT))&SCG_SIRCDIV_DIVM_EN_MASK)
#define SCG_SIRCDIV_DIVH_EN_MASK       0x1000000u
#define SCG_SIRCDIV_DIVH_EN_SHIFT      24u
#define SCG_SIRCDIV_DIVH_EN_WIDTH      1u
#define SCG_SIRCDIV_DIVH_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVH_EN_SHIFT))&SCG_SIRCDIV_DIVH_EN_MASK)
#define SCG_SIRCDIV_DIVL_MASK          0x70000u
#define SCG_SIRCDIV_DIVL_SHIFT         16u
#define SCG_SIRCDIV_DIVL_WIDTH         3u
#define SCG_SIRCDIV_DIVL(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVL_SHIFT))&SCG_SIRCDIV_DIVL_MASK)
#define SCG_SIRCDIV_DIVM_MASK          0x700u
#define SCG_SIRCDIV_DIVM_SHIFT         8u
#define SCG_SIRCDIV_DIVM_WIDTH         3u
#define SCG_SIRCDIV_DIVM(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVM_SHIFT))&SCG_SIRCDIV_DIVM_MASK)
#define SCG_SIRCDIV_DIVH_MASK          0x7u
#define SCG_SIRCDIV_DIVH_SHIFT         0u
#define SCG_SIRCDIV_DIVH_WIDTH         3u
#define SCG_SIRCDIV_DIVH(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SIRCDIV_DIVH_SHIFT))&SCG_SIRCDIV_DIVH_MASK)
/* SIRCDIV Reg Mask */
#define SCG_SIRCDIV_MASK               0x77070707u
/* SIRCTCFG Bit Fields */
#define SCG_SIRCTCFG_TRIMDIV_MASK      0x7FF0000u
#define SCG_SIRCTCFG_TRIMDIV_SHIFT     16u
#define SCG_SIRCTCFG_TRIMDIV_WIDTH     11u
#define SCG_SIRCTCFG_TRIMDIV(x)        (((uint32_t)(((uint32_t)(x))<<SCG_SIRCTCFG_TRIMDIV_SHIFT))&SCG_SIRCTCFG_TRIMDIV_MASK)
#define SCG_SIRCTCFG_TRIMSRC_MASK      0x3u
#define SCG_SIRCTCFG_TRIMSRC_SHIFT     0u
#define SCG_SIRCTCFG_TRIMSRC_WIDTH     2u
#define SCG_SIRCTCFG_TRIMSRC(x)        (((uint32_t)(((uint32_t)(x))<<SCG_SIRCTCFG_TRIMSRC_SHIFT))&SCG_SIRCTCFG_TRIMSRC_MASK)
/* SIRCTCFG Reg Mask */
#define SCG_SIRCTCFG_MASK              0x07FF0003u
/* SIRCSTAT Bit Fields */
#define SCG_SIRCSTAT_TRIMFINE_MASK     0x3F00u
#define SCG_SIRCSTAT_TRIMFINE_SHIFT    8u
#define SCG_SIRCSTAT_TRIMFINE_WIDTH    6u
#define SCG_SIRCSTAT_TRIMFINE(x)       (((uint32_t)(((uint32_t)(x))<<SCG_SIRCSTAT_TRIMFINE_SHIFT))&SCG_SIRCSTAT_TRIMFINE_MASK)
#define SCG_SIRCSTAT_TRIMCOAR_MASK     0x3Fu
#define SCG_SIRCSTAT_TRIMCOAR_SHIFT    0u
#define SCG_SIRCSTAT_TRIMCOAR_WIDTH    6u
#define SCG_SIRCSTAT_TRIMCOAR(x)       (((uint32_t)(((uint32_t)(x))<<SCG_SIRCSTAT_TRIMCOAR_SHIFT))&SCG_SIRCSTAT_TRIMCOAR_MASK)
/* SIRCSTAT Reg Mask */
#define SCG_SIRCSTAT_MASK              0x00003F3Fu
/* FIRCCSR Bit Fields */
#define SCG_FIRCCSR_ERR_MASK           0x4000000u
#define SCG_FIRCCSR_ERR_SHIFT          26u
#define SCG_FIRCCSR_ERR_WIDTH          1u
#define SCG_FIRCCSR_ERR(x)             (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_ERR_SHIFT))&SCG_FIRCCSR_ERR_MASK)
#define SCG_FIRCCSR_SEL_MASK           0x2000000u
#define SCG_FIRCCSR_SEL_SHIFT          25u
#define SCG_FIRCCSR_SEL_WIDTH          1u
#define SCG_FIRCCSR_SEL(x)             (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_SEL_SHIFT))&SCG_FIRCCSR_SEL_MASK)
#define SCG_FIRCCSR_VLD_MASK           0x1000000u
#define SCG_FIRCCSR_VLD_SHIFT          24u
#define SCG_FIRCCSR_VLD_WIDTH          1u
#define SCG_FIRCCSR_VLD(x)             (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_VLD_SHIFT))&SCG_FIRCCSR_VLD_MASK)
#define SCG_FIRCCSR_LK_MASK            0x800000u
#define SCG_FIRCCSR_LK_SHIFT           23u
#define SCG_FIRCCSR_LK_WIDTH           1u
#define SCG_FIRCCSR_LK(x)              (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_LK_SHIFT))&SCG_FIRCCSR_LK_MASK)
#define SCG_FIRCCSR_CM_MASK            0x10000u
#define SCG_FIRCCSR_CM_SHIFT           16u
#define SCG_FIRCCSR_CM_WIDTH           1u
#define SCG_FIRCCSR_CM(x)              (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_CM_SHIFT))&SCG_FIRCCSR_CM_MASK)
#define SCG_FIRCCSR_TRLK_MASK          0x400u
#define SCG_FIRCCSR_TRLK_SHIFT         10u
#define SCG_FIRCCSR_TRLK_WIDTH         1u
#define SCG_FIRCCSR_TRLK(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_TRLK_SHIFT))&SCG_FIRCCSR_TRLK_MASK)
#define SCG_FIRCCSR_TRUP_MASK          0x200u
#define SCG_FIRCCSR_TRUP_SHIFT         9u
#define SCG_FIRCCSR_TRUP_WIDTH         1u
#define SCG_FIRCCSR_TRUP(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_TRUP_SHIFT))&SCG_FIRCCSR_TRUP_MASK)
#define SCG_FIRCCSR_TREN_MASK          0x100u
#define SCG_FIRCCSR_TREN_SHIFT         8u
#define SCG_FIRCCSR_TREN_WIDTH         1u
#define SCG_FIRCCSR_TREN(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_TREN_SHIFT))&SCG_FIRCCSR_TREN_MASK)
#define SCG_FIRCCSR_STEN_MASK          0x2u
#define SCG_FIRCCSR_STEN_SHIFT         1u
#define SCG_FIRCCSR_STEN_WIDTH         1u
#define SCG_FIRCCSR_STEN(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_STEN_SHIFT))&SCG_FIRCCSR_STEN_MASK)
#define SCG_FIRCCSR_EN_MASK            0x1u
#define SCG_FIRCCSR_EN_SHIFT           0u
#define SCG_FIRCCSR_EN_WIDTH           1u
#define SCG_FIRCCSR_EN(x)              (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCSR_EN_SHIFT))&SCG_FIRCCSR_EN_MASK)
/* FIRCCSR Reg Mask */
#define SCG_FIRCCSR_MASK               0x07810703u
/* FIRCDIV Bit Fields */
#define SCG_FIRCDIV_DIVL_ACK_MASK      0x40000000u
#define SCG_FIRCDIV_DIVL_ACK_SHIFT     30u
#define SCG_FIRCDIV_DIVL_ACK_WIDTH     1u
#define SCG_FIRCDIV_DIVL_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVL_ACK_SHIFT))&SCG_FIRCDIV_DIVL_ACK_MASK)
#define SCG_FIRCDIV_DIVM_ACK_MASK      0x20000000u
#define SCG_FIRCDIV_DIVM_ACK_SHIFT     29u
#define SCG_FIRCDIV_DIVM_ACK_WIDTH     1u
#define SCG_FIRCDIV_DIVM_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVM_ACK_SHIFT))&SCG_FIRCDIV_DIVM_ACK_MASK)
#define SCG_FIRCDIV_DIVH_ACK_MASK      0x10000000u
#define SCG_FIRCDIV_DIVH_ACK_SHIFT     28u
#define SCG_FIRCDIV_DIVH_ACK_WIDTH     1u
#define SCG_FIRCDIV_DIVH_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVH_ACK_SHIFT))&SCG_FIRCDIV_DIVH_ACK_MASK)
#define SCG_FIRCDIV_DIVL_EN_MASK       0x4000000u
#define SCG_FIRCDIV_DIVL_EN_SHIFT      26u
#define SCG_FIRCDIV_DIVL_EN_WIDTH      1u
#define SCG_FIRCDIV_DIVL_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVL_EN_SHIFT))&SCG_FIRCDIV_DIVL_EN_MASK)
#define SCG_FIRCDIV_DIVM_EN_MASK       0x2000000u
#define SCG_FIRCDIV_DIVM_EN_SHIFT      25u
#define SCG_FIRCDIV_DIVM_EN_WIDTH      1u
#define SCG_FIRCDIV_DIVM_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVM_EN_SHIFT))&SCG_FIRCDIV_DIVM_EN_MASK)
#define SCG_FIRCDIV_DIVH_EN_MASK       0x1000000u
#define SCG_FIRCDIV_DIVH_EN_SHIFT      24u
#define SCG_FIRCDIV_DIVH_EN_WIDTH      1u
#define SCG_FIRCDIV_DIVH_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVH_EN_SHIFT))&SCG_FIRCDIV_DIVH_EN_MASK)
#define SCG_FIRCDIV_DIVL_MASK          0x70000u
#define SCG_FIRCDIV_DIVL_SHIFT         16u
#define SCG_FIRCDIV_DIVL_WIDTH         3u
#define SCG_FIRCDIV_DIVL(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVL_SHIFT))&SCG_FIRCDIV_DIVL_MASK)
#define SCG_FIRCDIV_DIVM_MASK          0x700u
#define SCG_FIRCDIV_DIVM_SHIFT         8u
#define SCG_FIRCDIV_DIVM_WIDTH         3u
#define SCG_FIRCDIV_DIVM(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVM_SHIFT))&SCG_FIRCDIV_DIVM_MASK)
#define SCG_FIRCDIV_DIVH_MASK          0x7u
#define SCG_FIRCDIV_DIVH_SHIFT         0u
#define SCG_FIRCDIV_DIVH_WIDTH         3u
#define SCG_FIRCDIV_DIVH(x)            (((uint32_t)(((uint32_t)(x))<<SCG_FIRCDIV_DIVH_SHIFT))&SCG_FIRCDIV_DIVH_MASK)
/* FIRCDIV Reg Mask */
#define SCG_FIRCDIV_MASK               0x77070707u
/* FIRCCFG Bit Fields */
#define SCG_FIRCCFG_CLKEN_MASK         0x3u
#define SCG_FIRCCFG_CLKEN_SHIFT        0u
#define SCG_FIRCCFG_CLKEN_WIDTH        2u
#define SCG_FIRCCFG_CLKEN(x)           (((uint32_t)(((uint32_t)(x))<<SCG_FIRCCFG_CLKEN_SHIFT))&SCG_FIRCCFG_CLKEN_MASK)
/* FIRCCFG Reg Mask */
#define SCG_FIRCCFG_MASK               0x00000003u
/* FIRCTCFG Bit Fields */
#define SCG_FIRCTCFG_TRIMDIV_MASK      0x7FF0000u
#define SCG_FIRCTCFG_TRIMDIV_SHIFT     16u
#define SCG_FIRCTCFG_TRIMDIV_WIDTH     11u
#define SCG_FIRCTCFG_TRIMDIV(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FIRCTCFG_TRIMDIV_SHIFT))&SCG_FIRCTCFG_TRIMDIV_MASK)
#define SCG_FIRCTCFG_TRIMSRC_MASK      0x3u
#define SCG_FIRCTCFG_TRIMSRC_SHIFT     0u
#define SCG_FIRCTCFG_TRIMSRC_WIDTH     2u
#define SCG_FIRCTCFG_TRIMSRC(x)        (((uint32_t)(((uint32_t)(x))<<SCG_FIRCTCFG_TRIMSRC_SHIFT))&SCG_FIRCTCFG_TRIMSRC_MASK)
/* FIRCTCFG Reg Mask */
#define SCG_FIRCTCFG_MASK              0x07FF0003u
/* FIRCSTAT Bit Fields */
#define SCG_FIRCSTAT_TRIMCOAR_MASK     0x3F00u
#define SCG_FIRCSTAT_TRIMCOAR_SHIFT    8u
#define SCG_FIRCSTAT_TRIMCOAR_WIDTH    6u
#define SCG_FIRCSTAT_TRIMCOAR(x)       (((uint32_t)(((uint32_t)(x))<<SCG_FIRCSTAT_TRIMCOAR_SHIFT))&SCG_FIRCSTAT_TRIMCOAR_MASK)
#define SCG_FIRCSTAT_TRIMFINE_MASK     0xFFu
#define SCG_FIRCSTAT_TRIMFINE_SHIFT    0u
#define SCG_FIRCSTAT_TRIMFINE_WIDTH    8u
#define SCG_FIRCSTAT_TRIMFINE(x)       (((uint32_t)(((uint32_t)(x))<<SCG_FIRCSTAT_TRIMFINE_SHIFT))&SCG_FIRCSTAT_TRIMFINE_MASK)
/* FIRCSTAT Reg Mask */
#define SCG_FIRCSTAT_MASK              0x00003FFFu
/* SOSCCSR Bit Fields */
#define SCG_SOSCCSR_ERR_MASK           0x4000000u
#define SCG_SOSCCSR_ERR_SHIFT          26u
#define SCG_SOSCCSR_ERR_WIDTH          1u
#define SCG_SOSCCSR_ERR(x)             (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_ERR_SHIFT))&SCG_SOSCCSR_ERR_MASK)
#define SCG_SOSCCSR_VLD_MASK           0x1000000u
#define SCG_SOSCCSR_VLD_SHIFT          24u
#define SCG_SOSCCSR_VLD_WIDTH          1u
#define SCG_SOSCCSR_VLD(x)             (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_VLD_SHIFT))&SCG_SOSCCSR_VLD_MASK)
#define SCG_SOSCCSR_LK_MASK            0x800000u
#define SCG_SOSCCSR_LK_SHIFT           23u
#define SCG_SOSCCSR_LK_WIDTH           1u
#define SCG_SOSCCSR_LK(x)              (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_LK_SHIFT))&SCG_SOSCCSR_LK_MASK)
#define SCG_SOSCCSR_CMRE_MASK          0x20000u
#define SCG_SOSCCSR_CMRE_SHIFT         17u
#define SCG_SOSCCSR_CMRE_WIDTH         1u
#define SCG_SOSCCSR_CMRE(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_CMRE_SHIFT))&SCG_SOSCCSR_CMRE_MASK)
#define SCG_SOSCCSR_CM_MASK            0x10000u
#define SCG_SOSCCSR_CM_SHIFT           16u
#define SCG_SOSCCSR_CM_WIDTH           1u
#define SCG_SOSCCSR_CM(x)              (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_CM_SHIFT))&SCG_SOSCCSR_CM_MASK)
#define SCG_SOSCCSR_BYPASS_MASK        0x2u
#define SCG_SOSCCSR_BYPASS_SHIFT       1u
#define SCG_SOSCCSR_BYPASS_WIDTH       1u
#define SCG_SOSCCSR_BYPASS(x)          (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_BYPASS_SHIFT))&SCG_SOSCCSR_BYPASS_MASK)
#define SCG_SOSCCSR_EN_MASK            0x1u
#define SCG_SOSCCSR_EN_SHIFT           0u
#define SCG_SOSCCSR_EN_WIDTH           1u
#define SCG_SOSCCSR_EN(x)              (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCSR_EN_SHIFT))&SCG_SOSCCSR_EN_MASK)
/* SOSCCSR Reg Mask */
#define SCG_SOSCCSR_MASK               0x05830003u
/* SOSCCFG Bit Fields */
#define SCG_SOSCCFG_CURPRG_SF_MASK     0xC000000u
#define SCG_SOSCCFG_CURPRG_SF_SHIFT    26u
#define SCG_SOSCCFG_CURPRG_SF_WIDTH    2u
#define SCG_SOSCCFG_CURPRG_SF(x)       (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCFG_CURPRG_SF_SHIFT))&SCG_SOSCCFG_CURPRG_SF_MASK)
#define SCG_SOSCCFG_CURPRG_COMP_MASK   0x3000000u
#define SCG_SOSCCFG_CURPRG_COMP_SHIFT  24u
#define SCG_SOSCCFG_CURPRG_COMP_WIDTH  2u
#define SCG_SOSCCFG_CURPRG_COMP(x)     (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCFG_CURPRG_COMP_SHIFT))&SCG_SOSCCFG_CURPRG_COMP_MASK)
#define SCG_SOSCCFG_EOCV_MASK          0xFF0000u
#define SCG_SOSCCFG_EOCV_SHIFT         16u
#define SCG_SOSCCFG_EOCV_WIDTH         8u
#define SCG_SOSCCFG_EOCV(x)            (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCFG_EOCV_SHIFT))&SCG_SOSCCFG_EOCV_MASK)
#define SCG_SOSCCFG_GM_SEL_MASK        0xC0u
#define SCG_SOSCCFG_GM_SEL_SHIFT       6u
#define SCG_SOSCCFG_GM_SEL_WIDTH       2u
#define SCG_SOSCCFG_GM_SEL(x)          (((uint32_t)(((uint32_t)(x))<<SCG_SOSCCFG_GM_SEL_SHIFT))&SCG_SOSCCFG_GM_SEL_MASK)
/* SOSCCFG Reg Mask */
#define SCG_SOSCCFG_MASK               0x0FFF00C0u
/* PLL0CSR Bit Fields */
#define SCG_PLL0CSR_PLLLK_MASK         0x8000000u
#define SCG_PLL0CSR_PLLLK_SHIFT        27u
#define SCG_PLL0CSR_PLLLK_WIDTH        1u
#define SCG_PLL0CSR_PLLLK(x)           (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_PLLLK_SHIFT))&SCG_PLL0CSR_PLLLK_MASK)
#define SCG_PLL0CSR_ERR_MASK           0x4000000u
#define SCG_PLL0CSR_ERR_SHIFT          26u
#define SCG_PLL0CSR_ERR_WIDTH          1u
#define SCG_PLL0CSR_ERR(x)             (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_ERR_SHIFT))&SCG_PLL0CSR_ERR_MASK)
#define SCG_PLL0CSR_SEL_MASK           0x2000000u
#define SCG_PLL0CSR_SEL_SHIFT          25u
#define SCG_PLL0CSR_SEL_WIDTH          1u
#define SCG_PLL0CSR_SEL(x)             (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_SEL_SHIFT))&SCG_PLL0CSR_SEL_MASK)
#define SCG_PLL0CSR_VLD_MASK           0x1000000u
#define SCG_PLL0CSR_VLD_SHIFT          24u
#define SCG_PLL0CSR_VLD_WIDTH          1u
#define SCG_PLL0CSR_VLD(x)             (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_VLD_SHIFT))&SCG_PLL0CSR_VLD_MASK)
#define SCG_PLL0CSR_LK_MASK            0x800000u
#define SCG_PLL0CSR_LK_SHIFT           23u
#define SCG_PLL0CSR_LK_WIDTH           1u
#define SCG_PLL0CSR_LK(x)              (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_LK_SHIFT))&SCG_PLL0CSR_LK_MASK)
#define SCG_PLL0CSR_CMRE_MASK          0x20000u
#define SCG_PLL0CSR_CMRE_SHIFT         17u
#define SCG_PLL0CSR_CMRE_WIDTH         1u
#define SCG_PLL0CSR_CMRE(x)            (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_CMRE_SHIFT))&SCG_PLL0CSR_CMRE_MASK)
#define SCG_PLL0CSR_CM_MASK            0x10000u
#define SCG_PLL0CSR_CM_SHIFT           16u
#define SCG_PLL0CSR_CM_WIDTH           1u
#define SCG_PLL0CSR_CM(x)              (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_CM_SHIFT))&SCG_PLL0CSR_CM_MASK)
#define SCG_PLL0CSR_STEN_MASK          0x2u
#define SCG_PLL0CSR_STEN_SHIFT         1u
#define SCG_PLL0CSR_STEN_WIDTH         1u
#define SCG_PLL0CSR_STEN(x)            (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_STEN_SHIFT))&SCG_PLL0CSR_STEN_MASK)
#define SCG_PLL0CSR_EN_MASK            0x1u
#define SCG_PLL0CSR_EN_SHIFT           0u
#define SCG_PLL0CSR_EN_WIDTH           1u
#define SCG_PLL0CSR_EN(x)              (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CSR_EN_SHIFT))&SCG_PLL0CSR_EN_MASK)
/* PLL0CSR Reg Mask */
#define SCG_PLL0CSR_MASK               0x0F830003u
/* PLL0DIV Bit Fields */
#define SCG_PLL0DIV_DIVL_ACK_MASK      0x40000000u
#define SCG_PLL0DIV_DIVL_ACK_SHIFT     30u
#define SCG_PLL0DIV_DIVL_ACK_WIDTH     1u
#define SCG_PLL0DIV_DIVL_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVL_ACK_SHIFT))&SCG_PLL0DIV_DIVL_ACK_MASK)
#define SCG_PLL0DIV_DIVM_ACK_MASK      0x20000000u
#define SCG_PLL0DIV_DIVM_ACK_SHIFT     29u
#define SCG_PLL0DIV_DIVM_ACK_WIDTH     1u
#define SCG_PLL0DIV_DIVM_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVM_ACK_SHIFT))&SCG_PLL0DIV_DIVM_ACK_MASK)
#define SCG_PLL0DIV_DIVH_ACK_MASK      0x10000000u
#define SCG_PLL0DIV_DIVH_ACK_SHIFT     28u
#define SCG_PLL0DIV_DIVH_ACK_WIDTH     1u
#define SCG_PLL0DIV_DIVH_ACK(x)        (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVH_ACK_SHIFT))&SCG_PLL0DIV_DIVH_ACK_MASK)
#define SCG_PLL0DIV_DIVL_EN_MASK       0x4000000u
#define SCG_PLL0DIV_DIVL_EN_SHIFT      26u
#define SCG_PLL0DIV_DIVL_EN_WIDTH      1u
#define SCG_PLL0DIV_DIVL_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVL_EN_SHIFT))&SCG_PLL0DIV_DIVL_EN_MASK)
#define SCG_PLL0DIV_DIVM_EN_MASK       0x2000000u
#define SCG_PLL0DIV_DIVM_EN_SHIFT      25u
#define SCG_PLL0DIV_DIVM_EN_WIDTH      1u
#define SCG_PLL0DIV_DIVM_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVM_EN_SHIFT))&SCG_PLL0DIV_DIVM_EN_MASK)
#define SCG_PLL0DIV_DIVH_EN_MASK       0x1000000u
#define SCG_PLL0DIV_DIVH_EN_SHIFT      24u
#define SCG_PLL0DIV_DIVH_EN_WIDTH      1u
#define SCG_PLL0DIV_DIVH_EN(x)         (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVH_EN_SHIFT))&SCG_PLL0DIV_DIVH_EN_MASK)
#define SCG_PLL0DIV_DIVL_MASK          0x70000u
#define SCG_PLL0DIV_DIVL_SHIFT         16u
#define SCG_PLL0DIV_DIVL_WIDTH         3u
#define SCG_PLL0DIV_DIVL(x)            (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVL_SHIFT))&SCG_PLL0DIV_DIVL_MASK)
#define SCG_PLL0DIV_DIVM_MASK          0x700u
#define SCG_PLL0DIV_DIVM_SHIFT         8u
#define SCG_PLL0DIV_DIVM_WIDTH         3u
#define SCG_PLL0DIV_DIVM(x)            (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVM_SHIFT))&SCG_PLL0DIV_DIVM_MASK)
#define SCG_PLL0DIV_DIVH_MASK          0x7u
#define SCG_PLL0DIV_DIVH_SHIFT         0u
#define SCG_PLL0DIV_DIVH_WIDTH         3u
#define SCG_PLL0DIV_DIVH(x)            (((uint32_t)(((uint32_t)(x))<<SCG_PLL0DIV_DIVH_SHIFT))&SCG_PLL0DIV_DIVH_MASK)
/* PLL0DIV Reg Mask */
#define SCG_PLL0DIV_MASK               0x77070707u
/* PLL0CFG Bit Fields */
#if SCG_POSTDIV_SUPPORT  /* FC41501MS */
    #define SCG_PLL0CFG_MULT_MASK          0xFF0000u
    #define SCG_PLL0CFG_MULT_SHIFT         16u
    #define SCG_PLL0CFG_MULT_WIDTH         8u
    #define SCG_PLL0CFG_MULT(x)            (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CFG_MULT_SHIFT))&SCG_PLL0CFG_MULT_MASK)
    #define SCG_PLL0CFG_PREDIV_MASK        0x1F00u
    #define SCG_PLL0CFG_PREDIV_SHIFT       8u
    #define SCG_PLL0CFG_PREDIV_WIDTH       5u
    #define SCG_PLL0CFG_PREDIV(x)          (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CFG_PREDIV_SHIFT))&SCG_PLL0CFG_PREDIV_MASK)
    #define SCG_PLL0CFG_PSTDIV_MASK        0x30u
    #define SCG_PLL0CFG_PSTDIV_SHIFT       4u
    #define SCG_PLL0CFG_PSTDIV(x) (((uint32_t)(((uint32_t)(x))<<SCG_PLLCFG_PSTDIV_SHIFT))&SCG_PLLCFG_PSTDIV_MASK)
#else
    #define SCG_PLL0CFG_MULT_MASK          0x3F0000u
    #define SCG_PLL0CFG_MULT_SHIFT         16u
    #define SCG_PLL0CFG_MULT_WIDTH         6u
    #define SCG_PLL0CFG_MULT(x)            (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CFG_MULT_SHIFT))&SCG_PLL0CFG_MULT_MASK)
    #define SCG_PLL0CFG_PREDIV_MASK        0xF00u
    #define SCG_PLL0CFG_PREDIV_SHIFT       8u
    #define SCG_PLL0CFG_PREDIV_WIDTH       4u
    #define SCG_PLL0CFG_PREDIV(x)          (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CFG_PREDIV_SHIFT))&SCG_PLL0CFG_PREDIV_MASK)
#endif

#define SCG_PLL0CFG_SOURCE_MASK        0x1u
#define SCG_PLL0CFG_SOURCE_SHIFT       0u
#define SCG_PLL0CFG_SOURCE_WIDTH       1u
#define SCG_PLL0CFG_SOURCE(x)          (((uint32_t)(((uint32_t)(x))<<SCG_PLL0CFG_SOURCE_SHIFT))&SCG_PLL0CFG_SOURCE_MASK)
/* PLL0CFG Reg Mask */
#define SCG_PLL0CFG_MASK               0x003F0F01u
/* SIRC32KCSR Bit Fields */
#define SCG_SIRC32KCSR_VLD_MASK        0x1000000u
#define SCG_SIRC32KCSR_VLD_SHIFT       24u
#define SCG_SIRC32KCSR_VLD_WIDTH       1u
#define SCG_SIRC32KCSR_VLD(x)          (((uint32_t)(((uint32_t)(x))<<SCG_SIRC32KCSR_VLD_SHIFT))&SCG_SIRC32KCSR_VLD_MASK)
#define SCG_SIRC32KCSR_LK_MASK         0x800000u
#define SCG_SIRC32KCSR_LK_SHIFT        23u
#define SCG_SIRC32KCSR_LK_WIDTH        1u
#define SCG_SIRC32KCSR_LK(x)           (((uint32_t)(((uint32_t)(x))<<SCG_SIRC32KCSR_LK_SHIFT))&SCG_SIRC32KCSR_LK_MASK)
#define SCG_SIRC32KCSR_EN_MASK         0x1u
#define SCG_SIRC32KCSR_EN_SHIFT        0u
#define SCG_SIRC32KCSR_EN_WIDTH        1u
#define SCG_SIRC32KCSR_EN(x)           (((uint32_t)(((uint32_t)(x))<<SCG_SIRC32KCSR_EN_SHIFT))&SCG_SIRC32KCSR_EN_MASK)
/* SIRC32KCSR Reg Mask */
#define SCG_SIRC32KCSR_MASK            0x01800001u
/**
 * @}
 */ /* end of group SCG_Register_Masks */
/**
 * @}
 */ /* end of group SCG_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
