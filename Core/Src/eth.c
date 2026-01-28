#include "main.h"
#include "apd.h"
#include "spi.h"
#include "eth.h"
#include "tim.h"
#include <stdio.h>

void eth_Init()
{
	uint16_t addr1 = GAR;
	uint8_t BSB1 = Common_Register;
	uint8_t data1[4] = {0xC0, 0xA8, 0x7B, 0x01}; // Default Gateway Address : 192.168.123.1
	eth_Write_nByte(addr1, BSB1, data1, 4);

	uint16_t addr2 = SUBR;
	uint8_t BSB2 = Common_Register;
	uint8_t data2[4] = {0xFF, 0xFF, 0xFF, 0x00}; // Subnet Mask Address : 255.255.255.0
	eth_Write_nByte(addr2, BSB2, data2, 4);

	uint16_t addr3 = SIPR;
	uint8_t BSB3 = Common_Register;
	uint8_t data3[4] = {0xC0, 0xA8, 0x7B, 0x64}; // IP Address : 192.168.123.100
	eth_Write_nByte(addr3, BSB3, data3, 4);
}

void eth_Write_1Byte(uint16_t addr, uint8_t BSB, uint8_t data) {

	uint8_t addr1 = (uint8_t)(addr >> 8);
	uint8_t addr2 = (uint8_t)(addr & 0x00FF);
	uint8_t ctrl_phs = BSB;
	ctrl_phs <<= 3;
	ctrl_phs |= 0x04; // R/W = 1, OM = 00

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);

	transmit_1Byte(addr1);
	transmit_1Byte(addr2);
	transmit_1Byte(ctrl_phs);
	transmit_1Byte(data);

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);
	printf("1 Complete\n");
}

void eth_Write_nByte(uint16_t addr, uint8_t BSB, uint8_t data[], int datasize) {

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);

	uint8_t addr1 = (uint8_t)(addr >> 8);
	uint8_t addr2 = (uint8_t)(addr & 0x00FF);
	uint8_t ctrl_phs = BSB;
	ctrl_phs <<= 3;
	ctrl_phs |= 0x04; // R/W = 1, OM = 00

	transmit_1Byte(addr1);
	transmit_1Byte(addr2);
	transmit_1Byte(ctrl_phs);

	for(int i=0; i<datasize; i++) {
		transmit_1Byte(data[i]);
	}

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);
	printf("n Complete\n");
}


uint8_t eth_Read_1Byte(uint16_t addr, uint8_t BSB) {

	uint8_t rd_val;
	uint8_t addr1 = (uint8_t)(addr >> 8);
	uint8_t addr2 = (uint8_t)(addr & 0x00FF);
	uint8_t ctrl_phs = BSB;
	ctrl_phs <<= 3;
	ctrl_phs |= 0x00; // R/W = 0, OM = 00
	
	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);

	transmit_1Byte(addr1);
	transmit_1Byte(addr2);
	transmit_1Byte(ctrl_phs);

	SPI1->DR = 0x01; // Dummy Write;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET) { ; }
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET){ ; }
	rd_val = SPI1->DR;

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);

	printf("read Complete\n");
	return rd_val;
}

void eth_Read_nByte(uint16_t addr, uint8_t BSB, uint8_t data[], int datasize) {

	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_RESET);


	HAL_GPIO_WritePin(GPIOB, ENET_SCSn_Pin, GPIO_PIN_SET);
}

void transmit_1Byte(uint8_t data) {
	SPI1->DR = data;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET) { ; }
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET){ ; }
	SPI1->DR;
}
