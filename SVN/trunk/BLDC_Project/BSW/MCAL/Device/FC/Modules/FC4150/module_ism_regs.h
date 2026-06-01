#ifndef _MODULE_ISM_KJO_Ufdi34_REGS_H_
#define _MODULE_ISM_KJO_Ufdi34_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- ISM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup ISM_Peripheral_Access_Layer ISM Peripheral Access Layer
 * @{
 */
/** ISM - Size of Registers Arrays */
/** ISM - Register Layout Typedef */
typedef struct {
  __I  uint32_t PARAM                         ; /* Parameter, offset: 0x0 */
  __IO uint32_t CTRL                          ; /* Control register, offset: 0x4 */
  __IO uint32_t E_STATUS                      ; /* Event Status, offset: 0x8 */
  __IO uint32_t E_CTRL                        ; /* Event Control, offset: 0xC */
  __IO uint32_t EC_CTRL                       ; /* Event Control Mode Control, offset: 0x10 */
       uint8_t  RESERVED_0[236];
  __IO uint32_t FPC_STATUS0                   ; /* FPC Status, offset: 0x100 */
  __IO uint32_t FPC_CTRL0                     ; /* FPC Control, offset: 0x104 */
  __IO uint32_t FPC_CONFIG0                   ; /* FPC Configure, offset: 0x108 */
  __IO uint32_t FPC_TIMER0                    ; /* FPC Timer, offset: 0x10c */
  __IO uint32_t FPC_STATUS1                   ; /* FPC Status, offset: 0x110 */
  __IO uint32_t FPC_CTRL1                     ; /* FPC Control, offset: 0x114 */
  __IO uint32_t FPC_CONFIG1                   ; /* FPC Configure, offset: 0x118 */
  __IO uint32_t FPC_TIMER1                    ; /* FPC Timer, offset: 0x11c */
  __IO uint32_t FPC_STATUS2                   ; /* FPC Status, offset: 0x120 */
  __IO uint32_t FPC_CTRL2                     ; /* FPC Control, offset: 0x124 */
  __IO uint32_t FPC_CONFIG2                   ; /* FPC Configure, offset: 0x128 */
  __IO uint32_t FPC_TIMER2                    ; /* FPC Timer, offset: 0x12c */
  __IO uint32_t FPC_STATUS3                   ; /* FPC Status, offset: 0x130 */
  __IO uint32_t FPC_CTRL3                     ; /* FPC Control, offset: 0x134 */
  __IO uint32_t FPC_CONFIG3                   ; /* FPC Configure, offset: 0x138 */
  __IO uint32_t FPC_TIMER3                    ; /* FPC Timer, offset: 0x13c */
  __IO uint32_t FPC_STATUS4                   ; /* FPC Status, offset: 0x140 */
  __IO uint32_t FPC_CTRL4                     ; /* FPC Control, offset: 0x144 */
  __IO uint32_t FPC_CONFIG4                   ; /* FPC Configure, offset: 0x148 */
  __IO uint32_t FPC_TIMER4                    ; /* FPC Timer, offset: 0x14c */
  __IO uint32_t FPC_STATUS5                   ; /* FPC Status, offset: 0x150 */
  __IO uint32_t FPC_CTRL5                     ; /* FPC Control, offset: 0x154 */
  __IO uint32_t FPC_CONFIG5                   ; /* FPC Configure, offset: 0x158 */
  __IO uint32_t FPC_TIMER5                    ; /* FPC Timer, offset: 0x15c */
  __IO uint32_t FPC_STATUS6                   ; /* FPC Status, offset: 0x160 */
  __IO uint32_t FPC_CTRL6                     ; /* FPC Control, offset: 0x164 */
  __IO uint32_t FPC_CONFIG6                   ; /* FPC Configure, offset: 0x168 */
  __IO uint32_t FPC_TIMER6                    ; /* FPC Timer, offset: 0x16c */
  __IO uint32_t FPC_STATUS7                   ; /* FPC Status, offset: 0x170 */
  __IO uint32_t FPC_CTRL7                     ; /* FPC Control, offset: 0x174 */
  __IO uint32_t FPC_CONFIG7                   ; /* FPC Configure, offset: 0x178 */
  __IO uint32_t FPC_TIMER7                    ; /* FPC Timer, offset: 0x17c */
  __IO uint32_t FPC_STATUS8                   ; /* FPC Status, offset: 0x180 */
  __IO uint32_t FPC_CTRL8                     ; /* FPC Control, offset: 0x184 */
  __IO uint32_t FPC_CONFIG8                   ; /* FPC Configure, offset: 0x188 */
  __IO uint32_t FPC_TIMER8                    ; /* FPC Timer, offset: 0x18c */
  __IO uint32_t FPC_STATUS9                   ; /* FPC Status, offset: 0x190 */
  __IO uint32_t FPC_CTRL9                     ; /* FPC Control, offset: 0x194 */
  __IO uint32_t FPC_CONFIG9                   ; /* FPC Configure, offset: 0x198 */
  __IO uint32_t FPC_TIMER9                    ; /* FPC Timer, offset: 0x19c */
  __IO uint32_t FPC_STATUS10                  ; /* FPC Status, offset: 0x1a0 */
  __IO uint32_t FPC_CTRL10                    ; /* FPC Control, offset: 0x1a4 */
  __IO uint32_t FPC_CONFIG10                  ; /* FPC Configure, offset: 0x1a8 */
  __IO uint32_t FPC_TIMER10                   ; /* FPC Timer, offset: 0x1ac */
  __IO uint32_t FPC_STATUS11                  ; /* FPC Status, offset: 0x1b0 */
  __IO uint32_t FPC_CTRL11                    ; /* FPC Control, offset: 0x1b4 */
  __IO uint32_t FPC_CONFIG11                  ; /* FPC Configure, offset: 0x1b8 */
  __IO uint32_t FPC_TIMER11                   ; /* FPC Timer, offset: 0x1bc */
  __IO uint32_t FPC_STATUS12                  ; /* FPC Status, offset: 0x1c0 */
  __IO uint32_t FPC_CTRL12                    ; /* FPC Control, offset: 0x1c4 */
  __IO uint32_t FPC_CONFIG12                  ; /* FPC Configure, offset: 0x1c8 */
  __IO uint32_t FPC_TIMER12                   ; /* FPC Timer, offset: 0x1cc */
  __IO uint32_t FPC_STATUS13                  ; /* FPC Status, offset: 0x1d0 */
  __IO uint32_t FPC_CTRL13                    ; /* FPC Control, offset: 0x1d4 */
  __IO uint32_t FPC_CONFIG13                  ; /* FPC Configure, offset: 0x1d8 */
  __IO uint32_t FPC_TIMER13                   ; /* FPC Timer, offset: 0x1dc */
  __IO uint32_t FPC_STATUS14                  ; /* FPC Status, offset: 0x1e0 */
  __IO uint32_t FPC_CTRL14                    ; /* FPC Control, offset: 0x1e4 */
  __IO uint32_t FPC_CONFIG14                  ; /* FPC Configure, offset: 0x1e8 */
  __IO uint32_t FPC_TIMER14                   ; /* FPC Timer, offset: 0x1ec */
  __IO uint32_t FPC_STATUS15                  ; /* FPC Status, offset: 0x1f0 */
  __IO uint32_t FPC_CTRL15                    ; /* FPC Control, offset: 0x1f4 */
  __IO uint32_t FPC_CONFIG15                  ; /* FPC Configure, offset: 0x1f8 */
  __IO uint32_t FPC_TIMER15                   ; /* FPC Timer, offset: 0x1fc */
  __IO uint32_t LAM_STATUS0                   ; /* LAM Status, offset: 0x200 */
  __IO uint32_t LAM_CTRL0                     ; /* LAM Control, offset: 0x204 */
  __IO uint32_t LAM_CONFIG0                   ; /* LAM Configure, offset: 0x208 */
  __IO uint32_t LAM_COUNTER0                  ; /* LAM Counter, offset: 0x20c */
  __IO uint32_t LAM_STATUS1                   ; /* LAM Status, offset: 0x210 */
  __IO uint32_t LAM_CTRL1                     ; /* LAM Control, offset: 0x214 */
  __IO uint32_t LAM_CONFIG1                   ; /* LAM Configure, offset: 0x218 */
  __IO uint32_t LAM_COUNTER1                  ; /* LAM Counter, offset: 0x21c */
  __IO uint32_t LAM_STATUS2                   ; /* LAM Status, offset: 0x220 */
  __IO uint32_t LAM_CTRL2                     ; /* LAM Control, offset: 0x224 */
  __IO uint32_t LAM_CONFIG2                   ; /* LAM Configure, offset: 0x228 */
  __IO uint32_t LAM_COUNTER2                  ; /* LAM Counter, offset: 0x22c */
  __IO uint32_t LAM_STATUS3                   ; /* LAM Status, offset: 0x230 */
  __IO uint32_t LAM_CTRL3                     ; /* LAM Control, offset: 0x234 */
  __IO uint32_t LAM_CONFIG3                   ; /* LAM Configure, offset: 0x238 */
  __IO uint32_t LAM_COUNTER3                  ; /* LAM Counter, offset: 0x23c */
  __IO uint32_t LAM_STATUS4                   ; /* LAM Status, offset: 0x240 */
  __IO uint32_t LAM_CTRL4                     ; /* LAM Control, offset: 0x244 */
  __IO uint32_t LAM_CONFIG4                   ; /* LAM Configure, offset: 0x248 */
  __IO uint32_t LAM_COUNTER4                  ; /* LAM Counter, offset: 0x24c */
  __IO uint32_t LAM_STATUS5                   ; /* LAM Status, offset: 0x250 */
  __IO uint32_t LAM_CTRL5                     ; /* LAM Control, offset: 0x254 */
  __IO uint32_t LAM_CONFIG5                   ; /* LAM Configure, offset: 0x258 */
  __IO uint32_t LAM_COUNTER5                  ; /* LAM Counter, offset: 0x25c */
  __IO uint32_t LAM_STATUS6                   ; /* LAM Status, offset: 0x260 */
  __IO uint32_t LAM_CTRL6                     ; /* LAM Control, offset: 0x264 */
  __IO uint32_t LAM_CONFIG6                   ; /* LAM Configure, offset: 0x268 */
  __IO uint32_t LAM_COUNTER6                  ; /* LAM Counter, offset: 0x26c */
  __IO uint32_t LAM_STATUS7                   ; /* LAM Status, offset: 0x270 */
  __IO uint32_t LAM_CTRL7                     ; /* LAM Control, offset: 0x274 */
  __IO uint32_t LAM_CONFIG7                   ; /* LAM Configure, offset: 0x278 */
  __IO uint32_t LAM_COUNTER7                  ; /* LAM Counter, offset: 0x27c */
  __IO uint32_t LAM_STATUS8                   ; /* LAM Status, offset: 0x280 */
  __IO uint32_t LAM_CTRL8                     ; /* LAM Control, offset: 0x284 */
  __IO uint32_t LAM_CONFIG8                   ; /* LAM Configure, offset: 0x288 */
  __IO uint32_t LAM_COUNTER8                  ; /* LAM Counter, offset: 0x28c */
  __IO uint32_t LAM_STATUS9                   ; /* LAM Status, offset: 0x290 */
  __IO uint32_t LAM_CTRL9                     ; /* LAM Control, offset: 0x294 */
  __IO uint32_t LAM_CONFIG9                   ; /* LAM Configure, offset: 0x298 */
  __IO uint32_t LAM_COUNTER9                  ; /* LAM Counter, offset: 0x29c */
  __IO uint32_t LAM_STATUS10                  ; /* LAM Status, offset: 0x2a0 */
  __IO uint32_t LAM_CTRL10                    ; /* LAM Control, offset: 0x2a4 */
  __IO uint32_t LAM_CONFIG10                  ; /* LAM Configure, offset: 0x2a8 */
  __IO uint32_t LAM_COUNTER10                 ; /* LAM Counter, offset: 0x2ac */
  __IO uint32_t LAM_STATUS11                  ; /* LAM Status, offset: 0x2b0 */
  __IO uint32_t LAM_CTRL11                    ; /* LAM Control, offset: 0x2b4 */
  __IO uint32_t LAM_CONFIG11                  ; /* LAM Configure, offset: 0x2b8 */
  __IO uint32_t LAM_COUNTER11                 ; /* LAM Counter, offset: 0x2bc */
  __IO uint32_t LAM_STATUS12                  ; /* LAM Status, offset: 0x2c0 */
  __IO uint32_t LAM_CTRL12                    ; /* LAM Control, offset: 0x2c4 */
  __IO uint32_t LAM_CONFIG12                  ; /* LAM Configure, offset: 0x2c8 */
  __IO uint32_t LAM_COUNTER12                 ; /* LAM Counter, offset: 0x2cc */
  __IO uint32_t LAM_STATUS13                  ; /* LAM Status, offset: 0x2d0 */
  __IO uint32_t LAM_CTRL13                    ; /* LAM Control, offset: 0x2d4 */
  __IO uint32_t LAM_CONFIG13                  ; /* LAM Configure, offset: 0x2d8 */
  __IO uint32_t LAM_COUNTER13                 ; /* LAM Counter, offset: 0x2dc */
  __IO uint32_t LAM_STATUS14                  ; /* LAM Status, offset: 0x2e0 */
  __IO uint32_t LAM_CTRL14                    ; /* LAM Control, offset: 0x2e4 */
  __IO uint32_t LAM_CONFIG14                  ; /* LAM Configure, offset: 0x2e8 */
  __IO uint32_t LAM_COUNTER14                 ; /* LAM Counter, offset: 0x2ec */
  __IO uint32_t LAM_STATUS15                  ; /* LAM Status, offset: 0x2f0 */
  __IO uint32_t LAM_CTRL15                    ; /* LAM Control, offset: 0x2f4 */
  __IO uint32_t LAM_CONFIG15                  ; /* LAM Configure, offset: 0x2f8 */
  __IO uint32_t LAM_COUNTER15                 ; /* LAM Counter, offset: 0x2fc */
} ISM_Type, *ISM_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- ISM Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup ISM_Register_Masks ISM Register Masks
 * @{
 */
 
/* PARAM Bit Fields */
#define ISM_PARAM_LAM_MASK             0x1F000000u
#define ISM_PARAM_LAM_SHIFT            24u
#define ISM_PARAM_LAM_WIDTH            5u
#define ISM_PARAM_LAM(x)               (((uint32_t)(((uint32_t)(x))<<ISM_PARAM_LAM_SHIFT))&ISM_PARAM_LAM_MASK)
#define ISM_PARAM_FPC_MASK             0x1F0000u
#define ISM_PARAM_FPC_SHIFT            16u
#define ISM_PARAM_FPC_WIDTH            5u
#define ISM_PARAM_FPC(x)               (((uint32_t)(((uint32_t)(x))<<ISM_PARAM_FPC_SHIFT))&ISM_PARAM_FPC_MASK)
#define ISM_PARAM_ECMC_MASK            0xFu
#define ISM_PARAM_ECMC_SHIFT           0u
#define ISM_PARAM_ECMC_WIDTH           4u
#define ISM_PARAM_ECMC(x)              (((uint32_t)(((uint32_t)(x))<<ISM_PARAM_ECMC_SHIFT))&ISM_PARAM_ECMC_MASK)
/* PARAM Reg Mask */
#define ISM_PARAM_MASK                 0x1F1F000Fu
/* CTRL Bit Fields */
#define ISM_CTRL_EN_MASK               0x80000000u
#define ISM_CTRL_EN_SHIFT              31u
#define ISM_CTRL_EN_WIDTH              1u
#define ISM_CTRL_EN(x)                 (((uint32_t)(((uint32_t)(x))<<ISM_CTRL_EN_SHIFT))&ISM_CTRL_EN_MASK)
#define ISM_CTRL_IEN_MASK              0x1u
#define ISM_CTRL_IEN_SHIFT             0u
#define ISM_CTRL_IEN_WIDTH             1u
#define ISM_CTRL_IEN(x)                (((uint32_t)(((uint32_t)(x))<<ISM_CTRL_IEN_SHIFT))&ISM_CTRL_IEN_MASK)
/* CTRL Reg Mask */
#define ISM_CTRL_MASK                  0x80000001u
/* E_STATUS Bit Fields */
#define ISM_E_STATUS_ECS_MASK          0xF0000u
#define ISM_E_STATUS_ECS_SHIFT         16u
#define ISM_E_STATUS_ECS_WIDTH         4u
#define ISM_E_STATUS_ECS(x)            (((uint32_t)(((uint32_t)(x))<<ISM_E_STATUS_ECS_SHIFT))&ISM_E_STATUS_ECS_MASK)
#define ISM_E_STATUS_ES_MASK           0xFFFFu
#define ISM_E_STATUS_ES_SHIFT          0u
#define ISM_E_STATUS_ES_WIDTH          16u
#define ISM_E_STATUS_ES(x)             (((uint32_t)(((uint32_t)(x))<<ISM_E_STATUS_ES_SHIFT))&ISM_E_STATUS_ES_MASK)
/* E_STATUS Reg Mask */
#define ISM_E_STATUS_MASK              0x000FFFFFu
/* E_CTRL Bit Fields */
#define ISM_E_CTRL_ECE_MASK            0xF0000u
#define ISM_E_CTRL_ECE_SHIFT           16u
#define ISM_E_CTRL_ECE_WIDTH           4u
#define ISM_E_CTRL_ECE(x)              (((uint32_t)(((uint32_t)(x))<<ISM_E_CTRL_ECE_SHIFT))&ISM_E_CTRL_ECE_MASK)
#define ISM_E_CTRL_EE_MASK             0xFFFFu
#define ISM_E_CTRL_EE_SHIFT            0u
#define ISM_E_CTRL_EE_WIDTH            16u
#define ISM_E_CTRL_EE(x)               (((uint32_t)(((uint32_t)(x))<<ISM_E_CTRL_EE_SHIFT))&ISM_E_CTRL_EE_MASK)
/* E_CTRL Reg Mask */
#define ISM_E_CTRL_MASK                0x000FFFFFu
/* EC_CTRL Bit Fields */
#define ISM_EC_CTRL_THRL_3_MASK        0xF0000000u
#define ISM_EC_CTRL_THRL_3_SHIFT       28u
#define ISM_EC_CTRL_THRL_3_WIDTH       4u
#define ISM_EC_CTRL_THRL_3(x)          (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_THRL_3_SHIFT))&ISM_EC_CTRL_THRL_3_MASK)
#define ISM_EC_CTRL_SEL_3_MASK         0xF000000u
#define ISM_EC_CTRL_SEL_3_SHIFT        24u
#define ISM_EC_CTRL_SEL_3_WIDTH        4u
#define ISM_EC_CTRL_SEL_3(x)           (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_SEL_3_SHIFT))&ISM_EC_CTRL_SEL_3_MASK)
#define ISM_EC_CTRL_THRL_2_MASK        0xF00000u
#define ISM_EC_CTRL_THRL_2_SHIFT       20u
#define ISM_EC_CTRL_THRL_2_WIDTH       4u
#define ISM_EC_CTRL_THRL_2(x)          (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_THRL_2_SHIFT))&ISM_EC_CTRL_THRL_2_MASK)
#define ISM_EC_CTRL_SEL_2_MASK         0xF0000u
#define ISM_EC_CTRL_SEL_2_SHIFT        16u
#define ISM_EC_CTRL_SEL_2_WIDTH        4u
#define ISM_EC_CTRL_SEL_2(x)           (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_SEL_2_SHIFT))&ISM_EC_CTRL_SEL_2_MASK)
#define ISM_EC_CTRL_THRL_1_MASK        0xF000u
#define ISM_EC_CTRL_THRL_1_SHIFT       12u
#define ISM_EC_CTRL_THRL_1_WIDTH       4u
#define ISM_EC_CTRL_THRL_1(x)          (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_THRL_1_SHIFT))&ISM_EC_CTRL_THRL_1_MASK)
#define ISM_EC_CTRL_SEL_1_MASK         0xF00u
#define ISM_EC_CTRL_SEL_1_SHIFT        8u
#define ISM_EC_CTRL_SEL_1_WIDTH        4u
#define ISM_EC_CTRL_SEL_1(x)           (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_SEL_1_SHIFT))&ISM_EC_CTRL_SEL_1_MASK)
#define ISM_EC_CTRL_THRL_0_MASK        0xF0u
#define ISM_EC_CTRL_THRL_0_SHIFT       4u
#define ISM_EC_CTRL_THRL_0_WIDTH       4u
#define ISM_EC_CTRL_THRL_0(x)          (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_THRL_0_SHIFT))&ISM_EC_CTRL_THRL_0_MASK)
#define ISM_EC_CTRL_SEL_0_MASK         0xFu
#define ISM_EC_CTRL_SEL_0_SHIFT        0u
#define ISM_EC_CTRL_SEL_0_WIDTH        4u
#define ISM_EC_CTRL_SEL_0(x)           (((uint32_t)(((uint32_t)(x))<<ISM_EC_CTRL_SEL_0_SHIFT))&ISM_EC_CTRL_SEL_0_MASK)
/* EC_CTRL Reg Mask */
#define ISM_EC_CTRL_MASK               0xFFFFFFFFu
/* FPC_STATUS Bit Fields */
#define ISM_FPC_STATUS_RGD_MASK        0x2u
#define ISM_FPC_STATUS_RGD_SHIFT       1u
#define ISM_FPC_STATUS_RGD_WIDTH       1u
#define ISM_FPC_STATUS_RGD(x)          (((uint32_t)(((uint32_t)(x))<<ISM_FPC_STATUS_RGD_SHIFT))&ISM_FPC_STATUS_RGD_MASK)
#define ISM_FPC_STATUS_FGD_MASK        0x1u
#define ISM_FPC_STATUS_FGD_SHIFT       0u
#define ISM_FPC_STATUS_FGD_WIDTH       1u
#define ISM_FPC_STATUS_FGD(x)          (((uint32_t)(((uint32_t)(x))<<ISM_FPC_STATUS_FGD_SHIFT))&ISM_FPC_STATUS_FGD_MASK)
/* FPC_STATUS0 Reg Mask */
#define ISM_FPC_STATUS_MASK            0x00000003u
/* FPC_CTRL Bit Fields */
#define ISM_FPC_CTRL_IEN_MASK          0x2u
#define ISM_FPC_CTRL_IEN_SHIFT         1u
#define ISM_FPC_CTRL_IEN_WIDTH         1u
#define ISM_FPC_CTRL_IEN(x)            (((uint32_t)(((uint32_t)(x))<<ISM_FPC_CTRL_IEN_SHIFT))&ISM_FPC_CTRL_IEN_MASK)
#define ISM_FPC_CTRL_EN_MASK           0x1u
#define ISM_FPC_CTRL_EN_SHIFT          0u
#define ISM_FPC_CTRL_EN_WIDTH          1u
#define ISM_FPC_CTRL_EN(x)             (((uint32_t)(((uint32_t)(x))<<ISM_FPC_CTRL_EN_SHIFT))&ISM_FPC_CTRL_EN_MASK)
/* FPC_CTRL0 Reg Mask */
#define ISM_FPC_CTRL_MASK              0x00000003u
/* FPC_CONFIG Bit Fields */
#define ISM_FPC_CONFIG_FEG_MASK        0xC00000u
#define ISM_FPC_CONFIG_FEG_SHIFT       22u
#define ISM_FPC_CONFIG_FEG_WIDTH       2u
#define ISM_FPC_CONFIG_FEG(x)          (((uint32_t)(((uint32_t)(x))<<ISM_FPC_CONFIG_FEG_SHIFT))&ISM_FPC_CONFIG_FEG_MASK)
#define ISM_FPC_CONFIG_FED_MASK        0x300000u
#define ISM_FPC_CONFIG_FED_SHIFT       20u
#define ISM_FPC_CONFIG_FED_WIDTH       2u
#define ISM_FPC_CONFIG_FED(x)          (((uint32_t)(((uint32_t)(x))<<ISM_FPC_CONFIG_FED_SHIFT))&ISM_FPC_CONFIG_FED_MASK)
#define ISM_FPC_CONFIG_REG_MASK        0xC0000u
#define ISM_FPC_CONFIG_REG_SHIFT       18u
#define ISM_FPC_CONFIG_REG_WIDTH       2u
#define ISM_FPC_CONFIG_REG(x)          (((uint32_t)(((uint32_t)(x))<<ISM_FPC_CONFIG_REG_SHIFT))&ISM_FPC_CONFIG_REG_MASK)
#define ISM_FPC_CONFIG_RED_MASK        0x30000u
#define ISM_FPC_CONFIG_RED_SHIFT       16u
#define ISM_FPC_CONFIG_RED_WIDTH       2u
#define ISM_FPC_CONFIG_RED(x)          (((uint32_t)(((uint32_t)(x))<<ISM_FPC_CONFIG_RED_SHIFT))&ISM_FPC_CONFIG_RED_MASK)
#define ISM_FPC_CONFIG_CMP_MASK        0xFFFFu
#define ISM_FPC_CONFIG_CMP_SHIFT       0u
#define ISM_FPC_CONFIG_CMP_WIDTH       16u
#define ISM_FPC_CONFIG_CMP(x)          (((uint32_t)(((uint32_t)(x))<<ISM_FPC_CONFIG_CMP_SHIFT))&ISM_FPC_CONFIG_CMP_MASK)
/* FPC_CONFIG0 Reg Mask */
#define ISM_FPC_CONFIG_MASK            0x00FFFFFFu
/* FPC_TIMER Bit Fields */
#define ISM_FPC_TIMER_TIM_MASK         0xFFFFu
#define ISM_FPC_TIMER_TIM_SHIFT        0u
#define ISM_FPC_TIMER_TIM_WIDTH        16u
#define ISM_FPC_TIMER_TIM(x)           (((uint32_t)(((uint32_t)(x))<<ISM_FPC_TIMER_TIM_SHIFT))&ISM_FPC_TIMER_TIM_MASK)
/* FPC_TIMER0 Reg Mask */
#define ISM_FPC_TIMER_MASK             0x0000FFFFu
/* LAM_STATUS Bit Fields */
#define ISM_LAM_STATUS_OVFL_MASK       0x80000000u
#define ISM_LAM_STATUS_OVFL_SHIFT      31u
#define ISM_LAM_STATUS_OVFL_WIDTH      1u
#define ISM_LAM_STATUS_OVFL(x)         (((uint32_t)(((uint32_t)(x))<<ISM_LAM_STATUS_OVFL_SHIFT))&ISM_LAM_STATUS_OVFL_MASK)
#define ISM_LAM_STATUS_COUNT_MASK      0xFFFFFFu
#define ISM_LAM_STATUS_COUNT_SHIFT     0u
#define ISM_LAM_STATUS_COUNT_WIDTH     24u
#define ISM_LAM_STATUS_COUNT(x)        (((uint32_t)(((uint32_t)(x))<<ISM_LAM_STATUS_COUNT_SHIFT))&ISM_LAM_STATUS_COUNT_MASK)
/* LAM_STATUS0 Reg Mask */
#define ISM_LAM_STATUS_MASK            0x80FFFFFFu
/* LAM_CTRL Bit Fields */
#define ISM_LAM_CTRL_IEN_MASK          0x2u
#define ISM_LAM_CTRL_IEN_SHIFT         1u
#define ISM_LAM_CTRL_IEN_WIDTH         1u
#define ISM_LAM_CTRL_IEN(x)            (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CTRL_IEN_SHIFT))&ISM_LAM_CTRL_IEN_MASK)
#define ISM_LAM_CTRL_EN_MASK           0x1u
#define ISM_LAM_CTRL_EN_SHIFT          0u
#define ISM_LAM_CTRL_EN_WIDTH          1u
#define ISM_LAM_CTRL_EN(x)             (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CTRL_EN_SHIFT))&ISM_LAM_CTRL_EN_MASK)
/* LAM_CTRL0 Reg Mask */
#define ISM_LAM_CTRL_MASK              0x00000003u
/* LAM_CONFIG Bit Fields */
#define ISM_LAM_CONFIG_RCS_MASK        0xF00000u
#define ISM_LAM_CONFIG_RCS_SHIFT       20u
#define ISM_LAM_CONFIG_RCS_WIDTH       4u
#define ISM_LAM_CONFIG_RCS(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_RCS_SHIFT))&ISM_LAM_CONFIG_RCS_MASK)
#define ISM_LAM_CONFIG_MCS_MASK        0xF0000u
#define ISM_LAM_CONFIG_MCS_SHIFT       16u
#define ISM_LAM_CONFIG_MCS_WIDTH       4u
#define ISM_LAM_CONFIG_MCS(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_MCS_SHIFT))&ISM_LAM_CONFIG_MCS_MASK)
#define ISM_LAM_CONFIG_IVW_MASK        0x1000u
#define ISM_LAM_CONFIG_IVW_SHIFT       12u
#define ISM_LAM_CONFIG_IVW_WIDTH       1u
#define ISM_LAM_CONFIG_IVW(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_IVW_SHIFT))&ISM_LAM_CONFIG_IVW_MASK)
#define ISM_LAM_CONFIG_EDS_MASK        0xF00u
#define ISM_LAM_CONFIG_EDS_SHIFT       8u
#define ISM_LAM_CONFIG_EDS_WIDTH       4u
#define ISM_LAM_CONFIG_EDS(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_EDS_SHIFT))&ISM_LAM_CONFIG_EDS_MASK)
#define ISM_LAM_CONFIG_EWS_MASK        0x10u
#define ISM_LAM_CONFIG_EWS_SHIFT       4u
#define ISM_LAM_CONFIG_EWS_WIDTH       1u
#define ISM_LAM_CONFIG_EWS(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_EWS_SHIFT))&ISM_LAM_CONFIG_EWS_MASK)
#define ISM_LAM_CONFIG_RMS_MASK        0x8u
#define ISM_LAM_CONFIG_RMS_SHIFT       3u
#define ISM_LAM_CONFIG_RMS_WIDTH       1u
#define ISM_LAM_CONFIG_RMS(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_RMS_SHIFT))&ISM_LAM_CONFIG_RMS_MASK)
#define ISM_LAM_CONFIG_MOS_MASK        0x4u
#define ISM_LAM_CONFIG_MOS_SHIFT       2u
#define ISM_LAM_CONFIG_MOS_WIDTH       1u
#define ISM_LAM_CONFIG_MOS(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_MOS_SHIFT))&ISM_LAM_CONFIG_MOS_MASK)
#define ISM_LAM_CONFIG_IVM_MASK        0x2u
#define ISM_LAM_CONFIG_IVM_SHIFT       1u
#define ISM_LAM_CONFIG_IVM_WIDTH       1u
#define ISM_LAM_CONFIG_IVM(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_IVM_SHIFT))&ISM_LAM_CONFIG_IVM_MASK)
#define ISM_LAM_CONFIG_IVR_MASK        0x1u
#define ISM_LAM_CONFIG_IVR_SHIFT       0u
#define ISM_LAM_CONFIG_IVR_WIDTH       1u
#define ISM_LAM_CONFIG_IVR(x)          (((uint32_t)(((uint32_t)(x))<<ISM_LAM_CONFIG_IVR_SHIFT))&ISM_LAM_CONFIG_IVR_MASK)
/* LAM_CONFIG0 Reg Mask */
#define ISM_LAM_CONFIG_MASK            0x00FF1F1Fu
/* LAM_COUNTER Bit Fields */
#define ISM_LAM_COUNTER_CNT_MASK       0xFFFFFFu
#define ISM_LAM_COUNTER_CNT_SHIFT      0u
#define ISM_LAM_COUNTER_CNT_WIDTH      24u
#define ISM_LAM_COUNTER_CNT(x)         (((uint32_t)(((uint32_t)(x))<<ISM_LAM_COUNTER_CNT_SHIFT))&ISM_LAM_COUNTER_CNT_MASK)
/* LAM_COUNTER0 Reg Mask */
#define ISM_LAM_COUNTER_MASK           0x00FFFFFFu
/**
 * @}
 */ /* end of group ISM_Register_Masks */
/**
 * @}
 */ /* end of group ISM_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
