#ifndef _MODULE_PCC_KJO_Ufdi9_REGS_H_
#define _MODULE_PCC_KJO_Ufdi9_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- PCC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup PCC_Peripheral_Access_Layer PCC Peripheral Access Layer
 * @{
 */
/** PCC - Size of Registers Arrays */
/** PCC - Register Layout Typedef */
typedef struct {
       uint8_t  RESERVED_0[132];
  __IO uint32_t PCC_DMA_MUX                   ; /* DMA MUX Clock Control Register, offset: 0x84 */
       uint8_t  RESERVED_1[16];
  __IO uint32_t PCC_FTU3                      ; /* FTU3 Clock Control Register, offset: 0x98 */
  __IO uint32_t PCC_ADC1                      ; /* ADC1 Clock Control Register, offset: 0x9C */
       uint8_t  RESERVED_2[16];
  __IO uint32_t PCC_FCSPI0                    ; /* FCSPI0 Clock Control Register, offset: 0xB0 */
  __IO uint32_t PCC_FCSPI1                    ; /* FCSPI1 Clock Control Register, offset: 0xB4 */
  __IO uint32_t PCC_FCSPI2                    ; /* FCSPI2 Clock Control Register, offset: 0xB8 */
  __IO uint32_t PCC_FCSPI3                    ; /* FCSPI3 Clock Control Register, offset: 0xBC */
       uint8_t  RESERVED_3[4];
  __IO uint32_t PCC_PTIMER1                   ; /* PTIMER1 Clock Control Register, offset: 0xC4 */
  __IO uint32_t PCC_CRC                       ; /* CRC Clock Control Register, offset: 0xC8 */
       uint8_t  RESERVED_4[12];
  __IO uint32_t PCC_PTIMER0                   ; /* PTIMER0 Clock Control Register, offset: 0xD8 */
  __IO uint32_t PCC_FCPIT                     ; /* FCPIT Clock Control Register, offset: 0xDC */
  __IO uint32_t PCC_FTU0                      ; /* FTU0 Clock Control Register, offset: 0xE0 */
  __IO uint32_t PCC_FTU1                      ; /* FTU1 Clock Control Register, offset: 0xE4 */
  __IO uint32_t PCC_FTU2                      ; /* FTU2 Clock Control Register, offset: 0xE8 */
  __IO uint32_t PCC_ADC0                      ; /* ADC0 Clock Control Register, offset: 0xEC */
       uint8_t  RESERVED_5[4];
  __IO uint32_t PCC_RTC                       ; /* RTC Clock Control Register, offset: 0xF4 */
  __IO uint32_t PCC_CMU0                      ; /* CMU0 Clock Control Register, offset: 0xF8 */
  __IO uint32_t PCC_CMU1                      ; /* CMU1 Clock Control Register, offset: 0xFC */
  __IO uint32_t PCC_AONTIMER                  ; /* AONTIMER0 Clock Control Register, offset: 0x100 */
       uint8_t  RESERVED_6[4];
  __IO uint32_t PCC_TSTMP0                    ; /* TSTMP0 Clock Control Register, offset: 0x108 */
  __IO uint32_t PCC_CMU2                      ; /* CMU2 Clock Control Register, offset: 0x10C */
  __IO uint32_t PCC_CMU3                      ; /* CMU3 Clock Control Register, offset: 0x110 */
       uint8_t  RESERVED_7[16];
  __IO uint32_t PCC_PORTA                     ; /* Port A Clock Control Register, offset: 0x124 */
  __IO uint32_t PCC_PORTB                     ; /* Port B Clock Control Register, offset: 0x128 */
  __IO uint32_t PCC_PORTC                     ; /* Port C Clock Control Register, offset: 0x12C */
  __IO uint32_t PCC_PORTD                     ; /* Port D Clock Control Register, offset: 0x130 */
  __IO uint32_t PCC_PORTE                     ; /* Port E Clock Control Register, offset: 0x134 */
       uint8_t  RESERVED_8[4];
  __IO uint32_t PCC_WKU                       ; /* WKU Clock Control Register, offset: 0x13C */
       uint8_t  RESERVED_9[16];
  __IO uint32_t PCC_I2S0                      ; /* I2S0 Clock Control Register, offset: 0x150 */
  __IO uint32_t PCC_I2S1                      ; /* I2S1 Clock Control Register, offset: 0x154 */
  __IO uint32_t PCC_FTU6                      ; /* FTU6 Clock Control Register, offset: 0x158 */
  __IO uint32_t PCC_FTU7                      ; /* FTU7 Clock Control Register, offset: 0x15C */
       uint8_t  RESERVED_10[12];
  __IO uint32_t PCC_FCUART3                   ; /* FCUART3 Clock Control Register, offset: 0x16C */
  __IO uint32_t PCC_FCUART4                   ; /* FCUART4 Clock Control Register, offset: 0x170 */
  __IO uint32_t PCC_FCUART5                   ; /* FCUART5 Clock Control Register, offset: 0x174 */
       uint8_t  RESERVED_11[12];
  __IO uint32_t PCC_FWM                       ; /* FWM Clock Control Register, offset: 0x184 */
       uint8_t  RESERVED_12[16];
  __IO uint32_t PCC_FCIIC0                    ; /* FCIIC0 Clock Control Register, offset: 0x198 */
  __IO uint32_t PCC_FCIIC1                    ; /* FCIIC1 Clock Control Register, offset: 0x19C */
       uint8_t  RESERVED_13[8];
  __IO uint32_t PCC_FCUART0                   ; /* FCUART0 Clock Control Register, offset: 0x1A8 */
  __IO uint32_t PCC_FCUART1                   ; /* FCUART1 Clock Control Register, offset: 0x1AC */
  __IO uint32_t PCC_FCUART2                   ; /* FCUART2 Clock Control Register, offset: 0x1B0 */
       uint8_t  RESERVED_14[4];
  __IO uint32_t PCC_FTU4                      ; /* FTU4 Clock Control Register, offset: 0x1B8 */
  __IO uint32_t PCC_FTU5                      ; /* FTU5 Clock Control Register, offset: 0x1BC */
  __IO uint32_t PCC_LU0                       ; /* LU0 Clock Control Register, offset: 0x1C0 */
       uint8_t  RESERVED_15[8];
  __IO uint32_t PCC_CMP0                      ; /* CMP0 Clock Control Register, offset: 0x1CC */
  __IO uint32_t PCC_CMP1                      ; /* CMP1 Clock Control Register, offset: 0x1D0 */
  __IO uint32_t PCC_CMP2                      ; /* CMP2 Clock Control Register, offset: 0x1D4 */
  __IO uint32_t PCC_OSPI                      ; /* OctalSPI Clock Control Register, offset: 0x1D8 */
       uint8_t  RESERVED_16[4];
  __IO uint32_t PCC_ENET                      ; /* ENET Clock Control Register, offset: 0x1E0 */
       uint8_t  RESERVED_17[8];
  __IO uint32_t PCC_TMU0                      ; /* TMU0 Clock Control Register, offset: 0x1EC */
  __IO uint32_t PCC_TSTMP1                    ; /* TSTMP1 Clock Control Register, offset: 0x1F0 */
       uint8_t  RESERVED_18[12];
  __IO uint32_t PCC_FLEXCAN0                  ; /* FLEXCAN0 Clock Control Register, offset: 0x200 */
       uint8_t  RESERVED_19[12];
  __IO uint32_t PCC_FLEXCAN1                  ; /* FLEXCAN1 Clock Control Register, offset: 0x210 */
       uint8_t  RESERVED_20[12];
  __IO uint32_t PCC_FLEXCAN2                  ; /* FLEXCAN2 Clock Control Register, offset: 0x220 */
       uint8_t  RESERVED_21[12];
  __IO uint32_t PCC_FLEXCAN3                  ; /* FLEXCAN3 Clock Control Register, offset: 0x230 */
       uint8_t  RESERVED_22[12];
  __IO uint32_t PCC_FLEXCAN4                  ; /* FLEXCAN4 Clock Control Register, offset: 0x240 */
       uint8_t  RESERVED_23[12];
  __IO uint32_t PCC_FLEXCAN5                  ; /* FLEXCAN5 Clock Control Register, offset: 0x250 */
       uint8_t  RESERVED_24[12];
  __IO uint32_t PCC_HSM                       ; /* HSM Clock Control Register, offset: 0x260 */
} PCC_Type, *PCC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- PCC Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup PCC_Register_Masks PCC Register Masks
 * @{
 */
 
/* DMA_MUX Bit Fields */
#define PCC_DMA_MUX_CGC_MASK           0x40000000u
#define PCC_DMA_MUX_CGC_SHIFT          30u
#define PCC_DMA_MUX_CGC_WIDTH          1u
#define PCC_DMA_MUX_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_DMA_MUX_CGC_SHIFT))&PCC_DMA_MUX_CGC_MASK)
/* DMA_MUX Reg Mask */
#define PCC_DMA_MUX_MASK               0x40000000u
/* FTU3 Bit Fields */
#define PCC_FTU3_CGC_MASK              0x40000000u
#define PCC_FTU3_CGC_SHIFT             30u
#define PCC_FTU3_CGC_WIDTH             1u
#define PCC_FTU3_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU3_CGC_SHIFT))&PCC_FTU3_CGC_MASK)
#define PCC_FTU3_SEL_MASK              0x7000000u
#define PCC_FTU3_SEL_SHIFT             24u
#define PCC_FTU3_SEL_WIDTH             3u
#define PCC_FTU3_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU3_SEL_SHIFT))&PCC_FTU3_SEL_MASK)
/* FTU3 Reg Mask */
#define PCC_FTU3_MASK                  0x47000000u
/* ADC1 Bit Fields */
#define PCC_ADC1_CGC_MASK              0x40000000u
#define PCC_ADC1_CGC_SHIFT             30u
#define PCC_ADC1_CGC_WIDTH             1u
#define PCC_ADC1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC1_CGC_SHIFT))&PCC_ADC1_CGC_MASK)
#define PCC_ADC1_SEL_MASK              0x7000000u
#define PCC_ADC1_SEL_SHIFT             24u
#define PCC_ADC1_SEL_WIDTH             3u
#define PCC_ADC1_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC1_SEL_SHIFT))&PCC_ADC1_SEL_MASK)
#define PCC_ADC1_DIV_MASK              0x7u
#define PCC_ADC1_DIV_SHIFT             0u
#define PCC_ADC1_DIV_WIDTH             3u
#define PCC_ADC1_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC1_DIV_SHIFT))&PCC_ADC1_DIV_MASK)
/* ADC1 Reg Mask */
#define PCC_ADC1_MASK                  0x47000007u
/* FCSPI0 Bit Fields */
#define PCC_FCSPI0_CGC_MASK            0x40000000u
#define PCC_FCSPI0_CGC_SHIFT           30u
#define PCC_FCSPI0_CGC_WIDTH           1u
#define PCC_FCSPI0_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI0_CGC_SHIFT))&PCC_FCSPI0_CGC_MASK)
#define PCC_FCSPI0_SEL_MASK            0x7000000u
#define PCC_FCSPI0_SEL_SHIFT           24u
#define PCC_FCSPI0_SEL_WIDTH           3u
#define PCC_FCSPI0_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI0_SEL_SHIFT))&PCC_FCSPI0_SEL_MASK)
/* FCSPI0 Reg Mask */
#define PCC_FCSPI0_MASK                0x47000000u
/* FCSPI1 Bit Fields */
#define PCC_FCSPI1_CGC_MASK            0x40000000u
#define PCC_FCSPI1_CGC_SHIFT           30u
#define PCC_FCSPI1_CGC_WIDTH           1u
#define PCC_FCSPI1_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI1_CGC_SHIFT))&PCC_FCSPI1_CGC_MASK)
#define PCC_FCSPI1_SEL_MASK            0x7000000u
#define PCC_FCSPI1_SEL_SHIFT           24u
#define PCC_FCSPI1_SEL_WIDTH           3u
#define PCC_FCSPI1_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI1_SEL_SHIFT))&PCC_FCSPI1_SEL_MASK)
/* FCSPI1 Reg Mask */
#define PCC_FCSPI1_MASK                0x47000000u
/* FCSPI2 Bit Fields */
#define PCC_FCSPI2_CGC_MASK            0x40000000u
#define PCC_FCSPI2_CGC_SHIFT           30u
#define PCC_FCSPI2_CGC_WIDTH           1u
#define PCC_FCSPI2_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI2_CGC_SHIFT))&PCC_FCSPI2_CGC_MASK)
#define PCC_FCSPI2_SEL_MASK            0x7000000u
#define PCC_FCSPI2_SEL_SHIFT           24u
#define PCC_FCSPI2_SEL_WIDTH           3u
#define PCC_FCSPI2_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI2_SEL_SHIFT))&PCC_FCSPI2_SEL_MASK)
/* FCSPI2 Reg Mask */
#define PCC_FCSPI2_MASK                0x47000000u
/* FCSPI3 Bit Fields */
#define PCC_FCSPI3_CGC_MASK            0x40000000u
#define PCC_FCSPI3_CGC_SHIFT           30u
#define PCC_FCSPI3_CGC_WIDTH           1u
#define PCC_FCSPI3_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI3_CGC_SHIFT))&PCC_FCSPI3_CGC_MASK)
#define PCC_FCSPI3_SEL_MASK            0x7000000u
#define PCC_FCSPI3_SEL_SHIFT           24u
#define PCC_FCSPI3_SEL_WIDTH           3u
#define PCC_FCSPI3_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCSPI3_SEL_SHIFT))&PCC_FCSPI3_SEL_MASK)
/* FCSPI3 Reg Mask */
#define PCC_FCSPI3_MASK                0x47000000u
/* PTIMER1 Bit Fields */
#define PCC_PTIMER1_CGC_MASK           0x40000000u
#define PCC_PTIMER1_CGC_SHIFT          30u
#define PCC_PTIMER1_CGC_WIDTH          1u
#define PCC_PTIMER1_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_PTIMER1_CGC_SHIFT))&PCC_PTIMER1_CGC_MASK)
/* PTIMER1 Reg Mask */
#define PCC_PTIMER1_MASK               0x40000000u
/* CRC Bit Fields */
#define PCC_CRC_CGC_MASK               0x40000000u
#define PCC_CRC_CGC_SHIFT              30u
#define PCC_CRC_CGC_WIDTH              1u
#define PCC_CRC_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_CRC_CGC_SHIFT))&PCC_CRC_CGC_MASK)
/* CRC Reg Mask */
#define PCC_CRC_MASK                   0x40000000u
/* PTIMER0 Bit Fields */
#define PCC_PTIMER0_CGC_MASK           0x40000000u
#define PCC_PTIMER0_CGC_SHIFT          30u
#define PCC_PTIMER0_CGC_WIDTH          1u
#define PCC_PTIMER0_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_PTIMER0_CGC_SHIFT))&PCC_PTIMER0_CGC_MASK)
/* PTIMER0 Reg Mask */
#define PCC_PTIMER0_MASK               0x40000000u
/* FCPIT Bit Fields */
#define PCC_FCPIT_CGC_MASK             0x40000000u
#define PCC_FCPIT_CGC_SHIFT            30u
#define PCC_FCPIT_CGC_WIDTH            1u
#define PCC_FCPIT_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_FCPIT_CGC_SHIFT))&PCC_FCPIT_CGC_MASK)
#define PCC_FCPIT_SEL_MASK             0x7000000u
#define PCC_FCPIT_SEL_SHIFT            24u
#define PCC_FCPIT_SEL_WIDTH            3u
#define PCC_FCPIT_SEL(x)               (((uint32_t)(((uint32_t)(x))<<PCC_FCPIT_SEL_SHIFT))&PCC_FCPIT_SEL_MASK)
/* FCPIT Reg Mask */
#define PCC_FCPIT_MASK                 0x47000000u
/* FTU0 Bit Fields */
#define PCC_FTU0_CGC_MASK              0x40000000u
#define PCC_FTU0_CGC_SHIFT             30u
#define PCC_FTU0_CGC_WIDTH             1u
#define PCC_FTU0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU0_CGC_SHIFT))&PCC_FTU0_CGC_MASK)
#define PCC_FTU0_SEL_MASK              0x7000000u
#define PCC_FTU0_SEL_SHIFT             24u
#define PCC_FTU0_SEL_WIDTH             3u
#define PCC_FTU0_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU0_SEL_SHIFT))&PCC_FTU0_SEL_MASK)
/* FTU0 Reg Mask */
#define PCC_FTU0_MASK                  0x47000000u
/* FTU1 Bit Fields */
#define PCC_FTU1_CGC_MASK              0x40000000u
#define PCC_FTU1_CGC_SHIFT             30u
#define PCC_FTU1_CGC_WIDTH             1u
#define PCC_FTU1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU1_CGC_SHIFT))&PCC_FTU1_CGC_MASK)
#define PCC_FTU1_SEL_MASK              0x7000000u
#define PCC_FTU1_SEL_SHIFT             24u
#define PCC_FTU1_SEL_WIDTH             3u
#define PCC_FTU1_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU1_SEL_SHIFT))&PCC_FTU1_SEL_MASK)
/* FTU1 Reg Mask */
#define PCC_FTU1_MASK                  0x47000000u
/* FTU2 Bit Fields */
#define PCC_FTU2_CGC_MASK              0x40000000u
#define PCC_FTU2_CGC_SHIFT             30u
#define PCC_FTU2_CGC_WIDTH             1u
#define PCC_FTU2_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU2_CGC_SHIFT))&PCC_FTU2_CGC_MASK)
#define PCC_FTU2_SEL_MASK              0x7000000u
#define PCC_FTU2_SEL_SHIFT             24u
#define PCC_FTU2_SEL_WIDTH             3u
#define PCC_FTU2_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU2_SEL_SHIFT))&PCC_FTU2_SEL_MASK)
/* FTU2 Reg Mask */
#define PCC_FTU2_MASK                  0x47000000u
/* ADC0 Bit Fields */
#define PCC_ADC0_CGC_MASK              0x40000000u
#define PCC_ADC0_CGC_SHIFT             30u
#define PCC_ADC0_CGC_WIDTH             1u
#define PCC_ADC0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC0_CGC_SHIFT))&PCC_ADC0_CGC_MASK)
#define PCC_ADC0_SEL_MASK              0x7000000u
#define PCC_ADC0_SEL_SHIFT             24u
#define PCC_ADC0_SEL_WIDTH             3u
#define PCC_ADC0_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC0_SEL_SHIFT))&PCC_ADC0_SEL_MASK)
#define PCC_ADC0_DIV_MASK              0x7u
#define PCC_ADC0_DIV_SHIFT             0u
#define PCC_ADC0_DIV_WIDTH             3u
#define PCC_ADC0_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ADC0_DIV_SHIFT))&PCC_ADC0_DIV_MASK)
/* ADC0 Reg Mask */
#define PCC_ADC0_MASK                  0x47000007u
/* RTC Bit Fields */
#define PCC_RTC_CGC_MASK               0x40000000u
#define PCC_RTC_CGC_SHIFT              30u
#define PCC_RTC_CGC_WIDTH              1u
#define PCC_RTC_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_RTC_CGC_SHIFT))&PCC_RTC_CGC_MASK)
/* RTC Reg Mask */
#define PCC_RTC_MASK                   0x40000000u
/* CMU0 Bit Fields */
#define PCC_CMU0_CGC_MASK              0x40000000u
#define PCC_CMU0_CGC_SHIFT             30u
#define PCC_CMU0_CGC_WIDTH             1u
#define PCC_CMU0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU0_CGC_SHIFT))&PCC_CMU0_CGC_MASK)
/* CMU0 Reg Mask */
#define PCC_CMU0_MASK                  0x40000000u
/* CMU1 Bit Fields */
#define PCC_CMU1_CGC_MASK              0x40000000u
#define PCC_CMU1_CGC_SHIFT             30u
#define PCC_CMU1_CGC_WIDTH             1u
#define PCC_CMU1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU1_CGC_SHIFT))&PCC_CMU1_CGC_MASK)
/* CMU1 Reg Mask */
#define PCC_CMU1_MASK                  0x40000000u
/* AONTIMER Bit Fields */
#define PCC_AONTIMER_CGC_MASK          0x40000000u
#define PCC_AONTIMER_CGC_SHIFT         30u
#define PCC_AONTIMER_CGC_WIDTH         1u
#define PCC_AONTIMER_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_AONTIMER_CGC_SHIFT))&PCC_AONTIMER_CGC_MASK)
#define PCC_AONTIMER_SEL_MASK          0x7000000u
#define PCC_AONTIMER_SEL_SHIFT         24u
#define PCC_AONTIMER_SEL_WIDTH         3u
#define PCC_AONTIMER_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_AONTIMER_SEL_SHIFT))&PCC_AONTIMER_SEL_MASK)
#define PCC_AONTIMER_DIV_MASK          0x7u
#define PCC_AONTIMER_DIV_SHIFT         0u
#define PCC_AONTIMER_DIV_WIDTH         3u
#define PCC_AONTIMER_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_AONTIMER_DIV_SHIFT))&PCC_AONTIMER_DIV_MASK)
/* AONTIMER Reg Mask */
#define PCC_AONTIMER_MASK              0x47000007u
/* TSTMP0 Bit Fields */
#define PCC_TSTMP0_CGC_MASK            0x40000000u
#define PCC_TSTMP0_CGC_SHIFT           30u
#define PCC_TSTMP0_CGC_WIDTH           1u
#define PCC_TSTMP0_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_TSTMP0_CGC_SHIFT))&PCC_TSTMP0_CGC_MASK)
/* TSTMP0 Reg Mask */
#define PCC_TSTMP0_MASK                0x40000000u
/* CMU2 Bit Fields */
#define PCC_CMU2_CGC_MASK              0x40000000u
#define PCC_CMU2_CGC_SHIFT             30u
#define PCC_CMU2_CGC_WIDTH             1u
#define PCC_CMU2_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU2_CGC_SHIFT))&PCC_CMU2_CGC_MASK)
/* CMU2 Reg Mask */
#define PCC_CMU2_MASK                  0x40000000u
/* CMU3 Bit Fields */
#define PCC_CMU3_CGC_MASK              0x40000000u
#define PCC_CMU3_CGC_SHIFT             30u
#define PCC_CMU3_CGC_WIDTH             1u
#define PCC_CMU3_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMU3_CGC_SHIFT))&PCC_CMU3_CGC_MASK)
/* CMU3 Reg Mask */
#define PCC_CMU3_MASK                  0x40000000u
/* PORTA Bit Fields */
#define PCC_PORTA_CGC_MASK             0x40000000u
#define PCC_PORTA_CGC_SHIFT            30u
#define PCC_PORTA_CGC_WIDTH            1u
#define PCC_PORTA_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_PORTA_CGC_SHIFT))&PCC_PORTA_CGC_MASK)
/* PORTA Reg Mask */
#define PCC_PORTA_MASK                 0x40000000u
/* PORTB Bit Fields */
#define PCC_PORTB_CGC_MASK             0x40000000u
#define PCC_PORTB_CGC_SHIFT            30u
#define PCC_PORTB_CGC_WIDTH            1u
#define PCC_PORTB_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_PORTB_CGC_SHIFT))&PCC_PORTB_CGC_MASK)
/* PORTB Reg Mask */
#define PCC_PORTB_MASK                 0x40000000u
/* PORTC Bit Fields */
#define PCC_PORTC_CGC_MASK             0x40000000u
#define PCC_PORTC_CGC_SHIFT            30u
#define PCC_PORTC_CGC_WIDTH            1u
#define PCC_PORTC_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_PORTC_CGC_SHIFT))&PCC_PORTC_CGC_MASK)
/* PORTC Reg Mask */
#define PCC_PORTC_MASK                 0x40000000u
/* PORTD Bit Fields */
#define PCC_PORTD_CGC_MASK             0x40000000u
#define PCC_PORTD_CGC_SHIFT            30u
#define PCC_PORTD_CGC_WIDTH            1u
#define PCC_PORTD_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_PORTD_CGC_SHIFT))&PCC_PORTD_CGC_MASK)
/* PORTD Reg Mask */
#define PCC_PORTD_MASK                 0x40000000u
/* PORTE Bit Fields */
#define PCC_PORTE_CGC_MASK             0x40000000u
#define PCC_PORTE_CGC_SHIFT            30u
#define PCC_PORTE_CGC_WIDTH            1u
#define PCC_PORTE_CGC(x)               (((uint32_t)(((uint32_t)(x))<<PCC_PORTE_CGC_SHIFT))&PCC_PORTE_CGC_MASK)
/* PORTE Reg Mask */
#define PCC_PORTE_MASK                 0x40000000u
/* WKU Bit Fields */
#define PCC_WKU_CGC_MASK               0x40000000u
#define PCC_WKU_CGC_SHIFT              30u
#define PCC_WKU_CGC_WIDTH              1u
#define PCC_WKU_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_WKU_CGC_SHIFT))&PCC_WKU_CGC_MASK)
/* WKU Reg Mask */
#define PCC_WKU_MASK                   0x40000000u
/* I2S0 Bit Fields */
#define PCC_I2S0_CGC_MASK              0x40000000u
#define PCC_I2S0_CGC_SHIFT             30u
#define PCC_I2S0_CGC_WIDTH             1u
#define PCC_I2S0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_I2S0_CGC_SHIFT))&PCC_I2S0_CGC_MASK)
#define PCC_I2S0_SEL_MASK              0x7000000u
#define PCC_I2S0_SEL_SHIFT             24u
#define PCC_I2S0_SEL_WIDTH             3u
#define PCC_I2S0_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_I2S0_SEL_SHIFT))&PCC_I2S0_SEL_MASK)
#define PCC_I2S0_DIV_MASK              0x7u
#define PCC_I2S0_DIV_SHIFT             0u
#define PCC_I2S0_DIV_WIDTH             3u
#define PCC_I2S0_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_I2S0_DIV_SHIFT))&PCC_I2S0_DIV_MASK)
/* I2S0 Reg Mask */
#define PCC_I2S0_MASK                  0x47000007u
/* I2S1 Bit Fields */
#define PCC_I2S1_CGC_MASK              0x40000000u
#define PCC_I2S1_CGC_SHIFT             30u
#define PCC_I2S1_CGC_WIDTH             1u
#define PCC_I2S1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_I2S1_CGC_SHIFT))&PCC_I2S1_CGC_MASK)
#define PCC_I2S1_SEL_MASK              0x7000000u
#define PCC_I2S1_SEL_SHIFT             24u
#define PCC_I2S1_SEL_WIDTH             3u
#define PCC_I2S1_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_I2S1_SEL_SHIFT))&PCC_I2S1_SEL_MASK)
#define PCC_I2S1_DIV_MASK              0x7u
#define PCC_I2S1_DIV_SHIFT             0u
#define PCC_I2S1_DIV_WIDTH             3u
#define PCC_I2S1_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_I2S1_DIV_SHIFT))&PCC_I2S1_DIV_MASK)
/* I2S1 Reg Mask */
#define PCC_I2S1_MASK                  0x47000007u
/* FTU6 Bit Fields */
#define PCC_FTU6_CGC_MASK              0x40000000u
#define PCC_FTU6_CGC_SHIFT             30u
#define PCC_FTU6_CGC_WIDTH             1u
#define PCC_FTU6_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU6_CGC_SHIFT))&PCC_FTU6_CGC_MASK)
#define PCC_FTU6_SEL_MASK              0x7000000u
#define PCC_FTU6_SEL_SHIFT             24u
#define PCC_FTU6_SEL_WIDTH             3u
#define PCC_FTU6_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU6_SEL_SHIFT))&PCC_FTU6_SEL_MASK)
/* FTU6 Reg Mask */
#define PCC_FTU6_MASK                  0x47000000u
/* FTU7 Bit Fields */
#define PCC_FTU7_CGC_MASK              0x40000000u
#define PCC_FTU7_CGC_SHIFT             30u
#define PCC_FTU7_CGC_WIDTH             1u
#define PCC_FTU7_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU7_CGC_SHIFT))&PCC_FTU7_CGC_MASK)
#define PCC_FTU7_SEL_MASK              0x7000000u
#define PCC_FTU7_SEL_SHIFT             24u
#define PCC_FTU7_SEL_WIDTH             3u
#define PCC_FTU7_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU7_SEL_SHIFT))&PCC_FTU7_SEL_MASK)
/* FTU7 Reg Mask */
#define PCC_FTU7_MASK                  0x47000000u
/* FCUART3 Bit Fields */
#define PCC_FCUART3_CGC_MASK           0x40000000u
#define PCC_FCUART3_CGC_SHIFT          30u
#define PCC_FCUART3_CGC_WIDTH          1u
#define PCC_FCUART3_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART3_CGC_SHIFT))&PCC_FCUART3_CGC_MASK)
#define PCC_FCUART3_SEL_MASK           0x7000000u
#define PCC_FCUART3_SEL_SHIFT          24u
#define PCC_FCUART3_SEL_WIDTH          3u
#define PCC_FCUART3_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART3_SEL_SHIFT))&PCC_FCUART3_SEL_MASK)
/* FCUART3 Reg Mask */
#define PCC_FCUART3_MASK               0x47000000u
/* FCUART4 Bit Fields */
#define PCC_FCUART4_CGC_MASK           0x40000000u
#define PCC_FCUART4_CGC_SHIFT          30u
#define PCC_FCUART4_CGC_WIDTH          1u
#define PCC_FCUART4_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART4_CGC_SHIFT))&PCC_FCUART4_CGC_MASK)
#define PCC_FCUART4_SEL_MASK           0x7000000u
#define PCC_FCUART4_SEL_SHIFT          24u
#define PCC_FCUART4_SEL_WIDTH          3u
#define PCC_FCUART4_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART4_SEL_SHIFT))&PCC_FCUART4_SEL_MASK)
/* FCUART4 Reg Mask */
#define PCC_FCUART4_MASK               0x47000000u
/* FCUART5 Bit Fields */
#define PCC_FCUART5_CGC_MASK           0x40000000u
#define PCC_FCUART5_CGC_SHIFT          30u
#define PCC_FCUART5_CGC_WIDTH          1u
#define PCC_FCUART5_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART5_CGC_SHIFT))&PCC_FCUART5_CGC_MASK)
#define PCC_FCUART5_SEL_MASK           0x7000000u
#define PCC_FCUART5_SEL_SHIFT          24u
#define PCC_FCUART5_SEL_WIDTH          3u
#define PCC_FCUART5_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART5_SEL_SHIFT))&PCC_FCUART5_SEL_MASK)
/* FCUART5 Reg Mask */
#define PCC_FCUART5_MASK               0x47000000u
/* FWM Bit Fields */
#define PCC_FWM_CGC_MASK               0x40000000u
#define PCC_FWM_CGC_SHIFT              30u
#define PCC_FWM_CGC_WIDTH              1u
#define PCC_FWM_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_FWM_CGC_SHIFT))&PCC_FWM_CGC_MASK)
/* FWM Reg Mask */
#define PCC_FWM_MASK                   0x40000000u
/* FCIIC0 Bit Fields */
#define PCC_FCIIC0_CGC_MASK            0x40000000u
#define PCC_FCIIC0_CGC_SHIFT           30u
#define PCC_FCIIC0_CGC_WIDTH           1u
#define PCC_FCIIC0_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC0_CGC_SHIFT))&PCC_FCIIC0_CGC_MASK)
#define PCC_FCIIC0_SEL_MASK            0x7000000u
#define PCC_FCIIC0_SEL_SHIFT           24u
#define PCC_FCIIC0_SEL_WIDTH           3u
#define PCC_FCIIC0_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC0_SEL_SHIFT))&PCC_FCIIC0_SEL_MASK)
/* FCIIC0 Reg Mask */
#define PCC_FCIIC0_MASK                0x47000000u
/* FCIIC1 Bit Fields */
#define PCC_FCIIC1_CGC_MASK            0x40000000u
#define PCC_FCIIC1_CGC_SHIFT           30u
#define PCC_FCIIC1_CGC_WIDTH           1u
#define PCC_FCIIC1_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC1_CGC_SHIFT))&PCC_FCIIC1_CGC_MASK)
#define PCC_FCIIC1_SEL_MASK            0x7000000u
#define PCC_FCIIC1_SEL_SHIFT           24u
#define PCC_FCIIC1_SEL_WIDTH           3u
#define PCC_FCIIC1_SEL(x)              (((uint32_t)(((uint32_t)(x))<<PCC_FCIIC1_SEL_SHIFT))&PCC_FCIIC1_SEL_MASK)
/* FCIIC1 Reg Mask */
#define PCC_FCIIC1_MASK                0x47000000u
/* FCUART0 Bit Fields */
#define PCC_FCUART0_CGC_MASK           0x40000000u
#define PCC_FCUART0_CGC_SHIFT          30u
#define PCC_FCUART0_CGC_WIDTH          1u
#define PCC_FCUART0_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART0_CGC_SHIFT))&PCC_FCUART0_CGC_MASK)
#define PCC_FCUART0_SEL_MASK           0x7000000u
#define PCC_FCUART0_SEL_SHIFT          24u
#define PCC_FCUART0_SEL_WIDTH          3u
#define PCC_FCUART0_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART0_SEL_SHIFT))&PCC_FCUART0_SEL_MASK)
/* FCUART0 Reg Mask */
#define PCC_FCUART0_MASK               0x47000000u
/* FCUART1 Bit Fields */
#define PCC_FCUART1_CGC_MASK           0x40000000u
#define PCC_FCUART1_CGC_SHIFT          30u
#define PCC_FCUART1_CGC_WIDTH          1u
#define PCC_FCUART1_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART1_CGC_SHIFT))&PCC_FCUART1_CGC_MASK)
#define PCC_FCUART1_SEL_MASK           0x7000000u
#define PCC_FCUART1_SEL_SHIFT          24u
#define PCC_FCUART1_SEL_WIDTH          3u
#define PCC_FCUART1_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART1_SEL_SHIFT))&PCC_FCUART1_SEL_MASK)
/* FCUART1 Reg Mask */
#define PCC_FCUART1_MASK               0x47000000u
/* FCUART2 Bit Fields */
#define PCC_FCUART2_CGC_MASK           0x40000000u
#define PCC_FCUART2_CGC_SHIFT          30u
#define PCC_FCUART2_CGC_WIDTH          1u
#define PCC_FCUART2_CGC(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART2_CGC_SHIFT))&PCC_FCUART2_CGC_MASK)
#define PCC_FCUART2_SEL_MASK           0x7000000u
#define PCC_FCUART2_SEL_SHIFT          24u
#define PCC_FCUART2_SEL_WIDTH          3u
#define PCC_FCUART2_SEL(x)             (((uint32_t)(((uint32_t)(x))<<PCC_FCUART2_SEL_SHIFT))&PCC_FCUART2_SEL_MASK)
/* FCUART2 Reg Mask */
#define PCC_FCUART2_MASK               0x47000000u
/* FTU4 Bit Fields */
#define PCC_FTU4_CGC_MASK              0x40000000u
#define PCC_FTU4_CGC_SHIFT             30u
#define PCC_FTU4_CGC_WIDTH             1u
#define PCC_FTU4_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU4_CGC_SHIFT))&PCC_FTU4_CGC_MASK)
#define PCC_FTU4_SEL_MASK              0x7000000u
#define PCC_FTU4_SEL_SHIFT             24u
#define PCC_FTU4_SEL_WIDTH             3u
#define PCC_FTU4_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU4_SEL_SHIFT))&PCC_FTU4_SEL_MASK)
/* FTU4 Reg Mask */
#define PCC_FTU4_MASK                  0x47000000u
/* FTU5 Bit Fields */
#define PCC_FTU5_CGC_MASK              0x40000000u
#define PCC_FTU5_CGC_SHIFT             30u
#define PCC_FTU5_CGC_WIDTH             1u
#define PCC_FTU5_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU5_CGC_SHIFT))&PCC_FTU5_CGC_MASK)
#define PCC_FTU5_SEL_MASK              0x7000000u
#define PCC_FTU5_SEL_SHIFT             24u
#define PCC_FTU5_SEL_WIDTH             3u
#define PCC_FTU5_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_FTU5_SEL_SHIFT))&PCC_FTU5_SEL_MASK)
/* FTU5 Reg Mask */
#define PCC_FTU5_MASK                  0x47000000u
/* LU0 Bit Fields */
#define PCC_LU0_CGC_MASK               0x40000000u
#define PCC_LU0_CGC_SHIFT              30u
#define PCC_LU0_CGC_WIDTH              1u
#define PCC_LU0_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_LU0_CGC_SHIFT))&PCC_LU0_CGC_MASK)
/* LU0 Reg Mask */
#define PCC_LU0_MASK                   0x40000000u
/* CMP0 Bit Fields */
#define PCC_CMP0_CGC_MASK              0x40000000u
#define PCC_CMP0_CGC_SHIFT             30u
#define PCC_CMP0_CGC_WIDTH             1u
#define PCC_CMP0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMP0_CGC_SHIFT))&PCC_CMP0_CGC_MASK)
/* CMP0 Reg Mask */
#define PCC_CMP0_MASK                  0x40000000u
/* CMP1 Bit Fields */
#define PCC_CMP1_CGC_MASK              0x40000000u
#define PCC_CMP1_CGC_SHIFT             30u
#define PCC_CMP1_CGC_WIDTH             1u
#define PCC_CMP1_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMP1_CGC_SHIFT))&PCC_CMP1_CGC_MASK)
/* CMP1 Reg Mask */
#define PCC_CMP1_MASK                  0x40000000u
/* CMP2 Bit Fields */
#define PCC_CMP2_CGC_MASK              0x40000000u
#define PCC_CMP2_CGC_SHIFT             30u
#define PCC_CMP2_CGC_WIDTH             1u
#define PCC_CMP2_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_CMP2_CGC_SHIFT))&PCC_CMP2_CGC_MASK)
/* CMP2 Reg Mask */
#define PCC_CMP2_MASK                  0x40000000u
/* OSPI Bit Fields */
#define PCC_OSPI_CGC_MASK              0x40000000u
#define PCC_OSPI_CGC_SHIFT             30u
#define PCC_OSPI_CGC_WIDTH             1u
#define PCC_OSPI_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_OSPI_CGC_SHIFT))&PCC_OSPI_CGC_MASK)
/* OSPI Reg Mask */
#define PCC_OSPI_MASK                  0x40000000u
/* ENET Bit Fields */
#define PCC_ENET_CGC_MASK              0x40000000u
#define PCC_ENET_CGC_SHIFT             30u
#define PCC_ENET_CGC_WIDTH             1u
#define PCC_ENET_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ENET_CGC_SHIFT))&PCC_ENET_CGC_MASK)
#define PCC_ENET_SEL_MASK              0x7000000u
#define PCC_ENET_SEL_SHIFT             24u
#define PCC_ENET_SEL_WIDTH             3u
#define PCC_ENET_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ENET_SEL_SHIFT))&PCC_ENET_SEL_MASK)
#define PCC_ENET_DIV_MASK              0x7u
#define PCC_ENET_DIV_SHIFT             0u
#define PCC_ENET_DIV_WIDTH             3u
#define PCC_ENET_DIV(x)                (((uint32_t)(((uint32_t)(x))<<PCC_ENET_DIV_SHIFT))&PCC_ENET_DIV_MASK)
/* ENET Reg Mask */
#define PCC_ENET_MASK                  0x47000007u
/* TMU0 Bit Fields */
#define PCC_TMU0_CGC_MASK              0x40000000u
#define PCC_TMU0_CGC_SHIFT             30u
#define PCC_TMU0_CGC_WIDTH             1u
#define PCC_TMU0_CGC(x)                (((uint32_t)(((uint32_t)(x))<<PCC_TMU0_CGC_SHIFT))&PCC_TMU0_CGC_MASK)
#define PCC_TMU0_SEL_MASK              0x7000000u
#define PCC_TMU0_SEL_SHIFT             24u
#define PCC_TMU0_SEL_WIDTH             3u
#define PCC_TMU0_SEL(x)                (((uint32_t)(((uint32_t)(x))<<PCC_TMU0_SEL_SHIFT))&PCC_TMU0_SEL_MASK)
/* TMU0 Reg Mask */
#define PCC_TMU0_MASK                  0x47000000u
/* TSTMP1 Bit Fields */
#define PCC_TSTMP1_CGC_MASK            0x40000000u
#define PCC_TSTMP1_CGC_SHIFT           30u
#define PCC_TSTMP1_CGC_WIDTH           1u
#define PCC_TSTMP1_CGC(x)              (((uint32_t)(((uint32_t)(x))<<PCC_TSTMP1_CGC_SHIFT))&PCC_TSTMP1_CGC_MASK)
/* TSTMP1 Reg Mask */
#define PCC_TSTMP1_MASK                0x40000000u
/* FLEXCAN0 Bit Fields */
#define PCC_FLEXCAN0_CGC_MASK          0x40000000u
#define PCC_FLEXCAN0_CGC_SHIFT         30u
#define PCC_FLEXCAN0_CGC_WIDTH         1u
#define PCC_FLEXCAN0_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN0_CGC_SHIFT))&PCC_FLEXCAN0_CGC_MASK)
#define PCC_FLEXCAN0_SEL_MASK          0x7000000u
#define PCC_FLEXCAN0_SEL_SHIFT         24u
#define PCC_FLEXCAN0_SEL_WIDTH         3u
#define PCC_FLEXCAN0_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN0_SEL_SHIFT))&PCC_FLEXCAN0_SEL_MASK)
#define PCC_FLEXCAN0_DIV_MASK          0x7u
#define PCC_FLEXCAN0_DIV_SHIFT         0u
#define PCC_FLEXCAN0_DIV_WIDTH         3u
#define PCC_FLEXCAN0_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN0_DIV_SHIFT))&PCC_FLEXCAN0_DIV_MASK)
/* FLEXCAN0 Reg Mask */
#define PCC_FLEXCAN0_MASK              0x47000007u
/* FLEXCAN1 Bit Fields */
#define PCC_FLEXCAN1_CGC_MASK          0x40000000u
#define PCC_FLEXCAN1_CGC_SHIFT         30u
#define PCC_FLEXCAN1_CGC_WIDTH         1u
#define PCC_FLEXCAN1_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN1_CGC_SHIFT))&PCC_FLEXCAN1_CGC_MASK)
#define PCC_FLEXCAN1_SEL_MASK          0x7000000u
#define PCC_FLEXCAN1_SEL_SHIFT         24u
#define PCC_FLEXCAN1_SEL_WIDTH         3u
#define PCC_FLEXCAN1_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN1_SEL_SHIFT))&PCC_FLEXCAN1_SEL_MASK)
#define PCC_FLEXCAN1_DIV_MASK          0x7u
#define PCC_FLEXCAN1_DIV_SHIFT         0u
#define PCC_FLEXCAN1_DIV_WIDTH         3u
#define PCC_FLEXCAN1_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN1_DIV_SHIFT))&PCC_FLEXCAN1_DIV_MASK)
/* FLEXCAN1 Reg Mask */
#define PCC_FLEXCAN1_MASK              0x47000007u
/* FLEXCAN2 Bit Fields */
#define PCC_FLEXCAN2_CGC_MASK          0x40000000u
#define PCC_FLEXCAN2_CGC_SHIFT         30u
#define PCC_FLEXCAN2_CGC_WIDTH         1u
#define PCC_FLEXCAN2_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN2_CGC_SHIFT))&PCC_FLEXCAN2_CGC_MASK)
#define PCC_FLEXCAN2_SEL_MASK          0x7000000u
#define PCC_FLEXCAN2_SEL_SHIFT         24u
#define PCC_FLEXCAN2_SEL_WIDTH         3u
#define PCC_FLEXCAN2_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN2_SEL_SHIFT))&PCC_FLEXCAN2_SEL_MASK)
#define PCC_FLEXCAN2_DIV_MASK          0x7u
#define PCC_FLEXCAN2_DIV_SHIFT         0u
#define PCC_FLEXCAN2_DIV_WIDTH         3u
#define PCC_FLEXCAN2_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN2_DIV_SHIFT))&PCC_FLEXCAN2_DIV_MASK)
/* FLEXCAN2 Reg Mask */
#define PCC_FLEXCAN2_MASK              0x47000007u
/* FLEXCAN3 Bit Fields */
#define PCC_FLEXCAN3_CGC_MASK          0x40000000u
#define PCC_FLEXCAN3_CGC_SHIFT         30u
#define PCC_FLEXCAN3_CGC_WIDTH         1u
#define PCC_FLEXCAN3_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN3_CGC_SHIFT))&PCC_FLEXCAN3_CGC_MASK)
#define PCC_FLEXCAN3_SEL_MASK          0x7000000u
#define PCC_FLEXCAN3_SEL_SHIFT         24u
#define PCC_FLEXCAN3_SEL_WIDTH         3u
#define PCC_FLEXCAN3_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN3_SEL_SHIFT))&PCC_FLEXCAN3_SEL_MASK)
#define PCC_FLEXCAN3_DIV_MASK          0x7u
#define PCC_FLEXCAN3_DIV_SHIFT         0u
#define PCC_FLEXCAN3_DIV_WIDTH         3u
#define PCC_FLEXCAN3_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN3_DIV_SHIFT))&PCC_FLEXCAN3_DIV_MASK)
/* FLEXCAN3 Reg Mask */
#define PCC_FLEXCAN3_MASK              0x47000007u
/* FLEXCAN4 Bit Fields */
#define PCC_FLEXCAN4_CGC_MASK          0x40000000u
#define PCC_FLEXCAN4_CGC_SHIFT         30u
#define PCC_FLEXCAN4_CGC_WIDTH         1u
#define PCC_FLEXCAN4_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN4_CGC_SHIFT))&PCC_FLEXCAN4_CGC_MASK)
#define PCC_FLEXCAN4_SEL_MASK          0x7000000u
#define PCC_FLEXCAN4_SEL_SHIFT         24u
#define PCC_FLEXCAN4_SEL_WIDTH         3u
#define PCC_FLEXCAN4_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN4_SEL_SHIFT))&PCC_FLEXCAN4_SEL_MASK)
#define PCC_FLEXCAN4_DIV_MASK          0x7u
#define PCC_FLEXCAN4_DIV_SHIFT         0u
#define PCC_FLEXCAN4_DIV_WIDTH         3u
#define PCC_FLEXCAN4_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN4_DIV_SHIFT))&PCC_FLEXCAN4_DIV_MASK)
/* FLEXCAN4 Reg Mask */
#define PCC_FLEXCAN4_MASK              0x47000007u
/* FLEXCAN5 Bit Fields */
#define PCC_FLEXCAN5_CGC_MASK          0x40000000u
#define PCC_FLEXCAN5_CGC_SHIFT         30u
#define PCC_FLEXCAN5_CGC_WIDTH         1u
#define PCC_FLEXCAN5_CGC(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN5_CGC_SHIFT))&PCC_FLEXCAN5_CGC_MASK)
#define PCC_FLEXCAN5_SEL_MASK          0x7000000u
#define PCC_FLEXCAN5_SEL_SHIFT         24u
#define PCC_FLEXCAN5_SEL_WIDTH         3u
#define PCC_FLEXCAN5_SEL(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN5_SEL_SHIFT))&PCC_FLEXCAN5_SEL_MASK)
#define PCC_FLEXCAN5_DIV_MASK          0x7u
#define PCC_FLEXCAN5_DIV_SHIFT         0u
#define PCC_FLEXCAN5_DIV_WIDTH         3u
#define PCC_FLEXCAN5_DIV(x)            (((uint32_t)(((uint32_t)(x))<<PCC_FLEXCAN5_DIV_SHIFT))&PCC_FLEXCAN5_DIV_MASK)
/* FLEXCAN5 Reg Mask */
#define PCC_FLEXCAN5_MASK              0x47000007u
/* HSM Bit Fields */
#define PCC_HSM_CGC_MASK               0x40000000u
#define PCC_HSM_CGC_SHIFT              30u
#define PCC_HSM_CGC_WIDTH              1u
#define PCC_HSM_CGC(x)                 (((uint32_t)(((uint32_t)(x))<<PCC_HSM_CGC_SHIFT))&PCC_HSM_CGC_MASK)
/* HSM Reg Mask */
#define PCC_HSM_MASK                   0x40000000u
/**
 * @}
 */ /* end of group PCC_Register_Masks */
/**
 * @}
 */ /* end of group PCC_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
