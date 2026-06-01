#ifndef _SPINDLE_CONTROL_H__
#define _SPINDLE_CONTROL_H__

#include "typedef.h"

typedef enum
{
	SPINDLE_DIR_STOP = 0,
	SPINDLE_DIR_OPEN,
	SPINDLE_DIR_CLOSE,
} spindle_direction_e;

typedef enum
{
	PLG_CMD_STOP = 0,
	PLG_CMD_OPEN,
	PLG_CMD_CLOSE,
} PLG_Action_t;

extern PLG_Action_t PLG_Action_Command;

void Spindle_Control_Init(void);
void Spindle_Control_Task_5ms(void);

/* 获取由编码器计算得到的物理转速（单位：rpm，方向同编码器计数方向） */
float Spindle_GetPhysicalSpeedRPM(void);

#endif
