#ifndef __eth_h__
#define __eth_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define USE_SPI1_DIRECT 1 

#define SIMR 0x0018


#define Common_Register 00000
#define Socket_0_Register 00001
#define Socket_0_Tx_Register 00010
#define Socket_0_Rx_Register 00011
#define Socket_1_Register 00101
#define Socket_1_Tx_Register 00110
#define Socket_1_Rx_Register 00111
#define Socket_2_Register 01001
#define Socket_2_Tx_Register 01010
#define Socket_2_Rx_Register 01011
#define Socket_3_Register 01101
#define Socket_3_Tx_Register 01110
#define Socket_3_Rx_Register 01111
#define Socket_4_Register 10001
#define Socket_4_Tx_Register 10010
#define Socket_4_Rx_Register 10011
#define Socket_5_Register 10101
#define Socket_5_Tx_Register 10110
#define Socket_5_Rx_Register 10111
#define Socket_6_Register 11001
#define Socket_6_Tx_Register 11010
#define Socket_6_Rx_Register 11011
#define Socket_7_Register 11101
#define Socket_7_Tx_Register 11110
#define Socket_7_Rx_Register 11111

void eth_Write_Data();
void eth_Write_1Byte(uint16_t addr, uint8_t BSB, uint8_t data);
void eth_Write_nByte(uint16_t addr, uint8_t BSB, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif
