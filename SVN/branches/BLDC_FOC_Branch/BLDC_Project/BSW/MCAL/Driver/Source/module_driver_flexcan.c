/**
 * @file module_driver_flexcan.h
 * @author Flagchip
 * @brief FLEXCAN driver source code
 * @version 2.0.0
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */

/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip038   N/A          First version
*   2.0.1       2024-09-08    Flagchip038   N/A          Update PNET check process
*   2.0.2       2024-10-20    Flagchip038   N/A          Add FlexCAN Errata 001 fix
*   2.1.0       2024-11-20    Flagchip038   N/A          Add clear flag interrupt macro
*   2.2.0       2025-02-20    Flagchip038   N/A          Fix extended id SRR bit = 0 issue
*********************************************************************************/

#include "module_driver_flexcan.h"    /* include peripheral declarations */

#if FLEXCAN_INSTANCE_COUNT > 0U


/* ################################################################################## */
/* ####################################### Macro #################################### */

#ifndef NULL
    #define NULL ((void *)0)
#endif

#define FLEXCAN_ESR1_ERROR_OK_MASK                     0x40080u





#define USE_CBT_NORMAL



#define TQ_NUM_IPT                  2U

#define TQ_SYNC_NUM                 1U

/* Ctrl1 */
#define TQ_NUM_CTRL1_MAX            25U
#define TQ_NUM_CTRL1_MIN            8U

#define CTRL1_PRESDIV_MAX           256U
#define CTRL1_PRESDIV_MIN           1U

#define CTRL1_RJW_MAX               4U
#define CTRL1_RJW_MIN               1U

#define CTRL1_PROPSEG_MAX           8U
#define CTRL1_PROPSEG_MIN           1U

#define CTRL1_PSEG1_MAX             8U
#define CTRL1_PSEG1_MIN             1U

#define CTRL1_TIMERSEGMENT1_MAX     16U
#define CTRL1_TIMERSEGMENT1_MIN     2U

#define CTRL1_PSEG2_MAX             8U
#define CTRL1_PSEG2_MIN             2U


/* CBT */
#define TQ_NUM_CBT_MAX              25U /* 80U */
#define TQ_NUM_CBT_MIN              8U

#define CBT_PRESDIV_MAX             1024U
#define CBT_PRESDIV_MIN             1U

#define CBT_RJW_MAX                 32U
#define CBT_RJW_MIN                 1U

#define CBT_PROPSEG_MAX             64U
#define CBT_PROPSEG_MIN             1U

#define CBT_PSEG1_MAX               32U
#define CBT_PSEG1_MIN               1U

#define CBT_TIMERSEGMENT1_MAX       96U
#define CBT_TIMERSEGMENT1_MIN       2U

#define CBT_PSEG2_MAX               32U
#define CBT_PSEG2_MIN               2U


/* FDCBT */
#define TQ_NUM_FDCBT_MAX            25U
#define TQ_NUM_FDCBT_MIN            5U

#define FDCBT_PRESDIV_MAX           1024U
#define FDCBT_PRESDIV_MIN           1U

#define FDCBT_RJW_MAX               8U
#define FDCBT_RJW_MIN               1U

#define FDCBT_PROPSEG_MAX           31U
#define FDCBT_PROPSEG_MIN           0U

#define FDCBT_PSEG1_MAX             8U
#define FDCBT_PSEG1_MIN             1U

#define FDCBT_TIMERSEGMENT1_MAX     39U
#define FDCBT_TIMERSEGMENT1_MIN     2U

#define FDCBT_PSEG2_MAX             8U
#define FDCBT_PSEG2_MIN             2U

#define CAN_ONEMB_WORD_NUM             4U /* one MB is 4*4=16bytes */


typedef struct
{
    const uint8  u8RFFN;                    /** CAN2[RFFN] setting value */
    const uint8  u8LegacyFilterNum;         /** Legacy Fifo Filter Elements number, standard occupies 1, extended occupies 2 */
    const uint8  u8MbUsedForLegacyFifo;     /** MB number used for legacy rx fifo and filter elements, RXIMR num same to MB */
} FLEXCAN_LegacyFifoFilterType;

/* ################################################################################## */
/* ############################# Local Const Variables ############################## */

/* CAN Instance */
static FLEXCAN_Type *const  s_aFlexCan_InstanceTable[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_BASE_PTRS;
static const uint8_t  s_aFlexCanFd_SupportTable[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_FD_SUPPORT_PTRS;
static const uint8_t  s_aFlexCanEnhancedElementNums[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_ENHANCED_FIFO_ELEMENT_MAX_PTRS;
static const uint8_t  s_aFlexCanMbNums[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_MB_NUM_PTRS;
static const uint8_t  s_aFlexCanDataLenNums[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_FD_DATALEN_RANGE_NUM_PTRS;
static const uint8_t  s_aFlexCanEnhancedDepthp[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_ENHANCED_FIFO_DEPTH_PTRS;
static const uint8_t  s_aFlexCanGateNumSizes[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_GATE_BUFNUM_PTRS;
static const uint8_t  s_aFlexCanIflagMaskSizes[FLEXCAN_INSTANCE_COUNT] = FLEXCAN_IFLAGMASK_NUM_PTRS;

/* CAN Legacy FIFO Filter check array */
static const FLEXCAN_LegacyFifoFilterType s_aFlexCan_LegacyFilterCheckTable[FLEXCAN_LEGACY_FIFO_NUM_TABLE_LENGTH] = FLEXCAN_LEGACY_FIFO_PTRS;

#ifdef FLEXCAN_ERRATA_TRANSMIT_LIMIT
    #if FLEXCAN_ERRATA_TRANSMIT_LIMIT == STD_ON
        static const uint8_t s_aFlexCan_TransmitLimit_List[FLEXCAN_ERRATA_TRANSMIT_LM_LIST_LEN] = FLEXCAN_ERRATA_TRANSMIT_LM_LIST;
    #endif
#else
#define FLEXCAN_ERRATA_TRANSMIT_LIMIT  STD_OFF
#endif

/* ################################################################################## */
/* ########################### Local Prototype Functions ############################ */




/* ################################################################################## */
/* ########################### Global Prototype Functions ########################### */


/* ################################################################################## */
/* ################################ Local Functions ################################# */


#if FLEXCAN_DEV_ERROR_REPORT == STD_ON
/**
 * @brief Check FLEXCAN instance
 *
 * @param pCanHandle Can Handle point
 * @return FLEXCAN_E_OK is OK
 */
LOCAL_INLINE FLEXCAN_ErrorType FLEXCAN_LL_CheckInstance(FLEXCAN_InstanceType eCanInstance)
{
    FLEXCAN_ErrorType tRetVal;

    if ((uint8_t)eCanInstance < FLEXCAN_INSTANCE_COUNT)
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal = FLEXCAN_E_INVALID_PARAM;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_CHECKINSTANCE, FLEXCAN_E_INVALID_PARAM);
    }

    return tRetVal;
}

#endif


LOCAL_INLINE uint8_t FLEXCAN_LL_CheckContains(const uint8_t *pList, uint8_t u8Len, uint8_t u8Value)
{
    uint8_t u8Index;
    uint8_t u8Retval;

    u8Retval = 0U;
    for(u8Index=0U; u8Index < u8Len; u8Index++)
    {
        if(pList[u8Index] == u8Value)
        {
            u8Retval = 1U;
            break;
        }
    }

    return u8Retval;
}
/**
 * @brief Check FLEXCAN Fd Support instance
 *
 * @param pCanHandle Can Handle point
 * @return FLEXCAN_E_OK is OK
 */
LOCAL_INLINE FLEXCAN_ErrorType FLEXCAN_LL_CheckFdInstance(uint8_t u8CanIndex)
{
    FLEXCAN_ErrorType tRetVal;

    if (s_aFlexCanFd_SupportTable[u8CanIndex])
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal = FLEXCAN_E_INVALID_PARAM;
    }

    return tRetVal;
}

#if FLEXCAN_DEV_ERROR_REPORT == STD_ON
/**
 * @brief Check Legency Fifo Num
 *
 * @param u32RxFilterCnt Legency fifo num
 * @return FLEXCAN_E_OK is OK
 */
LOCAL_INLINE FLEXCAN_ErrorType FLEXCAN_LL_CheckLengcyFifoNum(uint32_t u32RxFilterCnt)
{
    FLEXCAN_ErrorType tRetVal;

    if (u32RxFilterCnt % 8 == 0)
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal = FLEXCAN_E_INVALID_PARAM;
    }

    return tRetVal;
}
#endif



LOCAL_INLINE uint8_t FLEXCAN_LL_GetMbNum(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg)
{
    uint8_t u8Num;
    if(pInitCfg->bEnFd)
    {
        u8Num = (uint8_t)(s_aFlexCanMbNums[pCanHandle->eInstance]/s_aFlexCanIflagMaskSizes[pCanHandle->eInstance]*16U/(pInitCfg->tMbCfg.aDataWidthRange[0]+8U));
#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
        if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
        {
            u8Num = (uint8_t)(u8Num + s_aFlexCanMbNums[pCanHandle->eInstance]/s_aFlexCanIflagMaskSizes[pCanHandle->eInstance]*16U/(pInitCfg->tMbCfg.aDataWidthRange[1]+8U));
        }
#elif FLEXCAN_IFLAGMASK_NUM_MAX > 2U
        if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
        {
            u8Num = (uint8_t)(u8Num + s_aFlexCanMbNums[pCanHandle->eInstance]/s_aFlexCanIflagMaskSizes[pCanHandle->eInstance]*16U/(pInitCfg->tMbCfg.aDataWidthRange[2]+8U));
        }
#endif
    }
    else
    {
        u8Num = s_aFlexCanMbNums[pCanHandle->eInstance];
    }
    return u8Num;
}

#if 0
LOCAL_INLINE void FLEXCAN_LL_SetMbMask(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg)
{
    uint8_t  u8Index;
    uint8_t  u8MbCnt;
    u8Index = 0U;
    u8MbCnt = pInitCfg->tMbCfg.u8MBCnt;
    pCanHandle->tStatus.aTxInterruptMask[0] = 0U;
    for(u8Index=0U;u8Index<u8MbCnt;u8Index++)
    {
        if(pInitCfg->tMbCfg.pMBList[u8Index].bEnMBInt)
        {
            if(u8Index<32U)
            {
                pCanHandle->tStatus.aTxInterruptMask[0] = (pCanHandle->tStatus.aTxInterruptMask[0] << u8Index) | pCanHandle->tStatus.aTxInterruptMask[0];
                pCanHandle->tStatus.aInterruptMask[0] = (pCanHandle->tStatus.aInterruptMask[0] << u8Index) | pCanHandle->tStatus.aInterruptMask[0];
            }
            #if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
            else if(u8Index<64U)
            {
                if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
                {
                    pCanHandle->tStatus.aTxInterruptMask[1] = (pCanHandle->tStatus.aTxInterruptMask[1] << u8Index) | pCanHandle->tStatus.aTxInterruptMask[1];
                    pCanHandle->tStatus.aInterruptMask[1] = (pCanHandle->tStatus.aInterruptMask[1] << u8Index) | pCanHandle->tStatus.aInterruptMask[1];
                }
            }
            #elif FLEXCAN_IFLAGMASK_NUM_MAX > 2U
            else if(u8Index<96U)
            {
                if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
                {
                    pCanHandle->tStatus.aTxInterruptMask[2] = (pCanHandle->tStatus.aTxInterruptMask[2] << u8Index) | pCanHandle->tStatus.aTxInterruptMask[2];
                    pCanHandle->tStatus.aInterruptMask[2] = (pCanHandle->tStatus.aInterruptMask[2] << u8Index) | pCanHandle->tStatus.aInterruptMask[2];
                }
            }
            #endif
        }
        else
        {
            if(u8Index<32U)
            {
                pCanHandle->tStatus.aTxPollingMask[0] = (pCanHandle->tStatus.aTxPollingMask[0] << u8Index) | pCanHandle->tStatus.aTxPollingMask[0];
                pCanHandle->tStatus.aPollingMask[0] = (pCanHandle->tStatus.aPollingMask[0] << u8Index) | pCanHandle->tStatus.aPollingMask[0];
            }
            #if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
            else if(u8Index<64U)
            {
                if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
                {
                    pCanHandle->tStatus.aTxPollingMask[1] = (pCanHandle->tStatus.aTxPollingMask[1] << u8Index) | pCanHandle->tStatus.aTxPollingMask[1];
                    pCanHandle->tStatus.aPollingMask[1] = (pCanHandle->tStatus.aPollingMask[1] << u8Index) | pCanHandle->tStatus.aPollingMask[1];
                }
            }
            #elif FLEXCAN_IFLAGMASK_NUM_MAX > 2U
            else if(u8Index<96U)
            {
                if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
                {
                    pCanHandle->tStatus.aTxPollingMask[2] = (pCanHandle->tStatus.aTxPollingMask[2] << u8Index) | pCanHandle->tStatus.aTxPollingMask[2];
                    pCanHandle->tStatus.aPollingMask[2] = (pCanHandle->tStatus.aPollingMask[2] << u8Index) | pCanHandle->tStatus.aPollingMask[2];
                }
            }
            #endif
        }
    }

}
#endif

LOCAL_INLINE uint8_t FLEXCAN_LL_GetMbIndexByTxHandle(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle)
{
    uint32_t u32Mask;
    uint8_t  u8Index;
    uint8_t  u8MbIndex;
    uint8_t  u8Find;
    u8Find = 0U;

    u8MbIndex = 0U;
    u8Index = 0U;

    u32Mask = pCanHandle->tStatus.aTxInterruptMask[0]|pCanHandle->tStatus.aTxPollingMask[0];

    while(u32Mask)
    {
        if((u32Mask & 0x01U) == 0x01U)
        {
            if(u8Index==u8TxHandle)
            {
                u8Find = 1U;
                break;
            }
            u8Index++;
        }
        u32Mask = (uint32_t)(u32Mask >> 1U);
        u8MbIndex++;
    }
#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
    {
        if(u8Find==0U)
        {
            u32Mask = pCanHandle->tStatus.aTxInterruptMask[1]|pCanHandle->tStatus.aTxPollingMask[1];

            while(u32Mask)
            {
                if((u32Mask&0x01U)==0x01U)
                {
                    if(u8Index==u8TxHandle)
                    {
                        u8Find = 1U;
                        break;
                    }
                    u8Index++;
                }
                u32Mask = (uint32_t)(u32Mask >> 1U);
                u8MbIndex++;
            }
        }
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
    {
        if(u8Find==0U)
        {
            u32Mask = pCanHandle->tStatus.aTxInterruptMask[1]|pCanHandle->tStatus.aTxPollingMask[1];

            while(u32Mask)
            {
                if((u32Mask&0x01U)==0x01U)
                {
                    if(u8Index==u8TxHandle)
                    {
                        u8Find = 1U;
                        break;
                    }
                    u8Index++;
                }
                u32Mask = (uint32_t)(u32Mask >> 1U);
                u8MbIndex++;
            }
        }
    }
#endif

    if(u8Find==0U)
    {
        u8MbIndex = 0xFFU;
    }

    return u8MbIndex;
}

LOCAL_INLINE uint8_t FLEXCAN_LL_GetTxHandleByMbIndex(FLEXCAN_HandleType *pCanHandle, uint8_t u8MbIndex)
{
    uint32_t u32Mask;
    uint8_t  u8Index;
    uint8_t  u8TxHandle;
    uint8_t  u8Find;

    u8Find = 0U;
    u8Index = 0U;
    u8TxHandle = 0U;

    u32Mask = pCanHandle->tStatus.aTxInterruptMask[0] | pCanHandle->tStatus.aTxPollingMask[0];

    while(u32Mask)
    {
        if((u32Mask & 0x01U) == 0x01U)
        {
            if(u8Index==u8MbIndex)
            {
                u8Find = 1U;
                break;
            }
            u8TxHandle++;
        }
        u32Mask = (uint32_t)(u32Mask >> 1U);
        u8Index++;
    }

#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
    {
        if(u8Find==0U)
        {
            u32Mask = pCanHandle->tStatus.aTxInterruptMask[1] | pCanHandle->tStatus.aTxPollingMask[1];

            while(u32Mask)
            {
                if((u32Mask & 0x01U) == 0x01U)
                {
                    if(u8Index==u8MbIndex)
                    {
                        u8Find = 1U;
                        break;
                    }
                    u8TxHandle++;
                }
                u32Mask = (uint32_t)(u32Mask >> 1U);
                u8Index++;
            }
        }
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
    {
        if(u8Find==0U)
        {
            u32Mask = pCanHandle->tStatus.aTxInterruptMask[1] | pCanHandle->tStatus.aTxPollingMask[1];

            while(u32Mask)
            {
                if((u32Mask & 0x01U) == 0x01U)
                {
                    if(u8Index==u8MbIndex)
                    {
                        u8Find = 1U;
                        break;
                    }
                    u8TxHandle++;
                }
                u32Mask = (uint32_t)(u32Mask >> 1U);
                u8Index++;
            }
        }
    }
#endif

    if(u8Find==0U)
    {
        u8TxHandle = 0xFFU;
    }

    return u8TxHandle;
}


LOCAL_INLINE uint8_t FLEXCAN_LL_GetRxHandleByMbIndex(FLEXCAN_HandleType *pCanHandle, uint8_t u8MbIndex)
{
    uint32_t u32Mask;
    uint8_t  u8Index;
    uint8_t  u8RxHandle;
    uint8_t  u8Find;
    u8Find = 0U;

    u8Index = 0U;
    u8RxHandle = 0U;

    u32Mask = pCanHandle->tStatus.aRxInterruptMask[0] | pCanHandle->tStatus.aRxPollingMask[0];

    while(u32Mask)
    {
        if((u32Mask & 0x01U) == 0x01U)
        {
            if(u8Index==u8MbIndex)
            {
                u8Find = 1U;
                break;
            }
            u8RxHandle++;
        }
        u32Mask = (uint32_t)(u32Mask >> 1U);
        u8Index++;
    }

#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
    {
        if(u8Find==0U)
        {
            u32Mask = pCanHandle->tStatus.aRxInterruptMask[1] | pCanHandle->tStatus.aRxPollingMask[1];

            while(u32Mask)
            {
                if((u32Mask & 0x01U) == 0x01U)
                {
                    if(u8Index==u8MbIndex)
                    {
                        u8Find = 1U;
                        break;
                    }
                    u8RxHandle++;
                }
                u32Mask = (uint32_t)(u32Mask >> 1U);
                u8Index++;
            }
        }
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
    {
        if(u8Find==0U)
        {
            u32Mask = pCanHandle->tStatus.aRxInterruptMask[1] | pCanHandle->tStatus.aRxPollingMask[1];

            while(u32Mask)
            {
                if((u32Mask & 0x01U) == 0x01U)
                {
                    if(u8Index==u8MbIndex)
                    {
                        u8Find = 1U;
                        break;
                    }
                    u8RxHandle++;
                }
                u32Mask = (uint32_t)(u32Mask >> 1U);
                u8Index++;
            }
        }
    }
#endif

    if(u8Find==0U)
    {
        u8RxHandle = 0xFFU;
    }

    return u8RxHandle;
}

/**
 * @brief Initial embedded can ram area
 *
 * @param u8CanIndex CanIndex, Must less than FLEXCAN_INSTANCE_COUNT
 */
static void FLEXCAN_LL_EmbededRam_Init(FLEXCAN_InstanceType eInstance)
{
    volatile uint32_t u32Index ;
    volatile uint32_t ramAddr;
    FLEXCAN_Type *pCan;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[(uint8_t)eInstance];

    for (u32Index = 0U; u32Index < s_aFlexCanMbNums[eInstance]*4U; u32Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_MB_RAM_OFFSET, u32Index * 4U);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u32Index = 0U; u32Index < s_aFlexCanMbNums[eInstance]; u32Index++)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_RXIMR_OFFSET, u32Index * 4U);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u32Index = 0U; u32Index < FLEXCAN_RXFIR_TEST_LEN; u32Index+=4U)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_RXFIR_TEST_OFFSET, u32Index);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u32Index = 0U; u32Index < FLEXCAN_MASK_LEN; u32Index+=4U)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_MASK_OFFSET, u32Index);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u32Index = 0U; u32Index < FLEXCAN_SMBTX_LEN; u32Index+=4U)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_SMBTX_OFFSET, u32Index);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u32Index = 0U; u32Index < FLEXCAN_SMBRX0_LEN; u32Index+=4U)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_SMBRX0_OFFSET, u32Index);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    for (u32Index = 0U; u32Index < FLEXCAN_SMBRX1_LEN; u32Index+=4U)
    {
        ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_SMBRX1_OFFSET, u32Index);
        FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
    }

    /* only can fd support these memory */
    if(s_aFlexCanFd_SupportTable[eInstance])
    {
        for (u32Index = 0U; u32Index < FLEXCAN_FD_SMBTX_LEN; u32Index+=4U)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_FD_SMBTX_OFFSET, u32Index);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }

        for (u32Index = 0U; u32Index < FLEXCAN_FD_SMBRX0_LEN; u32Index+=4U)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_FD_SMBRX0_OFFSET, u32Index);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }

        for (u32Index = 0U; u32Index < FLEXCAN_FD_SMBRX1_LEN; u32Index+=4U)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_FD_SMBRX1_OFFSET, u32Index);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }
    }

    /* only enhanced rx fifo support these memory */
    if(s_aFlexCanEnhancedDepthp[eInstance])
    {
        if(s_aFlexCanFd_SupportTable[eInstance])
        {
            /** initial rx fifo with fd */
            for (u32Index = 0U; u32Index < s_aFlexCanEnhancedDepthp[eInstance]*4U*FLEXCAN_ERX_FIFO_FD_WIDTH; u32Index+=4U)
            {
                ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_ERX_FIFO_OFFSET, u32Index );
                FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
            }
        }
        else
        {
            /** initial rx fifo non-fd */
            for (u32Index = 0U; u32Index < s_aFlexCanEnhancedDepthp[eInstance]*4U*FLEXCAN_ERX_FIFO_NONFD_WIDTH; u32Index+=4U)
            {
                ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_ERX_FIFO_OFFSET, u32Index );
                FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
            }
        }

        /* enhanced fifo elements */
        for (u32Index = 0U; u32Index < s_aFlexCanEnhancedElementNums[eInstance]; u32Index++)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_ERFFEL_OFFSET, u32Index * 4U);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }
    }

    /* gate buffer */
    if(s_aFlexCanGateNumSizes[eInstance])
    {
        for (u32Index = 0U; u32Index < s_aFlexCanGateNumSizes[eInstance]*2U; u32Index++)
        {
            ramAddr = FLEXCAN_REGISTER_WITHOFFSET(pCan, FLEXCAN_GATEBUF_OFFSET, u32Index * 4U);
            FLEXCAN_REG32_CONTENT(ramAddr) = 0U;
        }
    }
}



