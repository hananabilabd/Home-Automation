/*
 * SPI_Master_H_file.h
 *
 * Created: 7/1/2019 6:35:03 PM
 *  Author: Z.50
 */ 


#ifndef SPI_MASTER_H_FILE_H_
#define SPI_MASTER_H_FILE_H_

#include <avr/io.h>							/* Include AVR std. library file */

#define MOSI 5								/* Define SPI bus pins */
#define MISO 6
#define SCK 7
#define SS 4
#define SS_Enable PORTB &= ~(1<<SS)			/* Define Slave enable */
#define SS_Disable PORTB |= (1<<SS)			/* Define Slave disable */

void SPI_Init();							/* SPI initialize function */
void SPI_Write(char);						/* SPI write data function */
char SPI_Read();							/* SPI read data function */

#endif /* SPI_MASTER_H_FILE_H_ */