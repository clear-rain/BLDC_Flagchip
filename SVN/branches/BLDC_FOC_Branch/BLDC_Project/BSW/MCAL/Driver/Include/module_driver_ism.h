/**
 * @file module_driver_ism.h
 * @author Flagchip
 * @brief ISM driver type definition and API
 * @version 2.0.0
 * @date 2024-07-25
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    QXW0076       N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_ISM_H_
#define _DRIVER_MODULE_DRIVER_ISM_H_

#include "HwA_ism.h"

#if ISM_INSTANCE_COUNT > 0U

/**
 * @addtogroup module_driver_ism
 * @{
 */

#define ISM_ECM_CHANNEL(x)  (1<<(x)) /**<   Define the ISM_ECM_CHANNEL macro, which calculates the mask value for an ECM channel based on the channel number (x) */

#define ISM_LAM_CHANNEL(x)  (1<<(x)) /**<   Define the ISM_LAM_CHANNEL macro, which calculates the mask value for an LAM channel based on the channel number (x) */

#define ISM_FPC_CHANNEL(x)  (1<<(x)) /**<   Define the ISM_FPC_CHANNEL macro, which calculates the mask value for an FPC channel based on the channel number (x) */

#define FPC_INSTANCE_COUNT (16U)     /**<   Define the FPC_INSTANCE_COUNT constant, indicating the number of FPC instances is 16 */

#define LAM_INSTANCE_COUNT (16U)     /**<   Define the LAM_INSTANCE_COUNT constant, indicating the number of LAM instances is 16 */

#define ECM_INSTANCE_COUNT (4U)      /**<   Define the ECM_INSTANCE_COUNT constant, indicating the number of ECM instances is 4 */


typedef enum
{
    ISM_INSTANCE_0 = 0U,  /**<  ISM instance 0 is selected. */ 
} ISM_InstanceType; /* Defines the ISM instance type enumeration to identify different ISM instances. */


#define ISM_COMMON_INIT_ID 							0U /**<   Defines the initialization identifier for ISM common components */

#define ISM_FPC_CONFIG_ID 							1U /**<   Defines the configuration identifier for Flash Parameter Configuration (FPC) */

#define ISM_FPC_ENABLE_ID 							2U /**<   Defines the enable identifier for FPC functionalities */

#define ISM_LAM_CONFIG_ID 							3U /**<   Defines the configuration identifier for Load and Manage (LAM) functionalities */

#define ISM_LAM_ENABLE_ID 							4U /**<   Defines the enable identifier for LAM functionalities */

#define ISM_ECM_CONFIG_ID 							5U /**<   Defines the configuration identifier for Extended Configuration and Management (ECM) functionalities */

#define ISM_STATUS_FUNCTION_ERROR			 0x0U /**<   Defines a status error code indicating a function error */

#define ISM_E_PARAM_CHANNEL   			     0x02U /**<   Defines an error code indicating a channel parameter error */

#define ISM_E_PARAM_POINTER   			     0x03U /**<   Defines an error code indicating a pointer parameter error */

#define ISM_E_PARAM_COUNT				     0x04U /**<   Defines an error code indicating a count parameter error */

#define ISM_E_PARAM_INVALID				     0x05U /**<   Defines an error code indicating an invalid parameter */

/**
 * @brief PFC Glitch detecte type
 *
 */
typedef enum
{
    FPC_RISING_GLITCH_DETECTED = 0x01U,    /**<  PFC Rising Glitch Detected. */ /**< FPC_RISING_GLITCH_DETECTED */
    FPC_FALLING_GLITCH_DETECTED = 0x02U    /**<  PFC Falling Glitch Detected. *//**< FPC_FALLING_GLITCH_DETECTED */
} FPC_GlitchDetectType;


/**
 * @brief The structure of the ISM processing handle
 *
 */
