#include  <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include<driver/i2c_master.h>
#include "driver/i2c_slave.h"
#include<i2c/i2c_init.h>
#include<gpio/gpio_init.h>

void app_main(void)
{
    esp_err_t ret;

    ret = nvs_flash_init(); /* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    
    i2c_init();
    gpio_init();

    while(1)
    {
        bool kk = i2c_receive();
        if(kk == true)
        {
            gpio_set_level(GPIO_NUM_1,!gpio_get_level(GPIO_NUM_1));
            printf("read data: %x %x\n",read_buffer[0],read_buffer[1]);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}