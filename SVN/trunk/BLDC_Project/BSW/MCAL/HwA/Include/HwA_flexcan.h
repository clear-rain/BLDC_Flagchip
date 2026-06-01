/**
 * @file HwA_flexcan.h
 * @author Flagchip
 * @brief FLEXCAN hardware access layer
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
*   2.0.1       2024-08-20    Flagchip038   N/A          -- Check FIFO status with DMA flag
*                                                        -- Fix CAN get MB code with busy issue
*   2.0.2       2024-10-20    Flagchip038   N/A          Add Multi Iflag/IMask check
*   2.1.0      2025-02-19     Flagchip038   N/A          SRR bit must be same to IDE
*********************************************************************************/

#ifndef _HWA_FLEXCAN_H_
#define _HWA_FLEXCAN_H_

#include "device_header.h"


#if FLEXCAN_INSTANCE_COUNT > 0U


/* ################################################################################## */
/* ####################################### Macro #################################### */

/******************************* Message Buffer Structure **************************************/

/************************************************* 8bytes data ********************************************************/
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)              |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */


/************************************************* 16bytes data *******************************************************/
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)              |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */
/*                                        ................................                                              */
/* 0x1C  |    Data Byte 12                    |     Data Byte 13                  |     Data Byte 14    | Data Byte 15| */


/************************************************* 32bytes data *******************************************************/
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)               |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */
/*                                        ................................                                              */
/* 0x30  |    Data Byte 28                    |     Data Byte 29                  |     Data Byte 30    | Data Byte 31| */


/************************************************* 64bytes data *******************************************************/
/*         31    30    29    28   27 26 25 24   23   22    21    20   19 18 17 16  15 14 13 12 11 10 9 8 7 6 5 4 3 2 1  */
/* 0x00  | EDL | BRS | ESI |    |    CODE     |    | SRR | IDE | RTR |    DLC     |          TIME STAMP               | */
/* 0x04  |       PRIO      |         ID (STD/EXT high 11bits)              |           ID (EXT low 18bits)            | */
/* 0x08  |    Data Byte 0                     |     Data Byte 1                   |     Data Byte 2     | Data Byte 3 | */
/* 0x0C  |    Data Byte 4                     |     Data Byte 5                   |     Data Byte 6     | Data Byte 7 | */
/*                                        ................................                                              */
/* 0x44  |    Data Byte 60                    |     Data Byte 61                  |     Data Byte 62    | Data Byte 63| */


/**
 * @defgroup HwA_flexcan HwA_flexcan
 * @ingroup module_driver_flexcan
 * @{
 */


/* Register address with offset */
#define FLEXCAN_REGISTER_WITHOFFSET2(reg,offset1)                ((uint32_t)(reg)+(uint32_t)(offset1))
/* Register address with offset */
#define FLEXCAN_REGISTER_WITHOFFSET(reg,offset1,offset2)                ((uint32_t)(reg)+(uint32_t)(offset1)+(uint32_t)(offset2))
/* Get register value */
#define FLEXCAN_REG32_CONTENT(reg)                                        (*((uint32_t*)(reg)))




/** @brief U32 value around */
#define FLEXCAN_U32MACRO(var)                                           ((uint32_t)(var))
/** @brief U32 value shift */
#define FLEXCAN_U32SHIFT(var,mask,shift)                                ((uint32_t)((((uint32_t)(var))&(mask))<<(shift)))
/** @brief U32 value shift and revert */
#define FLEXCAN_U32NOTSHIFT(mask,shift)                                 ((uint32_t)(~(((uint32_t)(mask))<<(shift))))

/** @breif Flexcan SRR bit mask */
#define FLEXCAN_MB_SRR_MASK_U32                                         0x00400000U

/* legacy message buffer */

/** @brief Legacy/EnHanced Message Buffer Header */
#define FLEXCAN_MB_HEADER_BYTELEN                                       8UL
/** @brief Legacy Message Buffer Address */
#define FLEXCAN_MB_ADDR(mbOffset, mbIndex, dataLen)                     FLEXCAN_U32MACRO(FLEXCAN_U32MACRO(mbOffset)+FLEXCAN_U32MACRO(mbIndex)*(FLEXCAN_U32MACRO(dataLen)+FLEXCAN_MB_HEADER_BYTELEN))


/** @brief Legacy Message Buffer word n Address */
#define FLEXCAN_MB_WORDN_ADDR(mbOffset, mbIndex, dataLen, offset)       (FLEXCAN_MB_ADDR((mbOffset), (mbIndex), (dataLen))+FLEXCAN_U32MACRO(offset))

/** @brief check mb data length */
#define FLEXCAN_MB_GET_DATALEN(mbindex, mbNum, datalenNum, datalenarray)     ((uint8_t)(datalenarray[( ((mbindex)*(datalenNum)/(mbNum)) )]))

/** @brief Legacy Message Buffer Data Address */
/* #define FLEXCAN_MB_DATA_ADDR_GET(mbOffset, mbIndex, dataLen)            (FLEXCAN_MB_WORDN_ADDR((mbOffset), (mbIndex), (dataLen),2U)) */

/** @brief Legacy Message Buffer EDL Get */
#define FLEXCAN_MB_EDL_GET(edlAddr)                                     ((FLEXCAN_REG32_CONTENT(edlAddr)>>31)&0x01U)
/** @brief Legacy Message Buffer EDL Clear */
#define FLEXCAN_MB_EDL_CLR(edlAddr)                                     (FLEXCAN_REG32_CONTENT(edlAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,31))
/** @brief Legacy Message Buffer EDL Attach */
#define FLEXCAN_MB_EDL_ATTACH(edlAddr,var)                              (FLEXCAN_REG32_CONTENT(edlAddr) |= FLEXCAN_U32SHIFT(var,0x01U,31))
/** @brief Legacy Message Buffer EDL Set */
#define FLEXCAN_MB_EDL_SET(edlAddr,var)                                 FLEXCAN_REG32_CONTENT(edlAddr) =  ((FLEXCAN_REG32_CONTENT(edlAddr) & FLEXCAN_U32NOTSHIFT(0x01U,31)) | FLEXCAN_U32SHIFT(var,0x01U,31))


/** @brief Legacy Message Buffer BRS Get */
#define FLEXCAN_MB_BRS_GET(brsAddr)                                     (((FLEXCAN_REG32_CONTENT(brsAddr))>>30)&0x01U)
/** @brief Legacy Message Buffer BRS Clear */
#define FLEXCAN_MB_BRS_CLR(brsAddr)                                     (FLEXCAN_REG32_CONTENT(brsAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,30))
/** @brief Legacy Message Buffer BRS Attach */
#define FLEXCAN_MB_BRS_ATTACH(brsAddr,var)                              (FLEXCAN_REG32_CONTENT(brsAddr) |= FLEXCAN_U32SHIFT(var,0x01U,30))
/** @brief Legacy Message Buffer BRS set */
#define FLEXCAN_MB_BRS_SET(brsAddr,var)                                 FLEXCAN_REG32_CONTENT(brsAddr) =  ((FLEXCAN_REG32_CONTENT(brsAddr) & FLEXCAN_U32NOTSHIFT(0x01U,30)) | FLEXCAN_U32SHIFT(var,0x01U,30))

/** @brief Legacy Message Buffer ESI Get */
#define FLEXCAN_MB_ESI_GET(esiAddr)                                     (((FLEXCAN_REG32_CONTENT(esiAddr))>>29)&0x01U)
/** @brief Legacy Message Buffer ESI Clear */
#define FLEXCAN_MB_ESI_CLR(esiAddr)                                     (FLEXCAN_REG32_CONTENT(esiAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,29))
/** @brief Legacy Message Buffer ESI Attach */
#define FLEXCAN_MB_ESI_ATTACH(esiAddr,var)                              (FLEXCAN_REG32_CONTENT(esiAddr) |= FLEXCAN_U32SHIFT(var,0x01U,29))
/** @brief Legacy Message Buffer ESI Set */
#define FLEXCAN_MB_ESI_SET(esiAddr,var)                                 FLEXCAN_REG32_CONTENT(esiAddr) =  ((FLEXCAN_REG32_CONTENT(esiAddr) & FLEXCAN_U32NOTSHIFT(0x01U,29)) | FLEXCAN_U32SHIFT(var,0x01U,29))

/** @brief Legacy Message Buffer CODE Get */
#define FLEXCAN_MB_CODE_GET(codeAddr)                                   (((FLEXCAN_REG32_CONTENT(codeAddr))>>24)&0x0EU)
/** @brief Legacy Message Buffer CODE Clear */
#define FLEXCAN_MB_CODE_CLR(codeAddr)                                   (FLEXCAN_REG32_CONTENT(codeAddr) &= FLEXCAN_U32NOTSHIFT(0x0FU,24))
/** @brief Legacy Message Buffer CODE Attach */
#define FLEXCAN_MB_CODE_ATTACH(codeAddr,var)                            (FLEXCAN_REG32_CONTENT(codeAddr) |= FLEXCAN_U32SHIFT(var,0x0FU,24))
/** @brief Legacy Message Buffer CODE set */
#define FLEXCAN_MB_CODE_SET(codeAddr,var)                               FLEXCAN_REG32_CONTENT(codeAddr) =  ((FLEXCAN_REG32_CONTENT(codeAddr) & FLEXCAN_U32NOTSHIFT(0x0FU,24)) | FLEXCAN_U32SHIFT(var,0x0FU,24))


