/*
 * ProgramChangeToggleToggle.cpp
 *
 *  Created on: Aug 28, 2017
 *      Author: mario
 */

#include "ProgramChangeToggle.h"

#include "../../command/ProgramChangeCommand.h"



ProgramChangeToggle::ProgramChangeToggle() :
	channel(0),
	bank(0),
	program(0),
	parameter(0),
	ledPin(0),
	toggle(false),
	updated(false),
	dispatcher(NULL)
{
	// TODO Auto-generated constructor stub
}

ProgramChangeToggle::ProgramChangeToggle(const int* data) :
	channel(0),
	bank(0),
	program(0),
	parameter(0),
	ledPin(0),
	toggle(false),
	updated(false),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ProgramChangeToggle successfully initialized");
	} else {
		Serial.println("Error occurred in ProgramChangeToggle while loading data");
	}
#endif /* DEBUG */
}

ProgramChangeToggle::ProgramChangeToggle(const int* data, Dispatcher* dispatcher) :
	channel(0),
	bank(0),
	program(0),
	parameter(0),
	ledPin(0),
	toggle(false),
	updated(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("ProgramChangeToggle successfully initialized and dispatcher successfully assigned");
	} else {
		Serial.println("Error occurred in ProgramChangeToggle while loading data");
	}
#endif /* DEBUG */
}

ProgramChangeToggle::ProgramChangeToggle(const int* data, uint8_t ledPin, Dispatcher* dispatcher) :
	channel(0),
	bank(0),
	program(0),
	parameter(0),
	ledPin(0),
	toggle(false),
	updated(false),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);

#ifdef DEBUG
	if(success){
		Serial.println("ProgramChangeToggle successfully initialized and dispatcher successfully assigned");
	} else {
		Serial.println("Error occurred in ProgramChangeToggle while loading data");
	}
#endif /* DEBUG */
}

ProgramChangeToggle::~ProgramChangeToggle() {
	dispatcher = NULL;
}


/* ProgramChangeToggle::update()
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

void ProgramChangeToggle::update(const uint32_t* time){
	if(updated){
		if(toggle){
			dispatcher->addCommand(new ProgramChangeCommand(channel, bank, program));
		}
		digitalWrite(ledPin, toggle);
		updated = false;
	}
}

void ProgramChangeToggle::setParameter(const uint16_t * value){
	if(parameter != *value){
		parameter = *value;
		toggle = !toggle;

		updated = true;
	}
}

uint16_t ProgramChangeToggle::getParameter(){
	return parameter;
}

boolean ProgramChangeToggle::setConfiguration(const int* data){
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
    void ProgramChangeToggle::printContents(){
    	String result = String("Program Change \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Bank         : " + bank + "\n";
    	result += (String)"program      : " + program + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */
