#include<i2c/i2c_init.h>
#include<stdio.h>
#include<driver/gpio.h>
#include<xl9555/xl9555_macro.h>

#define xl9555_Address 0x20

#define XL9555_INT_IO GPIO_NUM_40
#define XL9555_INT_IO_state gpio_get_level(XL9555_INT_IO)

#define KEY0_read xl9555_pin_read(KEY0_IO)
#define KEY1_read xl9555_pin_read(KEY1_IO)
#define KEY2_read xl9555_pin_read(KEY2_IO)
#define KEY3_read xl9555_pin_read(KEY3_IO)

void xl9555_Writereg(uint8_t RegAddress,uint8_t data)
{
    i2c_start();
    i2c_sendbyte(xl9555_Address << 1 | 0);
    i2c_receiveAck();
    i2c_sendbyte(RegAddress);
    i2c_receiveAck();
    i2c_sendbyte(data);
    i2c_receiveAck();
    i2c_stop();
}

uint8_t xl9555_Readreg(int8_t RegAddress)
{
    i2c_start();
    i2c_sendbyte(xl9555_Address << 1 | 0);
    i2c_receiveAck();
    i2c_sendbyte(RegAddress);
    i2c_receiveAck();
    
    i2c_start();
    i2c_sendbyte(xl9555_Address << 1 | 1);
    i2c_receiveAck();
    uint8_t data = i2c_receivebyte();
    i2c_sendAck(1);
    i2c_stop();
    return data;
}

int xl9555_pin_read(uint16_t pin)
{
    uint16_t ret;
    uint8_t r_data[2];
    
    r_data[0] = xl9555_Readreg(0x00); // 读取 XL9555 的 PIN0 寄存器
    r_data[1] = xl9555_Readreg(0x01); // 读取 XL9555 的 PIN1 寄存器
    ret = r_data[1] << 8 | r_data[0];
    
    return (ret & pin) ? 1 : 0; // 如果 pin 对应的引脚为高电平，则返回 1，否则返回 0
}

uint16_t xl9555_pin_write(uint16_t pin, int val) 
{
    uint8_t w_data[2];
    uint16_t temp = 0x0000;

    // 读取当前的数据
    w_data[0] = xl9555_Readreg(0x02);
    w_data[1] = xl9555_Readreg(0x03);

    // 根据pin和val更新数据
    if (pin <= 0x0080) 
    {
        if (val) {
            w_data[0] |= (uint8_t)(0xFF & pin);  // 设置相应的位
        } else {
            w_data[0] &= ~(uint8_t)(0xFF & pin); // 清除相应的位
        }
    } 
    else 
    {
        if (val) 
        {
            w_data[1] |= (uint8_t)(0xFF & (pin >> 8));  // 设置相应的位
        } 
        else 
        {
            w_data[1] &= ~(uint8_t)(0xFF & (pin >> 8)); // 清除相应的位
        }
    }
    // 将更新后的数据写回设备
    xl9555_Writereg(0x02, w_data[0]);
    xl9555_Writereg(0x03, w_data[1]);

    // 组合更新后的数据
    temp = ((uint16_t)w_data[1] << 8) | w_data[0];

    // 返回更新后的16位数据
    return temp;
}

void xl9555_init(void)
{
    i2c_gpio_init();

    gpio_config_t gpio_init_struct = {0};
    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;
    gpio_init_struct.mode = GPIO_MODE_INPUT;
    gpio_init_struct.pin_bit_mask = (1ull << XL9555_INT_IO);
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&gpio_init_struct); /* 配置 XL_INT 引脚 */
    /* 上电先读取一次清除中断标志 */
    xl9555_Readreg(0x00);

    xl9555_Writereg(0x06,0xF0);
    xl9555_Writereg(0x07,0x03);//config io mode

    xl9555_pin_write(BEEP_IO, 1);
    xl9555_pin_write(SPK_EN_IO, 1);
}

uint8_t xl9555_key_scan(uint8_t mode)
{
    uint8_t keyval = 0;
    static uint8_t key_up = 1;                                          /* 按键按松开标志 */

    if (mode)
    {
        key_up = 1;                                                     /* 支持连按 */
    }
    
    if (key_up && (KEY3_read == 0 || KEY2_read == 0 || KEY1_read == 0  || KEY0_read == 0 )) /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        for(int k = 0;k<100;k++);                                                 /* 去抖动 */
        key_up = 0;

        if (KEY3_read == 0)
        {
            keyval = 4;
        }

        if (KEY2_read == 0)
        {
            keyval = 3;
        }

        if (KEY1_read == 0)
        {
            keyval = 2;
        }

        if (KEY0_read == 0)
        {
            keyval = 1;
        }
    }
    else if (KEY3_read == 1 && KEY2_read == 1 && KEY1_read == 1 && KEY0_read == 1)      /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;                                                     
}
