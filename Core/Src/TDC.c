#include "main.h"
#include "TDC.h"
#include "tim.h"
#include "LD.h"
#include <stdio.h>

uint16_t TDC_CR = 0x1111;		//Configuration Register
uint8_t cal1[3];

void TDC_Init(SPI_HandleTypeDef *hspi)
{

	TDC_Conf1_Init(hspi);
	TDC_Conf2_Init(hspi);
	printf("Configuration = %04x\n", TDC_CR);

}


void TDC_Conf1_Init(SPI_HandleTypeDef *hspi) {

	uint8_t conf = 0x00;

	//Transmit
	TDC_Write_Data(TDC_CONF1_REG, conf);

	//Receive
	uint16_t conf1 = TDC_Read_8(TDC_CONF1_REG, 1);

	TDC_CR = (uint16_t)(conf1 << 8);
}


void TDC_Conf2_Init(SPI_HandleTypeDef *hspi) {

	uint8_t conf = 0xB1;

	//Transmit
	TDC_Write_Data(TDC_CONF2_REG, conf);

	//Receive
	uint16_t conf2 = TDC_Read_8(TDC_CONF2_REG, 1);

	TDC_CR |= (uint16_t)conf2;

}

void TDC_Do_Read(SPI_HandleTypeDef *hspi) {
	TDC_Write_Data(TDC_CONF1_REG, 0x01);
	printf("Time1 = ",TDC_Read_24(TDC_TIME1_REG, 1));
	TDC_Read_24(TDC_TIME2_REG, 1);
	TDC_Read_24(TDC_TIME1_REG, 1);
	TDC_Read_24(TDC_TIME1_REG, 1);
}

void TDC_Read_Time1(SPI_HandleTypeDef *hspi) {

	TDC_Read_24(TDC_TIME1_REG, 1);

	printf("time1 1 = %02x\n", time[1]);
	printf("time1 2 = %02x\n", time[2]);
	printf("time1 3 = %02x\n", time[3]);

	uint32_t tim = ( (time[1] << 16) | (time[2] << 8) | (time[3]) );
	printf("time1 = %06x\n", (unsigned int)tim);

}

void TDC_Read_Time2(SPI_HandleTypeDef *hspi) {

	TDC_Read_24(TDC_TIME2_REG, 1);

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

	if (TDC_num == 0x1) {
		GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U; 	// CS1 Reset
	}
	else if (TDC_num == 0x2) {
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

	if (TDC_num == 0x1) {
		GPIOB->BSRR = SPI2_CS1_TDC_PB06_Pin << 16U; 	// CS1 Reset
	}
	else if (TDC_num == 0x2) {
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
