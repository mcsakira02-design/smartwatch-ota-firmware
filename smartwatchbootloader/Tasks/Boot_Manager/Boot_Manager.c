#include "Boot_Manager.h"
#include "main.h"
#include "Flash.h"
#include "elog.h"
#include "common.h"
#include "w25qxx.h"
#include "Iwdg.h"
/*上电跳转标志位，这样软复位的时候不会被清除*/
uint32_t  g_JumpInit __attribute__((at(0x2001FFF0)));

/* AES decryption variables */
uint8_t aes_key[32];           // AES-256 key (32 bytes)
uint8_t aes_iv[16];            // AES IV vector (16 bytes)
uint8_t read_buffer[4096];     // 4K read buffer for external flash

/* App upgrade constants */
#define APP_START_ADDRESS   (0x800C000)  // App start address
#define FLASH_SECTOR_SIZE   (4096)       // Flash sector size: 4KB

/* Global variables for firmware upgrade */
int32_t fil_size = 0;         // File size received from Ymodem
uint8_t au8_test[4096];       // Test buffer for Ymodem
uint8_t flash_erase_state = 0; // Flash erase operation result

st_App_Info_t AppInfo;
/* Function implementations --------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//static uint32_t s_jump_address;
/**
 * @brief  Jump to application program
 * @param  None
 * @retval None
 */
static void SetAppFlagValue(en_App_FlagType_t AppFlagType, uint32_t AppFlagValue)
{
    /* 根据类型写入数据 */
    switch(AppFlagType)
    {
        case App_RunState:
            AppInfo.u32_App_RunState = AppFlagValue;
            AppInfo.u32_App_RunState_Anti = ~AppFlagValue;
            break;
        case App_AreaASize:
            AppInfo.u32_App_AreaASize = AppFlagValue;
            AppInfo.u32_App_AreaASize_Anti = ~AppFlagValue;
            break;
        case App_AreaBState:
            AppInfo.u32_App_AreaBState = AppFlagValue;
            AppInfo.u32_App_AreaBState_Anti = ~AppFlagValue;
            break;
        case App_AreaBSize:
            AppInfo.u32_App_AreaBSize = AppFlagValue;
            AppInfo.u32_App_AreaBSize_Anti = ~AppFlagValue;
            break;
        default:
            break;
    }
    /*先擦除再写入*/
    flash_erase_state = Flash_erase(AppFlagAddress,sizeof(st_App_Info_t));
    if(flash_erase_state != 0)
    {
        log_e("Flash erase failed");
        return;
    }
    for(uint8_t i = 0; i < sizeof(st_App_Info_t); i += 4)
    {
        Flash_Write(AppFlagAddress + i, *(uint32_t *)((uint8_t *)(&AppInfo) + i));
    }
}

/**
 * @brief  Read App Flag Value
 * @param  AppFlagType: App Flag Type
 * @param  AppFlagValue: App Flag Value
 * @retval uint8_t: 0: Success, 1: Failed
 */
static uint8_t ReadAppFlagValue(en_App_FlagType_t AppFlagType, uint32_t *p_u32_AppFlagValue)
{
    uint8_t u8_result = 1;
    /* 先回读所有数据 */
    
    memcpy(&AppInfo, (uint8_t *)BOOT_MANAGER_APP_INFO_ADDR, sizeof(st_App_Info_t));
    /* 根据类型读取数据 */
    switch(AppFlagType)
    {
        case App_RunState:
            if(AppInfo.u32_App_RunState == ~AppInfo.u32_App_RunState_Anti)
            {
                *p_u32_AppFlagValue = AppInfo.u32_App_RunState;
                u8_result = 0;
            }
            break;
        case App_AreaASize:
            if(AppInfo.u32_App_AreaASize == ~AppInfo.u32_App_AreaASize_Anti)
            {
                *p_u32_AppFlagValue = AppInfo.u32_App_AreaASize;
                u8_result = 0;
            }
            break;
        case App_AreaBState:
            if(AppInfo.u32_App_AreaBState == ~AppInfo.u32_App_AreaBState_Anti)
            {
                *p_u32_AppFlagValue = AppInfo.u32_App_AreaBState;
                u8_result = 0;
            }
            break;
        case App_AreaBSize:
            if(AppInfo.u32_App_AreaBSize == ~AppInfo.u32_App_AreaBSize_Anti)
            {
                *p_u32_AppFlagValue = AppInfo.u32_App_AreaBSize;
                u8_result = 0;
            }
            break;
        default:
			/*No Action*/
            break;
    }
	return u8_result;
}

