#include "main.h"
#include "apd.h"
#include "spi.h"
#include <stdio.h>

uint16_t apd_val = 0;

void apd_Write_Data(uint16_t data_bit)
{
	uint16_t ctrl_bit = 0x0007 << 10;
	apd_val = ctrl_bit | data_bit;

	apd_Transmit_Data(apd_val);

	ctrl_bit = 0x0002 << 10;
	apd_val = ctrl_bit | data_bit;

	apd_Transmit_Data(apd_val);
}

void apd_Transmit_Data(uint16_t data_bit) {

	HAL_GPIO_WritePin(GPIOC, SPI3_CS_BIASCTRL_PC00_Pin, GPIO_PIN_RESET); // CS Reset

#if USE_SPI3_DIRECT
    SPI3->DR = data_bit; // insert data_bit into DR register
	while ((SPI3->SR & SPI_FLAG_TXE) == RESET) { printf("Start\n"); }
	SPI3->DR;

#else
	HAL_SPI_Transmit(&hspi3, data_bit, 1, 100);
	printf("Success\n");
#endif
	HAL_GPIO_WritePin(GPIOC, SPI3_CS_BIASCTRL_PC00_Pin, GPIO_PIN_SET);
}
