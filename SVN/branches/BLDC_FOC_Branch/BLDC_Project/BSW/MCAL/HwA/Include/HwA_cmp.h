/**
 * @file HwA_cmp.h
 * @author Flagchip
 * @brief CMP hardware access layer
 * @version 2.0.0
 * @date 2024-08-30
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-08-30    Flagchip0126  N/A          First version
*********************************************************************************/


#ifndef _HWA_CMP_H_
#define _HWA_CMP_H_

#include "device_header.h"

#if CMP_INSTANCE_COUNT > 0U

/**
 * @defgroup HwA_cmp HwA_cmp
 * @ingroup module_driver_cmp
 * @{
 */

/********* Local typedef ************/

/**
 * @brief The instance index of the CMP mode
 */
typedef enum
{
    CMP_MODE_DISABLE                 = 0U,   /**< CMP function mode is disable */
    CMP_MODE_CONTINUOUS              = 1U,   /**< CMP function mode is continuous */
    CMP_MODE_SAMPLE_NONFILTER_EXTCLK = 2U,   /**< CMP function mode is sampled,non-filtered mode 1*/
    CMP_MODE_SAMPLE_NONFILTER_INTCLK = 3U,   /**< CMP function mode is sampled,non-filtered mode 2*/
    CMP_MODE_SAMPLE_FILTER_EXTCLK    = 4U,   /**< CMP function mode is sampled,filtered mode 1*/
    CMP_MODE_SAMPLE_FILTER_INTCLK    = 5U,   /**< CMP function mode is sampled,filtered mode 2*/
    CMP_MODE_WINDOW                  = 6U,   /**< CMP function mode is windowed mode */
    CMP_MODE_WINDOW_RESAMPLE         = 7U,   /**< CMP function mode is windowed,re-sampled mode */
    CMP_MODE_WINDOW_FILTER           = 8U,   /**< CMP function mode is windowed,filtered mode */
#ifdef CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE
    CMP_MODE_CHANNEL_SCAN            = 9U    /**< CMP channel scan mode */
#endif
} CMP_ModeSelType;

/**
 * @brief The instance index of the CMP peripheral
 */
typedef enum
{
    CMP_INSTANCE_0 = 0U,   /**< CMP instance 0 is selected */
    CMP_INSTANCE_1 = 1U,   /**< CMP instance 1 is selected */
    CMP_INSTANCE_2 = 2U    /**< CMP instance 2 is selected */
} CMP_InstanceType;

/**
 * @brief The instance index of the CMP DAC enable select
 */
typedef enum
{
    CMP_DACENABLE_DCR  = 0U,  /**< CMP Dac is enabled by DCR[DAC_EN] */
    CMP_DACENABLE_CCR0 = 1U   /**< CMP Dac is enabled by CCR0[EN] */
} CMP_DacEnableSrcType;

/**
 * @brief The instance index of the CMP output invert
 */
typedef enum
{
    CMP_NON_INVERT = 0U,  /**< CMP output do not Invert*/
    CMP_INVERT     = 1U   /**< CMP output  Invert */
} CMP_InvertType;

/**
 * @brief The instance index of the CMP output select
 */
typedef enum
{
    CMP_FILTEROUT   = 0U,  /**< CMP filter output  */
    CMP_UNFILTEROUT = 1U   /**< CMP Unfilter output  */
} CMP_OutSelectType;

/**
 * @brief The instance index of the CMP window level
 */
typedef enum
{
    CMP_HOLD    = 0U,  /**< CMP output hold when window close  */
    CMP_USERDEF = 1U   /**< CMP output userdefine when window close  */
} CMP_OutWinLevelType;

/**
 * @brief The instance index of the window output under userdefine CMP window level
 */
typedef enum
{
    CMP_OUTWIN_0 = 0U,   /**< CMP window output is 0  */
    CMP_OUTWIN_1 = 1U    /**< CMP window output is 1  */
} CMP_OutWinLevel_UserDefType;


/**
 * @brief The instance index of the CMP Event caused window close
 */
typedef enum
{
    CMP_RISINGEDGE  = 0U,   /**< CMP output event RisingEdge causes window close  */
    CMP_FALLINGEDGE = 1U,   /**< CMP output event FallingEdge causes window close  */
    CMP_BOTHEDGES   = 2U,   /**< CMP output event bothEdges causes window close  */
} CMP_EventType;

