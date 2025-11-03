#ifndef __TDC_H__
#define __TDC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define TDC_CONF1_REG	0x00
#define TDC_CONF2_REG	0x01
#define C = 300000000;

void TDC_Init(SPI_HandleTypeDef *hspi);
void TDC_Conf1_Init(SPI_HandleTypeDef *hspi);
void TDC_Conf2_Init(SPI_HandleTypeDef *hspi);


#ifdef __cplusplus
}
#endif

#endif
