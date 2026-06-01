#include "BspCan.h"
#include "BspGpio.h"
#include "com.h"
#ifndef ECU_ADDRESS_BLDC
#include "uds_tpl.h"
#include "uds_srv.h"
#else
#include "CompatibleInfo.h"
#endif

//#include "Pdu_cfg.h"

extern void SetFristFrameFlag(uint8 data);
extern uint8 GetFristFrameFlag(void);
extern void Set_XcpReceiveFlag(uint8 Flag);
static void CAN_Tx_CallBack(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle);
static void CAN1_Tx_CallBack(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle);
static void CAN_Rx_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_RxMsgType *pRxMsg);
static void CAN1_Rx_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_RxMsgType *pRxMsg);

static void CAN1_Error_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_ErrorInfoType *pErrorInfo);
static void CAN_FifoIssue_CallBack(FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue);
static void CAN1_FifoIssue_CallBack(FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue);
/* ################################################################################## */
/* ####################################### Macro #################################### */
#ifdef ECU_ADDRESS_PDM_FL

uint8  g_ui8CanRxBuffer[CANRX_NUM][8];
uint16 g_ui16CanRxTimeoutCnt[CANRX_NUM];
Bsp_CanRxInit_t g_stBsp_CanRxInit[CANRX_NUM] =
{
		{0,    {0 , 1, FLEXCAN_ID_STD, 0x150,           0x7FF},     10,       8,   	&g_ui8CanRxBuffer[0][0],   &g_ui16CanRxTimeoutCnt[0],		0,		 0,   0,  PDU_Index_150  },
		{1,    {0 , 1, FLEXCAN_ID_STD, 0x5E2,           0x7FF},    500,       8,   	&g_ui8CanRxBuffer[1][0],   &g_ui16CanRxTimeoutCnt[1],		0,		 9,   0,  PDU_Index_5E2  },
		{2,    {0 , 1, FLEXCAN_ID_STD, 0x1C2,           0x7FF},     20,       8,   	&g_ui8CanRxBuffer[2][0],   &g_ui16CanRxTimeoutCnt[2],		0,		18,   0,  PDU_Index_1C2  },
		{3,    {0 , 1, FLEXCAN_ID_STD, 0x2A0,           0x7FF},     50,       8,   	&g_ui8CanRxBuffer[3][0],   &g_ui16CanRxTimeoutCnt[3],		0,		24,   0,  PDU_Index_2A0  },
		{4,    {0 , 1, FLEXCAN_ID_STD, 0x3AE,           0x7FF},    100,       8,   	&g_ui8CanRxBuffer[4][0],   &g_ui16CanRxTimeoutCnt[4],		0,		38,   0,  PDU_Index_3AE  },
		{5,    {0 , 1, FLEXCAN_ID_STD, 0x3AF,           0x7FF},    100,       8,   	&g_ui8CanRxBuffer[5][0],   &g_ui16CanRxTimeoutCnt[5],		0,		42,   0,  PDU_Index_3AF  },
		{6,    {0 , 1, FLEXCAN_ID_STD, 0x3AA,           0x7FF},    100,       8,   	&g_ui8CanRxBuffer[6][0],   &g_ui16CanRxTimeoutCnt[6],		0,		45,   0,  PDU_Index_3AA  },
		{7,    {0 , 1, FLEXCAN_ID_STD, 0x6C0,           0x7FF},      0,       8,   	&g_ui8CanRxBuffer[7][0],   &g_ui16CanRxTimeoutCnt[7],		0,		 1,   0,  PDU_Index_RxXcp},
		{8,    {0 , 1, FLEXCAN_ID_STD, 0x43F, 			 0x780},      0,       8,   	&g_ui8CanRxBuffer[8][0],   &g_ui16CanRxTimeoutCnt[8],		0,	    50,   0,  PDU_Index_RxNM },
		{9,    {0 , 1, FLEXCAN_ID_STD, 0x7DF,           0x7FF},      0,       8,   	&g_ui8CanRxBuffer[9][0],   &g_ui16CanRxTimeoutCnt[9],		0,		 4,   0,  PDU_Index_7DF  },
		{10,   {0 , 1, FLEXCAN_ID_STD, 0x771,           0x7FF},      0,       8,   	&g_ui8CanRxBuffer[10][0],  &g_ui16CanRxTimeoutCnt[10],		0,		 3,   0,  PDU_Index_771  },

};

uint8 g_ui8CanTxBuffer[CANTX_NUM][8];
Bsp_CanTxInit_t g_stBsp_CanTxInit[CANTX_NUM] =
{
	/*报文发送放在5ms任务中，故初始化配置的周期性发送报文时间实际为[配置参数*5]*/
#ifndef ECU_ADDRESS_BLDC
	{0,    0x5C3, TXMAILBOX_5C3_INDEX,    (500/5),       0,    8,   &g_ui8CanTxBuffer[0][0], PDU_Index_5C3  },
#else
	{0,    0x5C3, TXMAILBOX_5C3_INDEX,    (10/5),       0,    8,   &g_ui8CanTxBuffer[0][0], PDU_Index_5C3  },
#endif
	{1,    0x3B6, TXMAILBOX_3B6_INDEX,    (100/5),       0,    8,   &g_ui8CanTxBuffer[1][0], PDU_Index_3B6  },
	{2,    0x3A6, TXMAILBOX_3A6_INDEX,    (100/5),       0,    8,   &g_ui8CanTxBuffer[2][0], PDU_Index_3A6  },
	{3,    0x6C1, TXMAILBOX_6C1_INDEX,      0,           0,    8,   &g_ui8CanTxBuffer[3][0], PDU_Index_TxXcp},
	{4,    0x471, TXMAILBOX_471_INDEX,      0,           0,    8,   &g_ui8CanTxBuffer[4][0], PDU_Index_TxNM },
	{5,    0x779, TXMAILBOX_779_INDEX,      0,           0,    8,   &g_ui8CanTxBuffer[5][0], PDU_Index_779  },
};

/*先初始化TX ，再初始化RX*/
FLEXCAN_MbSettingType stFLEXCAN_MBFilter[CANTX_NUM+CANRX_NUM] =
{
		/*TX*/
		{1,1,FLEXCAN_ID_STD,0x5C3},
		{1,1,FLEXCAN_ID_STD,0x3B6},
		{1,1,FLEXCAN_ID_STD,0x3A6},
		{1,1,FLEXCAN_ID_STD,0x6C1},
		{1,1,FLEXCAN_ID_STD,0x471},
		{1,1,FLEXCAN_ID_STD,0x779},
		/*RX*/
		{0,1,FLEXCAN_ID_STD,0x150,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x5E2,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x1C2,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x2A0,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x3AE,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x3AF,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x3AA,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x6C0,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x43F,0x780},
		{0,1,FLEXCAN_ID_STD,0x7DF,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x771,0x7FF},
};

#endif


