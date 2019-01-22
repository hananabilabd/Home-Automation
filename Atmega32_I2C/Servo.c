/*
 * Servo.c
 *
 *  Created on: Mar 30, 2018
 *      Author: Hanna Nabil
 */

#include "typedef.h"
#include "IO.h"
#include "macros.h"
#define F_CPU 12000000UL
#include <util/delay.h>
#include "Timer.h"
#include "DIO.h"
#include "Servo.h"
#define PWM_Pin 5 // D5 ===> OC1A
//#define PWM_Pin 4 // D4 ===> OC1B

void Servo_Init(void){ // OC1A ==>D5
#if (PWM_Pin == 5)
	TCCR1A =0b10000010;
		TCCR1B=0b00011100;// Prescale clk /256
		ICR1L=937; // this register is actually 8 bit but when we put a value higher than 256 in it , it overflows in ICR1H
		DIO_SetPinDirection('D',5,1);
#elif (PWM_Pin == 4)
		TCCR1A =0b00100010;
		TCCR1B=0b00011100;  // Prescale clk /256
		ICR1L=937;
		DIO_SetPinDirection('D',4,1);
#endif
}
void Servo_WriteAngle(u8 angle){ // takes from 0 to 180
	d64 x= (angle* (1.0/2.0)) +25;
	#if (PWN_Pin ==5)
		OCR1AL=  (u64) x; // cast into int
	#elif (PWM_Pin ==4)
		OCR1BL=  (u64) x; // cast into int
	#endif
	//_delay_ms(50);

}
