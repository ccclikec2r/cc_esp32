#include  <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include <xl9555/xl9555_init.h>

void app_main(void)
{
    esp_err_t ret;

    ret = nvs_flash_init(); /* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

   xl9555_init();

    while(1)
    {
        uint8_t keyid = xl9555_key_scan(0);
        if(keyid == 1)
        {
            printf("k0\n");
        }
            
        if(keyid == 2)
        {
            printf("k1\n");
        }
        
        if(keyid == 3)
        {
            printf("k2\n");
        }
        if(keyid == 4)
        {
            printf("k3\n");
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}