/**
 * @brief The instance index of the CMP filter count numbers
 */
typedef enum
{
    CMP_FILTERCNT_0  = 0U,  /**< CMP filter is bypassed  */
    CMP_FILTERCNT_1  = 1U,  /**< CMP filter is 1 consecutive sample  */
    CMP_FILTERCNT_2  = 2U,  /**< CMP filter is 2 consecutive sample  */
    CMP_FILTERCNT_3  = 3U,  /**< CMP filter is 3 consecutive sample  */
    CMP_FILTERCNT_4  = 4U   /**< CMP filter is 4 consecutive sample  */
} CMP_FilterCntType;

/**
 * @brief The instance index of the CMP hysteresis control
 */
typedef enum
{
    CMP_HYSTCTRL_0  = 0U,  /**< CMP  0 hysteresis internal  */
    CMP_HYSTCTRL_1  = 1U,  /**< CMP  1 hysteresis internal  */
    CMP_HYSTCTRL_2  = 2U,  /**< CMP  2 hysteresis internal  */
    CMP_HYSTCTRL_3  = 3U   /**< CMP  3 hysteresis internal  */
} CMP_HystCtrlType;

#ifdef CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE
/**
 * @brief The fixed CMP port for reference in channel scan mode
 */
typedef enum
{
    CMP_PORTSEL_MUX_P = 0U, /**< CMP  Positive Port */
    CMP_PORTSEL_MUX_N = 1U  /**< CMP  Negative Port */
} CMP_PortSelType;
#endif

/**
 * @brief The source of the CMP input
 */
typedef enum
{
    CMP_INSRCSEL_DAC = 0U,  /**< CMP input source is DAC */
    CMP_INSRCSEL_MUX = 1U   /**< CMP input source is analog 1-8 mux */
} CMP_INSrcSelType;

/**
 * @brief The instance index of the CMP input mux
 */
typedef enum
{
    CMP_INSEL_MUX_IN0 = 0U,  /**< CMP input mux from IN0(CMP0,CMP1,CMP2) */
    CMP_INSEL_MUX_IN1 = 1U,  /**< CMP input mux from IN1(CMP0,CMP1,CMP2) */
    CMP_INSEL_MUX_IN2 = 2U,  /**< CMP input mux from IN2(CMP0,CMP1,CMP2) */
    CMP_INSEL_MUX_IN3 = 3U,  /**< CMP input mux from IN3(CMP0,CMP1,CMP2) */
    CMP_INSEL_MUX_IN4 = 4U,  /**< CMP input mux from IN4(CMP0,CMP1,CMP2) */
    CMP_INSEL_MUX_IN5 = 5U,  /**< CMP input mux from IN5(CMP1,CMP2) */
    CMP_INSEL_MUX_IN6 = 6U,  /**< CMP input mux from IN6(CMP1,CMP2) */
    CMP_INSEL_MUX_IN7 = 7U   /**< CMP input mux from IN7(CMP1,CMP2) */
} CMP_MuxSelType;

/**
 * @brief The instance index of DAC high voltage reference select
 */
typedef enum
{
    CMP_DACVINREF_H0 = 0U,  /**< CMP DAC high voltage input reference vrefh0 */
    CMP_DACVINREF_H1 = 1U   /**< CMP DAC high voltage input reference vrefh1 */
} CMP_DacVinRefSelType;

/**
 * @brief The instance index of high power mode select
 */
typedef enum
{
    CMP_LOWSPEEDMOD  = 0U,   /**< CMP low speed mode */
    CMP_HIGHSPEEDMOD = 1U    /**< CMP high speed mode */
} CMP_SpeedModSelType;

/**
 * @brief Defines CMP out status
 */
typedef enum
{
    CMP_OUT_FALLING_EDGE = 0U,    /**< CMP out detect falling edge  */
    CMP_OUT_RISING_EDGE  = 1U,    /**< CMP out detect rising edge  */
    CMP_OUT_NONE         = 2U     /**< CMP out detect none  */
} CMP_OutStatus;


/********* Local inline function ************/

