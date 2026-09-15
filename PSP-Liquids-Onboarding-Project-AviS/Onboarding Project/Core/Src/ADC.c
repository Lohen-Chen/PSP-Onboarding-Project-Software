/*
 * ADC.c
 *
 *  Created on: Sep 15, 2026
 *      Author: Lohen Chen
 */

#include "ADC.h"

uint16_t readFromADCChannel(uint8_t channel){
	uint8_t byte1 = 0b00000110 | ((channel >> 2) & 0x01); // 100 -> 00000001
	uint8_t byte2 = 0b00000000 | ((channel << 6) & 0x03); //001 -> 01000000
	uint8_t byte3 = 0x00;

	uint8_t txBuf[3] = { byte1, byte2, byte3 };
	uint8_t rxBuf[3];

	HAL_SPI_TransmitReceive(&hspi1, txBuf, rxBuf, 3, 1000);
}
