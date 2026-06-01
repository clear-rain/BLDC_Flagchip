#ifndef _DEVICE_FEATURES_FC4150F1M__A_FLASH_COMMON_H_
#define _DEVICE_FEATURES_FC4150F1M__A_FLASH_COMMON_H_
/*********************** FLASH Features ****************************/

#define FLASHDRV_ADDR            0x01817000U

#define DFLASH_SUPPORT                            STD_ON

#define PFLASH_FINE_SUPPORT                       STD_OFF

#define FLASH									  ((FLASH_ROM_API_ENTRY_T*)FLASHDRV_ADDR)
#define FLASHDRV_BASE_ADDR						  {FLASH}
#define FLASH_INSTANCE_COUNT                      0x1U

/** PFlash total size */
#define PFLASH_SIZE                               0x100000U
/** PFlash start address */
#define PFLASH_ADDR_START                         0x00U
/** Flash bank size */
#define PFLASH_BANK_SIZE                          0x100000U
/** Flash 256K size */
#define FLASH_256KB_SIZE                          0x40000U
/** Flash phantom offset */
#define PFLASH_PHANTOM_OFFSET                     (PFLASH_BANK_SIZE - FLASH_256KB_SIZE)
/** Flash end address */
#define PFLASH_ADDR_END                           0xFFFFFu
/** One PFlash Bank, every bank is 1MB */
#define PFLASH_BANK_NUM                           0x01U
/** Flash Bank 0 size */
#define PFLASH_BANK0_SIZE                         0x100000U
/** Bank 0 start address */
#define PFLASH_BANK0_START                        0x00U
/** Bank 1 end address */
#define PFLASH_BANK0_END                          0xFFFFFu
/** Bank 0 tail 256k start address */
#define PFLASH_BANK0_TAIL_256K_START              0xC0000U
/** Program minimum size */
#define PFLASH_PROGRAM_PAGE_MIN_SIZE              0x08U
/** Erase size */
#define PFLASH_ERASE_SECTOR_SIZE                  0x2000U /* 8192 bytes */
/** DFlash total size */
#define DFLASH_SIZE                               0x40000U
/** Flash start address */
#define DFLASH_ADDR_START                         0x01100000U
/** Flash end address */
#define DFLASH_ADDR_END                           0x0113FFFFu
/** One DFlash Bank, every bank is 256KB */
#define DFLASH_BANK_NUM                           0x01U
/** Bank 0 start address */
#define DFLASH_BANK0_START                        0x01100000U
/** Bank 0 end address */
#define DFLASH_BANK0_END                          0x0113FFFF
/** Program minimum size */
#define DFLASH_PROGRAM_PAGE_MIN_SIZE              0x08U
/** Erase size */
#define DFLASH_ERASE_SECTOR_SIZE                  0x2000U /* 8192 bytes */
/** Program maximum */
#define FLASH_PROGRAM_PAGE_MAX_SIZE               0x80U  /* 128 bytes */
/** DFlash index */
#define DFLASH_INDEX                              PFLASH_BANK_NUM

#define STATUS_SUCCESS       0x000UL
#define STATUS_ERROR         0x001UL
#define STATUS_HVOP          0x002UL
#define STATUS_PEG_FAILED    0x003UL
#define STATUS_ECC_ERROR     0x004UL
#define STATUS_ECC_WARNING   0x005UL
#define STATUS_RWW_ERROR     0x006UL
#define STATUS_EDC_ERROR     0x007UL
#define STATUS_ENC_ERROR     0x008UL
#define STATUS_PEP_ERROR     0x009UL
#define STATUS_WDG_ERROR     0x00AUL
#define STATUS_RE_ERROR      0x00BUL

#define FLASH_ECC_CHECK             0x3UL
#define FLASH_SBC_CHECK             0x4UL
#define FLASH_RWW_CHECK             0x5UL
#define FLASH_EDC_CHECK             0x6UL
#define FLASH_PEG_CHECK             0x7UL
#define FLASH_PEP_CHECK             0x8UL
#define FLASH_RE_CHECK              0x9UL
#define FLASH_NVR_TIMEOUT_CHECK     0xAUL
#define FLASH_PES_CHECK             0xBUL
#define FLASH_NVR_LOCK_CHECK        0xCUL

#define FLASH_PRGM_SIZE1     2UL
#define FLASH_PRGM_SIZE2     4UL
#define FLASH_PRGM_SIZE3     6UL
#define FLASH_PRGM_SIZE4     8UL
#define FLASH_PRGM_SIZE5     10UL
#define FLASH_PRGM_SIZE6     12UL
#define FLASH_PRGM_SIZE7     14UL
#define FLASH_PRGM_SIZE8     16UL
#define FLASH_PRGM_SIZE9     18UL
#define FLASH_PRGM_SIZE10    20UL
#define FLASH_PRGM_SIZE11    22UL
#define FLASH_PRGM_SIZE12    24UL
#define FLASH_PRGM_SIZE13    26UL
#define FLASH_PRGM_SIZE14    28UL
#define FLASH_PRGM_SIZE15    30UL
#define FLASH_PRGM_SIZE16    32UL

#define FLASH_WAIT_SELECT1    1UL
#define FLASH_WAIT_SELECT2    2UL
#define FLASH_WAIT_SELECT3    3UL
#define FLASH_WAIT_SELECT4    4UL
#define FLASH_WAIT_SELECT5    5UL
#define FLASH_WAIT_SELECT6    6UL
#define FLASH_WAIT_SELECT7    7UL
#define FLASH_WAIT_SELECT8    8UL

#define FLASH_MARGIN_LEVEL0    0UL
#define FLASH_MARGIN_LEVEL1    1UL

#define FLASH_WDG_TIMEOUT_SELECT0    0UL
#define FLASH_WDG_TIMEOUT_SELECT1    1UL
#define FLASH_WDG_TIMEOUT_SELECT2    2UL
#define FLASH_WDG_TIMEOUT_SELECT3    3UL

#define FLASH_WDG_ENABLE     0UL
#define FLASH_WDG_DISABLE    1UL

#define FLASH_WDG_INT_ENABLE     1UL
#define FLASH_WDG_INT_DISABLE    0UL

#define WDG_TUNE_DISABLE    0x1UL
#define WDG_TUNE_ENABLE     0x0UL

#define FLASH_BUF_PREF_DISABLE    0x0UL
#define FLASH_BUF_PREF_ENABLE     0x1UL

#define FLASH_READ_WAIT_LOCK_DISABLE    0x0UL
#define FLASH_READ_WAIT_LOCK_ENABLE     0x1UL

#define FLASH_AUTO_HOLD_DISABLE       0x0UL
#define FLASH_AUTO_HOLD_ENABLE        0x1UL

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
} FLASH_ROM_API_ENTRY_T;

#endif