/**
 * @brief set CMP enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetEn(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CCR0;
    pCmp->CCR0 = ((u32RegVal & (~(uint32_t)CMP_CCR0_EN_MASK)) | CMP_CCR0_EN(bEnable));
}

/**
 * @brief set CMP DMA enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetDma(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_DMA_EN_MASK)) | CMP_CCR1_DMA_EN(bEnable));
}

/**
 * @brief set CMP mode
 *
 * @param pCmp the CMP instance to use
 * @param eMod the CMP mode to use
 * @param u8FilterPrd the CMP filter period
 * @param eFilterCnt the CMP filter sample count
 */
LOCAL_INLINE void CMP_HWA_SetComparatorMod(CMP_Type *const pCmp, CMP_ModeSelType eMode, uint8_t u8FilterPrd, CMP_FilterCntType eFilterCnt)
{
    uint32_t u32RegVal = pCmp->CCR1;

    switch (eMode)
    {
        case CMP_MODE_DISABLE:
        {
            /* Nothing deal with */
        }
        break;

        case CMP_MODE_CONTINUOUS:
        {
            u32RegVal &= ~CMP_CCR1_WIN_EN_MASK;
            u32RegVal &= ~CMP_CCR1_SAMPLE_EN_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_PER_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
        }
        break;

        case CMP_MODE_SAMPLE_NONFILTER_EXTCLK:
        {
            u32RegVal &= ~CMP_CCR1_WIN_EN_MASK;
            u32RegVal |=  CMP_CCR1_SAMPLE_EN(true);
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
            u32RegVal |=  CMP_CCR1_FILT_CNT(0x01);
        }
        break;

        case CMP_MODE_SAMPLE_NONFILTER_INTCLK:
        {
            u32RegVal &= ~CMP_CCR1_WIN_EN_MASK;
            u32RegVal &= ~CMP_CCR1_SAMPLE_EN_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_PER_MASK;
            u32RegVal |=  CMP_CCR1_FILT_CNT(0x01)|
                          CMP_CCR1_FILT_PER(u8FilterPrd);
        }
        break;

        case CMP_MODE_SAMPLE_FILTER_EXTCLK:
        {
            u32RegVal &= ~CMP_CCR1_WIN_EN_MASK;
            u32RegVal |=  CMP_CCR1_SAMPLE_EN(true);
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
            u32RegVal |=  CMP_CCR1_FILT_CNT(eFilterCnt);
        }
        break;

        case CMP_MODE_SAMPLE_FILTER_INTCLK:
        {
            u32RegVal &= ~CMP_CCR1_WIN_EN_MASK;
            u32RegVal &= ~CMP_CCR1_SAMPLE_EN_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_PER_MASK;
            u32RegVal |=  CMP_CCR1_FILT_CNT(eFilterCnt)|
                          CMP_CCR1_FILT_PER(u8FilterPrd);
        }
        break;

        case CMP_MODE_WINDOW:
        {
            u32RegVal |=  CMP_CCR1_WIN_EN(true);
            u32RegVal &= ~CMP_CCR1_SAMPLE_EN_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_PER_MASK;
        }
        break;

        case CMP_MODE_WINDOW_RESAMPLE:
        {
            u32RegVal |=  CMP_CCR1_WIN_EN(true);
            u32RegVal &= ~CMP_CCR1_SAMPLE_EN_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_PER_MASK;
            u32RegVal |=  CMP_CCR1_FILT_CNT(0x01)|
                          CMP_CCR1_FILT_PER(u8FilterPrd);
        }
        break;

        case CMP_MODE_WINDOW_FILTER:
        {
            u32RegVal |=  CMP_CCR1_WIN_EN(true);
            u32RegVal &= ~CMP_CCR1_SAMPLE_EN_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_CNT_MASK;
            u32RegVal &= ~CMP_CCR1_FILT_PER_MASK;
            u32RegVal |=  CMP_CCR1_FILT_CNT(eFilterCnt)|
                          CMP_CCR1_FILT_PER(u8FilterPrd);
        }
        break;

#ifdef CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE
        case CMP_MODE_CHANNEL_SCAN:
        {
            pCmp->CSCR0 |= CMP_CSCR0_CS_EN(true) ;
        }
        break;
#endif

        default:
        break;
    }

    pCmp->CCR1 = u32RegVal;
}

