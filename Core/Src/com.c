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
static SPI_HandleTypeDef *t_hspi;
static uint8_t  s_line[RX_LINE_MAX];
static uint16_t s_idx = 0;

static const uint8_t tx_banner[] =
"\n Press Command\r\n"
" 1) LDON : Turn On LD\r\n"
" 2) RTMP : Read Temperature\r\n"
" 3) RDIS : Read Distance\r\n"
" >> ";

void Com_Init(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c, SPI_HandleTypeDef *hspi)
{
    c_huart = huart;
    t_hi2c  = hi2c;
    t_hspi = hspi;

    HAL_UART_Transmit(c_huart, (uint8_t*)tx_banner, sizeof(tx_banner) - 1, HAL_MAX_DELAY);
}


void Com_DoCommand(const char *line)
{
    if (line[0] == '\0') return;


    //LDON

    if (strstr(line, "LDON")) {
        LD_Start();
        HAL_UART_Transmit(c_huart, (uint8_t*)"LD set HIGH\r\n", 13, HAL_MAX_DELAY);
    }


    //RTMP

    else if (strstr(line, "RTMP")) {

    	Tmp117_Init(t_hi2c);
    	while(1) {
			Tmp117_Read(t_hi2c);
			if(cnt > 10) {
				break;
			}
    	}
    }

    else if (strstr(line, "RDIS")) {
    	TDC_Init(t_hspi);
    }

    HAL_UART_Transmit(c_huart, (uint8_t*)tx_banner, sizeof(tx_banner) - 1, HAL_MAX_DELAY);

}


void Com_OnRxChar(uint8_t ch)
{
    if (ch == '\r') {
        s_line[s_idx] = '\0';
        Com_DoCommand((char*)s_line);
        s_idx = 0;
        s_line[0] = '\0';
        return;
    }

    if (s_idx < RX_LINE_MAX - 1) {
        s_line[s_idx++] = ch;
    }
    else {
        s_idx = 0;
        HAL_UART_Transmit(c_huart, (uint8_t*)"\r\nERR: line too long\r\n", 22, HAL_MAX_DELAY);
        HAL_UART_Transmit(c_huart, (uint8_t*)tx_banner, sizeof(tx_banner) - 1, HAL_MAX_DELAY);
    }
}
