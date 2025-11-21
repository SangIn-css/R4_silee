#include "main.h"
#include "LD.h"
#include "tim.h"
#include "TDC.h"
#include "spi.h"
#include "usart.h"
#include "com.h"
#include <stdio.h>

extern float CALI2_PERIODS;
extern uint8_t rx_ch;
int LD_cnt = 0;
float max = 0.0;
float min = 1000.0;

void LD_ON(void)
{

	//Start New Measurement
	TDC_Write_Data(TDC_CONF1_REG, 0x01U);

	//Start1,2 Signal
	HAL_GPIO_WritePin(GPIOB,REF_SIG_PB08_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,REF_SIG_PB08_Pin,GPIO_PIN_RESET);

	//Stop1 Signal (LD On/Off)
	HAL_GPIO_WritePin(GPIOB, LD_TRIG_PB02_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LD_TRIG_PB02_Pin, GPIO_PIN_RESET);

	//delay 1us
	for(int i = 0; i < 200; i++) {
		asm("nop");
	}

	float norm_LSB = 62.5 / (((unsigned int)TDC_Read_24(TDC_CAL2_REG, 2) - (unsigned int)TDC_Read_24(TDC_CAL1_REG, 1)) / (CALI2_PERIODS - 1.0));
	float ToF = ((unsigned int)TDC_Read_24(TDC_TIME1_REG, 2) - (unsigned int)TDC_Read_24(TDC_TIME1_REG, 1)) * norm_LSB;

	if (ToF > max) {
		max = ToF;
	}

	if (ToF < min) {
		min = ToF;
	}

	LD_cnt++;

	if(LD_cnt % 100 == 0) {
		printf("\n");
		printf("MAX_DIS = %f m\n", max * 0.15);
		printf("MIN_DIS = %f m\n\n", min * 0.15);
		max = 0.0;
		min = 1000.0;
	}

	if(LD_cnt == 50000) {
		HAL_TIM_Base_Stop(&htim2);
		HAL_UART_Receive_IT(&huart1, &rx_ch, 1);
		Com_Init();
	}
}

