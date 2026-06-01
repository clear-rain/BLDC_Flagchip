/**
 * @file module_driver_sec.c
 * @author Flagchip075
 * @brief SEC driver source code
 * @version 2.0.0
 * @date 2024-11-16
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip120   N/A          First version
*********************************************************************************/

#include "module_driver_sec.h"

#if SEC_INSTANCE_COUNT > 0U

#ifndef SEC_DEV_ERROR_REPORT
#define SEC_DEV_ERROR_REPORT	STD_OFF
#endif

#if SEC_DEV_ERROR_REPORT == STD_ON
#define SEC_ReportDevError(func, error) ReportDevError(SEC_MODULE_ID, func, error)
#endif

static SEC_Type *const s_pSEC_Instance = SEC;

/**
 * @brief This function can be used to enable the Debug mode.
 * @return  true means enable debug success ,false means enable debug failed.
 **/
bool SEC_EnDebugMode(void)
{
    bool ret = false;
    if (SEC_HWA_GetWritePer(s_pSEC_Instance))
    {
        SEC_HWA_EnDebug(s_pSEC_Instance);
        ret = true;
    }
    return ret;
}



/**
 * @brief This function can be used to  re-enable the Debug mode by the re-enable keys.
 * @param keys The Debug mode re-enable keys.
 * @return true means re-enable success,false means re-enable failed.
 **/
bool SEC_ReEnDebugMode(const ReEnDebug_Keys keys)
{
    bool ret = false;
    if (SEC_HWA_GetReEnDebug(s_pSEC_Instance))
    {
        SEC_HWA_WriteReEnKeyn(s_pSEC_Instance, 0u, keys.Re_key0);
        SEC_HWA_WriteReEnKeyn(s_pSEC_Instance, 1u, keys.Re_key1);
        SEC_HWA_WriteReEnKeyn(s_pSEC_Instance, 2u, keys.Re_key2);
        SEC_HWA_WriteReEnKeyn(s_pSEC_Instance, 3u, keys.Re_key3);
        ret = true;
    }
    return ret;
}

/**
 * @brief This function can get the system state (secured or no secured).
 **/
Systemstate SEC_SystemSecureState(void)
{
    Systemstate  ret =  Securedstate ;
    uint16_t sskey0 = SEC_HWA_GetSScontrol0(s_pSEC_Instance);
    uint16_t sskey1 = SEC_HWA_GetSScontrol1(s_pSEC_Instance);
    if ((sskey0 == 0xC35AU) && (sskey1 == 0xFFFFU))
    {
        ret = UnSecuredstate;
    }
    return ret ;
}


/**
 * @brief This function can enable the test mode.
 * @return true means enable test mode success,false means enable test mode failed.
 **/
bool SEC_EnTestMode(void)
{

    bool ret = false;
    if (SEC_HWA_GetWritePer(s_pSEC_Instance))
    {
        SEC_HWA_EnTest(s_pSEC_Instance);
        ret = true;
    }
    return ret;
}


/**
 *@brief This function can Re-enable the test mode by the re-enable key.
 *@param key The test mode re-enable key.The key is up to the user to decide in advance.
 *@return true means re-enable success,false means re-enable failed.
 **/
bool SEC_ReEnTestMode(const uint32_t key)
{
    bool ret = false;

    bool writeper = SEC_HWA_GetWritePer(s_pSEC_Instance);
    bool reentest = SEC_HWA_GetReEnTest(s_pSEC_Instance);
    if ((true == writeper) && (true == reentest))
    {
        SEC_HWA_ReEnTestKey(s_pSEC_Instance, key);
        ret = true;
    }
    return ret;
}


/**
 * @brief This function can used to set the NVR write and read permission.
 * @return true means setPer success,false means setPer failed.
 **/
bool SEC_SetNvrPer(const NVR_Per per)
{
    bool ret = false;
    if (SEC_HWA_GetWritePer(s_pSEC_Instance))
    {
        if (per.ReadEn == true)
        {
            SEC_HWA_EnReadB0NVR(s_pSEC_Instance);
        }
        else
        {
            SEC_HWA_DisReadB0NVR(s_pSEC_Instance);
        }

        if (per.WritEn == true)
        {
            SEC_HWA_EnWriteB0NVR(s_pSEC_Instance);
        }
        else
        {
            SEC_HWA_DisWriteB0NVR(s_pSEC_Instance);
        }
        ret = true;
    }
    return ret;
}


/**
 * @brief  This function can used to sent a Cipher key to HSM.
 * @param chipkey The Cipher key.
 * @return  true means send Cipher success,false means send Cipher failed.
 **/
bool SEC_SendCiperKey(const Cipher_Keys chipkey)
{
    bool ret  = false;
    if (SEC_HWA_GetWritePer(s_pSEC_Instance))
    {
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 0u, chipkey.Cipher_Key0);
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 1u, chipkey.Cipher_Key1);
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 2u, chipkey.Cipher_Key2);
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 3u, chipkey.Cipher_Key3);
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 4u, chipkey.Cipher_Key4);
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 5u, chipkey.Cipher_Key5);
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 6u, chipkey.Cipher_Key6);
        SEC_HWA_WriteCipKey(s_pSEC_Instance, 7u, chipkey.Cipher_Key7);
        ret  = true;
    }
    return ret;
}

#endif