/**
 * @brief Lowpower mode enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetEnLPMode(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CCR0;
    pCmp->CCR0 = ((u32RegVal & (~(uint32_t)CMP_CCR0_LP_EN_MASK)) | CMP_CCR0_LP_EN(bEnable));
}

/**
 * @brief set DAC enable selection
 *
 * @param pCmp the CMP instance to use
 * @param eType Dac enable source
 */
LOCAL_INLINE void CMP_HWA_SetDacEnableSrc(CMP_Type *const pCmp, CMP_DacEnableSrcType eType)
{
    uint32_t u32RegVal = pCmp->CCR0;
    pCmp->CCR0 = ((u32RegVal & (~(uint32_t)CMP_CCR0_DACEN_SEL_MASK)) | CMP_CCR0_DACEN_SEL(eType));
}

/**
 * @brief set CPM output invert
 *
 * @param pCmp the CMP instance to use
 * @param eType CPM output invert type
 */
LOCAL_INLINE void CMP_HWA_SetCmpOutInvert(CMP_Type *const pCmp, CMP_InvertType eType)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_CMPOUT_INV_MASK)) | CMP_CCR1_CMPOUT_INV(eType));
}

/**
 * @brief set CPM output filter/unfilter selection
 *
 * @param pCmp the CMP instance to use
 * @param eType CPM output filter/unfilter type
 */
LOCAL_INLINE void CMP_HWA_SetCmpOutSel(CMP_Type *const pCmp, CMP_OutSelectType eType)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_CMPOUT_SEL_MASK)) | CMP_CCR1_CMPOUT_SEL(eType));
}

/**
 * @brief set comparator output pin enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetEnCmpOutPack(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_CMPOUT_PEN_MASK)) | CMP_CCR1_CMPOUT_PEN(bEnable));
}

/**
 * @brief set CMPOUT_WIN level, when window is closed
 *
 * @param pCmp the CMP instance to use
 * @param eType CMPOUT_WIN level type
 */
LOCAL_INLINE void CMP_HWA_SetCmpOutWinLevel(CMP_Type *const pCmp, CMP_OutWinLevelType eType)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_CMPOUT_WIN_OWEN_MASK)) | CMP_CCR1_CMPOUT_WIN_OWEN(eType));
}

/**
 * @brief set CMPOUT_WIN level in user-define mode, when window is closed
 *
 * @param pCmp the CMP instance to use
 * @param eType user-define CMPOUT_WIN level type
 */
LOCAL_INLINE void CMP_HWA_SetCmpOutWin(CMP_Type *const pCmp, CMP_OutWinLevel_UserDefType eType)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_CMPOUT_WIN_OW_MASK)) | CMP_CCR1_CMPOUT_WIN_OW(eType));
}

/**
 * @brief set invert the WINDOW/SAMPLE signal enable or not
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetEnWinSampleInvert(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_WIN_INV_MASK)) | CMP_CCR1_WIN_INV(bEnable));
}

/**
 * @brief WINDOW signal can or not be closed by CMPO event when window mode
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetEnEventCloseWin(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_WIN_CLS_MASK)) | CMP_CCR1_WIN_CLS(bEnable));
}

/**
 * @brief set which CMPO event causes window close
 *
 * @param pCmp the CMP instance to use
 * @param eType CMPO event type
 */
LOCAL_INLINE void CMP_HWA_SetEventCloseWin(CMP_Type *const pCmp, CMP_EventType eType)
{
    uint32_t u32RegVal = pCmp->CCR1;
    pCmp->CCR1 = ((u32RegVal & (~(uint32_t)CMP_CCR1_EVT_SEL_MASK)) | CMP_CCR1_EVT_SEL(eType));
}

/**
 * @brief set CMP power mode select
 *
 * @param pCmp the CMP instance to use
 * @param eMod CMP power mode
 */
LOCAL_INLINE void CMP_HWA_SetSpeedMod(CMP_Type *const pCmp, CMP_SpeedModSelType eMod)
{
    uint32_t u32RegVal = pCmp->CCR2;
    pCmp->CCR2 = ((u32RegVal & (~(uint32_t)CMP_CCR2_HPMD_MASK)) | CMP_CCR2_HPMD(eMod));
}

