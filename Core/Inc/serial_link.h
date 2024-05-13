#ifndef __SERIAL_LINK_H
#define __SERIAL_LINK_H

#include "stm32h5xx_hal.h"

#define RX_BUF_SIZE 30
#define TX_BUF_SIZE 30

extern void serialLinkHandler(void);
extern UART_HandleTypeDef* pSerialLinkUart;
extern DMA_HandleTypeDef* pSerialLink_GPDMA_Channel_RX;


#endif /* __SERIAL_LINK_H */