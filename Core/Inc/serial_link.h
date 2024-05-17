#ifndef __SERIAL_LINK_H
#define __SERIAL_LINK_H

#include "stm32h5xx_hal.h"

#define RX_BUF_SIZE 18
#define TX_BUF_SIZE 50
#define COM_BUF_SIZE    100

extern void serialLinkHandler(void);
extern UART_HandleTypeDef* pSerialLinkUart;
extern DMA_HandleTypeDef* pSerialLink_GPDMA_Channel_RX;
extern UART_HandleTypeDef* pComUart;


#endif /* __SERIAL_LINK_H */