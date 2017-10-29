/*
 * NoteControlChange16BitCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "NoteControlChange16BitCommand.h"
#include "../testing/configuration.h"

NoteControlChange16BitCommand::NoteControlChange16BitCommand() :
	channel(0),
	pitch(0),
	velocity(0),
	ccNumberMSB(0),
	ccValueMSB(0),
	ccNumberLSB(0),
	ccValueLSB(0)
{
}

NoteControlChange16BitCommand::NoteControlChange16BitCommand(const uint8_t& channel,
															 const uint8_t& pitch,
															 const uint8_t& velocity,
															 const uint8_t& ccNumberMSB,
															 const uint8_t& ccValueMSB,
															 const uint8_t& ccNumberLSB,
															 const uint8_t& ccValueLSB)
  : channel(channel),
	pitch(pitch),
	velocity(velocity),
	ccNumberMSB(ccNumberMSB),
	ccValueMSB(ccValueMSB),
	ccNumberLSB(ccNumberLSB),
	ccValueLSB(ccValueLSB)
{
}

NoteControlChange16BitCommand::~NoteControlChange16BitCommand() {

#ifdef DEBUG
	Serial.println("NoteControlChange16BitCommand Destructor called");
#endif /* DEBUG */
}

void NoteControlChange16BitCommand::operator ()() const {
	usbMIDI.sendNoteOn(pitch, velocity, channel);
	usbMIDI.sendControlChange(ccNumberMSB, ccValueMSB, channel);
	usbMIDI.sendControlChange(ccNumberLSB, ccValueLSB, channel);
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("Note ControlChange 16Bit");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel      : ");
	Serial.println(pitch);
	Serial.print("Printing Pitch        : ");
	Serial.println(pitch);
	Serial.print("Printing Velocity     : ");
	Serial.println(velocity);
	Serial.print("Printing ccNumberMSB  : ");
	Serial.println(ccNumberMSB);
	Serial.print("Printing ccValueMSB  : ");
	Serial.println(ccValueMSB);
	Serial.print("Printing ccNumberLSB  : ");
	Serial.println(ccNumberLSB);
	Serial.print("Printing ccValueLSB  : ");
	Serial.println(ccValueLSB);
#endif /* DEBUG */
}
