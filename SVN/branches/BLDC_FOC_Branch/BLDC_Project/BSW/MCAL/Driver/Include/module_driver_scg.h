/**
 * @file module_driver_scg.h
 * @author Flagchip
 * @brief SCG driver type definition and API
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
#ifndef _DRIVER_MODULE_DRIVER_SCG_H_
#define _DRIVER_MODULE_DRIVER_SCG_H_

#include "HwA_scg.h"

#if SCG_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_scg
 * @{
 */
#ifndef SCG_DEV_ERROR_REPORT
#define SCG_DEV_ERROR_REPORT	STD_OFF
#endif

#if SCG_DEV_ERROR_REPORT == STD_ON
#define SCG_ReportDevError(func, error) ReportDevError(SCG_MODULE_ID, func, error)
#endif

/**
 * @name  SCG OSC frequency
 *
 * @{
 */

#ifndef FOSC_FREQUENCY
#define FOSC_FREQUENCY   16000000U
#endif

#ifndef SOSC_FREQUENCY
#define SOSC_FREQUENCY   32768U
#endif
/** @} */

/**
 * @name  SCG Clock Symbol
 *
 * @{
 */
#define SCG_CORE_CLOCK_SYMBOL CORE
#define SCG_BUS_CLOCK_SYMBOL BUS
#define SCG_SLOW_CLOCK_SYMBOL SLOW
#define SCG_SIRC_CLOCK_SYMBOL SIRC
#define SCG_SIRC32K_CLOCK_SYMBOL SIRC32K
#define SCG_FIRC_CLOCK_SYMBOL FIRC
#define SCG_FOSC_CLOCK_SYMBOL FOSC
#define SCG_SOSC_CLOCK_SYMBOL SOSC
#define SCG_PLL0_CLOCK_SYMBOL PLL0
/** @} */

/**
 * @name  SCG API Service IDs
 *
 * @{
 */
#define SCG_SET_SIRC_ID   		  0x00U
#define SCG_ENABLE_SIRC32K_ID     0x01U
#define SCG_ENABLE_FIRC_ID   	  0x02U
#define SCG_ENABLE_FOSC_ID        0x03U
#define SCG_ENABLE_SOSC_ID        0x04U
#define SCG_ENABLE_PLL0_ID  	  0x05U
#define SCG_SET_CLOCK_CTRL_ID     0x06U
#define SCG_SET_CLOCK_OUT_ID      0x07U
#define SCG_SWITCH_SYS_CLOCK_ID   0x08U
#define SCG_GET_SCG_CLOCK_FREQ_ID 0x09U
#define SCG_SCG_DEINIT_ID         0x0AU
#define SCG_SCG_INTERRUPT_INIT_ID 0x0BU
/** @} */

/**
 * @name  SCG Dev Error Code
 * @brief Error Code of calling SCG apis
 *
 * @{
 */
#define SCG_E_PARAM_POINTER   			0x01U
#define SCG_E_PARAM_OUT_RANGE   		0x02U
/** @} */

/** @brief clock list for internal clock tree */
typedef enum
{
    /* Main clocks */
    SCG_CORE_CLK                       = 0U,       /**< Core clock                 */
    SCG_BUS_CLK                        = 1U,       /**< Bus clock                  */
    SCG_SLOW_CLK                       = 2U,       /**< Slow clock                 */
    SCG_SIRC_CLK                       = 3U,       /**< SIRC clock                 */
    SCG_SIRC32K_CLK                    = 4U,       /**< SIRC clock                 */
    SCG_FIRC_CLK                       = 5U,       /**< FIRC clock                 */
    SCG_FOSC_CLK                       = 6U,       /**< FOSC clock                 */
    SCG_PLL0_CLK                       = 7U,       /**< PLL0 clock                 */
    SCG_SOSC_CLK                       = 8U,       /**< SOSC clock                 */
    SCG_SCG_CLKOUT_CLK                 = 9U,       /**< SCG CLK_OUT clock          */
    SCG_SIRCDIVH_CLK                   = 10U,      /**< SIRCDIVH functional clock  */
    SCG_SIRCDIVM_CLK                   = 11U,      /**< SIRCDIVM functional clock  */
    SCG_SIRCDIVL_CLK                   = 12U,      /**< SIRCDIVL functional clock  */
    SCG_FIRCDIVH_CLK                   = 13U,      /**< FIRCDIVH functional clock  */
    SCG_FIRCDIVM_CLK                   = 14U,      /**< FIRCDIVM functional clock  */
    SCG_FIRCDIVL_CLK                   = 15U,      /**< FIRCDIVL functional clock  */
    SCG_FOSCDIVH_CLK                   = 16U,      /**< FOSCDIVH functional clock  */
    SCG_FOSCDIVM_CLK                   = 17U,      /**< FOSCDIVM functional clock  */
    SCG_FOSCDIVL_CLK                   = 18U,      /**< FOSCDIVL functional clock  */
    SCG_PLL0DIVH_CLK                   = 19U,      /**< PLL0DIVH functional clock  */
    SCG_PLL0DIVM_CLK                   = 20U,      /**< PLL0DIVM functional clock  */
    SCG_PLL0DIVL_CLK                   = 21U,      /**< PLL0DIVL functional clock  */
    SCG_END_OF_CLOCKS                  = 22U       /**< End of SCG clocks          */
} SCG_ClkSrcType;

