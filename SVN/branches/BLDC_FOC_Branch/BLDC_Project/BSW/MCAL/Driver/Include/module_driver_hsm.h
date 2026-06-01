/**
 * @file module_driver_hsm.h
 * @author Flagchip051
 * @brief HSM driver type definition and API
 * @version 2.0.0
 * @date 2024-11-04
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip051   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_hsm_H_
#define _DRIVER_MODULE_DRIVER_hsm_H_

#include "device_header.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @addtogroup module_driver_hsm
 * @{
 */


/**
 * @brief Status returned by HSM APIs
 *
 */
typedef enum {
    HSM_STATUS_SUCCESS = 0U,    /**< return this when HSM API execute successfully */
    HSM_STATUS_BUSY,            /**< return this when hsm driver or the hardware is busy now */
    HSM_STATUS_PARAM_ERR,       /**< return this when parameter error */
    HSM_STATUS_ERROR,           /**< return this when some error happen in HSM API */
    HSM_STATUS_ECC_ERROR,       /**< return this when flash ecc error */
    HSM_STATUS_IDLE,            /**< return this when driver has nothing to do */
    HSM_STATUS_ERROR_STOP,      /**< return this when the continous operation in poll API or ISR is stopped due to some error happen */
    HSM_STATUS_FINISH,          /**< return this only when FC4150F512 CMAC/XMAC push data into hardware finish  */
    HSM_STATUS_PASS,            /**< return this when ecc/sm2 verify pass, or check pass in CMAC/XMAC/CCM/GCM which icv check enabled */
    HSM_STATUS_FAIL,            /**< return this when ecc/sm2 verify fail, or check fail in CMAC/XMAC/CCM/GCM which icv check enabled, or get random data fail */
    HSM_STATUS_AGAIN,           /**< return this when the HSM API need call again */
    HSM_STATUS_LOGIC_ERR,       /**< return this when HSM API called in wrong logic */
    HSM_STATUS_HW_ERR,          /**< return this when the HSM hardware error happen */
    HSM_STATUS_HW_IDLE,         /**< return this when the HSM hardware has nothing to do */
    HSM_STATUS_ALREADY_FINISHED,/**< return this only when FC4150F512 CMAC/XMAC has pushed all data into the hardware */
    HSM_STATUS_NOT_SUPPORT,     /**< return this when driver not support the usage */
} HSM_StatusType;

/**
 * @name Type definition for HSM Isr/Poll mode
 *
 */
/**@{*/

/**
 * @brief Poll mode value for type "HSM_TriggerSrcType"
 *
 * HSM driver can work in two mode:Isr mode and poll mode.
 * In poll mode, Hsm interrupt is disabled, if the algorithm need more than one step in driver,
 * driver API user should call the API to trigger the internal state machine go to next state.
 * If don't need trigger the process any more, user should call the specific API to get the result state more than one time until driver API return it actually.
 * Driver user use this to configure the driver running mode when call HSM_Init to initialize the driver.
 */
#define HSM_TRIGGER_SRC_USER_POLL (0U)

/**
 * @brief Isr mode value for type "HSM_TriggerSrcType"
 *
 * HSM driver can work in two mode:Isr mode and poll mode.
 * In Isr mode, Hsm interrupt is enabled, driver API user only call the specific API to start the process.
 * If the algorithm need more than one step in driver, the isr will trigger the next process step in driver internal.
 * After all steps finished, and the result will be passed to the callback registered in the init API called by driver user.
 * So if driver user want to use isr mode, you should use this mode and set the callback function into the driver when call HSM_Init.
 * Driver user use this to configure the driver running mode when initializes the driver.
 */
#define HSM_TRIGGER_SRC_ISR       (1U)

/**
 * @brief type definition for HSM_Init
 *
 * HSM driver can work in two mode:Isr mode and poll mode.
 * Isr mode's detail can refer to HSM_TRIGGER_SRC_ISR.
 * Poll mode's detail can refer to HSM_TRIGGER_SRC_USER_POLL
 */
typedef uint32_t HSM_TriggerSrcType;

/**
 * @brief HSM 4bytes unit data format for HSM_DataFormatType
 * for example, if data is 0x000102030405060708090a0b0c0d0e0f, use this format, should be divided as following.
 * 0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f
 */
#define HSM_DATA_FORMAT_4B    0u

/**
 * @brief HSM 1byte unit data format for HSM_DataFormatType
 * for example, if data is 0x000102030405060708090a0b0c0d0e0f, use this format, should be divided as following.
 * 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
 */
#define HSM_DATA_FORMAT_1B    1u

/**
 * @brief HSM  data format
 * refer to HSM_DATA_FORMAT_4B, HSM_DATA_FORMAT_1B
 */
typedef uint32_t HSM_DataFormatType;


/**
 * @brief AES128 key type value for type "HSM_AesKeyBitCntType"
 *
 */
#define HSM_AES_KEY128  (0U)

/**
 * @brief AES192 key type value for type "HSM_AesKeyBitCntType"
 *
 */
#define HSM_AES_KEY192  (1U)

/**
 * @brief AES256 key type value for type "HSM_AesKeyBitCntType"
 *
 */
#define HSM_AES_KEY256  (2U)

/**
 * @brief type definition for AES key
 *
 * HSM support AES128/192/256, driver api use this to select the algorithm.
 */
typedef uint32_t HSM_AesKeyBitCntType;

/**
 * @brief AES CTR mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_CTR  (0U)

/**
 * @brief AES CBC mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_CBC  (1U)

/**
 * @brief AES ECB mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_ECB  (2U)

/**
 * @brief AES CFB mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_CFB  (3U)

/**
 * @brief AES OFB mode value for type "HSM_AesEnDecryptAlgType"
 *
 */
#define HSM_AES_OFB  (4U)

/**
 * @brief type definition for AES encrypt/decrypt mode
 *
 * HSM support CTR/CBC/ECB/CFB/OFB mode, driver api use this to select the encrypt/decrypt mode.
 */
typedef uint32_t HSM_AesEnDecryptAlgType;

/**
 * @brief vendor key value for type "HSM_AesKeyType"
 *
 * HSM hardware support accessing the aes key stored in nvr flash directly,
 * chip user should program the key in flash already.
 * This way don't need software read data and write it to some place,
 * hardware will read the data itself automatically.
 */
#define HSM_AES_KEY_CHIP_VENDOR_IFR (0U) /* key has existed in Flash IFR, it provided by chip hardware, not changeable */

/**
 * @brief driver user's new key value for type "HSM_AesKeyType"
 *
 * HSM use the key passed by driver API user.
 */
#define HSM_AES_KEY_NEW             (1U) /* user should provide the new key */

/**
 * @brief driver user's new key value for type "HSM_AesKeyType"
 *
 * Note: This key is supported from FC4150F1MB chip.
 * First, user should program the NVR control bit BRC1(BootROM Configuration 1) bit 22(Enable the output of plaintext decrypted by ROOT key) to 0 to enable,
 *        this force the hsm device to output the decrypted result to hsm device internal when use key HSM_AES_KEY_CHIP_VENDOR_IFR. Reset the chip, no need do this again, just do it once.
 * Second, use the HSM_AES_KEY_CHIP_VENDOR_IFR type key to decrypt the encrypted text.
 * Third, use the HSM_AES_KEY_DERIVED type key do others.
 */
#define HSM_AES_KEY_DERIVED         (2U) /* the key is derived from the encrypted text by IFR key */

/**
 * @brief type definition for the key source
 *
 * key from the nvr refer to HSM_AES_KEY_CHIP_VENDOR_IFR
 * key from driver user's parameters refer to HSM_AES_KEY_NEW
 * key from encrypted data refer to HSM_AES_KEY_DERIVED
 */
typedef uint32_t HSM_AesKeyType;

/**
 * @brief CMAC(CBC-MAC) algorithm value for type "HSM_XCMacAlgType"
 *
 */
#define HSM_MAC_CMAC  (0U)

/**
 * @brief XMAC(XCBC-MAC) algorithm value for type "HSM_XCMacAlgType"
 *
 */
#define HSM_MAC_XMAC  (1U) /* xcbc mac */

/**
 * @brief type definition for MAC algorithm
 *
 * Support use AES or SM4 as the backend.
 */
typedef uint32_t HSM_XCMacAlgType;

/**
 * @brief SHA160 algorithm value for type "HSM_ShaAlgType/HSM_HashAlgType"
 *
 */
#define HSM_SHA_160     (1U)

/**
 * @brief SHA224 algorithm value for type "HSM_ShaAlgType/HSM_HashAlgType"
 *
 */
#define HSM_SHA_224     (2U)

/**
 * @brief SHA256 algorithm value for type "HSM_ShaAlgType/HSM_HashAlgType"
 *
 */
#define HSM_SHA_256     (3U)

/**
 * @brief SHA384 algorithm value for type "HSM_ShaAlgType/HSM_HashAlgType"
 *
 */
#define HSM_SHA_384     (4U)

/**
 * @brief SHA512 algorithm value for type "HSM_ShaAlgType/HSM_HashAlgType"
 *
 */
#define HSM_SHA_512     (5U)

/**
 * @brief SHA512/224 algorithm value for type "HSM_ShaAlgType/HSM_HashAlgType"
 *
 */
#define HSM_SHA_512_224 (6U)

/**
 * @brief SHA512/256 algorithm value for type "HSM_ShaAlgType/HSM_HashAlgType"
 *
 */
#define HSM_SHA_512_256 (7U)

/**
 * @brief type definition for SHA algorithm
 * refer to HSM_SHA_160,HSM_SHA_224,HSM_SHA_256,HSM_SHA_384,HSM_SHA_512,HSM_SHA_512_224,HSM_SHA_512_256
 */
typedef uint32_t HSM_ShaAlgType;

/**
 * @brief MD5 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_MD5          (0U)

/**
 * @brief SHA160 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA_160      (1U)

/**
 * @brief SHA224 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA_224      (2U)

/**
 * @brief SHA256 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA_256      (3U)

/**
 * @brief SHA384 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA_384      (4U)

/**
 * @brief SHA512 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA_512      (5U)

/**
 * @brief SHA512/224 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA_512_224  (6U)

/**
 * @brief SHA512/256 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SHA_512_256  (7U)

/**
 * @brief SM3 algorithm value for type "HSM_HashAlgType"
 *
 */
#define HSM_HASH_SM3          (8U)
/**
 * @brief type definition for SHA algorithm
 * refer to HSM_SHA_160,HSM_SHA_224,HSM_SHA_256,HSM_SHA_384,HSM_SHA_512,HSM_SHA_512_224,HSM_SHA_512_256,HSM_HASH_MD5,HSM_HASH_SM3
 */
typedef uint32_t HSM_HashAlgType;

/**
 * @brief SMAC mode value for type "HSM_HfamMacType"
 *
 */
#define HSM_HFAM_MAC_SMAC (0U)

/**
 * @brief HMAC mode value for type "HSM_HfamMacType"
 *
 */
#define HSM_HFAM_MAC_HMAC (1U)

/**
 * @brief SM3/MD5/SHA can generate MAC, use this to select the type of MAC
 * SMAC refer to HSM_HFAM_MAC_SMAC
 * HMAC refer to HSM_HFAM_MAC_HMAC
 */
typedef uint32_t HSM_HfamMacType;

/**
 * @brief vendor key value for type "HSM_Sm4KeyType"
 *
 * HSM hardware support accessing the SM4 key stored in nvr flash directly,
 * chip user should program the key in flash already.
 * This way don't need software read data and write it to some place,
 * hardware will read the data itself automatically.
 */
#define HSM_SM4_KEY_CHIP_VENDOR_IFR (0U) /* key has existed in Flash IFR, it provided by chip, not changeable */

/**
 * @brief driver user's new key value for type "HSM_Sm4KeyType"
 *
 * HSM use the key passed by driver API user.
 */
#define HSM_SM4_KEY_NEW             (1U) /* user should provide the new key */

/**
 * @brief driver user's new key value for type "HSM_AesKeyType"
 *
 * Note: This key is supported from FC4150F1MB chip.
 * First, user should program the NVR control bit BRC1(BootROM Configuration 1) bit 22(Enable the output of plaintext decrypted by ROOT key) to 0 to enable,
 *        this force the hsm device to output the decrypted result to hsm device internal when use key HSM_SM4_KEY_CHIP_VENDOR_IFR. Reset the chip, no need do this again, just do it once.
 * Second, use the HSM_SM4_KEY_CHIP_VENDOR_IFR type key to decrypt the encrypted text.
 * Third, use the HSM_SM4_KEY_DERIVED type key do others.
 */
#define HSM_SM4_KEY_DERIVED         (2U) /* the key is derived from the encrypted text by IFR key */

typedef uint32_t HSM_Sm4KeyType;

/**
 * @brief SM4 CTR mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_CTR (0U)

/**
 * @brief SM4 CBC mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_CBC (1U)

/**
 * @brief SM4 ECB mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_ECB (2U)

/**
 * @brief SM4 CFB mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_CFB (3U)

/**
 * @brief SM4 OFB mode value for type "HSM_Sm4EnDecryptAlgType"
 *
 */
#define HSM_SM4_OFB (4U)

/**
 * @brief type definition for SM4 encrypt/decrypt mode
 *
 * HSM support CTR/CBC/ECB/CFB/OFB mode, driver api use this to select the encrypt/decrypt mode.
 */
typedef uint32_t HSM_Sm4EnDecryptAlgType;

/**
 * @brief Boolean false value definition for type HSM_BoolType used by HSM
 *
 */
#define         HSM_FALSE (0u)

/**
 * @brief Boolean true value definition for type HSM_BoolType used by HSM
 *
 */
#define         HSM_TRUE  (1u)

/**
 * @brief Boolean type for HSM
 *
 */
typedef uint32_t HSM_BoolType; /* one byte ensure read atomicly */

/**
 * @brief ECC curve NIST SECP224R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP224R1 (0U)

/**
 * @brief ECC curve NIST SECP256R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP256R1 (1U)

/**
 * @brief ECC curve NIST SECP384R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP384R1 (2U)

/**
 * @brief ECC curve NIST SECP521R1 value for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_SECP521R1 (3U)

/**
 * @brief max count of ECC curve supported for type "HSM_DrvEccCurvePrmIndexType"
 *
 */
#define HSM_DRV_ECC_CURVE_PRM_IDX_MAX       (4U)

/**
 * @brief type definition for ECC curve data that defined by NIST
 *
 */
typedef uint32_t HSM_DrvEccCurvePrmIndexType;

/**
 * @brief the true random count return by the API
 *
 */
#define TRNG_RANDOM_NUMBER_CNT 16



/**
 * @brief type definition for True random hardware instance
 *
 * FC4150 series only support one instance.
 * FC7300 series support two instance.
 */
typedef uint32_t HSM_TrngInstanceType;

/**
 * @brief type definition for algorithm stop callback registered in HSM_Init API.
 *
 */
typedef void (*HSM_StopCbType)(HSM_StatusType eRet);

/**
 * @brief type definition for isr enable/disable callback registered in HSM_Init API.
 *
 */
typedef void (*HSM_IsrEnableCbType)(HSM_BoolType);

/**
 * @brief init parameters for HSM_Init
 *
 */
typedef struct {
    HSM_TriggerSrcType  eTriggerSrc; /**< the driver internal status change triggered by interrupt or user poll  */
    HSM_StopCbType      pStopCb; /**< if eTriggerSrc is interrupt(HSM_TRIGGER_SRC_ISR), when the driver stop, this callback will be invoked by driver if it's configured */
    HSM_IsrEnableCbType pIsrEnCb; /**< driver internal use this callback to enable/disable hsm interrupt */
} HSM_InitCfgType;

/**
 * @brief key information used by AES when use one key in software
 *
 */
typedef struct {
    HSM_AesKeyBitCntType  eKeyType; /**< the key bit count, which determine the AES algorithm type */
    const uint8_t        *pKeyAddr; /**< the key data pointer, the start address should 4bytes align, the buffer array should declared by uint32_t */
} HSM_AesNewKeyInfType;

/**
 * @brief key information used by AES when use one key in nvr flash
 *
 */
typedef struct {
    HSM_AesKeyBitCntType eKeyType; /**< the key bit count, which determine the AES algorithm type */
} HSM_AesVendorKeyInfType;

