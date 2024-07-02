#include<driver/gpio.h>

#define i2c_scl_pin GPIO_NUM_42
#define i2c_sda_pin GPIO_NUM_41


void i2c_gpio_init(void)
{
    gpio_config_t io_config_i2c;
    io_config_i2c.mode = GPIO_MODE_INPUT_OUTPUT_OD;
    io_config_i2c.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_config_i2c.pull_up_en = GPIO_PULLUP_DISABLE;
    io_config_i2c.pin_bit_mask = (1ULL << i2c_scl_pin) | (1ULL << i2c_sda_pin) ;
    
    gpio_config(&io_config_i2c);   

    gpio_set_level(i2c_scl_pin,1); 
    gpio_set_level(i2c_sda_pin,1);
}

void i2c_sda_S(int k)
{
    gpio_set_level(i2c_sda_pin,k);
    //for(int i = 0;i < 100;i++);
    //vTaskDelay(pdMS_TO_TICKS(10));
}

void i2c_scl_S(int m)
{
    gpio_set_level(i2c_scl_pin,m);
    //for(int i = 0;i < 100;i++);
    //vTaskDelay(pdMS_TO_TICKS(10));
}

uint8_t  i2c_scl_R(void)
{
    return gpio_get_level(i2c_scl_pin);
}
uint8_t  i2c_sda_R(void)
{
    return gpio_get_level(i2c_sda_pin);
}

void i2c_start(void)
{
    i2c_sda_S(1);
    i2c_scl_S(1);
    i2c_sda_S(0);
    i2c_scl_S(0);
}

void i2c_stop(void)
{
    i2c_sda_S(0);
    i2c_scl_S(1);
    i2c_sda_S(1);
}

void i2c_sendbyte(uint8_t Byte)
{
    for(int i = 0;i<8;i++)
    {
        i2c_sda_S(Byte & (0x80 >> i));
        i2c_scl_S(1);
        i2c_scl_S(0);
    }
}

uint8_t i2c_receivebyte(void)
{
    uint8_t byte = 0x00;
    i2c_sda_S(1);
    
    for(int j = 0;j<8;j++)
    {
        i2c_scl_S(1);
        if(i2c_sda_R() == 1)
        {
             byte |= (0x80 >> j);
        }
        i2c_scl_S(0);
    }
    return byte;
}

void i2c_sendAck(uint8_t AckBit)
{
    i2c_sda_S(AckBit);
    i2c_scl_S(1);
    i2c_scl_S(0);
}

uint8_t i2c_receiveAck(void)
{
    uint8_t Ackbit ;
    i2c_sda_S(1);
    i2c_scl_S(1);
    Ackbit = i2c_sda_R();
    i2c_scl_S(0);
    return Ackbit;
}