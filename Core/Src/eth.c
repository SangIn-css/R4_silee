#include "main.h"
#include "apd.h"
#include "spi.h"
#include "eth.h"
#include <stdio.h>

void eth_Write_Data()
{
	uint16_t addr1 = SIMR;
	eth_Write_1Byte(addr1, 00000, data);	// write data on 
}

void eth_Write_1Byte(uint16_t addr, uint8_t BSB, uint8_t data) {

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);

	uint16_t ctrl_phase = BSB;
	ctrl_phase <<= 3;
	ctrl_phase |= 0x04; // R/W = 1, OM = 00 
	uint32_t val = (addr << 16) | (ctrl_phase << 8) | (data);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&val, 3, 100);

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);
}

void eth_Write_nByte(uint16_t addr, uint8_t BSB, uint8_t data) {

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);

	uint16_t ctrl_phase = BSB;
	ctrl_phase <<= 3;
	ctrl_phase |= 0x04; // R/W = 1, OM = 00 
	uint32_t val = (addr << 16) | (ctrl_phase << 8) | (data);
	HAL_SPI_Transmit(&hspi1, (uint8_t*)&val, 3, 100);

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);
}