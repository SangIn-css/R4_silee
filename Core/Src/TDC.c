#include "main.h"
#include "TDC.h"
#include "tim.h"
#include "LD.h"
#include <stdio.h>

uint16_t TDC_CR = 0x0000;		//Configuration Register
uint8_t cal1[3];

void TDC_Init(SPI_HandleTypeDef *hspi)
{

	TDC_Conf1_Init(hspi);
	TDC_Conf2_Init(hspi);
	printf("Configuration = %04x\n", TDC_CR);

}


void TDC_Conf1_Init(SPI_HandleTypeDef *hspi) {

	uint8_t Auto_Inc = 0x0;			// Auto Increment mode				(0)
	uint8_t RW = 0x1;					// Read Write (Write)					(1)


	uint8_t FORCE_CAL = 0x0;		// 	Calibration by Force				(0)
	uint8_t PARITY_EN = 0x0;		// Parity Enable`	`						(0)
	uint8_t TRIGG_EDGE = 0x0;		// Trigger Edge 	`					(0)
	uint8_t STOP_EDGE = 0x0;		// 	Stop Edge								(0)
	uint8_t START_EDGE = 0x0;		// Start Edge							(0)
	uint8_t MEAS_MODE = 0x0;		// Measurement Mode				(00)
	uint8_t START_MEAS = 0x1;		// 	Start New Measurement		(1)

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
	uint8_t RW = 0x1;					// Read Write (Write)					(1)

	uint8_t CALIBRATION2_PERIODS = 0x2;		// 	Calibration Period				(10)
	uint8_t AVG_CYCLES = 0x6;		// The number of Measurement Cycles	`	(110)
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
	wrt_pnt[1] = 0x00;

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, wrt_pnt, rcv_bit, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);
	RW = 0x1;

	TDC_CR |= (uint16_t)rcv_bit[1];
}

//void TDC_Do_Read(SPI_HandleTypeDef *hspi) {
//
//	LD_Start();
//
//}


//void TDC_Read(SPI_HandleTypeDef *hspi, TDC_REG) {
//
//	uint8_t Auto_Inc = 0x0;
//	uint8_t RW = 0x0;
//	uint8_t wrt_pnt[2];
//	uint8_t time[4];
//
//	wrt_pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_REG) );
//	wrt_pnt[1] = 0x0;
//	wrt_pnt[2] = 0x0;
//	wrt_pnt[3] = 0x0;
//
//	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive(hspi, wrt_pnt, time, 4, HAL_MAX_DELAY);
//	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);
//
//	printf("time2 1 = %02x\n", time[1]);
//	printf("time2 2 = %02x\n", time[2]);
//	printf("time2 3 = %02x\n", time[3]);
//
//	uint32_t tim = ( (time[1] << 16) | (time[2] << 8) | (time[3]) );
//	printf("time2 = %06x\n", (unsigned int)tim);

//}


void TDC_Read_Time1(SPI_HandleTypeDef *hspi) {


//	TDC_Read(hspi, TDC_TIME1_REG);
	uint8_t Auto_Inc = 0x0;
	uint8_t RW = 0x0;
	uint8_t wrt_pnt[2];
	uint8_t time[4];

	wrt_pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_TIME1_REG) );
	wrt_pnt[1] = 0x0;
	wrt_pnt[2] = 0x0;
	wrt_pnt[3] = 0x0;

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, wrt_pnt, time, 4, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);

	printf("time1 1 = %02x\n", time[1]);
	printf("time1 2 = %02x\n", time[2]);
	printf("time1 3 = %02x\n", time[3]);

	uint32_t tim = ( (time[1] << 16) | (time[2] << 8) | (time[3]) );
	printf("time1 = %06x\n", (unsigned int)tim);

}

