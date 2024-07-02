#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_flash.h"
#include <esp_log.h>
#include <freertos/queue.h>

const char *name = "cc";

void taskA(void* param)
{
    char *text = (char *)param;
     while (1)
    {
        ESP_LOGI("taskA","i miss u");
        printf("taskA get data: %s\n",text);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

typedef struct people
{
    char *name;
    int age ;
    int num ; 
}people;

people cc = {
    .age = 18,
    .num = 135,
    .name = "cc",
};

void taskB(void* param)
{
    people *kk;
    kk = (people*)param;

    while(1)
    {
        ESP_LOGI("taskB","me too");
        printf("taskB get data: \n");
        printf("               name: %s\n",kk->name);
        printf("                age: %d\n",kk->age);
        printf("                num: %d\n",kk->num);
        vTaskDelay(pdMS_TO_TICKS(2000));

        vTaskDelete(NULL);
    }
}

void app_main(void)
{
    TaskHandle_t taskA_handle = NULL;
    TaskHandle_t taskB_handle;
    xTaskCreatePinnedToCore(taskA,"task1",2048,(void *)name,1,&taskA_handle,1);
    xTaskCreatePinnedToCore(taskB,"task2",2048,(void*)&cc,1,&taskB_handle,0);

    BaseType_t A_core = xTaskGetCoreID(taskA_handle);
    BaseType_t B_core = xTaskGetCoreID(taskB_handle);

    BaseType_t A_priority = uxTaskPriorityGet(taskA_handle);
    BaseType_t B_priority = uxTaskPriorityGet(taskB_handle);

    printf("taskA core : %d\n",A_core);
    printf("taskB core : %d\n",B_core);

    printf("taskA Priority : %d\n",A_priority);
    printf("taskB Priority : %d\n",B_priority);

    vTaskPrioritySet(taskA_handle,2);
    BaseType_t NEW_A_priority = uxTaskPriorityGet(taskA_handle);
    printf("New taskA Priority : %d\n",NEW_A_priority);

    //test to thrift memory
    UBaseType_t A_stack = uxTaskGetStackHighWaterMark(taskA_handle);
    UBaseType_t B_stack = uxTaskGetStackHighWaterMark(taskB_handle);

    printf("taskA remian stack : %d\n",A_stack);
    printf("taskB remain stack : %d\n",B_stack);

    /*need to menucofnig config two macro*/
    // static char task_stat[512] = {0};
    // vTaskList(task_stat);
    // printf("%s\n",task_stat);

    if(taskA_handle!=NULL)
    {
        vTaskDelete(taskA_handle);
    }
  
}