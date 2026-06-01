/**
 * @file module_driver_rtc.c
 * @author Flagchip032
 * @brief RTC driver source code
 * @version 2.0.0
 * @date 2024-06-10
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#include "module_driver_rtc.h"

#if RTC_INSTANCE_COUNT > 0U

#include "module_driver_smisc.h"


#ifndef RTC_DEV_ERROR_REPORT
#define RTC_DEV_ERROR_REPORT	STD_OFF
#endif

#if RTC_DEV_ERROR_REPORT == STD_ON
#define RTC_ReportDevError(func, error) ReportDevError(RTC_MODULE_ID, func, error)
#endif

/********* Local variable ************/
static RTC_Type * const s_pRtcBasePtrs[RTC_INSTANCE_COUNT] = RTC_BASE_PTRS;

/* Table of month length (in days) for the Common-year*/
static const uint8_t ComYear[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

/* Table of month length (in days) for the Leap-year*/
static const uint8_t LeapYear[] = {0U, 31U, 29U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

static uint32_t RTC_ReadSecondValue(RTC_Type *const pRtc)
{
	uint32_t u32Value0, u32Value1;
	do
	{
		/* RTC_SR must be read in a stable state */
		u32Value0 = RTC_HWA_ReadSecondValue(pRtc);
		u32Value1 = RTC_HWA_ReadSecondValue(pRtc);
	} while (u32Value0 != u32Value1);
	return u32Value0;
}

static bool RTC_IsLeapYear(uint16_t u16Year)
{
    bool bYearLeap = false;

    if ((u16Year % 4U) > 0U)
    {
        bYearLeap = false;
    }
    else if ((u16Year % 100U) > 0U)
    {
        bYearLeap = true;
    }
    else if ((u16Year % 400U) > 0U)
    {
        bYearLeap = false;
    }
    else
    {
        bYearLeap = true;
    }

    /* Return the exit code */
    return bYearLeap;
}

static bool RTC_CheckTimeDate(const RTC_TimeDate * const pTimeDate)
{
    bool bCheckReturn = true;
    const uint8_t * pMonth;
    pMonth = RTC_IsLeapYear(pTimeDate->u16Year) ? LeapYear : ComYear;

    if (pTimeDate->u16Year < START_YEAR || pTimeDate->u16Year > END_YEAR 
            || pTimeDate->u8Month < 1U || pTimeDate->u8Month > 12U
            || pTimeDate->u8Day < 1U || pTimeDate->u8Day > pMonth[pTimeDate->u8Month]
            || pTimeDate->u8Hour >= 24
            || pTimeDate->u8Minute >= 60
            || pTimeDate->u8Second >= 60)
    {
        bCheckReturn = false;
    }
    return bCheckReturn;
}

static void RTC_TimeDate_To_Second(RTC_TimeDate * const pTimeDate, uint32_t u32Second)
{
    uint32_t u32CountDays;
    uint32_t u32TempCount;
    uint32_t u32TempDays;

    u32CountDays = u32Second / SECONDS_DAY;
    u32TempCount = u32Second % SECONDS_DAY;

    pTimeDate->u8Hour = (uint8_t)(u32TempCount / SECONDS_HOUR);
    u32TempCount = u32TempCount % SECONDS_HOUR;

    pTimeDate->u8Minute = (uint8_t)(u32TempCount / SECONDS_MINUTE);
    pTimeDate->u8Second = (uint8_t)(u32TempCount % SECONDS_MINUTE);

    pTimeDate->u16Year = (uint16_t)START_YEAR;

    u32TempDays = DAYS_COM_YEAR;
    while (u32CountDays >= u32TempDays)
    {
        pTimeDate->u16Year++;
        u32CountDays -= u32TempDays;
        u32TempDays = (RTC_IsLeapYear(pTimeDate->u16Year)) ? DAYS_LEAP_YEAR : DAYS_COM_YEAR;
    }

    u32CountDays += 1;

    for (uint8_t u8TempMonth = 1; u8TempMonth <= 12; u8TempMonth++)
    {
        u32TempCount = (RTC_IsLeapYear(pTimeDate->u16Year)) ? (uint32_t)LeapYear[u8TempMonth] : (uint32_t)ComYear[u8TempMonth];
        if (u32CountDays <= u32TempCount)
        {
            pTimeDate->u8Month = (uint8_t)u8TempMonth;
            pTimeDate->u8Day = (uint8_t)u32CountDays;
            break;
        }
        else
        {
        	u32CountDays -= u32TempCount;
        }
    }
}

static uint32_t RTC_Second_To_TimeDate(const RTC_TimeDate * const pTimeDate)
{
    uint32_t u32Second;

    uint32_t u32TempDay;

    u32Second = (pTimeDate->u16Year - START_YEAR) * SECONDS_DAY * DAYS_COM_YEAR;

    for (uint32_t u32TempYear = START_YEAR; u32TempYear < pTimeDate->u16Year; u32TempYear++)
    {
        if (RTC_IsLeapYear((uint16_t)u32TempYear))
        {
            u32Second += SECONDS_DAY;
        }
    }

    for (uint8_t u8TempMonth = 1; u8TempMonth < pTimeDate->u8Month; u8TempMonth++)
    {
        u32TempDay = (RTC_IsLeapYear(pTimeDate->u16Year)) ? (uint32_t)LeapYear[u8TempMonth] : (uint32_t)ComYear[u8TempMonth];
        u32Second += (u32TempDay * SECONDS_DAY);
    }

    u32Second += ((uint32_t)((pTimeDate->u8Day - 1U) * SECONDS_DAY) + \
                pTimeDate->u8Hour * SECONDS_HOUR + \
                pTimeDate->u8Minute * SECONDS_MINUTE + \
                pTimeDate->u8Second);
                
    return u32Second;
}


/**
 * @brief Initialize Rtc instance
 *
 * @param pRtcHandle the RTC instance
 * @param pInitStruct Rtc initialization structure
 * @note This function could only write once after POR.
 */
void RTC_Init(RTC_HandleType* pRtcHandle, const RTC_InitType *const pInitStruct)
{
	RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
#if RTC_DEV_ERROR_REPORT == STD_ON
    uint32_t u32RtcClockFrequency = 0U;
    bool bSMISCClockValid = SMISC_GetSMISCClockFreq(SMISC_RTC_CLK, &u32RtcClockFrequency);
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_INIT_ID, RTC_E_PARAM_INSTANCE);
    }
    else if (NULL == pInitStruct)
    {
        RTC_ReportDevError(RTC_INIT_ID, RTC_E_PARAM_POINTER);
    }
    else if (false == bSMISCClockValid)
    {
        RTC_ReportDevError(RTC_INIT_ID, RTC_E_PARAM_CLOCK);
    }
    else if (0U == u32RtcClockFrequency)
    {
        RTC_ReportDevError(RTC_INIT_ID, RTC_E_PARAM_CLOCK);
    }
    else
    {        
#endif
        /* Disable interrupt */
        RTC_HWA_DisableOverflowInterrupt(pRtc);
        /*Disable Second interrupt*/
        RTC_HWA_DisableSecondInterrupt(pRtc);
        /*Disable Alarm interrupt*/
        RTC_HWA_DisableAlarmInterrupt(pRtc);

        /* disable the rtc clock*/
        RTC_HWA_DisableRtcCounter(pRtc);
        /* clear PR register */
        RTC_HWA_SetPrescalerCounterValue(pRtc, 0U);
        /* clear CR register */
        RTC_HWA_ConfigControl(pRtc, 0U);
        if (pInitStruct->bStableClkoutFreq)
        {
            RTC_HWA_SetClkoutFreqStable(pRtc);
        }
        else
        {
            RTC_HWA_SetClkoutFromSelectFreq(pRtc);
        }
        /* TSIC should only be altered when TSIE is clear */
        RTC_HWA_SetSecondAndClkoutFreq(pRtc, pInitStruct->eSecIntAndClkoutFreq);
        /* Set alarm value */
        RTC_HWA_SetAlarmCounterValue(pRtc, pInitStruct->u32AlarmValue);
        /* save alarm value */
        pRtcHandle->u32AlarmValue = pInitStruct->u32AlarmValue;

        /* disable the rtc timer */
        RTC_HWA_DisableRtcCounter(pRtc);

		/* enable alarm interrupt */
		RTC_HWA_EnableAlarmInterrupt(pRtc, pInitStruct->bAlarmIntEn);

		/* enable overflow interrupt */
		RTC_HWA_EnableOverflowInterrupt(pRtc, pInitStruct->bOverflowIntEn);

		/* enable second interrupt */
		RTC_HWA_EnableSecondInterrupt(pRtc, pInitStruct->bSecondIntEn);

#if RTC_DEV_ERROR_REPORT == STD_ON        
    }
#endif
}