/**
 * @brief set Comparator hard block hysteresis control
 *
 * @param pCmp the CMP instance to use
 * @param eType CMP hysteresis control type
 */
LOCAL_INLINE void CMP_HWA_SetHystCtrl(CMP_Type *const pCmp, CMP_HystCtrlType eType)
{
    uint32_t u32RegVal = pCmp->CCR2;
    pCmp->CCR2 = ((u32RegVal & (~(uint32_t)CMP_CCR2_HYSTCTR_MASK)) | CMP_CCR2_HYSTCTR(eType));
}

/**
 * @brief set which input is selected for the positive mux
 *
 * @param pCmp the CMP instance to use
 * @param eType CMP positive mux type
 */
LOCAL_INLINE void CMP_HWA_SetPSelMux(CMP_Type *const pCmp, CMP_MuxSelType eType)
{
    uint32_t u32RegVal = pCmp->CCR2;
    pCmp->CCR2 = ((u32RegVal & (~(uint32_t)CMP_CCR2_PSEL_MASK)) | CMP_CCR2_PSEL(eType));
}

/**
 * @brief set which input is selected for the negative mux
 *
 * @param pCmp the CMP instance to use
 * @param eType CMP negative mux type
 */
LOCAL_INLINE void CMP_HWA_SetNSelMux(CMP_Type *const pCmp, CMP_MuxSelType eType)
{
    uint32_t u32RegVal = pCmp->CCR2;
    pCmp->CCR2 = ((u32RegVal & (~(uint32_t)CMP_CCR2_MSEL_MASK)) | CMP_CCR2_MSEL(eType));
}

/**
 * @brief set the input to the positive port of the comparator
 *
 * @param pCmp the CMP instance to use
 * @param eType CMP positive input source type(analog mux,dac)
 */
LOCAL_INLINE void CMP_HWA_SetINPSel(CMP_Type *const pCmp, CMP_INSrcSelType eType)
{
    uint32_t u32RegVal = pCmp->CCR2;
    pCmp->CCR2 = ((u32RegVal & (~(uint32_t)CMP_CCR2_INPSEL_MASK)) | CMP_CCR2_INPSEL(eType));
}

/**
 * @brief set the input to the negative port of the comparator
 *
 * @param pCmp the CMP instance to use
 * @param eType CMP negative input source type(analog mux,dac)
 */
LOCAL_INLINE void CMP_HWA_SetINNSel(CMP_Type *const pCmp, CMP_INSrcSelType eType)
{
    uint32_t u32RegVal = pCmp->CCR2;
    pCmp->CCR2 = ((u32RegVal & (~(uint32_t)CMP_CCR2_INMSEL_MASK)) | CMP_CCR2_INMSEL(eType));
}

/**
 * @brief set CMP DAC enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetEnDac(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->DCR;
    pCmp->DCR = ((u32RegVal & (~(uint32_t)CMP_DCR_DAC_EN_MASK)) | CMP_DCR_DAC_EN(bEnable));
}

/**
 * @brief set DAC reference voltage source
 *
 * @param pCmp the CMP instance to use
 * @param eType CMP reference voltage source type
 */
LOCAL_INLINE void CMP_HWA_SetVinRefSel(CMP_Type *const pCmp, CMP_DacVinRefSelType eType)
{
    uint32_t u32RegVal = pCmp->DCR;
    pCmp->DCR = ((u32RegVal & (~(uint32_t)CMP_DCR_VRSEL_MASK)) | CMP_DCR_VRSEL(eType));
}

/**
 * @brief set CMP Dac output
 *
 * @param pCmp the CMP instance to use
 * @param u8Data the Dac data
 * @note output = (VinRef / 256) * (u8Data + 1)
 */
LOCAL_INLINE void CMP_HWA_SetDacData(CMP_Type *const pCmp, uint8_t u8Data)
{
    uint32_t u32RegVal = pCmp->DCR;
    pCmp->DCR = ((u32RegVal & (~(uint32_t)CMP_DCR_DAC_DATA_MASK)) | CMP_DCR_DAC_DATA(u8Data));
}

