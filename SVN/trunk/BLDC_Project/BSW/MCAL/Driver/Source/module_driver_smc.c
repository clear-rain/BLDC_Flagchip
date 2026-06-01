/**
 * @file module_driver_smc.c
 * @author Flagchip032
 * @brief SMC driver source code
 * @version 2.0.0
 * @date 2024-05-15
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip055   N/A          First version
*********************************************************************************/

#include "module_driver_smc.h"

#if SMC_INSTANCE_COUNT > 0U

/**
 * @brief Set system mode
 *
 * @param pControlStruct Smc configuration structure
 * @return Smc return type
 */
SMC_StatusType SMC_SetSystemMode(SMC_ModeType eMode)
{
    SMC_StatusType eRet = SMC_STATUS_SUCCESS;
    if (eMode > SMC_MODE_MAX_ID)
    {
        eRet = SMC_STATUS_PARAM_INVALID;
    }
    else
    {
        switch (eMode)
        {
            case SMC_MODE_RUN:
                /* Clear the SLEEPDEEP bit to disable deep sleep mode */
                CM4_HWA_DisableDeepSleep();

                break;
            case SMC_MODE_STOP:
                /* switch smc mode to stop mode */
                SMC_HWA_SetStopModeCtrl(SMC_STOP_MODE);
                /* Set the SLEEPDEEP bit to enable deep sleep mode (STOP)*/
                CM4_HWA_EnableDeepSleep();

                /* Cpu is going into deep sleep state */
                STANDBY();

                break;

            case SMC_MODE_WAIT:
                /* Clear the SLEEPDEEP bit to disable deep sleep mode */
                CM4_HWA_DisableDeepSleep();

                /* Cpu is going into sleep state */
                STANDBY();

                break;

            case SMC_MODE_STANBY_0:
                /* select standby mode*/
                SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_0);

                /* switch smc mode to standby mode */
                SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);
                /* Set the SLEEPDEEP bit to enable deep sleep mode */
                CM4_HWA_EnableDeepSleep();

                /* Cpu is going into deep sleep state */
                STANDBY();

                break;

            case SMC_MODE_STANBY_1:
                /* select standby mode*/
                SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_1);

                /* switch smc mode to standby mode */
                SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);

                /* Set the SLEEPDEEP bit to enable deep sleep mode */
                CM4_HWA_EnableDeepSleep();

                /* Cpu is going into deep sleep state */
                STANDBY();
                break;

            case SMC_MODE_STANBY_2:
                /* select standby mode*/
                SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_2);

                /* switch smc mode to standby mode */
                SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);

                /* Set the SLEEPDEEP bit to enable deep sleep mode */
                CM4_HWA_EnableDeepSleep();

                /* Cpu is going into deep sleep state */
                STANDBY();
                break;

            case SMC_MODE_STANBY_3:
                /* select standby mode*/
                SMC_HWA_SetStandbyMode(SMC_CFG_STANDBY_3);

                /* switch smc mode to standby mode */
                SMC_HWA_SetStopModeCtrl(SMC_STANDBY_MODE);

                /* Set the SLEEPDEEP bit to enable deep sleep mode */
                CM4_HWA_EnableDeepSleep();

                /* Cpu is going into deep sleep state */
                STANDBY();
                break;
            default:
                /* do nothing */
                break;

        }
    }
    return eRet;
}

#endif
