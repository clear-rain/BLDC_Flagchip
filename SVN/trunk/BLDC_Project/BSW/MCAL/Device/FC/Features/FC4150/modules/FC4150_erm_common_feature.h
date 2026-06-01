#ifndef _DEVICE_FEATURES_FC4150_ERM_COMMON_H_
#define _DEVICE_FEATURES_FC4150_ERM_COMMON_H_

/*********************** ERM Features ****************************/

/** Number of instances of the ERM module. */
#define ERM_INSTANCE_COUNT                       (1u)

/* ERM - Peripheral instance base addresses */
/** Peripheral ERM base address */
#define ERM_BASE                                 (0x40018000u)
/** Peripheral ERM base pointer */
#define ERM                                      ((ERM_Type *)ERM_BASE)

/** Array initializer of ERM peripheral base addresses */
#define ERM_BASE_ADDRS                           {ERM_BASE}

/** Array initializer of ERM peripheral base pointers */
#define ERM_BASE_PTRS                            {ERM}

#endif