/** @brief Legacy Message Buffer SRR Get */
#define FLEXCAN_MB_SRR_GET(srrAddr)                                     (((FLEXCAN_REG32_CONTENT(srrAddr)) >>22)&0x01U)
/** @brief Legacy Message Buffer SRR Clear */
#define FLEXCAN_MB_SRR_CLR(srrAddr)                                     (FLEXCAN_REG32_CONTENT(srrAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,22))
/** @brief Legacy Message Buffer SRR Attach */
#define FLEXCAN_MB_SRR_ATTACH(srrAddr,var)                              (FLEXCAN_REG32_CONTENT(srrAddr) |= FLEXCAN_U32SHIFT(var,0x01U,22))
/** @brief Legacy Message Buffer SRR set */
#define FLEXCAN_MB_SRR_SET(srrAddr,var)                                 FLEXCAN_REG32_CONTENT(srrAddr) =  ((FLEXCAN_REG32_CONTENT(srrAddr) & FLEXCAN_U32NOTSHIFT(0x0FU,22)) | FLEXCAN_U32SHIFT(var,0x0FU,22))

/** @brief Legacy Message Buffer IDE Get */
#define FLEXCAN_MB_IDE_GET(ideAddr)                                     (((FLEXCAN_REG32_CONTENT(ideAddr))>>21)&0x01U)
/** @brief Legacy Message Buffer IDE Clear */
#define FLEXCAN_MB_IDE_CLR(ideAddr)                                     (FLEXCAN_REG32_CONTENT(ideAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,21))
/** @brief Legacy Message Buffer IDE Attach */
#define FLEXCAN_MB_IDE_ATTACH(ideAddr,var)                              (FLEXCAN_REG32_CONTENT(ideAddr) |= FLEXCAN_U32SHIFT(var,0x01U,21))
/** @brief Legacy Message Buffer IDE set with SRR */
#define FLEXCAN_MB_IDE_SRR_SET(ideAddr,var)                              FLEXCAN_REG32_CONTENT(ideAddr) =  ((FLEXCAN_REG32_CONTENT(ideAddr) & FLEXCAN_U32NOTSHIFT(0x03U,21)) | FLEXCAN_U32SHIFT(var,0x03U,21))


/** @brief Legacy Message Buffer RTR Get */
#define FLEXCAN_MB_RTR_GET(rtrAddr)                                     (((FLEXCAN_REG32_CONTENT(rtrAddr))>>20)&0x01U)
/** @brief Legacy Message Buffer RTR Clear */
#define FLEXCAN_MB_RTR_CLR(rtrAddr)                                     (FLEXCAN_REG32_CONTENT(rtrAddr) &= FLEXCAN_U32NOTSHIFT(0x01U,20))
/** @brief Legacy Message Buffer RTR Attach */
#define FLEXCAN_MB_RTR_ATTACH(rtrAddr,var)                              (FLEXCAN_REG32_CONTENT(rtrAddr) |= FLEXCAN_U32SHIFT(var,0x01U,20))
/** @brief Legacy Message Buffer RTR set */
#define FLEXCAN_MB_RTR_SET(rtrAddr,var)                                 FLEXCAN_REG32_CONTENT(rtrAddr) =  ((FLEXCAN_REG32_CONTENT(rtrAddr) & FLEXCAN_U32NOTSHIFT(0x01U,20)) | FLEXCAN_U32SHIFT(var,0x01U,20))

/** @brief Legacy Message Buffer DLC Get */
#define FLEXCAN_MB_DLC_GET(dlcAddr)                                     (((FLEXCAN_REG32_CONTENT(dlcAddr))>>16)&0x0FU)
/** @brief Legacy Message Buffer DLC Clear */
#define FLEXCAN_MB_DLC_CLR(dlcAddr)                                     (FLEXCAN_REG32_CONTENT(dlcAddr) &= FLEXCAN_U32NOTSHIFT(0x0FU,16))
/** @brief Legacy Message Buffer DLC Attach */
#define FLEXCAN_MB_DLC_ATTACH(dlcAddr,var)                              (FLEXCAN_REG32_CONTENT(dlcAddr) |= FLEXCAN_U32SHIFT(var,0x0FU,16))
/** @brief Legacy Message Buffer DLC Set */
#define FLEXCAN_MB_DLC_SET(dlcAddr,var)                                 FLEXCAN_REG32_CONTENT(dlcAddr) =  ((FLEXCAN_REG32_CONTENT(dlcAddr) & FLEXCAN_U32NOTSHIFT(0x0FU,16)) | FLEXCAN_U32SHIFT(var,0x0FU,16))

/** @brief Legacy Message Buffer TIME STAMP Get */
#define FLEXCAN_MB_TIMESTAMP_GET(timestampAddr)                         (FLEXCAN_REG32_CONTENT(timestampAddr)&0xFFFFU)
/** @brief Legacy Message Buffer TIME STAMP Clear */
#define FLEXCAN_MB_TIMESTAMP_CLR(timestampAddr)                         (FLEXCAN_REG32_CONTENT(timestampAddr) &= FLEXCAN_U32NOTSHIFT(0xFFFFU,0))
/** @brief Legacy Message Buffer TIME STAMP Attach */
#define FLEXCAN_MB_TIMESTAMP_ATTACH(timestampAddr,var)                  (FLEXCAN_REG32_CONTENT(timestampAddr) |= FLEXCAN_U32SHIFT(var,0xFFFFU,0))
/** @brief Legacy Message Buffer TIME STAMP Set */
#define FLEXCAN_MB_TIMESTAMP_SET(timestampAddr,var)                     FLEXCAN_REG32_CONTENT(timestampAddr) =  ((FLEXCAN_REG32_CONTENT(timestampAddr) & FLEXCAN_U32NOTSHIFT(0xFFFFU,0)) | FLEXCAN_U32SHIFT(var,0xFFFFU,0))

/** @brief Legacy Message Buffer PRIO Get */
#define FLEXCAN_MB_PRIO_GET(prioAddr)                                   (((FLEXCAN_REG32_CONTENT(prioAddr))>>29)&0x07U)
/** @brief Legacy Message Buffer PRIO Clear */
#define FLEXCAN_MB_PRIO_CLR(prioAddr)                                   (FLEXCAN_REG32_CONTENT(prioAddr) &= FLEXCAN_U32NOTSHIFT(0x07U,29))
/** @brief Legacy Message Buffer PRIO Attach */
#define FLEXCAN_MB_PRIO_ATTACH(prioAddr,var)                            (FLEXCAN_REG32_CONTENT(prioAddr) |= FLEXCAN_U32SHIFT(var,0x07U,29))
/** @brief Legacy Message Buffer PRIO Set */
#define FLEXCAN_MB_PRIO_SET(prioAddr,var)                               FLEXCAN_REG32_CONTENT(prioAddr) =  ((FLEXCAN_REG32_CONTENT(prioAddr) & FLEXCAN_U32NOTSHIFT(0x07U,29)) | FLEXCAN_U32SHIFT(var,0x07U,29))

/** @brief Legacy Message Buffer STD ID Get */
#define FLEXCAN_MB_STDID_GET(stdidAddr)                                 (((FLEXCAN_REG32_CONTENT(stdidAddr))>>18)&0x7FFU)
/** @brief Legacy Message Buffer STD ID CLR */
#define FLEXCAN_MB_STDID_CLR(stdidAddr)                                 (FLEXCAN_REG32_CONTENT(stdidAddr) &= FLEXCAN_U32NOTSHIFT(0x7FFU,18))
/** @brief Legacy Message Buffer STD ID Attach */
#define FLEXCAN_MB_STDID_ATTACH(stdidAddr,var)                          (FLEXCAN_REG32_CONTENT(stdidAddr) |= FLEXCAN_U32SHIFT(var,0x7FFU,18))
/** @brief Legacy Message Buffer STD ID set */
#define FLEXCAN_MB_STDID_SET(stdidAddr,var)                             FLEXCAN_REG32_CONTENT(stdidAddr) =  ((FLEXCAN_REG32_CONTENT(stdidAddr) & FLEXCAN_U32NOTSHIFT(0x7FFU,18)) | FLEXCAN_U32SHIFT(var,0x7FFU,18))

/** @brief Legacy Message Buffer EXT ID Get */
#define FLEXCAN_MB_EXTID_GET(extidAddr)                                 ((FLEXCAN_REG32_CONTENT(extidAddr))&0x1FFFFFFF)
/** @brief Legacy Message Buffer EXT ID Clear */
#define FLEXCAN_MB_EXTID_CLR(extidAddr)                                 (FLEXCAN_REG32_CONTENT(extidAddr) &= FLEXCAN_U32NOTSHIFT(0x1FFFFFFF,0))
/** @brief Legacy Message Buffer EXT ID Attach */
#define FLEXCAN_MB_EXTID_ATTACH(extidAddr,var)                          (FLEXCAN_REG32_CONTENT(extidAddr) |= FLEXCAN_U32SHIFT(var,0x1FFFFFFF,0))
/** @brief Legacy Message Buffer EXT ID set */
#define FLEXCAN_MB_EXTID_SET(extidAddr,var)                             FLEXCAN_REG32_CONTENT(extidAddr) =  ((FLEXCAN_REG32_CONTENT(extidAddr) & FLEXCAN_U32NOTSHIFT(0x1FFFFFFF,0)) | FLEXCAN_U32SHIFT(var,0x1FFFFFFF,0))

