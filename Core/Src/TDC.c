#include "main.h"
#include "TDC.h"
#include "tim.h"
#include "LD.h"
#include <stdio.h>

uint16_t TDC_CR1;		//Configuration Register
uint16_t TDC_CR2;

void TDC_Init(SPI_HandleTypeDef *hspi)
{

	TDC_Conf1_Init(hspi);
	TDC_Conf2_Init(hspi);

}


void TDC_Conf1_Init(SPI_HandleTypeDef *hspi) {

	uint8_t conf = 0x00;

	//Transmit
	TDC_Write_Data(TDC_CONF1_REG, conf);

	//Receive
	uint16_t conf1 = TDC_Read_8(TDC_CONF1_REG, 1);
	uint16_t conf2 = TDC_Read_8(TDC_CONF1_REG, 2);

	TDC_CR1 = (uint16_t)(conf1 << 8);
	TDC_CR2 = (uint16_t)(conf2 << 8);
}


void TDC_Conf2_Init(SPI_HandleTypeDef *hspi) {

	uint8_t conf = 0xF8;

	//Transmit
	TDC_Write_Data(TDC_CONF2_REG, conf);

	//Receive
	uint16_t conf1 = TDC_Read_8(TDC_CONF2_REG, 1);
	uint16_t conf2 = TDC_Read_8(TDC_CONF2_REG, 2);

	TDC_CR1 |= (uint16_t)conf1;
	TDC_CR2 |= (uint16_t)conf2;

}


void TDC_Write_Data(uint8_t addr, uint8_t data)
{
	uint16_t val = addr;
	val |= 0x40U;
	val <<= 8;
	val |= data;

	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U;
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin << 16U;

#if 1
    SPI2->DR = val;
	while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET) { ; }
	while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
	SPI2->DR;

#else
	if(HAL_SPI_Transmit(&hspi2, (uint8_t*)val, 2, 100) != HAL_OK)
    {
      txString("TDCWriteData_SPI_Error\r\n");
    }
#endif

	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin;
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin;
}

uint8_t TDC_Read_8(uint8_t addr, uint8_t TDC_num)
{
	uint16_t val = (uint16_t)addr;
	val |= 0x00U;
	val <<= 8;
	uint16_t rx;
	uint8_t Rx;

	if (TDC_num == 0x01) {
		GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U; 	// CS1 Reset
	}
	else if (TDC_num == 0x02) {
		GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin << 16U; 	// CS2 Reset
	}

	#if 1
		SPI2->DR = val;		// Transmit Register Address
		while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET) { ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
		rx = SPI2->DR;

	#else
		if(HAL_SPI_TransmitReceive(&hspi2, wr_val, rd_val, 4, 100) != HAL_OK)
		{
			txString("TDCRead8_SPI_Error\r\n");
		}

	#endif
	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin;		// CS Set
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin;

	Rx = (uint8_t)(rx & 0x00FF);
	return Rx;

}

uint32_t TDC_Read_24(uint8_t addr, uint8_t TDC_num)
{
	uint16_t val = addr;
	val |= 0x00U;
	val <<= 8;
	uint16_t rx[2];
	uint32_t Rx;

	if (TDC_num == 0x01) {
		GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U; 	// CS1 Reset
	}
	else if (TDC_num == 0x02) {
		GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin << 16U; 	// CS2 Reset
	}

	#if 1
		SPI2->DR = val;		// Transmit Register Address
		while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET) { ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
		rx[0] = SPI2->DR;

		SPI2->DR = 0x0000;	// Transmit Dummy value
		while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET){ ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
		rx[1] = SPI2->DR;

	#else
		if(HAL_SPI_TransmitReceive(&hspi2, wr_val, rd_val, 4, 100) != HAL_OK)
		{
			txString("TDCRead24_SPI_Error\r\n");
		}

	#endif
	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin;		// CS Set
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin;

	rx[0] &= 0x00FF;
	Rx = (rx[0] << 16) | (rx[1]);
	return Rx;

}