/**
 * @brief  Jump to application program
 * @param  None
 * @retval None
 */
void BootManager_JumpToApp(void)
{
    uint32_t local_jump_address;
    pFunction jump_to_application;
    uint32_t stack_top_address;
    uint32_t app_flagvalue = 0;
    memcpy(&AppInfo, (uint8_t *)BOOT_MANAGER_APP_INFO_ADDR, sizeof(st_App_Info_t));
    if(0x55AA55AA == g_JumpInit)    //软件复位之后
    {
        g_JumpInit = 0xFFFFFFFF;
        IWDG_Init(IWDG_Prescaler_64,3000);
        stack_top_address = (*(__IO uint32_t *)ApplicationAddress);
        if ((stack_top_address & 0x2FFE0000U) == 0x20000000U)
        {
            /* Disable all interrupts to prevent interference during jump */
            __disable_irq();
            NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xC000U);
            RCC_DeInit();
            
            /* Get program start address (reset address) from second word */
            local_jump_address = *(__IO uint32_t *)(ApplicationAddress + 4U);

            /* Initialize user application's Stack Pointer */
            __set_MSP(*(__IO uint32_t *)ApplicationAddress);

            /* Type conversion */
            jump_to_application = (pFunction)local_jump_address;

            /* Jump to application */
            jump_to_application();
        }
    }
    else if((ReadAppFlagValue(App_RunState, &app_flagvalue) == 0) && \
		(app_flagvalue == APP_Valid)) //冷启动
    {
        /* Check if stack top address is valid */
        stack_top_address = (*(__IO uint32_t *)ApplicationAddress);
        if ((stack_top_address & 0x2FFE0000U) == 0x20000000U)
        {
            /* Disable all interrupts to prevent interference during jump */
            __disable_irq();
            NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xC000U);
            RCC_DeInit();
            
            /* Get program start address (reset address) from second word */
            local_jump_address = *(__IO uint32_t *)(ApplicationAddress + 4U);

            /* Initialize user application's Stack Pointer */
            __set_MSP(*(__IO uint32_t *)ApplicationAddress);

            /* Type conversion */
            jump_to_application = (pFunction)local_jump_address;

            /* Jump to application */
            jump_to_application();
        }
        else
        {

            log_e("Invalid stack top address");
        }
    }
    else
    {
        log_e("App validation failed");
    }
}

/* Private variables ---------------------------------------------------------*/
int32_t g_app_size = 0;

/**
 * @brief  Restore firmware from external flash to application area
 * @param  fl_size: Firmware size
 * @retval 0: Success, -1: Error
 */
int8_t CheckAppValid(int32_t fl_size)
{
    /* Parameter validation */
    if (fl_size <= 0)
    {
        return -1;
    }
    
    /* Validate app size range */
    if ((fl_size > (MAX_APP_SIZE - 1)) || (fl_size < 0))
    {
        return -1;
    }
    
    /* Check if App area has valid data by reading the stack pointer */
    uint32_t stack_top_address = (*(__IO uint32_t *)ApplicationAddress);
    
    /* Basic validation: stack pointer should be in valid RAM range */
    if ((stack_top_address & 0x2FFE0000U) != 0x20000000U)
    {
        return -1;
    }
    
    /* App validation successful */
    return 0;
}

/**
 * @brief Initialize AES key and IV from Keros chip
 * @retval 0: Success, 1: Failed
 */
int8_t InitAESKeyAndIV(void)
{
    // Initialize Keros AES manager
    if (keros_aes_init() != 0) {
        log_e("Keros AES init failed");
        return 1;
    }
    
    // Read AES key and IV from Keros chip
    if (keros_aes_read_key_vector(aes_key, aes_iv) != 0) {
        log_e("Read AES key and IV failed");
        return 1;
    }
    
    log_i("AES key and IV initialized successfully");
    return 0;
}

/**
 * @brief Erase app flash sectors
 * @param app_size: Application size in bytes
 * @retval 0: Success, 1: Failed
 */
int8_t EraseAppFlashSectors(uint32_t app_size)
{
    uint32_t sector_count = (app_size + FLASH_SECTOR_SIZE - 1) / FLASH_SECTOR_SIZE;
    uint32_t start_address = APP_START_ADDRESS;
    
    log_i("Erasing %d sectors starting from 0x%08X", sector_count, start_address);
    
    for (uint32_t i = 0; i < sector_count; i++) {
        // Unlock flash for erase operation
        FLASH_Unlock();
        
        // Erase sector
        FLASH_Status status = FLASH_EraseSector(FLASH_Sector_3 + i, VoltageRange_3);
        
        // Lock flash after operation
        FLASH_Lock();
        
        if (status != FLASH_COMPLETE) {
            log_e("Flash erase failed at sector %d, status: %d", i, status);
            return 1;
        }
    }
    
    log_i("Flash sectors erased successfully");
    return 0;
}