/**
 * @brief This Function is used to receive Special Message Buffer data
 *
 * @param pCanHandle Can Handle point
 * @param u8RealMbIndex, message buffer index 0...31, if fifo enable, always 0
 */
static void FLEXCAN_LL_ReceiveMb(FLEXCAN_HandleType *pCanHandle, uint8_t u8RealMbIndex)
{
    FLEXCAN_Type *pCan;

    uint32_t     *pSrc;
    uint32_t     *pDest;
    uint8_t      u8Index;

    uint32_t     u32TempAddr;
    uint32_t     u32WordLen;
    uint8_t      u8DateLen;

    u8DateLen = FLEXCAN_MB_GET_DATALEN(u8RealMbIndex, s_aFlexCanMbNums[pCanHandle->eInstance],s_aFlexCanDataLenNums[pCanHandle->eInstance], pCanHandle->tStatus.aMbDataWidth);

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

    pCanHandle->tSettings.pRxBuf->u8CanIndex = pCanHandle->eInstance;
    pCanHandle->tSettings.pRxBuf->u8RxHandle = u8RealMbIndex;


    /* message buffer 1th word */
    u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RealMbIndex, u8DateLen, 0U);

    pCanHandle->tSettings.pRxBuf->bEnFd = (uint8_t)((FLEXCAN_MB_EDL_GET(u32TempAddr) == 0U) ? 0U : 1U);
    pCanHandle->tSettings.pRxBuf->bEnBrs = (uint8_t)((FLEXCAN_MB_BRS_GET(u32TempAddr) == 0U) ? 0U : 1U);


    pCanHandle->tSettings.pRxBuf->u32DataLen = FLEXCAN_MB_DLC_GET(u32TempAddr);
    pCanHandle->tSettings.pRxBuf->u32DataLen = FLEXCAN_DlcToDataLen(pCanHandle->tSettings.pRxBuf->u32DataLen);
    pCanHandle->tSettings.pRxBuf->eFrameType = (FLEXCAN_IdType)(FLEXCAN_MB_IDE_GET(u32TempAddr));

    /* message buffer 2th word */
    u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RealMbIndex, u8DateLen, 4U);

    if (pCanHandle->tSettings.pRxBuf->eFrameType)
    {
        pCanHandle->tSettings.pRxBuf->u32CanId = FLEXCAN_MB_EXTID_GET(u32TempAddr);
    }
    else
    {
        pCanHandle->tSettings.pRxBuf->u32CanId = FLEXCAN_MB_STDID_GET(u32TempAddr);
    }



    pDest = (uint32_t *)pCanHandle->tSettings.pRxBuf->aData;
    /* message buffer 3th word */
    pSrc = (uint32_t *)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RealMbIndex, u8DateLen, 8U);


    u32WordLen = pCanHandle->tSettings.pRxBuf->u32DataLen / 4U + (pCanHandle->tSettings.pRxBuf->u32DataLen % 4U > 0U ? 1U : 0U);

    for (u8Index = 0U; u8Index < u32WordLen; u8Index++)
    {
        /* big endian to little endian */
        REV_BYTES_32(pSrc[u8Index], pDest[u8Index]);
    }

    (void)pCan->TIMER;     /* Read TIMER to unlock message buffers */
}


/**
 * @brief This Function is used to receive Enhance FIFO Buffer data
 *
 * @param pCanHandle Can handle point
 */
static void FLEXCAN_LL_ReceiveEnhanceFifo(FLEXCAN_HandleType *pCanHandle)
{
    volatile uint32_t       *pSrc;
    volatile uint32_t       *pDest;
    uint8_t                 u8Index;
    FLEXCAN_Type            *pCan;


    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

    pCanHandle->tSettings.pRxBuf->u8CanIndex = pCanHandle->eInstance;

    pCanHandle->tSettings.pRxBuf->bEnFd = (uint8_t)(FLEXCAN_EFIFOMB_EDL_GET());
    pCanHandle->tSettings.pRxBuf->bEnBrs = (uint8_t)(FLEXCAN_EFIFOMB_BRS_GET());

    pCanHandle->tSettings.pRxBuf->u32DataLen = FLEXCAN_EFIFOMB_DLC_GET();
    pCanHandle->tSettings.pRxBuf->u32DataLen = (uint8_t)(FLEXCAN_DlcToDataLen(pCanHandle->tSettings.pRxBuf->u32DataLen));
    pCanHandle->tSettings.pRxBuf->eFrameType = (FLEXCAN_IdType)(FLEXCAN_EFIFOMB_IDE_GET());

    if (pCanHandle->tSettings.pRxBuf->eFrameType)
    {
        pCanHandle->tSettings.pRxBuf->u32CanId = FLEXCAN_EFIFOMB_EXTID_GET();
    }
    else
    {
        pCanHandle->tSettings.pRxBuf->u32CanId = FLEXCAN_EFIFOMB_STDID_GET();
    }

    pDest = (uint32_t *)pCanHandle->tSettings.pRxBuf->aData;
    /* message buffer 3th word */
    pSrc = (volatile uint32_t *)FLEXCAN_EFIFOMB_DATAADDR_GET(0U);


    //u32WordLen = pCanHandle->tStatus1.pRxBuf->u32DataLen / 4U + (pCanHandle->tStatus1.pRxBuf->u32DataLen % 4U > 0U ? 1U : 0U);

    for (u8Index = 0U; u8Index < 18U; u8Index++)
    {
        /* big endian to little endian */
        REV_BYTES_32(pSrc[u8Index], pDest[u8Index]);
    }

    //u32WordLen = FLEXCAN_EFIFOMB_HRTIMESTAMP_GET(u32WordLen);             /* Read TIMER to unlock message buffers */

    /* clear fifo data available status */
    FLEXCAN_HWA_ERFSRClearEnhancedFifoFlag(pCan, (FLEXCAN_ERFSR_ERFDA_MASK | FLEXCAN_ERFSR_ERFWMI_MASK));

}


/**
 * @brief Polling Legacy Rx FIFO data
 *
 * @param pCanHandle Can handle point
 */
static void FLEXCAN_LL_PollingLegacyFifoData(FLEXCAN_HandleType *pCanHandle)
{
    uint32_t          u32Status;
    FLEXCAN_Type      *pCan;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

    /* IFLAG1[BIT5] (Frames available in Rx FIFO) is asserted when there is at least one frame available to be read from the FIFO. */
    u32Status = FLEXCAN_HWA_CheckLegacyFifoData(pCan);

    while (u32Status != 0U)
    {
        FLEXCAN_LL_ReceiveMb(pCanHandle, 0);

        FLEXCAN_HWA_UnlockMbNoFifoFlag(pCan, (uint32_t)5);

        pCanHandle->tSettings.pRxBuf->u8RxHandle = 0xFFU;
#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
        u32Status = FLEXCAN_HWA_GetFlag1NoFifoFlag(pCan, 5);
        pCanHandle->tSettings.pRxNotify(pCanHandle, pCanHandle->tSettings.pRxBuf);
#else
        pCanHandle->tSettings.pRxNotify(pCanHandle, pCanHandle->tSettings.pRxBuf);
        u32Status = FLEXCAN_HWA_GetFlag1NoFifoFlag(pCan, 5);
#endif
    }
}


