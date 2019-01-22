/*
 * LCD.h
 *
 *  Created on: Mar 2, 2018
 *      Author: Hanna Nabil
 */

#ifndef LCD_H_
#define LCD_H_
void LCD_writeCharacter(u8 character);
void LCD_writeCommand(u8 character);
void LCD_Init(void);
void LCD_WriteString(u8 *arr);
void LCD_SetPosition(u8 row,u8 column);
void LCD_Write_Number(u64 number);
void LCD_Write_Float(double  realValue);
void LCD_Write_Special(void);
void LCD_Clear_Screen(void);
void Hanna(void);
#endif /* LCD_H_ */
