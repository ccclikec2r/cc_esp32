#include<stdio.h>
#include<driver/gpio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

void app_main(void) 
{
    gpio_config_t io_config;
    io_config.mode = GPIO_MODE_DEF_OUTPUT;
    io_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_config.pull_up_en = GPIO_PULLUP_DISABLE;
    io_config.pin_bit_mask = 1ULL << 22;//mask->pin
    gpio_config(&io_config);
    gpio_set_level(GPIO_NUM_22 ,1);
    while(1)
    {
        gpio_set_level(GPIO_NUM_22,1);
        vTaskDelay(500/portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM_22,0);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}