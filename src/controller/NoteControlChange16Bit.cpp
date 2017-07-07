/*
 * NoteControlChange16Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "NoteControlChange16Bit.h"

NoteControlChange16Bit::NoteControlChange16Bit() :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumberMSB(0),
	controlChangeNumberLSB(0),
	topValue(0),
	bottomValue(0),
	parameter(0)
{
	// TODO Auto-generated constructor stub
}

NoteControlChange16Bit::~NoteControlChange16Bit() {
	// TODO Auto-generated destructor stub
}

void NoteControlChange16Bit::execute(){

}

void NoteControlChange16Bit::update(const uint32_t* value){

}

void NoteControlChange16Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t NoteControlChange16Bit::getParameter(){
	return parameter;
}

boolean NoteControlChange16Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[6] == 0x01 &&
		data[12] == 0xFF
	  )
	{
		channel = data[2];
		pitch = data[3];
		velocity = data[4];
		velocityOption = data[5];
		controlChangeNumberMSB = data[7];
		controlChangeNumberLSB = controlChangeNumberMSB + 32;

		topValue = this->convertBytesTo14Bit(data[8], data[9]);
		bottomValue = this->convertBytesTo14Bit(data[10], data[11]);

		result = true;
	}

	return result;
}
/**
 *  Convert Supplied MSB and LSB values to the
 *  14Bit value they represent, store and return
 *  the result in a 16Bit value
 */

uint16_t NoteControlChange16Bit::convertBytesTo14Bit(uint8_t msb, uint8_t lsb){
	uint16_t result = 0;
	uint16_t MSB = (msb & 0x7F) << 7;
	uint16_t LSB = lsb & 0x7F;

	result = MSB | LSB;

	return result;
}

#ifdef DEBUG
    String NoteControlChange16Bit::toString(){
    	String result = String("Note Control Change 16Bit \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"Vel Option   : " + velocityOption + "\n";
    	result += (String)"CC nr MSB    : " + controlChangeNumberMSB + "\n";
    	result += (String)"CC nr LSB    : " + controlChangeNumberLSB + "\n";
    	result += (String)"Top Value    : " + topValue + "\n";
    	result += (String)"Bottom Value : " + bottomValue + "\n";

    	result += (String)"Parameter    : " + parameter + "\n";
    	return result;

    	return result;
    }
#endif /* DEBUG */


