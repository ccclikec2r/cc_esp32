#include<stdio.h>

#ifndef _AP3216C_ININ_H
#define _AP3216C_INIT_H

struct ap3216c_data
{
    uint16_t ir;
    uint16_t als;
    uint16_t ps;
};

void ap3216c_writereg(uint8_t RegAddress,uint8_t data);
uint8_t ap3216c_Readreg(int8_t RegAddress);
void ap3216c_init(void);
void ap3216c_getdata(struct ap3216c_data *data);


#endif