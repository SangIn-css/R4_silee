#include "main.h"
#include "TDC.h"
#include <stdio.h>

uint8_t TTR = 0x11;

void TDC_Init(SPI_HandleTypeDef *hspi)
{
	uint8_t conf1[2];
	uint8_t conf2[2];
	uint8_t pnt[2];
	uint8_t rx[2];
	uint8_t rx_buf;

	uint8_t Auto_Inc = 0x0;			// Auto Increment mode				(0)
	uint8_t RW = 0x1;					//Read Write								(1)

	uint8_t FORCE_CAL = 0x0;		// 	Calibration by Force				(0)
	uint8_t PARITY_EN = 0x0;		// Parity Enable`	`						(0)
	uint8_t TRIGG_EDGE = 0x0;		// Trigger Edge 	`					(0)
	uint8_t STOP_EDGE = 0x0;		// 	Stop Edge								(0)
	uint8_t START_EDGE = 0x0;		// Start Edge							(0)
	uint8_t MEAS_MODE = 0x0;		// Measurement Mode				(10)
	uint8_t START_MEAS = 0x1;		// 	Start New Measurement		(1)

	uint8_t CALIBRATION2_PERIODS = 0x1;		// 	Calibration by Force		(01)
	uint8_t AVG_CYCLES = 0x0;		// Parity Enable`	`									(000)
	uint8_t NUM_STOP = 0x0;		// Trigger Edge 	`										(000)

	conf1[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CONF1_REG) );			//Configuration Register Address
	conf1[1] = (uint8_t)( (FORCE_CAL << 7) | (PARITY_EN << 6) | (TRIGG_EDGE << 5) | (STOP_EDGE << 4)
			| (START_EDGE << 3)| (MEAS_MODE << 1) | (START_MEAS) );

	conf2[0] = TDC_CONF2_REG;
	conf2[1] = (uint16_t)( (CALIBRATION2_PERIODS  << 6) | (AVG_CYCLES << 3) | (NUM_STOP));


	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, conf1, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);


	RW = 0x0;
	pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CONF1_REG) );
	pnt[1] = 0x00;

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, pnt, rx, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);


	rx_buf = rx[1];

	TTR = (uint8_t)rx_buf;

	printf("conf1[0] = %02x\n", conf1[0]);
	printf("conf1[1] = %02x\n", conf1[1]);
	printf("TDC = %02x\n", TTR);
	printf("Rx = %02x\n", rx_buf);
}