/**
 * @brief De-initialize Rtc instance
 *
 * @param pRtcHandle the RTC instance
 */
void RTC_Deinit(RTC_HandleType* pRtcHandle)
{
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_DEINIT_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif  
        RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
        /* disable the rtc timer */
        RTC_HWA_DisableRtcCounter(pRtc);
        /* clear PR register */
        RTC_HWA_SetPrescalerCounterValue(pRtc, 0U);
        /* clear SR register */
        RTC_HWA_SetSecondCounterValue(pRtc, 0U);
        /* clear TAR register */
        RTC_HWA_SetAlarmCounterValue(pRtc, 0U);
        /* clear IER register */
        RTC_HWA_SetInterruptValue(pRtc, 0U);
        /* clear CR register */
        RTC_HWA_ConfigControl(pRtc, 0U);
        pRtcHandle->tSettings.pAlarmCallback = NULL;
        pRtcHandle->tSettings.pSecondCallback = NULL;

        __NVIC_DisableIRQ(RTC_IRQn);
        __NVIC_DisableIRQ(RTC_seconds_IRQn);
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif
}

/**
 * @brief Rtc start
 *
 * @param pRtcHandle the RTC instance
 */
void RTC_Start(RTC_HandleType* pRtcHandle)
{
	RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_START_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif  
        /*enable the rtc clock*/
        RTC_HWA_EnableRtcCounter(pRtc);
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif
}

