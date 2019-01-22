/*
 * I2C.c
 *
 *  Created on: Apr 20, 2018
 *      Author: Hanna Nabil
 */
#include "typedef.h"
#include "IO.h"
#include "macros.h"
#include "DIO.h"
#include "Timer.h"
#include "I2C.h"
//https://www.engineersgarage.com/embedded/avr-microcontroller-projects/atmega32-twi-two-wire-interface

void I2C_INIT_master(void){
	TWBR=0x04; // Bit Rate
	// SCL freq= F_CPU/(16+2(TWBR).4^TWPS)

	clr_bit(TWSR,0);// Prescaler =1
	clr_bit(TWSR,1);

	//set_bit(TWCR,6); // Enable acknowledge bit
	set_bit(TWCR,2);  //enable TWI (I2C)

}
void I2C_INIT_slave(void){
	TWAR=0x20;    // Fill slave address to TWAR
	set_bit(TWCR,2);  //enable TWI (I2C)
}
void I2C_Start(void){
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	set_bit(TWCR,7); // Clear TWI interrupt flag
	set_bit(TWCR,5); // start condition bit
	set_bit(TWCR,2); // Enable TWI
	while (get_bit(TWCR,7)==0);// Wait till start condition is transmitted (wait if not equal 1 )
	while((TWSR & 0xF8)!= START_ACK); //  ==> A START condition has been transmitted ==> Check for the acknowledgment

}
void I2C_Repeated_start(void){
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	set_bit(TWCR,7); // Clear TWI interrupt flag
	set_bit(TWCR,5); // start condition bit
	set_bit(TWCR,2); // Enable TWI
	while (get_bit(TWCR,7)==0);// Wait till start condition is transmitted (wait if not equal 1 )
	while((TWSR & 0xF8)!= REP_START_ACK); //  ==> A START condition has been transmitted ==> Check for the acknowledgment
}
void I2C_Send_slave_address_with_write_req(u8 slave_address){
	TWDR=slave_address;    // Address and read instruction
	clr_bit(TWDR,0); // write
	// Clear TWI interrupt flag,Enable TWI
	set_bit(TWCR,7); // Clear TWI interrupt flag
	set_bit(TWCR,2); // Enable TWI

	while (get_bit(TWCR,7)==0); // Wait till complete TWDR byte transmitted

	while((TWSR & 0xF8)!= SLAVE_ADD_AND_WR_ACK);  // Check for the acknowledgment f8 ==> because we check for the most 5 bits (from 7 to bit 3)
}
void I2C_Send_slave_address_with_read_req(u8 slave_address){
	TWDR=slave_address;    // Address and read instruction
	set_bit(TWDR,0); // Read

	// Clear TWI interrupt flag,Enable TWI
	set_bit(TWCR,7); // Clear TWI interrupt flag
	set_bit(TWCR,2); // Enable TWI

	while (get_bit(TWCR,7)==0); // Wait till complete TWDR byte transmitted

	while((TWSR & 0xF8)!=  SLAVE_ADD_AND_RD_ACK);  // Check for the acknowledgment f8 ==> because we check for the most 5 bits (from 7 to bit 3)
}
void I2C_Write_byte(u8 byte){
	TWDR=byte;    // put data in TWDR

	// Clear TWI interrupt flag,Enable TWI
	set_bit(TWCR,7); // Clear TWI interrupt flag
	set_bit(TWCR,2); // Enable TWI

	while (get_bit(TWCR,7)==0); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != WR_BYTE_ACK); // Check for the acknowledgment Data byte has been transmitted ACK has been received
}
u8 i2c_read_byte(void){
	// Clear TWI interrupt flag,Enable TWI
	set_bit(TWCR,7); // Clear TWI interrupt flag
	set_bit(TWCR,2); // Enable TWI

	while (get_bit(TWCR,7)==0); // Wait till complete TWDR byte transmitted

	while((TWSR & 0xF8) != RD_BYTE_WITH_NACK); // Check for the acknowledgment

	return TWDR;
}
void I2C_Stop(void){
	set_bit(TWCR,7); // Clear TWI interrupt flag
	set_bit(TWCR,4);//Put stop condition
	set_bit(TWCR,2); // Enable TWI
	while (get_bit(TWCR,4)==0);
}
void I2C_Slave_check_slave_address_received_with_write_req(void){ // slave Transmitter


		// Clear TWI interrupt flag,Enable TWI ,Get acknowledgment
		//set_bit(TWCR,7); // Clear TWI interrupt flag
		//set_bit(TWCR,2); // Enable TWI
		//set_bit(TWCR,6);// Get acknowledgment
		TWCR |= (1<<7 )|(1<<6 )|(1<<2 );
		while (!(TWCR & (1<<7)));  // Wait for TWINT flag
		while((TWSR & 0xF8)!= SLAVE_ADD_RCVD_WR_REQ);    // Loop till correct acknowledgment have been received
}
void I2C_Slave_check_slave_address_received_with_read_req(void){ // slave receiver


		// Clear TWI interrupt flag,Enable TWI ,Get acknowledgment
		//set_bit(TWCR,7); // Clear TWI interrupt flag
		//set_bit(TWCR,2); // Enable TWI
		//set_bit(TWCR,6);// Get acknowledgment

		TWCR |= (1<<7 )|(1<<6 )|(1<<2 );
		while (!(TWCR & (1<<7)));  // Wait for TWINT flag
		while((TWSR & 0xF8)!= SLAVE_ADD_RCVD_RD_REQ);  // Loop till correct acknowledgment have been received


}
u8   I2C_Slave_read_byte(void){
	// Clear TWI interrupt flag,Enable TWI ,Get acknowledgment
			 	//set_bit(TWCR,7); // Clear TWI interrupt flag
			 	//set_bit(TWCR,2); // Enable TWI
			 	//set_bit(TWCR,6);// Get acknowledgment

			TWCR |= (1<<7 )|(1<<6 )|(1<<2 );
			while (get_bit(TWCR,7)==0);    // Wait for TWINT flag
	    while((TWSR & 0xF8)!= SLAVE_DATA_RECEIVED);        // Wait for acknowledgment
	   return TWDR;                    // Get value from TWDR

}
void I2C_Slave_write_byte(u8 byte){
	TWDR= byte;              // Fill TWDR register with the data to be sent
	// Clear TWI interrupt flag,Enable TWI
	//set_bit(TWCR,7); // Clear TWI interrupt flag
	//set_bit(TWCR,2); // Enable TWI
	TWCR |= (1<<7 )|(1<<6 )|(1<<2 );
	while (get_bit(TWCR,7)==0);
	while((TWSR & 0xF8) != SLAVE_BYTE_TRANSMITTED); // Wait for the acknowledgment
}