/**
 * @brief set comparator rising interrupt enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetIntEn_Rising(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->IER;
    pCmp->IER = ((u32RegVal & (~(uint32_t)CMP_IER_CFR_IE_MASK)) | CMP_IER_CFR_IE(bEnable));
}

/**
 * @brief get comparator rising interrupt enable status
 *
 * @param pCmp the CMP instance to use
 * @return comparator rising interrupt status
 */
LOCAL_INLINE bool CMP_HWA_GetIntEn_Rising(CMP_Type *const pCmp)
{
    bool RetStatus = false;
    uint32_t u32RegVal = pCmp->IER;

    RetStatus = (bool)((((u32RegVal & CMP_IER_CFR_IE_MASK) >> CMP_IER_CFR_IE_SHIFT) != 0U) ? true : false);
    return RetStatus;
}

/**
 * @brief set comparator falling interrupt enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetIntEn_Falling(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->IER;
    pCmp->IER = ((u32RegVal & (~(uint32_t)CMP_IER_CFF_IE_MASK)) | CMP_IER_CFF_IE(bEnable));
}

/**
 * @brief get comparator falling interrupt enable status
 *
 * @param pCmp the CMP instance to use
 * @return comparator falling interrupt status
 */
LOCAL_INLINE bool CMP_HWA_GetIntEn_Falling(CMP_Type *const pCmp)
{
    bool bRetStatus = false;
    uint32_t u32RegVal = pCmp->IER;

    bRetStatus = (bool)((((u32RegVal & CMP_IER_CFF_IE_MASK) >> CMP_IER_CFF_IE_SHIFT) != 0U) ? true : false);
    return bRetStatus;
}

/**
 * @brief get CMP output rising edge status
 *
 * @param pCmp the CMP instance to use
 * @return CMP rising edge status
 */
LOCAL_INLINE bool CMP_HWA_GetIntFlag_Rising(CMP_Type *const pCmp)
{
    bool bRetStatus = false;
    uint32_t u32RegVal = pCmp->CSR;

    bRetStatus = (bool)((((u32RegVal & CMP_CSR_CFR_MASK) >> CMP_CSR_CFR_SHIFT) != 0U) ? true : false);
    return bRetStatus;
}

/**
 * @brief get CMP output falling edge status
 *
 * @param pCmp the CMP instance to use
 * @return CMP falling edge status
 */
LOCAL_INLINE bool CMP_HWA_GetIntFlag_Falling(CMP_Type *const pCmp)
{
    bool bRetStatus = false;
    uint32_t u32RegVal = pCmp->CSR;

    bRetStatus = (bool)((((u32RegVal & CMP_CSR_CFF_MASK) >> CMP_CSR_CFF_SHIFT) != 0U) ? true : false);
    return bRetStatus;
}

/**
 * @brief clear rising interrupt flag
 *
 * @param pCmp the CMP instance to use
 */
LOCAL_INLINE void CMP_HWA_ClearIntFlag_Rising(CMP_Type *const pCmp)
{
    uint32_t u32RegVal = pCmp->CSR;
    pCmp->CSR = ((u32RegVal & (~(uint32_t)CMP_CSR_CFR_MASK)) | CMP_CSR_CFR(true));
}

/**
 * @brief clear falling interrupt flag
 *
 * @param pCmp the CMP instance to use
 */
LOCAL_INLINE void CMP_HWA_ClearIntFlag_Falling(CMP_Type *const pCmp)
{
    uint32_t u32RegVal = pCmp->CSR;
    pCmp->CSR = ((u32RegVal & (~(uint32_t)CMP_CSR_CFF_MASK)) | CMP_CSR_CFF(true));
}

/**
 * @brief get CMP filtered output
 *
 * @param pCmp the CMP instance to use
 * @return CMP filtered output
 */
LOCAL_INLINE uint32_t CMP_HWA_GetCmpOut(CMP_Type *const pCmp)
{
    uint32_t u32RegVal = pCmp->CSR;
    u32RegVal = (u32RegVal & CMP_CSR_CMPOUT_FILTER_MASK) >> CMP_CSR_CMPOUT_FILTER_SHIFT;
    return u32RegVal;
}

#ifdef CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE

