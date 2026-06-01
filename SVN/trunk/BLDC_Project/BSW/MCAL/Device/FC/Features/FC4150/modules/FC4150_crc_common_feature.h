#ifndef _DEVICE_FEATURES_FC4150_CRC_COMMON_H_
#define _DEVICE_FEATURES_FC4150_CRC_COMMON_H_
/*********************** CRC Features ****************************/
/** Number of instances of the CRC module. */
#define CRC_INSTANCE_COUNT                       (1u)
/* CRC - Peripheral instance base addresses */
/** Peripheral CRC base address */
#define CRC_BASE                                 (0x40032000u)
/** Peripheral CRC base pointer */
#define CRC                                      ((CRC_Type *)CRC_BASE)
/** Array initializer of CRC peripheral base addresses */
#define CRC_BASE_ADDRS                           {CRC_BASE}
/** Array initializer of CRC peripheral base pointers */
#define CRC_BASE_PTRS                            {CRC}
#endif
