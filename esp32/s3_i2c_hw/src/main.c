#include  <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include <ap3216c/ap3216c_init.h>

void app_main(void)
{
    esp_err_t ret;

    ret = nvs_flash_init(); /* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ap3216c_init();
    
    struct ap3216c_data cc = {0};
   
    while(1)
    {
       ap3216c_getdata(&cc);
       printf("als: %d\n ir: %d\n ps: %d\n",cc.als,cc.ir,cc.ps);

       vTaskDelay(pdMS_TO_TICKS(500));
    }
}