/**
 * @brief Polling Legacy Rx FIFO warning notification
 *
 * @param pCanHandle Can handle point
 */
static void FLEXCAN_LL_PollingLegacyFifoWarning(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_Type      *pCan;
    FLEXCAN_FifoIssueType tFifoIssue;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

    if (FLEXCAN_HWA_CheckLegacyFifoWarning(pCan) != 0U)
    {
        tFifoIssue.eFifoType = FLEXCAN_LEGACY_FIFO;
        tFifoIssue.u8FifoWarings = 1U;
        tFifoIssue.u8FifoUnderflow = 0U;
        tFifoIssue.u8FifoOverflow = 0U;
#if FLEXCAN_ERROR_FLAG_CLEAR_FIRST == STD_ON
        FLEXCAN_HWA_ClearIFLAG1FifoWarningFlag(pCan);
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
#else
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
        FLEXCAN_HWA_ClearIFLAG1FifoWarningFlag(pCan);
#endif
    }
}


/**
 * @brief Polling Legacy Rx FIFO warning notification
 *
 * @param pCanHandle Can handle point
 */
static void FLEXCAN_LL_PollingLegacyFifoError(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_Type      *pCan;
    FLEXCAN_FifoIssueType tFifoIssue;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

    if (FLEXCAN_HWA_CheckLegacyFifoDataLost(pCan) != 0U)
    {
        tFifoIssue.eFifoType = FLEXCAN_LEGACY_FIFO;
        tFifoIssue.u8FifoWarings = 0U;
        tFifoIssue.u8FifoUnderflow = 0U;
        tFifoIssue.u8FifoOverflow = 1U;
#if FLEXCAN_ERROR_FLAG_CLEAR_FIRST == STD_ON
        FLEXCAN_HWA_ClearIFLAG1FifoErrorFlag(pCan);
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
#else
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
        FLEXCAN_HWA_ClearIFLAG1FifoErrorFlag(pCan);
#endif
    }
}


/**
 * @brief Polling Enhanced Rx FIFO Data
 *
 * @param pCanHandle Can handle point
 */
static void FLEXCAN_LL_PollingEnhancedFifoData(FLEXCAN_HandleType *pCanHandle)
{
    uint32_t                u32Status;
    FLEXCAN_Type            *pCan;
    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
    u32Status = FLEXCAN_HWA_ERFSRGetDataValid(pCan);
    while (u32Status != 0U)
    {
        FLEXCAN_LL_ReceiveEnhanceFifo(pCanHandle);

        pCanHandle->tSettings.pRxBuf->u8RxHandle = 0xFFU;

#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
        /* check fd fifo data available */
        u32Status = FLEXCAN_HWA_ERFSRGetDataValid(pCan);
        pCanHandle->tSettings.pRxNotify(pCanHandle, pCanHandle->tSettings.pRxBuf);
#else
        pCanHandle->tSettings.pRxNotify(pCanHandle, pCanHandle->tSettings.pRxBuf);
        /* check fd fifo data available */
        u32Status = FLEXCAN_HWA_ERFSRGetDataValid(pCan);
#endif
    }

}


/**
 * @brief Polling Enhanced Rx FIFO error
 *
 * @param pCanHandle Can handle point
 */
static void FLEXCAN_LL_PollingEnhancedFifoError(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_Type            *pCan;
    FLEXCAN_FifoIssueType tFifoIssue;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

    tFifoIssue.eFifoType = FLEXCAN_ENHANCED_FIFO;
    tFifoIssue.u8FifoWarings = 0U;
    if (FLEXCAN_HWA_ERFSRGetUnderflow(pCan) != 0U)
    {
        tFifoIssue.u8FifoUnderflow = 1U;
    }
    else
    {
        tFifoIssue.u8FifoUnderflow = 0U;
    }

    if (FLEXCAN_HWA_ERFSRGetOverflow(pCan) != 0U)
    {
        tFifoIssue.u8FifoOverflow = 1U;
    }
    else
    {
        tFifoIssue.u8FifoOverflow = 0U;
    }

#if FLEXCAN_ERROR_FLAG_CLEAR_FIRST == STD_ON
    if(tFifoIssue.u8FifoUnderflow)
    {
        FLEXCAN_HWA_ERFSRClrUnderflow(pCan); /* clear underflow */
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
    }
    if(tFifoIssue.u8FifoOverflow)
    {
        FLEXCAN_HWA_ERFSRClrOverflow(pCan); /* clean overflow */
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
    }
#else
    if(tFifoIssue.u8FifoUnderflow)
    {
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
        FLEXCAN_HWA_ERFSRClrUnderflow(pCan); /* clear underflow */
    }
    if(tFifoIssue.u8FifoOverflow)
    {
        pCanHandle->tSettings.pFifoIssueNotify(pCanHandle, &tFifoIssue);
        FLEXCAN_HWA_ERFSRClrOverflow(pCan); /* clean overflow */
    }
#endif
}

/**
 * @brief Set Legacy Rx FIFO
 *
 * @param pCanHandle Can handle point
 * @param pRxFilterList Filter id list
 * @param u32RxFilterCnt Filter id list length
 * @return FLEXCAN_E_OK is ok
 */
static FLEXCAN_ErrorType FLEXCAN_LL_SetLegacyFifo(FLEXCAN_HandleType *pCanHandle, FLEXCAN_FifoFilterType *pRxFilterList, uint32_t u32RxFilterCnt)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t          u32Index;
    FLEXCAN_Type     *pCan;
    uint32_t         u32ElementNum;
    const FLEXCAN_LegacyFifoFilterType *pLegacyFilter = NULL;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif
        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
        tRetVal = FLEXCAN_LL_CheckLengcyFifoNum(u32RxFilterCnt);

        if (tRetVal == FLEXCAN_E_OK)
        {
        #else
        tRetVal = FLEXCAN_E_OK;
        #endif

            pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
            pCanHandle->tStatus.u8MbStart = 0U;

            /* set legacy fifo */
            FLEXCAN_HWA_EnableLegacyFifo(pCan);

            #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
            /* filter element number must be multi of 8 */
            if ((u32RxFilterCnt % 8U) || (u32RxFilterCnt > FLEXCAN_LEGACY_FIFO_ELEMENT_MAX))
            {
                FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_PARAM);
            }
            #endif

            for (u32Index = 0U; u32Index < sizeof(s_aFlexCan_LegacyFilterCheckTable)/sizeof(s_aFlexCan_LegacyFilterCheckTable[0]); u32Index++)
            {
                if (s_aFlexCan_LegacyFilterCheckTable[u32Index].u8LegacyFilterNum == u32RxFilterCnt)
                {
                    pLegacyFilter = &s_aFlexCan_LegacyFilterCheckTable[u32Index];

                    break;
                }
            }

            if(pLegacyFilter==NULL)
            {
                tRetVal |= FLEXCAN_E_NULL_POINT;
            }
            else
            {

                /*           31   30      29  28  27  26  25  24       23  22  21  20  19  18  17  16          15  14  13  12  11  10  9   8          7   6   5   4   3   2   1   0        */
                /* Format A: RTR  IDE |                                  RXIDA (standard =29-19, extended = 29-1)                                                               |          */
                /* Format B: RTR  IDE |   RXIDB_0 (standart = 29-19, extended = 29-16) MSB compare          |  RTR IDE|RXIDB_1 (standart = 13-3, extended = 13-0) MSB compare              */
                /* Format C: RXIDC_0 (std/ext = 31-24) MSB compare |  RXIDC_1 (std/ext = 23-16) MSB compare |  RXIDC_2 (std/ext =15-8) MSB compare  |  RXIDC_3 (std/ext =7-0) MSB compare  */

                /* always format A */

                u32ElementNum = 0U;
                for (u32Index = 0U; u32Index < u32RxFilterCnt; u32Index++)
                {
                    /* extended id */
                    if (pRxFilterList[u32Index].eRxFrameType == FLEXCAN_ID_EXT)
                    {
                        FLEXCAN_HWA_MbRam(pCan, CAN_ONEMB_WORD_NUM * FLEXCAN_LEGACY_FIFO_FILTER_START + u32Index, (1U << 30) | (pRxFilterList[u32Index].u32RxCanId << 1)); /* id */
                        if (u32Index < pLegacyFilter->u8MbUsedForLegacyFifo)
                        {
                            FLEXCAN_HWA_SetIndividualMask(pCan, u32Index, (1U << 30) | (pRxFilterList[u32Index].u32RxCanIdMask << 1)); /* mask */
                        }
                        else  /* left used global rx fifo mask */
                        {
                            FLEXCAN_HWA_SetFifoGlobalMask(pCan, (1U << 30) | (pRxFilterList[u32Index].u32RxCanIdMask << 1));
                        }

                        u32ElementNum += 2U;
                    }
                    else /* standard id */
                    {
                        FLEXCAN_HWA_MbRam(pCan, CAN_ONEMB_WORD_NUM * FLEXCAN_LEGACY_FIFO_FILTER_START + u32Index, pRxFilterList[u32Index].u32RxCanId << 19); /* id */
                        if (u32Index < pLegacyFilter->u8MbUsedForLegacyFifo)
                        {
                            FLEXCAN_HWA_SetIndividualMask(pCan, u32Index,  pRxFilterList[u32Index].u32RxCanIdMask << 19); /* mask */
                        }
                        else  /* left used global rx fifo mask */
                        {
                            FLEXCAN_HWA_SetFifoGlobalMask(pCan, pRxFilterList[u32Index].u32RxCanIdMask << 19);
                        }
                        u32ElementNum++;
                    }
                }

                if(u32ElementNum > FLEXCAN_LEGACY_FIFO_ELEMENT_MAX)
                {
                    tRetVal |= FLEXCAN_E_INVALID_PARAM;
                }
                else
                {
                    /* set fifo filter num */
                    FLEXCAN_HWA_SetLegacyFifoFilterNum(pCan, pLegacyFilter->u8RFFN);

                    /* insert rx filter before tx message buffer, every group filter contains 8 elements(2MBs), at least 2 groups */
                    pCanHandle->tStatus.u8MbStart = pLegacyFilter->u8MbUsedForLegacyFifo;

                }

            }


            #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
        }
            #endif
        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
        #endif

    return tRetVal;
}

/**
 * @brief Set Enhanced Rx FIFO
 *
 * @param pCanHandle Can Handle point
 * @param pRxFilterList Filter id list
 * @param u32RxFilterCnt Filter id list length
 * @param u8WaterMark DMA Wartmark
 * @return FLEXCAN_E_OK is ok
 */
static FLEXCAN_ErrorType FLEXCAN_LL_SetEnhancedFifo(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t          u32FilterNum;
    uint32_t          u32Index;
    FLEXCAN_Type     *pCan;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    tRetVal = FLEXCAN_LL_CheckFdInstance(pCanHandle->eInstance);

    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif

        uint32_t    u32ExtIDFilterNum;
        uint32_t    u32StdIDFilterNum;
        uint32_t    u32TempERFCR;

        /* current pCan instance */
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

        /* Configure the filter elements by writing in the ERFFELn registers (ERFFELn registers are implemented in RAM; thus, they must be explicitly initialized prior to any reception). */

        /* standard id filter */
        /* 31-30     29-28     27           26-16           15-12      11           10-0                                           */
        /* FSCH=b00  Reserved  RTR filter   STD ID filter   Reserved   RTR mask     STD ID mask       id_filter&id_mask            */
        /* FSCH=b01  Reserved  RTR filter   STD ID filter2  Reserved   RTR mask     STD ID filter1    id filter1<=id<= id filter2  */
        /* FSCH=b10  Reserved  RTR filter2  STD ID filter2  Reserved   RTR filter1  STD ID filter1    id filter1= id = id filter2  */

        /* extended id filter */
        /* 31-30      29           28-0             */
        /* FSCH=00b   RTR filter   EXT ID filter    */
        /* Reserved   RTR mask     EXT ID mask      */
        /* FSCH=01b   RTR filter   EXT ID filter2   */
        /* Reserved   RTR mask     EXT ID filter1   */
        /* FSCH=10b   RTR filter2  EXT ID filter2   */
        /* Reserved   RTR filter1  EXT ID filter1   */

        u32ExtIDFilterNum = 0U;
        u32StdIDFilterNum = 0U;

        /* set extended id mask first */
        for (u32Index = 0U; u32Index < pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt; u32Index++)
        {

            if (pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList[u32Index].eRxFrameType == FLEXCAN_ID_EXT)
            {
                /* extended id first */
                /* pCan->ERFFEL[u32Index] &= 0xFFFFFFFU; */
                FLEXCAN_HWA_EnhancedFifoFilter(pCan, u32ExtIDFilterNum * 2U, pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList[u32Index].u32RxCanId);    /* id   */
                FLEXCAN_HWA_EnhancedFifoFilter(pCan, u32ExtIDFilterNum * 2U + 1U, pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList[u32Index].u32RxCanIdMask); /* mask */

                u32ExtIDFilterNum++;
            }
        }

        /* set standard id mask */
        for (u32Index = 0U; u32Index < pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt; u32Index++)
        {
            /* standard id */
            if (pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList[u32Index].eRxFrameType == FLEXCAN_ID_STD)
            {
                FLEXCAN_HWA_EnhancedFifoFilter(pCan, u32ExtIDFilterNum * 2U + u32StdIDFilterNum,
                                               (pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList[u32Index].u32RxCanId << 16) | pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList[u32Index].u32RxCanIdMask);
                u32StdIDFilterNum++;
            }
        }


        /* standard id number must multiple of 2 */
        tRetVal = (FLEXCAN_ErrorType)(tRetVal | ((u32StdIDFilterNum % 2U == 1U) ? FLEXCAN_E_INVALID_PARAM : FLEXCAN_E_OK));

        if (tRetVal == FLEXCAN_E_OK)
        {
            /* total id filter number */
            u32FilterNum = u32ExtIDFilterNum*2 + u32StdIDFilterNum;

            if(u32FilterNum > s_aFlexCanEnhancedElementNums[pCanHandle->eInstance])
            {
                tRetVal |= FLEXCAN_E_INVALID_PARAM;
            }
            else
            {

                /* Write one to ERFSR[ERFCLR] to reset Enhanced Rx FIFO engine */
                FLEXCAN_HWA_ERFSRResetEnhancedFifo(pCan);
                /* Clear EFRSR[ERFUFW], EFRSR[ERFOVF], EFRSR[ERFWMI], and EFRSR[ERFDA], if they are set. */
                FLEXCAN_HWA_ERFSRClearEnhancedFifoFlag(pCan, FLEXCAN_ERFSR_ERFOVF_MASK | FLEXCAN_ERFSR_ERFUFW_MASK | FLEXCAN_ERFSR_ERFWMI_MASK | FLEXCAN_ERFSR_ERFDA_MASK);
                /* Write EFRCR[NFE] to configure the total number of enhanced Rx FIFO filter elements to be used in Enhanced Rx FIFO reception. */


                /* set rx fifo filter num, (n+1)*2 */
                u32TempERFCR = ((u32FilterNum / 2U - 1U) << FLEXCAN_ERFCR_NFE_SHIFT)&FLEXCAN_ERFCR_NFE_MASK;

                /* Write ERFCR[NEXIF] to configure the number of extended ID and standard ID filter elements to be used in Enhanced Rx FIFO reception (NEXIF �� NFE + 1). */
                /* set rx fifo extended id filter num, <= NFE+1 */
                u32TempERFCR |= (u32ExtIDFilterNum << FLEXCAN_ERFCR_NEXIF_SHIFT)&FLEXCAN_ERFCR_NEXIF_MASK;

                u32TempERFCR |= FLEXCAN_ERFCR_ERFWM(pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.u8FifoWaterMark - 1U); /* receive 1 message will indicate to fifo water mark */

                u32TempERFCR |= FLEXCAN_ERFCR_DMALW((12U + pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.eFifoDataLength) / 4);

                u32TempERFCR |= FLEXCAN_ERFCR_ERFEN_MASK; /* enable enhance fifo dma */

                FLEXCAN_HWA_SetERFCR(pCan, u32TempERFCR);

                /* set enhanced fifo */
                FLEXCAN_HWA_EnableFDFifo(pCan);

                /* Configure the Enhanced Rx FIFO watermark by writing ERFCR[ERFWM]. */

                /* If interrupts will be used, set the interrupt enables in the ERIER register */

                /* If DMA will be used, set MCR[DMA] to enable DMA operation and write ERFCR[DMALW] to configure the number of words to transfer for each Enhanced Rx FIFO data element */
            }

        }
        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
        #endif

    return tRetVal;

}


