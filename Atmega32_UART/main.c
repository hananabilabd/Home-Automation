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
#include "UART.h"
// This assignment is to make a LDR controlling a Led in an inversely manner
int main(void)
{
	u8 arr []="Hannon";
	u8 a []="han";

	int i =0;
	UART_INIT();
	//DIO_SetPinDirection('D',7,1);
	//DIO_SetPinValue('D',7,1);
	u8 Data;
	while (1){
		//Data = UART_ReceiveData();
		//Data = UART_Check_ReceivedString(a);


			UART_TransmitData(0);
			UART_TransmitData(1);



		/*
		 if (Data==1){
			DIO_SetPinValue('D',7,1);
		}*/

	}
	return 0;
}

