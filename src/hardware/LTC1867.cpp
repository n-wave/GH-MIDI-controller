

#include "LTC1867.h"

 unsigned int channelSelection[8] = {
		 	 	 	 	 	 	 	  0x84,	//Channel 0
									  0xC4, //Channel 1
									  0x94, //Channel 2
									  0xD4, //Channel 3
									  0xA4, //Channel 4
									  0xE4, //Channel 5
									  0xB4, //Channel 6
									  0xF4  //Channel 7
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
							 {1000, 65475}, //Body Pot 3
							 {450, 65503}, //X - axis
							 {450, 65503}, //Y - axis
						   };

volatile uint32_t sensors[16] = {0};
volatile uint16_t mappedValues[16] = {0};

volatile uint16_t averagedValues[16] = {0};

SPISettings settings = SPISettings(16000000, MSBFIRST, SPI_MODE1);

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

void LTC1867_reset(){
	sensors[16] = {0};
	mappedValues[16] = {0};
	averagedValues[16] = {0};

	addressIndex = 0;
	memoryIndex = 7;

	digitalWrite(EN_DAC1, HIGH); //Active LOW thus disabled
	digitalWrite(CS_DAC1, LOW); //short Pulse
	digitalWrite(EN_DAC2, HIGH);
	digitalWrite(CS_DAC2, LOW);
}


/* Short pulse on the chip enable pin
 * This will signal the ADC to start
 * sampling and convert the analog to
 * the a digital value
 *
 * The pin number is 7 and is accesible
 * via the D port register on bit 3
 * which can be set by executing.
 *
 * GPIOD_PDOR |= (1<<3);
 * 			 or
 * GPIOD_PDOR |= B1000 >> saves a bitshift
 *
 * saves a bitshift
 *
 * instead of the function call:
 * digitalWrite(CS_ADC1, HIGH)
 *
 * The delayMicroSeconds is needed as a delay
 * to give the ADC time to setup the next
 * conversion and retrieve the previous
 * conversion based on the requested address
 * prior to the current conversion
 *
 * After the delay the CS and EN pin are
 * taken low and thus enabling the tristate
 * buffer and signal the ADC that a SPI transfer
 * will occur. The EN pin is bit 2 on the D port
 * and both bits 3 and 2 can be cleared by
 *
 * GPIOD_PDOR &= ~B1100;
 *
 * instead of the two function calls
 *
 * digitalWrite(CS_ADC1, LOW)
 * digitalWrite(EN_ADC1, LOW);
 */


void LTC1867_readSensors() {
  SPI.beginTransaction(settings);

  addressIndex = addressIndex & 7;
  memoryIndex = memoryIndex & 7;

  //Start Reading ADC1

  GPIOD_PDOR |= B1000; // pin 7 HIGH -> CS_ADC1
  delayMicroseconds(3); // delayMicroseconds 2 is to short

  GPIOD_PDOR &= ~B1100; // pin 7 & 8 LOW -> CS_ADC1 and EN_ADC1

  highVal = SPI.transfer(channelSelection[addressIndex]); //Send channel for next cycle and exhange MSB
  lowVal = SPI.transfer(0x00); //Send 8Bytes of 0x00 and store LSB

  //Sum up 128 times and calculated averages do a test with max 16Bit value (1000 * 128) >> 7 = 1000 //passed without cabling
  //After averaging has taken place set initial values to zero.
  //Disable interrupts when resetting the values

  sensors[memoryIndex] += (highVal<<8) + lowVal;

  //Finished disable buffers DAC1
  GPIOD_PDOR |= B0100; //digitalWrite(EN_ADC, HIGH); //DISABLE the buffers DAC1

  //Start Reading ADC1
  GPIOC_PDOR |= B10000; //  digitalWrite(CS_ADC, HIGH);
  delayMicroseconds(3);

  GPIOC_PDOR  &= ~B11000;  	  //digitalWrite(CS_DAC2, LOW);
  	  	  	  	  	  	  	  //digitalWrite(EN_DAC2, LOW); //Enable the buffers DAC1

  highVal = SPI.transfer(channelSelection[addressIndex]); //Send channel for next cycle and exhange MSB
  lowVal = SPI.transfer(0x00); //Send 8Bytes of 0x00 and store LSB

  sensors[memoryIndex + 8] += (highVal<<8) + lowVal;

  //Finished disable buffers ADC2
  GPIOC_PDOR |= B1000; //digitalWrite(EN_DAC2, HIGH); //DISABLE the buffers DAC2

  addressIndex++;
  memoryIndex ++;

  SPI.endTransaction();
}


/* Optimize use double buffering
 * and swap the buffers
 */

void LTC1867_calculateAverage(){
	uint32_t tmpValue;

  for(int i=0; i<8; i++){
	  //sensors[i] are (128)summed up values by
	  //by bit shifting with >> 7 a fast division of 128 takes place

	  tmpValue = sensors[i] >> 7;

	  if(tmpValue <= (averagedValues[i] - offsetTable[i]) || tmpValue >= (averagedValues[i] + offsetTable[i])){
		  averagedValues[i] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[i][0] , mapTable[i][1]);
		  mappedValues[i] = map(tmpValue, mapTable[i][1], mapTable[i][0], 0, 16384) & 0xFFFF;
	  }
	  tmpValue = 0;
 	  sensors[i] = 0; // reset and start summing the values again
  }

  for(int i=8; i<11; i++){
	  tmpValue = sensors[i] >> 7;

	  if(tmpValue <= (averagedValues[i] - offsetTable[i]) || tmpValue >= (averagedValues[i] + offsetTable[i])){
		  averagedValues[i] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[i][0] , mapTable[i][1]);
		  mappedValues[i] = map(tmpValue, mapTable[i][1], mapTable[i][0], 16384, 0) & 0xFFFF;
	  }
	  tmpValue = 0;
 	  sensors[i] = 0; // reset and start summing the values again
  }

  for(int i=11; i<16; i++){
	  tmpValue = sensors[i] >> 7;

	  if(tmpValue <= (averagedValues[i] - offsetTable[i]) || tmpValue >= (averagedValues[i] + offsetTable[i])){
		  averagedValues[i] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[i][0] , mapTable[i][1]);
		  mappedValues[i] = map(tmpValue, mapTable[i][1], mapTable[i][0], 0, 16384) & 0xFFFF;
	  }
	  tmpValue = 0;
 	  sensors[i] = 0; // reset and start summing the values again
  }
 //Offset for the joystick this way it will be st up in the middle position
}