/**
 * @brief AES hardware backend for CMAC/XMAC for type "HSM_XCMAC_BackendType"
 *
 */
#define HSM_XCMAC_BACKEND_AES 0u

/**
 * @brief SM4 hardware backend for CMAC/XMAC for type "HSM_XCMAC_BackendType"
 *
 */
#define HSM_XCMAC_BACKEND_SM4 1u

/**
 * @brief type definition for CMAC/XMAC's hardware backend
 * AES backend refer to HSM_XCMAC_BACKEND_AES
 * SM4 backend refer to HSM_XCMAC_BACKEND_SM4
 */
typedef uint32_t  HSM_XCMAC_BackendType;

/**
 * @brief CMAC/XMAC information used by driver when call specific API
 *
 */
typedef struct {
    HSM_XCMAC_BackendType       eBackend; /**< HSM_XCMAC_BACKEND_AES:aes+x/cmac or HSM_XCMAC_BACKEND_SM4:sm4+x/cmac */
    HSM_AesKeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR/HSM_AES_KEY_DERIVED, this MUST configure */
    uint32_t                    u32GenMacByteCnt; /**< XCMAC API generate MAC data, it's "u32GenMacByteCnt" size ICV data */
    HSM_BoolType                bCheckMacEn;  /**< if enable this check, user should place the data after the input data, hsm will check the generated data and it, if fail, hsm generate a interrupt, and if user get hw status, will get a error status */

    const uint8_t              *pDataInput; /**< start address should align with 4bytes */
    uint32_t                    u32InputByteCnt; /**< the input data byte count, no need 16bytes aligned */
    uint8_t                    *pDataOutput; /**< start address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /**< 4bytes align, the output data buffer "pDataOutput" size, should >= "u32GenMacByteCnt" */

    HSM_DataFormatType          eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType          eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
} HSM_XCMacType;

/**
 * @brief CMAC information used by driver when call specific API
 *
 */
typedef HSM_XCMacType HSM_CMacType;

/**
 * @brief XMAC information used by driver when call specific API
 *
 */
typedef HSM_XCMacType HSM_XMacType;

/**
 * @brief AES hardware backend for CCM for type "HSM_CcmBackendType"
 *
 */
#define HSM_CCM_BACKEND_AES 0u

/**
 * @brief SM4 hardware backend for CCM for type "HSM_CcmBackendType"
 *
 */
#define HSM_CCM_BACKEND_SM4 1u

/**
 * @brief type definition for CCM's hardware backend
 * AES backend refer to HSM_CCM_BACKEND_AES
 * SM4 backend refer to HSM_CCM_BACKEND_SM4
 */
typedef uint32_t  HSM_CcmBackendType;

/**
 * @brief CCM Encrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_CcmBackendType          eBackend; /**< HSM_CCM_BACKEND_AES use aes for ccm, or HSM_CCM_BACKEND_SM4:sm4 for ccm */
    HSM_AesKeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */

    const uint8_t              *pAllData; /**< start address should align with 4bytes, place AAD data(16bytes align) first, then input data */
    uint32_t                    u32AadByteCnt; /**< the byte count contain the 2bytes in the head, it's the valid data size, not after aligned, 128bit(16Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /**< 128bit(16Bytes) align, ONLY represent data */

    uint32_t                    u32GenMacByteCnt; /**< output mac size */
    uint8_t                    *pDataOutput; /**< start address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /**< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */

    const uint8_t              *pIvData;  /**< 32bytes array, start address should align with 4bytes, iv data, consist of 16bytes B0 data, and 16bytes CTR,  MUST configure */
    uint8_t                    *pMacOut;  /**< 16bytes array, start address should align with 4bytes, HSM generated MAC data */
    uint8_t                    *pEmacOut; /**< 16bytes array, start address should align with 4bytes, HSM generated encrypted MAC data */
} HSM_CcmEncryptType;


/**
 * @brief CCM Decrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_CcmBackendType          eBackend;    /**< HSM_CCM_BACKEND_AES use aes for ccm, or HSM_CCM_BACKEND_SM4:sm4 for ccm */
    HSM_AesKeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */



    const uint8_t              *pAllData; /**< start address should align with 4bytes, place AAD data(if exist, 16bytes align) first, then input data, then MAC data(if exist) */

    uint32_t                    u32AadByteCnt; /**< 128bit(16Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /**< 128bit(16Bytes) align */
    HSM_BoolType                bCheckMacEn; /**< check the MAC data in input or not */
    uint32_t                    u32MacByteCnt; /**< 128bit(16Bytes) align */

    uint8_t                    *pDataOutput; /**< start address should 4bytes align, point to the buffer that store the result */
    uint32_t                    u32OutputMemSize; /**< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */

    const uint8_t              *pIvData; /**< 32bytes array, start address should align with 4bytes, iv data, consist of 16bytes B0 data, and 16bytes CTR,  MUST configure */
} HSM_CcmDecryptType;


/**
 * @brief AES hardware backend for GCM for type "HSM_GcmBackendType"
 *
 */
#define HSM_GCM_BACKEND_AES 0u

/**
 * @brief SM4 hardware backend for GCM for type "HSM_GcmBackendType"
 *
 */
#define HSM_GCM_BACKEND_SM4 1u

/**
 * @brief type definition for GCM's hardware backend
 * AES backend refer to HSM_GCM_BACKEND_AES
 * SM4 backend refer to HSM_GCM_BACKEND_SM4
 */
typedef uint32_t  HSM_GcmBackendType;


/**
 * @brief GCM Encrypt information used by driver when call specific API
 *
 */
typedef  struct {
    HSM_GcmBackendType          eBackend; /**< HSM_GCM_BACKEND_AES use aes for gcm, or HSM_GCM_BACKEND_SM4:sm4 for gcm */
    HSM_AesKeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */

    const uint8_t              *pAllData; /**< start address should align with 4bytes, place IV data first, then AAD data(16bytes align), then input data */
    uint32_t                    u32IvDataByteCnt; /**< 64bit(8Bytes) align, if not, only the aligned data treat as IV, the left IV bytes will be treated as AAD data  */
    uint32_t                    u32AadByteCnt; /**< 64bit(8Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /**< 128bit(16Bytes) align */

    uint32_t                    u32GenMacByteCnt; /**< set the MAC result byte count */
    uint8_t                    *pDataOutput; /**< start address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /**< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint8_t                    *pMacOut; /**< 16bytes array, start address should align with 4bytes, HSM generated encrypted MAC data */
}  HSM_GcmEncryptType;

/**
 * @brief GCM Decrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_GcmBackendType          eBackend; /**< HSM_GCM_BACKEND_AES use aes for gcm, or HSM_GCM_BACKEND_SM4:sm4 for gcm */
    HSM_AesKeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */

    const uint8_t              *pAllData; /**< start address should align with 4bytes, place IV data first, then AAD data(if exist, 16bytes align), then input data, then MAC data(if exist) */
    uint32_t                    u32IvDataByteCnt; /**< 64bit(8Bytes) align, if not, only the aligned data treat as IV, the left IV bytes will be treated as AAD data  */
    uint32_t                    u32AadByteCnt; /**< 64bit(8Bytes) align, if not, only the aligned data treat as AAD, the left AAD bytes will be treated as input data  */
    uint32_t                    u32InputByteCnt; /**< 128bit(16Bytes) align */
    HSM_BoolType                bCheckMacEn; /**< check the MAC data in input or not */
    uint32_t                    u32MacByteCnt; /**< 128bit(16Bytes) align */

    uint8_t                    *pDataOutput; /**< start address should 4bytes align, point to the buffer that store the result */
    uint32_t                    u32OutputMemSize; /**< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
} HSM_GcmDecryptType;


/**
 * @brief AES encrypt/decrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_AesKeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR/HSM_AES_KEY_DERIVED, this MUST configure */
    HSM_AesEnDecryptAlgType     eAesAlg; /**< encrypt/decrypt mode */

    const uint8_t              *pDataInput;      /**< start address should align with 4bytes */
    uint32_t                    u32InputByteCnt; /**< 128bit(16Bytes) align */
    uint8_t                    *pDataOutput; /**< start address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /**< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */

    const uint8_t              *pIvData; /**< 16bytes array, start address should align with 4bytes, 128bit(16Bytes) iv(initialization vector) data array, ECB not need configure this */
} HSM_AesEnDecryptType;


/**
 * @brief AES encrypt information used by driver when call specific API
 *
 */
typedef HSM_AesEnDecryptType HSM_AesDecryptType;


/**
 * @brief AES decrypt information used by driver when call specific API
 *
 */
typedef HSM_AesEnDecryptType HSM_AesEncryptType;


/**
 * @brief SHA/MD5/SM3 context information used by driver when call specific API
 *
 */
typedef struct {
    HSM_BoolType       bGenerateMacEn; /**< whether generate MAC */
    HSM_HfamMacType    eMacType; /* !< if enable generating MAC, this should configure */
    const uint8_t     *pKeyData; /* !< start address should 4bytes align, key to generate MAC, if enable generating MAC, this should configure */
    uint32_t           u32KeyByteCnt; /* !< the byte count of key data, max 1024bits */
    uint32_t           u32GenerateMacByteCnt; /* !< the byte count of MAC data output, max is according to SHA/MD5/SM3 result length */

    uint32_t           u32InputDataByteCnt; /* !< the byte count of input data */
    const uint8_t     *pInputData; /**< start address should 4bytes align, point to the input data */
} HSM_SmsCfgType; /* sms is short for sha/md5/sm3 */

/**
 * @brief SHA context information used by driver when call specific API
 *
 */
typedef HSM_SmsCfgType HSM_ShaCtxType;

/**
 * @brief MD5 context information used by driver when call specific API
 *
 */
typedef HSM_SmsCfgType HSM_Md5CtxType;

/**
 * @brief SM3 context information used by driver when call specific API
 *
 */
typedef HSM_SmsCfgType HSM_Sm3CtxType;

/**
 * @brief SHA/MD5/SM3 scatter api context information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t           u32InputDataByteCnt; /* !< the byte count of input data */
    const uint8_t     *pInputData; /**< start address should 4bytes align, point to the input data */
} HSM_SmsScatterCfgType; /* sms is short for sha/md5/sm3 */

/**
 * @brief SHA Scatter context information used by driver when call specific API
 *
 */
typedef HSM_SmsScatterCfgType HSM_ShaScatterCtxType;

/**
 * @brief MD5 Scatter context information used by driver when call specific API
 *
 */
typedef HSM_SmsScatterCfgType HSM_Md5ScatterCtxType;

/**
 * @brief SM3 Scatter context information used by driver when call specific API
 *
 */
typedef HSM_SmsScatterCfgType HSM_Sm3ScatterCtxType;


/**
 * @brief type definition for driver to store information
 *
 */
typedef struct {
    uint8_t aResult[64]; /**< store the sha result, max size 64bytes is for SHA512 */
    uint32_t u32ByteCnt; /**< store the result uint8_t count, it's set by driver */
} HSM_ShaResultBufType;

/**
 * @brief SHA information used by driver when call specific API
 *
 */
typedef struct {
    HSM_ShaAlgType        eAlg; /**< select sha algorithm type */
    HSM_ShaCtxType        tCfg; /**< sha algorithm parameter set by user */
    uint8_t              *pResult; /**< point to the memory that driver to store result */
    uint32_t              u32ResultBufSize; /**< the size of buffer 'pResult' to store result */
    HSM_DataFormatType    eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType    eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
} HSM_ShaType;

/**
 * @brief MD5 information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Md5CtxType        tCfg; /**< MD5 algorithm parameter set by user */
    uint8_t              *pResult; /**< MD5 result is 16bytes, point to the memory that driver to store result */
    uint32_t              u32ResultBufSize; /**< the size of buffer 'pResult' to store result */
    HSM_DataFormatType    eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType    eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
} HSM_Md5Type;

/**
 * @brief SM3 information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Sm3CtxType        tCfg; /**< sm3 algorithm parameter set by user */
    uint8_t              *pResult; /**< sm3 result is 32bytes, point to the memory that driver to store result */
    uint32_t              u32ResultBufSize; /**< the size of buffer 'pResult' to store result */
    HSM_DataFormatType    eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType    eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
} HSM_Sm3Type;

/**
 * @brief SHA Scatter API init information used by driver when call specific API
 *
 */
typedef struct {
    HSM_ShaAlgType         eAlg; /**< select sha algorithm type */
    HSM_ShaScatterCtxType  tCfg; /**< sha algorithm parameter set by user */
} HSM_ScatterShaInitType;

/**
 * @brief SHA Scatter API finalize information used by driver when call specific API
 *
 */
typedef struct {
    HSM_ShaScatterCtxType  tCfg; /**< sha algorithm parameter set by user */
    HSM_ShaResultBufType *pResult; /**< point to the memory that driver to store result */
} HSM_ScatterShaFinalType;


/**
 * @brief MD5 Scatter API init information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Md5ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
} HSM_ScatterMd5InitType;

/**
 * @brief MD5 Scatter API finalize information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Md5ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
    uint8_t               *pRet; /**< 16bytes array, start address should align with 4bytes, point to the memory that driver to store result */
} HSM_ScatterMd5FinalType;


/**
 * @brief SM3 Scatter API init information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Sm3ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
} HSM_ScatterSm3InitType;

/**
 * @brief SM3 Scatter API finalize information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Sm3ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
    uint8_t               *pRet; /**< 32bytes array, start address should align with 4bytes, point to the memory that driver to store result */
} HSM_ScatterSm3FinalType;

/**
 * @brief SHA Scatter API init information used by driver when call specific API
 *
 */
typedef struct {
    HSM_ShaAlgType         eAlg; /**< select sha algorithm type */
    HSM_ShaScatterCtxType  tCfg; /**< sha algorithm parameter set by user */
    HSM_DataFormatType     eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
} HSM_ShaInitType;

/**
 * @brief SHA Scatter API finalize information used by driver when call specific API
 *
 */
typedef struct {
    HSM_ShaScatterCtxType  tCfg; /**< sha algorithm parameter set by user */
    uint8_t               *pResult; /**< point to the memory that driver to store result */
    uint32_t               u32ResultBufSize; /**< the size of buffer 'pResult' to store result */
    HSM_DataFormatType     eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
} HSM_ShaFinalType;

/**
 * @brief MD5 Scatter API init information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Md5ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
    HSM_DataFormatType     eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
} HSM_Md5InitType;

/**
 * @brief MD5 Scatter API finalize information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Md5ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
    uint8_t               *pResult; /**< point to the memory uint8_t[16] that driver to store result */
    uint32_t               u32ResultBufSize; /**< the size of buffer 'pResult' to store result */
    HSM_DataFormatType     eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
} HSM_Md5FinalType;


/**
 * @brief SM3 Scatter API init information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Sm3ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
    HSM_DataFormatType     eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
} HSM_Sm3InitType;

/**
 * @brief SM3 Scatter API finalize information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Sm3ScatterCtxType  tCfg; /**< MD5 algorithm parameter set by user */
    uint8_t               *pResult; /**< point to the memory uint8_t[32] that driver to store result */
    uint32_t               u32ResultBufSize; /**< the size of buffer 'pResult' to store result */
    HSM_DataFormatType     eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
} HSM_Sm3FinalType;

/**
 * @brief HMAC/SMAC information used by driver when call specific API
 *
 */
typedef struct {
    HSM_HfamMacType       eMacType; /* !< if enable generating MAC, this should configure */
    const uint8_t        *pKeyData; /* !< key to generate MAC, if enable generating MAC, this should configure */
    uint32_t              u32KeyByteCnt; /* !< the byte count of key data, max 1024bits */
    HSM_DataFormatType    eKeyFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    uint32_t              u32GenerateMacByteCnt; /* !< the byte count of MAC data output, max is according to SHA/MD5/SM3 result length */
} HSM_HashMacType;

/**
 * @brief RSA information used by driver when call specific API
 *
 */
typedef struct {
    const uint8_t      *pInputData; /**< input data A */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data A */
    HSM_DataFormatType  eInputDataFmt;

    const uint8_t      *pKeyE; /**< input key E data for "result = (input data)^E mod N" */
    uint32_t            u32KeyEByteCount; /**< the byte count of key E */
    HSM_DataFormatType  eKeyEFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyN; /**< input key N data for "result = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< hw will get the actual key data bit count according to the non-zero bit count, it means key not generate by multiply 2 */
    HSM_DataFormatType  eKeyNFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /* point to the variable to store the output result length */
} HSM_RsaType;

