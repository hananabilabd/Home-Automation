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
#define Slave_Address			0x20

#include "I2C_Slave_H_File.h"

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

void delay2(u32 Counter)
{
	for (u32 i=0 ; i<Counter;i++){
				asm("NOP");
				asm("NOP");
				asm("NOP");
				asm("NOP");
				asm("NOP");
				asm("NOP");
			}
}
u8 count = 0;
int main(void)
{

	I2C_Slave_Init(Slave_Address);

	DIO_SetPinDirection('C',7,1); // as Output
	DIO_SetPinDirection('C',6,1);
	UART_INIT();
	spi_init_slave();                             //Initialize slave SPI
	sei();//set global interrupt flag


	while (1){
		UART_TransmitData(data);

		switch(I2C_Slave_Listen())				/* Check for any SLA+W or SLA+R */
		{
		case 0:
		{
			do
			{
				count = I2C_Slave_Receive();/* Receive data byte*/
				if (count==0){DIO_SetPinValue('C',6,1);// Led off
				delay2(50000);
				}
				else if (count==1){DIO_SetPinValue('C',6,1);// Led on
				delay2(50000);
				}

			} while (count != -1);			/* Receive until STOP/REPEATED START received */
			break;
		}
		case 1:
		{
			int8_t Ack_status;

			do
			{
				DIO_SetPinValue('C',6,0);// Led on
				Ack_status = I2C_Slave_Transmit(1);	/* Send data byte */
				DIO_SetPinValue('C',6,1);// Led on

			} while (Ack_status == 0 || Ack_status == -1 || Ack_status == -2 );		/* Send until N Acknowledgment is received */
			break;
		}
		default:
			break;
		}

	}

}