/* enhanced fifo message buffer */

/** @brief Enhanced FIFO Message Buffer EDL Get */
#define FLEXCAN_EFIFOMB_EDL_GET()                                     ((pCan->ERX_FIFO[0U]>>31)&0x01U)

/** @brief Enhanced FIFO Message Buffer BRS Get */
#define FLEXCAN_EFIFOMB_BRS_GET()                                     ((pCan->ERX_FIFO[0U]>>30)&0x01U)

/** @brief Enhanced FIFO Message Buffer ESI Get */
#define FLEXCAN_EFIFOMB_ESI_GET()                                     ((pCan->ERX_FIFO[0U]>>29)&0x01U)

/** @brief Enhanced FIFO Message Buffer SRR Get */
#define FLEXCAN_EFIFOMB_SRR_GET()                                     ((pCan->ERX_FIFO[0U] >>22)&0x01U)

/** @brief Enhanced FIFO Message Buffer IDE Get */
#define FLEXCAN_EFIFOMB_IDE_GET()                                     ((pCan->ERX_FIFO[0U]>>21)&0x01U)

/** @brief Enhanced FIFO Message Buffer RTR Get */
#define FLEXCAN_EFIFOMB_RTR_GET()                                     ((pCan->ERX_FIFO[0U]>>20)&0x01U)

/** @brief Enhanced FIFO Message Buffer DLC Get */
#define FLEXCAN_EFIFOMB_DLC_GET()                                     ((pCan->ERX_FIFO[0U]>>16)&0x0FU)

/** @brief Enhanced FIFO Message Buffer TIME STAMP Get */
#define FLEXCAN_EFIFOMB_TIMESTAMP_GET()                               (pCan->ERX_FIFO[0U]&0xFFU)

/** @brief Enhanced FIFO Message Buffer STD ID Get */
#define FLEXCAN_EFIFOMB_STDID_GET()                                   ((pCan->ERX_FIFO[1U]>>18)&0x7FFU)

/** @brief Enhanced FIFO Message Buffer EXT ID Get */
#define FLEXCAN_EFIFOMB_EXTID_GET()                                   (pCan->ERX_FIFO[1U]&0x1FFFFFFF)

/** @brief Enhanced FIFO Message Buffer Data Get */
#define FLEXCAN_EFIFOMB_DATAADDR_GET(wordIndex)                       (&(pCan->ERX_FIFO[2U+(wordIndex)]))

/** @brief Enhanced FIFO Message Buffer IDHIT Get */
#define FLEXCAN_EFIFOMB_IDHIT_GET(dataWordLen)                        ((pCan->ERX_FIFO[2U+(dataWordLen)])&0x1FFU)

/** @brief Enhanced FIFO Message Buffer HR Time Stamp Get */
#define FLEXCAN_EFIFOMB_HRTIMESTAMP_GET(dataWordLen)                  (pCan->ERX_FIFO[3U+(dataWordLen)])

/* enhanced fifo message buffer from user buffer*/

/** @brief Enhanced FIFO Message Buffer EDL Get */
#define FLEXCAN_EFIFOMB_EDL_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>31)&0x01U)

/** @brief Enhanced FIFO Message Buffer BRS Get */
#define FLEXCAN_EFIFOMB_BRS_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>30)&0x01U)

/** @brief Enhanced FIFO Message Buffer ESI Get */
#define FLEXCAN_EFIFOMB_ESI_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>29)&0x01U)

/** @brief Enhanced FIFO Message Buffer SRR Get */
#define FLEXCAN_EFIFOMB_SRR_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U] >>22)&0x01U)

/** @brief Enhanced FIFO Message Buffer IDE Get */
#define FLEXCAN_EFIFOMB_IDE_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>21)&0x01U)

/** @brief Enhanced FIFO Message Buffer RTR Get */
#define FLEXCAN_EFIFOMB_RTR_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>20)&0x01U)

/** @brief Enhanced FIFO Message Buffer DLC Get */
#define FLEXCAN_EFIFOMB_DLC_GET_FROM_BUFFER(Addr)                                     ((((uint32_t*)Addr)[0U]>>16)&0x0FU)

/** @brief Enhanced FIFO Message Buffer TIME STAMP Get */
#define FLEXCAN_EFIFOMB_TIMESTAMP_GET_FROM_BUFFER(Addr)                               (((uint32_t*)Addr)[0U]&0xFFU)

/** @brief Enhanced FIFO Message Buffer STD ID Get */
#define FLEXCAN_EFIFOMB_STDID_GET_FROM_BUFFER(Addr)                                   ((((uint32_t*)Addr)[1U]>>18)&0x7FFU)

/** @brief Enhanced FIFO Message Buffer EXT ID Get */
#define FLEXCAN_EFIFOMB_EXTID_GET_FROM_BUFFER(Addr)                                   (((uint32_t*)Addr)[1U]&0x1FFFFFFF)

/** @brief Enhanced FIFO Message Buffer Data Get */
#define FLEXCAN_EFIFOMB_DATAADDR_GET_FROM_BUFFER(Addr, wordIndex)                      (&(((uint32_t*)Addr)[2U+(wordIndex)]))

/** @brief Enhanced FIFO Message Buffer IDHIT Get */
#define FLEXCAN_EFIFOMB_IDHIT_GET_FROM_BUFFER(Addr, dataWordLen)                       ((((uint32_t*)Addr)[2U+(dataWordLen)])&0x1FFU)

/** @brief Enhanced FIFO Message Buffer HR Time Stamp Get */
#define FLEXCAN_EFIFOMB_HRTIMESTAMP_GET_FROM_BUFFER(Addr, dataWordLen)                 (((uint32_t*)Addr)[3U+(dataWordLen)])

/* ################################################################################## */
/* ################################### Type define ################################## */

/**
 * @brief  FLEXCAN Clock Source Select Enumeration
 *
 */
typedef enum
{
    FLEXCAN_CLOCK_CANPE = 0x00U,      /**< FLEXCAN_CLOCK_CANPE  clock from can peripheral clock */
    FLEXCAN_CLOCK_INTERFACE = 0x01U   /**< FLEXCAN_CLOCK_INTERFACE  clock from can interface clock     */
} FLEXCAN_ClockSrcType;

/**
 * @brief FLEXCAN data length type
 *
 */
typedef enum
{
    FLEXCAN_DATAWIDTH_8  = 8U, /**< FLEXCAN_DATALEN_8  8 bytes data width  */
    FLEXCAN_DATAWIDTH_16 = 16U,/**< FLEXCAN_DATALEN_16 16 bytes data width */
    FLEXCAN_DATAWIDTH_32 = 32U,/**< FLEXCAN_DATALEN_32 32 bytes data width */
    FLEXCAN_DATAWIDTH_64 = 64U /**< FLEXCAN_DATALEN_64 64 bytes data width */

} FLEXCAN_DataWidthType;

/**
 * @brief CAN Pretended Network Filter type
 *
 */
typedef enum
{
    FLEXCAN_PNET_ID_FILTER = 0U,                       /**< FLEXCAN_PNET_ID_FILTER only ID filter */
    FLEXCAN_PNET_ID_AND_PAYLOAD_FILTER = 1U,           /**< FLEXCAN_PNET_ID_AND_PAYLOAD_FILTER id and payload filter */
    FLEXCAN_PNET_ID_FILTER_WITH_NCOUNT = 2U,           /**< FLEXCAN_PNET_ID_FILTER_WITH_NCOUNT id with count */
    FLEXCAN_PNET_ID_AND_PAYLOAD_FILTER_WITH_NCOUNT = 3U/**< FLEXCAN_PNET_ID_AND_PAYLOAD_FILTER_WITH_NCOUNT id and payload with count */
}FLEXCAN_PNET_FilterType;

/**
 * @brief CAN Pretended Network ID Filter type
 *
 */
typedef enum
{
    FLEXCAN_PNET_ID_FILTER_SAME = 0U,         /**< FLEXCAN_PNET_ID_FILTER_SAME id with mask check match */
    FLEXCAN_PNET_ID_FILTER_GREATER_EQUAL = 1U,/**< FLEXCAN_PNET_ID_FILTER_GREATER_EQUAL only match greater and equal ID1 */
    FLEXCAN_PNET_ID_FILTER_SMALLER_EQUAL = 2U,/**< FLEXCAN_PNET_ID_FILTER_SMALLER_EQUAL only match less and equal ID1 */
    FLEXCAN_PNET_ID_FILTER_RANGE = 3U         /**< FLEXCAN_PNET_ID_FILTER_RANGE greater and equal ID1 and less and equal ID2 */
}FLEXCAN_PNET_IdFilterType;

