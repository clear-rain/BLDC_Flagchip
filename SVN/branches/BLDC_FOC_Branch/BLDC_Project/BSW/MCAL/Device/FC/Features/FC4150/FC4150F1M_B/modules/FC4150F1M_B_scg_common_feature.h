#ifndef _DEVICE_FEATURES_FC4150F1M__B_SCG_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_SCG_COMMON_H_
///** Wait or not in the the clock configuration sequence. */
 /*For FC4150F512:no need */
#define SCG_CLOCK_CONF_WAIT_ACK                    (1u)

#define SCG_LPWDG_SUPPORT   (0u)

/*************** PLL0 Limits ***************/
#define PLL0_VCO_CLK_MAX        400000000U
#define PLL0_VCO_CLK_MIN        180000000U
#define PLL0_FEEDBACK_CLK_MAX   16000000U
#define PLL0_FEEDBACK_CLK_MIN   1000000U
#define PLL0_CLK_MAX            200000000U
#define PLL0_CLK_MIN            90000000U

#endif
