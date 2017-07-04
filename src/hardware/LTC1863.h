
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

#define CHANNEL_0 0x84 // 10000100 00000000
#define CHANNEL_1 0xC4 // 11000100 00000000
#define CHANNEL_2 0x94 // 10010100 00000000
#define CHANNEL_3 0xD4 // 11010100 00000000
#define CHANNEL_4 0xA4 // 10100100 00000000
#define CHANNEL_5 0xE4 // 11100100 00000000
#define CHANNEL_6 0xB4 // 10110100 00000000
#define CHANNEL_7 0xF4 // 11110100 00000000

#define CS_DAC1 10 // chipSelect pin take high for at least 2 uS and then low 
#define CS_DAC2 9


extern volatile unsigned int channelSelection[8];
extern volatile unsigned int DAC1[8];             
extern volatile unsigned int DAC2[8];
extern unsigned int inx;

void LTC1863_init();
void LTC1863_readSensors();   
void LTC1863_readDAC1();
void LTC1863_readDAC2();

#endif                   


