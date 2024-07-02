#include <driver/uart.h>
#include  <driver/gpio.h>
#include <string.h>

#define RX_BUF_SIZE 1024

QueueHandle_t myqueue;

void uart0_init(void)
{
     uart_config_t myuart = {
        .baud_rate = 115200,
        .data_bits = 8,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .parity = UART_PARITY_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT,
        .stop_bits = UART_STOP_BITS_1,
    };
    uart_param_config(UART_NUM_0,&myuart);

    uart_set_pin(UART_NUM_0,GPIO_NUM_43,GPIO_NUM_44,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);

    uart_driver_install(UART_NUM_0,RX_BUF_SIZE * 3,RX_BUF_SIZE * 3,10,&myqueue,0);
}

void uart0_receive(void)
{
    char receive_buffer[RX_BUF_SIZE] = {0};
    uint32_t len = 0;
    uart_get_buffered_data_len(UART_NUM_0,(size_t *)&len);
    if(uart_read_bytes(UART_NUM_0,(void *)receive_buffer,len,100) !=-1)
    {
         printf("receive data : %s\n",receive_buffer);
    }
    
}