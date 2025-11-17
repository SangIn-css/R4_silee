#include "main.h"
#include "LD.h"
#include "tim.h"
#include "TDC.h"
#include "spi.h"
#include <stdio.h>

void LD_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}


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

	printf("Read Distance\n");
	float norm_LSB = 62.5 / (((unsigned int)TDC_Read_24(TDC_CAL2_REG, 2) - (unsigned int)TDC_Read_24(TDC_CAL1_REG, 1)) / (40.0 - 1.0));
	float ToF = ((unsigned int)TDC_Read_24(TDC_TIME1_REG, 2) - (unsigned int)TDC_Read_24(TDC_TIME1_REG, 1)) * norm_LSB;
	printf("DIS = %f m\n\n", ToF * 0.15);
}

