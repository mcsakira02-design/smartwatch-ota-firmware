/**
  ******************************************************************************
  * @file    ymodem.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    10/15/2010
  * @brief   Ymodem protocol implementation for bootloader
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "stm32f4xx_flash.h"
#include "Boot_Manager.h"
#include "Flash.h"
#include "AES.h"
#include "elog.h"
#include "keros_aes_manager.h"
#include "keros_lib.h"
#include <string.h>

/* Private variables ---------------------------------------------------------*/
static uint8_t file_name[FILE_NAME_LENGTH];
// static uint8_t aes_iv[16];   /* AES initial vector - read from KEROS chip */
// static uint8_t aes_key[32];  /* AES key - read from KEROS chip */
// static uint8_t aes_initialized = 0;  /* Flag to indicate if AES key/vector are loaded */

extern int32_t g_app_size;

/* Private function prototypes -----------------------------------------------*/
static int32_t Receive_Byte(uint8_t *c, uint32_t timeout);
static uint32_t Send_Byte(uint8_t c);
static int32_t Receive_Packet(uint8_t *data, int32_t *length, uint32_t timeout);

/**
  * @brief  Receive byte from sender
  * @param  c: Character
  * @param  timeout: Timeout
  * @retval 0: Byte received, -1: Timeout
  */
static int32_t Receive_Byte(uint8_t *c, uint32_t timeout)
{
    while (timeout-- > 0)
    {
        if (SerialKeyPressed(c) == 1)
        {
            return 0;
        }
    }
    return -1;
}

/**
  * @brief  Send a byte
  * @param  c: Character
  * @retval 0: Byte sent
  */
static uint32_t Send_Byte(uint8_t c)
{
    SerialPutChar(c);
    return 0;
}

/**
  * @brief  Receive a packet from sender
  * @param  data: Packet data buffer
  * @param  length: Packet length
  * @param  timeout: Timeout value
  * @retval 0: Normal return, -1: Timeout or packet error, 1: Abort by user
  */
static int32_t Receive_Packet(uint8_t *data, int32_t *length, uint32_t timeout)
{
    uint16_t i, packet_size;
    uint8_t c;
    
    *length = 0;
    if (Receive_Byte(&c, timeout) != 0)
    {
        return -1;
    }
    
    switch (c)
    {
        case SOH:
            packet_size = PACKET_SIZE;
            break;
        case STX:
            packet_size = PACKET_1K_SIZE;
            break;
        case EOT:
            return 0;
        case CA:
            if ((Receive_Byte(&c, timeout) == 0) && (c == CA))
            {
                *length = -1;
                return 0;
            }
            else
            {
                return -1;
            }
        case ABORT1:
        case ABORT2:
            return 1;
        default:
            return -1;
    }
    
    *data = c;
    for (i = 1; i < (packet_size + PACKET_OVERHEAD); i++)
    {
        if (Receive_Byte(data + i, timeout) != 0)
        {
            return -1;
        }
    }
    
    if (data[PACKET_SEQNO_INDEX] != ((data[PACKET_SEQNO_COMP_INDEX] ^ 0xff) & 0xff))
    {
        return -1;
    }
    
    *length = packet_size;
    return 0;
}

/**
  * @brief  Initialize AES keys and vectors from KEROS chip
  * @param  None
  * @retval 0: Success, -1: Error
  */
//static int32_t Initialize_AES_Keys(void)
//{
//    uint8_t status;
//    
//    if (aes_initialized)
//    {
//        return 0;  /* Already initialized */
//    }
//    
//    /* Initialize KEROS AES chip */
//    status = keros_aes_init();
//    if (status != KEROS_STATUS_OK)
//    {
//        log_e("KEROS AES chip initialization failed, error code: %d", status);
//        return -1;
//    }
//    
//    /* Read AES key and vector from KEROS EEPROM */
//    status = keros_aes_read_key_vector(aes_key, aes_iv);
//    if (status != KEROS_STATUS_OK)
//    {
//        log_e("Failed to read AES key and vector from KEROS, error code: %d", status);
//        return -1;
//    }
//    
//    /* Perform authentication test */
//    status = keros_aes_authentication_test();
//    if (status != KEROS_STATUS_OK)
//    {
//        log_e("KEROS authentication test failed, error code: %d", status);
//        return -1;
//    }
//    
//    aes_initialized = 1;
//    log_i("AES keys and vectors initialized successfully from KEROS chip");
//    
//    return 0;
//}