#ifdef ECU_ADDRESS_PDM_FR
uint8  g_ui8CanRxBuffer[CANRX_NUM][8];
uint16 g_ui16CanRxTimeoutCnt[CANRX_NUM];
Bsp_CanRxInit_t g_stBsp_CanRxInit[CANRX_NUM] =
{
	{0,    {0 , 1, FLEXCAN_ID_STD, 0x151,           0x7FF},     10,       8,   	&g_ui8CanRxBuffer[0][0],   &g_ui16CanRxTimeoutCnt[0],		0,		 0,   0  ,PDU_Index_151  },
	{1,    {0 , 1, FLEXCAN_ID_STD, 0x5E2,           0x7FF},    500,       8,   	&g_ui8CanRxBuffer[1][0],   &g_ui16CanRxTimeoutCnt[1],		0,		 9,   0  ,PDU_Index_5E2  },
	{2,    {0 , 1, FLEXCAN_ID_STD, 0x1C2,           0x7FF},     20,       8,   	&g_ui8CanRxBuffer[2][0],   &g_ui16CanRxTimeoutCnt[2],		0,		18,   0  ,PDU_Index_1C2  },
	{3,    {0 , 1, FLEXCAN_ID_STD, 0x2A1,           0x7FF},     50,       8,   	&g_ui8CanRxBuffer[3][0],   &g_ui16CanRxTimeoutCnt[3],		0,		24,   0  ,PDU_Index_2A1  },
	{4,    {0 , 1, FLEXCAN_ID_STD, 0x3AE,           0x7FF},    100,       8,   	&g_ui8CanRxBuffer[4][0],   &g_ui16CanRxTimeoutCnt[4],		0,		37,   0  ,PDU_Index_3AE  },
	{5,    {0 , 1, FLEXCAN_ID_STD, 0x3AF,           0x7FF},    100,       8,   	&g_ui8CanRxBuffer[5][0],   &g_ui16CanRxTimeoutCnt[5],		0,		41,   0  ,PDU_Index_3AF  },
	{6,    {0 , 1, FLEXCAN_ID_STD, 0x3AB,           0x7FF},    100,       8,   	&g_ui8CanRxBuffer[6][0],   &g_ui16CanRxTimeoutCnt[6],		0,		44,   0  ,PDU_Index_3AB  },
	{7,    {0 , 1, FLEXCAN_ID_STD, 0x6C2,           0x7FF},      0,       8,   	&g_ui8CanRxBuffer[7][0],   &g_ui16CanRxTimeoutCnt[7],		0,		 1,   0  ,PDU_Index_RxXcp},
	{8,    {0 , 1, FLEXCAN_ID_STD, 0x449, 			 0x780},      0,       8,   	&g_ui8CanRxBuffer[8][0],   &g_ui16CanRxTimeoutCnt[8],		0,	    50,   0  ,PDU_Index_RxNM },
	{9,    {0 , 1, FLEXCAN_ID_STD, 0x7DF,           0x7FF},      0,       8,   	&g_ui8CanRxBuffer[9][0],   &g_ui16CanRxTimeoutCnt[9],		0,		 4,   0  ,PDU_Index_7DF  },
	{10,   {0 , 1, FLEXCAN_ID_STD, 0x770,           0x7FF},      0,       8,   	&g_ui8CanRxBuffer[10][0],  &g_ui16CanRxTimeoutCnt[10],		0,		 3,   0  ,PDU_Index_770  },

};

uint8 g_ui8CanTxBuffer[CANTX_NUM][8];
Bsp_CanTxInit_t g_stBsp_CanTxInit[CANTX_NUM] =
{
	/*报文发送放在5ms任务中，故初始化配置的周期性发送报文时间实际为[配置参数*5]*/
	{0,    0x5CB, TXMAILBOX_5CB_INDEX,    (500/5),       0,    8,   &g_ui8CanTxBuffer[0][0], PDU_Index_5CB  },
	{1,    0x3B7, TXMAILBOX_3B7_INDEX,    (100/5),       0,    8,   &g_ui8CanTxBuffer[1][0], PDU_Index_3B7  },
	{2,    0x3A7, TXMAILBOX_3A7_INDEX,    (100/5),       0,    8,   &g_ui8CanTxBuffer[2][0], PDU_Index_3A7  },
	{3,    0x6C3, TXMAILBOX_6C3_INDEX,      0,           0,    8,   &g_ui8CanTxBuffer[3][0], PDU_Index_TxXcp},
	{4,    0x472, TXMAILBOX_472_INDEX,      0,           0,    8,   &g_ui8CanTxBuffer[4][0], PDU_Index_TxNM },
	{5,    0x778, TXMAILBOX_778_INDEX,      0,           0,    8,   &g_ui8CanTxBuffer[5][0], PDU_Index_778  },
};

/*先初始化TX ，再初始化RX*/
FLEXCAN_MbSettingType stFLEXCAN_MBFilter[CANTX_NUM+CANRX_NUM] =
{
		/*TX*/
		{1,1,FLEXCAN_ID_STD,0x5CB},
		{1,1,FLEXCAN_ID_STD,0x3B7},
		{1,1,FLEXCAN_ID_STD,0x3A7},
		{1,1,FLEXCAN_ID_STD,0x6C3},
		{1,1,FLEXCAN_ID_STD,0x472},
		{1,1,FLEXCAN_ID_STD,0x778},
		/*RX*/
		{0,1,FLEXCAN_ID_STD,0x151,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x5E2,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x1C2,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x2A1,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x3AE,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x3AF,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x3AB,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x6C2,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x449,0x780},
		{0,1,FLEXCAN_ID_STD,0x7DF,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x770,0x7FF},
};

#endif



uint8  g_ui8CanFdRxBuffer[2][8];
uint16 g_ui16CanFdRxTimeoutCnt[2];
Bsp_CanRxInit_t g_stBsp_CanFdRxInit[2] =
{
		{0, {0 , 1, FLEXCAN_ID_STD, 0x100, 0x7FF},  500, 8, &g_ui8CanFdRxBuffer[0][0], &g_ui16CanFdRxTimeoutCnt[0], 0, 0, 0, 0},
		{1, {0 , 1, FLEXCAN_ID_STD, 0x101, 0x7FF}, 500, 8, &g_ui8CanFdRxBuffer[1][0], &g_ui16CanFdRxTimeoutCnt[1], 0, 8, 0, 1},
};

/*先初始化TX ，再初始化RX*/
FLEXCAN_MbSettingType stFLEXCANFD_MBFilter[3] =
{
		{1,1,FLEXCAN_ID_STD,0x102},
		{0,1,FLEXCAN_ID_STD,0x100,0x7FF},
		{0,1,FLEXCAN_ID_STD,0x101,0x7FF},
};



#define CAN_FD_ENABLE            STD_OFF

#define CAN_CLOCK_FROM_BUS       STD_OFF

#define CAN_FIFO_RECEIVE         STD_ON

#define CAN_ERROR_INTERRUPT      STD_ON
#define CAN_RX_INTERRUPT         STD_ON
#define CAN_TX_INTERRUPT         STD_ON
#define CAN_FIFO_INTERRUPT       STD_OFF

#define IF_USE_PDUR 1

/**
 * @brief FLEXCAN baud-rate clock source
 *
 */
typedef enum
{
    FLEXCAN_BAUDCLK_HZ_8M   = 8000000U,  /**< FLEXCAN_BAUDCLK_HZ_8M   8MHz clock source   */
    FLEXCAN_BAUDCLK_HZ_12M  = 12000000U, /**< FLEXCAN_BAUDCLK_HZ_12M  12MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_16M  = 16000000U, /**< FLEXCAN_BAUDCLK_HZ_16M  16MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_24M  = 24000000U, /**< FLEXCAN_BAUDCLK_HZ_24M  24MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_48M  = 48000000U, /**< FLEXCAN_BAUDCLK_HZ_48M  48MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_96M  = 96000000U, /**< FLEXCAN_BAUDCLK_HZ_96M  96MHz clock source  */
    FLEXCAN_BAUDCLK_HZ_120M = 120000000U,/**< FLEXCAN_BAUDCLK_HZ_120M 120MHz clock source */
    FLEXCAN_BAUDCLK_HZ_150M = 150000000U /**< FLEXCAN_BAUDCLK_HZ_150M 150MHz clock source */
} CAN_BaudClkType;



/**
 * @brief FLEXCAN baud-rate source
 *
 */
typedef enum
{
    FLEXCAN_BAUD_100K = 100000U, /**< FLEXCAN_BAUD_100K normal bit 100Kbps */
    FLEXCAN_BAUD_125K = 125000U, /**< FLEXCAN_BAUD_100K normal bit 125Kbps */
    FLEXCAN_BAUD_250K = 250000U, /**< FLEXCAN_BAUD_250K normal bit 250Kbps */
    FLEXCAN_BAUD_500K = 500000U, /**< FLEXCAN_BAUD_500K normal bit 500Kbps */
    FLEXCAN_BAUD_800K = 800000U, /**< FLEXCAN_BAUD_500K normal bit 800Kbps */
    FLEXCAN_BAUD_1M   = 1000000U,/**< FLEXCAN_BAUD_1M   normal bit 1Mbps   */
    FLEXCAN_BAUD_2M   = 2000000U,/**< FLEXCAN_BAUD_2M   normal bit 2Mbps   */
    FLEXCAN_BAUD_3M   = 3000000U,/**< FLEXCAN_BAUD_3M   normal bit 3Mbps   */
    FLEXCAN_BAUD_4M   = 4000000U,/**< FLEXCAN_BAUD_4M   normal bit 4Mbps   */
    FLEXCAN_BAUD_5M   = 5000000U,/**< FLEXCAN_BAUD_5M   normal bit 5Mbps   */
    FLEXCAN_BAUD_6M   = 6000000U,/**< FLEXCAN_BAUD_6M   normal bit 6Mbps   */
    FLEXCAN_BAUD_8M   = 8000000U /**< FLEXCAN_BAUD_8M   normal bit 8Mbps   */
} CAN_BaudType;


