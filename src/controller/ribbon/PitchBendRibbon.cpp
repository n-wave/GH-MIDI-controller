/*
 * PitchBend.cpp
 *
 *  Created on: Jul 5, 2017
 *      Author: mario
 */

#include "../../command/PitchBendCommand.h"
#include "PitchBendRibbon.h"

PitchBendRibbon::PitchBendRibbon() :
	channel(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
}

PitchBendRibbon::PitchBendRibbon(const int* data) :
	channel(0),
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
		Serial.println("PitchBend successfully initialized");
	} else {
		Serial.println("Error occurred in PitchBend while loading data");
	}
#endif /* DEBUG */
}

PitchBendRibbon::PitchBendRibbon(const int* data, Dispatcher* dispatcher) :
	channel(0),
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
		Serial.println("PitchBend successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in PitchBend while loading data");
	}
#endif /* DEBUG */
}

PitchBendRibbon::~PitchBendRibbon(){
	dispatcher = NULL;
}


/* PitchBend::update()
 *
 * Calculate values.
 *
 * add new PitchBend Command
 *
 * arg 1: uint8_t channel
 * arg 2: uint16_t pbValue
 *
 */

void PitchBendRibbon::update(){
	if(updated){
		dispatcher->addCommand(new PitchBendCommand(channel, parameter));
		updated = false;
	}
}

void PitchBendRibbon::setParameter(const uint16_t* value){
	uint16_t tmp = *value;

	if(tmp != parameter){
		parameter = tmp;
		updated = true;
	}
}

boolean PitchBendRibbon::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[3] == 0xFF
	  )
	{
		channel = data[2];
		result = true;
	}

	return result;
}

#ifdef DEBUG
void PitchBendRibbon::printContents(){
	String result = String("Pitch Bend \n");
	result += (String)"MIDI Channel : " + channel + "\n";
	result += (String)"Parameter    : " + parameter + "\n";

	Serial.println(result);
}
#endif /* DEUUG */
