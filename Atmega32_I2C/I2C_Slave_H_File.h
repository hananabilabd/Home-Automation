/*
 * I2C_Slave_H_File.h
 *
 * Created: 7/1/2019 9:12:20 PM
 *  Author: Z.50
 */ 


#ifndef I2C_SLAVE_H_FILE_H_
#define I2C_SLAVE_H_FILE_H_

#include <avr/io.h>								/* Include AVR std. library file */

void I2C_Slave_Init(uint8_t slave_address);		/* I2C slave initialize function with Slave address */
int8_t I2C_Slave_Listen();						/* I2C slave listen function */
int8_t I2C_Slave_Transmit(char data);			/* I2C slave transmit function */
char I2C_Slave_Receive();						/* I2C slave receive function */

#endif /* I2C_SLAVE_H_FILE_H_ */