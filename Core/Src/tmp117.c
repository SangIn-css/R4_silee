#include "main.h"
#include "tmp117.h"

int16_t CR;		// value of Configuration Register
int16_t TR;		// value of Temperature Register
uint32_t t = 0;
uint32_t tmpt = 0;

void Tmp117_Init(I2C_HandleTypeDef *hi2c){

	uint8_t conf[3];
//	uint8_t rx_buf[2];

	uint8_t MOD = 0x0;		// Set conversion mode					(00)
	uint8_t CONV1 = 0x2;		// Conversion cycle bit 1`	`		(10)
	uint8_t CONV2 = 0x0;		// Conversion cycle bit 2	`		(0)
	uint8_t AVG = 0x1;		// Conversion averaging mode		(01)
	uint8_t TnA = 0x1;		// Therm/Alert mode						(1)
	uint8_t POL = 0x0;		// ALERT Pin polarity						(0)
	uint8_t DRA = 0x0;		// ALERT Pin select bit					(0)
	uint8_t SR = 0x0;		// Software Reset bit						(0)

	conf[0] = 0x01;			// Configuration Register Address
	conf[1] = (int16_t)( (MOD << 2) | (CONV1) );
	conf[2] = (int16_t)( (CONV2 << 7) | (AVG << 5) | (TnA << 4) | (POL << 3) | (DRA << 2) | (SR << 1) );

	HAL_I2C_Master_Transmit(hi2c,TMP117_ADDR, conf, 3, HAL_MAX_DELAY);
//	HAL_I2C_Master_Receive(hi2c, TMP117_ADDR, rx_buf, 2, HAL_MAX_DELAY);			//check

//	CR = (int16_t)((rx_buf[0] << 8) | rx_buf[1]);
//	return CR;

	Tmp117_Start();
}


void Tmp117_Start() {

}


void Tmp117_Stop() {

}


void Tmp117_Read(I2C_HandleTypeDef *hi2c)
{

    uint8_t reg = TMP117_TEMP_REG;
    uint8_t rx_buf[2];
    uint32_t tm = HAL_GetTick();

	if(isDataReady(hi2c)) {
		HAL_I2C_Master_Transmit(hi2c, TMP117_ADDR, &reg, 1, HAL_MAX_DELAY);
		HAL_I2C_Master_Receive(hi2c, TMP117_ADDR, rx_buf, 2, HAL_MAX_DELAY);

		TR = (int16_t)((rx_buf[0] << 8) | rx_buf[1]);
		float temp =  TR * 0.0078125f;		//convert 16Bit to decimal Temperature

		printf("Temperature = %.2f C\r\n", temp);
		Tmp117_Read_Bit(hi2c);
		printf("%04x\n", tm);
	}

}

void Tmp117_Read_Bit(I2C_HandleTypeDef *hi2c)
{
	printf("Temp Bit = %04x \n", TR);
}

int16_t isDataReady(I2C_HandleTypeDef *hi2c) {

	uint8_t rx_buf[2];
	uint8_t conf = 0x01;	// Configuration Register Address

	HAL_I2C_Master_Transmit(hi2c,TMP117_ADDR, &conf, 1, HAL_MAX_DELAY);			//Register Pointer
	HAL_I2C_Master_Receive(hi2c, TMP117_ADDR, rx_buf, 2, HAL_MAX_DELAY);

	CR = (int16_t)((rx_buf[0] << 8) | rx_buf[1]);
	int16_t bool = CR & 0x2000;				// Is Data_Ready Register set
	return bool;
}
