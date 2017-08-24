/*
 * ControlChangeFadeSwitch8Bit.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "ControlChangeFadeSwitch8Bit.h"
#include "../../command/ControlChange8BitCommand.h"

ControlChangeFadeSwitch8Bit::ControlChangeFadeSwitch8Bit() :
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	dispatcher(NULL)
{
}

ControlChangeFadeSwitch8Bit::ControlChangeFadeSwitch8Bit(const int* data) :
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFadeSwitch8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in ControlChangeFadeSwitch8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeSwitch8Bit::ControlChangeFadeSwitch8Bit(const int* data, Dispatcher* dispatcher) :
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ControlChangeFadeSwitch8Bit successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in ControlChangeFadeSwitch8Bit while loading data");
	}
#endif /* DEBUG */
}

ControlChangeFadeSwitch8Bit::~ControlChangeFadeSwitch8Bit() {
	dispatcher = NULL;
}


/* ControlChangeFadeSwitch8Bit::update()
 *
 * Calculate values.
 *
 * add new PitchBendNote Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t ccNumber
 * arg 3: uint8_t ccValue
 *
 */

void ControlChangeFadeSwitch8Bit::update(const uint32_t* time) {
	dispatcher->addCommand(new ControlChange8BitCommand(5, 14, 127));
}

void ControlChangeFadeSwitch8Bit::setParameter(const uint16_t* value) {
	parameter = *value;
}

uint16_t ControlChangeFadeSwitch8Bit::getParameter() {
	return parameter;
}

boolean ControlChangeFadeSwitch8Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[3] == 0x00 &&
		data[12] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumber = data[4];
		start = data[5];
		hold = data[6];
		end = data[7];
		fadeIn = this->convertBytesTo16Bit(data[8], data[9]);
		fadeOut = this->convertBytesTo16Bit(data[10], data[11]);

		result = true;
	}

	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  16Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChangeFadeSwitch8Bit::convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0XFF) << 8;
	uint16_t LSB = lsb & 0xFF;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
void ControlChangeFadeSwitch8Bit::printContents(){
	String result = String("Control Change Fade Switch 8Bit \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"CC number    : " + controlChangeNumber + "\n";
	result += (String)"Start        : " + start + "\n";
	result += (String)"Hold         : " + hold + "\n";
	result += (String)"End          : " + end + "\n";
	result += (String)"FadeIn       : " + fadeIn + "\n";
	result += (String)"FadeOut      : " + fadeOut + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	Serial.println(result);
}
#endif /* DEBUG */
