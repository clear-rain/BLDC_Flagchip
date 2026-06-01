#ifndef _DEVICE_FEATURES_FC4150F1M__S_SCG_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__S_SCG_COMMON_H_
///** Wait or not in the the clock configuration sequence. */
 /*For FC4150F512:no need */
#define SCG_CLOCK_CONF_WAIT_ACK                    (1u)

#define SCG_LPWDG_SUPPORT   (1u)
#define SCG_POSTDIV_SUPPORT (1u)

/*************** PLL0 Limits ***************/
#define PLL0_VCO_CLK_MAX        600000000U
#define PLL0_VCO_CLK_MIN        200000000U
#define PLL0_FEEDBACK_CLK_MAX   4000000U
#define PLL0_FEEDBACK_CLK_MIN   2000000U
#define PLL0_CLK_MAX            300000000U
#define PLL0_CLK_MIN            100000000U


#endif
