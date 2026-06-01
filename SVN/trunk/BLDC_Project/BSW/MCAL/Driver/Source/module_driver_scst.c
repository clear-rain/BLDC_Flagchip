/**
 * @file module_driver_scst.c
 * @author Flagchip074
 * @brief scst driver source code
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

#include "module_driver_smisc.h"
#include "module_driver_scst.h"

#ifndef SCST_DEV_ERROR_REPORT
#define SCST_DEV_ERROR_REPORT    STD_OFF
#endif

#if SCST_DEV_ERROR_REPORT == STD_ON
#define SCST_ReportDevError(func, error) ReportDevError(SCST_MODULE_ID, func, error)
#endif

/**
 * @brief The SCST Atomic Test function prototype
 *
 */
typedef Type_M4ST_AtomicStatus (*Type_M4ST_RegressionTest) (uint32_t TestStart, uint32_t TestEnd, uint32_t InjectEnable, uint32_t RamBase);

/**
 * @brief The SCST Run selected tests function prototype
 *
 */
typedef Type_M4ST_AtomicStatus (*Type_M4ST_AtomicTest) (uint32_t TestID, uint32_t InjectEnable, uint32_t RamBase);

/**
 * @brief M4ST API structure
 *
 */
typedef struct Struct_M4ST_RomTable
{
    Type_M4ST_RegressionTest  RegressionTest;       /**< Regression Test */
    Type_M4ST_AtomicTest    AluTest;                /**< Arithmetic Logic Unit Test */
    Type_M4ST_AtomicTest    AluMLATest;             /**< Arithmetic Logic Unit MLA Test */
    Type_M4ST_AtomicTest    AluSHIFTTest;           /**< Arithmetic Logic Unit Shift Test */
    Type_M4ST_AtomicTest    AluTest1;               /**< Arithmetic Logic Unit Test 1 */
    Type_M4ST_AtomicTest    AluTest2;               /**< Arithmetic Logic Unit Test 2 */
    Type_M4ST_AtomicTest    AluTest3;               /**< Arithmetic Logic Unit Test 3 */
    Type_M4ST_AtomicTest    AluTest4;               /**< Arithmetic Logic Unit Test 4 */
    Type_M4ST_AtomicTest    AluTest5;               /**< Arithmetic Logic Unit Test 5 */
    Type_M4ST_AtomicTest    AluTest6;               /**< Arithmetic Logic Unit Test 6 */
    Type_M4ST_AtomicTest    RegbankTest1;           /**< Register bank Test 1 */
    Type_M4ST_AtomicTest    RegbankTest2;           /**< Register bank Test 2 */
    Type_M4ST_AtomicTest    RegbankTest3;           /**< Register bank Test 3 */
    Type_M4ST_AtomicTest    RegbankTest4;           /**< Register bank Test 4 */
    Type_M4ST_AtomicTest    RegbankTest5;           /**< Register bank Test 5 */
    Type_M4ST_AtomicTest    RegbankTest6;           /**< Register bank Test 6 */
    Type_M4ST_AtomicTest    LoadStoreTest1;         /**< Load Store Test 1 */
    Type_M4ST_AtomicTest    LoadStoreTest2;         /**< Load Store Test 2 */
    Type_M4ST_AtomicTest    LoadStoreTest3;         /**< Load Store Test 3 */
    Type_M4ST_AtomicTest    LoadStoreTest4;         /**< Load Store Test 4 */
    Type_M4ST_AtomicTest    LoadStoreTest5;         /**< Load Store Test 5 */
    Type_M4ST_AtomicTest    LoadStoreTest6;         /**< Load Store Test 6 */
    Type_M4ST_AtomicTest    SimdSatTest1;           /**< SimdSat Test 1 */
    Type_M4ST_AtomicTest    SimdSatTest2;           /**< SimdSat Test 2 */
    Type_M4ST_AtomicTest    SimdSatTest3;           /**< SimdSat Test 3 */
    Type_M4ST_AtomicTest    SimdSatTest4;           /**< SimdSat Test 4 */
    Type_M4ST_AtomicTest    MacTest1;               /**< Mac Test 1 */
    Type_M4ST_AtomicTest    MacTest2;               /**< Mac Test 2 */
    Type_M4ST_AtomicTest    FetchTest;              /**< Fetch Test */
    Type_M4ST_AtomicTest    StatusTest1;            /**< Status Test 1 */
    Type_M4ST_AtomicTest    StatusTest2;            /**< Status Test 2 */
    Type_M4ST_AtomicTest    BranchTest1;            /**< Branch Test 1 */
    Type_M4ST_AtomicTest    BranchTest2;            /**< Branch Test 2 */
    Type_M4ST_AtomicTest    IntSvcTest;             /**< Interrupt Svc Test */
    Type_M4ST_AtomicTest    IntBusFaultTest;        /**< Interrupt Bus Fault Test */
    Type_M4ST_AtomicTest    IntHardFaultTest1;      /**< Interrupt HardFault Test 1 */
    Type_M4ST_AtomicTest    IntHardFaultTest2;      /**< Interrupt HardFault Test 2 */
    Type_M4ST_AtomicTest    IntUsageFaultTest;      /**< Interrupt UsageFault Test */
    Type_M4ST_AtomicTest    IntSystickTest;         /**< Interrupt Systick Test */
    Type_M4ST_AtomicTest    IntPendSvTest;          /**< Interrupt PendSv Test */
    Type_M4ST_AtomicTest    IntMemFaultTest;        /**< Interrupt MemManageFault Test */
    Type_M4ST_AtomicTest    IntMaskingTest;         /**< Interrupt Masking Test */
    Type_M4ST_AtomicTest    IntHandlerThreadsTest;  /**< Interrupt Handler Threads Test */
    Type_M4ST_AtomicTest    IntNMIHfTest;           /**< Interrupt NMIHf Test */
    Type_M4ST_AtomicTest    IntTailChainTest;       /**< Interrupt Tail Chain Test */
    Type_M4ST_AtomicTest    IntAluTest;             /**< Interrupt Arithmetic Logic Unit Test */
    Type_M4ST_AtomicTest    IntBranchTest;          /**< Interrupt Branch Test */
    Type_M4ST_AtomicTest    IntStatusTest;          /**< Interrupt Status Test */
} Type_M4ST_RomTable;