/** @brief indicate the clock status for each clock source in clock tree list. */
typedef enum
{
    SCG_STATUS_SUCCESS = 0U,          /**< function called success */
    SCG_STATUS_SEQUENCE_ERROR = 1U,   /**< function called report sequence error */
    SCG_STATUS_TIMEOUT = 2U,          /**< function called report timeout error */
    SCG_STATUS_IRC_ERROR = 3U,        /**< function called report internal clock error */
    SCG_STATUS_PARAM_ERROR = 4U,      /**< function called report internal clock error */
	SCG_STATUS_ERRTA_PMC_001 = 0x10   /**< for FC4150F512, FC4150F2M, FC4150F1MA, if using standby,
										   the bus clock allocation must be either DIV1 or DIV2 */
} SCG_StatusType;

/**
 * @brief SCG SystemClk type.
 */
typedef enum
{
    SCG_SYSTEM_CLOCK_CORE,  /**< Core clock.        */
    SCG_SYSTEM_CLOCK_BUS,   /**< BUS clock.         */
    SCG_SYSTEM_CLOCK_SLOW,  /**< System slow clock. */
    SCG_SYSTEM_CLOCK_MAX    /**< Max value.         */
} SCG_SystemClkType;

/**
 * @brief SCG xxxIRC TRIMSRC type.
*/
typedef enum
{
    SCG_IRC_TRIMSRC_RESERVE0   = 0U,   /**< Clock Trim source reserve0  */
    SCG_IRC_TRIMSRC_RESERVE1   = 1U,   /**< Clock Trim source reserve1  */
    SCG_IRC_TRIMSRC_FOSC       = 2U,   /**< Clock Trim source FOSC      */
    SCG_IRC_TRIMSRC_SOSC       = 3U    /**< Clock Trim source SOSC      */
} SCG_IrcTrimSrcType;


/**
 * @brief SCG asynchronous clock type.
    */
typedef enum
{
    SCG_ASYNC_CLOCK_DIVH   = 0U,   /**< High Frequency Clock divider */
    SCG_ASYNC_CLOCK_DIVM   = 1U,   /**< Mid Frequency Clock divider  */
    SCG_ASYNC_CLOCK_DIVL   = 2U,   /**< Low Frequency Clock divider  */
    SCG_ASYNC_CLOCK_MAX    = 3U    /**< Max value.       */
} SCG_AsyncClkType;

/**
 * @brief SCG_CCR [SCS]  to Select system clock source
 *
 */
typedef enum
{
    SCG_CLOCK_SRC_FOSC     = 1U,       /**< System OSC. */
    SCG_CLOCK_SRC_FIRC     = 3U,       /**< Fast IRC.   */
    SCG_CLOCK_SRC_PLL0     = 6U,       /**< System PLL. */
    SCG_CLOCK_SRC_NONE     = 255U      /**< MAX value.  */
} SCG_ClockSrcType;

/**
 * @brief SCG_CCR [DIVCORE ]/ SCG_CCR [DIVBUS ]/ SCG_CCR [DIVSLOW ]  to Select system clock source.
 *
 */
