/*
 * UART.c
 *
 *  Created on: Apr 13, 2018
 *      Author: Hanna Nabil
 */

#include "typedef.h"
#include "IO.h"
#include "macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#include "DIO.h"
#include "UART.h"
#include <stdio.h>
#include <string.h>
/* Rx ==> D0  ==> to be connected with Tx of USB to TTL
 * Tx ==> D1
 *
 */
void UART_INIT(void){
	DIO_SetPinDirection('D',0,0);
	DIO_SetPinDirection('D',1,1);

	set_bit(UCSRB,3);
	set_bit(UCSRB,4);

	//set_bit(UCSRC,7);// by default is set
	set_bit(UCSRC,1);
	set_bit(UCSRC,2);
	UBRRL=78;
	UBRRH=0;


}

void UART_TransmitData(u8 Data){
	while(get_bit(UCSRA,5)==0);
	UDR = Data;
}
u8 UART_ReceiveData(void){
	while(get_bit(UCSRA,7)==0);
	/* Clear Flag */
  set_bit(UCSRA,7);
	return UDR;
}
void UART_TransmitString(u8 *arr){
	u8 counter =0;
		while(arr[counter] != '\0'){ //Null character
			UART_TransmitData(arr[counter]);
			counter ++;
		}
		UART_TransmitData('\n');
}
u8  UART_Check_ReceivedString(u8 *string){
	u8 array[10] ={0};
	u8 counter =0;

	u8 true =1;
	u8 false =0;
		while(UART_ReceiveData() != '\0'){ //Null character
			array[counter]=UART_ReceiveData();
			counter ++;

		}
		int n=memcmp ( string, array, sizeof(string) );
		if (n ==0){return true;}
		else {return false;}

}
