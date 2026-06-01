/***************************************************************************
 * @file motor_voltage_injection_inductance.c
 * @brief 电压脉冲注入测量电感模块，参考 MD380 永磁同步机参数辨识思路移植。
 *
 * 本文件刻意保持独立，当前没有接入工程原有运行逻辑。只有在完成下方
 * USER_PORT 标记的硬件访问函数后，才建议把本文件加入构建并调用公开接口。
 *
 * 参考逻辑：
 *   MD380 MotorPmsmParEst.c:
 *     SynInitPosDetect()
 *     SynCalLabAndLbc()
 *     SynInitPosDetSetTs()
 *     SynInitPosDetSetPwm()
 *
 * MD380 算法概要：
 *   1. 关闭普通 PWM，强制 6 个桥臂状态：
 *        0: A+, B-   1: A-, B+
 *        2: B+, C-   3: B-, C+
 *        4: A-, C+   5: A+, C-
 *        6: 恢复普通 PWM，7: 全部强制关闭/初始化状态
 *   2. 逐步增大脉宽，直到电流响应达到限值。
 *   3. 对 6 个桥臂状态执行两轮注入，并保存电流增量。
 *   4. 计算线电感 LAB/LBC/LCA：
 *        L = (Udc - I * Rs) * pulse_time / I
 *
 * 针对当前 BLDC 工程的说明：
 *   - 原 MD380 代码直接写 TI ePWM 寄存器。本文件把这些硬件动作放在弱
 *     USER_PORT 钩子函数后面，因此不需要修改原工程代码。
 *   - 本文件中的电流、电压单位采用 SI 单位：A、V、s、H。
 *   - 默认钩子函数只是占位实现，在被替换前会让模块安全失败。
 ***************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#if defined(__GNUC__)
#define BLDC_VI_WEAK __attribute__((weak))
#else
#define BLDC_VI_WEAK
#endif

#ifndef BLDC_VI_SECTION_SAFE_OFF
#define BLDC_VI_SECTION_SAFE_OFF (7u)
#endif

#ifndef BLDC_VI_SECTION_RESTORE_PWM
#define BLDC_VI_SECTION_RESTORE_PWM (6u)
#endif

#ifndef BLDC_VI_SECTION_COUNT
#define BLDC_VI_SECTION_COUNT (6u)
#endif

#ifndef BLDC_VI_SAMPLE_COUNT
#define BLDC_VI_SAMPLE_COUNT (12u)
#endif

typedef enum
{
    BLDC_VI_STATUS_IDLE = 0,
    BLDC_VI_STATUS_BUSY,
    BLDC_VI_STATUS_DONE,
    BLDC_VI_STATUS_FAULT
} BLDC_VI_Status;

typedef enum
{
    BLDC_VI_FAULT_NONE = 0,
    BLDC_VI_FAULT_USER_PORT_NOT_READY,
    BLDC_VI_FAULT_NO_CURRENT_RESPONSE,
    BLDC_VI_FAULT_PULSE_WIDTH_LIMIT,
    BLDC_VI_FAULT_INVALID_CONFIG
} BLDC_VI_Fault;

typedef enum
{
    BLDC_VI_STATE_IDLE = 0,
    BLDC_VI_STATE_INIT,
    BLDC_VI_STATE_FIND_WIDTH,
    BLDC_VI_STATE_MEASURE,
    BLDC_VI_STATE_CALC,
    BLDC_VI_STATE_DONE,
    BLDC_VI_STATE_FAULT
} BLDC_VI_State;

typedef struct
{
    float initial_pulse_us;          /* 初始注入脉宽，MD380 默认约 50 us。 */
    float max_pulse_us;              /* 脉宽搜索的安全上限。 */
    float slow_step_us;              /* 电流接近限值时的脉宽递增步长。 */
    float fast_step_us;              /* 电流远低于限值时的脉宽递增步长。 */
    float current_limit_a;           /* 电流响应超过该值后停止脉宽搜索。 */
    float min_current_response_a;    /* 用于判断缺相/无输出的最小电流响应。 */
    float phase_resistance_ohm;      /* 定子相/线电阻，用于扣除 I*R 压降。 */
    float effective_pulse_factor;    /* 等效脉冲时间系数，MD380 约为 2 倍脉宽，需 USER_PORT 确认。 */
} BLDC_VI_Config;

