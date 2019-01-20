/*
 * Atmega32_SPI_Master.c
 *
 * Created: 7/1/2019 6:30:57 PM
 *  Author: Z.50
 */ 

#define F_CPU 8000000UL	
#include <avr/io.h>
#include <util/delay.h>					/* Include Delay header file */
#include <stdio.h>
#include <string.h>
#include "LCD_16x2_H_file.h"			/* Include LCD header file */
#include "SPI_Master_H_file.h"			/* Include SPI master header file */
#include "ADC_H_file.h"

int main(void)
{
	char Temp[10];
	float celsius;
	
	LCD_Init();
	ADC_Init();                 /* initialize ADC*/
	SPI_Init();
	
	LCD_String_xy(1, 0, "Master Device");
	LCD_String_xy(2, 0, "Temp:    ");
	SS_Enable;
	
    while(1)
    {
        //TODO:: Please write your application code 
		celsius = (ADC_Read(0)*4.88);
		celsius = (celsius/10.00);
		
		sprintf(Temp,"%d%cC  ", (int)celsius, degree_sysmbol);               /* convert integer value to ASCII string */
		LCD_String_xy(2, 8, Temp);
		SPI_Write(celsius);
		
		_delay_ms(500);
		memset(Temp,0,10);
		
    }
}