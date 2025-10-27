#ifndef __TMP117_H__
#define __TMP117_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"

#define TMP117_ADDR       (0x48 << 1)   // ADD0=GND
#define TMP117_TEMP_REG   0x00

void Tmp117_Init (I2C_HandleTypeDef *hi2c);
float Tmp117_Read(I2C_HandleTypeDef *hi2c);
int16_t Tmp117_Read_Bit(I2C_HandleTypeDef *hi2c);
int16_t isDataReady(I2C_HandleTypeDef *hi2c);

#ifdef __cplusplus
}
#endif

#endif
