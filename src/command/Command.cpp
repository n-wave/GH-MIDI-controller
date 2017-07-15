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
	// TODO Auto-generated constructor stub

}

Command::~Command() {
	// TODO Auto-generated destructor stub
#ifdef DEBUG
	Serial.println("Command Destructor called");
#endif /* DEBUG */
}

