/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOOT_MANAGER_H
#define __BOOT_MANAGER_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "AES.h"
#include "keros_aes_manager.h"
#include "w25qxx_Handler.h"
#include "stm32f4xx_flash.h"
#include <string.h>
/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);
typedef struct
{
    uint32_t u32_App_RunState;
    uint32_t u32_App_RunState_Anti;

    uint32_t u32_App_AreaASize;
    uint32_t u32_App_AreaASize_Anti;

    uint32_t u32_App_AreaBState;
    uint32_t u32_App_AreaBState_Anti;

    uint32_t u32_App_AreaBSize;
    uint32_t u32_App_AreaBSize_Anti;
}st_App_Info_t;

typedef enum
{
    App_RunState = 0,
    App_AreaASize,
    App_AreaBState,
    App_AreaBSize
}en_App_FlagType_t;

typedef enum
{
    APP_WAIT_UPDATE = 0x11111111,
    APP_Check_NewApp = 0x22222222,
    APP_AreaAToAreaB = 0x33333333,
    APP_Valid = 0x44444444,
    APP_AreaBState_Valid = 0x55555555,
}en_App_State_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define ApplicationAddress          0x800C000
#define AppFlagAddress              0x8008000
#define NVIC_VectTab_FLASH          ((uint32_t)0x08000000)
#define BOOT_MANAGER_APP_INFO_ADDR  0x08008000
#define BOOT_FLAGRESULT             0xFFFFFFFF
#define MAXAPP_SIZE                 464 * 1024              //app大小最大464kb
/* Exported functions ------------------------------------------------------- */
void BootManager_JumpToApp(void);
int8_t CheckAppValid(int32_t fl_size);
int8_t BootManager_BackToApp(uint8_t u8_block_index);
int8_t InitAESKeyAndIV(void);
int8_t EraseAppFlashSectors(uint32_t app_size);
void BootManager_BootDownload(void);
void Boot_Manager_State(void);
#endif /* __BOOT_MANAGER_H */

