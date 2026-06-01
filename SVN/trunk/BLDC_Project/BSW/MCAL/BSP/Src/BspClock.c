#include "BspClock.h"

static const PCC_CtrlType BSP_PCC_Config[] =
{
	{PCC_CLK_PORTA, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_PORTB, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_PORTC, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_PORTD, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_PORTE, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	
	{PCC_CLK_FCIIC0, true, PCC_CLKGATE_SRC_FIRCDIV, PCC_CLK_DIV_BY1},
	
	{PCC_CLK_FCSPI0, true, PCC_CLKGATE_SRC_FIRCDIV,PCC_CLK_DIV_BY1},
	{PCC_CLK_FCSPI1, true, PCC_CLKGATE_SRC_FIRCDIV,PCC_CLK_DIV_BY1},
	{PCC_CLK_FCSPI2, true, PCC_CLKGATE_SRC_FIRCDIV,PCC_CLK_DIV_BY1},
	{PCC_CLK_DMA_MUX, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},

    {PCC_CLK_FTU3, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_FTU2, true, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1},
	{PCC_CLK_FTU1, true, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1},
	{PCC_CLK_FTU0, true, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1},
	{PCC_CLK_ADC0, true, PCC_CLKGATE_SRC_FIRCDIV, PCC_CLK_DIV_BY1},
	{PCC_CLK_ADC1, true, PCC_CLKGATE_SRC_FIRCDIV, PCC_CLK_DIV_BY1},
	
	{PCC_CLK_CAN1, true, PCC_CLKGATE_SRC_FIRCDIV, PCC_CLK_DIV_BY2},
	{PCC_CLK_CAN2, true, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1},
	{PCC_CLK_PTIMER1, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_HSM, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_RTC, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_AONTIMER, false, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
	{PCC_CLK_WKU, true, PCC_CLKGATE_SRC_OFF, PCC_CLK_DIV_BY1},
};
/* Global handle of clock  */
SCG_HandleType g_tScgHandle;


/*   PCBA external oscillator value, these macro is user defined.                   */
/*   FOSC/SOSC clock need to manually configuration according to  PCBA XTAL value
 *   in SOSC/FOSc configuration.
 *   Current default value is the XTAL value on EVB board.                          */

static void Bsp_SMISC_SetClockout(void);
static void Bsp_SMISC_SetSysCgc(void);
static void Bsp_Fosc_ClockErrorInterrupt_CallBack(SCG_HandleType* pHandle);
static void Bsp_Pll0_ClockErrorInterrupt_CallBack(SCG_HandleType* pHandle);


void Bsp_SCG_Init(void)
{
	SCG_StatusType eRetVal;

	/* Enable SIRC DIV, DIVH=DIV1(12M), DIVM=DIV4(3M), DIVL=DIV4(3M) */
    SCG_SircType tSircStruct =
	{
		.bLock = false,
		.bCm = false,
		.bTrEn = false,
		.bLpen = false,
		.bSten = false,
		.eDivH = SCG_ASYNCCLOCKDIV_BY1,
		.eDivM = SCG_ASYNCCLOCKDIV_BY4,
		.eDivL = SCG_ASYNCCLOCKDIV_BY4,
		.u8TrimSrc = (uint8_t)SCG_IRC_TRIMSRC_RESERVE0
	};
    eRetVal = SCG_SetSIRC(&tSircStruct);

	/* Enable SIRC32K  */
    SCG_Sirc32kType tSirc32kCfg =
    {
    	.bLock = false
    };
    eRetVal = SCG_EnableSIRC32K(&tSirc32kCfg);

	/* SOSC is disabled */

	/* Enable FOSC clock, DIVH=DIV1(16M), DIVM=DIV4(4M), DIVL=DIV8(2M) */
	SCG_FoscType tFoscStruct =
	{
		.bLock = false,
		.bCm = true,
		.bCmre = false,
		.bSten = false,
		.bBypass = false,
		.eDivH = SCG_ASYNCCLOCKDIV_BY1,
		.eDivM = SCG_ASYNCCLOCKDIV_BY4,
		.eDivL = SCG_ASYNCCLOCKDIV_BY8,
		.u8Eocv = 0x4
	};
	eRetVal = SCG_EnableFOSC(&tFoscStruct);

    /*   Enable PLL0 clock frequency    */
    /*   input frequency as FOSC, currently on board is 16Mhz
         pre-divider is 4, multiplier is 60.
         output clock is 16/4*60/2=120Mhz             */
	SCG_Pll0Type tPll0Cfg =
	{
		.bCm = true,
		.bCmre =false,
		.bLock = false,
		.bSten = true,
	    .eSrc = SCG_PLL0SOURCE_FOSC,

#if SCG_POSTDIV_SUPPORT  /* FC41501MS PLL0 is different */
		/* output clock is 24/8*100/2=150Mhz */
	    .ePrediv = SCG_PLL0PREDIV_BY8,
		.eMult =  84U,
		.ePstDiv = SCG_PLLPSTDIV_BY2,
#else
	    .ePrediv = SCG_PLL0PREDIV_BY4,
	    .eMult =  SCG_PLL0MULTIPLY_BY60,
#endif
	    .eDivH = SCG_ASYNCCLOCKDIV_BY1,
	    .eDivM = SCG_ASYNCCLOCKDIV_BY2,
		.eDivL = SCG_ASYNCCLOCKDIV_BY4
	};
	eRetVal = SCG_EnablePLL0(&tPll0Cfg);

	/* Set system clock  */
	SCG_ClockCtrlType tClockCtrlCfg =
	{
	    .bSysClkMonitor = false,
		.eSrc = SCG_CLOCK_SRC_PLL0,
		.eDivCore = SCG_CLOCK_DIV_BY1,
		.eDivBus = SCG_CLOCK_DIV_BY2,
		.eDivSlow = SCG_CLOCK_DIV_BY8,
	};
	eRetVal = SCG_SetClkCtrl(&tClockCtrlCfg);

	/* Enable FIRC clock, DIVH=DIV1(96M), DIVM=DIV2(48M), DIVL=DIV4(24M) */
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
    eRetVal = SCG_EnableFIRC(&tFircCfg);

	/* Set Nvm clock source */
	eRetVal = SCG_SetNvmClk(SCG_NVMCLK_SRC_FIRC);

	/* Set clock out  */
	SCG_SetClkOut(SCG_CLOCKOUT_SRC_FOSC);

    /**
     *   SCG clock error interrupt configuration(optional)
     *   clock monitor should enable and clock monitor reset should disable
     */
	SCG_InterruptType tClockErrIntrConfig =
	{
	    .u32InterruptMask = (uint32_t)( SCG_INTR_MASK_FOSC_CLK_ERR|SCG_INTR_MASK_PLL0_CLK_ERR ),
		.pFircClkErrNotify = NULL,
		.pSircClkErrNotify = NULL,
		.pSoscClkErrNotify = NULL,
		.pFoscClkErrNotify = Bsp_Fosc_ClockErrorInterrupt_CallBack,
		.pPll0ClkErrNotify = Bsp_Pll0_ClockErrorInterrupt_CallBack
	};
    SCG_InterruptInit(&g_tScgHandle, &tClockErrIntrConfig);

    PROCESS_UNUSED_VAR(eRetVal)
}

void Bsp_PCC_Init(void)
{
    uint8_t i;

    for (i = 0U; i < sizeof(BSP_PCC_Config) / sizeof(PCC_CtrlType); i++)
    {
        PCC_SetPcc(&BSP_PCC_Config[i]);
    }
}

static void Bsp_SMISC_Init(void)
{
    SMISC_AONCLKSRType tAONCLKStruct =
    {
        .eAon32KSel = SMISC_AON32K_SIRC32K,
		.eAonSel = SMISC_AON_SIRCDIV_128K,
//		.eAonSel = SMISC_AON_SIRC32K,
		.eRtcSel = SMISC_RTC_SIRCDIV_32K
    };

	Bsp_SMISC_SetSysCgc();
    SMISC_SetAonClkSrc(&tAONCLKStruct);
}

static void Bsp_SMISC_SetClockout(void)
{
    SMISC_ClkoutType smiscClkOut = {0};
    smiscClkOut.eDivider = SMISC_CLKOUT_DIV_BY4;
    smiscClkOut.bEnable = true;
    smiscClkOut.eSource = SMISC_CLKOUT_SCG_CLKOUT;
    SMISC_SetClockout(&smiscClkOut);
}

static void Bsp_SMISC_SetSysCgc(void)
{
    SMISC_SysCgcType tSmiscSysCgc = {0};
    tSmiscSysCgc.bEnableIsm = false;
    tSmiscSysCgc.bEnableSec = true;
    tSmiscSysCgc.bEnableIntm = false;
    tSmiscSysCgc.bEnableEim = false;
    tSmiscSysCgc.bEnableErm = false;
    tSmiscSysCgc.bEnableDma = true;
    tSmiscSysCgc.bEnableMap = true;
    SMISC_SetClockGate(&tSmiscSysCgc);
}

void Bsp_ClockInit(void)
{
	SCG_Deinit();

	Bsp_SCG_Init();

    Bsp_PCC_Init();

    Bsp_SMISC_Init();

	Bsp_SMISC_SetClockout();

	Bsp_SMISC_SetSysCgc();
}

static void Bsp_Fosc_ClockErrorInterrupt_CallBack(SCG_HandleType* pHandle)
{
	PROCESS_UNUSED_VAR(pHandle)
}

static void Bsp_Pll0_ClockErrorInterrupt_CallBack(SCG_HandleType* pHandle)
{
	PROCESS_UNUSED_VAR(pHandle)
}





