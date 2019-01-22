/*
 * Timer.c
 *
 *  Created on: Mar 24, 2018
 *      Author: Hanna Nabil
 */
#include "typedef.h"
#include "IO.h"
#include "macros.h"
#include "DIO.h"
#include "Timer.h"

#define Timer0_Mode 'PWM' // Normal (overflow) , PWM , CTC
#define Timer0_Prescale '256' // NO , 'clk/8' , clk /64 , clk/256 , clk /1024

#define Timer1_Mode 'phase' // ICU ,  PWM (Fast PWM) , OFF
#define Timer1_PWM_Pin  5

u32 c1 ,c2,c3 =0;
u32 T1_counter =0;
u8 flag =0;
u32 duty ,periodicity=0;

#if (Timer0_Mode == 'CTC')
	void __vector_10 (void) __attribute__((signal,__INTR_ATTRS));

#elif (Timer0_Mode == 'Normal')
	void __vector_11 (void) __attribute__((signal,__INTR_ATTRS));
#endif
#if (Timer1_Mode == 'ICU')
	void __vector_6 (void) __attribute__((signal,__INTR_ATTRS));
	void __vector_9 (void) __attribute__((signal,__INTR_ATTRS));
#elif (Timer1_Mode == 'Normal')
	void __vector_9 (void) __attribute__((signal,__INTR_ATTRS));
#endif

/*
 * Timer Tick = 1/ Frequency  =1 / 12*10^6 =
 * Timer Overflow = Timer Tick * 256 (register size) =
 * no of  ISR Accessing = Desired Time / Timer Overflow = 1 sec /....
 */
void Timer0_Init (void){ // Normal mode
		set_bit(SREG,7); // Enable Global Interrupt

		#if (Timer0_Mode == 'Normal')
				set_bit(TIMSK,0); // Timer/Counter0 Overflow Interrupt Enable

				clr_bit(TCCR0,3); // Normal Mode
				clr_bit(TCCR0,6);


		#elif (Timer0_Mode == 'CTC')
				set_bit(TIMSK,1); //  Timer/Counter0 Output Compare Match Interrupt Enable

				set_bit(TCCR0,3); // CTC Mode
				clr_bit(TCCR0,6);
				OCR0=100; // Output Compare Register ,this is the register we want to compare with
		#elif (Timer0_Mode == 'PWM') // on pin OC0==> B3
				//set_bit(TIMSK,1); //  Timer/Counter0 Output Compare Match Interrupt Enable

				set_bit(TCCR0,3); // Fast PWM Mode
				set_bit(TCCR0,6);

				clr_bit(TCCR0,4);// Clear OC0 on compare match, set OC0 at TOP
				set_bit(TCCR0,5);
				DIO_SetPinDirection('B',3,1);
				OCR0=200; // play in Duty cycle as maximum is 256
				// Duty cycle = (OCR0 /256 )* 100
		#endif

		#if (Timer0_Prescale == 'NO')
				set_bit(TCCR0,0);// Datasheet Page 79 No prescaler
				clr_bit(TCCR0,1);
				clr_bit(TCCR0,2);



		#elif (Timer0_Prescale =='8')
				clr_bit(TCCR0,0); // Datasheet Page 79 with prescaler ==> clk /8
				set_bit(TCCR0,1);
				clr_bit(TCCR0,2);


		#elif (Timer0_Prescale =='64')
				set_bit(TCCR0,0);// Datasheet Page 79 with prescaler ==> clk /64
				set_bit(TCCR0,1);
				clr_bit(TCCR0,2);
		#elif (Timer0_Prescale =='256')
				clr_bit(TCCR0,0);// Datasheet Page 79 with prescaler ==> clk /256
				clr_bit(TCCR0,1);
				set_bit(TCCR0,2);


		#elif (Timer0_Prescale =='1024')
				set_bit(TCCR0,0);// Datasheet Page 79 with prescaler ==> clk /1024
				clr_bit(TCCR0,1);
				set_bit(TCCR0,2);


		#endif

	}


