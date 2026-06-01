/**
 * @file module_driver_scg.c
 * @author Flagchip
 * @brief SCG driver source code
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

#include "module_driver_scg.h"

#if SCG_INSTANCE_COUNT > 0U

/* ################################################################################## */
/* ####################################### Macro #################################### */
#define SCG_CheckClockAckStatus(x, timeout, returnVal) \
    while ((x) && (timeout > 0U))                      \
    {                                                  \
        timeout--;                                     \
    }                                                  \
    if (timeout != 0U)                                 \
    {                                                  \
        returnVal = SCG_STATUS_SUCCESS;                \
    }                                                  \
    else                                               \
    {                                                  \
        returnVal = SCG_STATUS_TIMEOUT;                \
    }

#define SCG_GetDivHClock(_clock_, input_freq, ouput_freq)               \
    {                                                                   \
        uint32_t u32DivRegVal;                                          \
                                                                        \
        u32DivRegVal = SCG_HWA_GetClockDiv(_clock_);                    \
        ouput_freq = SCG_CALCULATE_DIVH_FREQ(input_freq, u32DivRegVal); \
    }

#define SCG_GetDivMClock(_clock_, input_freq, ouput_freq)               \
    {                                                                   \
        uint32_t u32DivRegVal;                                          \
                                                                        \
        u32DivRegVal = SCG_HWA_GetClockDiv(_clock_);                    \
        ouput_freq = SCG_CALCULATE_DIVM_FREQ(input_freq, u32DivRegVal); \
    }

#define SCG_GetDivLClock(_clock_, input_freq, ouput_freq)               \
    {                                                                   \
        uint32_t u32DivRegVal;                                          \
                                                                        \
        u32DivRegVal = SCG_HWA_GetClockDiv(_clock_);                    \
        ouput_freq = SCG_CALCULATE_DIVL_FREQ(input_freq, u32DivRegVal); \
    }

/* ################################################################################## */
/* ################################ Local Variables ################################# */

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */
static uint32_t SCG_CalculatePll0Freq(const SCG_ClkSrcType eScgClockName);
static uint32_t SCG_CalculateSystemFreq(const SCG_ClkSrcType eScgClockName);
static uint32_t SCG_CalculateSircFreq(const SCG_ClkSrcType eScgClockName);
static uint32_t SCG_CalculateFircFreq(const SCG_ClkSrcType eScgClockName);
static uint32_t SCG_CalculateFoscFreq(const SCG_ClkSrcType eScgClockName);
static uint32_t SCG_CalculateClkOutFreq(void);

/* ################################################################################## */
/* ######################### Global prototype Functions  ############################ */