/**
 * @brief Baud-rate clock and divider
 *
 */
typedef struct
{
    CAN_BaudClkType      eClkHz;      /**< Clock Hz for baudrate             */
    CAN_BaudType         eBaudrate;   /**< Normal bit baudrate               */
    uint32_t             u32Presdiv;  /**< Presdiv for can                   */
    uint32_t             u32Propseg;  /**< Propseg for can                   */
    uint32_t             u32Pseg1;    /**< Pseg1 for can                     */
    uint32_t             u32Pseg2;    /**< Pseg2 for can                     */
    uint32_t             u32Rjw;      /**< RJW for can                       */
} CAN_BaudRegType;



/* ################################################################################## */
/* ################################ Local Variables ################################# */

static FLEXCAN_RxMsgType s_aaRxDataBuf[2][6];

uint32_t s_aTxErrorCount[CANTX_NUM] = {0,0};

#if (CAN_CLOCK_FROM_BUS==STD_OFF)
static PCC_ClkSrcType s_aPccClkCan[] = {
        PCC_CLK_CAN0
        ,PCC_CLK_CAN1
        ,PCC_CLK_CAN2
#if FLEXCAN_INSTANCE_COUNT > 3u
        ,PCC_CLK_CAN3
        ,PCC_CLK_CAN4
        ,PCC_CLK_CAN5
#endif
};
#endif


/* Normal bit table */
static const CAN_BaudRegType s_aFlexCan_NormalBaudDividerTable[] =
{
    /* clock source hz          baudrate             presdiv    propseg   pseg1   pseg2   rjw  */
    { FLEXCAN_BAUDCLK_HZ_16M,   FLEXCAN_BAUD_500K,   2,         8,        4,      3,      3  },
//    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_100K,   12,        7,        6,      6,      1  },
//    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_125K,   12,        5,        5,      5,      1  },
//    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_250K,   8,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_500K,   4,         5,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_800K,   3,         5,        2,      2,      1  },
//    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_1M,     2,         5,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_2M,     1,         5,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_100K,   32,        8,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_125K,   24,        7,        4,      4,      1  },
//    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_250K,   24,        3,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_500K,   6,         7,        4,      4,      3  },
//    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_800K,   4,         8,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_1M,     3,         7,        4,      4,      1  },
//    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_2M,     2,         5,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_100K,   80,        8,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_125K,   64,        8,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_250K,   32,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_500K,   16,        8,        3,      3,      3  },
//    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_800K,   15,        5,        2,      2,      1  },
//    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_1M,     8,         8,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_2M,     4,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_500K,   20,        8,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_1M,     10,        8,        3,      3,      1  },
//    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_2M,     5,         8,        3,      3,      1  }

};

/* Data bit table */
static const CAN_BaudRegType s_aFlexCan_DataBaudDividerTable[] =
{
    /* clock source hz          baudrate             presdiv    propseg   pseg1   pseg2   rjw  */
    { FLEXCAN_BAUDCLK_HZ_16M,   FLEXCAN_BAUD_2M,     1,         3,        2,      2,      2  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_1M,     2,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_2M,     1,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_24M,   FLEXCAN_BAUD_3M,     1,         3,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_1M,     3,         7,        4,      4,      1  },
	{ FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_2M,     2,         6,        3,      2,      2  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_3M,     1,         7,        4,      4,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_4M,     1,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_48M,   FLEXCAN_BAUD_6M,     1,         3,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_1M,     8,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_2M,     4,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_3M,     4,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_4M,     3,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_5M,     2,         5,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_6M,     2,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_120M,  FLEXCAN_BAUD_8M,     1,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_1M,     10,        8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_2M,     5,         8,        3,      3,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_3M,     5,         5,        2,      2,      1  },
    { FLEXCAN_BAUDCLK_HZ_150M,  FLEXCAN_BAUD_5M,     2,         8,        3,      3,      1  }
};

#if CAN_FIFO_RECEIVE == STD_ON
/* fifo filter table */
//static const FLEXCAN_RxFilterType s_aFlexCan2_RxFifoFilter[] =
//{
//
//    /* eRxFrameType             u32RxCanId              u32RxCanIdMask */
//    { FLEXCAN_ID_STD,           0x001U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x002U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x003U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x004U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x005U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x006U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x007U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x008U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x009U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x00AU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x00BU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x00CU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x00DU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x00EU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x00FU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x010U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x011U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x012U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x013U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x014U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x015U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x016U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x017U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x018U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x019U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x01AU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x01BU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x01CU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x01DU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x01EU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x01FU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x020U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x021U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x022U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x023U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x024U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x025U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x026U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x027U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x028U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x029U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x02AU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x02BU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x02CU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x02DU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x02EU,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x02FU,                 0x222U         },
//    { FLEXCAN_ID_STD,           0x030U,                 0x345U         }
//};
//static const FLEXCAN_RxFilterType s_aFlexCan0_RxFifoFilter[] =
//{
//    /* eRxFrameType             u32RxCanId              u32RxCanIdMask */
//    { FLEXCAN_ID_STD,           0x332U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x667U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x667U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x667U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x667U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x667U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x667U,                 0x7FFU         },
//    { FLEXCAN_ID_STD,           0x667U,                 0x7FFU         }
//};
#endif

/* mb filter table */
//static const FLEXCAN_RxFilterType s_aFlexCan0_RxMbFilter[] =
//{
//    /* eRxFrameType             u32RxCanId              u32RxCanIdMask */
//    { FLEXCAN_ID_STD,           0x444U,                 0x7FFU         }
//};
//static const FLEXCAN_RxFilterType s_aFlexCan2_RxMbFilter[] =
//{
//    /* eRxFrameType             u32RxCanId              u32RxCanIdMask */
//    { FLEXCAN_ID_STD,           0x555U,                 0x7FFU         }
//};






/* ################################################################################## */
/* ############################ Local Prototype Functions ########################### */
static void BSP_CAN_LL_Init(FLEXCAN_HandleType *pCanHandle);
void BSP_CAN_LL_TransmitData(FLEXCAN_HandleType *pCanHandle , uint8 TxMessageIndex);

static void CAN_Error_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_ErrorInfoType *pErrorInfo);
static void CAN_FifoIssue_CallBack(FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue);
static void CAN_Tx_CallBack(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle);
static void CAN_Rx_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_RxMsgType *pRxMsg);


/* ################################################################################## */
/* ####################################### Gobal #################################### */
FLEXCAN_HandleType  g_tCan2 =
{
    .eInstance = FLEXCAN_INSTANCE_2,
    {
        .eStatusSeq = FLEXCAN_SEQUENCE_DEINIT
    },
    {
        .pRxBuf = (FLEXCAN_RxMsgType *) &s_aaRxDataBuf[0]
        , .pWakeMsg = NULL
		, .pErrorNotify = CAN_Error_CallBack
		, .pFifoIssueNotify = CAN_FifoIssue_CallBack
		, .pTxNotify = CAN_Tx_CallBack
		, .pRxNotify = CAN_Rx_CallBack
		, .pWakeNotify = NULL
    }
};
FLEXCAN_HandleType  g_tCan1 =
{
    .eInstance = FLEXCAN_INSTANCE_1,
    {
        .eStatusSeq = FLEXCAN_SEQUENCE_DEINIT
    },
    {
        .pRxBuf = (FLEXCAN_RxMsgType *) &s_aaRxDataBuf[1]
        , .pWakeMsg = NULL
		, .pErrorNotify = CAN1_Error_CallBack
        , .pFifoIssueNotify = CAN1_FifoIssue_CallBack
		, .pTxNotify = CAN1_Tx_CallBack
		, .pRxNotify = CAN1_Rx_CallBack
        , .pWakeNotify = NULL
    }
};

