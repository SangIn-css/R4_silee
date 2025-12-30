#include "main.h"
#include "apd.h"
#include <stdio.h>

void apd_Write_Data(uint8_t data)
{
	uint8_t ctrl_bit = 0x01 << 10;
	uint16_t data_bit = 0x03FF;
	uint16_t val = ctrl_bit | data_bit;

	GPIOC->BSRR = SPI3_CS_BIASCTRL_PC00_Pin << 16U;

#if 1
    SPI3->DR = val;
	while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET) { ; }
	while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
	SPI3->DR;

#else
	if(HAL_SPI_Transmit(&hspi3, val, 1, 100) != HAL_OK)
    {
      txString("TDCWriteData_SPI_Error\r\n");
    }
#endif

	GPIOC->BSRR = SPI3_CS_BIASCTRL_PC00_Pin;
}