typedef struct
{
    BLDC_VI_Status status;
    BLDC_VI_Fault fault;
    float pulse_width_us;
    float bus_voltage_v;
    float raw_delta_current_a[BLDC_VI_SAMPLE_COUNT];
    float line_inductance_h[3];      /* [0]=LAB，[1]=LBC，[2]=LCA */
    float line_inductance_mh[3];
    float average_line_inductance_h;
    float average_line_inductance_mh;
    float min_used_current_a[3];
} BLDC_VI_Result;

typedef struct
{
    BLDC_VI_Config cfg;
    BLDC_VI_Result result;
    BLDC_VI_State state;
    uint8_t period_cnt;
    uint8_t section;
    uint8_t pass;
    float base_current_a;
} BLDC_VI_Context;

static BLDC_VI_Context s_bldc_vi;

/***************************************************************************
 * USER_PORT 钩子函数
 *
 * 可以用工程相关的强定义替换这些弱定义，也可以直接只修改这个新增文件。
 * 原工程文件无需改动。
 ***************************************************************************/

/*
 * 检查所有工程相关硬件钩子是否已经准备好。
 * 默认实现返回 false，避免移植完成前误调用导致桥臂发脉冲。
 */
BLDC_VI_WEAK bool BLDC_VI_UserPortReady(void)
{
    /*
     * TODO(USER_PORT):
     * 当前工程中的建议实现：
     *   - 只有以下移植点全部完成后才返回 true：
     *       1. BLDC_VI_SetBridgeSection() 能准确强制 6 个桥臂状态。
     *       2. BLDC_VI_SetPulseWidthUs() 能产生一次性脉冲，或为注入步骤
     *          设置等效的短 PWM 周期。
     *       3. BLDC_VI_ReadPhaseCurrentA() 能在注入脉冲响应对应时刻采样电流。
     *       4. BLDC_VI_ReadBusVoltageV() 能返回脉冲期间桥臂实际使用的母线电压。
     *
     * 可选的就绪检查：
     *   - BSW/CDD/MotorDriver/Src/MotorControl.c 中的 g_ui8Motor_Inited != 0。
     *   - 注入前没有有效的 MotorDriver/Hall 故障。
     *   - FOC 或主轴普通 PWM 输出已经停止，例如进入本独立流程前调用
     *     MotorAPI_StatusSet(false)。
     *
     * 默认保持 false，让误调用安全失败。
     */
    return false;
}

/*
 * 使能注入脉冲流程使用的逆变器/门驱通路。
 * 该钩子应让桥臂具备被强制区段控制的条件，但不应启动普通 FOC 或主轴控制输出。
 */
BLDC_VI_WEAK void BLDC_VI_EnableDrive(void)
{
    /*
     * TODO(USER_PORT):
     * 当前工程中的建议实现：
     *   - 如果走 TLE92104/TLE92108 路径，复用 MotorDriver_Init()/Motor_Enable()
     *     使用的使能路径：
     *       IoHwAb_Dio_WriteChannel(DRV_EN_IDX, 1);
     *       Motor_Enable(TRUE);
     *   - 如果走 FOC 三相 PWM 路径，还要确认 Bsp_PWM_Init() 后 FTU 定时器
     *     已经运行。
     *
     * 需要人工确认：
     *   - 仅 DRV_EN_IDX 是否足以使能功率级，还是必须先写 HBMODE 后桥臂才导通。
     *   - 注入流程占用桥臂期间，是否需要暂停普通 Motor_Mainfunction()。
     */
}

/*
 * 注入结束或故障时关闭逆变器/门驱通路。
 * 实现时应先强制到不导通状态，再按需要把桥臂控制权交回普通电机控制代码。
 */
BLDC_VI_WEAK void BLDC_VI_DisableDrive(void)
{
    /*
     * TODO(USER_PORT):
     * 当前工程中的建议实现：
     *   - 先强制安全桥臂状态：
     *       BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_SAFE_OFF);
     *   - 再停止普通输出：
     *       MotorAPI_StatusSet(false);       // FOC 路径有效时
     *       Motor_SetDuty(0) 或 Motor_Stop(); // 主轴/TLE 路径有效时
     *   - 如果门驱需要保持唤醒以便 SPI/状态诊断，可选择保持 DRV_EN_IDX 使能；
     *     否则用下面方式关闭：
     *       IoHwAb_Dio_WriteChannel(DRV_EN_IDX, 0);
     *
     * 需要人工确认：
     *   - 关闭 DRV_EN_IDX 是否会清除门驱状态或故障锁存。
     */
}