/* ################################################################################## */
/* ################################ Local Functions ################################# */
static void BSP_CAN_LL_InitCfg(FLEXCAN_InitType *pCfg)
{
    pCfg->eClkSrcSel = FLEXCAN_CLOCK_CANPE;
    pCfg->bListenOnly = 0U;
    pCfg->tNormalBaud.u32Presdiv = 0U;
    pCfg->tNormalBaud.u32Propseg = 0U;
    pCfg->tNormalBaud.u32Pseg1 = 0U;
    pCfg->tNormalBaud.u32Pseg2 = 0U;
    pCfg->tNormalBaud.u32Rjw = 0U;
    pCfg->bEnFd = 0U;
    pCfg->tFdBaud.u32Presdiv = 0U;
    pCfg->tFdBaud.u32Propseg = 0U;
    pCfg->tFdBaud.u32Pseg1 = 0U;
    pCfg->tFdBaud.u32Pseg2 = 0U;
    pCfg->tFdBaud.u32Rjw = 0U;

    pCfg->bEnErrInt  = 0U;
    pCfg->bEnBusOffInt = 0U;
    pCfg->bEnBusOffDoneInt = 0U;
    pCfg->bEnWarningInt = 0U;
    pCfg->bEnSsp     = 0U;
    pCfg->bEnAutoRec = 0U;

    pCfg->tMbCfg.pMBList = NULL;
    pCfg->tMbCfg.u8MBCnt = 0U;

    pCfg->tRxFifoFilterCfg.bEnFifo = 0U;
    pCfg->tRxFifoFilterCfg.eFifoType = 0U;
    pCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bEnFifoDMA = 0U;
    pCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bDataAvaliableInt = 0U;
    pCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bWarningInt = 0U;
    pCfg->tRxFifoFilterCfg.tLegacyFifoCfg.bOverflowInt = 0U;
    pCfg->tRxFifoFilterCfg.tLegacyFifoCfg.u8RxFilterFifoCnt = 0U;
    pCfg->tRxFifoFilterCfg.tLegacyFifoCfg.pRxFilterFifoList = NULL;

    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bEnFifoDMA = 0U;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt = 0U;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.u8FifoWaterMark = 0U;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bWaterMarkInt = 0U;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt = 0U;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt = 0U;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.eFifoDataLength = FLEXCAN_DATAWIDTH_64;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt = 0U;
    pCfg->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList = NULL;
    pCfg->tPnetCfg.bPNetEnable = 0U;
}

/**
 * @brief Process CAN Baudrate from table
 *
 * @param pBaudCfg baudrate configuration
 * @return 0 is ok
 */
static uint8_t BSP_CAN_LL_ProcessBaud(FLEXCAN_InstanceType eInstance, FLEXCAN_InitType *const pInitCfg)
{
    uint32_t         u32Mod;
    uint8_t          u8RetVal;
    uint32_t         u32Index;
    uint32_t         u32ClkHz;
    CAN_BaudType     eNormalBaud = FLEXCAN_BAUD_500K;
    CAN_BaudType     eFdBaud = FLEXCAN_BAUD_2M;

    u8RetVal = 1U;

	#if (CAN_CLOCK_FROM_BUS==STD_ON)
	pInitCfg->eClkSrcSel = FLEXCAN_CLOCK_INTERFACE; /* can interface clock */
	u32ClkHz = SCG_GetScgClockFreq(SCG_BUS_CLK);
	PROCESS_UNUSED_VAR(eInstance);
	#else
    pInitCfg->eClkSrcSel = FLEXCAN_CLOCK_CANPE; /* functional clock */
    u32ClkHz = PCC_GetPccFunctionClock(s_aPccClkCan[eInstance]);
    #endif

    if (pInitCfg->bEnFd)
    {
        u32Mod = (uint32_t)u32ClkHz % (uint32_t)eFdBaud;
        if (u32Mod != 0U)
        {
            u8RetVal = 1U;
        }
        else
        {

            /* loop check for normal bit rate */
            for (u32Index = 0U; u32Index < sizeof(s_aFlexCan_NormalBaudDividerTable) / sizeof(s_aFlexCan_NormalBaudDividerTable[0]); u32Index++)
            {
                if ((u32ClkHz == s_aFlexCan_NormalBaudDividerTable[u32Index].eClkHz) && (eNormalBaud == s_aFlexCan_NormalBaudDividerTable[u32Index].eBaudrate))
                {
                    pInitCfg->tNormalBaud.u32Presdiv = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Presdiv;
                    pInitCfg->tNormalBaud.u32Propseg = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Propseg;
                    pInitCfg->tNormalBaud.u32Pseg1 = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg1;
                    pInitCfg->tNormalBaud.u32Pseg2 = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg2;
                    pInitCfg->tNormalBaud.u32Rjw = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Rjw;

                    u8RetVal = 0U;
                    break;
                }
            }


            if (u8RetVal == 0U)
            {
                u8RetVal = 1U;

                /* loop for fd data bit rate */
                for (u32Index = 0U; u32Index < sizeof(s_aFlexCan_DataBaudDividerTable) / sizeof(s_aFlexCan_DataBaudDividerTable[0]); u32Index++)
                {
                    if ((u32ClkHz == s_aFlexCan_DataBaudDividerTable[u32Index].eClkHz) && (eFdBaud == s_aFlexCan_DataBaudDividerTable[u32Index].eBaudrate))
                    {
                        pInitCfg->tFdBaud.u32Presdiv = s_aFlexCan_DataBaudDividerTable[u32Index].u32Presdiv;
                        pInitCfg->tFdBaud.u32Propseg = s_aFlexCan_DataBaudDividerTable[u32Index].u32Propseg;
                        pInitCfg->tFdBaud.u32Pseg1 = s_aFlexCan_DataBaudDividerTable[u32Index].u32Pseg1;
                        pInitCfg->tFdBaud.u32Pseg2 = s_aFlexCan_DataBaudDividerTable[u32Index].u32Pseg2;
                        pInitCfg->tFdBaud.u32Rjw = s_aFlexCan_DataBaudDividerTable[u32Index].u32Rjw;

                        u8RetVal = 0U;
                        break;
                    }
                }
            }


        }
    }
    else
    {
        u32Mod = (uint32_t)u32ClkHz % (uint32_t)eNormalBaud;
        if (u32Mod != 0U)
        {
            u8RetVal = 1U;
        }

        else
        {
            u8RetVal = 1U;
            /* loop check for normal bit rate */
            for (u32Index = 0U; u32Index < sizeof(s_aFlexCan_NormalBaudDividerTable) / sizeof(s_aFlexCan_NormalBaudDividerTable[0]); u32Index++)
            {
                if ((u32ClkHz == s_aFlexCan_NormalBaudDividerTable[u32Index].eClkHz) && (eNormalBaud == s_aFlexCan_NormalBaudDividerTable[u32Index].eBaudrate))
                {

                    pInitCfg->tNormalBaud.u32Presdiv = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Presdiv;
                    pInitCfg->tNormalBaud.u32Propseg = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Propseg;
                    pInitCfg->tNormalBaud.u32Pseg1 = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg1;
                    pInitCfg->tNormalBaud.u32Pseg2 = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Pseg2;
                    pInitCfg->tNormalBaud.u32Rjw = s_aFlexCan_NormalBaudDividerTable[u32Index].u32Rjw;
                    u8RetVal = 0U;
                }
            }
        }
    }

    return u8RetVal;
}




/**
 * @brief CAN init with index
 *
 * @param u8CanIndex
 */
