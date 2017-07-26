/*
 * NoteControlChange8BitCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "NoteControlChange8BitCommand.h"
#include "../testing/configuration.h"

NoteControlChange8BitCommand::NoteControlChange8BitCommand() :
	channel(0),
	pitch(0),
	velocity(0),
	ccNumber(0),
	ccValue(0)
{
}

NoteControlChange8BitCommand::NoteControlChange8BitCommand(const uint8_t& channel,
														   const uint8_t& pitch,
														   const uint8_t& velocity,
														   const uint8_t& ccNumber,
														   const uint8_t& ccValue)
  : channel(channel),
	pitch(pitch),
	velocity(velocity),
	ccNumber(ccNumber),
	ccValue(ccValue)
{
}

NoteControlChange8BitCommand::~NoteControlChange8BitCommand() {
#ifdef DEBUG
	Serial.println("NoteControlChange8BitCommand Destructor called");
#endif /* DEBUG */
}

void NoteControlChange8BitCommand::operator ()() const {
	usbMIDI.sendNoteOn(pitch, velocity, channel);
	usbMIDI.sendControlChange(ccNumber, ccValue, channel);
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("Note ControlChange 8bit ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel      : ");
	Serial.println(channel);
	Serial.print("Printing Pitch        : ");
	Serial.println(pitch);
	Serial.print("Printing Velocity     : ");
	Serial.println(velocity);
	Serial.print("Printing ccNumber     : ");
	Serial.println(ccNumber);
	Serial.print("Printing ccValue      : ");
	Serial.println(ccValue);
#endif
}
