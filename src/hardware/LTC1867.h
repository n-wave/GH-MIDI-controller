
/*
 *      ADC LTC1867
 *  
 *    Mario Van Etten 
 *  
 *       24-02-2017
 * 
 * SPI Communication for 
 * the LTC1867 16Bit
 * Analog Digital Converter.
 * 
 * This specific project
 * uses two ADC's, these
 * are sampled in the
 * same interrupt.
 *
 */



#ifndef LTC1867_H
#define LTC1867_H

#include "Arduino.h"
#include <SPI.h>
#include "../testing/configuration.h"

namespace ltc1867 {
	extern uint8_t en_adc1; // Enable the Buffers ADC1, active low, if high the buffer is in a high impedance state
	extern uint8_t cs_adc1; // chipSelect pin ADC1 take high for at least 2 uS and then low
	extern uint8_t en_adc2; // Enable the Buffers ADC2, active low, if high the buffer is in a high impedance state
	extern uint8_t cs_adc2;// chipSelect pin ADC2

	extern unsigned int channelSelection[8];

	extern volatile uint32_t* writePtrOne;
	extern volatile uint32_t* writePtrTwo;
	extern volatile uint32_t* bufferPtr;

	extern volatile uint32_t bufferOne[16];
	extern volatile uint32_t bufferTwo[16];


	extern volatile boolean bufferActive; //buffer active  0 = bufferOne, 1 = bufferTwo


	extern SPISettings settings;

	extern uint16_t averagedValues[16];
	extern uint16_t mappedValues[16];
	extern uint16_t offsetTable[16];  //hysteresis table for every sensor
	extern uint16_t mapTable[16][2];

	void init();
	void reset();
	void readSensors();

	void swapBuffer();

	void calculateAverage();

	void mapValues();
} // namespace LTC1867_H
#endif //LTC1867_H