/**
 * @brief CAN Pretended Network Payload Filter type
 *
 */
typedef enum
{
    FLEXCAN_PNET_PAYLOAD_FILTER_SAME = 0U,         /**< FLEXCAN_PNET_PAYLOAD_FILTER_SAME payload with mask check match, FLT_DLC_LO must equal to FLT_DLC_HI */
    FLEXCAN_PNET_PAYLOAD_FILTER_GREATER_EQUAL = 1U,/**< FLEXCAN_PNET_PAYLOAD_FILTER_GREATER_EQUAL payload greater and equal than PL1_HI+PL1_LO */
    FLEXCAN_PNET_PAYLOAD_FILTER_SMALLER_EQUAL = 2U,/**< FLEXCAN_PNET_PAYLOAD_FILTER_SMALLER_EQUAL payload less and equal than PL1_HI+PL1_LO */
    FLEXCAN_PNET_PAYLOAD_FILTER_RANGE = 3U         /**< FLEXCAN_PNET_PAYLOAD_FILTER_RANGE payload greater and equal than PL1_HI+PL1_LO and less and equal than PL2_HI+PL2_LO */
}FLEXCAN_PNET_PayloadFilterType;

/* ################################################################################## */
/* ################################## Local Inline ################################## */



/**
 * @brief Set Module Disable
 *
 * @param pCan FLEXCAN instance value
 * @param bDisable set whether disable
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMcrDisable(FLEXCAN_Type *const pCan, uint8_t bDisable)
{
    if (bDisable == TRUE)
    {
        pCan->MCR |= FLEXCAN_MCR_MDIS_MASK;         /* bitMDIS=1: Disable module before selecting clock     */
    }
    else
    {
        pCan->MCR &= ~FLEXCAN_MCR_MDIS_MASK;
    }
}

/**
 * @brief Set Module Freeze
 *
 * @param pCan FLEXCAN instance value
 * @param bFreeze set whether freeze
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMcrFreeze(FLEXCAN_Type *const pCan, uint8_t bFreeze)
{
    if (bFreeze == TRUE)
    {
        pCan->MCR |= FLEXCAN_MCR_FRZ_MASK;         /* bitMDIS=1: Disable module before selecting clock     */
    }
    else
    {
        pCan->MCR &= ~FLEXCAN_MCR_FRZ_MASK;
    }
}


/**
 * @brief Set Module Halt and Freeze
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetHaltFreeze(FLEXCAN_Type *const pCan)
{
    pCan->MCR |= FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK;
}

/**
 * @brief Wait FLEXCAN Module Enter Freezen mode
 *
 * @param pCan FLEXCAN instance value
 * @param u32TimeoutTick Timeout tick
 * @return 0U is really in freezen mode
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrFreezen(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    /* wait for bitFRZACK=1 on freeze mode entry/exit */
    while ( (!((pCan->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT))  && (u32TimeoutTick-->0U) )
    {

    }

    return (u32TimeoutTick==0U);
}

/**
 * @brief Wait FLEXCAN Module Exit Freezen mode
 *
 * @param pCan FLEXCAN instance value
 * @param u32TimeoutTick Timeout tick
 * @return 1U is really in freezen mode
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrExitFreezen(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    while ( ((pCan->MCR & FLEXCAN_MCR_FRZACK_MASK) >> FLEXCAN_MCR_FRZACK_SHIFT)   && (u32TimeoutTick-->0U) )
    {}
    /*  wait for bitFRZACK to clear (not in freeze mode) */

    return (u32TimeoutTick==0U);
}

/**
 * @brief Wait FLEXCAN Module Ready
 *
 * @param pCan FLEXCAN instance value
 * @param u32TimeoutTick Timeout tick
 * @return 1U is really ready
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrReady(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    while ( ((pCan->MCR & FLEXCAN_MCR_NOTRDY_MASK) >> FLEXCAN_MCR_NOTRDY_SHIFT)    && (u32TimeoutTick-->0U) )
    {}
    /*  wait for bitNOTRDY to clear (module ready) */

    return (u32TimeoutTick==0U);
}

/**
 * @brief Wait FLEXCAN Module Not Ready
 *
 * @param pCan FLEXCAN instance value
 * @param u32TimeoutTick Timeout tick
 * @return 1U is really not ready
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_WaitMcrNoReady(FLEXCAN_Type *const pCan, uint32_t u32TimeoutTick)
{
    while ( (!((pCan->MCR & FLEXCAN_MCR_NOTRDY_MASK) >> FLEXCAN_MCR_NOTRDY_SHIFT))  && (u32TimeoutTick-->0U) )
    {}
    /*  wait for bitNOTRDY to set (module ready) */

    return (u32TimeoutTick==0U);
}

/**
 * @brief Set FLEXCAN MCR value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMCR(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->MCR = u32Value;
}

/**
 * @brief Get FLEXCAN MCR value
 *
 * @param pCan FLEXCAN instance value
 * @return MCR value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetMCR(FLEXCAN_Type *const pCan)
{
    return (uint32_t)pCan->MCR;
}

/**
 * @brief Attach FLEXCAN MCR value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value attached value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMCR(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->MCR |= u32Value;
}

/**
 * @brief Check FLEXCAN LegacyFifo Enabled
 *
 * @param pCan FLEXCAN instance value
 * @return 0 is disable, others are enabled
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoEn(FLEXCAN_Type *const pCan)
{
    return (uint32_t)pCan->MCR & FLEXCAN_MCR_RFEN_MASK;
}

/**
 * @brief Check if fifo dma enable
 *
 * @param pCan FLEXCAN instance value
 * @return 0 is none, others is dma enabled
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckFifoDma(FLEXCAN_Type *const pCan)
{
    return (pCan->MCR  & FLEXCAN_MCR_DMA_MASK);
}

/**
 * @brief Check if it is in pretended mode
 *
 * @param pCan FLEXCAN instance value
 * @param bEntryPNET if entry or out of pretended network
 * @param u32TimeoutTick timeout counter of tick
 * @return 0 is not ok, other is ok
 */
LOCAL_INLINE uint8_t FLEXCAN_HWA_CheckPNETAck(FLEXCAN_Type *const pCan, uint8_t bEntryPNET, uint32_t u32TimeoutTick)
{
    if(bEntryPNET)
    {
        while ( (!(pCan->MCR & FLEXCAN_MCR_LPMACK_MASK))  && (u32TimeoutTick-->0U) )
        {}
        /*  wait for bit LPMACK to set (low power mode ready) */
    }
    else
    {
        while ( (pCan->MCR & FLEXCAN_MCR_LPMACK_MASK)  && (u32TimeoutTick-->0U) )
        {}
    }

    return (u32TimeoutTick==0U);

}

/**
 * @brief Set FLEXCAN baudrate clock source
 *
 * @param pCan FLEXCAN instance value
 * @param tBaudClk Baudrate clock source
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCtrl1BaudSrc(FLEXCAN_Type *const pCan, FLEXCAN_ClockSrcType tBaudClk)
{
    if (tBaudClk == FLEXCAN_CLOCK_INTERFACE)
    {
        pCan->CTRL1 |= FLEXCAN_CTRL1_CLKSRC_MASK;
    }
    else
    {
        pCan->CTRL1 &= ~FLEXCAN_CTRL1_CLKSRC_MASK;
    }
}

/**
 * @brief Set FLEXCAN ctrl1 value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCtrl1(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL1 = u32Value;
}

/**
 * @brief Attach FLEXCAN ctrl1 value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value attached value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachCtrl1(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL1 |= u32Value;
}

/**
 * @brief Get FLEXCAN ctrl1 value
 *
 * @param pCan FLEXCAN instance value
 * @return CTRL1 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetCtrl1(FLEXCAN_Type *const pCan)
{
    return pCan->CTRL1;
}


/**
 * @brief Set CTRL2 value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCtrl2(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL2 = u32Value;
}

/**
 * @brief Attach FLEXCAN ctrl2 value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value attached value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachCtrl2(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CTRL2 |= u32Value;
}

/**
 * @brief Get CTRL2 value
 *
 * @param pCan FLEXCAN instance value
 * @return CTRL2 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetCtrl2(FLEXCAN_Type *const pCan)
{
    return pCan->CTRL2;
}


/**
 * @brief Check Interrupt Mask
 *
 * @param pCan FLEXCAN instance value
 * @return 0 is disable, others is enable
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckErrorInterrupt(FLEXCAN_Type *const pCan)
{
    return ( (FLEXCAN_HWA_GetCtrl1(pCan) & (FLEXCAN_CTRL1_BOFFMSK_MASK | FLEXCAN_CTRL1_ERRMSK_MASK | FLEXCAN_CTRL1_TWRNMSK_MASK | FLEXCAN_CTRL1_RWRNMSK_MASK )) |
                   (FLEXCAN_HWA_GetCtrl2(pCan) & ( FLEXCAN_CTRL2_ERRMSK_FAST_MASK | FLEXCAN_CTRL2_BOFFDONEMSK_MASK)) );
}


/**
 * @brief Clear IFLAG1 Flag
 *
 * @param pCan FLEXCAN instance value
 * @param u32W1cFlag write clear value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFlag1(FLEXCAN_Type *const pCan, uint32_t u32W1cFlag)
{
    pCan->IFLAG1 = u32W1cFlag;
}

#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
/**
 * @brief Clear IFLAG2 Flag
 *
 * @param pCan FLEXCAN instance value
 * @param u32W1cFlag write clear value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFlag2(FLEXCAN_Type *const pCan, uint32_t u32W1cFlag)
{
    pCan->IFLAG2 = u32W1cFlag;
}
#endif

#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
/**
 * @brief Clear IFLAG3 Flag
 *
 * @param pCan FLEXCAN instance value
 * @param u32W1cFlag write clear value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFlag3(FLEXCAN_Type *const pCan, uint32_t u32W1cFlag)
{
    pCan->IFLAG3 = u32W1cFlag;
}
#endif


/**
 * @brief Get IFLAG1 Flag
 *
 * @param pCan FLEXCAN instance value
 * @return flag1 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetFlag1(FLEXCAN_Type *const pCan)
{
    return pCan->IFLAG1;
}

#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
/**
 * @brief Get IFLAG2 Flag
 *
 * @param pCan FLEXCAN instance value
 * @return flag2 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetFlag2(FLEXCAN_Type *const pCan)
{
    return pCan->IFLAG2;
}
#endif

#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
/**
 * @brief Get IFLAG3 Flag
 *
 * @param pCan FLEXCAN instance value
 * @return flag3 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetFlag3(FLEXCAN_Type *const pCan)
{
    return pCan->IFLAG3;
}

#endif

/**
 * @brief Clear Rx Flag and unlock MB
 *
 * @param pCan FLEXCAN instance value
 * @param u32MbIndex Message Buffer Index
 */