/**
 * @brief RSA SSA input data is the raw message for HSM_RsaSsaInputType
 *
 */
#define HSM_RSA_SSA_INPUT_RAW_MESSAGE  0u

/**
 * @brief RSA SSA input data is the hash value of raw message for HSM_RsaSsaInputType
 *
 */
#define HSM_RSA_SSA_INPUT_HASH_DATA    1u

/**
 * @brief type definition for rsa ssa input data type
 * refer to HSM_RSA_SSA_INPUT_RAW_MESSAGE, HSM_RSA_SSA_INPUT_HASH_DATA
 */
typedef uint32_t HSM_RsaSsaInputType;


/**
 * @brief RSA PSS signature information used by driver when call specific API
 *
 */
typedef struct {
    HSM_HashAlgType     eMgfHashType; /**< the hash type used by MGF1 */
    HSM_DataFormatType  eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */

    uint32_t            u32EmBitCnt; /* RFC8017 require set it to (N's bit count - 1).the em data bit count, it MUST < N's bit count */

    HSM_HashAlgType     eHashType; /**< the hash type used by signature */
    HSM_RsaSsaInputType eInputType; /**< input data type, may raw input message, or the hash data of raw message */
    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data */

    const uint8_t      *pPrivateKey; /**< private key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PrivateKeyByteCnt; /**< the byte count of key E */

    HSM_BoolType        bUseInputSaltData;  /**< use input salt data or not, , suggest set to HSM_FALSE to use internal random data */
    const uint8_t      *pSalt; /**< input salt data, , suggest set to NULL. if use hsm internal random data, just set it to NULL */
    uint32_t            u32SaltByteCount; /**< the byte count of salt data, it must > 0, suggest use hash length, for example, if eHashType is HSM_SHA_256, set this to 256/8=32bytes */

    const uint8_t      *pKeyN; /**< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< key N's data byte count */


    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    uint32_t           *pResultByteCnt; /**< the result data byte count */

    uint32_t            u32TrailerField;  /**< if you don't know how to set it, just set it to 0xbc, the trailer byte data, here use uint32_t for align, the valid data is u32TrailerField & 0xff */
} HSM_RsaSsaPssSignType;



/**
 * @brief RSA PSS signature verify information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t            u32EmBitCnt; /* RFC8017 require set it to (N's bit count - 1). the em data bit count, it MUST < N's bit count, should keep same with the signature generate configuration */
    HSM_HashAlgType     eMgfHashType; /**< the hash type used by signature */
    HSM_HashAlgType     eHashType; /**< the hash type used by signature */
    uint32_t            u32SaltByteCount; /**< the byte count of salt data, it must > 0, suggest use hash length, for example, if eHashType is HSM_SHA_256, set this to 256/8=32bytes */

    HSM_DataFormatType  eInputDataFmt; /**< input data(raw message or hash data) organized format, uint8_t array, or uint32_t array */
    HSM_RsaSsaInputType eInputType; /**< input data type, may raw input message, or the hash data of raw message */
    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data, when the eInputType is HSM_RSA_SSA_INPUT_RAW_MESSAGE */

    HSM_DataFormatType  eInputSPNFmt; /**< Signature/Public key/N input data organized format, uint8_t array, or uint32_t array */
    const uint8_t      *pSignData; /**< input signature data */
    uint32_t            u32SignDataByteCount; /**< the byte count of signature data, it must > 0 */

    const uint8_t      *pPublicKey; /**< public key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PublicKeyByteCnt; /**< the byte count of key E */

    const uint8_t      *pKeyN; /**< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< key N data byte count */

    uint32_t            u32TrailerField; /**< if you don't know how to set it, just set it to 0xbc, the trailer byte data, here use uint32_t for align, the valid data is u32TrailerField & 0xff */
} HSM_RsaSsaPssVerifyType;

/**
 * @brief RSA PKCS1 V1.5 signature information used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType  eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */

    uint32_t            u32EmByteCnt; /**< set it 0 to use default value. RFC8017 require set it to N'byte count, equal to u32KeyNByteCount. the em data byte count, itx8 MUST < N's bit count, should keep same with the signature generate configuration */

    HSM_HashAlgType     eHashType; /**< the hash type used by signature */

    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data */

    const uint8_t      *pPrivateKey; /**< private key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PrivateKeyByteCnt; /**< the byte count of key E */

    HSM_BoolType        bUseInputDer; /**< set to HSM_TRUE when RFC8017 not support some hash algorithm, for example SM3 Hash type, DER encoding of the DigestInfo value, if use hsm internal data, just set it to HSM_FALSE */
    const uint8_t      *pDer; /**< when bUseInputDer is HSM_TRUE, this field point to the DER encoding of the DigestInfo value, others, ignore */
    uint32_t            u32DerByteCount; /**< when bUseInputDer is HSM_TRUE, this field represent the byte count of DER data,  if bUseInputDer is HSM_FALSE, ignore this field */

    const uint8_t      *pKeyN; /**< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< key N's data byte count */


    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    uint32_t           *pResultByteCnt; /**< the result data byte count */
} HSM_RsaSsaPkcs1V15SignType;

/**
 * @brief RSA PKCS1 V1.5 signature verify information used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType  eInputFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    uint32_t            u32EmByteCnt; /**< set it 0 to use default value. RFC8017 require set it to N'byte count, equal to u32KeyNByteCount. the em data byte count, itx8 MUST < N's bit count, should keep same with the signature generate configuration */

    HSM_HashAlgType     eHashType; /**< the hash type used by signature */

    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data */

    const uint8_t      *pSignData; /**< input signature data */
    uint32_t            u32SignDataByteCount; /**< the byte count of signature data, it must > 0 */

    const uint8_t      *pPublicKey; /**< public key, input key E data for "A = (input data)^E mod N" */
    uint32_t            u32PublicKeyByteCnt; /**< the byte count of key E */

    HSM_BoolType        bUseInputDer; /**< set to HSM_TRUE when RFC8017 not support some hash algorithm, for example SM3 Hash type, DER encoding of the DigestInfo value, if use hsm internal data, just set it to HSM_FALSE */
    const uint8_t      *pDer; /**< when bUseInputDer is HSM_TRUE, this field point to the DER encoding of the DigestInfo value, others, ignore */
    uint32_t            u32DerByteCount; /**< when bUseInputDer is HSM_TRUE, this field represent the byte count of DER data,  if bUseInputDer is HSM_FALSE, ignore this field */

    const uint8_t      *pKeyN; /**< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< key N's data byte count */
} HSM_RsaSsaPkcs1V15VerifyType;

/**
 * @brief RSA PKCS1 V1.5 encrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_BoolType        bUsePseudoRand;  /**< whether use pseudo number to speed up the encrypt process */

    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data */
    HSM_DataFormatType  eInputDataFmt;

    const uint8_t      *pKeyE; /**< private key, input key E data for "result = (input data)^E mod N" */
    uint32_t            u32KeyEByteCount; /**< the byte count of key E */
    HSM_DataFormatType  eKeyEFmt; /**< input public key E organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyN; /**< input key N data for "result = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< key N's data byte count */
    HSM_DataFormatType  eKeyNFmt; /**< input public key E organized format, uint8_t array, or uint32_t array */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /**< the result data byte count */
} HSM_RsaEsPkcs1V15EncryptType;

/**
 * @brief RSA PKCS1 V1.5 decrypt information used by driver when call specific API
 *
 */
typedef struct {
    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data */
    HSM_DataFormatType  eInputDataFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyD; /**< private key, input key D data for "result = (input data)^D mod N" */
    uint32_t            u32KeyDByteCnt; /**< the byte count of key D */
    HSM_DataFormatType  eKeyDFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyN; /**< input key N data for "result = (input data)^D mod N" */
    uint32_t            u32KeyNByteCount; /**< key N's data byte count */
    HSM_DataFormatType  eKeyNFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /**< the result data byte count */
} HSM_RsaEsPkcs1V15DecryptType;

/**
 * @brief RSA OAEP encrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_BoolType        bUsePseudoRand; /**< whether use pseudo number to speed up the encrypt process */

    HSM_HashAlgType     eHashType; /**< the hash type used to encrypt */
    HSM_HashAlgType     eMgfHashType; /**< the hash type used to mgf, suggest use the same value with eHashType, refer to RFC8017 specification */

    const uint8_t      *pLabel; /**< input data */
    uint32_t            u32LabelByteCount; /**< the byte count of input data */
    HSM_DataFormatType  eLabelFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data */
    HSM_DataFormatType  eInputDataFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyE; /**< public key, input key E data for "result = (input data)^E mod N" */
    uint32_t            u32KeyEByteCount; /**< the byte count of key E */
    HSM_DataFormatType  eKeyEFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyN; /**< input key N data for "result = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< key N's data byte count */
    HSM_DataFormatType  eKeyNFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /**< the result data byte count */
} HSM_RsaEsOaepEncryptType;

/**
 * @brief RSA OAEP decrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_HashAlgType     eHashType; /**< the hash type used to encrypt */
    HSM_HashAlgType     eMgfHashType; /**< the hash type used to mgf, suggest use the same value with eHashType, refer to RFC8017 specification */

    const uint8_t      *pLabel; /**< input data */
    uint32_t            u32LabelByteCount; /**< the byte count of input data */
    HSM_DataFormatType  eLabelFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pInputData; /**< input data */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data */
    HSM_DataFormatType  eInputDataFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyE; /**< private key, input key E data for "result = (input data)^E mod N" */
    uint32_t            u32KeyEByteCount; /**< the byte count of key E */
    HSM_DataFormatType  eKeyEFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyN; /**< input key N data for "result = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< key N's data byte count */
    HSM_DataFormatType  eKeyNFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /**< the result data byte count */
} HSM_RsaEsOaepDecryptType;

/**
 * @brief big number (A^E % N) information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t            u32HwCtrlFlag; /* if you don't know how to set it, try set it 0. bit[0]:input data normal(0)/montgomery, bit[1]:output data normal(0)/montgomery, bit[2]:data is integer(0)/binary, bit[3]:timing not equal(0)/equal */
    const uint8_t      *pInputData; /**< input data A */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data A */
    HSM_DataFormatType  eInputDataFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyE; /**< input key E data for "result = (input data)^E mod N" */
    uint32_t            u32KeyEByteCount; /**< the byte count of key E */
    HSM_DataFormatType  eKeyEFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    const uint8_t      *pKeyN; /**< input key N data for "result = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< hw will get the actual key data bit count according to the non-zero bit count, it means key not generate by multiply 2 */
    HSM_DataFormatType  eKeyNFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /* point to the variable to store the output result length */
} HSM_BnCalcModExpType;

/**
 * @brief two big number calculation information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t            u32HwCtrlFlag; /* if you don't know how to set it, try set it 0. bit[0]:input data normal(0)/montgomery, bit[1]:output data normal(0)/montgomery, bit[2]:data is integer(0)/binary, bit[3]:timing not equal(0)/equal */

    HSM_DataFormatType  eInputDataFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    const uint8_t      *pInputData; /**< input data A */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data A */

    HSM_DataFormatType  eInputData2Fmt; /**< input data organized format, uint8_t array, or uint32_t array */
    const uint8_t      *pInputData2; /**< input data A */
    uint32_t            u32InputData2ByteCount; /**< the byte count of input data A */

    HSM_DataFormatType  eKeyNFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    const uint8_t      *pKeyN; /**< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< hw will get the actual key data bit count according to the non-zero bit count, it means key not generate by multiply 2 */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /* point to the variable to store the output result length */
} HSM_BnCalcABType;

/**
 * @brief one big number calculation information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t            u32HwCtrlFlag; /* if you don't know how to set it, try set it 0. bit[0]:input data normal(0)/montgomery, bit[1]:output data normal(0)/montgomery, bit[2]:data is integer(0)/binary, bit[3]:timing not equal(0)/equal */

    HSM_DataFormatType  eInputDataFmt; /**< input data organized format, uint8_t array, or uint32_t array */
    const uint8_t      *pInputData; /**< input data A */
    uint32_t            u32InputDataByteCount; /**< the byte count of input data A */


    const uint8_t      *pKeyN; /**< input key N data for "A = (input data)^E mod N" */
    uint32_t            u32KeyNByteCount; /**< hw will get the actual key data bit count according to the non-zero bit count, it means key not generate by multiply 2 */
    HSM_DataFormatType  eKeyNFmt; /**< input data organized format, uint8_t array, or uint32_t array */

    uint8_t            *pResult; /**< output buffer, the buffer size should >= "u32KeyNByteCount" */
    uint32_t            u32ResultBufByteCnt; /**< the result buffer size */
    HSM_DataFormatType  eOutputFmt; /**< output data organized format, uint8_t array, or uint32_t array */
    uint32_t           *pResultByteCnt; /* point to the variable to store the output result length */
} HSM_BnCalcAType;





/**
 * @brief base64 encode information used by driver when call specific API
 *
 * @note BASE64 encode is implemented by driver software, HSM hardware not support it.
 */
typedef struct {
    const uint8_t *pInput; /**< input data */
    uint32_t       u32InputByteCnt; /**< byte count of input data */
    char          *pOut; /**< result buffer */
    uint32_t       u32OutBufByteCnt; /**< to tell driver the result buffer size */
    uint32_t       u32OutByteCnt; /**< driver set this variable to tell user the acutal result size */
} HSM_Base64EncodeType;

/**
 * @brief base64 decode information used by driver when call specific API
 *
 * @note BASE64 decode is implemented by driver software, HSM hardware not support it.
 */
typedef struct {
    const char     *pInput; /**< input data */
    uint32_t        u32InputByteCnt; /**< byte count of input data */
    uint8_t        *pOut; /**< result buffer */
    uint32_t        u32OutBufByteCnt;  /**< to tell the result buffer size */
    uint32_t        u32OutByteCnt; /**< driver set this variable to tell user the acutal result size */
} HSM_Base64DecodeType;


/**
 * @brief SM4 encrypt/decrypt information used by driver when call specific API
 *
 */
typedef struct {
    HSM_Sm4KeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    const uint8_t              *pKeyAddr; /**< 16bytes array, start address should align with 4bytes,  when eUseKeyType is HSM_SM4_KEY_NEW, this MUST configure */
    HSM_Sm4EnDecryptAlgType     eSm4Alg; /**< SM4 encrypt/decrypt mode */

    const uint8_t              *pDataInput;      /**< start address should align with 4bytes */
    uint32_t                    u32InputByteCnt; /**< 128bit(16Bytes) align */
    uint8_t                    *pDataOutput; /**< start address should align with 4bytes */
    uint32_t                    u32OutputMemSize; /**< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */

    const uint8_t              *pIvData; /**< 16bytes array, start address should align with 4bytes, 128bit(16Bytes) iv(initialization vector) data array, ECB not need configure this */
} HSM_Sm4EnDecryptType;

/**
 * @brief SM4 decrypt information used by driver when call specific API
 *
 */
typedef HSM_Sm4EnDecryptType HSM_Sm4DecryptType;

/**
 * @brief SM4 encrypt information used by driver when call specific API
 *
 */
typedef HSM_Sm4EnDecryptType HSM_Sm4EncryptType;

/**
 * @brief SM2 encrypt information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t u32SM2InputByteCnt;    /**< the length should be <= 32bytes */
    uint32_t *pSM2OutputByteCnt;    /**< driver internal will set output byte count in the memory this pointer point to */
    const uint8_t  *pInputData;         /**< start address should 4bytes align, length should be more than u32SM2InputByteCnt, and must be 4bytes align */
    const uint8_t  *pPublicKey_x;       /**< 32bytes array, start address should align with 4bytes, public key axis x data */
    const uint8_t  *pPublicKey_y;       /**< 32bytes array, start address should align with 4bytes, public key axis y data */
    uint8_t  *pOutputData;        /**< start address should 4bytes align, length should be more than u32SM2InputByteCnt+97, and must be 4bytes align */
} HSM_Sm2EncryptType;

