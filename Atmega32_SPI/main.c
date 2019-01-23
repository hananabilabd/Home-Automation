/*
 * main.c
 *
 *  Created on: Feb 24, 2018
 *      Author: Hanna Nabil
 */

#include "typedef.h"
#include "IO.h"
#include "macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"
#include <avr/interrupt.h>
#include <util/delay.h>
//#include <avr/spi.h>


volatile uint8_t data;

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
  uint8_t data = SPDR;

  if (data == 1){
  			DIO_SetPinValue('D',0,1);// Led on
  			_delay_ms(1000);
  			}
  else if (data == 0){
    				DIO_SetPinValue('D',0,0);
    				_delay_ms(1000);
    			}


}


int main(void)
{

	 DIO_SetPinDirection('D',0,1); // as Output
	    spi_init_slave();                             //Initialize slave SPI

	    sei();//set global interrupt flag

	    //DIO_SetPinValue('D',0,1);




 while (1); // do nothing

}
