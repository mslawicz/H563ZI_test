#include "serial_link.h"
#include "cmsis_os2.h"
#include "stdio.h"
#include "string.h"
#include "main.h"

uint8_t rxBuf[RX_BUF_SIZE];
uint8_t txBuf[TX_BUF_SIZE];
uint8_t comTxBuf[COM_BUF_SIZE];

UART_HandleTypeDef* pSerialLinkUart = NULL;
DMA_HandleTypeDef* pSerialLink_GPDMA_Channel_RX = NULL;
UART_HandleTypeDef* pComUart = NULL;

void requestDmaReception(void);

void serialLinkHandler(void)
{
    uint8_t counter = 0;
    requestDmaReception();
    /* Infinite loop */
    for(;;)
    {
        int n = sprintf((char*)txBuf, "Sending very long message #%u\r\n", counter++);
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
    /* Size provides the number of received characters since the last buffer overrun interrupt */
    static uint16_t dataIdx = 0;    /* index of the current received data */
    static uint16_t comIdx = 0;     /* current wr index in the com buffer */
    if(huart == pSerialLinkUart)
    {
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST1_Pin, GPIO_PIN_SET);
        uint16_t dataSize = Size - dataIdx;     /* size of the current received data */
        memcpy(comTxBuf+comIdx, rxBuf+dataIdx, dataSize);
        dataIdx = Size % RX_BUF_SIZE;
        comIdx += dataSize;     /* update com index with the number of current received data */
        if(dataIdx > 0)
        {
            /* propably the idle condition occured */
            /* it won't be executed here when the idle condition and buffer overrun occure at the same time */
            /* in such a case 2 messages will be sent to COM link next time */
            HAL_GPIO_WritePin(TEST2_GPIO_Port, TEST2_Pin, GPIO_PIN_SET);
            HAL_UART_Transmit_DMA(pComUart, comTxBuf, comIdx);
            comIdx = 0;
            HAL_GPIO_WritePin(TEST2_GPIO_Port, TEST2_Pin, GPIO_PIN_RESET);
        }
        HAL_GPIO_WritePin(TEST1_GPIO_Port, TEST1_Pin, GPIO_PIN_RESET);
    }
}

void requestDmaReception(void)
{
    /* request reception of a specified number of characters or to idle state */
    HAL_UARTEx_ReceiveToIdle_DMA(pSerialLinkUart, rxBuf, RX_BUF_SIZE);
    /* disable half transfer interrupt just after the reception request */
    __HAL_DMA_DISABLE_IT(pSerialLink_GPDMA_Channel_RX, DMA_IT_HT);    
}

/**
  * @brief  BSP Push Button callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None
  */
void BSP_PB_Callback(Button_TypeDef Button)
{
    if(Button == BUTTON_USER)
    {
        HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
    }
}