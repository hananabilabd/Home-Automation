/*
 * Keypad.c
 *
 *  Created on: Mar 9, 2018
 *      Author: Hanna Nabil
 */
#include "typedef.h"
#include "IO.h"
#include "macros.h"

#define F_CPU 12000000UL
#include <util/delay.h>
#include "Keypad_config.h"
#include "DIO.h"
#include "Keypad.h"
void Keypad_Init(void){
	DIO_SetPinDirection(Keypad_port,R0,0);
	DIO_SetPinValue(Keypad_port,R0,1);
	DIO_SetPinDirection(Keypad_port,R1,0);
	DIO_SetPinValue(Keypad_port,R1,1);
	DIO_SetPinDirection(Keypad_port,R2,0);
	DIO_SetPinValue(Keypad_port,R2,1);
	DIO_SetPinDirection(Keypad_port,R3,0);
	DIO_SetPinValue(Keypad_port,R3,1);

	DIO_SetPinDirection(Keypad_port,C0,1);
	DIO_SetPinDirection(Keypad_port,C1,1);
	DIO_SetPinDirection(Keypad_port,C2,1);
	DIO_SetPinDirection(Keypad_port,C3,1);
}

u8 Keypad_GetButtonSatus (u8 Button_Num)
{
	u8 value =0;
	const u8 Real_row[]={R0,R1,R2,R3};
	const u8 Real_col[]={C0,C1,C2,C3};
	u8 row =Button_Num /4 ;
	u8 col = Button_Num % 4 ;
	// Throw High on all  of them
	DIO_SetPinValue(Keypad_port,C0,1);
	DIO_SetPinValue(Keypad_port,C1,1);
	DIO_SetPinValue(Keypad_port,C2,1);
	DIO_SetPinValue(Keypad_port,C3,1);

	// Then Throw low on the specific Pin Which in the column i want to read
	DIO_SetPinValue(Keypad_port,Real_col[col],0);

	u8 x= DIO_ReadPinValue(Keypad_port,Real_row[row]);
	if (x==0)
	{
		_delay_ms(100);
		u8 x= DIO_ReadPinValue(Keypad_port,Real_row[row]);
		if (x==0)
		{
			value =1; // Key is Pressed
		}
	}
	return value;
}