/**
 * @brief Read data from external flash, decrypt and write to app area
 * @retval 0: Success, 1: Failed
 */
int8_t BootManager_BackToApp(uint8_t u8_block_index)
{
    uint8_t temp_block[16];              // 原密文数据缓存
    uint8_t write_time = 0;              // 一个解析包写入次数
    uint16_t read_time = 0, read_data_count = 0;  // 读取数据再解密的次数（每次解密16个字节）
    uint32_t app_size = 0;               // 升级包的大小
    uint16_t read_memory_size = 0;
    uint32_t read_memory_index = 0;
    uint32_t ram_source = 0;
    uint32_t app_run_flash_destination = APP_START_ADDRESS;
    
    log_i("Starting BootManager_BackToApp process");
    
    // 先读一帧，用来解析头文件格式
    if (W25Q64_ReadData(u8_block_index, read_buffer, &read_memory_size) != 0) {
        log_e("Failed to read first frame from external flash");
        return 1;
    }

    if (read_memory_size >= 16) {
        memcpy(temp_block, read_buffer, 16);
        // 解析得到自定义内容+文件大小
        Aes_IV_key256bit_Decode(aes_iv, temp_block, aes_key);
        app_size = (temp_block[15] << 24) + (temp_block[14] << 16) + (temp_block[13] << 8) + temp_block[12];
        log_i("AppSize=%d", app_size);
        
        // Validate app size
        if (app_size <= 0) {
            log_e("Invalid app size: %d", app_size);
            return 1;
        }

        if (app_size > MAX_APP_SIZE) {
            log_e("App size too large: %d bytes (max: %d bytes)", app_size, MAX_APP_SIZE);
            return 1;
        }
        
        // 计算升级包读取次数
        read_data_count = app_size / 16;
        if (app_size % 16 != 0) {
            read_data_count += 1;
        }
        read_memory_index += 16;
    } else {
        log_e("Read memory size too small: %d", read_memory_size);
        return 1;
    }
    
    // 数据帧
    // 将待写入区的内容擦除
    uint8_t flash_erase_state = Flash_erase(ApplicationAddress,app_size);
    if(flash_erase_state != 0)
    {
        log_e("Flash erase failed");
        return 1;
    }

    log_i("Starting decryption and flash write process, total blocks: %d", read_data_count);
    
    for (read_time = 0; read_time < read_data_count; read_time++) {
        // 判断下当前buffer下的数据是否读取完毕
        if (read_memory_index == read_memory_size) {
            if (W25Q64_ReadData(u8_block_index,read_buffer, &read_memory_size) != 0) {
                log_e("Read extern buffer error at block %d", read_time);
                return 1;
            }
            read_memory_index = 0;
        }
        
        // 拷贝16个数据
        memcpy(temp_block, read_buffer + read_memory_index, 16);
        read_memory_index += 16;
        
        // 解析16个数据
        Aes_IV_key256bit_Decode(aes_iv, temp_block, aes_key);
        
        // 写入Flash，每16字节解密数据按4字节为单位写入
        ram_source = (uint32_t)temp_block;
        FLASH_Unlock();
        
        for (write_time = 0; write_time < 4; write_time++) {
            uint32_t word_data = *(uint32_t*)ram_source;
            FLASH_Status status = FLASH_ProgramWord(app_run_flash_destination, word_data);
            if (status != FLASH_COMPLETE) {
                FLASH_Lock();
                log_e("Flash programming failed at address 0x%08X, status: %d, word: 0x%08X", 
                      app_run_flash_destination, status, word_data);
                return 1;
            }
            app_run_flash_destination += 4;
            ram_source += 4;
        }
        
        FLASH_Lock();
        
        // Progress logging every 100 blocks or at completion
        if ((read_time + 1) % 100 == 0 || read_time + 1 == read_data_count) {
            uint32_t progress = ((read_time + 1) * 100) / read_data_count;
            log_i("Progress: %d%% (%d/%d blocks processed)", progress, read_time + 1, read_data_count);
        }
    }
    log_i("BootManager_BackToApp process completed successfully");
    return 0;
}


