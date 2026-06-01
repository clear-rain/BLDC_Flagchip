#ifndef _MODULE_FARC_KJO_Ufdi35_REGS_H_
#define _MODULE_FARC_KJO_Ufdi35_REGS_H_
#ifdef __cplusplus
 extern "C" {
#endif


/* ----------------------------------------------------------------------------

   -- FARC Peripheral Access Layer

   ---------------------------------------------------------------------------- */



/**

 * @addtogroup FARC_Peripheral_Access_Layer FARC Peripheral Access Layer

 * @{

 */



/** FARC - Size of Registers Arrays */



/** FARC - Register Layout Typedef */



typedef struct {



  __I  uint32_t LRBAR                         ; /* Logical Region Base Address Register, offset: 0x0 */

  __IO uint32_t PRBAR                         ; /* Physical Region Base Address Register, offset: 0x4 */

  __IO uint32_t LRSR                          ; /* Logical Region Size Register, offset: 0x8 */



} FARC_Type, *FARC_MemMapPtr;



/** Number of instances of the FARC module. */

#define FARC_INSTANCE_COUNT                      (1u)



/* FARC - Peripheral instance base addresses */

/** Peripheral FARC base address */

#define FARC_BASE                                (0x40011000u)

/** Peripheral FARC base pointer */

#define FARC                                     ((FARC_Type *)FARC_BASE)

/** Array initializer of FARC peripheral base addresses */

#define FARC_BASE_ADDRS                          {FARC_BASE}

/** Array initializer of FARC peripheral base pointers */

#define FARC_BASE_PTRS                           {FARC}

// need fill by yourself

///** Number of interrupt vector arrays for the FARC module. */

//#define FARC_IRQS_ARR_COUNT                       (1u)

///** Number of interrupt channels for the FARC module. */

//#define FARC_IRQS_CH_COUNT                        (1u)

///** Interrupt vectors for the FARC peripheral type */

//#define FARC_IRQS                                {FARC_IRQn}





/* ----------------------------------------------------------------------------

   -- FARC Register Masks

   ---------------------------------------------------------------------------- */



/**

 * @addtogroup FARC_Register_Masks FARC Register Masks

 * @{

 */



/* LRBAR Bit Fields */

#define FARC_LRBAR_LRBA_MASK           0xFFFFFFFFu

#define FARC_LRBAR_LRBA_SHIFT          0u

#define FARC_LRBAR_LRBA_WIDTH          32u

#define FARC_LRBAR_LRBA(x)             (((uint32_t)(((uint32_t)(x))<<FARC_LRBAR_LRBA_SHIFT))&FARC_LRBAR_LRBA_MASK)

/* LRBAR Reg Mask */

#define FARC_LRBAR_MASK                0xFFFFFFFFu



/* PRBAR Bit Fields */

#define FARC_PRBAR_PRBA_MASK           0xFFFFFFFFu

#define FARC_PRBAR_PRBA_SHIFT          0u

#define FARC_PRBAR_PRBA_WIDTH          32u

#define FARC_PRBAR_PRBA(x)             (((uint32_t)(((uint32_t)(x))<<FARC_PRBAR_PRBA_SHIFT))&FARC_PRBAR_PRBA_MASK)

/* PRBAR Reg Mask */

#define FARC_PRBAR_MASK                0xFFFFFFFFu



/* LRSR Bit Fields */

#define FARC_LRSR_LRS_MASK             0xFFFFFFFFu

#define FARC_LRSR_LRS_SHIFT            0u

#define FARC_LRSR_LRS_WIDTH            32u

#define FARC_LRSR_LRS(x)               (((uint32_t)(((uint32_t)(x))<<FARC_LRSR_LRS_SHIFT))&FARC_LRSR_LRS_MASK)

/* LRSR Reg Mask */

#define FARC_LRSR_MASK                 0xFFFFFFFFu





/**

 * @}

 */ /* end of group FARC_Register_Masks */



/**

 * @}

 */ /* end of group FARC_Peripheral_Access_Layer */



#ifdef __cplusplus
}
#endif
#endif
