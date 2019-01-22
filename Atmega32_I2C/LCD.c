/*
 * lcd.c
 *
 *  Created on: Mar 2, 2018
 *      Author: Hanna Nabil
 */

#include "typedef.h"
#include "LCD_config.h"
#include "DIO.h"
#include "DIO.h"
#include "LCD.h"
#define F_CPU 12000000UL
#include <util/delay.h>
//Anode --> 5v   , K (cathode) -->0V ,, D0-D7 --> Port
// RS , RW ,E -->Control Pins
//VSS -->Ground ,, VDD --> +5V
void LCD_writeCharacter(u8 character){
	DIO_setPortValue(LCD_port,character);
	DIO_SetPinValue(LCD_control_port,RS,1);//RS 1 For writing Data
	DIO_SetPinValue(LCD_control_port,RW,0); //RW O For FOR writing (active Low)
	DIO_SetPinValue(LCD_control_port,E,1); //access open
	_delay_ms(1);
	DIO_SetPinValue(LCD_control_port,E,0);// Give pulse
	_delay_ms(2);
}
void LCD_writeCommand(u8 character){
	DIO_setPortValue(LCD_port,character);
	DIO_SetPinValue(LCD_control_port,RS,0); //RS 0 For writing Commands
	DIO_SetPinValue(LCD_control_port,RW,0);// RW O For FOR writing (active Low)
	DIO_SetPinValue(LCD_control_port,E,1); // Give Pulse to Open Access
	_delay_ms(1);
	DIO_SetPinValue(LCD_control_port,E,0);
	_delay_ms(2);
}
void LCD_Init(void){ // Look at LCD Data Sheet Page 13 for 8-Bit Initialization
	DIO_setPortDirection(LCD_port,0xFF);
	DIO_SetPinDirection(LCD_control_port,RS,1);
	DIO_SetPinDirection(LCD_control_port,RW,1);
	DIO_SetPinDirection(LCD_control_port,E,1);
	_delay_ms(50);
	LCD_writeCommand(0b00111000);//Function Set 001(DL)(N)(F)-- , DL-->Data Length (1 for 8 bit and 0 for 4 bit) ,, N-->Lines (1 for 2 lines & 0 for 1 Line) ,, F --> Font (1 for 5*7 and 0 for 5*8 )
	_delay_ms(1);
	LCD_writeCommand(0b00001100);// Display On /OFF control 00001DCB , D --> Entire Display On /OFF 1 for On , C Cursor ON / OFF 1 for ON , B for Blinking Cursor 1 for ON
	_delay_ms(1);
	LCD_writeCommand(0b00000001);// Clear Display
		_delay_ms(2);
}
// Array is passed always to function by reference but there is a special case in array of character we can know the end of array with the help of Null character
void LCD_WriteString(u8 *arr){// same as arr[]
	u8 counter =0;
	while(arr[counter] != '\0'){ //Null character
		LCD_writeCharacter(arr[counter]);
		counter ++;
	}

}
void LCD_SetPosition(u8 row,u8 column){
	if (column <=39 && row <3){ // Capacity
	if (row==0){
		LCD_writeCommand(128+column); // as in LCD Datasheet page 16 Set DDRAM address begin with 0b1 --> which mean 128
	}
	else if  (row==1){
		LCD_writeCommand(128+64+column);
	}
	}
}
void LCD_Write_Number(u64 number){
	u64 reversed =1;
	u8 temp =0;
	if (number ==0){ //
		LCD_writeCharacter('0');
	}
	while (number != 0){
		temp =number %10 ; //to get unit
		number =number /10; //to get tenth
		reversed=reversed *10 +temp; //construct the number in reversed  order
	}
	while (reversed != 1){
		temp =reversed %10 ; // get unit
		reversed =reversed /10; // get tenth
		LCD_writeCharacter(temp +48);// because of the ask code
	}
}
void LCD_Write_Float(double realValue){

	int intValue = (int)realValue;
	u64 number = intValue;
	double diffValue = realValue - (double)intValue;
	int anotherIntValue = (int)(diffValue * 1000.0);
	u64 reversed =1;
	u8 temp =0;
	if (number ==0){ //
		LCD_writeCharacter('0');
	}
	while (number != 0){
		temp =number % 10 ; //to get unit
		number =number /10; //to get tenth
		reversed=reversed *10 +temp; //construct the number in reversed  order
	}
	while (reversed != 1){
		temp =reversed % 10 ; // get unit
		reversed =reversed /10; // get tenth
		LCD_writeCharacter(temp +48);// because of the ask code
	}
	LCD_writeCharacter('.');
	// second integer (integer after floating point)
	u64 reversed2 =1;
	u8 temp2 =0;
	if (anotherIntValue ==0){ //
			LCD_writeCharacter('0');
		}
		while (anotherIntValue != 0){
			temp2 =anotherIntValue % 10 ; //to get unit
			anotherIntValue =anotherIntValue /10; //to get tenth
			reversed2 = reversed2 *10 +temp2; //construct the number in reversed  order
		}
		while (reversed2 != 1){
			temp2 =reversed2 % 10 ; // get unit
			reversed2 =reversed2 /10; // get tenth
			LCD_writeCharacter(temp2 +48);// because of the ask code
		}
}
void LCD_Write_Special(void){
	s8 i,j;
	for (i=13,j=0;i>=0,j<=15 ;i--,j++){
		Hanna();

		LCD_SetPosition(1,i);
		LCD_writeCharacter(2);
		LCD_writeCharacter(1);
		LCD_writeCharacter(0);
		LCD_SetPosition(0,j);
		u8 array[]="HANNA";
		LCD_WriteString(array);
		_delay_ms(300);
		LCD_Clear_Screen();
	}

	for (i=3,j=14;i<=13,j>=0 ;i++,j--){
			Hanna();

			LCD_SetPosition(1,i);
			LCD_writeCharacter(2);
			LCD_writeCharacter(1);
			LCD_writeCharacter(0);
			LCD_SetPosition(0,j);
			u8 array[]="HANNA";
			LCD_WriteString(array);
			_delay_ms(300);
			LCD_Clear_Screen();
		}



}
void LCD_Clear_Screen(void){
	LCD_writeCommand(0b00000001);
}
void Hanna(void){ // for writing in arabic
	LCD_writeCommand(0b01000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00001000);
		LCD_writeCharacter(0b00010100);
		LCD_writeCharacter(0b00000010);
		LCD_writeCharacter(0b00011111);
		//el 7arf el tane
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00010000);
		LCD_writeCharacter(0b00010000);
		LCD_writeCharacter(0b00011111);
		// 3rd
		LCD_writeCharacter(0b00000000);
		LCD_writeCharacter(0b00010000);
		LCD_writeCharacter(0b00010000);
		LCD_writeCharacter(0b00010000);
		LCD_writeCharacter(0b00010010);
		LCD_writeCharacter(0b00010000);
		LCD_writeCharacter(0b00010000);
		LCD_writeCharacter(0b00011111);
}
