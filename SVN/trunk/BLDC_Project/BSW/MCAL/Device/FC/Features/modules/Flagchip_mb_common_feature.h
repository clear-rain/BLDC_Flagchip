#ifndef _DEVICE_FEATURES_FLAGCHIP_MB_COMMON_H_
#define _DEVICE_FEATURES_FLAGCHIP_MB_COMMON_H_

/************ MB Features **************/
#define MB_INSTANCE_COUNT					1u
/** Peripheral MB base address */
#define MB_BASE                            (0x40058000u)
/** Peripheral MB base pointer */
#define MB                             ((MB_Type *)MB_BASE)
/* Channel master done code */
#define MB_MASTER_DONE_CODE                         0xFC730000u


#endif /* _DEVICE_FEATURES_FLAGCHIP_MB_COMMON_H_ */
