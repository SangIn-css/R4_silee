#ifndef __COM_H__
#define __COM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void COM_Init(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c);
void COM_OnRxChar(uint8_t ch);

#ifdef __cplusplus
}
#endif

#endif
