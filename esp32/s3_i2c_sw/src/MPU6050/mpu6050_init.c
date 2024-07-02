#include<i2c/i2c_init.h>
#include<stdio.h>
#include<MPU6050/MPU6050_reg.h>

#define MPU6050_Address 0xD0

struct mpu6050_data 
{
    int16_t Accx,Accy,Accz;
    int16_t GyroX,Gyroy,GyroZ;
};

void mpu6050_writereg(uint8_t RegAddress,uint8_t data)
{
    i2c_start();
    i2c_sendbyte(MPU6050_Address);
    i2c_receiveAck();
    i2c_sendbyte(RegAddress);
    i2c_receiveAck();
    i2c_sendbyte(data);
    i2c_receiveAck();
    i2c_stop();
}

uint8_t mpu6050_Readreg(int8_t RegAddress)
{
    i2c_start();
    i2c_sendbyte(MPU6050_Address);
    i2c_receiveAck();
    i2c_sendbyte(RegAddress);
    i2c_receiveAck();
    
    i2c_start();
    i2c_sendbyte(MPU6050_Address | 0x01);
    i2c_receiveAck();
    uint8_t data = i2c_receivebyte();
    i2c_sendAck(1);
    i2c_stop();
    return data;
}

void mpu6050_init(void)
{
    i2c_gpio_init();
    /*MPU6050寄存器初始化，需要对照MPU6050手册的寄存器描述配置，此处仅配置了部分重要的寄存器*/
	mpu6050_writereg(MPU6050_PWR_MGMT_2, 0x00);		//电源管理寄存器2，保持默认值0，所有轴均不待机
	mpu6050_writereg(MPU6050_SMPLRT_DIV, 0x09);		//采样率分频寄存器，配置采样率
	mpu6050_writereg(MPU6050_CONFIG, 0x06);			//配置寄存器，配置DLPF
	mpu6050_writereg(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	mpu6050_writereg(MPU6050_ACCEL_CONFIG, 0x18);	//加速度计配置寄存器，选择满量程为±16g
}

uint8_t mpu6050_getID(void)
{
	return mpu6050_Readreg(MPU6050_WHO_AM_I);		
}

void mpu6050_getdata(struct mpu6050_data *mpu6050_data)
{
    uint8_t DataH, DataL;								//定义数据高8位和低8位的变量
	
	DataH = mpu6050_Readreg(MPU6050_ACCEL_XOUT_H);		//读取加速度计X轴的高8位数据
	DataL = mpu6050_Readreg(MPU6050_ACCEL_XOUT_L);		//读取加速度计X轴的低8位数据
	mpu6050_data->Accx = (DataH << 8) | DataL;			//数据拼接，通过输出参数返回
	
	DataH = mpu6050_Readreg(MPU6050_ACCEL_YOUT_H);		
	DataL = mpu6050_Readreg(MPU6050_ACCEL_YOUT_L);		
	mpu6050_data->Accy = (DataH << 8) | DataL;			
	
	DataH = mpu6050_Readreg(MPU6050_ACCEL_ZOUT_H);		
	DataL = mpu6050_Readreg(MPU6050_ACCEL_ZOUT_L);		
	mpu6050_data->Accz = (DataH << 8) | DataL;			
	
	DataH = mpu6050_Readreg(MPU6050_GYRO_XOUT_H);		//读取陀螺仪X轴的高8位数据
	DataL = mpu6050_Readreg(MPU6050_GYRO_XOUT_L);		//读取陀螺仪X轴的低8位数据
	mpu6050_data->GyroX = (DataH << 8) | DataL;			//数据拼接，通过输出参数返回
	
	DataH = mpu6050_Readreg(MPU6050_GYRO_YOUT_H);		
	DataL = mpu6050_Readreg(MPU6050_GYRO_YOUT_L);		
	mpu6050_data->Gyroy = (DataH << 8) | DataL;			
	
	DataH = mpu6050_Readreg(MPU6050_GYRO_ZOUT_H);		
	DataL = mpu6050_Readreg(MPU6050_GYRO_ZOUT_L);		
	mpu6050_data->GyroZ = (DataH << 8) | DataL;			
}