typedef enum
{
    SCG_CLOCK_DIV_BY1   = 0U,     /**< Divided by 1.    */
    SCG_CLOCK_DIV_BY2   = 1U,     /**< Divided by 2.    */
    SCG_CLOCK_DIV_BY3   = 2U,     /**< Divided by 3.    */
    SCG_CLOCK_DIV_BY4   = 3U,     /**< Divided by 4.    */
    SCG_CLOCK_DIV_BY5   = 4U,     /**< Divided by 5.    */
    SCG_CLOCK_DIV_BY6   = 5U,     /**< Divided by 6.    */
    SCG_CLOCK_DIV_BY7   = 6U,     /**< Divided by 7.    */
    SCG_CLOCK_DIV_BY8   = 7U,     /**< Divided by 8.    */
    SCG_CLOCK_DIV_BY9   = 8U,     /**< Divided by 9.    */
    SCG_CLOCK_DIV_BY10  = 9U,     /**< Divided by 10.   */
    SCG_CLOCK_DIV_BY11  = 10U,    /**< Divided by 11.   */
    SCG_CLOCK_DIV_BY12  = 11U,    /**< Divided by 12.   */
    SCG_CLOCK_DIV_BY13  = 12U,    /**< Divided by 13.   */
    SCG_CLOCK_DIV_BY14  = 13U,    /**< Divided by 14.   */
    SCG_CLOCK_DIV_BY15  = 14U,    /**< Divided by 15.   */
    SCG_CLOCK_DIV_BY16  = 15U     /**< Divided by 16.   */
} SCG_ClockDivType;

/**
 * @brief SCG_ CLKOUTCFG [CLKOUTSEL]  to Select system clock source.
 */
typedef enum
{
    SCG_CLOCKOUT_SRC_OFF      = 0U,   /**< SCG OFF.   */
    SCG_CLOCKOUT_SRC_FOSC     = 1U,   /**< Fast OSC.   */
    SCG_CLOCKOUT_SRC_SIRC     = 2U,   /**< Slow IRC.   */
    SCG_CLOCKOUT_SRC_FIRC     = 3U,   /**< Fast IRC.   */
    SCG_CLOCKOUT_SRC_SOSC     = 4U,   /**< Slow OSC.   */
    SCG_CLOCKOUT_SRC_PLL0     = 6U,   /**< System PLL. */
    SCG_CLOCKOUT_SRC_SIRC32K  = 7U    /**< SIRC32K_CLK.*/
} SCG_ClockoutSrcType;

/**
 * @brief SCG_CLKOUTCFG [NVMCLK_FIRC_SIRC]  to select nvm clock source.
 */
typedef enum
{
    SCG_NVMCLK_SRC_SIRC = 30u,   /**< NVM source choose SIRC.   */
    SCG_NVMCLK_SRC_FIRC = 31u    /**< NVM source choose FIRC.   */
}SCG_NvmClkSrcType;

/** @brief [DIVL]/[DIVM]/[DIVH] bit field definition for SCG_SIRC/ SCG_FIRC/ SCG_FOSC/ SCG_PLL0 registers */
typedef enum
{
    SCG_ASYNC_CLOCK_DISABLE  = 0U,        /**< Clock output is disabled.  */
    SCG_ASYNCCLOCKDIV_BY1    = 1U,        /**< Divided by 1.              */
    SCG_ASYNCCLOCKDIV_BY2    = 2U,        /**< Divided by 2.              */
    SCG_ASYNCCLOCKDIV_BY4    = 3U,        /**< Divided by 4.              */
    SCG_ASYNCCLOCKDIV_BY8    = 4U,        /**< Divided by 8.              */
    SCG_ASYNCCLOCKDIV_BY16   = 5U,        /**< Divided by 16.             */
    SCG_ASYNCCLOCKDIV_BY32   = 6U,        /**< Divided by 32.             */
    SCG_ASYNCCLOCKDIV_BY64   = 7U         /**< Divided by 64.             */
} SCG_AsyncClockDivType;