LOCAL_INLINE void FLEXCAN_HWA_UnlockMbNoFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    (void)pCan->TIMER;     /* Read TIMER to unlock message buffers */
    if(u32MbIndex<32)
    {
        pCan->IFLAG1 = 1U << u32MbIndex;
    }
#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    else if(u32MbIndex < 64)
    {
        pCan->IFLAG2 = 1U << (u32MbIndex-32);
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    else if(u32MbIndex < 96)
    {
        pCan->IFLAG3 = 1U << (u32MbIndex-64);
    }
#endif
    else
    {

    }
}

/**
 * @brief Clear MB Flag
 *
 * @param pCan FLEXCAN instance value
 * @param u32MbIndex Message Buffer Index
 */
LOCAL_INLINE void FLEXCAN_HWA_W1cFlag1NoFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    if(u32MbIndex<32)
    {
        pCan->IFLAG1 = 1U << u32MbIndex;
    }
#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    else if(u32MbIndex < 64)
    {
        pCan->IFLAG2 = 1U << (u32MbIndex-32);
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    else if(u32MbIndex < 96)
    {
        pCan->IFLAG3 = 1U << (u32MbIndex-64);
    }
#endif
    else
    {

    }
}

/**
 * @brief Get MB Flag
 *
 * @param pCan FLEXCAN instance value
 * @param u32MbIndex Message Buffer Index
 * @return flag value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetFlag1NoFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    if(u32MbIndex<32)
    {
        return (pCan->IFLAG1 >> u32MbIndex) & 0x01U;
    }
#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
    else if(u32MbIndex < 64)
    {
        return (pCan->IFLAG2 >> (u32MbIndex-32)) & 0x01U;
    }
#endif
#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
    else if(u32MbIndex < 96)
    {
        return (pCan->IFLAG3 >> (u32MbIndex-64)) & 0x01U;
    }
#endif
    else
    {
        return 0U;
    }
}

/**
 * @brief Check if legacy fifo contains at least one data
 *
 * @param pCan FLEXCAN instance value
 * @return 0 is none, others is data avaliable
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoData(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT5] (Frames available in Rx FIFO) is asserted when there is at least one frame available to be read from the FIFO. */
    return (pCan->IFLAG1  & 0x20U);
}

/**
 * @brief Check if legacy fifo contains 5 data and trigger warning
 *
 * @param pCan FLEXCAN instance value
 * @return 0 is none, others are warning
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoWarning(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT6] is asserted when there is 5 data. */
    return (pCan->IFLAG1  & 0x40U);
}

/**
 * @brief Check if legacy fifo data lost
 *
 * @param pCan FLEXCAN instance value
 * @return 0 is none, others are lost
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoDataLost(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT7] is asserted when there is data lost. */
    return (pCan->IFLAG1  & 0x80U);
}

/**
 * @brief Clear Legacy Fifo Rx data available Flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClearIFLAG1FifoFlag(FLEXCAN_Type *const pCan)
{
    /* Read TIMER to unlock message buffers */
    (void)pCan->TIMER;

    pCan->IFLAG1 = 1U << 5;
}

/**
 * @brief Clear Legacy Fifo Rx warning Flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClearIFLAG1FifoWarningFlag(FLEXCAN_Type *const pCan)
{
    pCan->IFLAG1 = 1U << 6;
}

/**
 * @brief Clear Legacy Fifo Rx error Flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClearIFLAG1FifoErrorFlag(FLEXCAN_Type *const pCan)
{
    pCan->IFLAG1 = 1U << 7;
}

/**
 * @brief Check Legacy Fifo Data Valid Polling Flag
 *
 * @param pCan FLEXCAN instance value
 * @return data valid polling flag, 0 is not ok, 1 is ok
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoDataPolling(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT5] (Frames available in Rx FIFO) is asserted when there is at least one frame available to be read from the FIFO. */
    uint32_t u32Temp = (~pCan->IMASK1);
    return (pCan->IFLAG1 & u32Temp & 0x20U);
}


/**
 * @brief Check Legacy Fifo Data warning Polling Flag
 *
 * @param pCan FLEXCAN instance value
 * @return data warning polling flag, 0 is not ok, 1 is ok
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoWarningPolling(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT6] is asserted when there is 5 data. */
    uint32_t u32Temp = (~pCan->IMASK1);
    return (pCan->IFLAG1 & u32Temp & 0x40U);
}

/**
 * @brief Check Legacy Fifo Data lost Polling Flag
 *
 * @param pCan FLEXCAN instance value
 * @return data lost polling flag, 0 is not ok, 1 is ok
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoErrorPolling(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT7] is asserted when there is data lost. */
    uint32_t u32Temp = (~pCan->IMASK1);
    return (pCan->IFLAG1 & u32Temp & 0x80U);
}

/**
 * @brief Check Legacy Fifo Data Valid Interrupt Flag
 *
 * @param pCan FLEXCAN instance value
 * @return data valid interrupt flag, 0 is not ok, 1 is ok
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoDataInterrupt(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT5] (Frames available in Rx FIFO) is asserted when there is at least one frame available to be read from the FIFO. */
    uint32_t u32Temp = (pCan->IMASK1);
    return (pCan->IFLAG1 & u32Temp & 0x20U);
}
/**
 * @brief Check Legacy Fifo Data warning interrupt Flag
 *
 * @param pCan FLEXCAN instance value
 * @return data warning interrupt flag, 0 is not ok, 1 is ok
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoWarningInterrupt(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT6] is asserted when there is 5 data. */
    uint32_t u32Temp = (pCan->IMASK1);
    return (pCan->IFLAG1 & u32Temp & 0x40U);
}

/**
 * @brief Check Legacy Fifo Data lost interrupt Flag
 *
 * @param pCan FLEXCAN instance value
 * @return data lost interrupt flag, 0 is not ok, 1 is ok
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckLegacyFifoErrorInterrupt(FLEXCAN_Type *const pCan)
{
    /* IFLAG1[BIT7] is asserted when there is data lost. */
    uint32_t u32Temp = (pCan->IMASK1);
    return (pCan->IFLAG1 & u32Temp & 0x80U);
}

