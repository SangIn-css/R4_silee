#include "main.h"
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
static I2C_HandleTypeDef  *t_hi2c;
static SPI_HandleTypeDef *t_hspi;
static uint8_t  line[RX_LINE_MAX];
static uint16_t idx = 0;

static const uint8_t start_txt[] =
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

    HAL_UART_Transmit(c_huart, (uint8_t*)start_txt, sizeof(start_txt) - 1, HAL_MAX_DELAY);
}


void Com_DoCommand(const char *line)
{
    if (line[0] == '\0') return;


    //LDON (Turn on LD)
    if (strstr(line, "LDON")) {
        LD_Start();
    }


    //RTMP (Read Temperature)
    else if (strstr(line, "RTMP")) {
    	Tmp117_Init(t_hi2c);
    	while(cnt < 10) {
			Tmp117_Read(t_hi2c);
    	}
    }


    //RDIS (Read Distance)
    else if (strstr(line, "RDIS")) {

    	LD_Start();
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
