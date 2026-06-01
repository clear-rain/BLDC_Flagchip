#include "SBC_Cfg.h"
#include "SBC_Driver.h"
#include "SBC_Types.h"
#include "SBC.h"
// #include "Dio.h"

#define SBC_WDG_FEED_CNT 18U

extern const uint8_t gau8_SBCStatAddrBuf[];
extern const SBC_Reg_t gtSBC_CtrlRegBuff[];
extern const SBC_Reg_t gtSBC_SwkCtrlRegBuff[];
extern const SBC_Reg_t gtSBC_SwkTrimCtrlRegBuff[];
uint8_t  gui8_SbcWk0 = 0x00U;
uint8_t  gui8_SbcWk1 = 0x00U;

uint8_t  gui8_SbcResetReason = 0x00u;
uint8_t  gui8_SbcStopReason = 0x00u;
E_CDD_SBC_MODE  g_eSBC_RunMode = e_CDD_SBC_INIT_MODE;
E_CDD_SBC_MODE  g_eSBC_RunModePre = e_CDD_SBC_NORMAL_MODE;
static E_CDD_SBC_MODE  s_eSBC_RunModePre = e_CDD_SBC_INIT_MODE;
static uint8_t  sui8_NormalModeCnt = 0U;
static uint8_t  sui8_StopCnt = 0U;

static uint16 su16_UpaSyncTxData;
__attribute__((aligned(16))) uint16_t gau16_SBCSpiRxBuff[SBC_ALL_REG_NUM] ;
static __attribute__((aligned(16))) uint16_t sau16_SBCSpiTxBuff[SBC_ALL_REG_NUM] ;

uint16_t g_ui16WdgCount = 1000U;
static SBC_Reg_t  stSBC_CtrlRegBuff[SBC_CTRL_REG_NUM];

static void SBC_SwkCfg(void);

void Cdd_SbcSpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr)
{
//    pFcspiHandle = pFcspiHandle;
//    bIsInIsr = bIsInIsr;
}
void Cdd_SbcTurnOnVcc2(void)
{
    uint8_t u8RxData;
	SBC_SpiInit();
    SBC_ReadRegSync(SBC_M_S_CTRL_ADDR, &gui8_SbcStopReason);
	SBC_ReadRegSync(SBC_M_S_CTRL_ADDR, &gui8_SbcStopReason);
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR, 0x0C);
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR, 0x0C);    
}
/**
 * *********************************************************************************************************************
 * Name         :
 * Description  :
 * Algorithm    : Void
 * Input        : Void
 * Output       : Void
 * Return       : Void
 * *********************************************************************************************************************
 */
void SBC_AllRegsInitSync(void)
{
    uint8_t u8RegIndex;
    uint8_t u8TxCnt = 0;
    uint8_t u8RxData = 0;

    g_eSBC_RunMode = e_CDD_SBC_NORMAL_MODE;
    SBC_DiagInit();

    SBC_ReadRegSync(SBC_WK_STAT_0_ADDR, &gui8_SbcWk0);
    SBC_ReadRegSync(SBC_WK_STAT_1_ADDR, &gui8_SbcWk1);
    SBC_ReadRegSync(SBC_DEV_STAT_ADDR, &gui8_SbcResetReason);
    // todo: 通过运行模式/VCP输出/配置后读取与配置是否一致来判断  初始化失败
    SBC_WriteRegSync(SBC_HW_CTRL_0_ADDR, 0x40);
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR, 0xCC);// software reset
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR, 0x0C);
    // read family id
    if (e_CDD_SBC_ERROR == SBC_Diag_ReadChipId())   //todo: 初始化失败的话，需要增加尝试恢复逻辑，具体需求待探讨
    {
        g_eSBC_RunMode = e_CDD_SBC_SPI_ERROR_MODE;
        return;
    };
    // feed watchdog
    SBC_WriteRegSync(SBC_WD_CTRL_ADDR, SBC_WDG_VALUE);
    // set sbc to normal mode and open VCC2
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR, 0x0C);

    sau16_SBCSpiTxBuff[u8TxCnt++] = SBC_FAM_PROD_STATE_ADDR;
    for (u8RegIndex = 0; u8RegIndex < SBC_CTRL_REG_NUM; u8RegIndex++)
    {
        stSBC_CtrlRegBuff[u8RegIndex].u8Addr = gtSBC_CtrlRegBuff[u8RegIndex].u8Addr;
        stSBC_CtrlRegBuff[u8RegIndex].u8Data = gtSBC_CtrlRegBuff[u8RegIndex].u8Data;

        su16_UpaSyncTxData = gtSBC_CtrlRegBuff[u8RegIndex].u8Data;
        if (1u == gtSBC_CtrlRegBuff[u8RegIndex].u8OpFlg)
        {
            su16_UpaSyncTxData = (su16_UpaSyncTxData << 8U) + (gtSBC_CtrlRegBuff[u8RegIndex].u8Addr | 0x80U);
        }
        else
        {
            su16_UpaSyncTxData = (su16_UpaSyncTxData << 8U) + gtSBC_CtrlRegBuff[u8RegIndex].u8Addr;
        }
        sau16_SBCSpiTxBuff[u8TxCnt++] = su16_UpaSyncTxData;
    } // end for

    for (u8RegIndex = 0; u8RegIndex < SBC_STAT_REG_NUM; u8RegIndex++)
    {
        su16_UpaSyncTxData = gau8_SBCStatAddrBuf[u8RegIndex];
        sau16_SBCSpiTxBuff[u8TxCnt++] = su16_UpaSyncTxData;
    } // end for
    SBC_SpiSendDataSetEB((uint8_t *)sau16_SBCSpiTxBuff, (uint8_t *)gau16_SBCSpiRxBuff, SBC_ALL_REG_NUM);
    SBC_SpiSendDataSeqAsync();
    sui8_NormalModeCnt = 100u;
}
static void SBC_WdgFeed(void)
{
    static uint8_t u8WdgFeedCnt = 0;
    u8WdgFeedCnt = (u8WdgFeedCnt + 1) % 5; //  feed wdg once per 50ms

    /***********************************   MCAL Set trigger condition count   **************************************/
    g_ui16WdgCount = (g_ui16WdgCount > 10u) ? g_ui16WdgCount - 10u : 0U;

    if (0U == g_ui16WdgCount)
    {
        stSBC_CtrlRegBuff[2].u8Data = 0x00;
        stSBC_CtrlRegBuff[2].u8Addr = SBC_FAM_PROD_STATE_ADDR;
        stSBC_CtrlRegBuff[2].u8OpFlg = 0;
        return;
    }
/***********************************  MCAL set trigger condition End **************************************/
    //
    if(0U == u8WdgFeedCnt)
    {
        stSBC_CtrlRegBuff[2].u8Data = SBC_WDG_VALUE; // //53 74 55 D4
        stSBC_CtrlRegBuff[2].u8Addr = SBC_WD_CTRL_ADDR;
        stSBC_CtrlRegBuff[2].u8OpFlg = 1;
    }
    else
    {
        stSBC_CtrlRegBuff[2].u8Data = 0x00;
        stSBC_CtrlRegBuff[2].u8Addr = SBC_FAM_PROD_STATE_ADDR;
        stSBC_CtrlRegBuff[2].u8OpFlg = 0;
    }
}