/**
 * @brief Set special message buffer interrupt
 *
 * @param pCan FLEXCAN instance value
 * @param u32Mask Message Buffer interrupt mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMask1MbInterrupt(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->IMASK1 = u32Mask;
}

/**
 * @brief Attach special message buffer interrupt MASK1
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMask1MbInterrupt(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->IMASK1 |= u32Mask;
}

#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
/**
 * @brief Attach special message buffer interrupt MASK2
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMask2MbInterrupt(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->IMASK2 |= u32Mask;
}
#endif

#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
/**
 * @brief Attach special message buffer interrupt MASK2
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMask3MbInterrupt(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->IMASK3 |= u32Mask;
}
#endif

/**
 * @brief Attach special message buffer interrupt
 *
 * @param pCan FLEXCAN instance value
 * @param u32MbIndex Message Buffer index
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachMbIndexInterrupt(FLEXCAN_Type *const pCan, uint32_t u32MbIndex)
{
    pCan->IMASK1 |= 1U << u32MbIndex;
}

/**
 * @brief Set Legacy Fifo Rx interrupt
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMaskFifoInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->IMASK1 = 1U << 5U;
}

/**
 * @brief Get special message buffer interrupt
 *
 * @param pCan FLEXCAN instance value
 * @return IMASK1 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetMask1(FLEXCAN_Type *const pCan)
{
    return pCan->IMASK1;
}


#if FLEXCAN_IFLAGMASK_NUM_MAX > 1U
/**
 * @brief Get special message buffer interrupt
 *
 * @param pCan FLEXCAN instance value
 * @return IMASK2 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetMask2(FLEXCAN_Type *const pCan)
{
    return pCan->IMASK2;
}

#if FLEXCAN_IFLAGMASK_NUM_MAX > 2U
/**
 * @brief Get special message buffer interrupt
 *
 * @param pCan FLEXCAN instance value
 * @return IMASK3 value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetMask3(FLEXCAN_Type *const pCan)
{
    return pCan->IMASK3;
}
#endif

#endif

/**
 * @brief Set CBT value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetCBT(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->CBT = u32Value;
}

/**
 * @brief Set FDCBT value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFDCBT(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->FDCBT = u32Value;
}

/**
 * @brief Set FDCTRL value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFDCTRL(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->FDCTRL = u32Value;
}



/**
 * @brief Set MB data width in MBDSR
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CalDataWidth(uint8_t* pDataWidthArr)
{
    uint32_t u32Ret;
    /* MBDSR0, pMb 0-31 data length, 8-0,16-1,32-2,64-3 */
    u32Ret = (FLEXCAN_FDCTRL_MBDSR0(pDataWidthArr[0] == FLEXCAN_DATAWIDTH_8?0U:(pDataWidthArr[0] == FLEXCAN_DATAWIDTH_16?1U:(pDataWidthArr[0] == FLEXCAN_DATAWIDTH_32?2U:3U))));


#if FLEXCAN_FD_DATALEN_RANGE_NUM_MAX > 1U
        u32Ret |= FLEXCAN_FDCTRL_MBDSR1(u32Ret + (pDataWidthArr[1] == FLEXCAN_DATAWIDTH_8?0U:(pDataWidthArr[1] == FLEXCAN_DATAWIDTH_16?1U:(pDataWidthArr[1] == FLEXCAN_DATAWIDTH_32?2U:3U))));
#endif

#if FLEXCAN_FD_DATALEN_RANGE_NUM_MAX > 2U
    	u32Ret |= FLEXCAN_FDCTRL_MBDSR2(u32Ret + FLEXCAN_FDCTRL_MBDSR2(pDataWidthArr[2] == FLEXCAN_DATAWIDTH_8?0U:(pDataWidthArr[2] == FLEXCAN_DATAWIDTH_16?1U:(pDataWidthArr[2] == FLEXCAN_DATAWIDTH_32?2U:3U))));
#endif
    return u32Ret;
}

/**
 * @brief Set EPRS value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetEPRS(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->EPRS = u32Value;
}

/**
 * @brief Set ENCBT value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetENCBT(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->ENCBT = u32Value;
}

/**
 * @brief Set EDCBT value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetEDCBT(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->EDCBT = u32Value;
}

/**
 * @brief Set ETDC value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value write value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetETDC(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->ETDC = u32Value;
}


/**
 * @brief This Function is used to get FLEXCAN rx timestamp
 *
 * @param pCan is FLEXCAN instance value
 * @return timestamp Register Value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetTimeStamp(FLEXCAN_Type *const pCan)
{
    return pCan->TIMER;
}

/**
 * @brief This Function is used to get FLEXCAN error
 *
 * @param pCan is FLEXCAN instance value
 * @return ESR1 Register Value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetErrorInfo(FLEXCAN_Type *const pCan)
{
    return pCan->ESR1;
}

/**
 * @brief This Function is used to get FLEXCAN error with interrupt
 *
 * @param pCan is FLEXCAN instance value
 * @return ESR1 Register Value with interrupt mask
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetErrorIntInfo(FLEXCAN_Type *const pCan)
{
	uint32_t u32IntMask = 0U;

	u32IntMask = ((0U == (pCan->CTRL1 & FLEXCAN_CTRL1_ERRMSK_MASK))?0U:FLEXCAN_ESR1_ERRINT_MASK);
	u32IntMask |= ((0U == (pCan->CTRL1 & FLEXCAN_CTRL1_BOFFMSK_MASK))?0U:FLEXCAN_ESR1_BOFFINT_MASK);
	u32IntMask |= ((0U == (pCan->CTRL2 & FLEXCAN_CTRL2_ERRMSK_FAST_MASK))?0U:FLEXCAN_ESR1_ERRINT_FAST_MASK);
	u32IntMask |= ((0U == (pCan->CTRL2 & FLEXCAN_CTRL2_BOFFDONEMSK_MASK))?0U:FLEXCAN_ESR1_BOFFDONEINT_MASK);

    return (pCan->ESR1 & u32IntMask);
}

/**
 * @brief Clear Error Info
 *
 * @param pCan FLEXCAN instance value
 * @param u32ErrorEsr1 is read from FLEXCAN_GetErrorInfo
 */
LOCAL_INLINE void FLEXCAN_HWA_ClrErrorInfo(FLEXCAN_Type *const pCan, uint32_t u32ErrorEsr1)
{
    pCan->ESR1 = u32ErrorEsr1;
}

/**
 * @brief This Function is used to get FLEXCAN error count
 *
 * @param pCan is FLEXCAN instance value
 * @return ECR Register Value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetErrorCount(FLEXCAN_Type *const pCan)
{
    return pCan->ECR;
}

/**
 * @brief This Function is used to get FLEXCAN enhanced fifo error count
 *
 * @param pCan is FLEXCAN instance value
 * @return ERFSR Register Value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetERFSR(FLEXCAN_Type *const pCan)
{
    return pCan->ERFSR;
}


/**
 * @brief Enable FLEXCAN Legacy Fifo
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_EnableLegacyFifo(FLEXCAN_Type *const pCan)
{
    /* if enable legacy fifo, FD fifo must be disabled */
    pCan->MCR |= FLEXCAN_MCR_RFEN_MASK;       /* set legacy fifo */
}

/**
 * @brief Disable FLEXCAN Legacy Fifo
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_DisableLegacyFifo(FLEXCAN_Type *const pCan)
{
    /* if enable legacy fifo, FD fifo must be disabled */
    pCan->MCR &= ~FLEXCAN_MCR_RFEN_MASK;      /* clear legacy fifo */
}


/**
 * @brief Attach FLEXCAN ERFCR value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value attached value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachERFCR(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->ERFCR |= u32Value;
}

/**
 * @brief Check Enhanced FIFO Enable
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckEnhancedFIFOEn(FLEXCAN_Type *const pCan)
{
    return (pCan->ERFCR & FLEXCAN_ERFCR_ERFEN_MASK);
}

/**
 * @brief Enable FLEXCAN FD Fifo
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_EnableFDFifo(FLEXCAN_Type *const pCan)
{
    /* if enable fd fifo, legacy fifo must be disabled */
    pCan->ERFCR |= FLEXCAN_ERFCR_ERFEN_MASK;  /* set enhanced fifo */
}

/**
 * @brief Disable FLEXCAN FD Fifo
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_DisableFDFifo(FLEXCAN_Type *const pCan)
{
    /* if enable fd fifo, legacy fifo must be disabled */
    pCan->ERFCR &= ~FLEXCAN_ERFCR_ERFEN_MASK; /* clear enhanced fifo */
}



/**
 * @brief Check FLEXCAN legacy fifo if enabled
 *
 * @param pCan FLEXCAN instance value
 * @return 1 is legacy fifo enabled, 0 is disabled
 */
LOCAL_INLINE uint8_t FLEXCAN_HWA_CheckLegacyFifoEnabled(FLEXCAN_Type *const pCan)
{
    uint8_t  u8RetVal;
    uint32_t u32Value;

    /* get legacy fifo */
    u32Value = (pCan->MCR & FLEXCAN_MCR_RFEN_MASK) >> FLEXCAN_MCR_RFEN_SHIFT;

    u8RetVal = u32Value == 0U ? (uint8_t)0x0U : (uint8_t)0x1U;

    return u8RetVal;
}

/**
 * @brief Check FLEXCAN FD fifo if enabled
 *
 * @param pCan FLEXCAN instance value
 * @return 1 is legacy fifo enabled, 0 is disabled
 */
LOCAL_INLINE uint8_t FLEXCAN_HWA_CheckFdFifoEnabled(FLEXCAN_Type *const pCan)
{
    uint8_t  u8RetVal;
    uint32_t u32Value;
    /* get enhanced fifo */
    u32Value = (pCan->ERFCR & FLEXCAN_ERFCR_ERFEN_MASK) >> FLEXCAN_ERFCR_ERFEN_SHIFT;

    u8RetVal = u32Value == 0U ? (uint8_t)0x0U : (uint8_t)0x1U;

    return u8RetVal;
}


/**
 * @brief Set legacy fifo filter number number
 *
 * @param pCan FLEXCAN instance value
 * @param u32RFFN is total filter number
 */
