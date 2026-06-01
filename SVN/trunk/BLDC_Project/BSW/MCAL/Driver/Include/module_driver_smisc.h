/**
 * @file module_driver_SMISC.h
 * @author Flagchip
 * @brief SMISC driver type definition and API
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

#ifndef _DRIVER_MODULE_DRIVER_SMISC_H_
#define _DRIVER_MODULE_DRIVER_SMISC_H_

#include "HwA_smisc.h"

#if SMISC_INSTANCE_COUNT > 0U

#include "module_driver_scg.h"

/**
 * @addtogroup module_driver_smisc
 * @{
 */

/**
 * @name  Smisc related clock frequency definition
 *
 * @{
 */
#define SMISC_AONCLK_128K      128000U
#define SMISC_AONCLK_32K        32000U
#define SMISC_AONCLK_SOSC_32K   32768U
#define SMISC_AONCLK_1K          1000U
#define SMISC_UID_REGISTERS_CNT     4U
/** @}*/

/**
 * @name  PCC API Service IDs
 *
 * @{
 */
#define SMISC_SET_CLOCK_OUT_ID    0x00U
#define SMISC_SET_CLOCK_CGC_ID    0x01U
#define SMISC_SET_AON_CLOCK_ID    0x02U
#define SMISC_GET_CLOCK_FREQ_ID   0x03U
/** @}*/

/**
 * @name  PCC Dev Error Code
 * @brief Error Code of calling PCC apis
 *
 * @{
 */
#define SMISC_E_PARAM_INSTANCE   			0x01U
#define SMISC_E_PARAM_POINTER   			0x02U
#define SMISC_E_PARAM_OUT_RANGE   			0x03U
/** @}*/

/** @brief SMISC instance number */
typedef enum
{
	SMISC_INSTANCE_0 = 0U,
	SMISC_INSTANCE_ERR
} SMISC_InstanceType;

/** @brief SMISC_CHIPCTLR[CKOUTSEL] SMISC clock out source definition. */
typedef enum
{
    SMISC_CLKOUT_SCG_CLKOUT     = 0U,     /**< SCG CLKOUT                                          */
    SMISC_CLKOUT_FOSC_DIVM_CLK  = 2U,     /**< FXOSC DIVBUS CLK                                    */
    SMISC_CLKOUT_SIRC_DIVM_CLK  = 4U,     /**< SIRC DIVBUS CLK                                     */
    SMISC_CLKOUT_FIRC_DIVM_CLK  = 6U,     /**< FIRC DIVBUS CLK                                     */
	SMISC_CLKOUT_CORE_CLK       = 7U,     /**< CORE CLK                                            */
    SMISC_CLKOUT_PLL0_DIVM_CLK  = 8U,     /**< SPLL DIVBUS CLK                                     */
	SMISC_CLKOUT_BUS_CLK        = 9U,     /**< BUS CLK                                            */
    SMISC_CLKOUT_AON_CLK        = 12U,    /**< AON_CLK as selected by SMISC_AONCLKS[AONCLKSEL]     */
    SMISC_CLKOUT_RTC_CLK        = 14U     /**< 32K_CLK as selected by SMISC_AONCLKS[RTCCLKSEL]  */
} SMISC_ClkoutSrcType;

/** @brief SMISC_CHIPCTLR[CKOUTSEL]  SMISC clock out divider definition. */
typedef enum
{
    SMISC_CLKOUT_DIV_BY1 = 0x0U,        /**< Divided by 1 */
    SMISC_CLKOUT_DIV_BY2 = 0x1U,        /**< Divided by 2 */
    SMISC_CLKOUT_DIV_BY3 = 0x2U,        /**< Divided by 3 */
    SMISC_CLKOUT_DIV_BY4 = 0x3U,        /**< Divided by 4 */
    SMISC_CLKOUT_DIV_BY5 = 0x4U,        /**< Divided by 5 */
    SMISC_CLKOUT_DIV_BY6 = 0x5U,        /**< Divided by 6 */
    SMISC_CLKOUT_DIV_BY7 = 0x6U,        /**< Divided by 7 */
    SMISC_CLKOUT_DIV_BY8 = 0x7U         /**< Divided by 8 */
} SMISC_ClkoutDivType;

