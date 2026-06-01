#ifndef _SBC_TYPES_H_
#define _SBC_TYPES_H_

// #include "Platform.h"
#include "main.h"
typedef struct {
	uint8_t u8Addr;
	uint8_t u8Data;
	uint8_t u8OpFlg;
} SBC_Reg_t;

typedef enum {
    e_CDD_SBC_INIT_MODE = 0,	// Power on mode
    e_CDD_SBC_NORMAL_MODE,	    // Normal mode
    e_CDD_SBC_SLEEP_MODE,		// Sleep mode
    e_CDD_SBC_STOP_MODE,		// Stop mode
	e_CDD_SBC_RESET_MODE,		// Reset mode
	e_CDD_SBC_FAILSAFE_MODE,	// Fail-Safe mode
	e_CDD_SBC_SPI_ERROR_MODE,	// SPI error mode	
	e_CDD_SBC_MAX_MODE
}E_CDD_SBC_MODE;

typedef enum {
   e_CDD_SBC_OK = 0,
   e_CDD_SBC_ERROR,
}E_CDD_SBC_ERR_STATUS;

#endif /* _SBC_TYPES_H_ */