/** @brief SCG_ PLL0CFG[PREDIV]  for PLL0 clock calculation */
typedef enum
{
    SCG_PLL0PREDIV_BY1 = 0U,    /**< Divided by 1. */
    SCG_PLL0PREDIV_BY3 = 2U,    /**< Divided by 3. */
    SCG_PLL0PREDIV_BY4 = 3U,    /**< Divided by 4. */
    SCG_PLL0PREDIV_BY5 = 4U,    /**< Divided by 5. */
    SCG_PLL0PREDIV_BY6 = 5U,    /**< Divided by 6. */
    SCG_PLL0PREDIV_BY7 = 6U,    /**< Divided by 7. */
    SCG_PLL0PREDIV_BY8 = 7U,    /**< Divided by 8. */
    SCG_PLL0PREDIV_BY9 = 8U,    /**< Divided by 9. */
    SCG_PLL0PREDIV_BY10 = 9U,   /**< Divided by 10. */
    SCG_PLL0PREDIV_BY11 = 10U,  /**< Divided by 11. */
    SCG_PLL0PREDIV_BY12 = 11U,  /**< Divided by 12. */
    SCG_PLL0PREDIV_BY13 = 12U,  /**< Divided by 13. */
    SCG_PLL0PREDIV_BY14 = 13U,  /**< Divided by 14. */
    SCG_PLL0PREDIV_BY15 = 14U,  /**< Divided by 15. */
    SCG_PLL0PREDIV_BY16 = 15U,  /**< Divided by 16. */
#if SCG_POSTDIV_SUPPORT
    SCG_PLL0PREDIV_BY17 = 16U,  /**< Divided by 17. */
    SCG_PLL0PREDIV_BY18 = 17U,  /**< Divided by 18. */
    SCG_PLL0PREDIV_BY19 = 18U,  /**< Divided by 19. */
    SCG_PLL0PREDIV_BY20 = 19U,  /**< Divided by 20. */
    SCG_PLL0PREDIV_BY21 = 20U,  /**< Divided by 21. */
    SCG_PLL0PREDIV_BY22 = 21U,  /**< Divided by 22. */
    SCG_PLL0PREDIV_BY23 = 22U,  /**< Divided by 23. */
    SCG_PLL0PREDIV_BY24 = 23U,  /**< Divided by 24. */
    SCG_PLL0PREDIV_BY25 = 24U,  /**< Divided by 25. */
    SCG_PLL0PREDIV_BY26 = 25U,  /**< Divided by 26. */
    SCG_PLL0PREDIV_BY27 = 26U,  /**< Divided by 27. */
    SCG_PLL0PREDIV_BY28 = 27U,  /**< Divided by 28. */
    SCG_PLL0PREDIV_BY29 = 28U,  /**< Divided by 29. */
    SCG_PLL0PREDIV_BY30 = 29U,  /**< Divided by 30. */
    SCG_PLL0PREDIV_BY31 = 30U,  /**< Divided by 31. */
    SCG_PLL0PREDIV_BY32 = 31U   /**< Divided by 32. */
#endif
} SCG_Pll0PredivType;

/** @brief SCG_ PLL0CFG[SOURCE] to Select PLL0 clock sourec */
typedef enum
{
    SCG_PLL0SOURCE_FOSC = 0U,
    SCG_PLL0SOURCE_FIRC = 1U
} SCG_Pll0SourceType;


#if SCG_POSTDIV_SUPPORT
/** @brief SCG_ PLL0CFG[PSTDIV]  for PLL clock calculation */
typedef enum
{
    SCG_PLLPSTDIV_BY2 = 1U,  /**< Divided by 2. */
    SCG_PLLPSTDIV_BY4 = 2U,  /**< Divided by 4. */
    SCG_PLLPSTDIV_BY8 = 3U   /**< Divided by 8. */
} SCG_Pll0PstdivType;

