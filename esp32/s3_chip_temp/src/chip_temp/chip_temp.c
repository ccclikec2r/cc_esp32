#include <esp_log.h>
#include<driver/temperature_sensor.h>

void chip_temp_init(void)
{
    temperature_sensor_handle_t temp_handle = NULL;
    temperature_sensor_config_t temperature_sensor_config = {
        .range_max = 50,
        .range_min = 20,
        .clk_src = TEMPERATURE_SENSOR_CLK_SRC_DEFAULT,
    };

    ESP_ERROR_CHECK(temperature_sensor_install(&temperature_sensor_config,&temp_handle));
    ESP_ERROR_CHECK(temperature_sensor_enable(temp_handle));

    float temp_data;
    ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_handle, &temp_data));
    printf("Temperature in %f °C\n", temp_data);

    ESP_ERROR_CHECK(temperature_sensor_disable(temp_handle));
}