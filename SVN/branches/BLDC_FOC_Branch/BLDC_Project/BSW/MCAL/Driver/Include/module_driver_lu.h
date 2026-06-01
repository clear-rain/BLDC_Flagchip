/**
 * @file module_driver_lu.h
 * @author Flagchip032
 * @brief LU driver type definition and API
 * @version 2.0.0
 * @date 2024-11-10
 *
 * @copyright Copyright (c) 2024 Flagchip Semiconductors Co., Ltd.
 *
 * @details
 */
/********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip032   N/A          First version
*********************************************************************************/
#ifndef _DRIVER_MODULE_DRIVER_LU_H_
#define _DRIVER_MODULE_DRIVER_LU_H_

#include "HwA_lu.h"

#if LU_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_lu
 * @{
 */
#if defined(__cplusplus)
extern "C" {
#endif


/**
 * @name  LU API Service IDs
 * @{
 */
#define LU_INIT_ID    0x00   /**< Service ID for LU initialization. */
#define LU_DEINIT_ID  0x01   /**< Service ID for LU deinitialization. */
/**
 * @}
 */

/**
 * @name  LU Dev Error Code
 * @{
 */
#define LU_E_PARAM_INSTANCE     0x01U   /**< Error code for invalid LU instance parameter. */
#define LU_E_PARAM_NULLPTR      0x02U   /**< Error code for null pointer parameter. */
/**
 * @}
 */

/**
 * @brief Macro for configuring AOI inputs.
 *
 * @param AoiIn AOI input index.
 * @param AoiInN AOI input N index.
 * @param InNCfgNType Input N configuration type.
 * @return Configured bit field.
 */
#define LU_AOI_IN_N_CFG_N(AoiIn, AoiInN, InNCfgNType) ((((uint32_t)(InNCfgNType) & 0x3U) << (((uint32_t)3U - (uint32_t)(AoiInN)) << 3U)) << (((uint32_t)3U - (uint32_t)(AoiIn)) << 3U))

/**
 * @brief Macro for getting the mask for AOI input configuration.
 *
 * @param AoiIn AOI input index.
 * @param AoiInN AOI input N index.
 * @return Mask for the configuration.
 */
#define LU_AOI_IN_N_CFG_N_MASK(AoiIn, AoiInN) (((uint32_t)0x3U << (((uint32_t)3U - (uint32_t)(AoiInN)) << 3U)) << (((uint32_t)3U - (uint32_t)(AoiIn)) << 3U))

/**
 * @brief Macro for configuring an individual AOI input.
 *
 * @param AoiInN AOI input N index.
 * @param CfgNType Configuration type.
 * @return Configured bit field.
 */
#define LU_AOI_IN_CFG(AoiInN, CfgNType) ((((uint32_t)(CfgNType) & 0x3U) << (((uint32_t)3U - (uint32_t)(AoiInN)) << 1U)))

/**
 * @brief Macro for getting the mask for an individual AOI input configuration.
 *
 * @param AoiInN AOI input N index.
 * @return Mask for the configuration.
 */
#define LU_AOI_IN_CFG_MASK(AoiInN) ((((uint32_t)0x3U) << (((uint32_t)3U - (uint32_t)(AoiInN)) << 1U)))

/**
 * @brief Macro for configuring an AOI input.
 *
 * @param AoiIn AOI input index.
 * @param InNType Input configuration type.
 * @return Configured bit field.
 */
#define LU_AOI_IN_N_CFG(AoiIn, InNType) ((((uint32_t)(InNType) & 0xFFU) << (((uint32_t)3U - (uint32_t)(AoiIn)) << 3U)))

/**
 * @brief Macro for getting the mask for an AOI input configuration.
 *
 * @param AoiIn AOI input index.
 * @return Mask for the configuration.
 */
#define LU_AOI_IN_N_CFG_MASK(AoiIn) ((((uint32_t)0xFFU) << (((uint32_t)3U - (uint32_t)(AoiIn)) << 3U)))

/**
 * @brief Macro for setting synchronous control for an input.
 *
 * @param InputN Input index.
 * @param value Value to set.
 * @return Configured bit field.
 */
#define LU_SYNC_CONTROL_INPUT_N(InputN, value) ((uint32_t)(value) << (InputN))
/**
 * @}
 */


/**
 * @brief LU instance type.
 */
typedef enum
{
    LU_INSTANCE_0 = 0U,  /**< LU instance 0 is selected. Corresponds to the first available LU module. */
} LU_InstanceType;

/**
 * @brief LU return status type.
 */
typedef enum
{
    LU_STATUS_SUCCESS = 0U,    /**< Operation was successful. */
    LU_STATUS_PARAM_INVALID = 1U    /**< Invalid parameter was passed. */
} LU_StatusType;

/**
 * @brief LU AOI input type.
 */
typedef enum
{
    LU_AOI_IN_0 = 0U,
    LU_AOI_IN_1,
    LU_AOI_IN_2,
    LU_AOI_IN_3,
} LU_AoiInType;

/**
 * @brief LU AOI input (n) type.
 */
typedef enum
{
    LU_AOI_IN_N_A = 0U,
    LU_AOI_IN_N_B,
    LU_AOI_IN_N_C,
    LU_AOI_IN_N_D
} LU_AoiInNType;

/**
 * @brief LU input mode type.
 */
typedef enum
{
    FORCE_ITEM_AS_ZERO    = 0U,    /**< Force item as logic zero. */
    PASS_THROUGH_ITEM,             /**< Pass through item. */
    COMPLEMENT_ITEM,               /**< Complement item. */
    FORCE_ITEM_AS_ONE              /**< Force item as logic one. */
} LU_InModeType;

/**
 * @brief LU output initialization value.
 */
typedef enum
{
    LU_OUTPUT_INIT_ZERO = 0U,    /**< Initialize output as logic zero. */
    LU_OUTPUT_INIT_ONE,          /**< Initialize output as logic one. */
    LU_OUTPUT_INIT_DISABLE       /**< Disable initialization. */
} LU_OutputInitValueType;

/**
 * @brief LU AOI input (n) configuration.
 */
typedef struct
{
    LU_InModeType eInNACfg;       /**< AOI IN(n) A configuration. */
    LU_InModeType eInNBCfg;       /**< AOI IN(n) B configuration. */
    LU_InModeType eInNCCfg;       /**< AOI IN(n) C configuration. */
    LU_InModeType eInNDCfg;       /**< AOI IN(n) D configuration. */
} LU_InConfigType;

/**
 * @brief LU AOI configuration.
 */
typedef struct
{
    LU_InConfigType tIn0Config;         /**< AOI IN0 configuration. */
    LU_InConfigType tIn1Config;         /**< AOI IN1 configuration. */
    LU_InConfigType tIn2Config;         /**< AOI IN2 configuration. */
    LU_InConfigType tIn3Config;         /**< AOI IN3 configuration. */
} LU_AoiConfigType;

/**
 * @brief LU inputs synchronous control.
 */
typedef struct
{
    bool bInputNA;        /**< LU IN(n) A sync control. */
    bool bInputNB;        /**< LU IN(n) B sync control. */
    bool bInputNC;        /**< LU IN(n) C sync control. */
    bool bInputND;        /**< LU IN(n) D sync control. */
} LU_InputsSyncCtrlType;

/**
 * @brief LU initialization type.
 */
typedef struct
{
    LU_LgType eLgNum;                          /**< LG number. */
    LU_AoiConfigType tAoi0Config;              /**< AOI0 configuration. */
    LU_AoiConfigType tAoi1Config;              /**< AOI1 configuration. */
    LU_InputsSyncCtrlType tSyncCtrl;           /**< Inputs sync control. */
    LU_BypassModeType eAoiMode;                /**< AOI mode. */
    LU_ConfigModeType eFFMode;                 /**< Flip-flop mode. */
    LU_OutputInitValueType eFFInitValue;       /**< Flip-flop initial value. */
    LU_InputNType eFbMode;                     /**< Feedback override control in JKFF mode. */
    uint8_t u8Aoi0FiltCnt;                     /**< AOI0 input filter sample count. */
    uint8_t u8Aoi0Period;                      /**< AOI0 input filter sample period. */
    uint8_t u8Aoi1FiltCnt;                     /**< AOI1 input filter sample count. */
    uint8_t u8Aoi1Period;                      /**< AOI1 input filter sample period. */
} LU_InitType;


/**
 * @brief Initializes a LU instance.
 *
 * @param eInstance The LU instance to initialize.
 * @param pInitStruct Pointer to the initialization structure.
 * @return LU return type indicating success or failure.
 */
LU_StatusType LU_Init(LU_InstanceType eInstance, const LU_InitType *const pInitStruct);

/**
 * @brief Deinitializes a LU instance.
 *
 * @param eInstance The LU instance to deinitialize.
 */
void LU_Deinit(LU_InstanceType eInstance);
#if defined(__cplusplus)
}
#endif

/*** @}*/
#endif
#endif
