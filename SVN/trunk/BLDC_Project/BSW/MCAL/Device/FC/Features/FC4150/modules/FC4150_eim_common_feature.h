#ifndef _DEVICE_FEATURES_FC4150_EIM_COMMON_H_
#define _DEVICE_FEATURES_FC4150_EIM_COMMON_H_

/*********************** EIM Features ****************************/

/** Number of instances of the EIM module. */
#define EIM_INSTANCE_COUNT                       (1u)

/* EIM - Peripheral instance base addresses */
/** Peripheral EIM base address */
#define EIM_BASE                                 (0x40019000u)
/** Peripheral EIM base pointer */
#define EIM                                      ((EIM_Type *)EIM_BASE)

/** Array initializer of EIM peripheral base addresses */
#define EIM_BASE_ADDRS                           {EIM_BASE}

/** Array initializer of EIM peripheral base pointers */
#define EIM_BASE_PTRS                            {EIM}

#endif
