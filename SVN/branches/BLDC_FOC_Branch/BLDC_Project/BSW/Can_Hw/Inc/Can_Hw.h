#ifndef CAN_HW_H_
#define CAN_HW_H_

#include "v_def.h"
#ifndef ECU_ADDRESS_BLDC
#include "CanSM.h"
#else
#endif
#include "module_driver_flexcan.h"

#define E_OK      0
#define E_NOT_OK  1
/* MCR bit31: Module Disable (module disabled when 1) */
#define FLEXCAN_MCR_MDIS_U32                    ((uint32)0x80000000U)
/* MCR bit30: Freeze enable (enable to enter freeze mode when HALT is set) */
#define FLEXCAN_MCR_FRZ_U32                     ((uint32)0x40000000U)
/* MCR bit29: FIFO mode enable */
#define FLEXCAN_MCR_FEN_U32                     ((uint32)0x20000000U)
/* MCR bit28: Module Halt (module enters freeze mode when this bit is set providing the FRZ bit is set) */
#define FLEXCAN_MCR_HALT_U32                    ((uint32)0x10000000U)
/* CTRL bit15: Bus Off Mask (bus off interrupt enabled when set) */
#define FLEXCAN_CTRL_BOFFMSK_U32                ((uint32)0x00008000U)
#define FLEXCAN_CTRL_BOFFMSK_SHIFT_U32          ((uint32)15U)
/* ESR bit2: Bus off interrupt flag (set after the module enters bus off state) */
#define FLEXCAN_ESR_BOFFINT_U32                 ((uint32)0x00000004U)
#define FLEXCAN_ESR_BOFFINT_SHIFT_U32           ((uint32)2U)
#define FLEXCAN_ESR_ERRINT_U32                  ((uint32)0x00000002U)
#define FLEXCAN_ESR_ERRINT_SHIFT_U32            ((uint32)1U)

/* FLEXCAN - Peripheral instance base addresses */
/** Peripheral FLEXCAN0 base address */
#define FLEXCAN0_BASE                            (0x40080000u)
/** Peripheral FLEXCAN0 base pointer */
#define FLEXCAN0                                 ((FLEXCAN_Type *)FLEXCAN0_BASE)
/** Peripheral FLEXCAN1 base address */
#define FLEXCAN1_BASE                            (0x40084000u)
/** Peripheral FLEXCAN1 base pointer */
#define FLEXCAN1                                 ((FLEXCAN_Type *)FLEXCAN1_BASE)
/** Peripheral FLEXCAN2 base address */
#define FLEXCAN2_BASE                            (0x40088000u)
/** Peripheral FLEXCAN2 base pointer */
#define FLEXCAN2                                 ((FLEXCAN_Type *)FLEXCAN2_BASE)
/** Array initializer of FLEXCAN peripheral base addresses */
#define FLEXCAN_BASE_ADDRS                       {FLEXCAN0_BASE, FLEXCAN1_BASE, FLEXCAN2_BASE}
/** Array initializer of FLEXCAN peripheral base pointers */
#define FLEXCAN_BASE_PTRS                        {FLEXCAN0, FLEXCAN1, FLEXCAN2}

#define FLEXCAN_INSTANCE_COUNT                   (3u)

#define FLEXCAN_ESR_CONFIG_MASK_U32         ((uint32)0x00130006U)

typedef enum
{
    CAN_CS_UNINIT = 0U, /**< CAN controller state UNINIT. */
    CAN_CS_STARTED,     /**< CAN controller state STARTED. */
    CAN_CS_STOPPED,     /**< CAN controller state STOPPED. */
    CAN_CS_SLEEP        /**< CAN controller state SLEEP. */
} Can_ControllerStateType;

uint8 Can_Hw_ChkBusOffStatus(uint8 u8CanIndex);
void Can_FlexCan_BusOff(uint8 u8CanIndex);
uint8 Can_SetControlMode(Can_ControllerStateType Transition);
uint8 CanSetControlToStopMode(void);
uint8 CanSetControlToStartMode(void);
#endif
