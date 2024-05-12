#include "serial_link.h"
#include "cmsis_os2.h"
#include "stdio.h"

uint8_t rxBuf[RX_BUF_SIZE];
uint8_t txBuf[TX_BUF_SIZE];

UART_HandleTypeDef* pSerialLinkUart = NULL;

void serialLinkHandler(void)
{
    uint8_t counter = 0;
    /* Infinite loop */
    for(;;)
    {
        int n = sprintf((char*)txBuf, "Sending message #%u.", counter++);
        if(n>0)
        {
            HAL_UART_Transmit_DMA(pSerialLinkUart, txBuf, n);
        }
        osDelay(100);
    }
}