/**
 * @brief SM2 decrypt information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t u32SM2InputByteCnt;    /**< the length should be <= 129bytes */
    uint32_t *pSM2OutputByteCnt;    /**< driver internal will set output byte count in the memory this pointer point to */
    const uint8_t  *pInputData;           /**< start address should 4bytes align, length should be more than u32SM2InputByteCnt, and must be 4bytes align */
    const uint8_t  *pPrivateKey;          /**< 32bytes array, start address should align with 4bytes, private key */
    uint8_t  *pOutputData;          /**< start address should 4bytes align, length should be more than u32SM2InputByteCnt-97, and must be 4bytes align */
}HSM_Sm2DecryptType;

/**
 * @brief SM2 sign information used by driver when call specific API
 *
 */
typedef struct {
    HSM_BoolType bUseDefaultID;     /**< TRUE means use default ID. FALSE means use specific ID with "pInputData_ID" and "u32SM2InputIDByteCnt" params. */
    HSM_BoolType bHashInput;        /**< TRUE means process hash message. FALSE means process raw M message */
    uint32_t u32SM2InputMByteCnt;   /**< the length should be <= 32bytes */
    uint32_t u32SM2InputIDByteCnt;  /**< the length should be <= 32bytes note: If "bUseDefaultID" is FALSE, would use this specific ID length with byte unit. */
    const uint8_t *pInputData_ID;        /**< note: If "bUseDefaultID" is FALSE, would use this specific ID. length should be more than u32SM2InputIDByteCnt, and must be 4bytes align */
    const uint8_t *pInputData_MOrHash;   /**< length should be more than u32SM2InputMOrHashByteCnt, and must be 4bytes align */
    const uint8_t *pPrivateKey;     /**< 32bytes array, start address should align with 4bytes, private key */
    const uint8_t *pPublicKey_X;    /**< 32bytes array, start address should align with 4bytes, If bHashInput is false, the pointer must be not NULL */
    const uint8_t *pPublicKey_Y;    /**< 32bytes array, start address should align with 4bytes, If bHashInput is false, the pointer must be not NULL */
    uint8_t *pOutputData_R;   /**< 32bytes array, start address should align with 4bytes, sign result R */
    uint8_t *pOutputData_S;   /**< 32bytes array, start address should align with 4bytes, sign result S */
}HSM_Sm2SignType;

/**
 * @brief SM2 verify information used by driver when call specific API
 *
 */
typedef struct {
    HSM_BoolType bUseDefaultID;     /**< TRUE means use default ID. FALSE means use specific ID with "pInputData_ID" and "u32SM2InputIDByteCnt" params. */
    HSM_BoolType bHashInput;        /**< TRUE means process hash message. FALSE means process raw M message */
    uint32_t u32SM2InputMByteCnt;   /**< the length should be <= 32bytes */
    uint32_t u32SM2InputIDByteCnt;  /**< the length should be <= 32bytes note: If "bUseDefaultID" is FALSE, would use this specific ID length with byte unit. */
    const uint8_t *pInputData_MOrHash;   /**< length should be more than u32SM2InputMOrHashByteCnt, and must be 4bytes align */
    const uint8_t *pInputData_ID;        /**< note: If "bUseDefaultID" is FALSE, would use this specific ID. length should be more than u32SM2InputIDByteCnt, and must be 4bytes align */
    const uint8_t *pInputData_R;    /**< 32bytes array, start address should align with 4bytes, the sign result R */
    const uint8_t *pInputData_S;    /**< 32bytes array, start address should align with 4bytes, the sign result S */
    const uint8_t *pPublicKey_X;    /**< 32bytes array, start address should align with 4bytes, the public key X */
    const uint8_t *pPublicKey_Y;    /**< 32bytes array, start address should align with 4bytes, the public key Y */
}HSM_Sm2VerifyType;

/**
 * @brief SM2 key pair generation information used by driver when call specific API
 *
 */
typedef struct {
    uint8_t  *pPrivateKey;  /**< 32bytes array, start address should align with 4bytes, private key */
    uint8_t  *pPublicKey_X; /**< 32bytes array, start address should align with 4bytes, the public key X */
    uint8_t  *pPublicKey_Y; /**< 32bytes array, start address should align with 4bytes, the public key Y */
}HSM_Sm2GenKeyPairType;

/**
 * @brief SM2 ZA generation information used by driver when call specific API
 *
 */
typedef struct {
    HSM_BoolType bUseDefaultID; /**< TRUE means use default ID. FALSE means use specific ID with "pInputData_ID" and "u32SM2InputIDByteCnt" params. */
    uint32_t  u32SM2InputIDByteCnt;/**< the length should be <= 32bytes  note: If "bUseDefaultID" is FALSE, would use this specific ID length with byte unit.*/
    const uint8_t *pPublicKey_X; /**< 32bytes array, start address should align with 4bytes, public key X */
    const uint8_t *pPublicKey_Y; /**< 32bytes array, start address should align with 4bytes, public key Y */
    const uint8_t *pInputData_ID; /**< note: If "bUseDefaultID" is FALSE, would use this specific ID. length should be more than u32SM2InputIDByteCnt, and must be 4bytes align */
    uint8_t  *pOutputData_Za; /**< 32bytes array, start address should align with 4bytes, Length is 32bytes, SM3 always output 256bit */
}HSM_Sm2GenZaType;

/**
 * @brief SM2 HASH generation information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t u32InputDataByteCnt;       /**< input data byte count */
    const uint8_t *pInputData_ZaAndM;        /**< note: it should be ZA||M, the length should be more than u32InputDataByteCnt, and must be 4bytes align */
    uint8_t  *pOutputData_Hash;    /**< 32bytes array, start address should align with 4bytes, Length is 32bytes, SM3 always output 256bit */
}HSM_Sm2GenHashType;

/**
 * @brief ECC curve information used by driver when call specific API
 *
 */
typedef struct {
    const uint8_t       *pP;     /**< start address should 4bytes align, ecc curve modulus */
    const uint8_t       *pN;     /**< start address should 4bytes align, ecc curve order; size; the count of all possible EC points */
    const uint8_t       *pA;     /**< start address should 4bytes align, the constant "a" in y^2 = x^3 + a*x + b (mod p) */
    const uint8_t       *pB;     /**< start address should 4bytes align, the constant "b" in y^2 = x^3 + a*x + b (mod p) */
    const uint8_t       *pGx;    /**< start address should 4bytes align, x of the curve generator point G {x, y} */
    const uint8_t       *pGy;    /**< start address should 4bytes align, y of the curve generator point G {x, y} */
    HSM_DataFormatType  eDataFormat; /**< the curve parameters data format  */
    uint32_t            u32ByteCount;   /**< all the data size, it should contains all pN data */
} HSM_DrvEccCurveParamType;

/**
 * @brief ECC verify information used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType          eInputFmt;      /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DrvEccCurveParamType    tCurve;         /**< ecc curve parameters */
    const uint8_t              *pkGx;           /**< public key axis x */
    uint32_t                    u32pKGxByteCnt; /**< byte count of public key axis x data */
    const uint8_t              *pkGy;           /**< public key axis y */
    uint32_t                    u32pKGyByteCnt; /**< byte count of public key axis y data */
    const uint8_t              *pHashData;      /**< hash of the data to verify */
    uint32_t                    u32HashByteCnt; /**< byte count of hash data */
    const uint8_t              *pR;             /**< the sign result R of the data to verify */
    uint32_t                    u32RByteCnt;    /**< byte count of signature R */
    const uint8_t              *pS;             /**< the sign result S of the data to verify */
    uint32_t                    u32SByteCnt;    /**< byte count of signature S */
} HSM_EccVerifyType;

/**
 * @brief ECC sign information used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType          eInputFmt;              /**< input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType          eOutputFmt;             /**< output result data format  */
    HSM_DrvEccCurveParamType    tCurve;                 /**< ecc curve parameters */

    const uint8_t              *pPrivateKey;            /**< private key  */
    uint32_t                    u32PrivateKeyByteCnt;   /**< the private key size, should < curve parameter N size */
    const uint8_t              *pHashData;              /**< hash of the data to sign  */
    uint32_t                    u32HashByteCnt;         /**< the hash value size, should < curve parameter N size */

    uint32_t                    u32ResultBufferSize;    /* the size of buffer pR/pS point to */
    /* the following the sign output */
    uint8_t                    *pR;                     /**< buffer size MUST >= tCurve.u32ByteCount, driver internal use this buffer to store the sign result R of the data to sign */
    uint8_t                    *pS;                     /**< buffer size MUST >= tCurve.u32ByteCount, driver internal use this buffer to store the sign result S of the data to sign */
    uint32_t                   *pRSResultByteCnt;       /**< point to the variable to store the signature result R/S byte count */
} HSM_EccSignType;

/**
 * @brief ECC key pair generation information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t  u32ByteCount;             /**< all the data size, it should contains all N data */

    HSM_DrvEccCurveParamType tCurve;    /**< ecc curve parameters */

    /* the following the generation output */
    uint8_t *pPrivateKey;  /**< start address should 4bytes align, driver use this buffer to store private key result  */
    uint8_t *pPublicKey_X; /**< start address should 4bytes align, driver use this buffer to store public key axis x result */
    uint8_t *pPublicKey_Y; /**< start address should 4bytes align, driver use this buffer to store public key axis y result */
} HSM_EccKeyPairGenType;

/**
 * @brief ECC derive public key from private key information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t  u32ByteCount;                 /**< all the data size, it should contains all N data */

    HSM_DrvEccCurveParamType tCurve;        /**< ecc curve parameters */
    const uint8_t           *pPrivateKey;               /**< start address should 4bytes align, private key  */
    uint32_t        u32PrivateKeyByteCount; /**< the byte count of private key data  */
    /* the following the generation output */
    uint8_t                 *pPublicKey_X;              /**< start address should 4bytes align, driver use this buffer to store public key axis x */
    uint8_t                 *pPublicKey_Y;              /**< start address should 4bytes align, driver use this buffer to store public key axis y */
} HSM_EccPubKeyGenType;

#define HSM_ECC_CALC_HW_FLAG_COORD_AFFINE       0x00u
#define HSM_ECC_CALC_HW_FLAG_COORD_XONLY        0x01u

#define HSM_ECC_CALC_HW_FLAG_R2MODN_DISABLE     0x00u
#define HSM_ECC_CALC_HW_FLAG_R2MODN_ENABLE      0x02u

#define HSM_ECC_CALC_HW_FLAG_DATA_INTEGER       0x00u
#define HSM_ECC_CALC_HW_FLAG_DATA_BINARY        0x04u

#define HSM_ECC_CALC_HW_FLAG_TIMING_UNEQUAL     0x00u
#define HSM_ECC_CALC_HW_FLAG_TIMING_EQUAL       0x08u

#define HSM_ECC_CALC_HW_FLAG_CURVE_STANDARD     0x00u
#define HSM_ECC_CALC_HW_FLAG_CURVE_MONTGOMERY   0x10u
#define HSM_ECC_CALC_HW_FLAG_CURVE_EDWARDS      0x20u

/**
 * @brief ECC point add
 *
 */
typedef struct {
    uint32_t                    u32HwCtrlFlag; /**< if you don't know how to set this, just set this to 0; bit[0]coord affine or xonly(1), bit[1] r2modn enable, bit[2]integer(0) or binary, bit [3] timing unequ(0) or equal, bit[5:4] curve type(0:standard, 1:montgomery, 2:edwards */

    HSM_DataFormatType          eInputFmt;
    HSM_DrvEccCurveParamType    tCurve;

    uint8_t                    *pP1x;
    uint32_t                    u32P1xByteCnt;
    uint8_t                    *pP1y;
    uint32_t                    u32P1yByteCnt;

    const uint8_t              *pP2x;            /**< when calculate 'k x G', this should configure  */
    uint32_t                    u32P2xByteCnt; /**< the byte count of k data  */
    const uint8_t              *pP2y;            /**< when calculate 'k x G', this should configure  */
    uint32_t                    u32P2yByteCnt; /**< the byte count of k data  */

    HSM_DataFormatType          eOutputFmt;
    uint8_t                    *pResultX;                 /**< buffer to store the result x */
    uint32_t                    u32ResultXBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultXByteCnt;
    uint8_t                    *pResultY;                 /**< buffer to store the result y */
    uint32_t                    u32ResultYBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultYByteCnt;
} HSM_EccPointAddType;

/**
 * @brief ECC point x 2
 *
 */
typedef struct {
    uint32_t                    u32HwCtrlFlag; /**< if you don't know how to set this, just set this to 0; bit[0]coord affine or xonly(1), bit[1] r2modn enable, bit[2]integer(0) or binary, bit [3] timing unequ(0) or equal, bit[5:4] curve type(0:standard, 1:montgomery, 2:edwards */

    HSM_DataFormatType          eInputFmt;
    HSM_DrvEccCurveParamType    tCurve;

    uint8_t                    *pP1x;
    uint32_t                    u32P1xByteCnt;
    uint8_t                    *pP1y;
    uint32_t                    u32P1yByteCnt;

    HSM_DataFormatType          eOutputFmt;
    uint8_t                    *pResultX;                 /**< buffer to store the result x */
    uint32_t                    u32ResultXBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultXByteCnt;
    uint8_t                    *pResultY;                 /**< buffer to store the result y */
    uint32_t                    u32ResultYBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultYByteCnt;
} HSM_EccPointX2Type;

/**
 * @brief ECC point x N
 *
 */
typedef struct {
    uint32_t                    u32HwCtrlFlag; /**< if you don't know how to set this, just set this to 0; bit[0]coord affine or xonly(1), bit[1] r2modn enable, bit[2]integer(0) or binary, bit [3] timing unequ(0) or equal, bit[5:4] curve type(0:standard, 1:montgomery, 2:edwards */

    HSM_DrvEccCurveParamType    tCurve;

    HSM_DataFormatType          eP1Fmt;
    const uint8_t              *pP1x;
    uint32_t                    u32P1xByteCnt;
    const uint8_t              *pP1y;
    uint32_t                    u32P1yByteCnt;

    HSM_DataFormatType          eNFmt;
    const uint8_t              *pN;
    uint32_t                    u32NByteCnt;

    HSM_DataFormatType          eOutputFmt;
    uint8_t                    *pResultX;                 /**< buffer to store the result x */
    uint32_t                    u32ResultXBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultXByteCnt;
    uint8_t                    *pResultY;                 /**< buffer to store the result y */
    uint32_t                    u32ResultYBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultYByteCnt;
} HSM_EccPointXNType;

typedef struct {
    HSM_DataFormatType          eInputFmt;
    HSM_DrvEccCurveParamType    tCurve;

    const uint8_t              *pPx;
    uint32_t                    u32PxByteCnt;

    HSM_DataFormatType          eOutputFmt;
    uint8_t                    *pResultOddY;                 /**< buffer to store the result y */
    uint32_t                    u32ResultOddYBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultOddYByteCnt;
    uint8_t                    *pResultEvenY;                 /**< buffer to store the result x */
    uint32_t                    u32ResultEvenYBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pResultEvenYByteCnt;
} HSM_EccDeriveYFromXType;

/**
 * @brief ED25519 input data is raw data
 *
 */
#define HSM_ED25519_INPUT_RAW_DATA     0u

/**
 * @brief ED25519 input data is the hash value of private key
 *
 */
#define HSM_ED25519_INPUT_HASH_DATA    1u

/**
 * @brief type definition for ED25519 input data type
 * refer to HSM_ED25519_INPUT_RAW_DATA, HSM_ED25519_INPUT_HASH_DATA
 */
typedef uint32_t HSM_Ed25519InputType;

typedef struct {
#if 0
    const uint8_t      *pP;
    const uint8_t      *pL;
    const uint8_t      *pA;              /* curve formula parameter a */
    const uint8_t      *pD;              /* curve formula parameter d */
    const uint8_t      *pBx;
    const uint8_t      *pBy;
    HSM_DataFormatType  eCurveDataFmt;
    uint32_t            u32ByteCnt;
#endif

    HSM_DrvEccCurveParamType tCurveParm;

    uint32_t            u32B;
    uint32_t            u32C;
    uint32_t            u32N;

    HSM_HashAlgType     eHashAlg;
} HSM_Ed25519CurveType;

