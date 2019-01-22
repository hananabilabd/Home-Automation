/*
 * Interrupt.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Hanna Nabil
 */
#include "typedef.h"
#include "IO.h"
#include "macros.h"
#define F_CPU 12000000UL
#include <util/delay.h>



//void __vector_1 (void) __attribute__((signal,__INTR_ATTRS));
//void __vector_2 (void) __attribute__((signal,__INTR_ATTRS));

/*
 *  INT0 ==> D2
 *  INT1 ==> D3
 *  INT2 ==> B2
 */
void Interrupt_Init_INT0(void)
{ //Digital External Interrupt for INT0 at falling edge
	set_bit(SREG,7); // Enable Global Interrupt
	set_bit(GICR,6); // Enable Peripheral Interrupt
	clr_bit(MCUCR,0); // Mode of the peripheral interrupt to be falling edge  page 64 in datasheet
	clr_bit(MCUCR,1);

}
void Interrupt_Init_INT1(void)
{ //Digital External Interrupt for INT1 at falling edge
	set_bit(SREG,7); // Enable Global Interrupt
	set_bit(GICR,7); // Enable Peripheral Interrupt
	clr_bit(MCUCR,2); // Mode of the peripheral interrupt to be falling edge  page 64 in datasheet
	set_bit(MCUCR,3);

}
void Interrupt_Init_INT2(void)
{ //Digital External Interrupt for INT1 at falling edge
	set_bit(SREG,7); // Enable Global Interrupt
	set_bit(GICR,5); // Enable Peripheral Interrupt
	clr_bit(MCUCSR,6); // Mode of the peripheral interrupt to be falling edge  page 64 in datasheet
	// only supported falling and rising edge
	// one is rising edge , zero in MCUCSR to falling edge
	// page 65 in the Datasheet


}

void __vector_1 (void) // page 42 in datasheet
{
	DIO_SetPinValue('C',7,1);

	_delay_ms(100);
}
void __vector_2 (void)
{
	DIO_SetPinValue('C',7,0);

	_delay_ms(100);
}
void __vector_3 (void)
{
	DIO_SetPinValue('C',7,0);

	_delay_ms(100);
}

