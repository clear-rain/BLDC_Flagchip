/*
 * MotorDriver_Diag.c
 *
 *  Created on: 2025年3月19日
 *      Author: 14013
 */

#include "MotorDriver_Diag.h"
#include "MotorDriver_Cfg.h"
#include "MotorDriver_Driver.h"
#include "MotorControl.h"
#include "hall.h"
#include "IoHwAb_Adc.h"
#include "AsrNm.h"

TLE92104_FaultIndicator_t  g_unFaultIndicator = {.all_flags = 0};
/*Off-Line Diagnose*/
MotorDriver_Offline_Diag_error g_unMotorDriverOfflineDiagErrorCode = { .errors = 0 };

static uint16 Offline_diag_count = 0;
static uint8 Offline_diag_started = 0;
MotorErrorStatus_t  g_unMotorErrorStatus = {.byte = 0};
uint8  MotorDriver_Offline_diag_exit_flag = 0;
extern uint8 g_ui8HallInterruptOpened;
extern sint16 g_si16MotorDuty;

uint32 MCU_Voltage_for_Off_Line_Diag = 12000;
void SH1PullUpSH2PullDownDiag(void)
{
	MCU_Voltage_for_Off_Line_Diag = CDD_GetBatmVolt();
	uint32 l_u32Short2BatVol = Lib_Linear_6P_Interpo(MCU_Voltage_for_Off_Line_Diag,9000,11000,12000,13000,14000,16000,\
													1980,2416,2638,2855,3078,3515);
	if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]<330 && g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]>230 \
			&& g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]<330 && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]>230)//M+:285 M-:285~286
    {
    	g_unMotorDriverOfflineDiagErrorCode.errors = 0;
    }
    else if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]<50 && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]<50)//M+:13~14 M-:15~17
    {
    	g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2gnd_error = 1;
    }
	else if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]<300 && g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]>200\
			&& g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]>500 && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]<650)//M+:250 M-:578
    {
    	g_unMotorDriverOfflineDiagErrorCode.bits.motoropenload_error = 1;
    }
	else if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]>=(l_u32Short2BatVol-200) && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]>=(l_u32Short2BatVol-200))//M+:3145 M-:3142
	{
		g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2vcc_error = 1;
	}
}

void SH1PullDownSH2PullUpDiag(void)
{
	MCU_Voltage_for_Off_Line_Diag = CDD_GetBatmVolt();
	uint32 l_u32Short2BatVol = Lib_Linear_6P_Interpo(MCU_Voltage_for_Off_Line_Diag,9000,11000,12000,13000,14000,16000,\
													1980,2416,2638,2855,3078,3515);
	if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]<330 && g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]>230 \
			&& g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]<330 && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]>230)//M+:285 M-:285~288
	{
//            g_unMotorDriverOfflineDiagErrorCode.bits.no_error = DRV8706_NO_ERROR;
	}
	else if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]>=(l_u32Short2BatVol-200) && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]>=(l_u32Short2BatVol-200))//M+:3148 M-:3145
	{
		g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2vcc_error = 1;
	}
	else if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]<650 && g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]>500\
			&& g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]>200 && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]<300)//M+:576 M-:250
	{
		g_unMotorDriverOfflineDiagErrorCode.bits.motoropenload_error = 1;
	}
	else if(g_aui32Adc0VoltBuf[Adc0Channel_23_MOTOR_POSITIVE]<50 && g_aui32Adc1VoltBuf[Adc1Channel_24_MOTOR_NEGATIVE]<50)//M+:0 M-:0
	{
		g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2gnd_error = 1;
	}
}