typedef struct {
    HSM_BoolType                bUseExtCurve;
    const HSM_Ed25519CurveType *ptExtCurve;

    HSM_Ed25519InputType        eInputType;

    const uint8_t              *pInputData;
    uint32_t                    u32InputDataByteCnt;
    HSM_DataFormatType          eInputFmt;



    HSM_DataFormatType          eOutputFmt;
    uint8_t                    *pResultX;                 /**< buffer to store the result x axis */
    uint32_t                    u32ResultXBufByteCnt;     /**< input result x buffer size */
    uint32_t                   *pResultXByteCnt;          /**< point to the variable which to store the X axis data byte count */

    uint8_t                    *pResultY;                 /**< buffer to store the result x axis */
    uint32_t                    u32ResultYBufByteCnt;     /**< input result x buffer size */
    uint32_t                   *pResultYByteCnt;          /**< point to the variable which to store the X axis data byte count */

    uint8_t                    *pPublicKey;                 /**< buffer to store the public key encoded according to the rfc8032 */
    uint32_t                    u32PublicKeyBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pPublicKeyByteCnt;
} HSM_Ed25519PubKeyGenType;

typedef struct {
    HSM_BoolType                bUseExtCurve;
    const HSM_Ed25519CurveType *ptExtCurve;

    HSM_Ed25519InputType        ePrivateKeyOrHashType;
    const uint8_t              *pPrivateKeyOrHash;
    uint32_t                    u32PrivateKeyOrHashByteCnt;
    HSM_DataFormatType          ePrivateKeyOrHashFmt;

    HSM_Ed25519InputType        eMessageOrHashType;
    const uint8_t              *pMessageOrHash;
    uint32_t                    u32MessageOrHashByteCnt;
    HSM_DataFormatType          eMessageOrHashFmt;

    const uint8_t              *pHashRAM;
    uint32_t                    u32HashRAMByteCnt;
    HSM_DataFormatType          eHashRAMFmt;

    HSM_DataFormatType          eOutputFmt;

    uint8_t                    *pRx;                 /**< buffer to store the result y */
    uint32_t                    u32RxBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pRxByteCnt;

    uint8_t                    *pR;                 /**< buffer to store the result y */
    uint32_t                    u32RBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pRByteCnt;

    uint8_t                    *pS;                 /**< buffer to store the result x */
    uint32_t                    u32SBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pSByteCnt;
} HSM_Ed25519SignType;

typedef struct {
    HSM_BoolType                bUseExtCurve;
    const HSM_Ed25519CurveType *ptExtCurve;

    const uint8_t              *pPublicKey;
    uint32_t                    u32PublicKeyByteCnt;
    HSM_DataFormatType          ePublicKeyFmt;


    HSM_Ed25519InputType        eMessageOrHashType;
    const uint8_t              *pMessageOrHash;
    uint32_t                    u32MessageOrHashByteCnt;
    HSM_DataFormatType          eMessageOrHashFmt;


    const uint8_t              *pR;                 /**< buffer to store the result y */
    uint32_t                    u32RByteCnt;           /**< input result x buffer size, output result x size actually */
    HSM_DataFormatType          eRFmt;

    const uint8_t              *pS;                 /**< buffer to store the result y */
    uint32_t                    u32SByteCnt;           /**< input result x buffer size, output result x size actually */
    HSM_DataFormatType          eSFmt;
} HSM_Ed25519VerifyType;

typedef struct {
    HSM_BoolType                bUseExtCurve;
    const HSM_Ed25519CurveType *ptExtCurve;

    const uint8_t              *pY;
    uint32_t                    u32YByteCnt;
    HSM_DataFormatType          eYFmt;


    HSM_DataFormatType          eOutputFmt;

    uint8_t                    *pOddX;                 /**< buffer to store the result y */
    uint32_t                    u32OddXBufByteCnt;           /**< input result x buffer size, output result x size actually */
    uint32_t                   *pOddXByteCnt;

    uint8_t                    *pEvenX;
    uint32_t                    u32EvenXBufByteCnt;
    uint32_t                   *pEvenXByteCnt;

} HSM_Ed25519Y2XType;

/**
 * @brief ECC point check whether valid
 *
 */
typedef struct {
    uint32_t                    u32HwCtrlFlag; /**< if you don't know how to set this, just set this to 0; bit[0]coord affine or xonly(1), bit[1] r2modn enable, bit[2]integer(0) or binary, bit [3] timing unequ(0) or equal, bit[5:4] curve type(0:standard, 1:montgomery, 2:edwards */

    HSM_DataFormatType          eInputFmt;
    HSM_DrvEccCurveParamType    tCurve;

    uint8_t                    *pP1x;
    uint32_t                    u32P1xByteCnt;
    uint8_t                    *pP1y;
    uint32_t                    u32P1yByteCnt;
} HSM_EccPointCheckType;

/**
 * @brief ECC encrypt information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t       u32ByteCount;            /**< all the data size, it should contains all N data */

    const uint8_t *pCoeffi_A;               /**< start address should 4bytes align, the constant "a" in y^2 = x^3 + a*x + b (mod p), all data 8 bytes aligned */
    const uint8_t *pCoeffi_B;               /**< start address should 4bytes align, the constant "b" in y^2 = x^3 + a*x + b (mod p) */
    const uint8_t *pP;                      /**< start address should 4bytes align, ecc curve modulus */
    const uint8_t *pN;                      /**< start address should 4bytes align, ecc curve order; size; the count of all possible EC points */
    const uint8_t *pOtherSidePublicKey_x;   /**< start address should 4bytes align, decrypt side's public key axis x data */
    const uint8_t *pOtherSidePublicKey_y;   /**< start address should 4bytes align, decrypt side's public key axis y data */
    const uint8_t *pPrivateKey;             /**< start address should 4bytes align, encrypt side private key */
    const uint8_t *pPlainData;              /**< start address should 4bytes align, data to be encrypted, its byte count should be same as u32ByteCount */

    uint8_t       *pEncryedData;            /**< start address should 4bytes align, driver internal write the result to this buffer */
} HSM_EccEasyEncryType;

/**
 * @brief ECC decrypt information used by driver when call specific API
 *
 */
typedef struct {
    uint32_t  u32ByteCount; /**< all the data size, it should contains all N data */

    const uint8_t  *pCoeffi_A;              /**< start address should 4bytes align, the constant "a" in y^2 = x^3 + a*x + b (mod p), all data 8 bytes aligned */
    const uint8_t  *pCoeffi_B;              /**< start address should 4bytes align, the constant "b" in y^2 = x^3 + a*x + b (mod p) */
    const uint8_t  *pP;                     /**< start address should 4bytes align, ecc curve modulus */
    const uint8_t  *pN;                     /**< start address should 4bytes align, ecc curve order; size; the count of all possible EC points */
    const uint8_t  *pOtherSidePublicKey_x;  /**< start address should 4bytes align, encrypt side's public key axis x data */
    const uint8_t  *pOtherSidePublicKey_y;  /**< start address should 4bytes align, encrypt side's public key axis y data */
    const uint8_t  *pPrivateKey;            /**< start address should 4bytes align, decrypt side private key */
    const uint8_t  *pEncryedData;           /**< start address should 4bytes align, data to be decrypted, its byte count should be same as u32ByteCount */

    uint8_t        *pPlainData;             /**< start address should 4bytes align, driver internal write the result to this buffer */
} HSM_EccEasyDecryType;


/**
 * @brief Flexiable AES zero padding type for type "HSM_FlexAesPadType"
 * if input data is not aligned with 16bytes, this configuration will make append byte data 0 to keep 16bytes align.
 */
#define HSM_FLEXAES_PAD_ZERO  0u

/**
 * @brief Flexiable AES PKCS7 padding type for type "HSM_FlexAesPadType"
 * if input data is not aligned with 16bytes, this configuration will make append bytes by PKCS7 method to keep 16bytes align.
 */
#define HSM_FLEXAES_PAD_PKCS7 1u

/**
 * @brief Flexiable AES padding type definition
 * if use zero padding, refer to HSM_FLEXAES_PAD_ZERO, after decrypt, user should remove the zero manually
 * if use PKCS7 padding, refer to HSM_FLEXAES_PAD_PKCS7
 */
typedef uint32_t HSM_FlexAesPadType;



/**
 * @brief flexiable AES information used by driver when call specific API
 * AES encrypt/decrypt API, the parameter has limit. The data address has no limit, and the data size has no limit.
 * @note If you want to run fast, suggest the address 4bytes aligned, and the data size 16bytes aligned.
 */
typedef struct {
    HSM_AesKeyType              eUseKeyType; /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf; /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf; /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR/HSM_AES_KEY_DERIVED, this MUST configure */
    HSM_AesEnDecryptAlgType     eAesAlg; /**< encrypt/decrypt mode */

    const uint8_t               *pDataInput;      /**< the input data buffer address */
    uint32_t                    u32InputByteCnt; /**< the input data byte count, when decrypt, it should present the size of all the encrypted text */
    HSM_FlexAesPadType          ePad;  /**< for encrypt, if data size not 16bytes aligned, the pad byte should refer to this configuration,
                                            for decrypt, driver to process the padding data according to this,
                                            however, if zero padding, driver will not remove the padding 0, user should delete the data manually  */
    HSM_DataFormatType          eInputFmt; /**< key/iv/input data organized format, uint8_t array, or uint32_t array */
    HSM_DataFormatType          eOutputFmt; /**< output result data format  */
    uint8_t                     *pDataOutput; /**< the output buffer to store the result */
    uint32_t                    u32OutputMemSize; /**< the output data buffer "pDataOutput" size, should >= "u32InputByteCnt" */
    uint32_t                    *pGenerateOutByteCnt; /**< point to the uint32_t variable to store the result byte count, can be NULL */
    const uint8_t               *pIvData; /**< 128bit(16Bytes) iv(initialization vector) data array, ECB not need configure this */
} HSM_FlexAesEnDecryptType;



/**
 * @brief PBKDF2 information used by driver when call specific API
 *
 */
typedef struct {
    HSM_HashAlgType eHashAlg;
    uint32_t        u32Counter;
    uint32_t        u32dkLen;
	uint32_t        u32PasswordByteLength;
    const uint8_t  *pPassword;
    uint32_t        u32SaltByteLength;
    const uint8_t  *pSalt;
    uint8_t        *pKdfOutput;
} HSM_PBKDF2Type;

/**
 * @brief scatter CMAC/XMAC first block data information used by driver when call specific API
 *
 */
typedef struct {
    HSM_XCMAC_BackendType       eBackend;           /**< HSM_XCMAC_BACKEND_AES:aes+x/cmac or HSM_XCMAC_BACKEND_SM4:sm4+x/cmac */
    HSM_AesKeyType              eUseKeyType;        /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf;         /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;      /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR, this MUST configure */
    uint32_t                    u32GenMacByteCnt;   /**< XCMAC API generate MAC data, it's "u32GenMacByteCnt" size ICV data */
    HSM_BoolType                bCheckMacEn;        /**< if enable this check, user should place the data after the input data, hsm will check the generated data and it, if fail, hsm generate a interrupt, and if user get hw status, will get a error status */

    const uint8_t              *pDataInput;         /**< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /**< the input data byte count, no need 16bytes aligned */
} HSM_ScatterXCMacInitType;

/**
 * @brief scatter CMAC/XMAC the block after the first one(except the last one) information used by driver when call specific API
 *
 */
typedef struct {
    const uint32_t             *pDataInput;         /**< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /**< the input data byte count, no need 16bytes aligned */
} HSM_ScatterXCMacUpdateType;

/**
 * @brief scatter CMAC/XMAC the last one block data information used by driver when call specific API
 *
 */
typedef struct {
    const uint32_t             *pDataInput;         /**< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /**< the input data byte count, no need 16bytes aligned */
    uint32_t                   *pDataOutput;        /**< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /**< 4bytes align, the output data buffer "pDataOutput" size, should >= "u32GenMacByteCnt" */
} HSM_ScatterXCMacFinalType;

/**
 * @brief scatter CMAC/XMAC first block data information used by driver when call specific API
 *
 */
typedef struct {
    HSM_XCMAC_BackendType       eBackend;           /**< HSM_XCMAC_BACKEND_AES:aes+x/cmac or HSM_XCMAC_BACKEND_SM4:sm4+x/cmac */
    HSM_AesKeyType              eUseKeyType;        /**< the key source:vendor key programmed in nvr flash or new key in software */
    HSM_AesNewKeyInfType        tNewKeyInf;         /**< when eUseKeyType is HSM_AES_KEY_NEW, this MUST configure */
    HSM_AesVendorKeyInfType     tVendorKeyInf;      /**< when eUseKeyType is HSM_AES_KEY_CHIP_VENDOR_IFR/HSM_AES_KEY_DERIVED, this MUST configure */
    uint32_t                    u32GenMacByteCnt;   /**< XCMAC API generate MAC data, it's "u32GenMacByteCnt" size ICV data */
    HSM_BoolType                bCheckMacEn;        /**< if enable this check, user should place the data after the input data, hsm will check the generated data and it, if fail, hsm generate a interrupt, and if user get hw status, will get a error status */
    HSM_DataFormatType          eInputFmt;          /**< the input data format of init/update/finally api */

    const uint8_t              *pDataInput;         /**< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /**< the input data byte count, no need 16bytes aligned */
} HSM_FlexXCMacInitType;

/**
 * @brief scatter CMAC/XMAC the block after the first one(except the last one) information used by driver when call specific API
 *
 */
typedef struct {
    const uint8_t              *pInputData;         /**< address should align with 4bytes */
    uint32_t                    u32InputDataByteCnt;    /**< the input data byte count, no need 16bytes aligned */
} HSM_FlexXCMacUpdateType;

/**
 * @brief scatter CMAC/XMAC the last one block data information used by driver when call specific API
 *
 */
typedef struct {
    const uint8_t              *pDataInput;         /**< address should align with 4bytes */
    uint32_t                    u32InputByteCnt;    /**< the input data byte count, no need 16bytes aligned */

    HSM_DataFormatType          eOutputFmt;          /**< the output format of output MAC result */
    uint8_t                    *pDataOutput;        /**< address should align with 4bytes */
    uint32_t                    u32OutputMemSize;   /**< 4bytes align, the output data buffer "pDataOutput" size, should >= "u32GenMacByteCnt" */
} HSM_FlexXCMacFinalType;


/**
 * @brief extract public key information from certificate to be check used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType eFmt;                            /**< driver will set the data format of  data */
    uint8_t     *pPublicKeyAlgorithm;                   /**< a buffer pointer, if you don't understand, use a uint8_t[16], size at least 9bytes , refer to X.509 specification, cert.TBSCertificate.SubjectPublicKeyInfo.AlgorithmIdentifier.algorithm */
    uint32_t    u32PublicKeyAlgorithmByteCnt;           /**< the size of the buffer pPublicKeyAlgorithm point to, suggest use 16bytes array, driver will set it the actual data size */
    uint8_t     *pPublicKeyAlgorithmParameter;          /**< a buffer pointer, if you don't understand, use a uint8_t[16], size at least 8bytes , refer to X.509 specification, cert.TBSCertificate.SubjectPublicKeyInfo.AlgorithmIdentifier.parameters */
    uint32_t    u32PublicKeyAlgorithmParameterByteCnt;  /**< the size of the buffer pPublicKeyAlgorithmParameter point to, suggest use 16bytes array, driver will set it the actual data size */
    uint8_t     *pPublicKeyData;                        /**< a buffer pointer, if you don't understand, use a uint8_t[1036], for ECC public key, at least 1+(modulus'size x 2) for RSA public key, at least 11+Nsize+Esize bytes, Nsize is the N's size, Esize is E'size, refer to X.509 specification, cert.TBSCertificate.SubjectPublicKeyInfo.subjectPublicKey */
    uint32_t    u32PublicKeyDataByteCnt;                /**< the size of the buffer pPublicKeyData point to, suggest if ECC public key, use 264bytes(>1+128*2, 128 for max ECC1024) array; if RSA public key ,suggest use 1036bytes(>11+512+512, 512 for max RSA4096), driver will set it the actual data size */


    uint8_t     *pSignature;                            /**< a buffer pointer, if you don't understand, use a uint8_t[512], if the key is signed by RSA root key, at least root key modulus'size. if the key is signed by ECC root key, at least 11 + root key modulus's size x 2,  refer to X.509 specification, cert.signatureValue */
    uint32_t    u32SignatureByteCnt;                    /**< the size of the buffer pSignature point to, if root key is RSA key, suggest use 512bytes array, if root key is ECC key, suggest use 268bytes(>11+128x2), driver will set it the actual data size */
    uint8_t     *pSignatureAlgorithm;                   /**< a buffer pointer, if you don't understand, use a uint8_t[16], size at least 9bytes , refer to X.509 specification, cert.AlgorithmIdentifier.algorithm */
    uint32_t    u32SignatureAlgorithmByteCnt;           /**< the size of the buffer pSignatureAlgorithm point to, suggest use 16bytes array, driver will set it the actual data size */
    uint8_t     *pSignatureAlgorithmParameter;          /**< a buffer pointer, if you don't understand, use a uint8_t[64], size at least 9bytes , refer to X.509 specification, cert.AlgorithmIdentifier.algorithm */
    uint32_t    u32SignatureAlgorithmParameterByteCnt;  /**< the size of the buffer pSignatureAlgorithmParameter point to, suggest use 64bytes array, driver will set it the actual data size */
    uint8_t     *pToBeSigned;                           /**< a buffer pointer, if you don't understand, use a byte array ,if the string length of certificate is A, the byte array's size use (A / 3 * 4), refer to X.509 specification, cert.TBSCertificate */
    uint32_t    u32ToBeSignedByteCnt;                   /**< the size of the buffer pToBeSigned point to, driver will set it the actual data size */
} HSM_X509KeyToCheckInfType;