static void SBC_DataDealToSend(void)
{
    uint8_t u8RegIndex;
    uint8_t u8TxCnt = 0;
    sau16_SBCSpiTxBuff[u8TxCnt++] = SBC_FAM_PROD_STATE_ADDR;
    for(u8RegIndex = 0; u8RegIndex < SBC_CTRL_REG_NUM; u8RegIndex++)
    {
        if(1u == stSBC_CtrlRegBuff[u8RegIndex].u8OpFlg)
        {
            stSBC_CtrlRegBuff[u8RegIndex].u8OpFlg = 0u;
            su16_UpaSyncTxData = stSBC_CtrlRegBuff[u8RegIndex].u8Data;
            su16_UpaSyncTxData = (su16_UpaSyncTxData << 8U) + (stSBC_CtrlRegBuff[u8RegIndex].u8Addr | 0x80U);
        }
        else
        {
            su16_UpaSyncTxData = (stSBC_CtrlRegBuff[u8RegIndex].u8Addr & 0x00FFU);
        }
        sau16_SBCSpiTxBuff[u8TxCnt++] = su16_UpaSyncTxData;
    }// end for

    for (u8RegIndex = 0; u8RegIndex < SBC_STAT_REG_NUM; u8RegIndex++)
    {
        su16_UpaSyncTxData = (gau8_SBCStatAddrBuf[u8RegIndex] & 0x00FFU);
        sau16_SBCSpiTxBuff[u8TxCnt++] = su16_UpaSyncTxData;
    }// end for 
}

void SBC_NormalRun(void)
{
    if(g_eSBC_RunMode != e_CDD_SBC_NORMAL_MODE)
    {
        g_eSBC_RunModePre = g_eSBC_RunMode;
        return;
    }
    if (0 != sui8_NormalModeCnt)
    {
        SBC_DiagDeal(); // 
    }
    else
    {
        sui8_NormalModeCnt = 100;
        SBC_AllRegsInitSync();
    }
    SBC_WdgFeed();
    SBC_DataDealToSend();
    SBC_SpiSendDataSeqAsync();
}

