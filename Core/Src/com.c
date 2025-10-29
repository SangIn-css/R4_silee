#include "main.h"
#include "com.h"
#include "tmp117.h"
#include "LD.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>

extern TIM_HandleTypeDef htim2;
extern uint8_t cnt;

#define RX_LINE_MAX 64

static UART_HandleTypeDef *c_huart;
static I2C_HandleTypeDef  *t_hi2c;
static uint8_t input[RX_LINE_MAX];
static uint16_t idx = 0;

static const uint8_t start_txt[] =
"\n Press Command\r\n"
" 1) LDON : Turn On LD\r\n"
" 2) RTMP : Read Temperature\r\n"
" >> ";

void Com_Init(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c)
{
    c_huart = huart;
    t_hi2c  = hi2c;

    HAL_UART_Transmit(c_huart, (uint8_t*)start_txt, sizeof(start_txt) - 1, HAL_MAX_DELAY);
}


static void Com_DoCommand(const char *input_txt)
{

    //LDON

    if (strstr(input_txt, "LDON")) {
        LD_Start();
        HAL_UART_Transmit(c_huart, (uint8_t*)"LD set HIGH\r\n", 13, HAL_MAX_DELAY);
    }


    //RTMP

    else if (strstr(input_txt, "RTMP")) {

    	Tmp117_Init(t_hi2c);
    	while(1) {
			Tmp117_Read(t_hi2c);
			if(cnt > 10) {
				break;
			}
    	}
    }

    else {
            HAL_UART_Transmit(c_huart, (uint8_t*)"ERR: Unknown cmd\r\n", 18, HAL_MAX_DELAY);
        }

    HAL_UART_Transmit(c_huart, (uint8_t*)start_txt, sizeof(start_txt) - 1, HAL_MAX_DELAY);

}


void Com_OnRxChar(uint8_t ch)
{
	if (idx < RX_LINE_MAX - 1) {
	        input[idx] = ch;
	        idx++;
	    }

    if (ch == '\r') {
        input[idx] = '\0';
        Com_DoCommand((char*)input);
        idx = 0;
        input[0] = '\0';
        return;
    }
}
