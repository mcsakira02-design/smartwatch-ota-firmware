/*****************************************************************************
 * KEROS Interface driver
 *
 *
 * Copyright(C) CHIPSBRAIN GLOBAL CO., Ltd.
 * All rights reserved.
 *
 * File Name    : keros_interface.c
 * Author       : ARES HA
 *
 * Version      : V0.3
 * Date         : 2015.09.08
 * Description  : Keros Interface Source
 ****************************************************************************/

/* USER INCLUDE BEGIN */

#include "stm32f4xx.h"
#include "common.h"

/* USER INCLUDE END  */

#include "keros_lib.h"
#include "keros_i2c_interface.h"
#include "keros_interface.h"

/* External function declarations */
extern void Delay(__IO uint32_t nTime);


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/
/* USER CODE BEGIN  */

uint8_t keros_read_data( uint16_t sub_addr, int read_len, uint8_t * r_data )
{
		uint8_t bSubAddress[2];

		bSubAddress[0] = sub_addr>>8;
		bSubAddress[1] = sub_addr & 0xff;

		return I2CRead(KEROS_DEVID_ADDR,bSubAddress,2,r_data,read_len);
}

uint8_t keros_write_data( uint16_t sub_addr, uint8_t * w_data, int write_len )
{
		uint8_t bSubAddress[2];

		bSubAddress[0] = sub_addr>>8;
		bSubAddress[1] = sub_addr & 0xff;

		return I2CWrite(KEROS_DEVID_ADDR,bSubAddress,2,w_data,write_len);
}

// 1ms
void keros_delay ( uint32_t wait_time )
{
		Delay(wait_time);
}

uint8_t keros_power_on( void )
{
	uint8_t Data = 0xF0;
	
	I2CMasterStart();
    	I2CMasterWrite(0x38);
	I2CMasterStart();
    	I2CMasterWrite(0x38);
	

	return I2CWrite(KEROS_DEVID_ADDR,NULL,0,&Data,1);	// Power ON
}
/* USER CODE END  */


