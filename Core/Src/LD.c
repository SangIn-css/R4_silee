#include "main.h"
#include "LD.h"
#include "tim.h"
#include <stdio.h>

void LD_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}


void LD_ON(void)
{
	//Start Signal (TDC)
	HAL_GPIO_WritePin(GPIOB,REF_SIG_PB08_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,REF_SIG_PB08_Pin,GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOB, LD_TRIG_PB02_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LD_TRIG_PB02_Pin, GPIO_PIN_RESET);
	printf("LD ON\n");

}
