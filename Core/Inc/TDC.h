#ifndef __TDC_H__
#define __TDC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define TDC_CONF1_REG	0x00
#define TDC_CONF2_REG	0x01

#define TDC_TIME1_REG 	0x10
#define TDC_TIME2_REG	    0x12
#define TDC_TIME3_REG		0x14
#define TDC_TIME4_REG		0x16
#define TDC_TIME5_REG		0x18
#define TDC_TIME6_REG		0x1A

#define TDC_CAL1_REG		0x1B
#define TDC_CAL2_REG		0x1C

#define clk_Period 		16 * (10^6)
#define C						3 * (10^8)

void TDC_Init(SPI_HandleTypeDef *hspi);
void TDC_Conf1_Init(SPI_HandleTypeDef *hspi);
void TDC_Conf2_Init(SPI_HandleTypeDef *hspi);
void TDC_Do_Read(SPI_HandleTypeDef *hspi);
void TDC_Read_Time1(SPI_HandleTypeDef *hspi);
void TDC_Read_Time2(SPI_HandleTypeDef *hspi);
void TDC_Read_Cal1(SPI_HandleTypeDef *hspi);
void TDC_Read_Cal2(SPI_HandleTypeDef *hspi);
void TDC_Write_Data(uint8_t addr, uint8_t data);
uint8_t TDC_Read_8(uint8_t addr, uint8_t TDC_num);
uint32_t TDC_Read_24(uint8_t addr, uint8_t TDC_num);
//uint16_t TDC_Dst_Calc(SPI_HandleTypeDef *hspi);


#ifdef __cplusplus
}
#endif

#endif

/**
  @file  			tdc.c
  @brief      tdc configuration 및 기능
	@details
	@author 		tg.An
	@date 			2021.03.11
	@version 		1.0.0
*/

