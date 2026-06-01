#ifndef _DEVICE_FEATURES_FC4150F1M__B_CMP_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_CMP_COMMON_H_
/*********************** CMP Features ****************************/
#ifdef CMP_INSTANCE_COUNT
#undef CMP_INSTANCE_COUNT
#endif
/** Number of instances of the FLEXCAN module. */
#define CMP_INSTANCE_COUNT                   (1u)

/** Peripheral CMP0 base address */
#define CMP0_BASE                                (0x40073000u)

/** Peripheral CMP0 base pointer */
#define CMP0                                     ((CMP_Type *)CMP0_BASE)

#ifdef CMP_BASE_ADDRS
#undef CMP_BASE_ADDRS
#endif
/** Array initializer of CMP peripheral base addresses */
#define CMP_BASE_ADDRS                           {CMP0_BASE}

#ifdef CMP_BASE_PTRS
#undef CMP_BASE_PTRS
#endif
/** Array initializer of CMP peripheral base pointers */
#define CMP_BASE_PTRS                            {CMP0}

#define CMP_SUPPORT_CHANNELSCAN_MODE_FEATURE

#endif