/**
 * @brief extract public key information from certificate used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType  eFmt;                                   /**< driver will set the data format of  data */
    uint8_t            *pPublicKeyAlgorithm;                    /**< a buffer pointer, if you don't understand, use a uint8_t[16], size at least 9bytes , refer to X.509 specification, cert.TBSCertificate.SubjectPublicKeyInfo.AlgorithmIdentifier.algorithm */
    uint32_t            u32PublicKeyAlgorithmByteCnt;           /**< the size of the buffer pPublicKeyAlgorithm point to, suggest use 16bytes array, driver will set it the actual data size */
    uint8_t            *pPublicKeyAlgorithmParameter;           /**< a buffer pointer, if you don't understand, use a uint8_t[16], size at least 8bytes , refer to X.509 specification, cert.TBSCertificate.SubjectPublicKeyInfo.AlgorithmIdentifier.parameters */
    uint32_t            u32PublicKeyAlgorithmParameterByteCnt;  /**< the size of the buffer pPublicKeyAlgorithmParameter point to, suggest use 16bytes array, driver will set it the actual data size */
    uint8_t            *pPublicKeyData;                         /**< a buffer pointer, if you don't understand, use a uint8_t[1036], for ECC public key, at least 1+(modulus'size x 2) for RSA public key, at least 11+Nsize+Esize bytes, Nsize is the N's size, Esize is E'size, refer to X.509 specification, cert.TBSCertificate.SubjectPublicKeyInfo.subjectPublicKey */
    uint32_t            u32PublicKeyDataByteCnt;                /**< the size of the buffer pPublicKeyData point to, suggest if ECC public key, use 264bytes(>1+128*2, 128 for max ECC1024) array; if RSA public key ,suggest use 1036bytes(>11+512+512, 512 for max RSA4096), driver will set it the actual data size */
} HSM_X509CertKeyInfType;

/**
 * @brief RSA public key information from certificate used by driver when call specific API
 *
 */
typedef struct {
    uint32_t      *pBitCnt;         /**< point to the variable to store the bit count of the N data */
    uint8_t       *pN;              /**< point to the buffer to store the N data */
    uint32_t       u32NBufByteCnt;  /**< user should set this to tell the driver the size of buffer the pN point to */
    uint32_t      *pNByteCnt;       /**< point to the variable to store the actual N data byte count */

    uint8_t       *pE;              /**< point to the buffer to store the E data */
    uint32_t       u32EBufByteCnt;  /**< user should set this to tell the driver the size of buffer the pN point to */
    uint32_t      *pEByteCnt;       /**< point to the variable to store the actual E data byte count */
} HSM_X509RsaPublicKeyType;

/**
 * @brief ECC public key information from certificate used by driver when call specific API
 *
 */
typedef struct {
    uint32_t      *pBitCnt;             /**< point to the variable to store the bit count of curve modulus P */

    uint8_t       *pkGx;                /**< point to the buffer to store the public key X data */
    uint32_t       u32kGxBufByteCnt;    /**< user should set this to tell the driver the size of buffer the pkGx point to */
    uint32_t      *pkGxByteCnt;         /**< point to the variable to store the public key X data byte count */

    uint8_t       *pkGy;                /**< point to the buffer to store the public key Y data */
    uint32_t       u32kGyBufByteCnt;    /**< user should set this to tell the driver the size of buffer the pkGy point to */
    uint32_t      *pkGyByteCnt;         /**< point to the variable to store the public key Y data byte count */

    HSM_DrvEccCurveParamType *pCurve;   /**< point to the variable to store the curve parameter */
} HSM_X509EccPublicKeyType;

/**
 * @brief public key type information from certificate used by driver when call specific API
 *
 */
typedef enum {
    HSM_X509_KEY_RSA_PUBLIC_KEY = 0, /**< the public key type is RSA  */
    HSM_X509_KEY_ECC_PUBLIC_KEY      /**< the public key type is ECC  */
} HSM_X509PubKeyKeyTypeType;

/**
 * @brief public key information from certificate used by driver when call specific API
 *
 */
typedef struct {
    HSM_DataFormatType          eFmt;       /**< the data format, driver will set it */
    HSM_X509PubKeyKeyTypeType   eKeyType;   /**< the public key type, driver will set it, if RSA, the tRsaPubKey will has the effective data, if ECC ,the tEccPubKey has effective data */
    HSM_X509RsaPublicKeyType    tRsaPubKey; /**< the rsa public key information */
    HSM_X509EccPublicKeyType    tEccPubKey; /**< the ecc public key information */
} HSM_X509PublicKeyInfType;

/**@}*/


/**
 * @name API declaration for HSM
 *
 */
/**@{*/
/**
 * @brief Init the default configuration parameters
 *
 * @param pCfg  The memory this pointer point to is fullfilled by driver internal to get the default parameters(poll mode, disable HSM interrupt).
 * @return HSM_StatusType HSM_STATUS_SUCCESS when get parameters successfully. Others, some error occur.
 */
HSM_StatusType HSM_InitDefaultParams(HSM_InitCfgType *pCfg);

/**
 * @brief Init the HSM driver and HSM hardware.
 *
 * @param u32HsmBusClkFreq  The HSM bus clock in Hz, it's used to initialize the True Random hardware.
 * @param pCfg  The initialize parameters, poll mode/isr mode, the callback to enable/disable HSM isr, if use isr mode, also should provide the stop callback.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when get parameters successfully. Others, some error occur.
 */
HSM_StatusType HSM_Init(uint32_t u32HsmBusClkFreq, const HSM_InitCfgType *pCfg);

/**
 * @brief Reset part of hardware of HSM
 *
 */
void           HSM_ForceAbort(void);

/**
 * @brief Get the lastest algorithm HSM hardware status
 *
 * this API is used for debug, when result is not right, can use it to get the hardware status after call the API
 */
HSM_StatusType HSM_GetLastestHwStatus(void);

/**
 * @brief setup the AES encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_AesEncryptSetupEnv(void);

/**
 * @brief reset the AES encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_AesEncryptReset(void);

/**
 * @brief AES encrypt API
 *
 * @param pCfg  AES encrypt parameters.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_AesEncrypt(const HSM_AesEncryptType *pCfg);

/**
 * @brief AES encrypt poll hardware running state
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN When need call this API again. Others, some error occur.
 */
HSM_StatusType HSM_AesEncryptFinishPoll(void); /* call HSM_AesEncrypt, then call this to loop */

/**
 * @brief exit the AES encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_AesEncryptExitEnv(void);

/**
 * @brief setup the AES decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_AesDecryptSetupEnv(void);

/**
 * @brief reset the AES decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_AesDecryptReset(void);

/**
 * @brief AES decrypt
 *
 * @param pCfg  AES decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_AesDecrypt(const HSM_AesDecryptType *pCfg);

/**
 * @brief Poll API to get the AES decrypt result state
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_AesDecryptFinishPoll(void); /* call HSM_AesDecrypt, then call this to loop */

/**
 * @brief exit the AES decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_AesDecryptExitEnv(void);

/**
 * @brief setup the CMAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CMacSetupEnv(void);

/**
 * @brief reset the CMAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_CMacReset(void);

/**
 * @brief CMAC
 *
 * @param pCfg  CMAC parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CMac(const HSM_CMacType *pCfg);
/**
 * @brief Generate derived key
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_ERROR when NVR.BC1.BIT22 is 1, others some error occur.
 */
HSM_StatusType HSM_CMacGenerateDerivedKey(const HSM_FlexAesEnDecryptType *pCfg);
/**
 * @brief Poll API to trigger the CMAC process.
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_CMacPoll(void); /* call HSM_CMac, then call this to loop */

/**
 * @brief exit the CMAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_CMacExitEnv(void);

/**
 * @brief setup the XCBC-MAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_XMacSetupEnv(void);

/**
 * @brief reset the XMAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_XMacReset(void);

/**
 * @brief XMAC
 *
 * @param pCfg  XMAC parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_XMac(const HSM_XMacType *pCfg);

/**
 * @brief Poll API to trigger the XMAC process.
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_XMacPoll(void); /* call HSM_XMac, then call this to loop */

/**
 * @brief exit the XMAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_XMacExitEnv(void);

/**
 * @brief setup the CCM encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmEncryptSetupEnv(void);

/**
 * @brief reset the CCM encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_CcmEncryReset(void);

/**
 * @brief CCM encrypt
 *
 * @param pCfg  CCM encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmEncry(const HSM_CcmEncryptType *pCfg);

/**
 * @brief Poll API to get the CCM encrypt result state
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_CcmEncryFinishStatPoll(void);

/**
 * @brief exit the CCM encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_CcmEncryptExitEnv(void);

/**
 * @brief setup the CCM decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmDecryptSetupEnv(void);

/**
 * @brief reset the CCM decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_CcmDecryReset(void);

/**
 * @brief CCM decrypt
 *
 * @param pCfg  CCM decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_CcmDecry(const HSM_CcmDecryptType *pCfg);

/**
 * @brief Poll API to get the CCM decrypt result state
 *
 * @return HSM_StatusType HSM_STATUS_AGAIN when need call this api again.
 *        If enable ICV check, pass return HSM_STATUS_PASS, or return HSM_STATUS_FAIL.
 *        If not enable ICV check, finish return HSM_STATUS_SUCCESS. Others, some error occur.
 */
HSM_StatusType HSM_CcmDecryFinishStatPoll(void);

/**
 * @brief exit the CCM decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_CcmDecryptExitEnv(void);

/**
 * @brief setup the GCM encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmEncryptSetupEnv(void);

/**
 * @brief reset the GCM encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_GcmEncryReset(void);

/**
 * @brief GCM encrypt
 *
 * @param pCfg  GCM encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmEncry(const HSM_GcmEncryptType *pCfg);

/**
 * @brief Poll API to get the GCM encrypt result state
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_GcmEncryFinishStatPoll(void);

/**
 * @brief exit the GCM encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_GcmEncryptExitEnv(void);

/**
 * @brief setup the GCM decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmDecryptSetupEnv(void);

/**
 * @brief reset the GCM decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_GcmDecryReset(void);

/**
 * @brief GCM decrypt
 *
 * @param pCfg  GCM decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_GcmDecry(const HSM_GcmDecryptType *pCfg);

/**
 * @brief Poll API to get the GCM encrypt result state
 *
 * @return HSM_StatusType HSM_STATUS_AGAIN when need call this api again.
 *        If enable ICV check, pass return HSM_STATUS_PASS, or return HSM_STATUS_FAIL.
 *        If not enable ICV check, finish return HSM_STATUS_SUCCESS. Others, some error occur.
 */
HSM_StatusType HSM_GcmDecryFinishStatPoll(void);

