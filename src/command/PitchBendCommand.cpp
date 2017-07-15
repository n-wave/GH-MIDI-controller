/*
 * PitchBendCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "PitchBendCommand.h"
#include "../testing/configuration.h"

PitchBendCommand::PitchBendCommand() :
	channel(0),
	pbValue(0)
{}

PitchBendCommand::PitchBendCommand(const uint8_t channel,
								   const uint16_t pbValue)
  : channel(channel),
	pbValue(pbValue)
{
}

PitchBendCommand::~PitchBendCommand() {
#ifdef DEBUG
	Serial.println("PitchBendCommand Destructor called");
#endif /* DEBUG */
}

void PitchBendCommand::operator ()() const {
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("       Pitch Bend       ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel      : ");
	Serial.println(channel);
	Serial.print("Printing pbValue      : ");
	Serial.println(pbValue);
#endif /* DEBUG */
}
