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
	delay_11p1_ns(1);
	HAL_GPIO_WritePin(GPIOB,LD_TRIG_PB02_Pin,GPIO_PIN_RESET);

}

void delay_11p1_ns(uint8_t time) {

	HAL_TIM_Base_Start_IT(&htim6);

	__HAL_TIM_SET_COUNTER(&htim6, 0);
	while((__HAL_TIM_GET_COUNTER(&htim6)) < time);		//delay for 11.1ns
}
