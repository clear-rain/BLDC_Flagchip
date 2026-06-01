#ifndef _DEVICE_FEATURES_FC4150F1M__A_SMISC_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__A_SMISC_COMMON_H_

/** Controls ROM Clock Gating support or not
 * Reserved for FC4150F512. For FC4150F2M and FC4150F1M_A, the reset value of CGCROM is 0b.
 * For FC4150F1M_B, the reset value CGCROM is 1b  */
#define SMISC_ROM_CLOCK_GATING_SUPPORT (1u)
/**  always-on 32K clock for pin filter/stop ack selection support or not.
 *For FC4150F2M, FC4150F1M_A, and FC4150F1M_B, support always-on 32K clock for pin filter/stop ack selection*/
#define SMISC_ALON32KSOURCE_SELECT_SUPPORT  (1u)

#endif