LOCAL_INLINE void FLEXCAN_HWA_SetLegacyFifoFilterNum(FLEXCAN_Type *const pCan, uint32_t u32RFFN)
{
    pCan->CTRL2 &= ~FLEXCAN_CTRL2_RFFN_MASK; /* clear fifo filter number */
    pCan->CTRL2 |= ((u32RFFN) << FLEXCAN_CTRL2_RFFN_SHIFT)&FLEXCAN_CTRL2_RFFN_MASK;
}

/**
 * @brief Set legacy fifo filter number number
 *
 * @param pCan FLEXCAN instance value
 * @param u32FilterNum is total filter number
 */
LOCAL_INLINE void FLEXCAN_HWA_SetLegacyFifoFilterNum1(FLEXCAN_Type *const pCan, uint32_t u32FilterNum)
{
    pCan->CTRL2 &= ~FLEXCAN_CTRL2_RFFN_MASK; /* clear fifo filter number */
    pCan->CTRL2 |= ((u32FilterNum - 1U) << FLEXCAN_CTRL2_RFFN_SHIFT)&FLEXCAN_CTRL2_RFFN_MASK;
}


/**
 * @brief Check FLEXCAN FD enable
 *
 * @param pCan FLEXCAN instance value
 * @return 1 is fd enabled, 0 is disabled
 */
LOCAL_INLINE uint8_t FLEXCAN_HWA_CheckFd(FLEXCAN_Type *const pCan)
{
    uint8_t  u8RetVal;
    uint32_t u32Value;

    /* get fd enable */
    u32Value = (pCan->MCR & FLEXCAN_MCR_FDEN_MASK) >> FLEXCAN_MCR_FDEN_SHIFT;

    u8RetVal = u32Value == 0U ? (uint8_t)0x0U : (uint8_t)0x1U;

    return u8RetVal;
}


/**
 * @brief Set RXIMR for FLEXCAN
 *
 * @param pCan FLEXCAN instance value
 * @param u32MbIndex Message Buffer Index
 * @param u32Mask ID Mask
 */
LOCAL_INLINE void FLEXCAN_HWA_SetIndividualMask(FLEXCAN_Type *const pCan, uint32_t u32MbIndex, uint32_t u32Mask)
{
    pCan->RXIMR[u32MbIndex] = u32Mask;
}

/**
 * @brief Set MB global mask value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Mask mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetMBGlobalMask(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->RXMGMASK = u32Mask;
}

/**
 * @brief Set Fifo global mask value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Mask mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetFifoGlobalMask(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->RXFGMASK = u32Mask;
}


/**
 * @brief Set rx14 mask value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Mask mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetRx14Mask(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->RX14MASK = u32Mask;
}

/**
 * @brief Set rx15 mask value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Mask mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetRx15Mask(FLEXCAN_Type *const pCan, uint32_t u32Mask)
{
    pCan->RX15MASK = u32Mask;
}

/**
 * @brief Set value to FLEXCAN RAM
 *
 * @param pCan FLEXCAN instance value
 * @param u32RamIndex RAM index for FLEXCAN
 * @param u32Value written value
 */
LOCAL_INLINE void FLEXCAN_HWA_MbRam(FLEXCAN_Type *const pCan, uint32_t u32RamIndex, uint32_t u32Value)
{
    pCan->RAM[u32RamIndex] = u32Value;
}

/**
 * @brief Clear PNET CTRL1_PN
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClrPNET_CTRL1_PN(FLEXCAN_Type *const pCan)
{
    pCan->CTRL1_PN = 0U;
}

/**
 * @brief Set PNET timeout Interrupt
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_TimeoutInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->CTRL1_PN = FLEXCAN_CTRL1_PN_WTOF_MSK_MASK;
}

/**
 * @brief Check PNET timeout Interrupt
 *
 * @param pCan FLEXCAN instance value
 *
 * @return 0 is no timeout interrupt, others means contains interrupt
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_ChkPNET_TimeoutInterrupt(FLEXCAN_Type *const pCan)
{
    uint32_t u32Temp = pCan->CTRL1_PN & FLEXCAN_CTRL1_PN_WTOF_MSK_MASK;
    u32Temp = u32Temp & pCan->WU_MTC & FLEXCAN_WU_MTC_WTOF_MASK;
    return u32Temp;
}

/**
 * @brief Check PNET match Interrupt
 *
 * @param pCan FLEXCAN instance value
 *
 * @return 0 is no timeout interrupt, others means contains interrupt
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_ChkPNET_MatchInterrupt(FLEXCAN_Type *const pCan)
{
    uint32_t u32Temp = pCan->CTRL1_PN & FLEXCAN_CTRL1_PN_WUMF_MSK_MASK;
    u32Temp = u32Temp & pCan->WU_MTC & FLEXCAN_WU_MTC_WUMF_MASK;
    return u32Temp;
}

/**
 * @brief Attach PNET timeout Interrupt
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachPNET_TimeoutInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->CTRL1_PN |= FLEXCAN_CTRL1_PN_WTOF_MSK_MASK;
}

/**
 * @brief Set PNET match Interrupt
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_MatchInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->CTRL1_PN = FLEXCAN_CTRL1_PN_WUMF_MSK_MASK;
}

/**
 * @brief Attach PNET match Interrupt
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachPNET_MatchInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->CTRL1_PN |= FLEXCAN_CTRL1_PN_WUMF_MSK_MASK;
}

/**
 * @brief Set PNET Match Count value
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, match count
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_MatchCount(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN = FLEXCAN_CTRL1_PN_NMATCH(u8Value);
}

/**
 * @brief Attach PNET Match Count value
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, match count
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachPNET_MatchCount(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN |= FLEXCAN_CTRL1_PN_NMATCH(u8Value);
}

/**
 * @brief Set PNET Filter Type
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, Filter Type
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_FilterType(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN = FLEXCAN_CTRL1_PN_FCS(u8Value);
}

/**
 * @brief Attach PNET Filter Type
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, Filter Type
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachPNET_FilterType(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN |= FLEXCAN_CTRL1_PN_FCS(u8Value);
}


/**
 * @brief Set PNET ID Filter Type
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, ID Filter Type
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_IDFilterType(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN = FLEXCAN_CTRL1_PN_IDFS(u8Value);
}


/**
 * @brief Attach PNET ID Filter Type
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, ID Filter Type
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachPNET_IDFilterType(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN |= FLEXCAN_CTRL1_PN_IDFS(u8Value);
}


/**
 * @brief Set PNET Payload Filter Type
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, Payload Filter Type
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_PayloadFilterType(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN = FLEXCAN_CTRL1_PN_PLFS(u8Value);
}


/**
 * @brief Attach PNET Payload Filter Type
 *
 * @param pCan FLEXCAN instance value
 * @param u8Value written value, Payload Filter Type
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachPNET_PayloadFilterType(FLEXCAN_Type *const pCan, uint8_t u8Value)
{
    pCan->CTRL1_PN |= FLEXCAN_CTRL1_PN_PLFS(u8Value);
}


/**
 * @brief Set PNET ID 1
 *
 * @param pCan FLEXCAN instance value
 * @param u8IDE 0-standard, 1-extended
 * @param u8RTR 0-data, 1-remote
 * @param u32ID1 id value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_ID1(FLEXCAN_Type *const pCan, uint8_t u8IDE, uint8_t u8RTR, uint32_t u32ID1)
{
    pCan->FLT_ID1 = FLEXCAN_FLT_ID1_FLT_IDE(u8IDE) | FLEXCAN_FLT_ID1_FLT_RTR(u8RTR) | ((u8IDE==0)?(((uint32_t)u32ID1)<<18U):u32ID1);
}


/**
 * @brief Set PNET ID 2
 *
 * @param pCan FLEXCAN instance value
 * @param u8IDE 0-standard, 1-extended
 * @param u8RTR 0-data, 1-remote
 * @param u32ID2 id value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_ID2(FLEXCAN_Type *const pCan, uint8_t u8IDE, uint8_t u8RTR, uint32_t u32ID2)
{
    pCan->FLT_ID2_IDMASK = FLEXCAN_FLT_ID2_IDMASK_IDE_MSK(u8IDE) | FLEXCAN_FLT_ID2_IDMASK_RTR_MSK(u8RTR) | ((u8IDE==0)?(((uint32_t)u32ID2)<<18U):u32ID2);
}


/**
 * @brief Set PNET DLC
 *
 * @param pCan FLEXCAN instance value
 * @param u8DLC1 Low value
 * @param u8DLC2 High value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_DlcRange(FLEXCAN_Type *const pCan, uint8_t u8DLC1, uint8_t u8DLC2)
{
    pCan->FLT_DLC = FLEXCAN_FLT_DLC_FLT_DLC_HI(u8DLC2) | FLEXCAN_FLT_DLC_FLT_DLC_LO(u8DLC1);
}

/**
 * @brief Set PNET Payload 1 data content
 *
 * @param pCan FLEXCAN instance value
 * @param u32High High value
 * @param u32Low Low value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_Payload1Content(FLEXCAN_Type *const pCan, uint32_t u32High, uint32_t u32Low)
{
    pCan->PL1_HI = u32High;
    pCan->PL1_LO = u32Low;
}

/**
 * @brief Set PNET Payload 2 data content
 *
 * @param pCan FLEXCAN instance value
 * @param u32High High value
 * @param u32Low Low value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_Payload2Content(FLEXCAN_Type *const pCan, uint32_t u32High, uint32_t u32Low)
{
    pCan->PL2_PLMASK_HI = u32High;
    pCan->PL2_PLMASK_LO = u32Low;
}


/**
 * @brief Set PNET Timeout value
 *
 * @param pCan FLEXCAN instance value
 * @param u16Value written value, period is 64 times of can bit time
 */
