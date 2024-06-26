#include<stdio.h>
#include<driver/gpio.h>
#include<driver/gptimer.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<esp_log.h>

//callback
bool test_alarm_cb_t(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
{
    gpio_set_level(GPIO_NUM_1,!gpio_get_level(GPIO_NUM_1));
    //ESP_LOGI("Timer:","ON");
    //printf("On !");
    return true;
}

void timer_init(void)
{
    gptimer_handle_t gptimer = NULL; //handle
    gptimer_config_t gptimer_config;
    gptimer_config.clk_src = GPTIMER_CLK_SRC_DEFAULT;
    gptimer_config.direction = GPTIMER_COUNT_UP;
    //gptimer_config.flags = ;
    gptimer_config.intr_priority = 1;
    gptimer_config.resolution_hz = 1*1000*1000;//1mhz->1s

    gptimer_new_timer(&gptimer_config,&gptimer);

    gptimer_alarm_config_t gptimer_alarm;
    gptimer_alarm.alarm_count = 1*1000*1000;
    gptimer_alarm.flags.auto_reload_on_alarm = true;
    gptimer_alarm.reload_count = 0;    
    gptimer_set_alarm_action(gptimer,&gptimer_alarm);

    const gptimer_event_callbacks_t abc ={
        .on_alarm = test_alarm_cb_t,
    };
    
    gptimer_register_event_callbacks(gptimer,&abc,NULL);

    gptimer_enable(gptimer);
    gptimer_start(gptimer);
}
 
