/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void delay_us(uint16_t time);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DETECT1_PULSE_PC13_Pin GPIO_PIN_13
#define DETECT1_PULSE_PC13_GPIO_Port GPIOC
#define FEEDBACK_SWITCH_PC14_Pin GPIO_PIN_14
#define FEEDBACK_SWITCH_PC14_GPIO_Port GPIOC
#define DETECT_PULSE_PC15_Pin GPIO_PIN_15
#define DETECT_PULSE_PC15_GPIO_Port GPIOC
#define MCU_MAIN_CLK_Pin GPIO_PIN_0
#define MCU_MAIN_CLK_GPIO_Port GPIOH
#define SPI3_CS_BIASCTRL_PC00_Pin GPIO_PIN_0
#define SPI3_CS_BIASCTRL_PC00_GPIO_Port GPIOC
#define SPI3_MOSI_BIASCTRL_PC01_Pin GPIO_PIN_1
#define SPI3_MOSI_BIASCTRL_PC01_GPIO_Port GPIOC
#define SPI2_MISO_TDC_PC02_Pin GPIO_PIN_2
#define SPI2_MISO_TDC_PC02_GPIO_Port GPIOC
#define SPI2_MOSI_TDC_PC03_Pin GPIO_PIN_3
#define SPI2_MOSI_TDC_PC03_GPIO_Port GPIOC
#define ADC_IN1_LDVOL_PA01_Pin GPIO_PIN_1
#define ADC_IN1_LDVOL_PA01_GPIO_Port GPIOA
#define R4_VER_0_Pin GPIO_PIN_2
#define R4_VER_0_GPIO_Port GPIOA
#define R4_VER_1_Pin GPIO_PIN_3
#define R4_VER_1_GPIO_Port GPIOA
#define SPI1_SCK_ETHERNET_PA05_Pin GPIO_PIN_5
#define SPI1_SCK_ETHERNET_PA05_GPIO_Port GPIOA
#define SPI1_MISO_ETHERNET_PA06_Pin GPIO_PIN_6
#define SPI1_MISO_ETHERNET_PA06_GPIO_Port GPIOA
#define SPI1_MOSI_ETHERNET_PA07_Pin GPIO_PIN_7
#define SPI1_MOSI_ETHERNET_PA07_GPIO_Port GPIOA
#define TDC_INTB1_PC4_Pin GPIO_PIN_4
#define TDC_INTB1_PC4_GPIO_Port GPIOC
#define TDC_INTB2_PC5_Pin GPIO_PIN_5
#define TDC_INTB2_PC5_GPIO_Port GPIOC
#define ADC1_IN8_APDBIAS_PB00_Pin GPIO_PIN_0
#define ADC1_IN8_APDBIAS_PB00_GPIO_Port GPIOB
#define ADC1_IN8_MAINVOL_PB01_Pin GPIO_PIN_1
#define ADC1_IN8_MAINVOL_PB01_GPIO_Port GPIOB
#define LD_TRIG_PB02_Pin GPIO_PIN_2
#define LD_TRIG_PB02_GPIO_Port GPIOB
#define I2C2_SCL_TEMP_PB10_Pin GPIO_PIN_10
#define I2C2_SCL_TEMP_PB10_GPIO_Port GPIOB
#define ENET_SCSn_Pin GPIO_PIN_12
#define ENET_SCSn_GPIO_Port GPIOB
#define SPI2_SCLK_TDC_PB13_Pin GPIO_PIN_13
#define SPI2_SCLK_TDC_PB13_GPIO_Port GPIOB
#define ENET_RSTn_Pin GPIO_PIN_14
#define ENET_RSTn_GPIO_Port GPIOB
#define ENET_INTn_Pin GPIO_PIN_15
#define ENET_INTn_GPIO_Port GPIOB
#define TIM3_CH1_PWM_BLDC_PC06_Pin GPIO_PIN_6
#define TIM3_CH1_PWM_BLDC_PC06_GPIO_Port GPIOC
#define GUIDE_LD_PC07_Pin GPIO_PIN_7
#define GUIDE_LD_PC07_GPIO_Port GPIOC
#define ERR_PULSE_Pin GPIO_PIN_8
#define ERR_PULSE_GPIO_Port GPIOC
#define IND_RED_LED_PC09_Pin GPIO_PIN_9
#define IND_RED_LED_PC09_GPIO_Port GPIOC
#define TIM1_CH1_ENC_INPUT_PA08_Pin GPIO_PIN_8
#define TIM1_CH1_ENC_INPUT_PA08_GPIO_Port GPIOA
#define MAIN_UART1_TX_PA09_Pin GPIO_PIN_9
#define MAIN_UART1_TX_PA09_GPIO_Port GPIOA
#define MAIN_UART1_RX_PA10_Pin GPIO_PIN_10
#define MAIN_UART1_RX_PA10_GPIO_Port GPIOA
#define R4_VER_2_Pin GPIO_PIN_11
#define R4_VER_2_GPIO_Port GPIOA
#define R4_VER_3_Pin GPIO_PIN_12
#define R4_VER_3_GPIO_Port GPIOA
#define SYS_JTMS_PA13_Pin GPIO_PIN_13
#define SYS_JTMS_PA13_GPIO_Port GPIOA
#define SYS_JTCK_PA14_Pin GPIO_PIN_14
#define SYS_JTCK_PA14_GPIO_Port GPIOA
#define SYS_JTDI_PA15_Pin GPIO_PIN_15
#define SYS_JTDI_PA15_GPIO_Port GPIOA
#define SPI3_SCLK_BIASCTRL_PC10_Pin GPIO_PIN_10
#define SPI3_SCLK_BIASCTRL_PC10_GPIO_Port GPIOC
#define I2C2_SDA_TEMP_PC12_Pin GPIO_PIN_12
#define I2C2_SDA_TEMP_PC12_GPIO_Port GPIOC
#define SYS_JTRST_PB04_Pin GPIO_PIN_4
#define SYS_JTRST_PB04_GPIO_Port GPIOB
#define IND_BLU_LED_PB05_Pin GPIO_PIN_5
#define IND_BLU_LED_PB05_GPIO_Port GPIOB
#define SPI2_CS1_TDC_PB06_Pin GPIO_PIN_6
#define SPI2_CS1_TDC_PB06_GPIO_Port GPIOB
#define SPI2_CS2_TDC_PB07_Pin GPIO_PIN_7
#define SPI2_CS2_TDC_PB07_GPIO_Port GPIOB
#define REF_SIG_PB08_Pin GPIO_PIN_8
#define REF_SIG_PB08_GPIO_Port GPIOB
#define IND_GRN_LED_PB09_Pin GPIO_PIN_9
#define IND_GRN_LED_PB09_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