static void BSP_CAN_LL_Init(FLEXCAN_HandleType *pCanHandle)
{
    FLEXCAN_ErrorType       tRetVal;
    FLEXCAN_InitType        tInitCfg;

   if(pCanHandle->eInstance == FLEXCAN_INSTANCE_1)
   {
		FLEXCAN_MbSettingType	astFLEXCAN_RxFilter[3];
		/* initial parameters */
		BSP_CAN_LL_InitCfg(&tInitCfg);

		#if CAN_ERROR_INTERRUPT == STD_ON
		tInitCfg.bEnErrInt = 1U;
		tInitCfg.bEnBusOffInt = 1U;
		tInitCfg.bEnBusOffDoneInt = 1U;
		tInitCfg.bEnWarningInt = 1U;
		#endif

		for(uint8 i = 0; i < 1 ; i++)
		{
			astFLEXCAN_RxFilter[i].bEnMBInt = stFLEXCANFD_MBFilter[i].bEnMBInt;
			astFLEXCAN_RxFilter[i].bIsTxMB = stFLEXCANFD_MBFilter[i].bIsTxMB;
		}
		/* Rx MB config */
		for(uint8 i = 1; i < 3 ; i++)
		{
			astFLEXCAN_RxFilter[i].eRxFrameType = stFLEXCANFD_MBFilter[i].eRxFrameType;
			astFLEXCAN_RxFilter[i].u32RxCanId = stFLEXCANFD_MBFilter[i].u32RxCanId;
			astFLEXCAN_RxFilter[i].u32RxCanIdMask = stFLEXCANFD_MBFilter[i].u32RxCanIdMask;
			astFLEXCAN_RxFilter[i].bEnMBInt = stFLEXCANFD_MBFilter[i].bEnMBInt;
			astFLEXCAN_RxFilter[i].bIsTxMB = stFLEXCANFD_MBFilter[i].bIsTxMB;
		}
		tInitCfg.tMbCfg.pMBList = astFLEXCAN_RxFilter;
		tInitCfg.tMbCfg.u8MBCnt = sizeof(astFLEXCAN_RxFilter)/sizeof(astFLEXCAN_RxFilter[0]);

		#if CAN_FIFO_RECEIVE == STD_OFF
		tInitCfg.tRxFifoFilterCfg.bEnFifo = 1U;
		#if CAN_FD_ENABLE == STD_ON
		/* enhanced fifo */
		tInitCfg.tRxFifoFilterCfg.u8FifoType = 1U;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bEnFifoDMA = 0U;
		#if CAN_RX_INTERRUPT == STD_ON
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt = 1U;
		#endif
		/* Rx Fifo config */
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList = pCanHandle->eInstance == 0 ? (FLEXCAN_RxFilterType *)s_aFlexCan0_RxFifoFilter : (FLEXCAN_RxFilterType *)s_aFlexCan2_RxFifoFilter;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt = pCanHandle->eInstance == 0 ? (sizeof(s_aFlexCan0_RxFifoFilter) / sizeof(s_aFlexCan0_RxFifoFilter[0])) : (sizeof(
																  s_aFlexCan2_RxFifoFilter) / sizeof(s_aFlexCan2_RxFifoFilter[0]));
		#else
		/* legacy fifo */
		tInitCfg.tRxFifoFilterCfg.u8FifoType = 0U;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bEnFifoDMA = 0U;
		#if CAN_RX_INTERRUPT == STD_ON
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bDataAvaliableInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bWarningInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bOverflowInt = 1U;
		#endif
		/* Rx Fifo config */
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.pRxFilterFifoList = pCanHandle->eInstance == 0 ? (FLEXCAN_RxFilterType *)s_aFlexCan0_RxFifoFilter : (FLEXCAN_RxFilterType *)s_aFlexCan2_RxFifoFilter;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.u8RxFilterFifoCnt = pCanHandle->eInstance == 0 ? (sizeof(s_aFlexCan0_RxFifoFilter) / sizeof(s_aFlexCan0_RxFifoFilter[0])) : (sizeof(
															  s_aFlexCan2_RxFifoFilter) / sizeof(s_aFlexCan2_RxFifoFilter[0]));
		#endif
		#endif

		#if CAN_FIFO_INTERRUPT == STD_ON
		tInitCfg.bEnFifoInt = 1U;
		#endif

		tInitCfg.bEnFd = TRUE;
		tInitCfg.tMbCfg.aDataWidthRange[0] = FLEXCAN_DATAWIDTH_8;

		tRetVal = BSP_CAN_LL_ProcessBaud(pCanHandle->eInstance, &tInitCfg);


		if (tRetVal == 0U)
		{
			/* initial can */
			tRetVal = FLEXCAN_Init(pCanHandle, &tInitCfg);

			FLEXCAN_Start(pCanHandle); /* Start CAN */
		}
   }
   else if(pCanHandle->eInstance == FLEXCAN_INSTANCE_2)
   {
		FLEXCAN_MbSettingType	astFLEXCAN_RxFilter[CANRX_NUM+CANTX_NUM];
		/* initial parameters */
		BSP_CAN_LL_InitCfg(&tInitCfg);


		#if CAN_ERROR_INTERRUPT == STD_ON
		tInitCfg.bEnErrInt = 1U;
		tInitCfg.bEnBusOffInt = 1U;
		tInitCfg.bEnBusOffDoneInt = 1U;
		tInitCfg.bEnWarningInt = 1U;
		#endif

		/* tx mb config*/
		for(uint8 i = 0; i < CANTX_NUM ; i++)
		{
			astFLEXCAN_RxFilter[i].bIsTxMB = stFLEXCAN_MBFilter[i].bIsTxMB;
			astFLEXCAN_RxFilter[i].bEnMBInt = stFLEXCAN_MBFilter[i].bEnMBInt;
		}
		/* Rx MB config */
		for(uint8 i = CANTX_NUM; i < (CANRX_NUM + CANTX_NUM) ; i++)
		{
			astFLEXCAN_RxFilter[i].eRxFrameType = stFLEXCAN_MBFilter[i].eRxFrameType;
			astFLEXCAN_RxFilter[i].u32RxCanId = stFLEXCAN_MBFilter[i].u32RxCanId;
			astFLEXCAN_RxFilter[i].u32RxCanIdMask = stFLEXCAN_MBFilter[i].u32RxCanIdMask;
			astFLEXCAN_RxFilter[i].bEnMBInt = stFLEXCAN_MBFilter[i].bEnMBInt;
			astFLEXCAN_RxFilter[i].bIsTxMB = stFLEXCAN_MBFilter[i].bIsTxMB;
		}
		tInitCfg.tMbCfg.pMBList = astFLEXCAN_RxFilter;
		tInitCfg.tMbCfg.u8MBCnt = sizeof(astFLEXCAN_RxFilter)/sizeof(astFLEXCAN_RxFilter[0]);

		#if CAN_FIFO_RECEIVE == STD_OFF
		tInitCfg.tRxFifoFilterCfg.bEnFifo = 1U;
		#if CAN_FD_ENABLE == STD_ON
		/* enhanced fifo */
		tInitCfg.tRxFifoFilterCfg.u8FifoType = 1U;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bEnFifoDMA = 0U;
		#if CAN_RX_INTERRUPT == STD_ON
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt = 1U;
		#endif
		/* Rx Fifo config */
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList = pCanHandle->eInstance == 0 ? (FLEXCAN_RxFilterType *)s_aFlexCan0_RxFifoFilter : (FLEXCAN_RxFilterType *)s_aFlexCan2_RxFifoFilter;
		tInitCfg.tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt = pCanHandle->eInstance == 0 ? (sizeof(s_aFlexCan0_RxFifoFilter) / sizeof(s_aFlexCan0_RxFifoFilter[0])) : (sizeof(
																  s_aFlexCan2_RxFifoFilter) / sizeof(s_aFlexCan2_RxFifoFilter[0]));
		#else
		/* legacy fifo */
		tInitCfg.tRxFifoFilterCfg.u8FifoType = 0U;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bEnFifoDMA = 0U;
		#if CAN_RX_INTERRUPT == STD_ON
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bDataAvaliableInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bWarningInt = 1U;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.bOverflowInt = 1U;
		#endif
		/* Rx Fifo config */
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.pRxFilterFifoList = pCanHandle->eInstance == 0 ? (FLEXCAN_RxFilterType *)s_aFlexCan0_RxFifoFilter : (FLEXCAN_RxFilterType *)s_aFlexCan2_RxFifoFilter;
		tInitCfg.tRxFifoFilterCfg.tLegacyFifoCfg.u8RxFilterFifoCnt = pCanHandle->eInstance == 0 ? (sizeof(s_aFlexCan0_RxFifoFilter) / sizeof(s_aFlexCan0_RxFifoFilter[0])) : (sizeof(
															  s_aFlexCan2_RxFifoFilter) / sizeof(s_aFlexCan2_RxFifoFilter[0]));
		#endif
		#endif

		#if CAN_FIFO_INTERRUPT == STD_ON
		tInitCfg.bEnFifoInt = 1U;
		#endif

		#if CAN_FD_ENABLE == STD_ON
		tInitCfg.bEnFd = TRUE;
		#else
		tInitCfg.bEnFd = FALSE;
		#endif

		tRetVal = BSP_CAN_LL_ProcessBaud(pCanHandle->eInstance, &tInitCfg);


		if (tRetVal == 0U)
		{
			/* initial can */
			tRetVal = FLEXCAN_Init(pCanHandle, &tInitCfg);

			FLEXCAN_Start(pCanHandle); /* Start CAN */
		}
   }

}

