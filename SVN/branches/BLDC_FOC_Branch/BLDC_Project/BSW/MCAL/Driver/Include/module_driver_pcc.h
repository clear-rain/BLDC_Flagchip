/**
 * @file module_driver_pcc.h
 * @author Flagchip
 * @brief PCC driver type definition and API
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_PCC_H_
#define _DRIVER_MODULE_DRIVER_PCC_H_

#include "module_driver_scg.h"

#if PCC_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_pcc
 * @{
 */

/**
  * @name  PCC_FTU_TCLK_FREQ
  * @brief FTU input TCLK frequency
  */
#ifndef PCC_FTU_TCLK_FREQ
#define PCC_FTU_TCLK_FREQ   0U
#endif

/**
 * @name  PCC API Service IDs
 *
 * @{
 */
#define PCC_SET_PCC_ID                  0x00U
#define PCC_GET_PCC_INTERFACE_CLOCK_ID  0x01U
#define PCC_GET_PCC_FUNCTION_CLOCK_ID   0x02U
/** @}*/

/**
 * @name  PCC Dev Error Code
 * @brief Error Code of calling PCC apis
 *
 * @{
 */
#define PCC_E_PARAM_POINTER   			0x01U
#define PCC_E_PARAM_OUT_RANGE  			0x02U
/** @}*/

/**
 * @name  PCC API Service IDs
 * @brief Marco for PCCn Bit Field definition 
 * 
 * @{
 */
#define PCC_UNUSED_MASK                     0x80000000U
#define PCC_CGC_MASK                        0x40000000U
#define PCC_CGC_SHIFT                       30U
#define PCC_CGC_WIDTH                       1U
#define PCC_CGC(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_CGC_SHIFT))&PCC_CGC_MASK)
#define PCC_SEL_MASK                        0x7000000U
#define PCC_SEL_SHIFT                       24U
#define PCC_SEL_WIDTH                       3U
#define PCC_SEL(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_SEL_SHIFT))&PCC_SEL_MASK)
#define PCC_GetSEL(x)                       ((((uint32_t)(x))&PCC_SEL_MASK)>>PCC_SEL_SHIFT)
#define PCC_DIV_MASK                        0x7U
#define PCC_DIV_SHIFT                       0U
#define PCC_DIV_WIDTH                       3U
#define PCC_DIV(x)                          (((uint32_t)(((uint32_t)(x))<<PCC_DIV_SHIFT))&PCC_DIV_MASK)
#define PCC_GetDIV(x)                       ((((uint32_t)(x))&PCC_DIV_MASK)>>PCC_DIV_SHIFT)
#define PCC_MUX_MAX_NUMBER                  8U

/*        PCC property MACRO, defines every peripheral clock system architecture      */
#define PCC_CLK_NOT_APPLY               (0U)
#define PCC_CGC_AVAILABLE               (1U << 0U)
#define PCC_FUNCCLK_MUXDIVH_USED        (1U << 1U)
#define PCC_FUNCCLK_MUXDIVM_USED        (1U << 2U)
#define PCC_FUNCCLK_MUXDIVL_USED        (1U << 3U)
#define PCC_FUNCCLK_MUXDIVHPIN_USED     (1U << 4U)
#define PCC_MOUDULE_DIV_USED            (1U << 5U)
#define PCC_CLK_DOMAIN_CORE             (1U << 6U)
#define PCC_CLK_DOMAIN_BUS              (1U << 7U)

#define PCC_PROPERTY_MUXDIV_MASK           (PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVM_USED | PCC_FUNCCLK_MUXDIVL_USED)
#define PCC_PROPERTY_MUXDIV_ALL_MASK       (PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVM_USED | PCC_FUNCCLK_MUXDIVL_USED | PCC_FUNCCLK_MUXDIVHPIN_USED)
/** @}*/

/** @brief PCC instance number */
typedef enum
{
	PCC_INSTANCE_0 = 0U,
	PCC_INSTANCE_ERR
} PCC_InstanceType;

