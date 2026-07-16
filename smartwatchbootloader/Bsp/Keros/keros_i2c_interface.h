/*****************************************************************************
 * KEROS I2C Bus Driver Header
 *
 *
 * Copyright(C) CHIPSBRAIN GLOBAL CO., Ltd.
 * All rights reserved.
 *
 * File Name    : keros_i2c_interface.h
 * Author       : ARES HA
 *
 * Version      : V0.3
 * Date         : 2015.09.08
 * Description  : Keros I2C Bus Driver
 ****************************************************************************/

#ifndef _I2CBUS_H
#define _I2CBUS_H

/*  Conditional extern definition */
/*  ============================================================================= */
#ifdef   _SOURCE_I2CBUS_
#define  I2C_EXT
#else
#define  I2C_EXT  extern
#endif


#define KEROS_DEVID_ADDR          0x38  /* Address including R/W flag */

/* ****************************************************************************** */
// I2C channel number 0 ~ 3
enum{
	BUS0,
	BUS1,
	BUS2,
	BUS3,
	BUS4,		// external
	BUS_MAX
};


#define ERR_I2C_BUS_DISABLE        		0x01
#define ERR_I2C_NO_ADDRESS_ACK     		0x02
#define ERR_I2C_NO_SUBADDRESS_ACK  	0x04
#define ERR_I2C_NO_DATA_ACK        		0x08

#define MAXATTEMPTS                	3
#define MAX_CLOCKSTRETCHING     5000


I2C_EXT void I2CSetInitial(void);
I2C_EXT void I2CSetEnable(uint8_t cEnable);
I2C_EXT uint8_t I2CGetEnable(void);
I2C_EXT uint8_t I2CWrite (uint8_t bDevAddr, uint8_t *pbAddr, uint8_t wAddrLen, uint8_t *pbData, uint8_t wData);
I2C_EXT uint8_t I2CRead ( uint8_t bDevAddr, uint8_t *pbAddr, uint8_t wAddrLen, uint8_t *pbData, uint8_t wData);
I2C_EXT uint8_t I2CSendDeviceAddress( uint8_t bDevAddr);

/*  only modul internal use: */
I2C_EXT void I2CMasterStop(void);
I2C_EXT void I2CMasterInit(void);
I2C_EXT void I2CMasterStart(void);
I2C_EXT uint8_t I2CMasterWrite( uint8_t bDataByte);
I2C_EXT uint8_t I2CMasterRead(uint8_t bAck);
I2C_EXT uint8_t I2CMasterReceiver(uint8_t cAddr);

#endif