/**
 * @brief Configure can receive message box and id filter
 *
 * @param pCanHandle Can Handle point
 * @param pCanHandle Contains CAN Instance, Rx CAN ID and Mask
 * @return 0 is ok
 */
static FLEXCAN_ErrorType FLEXCAN_LL_RxFilterConfig(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg)
{
    FLEXCAN_ErrorType       tRetVal;
    FLEXCAN_Type            *pCan;
    FLEXCAN_MbSettingType   *pCurRxCfg;
    uint32_t                u32Mask;
    uint8_t                 u8Index11;
    uint8_t                 u8MaskIndex;
    uint8_t                 u8TxMbIndex;
    uint8_t                 u8RxMbIndex;
    uint32_t                u32TempAddr;

    tRetVal = FLEXCAN_E_OK;

    /* current pCan instance */
    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];


    if (pInitCfg->tRxFifoFilterCfg.bEnFifo)
    {
        if (pInitCfg->tRxFifoFilterCfg.eFifoType == FLEXCAN_LEGACY_FIFO)
        {
            /* set fifo filter parameter */
            tRetVal |= FLEXCAN_LL_SetLegacyFifo(pCanHandle, pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.pRxFilterFifoList, (uint32_t)pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.u8RxFilterFifoCnt);
        }
        else
        {
            /* only canfd controller support enhanced fifo features */
            if (FLEXCAN_LL_CheckFdInstance(pCanHandle->eInstance) == FLEXCAN_E_OK)
            {
                tRetVal |= (FLEXCAN_ErrorType)(tRetVal | FLEXCAN_LL_SetEnhancedFifo(pCanHandle, pInitCfg));
            }

        }
    }

    if((pInitCfg->tMbCfg.u8MBCnt > 0U) && (pInitCfg->tMbCfg.pMBList == NULL) )
    {
        tRetVal |= FLEXCAN_E_NULL_POINT;
    }


    if(tRetVal == FLEXCAN_E_OK)
    {
        for(u8Index11=0U; u8Index11 < s_aFlexCanIflagMaskSizes[pCanHandle->eInstance]; u8Index11++)
        {
            pCanHandle->tStatus.aTxInterruptMask[u8Index11] = 0U;
            pCanHandle->tStatus.aTxPollingMask[u8Index11] = 0U;
            pCanHandle->tStatus.aRxInterruptMask[u8Index11] = 0U;
            pCanHandle->tStatus.aRxPollingMask[u8Index11] = 0U;
            pCanHandle->tStatus.aInterruptMask[u8Index11] = 0U;
            pCanHandle->tStatus.aPollingMask[u8Index11] = 0U;

        }
        /* for tx first. */
        u8TxMbIndex = pCanHandle->tStatus.u8MbStart;
        for(u8Index11=0U; u8Index11 <pInitCfg->tMbCfg.u8MBCnt; u8Index11++ )
        {
            if(pInitCfg->tMbCfg.pMBList[u8Index11].bIsTxMB == 1U)
            {
                #if FLEXCAN_ERRATA_TRANSMIT_LIMIT == STD_ON
                if(pInitCfg->tRxFifoFilterCfg.bEnFifo && pInitCfg->tRxFifoFilterCfg.eFifoType == FLEXCAN_ENHANCED_FIFO)
                {
                    while(FLEXCAN_LL_CheckContains(s_aFlexCan_TransmitLimit_List, FLEXCAN_ERRATA_TRANSMIT_LM_LIST_LEN, u8TxMbIndex)==1U)
                    {
                        u8TxMbIndex = (uint8_t)(u8TxMbIndex + 1U);
                    }
                }
                #endif

                if(u8TxMbIndex<32U)
                    u8MaskIndex = 0U;
                else if(u8TxMbIndex<64U)
                    u8MaskIndex = 1U;
                else if(u8TxMbIndex<96U)
                    u8MaskIndex = 2U;
                else
                    u8MaskIndex = 0U;

                if(pInitCfg->tMbCfg.pMBList[u8Index11].bEnMBInt)
                {
                    pCanHandle->tStatus.aTxInterruptMask[u8MaskIndex] = pCanHandle->tStatus.aTxInterruptMask[u8MaskIndex] + (1U<<u8TxMbIndex);
                    pCanHandle->tStatus.aInterruptMask[u8MaskIndex] = pCanHandle->tStatus.aInterruptMask[u8MaskIndex] + (1U<<u8TxMbIndex);
                }
                else
                {
                    pCanHandle->tStatus.aTxPollingMask[u8MaskIndex] = pCanHandle->tStatus.aTxPollingMask[u8MaskIndex] + (1U<<u8TxMbIndex);
                    pCanHandle->tStatus.aPollingMask[u8MaskIndex] = pCanHandle->tStatus.aPollingMask[u8MaskIndex] + (1U<<u8TxMbIndex);

                }
                u8TxMbIndex = (uint8_t)(u8TxMbIndex + 1U);

            }
        }

        /* for rx first. */
        u8RxMbIndex = pCanHandle->tStatus.u8MbStart;
        for(u8Index11=0U; u8Index11 <pInitCfg->tMbCfg.u8MBCnt; u8Index11++ )
        {
            if(pInitCfg->tMbCfg.pMBList[u8Index11].bIsTxMB == 0U)
            {
                if(u8RxMbIndex<32U)
                    u8MaskIndex = 0U;
                else if(u8RxMbIndex<64U)
                    u8MaskIndex = 1U;
                else if(u8RxMbIndex<96U)
                    u8MaskIndex = 2U;
                else
                    u8MaskIndex = 0U;

                /* is tx occupied */
                while((((pCanHandle->tStatus.aTxInterruptMask[u8MaskIndex]>>u8RxMbIndex)&0x01U)==0x01U) || (((pCanHandle->tStatus.aTxPollingMask[u8MaskIndex]>>u8RxMbIndex)&0x01U)==0x01U) )
                {
                    u8RxMbIndex = (uint8_t)(u8RxMbIndex + 1U);
                }

                if(pInitCfg->tMbCfg.pMBList[u8Index11].bEnMBInt)
                {
                    pCanHandle->tStatus.aRxInterruptMask[u8MaskIndex] = pCanHandle->tStatus.aRxInterruptMask[u8MaskIndex] + (1U<<u8RxMbIndex);
                    pCanHandle->tStatus.aInterruptMask[u8MaskIndex] = pCanHandle->tStatus.aInterruptMask[u8MaskIndex] + (1U<<u8RxMbIndex);
                }
                else
                {
                    pCanHandle->tStatus.aRxPollingMask[u8MaskIndex] = pCanHandle->tStatus.aRxPollingMask[u8MaskIndex] + (1U<<u8RxMbIndex);
                    pCanHandle->tStatus.aPollingMask[u8MaskIndex] = pCanHandle->tStatus.aPollingMask[u8MaskIndex] + (1U<<u8RxMbIndex);

                }

                uint8_t u8DateLen;
                                    /* ############## current rx pMb #################### */

                u8DateLen = FLEXCAN_MB_GET_DATALEN(u8RxMbIndex, s_aFlexCanMbNums[pCanHandle->eInstance],s_aFlexCanDataLenNums[pCanHandle->eInstance], pCanHandle->tStatus.aMbDataWidth);

                /* current rx filter */
                pCurRxCfg = &(pInitCfg->tMbCfg.pMBList[u8Index11]);

                /* message buffer 1th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RxMbIndex, u8DateLen, 0U);

                FLEXCAN_MB_IDE_SRR_SET(u32TempAddr, (pCurRxCfg->eRxFrameType == FLEXCAN_ID_STD) ? (pCurRxCfg->eRxFrameType) : (pCurRxCfg->eRxFrameType | FLEXCAN_MB_SRR_MASK_U32));

                /* message buffer 2th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RxMbIndex, u8DateLen, 4U);

                /* 1. set filter id */
                if (pCurRxCfg->eRxFrameType == FLEXCAN_ID_STD)
                {
                    FLEXCAN_MB_STDID_SET(u32TempAddr, pCurRxCfg->u32RxCanId);
                    u32Mask = pCurRxCfg->u32RxCanIdMask << 18U; /* stardard id left shift 18 bits */
                }
                else /* extended id filter */
                {
                    FLEXCAN_MB_EXTID_SET(u32TempAddr, pCurRxCfg->u32RxCanId);
                    u32Mask = pCurRxCfg->u32RxCanIdMask; /* extendex id */
                }

                /* message buffer 1th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8RxMbIndex, u8DateLen, 0U);
                /* set code 0x04U to enable rx */
                FLEXCAN_MB_CODE_SET(u32TempAddr, 4U);

                /* 3. set rx filter u32Mask */
#if 1
                {
                    /* In FRZ mode, init CAN1 16 msg buf filters */
                    FLEXCAN_HWA_SetIndividualMask(pCan, (uint32_t)u8RxMbIndex, u32Mask);
                }
#else
                {
                    /* global u32Mask */
                    /* Global acceptance u32Mask: check all ID bits     */
                    if (u8RxMbIndex == 14U)
                    {
                        FLEXCAN_HWA_SetRx14Mask(pCan, u32Mask);
                    }
                    else if (u8RxMbIndex == 15U)
                    {
                        FLEXCAN_HWA_SetRx15Mask(pCan, u32Mask);
                    }
                    else
                    {
                        FLEXCAN_HWA_SetMBGlobalMask(pCan, u32Mask);
                    }
                }
#endif
                u8RxMbIndex = (uint8_t)(u8RxMbIndex + 1U);

            }
        }

        if(u8TxMbIndex > u8RxMbIndex)
            u8RxMbIndex = u8TxMbIndex;

        /* set max pMb number */
        FLEXCAN_HWA_AttachMCR(pCan, FLEXCAN_MCR_MAXMB(u8RxMbIndex-1U)   /* Maximum pMb index */
                              | FLEXCAN_MCR_IRMQ(1U));   /* individual Rx masking */
    }

    return tRetVal;
}


/**
 * @brief Configure can interrupt
 *
 * @param pCanHandle Can Handle point
 * @param pIntCfg Contians interrupt enable and call back function points
 * @return 0 is ok
 */
static FLEXCAN_ErrorType FLEXCAN_LL_SetInterrupt(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg)
{
    FLEXCAN_ErrorType    tRetVal;
    FLEXCAN_Type         *pCan;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    /* check buffer point if it is null */
    if (((pInitCfg->bEnErrInt == 1U) || (pInitCfg->bEnBusOffInt == 1U) ||
            (pInitCfg->bEnWarningInt == 1U) || (pInitCfg->bEnBusOffDoneInt == 1U) ) &&
          (pCanHandle->tSettings.pErrorNotify == NULL))
    {
        tRetVal |= FLEXCAN_E_NULL_POINT;
    }
//    if ((pInitCfg->tMbCfg.bEnTxMBInt == 1U) && (pCanHandle->tSettings.pTxNotify == NULL))
//    {
//        tRetVal |= FLEXCAN_E_NULL_POINT;
//    }
//    if ((pInitCfg->tMbCfg.bEnRxMBInt == 1U) && (pCanHandle->tSettings.pRxNotify == NULL))
//    {
//        tRetVal |= FLEXCAN_E_NULL_POINT;
//    }

    if(pInitCfg->tRxFifoFilterCfg.bEnFifo)
    {
        if(pInitCfg->tRxFifoFilterCfg.eFifoType == FLEXCAN_LEGACY_FIFO)
        {
            if ((pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bDataAvaliableInt == 1U) && (pCanHandle->tSettings.pRxNotify == NULL))
            {
                tRetVal |= FLEXCAN_E_NULL_POINT;
            }

            if ((pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bOverflowInt == 1U) && (pCanHandle->tSettings.pFifoIssueNotify == NULL))
            {
                tRetVal |= FLEXCAN_E_NULL_POINT;
            }

            if ((pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bWarningInt == 1U) && (pCanHandle->tSettings.pFifoIssueNotify == NULL))
            {
                tRetVal |= FLEXCAN_E_NULL_POINT;
            }
        }
        else
        {
            if ((pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt == 1U) && (pCanHandle->tSettings.pRxNotify == NULL))
            {
                tRetVal |= FLEXCAN_E_NULL_POINT;
            }

            if ((pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt == 1U) && (pCanHandle->tSettings.pFifoIssueNotify == NULL))
            {
                tRetVal |= FLEXCAN_E_NULL_POINT;
            }

            if ((pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt == 1U) && (pCanHandle->tSettings.pFifoIssueNotify == NULL))
            {
                tRetVal |= FLEXCAN_E_NULL_POINT;
            }
        }
    }


    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

        if (pInitCfg->bEnErrInt)
        {
            FLEXCAN_HWA_AttachCtrl1(pCan, FLEXCAN_CTRL1_ERRMSK(1U) );   /* error interrupt u32Mask */

            if (FLEXCAN_LL_CheckFdInstance(pCanHandle->eInstance) == FLEXCAN_E_OK)
            {
                FLEXCAN_HWA_AttachCtrl2(pCan, FLEXCAN_CTRL2_ERRMSK_FAST(1U) /* fast error */);
            }
        }

        if (pInitCfg->bEnBusOffInt)
        {
            FLEXCAN_HWA_AttachCtrl1(pCan, FLEXCAN_CTRL1_BOFFMSK(1U));  /* busoff interrupt u32Mask */
        }

        if (pInitCfg->bEnBusOffDoneInt)
        {
            FLEXCAN_HWA_AttachCtrl2(pCan, FLEXCAN_CTRL2_BOFFDONEMSK(1U) /* busoff done interrupt mask */);
        }

        if (pInitCfg->bEnWarningInt)
        {//add by lvziqi for CAN busoff funciton
            FLEXCAN_HWA_AttachCtrl1(pCan, FLEXCAN_CTRL1_TWRNMSK(1U) | FLEXCAN_CTRL1_RWRNMSK(1U)|FLEXCAN_CTRL1_BOFFREC(1)  /* tx/rx warning interrupt mask */);
        }

        if (pInitCfg->tRxFifoFilterCfg.bEnFifo)
        {
            if (pInitCfg->tRxFifoFilterCfg.eFifoType == FLEXCAN_LEGACY_FIFO) /* legacy fifo */
            {
                FLEXCAN_HWA_SetMask1MbInterrupt(pCan, (uint32_t)(((uint32_t)pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bDataAvaliableInt)<<5U) |
                        (uint32_t)(((uint32_t)pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bWarningInt)<<6U) |
                        (uint32_t)(((uint32_t)pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bOverflowInt)<<7U) );
            }
            else /* enhance fifo */
            {
                FLEXCAN_HWA_SetERFIER(pCan, FLEXCAN_ERFIER_ERFDAIE(pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt) |
                        FLEXCAN_ERFIER_ERFWMIIE(pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bWaterMarkInt) |
                        FLEXCAN_ERFIER_ERFOVFIE(pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt)  |
                        FLEXCAN_ERFIER_ERFUFWIE(pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt) );

            }
        }

        /* MB 31-0 IMASK1 */
        FLEXCAN_HWA_AttachMask1MbInterrupt(pCan, pCanHandle->tStatus.aInterruptMask[0]);
        #if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
        /* MB 63-32 IMASK2 */
        if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
        {
        	FLEXCAN_HWA_AttachMask2MbInterrupt(pCan, pCanHandle->tStatus.aInterruptMask[1]);
        }
        #endif
        #if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
        /* MB 95-64 IMASK3 */
        if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
        {
            FLEXCAN_HWA_AttachMask3MbInterrupt(pCan, pCanHandle->tStatus.aInterruptMask[2]);
        }
        #endif

        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
        #endif

    return tRetVal;
}

