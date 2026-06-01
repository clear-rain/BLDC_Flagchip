#ifndef _MODULE_PMC_KJO_Ufdi12_REGS_H_
#define _MODULE_PMC_KJO_Ufdi12_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- PMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup PMC_Peripheral_Access_Layer PMC Peripheral Access Layer
 * @{
 */
/** PMC - Size of Registers Arrays */
/** PMC - Register Layout Typedef */
typedef struct {
  __IO uint32_t LVSCR                         ; /* Low Voltage Status and Control Register, offset: 0x0 */
  __IO uint32_t CONFIG                        ; /* PMC Configuration Register, offset: 0x4 */
} PMC_Type, *PMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PMC Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup PMC_Register_Masks PMC Register Masks
 * @{
 */
 
/* LVSCR Bit Fields */
#define PMC_LVSCR_POR_FLAG_MASK        0x80000000u
#define PMC_LVSCR_POR_FLAG_SHIFT       31u
#define PMC_LVSCR_POR_FLAG_WIDTH       1u
#define PMC_LVSCR_POR_FLAG(x)          (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_POR_FLAG_SHIFT))&PMC_LVSCR_POR_FLAG_MASK)
#define PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK 0x800000u
#define PMC_LVSCR_LVR1P1V_RPM_FLAG_SHIFT 23u
#define PMC_LVSCR_LVR1P1V_RPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR1P1V_RPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR1P1V_RPM_FLAG_SHIFT))&PMC_LVSCR_LVR1P1V_RPM_FLAG_MASK)
#define PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK 0x400000u
#define PMC_LVSCR_LVR1P1V_FPM_FLAG_SHIFT 22u
#define PMC_LVSCR_LVR1P1V_FPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR1P1V_FPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR1P1V_FPM_FLAG_SHIFT))&PMC_LVSCR_LVR1P1V_FPM_FLAG_MASK)
#define PMC_LVSCR_HVD1P1V_STATUS_MASK  0x800u
#define PMC_LVSCR_HVD1P1V_STATUS_SHIFT 11u
#define PMC_LVSCR_HVD1P1V_STATUS_WIDTH 1u
#define PMC_LVSCR_HVD1P1V_STATUS(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD1P1V_STATUS_SHIFT))&PMC_LVSCR_HVD1P1V_STATUS_MASK)
#define PMC_LVSCR_HVD1P1V_FLAG_MASK    0x8u
#define PMC_LVSCR_HVD1P1V_FLAG_SHIFT   3u
#define PMC_LVSCR_HVD1P1V_FLAG_WIDTH   1u
#define PMC_LVSCR_HVD1P1V_FLAG(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD1P1V_FLAG_SHIFT))&PMC_LVSCR_HVD1P1V_FLAG_MASK)

#if PMC_V25_SUPPORT
#define PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK 0x200000u
#define PMC_LVSCR_LVR2P5V_RPM_FLAG_SHIFT 21u
#define PMC_LVSCR_LVR2P5V_RPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR2P5V_RPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR2P5V_RPM_FLAG_SHIFT))&PMC_LVSCR_LVR2P5V_RPM_FLAG_MASK)
#define PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK 0x100000u
#define PMC_LVSCR_LVR2P5V_FPM_FLAG_SHIFT 20u
#define PMC_LVSCR_LVR2P5V_FPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR2P5V_FPM_FLAG(x)  (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR2P5V_FPM_FLAG_SHIFT))&PMC_LVSCR_LVR2P5V_FPM_FLAG_MASK)
#define PMC_LVSCR_HVD2P5V_STATUS_MASK  0x400u
#define PMC_LVSCR_HVD2P5V_STATUS_SHIFT 10u
#define PMC_LVSCR_HVD2P5V_STATUS_WIDTH 1u
#define PMC_LVSCR_HVD2P5V_STATUS(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD2P5V_STATUS_SHIFT))&PMC_LVSCR_HVD2P5V_STATUS_MASK)
#define PMC_LVSCR_HVD2P5V_FLAG_MASK    0x4u
#define PMC_LVSCR_HVD2P5V_FLAG_SHIFT   2u
#define PMC_LVSCR_HVD2P5V_FLAG_WIDTH   1u
#define PMC_LVSCR_HVD2P5V_FLAG(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD2P5V_FLAG_SHIFT))&PMC_LVSCR_HVD2P5V_FLAG_MASK)
#endif

#if PMC_V3_SUPPORT
#define PMC_LVSCR_LVR3V_RPM_FLAG_MASK  0x20000u
#define PMC_LVSCR_LVR3V_RPM_FLAG_SHIFT 17u
#define PMC_LVSCR_LVR3V_RPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR3V_RPM_FLAG(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR3V_RPM_FLAG_SHIFT))&PMC_LVSCR_LVR3V_RPM_FLAG_MASK)
#define PMC_LVSCR_LVR3V_FPM_FLAG_MASK  0x10000u
#define PMC_LVSCR_LVR3V_FPM_FLAG_SHIFT 16u
#define PMC_LVSCR_LVR3V_FPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR3V_FPM_FLAG(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR3V_FPM_FLAG_SHIFT))&PMC_LVSCR_LVR3V_FPM_FLAG_MASK)
#define PMC_LVSCR_HVD3V_STATUS_MASK    0x100u
#define PMC_LVSCR_HVD3V_STATUS_SHIFT   8u
#define PMC_LVSCR_HVD3V_STATUS_WIDTH   1u
#define PMC_LVSCR_HVD3V_STATUS(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD3V_STATUS_SHIFT))&PMC_LVSCR_HVD3V_STATUS_MASK)
#define PMC_LVSCR_HVD3V_FLAG_MASK      0x1u
#define PMC_LVSCR_HVD3V_FLAG_SHIFT     0u
#define PMC_LVSCR_HVD3V_FLAG_WIDTH     1u
#define PMC_LVSCR_HVD3V_FLAG(x)        (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD3V_FLAG_SHIFT))&PMC_LVSCR_HVD3V_FLAG_MASK)
#endif

#if PMC_V5_SUPPORT
#define PMC_LVSCR_LVR5V_RPM_FLAG_MASK  0x20000u
#define PMC_LVSCR_LVR5V_RPM_FLAG_SHIFT 17u
#define PMC_LVSCR_LVR5V_RPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR5V_RPM_FLAG(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR5V_RPM_FLAG_SHIFT))&PMC_LVSCR_LVR5V_RPM_FLAG_MASK)
#define PMC_LVSCR_LVR5V_FPM_FLAG_MASK  0x10000u
#define PMC_LVSCR_LVR5V_FPM_FLAG_SHIFT 16u
#define PMC_LVSCR_LVR5V_FPM_FLAG_WIDTH 1u
#define PMC_LVSCR_LVR5V_FPM_FLAG(x)    (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVR5V_FPM_FLAG_SHIFT))&PMC_LVSCR_LVR5V_FPM_FLAG_MASK)
#define PMC_LVSCR_LVD5V_STATUS_MASK    0x1000u
#define PMC_LVSCR_LVD5V_STATUS_SHIFT   12u
#define PMC_LVSCR_LVD5V_STATUS_WIDTH   1u
#define PMC_LVSCR_LVD5V_STATUS(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVD5V_STATUS_SHIFT))&PMC_LVSCR_LVD5V_STATUS_MASK)
#define PMC_LVSCR_HVD5V_STATUS_MASK    0x100u
#define PMC_LVSCR_HVD5V_STATUS_SHIFT   8u
#define PMC_LVSCR_HVD5V_STATUS_WIDTH   1u
#define PMC_LVSCR_HVD5V_STATUS(x)      (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD5V_STATUS_SHIFT))&PMC_LVSCR_HVD5V_STATUS_MASK)
#define PMC_LVSCR_LVD5V_FLAG_MASK      0x10u
#define PMC_LVSCR_LVD5V_FLAG_SHIFT     4u
#define PMC_LVSCR_LVD5V_FLAG_WIDTH     1u
#define PMC_LVSCR_LVD5V_FLAG(x)        (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_LVD5V_FLAG_SHIFT))&PMC_LVSCR_LVD5V_FLAG_MASK)
#define PMC_LVSCR_HVD5V_FLAG_MASK      0x1u
#define PMC_LVSCR_HVD5V_FLAG_SHIFT     0u
#define PMC_LVSCR_HVD5V_FLAG_WIDTH     1u
#define PMC_LVSCR_HVD5V_FLAG(x)        (((uint32_t)(((uint32_t)(x))<<PMC_LVSCR_HVD5V_FLAG_SHIFT))&PMC_LVSCR_HVD5V_FLAG_MASK)
#endif

#if PMC_V5_SUPPORT
/* LVSCR Reg Mask */
#define PMC_LVSCR_MASK                 0x80F31D1Du
#else
/* LVSCR Reg Mask */
#define PMC_LVSCR_MASK                 0x80C30909u
#endif

/* CONFIG Bit Fields */
#if PMC_LVD_SUPPORT
#define PMC_CONFIG_LVD_IE_MASK         0x200u
#define PMC_CONFIG_LVD_IE_SHIFT        9u
#define PMC_CONFIG_LVD_IE_WIDTH        1u
#define PMC_CONFIG_LVD_IE(x)           (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_LVD_IE_SHIFT))&PMC_CONFIG_LVD_IE_MASK)
#endif

#define PMC_CONFIG_HVD_IE_MASK         0x100u
#define PMC_CONFIG_HVD_IE_SHIFT        8u
#define PMC_CONFIG_HVD_IE_WIDTH        1u
#define PMC_CONFIG_HVD_IE(x)           (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_HVD_IE_SHIFT))&PMC_CONFIG_HVD_IE_MASK)

#if PMC_BUFVREF10_SUPPORT
#define PMC_CONFIG_BUF10_EN_MASK  0x8u
#define PMC_CONFIG_BUF10_EN_SHIFT 3u
#define PMC_CONFIG_BUF10_EN_WIDTH 1u
#define PMC_CONFIG_BUF10_EN(x)    (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_BUF10_EN_SHIFT))&PMC_CONFIG_BUF10_EN_MASK)
#else
#define PMC_CONFIG_RPM_VDD2P5_EN_MASK  0x8u
#define PMC_CONFIG_RPM_VDD2P5_EN_SHIFT 3u
#define PMC_CONFIG_RPM_VDD2P5_EN_WIDTH 1u
#define PMC_CONFIG_RPM_VDD2P5_EN(x)    (((uint32_t)(((uint32_t)(x))<<PMC_CONFIG_RPM_VDD2P5_EN_SHIFT))&PMC_CONFIG_RPM_VDD2P5_EN_MASK)
#endif

#if PMC_BUFVREF10_SUPPORT
/* CONFIG Reg Mask */
#define PMC_CONFIG_MASK                0x00000108u
#else
/* CONFIG Reg Mask */
#define PMC_CONFIG_MASK                0x00000308u
#endif
/**
 * @}
 */ /* end of group PMC_Register_Masks */
/**
 * @}
 */ /* end of group PMC_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