/**
 * @brief set comparator channel scan interrupt enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetIntEn_ChannelScan(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->IER;
    pCmp->IER = ((u32RegVal & (~(uint32_t)CMP_IER_CSF_IE_MASK)) | CMP_IER_CSF_IE(bEnable));
}

/**
 * @brief get comparator channel scan interrupt enable status
 *
 * @param pCmp the CMP instance to use
 * @return comparator channel scan interrupt status
 */
LOCAL_INLINE bool CMP_HWA_GetIntEn_ChannelScan(CMP_Type *const pCmp)
{
    bool bRetStatus = false;
    uint32_t u32RegVal = pCmp->IER;

    bRetStatus = (bool)((((u32RegVal & CMP_IER_CSF_IE_MASK) >> CMP_IER_CSF_IE_SHIFT) != 0U) ? true : false);
    return bRetStatus;
}

/**
 * @brief clear channel scan interrupt flag
 *
 * @param pCmp the CMP instance to use
 */
LOCAL_INLINE void CMP_HWA_ClearIntFlag_ChannelScan(CMP_Type *const pCmp)
{
    uint32_t u32RegVal = pCmp->CSR;
    pCmp->CSR = ((u32RegVal & (~(uint32_t)CMP_CSR_CSF_MASK)) | CMP_CSR_CSF(true));
}

/**
 * @brief set CMP and DAC initialization delay modulus
 *
 * @param pCmp cmp type point
 * @param u8Modulus pCmp the CMP instance to use
 */
LOCAL_INLINE void CMP_HWA_SetCSInitModulus(CMP_Type *const pCmp, uint8_t u8Modulus)
{
    uint32_t u32RegVal = pCmp->CSCR0;
    pCmp->CSCR0 = ((u32RegVal & (~(uint32_t)CMP_CSCR0_CS_INITMOD_MASK)) | CMP_CSCR0_CS_INITMOD(u8Modulus));
}

/**
 * @brief set number of clock cycles for sampling
 *
 * @param pCmp the CMP instance to use
 * @param u8Nsam the sampling clocks value
 */
LOCAL_INLINE void CMP_HWA_SetCSNSAM(CMP_Type *const pCmp, uint8_t u8Nsam)
{
    uint32_t u32RegVal = pCmp->CSCR0;
    pCmp->CSCR0 = ((u32RegVal & (~(uint32_t)CMP_CSCR0_CS_NSAM_MASK)) | CMP_CSCR0_CS_NSAM(u8Nsam));
}

/**
 * @brief set CMP channel scan enable
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetCSEn(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CSCR0;
    pCmp->CSCR0 = ((u32RegVal & (~(uint32_t)CMP_CSCR0_CS_EN_MASK)) | CMP_CSCR0_CS_EN(bEnable));
}

/**
 * @brief set channel scan fixed channel
 *
 * @param pCmp the CMP instance to use
 * @param eChannel the fixed channel
 */
LOCAL_INLINE void CMP_HWA_SetCSFixedChannel(CMP_Type *const pCmp, CMP_MuxSelType eChannel)
{
    uint32_t u32RegVal = pCmp->CSCR1;
    pCmp->CSCR1 = ((u32RegVal & (~(uint32_t)CMP_CSCR1_FIXCH_MASK)) | CMP_CSCR1_FIXCH(eChannel));
}

/**
 * @brief set channel scan fixed port
 *
 * @param pCmp the CMP instance to use
 * @param ePort the fixed port
 */
LOCAL_INLINE void CMP_HWA_SetCSFixedPort(CMP_Type *const pCmp, CMP_PortSelType ePort)
{
    uint32_t u32RegVal = pCmp->CSCR1;
    pCmp->CSCR1 = ((u32RegVal & (~(uint32_t)CMP_CSCR1_FIXP_MASK)) | CMP_CSCR1_FIXP(ePort));
}

/**
 * @brief set channel scan channel enabled
 *
 * @param pCmp the CMP instance to use
 * @param eChannel the enabled channel
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetCSChannelEn(CMP_Type *const pCmp, CMP_MuxSelType eChannel, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CSCR1;
    pCmp->CSCR1 = ((u32RegVal & (~(uint32_t)(1 << eChannel))) | (((uint32_t)bEnable) << eChannel));
}

/**
 * @brief get CMP output channel scan status
 *
 * @param pCmp the CMP instance to use
 * @return CMP channel scan status
 */
