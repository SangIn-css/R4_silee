#ifndef __TDC_H__
#define __TDC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define TDC_CONF1_REG	0x00
#define TDC_CONF2_REG	0x01

#define TDC_TIME1_REG 	0x10
#define TDC_TIME2_REG	    0x12
#define TDC_TIME3_REG		0x14
#define TDC_TIME4_REG		0x16
#define TDC_TIME5_REG		0x18
#define TDC_TIME6_REG		0x1A

#define TDC_CAL1_REG		0x1B
#define TDC_CAL2_REG		0x1C

#define clk_Period 		16 * (10^6)
#define C						3 * (10^8)

void TDC_Init(SPI_HandleTypeDef *hspi);
void TDC_Transmit_Start();
void TDC_Conf1_Init(SPI_HandleTypeDef *hspi);
void TDC_Conf2_Init(SPI_HandleTypeDef *hspi);
void TDC_Read_Cal1(SPI_HandleTypeDef *hspi);
//uint16_t TDC_Dst_Calc(SPI_HandleTypeDef *hspi);


#ifdef __cplusplus
}
#endif

#endif