/*
 * 配置注入脉冲宽度，单位为微秒。
 * 该函数对应 MD380 中每次强制脉冲前修改 ePWM 周期/比较寄存器的逻辑。
 */
BLDC_VI_WEAK void BLDC_VI_SetPulseWidthUs(float pulse_width_us)
{
    (void)pulse_width_us;
    /*
     * TODO(USER_PORT): 设置 PWM 周期/比较值，或设置一次性脉冲宽度。
     * 在 MD380 中对应 SynInitPosDetSetTs()。
     *
     * 当前工程中的建议实现：
     *   方案 A，FTU/FOC PWM 路径：
     *     - 现有 FOC PWM 在 motor_svpwm.c 中直接写比较值：
     *         FTU_HWA_SetChannelValue(FTU0, 2, CH_A / 2);
     *         FTU_HWA_SetChannelValue(FTU0, 4, CH_B / 2);
     *         FTU_HWA_SetChannelValue(FTU0, 6, CH_C / 2);
     *         FTU_HWA_GenerateSwSync(FTU0);
     *     - Motor_SetPwmFreq() 会把 FTU0 配为 16-25 kHz 普通 PWM 周期，
     *       但注入需要更短且可控的脉冲。更可能需要新增一个小的 FTU 帮助函数，
     *       按 pulse_width_us 设置周期/计数，而不是直接复用 Motor_SetPwmFreq()。
     *
     *   方案 B，TLE92104 半桥模式路径：
     *     - 使用定时器或任务 tick 状态机保持某个 HBMODE 状态 pulse_width_us，
     *       然后立即切回安全关闭。
     *
     * 需要人工确认：
     *   - FC4150 定时器时钟，以及 FTU 通道 2/4/6 的实际映射。
     *   - ADC 电流采样是在安全关闭前还是关闭后发生。
     */
}

/*
 * 强制 6 个桥臂注入区段之一，或恢复 PWM/进入安全关闭。
 * 具体桥臂编码依赖项目硬件，必须先映射到门驱芯片或 FTU 输出级后，
 * 本模块才能在硬件上运行。
 */
BLDC_VI_WEAK void BLDC_VI_SetBridgeSection(uint8_t section)
{
    (void)section;
    /*
     * TODO(USER_PORT): 强制逆变桥状态。
     * 区段映射沿用 MD380：
     *   0 A+,B-  1 A-,B+  2 B+,C-  3 B-,C+  4 A-,C+  5 A+,C-
     *   6 恢复普通 PWM 寄存器
     *   7 强制所有相关闭/注入初始化状态
     *
     * 当前工程中的建议实现：
     *   如果要尽量贴近 MD380，优先方案如下：
     *     - 使用电机驱动芯片的 HBMODE 寄存器路径，因为 MD380 例程不是普通
     *       SVPWM，而是直接强制高边/低边组合。
     *     - 现有文件已在 Motor_SetDuty()/Motor_Stop() 中写过 HBMODE：
     *         TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table
     *             [Usual_Use_CTRL_HBMODE_INDEX].data = ...;
     *         TLE92104_Usual_Use_CTRL_REG_SPI_Frame_Table
     *             [Usual_Use_CTRL_HBMODE_INDEX].OP = OP_Read_And_WriteOrClear_Bit;
     *         TLE9210x_RegSendAsyncTask(); 或 TLE92108_SpiSendSync(...)
     *     - 需要把每个注入区段映射到正确的 TLE92104 HBMODE 位模式。
     *       当前工程使用 0x06 和 0x09 表示两个普通电机方向，0x00 表示停止，
     *       但这些信息还不足以证明 6 个注入状态的完整映射。
     *
     *   FOC PWM 路径的可能备选方案：
     *     - 强制 e_PWM_INA_IDX/e_PWM_INB_IDX/e_PWM_INC_IDX 或 FTU 通道 2/4/6
     *       的占空比计数，模拟两相脉冲。
     *     - 该方案不够直接，因为每相一个 PWM 比较通道不一定能独立命令高边
     *       和低边状态。
     *
     * 需要人工确认：
     *   - TLE92104/TLE92108 对以下状态的精确 HBMODE 编码：
     *       A 高边 + B 低边，A 低边 + B 高边，
     *       B 高边 + C 低边，B 低边 + C 高边，
     *       A 低边 + C 高边，A 高边 + C 低边，
     *       全关闭，以及恢复普通 PWM 模式。
     *   - 本文件中的 A/B/C 在板级原理图中对应 U/V/W 还是 INA/INB/INC。
     */
}

