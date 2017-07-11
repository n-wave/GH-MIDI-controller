/*
 * NoteControlChange8Bit.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "NoteControlChange8Bit.h"

NoteControlChange8Bit::NoteControlChange8Bit() :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0)
{
}

NoteControlChange8Bit::NoteControlChange8Bit(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	controlChangeNumber(0),
	topValue(0),
	bottomValue(0),
	parameter(0)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteControlChange8Bit successfully initialized");
	} else {
		Serial.println("Error occurred in NoteControlChange8Bit while loading data");
	}
#endif /* DEBUG */
}

NoteControlChange8Bit::~NoteControlChange8Bit() {
	// TODO Auto-generated destructor stub
}

void NoteControlChange8Bit::execute(){

}

void NoteControlChange8Bit::update(const uint32_t* time){

}

void NoteControlChange8Bit::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t NoteControlChange8Bit::getParameter(){
	return parameter;
}

boolean NoteControlChange8Bit::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[6] == 0x00 &&
		data[10] == 0xFF
      )
	{
		channel = data[2];
		pitch = data[3];
		velocity = data[4];
		velocityOption = data[5];
		controlChangeNumber = data[7];
		topValue = data[8];
		bottomValue = data[9];
		result = true;
	}
	return result;
}

#ifdef DEBUG
    void NoteControlChange8Bit::printContents(){
    	String result = String("Note Control Change 8 Bit \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     ; " + velocity + "\n";
    	result += (String)"Vel Option   : " + velocityOption + "\n";
    	result += (String)"CC nr        : " + controlChangeNumber + "\n";
    	result += (String)"TopValue     : " + topValue + "\n";
    	result += (String)"BottomValue  : " + bottomValue + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
