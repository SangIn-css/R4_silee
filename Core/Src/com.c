#include "main.h"
#include "tim.h"
#include "i2c.h"
#include "com.h"
#include "tmp117.h"
#include "LD.h"
#include "TDC.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>

extern TIM_HandleTypeDef htim2;
extern uint8_t cnt;

#define RX_LINE_MAX 64

static UART_HandleTypeDef *c_huart;
static uint8_t  line[RX_LINE_MAX];
static uint16_t idx = 0;

static const uint8_t start_txt[] =
"\n Press Command\n"
" 1) RTMP : Read Temperature\n"
" 2) RDIS : Read Distance\n"
" 3) DRMT : Drive Motor\n"
" >> ";

void Com_Init(UART_HandleTypeDef *huart)
{
    c_huart = huart;

    HAL_UART_Transmit(c_huart, (uint8_t*)start_txt, sizeof(start_txt) - 1, HAL_MAX_DELAY);
}


void Com_DoCommand(const char *line)
{
    if (line[0] == '\0') return;

    //RTMP (Read Temperature)
    if (strstr(line, "RTMP")) {
    	Tmp117_Init(&hi2c2);
    	while(cnt < 10) {
			Tmp117_Read(&hi2c2);
    	}
    }

    //RDIS (Read Distance)
    else if (strstr(line, "RDIS")) {
    	LD_Start();
    }

    //DRMT (Drive Motor)
    else if (strstr(line, "DRMT")) {
    	printf("COM\n");
    	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//    	HAL_TIM_Base_Start_IT(&htim3);
    }

    else {
    	printf("Incorrect Command\n");
    }
    HAL_UART_Transmit(c_huart, (uint8_t*)start_txt, sizeof(start_txt) - 1, HAL_MAX_DELAY);

}


void Com_OnRxChar(uint8_t ch)
{
    if (ch == '\r') {
        line[idx] = '\0';
        Com_DoCommand((char*)line);
        idx = 0;
        line[0] = '\0';
        return;
    }

    if (idx < RX_LINE_MAX - 1) {
        line[idx] = ch;
        idx++;
    }
}
