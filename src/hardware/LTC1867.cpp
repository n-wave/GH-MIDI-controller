

#include "LTC1867.h"

namespace ltc1867 {

uint8_t en_adc1 = 7; // Enable the Buffers ADC1, active low, if high the buffer is in a high impedance state
uint8_t cs_adc1 = 8; // chipSelect pin ADC1 take high for at least 2 uS and then low
uint8_t en_adc2 = 9; // Enable the Buffers ADC2, active low, if high the buffer is in a high impedance state
uint8_t cs_adc2 = 10;// chipSelect pin ADC2


/*
 * channel configuration
 * 8 channels
 * single ended
 * unipolar input
 *
 */

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

uint16_t offsetTable[16] = {
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
							75, //Body Pot 1
							75, //Body Pot 2
							75, //Body Pot 3
							50, //X axis
							50, //Y Axis
						  };

//Values used for the appropiate offset used in the mappen
//of the averaged values to 14Bit values

uint16_t mapTable[16][2] = {
							 {500, 65500}, //Head Potentiometer 1
							 {500, 65500}, //Head Potentiometer 2
							 {500, 65500}, //Head Potentiometer 3
							 {500, 65500}, //Head Potentiometer 4
							 {500, 65500}, //Head Potentiometer 5
							 {500, 65500}, //Head Potentiometer 6
							 {500, 65500}, //Ribbon 1
							 {500, 65500}, //Ribbon 2
							 {200, 65500}, //Pressure 1
							 {200, 65500}, //Pressure 2
							 {200, 65500}, //Pressure 3
							 {500, 62000}, //Body Pot 1
							 {516, 62000}, //Body Pot 2
							 {1000, 62000}, //Body Pot 3
							 {450, 65503}, //X - axis
							 {450, 65503}, //Y - axis
						   };

SPISettings settings = SPISettings(16000000, MSBFIRST, SPI_MODE1);

volatile uint32_t* writePtrOne = NULL;
volatile uint32_t* writePtrTwo = NULL;
volatile uint32_t* bufferPtr = NULL;

volatile uint32_t bufferOne[16] = {0};
volatile uint32_t bufferTwo[16] = {0};

uint16_t mappedValues[16] = {0};
uint16_t averagedValues[16] = {0};

volatile boolean bufferActive = 0;

volatile unsigned int addressIndex = 0;
volatile unsigned int memoryIndex = 7;

volatile unsigned int highVal = 0;
volatile unsigned int lowVal = 0;

void init() {
  //ToDo Set middlePoint position for the X and Y axis of the joystick/

  bufferActive = 0;
  writePtrOne = &bufferOne[0];
  writePtrTwo = &bufferOne[8];
  bufferPtr = bufferTwo;

  SPI.setSCK(14);   //Has no Led attached on the board better pulse from the clock
  SPI.setMOSI(11);
  SPI.setMISO(12);

  //Set Pins associated with ADC1
  pinMode(en_adc1, OUTPUT);
  digitalWrite(en_adc1, HIGH); //Active LOW thus disabled

  pinMode(cs_adc1, OUTPUT);
  digitalWrite(cs_adc1, LOW); //short Pulse

  //Set Pins associated with ADC2
  pinMode(en_adc2, OUTPUT);
  digitalWrite(en_adc2, HIGH);

  pinMode(cs_adc2, OUTPUT);
  digitalWrite(cs_adc2, LOW);

  SPI.begin();
}

void reset(){
	mappedValues[16] = {0};
	averagedValues[16] = {0};

	bufferActive = 0;
	writePtrOne = &bufferOne[0];
	writePtrTwo = &bufferOne[8];
	bufferPtr = bufferTwo;



	addressIndex = 0;
	memoryIndex = 7;

	GPIOD_PDOR |= B0100;  //digitalWrite(en_adc1, HIGH); Active LOW thus disabled
	GPIOD_PDOR &= ~B1000;  //digitalWrite(cs_adc1, LOW); //short Pulse keep low

	GPIOC_PDOR |= B1000;   //digitalWrite(en_adc2, HIGH); //DISABLE the buffers DAC2
	GPIOC_PDOR &= ~B10000; //digitalWrite(cs_adc2, LOW);
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
 * GPIOD_PDOR |= B1000; >> saves a bitshift
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
 *
 *
 */


void readSensors() {
  SPI.beginTransaction(settings);

  addressIndex = addressIndex & 7;
  memoryIndex = memoryIndex & 7;

  //Start Reading ADC1

  GPIOD_PDOR |= B1000; // pin 7 HIGH -> CS_ADC1
  delayMicroseconds(3); // delayMicroseconds 2 is to short

  GPIOD_PDOR &= ~B1100; // pin 7 & 8 LOW -> CS_ADC1 and EN_ADC1

  highVal = SPI.transfer(channelSelection[addressIndex]); //Send channel for next cycle and exhange MSB
  lowVal = SPI.transfer(0x00); //Send 8Bytes of 0x00 and store LSB

  writePtrOne[memoryIndex] += (highVal<<8) + lowVal;

  //Finished disable buffers ADC
  GPIOD_PDOR |= B0100; //digitalWrite(EN_ADC, HIGH); //DISABLE the buffers ADC1

  //Start Reading ADC1
  GPIOC_PDOR |= B10000; //  digitalWrite(CS_ADC, HIGH);
  delayMicroseconds(3);

  GPIOC_PDOR  &= ~B11000;  	  //digitalWrite(CS_ADC2, LOW);
  	  	  	  	  	  	  	  //digitalWrite(EN_ADC2, LOW); //Enable the buffers DAC1

  highVal = SPI.transfer(channelSelection[addressIndex]); //Send channel for next cycle and exhange MSB
  lowVal = SPI.transfer(0x00); //Send 8Bytes of 0x00 and store LSB

  writePtrTwo[memoryIndex] += (highVal<<8) + lowVal; //The pointer is offsetted to the eight element of the buffer
  	  	  	  	  	  	  	  	  	  	  	  	  	 //This in effect eliminates an instruction in the loop
  	  	  	  	  	  	  	  	  	  	  	  	  	 //Make sure the pointer doesn't read off memory outside the loop


  //Finished disable tristate buffers ADC2
  GPIOC_PDOR |= B1000; //digitalWrite(en_adc2, HIGH); //DISABLE the buffers DAC2

  addressIndex++;
  memoryIndex++;

  SPI.endTransaction();
}

void swapBuffer(){
	bufferActive = !bufferActive;

	if(bufferActive == 0){
		writePtrOne = &bufferOne[0];
		writePtrTwo = &bufferOne[8];
		bufferPtr = bufferTwo;
	} else {
		writePtrOne = &bufferTwo[0];
		writePtrTwo = &bufferTwo[8];
		bufferPtr = bufferOne;
	}
}



/* Optimize use double buffering
 * and swap the buffers
 */

void calculateAverage(){
  uint16_t tmpValue;
  int bufferIndex = 0;

  while(bufferIndex < 8){
	  //sensors[i] are (128)summed up values by
	  //by bit shifting with >> 7 a fast division of 128 takes place

	  tmpValue = (bufferPtr[bufferIndex] >> 7) & 0xFFFF ;

	  if(tmpValue <= (averagedValues[bufferIndex] - offsetTable[bufferIndex]) || tmpValue >= (averagedValues[bufferIndex] + offsetTable[bufferIndex])){
		  averagedValues[bufferIndex] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[bufferIndex][0] , mapTable[bufferIndex][1]);

		  mappedValues[bufferIndex] = (tmpValue - mapTable[bufferIndex][1])*(16384-0) / (mapTable[bufferIndex][0] - mapTable[bufferIndex][1]) + 0;
	  }
	  tmpValue = 0;
	  bufferPtr[bufferIndex] = 0; // reset and start summing the values again

	  bufferIndex++;
  }

  while(bufferIndex < 11){
	  tmpValue = bufferPtr[bufferIndex] >> 7;

	  if(tmpValue <= (averagedValues[bufferIndex] - offsetTable[bufferIndex]) || tmpValue >= (averagedValues[bufferIndex] + offsetTable[bufferIndex])){
		  averagedValues[bufferIndex] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[bufferIndex][0] , mapTable[bufferIndex][1]);
		  mappedValues[bufferIndex] = (tmpValue - mapTable[bufferIndex][1]) * (0 - 16384) / (mapTable[bufferIndex][0] - mapTable[bufferIndex][1]) + 16384;
	  }
	  tmpValue = 0;
	  bufferPtr[bufferIndex] = 0; // reset and start summing the values again

	  bufferIndex++;
  }

  while(bufferIndex < 16){
	  tmpValue = bufferPtr[bufferIndex] >> 7;

	  if(tmpValue <= (averagedValues[bufferIndex] - offsetTable[bufferIndex]) || tmpValue >= (averagedValues[bufferIndex] + offsetTable[bufferIndex])){
		  averagedValues[bufferIndex] = tmpValue;
		  tmpValue = constrain(tmpValue, mapTable[bufferIndex][0] , mapTable[bufferIndex][1]);
		  mappedValues[bufferIndex] = (tmpValue - mapTable[bufferIndex][1])*(16384-0) / (mapTable[bufferIndex][0] - mapTable[bufferIndex][1]) + 0;

	 }
	 tmpValue = 0;
	 bufferPtr[bufferIndex] = 0; // reset and start summing the values again

	 bufferIndex++;
  }

	}
} // namespace ltc1867


