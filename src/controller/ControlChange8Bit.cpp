/*
 * ControlChange8Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "ControlChange8Bit.h"

ControlChange8Bit::ControlChange8Bit() :
	channel(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0)
{
	// TODO Auto-generated constructor stub
}

ControlChange8Bit::~ControlChange8Bit() {
	// TODO Auto-generated destructor stub
}

void ControlChange8Bit::execute() {

}

void ControlChange8Bit::update(const uint32_t* time) {

}

void ControlChange8Bit::setParameter(const uint16_t* value) {
	parameter = *value;
}

uint16_t ControlChange8Bit::getParameter() {
	return parameter;
}

boolean ControlChange8Bit::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[3] == 0x00 &&
		data[7] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumber = data[4];
		topValue = data[5];
		bottomValue = data[6];

		result = true;
	}

	return result;
}

#ifdef DEBUG
    String ControlChange8Bit::toString(){
    	String result = String("Control Change 8Bit");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	return result;
    }
#endif /* DEBUG */
