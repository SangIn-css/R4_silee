#ifndef __TDC_H__
#define __TDC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define TDC_CONF1_REG	0x00
#define TDC_CONF2_REG	0x01

#define TDC_TIME1_REG 	0x10
#define TDC_TIME2_REG	0x12

#define TDC_CAL1_REG	0x1B
#define TDC_CAL2_REG	0x1C

#define USE_SPI2_DIRECT 1

void TDC_Init();
void TDC_Conf1_Init();
void TDC_Conf2_Init();
void TDC_Write_Data(uint8_t addr, uint8_t data);
uint8_t TDC_Read_8(uint8_t addr, uint8_t TDC_num);
uint32_t TDC_Read_24(uint8_t addr, uint8_t TDC_num);


#ifdef __cplusplus
}
#endif

#endif
