#ifndef _SBC_DRIVER_H_
#define _SBC_DRIVER_H_

// #include "Platform.h"
#include "main.h"

extern void SBC_AllRegsInitSync(void);
extern void SBC_NormalRun(void);

extern void SBC_StopRun(void);
extern void SBC_SleepRun(void);
extern void SBC_RestartModeRun(void);

extern void Cdd_SbcSpiCompleteCallback(struct _FCSPI_HandleType *pFcspiHandle, FCSPI_AtomicBoolType bIsInIsr);

#endif /* _SBC_DRIVER_H_ */


