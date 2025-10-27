#include "main.h"
#include "LD.h"
#include "tim.h"

void LD_Start(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}


void LD_ON(void)
{
	HAL_GPIO_WritePin(GPIOB,LD_TRIG_PB02_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,LD_TRIG_PB02_Pin,GPIO_PIN_RESET);
}