/** #include "tdc.h"

volatile TDCType g_TDC1;
volatile TDCType g_TDC2;
volatile float g_DistanceOffset = 0.0;

volatile uint8_t g_CalibrationMode = 0;

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

//
	@brief    TDC Default Initialize
	@details 	TDC를 사용하기 위한 초기화 과정을 수행하고 해당 값이 정상적으로 설정되었는지 확인.
	@author   tg.An
	@date     2021.01.10
	@param    None
	@return   None
	@throw		일정 횟수이상 tdc 초기화를 못하는 경우 error 동작을 수행
	@remark
//

/**
void TDCInit(void)
{
	bool result = false;
	uint8_t tdc_errcnt = 0U;
	uint8_t errcheck = 0U;

#ifdef ETHERNET_MODE
//	USART1_SendStrData(" TDC Init . . . ", sizeof(" TDC Init . . . "));
    printf(" TDC Init . . . ");
#else
	//puts("TDC Init Start\n");
#endif
	while(result != true) {
		WDT_Reload();

		TDCWriteData(ADDR_TDC_CONFIG1, DATA_TDC_CONFIG1);
		if(CheckTDCReadData8bit(ADDR_TDC_CONFIG1, DATA_TDC_CONFIG1) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_CONFIG2, DATA_TDC_CONFIG2);
		if(CheckTDCReadData8bit(ADDR_TDC_CONFIG2, DATA_TDC_CONFIG2) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_INT_STATUS, DATA_TDC_INT_STATUS);
		// Interrupt Clear Data
    	if(CheckTDCReadData8bit(ADDR_TDC_INT_STATUS, 0U) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_INT_MASK, DATA_TDC_INT_MASK);
		if(CheckTDCReadData8bit(ADDR_TDC_INT_MASK, DATA_TDC_INT_MASK) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_COARSE_CNTR_OVF_H, DATA_TDC_COARSE_CNTR_OVF_H);
		if(CheckTDCReadData8bit(ADDR_TDC_COARSE_CNTR_OVF_H, DATA_TDC_COARSE_CNTR_OVF_H) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_COARSE_CNTR_OVF_L, DATA_TDC_COARSE_CNTR_OVF_L);
		if(CheckTDCReadData8bit(ADDR_TDC_COARSE_CNTR_OVF_L, DATA_TDC_COARSE_CNTR_OVF_L) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_CLOCK_CNTR_OVF_H, DATA_TDC_CLOCK_CNTR_OVF_H);
		if(CheckTDCReadData8bit(ADDR_TDC_CLOCK_CNTR_OVF_H, DATA_TDC_CLOCK_CNTR_OVF_H) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_CLOCK_CNTR_OVF_L, DATA_TDC_CLOCK_CNTR_OVF_L);
		if(CheckTDCReadData8bit(ADDR_TDC_CLOCK_CNTR_OVF_L, DATA_TDC_CLOCK_CNTR_OVF_L) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_CLOCK_CNTR_STOP_MASK_H, DATA_TDC_CLOCK_CNTR_STOP_MASK_H);
		if(CheckTDCReadData8bit(ADDR_TDC_CLOCK_CNTR_STOP_MASK_H, DATA_TDC_CLOCK_CNTR_STOP_MASK_H) != true)
		{
			errcheck++;
		}

		TDCWriteData(ADDR_TDC_CLOCK_CNTR_STOP_MASK_L, DATA_TDC_CLOCK_CNTR_STOP_MASK_L);
		if(CheckTDCReadData8bit(ADDR_TDC_CLOCK_CNTR_STOP_MASK_L, DATA_TDC_CLOCK_CNTR_STOP_MASK_L) != true)
		{
			errcheck++;
		}

		if(errcheck == 0U)
		{
			result = true;
		}
		else
		{
			errcheck = 0U;
			result = false;

			tdc_errcnt++;
			if(tdc_errcnt == TDC_INIT_ERR_CNT)
			{
#ifdef ETHERNET_MODE
				USART1_SendStrData("[fail]\r\n", sizeof("[fail]\r\n"));
#else
				//puts("TDC Init Fail\n");
#endif
				//tdc init error
				//TIM_ITConfig(TIM4, TIM_IT_UPDATE, DISABLE);
                __HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);
				LEDControl(LED_COLOR_RED, false);
				LEDControl(LED_COLOR_BLUE, false);
				LEDControl(LED_COLOR_GREEN, false);

				PulsePinInit();
				PulsePinControl(ERROR_OUTPUT_PULSE, PIN_ACTIVE);

				LEDControl(LED_COLOR_RED, true);
				LEDControl(LED_COLOR_GREEN, true);

				while(true)
				{
					WDT_Reload();
                    HAL_Delay(500);
				}
			}
		}

		//DelayMs(100);
        HAL_Delay(100);
	}


	if(g_MainStatus == kStatusMain_Factory)
	{
		g_MotorStatus = kStatusMotor_TdcDataCalibration;
	}
	else
	{
		g_MotorStatus = kStatusMotor_ApdBiasControl;
	}

#ifdef ETHERNET_MODE
//	USART1_SendStrData("[ok]\r\n", sizeof("[ok]\r\n"));
    printf("[ok]\r\n");
#else
	//puts("TDC Init Complete\n");
#endif
}

#if 0
//
	@brief    TDC Calibration
	@details 	factory 모드에서 접근하며, tdc calibration 값과 tdc core1 값을 계산해서 고정값으로 가지기 위함. \n
						tdc calibration 기능을 수행하면서 거리 offset도 함께 구함.
	@author   tg.An
	@date     2021.01.10
	@param    None
	@return   None
	@throw		일정 횟수이상 tdc 초기화를 못하는 경우 error 동작을 수행
	@todo			1. 거리 offset을 구할때 lidar 설치 상태가 지면과 수직으로 설정이 되어야하며, \n
						채널에 따른 거리offset을 다르게 가져가야 할 지 논의가 필요 \n
						2. 만약 거리 offset이 일정 범위이상 벗어나는 경우 bias 컨트롤이 정상적이지 않다고 판단할 수 있으며, \n
						error 처리를 하는 부분을 구현해야 할 것으로 보임. hw 쪽에서 delay가 발생되는 것을 계산해서 범위를 지정해야 할 것으로 보임
	@remark   2021.01.12 : motor speed 제어하는 기능 및 온도보상 추가.
//
//uint8_t slit_num = 0;
//void TDCCalibration(void)
//{
//	uint8_t tdc_errcnt = 0U;
//    uint16_t calcheckcnt = 0U;
//	uint64_t tdc1_calibration1 = 0U, tdc1_calibration2 = 0U;
//	uint64_t tdc2_calibration1 = 0U, tdc2_calibration2 = 0U;
//	uint64_t tdc1_time = 0U, tdc2_time = 0U;
//	double tof2 = 0.0, tof3 = 0.0;
//
//	#ifdef ETHERNET_MODE
////		USART1_SendStrData(" TDC Calibration . . . ", sizeof(" TDC Calibration . . . "));
//    printf(" TDC Calibration . . . ");
//	#else
//		//puts("TDC Calibration Start\n");
//	#endif
//
//	while (g_MotorStatus == kStatusMotor_TdcDataCalibration)	{
//		WDT_Reload();
//
//		while (g_EncoderStatus != kStatusEncoder_Signal) {
//			;
//		}
//
//    g_EncoderStatus = kStatusEncoder_Wait;
//
//    //0 radian에 맞는 채널의 각도에서 거리 오프셋을 맞춤. 만약 각이 올라가게 되면 거리 오차가 더 발생해서 따로 오프셋을 가져야함
//    //0도에서의 오프셋만 먼저 가진 뒤에 나머지 채널에 따른 거리는 채널 각도에 따라 보정하고 offset 적용
//    if(g_CurrentSlitIndex == CH1_CENTER_SLIT) {
//      TDCWriteData(ADDR_TDC_CONFIG1, 0x01U);
//
//      TDC_START_GPIO_Port->BSRR = TDC_START_Pin;
//      TDC_START_GPIO_Port->BSRR = TDC_START_Pin << 16U;
//
//      LD_TRIGGER_GPIO_Port->BSRR = LD_TRIGGER_Pin;
//      LD_TRIGGER_GPIO_Port->BSRR = LD_TRIGGER_Pin << 16U;
//      DelayUs(1U);
//
//      g_TDC1.m_Calibration1 = TDCReadData24bit(TDC_CORE1, ADDR_TDC_CALIBRATION1);
//      g_TDC1.m_Calibration2 = TDCReadData24bit(TDC_CORE1, ADDR_TDC_CALIBRATION2);
//      g_TDC2.m_Calibration1 = TDCReadData24bit(TDC_CORE2, ADDR_TDC_CALIBRATION1);
//      g_TDC2.m_Calibration2 = TDCReadData24bit(TDC_CORE2, ADDR_TDC_CALIBRATION2);
//      g_TDC1.m_Time = TDCReadData24bit(TDC_CORE1, ADDR_TDC_TIME1);
//      g_TDC2.m_Time = TDCReadData24bit(TDC_CORE2, ADDR_TDC_TIME1);
//
//      if((g_TDC1.m_Calibration1 != 0U) && (g_TDC1.m_Calibration2 != 0U)
//			&& (g_TDC2.m_Calibration1 != 0U) && (g_TDC2.m_Calibration2 != 0U)) { /*fixed for MISRA rule 12.4*/
//				tdc1_calibration1 += g_TDC1.m_Calibration1;
//				tdc1_calibration2 += g_TDC1.m_Calibration2;
//				tdc2_calibration1 += g_TDC2.m_Calibration1;
//				tdc2_calibration2 += g_TDC2.m_Calibration2;
//				tdc1_time += g_TDC1.m_Time;
//				tdc2_time += g_TDC2.m_Time;
//
//				calcheckcnt++;
//				if (calcheckcnt == TDC_CALIBRATION_CNT)
//				{
//					g_TDC1.m_Calibration1 = (uint32_t)(tdc1_calibration1 / TDC_CALIBRATION_CNT);
//					g_TDC1.m_Calibration2 = (uint32_t)(tdc1_calibration2 / TDC_CALIBRATION_CNT);
//					g_TDC2.m_Calibration1 = (uint32_t)(tdc2_calibration1 / TDC_CALIBRATION_CNT);
//					g_TDC2.m_Calibration2 = (uint32_t)(tdc2_calibration2 / TDC_CALIBRATION_CNT);
//					g_TDC1.m_Time = (uint32_t)(tdc1_time / TDC_CALIBRATION_CNT);
//					g_TDC2.m_Time = (uint32_t)(tdc2_time / TDC_CALIBRATION_CNT);
//
//					TOFCalculation();
//
//					tdc2_time = g_TDC2.m_Time;
//					tof2 = g_TDC2.m_NormLSB * ((double)tdc2_time);
//					tof3 = tof2 - g_TDC1.m_TOF1;
//
//					// Distance Offset Range Error Check가 필요하다. 만약 어느정도 범위안에 안들어오면 에러처리를 해야함. 보통 -2.0 정도 나옴
//          g_DistanceOffset = (float)(TDC_SETTING_DISTANCE - ((float)LIGHT_SPEED  * tof3 / 2.0)); /*fixed for MISRA rule 10.2*/
//
//					//TIM_ITConfig(TIM1, TIM_IT_CC1, DISABLE);
//                    __HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
//					g_MotorStatus = kStatusMotor_TdcComplete;
//
//#ifdef ETHERNET_MODE
////					USART1_SendStrData("[ok]\r\n", sizeof("[ok]\r\n"));
//                    printf("[ok]\r\n");
//#else
//					//puts("TDC Calibration Complete\n");
//#endif
//				}
//      }
//      else
//      {
//        calcheckcnt = 0U;
//        tdc1_calibration1 = 0U;
//        tdc1_calibration2 = 0U;
//        tdc2_calibration1 = 0U;
//        tdc2_calibration2 = 0U;
//        tdc1_time = 0U;
//        tdc2_time = 0U;
//
//				tdc_errcnt++;
//				if(tdc_errcnt == TDC_CAL_ERR_CNT) {
//
//					//Error Mode로 이동해야함.
//#ifdef ETHERNET_MODE
////					USART1_SendStrData("[fail]\r\n", sizeof("[fail]\r\n"));
//                  printf("[fail]\r\n");
//#else
//					//puts("TDC Calibration Error\n");
//#endif
//          			LEDControl(LED_COLOR_RED, false);
//					LEDControl(LED_COLOR_BLUE, false);
//					LEDControl(LED_COLOR_GREEN, false);
//
//					PulsePinInit();
//					PulsePinControl(ERROR_OUTPUT_PULSE, PIN_ACTIVE);
//
//					LEDControl(LED_COLOR_RED, true);
//					LEDControl(LED_COLOR_GREEN, true);
//
//					while(true) {
//						WDT_Reload();
//                        HAL_Delay(500);
//					}
//				}
//      }
//    }
//		else {
//		}
//
//		/* T.G.AN(2021.02.23) : TDC Calibration 및 거리 Offset을 잡을 때 Motor 속도 및 온도에 따른 APD 바이어스 조절 */
//		if(I2C2_Read(TMP117_ADDRESS, TMP117_CONFIG) == TMP117_COMPLETE) {
//			TemperatureControl();
//		}
//	}
//}
//#else
//void TDCCalibration(void)
//{
//	g_CalibrationMode = 1;
//	g_EncoderCaptureFirstCheck = false;
//    g_CurrentSlitIndex = 0U;
//    g_EncoderCaptureTotalCnt = 0U;
//
//    //USART1_SendString(" TDC Calibration . . . ");
//    printf(" TDC Calibration . . . ");
//	//TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
//    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
//
//    DelayMs(1000);
//
//
//    g_ChannelStatus = kStatusChannel_1;
//    g_RunStatus = kStatusRun_DataComplete;
//    g_MainStatus = kStatusMain_Run;
//    g_MotorStatus = kStatusMotor_CheckStartPointSlit;
//    CheckStartPointSlit();
//
//    RunMode();
//
//	__HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);
//	g_MotorStatus = kStatusMotor_TdcComplete;
//
//    printf("[ok]\r\n");
//
//}
//#endif
//
///**
//    @brief    TDC Calculation
//    @author   tg.An
//    @date     2021.01.12
//    @param    None
//    @return   None
//    @remark   TOF Parameter Calculation \n
//              TDC2 값만 계산을 해주면 되기 때문에 TDC1은 미리 계산을 해둔다. 이후에 TDC2 Read Time 값에서 NormLSB를 곱해서 Distance를 구함. \n
//              Temp 변수를 사용해서 Volatile 연산 Warning 제거.
//*/
//void TOFCalculation(void)
//{
//    double tdc1_calcnt = 0.0, tdc2_calcnt = 0.0;
//	uint32_t _tdc1time = 0U;
//
//    uint32_t tdc1_calibration1 = g_TDC1.m_Calibration1;
//    uint32_t tdc1_calibration2 = g_TDC1.m_Calibration2;
//    uint32_t tdc2_calibration1 = g_TDC2.m_Calibration1;
//    uint32_t tdc2_calibration2 = g_TDC2.m_Calibration2;
//
//    tdc1_calcnt = (double)(tdc1_calibration2 - tdc1_calibration1) / (double)(TDC_CALIBRATION_CLOCK - 1);
//    tdc2_calcnt = (double)(tdc2_calibration2 - tdc2_calibration1) / (double)(TDC_CALIBRATION_CLOCK - 1);
//    g_TDC1.m_NormLSB = 0.0000000625 / tdc1_calcnt; //TDC 입력 Clock 16Mhz
//	g_TDC2.m_NormLSB = 0.0000000625 / tdc2_calcnt;
//
//    /* Volatile Warning */
//    _tdc1time = g_TDC1.m_Time;
//    g_TDC1.m_TOF1 = ((double)_tdc1time) * g_TDC1.m_NormLSB;
//}
//
///**
//	@brief    TDC Write Data
//	@author   tg.An
//	@date     2021.01.10
//	@param    uint8_t addr : TDC Register
//	@param    uint8_t data : Input Command
//	@return   None
//	@remark   0x40 = Write Bit Enable / SPI2 = 16bit Transmit \n
//*/
//void TDCWriteData(uint8_t addr, uint8_t data)
//{
//	uint16_t val = addr;
//	val |= 0x40U;
//	val <<= 8;
//	val |= data;
//
//	TDC_CS1_GPIO_Port->BSRR = TDC_CS1_Pin << 16U; //비선택
//    TDC_CS2_GPIO_Port->BSRR = TDC_CS2_Pin << 16U;
//#if 1
//    SPI2->DR = val;
//	while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET)
//	{
//		;
//	}
//	while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET)
//	{
//		;
//	}
//	SPI2->DR;
//
//#else
//	if(HAL_SPI_Transmit(&hspi2, (uint8_t*)val, 2, 100) != HAL_OK)
//    {
//      txString("TDCWriteData_SPI_Error\r\n");
//    }
//
//#endif
//	TDC_CS1_GPIO_Port->BSRR = TDC_CS1_Pin; //선택(SPI통신)
//    TDC_CS2_GPIO_Port->BSRR = TDC_CS2_Pin;
//}
//
///**
//	@brief    Check TDC Read Data 8Bit
//	@details	tdc에서 입력한 값이 정상적으로 설정되었는지 확인 기능 수행
//	@author   tg.An
//	@date     2021.02.24
//	@param    uint8_t addr : TDC Register
//	@param    uint8_t writedata : 이전에 입력한 tdc data
//	@return   bool result : write한 값과 read한 값이 같으면 true, 다르면 false
//	@remark
//*/
//bool CheckTDCReadData8bit(uint8_t addr, uint8_t writedata)
//{
//	bool result = false;
//	uint8_t tdc1_readdata = 0U, tdc2_readdata = 0U;
//
//	tdc1_readdata = TDCReadData8bit(TDC_CORE1, addr);
//	tdc2_readdata = TDCReadData8bit(TDC_CORE2, addr);
//	if((writedata == tdc1_readdata) && (writedata == tdc2_readdata))
//	{
//		result = true;
//	}
//	else
//	{
//		result = false;
//	}
//
//	return result;
//}
//
///**
//	@brief    TDC Read Data 8Bit
//	@author   tg.An
//	@date     2021.02.24
//	@param    uint8_t core : TDC Corex
//	@param    uint8_t addr : TDC Register
//	@return   uint8_t result : TDC Read 8Bit Data
//	@remark
//*/
//uint8_t TDCReadData8bit(uint8_t core, uint8_t addr)
//{
//	uint16_t val = addr;
//	uint32_t readdata = 0U;
//	uint8_t result = 0U;
//
//  	val <<= 8;
//  	if(core == TDC_CORE1)
//	{
//		TDC_CS1_GPIO_Port->BSRR = TDC_CS1_Pin << 16U;
//  	}
//  	else if(core == TDC_CORE2)
//	{
//		TDC_CS2_GPIO_Port->BSRR = TDC_CS2_Pin << 16U;
//	}
//	else {}
//#if 1
//
//	SPI2->DR = val;
//	while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET)
//	{
//		;
//	}
//	while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET)
//	{
//		;
//	}
//	readdata = (SPI2->DR);
//#else
//    if(HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)val, &result, 2, 100) != HAL_OK)
//	{
//		txString("TDCReadData8bit_SPI_Error\r\n");
//	}
//
//#endif
//	if(core == TDC_CORE1)
//	{
//		TDC_CS1_GPIO_Port->BSRR = TDC_CS1_Pin;
//	}
//  else if(core == TDC_CORE2)
//  {
//		TDC_CS2_GPIO_Port->BSRR = TDC_CS2_Pin;
//	}
//	else {}
//
//	result = (uint8_t)readdata;
//	return result;
//}
//
///**
//	@brief    TDC Read Data 24Bit
//	@author   tg.An
//	@date     2021.01.10
//	@param    uint8_t core : TDC Corex
//	@param    uint8_t addr : TDC Register
//	@return   uint32_t result : TDC Read 24Bit Data
//	@remark
//*/
//
//uint32_t g_Tdc_read_error = 0;
//uint32_t TDCReadData24bit(uint8_t core, uint8_t addr)
//{
//	uint16_t val = addr;
//	uint32_t result = 0U;
//
//    val <<= 8;
//
//  	if(core == TDC_CORE1)
//	{
//		TDC_CS1_GPIO_Port->BSRR = TDC_CS1_Pin << 16U;
//  	}
//  	else if(core == TDC_CORE2)
//	{
//		TDC_CS1_GPIO_Port->BSRR = TDC_CS2_Pin << 16U;
//	}
//	else {}
//#if 1
//    SPI2->DR = val;
//	while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET)
//	{
//		;
//	}
//	while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET)
//	{
//		;
//	}
//	result = (SPI2->DR);
//    result <<= 16;
//
//	SPI2->DR = 0x0000U;
//	while ((SPI2->SR & SPI_FLAG_TXE) == (uint16_t)RESET)
//	{
//		;
//	}
//	while ((SPI2->SR & SPI_FLAG_RXNE) == (uint16_t)RESET)
//	{
//		;
//	}
//	result |= (SPI2->DR);
//
//#else
//
//  if(HAL_SPI_TransmitReceive(&hspi2, buff, read_buff, 4, 1) != HAL_OK)
//  {
//	txString("TDCReadData24bit_SPI_Error\r\n");
//  }
//
//#endif
//  	if(core == TDC_CORE1)
//	{
//		TDC_CS1_GPIO_Port->BSRR = TDC_CS1_Pin;
//	}
//  	else if(core == TDC_CORE2)
//	{
//		TDC_CS2_GPIO_Port->BSRR = TDC_CS2_Pin;
//	}
//	else {}
//#if 0
//  if(result == 0x00000000)
//  {
//    g_Tdc_read_error = 0xFF;
//  }
//  else
//  {
//    g_Tdc_read_error = 0;
//  }
//
//  if(result > 800)
//  {
//    result = 0;
//    return result;
//  }
// #endif
//#if 0
// if(/*(core == TDC_CORE1) && */(addr == ADDR_TDC_TIME1))
// {
//	 if(result > 0xFFFF)
//	 {
//		 printf("Error Read : %d\r\n", result);
//	 }
// }
//#endif
//	return result;
//}
//
///**
//	@brief    TDC configuration
//	@author   tg.An
//	@date     2021.01.10
//	@param    None
//	@return   None
//	@remark
//*/
//#if 0
//void TDCConfig(void)
//{
//	SPI_InitTypeDef SPI_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//
//	GPIO_PinAFConfig(TDC_SCK_Port, GPIO_PinSource13, GPIO_AF_SPI2);
//	GPIO_PinAFConfig(TDC_MISO_Port, GPIO_PinSource2, GPIO_AF_SPI2);
//	GPIO_PinAFConfig(TDC_MOSI_Port, GPIO_PinSource3, GPIO_AF_SPI2);
//
//	GPIO_InitStructure.GPIO_Pin = TDC_SCK_Pin;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(TDC_SCK_Port, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = TDC_MOSI_Pin;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(TDC_MOSI_Port, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = TDC_MISO_Pin;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(TDC_MISO_Port, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = TDC_CS1_Pin | TDC_CS2_Pin;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(TDC_CS_Port, &GPIO_InitStructure);
//	GPIO_SetBits(TDC_CS_Port, TDC_CS1_Pin);
//	GPIO_SetBits(TDC_CS_Port, TDC_CS2_Pin);
//
//	GPIO_InitStructure.GPIO_Pin = TDC_START_Pin;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(TDC_START_Port, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = TDC_INT1_Pin | TDC_INT2_Pin;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(TDC_INT_Port, &GPIO_InitStructure);
//
//	/* SPI2 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
//
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial = 10U;
//	SPI_Init(SPI2, &SPI_InitStructure);
//	SPI_Cmd(SPI2, ENABLE);
//}
//#endif

