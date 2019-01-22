/*
 * UART.h
 *
 *  Created on: Apr 13, 2018
 *      Author: Hanna Nabil
 */

#ifndef UART_H_
#define UART_H_

#define BaudRate 9600
#define Freq 12000000
#define My_BRR  (Freq / 16/ BaudRate -1)

void UART_INIT(void);
void UART_TransmitData(u8 Data);
u8 UART_ReceiveData(void);
void UART_TransmitString(u8 *arr);
u8  UART_Check_ReceivedString(u8 *string);

#endif /* UART_H_ */
