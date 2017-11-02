
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

#define EN_DAC1 7 // Enable the Buffers DAC1, active low, if high the buffer is in a high impedance state
#define CS_DAC1 8 // chipSelect pin DAC1 take high for at least 2 uS and then low 
#define EN_DAC2 9 // Enable the Buffers DAC1, active low, if high the buffer is in a high impedance state
#define CS_DAC2 10// chipSelect pin DAC2 

#include "Arduino.h"
#include <SPI.h>
#include "../testing/configuration.h"

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

void LTC1867_init();
void LTC1867_reset();
void LTC1867_readSensors();

void LTC1867_swapBuffer();

void LTC1867_calculateAverage();

void LTC1867_mapValues();

#endif




