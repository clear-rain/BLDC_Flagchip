#include <stdint.h>
#include <stdbool.h>
#include "Spindle_Control.h"
#include "rte.h"

PLG_Action_t PLG_Action_Command;
volatile uint8_t DebugControlAct = 0;
void APP_5ms(void)
{
    /*
     * 同时支持 Debug 和 CAN 两种控制：
     * DebugControlAct / CAN 命令任意一个发生变化，就切换成该通道的控制逻辑。
     */
    static uint8_t prevDebugControlAct = 0u;
    static uint8_t prevCanCmd = 0u;
    /* 0: CAN 控制；1: Debug 控制 */
    static uint8_t lastCtrlSource = 0u;

    uint8_t CanCmd = 0u;
    bool debugChanged;
    bool canChanged;

    RTE_Read_Com_DRD_FL_DoorOpenAg(&CanCmd);

    debugChanged = (DebugControlAct != prevDebugControlAct);
    canChanged   = (CanCmd         != prevCanCmd);

    if (debugChanged && !canChanged)
    {
        lastCtrlSource = 1u; /* 只 Debug 变化，切到 Debug 控制 */
    }
    else if (canChanged && !debugChanged)
    {
        lastCtrlSource = 0u; /* 只 CAN 变化，切到 CAN 控制 */
    }
    else if (canChanged && debugChanged)
    {
        /* 两个同时变化时，优先使用 CAN 控制（如需改优先级可调整这里） */
        lastCtrlSource = 0u;
    }
    else
    {
        /* 都没变化，则保持上一次的控制通道 */
    }

    /* 根据当前选中的控制通道设定 PLG_Action_Command */
    if (lastCtrlSource == 1u)
    {
        /* Debug 控制：使用 DebugControlAct 的值 */
        switch (DebugControlAct)
        {
            case 0:
                PLG_Action_Command = PLG_CMD_STOP;
                break;
            case 1:
                PLG_Action_Command = PLG_CMD_OPEN;
                break;
            case 2:
                PLG_Action_Command = PLG_CMD_CLOSE;
                break;
            default:
                PLG_Action_Command = PLG_CMD_STOP;
                break;
        }
    }
    else
    {
        /* CAN 控制：使用 CanCmd 的值 */
        switch (CanCmd)
        {
            case 0:
                PLG_Action_Command = PLG_CMD_STOP;
                break;
            case 1:
                PLG_Action_Command = PLG_CMD_OPEN;
                break;
            case 2:
                PLG_Action_Command = PLG_CMD_CLOSE;
                break;
            default:
                PLG_Action_Command = PLG_CMD_STOP;
                break;
        }
    }

    /* 记录本周期值，用于下次判断是否变化 */
    prevDebugControlAct = DebugControlAct;
    prevCanCmd         = CanCmd;
}
