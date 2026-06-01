#include "BspRtc.h"
#include <IoHwAb_Dio.h>
static void Bsp_RTC_IRQHandler(RTC_HandleType *pHandle);
static void Bsp_Rtc_ConfigInit(void);

RTC_HandleType g_tRtcHandle;
static unsigned int test_count = 0;

static void Bsp_RTC_IRQHandler(RTC_HandleType *pHandle)
{
    (void)pHandle;
    if(test_count%2 == 0)
    {
//    	IoHwAb_Dio_FlipChannel(VBAT_HALL_CTRL_IDX);
    }
    if (test_count++ == 200000)
    {
        test_count = 0;
    }
    RTC_SetCountValue(&g_tRtcHandle, 0U);
}

static void Bsp_Rtc_ConfigInit(void)
{
    RTC_InitType tInitStruct = {0};
    tInitStruct.u32AlarmValue = (uint32_t)2U;                  /* configure alarm interrupt value to 2, the unit is second */
//    tInitStruct.bOverflowIntEn = true;
    tInitStruct.bAlarmIntEn = true;

//    g_tRtcHandle.tSettings.pOverflowCallback = Bsp_RTC_IRQHandler;     /* configure the alarm notification function */
    g_tRtcHandle.tSettings.pAlarmCallback = Bsp_RTC_IRQHandler;
    RTC_Init(&g_tRtcHandle, &tInitStruct);
    RTC_SetCountValue(&g_tRtcHandle, 0U);
}

void Bsp_Rtc_Init(void)
{
	g_tRtcHandle.eInstance = RTC_INSTANCE_0;
    Bsp_Rtc_ConfigInit();
    RTC_SetCountValue(&g_tRtcHandle, 0xfffffffb);
}

void Bsp_RtcStart(void)
{
    RTC_Start(&g_tRtcHandle);
}
