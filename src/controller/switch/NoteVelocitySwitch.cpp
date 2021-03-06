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
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
}

NoteVelocitySwitch::NoteVelocitySwitch(const int* data) :
	channel(0),
	pitch(0),
	velocity(0),
	parameter(0),
	updated(false),
	dispatcher(NULL)
{
	this->setConfiguration(data);

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

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
	parameter(0),
	updated(false),
	dispatcher(dispatcher)
{
	this->setConfiguration(data);

#ifdef DEBUG
	boolean success = this->setConfiguration(data);

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

void NoteVelocitySwitch::update(){
	if(updated){
		uint8_t tmp = velocity*parameter;
		dispatcher->addCommand(new NoteVelocityCommand(channel, pitch, tmp));
		updated = false;
	}
}

/** Zero or one no bitshift needed **/
void NoteVelocitySwitch::setParameter(const uint16_t* value){
	if(parameter != *value){
		parameter = *value;
		updated = true;
	}
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
    	result += (String)"Parameter    : " + parameter + "\n";

    	Serial.println(result);
    }
#endif /* DEBUG */

