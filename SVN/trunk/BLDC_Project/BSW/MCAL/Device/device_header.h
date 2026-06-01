/**
 * @file device_header.h
 * @author Flagchip
 * @brief include all peripheral register files
 * @version 2.0.0
 * @date 2023-09-20
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
#ifndef DEVICE_HEADER_H
#define DEVICE_HEADER_H

#define FC4150_DEVICE_START     0U
#define FC4150F1MBS1P100T1B     0U
#define FC4150F1MBS1P144T1B     1U
#define FC4150F1MBS1P64T1B      2U
#define FC4150F1MBS2P100T1B     3U
#define FC4150F1MBS2P144T1B     4U
#define FC4150F1MBS2P64T1B      5U
#define FC4150F1MS1P100T2B      6U
#define FC4150F1MS1P144T2B      7U
#define FC4150F1MS1P64T2B       8U
#define FC4150F1MBS1P100T1A     9U
#define FC4150F1MBS1P144T1A     10U
#define FC4150F1MBS2P100T1A     11U
#define FC4150F1MBS2P144T1A     12U
#define FC4150F2MBS1P100T1A     13U
#define FC4150F2MBS1P144T1A     14U
#define FC4150F2MBS1P176T1A     15U
#define FC4150F2MBS2P100T1A     16U
#define FC4150F2MBS2P144T1A     17U
#define FC4150F2MBS2P176T1A     18U
#define FC4150F2MBS3P100T1A     19U
#define FC4150F2MBS3P144T1A     20U
#define FC4150F2MBS3P176T1A     21U
#define FC4150F2MBS4P100T1A     22U
#define FC4150F2MBS4P144T1A     23U
#define FC4150F2MBS4P176T1A     24U
#define FC4150F512BS1P100T1A    25U
#define FC4150F512BS1P144T1A    26U
#define FC4150F512BS1P64T1A     27U
#define FC4150F512BS2P100T1A    28U
#define FC4150F512BS2P144T1A    29U
#define FC4150F512BS2P64T1A     30U
#define FC4150_DEVICE_END       99U



#define ADC_MODULE_ID          1
#define AFCB_MODULE_ID         2
#define AONTIMER_MODULE_ID     3
#define CACHE_MODULE_ID        4
#define CMP_MODULE_ID          5
#define CMU_MODULE_ID          6
#define CORDIC_MODULE_ID       7
#define CRC_MODULE_ID          8
#define DMA_MODULE_ID          9
#define EIM_MODULE_ID          10
#define ENET_MODULE_ID         11
#define ERM_MODULE_ID          12
#define FCIIC_MODULE_ID        13
#define FCPIT_MODULE_ID        14
#define FCSPI_MODULE_ID        15
#define FCUART_MODULE_ID       16
#define FLASH_MODULE_ID        17
#define FLEXCAN_MODULE_ID      18
#define FTU_MODULE_ID          19
#define FWM_MODULE_ID          20
#define GPIO_MODULE_ID         21
#define HSM_MODULE_ID          22
#define I2S_MODULE_ID          23
#define INTM_MODULE_ID         24
#define ISM_MODULE_ID          25
#define LIN_MODULE_ID          26
#define LU_MODULE_ID           27
#define MAP_MODULE_ID          28
#define MCM_MODULE_ID          29
#define MPU_MODULE_ID          30
#define OSPI_MODULE_ID         31
#define PCC_MODULE_ID          32
#define PMC_MODULE_ID          33
#define PORT_MODULE_ID         34
#define PTIMER_MODULE_ID       35
#define RCM_MODULE_ID          36
#define RTC_MODULE_ID          37
#define SCG_MODULE_ID          38
#define SCST_MODULE_ID         39
#define SEC_MODULE_ID          40
#define SMC_MODULE_ID          41
#define SMISC_MODULE_ID        42
#define SYSTICK_MODULE_ID      43
#define TRGSEL_MODULE_ID       44
#define TSTMP_MODULE_ID        45
#define WDOG_MODULE_ID         46
#define WKU_MODULE_ID          47
#define FREQM_MODULE_ID        48

#include "typedef.h"

#include "_device.h"

#if DEVICE_NAME == FC4150F1MBS1P100T1B
    #include "FC\Features\FC4150\FC4150F1M_B\FC4150F1MBS1P100T1B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS1P144T1B
    #include "FC\Features\FC4150\FC4150F1M_B\FC4150F1MBS1P144T1B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS1P64T1B
    #include "FC\Features\FC4150\FC4150F1M_B\FC4150F1MBS1P64T1B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS2P100T1B
    #include "FC\Features\FC4150\FC4150F1M_B\FC4150F1MBS2P100T1B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS2P144T1B
    #include "FC\Features\FC4150\FC4150F1M_B\FC4150F1MBS2P144T1B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS2P64T1B
    #include "FC\Features\FC4150\FC4150F1M_B\FC4150F1MBS2P64T1B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MS1P100T2B
    #include "FC\Features\FC4150\FC4150F1M_S\FC4150F1MS1P100T2B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MS1P144T2B
    #include "FC\Features\FC4150\FC4150F1M_S\FC4150F1MS1P144T2B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MS1P64T2B
    #include "FC\Features\FC4150\FC4150F1M_S\FC4150F1MS1P64T2B_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS1P100T1A
    #include "FC\Features\FC4150\FC4150F1M_A\FC4150F1MBS1P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS1P144T1A
    #include "FC\Features\FC4150\FC4150F1M_A\FC4150F1MBS1P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS2P100T1A
    #include "FC\Features\FC4150\FC4150F1M_A\FC4150F1MBS2P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F1MBS2P144T1A
    #include "FC\Features\FC4150\FC4150F1M_A\FC4150F1MBS2P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS1P100T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS1P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS1P144T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS1P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS1P176T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS1P176T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS2P100T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS2P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS2P144T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS2P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS2P176T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS2P176T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS3P100T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS3P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS3P144T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS3P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS3P176T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS3P176T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS4P100T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS4P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS4P144T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS4P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F2MBS4P176T1A
    #include "FC\Features\FC4150\FC4150F2M\FC4150F2MBS4P176T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F512BS1P100T1A
    #include "FC\Features\FC4150\FC4150F512\FC4150F512BS1P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F512BS1P144T1A
    #include "FC\Features\FC4150\FC4150F512\FC4150F512BS1P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F512BS1P64T1A
    #include "FC\Features\FC4150\FC4150F512\FC4150F512BS1P64T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F512BS2P100T1A
    #include "FC\Features\FC4150\FC4150F512\FC4150F512BS2P100T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F512BS2P144T1A
    #include "FC\Features\FC4150\FC4150F512\FC4150F512BS2P144T1A_feature.h"
#endif
#if DEVICE_NAME == FC4150F512BS2P64T1A
    #include "FC\Features\FC4150\FC4150F512\FC4150F512BS2P64T1A_feature.h"
#endif


#if  DEVICE_NAME >= FC4150_DEVICE_START && DEVICE_NAME < FC4150_DEVICE_END
    #include "Arm/CMSIS5_590/Core/Include/core_cm4.h"
    #include "Arm/cm4/arm_cortex_asm.h"

    #if ADC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_adc_regs.h"
    #endif
    #if AFCB_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_afcb_regs.h"
    #endif
    #if AONTIMER_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_aontimer_regs.h"
    #endif
    #if CCU_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_ccu_regs.h"
    #endif
    #if CMP_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_cmp_regs.h"
    #endif
    #if CMU_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_cmu_regs.h"
    #endif

    #if CORDIC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_cordic_regs.h"
    #endif

    #if CRC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_crc_regs.h"
    #endif
    #if DMAMUX_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_dmamux_regs.h"
    #endif
    #if DMA_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_dma_regs.h"
    #endif
    #if EIM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_eim_regs.h"
    #endif

    #if ENET_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_enet_regs.h"
    #endif
    #if ERM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_erm_regs.h"
    #endif
    #if FARC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_farc_regs.h"
    #endif
    #if FCIIC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_fciic_regs.h"
    #endif
    #if FCPIT_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_fcpit_regs.h"
    #endif
    #if FCSPI_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_fcspi_regs.h"
    #endif
    #if FCUART_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_fcuart_regs.h"
    #endif
    #if FLEXCAN_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_flexcan_regs.h"
    #endif
    #if FMC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_fmc_regs.h"
    #endif
    #if FREQM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_freqm_regs.h"
    #endif
    #if FTU_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_ftu_regs.h"
    #endif
    #if FWM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_fwm_regs.h"
    #endif
    #if GPIO_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_gpio_regs.h"
    #endif
    #if I2S_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_i2s_regs.h"
    #endif
    #if INTM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_intm_regs.h"
    #endif
    #if ISM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_ism_regs.h"
    #endif
    #if LU_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_lu_regs.h"
    #endif
    #if MAP_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_map_regs.h"
    #endif
    #if MCM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_mcm_regs.h"
    #endif
    #if OSPI_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_ospi_regs.h"
    #endif
    #if PCC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_pcc_regs.h"
    #endif
    #if PMC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_pmc_regs.h"
    #endif
    #if PORT_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_port_regs.h"
    #endif
    #if PTIMER_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_ptimer_regs.h"
    #endif
    #if RCM_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_rcm_regs.h"
    #endif
    #if RTC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_rtc_regs.h"
    #endif
    #if SCG_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_scg_regs.h"
    #endif
    #if SEC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_sec_regs.h"
    #endif
    #if SMC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_smc_regs.h"
    #endif
    #if SMISC_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_smisc_regs.h"
    #endif
    #if TRGSEL_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_trgsel_regs.h"
    #endif
    #if TSTMP_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_tstmp_regs.h"
    #endif
    #if WDOG_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_wdog_regs.h"
    #endif
    #if WKU_INSTANCE_COUNT > 0U
        #include "FC/Modules/FC4150/module_wku_regs.h"
    #endif


#else
    #error "Unavailable Device Type!!!"
#endif

#include "FC/fclib/fcmath.h"
#include "FC/fclib/fcfunc.h"


#define ReportDevError(module, func, error) { while(true){(void)module;(void)func;(void)error;} }

#endif /* DEVICE_HEADER_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
