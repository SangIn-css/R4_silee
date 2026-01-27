#include "main.h"
#include "tim.h"
#include "i2c.h"
#include "com.h"
#include "LD.h"
#include "TDC.h"
#include "usart.h"
#include "apd.h"
#include "eth.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include <tmp.h>

extern TIM_HandleTypeDef htim2;
extern uint8_t cnt;

#define RX_LINE_MAX 10

static uint8_t  line[RX_LINE_MAX];
static uint16_t idx = 0;

static const uint8_t start_txt[] =
"\n Press Command\n"
" 1) STOP : Stop All Command\n"
" 2) RTMP : Read Temperature\n"
" 3) RDIS : Read Distance\n"
" 4) DRMT : Drive Motor\n"
" 5) RENC : Read Encoder\n"
" 6) CMPB : Compensate Bias\n"
" 7) ETHE : Ethernet\n"
" >> ";

void Com_Init()
{
    HAL_UART_Transmit(&huart1, (uint8_t*)start_txt, sizeof(start_txt) - 1, HAL_MAX_DELAY);
}


void Com_DoCommand(const char *line)
{
    if (line[0] == '\0') return;

    //STOP
    if (strstr(line, "STOP")) {
    	htim8.Instance->CCR1 = 0;	//Stop motor
    	NVIC_SystemReset();
    }

    //RTMP
    else if (strstr(line, "RTMP")) {
    	tmp_Init(&hi2c2);
    	while(cnt < 10) {
			tmp_Read(&hi2c2);
    	}
    	cnt = 0;
    }

    //RDIS
    else if (strstr(line, "RDIS")) {
    	HAL_TIM_Base_Start_IT(&htim2);
    }

    //DRMT
    else if (strstr(line, "DRMT")) {
    	printf("Drive Motor\n");
    	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    	HAL_Delay(500);
    	HAL_GPIO_WritePin(GPIOC, FEEDBACK_SWITCH_PC14_Pin, GPIO_PIN_SET);
    }

    //RENC
    else if (strstr(line, "RENC")) {
    	HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
    }

    //CMPB
    else if (strstr(line, "CMPB")) {
    	uint16_t data = 0x100;
    	apd_Write_Data(data);
    }

    //ETHE
    else if (strstr(line, "ETHE")) {
        eth_Init();
        eth_Write_1Byte(0x0003, 11101, 0x17);
        printf("Read Value: %04x\n", eth_Read_1Byte(0x0003, 11101));
    }

    else {
    	printf("Incorrect Command\n");
    }

    HAL_UART_Transmit(&huart1, (uint8_t*)start_txt, sizeof(start_txt) - 1, HAL_MAX_DELAY);

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