/*
 * 读取瞬时三相电流，单位为安培。
 * 状态机会在强制脉冲区段前后调用该函数，用于估算 LAB/LBC/LCA 计算所需的
 * 电流增量。
 */
BLDC_VI_WEAK void BLDC_VI_ReadPhaseCurrentA(float *ia, float *ib, float *ic)
{
    /*
     * TODO(USER_PORT): 读取瞬时相电流，单位为安培。
     * 当前工程中的候选数据可能来自 motor_current_0 或 ADC 转换路径，但必须
     * 确认具体比例和采样时序。
     *
     * 当前工程中的建议实现：
     *   方案 A，FOC 电流路径：
     *     - motor_adc.c 中会更新：
     *         extern MotorCurrent motor_current_0;
     *         motor_current_0.ia = (...raw... - offset) * CURRENT_ADC_SCALE;
     *         motor_current_0.ib = (...raw... - offset) * CURRENT_ADC_SCALE;
     *     - 可使用 ia = motor_current_0.ia，ib = motor_current_0.ib；
     *       如果没有 C 相实测值，可令 ic = -(ia + ib)。
     *
     *   方案 B，主轴/电流诊断路径：
     *     - MotorControl.c 中有 Motor_GetCurmA()，基于 g_aCurrentIn50Us[]。
     *       它看起来是单路电机电流估算，不是三相电流。因此除非你明确只想
     *       针对每个强制区段测量导通线电流，否则不足以计算 LAB/LBC/LCA。
     *
     * 需要人工确认：
     *   - ADC 采样是否与脉冲响应同步。MD380 在强制桥臂状态有效期间，通过
     *     ADC 中断采样。
     *   - U/V/W 电流的实际符号约定。虽然算法使用电流增量绝对值，但仍会
     *     按区段选择不同相电流。
     */
    if (ia)
    {
        *ia = 0.0f;
    }
    if (ib)
    {
        *ib = 0.0f;
    }
    if (ic)
    {
        *ic = 0.0f;
    }
}

/*
 * 读取电感计算使用的直流母线电压，单位为伏特。
 * 该值应代表脉冲期间桥臂实际施加的电压，而不是归一化的 FOC 电压指令。
 */
BLDC_VI_WEAK float BLDC_VI_ReadBusVoltageV(void)
{
    /*
     * TODO(USER_PORT): 返回直流母线电压，单位为伏特。
     * 当前工程有 motor_param.vdc 和 Motor_MotVoltTask 两条路径，但需要选择
     * 适用于本注入计算的正确电压。
     *
     * 当前工程中的建议实现：
     *   - MotorControl.c 通过 Motor_MotVoltTask() 根据以下 ADC 通道计算
     *     Motor_MotVolt：
     *       Adc0Channel_23_MOTOR_POSITIVE
     *       Adc1Channel_24_MOTOR_NEGATIVE
     *     并提供接口：
     *       sint32 Motor_GetMotVolt(void)
     *   - 需要确认单位。从代码看 `(adc_diff * 448 / 100)` 像是缩放后的
     *     电压值，但它到底是 mV、0.1V，还是其他由原始值推导的工程单位，
     *     必须验证后在这里换算成 V。
     *
     * 如果 Motor_GetMotVolt() 单位为 mV，可候选使用：
     *   return (float)Motor_GetMotVolt() * 0.001f;
     *
     * 如果只按 FOC 模型参数处理，可候选使用：
     *   return motor_foc_struct.motor_param.vdc;
     *
     * 需要人工确认：
     *   - 注入计算应使用桥臂处的直流母线电压，而不是相电压指令或电机端
     *     差分电压。
     */
    return 0.0f;
}

/*
 * 按需把注入模块故障上报到项目诊断。
 * 台架调试阶段可以保持为空，通过调试器直接读取 BLDC_VI_GetFault() 和
 * BLDC_VI_GetResult()。
 */
