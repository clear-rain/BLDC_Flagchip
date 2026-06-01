#ifndef _DEVICE_FEATURES_FC4150_DMA_COMMON_H_
#define _DEVICE_FEATURES_FC4150_DMA_COMMON_H_
/*********************** DMA Features ****************************/
/** Number of instances of the DMA module. */
#define DMA_INSTANCE_COUNT                       (1u)
/* DMA - Peripheral instance base addresses */
/** Peripheral DMA base address */
#define DMA_BASE                                 (0x40008000u)
/** Peripheral DMA base pointer */
#define DMA                                      ((DMA_Type *)DMA_BASE)
/** Array initializer of DMA peripheral base addresses */
#define DMA_BASE_ADDRS                           {DMA_BASE}
/** Array initializer of DMA peripheral base pointers */
#define DMA_BASE_PTRS                            {DMA}
// need fill by yourself
///** Number of interrupt vector arrays for the DMA module. */
//#define DMA_IRQS_ARR_COUNT                       (1u)
///** Number of interrupt channels for the DMA module. */
//#define DMA_IRQS_CH_COUNT                        (1u)
///** Interrupt vectors for the DMA peripheral type */
//#define DMA_IRQS                                 {DMA_IRQn}
#endif
