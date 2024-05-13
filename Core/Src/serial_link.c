#include "serial_link.h"
#include "cmsis_os2.h"
#include "stdio.h"
#include "main.h"

uint8_t rxBuf[RX_BUF_SIZE];
uint8_t txBuf[TX_BUF_SIZE];

UART_HandleTypeDef* pSerialLinkUart = NULL;
DMA_HandleTypeDef* pSerialLink_GPDMA_Channel_RX = NULL;

void requestDmaReception(void);

void serialLinkHandler(void)
{
    uint8_t counter = 0;
    requestDmaReception();
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
        UNUSED(Size);
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST1_Pin, GPIO_PIN_SET);
        requestDmaReception();
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST1_Pin, GPIO_PIN_RESET);
        /* Size provides the number of received characters */
    }
}

void requestDmaReception(void)
{
    /* request reception of a specified number of characters or to idle state */
    HAL_UARTEx_ReceiveToIdle_DMA(pSerialLinkUart, rxBuf, 15);
    /* disable half transfer interrupt just after the reception request */
    __HAL_DMA_DISABLE_IT(pSerialLink_GPDMA_Channel_RX, DMA_IT_HT);    
}