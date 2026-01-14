#include "main.h"
#include "TDC.h"
#include "tim.h"
#include "LD.h"
#include <stdio.h>

uint16_t TDC_CR1;		//Configuration Register
uint16_t TDC_CR2;
float CALI2_PERIODS = 1.0;

void TDC_Init()
{
	TDC_Conf1_Init();
	TDC_Conf2_Init();
}


void TDC_Conf1_Init() {

	uint8_t conf = 0x00;

	//Transmit
	TDC_Write_Data(TDC_CONF1_REG, conf);

	//Receive
	uint16_t conf1 = TDC_Read_8(TDC_CONF1_REG, 1);
	uint16_t conf2 = TDC_Read_8(TDC_CONF1_REG, 2);

	TDC_CR1 = (uint16_t)(conf1 << 8);
	TDC_CR2 = (uint16_t)(conf2 << 8);
}


void TDC_Conf2_Init() {

	uint8_t conf = 0xF8;

	//Transmit
	TDC_Write_Data(TDC_CONF2_REG, conf);

	//Receive
	uint16_t conf1 = TDC_Read_8(TDC_CONF2_REG, 1);
	uint16_t conf2 = TDC_Read_8(TDC_CONF2_REG, 2);

	TDC_CR1 |= (uint16_t)conf1;
	TDC_CR2 |= (uint16_t)conf2;

	if(conf & 0xC0) {
		CALI2_PERIODS = 40.0;
	}
	else if(conf & 0x80) {
		CALI2_PERIODS = 20.0;
	}
	else if(conf & 0x40) {
		CALI2_PERIODS = 10.0;
	}
	else {
		CALI2_PERIODS = 2.0;
	}
}

void TDC_Write_Data(uint8_t addr, uint8_t data)
{
	uint16_t val = addr;
	val |= 0x40U;
	val <<= 8;
	val |= data;

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS2_TDC_PB07_Pin, GPIO_PIN_RESET);

#if 1
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

uint8_t TDC_Read_8(uint8_t addr, uint8_t TDC_num)
{
	uint16_t val = (uint16_t)addr;
	val |= 0x00U;
	val <<= 8;
	uint16_t rx;
	uint8_t Rx;

	if (TDC_num == 0x01) {						// CS1 Reset
		HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	}
	else if (TDC_num == 0x02) {			// CS2 Reset
		HAL_GPIO_WritePin(GPIOB, SPI2_CS2_TDC_PB07_Pin, GPIO_PIN_RESET);
	}

	#if 1
		SPI2->DR = val;		// Transmit Register Address
		while ((SPI2->SR & SPI_FLAG_TXE) == RESET) { ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == RESET){ ; }
		rx = SPI2->DR;

	#else
		HAL_SPI_TransmitReceive(&hspi2, wr_val, rd_val, 4, 100);
	#endif
		HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SPI2_CS2_TDC_PB07_Pin, GPIO_PIN_SET);

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

	if (TDC_num == 0x01) {			// CS1 Reset
		HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET); }
	else if (TDC_num == 0x02) {		// CS2 Reset
		HAL_GPIO_WritePin(GPIOB, SPI2_CS2_TDC_PB07_Pin, GPIO_PIN_RESET); }

	#if 1
		SPI2->DR = val;		// Transmit Register Address
		while ((SPI2->SR & SPI_FLAG_TXE) == RESET) { ; } 
		while ((SPI2->SR & SPI_FLAG_RXNE) == RESET){ ; }
		rx[0] = SPI2->DR;

		SPI2->DR = 0x0000;	// Transmit Dummy value
		while ((SPI2->SR & SPI_FLAG_TXE) == RESET){ ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == RESET){ ; }
		rx[1] = SPI2->DR;

	#else
		HAL_SPI_TransmitReceive(&hspi2, wr_val, rd_val, 4, 100);

	#endif
		HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SPI2_CS2_TDC_PB07_Pin, GPIO_PIN_SET);

	rx[0] &= 0x00FF;
	Rx = (rx[0] << 16) | (rx[1]);
	return Rx;

}
