#include "serial_link.h"
#include "cmsis_os2.h"
#include "stdio.h"
#include "main.h"

uint8_t rxBuf[RX_BUF_SIZE];
uint8_t txBuf[TX_BUF_SIZE];

UART_HandleTypeDef* pSerialLinkUart = NULL;

void serialLinkHandler(void)
{
    uint8_t counter = 0;
    HAL_UART_Receive_DMA(pSerialLinkUart, rxBuf, 23);
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

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart == pSerialLinkUart)
    {
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST1_Pin, GPIO_PIN_SET);
        HAL_UART_Receive_DMA(pSerialLinkUart, rxBuf, 10);
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST1_Pin, GPIO_PIN_RESET);
    }
}