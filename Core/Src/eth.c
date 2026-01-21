#include "main.h"
#include "apd.h"
#include "spi.h"
#include "eth.h"
#include <stdio.h>

void eth_Init()
{
	uint16_t addr1 = GAR;
	uint8_t BSB1 = Common_Register;

	eth_Write_1Byte(addr1, BSB1, data);	// write data on 
	eth_Write_1Byte(addr1, BSB1, data);
}

void eth_Write_1Byte(uint16_t addr, uint8_t BSB, uint8_t data) {

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);

	uint16_t ctrl_phs = BSB;
	ctrl_phs <<= 3;
	ctrl_phs |= 0x04; // R/W = 1, OM = 00 
	uint32_t val = (addr << 16) | (ctrl_phs << 8) | (data);
	HAL_SPI_Transmit(&hspi1, &val, 4, 100);

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);
}

void eth_Write_nByte(uint16_t addr, uint8_t BSB, uint8_t data[], int datasize) {

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);

	uint16_t ctrl_phs = BSB;
	ctrl_phs <<= 3;
	ctrl_phs |= 0x04;
	uint32_t val = (addr << 16) | (ctrl_phs << 8) | (data[0]);
	HAL_SPI_Transmit(&hspi1, &val, 4, 100);
	for(int i = 1; i < datasize; i++) {
		HAL_SPI_Transmit(&hspi1, &data[i], 1, 100);
	}

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);
}