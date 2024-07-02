#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_flash.h"
#include <esp_log.h>
#include <freertos/queue.h>
#include<freertos/semphr.h>


typedef struct people
{
    int age;
    int num;
}ple;

QueueHandle_t myqueue = NULL;

void taskA(void* param)
{
    ESP_LOGI("taskA","ready!");
    ple receivedata ;
    BaseType_t queue_state;
    while (1)
    {
        queue_state = xQueueReceive(myqueue,&receivedata,10);
        if(queue_state != pdFALSE)
        {
            printf("queue: %d\n",receivedata.num);
            //vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

void taskB(void* param)
{
    ESP_LOGI("taskB","ready!");

    ple senddata = {
        .age = 18,
        .num = 1,
    };
    BaseType_t queue_state;
    while(1)
    {
        senddata.num +=1;
        queue_state = xQueueSend(myqueue,&senddata,10);
        if(queue_state != pdFALSE)
        {
            printf("send done\n");
        }

        if(senddata.num == 8)
        {
            senddata.num = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    myqueue = xQueueCreate(5,sizeof(ple));

    TaskHandle_t taskA_handle = NULL;
    TaskHandle_t taskB_handle = NULL;
    
    xTaskCreatePinnedToCore(taskA,"task1",1024*2,NULL,1,&taskA_handle,0);
    xTaskCreatePinnedToCore(taskB,"task2",1024*2,NULL,1,&taskB_handle,1);

    BaseType_t A_stack = uxTaskGetStackHighWaterMark(taskA_handle);
    BaseType_t B_stack = uxTaskGetStackHighWaterMark(taskB_handle);

    //static char pc_state[512] = {0};

    while(1)
    {
        printf("TaskA remain stack: %d\n",A_stack);
        printf("TaskB remain stack: %d\n",B_stack);

        // vTaskList(pc_state);
        // printf("----------------------------------\n");
        // printf("Name    State    Priority    Stack    Num\n");
        // printf("%s\n",pc_state);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}