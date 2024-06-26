#include  <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include <driver/gpio.h>

#define LED GPIO_NUM_1
#define key GPIO_NUM_0

void key_test(void *arg)
{
    gpio_set_level(LED,!gpio_get_level(LED));
}

void app_main(void)
{
    esp_err_t ret;

    ret = nvs_flash_init(); /* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    
    gpio_config_t led_config;
    led_config.mode = GPIO_MODE_INPUT_OUTPUT;
    led_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    led_config.pull_up_en = GPIO_PULLUP_ENABLE;
    led_config.intr_type = GPIO_INTR_DISABLE;
    led_config.pin_bit_mask = 1ULL << LED;
    
    gpio_config(&led_config);
    gpio_set_level(LED,1);

    gpio_config_t key_config;
    key_config.mode = GPIO_MODE_INPUT;
    key_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    key_config.pull_up_en = GPIO_PULLUP_ENABLE;
    key_config.intr_type = GPIO_INTR_NEGEDGE;
    key_config.pin_bit_mask = 1ULL << key;
    gpio_config(&key_config);
    
    gpio_set_intr_type(key,GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);
    gpio_isr_handler_add(key,key_test,NULL);
    gpio_intr_enable(key);

    while(1)
    {
        // gpio_set_level(LED,!gpio_get_level(LED));
        vTaskDelay(100);
    }
}