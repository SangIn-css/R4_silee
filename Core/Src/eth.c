#include "main.h"
#include "apd.h"
#include "spi.h"
#include <stdio.h>

void eth_Write_Data(uint8_t addr, uint8_t data)
{
	uint16_t val = addr;
	val |= 0x40U;	//R/W = 1 (Write)
	val <<= 8;
	val |= data;

#if USE_SPI1_DIRECT
    SPI2->DR = val;
	while ((SPI2->SR & SPI_FLAG_TXE) == RESET) { ; }		// Wait until data is transmitted
	while ((SPI2->SR & SPI_FLAG_RXNE) == RESET){ ; }
	SPI2->DR;

#else
	HAL_SPI_Transmit(&hspi2, (uint8_t*)val, 2, 100);

#endif
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS2_TDC_PB07_Pin, GPIO_PIN_SET);
}