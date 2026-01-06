#ifndef __APD_H__
#define __APD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void apd_Write_Data(uint16_t data_bit);
void apd_Transmit_Data(uint16_t data_bit);

#ifdef __cplusplus
}
#endif

#endif
