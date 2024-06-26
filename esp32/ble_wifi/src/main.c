#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <wifi_provisioning/manager.h>
#include <wifi_provisioning/scheme_ble.h>
#include <esp_log.h>


//wifi callback
void mywifi_callback(void* event_handler_arg,
                            esp_event_base_t event_base,
                            int32_t event_id,
                            void* event_data)
{
    if(WIFI_EVENT)
    {

    }
    else if(WIFI_PROV_EVENT)
    {
        switch (event_id)
        {
        case WIFI_PROV_START:
            printf("prov start\n");
            break;
        case WIFI_PROV_CRED_RECV:
            wifi_sta_config_t *wifi_sta_cfg = (wifi_sta_config_t *)event_data;
            ESP_LOGI("prov","receive: "
                            "\n\tSSID :%s\n\tPassword : %s \n",
                            (const char *)wifi_sta_cfg->ssid,
                            (const char *)wifi_sta_cfg->password);
            break;
        case WIFI_PROV_CRED_SUCCESS:
            ESP_LOGI("prov","prov success");
            break;
        case WIFI_PROV_END:
            wifi_prov_mgr_deinit();
            break;;
        default:
            break;
        }
        
    }
    else if(event_base == IP_EVENT) 
    {
            
    }
    
}

void app_main() 
{
    //neccessary init
    nvs_flash_init();//nvs init
    esp_netif_init();//network init
    esp_event_loop_create_default();//loop event
 
    esp_netif_create_default_wifi_sta();//sta mode port

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();//usual use default
    esp_wifi_init(&config);


    //enroll wifi event callback
    esp_event_handler_register(WIFI_EVENT,//all wifi event
                                             ESP_EVENT_ANY_ID,//correspondence event
                                             mywifi_callback,//wifi callback
                                             NULL);
    //enroll provision wifi event callback
    esp_event_handler_register(WIFI_PROV_EVENT,//provision wifi event
                                             ESP_EVENT_ANY_ID,//correspondence event
                                             mywifi_callback,//wifi callback
                                             NULL);
    //enroll ip event callback
    esp_event_handler_register(IP_EVENT,//IP event
                                             IP_EVENT_STA_GOT_IP,//correspondence event
                                             mywifi_callback,//wifi callback
                                             NULL);//send to param                                         

    wifi_prov_mgr_config_t prov_mgr_config ={
        .scheme = wifi_prov_scheme_ble,
        .scheme_event_handler = WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BLE,
        
    };
    //ESP_ERROR_CHECK( wifi_prov_mgr_init(prov_mgr_config) );
    wifi_prov_mgr_init(prov_mgr_config);
    
    wifi_prov_mgr_start_provisioning(WIFI_PROV_SECURITY_1,"123","PROV_cc",NULL);

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}