/**
 * @brief Rtc stop
 *
 * @param pRtcHandle the RTC instance
 */
void RTC_Stop(RTC_HandleType* pRtcHandle)
{
	RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_STOP_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif 
        /*disable the rtc clock*/
        RTC_HWA_DisableRtcCounter(pRtc);
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif
}

/**
 * @brief set count value
 *
 * @param pRtcHandle Pointer to the RTC handle structure.
 * @param u32CounetValue The count value to set.
 */
void RTC_SetCountValue(RTC_HandleType* pRtcHandle, const uint32_t u32CounetValue)
{
	RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_SET_COUNT_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif 
        /*disable the rtc clock*/
        RTC_HWA_DisableRtcCounter(pRtc);
        /* Set count value */
        RTC_HWA_SetSecondCounterValue(pRtc, u32CounetValue);
        /*enable the rtc clock*/
        RTC_HWA_EnableRtcCounter(pRtc);
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif
}

/**
 * @brief Rtc alarm value
 *
 * @param pRtcHandle the RTC instance
 * @param u32AlarmValue Input value
 */
void RTC_UpdateAlarmValue(RTC_HandleType* pRtcHandle, const uint32_t u32AlarmValue)
{
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_UPDATE_ALARM_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif 
        RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
        /*disable the rtc clock*/
        RTC_HWA_DisableRtcCounter(pRtc);
        /* clear PR register */
        RTC_HWA_SetPrescalerCounterValue(pRtc, 0U);
        /* Set alarm value */
        RTC_HWA_SetAlarmCounterValue(pRtc, RTC_ReadSecondValue(pRtc) + u32AlarmValue - (uint32_t)1U);
        pRtcHandle->u32AlarmValue = u32AlarmValue;
        /*enable the rtc clock*/
        RTC_HWA_EnableRtcCounter(pRtc);
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif
}

/**
 * @brief Check RTC overflow flag
 *
 * @param pRtcHandle the RTC instance
 * @return Overflow flag
 */
uint32_t RTC_CheckOverflowFlag(RTC_HandleType* pRtcHandle)
{
	RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_CHECK_OVERFLOW_FLAF_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif 
        return RTC_HWA_ReadOverflowFlag(pRtc);
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif 
}

/**
 * @brief Get time and date
 *
 * @param pRtcHandle the RTC instance
 * @param pTimeDate the structure of time and date
 */
void RTC_GetTimeDate(RTC_HandleType* pRtcHandle, RTC_TimeDate * const pTimeDate)
{
    uint32_t u32Second;
    RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];

#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_GET_TIMEDATE_ID, RTC_E_PARAM_INSTANCE);
    }   
#endif

    u32Second = RTC_ReadSecondValue(pRtc);
    RTC_TimeDate_To_Second(pTimeDate, u32Second);
}

/**
 * @brief Set time and date
 *
 * @param pRtcHandle the RTC instance
 * @param pTimeDate the structure of time and date
 */
void RTC_SetTimeDate(RTC_HandleType* pRtcHandle, const RTC_TimeDate * const pTimeDate)
{
    uint32_t u32Second;
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_SET_TIMEDATE_ID, RTC_E_PARAM_INSTANCE);
    }   
    else if (NULL == pTimeDate)
    {
        RTC_ReportDevError(RTC_SET_TIMEDATE_ID, RTC_E_PARAM_POINTER);
    } 
#endif 
    if (true == RTC_CheckTimeDate(pTimeDate))
    {
        u32Second = RTC_Second_To_TimeDate(pTimeDate);
        RTC_SetCountValue(pRtcHandle, u32Second);
    }
#if RTC_DEV_ERROR_REPORT == STD_ON
    else
    {
        RTC_ReportDevError(RTC_SET_TIMEDATE_ID, RTC_E_PARAM_FORMAT);
    } 