/* ################################################################################## */
/* ################################ Local Functions  ################################ */
static uint32_t SCG_CalculatePll0Freq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq, u32ClkFreq;
    uint8_t u8Temp, u8PreDiv;
    uint16_t u16Mult;

    if (true == SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL))
    {
        u8Temp = SCG_HWA_GetPllSrc(SCG_PLL0_CLOCK_SYMBOL);
        if (u8Temp == (uint8_t)SCG_PLL0SOURCE_FIRC)
        {

            u32ClkFreq = FIRC_CLOCK / 2U;
        }
        else
        {
            /* (u8Temp == (uint8_t)SCG_PLLSOURCE_FOSC) */
            u32ClkFreq = FOSC_FREQUENCY;
        }
        u8PreDiv = SCG_HWA_GetPllPrediv(SCG_PLL0_CLOCK_SYMBOL);
        u16Mult = SCG_HWA_GetPllMult(SCG_PLL0_CLOCK_SYMBOL);

#if SCG_POSTDIV_SUPPORT /* FC41501MS */
        u8Temp = SCG_HWA_GetPllPstDiv(SCG_PLL0_CLOCK_SYMBOL);
        /* PSTDIV = 0b/1b, Post-Divider divide 2 */
        if (u8Temp == 0U)
        {
            u8Temp = 1U;
        }

        u32ClkFreq = ((u32ClkFreq / (u8PreDiv + 1U) * (u16Mult + 16U)) >> u8Temp);
#else
        u32ClkFreq = (u32ClkFreq / (u8PreDiv + 1U) * (u16Mult + 16U) / 2U);
#endif

        if (SCG_PLL0_CLK == eScgClockName)
        {
            u32Freq = u32ClkFreq;
        }
        else if (SCG_PLL0DIVH_CLK == eScgClockName)
        {
            SCG_GetDivHClock(SCG_PLL0_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else if (SCG_PLL0DIVM_CLK == eScgClockName)
        {
            SCG_GetDivMClock(SCG_PLL0_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else if (SCG_PLL0DIVL_CLK == eScgClockName)
        {
            SCG_GetDivLClock(SCG_PLL0_CLOCK_SYMBOL, u32ClkFreq, u32Freq);
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateSystemFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq, u32ClkFreq;
    uint8_t u8Temp, u8DivCore, u8DivBus, u8DivSlow;

    u8Temp = SCG_HWA_GetSysClkSrc();

    if (SCG_CLOCK_SRC_FOSC == (SCG_ClockSrcType)u8Temp)
    {
        u32ClkFreq = FOSC_FREQUENCY;
    }
    else if (SCG_CLOCK_SRC_FIRC == (SCG_ClockSrcType)u8Temp)
    {
        u32ClkFreq = FIRC_CLOCK;
    }
    else if (SCG_CLOCK_SRC_PLL0 == (SCG_ClockSrcType)u8Temp)
    {
        u32ClkFreq = SCG_CalculatePll0Freq(SCG_PLL0_CLK);
    }
    else
    {
        u32ClkFreq = UNKNOWN_CLOCK;
    }

    u8DivCore = (uint8_t)(SCG_HWA_GetSysClkDivCore() + 1U);
    u8DivBus = (uint8_t)(SCG_HWA_GetSysClkDivBus() + 1U);
    u8DivSlow = (uint8_t)(SCG_HWA_GetSysClkDivSlow() + 1U);

    u32ClkFreq = (uint32_t)(u32ClkFreq / u8DivCore);

    if (SCG_CORE_CLK == eScgClockName)
    {
        u32Freq = u32ClkFreq;
    }
    else if (SCG_BUS_CLK == eScgClockName)
    {
        u32Freq = (uint32_t)(u32ClkFreq / u8DivBus);
    }
    else
    {
        /* (SCG_SLOW_CLK == eScgClockName) */
        u32Freq = (uint32_t)(u32ClkFreq / u8DivSlow);
    }

    return u32Freq;
}

static uint32_t SCG_CalculateSircFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq;

    if (SCG_SIRC_CLK == eScgClockName)
    {
        u32Freq = SIRC_CLOCK;
    }
    else if (SCG_SIRCDIVH_CLK == eScgClockName)
    {
        SCG_GetDivHClock(SCG_SIRC_CLOCK_SYMBOL, SIRC_CLOCK, u32Freq);
    }
    else if (SCG_SIRCDIVM_CLK == eScgClockName)
    {
        SCG_GetDivMClock(SCG_SIRC_CLOCK_SYMBOL, SIRC_CLOCK, u32Freq);
    }
    else if (SCG_SIRCDIVL_CLK == eScgClockName)
    {
        SCG_GetDivLClock(SCG_SIRC_CLOCK_SYMBOL, SIRC_CLOCK, u32Freq);
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateFircFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq;

    if (true == SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL))
    {
        if (SCG_FIRC_CLK == eScgClockName)
        {
            u32Freq = FIRC_CLOCK;
        }
        else if (SCG_FIRCDIVH_CLK == eScgClockName)
        {
            SCG_GetDivHClock(SCG_FIRC_CLOCK_SYMBOL, FIRC_CLOCK, u32Freq);
        }
        else if (SCG_FIRCDIVM_CLK == eScgClockName)
        {
            SCG_GetDivMClock(SCG_FIRC_CLOCK_SYMBOL, FIRC_CLOCK, u32Freq);
        }
        else if (SCG_FIRCDIVL_CLK == eScgClockName)
        {
            SCG_GetDivLClock(SCG_FIRC_CLOCK_SYMBOL, FIRC_CLOCK, u32Freq);
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateFoscFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq;

    if (true == SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL))
    {
        if (SCG_FOSC_CLK == eScgClockName)
        {
            u32Freq = FOSC_FREQUENCY;
        }
        else if (SCG_FOSCDIVH_CLK == eScgClockName)
        {
            SCG_GetDivHClock(SCG_FOSC_CLOCK_SYMBOL, FOSC_FREQUENCY, u32Freq);
        }
        else if (SCG_FOSCDIVM_CLK == eScgClockName)
        {
            SCG_GetDivMClock(SCG_FOSC_CLOCK_SYMBOL, FOSC_FREQUENCY, u32Freq);
        }
        else if (SCG_FOSCDIVL_CLK == eScgClockName)
        {
            SCG_GetDivLClock(SCG_FOSC_CLOCK_SYMBOL, FOSC_FREQUENCY, u32Freq);
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

static uint32_t SCG_CalculateClkOutFreq(void)
{
    uint8_t u8ClockoutSrc;
    uint32_t u32Freq;
    /* check clock out configuration */
    u8ClockoutSrc = SCG_HWA_GetClkOutSel();

    if ((uint8_t)SCG_CLOCKOUT_SRC_OFF == u8ClockoutSrc)
    {
        u32Freq = 0U;
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_FOSC == u8ClockoutSrc)
    {
        u32Freq = FOSC_FREQUENCY;
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_SIRC == u8ClockoutSrc)
    {
        u32Freq = SCG_CalculateSircFreq(SCG_SIRC_CLK);
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_FIRC == u8ClockoutSrc)
    {
        u32Freq = SCG_CalculateFircFreq(SCG_FIRC_CLK);
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_SOSC == u8ClockoutSrc)
    {
        u32Freq = SOSC_FREQUENCY;
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_PLL0 == u8ClockoutSrc)
    {
        u32Freq = SCG_CalculatePll0Freq(SCG_PLL0_CLK);
    }
    else if ((uint8_t)SCG_CLOCKOUT_SRC_SIRC32K == u8ClockoutSrc)
    {
        u32Freq = SIRC32K_CLOCK;
    }
    else
    {
        u32Freq = UNKNOWN_CLOCK;
    }

    return u32Freq;
}

/* ################################################################################## */
/* ################################ Global Functions ################################ */
/**
 * @brief Enable SOSC
 *
 * @param pSoscConfig SOSC configuration
 * @return SCG_StatusType Function status
 */
SCG_StatusType SCG_EnableSOSC(const SCG_SoscType *const pSoscConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (NULL == pSoscConfig)
    {
        SCG_ReportDevError(SCG_ENABLE_SOSC_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        /* configure recommend value */
        u32TempVal = (uint32_t)(SCG_SOSCCFG_EOCV(pSoscConfig->u8Eocv) |
                                SCG_SOSCCFG_GM_SEL(3U) |
                                SCG_SOSCCFG_CURPRG_SF(3U) |
                                SCG_SOSCCFG_CURPRG_COMP(3U));
        SCG_HWA_SetSoscCfg(u32TempVal);

        /* Unlock CSR register first */
        SCG_HWA_UnlockSoscCsr();

        /* Configure SOSC CSR register */
        u32TempVal = SCG_HWA_GetSoscCsr();
        u32TempVal &= ~(uint32_t)(SCG_SOSCCSR_BYPASS_MASK | SCG_SOSCCSR_CM_MASK | SCG_SOSCCSR_CMRE_MASK);
        u32TempVal |= SCG_SOSCCSR_BYPASS(pSoscConfig->bBypass);
        SCG_HWA_SetSoscCsr(u32TempVal);

        /* Enable SOSC*/
        SCG_HWA_EnableSosc();

        /* Wait SOSC valid */
        u32TempVal = SOSC_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_SOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            if (pSoscConfig->bCm)
            {
                SCG_HWA_EnableSoscClockMonitor();
            }

            if (pSoscConfig->bCmre)
            {
                SCG_HWA_EnableSoscClockMonitorReset();
            }

            if (pSoscConfig->bLock)
            {
                /* Lock CSR */
                SCG_HWA_LockSoscCsr();
            }
        }
        else
        {
            SCG_HWA_SetSoscCsr(0U);
        }

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eStatusVal;
}

/**
 * @brief Disable SOSC
 *
 * @return SCG_StatusType Function status
 */
SCG_StatusType SCG_DisableSOSC(void)
{
    SCG_StatusType eStatusVal;
    uint32_t u32TempVal;

    /* Unlock CSR register first */
    SCG_HWA_UnlockSoscCsr();

    /* Disable SOSC */
    SCG_HWA_DisableSosc();

    /* Wait SOSC valid */
    u32TempVal = SOSC_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_SOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Clear CSR register */
        SCG_HWA_SetSoscCsr(0U);
    }

    return eStatusVal;
}

/**
 * @brief Enable FOSC clock with input configuration
 *
 * @param pFoscConfig FOSC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFOSC(const SCG_FoscType *const pFoscConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal;
    uint32_t u32DivHClockFreq = 0U;
    uint32_t u32DivMClockFreq = 0U;
    uint32_t u32DivLClockFreq = 0U;
#if SCG_LPWDG_SUPPORT
    uint8_t u8MSBVal;
#endif

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFoscConfig)
    {
        SCG_ReportDevError(SCG_ENABLE_FOSC_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        /* Check DIV clock frequency is valid or not */
        if (SCG_ASYNC_CLOCK_DISABLE != pFoscConfig->eDivH)
        {
            u32DivHClockFreq = (uint32_t)(FOSC_FREQUENCY >> ((uint8_t)(pFoscConfig->eDivH) - 1U));
        }

        if (SCG_ASYNC_CLOCK_DISABLE != pFoscConfig->eDivM)
        {
            u32DivMClockFreq = (uint32_t)(FOSC_FREQUENCY >> ((uint8_t)(pFoscConfig->eDivM) - 1U));
        }

        if (SCG_ASYNC_CLOCK_DISABLE != pFoscConfig->eDivL)
        {
            u32DivLClockFreq = (uint32_t)(FOSC_FREQUENCY >> ((uint8_t)(pFoscConfig->eDivL) - 1U));
        }

        if ((u32DivHClockFreq > FOSC_DIVH_MAX_CLOCK) || (u32DivMClockFreq > FOSC_DIVM_MAX_CLOCK) || (u32DivLClockFreq > FOSC_DIVL_MAX_CLOCK))
        {
            eStatusVal = SCG_STATUS_PARAM_ERROR;
        }
        else
        {
            /* Disable FOSC DIVEN */
            SCG_HWA_DiableFoscDiv();
#if SCG_CLOCK_CONF_WAIT_ACK
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_FOSC_CLOCK_SYMBOL)) ==
                                     SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                    u32TempVal, eStatusVal) if (eStatusVal == SCG_STATUS_SUCCESS)
#endif
            {

                /* COMP_EN is setting to 1  COMP_EN must be 1 when using an external crystal */
                /* Configure GM to the max value, GM_SEL: 15U */
                u32TempVal = SCG_FOSCCFG_BYPASS(pFoscConfig->bBypass) | SCG_FOSCCFG_COMP_EN(!(pFoscConfig->bBypass)) |
                             SCG_FOSCCFG_EOCV(pFoscConfig->u8Eocv) | SCG_FOSCCFG_GM_SEL(15U) |
                             SCG_FOSCCFG_ALC_D(1U) | SCG_FOSCCFG_HYST_D(0U);
                SCG_HWA_SetFoscCfg(u32TempVal);

                /* Unlock CSR register */
                SCG_HWA_UnlockFoscCsr();

                /* Configure CSR register */
                u32TempVal = SCG_HWA_GetFoscCsr();
                u32TempVal &= ~(uint32_t)(SCG_FOSCCSR_STEN_MASK | SCG_FOSCCSR_CM_MASK | SCG_FOSCCSR_CMRE_MASK);
                u32TempVal |= SCG_FOSCCSR_STEN(pFoscConfig->bSten);
                SCG_HWA_SetFoscCsr(u32TempVal);

                /* Configure DIV value */
                u32TempVal = SCG_HWA_GetClockDiv(SCG_FOSC_CLOCK_SYMBOL);
                u32TempVal &= ~(uint32_t)(SCG_FOSCDIV_DIVL_MASK | SCG_FOSCDIV_DIVM_MASK | SCG_FOSCDIV_DIVH_MASK);
                u32TempVal |= (SCG_FOSCDIV_DIVH(pFoscConfig->eDivH) |
                               SCG_FOSCDIV_DIVM(pFoscConfig->eDivM) |
                               SCG_FOSCDIV_DIVL(pFoscConfig->eDivL));
                SCG_HWA_SetFoscDiv(u32TempVal);

                /* Enable FOSC */
                SCG_HWA_EnableFosc();

                /* Wait FOSC vaild */
                u32TempVal = FOSC_STABILIZATION_TIMEOUT;
                SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

                if (eStatusVal == SCG_STATUS_SUCCESS)
                {
                    /* Enable DIV */
                    SCG_HWA_EnableFoscDiv();

                    if (pFoscConfig->bCm)
                    {
                        SCG_HWA_EnableFoscClockMonitor();
                    }

                    if (pFoscConfig->bCmre)
                    {
                        SCG_HWA_EnableFoscClockMonitorReset();
                    }

                    if (pFoscConfig->bLock)
                    {
                        /* Lock FOSC CSR register */
                        SCG_HWA_LockFoscCsr();
                    }

                    /* Wait DIV[ACK] change to 1 */
#if SCG_CLOCK_CONF_WAIT_ACK
                    u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
                    SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_FOSC_CLOCK_SYMBOL)) !=
                                             SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                            u32TempVal, eStatusVal)
#endif

#if SCG_LPWDG_SUPPORT
                    /* if OSC >= 40M ,set 5, if OSC = 32M,set 10, if OSC = 24M, set 15, if OSC = 16M, set 20, if OSC = 8M, set 25*/
                    /* This is the protection measure during low power wake up, if SCG register not valid after the setting time, the chip will reset
                     * and will set clock error flag in RGM register */
                    u8MSBVal = ((FOSC_FREQUENCY / 8000000U) >= 5U) ? (uint8_t)5U : (uint8_t)((6U - (FOSC_FREQUENCY / 8000000U)) * 5U);
                    SCG_HWA_SetWKPWDG(u8MSBVal);
#endif
                }
                else
                {
                    /* Clear CSR configuration */
                    SCG_HWA_SetFoscCsr(0U);

                    /* Clear CFG configuration*/
                    SCG_HWA_SetFoscCfg(0U);

                    /* Clear DIV configuration*/
                    SCG_HWA_SetFoscDiv(0U);
                }
            }
        }

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif

    return eStatusVal;
}

/**
 * @brief Disable FOSC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFOSC(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;
    uint8_t u8ClkSrc;

    u8ClkSrc = SCG_HWA_GetSysClkSrc();
    if ((uint8_t)SCG_CLOCK_SRC_FOSC == u8ClkSrc)
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else if ((SCG_HWA_GetPllSrc(SCG_PLL0_CLOCK_SYMBOL) == (uint8_t)SCG_PLL0SOURCE_FOSC) && ((uint8_t)SCG_CLOCK_SRC_PLL0 == u8ClkSrc))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        /* do nothing */
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock CSR register */
        SCG_HWA_UnlockFoscCsr();

        /* Clear FOSC[EN] bit */
        SCG_HWA_DisableFosc();

        u32TempVal = CLOCK_OFF_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Clear CSR register */
            SCG_HWA_SetFoscCsr(0U);

            /* In order to avoid the DIV register value not cleared, Clear FOSC DIV register twice */
            SCG_HWA_SetFoscDiv(0U);
            SCG_HWA_SetFoscDiv(0U);
        }
    }

    return eStatusVal;
}

