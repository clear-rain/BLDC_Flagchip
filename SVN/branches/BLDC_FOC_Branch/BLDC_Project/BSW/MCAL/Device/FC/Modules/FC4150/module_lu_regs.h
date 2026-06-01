#ifndef _MODULE_LU_KJO_Ufdi1_REGS_H_
#define _MODULE_LU_KJO_Ufdi1_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- LU Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup LU_Peripheral_Access_Layer LU Peripheral Access Layer
 * @{
 */
/** LU - Size of Registers Arrays */
/** LU - Register Layout Typedef */

typedef struct {
    struct {
      __IO uint32_t AOI_0                        ; /* AOI0 configuration, offset: 0x0+n*10h */
      __IO uint32_t AOI_1                        ; /* AOI1 configuration, offset: 0x4+n*10h */
      __IO uint32_t CTRL                         ; /* lg configuration, offset: 0x8+n*10h */
      __IO uint32_t FILT                         ; /* input filter, offset: 0xc+n*10h */
    } LG[LG_CNT];
} LU_Type, *LU_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- LU Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup LU_Register_Masks LU Register Masks
 * @{
 */
 
/* AOI_0 Bit Fields */
#define LU_AOI_0_IN0A_CFG_MASK         0xC0000000u
#define LU_AOI_0_IN0A_CFG_SHIFT        30u
#define LU_AOI_0_IN0A_CFG_WIDTH        2u
#define LU_AOI_0_IN0A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN0A_CFG_SHIFT))&LU_AOI_0_IN0A_CFG_MASK)
#define LU_AOI_0_IN0B_CFG_MASK         0x30000000u
#define LU_AOI_0_IN0B_CFG_SHIFT        28u
#define LU_AOI_0_IN0B_CFG_WIDTH        2u
#define LU_AOI_0_IN0B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN0B_CFG_SHIFT))&LU_AOI_0_IN0B_CFG_MASK)
#define LU_AOI_0_IN0C_CFG_MASK         0xC000000u
#define LU_AOI_0_IN0C_CFG_SHIFT        26u
#define LU_AOI_0_IN0C_CFG_WIDTH        2u
#define LU_AOI_0_IN0C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN0C_CFG_SHIFT))&LU_AOI_0_IN0C_CFG_MASK)
#define LU_AOI_0_IN0D_CFG_MASK         0x3000000u
#define LU_AOI_0_IN0D_CFG_SHIFT        24u
#define LU_AOI_0_IN0D_CFG_WIDTH        2u
#define LU_AOI_0_IN0D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN0D_CFG_SHIFT))&LU_AOI_0_IN0D_CFG_MASK)
#define LU_AOI_0_IN1A_CFG_MASK         0xC00000u
#define LU_AOI_0_IN1A_CFG_SHIFT        22u
#define LU_AOI_0_IN1A_CFG_WIDTH        2u
#define LU_AOI_0_IN1A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN1A_CFG_SHIFT))&LU_AOI_0_IN1A_CFG_MASK)
#define LU_AOI_0_IN1B_CFG_MASK         0x300000u
#define LU_AOI_0_IN1B_CFG_SHIFT        20u
#define LU_AOI_0_IN1B_CFG_WIDTH        2u
#define LU_AOI_0_IN1B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN1B_CFG_SHIFT))&LU_AOI_0_IN1B_CFG_MASK)
#define LU_AOI_0_IN1C_CFG_MASK         0xC0000u
#define LU_AOI_0_IN1C_CFG_SHIFT        18u
#define LU_AOI_0_IN1C_CFG_WIDTH        2u
#define LU_AOI_0_IN1C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN1C_CFG_SHIFT))&LU_AOI_0_IN1C_CFG_MASK)
#define LU_AOI_0_IN1D_CFG_MASK         0x30000u
#define LU_AOI_0_IN1D_CFG_SHIFT        16u
#define LU_AOI_0_IN1D_CFG_WIDTH        2u
#define LU_AOI_0_IN1D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN1D_CFG_SHIFT))&LU_AOI_0_IN1D_CFG_MASK)
#define LU_AOI_0_IN2A_CFG_MASK         0xC000u
#define LU_AOI_0_IN2A_CFG_SHIFT        14u
#define LU_AOI_0_IN2A_CFG_WIDTH        2u
#define LU_AOI_0_IN2A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN2A_CFG_SHIFT))&LU_AOI_0_IN2A_CFG_MASK)
#define LU_AOI_0_IN2B_CFG_MASK         0x3000u
#define LU_AOI_0_IN2B_CFG_SHIFT        12u
#define LU_AOI_0_IN2B_CFG_WIDTH        2u
#define LU_AOI_0_IN2B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN2B_CFG_SHIFT))&LU_AOI_0_IN2B_CFG_MASK)
#define LU_AOI_0_IN2C_CFG_MASK         0xC00u
#define LU_AOI_0_IN2C_CFG_SHIFT        10u
#define LU_AOI_0_IN2C_CFG_WIDTH        2u
#define LU_AOI_0_IN2C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN2C_CFG_SHIFT))&LU_AOI_0_IN2C_CFG_MASK)
#define LU_AOI_0_IN2D_CFG_MASK         0x300u
#define LU_AOI_0_IN2D_CFG_SHIFT        8u
#define LU_AOI_0_IN2D_CFG_WIDTH        2u
#define LU_AOI_0_IN2D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN2D_CFG_SHIFT))&LU_AOI_0_IN2D_CFG_MASK)
#define LU_AOI_0_IN3A_CFG_MASK         0xC0u
#define LU_AOI_0_IN3A_CFG_SHIFT        6u
#define LU_AOI_0_IN3A_CFG_WIDTH        2u
#define LU_AOI_0_IN3A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN3A_CFG_SHIFT))&LU_AOI_0_IN3A_CFG_MASK)
#define LU_AOI_0_IN3B_CFG_MASK         0x30u
#define LU_AOI_0_IN3B_CFG_SHIFT        4u
#define LU_AOI_0_IN3B_CFG_WIDTH        2u
#define LU_AOI_0_IN3B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN3B_CFG_SHIFT))&LU_AOI_0_IN3B_CFG_MASK)
#define LU_AOI_0_IN3C_CFG_MASK         0xCu
#define LU_AOI_0_IN3C_CFG_SHIFT        2u
#define LU_AOI_0_IN3C_CFG_WIDTH        2u
#define LU_AOI_0_IN3C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN3C_CFG_SHIFT))&LU_AOI_0_IN3C_CFG_MASK)
#define LU_AOI_0_IN3D_CFG_MASK         0x3u
#define LU_AOI_0_IN3D_CFG_SHIFT        0u
#define LU_AOI_0_IN3D_CFG_WIDTH        2u
#define LU_AOI_0_IN3D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_0_IN3D_CFG_SHIFT))&LU_AOI_0_IN3D_CFG_MASK)
/* AOI_00 Reg Mask */
#define LU_AOI_0_MASK                  0xFFFFFFFFu
/* AOI_1 Bit Fields */
#define LU_AOI_1_IN0A_CFG_MASK         0xC0000000u
#define LU_AOI_1_IN0A_CFG_SHIFT        30u
#define LU_AOI_1_IN0A_CFG_WIDTH        2u
#define LU_AOI_1_IN0A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN0A_CFG_SHIFT))&LU_AOI_1_IN0A_CFG_MASK)
#define LU_AOI_1_IN0B_CFG_MASK         0x30000000u
#define LU_AOI_1_IN0B_CFG_SHIFT        28u
#define LU_AOI_1_IN0B_CFG_WIDTH        2u
#define LU_AOI_1_IN0B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN0B_CFG_SHIFT))&LU_AOI_1_IN0B_CFG_MASK)
#define LU_AOI_1_IN0C_CFG_MASK         0xC000000u
#define LU_AOI_1_IN0C_CFG_SHIFT        26u
#define LU_AOI_1_IN0C_CFG_WIDTH        2u
#define LU_AOI_1_IN0C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN0C_CFG_SHIFT))&LU_AOI_1_IN0C_CFG_MASK)
#define LU_AOI_1_IN0D_CFG_MASK         0x3000000u
#define LU_AOI_1_IN0D_CFG_SHIFT        24u
#define LU_AOI_1_IN0D_CFG_WIDTH        2u
#define LU_AOI_1_IN0D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN0D_CFG_SHIFT))&LU_AOI_1_IN0D_CFG_MASK)
#define LU_AOI_1_IN1A_CFG_MASK         0xC00000u
#define LU_AOI_1_IN1A_CFG_SHIFT        22u
#define LU_AOI_1_IN1A_CFG_WIDTH        2u
#define LU_AOI_1_IN1A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN1A_CFG_SHIFT))&LU_AOI_1_IN1A_CFG_MASK)
#define LU_AOI_1_IN1B_CFG_MASK         0x300000u
#define LU_AOI_1_IN1B_CFG_SHIFT        20u
#define LU_AOI_1_IN1B_CFG_WIDTH        2u
#define LU_AOI_1_IN1B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN1B_CFG_SHIFT))&LU_AOI_1_IN1B_CFG_MASK)
#define LU_AOI_1_IN1C_CFG_MASK         0xC0000u
#define LU_AOI_1_IN1C_CFG_SHIFT        18u
#define LU_AOI_1_IN1C_CFG_WIDTH        2u
#define LU_AOI_1_IN1C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN1C_CFG_SHIFT))&LU_AOI_1_IN1C_CFG_MASK)
#define LU_AOI_1_IN1D_CFG_MASK         0x30000u
#define LU_AOI_1_IN1D_CFG_SHIFT        16u
#define LU_AOI_1_IN1D_CFG_WIDTH        2u
#define LU_AOI_1_IN1D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN1D_CFG_SHIFT))&LU_AOI_1_IN1D_CFG_MASK)
#define LU_AOI_1_IN2A_CFG_MASK         0xC000u
#define LU_AOI_1_IN2A_CFG_SHIFT        14u
#define LU_AOI_1_IN2A_CFG_WIDTH        2u
#define LU_AOI_1_IN2A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN2A_CFG_SHIFT))&LU_AOI_1_IN2A_CFG_MASK)
#define LU_AOI_1_IN2B_CFG_MASK         0x3000u
#define LU_AOI_1_IN2B_CFG_SHIFT        12u
#define LU_AOI_1_IN2B_CFG_WIDTH        2u
#define LU_AOI_1_IN2B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN2B_CFG_SHIFT))&LU_AOI_1_IN2B_CFG_MASK)
#define LU_AOI_1_IN2C_CFG_MASK         0xC00u
#define LU_AOI_1_IN2C_CFG_SHIFT        10u
#define LU_AOI_1_IN2C_CFG_WIDTH        2u
#define LU_AOI_1_IN2C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN2C_CFG_SHIFT))&LU_AOI_1_IN2C_CFG_MASK)
#define LU_AOI_1_IN2D_CFG_MASK         0x300u
#define LU_AOI_1_IN2D_CFG_SHIFT        8u
#define LU_AOI_1_IN2D_CFG_WIDTH        2u
#define LU_AOI_1_IN2D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN2D_CFG_SHIFT))&LU_AOI_1_IN2D_CFG_MASK)
#define LU_AOI_1_IN3A_CFG_MASK         0xC0u
#define LU_AOI_1_IN3A_CFG_SHIFT        6u
#define LU_AOI_1_IN3A_CFG_WIDTH        2u
#define LU_AOI_1_IN3A_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN3A_CFG_SHIFT))&LU_AOI_1_IN3A_CFG_MASK)
#define LU_AOI_1_IN3B_CFG_MASK         0x30u
#define LU_AOI_1_IN3B_CFG_SHIFT        4u
#define LU_AOI_1_IN3B_CFG_WIDTH        2u
#define LU_AOI_1_IN3B_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN3B_CFG_SHIFT))&LU_AOI_1_IN3B_CFG_MASK)
#define LU_AOI_1_IN3C_CFG_MASK         0xCu
#define LU_AOI_1_IN3C_CFG_SHIFT        2u
#define LU_AOI_1_IN3C_CFG_WIDTH        2u
#define LU_AOI_1_IN3C_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN3C_CFG_SHIFT))&LU_AOI_1_IN3C_CFG_MASK)
#define LU_AOI_1_IN3D_CFG_MASK         0x3u
#define LU_AOI_1_IN3D_CFG_SHIFT        0u
#define LU_AOI_1_IN3D_CFG_WIDTH        2u
#define LU_AOI_1_IN3D_CFG(x)           (((uint32_t)(((uint32_t)(x))<<LU_AOI_1_IN3D_CFG_SHIFT))&LU_AOI_1_IN3D_CFG_MASK)
/* AOI_10 Reg Mask */
#define LU_AOI_1_MASK                  0xFFFFFFFFu
/* CTRL Bit Fields */
#define LU_CTRL_BYPASS_MASK            0x3000u
#define LU_CTRL_BYPASS_SHIFT           12u
#define LU_CTRL_BYPASS_WIDTH           2u
#define LU_CTRL_BYPASS(x)              (((uint32_t)(((uint32_t)(x))<<LU_CTRL_BYPASS_SHIFT))&LU_CTRL_BYPASS_MASK)
#define LU_CTRL_SYNC_MASK              0xF00u
#define LU_CTRL_SYNC_SHIFT             8u
#define LU_CTRL_SYNC_WIDTH             4u
#define LU_CTRL_SYNC(x)                (((uint32_t)(((uint32_t)(x))<<LU_CTRL_SYNC_SHIFT))&LU_CTRL_SYNC_MASK)
#define LU_CTRL_FB_OVRD_MASK           0xC0u
#define LU_CTRL_FB_OVRD_SHIFT          6u
#define LU_CTRL_FB_OVRD_WIDTH          2u
#define LU_CTRL_FB_OVRD(x)             (((uint32_t)(((uint32_t)(x))<<LU_CTRL_FB_OVRD_SHIFT))&LU_CTRL_FB_OVRD_MASK)
#define LU_CTRL_MOD_MASK               0x1Cu
#define LU_CTRL_MOD_SHIFT              2u
#define LU_CTRL_MOD_WIDTH              3u
#define LU_CTRL_MOD(x)                 (((uint32_t)(((uint32_t)(x))<<LU_CTRL_MOD_SHIFT))&LU_CTRL_MOD_MASK)
#define LU_CTRL_INIT_EN_MASK           0x2u
#define LU_CTRL_INIT_EN_SHIFT          1u
#define LU_CTRL_INIT_EN_WIDTH          1u
#define LU_CTRL_INIT_EN(x)             (((uint32_t)(((uint32_t)(x))<<LU_CTRL_INIT_EN_SHIFT))&LU_CTRL_INIT_EN_MASK)
#define LU_CTRL_FF_INIT_MASK           0x1u
#define LU_CTRL_FF_INIT_SHIFT          0u
#define LU_CTRL_FF_INIT_WIDTH          1u
#define LU_CTRL_FF_INIT(x)             (((uint32_t)(((uint32_t)(x))<<LU_CTRL_FF_INIT_SHIFT))&LU_CTRL_FF_INIT_MASK)
/* CTRL0 Reg Mask */
#define LU_CTRL_MASK                   0x00003FDFu
/* FILT Bit Fields */
#define LU_FILT_CNT0_MASK              0x7000000u
#define LU_FILT_CNT0_SHIFT             24u
#define LU_FILT_CNT0_WIDTH             3u
#define LU_FILT_CNT0(x)                (((uint32_t)(((uint32_t)(x))<<LU_FILT_CNT0_SHIFT))&LU_FILT_CNT0_MASK)
#define LU_FILT_PRE0_MASK              0xFF0000u
#define LU_FILT_PRE0_SHIFT             16u
#define LU_FILT_PRE0_WIDTH             8u
#define LU_FILT_PRE0(x)                (((uint32_t)(((uint32_t)(x))<<LU_FILT_PRE0_SHIFT))&LU_FILT_PRE0_MASK)
#define LU_FILT_CNT1_MASK              0x700u
#define LU_FILT_CNT1_SHIFT             8u
#define LU_FILT_CNT1_WIDTH             3u
#define LU_FILT_CNT1(x)                (((uint32_t)(((uint32_t)(x))<<LU_FILT_CNT1_SHIFT))&LU_FILT_CNT1_MASK)
#define LU_FILT_PRE1_MASK              0xFFu
#define LU_FILT_PRE1_SHIFT             0u
#define LU_FILT_PRE1_WIDTH             8u
#define LU_FILT_PRE1(x)                (((uint32_t)(((uint32_t)(x))<<LU_FILT_PRE1_SHIFT))&LU_FILT_PRE1_MASK)
/* FILT0 Reg Mask */
#define LU_FILT_MASK                   0x07FF07FFu
/**
 * @}
 */ /* end of group LU_Register_Masks */
/**
 * @}
 */ /* end of group LU_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
