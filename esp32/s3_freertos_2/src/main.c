#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_flash.h"
#include <esp_log.h>
#include <freertos/queue.h>

QueueHandle_t myqueue = NULL;

typedef struct people
{
    int age;
    int num;
}ple;

void taskA(void* param)
{
    ESP_LOGI("taskA","ready!");
    ple receivedata ;
    while (1)
    {
        if(xQueueReceive(myqueue,&receivedata,pdMS_TO_TICKS(100)))
        {
            ESP_LOGI("taskA","queue: %d\n",receivedata.num);
            //vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

void taskB(void* param)
{
    ESP_LOGI("taskB","ready!");
    ple senddata = {
        .age = 18,
        .num = 150,
    };
    
    while(1)
    {
        senddata.num +=1;
        xQueueSend(myqueue,&senddata,pdMS_TO_TICKS(100));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    myqueue = xQueueCreate(10,sizeof(ple));

    TaskHandle_t taskA_handle = NULL;
    TaskHandle_t taskB_handle = NULL;
    xTaskCreatePinnedToCore(taskA,"task1",2048,NULL,1,&taskA_handle,1);
    xTaskCreatePinnedToCore(taskB,"task2",2048,NULL,1,&taskB_handle,0);
  
    BaseType_t A_stack = uxTaskGetStackHighWaterMark(taskA_handle);
    BaseType_t B_stack = uxTaskGetStackHighWaterMark(taskB_handle);

    while(1)
    {
        printf("TaskA remain stack: %d\n",A_stack);
        printf("TaskB remain stack: %d\n",B_stack);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}