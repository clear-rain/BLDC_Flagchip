#ifndef _DEVICE_FEATURES_FC4150F1M__B_FLASH_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__B_FLASH_COMMON_H_
/*********************** FLASH Features ****************************/

#define FLASHDRV_ADDR            0x0180D000U

#define DFLASH_SUPPORT                            STD_ON

#define PFLASH_FINE_SUPPORT                       STD_ON

#define FLASH_API_EXTENDED_SUPPORT                STD_ON

#define FLASH_API_1MB_SUPPORT                     STD_ON

#define FLASH									  ((FLASH_ROM_API_ENTRY_T*)FLASHDRV_ADDR)
#define FLASHDRV_BASE_ADDR						  {FLASH}
#define FLASH_INSTANCE_COUNT                      0x1U

/** PFlash total size */
#define PFLASH_SIZE                               0x100000U
/** DFlash total size */
#define DFLASH_SIZE                               0x20000U
/** Flash bank size */
#define PFLASH_BANK_SIZE                          0x80000U
/** Flash 256K size */
#define FLASH_256KB_SIZE                          0x40000U
/** Flash phantom offset */
#define PFLASH_PHANTOM_OFFSET                     (PFLASH_BANK_SIZE - FLASH_256KB_SIZE)
/** NVR total size */
#define NVR_SIZE                                  0xC000U
/** Flash start address */
#define PFLASH_ADDR_START                         0x00U
/** Flash end address */
#define PFLASH_ADDR_END                           0xFFFFFu
/** Two Flash Bank, every bank is 256KB */
#define PFLASH_BANK_NUM                           0x02U
/** Bank 0 start address */
#define PFLASH_BANK0_START                        0x00U
/** Bank 0 end address */
#define PFLASH_BANK0_END                          0x7FFFFu
/** Bank 0 tail start address */
#define PFLASH_BANK0_TAIL_256K_START              0x40000u
/** Bank 1 start address */
#define PFLASH_BANK1_START                        0x80000u
/** Bank 1 end address */
#define PFLASH_BANK1_END                          PFLASH_ADDR_END
/** Bank 1 tail start address */
#define PFLASH_BANK1_TAIL_256K_START              (PFLASH_BANK1_END + 1 - 0x40000)
/** Program minimum size */
#define PFLASH_PROGRAM_PAGE_MIN_SIZE              0x08U
/** PFLASH Erase size */
#define PFLASH_ERASE_SECTOR_SIZE                  0x800U /* 2048 bytes */
#define DFLASH_PROGRAM_PAGE_MIN_SIZE              0x08U
/** DFLASH Erase size */
#define DFLASH_ERASE_SECTOR_SIZE                  0x800U /* 2048 bytes */
/** Flash start address */
#define DFLASH_ADDR_START                         0x01100000U
/** Flash end address */
#define DFLASH_ADDR_END                           0x0111FFFFu
/** DFlash bank0 start address */
#define DFLASH_BANK0_START                        0x01100000U
/** DFlash bank0 end address */
#define DFLASH_BANK0_END                          0x0111FFFFu
/** Program maximum */
#define FLASH_PROGRAM_PAGE_MAX_SIZE               0x80U  /* 128 bytes */
/** DFlash index */
#define DFLASH_INDEX                              PFLASH_BANK_NUM


/** status_t */
#define     STATUS_SUCCESS                        0x000UL
#define     STATUS_ERROR                          0x001UL
#define     STATUS_ECC_ERROR                      0x010UL
#define     STATUS_ECC_WARNING                    0x020UL
#define     STATUS_AEE_ERROR                      0x040UL
#define     STATUS_EDC_ERROR                      0x080UL
#define     STATUS_RWW_ERROR                      0x100UL
#define     STATUS_PEP_ERROR                      0x200UL
#define     STATUS_PES_ERROR                      0x400UL
#define     STATUS_HVOP                           0x800UL
#define     STATUS_PEG_FAILED                     0x1000UL
#define     STATUS_ANA                            0x2000UL
#define     STATUS_WDG_ERROR                      0x4000UL
#define     STATUS_NVR_LOCK                       0x8000UL
#define     STATUS_RE_ERROR                       0x10000UL
#define     STATUS_ENC_ERROR                      0x20000UL
#define     STATUS_NVR_CFG_LOAD_ERROR             0x40000UL
#define     STATUS_NVR_LOAD_ERROR                 0x80000UL
#define     STATUS_OTA_LOAD_ERROR                 0x100000UL
#define     STATUS_ARRAY_BP                       0x200000UL
#define     STATUS_NVR_TIMEOUT_ERROR              0x400000UL