/**
 * @brief Read data from external flash, decrypt and write to app area
 * @retval 0: Success, 1: Failed
 */
void BootManager_BootDownload(void)
{
    /*1.直接下载到App区*/
    fil_size = Ymodem_Receive(au8_test);
    /*2.执行解密搬运操作*/
    if((0 == BootManager_BackToApp(BLOCKA))&&(fil_size > 0))
    {
        log_a("Decryption and transfer completed successfully");
        /*3.验证App区数据有效性*/
        if(0 == CheckAppValid(fil_size))
        {
            log_a("App validation success!");
            SetAppFlagValue(App_AreaASize, fil_size);
            SetAppFlagValue(App_AreaBSize, fil_size);
            SetAppFlagValue(App_AreaBState, APP_AreaBState_Valid);
            //SetAppFlagValue(App_RunState, APP_Valid);
			
            /*4.跳转App*/
            //BootManager_JumpToApp();
            /* 升级成功，设置状态为检查新App*/
            SetAppFlagValue(App_RunState, APP_Check_NewApp);
            /*设置共享变量，上电就跳转*/
            g_JumpInit = 0x55AA55AA;
            //执行软复位
            NVIC_SystemReset();
        }
        else
        {
            log_e("App validation failed after decryption!");
        }
    }
    else
    {
        log_e("Decryption and transfer failed!");
    }
}

/**
 * @brief Read data from external flash, decrypt and write to app area
 * @retval 0: Success, 1: Failed
 */
uint8_t Boot_Manager_AareaToBarea(void)
{
    /*读取A区数据大小并设置*/
    uint32_t fil_size = 0;
	uint16_t tmp_buffer = 0;
    if(1 == ReadAppFlagValue(App_AreaASize,&fil_size))
    {
        return 1;
    }
    SetBlockParmeter(BLOCKA, fil_size);
    uint8_t ret = 0;
    do
    {
        ret = W25Q64_ReadData(BLOCKA, (uint8_t *)&au8_test, &tmp_buffer);
        if(0 == ret)
        {
            W25Q64_WriteData(BLOCKB, (uint8_t *)&au8_test, tmp_buffer);
            break;
        }
        else if(1 == ret)
        {
            //数据读取完毕
            break;
        }
        else
        {
            //数据读取失败
            return 1;
        }
    }
    while(1);
    /*设置B区数据大小*/
    SetAppFlagValue(App_AreaBSize, fil_size);
    return 0;
}

/**
 * @brief Read data from external flash, decrypt and write to app area
 * @retval 0: Success, 1: Failed
 */
uint8_t Boot_Manager_AppWaitUpdate(void)
{
    uint8_t ret = 1;
	uint32_t t_u32_tmp_size = 0;
    //此处处于App应用层端下载的数据，有Bootloader进行下载跳转
    log_i("Waiting for app update...");
    /*1. 读取A区的数据大小并同步到内部w25q结构体中 */
    if(1 == ReadAppFlagValue(App_AreaASize,&t_u32_tmp_size) && \
       (t_u32_tmp_size > MAXAPP_SIZE))
    {
        log_i("App load failed: %d", t_u32_tmp_size);
        //清除状态，直接跳转回App
        return ret;
    }
    SetBlockParmeter(BLOCKA,t_u32_tmp_size);

    /*2. 擦除App运行区域flash ，备份区数据已经存在了，不需要额外刷新*/
    if((0 == BootManager_BackToApp(BLOCKA))&&(t_u32_tmp_size > 0))
    {
        log_a("Decryption and transfer completed successfully");
        /*3.验证App区数据有效性*/
        if(0 == CheckAppValid(t_u32_tmp_size))
        {
            log_a("App validation success!");
            ret = 0;
        }
        else
        {
            /* 校验App无效,需要回溯备份区 */
            return ret;
        }
    }
    else
    {
        /* 验证App区数据无效,需要回溯备份区 */
        return ret;
    }
    /*升级成功，返回正确状态*/
    return ret;
}
/**
 * @brief Read data from external flash, decrypt and write to app area
 * @retval 0: Success, 1: Failed
 */
uint8_t Boot_Manager_Rollback_Backup_Area(void)
{
    /*检查B区数据大小是否有效*/
    uint32_t t_u32_App_AreaBSize = 0;
    if(1 == ReadAppFlagValue(App_AreaBSize,&t_u32_App_AreaBSize) && \
        (t_u32_App_AreaBSize > MAXAPP_SIZE))
    {
        log_i("Rollback App failed: %d");
        return 1;
    }
    /*读备份区B的大小映射到B的内存中*/
    SetBlockParmeter(BLOCKB,t_u32_App_AreaBSize);
    /* 备份区B的数据搬运到App中 */
    if(0 == BootManager_BackToApp(BLOCKB))
    {
        return 0;
    }
    return 1;
}