/** @brief PCC clock list */
typedef enum
{
    PCC_CLK_DMA_MUX,                 /**< PCC clock property  PCC_CLK_DMA_MUX */
    PCC_CLK_FTU3,                    /**< PCC clock property  PCC_CLK_FTU3 */
    PCC_CLK_ADC1,                    /**< PCC clock property  PCC_CLK_ADC1 */
    PCC_CLK_FCSPI0,                  /**< PCC clock property  PCC_CLK_FCSPI0 */
    PCC_CLK_FCSPI1,                  /**< PCC clock property  PCC_CLK_FCSPI1 */
    PCC_CLK_FCSPI2,                  /**< PCC clock property  PCC_CLK_FCSPI2 */
#if PCC_SPI3_SUPPORT
    PCC_CLK_FCSPI3,                  /**< PCC clock property  PCC_CLK_FCSPI3 */
#endif
    PCC_CLK_PTIMER1,                 /**< PCC clock property  PCC_CLK_PTIMER1 */
    PCC_CLK_CRC,                     /**< PCC clock property  PCC_CLK_CRC */
    PCC_CLK_PTIMER0,                 /**< PCC clock property  PCC_CLK_PTIMER0 */
    PCC_CLK_FCPIT0,                  /**< PCC clock property  PCC_CLK_FCPIT0 */
    PCC_CLK_FTU0,                    /**< PCC clock property  PCC_CLK_FTU0 */
    PCC_CLK_FTU1,                    /**< PCC clock property  PCC_CLK_FTU1 */
    PCC_CLK_FTU2,                    /**< PCC clock property  PCC_CLK_FTU2 */
    PCC_CLK_ADC0,                    /**< PCC clock property  PCC_CLK_ADC0 */
    PCC_CLK_RTC,                     /**< PCC clock property  PCC_CLK_RTC */
    PCC_CLK_CMU0,                    /**< PCC clock property  PCC_CLK_CMU0 */
    PCC_CLK_CMU1,                    /**< PCC clock property  PCC_CLK_CMU1 */
    PCC_CLK_AONTIMER,                /**< PCC clock property  PCC_CLK_AONTIMER */
#if PCC_TSTMP0_SUPPORT
    PCC_CLK_TSTMP0,                  /**< PCC clock property  PCC_CLK_TSTMP0 */
#endif
    PCC_CLK_CMU2,                    /**< PCC clock property  PCC_CLK_CMU2 */
    PCC_CLK_CMU3,                    /**< PCC clock property  PCC_CLK_CMU3 */
#if PCC_CORDIC_SUPPORT
    PCC_CLK_CORDIC,                  /**< PCC clock property  PCC_CLK_CORDIC */
#endif
#if PCC_FREQM_SUPPORT
    PCC_CLK_FREQM,                   /**< PCC clock property  PCC_CLK_FREQM */
#endif
    PCC_CLK_PORTA,                   /**< PCC clock property  PCC_CLK_PORTA */
    PCC_CLK_PORTB,                   /**< PCC clock property  PCC_CLK_PORTB */
    PCC_CLK_PORTC,                   /**< PCC clock property  PCC_CLK_PORTC */
    PCC_CLK_PORTD,                   /**< PCC clock property  PCC_CLK_PORTD */
    PCC_CLK_PORTE,                   /**< PCC clock property  PCC_CLK_PORTE */
    PCC_CLK_WKU,                     /**< PCC clock property  PCC_CLK_WKU */
#if PCC_I2S0_SUPPORT
    PCC_CLK_I2S0,                    /**< PCC clock property  PCC_CLK_I2S0 */
#endif
#if PCC_I2S1_SUPPORT
    PCC_CLK_I2S1,                    /**< PCC clock property  PCC_CLK_I2S1 */
#endif
#if PCC_FTU6_SUPPORT
    PCC_CLK_FTU6,                    /**< PCC clock property  PCC_CLK_FTU6 */
#endif
#if PCC_FTU7_SUPPORT
    PCC_CLK_FTU7,                    /**< PCC clock property  PCC_CLK_FTU7 */
#endif
    PCC_CLK_FCUART3,                 /**< PCC clock property  PCC_CLK_FCUART3 */
    PCC_CLK_FCUART4,                 /**< PCC clock property  PCC_CLK_FCUART4 */
    PCC_CLK_FCUART5,                 /**< PCC clock property  PCC_CLK_FCUART5 */
    PCC_CLK_FWM,                     /**< PCC clock property  PCC_CLK_FWM */
    PCC_CLK_FCIIC0,                  /**< PCC clock property  PCC_CLK_FCIIC0 */
    PCC_CLK_FCIIC1,                  /**< PCC clock property  PCC_CLK_FCIIC1 */
    PCC_CLK_FCUART0,                 /**< PCC clock property  PCC_CLK_FCUART0 */
    PCC_CLK_FCUART1,                 /**< PCC clock property  PCC_CLK_FCUART1 */
    PCC_CLK_FCUART2,                 /**< PCC clock property  PCC_CLK_FCUART2 */
    PCC_CLK_FTU4,                    /**< PCC clock property  PCC_CLK_FTU4 */
    PCC_CLK_FTU5,                    /**< PCC clock property  PCC_CLK_FTU5 */
    PCC_CLK_LU0,                     /**< PCC clock property  PCC_CLK_LU0 */
    PCC_CLK_CMP0,                    /**< PCC clock property  PCC_CLK_CMP0 */
#if PCC_CMP1_SUPPORT
    PCC_CLK_CMP1,                    /**< PCC clock property  PCC_CLK_CMP1 */
#endif
#if PCC_CMP2_SUPPORT
    PCC_CLK_CMP2,                    /**< PCC clock property  PCC_CLK_CMP2 */
#endif
#if PCC_OSPI_SUPPORT
    PCC_CLK_OSPI,                    /**< PCC clock property  PCC_CLK_OSPI */
#endif
#if PCC_ENET_SUPPORT
    PCC_CLK_ENET,                    /**< PCC clock property  PCC_CLK_ENET */
#endif
#if PCC_TSTMP1_SUPPORT
    PCC_CLK_TSTMP1,                  /**< PCC clock property  PCC_CLK_TSTMP1 */
#endif
    PCC_CLK_CAN0,                    /**< PCC clock property  PCC_CLK_CAN0 */
    PCC_CLK_CAN1,                    /**< PCC clock property  PCC_CLK_CAN1 */
    PCC_CLK_CAN2,                    /**< PCC clock property  PCC_CLK_CAN2 */
#if PCC_CAN3_SUPPORT
    PCC_CLK_CAN3,                    /**< PCC clock property  PCC_CLK_CAN3 */
#endif
#if PCC_CAN4_SUPPORT
    PCC_CLK_CAN4,                    /**< PCC clock property  PCC_CLK_CAN4 */
#endif
#if PCC_CAN5_SUPPORT
    PCC_CLK_CAN5,                    /**< PCC clock property  PCC_CLK_CAN5 */
#endif
    PCC_CLK_HSM,                     /**< PCC clock property  PCC_CLK_HSM */
    PCC_END_OF_CLOCKS                /**< PCC clock property  PCC_END_OF_CLOCKS */
} PCC_ClkSrcType;

