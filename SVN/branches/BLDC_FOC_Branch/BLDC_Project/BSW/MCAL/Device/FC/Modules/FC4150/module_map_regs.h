#ifndef _MODULE_MAP_KJO_Ufdi15_REGS_H_
#define _MODULE_MAP_KJO_Ufdi15_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- MAP Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup MAP_Peripheral_Access_Layer MAP Peripheral Access Layer
 * @{
 */
/** MAP - Size of Registers Arrays */
/** MAP - Register Layout Typedef */
#define MAP_ACUR_COUNT 7
typedef struct {
  __IO uint32_t CSR                           ; /* Control and Status Register, offset: 0x0 */
       uint8_t  RESERVED_0[20];
  __I  uint32_t FAR                           ; /* Fault Address Register, offset: 0x18 */
  __IO uint32_t FIR                           ; /* Fault Information Register, offset: 0x1c */
       uint8_t  RESERVED_1[992];
  __I  uint32_t STA_RD0                       ; /* Start Address Register in Region Descriptor0, offset: 0x400 */
  __I  uint32_t ENA_RD0                       ; /* End Address Register in Region Descriptor0, offset: 0x404 */
  __IO uint32_t MAC_RD0                       ; /* MAP access control register in region descriptor0, offset: 0x408 */
  __I  uint32_t EN_RD0                        ; /* Enable Register in Region Descriptor0, offset: 0x40c */
  __IO uint32_t STA_RD1                       ; /* Start Address Register in Region Descriptor n (n = 1~7), offset: 0x410 */
  __IO uint32_t ENA_RD1                       ; /* End Address Register in Region Descriptor n(n = 1~7), offset: 0x414 */
  __IO uint32_t MAC_RD1                       ; /* MAP Access Control Register in Region Descriptor n (n = 1~7), offset: 0x418 */
  __IO uint32_t EN_RD1                        ; /* Enable Register in Region Descriptor n (n = 1~7), offset: 0x41c */
  __IO uint32_t STA_RD2                       ; /* Start Address Register in Region Descriptor n (n = 1~7), offset: 0x420 */
  __IO uint32_t ENA_RD2                       ; /* End Address Register in Region Descriptor n(n = 1~7), offset: 0x424 */
  __IO uint32_t MAC_RD2                       ; /* MAP Access Control Register in Region Descriptor n (n = 1~7), offset: 0x428 */
  __IO uint32_t EN_RD2                        ; /* Enable Register in Region Descriptor n (n = 1~7), offset: 0x42c */
  __IO uint32_t STA_RD3                       ; /* Start Address Register in Region Descriptor n (n = 1~7), offset: 0x430 */
  __IO uint32_t ENA_RD3                       ; /* End Address Register in Region Descriptor n(n = 1~7), offset: 0x434 */
  __IO uint32_t MAC_RD3                       ; /* MAP Access Control Register in Region Descriptor n (n = 1~7), offset: 0x438 */
  __IO uint32_t EN_RD3                        ; /* Enable Register in Region Descriptor n (n = 1~7), offset: 0x43c */
  __IO uint32_t STA_RD4                       ; /* Start Address Register in Region Descriptor n (n = 1~7), offset: 0x440 */
  __IO uint32_t ENA_RD4                       ; /* End Address Register in Region Descriptor n(n = 1~7), offset: 0x444 */
  __IO uint32_t MAC_RD4                       ; /* MAP Access Control Register in Region Descriptor n (n = 1~7), offset: 0x448 */
  __IO uint32_t EN_RD4                        ; /* Enable Register in Region Descriptor n (n = 1~7), offset: 0x44c */
  __IO uint32_t STA_RD5                       ; /* Start Address Register in Region Descriptor n (n = 1~7), offset: 0x450 */
  __IO uint32_t ENA_RD5                       ; /* End Address Register in Region Descriptor n(n = 1~7), offset: 0x454 */
  __IO uint32_t MAC_RD5                       ; /* MAP Access Control Register in Region Descriptor n (n = 1~7), offset: 0x458 */
  __IO uint32_t EN_RD5                        ; /* Enable Register in Region Descriptor n (n = 1~7), offset: 0x45c */
  __IO uint32_t STA_RD6                       ; /* Start Address Register in Region Descriptor n (n = 1~7), offset: 0x460 */
  __IO uint32_t ENA_RD6                       ; /* End Address Register in Region Descriptor n(n = 1~7), offset: 0x464 */
  __IO uint32_t MAC_RD6                       ; /* MAP Access Control Register in Region Descriptor n (n = 1~7), offset: 0x468 */
  __IO uint32_t EN_RD6                        ; /* Enable Register in Region Descriptor n (n = 1~7), offset: 0x46c */
  __IO uint32_t STA_RD7                       ; /* Start Address Register in Region Descriptor n (n = 1~7), offset: 0x470 */
  __IO uint32_t ENA_RD7                       ; /* End Address Register in Region Descriptor n(n = 1~7), offset: 0x474 */
  __IO uint32_t MAC_RD7                       ; /* MAP Access Control Register in Region Descriptor n (n = 1~7), offset: 0x478 */
  __IO uint32_t EN_RD7                        ; /* Enable Register in Region Descriptor n (n = 1~7), offset: 0x47c */
       uint8_t  RESERVED_2[896];
  __IO uint32_t ACUR0                         ; /* Access Control Update Register in Region Descriptor0, offset: 0x800 */
  __IO uint32_t ACUR[MAP_ACUR_COUNT]          ; /* Access Control Update Register in Region Descriptor n (n = 1~7), offset: 0x804 */
} MAP_Type, *MAP_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- MAP Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup MAP_Register_Masks MAP Register Masks
 * @{
 */
 
/* CSR Bit Fields */
#define MAP_CSR_ERRP1_MASK             0x40000000u
#define MAP_CSR_ERRP1_SHIFT            30u
#define MAP_CSR_ERRP1_WIDTH            1u
#define MAP_CSR_ERRP1(x)               (((uint32_t)(((uint32_t)(x))<<MAP_CSR_ERRP1_SHIFT))&MAP_CSR_ERRP1_MASK)
#define MAP_CSR_GE_MASK                0x1u
#define MAP_CSR_GE_SHIFT               0u
#define MAP_CSR_GE_WIDTH               1u
#define MAP_CSR_GE(x)                  (((uint32_t)(((uint32_t)(x))<<MAP_CSR_GE_SHIFT))&MAP_CSR_GE_MASK)
/* CSR Reg Mask */
#define MAP_CSR_MASK                   0x40000001u
/* FAR Bit Fields */
#define MAP_FAR_FADDR_MASK             0xFFFFFFFFu
#define MAP_FAR_FADDR_SHIFT            0u
#define MAP_FAR_FADDR_WIDTH            32u
#define MAP_FAR_FADDR(x)               (((uint32_t)(((uint32_t)(x))<<MAP_FAR_FADDR_SHIFT))&MAP_FAR_FADDR_MASK)
/* FAR Reg Mask */
#define MAP_FAR_MASK                   0xFFFFFFFFu
/* FIR Bit Fields */
#define MAP_FIR_EC_MASK                0xFFFF0000u
#define MAP_FIR_EC_SHIFT               16u
#define MAP_FIR_EC_WIDTH               16u
#define MAP_FIR_EC(x)                  (((uint32_t)(((uint32_t)(x))<<MAP_FIR_EC_SHIFT))&MAP_FIR_EC_MASK)
#define MAP_FIR_EMID_MASK              0xF0u
#define MAP_FIR_EMID_SHIFT             4u
#define MAP_FIR_EMID_WIDTH             4u
#define MAP_FIR_EMID(x)                (((uint32_t)(((uint32_t)(x))<<MAP_FIR_EMID_SHIFT))&MAP_FIR_EMID_MASK)
#define MAP_FIR_EATT_MASK              0xEu
#define MAP_FIR_EATT_SHIFT             1u
#define MAP_FIR_EATT_WIDTH             3u
#define MAP_FIR_EATT(x)                (((uint32_t)(((uint32_t)(x))<<MAP_FIR_EATT_SHIFT))&MAP_FIR_EATT_MASK)
#define MAP_FIR_ET_MASK                0x1u
#define MAP_FIR_ET_SHIFT               0u
#define MAP_FIR_ET_WIDTH               1u
#define MAP_FIR_ET(x)                  (((uint32_t)(((uint32_t)(x))<<MAP_FIR_ET_SHIFT))&MAP_FIR_ET_MASK)
/* FIR Reg Mask */
#define MAP_FIR_MASK                   0xFFFF00FFu
/* STA_RD0 Bit Fields */
#define MAP_STA_RD0_SADDR_MASK         0xFFFFFFE0u
#define MAP_STA_RD0_SADDR_SHIFT        5u
#define MAP_STA_RD0_SADDR_WIDTH        27u
#define MAP_STA_RD0_SADDR(x)           (((uint32_t)(((uint32_t)(x))<<MAP_STA_RD0_SADDR_SHIFT))&MAP_STA_RD0_SADDR_MASK)
/* STA_RD0 Reg Mask */
#define MAP_STA_RD0_MASK               0xFFFFFFE0u
/* STA_RD Bit Fields */
#define MAP_STA_RD_SADDR_MASK          0xFFFFFFE0u
#define MAP_STA_RD_SADDR_SHIFT         5u
#define MAP_STA_RD_SADDR_WIDTH         27u
#define MAP_STA_RD_SADDR(x)            (((uint32_t)(((uint32_t)(x))<<MAP_STA_RD_SADDR_SHIFT))&MAP_STA_RD_SADDR_MASK)
/* STA_RD1 Reg Mask */
#define MAP_STA_RD_MASK                0xFFFFFFE0u
/* ENA_RD0 Bit Fields */
#define MAP_ENA_RD0_ENADDR_MASK        0xFFFFFFE0u
#define MAP_ENA_RD0_ENADDR_SHIFT       5u
#define MAP_ENA_RD0_ENADDR_WIDTH       27u
#define MAP_ENA_RD0_ENADDR(x)          (((uint32_t)(((uint32_t)(x))<<MAP_ENA_RD0_ENADDR_SHIFT))&MAP_ENA_RD0_ENADDR_MASK)
/* ENA_RD0 Reg Mask */
#define MAP_ENA_RD0_MASK               0xFFFFFFE0u
/* ENA_RD Bit Fields */
#define MAP_ENA_RD_ENADDR_MASK         0xFFFFFFE0u
#define MAP_ENA_RD_ENADDR_SHIFT        5u
#define MAP_ENA_RD_ENADDR_WIDTH        27u
#define MAP_ENA_RD_ENADDR(x)           (((uint32_t)(((uint32_t)(x))<<MAP_ENA_RD_ENADDR_SHIFT))&MAP_ENA_RD_ENADDR_MASK)
/* ENA_RD1 Reg Mask */
#define MAP_ENA_RD_MASK                0xFFFFFFE0u
/* MAC_RD0 Bit Fields */
#define MAP_MAC_RD0_BM4AE_MASK         0x3000000u
#define MAP_MAC_RD0_BM4AE_SHIFT        24u
#define MAP_MAC_RD0_BM4AE_WIDTH        2u
#define MAP_MAC_RD0_BM4AE(x)           (((uint32_t)(((uint32_t)(x))<<MAP_MAC_RD0_BM4AE_SHIFT))&MAP_MAC_RD0_BM4AE_MASK)
#define MAP_MAC_RD0_BM3AE_MASK         0xF80000u
#define MAP_MAC_RD0_BM3AE_SHIFT        19u
#define MAP_MAC_RD0_BM3AE_WIDTH        5u
#define MAP_MAC_RD0_BM3AE(x)           (((uint32_t)(((uint32_t)(x))<<MAP_MAC_RD0_BM3AE_SHIFT))&MAP_MAC_RD0_BM3AE_MASK)
#define MAP_MAC_RD0_BM2AE_MASK         0x3E000u
#define MAP_MAC_RD0_BM2AE_SHIFT        13u
#define MAP_MAC_RD0_BM2AE_WIDTH        5u
#define MAP_MAC_RD0_BM2AE(x)           (((uint32_t)(((uint32_t)(x))<<MAP_MAC_RD0_BM2AE_SHIFT))&MAP_MAC_RD0_BM2AE_MASK)
/* MAC_RD0 Reg Mask */
#define MAP_MAC_RD0_MASK               0x03FBE000u
/* MAC_RD Bit Fields */
#define MAP_MAC_RD_BM4AE_MASK          0x3000000u
#define MAP_MAC_RD_BM4AE_SHIFT         24u
#define MAP_MAC_RD_BM4AE_WIDTH         2u
#define MAP_MAC_RD_BM4AE(x)            (((uint32_t)(((uint32_t)(x))<<MAP_MAC_RD_BM4AE_SHIFT))&MAP_MAC_RD_BM4AE_MASK)
#define MAP_MAC_RD_BM3AE_MASK          0xF80000u
#define MAP_MAC_RD_BM3AE_SHIFT         19u
#define MAP_MAC_RD_BM3AE_WIDTH         5u
#define MAP_MAC_RD_BM3AE(x)            (((uint32_t)(((uint32_t)(x))<<MAP_MAC_RD_BM3AE_SHIFT))&MAP_MAC_RD_BM3AE_MASK)
#define MAP_MAC_RD_BM2AE_MASK          0x3E000u
#define MAP_MAC_RD_BM2AE_SHIFT         13u
#define MAP_MAC_RD_BM2AE_WIDTH         5u
#define MAP_MAC_RD_BM2AE(x)            (((uint32_t)(((uint32_t)(x))<<MAP_MAC_RD_BM2AE_SHIFT))&MAP_MAC_RD_BM2AE_MASK)
/* MAC_RD1 Reg Mask */
#define MAP_MAC_RD_MASK                0x03FBE000u
/* EN_RD0 Bit Fields */
#define MAP_EN_RD0_EN_MASK             0x1u
#define MAP_EN_RD0_EN_SHIFT            0u
#define MAP_EN_RD0_EN_WIDTH            1u
#define MAP_EN_RD0_EN(x)               (((uint32_t)(((uint32_t)(x))<<MAP_EN_RD0_EN_SHIFT))&MAP_EN_RD0_EN_MASK)
/* EN_RD0 Reg Mask */
#define MAP_EN_RD0_MASK                0x00000001u
/* EN_RD Bit Fields */
#define MAP_EN_RD_EN_MASK              0x1u
#define MAP_EN_RD_EN_SHIFT             0u
#define MAP_EN_RD_EN_WIDTH             1u
#define MAP_EN_RD_EN(x)                (((uint32_t)(((uint32_t)(x))<<MAP_EN_RD_EN_SHIFT))&MAP_EN_RD_EN_MASK)
/* EN_RD1 Reg Mask */
#define MAP_EN_RD_MASK                 0x00000001u
/* ACUR0 Bit Fields */
#define MAP_ACUR0_BM4AE_MASK           0x3000000u
#define MAP_ACUR0_BM4AE_SHIFT          24u
#define MAP_ACUR0_BM4AE_WIDTH          2u
#define MAP_ACUR0_BM4AE(x)             (((uint32_t)(((uint32_t)(x))<<MAP_ACUR0_BM4AE_SHIFT))&MAP_ACUR0_BM4AE_MASK)
#define MAP_ACUR0_BM3AE_MASK           0xF80000u
#define MAP_ACUR0_BM3AE_SHIFT          19u
#define MAP_ACUR0_BM3AE_WIDTH          5u
#define MAP_ACUR0_BM3AE(x)             (((uint32_t)(((uint32_t)(x))<<MAP_ACUR0_BM3AE_SHIFT))&MAP_ACUR0_BM3AE_MASK)
#define MAP_ACUR0_BM2AE_MASK           0x3E000u
#define MAP_ACUR0_BM2AE_SHIFT          13u
#define MAP_ACUR0_BM2AE_WIDTH          5u
#define MAP_ACUR0_BM2AE(x)             (((uint32_t)(((uint32_t)(x))<<MAP_ACUR0_BM2AE_SHIFT))&MAP_ACUR0_BM2AE_MASK)
/* ACUR0 Reg Mask */
#define MAP_ACUR0_MASK                 0x03FBE000u
/* ACUR Bit Fields */
#define MAP_ACUR_BM4AE_MASK            0x3000000u
#define MAP_ACUR_BM4AE_SHIFT           24u
#define MAP_ACUR_BM4AE_WIDTH           2u
#define MAP_ACUR_BM4AE(x)              (((uint32_t)(((uint32_t)(x))<<MAP_ACUR_BM4AE_SHIFT))&MAP_ACUR_BM4AE_MASK)
#define MAP_ACUR_BM3AE_MASK            0xF80000u
#define MAP_ACUR_BM3AE_SHIFT           19u
#define MAP_ACUR_BM3AE_WIDTH           5u
#define MAP_ACUR_BM3AE(x)              (((uint32_t)(((uint32_t)(x))<<MAP_ACUR_BM3AE_SHIFT))&MAP_ACUR_BM3AE_MASK)
#define MAP_ACUR_BM2AE_MASK            0x3E000u
#define MAP_ACUR_BM2AE_SHIFT           13u
#define MAP_ACUR_BM2AE_WIDTH           5u
#define MAP_ACUR_BM2AE(x)              (((uint32_t)(((uint32_t)(x))<<MAP_ACUR_BM2AE_SHIFT))&MAP_ACUR_BM2AE_MASK)
/* ACUR1 Reg Mask */
#define MAP_ACUR_MASK                  0x03FBE000u
/**
 * @}
 */ /* end of group MAP_Register_Masks */
/**
 * @}
 */ /* end of group MAP_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
