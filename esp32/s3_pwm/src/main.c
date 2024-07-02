#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include<driver/ledc.h>
#include<driver/gpio.h>
#include<PWM/PWM_init.h>


void app_main() 
{
    //neccessary init
    nvs_flash_init();//nvs init

    pwm_init(1000,10);
    
    while(1)
    {
        for(int i = 0 ; i < 1000 ; i+=5)
        {
            pwm_set_duty(i);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        for(int j = 1000; j>5;j-=5)
        {
            pwm_set_duty(j);
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}