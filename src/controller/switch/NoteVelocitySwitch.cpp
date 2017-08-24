/*
 * NoteVelocitySwitch.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: mario
 */

#include "NoteVelocitySwitch.h"
#include "../../command/NoteVelocityCommand.h"

NoteVelocitySwitch::NoteVelocitySwitch() :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0),
	dispatcher(NULL)
{
}

NoteVelocitySwitch::NoteVelocitySwitch(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0),
	dispatcher(NULL)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteVelocitySwitch successfully initialized");
	} else {
		Serial.println("Error occurred in NoteVelocitySwitch::NoteVelocitySwitch(const int*) while loading data");
	}
#endif /* DEBUG */
}

NoteVelocitySwitch::NoteVelocitySwitch(const int* data, Dispatcher* dispatcher) :
	channel(0),
	pitch(0),
	velocity(0),
	velocityOption(0),
	parameter(0),
	dispatcher(dispatcher)
{
	boolean success = this->setConfiguration(data);

#ifdef DEBUG
	if(success){
		Serial.println("NoteVelocitySwitch successfully initialized and dispatcher assigned");
	} else {
		Serial.println("Error occurred in NoteVelocitySwitch::NoteVelocitySwitch(const int*, Dispatcher) while loading data");
	}
#endif /* DEBUG */
}

NoteVelocitySwitch::~NoteVelocitySwitch() {
	dispatcher = NULL;
}

/* NoteVelocitySwitch::update()
 *
 * Calculate values.
 *
 * add new NoteVelocitySwitchCommand
 *
 * arg 1: uint8_t channel
 * arg 2: uint8_t pitch
 * arg 3: uint8_t velocity
 *
 */

void NoteVelocitySwitch::update(const uint32_t* time){
	dispatcher->addCommand(new NoteVelocityCommand(16, 52, 110));
}

void NoteVelocitySwitch::setParameter(const uint16_t* value){
	parameter = *value;
}

uint16_t NoteVelocitySwitch::getParameter(){
	return parameter;
}

boolean NoteVelocitySwitch::setConfiguration(const int* data){
	boolean result = false;

	if(
		data[0] == 0xF0 &&
		data[1] == ID &&
		data[6] == 0xFF
	  )
	{
		channel = data[2];
		pitch = data[3];
		velocity = data[4];
		velocityOption = data[5];

		result = true;
	}
	return result;
}

#ifdef DEBUG
    void NoteVelocitySwitch::printContents(){
    	String result = String("Note Velocity Switch \n");
    	result += (String)"MIDI Channel : " + channel + "\n";
    	result += (String)"Pitch        : " + pitch + "\n";
    	result += (String)"Velocity     : " + velocity + "\n";
    	result += (String)"Vel Option   : " + velocityOption + "\n";
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