/**
 * @brief Set SIRC configuration and configure SIRC DIV
 *
 * @param pSircConfig SIRC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetSIRC(const SCG_SircType *const pSircConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal = 0U;
    uint16_t u16TrimDiv = 0U;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (NULL == pSircConfig)
    {
        SCG_ReportDevError(SCG_SET_SIRC_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        /* Unlock SIRC CSR register */
        SCG_HWA_UnlockSircCsr();

        /* Configure CSR register */
        u32TempVal = SCG_HWA_GetSircCsr();
        u32TempVal &= ~(uint32_t)(SCG_SIRCCSR_STEN_MASK | SCG_SIRCCSR_LPEN_MASK | SCG_SIRCCSR_TREN_MASK | SCG_SIRCCSR_TRUP_MASK | SCG_SIRCCSR_CM_MASK);
        u32TempVal |= (uint32_t)(SCG_SIRCCSR_TRUP(pSircConfig->bTrEn) |
                                 SCG_SIRCCSR_TREN(pSircConfig->bTrEn) |
                                 SCG_SIRCCSR_LPEN(pSircConfig->bLpen) |
                                 SCG_SIRCCSR_STEN(pSircConfig->bSten));
        SCG_HWA_SetSircCsr(u32TempVal);

        /* Disable SIRC DIV[EN] bit */
        SCG_HWA_DiableSircDiv();

#if SCG_CLOCK_CONF_WAIT_ACK
        u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_SIRC_CLOCK_SYMBOL)) ==
                                 SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                u32TempVal, eStatusVal)
        if (eStatusVal == SCG_STATUS_SUCCESS)
#else
        eStatusVal = SCG_STATUS_SUCCESS;
