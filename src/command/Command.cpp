/*
 * Command.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: mario
 */

#include "Command.h"
#include "Arduino.h"
#include "../testing/configuration.h"

Command::Command() {
	// Abstract virtual class nothing to do.
}

Command::~Command() {
	// TODO Auto-generated destructor stub
#ifdef DEBUG
	Serial.println("Command Destructor called");
#endif /* DEBUG */
}

