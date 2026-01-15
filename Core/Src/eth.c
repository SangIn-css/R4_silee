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
    SPI1->DR = val;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET) { ; }		// Wait until data is transmitted
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET){ ; }
	SPI1->DR;

#else
	HAL_SPI_Transmit(&hspi2, (uint8_t*)val, 2, 100);

#endif

}