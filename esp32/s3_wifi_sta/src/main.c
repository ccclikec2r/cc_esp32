#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <wifi_provisioning/manager.h>
#include <wifi_provisioning/scheme_ble.h>
#include <esp_log.h>
#include<wifi_prov/wifi_prov.h>
#include<wifi_sta/wifi_sta.h>

void app_main() 
{
    //neccessary init
    nvs_flash_init();//nvs init
    esp_netif_init();//network init
    esp_event_loop_create_default();//loop event
    esp_netif_create_default_wifi_sta();//sta mode port

    wifi_sta();

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}