BLDC_VI_WEAK void BLDC_VI_ReportFault(BLDC_VI_Fault fault)
{
    (void)fault;
    /*
     * TODO(USER_PORT):
     * 当前工程中的建议实现：
     *   - 调试初期，将该函数保留为仅调试钩子，通过调试器查看
     *     BLDC_VI_GetFault()/BLDC_VI_GetResult()。
     *   - 如果后续需要量产诊断，可把故障映射到 Motor_DTC_Task() 使用的
     *     现有 DTC 路径，例如 g_unMotorErrorStatus 中的开路或短路故障标志。
     *
     * 建议映射思路：
     *   BLDC_VI_FAULT_NO_CURRENT_RESPONSE / PULSE_WIDTH_LIMIT:
     *     可近似认为是输出缺相或注入失败。
     *   BLDC_VI_FAULT_USER_PORT_NOT_READY / INVALID_CONFIG:
     *     属于软件/配置故障，最好不要作为电机硬件 DTC 上报。
     */
}

/*
 * 返回 float 的绝对值。
 * 使用本地小函数，避免嵌入式构建环境中 fabsf 的库依赖差异。
 */
static float BLDC_VI_AbsF(float value)
{
    return (value >= 0.0f) ? value : -value;
}

/*
 * 返回两个 float 中较小的值。
 * MD380 计算会取正/反脉冲响应中的较小值，以减小饱和和不对称因素影响。
 */
static float BLDC_VI_MinF(float a, float b)
{
    return (a <= b) ? a : b;
}

/*
 * 根据桥臂区段选择对应的相电流采样值。
 * 区段 0/1 使用 A 相，2/3 使用 B 相，4/5 使用 C 相，与 MD380 测量顺序一致。
 */
static float BLDC_VI_GetCurrentForSection(uint8_t section)
{
    float ia;
    float ib;
    float ic;

    BLDC_VI_ReadPhaseCurrentA(&ia, &ib, &ic);

    if (section <= 1u)
    {
        return ia;
    }
    if (section <= 3u)
    {
        return ib;
    }
    return ic;
}

/*
 * 将模块置为故障状态，并强制桥臂进入安全状态。
 * 该函数统一故障退出时的关断行为，确保所有错误出口下的注入输出状态一致。
 */
static void BLDC_VI_EnterFault(BLDC_VI_Fault fault)
{
    s_bldc_vi.state = BLDC_VI_STATE_FAULT;
    s_bldc_vi.result.status = BLDC_VI_STATUS_FAULT;
    s_bldc_vi.result.fault = fault;
    BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_SAFE_OFF);
    BLDC_VI_DisableDrive();
    BLDC_VI_ReportFault(fault);
}

/*
 * 在脉冲状态机启动前校验用户配置。
 * 这样可以避免无效的电流限值、时间参数或电阻参数进入桥臂控制步骤。
 */
static bool BLDC_VI_ConfigValid(const BLDC_VI_Config *cfg)
{
    if (cfg == NULL)
    {
        return false;
    }
    if ((cfg->initial_pulse_us <= 0.0f) || (cfg->max_pulse_us <= cfg->initial_pulse_us))
    {
        return false;
    }
    if ((cfg->slow_step_us <= 0.0f) || (cfg->fast_step_us <= 0.0f))
    {
        return false;
    }
    if ((cfg->current_limit_a <= 0.0f) || (cfg->min_current_response_a < 0.0f))
    {
        return false;
    }
    if ((cfg->phase_resistance_ohm < 0.0f) || (cfg->effective_pulse_factor <= 0.0f))
    {
        return false;
    }
    return true;
}

/*
 * 根据捕获到的电流数据计算 LAB/LBC/LCA 和平均线电感。
 * 公式沿用 MD380 思路：
 *   L = (Udc - I * Rs) * pulse_time / I
 */