/** @brief indicate the clock status for each clock source in clock tree list. */
typedef enum
{
    SMISC_CLOCK_UNDEFINE = 0U,                /**< Clock status undefined from power on  */
    SMISC_CLOCK_DISABLE  = 1U,                /**< clock source set as disabled  */
    SMISC_CLOCK_VALID    = 2U,                /**< clock set succeed  */
    SMISC_CLOCK_ERROR    = 3U,                /**< clock set failed  */
    SMISC_CLOCK_UNKNOWN  = 4U
} SMISC_ClockStatusDef;

/** @brief module clock status and frequency record structure */
typedef struct
{
    SMISC_ClockStatusDef eClkStatus;    /**< Indicate the clock status for each clock source in clock tree list. */
    uint32_t  u32Freq;                  /**< frequency value. */
} SMISC_ClockInfoType;

/** @brief data type for register SMISC_CHIPCTLR,mainly focus on CLKOUT setting  */
typedef struct
{
    bool bEnable;                        /**< SMISC ClockOut enable.          */
    SMISC_ClkoutSrcType  eSource;        /**< SMISC ClockOut source select.   */
    SMISC_ClkoutDivType  eDivider;       /**< SMISC ClockOut divide ratio.    */
} SMISC_ClkoutType;

/** @brief data type for register SMISC_SYSCGC, extra CGC for SEC, INTM, EIM, ERM, DMA  */
typedef struct
{
    bool bEnableIsm;      /**< SMISC_SYSCGC[CGCISM], Controls ISM clock gating.       */
    bool bEnableSec;      /**< SMISC_SYSCGC[CGCSEC], Controls SEC clock gating.       */
    bool bEnableIntm;     /**< SMISC_SYSCGC[CGCINTM], Controls CGCINTM clock gating.  */
    bool bEnableEim;      /**< EIM Clock Gating Control enable.     */
    bool bEnableErm;      /**< ERM Clock Gating Control enable.     */
    bool bEnableDma;      /**< DMA Clock Gating Control enable.     */
    bool bEnableMap;      /**< MAP Clock Gating Control enable.     */
#if SMISC_ROM_CLOCK_GATING_SUPPORT
    bool bEnableRom;      /**< ROM Clock Gating Control enable.     */
#endif
} SMISC_SysCgcType;

/** @brief data type for SMISC_AONCLKSR[32KAONCLKSEL], Set AON32K clock source  */
typedef enum
{
    SMISC_AON32K_RESERVE     = 0U,        /**< SMISC_AONCLKSR[32KAONCLKSEL]  RESERVE. W1C  */
    SMISC_AON32K_SIRCDIV_32K = 1U,        /**< SMISC_AONCLKSR[32KAONCLKSEL], SIRCDIV_32K.  */
    SMISC_AON32K_SOSC32K     = 2U,        /**< SMISC_AONCLKSR[32KAONCLKSEL], SOSC32K.      */
    SMISC_AON32K_SIRC32K     = 3U         /**< SMISC_AONCLKSR[32KAONCLKSEL], SIRC32K .     */
} SMISC_AON32KClkSelType;

/** @brief data type for SMISC_AONCLKSR[RTCCLKSEL], Set RTC clock source  */
typedef enum
{
    SMISC_RTC_FOSCDIVL    = 0U,          /**< SMISC_AONCLKSR[RTCCLKSEL], FOSCDIVL.     */
    SMISC_RTC_SIRCDIV_32K = 1U,          /**< SMISC_AONCLKSR[RTCCLKSEL], SIRCDIV_32K.  */
    SMISC_RTC_SOSC        = 2U,          /**< SMISC_AONCLKSR[RTCCLKSEL], SOSC32K .     */
    SMISC_RTC_SIRC32K     = 3U           /**< SMISC_AONCLKSR[RTCCLKSEL], SIRC32K .     */
} SMISC_RTCClkSelType;

