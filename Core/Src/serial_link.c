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
    HAL_UARTEx_ReceiveToIdle_DMA(pSerialLinkUart, rxBuf, 15);
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
        HAL_UARTEx_ReceiveToIdle_DMA(pSerialLinkUart, rxBuf, 15);
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST1_Pin, GPIO_PIN_RESET);
    }
}

/**
  * @brief  Reception Event Callback (Rx event notification called after use of advanced reception service).
  * @param  huart UART handle
  * @param  Size  Number of data available in application reception buffer (indicates a position in
  *               reception buffer until which, data are available)
  * @retval None
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart == pSerialLinkUart)
    {
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST2_Pin, GPIO_PIN_SET);
        HAL_UARTEx_ReceiveToIdle_DMA(pSerialLinkUart, rxBuf, 15);
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST2_Pin, GPIO_PIN_RESET);
        if(Size == 7)
        {
            HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST2_Pin, GPIO_PIN_RESET);
        }
        else if(Size > 7)
        {
            HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST2_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST2_Pin, GPIO_PIN_RESET);
        }
    }
}