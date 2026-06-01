/**
 * @file module_driver_scst.h
 * @author Flagchip074
 * @brief SCST driver type definition and API
 * @version 2.0.0
 * @date 2024-11-08
 *
 * @copyright Copyright (c) 2020-2024 Flagchip Semiconductors Co., Ltd.
 *
 */
/*********************************************************************************
*  Revision History:

*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   2.0.0       2024-04-20    Flagchip074   N/A          First version
*********************************************************************************/

#ifndef _DRIVER_MODULE_DRIVER_SCST_H_
#define _DRIVER_MODULE_DRIVER_SCST_H_

#include "device_header.h"

/**
 * @addtogroup module_driver_scst
 * @{
 */

/**
 * @name  SCST API Service IDs
 *
 * @{
 */
#define SCST_EXECUTETEST_ID 0U
/** @}*/

/**
 * @name  SCST Dev Error Code
 * @brief Error Code of calling SCST apis
 *
 * @{
 */
#define SCST_E_PARAM_INVALID           0x01U
/** @}*/

/**
 * @brief typed of test result returned
 *
 */
typedef enum
{
    M4ST_FaultInjectError,              /**< Fault Inject Error */
    M4ST_ErrorAluTest,                  /**< Arithmetic Logic Unit Test Error */
    M4ST_ErrorAluMLATest,               /**< Arithmetic Logic Unit MLA Test Error */
    M4ST_ErrorAluSHIFTTest,             /**< Arithmetic Logic Unit Shift Test Error */
    M4ST_ErrorAluTest1,                  /**< Arithmetic Logic Unit Test 1 Error */
    M4ST_ErrorAluTest2,                  /**< Arithmetic Logic Unit Test 2 Error */
    M4ST_ErrorAluTest3,                  /**< Arithmetic Logic Unit Test 3 Error */
    M4ST_ErrorAluTest4,                  /**< Arithmetic Logic Unit Test 4 Error */
    M4ST_ErrorAluTest5,                  /**< Arithmetic Logic Unit Test 5 Error */
    M4ST_ErrorAluTest6,                  /**< Arithmetic Logic Unit Test 6 Error */
    M4ST_ErrorRegbankTest1,              /**< Register bank Test 1 Error */
    M4ST_ErrorRegbankTest2,              /**< Register bank Test 2 Error */
    M4ST_ErrorRegbankTest3,              /**< Register bank Test 3 Error */
    M4ST_ErrorRegbankTest4,              /**< Register bank Test 4 Error */
    M4ST_ErrorRegbankTest5,              /**< Register bank Test 5 Error */
    M4ST_ErrorRegbankTest6,              /**< Register bank Test 6 Error */
    M4ST_ErrorLoadStoreTest1,            /**< Load Store Test 1 Error */
    M4ST_ErrorLoadStoreTest2,            /**< Load Store Test 2 Error */
    M4ST_ErrorLoadStoreTest3,            /**< Load Store Test 3 Error */
    M4ST_ErrorLoadStoreTest4,            /**< Load Store Test 4 Error */
    M4ST_ErrorLoadStoreTest5,            /**< Load Store Test 5 Error */
    M4ST_ErrorLoadStoreTest6,            /**< Load Store Test 6 Error */
    M4ST_ErrorSimdSatTest1,              /**< SimdSat Test 1 Error */
    M4ST_ErrorSimdSatTest2,              /**< SimdSat Test 2 Error */
    M4ST_ErrorSimdSatTest3,              /**< SimdSat Test 3 Error */
    M4ST_ErrorSimdSatTest4,              /**< SimdSat Test 4 Error */
    M4ST_ErrorMacTest1,                  /**< Mac Test 1 Error */
    M4ST_ErrorMacTest2,                  /**< Mac Test 2 Error */
    M4ST_ErrorFetchTest,                 /**< Fetch Test Error */
    M4ST_ErrorStatusTest1,               /**< Status Test 1 Error */
    M4ST_ErrorStatusTest2,               /**< Status Test 2 Error */
    M4ST_ErrorBranchTest1,               /**< Branch Test 1 Error */
    M4ST_ErrorBranchTest2,               /**< Branch Test 2 Error */
    M4ST_ErrorIntSvcTest,                /**< Interrupt Svc Test Error */
    M4ST_ErrorIntBusFaultTest,           /**< Interrupt Bus Fault Test Error */
    M4ST_ErrorIntHardFaultTest1,         /**< Interrupt HardFault Test 1 Error */
    M4ST_ErrorIntHardFaultTest2,         /**< Interrupt HardFault Test 2 Error */
    M4ST_ErrorIntUsageFaultTest,         /**< Interrupt UsageFault Test Error */
    M4ST_ErrorIntSystickTest,            /**< Interrupt Systick Test Error */
    M4ST_ErrorIntPendSvTest,             /**< Interrupt PendSv Test Error */
    M4ST_ErrorIntMemFaultTest,           /**< Interrupt MemManageFault Test Error */
    M4ST_ErrorIntMaskingTest,            /**< Interrupt Masking Test Error */
    M4ST_ErrorIntHandlerThreadsTest,     /**< Interrupt Handler Threads Test Error */
    M4ST_ErrorIntNMIHfTest,              /**< Interrupt NMIHf Test Error */
    M4ST_ErrorIntTailChainTest,          /**< Interrupt Tail Chain Test Error */
    M4ST_ErrorIntAluTest,                /**< Interrupt Arithmetic Logic Unit Test Error */
    M4ST_ErrorIntBranchTest,             /**< Interrupt Branch Test Error */
    M4ST_ErrorIntStatusTest,             /**< Interrupt Status Test Error */
    M4ST_ErrorM4ST_TestPass              /**< M4 Self Test Pass*/
} Type_M4ST_AtomicStatus;

