#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include<chip_temp/chip_temp.h>

void app_main() 
{
    //neccessary init
    nvs_flash_init();//nvs init

    chip_temp_init();

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}