/**
 * @brief exit the GCM decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_GcmDecryptExitEnv(void);

/**
 * @brief setup the True Random environment
 *
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandSetupEnv(uint32_t u32HsmBusClkFreq);

/**
 * @brief reset the True Random environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandReset(void);

/**
 * @brief reset the True Random environment with re-init the hardware
 *
 * @param u32NewBusClk  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandResetNewClk(uint32_t u32NewBusClk);

/**
 * @brief Get the true random data
 *
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandGet(uint32_t (*pRandom)[TRNG_RANDOM_NUMBER_CNT]);

/**
 * @brief Poll API to get the true random data
 *
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_FAIL when get fail. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_TrueRandGetPoll(uint32_t (*pRandom)[TRNG_RANDOM_NUMBER_CNT]);

/**
 * @brief exit the True Random environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_TrueRandExitEnv(void);

/**
 * @brief setup the Fast Pseudo Random environment
 *
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @param u32InitSeed  when the TRNG not ready, use this seed.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_FastPseudoRandSetupEnv(uint32_t u32HsmBusClkFreq, uint32_t u32InitSeed);

/**
 * @brief reset the Fast Pseudo Random environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_FastPseudoRandReset(void);

/**
 * @brief reset the Fast Pseudo Random environment and re-configure the hardware
 *
 * @param u32NewBusClk  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_FastPseudoRandResetNewClk(uint32_t u32NewBusClk);

/**
 * @brief exit the Fast Pseudo Random environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FastPseudoRandExitEnv(void);

/**
 * @brief get the  Pseudo Random
 * @note this API will get the data immediately, no need wait
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FastPseudoRandGet(uint8_t *pRandom, uint32_t u32ReadByteCount);

/**
 * @brief force to refresh the  Pseudo Random seed
 * @note this API will refresh immediately, no need wait
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FastPseudoRandRefreshSeed(uint32_t u32Seed);

/**
 * @brief set the count of no-repeat fixed size random number
 * @note this API will refresh immediately, no need wait
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FastPseudoRandSetNoRepeatCount(uint32_t u32Count);

/**
 * @brief setup the Pseudo Random environment
 *
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandSetupEnv(uint32_t u32HsmBusClkFreq);

/**
 * @brief reset the Pseudo Random environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandReset(void);

/**
 * @brief reset the Pseudo Random environment and re-configure the hardware
 *
 * @param u32NewBusClk  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandResetNewClk(uint32_t u32NewBusClk);

/**
 * @brief Get the pseudo random data
 *
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandGet(uint32_t (*pRandom)[32]);

/**
 * @brief Poll API to get the pseudo random data
 *
 * @param pRandom  the array address to store the result
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandGetPoll(uint32_t (*pRandom)[32]);

/**
 * @brief Poll API to finish the pseudo random process
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandFinishPoll(void);

/**
 * @brief  API in isr mode to finish the pseudo random process
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandFinish(void);

/**
 * @brief exit the Pseudo Random environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_PseudoRandExitEnv(void);

/**
 * @brief setup the SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ShaSetupEnv(void);

/**
 * @brief reset the SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_ShaReset(void);

/**
 * @brief SHA
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sha(const HSM_ShaType *pCfg);

/**
 * @brief SHA poll API
 *
 * @param pRet the memory to store result
 * @param u32BufSize the size of buffer pRet, for example, if SHA256 used, result is 32bytes, if u32BufSize <= 32, read the length wanted. if u32BufSize > 32, just read 32bytes
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_ShaGetPoll(uint8_t *pRet, uint32_t u32BufSize);

/**
 * @brief exit the SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_ShaExitEnv(void);

/**
 * @brief setup the MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Md5SetupEnv(void);

/**
 * @brief reset the MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_Md5Reset(void);

/**
 * @brief MD5
 *
 * @param pCfg  MD5 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Md5(const HSM_Md5Type *pCfg);

/**
 * @brief MD5 poll API
 *
 * @param pRet the buffer to store result
 * @param u32BufSize the size of buffer pRet, result is 16bytes, if u32BufSize <= 16, read the length wanted. if u32BufSize > 16, just read 16bytes
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Md5GetPoll(uint8_t *pRet, uint32_t u32BufSize);

/**
 * @brief exit the MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Md5ExitEnv(void);


/**
 * @brief setup the SM2 encrypt environment
 *
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2EncrySetupEnv(uint32_t u32HsmBusClkFreq);

/**
 * @brief SM2 encrypt
 *
 * @param pCfg  SM2 encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Encry(const HSM_Sm2EncryptType *pCfg);

/**
 * @brief SM2 encrypt poll API
 *
 * @param pCfg  SM2 encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm2EncryPoll(const HSM_Sm2EncryptType *pCfg);

/**
 * @brief exit the SM2 encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm2EncryExitEnv(void);

/**
 * @brief setup the SM2 decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2DecrySetupEnv(void);

/**
 * @brief SM2 decrypt
 *
 * @param pCfg  SM2 decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Decry(const HSM_Sm2DecryptType *pCfg);

/**
 * @brief SM2 decrypt poll API
 *
 * @param pCfg  SM2 decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm2DecryPoll(const HSM_Sm2DecryptType *pCfg);

/**
 * @brief exit the SM2 decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm2DecryExitEnv(void);

/**
 * @brief setup the SM2 sign environment
 *
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2SignSetupEnv(uint32_t u32HsmBusClkFreq);

/**
 * @brief SM2 sign
 *
 * @param pCfg  SM2 sign parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Sign(const HSM_Sm2SignType *pCfg);

/**
 * @brief SM2 sign poll API
 *
 * @param pCfg  SM2 sign parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm2SignPoll(const HSM_Sm2SignType *pCfg);

/**
 * @brief exit the SM2 sign environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm2SignExitEnv(void);

/**
 * @brief setup the SM2 verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2VerifySetupEnv(void);

/**
 * @brief SM2 verify
 *
 * @param pCfg  SM2 verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2Verify(const HSM_Sm2VerifyType *pCfg);

/**
 * @brief SM2 verify poll API
 *
 * @param pCfg  SM2 verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_PASS when verify pass. HSM_STATUS_FAIL when verify fail. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm2VerifyPoll(const HSM_Sm2VerifyType *pCfg);

/**
 * @brief exit the SM2 verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm2VerifyExitEnv(void);

/**
 * @brief setup the SM2 key pair generate environment
 *
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenKeyPairSetupEnv(uint32_t u32HsmBusClkFreq);

/**
 * @brief SM2 key pair generate
 *
 * @param pCfg  SM2 key pair parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenKeyPair(const HSM_Sm2GenKeyPairType *pCfg);

/**
 * @brief SM2 key pair generate poll API
 *
 * @param pCfg  SM2 key pair parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenKeyPairPoll(const HSM_Sm2GenKeyPairType *pCfg);

/**
 * @brief exit the SM2 key pair generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenKeyPairExitEnv(void);

/**
 * @brief setup the SM2 ZA generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenZaSetupEnv(void);

/**
 * @brief SM2 ZA
 *
 * @param pCfg  SM2 ZA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenZa(const HSM_Sm2GenZaType *pCfg);

/**
 * @brief SM2 ZA generate poll API
 *
 * @param pCfg  SM2 ZA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenZaPoll(const HSM_Sm2GenZaType *pCfg);

/**
 * @brief exit the SM2 ZA generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenZaExitEnv(void);

/**
 * @brief setup the SM2 HASH generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenHashSetupEnv(void);

/**
 * @brief SM2 Hash generate
 *
 * @param pCfg  SM2 HASH parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenHash(const HSM_Sm2GenHashType *pCfg);

/**
 * @brief SM2 Hash generate poll API
 *
 * @param pCfg  SM2 HASH parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenHashPoll(const HSM_Sm2GenHashType *pCfg);

/**
 * @brief exit the SM2 HASH generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm2GenHashExitEnv(void);

/**
 * @brief setup the SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm3SetupEnv(void);

/**
 * @brief reset the SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_Sm3Reset(void);

/**
 * @brief SM3
 *
 * @param pCfg  SM3 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm3(const HSM_Sm3Type *pCfg);

/**
 * @brief SM3 poll API
 *
 * @param pRet the buffer to store result
 * @param u32BufSize the size of buffer pRet, result is 32bytes, if u32BufSize <= 32, read the length wanted. if u32BufSize > 32, just read 32bytes
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm3GetPoll(uint8_t *pRet, uint32_t u32BufSize);

/**
 * @brief exit the SM3  environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm3ExitEnv(void);


/**
 * @brief setup the RSA environment
 *
 * @param u32RsaBitCnt  RSA exp-mod calculation bit count, max 4096
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaSetupEnv(uint32_t u32RsaBitCnt);

/**
 * @brief RSA
 *
 * @param pCfg  RSA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_Rsa(const HSM_RsaType *pCfg);

/**
 * @brief RSA poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaPoll(void);

/**
 * @brief reset the RSA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaReset(void);

/**
 * @brief exit the RSA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaExitEnv(void);

/**
 * @brief setup the RSA SSA PSS Sign environment
 *
 * @param u32RsaBitCnt  RSA calculation mod N, N's bit count
 * @param u32HsmBusClk HSM bus clock
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssSignSetupEnv(uint32_t u32RsaBitCnt, uint32_t u32HsmBusClk);

/**
 * @brief RSA SSA PSS Sign
 *
 * @param pCfg  RSA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssSign(const HSM_RsaSsaPssSignType *pCfg);

/**
 * @brief RSA SSA PSS Sign poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssSignPoll(void);

/**
 * @brief reset the RSA SSA PSS Sign environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssSignReset(void);

/**
 * @brief exit the RSA SSA PSS Sign environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssSignExitEnv(void);


/**
 * @brief setup the RSA SSA PSS Verify environment
 *
 * @param u32RsaBitCnt  RSA calculation mod N, N's bit count
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssVerifySetupEnv(uint32_t u32RsaBitCnt);

/**
 * @brief RSA SSA PSS Verify
 *
 * @param pCfg  RSA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssVerify(const HSM_RsaSsaPssVerifyType *pCfg);

/**
 * @brief RSA SSA PSS Verify poll API
 *
 * @return HSM_StatusType HSM_STATUS_PASS when verify successfully. HSM_STATUS_FAIL when verify failed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssVerifyPoll(void);

/**
 * @brief reset the RSA SSA PSS Verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssVerifyReset(void);

/**
 * @brief exit the RSA SSA PSS Verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPssVerifyExitEnv(void);



/**
 * @brief setup the RSA SSA PKCS1 v1.5 Sign environment
 *
 * @param u32RsaBitCnt  RSA calculation mod N, N's bit count
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15SignSetupEnv(uint32_t u32RsaBitCnt);

/**
 * @brief RSA SSA PKCS1 v1.5 Sign
 *
 * @param pCfg  RSA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15Sign(const HSM_RsaSsaPkcs1V15SignType *pCfg);

/**
 * @brief RSA SSA PKCS1 v1.5 Sign poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15SignPoll(void);

/**
 * @brief reset the RSA SSA PKCS1 v1.5 Sign environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15SignReset(void);

/**
 * @brief exit the RSA SSA PKCS1 v1.5 Sign environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15SignExitEnv(void);


/**
 * @brief setup the RSA SSA PKCS1 v1.5 Verify environment
 *
 * @param u32RsaBitCnt  RSA calculation mod N, N's bit count
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15VerifySetupEnv(uint32_t u32RsaBitCnt);

/**
 * @brief RSA SSA PKCS1 v1.5 Verify
 *
 * @param pCfg  RSA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15Verify(const HSM_RsaSsaPkcs1V15VerifyType *pCfg);

/**
 * @brief RSA SSA PKCS1 v1.5 Verify poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15VerifyPoll(void);

/**
 * @brief reset the RSA SSA PKCS1 v1.5 Verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15VerifyReset(void);

/**
 * @brief exit the RSA SSA PKCS1 v1.5 Verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaSsaPkcs1V15VerifyExitEnv(void);


#if defined HSM_BASE64ENCODE_USED
/* the following API is not provide so far, they are implemented by software, used for RSA certificate in the future */
HSM_StatusType HSM_Base64Encode(HSM_Base64EncodeType *pCfg);
HSM_StatusType HSM_Base64Decode(HSM_Base64DecodeType *pCfg);
#endif

/**
 * @brief setup the SM4 encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm4EncryptSetupEnv(void);

/**
 * @brief reset SM4 encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_Sm4EncryptReset(void);

/**
 * @brief SM4 encrypt
 *
 * @param pCfg  SM4 encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm4Encrypt(const HSM_Sm4EncryptType *pCfg);

/**
 * @brief SM4 encrypt status poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm4EncryptFinishPoll(void);

/**
 * @brief exit the SM4 encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm4EncryptExitEnv(void);

/**
 * @brief setup the SM4 decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm4DecryptSetupEnv(void);

/**
 * @brief reset the SM4 decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_Sm4DecryptReset(void);

/**
 * @brief SM4 decrypt
 *
 * @param pCfg  SM4 decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_Sm4Decrypt(const HSM_Sm4DecryptType *pCfg);

/**
 * @brief SM4 decrypt status poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_Sm4DecryptFinishPoll(void);

/**
 * @brief exit the SM4 decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_Sm4DecryptExitEnv(void);

/**
 * @brief ecc parameters get API
 *
 * @param eIdx  the ecc curve parameter index, refer to HSM_DRV_ECC_CURVE_PRM_IDX_SECP224R1 and so on
 * @param pEccPrm  the buffer to store the ecc curve parameter
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_EccGetCurveParam(HSM_DrvEccCurvePrmIndexType eIdx, HSM_DrvEccCurveParamType *pEccPrm);

/**
 * @brief setup the ECC verify environment
 *
 * @param u32BitCnt  ECC modulus P bit count, only  check the number in driver, hardware do nothing with it
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccVerifySetupEnv(uint32_t u32BitCnt);

/**
 * @brief ECC Verify
 *
 * @param pCfg  ECC verify parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccVerify(const HSM_EccVerifyType *pCfg);

/**
 * @brief reset ECC verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_EccVerifyReset(void);

/**
 * @brief ECC Verify poll API
 *
 * @return HSM_StatusType HSM_STATUS_PASS when verify pass. HSM_STATUS_FAIL when verify fail. HSM_STATUS_AGAIN When need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_EccVerifyPoll(void);

/**
 * @brief exit the ECC verify environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccVerifyExitEnv(void);

/**
 * @brief setup the ECC sign environment
 *
 * @param u32BitCnt  ECC modulus P bit count, only  check the number in driver, hardware do nothing with it
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccSignSetupEnv(uint32_t u32BitCnt, uint32_t u32HsmBusClkFreq);

/**
 * @brief reset ECC sign environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_EccSignReset(void);

/**
 * @brief ECC Sign
 *
 * @param pCfg  ECC sign parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccSign(const HSM_EccSignType *pCfg);

/**
 * @brief ECC sign poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */

HSM_StatusType HSM_EccSignPoll(void);

/**
 * @brief exit the ECC sign environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccSignExitEnv(void);

/**
 * @brief setup the ECC key pair generate environment
 *
 * @param u32BitCnt  ECC modulus P bit count, only  check the number in driver, hardware do nothing with it
 * @param u32HsmBusClkFreq  the current HSM hardware bus clock in Hz
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccKeyPairGenSetupEnv(uint32_t u32BitCnt, uint32_t u32HsmBusClkFreq);

/**
 * @brief reset ECC key pair generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_EccKeyPairGenReset(void);

/**
 * @brief ECC key pair generate
 *
 * @param pCfg  ECC key pair generate parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccKeyPairGen(const HSM_EccKeyPairGenType *pCfg);

/**
 * @brief ECC key pair generate poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_EccKeyPairGenPoll(void);

/**
 * @brief exit the ECC key pair generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccKeyPairGenExitEnv(void);

/**
 * @brief setup the ECC public key generate environment
 *
 * @param u32BitCnt  ECC modulus P bit count, only  check the number in driver, hardware do nothing with it
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccPubKeyGenSetupEnv(uint32_t u32BitCnt);

/**
 * @brief reset ECC public key generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_EccPubKeyGenReset(void);

/**
 * @brief ECC public key generate from private key
 *
 * @param pCfg  ECC public key generate parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccPubKeyGen(const HSM_EccPubKeyGenType *pCfg);

/**
 * @brief ECC public key generate poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_EccPubKeyGenPoll(void);

/**
 * @brief exit the ECC public key generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccPubKeyGenExitEnv(void);

/**
 * @brief setup the ECC encrypt environment
 *
 * @param u32BitCnt  ECC modulus P bit count, only  check the number in driver, hardware do nothing with it
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyEncrySetupEnv(uint32_t u32BitCnt);

/**
 * @brief reset ECC encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyEncryReset(void);

/**
 * @brief ECC encrypt
 *
 * @param pCfg  ECC encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyEncry(const HSM_EccEasyEncryType *pCfg);

/**
 * @brief ECC encrypt poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyEncryPoll(void);

/**
 * @brief exit the ECC encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccEasyEncryExitEnv(void);

/**
 * @brief setup the ECC decrypt environment
 *
 * @param u32BitCnt  ECC modulus P bit count, only  check the number in driver, hardware do nothing with it
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyDecrySetupEnv(uint32_t u32BitCnt);

/**
 * @brief reset ECC decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyDecryReset(void);

/**
 * @brief ECC decrypt
 *
 * @param pCfg  ECC decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyDecry(const HSM_EccEasyDecryType *pCfg);

/**
 * @brief ECC decrypt poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_EccEasyDecryPoll(void);

/**
 * @brief exit the ECC decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccEasyDecryExitEnv(void);

/**
 * @brief HSM exit current algorithm environment API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when driver not in algorithm enviroment.
 */
HSM_StatusType HSM_CommonExitEnv(void);

/**
 * @brief setup the scatter SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterShaSetupEnv(void);

/**
 * @brief reset the scatter SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_ScatterShaReset(void);

/**
 * @brief exit the scatter SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_ScatterShaExitEnv(void);

/**
 * @brief Scatter SHA Init API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 * @note sha160,sha224,sha256 input data byte length should be 64bytes aligned; sha384, sha512, sha512_224, sha512_256 should 128bytes aligned.
 */
HSM_StatusType HSM_ScatterShaInit(const HSM_ScatterShaInitType *pCfg);

/**
 * @brief Scatter SHA Update API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 * @note sha160,sha224,sha256 input data byte length should be 64bytes aligned; sha384, sha512, sha512_224, sha512_256 should 128bytes aligned.
 */
HSM_StatusType HSM_ScatterShaUpdate(const HSM_ShaScatterCtxType *pCfg);

