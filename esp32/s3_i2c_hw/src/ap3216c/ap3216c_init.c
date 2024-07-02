#include<stdio.h>
#include<driver/i2c_master.h>
#include<driver/i2c_slave.h>
#include<driver/gpio.h>

#define i2c0_scl GPIO_NUM_42
#define i2c0_sda GPIO_NUM_41
#define ap3216c_Adress 0x1E
// #define ap3216c_Adress_read  0x3D
// #define ap3216c_Adress_write 0x3C

i2c_master_bus_handle_t ap3216c_i2c_bus_handle;
i2c_master_dev_handle_t ap3216c_i2c_dev_handle;

uint8_t write = 0X3C;
uint8_t read = 0X3D;

struct ap3216c_data
{
    uint16_t ir;//infrared
    uint16_t als;//light
    uint16_t ps;//distance
};

// void mpu6050_writereg(uint8_t RegAddress,uint8_t data)
// {
//     i2c_start();
//     i2c_sendbyte(ap3216c_Adress);
//     i2c_receiveAck();
//     i2c_sendbyte(RegAddress);
//     i2c_receiveAck();
//     i2c_sendbyte(data);
//     i2c_receiveAck();
//     i2c_stop();
// }

// uint8_t mpu6050_Readreg(int8_t RegAddress)
// {
//     i2c_start();
//     i2c_sendbyte(ap3216c_Adress);
//     i2c_receiveAck();
//     i2c_sendbyte(RegAddress);
//     i2c_receiveAck();
    
//     i2c_start();
//     i2c_sendbyte(ap3216c_Adress | 0x01);
//     i2c_receiveAck();
//     uint8_t data = i2c_receivebyte();
//     i2c_sendAck(1);
//     i2c_stop();
//     return data;
// }

uint8_t ap3216c_ReadReg(uint8_t RegAddress)
{
   uint8_t data;
   i2c_master_transmit(ap3216c_i2c_dev_handle,&write,sizeof(write),-1);
   i2c_master_transmit_receive(ap3216c_i2c_dev_handle,&RegAddress,sizeof(RegAddress),&data,sizeof(data),-1);
   return data;
}

void ap3216c_WriteReg(uint8_t RegAddress,uint8_t data)
{
    i2c_master_transmit(ap3216c_i2c_dev_handle,&write,sizeof(write),-1);
    i2c_master_transmit(ap3216c_i2c_dev_handle,&RegAddress,sizeof(RegAddress),-1);
    i2c_master_transmit(ap3216c_i2c_dev_handle,&data,sizeof(data),-1);
}

void ap3216c_init(void)
{
    i2c_master_bus_config_t ap3216c_i2c_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .flags.enable_internal_pullup = 1,
        .glitch_ignore_cnt = 7,
        .i2c_port = I2C_NUM_0,
        .intr_priority = true,
        .scl_io_num = i2c0_scl,
        .sda_io_num = i2c0_sda,
        //.trans_queue_depth = ,
    };
    i2c_new_master_bus(&ap3216c_i2c_bus_config,&ap3216c_i2c_bus_handle);

    i2c_device_config_t ap3216c_dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = ap3216c_Adress,
        .scl_speed_hz = 400000,
    };
    i2c_master_bus_add_device(ap3216c_i2c_bus_handle,&ap3216c_dev_config,&ap3216c_i2c_dev_handle);

    ap3216c_WriteReg(0x00,0x04);//sw reset
    for(int i =0 ;i<50;i++);
    ap3216c_WriteReg(0x00,0x03);//config mode

    if(ap3216c_ReadReg(0x00) != 0x03)
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
        buf[i] = ap3216c_ReadReg(0X0A + i); //0X0A->IR_LOW  0X0B->IR_HIGH ...
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