void TDC_Read_Time2(SPI_HandleTypeDef *hspi) {

	uint8_t Auto_Inc = 0x0;
	uint8_t RW = 0x0;
	uint8_t wrt_pnt[2];
	uint8_t time[4];

	wrt_pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_TIME2_REG) );
	wrt_pnt[1] = 0x0;
	wrt_pnt[2] = 0x0;
	wrt_pnt[3] = 0x0;

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, wrt_pnt, time, 4, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);

	printf("time2 1 = %02x\n", time[1]);
	printf("time2 2 = %02x\n", time[2]);
	printf("time2 3 = %02x\n", time[3]);

	uint32_t tim = ( (time[1] << 16) | (time[2] << 8) | (time[3]) );
	printf("time2 = %06x\n", (unsigned int)tim);

}


void TDC_Read_Cal1(SPI_HandleTypeDef *hspi) {

	uint8_t Auto_Inc = 0x0;
	uint8_t RW = 0x0;
	uint8_t wrt_pnt[2];
	uint8_t cal[4];

	wrt_pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CAL1_REG) );
	wrt_pnt[1] = 0x0;
	wrt_pnt[2] = 0x0;
	wrt_pnt[3] = 0x0;

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, wrt_pnt, cal, 4, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);

	printf("cal1 1 = %02x\n", cal[1]);
	printf("cal1 2 = %02x\n", cal[2]);
	printf("cal1 3 = %02x\n", cal[3]);

	uint32_t cali = ( (cal[1] << 16) | (cal[2] << 8) | (cal[3]) );
	printf("cal1 = %06x\n", (unsigned int)cali);

}


void TDC_Read_Cal2(SPI_HandleTypeDef *hspi) {

	uint8_t Auto_Inc = 0x0;
	uint8_t RW = 0x0;
	uint8_t wrt_pnt[2];
	uint8_t cal[4];

	wrt_pnt[0] = (uint8_t)( (Auto_Inc << 7) | (RW << 6 ) | (TDC_CAL2_REG) );
	wrt_pnt[1] = 0x0;
	wrt_pnt[2] = 0x0;
	wrt_pnt[3] = 0x0;

	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, wrt_pnt, cal, 4, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_TDC_PB06_Pin, GPIO_PIN_SET);

	printf("cal2 1 = %02x\n", cal[1]);
	printf("cal2 2 = %02x\n", cal[2]);
	printf("cal2 3 = %02x\n", cal[3]);

	uint32_t cali = ( (cal[1] << 16) | (cal[2] << 8) | (cal[3]) );
	printf("cal2 = %06x\n", (unsigned int)cali);

}


void TDC_Write_Data(uint8_t addr, uint8_t data)
{
	uint16_t val = addr;
	val |= 0x40U;
	val <<= 8;
	val |= data;

	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U; //비선택
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

	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin; //선택(SPI통신)
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin;
}

void TDC_Read_Data(uint8_t addr, uint8_t rx[3])
{
	uint16_t val = addr;
	val |= 0x00U;
	val <<= 8;


	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U; 	// CS Reset
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin << 16U;

	#if 1
		SPI2->DR = val;
		while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET) { ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
		SPI2->DR;	// dummy Rx value


		SPI2->DR = 0x0000;	// Transmit Dummy value
		while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET){ ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
		Rx[0] = SPI2->DR;

	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin;		// CS Set
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin;

	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U;
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin << 16U;

	#if 1
		SPI2->DR = 0x0000;
		while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET){ ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
		Rx[1] = SPI2->DR;


		SPI2->DR = 0x0000;	// Transmit Dummy value
		while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET){ ; }
		while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET){ ; }
		Rx[2] = SPI2->DR;

	GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin;
	GPIOB->BSRR = SPI2_CS2_TDC_PB07_Pin;

	#endif
}

//uint16_t TDC_Dst_Calc(SPI_HandleTypeDef *hspi) {
//	dst = c * ToF / 2;
//	ToF = (t1 - tn) * norm_LSB + (clk_Cnt_n) * (clk_Period);
//	norm_LSB = clk_Period / cal_Count;
//	cal_Count = (cali2 - cali1) / ((cali2_Period) - 1);
//
//}