/** @brief data type for SMISC_AONCLKSR[AONCLKSEL], Set Always on clock source  */
typedef enum
{
    SMISC_AON_SIRCDIV_128K = 0U,          /**< SMISC_AONCLKSR[AONCLKSEL], SIRCDIV_128K.*/
    SMISC_AON_SIRC32K      = 1U,          /**< SMISC_AONCLKSR[AONCLKSEL], SIRC32K.     */
    SMISC_AON_SIRCDIV_32K  = 2U,          /**< SMISC_AONCLKSR[AONCLKSEL], SIRCDIV_32K. */
    SMISC_AON_SIRC32_1K    = 3U           /**< SMISC_AONCLKSR[AONCLKSEL], SIRC32_1K.   */
} SMISC_AONClkSelType;

/** @brief SMISC clock source type for clock infomation querry  */
typedef enum
{
    SMISC_AON32K_CLK          = 0U,       /**< AON32K_CLK            */
    SMISC_RTC_CLK             = 1U,       /**< RTC_CLK               */
    SMISC_AON_CLK             = 2U,       /**< AON_CLK               */
    SMISC_TRACE_CLK           = 3U,       /**< TRACE_CLK             */
    SMISC_CLKOUT_CLK          = 4U,       /**< CLOCK_OUT_CLK         */
    SMISC_END_OF_CLOCKS       = 5U        /**< End of SMISC clocks   */
} SMISC_ClkSrcType;

/** @brief data type for register SMISC_AONCLKSR. */
typedef struct
{
    SMISC_AON32KClkSelType eAon32KSel;    /**< AON32K clock source select.  */
    SMISC_RTCClkSelType eRtcSel;          /**< RTC clock source select.     */
    SMISC_AONClkSelType eAonSel;          /**< AON clock source select.     */
} SMISC_AONCLKSRType;
/**
 * @brief data type for register SMISC_TRACECLKDICV.
 * clock for the trace clock is CPU core clock.
 * Divider output clock = Divider input clock * [(TRACEFRAC+1)/(TRACEDIV+1)].
 */
typedef struct
{
    bool      bEnable;         /**< Trace clock divider enable.         */
    uint8_t   u8Div;           /**< Trace clock divider divisor.        */
    bool      bDivFraction;    /**< Trace clock divider fraction.       */
} SMISC_TraceClkDivType;

/**
 * @brief set clock out. with clock out pin configure, 
 * the clock would be monitored.need to call SCG_SetClkOut,if clock out source set to SCG CLKOUT.
 * @param pSmiscClkOut: smiscClkOut instance for clock out configuration. 
 */
void SMISC_SetClockout(SMISC_ClkoutType *pSmiscClkOut);

/**
 * @brief Set SEC, INTM, EIM, ERM, DMA clock enable.
 *        These 5 peripheral is control separately.
 * @param pSysCgc: pointer to SysCgc instance for clock gate configuration
 */
void SMISC_SetClockGate(SMISC_SysCgcType *pSysCgc);

/**
 * @brief set always on clock source configuration include AON32K, RTC, AONCLK clock.
 * 
 * @param pAonclkSrcType pointer to AONCLKSR instance for AON clock source configuration
 */
void SMISC_SetAonClkSrc( SMISC_AONCLKSRType *pAonclkSrcType);

/**
 * @brief set trace clock.
 * Divider output clock = Divider input clock * [(TRACEFRAC+1)/(TRACEDIV+1)].
 * @param bEnable: SMISC_TRACECLK[TRACEDIVEN]  trace divider bEnable.
 * @param u8Divider: SMISC_TRACECLK[TRACEDIV] trace clock divider setting.
 * @param u8Frac: SMISC_TRACECLK[TRACEFRAC].
 */
void SMISC_SetTraceClockConfig(bool bEnable, uint8_t u8Divider, uint8_t u8Frac);

/**
 * @brief Report the clock source status and frequency configured in MCU run time.
 *        The clock frequency and status would change by clock set function.
 * @param eSmiscClockName: the SMISC clock source to query
 * @param pFrequency: frequency variable point to get the frequency value
 * @return true or false. This indicate the clock source status invalid or request clock source out of
 *         range.
 */
bool SMISC_GetSMISCClockFreq(SMISC_ClkSrcType eSmiscClockName,  uint32_t *pFrequency);

/** @}*/ /* module_driver_smisc */

#endif

#endif


