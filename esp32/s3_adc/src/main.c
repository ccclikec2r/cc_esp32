#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include<hal/adc_types.h>
#include<esp_adc/adc_oneshot.h>
#include<ADC7_init/ADC7_init.h>

void app_main() 
{
    //neccessary init
    nvs_flash_init();//nvs init

    int raw_data = 0;

    adc7_init();
    while(1)
    {
        raw_data = adc7_getval(10);
        float conv_data = (float)raw_data * (3.3 / 4096); 
        printf("Raw val : %d\n",raw_data);
        printf("voltage : %.3f\n",conv_data);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}