/** FLASH_READ_STATUS_CHECK_SELECT_T */
#define     FLASH_ECC_CHECK                       0x010UL
#define     FLASH_SBC_CHECK                       0x020UL
#define     FLASH_AEE_CHECK                       0x040UL
#define     FLASH_EDC_CHECK                       0x080UL
#define     FLASH_RWW_CHECK                       0x100UL
#define     FLASH_PEP_CHECK                       0x200UL
#define     FLASH_PES_CHECK                       0x400UL
#define     FLASH_HVOP_CHECK                      0x800UL
#define     FLASH_PEG_CHECK                       0x1000UL
#define     FLASH_ANA_CHECK                       0x2000UL
#define     FLASH_WDG_CHECK                       0x4000UL
#define     FLASH_NVR_LOCK_CHECK                  0x8000UL
#define     FLASH_RE_CHECK                        0x10000UL
#define     FLASH_ENC_CHECK                       0x20000UL
#define     FLASH_NVR_CFG_LOAD_CHECK              0x40000UL
#define     FLASH_NVR_LOAD_CHECK                  0x80000UL
#define     FLASH_OTA_LOAD_CHECK                  0x100000UL
#define     FLASH_ARRAY_BP_CHECK                  0x200000UL
#define     FLASH_NVR_TIMEOUT_CHECK               0x400000UL

/** FLASH_PRGM_SIZE_T */
#define     FLASH_PRGM_SIZE1     2UL
#define     FLASH_PRGM_SIZE2     4UL
#define     FLASH_PRGM_SIZE3     6UL
#define     FLASH_PRGM_SIZE4     8UL
#define     FLASH_PRGM_SIZE5     10UL
#define     FLASH_PRGM_SIZE6     12UL
#define     FLASH_PRGM_SIZE7     14UL
#define     FLASH_PRGM_SIZE8     16UL
#define     FLASH_PRGM_SIZE9     18UL
#define     FLASH_PRGM_SIZE10    20UL
#define     FLASH_PRGM_SIZE11    22UL
#define     FLASH_PRGM_SIZE12    24UL
#define     FLASH_PRGM_SIZE13    26UL
#define     FLASH_PRGM_SIZE14    28UL
#define     FLASH_PRGM_SIZE15    30UL
#define     FLASH_PRGM_SIZE16    32UL

/** FLASH_WAIT_STATE_SELECT_T */
#define     FLASH_WAIT_SELECT1    1UL
#define     FLASH_WAIT_SELECT2    2UL
#define     FLASH_WAIT_SELECT3    3UL
#define     FLASH_WAIT_SELECT4    4UL
#define     FLASH_WAIT_SELECT5    5UL
#define     FLASH_WAIT_SELECT6    6UL
#define     FLASH_WAIT_SELECT7    7UL
#define     FLASH_WAIT_SELECT8    8UL

/** FLASH_MARGIN_LEVEL_SELECT_T */
#define     FLASH_MARGIN_LEVEL0    0UL
#define     FLASH_MARGIN_LEVEL1    1UL

/** FLASH_WDG_TIMEOUT_SELECT_T */
#define     FLASH_WDG_TIMEOUT_SELECT0    0UL
#define     FLASH_WDG_TIMEOUT_SELECT1    1UL
#define     FLASH_WDG_TIMEOUT_SELECT2    2UL
#define     FLASH_WDG_TIMEOUT_SELECT3    3UL

/** FLASH_WDG_CFG_T */
#define     FLASH_WDG_ENABLE     0UL
#define     FLASH_WDG_DISABLE    1UL

/** FLASH_WDG_INT_CFG_T */
#define     FLASH_WDG_INT_ENABLE     1UL
#define     FLASH_WDG_INT_DISABLE    0UL

/** FLASH_PRGM_WDG_TUNE_SELECT_T */
#define     WDG_TUNE_DISABLE    0x1UL
#define     WDG_TUNE_ENABLE     0x0UL