/**
 * @brief Configure can pretended network
 *
 * @param pCanHandle Contains CAN Instance, Rx CAN ID and Mask
 * @param pInitCfg initial parameters
 * @return 0 is ok
 */
static inline FLEXCAN_ErrorType FLEXCAN_LL_SetPNETPayload(FLEXCAN_Type *pCan, const FLEXCAN_InitType *const pInitCfg)
{
    FLEXCAN_ErrorType       tRetVal;
    tRetVal = FLEXCAN_E_OK;

    if( (pInitCfg->tPnetCfg.tPayloadCfg.u8DataLen1 > 8U ) ||
            (pInitCfg->tPnetCfg.tPayloadCfg.u8DataLen2 > 8U) )
    {
        tRetVal |= FLEXCAN_E_INVALID_PARAM;
    }
    else
    {

        FLEXCAN_HWA_AttachPNET_PayloadFilterType(pCan, pInitCfg->tPnetCfg.tPayloadCfg.eFilterType);
        FLEXCAN_HWA_SetPNET_DlcRange(pCan, pInitCfg->tPnetCfg.tPayloadCfg.u8DataLen1, pInitCfg->tPnetCfg.tPayloadCfg.u8DataLen2);
        FLEXCAN_HWA_SetPNET_Payload1Content(pCan,pInitCfg->tPnetCfg.tPayloadCfg.aData1[1],pInitCfg->tPnetCfg.tPayloadCfg.aData1[0]);
        if(pInitCfg->tPnetCfg.tPayloadCfg.eFilterType == FLEXCAN_PNET_PAYLOAD_FILTER_SAME)
        {
            /* FLT_DLC_LO must same to FLT_DLC_HI */
            if(pInitCfg->tPnetCfg.tPayloadCfg.u8DataLen1 == pInitCfg->tPnetCfg.tPayloadCfg.u8DataLen2)
            {
                /* Mask */
                FLEXCAN_HWA_SetPNET_Payload2Content(pCan,pInitCfg->tPnetCfg.tPayloadCfg.aData2[1],pInitCfg->tPnetCfg.tPayloadCfg.aData2[0]);
            }
            else
            {
                tRetVal |= FLEXCAN_E_INVALID_PARAM;
            }

        }
        else if(pInitCfg->tPnetCfg.tPayloadCfg.eFilterType == FLEXCAN_PNET_PAYLOAD_FILTER_GREATER_EQUAL)
        {

        }
        else if(pInitCfg->tPnetCfg.tPayloadCfg.eFilterType == FLEXCAN_PNET_PAYLOAD_FILTER_SMALLER_EQUAL)
        {

        }
        else if(pInitCfg->tPnetCfg.tPayloadCfg.eFilterType == FLEXCAN_PNET_PAYLOAD_FILTER_RANGE)
        {
            /* Data1 <= data <= Data2 */
            FLEXCAN_HWA_SetPNET_Payload2Content(pCan,pInitCfg->tPnetCfg.tPayloadCfg.aData2[1],pInitCfg->tPnetCfg.tPayloadCfg.aData2[0]);
        }
        else
        {

        }
    }

    return tRetVal;

}

/**
 * @brief Configure can pretended network
 *
 * @param pCanHandle Contains CAN Instance, Rx CAN ID and Mask
 * @param pInitCfg initial parameters
 * @return 0 is ok
 */
static FLEXCAN_ErrorType FLEXCAN_LL_SetPNET(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg)
{
    FLEXCAN_ErrorType       tRetVal;
    FLEXCAN_Type            *pCan;

    tRetVal = FLEXCAN_E_OK;

    /* current pCan instance */
    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

    FLEXCAN_HWA_ClrPNET_CTRL1_PN(pCan);

    if(pCanHandle->tSettings.pWakeNotify==NULL)
    {
        tRetVal = FLEXCAN_E_NULL_POINT;
    }
    else
    {

        /* timeout */
        if(pInitCfg->tPnetCfg.bTimeoutEn)
        {
            FLEXCAN_HWA_SetPNET_Timeout(pCan, pInitCfg->tPnetCfg.u16Timeout); /* timeout value, 64 times of can bit time */
            FLEXCAN_HWA_AttachPNET_TimeoutInterrupt(pCan); /* timeout interrupt */
        }

        /* match filter */
        if(pInitCfg->tPnetCfg.bFilterEnable)
        {
            FLEXCAN_HWA_AttachPNET_FilterType(pCan, (uint8_t)pInitCfg->tPnetCfg.ePnetFilterType); /* filter type */
            FLEXCAN_HWA_AttachPNET_MatchCount(pCan, pInitCfg->tPnetCfg.u8MatchTimes); /* match count */
            FLEXCAN_HWA_AttachPNET_MatchInterrupt(pCan); /* match interrupt */

            /* 4 types filter always contain id filter */
            FLEXCAN_HWA_AttachPNET_IDFilterType(pCan, pInitCfg->tPnetCfg.tIdCfg.eFilterType); /* id filter type */
            FLEXCAN_HWA_SetPNET_ID1(pCan, pInitCfg->tPnetCfg.tIdCfg.tID1.u8IDE, pInitCfg->tPnetCfg.tIdCfg.tID1.u8RTR, pInitCfg->tPnetCfg.tIdCfg.tID1.u32Id);

            if(pInitCfg->tPnetCfg.tIdCfg.eFilterType == FLEXCAN_PNET_ID_FILTER_SAME)
            {
                /* mask */
                FLEXCAN_HWA_SetPNET_ID2(pCan, pInitCfg->tPnetCfg.tIdCfg.tID2_Mask.u8IDE, pInitCfg->tPnetCfg.tIdCfg.tID2_Mask.u8RTR, pInitCfg->tPnetCfg.tIdCfg.tID2_Mask.u32Id);

            }
            else if(pInitCfg->tPnetCfg.tIdCfg.eFilterType == FLEXCAN_PNET_ID_FILTER_GREATER_EQUAL)
            {

            }
            else if(pInitCfg->tPnetCfg.tIdCfg.eFilterType == FLEXCAN_PNET_ID_FILTER_SMALLER_EQUAL)
            {

            }
            else if(pInitCfg->tPnetCfg.tIdCfg.eFilterType == FLEXCAN_PNET_ID_FILTER_RANGE)
            {
                /* ID1 <= id <= ID2 */
                FLEXCAN_HWA_SetPNET_ID2(pCan, pInitCfg->tPnetCfg.tIdCfg.tID2_Mask.u8IDE, pInitCfg->tPnetCfg.tIdCfg.tID2_Mask.u8RTR, pInitCfg->tPnetCfg.tIdCfg.tID2_Mask.u32Id);
            }
            else
            {

            }

            if(pInitCfg->tPnetCfg.ePnetFilterType == FLEXCAN_PNET_ID_FILTER)
            {

            }
            else if(pInitCfg->tPnetCfg.ePnetFilterType == FLEXCAN_PNET_ID_AND_PAYLOAD_FILTER) /* payload contained */
            {
                tRetVal |= FLEXCAN_LL_SetPNETPayload(pCan, pInitCfg);

            }
            else if(pInitCfg->tPnetCfg.ePnetFilterType ==  FLEXCAN_PNET_ID_FILTER_WITH_NCOUNT)
            {
                FLEXCAN_HWA_AttachPNET_MatchCount(pCan,pInitCfg->tPnetCfg.u8MatchTimes); /* match times */
            }
            else if(pInitCfg->tPnetCfg.ePnetFilterType ==  FLEXCAN_PNET_ID_AND_PAYLOAD_FILTER_WITH_NCOUNT) /* payload contained */
            {
                FLEXCAN_HWA_AttachPNET_MatchCount(pCan,pInitCfg->tPnetCfg.u8MatchTimes); /* match times */

                tRetVal |= FLEXCAN_LL_SetPNETPayload(pCan, pInitCfg);
            }
            else
            {

            }
        }
    }

    return tRetVal;
}

/**
 * @brief Interrupt check Tx Iflag and return Handler flag
 *
 * @param pCanHandle Can Handle Point
 */
static void FLEXCAN_LL_InterruptTx(FLEXCAN_HandleType *pCanHandle)
{
    uint8_t             u8MbIndex;
    FLEXCAN_Type        *pCan;
    uint32_t            u32Iflag;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
    u32Iflag = FLEXCAN_HWA_GetFlag1(pCan) & (pCanHandle->tStatus.aTxInterruptMask[0]);
    if(u32Iflag)
    {
        u8MbIndex = 0U;
        while ((u32Iflag != 0U))
        {
            if ((u32Iflag & 0x01U) == 0x01U)
            {
#if FLEXCAN_TX_FLAG_CLEAR_FIRST == STD_ON
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
                pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
#else
                pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
#endif


            }

            u8MbIndex++;
            u32Iflag = u32Iflag >> 1;
        }
    }
#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag2(pCan) & (pCanHandle->tStatus.aTxInterruptMask[1]);
        if(u32Iflag)
        {
            u8MbIndex = 32U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
#if FLEXCAN_TX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
#else
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }
        }
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag3(pCan) & (pCanHandle->tStatus.aTxInterruptMask[2]);
        if(u32Iflag)
        {
            u8MbIndex = 64U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
#if FLEXCAN_TX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
#else
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }
        }
    }
#endif

}

/**
 * @brief Polling Tx Iflag
 *
 * @param pCanHandle Can Handle Point
 */
static void FLEXCAN_LL_PollingTx(FLEXCAN_HandleType *pCanHandle)
{
    uint8_t             u8MbIndex;
    FLEXCAN_Type        *pCan;
    uint32_t            u32Iflag;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
    u32Iflag = FLEXCAN_HWA_GetFlag1(pCan) & (pCanHandle->tStatus.aTxPollingMask[0]);
    if(u32Iflag)
    {
        u8MbIndex = 0U;
        while ((u32Iflag != 0U))
        {
            if ((u32Iflag & 0x01U) == 0x01U)
            {
#if FLEXCAN_TX_FLAG_CLEAR_FIRST == STD_ON
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
                pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
#else
                pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
#endif
            }

            u8MbIndex++;
            u32Iflag = u32Iflag >> 1;
        }
    }
#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag2(pCan) & (pCanHandle->tStatus.aTxPollingMask[1]);
        if(u32Iflag)
        {
            u8MbIndex = 32U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
#if FLEXCAN_TX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
#else
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }
        }
    }

#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag3(pCan) & (pCanHandle->tStatus.aTxPollingMask[2]);
        if(u32Iflag)
        {
            u8MbIndex = 64U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
#if FLEXCAN_TX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
#else
                    pCanHandle->tSettings.pTxNotify(pCanHandle, FLEXCAN_LL_GetTxHandleByMbIndex(pCanHandle, u8MbIndex));
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }
        }
    }
#endif

}



/**
 * @brief Interrupt check Message Buffer Received Data
 *
 * @param u8CanIndex Can Index, Must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxMsgList Message Stored buffer point
 */
static void FLEXCAN_LL_InterruptRx(FLEXCAN_HandleType *pCanHandle)
{
    uint8_t             u8MbIndex;
    FLEXCAN_Type        *pCan;
    uint32_t            u32Iflag;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
    u32Iflag = FLEXCAN_HWA_GetFlag1(pCan) & (pCanHandle->tStatus.aRxInterruptMask[0]);
    if(u32Iflag)
    {
        u8MbIndex = 0U;
        while ((u32Iflag != 0U))
        {
            if ((u32Iflag & 0x01U) == 0x01U)
            {
                FLEXCAN_LL_ReceiveMb(pCanHandle, u8MbIndex);
                pCanHandle->tSettings.pRxBuf->u8RxHandle = FLEXCAN_LL_GetRxHandleByMbIndex(pCanHandle,u8MbIndex);
#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
                pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
#else
                pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
#endif
            }

            u8MbIndex++;
            u32Iflag = u32Iflag >> 1;
        }

    }

#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag2(pCan) & (pCanHandle->tStatus.aRxInterruptMask[1]);
        if(u32Iflag)
        {
            u8MbIndex = 32U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
                    FLEXCAN_LL_ReceiveMb(pCanHandle, u8MbIndex);
                    pCanHandle->tSettings.pRxBuf->u8RxHandle = FLEXCAN_LL_GetRxHandleByMbIndex(pCanHandle,u8MbIndex);
#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
#else
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }

        }
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag3(pCan) & (pCanHandle->tStatus.aRxInterruptMask[2]);
        if(u32Iflag)
        {
            u8MbIndex = 64U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
                    FLEXCAN_LL_ReceiveMb(pCanHandle, u8MbIndex);
                    pCanHandle->tSettings.pRxBuf->u8RxHandle = FLEXCAN_LL_GetRxHandleByMbIndex(pCanHandle,u8MbIndex);
#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
#else
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }

        }
    }
