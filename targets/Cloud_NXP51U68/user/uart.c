

#include "fsl_device_registers.h"
#include "fsl_usart.h"
#include "board.h"
#include "pin_mux.h"

#define BOARD_UART          USART0
#define BOARD_UART_BAUDRATE 115200
#define BOARD_UART_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm0)

#define LOS_OS   1

#ifdef LOS_OS

#else
void TaskDelay(int time)
{

    volatile int i;
    while(time > 0)
    {
        i = 10000;
        while(i-->0);
    } 
    return;
}

#endif

status_t uart_init(VOID)
{
    status_t result; 
    uint32_t srcFreq = 0;
    usart_config_t usart_config;
    USART_GetDefaultConfig(&usart_config);
    srcFreq = BOARD_UART_CLK_FREQ;
    usart_config.baudRate_Bps = BOARD_UART_BAUDRATE;
    USART_Init(BOARD_UART, &usart_config, srcFreq);
    return result;
}
int uart_read(uint8_t *buf,size_t len,int timeout)
{
    int ret = 0;
    ret = USART_ReadBlockingTimeout(BOARD_UART,buf,len,timeout);
    return ret;
}
int uart_write(uint8_t *buf,size_t len)
{
    USART_WriteBlocking(BOARD_UART,buf,len);
    return len;
}



















