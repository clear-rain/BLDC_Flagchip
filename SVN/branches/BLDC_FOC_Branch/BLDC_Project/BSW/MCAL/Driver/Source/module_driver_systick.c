/**
 * @file module_driver_systick.c
 * @author Flagchip
 * @brief SYSTICK driver source code
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip113   N/A          First version
*********************************************************************************/
#include "module_driver_systick.h"


#ifndef SYSTICK_DEV_ERROR_REPORT
    #define SYSTICK_DEV_ERROR_REPORT    STD_OFF
#endif

#if SYSTICK_DEV_ERROR_REPORT == STD_ON
    #define SYSTICK_ReportDevError(func, error)     ReportDevError(SYSTICK_MODULE_ID, func, error)
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * @brief Initializes the SysTick timer.
 *
 * This function initializes the SysTick timer with the provided configuration.
 *
 * @param pTickCfg Pointer to the configuration structure for the SysTick timer.
 */
void SYSTICK_Init(systickType *pTickCfg)
{
    uint8_t u8Temp;

    // Check for a valid configuration pointer and handle errors if enabled
    #if SYSTICK_DEV_ERROR_REPORT == STD_ON
    if (pTickCfg == NULL)
    {
        SYSTICK_ReportDevError(SYSTICK_INIT_ID, SYSTICK_E_PARAM_NULLPTR);
    }
    else
    {
    #endif

        // Reset the value of the counter
        SysTick->VAL = 0U;

        // Set the reload value of the SysTick timer
        SysTick->LOAD = pTickCfg->u32LoadValue;

        // Configure the SysTick timer to use the internal clock and enable interrupt
        u8Temp = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
        SysTick->CTRL = u8Temp;

        #if SYSTICK_DEV_ERROR_REPORT == STD_ON
    }
    #endif
}


/**
 * @brief Enables the SysTick timer.
 *
 * This function enables the SysTick timer.
 */
void SysTick_Enable(void)
{
    // Enable the SysTick timer
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief Disables the SysTick timer.
 *
 * This function disables the SysTick timer.
 */
void SysTick_Disable(void)
{
    // Disable the SysTick timer
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}

/**
 * @brief Returns the current count value of the SysTick timer.
 *
 * This function returns the current count value of the SysTick timer.
 *
 * @return The current count value.
 */
uint32_t SysTick_GetCntValue(void)
{
    // Return the current count value
    return SysTick->CTRL;
}
