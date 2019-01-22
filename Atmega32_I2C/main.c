/*
 * main.c
 *
 *  Created on: Feb 24, 2018
 *      Author: Hanna Nabil
 */

#include "typedef.h"
#include "IO.h"
#include "macros.h"
#define F_CPU 12000000UL
#include <util/delay.h>
#include "DIO.h"
//#include "Timer.h"
#include "I2C.h"

u8 address=0x20, read=1, write=0;
u8 write_data, recv_data;
u8 result;
	int main(void)
	{
		_delay_ms(2000);
		DIO_setPortDirection('B',0xFF);
		DIO_SetPinDirection('C',7,1);
		//DIO_SetPinDirection('C',0,0);
		//DIO_SetPinDirection('C',1,0);

		I2C_INIT_slave();  // Function to initialize TWI
		while(1)
		{
			I2C_Slave_check_slave_address_received_with_read_req();
			 result=I2C_Slave_read_byte();
			if (result ==0 || result == '0' || result == '1'|| result == 1){
				DIO_SetPinValue('C',7,1);// Led on
				  			_delay_ms(1000);
				  			write_data==0x00;
			}
			else if (result ==1){
				DIO_SetPinValue('C',7,1);
				  				_delay_ms(1000);
				  				write_data==0x01;
			}
			I2C_Slave_check_slave_address_received_with_write_req();
			I2C_Slave_write_byte(write_data);



		}


		return 0;
	}