#endif


}



/**
 * @brief Polling Message Buffer Received Data
 *
 * @param u8CanIndex Can Index, Must less than FLEXCAN_INSTANCE_COUNT
 * @param pRxMsgList Message Stored buffer point
 */
static void FLEXCAN_LL_PollingRx(FLEXCAN_HandleType *pCanHandle)
{
    uint8_t             u8MbIndex;
    FLEXCAN_Type        *pCan;
    uint32_t            u32Iflag;

    pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
    u32Iflag = FLEXCAN_HWA_GetFlag1(pCan) & (pCanHandle->tStatus.aRxPollingMask[0]);
    if(u32Iflag)
    {
        u8MbIndex = 0U;
        while ((u32Iflag != 0U))
        {
            if ((u32Iflag & 0x01U) == 0x01U)
            {
                FLEXCAN_LL_ReceiveMb(pCanHandle, u8MbIndex);
                pCanHandle->tSettings.pRxBuf->u8RxHandle = FLEXCAN_LL_GetRxHandleByMbIndex(pCanHandle,u8MbIndex);
#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
                pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
#else
                pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
                FLEXCAN_HWA_SetFlag1(pCan, 1U<<u8MbIndex);
#endif
            }

            u8MbIndex++;
            u32Iflag = u32Iflag >> 1;
        }

    }

#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 1U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag2(pCan) & (pCanHandle->tStatus.aRxPollingMask[1]);
        if(u32Iflag)
        {
            u8MbIndex = 32U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
                    FLEXCAN_LL_ReceiveMb(pCanHandle, u8MbIndex);
                    pCanHandle->tSettings.pRxBuf->u8RxHandle = FLEXCAN_LL_GetRxHandleByMbIndex(pCanHandle,u8MbIndex);
#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
#else
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
                    FLEXCAN_HWA_SetFlag2(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }

        }
    }

#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    if(s_aFlexCanIflagMaskSizes[pCanHandle->eInstance] > 2U)
    {
        u32Iflag = FLEXCAN_HWA_GetFlag3(pCan) & (pCanHandle->tStatus.aRxPollingMask[2]);
        if(u32Iflag)
        {
            u8MbIndex = 64U;
            while ((u32Iflag != 0U))
            {
                if ((u32Iflag & 0x01U) == 0x01U)
                {
                    FLEXCAN_LL_ReceiveMb(pCanHandle, u8MbIndex);
                    pCanHandle->tSettings.pRxBuf->u8RxHandle = FLEXCAN_LL_GetRxHandleByMbIndex(pCanHandle,u8MbIndex);
#if FLEXCAN_RX_FLAG_CLEAR_FIRST == STD_ON
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
#else
                    pCanHandle->tSettings.pRxNotify(pCanHandle, &pCanHandle->tSettings.pRxBuf[0]);
                    FLEXCAN_HWA_SetFlag3(pCan, 1U<<u8MbIndex);
#endif
                }

                u8MbIndex++;
                u32Iflag = u32Iflag >> 1;
            }

        }
    }
#endif

}


/**
 * @brief Get can error
 *
 * @param pCanHandle Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @param bInterrupt if it is called in interrupt, set 1
 * @return error structure
 */
static FLEXCAN_ErrorType FLEXCAN_LL_ProcessError(FLEXCAN_HandleType *pCanHandle, uint8_t bInterrupt)
{
    FLEXCAN_ErrorType     tRetVal;
    FLEXCAN_Type          *pCan;
    FLEXCAN_ErrorInfoType tErrorInfo;
    uint32_t              u32ECR;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if ((tRetVal == FLEXCAN_E_OK) && (pCanHandle->tStatus.eStatusSeq >= FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
    }


    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

        tErrorInfo.u32ESR1Value = FLEXCAN_HWA_GetErrorInfo(pCan);

        u32ECR = FLEXCAN_HWA_GetErrorCount(pCan);

        tErrorInfo.u32ESR1Value &= FLEXCAN_ESR1_BIT1ERR_FAST_MASK | FLEXCAN_ESR1_BIT0ERR_FAST_MASK | FLEXCAN_ESR1_CRCERR_FAST_MASK | FLEXCAN_ESR1_FRMERR_FAST_MASK |
                                   FLEXCAN_ESR1_STFERR_FAST_MASK |
                                   FLEXCAN_ESR1_ERROVR_MASK | FLEXCAN_ESR1_ERRINT_FAST_MASK | FLEXCAN_ESR1_BOFFDONEINT_MASK | FLEXCAN_ESR1_TWRNINT_MASK | FLEXCAN_ESR1_RWRNINT_MASK |
                                   FLEXCAN_ESR1_BIT1ERR_MASK | FLEXCAN_ESR1_BIT0ERR_MASK | FLEXCAN_ESR1_ACKERR_MASK | FLEXCAN_ESR1_CRCERR_MASK | FLEXCAN_ESR1_FRMERR_MASK | FLEXCAN_ESR1_STFERR_MASK |
                                   FLEXCAN_ESR1_TXWRN_MASK | FLEXCAN_ESR1_RXWRN_MASK | FLEXCAN_ESR1_FLTCONF_MASK | FLEXCAN_ESR1_BOFFINT_MASK | FLEXCAN_ESR1_ERRINT_MASK;
        if (tErrorInfo.u32ESR1Value)
        {
            FLEXCAN_HWA_ClrErrorInfo(pCan, tErrorInfo.u32ESR1Value);
        }


        tErrorInfo.u32RxErrCnt = (u32ECR & FLEXCAN_ECR_RXERRCNT_MASK) >> FLEXCAN_ECR_RXERRCNT_SHIFT;
        tErrorInfo.u32RxErrCnt_Fast = (u32ECR & FLEXCAN_ECR_RXERRCNT_FAST_MASK) >> FLEXCAN_ECR_RXERRCNT_FAST_SHIFT;
        tErrorInfo.u32TxErrCnt = (u32ECR & FLEXCAN_ECR_TXERRCNT_MASK) >> FLEXCAN_ECR_TXERRCNT_SHIFT;
        tErrorInfo.u32TxErrCnt_Fast = (u32ECR & FLEXCAN_ECR_TXERRCNT_FAST_MASK) >> FLEXCAN_ECR_TXERRCNT_FAST_SHIFT;

        u32ECR = (tErrorInfo.u32ESR1Value & (FLEXCAN_ESR1_BOFFINT_MASK | FLEXCAN_ESR1_ERRINT_MASK));

        if (u32ECR && bInterrupt)
        {
            pCanHandle->tSettings.pErrorNotify(pCanHandle, &tErrorInfo);
        }

        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
    else
    {
        PROCESS_UNUSED_VAR(tErrorInfo);
        PROCESS_UNUSED_VAR(u32ECR);
    }
        #endif

    return tRetVal;
}

/**
 * @brief Get can pet message
 *
 * @param pCanHandle Can Index, must less than FLEXCAN_INSTANCE_COUNT
 * @return error structure
 */
static void FLEXCAN_LL_ProcessPNET(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_Type          *pCan;
    pCan = s_aFlexCan_InstanceTable[(uint8_t)pCanHandle->eInstance];

    FLEXCAN_HWA_CheckPNETAck(pCan, 0U, 1000);

    if( (pCanHandle->tSettings.pWakeNotify != NULL) && (pCanHandle->tSettings.pWakeMsg != NULL) )
    {
        uint32_t u32Temp;


        u32Temp = FLEXCAN_HWA_ChkPNET_TimeoutInterrupt(pCan);

        /* timeout wake-up */
        if(u32Temp > 0U)
        {
            pCanHandle->tSettings.pWakeMsg->u8CanIndex = pCanHandle->eInstance;
            pCanHandle->tSettings.pWakeMsg->eWakeupSrc = FLEXCAN_PENT_WAKEUP_SRC_TIMEOUT;

            pCanHandle->tSettings.pWakeNotify(pCanHandle, pCanHandle->tSettings.pWakeMsg);

            FLEXCAN_HWA_ClrPNET_TimeoutFlag(pCan);
        }
        u32Temp = FLEXCAN_HWA_ChkPNET_MatchInterrupt(pCan);
        /* match wake-up */
        if(u32Temp > 0U)
        {
            pCanHandle->tSettings.pWakeMsg->u8CanIndex = pCanHandle->eInstance;
            pCanHandle->tSettings.pWakeMsg->eWakeupSrc = FLEXCAN_PENT_WAKEUP_SRC_MATCH;
            u32Temp = FLEXCAN_HWA_GetPNET_MatchCount(pCan);
            if(u32Temp > 4U)
            {
                u32Temp = 4U; /* wake-up store max 4 frames */
            }

            uint32_t u32TempAddr;
            uint32_t u32Index;
            uint32_t u32WordLen;
            uint32_t *pSrc;
            uint32_t *pDest;

            for(u32Index = 0U; u32Index < u32Temp; u32Index++)
            {
                u32TempAddr = FLEXCAN_HWA_PNETRamAddr(pCan, u32Index);
                pCanHandle->tSettings.pWakeMsg->u32DataLen = FLEXCAN_MB_DLC_GET(u32TempAddr);
                pCanHandle->tSettings.pWakeMsg->u32DataLen = FLEXCAN_DlcToDataLen(pCanHandle->tSettings.pWakeMsg->u32DataLen);
                pCanHandle->tSettings.pWakeMsg->eFrameType = (FLEXCAN_IdType)(FLEXCAN_MB_IDE_GET(u32TempAddr));

                /* message buffer 2th word */
                u32TempAddr = u32TempAddr + 4U;

                if (pCanHandle->tSettings.pWakeMsg->eFrameType)
                {
                    pCanHandle->tSettings.pWakeMsg->u32CanId = FLEXCAN_MB_EXTID_GET(u32TempAddr);
                }
                else
                {
                    pCanHandle->tSettings.pWakeMsg->u32CanId = FLEXCAN_MB_STDID_GET(u32TempAddr);
                }



                pDest = (uint32_t *)pCanHandle->tSettings.pWakeMsg->aData;
                /* message buffer 3th word */
                pSrc = (uint32_t*)(u32TempAddr + 4U);


                u32WordLen = pCanHandle->tSettings.pWakeMsg->u32DataLen / 4U + (pCanHandle->tSettings.pWakeMsg->u32DataLen % 4U > 0U ? 1U : 0U);

                for (u32TempAddr = 0U; u32TempAddr < u32WordLen; u32TempAddr++)
                {
                    /* big endian to little endian */
                    REV_BYTES_32(pSrc[u32TempAddr], pDest[u32TempAddr]);
                }

            }

            pCanHandle->tSettings.pWakeNotify(pCanHandle, pCanHandle->tSettings.pWakeMsg);
            FLEXCAN_HWA_ClrPNET_MatchFlag(pCan);
        }
    }


}
/* ################################################################################## */
/* ################################ Global Functions ################################ */
/**
 * @brief Get CAN Data width number for current can
 *    MBDSR0..MBDSRn
 *
 * @param pCanHandle Can Handle point
 * @return data width array number
 */
uint8_t FLEXCAN_GetDataWidthArrayLen(FLEXCAN_HandleType *pCanHandle)
{
    return s_aFlexCanDataLenNums[pCanHandle->eInstance];
}

/**
 * @brief Initial CAN
 *
 * @param pCanHandle Can Handle point
 * @param pInitCfg  clock, baud-rate, canfd, data length and so on.
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_Init(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_InitType *const pInitCfg)
{
    FLEXCAN_ErrorType    tRetVal;
    uint32_t             u32TempCtrl1;
    uint32_t             u32TempMcr;
    FLEXCAN_Type         *pCan;

    uint32_t              u32FdCtrl = 0U;
    uint32_t              u32Eprs;
    uint32_t              u32Encbt;
    uint32_t              u32Edcbt = 0U;
    uint8_t               u8DataWidthNum;
    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);


    if ((tRetVal == FLEXCAN_E_OK) && (pCanHandle->tStatus.eStatusSeq == FLEXCAN_SEQUENCE_DEINIT))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_SEQUENCE);
    }

    if ((pCanHandle == NULL) || (pInitCfg == NULL))
    {
        tRetVal |= FLEXCAN_E_NULL_POINT;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_NULL_POINT);
    }
    else
    {
        if(pInitCfg->tRxFifoFilterCfg.bEnFifo)
        {
            /* legacy only support non-fd */
            if (pInitCfg->tRxFifoFilterCfg.eFifoType == FLEXCAN_LEGACY_FIFO)
            {
                if (pInitCfg->bEnFd == 1U)
                {
                    tRetVal |= FLEXCAN_E_INVALID_PARAM;
                    FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_PARAM);
                }
                else
                {
                    /* the filter number must be multi of 8 */
                    if(pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.u8RxFilterFifoCnt%8)
                    {
                        tRetVal |= FLEXCAN_E_INVALID_PARAM;
                        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_PARAM);
                    }
                }
            }
            else /* enhanced fifo */
            {
                if (pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.u8FifoWaterMark > s_aFlexCanEnhancedDepthp[pCanHandle->eInstance])
                {
                    tRetVal |= FLEXCAN_E_INVALID_PARAM;
                    FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_PARAM);
                }
                else
                {
                    /* the filter number must be multi of 2 */
                    if(pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt%2)
                    {
                        tRetVal |= FLEXCAN_E_INVALID_PARAM;
                        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_PARAM);
                    }
                }
            }
        }

    }


    u8DataWidthNum = FLEXCAN_GetDataWidthArrayLen(pCanHandle);



	#endif
        /* copy data width number to status */
        for(u8DataWidthNum=0U; u8DataWidthNum<FLEXCAN_FD_DATALEN_RANGE_NUM_MAX; u8DataWidthNum++)
        {
            if (pInitCfg->bEnFd == 0U)
            {
                pCanHandle->tStatus.aMbDataWidth[u8DataWidthNum] = FLEXCAN_DATAWIDTH_8;
            }
            else
            {
                pCanHandle->tStatus.aMbDataWidth[u8DataWidthNum] = pInitCfg->tMbCfg.aDataWidthRange[u8DataWidthNum];
            }
        }
	#if FLEXCAN_DEV_ERROR_REPORT == STD_ON

    if (tRetVal == FLEXCAN_E_OK)
    {
    #endif

        pCan = s_aFlexCan_InstanceTable[(uint8_t)pCanHandle->eInstance];

        tRetVal = FLEXCAN_E_OK;


        if (pInitCfg->bEnFd == 0U)
        {
            /* when pCan fd enabled, pCan normal bit set by CBT !!!! */
            u32Eprs  =  FLEXCAN_EPRS_ENPRESDIV(pInitCfg->tNormalBaud.u32Presdiv - 1U);

            u32Encbt =  FLEXCAN_ENCBT_NRJW(pInitCfg->tNormalBaud.u32Rjw - 1U) |
                        FLEXCAN_ENCBT_NTSEG2(pInitCfg->tNormalBaud.u32Pseg2  - 1U) |
                        FLEXCAN_ENCBT_NTSEG1(pInitCfg->tNormalBaud.u32Pseg1 + pInitCfg->tNormalBaud.u32Propseg - 1U) ;
        }
        else
        {
            u32FdCtrl = FLEXCAN_FDCTRL_FDRATE(pInitCfg->bEnFd);

            u32FdCtrl = (uint32_t)(u32FdCtrl | FLEXCAN_HWA_CalDataWidth((uint8_t*)pInitCfg->tMbCfg.aDataWidthRange));

            u32Eprs  =  FLEXCAN_EPRS_ENPRESDIV(pInitCfg->tNormalBaud.u32Presdiv - 1U) |
                        FLEXCAN_EPRS_EDPRESDIV(pInitCfg->tFdBaud.u32Presdiv - 1U);

            u32Encbt =  FLEXCAN_ENCBT_NRJW(pInitCfg->tNormalBaud.u32Rjw - 1U) |
                        FLEXCAN_ENCBT_NTSEG2(pInitCfg->tNormalBaud.u32Pseg2  - 1U) |
                        FLEXCAN_ENCBT_NTSEG1(pInitCfg->tNormalBaud.u32Pseg1 + pInitCfg->tNormalBaud.u32Propseg - 1U);

            u32Edcbt =  FLEXCAN_EDCBT_DRJW(pInitCfg->tFdBaud.u32Rjw - 1U) |
                        FLEXCAN_EDCBT_DTSEG2(pInitCfg->tFdBaud.u32Pseg2 - 1U) |
                        FLEXCAN_EDCBT_DTSEG1(pInitCfg->tFdBaud.u32Pseg1 + pInitCfg->tFdBaud.u32Propseg - 1U);
        }

        FLEXCAN_HWA_SetMcrDisable(pCan, TRUE);
        FLEXCAN_HWA_SetCtrl1(pCan, 0U);
        FLEXCAN_HWA_SetCtrl1BaudSrc(pCan, pInitCfg->eClkSrcSel);

        FLEXCAN_HWA_SetMcrDisable(pCan, FALSE);

        /*  mcr->B.bitMDIS = 0; */

        FLEXCAN_HWA_SetHaltFreeze(pCan);

        /* wait for bitFRZACK=1 on freeze mode entry/exit */
        if (FLEXCAN_HWA_WaitMcrFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_E_TIMEOUT;
        }
        else
        {
            FLEXCAN_HWA_SetCtrl2(pCan,
                                 FLEXCAN_CTRL2_WRMFRZ(1U)      |  /* initial ram ecc */
                                 FLEXCAN_CTRL2_TASD(20U)       |
                                 FLEXCAN_CTRL2_ISOCANFDEN(1U)  |
                                 FLEXCAN_CTRL2_BTE(1U)
                                );

            /* when pCan fd disabled, pCan normal bit set by CTRL1 !!!! */
            u32TempCtrl1 = FLEXCAN_CTRL1_CLKSRC(pInitCfg->eClkSrcSel) | FLEXCAN_CTRL1_LOM(pInitCfg->bListenOnly) | FLEXCAN_CTRL1_BOFFREC(pInitCfg->bEnAutoRec);


            if (!pInitCfg->bEnFd)
            {
                FLEXCAN_HWA_SetEPRS(pCan, u32Eprs);
                FLEXCAN_HWA_SetENCBT(pCan, u32Encbt);
            }
            else
            {
                FLEXCAN_HWA_SetFDCTRL(pCan, u32FdCtrl);
                FLEXCAN_HWA_SetEPRS(pCan, u32Eprs);
                FLEXCAN_HWA_SetENCBT(pCan, u32Encbt);
                FLEXCAN_HWA_SetEDCBT(pCan, u32Edcbt);
            }


            FLEXCAN_HWA_SetCtrl1(pCan, u32TempCtrl1);

            if (pInitCfg->bEnSsp != 0)
            {

                FLEXCAN_HWA_SetETDC(pCan,
                                    FLEXCAN_ETDC_ETDCEN(1U) |
                                    FLEXCAN_ETDC_ETDCOFF((pInitCfg->tFdBaud.u32Propseg + pInitCfg->tFdBaud.u32Pseg1 + 1)*pInitCfg->tFdBaud.u32Presdiv) /* (sync+propseg+pseg1)∗presdiv */
                                   );
            }
            /* initial RAM to avoid ECC error */
            FLEXCAN_LL_EmbededRam_Init(pCanHandle->eInstance);

            u32TempMcr = FLEXCAN_MCR_MDIS(0) |               /* enable pCan module */
                         FLEXCAN_MCR_FRZ(1)    |                 /* not frozen */
                         FLEXCAN_MCR_HALT(1)   |                 /* not halt */
                         FLEXCAN_MCR_SOFTRST(0) |                /* not reset */
                         FLEXCAN_MCR_SUPV(1)   |                 /* supervisor mode */
                         FLEXCAN_MCR_WRNEN(0)  |                 /* wake up disable */
                         FLEXCAN_MCR_SRXDIS(1) |                 /* self reception disable */
                         FLEXCAN_MCR_IRMQ(0)   |                 /* individual Rx masking */
                         FLEXCAN_MCR_PNET_EN(0) |                /* Pretended Networking Enable */
                         FLEXCAN_MCR_LPRIOEN(0) |                /* Local Priority disable */
                         FLEXCAN_MCR_AEN(1)    |                 /* abort disable */
                         FLEXCAN_MCR_FDEN(pInitCfg->bEnFd) |     /* CAN FD enable */
                         FLEXCAN_MCR_IDAM(0)   |                 /* ID Acceptance Mode for Rx FIFO, format A */
                         FLEXCAN_MCR_MAXMB(0);                   /* Max number of Message Buffer, num 31 is the 32th MB */

            if(pInitCfg->tRxFifoFilterCfg.bEnFifo)
            {
                if(pInitCfg->tRxFifoFilterCfg.eFifoType == FLEXCAN_LEGACY_FIFO) /* legacy fifo */
                {
                    u32TempMcr |= FLEXCAN_MCR_DMA(pInitCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bEnFifoDMA);     /* DMA enable */
                    u32TempMcr |= FLEXCAN_MCR_RFEN(1U); /* Legacy RX FIFO, only when canfd not enable */
                }
                else /* enhanced fifo */
                {
                    u32TempMcr |= FLEXCAN_MCR_DMA(pInitCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bEnFifoDMA);     /* DMA enable */
                }

            }

            FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);       /* Negate FlexCAN 1 halt state for 32 MBs */

        }

        tRetVal |= FLEXCAN_LL_RxFilterConfig(pCanHandle, pInitCfg);

        /* check mb total number */
        if(FLEXCAN_LL_GetMbNum(pCanHandle, pInitCfg)<(pCanHandle->tStatus.u8MbStart+pInitCfg->tMbCfg.u8MBCnt))
        {
            tRetVal |= FLEXCAN_E_MB_OUTOFRANGE;
        }

        if (tRetVal == FLEXCAN_E_OK)
        {
            tRetVal |= FLEXCAN_LL_SetInterrupt(pCanHandle, pInitCfg);
        }

        if (tRetVal == FLEXCAN_E_OK)
        {
            pCanHandle->tStatus.eStatusSeq = FLEXCAN_SEQUENCE_NOTSTART;
        }

        /* Pretended Network for Wake-up in STOP Mode */
        if(pInitCfg->tPnetCfg.bPNetEnable)
        {
            tRetVal |= FLEXCAN_LL_SetPNET(pCanHandle, pInitCfg);
            FLEXCAN_HWA_AttachMCR(pCan, FLEXCAN_MCR_PNET_EN_MASK);
            /* FLEXCAN_HWA_CheckPNETAck(pCan, 1U, 1000); */
        }

        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
    else
    {
        PROCESS_UNUSED_VAR(u32FdCtrl);
    }
        #endif
    return tRetVal;
}


