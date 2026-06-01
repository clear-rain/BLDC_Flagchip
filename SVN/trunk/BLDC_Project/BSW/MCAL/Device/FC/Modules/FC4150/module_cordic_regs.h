#ifndef __MODULE_CORDIC_KJO_Ufdi42_REGS_H_
#define __MODULE_CORDIC_KJO_Ufdi42_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* ----------------------------------------------------------------------------
   -- CORDIC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CORDIC_Peripheral_Access_Layer CORDIC Peripheral Access Layer
 * @{
 */

/** CORDIC - Size of Registers Arrays */

/** CORDIC - Register Layout Typedef */

typedef struct {

  __IO uint32_t CTRL                          ; /* Control Register, offset: 0x0 */
       uint8_t  RESERVED_0[12];
  __IO uint32_t X_INPUT                       ; /* X-axis Input Data, offset: 0x10 */
  __IO uint32_t Y_INPUT                       ; /* Y-axis Input Data, offset: 0x14 */
  __IO uint32_t Z_INPUT                       ; /* Z-axis Input Data, offset: 0x18 */
       uint8_t  RESERVED_1[4];
  __IO uint32_t STAT                          ; /* State Register, offset: 0x20 */
  __I  uint32_t X_OUTPUT                      ; /* X-axis Output Data, offset: 0x24 */
  __I  uint32_t Y_OUTPUT                      ; /* Y-axis Output Data, offset: 0x28 */
  __I  uint32_t Z_OUTPUT                      ; /* Z-axis Output Data, offset: 0x2C */

} CORDIC_Type, *CORDIC_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- CORDIC Register Masks
   ---------------------------------------------------------------------------- */

/**
 * @addtogroup CORDIC_Register_Masks CORDIC Register Masks
 * @{
 */

/* CTRL Bit Fields */
#define CORDIC_CTRL_IE_MASK            0x80000000u
#define CORDIC_CTRL_IE_SHIFT           31u
#define CORDIC_CTRL_IE_WIDTH           1u
#define CORDIC_CTRL_IE(x)              (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_IE_SHIFT))&CORDIC_CTRL_IE_MASK)
#define CORDIC_CTRL_ITER_MASK          0x30u
#define CORDIC_CTRL_ITER_SHIFT         4u
#define CORDIC_CTRL_ITER_WIDTH         2u
#define CORDIC_CTRL_ITER(x)            (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_ITER_SHIFT))&CORDIC_CTRL_ITER_MASK)
#define CORDIC_CTRL_OS_MASK            0xEu
#define CORDIC_CTRL_OS_SHIFT           1u
#define CORDIC_CTRL_OS_WIDTH           3u
#define CORDIC_CTRL_OS(x)              (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_OS_SHIFT))&CORDIC_CTRL_OS_MASK)
#define CORDIC_CTRL_MODE_MASK          0x1u
#define CORDIC_CTRL_MODE_SHIFT         0u
#define CORDIC_CTRL_MODE_WIDTH         1u
#define CORDIC_CTRL_MODE(x)            (((uint32_t)(((uint32_t)(x))<<CORDIC_CTRL_MODE_SHIFT))&CORDIC_CTRL_MODE_MASK)
/* CTRL Reg Mask */
#define CORDIC_CTRL_MASK               0x8000003Fu

/* X_INPUT Bit Fields */
#define CORDIC_X_INPUT_DATA_MASK       0xFFFFFFFFu
#define CORDIC_X_INPUT_DATA_SHIFT      0u
#define CORDIC_X_INPUT_DATA_WIDTH      32u
#define CORDIC_X_INPUT_DATA(x)         (((uint32_t)(((uint32_t)(x))<<CORDIC_X_INPUT_DATA_SHIFT))&CORDIC_X_INPUT_DATA_MASK)
/* X_INPUT Reg Mask */
#define CORDIC_X_INPUT_MASK            0xFFFFFFFFu

/* Y_INPUT Bit Fields */
#define CORDIC_Y_INPUT_DATA_MASK       0xFFFFFFFFu
#define CORDIC_Y_INPUT_DATA_SHIFT      0u
#define CORDIC_Y_INPUT_DATA_WIDTH      32u
#define CORDIC_Y_INPUT_DATA(x)         (((uint32_t)(((uint32_t)(x))<<CORDIC_Y_INPUT_DATA_SHIFT))&CORDIC_Y_INPUT_DATA_MASK)
/* Y_INPUT Reg Mask */
#define CORDIC_Y_INPUT_MASK            0xFFFFFFFFu

/* Z_INPUT Bit Fields */
#define CORDIC_Z_INPUT_DATA_MASK       0xFFFFFFFFu
#define CORDIC_Z_INPUT_DATA_SHIFT      0u
#define CORDIC_Z_INPUT_DATA_WIDTH      32u
#define CORDIC_Z_INPUT_DATA(x)         (((uint32_t)(((uint32_t)(x))<<CORDIC_Z_INPUT_DATA_SHIFT))&CORDIC_Z_INPUT_DATA_MASK)
/* Z_INPUT Reg Mask */
#define CORDIC_Z_INPUT_MASK            0xFFFFFFFFu

/* STAT Bit Fields */
#define CORDIC_STAT_DONE_MASK          0x1u
#define CORDIC_STAT_DONE_SHIFT         0u
#define CORDIC_STAT_DONE_WIDTH         1u
#define CORDIC_STAT_DONE(x)            (((uint32_t)(((uint32_t)(x))<<CORDIC_STAT_DONE_SHIFT))&CORDIC_STAT_DONE_MASK)
/* STAT Reg Mask */
#define CORDIC_STAT_MASK               0x00000001u

/* X_OUTPUT Bit Fields */
#define CORDIC_X_OUTPUT_DATA_MASK      0xFFFFFFFFu
#define CORDIC_X_OUTPUT_DATA_SHIFT     0u
#define CORDIC_X_OUTPUT_DATA_WIDTH     32u
#define CORDIC_X_OUTPUT_DATA(x)        (((uint32_t)(((uint32_t)(x))<<CORDIC_X_OUTPUT_DATA_SHIFT))&CORDIC_X_OUTPUT_DATA_MASK)
/* X_OUTPUT Reg Mask */
#define CORDIC_X_OUTPUT_MASK           0xFFFFFFFFu

/* Y_OUTPUT Bit Fields */
#define CORDIC_Y_OUTPUT_DATA_MASK      0xFFFFFFFFu
#define CORDIC_Y_OUTPUT_DATA_SHIFT     0u
#define CORDIC_Y_OUTPUT_DATA_WIDTH     32u
#define CORDIC_Y_OUTPUT_DATA(x)        (((uint32_t)(((uint32_t)(x))<<CORDIC_Y_OUTPUT_DATA_SHIFT))&CORDIC_Y_OUTPUT_DATA_MASK)
/* Y_OUTPUT Reg Mask */
#define CORDIC_Y_OUTPUT_MASK           0xFFFFFFFFu

/* Z_OUTPUT Bit Fields */
#define CORDIC_Z_OUTPUT_DATA_MASK      0xFFFFFFFFu
#define CORDIC_Z_OUTPUT_DATA_SHIFT     0u
#define CORDIC_Z_OUTPUT_DATA_WIDTH     32u
#define CORDIC_Z_OUTPUT_DATA(x)        (((uint32_t)(((uint32_t)(x))<<CORDIC_Z_OUTPUT_DATA_SHIFT))&CORDIC_Z_OUTPUT_DATA_MASK)
/* Z_OUTPUT Reg Mask */
#define CORDIC_Z_OUTPUT_MASK           0xFFFFFFFFu


/**
 * @}
 */ /* end of group CORDIC_Register_Masks */

/**
 * @}
 */ /* end of group CORDIC_Peripheral_Access_Layer */

#ifdef __cplusplus
}
#endif
#endif
