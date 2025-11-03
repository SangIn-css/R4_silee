#include "main.h"
#include "TDC.h"
#include <stdio.h>

uint16_t TDC_CR = 0x0000;		//Configuration Register

void TDC_Init(SPI_HandleTypeDef *hspi)
{

	TDC_Conf1_Init(hspi);
	TDC_Conf2_Init(hspi);
	printf("Configuration = %04x\n", TDC_CR);

//	TDC_Dst_Read (hspi);

}

void TDC_Conf1_Init(SPI_HandleTypeDef *hspi) {

	uint8_t Auto_Inc = 0x0;			// Auto Increment mode				(0)
	uint8_t RW = 0x1;					//Read Write								(1)


	uint8_t FORCE_CAL = 0x0;		// 	Calibration by Force				(0)
	uint8_t PARITY_EN = 0x1;		// Parity Enable`	`						(1)
	uint8_t TRIGG_EDGE = 0x0;		// Trigger Edge 	`					(0)
	uint8_t STOP_EDGE = 0x0;		// 	Stop Edge								(0)
	uint8_t START_EDGE = 0x0;		// Start Edge							(0)
	uint8_t MEAS_MODE = 0x1;		// Measurement Mode				(01)
	uint8_t START_MEAS = 0x0;		// 	Start New Measurement		(0)

	uint8_t conf[2];
	uint8_t rcv_bit[2];
	uint8_t wrt_pnt[2];

	conf[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CONF1_REG) );			//Configuration1 Register Address
	conf[1] = (uint8_t)( (FORCE_CAL << 7) | (PARITY_EN << 6) | (TRIGG_EDGE << 5) | (STOP_EDGE << 4)
			| (START_EDGE << 3)| (MEAS_MODE << 1) | (START_MEAS) );


	//Transmit
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, conf, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);


	//Receive
	RW = 0x0;
	wrt_pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CONF1_REG) );
	wrt_pnt[1] = 0x00;		//dummy

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, wrt_pnt, rcv_bit, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);
	RW = 0x1;

	TDC_CR |= (uint16_t)(rcv_bit[1] << 8);
}


void TDC_Conf2_Init(SPI_HandleTypeDef *hspi) {

	uint8_t Auto_Inc = 0x0;			// Auto Increment mode				(0)
	uint8_t RW = 0x1;					//Read Write								(1)

	uint8_t CALIBRATION2_PERIODS = 0x1;		// 	Calibration Period				(01)
	uint8_t AVG_CYCLES = 0x0;		// The number of Measurement Cycles	`	(000)
	uint8_t NUM_STOP = 0x1;		// The number of STOP 	`								(001)

	uint8_t conf[2];
	uint8_t rcv_bit[2];
	uint8_t wrt_pnt[2];

	conf[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CONF2_REG) );			//Configuration2 Register Address
	conf[1] = (uint8_t)( (CALIBRATION2_PERIODS  << 6) | (AVG_CYCLES << 3) | (NUM_STOP));

	//Transmit
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, conf, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);


	//Receive
	RW = 0x0;
	wrt_pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CONF2_REG) );
	wrt_pnt[1] = 0x00;		//dummy

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, wrt_pnt, rcv_bit, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);
	RW = 0x1;

	TDC_CR |= (uint16_t)rcv_bit[1];
}

//uint16_t TDC_Dst_Calc(SPI_HandleTypeDef *hspi) {
//	dst = c * ToF;
//	ToF = (t1 - tn) * norm_LSB + (clk_Cnt_n) * (clk_Period);
//	norm_LSB = clk_Period / cal_Count;
//	cal_Count = (cali2 - cali1) / ((cali2_Period) - 1);
//
//}
