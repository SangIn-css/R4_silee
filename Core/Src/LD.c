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
//	TDC_Write_Data(TDC_CONF1_REG, 0x01U);

	//Start1,2 Signal
	HAL_GPIO_WritePin(GPIOB,REF_SIG_PB08_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,REF_SIG_PB08_Pin,GPIO_PIN_RESET);

	//Stop1 Signal (LD On/Off)
	HAL_GPIO_WritePin(GPIOB, LD_TRIG_PB02_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LD_TRIG_PB02_Pin, GPIO_PIN_RESET);

//	TDC_Read_Time1(&hspi2);
//	TDC_Read_Time2(&hspi2);
//	TDC_Read_Cal1(&hspi2);
//	TDC_Read_Cal2(&hspi2);

}


//static void _delay_tick(uint32_t uiCount); /*fixed for MISRA rule 8.1*/
//
//static void _delay_tick(uint32_t uiCount)
//{
//	__asm("    subs    r0, #1\n"
//				"    bne.n   _delay_tick\n"
//				"    bx      lr");
//}
//
//
//void DelayUs(uint32_t us)
//{
//	_delay_tick(us * (SystemCoreClock / 3U / 1000000U)); /*fixed for MISRA rule 10.1*/
//}
//
//
//void DelayMs(uint32_t ms)
//{
//	DelayUs(ms * 1000U); /*fixed for MISRA rule 10.1*/
//}