/**
 * @brief CAN transmit special data
 *
 * @param u8CanIndex
 */
void BSP_CAN_LL_TransmitData(FLEXCAN_HandleType *pCanHandle, uint8 TxMessageIndex)
{
    FLEXCAN_TxMsgType tTxMsg = {0};
    FLEXCAN_ErrorType tRetval;
    const static uint8_t debugBuffer[8] = {0x12, 0x34, 0x56, 0x78, 0, 0, 0, 0};

//    FCFUNC_FcOwnMemcpy(tTxMsg.aData, g_stBsp_CanTxInit[TxMessageIndex].pui8CanTxBuffer,g_stBsp_CanTxInit[TxMessageIndex].ui8Dlc , NULL);
    FCFUNC_FcOwnMemcpy(tTxMsg.aData, debugBuffer, 8 , NULL);
    tTxMsg.u32CanId = 0x102;//g_stBsp_CanTxInit[TxMessageIndex].ui32FrameId;
    tTxMsg.u8TxHandle = 0;//g_stBsp_CanTxInit[TxMessageIndex].ui8Index;

//    #if CAN_FD_ENABLE == STD_ON
//    tTxMsg.bEnFd = TRUE;
//    tTxMsg.bEnBrs = TRUE;
//    tTxMsg.u32DataLen = 12U;
//    #else
    tTxMsg.bEnFd = TRUE;
    tTxMsg.bEnBrs = TRUE;
    tTxMsg.u32DataLen = 8;
//    #endif
    tTxMsg.eDataType = FLEXCAN_FRAME_DATA;
    tTxMsg.eFrameType = FLEXCAN_ID_STD;
    if (s_aTxErrorCount[pCanHandle->eInstance] == 0)
    {
        tRetval = FLEXCAN_TransmitData(pCanHandle, &tTxMsg);
    }
    PROCESS_UNUSED_VAR(tRetval);
}

void BSP_CAN_Transmit(uint32 FrameId,uint8 *pduInfoPtr,FLEXCAN_HandleType g_tCan)
{
	FLEXCAN_TxMsgType tTxMsg = {0};
	tTxMsg.u32DataLen = 8;
    tTxMsg.bEnFd = FALSE;
    tTxMsg.bEnBrs = FALSE;
	tTxMsg.eDataType = FLEXCAN_FRAME_DATA;
	tTxMsg.eFrameType = FLEXCAN_ID_STD;
	uint8 Tx_Mb = 0xFF;
	for(uint8 i = 0;i < CANTX_NUM;i++)
	{
		if(FrameId == g_stBsp_CanTxInit[i].ui32FrameId)
		{
			Tx_Mb = g_stBsp_CanTxInit[i].ui8MBindex;
		}
	}
	if(Tx_Mb == 0xFF)
	{
		return;
	}
	tTxMsg.u8TxHandle = Tx_Mb;
	tTxMsg.u32CanId = FrameId;
	//tTxMsg.aData = pduInfoPtr;
    FCFUNC_FcOwnMemcpy(tTxMsg.aData, pduInfoPtr,8 , NULL);
    if(g_tCan1.eInstance == g_tCan.eInstance)
    {
//		FLEXCAN_TransmitData(&g_tCan1, &tTxMsg);
    }
    else if(g_tCan2.eInstance == g_tCan.eInstance)
    {
    	FLEXCAN_TransmitData(&g_tCan2, &tTxMsg);
    }
}

typedef struct
{
	uint8 head;
	uint8 tail;
	uint8 FifoBuffer[30][8];
}XcpFifoStruct;

XcpFifoStruct XcpFifo;

void  XcpFifoStructInit(void)
{
	XcpFifo.head = 0;
	XcpFifo.tail = 0;
	memset(XcpFifo.FifoBuffer,0,sizeof(XcpFifo.FifoBuffer));
}

void ApplXcpSend( uint8_t len,const uint8_t* msg )
{
	if(((XcpFifo.tail + 1u)% 30u) != XcpFifo.head)
	{
		memset(XcpFifo.FifoBuffer[XcpFifo.tail],0,sizeof(XcpFifo.FifoBuffer[XcpFifo.tail]));
		FCFUNC_FcOwnMemcpy(XcpFifo.FifoBuffer[XcpFifo.tail], msg,len , NULL);
		XcpFifo.tail = ((XcpFifo.tail + 1u) % 30u);
	}
}

void XcpEventTransmit_1ms(void)
{
	if(XcpFifo.head  != XcpFifo.tail)
	{
		if( 0 == BSP_XCP_Transmit(8,XcpFifo.FifoBuffer[XcpFifo.head],XCP_TX_PDUID))
		{
			XcpFifo.head = ((XcpFifo.head + 1u) % 30u);
		}
	}
}

FLEXCAN_ErrorType BSP_XCP_Transmit(uint8_t len,const uint8_t* msg,uint32 ID)
{
	uint8 i;
	FLEXCAN_TxMsgType tTxMsg = {0};
	FLEXCAN_ErrorType     tRetVal;
	tTxMsg.u32DataLen = len;
    tTxMsg.bEnFd = FALSE;
    tTxMsg.bEnBrs = FALSE;
	tTxMsg.eDataType = FLEXCAN_FRAME_DATA;
	tTxMsg.eFrameType = FLEXCAN_ID_STD;

	for(i = 0;i < CANTX_NUM;i++)
	{
		if(ID == g_stBsp_CanTxInit[i].ui32FrameId)
		{
			tTxMsg.u8TxHandle = g_stBsp_CanTxInit[i].ui8MBindex;
			break;
		}
	}
	if(i == CANTX_NUM)
	{
		return 0xAA;
	}

	tTxMsg.u32CanId = ID;
	FCFUNC_FcOwnMemcpy(tTxMsg.aData, msg,len , NULL);
	tRetVal = FLEXCAN_TransmitData(&g_tCan1, &tTxMsg);
	return tRetVal;
}

/* ################################################################################## */
/* ################################ Global Functions ################################ */

void BSP_CAN_Init(void)
{
    #if FLEXCAN_USED_INSTANCE0 == STD_ON
    BSP_CAN_LL_Init(&g_tCan0);
    #endif /* end for #if FLEXCAN_USED_INSTANCE0 == STD_ON */

    #if FLEXCAN_USED_INSTANCE1 == STD_ON
    BSP_CAN_LL_Init(&g_tCan1);
	#endif /* end for #if FLEXCAN_USED_INSTANCE1 == STD_ON */
	#if FLEXCAN_USED_INSTANCE2 == STD_ON
    BSP_CAN_LL_Init(&g_tCan2);
    #endif /* end for #if FLEXCAN_USED_INSTANCE2 == STD_ON */
}

void BSP_CAN_TransmitData(void)
{
    #if FLEXCAN_USED_INSTANCE0 == STD_ON
//    BSP_CAN_LL_TransmitData(&g_tCan0);
    #endif /* end for #if FLEXCAN_USED_INSTANCE0 == STD_ON */

    #if FLEXCAN_USED_INSTANCE1 == STD_ON
//    BSP_CAN_LL_TransmitData(&g_tCan1, 0);
    #endif /* end for #if FLEXCAN_USED_INSTANCE1 == STD_ON */

	#if FLEXCAN_USED_INSTANCE2 == STD_ON
	//    BSP_CAN_LL_TransmitData(&g_tCan2);
	#endif /* end for #if FLEXCAN_USED_INSTANCE2 == STD_ON */

}

static void CAN_Error_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_ErrorInfoType *pErrorInfo)
{
    s_aTxErrorCount[pCanHandle->eInstance]++;
    PROCESS_UNUSED_VAR(pErrorInfo);
}

static void CAN1_Error_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_ErrorInfoType *pErrorInfo)
{
	//
}

static void CAN_FifoIssue_CallBack(FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue)
{
    PROCESS_UNUSED_VAR(pHandle);
    PROCESS_UNUSED_VAR(pFifoIssue);
}

static void CAN1_FifoIssue_CallBack(FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue)
{
	//
}

