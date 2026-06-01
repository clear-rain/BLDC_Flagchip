#ifndef MOTOR_LIB_MOTOR_API_H_
#define MOTOR_LIB_MOTOR_API_H_

#include <stdint.h>
#include <stdbool.h>
#include "motor_misc.h" // 引入 MotorCtrlMode 定义
#include "motor_pid.h"  // 直接对外暴露 MotorPid（按你的选项 B）

// 初始化（电机模块初始化，不改变运行状态）
void MotorAPI_Init(void);

// 状态 开/关
void MotorAPI_StatusSet(bool on);
bool MotorAPI_StatusGet(void);

// 控制模式 设置/反馈（电流/速度）
void MotorAPI_ModeSet(MotorCtrlMode mode);
MotorCtrlMode MotorAPI_ModeGet(void);

// 速度 设置/反馈（RPM）
void MotorAPI_SpeedSetRPM(float rpm);
float MotorAPI_SpeedGetRPM(void);

// 电流(Q/D) 设置/反馈
void MotorAPI_CurrentSetDQ(float id_ref, float iq_ref);
void MotorAPI_CurrentGetDQRef(float *id_ref, float *iq_ref);
void MotorAPI_CurrentGetDQMea(float *id_mea, float *iq_mea);

// 电压(Q/D) 设置/反馈（电压模式使用，单位与 motor_d_q_voltage_out 一致）
void MotorAPI_VoltageSetDQ(float vd_ref, float vq_ref);
void MotorAPI_VoltageGetDQRef(float *vd_ref, float *vq_ref);

// 读取当前实际输出的 dq 电压（FOC 最终用于 SVPWM 的值）
void MotorAPI_VoltageGetDQOut(float *vd_out, float *vq_out);

// 运行态接口：设置电流环 PID 的积分(sum)，用于无扰切换
void MotorAPI_CurrentPidRuntimeSetSum(float id_sum, float iq_sum);

// 运行态接口：设置速度环 PID 的积分(sum)，用于速度模式起步注入
void MotorAPI_SpeedPidRuntimeSetSum(float speed_sum);

// PID参数 设置/反馈
void MotorAPI_PidSetSpeed(const MotorPid *pid);
void MotorAPI_PidSetId(const MotorPid *pid);
void MotorAPI_PidSetIq(const MotorPid *pid);
void MotorAPI_PidGetSpeed(MotorPid *pid);
void MotorAPI_PidGetId(MotorPid *pid);
void MotorAPI_PidGetIq(MotorPid *pid);

void MotorAPI_ErrorClear(void);
void MotorAPI_ErrorGet(uint32_t *p);

#endif /* MOTOR_LIB_MOTOR_API_H_ */
