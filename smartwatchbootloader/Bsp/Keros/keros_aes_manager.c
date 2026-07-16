/*****************************************************************************
 * KEROS AES Manager
 *
 * Copyright(C) 2024
 * All rights reserved.
 *
 * File Name    : keros_aes_manager.c
 * Author       : Bootloader Team
 * Version      : V1.0
 * Date         : 2024.12.31
 * Description  : KEROS AES key and vector management for bootloader
 ****************************************************************************/

#include "keros_aes_manager.h"
#include "keros_lib.h"
#include "keros_interface.h"
#include "common.h"
#include "elog.h"
#include <string.h>
#include "keros_i2c_interface.h"

/* Private variables */
static uint8_t g_aes_key[32];     /* AES-256 key storage */
static uint8_t g_aes_vector[16];  /* AES initial vector storage */
static uint8_t g_keros_initialized = 0;

/* Private function prototypes */
static uint8_t calculate_crc8(uint8_t *data, uint8_t len);
static uint8_t verify_aes_data_crc(uint8_t *data);

#define NUM_CHECKDATA 16
/**
 * @brief Calculate CRC8 checksum
 * @param data: Data buffer pointer
 * @param len: Data length
 * @retval CRC8 checksum value
 */
static uint8_t calculate_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0x00;
    uint8_t i, j;
    
    for (i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (j = 0; j < 8; j++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ 0x07;  /* CRC-8 polynomial: x^8 + x^2 + x + 1 */
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

/**
 * @brief Verify AES data CRC checksum
 * @param data: Data buffer containing vector(16) + key(32) + CRC8(1) + CRC8_INV(1)
 * @retval 1: CRC verification passed, 0: CRC verification failed
 */
static uint8_t verify_aes_data_crc(uint8_t *data)
{
    uint8_t calculated_crc8;
    uint8_t crc8_inv;
    
    /* Calculate CRC8 for vector and key (48 bytes) */
    calculated_crc8 = calculate_crc8(data, 48);
    crc8_inv = ~data[48];
    
    /* Verify CRC8 and its inverse */
    if ((calculated_crc8 == data[48]) && (data[49] == crc8_inv))
    {
        return 1;  /* CRC verification passed */
    }
    else
    {
        return 0;  /* CRC verification failed */
    }
}
uint8_t user_keros_authentication_test(void)
{
    uint8_t indata[16];
    uint8_t odata[16];
    uint8_t status;
    
    // 生成随机测试数据
    for (uint8_t i = 0; i < 16; i++) {
        indata[i] = keros_random();
    }
    
    // 执行认证
    status = keros_authentication(SET_AES_KEY_SIZE_256, 0, indata, odata);
    
    if (status != TRUE) {
        //DEBUG_OUT("Authentication failed, status: %d", status);
        return 1;
    }
    
    // 防跳过验证
    for (uint8_t i = NUM_CHECKDATA/2; i < NUM_CHECKDATA; i++) {
        odata[i] = odata[i] ^ indata[NUM_CHECKDATA-1];
    }
    
    for (uint8_t i = 0; i < NUM_CHECKDATA/2; i++) {
        odata[i] = odata[i] ^ indata[0];
    }
    
    // 验证数据
    for (uint8_t i = 0; i < NUM_CHECKDATA; i++) {
        if (indata[i] != odata[i]) {
            //DEBUG_OUT("Data verification failed at index %d", i);
            return 2;
        }
    }
    
//    DEBUG_OUT("Authentication test passed");
    return 0;
}
/**
 * @brief Initialize KEROS AES chip
 * @param None
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_init(void)
{
    uint8_t serial_data[16];
    uint8_t init_status;
    
    if (g_keros_initialized)
    {
        return KEROS_STATUS_OK;  /* Already initialized */
    }
    
    I2CSetInitial();

    /* Power on KEROS chip */
    keros_power_on();
    keros_delay(2);  /* Wait for power stabilization - increased to match EepromData project */
    
    /* Initialize KEROS library */
    init_status = keros_init(serial_data);
    if (init_status != KEROS_STATUS_OK)
    {
        log_e("KEROS initialization failed, error code: %d", init_status);
        return init_status;
    }
    
    g_keros_initialized = 1;
    log_i("KEROS AES chip initialized successfully");
    
    return KEROS_STATUS_OK;
}