static void BLDC_VI_CalculateResult(void)
{
    uint8_t index;
    float sum_h = 0.0f;
    float pulse_time_s;

    s_bldc_vi.result.bus_voltage_v = BLDC_VI_ReadBusVoltageV();
    pulse_time_s = s_bldc_vi.result.pulse_width_us * 1.0e-6f * s_bldc_vi.cfg.effective_pulse_factor;

    for (index = 0u; index < 3u; index++)
    {
        uint8_t sel = (uint8_t)(index << 1u);
        float cur1 = BLDC_VI_MinF(s_bldc_vi.result.raw_delta_current_a[sel],
                                  s_bldc_vi.result.raw_delta_current_a[sel + 1u]);
        float cur2 = BLDC_VI_MinF(s_bldc_vi.result.raw_delta_current_a[sel + 6u],
                                  s_bldc_vi.result.raw_delta_current_a[sel + 7u]);
        float delta_i = 0.5f * (cur1 + cur2);
        float effective_voltage;
        float inductance_h;

        s_bldc_vi.result.min_used_current_a[index] = delta_i;

        if (delta_i <= s_bldc_vi.cfg.min_current_response_a)
        {
            BLDC_VI_EnterFault(BLDC_VI_FAULT_NO_CURRENT_RESPONSE);
            return;
        }

        effective_voltage = s_bldc_vi.result.bus_voltage_v
                            - delta_i * s_bldc_vi.cfg.phase_resistance_ohm;
        if (effective_voltage < 0.0f)
        {
            effective_voltage = 0.0f;
        }

        inductance_h = (effective_voltage * pulse_time_s) / delta_i;
        s_bldc_vi.result.line_inductance_h[index] = inductance_h;
        s_bldc_vi.result.line_inductance_mh[index] = inductance_h * 1000.0f;
        sum_h += inductance_h;
    }

    s_bldc_vi.result.average_line_inductance_h = sum_h / 3.0f;
    s_bldc_vi.result.average_line_inductance_mh =
        s_bldc_vi.result.average_line_inductance_h * 1000.0f;
    s_bldc_vi.result.status = BLDC_VI_STATUS_DONE;
    s_bldc_vi.result.fault = BLDC_VI_FAULT_NONE;
    s_bldc_vi.state = BLDC_VI_STATE_DONE;

    BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_RESTORE_PWM);
    BLDC_VI_DisableDrive();
}

/*
 * 用保守默认值填充配置结构体。
 * 这些默认值只是调试占位，需要结合实际电机、母线电压、电流比例和桥臂时序确认。
 */
void BLDC_VI_InitDefaultConfig(BLDC_VI_Config *cfg)
{
    if (cfg == NULL)
    {
        return;
    }

    cfg->initial_pulse_us = 50.0f;
    cfg->max_pulse_us = 60000.0f;
    cfg->slow_step_us = 2.0f;
    cfg->fast_step_us = 20.0f;
    cfg->current_limit_a = 8.0f;
    cfg->min_current_response_a = 0.05f;
    cfg->phase_resistance_ohm = 0.12f;
    cfg->effective_pulse_factor = 2.0f;
}

/*
 * 启动一次新的电压注入电感测量。
 * cfg 传入 NULL 时使用 BLDC_VI_InitDefaultConfig() 的默认配置；但在
 * BLDC_VI_UserPortReady() 返回 true 之前，本函数仍会拒绝实际运行。
 */
void BLDC_VI_Start(const BLDC_VI_Config *cfg)
{
    BLDC_VI_Config local_cfg;

    if (cfg == NULL)
    {
        BLDC_VI_InitDefaultConfig(&local_cfg);
        cfg = &local_cfg;
    }

    (void)memset(&s_bldc_vi, 0, sizeof(s_bldc_vi));
    s_bldc_vi.cfg = *cfg;
    s_bldc_vi.result.status = BLDC_VI_STATUS_BUSY;
    s_bldc_vi.result.fault = BLDC_VI_FAULT_NONE;
    s_bldc_vi.result.pulse_width_us = cfg->initial_pulse_us;

    if (!BLDC_VI_ConfigValid(cfg))
    {
        BLDC_VI_EnterFault(BLDC_VI_FAULT_INVALID_CONFIG);
        return;
    }

    if (!BLDC_VI_UserPortReady())
    {
        BLDC_VI_EnterFault(BLDC_VI_FAULT_USER_PORT_NOT_READY);
        return;
    }

    s_bldc_vi.state = BLDC_VI_STATE_INIT;
}

/*
 * 停止测量状态机，并恢复到安全输出状态。
 * 如果应用逻辑或操作人员中止测试，可调用该函数。
 */
void BLDC_VI_Stop(void)
{
    BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_RESTORE_PWM);
    BLDC_VI_DisableDrive();
    s_bldc_vi.state = BLDC_VI_STATE_IDLE;
    s_bldc_vi.result.status = BLDC_VI_STATUS_IDLE;
}

/*
 * 执行注入测量状态机的一步。
 * 硬件钩子实现后，应在确定性的周期上下文中调用；调用周期必须保证脉冲开关
 * 和电流采样符合预期测量序列。
 */