/**
 * @brief Scatter SHA Finish API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterShaFinalize(const HSM_ScatterShaFinalType *pCfg);

/**
 * @brief Scatter SHA poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_ScatterShaStatePoll(void);


/**
 * @brief setup the scatter MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterMd5SetupEnv(void);

/**
 * @brief reset the scatter MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_ScatterMd5Reset(void);

/**
 * @brief exit the scatter MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_ScatterMd5ExitEnv(void);

/**
 * @brief Scatter MD5 Init API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterMd5Init(const HSM_ScatterMd5InitType *pCfg);

/**
 * @brief Scatter MD5 Update API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterMd5Update(const HSM_Md5ScatterCtxType *pCfg);

/**
 * @brief Scatter MD5 Finish API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterMd5Finalize(const HSM_ScatterMd5FinalType *pCfg);

/**
 * @brief Scatter MD5 poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_ScatterMd5StatePoll(void);

/**
 * @brief setup the scatter SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterSm3SetupEnv(void);

/**
 * @brief reset the scatter SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_ScatterSm3Reset(void);

/**
 * @brief exit the scatter SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_ScatterSm3ExitEnv(void);

/**
 * @brief Scatter SM3 Init API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterSm3Init(const HSM_ScatterSm3InitType *pCfg);

/**
 * @brief Scatter SM3 Update API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterSm3Update(const HSM_Sm3ScatterCtxType *pCfg);

/**
 * @brief Scatter SM3 Finish API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterSm3Finalize(const HSM_ScatterSm3FinalType *pCfg);

/**
 * @brief Scatter SM3 poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_ScatterSm3StatePoll(void);

/**
 * @brief setup the flexiable SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexShaSetupEnv(void);

/**
 * @brief reset the flexiable SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_FlexShaReset(void);

/**
 * @brief exit the flexiable SHA environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FlexShaExitEnv(void);

/**
 * @brief flexiable SHA Init API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexShaInit(const HSM_ShaInitType *pCfg);

/**
 * @brief flexiable SHA Update API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexShaUpdate(const HSM_ShaScatterCtxType *pCfg);

/**
 * @brief flexiable SHA Finish API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexShaFinalize(const HSM_ShaFinalType *pCfg);

/**
 * @brief flexiable SHA poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_FlexShaStatePoll(void);

/**
 * @brief flexiable SHA HMAC/SMAC configure parameter API
 * @note this api should called before init api
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_FlexShaConfMac(const HSM_HashMacType *pCfg);


/**
 * @brief setup the scatter MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5SetupEnv(void);

/**
 * @brief reset the scatter MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5Reset(void);

/**
 * @brief exit the scatter MD5 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5ExitEnv(void);

/**
 * @brief Scatter MD5 Init API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5Init(const HSM_Md5InitType *pCfg);

/**
 * @brief Scatter MD5 Update API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5Update(const HSM_Md5ScatterCtxType *pCfg);

/**
 * @brief Scatter MD5 Finish API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5Finalize(const HSM_Md5FinalType *pCfg);

/**
 * @brief Scatter MD5 poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5StatePoll(void);

/**
 * @brief flexiable MD5 HMAC/SMAC configure parameter API
 * @note this api should called before init api
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_FlexMd5ConfMac(const HSM_HashMacType *pCfg);

/**
 * @brief setup the scatter SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3SetupEnv(void);

/**
 * @brief reset the scatter SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3Reset(void);

/**
 * @brief exit the scatter SM3 environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3ExitEnv(void);

/**
 * @brief Scatter SM3 Init API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3Init(const HSM_Sm3InitType *pCfg);

/**
 * @brief Scatter SM3 Update API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3Update(const HSM_Sm3ScatterCtxType *pCfg);

/**
 * @brief Scatter SM3 Finish API
 *
 * @param pCfg  SHA parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3Finalize(const HSM_Sm3FinalType *pCfg);

/**
 * @brief Scatter SM3 poll API
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3StatePoll(void);

/**
 * @brief flexiable SM3 HMAC/SMAC configure parameter API
 * @note this api should called before init api
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_FlexSm3ConfMac(const HSM_HashMacType *pCfg);

/**
 * @brief Setup the flexiable AES encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy.
 */
HSM_StatusType HSM_FlexAesEncryptSetupEnv(void);

/**
 * @brief Reset the flexiable AES encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_FlexAesEncryptReset(void);

/**
 * @brief Exit the flexiable AES encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_FlexAesEncryptExitEnv(void);

/**
 * @brief start AES encrypt
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexAesEncrypt(const HSM_FlexAesEnDecryptType *pCfg);
/**
 * @brief Generate derived key
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_ERROR when NVR.BC1.BIT22 is 1, others some error occur.
 */
HSM_StatusType HSM_FlexAesEncryptGenerateDerivedKey (const HSM_FlexAesEnDecryptType *pCfg);

/**
 * @brief poll mode to trigger the AES encrypt process
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when API finisn successfully. HSM_STATUS_AGAIN when need call this API again. Others, some error occur.
 */
HSM_StatusType HSM_FlexAesEncryptPoll(void);

/**
 * @brief Setup the flexiable AES decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy.
 */
HSM_StatusType HSM_FlexAesDecryptSetupEnv(void);

/**
 * @brief Reset the flexiable AES decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_FlexAesDecryptReset(void);

/**
 * @brief Exit the flexiable AES decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_FlexAesDecryptExitEnv(void);
/**
 * @brief Generate derived key
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_ERROR when NVR.BC1.BIT22 is 1, others some error occur.
 */
HSM_StatusType HSM_FlexAesDecryptGenerateDerivedKey (const HSM_FlexAesEnDecryptType *pCfg);

/**
 * @brief start AES decrypt
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY when driver is busy. Others, some error occur.
 * @note if the data is encrypted by zero-padding, the zero padded CAN NOT be removed by driver, user should process it manually.
 */
HSM_StatusType HSM_FlexAesDecrypt(const HSM_FlexAesEnDecryptType *pCfg);

/**
 * @brief poll mode to trigger the AES decrypt process
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when API finisn successfully. HSM_STATUS_AGAIN when need call this API again. Others, some error occur.
 */
HSM_StatusType HSM_FlexAesDecryptPoll(void);


/**
 * @brief exit the PBKDF2 generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_PBKDF2ExitEnv(void);

/**
 * @brief setup the PBKDF2 generate environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_PBKDF2SetupEnv(void);

/**
 * @brief SM2 PBKDF2 generate
 *
 * @param pCfg  PBKDF2 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_PBKDF2(const HSM_PBKDF2Type *pCfg);

/**
 * @brief SM2 PBKDF2 generate poll API
 *
 * @param pCfg  PBKDF2 parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_PBKDF2Poll(const HSM_PBKDF2Type *pCfg);

/**
 * @brief set up environment for RSA Encryption Schemes OAEP padding encrypt
 *
 * @param u32RsaBitCnt  the RSA's parameter N's bit count, only support 1-4096
 * @param u32BusClk     the HSM's bus clock
 * @param u32Seed       if use pseudo number in HSM_RsaEsOaepEncrypt's parameter, this seed will take effect
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepEncryptSetupEnv(uint32_t u32RsaBitCnt, uint32_t u32BusClk, uint32_t u32Seed);

/**
 * @brief RSA OAEP encrypt
 *
 * @param pCfg  RSA OAEP encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepEncrypt(const HSM_RsaEsOaepEncryptType *pCfg);

/**
 * @brief RSA OAEP encrypt poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepEncryptPoll(void);

/**
 * @brief Reset the RSA OAEP encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_RsaEsOaepEncryptReset(void);

/**
 * @brief exit the RSA OAEP encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepEncryptExitEnv(void);

/**
 * @brief set up environment for RSA Encryption Schemes OAEP padding decrypt
 *
 * @param u32RsaBitCnt  the RSA's parameter N's bit count, only support 1-4096
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepDecryptSetupEnv(uint32_t u32RsaBitCnt);

/**
 * @brief RSA OAEP decrypt
 *
 * @param pCfg  RSA OAEP decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepDecrypt(const HSM_RsaEsOaepDecryptType *pCfg);

/**
 * @brief RSA OAEP decrypt poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepDecryptPoll(void);

/**
 * @brief Reset the RSA OAEP decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_RsaEsOaepDecryptReset(void);

/**
 * @brief exit the RSA OAEP decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaEsOaepDecryptExitEnv(void);

/**
 * @brief set up environment for RSA Encryption Schemes PKCS1V1.5 padding decrypt
 *
 * @param u32RsaBitCnt  the RSA's parameter N's bit count, only support 1-4096
 * @param u32BusClk     the HSM's bus clock
 * @param u32Seed       if use pseudo number in HSM_RsaEsPkcs1V15Encrypt's parameter, this seed will take effect
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15EncryptSetupEnv(uint32_t u32RsaBitCnt, uint32_t u32BusClk, uint32_t u32Seed);

/**
 * @brief RSA PKCS1V1.5 encrypt
 *
 * @param pCfg  RSA PKCS1V1.5 encrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15Encrypt(const HSM_RsaEsPkcs1V15EncryptType *pCfg);

/**
 * @brief RSA PKCS1V1.5 encrypt poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15EncryptPoll(void);

/**
 * @brief Reset the RSA PKCS1V1.5 encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_RsaEsPkcs1V15EncryptReset(void);

/**
 * @brief exit the RSA OAEP encrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15EncryptExitEnv(void);

/**
 * @brief set up environment for RSA Encryption Schemes PKCS1V1.5 padding decrypt
 *
 * @param u32RsaBitCnt  the RSA's parameter N's bit count, only support 1-4096
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15DecryptSetupEnv(uint32_t u32RsaBitCnt);

/**
 * @brief RSA PKCS1V1.5 decrypt
 *
 * @param pCfg  RSA PKCS1V1.5 decrypt parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15Decrypt(const HSM_RsaEsPkcs1V15DecryptType *pCfg);

/**
 * @brief RSA PKCS1V1.5 decrypt poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15DecryptPoll(void);

/**
 * @brief Reset the RSA PKCS1V1.5 decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_RsaEsPkcs1V15DecryptReset(void);

/**
 * @brief exit the RSA PKCS1V1.5 decrypt environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_RsaEsPkcs1V15DecryptExitEnv(void);

/**
 * @brief set up environment for scatter CMAC
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_ScatterCMacSetupEnv(void);

/**
 * @brief Reset the scatter cmac environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_ScatterCMacReset(void);

/**
 * @brief exit the scatter cmac environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_ScatterCMacExitEnv(void);

/**
 * @brief CMAC process the first block data
 *
 * @param pCfg first block data parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterCMacInit(const HSM_ScatterXCMacInitType *pCfg);

/**
 * @brief CMAC process the block data from the second one, except the last one
 *
 * @param pCfg first block data parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterCMacUpdate(const HSM_ScatterXCMacUpdateType *pCfg);

/**
 * @brief CMAC process the last block data
 *
 * @param pCfg the last block data parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_ScatterCMacFinalize(const HSM_ScatterXCMacFinalType *pCfg);

/**
 * @brief init/update/finalize process poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_ScatterCMacStatePoll(void);

/**
 * @brief set up environment for flexiable CMAC
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. Others, some error occur.
 */
HSM_StatusType HSM_FlexCMacSetupEnv(void);

/**
 * @brief Reset the flexiable CMAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_FlexCMacReset(void);

/**
 * @brief exit the flexiable CMAC environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_FlexCMacExitEnv(void);

/**
 * @brief CMAC process the first block data
 *
 * @param pCfg first block data parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexCMacInit(const HSM_FlexXCMacInitType *pCfg);

/**
 * @brief CMAC process the block data from the second one
 *
 * @param pCfg first block data parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexCMacUpdate(const HSM_FlexXCMacUpdateType *pCfg);

/**
 * @brief CMAC process the last block data
 *
 * @param pCfg the last block data parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_FlexCMacFinalize(const HSM_FlexXCMacFinalType *pCfg);


/**
 * @brief init/update/finalize process poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_FlexCMacStatePoll(void);



/**
 * @brief setup the big number calculation environment
 *
 * @param u32RsaBitCnt the modulus's bit count
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_BnCalcSetupEnv(uint32_t u32RsaBitCnt);

/**
 * @brief exit the big number calculation environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_BnCalcExitEnv(void);

/**
 * @brief calculate the (A^E) % N
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_BnCalcModExp(const HSM_BnCalcModExpType *pCfg);

/**
 * @brief calculate the (A + B) % N
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_BnCalcModAdd(const HSM_BnCalcABType *pCfg);

/**
 * @brief calculate the (A - B) % N
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_BnCalcModSub(const HSM_BnCalcABType *pCfg);

/**
 * @brief calculate the (A x B) % N
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_BnCalcModMultiply(const HSM_BnCalcABType *pCfg);

/**
 * @brief calculate the sqrt(A) % N
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_BnCalcModSquareRoot (const HSM_BnCalcAType *pCfg);

/**
 * @brief big number calculation poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_BnCalcPoll(void);

/**
 * @brief Reset the big number calculation environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_LOGIC_ERR when not in the right environment.
 */
HSM_StatusType HSM_BnCalcReset(void);

/**
 * @brief setup the ECC point calculation environment
 *
 * @param u32BitCnt the modulus's bit count
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccCalcSetupEnv(uint32_t u32BitCnt);

/**
 * @brief exit the ECC point calculation environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccCalcExitEnv(void);

/**
 * @brief reset the ECC point calculation environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccCalcReset(void);

/**
 * @brief calculate the (P1 + P2)
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccCalcAdd(const HSM_EccPointAddType *pCfg);

/**
 * @brief calculate the (P1 x 2)
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccCalcX2(const HSM_EccPointX2Type *pCfg);

/**
 * @brief calculate the (P1 x N)
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccCalcXN(const HSM_EccPointXNType *pCfg);

/**
 * @brief ECC point calculation poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_EccCalcPoll(void);

/**
 * @brief setup the ECC point X -> Y environment
 *
 * @param u32BitCnt the modulus's bit count
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccDeriveYFromXSetupEnv(uint32_t u32BitCnt);

/**
 * @brief derive the Y from the X on ECC curve
 *
 * @param pCfg   parameters for trigger the process
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_EccDeriveYFromX(const HSM_EccDeriveYFromXType *pCfg);

/**
 * @brief ECC point X->Y calculation poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_EccDeriveYFromXPoll(void);

/**
 * @brief reset the ECC point X->Y calculation environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccDeriveYFromXReset(void);

/**
 * @brief exit the ECC point X->Y calculation environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_EccDeriveYFromXExitEnv(void);

/**
 * @brief get the public key data detail from the PEM string format certificate
 * @note this API will get the information directly, it doesn't trigger interrupt or poll.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_X509_GetCertKeyToCheckInf(const char *pPEM, HSM_X509KeyToCheckInfType *pPublicKeyInf);

/**
 * @brief get the public key data detail from the byte data after base64-decoded PEM string format certificate
 * @note this API will get the information directly, it doesn't trigger interrupt or poll.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_X509_GetCertKeyToCheckInfAfterBase64Decode(const uint8_t *pBytesData, uint32_t u32TotalByteCnt, HSM_X509KeyToCheckInfType *pPublicKeyInf);

/**
 * @brief get the root public key data detail from the PEM string format certificate
 * @note this API will get the information directly, it doesn't trigger interrupt or poll.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_X509_GetCertKeyInf(const char *pPEM, HSM_X509CertKeyInfType *pPublicKeyInf);

/**
 * @brief get the root public key data detail from the byte data after base64-decoded PEM string format certificate
 * @note this API will get the information directly, it doesn't trigger interrupt or poll.
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_X509_GetCertKeyInfAfterBase64Decode(const uint8_t *pBytesData, uint32_t u32TotalByteCnt, HSM_X509CertKeyInfType *pPublicKeyInf);

/**
 * @brief setup environment for root public key check the signed certificate
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_X509_CheckKeySignatureSetupEnv(void);

/**
 * @brief exit the public key certificate validity check environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_X509_CheckKeySignatureExitEnv(void);

/**
 * @brief use the root public key certificate to check the validity of the signed public key certificate
 *
 * @param pPublicKeyToCheck  the public key to be check
 * @param pPublicKeyRoot     the root public key to check
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_X509_CheckKeySignature(const HSM_X509KeyToCheckInfType *pPublicKeyToCheck, const HSM_X509CertKeyInfType *pPublicKeyRoot);

/**
 * @brief X.509 check public key poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_X509_CheckKeySignaturePoll(void);

/**
 * @brief setup environment for extracting public key from X.509 public key certificate
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_BUSY When driver is busy. Others, some error occur.
 */
HSM_StatusType HSM_X509_GetPubKeySetupEnv(void);

/**
 * @brief exit the public key certificate extract environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_X509_GetPubKeyExitEnv(void);

/**
 * @brief extract the public key from the certificate
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need poll(in poll mode)/wait interrupt callback(in isr mode). Others, some error occur.
 */
HSM_StatusType HSM_X509_GetPubKey(const HSM_X509CertKeyInfType *pPublicKeyInf, HSM_X509PublicKeyInfType *pPublicKey);

/**
 * @brief X.509 public key extract poll api
 *
 * @note the state machine in driver internal need this api to trigger the transition between states
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed. HSM_STATUS_AGAIN when need call this api again. Others, some error occur.
 */
HSM_StatusType HSM_X509_GetPubKeyPoll(void);

/**
 * @brief reset X.509 public key extract environment
 *
 * @return HSM_StatusType HSM_STATUS_SUCCESS when succeed.  Others, some error occur.
 */
HSM_StatusType HSM_X509_GetPubKeyReset(void);


/**
 * @brief HSM isr function
 *
 * @note DO NOT use this function in interrupt vector table, suggest user implement one function to invoke this API, and set the wrapper function as the entry in the interrupt vector table
 */
void HSM_IRQHandler(void);
/**@}*/

/** @}*/ /* module_driver_hsm */

#if defined(__cplusplus)
}
#endif
#endif /* _DRIVER_MODULE_DRIVER_hsm_H_ */
