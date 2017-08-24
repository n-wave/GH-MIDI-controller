/*
 * PitchBendNote.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "PitchBendNote.h"
#include "../../command/PitchBendNoteCommand.h"

PitchBendNote::PitchBendNote() :
	channel(0),
	pitch(0),
	velocity(0),
	parameter(0),
	dispatcher(NULL)
{
}

PitchBendNote::PitchBendNote(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	parameter(0),
	dispatcher(NULL)
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

PitchBendNote::PitchBendNote(const int* data, Dispatcher* dispatcher) :
	channel(0),
	pitch(0),
	velocity(0),
	parameter(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("PitchBendNote successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in PitchBendNote while loading data");
	}
#endif /* DEBUG */
}

PitchBendNote::~PitchBendNote() {
	dispatcher = NULL;
}


/* PitchBendNote::update()
 *
 * Calculate values.
 *
 * add new PitchBendNote Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t pitch
 * arg 3: uint8_t velocity
 * arg 4: uint16_t pbValue
 *
 */


void PitchBendNote::update(const uint32_t* time) {
	dispatcher->addCommand(new PitchBendNoteCommand(0, 60, 100, 14000));
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
		data[1] == ID &&
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
void PitchBendNote::printContents(){
	String result = String("Pitch Bend Note \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Pitch        : " + pitch + "\n";
	result += (String)"Velocity     : " + velocity + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	Serial.println(result);
}
#endif
