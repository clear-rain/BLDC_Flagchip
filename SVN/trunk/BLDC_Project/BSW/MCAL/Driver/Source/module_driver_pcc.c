/**
 * @file module_driver_pcc.c
 * @author Flagchip
 * @brief PCC driver source code
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

#include "module_driver_pcc.h"

#if PCC_INSTANCE_COUNT > 0U

/* ################################################################################## */
/* ####################################### Macro #################################### */
#ifndef PCC_DEV_ERROR_REPORT
#define PCC_DEV_ERROR_REPORT	STD_OFF
#endif

#if PCC_DEV_ERROR_REPORT == STD_ON
#define PCC_ReportDevError(func, error) ReportDevError(PCC_MODULE_ID, func, error)
#endif

/* ################################################################################## */
/* ################################### Type define ################################## */
/**
 * @brief PCC clock attribution.
 * @param u32RegOffset: the register offset base on PCC module base address 0x4006_5000h.
 * @param u8ClockProperty include clock domain and clock MUX information by bit filed setting.
 */
typedef struct
{
    uint32_t u32RegOffset;
    uint32_t u32ClockProperty;
} PCC_ClockMapType;

/**
 * @brief PCC peripheral clock index map to SCG clock source
 * @param ePccClkIndex: PCC peripheral clock index
 * @param eScgClkIndex SCG clock source
 */
typedef struct
{
    PCC_ClkGateSrcType ePccClkIndex;
    SCG_ClkSrcType eScgClkIndex;
} PCC_ClockIndexMap;

/***************** Local Variables *********************/
/**
 * @brief PCC clock index to SCG clock source map.
*/
static const PCC_ClockIndexMap s_tPccClocIndexkMap[PCC_MUX_MAX_NUMBER] =
{
    {PCC_CLKGATE_SRC_OFF, SCG_END_OF_CLOCKS},
    {PCC_CLKGATE_SRC_FOSCDIV, SCG_FOSCDIVH_CLK},
    {PCC_CLKGATE_SRC_SIRCDIV, SCG_SIRCDIVH_CLK},
    {PCC_CLKGATE_SRC_FIRCDIV, SCG_FIRCDIVH_CLK},
    {PCC_CLKGATE_SRC_RESERVE0, SCG_END_OF_CLOCKS},
    {PCC_CLKGATE_SRC_RESERVE1, SCG_END_OF_CLOCKS},
    {PCC_CLKGATE_SRC_PLL0DIV, SCG_PLL0DIVH_CLK},
    {PCC_CLKGATE_SRC_RESERVE2, SCG_END_OF_CLOCKS}
};


/* ################################################################################## */
/* ################################ Local Variables ################################# */
/**
 * @brief clock attribution map. defined according to FC4150 user manual Table 20. The peripherals PCC assignment.
 */
