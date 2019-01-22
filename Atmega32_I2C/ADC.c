/*
 * ADC.c
 *
 *  Created on: Mar 17, 2018
 *      Author: Hanna Nabil
 */
#include "typedef.h"
#include "IO.h"
#include "macros.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#define ADC_Pin 0 // ADC Pin in Port A from Pin0  to Pin 7


void __vector_16 (void) __attribute__((signal,__INTR_ATTRS));
void ADC_Init_NoInterrupt(void){
	// page 212
	// ADMUX = 0b 0110 0000
	// ADCSRA =0B 1000 0000
	/*
	clr_bit(ADMUX,7);
	set_bit(ADMUX,6); // voltage reference selection bits

	set_bit(ADMUX,5); // Enable ADC Left Adjustment Result

	// choosing which ADC from adc0 to adc8
	clr_bit(ADMUX,4);
	clr_bit(ADMUX,3);
	clr_bit(ADMUX,2);
	clr_bit(ADMUX,1);
	clr_bit(ADMUX,0);
*/
#if (ADC_Pin ==0)
	ADMUX = 0b01100000;
#elif (ADC_Pin ==1)
	ADMUX = 0b01100001;
#elif (ADC_Pin ==2)
	ADMUX = 0b01100010;
#elif (ADC_Pin ==3)
	ADMUX = 0b01100011;
#elif (ADC_Pin ==4)
	ADMUX = 0b01100100;
#elif (ADC_Pin ==5)
	ADMUX = 0b01100101;
#elif (ADC_Pin ==6)
	ADMUX = 0b01100110;
#elif (ADC_Pin ==7)
	ADMUX = 0b01100111;
#endif
	set_bit(ADCSRA,7); // Enable ADC
	clr_bit(ADCSRA,6); // don't start conversion
	clr_bit(ADCSRA,5); // 	No auto-trigger
	clr_bit(ADCSRA,4); //

	clr_bit(ADCSRA,3);  //  No Interrupt

	clr_bit(ADCSRA,0);  // pre-scale divide by 2
	clr_bit(ADCSRA,1);  //
	clr_bit(ADCSRA,2);  //
}
void ADC_Init_WithInterrupt(void){
	// page 212
	// ADMUX = 0b 0110 0000
	// ADCSRA =0B 1000 0000
	clr_bit(ADMUX,7);
	set_bit(ADMUX,6); // voltage reference selection bits


	set_bit(ADMUX,5); // Enable ADC Left Adjustment Result

	// choosing which ADC from adc0 to adc8
	clr_bit(ADMUX,4);
	clr_bit(ADMUX,3);
	clr_bit(ADMUX,2);
	clr_bit(ADMUX,1);
	clr_bit(ADMUX,0);

	set_bit(ADCSRA,7); // Enable ADC
	clr_bit(ADCSRA,6); // don't start conversion yet
	clr_bit(ADCSRA,5); // 	No auto-trigger
	clr_bit(ADCSRA,4); //

	set_bit(SREG,7); // Enable Global Interrupt
	set_bit(ADCSRA,3);  //  Interrupt ON (Enable Peripheral Interrupt)

	clr_bit(ADCSRA,0);  // pre-scale divide by 2  ==> Lowest Minimum Prescale
	clr_bit(ADCSRA,1);  //
	clr_bit(ADCSRA,2);  //

	set_bit(ADCSRA,6); // start conversion Now
}
 d64 ADC_ReadOutput(void){
	 set_bit(ADCSRA,6); // start conversion
	 while ( get_bit(ADCSRA,4)==0 ){

	 }
	 set_bit(ADCSRA,4);
	 d64 analog = (ADCH * 5.0 )/ 256.0 ; //  analog = digital * Vreference / 2^resolution
	 return analog;
 }

 void __vector_16 (void) //from vector table
 {
	 d64 analog = (ADCH * 5.0 )/ 256.0 ;
	 //d64 analog =ADC_ReadOutput_WithInterrupt();
		u8 s[]="   ";
		u8 n[]="Hanna";

			//analog =ADC_ReadOutput();
				//LCD_SetPosition(0,0);
				LCD_WriteString(s);
				LCD_SetPosition(0,0);

				LCD_Write_Float(analog);
				set_bit(ADCSRA,6); // start conversion Now

 }
