#include<stdio.h>

#ifndef _xl9555_ININ_H
#define _xl9555_INIT_H

void xl9555_init(void);
uint8_t xl9555_Readreg(int8_t RegAddress);
void xl9555_Writereg(uint8_t RegAddress,uint8_t data);
int xl9555_pin_read(uint16_t pin);
uint16_t xl9555_pin_write(uint16_t pin, int val);
uint8_t xl9555_key_scan(uint8_t mode);

#endif