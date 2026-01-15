#ifndef __APD_H__
#define __APD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define USE_SPI1_DIRECT 1 

void eth_Write_Data(uint8_t addr, uint8_t data)

#ifdef __cplusplus
}
#endif

#endif