#endif
        {
            if (pSircConfig->bCm)
            {
                SCG_HWA_EnableSircClockMonitor();
            }

            if (pSircConfig->bLock)
            {
                /* lock CSR */
                SCG_HWA_LockSircCsr();
            }

            /* Configure SIRC DIV */
            u32TempVal = SCG_HWA_GetClockDiv(SCG_SIRC_CLOCK_SYMBOL);
            u32TempVal &= ~(uint32_t)(SCG_SIRCDIV_DIVL_MASK | SCG_SIRCDIV_DIVM_MASK | SCG_SIRCDIV_DIVH_MASK);
            u32TempVal |= (uint32_t)(SCG_SIRCDIV_DIVL(pSircConfig->eDivL) |
                                     SCG_SIRCDIV_DIVM(pSircConfig->eDivM) |
                                     SCG_SIRCDIV_DIVH(pSircConfig->eDivH));
            SCG_HWA_SetSircDiv(u32TempVal);

            /* Enable SIRC DIV */
            SCG_HWA_EnableSircDiv();
#if SCG_CLOCK_CONF_WAIT_ACK
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_SIRC_CLOCK_SYMBOL)) !=
                                     SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                    u32TempVal, eStatusVal)
#else
            eStatusVal = SCG_STATUS_SUCCESS;
#endif
            if (SCG_STATUS_SUCCESS != eStatusVal)
            {
                /* Clear SIRC DIV register */
                SCG_HWA_SetSircDiv(0U);
            }

            /* Set SIRCTCFG register */
            if (pSircConfig->bTrEn == true)
            {
                /*   set SIRCTCFG trim configuration    */
                if (pSircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_FOSC)
                {
                    /*   Trim clock source choose FOSC   */
                    u16TrimDiv = (uint16_t)(FOSC_FREQUENCY / 1000000U - 1U);
                }
                else if (pSircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_SOSC)
                {
                    /*   Trim clock source choose SOSC   */
                    u16TrimDiv = 0U;
                }
                else
                {
                    /* Do nothing */
                }
                u32TempVal = (uint32_t)(SCG_SIRCTCFG_TRIMSRC(pSircConfig->u8TrimSrc) | SCG_SIRCTCFG_TRIMDIV(u16TrimDiv));
                SCG_HWA_SetSircTcfg(u32TempVal);
            }
        }

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif

    return eStatusVal;
}

/**
 * @brief Disable SIRC DIV and clear DIV configuration
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_ClearSIRC(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;

    /* check SIRC is invalid, if invalid, do not configure SIRC */
    if (true != SCG_HWA_GetClockVliad(SCG_SIRC_CLOCK_SYMBOL))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock SIRC CSR register */
        SCG_HWA_UnlockSircCsr();

        /* Disable SIRC DIV[EN] bit */
        SCG_HWA_DiableSircDiv();

        /* Clear SIRC DIV register */
        SCG_HWA_SetSircDiv(0U);
    }

    return eStatusVal;
}

/**
 * @brief Enable SIRC32K
 *
 * @param pSirc32kConfig SIRC32K configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableSIRC32K(const SCG_Sirc32kType *const pSirc32kConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (NULL == pSirc32kConfig)
    {
        SCG_ReportDevError(SCG_ENABLE_SIRC32K_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        /* Unlock SIRC32K CSR register */
        SCG_HWA_UnlockSirc32kCsr();

        /* Enable SIRC32K */
        SCG_HWA_EnableSirc32kCsr();

        /* Wait SIRC32K valid */
        u32TempVal = SIRC_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_SIRC32K_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            if (pSirc32kConfig->bLock)
            {
                /* Lock SIRC32K CSR register */
                SCG_HWA_LockSirc32kCsr();
            }
        }

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eStatusVal;
}

/**
 * @brief Disable SIRC32K
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableSIRC32K(void)
{
    SCG_StatusType eStatusVal;
    uint32_t u32TempVal;

    /* Unlock SIRC32K CSR register */
    SCG_HWA_UnlockSirc32kCsr();

    /* Disable SIRC32K */
    SCG_HWA_DisableSirc32kCsr();

    /* Wait SIRC32K not valid */
    u32TempVal = SIRC_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_SIRC32K_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    return eStatusVal;
}

/**
 * @brief Enable FIRC
 *
 * @param pFircConfig FIRC configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnableFIRC(const SCG_FircType *const pFircConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal;
    uint16_t u16TrimDiv = 0U;
    uint32_t u32DivMClockFreq = 0U;
    uint32_t u32DivLClockFreq = 0U;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (NULL == pFircConfig)
    {
        SCG_ReportDevError(SCG_ENABLE_FIRC_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        /* Check DIV clock frequency is valid or not */
        if (SCG_ASYNC_CLOCK_DISABLE != pFircConfig->eDivM)
        {
            u32DivMClockFreq = (uint32_t)(FIRC_CLOCK >> ((uint8_t)(pFircConfig->eDivM) - 1U));
        }
        if (SCG_ASYNC_CLOCK_DISABLE != pFircConfig->eDivL)
        {
            u32DivLClockFreq = (uint32_t)(FIRC_CLOCK >> ((uint8_t)(pFircConfig->eDivL) - 1U));
        }

        if ((u32DivMClockFreq > FIRC_DIVM_MAX_CLOCK) || (u32DivLClockFreq > FIRC_DIVL_MAX_CLOCK))
        {
            eStatusVal = SCG_STATUS_PARAM_ERROR;
        }
        else
        {
            /* Disable FIRC div */
            SCG_HWA_DiableFircDiv();
#if SCG_CLOCK_CONF_WAIT_ACK
            /* Wait DIV[ACK] change to 0 */
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_FIRC_CLOCK_SYMBOL)) ==
                                     SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                    u32TempVal, eStatusVal)
            if (eStatusVal == SCG_STATUS_SUCCESS)
#endif
            {
                /* Unlock CSR register */
                SCG_HWA_UnlockFircCsr();

                /* Configure recommend value */
                SCG_HWA_SetFircCfg(SCG_FIRCCFG_CLKEN(3U));

                /* Configure CSR register */
                u32TempVal = SCG_HWA_GetFircCsr();
                u32TempVal &= ~(uint32_t)(SCG_FIRCCSR_STEN_MASK | SCG_FIRCCSR_TREN_MASK | SCG_FIRCCSR_TRUP_MASK | SCG_FIRCCSR_CM_MASK);
                u32TempVal |= (uint32_t)(SCG_FIRCCSR_TRUP(pFircConfig->bTrEn) | /*    configure TRUP and EN together with TREN setting   */
                                         SCG_FIRCCSR_TREN(pFircConfig->bTrEn) |
                                         SCG_FIRCCSR_STEN(pFircConfig->bSten));
                SCG_HWA_SetFircCsr(u32TempVal);

                /* Configure DIV value */
                u32TempVal = SCG_HWA_GetClockDiv(SCG_FIRC_CLOCK_SYMBOL);
                u32TempVal &= ~(uint32_t)(SCG_FIRCDIV_DIVL_MASK | SCG_FIRCDIV_DIVM_MASK | SCG_FIRCDIV_DIVH_MASK);
                u32TempVal |= (SCG_FIRCDIV_DIVH(pFircConfig->eDivH) | SCG_FIRCDIV_DIVM(pFircConfig->eDivM) |
                               SCG_FIRCDIV_DIVL(pFircConfig->eDivL));
                SCG_HWA_SetFircDiv(u32TempVal);

                /* Set CSR[EN] bit to 1 */
                SCG_HWA_EnableFirc();

                /* Wait FIRC valid */
                u32TempVal = FIRC_STABILIZATION_TIMEOUT;
                SCG_CheckClockAckStatus((false == SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

                if (eStatusVal == SCG_STATUS_SUCCESS)
                {
                    if (pFircConfig->bCm)
                    {
                        SCG_HWA_EnableFircClockMonitor();
                    }

                    if (pFircConfig->bLock)
                    {
                        /* lock CSR register */
                        SCG_HWA_LockFircCsr();
                    }

                    /* Enable DIV */
                    SCG_HWA_EnableFircDiv();

#if SCG_CLOCK_CONF_WAIT_ACK
                    /* Wait DIV[ACK] change to 1 */
                    u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
                    SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_FIRC_CLOCK_SYMBOL)) !=
                                             SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                            u32TempVal, eStatusVal)
#endif

                    /*   For clock auto trim, set TREN to True together with TRUP to True   */
                    if (pFircConfig->bTrEn == true)
                    {
                        /*   set FIRCTCFG trim configuration    */
                        if (pFircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_FOSC)
                        {
                            /*   Trim clock source choose FOSC   */
                            u16TrimDiv = (uint16_t)(FOSC_FREQUENCY / 1000000U - 1U);
                        }
                        else if (pFircConfig->u8TrimSrc == (uint8_t)SCG_IRC_TRIMSRC_SOSC)
                        {
                            /*   Trim clock source choose SOSC   */
                            u16TrimDiv = 0U;
                        }
                        else
                        {
                            /*   do nothing   */
                        }
                        u32TempVal = (uint32_t)(SCG_FIRCTCFG_TRIMSRC(pFircConfig->u8TrimSrc) | SCG_FIRCTCFG_TRIMDIV(u16TrimDiv));
                        SCG_HWA_SetFircTcfg(u32TempVal);
                    }
                    else
                    {
                        /*   Trim disabled, just using IC internal IRC trim value */
                    }
                }
                else
                {
                    /* Clear CSR configuration */
                    SCG_HWA_SetFircCsr(0U);

                    /* Clear DIV configuration*/
                    SCG_HWA_SetFircDiv(0U);
                }
            }
        }

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eStatusVal;
}

