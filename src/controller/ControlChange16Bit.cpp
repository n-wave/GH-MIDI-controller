/*
 * ControlChange16Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "ControlChange16Bit.h"

ControlChange16Bit::ControlChange16Bit() :
	channel(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0)
{
}

ControlChange16Bit::~ControlChange16Bit() {
	// TODO Auto-generated destructor stub
}

void ControlChange16Bit::execute() {

}

void ControlChange16Bit::update(const uint32_t* time) {

}

void ControlChange16Bit::setParameter(const uint16_t* value) {

}

uint16_t ControlChange16Bit::getParameter() {
	return 0;
}

boolean ControlChange16Bit:: setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[3] == 0x01 &&
		data[9] == 0xFF
	  )
	{
		channel = data[2];
		controlChangeNumberMSB = data[4];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		topValue = this->convertBytesTo14Bit(data[5], data[6]);
		bottomValue = this->convertBytesTo14Bit(data[7], data[8]);

		result = true;
	}
	return result;
}

/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t ControlChange16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    String ControlChange16Bit::toString(){
    	String result = String("Control Change 16Bit \n");

    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	return result;
    }
#endif /* DEBUG */