uint8_t packet_data[PACKET_1K_SIZE + PACKET_OVERHEAD];
uint8_t file_size[FILE_SIZE_LENGTH];
uint8_t *file_ptr, *buf_ptr;
int32_t i, packet_length, session_done, file_done, packets_received, errors, session_begin, size = 0;
/**
  * @brief  Receive a file using the ymodem protocol
  * @param  buf: Address of the first byte
  * @retval The size of the file
  *//**
  * @brief  使用Ymodem协议接收文件
  * @param  buf: 数据缓冲区指针，用于存储接收到的数据
  * @retval 接收到的文件大小，负值表示出现错误
  *         -1: 文件大小超过Flash容量
  *         -3: 用户中止传输
  *         0: 传输正常结束或其他错误
  *         正值: 接收到的文件大小
  */
int32_t Ymodem_Receive(uint8_t *buf)
{
    /* 主循环，处理整个Ymodem会话 */
    for (session_done = 0, errors = 0, session_begin = 0; ;)
    {
        /* 内层循环，处理单个文件传输 */
        for (packets_received = 0, file_done = 0, buf_ptr = buf; ;)
        {
            /* 接收数据包 */
            switch (Receive_Packet(packet_data, &packet_length, NAK_TIMEOUT))
            {
                case 0:
                    /* 成功接收到数据包，重置错误计数 */
                    errors = 0;
                    switch (packet_length)
                    {
                        /* Abort by sender */
                        case -1:
                            Send_Byte(ACK);
                            return 0;
                        /* End of transmission */
                        case 0:
                            Send_Byte(ACK);
                            file_done = 1;
                            break;
                        /* Normal packet */
                        default:
                            /* 检查包序列号是否正确 */
                            if ((packet_data[PACKET_SEQNO_INDEX] & 0xff) != (packets_received & 0xff))
                            {
                                Send_Byte(NAK);
                            }
                            else
                            {
                                /* 处理第一个包（文件名包） */
                                if (packets_received == 0)
                                {
                                    /* Filename packet */
                                    if (packet_data[PACKET_HEADER] != 0)
                                    {
                                        /* Filename packet has valid data */
                                        /* 提取文件名 */
                                        for (i = 0, file_ptr = packet_data + PACKET_HEADER; (*file_ptr != 0) && (i < FILE_NAME_LENGTH);)
                                        {
                                            file_name[i++] = *file_ptr++;
                                        }
                                        file_name[i++] = '\0';
                                        
										log_d("file name = %s", file_name);
                                        /* 提取文件大小 */
                                        for (i = 0, file_ptr++; (*file_ptr != ' ') && (i < FILE_SIZE_LENGTH);)
                                        {
                                            file_size[i++] = *file_ptr++;
                                        }
                                        file_size[i++] = '\0';
                                        
                                        Str2Int(file_size, &size);
                                        g_app_size = size;
                                        
                                        /* 检查文件大小是否超出Flash容量 */
                                        if (size > (FLASH_SIZE - 1))
                                        {
                                            /* End session */
                                            Send_Byte(CA);
                                            Send_Byte(CA);
                                            return -1;
                                        }

                                        Send_Byte(ACK);
                                        Send_Byte(CRC16);
                                    }
                                    /* 文件名包为空，结束会话 */
                                    else
                                    {
                                        Send_Byte(ACK);
                                        file_done = 1;
                                        session_done = 1;
                                        break;
                                    }
                                }
                                /* 处理数据包 */
                                else
                                {
                                    // 直接将接收到的数据写入外部flash，无需解密和搬运到内部flash
                                    memcpy(buf_ptr, packet_data + PACKET_HEADER, packet_length);
                                    // 写入外部flash（W25Q64），假设写入地址和长度由buf_ptr和packet_length决定
                                    if (W25Q64_WriteData(BLOCKA,buf_ptr, packet_length) != 0)
                                    {
                                        log_e("W25Q64_WriteData failed");
                                        Send_Byte(CA);
                                        Send_Byte(CA);
                                        return -1;
                                    }
                                    Send_Byte(ACK);
                                }
                                packets_received++;
                                session_begin = 1;
                            }
                    }
                    break;
                case 1:
                    /* 用户中止传输 */
                    Send_Byte(CA);
                    Send_Byte(CA);
                    return -3;
                default:
                    /* 处理接收错误 */
                    if (session_begin > 0)
                    {
                        errors++;
                    }
                    if (errors > MAX_ERRORS)
                    {
                        Send_Byte(CA);
                        Send_Byte(CA);
                        return 0;
                    }
                    Send_Byte(CRC16);
                    break;
            }
            /* 检查文件是否传输完成 */
            if (file_done != 0)
            {
                break;
            }
        }
        /* 检查会话是否完成 */
        if (session_done != 0)
        {
            break;
        }
    }
    //正确退出逻辑，会执行一次剩余数据写入逻辑
    W25Q64_WriteData_End(BLOCKA);
    /* 返回从第一个数据包解密得到的实际App大小 */
    return (int32_t)size;
}

