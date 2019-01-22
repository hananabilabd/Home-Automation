/*
 * Timer.h
 *
 *  Created on: Mar 24, 2018
 *      Author: Hanna Nabil
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "typedef.h"
void Timer0_Init (void);
void Timer1_Init(void);

void Timer1_ICU_Init(void);
void Timer1_ICU (void);
void Timer0_PWM(u8 ocr);
void Timer1_PWM(u8 ocr ,u16 icr);

//extern u32 c1 ,c2,c3;
//extern u8 flag;
extern u32 duty ,periodicity;
#endif /* TIMER_H_ */