/**
 * @brief Pcc clock status
*/
typedef enum
{
    PCC_STATUS_SUCCESS = 0U,                /**< PCC operation success.   */
    PCC_STATUS_CLOCK_INVALID = 1U,          /**< PCC operation failed.   */
    PCC_STATUS_CONFIGURED_NOT_SUPPORT = 1U  /**< PCC operation not support.  */
} PCC_StatusType;

/**
 * @brief Pcc clock status:
 *   PCC_CLOCK_UNDEFINE: clock not initialized.
 *   PCC_CLOCK_VALID: clock valid for query.
 *   PCC_CLOCK_ERROR: clock initialized but failed.
*/
typedef enum
{
    PCC_CLOCK_UNDEFINE      = 0U,    /**< clock source undefined  */
    PCC_CLOCK_DISABLE       = 1U,    /**< clock source set as disabled  */
    PCC_CLOCK_VALID         = 2U,    /**< clock source set as valid  */
    PCC_CLOCK_ERROR         = 3U,    /**< clock source set as error  */
    PCC_CLOCK_TIMEOUT       = 4U,    /**< clock source set as timeout  */
    PCC_CLOCK_PARAM_INVALID = 5U,    /**< clock source set as invalid parameter  */
    PCC_CLOCK_UNKNOWN       = 6U     /**< clock source unknown  */
} PCC_ClockStatusDef;