void SBC_RestartModeRun(void)
{
    if(e_CDD_SBC_RESET_MODE != g_eSBC_RunMode)
    {
        return;
    }
    SBC_WriteRegSync(SBC_HW_CTRL_0_ADDR,0x00);
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR,0xC0);
}
static void SBC_SwkCfg(void)
{
    uint8_t u8_idx = 0u;
    uint8_t u8RxData = 0u;
    // close VCP
    SBC_WriteRegSync(SBC_HW_CTRL_0_ADDR,0x00);
    SBC_WriteRegSync(SBC_HW_CTRL_0_ADDR,0x00);

  
    SBC_WriteRegSync(SBC_SWK_CTRL_ADDR,0x60U);
    // WK_CTRL 0
    SBC_WriteRegSync(SBC_WK_CTRL_0_ADDR,0x04);
    // trun off CAN
    SBC_WriteRegSync(SBC_BUS_CTRL_0_ADDR,0x00);
    // cfg CDR
    SBC_WriteRegSync(SBC_SWK_BTL0_CTRL_ADDR,0xA0);
    SBC_WriteRegSync(SBC_SWK_CDR_CTRL_2_ADDR,0x00);
    SBC_WriteRegSync(SBC_SWK_CDR_LIMIT_HIGH_CTRL_ADDR,0xA8);
    SBC_WriteRegSync(SBC_SWK_CDR_LIMIT_LOW_CTRL_ADDR,0x98);
    // Set CDR ON
    SBC_WriteRegSync(SBC_SWK_CDR_CTRL_1_ADDR,0x05);
    SBC_ReadRegSync(SBC_SWK_OPT_CTRL_ADDR,&u8RxData);
    SBC_WriteRegSync(SBC_SWK_OPT_CTRL_ADDR,(u8RxData|0x80));
    SBC_WriteRegSync(SBC_SWK_CTRL_ADDR,0x00U);

    // set SWK CAN ID/MASK/DLC/DATAS
    for (u8_idx = 3u; u8_idx < 20u;u8_idx ++)
    {
        SBC_WriteRegSync(gtSBC_SwkCtrlRegBuff[u8_idx].u8Addr,gtSBC_SwkCtrlRegBuff[u8_idx].u8Data);
    }
    
    SBC_WriteRegSync(SBC_BUS_STAT_ADDR,0xFF);

    // GPIO CTRL
    SBC_WriteRegSync(SBC_GPIO_CTRL_ADDR,0x03);
    // WK_CTRL 1
    SBC_WriteRegSync(SBC_WK_CTRL_1_ADDR,0x01);
    // WK_PUPD_CTRL
    SBC_WriteRegSync(SBC_WK_PUPD_CTRL_ADDR,0x01);
    // TIMER_CTRL
    SBC_WriteRegSync(SBC_TIMER_CTRL_ADDR,0x43);//0x31//0x43


    SBC_WriteRegSync(SBC_WK_STAT_0_ADDR,0x00U);
    SBC_WriteRegSync(SBC_WK_STAT_1_ADDR, 0x00U);
    SBC_WriteRegSync(SBC_SWK_OPT_CTRL_ADDR,0x80U);
    SBC_WriteRegSync(SBC_SWK_CAN_FD_ADDR,0x21U);
    SBC_WriteRegSync(SBC_SWK_CTRL_ADDR,0x01U);
    SBC_WriteRegSync(SBC_BUS_STAT_ADDR,0x00U);
    SBC_WriteRegSync(SBC_BUS_CTRL_0_ADDR,0x05U);
    

}

void SBC_SleepRun(void)
{
    uint8_t u8_idx = 0u;
    uint8_t u8RxData = 0u;
    uint8_t val = 0u;
    if(g_eSBC_RunMode != e_CDD_SBC_SLEEP_MODE)
    {
        return;
    }
    SBC_SwkCfg();

    // set sbc to sleep mode
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR,0x40U);
    SBC_WriteRegSync(SBC_M_S_CTRL_ADDR,0x40U);
}

void SBC_StopRun(void)
{
    uint8_t u8_idx = 0u;
    uint8_t u8RxData = 0u;
    if(g_eSBC_RunMode != e_CDD_SBC_STOP_MODE)
    {
        return;
    }
    if(sui8_StopCnt == 0)
    {
        SBC_SwkCfg();
        // close wdg
        SBC_WriteRegSync(SBC_WD_CTRL_ADDR,SBC_WDG_VALUE);
        // set sbc to stop mode
        SBC_WriteRegSync(SBC_M_S_CTRL_ADDR,0x80U);
        sui8_StopCnt = 100;
    }
    else
    {
        return;
    }
}
E_CDD_SBC_ERR_STATUS Cdd_SbcModeSet(E_CDD_SBC_MODE e_mode)
{
	if (e_CDD_SBC_MAX_MODE <= e_mode)
	{
		return e_CDD_SBC_ERROR;
	}

    g_eSBC_RunMode = e_mode;

    if(g_eSBC_RunModePre != g_eSBC_RunMode)
    {
        g_eSBC_RunModePre = g_eSBC_RunMode;
    }
    else
    {
        return e_CDD_SBC_OK;
    }
    switch(g_eSBC_RunMode){
        case e_CDD_SBC_NORMAL_MODE:
            sui8_NormalModeCnt = 0;
            break;
        case e_CDD_SBC_STOP_MODE:
            sui8_StopCnt = 0;
            break;
        case e_CDD_SBC_SLEEP_MODE:
            break;
        case e_CDD_SBC_RESET_MODE:
            break;
        default:
            break;
    }
    return e_CDD_SBC_OK;
}


