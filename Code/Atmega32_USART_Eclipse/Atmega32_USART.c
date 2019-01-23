/*
 * Atmega32_USART.c
 *
 *  Created on: Jan 22, 2019
 *      Author: Z.50
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

//#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);   /* Turn on the transmission and reception */
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); /* Use 8-bit character sizes */

	UBRRL = BAUD_PRESCALE; 					/* Load lower 8-bits of the baud rate value */
	UBRRH = (BAUD_PRESCALE >> 8);			/*Load upper 8-bits*/
}

unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0); /*Do nothing until data have been received*/
	return(UDR);				/* return the byte*/
}

void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE))); /*Wait for empty transmit buffer*/
	UDR = ch ;
}

void UART_SendString(char *str)
{
	unsigned char j=0;

	while (str[j]!=0)	/*send string up to null */
	{
		UART_TxChar(str[j]);
		j++;
	}
}

int main()
{
	char c;
	UART_init(9600);

	//UART_SendString("\n\t Echo Test ");
	while(1)
	{
		//c=UART_RxChar();
		UART_TxChar(1);
	}
	return 0;
}

