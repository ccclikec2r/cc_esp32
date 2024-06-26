#ifndef _I2C_ININ_H
#define _I2C_INIT_H

void i2c_init(void);
bool i2c_receive(void);
extern uint8_t read_buffer[2];

#endif