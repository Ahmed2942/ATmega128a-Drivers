/*
 * I2C_Slave_H_File.h
 *
 */ 


#ifndef I2C_SLAVE_H_FILE_H_
#define I2C_SLAVE_H_FILE_H_

#include <avr/io.h>								/* Include AVR std. library file */

void I2C_Slave_Init(u8 slave_address);		/* I2C slave initialize function with Slave address */
u8 I2C_Slave_Listen();						/* I2C slave listen function */
u8 I2C_Slave_Transmit(char data);			/* I2C slave transmit function */
char I2C_Slave_Receive();						/* I2C slave receive function */

#endif /* I2C_SLAVE_H_FILE_H_ */