/** @brief SCG_ PLL0CFG [MULT]  for PLL0 clock calculation. 
 * 
 *  @note  Multiplier needs to be greater than 16
*/
typedef uint8_t SCG_Pll0MultiplyType;
#else
/** @brief SCG_ PLL0CFG [MULT]  for PLL0 clock calculation. 
 * 
 *  @note  Multiplier needs to be greater than 16
*/
typedef enum
{
    SCG_PLL0MULTIPLY_BY16 = 0U,      /**< Multiply by 16 */
    SCG_PLL0MULTIPLY_BY17 = 1U,      /**< Multiply by 17 */
    SCG_PLL0MULTIPLY_BY18 = 2U,      /**< Multiply by 18 */
    SCG_PLL0MULTIPLY_BY19 = 3U,      /**< Multiply by 19 */
    SCG_PLL0MULTIPLY_BY20 = 4U,      /**< Multiply by 20 */
    SCG_PLL0MULTIPLY_BY21 = 5U,      /**< Multiply by 21 */
    SCG_PLL0MULTIPLY_BY22 = 6U,      /**< Multiply by 22 */
    SCG_PLL0MULTIPLY_BY23 = 7U,      /**< Multiply by 23 */
    SCG_PLL0MULTIPLY_BY24 = 8U,      /**< Multiply by 24 */
    SCG_PLL0MULTIPLY_BY25 = 9U,      /**< Multiply by 25 */
    SCG_PLL0MULTIPLY_BY26 = 10U,     /**< Multiply by 26 */
    SCG_PLL0MULTIPLY_BY27 = 11U,     /**< Multiply by 27 */
    SCG_PLL0MULTIPLY_BY28 = 12U,     /**< Multiply by 28 */
    SCG_PLL0MULTIPLY_BY29 = 13U,     /**< Multiply by 29 */
    SCG_PLL0MULTIPLY_BY30 = 14U,     /**< Multiply by 30 */
    SCG_PLL0MULTIPLY_BY31 = 15U,     /**< Multiply by 31 */
    SCG_PLL0MULTIPLY_BY32 = 16U,     /**< Multiply by 32 */
    SCG_PLL0MULTIPLY_BY33 = 17U,     /**< Multiply by 33 */
    SCG_PLL0MULTIPLY_BY34 = 18U,     /**< Multiply by 34 */
    SCG_PLL0MULTIPLY_BY35 = 19U,     /**< Multiply by 35 */
    SCG_PLL0MULTIPLY_BY36 = 20U,     /**< Multiply by 36 */
    SCG_PLL0MULTIPLY_BY37 = 21U,     /**< Multiply by 37 */
    SCG_PLL0MULTIPLY_BY38 = 22U,     /**< Multiply by 38 */
    SCG_PLL0MULTIPLY_BY39 = 23U,     /**< Multiply by 39 */
    SCG_PLL0MULTIPLY_BY40 = 24U,     /**< Multiply by 40 */
    SCG_PLL0MULTIPLY_BY41 = 25U,     /**< Multiply by 41 */
    SCG_PLL0MULTIPLY_BY42 = 26U,     /**< Multiply by 42 */
    SCG_PLL0MULTIPLY_BY43 = 27U,     /**< Multiply by 43 */
    SCG_PLL0MULTIPLY_BY44 = 28U,     /**< Multiply by 44 */
    SCG_PLL0MULTIPLY_BY45 = 29U,     /**< Multiply by 45 */
    SCG_PLL0MULTIPLY_BY46 = 30U,     /**< Multiply by 46 */
    SCG_PLL0MULTIPLY_BY47 = 31U,     /**< Multiply by 47 */
    SCG_PLL0MULTIPLY_BY48 = 32U,     /**< Multiply by 48 */
    SCG_PLL0MULTIPLY_BY49 = 33U,     /**< Multiply by 49 */
    SCG_PLL0MULTIPLY_BY50 = 34U,     /**< Multiply by 50 */
    SCG_PLL0MULTIPLY_BY51 = 35U,     /**< Multiply by 51 */
    SCG_PLL0MULTIPLY_BY52 = 36U,     /**< Multiply by 52 */
    SCG_PLL0MULTIPLY_BY53 = 37U,     /**< Multiply by 53 */
    SCG_PLL0MULTIPLY_BY54 = 38U,     /**< Multiply by 54 */
    SCG_PLL0MULTIPLY_BY55 = 39U,     /**< Multiply by 55 */
    SCG_PLL0MULTIPLY_BY56 = 40U,     /**< Multiply by 56 */
    SCG_PLL0MULTIPLY_BY57 = 41U,     /**< Multiply by 57 */
    SCG_PLL0MULTIPLY_BY58 = 42U,     /**< Multiply by 58 */
    SCG_PLL0MULTIPLY_BY59 = 43U,     /**< Multiply by 59 */
    SCG_PLL0MULTIPLY_BY60 = 44U,     /**< Multiply by 60 */
    SCG_PLL0MULTIPLY_BY61 = 45U,     /**< Multiply by 61 */
    SCG_PLL0MULTIPLY_BY62 = 46U,     /**< Multiply by 62 */
    SCG_PLL0MULTIPLY_BY63 = 47U      /**< Multiply by 63 */
} SCG_Pll0MultiplyType;
#endif

