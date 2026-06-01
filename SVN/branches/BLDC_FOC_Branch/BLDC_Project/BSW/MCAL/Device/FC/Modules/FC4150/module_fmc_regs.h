#ifndef _MODULE_FMC_KJO_Ufdi26_REGS_H_
#define _MODULE_FMC_KJO_Ufdi26_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- FMC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FMC_Peripheral_Access_Layer FMC Peripheral Access Layer
 * @{
 */
/** FMC - Size of Registers Arrays */
/** FMC - Register Layout Typedef */
#define FMC_FB_FPELCK_COUNT 3
#define FMC_FB_CPELCK_COUNT 2
typedef struct {
  __IO uint32_t FAPC0                         ; /* Flash Access Port Control 0, offset: 0x0 */
       uint8_t  RESERVED_0[12];
  __IO uint32_t FEEC                          ; /* Flash ECC Error Control, offset: 0x10 */
       uint8_t  RESERVED_1[748];
  __IO uint32_t FPESA_L                       ; /* Flash Program Erase Start Address Logical, offset: 0x300 */
  __I  uint32_t FPESA_P                       ; /* Flash Program Erase Start Address Physical, offset: 0x304 */
       uint8_t  RESERVED_2[56];
  __IO uint32_t FB_FPELCK[FMC_FB_FPELCK_COUNT]; /* Flash Block n Fine Program Erase Lock, offset: 0x340 */
       uint8_t  RESERVED_3[12];
  __IO uint32_t FN_FPELCK                     ; /* Flash NVR Fine Program Erase Lock, offset: 0x358 */
  __IO uint32_t FB_CPELCK[FMC_FB_CPELCK_COUNT]; /* Flash Block n Coarse Program Erase Lock, offset: 0x35c */
       uint8_t  RESERVED_4[412];
  __IO uint32_t OTA_CTRL                      ; /* FLASH OTA Control, offset: 0x500 */
  __IO uint32_t OTA_START_ADDR                ; /* FLASH OTA Start Address, offset: 0x504 */
  __IO uint32_t OTA_END_ADDR                  ; /* FLASH OTA End Address, offset: 0x508 */
  __I  uint32_t OTA_VER_LOC                   ; /* FLASH OTA Version Location, offset: 0x50C */
  __I  uint32_t OTA_ACT_VER                   ; /* FLASH OTA Active Version, offset: 0x510 */
} FMC_Type, *FMC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FMC Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FMC_Register_Masks FMC Register Masks
 * @{
 */
 
/* FAPC0 Bit Fields */
#define FMC_FAPC0_DBPEN_MASK           0x20u
#define FMC_FAPC0_DBPEN_SHIFT          5u
#define FMC_FAPC0_DBPEN_WIDTH          1u
#define FMC_FAPC0_DBPEN(x)             (((uint32_t)(((uint32_t)(x))<<FMC_FAPC0_DBPEN_SHIFT))&FMC_FAPC0_DBPEN_MASK)
#define FMC_FAPC0_CBPEN_MASK           0x10u
#define FMC_FAPC0_CBPEN_SHIFT          4u
#define FMC_FAPC0_CBPEN_WIDTH          1u
#define FMC_FAPC0_CBPEN(x)             (((uint32_t)(((uint32_t)(x))<<FMC_FAPC0_CBPEN_SHIFT))&FMC_FAPC0_CBPEN_MASK)
#define FMC_FAPC0_DBBEN_MASK           0x2u
#define FMC_FAPC0_DBBEN_SHIFT          1u
#define FMC_FAPC0_DBBEN_WIDTH          1u
#define FMC_FAPC0_DBBEN(x)             (((uint32_t)(((uint32_t)(x))<<FMC_FAPC0_DBBEN_SHIFT))&FMC_FAPC0_DBBEN_MASK)
#define FMC_FAPC0_CBBEN_MASK           0x1u
#define FMC_FAPC0_CBBEN_SHIFT          0u
#define FMC_FAPC0_CBBEN_WIDTH          1u
#define FMC_FAPC0_CBBEN(x)             (((uint32_t)(((uint32_t)(x))<<FMC_FAPC0_CBBEN_SHIFT))&FMC_FAPC0_CBBEN_MASK)
/* FAPC0 Reg Mask */
#define FMC_FAPC0_MASK                 0x00000033u
/* FEEC Bit Fields */
#define FMC_FEEC_DDBEE_MASK            0x80u
#define FMC_FEEC_DDBEE_SHIFT           7u
#define FMC_FEEC_DDBEE_WIDTH           1u
#define FMC_FEEC_DDBEE(x)              (((uint32_t)(((uint32_t)(x))<<FMC_FEEC_DDBEE_SHIFT))&FMC_FEEC_DDBEE_MASK)
/* FEEC Reg Mask */
#define FMC_FEEC_MASK                  0x00000080u
/* FPESA_L Bit Fields */
#define FMC_FPESA_L_PESA_L_MASK        0xFFFFFFFFu
#define FMC_FPESA_L_PESA_L_SHIFT       0u
#define FMC_FPESA_L_PESA_L_WIDTH       32u
#define FMC_FPESA_L_PESA_L(x)          (((uint32_t)(((uint32_t)(x))<<FMC_FPESA_L_PESA_L_SHIFT))&FMC_FPESA_L_PESA_L_MASK)
/* FPESA_L Reg Mask */
#define FMC_FPESA_L_MASK               0xFFFFFFFFu
/* FPESA_P Bit Fields */
#define FMC_FPESA_P_PESA_P_MASK        0xFFFFFFFFu
#define FMC_FPESA_P_PESA_P_SHIFT       0u
#define FMC_FPESA_P_PESA_P_WIDTH       32u
#define FMC_FPESA_P_PESA_P(x)          (((uint32_t)(((uint32_t)(x))<<FMC_FPESA_P_PESA_P_SHIFT))&FMC_FPESA_P_PESA_P_MASK)
/* FPESA_P Reg Mask */
#define FMC_FPESA_P_MASK               0xFFFFFFFFu
/* FB_FPELCK Bit Fields */
#define FMC_FB_FPELCK_FPELCK_MASK      0xFFFFFFFFu
#define FMC_FB_FPELCK_FPELCK_SHIFT     0u
#define FMC_FB_FPELCK_FPELCK_WIDTH     32u
#define FMC_FB_FPELCK_FPELCK(x)        (((uint32_t)(((uint32_t)(x))<<FMC_FB_FPELCK_FPELCK_SHIFT))&FMC_FB_FPELCK_FPELCK_MASK)
/* FB_FPELCK0 Reg Mask */
#define FMC_FB_FPELCK_MASK             0xFFFFFFFFu
/* FN_FPELCK Bit Fields */
#define FMC_FN_FPELCK_FPELCK_MASK      0x1u
#define FMC_FN_FPELCK_FPELCK_SHIFT     0u
#define FMC_FN_FPELCK_FPELCK_WIDTH     1u
#define FMC_FN_FPELCK_FPELCK(x)        (((uint32_t)(((uint32_t)(x))<<FMC_FN_FPELCK_FPELCK_SHIFT))&FMC_FN_FPELCK_FPELCK_MASK)
/* FN_FPELCK Reg Mask */
#define FMC_FN_FPELCK_MASK             0x00000001u
/* FB_CPELCK Bit Fields */
#define FMC_FB_CPELCK_CPELCK_MASK      0xFFFFFFFFu
#define FMC_FB_CPELCK_CPELCK_SHIFT     0u
#define FMC_FB_CPELCK_CPELCK_WIDTH     32u
#define FMC_FB_CPELCK_CPELCK(x)        (((uint32_t)(((uint32_t)(x))<<FMC_FB_CPELCK_CPELCK_SHIFT))&FMC_FB_CPELCK_CPELCK_MASK)
/* FB_CPELCK0 Reg Mask */
#define FMC_FB_CPELCK_MASK             0xFFFFFFFFu
/* OTA_CTRL Bit Fields */
#define FMC_OTA_CTRL_OTA_LOCK_MASK     0x40u
#define FMC_OTA_CTRL_OTA_LOCK_SHIFT    6u
#define FMC_OTA_CTRL_OTA_LOCK_WIDTH    1u
#define FMC_OTA_CTRL_OTA_LOCK(x)       (((uint32_t)(((uint32_t)(x))<<FMC_OTA_CTRL_OTA_LOCK_SHIFT))&FMC_OTA_CTRL_OTA_LOCK_MASK)
#define FMC_OTA_CTRL_OTA_ACTIVE_MASK   0x20u
#define FMC_OTA_CTRL_OTA_ACTIVE_SHIFT  5u
#define FMC_OTA_CTRL_OTA_ACTIVE_WIDTH  1u
#define FMC_OTA_CTRL_OTA_ACTIVE(x)     (((uint32_t)(((uint32_t)(x))<<FMC_OTA_CTRL_OTA_ACTIVE_SHIFT))&FMC_OTA_CTRL_OTA_ACTIVE_MASK)
#define FMC_OTA_CTRL_OTA_EN_MASK       0x1Fu
#define FMC_OTA_CTRL_OTA_EN_SHIFT      0u
#define FMC_OTA_CTRL_OTA_EN_WIDTH      5u
#define FMC_OTA_CTRL_OTA_EN(x)         (((uint32_t)(((uint32_t)(x))<<FMC_OTA_CTRL_OTA_EN_SHIFT))&FMC_OTA_CTRL_OTA_EN_MASK)
/* OTA_CTRL Reg Mask */
#define FMC_OTA_CTRL_MASK              0x0000007Fu
/* OTA_START_ADDR Bit Fields */
#define FMC_OTA_START_ADDR_OTA_START_ADDR_MASK 0xFE000u
#define FMC_OTA_START_ADDR_OTA_START_ADDR_SHIFT 13u
#define FMC_OTA_START_ADDR_OTA_START_ADDR_WIDTH 7u
#define FMC_OTA_START_ADDR_OTA_START_ADDR(x) (((uint32_t)(((uint32_t)(x))<<FMC_OTA_START_ADDR_OTA_START_ADDR_SHIFT))&FMC_OTA_START_ADDR_OTA_START_ADDR_MASK)
/* OTA_START_ADDR Reg Mask */
#define FMC_OTA_START_ADDR_MASK        0x000FE000u
/* OTA_END_ADDR Bit Fields */
#define FMC_OTA_END_ADDR_OTA_END_ADDR_MASK 0xFE000u
#define FMC_OTA_END_ADDR_OTA_END_ADDR_SHIFT 13u
#define FMC_OTA_END_ADDR_OTA_END_ADDR_WIDTH 7u
#define FMC_OTA_END_ADDR_OTA_END_ADDR(x) (((uint32_t)(((uint32_t)(x))<<FMC_OTA_END_ADDR_OTA_END_ADDR_SHIFT))&FMC_OTA_END_ADDR_OTA_END_ADDR_MASK)
/* OTA_END_ADDR Reg Mask */
#define FMC_OTA_END_ADDR_MASK          0x000FE000u
/* OTA_VER_LOC Bit Fields */
#define FMC_OTA_VER_LOC_OTA_VER_LOC_MASK 0xFFFFFu
#define FMC_OTA_VER_LOC_OTA_VER_LOC_SHIFT 0u
#define FMC_OTA_VER_LOC_OTA_VER_LOC_WIDTH 20u
#define FMC_OTA_VER_LOC_OTA_VER_LOC(x) (((uint32_t)(((uint32_t)(x))<<FMC_OTA_VER_LOC_OTA_VER_LOC_SHIFT))&FMC_OTA_VER_LOC_OTA_VER_LOC_MASK)
/* OTA_VER_LOC Reg Mask */
#define FMC_OTA_VER_LOC_MASK           0x000FFFFFu
/* OTA_ACT_VER Bit Fields */
#define FMC_OTA_ACT_VER_OTA_ACT_VER_MASK 0xFFFFu
#define FMC_OTA_ACT_VER_OTA_ACT_VER_SHIFT 0u
#define FMC_OTA_ACT_VER_OTA_ACT_VER_WIDTH 16u
#define FMC_OTA_ACT_VER_OTA_ACT_VER(x) (((uint32_t)(((uint32_t)(x))<<FMC_OTA_ACT_VER_OTA_ACT_VER_SHIFT))&FMC_OTA_ACT_VER_OTA_ACT_VER_MASK)
/* OTA_ACT_VER Reg Mask */
#define FMC_OTA_ACT_VER_MASK           0x0000FFFFu
/**
 * @}
 */ /* end of group FMC_Register_Masks */
/**
 * @}
 */ /* end of group FMC_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
