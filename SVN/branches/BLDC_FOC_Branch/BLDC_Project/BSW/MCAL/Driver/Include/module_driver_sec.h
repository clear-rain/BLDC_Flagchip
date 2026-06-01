
/**
 * @file module_driver_sec.h
 * @author Flagchip075
 * @brief SEC driver type definition and API
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

#ifndef _MODULE_DRIVER_SEC_H_
#define _MODULE_DRIVER_SEC_H_

#include"HwA_sec.h"

#if SEC_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_sec
 * @{
 */
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Debug Re-Enable Key
 * @note  Only if four 32-bit writes match, it will set the DEN to 0x5 to enable
    debug and unlock SEC registers. The key is up to the user to decide in advance.
 **/
typedef struct
{
    uint32_t Re_key0;           /**< The Debug Re-enable key 0*/
    uint32_t Re_key1;           /**< The Debug Re-enable key 1*/
    uint32_t Re_key2;           /**< The Debug Re-enable key 2*/
    uint32_t Re_key3;           /**< The Debug Re-enable key 3*/

} ReEnDebug_Keys;

/**
 * @brief Block Cipher Key
 * @brief Block Cipher Key, pass directly to HSM as external pin.
 * The key is up to the user to decide in advance.
 **/

typedef struct
{
    uint32_t Cipher_Key0;       /**< The Block Cipher Key 0*/
    uint32_t Cipher_Key1;       /**< The Block Cipher Key 1*/
    uint32_t Cipher_Key2;       /**< The Block Cipher Key 2*/
    uint32_t Cipher_Key3;       /**< The Block Cipher Key 3*/
    uint32_t Cipher_Key4;       /**< The Block Cipher Key 4*/
    uint32_t Cipher_Key5;       /**< The Block Cipher Key 5*/
    uint32_t Cipher_Key6;       /**< The Block Cipher Key 6*/
    uint32_t Cipher_Key7;       /**< The Block Cipher Key 7*/
} Cipher_Keys;

/**
 * @brief NVR write and read Permissions.
 * @*/
typedef struct
{
    bool WritEn;                /**< The NVR write permission*/
    bool ReadEn;                /**< The NVR read permission*/
} NVR_Per;



/**
 * @brief Indicate the system state
 *
 **/
typedef enum
{
    Securedstate = 0u,          /**< The system is in secured state*/
    UnSecuredstate = 1u         /**< The system is in no secured state*/
} Systemstate;

/**
 * @brief This function can be used to enable the Debug mode.
 * @return  true means enable debug success ,false means enable debug failed.
 **/
bool SEC_EnDebugMode(void);


/**
 * @brief This function can be used to  re-enable the Debug mode by the re-enable keys.
 * @param keys  The Debug mode re-enable keys.The key is up to the user to decide in advance.
 * @return true means re-enable success,false means re-enable failed.
 **/
bool SEC_ReEnDebugMode(const ReEnDebug_Keys keys);



/**
 * @brief This function can get the system state (secured or no secured).
 **/
Systemstate SEC_SystemSecureState(void);




/**
 * @brief This function can enable the test mode.
 * @return true means enable test mode success,false means enable test mode failed.
 **/
bool SEC_EnTestMode(void);



/**
 *@brief This function can Re-enable the test mode by the re-enable key.
 *@param key The test mode re-enable key.
 *@return true means re-enable success,false means re-enable failed.
 **/
bool SEC_ReEnTestMode(const uint32_t key);



/**
 * @brief This function can used to set the NVR write and read permission.
 * @return true means setPer success,false means setPer failed.
 **/
bool SEC_SetNvrPer(const NVR_Per per);


/**
 * @brief  This function can used to sent a Cipher key to HSM.
 * @param chipkey The Cipher key.
 * @return  true means send Cipher success,false means send Cipher failed.
 **/
bool SEC_SendCiperKey(const Cipher_Keys chipkey);



#if defined(__cplusplus)
}
#endif

/** @}*/

#endif

#endif /* _MODULE_DRIVER_SEC_H_ */
