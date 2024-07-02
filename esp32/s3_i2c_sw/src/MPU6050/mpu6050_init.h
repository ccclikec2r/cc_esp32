#include<stdio.h>

#ifndef _MPU6050_ININ_H
#define _MPU6050_INIT_H

struct mpu6050_data 
{
    int16_t Accx,Accy,Accz;
    int16_t GyroX,Gyroy,GyroZ;
};

void mpu6050_init(void);
void mpu6050_writereg(uint8_t RegAddress,uint8_t data);
uint8_t mpu6050_ReadReg(int8_t RegAddress);
void mpu6050_getdata(struct mpu6050_data *mpu6050_data);
uint8_t mpu6050_getID(void);

#endif