LOCAL_INLINE void FLEXCAN_HWA_SetPNET_Timeout(FLEXCAN_Type *const pCan, uint16_t u16Value)
{
    pCan->CTRL2_PN = u16Value;
}

/**
 * @brief Clear PNET Interrupt flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClrPNET_IntFlag(FLEXCAN_Type *const pCan)
{
    pCan->WU_MTC = FLEXCAN_WU_MTC_WTOF_MASK | FLEXCAN_WU_MTC_WUMF_MASK;
}

/**
 * @brief Clear PNET timeout Interrupt flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClrPNET_TimeoutFlag(FLEXCAN_Type *const pCan)
{
    pCan->WU_MTC = FLEXCAN_WU_MTC_WTOF_MASK;
}

/**
 * @brief Clear PNET match Interrupt flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ClrPNET_MatchFlag(FLEXCAN_Type *const pCan)
{
    pCan->WU_MTC = FLEXCAN_WU_MTC_WUMF_MASK;
}

/**
 * @brief Get PNET Match Counter
 *
 * @param pCan FLEXCAN instance value
 *
 * @return count value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_GetPNET_MatchCount(FLEXCAN_Type *const pCan)
{
    return ((pCan->WU_MTC & FLEXCAN_WU_MTC_MCOUNTER_MASK)>>FLEXCAN_WU_MTC_MCOUNTER_SHIFT);
}


/**
 * @brief Get value from FLEXCAN Wake-up message index
 *
 * @param pCan FLEXCAN instance value
 * @param u32MsgIndex Wake-up Message index for FLEXCAN
 * @return ram address
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_PNETRamAddr(FLEXCAN_Type *const pCan, uint32_t u32MsgIndex)
{
    return (uint32_t)(&(pCan->WMB_RAM[u32MsgIndex*4]));
}


/**
 * @brief Set ERFCR value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetERFCR(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->ERFCR = u32Value;
}


/**
 * @brief Set ERFIER value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FLEXCAN_HWA_SetERFIER(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->ERFIER = u32Value;
}


/**
 * @brief Attache ERFIER value
 *
 * @param pCan FLEXCAN instance value
 * @param u32Value written value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachERFIER(FLEXCAN_Type *const pCan, uint32_t u32Value)
{
    pCan->ERFIER |= u32Value;
}


/**
 * @brief Check Enhanced FIFO Polling flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckEnhancedFifoPollingFlag(FLEXCAN_Type *const pCan)
{
    return ((~pCan->ERFIER) & pCan->ERFSR & (FLEXCAN_ERFSR_ERFDA_MASK | FLEXCAN_ERFSR_ERFOVF_MASK |
            FLEXCAN_ERFSR_ERFUFW_MASK | FLEXCAN_ERFSR_ERFWMI_MASK) );
}


/**
 * @brief Check Enhanced FIFO data polling flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckEnhancedFifoDataPolling(FLEXCAN_Type *const pCan)
{
    uint32_t u32Temp = pCan->ERFSR;
    u32Temp = ((~pCan->ERFIER) & u32Temp & (FLEXCAN_ERFSR_ERFDA_MASK |FLEXCAN_ERFSR_ERFWMI_MASK) );
    u32Temp = u32Temp | (pCan->MCR & FLEXCAN_MCR_DMA_MASK); /* no dma enable */
    return u32Temp;
}


/**
 * @brief Check Enhanced FIFO error polling flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckEnhancedFifoErrorPolling(FLEXCAN_Type *const pCan)
{
    uint32_t u32Temp = pCan->ERFSR;
    return ((~pCan->ERFIER) & u32Temp & (FLEXCAN_ERFSR_ERFOVF_MASK | FLEXCAN_ERFSR_ERFUFW_MASK) );
}

/**
 * @brief Check Enhanced FIFO data interrupt flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckEnhancedFifoDataInterrupt(FLEXCAN_Type *const pCan)
{
    uint32_t u32Temp = pCan->ERFSR;
    u32Temp = (pCan->ERFIER & u32Temp & (FLEXCAN_ERFSR_ERFDA_MASK |FLEXCAN_ERFSR_ERFWMI_MASK) );
    u32Temp = u32Temp | (pCan->MCR & FLEXCAN_MCR_DMA_MASK); /* no dma enable */
    return u32Temp;
}


/**
 * @brief Check Enhanced FIFO error interrupt flag
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_CheckEnhancedFifoErrorInterrupt(FLEXCAN_Type *const pCan)
{
    uint32_t u32Temp = pCan->ERFSR;
    return (pCan->ERFIER & u32Temp & (FLEXCAN_ERFSR_ERFOVF_MASK | FLEXCAN_ERFSR_ERFUFW_MASK) );
}


/**
 * @brief Reset Enhanced FIFO Engine
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ERFSRResetEnhancedFifo(FLEXCAN_Type *const pCan)
{
    /* Write one to ERFSR[ERFCLR] to reset Enhanced Rx FIFO engine */
    pCan->ERFSR |= FLEXCAN_ERFSR_ERFCLR_MASK;
}


/**
 * @brief Get Enhanced Fifo Flag with mask
 *
 * @param pCan FLEXCAN instance value
 * @param u32Shift flag shift
 * @param u32Mask flag mask
 * @return flag value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_ERFSRGetEnhancedFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32Shift, uint32_t u32Mask)
{
    /* Write one clear status */
    return ((pCan->ERFSR & u32Mask) >> u32Shift);
}

/**
 * @brief Get Enhanced Fifo Data valid
 *
 * @param pCan FLEXCAN instance value
 * @return flag value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_ERFSRGetDataValid(FLEXCAN_Type *const pCan)
{
    /* Write one clear status */
	 return (pCan->ERFSR & (FLEXCAN_ERFSR_ERFDA_MASK | FLEXCAN_ERFSR_ERFWMI_MASK));
}

/**
 * @brief Clear Enhanced Fifo underflow
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ERFSRClrUnderflow(FLEXCAN_Type *const pCan)
{
    /* Write one clear status */
    pCan->ERFSR = FLEXCAN_ERFSR_ERFUFW_MASK;
}

/**
 * @brief Clear Enhanced Fifo overflow
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_ERFSRClrOverflow(FLEXCAN_Type *const pCan)
{
    /* Write one clear status */
    pCan->ERFSR = FLEXCAN_ERFSR_ERFOVF_MASK;
}

/**
 * @brief Get Enhanced Fifo underflow
 *
 * @param pCan FLEXCAN instance value
 * @return flag value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_ERFSRGetUnderflow(FLEXCAN_Type *const pCan)
{
    /* Write one clear status */
    return (pCan->ERFSR & FLEXCAN_ERFSR_ERFUFW_MASK);
}

/**
 * @brief Get Enhanced Fifo overflow
 *
 * @param pCan FLEXCAN instance value
 * @return flag value
 */
LOCAL_INLINE uint32_t FLEXCAN_HWA_ERFSRGetOverflow(FLEXCAN_Type *const pCan)
{
    /* Write one clear status */
    return (pCan->ERFSR & FLEXCAN_ERFSR_ERFOVF_MASK);
}

/**
 * @brief Clear Enhanced Fifo status
 *
 * @param pCan FLEXCAN instance value
 * @param u32ClearMask clear mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_ERFSRClearEnhancedFifoFlag(FLEXCAN_Type *const pCan, uint32_t u32ClearMask)
{
    /* Write one clear status */
    pCan->ERFSR = u32ClearMask;
}

/**
 * @brief Clear Enhanced Fifo Error
 *
 * @param pCan FLEXCAN instance value
 * @param u32ClearMask clear mask value
 */
LOCAL_INLINE void FLEXCAN_HWA_ERFSRClearError(FLEXCAN_Type *const pCan, uint32_t u32ClearMask)
{
    /* Write one clear status */
    pCan->ERFSR = u32ClearMask;
}

/**
 * @brief Set Enhance Fifo interrupt value
 *
 * @param pCan FLEXCAN instance value
 */
LOCAL_INLINE void FLEXCAN_HWA_AttachERFIERDataInterrupt(FLEXCAN_Type *const pCan)
{
    pCan->ERFIER |= FLEXCAN_ERFIER_ERFDAIE_MASK;
}

/**
 * @brief Set Enhanced Fifo filter value
 *
 * @param pCan FLEXCAN instance value
 * @param u32FilterIndex Filter index
 * @param u32Value filter value
 */
LOCAL_INLINE void FLEXCAN_HWA_EnhancedFifoFilter(FLEXCAN_Type *const pCan, uint32_t u32FilterIndex, uint32_t u32Value)
{
    pCan->ERFFEL[u32FilterIndex] = u32Value;
}

/** @}*/

#endif

#endif
