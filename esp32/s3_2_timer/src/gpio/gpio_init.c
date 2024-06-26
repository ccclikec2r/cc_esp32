#include<driver/gpio.h>

void gpio_init(void)
{
    gpio_config_t io_config_led;
    io_config_led.mode = GPIO_MODE_INPUT_OUTPUT;
    io_config_led.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_config_led.pull_up_en = GPIO_PULLUP_DISABLE;
    io_config_led.intr_type = GPIO_INTR_DISABLE;
    io_config_led.pin_bit_mask = 1ULL << GPIO_NUM_1;//1(A) unsigned long long left 1 bit->1(A)1
    
    gpio_config(&io_config_led);

    gpio_set_level(GPIO_NUM_1,1);

}