/**
 * @brief Disable FIRC
 *
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisableFIRC(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;
    uint8_t u8ClkSrc;

    u8ClkSrc = SCG_HWA_GetSysClkSrc();
    if ((uint8_t)SCG_CLOCK_SRC_FIRC == u8ClkSrc)
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else if ((SCG_HWA_GetPllSrc(SCG_PLL0_CLOCK_SYMBOL) == (uint8_t)SCG_PLL0SOURCE_FIRC) && ((uint8_t)SCG_CLOCK_SRC_PLL0 == u8ClkSrc))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        /* do nothing */
    }

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Unlock CSR register */
        SCG_HWA_UnlockFircCsr();

        /* Disable FIRC */
        SCG_HWA_DisableFirc();

        /* Wait FIRC not valid */
        u32TempVal = FIRC_STABILIZATION_TIMEOUT;
        SCG_CheckClockAckStatus((true == SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Clear CSR register */
            SCG_HWA_SetFircCsr(0U);

            /* In order to avoid the DIV register value not cleared, Clear FIRC DIV register twice */
            SCG_HWA_SetFircDiv(0U);
            SCG_HWA_SetFircDiv(0U);
        }
    }
    return eStatusVal;
}

/**
 * @brief Enable PLL0
 *
 * @param pPll0Config PLL0 configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_EnablePLL0(const SCG_Pll0Type *const pPll0Config)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal;
    uint32_t u32Freq, u32FeedBackFreq, u32VcoFreq;
    uint32_t u32DivHClockFreq = 0U;
    uint32_t u32DivMClockFreq = 0U;
    uint32_t u32DivLClockFreq = 0U;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (NULL == pPll0Config)
    {
        SCG_ReportDevError(SCG_ENABLE_PLL0_ID, SCG_E_PARAM_POINTER);
    }
    else if(1U == pPll0Config->ePrediv)
    {
    	SCG_ReportDevError(SCG_ENABLE_PLL0_ID, SCG_E_PARAM_OUT_RANGE);
    }
    else
    {
#endif

        if ((true != SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)) && (SCG_PLL0SOURCE_FOSC == pPll0Config->eSrc))
        {
            eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
        }
        else if ((true != SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)) && (SCG_PLL0SOURCE_FIRC == pPll0Config->eSrc))
        {
            eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
        }
        else if (true == SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL))
        {
            /* check pll is valid, if valid, do not configure PLL */
            eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
        }
        else
        {
            eStatusVal = SCG_STATUS_SUCCESS;
        }

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /*   PLL input is FOSC or FIRC clock/2  */
            u32Freq = (SCG_PLL0SOURCE_FOSC == pPll0Config->eSrc) ? (FOSC_FREQUENCY) : (FIRC_CLOCK / 2U);

            /* Check the PLL feedback clock range */
            u32FeedBackFreq = u32Freq / ((uint8_t)(pPll0Config->ePrediv) + 1U);
            if (u32FeedBackFreq < PLL0_FEEDBACK_CLK_MIN || u32FeedBackFreq > PLL0_FEEDBACK_CLK_MAX)
            {
                eStatusVal = SCG_STATUS_PARAM_ERROR;
            }
            else
            {
                /* Check the PLL VCO clock range */
                u32VcoFreq = u32FeedBackFreq * ((uint8_t)(pPll0Config->eMult) + 16U);

                if ((u32VcoFreq < PLL0_VCO_CLK_MIN) || (u32VcoFreq > PLL0_VCO_CLK_MAX))
                {
                    eStatusVal = SCG_STATUS_PARAM_ERROR;
                }
                else
                {
#if SCG_POSTDIV_SUPPORT
                    /* PSTDIV = 0b/1b, Post-Divider divide 2 */
                    u32TempVal = ((0U == (uint8_t)(pPll0Config->ePstDiv)) ? 1U : (uint32_t)(pPll0Config->ePstDiv));
                    u32Freq = (u32VcoFreq >> u32TempVal);
#else
                    /* Check the PLL out clock range */
                    u32Freq = u32VcoFreq / 2U;
#endif
                   if ( (u32Freq < PLL0_CLK_MIN) || (u32Freq > PLL0_CLK_MAX) )
                   {
                	   eStatusVal = SCG_STATUS_PARAM_ERROR;
                   }

                }
            }

            /* Check DIV clock frequency is valid or not */
            if (eStatusVal == SCG_STATUS_SUCCESS)
            {
                if (pPll0Config->eDivH != SCG_ASYNC_CLOCK_DISABLE)
                {
                    u32DivHClockFreq = (uint32_t)(u32Freq >> ((uint8_t)(pPll0Config->eDivH) - 1U));
                }
                if (pPll0Config->eDivM != SCG_ASYNC_CLOCK_DISABLE)
                {
                    u32DivMClockFreq = (uint32_t)(u32Freq >> ((uint8_t)(pPll0Config->eDivM) - 1U));
                }
                if (pPll0Config->eDivL != SCG_ASYNC_CLOCK_DISABLE)
                {
                    u32DivLClockFreq = (uint32_t)(u32Freq >> ((uint8_t)(pPll0Config->eDivL) - 1U));
                }

                if ((u32DivHClockFreq > PLL0_DIVH_MAX_CLOCK) || (u32DivMClockFreq > PLL0_DIVM_MAX_CLOCK) || (u32DivLClockFreq > PLL0_DIVL_MAX_CLOCK))
                {
                    eStatusVal = SCG_STATUS_PARAM_ERROR;
                }
            }
        }

        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Enable PLLDIV */
            SCG_HWA_DisablePllDiv(SCG_PLL0_CLOCK_SYMBOL);
