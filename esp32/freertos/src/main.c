#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<esp_log.h>

int testnum[] = {1,2,3};
static const char *ptext = "me too";

void taskA(void *param)
{
    int *pint;
    pint = (int *)param;
    ESP_LOGI("taskA","i miss u");
    while(1)
    {
        for(int i = 0;i < 3;i++)
        {
             printf("getnum: %d\n",*(pint+i));
             vTaskDelay(pdMS_TO_TICKS(1000));//convert systick to ms
        }
        
    }
}

void taskB(void *param)
{
    char *ptext_task;
    ptext_task = (char *)param;
    
    printf("message: %s\n",ptext_task);

    vTaskDelay(pdMS_TO_TICKS(3000));
    //delte method 1
    vTaskDelete(NULL);
}

void app_main() 
{
    //xTaskCreatePinnedToCore(function,task's name,stack byte,send to task,priority,handle,core)
    TaskHandle_t myhandle = NULL; 
    xTaskCreatePinnedToCore(taskA,"hi",2048,(void *)testnum,1,&myhandle,1);
    xTaskCreatePinnedToCore(taskB,"hello",2048,(void *)ptext,2,NULL,1);
    //delete method 2
    vTaskDelay(pdMS_TO_TICKS(5000));
    if(myhandle!=NULL)
    {
        vTaskDelete(myhandle);
    }
}