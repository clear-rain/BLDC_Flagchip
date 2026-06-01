#ifndef _MODULE_FCIIC_KJO_Ufdi5_REGS_H_
#define _MODULE_FCIIC_KJO_Ufdi5_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- FCIIC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCIIC_Peripheral_Access_Layer FCIIC Peripheral Access Layer
 * @{
 */
/** FCIIC - Size of Registers Arrays */
/** FCIIC - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[16];
  __IO uint32_t MCR                           ; /* Master Control, offset: 0x10 */
  __IO uint32_t MSR                           ; /* Master Status, offset: 0x14 */
  __IO uint32_t MIER                          ; /* Master Interrupt Enable, offset: 0x18 */
  __IO uint32_t MDER                          ; /* Master DMA Enable, offset: 0x1C */
  __IO uint32_t MCFGR0                        ; /* Master Configuration 0, offset: 0x20 */
  __IO uint32_t MCFGR1                        ; /* Master Configuration 1, offset: 0x24 */
  __IO uint32_t MCFGR2                        ; /* Master Configuration 2, offset: 0x28 */
  __IO uint32_t MCFGR3                        ; /* Master Configuration 3, offset: 0x2C */
       uint8_t  RESERVED_1[16];
  __IO uint32_t MDMR                          ; /* Master Data Match, offset: 0x40 */
       uint8_t  RESERVED_2[4];
  __IO uint32_t MCCR                          ; /* Master Clock Configuration, offset: 0x48 */
       uint8_t  RESERVED_3[12];
  __IO uint32_t MFCR                          ; /* Master FIFO Control, offset: 0x58 */
  __I  uint32_t MFSR                          ; /* Master FIFO Status, offset: 0x5C */
  __O  uint32_t MTDR                          ; /* Master Transmit Data, offset: 0x60 */
       uint8_t  RESERVED_4[12];
  __I  uint32_t MRDR                          ; /* Master Receive Data, offset: 0x70 */
       uint8_t  RESERVED_5[16];
       uint8_t  RESERVED_6[140];
  __IO uint32_t SCR                           ; /* Slave Control, offset: 0x110 */
  __IO uint32_t SSR                           ; /* Slave Status, offset: 0x114 */
  __IO uint32_t SIER                          ; /* Slave Interrupt Enable, offset: 0x118 */
  __IO uint32_t SDER                          ; /* Slave DMA Enable, offset: 0x11C */
       uint8_t  RESERVED_7[4];
  __IO uint32_t SCFGR1                        ; /* Slave Configuration 1, offset: 0x124 */
  __IO uint32_t SCFGR2                        ; /* Slave Configuration 2, offset: 0x128 */
       uint8_t  RESERVED_8[20];
  __IO uint32_t SAMR                          ; /* Slave Address Match, offset: 0x140 */
       uint8_t  RESERVED_9[12];
  __I  uint32_t SASR                          ; /* Slave Address Status, offset: 0x150 */
  __IO uint32_t STAR                          ; /* Slave Transmit ACK, offset: 0x154 */
       uint8_t  RESERVED_10[8];
  __O  uint32_t STDR                          ; /* Slave Transmit Data, offset: 0x160 */
       uint8_t  RESERVED_11[12];
  __I  uint32_t SRDR                          ; /* Slave Receive Data, offset: 0x170 */
} FCIIC_Type, *FCIIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FCIIC Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FCIIC_Register_Masks FCIIC Register Masks
 * @{
 */
 
/* MCR Bit Fields */
#define FCIIC_MCR_RRF_MASK             0x200u
#define FCIIC_MCR_RRF_SHIFT            9u
#define FCIIC_MCR_RRF_WIDTH            1u
#define FCIIC_MCR_RRF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MCR_RRF_SHIFT))&FCIIC_MCR_RRF_MASK)
#define FCIIC_MCR_RTF_MASK             0x100u
#define FCIIC_MCR_RTF_SHIFT            8u
#define FCIIC_MCR_RTF_WIDTH            1u
#define FCIIC_MCR_RTF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MCR_RTF_SHIFT))&FCIIC_MCR_RTF_MASK)
#define FCIIC_MCR_DBGEN_MASK           0x8u
#define FCIIC_MCR_DBGEN_SHIFT          3u
#define FCIIC_MCR_DBGEN_WIDTH          1u
#define FCIIC_MCR_DBGEN(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MCR_DBGEN_SHIFT))&FCIIC_MCR_DBGEN_MASK)
#define FCIIC_MCR_RST_MASK             0x2u
#define FCIIC_MCR_RST_SHIFT            1u
#define FCIIC_MCR_RST_WIDTH            1u
#define FCIIC_MCR_RST(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MCR_RST_SHIFT))&FCIIC_MCR_RST_MASK)
#define FCIIC_MCR_MEN_MASK             0x1u
#define FCIIC_MCR_MEN_SHIFT            0u
#define FCIIC_MCR_MEN_WIDTH            1u
#define FCIIC_MCR_MEN(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MCR_MEN_SHIFT))&FCIIC_MCR_MEN_MASK)
/* MCR Reg Mask */
#define FCIIC_MCR_MASK                 0x0000030Bu
/* MSR Bit Fields */
#define FCIIC_MSR_BBF_MASK             0x2000000u
#define FCIIC_MSR_BBF_SHIFT            25u
#define FCIIC_MSR_BBF_WIDTH            1u
#define FCIIC_MSR_BBF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_BBF_SHIFT))&FCIIC_MSR_BBF_MASK)
#define FCIIC_MSR_MBF_MASK             0x1000000u
#define FCIIC_MSR_MBF_SHIFT            24u
#define FCIIC_MSR_MBF_WIDTH            1u
#define FCIIC_MSR_MBF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_MBF_SHIFT))&FCIIC_MSR_MBF_MASK)
#define FCIIC_MSR_DMF_MASK             0x4000u
#define FCIIC_MSR_DMF_SHIFT            14u
#define FCIIC_MSR_DMF_WIDTH            1u
#define FCIIC_MSR_DMF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_DMF_SHIFT))&FCIIC_MSR_DMF_MASK)
#define FCIIC_MSR_PLTF_MASK            0x2000u
#define FCIIC_MSR_PLTF_SHIFT           13u
#define FCIIC_MSR_PLTF_WIDTH           1u
#define FCIIC_MSR_PLTF(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_PLTF_SHIFT))&FCIIC_MSR_PLTF_MASK)
#define FCIIC_MSR_FEF_MASK             0x1000u
#define FCIIC_MSR_FEF_SHIFT            12u
#define FCIIC_MSR_FEF_WIDTH            1u
#define FCIIC_MSR_FEF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_FEF_SHIFT))&FCIIC_MSR_FEF_MASK)
#define FCIIC_MSR_ALF_MASK             0x800u
#define FCIIC_MSR_ALF_SHIFT            11u
#define FCIIC_MSR_ALF_WIDTH            1u
#define FCIIC_MSR_ALF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_ALF_SHIFT))&FCIIC_MSR_ALF_MASK)
#define FCIIC_MSR_NDF_MASK             0x400u
#define FCIIC_MSR_NDF_SHIFT            10u
#define FCIIC_MSR_NDF_WIDTH            1u
#define FCIIC_MSR_NDF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_NDF_SHIFT))&FCIIC_MSR_NDF_MASK)
#define FCIIC_MSR_SDF_MASK             0x200u
#define FCIIC_MSR_SDF_SHIFT            9u
#define FCIIC_MSR_SDF_WIDTH            1u
#define FCIIC_MSR_SDF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_SDF_SHIFT))&FCIIC_MSR_SDF_MASK)
#define FCIIC_MSR_EPF_MASK             0x100u
#define FCIIC_MSR_EPF_SHIFT            8u
#define FCIIC_MSR_EPF_WIDTH            1u
#define FCIIC_MSR_EPF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_EPF_SHIFT))&FCIIC_MSR_EPF_MASK)
#define FCIIC_MSR_RDF_MASK             0x2u
#define FCIIC_MSR_RDF_SHIFT            1u
#define FCIIC_MSR_RDF_WIDTH            1u
#define FCIIC_MSR_RDF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_RDF_SHIFT))&FCIIC_MSR_RDF_MASK)
#define FCIIC_MSR_TDF_MASK             0x1u
#define FCIIC_MSR_TDF_SHIFT            0u
#define FCIIC_MSR_TDF_WIDTH            1u
#define FCIIC_MSR_TDF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_MSR_TDF_SHIFT))&FCIIC_MSR_TDF_MASK)
/* MSR Reg Mask */
#define FCIIC_MSR_MASK                 0x03007F0Fu
/* MIER Bit Fields */
#define FCIIC_MIER_DMIE_MASK           0x4000u
#define FCIIC_MIER_DMIE_SHIFT          14u
#define FCIIC_MIER_DMIE_WIDTH          1u
#define FCIIC_MIER_DMIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_DMIE_SHIFT))&FCIIC_MIER_DMIE_MASK)
#define FCIIC_MIER_PLTIE_MASK          0x2000u
#define FCIIC_MIER_PLTIE_SHIFT         13u
#define FCIIC_MIER_PLTIE_WIDTH         1u
#define FCIIC_MIER_PLTIE(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_PLTIE_SHIFT))&FCIIC_MIER_PLTIE_MASK)
#define FCIIC_MIER_FEIE_MASK           0x1000u
#define FCIIC_MIER_FEIE_SHIFT          12u
#define FCIIC_MIER_FEIE_WIDTH          1u
#define FCIIC_MIER_FEIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_FEIE_SHIFT))&FCIIC_MIER_FEIE_MASK)
#define FCIIC_MIER_ALIE_MASK           0x800u
#define FCIIC_MIER_ALIE_SHIFT          11u
#define FCIIC_MIER_ALIE_WIDTH          1u
#define FCIIC_MIER_ALIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_ALIE_SHIFT))&FCIIC_MIER_ALIE_MASK)
#define FCIIC_MIER_NDIE_MASK           0x400u
#define FCIIC_MIER_NDIE_SHIFT          10u
#define FCIIC_MIER_NDIE_WIDTH          1u
#define FCIIC_MIER_NDIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_NDIE_SHIFT))&FCIIC_MIER_NDIE_MASK)
#define FCIIC_MIER_SDIE_MASK           0x200u
#define FCIIC_MIER_SDIE_SHIFT          9u
#define FCIIC_MIER_SDIE_WIDTH          1u
#define FCIIC_MIER_SDIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_SDIE_SHIFT))&FCIIC_MIER_SDIE_MASK)
#define FCIIC_MIER_EPIE_MASK           0x100u
#define FCIIC_MIER_EPIE_SHIFT          8u
#define FCIIC_MIER_EPIE_WIDTH          1u
#define FCIIC_MIER_EPIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_EPIE_SHIFT))&FCIIC_MIER_EPIE_MASK)
#define FCIIC_MIER_RDIE_MASK           0x2u
#define FCIIC_MIER_RDIE_SHIFT          1u
#define FCIIC_MIER_RDIE_WIDTH          1u
#define FCIIC_MIER_RDIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_RDIE_SHIFT))&FCIIC_MIER_RDIE_MASK)
#define FCIIC_MIER_TDIE_MASK           0x1u
#define FCIIC_MIER_TDIE_SHIFT          0u
#define FCIIC_MIER_TDIE_WIDTH          1u
#define FCIIC_MIER_TDIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MIER_TDIE_SHIFT))&FCIIC_MIER_TDIE_MASK)
/* MIER Reg Mask */
#define FCIIC_MIER_MASK                0x00007F0Fu
/* MDER Bit Fields */
#define FCIIC_MDER_RDDE_MASK           0x2u
#define FCIIC_MDER_RDDE_SHIFT          1u
#define FCIIC_MDER_RDDE_WIDTH          1u
#define FCIIC_MDER_RDDE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MDER_RDDE_SHIFT))&FCIIC_MDER_RDDE_MASK)
#define FCIIC_MDER_TDDE_MASK           0x1u
#define FCIIC_MDER_TDDE_SHIFT          0u
#define FCIIC_MDER_TDDE_WIDTH          1u
#define FCIIC_MDER_TDDE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MDER_TDDE_SHIFT))&FCIIC_MDER_TDDE_MASK)
/* MDER Reg Mask */
#define FCIIC_MDER_MASK                0x00000003u
/* MCFGR0 Bit Fields */
#define FCIIC_MCFGR0_RDMO_MASK         0x200u
#define FCIIC_MCFGR0_RDMO_SHIFT        9u
#define FCIIC_MCFGR0_RDMO_WIDTH        1u
#define FCIIC_MCFGR0_RDMO(x)           (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR0_RDMO_SHIFT))&FCIIC_MCFGR0_RDMO_MASK)
#define FCIIC_MCFGR0_TRGEN_MASK        0x1u
#define FCIIC_MCFGR0_TRGEN_SHIFT       0u
#define FCIIC_MCFGR0_TRGEN_WIDTH       1u
#define FCIIC_MCFGR0_TRGEN(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR0_TRGEN_SHIFT))&FCIIC_MCFGR0_TRGEN_MASK)
/* MCFGR0 Reg Mask */
#define FCIIC_MCFGR0_MASK              0x00000201u
/* MCFGR1 Bit Fields */
#define FCIIC_MCFGR1_PINCFG_MASK       0x2000000u
#define FCIIC_MCFGR1_PINCFG_SHIFT      25u
#define FCIIC_MCFGR1_PINCFG_WIDTH      1u
#define FCIIC_MCFGR1_PINCFG(x)         (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR1_PINCFG_SHIFT))&FCIIC_MCFGR1_PINCFG_MASK)
#define FCIIC_MCFGR1_MATCFG_MASK       0x70000u
#define FCIIC_MCFGR1_MATCFG_SHIFT      16u
#define FCIIC_MCFGR1_MATCFG_WIDTH      3u
#define FCIIC_MCFGR1_MATCFG(x)         (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR1_MATCFG_SHIFT))&FCIIC_MCFGR1_MATCFG_MASK)
#define FCIIC_MCFGR1_TIMECFG_MASK      0x400u
#define FCIIC_MCFGR1_TIMECFG_SHIFT     10u
#define FCIIC_MCFGR1_TIMECFG_WIDTH     1u
#define FCIIC_MCFGR1_TIMECFG(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR1_TIMECFG_SHIFT))&FCIIC_MCFGR1_TIMECFG_MASK)
#define FCIIC_MCFGR1_IGNACK_MASK       0x200u
#define FCIIC_MCFGR1_IGNACK_SHIFT      9u
#define FCIIC_MCFGR1_IGNACK_WIDTH      1u
#define FCIIC_MCFGR1_IGNACK(x)         (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR1_IGNACK_SHIFT))&FCIIC_MCFGR1_IGNACK_MASK)
#define FCIIC_MCFGR1_AUTOSTOP_MASK     0x100u
#define FCIIC_MCFGR1_AUTOSTOP_SHIFT    8u
#define FCIIC_MCFGR1_AUTOSTOP_WIDTH    1u
#define FCIIC_MCFGR1_AUTOSTOP(x)       (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR1_AUTOSTOP_SHIFT))&FCIIC_MCFGR1_AUTOSTOP_MASK)
#define FCIIC_MCFGR1_PRESCALE_MASK     0x7u
#define FCIIC_MCFGR1_PRESCALE_SHIFT    0u
#define FCIIC_MCFGR1_PRESCALE_WIDTH    3u
#define FCIIC_MCFGR1_PRESCALE(x)       (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR1_PRESCALE_SHIFT))&FCIIC_MCFGR1_PRESCALE_MASK)
/* MCFGR1 Reg Mask */
#define FCIIC_MCFGR1_MASK              0x02070707u
/* MCFGR2 Bit Fields */
#define FCIIC_MCFGR2_FILTSDA_MASK      0xF000000u
#define FCIIC_MCFGR2_FILTSDA_SHIFT     24u
#define FCIIC_MCFGR2_FILTSDA_WIDTH     4u
#define FCIIC_MCFGR2_FILTSDA(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR2_FILTSDA_SHIFT))&FCIIC_MCFGR2_FILTSDA_MASK)
#define FCIIC_MCFGR2_FILTSCL_MASK      0xF0000u
#define FCIIC_MCFGR2_FILTSCL_SHIFT     16u
#define FCIIC_MCFGR2_FILTSCL_WIDTH     4u
#define FCIIC_MCFGR2_FILTSCL(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR2_FILTSCL_SHIFT))&FCIIC_MCFGR2_FILTSCL_MASK)
#define FCIIC_MCFGR2_BUSIDLE_MASK      0xFFFu
#define FCIIC_MCFGR2_BUSIDLE_SHIFT     0u
#define FCIIC_MCFGR2_BUSIDLE_WIDTH     12u
#define FCIIC_MCFGR2_BUSIDLE(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR2_BUSIDLE_SHIFT))&FCIIC_MCFGR2_BUSIDLE_MASK)
/* MCFGR2 Reg Mask */
#define FCIIC_MCFGR2_MASK              0x0F0F0FFFu
/* MCFGR3 Bit Fields */
#define FCIIC_MCFGR3_PINLOW_MASK       0xFFF00u
#define FCIIC_MCFGR3_PINLOW_SHIFT      8u
#define FCIIC_MCFGR3_PINLOW_WIDTH      12u
#define FCIIC_MCFGR3_PINLOW(x)         (((uint32_t)(((uint32_t)(x))<<FCIIC_MCFGR3_PINLOW_SHIFT))&FCIIC_MCFGR3_PINLOW_MASK)
/* MCFGR3 Reg Mask */
#define FCIIC_MCFGR3_MASK              0x000FFF00u
/* MDMR Bit Fields */
#define FCIIC_MDMR_MATCH1_MASK         0xFF0000u
#define FCIIC_MDMR_MATCH1_SHIFT        16u
#define FCIIC_MDMR_MATCH1_WIDTH        8u
#define FCIIC_MDMR_MATCH1(x)           (((uint32_t)(((uint32_t)(x))<<FCIIC_MDMR_MATCH1_SHIFT))&FCIIC_MDMR_MATCH1_MASK)
#define FCIIC_MDMR_MATCH0_MASK         0xFFu
#define FCIIC_MDMR_MATCH0_SHIFT        0u
#define FCIIC_MDMR_MATCH0_WIDTH        8u
#define FCIIC_MDMR_MATCH0(x)           (((uint32_t)(((uint32_t)(x))<<FCIIC_MDMR_MATCH0_SHIFT))&FCIIC_MDMR_MATCH0_MASK)
/* MDMR Reg Mask */
#define FCIIC_MDMR_MASK                0x00FF00FFu
/* MCCR Bit Fields */
#define FCIIC_MCCR_DATAVD_MASK         0x3F000000u
#define FCIIC_MCCR_DATAVD_SHIFT        24u
#define FCIIC_MCCR_DATAVD_WIDTH        6u
#define FCIIC_MCCR_DATAVD(x)           (((uint32_t)(((uint32_t)(x))<<FCIIC_MCCR_DATAVD_SHIFT))&FCIIC_MCCR_DATAVD_MASK)
#define FCIIC_MCCR_SETHOLD_MASK        0x3F0000u
#define FCIIC_MCCR_SETHOLD_SHIFT       16u
#define FCIIC_MCCR_SETHOLD_WIDTH       6u
#define FCIIC_MCCR_SETHOLD(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_MCCR_SETHOLD_SHIFT))&FCIIC_MCCR_SETHOLD_MASK)
#define FCIIC_MCCR_CLKHI_MASK          0x3F00u
#define FCIIC_MCCR_CLKHI_SHIFT         8u
#define FCIIC_MCCR_CLKHI_WIDTH         6u
#define FCIIC_MCCR_CLKHI(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_MCCR_CLKHI_SHIFT))&FCIIC_MCCR_CLKHI_MASK)
#define FCIIC_MCCR_CLKLO_MASK          0x3Fu
#define FCIIC_MCCR_CLKLO_SHIFT         0u
#define FCIIC_MCCR_CLKLO_WIDTH         6u
#define FCIIC_MCCR_CLKLO(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_MCCR_CLKLO_SHIFT))&FCIIC_MCCR_CLKLO_MASK)
/* MCCR Reg Mask */
#define FCIIC_MCCR_MASK                0x3F3F3F3Fu
/* MFCR Bit Fields */
#define FCIIC_MFCR_RXWATER_MASK        0xF0000u
#define FCIIC_MFCR_RXWATER_SHIFT       16u
#define FCIIC_MFCR_RXWATER_WIDTH       4u
#define FCIIC_MFCR_RXWATER(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_MFCR_RXWATER_SHIFT))&FCIIC_MFCR_RXWATER_MASK)
#define FCIIC_MFCR_TXWATER_MASK        0xFu
#define FCIIC_MFCR_TXWATER_SHIFT       0u
#define FCIIC_MFCR_TXWATER_WIDTH       4u
#define FCIIC_MFCR_TXWATER(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_MFCR_TXWATER_SHIFT))&FCIIC_MFCR_TXWATER_MASK)
/* MFCR Reg Mask */
#define FCIIC_MFCR_MASK                0x000F000Fu
/* MFSR Bit Fields */
#define FCIIC_MFSR_RXCOUNT_MASK        0xF0000u
#define FCIIC_MFSR_RXCOUNT_SHIFT       16u
#define FCIIC_MFSR_RXCOUNT_WIDTH       4u
#define FCIIC_MFSR_RXCOUNT(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_MFSR_RXCOUNT_SHIFT))&FCIIC_MFSR_RXCOUNT_MASK)
#define FCIIC_MFSR_TXCOUNT_MASK        0xFu
#define FCIIC_MFSR_TXCOUNT_SHIFT       0u
#define FCIIC_MFSR_TXCOUNT_WIDTH       4u
#define FCIIC_MFSR_TXCOUNT(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_MFSR_TXCOUNT_SHIFT))&FCIIC_MFSR_TXCOUNT_MASK)
/* MFSR Reg Mask */
#define FCIIC_MFSR_MASK                0x000F000Fu
/* MTDR Bit Fields */
#define FCIIC_MTDR_CMD_MASK            0x700u
#define FCIIC_MTDR_CMD_SHIFT           8u
#define FCIIC_MTDR_CMD_WIDTH           3u
#define FCIIC_MTDR_CMD(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_MTDR_CMD_SHIFT))&FCIIC_MTDR_CMD_MASK)
#define FCIIC_MTDR_DATA_MASK           0xFFu
#define FCIIC_MTDR_DATA_SHIFT          0u
#define FCIIC_MTDR_DATA_WIDTH          8u
#define FCIIC_MTDR_DATA(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MTDR_DATA_SHIFT))&FCIIC_MTDR_DATA_MASK)
/* MTDR Reg Mask */
#define FCIIC_MTDR_MASK                0x000007FFu
/* MRDR Bit Fields */
#define FCIIC_MRDR_RXEMPTY_MASK        0x4000u
#define FCIIC_MRDR_RXEMPTY_SHIFT       14u
#define FCIIC_MRDR_RXEMPTY_WIDTH       1u
#define FCIIC_MRDR_RXEMPTY(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_MRDR_RXEMPTY_SHIFT))&FCIIC_MRDR_RXEMPTY_MASK)
#define FCIIC_MRDR_DATA_MASK           0xFFu
#define FCIIC_MRDR_DATA_SHIFT          0u
#define FCIIC_MRDR_DATA_WIDTH          8u
#define FCIIC_MRDR_DATA(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_MRDR_DATA_SHIFT))&FCIIC_MRDR_DATA_MASK)
/* MRDR Reg Mask */
#define FCIIC_MRDR_MASK                0x000040FFu
/* SCR Bit Fields */
#define FCIIC_SCR_FILTEN_MASK          0x10u
#define FCIIC_SCR_FILTEN_SHIFT         4u
#define FCIIC_SCR_FILTEN_WIDTH         1u
#define FCIIC_SCR_FILTEN(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SCR_FILTEN_SHIFT))&FCIIC_SCR_FILTEN_MASK)
#define FCIIC_SCR_RST_MASK             0x2u
#define FCIIC_SCR_RST_SHIFT            1u
#define FCIIC_SCR_RST_WIDTH            1u
#define FCIIC_SCR_RST(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SCR_RST_SHIFT))&FCIIC_SCR_RST_MASK)
#define FCIIC_SCR_SEN_MASK             0x1u
#define FCIIC_SCR_SEN_SHIFT            0u
#define FCIIC_SCR_SEN_WIDTH            1u
#define FCIIC_SCR_SEN(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SCR_SEN_SHIFT))&FCIIC_SCR_SEN_MASK)
/* SCR Reg Mask */
#define FCIIC_SCR_MASK                 0x00000013u
/* SSR Bit Fields */
#define FCIIC_SSR_BBF_MASK             0x2000000u
#define FCIIC_SSR_BBF_SHIFT            25u
#define FCIIC_SSR_BBF_WIDTH            1u
#define FCIIC_SSR_BBF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_BBF_SHIFT))&FCIIC_SSR_BBF_MASK)
#define FCIIC_SSR_SBF_MASK             0x1000000u
#define FCIIC_SSR_SBF_SHIFT            24u
#define FCIIC_SSR_SBF_WIDTH            1u
#define FCIIC_SSR_SBF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_SBF_SHIFT))&FCIIC_SSR_SBF_MASK)
#define FCIIC_SSR_SARF_MASK            0x8000u
#define FCIIC_SSR_SARF_SHIFT           15u
#define FCIIC_SSR_SARF_WIDTH           1u
#define FCIIC_SSR_SARF(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_SARF_SHIFT))&FCIIC_SSR_SARF_MASK)
#define FCIIC_SSR_GCF_MASK             0x4000u
#define FCIIC_SSR_GCF_SHIFT            14u
#define FCIIC_SSR_GCF_WIDTH            1u
#define FCIIC_SSR_GCF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_GCF_SHIFT))&FCIIC_SSR_GCF_MASK)
#define FCIIC_SSR_AM1F_MASK            0x2000u
#define FCIIC_SSR_AM1F_SHIFT           13u
#define FCIIC_SSR_AM1F_WIDTH           1u
#define FCIIC_SSR_AM1F(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_AM1F_SHIFT))&FCIIC_SSR_AM1F_MASK)
#define FCIIC_SSR_AM0F_MASK            0x1000u
#define FCIIC_SSR_AM0F_SHIFT           12u
#define FCIIC_SSR_AM0F_WIDTH           1u
#define FCIIC_SSR_AM0F(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_AM0F_SHIFT))&FCIIC_SSR_AM0F_MASK)
#define FCIIC_SSR_TREF_MASK            0x800u
#define FCIIC_SSR_TREF_SHIFT           11u
#define FCIIC_SSR_TREF_WIDTH           1u
#define FCIIC_SSR_TREF(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_TREF_SHIFT))&FCIIC_SSR_TREF_MASK)
#define FCIIC_SSR_BEF_MASK             0x400u
#define FCIIC_SSR_BEF_SHIFT            10u
#define FCIIC_SSR_BEF_WIDTH            1u
#define FCIIC_SSR_BEF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_BEF_SHIFT))&FCIIC_SSR_BEF_MASK)
#define FCIIC_SSR_SDF_MASK             0x200u
#define FCIIC_SSR_SDF_SHIFT            9u
#define FCIIC_SSR_SDF_WIDTH            1u
#define FCIIC_SSR_SDF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_SDF_SHIFT))&FCIIC_SSR_SDF_MASK)
#define FCIIC_SSR_RSF_MASK             0x100u
#define FCIIC_SSR_RSF_SHIFT            8u
#define FCIIC_SSR_RSF_WIDTH            1u
#define FCIIC_SSR_RSF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_RSF_SHIFT))&FCIIC_SSR_RSF_MASK)
#define FCIIC_SSR_TAF_MASK             0x8u
#define FCIIC_SSR_TAF_SHIFT            3u
#define FCIIC_SSR_TAF_WIDTH            1u
#define FCIIC_SSR_TAF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_TAF_SHIFT))&FCIIC_SSR_TAF_MASK)
#define FCIIC_SSR_AVF_MASK             0x4u
#define FCIIC_SSR_AVF_SHIFT            2u
#define FCIIC_SSR_AVF_WIDTH            1u
#define FCIIC_SSR_AVF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_AVF_SHIFT))&FCIIC_SSR_AVF_MASK)
#define FCIIC_SSR_RDF_MASK             0x2u
#define FCIIC_SSR_RDF_SHIFT            1u
#define FCIIC_SSR_RDF_WIDTH            1u
#define FCIIC_SSR_RDF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_RDF_SHIFT))&FCIIC_SSR_RDF_MASK)
#define FCIIC_SSR_TDF_MASK             0x1u
#define FCIIC_SSR_TDF_SHIFT            0u
#define FCIIC_SSR_TDF_WIDTH            1u
#define FCIIC_SSR_TDF(x)               (((uint32_t)(((uint32_t)(x))<<FCIIC_SSR_TDF_SHIFT))&FCIIC_SSR_TDF_MASK)
/* SSR Reg Mask */
#define FCIIC_SSR_MASK                 0x0300FF0Fu
/* SIER Bit Fields */
#define FCIIC_SIER_SARIE_MASK          0x8000u
#define FCIIC_SIER_SARIE_SHIFT         15u
#define FCIIC_SIER_SARIE_WIDTH         1u
#define FCIIC_SIER_SARIE(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_SARIE_SHIFT))&FCIIC_SIER_SARIE_MASK)
#define FCIIC_SIER_GCIE_MASK           0x4000u
#define FCIIC_SIER_GCIE_SHIFT          14u
#define FCIIC_SIER_GCIE_WIDTH          1u
#define FCIIC_SIER_GCIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_GCIE_SHIFT))&FCIIC_SIER_GCIE_MASK)
#define FCIIC_SIER_AM1IE_MASK          0x2000u
#define FCIIC_SIER_AM1IE_SHIFT         13u
#define FCIIC_SIER_AM1IE_WIDTH         1u
#define FCIIC_SIER_AM1IE(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_AM1IE_SHIFT))&FCIIC_SIER_AM1IE_MASK)
#define FCIIC_SIER_AM0IE_MASK          0x1000u
#define FCIIC_SIER_AM0IE_SHIFT         12u
#define FCIIC_SIER_AM0IE_WIDTH         1u
#define FCIIC_SIER_AM0IE(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_AM0IE_SHIFT))&FCIIC_SIER_AM0IE_MASK)
#define FCIIC_SIER_TREIE_MASK          0x800u
#define FCIIC_SIER_TREIE_SHIFT         11u
#define FCIIC_SIER_TREIE_WIDTH         1u
#define FCIIC_SIER_TREIE(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_TREIE_SHIFT))&FCIIC_SIER_TREIE_MASK)
#define FCIIC_SIER_BEIE_MASK           0x400u
#define FCIIC_SIER_BEIE_SHIFT          10u
#define FCIIC_SIER_BEIE_WIDTH          1u
#define FCIIC_SIER_BEIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_BEIE_SHIFT))&FCIIC_SIER_BEIE_MASK)
#define FCIIC_SIER_SDIE_MASK           0x200u
#define FCIIC_SIER_SDIE_SHIFT          9u
#define FCIIC_SIER_SDIE_WIDTH          1u
#define FCIIC_SIER_SDIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_SDIE_SHIFT))&FCIIC_SIER_SDIE_MASK)
#define FCIIC_SIER_RSIE_MASK           0x100u
#define FCIIC_SIER_RSIE_SHIFT          8u
#define FCIIC_SIER_RSIE_WIDTH          1u
#define FCIIC_SIER_RSIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_RSIE_SHIFT))&FCIIC_SIER_RSIE_MASK)
#define FCIIC_SIER_TAIE_MASK           0x8u
#define FCIIC_SIER_TAIE_SHIFT          3u
#define FCIIC_SIER_TAIE_WIDTH          1u
#define FCIIC_SIER_TAIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_TAIE_SHIFT))&FCIIC_SIER_TAIE_MASK)
#define FCIIC_SIER_AVIE_MASK           0x4u
#define FCIIC_SIER_AVIE_SHIFT          2u
#define FCIIC_SIER_AVIE_WIDTH          1u
#define FCIIC_SIER_AVIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_AVIE_SHIFT))&FCIIC_SIER_AVIE_MASK)
#define FCIIC_SIER_RDIE_MASK           0x2u
#define FCIIC_SIER_RDIE_SHIFT          1u
#define FCIIC_SIER_RDIE_WIDTH          1u
#define FCIIC_SIER_RDIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_RDIE_SHIFT))&FCIIC_SIER_RDIE_MASK)
#define FCIIC_SIER_TDIE_MASK           0x1u
#define FCIIC_SIER_TDIE_SHIFT          0u
#define FCIIC_SIER_TDIE_WIDTH          1u
#define FCIIC_SIER_TDIE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SIER_TDIE_SHIFT))&FCIIC_SIER_TDIE_MASK)
/* SIER Reg Mask */
#define FCIIC_SIER_MASK                0x0000FF0Fu
/* SDER Bit Fields */
#define FCIIC_SDER_AVDE_MASK           0x4u
#define FCIIC_SDER_AVDE_SHIFT          2u
#define FCIIC_SDER_AVDE_WIDTH          1u
#define FCIIC_SDER_AVDE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SDER_AVDE_SHIFT))&FCIIC_SDER_AVDE_MASK)
#define FCIIC_SDER_RDDE_MASK           0x2u
#define FCIIC_SDER_RDDE_SHIFT          1u
#define FCIIC_SDER_RDDE_WIDTH          1u
#define FCIIC_SDER_RDDE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SDER_RDDE_SHIFT))&FCIIC_SDER_RDDE_MASK)
#define FCIIC_SDER_TDDE_MASK           0x1u
#define FCIIC_SDER_TDDE_SHIFT          0u
#define FCIIC_SDER_TDDE_WIDTH          1u
#define FCIIC_SDER_TDDE(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SDER_TDDE_SHIFT))&FCIIC_SDER_TDDE_MASK)
/* SDER Reg Mask */
#define FCIIC_SDER_MASK                0x00000007u
/* SCFGR1 Bit Fields */
#define FCIIC_SCFGR1_ADDRCFG_MASK      0x70000u
#define FCIIC_SCFGR1_ADDRCFG_SHIFT     16u
#define FCIIC_SCFGR1_ADDRCFG_WIDTH     3u
#define FCIIC_SCFGR1_ADDRCFG(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_ADDRCFG_SHIFT))&FCIIC_SCFGR1_ADDRCFG_MASK)
#define FCIIC_SCFGR1_HSMEN_MASK        0x2000u
#define FCIIC_SCFGR1_HSMEN_SHIFT       13u
#define FCIIC_SCFGR1_HSMEN_WIDTH       1u
#define FCIIC_SCFGR1_HSMEN(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_HSMEN_SHIFT))&FCIIC_SCFGR1_HSMEN_MASK)
#define FCIIC_SCFGR1_IGNACK_MASK       0x1000u
#define FCIIC_SCFGR1_IGNACK_SHIFT      12u
#define FCIIC_SCFGR1_IGNACK_WIDTH      1u
#define FCIIC_SCFGR1_IGNACK(x)         (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_IGNACK_SHIFT))&FCIIC_SCFGR1_IGNACK_MASK)
#define FCIIC_SCFGR1_RXCFG_MASK        0x800u
#define FCIIC_SCFGR1_RXCFG_SHIFT       11u
#define FCIIC_SCFGR1_RXCFG_WIDTH       1u
#define FCIIC_SCFGR1_RXCFG(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_RXCFG_SHIFT))&FCIIC_SCFGR1_RXCFG_MASK)
#define FCIIC_SCFGR1_TXCFG_MASK        0x400u
#define FCIIC_SCFGR1_TXCFG_SHIFT       10u
#define FCIIC_SCFGR1_TXCFG_WIDTH       1u
#define FCIIC_SCFGR1_TXCFG(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_TXCFG_SHIFT))&FCIIC_SCFGR1_TXCFG_MASK)
#define FCIIC_SCFGR1_SAEN_MASK         0x200u
#define FCIIC_SCFGR1_SAEN_SHIFT        9u
#define FCIIC_SCFGR1_SAEN_WIDTH        1u
#define FCIIC_SCFGR1_SAEN(x)           (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_SAEN_SHIFT))&FCIIC_SCFGR1_SAEN_MASK)
#define FCIIC_SCFGR1_GCEN_MASK         0x100u
#define FCIIC_SCFGR1_GCEN_SHIFT        8u
#define FCIIC_SCFGR1_GCEN_WIDTH        1u
#define FCIIC_SCFGR1_GCEN(x)           (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_GCEN_SHIFT))&FCIIC_SCFGR1_GCEN_MASK)
#define FCIIC_SCFGR1_ACKSTALL_MASK     0x8u
#define FCIIC_SCFGR1_ACKSTALL_SHIFT    3u
#define FCIIC_SCFGR1_ACKSTALL_WIDTH    1u
#define FCIIC_SCFGR1_ACKSTALL(x)       (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_ACKSTALL_SHIFT))&FCIIC_SCFGR1_ACKSTALL_MASK)
#define FCIIC_SCFGR1_TXDSTALL_MASK     0x4u
#define FCIIC_SCFGR1_TXDSTALL_SHIFT    2u
#define FCIIC_SCFGR1_TXDSTALL_WIDTH    1u
#define FCIIC_SCFGR1_TXDSTALL(x)       (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_TXDSTALL_SHIFT))&FCIIC_SCFGR1_TXDSTALL_MASK)
#define FCIIC_SCFGR1_RXSTALL_MASK      0x2u
#define FCIIC_SCFGR1_RXSTALL_SHIFT     1u
#define FCIIC_SCFGR1_RXSTALL_WIDTH     1u
#define FCIIC_SCFGR1_RXSTALL(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_RXSTALL_SHIFT))&FCIIC_SCFGR1_RXSTALL_MASK)
#define FCIIC_SCFGR1_ADRSTALL_MASK     0x1u
#define FCIIC_SCFGR1_ADRSTALL_SHIFT    0u
#define FCIIC_SCFGR1_ADRSTALL_WIDTH    1u
#define FCIIC_SCFGR1_ADRSTALL(x)       (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR1_ADRSTALL_SHIFT))&FCIIC_SCFGR1_ADRSTALL_MASK)
/* SCFGR1 Reg Mask */
#define FCIIC_SCFGR1_MASK              0x00073F0Fu
/* SCFGR2 Bit Fields */
#define FCIIC_SCFGR2_FILTSDA_MASK      0xF000000u
#define FCIIC_SCFGR2_FILTSDA_SHIFT     24u
#define FCIIC_SCFGR2_FILTSDA_WIDTH     4u
#define FCIIC_SCFGR2_FILTSDA(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR2_FILTSDA_SHIFT))&FCIIC_SCFGR2_FILTSDA_MASK)
#define FCIIC_SCFGR2_FILTSCL_MASK      0xF0000u
#define FCIIC_SCFGR2_FILTSCL_SHIFT     16u
#define FCIIC_SCFGR2_FILTSCL_WIDTH     4u
#define FCIIC_SCFGR2_FILTSCL(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR2_FILTSCL_SHIFT))&FCIIC_SCFGR2_FILTSCL_MASK)
#define FCIIC_SCFGR2_DATAVD_MASK       0x3F00u
#define FCIIC_SCFGR2_DATAVD_SHIFT      8u
#define FCIIC_SCFGR2_DATAVD_WIDTH      6u
#define FCIIC_SCFGR2_DATAVD(x)         (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR2_DATAVD_SHIFT))&FCIIC_SCFGR2_DATAVD_MASK)
#define FCIIC_SCFGR2_CLKHOLD_MASK      0xFu
#define FCIIC_SCFGR2_CLKHOLD_SHIFT     0u
#define FCIIC_SCFGR2_CLKHOLD_WIDTH     4u
#define FCIIC_SCFGR2_CLKHOLD(x)        (((uint32_t)(((uint32_t)(x))<<FCIIC_SCFGR2_CLKHOLD_SHIFT))&FCIIC_SCFGR2_CLKHOLD_MASK)
/* SCFGR2 Reg Mask */
#define FCIIC_SCFGR2_MASK              0x0F0F3F0Fu
/* SAMR Bit Fields */
#define FCIIC_SAMR_ADDR1_MASK          0x7FE0000u
#define FCIIC_SAMR_ADDR1_SHIFT         17u
#define FCIIC_SAMR_ADDR1_WIDTH         10u
#define FCIIC_SAMR_ADDR1(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SAMR_ADDR1_SHIFT))&FCIIC_SAMR_ADDR1_MASK)
#define FCIIC_SAMR_ADDR0_MASK          0x7FEu
#define FCIIC_SAMR_ADDR0_SHIFT         1u
#define FCIIC_SAMR_ADDR0_WIDTH         10u
#define FCIIC_SAMR_ADDR0(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SAMR_ADDR0_SHIFT))&FCIIC_SAMR_ADDR0_MASK)
/* SAMR Reg Mask */
#define FCIIC_SAMR_MASK                0x07FE07FEu
/* SASR Bit Fields */
#define FCIIC_SASR_ANV_MASK            0x4000u
#define FCIIC_SASR_ANV_SHIFT           14u
#define FCIIC_SASR_ANV_WIDTH           1u
#define FCIIC_SASR_ANV(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_SASR_ANV_SHIFT))&FCIIC_SASR_ANV_MASK)
#define FCIIC_SASR_RADDR_MASK          0x7FFu
#define FCIIC_SASR_RADDR_SHIFT         0u
#define FCIIC_SASR_RADDR_WIDTH         11u
#define FCIIC_SASR_RADDR(x)            (((uint32_t)(((uint32_t)(x))<<FCIIC_SASR_RADDR_SHIFT))&FCIIC_SASR_RADDR_MASK)
/* SASR Reg Mask */
#define FCIIC_SASR_MASK                0x000047FFu
/* STAR Bit Fields */
#define FCIIC_STAR_TXNACK_MASK         0x1u
#define FCIIC_STAR_TXNACK_SHIFT        0u
#define FCIIC_STAR_TXNACK_WIDTH        1u
#define FCIIC_STAR_TXNACK(x)           (((uint32_t)(((uint32_t)(x))<<FCIIC_STAR_TXNACK_SHIFT))&FCIIC_STAR_TXNACK_MASK)
/* STAR Reg Mask */
#define FCIIC_STAR_MASK                0x00000001u
/* STDR Bit Fields */
#define FCIIC_STDR_DATA_MASK           0xFFu
#define FCIIC_STDR_DATA_SHIFT          0u
#define FCIIC_STDR_DATA_WIDTH          8u
#define FCIIC_STDR_DATA(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_STDR_DATA_SHIFT))&FCIIC_STDR_DATA_MASK)
/* STDR Reg Mask */
#define FCIIC_STDR_MASK                0x000000FFu
/* SRDR Bit Fields */
#define FCIIC_SRDR_SOF_MASK            0x8000u
#define FCIIC_SRDR_SOF_SHIFT           15u
#define FCIIC_SRDR_SOF_WIDTH           1u
#define FCIIC_SRDR_SOF(x)              (((uint32_t)(((uint32_t)(x))<<FCIIC_SRDR_SOF_SHIFT))&FCIIC_SRDR_SOF_MASK)
#define FCIIC_SRDR_RXEMPTY_MASK        0x4000u
#define FCIIC_SRDR_RXEMPTY_SHIFT       14u
#define FCIIC_SRDR_RXEMPTY_WIDTH       1u
#define FCIIC_SRDR_RXEMPTY(x)          (((uint32_t)(((uint32_t)(x))<<FCIIC_SRDR_RXEMPTY_SHIFT))&FCIIC_SRDR_RXEMPTY_MASK)
#define FCIIC_SRDR_DATA_MASK           0xFFu
#define FCIIC_SRDR_DATA_SHIFT          0u
#define FCIIC_SRDR_DATA_WIDTH          8u
#define FCIIC_SRDR_DATA(x)             (((uint32_t)(((uint32_t)(x))<<FCIIC_SRDR_DATA_SHIFT))&FCIIC_SRDR_DATA_MASK)
/* SRDR Reg Mask */
#define FCIIC_SRDR_MASK                0x0000C0FFu
/**
 * @}
 */ /* end of group FCIIC_Register_Masks */
/**
 * @}
 */ /* end of group FCIIC_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