#if SCG_CLOCK_CONF_WAIT_ACK
            /* Wait DIV[ACK] change to 0 */
            u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
            SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_PLL0_CLOCK_SYMBOL)) ==
                                     SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                    u32TempVal, eStatusVal) 
            if (eStatusVal == SCG_STATUS_SUCCESS)
#endif
            {
                /* unlock PLL CSR register */
                SCG_HWA_UnlockPllCsr(SCG_PLL0_CLOCK_SYMBOL);

                /* Configure PLLCFG register */
                SCG_HWA_SetPll0Csr(0U);
                u32TempVal = SCG_PLL0CFG_PREDIV(pPll0Config->ePrediv) |
                             SCG_PLL0CFG_MULT(pPll0Config->eMult) |
#if SCG_POSTDIV_SUPPORT
                             SCG_PLL0CFG_PSTDIV(pPll0Config->ePstDiv) |
#endif
                             SCG_PLL0CFG_SOURCE(pPll0Config->eSrc);
                SCG_HWA_SetPllCfg(SCG_PLL0_CLOCK_SYMBOL, u32TempVal);


                /* Configure PLLCSR register */
                u32TempVal = SCG_PLLCSR_STEN(pPll0Config->bSten);
                SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, u32TempVal);

                /* Configure PLLDIV */
                u32TempVal = SCG_HWA_GetClockDiv(SCG_PLL0_CLOCK_SYMBOL);
                u32TempVal &= ~(uint32_t)(SCG_PLLDIV_DIVL_MASK | SCG_PLLDIV_DIVM_MASK | SCG_PLLDIV_DIVH_MASK);
                u32TempVal |= (SCG_PLLDIV_DIVH(pPll0Config->eDivH) |
                               SCG_PLLDIV_DIVM(pPll0Config->eDivM) |
                               SCG_PLLDIV_DIVL(pPll0Config->eDivL));
                SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, u32TempVal);

                /* Set CSR[EN] bit to 1 */
                SCG_HWA_EnablePll(SCG_PLL0_CLOCK_SYMBOL);

                /* Wait PLL valid */
                u32TempVal = PLL0_STABILIZATION_TIMEOUT;
                SCG_CheckClockAckStatus((false == SCG_HWA_GetPllLocked(SCG_PLL0_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

                if (eStatusVal == SCG_STATUS_SUCCESS)
                {
                    /* Enable PLLDIV */
                    SCG_HWA_EnablePllDiv(SCG_PLL0_CLOCK_SYMBOL);

                    if (pPll0Config->bCm)
                    {
                        SCG_HWA_EnablePllClockMonitor(SCG_PLL0_CLOCK_SYMBOL);
                    }

                    if (pPll0Config->bCmre)
                    {
                        SCG_HWA_EnablePllClockMonitorReset(SCG_PLL0_CLOCK_SYMBOL);
                    }

                    if (pPll0Config->bLock)
                    {
                        /* lock CSR register */
                        SCG_HWA_LockPllCsr(SCG_PLL0_CLOCK_SYMBOL);
                    }

#if SCG_CLOCK_CONF_WAIT_ACK
                    /* Wait DIV[ACK] change to 1 */
                    u32TempVal = CLOCK_DIV_STABILIZATION_TIMEOUT;
                    SCG_CheckClockAckStatus((SCG_CHECK_DIV_ACK(SCG_HWA_GetClockDiv(SCG_PLL0_CLOCK_SYMBOL)) !=
                                             SCG_CLOCKDIV_DIV_ACK_MASK_SHIFT),
                                            u32TempVal, eStatusVal)
#endif
                }
                else
                {
                    /* Clear CFG configuration */
                    SCG_HWA_SetPllCfg(SCG_PLL0_CLOCK_SYMBOL, 0U);

                    /* Clear CSR configuration */
                    SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, 0U);

                    /* Clear DIV configuration*/
                    SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, 0U);
                }
            }
        }

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif

    return eStatusVal;
}

/**
 * @brief Disable PLL0
 *
 * @param pPll0Config PLL0 configuration
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_DisablePLL0(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;
    uint32_t u32TempVal;

    /* unlock PLL CSR register */
    SCG_HWA_UnlockPllCsr(SCG_PLL0_CLOCK_SYMBOL);

    /* Clear CFG configuration */
    SCG_HWA_SetPllCfg(SCG_PLL0_CLOCK_SYMBOL, 0U);

    /* Clear CSR configuration */
    SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, 0U);

    u32TempVal = CLOCK_OFF_STABILIZATION_TIMEOUT;
    SCG_CheckClockAckStatus((true == SCG_HWA_GetPllLocked(SCG_PLL0_CLOCK_SYMBOL)), u32TempVal, eStatusVal)

    if (eStatusVal == SCG_STATUS_SUCCESS)
    {
        /* Clear CSR register */
        SCG_HWA_SetPllCsr(SCG_PLL0_CLOCK_SYMBOL, 0U);

        /* In order to avoid the DIV register value not cleared, Clear PLL DIV register twice */
        SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, 0U);
        SCG_HWA_SetPllDiv(SCG_PLL0_CLOCK_SYMBOL, 0U);
    }

    return eStatusVal;
}

/**
 * @brief Set system run time clock and related CORE/BUS/SLOW clock.
 *
 * @param pSysClkConfig pointer to the clockCtrlType structure data instance,which defined for system clock selection.
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SetClkCtrl(const SCG_ClockCtrlType *const pSysClkConfig)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal, u32Freq = 0U, u32FreqCore, u32FreqBus, u32FreqSlow;
    uint8_t u8ClkSrc;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (NULL == pSysClkConfig)
    {
        SCG_ReportDevError(SCG_SET_CLOCK_CTRL_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        /* Switch clock source */
        eStatusVal = SCG_SwitchSystemClock(pSysClkConfig->eSrc);

        /* Check configuration */
        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            if (SCG_CLOCK_SRC_FOSC == pSysClkConfig->eSrc)
            {
                u32Freq = FOSC_FREQUENCY;
            }
            else if (SCG_CLOCK_SRC_FIRC == pSysClkConfig->eSrc)
            {
                u32Freq = FIRC_CLOCK;
            }
            else if (SCG_CLOCK_SRC_PLL0 == pSysClkConfig->eSrc)
            {
                u32Freq = SCG_CalculatePll0Freq(SCG_PLL0_CLK);
            }
            else
            {
                /* do nothing */
            }

            u32FreqCore = u32Freq / ((uint8_t)pSysClkConfig->eDivCore + 1U);
            u32FreqBus = u32FreqCore / ((uint8_t)pSysClkConfig->eDivBus + 1U);
            u32FreqSlow = u32FreqCore / ((uint8_t)pSysClkConfig->eDivSlow + 1U);
            if ((u32FreqCore > SYS_CORE_CLK_MAX) || (u32FreqBus > SYS_BUS_CLK_MAX) || (u32FreqSlow > SYS_SLOW_CLK_MAX))
            {
                eStatusVal = SCG_STATUS_PARAM_ERROR;
            }

            /* ERR_SCG_001 */
            if( (pSysClkConfig->eDivCore) == (pSysClkConfig->eDivBus) )
            {
                if( SCG_CLOCK_DIV_BY1 != (pSysClkConfig->eDivCore) )
                {
                    eStatusVal = SCG_STATUS_PARAM_ERROR;
                }
            }
        }

        /* Configure register */
        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            /* Switch system clock */
            SCG_HWA_SetSystemClock((uint8_t)pSysClkConfig->eSrc);

            /* Wait CCR update ready */
            u32TempVal = SCG_CLKSRC_STABILIZATION_TIMEOUT;
            u8ClkSrc = SCG_HWA_GetSysClkSrc();
            while ((SCG_HWA_GetSysClkUPRD() == false) && (u8ClkSrc != (uint8_t)pSysClkConfig->eSrc) && (u32TempVal > 0U))
            {
                u32TempVal--;
                u8ClkSrc = SCG_HWA_GetSysClkSrc();
            }
            if ((uint32_t)0U != u32TempVal)
            {
                /* Configure CCR register to select divider */
            	/* ERR_RCM_002(FC4150F1M_B) SCG_CCR_SYSCLK_CME will be set enable mandatory. */
                u32TempVal = (uint32_t)((uint32_t)SCG_CCR_SYSCLK_CME(1U) |
                                        (uint32_t)SCG_CCR_SCS(pSysClkConfig->eSrc) |
                                        (uint32_t)SCG_CCR_DIVCORE(pSysClkConfig->eDivCore) |
                                        (uint32_t)SCG_CCR_DIVBUS(pSysClkConfig->eDivBus) |
                                        (uint32_t)SCG_CCR_DIVSLOW(pSysClkConfig->eDivSlow));
                SCG_HWA_SetCCR(u32TempVal);

                u32TempVal = SCG_CLKSRC_STABILIZATION_TIMEOUT;
                while (((SCG_HWA_GetSysClkUPRD() == false)) && (u32TempVal > 0U))
                {
                    u32TempVal--;
                }

                if ((uint32_t)0U == u32TempVal)
                {
                    eStatusVal = SCG_STATUS_TIMEOUT;
                }
            }
            else
            {
                eStatusVal = SCG_STATUS_TIMEOUT;
            }
        }