/**
 * @brief Read data from external flash, decrypt and write to app area
 * @retval void
 */
void Boot_Manager_State(void)
{
    uint32_t t_u32_App_RunState = 0;
    if(1 == ReadAppFlagValue(App_RunState,&t_u32_App_RunState))
    {
        /* 校验App无效,需要重新升级 */
        log_i("App Invalid");
    }
    // Initialize AES key and IV
    if (InitAESKeyAndIV() != 0) {
        log_e("AES initialization failed");
        return;
    }
    /* 读取App运行状态信息 */
    switch(t_u32_App_RunState)
    {
        case APP_WAIT_UPDATE:
            if(1 == Boot_Manager_AppWaitUpdate())
            {
                /*升级失败，回退版本*/
                if(1 == Boot_Manager_Rollback_Backup_Area())
                {
                    /* 清除所有数据状态 */
                    SetAppFlagValue(App_RunState, 0);
                    SetAppFlagValue(App_AreaBSize, 0);
                    SetAppFlagValue(App_AreaBState, 0);
                    SetAppFlagValue(App_AreaASize, 0);
                    //执行软复位
                    NVIC_SystemReset();
                }
                return;
            }
            else
            {
                /* 升级成功，设置状态为检查新App*/
                SetAppFlagValue(App_RunState, APP_Check_NewApp);
                /*设置共享变量，上电就跳转*/
                g_JumpInit = 0x55AA55AA;
                //执行软复位
                NVIC_SystemReset();
            }
            break;
        case APP_Check_NewApp:
            /*一般不会进入这里，进入这里说明上一次升级失败，需要回退版本*/
            if(1 == Boot_Manager_Rollback_Backup_Area())
            {
                /* 清除所有数据状态 */
                SetAppFlagValue(App_RunState, 0);
                SetAppFlagValue(App_AreaBSize, 0);
                SetAppFlagValue(App_AreaBState, 0);
                SetAppFlagValue(App_AreaASize, 0);
                //执行软复位
                NVIC_SystemReset();
            }
            else
            {
                /* 升级成功，进行跳转 */
                SetAppFlagValue(App_RunState, APP_Valid);
                //执行软复位,进行跳转
                NVIC_SystemReset();
            }
            break;
        case APP_AreaAToAreaB:
            //验证成功，保留当前A区的数据搬运到B区
            if(0 == Boot_Manager_AareaToBarea())
            {
                /* 升级成功，设置状态为检查新App*/
                SetAppFlagValue(App_AreaBState,APP_AreaBState_Valid);
                SetAppFlagValue(App_RunState,APP_Valid);
                //执行软复位
                NVIC_SystemReset();
            }
            else
            {
                //备份失败，仍然可以跳转到App，但是下次没有回退功能了
                SetAppFlagValue(App_AreaBState,0);
            }
            
            break;
        case APP_Valid:
            /* 校验App有效,不会进入这个条件 */
        default:
            //log_i("App Invalid");
            /* 检查备份区是否存在有效标识，备份区App是否有效
                如果有效，则把B区数据搬运到App中
                如果无效，则进入升级流程*/
            uint32_t t_u32_App_AreaBState = 0;
            if((1 == ReadAppFlagValue(App_AreaBState,&t_u32_App_AreaBState)) || \
               (t_u32_App_AreaBState == APP_AreaBState_Valid))
            {
                log_i("App load failed: %d", t_u32_App_AreaBState);
                //重新下载数据
                BootManager_BootDownload();
            }
            else
            {
                /*检查B区数据大小是否有效*/
                uint32_t t_u32_App_AreaBSize = 0;
                if(1 == ReadAppFlagValue(App_AreaBSize,&t_u32_App_AreaBSize) || \
                        (t_u32_App_AreaBSize > MAXAPP_SIZE))
                {
                    log_i("App load failed: %d");
                    //重新下载数据
                    BootManager_BootDownload();
                }
                else
                {
                    /*读备份区B的大小映射到B的内存中*/
                    SetBlockParmeter(BLOCKB,t_u32_App_AreaBSize);
                    /* 备份区B的数据搬运到App中 */
                    BootManager_BackToApp(BLOCKB);
                }

            }
            break;
    }
}


