/*
 * AllNotesOffCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "AllNotesOffCommand.h"
#include "../testing/configuration.h"

AllNotesOffCommand::AllNotesOffCommand() :
	channel(0),
	ccNumber(123),
	ccValue(0)
{
}

AllNotesOffCommand::~AllNotesOffCommand() {
#ifdef DEBUG
	Serial.println("AllNotesOffCommand Destructor called");
#endif /* DEBUG */
}

void AllNotesOffCommand::operator ()() const {
	usbMIDI.sendControlChange(ccNumber, ccValue, channel);
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("      All Notes Off     ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel      : ");
	Serial.println(channel);
	Serial.print("Printing ccNumber     : ");
	Serial.println(ccNumber);
	Serial.print("Printing ccValue      : ");
	Serial.println(ccValue);
#endif /* DEBUG */
}