/** status_t */
#define     FLASH_BUF_PREF_DISABLE    0x0UL
#define     FLASH_BUF_PREF_ENABLE     0x1UL

/** status_t */
#define     FLASH_READ_WAIT_LOCK_DISABLE    0x0UL
#define     FLASH_READ_WAIT_LOCK_ENABLE     0x1UL

/** status_t */
#define     FLASH_AUTO_HOLD_DISABLE       0x0UL
#define     FLASH_AUTO_HOLD_ENABLE        0x1UL

typedef struct
{
    uint32_t blk_sel;
    uint32_t dest;
} FLASH_DRV_ERASESECTOR_CFG_T;

typedef struct
{
    uint32_t dest;
    uint32_t size;
    uint32_t *pData;
    uint32_t  wdg_tune;
} FLASH_DRV_PRGM_CFG_T;

typedef struct
{
    uint32_t dest;
    uint32_t sed0;
    uint32_t sed1;
    uint32_t sed2;
    uint32_t sed3;
    uint32_t sed4;
    uint32_t sed5;
    uint32_t sed6;
    uint32_t sed7;
    uint32_t sed8;
    uint32_t sed9;
    uint32_t  wait_number;
    uint32_t  mrv;
    uint32_t  ais;
    uint32_t    bpe;
} FLASH_DRV_TEST_CHECK_CFG_T;

typedef struct
{
    uint32_t data0;
    uint32_t data1;
    uint32_t data2;
    uint32_t data3;
    uint32_t data4;
    uint32_t data5;
    uint32_t data6;
    uint32_t data7;
    uint32_t data8;
    uint32_t data9;
} FLASH_DRV_TEST_CHECK_DATA_CFG_T;

typedef struct
{
    uint32_t time;
    uint32_t wint_en;
    uint32_t wen;
} FLASH_DRV_WDG_CFG_T;

typedef struct
{
    uint32_t data1;
    uint32_t data2;
    uint32_t data3;
    uint32_t dest;
} FLASH_DRV_ECC_CHECK_CFG_T;

typedef struct
{
    uint32_t CBUF;
    uint32_t DBUF;
    uint32_t CPREF;
    uint32_t DPREF;
} FLASH_DRV_BUF_PREF_CFG_T;

typedef struct
{
    uint32_t lock_sel;
    uint32_t  wait_number;
} FLASH_DRV_READ_WAIT_CFG_T;

typedef enum
{
    FLASH_TEST_CFG_DISABLE = 0x0UL,
    FLASH_TEST_CFG_ENABLE  = 0x1UL,
    FLASH_TEST_NO_CFG      = 0xFFFFFFFFUL
} FLASH_DRV_TEST_CFG_E;

typedef struct
{
    FLASH_DRV_TEST_CFG_E    ecc_in_cfg;
    FLASH_DRV_TEST_CFG_E    edc_in_cfg;
    FLASH_DRV_TEST_CFG_E    ecc_single_bit_cfg;
} FLASH_DRV_TEST_CFG_T;

typedef struct{
	uint32_t ehv;
	uint32_t ers;
	uint32_t ess;
	uint32_t pgm;
	uint32_t pecie;
	uint32_t encie;
	uint32_t edcie;
}FLASH_DRV_MCTL_CFG_T;


