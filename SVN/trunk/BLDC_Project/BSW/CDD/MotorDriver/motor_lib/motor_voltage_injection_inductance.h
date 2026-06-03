/***************************************************************************
文件功能：电压脉冲注入测量线电感模块声明
文件说明：
    1. 本头文件只放对外需要使用的宏、结构体、全局变量和函数声明。
    2. 硬件移植相关 USER_PORT 函数在 .c 中有弱定义，接入时可以用同名
       强定义替换，也可以直接在 .c 文件中补齐。
***************************************************************************/

#ifndef MOTOR_VOLTAGE_INJECTION_INDUCTANCE_H_
#define MOTOR_VOLTAGE_INJECTION_INDUCTANCE_H_

#include <stdint.h>
#include <IoHwAb_Dio.h>

#ifndef DSP_CLOCK
#define DSP_CLOCK                  (1u)
#endif

#define SYNI_CUR_Q12               (4096.0f)
#define SYNI_CUR_BUF_NUM           (12u)
#define SYNI_PHASE_NUM             (3u)

#define SYNI_STATUS_IDLE           (0u)
#define SYNI_STATUS_BUSY           (1u)
#define SYNI_STATUS_FINISH         (2u)
#define SYNI_STATUS_FAULT          (3u)

#define SYNI_FAULT_NONE            (0u)
#define SYNI_FAULT_USER_PORT       (1u)
#define SYNI_FAULT_PULSE_WIDTH     (2u)
#define SYNI_FAULT_NO_CURRENT      (3u)
#define SYNI_FAULT_NO_UDC          (4u)

typedef uint8_t  Uchar;
typedef uint16_t Uint;
typedef uint32_t Ulong;

/*******************结构体声明******************************************/
typedef struct
{
	Uint  Step;                         // 辨识状态，仿照 gIPMInitPos.Step
	Uint  PeriodCnt;                    // 周期计数，配合发波和采样
	Uint  Section;                      // 当前桥臂区段，0-5 为六种注入状态
	Uint  PhsChkStep;                   // 保留字段，当前只做电感测量时不使用
	Uint  PWMTs;                        // 当前注入脉宽计数，单位为 DSP_CLOCK tick
	Uint  InitPWMTs;                    // 初始注入脉宽计数
	Uint  MaxPWMTs;                     // 脉宽搜索上限
	Uint  SlowStepTs;                   // 接近电流限值时的脉宽步长
	Uint  FastStepTs;                   // 远低于电流限值时的脉宽步长
	int32_t    CurFirst;                     // 注入前基准电流，Q12
	int32_t   CurLimit;                     // 电流响应限值，Q12
	int32_t   CurMin;                       // 最小有效电流响应，Q12
	int32_t   Cur[SYNI_CUR_BUF_NUM];        // IU+、IU-、IV+、IV-、IW+、IW- 两轮
	Uint  LPhase[SYNI_PHASE_NUM];       // 线电感，单位 0.01mH，仿照 MD380
	float LPhase_H[SYNI_PHASE_NUM];     // 线电感，单位 H
	float LPhase_mH[SYNI_PHASE_NUM];    // 线电感，单位 mH
	float LPhaseAvg_mH;                 // 三个线电感平均值，单位 mH
	float CurLimitA;                    // 电流限值，单位 A，用于生成 CurLimit
	float CurMinA;                      // 最小有效响应，单位 A，用于生成 CurMin
	float RsOhm;                        // 定子相/线电阻，用于扣除 I*R 压降
	float UdcVolt;                      // 最近一次计算使用的母线电压，单位 V
	float PulseTimeK;                   // 等效脉冲时间系数，MD380 计算约为 2 倍脉宽
	Uint  Status;                       // SYNI_STATUS_xxx
	Uint  Fault;                        // SYNI_FAULT_xxx
} IPM_INITPOS_PULSE_STR;

/*******************全局变量声明****************************************/
extern IPM_INITPOS_PULSE_STR gIPMInitPos;

/*******************相关函数声明****************************************/
void SynInitPosParDefault(void);
void SynInitPosStart(void);
void SynInitPosDetect(void);
void SynCalLabAndLbc(void);
void SynInitPosDetSetTs(void);
void SynInitPosDetSetPwm(Uint Section);
void EnableDrive(void);
void DisableDrive(void);

/*******************USER_PORT 函数声明**********************************/
Uint  SynUserPortReady(void);
void  SynUserPortSetPulseWidthUs(float PulseWidthUs);
void  SynUserPortSetBridgeSection(Uint Section);
void  SynUserPortReadIUVW(float *Iu, float *Iv, float *Iw);
float SynUserPortReadUDC(void);
void  SynUserPortReportFault(Uint Fault);

#endif /* MOTOR_VOLTAGE_INJECTION_INDUCTANCE_H_ */