static const PCC_ClockMapType s_tPccClockMap[PCC_END_OF_CLOCKS] =
{
    {0x84,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},                                                          /**<  PCC clock property  PCC_CLK_DMA_MUX   */
    {0x98,  PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED}, /**<  PCC clock property  PCC_CLK_FTU3      */
    {0x9C,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVM_USED},        /**<  PCC clock property  PCC_CLK_ADC1      */
    {0xB0,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},        /**<  PCC clock property  PCC_CLK_FCSPI0   */
    {0xB4,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},        /**<  PCC clock property  PCC_CLK_FCSPI1   */
    {0xB8,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},        /**<  PCC clock property  PCC_CLK_FCSPI2   */
#if PCC_SPI3_SUPPORT
    {0xBC,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},        /**<  PCC clock property  PCC_CLK_FCSPI3   */
#endif
    {0xC4,  PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_PTIMER1   */
    {0xC8,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_CRC       */
    {0xD8,  PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_PTIMER0   */
    {0xDC,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},      /**<  PCC clock property  PCC_CLK_FCPIT0   */
    {0xE0,  PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED},   /**<  PCC clock property  PCC_CLK_FTU0   */
    {0xE4,  PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED},   /**<  PCC clock property  PCC_CLK_FTU1   */
    {0xE8,  PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED},   /**<  PCC clock property  PCC_CLK_FTU2   */
    {0xEC,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVM_USED},          /**<  PCC clock property  PCC_CLK_ADC0   */
    {0xF4,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_RTC    */
    {0xF8,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_CMU0   */
    {0xFC,  PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_CMU1   */
    {0x100, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVM_USED},    /**<  PCC clock property  PCC_CLK_AONTIMER0   */
#if PCC_TSTMP0_SUPPORT
	{0x108, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_TSTMP0 */
#endif
	{0x10C, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_CMU2   */
    {0x110, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_CMU3   */
#if PCC_CORDIC_SUPPORT
	{0x114, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_CORDIC */
#endif
#if PCC_FREQM_SUPPORT
	{0x118, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_FREQM  */
#endif
    {0x124, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_PORTA  */
    {0x128, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_PORTB  */
    {0x12C, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_PORTC  */
    {0x130, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_PORTD  */
    {0x134, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_PORTE  */
    {0x13C, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_WKU    */
#if PCC_I2S0_SUPPORT
	{0x150, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVM_USED},  /**<  PCC clock property  PCC_CLK_I2S0 */
#endif
#if PCC_I2S1_SUPPORT
	{0x154, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVM_USED},  /**<  PCC clock property  PCC_CLK_I2S1 */
#endif
#if PCC_FTU6_SUPPORT
    {0x158, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED}, /**<  PCC clock property  PCC_CLK_FTU6  */
#endif
#if PCC_FTU7_SUPPORT
	{0x15C, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED}, /**<  PCC clock property  PCC_CLK_FTU7   */
#endif  
    {0x16C, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCUART3  */
    {0x170, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCUART4  */
    {0x174, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCUART5  */
    {0x184, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},                              /**<  PCC clock property  PCC_CLK_FWM      */
    {0x198, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCIIC0   */
    {0x19C, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCIIC1   */
    {0x1A8, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCUART0  */
    {0x1AC, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCUART1  */
    {0x1B0, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVM_USED},   /**<  PCC clock property  PCC_CLK_FCUART2  */
    {0x1B8, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED},   /**<  PCC clock property  PCC_CLK_FTU4   */
    {0x1BC, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_FUNCCLK_MUXDIVH_USED | PCC_FUNCCLK_MUXDIVHPIN_USED},   /**<  PCC clock property  PCC_CLK_FTU5   */
    {0x1C0, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_LU0    */
    {0x1CC, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_CMP0   */
#if PCC_CMP1_SUPPORT
    {0x1D0, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_CMP1   */
#endif
#if PCC_CMP2_SUPPORT
	{0x1D4, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_CMP2   */
#endif
#if PCC_OSPI_SUPPORT
    {0x1D8, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE},       /**<  PCC clock property  PCC_CLK_OSPI   */
#endif
#if PCC_ENET_SUPPORT
    {0x1E0, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVH_USED},  /**<  PCC clock property  PCC_CLK_ENET      */
#endif
#if PCC_TSTMP1_SUPPORT
    {0x1F0, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE},        /**<  PCC clock property  PCC_CLK_TSTAMP1   */
#endif  
    {0x200, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVH_USED},   /**<  PCC clock property  PCC_CLK_CAN0  */
    {0x210, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVH_USED},   /**<  PCC clock property  PCC_CLK_CAN1  */
    {0x220, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVH_USED},   /**<  PCC clock property  PCC_CLK_CAN2  */
#if PCC_CAN3_SUPPORT
    {0x230, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVH_USED},   /**<  PCC clock property  PCC_CLK_CAN3  */
#endif
#if PCC_CAN4_SUPPORT
	{0x240, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVH_USED},   /**<  PCC clock property  PCC_CLK_CAN4  */
#endif
#if PCC_CAN5_SUPPORT
	{0x250, PCC_CLK_DOMAIN_CORE | PCC_CGC_AVAILABLE | PCC_MOUDULE_DIV_USED | PCC_FUNCCLK_MUXDIVH_USED},   /**<  PCC clock property  PCC_CLK_CAN5  */
#endif
	{0x260, PCC_CLK_DOMAIN_BUS  | PCC_CGC_AVAILABLE}  /**<  PCC clock property  PCC_CLK_HSM  */
};

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */

/* ################################################################################## */
/* ######################### Global prototype Functions  ############################ */

/* ################################################################################## */
/* ################################ Local Functions  ################################ */

/* ################################################################################## */
/* ################################ Global Functions ################################ */
/**
 * @brief get PCC function clock status and value.
 *
 * @param pcc_ClkSrcType eClockName: used for choose PCC clock source to query.
 */
uint32_t PCC_GetPccFunctionClock(const PCC_ClkSrcType eClockName)
{
    uint8_t u8DivVal;
    PCC_ClkGateSrcType eSelVal;
    uint32_t u32ScgClkIndex = 0U;
    uint32_t u32FunctionFreqVal = 0U;
    uint32_t u32RegVal, u32ScgClkDivIndex;
    const PCC_ClockMapType *pAttributeVal;

#if PCC_DEV_ERROR_REPORT == STD_ON
	if (eClockName >= PCC_END_OF_CLOCKS)
	{
		PCC_ReportDevError(PCC_GET_PCC_FUNCTION_CLOCK_ID, PCC_E_PARAM_OUT_RANGE);
	}
	else
	{
#endif

    /* Get peripheral PCC register value */
    u32RegVal = *((volatile uint32_t *)(PCC_BASE + s_tPccClockMap[eClockName].u32RegOffset));
    pAttributeVal = &s_tPccClockMap[eClockName];
    /* Check peripheral PCC is valid or not and peripheral have function clock or not */
    if ((PCC_CGC_MASK == (u32RegVal & PCC_CGC_MASK)) && (0U != (pAttributeVal->u32ClockProperty & PCC_PROPERTY_MUXDIV_ALL_MASK)))
    {
        eSelVal = (PCC_ClkGateSrcType)((uint8_t)PCC_GetSEL(u32RegVal));
        /* Get PCC divide value */
        if (PCC_MOUDULE_DIV_USED == (pAttributeVal->u32ClockProperty & PCC_MOUDULE_DIV_USED))
        {
            u8DivVal = (uint8_t)((uint8_t)PCC_GetDIV(u32RegVal) + 1U);
        }
        else
        {
            u8DivVal = 1U;
        }

        /* Get peripheral function clock source which is from SCG or TCLK */
        if (PCC_CLKGATE_SRC_OFF == eSelVal)
        {
            if (PCC_FUNCCLK_MUXDIVHPIN_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVHPIN_USED))
            {
                u32FunctionFreqVal = PCC_FTU_TCLK_FREQ;
            }
            else
            {
                u32FunctionFreqVal = 0U;
            }
        }
        else
        {
            if (PCC_FUNCCLK_MUXDIVH_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVH_USED))
            {
                u32ScgClkDivIndex = 0U;
            }
            else if (PCC_FUNCCLK_MUXDIVM_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVM_USED))
            {
                u32ScgClkDivIndex = 1U;
            }
            else if (PCC_FUNCCLK_MUXDIVL_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVL_USED))
            {
                u32ScgClkDivIndex = 2U;
            }
            else
            {
                u32ScgClkDivIndex = 0U;
            }
            u32ScgClkIndex = (uint32_t)s_tPccClocIndexkMap[eSelVal].eScgClkIndex + u32ScgClkDivIndex;
        }

        /* If clock source is valid, calculate peripheral function clock */
        if ((uint32_t)SCG_END_OF_CLOCKS != u32ScgClkIndex)
        {
            u32FunctionFreqVal = SCG_GetScgClockFreq((SCG_ClkSrcType)u32ScgClkIndex) / u8DivVal;
        }
    }
    else
    {
        u32FunctionFreqVal = 0U;
    }

#if PCC_DEV_ERROR_REPORT == STD_ON
	}
#endif

    return u32FunctionFreqVal;
}


/**
 * @brief get PCC interface clock status and value.
 *
 * @param pcc_ClkSrcType eClockName: used for choose PCC clock source to query.
 */
uint32_t PCC_GetPccInterfaceClock(const PCC_ClkSrcType eClockName)
{
    uint32_t u32InterfaceFreqVal = 0U;
    uint32_t u32AttributeVal = 0U;

#if PCC_DEV_ERROR_REPORT == STD_ON
	if (eClockName > PCC_END_OF_CLOCKS)
	{
		PCC_ReportDevError(PCC_GET_PCC_INTERFACE_CLOCK_ID, PCC_E_PARAM_OUT_RANGE);
	}
	else
	{
#endif

    u32AttributeVal = s_tPccClockMap[eClockName].u32ClockProperty;
    if (PCC_CLK_DOMAIN_BUS == (u32AttributeVal & PCC_CLK_DOMAIN_BUS))
    {
        u32InterfaceFreqVal = SCG_GetScgClockFreq(SCG_BUS_CLK);
    }
    else if (PCC_CLK_DOMAIN_CORE == (u32AttributeVal & PCC_CLK_DOMAIN_CORE))
    {
        u32InterfaceFreqVal = SCG_GetScgClockFreq(SCG_CORE_CLK);
    }
    else
    {
        u32InterfaceFreqVal = 0U;
    }

#if PCC_DEV_ERROR_REPORT == STD_ON
	}
#endif

    return u32InterfaceFreqVal;
}

/**
 * @brief set PCC one peripheral clock configuration.
 *
 * @param PCC_CtrlType* pConfig: the PCC initialize value point set by user.
 * @return PCC_StatusType pcc function status
 */
PCC_StatusType PCC_SetPcc(const PCC_CtrlType *const pConfig)
{
    PCC_StatusType eStatus = PCC_STATUS_CLOCK_INVALID;
    uint8_t u8DivVal;
    uint32_t u32ExceptRegVal, u32ScgClkDivIndex;
    uint32_t u32ScgClkIndex = 0U;
    uint32_t u32FreqVal = 0U;
    uint32_t u32FunctionFreqVal = 0U;
    uint32_t u32RegVal = 0U;
    const PCC_ClockMapType *pAttributeVal;

#if PCC_DEV_ERROR_REPORT == STD_ON
	if (NULL == pConfig)
	{
		PCC_ReportDevError(PCC_SET_PCC_ID, PCC_E_PARAM_POINTER);
	}
	else
	{
#endif

    pAttributeVal = &s_tPccClockMap[pConfig->eClockName];

    /* check peripheral clock domain to calculate module clock */
    if (PCC_CLK_DOMAIN_BUS == (pAttributeVal->u32ClockProperty & PCC_CLK_DOMAIN_BUS))
    {
        u32FreqVal = SCG_GetScgClockFreq(SCG_BUS_CLK);
    }
    else if (PCC_CLK_DOMAIN_CORE == (pAttributeVal->u32ClockProperty & PCC_CLK_DOMAIN_CORE))
    {
        u32FreqVal = SCG_GetScgClockFreq(SCG_CORE_CLK);
    }
    else
    {
        /* Do nothing */
    }

    if (0U == u32FreqVal)
    {
        /* Please call SCG function first */
        eStatus = PCC_STATUS_CLOCK_INVALID;
    }
    else
    {
    	eStatus = PCC_STATUS_SUCCESS;
    }

    if (PCC_STATUS_SUCCESS == eStatus)
    {
        /* Disable PCC gate */
        *((volatile uint32_t *)(PCC_BASE + pAttributeVal->u32RegOffset)) &= ~(uint32_t)(PCC_CGC_MASK);
        if (pConfig->bEn)
        {
            if (PCC_MOUDULE_DIV_USED == (pAttributeVal->u32ClockProperty & PCC_MOUDULE_DIV_USED))
            {
                u8DivVal = (uint8_t)((uint8_t)pConfig->eDivider + 1U);
                u32RegVal |= PCC_DIV(pConfig->eDivider);
            }
            else
            {
                u8DivVal = 1U;
            }

            if (0U != (pAttributeVal->u32ClockProperty & PCC_PROPERTY_MUXDIV_ALL_MASK))
            {
                u32RegVal |= PCC_SEL(pConfig->eClkSrc);
            }

            if (PCC_CGC_AVAILABLE == (pAttributeVal->u32ClockProperty & PCC_CGC_AVAILABLE))
            {
                /* Enable peripheral clock */
                u32RegVal |= PCC_CGC_MASK;
            }

            /* Configure PCC register */
            *((volatile uint32_t *)(PCC_BASE + pAttributeVal->u32RegOffset)) = u32RegVal;

            /* Get peripheral function clock source which is from SCG or TCLK */
            if (PCC_CLKGATE_SRC_OFF == pConfig->eClkSrc)
            {
                if (PCC_FUNCCLK_MUXDIVHPIN_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVHPIN_USED))
                {
                    u32FunctionFreqVal = PCC_FTU_TCLK_FREQ;
                }
                else
                {
                    u32FunctionFreqVal = 0U;
                    u8DivVal = 0U;
                }
            }
            else
            {
                if (PCC_FUNCCLK_MUXDIVH_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVH_USED))
                {
                    u32ScgClkDivIndex = 0U;
                }
                else if (PCC_FUNCCLK_MUXDIVM_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVM_USED))
                {
                    u32ScgClkDivIndex = 1U;
                }
                else if (PCC_FUNCCLK_MUXDIVL_USED == (pAttributeVal->u32ClockProperty & PCC_FUNCCLK_MUXDIVL_USED))
                {
                    u32ScgClkDivIndex = 2U;
                }
                else
                {
                    u32ScgClkDivIndex = 0U;
                }
                u32ScgClkIndex = (uint32_t)s_tPccClocIndexkMap[pConfig->eClkSrc].eScgClkIndex + u32ScgClkDivIndex;

                /* Calculate peripheral function clock */
                if ( ((uint32_t)SCG_END_OF_CLOCKS != u32ScgClkIndex) && (0U != u8DivVal) )
                {
                    u32FunctionFreqVal = SCG_GetScgClockFreq((SCG_ClkSrcType)u32ScgClkIndex) / u8DivVal;
                }
            }

            u32ExceptRegVal = u32RegVal;
        }
        else
        {
            /* Clear PCC register */
            *((volatile uint32_t *)(PCC_BASE + pAttributeVal->u32RegOffset)) = 0U;
            u32ExceptRegVal = 0U;
            u32FunctionFreqVal = 0U;
        }

        /* Check PCC register has been configured, If current CPU do not have permission to configure the PCC register, the except value
         * will not match the actual value */
        if ( (u32ExceptRegVal|PCC_UNUSED_MASK) != *((volatile uint32_t *)(PCC_BASE + pAttributeVal->u32RegOffset)) )
        {
            /* In this case, current core does not have permission to control the register */
            eStatus = PCC_STATUS_CONFIGURED_NOT_SUPPORT;
        }
        else if (u32FunctionFreqVal > 150000000U)
        {
            /* In this case, current function clock too high, must configured below 150M */
            eStatus = PCC_STATUS_CONFIGURED_NOT_SUPPORT;
        }
        else
        {
            /* do nothing */
        }
    }

#if PCC_DEV_ERROR_REPORT == STD_ON
    }
#endif

    return eStatus;
}

#endif


