#ifndef _MODULE_FLEXCAN_KJO_Ufdi7_REGS_H_
#define _MODULE_FLEXCAN_KJO_Ufdi7_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- FLEXCAN Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FLEXCAN_Peripheral_Access_Layer FLEXCAN Peripheral Access Layer
 * @{
 */
/** FLEXCAN - Size of Registers Arrays */
/** FLEXCAN - Register Layout Typedef */
#define FLEXCAN_RAM_COUNT          128
#define FLEXCAN_RXIMR_COUNT        32
#define FLEXCAN_ERX_FIFO_COUNT     240
#define FLEXCAN_ERFFEL_COUNT       32
#define FLEXCAN_WAKEUP_DATA_DEPTH  4U

typedef struct {
  __IO uint32_t MCR                           ; /* Module Configuration register, offset: 0x0 */
  __IO uint32_t CTRL1                         ; /* Control 1 register, offset: 0x4 */
  __IO uint32_t TIMER                         ; /* Free Running Timer, offset: 0x8 */
       uint8_t  RESERVED_0[4];
  __IO uint32_t RXMGMASK                      ; /* Rx Mailboxes Global Mask register, offset: 0x10 */
  __IO uint32_t RX14MASK                      ; /* Rx 14 Mask register, offset: 0x14 */
  __IO uint32_t RX15MASK                      ; /* Rx 15 Mask register, offset: 0x18 */
  __I  uint32_t ECR                           ; /* Error Counter, offset: 0x1C */
  __IO uint32_t ESR1                          ; /* Error and Status 1 register, offset: 0x20 */
       uint8_t  RESERVED_1[4];
  __IO uint32_t IMASK1                        ; /* Interrupt Masks 1 register, offset: 0x28 */
       uint8_t  RESERVED_2[4];
  __IO uint32_t IFLAG1                        ; /* Interrupt Flags 1 register, offset: 0x30 */
  __IO uint32_t CTRL2                         ; /* Control 2 register, offset: 0x34 */
  __I  uint32_t ESR2                          ; /* Error and Status 2 register, offset: 0x38 */
       uint8_t  RESERVED_3[8];
  __I  uint32_t CRCR                          ; /* CRC register, offset: 0x44 */
  __IO uint32_t RXFGMASK                      ; /* Legacy Rx FIFO Global Mask register, offset: 0x48 */
  __I  uint32_t RXFIR                         ; /* Legacy Rx FIFO Information register, offset: 0x4C */
  __IO uint32_t CBT                           ; /* CAN Bit Timing register, offset: 0x50 */
       uint8_t  RESERVED_4[44];
  __IO uint32_t RAM[FLEXCAN_RAM_COUNT]        ; /* Embedded RAM, offset: 0x80 */
       uint8_t  RESERVED_5[1536];
  __IO uint32_t RXIMR[FLEXCAN_RXIMR_COUNT]    ; /* Rx Individual Mask registers, offset: 0x880 */
       uint8_t  RESERVED_6[480];
  __IO uint32_t MECR                          ; /* Memory Error Control register, offset: 0xAE0 */
  __IO uint32_t ERRIAR                        ; /* Error Injection Address register, offset: 0xAE4 */
  __IO uint32_t ERRIDPR                       ; /* Error Injection Data Pattern register, offset: 0xAE8 */
  __IO uint32_t ERRIPPR                       ; /* Error Injection Parity Pattern register, offset: 0xAEC */
  __I  uint32_t RERRAR                        ; /* Error Report Address register, offset: 0xAF0 */
  __I  uint32_t RERRDR                        ; /* Error Report Data register, offset: 0xAF4 */
  __I  uint32_t RERRSYNR                      ; /* Error Report Syndrome register, offset: 0xAF8 */
  __IO uint32_t ERRSR                         ; /* Error Status register, offset: 0xAFC */
  __IO uint32_t CTRL1_PN                      ; /* Pretended Networking Control 1 register, offset: 0xB00 */
  __IO uint32_t CTRL2_PN                      ; /* Pretended Networking Control 2 register, offset: 0xB04 */
  __IO uint32_t WU_MTC                        ; /* Pretended Networking Wake Up Match register, offset: 0xB08 */
  __IO uint32_t FLT_ID1                       ; /* Pretended Networking ID Filter 1 register, offset: 0xB0C */
  __IO uint32_t FLT_DLC                       ; /* Pretended Networking DLC Filter register, offset: 0xB10 */
  __IO uint32_t PL1_LO                        ; /* Pretended Networking Payload Low Filter 1 register, offset: 0xB14 */
  __IO uint32_t PL1_HI                        ; /* Pretended Networking Payload High Filter 1 register, offset: 0xB18 */
  __IO uint32_t FLT_ID2_IDMASK                ; /* Pretended Networking ID Filter 2 Register / ID Mask register, offset: 0xB1C */
  __IO uint32_t PL2_PLMASK_LO                 ; /* Pretended Networking Payload Low Filter 2 Register / Payload Low Mask register, offset: 0xB20 */
  __IO uint32_t PL2_PLMASK_HI                 ; /* Pretended Networking Payload High Filter 2 low order bits / Payload High Mask register, offset: 0xB24 */
       uint8_t  RESERVED_7[24];
#if 0
  __I  uint32_t WMB_CS0                       ; /* Wake Up Message Buffer register for C/S, offset: 0xb40 */
  __I  uint32_t WMB_ID0                       ; /* Wake Up Message Buffer Register for ID, offset: 0xb44 */
  __I  uint32_t WMB_D03_0                     ; /* Wake Up Message Buffer Register for Data 0-3, offset: 0xb48 */
  __I  uint32_t WMB_D47_0                     ; /* Wake Up Message Buffer Register Data 4-7, offset: 0xb4c */
  __I  uint32_t WMB_CS1                       ; /* Wake Up Message Buffer register for C/S, offset: 0xb50 */
  __I  uint32_t WMB_ID1                       ; /* Wake Up Message Buffer Register for ID, offset: 0xb54 */
  __I  uint32_t WMB_D03_1                     ; /* Wake Up Message Buffer Register for Data 0-3, offset: 0xb58 */
  __I  uint32_t WMB_D47_1                     ; /* Wake Up Message Buffer Register Data 4-7, offset: 0xb5c */
  __I  uint32_t WMB_CS2                       ; /* Wake Up Message Buffer register for C/S, offset: 0xb60 */
  __I  uint32_t WMB_ID2                       ; /* Wake Up Message Buffer Register for ID, offset: 0xb64 */
  __I  uint32_t WMB_D03_2                     ; /* Wake Up Message Buffer Register for Data 0-3, offset: 0xb68 */
  __I  uint32_t WMB_D47_2                     ; /* Wake Up Message Buffer Register Data 4-7, offset: 0xb6c */
  __I  uint32_t WMB_CS3                       ; /* Wake Up Message Buffer register for C/S, offset: 0xb70 */
  __I  uint32_t WMB_ID3                       ; /* Wake Up Message Buffer Register for ID, offset: 0xb74 */
  __I  uint32_t WMB_D03_3                     ; /* Wake Up Message Buffer Register for Data 0-3, offset: 0xb78 */
  __I  uint32_t WMB_D47_3                     ; /* Wake Up Message Buffer Register Data 4-7, offset: 0xb7c */
#else
  __I  uint32_t WMB_RAM[16]                   ; /* Wake Up Message Buffer Register for all message, layout same to message buffer */
#endif
       uint8_t  RESERVED_8[112];
  __IO uint32_t EPRS                          ; /* Enhanced CAN Bit Timing Prescalers, offset: 0xBF0 */
  __IO uint32_t ENCBT                         ; /* Enhanced Nominal CAN Bit Timing, offset: 0xBF4 */
  __IO uint32_t EDCBT                         ; /* Enhanced Data Phase CAN bit Timing, offset: 0xBF8 */
  __IO uint32_t ETDC                          ; /* Enhanced Transceiver Delay Compensation, offset: 0xBFC */
  __IO uint32_t FDCTRL                        ; /* CAN FD Control register, offset: 0xC00 */
  __IO uint32_t FDCBT                         ; /* CAN FD Bit Timing register, offset: 0xC04 */
  __I  uint32_t FDCRC                         ; /* CAN FD CRC register, offset: 0xC08 */
  __IO uint32_t ERFCR                         ; /* Enhanced Rx FIFO Control register, offset: 0xC0C */
  __IO uint32_t ERFIER                        ; /* Enhanced Rx FIFO Interrupt Enable register, offset: 0xC10 */
  __IO uint32_t ERFSR                         ; /* Enhanced Rx FIFO Status register, offset: 0xC14 */
#if FLEXCAN_GATE_SUPPORT == STD_ON
       uint8_t  RESERVED_9[3560];
  __IO uint32_t GATE_CS                       ; /* GATE_CS, offset: 0x1A00 */
       uint8_t  RESERVED_10[12];
  __IO uint32_t GATE_BUFFER[FLEXCAN_GATE_BUFFER_COUNT]; /* GATE_BUFFER[FLEXCAN_GATE_BUFFER_COUNT], offset: 0x1a10 */
       uint8_t  RESERVED_11[1504];
#else
       uint8_t  RESERVED_9[5096];
#endif
  __IO uint32_t ERX_FIFO[FLEXCAN_ERX_FIFO_COUNT]; /* ERX_FIFO[FLEXCAN_ERX_FIFO_COUNT], offset: 0x2000 */
       uint8_t  RESERVED_12[3136];
  __IO uint32_t ERFFEL[FLEXCAN_ERFFEL_COUNT]  ; /* Enhanced Rx FIFO Filter Element, offset: 0x3000 */
} FLEXCAN_Type, *FLEXCAN_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- FLEXCAN Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup FLEXCAN_Register_Masks FLEXCAN Register Masks
 * @{
 */
 
/* MCR Bit Fields */
#define FLEXCAN_MCR_MDIS_MASK          0x80000000u
#define FLEXCAN_MCR_MDIS_SHIFT         31u
#define FLEXCAN_MCR_MDIS_WIDTH         1u
#define FLEXCAN_MCR_MDIS(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_MDIS_SHIFT))&FLEXCAN_MCR_MDIS_MASK)
#define FLEXCAN_MCR_FRZ_MASK           0x40000000u
#define FLEXCAN_MCR_FRZ_SHIFT          30u
#define FLEXCAN_MCR_FRZ_WIDTH          1u
#define FLEXCAN_MCR_FRZ(x)             (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_FRZ_SHIFT))&FLEXCAN_MCR_FRZ_MASK)
#define FLEXCAN_MCR_RFEN_MASK          0x20000000u
#define FLEXCAN_MCR_RFEN_SHIFT         29u
#define FLEXCAN_MCR_RFEN_WIDTH         1u
#define FLEXCAN_MCR_RFEN(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_RFEN_SHIFT))&FLEXCAN_MCR_RFEN_MASK)
#define FLEXCAN_MCR_HALT_MASK          0x10000000u
#define FLEXCAN_MCR_HALT_SHIFT         28u
#define FLEXCAN_MCR_HALT_WIDTH         1u
#define FLEXCAN_MCR_HALT(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_HALT_SHIFT))&FLEXCAN_MCR_HALT_MASK)
#define FLEXCAN_MCR_NOTRDY_MASK        0x8000000u
#define FLEXCAN_MCR_NOTRDY_SHIFT       27u
#define FLEXCAN_MCR_NOTRDY_WIDTH       1u
#define FLEXCAN_MCR_NOTRDY(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_NOTRDY_SHIFT))&FLEXCAN_MCR_NOTRDY_MASK)
#define FLEXCAN_MCR_SOFTRST_MASK       0x2000000u
#define FLEXCAN_MCR_SOFTRST_SHIFT      25u
#define FLEXCAN_MCR_SOFTRST_WIDTH      1u
#define FLEXCAN_MCR_SOFTRST(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_SOFTRST_SHIFT))&FLEXCAN_MCR_SOFTRST_MASK)
#define FLEXCAN_MCR_FRZACK_MASK        0x1000000u
#define FLEXCAN_MCR_FRZACK_SHIFT       24u
#define FLEXCAN_MCR_FRZACK_WIDTH       1u
#define FLEXCAN_MCR_FRZACK(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_FRZACK_SHIFT))&FLEXCAN_MCR_FRZACK_MASK)
#define FLEXCAN_MCR_SUPV_MASK          0x800000u
#define FLEXCAN_MCR_SUPV_SHIFT         23u
#define FLEXCAN_MCR_SUPV_WIDTH         1u
#define FLEXCAN_MCR_SUPV(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_SUPV_SHIFT))&FLEXCAN_MCR_SUPV_MASK)
#define FLEXCAN_MCR_WRNEN_MASK         0x200000u
#define FLEXCAN_MCR_WRNEN_SHIFT        21u
#define FLEXCAN_MCR_WRNEN_WIDTH        1u
#define FLEXCAN_MCR_WRNEN(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_WRNEN_SHIFT))&FLEXCAN_MCR_WRNEN_MASK)
#define FLEXCAN_MCR_LPMACK_MASK        0x100000u
#define FLEXCAN_MCR_LPMACK_SHIFT       20u
#define FLEXCAN_MCR_LPMACK_WIDTH       1u
#define FLEXCAN_MCR_LPMACK(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_LPMACK_SHIFT))&FLEXCAN_MCR_LPMACK_MASK)
#define FLEXCAN_MCR_SRXDIS_MASK        0x20000u
#define FLEXCAN_MCR_SRXDIS_SHIFT       17u
#define FLEXCAN_MCR_SRXDIS_WIDTH       1u
#define FLEXCAN_MCR_SRXDIS(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_SRXDIS_SHIFT))&FLEXCAN_MCR_SRXDIS_MASK)
#define FLEXCAN_MCR_IRMQ_MASK          0x10000u
#define FLEXCAN_MCR_IRMQ_SHIFT         16u
#define FLEXCAN_MCR_IRMQ_WIDTH         1u
#define FLEXCAN_MCR_IRMQ(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_IRMQ_SHIFT))&FLEXCAN_MCR_IRMQ_MASK)
#define FLEXCAN_MCR_DMA_MASK           0x8000u
#define FLEXCAN_MCR_DMA_SHIFT          15u
#define FLEXCAN_MCR_DMA_WIDTH          1u
#define FLEXCAN_MCR_DMA(x)             (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_DMA_SHIFT))&FLEXCAN_MCR_DMA_MASK)
#define FLEXCAN_MCR_PNET_EN_MASK       0x4000u
#define FLEXCAN_MCR_PNET_EN_SHIFT      14u
#define FLEXCAN_MCR_PNET_EN_WIDTH      1u
#define FLEXCAN_MCR_PNET_EN(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_PNET_EN_SHIFT))&FLEXCAN_MCR_PNET_EN_MASK)
#define FLEXCAN_MCR_LPRIOEN_MASK       0x2000u
#define FLEXCAN_MCR_LPRIOEN_SHIFT      13u
#define FLEXCAN_MCR_LPRIOEN_WIDTH      1u
#define FLEXCAN_MCR_LPRIOEN(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_LPRIOEN_SHIFT))&FLEXCAN_MCR_LPRIOEN_MASK)
#define FLEXCAN_MCR_AEN_MASK           0x1000u
#define FLEXCAN_MCR_AEN_SHIFT          12u
#define FLEXCAN_MCR_AEN_WIDTH          1u
#define FLEXCAN_MCR_AEN(x)             (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_AEN_SHIFT))&FLEXCAN_MCR_AEN_MASK)
#define FLEXCAN_MCR_FDEN_MASK          0x800u
#define FLEXCAN_MCR_FDEN_SHIFT         11u
#define FLEXCAN_MCR_FDEN_WIDTH         1u
#define FLEXCAN_MCR_FDEN(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_FDEN_SHIFT))&FLEXCAN_MCR_FDEN_MASK)
#define FLEXCAN_MCR_IDAM_MASK          0x300u
#define FLEXCAN_MCR_IDAM_SHIFT         8u
#define FLEXCAN_MCR_IDAM_WIDTH         2u
#define FLEXCAN_MCR_IDAM(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_IDAM_SHIFT))&FLEXCAN_MCR_IDAM_MASK)
#define FLEXCAN_MCR_MAXMB_MASK         0x7Fu
#define FLEXCAN_MCR_MAXMB_SHIFT        0u
#define FLEXCAN_MCR_MAXMB_WIDTH        7u
#define FLEXCAN_MCR_MAXMB(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MCR_MAXMB_SHIFT))&FLEXCAN_MCR_MAXMB_MASK)
/* MCR Reg Mask */
#define FLEXCAN_MCR_MASK               0xFBB3FB7Fu
/* CTRL1 Bit Fields */
#define FLEXCAN_CTRL1_PRESDIV_MASK     0xFF000000u
#define FLEXCAN_CTRL1_PRESDIV_SHIFT    24u
#define FLEXCAN_CTRL1_PRESDIV_WIDTH    8u
#define FLEXCAN_CTRL1_PRESDIV(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PRESDIV_SHIFT))&FLEXCAN_CTRL1_PRESDIV_MASK)
#define FLEXCAN_CTRL1_RJW_MASK         0xC00000u
#define FLEXCAN_CTRL1_RJW_SHIFT        22u
#define FLEXCAN_CTRL1_RJW_WIDTH        2u
#define FLEXCAN_CTRL1_RJW(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_RJW_SHIFT))&FLEXCAN_CTRL1_RJW_MASK)
#define FLEXCAN_CTRL1_PSEG1_MASK       0x380000u
#define FLEXCAN_CTRL1_PSEG1_SHIFT      19u
#define FLEXCAN_CTRL1_PSEG1_WIDTH      3u
#define FLEXCAN_CTRL1_PSEG1(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PSEG1_SHIFT))&FLEXCAN_CTRL1_PSEG1_MASK)
#define FLEXCAN_CTRL1_PSEG2_MASK       0x70000u
#define FLEXCAN_CTRL1_PSEG2_SHIFT      16u
#define FLEXCAN_CTRL1_PSEG2_WIDTH      3u
#define FLEXCAN_CTRL1_PSEG2(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PSEG2_SHIFT))&FLEXCAN_CTRL1_PSEG2_MASK)
#define FLEXCAN_CTRL1_BOFFMSK_MASK     0x8000u
#define FLEXCAN_CTRL1_BOFFMSK_SHIFT    15u
#define FLEXCAN_CTRL1_BOFFMSK_WIDTH    1u
#define FLEXCAN_CTRL1_BOFFMSK(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_BOFFMSK_SHIFT))&FLEXCAN_CTRL1_BOFFMSK_MASK)
#define FLEXCAN_CTRL1_ERRMSK_MASK      0x4000u
#define FLEXCAN_CTRL1_ERRMSK_SHIFT     14u
#define FLEXCAN_CTRL1_ERRMSK_WIDTH     1u
#define FLEXCAN_CTRL1_ERRMSK(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_ERRMSK_SHIFT))&FLEXCAN_CTRL1_ERRMSK_MASK)
#define FLEXCAN_CTRL1_CLKSRC_MASK      0x2000u
#define FLEXCAN_CTRL1_CLKSRC_SHIFT     13u
#define FLEXCAN_CTRL1_CLKSRC_WIDTH     1u
#define FLEXCAN_CTRL1_CLKSRC(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_CLKSRC_SHIFT))&FLEXCAN_CTRL1_CLKSRC_MASK)
#define FLEXCAN_CTRL1_LPB_MASK         0x1000u
#define FLEXCAN_CTRL1_LPB_SHIFT        12u
#define FLEXCAN_CTRL1_LPB_WIDTH        1u
#define FLEXCAN_CTRL1_LPB(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_LPB_SHIFT))&FLEXCAN_CTRL1_LPB_MASK)
#define FLEXCAN_CTRL1_TWRNMSK_MASK     0x800u
#define FLEXCAN_CTRL1_TWRNMSK_SHIFT    11u
#define FLEXCAN_CTRL1_TWRNMSK_WIDTH    1u
#define FLEXCAN_CTRL1_TWRNMSK(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_TWRNMSK_SHIFT))&FLEXCAN_CTRL1_TWRNMSK_MASK)
#define FLEXCAN_CTRL1_RWRNMSK_MASK     0x400u
#define FLEXCAN_CTRL1_RWRNMSK_SHIFT    10u
#define FLEXCAN_CTRL1_RWRNMSK_WIDTH    1u
#define FLEXCAN_CTRL1_RWRNMSK(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_RWRNMSK_SHIFT))&FLEXCAN_CTRL1_RWRNMSK_MASK)
#define FLEXCAN_CTRL1_SMP_MASK         0x80u
#define FLEXCAN_CTRL1_SMP_SHIFT        7u
#define FLEXCAN_CTRL1_SMP_WIDTH        1u
#define FLEXCAN_CTRL1_SMP(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_SMP_SHIFT))&FLEXCAN_CTRL1_SMP_MASK)
#define FLEXCAN_CTRL1_BOFFREC_MASK     0x40u
#define FLEXCAN_CTRL1_BOFFREC_SHIFT    6u
#define FLEXCAN_CTRL1_BOFFREC_WIDTH    1u
#define FLEXCAN_CTRL1_BOFFREC(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_BOFFREC_SHIFT))&FLEXCAN_CTRL1_BOFFREC_MASK)
#define FLEXCAN_CTRL1_TSYN_MASK        0x20u
#define FLEXCAN_CTRL1_TSYN_SHIFT       5u
#define FLEXCAN_CTRL1_TSYN_WIDTH       1u
#define FLEXCAN_CTRL1_TSYN(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_TSYN_SHIFT))&FLEXCAN_CTRL1_TSYN_MASK)
#define FLEXCAN_CTRL1_LBUF_MASK        0x10u
#define FLEXCAN_CTRL1_LBUF_SHIFT       4u
#define FLEXCAN_CTRL1_LBUF_WIDTH       1u
#define FLEXCAN_CTRL1_LBUF(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_LBUF_SHIFT))&FLEXCAN_CTRL1_LBUF_MASK)
#define FLEXCAN_CTRL1_LOM_MASK         0x8u
#define FLEXCAN_CTRL1_LOM_SHIFT        3u
#define FLEXCAN_CTRL1_LOM_WIDTH        1u
#define FLEXCAN_CTRL1_LOM(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_LOM_SHIFT))&FLEXCAN_CTRL1_LOM_MASK)
#define FLEXCAN_CTRL1_PROPSEG_MASK     0x7u
#define FLEXCAN_CTRL1_PROPSEG_SHIFT    0u
#define FLEXCAN_CTRL1_PROPSEG_WIDTH    3u
#define FLEXCAN_CTRL1_PROPSEG(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PROPSEG_SHIFT))&FLEXCAN_CTRL1_PROPSEG_MASK)
/* CTRL1 Reg Mask */
#define FLEXCAN_CTRL1_MASK             0xFFFFFCFFu
/* TIMER Bit Fields */
#define FLEXCAN_TIMER_TIMER_MASK       0xFFFFu
#define FLEXCAN_TIMER_TIMER_SHIFT      0u
#define FLEXCAN_TIMER_TIMER_WIDTH      16u
#define FLEXCAN_TIMER_TIMER(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_TIMER_TIMER_SHIFT))&FLEXCAN_TIMER_TIMER_MASK)
/* TIMER Reg Mask */
#define FLEXCAN_TIMER_MASK             0x0000FFFFu
/* RXMGMASK Bit Fields */
#define FLEXCAN_RXMGMASK_MG_MASK       0xFFFFFFFFu
#define FLEXCAN_RXMGMASK_MG_SHIFT      0u
#define FLEXCAN_RXMGMASK_MG_WIDTH      32u
#define FLEXCAN_RXMGMASK_MG(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RXMGMASK_MG_SHIFT))&FLEXCAN_RXMGMASK_MG_MASK)
/* RXMGMASK Reg Mask */
#define FLEXCAN_RXMGMASK_MASK          0xFFFFFFFFu
/* RX14MASK Bit Fields */
#define FLEXCAN_RX14MASK_RX14M_MASK    0xFFFFFFFFu
#define FLEXCAN_RX14MASK_RX14M_SHIFT   0u
#define FLEXCAN_RX14MASK_RX14M_WIDTH   32u
#define FLEXCAN_RX14MASK_RX14M(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RX14MASK_RX14M_SHIFT))&FLEXCAN_RX14MASK_RX14M_MASK)
/* RX14MASK Reg Mask */
#define FLEXCAN_RX14MASK_MASK          0xFFFFFFFFu
/* RX15MASK Bit Fields */
#define FLEXCAN_RX15MASK_RX15M_MASK    0xFFFFFFFFu
#define FLEXCAN_RX15MASK_RX15M_SHIFT   0u
#define FLEXCAN_RX15MASK_RX15M_WIDTH   32u
#define FLEXCAN_RX15MASK_RX15M(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RX15MASK_RX15M_SHIFT))&FLEXCAN_RX15MASK_RX15M_MASK)
/* RX15MASK Reg Mask */
#define FLEXCAN_RX15MASK_MASK          0xFFFFFFFFu
/* ECR Bit Fields */
#define FLEXCAN_ECR_RXERRCNT_FAST_MASK 0xFF000000u
#define FLEXCAN_ECR_RXERRCNT_FAST_SHIFT 24u
#define FLEXCAN_ECR_RXERRCNT_FAST_WIDTH 8u
#define FLEXCAN_ECR_RXERRCNT_FAST(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ECR_RXERRCNT_FAST_SHIFT))&FLEXCAN_ECR_RXERRCNT_FAST_MASK)
#define FLEXCAN_ECR_TXERRCNT_FAST_MASK 0xFF0000u
#define FLEXCAN_ECR_TXERRCNT_FAST_SHIFT 16u
#define FLEXCAN_ECR_TXERRCNT_FAST_WIDTH 8u
#define FLEXCAN_ECR_TXERRCNT_FAST(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ECR_TXERRCNT_FAST_SHIFT))&FLEXCAN_ECR_TXERRCNT_FAST_MASK)
#define FLEXCAN_ECR_RXERRCNT_MASK      0xFF00u
#define FLEXCAN_ECR_RXERRCNT_SHIFT     8u
#define FLEXCAN_ECR_RXERRCNT_WIDTH     8u
#define FLEXCAN_ECR_RXERRCNT(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ECR_RXERRCNT_SHIFT))&FLEXCAN_ECR_RXERRCNT_MASK)
#define FLEXCAN_ECR_TXERRCNT_MASK      0xFFu
#define FLEXCAN_ECR_TXERRCNT_SHIFT     0u
#define FLEXCAN_ECR_TXERRCNT_WIDTH     8u
#define FLEXCAN_ECR_TXERRCNT(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ECR_TXERRCNT_SHIFT))&FLEXCAN_ECR_TXERRCNT_MASK)
/* ECR Reg Mask */
#define FLEXCAN_ECR_MASK               0xFFFFFFFFu
/* ESR1 Bit Fields */
#define FLEXCAN_ESR1_BIT1ERR_FAST_MASK 0x80000000u
#define FLEXCAN_ESR1_BIT1ERR_FAST_SHIFT 31u
#define FLEXCAN_ESR1_BIT1ERR_FAST_WIDTH 1u
#define FLEXCAN_ESR1_BIT1ERR_FAST(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_BIT1ERR_FAST_SHIFT))&FLEXCAN_ESR1_BIT1ERR_FAST_MASK)
#define FLEXCAN_ESR1_BIT0ERR_FAST_MASK 0x40000000u
#define FLEXCAN_ESR1_BIT0ERR_FAST_SHIFT 30u
#define FLEXCAN_ESR1_BIT0ERR_FAST_WIDTH 1u
#define FLEXCAN_ESR1_BIT0ERR_FAST(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_BIT0ERR_FAST_SHIFT))&FLEXCAN_ESR1_BIT0ERR_FAST_MASK)
#define FLEXCAN_ESR1_CRCERR_FAST_MASK  0x10000000u
#define FLEXCAN_ESR1_CRCERR_FAST_SHIFT 28u
#define FLEXCAN_ESR1_CRCERR_FAST_WIDTH 1u
#define FLEXCAN_ESR1_CRCERR_FAST(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_CRCERR_FAST_SHIFT))&FLEXCAN_ESR1_CRCERR_FAST_MASK)
#define FLEXCAN_ESR1_FRMERR_FAST_MASK  0x8000000u
#define FLEXCAN_ESR1_FRMERR_FAST_SHIFT 27u
#define FLEXCAN_ESR1_FRMERR_FAST_WIDTH 1u
#define FLEXCAN_ESR1_FRMERR_FAST(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_FRMERR_FAST_SHIFT))&FLEXCAN_ESR1_FRMERR_FAST_MASK)
#define FLEXCAN_ESR1_STFERR_FAST_MASK  0x4000000u
#define FLEXCAN_ESR1_STFERR_FAST_SHIFT 26u
#define FLEXCAN_ESR1_STFERR_FAST_WIDTH 1u
#define FLEXCAN_ESR1_STFERR_FAST(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_STFERR_FAST_SHIFT))&FLEXCAN_ESR1_STFERR_FAST_MASK)
#define FLEXCAN_ESR1_ERROVR_MASK       0x200000u
#define FLEXCAN_ESR1_ERROVR_SHIFT      21u
#define FLEXCAN_ESR1_ERROVR_WIDTH      1u
#define FLEXCAN_ESR1_ERROVR(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_ERROVR_SHIFT))&FLEXCAN_ESR1_ERROVR_MASK)
#define FLEXCAN_ESR1_ERRINT_FAST_MASK  0x100000u
#define FLEXCAN_ESR1_ERRINT_FAST_SHIFT 20u
#define FLEXCAN_ESR1_ERRINT_FAST_WIDTH 1u
#define FLEXCAN_ESR1_ERRINT_FAST(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_ERRINT_FAST_SHIFT))&FLEXCAN_ESR1_ERRINT_FAST_MASK)
#define FLEXCAN_ESR1_BOFFDONEINT_MASK  0x80000u
#define FLEXCAN_ESR1_BOFFDONEINT_SHIFT 19u
#define FLEXCAN_ESR1_BOFFDONEINT_WIDTH 1u
#define FLEXCAN_ESR1_BOFFDONEINT(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_BOFFDONEINT_SHIFT))&FLEXCAN_ESR1_BOFFDONEINT_MASK)
#define FLEXCAN_ESR1_SYNCH_MASK        0x40000u
#define FLEXCAN_ESR1_SYNCH_SHIFT       18u
#define FLEXCAN_ESR1_SYNCH_WIDTH       1u
#define FLEXCAN_ESR1_SYNCH(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_SYNCH_SHIFT))&FLEXCAN_ESR1_SYNCH_MASK)
#define FLEXCAN_ESR1_TWRNINT_MASK      0x20000u
#define FLEXCAN_ESR1_TWRNINT_SHIFT     17u
#define FLEXCAN_ESR1_TWRNINT_WIDTH     1u
#define FLEXCAN_ESR1_TWRNINT(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_TWRNINT_SHIFT))&FLEXCAN_ESR1_TWRNINT_MASK)
#define FLEXCAN_ESR1_RWRNINT_MASK      0x10000u
#define FLEXCAN_ESR1_RWRNINT_SHIFT     16u
#define FLEXCAN_ESR1_RWRNINT_WIDTH     1u
#define FLEXCAN_ESR1_RWRNINT(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_RWRNINT_SHIFT))&FLEXCAN_ESR1_RWRNINT_MASK)
#define FLEXCAN_ESR1_BIT1ERR_MASK      0x8000u
#define FLEXCAN_ESR1_BIT1ERR_SHIFT     15u
#define FLEXCAN_ESR1_BIT1ERR_WIDTH     1u
#define FLEXCAN_ESR1_BIT1ERR(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_BIT1ERR_SHIFT))&FLEXCAN_ESR1_BIT1ERR_MASK)
#define FLEXCAN_ESR1_BIT0ERR_MASK      0x4000u
#define FLEXCAN_ESR1_BIT0ERR_SHIFT     14u
#define FLEXCAN_ESR1_BIT0ERR_WIDTH     1u
#define FLEXCAN_ESR1_BIT0ERR(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_BIT0ERR_SHIFT))&FLEXCAN_ESR1_BIT0ERR_MASK)
#define FLEXCAN_ESR1_ACKERR_MASK       0x2000u
#define FLEXCAN_ESR1_ACKERR_SHIFT      13u
#define FLEXCAN_ESR1_ACKERR_WIDTH      1u
#define FLEXCAN_ESR1_ACKERR(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_ACKERR_SHIFT))&FLEXCAN_ESR1_ACKERR_MASK)
#define FLEXCAN_ESR1_CRCERR_MASK       0x1000u
#define FLEXCAN_ESR1_CRCERR_SHIFT      12u
#define FLEXCAN_ESR1_CRCERR_WIDTH      1u
#define FLEXCAN_ESR1_CRCERR(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_CRCERR_SHIFT))&FLEXCAN_ESR1_CRCERR_MASK)
#define FLEXCAN_ESR1_FRMERR_MASK       0x800u
#define FLEXCAN_ESR1_FRMERR_SHIFT      11u
#define FLEXCAN_ESR1_FRMERR_WIDTH      1u
#define FLEXCAN_ESR1_FRMERR(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_FRMERR_SHIFT))&FLEXCAN_ESR1_FRMERR_MASK)
#define FLEXCAN_ESR1_STFERR_MASK       0x400u
#define FLEXCAN_ESR1_STFERR_SHIFT      10u
#define FLEXCAN_ESR1_STFERR_WIDTH      1u
#define FLEXCAN_ESR1_STFERR(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_STFERR_SHIFT))&FLEXCAN_ESR1_STFERR_MASK)
#define FLEXCAN_ESR1_TXWRN_MASK        0x200u
#define FLEXCAN_ESR1_TXWRN_SHIFT       9u
#define FLEXCAN_ESR1_TXWRN_WIDTH       1u
#define FLEXCAN_ESR1_TXWRN(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_TXWRN_SHIFT))&FLEXCAN_ESR1_TXWRN_MASK)
#define FLEXCAN_ESR1_RXWRN_MASK        0x100u
#define FLEXCAN_ESR1_RXWRN_SHIFT       8u
#define FLEXCAN_ESR1_RXWRN_WIDTH       1u
#define FLEXCAN_ESR1_RXWRN(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_RXWRN_SHIFT))&FLEXCAN_ESR1_RXWRN_MASK)
#define FLEXCAN_ESR1_IDLE_MASK         0x80u
#define FLEXCAN_ESR1_IDLE_SHIFT        7u
#define FLEXCAN_ESR1_IDLE_WIDTH        1u
#define FLEXCAN_ESR1_IDLE(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_IDLE_SHIFT))&FLEXCAN_ESR1_IDLE_MASK)
#define FLEXCAN_ESR1_TX_MASK           0x40u
#define FLEXCAN_ESR1_TX_SHIFT          6u
#define FLEXCAN_ESR1_TX_WIDTH          1u
#define FLEXCAN_ESR1_TX(x)             (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_TX_SHIFT))&FLEXCAN_ESR1_TX_MASK)
#define FLEXCAN_ESR1_FLTCONF_MASK      0x30u
#define FLEXCAN_ESR1_FLTCONF_SHIFT     4u
#define FLEXCAN_ESR1_FLTCONF_WIDTH     2u
#define FLEXCAN_ESR1_FLTCONF(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_FLTCONF_SHIFT))&FLEXCAN_ESR1_FLTCONF_MASK)
#define FLEXCAN_ESR1_RX_MASK           0x8u
#define FLEXCAN_ESR1_RX_SHIFT          3u
#define FLEXCAN_ESR1_RX_WIDTH          1u
#define FLEXCAN_ESR1_RX(x)             (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_RX_SHIFT))&FLEXCAN_ESR1_RX_MASK)
#define FLEXCAN_ESR1_BOFFINT_MASK      0x4u
#define FLEXCAN_ESR1_BOFFINT_SHIFT     2u
#define FLEXCAN_ESR1_BOFFINT_WIDTH     1u
#define FLEXCAN_ESR1_BOFFINT(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_BOFFINT_SHIFT))&FLEXCAN_ESR1_BOFFINT_MASK)
#define FLEXCAN_ESR1_ERRINT_MASK       0x2u
#define FLEXCAN_ESR1_ERRINT_SHIFT      1u
#define FLEXCAN_ESR1_ERRINT_WIDTH      1u
#define FLEXCAN_ESR1_ERRINT(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR1_ERRINT_SHIFT))&FLEXCAN_ESR1_ERRINT_MASK)
/* ESR1 Reg Mask */
#define FLEXCAN_ESR1_MASK              0xDC3FFFFEu
/* IMASK1 Bit Fields */
#define FLEXCAN_IMASK1_BUF31TO0M_MASK  0xFFFFFFFFu
#define FLEXCAN_IMASK1_BUF31TO0M_SHIFT 0u
#define FLEXCAN_IMASK1_BUF31TO0M_WIDTH 32u
#define FLEXCAN_IMASK1_BUF31TO0M(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_IMASK1_BUF31TO0M_SHIFT))&FLEXCAN_IMASK1_BUF31TO0M_MASK)
/* IMASK1 Reg Mask */
#define FLEXCAN_IMASK1_MASK            0xFFFFFFFFu
/* IFLAG1 Bit Fields */
#define FLEXCAN_IFLAG1_BUF31TO8I_MASK  0xFFFFFF00u
#define FLEXCAN_IFLAG1_BUF31TO8I_SHIFT 8u
#define FLEXCAN_IFLAG1_BUF31TO8I_WIDTH 24u
#define FLEXCAN_IFLAG1_BUF31TO8I(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_IFLAG1_BUF31TO8I_SHIFT))&FLEXCAN_IFLAG1_BUF31TO8I_MASK)
#define FLEXCAN_IFLAG1_BUF7I_MASK      0x80u
#define FLEXCAN_IFLAG1_BUF7I_SHIFT     7u
#define FLEXCAN_IFLAG1_BUF7I_WIDTH     1u
#define FLEXCAN_IFLAG1_BUF7I(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_IFLAG1_BUF7I_SHIFT))&FLEXCAN_IFLAG1_BUF7I_MASK)
#define FLEXCAN_IFLAG1_BUF6I_MASK      0x40u
#define FLEXCAN_IFLAG1_BUF6I_SHIFT     6u
#define FLEXCAN_IFLAG1_BUF6I_WIDTH     1u
#define FLEXCAN_IFLAG1_BUF6I(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_IFLAG1_BUF6I_SHIFT))&FLEXCAN_IFLAG1_BUF6I_MASK)
#define FLEXCAN_IFLAG1_BUF5I_MASK      0x20u
#define FLEXCAN_IFLAG1_BUF5I_SHIFT     5u
#define FLEXCAN_IFLAG1_BUF5I_WIDTH     1u
#define FLEXCAN_IFLAG1_BUF5I(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_IFLAG1_BUF5I_SHIFT))&FLEXCAN_IFLAG1_BUF5I_MASK)
#define FLEXCAN_IFLAG1_BUF4TO1I_MASK   0x1Eu
#define FLEXCAN_IFLAG1_BUF4TO1I_SHIFT  1u
#define FLEXCAN_IFLAG1_BUF4TO1I_WIDTH  4u
#define FLEXCAN_IFLAG1_BUF4TO1I(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_IFLAG1_BUF4TO1I_SHIFT))&FLEXCAN_IFLAG1_BUF4TO1I_MASK)
#define FLEXCAN_IFLAG1_BUF0I_MASK      0x1u
#define FLEXCAN_IFLAG1_BUF0I_SHIFT     0u
#define FLEXCAN_IFLAG1_BUF0I_WIDTH     1u
#define FLEXCAN_IFLAG1_BUF0I(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_IFLAG1_BUF0I_SHIFT))&FLEXCAN_IFLAG1_BUF0I_MASK)
/* IFLAG1 Reg Mask */
#define FLEXCAN_IFLAG1_MASK            0xFFFFFFFFu
/* CTRL2 Bit Fields */
#define FLEXCAN_CTRL2_ERRMSK_FAST_MASK 0x80000000u
#define FLEXCAN_CTRL2_ERRMSK_FAST_SHIFT 31u
#define FLEXCAN_CTRL2_ERRMSK_FAST_WIDTH 1u
#define FLEXCAN_CTRL2_ERRMSK_FAST(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_ERRMSK_FAST_SHIFT))&FLEXCAN_CTRL2_ERRMSK_FAST_MASK)
#define FLEXCAN_CTRL2_BOFFDONEMSK_MASK 0x40000000u
#define FLEXCAN_CTRL2_BOFFDONEMSK_SHIFT 30u
#define FLEXCAN_CTRL2_BOFFDONEMSK_WIDTH 1u
#define FLEXCAN_CTRL2_BOFFDONEMSK(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_BOFFDONEMSK_SHIFT))&FLEXCAN_CTRL2_BOFFDONEMSK_MASK)
#define FLEXCAN_CTRL2_ECRWRE_MASK      0x20000000u
#define FLEXCAN_CTRL2_ECRWRE_SHIFT     29u
#define FLEXCAN_CTRL2_ECRWRE_WIDTH     1u
#define FLEXCAN_CTRL2_ECRWRE(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_ECRWRE_SHIFT))&FLEXCAN_CTRL2_ECRWRE_MASK)
#define FLEXCAN_CTRL2_WRMFRZ_MASK      0x10000000u
#define FLEXCAN_CTRL2_WRMFRZ_SHIFT     28u
#define FLEXCAN_CTRL2_WRMFRZ_WIDTH     1u
#define FLEXCAN_CTRL2_WRMFRZ(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_WRMFRZ_SHIFT))&FLEXCAN_CTRL2_WRMFRZ_MASK)
#define FLEXCAN_CTRL2_RFFN_MASK        0xF000000u
#define FLEXCAN_CTRL2_RFFN_SHIFT       24u
#define FLEXCAN_CTRL2_RFFN_WIDTH       4u
#define FLEXCAN_CTRL2_RFFN(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_RFFN_SHIFT))&FLEXCAN_CTRL2_RFFN_MASK)
#define FLEXCAN_CTRL2_TASD_MASK        0xF80000u
#define FLEXCAN_CTRL2_TASD_SHIFT       19u
#define FLEXCAN_CTRL2_TASD_WIDTH       5u
#define FLEXCAN_CTRL2_TASD(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_TASD_SHIFT))&FLEXCAN_CTRL2_TASD_MASK)
#define FLEXCAN_CTRL2_MRP_MASK         0x40000u
#define FLEXCAN_CTRL2_MRP_SHIFT        18u
#define FLEXCAN_CTRL2_MRP_WIDTH        1u
#define FLEXCAN_CTRL2_MRP(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_MRP_SHIFT))&FLEXCAN_CTRL2_MRP_MASK)
#define FLEXCAN_CTRL2_RRS_MASK         0x20000u
#define FLEXCAN_CTRL2_RRS_SHIFT        17u
#define FLEXCAN_CTRL2_RRS_WIDTH        1u
#define FLEXCAN_CTRL2_RRS(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_RRS_SHIFT))&FLEXCAN_CTRL2_RRS_MASK)
#define FLEXCAN_CTRL2_EACEN_MASK       0x10000u
#define FLEXCAN_CTRL2_EACEN_SHIFT      16u
#define FLEXCAN_CTRL2_EACEN_WIDTH      1u
#define FLEXCAN_CTRL2_EACEN(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_EACEN_SHIFT))&FLEXCAN_CTRL2_EACEN_MASK)
#define FLEXCAN_CTRL2_TIMER_SRC_MASK   0x8000u
#define FLEXCAN_CTRL2_TIMER_SRC_SHIFT  15u
#define FLEXCAN_CTRL2_TIMER_SRC_WIDTH  1u
#define FLEXCAN_CTRL2_TIMER_SRC(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_TIMER_SRC_SHIFT))&FLEXCAN_CTRL2_TIMER_SRC_MASK)
#define FLEXCAN_CTRL2_PREXCEN_MASK     0x4000u
#define FLEXCAN_CTRL2_PREXCEN_SHIFT    14u
#define FLEXCAN_CTRL2_PREXCEN_WIDTH    1u
#define FLEXCAN_CTRL2_PREXCEN(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_PREXCEN_SHIFT))&FLEXCAN_CTRL2_PREXCEN_MASK)
#define FLEXCAN_CTRL2_BTE_MASK         0x2000u
#define FLEXCAN_CTRL2_BTE_SHIFT        13u
#define FLEXCAN_CTRL2_BTE_WIDTH        1u
#define FLEXCAN_CTRL2_BTE(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_BTE_SHIFT))&FLEXCAN_CTRL2_BTE_MASK)
#define FLEXCAN_CTRL2_ISOCANFDEN_MASK  0x1000u
#define FLEXCAN_CTRL2_ISOCANFDEN_SHIFT 12u
#define FLEXCAN_CTRL2_ISOCANFDEN_WIDTH 1u
#define FLEXCAN_CTRL2_ISOCANFDEN(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_ISOCANFDEN_SHIFT))&FLEXCAN_CTRL2_ISOCANFDEN_MASK)
#define FLEXCAN_CTRL2_EDFLTDIS_MASK    0x800u
#define FLEXCAN_CTRL2_EDFLTDIS_SHIFT   11u
#define FLEXCAN_CTRL2_EDFLTDIS_WIDTH   1u
#define FLEXCAN_CTRL2_EDFLTDIS(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_EDFLTDIS_SHIFT))&FLEXCAN_CTRL2_EDFLTDIS_MASK)
/* CTRL2 Reg Mask */
#define FLEXCAN_CTRL2_MASK             0xFFFFF800u
/* ESR2 Bit Fields */
#define FLEXCAN_ESR2_LPTM_MASK         0x7F0000u
#define FLEXCAN_ESR2_LPTM_SHIFT        16u
#define FLEXCAN_ESR2_LPTM_WIDTH        7u
#define FLEXCAN_ESR2_LPTM(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR2_LPTM_SHIFT))&FLEXCAN_ESR2_LPTM_MASK)
#define FLEXCAN_ESR2_VPS_MASK          0x4000u
#define FLEXCAN_ESR2_VPS_SHIFT         14u
#define FLEXCAN_ESR2_VPS_WIDTH         1u
#define FLEXCAN_ESR2_VPS(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR2_VPS_SHIFT))&FLEXCAN_ESR2_VPS_MASK)
#define FLEXCAN_ESR2_IMB_MASK          0x2000u
#define FLEXCAN_ESR2_IMB_SHIFT         13u
#define FLEXCAN_ESR2_IMB_WIDTH         1u
#define FLEXCAN_ESR2_IMB(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ESR2_IMB_SHIFT))&FLEXCAN_ESR2_IMB_MASK)
/* ESR2 Reg Mask */
#define FLEXCAN_ESR2_MASK              0x007F6000u
/* CRCR Bit Fields */
#define FLEXCAN_CRCR_MBCRC_MASK        0x7F0000u
#define FLEXCAN_CRCR_MBCRC_SHIFT       16u
#define FLEXCAN_CRCR_MBCRC_WIDTH       7u
#define FLEXCAN_CRCR_MBCRC(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CRCR_MBCRC_SHIFT))&FLEXCAN_CRCR_MBCRC_MASK)
#define FLEXCAN_CRCR_TXCRC_MASK        0x7FFFu
#define FLEXCAN_CRCR_TXCRC_SHIFT       0u
#define FLEXCAN_CRCR_TXCRC_WIDTH       15u
#define FLEXCAN_CRCR_TXCRC(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CRCR_TXCRC_SHIFT))&FLEXCAN_CRCR_TXCRC_MASK)
/* CRCR Reg Mask */
#define FLEXCAN_CRCR_MASK              0x007F7FFFu
/* RXFGMASK Bit Fields */
#define FLEXCAN_RXFGMASK_FGM_MASK      0xFFFFFFFFu
#define FLEXCAN_RXFGMASK_FGM_SHIFT     0u
#define FLEXCAN_RXFGMASK_FGM_WIDTH     32u
#define FLEXCAN_RXFGMASK_FGM(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RXFGMASK_FGM_SHIFT))&FLEXCAN_RXFGMASK_FGM_MASK)
/* RXFGMASK Reg Mask */
#define FLEXCAN_RXFGMASK_MASK          0xFFFFFFFFu
/* RXFIR Bit Fields */
#define FLEXCAN_RXFIR_IDHIT_MASK       0x1FFu
#define FLEXCAN_RXFIR_IDHIT_SHIFT      0u
#define FLEXCAN_RXFIR_IDHIT_WIDTH      9u
#define FLEXCAN_RXFIR_IDHIT(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RXFIR_IDHIT_SHIFT))&FLEXCAN_RXFIR_IDHIT_MASK)
/* RXFIR Reg Mask */
#define FLEXCAN_RXFIR_MASK             0x000001FFu
/* CBT Bit Fields */
#define FLEXCAN_CBT_BTF_MASK           0x80000000u
#define FLEXCAN_CBT_BTF_SHIFT          31u
#define FLEXCAN_CBT_BTF_WIDTH          1u
#define FLEXCAN_CBT_BTF(x)             (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CBT_BTF_SHIFT))&FLEXCAN_CBT_BTF_MASK)
#define FLEXCAN_CBT_EPRESDIV_MASK      0x7FE00000u
#define FLEXCAN_CBT_EPRESDIV_SHIFT     21u
#define FLEXCAN_CBT_EPRESDIV_WIDTH     10u
#define FLEXCAN_CBT_EPRESDIV(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CBT_EPRESDIV_SHIFT))&FLEXCAN_CBT_EPRESDIV_MASK)
#define FLEXCAN_CBT_ERJW_MASK          0x1F0000u
#define FLEXCAN_CBT_ERJW_SHIFT         16u
#define FLEXCAN_CBT_ERJW_WIDTH         5u
#define FLEXCAN_CBT_ERJW(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CBT_ERJW_SHIFT))&FLEXCAN_CBT_ERJW_MASK)
#define FLEXCAN_CBT_EPROPSEG_MASK      0xFC00u
#define FLEXCAN_CBT_EPROPSEG_SHIFT     10u
#define FLEXCAN_CBT_EPROPSEG_WIDTH     6u
#define FLEXCAN_CBT_EPROPSEG(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CBT_EPROPSEG_SHIFT))&FLEXCAN_CBT_EPROPSEG_MASK)
#define FLEXCAN_CBT_EPSEG1_MASK        0x3E0u
#define FLEXCAN_CBT_EPSEG1_SHIFT       5u
#define FLEXCAN_CBT_EPSEG1_WIDTH       5u
#define FLEXCAN_CBT_EPSEG1(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CBT_EPSEG1_SHIFT))&FLEXCAN_CBT_EPSEG1_MASK)
#define FLEXCAN_CBT_EPSEG2_MASK        0x1Fu
#define FLEXCAN_CBT_EPSEG2_SHIFT       0u
#define FLEXCAN_CBT_EPSEG2_WIDTH       5u
#define FLEXCAN_CBT_EPSEG2(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CBT_EPSEG2_SHIFT))&FLEXCAN_CBT_EPSEG2_MASK)
/* CBT Reg Mask */
#define FLEXCAN_CBT_MASK               0xFFFFFFFFu
/* RAM Bit Fields */
/* RAM0 Reg Mask */
#define FLEXCAN_RAM_MASK               0x00000000u
/* RXIMR Bit Fields */
#define FLEXCAN_RXIMR_MI_MASK          0xFFFFFFFFu
#define FLEXCAN_RXIMR_MI_SHIFT         0u
#define FLEXCAN_RXIMR_MI_WIDTH         32u
#define FLEXCAN_RXIMR_MI(x)            (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RXIMR_MI_SHIFT))&FLEXCAN_RXIMR_MI_MASK)
/* RXIMR0 Reg Mask */
#define FLEXCAN_RXIMR_MASK             0xFFFFFFFFu
/* MECR Bit Fields */
#define FLEXCAN_MECR_ECRWRDIS_MASK     0x80000000u
#define FLEXCAN_MECR_ECRWRDIS_SHIFT    31u
#define FLEXCAN_MECR_ECRWRDIS_WIDTH    1u
#define FLEXCAN_MECR_ECRWRDIS(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_ECRWRDIS_SHIFT))&FLEXCAN_MECR_ECRWRDIS_MASK)
#define FLEXCAN_MECR_HANCEI_MSK_MASK   0x80000u
#define FLEXCAN_MECR_HANCEI_MSK_SHIFT  19u
#define FLEXCAN_MECR_HANCEI_MSK_WIDTH  1u
#define FLEXCAN_MECR_HANCEI_MSK(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_HANCEI_MSK_SHIFT))&FLEXCAN_MECR_HANCEI_MSK_MASK)
#define FLEXCAN_MECR_FANCEI_MSK_MASK   0x40000u
#define FLEXCAN_MECR_FANCEI_MSK_SHIFT  18u
#define FLEXCAN_MECR_FANCEI_MSK_WIDTH  1u
#define FLEXCAN_MECR_FANCEI_MSK(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_FANCEI_MSK_SHIFT))&FLEXCAN_MECR_FANCEI_MSK_MASK)
#define FLEXCAN_MECR_CEI_MSK_MASK      0x10000u
#define FLEXCAN_MECR_CEI_MSK_SHIFT     16u
#define FLEXCAN_MECR_CEI_MSK_WIDTH     1u
#define FLEXCAN_MECR_CEI_MSK(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_CEI_MSK_SHIFT))&FLEXCAN_MECR_CEI_MSK_MASK)
#define FLEXCAN_MECR_HAERRIE_MASK      0x8000u
#define FLEXCAN_MECR_HAERRIE_SHIFT     15u
#define FLEXCAN_MECR_HAERRIE_WIDTH     1u
#define FLEXCAN_MECR_HAERRIE(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_HAERRIE_SHIFT))&FLEXCAN_MECR_HAERRIE_MASK)
#define FLEXCAN_MECR_FAERRIE_MASK      0x4000u
#define FLEXCAN_MECR_FAERRIE_SHIFT     14u
#define FLEXCAN_MECR_FAERRIE_WIDTH     1u
#define FLEXCAN_MECR_FAERRIE(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_FAERRIE_SHIFT))&FLEXCAN_MECR_FAERRIE_MASK)
#define FLEXCAN_MECR_EXTERRIE_MASK     0x2000u
#define FLEXCAN_MECR_EXTERRIE_SHIFT    13u
#define FLEXCAN_MECR_EXTERRIE_WIDTH    1u
#define FLEXCAN_MECR_EXTERRIE(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_EXTERRIE_SHIFT))&FLEXCAN_MECR_EXTERRIE_MASK)
#define FLEXCAN_MECR_RERRDIS_MASK      0x200u
#define FLEXCAN_MECR_RERRDIS_SHIFT     9u
#define FLEXCAN_MECR_RERRDIS_WIDTH     1u
#define FLEXCAN_MECR_RERRDIS(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_RERRDIS_SHIFT))&FLEXCAN_MECR_RERRDIS_MASK)
#define FLEXCAN_MECR_ECCDIS_MASK       0x100u
#define FLEXCAN_MECR_ECCDIS_SHIFT      8u
#define FLEXCAN_MECR_ECCDIS_WIDTH      1u
#define FLEXCAN_MECR_ECCDIS(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_ECCDIS_SHIFT))&FLEXCAN_MECR_ECCDIS_MASK)
#define FLEXCAN_MECR_NCEFAFRZ_MASK     0x80u
#define FLEXCAN_MECR_NCEFAFRZ_SHIFT    7u
#define FLEXCAN_MECR_NCEFAFRZ_WIDTH    1u
#define FLEXCAN_MECR_NCEFAFRZ(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_MECR_NCEFAFRZ_SHIFT))&FLEXCAN_MECR_NCEFAFRZ_MASK)
/* MECR Reg Mask */
#define FLEXCAN_MECR_MASK              0x800DE380u
/* ERRIAR Bit Fields */
#define FLEXCAN_ERRIAR_INJADDR_H_MASK  0x3FFCu
#define FLEXCAN_ERRIAR_INJADDR_H_SHIFT 2u
#define FLEXCAN_ERRIAR_INJADDR_H_WIDTH 12u
#define FLEXCAN_ERRIAR_INJADDR_H(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRIAR_INJADDR_H_SHIFT))&FLEXCAN_ERRIAR_INJADDR_H_MASK)
#define FLEXCAN_ERRIAR_INJADDR_L_MASK  0x3u
#define FLEXCAN_ERRIAR_INJADDR_L_SHIFT 0u
#define FLEXCAN_ERRIAR_INJADDR_L_WIDTH 2u
#define FLEXCAN_ERRIAR_INJADDR_L(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRIAR_INJADDR_L_SHIFT))&FLEXCAN_ERRIAR_INJADDR_L_MASK)
/* ERRIAR Reg Mask */
#define FLEXCAN_ERRIAR_MASK            0x00003FFFu
/* ERRIDPR Bit Fields */
#define FLEXCAN_ERRIDPR_DFLIP_MASK     0xFFFFFFFFu
#define FLEXCAN_ERRIDPR_DFLIP_SHIFT    0u
#define FLEXCAN_ERRIDPR_DFLIP_WIDTH    32u
#define FLEXCAN_ERRIDPR_DFLIP(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRIDPR_DFLIP_SHIFT))&FLEXCAN_ERRIDPR_DFLIP_MASK)
/* ERRIDPR Reg Mask */
#define FLEXCAN_ERRIDPR_MASK           0xFFFFFFFFu
/* ERRIPPR Bit Fields */
#define FLEXCAN_ERRIPPR_PFLIP3_MASK    0x1F000000u
#define FLEXCAN_ERRIPPR_PFLIP3_SHIFT   24u
#define FLEXCAN_ERRIPPR_PFLIP3_WIDTH   5u
#define FLEXCAN_ERRIPPR_PFLIP3(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRIPPR_PFLIP3_SHIFT))&FLEXCAN_ERRIPPR_PFLIP3_MASK)
#define FLEXCAN_ERRIPPR_PFLIP2_MASK    0x1F0000u
#define FLEXCAN_ERRIPPR_PFLIP2_SHIFT   16u
#define FLEXCAN_ERRIPPR_PFLIP2_WIDTH   5u
#define FLEXCAN_ERRIPPR_PFLIP2(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRIPPR_PFLIP2_SHIFT))&FLEXCAN_ERRIPPR_PFLIP2_MASK)
#define FLEXCAN_ERRIPPR_PFLIP1_MASK    0x1F00u
#define FLEXCAN_ERRIPPR_PFLIP1_SHIFT   8u
#define FLEXCAN_ERRIPPR_PFLIP1_WIDTH   5u
#define FLEXCAN_ERRIPPR_PFLIP1(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRIPPR_PFLIP1_SHIFT))&FLEXCAN_ERRIPPR_PFLIP1_MASK)
#define FLEXCAN_ERRIPPR_PFLIP0_MASK    0x1Fu
#define FLEXCAN_ERRIPPR_PFLIP0_SHIFT   0u
#define FLEXCAN_ERRIPPR_PFLIP0_WIDTH   5u
#define FLEXCAN_ERRIPPR_PFLIP0(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRIPPR_PFLIP0_SHIFT))&FLEXCAN_ERRIPPR_PFLIP0_MASK)
/* ERRIPPR Reg Mask */
#define FLEXCAN_ERRIPPR_MASK           0x1F1F1F1Fu
/* RERRAR Bit Fields */
#define FLEXCAN_RERRAR_NCE_MASK        0x1000000u
#define FLEXCAN_RERRAR_NCE_SHIFT       24u
#define FLEXCAN_RERRAR_NCE_WIDTH       1u
#define FLEXCAN_RERRAR_NCE(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRAR_NCE_SHIFT))&FLEXCAN_RERRAR_NCE_MASK)
#define FLEXCAN_RERRAR_SAID_MASK       0x70000u
#define FLEXCAN_RERRAR_SAID_SHIFT      16u
#define FLEXCAN_RERRAR_SAID_WIDTH      3u
#define FLEXCAN_RERRAR_SAID(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRAR_SAID_SHIFT))&FLEXCAN_RERRAR_SAID_MASK)
#define FLEXCAN_RERRAR_ERRADDR_MASK    0x3FFCu
#define FLEXCAN_RERRAR_ERRADDR_SHIFT   2u
#define FLEXCAN_RERRAR_ERRADDR_WIDTH   12u
#define FLEXCAN_RERRAR_ERRADDR(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRAR_ERRADDR_SHIFT))&FLEXCAN_RERRAR_ERRADDR_MASK)
/* RERRAR Reg Mask */
#define FLEXCAN_RERRAR_MASK            0x01073FFCu
/* RERRDR Bit Fields */
#define FLEXCAN_RERRDR_RDATA_MASK      0xFFFFFFFFu
#define FLEXCAN_RERRDR_RDATA_SHIFT     0u
#define FLEXCAN_RERRDR_RDATA_WIDTH     32u
#define FLEXCAN_RERRDR_RDATA(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRDR_RDATA_SHIFT))&FLEXCAN_RERRDR_RDATA_MASK)
/* RERRDR Reg Mask */
#define FLEXCAN_RERRDR_MASK            0xFFFFFFFFu
/* RERRSYNR Bit Fields */
#define FLEXCAN_RERRSYNR_BE3_MASK      0x80000000u
#define FLEXCAN_RERRSYNR_BE3_SHIFT     31u
#define FLEXCAN_RERRSYNR_BE3_WIDTH     1u
#define FLEXCAN_RERRSYNR_BE3(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_BE3_SHIFT))&FLEXCAN_RERRSYNR_BE3_MASK)
#define FLEXCAN_RERRSYNR_SYND3_MASK    0x1F000000u
#define FLEXCAN_RERRSYNR_SYND3_SHIFT   24u
#define FLEXCAN_RERRSYNR_SYND3_WIDTH   5u
#define FLEXCAN_RERRSYNR_SYND3(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_SYND3_SHIFT))&FLEXCAN_RERRSYNR_SYND3_MASK)
#define FLEXCAN_RERRSYNR_BE2_MASK      0x800000u
#define FLEXCAN_RERRSYNR_BE2_SHIFT     23u
#define FLEXCAN_RERRSYNR_BE2_WIDTH     1u
#define FLEXCAN_RERRSYNR_BE2(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_BE2_SHIFT))&FLEXCAN_RERRSYNR_BE2_MASK)
#define FLEXCAN_RERRSYNR_SYND2_MASK    0x1F0000u
#define FLEXCAN_RERRSYNR_SYND2_SHIFT   16u
#define FLEXCAN_RERRSYNR_SYND2_WIDTH   5u
#define FLEXCAN_RERRSYNR_SYND2(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_SYND2_SHIFT))&FLEXCAN_RERRSYNR_SYND2_MASK)
#define FLEXCAN_RERRSYNR_BE1_MASK      0x8000u
#define FLEXCAN_RERRSYNR_BE1_SHIFT     15u
#define FLEXCAN_RERRSYNR_BE1_WIDTH     1u
#define FLEXCAN_RERRSYNR_BE1(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_BE1_SHIFT))&FLEXCAN_RERRSYNR_BE1_MASK)
#define FLEXCAN_RERRSYNR_SYND1_MASK    0x1F00u
#define FLEXCAN_RERRSYNR_SYND1_SHIFT   8u
#define FLEXCAN_RERRSYNR_SYND1_WIDTH   5u
#define FLEXCAN_RERRSYNR_SYND1(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_SYND1_SHIFT))&FLEXCAN_RERRSYNR_SYND1_MASK)
#define FLEXCAN_RERRSYNR_BE0_MASK      0x80u
#define FLEXCAN_RERRSYNR_BE0_SHIFT     7u
#define FLEXCAN_RERRSYNR_BE0_WIDTH     1u
#define FLEXCAN_RERRSYNR_BE0(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_BE0_SHIFT))&FLEXCAN_RERRSYNR_BE0_MASK)
#define FLEXCAN_RERRSYNR_SYND0_MASK    0x1Fu
#define FLEXCAN_RERRSYNR_SYND0_SHIFT   0u
#define FLEXCAN_RERRSYNR_SYND0_WIDTH   5u
#define FLEXCAN_RERRSYNR_SYND0(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_RERRSYNR_SYND0_SHIFT))&FLEXCAN_RERRSYNR_SYND0_MASK)
/* RERRSYNR Reg Mask */
#define FLEXCAN_RERRSYNR_MASK          0x9F9F9F9Fu
/* ERRSR Bit Fields */
#define FLEXCAN_ERRSR_HANCEIF_MASK     0x80000u
#define FLEXCAN_ERRSR_HANCEIF_SHIFT    19u
#define FLEXCAN_ERRSR_HANCEIF_WIDTH    1u
#define FLEXCAN_ERRSR_HANCEIF(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRSR_HANCEIF_SHIFT))&FLEXCAN_ERRSR_HANCEIF_MASK)
#define FLEXCAN_ERRSR_FANCEIF_MASK     0x40000u
#define FLEXCAN_ERRSR_FANCEIF_SHIFT    18u
#define FLEXCAN_ERRSR_FANCEIF_WIDTH    1u
#define FLEXCAN_ERRSR_FANCEIF(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRSR_FANCEIF_SHIFT))&FLEXCAN_ERRSR_FANCEIF_MASK)
#define FLEXCAN_ERRSR_CEIF_MASK        0x10000u
#define FLEXCAN_ERRSR_CEIF_SHIFT       16u
#define FLEXCAN_ERRSR_CEIF_WIDTH       1u
#define FLEXCAN_ERRSR_CEIF(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRSR_CEIF_SHIFT))&FLEXCAN_ERRSR_CEIF_MASK)
#define FLEXCAN_ERRSR_HANCEIOF_MASK    0x8u
#define FLEXCAN_ERRSR_HANCEIOF_SHIFT   3u
#define FLEXCAN_ERRSR_HANCEIOF_WIDTH   1u
#define FLEXCAN_ERRSR_HANCEIOF(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRSR_HANCEIOF_SHIFT))&FLEXCAN_ERRSR_HANCEIOF_MASK)
#define FLEXCAN_ERRSR_FANCEIOF_MASK    0x4u
#define FLEXCAN_ERRSR_FANCEIOF_SHIFT   2u
#define FLEXCAN_ERRSR_FANCEIOF_WIDTH   1u
#define FLEXCAN_ERRSR_FANCEIOF(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRSR_FANCEIOF_SHIFT))&FLEXCAN_ERRSR_FANCEIOF_MASK)
#define FLEXCAN_ERRSR_CEIOF_MASK       0x1u
#define FLEXCAN_ERRSR_CEIOF_SHIFT      0u
#define FLEXCAN_ERRSR_CEIOF_WIDTH      1u
#define FLEXCAN_ERRSR_CEIOF(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERRSR_CEIOF_SHIFT))&FLEXCAN_ERRSR_CEIOF_MASK)
/* ERRSR Reg Mask */
#define FLEXCAN_ERRSR_MASK             0x000D000Du
/* CTRL1_PN Bit Fields */
#define FLEXCAN_CTRL1_PN_WTOF_MSK_MASK 0x20000u
#define FLEXCAN_CTRL1_PN_WTOF_MSK_SHIFT 17u
#define FLEXCAN_CTRL1_PN_WTOF_MSK_WIDTH 1u
#define FLEXCAN_CTRL1_PN_WTOF_MSK(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PN_WTOF_MSK_SHIFT))&FLEXCAN_CTRL1_PN_WTOF_MSK_MASK)
#define FLEXCAN_CTRL1_PN_WUMF_MSK_MASK 0x10000u
#define FLEXCAN_CTRL1_PN_WUMF_MSK_SHIFT 16u
#define FLEXCAN_CTRL1_PN_WUMF_MSK_WIDTH 1u
#define FLEXCAN_CTRL1_PN_WUMF_MSK(x)   (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PN_WUMF_MSK_SHIFT))&FLEXCAN_CTRL1_PN_WUMF_MSK_MASK)
#define FLEXCAN_CTRL1_PN_NMATCH_MASK   0xFF00u
#define FLEXCAN_CTRL1_PN_NMATCH_SHIFT  8u
#define FLEXCAN_CTRL1_PN_NMATCH_WIDTH  8u
#define FLEXCAN_CTRL1_PN_NMATCH(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PN_NMATCH_SHIFT))&FLEXCAN_CTRL1_PN_NMATCH_MASK)
#define FLEXCAN_CTRL1_PN_PLFS_MASK     0x30u
#define FLEXCAN_CTRL1_PN_PLFS_SHIFT    4u
#define FLEXCAN_CTRL1_PN_PLFS_WIDTH    2u
#define FLEXCAN_CTRL1_PN_PLFS(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PN_PLFS_SHIFT))&FLEXCAN_CTRL1_PN_PLFS_MASK)
#define FLEXCAN_CTRL1_PN_IDFS_MASK     0xCu
#define FLEXCAN_CTRL1_PN_IDFS_SHIFT    2u
#define FLEXCAN_CTRL1_PN_IDFS_WIDTH    2u
#define FLEXCAN_CTRL1_PN_IDFS(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PN_IDFS_SHIFT))&FLEXCAN_CTRL1_PN_IDFS_MASK)
#define FLEXCAN_CTRL1_PN_FCS_MASK      0x3u
#define FLEXCAN_CTRL1_PN_FCS_SHIFT     0u
#define FLEXCAN_CTRL1_PN_FCS_WIDTH     2u
#define FLEXCAN_CTRL1_PN_FCS(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL1_PN_FCS_SHIFT))&FLEXCAN_CTRL1_PN_FCS_MASK)
/* CTRL1_PN Reg Mask */
#define FLEXCAN_CTRL1_PN_MASK          0x0003FF3Fu
/* CTRL2_PN Bit Fields */
#define FLEXCAN_CTRL2_PN_MATCHTO_MASK  0xFFFFu
#define FLEXCAN_CTRL2_PN_MATCHTO_SHIFT 0u
#define FLEXCAN_CTRL2_PN_MATCHTO_WIDTH 16u
#define FLEXCAN_CTRL2_PN_MATCHTO(x)    (((uint32_t)(((uint32_t)(x))<<FLEXCAN_CTRL2_PN_MATCHTO_SHIFT))&FLEXCAN_CTRL2_PN_MATCHTO_MASK)
/* CTRL2_PN Reg Mask */
#define FLEXCAN_CTRL2_PN_MASK          0x0000FFFFu
/* WU_MTC Bit Fields */
#define FLEXCAN_WU_MTC_WTOF_MASK       0x20000u
#define FLEXCAN_WU_MTC_WTOF_SHIFT      17u
#define FLEXCAN_WU_MTC_WTOF_WIDTH      1u
#define FLEXCAN_WU_MTC_WTOF(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WU_MTC_WTOF_SHIFT))&FLEXCAN_WU_MTC_WTOF_MASK)
#define FLEXCAN_WU_MTC_WUMF_MASK       0x10000u
#define FLEXCAN_WU_MTC_WUMF_SHIFT      16u
#define FLEXCAN_WU_MTC_WUMF_WIDTH      1u
#define FLEXCAN_WU_MTC_WUMF(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WU_MTC_WUMF_SHIFT))&FLEXCAN_WU_MTC_WUMF_MASK)
#define FLEXCAN_WU_MTC_MCOUNTER_MASK   0xFF00u
#define FLEXCAN_WU_MTC_MCOUNTER_SHIFT  8u
#define FLEXCAN_WU_MTC_MCOUNTER_WIDTH  8u
#define FLEXCAN_WU_MTC_MCOUNTER(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WU_MTC_MCOUNTER_SHIFT))&FLEXCAN_WU_MTC_MCOUNTER_MASK)
/* WU_MTC Reg Mask */
#define FLEXCAN_WU_MTC_MASK            0x0003FF00u
/* FLT_ID1 Bit Fields */
#define FLEXCAN_FLT_ID1_FLT_IDE_MASK   0x40000000u
#define FLEXCAN_FLT_ID1_FLT_IDE_SHIFT  30u
#define FLEXCAN_FLT_ID1_FLT_IDE_WIDTH  1u
#define FLEXCAN_FLT_ID1_FLT_IDE(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_ID1_FLT_IDE_SHIFT))&FLEXCAN_FLT_ID1_FLT_IDE_MASK)
#define FLEXCAN_FLT_ID1_FLT_RTR_MASK   0x20000000u
#define FLEXCAN_FLT_ID1_FLT_RTR_SHIFT  29u
#define FLEXCAN_FLT_ID1_FLT_RTR_WIDTH  1u
#define FLEXCAN_FLT_ID1_FLT_RTR(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_ID1_FLT_RTR_SHIFT))&FLEXCAN_FLT_ID1_FLT_RTR_MASK)
#define FLEXCAN_FLT_ID1_FLT_ID1_MASK   0x1FFFFFFFu
#define FLEXCAN_FLT_ID1_FLT_ID1_SHIFT  0u
#define FLEXCAN_FLT_ID1_FLT_ID1_WIDTH  29u
#define FLEXCAN_FLT_ID1_FLT_ID1(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_ID1_FLT_ID1_SHIFT))&FLEXCAN_FLT_ID1_FLT_ID1_MASK)
/* FLT_ID1 Reg Mask */
#define FLEXCAN_FLT_ID1_MASK           0x7FFFFFFFu
/* FLT_DLC Bit Fields */
#define FLEXCAN_FLT_DLC_FLT_DLC_LO_MASK 0xF0000u
#define FLEXCAN_FLT_DLC_FLT_DLC_LO_SHIFT 16u
#define FLEXCAN_FLT_DLC_FLT_DLC_LO_WIDTH 4u
#define FLEXCAN_FLT_DLC_FLT_DLC_LO(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_DLC_FLT_DLC_LO_SHIFT))&FLEXCAN_FLT_DLC_FLT_DLC_LO_MASK)
#define FLEXCAN_FLT_DLC_FLT_DLC_HI_MASK 0xFu
#define FLEXCAN_FLT_DLC_FLT_DLC_HI_SHIFT 0u
#define FLEXCAN_FLT_DLC_FLT_DLC_HI_WIDTH 4u
#define FLEXCAN_FLT_DLC_FLT_DLC_HI(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_DLC_FLT_DLC_HI_SHIFT))&FLEXCAN_FLT_DLC_FLT_DLC_HI_MASK)
/* FLT_DLC Reg Mask */
#define FLEXCAN_FLT_DLC_MASK           0x000F000Fu
/* PL1_LO Bit Fields */
#define FLEXCAN_PL1_LO_DATA_BYTE_0_MASK 0xFF000000u
#define FLEXCAN_PL1_LO_DATA_BYTE_0_SHIFT 24u
#define FLEXCAN_PL1_LO_DATA_BYTE_0_WIDTH 8u
#define FLEXCAN_PL1_LO_DATA_BYTE_0(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_LO_DATA_BYTE_0_SHIFT))&FLEXCAN_PL1_LO_DATA_BYTE_0_MASK)
#define FLEXCAN_PL1_LO_DATA_BYTE_1_MASK 0xFF0000u
#define FLEXCAN_PL1_LO_DATA_BYTE_1_SHIFT 16u
#define FLEXCAN_PL1_LO_DATA_BYTE_1_WIDTH 8u
#define FLEXCAN_PL1_LO_DATA_BYTE_1(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_LO_DATA_BYTE_1_SHIFT))&FLEXCAN_PL1_LO_DATA_BYTE_1_MASK)
#define FLEXCAN_PL1_LO_DATA_BYTE_2_MASK 0xFF00u
#define FLEXCAN_PL1_LO_DATA_BYTE_2_SHIFT 8u
#define FLEXCAN_PL1_LO_DATA_BYTE_2_WIDTH 8u
#define FLEXCAN_PL1_LO_DATA_BYTE_2(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_LO_DATA_BYTE_2_SHIFT))&FLEXCAN_PL1_LO_DATA_BYTE_2_MASK)
#define FLEXCAN_PL1_LO_DATA_BYTE_3_MASK 0xFFu
#define FLEXCAN_PL1_LO_DATA_BYTE_3_SHIFT 0u
#define FLEXCAN_PL1_LO_DATA_BYTE_3_WIDTH 8u
#define FLEXCAN_PL1_LO_DATA_BYTE_3(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_LO_DATA_BYTE_3_SHIFT))&FLEXCAN_PL1_LO_DATA_BYTE_3_MASK)
/* PL1_LO Reg Mask */
#define FLEXCAN_PL1_LO_MASK            0xFFFFFFFFu
/* PL1_HI Bit Fields */
#define FLEXCAN_PL1_HI_DATA_BYTE_4_MASK 0xFF000000u
#define FLEXCAN_PL1_HI_DATA_BYTE_4_SHIFT 24u
#define FLEXCAN_PL1_HI_DATA_BYTE_4_WIDTH 8u
#define FLEXCAN_PL1_HI_DATA_BYTE_4(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_HI_DATA_BYTE_4_SHIFT))&FLEXCAN_PL1_HI_DATA_BYTE_4_MASK)
#define FLEXCAN_PL1_HI_DATA_BYTE_5_MASK 0xFF0000u
#define FLEXCAN_PL1_HI_DATA_BYTE_5_SHIFT 16u
#define FLEXCAN_PL1_HI_DATA_BYTE_5_WIDTH 8u
#define FLEXCAN_PL1_HI_DATA_BYTE_5(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_HI_DATA_BYTE_5_SHIFT))&FLEXCAN_PL1_HI_DATA_BYTE_5_MASK)
#define FLEXCAN_PL1_HI_DATA_BYTE_6_MASK 0xFF00u
#define FLEXCAN_PL1_HI_DATA_BYTE_6_SHIFT 8u
#define FLEXCAN_PL1_HI_DATA_BYTE_6_WIDTH 8u
#define FLEXCAN_PL1_HI_DATA_BYTE_6(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_HI_DATA_BYTE_6_SHIFT))&FLEXCAN_PL1_HI_DATA_BYTE_6_MASK)
#define FLEXCAN_PL1_HI_DATA_BYTE_7_MASK 0xFFu
#define FLEXCAN_PL1_HI_DATA_BYTE_7_SHIFT 0u
#define FLEXCAN_PL1_HI_DATA_BYTE_7_WIDTH 8u
#define FLEXCAN_PL1_HI_DATA_BYTE_7(x)  (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL1_HI_DATA_BYTE_7_SHIFT))&FLEXCAN_PL1_HI_DATA_BYTE_7_MASK)
/* PL1_HI Reg Mask */
#define FLEXCAN_PL1_HI_MASK            0xFFFFFFFFu
/* FLT_ID2_IDMASK Bit Fields */
#define FLEXCAN_FLT_ID2_IDMASK_IDE_MSK_MASK 0x40000000u
#define FLEXCAN_FLT_ID2_IDMASK_IDE_MSK_SHIFT 30u
#define FLEXCAN_FLT_ID2_IDMASK_IDE_MSK_WIDTH 1u
#define FLEXCAN_FLT_ID2_IDMASK_IDE_MSK(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_ID2_IDMASK_IDE_MSK_SHIFT))&FLEXCAN_FLT_ID2_IDMASK_IDE_MSK_MASK)
#define FLEXCAN_FLT_ID2_IDMASK_RTR_MSK_MASK 0x20000000u
#define FLEXCAN_FLT_ID2_IDMASK_RTR_MSK_SHIFT 29u
#define FLEXCAN_FLT_ID2_IDMASK_RTR_MSK_WIDTH 1u
#define FLEXCAN_FLT_ID2_IDMASK_RTR_MSK(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_ID2_IDMASK_RTR_MSK_SHIFT))&FLEXCAN_FLT_ID2_IDMASK_RTR_MSK_MASK)
#define FLEXCAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_MASK 0x1FFFFFFFu
#define FLEXCAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_SHIFT 0u
#define FLEXCAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_WIDTH 29u
#define FLEXCAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_SHIFT))&FLEXCAN_FLT_ID2_IDMASK_FLT_ID2_IDMASK_MASK)
/* FLT_ID2_IDMASK Reg Mask */
#define FLEXCAN_FLT_ID2_IDMASK_MASK    0x7FFFFFFFu
/* PL2_PLMASK_LO Bit Fields */
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_0_MASK 0xFF000000u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_0_SHIFT 24u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_0_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_0(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_0_SHIFT))&FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_0_MASK)
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_1_MASK 0xFF0000u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_1_SHIFT 16u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_1_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_1(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_1_SHIFT))&FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_1_MASK)
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_2_MASK 0xFF00u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_2_SHIFT 8u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_2_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_2(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_2_SHIFT))&FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_2_MASK)
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_3_MASK 0xFFu
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_3_SHIFT 0u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_3_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_3(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_3_SHIFT))&FLEXCAN_PL2_PLMASK_LO_DATA_BYTE_3_MASK)
/* PL2_PLMASK_LO Reg Mask */
#define FLEXCAN_PL2_PLMASK_LO_MASK     0xFFFFFFFFu
/* PL2_PLMASK_HI Bit Fields */
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_4_MASK 0xFF000000u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_4_SHIFT 24u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_4_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_4(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_4_SHIFT))&FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_4_MASK)
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_5_MASK 0xFF0000u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_5_SHIFT 16u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_5_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_5(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_5_SHIFT))&FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_5_MASK)
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_6_MASK 0xFF00u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_6_SHIFT 8u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_6_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_6(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_6_SHIFT))&FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_6_MASK)
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_7_MASK 0xFFu
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_7_SHIFT 0u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_7_WIDTH 8u
#define FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_7(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_7_SHIFT))&FLEXCAN_PL2_PLMASK_HI_DATA_BYTE_7_MASK)
/* PL2_PLMASK_HI Reg Mask */
#define FLEXCAN_PL2_PLMASK_HI_MASK     0xFFFFFFFFu
/* WMB_CS Bit Fields */
#define FLEXCAN_WMB_CS_SRR_MASK        0x400000u
#define FLEXCAN_WMB_CS_SRR_SHIFT       22u
#define FLEXCAN_WMB_CS_SRR_WIDTH       1u
#define FLEXCAN_WMB_CS_SRR(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_CS_SRR_SHIFT))&FLEXCAN_WMB_CS_SRR_MASK)
#define FLEXCAN_WMB_CS_IDE_MASK        0x200000u
#define FLEXCAN_WMB_CS_IDE_SHIFT       21u
#define FLEXCAN_WMB_CS_IDE_WIDTH       1u
#define FLEXCAN_WMB_CS_IDE(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_CS_IDE_SHIFT))&FLEXCAN_WMB_CS_IDE_MASK)
#define FLEXCAN_WMB_CS_RTR_MASK        0x100000u
#define FLEXCAN_WMB_CS_RTR_SHIFT       20u
#define FLEXCAN_WMB_CS_RTR_WIDTH       1u
#define FLEXCAN_WMB_CS_RTR(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_CS_RTR_SHIFT))&FLEXCAN_WMB_CS_RTR_MASK)
#define FLEXCAN_WMB_CS_DLC_MASK        0xF0000u
#define FLEXCAN_WMB_CS_DLC_SHIFT       16u
#define FLEXCAN_WMB_CS_DLC_WIDTH       4u
#define FLEXCAN_WMB_CS_DLC(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_CS_DLC_SHIFT))&FLEXCAN_WMB_CS_DLC_MASK)
/* WMB_CS0 Reg Mask */
#define FLEXCAN_WMB_CS_MASK            0x007F0000u
/* WMB_ID Bit Fields */
#define FLEXCAN_WMB_ID_ID_MASK         0x1FFFFFFFu
#define FLEXCAN_WMB_ID_ID_SHIFT        0u
#define FLEXCAN_WMB_ID_ID_WIDTH        29u
#define FLEXCAN_WMB_ID_ID(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_ID_ID_SHIFT))&FLEXCAN_WMB_ID_ID_MASK)
/* WMB_ID0 Reg Mask */
#define FLEXCAN_WMB_ID_MASK            0x1FFFFFFFu
/* WMB_D03_ Bit Fields */
#define FLEXCAN_WMB_D03__DATA_BYTE_0_MASK 0xFF000000u
#define FLEXCAN_WMB_D03__DATA_BYTE_0_SHIFT 24u
#define FLEXCAN_WMB_D03__DATA_BYTE_0_WIDTH 8u
#define FLEXCAN_WMB_D03__DATA_BYTE_0(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D03__DATA_BYTE_0_SHIFT))&FLEXCAN_WMB_D03__DATA_BYTE_0_MASK)
#define FLEXCAN_WMB_D03__DATA_BYTE_1_MASK 0xFF0000u
#define FLEXCAN_WMB_D03__DATA_BYTE_1_SHIFT 16u
#define FLEXCAN_WMB_D03__DATA_BYTE_1_WIDTH 8u
#define FLEXCAN_WMB_D03__DATA_BYTE_1(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D03__DATA_BYTE_1_SHIFT))&FLEXCAN_WMB_D03__DATA_BYTE_1_MASK)
#define FLEXCAN_WMB_D03__DATA_BYTE_2_MASK 0xFF00u
#define FLEXCAN_WMB_D03__DATA_BYTE_2_SHIFT 8u
#define FLEXCAN_WMB_D03__DATA_BYTE_2_WIDTH 8u
#define FLEXCAN_WMB_D03__DATA_BYTE_2(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D03__DATA_BYTE_2_SHIFT))&FLEXCAN_WMB_D03__DATA_BYTE_2_MASK)
#define FLEXCAN_WMB_D03__DATA_BYTE_3_MASK 0xFFu
#define FLEXCAN_WMB_D03__DATA_BYTE_3_SHIFT 0u
#define FLEXCAN_WMB_D03__DATA_BYTE_3_WIDTH 8u
#define FLEXCAN_WMB_D03__DATA_BYTE_3(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D03__DATA_BYTE_3_SHIFT))&FLEXCAN_WMB_D03__DATA_BYTE_3_MASK)
/* WMB_D03_0 Reg Mask */
#define FLEXCAN_WMB_D03__MASK          0xFFFFFFFFu
/* WMB_D47_ Bit Fields */
#define FLEXCAN_WMB_D47__DATA_BYTE_4_MASK 0xFF000000u
#define FLEXCAN_WMB_D47__DATA_BYTE_4_SHIFT 24u
#define FLEXCAN_WMB_D47__DATA_BYTE_4_WIDTH 8u
#define FLEXCAN_WMB_D47__DATA_BYTE_4(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D47__DATA_BYTE_4_SHIFT))&FLEXCAN_WMB_D47__DATA_BYTE_4_MASK)
#define FLEXCAN_WMB_D47__DATA_BYTE_5_MASK 0xFF0000u
#define FLEXCAN_WMB_D47__DATA_BYTE_5_SHIFT 16u
#define FLEXCAN_WMB_D47__DATA_BYTE_5_WIDTH 8u
#define FLEXCAN_WMB_D47__DATA_BYTE_5(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D47__DATA_BYTE_5_SHIFT))&FLEXCAN_WMB_D47__DATA_BYTE_5_MASK)
#define FLEXCAN_WMB_D47__DATA_BYTE_6_MASK 0xFF00u
#define FLEXCAN_WMB_D47__DATA_BYTE_6_SHIFT 8u
#define FLEXCAN_WMB_D47__DATA_BYTE_6_WIDTH 8u
#define FLEXCAN_WMB_D47__DATA_BYTE_6(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D47__DATA_BYTE_6_SHIFT))&FLEXCAN_WMB_D47__DATA_BYTE_6_MASK)
#define FLEXCAN_WMB_D47__DATA_BYTE_7_MASK 0xFFu
#define FLEXCAN_WMB_D47__DATA_BYTE_7_SHIFT 0u
#define FLEXCAN_WMB_D47__DATA_BYTE_7_WIDTH 8u
#define FLEXCAN_WMB_D47__DATA_BYTE_7(x) (((uint32_t)(((uint32_t)(x))<<FLEXCAN_WMB_D47__DATA_BYTE_7_SHIFT))&FLEXCAN_WMB_D47__DATA_BYTE_7_MASK)
/* WMB_D47_0 Reg Mask */
#define FLEXCAN_WMB_D47__MASK          0xFFFFFFFFu
/* EPRS Bit Fields */
#define FLEXCAN_EPRS_EDPRESDIV_MASK    0x3FF0000u
#define FLEXCAN_EPRS_EDPRESDIV_SHIFT   16u
#define FLEXCAN_EPRS_EDPRESDIV_WIDTH   10u
#define FLEXCAN_EPRS_EDPRESDIV(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_EPRS_EDPRESDIV_SHIFT))&FLEXCAN_EPRS_EDPRESDIV_MASK)
#define FLEXCAN_EPRS_ENPRESDIV_MASK    0x3FFu
#define FLEXCAN_EPRS_ENPRESDIV_SHIFT   0u
#define FLEXCAN_EPRS_ENPRESDIV_WIDTH   10u
#define FLEXCAN_EPRS_ENPRESDIV(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_EPRS_ENPRESDIV_SHIFT))&FLEXCAN_EPRS_ENPRESDIV_MASK)
/* EPRS Reg Mask */
#define FLEXCAN_EPRS_MASK              0x03FF03FFu
/* ENCBT Bit Fields */
#define FLEXCAN_ENCBT_NRJW_MASK        0x1FC00000u
#define FLEXCAN_ENCBT_NRJW_SHIFT       22u
#define FLEXCAN_ENCBT_NRJW_WIDTH       7u
#define FLEXCAN_ENCBT_NRJW(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ENCBT_NRJW_SHIFT))&FLEXCAN_ENCBT_NRJW_MASK)
#define FLEXCAN_ENCBT_NTSEG2_MASK      0x7F000u
#define FLEXCAN_ENCBT_NTSEG2_SHIFT     12u
#define FLEXCAN_ENCBT_NTSEG2_WIDTH     7u
#define FLEXCAN_ENCBT_NTSEG2(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ENCBT_NTSEG2_SHIFT))&FLEXCAN_ENCBT_NTSEG2_MASK)
#define FLEXCAN_ENCBT_NTSEG1_MASK      0xFFu
#define FLEXCAN_ENCBT_NTSEG1_SHIFT     0u
#define FLEXCAN_ENCBT_NTSEG1_WIDTH     8u
#define FLEXCAN_ENCBT_NTSEG1(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ENCBT_NTSEG1_SHIFT))&FLEXCAN_ENCBT_NTSEG1_MASK)
/* ENCBT Reg Mask */
#define FLEXCAN_ENCBT_MASK             0x1FC7F0FFu
/* EDCBT Bit Fields */
#define FLEXCAN_EDCBT_DRJW_MASK        0x3C00000u
#define FLEXCAN_EDCBT_DRJW_SHIFT       22u
#define FLEXCAN_EDCBT_DRJW_WIDTH       4u
#define FLEXCAN_EDCBT_DRJW(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_EDCBT_DRJW_SHIFT))&FLEXCAN_EDCBT_DRJW_MASK)
#define FLEXCAN_EDCBT_DTSEG2_MASK      0xF000u
#define FLEXCAN_EDCBT_DTSEG2_SHIFT     12u
#define FLEXCAN_EDCBT_DTSEG2_WIDTH     4u
#define FLEXCAN_EDCBT_DTSEG2(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_EDCBT_DTSEG2_SHIFT))&FLEXCAN_EDCBT_DTSEG2_MASK)
#define FLEXCAN_EDCBT_DTSEG1_MASK      0x1Fu
#define FLEXCAN_EDCBT_DTSEG1_SHIFT     0u
#define FLEXCAN_EDCBT_DTSEG1_WIDTH     5u
#define FLEXCAN_EDCBT_DTSEG1(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_EDCBT_DTSEG1_SHIFT))&FLEXCAN_EDCBT_DTSEG1_MASK)
/* EDCBT Reg Mask */
#define FLEXCAN_EDCBT_MASK             0x03C0F01Fu
/* ETDC Bit Fields */
#define FLEXCAN_ETDC_ETDCEN_MASK       0x80000000u
#define FLEXCAN_ETDC_ETDCEN_SHIFT      31u
#define FLEXCAN_ETDC_ETDCEN_WIDTH      1u
#define FLEXCAN_ETDC_ETDCEN(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ETDC_ETDCEN_SHIFT))&FLEXCAN_ETDC_ETDCEN_MASK)
#define FLEXCAN_ETDC_TDMDIS_MASK       0x40000000u
#define FLEXCAN_ETDC_TDMDIS_SHIFT      30u
#define FLEXCAN_ETDC_TDMDIS_WIDTH      1u
#define FLEXCAN_ETDC_TDMDIS(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ETDC_TDMDIS_SHIFT))&FLEXCAN_ETDC_TDMDIS_MASK)
#define FLEXCAN_ETDC_ETDCOFF_MASK      0x7F0000u
#define FLEXCAN_ETDC_ETDCOFF_SHIFT     16u
#define FLEXCAN_ETDC_ETDCOFF_WIDTH     7u
#define FLEXCAN_ETDC_ETDCOFF(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ETDC_ETDCOFF_SHIFT))&FLEXCAN_ETDC_ETDCOFF_MASK)
#define FLEXCAN_ETDC_ETDCFAIL_MASK     0x8000u
#define FLEXCAN_ETDC_ETDCFAIL_SHIFT    15u
#define FLEXCAN_ETDC_ETDCFAIL_WIDTH    1u
#define FLEXCAN_ETDC_ETDCFAIL(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ETDC_ETDCFAIL_SHIFT))&FLEXCAN_ETDC_ETDCFAIL_MASK)
#define FLEXCAN_ETDC_ETDCVAL_MASK      0xFFu
#define FLEXCAN_ETDC_ETDCVAL_SHIFT     0u
#define FLEXCAN_ETDC_ETDCVAL_WIDTH     8u
#define FLEXCAN_ETDC_ETDCVAL(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ETDC_ETDCVAL_SHIFT))&FLEXCAN_ETDC_ETDCVAL_MASK)
/* ETDC Reg Mask */
#define FLEXCAN_ETDC_MASK              0xC07F80FFu
/* FDCTRL Bit Fields */
#define FLEXCAN_FDCTRL_FDRATE_MASK     0x80000000u
#define FLEXCAN_FDCTRL_FDRATE_SHIFT    31u
#define FLEXCAN_FDCTRL_FDRATE_WIDTH    1u
#define FLEXCAN_FDCTRL_FDRATE(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCTRL_FDRATE_SHIFT))&FLEXCAN_FDCTRL_FDRATE_MASK)
#define FLEXCAN_FDCTRL_MBDSR0_MASK     0x30000u
#define FLEXCAN_FDCTRL_MBDSR0_SHIFT    16u
#define FLEXCAN_FDCTRL_MBDSR0_WIDTH    2u
#define FLEXCAN_FDCTRL_MBDSR0(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCTRL_MBDSR0_SHIFT))&FLEXCAN_FDCTRL_MBDSR0_MASK)
#define FLEXCAN_FDCTRL_TDCEN_MASK      0x8000u
#define FLEXCAN_FDCTRL_TDCEN_SHIFT     15u
#define FLEXCAN_FDCTRL_TDCEN_WIDTH     1u
#define FLEXCAN_FDCTRL_TDCEN(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCTRL_TDCEN_SHIFT))&FLEXCAN_FDCTRL_TDCEN_MASK)
#define FLEXCAN_FDCTRL_TDCFAIL_MASK    0x4000u
#define FLEXCAN_FDCTRL_TDCFAIL_SHIFT   14u
#define FLEXCAN_FDCTRL_TDCFAIL_WIDTH   1u
#define FLEXCAN_FDCTRL_TDCFAIL(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCTRL_TDCFAIL_SHIFT))&FLEXCAN_FDCTRL_TDCFAIL_MASK)
#define FLEXCAN_FDCTRL_TDCOFF_MASK     0x1F00u
#define FLEXCAN_FDCTRL_TDCOFF_SHIFT    8u
#define FLEXCAN_FDCTRL_TDCOFF_WIDTH    5u
#define FLEXCAN_FDCTRL_TDCOFF(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCTRL_TDCOFF_SHIFT))&FLEXCAN_FDCTRL_TDCOFF_MASK)
#define FLEXCAN_FDCTRL_TDCVAL_MASK     0x3Fu
#define FLEXCAN_FDCTRL_TDCVAL_SHIFT    0u
#define FLEXCAN_FDCTRL_TDCVAL_WIDTH    6u
#define FLEXCAN_FDCTRL_TDCVAL(x)       (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCTRL_TDCVAL_SHIFT))&FLEXCAN_FDCTRL_TDCVAL_MASK)
/* FDCTRL Reg Mask */
#define FLEXCAN_FDCTRL_MASK            0x8003DF3Fu
/* FDCBT Bit Fields */
#define FLEXCAN_FDCBT_FPRESDIV_MASK    0x3FF00000u
#define FLEXCAN_FDCBT_FPRESDIV_SHIFT   20u
#define FLEXCAN_FDCBT_FPRESDIV_WIDTH   10u
#define FLEXCAN_FDCBT_FPRESDIV(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCBT_FPRESDIV_SHIFT))&FLEXCAN_FDCBT_FPRESDIV_MASK)
#define FLEXCAN_FDCBT_FRJW_MASK        0x70000u
#define FLEXCAN_FDCBT_FRJW_SHIFT       16u
#define FLEXCAN_FDCBT_FRJW_WIDTH       3u
#define FLEXCAN_FDCBT_FRJW(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCBT_FRJW_SHIFT))&FLEXCAN_FDCBT_FRJW_MASK)
#define FLEXCAN_FDCBT_FPROPSEG_MASK    0x7C00u
#define FLEXCAN_FDCBT_FPROPSEG_SHIFT   10u
#define FLEXCAN_FDCBT_FPROPSEG_WIDTH   5u
#define FLEXCAN_FDCBT_FPROPSEG(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCBT_FPROPSEG_SHIFT))&FLEXCAN_FDCBT_FPROPSEG_MASK)
#define FLEXCAN_FDCBT_FPSEG1_MASK      0xE0u
#define FLEXCAN_FDCBT_FPSEG1_SHIFT     5u
#define FLEXCAN_FDCBT_FPSEG1_WIDTH     3u
#define FLEXCAN_FDCBT_FPSEG1(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCBT_FPSEG1_SHIFT))&FLEXCAN_FDCBT_FPSEG1_MASK)
#define FLEXCAN_FDCBT_FPSEG2_MASK      0x7u
#define FLEXCAN_FDCBT_FPSEG2_SHIFT     0u
#define FLEXCAN_FDCBT_FPSEG2_WIDTH     3u
#define FLEXCAN_FDCBT_FPSEG2(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCBT_FPSEG2_SHIFT))&FLEXCAN_FDCBT_FPSEG2_MASK)
/* FDCBT Reg Mask */
#define FLEXCAN_FDCBT_MASK             0x3FF77CE7u
/* FDCRC Bit Fields */
#define FLEXCAN_FDCRC_FD_MBCRC_MASK    0x7F000000u
#define FLEXCAN_FDCRC_FD_MBCRC_SHIFT   24u
#define FLEXCAN_FDCRC_FD_MBCRC_WIDTH   7u
#define FLEXCAN_FDCRC_FD_MBCRC(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCRC_FD_MBCRC_SHIFT))&FLEXCAN_FDCRC_FD_MBCRC_MASK)
#define FLEXCAN_FDCRC_FD_TXCRC_MASK    0x1FFFFFu
#define FLEXCAN_FDCRC_FD_TXCRC_SHIFT   0u
#define FLEXCAN_FDCRC_FD_TXCRC_WIDTH   21u
#define FLEXCAN_FDCRC_FD_TXCRC(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_FDCRC_FD_TXCRC_SHIFT))&FLEXCAN_FDCRC_FD_TXCRC_MASK)
/* FDCRC Reg Mask */
#define FLEXCAN_FDCRC_MASK             0x7F1FFFFFu
/* ERFCR Bit Fields */
#define FLEXCAN_ERFCR_ERFEN_MASK       0x80000000u
#define FLEXCAN_ERFCR_ERFEN_SHIFT      31u
#define FLEXCAN_ERFCR_ERFEN_WIDTH      1u
#define FLEXCAN_ERFCR_ERFEN(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFCR_ERFEN_SHIFT))&FLEXCAN_ERFCR_ERFEN_MASK)
#define FLEXCAN_ERFCR_DMALW_MASK       0x7C000000u
#define FLEXCAN_ERFCR_DMALW_SHIFT      26u
#define FLEXCAN_ERFCR_DMALW_WIDTH      5u
#define FLEXCAN_ERFCR_DMALW(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFCR_DMALW_SHIFT))&FLEXCAN_ERFCR_DMALW_MASK)
#define FLEXCAN_ERFCR_NEXIF_MASK       0x7F0000u
#define FLEXCAN_ERFCR_NEXIF_SHIFT      16u
#define FLEXCAN_ERFCR_NEXIF_WIDTH      7u
#define FLEXCAN_ERFCR_NEXIF(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFCR_NEXIF_SHIFT))&FLEXCAN_ERFCR_NEXIF_MASK)
#define FLEXCAN_ERFCR_NFE_MASK         0x3F00u
#define FLEXCAN_ERFCR_NFE_SHIFT        8u
#define FLEXCAN_ERFCR_NFE_WIDTH        6u
#define FLEXCAN_ERFCR_NFE(x)           (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFCR_NFE_SHIFT))&FLEXCAN_ERFCR_NFE_MASK)
#define FLEXCAN_ERFCR_ERFWM_MASK       0x1Fu
#define FLEXCAN_ERFCR_ERFWM_SHIFT      0u
#define FLEXCAN_ERFCR_ERFWM_WIDTH      5u
#define FLEXCAN_ERFCR_ERFWM(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFCR_ERFWM_SHIFT))&FLEXCAN_ERFCR_ERFWM_MASK)
/* ERFCR Reg Mask */
#define FLEXCAN_ERFCR_MASK             0xFC7F3F1Fu
/* ERFIER Bit Fields */
#define FLEXCAN_ERFIER_ERFUFWIE_MASK   0x80000000u
#define FLEXCAN_ERFIER_ERFUFWIE_SHIFT  31u
#define FLEXCAN_ERFIER_ERFUFWIE_WIDTH  1u
#define FLEXCAN_ERFIER_ERFUFWIE(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFIER_ERFUFWIE_SHIFT))&FLEXCAN_ERFIER_ERFUFWIE_MASK)
#define FLEXCAN_ERFIER_ERFOVFIE_MASK   0x40000000u
#define FLEXCAN_ERFIER_ERFOVFIE_SHIFT  30u
#define FLEXCAN_ERFIER_ERFOVFIE_WIDTH  1u
#define FLEXCAN_ERFIER_ERFOVFIE(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFIER_ERFOVFIE_SHIFT))&FLEXCAN_ERFIER_ERFOVFIE_MASK)
#define FLEXCAN_ERFIER_ERFWMIIE_MASK   0x20000000u
#define FLEXCAN_ERFIER_ERFWMIIE_SHIFT  29u
#define FLEXCAN_ERFIER_ERFWMIIE_WIDTH  1u
#define FLEXCAN_ERFIER_ERFWMIIE(x)     (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFIER_ERFWMIIE_SHIFT))&FLEXCAN_ERFIER_ERFWMIIE_MASK)
#define FLEXCAN_ERFIER_ERFDAIE_MASK    0x10000000u
#define FLEXCAN_ERFIER_ERFDAIE_SHIFT   28u
#define FLEXCAN_ERFIER_ERFDAIE_WIDTH   1u
#define FLEXCAN_ERFIER_ERFDAIE(x)      (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFIER_ERFDAIE_SHIFT))&FLEXCAN_ERFIER_ERFDAIE_MASK)
/* ERFIER Reg Mask */
#define FLEXCAN_ERFIER_MASK            0xF0000000u
/* ERFSR Bit Fields */
#define FLEXCAN_ERFSR_ERFUFW_MASK      0x80000000u
#define FLEXCAN_ERFSR_ERFUFW_SHIFT     31u
#define FLEXCAN_ERFSR_ERFUFW_WIDTH     1u
#define FLEXCAN_ERFSR_ERFUFW(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFUFW_SHIFT))&FLEXCAN_ERFSR_ERFUFW_MASK)
#define FLEXCAN_ERFSR_ERFOVF_MASK      0x40000000u
#define FLEXCAN_ERFSR_ERFOVF_SHIFT     30u
#define FLEXCAN_ERFSR_ERFOVF_WIDTH     1u
#define FLEXCAN_ERFSR_ERFOVF(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFOVF_SHIFT))&FLEXCAN_ERFSR_ERFOVF_MASK)
#define FLEXCAN_ERFSR_ERFWMI_MASK      0x20000000u
#define FLEXCAN_ERFSR_ERFWMI_SHIFT     29u
#define FLEXCAN_ERFSR_ERFWMI_WIDTH     1u
#define FLEXCAN_ERFSR_ERFWMI(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFWMI_SHIFT))&FLEXCAN_ERFSR_ERFWMI_MASK)
#define FLEXCAN_ERFSR_ERFDA_MASK       0x10000000u
#define FLEXCAN_ERFSR_ERFDA_SHIFT      28u
#define FLEXCAN_ERFSR_ERFDA_WIDTH      1u
#define FLEXCAN_ERFSR_ERFDA(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFDA_SHIFT))&FLEXCAN_ERFSR_ERFDA_MASK)
#define FLEXCAN_ERFSR_ERFCLR_MASK      0x8000000u
#define FLEXCAN_ERFSR_ERFCLR_SHIFT     27u
#define FLEXCAN_ERFSR_ERFCLR_WIDTH     1u
#define FLEXCAN_ERFSR_ERFCLR(x)        (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFCLR_SHIFT))&FLEXCAN_ERFSR_ERFCLR_MASK)
#define FLEXCAN_ERFSR_ERFE_MASK        0x20000u
#define FLEXCAN_ERFSR_ERFE_SHIFT       17u
#define FLEXCAN_ERFSR_ERFE_WIDTH       1u
#define FLEXCAN_ERFSR_ERFE(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFE_SHIFT))&FLEXCAN_ERFSR_ERFE_MASK)
#define FLEXCAN_ERFSR_ERFF_MASK        0x10000u
#define FLEXCAN_ERFSR_ERFF_SHIFT       16u
#define FLEXCAN_ERFSR_ERFF_WIDTH       1u
#define FLEXCAN_ERFSR_ERFF(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFF_SHIFT))&FLEXCAN_ERFSR_ERFF_MASK)
#define FLEXCAN_ERFSR_ERFEL_MASK       0x3Fu
#define FLEXCAN_ERFSR_ERFEL_SHIFT      0u
#define FLEXCAN_ERFSR_ERFEL_WIDTH      6u
#define FLEXCAN_ERFSR_ERFEL(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFSR_ERFEL_SHIFT))&FLEXCAN_ERFSR_ERFEL_MASK)
/* ERFSR Reg Mask */
#define FLEXCAN_ERFSR_MASK             0xF803003Fu
/* ERX_FIFO Bit Fields */
#define FLEXCAN_ERX_FIFO_RX_MASK       0xFFFFFFFFu
#define FLEXCAN_ERX_FIFO_RX_SHIFT      0u
#define FLEXCAN_ERX_FIFO_RX_WIDTH      32u
#define FLEXCAN_ERX_FIFO_RX(x)         (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERX_FIFO_RX_SHIFT))&FLEXCAN_ERX_FIFO_RX_MASK)
/* ERX_FIFO0 Reg Mask */
#define FLEXCAN_ERX_FIFO_MASK          0xFFFFFFFFu
/* ERFFEL Bit Fields */
#define FLEXCAN_ERFFEL_FEL_MASK        0xFFFFFFFFu
#define FLEXCAN_ERFFEL_FEL_SHIFT       0u
#define FLEXCAN_ERFFEL_FEL_WIDTH       32u
#define FLEXCAN_ERFFEL_FEL(x)          (((uint32_t)(((uint32_t)(x))<<FLEXCAN_ERFFEL_FEL_SHIFT))&FLEXCAN_ERFFEL_FEL_MASK)
/* ERFFEL0 Reg Mask */
#define FLEXCAN_ERFFEL_MASK            0xFFFFFFFFu
/**
 * @}
 */ /* end of group FLEXCAN_Register_Masks */
/**
 * @}
 */ /* end of group FLEXCAN_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
