#include<stdio.h>
#include<driver/gpio.h>
#include<driver/gptimer.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include"timer_init/timer_init.h"
#include"gpio/gpio_init.h"
#include "nvs_flash.h"
#include "esp_system.h"

void app_main() 
{
    esp_err_t ret;
    ret = nvs_flash_init(); /* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }    

   gpio_init();
   timer_init();
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }   
}