Std_ReturnType MotorDriver_Offline_diag(void){
    static uint8_t MotorDiagCnt = 0u;
    Std_ReturnType Status = (Std_ReturnType)E_OK;

    if(g_eMotorState == MOTOR_STOP)       //if MOTOR is stop now , close gate driver before open off_line diag
    {
    	if(!Offline_diag_started)
    	{
    		if(Offline_diag_count<100)
    		{
    			Offline_diag_count++;
    			return E_OK;
    		}
    		else{
    			Offline_diag_count = 0;
    			Offline_diag_started = 1;
    		}
    	}
        MotorDiagCnt++;
        /* when Motor_Start function not be called , keep the gate driver close */
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].data = 0x00;
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].OP = OP_Read_And_WriteOrClear_Bit;

        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_VDS1_INDEX].data = 0x0FFF;
    }
    else if(g_eMotorState == MOTOR_PRESTART)       //Before exit Offline_Diag, RESET OFFLINE DIAG REGISTER and Clear fault register
    {
        MotorDiagCnt = 0u;

        if(g_si16MotorDuty>0)
        {
            TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].data = 0x06;
        }
        else{
            /* when Duty==0 , should set LSx and HSy on to enter the started state*/
            TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBMODE_INDEX].data = 0x09;
        }

        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_GENSTAT_INDEX].OP = OP_Read_And_WriteOrClear_Bit;
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_DSOV_INDEX].OP = OP_Read_And_WriteOrClear_Bit;
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBIDIAG_INDEX].data = 0xd400;

        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_VDS1_INDEX].data = 0x0b6d;

        motor_Running_state = MOTOR_RUNNING;

        MotorDriver_Offline_diag_exit_flag = 1;
        Offline_diag_started = 0;
        return Status;
    }
    else// if(g_eMotorState == MOTOR_STARTED)
    {
    	return Status;
    }

    if(get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 0) != 0 || get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 1) != 0 ||\
    get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 2) != 0 ||get_bit_from_rx_data(Usual_Use_CTRL_HBMODE_INDEX, 3) != 0 )
    {
    	return Status;
    }

    if(g_ui8HallInterruptOpened)
    {
    	g_unMotorDriverOfflineDiagErrorCode.errors = 0;
    	return Status;
    }

    if(NM_PREPARE_SLEEP_STATE == asrNmRte.state[0] || NM_BUS_SLEEP_STATE == asrNmRte.state[0])
    {
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBIDIAG_INDEX].data = 0xc000;
        return Status;
    }


    MotorDiagCnt%=12;

    if(1u == MotorDiagCnt)
	{
		/*Set preconditions:
		 *The bridge driver is in active mode: EN = High and BD_PASS = 0
		  The corresponding MOSFETs are off: HBxMODE[1:0] =00B
		  The device is operating operates in normal mode:
          VS and VDD are in the normal operating range
		  No watch dog failure*/

    /*Pull down all the SHx by activating the Ipddiag*/
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBIDIAG_INDEX].data = 0xc0ff;
	}

    if(3u == MotorDiagCnt)
    {
        /*Pull up all the SHx by deactivating the Ipddiag and activating Ipudiag*/
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBIDIAG_INDEX].data = 0xc000;
    }

    if(5u == MotorDiagCnt)
    {
        /*Pull Down SH1, Pull Up SH2*/
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBIDIAG_INDEX].data = 0xc001;
    }

    if(7u == MotorDiagCnt)
    {
        SH1PullDownSH2PullUpDiag();
    }

    if(9u == MotorDiagCnt)
    {
        /*Pull Up SH1, Pull Down SH2*/
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_CTRL_HBIDIAG_INDEX].data = 0xc002;
    }

    if(11u == MotorDiagCnt)
    {
        SH1PullUpSH2PullDownDiag();
    }


}

