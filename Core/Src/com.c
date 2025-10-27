#include "main.h"
#include "com.h"
#include "tmp117.h"
#include "LD.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>

extern TIM_HandleTypeDef htim2;

#define RX_LINE_MAX 64

static UART_HandleTypeDef *c_huart;
static I2C_HandleTypeDef  *t_hi2c;
static uint8_t  s_line[RX_LINE_MAX];
static uint16_t s_idx = 0;

static const uint8_t tx_banner[] =
"\n Press Command\r\n"
" 1) LDON : Turn On LD\r\n"
" 2) RTMP : Read Temperature\r\n"
" >> ";

void COM_Init(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c)
{
    c_huart = huart;
    t_hi2c  = hi2c;

    HAL_UART_Transmit(c_huart, (uint8_t*)tx_banner, sizeof(tx_banner) - 1, HAL_MAX_DELAY);
}


static void COM_DoCommand(const char *line)
{
    if (line[0] == '\0') return;


    //LDON

    if (strstr(line, "LDON")) {
        LD_Start();
        HAL_UART_Transmit(c_huart, (uint8_t*)"LD set HIGH\r\n", 13, HAL_MAX_DELAY);
    }


    //RTMP

    else if (strstr(line, "RTMP")) {

//    	int16_t  tmp = Tmp117_Init(t_hi2c);
//    	printf("Register = %04x \n", tmp);

    	Tmp117_Init(t_hi2c);
    	HAL_Delay(1000);
    	int cnt = 0;
    	while(cnt < 30) {
			float temp = Tmp117_Read(t_hi2c);
			printf("Temperature = %.2f C\r\n", temp);

			int16_t temp_bit = Tmp117_Read_Bit(t_hi2c);
			printf("Temp Bit = %04x \n", temp_bit);

			cnt++;
//			HAL_Delay(1000);
	}
    int16_t temp_bit = Tmp117_Read_Bit(t_hi2c);
    printf("Temp Bit = %04x \n", temp_bit);

    HAL_UART_Transmit(c_huart, (uint8_t*)tx_banner, sizeof(tx_banner) - 1, HAL_MAX_DELAY);

    }
}

void COM_OnRxChar(uint8_t ch)
{
    if (ch == '\r' || ch == '\n') {
        s_line[s_idx] = '\0';
        COM_DoCommand((char*)s_line);
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
