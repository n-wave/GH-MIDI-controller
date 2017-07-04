
#include "LTC1863.h"
#include <SPI.h>

volatile unsigned int channelSelection[8] = {CHANNEL_0,
                                             CHANNEL_1,
                                             CHANNEL_2,
                                             CHANNEL_3,
                                             CHANNEL_4,
                                             CHANNEL_5,
                                             CHANNEL_6,
                                             CHANNEL_7
                                            };


volatile unsigned int DAC1[8] = {
                                 0,  //Head Potentiometer 1
                                 0,  //Head Potentiometer 2
                                 0,  //Head Potentiometer 3
                                 0,  //Head Potentiometer 4
                                 0,  //Head Potentiometer 5
                                 0,  //Head Potentiometer 6
                                 0,  //Ribbon 1
                                 0   //Ribbon 2
                                 }; 

volatile unsigned int DAC2[8] = {
                                 0,  //Pressure Sensor 1
                                 0,  //Pressure Sensor 2
                                 0,  //Pressure Sensor 3
                                 0,  //Body Potentiometer 1
                                 0,  //Body Potentiometer 2
                                 0,  //Tremelo Potentiometer 3
                                 0,  //JoyStick X
                                 0   //JoyStick Y
                                 }; 

                                 
unsigned int addressIndex = 0;
unsigned int memoryIndex = 7;

unsigned int highVal = 0;
unsigned int lowVal = 0;

SPIClass SPIDAC;

void LTC1863_init() {
  SPIDAC.setSCK(13);
  SPIDAC.setMOSI(11);
  SPIDAC.setMISO(12);
  pinMode(CS_DAC1, OUTPUT);
  digitalWrite(CS_DAC1, LOW);

  pinMode(CS_DAC2, OUTPUT);
  digitalWrite(CS_DAC2, LOW);

  SPIDAC.begin();
}
/*
   Read value's from the
   two digital Audio Converters


*/
void LTC1863_readSensors() {
  addressIndex = addressIndex & 7;
  memoryIndex = memoryIndex & 7;
 


  SPIDAC.setSCK(13);
  SPIDAC.setMOSI(11);
  SPIDAC.setMISO(12);

  SPIDAC.begin();
  LTC1863_readDAC1();
  SPIDAC.end();

  SPIDAC.setSCK(14);
  SPIDAC.setMISO(8);
  SPIDAC.setMOSI(7);

  

  SPIDAC.begin();
  LTC1863_readDAC2();
  SPIDAC.end();
  
  addressIndex++;
  memoryIndex ++;
}

void LTC1863_readDAC1() {
   SPIDAC.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

  digitalWrite(CS_DAC1, HIGH);
  delayMicroseconds(10);
  digitalWrite(CS_DAC1, LOW);

  highVal = 0;
  lowVal = 0;

  highVal = SPIDAC.transfer(channelSelection[addressIndex]);
  lowVal = SPIDAC.transfer(0x00);

  DAC1[memoryIndex] = highVal << 8;
  DAC1[memoryIndex] = DAC1[memoryIndex] + lowVal;
  
  SPIDAC.endTransaction();
}

void LTC1863_readDAC2() {
  SPIDAC.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

  digitalWrite(CS_DAC2, HIGH);
  delayMicroseconds(10);
  digitalWrite(CS_DAC2, LOW);

  highVal = 0;
  lowVal = 0;

  highVal = SPIDAC.transfer(channelSelection[addressIndex]);
  lowVal = SPIDAC.transfer(0x00);

  DAC2[memoryIndex] = highVal << 8;
  DAC2[memoryIndex] = DAC2[memoryIndex] + lowVal;

  SPIDAC.endTransaction();  
}



