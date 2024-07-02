#include<i2c/i2c_init.h>
#include<stdio.h>

#define ap3216c_Address 0x1E

struct ap3216c_data
{
    uint16_t ir;
    uint16_t als;
    uint16_t ps;
};

void ap3216c_writereg(uint8_t RegAddress,uint8_t data)
{
    i2c_start();
    i2c_sendbyte(ap3216c_Address << 1 | 0);//0x3c
    i2c_receiveAck();
    i2c_sendbyte(RegAddress);
    i2c_receiveAck();
    i2c_sendbyte(data);
    i2c_receiveAck();
    i2c_stop();
}

uint8_t ap3216c_Readreg(int8_t RegAddress)
{
    i2c_start();
    i2c_sendbyte(ap3216c_Address << 1 | 0);
    i2c_receiveAck();
    i2c_sendbyte(RegAddress);
    i2c_receiveAck();
    
    i2c_start();
    i2c_sendbyte(ap3216c_Address << 1 | 1);//0x3D
    i2c_receiveAck();
    uint8_t data = i2c_receivebyte();
    i2c_sendAck(1);
    i2c_stop();

    return data;
}

void ap3216c_init(void)
{
    i2c_gpio_init();

    ap3216c_writereg(0x00,0x04);//reset
    for(int i =0 ;i<50;i++);
    ap3216c_writereg(0x00,0x03);

    if(ap3216c_Readreg(0x00) != 0x03)
    {
        printf("AP3216C init error !\n");
    }
    printf("AP3216C ready !\n");

}

void ap3216c_getdata(struct ap3216c_data *data)
{
    uint8_t buf[6];
    
    for (uint8_t i = 0; i < 6; i++)
    {
        buf[i] = ap3216c_Readreg(0X0A + i); //0X0A->IR_LOW  0X0B->IR_HIGH ...
    }

    if (buf[0] & 0X80)
    {
        data->ir = 0; /* IR_OF 位为 1,则数据无效 */
    }
    else
    {
        data->ir = ((uint16_t)buf[1] << 2) | (buf[0] & 0X03);/* 读取 IR 传感器数据 */ //|used to lump data
    }
    data->als = ((uint16_t)buf[3] << 8) | buf[2]; /* 读取 ALS 传感器数据 */
    if (buf[4] & 0x40)
    {
        data->ps = 0; /* ps_OF 位为 1,则数据无效 */
    }
    else
    {
        /* 读取 PS 传感器的数据 */
        data->ps = ((uint16_t)(buf[5] & 0X3F) << 4) | (buf[4] & 0X0F);
    }

}

