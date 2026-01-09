#include "main.h"
#include "apd.h"
#include <stdio.h>

void apd_Write_Data(uint16_t data_bit)
{

	uint16_t ctrl_bit = 0x0007 << 10;
	uint16_t val = ctrl_bit | data_bit;

	apd_Transmit_Data(val);

	printf("Start\n");

	ctrl_bit = 0x0002 << 10;
	val = ctrl_bit | data_bit;

	apd_Transmit_Data(val);

}

void apd_Transmit_Data(uint16_t data_bit) {

	GPIOC->BSRR = SPI3_CS_BIASCTRL_PC00_Pin << 16U;

#if 1
    SPI3->DR = data_bit;
	while ((SPI3->SR & SPI_FLAG_TXE) == (uint16_t)RESET) { ; }		// problem (SPI Flag check)
	while ((SPI3->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
	SPI3->DR;
	printf("Start4\n");

#else
	HAL_SPI_Transmit(&hspi3, val, 1, 100);

#endif

	GPIOC->BSRR = SPI3_CS_BIASCTRL_PC00_Pin;
}