/**
 * @brief De-initial can instance
 *
 * @param pCanHandle Can Handle point
 * @return 0 is ok, others are not ok
 */
FLEXCAN_ErrorType FLEXCAN_DeInit(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t          u32TempMcr;
    FLEXCAN_Type      *pCan;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if (tRetVal == FLEXCAN_E_OK)
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_SEQUENCE);
    }

    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif
        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
        FLEXCAN_HWA_SetHaltFreeze(pCan);

        /* wait for bitFRZACK=1 on freeze mode entry/exit */
        if (FLEXCAN_HWA_WaitMcrFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_E_TIMEOUT;
        }
        else
        {
            if (s_aFlexCanFd_SupportTable[pCanHandle->eInstance])
            {
                FLEXCAN_HWA_DisableFDFifo(pCan);
            }


            FLEXCAN_HWA_DisableLegacyFifo(pCan);
            FLEXCAN_HWA_ClrPNET_CTRL1_PN(pCan);

            u32TempMcr = FLEXCAN_MCR_MDIS(1)   |                 /* enable pCan module */
                         FLEXCAN_MCR_FRZ(0)    |                 /* not frozen */
                         FLEXCAN_MCR_RFEN(0U)  |                 /* RX FIFO disable */
                         FLEXCAN_MCR_HALT(0)   |                 /* not halt */
                         FLEXCAN_MCR_SOFTRST(1) |                /* not reset */
                         FLEXCAN_MCR_SUPV(1)   |                 /* supervisor mode */
                         FLEXCAN_MCR_WRNEN(0)  |                 /* wake up disable */
                         FLEXCAN_MCR_SRXDIS(1) |                 /* self reception disable */
                         FLEXCAN_MCR_IRMQ(0)   |                 /* individual Rx masking */
                         FLEXCAN_MCR_DMA(0)    |                 /* DMA enable */
                         FLEXCAN_MCR_PNET_EN(0) |                /* Pretended Networking Enable */
                         FLEXCAN_MCR_LPRIOEN(0) |                /* Local Priority disable */
                         FLEXCAN_MCR_AEN(0)    |                 /* abort disable */
                         FLEXCAN_MCR_FDEN(0)   |                 /* CAN FD enable */
                         FLEXCAN_MCR_IDAM(0)   |                 /* ID Acceptance Mode for Rx FIFO, format A */
                         FLEXCAN_MCR_MAXMB(0);                   /* Max number of Message Buffer, num 31 is the 32th MB */


            FLEXCAN_HWA_SetCtrl1(pCan, 0U);
            FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);       /* Negate FlexCAN 1 halt state for 32 MBs */
            pCanHandle->tStatus.eStatusSeq = FLEXCAN_SEQUENCE_DEINIT;
        }

        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Start can instance
 *
 * @param pCanHandle Can Handle point
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_Start(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t   u32TempMcr;
    FLEXCAN_Type *pCan;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if ((tRetVal == FLEXCAN_E_OK) && (pCanHandle->tStatus.eStatusSeq == FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_SEQUENCE);
    }


    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];
        u32TempMcr = FLEXCAN_HWA_GetMCR(pCan);

        u32TempMcr &= ~(FLEXCAN_MCR_FRZ(1U)    |  /* not frozen */
                        FLEXCAN_MCR_HALT(1U)    /* not halt */
                        /*| FLEXCAN_MCR_SUPV(1)   user mode */
                       ); /* not reset */

        FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);

        if (FLEXCAN_HWA_WaitMcrExitFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_E_TIMEOUT;
        }
        else
        {

            if (FLEXCAN_HWA_WaitMcrReady(pCan, 10000U) != 0U)
            {
                tRetVal |= FLEXCAN_E_TIMEOUT;
            }
            else
            {
                pCanHandle->tStatus.eStatusSeq = FLEXCAN_SEQUENCE_STARTED;
            }
        }
        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
        #endif

    return tRetVal;
}


/**
 * @brief Stop can instance
 *
 * @param pCanHandle Can Handle point
 */
FLEXCAN_ErrorType FLEXCAN_Stop(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_ErrorType tRetVal;
    uint32_t   u32TempMcr;
    FLEXCAN_Type *pCan;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if ((tRetVal == FLEXCAN_E_OK) && ((uint8_t)(pCanHandle->tStatus.eStatusSeq) >= (uint8_t)(FLEXCAN_SEQUENCE_NOTSTART)))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_SEQUENCE);
    }


    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif
        /* set started state */
        pCanHandle->tStatus.eStatusSeq = FLEXCAN_SEQUENCE_NOTSTART;

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

        u32TempMcr = FLEXCAN_HWA_GetMCR(pCan);

        u32TempMcr |= FLEXCAN_MCR_FRZ(1U)    |  /* not frozen */
                      FLEXCAN_MCR_HALT(1U)    /* not halt */
                      /*| FLEXCAN_MCR_SUPV(1)   user mode */
                      ; /* not reset */

        FLEXCAN_HWA_SetMCR(pCan, u32TempMcr);

        /* must wait */
        if (FLEXCAN_HWA_WaitMcrFreezen(pCan, 10000U) != 0U)
        {
            tRetVal |= FLEXCAN_E_TIMEOUT;
        }
        else
        {

            /* must wait */
            if (FLEXCAN_HWA_WaitMcrNoReady(pCan, 10000U) != 0U)
            {
                tRetVal |= FLEXCAN_E_TIMEOUT;
            }
            else
            {
            }
        }
        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }

        #endif

    return tRetVal;
}


