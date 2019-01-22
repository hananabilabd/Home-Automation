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
#include "I2C_Slave_H_File.h"
u8 address=0x20, read=1, write=0;
u8 write_data, recv_data;
u8 result;
/*
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
*/


#define Slave_Address			0x20
u8 count = 0;
u8 toggle_pin =0;
int main(void)
{

	DIO_SetPinDirection('C',7,1);
	DIO_SetPinDirection('C',6,1);
	I2C_Slave_Init(Slave_Address);
	//trying
    while(1)
    {

		switch(I2C_Slave_Listen())				/* Check for any SLA+W or SLA+R */
		{
			case 0:
			{


				do
				{

					count = I2C_Slave_Receive();/* Receive data byte*/
					if (count==0){DIO_SetPinValue('C',7,0);// Led on
					_delay_ms(2000);}
					else if (count==1){DIO_SetPinValue('C',7,1);// Led on
					_delay_ms(2000);}

					} while (count != -1);			/* Receive until STOP/REPEATED START received */
					//count = 0;

					break;
				}
				case 1:
				{
					int8_t Ack_status;

					do
					{
						DIO_SetPinValue('C',6,0);// Led on
						Ack_status = I2C_Slave_Transmit(1);	/* Send data byte */
						DIO_SetPinValue('C',6,1);// Led on
						//toggle_bit(PORTC,7);
						//if (toggle_pin ==0){toggle_pin =1;}
						//else {toggle_pin =0;}
						//DIO_SetPinValue('C',7,0);// Led on
						_delay_ms(1000);

						} while (Ack_status == 0 || Ack_status == -1 || Ack_status == -2 );		/* Send until N Acknowledgment is received */
						break;
					}
					default:
						DIO_SetPinValue('C',6,0);// Led on
					break;
				}
    }
}