/**
 * @brief The interrupt enable/disable mask of SCG
 *
 */
typedef enum
{
	SCG_INTR_MASK_FIRC_CLK_ERR		= 1U,			/**< interrupt mask of FIRC clock error */
	SCG_INTR_MASK_SIRC_CLK_ERR		= (1U << 1),	/**< interrupt mask of SIRC clock error */
	SCG_INTR_MASK_FOSC_CLK_ERR		= (1U << 2),	/**< interrupt mask of FOSC clock error */
	SCG_INTR_MASK_SOSC_CLK_ERR		= (1U << 3),	/**< interrupt mask of SOSC clock error */
	SCG_INTR_MASK_PLL0_CLK_ERR		= (1U << 4) 	/**< interrupt mask of PLL0 clock error */
} SCG_IntrMaskType;


/** @brief FOSC initial definition, include register SCG_FOSCCSR/SCG_FOSCDIV/SCG_FOSCCFG. */
typedef struct
{
    bool bLock;                       /**< SCG_FOSCCSR[LK] bit, Write to set the register can be written or not */
    bool bCm;                         /**< SCG_FOSCCSR[CM] bit, Clock Monitor is enable */
    bool bCmre;                       /**< SCG_FOSCCSR[CMRE] bit, Clock Monitor Reset Enable
                                           0 Generates interrupt, 1 Generates rese         */
    bool bSten;                       /**< SCG_FOSCCSR[STEN] bit, Clock Stop in Stop modes */
    bool bBypass;                     /**< SCG_FOSCCFG[BYPASS] bit, Configures FOSC for bypassing the internal oscillator.*/
    SCG_AsyncClockDivType eDivH;      /**< SCG_FOSCDIV[DIVH] bit field definition. */
    SCG_AsyncClockDivType eDivM;      /**< SCG_FOSCDIV[DIVM] bit field definition. */
    SCG_AsyncClockDivType eDivL;      /**< SCG_FOSCDIV[DIVL] bit field definition. */
    uint8_t u8Eocv;                   /**< SCG_FOSCCFG[EOCV] bit, end of count value */
} SCG_FoscType;

/** @brief SIRC initial definition, include register SCG_ SIRCCSR/ SCG_ SIRCDIV/ SCG_ SIRCTCCFG. */
typedef struct
{
    bool bLock;                        /**< SCG_SIRCCSR[LK] bit, Write to set the register can be written or not  */
    bool bCm;                          /**< SCG_SIRCCSR[CM] bit, FIRC/SIRC Clock Monitor Enable */
    bool bTrEn;                        /**< SCG_SIRCCSR[TREN] bit, IRC software trim enable (auto trim) */
    bool bLpen;                        /**< SCG_SIRCCSR[LPEN] bit, Clock Stop Enable */
    bool bSten;                        /**< SCG_SIRCCSR[STEN] bit, Clock Standby Enable */
    SCG_AsyncClockDivType eDivH;       /**< SCG_SIRCDIV[DIVH] bit field definition.*/
    SCG_AsyncClockDivType eDivM;       /**< SCG_SIRCDIV[DIVM] bit field definition.*/
    SCG_AsyncClockDivType eDivL;       /**< SCG_SIRCDIV[DIVL] bit field definition.*/
    uint8_t u8TrimSrc;                 /**< SCG_SIRCTCFG[TRIMSRC] IRC clock auto trim reference clock source select.*/
} SCG_SircType;

