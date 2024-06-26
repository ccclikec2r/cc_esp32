#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_flash.h"
#include <esp_log.h>
#include<freertos/queue.h>

void taskA(void* param)
{
     while (1)
    {
        ESP_LOGI("task1","i miss u");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

typedef struct people
{
    int age ;
    int num ; 
}people;

people cc = {
    .age = 18,
    .num = 135,
};

void taskB(void* param)
{
    people *kk;
    kk = (people*)param;

    while(1)
    {
        printf("age: %d\n",kk->age);
        printf("num: %d\n",kk->num);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    TaskHandle_t my_handle;
    xTaskCreatePinnedToCore(taskA,"task1",2048,NULL,1,&my_handle,1);
    xTaskCreatePinnedToCore(taskB,"task2",2048,(void*)&cc,1,NULL,0);
    if(my_handle!=NULL)
    {
        vTaskDelete(my_handle);
    }
  
}