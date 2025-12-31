#ifndef __TMP_H__
#define __TMP_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f4xx_hal.h"

#define TMP_ADDR       (0x48 << 1)   // ADD0=GND
#define TMP_TEMP_REG   0x00
#define TMP_CONF_REG   0x01

void tmp_Init (I2C_HandleTypeDef *hi2c);
void tmp_Read(I2C_HandleTypeDef *hi2c);
void tmp_Read_Bit(I2C_HandleTypeDef *hi2c);
uint16_t isDataReady(I2C_HandleTypeDef *hi2c);

#ifdef __cplusplus
}
#endif

#endif
