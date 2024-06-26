#include <driver/gpio.h>
#include<driver/i2c_master.h>
#include "driver/i2c_slave.h"
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

#define I2C_MASTER_SCL_IO GPIO_NUM_42
#define I2C_MASTER_SDA_IO GPIO_NUM_41

i2c_master_bus_handle_t i2c_master_bus_handle;
i2c_master_dev_handle_t i2c_master_dev_handle;

uint8_t write_buffer[] = {0x00};
uint8_t read_buffer[2];

void i2c_init(void)
{
    //master bus param
    i2c_master_bus_config_t i2c_masterbus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_new_master_bus(&i2c_masterbus_config,&i2c_master_bus_handle);

    //slave device
    i2c_device_config_t i2c_24c02_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = 0xA1,
        .scl_speed_hz = 100000,
    };
    
    i2c_master_bus_add_device(i2c_master_bus_handle,&i2c_24c02_config,&i2c_master_dev_handle);
}

bool i2c_receive(void)
{
    esp_err_t cc = i2c_master_transmit_receive(i2c_master_dev_handle,
                                                write_buffer,sizeof(write_buffer),
                                                read_buffer,sizeof(read_buffer),
                                                                                -1);
    if(cc == ESP_OK)
    {
        return true;
    }
    return false;
}