/*
 * PitchBendNoteCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "PitchBendNoteCommand.h"
#include "../testing/configuration.h"

PitchBendNoteCommand::PitchBendNoteCommand() :
	channel(0),
	pitch(0),
	velocity(0),
	pbValue(0)
{
	// TODO Auto-generated constructor stub
}

PitchBendNoteCommand::PitchBendNoteCommand(const uint8_t& channel,
										   const uint8_t& pitch,
										   const uint8_t& velocity,
										   const uint16_t& pbValue)
  : channel(channel),
	pitch(pitch),
	velocity(velocity),
	pbValue(pbValue)
{
}

PitchBendNoteCommand::~PitchBendNoteCommand() {
#ifdef DEBUG
	Serial.println("PitchBendNoteCommand Destructor called");
#endif /* DEBUG */
}

void PitchBendNoteCommand::operator ()() const {
	usbMIDI.sendNoteOn(pitch, velocity, channel);
    usbMIDI.sendPitchBend(pbValue, channel);
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("     Pitch Bend Note    ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel      : ");
	Serial.println(channel);
	Serial.print("Printing Pitch        : ");
	Serial.println(pitch);
	Serial.print("Printing Velocity     : ");
	Serial.println(velocity);
	Serial.print("Printing pbValue      : ");
	Serial.println(pbValue);
#endif
}