void BLDC_VI_Task(void)
{
    float cur;

    switch (s_bldc_vi.state)
    {
        case BLDC_VI_STATE_IDLE:
        case BLDC_VI_STATE_DONE:
        case BLDC_VI_STATE_FAULT:
            break;

        case BLDC_VI_STATE_INIT:
            s_bldc_vi.period_cnt = 0u;
            s_bldc_vi.section = 0u;
            s_bldc_vi.pass = 0u;
            s_bldc_vi.base_current_a = 0.0f;
            BLDC_VI_SetPulseWidthUs(s_bldc_vi.result.pulse_width_us);
            BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_SAFE_OFF);
            BLDC_VI_EnableDrive();
            s_bldc_vi.state = BLDC_VI_STATE_FIND_WIDTH;
            break;

        case BLDC_VI_STATE_FIND_WIDTH:
            s_bldc_vi.period_cnt++;
            if (s_bldc_vi.period_cnt >= 6u)
            {
                s_bldc_vi.period_cnt = 0u;
            }

            switch (s_bldc_vi.period_cnt)
            {
                case 0u:
                    BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_SAFE_OFF);
                    s_bldc_vi.section = (uint8_t)((s_bldc_vi.section + 1u) & 0x01u);
                    cur = BLDC_VI_AbsF(BLDC_VI_GetCurrentForSection(0u));
                    if (cur < BLDC_VI_AbsF(s_bldc_vi.base_current_a))
                    {
                        cur = BLDC_VI_AbsF(s_bldc_vi.base_current_a);
                    }

                    if ((cur >= s_bldc_vi.cfg.current_limit_a)
                        || (s_bldc_vi.result.pulse_width_us >= s_bldc_vi.cfg.max_pulse_us))
                    {
                        if ((s_bldc_vi.result.pulse_width_us >= s_bldc_vi.cfg.max_pulse_us)
                            && (cur < s_bldc_vi.cfg.min_current_response_a))
                        {
                            BLDC_VI_EnterFault(BLDC_VI_FAULT_PULSE_WIDTH_LIMIT);
                        }
                        else
                        {
                            s_bldc_vi.period_cnt = 0u;
                            s_bldc_vi.section = 0u;
                            s_bldc_vi.pass = 0u;
                            s_bldc_vi.state = BLDC_VI_STATE_MEASURE;
                        }
                    }
                    else
                    {
                        if (cur > (0.5f * s_bldc_vi.cfg.current_limit_a))
                        {
                            s_bldc_vi.result.pulse_width_us += s_bldc_vi.cfg.slow_step_us;
                        }
                        else
                        {
                            s_bldc_vi.result.pulse_width_us += s_bldc_vi.cfg.fast_step_us;
                        }

                        if (s_bldc_vi.result.pulse_width_us > s_bldc_vi.cfg.max_pulse_us)
                        {
                            s_bldc_vi.result.pulse_width_us = s_bldc_vi.cfg.max_pulse_us;
                        }
                        BLDC_VI_SetPulseWidthUs(s_bldc_vi.result.pulse_width_us);
                    }
                    break;

                case 1u:
                case 4u:
                    BLDC_VI_SetBridgeSection(s_bldc_vi.section);
                    break;

                case 3u:
                    BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_SAFE_OFF);
                    s_bldc_vi.section = (uint8_t)((s_bldc_vi.section + 1u) & 0x01u);
                    s_bldc_vi.base_current_a = BLDC_VI_GetCurrentForSection(0u);
                    break;

                default:
                    break;
            }
            break;

        case BLDC_VI_STATE_MEASURE:
            s_bldc_vi.period_cnt++;
            if (s_bldc_vi.period_cnt >= 3u)
            {
                s_bldc_vi.period_cnt = 0u;
            }

            switch (s_bldc_vi.period_cnt)
            {
                case 0u:
                    {
                        uint8_t sample_index;

                        BLDC_VI_SetBridgeSection(BLDC_VI_SECTION_SAFE_OFF);
                        cur = BLDC_VI_GetCurrentForSection(s_bldc_vi.section);
                        sample_index = (uint8_t)(s_bldc_vi.pass * BLDC_VI_SECTION_COUNT
                                                 + s_bldc_vi.section);
                        s_bldc_vi.result.raw_delta_current_a[sample_index] =
                            BLDC_VI_AbsF(cur - s_bldc_vi.base_current_a);

                        s_bldc_vi.section++;
                        if (s_bldc_vi.section >= BLDC_VI_SECTION_COUNT)
                        {
                            s_bldc_vi.section = 0u;
                            s_bldc_vi.pass++;
                            if (s_bldc_vi.pass >= 2u)
                            {
                                s_bldc_vi.state = BLDC_VI_STATE_CALC;
                            }
                        }
                    }
                    break;

                case 1u:
                    BLDC_VI_SetBridgeSection(s_bldc_vi.section);
                    break;

                case 2u:
                    s_bldc_vi.base_current_a = BLDC_VI_GetCurrentForSection(s_bldc_vi.section);
                    break;

                default:
                    break;
            }
            break;

        case BLDC_VI_STATE_CALC:
            BLDC_VI_CalculateResult();
            break;

        default:
            BLDC_VI_EnterFault(BLDC_VI_FAULT_INVALID_CONFIG);
            break;
    }
}

