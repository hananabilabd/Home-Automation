/*
 * ADC_H_file.h
 *
 * Created: 13/1/2019 6:08:37 PM
 *  Author: Z.50
 */ 

#ifndef ADC_H_FILE_H_
#define ADC_H_FILE_H_

#define F_CPU 8000000UL
#include <avr/io.h>							/* Include AVR std. library file */
#include <util/delay.h>					/* Include Delay header file */
#define degree_sysmbol 0xdf

void ADC_Init();
int ADC_Read(char);

#endif /* ADC_H_FILE_H_ */