#include  <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include<i2c/i2c_init.h>
#include<OLED/Hardware/OLED.h>
#include<OLED/Hardware/OLED_Data.h>

void app_main(void)
{
    esp_err_t ret;

    ret = nvs_flash_init(); /* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
   
    OLED_Init();

    //OLED_ShowString(0,0,"hello world!",OLED_8X16);
    //OLED_ShowChinese(0,20,"你");
    OLED_ShowImage(0,0,16,16,Diode);
    OLED_Update();

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
