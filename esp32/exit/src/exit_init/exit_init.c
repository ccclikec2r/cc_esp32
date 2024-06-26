#include<driver/gpio.h>

void static io_config_key_isr_hander(void *arg)
{
    gpio_set_level(GPIO_NUM_1,!gpio_get_level(GPIO_NUM_1));
}

void exit_init(void)
{
    gpio_config_t io_config_key;
    io_config_key.mode = GPIO_MODE_INPUT;
    io_config_key.intr_type = GPIO_INTR_NEGEDGE;//exit type->falling
    io_config_key.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_config_key.pull_up_en = GPIO_PULLUP_ENABLE;
    io_config_key.pin_bit_mask = 1ULL << 21;
    gpio_config(&io_config_key);

    gpio_set_intr_type(GPIO_NUM_21,GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);//exit priority
    gpio_isr_handler_add(GPIO_NUM_21,io_config_key_isr_hander,NULL);
}