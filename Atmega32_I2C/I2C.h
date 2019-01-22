/*
 * I2C.h
 *
 *  Created on: Apr 20, 2018
 *      Author: Hanna Nabil
 */

#ifndef I2C_H_
#define I2C_H_

//#include <avr/io.h>

#define START_ACK                0x08 // start has been sent
#define REP_START_ACK            0x10 // repeated start
#define SLAVE_ADD_AND_WR_ACK     0x18 // Master transmit ( slave address + Write request ) ACK
#define SLAVE_ADD_AND_RD_ACK     0x40 // Master transmit ( slave address + Read request ) ACK
#define WR_BYTE_ACK              0x28 // Master transmit data ACK
#define RD_BYTE_WITH_NACK        0x58 // Master received data with not ACK
#define SLAVE_ADD_RCVD_RD_REQ    0x60 // means that slave address is received with write req (slave_transmitter)
#define SLAVE_ADD_RCVD_WR_REQ    0xA8 // means that slave address is received with read req (slave receiver)
#define SLAVE_DATA_RECEIVED      0x80 // means that read byte req is received
#define SLAVE_BYTE_TRANSMITTED   0xC0 // means that write byte req is received

void I2C_INIT_master(void);
void I2C_INIT_slave(void);
void I2C_Start(void);
void I2C_Repeated_start(void);
void I2C_Send_slave_address_with_write_req(u8 slave_address);
void I2C_Send_slave_address_with_read_req(u8 slave_address);
void I2C_Write_byte(u8 byte);
u8 i2c_read_byte(void);
void I2C_Stop(void);
void I2C_Slave_check_slave_address_received_with_write_req(void);
void I2C_Slave_check_slave_address_received_with_read_req(void);
u8 I2C_Slave_read_byte(void);
void I2C_Slave_write_byte(u8 byte);

#endif /* I2C_H_ */
