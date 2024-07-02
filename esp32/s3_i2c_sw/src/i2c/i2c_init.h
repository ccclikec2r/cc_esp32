#include<stdio.h>
#ifndef _I2C_ININ_H
#define _I2C_INIT_H

void i2c_gpio_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_sendbyte(uint8_t Byte);
uint8_t i2c_receivebyte(void);
void i2c_sendAck(uint8_t AckBit);
uint8_t i2c_receiveAck(void);


#endif