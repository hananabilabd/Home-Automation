/*
 * Interrupt.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Hanna Nabil
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_
void Interrupt_Init_INT0(void);
void Interrupt_Init_INT1(void);
void Interrupt_Init_INT2(void);
void __vector_1 (void) __attribute__((signal,__INTR_ATTRS));
void __vector_2 (void) __attribute__((signal,__INTR_ATTRS));
void __vector_3 (void) __attribute__((signal,__INTR_ATTRS));
#endif /* INTERRUPT_H_ */
