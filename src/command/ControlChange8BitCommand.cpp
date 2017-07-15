/*
 * ControlChange8BitCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "ControlChange8BitCommand.h"
#include "../testing/configuration.h"

ControlChange8BitCommand::ControlChange8BitCommand() :
	channel(0),
	ccNumber(0),
	ccValue(0)
{
}

ControlChange8BitCommand::ControlChange8BitCommand(const uint8_t& channel,
												   const uint8_t& ccNumber,
												   const uint8_t& ccValue)
  : channel(channel),
	ccNumber(ccNumber),
	ccValue(ccValue)
{
}

ControlChange8BitCommand::~ControlChange8BitCommand() {
#ifdef DEBUG
	Serial.println("ControlChange8BitCommand Destructor called");
#endif /* DEBUG */
}

void ControlChange8BitCommand::operator ()() const {
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("  Control Change 8Bit   ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel      : ");
	Serial.println(channel);
	Serial.print("Printing ccNumber     : ");
	Serial.println(ccNumber);
	Serial.print("Printing ccValue      : ");
	Serial.println(ccValue);
#endif /* DEBUG */
}
