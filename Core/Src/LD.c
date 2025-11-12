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

	printf("STOP1 = %06x  ", (unsigned int)TDC_Read_24(TDC_TIME1_REG, 1));
	printf("STOP2 = %06x  ", (unsigned int)TDC_Read_24(TDC_TIME1_REG, 2));
	printf("CALI1 = %06x  ", (unsigned int)TDC_Read_24(TDC_CAL1_REG, 1));
	printf("CALI2 = %06x\n", (unsigned int)TDC_Read_24(TDC_CAL2_REG, 1));
}


//
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
//{rid
//	DelayUs(ms * 1000U); /*fixed for MISRA rule 10.1*/
//}
