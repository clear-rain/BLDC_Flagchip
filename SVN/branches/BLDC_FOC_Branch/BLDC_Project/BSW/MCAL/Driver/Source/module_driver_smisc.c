/**
 * @file module_driver_smisc.c
 * @author Flagchip
 * @brief SMISC driver source code
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

#include "module_driver_smisc.h"

#if SMISC_INSTANCE_COUNT > 0U


/* ################################################################################## */
/* ####################################### Macro #################################### */
#ifndef SMISC_DEV_ERROR_REPORT
#define SMISC_DEV_ERROR_REPORT	STD_OFF
#endif

#if SMISC_DEV_ERROR_REPORT == STD_ON
#define SMISC_ReportDevError(func, error) ReportDevError(SMISC_MODULE_ID, func, error)
#endif

/* ################################################################################## */
/* ################################ Local Variables ################################# */

/* ################################################################################## */
/* ######################### Global prototype Functions  ############################ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief set clock out. with clock out pin configure, the clock would be monitored.
 *        This Function may combined with SCG_sckout setting
 *        need to call SCG_SetClkOut,if clock out source set to SCG CLKOUT. *
 * @param pointer to smiscClkOut instance for clock out configuration
 */
void SMISC_SetClockout(SMISC_ClkoutType *pSmiscClkOut)
{
#if SMISC_DEV_ERROR_REPORT == STD_ON
	if (NULL == pSmiscClkOut)
	{
		SMISC_ReportDevError(SMISC_SET_CLOCK_OUT_ID, SMISC_E_PARAM_POINTER);
	}
	else
	{
#endif

	uint32_t u32Temp = SMISC->CHIPCTLR;

    /* configuration sequence
       1. Disable CLKOUTEN
       2. Set CLKOUTSEL
       3. Enable CLKOUTEN    */
    u32Temp &= ~(SMISC_CHIPCTLR_CLKOUTEN_MASK  |
                 SMISC_CHIPCTLR_CLKOUTDIV_MASK |
                 SMISC_CHIPCTLR_CLKOUTSEL_MASK);
    SMISC_HWA_SetChipCtrl(u32Temp);

    u32Temp |= SMISC_CHIPCTLR_CLKOUTSEL(pSmiscClkOut->eSource);
    u32Temp |= SMISC_CHIPCTLR_CLKOUTDIV(pSmiscClkOut->eDivider);
    SMISC_HWA_SetChipCtrl(u32Temp);

    u32Temp |= SMISC_CHIPCTLR_CLKOUTEN(pSmiscClkOut->bEnable);
    SMISC_HWA_SetChipCtrl(u32Temp);

#if SMISC_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Set SEC, INTM, EIM, ERM, DMA clock enable.
 *        These 5 peripheral is control separately.
 * @param pSysCgc: pointer to SysCgc instance for clock gate configuration
 */
void SMISC_SetClockGate(SMISC_SysCgcType *pSysCgc)
{
#if SMISC_DEV_ERROR_REPORT == STD_ON
	if (NULL == pSysCgc)
	{
		SMISC_ReportDevError(SMISC_SET_CLOCK_CGC_ID, SMISC_E_PARAM_POINTER);
	}
	else
	{
#endif

	uint32_t u32Temp = (uint32_t)SMISC->SYSCGC;
    u32Temp &= ~(SMISC_SYSCGC_CGCISM_MASK  |
                 SMISC_SYSCGC_CGCSEC_MASK  |
                 SMISC_SYSCGC_CGCINTM_MASK |
                 SMISC_SYSCGC_CGCEIM_MASK  |
                 SMISC_SYSCGC_CGCERM_MASK  |
                 SMISC_SYSCGC_CGCDMA_MASK  |
#if SMISC_ROM_CLOCK_GATING_SUPPORT
                 SMISC_SYSCGC_CGCROM_MASK  |
#endif
                 SMISC_SYSCGC_CGCMAP_MASK
                );
    u32Temp |= SMISC_SYSCGC_CGCISM(pSysCgc->bEnableIsm);
    u32Temp |= SMISC_SYSCGC_CGCSEC(pSysCgc->bEnableSec);
    u32Temp |= SMISC_SYSCGC_CGCINTM(pSysCgc->bEnableIntm);
    u32Temp |= SMISC_SYSCGC_CGCEIM(pSysCgc->bEnableEim);
    u32Temp |= SMISC_SYSCGC_CGCERM(pSysCgc->bEnableErm);
    u32Temp |= SMISC_SYSCGC_CGCDMA(pSysCgc->bEnableDma);
    u32Temp |= SMISC_SYSCGC_CGCMAP(pSysCgc->bEnableMap);
#if SMISC_ROM_CLOCK_GATING_SUPPORT
    u32Temp |= SMISC_SYSCGC_CGCROM(pSysCgc->bEnableRom);
#endif

    SMISC_HWA_SetSysCgc(u32Temp);

#if SMISC_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief set trace clock.
 * Divider output clock = Divider input clock * [(TRACEFRAC+1)/(TRACEDIV+1)].
 * @param bEnable: SMISC_TRACECLK[TRACEDIVEN]  trace divider bEnable.
 * @param u8Divider: SMISC_TRACECLK[TRACEDIV] trace clock divider setting.
 * @param u8Frac: SMISC_TRACECLK[TRACEFRAC].
 */
void SMISC_SetTraceClockConfig(bool bEnable, uint8_t u8Divider, uint8_t u8Frac)
{
    uint32_t u32Temp = 0U;
    /* disable divider    */
    SMISC_HWA_DisableTraceClkDiv();

    /* set divider value   */
    u32Temp = SMISC_TRACECLKDIV_TRACEDIVEN(bEnable) |
              SMISC_TRACECLKDIV_TRACEDIV(u8Divider) |
              SMISC_TRACECLKDIV_TRACEFRAC(u8Frac);

    SMISC_HWA_SetTraceClkDiv(u32Temp);
}

/**
 * @brief set always on clock source configuration include AON32K, RTC, AONCLK clock.
 * 
 * @param pAonclkSrcType pointer to AONCLKSR instance for AON clock source configuration
 */
void SMISC_SetAonClkSrc( SMISC_AONCLKSRType *pAonclkSrcType)
{
#if SMISC_DEV_ERROR_REPORT == STD_ON
	if (NULL == pAonclkSrcType)
	{
		SMISC_ReportDevError(SMISC_SET_AON_CLOCK_ID, SMISC_E_PARAM_POINTER);
	}
	else
	{
#endif

	uint32_t u32Temp = 0U;
    u32Temp = SMISC->AONCLKSR;

    u32Temp &= ~(uint32_t)(SMISC_AONCLKSR_AONCLKSEL_MASK |
#if SMISC_ALON32KSOURCE_SELECT_SUPPORT
                           SMISC_AONCLKSR_AON32KCLKSEL_MASK |
#endif
                           SMISC_AONCLKSR_RTCCLKSEL_MASK);
    u32Temp |= (uint32_t)(SMISC_AONCLKSR_AONCLKSEL(pAonclkSrcType->eAonSel) |
#if SMISC_ALON32KSOURCE_SELECT_SUPPORT
                          SMISC_AONCLKSR_AON32KCLKSEL(pAonclkSrcType->eAon32KSel) |
#endif
                          SMISC_AONCLKSR_RTCCLKSEL(pAonclkSrcType->eRtcSel));

    u32Temp &= ~(uint32_t)SMISC_AONCLKSR_AON1KCLKEN_MASK;
    if (pAonclkSrcType->eAonSel == SMISC_AON_SIRC32_1K)
    {
        u32Temp |= (uint32_t)SMISC_AONCLKSR_AON1KCLKEN_MASK;
    }
    else
    {
    }

    u32Temp &= ~(uint32_t)SMISC_AONCLKSR_SIRCDIV32KEN_MASK;
    if ((pAonclkSrcType->eAonSel == SMISC_AON_SIRCDIV_32K) ||
        (pAonclkSrcType->eAon32KSel == SMISC_AON32K_SIRCDIV_32K) ||
        (pAonclkSrcType->eRtcSel == SMISC_RTC_SIRCDIV_32K))
    {
        u32Temp |= (uint32_t)SMISC_AONCLKSR_SIRCDIV32KEN_MASK;
    }
    else
    {
    }

    SMISC_HWA_SetAonClkSr(u32Temp);

#if SMISC_DEV_ERROR_REPORT == STD_ON
	}
#endif
}

/**
 * @brief Report the clock source status and frequency configured in MCU run time.
 *        The clock frequency and status would change by clock set function.
 * @param eSmiscClockName: the SMISC clock source to query
 * @param pFrequency: frequency variable point to get the frequency value
 * @return true or false. This indicate the clock source status invalid or request clock source out of
 *         range.
 */
bool SMISC_GetSMISCClockFreq(SMISC_ClkSrcType eSmiscClockName,  uint32_t *pFrequency)
{
    bool bStatus = false;
    *pFrequency = 0U;
    uint8_t u8Temp = 0U;
    uint32_t u32TempRegVal = 0U;

#if SMISC_DEV_ERROR_REPORT == STD_ON
	if (NULL == pFrequency)
	{
		SMISC_ReportDevError(SMISC_GET_CLOCK_FREQ_ID, SMISC_E_PARAM_POINTER);
	}
	else if ((uint8_t)eSmiscClockName >= (uint8_t)SMISC_END_OF_CLOCKS)
	{
		SMISC_ReportDevError(SMISC_GET_CLOCK_FREQ_ID, SMISC_E_PARAM_OUT_RANGE);
	}
	else
	{
#endif

    u32TempRegVal = SMISC_HWA_GetAonClkSr();

    if(SMISC_AON_CLK == eSmiscClockName)
    {
    	u8Temp = (uint8_t)((u32TempRegVal & SMISC_AONCLKSR_AONCLKSEL_MASK) >> SMISC_AONCLKSR_AONCLKSEL_SHIFT);

    	if ( (uint8_t)SMISC_AON_SIRCDIV_128K == u8Temp )
    	{
    		bStatus = true;
    		*pFrequency = SMISC_AONCLK_128K;
    	}
    	else if ( (uint8_t)SMISC_AON_SIRC32K == u8Temp )
    	{
    		bStatus = true;
    		*pFrequency = SMISC_AONCLK_32K;
    	}
    	else if ( (uint8_t)SMISC_AON_SIRCDIV_32K == u8Temp )
    	{
            if ( 0U != (u32TempRegVal & SMISC_AONCLKSR_SIRCDIV32KEN_MASK) )
            {
        		bStatus = true;
        		*pFrequency = SMISC_AONCLK_32K;
            }
    	}
    	else
    	{
    		if ( 0U != (u32TempRegVal & SMISC_AONCLKSR_AON1KCLKEN_MASK) )
    		{
        		bStatus = true;
        		*pFrequency = SMISC_AONCLK_1K;
    		}
    	}
    }
#if SMISC_ALON32KSOURCE_SELECT_SUPPORT
    else if (SMISC_AON32K_CLK == eSmiscClockName)
    {
    	u8Temp = (uint8_t)((u32TempRegVal & SMISC_AONCLKSR_AON32KCLKSEL_MASK) >> SMISC_AONCLKSR_AON32KCLKSEL_SHIFT);
    	if ( (uint8_t)SMISC_AON32K_SIRCDIV_32K == u8Temp )
    	{
            if ( 0U != (u32TempRegVal & SMISC_AONCLKSR_SIRCDIV32KEN_MASK) )
            {
        		bStatus = true;
        		*pFrequency = SMISC_AONCLK_32K;
            }
    	}
    	else if ( (uint8_t)SMISC_AON32K_SIRC32K == u8Temp )
    	{
    		bStatus = true;
    		*pFrequency = SMISC_AONCLK_32K;
    	}
    	else if ( (uint8_t)SMISC_AON32K_SOSC32K == u8Temp )
    	{
    		bStatus = true;
    		*pFrequency = SMISC_AONCLK_SOSC_32K;
    	}
    	else
    	{
    		/* do nothing*/
    	}
    }
#endif
    else if (SMISC_RTC_CLK == eSmiscClockName)
    {
    	u8Temp = (uint8_t)((u32TempRegVal & SMISC_AONCLKSR_RTCCLKSEL_MASK) >> SMISC_AONCLKSR_RTCCLKSEL_SHIFT);
    	if ( (uint8_t)SMISC_RTC_FOSCDIVL == u8Temp )
    	{
    		*pFrequency = SCG_GetScgClockFreq(SCG_FOSCDIVL_CLK);
    		if (0U != *pFrequency)
    		{
        		bStatus = true;
    		}
    	}
    	else if ( (uint8_t)SMISC_RTC_SIRCDIV_32K == u8Temp )
    	{
    		if ( 0U != (u32TempRegVal & SMISC_AONCLKSR_SIRCDIV32KEN_MASK) )
    		{
        		bStatus = true;
        		*pFrequency = SMISC_AONCLK_32K;
    		}
    	}
    	else if ( (uint8_t)SMISC_RTC_SOSC == u8Temp )
    	{
    		bStatus = true;
    		*pFrequency = SMISC_AONCLK_SOSC_32K;
    	}
    	else
    	{
    		bStatus = true;
    		*pFrequency = SMISC_AONCLK_32K;
    	}
    }
    else
    {
    	/* do nothing */
    }

#if SMISC_DEV_ERROR_REPORT == STD_ON
	}
#endif

    return bStatus;
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
