#ifndef _SBC_DIAG_H_
#define _SBC_DIAG_H_

#include "SBC_Types.h"

E_CDD_SBC_ERR_STATUS SBC_Diag_ReadChipId(void);
extern void SBC_DiagInit(void);
extern void SBC_DiagDeal(void);

#endif /* _SBC_DIAG_H_ */
