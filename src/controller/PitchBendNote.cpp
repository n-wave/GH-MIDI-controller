/*
 * PitchBendNote.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "PitchBendNote.h"

PitchBendNote::PitchBendNote() :
	channel(0),
	pitch(0),
	velocity(0),
	parameter(0)
{
}

PitchBendNote::PitchBendNote(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	parameter(0)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("PitchBendNote successfully initialized");
	} else {
		Serial.println("Error occurred in PitchBendNote while loading data");
	}
#endif /* DEBUG */
}

PitchBendNote::~PitchBendNote() {
	// TODO Auto-generated destructor stub
}

void PitchBendNote::execute(){

}

void PitchBendNote::update(const uint32_t* time) {

}

void PitchBendNote::setParameter(const uint16_t* value) {
	parameter = *value;
}

uint16_t PitchBendNote::getParameter() {
	return parameter;
}

boolean PitchBendNote::setConfiguration(const int* data) {
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == id &&
		data[5] == 0xFF
	  )
	{
		channel = data[2];
		pitch = data[3];
		velocity = data[4];
		result = true;
	}
	return result;
}

#ifdef DEBUG
String PitchBendNote::toString(){
	String result = String("Pitch Bend Note \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Pitch        : " + pitch + "\n";
	result += (String)"Velocity     : " + velocity + "\n";
	result += (String)"Parameter    : " + parameter + "\n";
	return result;

	return result;
}
#endif
