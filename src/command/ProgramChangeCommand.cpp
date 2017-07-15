/*
 * ProgramChangeCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "ProgramChangeCommand.h"
#include "../testing/configuration.h"

ProgramChangeCommand::ProgramChangeCommand() :
	channel(0),
	bank(0),
	program(0)
{
	// TODO Auto-generated constructor stub

}

ProgramChangeCommand::ProgramChangeCommand (const uint8_t& channel,
											const uint8_t& bank,
											const uint8_t& program)
  :  channel(channel),
	 bank(bank),
	 program(program)
{
}

ProgramChangeCommand::~ProgramChangeCommand() {
#ifdef DEBUG
	Serial.println("ProgramChangeCommand Destructor called");
#endif /* DEBUG */
}

void ProgramChangeCommand::operator ()() const {
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("     Program Change     ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel    : ");
	Serial.println(channel);
	Serial.print("Printing Bank       : ");
	Serial.println(bank);
	Serial.print("Printing Program    : ");
	Serial.println(program);
#endif
}
