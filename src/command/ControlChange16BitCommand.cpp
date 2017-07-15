/*
 * ControlChange16BitCommand.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "ControlChange16BitCommand.h"
#include "../testing/configuration.h"

ControlChange16BitCommand::ControlChange16BitCommand() :
	channel(0),
	ccNumberMSB(0),
	ccValueMSB(0),
	ccNumberLSB(0),
	ccValueLSB(0)
{
	// TODO Auto-generated constructor stub

}

ControlChange16BitCommand::ControlChange16BitCommand(const uint8_t& channel,
													  const uint8_t& ccNumberMSB,
													  const uint8_t& ccValueMSB,
													  const uint8_t& ccNumberLSB,
													  const uint8_t& ccValueLSB)
  : channel(channel),
	ccNumberMSB(ccNumberMSB),
	ccValueMSB(ccValueMSB),
	ccNumberLSB(ccNumberLSB),
	ccValueLSB(ccValueLSB)
{
	// TODO Auto-generated destructor stub
}

ControlChange16BitCommand::~ControlChange16BitCommand(){
#ifdef DEBUG
	Serial.println("ControlChange16BitCommand Destructor called");
#endif
}

void ControlChange16BitCommand::operator ()() const {
#ifdef DEBUG
	Serial.println("_----------------------_");
	Serial.println("  Control Change 16Bit  ");
	Serial.println("-_-_-_-_-_-_-_-_-_-_-_-_");

	Serial.print("Printing Channel      : ");
	Serial.println(channel);
	Serial.print("Printing ccNumberMSB  : ");
	Serial.println(ccNumberMSB);
	Serial.print("Printing ccValueMSB   : ");
	Serial.println(ccNumberLSB);
	Serial.print(ccValueLSB);
#endif /* DEBUG */
}