typedef uint32_t (* FLASH_ERASE_BLOCK_FUNC)(uint32_t blk_sel);
typedef uint32_t (* FLASH_VOID_FUNC)(void);
typedef uint32_t (* FLASH_ERASE_SECTOR_FUNC)(FLASH_DRV_ERASESECTOR_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_PROGRAM_FUNC)(FLASH_DRV_PRGM_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_TEST_CHECK_FUNC)(FLASH_DRV_TEST_CHECK_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_READ_STATUS_CHECK_FUNC)(uint32_t  flash_api_cfg);
typedef uint32_t (* FLASH_READ_STATUS_CLEAR_FUNC)(uint32_t  flash_api_cfg);
typedef uint32_t (* FLASH_TEST_STATUS_FUNC)(FLASH_DRV_TEST_CHECK_DATA_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_WDOG_CFG_FUNC)(FLASH_DRV_WDG_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_ECC_CHECK_FUNC)(FLASH_DRV_ECC_CHECK_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_BUF_PREF_FUNC)(FLASH_DRV_BUF_PREF_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_READ_WAIT_CFG)(FLASH_DRV_READ_WAIT_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_AUTO_HOLD_FUNC)(uint32_t flash_api_cfg);
typedef uint32_t (* FLASH_READ_ADDR_FUNC)(uint32_t *data0);
typedef uint32_t (* FLASH_TEST_CFG_FUNC)(FLASH_DRV_TEST_CFG_T *flash_api_cfg);
typedef uint32_t (* FLASH_TEST_BP_CFG_FUNC)(FLASH_DRV_TEST_CFG_E flash_api_cfg);
typedef uint32_t (* FLASH_SECTOR_PROGRAM_FUNC)(uint32_t *dest, uint32_t *addr, uint32_t *info);
typedef uint32_t (* FLASH_DRV_MCTL_CFG_FUNC)(FLASH_DRV_MCTL_CFG_T *flash_api_cfg);

typedef struct
{
    FLASH_ERASE_BLOCK_FUNC                  FLASH_DRV_EraseBlock;
    FLASH_VOID_FUNC                         FLASH_DRV_EraseBlock_Clear;
    FLASH_ERASE_SECTOR_FUNC                 FLASH_DRV_EraseSector;
    FLASH_VOID_FUNC                         FLASH_DRV_EraseSector_Clear;
    FLASH_VOID_FUNC                         FLASH_DRV_EraseNvr;
    FLASH_VOID_FUNC                         FLASH_DRV_EraseNvr_Clear;
    FLASH_PROGRAM_FUNC                      FLASH_DRV_Program;
    FLASH_VOID_FUNC                         FLASH_DRV_Program_Clear;
    FLASH_PROGRAM_FUNC                      FLASH_DRV_Program_Nvr;
    FLASH_VOID_FUNC                         FLASH_DRV_Program_Nvr_Clear;
    FLASH_TEST_CHECK_FUNC                   FLASH_DRV_Array_Integrity_Check;
    FLASH_TEST_CHECK_FUNC                   FLASH_DRV_Margin_Read_Check;
    FLASH_READ_STATUS_CHECK_FUNC            FLASH_DRV_Read_Status_Check;
    FLASH_READ_STATUS_CLEAR_FUNC            FLASH_DRV_Read_Status_Check_Clear;
    FLASH_VOID_FUNC                         FLASH_DRV_HV_Status_Check;
    FLASH_TEST_STATUS_FUNC                  FLASH_DRV_Test_Status_Check;
    FLASH_WDOG_CFG_FUNC                     FLASH_DRV_Wdog_Configure;
    FLASH_VOID_FUNC                         FLASH_DRV_Wdog_Status;
    FLASH_VOID_FUNC                         FLASH_DRV_Wdog_Status_Clear;
    FLASH_ECC_CHECK_FUNC                    FLASH_DRV_EDC_Check;
    FLASH_ECC_CHECK_FUNC                    FLASH_DRV_ECC_Check;
    FLASH_VOID_FUNC                         FLASH_DRV_Test_Mode_Close;
    FLASH_BUF_PREF_FUNC                     FLASH_DRV_BUF_PREF_CFG;
    FLASH_READ_WAIT_CFG                     FLASH_DRV_Read_Wait_CFG;
    FLASH_AUTO_HOLD_FUNC                    FLASH_DRV_ENABLE_HOLD_CFG;
    FLASH_READ_ADDR_FUNC                    FLASH_DRV_READ_ADDR_FUNC;
    FLASH_TEST_CFG_FUNC                     FLASH_DRV_Test_Cfg_FUNC;
    FLASH_TEST_BP_CFG_FUNC                  FLASH_DRV_Array_Integrity_Suspend_FUNC;
    FLASH_VOID_FUNC                         FLASH_DRV_Test_Mode_Open;
    FLASH_SECTOR_PROGRAM_FUNC               FLASH_DRV_Sector_Program;
    FLASH_VOID_FUNC                         FLASH_DRV_CTL_Config_FUNC;
    FLASH_DRV_MCTL_CFG_FUNC                 FLASH_DRV_Config_FUNC;
} FLASH_ROM_API_ENTRY_T;



#endif