void Timer1_Init(void){ //16 bit Timer + FAST PWM
		#if (Timer1_Mode == 'PWM' && Timer1_PWM_Pin == 5)
			TCCR1A =0b10000010;
			TCCR1B=0b00011100;
			ICR1L=937;
			DIO_SetPinDirection('D',5,1);

		#elif (Timer1_Mode == 'PWM' && Timer1_PWM_Pin == 4)
				TCCR1A =0b00100010;
				TCCR1B=0b00011100;  // Prescale clk /256
				ICR1L=937;
				DIO_SetPinDirection('D',4,1);
		#elif (Timer1_Mode == 'phase' && Timer1_PWM_Pin == 5) //D5==>a
					TCCR1A =0b10000000;
					TCCR1B=0b00010010; // prescaler = 8
					//ICR1L=937;
					DIO_SetPinDirection('D',5,1);
	#elif (Timer1_Mode == 'phase' && Timer1_PWM_Pin == 4) // D4 ==>b
						TCCR1A =0b00100000;
						TCCR1B=0b00011100;
						ICR1L=937;
						DIO_SetPinDirection('D',4,1);

		#elif (Timer1_Mode == 'ICU')
			TCCR1A =0x00;
			TCCR1B=0b01000001; // Configure Timer1 for ICU and bit6 =1 to detect rising Edge
			set_bit(SREG,7); // Enable Global Interrupt
			set_bit(TIMSK,5); // Enable ICU Interrupt
			set_bit(TIMSK,2); // Enable Overflow Interrupt


			DIO_SetPinDirection('D',6,0);// Input ICP ==> D6  it is a pin for ICU

		#endif
}
void Timer0_PWM(u8 ocr){ // this function to give specific PWM through Pin ==> B3




					OCR0=ocr; // play in Duty cycle as maximum is 256
					// Duty cycle = (OCR0 /256 )* 100




}

void Timer1_PWM(u8 ocr ,u16 icr){// this function to give specific PWM through Pin ==> D4 or D5
	#if (Timer1_PWM_Pin == 5 && Timer1_Mode =='phase')
			OCR1AL=ocr;
			ICR1 =icr;
		#elif (Timer1_PWM_Pin == 5 && Timer1_Mode =='PWM')
			OCR1AL=ocr;
		#elif (Timer1_PWM_Pin == 4 && Timer1_Mode =='PWM')
			OCR1BL=ocr;
		#endif

}



u32 counter =0;

void __vector_11 (void) //Timer0  Mode==> Normal Mode (Overflow)
{
	counter ++;
		#if ( Timer0_Prescale == 'NO' )
			if (counter == 46875){ // Normal Mode + No Prescaler
						toggle_bit(PORTA, 0);
						counter =0;
					}


		#elif (Timer0_Prescale =='8')

			if (counter == 5859){ // Normal Mode +Prescaler clk /8
							toggle_bit(PORTA, 0);
							counter =0;
						}
		#elif (Timer0_Prescale =='64')

			if (counter == 732){ // Normal Mode +Prescaler clk/64
							toggle_bit(PORTA, 0);
							counter =0;
						}
		#elif (Timer0_Prescale =='256')

			if (counter == 183){ // Normal Mode +Prescaler clk /256
							toggle_bit(PORTA, 0);
							counter =0;
						}
		#elif (Timer0_Prescale =='1024')

			if (counter == 45){ // Normal Mode +Prescaler clk /1024
							toggle_bit(PORTA, 0);
							counter =0;
						}

		#endif



}



void __vector_10 (void) // Timer0 CTC Mode
{
	counter ++;

	if (counter == 120000){ // CTC +  No Prescaler
				toggle_bit(PORTA, 0);
				counter =0;
			}

}

void __vector_6 (void) // Timer1 ICU Mode
{
		if (flag==0){
			c1 =ICR1;
			clr_bit(TCCR1B,6); //to detect the falling edge
			T1_counter =0;
		}

		else if (flag==1){
			c2=ICR1 + (T1_counter * 65535);
			set_bit(TCCR1B,6); // to detect rising edge
		}
		else if  (flag==2){
			c3=ICR1 + (T1_counter * 65535) ;
			clr_bit(TIMSK,5); // to disable Peripheral Interrupt
		}

	flag++;
}
void __vector_9 (void) // Timer1 Normal (Overflow) Mode
{
		T1_counter++;

}
void Timer1_ICU_Init(void){
//LCD_Init();
Timer0_Init();
Timer1_Init();

}
void Timer1_ICU (void){
	if (flag ==3){
		//d64 duty ,periodicity=0;

					duty = (c2-c1)*100/(c3-c1);
					periodicity =(c3-c1)/12; //periodicity = c3-c1 /frequency
					//LCD_SetPosition(0,0);
					//LCD_Write_Float(duty);
					//LCD_Write_Number(duty);
					//LCD_SetPosition(1,0);
					//LCD_Write_Float(periodicity);
					//LCD_Write_Number(periodicity);
					set_bit(TIMSK,5); // To Enable Peripheral Interrupt
					set_bit(TIFR,5); // Read datasheet page 111
					flag=0;
				}
}
