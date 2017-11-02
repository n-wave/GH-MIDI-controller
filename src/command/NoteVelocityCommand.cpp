/*
 * NoteVelocityCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "NoteVelocityCommand.h"
#include "../testing/configuration.h"

NoteVelocityCommand::NoteVelocityCommand() :
	channel(0),
	pitch(0),
	velocity(0)
{
}

NoteVelocityCommand::NoteVelocityCommand(const uint8_t& channel,
										 const uint8_t& pitch,
										 const uint8_t& velocity)
  : channel(channel),
	pitch(pitch),
	velocity(velocity)
{
}

NoteVelocityCommand::~NoteVelocityCommand() {
#ifdef DEBUG
	Serial.println("NoteVelocityCommand Destructor called");
#endif /* DEBUG */
}

void NoteVelocityCommand::operator ()() const {
	usbMIDI.sendNoteOn(pitch, velocity, channel);
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("      Note Velocity     ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel    : ");
	Serial.println(channel);
	Serial.print("Printing pitch      : ");
	Serial.println(pitch);
	Serial.print("Printing velocity   : ");
	Serial.println(velocity);
#endif
}
