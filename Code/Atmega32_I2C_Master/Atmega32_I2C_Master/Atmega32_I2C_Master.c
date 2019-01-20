/*
 * Atmega32_I2C_Master.c
 *
 * Created: 7/1/2019 9:00:39 PM
 *  Author: Z.50
 */ 

#define F_CPU 8000000UL	
#include <avr/io.h>
#include <util/delay.h>						/* Include inbuilt defined Delay header file */
#include <stdio.h>							/* Include standard I/O header file */
#include <string.h>							/* Include string header file */
#include "I2C_Master_H_file.h"				/* Include I2C header file */
#include "LCD_16x2_H_file.h"				/* Include LCD header file */

#define Slave_Write_Address		0x20
#define Slave_Read_Address		0x21
#define	count					10

int main(void)
{
	char buffer[10];
	
	LCD_Init();								/* Initialize LCD */
	I2C_Init();								/* Initialize I2C */
	
	LCD_String_xy(1, 0, "Master Device");
	
    while(1)
    {
        //TODO:: Please write your application code 
		LCD_String_xy(2, 0, "Sending :       ");
		I2C_Start_Wait(Slave_Write_Address);/* Start I2C communication with SLA+W */
		_delay_ms(5);
		for (uint8_t i = 0; i < count ; i++)
		{
			sprintf(buffer, "%d    ",i);
			LCD_String_xy(2, 13, buffer);
			I2C_Write(i);					/* Send Incrementing count */
			_delay_ms(500);
		}
		LCD_String_xy(2, 0, "Receiving :       ");
		I2C_Repeated_Start(Slave_Read_Address);	/* Repeated Start I2C communication with SLA+R */
		_delay_ms(5);
		for (uint8_t i = 0; i < count; i++)
		{
			if(i < count - 1)
			sprintf(buffer, "%d    ", I2C_Read_Ack());/* Read and send Acknowledge of data */
			else
			sprintf(buffer, "%d    ", I2C_Read_Nack());/* Read and Not Acknowledge to data */
			LCD_String_xy(2, 13, buffer);
			_delay_ms(500);
		}
		I2C_Stop();							/* Stop I2C */
    }
}