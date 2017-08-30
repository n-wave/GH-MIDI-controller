
#include <SPI.h>
#include "LTC1867.h"

 unsigned int channelSelection[8] = {
		 	 	 	 	 	 	 	  CHANNEL_0,
                                      CHANNEL_1,
                                      CHANNEL_2,
                                      CHANNEL_3,
                                      CHANNEL_4,
                                      CHANNEL_5,
                                      CHANNEL_6,
                                      CHANNEL_7
                                    };

uint8_t offsetTable[16] = {
							50,	//Head Potentiometer 1
							50, //Head Potentiometer 2
							50, //Head Potentiometer 3
							50, //Head Potentiometer 4
							50, //Head Potentiometer 5
							50, //Head Potentiometer 6
							75, //Ribbon 1
							75, //Ribbon 2
							50, //Pressure 1
							50, //Pressure 2
							50, //Pressure 3
							50, //Body Pot 1
							50, //Body Pot 2
							50, //Body Pot 3
							50, //X axis
							50, //Y Axis
						  };

//Values used for the appropiate offset used in the mappen
//of the averaged values to 14Bit values

uint16_t mapTable[16][2] = {
							 {500, 65503}, //Head Potentiometer 1
							 {500, 65503}, //Head Potentiometer 2
							 {500, 65503}, //Head Potentiometer 3
							 {500, 65503}, //Head Potentiometer 4
							 {500, 65503}, //Head Potentiometer 5
							 {500, 65503}, //Head Potentiometer 6
							 {500, 65503}, //Ribbon 1
							 {500, 65503}, //Ribbon 2
							 {200, 65503}, //Pressure 1
							 {200, 65503}, //Pressure 2
							 {200, 65503}, //Pressure 3
							 {500, 65503}, //Body Pot 1
							 {516, 65503}, //Body Pot 2
							 {960, 65503}, //Body Pot 3
							 {450, 65503}, //X - axis
							 {450, 65503}, //Y - axis
						   };

volatile uint32_t sensors[16] = {0};
volatile uint16_t mappedValues[16] = {0};

#ifdef DEBUG
	volatile uint16_t averagedValues[16] = {0};
#endif /* DEBUG */


unsigned int addressIndex = 0;
unsigned int memoryIndex = 7;

unsigned int highVal = 0;
unsigned int lowVal = 0;
unsigned int bit14 = 0;

void LTC1867_init() {
  //Set middlePoint position for the X and Y axis of the joystick/
  averagedValues[14] = 32767;
  averagedValues[15] = 32767;

  SPI.setSCK(14);   //Has no Led attached on the boards better pulse from the clock
  SPI.setMOSI(11);
  SPI.setMISO(12);

  //Set Pins associated with ADC1
  pinMode(EN_DAC1, OUTPUT);
  digitalWrite(EN_DAC1, HIGH); //Active LOW thus disabled

  pinMode(CS_DAC1, OUTPUT);
  digitalWrite(CS_DAC1, LOW); //short Pulse

  //Set Pins associated with ADC2
  pinMode(EN_DAC2, OUTPUT);
  digitalWrite(EN_DAC2, HIGH);

  pinMode(CS_DAC2, OUTPUT);
  digitalWrite(CS_DAC2, LOW);

  SPI.begin();
}
/*
   Read value's from the
   two digital Audio Converters


*/
void LTC1867_readSensors() {
  addressIndex = addressIndex & 7;
  memoryIndex = memoryIndex & 7;

  LTC1867_readDAC1();
  LTC1867_readDAC2();

  addressIndex++;
  memoryIndex ++;
}

void LTC1867_readDAC1() {
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));

  digitalWrite(CS_DAC1, HIGH);
  delayMicroseconds(2);
  digitalWrite(CS_DAC1, LOW);

  digitalWrite(EN_DAC1, LOW); //Enable the buffers DAC1

  highVal = 0;
  lowVal = 0;

  highVal = SPI.transfer(channelSelection[addressIndex]); //Send channel for next cycle and exhange MSB
  lowVal = SPI.transfer(0x00); //Send 8Bytes of 0x00 and store LSB

  //Sum up 128 times and calculated averages do a test with max 16Bit value (1000 * 128) >> 7 = 1000 //passed without cabling
  //ToDo calculate effective update frequency for midi
  //After averaging has taken place set initial values to zero.
  //Disable interrupts when resetting the values

  sensors[memoryIndex] += (highVal<<8) + lowVal;


  //Finished disable buffers DAC1
  digitalWrite(EN_DAC1, HIGH); //DISABLE the buffers DAC1

  SPI.endTransaction();
}

void LTC1867_readDAC2() {
  SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE1));

  digitalWrite(CS_DAC2, HIGH);
  delayMicroseconds(2);
  digitalWrite(CS_DAC2, LOW);
  digitalWrite(EN_DAC2, LOW); //Enable the buffers DAC1

  highVal = 0;
  lowVal = 0;
  
  highVal = SPI.transfer(channelSelection[addressIndex]); //Send channel for next cycle and exhange MSB
  lowVal = SPI.transfer(0x00); //Send 8Bytes of 0x00 and store LSB

  sensors[memoryIndex + 8] += (highVal<<8) + lowVal;

  //Finished disable buffers DAC1
  digitalWrite(EN_DAC2, HIGH); //DISABLE the buffers DAC2
  
  SPI.endTransaction();
}

void LTC1867_calculateAverage(){
	uint32_t tmpValue;

  for(int i=0; i<8; i++){
	  tmpValue = sensors[i] >> 7;

	  if(tmpValue <= (averagedValues[i] - offsetTable[i]) || tmpValue >= (averagedValues[i] + offsetTable[i])){
		  averagedValues[i] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[i][0] , mapTable[i][1]);
		  mappedValues[i] = map(tmpValue, mapTable[i][1], mapTable[i][0], 0, 16383) & 0xFFFF;
	  }
	  tmpValue = 0;
 	  sensors[i] = 0; // reset and start summing the values again
  }

  for(int i=8; i<11; i++){
	  tmpValue = sensors[i] >> 7;

	  if(tmpValue <= (averagedValues[i] - offsetTable[i]) || tmpValue >= (averagedValues[i] + offsetTable[i])){
		  averagedValues[i] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[i][0] , mapTable[i][1]);
		  mappedValues[i] = map(tmpValue, mapTable[i][1], mapTable[i][0], 16383, 0) & 0xFFFF;
	  }
	  tmpValue = 0;
 	  sensors[i] = 0; // reset and start summing the values again
  }

  for(int i=11; i<16; i++){
	  tmpValue = sensors[i] >> 7;

	  if(tmpValue <= (averagedValues[i] - offsetTable[i]) || tmpValue >= (averagedValues[i] + offsetTable[i])){
		  averagedValues[i] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[i][0] , mapTable[i][1]);
		  mappedValues[i] = map(tmpValue, mapTable[i][1], mapTable[i][0], 0, 16383) & 0xFFFF;
	  }
	  tmpValue = 0;
 	  sensors[i] = 0; // reset and start summing the values again
  }
 //Offset for the joystick this way it will be st up in the middle position
}


