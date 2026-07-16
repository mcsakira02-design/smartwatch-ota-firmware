/*****************************************************************************
 * KEROS AES Manager Header
 *
 * Copyright(C) 2024
 * All rights reserved.
 *
 * File Name    : keros_aes_manager.h
 * Author       : Bootloader Team
 * Version      : V1.0
 * Date         : 2024.12.31
 * Description  : KEROS AES key and vector management for bootloader
 ****************************************************************************/

#ifndef __KEROS_AES_MANAGER_H_
#define __KEROS_AES_MANAGER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"


#define KEROS_AES_KEY_LENGTH       32
#define KEROS_AES_VECTOR_LENGTH    16
/* Function prototypes */

/**
 * @brief Initialize KEROS AES chip
 * @param None
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_init(void);

/**
 * @brief Read AES key and vector from KEROS EEPROM
 * @param key: Buffer to store AES key (32 bytes)
 * @param vector: Buffer to store AES vector (16 bytes)
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_read_key_vector(uint8_t *key, uint8_t *vector);

/**
 * @brief Get cached AES key
 * @param key: Buffer to store AES key (32 bytes)
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_get_key(uint8_t *key);

/**
 * @brief Get cached AES vector
 * @param vector: Buffer to store AES vector (16 bytes)
 * @retval KEROS_STATUS_OK: Success, others: Error code
 */
uint8_t keros_aes_get_vector(uint8_t *vector);

/**
 * @brief Test KEROS authentication
 * @param None
 * @retval 0: Success, others: Error code
 */
uint8_t keros_aes_authentication_test(void);

#ifdef __cplusplus
}
#endif

#endif /* __KEROS_AES_MANAGER_H_ */
