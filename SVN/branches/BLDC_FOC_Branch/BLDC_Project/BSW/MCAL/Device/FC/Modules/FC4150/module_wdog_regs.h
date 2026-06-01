#ifndef _MODULE_WDOG_KJO_Ufdi28_REGS_H_
#define _MODULE_WDOG_KJO_Ufdi28_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif
/* ----------------------------------------------------------------------------
   -- WDOG Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup WDOG_Peripheral_Access_Layer WDOG Peripheral Access Layer
 * @{
 */
/** WDOG - Size of Registers Arrays */
/** WDOG - Register Layout Typedef */
typedef struct {
  __IO uint32_t CS                            ; /* Watchdog Control and Status Register, offset: 0x0 */
  __IO uint32_t COUNTER                       ; /* Watchdog Counter Register, offset: 0x4 */
  __IO uint32_t TIMEOUT                       ; /* Watchdog Timeout Value Register, offset: 0x8 */
  __IO uint32_t WINDOW                        ; /* Watchdog Window Register, offset: 0xC */
} WDOG_Type, *WDOG_MemMapPtr;

/* ----------------------------------------------------------------------------
   -- WDOG Register Masks
   ---------------------------------------------------------------------------- */
/**
 * @addtogroup WDOG_Register_Masks WDOG Register Masks
 * @{
 */
 
