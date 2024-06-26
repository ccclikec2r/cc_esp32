#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "gpio/gpio_init.h"
#include "exit_init/exit_init.h"

void app_main() 
{
    printf("code start!");
    gpio_init();
    exit_init();
    while(1)
    {
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}