/**
 * @brief Read AES key and vector from KEROS EEPROM
 * @param key: Buffer to store AES key (32 bytes)
 * @param vector: Buffer to store AES vector (16 bytes)
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_read_key_vector(uint8_t *key, uint8_t *vector)
{
    uint8_t read_buffer[64];  /* EEPROM page size is 64 bytes */
    uint8_t status;
    uint32_t password = 0x00000000;  /* Default password */
    uint8_t page = 0;  /* Read from page 0 */
    
    if (key == NULL || vector == NULL)
    {
        log_e("Invalid parameter: key or vector is NULL");
        return KEROS_NULL_POINT_EXCEPTION;
    }
    
    /* Ensure KEROS is initialized */
    if (!g_keros_initialized)
    {
        status = keros_aes_init();
        if (status != KEROS_STATUS_OK)
        {
            return status;
        }
    }
    
    /* Perform authentication test before EEPROM access */
    status = keros_aes_authentication_test();
    if (status != KEROS_STATUS_OK)
    {
        log_e("KEROS authentication test failed, error code: %d", status);
        return status;
    }

    /* Read data from EEPROM */
    status = keros_eeprom_read(password, page, read_buffer, REQ_AES_NONE_READ);
    if (status != KEROS_STATUS_OK)
    {
        log_e("Read data from EEPROM failed, error code: %d", status);
        return status;
    }
    
    /* Verify CRC checksum */
    if (!verify_aes_data_crc(read_buffer))
    {
        log_e("EEPROM data CRC verification failed");
        return KEROS_ERROR_AUTHENTICATION;
    }
    
    /* Copy vector and key to output buffers */
    memcpy(vector, read_buffer, 16);      /* First 16 bytes: vector */
    memcpy(key, read_buffer + 16, 32);    /* Next 32 bytes: key */
    
    /* Store in global variables for future use */
    memcpy(g_aes_vector, vector, 16);
    memcpy(g_aes_key, key, 32);
    
    log_i("AES key and vector read successfully from KEROS EEPROM");
    
    return KEROS_STATUS_OK;
}

/**
 * @brief Get cached AES key
 * @param key: Buffer to store AES key (32 bytes)
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_get_key(uint8_t *key)
{
    if (key == NULL)
    {
        return KEROS_NULL_POINT_EXCEPTION;
    }
    
    /* If not cached, read from EEPROM */
    if (!g_keros_initialized)
    {
        uint8_t temp_vector[16];
        return keros_aes_read_key_vector(key, temp_vector);
    }
    
    memcpy(key, g_aes_key, 32);
    return KEROS_STATUS_OK;
}

/**
 * @brief Get cached AES vector
 * @param vector: Buffer to store AES vector (16 bytes)
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_get_vector(uint8_t *vector)
{
    if (vector == NULL)
    {
        return KEROS_NULL_POINT_EXCEPTION;
    }
    
    /* If not cached, read from EEPROM */
    if (!g_keros_initialized)
    {
        uint8_t temp_key[32];
        return keros_aes_read_key_vector(temp_key, vector);
    }
    
    memcpy(vector, g_aes_vector, 16);
    return KEROS_STATUS_OK;
}

/**
 * @brief Test KEROS authentication
 * @param None
 * @retval 0: Success, others: Error code
 */
uint8_t keros_aes_authentication_test(void)
{  
    uint8_t indata[16];
    uint8_t odata[16];
    uint8_t status;
    
    // 生成随机测试数据
    for (uint8_t i = 0; i < 16; i++) {
        indata[i] = keros_random();
    }
    
    // 执行认证
    status = keros_authentication(SET_AES_KEY_SIZE_256, 0, indata, odata);
    
    if (status != TRUE) {
        log_e("Authentication failed, status: %d", status);
        return 1;
    }
    
    // 防跳过验证
    for (uint8_t i = NUM_CHECKDATA/2; i < NUM_CHECKDATA; i++) {
        odata[i] = odata[i] ^ indata[NUM_CHECKDATA-1];
    }
    
    for (uint8_t i = 0; i < NUM_CHECKDATA/2; i++) {
        odata[i] = odata[i] ^ indata[0];
    }
    
    // 验证数据
    for (uint8_t i = 0; i < NUM_CHECKDATA; i++) {
        if (indata[i] != odata[i]) {
            log_e("Data verification failed at index %d", i);
            return 2;
        }
    }
    
    log_e("Authentication test passed");
    return 0;  
    // uint8_t test_data[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    //                          0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    // uint8_t encrypted_data[16];
    // uint8_t decrypted_data[16];
    // uint8_t status;
    
    // /* Ensure KEROS is initialized */
    // if (!g_keros_initialized)
    // {
    //     status = keros_aes_init();
    //     if (status != KEROS_STATUS_OK)
    //     {
    //         return status;
    //     }
    // }
    
    // /* Test encryption */
    // status = keros_req_enc_dec(test_data, encrypted_data, AES_REQ_ENCODING);
    // if (status != KEROS_STATUS_OK)
    // {
    //     log_e("KEROS encryption test failed, error code: %d", status);
    //     return status;
    // }
    
    // /* Test decryption */
    // status = keros_req_enc_dec(encrypted_data, decrypted_data, AES_REQ_DECODING);
    // if (status != KEROS_STATUS_OK)
    // {
    //     log_e("KEROS decryption test failed, error code: %d", status);
    //     return status;
    // }
    
    // /* Verify data integrity */
    // if (memcmp(test_data, decrypted_data, 16) != 0)
    // {
    //     log_e("KEROS authentication test failed: data mismatch");
    //     return KEROS_ERROR_AUTHENTICATION;
    // }
    
    // log_i("KEROS authentication test passed");
    // return KEROS_STATUS_OK;
}