/**
 * @brief typed of test index
 *
 */
typedef enum
{
    M4ST_AluTest,               /**< Arithmetic Logic Unit Test */
    M4ST_AluMLATest,            /**< Arithmetic Logic Unit MLA Test */
    M4ST_AluSHIFTTest,          /**< Arithmetic Logic Unit Shift Test */
    M4ST_AluTes1t,              /**< Arithmetic Logic Unit Test 1 */
    M4ST_AluTest2,              /**< Arithmetic Logic Unit Test 2 */
    M4ST_AluTest3,              /**< Arithmetic Logic Unit Test 3 */
    M4ST_AluTest4,              /**< Arithmetic Logic Unit Test 4 */
    M4ST_AluTest5,              /**< Arithmetic Logic Unit Test 5 */
    M4ST_AluTest6,              /**< Arithmetic Logic Unit Test 6 */
    M4ST_RegbankTest1,          /**< Register bank Test 1 */
    M4ST_RegbankTest2,          /**< Register bank Test 2 */
    M4ST_RegbankTest3,          /**< Register bank Test 3 */
    M4ST_RegbankTest4,          /**< Register bank Test 4 */
    M4ST_RegbankTest5,          /**< Register bank Test 5 */
    M4ST_RegbankTest6,          /**< Register bank Test 6 */
    M4ST_LoadStoreTest1,        /**< Load Store Test 1 */
    M4ST_LoadStoreTest2,        /**< Load Store Test 2 */
    M4ST_LoadStoreTest3,        /**< Load Store Test 3 */
    M4ST_LoadStoreTest4,        /**< Load Store Test 4 */
    M4ST_LoadStoreTest5,        /**< Load Store Test 5 */
    M4ST_LoadStoreTest6,        /**< Load Store Test 6 */
    M4ST_SimdSatTest1,          /**< SimdSat Test 1 */
    M4ST_SimdSatTest2,          /**< SimdSat Test 2 */
    M4ST_SimdSatTest3,          /**< SimdSat Test 3 */
    M4ST_SimdSatTest4,          /**< SimdSat Test 4 */
    M4ST_MacTest1,              /**< Mac Test 1 */
    M4ST_MacTest2,              /**< Mac Test 2 */
    M4ST_FetchTest,             /**< Fetch Test */
    M4ST_StatusTest1,           /**< Status Test 1 */
    M4ST_StatusTest2,           /**< Status Test 2 */
    M4ST_BranchTest1,           /**< Branch Test 1 */
    M4ST_BranchTest2,           /**< Branch Test 2 */
    M4ST_IntSvcTest,            /**< Interrupt Svc Test */
    M4ST_IntBusFaultTest,       /**< Interrupt Bus Fault Test */
    M4ST_IntHardFaultTest1,     /**< Interrupt HardFault Test 1 */
    M4ST_IntHardFaultTest2,     /**< Interrupt HardFault Test 2 */
    M4ST_IntUsageFaultTest,     /**< Interrupt UsageFault Test */
    M4ST_IntSystickTest,        /**< Interrupt Systick Test */
    M4ST_IntPendSvTest,         /**< Interrupt PendSv Test */
    M4ST_IntMemFaultTest,       /**< Interrupt MemManageFault Test */
    M4ST_IntMaskingTest,        /**< Interrupt Masking Test */
    M4ST_IntHandlerThreadsTest, /**< Interrupt Handler Threads Test */
    M4ST_IntNMIHfTest,          /**< Interrupt NMIHf Test */
    M4ST_IntTailChainTest,      /**< Interrupt Tail Chain Test */
    M4ST_IntAluTest,            /**< Interrupt Arithmetic Logic Unit Test */
    M4ST_IntBranchTest,         /**< Interrupt Branch Test */
    M4ST_IntStatusTest,         /**< Interrupt Status Test */
    M4ST_RegressionTest         /**< Regression Test */
} SCST_TestIndexType;

/**
 * @brief This function is used to get the result of the executed test
 *
 * @param test_index is test number,0U..47U
 * @param s_u32RamBase The first address of the 1k memory that the program needs to run
 * @return M4ST_ErrorM4ST_TestPass is ok, others are not ok
 */
Type_M4ST_AtomicStatus SCST_ExecuteTest(SCST_TestIndexType test_index,uint32_t *s_u32RamBase);

#if SMISC_ROM_CLOCK_GATING_SUPPORT
/**
 * @brief This function is used to enable the ROM clock
 *
 */
void SCST_Init(void);
#endif

/** @}*/ /* module_driver_scst */
#endif
