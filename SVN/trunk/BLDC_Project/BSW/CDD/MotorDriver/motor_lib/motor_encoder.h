/*
 * motor_encode.h
 * Public API for motor_encode.c
 *
 * 提供编码器传感器状态结构与对外函数声明。
 */

#ifndef MOTOR_ENCODE_H
#define MOTOR_ENCODE_H

#include <stdint.h>
#include <stdbool.h>
#include "typedef.h"
#include "device_header.h"
#include "motor_foc.h" /* for MotorEstimator */

/* 速度计算方式选择：
 * - 0：使用相邻两帧差分（旧实现）
 * - 1：使用环形缓冲窗口累计（新实现，默认）
 * 如需对比，可在此处切换宏值。 */
#ifndef MOTOR_ENCODER_SPEED_USE_BUFFER_WINDOW
#define MOTOR_ENCODER_SPEED_USE_BUFFER_WINDOW (1)
#endif

/* 传感器状态：对外可读（由 motor_encode.c 维护并更新） */
typedef struct
{
    int16_t mechanical_angle;            /* 原始计数，int16_t */
    float mechanical_angle_transformed;  /* 机械角 0..2π（rad） */
    float electrical_angle;              /* 电角 0..2π（rad） */
    float electrical_angle_estimated;    /* 外推电角（rad） */
    float last_electrical_angle;         /* 上一帧电角（rad） */
    uint8_t electrical_area;             /* 保留/兼容区 */
    uint8_t last_electrical_area;        /* 上一帧区域 */
    float electrical_angle_inc_per_tick; /* 电角增量 / tick（rad/tick） */
    float speed;                         /* 机械转速 rpm（滤波后） */
    int8_t direction;                    /* -1/0/1 */
} MOTOR_SENSOR_ENCODER;

/* 由 motor_encode.c 定义的全局可见状态 */
extern volatile MOTOR_SENSOR_ENCODER motor_sensor_encoder_state;

/* 运行时编码器电角度偏置（rad），默认等于 ENCODER_ELEC_ANGLE_OFFSET，
 * 可在开环校准阶段由其他模块修改，替代原先宏的作用。 */
extern float g_encoder_elec_angle_offset_cal;

/* 以 π 为单位的偏置系数：g_encoder_elec_angle_offset_cal = g_encoder_elec_angle_offset_pi * π。
 * 便于在调试器中直接看到 “N·π” 的 N。 */
extern float g_encoder_elec_angle_offset_pi;

/* 初始化编码器模块，驱动初始化时调用 */
void Motor_Encoder_Init(void);

/* 在 NVM 初始化完成后调用：从 NvMEncoderOffset[0] 中加载偏置系数，
 * 同步更新 g_encoder_elec_angle_offset_pi 与 g_encoder_elec_angle_offset_cal。 */
void Motor_Encoder_LoadOffsetFromNvM(void);

/* CAN 接收中断处理（将一帧编码器数据加入缓冲） */
void Motor_Encoder_CAN_IRQ(void);

/* 在估计/FOC 主循环中调用，完成解包、过滤和外推
 * 但保留此签名以便和 motor_foc 模块协同。 */
void Motor_Encoder_Transducer(MotorEstimator *estimator);

/* FTU 溢出/超时中断处理（清零角速度等） */
void Motor_Encoder_FTU_TOF_IRQ(void);

/* 读取最新一帧的原始 int16 计数（-32768..32767） */
int16_t Motor_Encoder_GetLatestRawCnt(void);

/* 1ms 周期调用：更新多圈行程格号（每圈18份） */
void Motor_Encoder_StrokeUpdate_1msTask(void);

int16_t Motor_Encoder_GetStrokeSector(void);
void Motor_Encoder_SetStrokeSector(int16_t sector);

/* 从 NVM 读取 Encoder 行程位置，取代原有 Hall Position 的用途 */
void Motor_Encoder_LoadStrokeFromNvM(void);

/* 将当前 Encoder 行程位置保存到 NVM（使用 EncoderStrokeId Block） */
void Motor_Encoder_SaveStrokeToNvM(void);

#endif /* MOTOR_ENCODE_H */
