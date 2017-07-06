/*
 * ControlChangeFade8Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "ControlChangeFade8Bit.h"

ControlChangeFade8Bit::ControlChangeFade8Bit() :
	channel(0),
	controlChangeNumber(0),
	start(0),
	hold(0),
	end(0),
	fadeIn(0),
	fadeOut(0),
	parameter(0)
{
}

ControlChangeFade8Bit::~ControlChangeFade8Bit() {
	// TODO Auto-generated destructor stub
}

void ControlChangeFade8Bit::execute() {

}

void ControlChangeFade8Bit::update(const uint32_t* time) {

}

void ControlChangeFade8Bit::setParameter(const uint16_t* value) {
	parameter = *value;
}

uint16_t ControlChangeFade8Bit::getParameter() {
	return parameter;
}

boolean ControlChangeFade8Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
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

uint16_t ControlChangeFade8Bit::convertBytesTo16Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0XFF) << 8;
	uint16_t LSB = lsb & 0xFF;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
String ControlChangeFade8Bit::toString(){
	String result = String("Control Change Fade 8Bit");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"CC number    : " + controlChangeNumber + "\n";
	result += (String)"Start        : " + start + "\n";
	result += (String)"Hold         : " + hold + "\n";
	result += (String)"End          : " + end + "\n";
	result += (String)"FadeIn       : " + fadeIn + "\n";
	result += (String)"FadeOut      : " + fadeOut + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	return result;
}
#endif /* DEBUG */
