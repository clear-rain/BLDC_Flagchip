#ifndef _DEVICE_FEATURES_FC4150F1M__A_CORE_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__A_CORE_COMMON_H_

/**
  * @brief Configuration of the Cortex-M4 Processor and Core Peripherals
  */
#define __MPU_PRESENT             1U       /**< FC4150FXX provides an MPU                     */
#define __NVIC_PRIO_BITS          3U       /**< FC4150FXX uses 3 Bits for the Priority Levels */
#define __FPU_PRESENT             1U       /**< FPU present                                   */

typedef enum
{
  /* Auxiliary constants */
  NotAvail_IRQn                      = -128,       /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn                = -14,      /**< Non Maskable Interrupt */
  HardFault_IRQn                     = -13,      /**< Cortex-M4 SV Hard Fault Interrupt */
  MemoryManagement_IRQn              = -12,      /**< Cortex-M4 Memory Management Interrupt */
  BusFault_IRQn                      = -11,      /**< Cortex-M4 Bus Fault Interrupt */
  UsageFault_IRQn                    = -10,      /**< Cortex-M4 Usage Fault Interrupt */
  SVCall_IRQn                        = -5,       /**< Cortex-M4 SV Call Interrupt */
  DebugMonitor_IRQn                  = -4,       /**< Cortex-M4 Debug Monitor Interrupt */
  PendSV_IRQn                        = -2,       /**< Cortex-M4 Pend SV Interrupt */
  SysTick_IRQn                       = -1,       /**< Cortex-M4 System Tick Interrupt */

  /* FC4150 Device specific interrupts */
  DMA0_IRQn                          = 0U,         /* DMA channel 0 transfer complete */
  DMA1_IRQn                          = 1U,         /* DMA channel 1 transfer complete */
  DMA2_IRQn                          = 2U,         /* DMA channel 2 transfer complete */
  DMA3_IRQn                          = 3U,         /* DMA channel 3 transfer complete */
  DMA4_IRQn                          = 4U,         /* DMA channel 4 transfer complete */
  DMA5_IRQn                          = 5U,         /* DMA channel 5 transfer complete */
  DMA6_IRQn                          = 6U,         /* DMA channel 6 transfer complete */
  DMA7_IRQn                          = 7U,         /* DMA channel 7 transfer complete */
  DMA8_IRQn                          = 8U,         /* DMA channel 8 transfer complete */
  DMA9_IRQn                          = 9U,         /* DMA channel 9 transfer complete */
  DMA10_IRQn                         = 10U,        /* DMA channel 10 transfer complete */
  DMA11_IRQn                         = 11U,        /* DMA channel 11 transfer complete */
  DMA12_IRQn                         = 12U,        /* DMA channel 12 transfer complete */
  DMA13_IRQn                         = 13U,        /* DMA channel 13 transfer complete */
  DMA14_IRQn                         = 14U,        /* DMA channel 14 transfer complete */
  DMA15_IRQn                         = 15U,        /* DMA channel 15 transfer complete */
  DMA_error_IRQn                     = 16U,        /* DMA error interrupt channels 0-15 */
  MCM_IRQn                           = 17U,        /* FPU sources */
  Flash_IRQn                         = 18U,        /* Flash Controller Command complete etc. interrupt */
  LVD_IRQn                           = 19U,        /* Low voltage detect interrupt */
  WDOG0_IRQn                         = 20U,        /* interrupt request out before wdg reset out */
  WDOG1_IRQn                         = 21U,        /* interrupt request out before wdg reset out */
  FWM_IRQn                           = 22U,        /* FWM output as interrupt */
  RCM_IRQn                           = 23U,        /* RCM Asynchronous Interrupt */
  FCIIC0_IRQn                        = 24U,        /* FCIIC0 Interrupt */
  FCIIC1_IRQn                        = 25U,        /* FCIIC1 Interrupt */
  FCSPI0_IRQn                        = 26U,        /* FCSPI0 Interrupt */
  FCSPI1_IRQn                        = 27U,        /* FCSPI1 Interrupt */
  FCSPI2_IRQn                        = 28U,        /* FCSPI2 Interrupt */
  FCUART0_IRQn                       = 29U,        /* FCUART0 Interrupt */
  FCUART1_IRQn                       = 30U,        /* FCUART1 Interrupt */
  FCUART2_IRQn                       = 31U,        /* FCUART2 Interrupt */
  ADC0_IRQn                          = 32U,        /* ADC0 interrupt request. */
  ADC1_IRQn                          = 33U,        /* ADC1 interrupt request. */
  CMP0_IRQn                          = 34U,        /* CMP0 interrupt request */
  CMP1_IRQn                          = 35U,        /* CMP1 interrupt request */
  CMP2_IRQn                          = 36U,        /* CMP2 interrupt request */
  ERM_fault_IRQn                     = 37U,        /* ERM single or double bit error interrupt */
  INTM_IRQn                          = 38U,        /* INTM timeout interrupt */
  RTC_IRQn                           = 39U,        /* RTC alarm interrupt */
  RTC_seconds_IRQn                   = 40U,        /* RTC seconds interrupt */
  FCPIT0_IRQn                        = 41U,        /* FCPIT0 interrupt */
  PTIMER0_IRQn                       = 42U,        /* PTIMER0 interrupt */
  PTIMER1_IRQn                       = 43U,        /* PTIMER interrupt */
  I2S0_IRQn                          = 44U,        /* I2S interrupt */
  I2S1_IRQn                          = 45U,        /* I2S interrupt */
  SCG_IRQn                           = 46U,        /* SCG bus interrupt request */
  AONTMR_IRQn                        = 47U,        /* Always On Timer    AOTMR0 AONTMR interrupt request */
  PORTA_IRQn                         = 48U,        /* PORTA Interrupt */
  PORTB_IRQn                         = 49U,        /* PORTB Interrupt */
  PORTC_IRQn                         = 50U,        /* PORTC Interrupt */
  PORTD_IRQn                         = 51U,        /* PORTD Interrupt */
  PORTE_IRQn                         = 52U,        /* PORTE Interrupt */
  SWI_IRQn                           = 53U,        /* Software interrupt */
  QSPI_IRQn                          = 54U,        /* QuadSPI QSPI All interrupts ORed output */
  FlexCAN0_IRQn                      = 60U,        /* FlexCAN0 interrupt */
  FlexCAN1_IRQn                      = 61U,        /* FlexCAN1 interrupt */
  FlexCAN2_IRQn                      = 62U,        /* FlexCAN2 interrupt */
  FlexCAN3_IRQn                      = 63U,        /* FlexCAN0 interrupt Reserved*/
  FlexCAN4_IRQn                      = 64U,        /* FlexCAN1 interrupt Reserved*/
  FlexCAN5_IRQn                      = 65U,        /* FlexCAN2 interrupt Reserved*/
  FTU0_IRQn                          = 66U,        /* FTU0 all source interrupt */
  FTU1_IRQn                          = 67U,        /* FTU1 all source interrupt */
  FTU2_IRQn                          = 68U,        /* FTU2 all source interrupt */
  FTU3_IRQn                          = 69U,        /* FTU3 all source interrupt */
  FTU4_IRQn                          = 70U,        /* FTU4 all source interrupt */
  FTU5_IRQn                          = 71U,        /* FTU5 all source interrupt */
  FTU6_IRQn                          = 72U,        /* FTU6 all source interrupt */
  FTU7_IRQn                          = 73U,        /* FTU7 all source interrupt */
  HSM0_IRQn                          = 74U,        /* Hardware Secure Module HSM0 Crypto interrupt */
  TSTAMP0_IRQn                       = 75U,        /* TSTAMP0 TimerStamp interrupt */
  CORDIC_IRQn                        = 76U,        /* Cordic Accelator interrupt */
  CMU0_IRQn                          = 77U,        /* CMU0 interrupt */
  CMU1_IRQn                          = 78U,        /* CMU1 interrupt */
  CMU2_IRQn                          = 79U,        /* CMU2 interrupt */
  CMU3_IRQn                          = 80U,        /* CMU3 interrupt */
  ISM0_IRQn                          = 81U,        /* ISM0 interrupt */
  FCSPI3_IRQn                        = 82U,        /* FCSPI2 Interrupt */
  FCUART3_IRQn                       = 83U,        /* FCUART3 Interrupt */
  FCUART4_IRQn                       = 84U,        /* FCUART4 Interrupt */
  FCUART5_IRQn                       = 85U,        /* FCUART5 Interrupt */
  TSTAMP1_IRQn                       = 86U,        /* TSTAMP1 TimerStamp interrupt */
  Reserved                           = 87U,         /* Reserved */
  ENET_TX0_IRQn                      = 88U,        /* ENET Tx Channel 0 interrupt */
  ENET_TX1_IRQn                      = 89U,        /* ENET Tx Channel 1 interrupt */
  ENET_RX0_IRQn                      = 90U,        /* ENET Rx Channel 0 interrupt */
  ENET_RX1_IRQn                      = 91U,        /* ENET Rx Channel 1 interrupt */
  ENET_System_IRQn                   = 92U,         /* ENET System Interupt */
  IRQn_MAX                           = 92U
} IRQn_Type;

#endif