#define DTC_E00888_ViuPdmCanBusOff 1
extern void set_DTC_Exist(uint8_t dtc_index, bool status);
extern void Set_DTCOccuCounter_Down(uint8_t dtc_index);
extern uint8_t DTC_checkTRC(uint8_t dtc_index);

/*Send message successfully callback function*/
static void CAN_Tx_CallBack(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle)
{
#ifndef ECU_ADDRESS_BLDC
    s_aTxErrorCount[pCanHandle->eInstance] = 0U;

    CanSM_ClrBusOff();

	set_DTC_Exist(DTC_E00888_ViuPdmCanBusOff, 0);

	if(DTC_checkTRC(DTC_E00888_ViuPdmCanBusOff) == 1)
	{
    	Set_DTCOccuCounter_Down(1);
	}

    if(0 == GetFristFrameFlag())
    {
    	SetFristFrameFlag(1);
    }
    PROCESS_UNUSED_VAR(u8TxHandle);
    uint8_t g_ui8TxMallIndex;
    #ifdef ECU_ADDRESS_PDM_FL
    g_ui8TxMallIndex = TXMAILBOX_779_INDEX;
    #endif
    #ifdef ECU_ADDRESS_PDM_FR
    g_ui8TxMallIndex = TXMAILBOX_778_INDEX;
    #endif
    if(u8TxHandle == g_ui8TxMallIndex)
    {
    	CanTp_L_Data_Confirm();
    }
#endif
}

static void CAN1_Tx_CallBack(FLEXCAN_HandleType *pCanHandle, uint8_t u8TxHandle)
{
	(void)pCanHandle;
	(void)u8TxHandle;
}

void Analysis_Com_signal_Task(void)
{
	for(uint i = 0 ; i < CANRX_NUM ; i++)
	{
		if(0 != g_stBsp_CanRxInit[i].ui8CanRx_Flag)
		{
			AnalysisReceiveSignals(g_stBsp_CanRxInit[i].stFLEXCAN_RxFilter.u32RxCanId ,\
					g_stBsp_CanRxInit[i].ui8StartBit_Index,g_stBsp_CanRxInit[i].pui8CanRxBuffer);
			g_stBsp_CanRxInit[i].ui8CanRx_Flag = 0;
		}
	}
}

static void CAN_Rx_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_RxMsgType *pRxMsg)
{
	uint16 i;

#ifndef ECU_ADDRESS_BLDC
	CanSM_ClrBusOff();

	set_DTC_Exist(DTC_E00888_ViuPdmCanBusOff, 0);

	if(DTC_checkTRC(DTC_E00888_ViuPdmCanBusOff) == 1)
	{
    	Set_DTCOccuCounter_Down(1);
	}
#endif
	(void)pCanHandle;

	/*Receive Xcp Frame */
	if(XCP_RX_PDUID == pRxMsg->u32CanId)
	{
		Set_XcpReceiveBuffer(pRxMsg->aData);
		Set_XcpReceiveFlag(1);
		return;
	}

	for( i = 0 ; i < CANRX_NUM ; i++)
	{
		if(g_stBsp_CanRxInit[i].stFLEXCAN_RxFilter.u32RxCanId == pRxMsg->u32CanId)
		{
			FCFUNC_FcOwnMemcpy(g_stBsp_CanRxInit[i].pui8CanRxBuffer, pRxMsg->aData, pRxMsg->u32DataLen, NULL);
//    	    E2E_WaitForFirstData(g_stBsp_CanRxInit[i].stFLEXCAN_RxFilter.u32RxCanId);
//            E2E_MainFunction(g_stBsp_CanRxInit[i].stFLEXCAN_RxFilter.u32RxCanId, &g_stBsp_CanRxInit[i]);
			*(g_stBsp_CanRxInit[i].pui16CanRxTimeoutCnt) = 0;
			g_stBsp_CanRxInit[i].ui8TimeOut_Flag = 0;
			g_stBsp_CanRxInit[i].ui8Dlc = pRxMsg->u32DataLen;
			break;
		}
	}
#if IF_USE_PDUR
	if(i < CANRX_NUM)
	{
		PduR_CanIfRxIndication(&g_stBsp_CanRxInit[i]);
	}
#ifndef ECU_ADDRESS_BLDC
	if( 8 == pRxMsg->u32DataLen)
	{

		if((0x400 == (pRxMsg->u32CanId & 0xF80))&&(Open == getUDS_NmRx()))
		{
			AsrNm_PduRxIndication(pRxMsg);
		}
	 }
#endif

#else
	if(pRxMsg->u32CanId == CAN_NM_ID)
	{
		AsrNm_PduRxIndication(&g_stBsp_CanRxInit[i]);
	}
	else if((pRxMsg->u32CanId == CAN_DIAG_PHY_ID) || (pRxMsg->u32CanId == CAN_DIAG_FUNC_ID))
	{
//		PushL_Fifo(pRxMsg->u32CanId,pRxMsg->u32DataLen,pRxMsg->aData);
	}
	else
	{
		g_stBsp_CanRxInit[i].ui8CanRx_Flag = 1;
	}
#endif
}

extern Recv_DataBuf_T Recv_DataBuf;
static void CAN1_Rx_CallBack(FLEXCAN_HandleType *pCanHandle, FLEXCAN_RxMsgType *pRxMsg)
{
	(void)pCanHandle;

	if(pRxMsg->u32CanId == 0x100)
	{
		Recv_DataBuf.Angle = (uint16_t)(((uint16_t)pRxMsg->aData[1] << 8) + (uint16_t)pRxMsg->aData[0]);
        extern void Motor_Encoder_CAN_IRQ(void);
        Motor_Encoder_CAN_IRQ();
	}
}

void CanRxTimeOutCheckOut_1ms(void)
{
	for(uint8 i = 0 ; i < CANRX_NUM ; i++)
	{
		if(0u != g_stBsp_CanRxInit[i].ui16CanRxTimeoutThreshold)
				//&& (*g_stBsp_CanRxInit[i].pui16CanRxTimeoutCnt) <= g_stBsp_CanRxInit[i].ui16CanRxTimeoutThreshold)
		{
			if((*(g_stBsp_CanRxInit[i].pui16CanRxTimeoutCnt)) <= 5000)
			{
				(*(g_stBsp_CanRxInit[i].pui16CanRxTimeoutCnt))++;
			}
			else
			{
				(*(g_stBsp_CanRxInit[i].pui16CanRxTimeoutCnt)) = (uint16)5000;
			}
		}
	}
}

void GetCanRxTimeOutResult_100ms(void)
{
	uint16 RxTimeOutNominal;
	for(uint8 i = 0 ; i < CANRX_NUM ; i++)
	{
		if((g_stBsp_CanRxInit[i].ui16CanRxTimeoutThreshold) <= 500)
		{
			RxTimeOutNominal = (uint16)((g_stBsp_CanRxInit[i].ui16CanRxTimeoutThreshold) * 10);
		}
		else
		{
			RxTimeOutNominal = 5000;
		}
		if((*(g_stBsp_CanRxInit[i].pui16CanRxTimeoutCnt)) < RxTimeOutNominal)
		{
			 continue;
		}
		else
		{
			if(0 == g_stBsp_CanRxInit[i].ui8TimeOut_Flag)
			{
				g_stBsp_CanRxInit[i].ui8TimeOut_Flag = 1;
			}
			else{}
		}
	}
#ifdef ECU_ADDRESS_PDM_FL
	Can_CheckTimeOut_DRD_FL_St_0x150();
	Can_CheckTimeOut_TBOX_TimeInfo_0x5E2();
	Can_CheckTimeOut_TVIU_Info_Prof1A_0x1C2();
	Can_CheckTimeOut_VIU0_0x2A0();
	Can_CheckTimeOut_VIU0_0x3AE();
	Can_CheckTimeOut_VIU0_0x3AF();
	Can_CheckTimeOut_VIU0_CDC_0x3AA();
#endif

#ifdef ECU_ADDRESS_PDM_FR
	Can_CheckTimeOut_DRD_FR_St_0x151();
	Can_CheckTimeOut_TBOX_TimeInfo_0x5E2();
	Can_CheckTimeOut_VIU_Info_Prof1A_0x1C2();
	Can_CheckTimeOut_VIU_0x2A1();
	Can_CheckTimeOut_VIU1_0x3AE();
	Can_CheckTimeOut_VIU1_0x3AF();
	Can_CheckTimeOut_VIU1_CDC_0x3AB();
#endif

}

