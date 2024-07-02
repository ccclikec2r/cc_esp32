#include<esp_wifi.h>
#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<nvs_flash.h>

void test_esp_event_cb(void* event_handler_arg, esp_event_base_t event_base,int32_t event_id,void* event_data)
{
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)//wifi event and sta start
    {
        esp_wifi_connect();
    }
    else if(event_base == IP_EVENT && event_id == ESP_EVENT_ANY_ID)//ip event
    {
        ip_event_got_ip_t* getinfostruct = (ip_event_got_ip_t*)event_data;
        esp_ip4_addr_t ip = getinfostruct->ip_info.ip;
        printf("ip address: "IPSTR "\n",IP2STR(&ip));
    }
}

void wifi_sta(void) 
{
    
    //enroll event callback ->default
    esp_event_handler_instance_t wifi_event_handler;
    esp_event_handler_instance_register(WIFI_EVENT,
                                            ESP_EVENT_ANY_ID,
                                            test_esp_event_cb,
                                            NULL,
                                            &wifi_event_handler);

    esp_event_handler_instance_t ip_event_handler;
    esp_event_handler_instance_register(IP_EVENT,
                                            IP_EVENT_ETH_GOT_IP,
                                            test_esp_event_cb,
                                            NULL,
                                            &ip_event_handler);

    wifi_init_config_t config  = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&config);

    esp_wifi_set_mode(WIFI_MODE_STA);
   
    wifi_config_t wifi_config = {
        .sta = {
                .ssid = "imissu",
                .password = "123321123",
        },
    };

    esp_wifi_set_config(WIFI_IF_STA,&wifi_config);

    esp_wifi_start();
}