/** @brief FIRC initial definition, include register SCG_ FIRCCSR/ SCG_ FIRCDIV/ SCG_ FIRCFG. */
typedef struct
{
    bool bLock;                        /**< SCG_FIRCCSR[VLD] bit, Read only, Clock is enabled and output clock is valid */
    bool bCm;                          /**< SCG_FIRCCSR[CM] bit, FIRC Clock Monitor Enable */
    bool bTrEn;                        /**< SCG_FIRCCSR[TREN] bit, IRC software trim enable (auto trim) */
    bool bSten;                        /**< SCG_FIRCCSR[STEN] bit, Clock Standby Enable */
    SCG_AsyncClockDivType eDivH;       /**< SCG_FIRCDIV[DIVH] bit field definition.*/
    SCG_AsyncClockDivType eDivM;       /**< SCG_FIRCDIV[DIVM] bit field definition.*/
    SCG_AsyncClockDivType eDivL;       /**< SCG_FIRCDIV[DIVL] bit field definition.*/
    uint8_t u8TrimSrc;                 /**< SCG_FIRCTCFG[TRIMSRC] IRC clock auto trim reference clock source select.*/
} SCG_FircType;

typedef struct
{
    bool bLock;                        /**< SIRC32KCSR[LK] bit, Write to set the register can be written or not  */
} SCG_Sirc32kType;

/** @brief SOSC definition, include register SCG_SOSCCFG. */
typedef struct
{
    bool bLock;                        /**< SCG_SOSCCSR[LK] bit, Write to set the register can be written or not.*/
    bool bBypass;                      /**< SCG_SOSCCSR[BYPASS] bit, Configures SOSC for bypassing the internal oscillator.*/
    bool bCm;                          /**< SCG_SOSCCSR[CM] bit,Clock Monitor enable.*/
    bool bCmre;                        /**< SCG_SOSCCSR[CMRE] bit, 1:Clock Monitor Reset, 0: interrupt*/
    uint8_t u8Eocv;                    /**< SCG_SOSCCFG[EOCV] bit, end of count value */
} SCG_SoscType;

/** @brief PLL0 definition, include register SCG_PLL0CSR/ SCG_PLL0DIV/SCG_PLL0CFG. */
typedef struct
{
    bool bLock;                        /**< SCG_PLL0CSR[LK] bit, Write to set the register can be written or not.*/
    bool bCm;                          /**< SCG_PLL0CSR[CM] bit,Clock Monitor enable.*/
    bool bCmre;                        /**< SCG_PLL0CSR[CMRE] bit, 1:Clock Monitor Reset, 0: interrupt*/
    bool bSten;                        /**< SCG_PLL0CSR[STEN] bit, Clock Standby Enable */
    SCG_Pll0SourceType eSrc;           /**< SCG_PLL0CFG[SOURCE] bit field definition.*/
    SCG_AsyncClockDivType eDivH;       /**< SCG_PLL0DIV[DIVH] bit field definition.*/
    SCG_AsyncClockDivType eDivM;       /**< SCG_PLL0DIV[DIVM] bit field definition.*/
    SCG_AsyncClockDivType eDivL;       /**< SCG_PLL0DIV[DIVL] bit field definition.*/
    SCG_Pll0PredivType ePrediv;        /**< SCG_PLL0CFG[PREDIV] bit field definition.*/
    SCG_Pll0MultiplyType eMult;        /**< SCG_PLL0CFG[MULT] bit field definition.*/
#if SCG_POSTDIV_SUPPORT
    SCG_Pll0PstdivType  ePstDiv;       /**< SCG_PLL0CFG[PSTDIV] bit field definition.*/
#endif
} SCG_Pll0Type;

/** @brief Current system clock definition, include register SCG_CCR. */
typedef struct
{
    bool bSysClkMonitor;               /**< SCG_CCR[SYSCLK_CME], System Clock monitor bit, this bit will be 1 mandatory.*/
    SCG_ClockSrcType eSrc;             /**< SCG_CCR[SCS], System Clock Source.*/
    SCG_ClockDivType eDivSlow;         /**< SCG_CCR[DIVSLOW], Slow Clock Divide Ratio.*/
    SCG_ClockDivType eDivBus;          /**< SCG_CCR[DIVBUS], Bus Clock Divide Ratio.*/
    SCG_ClockDivType eDivCore;         /**< SCG_CCR[DIVCORE], Core Clock Divide Ratio.*/
} SCG_ClockCtrlType;

/**
 * @brief The structure of the SCG processing handle
 *
 */
