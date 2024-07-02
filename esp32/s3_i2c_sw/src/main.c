#include  <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include <driver/gpio.h>
#include<i2c/i2c_init.h>
#include<MPU6050/mpu6050_init.h>

void app_main(void)
{
    esp_err_t ret;

    ret = nvs_flash_init(); /* 初始化 NVS */
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    mpu6050_init();

    struct mpu6050_data cc;

    while(1)
    {
        mpu6050_getdata(&cc);
        uint8_t id = mpu6050_getID();
        printf("id: %d\n",id);
        printf("Ax: %d AY: %d Az: %d\n",cc.Accx,cc.Accy,cc.Accz);
        printf("Gx: %d GY: %d Gz: %d\n",cc.GyroX,cc.Gyroy,cc.GyroZ);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}