#include "BspAontimer.h"
#include <IoHwAb_Dio.h>
static void Bsp_AONTIMER_IRQHandler(AONTIMER_HandleType* pHandle);

AONTIMER_HandleType g_tAontimerHandle;
static unsigned int test_count = 0;

static void Bsp_AONTIMER_IRQHandler(AONTIMER_HandleType* pHandle)
{
    if(test_count%2 == 0)
    {
//    	IoHwAb_Dio_FlipChannel(VBAT_HALL_CTRL_IDX);
    }
    if (test_count++ == 200000)
    {
        test_count = 0;
    }
    PROCESS_UNUSED_VAR(pHandle)
}

void Bsp_Aontimer_Init(void)
{
    AONTIMER_InitType tInitStruct;

    g_tAontimerHandle.eInstance = AONTIMER_INSTANCE_0;

    tInitStruct.eMode = AONTIMER_COUNTER_MODE;               /* use counter mode */
    tInitStruct.u8Prescaler = 0U;                            /* set aontimer counter prescaler to 4 */
    tInitStruct.eClkSrc = AONTIMER_SIRC_1MHZ;                  /* set clock source ,RTC clock frequency is 32k. */
    tInitStruct.u16StartValue = (uint16_t)1000U;            /* set the start value, when the counter increase to the value ,the interrupt function will be called. */

    tInitStruct.bIntEn = true; /* enable interrupt function */
    tInitStruct.pAontimerCallback = Bsp_AONTIMER_IRQHandler;        /* set the notify function */

    AONTIMER_Init(&g_tAontimerHandle, &tInitStruct);
}

void Bsp_AontimerStart(void)
{
    AONTIMER_StartTimer(&g_tAontimerHandle);
}
