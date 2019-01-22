/*
 * DIO.h
 *
 *  Created on: Feb 23, 2018
 *      Author: Hanna Nabil
 */

#ifndef DIO_H_
#define DIO_H_
void DIO_setPortDirection(u8 port_name,u8 value);
void DIO_setPortValue(u8 port_name, u8 value);
void DIO_SetPinDirection(u8 port_name,u8 pin_number,u8 value);
void DIO_SetPinValue(u8 port_name,u8 pin_number,u8 value);
u8 DIO_ReadPortValue(u8 port_name);
u8 DIO_ReadPinValue(u8 port_name,u8 pin_number);


#endif /* DIO_H_ */