#ifdef ECU_ADDRESS_PDM_FL

Std_ReturnType Can_CheckTimeOut_DRD_FL_St_0x150(void)
{
	if(1 == g_stBsp_CanRxInit[0].ui8TimeOut_Flag)
	{
		Com_DRD_FL_DoorOpenAg = 0xFF;
		Com_DRD_FL_ObstclXDst = 0;
		Com_DRD_FL_ObstclYDst = 0;
		Com_DRD_FL_ObstclZDst = 0;
		Com_DRD_FL_ObstclSpd = 0;
		Com_DRD_FL_Err = 0;
		Com_DRD_FL_St = 0xF;
		Com_DRD_FL_InstallPosnLrnSt = 0x3;
		Com_DRD_FL_Req = 0;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_TBOX_TimeInfo_0x5E2(void)
{
	if(1 == g_stBsp_CanRxInit[1].ui8TimeOut_Flag)
	{
		Com_TBOX_TimeYear = 2000;
		Com_TBOX_TimeMonth = 1;
		Com_TBOX_TimeDay = 1;
		Com_TBOX_TimeHour = 0;
		Com_TBOX_TimeMinute = 0;
		Com_TBOX_TimeSecond = 0;
		Com_TBOX_TimeZone = 0;
		Com_TBOX_TimeZoneNum = 0;
		Com_TBOX_TimeFlag = 0;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_TVIU_Info_Prof1A_0x1C2(void)
{
	if(1 == g_stBsp_CanRxInit[2].ui8TimeOut_Flag)
	{
		Com_VIU_Info_Prof1A_Checksum = 0;
		Com_VIU_Info_Prof1A_Counter = 0xF;
		Com_VIU_CarMode = 0xF;
		Com_VIU_UsageMode = 0xF;
		Com_VIU_PowerModeFltFlag = 0x3;
		Com_VIU_PowerMode = 0x3;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU0_0x2A0(void)
{
	if(1 == g_stBsp_CanRxInit[3].ui8TimeOut_Flag)
	{
		Com_VIU_RRDoorSt = 0x3;
		Com_VIU_RLDoorSt = 0x3;
		Com_VIU_PassDoorSt = 0x3;
		Com_VIU_DrvrDoorSt = 0x3;
		Com_VIU_DrvrDoorLockSt3 = 0;
		Com_VIU_DrvrDoorLockSt2 = 0x3;
		Com_VIU_TailgateSt = 0xF;
		Com_VIU_FLWinOpenDeg = 0x7F;
		Com_VIU_FRWinOpenDeg = 0x7F;
		Com_VIU_RLWinOpenDeg = 0x7F;
		Com_VIU_RRWinOpenDeg = 0x7F;
		Com_VDC_AmbT = 0xFF;
		Com_VIU_DrvrDoorLockStVld = 0;
		Com_VIU_DrvrDoorLockSt = 0x3;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU0_0x3AE(void)
{
	if(1 == g_stBsp_CanRxInit[4].ui8TimeOut_Flag)
	{
		Com_IPB_VehicleSpeedValid = 0;
		Com_VDC_brakePedalSts = 0;
		Com_IPB_VehicleSpeed = 0x1FFF;
		Com_VDC_TotalRang = 0xFFFFF;
		Com_VDC_actualGear = 0;
		Com_VDC_actualGearValid = 0;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU0_0x3AF(void)
{
	if(1 == g_stBsp_CanRxInit[5].ui8TimeOut_Flag)
	{
		Com_ABM_IMU_LongAcceleration = 0x3FFF;
		Com_ABM_IMU_LateralAcceleration = 0x3FFF;
		Com_ABM_IMU_YawRate = 0xFFFF;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU0_CDC_0x3AA(void)
{
	if(1 == g_stBsp_CanRxInit[6].ui8TimeOut_Flag)
	{
		Com_CDC_FullOpenDegSet = 0;
		Com_CDC_ModSet = 0;
		Com_CDC_PDMFL_Ctrl = 0;
		Com_CDC_HndFeelSet = 0;
		Com_CDC_OpenSpdSet = 0;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}



#endif

#ifdef ECU_ADDRESS_PDM_FR
Std_ReturnType Can_CheckTimeOut_DRD_FR_St_0x151(void)
{
	if(1 == g_stBsp_CanRxInit[0].ui8TimeOut_Flag)
	{
		Com_DRD_FR_DoorOpenAg = 0xFF;
		Com_DRD_FR_ObstclXDst = 0;
		Com_DRD_FR_ObstclYDst = 0;
		Com_DRD_FR_ObstclZDst = 0;
		Com_DRD_FR_ObstclSpd = 0;
		Com_DRD_FR_Err = 0;
		Com_DRD_FR_St = 0xF;
		Com_DRD_FR_InstallPosnLrnSt = 0x3;
		Com_DRD_FR_Req = 0;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_TBOX_TimeInfo_0x5E2(void)
{
	if(1 == g_stBsp_CanRxInit[1].ui8TimeOut_Flag)
	{
		Com_TBOX_TimeYear = 2000;
		Com_TBOX_TimeMonth = 1;
		Com_TBOX_TimeDay = 1;
		Com_TBOX_TimeHour = 0;
		Com_TBOX_TimeMinute = 0;
		Com_TBOX_TimeSecond = 0;
		Com_TBOX_TimeZone = 0;
		Com_TBOX_TimeZoneNum = 0;
		Com_TBOX_TimeFlag = 0;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU_Info_Prof1A_0x1C2(void)
{
	if(1 == g_stBsp_CanRxInit[2].ui8TimeOut_Flag)
	{
		Com_VIU_Info_Prof1A_Checksum = 0;
		Com_VIU_Info_Prof1A_Counter = 0xF;
		Com_VIU_CarMode = 0xF;
		Com_VIU_UsageMode = 0xF;
		Com_VIU_PowerModeFltFlag = 0x3;
		Com_VIU_PowerMode = 0x3;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU_0x2A1(void)
{
	if(1 == g_stBsp_CanRxInit[3].ui8TimeOut_Flag)
	{
		Com_VIU_RRDoorSt = 0x3;
		Com_VIU_RLDoorSt = 0x3;
		Com_VIU_PassDoorSt = 0x3;
		Com_VIU_DrvrDoorSt = 0x3;
		Com_VIU_PassDoorLockSt3 = 0;
		Com_VIU_PassDoorLockSt2 = 0x3;
		Com_VIU_TailgateSt = 0xF;
		Com_VIU_FLWinOpenDeg = 0x7F;
		Com_VIU_FRWinOpenDeg = 0x7F;
		Com_VIU_RLWinOpenDeg = 0x7F;
		Com_VIU_RRWinOpenDeg = 0x7F;
		Com_VDC_AmbT = 0xFF;
		Com_VIU_PassDoorLockSt = 0x3;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU1_0x3AE(void)
{
	if(1 == g_stBsp_CanRxInit[4].ui8TimeOut_Flag)
	{
		Com_IPB_VehicleSpeedValid = 0;
		Com_VDC_brakePedalSts = 0;
		Com_IPB_VehicleSpeed = 0x1FFF;
		Com_VDC_TotalRang = 0xFFFFF;
		Com_VDC_actualGear = 0;
		Com_VDC_actualGearValid = 0;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU1_0x3AF(void)
{
	if(1 == g_stBsp_CanRxInit[5].ui8TimeOut_Flag)
	{
		Com_ABM_IMU_LongAcceleration = 0x3FFF;
		Com_ABM_IMU_LateralAcceleration = 0x3FFF;
		Com_ABM_IMU_YawRate = 0xFFFF;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

Std_ReturnType Can_CheckTimeOut_VIU1_CDC_0x3AB(void)
{
	if(1 == g_stBsp_CanRxInit[6].ui8TimeOut_Flag)
	{
		Com_CDC_OpenSpdSet = 0;
		Com_CDC_FullOpenDegSet = 0;
		Com_CDC_ModSet = 0;
		Com_CDC_PDMFR_Ctrl = 0;
		Com_CDC_HndFeelSet = 0;
		Com_VIU_PassSeatOccptSt = 0x3;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}
#endif