/**
 * @brief Transmit data, if tx disable, must call FLEXCAN_TransmitProcess after transmiting
 *
 * @param pCanHandle Can Handle point
 * @param pTxMsg contains CAN instance, CAN ID, CAN FD and CAN data.
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitData(FLEXCAN_HandleType *pCanHandle, const FLEXCAN_TxMsgType *const pTxMsg)
{
    FLEXCAN_ErrorType     tRetVal;
    uint32_t              *pSrc;
    uint32_t              *pDest;
    uint32_t              u32Index;
    FLEXCAN_Type          *pCan;
    uint8_t               u8TxRealMbIndex;
    uint32_t              u32WordLen;
    uint32_t              u32TempAddr;
    uint32_t              u32Code;
    uint8_t               u8DateLen;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if ((tRetVal == FLEXCAN_E_OK) && (pCanHandle->tStatus.eStatusSeq == FLEXCAN_SEQUENCE_STARTED))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_SEQUENCE);
    }

    if (pTxMsg == NULL)
    {
        tRetVal |= FLEXCAN_E_INVALID_PARAM;
    }
    else
    {
        /* check buffer point if it is null */
        if (&(pTxMsg->aData) == NULL)
        {
            tRetVal |= FLEXCAN_E_INVALID_PARAM;
        }
        else
        {

        }
    }

    if ((pTxMsg->bEnFd == 1U) && (s_aFlexCanFd_SupportTable[pCanHandle->eInstance]==0U))
    {
        tRetVal |= FLEXCAN_E_INVALID_PARAM;
    }


    if (tRetVal == FLEXCAN_E_OK)
    {
    #else
    tRetVal = FLEXCAN_E_OK;
    #endif

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

        u8TxRealMbIndex = FLEXCAN_LL_GetMbIndexByTxHandle(pCanHandle, pTxMsg->u8TxHandle);

        if (u8TxRealMbIndex == 0xFFU)
        {
            tRetVal = FLEXCAN_E_INVALID_PARAM;
        }
        else
        {

            u8DateLen = FLEXCAN_MB_GET_DATALEN(u8TxRealMbIndex, s_aFlexCanMbNums[pCanHandle->eInstance], s_aFlexCanDataLenNums[pCanHandle->eInstance], pCanHandle->tStatus.aMbDataWidth);
            if (pTxMsg->u32DataLen > u8DateLen)
            {
                tRetVal |= FLEXCAN_E_INVALID_PARAM;
            }

            /* message buffer 1th word */
            u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, u8DateLen, 0U);
            u32Code = FLEXCAN_MB_CODE_GET(u32TempAddr);

            if ((0x8 != u32Code) && (0U != u32Code))
            {
                tRetVal = FLEXCAN_E_BUSY;
            }
            else
            {

                /* message buffer 1th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, u8DateLen, 0U);
                /* clear last value */
                FLEXCAN_REG32_CONTENT(u32TempAddr) = 0U;

                FLEXCAN_MB_EDL_SET(u32TempAddr, pTxMsg->bEnFd);
                FLEXCAN_MB_BRS_SET(u32TempAddr, pTxMsg->bEnBrs);


                /* DLC */
                u32Index = FLEXCAN_DataLenToDlc(pTxMsg->u32DataLen);
                FLEXCAN_MB_DLC_SET(u32TempAddr, u32Index);
                if (pTxMsg->eFrameType == FLEXCAN_ID_STD)
                {
                    /* SRR & IDE*/
                    FLEXCAN_MB_IDE_SRR_SET(u32TempAddr, pTxMsg->eFrameType);
                }
                else /* extended id */
                {
                    /* SRR & IDE */
                    FLEXCAN_MB_IDE_SRR_SET(u32TempAddr, pTxMsg->eFrameType | FLEXCAN_MB_SRR_MASK_U32); /* extended id must set SRR=1 */
                }
                /* message buffer 2th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, u8DateLen, 4U);
                /* clear last value */
                FLEXCAN_REG32_CONTENT(u32TempAddr) = 0U;

                /* standard id */
                if (pTxMsg->eFrameType == FLEXCAN_ID_STD)
                {
                    FLEXCAN_MB_STDID_SET(u32TempAddr, pTxMsg->u32CanId);
                }
                else /* extended id */
                {
                    FLEXCAN_MB_EXTID_SET(u32TempAddr, pTxMsg->u32CanId);
                }

                FLEXCAN_MB_PRIO_SET(u32TempAddr, 0U);

                pSrc = (uint32_t *)(uint32_t)(&(pTxMsg->aData[0]));
                /* message buffer 3th word */
                pDest = (uint32_t *)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, u8DateLen, 8U);

                u32WordLen = pTxMsg->u32DataLen / 4U + (pTxMsg->u32DataLen % 4U > 0U ? 1U : 0U);

                /* revert data to little endian */
                for (u32Index = 0U; u32Index < u32WordLen; u32Index++)
                {
                    /* big endian to little endian */
                    REV_BYTES_32(pSrc[u32Index], pDest[u32Index]);
                }


                /* message buffer 1th word */
                u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, u8DateLen, 0U);


                /* CODE set 0x0C to transmit */
                FLEXCAN_MB_CODE_SET(u32TempAddr, 0x0CU);


            }
        }
        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
    else
    {
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_TRANSMIT, FLEXCAN_E_INVALID_PARAM);
    }
        #endif

    return tRetVal;
}



/**
 * @brief Abort transmit with special transmit handler
 *
 * @param pCanHandle Can Handle point
 * @param u8TxHandle Transmit handler
 * @return 0 is ok
 */
FLEXCAN_ErrorType FLEXCAN_TransmitAbort(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle)
{
    FLEXCAN_ErrorType     tRetVal;
    FLEXCAN_Type          *pCan;
    uint8_t               u8TxRealMbIndex;
    uint32_t              u32TempAddr;
    uint8_t               u8DateLen;

    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if ((tRetVal == FLEXCAN_E_OK) && (pCanHandle->tStatus.eStatusSeq == FLEXCAN_SEQUENCE_STARTED))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_INIT, FLEXCAN_E_INVALID_SEQUENCE);
    }


    if (tRetVal == FLEXCAN_E_OK)
    {

    #endif

        pCan = (FLEXCAN_Type *)s_aFlexCan_InstanceTable[pCanHandle->eInstance];

        u8TxRealMbIndex = FLEXCAN_LL_GetMbIndexByTxHandle(pCanHandle, u8TxHandle);

        if (u8TxRealMbIndex == 0xFFU)
        {
            tRetVal = FLEXCAN_E_INVALID_PARAM;
        }
        else
        {
            u8DateLen = FLEXCAN_MB_GET_DATALEN(u8TxRealMbIndex, s_aFlexCanMbNums[pCanHandle->eInstance], s_aFlexCanDataLenNums[pCanHandle->eInstance], pCanHandle->tStatus.aMbDataWidth);
            /* message buffer 1th word */
            u32TempAddr = (uint32_t)FLEXCAN_MB_WORDN_ADDR(&(pCan->RAM[0U]), u8TxRealMbIndex, u8DateLen, 0U);


            /* CODE set 0x09 to aborting transmit */
            FLEXCAN_MB_CODE_SET(u32TempAddr, 0x09U);

            tRetVal = FLEXCAN_E_OK;
        }
        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
        #endif

    return tRetVal;
}



/**
 * @brief Transfer Data length to DLC
 *
 * @param u32DataLen data length
 * @return DLC
 */
uint32_t FLEXCAN_DataLenToDlc(uint32_t u32DataLen)
{
    uint32_t u32Dlc;

    switch (u32DataLen)
    {
        case 0U:
        case 1U:
        case 2U:
        case 3U:
        case 4U:
        case 5U:
        case 6U:
        case 7U:
        case 8U:
        {
            u32Dlc = u32DataLen;
        }
        break;
        case 12U:
        {
            u32Dlc = 9U;
        }
        break;
        case 16U:
        {
            u32Dlc = 10U;
        }
        break;
        case 20U:
        {
            u32Dlc = 11U;
        }
        break;
        case 24U:
        {
            u32Dlc = 12U;
        }
        break;
        case 32U:
        {
            u32Dlc = 13U;
        }
        break;
        case 48U:
        {
            u32Dlc = 14U;
        }
        break;
        case 64U:
        {
            u32Dlc = 15U;

        }
        break;

        default:
            u32Dlc = 0U;
            break;
    }

    return u32Dlc;
}


/**
 * @brief Transfer DLC to Data length
 *
 * @param u32Dlc DLC Data Length
 * @return
 */
uint32_t FLEXCAN_DlcToDataLen(uint32_t u32Dlc)
{
    uint32_t u32DataLen;


    switch (u32Dlc)
    {
        case 0U:
        case 1U:
        case 2U:
        case 3U:
        case 4U:
        case 5U:
        case 6U:
        case 7U:
        case 8U:
        {
            u32DataLen = u32Dlc;
        }
        break;
        case 9U:
        {
            u32DataLen = 12U;
        }
        break;
        case 10U:
        {
            u32DataLen = 16U;
        }
        break;
        case 11U:
        {
            u32DataLen = 20U;
        }
        break;
        case 12U:
        {
            u32DataLen = 24U;
        }
        break;
        case 13U:
        {
            u32DataLen = 32U;
        }
        break;
        case 14U:
        {
            u32DataLen = 48U;
        }
        break;
        case 15U:
        {
            u32DataLen = 64U;
        }
        break;

        default:
            u32DataLen = 0U;
            break;
    }

    return u32DataLen;
}



#define DTC_E00888_ViuPdmCanBusOff 1
extern void set_DTC_Exist(uint8_t dtc_index, bool status);
extern void Set_DTCOccuCounter_Up(uint8_t dtc_index);
extern uint8_t DTC_checkTRC(uint8_t dtc_index);


/* ################################################################################## */
/* ############################## Interrupt Services ################################ */

/**
 * @brief Can process for interrupt
 *
 * @param pCanHandle  Can handle point
 */
void FLEXCAN_InterruptProcess(FLEXCAN_HandleType *pCanHandle)
{
    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON

    FLEXCAN_ErrorType     tRetVal;
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if ((tRetVal == FLEXCAN_E_OK) && (pCanHandle->tStatus.eStatusSeq >= FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
    }

    if (tRetVal == FLEXCAN_E_OK)
    {
    #endif
        FLEXCAN_Type         *pCan;
        pCan = s_aFlexCan_InstanceTable[(uint8_t)pCanHandle->eInstance];
#ifndef ECU_ADDRESS_BLDC
        /* check busoff interrupt*/
    //    pCan->CTRL1 |= 0x40;
        if(0 == Can_Hw_ChkBusOffStatus(pCanHandle->eInstance))
        {
    		set_DTC_Exist(DTC_E00888_ViuPdmCanBusOff, 1);

    		if(DTC_checkTRC(DTC_E00888_ViuPdmCanBusOff) == 1)
    		{
    	    	Set_DTCOccuCounter_Up(1);
    		}

        	Can_FlexCan_BusOff(pCanHandle->eInstance);
        }
#endif

        if(FLEXCAN_HWA_CheckErrorInterrupt(pCan))
        {
            /* check error interrupt */
            FLEXCAN_LL_ProcessError(pCanHandle, 1U);
        }

        /* check transmit interrupt */
        FLEXCAN_LL_InterruptTx(pCanHandle);

        /* check receive interrupt */
        FLEXCAN_LL_InterruptRx(pCanHandle);

        /* check legacy fifo interrupt */
        if (FLEXCAN_HWA_CheckLegacyFifoEn(pCan))
        {
            /* get fifo data only when dma disable */
            if(!FLEXCAN_HWA_CheckFifoDma(pCan))
            {
                if(FLEXCAN_HWA_CheckLegacyFifoDataInterrupt(pCan))
                {
                    FLEXCAN_LL_PollingLegacyFifoData(pCanHandle);
                }
            }

            if(FLEXCAN_HWA_CheckLegacyFifoWarningInterrupt(pCan))
            {
                FLEXCAN_LL_PollingLegacyFifoWarning(pCanHandle);
            }

            if(FLEXCAN_HWA_CheckLegacyFifoErrorInterrupt(pCan))
            {
                FLEXCAN_LL_PollingLegacyFifoError(pCanHandle);
            }
        }

        if(FLEXCAN_LL_CheckFdInstance(pCanHandle->eInstance) == 0)
        {
            /* check enhanced fifo interrupt */
            if (FLEXCAN_HWA_CheckEnhancedFIFOEn(pCan))
            {
                if(FLEXCAN_HWA_CheckEnhancedFifoDataInterrupt(pCan))
                {
                    FLEXCAN_LL_PollingEnhancedFifoData(pCanHandle);
                }

                if(FLEXCAN_HWA_CheckEnhancedFifoErrorInterrupt(pCan))
                {
                    FLEXCAN_LL_PollingEnhancedFifoError(pCanHandle);
                }
            }
        }

        FLEXCAN_LL_ProcessPNET(pCanHandle);

        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
    else
    {
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_PROCESS, FLEXCAN_E_INVALID_PARAM);
    }
        #endif
}

/**
 * @brief Can process for polling
 *
 * @param pCanHandle  Can handle point
 */
void FLEXCAN_PollingProcess(FLEXCAN_HandleType *pCanHandle)
{
    #if FLEXCAN_DEV_ERROR_REPORT == STD_ON

    FLEXCAN_ErrorType     tRetVal;
    /* check parameter */
    tRetVal = FLEXCAN_LL_CheckInstance(pCanHandle->eInstance);

    if ((tRetVal == FLEXCAN_E_OK) && (pCanHandle->tStatus.eStatusSeq >= FLEXCAN_SEQUENCE_NOTSTART))
    {
        tRetVal = FLEXCAN_E_OK;
    }
    else
    {
        tRetVal |= FLEXCAN_E_INVALID_SEQUENCE;
    }

    if (tRetVal == FLEXCAN_E_OK)
    {
    #endif
        FLEXCAN_Type         *pCan;
        pCan = s_aFlexCan_InstanceTable[(uint8_t)pCanHandle->eInstance];

        if(!FLEXCAN_HWA_CheckErrorInterrupt(pCan))
        {
            /* check error interrupt */
            FLEXCAN_LL_ProcessError(pCanHandle, 0U);
        }

        /* check transmit interrupt */
        FLEXCAN_LL_PollingTx(pCanHandle);

        FLEXCAN_LL_PollingRx(pCanHandle);


        /* check legacy fifo interrupt */
        if (FLEXCAN_HWA_CheckLegacyFifoEn(pCan))
        {
            /* get fifo data only when dma disable */
            if(!FLEXCAN_HWA_CheckFifoDma(pCan))
            {
                if(FLEXCAN_HWA_CheckLegacyFifoDataPolling(pCan))
                {
                    FLEXCAN_LL_PollingLegacyFifoData(pCanHandle);
                }
            }

            if(FLEXCAN_HWA_CheckLegacyFifoWarningPolling(pCan))
            {
                FLEXCAN_LL_PollingLegacyFifoWarning(pCanHandle);
            }

            if(FLEXCAN_HWA_CheckLegacyFifoErrorPolling(pCan))
            {
                FLEXCAN_LL_PollingLegacyFifoError(pCanHandle);
            }
        }

        if(FLEXCAN_LL_CheckFdInstance(pCanHandle->eInstance) == 0)
        {
            /* check enhanced fifo interrupt */
            if (FLEXCAN_HWA_CheckEnhancedFIFOEn(pCan))
            {
                if(FLEXCAN_HWA_CheckEnhancedFifoDataPolling(pCan))
                {
                    FLEXCAN_LL_PollingEnhancedFifoData(pCanHandle);
                }

                if(FLEXCAN_HWA_CheckEnhancedFifoErrorPolling(pCan))
                {
                    FLEXCAN_LL_PollingEnhancedFifoError(pCanHandle);
                }
            }
        }

        #if FLEXCAN_DEV_ERROR_REPORT == STD_ON
    }
    else
    {
        FLEXCAN_ReportDevError(FLEXCAN_DET_ERROR_ID_FUNC_PROCESS, FLEXCAN_E_INVALID_PARAM);
    }
        #endif
}

#endif
