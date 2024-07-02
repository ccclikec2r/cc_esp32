#include<driver/ledc.h>
#include<driver/gpio.h>

void pwm_init(int freq,int resolution)
{
    ledc_timer_config_t mypwm = {
        .clk_cfg = LEDC_USE_APB_CLK,
        .duty_resolution = resolution,
        .freq_hz = freq,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_1,
    };
    ledc_timer_config(&mypwm);

    ledc_channel_config_t mypwm_channel = {
        .channel = LEDC_CHANNEL_1,
        .duty = 0,
        .gpio_num = GPIO_NUM_1,
        .intr_type = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_sel = LEDC_TIMER_1,
    };
    ledc_channel_config(&mypwm_channel);   
}

void pwm_set_duty(uint16_t duty)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_1,duty); 
    ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_1); 
}