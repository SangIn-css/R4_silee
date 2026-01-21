#ifndef __eth_h__
#define __eth_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define USE_SPI1_DIRECT 1 

// Common Register Addresses
#define MR 0x0000
#define GAR 0x0001
#define SUBR 0x0005
#define SHAR 0x0009
#define SIPR 0x000F
#define INTLEVEL 0x0013
#define IR 0x0015
#define IMR 0x0016
#define SIR 0x0017
#define SIMR 0x0018
#define RTR 0x0019
#define RCR 0x001B
#define PTIMER 0x001C
#define PMAGIC 0x001D
#define PHAR 0x001E
#define PSID 0x0024
#define PMRU 0x0026
#define UIPR 0x0028
#define UPORTR 0x002C
#define PHYCFGR 0x002E
#define VERSIONR 0x0039

// Socket Register Addresses
#define Sn_MR 0x0000
#define Sn_CR 0x0001
#define Sn_IR 0x0002        
#define Sn_SR 0x0003
#define Sn_PORT 0x0004
#define Sn_DHAR 0x0006
#define Sn_DIPR 0x000C
#define Sn_DPORT 0x0010
#define Sn_MSSR 0x0012
#define Sn_TOS 0x0015
#define Sn_TTL 0x0016
#define Sn_TX_FSR 0x0020
#define Sn_TX_RD 0x0022
#define Sn_TX_WR 0x0024
#define Sn_RX_RSR 0x0026
#define Sn_RX_RD 0x0028
#define Sn_RX_WR 0x002A
#define Sn_IMR 0x002C
#define Sn_FRAG 0x002D
#define Sn_KPALVTR 0x002F

// BSB
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