/**
 * @brief This function is used to get the result of the executed test
 *
 * @param test_index is test number,0U..47U
 * @param s_u32RamBase The first address of the 1k memory that the program needs to run
 * @return M4ST_ErrorM4ST_TestPass is ok, others are not ok
 */
Type_M4ST_AtomicStatus SCST_ExecuteTest(SCST_TestIndexType test_index,uint32_t *s_u32RamBase)
{
    Type_M4ST_AtomicStatus Status = M4ST_FaultInjectError;
    Type_M4ST_RomTable *M4ST_RomEntry = (Type_M4ST_RomTable *)M4ST_ROM_BASE;
#if SCST_DEV_ERROR_REPORT == STD_ON
    if(test_index > M4ST_RegressionTest)
    {
        SCST_ReportDevError(SCST_EXECUTETEST_ID, SCST_E_PARAM_INVALID);
    }
    else
    {
#endif
        switch(test_index)
        {
            case M4ST_AluTest:
                Status = M4ST_RomEntry->AluTest(0,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluMLATest:
                Status = M4ST_RomEntry->AluMLATest(1,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluSHIFTTest:
                Status = M4ST_RomEntry->AluSHIFTTest(2,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluTes1t:
                Status = M4ST_RomEntry->AluTest1(3,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluTest2:
                Status = M4ST_RomEntry->AluTest2(4,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluTest3:
                Status = M4ST_RomEntry->AluTest3(5,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluTest4:
                Status = M4ST_RomEntry->AluTest4(6,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluTest5:
                Status = M4ST_RomEntry->AluTest5(7,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_AluTest6:
                Status = M4ST_RomEntry->AluTest6(8,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_RegbankTest1:
                Status = M4ST_RomEntry->RegbankTest1(9,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_RegbankTest2:
                Status = M4ST_RomEntry->RegbankTest2(10,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_RegbankTest3:
                Status = M4ST_RomEntry->RegbankTest3(11,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_RegbankTest4:
                Status = M4ST_RomEntry->RegbankTest4(12,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_RegbankTest5:
                Status = M4ST_RomEntry->RegbankTest5(13,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_RegbankTest6:
                Status = M4ST_RomEntry->RegbankTest6(14,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_LoadStoreTest1:
                Status = M4ST_RomEntry->LoadStoreTest1(15,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_LoadStoreTest2:
                Status = M4ST_RomEntry->LoadStoreTest2(16,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_LoadStoreTest3:
                Status = M4ST_RomEntry->LoadStoreTest3(17,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_LoadStoreTest4:
                Status = M4ST_RomEntry->LoadStoreTest4(18,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_LoadStoreTest5:
                Status = M4ST_RomEntry->LoadStoreTest5(19,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_LoadStoreTest6:
                Status = M4ST_RomEntry->LoadStoreTest6(20,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_SimdSatTest1:
                Status = M4ST_RomEntry->SimdSatTest1(21,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_SimdSatTest2:
                Status = M4ST_RomEntry->SimdSatTest2(22,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_SimdSatTest3:
                Status = M4ST_RomEntry->SimdSatTest3(23,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_SimdSatTest4:
                Status = M4ST_RomEntry->SimdSatTest4(24,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_MacTest1:
                Status = M4ST_RomEntry->MacTest1(25,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_MacTest2:
                Status = M4ST_RomEntry->MacTest2(26,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_FetchTest:
                Status = M4ST_RomEntry->FetchTest(27,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_StatusTest1:
                Status = M4ST_RomEntry->StatusTest1(28,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_StatusTest2:
                Status = M4ST_RomEntry->StatusTest2(29,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_BranchTest1:
                Status = M4ST_RomEntry->BranchTest1(30,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_BranchTest2:
                Status = M4ST_RomEntry->BranchTest2(31,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntSvcTest:
                Status = M4ST_RomEntry->IntSvcTest(32,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntBusFaultTest:
                Status = M4ST_RomEntry->IntBusFaultTest(33,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntHardFaultTest1:
                Status = M4ST_RomEntry->IntHardFaultTest1(34,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntHardFaultTest2:
                Status = M4ST_RomEntry->IntHardFaultTest2(35,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntUsageFaultTest:
                Status = M4ST_RomEntry->IntUsageFaultTest(36,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntSystickTest:
                Status = M4ST_RomEntry->IntSystickTest(37,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntPendSvTest:
                Status = M4ST_RomEntry->IntPendSvTest(38,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntMemFaultTest:
                Status = M4ST_RomEntry->IntMemFaultTest(39,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntMaskingTest:
                Status = M4ST_RomEntry->IntMaskingTest(40,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntHandlerThreadsTest:
                Status = M4ST_RomEntry->IntHandlerThreadsTest(41,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntNMIHfTest:
                Status = M4ST_RomEntry->IntNMIHfTest(42,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntTailChainTest:
                Status = M4ST_RomEntry->IntTailChainTest(43,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntAluTest:
                Status = M4ST_RomEntry->IntAluTest(44,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntBranchTest:
                Status = M4ST_RomEntry->IntBranchTest(45,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_IntStatusTest:
                Status = M4ST_RomEntry->IntStatusTest(46,0,(uint32_t)&s_u32RamBase[0]);
            break;

            case M4ST_RegressionTest:
                Status = M4ST_RomEntry->RegressionTest(0,46,0,(uint32_t)&s_u32RamBase[0]);
            break;

            default:
                break;
        }
#if SCST_DEV_ERROR_REPORT == STD_ON
    }
#endif
    return Status;
}

#if SMISC_ROM_CLOCK_GATING_SUPPORT
/**
 * @brief This function is used to enable the ROM clock
 *
 */
void SCST_Init(void)
{
    SMISC_HWA_SetSysClock((uint32_t)SMISC_SYSCGC_CGCROM_MASK);
}
#endif