/*
 * 返回测量模块当前的高层状态。
 * 典型值为 IDLE、BUSY、DONE 或 FAULT。
 */
BLDC_VI_Status BLDC_VI_GetStatus(void)
{
    return s_bldc_vi.result.status;
}

/*
 * 返回测量模块最近一次检测到的故障。
 * 当 BLDC_VI_GetStatus() 返回 FAULT 时，该值才有实际意义。
 */
BLDC_VI_Fault BLDC_VI_GetFault(void)
{
    return s_bldc_vi.result.fault;
}

/*
 * 返回最新测量结果结构体的指针。
 * 返回指针指向内部静态存储，在下一次 BLDC_VI_Start() 调用前保持有效。
 */
const BLDC_VI_Result *BLDC_VI_GetResult(void)
{
    return &s_bldc_vi.result;
}

/*
 * 可选的离线计算辅助函数，用于不驱动硬件的实验室/台架分析。
 * delta_current_a 必须按 MD380 顺序排列：
 *   [0] IA+ [1] IA- [2] IB+ [3] IB- [4] IC+ [5] IC-
 *   [6] IA+ [7] IA- [8] IB+ [9] IB- [10] IC+ [11] IC-
 */
bool BLDC_VI_CalcLineInductanceOffline(const BLDC_VI_Config *cfg,
                                       float bus_voltage_v,
                                       float pulse_width_us,
                                       const float delta_current_a[BLDC_VI_SAMPLE_COUNT],
                                       BLDC_VI_Result *out_result)
{
    uint8_t index;
    float pulse_time_s;
    float sum_h = 0.0f;

    if ((cfg == NULL) || (delta_current_a == NULL) || (out_result == NULL))
    {
        return false;
    }
    if (!BLDC_VI_ConfigValid(cfg) || (pulse_width_us <= 0.0f))
    {
        return false;
    }

    (void)memset(out_result, 0, sizeof(*out_result));
    out_result->status = BLDC_VI_STATUS_DONE;
    out_result->fault = BLDC_VI_FAULT_NONE;
    out_result->pulse_width_us = pulse_width_us;
    out_result->bus_voltage_v = bus_voltage_v;
    pulse_time_s = pulse_width_us * 1.0e-6f * cfg->effective_pulse_factor;

    for (index = 0u; index < BLDC_VI_SAMPLE_COUNT; index++)
    {
        out_result->raw_delta_current_a[index] = delta_current_a[index];
    }

    for (index = 0u; index < 3u; index++)
    {
        uint8_t sel = (uint8_t)(index << 1u);
        float cur1 = BLDC_VI_MinF(delta_current_a[sel], delta_current_a[sel + 1u]);
        float cur2 = BLDC_VI_MinF(delta_current_a[sel + 6u], delta_current_a[sel + 7u]);
        float delta_i = 0.5f * (cur1 + cur2);
        float effective_voltage;

        if (delta_i <= cfg->min_current_response_a)
        {
            out_result->status = BLDC_VI_STATUS_FAULT;
            out_result->fault = BLDC_VI_FAULT_NO_CURRENT_RESPONSE;
            return false;
        }

        effective_voltage = bus_voltage_v - delta_i * cfg->phase_resistance_ohm;
        if (effective_voltage < 0.0f)
        {
            effective_voltage = 0.0f;
        }

        out_result->min_used_current_a[index] = delta_i;
        out_result->line_inductance_h[index] = (effective_voltage * pulse_time_s) / delta_i;
        out_result->line_inductance_mh[index] = out_result->line_inductance_h[index] * 1000.0f;
        sum_h += out_result->line_inductance_h[index];
    }

    out_result->average_line_inductance_h = sum_h / 3.0f;
    out_result->average_line_inductance_mh = out_result->average_line_inductance_h * 1000.0f;
    return true;
}