/**
 * @brief defined the clock source for function clock,match with PCC_XXX[SEL] bit filed.
 */
typedef enum
{
    PCC_CLKGATE_SRC_OFF        = 0U,  /**< clock source off  */
    PCC_CLKGATE_SRC_FOSCDIV    = 1U,  /**< clock source FOSCDIV  */
    PCC_CLKGATE_SRC_SIRCDIV    = 2U,  /**< clock source SIRCDIV  */
    PCC_CLKGATE_SRC_FIRCDIV    = 3U,  /**< clock source FIRCDIV  */
    PCC_CLKGATE_SRC_RESERVE0   = 4U,  /**< clock source reserve0  */
    PCC_CLKGATE_SRC_RESERVE1   = 5U,  /**< clock source reserve1  */
    PCC_CLKGATE_SRC_PLL0DIV    = 6U,  /**< clock source PLL0DIV  */
    PCC_CLKGATE_SRC_RESERVE2   = 7U   /**< clock source reserve2  */
} PCC_ClkGateSrcType;

/**
 * @brief define the clock divider,match with PCC_XXX[DIV] bit filed.
 */
typedef enum
{
    PCC_CLK_DIV_BY1     = 0U,             /**< Divide by 1 (pass-through, no clock divide) */
    PCC_CLK_DIV_BY2     = 1U,             /**< Divide by 2 */
    PCC_CLK_DIV_BY3     = 2U,             /**< Divide by 3 */
    PCC_CLK_DIV_BY4     = 3U,             /**< Divide by 4 */
    PCC_CLK_DIV_BY5     = 4U,             /**< Divide by 5 */
    PCC_CLK_DIV_BY6     = 5U,             /**< Divide by 6 */
    PCC_CLK_DIV_BY7     = 6U,             /**< Divide by 7 */
    PCC_CLK_DIV_BY8     = 7U              /**< Divide by 8 */
} PCC_ClkDivType;

/**
 * @brief define the PCC module initialization structure.
 */
typedef struct
{
    PCC_ClkSrcType eClockName;               /**< Peripheral clock source.                  */
    bool bEn;                                /**< Peripheral clock gate.                    */
    PCC_ClkGateSrcType eClkSrc;              /**< Peripheral clock source.                  */
    PCC_ClkDivType eDivider;                 /**< Peripheral clock divider value.           */
} PCC_CtrlType;

/**
 * @brief module internal PCC clock status maintain structure.
 * the driver would update the clock status and clock value at runtime.
 * @param u32PccBaseClk: the module's own working frequency.
 * @param u32PccFuncClk: the module's function used clock, like UART baud rate.
 */
typedef struct
{
	uint32_t u32PccBaseClk;  /**< PCC base clock. */
	uint32_t u32PccFuncClk;  /**< PCC function clock. */
    PCC_ClockStatusDef eClkStatus;  /**< PCC clock status. */
} PCC_ClockInfoType;

/**
 * @brief get PCC function clock status and value.
 *
 * @param eClockName used for choose PCC clock source to query.
 * @return Pcc function clock frequency
 *
 */
uint32_t PCC_GetPccFunctionClock(const PCC_ClkSrcType eClockName);

/**
 * @brief get PCC interface clock status and value.
 *
 * @param eClockName used for choose PCC clock source to query.
 * @return Pcc interface clock frequency
 *
 */
uint32_t PCC_GetPccInterfaceClock(const PCC_ClkSrcType eClockName);

/**
 * @brief set PCC one peripheral clock configuration.
 *
 * @param pConfig: the PCC initialize value point set by user.
 * @return PCC_StatusType pcc function status
 */
PCC_StatusType PCC_SetPcc(const PCC_CtrlType *const pConfig);

/** @}*/ /* module_driver_pcc */

#endif

#endif