typedef struct _ISM_HandleType
{
    boolean bEnable;                    /**<  Indicates whether ISM is enabled */
    boolean bIntEnable;                 /**<  Indicates whether interrupts are enabled */
    void(*pEventIsrCalllback)(struct _ISM_HandleType *pHandle, uint16_t u16Lamflags); /**<  Callback function pointer for handling Lam flags interrupts */
    void(*pEcmEventIsrCalllback)(struct _ISM_HandleType *pHandle, uint8_t u8EcmFlags); /**<  Callback function pointer for handling Ecm flags interrupts */

    struct
    {
        uint32_t u32Value;              /**<  Value of the ECM event status */
        uint32_t u32LamChannelRouter;   /**<  Router for LAM channel */
    } tEcmEventStatus[ECM_INSTANCE_COUNT]; /**<  Array of ECM event statuses for routing and storing ECM events */

    struct
    {
        bool bFpcChannelEn;             /**<  Indicates whether the FPC channel is enabled */
        bool bGlitchIntEnable;          /**<  Indicates whether glitch interrupts are enabled */
        ISM_FPC_EdgeDetectModeType eFallingDetectMode; /**<  Falling edge detection mode */
        ISM_FPC_EdgeDelayModeType eFallingDelayNode;   /**<  Falling edge delay node */
        ISM_FPC_EdgeDetectModeType eRisingDetectMode;  /**<  Rising edge detection mode */
        ISM_FPC_EdgeDelayModeType eRisingDelayNode;    /**<  Rising edge delay node */
        uint16_t u32ThresholdValue;     /**<  Threshold value */
        void(*pFpcChannelCalllback)(struct _ISM_HandleType *pHandle, uint32_t u32channel); /**<  Callback function pointer for FPC channels */
    } tIsmFpcChannelStatus[FPC_INSTANCE_COUNT]; /**<  Array of FPC channel statuses for configuring and monitoring FPC functionality */

    struct
    {
        bool bLamChannelEn;             /**<  Indicates whether the LAM channel is enabled */
        bool bOvflIntEnable;            /**<  Indicates whether overflow interrupts are enabled */
        uint8_t u8RcsSel;               /**<  RCS selection */
        uint8_t u8MonSel;               /**<  Monitor selection */
        ISM_LAM_InvertEventWindowType eInvWin; /**<  Event window inversion type */
        ISM_LAM_EventWindowEdgeType eWinEdgSel; /**<  Event window edge selection */
        ISM_LAM_EventWindowSelectType eEvtWinSel; /**<  Event window selection */
        ISM_LAM_RunModeSelectType eRunMode;      /**<  Run mode selection */
        ISM_LAM_MonitorSourceType eMonSrcSel;    /**<  Monitor source selection */
        ISM_LAM_InvertMonitorType eInvMon;       /**<  Monitor inversion type */
        ISM_LAM_InvertReferenceType eInvRef;     /**<  Reference inversion type */
        uint32_t u32EvtCntThreshold;             /**<  Event count threshold */
        void(*pLamChannelOverCalllback)(struct _ISM_HandleType *pHandle, uint32_t u32channel); /**<  Callback function pointer for LAM channels */
    } tIsmLamChannelStatus[LAM_INSTANCE_COUNT]; /**<  Array of LAM channel statuses for configuring and monitoring LAM functionality */
} ISM_HandleType; /**<  Structure defining the ISM handle type */


/**
 * @brief The structure of the ISM Fpc Structure.
 *
 */
typedef struct
{
    uint8_t u8FpcIndex; /**<  FPC index */
    bool bGlitchIntEnable; /**<  Glitch interrupt enable */
    ISM_FPC_EdgeDetectModeType eFallingDetectMode; /**<  Falling edge detection mode */
    ISM_FPC_EdgeDelayModeType eFallingDelayNode; /**<  Falling edge delay node */
    ISM_FPC_EdgeDetectModeType eRisingDetectMode; /**<  Rising edge detection mode */
    ISM_FPC_EdgeDelayModeType eRisingDelayNode; /**<  Rising edge delay node */
    uint16_t u32ThresholdValue; /**<  Threshold value */
    void(*pFpcChannelCalllback)(ISM_HandleType *pHandle, uint32_t u32channel); /**<  FPC channel callback function pointer */
} ISM_FpcCfgType; /**<  Defines the FPC configuration structure type ISM_FpcCfgType */

/**
 * @brief The structure of the ISM Lam Structure.
 *
 */
typedef struct
{
    uint8_t u8LamIndex; /**<  LAM index */
    bool bOvflIntEnable; /**<  Overflow interrupt enable */
    uint8_t u8RcsSel; /**<  RCS selection */
    uint8_t u8MonSel; /**<  Monitor selection */
    ISM_LAM_InvertEventWindowType eInvWin; /**<  Event window inversion type */
    ISM_LAM_EventWindowEdgeType eWinEdgSel; /**<  Window edge selection */
    ISM_LAM_EventWindowSelectType eEvtWinSel; /**<  Event window selection */
    ISM_LAM_RunModeSelectType eRunMode; /**<  Run mode selection */
    ISM_LAM_MonitorSourceType eMonSrcSel; /**<  Monitor source selection */
    ISM_LAM_InvertMonitorType eInvMon; /**<  Monitor inversion type */
    ISM_LAM_InvertReferenceType eInvRef; /**<  Reference inversion type */
    uint32_t u32EvtCntThreshold; /**<  Event count threshold */
    void(*pLamChannelOverCalllback)(ISM_HandleType *pHandle, uint32_t u32channel); /**<  LAM channel overflow callback function pointer */
} ISM_LamCfgType; /**<  Defines the LAM configuration structure type ISM_LamCfgType */


/**
 * @brief The structure of the ISM Init Structure.
 *
 */
typedef struct
{
    bool bIsmEnable; /**<  ISM enable */
    bool bIntEnable; /**<  Interrupt enable */
    void(*pEcmEventIsrCalllback)(ISM_HandleType *pHandle, uint8_t u8EcmFlags); /**<  ECM event ISR callback function pointer */
    void(*pEventIsrCalllback)(ISM_HandleType *pHandle, uint16_t u16Lamflags); /**<  Event ISR callback function pointer */
} ISM_InitCfgType; /**<  Defines the initialization configuration structure type ISM_InitCfgType */

