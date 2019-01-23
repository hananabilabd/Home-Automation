/*
 * SPI.c
 *
 *  Created on: Apr 14, 2018
 *      Author: Hanna Nabil
 */
#include "typedef.h"
#include "IO.h"
#include "macros.h"
#include "DIO.h"

#include "SPI.h"

#define MasterOrSlave 'Slave '

void SPI_INIT(void){

	#if MasterOrSlave == 'Master'
		DIO_SetPinDirection('B',7,1);// Clk as output because of Master
		DIO_SetPinDirection('B',4,1);// Slave select
		DIO_SetPinDirection('B',5,1);// MOSI
		DIO_SetPinDirection('B',6,0);// MISO
		SPCR=0b01010001;//Master  , Prescaler = f/16
	#elif MasterOrSlave == 'Slave'

		DIO_SetPinDirection('B',4,0);// Slave select as an Input
		DIO_SetPinDirection('B',5,0);// MOSI
		DIO_SetPinDirection('B',6,1);// MISO
		DIO_SetPinDirection('B',7,0);// Clk as Input because of Slave
		SPCR=0b01000001;// slave  , Prescaler =f/16
	#endif

}
u8 SPI_Transceiver(u8 Data){
	SPDR =Data;
	while (get_bit(SPSR,7)==0);
	return SPDR;

}
