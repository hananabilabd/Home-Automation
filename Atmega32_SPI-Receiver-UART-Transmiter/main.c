/*
 * main.c
 *
 *  Created on: Feb 24, 2018
 *      Author: Hanna Nabil
 */

#include "typedef.h"
#include "IO.h"
#include "macros.h"
#define F_CPU 12000000UL
#include <util/delay.h>
#include "DIO.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART.h"
//#include <avr/spi.h>
//#include<inttypes.h>

volatile u8 data;

void spi_init_slave (void)
{
	DIO_SetPinDirection('B',4,0);// Slave select as an Input
	DIO_SetPinDirection('B',5,0);// MOSI
	DIO_SetPinDirection('B',6,1);// MISO
	DIO_SetPinDirection('B',7,0);// Clk as Input because of Slave (SCK)
	//SPCR=0b11000000;// slave  , Prescaler =f/4 ,interrupt
	SPCR=(1<<SPE)|(1<<SPIE);       //Enable SPI && interrupt enable bit
	SPDR=0;
}


ISR(SPI_STC_vect)
{
	data = SPDR;

	if (data == 1){
		DIO_SetPinValue('C',7,1);// Led on
		_delay_ms(100);
	}
	else if (data == 0){
		DIO_SetPinValue('C',7,0);
		_delay_ms(100);
	}


}


int main(void)
{
	UART_INIT();
	DIO_SetPinDirection('C',7,1); // as Output
	spi_init_slave();                             //Initialize slave SPI

	sei();//set global interrupt flag


	while (1){
		UART_TransmitData(data);
		//UART_TransmitData(1);
	}

}
