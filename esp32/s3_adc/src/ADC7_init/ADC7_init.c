#include<hal/adc_types.h>
#include<esp_adc/adc_oneshot.h>

adc_oneshot_unit_handle_t adc_handle = NULL;

void adc7_init(void)
{
    adc_oneshot_unit_init_cfg_t adc7_config = {
        .clk_src = ADC_RTC_CLK_SRC_RC_FAST,
        .ulp_mode = ADC_ULP_MODE_RISCV,
        .unit_id = ADC_UNIT_1,
    };

    adc_oneshot_new_unit(&adc7_config,&adc_handle);

    adc_oneshot_chan_cfg_t adc7_chan = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };

    adc_oneshot_config_channel(adc_handle,ADC_CHANNEL_7,&adc7_chan);
   
}

int adc7_getval(int times)
{
    int data_buffer[times-1];
    int data_sum = 0;
    
    for(int i = 0 ;i < times;i++)
    {
        adc_oneshot_read(adc_handle,ADC_CHANNEL_7,&data_buffer[i]);
        data_sum += data_buffer[i];
    }
    int data_average = data_sum/times; 
    return data_average;
}