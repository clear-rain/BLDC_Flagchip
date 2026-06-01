#ifndef _DEVICE_FEATURES_FC4150F512_RCM_COMMON_H_
#define _DEVICE_FEATURES_FC4150F512_RCM_COMMON_H_
/**  The reset filter can use a AON32K clock or can not. */
/** FC4150F512 does not support a reset filter using the AON32K clock */
#define RCM_RESETPIN_FILTER_CLKSRC_SUPPORT_AON32K    (0u)
/**   the clock of reset delay time from when the interrupt asserts and the reset eventually occurs used is AON32K clock.*/
#define RCM_RESET_DELAY_CLOCK_AON32K                 (0u)

#define RCM_RESET_REQ_TOUT_SUPPORT (0u)

#endif
