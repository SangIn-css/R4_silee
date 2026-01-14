#include "main.h"
#include "apd.h"
#include <stdio.h>

void apd_Write_Data(uint16_t data_bit)
{
	uint16_t ctrl_bit = 0x0007 << 10;
	uint16_t val = ctrl_bit | data_bit;

	apd_Transmit_Data(val);

	ctrl_bit = 0x0002 << 10;
	val = ctrl_bit | data_bit;

	apd_Transmit_Data(val);
}

void apd_Transmit_Data(uint16_t data_bit) {

	HAL_GPIO_WritePin(GPIOC, SPI3_CS_BIASCTRL_PC00_Pin, GPIO_PIN_RESET); // CS Reset

#if 1
    SPI3->DR = data_bit; // insert data_bit into DR register
	while ((SPI3->SR & SPI_FLAG_TXE) == RESET) { ; }
	SPI3->DR;
	printf("Start4\n");

#else
	HAL_SPI_Transmit(&hspi3, val, 1, 100);

#endif
	HAL_GPIO_WritePin(GPIOC, SPI3_CS_BIASCTRL_PC00_Pin, GPIO_PIN_SET);
}
