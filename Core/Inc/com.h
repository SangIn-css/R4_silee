#ifndef __COM_H__
#define __COM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

void Com_Init();
void Com_DoCommand(const char *line);
void Com_OnRxChar(uint8_t ch);

#ifdef __cplusplus
}
#endif

#endif
