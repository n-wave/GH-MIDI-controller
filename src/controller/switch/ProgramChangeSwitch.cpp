/*
 * ProgramChangeSwitch.cpp
 *
 *  Created on: Aug 29, 2017
 *      Author: mario
 */

#include "ProgramChangeSwitch.h"

#include "../../command/ProgramChangeCommand.h"

ProgramChangeSwitch::ProgramChangeSwitch() :
	channel(0),
	bank(0),
	program(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
}

ProgramChangeSwitch::ProgramChangeSwitch(const int* data) :
	channel(0),
	bank(0),
	program(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("ProgramChangeSwitch successfully initialized");
	} else {
		Serial.println("Error occurred in ProgramChangeSwitch while loading data");
	}
#endif /* DEBUG */
}

ProgramChangeSwitch::ProgramChangeSwitch(const int* data, Dispatcher* dispatcher) :
	channel(0),
	bank(0),
	program(0),
	parameter(0),
	updated(false),
	dispatcher(dispatcher)
{
#ifndef DEBUG
	this->setConfiguration(data);
#endif

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

	if(success){
		Serial.println("ProgramChangeSwitch successfully initialized and dispatcher successfully assigned");
	} else {
		Serial.println("Error occurred in ProgramChangeSwitch while loading data");
	}
#endif /* DEBUG */
}


ProgramChangeSwitch::~ProgramChangeSwitch() {
	dispatcher = NULL;
}


/* ProgramChangeSwitch::update()
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

void ProgramChangeSwitch::update(){
	if(updated){
		if(parameter == 1){
			dispatcher->addCommand(new ProgramChangeCommand(channel, bank, program));
		}
		updated = false;
	}
}

void ProgramChangeSwitch::setParameter(const uint16_t * value)
{
	if(parameter != *value){
		parameter = *value;
		updated = true;
	}
}

boolean ProgramChangeSwitch::setConfiguration(const int* data){
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
    void ProgramChangeSwitch::printContents(){
    	String result = String("Program Change \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Bank         : " + bank + "\n";
    	result += (String)"program      : " + program + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