#endif
}

/**
 * @brief Get time and date compensation information.
 *
 * @param pRtcHandle the RTC instance
 * @param pCompensation the structure to compensate time accuracy
 */
void RTC_GetCompensation(RTC_HandleType* pRtcHandle, RTC_Compensation * const pCompensation)
{
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_GET_COMPENSATION_ID, RTC_E_PARAM_INSTANCE);
    }   
#endif 
    RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
    pCompensation->u8Interval = RTC_HWA_ReadCompInterval(pRtc);
    pCompensation->u8Value = RTC_HWA_ReadCompValue(pRtc);
}

/**
 * @brief Set time and date compensation value.
 *
 * @param pRtcHandle the RTC instance
 * @param pCompensation the structure to compensate time accuracy
 */
void RTC_SetCompensation(RTC_HandleType* pRtcHandle, const RTC_Compensation * const pCompensation)
{
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RRTC_SET_COMPENSATION_ID, RTC_E_PARAM_INSTANCE);
    }   
    else if (NULL == pCompensation)
    {
        RTC_ReportDevError(RTC_SET_COMPENSATION_ID, RTC_E_PARAM_POINTER);
    } 
#endif 
    RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
    RTC_HWA_SetCompInterval(pRtc, pCompensation->u8Interval);
    RTC_HWA_SetCompValue(pRtc, pCompensation->u8Interval);
}

/** @brief RTC common interrupt function
 *
 * @param pRtcHandle the RTC instance
 * @param eIntEvent the RTC interrupt mode
 */
void Rtc_CommonProcessInterrupt(RTC_HandleType* pRtcHandle, const RTC_IntEventType eIntEvent)
{
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_INTE_PROC_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif 
        switch (eIntEvent)
        {
            case RTC_ALARM_INT:
                if (NULL != pRtcHandle->tSettings.pAlarmCallback)
                {
                    pRtcHandle->tSettings.pAlarmCallback(pRtcHandle);
                }
                break;
            case RTC_SECOND_INT:
                if (NULL != pRtcHandle->tSettings.pSecondCallback)
                {
                    pRtcHandle->tSettings.pSecondCallback(pRtcHandle);
                }
                break;
            case RTC_OVERFLOW_INT:
                if (NULL != pRtcHandle->tSettings.pOverflowCallback)
                {
                    pRtcHandle->tSettings.pOverflowCallback(pRtcHandle);
                }
                break;
            default:
                /* do nothing*/
                break;
        }
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif 
}

/**
 * @brief RTC alarm and overflow interrupt handler entry
 *
 * @param pRtcHandle the RTC instance
 */
void RTC_Alarm_Overflow_IRQHandler(RTC_HandleType* pRtcHandle)
{
	RTC_Type * const pRtc = s_pRtcBasePtrs[pRtcHandle->eInstance];
#if RTC_DEV_ERROR_REPORT == STD_ON
    if ((uint32_t)pRtcHandle->eInstance >= RTC_INSTANCE_COUNT)
    {
        RTC_ReportDevError(RTC_IRQ_HANDER_ID, RTC_E_PARAM_INSTANCE);
    }    
    else
    {
#endif 
        if ((RTC_HWA_ReadOverflowFlag(pRtc)) && (RTC_HWA_ReadOverflowEnable(pRtc)))
        {
            /*oveflow Int*/
            Rtc_CommonProcessInterrupt(pRtcHandle, RTC_OVERFLOW_INT);
            /*enable the rtc clock*/
            RTC_HWA_DisableRtcCounter(pRtc);
            /* Set time counter value */
            RTC_HWA_SetSecondCounterValue(pRtc, 0u);
            /*enable the rtc clock*/
            RTC_HWA_EnableRtcCounter(pRtc);
        }

        if ((RTC_HWA_ReadAlarmFlag(pRtc)) && (RTC_HWA_ReadAlarmEnable(pRtc)))
        {
            uint32_t u32CountValue = 0;
            /*alarm Int*/
            Rtc_CommonProcessInterrupt(pRtcHandle, RTC_ALARM_INT);
            u32CountValue = RTC_ReadSecondValue(pRtc);
            /*enable the rtc clock*/
            RTC_HWA_DisableRtcCounter(pRtc);
            /* Set alarm value */
            RTC_HWA_SetAlarmCounterValue(pRtc, u32CountValue + pRtcHandle->u32AlarmValue - 1U);
            /*enable the rtc clock*/
            RTC_HWA_EnableRtcCounter(pRtc);
        }
#if RTC_DEV_ERROR_REPORT == STD_ON  
    }
#endif 
}


#endif

