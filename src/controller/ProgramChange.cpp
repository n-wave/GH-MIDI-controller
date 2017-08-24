/*
 * ProgramChange.cpp
 *
 *  Created on: Jul 4, 2017
 *      Author: mario
 */

#include "ProgramChange.h"

#include "../command/ProgramChangeCommand.h"


ProgramChange::ProgramChange() :
	channel(0),
	bank(0),
	program(0),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
}

ProgramChange::ProgramChange(const int* data) :
	channel(0),
	bank(0),
	program(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ProgramChange successfully initialized");
	} else {
		Serial.println("Error occurred in ProgramChange while loading data");
	}
#endif /* DEBUG */
}

ProgramChange::ProgramChange(const int* data, Dispatcher* dispatcher) :
	channel(0),
	bank(0),
	program(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ProgramChange successfully initialized and dispatcher successfully assigned");
	} else {
		Serial.println("Error occurred in ProgramChange while loading data");
	}
#endif /* DEBUG */
}


ProgramChange::~ProgramChange() {
	dispatcher = NULL;
}


/* ProgramChange::update()
 *
 * Calculate values.
 *
 * add new Program Change Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t bank
 * arg 3: uint8_t program
 *
 */

void ProgramChange::update(const uint32_t* time){
	dispatcher->addCommand(new ProgramChangeCommand(0, 50, 100));
}

void ProgramChange::setParameter(const uint16_t * value){}

uint16_t ProgramChange::getParameter(){
	return -1;
}

boolean ProgramChange::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[5] == 0xFF
	  )
	{
		channel = data[2];
		bank = data[3];
		program = data[4];

		result = true;
	}

	return result;
}

#ifdef DEBUG
    void ProgramChange::printContents(){
    	String result = String("Program Change \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Bank         : " + bank + "\n";
    	result += (String)"program      : " + program + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