void TLE92104_check_GENSTAT_error(void)
{
    if(get_bit_from_rx_data(Usual_Use_STAT_GENSTAT_INDEX, 0))
    {
        g_unFaultIndicator.bits.Charge_Pump_Undervoltage = 1;
    }
    else
    {
        g_unFaultIndicator.bits.Charge_Pump_Undervoltage = 0;
    }

    if(get_bit_from_rx_data(Usual_Use_STAT_GENSTAT_INDEX, 1))
    {
        g_unFaultIndicator.bits.VS_Undervoltage = 1;
    }
    else
    {
        g_unFaultIndicator.bits.VS_Undervoltage = 0;
    }

    if(get_bit_from_rx_data(Usual_Use_STAT_GENSTAT_INDEX, 2))
    {
        g_unFaultIndicator.bits.VS_Overvoltage = 1;
    }
    else
    {
        g_unFaultIndicator.bits.VS_Overvoltage = 0;
    }

    if(get_bit_from_rx_data(Usual_Use_STAT_GENSTAT_INDEX, 3))
    {
        g_unFaultIndicator.bits.CSO1_Overcurrent = 1;
    }
    else
    {
        g_unFaultIndicator.bits.CSO1_Overcurrent = 0;
    }

    if(get_bit_from_rx_data(Usual_Use_STAT_GENSTAT_INDEX, 5))
    {
        g_unFaultIndicator.bits.Thermal_Warning = 1;
    }
    else
    {
        g_unFaultIndicator.bits.Thermal_Warning = 0;
    }

    if(get_bit_from_rx_data(Usual_Use_STAT_GENSTAT_INDEX, 6))
    {
        g_unFaultIndicator.bits.Thermal_Shutdown = 1;
    }
    else
    {
        g_unFaultIndicator.bits.Thermal_Shutdown = 0;
    }
}
void TLE92104_check_DSOV_error(void)
{
    if((get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 0))||(get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 1))||\
    		(get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 2))||(get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 3)))
    {
    	g_unFaultIndicator.bits.DrainSource_Overvoltage = 1;
    }
    else
    {
    	g_unFaultIndicator.bits.DrainSource_Overvoltage = 0;
    }

}
//void TLE92104_check_DSOV_error(void)
//{
//    if(get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 0))
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 1;
//    }
//    else
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 0;
//    }
//
//    if(get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 1))
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 1;
//    }
//    else
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 0;
//    }
//
//    if(get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 2))
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 1;
//    }
//    else
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 0;
//    }
//
//    if(get_bit_from_rx_data(Usual_Use_STAT_DSOV_INDEX, 3))
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 1;
//    }
//    else
//    {
//        g_unFaultIndicator.bits.DrainSource_Overvoltage = 0;
//    }
//
//}

Std_ReturnType MotorDriver_Online_diag(void)
{
    Std_ReturnType Status = (Std_ReturnType)E_OK;
    if(g_eMotorState != MOTOR_STARTED)
    {
        Status = E_NOK;
        return Status;
    }

	TLE92104_check_GENSTAT_error();
	TLE92104_check_DSOV_error();
	if(g_unFaultIndicator.all_flags != 0)
    {
		g_unMotorErrorStatus.bits.MotorDriverChipFailure = 1;
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_GENSTAT_INDEX].OP = OP_Read_And_WriteOrClear_Bit;
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_DSOV_INDEX].OP = OP_Read_And_WriteOrClear_Bit;
        Motor_Stop();
	}
	else
	{
        g_unMotorErrorStatus.bits.MotorDriverChipFailure = 0;
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_GENSTAT_INDEX].OP = OP_Read_Only_Bit;
        TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table[Usual_Use_STAT_DSOV_INDEX].OP = OP_Read_Only_Bit;
	}

    return Status;
}


Std_ReturnType MotorDriver_MotorErrorSet(void)
{
    /* for offline diag */
	g_unMotorErrorStatus.bits.MotorOpenCircuitFailure = g_unMotorDriverOfflineDiagErrorCode.bits.motoropenload_error;
	g_unMotorErrorStatus.bits.MotorShortCircuitFailure = g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2gnd_error\
													|| g_unMotorDriverOfflineDiagErrorCode.bits.motorshort2vcc_error;

	return E_OK;
}

