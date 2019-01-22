/*
 * DIO.c
 *
 *  Created on: Feb 23, 2018
 *      Author: Hanna Nabil
 */


#include "typedef.h"
#include "IO.h"
#include "macros.h"
#include "DIO.h"
//#include "DIO.h"
void DIO_setPortDirection(u8 port_name,u8 value){ // Functions that deals with an entire register and determine it's direction
	switch(port_name){

	case 'A' :
		DDRA =value;
		break;
	case 'B' :
		DDRB=value;
		break;
	case 'C' :
		DDRC =value;
		break;
	case 'D' :
		DDRD =value;
		break;
	}
}
void DIO_setPortValue(u8 port_name,u8 value){
	switch(port_name){
	case 'A' :
		PORTA=value;
		break;
	case 'B':
		PORTB =value;
		break;
	case 'C':
		PORTC=value;
		break;
	case 'D' :
		PORTD=value;
		break;

	}
}
void DIO_SetPinDirection(u8 port_name,u8 pin_number,u8 value){
	//Function that deals with Bits in register and determine it's Direction
	switch(port_name){
	case 'A' :
		if (value==1){
			set_bit(DDRA,pin_number);
		}
		else if(value ==0){
			clr_bit(DDRA,pin_number);
		}
		break;
	case 'B' :
		if (value==1){
			set_bit(DDRB,pin_number);
		}
		else if(value ==0){
			clr_bit(DDRB,pin_number);
		}
		break;
	case 'C' :
		if (value==1){
			set_bit(DDRC,pin_number);
		}
		else if(value ==0){
			clr_bit(DDRC,pin_number);
		}
		break;
	case 'D' :
		if (value ==1){
			set_bit(DDRD,pin_number);
		}
		else if (value ==0){
			clr_bit(DDRD,pin_number);
		}
		break;
	}

}
void DIO_SetPinValue(u8 port_name,u8 pin_number,u8 value){
	//Function that deals with Bits in register and determine it's value
	switch(port_name){
	case 'A' :
		if (value==1){
			set_bit(PORTA,pin_number);
		}
		else if(value ==0){
			clr_bit(PORTA,pin_number);
		}
		break;
	case 'B' :
		if (value==1){
			set_bit(PORTB,pin_number);
		}
		else if(value ==0){
			clr_bit(PORTB,pin_number);
		}
		break;
	case 'C' :
		if (value==1){
			set_bit(PORTC,pin_number);
		}
		else if(value ==0){
			clr_bit(PORTC,pin_number);
		}
		break;
	case 'D' :
		if (value ==1){
			set_bit(PORTD,pin_number);
		}
		else if (value ==0){
			clr_bit(PORTD,pin_number);
		}
		break;
	}

}
u8 DIO_ReadPortValue(u8 port_name){
	u8 value;
	switch(port_name){
	case 'A':
		value=PINA;
		break;
	case 'B':
		value =PINB;
		break;
	case 'C':
		value =PINC;
		break;
	case 'D':
		value =PIND;
		break;

	}
	return value;

}
u8 DIO_ReadPinValue(u8 port_name,u8 pin_number){
	u8 value;
	switch (port_name){
	case 'A':
		value=get_bit(PINA,pin_number);
		break;
	case 'B':
		value=get_bit(PINB,pin_number);
		break;
	case 'C':
		value=get_bit(PINC,pin_number);
		break;
	case 'D':
		value=get_bit(PIND,pin_number);
		break;

	}
	return value;
}
