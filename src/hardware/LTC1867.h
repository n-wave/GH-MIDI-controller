
/*
 *      DAC LTC1863
 *  
 *    Mario Van Etten 
 *  
 *       24-02-2017
 * 
 * SPI Communication for 
 * the LTC1863 16Bit
 * Digital Audio Converter. 
 * 
 * This specific project
 * uses two DAC's, thus 
 * they are sampled in the 
 * same interrupt.
 * 
 * two seperate SI classes
 *
 */

/* 
 *  channel configuration 
 * 8 channels 
 * single ended 
 * unipolar 
 * input
 * 
 */
#ifndef LTC1863_H
#define LTC1863_H

#include "Arduino.h"
#include <SPI.h>
#include "../testing/configuration.h"

namespace ltc1867 {
	extern uint8_t EN_DAC1; // Enable the Buffers DAC1, active low, if high the buffer is in a high impedance state
	extern uint8_t CS_DAC1; // chipSelect pin DAC1 take high for at least 2 uS and then low
	extern uint8_t EN_DAC2; // Enable the Buffers DAC1, active low, if high the buffer is in a high impedance state
	extern uint8_t CS_DAC2;// chipSelect pin DAC2

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
} // namespace ltc1867
#endif