/**
 * @brief Init the ISM.
 *
 * @param pIsmHandle Ism processing handle.
 * @param pInitConfig ISMInstance initial configuration.
 */
void ISM_CommonInit(ISM_HandleType *pIsmHandle,const ISM_InitCfgType *pInitConfig);


/**
 * @brief Config the FPC channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8FpcIndex FPC index.
 * @param pConfig FPC configuration.
 */
void ISM_FpcConfig(ISM_HandleType *pIsmHandle,uint8_t u8FpcIndex, const ISM_FpcCfgType *pConfig);

/**
 * @brief Enable FPC channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8FpcIndex FPC index.
 * @param bEnable Enable value.
 */
void ISM_FpcEnable(ISM_HandleType *pIsmHandle,uint8_t u8FpcIndex, bool bEnable);

/**
 * @brief Config the LAM channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8LamIndex LAM index.
 * @param pConfig LAM configuration.
 */
void ISM_LamConfig(ISM_HandleType *pIsmHandle,uint8_t u8LamIndex, const ISM_LamCfgType *pConfig);


/**
 * @brief Enable LAM Channel.
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8LamIndex LAM index.
 * @param bEnable Enable value.
 */
void ISM_LamEnable(ISM_HandleType *pIsmHandle,uint8_t u8LamIndex, bool bEnable);

/**
 * @brief Enable LAM system event
 *
 * @param pIsmHandle Ism processing handle.
 * @param u8LamIndex Lam channel index.
 * @param u8EcmIndex Ecm channel index.
 * @param u8EventCount Threshold of the ECM channel counter value.
 */
void ISM_EcmEventConfig(ISM_HandleType *pIsmHandle,uint8_t u8LamIndex, uint8_t u8EcmIndex, uint8_t u8EventCount);


/**
 * @brief Gets the channels where ECM events happened.
 * 
 * @return uint8_t A bitmap indicating the channels where ECM events occurred.
 */
uint8_t ISM_GetEcmEventHappenedChannels(void);

/**
 * @brief Gets the channels where LAM events have occurred.
 * 
 * 
 * @return uint16_t A bit field where each bit represents a channel, set if an event has occurred on that channel.
 */
uint16_t ISM_GetLamEventHappenedChannels(void);

/**
 * @brief Clears the bits for ECM event channels.
 * 
 * @param u8Channels The bit field representing the channels to clear, with each bit corresponding to a channel.
 */
void ISM_ClearEcmEventHappenedChannels(uint8_t u8Channels);

/**
 * @brief Clears the bits for LAM event channels.
 * 
 * @param u16Channels The bit field representing the channels to clear, with each bit corresponding to a channel.
 */
void ISM_ClearLamEventHappenedChannels(uint16_t u16Channels);


/**
 * @brief Enables or disables the generation of ECM system events.
 * 
 * @param u32Channels The bit field representing the channels to operate on, with each bit corresponding to a channel.
 * @param bEnable Indicates whether to enable (true) or disable (false) event generation.
 */
void ISM_EnableEcmSystemEvent(uint32_t u32Channels, bool bEnable);

/**
 * @brief Enables or disables the generation of LAM system events.
 *  
 * @param u32Channels The bit field representing the channels to operate on, with each bit corresponding to a channel.
 * @param bEnable Indicates whether to enable (true) or disable (false) event generation.
 */
void ISM_EnableLamSystemEvent(uint32_t u32Channels, bool bEnable);


/**
 * @brief Clears the LAM status counter.
 * 
 * @param u8LamIndex The index of the LAM module to be operated on.
 */
void ISM_ClearLamStatusCounter(uint8_t u8LamIndex);

/**
 * @brief Gets the value of the LAM status counter.
 * 
 * @param u8LamIndex The index of the LAM module to read.
 * @return uint32_t The current value of the LAM status counter.
 */
uint32_t  ISM_GetLamStatusCounter(uint8_t u8LamIndex);

/**
 * @brief Clears the LAM status counter overflow flag.
 * 
 * @param u8LamIndex The index of the LAM module to be operated on.
 */
void ISM_ClearLamStatusOvfl(uint8_t u8LamIndex);

/**
 * @brief Checks if the LAM status counter has overflowed.
 * 
 * @param u8LamIndex The index of the LAM module to check.
 * @return bool True if the status counter has overflowed, false otherwise.
 */
bool ISM_GetLamStatusOvfl(uint8_t u8LamIndex);

/**
 * @param pIsmHandle Ism processing handle.
 * @brief ISM Interrupt Process Function.
 */
void ISMn_IRQHandler(ISM_HandleType *pIsmHandle);

/** @}*/ /* module_driver_ism. */

#endif

#endif