#if SCG_DIVBUS_CHECK
        /* ERR_PMC_001 */
        if (eStatusVal == SCG_STATUS_SUCCESS)
        {
            if (((pSysClkConfig->eDivBus) != SCG_CLOCK_DIV_BY1) && ((pSysClkConfig->eDivBus) != SCG_CLOCK_DIV_BY2))
            {
                eStatusVal = SCG_STATUS_ERRTA_PMC_001;
            }
        }
#endif

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif

    return eStatusVal;
}

/**
 * @brief Get clock frequency
 *
 * @param eScgClockName Clock source type
 * @return uint32_t frequency value
 */
uint32_t SCG_GetScgClockFreq(const SCG_ClkSrcType eScgClockName)
{
    uint32_t u32Freq = 0U;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (eScgClockName >= SCG_END_OF_CLOCKS)
    {
        SCG_ReportDevError(SCG_GET_SCG_CLOCK_FREQ_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        if ((SCG_CORE_CLK == eScgClockName) ||
                (SCG_BUS_CLK == eScgClockName) ||
                (SCG_SLOW_CLK == eScgClockName))
        {
            u32Freq = SCG_CalculateSystemFreq(eScgClockName);
        }
        else if ((SCG_SIRC_CLK == eScgClockName) ||
                 (SCG_SIRCDIVH_CLK == eScgClockName) ||
                 (SCG_SIRCDIVM_CLK == eScgClockName) ||
                 (SCG_SIRCDIVL_CLK == eScgClockName))
        {
            u32Freq = SCG_CalculateSircFreq(eScgClockName);
        }
        else if ((SCG_FIRC_CLK == eScgClockName) ||
                 (SCG_FIRCDIVH_CLK == eScgClockName) ||
                 (SCG_FIRCDIVM_CLK == eScgClockName) ||
                 (SCG_FIRCDIVL_CLK == eScgClockName))
        {
            u32Freq = SCG_CalculateFircFreq(eScgClockName);
        }
        else if ((SCG_FOSC_CLK == eScgClockName) ||
                 (SCG_FOSCDIVH_CLK == eScgClockName) ||
                 (SCG_FOSCDIVM_CLK == eScgClockName) ||
                 (SCG_FOSCDIVL_CLK == eScgClockName))
        {
            u32Freq = SCG_CalculateFoscFreq(eScgClockName);
        }
        else if ((SCG_PLL0_CLK == eScgClockName) ||
                 (SCG_PLL0DIVH_CLK == eScgClockName) ||
                 (SCG_PLL0DIVM_CLK == eScgClockName) ||
                 (SCG_PLL0DIVL_CLK == eScgClockName))
        {
            u32Freq = SCG_CalculatePll0Freq(eScgClockName);
        }
        else if (SCG_SIRC32K_CLK == eScgClockName)
        {
            u32Freq = SIRC32K_CLOCK;
        }
        else if (SCG_SOSC_CLK == eScgClockName)
        {
            u32Freq = SOSC_FREQUENCY;
        }
        else if (SCG_SCG_CLKOUT_CLK == eScgClockName)
        {
            u32Freq = SCG_CalculateClkOutFreq();
        }
        else
        {
            u32Freq = UNKNOWN_CLOCK;
        }

        if (UNKNOWN_CLOCK == u32Freq)
        {
            u32Freq = 0U;
        }
#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return u32Freq;
}

/**
 * @brief Select clock out source
 *
 * @param eClkoutSel clock out source
 */
void SCG_SetClkOut(const SCG_ClockoutSrcType eClkoutSel)
{
#if SCG_DEV_ERROR_REPORT == STD_ON
    if (eClkoutSel > SCG_CLOCKOUT_SRC_SIRC32K)
    {
        SCG_ReportDevError(SCG_SET_CLOCK_OUT_ID, SCG_E_PARAM_OUT_RANGE);
    }
    else
    {
#endif

        SCG_HWA_SetClkOutSel((uint8_t)eClkoutSel);

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief Select NVM clock source
 *
 * @param eNvmClkSrc NVM clock source
 * @return uint32_t function status
 **/
SCG_StatusType SCG_SetNvmClk(const SCG_NvmClkSrcType eNvmClkSrc)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;

    if ((true != SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)) && (eNvmClkSrc == SCG_NVMCLK_SRC_FIRC))
    {
        eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
    }
    else
    {
        SCG_HWA_SetNvmClk(((uint32_t)1U << eNvmClkSrc));
        eStatusVal = SCG_STATUS_SUCCESS;
    }
    return eStatusVal;
}

/**
 * @brief Switch system clock source
 *
 * @param eClock selected clock source
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_SwitchSystemClock(const SCG_ClockSrcType eClock)
{
    SCG_StatusType eStatusVal = SCG_STATUS_PARAM_ERROR;
    uint32_t u32TempVal;
    uint8_t u8ClkSrc;

#if SCG_DEV_ERROR_REPORT == STD_ON
    if (SCG_CLOCK_SRC_NONE == eClock)
    {
        SCG_ReportDevError(SCG_SWITCH_SYS_CLOCK_ID, SCG_E_PARAM_OUT_RANGE);
    }
    else
    {
#endif

        if ((true != SCG_HWA_GetClockVliad(SCG_FOSC_CLOCK_SYMBOL)) && (SCG_CLOCK_SRC_FOSC == eClock))
        {
            eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
        }
        else if ((true != SCG_HWA_GetClockVliad(SCG_FIRC_CLOCK_SYMBOL)) && (SCG_CLOCK_SRC_FIRC == eClock))
        {
            eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
        }
        else if ((true != SCG_HWA_GetClockVliad(SCG_PLL0_CLOCK_SYMBOL)) && (SCG_CLOCK_SRC_PLL0 == eClock))
        {
            eStatusVal = SCG_STATUS_SEQUENCE_ERROR;
        }
        else
        {
            u8ClkSrc = SCG_HWA_GetSysClkSrc();
            if ((uint8_t)eClock != u8ClkSrc)
            {
                SCG_HWA_SetSystemClock((uint8_t)eClock);

                u32TempVal = SCG_CLKSRC_STABILIZATION_TIMEOUT;
                while (((SCG_HWA_GetSysClkUPRD() == false) || (u8ClkSrc != (uint8_t)eClock)) && (u32TempVal > 0U))
                {
                    u32TempVal--;
                    u8ClkSrc = SCG_HWA_GetSysClkSrc();
                }

                if ((uint32_t)0U == u32TempVal)
                {
                    eStatusVal = SCG_STATUS_TIMEOUT;
                }
            }
            eStatusVal = SCG_STATUS_SUCCESS;
        }
#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return eStatusVal;
}

/**
 * @brief Clock source De-init
 * @param pScgHandle: Scg handle
 * @return SCG_StatusType function status
 */
SCG_StatusType SCG_Deinit(void)
{
    SCG_StatusType eStatusVal = SCG_STATUS_SUCCESS;

    SCG_FircType tFircCfg =
    {
        .bLock = false,
        .bCm = false,
        .bTrEn = false,
        .bSten = false,
        .eDivH = SCG_ASYNCCLOCKDIV_BY1,
        .eDivM = SCG_ASYNCCLOCKDIV_BY2,
        .eDivL = SCG_ASYNCCLOCKDIV_BY4,
        .u8TrimSrc = (uint8_t)SCG_IRC_TRIMSRC_RESERVE0
    };

    if (SCG_HWA_GetSysClkSrc() != (uint8_t)SCG_CLOCK_SRC_FIRC)
    {
        eStatusVal = SCG_SwitchSystemClock(SCG_CLOCK_SRC_FIRC);
        if (SCG_STATUS_SEQUENCE_ERROR == eStatusVal)
        {
            eStatusVal = SCG_EnableFIRC(&tFircCfg);
            if (SCG_STATUS_TIMEOUT != eStatusVal)
            {
                eStatusVal = SCG_SwitchSystemClock(SCG_CLOCK_SRC_FIRC);
            }
        }
    }

    if (SCG_STATUS_SUCCESS == eStatusVal)
    {
        /* Disable all clock source */
        (void)SCG_DisablePLL0();
        (void)SCG_DisableFOSC();
        (void)SCG_DisableSOSC();
        (void)SCG_DisableSIRC32K();
    }

    return eStatusVal;
}

/**
 * @brief  Set clock error interrupt.
 * @param pScgHandle: Scg handle
 * @param  pIntrStruct: pointer to interrupt configuration,
 */

void SCG_InterruptInit(SCG_HandleType *pScgHandle, const SCG_InterruptType *const pIntrStruct)
{
    uint32_t u32Temp = 0U;
#if SCG_DEV_ERROR_REPORT == STD_ON
    if ((NULL == pScgHandle) || (NULL == pIntrStruct))
    {
        SCG_ReportDevError(SCG_SCG_INTERRUPT_INIT_ID, SCG_E_PARAM_POINTER);
    }
    else
    {
#endif

        u32Temp = SCG_HWA_GetFircCsr();
        if ((0U != ((uint32_t)SCG_INTR_MASK_FIRC_CLK_ERR & (pIntrStruct->u32InterruptMask))) &&
            (SCG_FIRCCSR_CM_MASK == (u32Temp & SCG_FIRCCSR_CM_MASK)))
        {
            pScgHandle->pFircClkErrNotify = pIntrStruct->pFircClkErrNotify;
        }

        u32Temp = SCG_HWA_GetFoscCsr();
        if ((0U != ((uint32_t)SCG_INTR_MASK_FOSC_CLK_ERR & (pIntrStruct->u32InterruptMask))) &&
            (SCG_FOSCCSR_CM_MASK == (u32Temp & (SCG_FOSCCSR_CM_MASK | SCG_FOSCCSR_CMRE_MASK))))
        {
            pScgHandle->pFoscClkErrNotify = pIntrStruct->pFoscClkErrNotify;
        }

        u32Temp = SCG_HWA_GetSircCsr();
        if ((0U != ((uint32_t)SCG_INTR_MASK_SIRC_CLK_ERR & (pIntrStruct->u32InterruptMask))) &&
            (SCG_SIRCCSR_CM_MASK == (u32Temp & SCG_SIRCCSR_CM_MASK)))
        {
            pScgHandle->pSircClkErrNotify = pIntrStruct->pSircClkErrNotify;
        }

        u32Temp = SCG_HWA_GetSoscCsr();
        if ((0U != ((uint32_t)SCG_INTR_MASK_SOSC_CLK_ERR & (pIntrStruct->u32InterruptMask))) &&
            (SCG_SOSCCSR_CM_MASK == (u32Temp & (SCG_SOSCCSR_CM_MASK | SCG_SOSCCSR_CMRE_MASK))))
        {
            pScgHandle->pSoscClkErrNotify = pIntrStruct->pSoscClkErrNotify;
        }

        u32Temp = SCG_HWA_GetPll0Csr();
        if ((0U != ((uint32_t)SCG_INTR_MASK_PLL0_CLK_ERR & (pIntrStruct->u32InterruptMask))) &&
            (SCG_PLL0CSR_CM_MASK == (u32Temp & (SCG_PLL0CSR_CM_MASK | SCG_PLL0CSR_CMRE_MASK))))
        {
            pScgHandle->pPll0ClkErrNotify = pIntrStruct->pPll0ClkErrNotify;
        }

#if SCG_DEV_ERROR_REPORT == STD_ON
    }
#endif
}

/**
 * @brief Clock error interrupt handler
 * @param pScgHandle: Scg handle
 */

void SCG_UserIRQHandler(SCG_HandleType *pScgHandle)
{
    if ((true == SCG_HWA_CheckAndClearFircClkErr()) && (NULL != pScgHandle->pFircClkErrNotify))
    {
        pScgHandle->pFircClkErrNotify(pScgHandle);
    }

    if ((true == SCG_HWA_CheckAndClearSircClkErr()) && (NULL != pScgHandle->pSircClkErrNotify))
    {
        pScgHandle->pSircClkErrNotify(pScgHandle);
    }

    if ((true == SCG_HWA_CheckAndClearFoscClkErr()) && (NULL != pScgHandle->pFoscClkErrNotify))
    {
        pScgHandle->pFoscClkErrNotify(pScgHandle);
    }

    if ((true == SCG_HWA_CheckAndClearSoscClkErr()) && (NULL != pScgHandle->pSoscClkErrNotify))
    {
        pScgHandle->pSoscClkErrNotify(pScgHandle);
    }

    if ((true == SCG_HWA_CheckAndClearPll0ClkErr()) && (NULL != pScgHandle->pPll0ClkErrNotify))
    {
        pScgHandle->pPll0ClkErrNotify(pScgHandle);
    }
}

#endif
