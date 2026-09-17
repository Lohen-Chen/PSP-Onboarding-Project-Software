/*
 * ADC.c
 *
 *  Created on: Sep 15, 2026
 *      Author: Lohen Chen
 */

#include "ADC.h"
extern SPI_HandleTypeDef hspi1;

uint16_t readFromADCChannel(uint8_t channel){
	uint8_t byte1 = 0b00000110 | ((channel >> 2) & 0x01); // 100 -> 00000001
	uint8_t byte2 = 0b00000000 | ((channel & 0x03) << 6); // 001 -> 01000000
	uint8_t byte3 = 0x00;

	uint8_t txBuf[3] = { byte1, byte2, byte3 };
	uint8_t rxBuf[3];

	uint16_t result = 0;

	HAL_GPIO_WritePin(ADC_CS_GPIO_Port, ADC_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, txBuf, rxBuf, 3, 100);
	HAL_GPIO_WritePin(ADC_CS_GPIO_Port, ADC_CS_Pin, GPIO_PIN_SET);

	result |= (rxBuf[1] & 0b00001111) << 8; //must mask out the useless bits
	result |= rxBuf[2];

	return result;
}