LOCAL_INLINE bool CMP_HWA_GetIntFlag_ChannelScan(CMP_Type *const pCmp)
{
    bool bRetStatus = false;
    uint32_t u32RegVal = pCmp->CSR;

    bRetStatus = (bool)((((u32RegVal & CMP_CSR_CSF_MASK) >> CMP_CSR_CSF_SHIFT) != 0U) ? true : false);
    return bRetStatus;
}

/**
 * @brief set channel scan channel enabled
 *
 * @param pCmp the CMP instance to use
 * @param eChannel the enabled channel
 * @param bPresetstate preset state for channel
 */
LOCAL_INLINE void CMP_HWA_SetCSChannelPresetstate(CMP_Type *const pCmp, CMP_MuxSelType eChannel, bool bPresetstate)
{
    uint32_t u32RegVal = pCmp->CSCSR;
    pCmp->CSCSR = ((u32RegVal & (~(uint32_t)(1 << eChannel))) | (((uint32_t)bPresetstate) << eChannel));
}

/**
 * @brief get channel scan channel current state
 *
 * @param pCmp the CMP instance to use
 * @param eChannel the channel that want to get state
 */
LOCAL_INLINE bool CMP_HWA_GetCSChannelOut(CMP_Type *const pCmp, CMP_MuxSelType eChannel)
{
    bool OutFlag;
    uint32_t u32RegVal = pCmp->CSCSR;
    OutFlag = (bool)((u32RegVal & ((uint32_t)(1 << eChannel))) >> eChannel);

    return OutFlag;
}

/**
 * @brief software clear channel scan comparison results
 *
 * @param pCmp the CMP instance to use
 */
LOCAL_INLINE void CMP_HWA_ClearCSCompRes(CMP_Type *const pCmp)
{
    uint32_t u32RegVal = pCmp->CSCSR;
    pCmp->CSCSR = ((u32RegVal & (~(uint32_t)CMP_CSCSR_CS_SWCLR_MASK)) | CMP_CSCSR_CS_SWCLR(true));
}

/**
 * @brief software clear channel scan comparison results
 *
 * @param pCmp the CMP instance to use
 * @param bEnable enable/disable flag
 */
LOCAL_INLINE void CMP_HWA_SetCSCompareResultACEn(CMP_Type *const pCmp, bool bEnable)
{
    uint32_t u32RegVal = pCmp->CSCSR;
    pCmp->CSCSR = ((u32RegVal & (~(uint32_t)CMP_CSCSR_CS_ACLR_MASK)) | CMP_CSCSR_CS_ACLR(bEnable));
}

/**
 * @brief get channel scan comparison reuslt
 *
 * @param pCmp the CMP instance to use
 * @param eChannel the enabled channel
 * @return channel comparison result for a given channel
 */
LOCAL_INLINE uint32_t CMP_HWA_GetCSComparisonResult(CMP_Type *const pCmp, CMP_MuxSelType eChannel)
{
    uint32_t u32RegVal = pCmp->CSCSR;
    u32RegVal = (u32RegVal & (1U << eChannel)) >> eChannel;
    return u32RegVal;
}

/**
 * @brief set channel scan active
 *
 * @param pCmp the CMP instance to use
 * @return status cmp channel whether is active
 */
LOCAL_INLINE bool CMP_HWA_GetCSActive(CMP_Type *const pCmp)
{
	bool status;
    uint32_t u32RegVal = pCmp->CSSR;
    status = ((u32RegVal & ((uint32_t)CMP_CSSR_CS_ACTIVE_MASK)) >> CMP_CSSR_CS_ACTIVE_SHIFT) ? true : false;
    return status;
}

/**
 * @brief get channel scan comparison result changed flag
 *
 * @param pCmp the CMP instance to use
 * @param eChannel the channel to get comparison result changed flag
 * @return the comparison result changed flag for a given channel
 */
LOCAL_INLINE bool CMP_HWA_GetCSComparisonResultFlag(CMP_Type *const pCmp, CMP_MuxSelType eChannel)
{
    uint32_t u32RegVal = pCmp->CSSR;
    return ((u32RegVal & (1U << eChannel)) >> eChannel) ? true : false;
}

#endif

/** @}*/

#endif

#endif  /* #ifndef _HWA_CMP_H_ */