/* CS Bit Fields */
#define WDOG_CS_DLY_CNT_MSB_MASK       0x30000u
#define WDOG_CS_DLY_CNT_MSB_SHIFT      16u
#define WDOG_CS_DLY_CNT_MSB_WIDTH      2u
#define WDOG_CS_DLY_CNT_MSB(x)         (((uint32_t)(((uint32_t)(x))<<WDOG_CS_DLY_CNT_MSB_SHIFT))&WDOG_CS_DLY_CNT_MSB_MASK)
#define WDOG_CS_WIN_MASK               0x8000u
#define WDOG_CS_WIN_SHIFT              15u
#define WDOG_CS_WIN_WIDTH              1u
#define WDOG_CS_WIN(x)                 (((uint32_t)(((uint32_t)(x))<<WDOG_CS_WIN_SHIFT))&WDOG_CS_WIN_MASK)
#define WDOG_CS_FLAG_MASK              0x4000u
#define WDOG_CS_FLAG_SHIFT             14u
#define WDOG_CS_FLAG_WIDTH             1u
#define WDOG_CS_FLAG(x)                (((uint32_t)(((uint32_t)(x))<<WDOG_CS_FLAG_SHIFT))&WDOG_CS_FLAG_MASK)
#define WDOG_CS_PRESCALER_MASK         0x1000u
#define WDOG_CS_PRESCALER_SHIFT        12u
#define WDOG_CS_PRESCALER_WIDTH        1u
#define WDOG_CS_PRESCALER(x)           (((uint32_t)(((uint32_t)(x))<<WDOG_CS_PRESCALER_SHIFT))&WDOG_CS_PRESCALER_MASK)
#define WDOG_CS_ULK_STAT_MASK          0x800u
#define WDOG_CS_ULK_STAT_SHIFT         11u
#define WDOG_CS_ULK_STAT_WIDTH         1u
#define WDOG_CS_ULK_STAT(x)            (((uint32_t)(((uint32_t)(x))<<WDOG_CS_ULK_STAT_SHIFT))&WDOG_CS_ULK_STAT_MASK)
#define WDOG_CS_RECFG_STAT_MASK        0x400u
#define WDOG_CS_RECFG_STAT_SHIFT       10u
#define WDOG_CS_RECFG_STAT_WIDTH       1u
#define WDOG_CS_RECFG_STAT(x)          (((uint32_t)(((uint32_t)(x))<<WDOG_CS_RECFG_STAT_SHIFT))&WDOG_CS_RECFG_STAT_MASK)
#define WDOG_CS_CLK_SEL_MASK           0x300u
#define WDOG_CS_CLK_SEL_SHIFT          8u
#define WDOG_CS_CLK_SEL_WIDTH          2u
#define WDOG_CS_CLK_SEL(x)             (((uint32_t)(((uint32_t)(x))<<WDOG_CS_CLK_SEL_SHIFT))&WDOG_CS_CLK_SEL_MASK)
#define WDOG_CS_ENABLE_MASK            0x80u
#define WDOG_CS_ENABLE_SHIFT           7u
#define WDOG_CS_ENABLE_WIDTH           1u
#define WDOG_CS_ENABLE(x)              (((uint32_t)(((uint32_t)(x))<<WDOG_CS_ENABLE_SHIFT))&WDOG_CS_ENABLE_MASK)
#define WDOG_CS_INT_MASK               0x40u
#define WDOG_CS_INT_SHIFT              6u
#define WDOG_CS_INT_WIDTH              1u
#define WDOG_CS_INT(x)                 (((uint32_t)(((uint32_t)(x))<<WDOG_CS_INT_SHIFT))&WDOG_CS_INT_MASK)
#define WDOG_CS_UPDATE_MASK            0x20u
#define WDOG_CS_UPDATE_SHIFT           5u
#define WDOG_CS_UPDATE_WIDTH           1u
#define WDOG_CS_UPDATE(x)              (((uint32_t)(((uint32_t)(x))<<WDOG_CS_UPDATE_SHIFT))&WDOG_CS_UPDATE_MASK)
#define WDOG_CS_TST_MASK               0x18u
#define WDOG_CS_TST_SHIFT              3u
#define WDOG_CS_TST_WIDTH              2u
#define WDOG_CS_TST(x)                 (((uint32_t)(((uint32_t)(x))<<WDOG_CS_TST_SHIFT))&WDOG_CS_TST_MASK)
#define WDOG_CS_DBG_MASK               0x4u
#define WDOG_CS_DBG_SHIFT              2u
#define WDOG_CS_DBG_WIDTH              1u
#define WDOG_CS_DBG(x)                 (((uint32_t)(((uint32_t)(x))<<WDOG_CS_DBG_SHIFT))&WDOG_CS_DBG_MASK)
#define WDOG_CS_WAIT_MASK              0x2u
#define WDOG_CS_WAIT_SHIFT             1u
#define WDOG_CS_WAIT_WIDTH             1u
#define WDOG_CS_WAIT(x)                (((uint32_t)(((uint32_t)(x))<<WDOG_CS_WAIT_SHIFT))&WDOG_CS_WAIT_MASK)
#define WDOG_CS_STOP_MASK              0x1u
#define WDOG_CS_STOP_SHIFT             0u
#define WDOG_CS_STOP_WIDTH             1u
#define WDOG_CS_STOP(x)                (((uint32_t)(((uint32_t)(x))<<WDOG_CS_STOP_SHIFT))&WDOG_CS_STOP_MASK)
/* CS Reg Mask */
#define WDOG_CS_MASK                   0x0000DFFFu
/* COUNTER Bit Fields */
#define WDOG_COUNTER_CNTH_MASK         0xFF00u
#define WDOG_COUNTER_CNTH_SHIFT        8u
#define WDOG_COUNTER_CNTH_WIDTH        8u
#define WDOG_COUNTER_CNTH(x)           (((uint32_t)(((uint32_t)(x))<<WDOG_COUNTER_CNTH_SHIFT))&WDOG_COUNTER_CNTH_MASK)
#define WDOG_COUNTER_CNTL_MASK         0xFFu
#define WDOG_COUNTER_CNTL_SHIFT        0u
#define WDOG_COUNTER_CNTL_WIDTH        8u
#define WDOG_COUNTER_CNTL(x)           (((uint32_t)(((uint32_t)(x))<<WDOG_COUNTER_CNTL_SHIFT))&WDOG_COUNTER_CNTL_MASK)
/* COUNTER Reg Mask */
#define WDOG_COUNTER_MASK              0x0000FFFFu
/* TIMEOUT Bit Fields */
#define WDOG_TIMEOUT_TIMEOUT_VALH_MASK 0xFF00u
#define WDOG_TIMEOUT_TIMEOUT_VALH_SHIFT 8u
#define WDOG_TIMEOUT_TIMEOUT_VALH_WIDTH 8u
#define WDOG_TIMEOUT_TIMEOUT_VALH(x)   (((uint32_t)(((uint32_t)(x))<<WDOG_TIMEOUT_TIMEOUT_VALH_SHIFT))&WDOG_TIMEOUT_TIMEOUT_VALH_MASK)
#define WDOG_TIMEOUT_TIMEOUT_VALL_MASK 0xFFu
#define WDOG_TIMEOUT_TIMEOUT_VALL_SHIFT 0u
#define WDOG_TIMEOUT_TIMEOUT_VALL_WIDTH 8u
#define WDOG_TIMEOUT_TIMEOUT_VALL(x)   (((uint32_t)(((uint32_t)(x))<<WDOG_TIMEOUT_TIMEOUT_VALL_SHIFT))&WDOG_TIMEOUT_TIMEOUT_VALL_MASK)
/* TIMEOUT Reg Mask */
#define WDOG_TIMEOUT_MASK              0x0000FFFFu
/* WINDOW Bit Fields */
#define WDOG_WINDOW_WINDOW_HIGH_MASK   0xFF00u
#define WDOG_WINDOW_WINDOW_HIGH_SHIFT  8u
#define WDOG_WINDOW_WINDOW_HIGH_WIDTH  8u
#define WDOG_WINDOW_WINDOW_HIGH(x)     (((uint32_t)(((uint32_t)(x))<<WDOG_WINDOW_WINDOW_HIGH_SHIFT))&WDOG_WINDOW_WINDOW_HIGH_MASK)
#define WDOG_WINDOW_WINDOW_LOW_MASK    0xFFu
#define WDOG_WINDOW_WINDOW_LOW_SHIFT   0u
#define WDOG_WINDOW_WINDOW_LOW_WIDTH   8u
#define WDOG_WINDOW_WINDOW_LOW(x)      (((uint32_t)(((uint32_t)(x))<<WDOG_WINDOW_WINDOW_LOW_SHIFT))&WDOG_WINDOW_WINDOW_LOW_MASK)
/* WINDOW Reg Mask */
#define WDOG_WINDOW_MASK               0x0000FFFFu
/**
 * @}
 */ /* end of group WDOG_Register_Masks */
/**
 * @}
 */ /* end of group WDOG_Peripheral_Access_Layer */
 
#ifdef __cplusplus
}
#endif
#endif