typedef struct _SCG_HandleType
{
    void (*pFoscClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< FOSC clock error interrupt callback */
	void (*pSircClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< SIRC clock error interrupt callback */
	void (*pFircClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< FIRC clock error interrupt callback */
	void (*pSoscClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< SOSC clock error interrupt callback */
	void (*pPll0ClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< Pll0 clock error interrupt callback */
} SCG_HandleType;

/**
 * @brief The configuration option for the SCG interrupt
 *
 */
typedef struct
{
    uint32_t u32InterruptMask;								    /**< interrupt enable mask */
    void (*pFoscClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< FOSC clock error interrupt callback */
	void (*pSircClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< SIRC clock error interrupt callback */
	void (*pFircClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< FIRC clock error interrupt callback */
	void (*pSoscClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< SOSC clock error interrupt callback */
	void (*pPll0ClkErrNotify)(struct _SCG_HandleType *pHandle);	/**< Pll0 clock error interrupt callback */
} SCG_InterruptType;

/**
 * @brief Enable SOSC
 *
 * @param pSoscConfig SOSC configuration
 * @return SCG_StatusType Function status
 */
SCG_StatusType SCG_EnableSOSC(const SCG_SoscType *const pSoscConfig);

/**
 * @brief Disable SOSC
 *
 * @return SCG_StatusType Function status
 */
SCG_StatusType SCG_DisableSOSC(void);

/**
 * @brief Enable FOSC clock with input configuration
 *
 * @param pFoscConfig FOSC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFOSC(const SCG_FoscType *const pFoscConfig);

/**
 * @brief Disable FOSC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFOSC(void);

/**
 * @brief Set SIRC configuration and configure SIRC DIV
 *
 * @param pSircConfig SIRC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetSIRC(const SCG_SircType *const pSircConfig);

/**
 * @brief Disable SIRC DIV and clear DIV configuration
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_ClearSIRC(void);

/**
 * @brief Enable SIRC32K
 *
 * @param pSirc32kConfig SIRC32K configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableSIRC32K(const SCG_Sirc32kType *const pSirc32kConfig);

/**
 * @brief Disable SIRC32K
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableSIRC32K(void);

/**
 * @brief Enable FIRC
 *
 * @param pFircConfig FIRC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFIRC(const SCG_FircType *const pFircConfig);

/**
 * @brief Disable FIRC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFIRC(void);

/**
 * @brief Enable PLL0
 *
 * @param pPll0Config PLL0 configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnablePLL0(const SCG_Pll0Type *const pPll0Config);

/**
 * @brief Disable PLL0
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisablePLL0(void);

/**
 * @brief Set system run time clock and related CORE/BUS/SLOW clock.
 *
 * @param pSysClkConfig pointer to the clockCtrlType structure data instance,which defined for system clock selection.
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetClkCtrl(const SCG_ClockCtrlType *const pSysClkConfig);

/**
 * @brief Get clock frequency
 *
 * @param eScgClockName Clock source type
 * @return uint32_t frequency value
 */
uint32_t SCG_GetScgClockFreq(const SCG_ClkSrcType eScgClockName);

/**
 * @brief Select clock out source
 *
 * @param eClkoutSel clock out source
 */
void SCG_SetClkOut(const SCG_ClockoutSrcType eClkoutSel);

/**
 * @brief Select NVM clock source
 *
 * @param eNvmClkSrc NVM clock source
 * @return uint32_t function status
 **/
SCG_StatusType SCG_SetNvmClk(const SCG_NvmClkSrcType eNvmClkSrc);

/**
 * @brief Switch system clock source
 *
 * @param eClock selected clock source
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SwitchSystemClock(const SCG_ClockSrcType eClock);

/**
 * @brief Clock source De-init
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_Deinit(void);

/**
 * @brief  Set clock error interrupt.
 * @param pScgHandle: Scg handle
 * @param  pIntrStruct: pointer to interrupt configuration,
 */
void SCG_InterruptInit(SCG_HandleType* pScgHandle, const SCG_InterruptType *const pIntrStruct);

/**
 * @brief Clock error interrupt handler
 * @param pScgHandle: Scg handle
 */
void SCG_UserIRQHandler(SCG_HandleType* pScgHandle);

/** @}*/ /* module_driver_scg */

#endif

#endif
