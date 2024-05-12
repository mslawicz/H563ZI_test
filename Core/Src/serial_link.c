#include "serial_link.h"
#include "stm32h5xx_hal.h"
#include "cmsis_os2.h"

uint8_t rxBuf[RX_BUF_SIZE];
uint8_t txBuf[TX_BUF_SIZE];

void serialLinkHandler(void)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
}