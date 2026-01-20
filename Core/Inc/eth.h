#ifndef __APD_H__
#define __APD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define USE_SPI1_DIRECT 1 
#define SIMR 0x0018

void eth_Write_Data();
void eth_Write_1Byte(uint16_t addr, uint8_t BSB, uint8_t data);
void eth_Write_nByte(uint16_t addr, uint8_t BSB, uint8_t data)

#ifdef __cplusplus
}
#endif

#endif
