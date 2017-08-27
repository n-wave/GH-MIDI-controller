/*
 * PitchBendNoteRibbon.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "../../command/NoteVelocityCommand.h"
#include "../../command/PitchBendCommand.h"
#include "../../command/PitchBendNoteCommand.h"
#include "PitchBendNoteRibbon.h"

PitchBendNoteRibbon::PitchBendNoteRibbon() :
	channel(0),
	pitch(0),
	velocity(0),
	value14Bit(0),
	parameter(0),
	updated(false),
	sendNote(false),
	dispatcher(NULL)
{
}

PitchBendNoteRibbon::PitchBendNoteRibbon(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	value14Bit(0),
	parameter(0),
	updated(false),
	sendNote(false),
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

PitchBendNoteRibbon::PitchBendNoteRibbon(const int* data, Dispatcher* dispatcher) :
	channel(0),
	pitch(0),
	velocity(0),
	value14Bit(0),
	parameter(0),
	updated(false),
	sendNote(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("PitchBendNoteRibbon successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in PitchBendNoteRibbon while loading data");
	}
#endif /* DEBUG */
}

PitchBendNoteRibbon::~PitchBendNoteRibbon() {
	dispatcher = NULL;
}


/* PitchBendNoteRibbon::update()
 *
 * Calculate values.
 *
 * add new PitchBendNoteRibbon Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t pitch
 * arg 3: uint8_t velocity
 * arg 4: uint16_t pbValue
 *
 */


void PitchBendNoteRibbon::update(const uint32_t* time) {
	if(updated){
		if(value14Bit != 0){
			if(sendNote){
				dispatcher->addCommand(new PitchBendNoteCommand(channel,
																pitch,
																velocity,
																value14Bit));
			} else {
				dispatcher->addCommand(new PitchBendCommand(channel,
														    value14Bit));
			}
			sendNote = false;
		} else {
			dispatcher->addCommand(new PitchBendNoteCommand(channel,
															pitch,
															0,
															0));
			sendNote = false;
		}
		updated = false;
	}
}

void PitchBendNoteRibbon::setParameter(const uint16_t* value) {
	uint16_t tmp = *value >> 2;

	if(tmp != value14Bit){
		if(value14Bit == 0){
			sendNote = true;
		}

		parameter = *value;
		value14Bit = tmp;
		updated = true;
	}
}

uint16_t PitchBendNoteRibbon::getParameter() {
	return parameter;
}

boolean PitchBendNoteRibbon::setConfiguration(const int* data) {
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
void PitchBendNoteRibbon::printContents(){
	String result = String("Pitch Bend Note \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Pitch        : " + pitch + "\n";
	result += (String)"Velocity     : " + velocity + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	Serial.println(result);
}
#endif
